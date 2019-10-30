/*
 *
 * Realtek Low Speed ADC commands
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#include <common.h>
#include <command.h>

#include <asm/arch/lsadc.h>

enum lsadc_cmd {
	LSADC_INIT,
	LSADC_INT_CHK,
	LSADC_SHOW,
};

static int do_lsadc(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int mv = 0;
	int tmp = 0;

	if (argc < 2)
		return CMD_RET_USAGE;

	switch (*argv[1]) {
	case 'i': /* init */
#ifdef CONFIG_RTK_LSADC
		rtk_lsadc_init();
#endif /* CONFIG_RTK_LSADC */
		return 0;

	case 'p': /* pad0_int */
#ifdef CONFIG_RTK_LSADC
		tmp = rtk_lsadc0_pad0_int_chk();
		mv = rtk_lsadc0_pad0_mv_get();
		if (tmp)
			printf("LSADC0 pad0 interrupt occurs, voltage = %d mV\n", mv);
		else
			printf("LSADC0 pad0 status is the same, voltage = %d mV\n", mv);
#endif /* CONFIG_RTK_LSADC */
		return 0;

	case 's': /* show */
#ifdef CONFIG_RTK_LSADC
		mv = rtk_lsadc0_pad0_mv_get();
		printf("LSADC0 pad0 voltage = %d mV\n", mv);
#endif /* CONFIG_RTK_LSADC */
		return 0;
	}
	
	printf("\nunknown cmd [%s %s]\n\n", argv[0], argv[1]);

	return CMD_RET_USAGE;
}

U_BOOT_CMD(lsadc, 2, 0, do_lsadc,
	"Control LSADC0 pad0",
	"\t init                      --- initialize LSADC\n"
	"\t pad0_int                  --- check if LSADC0 pad0 interrupt occurs\n"
	"\t show                      --- show current millivolts of LSADC0 pad0\n"
	);

