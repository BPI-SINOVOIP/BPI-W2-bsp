/*
 * Devfreq Event Device of Realtek DCSYS Performance Counter
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define pr_fmt(fmt) "dcsys: edev: " fmt

#include <linux/devfreq-event.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <soc/realtek/rtk_dc_sys_pc.h>
#include <soc/realtek/rtk_devfreq.h>

#define EDEV_MAX_LOAD          1000

struct sys_data {
	int prev_cap;
	int weighted_cap_long;
	int weighted_cap_short;
	int weighted_delta_cap;
	int weighted_delta_cap_square;
};

struct dcsys_edev {
	struct dcsys_pc *pc;
	struct devfreq_event_dev *edev;
	struct sys_data data[2];
	struct notifier_block nb;
	int self_clear;
};

static inline void reset_sys_data(struct sys_data *d)
{
	d->prev_cap = 200;
	d->weighted_cap_long = 200;
	d->weighted_cap_short = 200;
}

static int dcsys_edev_set_owner(struct dcsys_edev *priv, int forced)
{
	int ret;
	unsigned int flags = forced ? DCSYS_PC_FORCE_SET : 0;

	ret = dcsys_pc_set_owner(priv->pc, flags);
	if (ret)
		pr_warn("dcsys_pc_set_owner() returns %d\n", ret);
	return ret;
}

static int dcsys_edev_clear_owner(struct dcsys_edev *priv)
{
	int ret;

	priv->self_clear = 1;
	ret = dcsys_pc_clear_owner(priv->pc);
	if (ret)
		pr_warn("dcsys_pc_clear_owner() returns %d\n", ret);
	priv->self_clear = 0;
	return ret;
}

static int dcsys_edev_start(struct dcsys_edev *priv)
{
	int ret = 0;

	if (dcsys_pc_is_owner(priv->pc) != 1)
		return 0;

	dcsys_pc_prog_configure(0, DC_PC_PROG_ID_VO, 0);
	dcsys_pc_prog_configure(4, DC_PC_PROG_ID_VO, 1);

	ret = dcsys_pc_start(priv->pc);
	if (ret)
		pr_warn("dcsys_pc_start() returns %d\n", ret);
	return 0;
}

static int dcsys_edev_stop(struct dcsys_edev *priv)
{
	int ret;

	ret = dcsys_pc_stop(priv->pc);
	if (ret)
		pr_warn("dcsys_pc_stop() returns %d\n", ret);
	return 0;
}

static int dcsys_edev_get_load_sys(struct dcsys_edev *priv, int sys)
{
	struct dcsys_pc_prog_data vo;
	struct dcsys_pc_global_data global;
	int load = 0;
	unsigned int div;
	unsigned int i = sys ? 4 : 0;

	dcsys_pc_global_get_data(sys, &global);
	dcsys_pc_prog_get_data(i, &vo);

	if (global.mon != 0) {
		div = global.mon / EDEV_MAX_LOAD;
		load = (global.ack - vo.ack) / div;
	}

	return load;
}

#define weight(_v0, _w0, _v1, _w1)  \
	(((_v0) * (_w0) + (_v1) * (_w1)) / ((_w0) + (_w1)))

static int dcsys_edev_capability_trasform(struct dcsys_edev *priv, int sys,
	int scaling)
{
	int cap;
	int load;
	int delta_cap;
	int delta_cap_square;
	struct sys_data *d = &priv->data[sys];

	load = dcsys_edev_get_load_sys(priv, sys);

	cap = load * scaling;
	if (cap == 0)
		return 0;

	delta_cap = cap - d->prev_cap;
	delta_cap_square = delta_cap * delta_cap;

	d->weighted_cap_long = weight(cap, 5, d->weighted_cap_long, 95);
	d->weighted_cap_short = weight(cap, 50, d->weighted_cap_short, 50);
	d->weighted_delta_cap = weight(delta_cap, 33,
		d->weighted_delta_cap, 66);
	d->weighted_delta_cap_square = weight(delta_cap_square, 33,
		d->weighted_delta_cap_square, 66);

	pr_debug("%s: SYS%d, LOADx%d, %4d %4d %4d %4d %4d %6d %6d\n",
		__func__, sys, scaling,
		cap, d->weighted_cap_short, d->weighted_cap_long,
		delta_cap, d->weighted_delta_cap,
		delta_cap_square, d->weighted_delta_cap_square);

	d->prev_cap = cap;

	if (cap < 60 && d->weighted_cap_short < 45 && d->weighted_cap_long < 30)
		return 0;

	return EDEV_MAX_LOAD;
}

static int dcsys_edev_get_load(struct dcsys_edev *priv, int scaling)
{
	int ret;
	int load0 = EDEV_MAX_LOAD;
	int load1 = EDEV_MAX_LOAD;

	if (dcsys_pc_is_owner(priv->pc) != 1)
		return -EINVAL;

	ret = dcsys_edev_stop(priv);
	if (ret)
		return ret;

	if (scaling < 0) {
		load0 = dcsys_edev_get_load_sys(priv, 0);
		load1 = dcsys_edev_get_load_sys(priv, 1);
	} else {
		load0 = dcsys_edev_capability_trasform(priv, 0, scaling);
		load1 = dcsys_edev_capability_trasform(priv, 1, scaling);
	}

	return load0 > load1 ? load0 : load1;
}

static int dcsys_edev_get_event(struct devfreq_event_dev *edev,
			 struct devfreq_event_data *edata)
{
	struct dcsys_edev *priv = edev->desc->driver_data;
	int ret;
	int scaling;

	scaling = rtk_devfreq_get_system_scaling(edata);

	edata->load_count = 0;
	edata->total_count = 0;

	ret = dcsys_edev_get_load(priv, scaling);
	if (ret < 0)
		return 0;

	edata->load_count = ret;
	edata->total_count = EDEV_MAX_LOAD;

	return 0;
}

static int dcsys_edev_set_event(struct devfreq_event_dev *edev)
{
	struct dcsys_edev *priv = edev->desc->driver_data;

	return dcsys_edev_start(priv);
}

static int dcsys_edev_enable(struct devfreq_event_dev *edev)
{
	struct dcsys_edev *priv = edev->desc->driver_data;
	int ret;

	ret = dcsys_edev_set_owner(priv, 0);
	if (ret)
		return ret;

	return dcsys_edev_start(priv);
}

static int dcsys_edev_disable(struct devfreq_event_dev *edev)
{
	struct dcsys_edev *priv = edev->desc->driver_data;
	int ret;

	ret = dcsys_edev_stop(priv);
	if (ret)
		return ret;

	return dcsys_edev_clear_owner(priv);
}

static int dcsys_edev_reset(struct devfreq_event_dev *edev)
{
	struct dcsys_edev *priv = edev->desc->driver_data;

	reset_sys_data(&priv->data[0]);
	reset_sys_data(&priv->data[1]);

	dcsys_edev_set_owner(priv, 1);
	dcsys_edev_start(priv);

	return 0;
}

static const struct devfreq_event_ops dcsys_edev_ops = {
	.enable = dcsys_edev_enable,
	.disable = dcsys_edev_disable,
	.reset = dcsys_edev_reset,
	.set_event = dcsys_edev_set_event,
	.get_event = dcsys_edev_get_event,
};

static struct devfreq_event_desc dcsys_edev_desc = {
	.name = "dcsys",
	.ops = &dcsys_edev_ops,
};

static int dcsys_dev_notifier_fn(struct notifier_block *nb, unsigned long state,
	void *data)
{
	struct dcsys_edev *priv = container_of(nb, struct dcsys_edev, nb);
	int ret;

	pr_debug("%s\n", __func__);

	if (priv->edev->enable_count <= 0)
		return NOTIFY_DONE;

	switch (state) {
	case DCSYS_PC_OWNER_SET:
		ret = dcsys_pc_is_owner(priv->pc);
		if (ret != 1)
			pr_debug("%s: dcsys pc onwer changed\n", __func__);
		break;

	case DCSYS_PC_OWNER_CLEAR:
		if (!priv->self_clear)
			dcsys_edev_reset(priv->edev);
		break;
	}

	return  NOTIFY_OK;
}

static int dcsys_edev_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct dcsys_edev *priv;
	int ret;

	dev_info(dev, "[DCSYS-EDEV] %s\n", __func__);

	if (!of_device_is_compatible(np, "devfreq-event"))
		return -EINVAL;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	ret = -EPROBE_DEFER;
	priv->pc = dcsys_pc_simple_get(dev);
	if (!priv->pc)
		goto error;

	priv->nb.notifier_call = dcsys_dev_notifier_fn;
	dcsys_edev_desc.driver_data = priv;

	reset_sys_data(&priv->data[0]);
	reset_sys_data(&priv->data[1]);

	priv->edev = devfreq_event_add_edev(&pdev->dev, &dcsys_edev_desc);
	if (IS_ERR(priv->edev)) {
		ret = PTR_ERR(priv->edev);
		goto error;
	}

	dcsys_pc_register_notifier(&priv->nb);

	return 0;

error:
	dcsys_pc_put(priv->pc);
	return 0;
}

static const struct of_device_id dcsys_edev_ids[] = {
	{ .compatible = "realtek,dcsys-event", },
	{}
};

static struct platform_driver dcsys_edev_driver = {
	.driver = {
		.name  = "rtk-dcsys:event",
		.of_match_table = dcsys_edev_ids,
	},
	.probe = dcsys_edev_probe,
};

static int __init dcsys_edev_init(void)
{
	return platform_driver_register(&dcsys_edev_driver);
}
device_initcall(dcsys_edev_init);

