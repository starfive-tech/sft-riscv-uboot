/**
  ******************************************************************************
  * @file  starfive_vic_dw_mmc.c
  * @author  StarFive Technology
  * @version  V1.0
  * @date  07/29/2020
  * @brief
  ******************************************************************************
  * @copy
  *
  * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STARFIVE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * COPYRIGHT 20120 Shanghai StarFive Technology Co., Ltd.
  */


#include <common.h>
#include <dwmmc.h>
#include <malloc.h>
#include <linux/printk.h>
#include <linux/errno.h>

#define	DWMMC_BUS_FREQ		100000000
#define	DWMMC_MAX_FREQ		10000000
#define	DWMMC_MIN_FREQ		400000

/*
 * This function adds the mmc channel to be registered with mmc core.
 * index -	mmc channel number.
 * regbase -	register base address of mmc channel specified in 'index'.
 * bus_width -	operating bus width of mmc channel specified in 'index'.
 */
int starfive_mmc_add_port(int index, u32 regbase, int bus_width)
{
	struct dwmci_host *host = NULL;
	u32 fifo_depth = 32;

	host = calloc(1, sizeof(struct dwmci_host));
	if (!host) {
		pr_err("dwmci_host calloc failed!\n");
		return -ENOMEM;
	}

	host->name = "VIC DWMMC0";
	host->ioaddr = (void *)(ulong)regbase;
	host->buswidth = bus_width;
	host->dev_index = index;
	host->bus_hz = DWMMC_BUS_FREQ;

	host->fifoth_val = MSIZE(0x2) |
	RX_WMARK(fifo_depth / 2 - 1) | TX_WMARK(fifo_depth / 2);

	/* Add the mmc channel to be registered with mmc core */
	if (add_dwmci(host, DWMMC_MAX_FREQ, DWMMC_MIN_FREQ)) {
		printf("DWMMC%d registration failed\n", index);
		return -1;
	}
	return 0;
}
