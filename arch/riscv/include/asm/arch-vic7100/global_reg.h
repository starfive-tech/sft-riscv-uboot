//
// vic_reg.h
//
// VIC registers Defines
//
// Description:
//
// Revision History:
//        DATE        VERSION  AUTHOR        NOTE
//        ----------  -------  -----------   ------------------------------
//        2019/04/29  0.1      Zavier           Initial
//

#ifndef _GLOBAL_REG_H
#define _GLOBAL_REG_H

// Pheripheral register access
#define REGW(a)             *((volatile UINT32 *)(a))
#define REGH(a)             *((volatile UINT16 *)(a))
#define REGB(a)             *((volatile UINT8 *)(a))


//CADENCE QSPI AHB
#define QSPI_BASE_AHB_ADDR  0x20000000

// OSPI
#define OSPI_BASE_ADDR		0x76000000

// DSP0
#define DSP_0_BASE_ADDR		0xA0000000

// DSP1
#define DSP_1_BASE_ADDR		0xA0100000

// NNE50
#define NNE50_BASE_ADDR		0x10800000

// SDIO0
#define SDIO0_BASE_ADDR     0x10000000

// SDIO1
#define SDIO1_BASE_ADDR     0x10010000


// DMAC
#define DMAC_DMA1P_BASE_ADDR    0x10500000

#define DMAC_DMA2P_BASE_ADDR	0x100b0000


#define SPI2AHB_BASE_ADDR   0x100f0000




// I2S_ADC
#define I2S_ADC_BASE_ADDR       0x10400000

// PDM
#define PDM_BASE_ADDR           0x10410000

// I2S_VAD
#define I2S_VAD_BASE_ADDR       0x10420000

// SPDIF
#define SPDIF_BASE_ADDR         0x10430000

// PWMDAC
#define PWMDAC_BASE_ADDR        0x10440000

// I2S_DAC_0
#define I2S_DAC_0_BASE_ADDR     0x10450000

// I2S_DAC_1
#define I2S_DAC_1_BASE_ADDR     0x10460000

// I2S_DAC16K
#define I2S_DAC16K_BASE_ADDR    0x10470000

// dom_audio_clkgen
#define AUDIO_CLK_GEN_BASE_ADDR        0x10480000

// dom_audio_rstgen
#define AUDIO_RST_GEN_BASE_ADDR        0x10490000

// dom_audio_sysctrl
#define AUDIO_SYS_CTRL_BASE_ADDR       0x104A0000

// USB
#define USB_BASE_ADDR           0x104C0000

// sgdma1p

// nne_csr

// noc_csr

// CLKGEN - csr
#define VIC_CLKGEN_TOP_SV_BASE_ADDR     0x11800000
#define CLKGEN_BASE_ADDR                0x11800000

// OTP
#define OTP_BASE_ADDR                   0x11810000


// ddrphy0_csr
#define DDRPHY0_BASE_ADDR               0x11820000

// ddrphy1_csr
#define DDRPHY1_BASE_ADDR               0x11830000

// RSTGEN
#define RSTGEN_BASE_ADDR                0x11840000

// SYSCON-mainsys
#define SYSCON_SYSMAIN_CTRL_BASE_ADDR   0x11850000

// SYSCON-remap-vp6-noc
#define SYSCON_REMAP_VP6_NOC_BASE_ADDR  0x11854000

// SYSCON-iopad
#define SYSCON_IOPAD_CTRL_BASE_ADDR     0x11858000

// SYSCON-simu-test
#define SYSCON_SIMU_TEST_BASE_ADDR      0x1185C000

// QSPI
#define QSPI_BASE_ADDR		            0x11860000

// HS-UART0
#define UART0_HS_BASE_ADDR              0x11870000

// HS-UART1
#define UART1_HS_BASE_ADDR              0x11880000

#define UART0_BASE_ADDR	UART0_HS_BASE_ADDR
#define UART1_BASE_ADDR	UART1_HS_BASE_ADDR

// UART2
#define UART2_BASE_ADDR                 0x12430000

