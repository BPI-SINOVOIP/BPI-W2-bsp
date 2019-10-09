/*
 * rtk_chip.c
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#include <linux/io.h>
#include <soc/realtek/rtk_chip.h>

#define SB2_BASE_ADDR		0x9801A000
#define	CHIP_ID				0x00000200
#define CHIP_REV			0x00000204

#define EFUSE_ADDR			0x980171d8
#define CHIP_INFO1			0x98007028

#define RTK1296_CPU_MASK	0x00000800

int get_rtd_chip_id(void) {
	int cpu_id = CHIP_ID_RTD1295;
	void __iomem *chip_info1_addr = ioremap(CHIP_INFO1, 0x4);

	if (readl(chip_info1_addr) & RTK1296_CPU_MASK) {
		cpu_id = CHIP_ID_RTD1296;
	}
	__iounmap(chip_info1_addr);
	return cpu_id;
}

#define RTD129x_CHIP_A00 (0x00000000)
#define RTD129x_CHIP_A01 (0x00010000)
#define RTD129x_CHIP_B00 (0x00020000)
#define RTD129x_CHIP_B01 (0x00030000)

int get_rtd_chip_revision(void) {
	void __iomem *chip_revision_addr = ioremap(SB2_BASE_ADDR + CHIP_REV, 0x4);

	int val = readl(chip_revision_addr);

	__iounmap(chip_revision_addr);

	switch (val) {
	case (RTD129x_CHIP_A00):
		return RTD_CHIP_A00;
	case (RTD129x_CHIP_A01):
		return RTD_CHIP_A01;
	case (RTD129x_CHIP_B00):
		return RTD_CHIP_B00;
	case (RTD129x_CHIP_B01):
		return RTD_CHIP_B01;
	default:
		printk("%s: Not define chip revision 0x%x\n", __func__, val);
	}
	return 0;
}


