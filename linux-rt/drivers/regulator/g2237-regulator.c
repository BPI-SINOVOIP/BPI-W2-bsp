 /*
 * g2237-regulator.c - GMT-G2237 Regulator driver
 *
 * Copyright (C) 2017-2018 Realtek Semiconductor Corporation
 * Copyright (C) 2017-2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#define pr_fmt(fmt) "g2237: " fmt

#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regmap.h>
#include <linux/suspend.h>
#include <soc/realtek/rtk_regmap.h>
#include <dt-bindings/regulator/gmt,g2237.h>
#include "g22xx-regulator.h"

/* regulator id */
enum {
	G2237_ID_DC1 = 0,
	G2237_ID_DC2,
	G2237_ID_DC3,
	G2237_ID_DC4,
	G2237_ID_DC5,
	G2237_ID_LDO1,
	G2237_ID_MAX
};

/* reg_field id */
enum {
	G2237_REG_FIELD_LPOFF_TO_DO = 0,
	G2237_REG_FIELD_SOFTOFF,
	G2237_REG_FIELD_DC4_ON,
	G2237_REG_FIELD_DC4_NMODE,
	G2237_REG_FIELD_DC4_SMODE,

	G2237_REG_FIELD_DC1_ON,
	G2237_REG_FIELD_DC1_NMODE,
	G2237_REG_FIELD_DC1_SMODE,
	G2237_REG_FIELD_DC1_NVO,
	G2237_REG_FIELD_DC1_SVO,

	G2237_REG_FIELD_DC2_ON,
	G2237_REG_FIELD_DC2_NMODE,
	G2237_REG_FIELD_DC2_SMODE,
	G2237_REG_FIELD_DC2_NVO,
	G2237_REG_FIELD_DC2_SVO,

	G2237_REG_FIELD_DC3_ON,
	G2237_REG_FIELD_DC3_NMODE,
	G2237_REG_FIELD_DC3_SMODE,
	G2237_REG_FIELD_DC3_NVO,
	G2237_REG_FIELD_DC3_SVO,

	G2237_REG_FIELD_DC5_ON,
	G2237_REG_FIELD_DC5_NMODE,
	G2237_REG_FIELD_DC5_SMODE,
	G2237_REG_FIELD_DC5_NVO,
	G2237_REG_FIELD_DC5_SVO,

	G2237_REG_FIELD_LDO1_ON,
	G2237_REG_FIELD_LDO1_NMODE,
	G2237_REG_FIELD_LDO1_SMODE,
	G2237_REG_FIELD_LDO1_NVO,
	G2237_REG_FIELD_LDO1_SVO,

	G2237_REG_FIELD_MAX
};

