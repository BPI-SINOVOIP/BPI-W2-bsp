/*
 * reset-rtk.c - Realtek reset controller & reset control
 *
 * Copyright (C) 2016-2017 Realtek Semiconductor Corporation
 * Copyright (C) 2016-2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/pm.h>
#include <linux/regmap.h>
#include <linux/reset.h>
#include <linux/reset-controller.h>
#include <linux/reset-helper.h>
#include <linux/slab.h>
#include <linux/suspend.h>
#include <soc/realtek/rtk_mmio.h>
#include <soc/realtek/rdbg.h>
#include <dt-bindings/reset/rtk,reset.h>

#include "common.h"

static DEFINE_SPINLOCK(rtk_reset_async_lock);
static LIST_HEAD(rtk_reset_async_list);

#define RESET_ASYNC         BIT(0)
#define RESET_NO_PM         BIT(1)
#define RESET_HAS_WRITE_EN  BIT(2)

struct reset_priv {
	struct device *dev;
	struct reset_controller_dev rcdev;
	unsigned int flags;

	/* register */
	void *reg;

	/* mmio regmap of reg */
	struct regmap *regmap;
	int offset;

	/* async reset control */
	unsigned int async_data;
	unsigned int async_group;
	struct list_head async_list;

	/* pm */
	unsigned int pm_data;
	unsigned int pm_ignore_bits;

	/* boot clear bits */
	unsigned int boot_clear_bits;

	/* reg tracker */
	struct rdbg_info *ref;
};

#define to_reset_priv(_p) container_of((_p), struct reset_priv, rcdev)

static inline int contain_write_en(struct reset_priv *priv)
{
	return !!(priv->flags & RESET_HAS_WRITE_EN);
}

static inline u32 bits_to_set(struct reset_priv *priv, u32 bits_to_set)
{
	return bits_to_set * (contain_write_en(priv) ? 3 : 1);
}

static inline u32 bits_to_clear(struct reset_priv *priv, u32 bits_to_clear)
{
	return contain_write_en(priv) ? (bits_to_clear << 1) : 0;
}

static inline u32 bits_to_mask(struct reset_priv *priv, u32 bits)
{
	return bits_to_set(priv, bits);
}

static inline void rtk_reset_write(struct reset_priv *priv, unsigned int val)
{
	WARN_ON_ONCE(1);
}

static inline void rtk_reset_read(struct reset_priv *priv, unsigned int *val)
{
	if (priv->regmap)
		regmap_read(priv->regmap, priv->offset, val);
	else if (priv->reg)
		*val = readl(priv->reg);
	else
		WARN_ON_ONCE(1);
}

static inline void rtk_reset_update_bits(struct reset_priv *priv,
	unsigned int mask, unsigned int val)
{
	dev_dbg(priv->dev, "%s: flags:%c mask=%08x, val=%08x\n",
		__func__, contain_write_en(priv) ? 'w' : '-' , mask, val);
	if (priv->regmap) {
		regmap_update_bits(priv->regmap, priv->offset, mask, val);
	} else if (priv->reg) {
		unsigned int rval;

		rval = readl(priv->reg);
		rval = (rval & ~mask) | (val & mask);
		writel(rval, priv->reg);
	} else
		WARN_ON_ONCE(1);
}

static int rtk_reset_assert(struct reset_controller_dev *rcdev,
		unsigned long id)
{
	struct reset_priv *priv = to_reset_priv(rcdev);
	u32 val, mask;

	if (priv->flags & RESET_ASYNC) {
		if (id == RTK_RSTN_DO_SYNC)
			return -EINVAL;
	}

	mask = bits_to_mask(priv, BIT(id));
	val = bits_to_clear(priv, BIT(id));
	rtk_reset_update_bits(priv, mask, val);

	rdbg_update_ref(priv->ref, BIT(id), __func__);

	return 0;
}

