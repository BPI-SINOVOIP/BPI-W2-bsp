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
#include <asm/cp15.h>
#include <asm/virt.h>

ENTRY(__cpu_do_lowpower)
	mov r1, #0
	mcr p15, 0, r1, c12, c12, 7
	//msr S3_0_C12_C12_7, r12
	isb
	mrc p15, 0, r1, c15, c2, 7
	//mrs r12, S3_0_C15_C2_7
	orr r1, r1, #0x1 /* send power down request*/
	mcr p15, 0, r1, c15, c2, 7
	//msr S3_0_C15_C2_7, r12
	isb
	dsb sy
	wfi
	ldr r3, [r0] //get entry address, if cpu do not power gating
	mov pc, r3
ENDPROC(__cpu_do_lowpower)