/* regmap_field & reg_field */
static const struct reg_field regs[G2237_REG_FIELD_MAX] __initconst = {
	[G2237_REG_FIELD_LPOFF_TO_DO] = REG_FIELD(0x02, 7, 7),
	[G2237_REG_FIELD_SOFTOFF]     = REG_FIELD(0x04, 7, 7),
	[G2237_REG_FIELD_DC1_ON]      = REG_FIELD(0x05, 7, 7),
	[G2237_REG_FIELD_DC2_ON]      = REG_FIELD(0x05, 6, 6),
	[G2237_REG_FIELD_DC3_ON]      = REG_FIELD(0x05, 5, 5),
	[G2237_REG_FIELD_DC4_ON]      = REG_FIELD(0x05, 4, 4),
	[G2237_REG_FIELD_DC5_ON]      = REG_FIELD(0x05, 3, 3),
	[G2237_REG_FIELD_LDO1_ON]     = REG_FIELD(0x05, 0, 0),
	[G2237_REG_FIELD_DC1_NMODE]   = REG_FIELD(0x07, 6, 7),
	[G2237_REG_FIELD_DC1_SMODE]   = REG_FIELD(0x07, 4, 5),
	[G2237_REG_FIELD_DC2_NMODE]   = REG_FIELD(0x07, 2, 3),
	[G2237_REG_FIELD_DC2_SMODE]   = REG_FIELD(0x07, 0, 1),
	[G2237_REG_FIELD_DC3_NMODE]   = REG_FIELD(0x08, 6, 7),
	[G2237_REG_FIELD_DC3_SMODE]   = REG_FIELD(0x08, 4, 5),
	[G2237_REG_FIELD_DC4_NMODE]   = REG_FIELD(0x08, 2, 3),
	[G2237_REG_FIELD_DC4_SMODE]   = REG_FIELD(0x08, 0, 1),
	[G2237_REG_FIELD_DC5_NMODE]   = REG_FIELD(0x09, 6, 7),
	[G2237_REG_FIELD_DC5_SMODE]   = REG_FIELD(0x09, 4, 5),
	[G2237_REG_FIELD_LDO1_NMODE]  = REG_FIELD(0x09, 2, 3),
	[G2237_REG_FIELD_LDO1_SMODE]  = REG_FIELD(0x09, 0, 1),
	[G2237_REG_FIELD_DC1_NVO]     = REG_FIELD(0x0A, 0, 3),
	[G2237_REG_FIELD_DC2_NVO]     = REG_FIELD(0x0B, 0, 4),
	[G2237_REG_FIELD_DC3_NVO]     = REG_FIELD(0x0C, 0, 4),
	[G2237_REG_FIELD_DC5_NVO]     = REG_FIELD(0x0D, 0, 3),
	[G2237_REG_FIELD_LDO1_NVO]    = REG_FIELD(0x0E, 0, 3),
	[G2237_REG_FIELD_DC1_SVO]     = REG_FIELD(0x0F, 0, 3),
	[G2237_REG_FIELD_DC2_SVO]     = REG_FIELD(0x10, 0, 4),
	[G2237_REG_FIELD_DC3_SVO]     = REG_FIELD(0x11, 0, 4),
	[G2237_REG_FIELD_DC5_SVO]     = REG_FIELD(0x12, 0, 3),
	[G2237_REG_FIELD_LDO1_SVO]    = REG_FIELD(0x13, 0, 3),
};

/* desc initdata */
static struct g22xx_desc_initdata initdata[G2237_ID_MAX] = {
	[G2237_ID_DC1]  = G22XX_DESC_INITDATA(G2237, DC1, regs),
	[G2237_ID_DC2]  = G22XX_DESC_INITDATA(G2237, DC2, regs),
	[G2237_ID_DC3]  = G22XX_DESC_INITDATA(G2237, DC3, regs),
	[G2237_ID_DC4]  = G22XX_DESC_INITDATA_NO_VO(G2237, DC4, regs),
	[G2237_ID_DC5]  = G22XX_DESC_INITDATA(G2237, DC5, regs),
	[G2237_ID_LDO1] = G22XX_DESC_INITDATA(G2237, LDO1, regs),
};

/* voltage table */
static const unsigned int dc1_vtbl[] = {
	2200000, 2300000, 2400000, 2500000,
	2600000, 2700000, 2800000, 2900000,
	3000000, 3100000, 3200000, 3300000,
	3400000, 3500000, 3600000, 3700000,
};

static const unsigned int dcx_vtbl[] = {
	 800000,  812500,  825000,  837500,
	 850000,  862500,  875000,  887500,
	 900000,  912500,  925000,  937500,
	 950000,  962500,  975000,  987500,
	1000000, 1012500, 1025000, 1037500,
	1050000, 1062500, 1075000, 1087500,
	1100000, 1112500, 1125000, 1137500,
	1150000, 1162500, 1175000, 1187500,
};

static const unsigned int dc4_vtbl[] = {
	1800000,
};

static const unsigned int dc5_vtbl[] = {
	 800000,  850000,  900000,  950000,
	1000000, 1050000, 1100000, 1200000,
	1300000, 1500000, 1600000, 1700000,
	1800000, 1900000, 2000000, 2500000,
};

static const unsigned int ldo1_vtbl[] = {
	2200000, 2300000, 2400000, 2500000,
	2600000, 2700000, 2800000, 2900000,
	3000000, 3000000, 3000000, 3000000,
	3000000, 3000000, 3000000, 3000000,
};

