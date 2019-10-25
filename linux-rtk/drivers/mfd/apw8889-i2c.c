/*
 * apw8889-i2c.c - Anpec APW8889 PMIC I2C driver
 *
 * Copyright (C) 2018-2019 Realtek Semiconductor Corporation
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

#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/regmap.h>
#include <linux/mfd/apw888x.h>
#include <linux/mfd/apw8889.h>
#include <soc/realtek/rtk_regmap.h>

/* regmap */
static const struct reg_default apw8889_reg_defaults[] = {
	{ .reg = APW8889_REG_ONOFF,        .def = 0xFD, },
	{ .reg = APW8889_REG_DISCHG,       .def = 0xFD, },
	{ .reg = APW8889_REG_DC1DC2_MODE,  .def = 0x22, },
	{ .reg = APW8889_REG_DC3DC4_MODE,  .def = 0x22, },
	{ .reg = APW8889_REG_DC5DC6_MODE,  .def = 0x22, },
	{ .reg = APW8889_REG_LDO1_MODE,    .def = 0x20, },
	{ .reg = APW8889_REG_DC1_NRMVOLT,  .def = 0x2C, },
	{ .reg = APW8889_REG_DC2_NRMVOLT,  .def = 0x24, },
	{ .reg = APW8889_REG_DC3_NRMVOLT,  .def = 0x24, },
	{ .reg = APW8889_REG_DC4_NRMVOLT,  .def = 0x24, },
	{ .reg = APW8889_REG_DC6_NRMVOLT,  .def = 0x32, },
	{ .reg = APW8889_REG_LDO1_NRMVOLT, .def = 0x12, },
	{ .reg = APW8889_REG_DC1_SLPVOLT,  .def = 0x2C, },
	{ .reg = APW8889_REG_DC2_SLPVOLT,  .def = 0x24, },
	{ .reg = APW8889_REG_DC3_SLPVOLT,  .def = 0x24, },
	{ .reg = APW8889_REG_DC4_SLPVOLT,  .def = 0x24, },
	{ .reg = APW8889_REG_DC6_SLPVOLT,  .def = 0x32, },
	{ .reg = APW8889_REG_LDO1_SLPVOLT, .def = 0x12, },
	{ .reg = APW8889_REG_CLAMP,        .def = 0x00, },
};

static bool apw8889_regmap_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case APW8889_REG_INTR ... APW8889_REG_PWRKEY:
	case APW8889_REG_SYS_CONTROL ... APW8889_REG_LDO1_SLPVOLT:
	case APW8889_REG_CLAMP:
	case APW8889_REG_CHIP_ID:
	case APW8889_REG_VERSION:
		return true;
	}
	return false;
}

static bool apw8889_regmap_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case APW8889_REG_INTR_MASK ... APW8889_REG_PWRKEY:
	case APW8889_REG_SYS_CONTROL ... APW8889_REG_LDO1_SLPVOLT:
	case APW8889_REG_CLAMP:
		return true;
	}
	return false;
}

static bool apw8889_regmap_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case APW8889_REG_INTR_MASK ... APW8889_REG_PWRKEY:
	case APW8889_REG_SYS_CONTROL:
	case APW8889_REG_CLAMP:
	case APW8889_REG_CHIP_ID:
	case APW8889_REG_VERSION:
		return true;
	}
	return false;
}

static const struct regmap_config apw8889_regmap_config = {
	.reg_bits         = 8,
	.val_bits         = 8,
	.max_register     = 0x1F,
	.cache_type       = REGCACHE_FLAT,
	.reg_defaults     = apw8889_reg_defaults,
	.num_reg_defaults = ARRAY_SIZE(apw8889_reg_defaults),
	.readable_reg     = apw8889_regmap_readable_reg,
	.writeable_reg    = apw8889_regmap_writeable_reg,
	.volatile_reg     = apw8889_regmap_volatile_reg,
};

static int apw8889_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct apw888x_device *adev;
	int ret;
	u32 chip_id, rev;

	adev = devm_kzalloc(dev, sizeof(*adev), GFP_KERNEL);
	if (!adev)
		return -ENOMEM;

	adev->regmap = devm_rtk_regmap_init_i2c(client, &apw8889_regmap_config);
	if (IS_ERR(adev->regmap))
		return PTR_ERR(adev->regmap);

	/* show chip info */
	ret = regmap_read(adev->regmap, APW8889_REG_CHIP_ID, &chip_id);
	if (ret) {
		dev_err(dev, "failed to read chip_id: %d\n", ret);
		return ret;
	}
	if (chip_id != 0x5a) {
		dev_err(dev, "chip_id(%02x) not match\n", chip_id);
		return -EINVAL;
	}
	regmap_read(adev->regmap, APW8889_REG_VERSION, &rev);
	dev_info(dev, "apw8889(%02x) rev%d\n", chip_id, rev);

	adev->chip_id = APW888X_DEVICE_ID_APW8889;
	adev->chip_rev = rev;
	adev->dev = dev;
	i2c_set_clientdata(client, adev);

	ret = apw888x_device_init(adev);
	if (ret) {
		dev_err(dev, "failed to add sub-devices: %d\n", ret);
		return ret;
	}
	dev_info(dev, "initialized\n");
	return 0;
}

static int apw8889_i2c_remove(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct apw888x_device *adev = i2c_get_clientdata(client);

	apw888x_device_exit(adev);
	dev_info(dev, "removed\n");
	return 0;
}


static const struct i2c_device_id apw8889_i2c_ids[] = {
	{"apw8889", 0},
	{}
};
MODULE_DEVICE_TABLE(i2c, apw8889_i2c_ids);

struct i2c_driver apw8889_i2c_driver = {
	.driver = {
		.name = "apw8889",
		.owner = THIS_MODULE,
	},
	.id_table = apw8889_i2c_ids,
	.probe    = apw8889_i2c_probe,
	.remove   = apw8889_i2c_remove,
};
EXPORT_SYMBOL_GPL(apw8889_i2c_driver);
module_i2c_driver(apw8889_i2c_driver);

MODULE_DESCRIPTION("Anpec APW8889 PMIC MFD Driver");
MODULE_AUTHOR("Cheng-Yu Lee <cylee12@realtek.com>");
MODULE_LICENSE("GPL");
