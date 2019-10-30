/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2018 by YH_HSIEH <yh_hsieh@realtek.com>
 *
 * Time initialization.
 */
#include <common.h>
#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/bootparam.h>

#ifdef CONFIG_RTK_SLAVE_CPU_BOOT
void bootup_slave_cpu(void)
{
	/* set blue logo info and reserve it */
	set_blue_logo_info();

	printf("Bring UP slave CPUs\n");

	__raw_writel(0x00000000, CPU_RELEASE_ADDR);
	asm volatile ("ISB SY" : : : "memory");
	sync();

	// core 123 jump to FSBL directly
	__raw_writel(0x00003F3F, 0x9801D538);
	asm volatile ("ISB SY" : : : "memory");
	sync();

	// Set each core processor reset
	__raw_writel(__raw_readl(0x9801D100) | 0xFF, 0x9801D100);
	asm volatile ("ISB SY" : : : "memory");
	sync();

	__raw_writel(0x00003233, 0x9801D900);
	asm volatile ("ISB SY" : : : "memory");
	sync();

}
#endif //CONFIG_RTK_SLAVE_CPU_BOOT:
