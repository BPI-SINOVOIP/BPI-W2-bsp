/*
 * g2227-regulator.c - GMT-G2227 Regulator Driver
 *
 * Copyright (C) 2016-2018 Realtek Semiconductor Corporation
 * Copyright (C) 2016-2018 Cheng-Yu Lee <cylee12@realtek.com>
 * Copyright (C) 2016 Simon Hsu <simon_hsu@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#define pr_fmt(fmt) "g2227: " fmt

#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regmap.h>
#include <linux/suspend.h>
#include <soc/realtek/rtk_cpu.h>
#include <soc/realtek/rtk_regmap.h>
#include <dt-bindings/regulator/gmt,g2227.h>
#include "g22xx-regulator.h"

/* regulator id */
enum g2227_regulator_id {
	G2227_ID_DCDC1 = 0,
	G2227_ID_DCDC2,
	G2227_ID_DCDC3,
	G2227_ID_DCDC4,
	G2227_ID_DCDC5,
	G2227_ID_DCDC6,
	G2227_ID_LDO2,
	G2227_ID_LDO3,
	G2227_ID_MAX
};

/* reg_field id */
enum {
	G2227_REG_FIELD_LPOFF_TO_DO = 0,
	G2227_REG_FIELD_TIME_LPOFF,
	G2227_REG_FIELD_TIME_LP,
	G2227_REG_FIELD_TIME_IT,
	G2227_REG_FIELD_SOFTOFF,

	G2227_REG_FIELD_DCDC1_ON,
	G2227_REG_FIELD_DCDC1_NMODE,
	G2227_REG_FIELD_DCDC1_SMODE,
	G2227_REG_FIELD_DCDC1_NVO,
	G2227_REG_FIELD_DCDC1_SVO,

	G2227_REG_FIELD_DCDC2_ON,
	G2227_REG_FIELD_DCDC2_NMODE,
	G2227_REG_FIELD_DCDC2_SMODE,
	G2227_REG_FIELD_DCDC2_NVO,
	G2227_REG_FIELD_DCDC2_SVO,

	G2227_REG_FIELD_DCDC3_ON,
	G2227_REG_FIELD_DCDC3_NMODE,
	G2227_REG_FIELD_DCDC3_SMODE,
	G2227_REG_FIELD_DCDC3_NVO,
	G2227_REG_FIELD_DCDC3_SVO,

	G2227_REG_FIELD_DCDC4_ON,
	G2227_REG_FIELD_DCDC4_NMODE,
	G2227_REG_FIELD_DCDC4_SMODE,

	G2227_REG_FIELD_DCDC5_ON,
	G2227_REG_FIELD_DCDC5_NMODE,
	G2227_REG_FIELD_DCDC5_SMODE,
	G2227_REG_FIELD_DCDC5_NVO,
	G2227_REG_FIELD_DCDC5_SVO,

	G2227_REG_FIELD_DCDC6_ON,
	G2227_REG_FIELD_DCDC6_NMODE,
	G2227_REG_FIELD_DCDC6_SMODE,
	G2227_REG_FIELD_DCDC6_NVO,
	G2227_REG_FIELD_DCDC6_SVO,

	G2227_REG_FIELD_LDO2_ON,
	G2227_REG_FIELD_LDO2_NMODE,
	G2227_REG_FIELD_LDO2_SMODE,
	G2227_REG_FIELD_LDO2_NVO,
	G2227_REG_FIELD_LDO2_SVO,

	G2227_REG_FIELD_LDO3_ON,
	G2227_REG_FIELD_LDO3_NMODE,
	G2227_REG_FIELD_LDO3_SMODE,
	G2227_REG_FIELD_LDO3_NVO,
	G2227_REG_FIELD_LDO3_SVO,

	G2227_REG_FIELD_CHIP_ID,
	G2227_REG_FIELD_VERSION,

	G2227_REG_FIELD_MAX
};

