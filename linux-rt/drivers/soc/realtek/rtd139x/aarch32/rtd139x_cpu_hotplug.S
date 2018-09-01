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
#include <asm/cp15.h>
#include <asm/virt.h>

#define SCTLR_ELx_I (1 << 12)
#define SCTLR_ELx_SA (1 << 3)
#define SCTLR_ELx_C (1 << 2)
#define SCTLR_ELx_A (1 << 1)

//#define SCTLR_ELx_FLAGS (SCTLR_ELx_M | SCTLR_ELx_A | SCTLR_ELx_C | SCTLR_ELx_SA | SCTLR_ELx_I)
#define SCTLR_ELx_FLAGS 0x100E

ENTRY(__cpu_do_lowpower)
	/* Clear sctlr flags. */
	mrc	p15, 0, r1, c1, c0, 0
	ldr	r2, =0x100E /* SCTLR_ELx_FLAGS */
	bic	r1, r1, r2
	mcr	p15, 0, r1, c1, c0, 0
	isb
	mrrc	p15, 1, r1, r2, c15
	bic	r1, r1, #0x1 << 6 //Disable CPUECTLR.SMP bit
	mcrr	p15, 1, r1, r2, c15
	isb
	dsb	sy
	wfi
	ldr	r3, [r0]//get entry address, if cpu do not power gating
	mov	pc, r3
ENDPROC(__cpu_do_lowpower)
