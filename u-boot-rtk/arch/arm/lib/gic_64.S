/*
 * GIC Initialization Routines.
 *
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm-offsets.h>
#include <config.h>
#include <linux/linkage.h>
#include <asm/gic.h>
#include <asm/macro.h>

/*************************************************************************
 *
 * void gic_init_secure(DistributorBase);
 *
 * Initialize secure copy of GIC at EL3.
 *
 *************************************************************************/
ENTRY(gic_init_secure)
	/*
	 * Initialize Distributor
	 * x0: Distributor Base
	 */
#if defined(CONFIG_GICV3)
	mov	w9, #0x37		/* EnableGrp0 | EnableGrp1NS */
					/* EnableGrp1S | ARE_S | ARE_NS */
	str	w9, [x0, GICD_CTLR]	/* Secure GICD_CTLR */
	ldr	w9, [x0, GICD_TYPER]
	and	w10, w9, #0x1f		/* ITLinesNumber */
	cbz	w10, 1f			/* No SPIs */
	add	x11, x0, (GICD_IGROUPRn + 4)
	add	x12, x0, (GICD_IGROUPMODRn + 4)
	mov	w9, #~0
0:	str	w9, [x11], #0x4
	str	wzr, [x12], #0x4	/* Config SPIs as Group1NS */
	sub	w10, w10, #0x1
	cbnz	w10, 0b
#elif defined(CONFIG_GICV2)
	mov	w9, #0x3		/* EnableGrp0 | EnableGrp1 */
	str	w9, [x0, GICD_CTLR]	/* Secure GICD_CTLR */
	ldr	w9, [x0, GICD_TYPER]
	and	w10, w9, #0x1f		/* ITLinesNumber */
	cbz	w10, 1f			/* No SPIs */
	add	w10, w10, #0x1		/* Also add SGI/PPI to the counter */
	add	x11, x0, (GICD_IGROUPRn)
	mov	w9, #~0			/* Config SGI/PPI/SPIs as Grp1 */
0:	str	w9, [x11], #0x4
	sub	w10, w10, #0x1
	cbnz	w10, 0b
#endif
1:
	ret
ENDPROC(gic_init_secure)


/*************************************************************************
 * For Gicv2:
 * void gic_init_secure_percpu(DistributorBase, CpuInterfaceBase);
 * For Gicv3:
 * void gic_init_secure_percpu(ReDistributorBase);
 *
 * Initialize secure copy of GIC at EL3.
 *
 *************************************************************************/
ENTRY(gic_init_secure_percpu)
#if defined(CONFIG_GICV3)
	/*
	 * Initialize ReDistributor
	 * x0: ReDistributor Base
	 */
	mrs	x10, mpidr_el1
	lsr	x9, x10, #32
	bfi	x10, x9, #24, #8	/* w10 is aff3:aff2:aff1:aff0 */
	mov	x9, x0
1:	ldr	x11, [x9, GICR_TYPER]
	lsr	x11, x11, #32		/* w11 is aff3:aff2:aff1:aff0 */
	cmp	w10, w11
	b.eq	2f
	add	x9, x9, #(2 << 16)
	b	1b

	/* x9: ReDistributor Base Address of Current CPU */
2:	mov	w10, #~0x2
	ldr	w11, [x9, GICR_WAKER]
	and	w11, w11, w10		/* Clear ProcessorSleep */
	str	w11, [x9, GICR_WAKER]
	dsb	st
	isb
