/*
 * UIO Interface of Realtek DCSYS Performance Counter
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define pr_fmt(fmt) "dcsys: uio: " fmt

#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/uio_driver.h>
#include <soc/realtek/rtk_dc_sys_pc.h>

struct dcsys_priv {
	struct uio_info *info;
	struct dcsys_pc *pc;
	atomic_t usage;
};

#define to_dinfo(_info) container_of(_info, struct dcsys_priv, info);

static int dcsys_open(struct uio_info *info, struct inode *inode)
{
	struct dcsys_priv *priv = info->priv;

	pr_debug("%s\n", __func__);

	if (atomic_read(&priv->usage))
		return -EBUSY;

	atomic_set(&priv->usage, 1);

	dcsys_pc_set_owner(priv->pc, DCSYS_PC_FORCE_SET);

	return 0;
}

static int dcsys_release(struct uio_info *info, struct inode *inode)
{
	struct dcsys_priv *priv = info->priv;

	pr_debug("%s\n", __func__);

	dcsys_pc_clear_owner(priv->pc);
	atomic_set(&priv->usage, 0);

	return 0;
}

static int dcsys_uio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device *parent = dev->parent;
	struct device_node *parent_np = parent->of_node;
	int ret;
	struct resource res;
	struct dcsys_priv *priv;
	struct uio_info *info;

	dev_info(dev, "[DCSYS-UIO] %s\n", __func__);

	info = devm_kzalloc(dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->pc = dcsys_pc_simple_get(dev);
	if (!priv->pc)
		return -EPROBE_DEFER;

	ret = of_address_to_resource(parent_np, 0, &res);
	if (ret) {
		dev_err(dev, "failed to get resource from parent\n");
		goto error;
	}

	info->mem[0].addr = res.start;
	info->mem[0].size = ALIGN(resource_size(&res), PAGE_SIZE);
	info->mem[0].memtype = UIO_MEM_PHYS;

	info->version = "0.0.1";
	info->name    = "rtk-dcsys";
	info->open    = dcsys_open;
	info->release = dcsys_release;
	info->priv    = priv;

	priv->info    = info;
	atomic_set(&priv->usage, 0);

	ret = uio_register_device(dev, info);
	if (ret) {
		dev_err(dev, "failed to register uio device\n");
		goto error;
	}

	platform_set_drvdata(pdev, info);

	return 0;

error:
	dcsys_pc_put(priv->pc);
	return ret;

}

static int dcsys_uio_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct uio_info *info = platform_get_drvdata(pdev);
	struct dcsys_priv *priv = info->priv;

	dev_info(dev, "[DCSYS-UIO] %s\n", __func__);

	uio_unregister_device(info);
	dcsys_pc_put(priv->pc);
	platform_set_drvdata(pdev, NULL);
	kfree(info);

	return 0;
}

static const struct of_device_id dcsys_uio_ids[] = {
	{ .compatible = "realtek,dcsys-pc-uio" },
	{}
};

static struct platform_driver dcsys_uio_driver = {
	.probe		= dcsys_uio_probe,
	.remove		= dcsys_uio_remove,
	.driver		= {
		.name	= "rtk-dcsys:uio",
		.owner	= THIS_MODULE,
		.of_match_table = dcsys_uio_ids,
	},
};

static int __init dcsys_uio_init(void)
{
	return platform_driver_register(&dcsys_uio_driver);
}
late_initcall(dcsys_uio_init);

