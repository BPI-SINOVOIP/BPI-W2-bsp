/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Alex Zuepke <azu@sysgo.de>
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
 *
 * (C) Copyright 2004
 * DAVE Srl
 * http://www.dave-tech.it
 * http://www.wawnet.biz
 * mailto:info@wawnet.biz
 *
 * (C) Copyright 2004 Texas Insturments
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/arch/rbus/iso_reg.h>
#include <asm/arch/io.h>

__weak void reset_misc(void)
{
}

int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	puts ("resetting ...\n");

	udelay (50000);				/* wait 50 ms */

	disable_interrupts();
	
#if defined(CONFIG_RTD1195) || defined(CONFIG_RTD1295) || defined(CONFIG_RTD1395)
	
	// trigger watchdog reset
	rtd_outl(ISO_TCWCR_reg,0xa5);
	rtd_outl(ISO_TCWTR_reg,0x1);
	rtd_outl(ISO_TCWOV_reg,1);
	rtd_outl(ISO_TCWCR_reg,0);
		
#endif

	//reset_misc();
	//reset_cpu(0);

	/*NOTREACHED*/
	return 0;
}
