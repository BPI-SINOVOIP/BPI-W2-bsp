/*
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm-offsets.h>
#include <config.h>
#include <asm/ptrace.h>
#include <asm/macro.h>
#include <linux/linkage.h>

#ifdef CONFIG_RTK_XEN_MONITOR_SUPPORT
#define XEN_MON_MAGIC	0xaabbccdd
#endif

/*
 * Enter Exception.
 * This will save the processor state that is ELR/X0~X30
 * to the stack frame.
 */
.macro	exception_entry
	stp	x29, x30, [sp, #-16]!
	stp	x27, x28, [sp, #-16]!
	stp	x25, x26, [sp, #-16]!
	stp	x23, x24, [sp, #-16]!
	stp	x21, x22, [sp, #-16]!
	stp	x19, x20, [sp, #-16]!
	stp	x17, x18, [sp, #-16]!
	stp	x15, x16, [sp, #-16]!
	stp	x13, x14, [sp, #-16]!
	stp	x11, x12, [sp, #-16]!
	stp	x9, x10, [sp, #-16]!
	stp	x7, x8, [sp, #-16]!
	stp	x5, x6, [sp, #-16]!
	stp	x3, x4, [sp, #-16]!
	stp	x1, x2, [sp, #-16]!

	/* Could be running at EL3/EL2/EL1 */
	switch_el x11, 3f, 2f, 1f
3:	mrs	x1, esr_el3
	mrs	x2, elr_el3
	b	0f
2:	mrs	x1, esr_el2
	mrs	x2, elr_el2
	b	0f
1:	mrs	x1, esr_el1
	mrs	x2, elr_el1
0:
	stp	x2, x0, [sp, #-16]!
	mov	x0, sp
.endm

/*
 * Exception vectors.
 */
	.align	11
	.globl	vectors
vectors:
	.align	7
	b	_do_bad_sync	/* Current EL Synchronous Thread */

	.align	7
	b	_do_bad_irq	/* Current EL IRQ Thread */

	.align	7
	b	_do_bad_fiq	/* Current EL FIQ Thread */

	.align	7
	b	_do_bad_error	/* Current EL Error Thread */

	.align	7
	b	_do_sync	/* Current EL Synchronous Handler */

	.align	7
	b	_do_irq		/* Current EL IRQ Handler */

	.align	7
	b	_do_fiq		/* Current EL FIQ Handler */

	.align	7
	b	_do_error	/* Current EL Error Handler */

#ifdef CONFIG_RTK_XEN_MONITOR_SUPPORT
	.align	7
	b	_do_smc_sync	/* Lower EL Synchronous Handler */
#endif

_do_bad_sync:
	exception_entry
	bl	do_bad_sync

_do_bad_irq:
	exception_entry
	bl	do_bad_irq

_do_bad_fiq:
	exception_entry
	bl	do_bad_fiq

_do_bad_error:
	exception_entry
	bl	do_bad_error

_do_sync:
	exception_entry
	bl	do_sync

_do_irq:
	exception_entry
	bl	do_irq

_do_fiq:
	exception_entry
	bl	do_fiq

_do_error:
	exception_entry
	bl	do_error

#ifdef CONFIG_RTK_XEN_MONITOR_SUPPORT
// For XEN monitor initialization, since Xen runs under EL2
// EL3 vector table will need to be set up for 1st time.
// X0:MAGIC, X1:VBAR_XEN, X2:SP_EL3_XEN
_do_smc_sync:
	ldr	x3, =XEN_MON_MAGIC
	cmp	x0, x3
	bne	1f
	mov	sp, x2		// Setup EL3 SP from XEN
	msr	vbar_el3, x1	// Setup XEN MONITOR vector
	mov	x0, #0
	b	2f
1:
	mov	x0, #1
2:
	eret
#endif
