/*
 * Realtek TP Driver
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

struct rtk_tp_device {
	struct miscdevice     mdev;
	struct device         *dev;
	/* pm */
	atomic_t              open_cnt;

	struct clk            *clk_tp;
	struct clk            *clk_tpb;
	struct reset_control  *rstc_tp;
	struct reset_control  *rstc_tpb;

	/* map */
	void                  *base_tp;
	phys_addr_t           addr_tp;
	resource_size_t       size_tp;
	void                  *base_tpb;
	phys_addr_t           addr_tpb;
	resource_size_t       size_tpb;
};

struct rtk_tp_ctx {
	struct rtk_tp_device *tpdev;
};

static int rtk_tp_open(struct inode *inode, struct file *filp)
{
	struct rtk_tp_device *tpdev = container_of(filp->private_data,
						      struct rtk_tp_device,
						      mdev);
	struct rtk_tp_ctx *ctx;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;
	ctx->tpdev = tpdev;
	filp->private_data = ctx;

	atomic_inc(&tpdev->open_cnt);
	pm_runtime_get_sync(tpdev->dev);

	return 0;
}

static int rtk_tp_release(struct inode *inode, struct file *filp)
{
	struct rtk_tp_ctx *ctx = filp->private_data;
	struct rtk_tp_device *tpdev = ctx->tpdev;

	pm_runtime_put_sync(tpdev->dev);
	atomic_dec(&tpdev->open_cnt);
	kfree(ctx);
	return 0;
}

static const struct vm_operations_struct rtk_tp_vm_ops = {
#ifdef CONFIG_HAVE_IOREMAP_PROT
	.access = generic_access_phys,
#endif
};

static int rtk_tp_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct rtk_tp_ctx *ctx = filp->private_data;
	struct rtk_tp_device *tpdev = ctx->tpdev;
	phys_addr_t addr;
	resource_size_t size;


	if (vma->vm_end < vma->vm_start)
		return -EINVAL;

	if (vma->vm_pgoff == 0) {
		addr = tpdev->addr_tp;
		size = tpdev->size_tp;
	} else if (vma->vm_pgoff == 1) {
		addr = tpdev->addr_tpb;
		size = tpdev->size_tpb;
	} else
		return -E2BIG;

	if (addr & ~PAGE_MASK)
		return -EINVAL;

	if ((vma->vm_end - vma->vm_start) > size)
		return -EINVAL;

	vma->vm_ops = &rtk_tp_vm_ops;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	return remap_pfn_range(vma,
			       vma->vm_start,
			       addr >> PAGE_SHIFT,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
}


static const struct file_operations rtk_tp_fops = {
	.owner         = THIS_MODULE,
	.open          = rtk_tp_open,
	.release       = rtk_tp_release,
	.mmap          = rtk_tp_mmap,
};

static void rtk_tp_power_on(struct rtk_tp_device *tpdev)
{
	clk_prepare_enable(tpdev->clk_tp);
	clk_prepare_enable(tpdev->clk_tpb);
	reset_control_deassert(tpdev->rstc_tp);
	reset_control_deassert(tpdev->rstc_tpb);
}

static void rtk_tp_power_off(struct rtk_tp_device *tpdev)
{
	 reset_control_assert(tpdev->rstc_tpb);
	 reset_control_assert(tpdev->rstc_tp);
	 clk_disable_unprepare(tpdev->clk_tpb);
	 clk_disable_unprepare(tpdev->clk_tp);
}

static int rtk_tp_runtime_resume(struct device *dev)
{
	struct rtk_tp_device *tpdev = dev_get_drvdata(dev);

	dev_dbg(dev, "enter %s\n", __func__);
	rtk_tp_power_on(tpdev);
	dev_dbg(dev, "exit %s\n", __func__);
	return 0;
}

static int rtk_tp_runtime_suspend(struct device *dev)
{
	struct rtk_tp_device *tpdev = dev_get_drvdata(dev);

	dev_dbg(dev, "enter %s\n", __func__);
	rtk_tp_power_off(tpdev);
	dev_dbg(dev, "exit %s\n", __func__);
	return 0;
}

static int rtk_tp_resume(struct device *dev)
{
	struct rtk_tp_device *tpdev = dev_get_drvdata(dev);

	if (atomic_read(&tpdev->open_cnt) == 0)
		return 0;

	dev_info(dev, "enter %s\n", __func__);
	rtk_tp_power_on(tpdev);
	dev_info(dev, "exit %s\n", __func__);
	return 0;
}

