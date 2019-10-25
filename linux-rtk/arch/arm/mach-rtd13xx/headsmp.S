#include <linux/linkage.h>
#include <linux/init.h>

#include <asm/assembler.h>

ENTRY(rtd13xx_secondary_startup)
        mrc     p15, 0, r0, c0, c0, 5 @ read MPIDR
        ldr     r8, =0xff00
        and     r0, r0, r8
        adr     r4, 1f
        ldmia   r4, {r5, r6}
        sub     r4, r4, r5
        add     r6, r6, r4
pen:    ldr     r7, [r6]
        cmp     r7, r0
        bne     pen
	b	secondary_startup
ENDPROC(rtd13xx_secondary_startup)

	.align 2
1: 	.long	.
	.long	pen_release
