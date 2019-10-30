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
	cbz	x0, slave_core

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