/* reg_field */
static const struct reg_field regs[G2227_REG_FIELD_MAX] __initconst = {
	[G2227_REG_FIELD_LPOFF_TO_DO] = REG_FIELD(0x02, 7, 7),
	[G2227_REG_FIELD_TIME_IT]     = REG_FIELD(0x02, 4, 5),
	[G2227_REG_FIELD_TIME_LP]     = REG_FIELD(0x02, 2, 3),
	[G2227_REG_FIELD_TIME_LPOFF]  = REG_FIELD(0x02, 0, 1),
	[G2227_REG_FIELD_SOFTOFF]     = REG_FIELD(0x04, 7, 7),
	[G2227_REG_FIELD_DCDC1_ON]    = REG_FIELD(0x05, 7, 7),
	[G2227_REG_FIELD_DCDC2_ON]    = REG_FIELD(0x05, 6, 6),
	[G2227_REG_FIELD_DCDC3_ON]    = REG_FIELD(0x05, 5, 5),
	[G2227_REG_FIELD_DCDC4_ON]    = REG_FIELD(0x05, 4, 4),
	[G2227_REG_FIELD_DCDC5_ON]    = REG_FIELD(0x05, 3, 3),
	[G2227_REG_FIELD_DCDC6_ON]    = REG_FIELD(0x05, 2, 2),
	[G2227_REG_FIELD_LDO2_ON]     = REG_FIELD(0x05, 1, 1),
	[G2227_REG_FIELD_LDO3_ON]     = REG_FIELD(0x05, 0, 0),
	[G2227_REG_FIELD_DCDC1_NMODE] = REG_FIELD(0x07, 6, 7),
	[G2227_REG_FIELD_DCDC1_SMODE] = REG_FIELD(0x07, 4, 5),
	[G2227_REG_FIELD_DCDC2_NMODE] = REG_FIELD(0x07, 2, 3),
	[G2227_REG_FIELD_DCDC2_SMODE] = REG_FIELD(0x07, 0, 1),
	[G2227_REG_FIELD_DCDC3_NMODE] = REG_FIELD(0x08, 6, 7),
	[G2227_REG_FIELD_DCDC3_SMODE] = REG_FIELD(0x08, 4, 5),
	[G2227_REG_FIELD_DCDC4_NMODE] = REG_FIELD(0x08, 2, 3),
	[G2227_REG_FIELD_DCDC4_SMODE] = REG_FIELD(0x08, 0, 1),
	[G2227_REG_FIELD_DCDC5_NMODE] = REG_FIELD(0x09, 6, 7),
	[G2227_REG_FIELD_DCDC5_SMODE] = REG_FIELD(0x09, 4, 5),
	[G2227_REG_FIELD_DCDC6_NMODE] = REG_FIELD(0x09, 2, 3),
	[G2227_REG_FIELD_DCDC6_SMODE] = REG_FIELD(0x09, 0, 1),
	[G2227_REG_FIELD_LDO2_NMODE]  = REG_FIELD(0x0A, 6, 7),
	[G2227_REG_FIELD_LDO2_SMODE]  = REG_FIELD(0x0A, 4, 5),
	[G2227_REG_FIELD_LDO3_NMODE]  = REG_FIELD(0x0A, 2, 3),
	[G2227_REG_FIELD_LDO3_SMODE]  = REG_FIELD(0x0A, 0, 1),
	[G2227_REG_FIELD_DCDC2_NVO]   = REG_FIELD(0x10, 0, 4),
	[G2227_REG_FIELD_DCDC3_NVO]   = REG_FIELD(0x11, 0, 4),
	[G2227_REG_FIELD_DCDC5_NVO]   = REG_FIELD(0x12, 0, 4),
	[G2227_REG_FIELD_DCDC1_NVO]   = REG_FIELD(0x13, 6, 7),
	[G2227_REG_FIELD_DCDC6_NVO]   = REG_FIELD(0x13, 0, 4),
	[G2227_REG_FIELD_LDO2_NVO]    = REG_FIELD(0x14, 4, 7),
	[G2227_REG_FIELD_LDO3_NVO]    = REG_FIELD(0x14, 0, 3),
	[G2227_REG_FIELD_DCDC2_SVO]   = REG_FIELD(0x15, 0, 4),
	[G2227_REG_FIELD_DCDC3_SVO]   = REG_FIELD(0x16, 0, 4),
	[G2227_REG_FIELD_DCDC5_SVO]   = REG_FIELD(0x17, 0, 4),
	[G2227_REG_FIELD_DCDC1_SVO]   = REG_FIELD(0x18, 6, 7),
	[G2227_REG_FIELD_DCDC6_SVO]   = REG_FIELD(0x18, 0, 4),
	[G2227_REG_FIELD_LDO2_SVO]    = REG_FIELD(0x19, 4, 7),
	[G2227_REG_FIELD_LDO3_SVO]    = REG_FIELD(0x19, 0, 3),
	[G2227_REG_FIELD_CHIP_ID]     = REG_FIELD(0x20, 3, 7),
	[G2227_REG_FIELD_VERSION]     = REG_FIELD(0x20, 0, 2),
};

