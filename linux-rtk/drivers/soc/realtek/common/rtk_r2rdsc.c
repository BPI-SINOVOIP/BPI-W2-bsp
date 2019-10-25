/*
 * Realtek R2RDSC Driver
 *
 * Copyright (C) 2019 Realtek Semiconductor Corp.
 *
 * Author:
 *   Cheng-Yu Lee <cylee12@realtek.com>
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
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/clk.h>
#include <linux/reset.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/list.h>
#include <linux/pm_runtime.h>
#include <linux/mm.h>

struct rtk_r2rdsc_device {
	struct miscdevice     mdev;
	struct device         *dev;
	/* pm */
	atomic_t              open_cnt;

	struct clk            *clk_r2rdsc;
	struct reset_control  *rstc_r2rdsc;

	/* map */
	void                  *base_r2rdsc;
	phys_addr_t           addr_r2rdsc;
	resource_size_t       size_r2rdsc;
};

struct rtk_r2rdsc_ctx {
	struct rtk_r2rdsc_device *rrdev;
};

static int rtk_r2rdsc_open(struct inode *inode, struct file *filp)
{
	struct rtk_r2rdsc_device *rrdev = container_of(filp->private_data,
						      struct rtk_r2rdsc_device,
						      mdev);
	struct rtk_r2rdsc_ctx *ctx;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;
	ctx->rrdev = rrdev;
	filp->private_data = ctx;

	atomic_inc(&rrdev->open_cnt);
	pm_runtime_get_sync(rrdev->dev);

	return 0;
}

static int rtk_r2rdsc_release(struct inode *inode, struct file *filp)
{
	struct rtk_r2rdsc_ctx *ctx = filp->private_data;
	struct rtk_r2rdsc_device *rrdev = ctx->rrdev;

	pm_runtime_put_sync(rrdev->dev);
	atomic_dec(&rrdev->open_cnt);
	kfree(ctx);
	return 0;
}

static const struct vm_operations_struct rtk_r2rdsc_vm_ops = {
#ifdef CONFIG_HAVE_IOREMAP_PROT
	.access = generic_access_phys,
#endif
};

static int rtk_r2rdsc_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct rtk_r2rdsc_ctx *ctx = filp->private_data;
	struct rtk_r2rdsc_device *rrdev = ctx->rrdev;
	phys_addr_t addr;
	resource_size_t size;


	if (vma->vm_end < vma->vm_start)
		return -EINVAL;

	addr = rrdev->addr_r2rdsc;
	size = rrdev->size_r2rdsc;

	if (addr & ~PAGE_MASK)
		return -EINVAL;

	if ((vma->vm_end - vma->vm_start) > size)
		return -EINVAL;

	vma->vm_ops = &rtk_r2rdsc_vm_ops;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	return remap_pfn_range(vma,
			       vma->vm_start,
			       addr >> PAGE_SHIFT,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
}


static const struct file_operations rtk_r2rdsc_fops = {
	.owner         = THIS_MODULE,
	.open          = rtk_r2rdsc_open,
	.release       = rtk_r2rdsc_release,
	.mmap          = rtk_r2rdsc_mmap,
};

static void rtk_r2rdsc_power_on(struct rtk_r2rdsc_device *rrdev)
{
	clk_prepare_enable(rrdev->clk_r2rdsc);
	reset_control_deassert(rrdev->rstc_r2rdsc);
}

static void rtk_r2rdsc_power_off(struct rtk_r2rdsc_device *rrdev)
{
	 reset_control_assert(rrdev->rstc_r2rdsc);
	 clk_disable_unprepare(rrdev->clk_r2rdsc);
}

static int rtk_r2rdsc_runtime_resume(struct device *dev)
{
	struct rtk_r2rdsc_device *rrdev = dev_get_drvdata(dev);

	dev_dbg(dev, "enter %s\n", __func__);
	rtk_r2rdsc_power_on(rrdev);
	dev_dbg(dev, "Exit %s\n", __func__);
	return 0;
}

static int rtk_r2rdsc_runtime_suspend(struct device *dev)
{
	struct rtk_r2rdsc_device *rrdev = dev_get_drvdata(dev);

	dev_dbg(dev, "enter %s\n", __func__);
	rtk_r2rdsc_power_off(rrdev);
	dev_dbg(dev, "Exit %s\n", __func__);
	return 0;
}

