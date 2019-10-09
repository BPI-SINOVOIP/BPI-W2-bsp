/*
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#include <soc/realtek/rtk_chip.h>
#include <linux/module.h>
#include <linux/io.h>

#define SB2_BASE_ADDR   0x9801A000
#define CHIP_ID_ADDR    0x98007028

#define	CHIP_ID		0x00000200
#define CHIP_REV	0x00000204

#define RTK1392_CPU_MASK 0x00001000

#define RTD139x_CHIP_A00 (0x00000000)
#define RTD139x_CHIP_A01 (0x00010000)
#define RTD139x_CHIP_B00 (0x00020000)

int get_rtd_chip_id(void)
{
	int cpu_id;
	void __iomem *id_addr = ioremap(CHIP_ID_ADDR, 0x4);

	cpu_id = CHIP_ID_RTD1395;

	if (readl(id_addr) & RTK1392_CPU_MASK)
		cpu_id = CHIP_ID_RTD1392;

	__iounmap(id_addr);

	return cpu_id;
}
EXPORT_SYMBOL(get_rtd_chip_id);

int get_rtd_chip_revision(void)
{
	int chip_revision = RTD_CHIP_A00;
	void __iomem *chip_revision_addr = ioremap(SB2_BASE_ADDR + CHIP_REV, 0x4);

	int val = readl(chip_revision_addr);

	__iounmap(chip_revision_addr);

	switch (val) {
	case (RTD139x_CHIP_A00):
		return RTD_CHIP_A00;
	case (RTD139x_CHIP_A01):
		return RTD_CHIP_A01;
	case (RTD139x_CHIP_B00):
		return RTD_CHIP_B00;
	default:
		printk("%s: Not define chip revision 0x%x\n", __func__, val);
	}
	return 0;
}
EXPORT_SYMBOL(get_rtd_chip_revision);