// UART3
#define UART3_BASE_ADDR                 0x12440000

// VENC
#define VENC_BASE_ADDR                  0x118E0000

// VDEC
#define VDEC_BASE_ADDR                  0x118F0000

//MapConv
#define MAP_CONV_BASE                   0x12210000

//gc300 2D
#define GC300_BASE_ADDR                 0x10100000

// JPEG
#define JPEG_BASE_ADDR                  0x11900000

// GPIO
#define GPIO_BASE_ADDR		            0x11910000
#define EZGPIO_FULLMUX_BASE_ADDR		0x11910000

// DLA

// VP6_APB

// I2C0
#define I2C0_BASE_ADDR          0x118b0000

// I2C1
#define I2C1_BASE_ADDR          0x118c0000

// I2C2
#define I2C2_BASE_ADDR          0x12450000

// I2C3
#define I2C3_BASE_ADDR          0x12460000

// SPI0
#define SPI0_BASE_ADDR          0x11890000

// SPI1
#define SPI1_BASE_ADDR          0x118a0000

// SPI2
#define SPI2_BASE_ADDR          0x12410000

// SPI3
#define SPI3_BASE_ADDR          0x12420000


// INT controller 0
#define VP6_INTC0_BASE_ADDR     0x12400000

// INT controller 1
#define VP6_INTC1_BASE_ADDR     0x124B0000

// sec Engine
#define SEC_BASE_ADDR           0x100D0000

//GMAC
#define GMAC_BASE_ADDR          0x10020000

//NBDLA
#define NBDLA_BASE_ADDR         0x11940000
#define NBDLA_RAM_BASE_ADDR     0x19C00000

// TIMER --WDT
#define TIMER_BASE_ADDR         0x12480000

// pwm -- ptc
#define PWM_BASE_ADDR           0x12490000  //PTC



// INTC
#define INTC_BASE_ADDR          0xA10A0000

//INT CTRL
#define INT_CTRL_BASE_ADDR  0xA10A0000


// SYSCON
#define VIC_SYSCON_BASE_ADDR 0xA1100000///0xA90B0000

// PTC
#define PTC_BASE_ADDR       0xA3020000///0xA9040000

// aon_clkgen
#define AON_CLKGEN_BASE_ADDR	 0xA3060000

// apb_sram
#define APB_SRAM_BASE_ADDR	     0xA3070000

// I2S_1
//#define I2S_1_BASE_ADDR     0xA1000000///0xA8020000

// PCM
///#define PCM_BASE_ADDR       0xA1040000/// 0xA8070000

// EFUSE
///#define EFUSE_BASE_ADDR     0xA1070000///0xA9030000

#define DSITX_BASE_ADDR                 0x12100000
#define CSI2TX_BASE_ADDR                0x12220000
#define ISP_MIPI_CONTROLLER0_BASE_ADDR  0x19800000
#define ISP_MIPI_CONTROLLER1_BASE_ADDR  0x19830000

#define VOUT_SYS_CLKGEN_BASE_ADDR  0x12240000
#define VOUT_SYS_RSTGEN_BASE_ADDR  0x12250000
#define VOUT_SYS_SYSCON_BASE_ADDR  0x12260000

#define ISP_CLKGEN_BASE_ADDR        0x19810000
#define ISP_RSTGEN_BASE_ADDR        0x19820000
#define ISP_SYSCONTROLLER_BASE_ADDR 0x19840000

#define ISP0_AXI_SLV_BASE_ADDR      0x19870000
#define ISP1_AXI_SLV_BASE_ADDR      0x198A0000

//TRNG
#define TRNG_BASE_ADDR      0x118D0000

#define DRAM_MEM2SYS(addr) ((addr) >= 0x80000000 && (addr) <= 0x87FFFFFFF  ?  ((addr) + 0xF80000000)  :  (addr))
#define DRAM_SYS2MEM(addr) ((addr) >= 0x1000000000 && (addr) <= 0x107FFFFFFF  ?  ((addr) - 0xF80000000)  :  (addr))

#endif // _GLOBAL_REG_H

