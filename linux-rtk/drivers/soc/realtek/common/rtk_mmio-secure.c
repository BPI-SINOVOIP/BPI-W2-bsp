/*
 * rtk_mmio-secure.c
 *
 * Copyright (C) 2019 Realtek Semiconductor Corporation
 *
 * Author:
 *      Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <linux/regmap.h>
#include <linux/io.h>
#include <soc/realtek/rtk_regmap.h>

static struct secure_register_desc crt_reg_desc[] = {
#ifdef CONFIG_RTK_MMIO_SECURE_RTD16XX_GENERIC_CRT
	DEFINE_REG_SMCCC_PHYS(0x014, 0x8400ffff, 0x8400fffe),
	DEFINE_REG_SMCCC_PHYS(0x06c, 0x8400ffff, 0x8400fffe),
	DEFINE_REG_SMCCC_PHYS(0x084, 0x8400ffff, 0x8400fffe),
	DEFINE_REG_SMCCC_PHYS(0x088, 0x8400ffff, 0x8400fffe),
#endif
#ifdef CONFIG_RTK_MMIO_SECURE_RTD13XX_GENERIC_CRT
	DEFINE_REG_SMCCC_PHYS(0x014, 0x8400ffff, 0x8400fffe),
	DEFINE_REG_SMCCC_PHYS(0x06c, 0x8400ffff, 0x8400fffe),
	DEFINE_REG_SMCCC_PHYS(0x084, 0x8400ffff, 0x8400fffe),
	DEFINE_REG_SMCCC_PHYS(0x088, 0x8400ffff, 0x8400fffe),
	DEFINE_REG_SMCCC_PHYS(0x094, 0x8400ffff, 0x8400fffe),
	DEFINE_REG_SMCCC_PHYS(0x454, 0x8400ffff, 0x8400fffe),
	DEFINE_REG_SMCCC_PHYS(0x458, 0x8400ffff, 0x8400fffe),
#endif
	DEFINE_REG_INVALID
};

static struct rtk_regmap_config crt_config = {
	.addr = 0x98000000,
	.descs = crt_reg_desc,
	.num_descs = ARRAY_SIZE(crt_reg_desc),
	.config = {
		.reg_bits = 32,
		.val_bits = 32,
		.reg_stride = 4,
	},
};

static struct rtk_regmap_config *configs[] = {
	&crt_config,
	NULL
};

struct rtk_regmap_config *rtk_mmio_match_config_by_addr(unsigned long addr)
{
	struct rtk_regmap_config **p;

	for (p = configs; *p != NULL; p++)
		if ((*p)->addr == addr)
			return *p;
	return NULL;
}

