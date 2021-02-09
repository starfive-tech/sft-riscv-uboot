/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2018 Microsemi Corporation.
 * Padmarao Begari, Microsemi Corporation <padmarao.begari@microsemi.com>
 * Copyright (C) 2018 SiFive Inc
 * Troy Benjegerdes, <troy.benjegerdes@sifive.com>
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <version.h>
#include <linux/sizes.h>

#ifdef CONFIG_SPL

#define CONFIG_SPL_MAX_SIZE		0x00100000
#define CONFIG_SPL_BSS_START_ADDR	0x85000000
#define CONFIG_SPL_BSS_MAX_SIZE		0x00100000
#define CONFIG_SYS_SPL_MALLOC_START	(CONFIG_SPL_BSS_START_ADDR + \
					 CONFIG_SPL_BSS_MAX_SIZE)
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x00100000

#define CONFIG_SPL_STACK	(0x08000000 + 0x001D0000 - \
				 GENERATED_GBL_DATA_SIZE)

#endif


#ifdef CONFIG_OF_CONTROL
#undef CONFIG_OF_SEPARATE
#define CONFIG_OF_EMBED
#endif

#define CONFIG_SYS_CACHELINE_SIZE 64

/*
 * CPU and Board Configuration Options
 */

#define CONFIG_BOOTP_SEND_HOSTNAME
//#define CONFIG_BOOTP_SERVERIP

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_CBSIZE	1024	/* Console I/O Buffer Size */
#define CONFIG_SYS_BOOTM_LEN (32 << 20) /* 32MB */

/*
 * Print Buffer Size
 */
#define CONFIG_SYS_PBSIZE	\
	(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)

/*
 * max number of command args
 */
#define CONFIG_SYS_MAXARGS	16

/*
 * Boot Argument Buffer Size
 */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE

/*
 * Size of malloc() pool
 * 512kB is suggested, (CONFIG_ENV_SIZE + 128 * 1024) was not enough
 */
#define CONFIG_SYS_MALLOC_LEN		SZ_8M

#define CONFIG_SYS_CLK_FREQ			1000000000
//#define CONFIG_SYS_CLK_FREQ			1200000000
//#define CONFIG_SYS_CLK_FREQ			1500000000


#define CONFIG_NR_DRAM_BANKS	1

#define PHYS_SDRAM_0		0x80000000	/* SDRAM Bank #1 */
//#define PHYS_SDRAM_0_SIZE	0x80000000	/* 2 GB */
#define PHYS_SDRAM_0_SIZE	0x200000000	/* 8 GB */


//#define CONFIG_RISCV_SMODE		1
//#undef CONFIG_RISCV_SMODE

//#ifdef CONFIG_RISCV_SMODE
//#define CONFIG_SYS_SDRAM_BASE	(PHYS_SDRAM_0 + 0x200000)
//#else
#define CONFIG_SYS_SDRAM_BASE	(PHYS_SDRAM_0)
//#endif

/*
 * Serial console configuration
 */
#ifndef UART3_BASE_ADDR
#define UART3_BASE_ADDR			0x12440000
#endif

#define SIFIVE_UART_BASE_ADDR 	UART3_BASE_ADDR
#define SIFIVE_PERIPH_CLK_FREQ (100000000UL)

#define CONSOLE_ARG				"console=ttyS0,115200\0"


/* Init Stack Pointer */
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_SDRAM_BASE + SZ_2M)
//(CONFIG_SYS_SDRAM_BASE + 0x600000 - \
//					GENERATED_GBL_DATA_SIZE)

//#define CONFIG_SYS_LOAD_ADDR		0xa0000000
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + SZ_16M)
#define CONFIG_STANDALONE_LOAD_ADDR	0x81000000

#define SIFIVE_BASE_ETHERNET	0x10020000	//GMAC
#define SIFIVE_BASE_GPIO	 	0x10060000

#define SIFIVE_ETHERNET_CLK_FREQ	(CONFIG_SYS_CLK_FREQ / 2)

#define SIFIVE_BASE_SPI			0xA3100000
#define CONFIG_SYS_SPI_BASE			SIFIVE_BASE_SPI
#define CONFIG_SYS_SPI_CLK			(CONFIG_SYS_CLK_FREQ / 2)
#define CONFIG_ENV_SPI_MAX_HZ		25000000

#define CONFIG_BOOTFILE			"vmlinuz"


