/*
 * apw8886-regulator.c - Anpec APW8886 Regulator sriver
 *
 * Copyright (C) 2018-2019 Realtek Semiconductor Corporation
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
 */

#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regmap.h>
#include <linux/suspend.h>
#include <linux/mfd/apw888x.h>
#include <linux/mfd/apw8886.h>
#include "apw888x-regulator.h"

/* regulator id */
enum {
	APW8886_ID_DC1 = 0,
	APW8886_ID_DC2,
	APW8886_ID_DC3,
	APW8886_ID_DC4,
	APW8886_ID_DC5,
	APW8886_ID_LDO1,
	APW8886_ID_MAX
};

#define APW8886_DESC(_id, _name, _min_uV, _uV_step, _n_volt, _type)\
{                                                                  \
	.desc = {                                                  \
		.owner       = THIS_MODULE,                        \
		.type        = REGULATOR_VOLTAGE,                  \
		.ops         = &apw888x_regulator_ops,             \
		.name        = _name,                              \
		.of_match    = _name,                              \
		.n_voltages  = _n_volt,                            \
		.min_uV      = _min_uV,                            \
		.uV_step     = _uV_step,                           \
		.id          = APW8886_ID_ ## _id,                 \
		.vsel_reg    = APW8886_REG_ ## _id ## _NRMVOLT,    \
		.vsel_mask   = APW8886_ ## _id ## _NRMVOLT_MASK,   \
		.enable_reg  = APW8886_REG_ONOFF,                  \
		.enable_mask = APW8886_ ## _id ## _ON_MASK,        \
		.enable_val  = APW8886_ ## _id ## _ON_MASK,        \
		.of_parse_cb = apw888x_regulator_of_parse_cb,      \
		.of_map_mode = apw888x_regulator_ ## _type ##_of_map_mode, \
	},                                                         \
	.nmode_reg  = APW8886_REG_ ## _id ## _MODE,                \
	.nmode_mask = APW8886_ ## _id ## _NRMMODE_MASK,            \
	.smode_reg  = APW8886_REG_ ## _id ## _MODE,                \
	.smode_mask = APW8886_ ## _id ## _SLPMODE_MASK,            \
	.svsel_reg  = APW8886_REG_ ## _id ## _SLPVOLT,             \
	.svsel_mask = APW8886_ ## _id ## _SLPVOLT_MASK,            \
}

#define APW8886_DESC_CLP(_id, _name, _min_uV, _uV_step, _n_volt, _type) \
{                                                                  \
	.desc = {                                                  \
		.owner       = THIS_MODULE,                        \
		.type        = REGULATOR_VOLTAGE,                  \
		.ops         = &apw888x_regulator_ops,             \
		.name        = _name,                              \
		.of_match    = _name,                              \
		.n_voltages  = _n_volt,                            \
		.min_uV      = _min_uV,                            \
		.uV_step     = _uV_step,                           \
		.id          = APW8886_ID_ ## _id,                 \
		.vsel_reg    = APW8886_REG_ ## _id ## _NRMVOLT,    \
		.vsel_mask   = APW8886_ ## _id ## _NRMVOLT_MASK,   \
		.enable_reg  = APW8886_REG_ONOFF,                  \
		.enable_mask = APW8886_ ## _id ## _ON_MASK,        \
		.enable_val  = APW8886_ ## _id ## _ON_MASK,        \
		.of_parse_cb = apw888x_regulator_of_parse_cb,      \
		.of_map_mode = apw888x_regulator_ ## _type ##_of_map_mode, \
	},                                                         \
	.nmode_reg  = APW8886_REG_ ## _id ## _MODE,                \
	.nmode_mask = APW8886_ ## _id ## _NRMMODE_MASK,            \
	.smode_reg  = APW8886_REG_ ## _id ## _MODE,                \
	.smode_mask = APW8886_ ## _id ## _SLPMODE_MASK,            \
	.svsel_reg  = APW8886_REG_ ## _id ## _SLPVOLT,             \
	.svsel_mask = APW8886_ ## _id ## _SLPVOLT_MASK,            \
	.clamp_reg  = APW8886_REG_CLAMP,                           \
	.clamp_mask = APW8886_ ## _id ## _CLAMP_MASK,              \
}

