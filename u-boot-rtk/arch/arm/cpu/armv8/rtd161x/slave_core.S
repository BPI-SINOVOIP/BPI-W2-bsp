/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2019 by YH Hsieh <yh_hsieh@realtek.com>
 *
 */

#include <asm-offsets.h>
#include <config.h>
#include <linux/linkage.h>
#include <asm/gic.h>
#include <asm/macro.h>
#include <asm/arch/cpu.h>

ENTRY(slave_cpu_spin)
	mov	x29, lr			/* Save LR */

slave_core:
	wfe
	mov	x0, #0
	ldr	x1, =CPU_RELEASE_ADDR
	ldr	w0, [x1]

	mov x3, x0
	lsr x3, x3, #28     /* x3 get wake-up cpu id */

	mrs x2, mpidr_el1
	lsr x2, x2, #8
	and x2, x2, #0xFF   /* x2 store cpu id */

	cmp x2, x3
	bne slave_core

	and x0, x0, #0xFFFFFF /* x0 get real entry address */

JUMP_TO_KERNEL:

#ifdef CONFIG_RTK_ARM32
	mov	x4, x0
	ldr	x5, =ES_TO_AARCH32
	bl	armv8_switch_to_el1_aarch
#endif
	br	x0			/* branch to the given address */

	mov	lr, x29			/* Restore LR */
	ret
ENDPROC(slave_cpu_spin)

