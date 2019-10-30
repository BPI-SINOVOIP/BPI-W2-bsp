/*
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm-offsets.h>
#include <config.h>
#include <linux/linkage.h>
#include <asm/macro.h>
#include <asm/armv8/mmu.h>
#include <asm/arch/cpu.h>

/*************************************************************************
 *
 * Startup Code (reset vector)
 *
 *************************************************************************/

.globl	_start
_start:
	b	reset

	.align 3

.globl	_TEXT_BASE
_TEXT_BASE:
	.quad	CONFIG_SYS_TEXT_BASE

/*
 * These are defined in the linker script.
 */
.globl	_end_ofs
_end_ofs:
	.quad	_end - _start

.globl	_bss_start_ofs
_bss_start_ofs:
	.quad	__bss_start - _start

.globl	_bss_end_ofs
_bss_end_ofs:
	.quad	__bss_end - _start

reset:
	/*
	 * Could be EL3/EL2/EL1, Initial State:
	 * Little Endian, MMU Disabled, i/dCache Disabled
	 */
	adr	x0, vectors
	switch_el x1, 3f, 2f, 1f
3:	msr	vbar_el3, x0
	mrs	x0, scr_el3
	orr	x0, x0, #0xf			/* SCR_EL3.NS|IRQ|FIQ|EA */
	msr	scr_el3, x0
	msr	cptr_el3, xzr			/* Enable FP/SIMD */
	ldr	x0, =COUNTER_FREQUENCY
	msr	cntfrq_el0, x0			/* Initialize CNTFRQ */
	b	0f
2:	msr	vbar_el2, x0
	mov	x0, #0x33ff
	msr	cptr_el2, x0			/* Enable FP/SIMD */
	b	0f
1:	msr	vbar_el1, x0
	mov	x0, #3 << 20
	msr	cpacr_el1, x0			/* Enable FP/SIMD */
0:

#ifdef CONFIG_TARGET_RTD161x
	/* Disable L3 prefetching
	 * L2WSCTL, [28:27] = 00 & L3WSCTL, [30:29] = 00
	 * L3PCTL,  [12:10] = 100
	 */
	mrs		x0, S3_0_C15_C1_4
	ldr		x1, =0x87FFE3FF
	and		x0, x0, x1
	ldr		x1, =0x1000
	orr		x0, x0, x1
	msr 	S3_0_C15_C1_4, x0
#endif

	/* Apply ARM core specific erratas */
	bl	apply_core_errata

	/*
	 * Cache/BPB/TLB Invalidate
	 * i-cache is invalidated before enabled in icache_enable()
	 * tlb is invalidated before mmu is enabled in dcache_enable()
	 * d-cache is invalidated before enabled in dcache_enable()
	 */

	/* Processor specific initialization */
	/* When bootcode is in el2, not to set gic. */
	switch_el x1, 3f, 2f, 1f
3:	
#ifdef CONFIG_GICV3_REALTEK
	bl	gic_v3_realtek_init
#else
	bl	lowlevel_init
#endif
2:
1:

#ifdef CONFIG_ARMV8_MULTIENTRY
	branch_if_master x0, x1, master_cpu

	/*
	 * Slave CPUs
	 */
slave_cpu:
	bl slave_cpu_spin

master_cpu:
	/* On the master CPU */
#endif /* CONFIG_ARMV8_MULTIENTRY */

	bl	_main

/*-----------------------------------------------------------------------*/

WEAK(apply_core_errata)

	mov	x29, lr			/* Save LR */
	/* For now, we support Cortex-A57 specific errata only */

	/* Check if we are running on a Cortex-A57 core */
	branch_if_a57_core x0, apply_a57_core_errata
0:
	mov	lr, x29			/* Restore LR */
	ret

apply_a57_core_errata:

#ifdef CONFIG_ARM_ERRATA_828024
	mrs	x0, S3_1_c15_c2_0	/* cpuactlr_el1 */
	/* Disable non-allocate hint of w-b-n-a memory type */
	mov	x0, #0x1 << 49
	/* Disable write streaming no L1-allocate threshold */
	mov	x0, #0x3 << 25
	/* Disable write streaming no-allocate threshold */
	mov	x0, #0x3 << 27
	msr	S3_1_c15_c2_0, x0	/* cpuactlr_el1 */
#endif

#ifdef CONFIG_ARM_ERRATA_826974
	mrs	x0, S3_1_c15_c2_0	/* cpuactlr_el1 */
	/* Disable speculative load execution ahead of a DMB */
	mov	x0, #0x1 << 59
	msr	S3_1_c15_c2_0, x0	/* cpuactlr_el1 */
#endif

#ifdef CONFIG_ARM_ERRATA_833069
	mrs	x0, S3_1_c15_c2_0	/* cpuactlr_el1 */
	/* Disable Enable Invalidates of BTB bit */
	and	x0, x0, #0xE
	msr	S3_1_c15_c2_0, x0	/* cpuactlr_el1 */
#endif
	b 0b
ENDPROC(apply_core_errata)

/*-----------------------------------------------------------------------*/

WEAK(lowlevel_init)
	mov	x29, lr			/* Save LR */

