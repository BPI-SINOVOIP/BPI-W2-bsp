/*
 * Realtek Demod Driver
 *
 * Copyright (C) 2018-2019 Realtek Semiconductor Corp.
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

struct rtk_demod_device {
	struct miscdevice     mdev;
	struct device         *dev;
	/* pm */
	atomic_t              open_cnt;
	struct clk            *pll;
	struct clk            *clk;
	struct reset_control  *rstc;

	/* map */
	void                  *internal_addr;
	phys_addr_t           addr;
	resource_size_t       size;
};

struct rtk_demod_ctx {
	struct rtk_demod_device *dmdev;
};

static int rtk_demod_open(struct inode *inode, struct file *filp)
{
	struct rtk_demod_device *dmdev = container_of(filp->private_data,
						      struct rtk_demod_device,
						      mdev);
	struct rtk_demod_ctx *ctx;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;
	ctx->dmdev = dmdev;
	filp->private_data = ctx;

	atomic_inc(&dmdev->open_cnt);
	pm_runtime_get_sync(dmdev->dev);

	return 0;
}

static int rtk_demod_release(struct inode *inode, struct file *filp)
{
	struct rtk_demod_ctx *ctx = filp->private_data;
	struct rtk_demod_device *dmdev = ctx->dmdev;

	pm_runtime_put_sync(dmdev->dev);
	atomic_dec(&dmdev->open_cnt);
	kfree(ctx);
	return 0;
}

static const struct vm_operations_struct rtk_demod_vm_ops = {
#ifdef CONFIG_HAVE_IOREMAP_PROT
	.access = generic_access_phys,
#endif
};

static int rtk_demod_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct rtk_demod_ctx *ctx = filp->private_data;
	struct rtk_demod_device *dmdev = ctx->dmdev;

	if (vma->vm_end < vma->vm_start)
		return -EINVAL;

	if (dmdev->addr & ~PAGE_MASK)
		return -EINVAL;

	if (vma->vm_end - vma->vm_start > dmdev->size)
		return -EINVAL;

	if (vma->vm_pgoff > (dmdev->size >> PAGE_SHIFT))
		return -EINVAL;

	vma->vm_ops  = &rtk_demod_vm_ops;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	return remap_pfn_range(vma,
			       vma->vm_start,
			       dmdev->addr >> PAGE_SHIFT,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
}


static const struct file_operations rtk_demod_fops = {
	.owner         = THIS_MODULE,
	.open          = rtk_demod_open,
	.release       = rtk_demod_release,
	.mmap          = rtk_demod_mmap,
};

static void rtk_demod_power_on(struct rtk_demod_device *dmdev)
{
	clk_prepare_enable(dmdev->clk);
	clk_prepare_enable(dmdev->pll);
	reset_control_deassert(dmdev->rstc);
}

static void rtk_demod_power_off(struct rtk_demod_device *dmdev)
{
	 reset_control_assert(dmdev->rstc);
	 clk_disable_unprepare(dmdev->clk);
	 clk_disable_unprepare(dmdev->pll);
}

static int rtk_demod_runtime_resume(struct device *dev)
{
	struct rtk_demod_device *dmdev = dev_get_drvdata(dev);

	dev_dbg(dev, "enter %s\n", __func__);
	rtk_demod_power_on(dmdev);
	dev_dbg(dev, "Exit %s\n", __func__);
	return 0;
}

static int rtk_demod_runtime_suspend(struct device *dev)
{
	struct rtk_demod_device *dmdev = dev_get_drvdata(dev);

	dev_dbg(dev, "enter %s\n", __func__);
	rtk_demod_power_off(dmdev);
	dev_dbg(dev, "Exit %s\n", __func__);
	return 0;
}

static int rtk_demod_resume(struct device *dev)
{
	struct rtk_demod_device *dmdev = dev_get_drvdata(dev);

	if (atomic_read(&dmdev->open_cnt) == 0)
		return 0;

	dev_info(dev, "enter %s\n", __func__);
	rtk_demod_power_on(dmdev);
	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static int rtk_demod_suspend(struct device *dev)
{
	struct rtk_demod_device *dmdev = dev_get_drvdata(dev);

	if (atomic_read(&dmdev->open_cnt) == 0)
		return 0;

	dev_info(dev, "enter %s\n", __func__);
	rtk_demod_power_off(dmdev);
	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static const struct dev_pm_ops rtk_demod_pm_ops = {
	.runtime_suspend = rtk_demod_runtime_suspend,
	.runtime_resume  = rtk_demod_runtime_resume,
	.suspend         = rtk_demod_suspend,
	.resume          = rtk_demod_resume,
};

static int rtk_demod_probe(struct platform_device *pdev)
{
	struct rtk_demod_device *dmdev;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int ret;
	struct resource res;

	dmdev = devm_kzalloc(dev, sizeof(*dmdev), GFP_KERNEL);
	if (!dmdev)
		return -ENOMEM;

	dmdev->dev = dev;

	dmdev->clk = devm_clk_get(dev, "cablerx");
	if (IS_ERR(dmdev->clk)) {
		ret = PTR_ERR(dmdev->clk);
		dev_err(dev, "cablerx: failed to get clk: %d\n", ret);
		return ret;
	}

	dmdev->pll = devm_clk_get(dev, "pll");
	if (IS_ERR(dmdev->pll)) {
		ret = PTR_ERR(dmdev->pll);
		dev_err(dev, "pll: failed to get clk: %d\n", ret);
		return ret;
	}

	dmdev->rstc = devm_reset_control_get(dev, NULL);
	if (IS_ERR(dmdev->rstc)) {
		ret = PTR_ERR(dmdev->rstc);
		dev_err(dev, "failed to get reset_control: %d\n", ret);
		return ret;
	}

	ret = of_address_to_resource(np, 0, &res);
	if (ret) {
		dev_err(dev, "failed to get address: %d\n", ret);
		return ret;
	}

	atomic_set(&dmdev->open_cnt, 0);

	dmdev->addr = res.start;
	dmdev->size = ALIGN(resource_size(&res), PAGE_SIZE);
	dmdev->internal_addr = devm_ioremap(dev, res.start,
		resource_size(&res));
	if (!dmdev->internal_addr) {
		dev_err(dev, "failed to ioremap\n");
		return -ENOMEM;
	}

	dmdev->mdev.minor  = MISC_DYNAMIC_MINOR;
	dmdev->mdev.name   = "demod";
	dmdev->mdev.fops   = &rtk_demod_fops;
	dmdev->mdev.parent = dev;
	ret = misc_register(&dmdev->mdev);
	if (ret) {
		dev_err(dev, "failed to register misc device: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, dmdev);
	pm_runtime_set_suspended(dev);
	pm_runtime_enable(dev);
	dev_info(dev, "initialized\n");
	return 0;
}

static int rtk_demod_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rtk_demod_device *dmdev = platform_get_drvdata(pdev);

	pm_runtime_disable(dev);
	platform_set_drvdata(pdev, NULL);
	misc_deregister(&dmdev->mdev);
	dev_info(dev, "removed\n");
	return 0;
}


static const struct of_device_id rtk_demod_ids[] = {
	{ .compatible = "realtek,demod" },
	{}
};

static struct platform_driver rtk_demod_driver = {
	.probe = rtk_demod_probe,
	.remove = rtk_demod_remove,
	.driver = {
		.owner = THIS_MODULE,
		.name = "rtk-demod",
		.of_match_table = rtk_demod_ids,
		.pm = &rtk_demod_pm_ops,
	},
};
module_platform_driver(rtk_demod_driver);
