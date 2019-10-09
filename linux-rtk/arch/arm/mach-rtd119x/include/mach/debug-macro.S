/*
 * arch/arm/mach-rtk119x/include/mach/debug-macro.S
 *
 * Debugging macro include header
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#define RBUS_PHYS_BASE			0x18000000
#define RBUS_VIRT_BASE			IOMEM(0xfe000000)

	.macro  addruart, rp, rv, tmp
	ldr	\rp, =RBUS_PHYS_BASE
	ldr	\rv, =RBUS_VIRT_BASE
	orr	\rp, \rp, #0x00007800
	orr	\rv, \rv, #0x00007800
	.endm

#define UART_SHIFT	2
#include <asm/hardware/debug-8250.S>
