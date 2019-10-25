/*
 * GMT-G2237 PMIC MFD driver
 *
 * Copyright (C) 2017-2019 Realtek Semiconductor Corporation
 *
 * Author:
 *	Cheng-Yu Lee <cylee12@realtek.com>
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
 */

#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/mfd/g22xx.h>
#include <linux/mfd/g2237.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <soc/realtek/rtk_regmap.h>

/* regmap */
static const struct reg_default g2237_reg_defaults[] = {
	{ .reg = G2237_REG_ONOFF,        .def = 0xF9, },
	{ .reg = G2237_REG_DISCHG,       .def = 0xF9, },
	{ .reg = G2237_REG_DC1DC2_MODE,  .def = 0x22, },
	{ .reg = G2237_REG_DC3DC4_MODE,  .def = 0x22, },
	{ .reg = G2237_REG_DC5LDO1_MODE, .def = 0x22, },
	{ .reg = G2237_REG_DC1_NRMVOLT,  .def = 0x0B, },
	{ .reg = G2237_REG_DC2_NRMVOLT,  .def = 0x10, },
	{ .reg = G2237_REG_DC3_NRMVOLT,  .def = 0x10, },
	{ .reg = G2237_REG_DC5_NRMVOLT,  .def = 0x0C, },
	{ .reg = G2237_REG_LDO1_NRMVOLT, .def = 0x03, },
	{ .reg = G2237_REG_DC1_SLPVOLT,  .def = 0x0B, },
	{ .reg = G2237_REG_DC2_SLPVOLT,  .def = 0x10, },
	{ .reg = G2237_REG_DC3_SLPVOLT,  .def = 0x10, },
	{ .reg = G2237_REG_DC5_SLPVOLT,  .def = 0x0C, },
	{ .reg = G2237_REG_LDO1_SLPVOLT, .def = 0x03, },
};

static bool g2237_regmap_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case G2237_REG_INTR ... G2237_REG_PWRKEY:
	case G2237_REG_SYS_CONTROL ... G2237_REG_VERSION:
		return true;
	}
	return false;
}

static bool g2237_regmap_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case G2237_REG_INTR_MASK ... G2237_REG_PWRKEY:
	case G2237_REG_SYS_CONTROL ... G2237_REG_LDO1_SLPVOLT:
		return true;
	}
	return false;
}

static bool g2237_regmap_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case G2237_REG_INTR ... G2237_REG_PWRKEY:
	case G2237_REG_SYS_CONTROL:
	case G2237_REG_CHIP_ID:
	case G2237_REG_VERSION:
		return true;
	}
	return false;
}

static const struct regmap_config g2237_regmap_config = {
	.reg_bits         = 8,
	.val_bits         = 8,
	.max_register     = 0x15,
	.cache_type       = REGCACHE_FLAT,
	.reg_defaults     = g2237_reg_defaults,
	.num_reg_defaults = ARRAY_SIZE(g2237_reg_defaults),
	.readable_reg     = g2237_regmap_readable_reg,
	.writeable_reg    = g2237_regmap_writeable_reg,
	.volatile_reg     = g2237_regmap_volatile_reg,
};

static int g2237_i2c_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct g22xx_device *gdev;
	int ret = 0;
	unsigned int chip_id, rev;

	gdev = devm_kzalloc(dev, sizeof(*gdev), GFP_KERNEL);
	if (gdev == NULL)
		return -ENOMEM;

	gdev->regmap = devm_rtk_regmap_init_i2c(client, &g2237_regmap_config);
	if (IS_ERR(gdev->regmap)) {
		ret = PTR_ERR(gdev->regmap);
		dev_err(dev, "failed to allocate regmap: %d\n", ret);
		return ret;
	}

	ret = regmap_read(gdev->regmap, G2237_REG_CHIP_ID, &chip_id);
	if (ret) {
		dev_err(dev, "failed to read chip_id: %d\n", ret);
		return ret;
	}
	if (chip_id != 0x25) {
		dev_err(dev, "invaild chip_id(%02x)\n", chip_id);
		return -EINVAL;
	}
	regmap_read(gdev->regmap, G2237_REG_VERSION, &rev);

	dev_info(dev, "g2237 rev%d\n", rev);
	gdev->chip_id = G22XX_DEVICE_ID_G2237;
	gdev->chip_rev = rev;
	gdev->dev = dev;

	i2c_set_clientdata(client, gdev);
	ret = g22xx_device_init(gdev);
	if (ret) {
		dev_err(dev, "failed to add sub-devices: %d\n", ret);
		return ret;
	}
	dev_info(dev, "initialized\n");
	return ret;
}

static int g2237_i2c_remove(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct g22xx_device *gdev = i2c_get_clientdata(client);

	g22xx_device_exit(gdev);
	dev_info(dev, "removed\n");
	return 0;
}

static const struct i2c_device_id g2237_i2c_id[] = {
	{ "g2237", 0 },
	{}
};
MODULE_DEVICE_TABLE(i2c, g2237_i2c_id);

struct i2c_driver g2237_i2c_driver = {
	.driver = {
		.name = "g2237",
	},
	.probe = g2237_i2c_probe,
	.remove = g2237_i2c_remove,
	.id_table = g2237_i2c_id,
};
EXPORT_SYMBOL_GPL(g2237_i2c_driver);
module_i2c_driver(g2237_i2c_driver);

MODULE_DESCRIPTION("GMT G237 PMIC MFD Driver");
MODULE_AUTHOR("Cheng-Yu Lee <cylee12@realtek.com>");
MODULE_LICENSE("GPL");

