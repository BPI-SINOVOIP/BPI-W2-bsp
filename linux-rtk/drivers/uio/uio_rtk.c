/*
 * Realtek Generic UIO Driver
 *
 * Copyright (C) 2017,2019 Realtek Semiconductor Corporation
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

#include <linux/clk.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/pm.h>
#include <linux/pm_clock.h>
#include <linux/pm_runtime.h>
#include <linux/reset.h>
#include <linux/slab.h>
#include <linux/uio_driver.h>

#ifdef CONFIG_UIO_ASSIGN_MINOR

struct minor_map {
	const char *name;
	int minor;
};

static const struct minor_map _map[] = {
	{ .name = "refclk", .minor = 253, },
	{ .name = "rbus",   .minor = 250, },
	{ .name = "tp",     .minor = 249, },
	{ .name = NULL,     .minor = 0,   }
};

static int rtk_uio_get_minor(const char *name)
{
	const struct minor_map *p;

	for (p = _map; p->name != NULL; p++)
		if (!strcmp(name, p->name))
			return p->minor;
	return 0;
}

#endif

struct rtk_uio_data {
	struct uio_info info;
	struct device *dev;
	struct reset_control *rstc;
};

#define to_data(_uio_info) ((_uio_info)->priv)

static int rtk_uio_open(struct uio_info *info, struct inode *inode)
{
	struct rtk_uio_data *priv = to_data(info);

	pm_runtime_get_sync(priv->dev);

	return 0;
}

static int rtk_uio_release(struct uio_info *info, struct inode *inode)
{
	struct rtk_uio_data *priv = to_data(info);

	pm_runtime_put_sync(priv->dev);

	return 0;
}

static int rtk_uio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int ret;
	struct rtk_uio_data *priv;
	struct uio_info *info;
	struct resource res;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	info = &priv->info;

	ret = pm_clk_create(dev);
	if (ret)
		dev_warn(dev, "failed to create pm_clk: %d\n", ret);
	else
		pm_clk_add(dev, NULL);

	if (of_get_property(np, "resets", NULL)) {
		priv->rstc = devm_reset_control_get(dev, NULL);
		if (IS_ERR(priv->rstc)) {
			ret = PTR_ERR(priv->rstc);
			dev_warn(dev, "failed to get reset control: %d\n", ret);
			priv->rstc = NULL;
		}
	}

	ret = of_address_to_resource(np, 0, &res);
	if (ret) {
		dev_err(dev, "failed to get resource: %d\n", ret);
		goto destroy_pm_clk;
	}
	info->mem[0].addr    = res.start;
	info->mem[0].size    = ALIGN(resource_size(&res), PAGE_SIZE);
	info->mem[0].memtype = UIO_MEM_PHYS;

	info->version = "0.0.2";
	info->name    = np->name;
	info->open    = rtk_uio_open;
	info->release = rtk_uio_release;
	info->priv    = priv;
#ifdef CONFIG_UIO_ASSIGN_MINOR
	info->minor = rtk_uio_get_minor(info->name);
	dev_dbg(dev, "minor is %d\n", info->minor);
#endif
	priv->dev     = dev;

	platform_set_drvdata(pdev, info);

	ret = uio_register_device(dev, info);
	if (ret) {
		dev_err(dev, "failed to register uio_device: %d\n", ret);
		goto destroy_pm_clk;
	}

	pm_runtime_set_suspended(dev);
	pm_runtime_enable(dev);
	if (priv->rstc)
		reset_control_deassert(priv->rstc);
	dev_info(dev, "initialized\n");
	return 0;
destroy_pm_clk:
	pm_clk_destroy(dev);
	return ret;

}

static int rtk_uio_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct uio_info *info = platform_get_drvdata(pdev);
	struct rtk_uio_data *priv = info->priv;

	if (priv->rstc)
		reset_control_assert(priv->rstc);
	pm_runtime_disable(dev);
	uio_unregister_device(info);
	platform_set_drvdata(pdev, NULL);
	pm_clk_destroy(dev);
	dev_info(dev, "removed\n");
	return 0;
}

static int rtk_uio_runtime_suspend(struct device *dev)
{
	int ret = 0;

	dev_dbg(dev, "enter %s\n", __func__);
	ret = pm_clk_suspend(dev);
	if (ret)
		dev_err(dev, "failed to pm_clk_suspend: %d\n", ret);
	dev_dbg(dev, "exit %s\n", __func__);
	return ret;
}

static int rtk_uio_runtime_resume(struct device *dev)
{
	int ret = 0;

	dev_dbg(dev, "enter %s\n", __func__);
	ret = pm_clk_resume(dev);
	if (ret)
		dev_err(dev, "failed to pm_clk_resume: %d\n", ret);
	dev_dbg(dev, "exit %s\n", __func__);
	return ret;
}

static const struct dev_pm_ops rtk_uio_dev_pm_ops = {
	.runtime_suspend = rtk_uio_runtime_suspend,
	.runtime_resume = rtk_uio_runtime_resume,
};

static const struct of_device_id rtk_uio_ids[] = {
	{ .compatible = "realtek,uio" },
	{}
};
MODULE_DEVICE_TABLE(of, rtk_uio_ids);

static struct platform_driver rtk_uio_driver = {
	.probe = rtk_uio_probe,
	.remove = rtk_uio_remove,
	.driver = {
		.name =  "rtk-uio",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(rtk_uio_ids),
		.pm = &rtk_uio_dev_pm_ops,
	},
};
module_platform_driver(rtk_uio_driver);

MODULE_AUTHOR("Cheng-Yu Lee");
MODULE_DESCRIPTION("Realtek Generic UIO driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:"  "rtk-uio");

