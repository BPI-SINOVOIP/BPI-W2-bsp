/*
 * GMT-G2227 PMIC Regulator driver
 *
 * Copyright (C) 2016-2019 Realtek Semiconductor Corporation
 *
 * Author:
 *      Cheng-Yu Lee <cylee12@realtek.com>
 *      Simon Hsu <simon_hsu@realtek.com>
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

#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regmap.h>
#include <linux/suspend.h>
#include <linux/mfd/g2227.h>
#include <soc/realtek/rtk_chip.h>
#include "g22xx-regulator.h"

/* regulator id */
enum g2227_regulator_id {
	G2227_ID_DC1 = 0,
	G2227_ID_DC2,
	G2227_ID_DC3,
	G2227_ID_DC4,
	G2227_ID_DC5,
	G2227_ID_DC6,
	G2227_ID_LDO2,
	G2227_ID_LDO3,
	G2227_ID_MAX
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

static const unsigned int ldo_vtbl[] = {
	 800000,  850000,  900000,  950000, 1000000, 1100000, 1200000, 1300000,
	1500000, 1600000, 1800000, 1900000, 2500000, 2600000, 3000000, 3100000,
};

#define G2227_DESC(_id, _name, _vtbl, _type)                       \
{                                                                  \
	.desc = {                                                  \
		.owner       = THIS_MODULE,                        \
		.type        = REGULATOR_VOLTAGE,                  \
		.ops         = &g22xx_regulator_ops,               \
		.name        = _name,                              \
		.of_match    = _name,                              \
		.n_voltages  = ARRAY_SIZE(_vtbl),                  \
		.volt_table  = _vtbl,                              \
		.id          = G2227_ID_ ## _id,                   \
		.vsel_reg    = G2227_REG_ ## _id ## _NRMVOLT,      \
		.vsel_mask   = G2227_ ## _id ## _NRMVOLT_MASK,     \
		.enable_reg  = G2227_REG_ONOFF,                    \
		.enable_mask = G2227_ ## _id ## _ON_MASK,          \
		.enable_val  = G2227_ ## _id ## _ON_MASK,          \
		.of_map_mode = g22xx_regulator_ ## _type ##_of_map_mode, \
		.of_parse_cb = g22xx_regulator_of_parse_cb,        \
	},                                                         \
	.nmode_reg  = G2227_REG_ ## _id ## _MODE,                  \
	.nmode_mask = G2227_ ## _id ## _NRMMODE_MASK,              \
	.smode_reg  = G2227_REG_ ## _id ## _MODE,                  \
	.smode_mask = G2227_ ## _id ## _SLPMODE_MASK,              \
	.svsel_reg  = G2227_REG_ ## _id ## _SLPVOLT,               \
	.svsel_mask = G2227_ ## _id ## _SLPVOLT_MASK,              \
}

#define G2227_DESC_FIXED_UV(_id, _name, _fixed_uV)                 \
{                                                                  \
	.desc = {                                                  \
		.owner       = THIS_MODULE,                        \
		.type        = REGULATOR_VOLTAGE,                  \
		.ops         = &g22xx_regulator_fixed_uV_ops,      \
		.name        = _name,                              \
		.of_match    = _name,                              \
		.n_voltages  = 1,                                  \
		.fixed_uV    = _fixed_uV,                          \
		.id          = G2227_ID_ ## _id,                   \
		.enable_reg  = G2227_REG_ONOFF,                    \
		.enable_mask = G2227_ ## _id ## _ON_MASK,          \
		.enable_val  = G2227_ ## _id ## _ON_MASK,          \
		.of_map_mode = g22xx_regulator_dc_of_map_mode,     \
		.of_parse_cb = g22xx_regulator_of_parse_cb,        \
	},                                                         \
	.nmode_reg  = G2227_REG_ ## _id ## _MODE,                  \
	.nmode_mask = G2227_ ## _id ## _NRMMODE_MASK,              \
	.smode_reg  = G2227_REG_ ## _id ## _MODE,                  \
	.smode_mask = G2227_ ## _id ## _SLPMODE_MASK,              \
}

/* regulator_desc */
static struct g22xx_regulator_desc desc[G2227_ID_MAX] = {
	[G2227_ID_DC1]  = G2227_DESC(DC1,  "dc1",  dcdc1_vtbl, dc),
	[G2227_ID_DC2]  = G2227_DESC(DC2,  "dc2",  dcdcx_vtbl, dc),
	[G2227_ID_DC3]  = G2227_DESC(DC3,  "dc3",  dcdcx_vtbl, dc),
	[G2227_ID_DC4]  = G2227_DESC_FIXED_UV(DC4, "dc4", 0),
	[G2227_ID_DC5]  = G2227_DESC(DC5,  "dc5",  dcdcx_vtbl, dc),
	[G2227_ID_DC6]  = G2227_DESC(DC6,  "dc6",  dcdcx_vtbl, dc),
	[G2227_ID_LDO2] = G2227_DESC(LDO2, "ldo2", ldo_vtbl,   ldo),
	[G2227_ID_LDO3] = G2227_DESC(LDO3, "ldo3", ldo_vtbl,   ldo),
};


/* pm */
static int g2227_regulator_suspend(struct device *dev)
{
	struct g22xx_regulator_device *grdev = dev_get_drvdata(dev);
	struct g22xx_regulator_data *pos;

#ifdef CONFIG_SUSPEND
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY)
		goto done;
#endif