/* desc initdata */
static struct g22xx_desc_initdata initdata[G2227_ID_MAX] = {
	[G2227_ID_DCDC1] = G22XX_DESC_INITDATA(G2227, DCDC1, regs),
	[G2227_ID_DCDC2] = G22XX_DESC_INITDATA(G2227, DCDC2, regs),
	[G2227_ID_DCDC3] = G22XX_DESC_INITDATA(G2227, DCDC3, regs),
	[G2227_ID_DCDC4] = G22XX_DESC_INITDATA_NO_VO(G2227, DCDC4, regs),
	[G2227_ID_DCDC5] = G22XX_DESC_INITDATA(G2227, DCDC5, regs),
	[G2227_ID_DCDC6] = G22XX_DESC_INITDATA(G2227, DCDC6, regs),
	[G2227_ID_LDO2]  = G22XX_DESC_INITDATA(G2227, LDO2, regs),
	[G2227_ID_LDO3]  = G22XX_DESC_INITDATA(G2227, LDO3, regs),
};

/* voltage table */
static const unsigned int dcdc1_vtbl[] = {
	3000000, 3100000, 3200000, 3300000,
};

static const unsigned int dcdcx_vtbl[] = {
	 800000,  812500,  825000,  837500,  850000,  862500,  875000,  887500,
	 900000,  912500,  925000,  937500,  950000,  962500,  975000,  987500,
	1000000, 1012500, 1025000, 1037500, 1050000, 1062500, 1075000, 1087500,
	1100000, 1112500, 1125000, 1137500, 1150000, 1162500, 1175000, 1187500,
};

static const unsigned int dcdc4_vtbl[] = {
	1800000,
};

static const unsigned int ldo_vtbl[] = {
	 800000,  850000,  900000,  950000, 1000000, 1100000, 1200000, 1300000,
	1500000, 1600000, 1800000, 1900000, 2500000, 2600000, 3000000, 3100000,
};

/* mode mapping callback */
static unsigned int g2227_regulator_dc_of_map_mode(unsigned int mode)
{
	if (mode == G2227_DC_MODE_FORCE_PWM)
		return REGULATOR_MODE_FAST;
	return REGULATOR_MODE_NORMAL;
}

static unsigned int g2227_regulator_ldo_of_map_mode(unsigned int mode)
{
	if (mode == G2227_LDO_MODE_ECO)
		return REGULATOR_MODE_IDLE;
	return REGULATOR_MODE_NORMAL;
}