/* mode mapping callback */
static unsigned int g2237_regulator_dc_of_map_mode(unsigned int mode)
{
	if (mode == G2237_DC_MODE_FORCE_PWM)
		return REGULATOR_MODE_FAST;
	return REGULATOR_MODE_NORMAL;
}

static unsigned int g2237_regulator_ldo_of_map_mode(unsigned int mode)
{
	if (mode == G2237_LDO_MODE_ECO)
		return REGULATOR_MODE_IDLE;
	return REGULATOR_MODE_NORMAL;
}

/* regulator_desc */
static struct g22xx_desc desc[G2237_ID_MAX] = {
	[G2237_ID_DC1] = {
		.desc = G22XX_DESC(G2237_ID_DC1, "dc1", dc1_vtbl),
		.desc.of_map_mode = g2237_regulator_dc_of_map_mode,
	},
	[G2237_ID_DC2] = {
		.desc = G22XX_DESC(G2237_ID_DC2, "dc2", dcx_vtbl),
		.desc.of_map_mode = g2237_regulator_dc_of_map_mode,
		.delay_volt_up = 40,
	},
	[G2237_ID_DC3] = {
		.desc = G22XX_DESC(G2237_ID_DC2, "dc3", dcx_vtbl),
		.desc.of_map_mode = g2237_regulator_dc_of_map_mode,
	},
	[G2237_ID_DC4] = {
		.desc = G22XX_DESC(G2237_ID_DC2, "dc4", dc4_vtbl),
		.desc.of_map_mode = g2237_regulator_dc_of_map_mode,
	},
	[G2237_ID_DC5] = {
		.desc = G22XX_DESC(G2237_ID_DC2, "dc5", dc5_vtbl),
		.desc.of_map_mode = g2237_regulator_dc_of_map_mode,
	},
	[G2237_ID_LDO1] = {
		.desc = G22XX_DESC(G2237_ID_DC2, "ldo1", ldo1_vtbl),
		.desc.of_map_mode = g2237_regulator_ldo_of_map_mode,
		.flags = G22XX_FLAG_TYPE_LDO,
	},
};

/* regmap */
static const struct reg_default g2237_reg_defaults[] = {
	{ .reg = 0x02, .def = 0xC7, },
	{ .reg = 0x04, .def = 0x00, },
	/* on/off */
	{ .reg = 0x05, .def = 0xF9, },
	/* mode */
	{ .reg = 0x07, .def = 0x22, },
	{ .reg = 0x08, .def = 0x22, },
	{ .reg = 0x09, .def = 0x22, },
	/* nrm volt */
	{ .reg = 0x0A, .def = 0x0B, },
	{ .reg = 0x0B, .def = 0x10, },
	{ .reg = 0x0C, .def = 0x10, },
	{ .reg = 0x0D, .def = 0x0C, },
	{ .reg = 0x0E, .def = 0x03, },
	/* slp volt */
	{ .reg = 0x0F, .def = 0x0B, },
	{ .reg = 0x10, .def = 0x10, },
	{ .reg = 0x11, .def = 0x10, },
	{ .reg = 0x12, .def = 0x0C, },
	{ .reg = 0x13, .def = 0x03, },
};

static bool g2237_regmap_writeable_reg(struct device *dev, unsigned int reg)
{
	return reg != 0;
}

static bool g2237_regmap_precious_reg(struct device *dev, unsigned int reg)
{
	return reg == 0;
}

static const struct regmap_config g2237_regmap_config_no_cache = {
	.reg_bits         = 8,
	.val_bits         = 8,
	.max_register     = 0x15,
	.writeable_reg    = g2237_regmap_writeable_reg,
	.precious_reg     = g2237_regmap_precious_reg,
};

static const struct regmap_config g2237_regmap_config = {
	.reg_bits         = 8,
	.val_bits         = 8,
	.max_register     = 0x15,
	.cache_type       = REGCACHE_FLAT,
	.reg_defaults     = g2237_reg_defaults,
	.num_reg_defaults = ARRAY_SIZE(g2237_reg_defaults),
	.writeable_reg    = g2237_regmap_writeable_reg,
	.precious_reg     = g2237_regmap_precious_reg,
};