	dev_info(dev, "Enter %s\n", __func__);
	list_for_each_entry(pos, &grdev->list, list)
		g22xx_prepare_suspend_state(pos->rdev, 0);
	regulator_suspend_prepare(PM_SUSPEND_MEM);
	dev_info(dev, "Exit %s\n", __func__);
done:
	return 0;
}

static const struct dev_pm_ops g2227_regulator_pm_ops = {
	.suspend = g2227_regulator_suspend,
};

static int g2227_regulator_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct g22xx_device *gdev = dev_get_drvdata(dev->parent);
	struct g22xx_regulator_device *grdev;
	int i, ret;
	int chip_rev;

	grdev = devm_kzalloc(dev, sizeof(*grdev), GFP_KERNEL);
	if (!grdev)
		return -ENOMEM;

	grdev->regmap = gdev->regmap;
	grdev->dev = dev;
	INIT_LIST_HEAD(&grdev->list);
	chip_rev = get_rtd_chip_revision();

	for (i = 0; i < ARRAY_SIZE(desc); i++) {
		struct regulator_dev *rdev;

		rdev = g22xx_regulator_register(grdev, &desc[i]);
		if (IS_ERR(rdev)) {
			ret = PTR_ERR(rdev);
			dev_err(dev, "failed to register %s: %d\n",
				desc[i].desc.name, ret);
			return ret;
		}
#ifdef CONFIG_ARCH_RTD129x
		/* workaround */
		if (desc[i].desc.id == G2227_ID_DC6 &&
		   (chip_rev == RTD_CHIP_A00 || chip_rev == RTD_CHIP_B00)) {
			struct g22xx_regulator_data *data
				= rdev_get_drvdata(rdev);

			BUG_ON(!data);
			data->state_mem.enabled = true;
			data->state_mem.disabled = false;
		}
#endif
	}

	platform_set_drvdata(pdev, grdev);
	dev_info(dev, "initialized\n");
	return 0;
}

static void g2227_regulator_shutdown(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct g22xx_regulator_device *grdev = platform_get_drvdata(pdev);
	struct g22xx_regulator_data *pos;

	dev_info(dev, "Enter %s\n", __func__);
	list_for_each_entry(pos, &grdev->list, list)
		g22xx_prepare_suspend_state(pos->rdev, 1);
	regulator_suspend_prepare(PM_SUSPEND_MEM);
	dev_info(dev, "Exit %s\n", __func__);
}


static const struct of_device_id g2227_regulator_ids[] = {
	{ .compatible = "gmt,g2227-regulator", },
	{}
};
MODULE_DEVICE_TABLE(i2c, g2227_regulator_ids);

static struct platform_driver g2227_regulator_driver = {
	.driver = {
		.name = "g2227-regulator",
		.owner = THIS_MODULE,
		.pm = &g2227_regulator_pm_ops,
		.of_match_table = g2227_regulator_ids,
	},
	.probe    = g2227_regulator_probe,
	.shutdown = g2227_regulator_shutdown,
};
module_platform_driver(g2227_regulator_driver);

MODULE_DESCRIPTION("GMT G2237 Regulator Driver");
MODULE_AUTHOR("Simon Hsu <simon_hsu@realtek.com>");
MODULE_AUTHOR("Cheng-Yu Lee <cylee12@realtek.com>");
MODULE_LICENSE("GPL");
