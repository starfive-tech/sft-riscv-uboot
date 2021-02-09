// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2017 Andes Technology Corporation
 * Rick Chen, Andes Technology Corporation <rick@andestech.com>
 */

#include <common.h>
#include <command.h>

unsigned long do_go_exec(ulong (*entry)(int, char * const []),
			 int argc, char *const argv[])
{
	cleanup_before_linux();

#if CONFIG_IS_ENABLED(STARFIVE_VIC7100_BOOTHACK)
  ulong addr;
  printf ("DEBUG: do_go_exec entry:%lx fdt:%lx\n",(ulong)entry,(ulong)(argv[1]));
  addr = simple_strtoul(argv[1], NULL, 16);
  printf ("fdt:%lx\n",addr);

  asm volatile ("mv a1, %1\n\t"
			"csrr a0, mhartid\n\t"
			"mv t4, %0\n\t"
			"jr t4\n\t"::"r" (entry),"r"(addr));
#endif

	return entry(argc, argv);
}
