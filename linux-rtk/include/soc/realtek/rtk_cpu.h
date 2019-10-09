/*
 * rtk_cpu.h
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#ifndef _RTD129x_CPU_H_INCLUDED_
#define _RTD129x_CPU_H_INCLUDED_

#include <linux/io.h>

#define SB2_BASE_ADDR 0x9801A000
#define CHIP_ID 0x00000200
#define CHIP_REV 0x00000204

#define EFUSE_ADDR 0x980171d8
#define CHIP_INFO1 0x98007028

#define RTK1295_CPU_ID 0x00000000
#define RTK1294_CPU_ID 0x00000001
#define RTK1296_CPU_ID 0x00000002

#define RTK129x_CPU_MASK 0x00000003
#define RTK1296_CPU_MASK 0x00000800

static inline int get_rtd129x_cpu_id(void) {
	int cpu_id = RTK1295_CPU_ID;

	void __iomem *efuse_addr = ioremap(EFUSE_ADDR, 0x4);
	void __iomem *chip_info1_addr = ioremap(CHIP_INFO1, 0x4);

	if ((readl(efuse_addr) & RTK129x_CPU_MASK) == RTK1294_CPU_ID)
		cpu_id = RTK1294_CPU_ID;
	else if (readl(chip_info1_addr) & RTK1296_CPU_MASK)
		cpu_id = RTK1296_CPU_ID;

	__iounmap(efuse_addr);
	__iounmap(chip_info1_addr);
	return cpu_id;
}

#define RTD129x_CHIP_REVISION_A00 (0x00000000)
#define RTD129x_CHIP_REVISION_A01 (0x00010000)
#define RTD129x_CHIP_REVISION_B00 (0x00020000)

static inline int get_rtd129x_cpu_revision(void) {
	void __iomem *chip_revision_addr;
	int val;

	chip_revision_addr = ioremap(SB2_BASE_ADDR + CHIP_REV, 0x4);
	val = readl(chip_revision_addr);
	__iounmap(chip_revision_addr);
	return val;
}

#endif //_RTD129x_CPU_H_INCLUDED_
