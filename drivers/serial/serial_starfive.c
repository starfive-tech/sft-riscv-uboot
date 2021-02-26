/*
 * Copyright (C) 2020 StarFive
 *
 * Modified to support VIC7100 SoC by StarFive
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

#include <common.h>
/* Driver Model for Serial is not defined */
//#include <dm.h>
#include <errno.h>
#include <watchdog.h>
#include <serial.h>
#include <linux/compiler.h>

#include <asm/io.h>
#include <asm/arch/global_reg.h>
#include <asm/arch/ezGPIO_fullMux_ctrl_macro.h>
#include <asm/arch/clkgen_ctrl_macro.h>
#include <asm/arch/rstgen_ctrl_macro.h>
#include <asm/arch/vic_module_reset_clkgen.h>

/* we don't need these, just backup */
#if 0
#define __io_bw()	__asm__ __volatile__("fence w,o" : : : "memory");
#define __io_aw()	do {} while (0)

/* Information about a serial port */

struct hive_serial_platdata {
	uint32_t base_addr;
};

/* HiFive unleashed UART register footprint */
typedef struct starfive_uart {
	u32 txdata;
	u32 rxdata;
	u32 txctrl;
	u32 rxctrl;
	u32 ie;
	u32 ip;
	u32 div;
} starfive_uart_t;
#endif

DECLARE_GLOBAL_DATA_PTR;

/* TXCTRL register */
#define UART_TXEN			0x1
#define UART_TXWM(x)		(((x) & 0xffff) << 16)

/* RXCTRL register */
#define UART_RXEN			0x1
#define UART_RXWM(x)		(((x) & 0xffff) << 16)

/* IP register */
#define UART_IP_TXWM		0x1
#define UART_IP_RXWM		0x2

#define UART_TXFIFO_FULL	0x80000000
#define UART_RXFIFO_EMPTY	0x80000000

#define  SER_RBR			(0x00)
#define  SER_THR			(0x00)
#define  SER_DLL			(0x00)
#define  SER_DLH			(0x04)
#define  SER_IER			(0x04)
#define  SER_IIR			(0x08)
#define  SER_FCR			(0x08)
#define  SER_LCR			(0x0C)
#define  SER_MCR			(0x10)
#define  SER_LSR			(0x14)
#define  SER_MSR			(0x18)
#define  SER_SCR			(0x1C)

//UART_LCR bit define
#define LCR_WORD_LEN5		(0<<0)
#define LCR_WORD_LEN6		(1<<0)
#define LCR_WORD_LEN7		(2<<0)
#define LCR_WORD_LEN8		(3<<0)
#define LCR_STOP_1BIT		(0<<2)
#define LCR_STOP_2BIT		(1<<2)
#define LCR_PE				(1<<3)
#define LCR_EPS				(1<<4)
#define LCR_SP				(1<<5)
#define LCR_BC				(1<<6)
#define LCR_DLAB			(1<<7)

//IER, interrupt enable reg
#define IER_ERBFI			(1<<0)  //rx interrupt enable
#define IER_ETBEI			(1<<1)  //tx interrupt enable
#define IER_ELSI			(1<<2)
#define IER_EDSSI			(1<<3)
#define IER_PTIME			(1<<7)

//IIR, interrupt identify reg
#define INTR_ID_RLSI		0x06
#define INTR_ID_DATAVL		0x04
#define INTR_ID_TIMEOUT		0x0C
#define INTR_ID_THR			0x02

//FCR
#define RCVR_TRIG_1C		(0x00 << 0x06) //1 char
#define RCVR_TRIG_QFL		(0x01 << 0x06) //1/4 FIFO
#define RCVR_TRIG_HFL		(0x02 << 0x06) //1/2 FIFO
#define RCVR_TRIG_LTF		(0x03 << 0x06) //2 less than full

#define TXEM_TRIG_EMT		(0x00 << 0x04) //FIFO empty
#define TXEM_TRIG_2C		(0x00 << 0x04) //2 char
#define TXEM_TRIG_QFL		(0x02 << 0x04) //1/4 FIFO
#define TXEM_TRIG_HFL		(0x03 << 0x04) //1/2 FIFO

#define DMA_MOD1			(0x01 << 0x03)
#define DMA_MOD0			(0x00 << 0x03)
#define TXFIFO_RST			(0x01 << 0x02)
#define RXFIFO_RST			(0x01 << 0x01)
#define FIFO_ENA			(0x01 << 0x00)

//LSR
#define DATA_RDY			(0x01<<0x00) //at least one byte available
#define RCV_OVERUN			(0x01<<0x01)
#define ERR_PARITY			(0x01<<0x02)
#define ERR_FRAMING			(0x01<<0x03)
#define ID_BREAK			(0x01<<0x04) //break interrupt bit
#define ID_THRE				(0x01<<0x05) //in FIFO THRE mode, it is the xmit fifo full flag !!!
#define ID_TEMPT			(0x01<<0x06)
#define ERR_RPE				(0x01<<0x07)