static void rtk_reset_deassert_sync(unsigned int group)
{
	struct reset_priv *p;
	u32 val, mask;

	list_for_each_entry(p, &rtk_reset_async_list, async_list) {
		if (p->async_group != group)
			continue;

		if (!p->async_data)
			continue;

		mask = bits_to_mask(p, p->async_data);
		val = bits_to_set(p, p->async_data);
		rtk_reset_update_bits(p, mask, val);

		rdbg_update_ref(p->ref, p->async_data, __func__);
		p->async_data = 0;
	}
}

static int rtk_reset_deassert(struct reset_controller_dev *rcdev,
		unsigned long id)
{
	struct reset_priv *priv = to_reset_priv(rcdev);
	u32 val, mask;
	unsigned long flags;

	if (priv->flags & RESET_ASYNC) {
		spin_lock_irqsave(&rtk_reset_async_lock, flags);
		if (id == RTK_RSTN_DO_SYNC)
			rtk_reset_deassert_sync(priv->async_group);
		else
			priv->async_data |= BIT(id);
		spin_unlock_irqrestore(&rtk_reset_async_lock, flags);

		return 0;
	}

	mask = bits_to_mask(priv, BIT(id));
	val = bits_to_set(priv, BIT(id));
	rtk_reset_update_bits(priv, mask, val);

	rdbg_update_ref(priv->ref, BIT(id), __func__);

	return 0;
}

static int rtk_reset_reset(struct reset_controller_dev *rcdev,
		unsigned long id)
{
	int ret;

	ret = rtk_reset_assert(rcdev, id);
	if (ret)
		return ret;

	return rtk_reset_deassert(rcdev, id);
}

static int rtk_reset_status(struct reset_controller_dev *rcdev,
		unsigned long id)
{
	struct reset_priv *priv = to_reset_priv(rcdev);
	unsigned int val = 0;

	rtk_reset_read(priv, &val);
	return !(val & BIT(id));
}

static struct reset_control_ops rtk_reset_ops = {
	.assert   = rtk_reset_assert,
	.deassert = rtk_reset_deassert,
	.reset    = rtk_reset_reset,
	.status   = rtk_reset_status,
};

static int rtk_reset_of_xlate(struct reset_controller_dev *rcdev,
		const struct of_phandle_args *reset_spec)
{
	struct reset_priv __maybe_unused *priv = to_reset_priv(rcdev);
	int id;

	if (reset_spec->args_count != 1)
		return -EINVAL;

	id = (int)reset_spec->args[0];
	return id;
}

static int rtk_reset_parse_dt(struct device_node *np, struct reset_priv *priv)
{
	u32 val;

	if (of_find_property(np, "has-write-en", NULL))
		priv->flags |= RESET_HAS_WRITE_EN;

	if (!of_property_read_u32(np, "async-group", &val)) {
		priv->flags |= RESET_ASYNC | RESET_NO_PM;
		priv->async_group = val;
		list_add(&priv->async_list, &rtk_reset_async_list);
	}

	if (of_find_property(np, "no-pm", NULL))
		priv->flags |= RESET_NO_PM;

	of_property_read_u32(np, "pm-ignore-bits", &priv->pm_ignore_bits);

	priv->boot_clear_bits = 0;
	of_property_read_u32(np, "boot-clear-bits", &priv->boot_clear_bits);

	return 0;
}

static int rtk_reset_suspend(struct device *dev)
{
	struct reset_priv *priv = dev_get_drvdata(dev);

	if (priv->flags & RESET_NO_PM)
		return 0;

#ifdef CONFIG_SUSPEND
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY)
		return 0;
#endif
	dev_info(dev, "Enter %s\n", __func__);

	rtk_reset_read(priv, &priv->pm_data);
	dev_dbg(dev, "%s: save val=%08x\n", __func__, priv->pm_data);

	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static int rtk_reset_resume(struct device *dev)
{
	struct reset_priv *priv = dev_get_drvdata(dev);
	unsigned int mask;
	unsigned int val;

	if (priv->flags & RESET_NO_PM)
		return 0;

#ifdef CONFIG_SUSPEND
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY)
		return 0;
