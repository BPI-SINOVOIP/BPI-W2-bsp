/*
 * Realtek DMC driver
 *
 * Copyright (C) 2017-2019 Realtek Semiconductor Corporation
 * Copyright (C) 2017-2019 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/io.h>
#include <linux/jiffies.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <soc/realtek/perfcnt.h>
#include <soc/realtek/dmc.h>
#include "include/rtk_dmc.h"

struct dmc_device {
	struct miscdevice     mdev;
	struct perfcnt_device pcdev;
	struct device         *dev;

	void                  *base;
	u32                   open_cnt;
	struct mutex          lock;

	int                   sysfs_reg;
};

static DEFINE_SPINLOCK(dmc_lock);

static u32 dmc_read(struct dmc_device *dmcdev, u32 offset)
{
	u32 val;
	unsigned long flags;

	spin_lock_irqsave(&dmc_lock, flags);
	writel(offset, dmcdev->base + DMC_SCH_INDEX);
	val = readl(dmcdev->base + DMC_SCH_DATA);
	spin_unlock_irqrestore(&dmc_lock, flags);

	dev_dbg(dmcdev->dev, "%s: off=%03x, val=%08x\n", __func__, offset, val);
	return val;
}

static void dmc_write(struct dmc_device *dmcdev, u32 offset, u32 val)
{
	unsigned long flags;

	dev_dbg(dmcdev->dev, "%s: off=%03x, val=%08x\n", __func__, offset, val);

	spin_lock_irqsave(&dmc_lock, flags);
	writel(offset, dmcdev->base + DMC_SCH_INDEX);
	writel(val, dmcdev->base + DMC_SCH_DATA);
	spin_unlock_irqrestore(&dmc_lock, flags);
}

static int dmc_perfcnt_start(struct perfcnt_device *pcdev)
{
	struct dmc_device *dmcdev = container_of(pcdev, struct dmc_device, pcdev);

	dmc_write(dmcdev, DMC_PC_CTRL, 0x2);
	dmc_write(dmcdev, DMC_PC_CTRL, 0x1);
	return 0;
}

static int dmc_perfcnt_stop(struct perfcnt_device *pcdev)
{
	struct dmc_device *dmcdev = container_of(pcdev, struct dmc_device, pcdev);

	dmc_write(dmcdev, DMC_PC_CTRL, 0x0);
	return 0;
}

static int dmc_perfcnt_reset(struct perfcnt_device *pcdev)
{
	struct dmc_device *dmcdev = container_of(pcdev, struct dmc_device, pcdev);

	dmc_write(dmcdev, DMC_PC_CTRL, 0x2);
	dmc_write(dmcdev, DMC_PC_CTRL, 0x0);
	return 0;
}

static int dmc_perfcnt_get_data(struct perfcnt_device *pcdev, u32 id, struct perfcnt_data *data)
{
	struct dmc_device *dmcdev = container_of(pcdev, struct dmc_device, pcdev);

	switch (id) {
	case DMC_PERFCNT_ID_CPU:
		data->data[0] = dmc_read(dmcdev, DMC_PC_CPU_REQ_NUM);
		data->data[1] = dmc_read(dmcdev, DMC_PC_CPU_ACC_LAT);
		break;

	case DMC_PERFCNT_ID_GPU:
		data->data[0] = dmc_read(dmcdev, DMC_PC_GPU_REQ_NUM);
		data->data[1] = dmc_read(dmcdev, DMC_PC_GPU_ACC_LAT);
		break;
	}
	return 0;
}

static const struct perfcnt_ops dmc_prefcnt_ops = {
	.start    = dmc_perfcnt_start,
	.stop     = dmc_perfcnt_stop,
	.reset    = dmc_perfcnt_reset,
	.get_data = dmc_perfcnt_get_data,
};

static int dmc_open(struct inode *inode, struct file *filp)
{
	struct dmc_device *dmcdev = container_of(filp->private_data,
		struct dmc_device, mdev);

	mutex_lock(&dmcdev->lock);
	if (dmcdev->open_cnt != 0) {
		mutex_unlock(&dmcdev->lock);
		return -EBUSY;
	}

	dmcdev->open_cnt = 1;
	perfcnt_suspend(&dmcdev->pcdev);
	mutex_unlock(&dmcdev->lock);
	return 0;
}

static int dmc_release(struct inode *inode, struct file *filp)
{
	struct dmc_device *dmcdev = container_of(filp->private_data,
		struct dmc_device, mdev);

	mutex_lock(&dmcdev->lock);
	dmcdev->open_cnt = 0;
	perfcnt_resume(&dmcdev->pcdev);
	mutex_unlock(&dmcdev->lock);
	return 0;
}

struct dmc_rw_data {
	u32 reg;
	u32 val;
};

#define DMC_IOCTL_REG_READ    _IOWR(0xD3, 0x1, struct dmc_rw_data)
#define DMC_IOCTL_REG_WRITE   _IOW(0xD3, 0x02, struct dmc_rw_data)
static long dmc_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct dmc_device *dmcdev = container_of(filp->private_data,
	                struct dmc_device, mdev);
	struct dmc_rw_data d;

	if (copy_from_user(&d, (int __user *)arg, sizeof(d)))
		return -EFAULT;

	if (!dmc_valid_reg(d.reg))
		return -EINVAL;

	switch (cmd)
	{
	case DMC_IOCTL_REG_READ:
		d.val = dmc_read(dmcdev, d.reg);
		if (copy_to_user((int __user *)arg, &d, sizeof(d)))
			return -EFAULT;
		break;
	case DMC_IOCTL_REG_WRITE:
		dmc_write(dmcdev, d.reg, d.val);
		break;
	}
	return 0;
}

static long dmc_compact_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	dmc_ioctl(filp, cmd, arg);
	return 0;
}

static const struct file_operations dmc_fops = {
	.owner         = THIS_MODULE,
	.open          = dmc_open,
	.release       = dmc_release,
	.compat_ioctl  = dmc_compact_ioctl,
	.unlocked_ioctl = dmc_ioctl,
};

static ssize_t reg_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct dmc_device *dmcdev = dev_get_drvdata(dev);
	int ret;
	unsigned int val;

	ret = kstrtouint(buf, 0, &val);
	if (ret)
		return ret;

	if (!dmc_valid_reg(val))
		return -EINVAL;

	dmcdev->sysfs_reg = val;
	return count;
}

static ssize_t reg_show(struct device *dev, struct device_attribute *attr, char * const buf)
{
	struct dmc_device *dmcdev = dev_get_drvdata(dev);

	if (!dmc_valid_reg(dmcdev->sysfs_reg))
		return -EINVAL;

	return scnprintf(buf, PAGE_SIZE, "0x%2x\n", dmcdev->sysfs_reg);
}
static DEVICE_ATTR(reg, 0644, reg_show, reg_store);

static ssize_t reg_val_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct dmc_device *dmcdev = dev_get_drvdata(dev);
	int ret;
	unsigned int val;

	if (!dmc_valid_reg(dmcdev->sysfs_reg))
		return -EINVAL;

	ret = kstrtouint(buf, 0, &val);
	if (ret)
		return ret;

	dmc_write(dmcdev, dmcdev->sysfs_reg, val);
	return count;
}

static ssize_t reg_val_show(struct device *dev, struct device_attribute *attr, char * const buf)
{
	struct dmc_device *dmcdev = dev_get_drvdata(dev);

	if (!dmc_valid_reg(dmcdev->sysfs_reg))
		return -EINVAL;

	return scnprintf(buf, PAGE_SIZE, "0x%08x\n", dmc_read(dmcdev, dmcdev->sysfs_reg));
}
static DEVICE_ATTR(reg_val, 0644, reg_val_show, reg_val_store);

static struct attribute *dmc_attrs[] = {
	&dev_attr_reg.attr,
	&dev_attr_reg_val.attr,
	NULL
};

static const struct attribute_group dmc_attr_group = {
	.attrs = dmc_attrs,
};

static int dmc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct dmc_device *dmcdev;
	struct resource res;
	int ret;

	dmcdev = devm_kzalloc(dev, sizeof(*dmcdev), GFP_KERNEL);
	if (!dmcdev)
		return -ENOMEM;

	ret = of_address_to_resource(np, 0, &res);
	if (ret) {
		dev_err(dev, "of_address_to_resource() returns %d\n", ret);
		return ret;
	}

	mutex_init(&dmcdev->lock);
	dmcdev->base = devm_ioremap(dev, res.start, resource_size(&res));
	if (!dmcdev->base) {
		dev_err(dev, "ioremap() returns NULL\n");
		return -ENOMEM;
	}

	ret = sysfs_create_group(&dev->kobj, &dmc_attr_group);
	if (ret) {
		dev_err(dev, "sysfs_create_group() returns %d\n", ret);
		return ret;
	}

	dmcdev->pcdev.dev = dev;
	dmcdev->pcdev.np  = np;
	dmcdev->pcdev.ops = &dmc_prefcnt_ops;
	ret = perfcnt_register(&dmcdev->pcdev);
	if (ret) {
		dev_err(dev, "perfcnt_register() returns %d\n", ret);
		goto remove_sysfs;
	}

	dmcdev->mdev.minor  = MISC_DYNAMIC_MINOR;
	dmcdev->mdev.name   = "dmc";
	dmcdev->mdev.fops   = &dmc_fops;
	dmcdev->mdev.parent = dev;
	ret = misc_register(&dmcdev->mdev);
	if (ret) {
		dev_err(dev, "misc_register() returns %d\n", ret);
		goto unregister_prefcnt;
	}

	platform_set_drvdata(pdev, dmcdev);
	dev_info(dev, "initialized\n");
	return 0;

unregister_prefcnt:
	perfcnt_unregister(&dmcdev->pcdev);
remove_sysfs:
	sysfs_remove_group(&dev->kobj, &dmc_attr_group);
	return ret;
}

static int dmc_remove(struct platform_device *pdev)
{
	struct dmc_device *dmcdev = platform_get_drvdata(pdev);
	struct device *dev = &pdev->dev;

	misc_deregister(&dmcdev->mdev);
	perfcnt_unregister(&dmcdev->pcdev);
	sysfs_remove_group(&dev->kobj, &dmc_attr_group);
	dev_info(dev, "removed\n");
	return 0;
}

static const struct of_device_id dmc_ids[] = {
	{ .compatible = "realtek,dmc", },
	{}
};

static struct platform_driver dmc_driver = {
	.probe  = dmc_probe,
	.remove = dmc_remove,
	.driver = {
		.owner = THIS_MODULE,
		.name   = "rtk-dmc",
		.of_match_table = dmc_ids,
	},
};
module_platform_driver(dmc_driver);

