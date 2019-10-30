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

	//A01 Jump to BL31 at EL3
#if defined(CONFIG_SYS_RTK_SPI_FLASH) || defined(CONFIG_SYS_RTK_SD_FLASH) || defined(CONFIG_SYS_NO_BL31)
	mov w2, #RTD129x_CHIP_REVISION_A00
#else
 	ldr x1, =SB2_CHIP_INFO
 	ldr	w2, [x1]
#endif
 	cmp w2, #RTD129x_CHIP_REVISION_A01
 	bne JUMP_TO_KERNEL   /*Just A01 need to go BL31*/
JUMP_TO_BL31:
    ldr x30, =BL31_ENTRY_ADDR
	ret

JUMP_TO_KERNEL:
	br	x0			/* branch to the given address */

	mov	lr, x29			/* Restore LR */
	ret
ENDPROC(slave_cpu_spin)