3:	ldr	w10, [x9, GICR_WAKER]
	tbnz	w10, #2, 3b		/* Wait Children be Alive */

	add	x10, x9, #(1 << 16)	/* SGI_Base */
	mov	w11, #~0
	str	w11, [x10, GICR_IGROUPRn]
	str	wzr, [x10, GICR_IGROUPMODRn]	/* SGIs|PPIs Group1NS */
	mov	w11, #0x1		/* Enable SGI 0 */
	str	w11, [x10, GICR_ISENABLERn]

	/* Initialize Cpu Interface */
	mrs	x10, ICC_SRE_EL3
	orr	x10, x10, #0xf		/* SRE & Disable IRQ/FIQ Bypass & */
					/* Allow EL2 access to ICC_SRE_EL2 */
	msr	ICC_SRE_EL3, x10
	isb

	mrs	x10, ICC_SRE_EL2
	orr	x10, x10, #0xf		/* SRE & Disable IRQ/FIQ Bypass & */
					/* Allow EL1 access to ICC_SRE_EL1 */
	msr	ICC_SRE_EL2, x10
	isb

	mov	x10, #0x3		/* EnableGrp1NS | EnableGrp1S */
	msr	ICC_IGRPEN1_EL3, x10
	isb

	msr	ICC_CTLR_EL3, xzr
	isb

	msr	ICC_CTLR_EL1, xzr	/* NonSecure ICC_CTLR_EL1 */
	isb

	mov	x10, #0x1 << 7		/* Non-Secure access to ICC_PMR_EL1 */
	msr	ICC_PMR_EL1, x10
	isb
#elif defined(CONFIG_GICV2)
	/*
	 * Initialize SGIs and PPIs
	 * x0: Distributor Base
	 * x1: Cpu Interface Base
	 */
	mov	w9, #~0			/* Config SGIs and PPIs as Grp1 */
	str	w9, [x0, GICD_IGROUPRn]	/* GICD_IGROUPR0 */
	mov	w9, #0x1		/* Enable SGI 0 */
	str	w9, [x0, GICD_ISENABLERn]

	/* Initialize Cpu Interface */
	mov	w9, #0x1e7		/* Disable IRQ/FIQ Bypass & */
					/* Enable Ack Group1 Interrupt & */
					/* EnableGrp0 & EnableGrp1 */
	str	w9, [x1, GICC_CTLR]	/* Secure GICC_CTLR */

	mov	w9, #0xf8		/* Non-Secure access to GICC_PMR */
	str	w9, [x1, GICC_PMR]
#endif
	ret
ENDPROC(gic_init_secure_percpu)


/*************************************************************************
 * For Gicv2:
 * void gic_kick_secondary_cpus(DistributorBase);
 * For Gicv3:
 * void gic_kick_secondary_cpus(void);
 *
 *************************************************************************/
ENTRY(gic_kick_secondary_cpus)
#if defined(CONFIG_GICV3)
	mov	x9, #(1 << 40)
	msr	ICC_ASGI1R_EL1, x9
	isb
#elif defined(CONFIG_GICV2)
	mov	w9, #0x8000
	movk	w9, #0x100, lsl #16
	str	w9, [x0, GICD_SGIR]
#endif
	ret
ENDPROC(gic_kick_secondary_cpus)


/*************************************************************************
 * For Gicv2:
 * void gic_wait_for_interrupt(CpuInterfaceBase);
 * For Gicv3:
 * void gic_wait_for_interrupt(void);
 *
 * Wait for SGI 0 from master.
 *
 *************************************************************************/
ENTRY(gic_wait_for_interrupt)
#if defined(CONFIG_GICV3)
	gic_wait_for_interrupt_m x9
#elif defined(CONFIG_GICV2)
	gic_wait_for_interrupt_m x0, w9
#endif
	ret
ENDPROC(gic_wait_for_interrupt)


#ifdef CONFIG_GICV3_REALTEK
/*************************************************************************
 * For Gicv3:
 * void rtk_arm_gic_init_percpu_v3(void);
 *
 *************************************************************************/
ENTRY(rtk_arm_gic_init_percpu_v3)

	/*
	 * Initialize Distributor
	 * x0: Distributor Base
	 */
	 
	/* Disable GICD_CTLR */
	mov	w1, #0x0
	str	w1, [x0]

	/* Set ID0 to non scure (group1) GICD_IGROUPRn  0x084~0x08C */
	ldr	w1, =0xFFFFFFFF
	str	w1, [x0, 0x084]
	str	w1, [x0, 0x088]
	str	w1, [x0, 0x08C]

	/* Enable ICDD_CTLR */
	mov	w1, #0x37
	str	w1, [x0]

	/* Enable redistributor power on */
	ldr	x0, =GICR_RD_BASE
	mov	w1, #0x00
	str	w1, [x0, 0x24]
	
	/* Wait until the power on state is reflected */