/*
 * Ethernet
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_DW_ALTDESCRIPTOR
#define CONFIG_PHY_ADDR		0
#define CONFIG_ARP_TIMEOUT	0x5000
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		192.168.120.200
#define CONFIG_IP_DEFRAG
#ifndef CONFIG_NET_MAXDEFRAG
#define CONFIG_NET_MAXDEFRAG 16384
#endif
#endif

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/* HACK these should have '#if defined (stuff) around them like zynqp*/
#define BOOT_TARGET_DEVICES(func) func(DHCP, dhcp, na) \
				func(MMC, mmc, 0)

#include <config_distro_bootcmd.h>

#if 0
#define SIFIVE_BASE_CLINT		0x02000000
#define SIFIVE_BASE_MTIME		0x0200bff8
#define SIFIVE_BASE_TIMECMP		0x02004000

#define SIFIVE_BASE_PRCI		0x10000000
#define SIFIVE_BASE_MAC_MGMT	0x100a0000

/* DT blob (fdt) address */
#define SIFIVE_FDT_BASE		0x86000000
#define KERNEL_LOAD_BASE		0x80700000

#define	CONFIG_EXTRA_ENV_SETTINGS	\
		"ip_dyn=yes\0" \
		"uboot_version=" __stringify(PLAIN_VERSION) "\0" \
		"mmcsetup=mmc part\0" \
		"fdt_high=0xffffffffffffffff\0" \
		"fdtsetup=fdt addr ${fdtcontroladdr}\0" \
		"fatenv=setenv fileaddr a0000000; fatload mmc 0:1 ${fileaddr} u74_uEnv.txt;" \
			"env import -t ${fileaddr} ${filesize}\0"		\
		BOOTENV
#endif

#include <environment/distro/sf.h>

#define TYPE_GUID_LOADER1	"5B193300-FC78-40CD-8002-E86C45580B47"
#define TYPE_GUID_LOADER2	"2E54B353-1271-4842-806F-E436D6AF6985"
#define TYPE_GUID_SYSTEM	"0FC63DAF-8483-4772-8E79-3D69D8477DE4"

#define PARTS_DEFAULT \
	"name=loader1,start=17K,size=1M,type=${type_guid_gpt_loader1};" \
	"name=loader2,size=4MB,type=${type_guid_gpt_loader2};" \
	"name=system,size=-,bootable,type=${type_guid_gpt_system};"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"fdt_high=0xffffffffffffffff\0" \
	"initrd_high=0xffffffffffffffff\0" \
	"kernel_addr_r=0x84000000\0" \
	"fdt_addr_r=0x88000000\0" \
	"scriptaddr=0x88100000\0" \
	"script_offset_f=0x1fff000\0" \
	"script_size_f=0x1000\0" \
	"pxefile_addr_r=0x88200000\0" \
	"ramdisk_addr_r=0x88300000\0" \
	"type_guid_gpt_loader1=" TYPE_GUID_LOADER1 "\0" \
	"type_guid_gpt_loader2=" TYPE_GUID_LOADER2 "\0" \
	"type_guid_gpt_system=" TYPE_GUID_SYSTEM "\0" \
	"partitions=" PARTS_DEFAULT "\0" \
	BOOTENV \
	BOOTENV_SF

#define CONFIG_PREBOOT \
	"setenv fdt_addr ${fdtcontroladdr};" \
	"fdt addr ${fdtcontroladdr};"


#define CONFIG_SYS_MAX_FLASH_SECT	0
#define CONFIG_SYS_MAX_FLASH_BANKS 0
/*
 * memtest works on 1.9 MB in DRAM
 */
#define CONFIG_SYS_MEMTEST_START	PHYS_SDRAM_0
#define CONFIG_SYS_MEMTEST_END		(PHYS_SDRAM_0 + PHYS_SDRAM_0_SIZE)

#define CONFIG_SYS_BAUDRATE_TABLE {9600,19200,38400,57600,115200,230400,460800,921600}
#define CONFIG_SYS_LOADS_BAUD_CHANGE 1		/* allow baudrate change */

/* 6.25MHz RTC clock, SiFive FU740 Manual ?? */
#define CONFIG_SYS_HZ_CLOCK	6250000


/*
+ * QSPI support
+ */
#ifdef CONFIG_OF_CONTROL		/* QSPI is controlled via DT */
#define CONFIG_CQSPI_REF_CLK		(250000000)
#endif
#define __io

#endif /* __CONFIG_H */
