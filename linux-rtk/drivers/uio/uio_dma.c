/*
 * uio_dma.c - create a static dma buffer form uio
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/uio_driver.h>

#include "uio_helper.h"

struct uio_dma_data {
	struct device *dev;
};

static int uio_dma_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct uio_dma_data *priv;
	struct uio_info *info;
	int dma_size;
	int ret;

	dev_info(dev, "%s\n", __func__);

	info = devm_kzalloc(dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	ret = of_property_read_u32(np, "uio,dma-size", &dma_size);
	if (ret) {
		dev_err(dev, "failed to read dma-size from dt\n");
		return ret;
	}

	platform_set_drvdata(pdev, info);

	ret = uio_mem_dma_alloc(dev, &info->mem[0], dma_size,
		GFP_KERNEL | GFP_DMA);
	if (ret)
		return ret;

	priv->dev     = dev;
	info->version = "0.0.1";
	info->name    = np->name;
	info->priv    = priv;

	ret = uio_register_device(dev, info);
	if (ret) {
		dev_err(dev, "uio_register_device() returns %d\n", ret);
		goto free_dma;
	}

	return 0;

free_dma:
	uio_mem_dma_free(dev, &info->mem[0]);

	return ret;
}

static int uio_dma_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct uio_info *info = platform_get_drvdata(pdev);

	dev_info(dev, "%s\n", __func__);

	uio_unregister_device(info);
	uio_mem_dma_free(dev, &info->mem[0]);
	return 0;
}


static const struct of_device_id uio_dma_ids[] = {
	{ .compatible = "dma-uio" },
	{}
};

static struct platform_driver uio_dma_driver = {
	.probe = uio_dma_probe,
	.remove = uio_dma_remove,
	.driver = {
		.name = "uio-dma",
		.owner = THIS_MODULE,
		.of_match_table = uio_dma_ids,
	},
};
module_platform_driver_probe(uio_dma_driver, uio_dma_probe);