/* regulator_desc */
static struct g22xx_desc desc[G2227_ID_MAX] = {
	[G2227_ID_DCDC1] = {
		.desc = G22XX_DESC(G2227_ID_DCDC1, "dcdc1", dcdc1_vtbl),
		.desc.of_map_mode = g2227_regulator_dc_of_map_mode,
	},
	[G2227_ID_DCDC2] = {
		.desc = G22XX_DESC(G2227_ID_DCDC2, "dcdc2", dcdcx_vtbl),
		.desc.of_map_mode = g2227_regulator_dc_of_map_mode,
	},
	[G2227_ID_DCDC3] = {
		.desc = G22XX_DESC(G2227_ID_DCDC3, "dcdc3", dcdcx_vtbl),
		.desc.of_map_mode = g2227_regulator_dc_of_map_mode,
		.delay_volt_up = 40,
	},
	[G2227_ID_DCDC4] = {
		.desc = G22XX_DESC(G2227_ID_DCDC4, "dcdc4", dcdc4_vtbl),
		.desc.of_map_mode = g2227_regulator_dc_of_map_mode,
	},
	[G2227_ID_DCDC5] = {
		.desc = G22XX_DESC(G2227_ID_DCDC5, "dcdc5", dcdcx_vtbl),
		.desc.of_map_mode = g2227_regulator_dc_of_map_mode,
	},
	[G2227_ID_DCDC6] = {
		.desc = G22XX_DESC(G2227_ID_DCDC6, "dcdc6", dcdcx_vtbl),
		.desc.of_map_mode = g2227_regulator_dc_of_map_mode,
	},
	[G2227_ID_LDO2] = {
		.desc = G22XX_DESC(G2227_ID_LDO2, "ldo2", ldo_vtbl),
		.desc.of_map_mode = g2227_regulator_ldo_of_map_mode,
		.flags = G22XX_FLAG_TYPE_LDO,
	},
	[G2227_ID_LDO3] = {
		.desc = G22XX_DESC(G2227_ID_LDO3, "ldo3", ldo_vtbl),
		.desc.of_map_mode = g2227_regulator_ldo_of_map_mode,
		.flags = G22XX_FLAG_TYPE_LDO,
	},
};

/* regmap */
static const struct reg_default g2227_regmap_defaults[] = {
	{ .reg = 0x02, .def = 0xc7, },
	{ .reg = 0x04, .def = 0x01, },
	/* on/off */
	{ .reg = 0x05, .def = 0xff, },
	/* mode */
	{ .reg = 0x07, .def = 0x22, },
	{ .reg = 0x08, .def = 0x22, },
	{ .reg = 0x09, .def = 0x22, },
	{ .reg = 0x0a, .def = 0x22, },
	/* nrm volt */
	{ .reg = 0x10, .def = 0x10, },
	{ .reg = 0x11, .def = 0x10, },
	{ .reg = 0x12, .def = 0x10, },
	{ .reg = 0x13, .def = 0xd0, },
	{ .reg = 0x14, .def = 0xa2, },
	/* slp volt */
	{ .reg = 0x15, .def = 0x10, },
	{ .reg = 0x16, .def = 0x10, },
	{ .reg = 0x17, .def = 0x10, },
	{ .reg = 0x18, .def = 0xd0, },
	{ .reg = 0x19, .def = 0xa2, },
	/* version */
	{ .reg = 0x20, .def = 0xd8, },
};

static bool g2227_regmap_writeable_reg(struct device *dev, unsigned int reg)
{
	return reg != 0;
}

static bool g2227_regmap_precious_reg(struct device *dev, unsigned int reg)
{
	return reg == 0;
}

static bool g2227_regmap_volatile_reg(struct device *dev, unsigned int reg)
{
	return reg == 0x20;
}

static const struct regmap_config g2227_regmap_config_no_cache = {
	.reg_bits         = 8,
	.val_bits         = 8,
	.max_register     = 0x20,
	.writeable_reg    = g2227_regmap_writeable_reg,
	.precious_reg     = g2227_regmap_precious_reg,
	.volatile_reg     = g2227_regmap_volatile_reg,
};

static const struct regmap_config g2227_regmap_config = {
	.reg_bits         = 8,
	.val_bits         = 8,
	.max_register     = 0x20,
	.cache_type       = REGCACHE_FLAT,
	.reg_defaults     = g2227_regmap_defaults,
	.num_reg_defaults = ARRAY_SIZE(g2227_regmap_defaults),
	.writeable_reg    = g2227_regmap_writeable_reg,
	.precious_reg     = g2227_regmap_precious_reg,
	.volatile_reg     = g2227_regmap_volatile_reg,
};

/* pm */
static int g2227_regulator_suspend(struct device *dev)
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

static const struct dev_pm_ops g2227_regulator_pm_ops = {
	.suspend = g2227_regulator_suspend,
};