#ifndef CONFIG_CORTEX_A55
	mov	x0, #0x1
	lsl	x0, x0, #6
	msr	S3_1_C15_C2_1, x0       /* set up each core CPUECTLR.SMPEN bit for Cache Coherency */
#endif

	/* setup ACTLR_EL3(2).CPUECTLR_EL1 bit*/
	mov	x0, #0x2
	
	mrs     x1, CurrentEL
    lsr     x1, x1, #2
	switch_el x1, 1f, 2f, 3f   /*B00 is at EL2, it does not have privilege to set EL3 */
	
3:	mrs x1, ACTLR_EL3
	orr	x1, x1, x0
	msr	ACTLR_EL3, x1   
	
2:	mrs	x1, ACTLR_EL2
	orr	x1, x1, x0
	msr	ACTLR_EL2, x1

1:  mrs	x1, ACTLR_EL1
	orr	x1, x1, x0
	msr	ACTLR_EL1, x1

#ifndef CONFIG_ARMV8_MULTIENTRY
	/*
	 * For single-entry systems the lowlevel init is very simple.
	 */
	ldr	x0, =GICD_BASE
	bl	gic_init_secure
	ldr	x0, =GICD_BASE
	ldr	x1, =GICC_BASE
	bl	gic_init_secure_percpu

#else /* CONFIG_ARMV8_MULTIENTRY is set */

#if defined(CONFIG_GICV2) || defined(CONFIG_GICV3)
	branch_if_slave x0, 1f
	ldr	x0, =GICD_BASE
	bl	gic_init_secure
1:
#if defined(CONFIG_GICV3)
	ldr	x0, =GICR_BASE
	bl	gic_init_secure_percpu
#elif defined(CONFIG_GICV2)
	ldr	x0, =GICD_BASE
	ldr	x1, =GICC_BASE
	bl	gic_init_secure_percpu
#endif
#endif

	branch_if_master x0, x1, 2f

	/*
	 * Slave should wait for master clearing spin table.
	 * This sync prevent salves observing incorrect
	 * value of spin table and jumping to wrong place.
	 */
#if defined(CONFIG_GICV2) || defined(CONFIG_GICV3)
#ifdef CONFIG_GICV2
	ldr	x0, =GICC_BASE
#endif
	bl	gic_wait_for_interrupt
#endif

	/*
	 * All slaves will enter EL2 and optionally EL1.
	 */

	//A01 Jump to BL31 at EL3
#ifdef CONFIG_TARGET_RTD1295
#if defined(CONFIG_SYS_RTK_SPI_FLASH) || defined(CONFIG_SYS_RTK_SD_FLASH) || defined(CONFIG_SYS_NO_BL31)
	mov w0, #RTD129x_CHIP_REVISION_A00
#else
 	ldr x1, =SB2_CHIP_INFO
 	ldr	w0, [x1]
#endif
 	cmp w0, #RTD129x_CHIP_REVISION_A01
 	bge 2f
#endif /* CONFIG_TARGET_RTD1295 */
	bl	armv8_switch_to_el2

#ifdef CONFIG_ARMV8_SWITCH_TO_EL1
	bl	armv8_switch_to_el1
#endif

#endif /* CONFIG_ARMV8_MULTIENTRY */

2:
	mov	lr, x29			/* Restore LR */
	ret
ENDPROC(lowlevel_init)

WEAK(smp_kick_all_cpus)
	/* Kick secondary cpus up by SGI 0 interrupt */
	mov	x29, lr			/* Save LR */
#if defined(CONFIG_GICV2) || defined(CONFIG_GICV3)
	ldr	x0, =GICD_BASE
	bl	gic_kick_secondary_cpus
#endif
	mov	lr, x29			/* Restore LR */
	ret
ENDPROC(smp_kick_all_cpus)

/*-----------------------------------------------------------------------*/

ENTRY(c_runtime_cpu_setup)
	/* Relocate vBAR */
	adr	x0, vectors
	switch_el x1, 3f, 2f, 1f
3:	msr	vbar_el3, x0
	b	0f
2:	msr	vbar_el2, x0
	b	0f
1:	msr	vbar_el1, x0
0:

	ret
ENDPROC(c_runtime_cpu_setup)

#ifdef CONFIG_GICV3_REALTEK

ENTRY(gic_v3_realtek_init)
	mov	x29, lr			/* Save LR */

	mrs	x0, mpidr_el1
	and x0, x0, 0xffff
	lsr	x1, x0, #0x8
	/* The cpu id in cortex-a55 is at [11:8] */
	mov x0, #0x0
	cmp x1, x0
	bne slave_gic_init
	/* To decide this is the master or slave core */
	
	ldr	x0, =GICD_BASE
	bl rtk_arm_gic_init_percpu_v3
	b end_gic_init

slave_gic_init:
	mov x2, #0x20000
	mul x3, x2, x1
	/* x1 is the cpu id for computing offset */
	/* x3 is the offset of RD and SGI base for each core */
	
	ldr	x0, =GICR_RD_BASE
	add x0, x0, x3
	ldr	x1, =GICR_SGI_BASE
	add x1, x1, x3
	bl rtk_arm_gic_init_slavecpu_v3
	
end_gic_init:

	mov	lr, x29			/* Restore LR */
	ret
ENDPROC(gic_v3_realtek_init)

#endif /* CONFIG_GICV3_REALTEK */