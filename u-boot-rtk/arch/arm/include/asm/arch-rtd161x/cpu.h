/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2018 by YH_HSIEH <yh_hsieh@realtek.com>
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

#define CHIP_NAME       "thor"

/* The dummy register tell bl31 whether aarch64 or aarch32
 * and tell bl31 whether skip tee os
 * Bit[0]: 0 <- for Aarch64, 1 <- for Aarch32
 * Bit[1]: 0 <- no skip tee os, 1 <- skip tee os
 */
#define AARCH_REGISTER 0x9800707C

#define RTD161x_CHIP_REVISION_A00 0x00000000
#define RTD161x_CHIP_REVISION_A01 0x00010000
#define RTD161x_CHIP_REVISION_B00 0x00020000

#define RTK1355_CPU_ID          0x00000000
#define RTK1395_CPU_ID          0x00000001
#define RTK1355_CPU_MASK        0x00000800
#define EFUSE_ADDR		(0x980171d8)
#define CHIP_INFO1 		(0x98007028)

#define RESUME_ADDR_SMC_ID 0x8400fffe

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
static inline u32 get_rtd161x_cpu_revision(void) {
	u32 val = __raw_readl(SB2_CHIP_INFO);
	return val; 
}

#endif


#endif
