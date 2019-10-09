/*
 * Copyright 2000-2009
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <version.h>
#include <linux/compiler.h>
#ifdef CONFIG_SYS_COREBOOT
#include <asm/arch/sysinfo.h>
#endif

#if defined(CONFIG_BOARD_WD_MONARCH) || defined(CONFIG_BOARD_WD_PELICAN)
/**
  4.1.0 New implementation for firmware upate
  4.1.1 Added code to boot into golden image
  4.1.2 KAM-12726 SATA Init failed in uboot
  4.1.3 Reset the bootstate after update_cbr has failed.
  4.1.4 Changed the default FAN speed to 20%
**/
const char __weak version_string[] = "4.1.4";
#else
const char __weak version_string[] = U_BOOT_VERSION_STRING;
#endif

static int do_version(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	printf("\n%s\n", version_string);
#ifdef CC_VERSION_STRING
	puts(CC_VERSION_STRING "\n");
#endif
#ifdef LD_VERSION_STRING
	puts(LD_VERSION_STRING "\n");
#endif
#ifdef CONFIG_SYS_COREBOOT
	printf("coreboot-%s (%s)\n", lib_sysinfo.version, lib_sysinfo.build);
#endif
	return 0;
}

U_BOOT_CMD(
	version,	1,		1,	do_version,
	"print monitor, compiler and linker version",
	""
);
