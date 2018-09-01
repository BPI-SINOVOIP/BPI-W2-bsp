/*
 *  Copyright (C) 2016 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include "cec.h"
#include "cec_dev.h"

int cec_device_en[2];
int *cec_device_pthis[2];

int cec_bus_match(struct device *dev, struct device_driver *drv)
{
	dev_info(dev, "bus match name = %s, drv_name = %s\n",
					dev_name(dev), drv->name);
	if (0 == strncmp(dev_name(dev), drv->name, 3))
		return 1;
	return 0;
}

#ifdef CONFIG_PM
int cec_check_device(struct device *dev)
{
	int device_en = 0;
	char device0[] = "cec0";
	char device1[] = "cec1";

	dev_info(dev, "check_device %s\n", dev_name(dev));
	if (0 == strncmp(dev_name(dev), device0, strlen(dev_name(dev))))
		device_en = cec_device_en[0];
	else if (0 == strncmp(dev_name(dev), device1, strlen(dev_name(dev))))
		device_en = cec_device_en[1];
	return device_en;
}

int cec_drv_suspend(struct device *dev)
{
	int device_en = cec_check_device(dev);

	dev_info(dev, "%s\n", __func__);
	if (device_en) {
		cec_device *p_dev = to_cec_device(dev);
		cec_driver *p_drv = to_cec_driver(dev->driver);

		return (p_drv->suspend) ? p_drv->suspend(p_dev) : 0;
	} else {
		dev_err(dev, "%s not implement yet !!\n", dev_name(dev));
		return 0;
	}
}

void cec_bus_shutdown(struct device *dev)
{
	cec_drv_suspend(dev);
}

int cec_drv_resume(struct device *dev)
{
	int device_en = cec_check_device(dev);

	dev_info(dev, "%s\n", __func__);
	if (device_en) {
		cec_device *p_dev = to_cec_device(dev);
		cec_driver *p_drv = to_cec_driver(dev->driver);

		return (p_drv->resume) ? p_drv->resume(p_dev) : 0;
	} else {
		dev_err(dev, "%s not implement yet !!\n", dev_name(dev));
		return 0;
	}
}

static const struct dev_pm_ops cec_bus_pm_ops = {
	.suspend = cec_drv_suspend,
	.resume = cec_drv_resume,
};
#endif

struct bus_type cec_bus_type = {
	.name    = "cec",
	.match   = cec_bus_match,
#ifdef CONFIG_PM
	.pm      = &cec_bus_pm_ops,
	.shutdown = cec_bus_shutdown,
#endif
};

/* cec device */

void cec_device_release(struct device *dev)
{
	cec_device *p_dev = to_cec_device(dev);

	dev_info(dev, "dev %s released\n", p_dev->name);
}

int register_cec_device(cec_device *device)
{
	struct device *dev = &device->dev;

	dev_set_name(dev, device->name);
	dev->bus = &cec_bus_type;
	dev->release  = cec_device_release;

	return device_register(dev);
}
EXPORT_SYMBOL(register_cec_device);

void unregister_cec_device(cec_device *device)
{
	device_unregister(&device->dev);
}
EXPORT_SYMBOL(unregister_cec_device);

/* cec driver */
int cec_drv_probe(struct device *dev)
{
	cec_device *p_dev = to_cec_device(dev);
	cec_driver *p_drv = to_cec_driver(dev->driver);

	dev_info(dev, "probe dev %s\n", p_dev->name);

	if (!p_drv->probe)
		return -ENODEV;

	if (p_drv->probe(p_dev) == 0) {
		create_cec_dev_node(p_dev);
		return 0;
	}
	return -ENODEV;
}

int cec_drv_remove(struct device *dev)
{
	cec_device *p_dev = to_cec_device(dev);
	cec_driver *p_drv = to_cec_driver(dev->driver);

	dev_info(dev, "remove dev %s\n", p_dev->name);

	if (p_drv->remove)
		p_drv->remove(p_dev);

	create_cec_dev_node(p_dev);
	return 0;
}

void cec_drv_shutdown(struct device *dev)
{
	cec_device *p_dev = to_cec_device(dev);
	cec_driver *p_drv = to_cec_driver(dev->driver);

	dev_info(dev, "shotdown dev %s\n", p_dev->name);

	if (p_drv->enable)
		p_drv->enable(p_dev, 0);
}

int register_cec_driver(cec_driver *driver)
{
	struct device_driver *drv = &driver->drv;

	drv->name     = driver->name;
	drv->bus      = &cec_bus_type;
	drv->probe    = cec_drv_probe;
	drv->remove   = cec_drv_remove;

	pr_info("register cec driver %s (%p)\n", drv->name, drv);

	return driver_register(drv);
}
EXPORT_SYMBOL(register_cec_driver);

void unregister_cec_driver(cec_driver *driver)
{
	struct device_driver *drv = &driver->drv;

	pr_info("unregister cec driver %s (%p)\n", drv->name, &driver->drv);
	driver_unregister(&driver->drv);
}
EXPORT_SYMBOL(unregister_cec_driver);

static int __init cec_core_init(void)
{
	return bus_register(&cec_bus_type);
}

static void __exit cec_core_exit(void)
{
	bus_unregister(&cec_bus_type);
}

module_init(cec_core_init);
module_exit(cec_core_exit);
