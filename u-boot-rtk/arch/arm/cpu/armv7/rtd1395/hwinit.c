/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2015 by Tom Ting <tom_ting@realtek.com>
 *
 */

#include <common.h>
#include <asm/io.h>

/*
 * Print CPU information
 */
int print_cpuinfo(void)
{
	printf("CPU  : Cortex-A53 Quad Core - AARCH32\n");

	return 0;
}

#if !defined(CONFIG_SYS_ICACHE_OFF) || !defined(CONFIG_SYS_DCACHE_OFF)
void enable_caches(void)
{
#ifndef CONFIG_SYS_ICACHE_OFF
        icache_enable();
#endif
#ifndef CONFIG_SYS_DCACHE_OFF
        dcache_enable();
#endif
}
#endif
