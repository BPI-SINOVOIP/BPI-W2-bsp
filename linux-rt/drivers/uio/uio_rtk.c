/*
 * Realtek Generic UIO Driver
 *
 * Copyright (C) 2017, Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
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

#include "uio_helper.h"

#define DRIVER_NAME "rtk-uio"

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
	struct uio_info *info;
	struct device *dev;
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

	dev_info(dev, "%s\n", __func__);

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	info = devm_kzalloc(dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	ret = pm_clk_create(dev);
	if (ret)
		dev_warn(dev, "pm_clk_create() returns %d\n", ret);
	else
		pm_clk_add(dev, NULL);

	ret = uio_mem_of_iomap(dev, &info->mem[0], 0);
	if (ret) {
		dev_err(dev, "uio_mem_of_iomap() returns %d\n", ret);
		goto destroy_pm_clk;
	}

	info->version = "0.0.1";
	info->name    = np->name;
	info->open    = rtk_uio_open;
	info->release = rtk_uio_release;
	info->priv    = priv;
#ifdef CONFIG_UIO_ASSIGN_MINOR
	info->minor = rtk_uio_get_minor(info->name);
	dev_dbg(dev, "minor is %d\n", info->minor);
#endif
	priv->info    = info;
	priv->dev     = dev;

	platform_set_drvdata(pdev, info);

	ret = uio_register_device(dev, info);
	if (ret) {
		dev_err(dev, "uio_register_device() returns %d\n", ret);
		goto unmap;
	}

	ret = uio_reset_control_deassert(dev, NULL);
	if (ret)
		dev_warn(dev, "uio_reset_control_deassert() returns %d\n", ret);

	pm_runtime_set_suspended(dev);
	pm_runtime_enable(dev);

	return 0;
unmap:
	uio_mem_iounmap(dev, &info->mem[0]);
destroy_pm_clk:
	pm_clk_destroy(dev);
	return ret;

}

static int rtk_uio_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct uio_info *info = platform_get_drvdata(pdev);

	dev_info(dev, "%s\n", __func__);

	pm_runtime_disable(dev);
	uio_unregister_device(info);
	platform_set_drvdata(pdev, NULL);
	uio_reset_control_assert(dev, NULL);
	uio_mem_iounmap(dev, &info->mem[0]);
	pm_clk_destroy(dev);

	return 0;
}

static int rtk_uio_runtime_suspend(struct device *dev)
{
	int ret = 0;

	dev_dbg(dev, "Enter %s\n", __func__);
	ret = pm_clk_suspend(dev);
	if (ret)
		dev_err(dev, "pm_clk_suspend() returns %d\n", ret);
	dev_dbg(dev, "Exit %s\n", __func__);
	return ret;
}

static int rtk_uio_runtime_resume(struct device *dev)
{
	int ret = 0;

	dev_dbg(dev, "Enter %s\n", __func__);
	ret = pm_clk_resume(dev);
	if (ret)
		dev_err(dev, "pm_clk_resume() returns %d\n", ret);
	dev_dbg(dev, "Exit %s\n", __func__);
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
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(rtk_uio_ids),
		.pm = &rtk_uio_dev_pm_ops,
	},
};
module_platform_driver(rtk_uio_driver);

MODULE_AUTHOR("Cheng-Yu Lee");
MODULE_DESCRIPTION("Realtek Generic UIO driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);

