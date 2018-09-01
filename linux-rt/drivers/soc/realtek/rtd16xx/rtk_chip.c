/*
 * Copyright (c) 2018 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#include <soc/realtek/rtk_chip.h>
#include <linux/module.h>
#include <linux/io.h>

#define SB2_BASE_ADDR 0x9801A000
#define CHIP_ID 0x00000200
#define CHIP_REV 0x00000204

#define RTD16xx_CHIP_A00 (0x00000000)
#define RTD16xx_CHIP_A01 (0x00010000)

int get_rtd_chip_id(void) {
	int chip_id = CHIP_ID_RTD1619;
	return chip_id;
}
EXPORT_SYMBOL(get_rtd_chip_id);

int get_rtd_chip_revision(void) {
	int chip_revision = RTD_CHIP_A00;
	void __iomem *chip_revision_addr = ioremap(SB2_BASE_ADDR + CHIP_REV, 0x4);

	int val = readl(chip_revision_addr);

	__iounmap(chip_revision_addr);

	switch (val) {
	case (RTD16xx_CHIP_A00):
		return RTD_CHIP_A00;
	case (RTD16xx_CHIP_A01):
		return RTD_CHIP_A01;
	default:
		printk("%s: Not define chip revision 0x%x\n", __func__, val);
	}
	return chip_revision;
}
EXPORT_SYMBOL(get_rtd_chip_revision);