/* MCR */
#define MCR_DTR			 	(0x01<<0x00) /* dtr output */
#define MCR_RTS			 	(0x01<<0x01) /* rts output */
#define MCR_OUT1			(0x01<<0x02) /* output #1 */
#define MCR_OUT2			(0x01<<0x03) /* output #2 */
#define MCR_LOOP			(0x01<<0x04) /* loop back */
#define MCR_AFCE			(0x01<<0x05) /* auto flow control enable */

//#define DW_UART_BASE_ADDR	 SIFIVE_UART_BASE_ADDR

	static u32 starfive_uart_read(u32 reg)
	{
		return readl(SIFIVE_UART_BASE_ADDR + reg);
	}

static void starfive_uart_write(u32 ch,u32 reg)
{
	writel(ch,SIFIVE_UART_BASE_ADDR + reg);
}


static void starfive_uart_putc(const char ch)
{
	while (!(starfive_uart_read(SER_LSR)&ID_TEMPT)) {
	};
	starfive_uart_write(ch,SER_THR);
}

static void starfive_uart_puts(const char *s)
{
	while (*s){
		starfive_uart_putc(*s++);
	}
}
static int starfive_uart_getc(void)
{
	/* Wait here until the the FIFO is not full */
	while (!(starfive_uart_read(SER_LSR) & DATA_RDY)) {
	};
	return starfive_uart_read(SER_RBR);
}

static void starfive_uart_setbrg(void)
{
	u64 baud_value;
	/*
	 * BAUD_VALUE = (CLOCK / BAUD_RATE) - 1
	 */
	baud_value = ((SIFIVE_PERIPH_CLK_FREQ / CONFIG_BAUDRATE)>>4);

	starfive_uart_write(((baud_value>>0)&0xFF),SER_DLL);
	starfive_uart_write(((baud_value>>8)&0xFF),SER_DLH);
}


static void ser_clrrxtmo(void)
{
	u32 reg32_val;

	while(1)  {
		reg32_val = starfive_uart_read(SER_IIR);
		if((reg32_val&0xC)!=0xC)
			break;
		reg32_val=starfive_uart_read(SER_RBR);
	}
}

static int starfive_uart_init(void)
{
	u32  datab, stopb, par, mcr;

	u8 databits = 8;
	u8 stopbits = 1;
	u8 parity = 0;
	u8 flow_ctl = 0;

	vic_uart0_reset_clk_gpio_evb_enable;
	vic_uart1_reset_clk_gpio_evb_enable;
	//vic_uart2_reset_clk_gpio_evb_enable;
	//vic_uart3_reset_clk_gpio_evb_enable;

	if(databits >=5 && databits <=8) {
		datab = (databits - 5);
	}
	else {
		return -1;
	}

	if(stopbits == 1) {
		stopb = LCR_STOP_1BIT;
	}
	else if(stopbits == 2) {
		stopb = LCR_STOP_2BIT;
	}
	else {
		return -1;
	}

	par = (parity == 0) ? 0 : (parity == 1) ? LCR_PE : (LCR_PE|LCR_EPS);
	mcr = (flow_ctl == 0) ? 0 : MCR_RTS | MCR_AFCE;

	starfive_uart_write(LCR_DLAB,SER_LCR);
	starfive_uart_setbrg();
	starfive_uart_write(datab|stopb|par,SER_LCR);

	//enable fifo and reset fifo, 1-byte int trig!
	starfive_uart_write((RCVR_TRIG_1C|TXEM_TRIG_EMT|
			     TXFIFO_RST|RXFIFO_RST|FIFO_ENA),
			    SER_FCR);

	starfive_uart_write(mcr,SER_MCR);

	//dis the ser interrupt
	starfive_uart_write(0x00,SER_IER);

	ser_clrrxtmo();
	return 0;
}

static int starfive_uart_tstc(void)
{
	return ((starfive_uart_read(SER_LSR)) & (1 << 0));
}

static struct serial_device starfive_uart_drv = {
	 .name = "starfive_uart",
	 .start = starfive_uart_init,
	 .stop = NULL,
	 .setbrg = starfive_uart_setbrg,
	 .putc = starfive_uart_putc,
	 .puts = starfive_uart_puts,
	 .getc = starfive_uart_getc,
	 .tstc = starfive_uart_tstc,
	};

void starfive_uart_initialize(void)
{
	serial_register(&starfive_uart_drv);
}

struct serial_device *default_serial_console(void)
{
	return &starfive_uart_drv;
}
