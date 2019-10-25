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

#define OTP_ADDR 0x980174f4
#define OTP_CHIP_MASK 0x000F0000
#define RTD1319 0x00000000
#define RTD1317 0x00010000
#define RTD1315 0x00020000

#define RTD13xx_CHIP_A00 (0x00000000)

int get_rtd_chip_id(void) {
	int chip_id = CHIP_ID_RTD1319;
	void __iomem *chip_id_addr;
	int val;

	chip_id_addr = ioremap(OTP_ADDR, 0x4);
	val = readl(chip_id_addr);
	__iounmap(chip_id_addr);

	switch (val & OTP_CHIP_MASK) {
	case (RTD1319):
		chip_id = CHIP_ID_RTD1319;
		break;
	case (RTD1317):
		chip_id = CHIP_ID_RTD1317;
		break;
	case (RTD1315):
		chip_id = CHIP_ID_RTD1315;
		break;
	default:
		printk("%s: Not define chip id 0x%x\n", __func__, val);
	}

	return chip_id;
}
EXPORT_SYMBOL(get_rtd_chip_id);

int get_rtd_chip_revision(void) {
	int chip_revision = RTD_CHIP_A00;
	void __iomem *chip_revision_addr = ioremap(SB2_BASE_ADDR + CHIP_REV, 0x4);

	int val = readl(chip_revision_addr);

	__iounmap(chip_revision_addr);

	switch (val) {
	case (RTD13xx_CHIP_A00):
		return RTD_CHIP_A00;
	default:
		printk("%s: Not define chip revision 0x%x\n", __func__, val);
	}
	return chip_revision;
}
EXPORT_SYMBOL(get_rtd_chip_revision);