static int rtk_r2rdsc_resume(struct device *dev)
{
	struct rtk_r2rdsc_device *rrdev = dev_get_drvdata(dev);

	if (atomic_read(&rrdev->open_cnt) == 0)
		return 0;

	dev_info(dev, "enter %s\n", __func__);
	rtk_r2rdsc_power_on(rrdev);
	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static int rtk_r2rdsc_suspend(struct device *dev)
{
	struct rtk_r2rdsc_device *rrdev = dev_get_drvdata(dev);

	if (atomic_read(&rrdev->open_cnt) == 0)
		return 0;

	dev_info(dev, "enter %s\n", __func__);
	rtk_r2rdsc_power_off(rrdev);
	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static const struct dev_pm_ops rtk_r2rdsc_pm_ops = {
	.runtime_suspend = rtk_r2rdsc_runtime_suspend,
	.runtime_resume  = rtk_r2rdsc_runtime_resume,
	.suspend         = rtk_r2rdsc_suspend,
	.resume          = rtk_r2rdsc_resume,
};

static int rtk_r2rdsc_probe(struct platform_device *pdev)
{
	struct rtk_r2rdsc_device *rrdev;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int ret;
	struct resource res;

	rrdev = devm_kzalloc(dev, sizeof(*rrdev), GFP_KERNEL);
	if (!rrdev)
		return -ENOMEM;

	rrdev->dev = dev;

	/* get r2rdsc resources */
	rrdev->clk_r2rdsc = devm_clk_get(dev, "r2rdsc");
	if (IS_ERR(rrdev->clk_r2rdsc)) {
		ret = PTR_ERR(rrdev->clk_r2rdsc);
		dev_err(dev, "r2rdsc: failed to get clk: %d\n", ret);
		return ret;
	}

	rrdev->rstc_r2rdsc = devm_reset_control_get(dev, "r2rdsc");
	if (IS_ERR(rrdev->rstc_r2rdsc)) {
		ret = PTR_ERR(rrdev->rstc_r2rdsc);
		dev_err(dev, "failed to get reset_control: %d\n", ret);
		return ret;
	}

	ret = of_address_to_resource(np, 0, &res);
	if (ret) {
		dev_err(dev, "r2rdsc: failed to get address: %d\n", ret);
		return ret;
	}

	rrdev->addr_r2rdsc = res.start;
	rrdev->size_r2rdsc = ALIGN(resource_size(&res), PAGE_SIZE);
	rrdev->base_r2rdsc = devm_ioremap(dev, res.start, resource_size(&res));
	if (!rrdev->base_r2rdsc) {
		dev_err(dev, "r2rdsc: failed to ioremap\n");
		return -ENOMEM;
	}

	atomic_set(&rrdev->open_cnt, 0);
	rrdev->mdev.minor  = MISC_DYNAMIC_MINOR;
	rrdev->mdev.name   = "r2rdsc";
	rrdev->mdev.fops   = &rtk_r2rdsc_fops;
	rrdev->mdev.parent = dev;
	ret = misc_register(&rrdev->mdev);
	if (ret) {
		dev_err(dev, "failed to register misc device: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, rrdev);
	pm_runtime_set_suspended(dev);
	pm_runtime_enable(dev);
	dev_info(dev, "initialized\n");

	return 0;
}

static int rtk_r2rdsc_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rtk_r2rdsc_device *rrdev = platform_get_drvdata(pdev);

	pm_runtime_disable(dev);
	platform_set_drvdata(pdev, NULL);
	misc_deregister(&rrdev->mdev);
	dev_info(dev, "removed\n");
	return 0;
}


static const struct of_device_id rtk_r2rdsc_ids[] = {
	{ .compatible = "realtek,r2rdsc" },
	{}
};

static struct platform_driver rtk_r2rdsc_driver = {
	.probe = rtk_r2rdsc_probe,
	.remove = rtk_r2rdsc_remove,
	.driver = {
		.owner = THIS_MODULE,
		.name = "rtk-r2rdsc",
		.of_match_table = rtk_r2rdsc_ids,
		.pm = &rtk_r2rdsc_pm_ops,
	},
};
module_platform_driver(rtk_r2rdsc_driver);