static int rtk_tp_suspend(struct device *dev)
{
	struct rtk_tp_device *tpdev = dev_get_drvdata(dev);

	if (atomic_read(&tpdev->open_cnt) == 0)
		return 0;

	dev_info(dev, "enter %s\n", __func__);
	rtk_tp_power_off(tpdev);
	dev_info(dev, "exit %s\n", __func__);
	return 0;
}

static const struct dev_pm_ops rtk_tp_pm_ops = {
	.runtime_suspend = rtk_tp_runtime_suspend,
	.runtime_resume  = rtk_tp_runtime_resume,
	.suspend         = rtk_tp_suspend,
	.resume          = rtk_tp_resume,
};

static int rtk_tp_probe(struct platform_device *pdev)
{
	struct rtk_tp_device *tpdev;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int ret;
	struct resource res;

	tpdev = devm_kzalloc(dev, sizeof(*tpdev), GFP_KERNEL);
	if (!tpdev)
		return -ENOMEM;

	tpdev->dev = dev;

	/* get tp resources */
	tpdev->clk_tp = devm_clk_get(dev, "tp");
	if (IS_ERR(tpdev->clk_tp)) {
		ret = PTR_ERR(tpdev->clk_tp);
		dev_err(dev, "tp: failed to get clk: %d\n", ret);
		return ret;
	}

	tpdev->rstc_tp = devm_reset_control_get(dev, "tp");
	if (IS_ERR(tpdev->rstc_tp)) {
		ret = PTR_ERR(tpdev->rstc_tp);
		dev_err(dev, "tp: failed to get reset_control: %d\n", ret);
		return ret;
	}

	ret = of_address_to_resource(np, 0, &res);
	if (ret) {
		dev_err(dev, "tp: failed to get address: %d\n", ret);
		return ret;
	}

	tpdev->addr_tp = res.start;
	tpdev->size_tp = ALIGN(resource_size(&res), PAGE_SIZE);
	tpdev->base_tp = devm_ioremap(dev, res.start, resource_size(&res));
	if (!tpdev->base_tp) {
		dev_err(dev, "tp: failed to ioremap\n");
		return -ENOMEM;
	}

	/* get tpb resources */
	tpdev->clk_tpb = devm_clk_get(dev, "tpb");
	if (IS_ERR(tpdev->clk_tpb)) {
		ret = PTR_ERR(tpdev->clk_tpb);
		dev_err(dev, "tpb: failed to get clk: %d\n", ret);
		return ret;
	}

	tpdev->rstc_tpb = devm_reset_control_get(dev, "tpb");
	if (IS_ERR(tpdev->rstc_tpb)) {
		ret = PTR_ERR(tpdev->rstc_tpb);
		dev_err(dev, "tpb: failed to get reset_control: %d\n", ret);
		return ret;
	}

	ret = of_address_to_resource(np, 1, &res);
	if (ret) {
		dev_err(dev, "tpb: failed to get address: %d\n", ret);
		return ret;
	}
	tpdev->addr_tpb = res.start;
	tpdev->size_tpb = ALIGN(resource_size(&res), PAGE_SIZE);
	tpdev->base_tpb = devm_ioremap(dev, res.start, resource_size(&res));
	if (!tpdev->base_tpb) {
		dev_err(dev, "tpb: failed to ioremap\n");
		return -ENOMEM;
	}

	atomic_set(&tpdev->open_cnt, 0);
	tpdev->mdev.minor  = MISC_DYNAMIC_MINOR;
	tpdev->mdev.name   = "tp";
	tpdev->mdev.fops   = &rtk_tp_fops;
	tpdev->mdev.parent = dev;
	ret = misc_register(&tpdev->mdev);
	if (ret) {
		dev_err(dev, "failed to register misc device: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, tpdev);
	pm_runtime_set_suspended(dev);
	pm_runtime_enable(dev);
	dev_info(dev, "initialized\n");
	return 0;
}

static int rtk_tp_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rtk_tp_device *tpdev = platform_get_drvdata(pdev);

	pm_runtime_disable(dev);
	platform_set_drvdata(pdev, NULL);
	misc_deregister(&tpdev->mdev);
	dev_info(dev, "removed\n");
	return 0;
}


static const struct of_device_id rtk_tp_ids[] = {
	{ .compatible = "realtek,tp" },
	{}
};

static struct platform_driver rtk_tp_driver = {
	.probe = rtk_tp_probe,
	.remove = rtk_tp_remove,
	.driver = {
		.owner = THIS_MODULE,
		.name = "rtk-tp",
		.of_match_table = rtk_tp_ids,
		.pm = &rtk_tp_pm_ops,

	},
};
module_platform_driver(rtk_tp_driver);