#define APW8886_DESC_FIXED_UV(_id, _name, _fixed_uV)               \
{                                                                  \
	.desc = {                                                  \
		.owner       = THIS_MODULE,                        \
		.type        = REGULATOR_VOLTAGE,                  \
		.ops         = &apw888x_regulator_fixed_uV_ops,    \
		.name        = _name,                              \
		.of_match    = _name,                              \
		.n_voltages  = 1,                                  \
		.fixed_uV    = _fixed_uV,                          \
		.id          = APW8886_ID_ ## _id,                 \
		.enable_reg  = APW8886_REG_ONOFF,                  \
		.enable_mask = APW8886_ ## _id ## _ON_MASK,        \
		.enable_val  = APW8886_ ## _id ## _ON_MASK,        \
		.of_parse_cb = apw888x_regulator_of_parse_cb,      \
		.of_map_mode = apw888x_regulator_dc_of_map_mode,   \
	},                                                         \
	.nmode_reg  = APW8886_REG_ ## _id ## _MODE,                \
	.nmode_mask = APW8886_ ## _id ## _NRMMODE_MASK,            \
	.smode_reg  = APW8886_REG_ ## _id ## _MODE,                \
	.smode_mask = APW8886_ ## _id ## _SLPMODE_MASK,            \
}

static struct apw888x_regulator_desc desc[] = {
	[APW8886_ID_DC1]  = APW8886_DESC(DC1, "dc1", 2200000, 25000, 64, dc),
	[APW8886_ID_DC2]  = APW8886_DESC_CLP(DC2, "dc2", 550000, 12500, 64, dc),
	[APW8886_ID_DC3]  = APW8886_DESC_CLP(DC3, "dc3", 550000, 12500, 64, dc),
	[APW8886_ID_DC4]  = APW8886_DESC(DC4, "dc4", 800000, 20000, 64, dc),
	[APW8886_ID_DC5]  = APW8886_DESC_FIXED_UV(DC5, "dc5", 0),
	[APW8886_ID_LDO1] = APW8886_DESC(LDO1, "ldo1", 1780000, 40000, 32, ldo),
};

/* pm */
static int apw8886_regulator_suspend(struct device *dev)
{
	struct apw888x_regulator_data *pos;
	struct apw888x_regulator_device *ardev = dev_get_drvdata(dev);

#ifdef CONFIG_SUSPEND
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY)
		goto done;
#endif

	dev_info(dev, "Enter %s\n", __func__);
	list_for_each_entry(pos, &ardev->list, list)
		apw888x_prepare_suspend_state(pos->rdev, 0);
	regulator_suspend_prepare(PM_SUSPEND_MEM);
	dev_info(dev, "Exit %s\n", __func__);
done:
	return 0;
}

static const struct dev_pm_ops apw8886_regulator_pm_ops = {
	.suspend = apw8886_regulator_suspend,
};

static int apw8886_regulator_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct apw888x_device *adev = dev_get_drvdata(dev->parent);
	struct apw888x_regulator_device *ardev;
	int i, ret;

	ardev = devm_kzalloc(dev, sizeof(*ardev), GFP_KERNEL);
	if (!ardev)
		return -ENOMEM;
	ardev->dev = dev;
	INIT_LIST_HEAD(&ardev->list);
	ardev->regmap = adev->regmap;

	for (i = 0; i < ARRAY_SIZE(desc); i++) {
		ret = apw888x_regulator_register(ardev, &desc[i]);
		if (ret) {
			dev_err(dev, "Failed to register %s: %d\n",
				desc[i].desc.name, ret);
			return ret;
		}
	}

	platform_set_drvdata(pdev, ardev);
	dev_info(dev, "initialized\n");
	return 0;
}

static void apw8886_regulator_shutdown(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct apw888x_regulator_device *ardev = platform_get_drvdata(pdev);
	struct apw888x_regulator_data *pos;

	dev_info(dev, "Enter %s\n", __func__);
	list_for_each_entry(pos, &ardev->list, list)
		apw888x_prepare_suspend_state(pos->rdev, 1);
	regulator_suspend_prepare(PM_SUSPEND_MEM);
	dev_info(dev, "Exit %s\n", __func__);
}

static const struct of_device_id apw8886_regulator_ids[] = {
	{ .compatible = "anpec,apw8886-regulator", },
	{}
};
MODULE_DEVICE_TABLE(of, apw8886_regulator_ids);

static struct platform_driver apw8886_regulator_driver = {
	.driver = {
		.name = "apw8886-regulator",
		.owner = THIS_MODULE,
		.pm = &apw8886_regulator_pm_ops,
		.of_match_table = apw8886_regulator_ids,
	},
	.probe    = apw8886_regulator_probe,
	.shutdown = apw8886_regulator_shutdown,
};
module_platform_driver(apw8886_regulator_driver);

MODULE_DESCRIPTION("Anpec APW8886 Regulator Driver");
MODULE_AUTHOR("Cheng-Yu Lee <cylee12@realtek.com>");
MODULE_LICENSE("GPL");


