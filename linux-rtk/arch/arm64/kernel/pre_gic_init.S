#include <linux/linkage.h>
#include <linux/init.h>
#include <linux/irqchip/arm-gic-v3.h>

#include <asm/assembler.h>
#include <asm/boot.h>
#include <asm/asm-offsets.h>
#include <asm/cache.h>
#include <asm/cputype.h>
#include <asm/sysreg.h>
#include <asm/virt.h>

#ifdef CONFIG_ARCH_RTD16xx

#define GICD_BASE 0xFF100000
#define GICD_IROUTERn_BASE 0xFF106000
#define CPUID 0
#define GICR_RD_BASE 0xFF140000
#define GICR_SGI_BASE 0xFF150000
#define GICD_IROUTER_VALUE CPUID << 8
#define OFFISE_84 0x84

ENTRY(gicv3_pre_init)
	ldr	x0, =GICD_BASE

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

	/* Wake up redistributor: kick ProcessorSleep and wait for ChildrenAsleep to be 0 */
	ldr	w1, [x0, 0x14]
	mov w2, #0xFFFFFFFD
	and	x1, x1, x2
	str	w1, [x0, 0x14]
	dsb	st
	isb

	/* Read the GICR_WAKER */
1:
	ldr	w1, [x0, 0x14]
	mov	x4, #0x4

	/* Read the ChildrenAsleep, bit [2] */
	and	x1, x1, x4
	cmp	x1, #0x0
	bne	1b

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
	str	w1, [x0, 0x80]

	/* Setup distributor GICR_IGROUP0 */
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
ENDPROC(gicv3_pre_init)
#endif /* CONFIG_ARCH_RTD16xx */

#if defined(CONFIG_ARCH_RTD129x) || defined(CONFIG_ARCH_RTD139x)

#define GICD_BASE 0xFF011000
#define GICC_BASE 0xFF012000

ENTRY(gic_init_secure)
	mov	w9, #0x3		/* EnableGrp0 | EnableGrp1 */
	str	w9, [x0, 0x000]	/* Secure GICD_CTLR */
	ldr	w9, [x0, 0x004]
	and	w10, w9, #0x1f	/* ITLinesNumber */
	cbz	w10, 1f		/* No SPIs */
	add	w10, w10, #0x1	/* Also add SGI/PPI to the counter */
	add	x11, x0, (0x080)
	mov	w9, #~0		/* Config SGI/PPI/SPIs as Grp1 */
0:
	str	w9, [x11], #0x4
	sub	w10, w10, #0x1
	cbnz	w10, 0b
1:
	ret
ENDPROC(gic_init_secure)

ENTRY(gic_init_secure_percpu)
	mov	w9, #~0		/* Config SGIs and PPIs as Grp1 */
	str	w9, [x0, 0x080]	/* GICD_IGROUPR0 */
	mov	w9, #0x1		/* Enable SGI 0 */
	str	w9, [x0, 0x100]
					/* Initialize Cpu Interface */
	mov	w9, #0x1e7		/* Disable IRQ/FIQ Bypass & */
					/* Enable Ack Group1 Interrupt & */
					/* EnableGrp0 & EnableGrp1 */
	str	w9, [x1, 0x000]	/* Secure GICC_CTLR */
	mov	w9, #0xf8		/* Non-Secure access to GICC_PMR */
	str	w9, [x1, 0x004]
	ret
ENDPROC(gic_init_secure_percpu)

ENTRY(gic_pre_init)
	ldr	x0, =GICD_BASE
	bl	gic_init_secure
	ldr	x0, =GICD_BASE
	ldr	x1, =GICC_BASE
	bl	gic_init_secure_percpu
ENDPROC(gic_pre_init)
#endif /* defined(CONFIG_ARCH_RTD129x) || defined(CONFIG_ARCH_RTD139x) */
