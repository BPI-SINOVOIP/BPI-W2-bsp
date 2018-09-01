/*
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * Author: Chih-Feng Tai <james.tai@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#include <linux/linkage.h>
#include <asm/assembler.h>
#include <asm/sysreg.h>
#include <asm/virt.h>

#define SCTLR_ELx_I (1 << 12)
#define SCTLR_ELx_SA (1 << 3)
#define SCTLR_ELx_C (1 << 2)
#define SCTLR_ELx_A (1 << 1)

#define SCTLR_ELx_FLAGS (SCTLR_ELx_M | SCTLR_ELx_A | SCTLR_ELx_C | SCTLR_ELx_SA | SCTLR_ELx_I)

.text
.pushsection .idmap.text, "ax"

ENTRY(__cpu_do_lowpower)
	/* Clear sctlr_el1 flags. */
	mrs x12, sctlr_el1
	ldr x13, =SCTLR_ELx_FLAGS
	bic x12, x12, x13
	msr sctlr_el1, x12
	isb
	mrs x12, S3_1_C15_C2_1
	bic x12, x12, #0x1 << 6 //Disable CPUECTLR.SMP bit
	msr S3_1_C15_C2_1, x12
	isb
	dsb sy
	wfi
	ldr w3, [x0]//get entry address, if cpu do not power gating
	br x3
ENDPROC(__cpu_do_lowpower)

.popsection