#endif
	dev_info(dev, "Enter %s\n", __func__);

	val  = priv->pm_data;
	mask = ~bits_to_mask(priv, priv->pm_ignore_bits);
	dev_info(dev, "%s: restore mask=%08x, val=%08x\n", __func__, mask, val);
	rtk_reset_update_bits(priv, mask, val);

	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static const struct dev_pm_ops rtk_reset_pm_ops = {
	.suspend_noirq = rtk_reset_suspend,
	.resume_noirq = rtk_reset_resume,
};

static int rtk_reset_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct reset_priv *priv;
	struct regmap *regmap;
	void *reg;
	int offset = 0;
	int ret;

	dev_info(dev, "%s\n", __func__);

	priv = devm_kzalloc(&pdev->dev, sizeof(struct reset_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	reg = of_iomap(np, 0);
	regmap = of_get_rtk_mmio_regmap_with_offset(np, 0, &offset);
	if (IS_ERR(regmap))
		regmap = NULL;
	if (!reg && IS_ERR_OR_NULL(regmap))
		return -EINVAL;

	priv->dev = dev;
	priv->reg = reg;
	if (regmap) {
		priv->regmap = regmap;
		priv->offset = offset;
		dev_info(dev, "use mmio regmap\n");
	}

	/* low level debug */
	if (is_clk_debug_enabled()) {
		priv->ref = of_rdbg_get_info(np, 0, 0);
		if (priv->ref)
			dev_err(dev, "rdbg add %s\n", np->name);
	}

	priv->rcdev.owner = THIS_MODULE;
	priv->rcdev.ops = &rtk_reset_ops;
	priv->rcdev.of_node = np;
	priv->rcdev.of_reset_n_cells = 1;
	priv->rcdev.of_xlate = rtk_reset_of_xlate;
	rtk_reset_parse_dt(np, priv);

	if (priv->boot_clear_bits) {
		u32 mask = bits_to_mask(priv, priv->boot_clear_bits);
		u32 val = bits_to_clear(priv, priv->boot_clear_bits);

		dev_info(dev, "boot_clear_bits: mask=%08x, val=%08x\n",
			mask, val);
		rtk_reset_update_bits(priv, mask, val);
	}
	ret = reset_controller_register(&priv->rcdev);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, priv);

	return ret;
}

static const struct of_device_id rtk_reset_match[] = {
	{.compatible = "realtek,reset-controller"},
	{}
};

static struct platform_driver rtk_reset_driver = {
	.probe = rtk_reset_probe,
	.driver = {
		.name   = "rtk-reset",
		.of_match_table = rtk_reset_match,
		.pm = &rtk_reset_pm_ops,
	},
};

static int __init rtk_reset_init(void)
{
	return platform_driver_register(&rtk_reset_driver);
}
core_initcall(rtk_reset_init);

/*
 * deprecated api
 */
static struct device_node *__rcp_np;

struct reset_control *rstc_get(const char *name)
{
	struct reset_control *rstc = ERR_PTR(-EINVAL);
	struct device_node *child;

	pr_notice("Deprecated API rstc_get is used by %s, PLEASE use of_reset_control_get\n",
		name);

	if (!__rcp_np)
		return ERR_PTR(-ENOENT);

	for_each_child_of_node(__rcp_np, child) {
		rstc = of_reset_control_get(child, name);
		if (!IS_ERR(rstc))
			return rstc;
	}

	pr_err("Failed to get rstc for %s\n", name);
	return rstc;
}
EXPORT_SYMBOL(rstc_get);

static const struct of_device_id rtk_rcp_match[] = {
	{.compatible = "realtek,reset-control-provider"},
	{}
};

static int rtk_rcp_probe(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "deprecated API OK\n");
	__rcp_np = pdev->dev.of_node;
	return 0;
}

static struct platform_driver rtk_rcp_driver = {
	.probe = rtk_rcp_probe,
	.driver = {
		.name   = "rtk-rcp",
		.of_match_table = rtk_rcp_match,
	},
};

static int __init rtk_rcp_init(void)
{
	return platform_driver_register(&rtk_rcp_driver);
}
core_initcall(rtk_rcp_init);

