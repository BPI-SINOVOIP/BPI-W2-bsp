/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2018 by YH_HSIEH <yh_hsieh@realtek.com>
 *
 */

#include <common.h>
#include <asm/io.h>

/*
 * Print CPU information
 */
int print_cpuinfo(void)
{
	printf("CPU  : Cortex-A55 Quad Core - AARCH64\n");

	return 0;
}
