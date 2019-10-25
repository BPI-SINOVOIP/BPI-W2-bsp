/*
 * Realtek DCSYS driver
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
#include <linux/mm.h>
#include <soc/realtek/perfcnt.h>
#include <soc/realtek/dcsys.h>
#include "include/rtk_dcsys.h"

struct dcsys_perfcnt_desc {
	u32 type;
	u32 conf_off;
	u32 conf_mask;
	u32 data_off;
};

#define DCSYS_PERFCNT_DESC_TOTAL(_id)                                 \
{                                                                     \
	.data_off = DCSYS_PC_TOTA_MON_NUM_ ## _id,                    \
}
#define DCSYS_PERFCNT_DESC_SYSH(_id)                                  \
{                                                                     \
	.conf_off = DCSYS_PC_SYSH_PROG_ ## _id ## _CTRL,              \
	.conf_mask = DCSYS_PC_SYSH_PROG_ ## _id ## _CTRL_MASK,        \
	.data_off = DCSYS_PC_SYSH_PROG_ ## _id ## _ACC_LAT,           \
}
#define DCSYS_PERFCNT_DESC_SYS(_id)                                   \
{                                                                     \
	.conf_off = DCSYS_PC_SYS_PROG_ ## _id ## _CTRL,               \
	.conf_mask = DCSYS_PC_SYS_PROG_ ## _id ## _CTRL_MASK,         \
	.data_off = DCSYS_PC_SYS_PROG_ ## _id ## _ACC_LAT,            \
}

static const struct dcsys_perfcnt_desc pcdev_descs[] = {
	[DCSYS_PERFCNT_ID_TOTAL_0] = DCSYS_PERFCNT_DESC_TOTAL(0),
	[DCSYS_PERFCNT_ID_TOTAL_1] = DCSYS_PERFCNT_DESC_TOTAL(1),
	[DCSYS_PERFCNT_ID_SYSH_0]  = DCSYS_PERFCNT_DESC_SYSH(0),
	[DCSYS_PERFCNT_ID_SYSH_1]  = DCSYS_PERFCNT_DESC_SYSH(1),
	[DCSYS_PERFCNT_ID_SYSH_2]  = DCSYS_PERFCNT_DESC_SYSH(2),
	[DCSYS_PERFCNT_ID_SYSH_3]  = DCSYS_PERFCNT_DESC_SYSH(3),
	[DCSYS_PERFCNT_ID_SYSH_4]  = DCSYS_PERFCNT_DESC_SYSH(4),
	[DCSYS_PERFCNT_ID_SYSH_5]  = DCSYS_PERFCNT_DESC_SYSH(5),
	[DCSYS_PERFCNT_ID_SYSH_6]  = DCSYS_PERFCNT_DESC_SYSH(6),
	[DCSYS_PERFCNT_ID_SYSH_7]  = DCSYS_PERFCNT_DESC_SYSH(7),
	[DCSYS_PERFCNT_ID_SYS_0]   = DCSYS_PERFCNT_DESC_SYS(0),
	[DCSYS_PERFCNT_ID_SYS_1]   = DCSYS_PERFCNT_DESC_SYS(1),
	[DCSYS_PERFCNT_ID_SYS_2]   = DCSYS_PERFCNT_DESC_SYS(2),
};

struct dcsys_device {
	struct miscdevice     mdev;
	struct perfcnt_device pcdev;
	const struct dcsys_perfcnt_desc
	                      *desc;
	struct device         *dev;

	void                  *internal_addr;
	phys_addr_t           addr;
	resource_size_t       size;
	u32                   open_cnt;
	struct mutex          lock;
};

static u32 dcsys_read(struct dcsys_device *dcdev, u32 offset)
{
	u32 val;

	val = readl(dcdev->internal_addr + offset);
	dev_dbg(dcdev->dev, "%s: off=%03x, val=%08x\n", __func__, offset, val);
	return val;
}

static void dcsys_write(struct dcsys_device *dcdev, u32 offset, u32 val)
{
	dev_dbg(dcdev->dev, "%s: off=%03x, val=%08x\n", __func__, offset, val);
	writel(val, dcdev->internal_addr + offset);
}

static void dcsys_update_bits(struct dcsys_device *dcdev,
			      u32 offset,
			      u32 mask,
			      u32 val)
{
	u32 rval;

	dev_dbg(dcdev->dev, "%s: off=%03x, mask=%08x, val=%08x\n", __func__,
		offset, mask, val);
	rval = readl(dcdev->internal_addr + offset);
	rval = (rval & ~mask) | (val & mask);
	writel(rval, dcdev->internal_addr + offset);
}


static int dcsys_perfcnt_start(struct perfcnt_device *pcdev)
{
	struct dcsys_device *dcdev = container_of(pcdev, struct dcsys_device, pcdev);

	dcsys_write(dcdev, DCSYS_PC_CTRL, 0);
	dcsys_write(dcdev, DCSYS_PC_CTRL, 1);
	return 0;
}

static int dcsys_perfcnt_stop(struct perfcnt_device *pcdev)
{
	struct dcsys_device *dcdev = container_of(pcdev, struct dcsys_device, pcdev);

	dcsys_write(dcdev, DCSYS_PC_CTRL, 0);
	return 0;
}

static int dcsys_perfcnt_reset(struct perfcnt_device *pcdev)
{
	struct dcsys_device *dcdev = container_of(pcdev, struct dcsys_device, pcdev);

	dcsys_write(dcdev, DCSYS_PC_CTRL, 0);
	return 0;
}

static int dcsys_perfcnt_set_conf(struct perfcnt_device *pcdev, u32 id, u32 conf)
{
	struct dcsys_device *dcdev = container_of(pcdev, struct dcsys_device, pcdev);
	const struct dcsys_perfcnt_desc *d = &dcdev->desc[id];

	switch (id) {
	default:
		return -EINVAL;
	case DCSYS_PERFCNT_ID_SYSH_0 ... DCSYS_PERFCNT_ID_SYSH_7:
	case DCSYS_PERFCNT_ID_SYS_0 ... DCSYS_PERFCNT_ID_SYS_2:
		break;
	}
	dcsys_update_bits(dcdev, d->conf_off, d->conf_mask, conf << (ffs(d->conf_mask) - 1));
	return 0;
}

static int dcsys_perfcnt_get_data(struct perfcnt_device *pcdev, u32 id, struct perfcnt_data *data)
{
	struct dcsys_device *dcdev = container_of(pcdev, struct dcsys_device, pcdev);
	const struct dcsys_perfcnt_desc *d = &dcdev->desc[id];
	u32 size = 0;
	int i;

	switch (id) {
	case DCSYS_PERFCNT_ID_TOTAL_0:
	case DCSYS_PERFCNT_ID_TOTAL_1:
		size = 3;
		break;
	case DCSYS_PERFCNT_ID_SYSH_0 ... DCSYS_PERFCNT_ID_SYSH_7:
	case DCSYS_PERFCNT_ID_SYS_0 ... DCSYS_PERFCNT_ID_SYS_2:
		size = 4;
		break;
	}

	for (i = 0; i < size; i++)
		data->data[i] = dcsys_read(dcdev, d->data_off + i * 4);
	return 0;
}

static const struct perfcnt_ops dcsys_prefcnt_ops = {
	.start    = dcsys_perfcnt_start,
	.stop     = dcsys_perfcnt_stop,
	.reset    = dcsys_perfcnt_reset,
	.set_conf = dcsys_perfcnt_set_conf,
	.get_data = dcsys_perfcnt_get_data,
};

static int dcsys_open(struct inode *inode, struct file *filp)
{
	struct dcsys_device *dcdev = container_of(filp->private_data,
		struct dcsys_device, mdev);

	mutex_lock(&dcdev->lock);
	if (dcdev->open_cnt != 0) {
		mutex_unlock(&dcdev->lock);
		return -EBUSY;
	}

	dcdev->open_cnt = 1;
	perfcnt_suspend(&dcdev->pcdev);
	mutex_unlock(&dcdev->lock);
	return 0;
}

static int dcsys_release(struct inode *inode, struct file *filp)
{
	struct dcsys_device *dcdev = container_of(filp->private_data,
		struct dcsys_device, mdev);

	mutex_lock(&dcdev->lock);
	dcdev->open_cnt = 0;
	perfcnt_resume(&dcdev->pcdev);
	mutex_unlock(&dcdev->lock);
	return 0;
}

static const struct vm_operations_struct dcsys_vm_ops = {
#ifdef CONFIG_HAVE_IOREMAP_PROT
	.access = generic_access_phys,
#endif
};

static int dcsys_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct dcsys_device *dcdev = container_of(filp->private_data,
		struct dcsys_device, mdev);

	if (vma->vm_end < vma->vm_start)
		return -EINVAL;

	if (dcdev->addr & ~PAGE_MASK)
		return -EINVAL;

	if (vma->vm_end - vma->vm_start > dcdev->size)
		return -EINVAL;

	if (vma->vm_pgoff > (dcdev->size >> PAGE_SHIFT))
		return -EINVAL;

	vma->vm_ops = &dcsys_vm_ops;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	return remap_pfn_range(vma,
			       vma->vm_start,
			       dcdev->addr >> PAGE_SHIFT,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
}


static const struct file_operations dcsys_fops = {
	.owner         = THIS_MODULE,
	.open          = dcsys_open,
	.release       = dcsys_release,
	.mmap          = dcsys_mmap,
};

static int dcsys_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct dcsys_device *dcdev;
	struct resource res;
	int ret;

	dcdev = devm_kzalloc(dev, sizeof(*dcdev), GFP_KERNEL);
	if (!dcdev)
		return -ENOMEM;

	ret = of_address_to_resource(np, 0, &res);
	if (ret) {
		dev_err(dev, "of_address_to_resource() returns %d\n", ret);
		return ret;
	}

	mutex_init(&dcdev->lock);
        dcdev->addr = res.start;
	dcdev->size = ALIGN(resource_size(&res), PAGE_SIZE);
	dcdev->internal_addr = devm_ioremap(dev, res.start, resource_size(&res));
	if (!dcdev->internal_addr) {
		dev_err(dev, "ioremap() returns NULL\n");
		return -ENOMEM;
	}

	dcdev->desc   = pcdev_descs;
	dcdev->pcdev.dev = dev;
	dcdev->pcdev.np  = np;
	dcdev->pcdev.ops = &dcsys_prefcnt_ops;
	ret = perfcnt_register(&dcdev->pcdev);
	if (ret) {
		dev_err(dev, "perfcnt_register() returns %d\n", ret);
		return ret;
	}

	dcdev->mdev.minor  = MISC_DYNAMIC_MINOR;
	dcdev->mdev.name   = "dcsys";
	dcdev->mdev.fops   = &dcsys_fops;
	dcdev->mdev.parent = dev;
	ret = misc_register(&dcdev->mdev);
	if (ret) {
		dev_err(dev, "misc_register() returns %d\n", ret);
		goto error;
	}

	platform_set_drvdata(pdev, dcdev);
	dev_info(dev, "initialized\n");
	return 0;
error:
	perfcnt_unregister(&dcdev->pcdev);
	return ret;
}

static int dcsys_remove(struct platform_device *pdev)
{
	struct dcsys_device *dcdev = platform_get_drvdata(pdev);

	misc_deregister(&dcdev->mdev);
	dev_info(dev, "removed\n");
	return 0;
}

static const struct of_device_id dcsys_ids[] = {
	{ .compatible = "realtek,dcsys", },
	{}
};

static struct platform_driver dcsys_driver = {
	.probe  = dcsys_probe,
	.remove = dcsys_remove,
	.driver = {
		.owner = THIS_MODULE,
		.name   = "rtk-dcsys",
		.of_match_table = dcsys_ids,
	},
};
module_platform_driver(dcsys_driver);

