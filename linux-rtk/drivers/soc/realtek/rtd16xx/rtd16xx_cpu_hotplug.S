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

.text
.pushsection .idmap.text, "ax"

ENTRY(__cpu_do_lowpower)
	mov x12, 0
	msr S3_0_C12_C12_7, x12
	isb
	mrs x12, S3_0_C15_C2_7
	orr x12, x12, #0x1 /* send power down request*/
	msr S3_0_C15_C2_7, x12
	isb
	dsb sy
	wfi
	ldr w3, [x0]//get entry address, if cpu do not power gating
	br x3
ENDPROC(__cpu_do_lowpower)

.popsection