static int g2227_regulator_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device_node *np = dev->of_node;
	struct g22xx_device *gdev;
	struct regmap *regmap;
	const struct regmap_config *cfg;
	int i, ret;
	unsigned int val;
	int chip_rev;

	dev_info(dev, "%s\n", __func__);

	gdev = devm_kzalloc(dev, sizeof(*gdev), GFP_KERNEL);
	if (!gdev)
		return -ENOMEM;
	gdev->maps = devm_kcalloc(dev, G2227_REG_FIELD_MAX,
		sizeof(*gdev->maps), GFP_KERNEL);
	if (!gdev->maps)
		return -ENOMEM;

	/* bootargs: disable regcache */
	if (g22xx_regcache_disabled()) {
		dev_info(dev, "no regcache\n");
		cfg = &g2227_regmap_config_no_cache;
	} else
		cfg = &g2227_regmap_config;

	regmap = devm_rtk_regmap_i2c_init(dev, client, cfg);
	if (IS_ERR(regmap))
		return -EINVAL;

	/* convert all reg_field to regmap_field */
	for (i = 0; i < G2227_REG_FIELD_MAX; i++) {
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

	chip_rev = get_rtd129x_cpu_revision();
	gdev->regmap = regmap;
	gdev->client = client;
	gdev->dev    = dev;

	/* workaround */
	ret = regmap_field_read(gdev->maps[G2227_REG_FIELD_VERSION], &val);
	if (ret)
		dev_warn(dev, "failed to reader version: %d\n", ret);
	else
		dev_info(dev, "g2227 version %02x\n", val);

	for (i = 0; i < ARRAY_SIZE(desc); i++) {
		ret = g22xx_regulator_register(gdev, &desc[i], &initdata[i]);
		if (ret) {
			dev_err(dev, "Failed to register %s: %d\n",
				g22xx_desc_name(&desc[i]), ret);
			return ret;
		}

		/* workaround */
		if (desc[i].desc.id == G2227_ID_DCDC6 &&
			(chip_rev == RTD129x_CHIP_REVISION_A00 ||
			chip_rev == RTD129x_CHIP_REVISION_B00)) {
			desc[i].state_mem.enabled  = true;
			desc[i].state_mem.disabled = false;
		}
	}

	i2c_set_clientdata(client, gdev);

	/* setup pm_power_off */
	ret = g22xx_setup_pm_power_off(dev,
		gdev->maps[G2227_REG_FIELD_SOFTOFF]);
	if (ret == 1)
		dev_info(dev, "system-power-controller\n");
	else if (ret <= 0)
		dev_err(dev, "g22xx_setup_pm_power_off() returns %d\n", ret);

	/* parse dt */
	if (of_property_read_u32(np, "g2227,lpoff-act", &val))
		val = G2227_LPOFF_TO_SHUTDOWN;
	regmap_field_write(gdev->maps[G2227_REG_FIELD_LPOFF_TO_DO], val);

	if (of_property_read_u32(np, "g2227,lpoff-time", &val))
		val = G2227_TIME_LPOFF_08S;
	regmap_field_write(gdev->maps[G2227_REG_FIELD_TIME_LPOFF], val);

	return 0;
}

static void g2227_regulator_shutdown(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	int i;

	dev_info(dev, "Enter %s\n", __func__);
	for (i = 0; i < ARRAY_SIZE(desc); i++)
		g22xx_prepare_suspend_state(desc[i].rdev, 1);
	regulator_suspend_prepare(PM_SUSPEND_MEM);
	dev_info(dev, "Exit %s\n", __func__);
}

static const struct i2c_device_id g2227_regulator_ids[] = {
	{"gmt-g2227", 0},
	{"gmt,g2227", 0},
	{}
};
MODULE_DEVICE_TABLE(i2c, g2227_regulator_ids);

static struct i2c_driver g2227_regulator_driver = {
	.driver = {
		.name = "gmt-g2227",
		.owner = THIS_MODULE,
		.pm = &g2227_regulator_pm_ops,
	},
	.id_table = g2227_regulator_ids,
	.probe    = g2227_regulator_probe,
	.shutdown = g2227_regulator_shutdown,
};
module_i2c_driver(g2227_regulator_driver);

MODULE_DESCRIPTION("GMT G2227 PMIC Driver");
MODULE_AUTHOR("Simon Hsu <simon_hsu@realtek.com>");
MODULE_AUTHOR("Cheng-Yu Lee <cylee12@realtek.com>");
MODULE_LICENSE("GPL");
