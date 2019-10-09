/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2015 by Tom Ting <tom_ting@realtek.com>
 *
 * Time initialization.
 */
#ifndef __RTK_CPU_H__
#define __RTK_CPU_H__


#define CPU_RELEASE_ADDR	0x98007f30
#define SB2_CHIP_INFO       0x9801a204
#define BL31_ENTRY_ADDR		0x10120000
#define TEE_MEM_START_ADDR	0x10100000ULL
#define TEE_MEM_SIZE		0x00F00000ULL
#define AFW_MEM_START_ADDR	0x0F900000ULL
#define AFW_MEM_SIZE		0x500000ULL
#define UBOOT_MEM_START_ADDR	0x30000ULL
#define UBOOT_MEM_SIZE			0xE0000ULL
#define BOOT_LOGO_ADDR		0x30000000ULL
#define BOOT_LOGO_SIZE		0x00900000ULL
#define VO_SECURE_ADDR		BOOT_LOGO_ADDR + BOOT_LOGO_SIZE - 0x100000
#define VO_SECURE_SIZE		0x00005a00ULL


#define RTD129x_CHIP_REVISION_A00 0x00000000
#define RTD129x_CHIP_REVISION_A01 0x00010000
#define RTD129x_CHIP_REVISION_B00 0x00020000

#define RTD139x_CHIP_REVISION_A00 0x00000000
#define RTD139x_CHIP_REVISION_A01 0x00010000
#define RTD139x_CHIP_REVISION_B00 0x00020000

#define RTK1355_CPU_ID          0x00000000
#define RTK1395_CPU_ID          0x00000001
#define RTK1355_CPU_MASK        0x00000800
#define EFUSE_ADDR		(0x980171d8)
#define CHIP_INFO1 		(0x98007028)

#ifndef __ASSEMBLY__

#include <asm/io.h>

static inline int get_cpu_id(void) {
	int cpu_id = RTK1395_CPU_ID;
	
	if (((*(unsigned int *)CHIP_INFO1) & RTK1355_CPU_MASK) == RTK1355_CPU_ID) {
            cpu_id = RTK1355_CPU_ID;
    }
	
	return cpu_id;
}

void bootup_slave_cpu(void);
static inline u32 get_rtd129x_cpu_revision(void) {
	u32 val = __raw_readl(SB2_CHIP_INFO);
	return val; 
}
static inline u32 get_rtd139x_cpu_revision(void) {
	u32 val = __raw_readl(SB2_CHIP_INFO);
	return val; 
}

#endif


#endif