/* pm */
static int g2237_regulator_suspend(struct device *dev)
{
	int i;

#ifdef CONFIG_SUSPEND
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY)
		goto done;
#endif

	dev_info(dev, "Enter %s\n", __func__);
	for (i = 0; i < ARRAY_SIZE(desc); i++)
		g22xx_prepare_suspend_state(desc[i].rdev, 0);
	regulator_suspend_prepare(PM_SUSPEND_MEM);
done:
	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static const struct dev_pm_ops g2237_regulator_pm_ops = {
	.suspend = g2237_regulator_suspend,
};

static int g2237_regulator_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct g22xx_device *gdev;
	struct regmap *regmap;
	const struct regmap_config *cfg;
	int i, ret;

	dev_info(dev, "%s\n", __func__);

	gdev = devm_kzalloc(dev, sizeof(*gdev), GFP_KERNEL);
	if (!gdev)
		return -ENOMEM;
	gdev->maps = devm_kcalloc(dev, G2237_REG_FIELD_MAX,
		sizeof(*gdev->maps), GFP_KERNEL);
	if (!gdev->maps)
		return -ENOMEM;

	/* bootargs: disable regcache */
	if (g22xx_regcache_disabled()) {
		dev_info(dev, "no regcache\n");
		cfg = &g2237_regmap_config_no_cache;
	} else
		cfg = &g2237_regmap_config;

	regmap = devm_rtk_regmap_i2c_init(dev, client, cfg);
	if (IS_ERR(regmap))
		return -EINVAL;

	/* convert all reg_field to regmap_field */
	for (i = 0; i < G2237_REG_FIELD_MAX; i++) {
		struct regmap_field *rf;

		rf = devm_regmap_field_alloc(dev, regmap, regs[i]);
		if (IS_ERR(rf)) {
			ret = PTR_ERR(rf);
			dev_err(dev, "Failed to alloc regmap field %d: %d\n",
				i, ret);
			return ret;
		}
		gdev->maps[i] = rf;
	}

	gdev->regmap = regmap;
	gdev->client = client;
	gdev->dev    = dev;

	for (i = 0; i < ARRAY_SIZE(desc); i++) {
		ret = g22xx_regulator_register(gdev, &desc[i], &initdata[i]);
		if (ret) {
			dev_err(dev, "Failed to register %s: %d\n",
				g22xx_desc_name(&desc[i]), ret);
			return ret;
		}
	}

	i2c_set_clientdata(client, gdev);

	/* setup pm_power_off */
	ret = g22xx_setup_pm_power_off(dev,
		gdev->maps[G2237_REG_FIELD_SOFTOFF]);
	if (ret == 1)
		dev_info(dev, "system-power-controller\n");
	else if (ret < 0)
		dev_err(dev, "g22xx_setup_pm_power_off() returns %d\n", ret);

	return 0;
}

static void g2237_regulator_shutdown(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	int i;

	dev_info(dev, "Enter %s\n", __func__);
	for (i = 0; i < ARRAY_SIZE(desc); i++)
		g22xx_prepare_suspend_state(desc[i].rdev, 1);
	regulator_suspend_prepare(PM_SUSPEND_MEM);
	dev_info(dev, "Exit %s\n", __func__);
}

static const struct i2c_device_id g2237_regulator_ids[] = {
	{"gmt-g2237", 0},
	{"gmt,g2237", 0},
	{}
};
MODULE_DEVICE_TABLE(i2c, g2237_regulator_ids);

static struct i2c_driver g2237_regulator_driver = {
	.driver = {
		.name = "gmt-g2237",
		.owner = THIS_MODULE,
		.pm = &g2237_regulator_pm_ops,
	},
	.id_table = g2237_regulator_ids,
	.probe    = g2237_regulator_probe,
	.shutdown = g2237_regulator_shutdown,
};
module_i2c_driver(g2237_regulator_driver);

MODULE_DESCRIPTION("GMT G2237 PMIC Driver");
MODULE_AUTHOR("Cheng-Yu Lee <cylee12@realtek.com>");
MODULE_LICENSE("GPL");

