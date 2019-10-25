/*
 * GMT-G22xx series PMIC Poweroff Driver
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
 */

#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <linux/mfd/g22xx.h>
#include <linux/mfd/g2227.h>

struct g22xx_poweroff_data {
	struct device *dev;
	struct g22xx_device *gdev;
	struct regmap_field *off;
};

static struct g22xx_poweroff_data *poweroff_data;

static void g22xx_pm_power_off(void)
{
	dev_emerg(poweroff_data->dev, "set softoff\n");
	regmap_field_write(poweroff_data->off, 1);
	for (;;)
		;
}

static int g22xx_poweroff_probe(struct platform_device *pdev)
{
	struct g22xx_poweroff_data *pdata;
	struct device *dev = &pdev->dev;
	struct g22xx_device *gdev = dev_get_drvdata(dev->parent);
	int ret;
	struct reg_field map = REG_FIELD(G2227_REG_SYS_CONTROL,
				 G2227_SOFTOFF_SHIFT,
				 G2227_SOFTOFF_SHIFT + G2227_SOFTOFF_WIDTH - 1);

	if (!dev->of_node || !of_device_is_available(dev->of_node))
		return -ENODEV;

	if (!gdev) {
		dev_err(dev, "no parent device\n");
		return -EINVAL;
	}

	if (!of_device_is_system_power_controller(dev->of_node)) {
		dev_info(dev, "not a system power controller\n");
		return 0;
	}

	if (pm_power_off) {
		dev_err(dev, "pm_power_off is already assigned with %pf\n",
			pm_power_off);
		return -EINVAL;
	}

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	pdata->dev = dev;
	pdata->gdev = gdev;
	pdata->off = devm_regmap_field_alloc(dev, gdev->regmap, map);
	if (IS_ERR(pdata->off)) {
		ret = PTR_ERR(pdata->off);
		dev_err(dev, "failed to create regmap field: %d\n", ret);
		return ret;
	}

	poweroff_data = pdata;
	pm_power_off = g22xx_pm_power_off;
	platform_set_drvdata(pdev, poweroff_data);
	dev_info(dev, "initialized\n");
	return 0;
}
static int g22xx_poweroff_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	platform_set_drvdata(pdev, NULL);
	pm_power_off = NULL;
	poweroff_data = NULL;
	dev_info(dev, "removed\n");
	return 0;
}

static const struct of_device_id g22xx_poweroff_ids[] = {
	{ .compatible = "gmt,g22xx-poweroff", },
	{}
};
static struct platform_driver g22xx_poweroff_driver = {
	.probe = g22xx_poweroff_probe,
	.remove = g22xx_poweroff_remove,
	.driver = {
		.name = "g22xx-poweroff",
		.of_match_table = g22xx_poweroff_ids,
	},
};
module_platform_driver(g22xx_poweroff_driver);