1:	
	ldr w1, [x0, 0x24]
	mov x4, #0x8
	
	and x1, x1, x4
	cmp x1, #0x0
	bne 1b

	/* Wake up redistributor: kick ProcessorSleep and wait for ChildrenAsleep to be 0 */
	ldr	w1, [x0, 0x14]
	mov w2, #0xFFFFFFFD
	and	x1, x1, x2
	str	w1, [x0, 0x14]
	dsb	st
	isb

	/* Read the GICR_WAKER */
2:
	ldr	w1, [x0, 0x14]
	mov	x4, #0x4

	/* Read the ChildrenAsleep, bit [2] */
	and	x1, x1, x4
	cmp	x1, #0x0
	bne	2b

	/* Setup redistributor SGI base GICR_IGROUP0 */
	ldr	x0, =GICR_SGI_BASE
	mov w1, #0xFFFFFFFF
	str	w1, [x0, 0x80]

	/* Setup redistributor SGI base GICR_IGRPMOD0 */
	mov w1, #0x0
	str	w1, [x0, 0xD00]

	/* Setup distributor GICR_IGROUP0 */
	ldr	x0, =GICD_BASE
	mov w1, #0xFFFFFFFF
	str	w1, [x0, 0x84]

	/* Setup distributor GICR_IGROUP0 */
	mov w1, #0x0
	str	w1, [x0, 0xD04]

	/* Setup CPU system register ICC_SRE_EL3*/
	mrs	x1, S3_6_C12_C12_5
	mov	x2, #0x9 /* SRE bit0, Enable bit 3 */
	orr x1,x1,x2
	msr	S3_6_C12_C12_5, x1
	isb

	/* Setup CPU system register ICC_CTLR_EL3 */
	mov	x2, #0x0
	msr	S3_6_C12_C12_4, x2
	isb

	ret
ENDPROC(rtk_arm_gic_init_percpu_v3)

/*************************************************************************
 * For Gicv3:
 * void rtk_arm_gic_init_slavecpu_v3(unsigned int GICR_RD_BASE_COREn, unsigned int GICR_SGI_BASE_COREn);
 *
 *************************************************************************/
ENTRY(rtk_arm_gic_init_slavecpu_v3)
	/* x0 Redistributor base, x1 Redistributor sgi base*/
	mov x8, x0
	mov x9, x1
	
	/* Enable redistributor power on */	
	mov	x0, x8 //Set up Redistributor base
	mov	w1, #0x00
	str	w1, [x0, 0x24]
	
	/* Wait until the power on state is reflected */
1:	
	ldr w1, [x0, 0x24]
	mov x4, #0x8
	
	and x1, x1, x4
	cmp x1, #0x0
	bne 1b

	/* Wake up redistributor: kick ProcessorSleep and wait for ChildrenAsleep to be 0 */
	ldr	w1, [x0, 0x14]
	mov w2, #0xFFFFFFFD
	and	x1, x1, x2
	str	w1, [x0, 0x14]
	dsb	st
	isb

	/* Read the GICR_WAKER */
2:
	ldr	w1, [x0, 0x14]
	mov	x4, #0x4

	/* Read the ChildrenAsleep, bit [2] */
	and	x1, x1, x4
	cmp	x1, #0x0
	bne	2b

	/* Setup redistributor SGI base GICR_IGROUP1 */
	mov	x0, x9  //Set up Redistributor SGI base
	mov w1, #0xFFFFFFFF
	str	w1, [x0, 0x80]

	/* Setup redistributor SGI base GICR_IGRPMOD1 */
	mov w1, #0x0
	str	w1, [x0, 0xD00]

	/* Setup CPU system register ICC_SRE_EL3*/
	mrs	x1, S3_6_C12_C12_5
	mov	x2, #0x9 /* SRE bit0, Enable bit 3 */
	orr x1,x1,x2
	msr	S3_6_C12_C12_5, x1
	isb

	/* Setup CPU system register ICC_CTLR_EL3 */
	mov	x2, #0x0
	msr	S3_6_C12_C12_4, x2
	isb

	ret
ENDPROC(rtk_arm_gic_init_slavecpu_v3)

#endif