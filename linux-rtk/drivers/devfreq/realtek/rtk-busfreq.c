/*
 * rtk-busfreq.c - Realtek Generic Bus DFS Driver
 *
 * Copyright (C) 2017,2019 Realtek Semiconductor Corporation
 * Copyright (C) 2017,2019 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#define pr_fmt(fmt) "busfreq: " fmt

#include <linux/clk.h>
#include <linux/devfreq.h>
#include <linux/devfreq-event.h>
#include <linux/io.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/pm_opp.h>
#include <linux/pm_runtime.h>
#include <linux/slab.h>
#include <linux/suspend.h>
#include <linux/sysfs.h>
#include <soc/realtek/devfreq_gov_data.h>

enum {
	BUSFREQ_GOV_PASSIVE,
	BUSFREQ_GOV_LTL,
	BUSFREQ_GOV_OTHER,
};

struct busfreq_data {
	struct device *dev;
	struct devfreq *devfreq;
	struct clk *clk;

	struct devfreq_dev_profile *profile;
	int gov_id;
	const char *gov_name;
	void *gov_data;

	struct devfreq_event_dev **edev;
	int edev_count;

	unsigned long cur_freq;
	unsigned long min_freq;
	unsigned long max_freq;
	unsigned long suspend_freq;
};


static inline void busfreq_enable_edev(struct busfreq_data *priv)
{
	int i;
	int ret;

	for (i = 0; i < priv->edev_count; i++) {
		ret = devfreq_event_enable_edev(priv->edev[i]);
		if (ret)
			dev_warn(priv->dev, "edev%d: devfreq_event_enable_edev() returns %d\n",
				i, ret);
	}
}

static inline void busfreq_disable_edev(struct busfreq_data *priv)
{
	int i;
	int ret;

	for (i = 0; i < priv->edev_count; i++) {
		ret = devfreq_event_disable_edev(priv->edev[i]);
		if (ret)
			dev_warn(priv->dev, "edev%d: devfreq_event_disable_edev() returns %d\n",
				i, ret);
	}
}

static inline void busfreq_restart_edev(struct busfreq_data *priv)
{
	int i;
	int ret;

	for (i = 0; i < priv->edev_count; i++) {
		ret = devfreq_event_set_event(priv->edev[i]);
		if (ret)
			dev_warn(priv->dev, "edev%d: devfreq_event_set_event() returns %d\n",
				i, ret);
	}
}

static int busfreq_get_dev_status(struct device *dev,
				  struct devfreq_dev_status *stat)
{
	struct busfreq_data *priv = dev_get_drvdata(dev);
	int i;
	int ret;
	int no_data = 0;

	stat->current_frequency = priv->cur_freq;
	stat->busy_time = stat->total_time = 0;

	for (i = 0; i < priv->edev_count; i++) {
		struct devfreq_event_data evdata;

		if (!priv->edev[i])
			continue;

		ret = devfreq_event_get_event(priv->edev[i], &evdata);
		if (ret) {
			dev_warn(dev, "edev%d: devfreq_event_get_event() returns %d\n",
				i, ret);
			continue;
		}

		dev_dbg(dev, "%s: edev%d: %ld / %ld\n", __func__,
			i, evdata.load_count, evdata.total_count);

		if (evdata.total_count == 0)
			no_data |= 1;
		stat->busy_time += evdata.load_count;
		stat->total_time += evdata.total_count;
	}
	if (no_data)
		stat->busy_time = stat->total_time = 0;
	busfreq_restart_edev(priv);

	return 0;
}

static int busfreq_get_cur_freq(struct device *dev, unsigned long *freq)
{
	struct busfreq_data *priv = dev_get_drvdata(dev);

	*freq = priv->cur_freq;
	return 0;
}

static int busfreq_set_clk_freq(struct busfreq_data *priv,
	   unsigned long new_freq)
{
	struct device *dev = priv->dev;
	int ret;

	if (priv->cur_freq == new_freq)
		return 0;

	dev_dbg(dev, "%s: set freq to %lu\n", __func__, new_freq);
	ret = clk_set_rate(priv->clk, new_freq);
	if (ret) {
		dev_err(dev, "clk_set_rate() returns %d\n", ret);
		return ret;
	}
	priv->cur_freq = new_freq;
	return 0;
}


static int busfreq_target(struct device *dev,
			  unsigned long *freq,
			  u32 flags)
{
	struct busfreq_data *priv = dev_get_drvdata(dev);
	struct dev_pm_opp *new_opp;
	unsigned long new_freq;

	rcu_read_lock();
	new_opp = devfreq_recommended_opp(dev, freq, flags);
	if (IS_ERR(new_opp)) {
		rcu_read_unlock();
		dev_err(dev, "Failed to find opp for %lu KHz\n", *freq);
		return PTR_ERR(new_opp);
	}

	new_freq = dev_pm_opp_get_freq(new_opp);
	rcu_read_unlock();

	return busfreq_set_clk_freq(priv, new_freq);
}

static int busfreq_suspend(struct device *dev)
{
	struct busfreq_data *priv = dev_get_drvdata(dev);
	unsigned long target = priv->suspend_freq;

	dev_info(dev, "%s enter\n", __func__);

	busfreq_disable_edev(priv);
	devfreq_suspend_device(priv->devfreq);

#ifdef CONFIG_SUSPEND
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY)
		target = priv->min_freq;
#endif
	busfreq_set_clk_freq(priv, target);
	dev_info(dev, "%s exit\n", __func__);
	return 0;
}

static int busfreq_resume(struct device *dev)
{
	struct busfreq_data *priv = dev_get_drvdata(dev);

	dev_info(dev, "%s enter\n", __func__);
	busfreq_set_clk_freq(priv, priv->max_freq);
	busfreq_enable_edev(priv);
	devfreq_resume_device(priv->devfreq);
	dev_info(dev, "%s exit\n", __func__);
	return 0;
}

static const struct dev_pm_ops busfreq_pm_ops = {
	SET_LATE_SYSTEM_SLEEP_PM_OPS(busfreq_suspend, busfreq_resume)
};

static int busfreq_add_edevs(struct busfreq_data *priv)
{
	struct device *dev = priv->dev;
	int i;

	priv->edev_count = devfreq_event_get_edev_count(dev);
	if (priv->edev_count < 0)
		priv->edev_count = 0;

	priv->edev = devm_kcalloc(dev, priv->edev_count, sizeof(*priv->edev),
		GFP_KERNEL);
	if (!priv->edev)
		return -ENOMEM;

	for (i = 0; i < priv->edev_count; i++) {
		priv->edev[i] = devfreq_event_get_edev_by_phandle(dev, i);
		if (IS_ERR(priv->edev[i]))
			return -EPROBE_DEFER;
	}
	return 0;
}

static int busfreq_setup_ltl(struct busfreq_data *priv)
{
	struct device *dev = priv->dev;
	struct devfreq_ltl_data *ltl_data;
	struct devfreq_dev_profile *profile = priv->profile;
	int ret;
	u32 data[3];

	ltl_data = devm_kzalloc(dev, sizeof(*ltl_data), GFP_KERNEL);
	if (!ltl_data)
		return -ENOMEM;

	ret = of_property_read_u32_array(dev->of_node, "ltl-data", data, 3);
	if (!ret) {
		ltl_data->th_cap       = data[0];
		ltl_data->th_cap_short = data[1];
		ltl_data->th_cap_long  = data[2];
	}
	priv->gov_data = ltl_data;

	profile->target         = busfreq_target;
	profile->get_dev_status = busfreq_get_dev_status;
	profile->get_cur_freq   = busfreq_get_cur_freq;
	profile->polling_ms     = 1000;
	profile->initial_freq   = priv->cur_freq;
	return 0;
}

static int busfreq_setup_passive(struct busfreq_data *priv)
{
	struct device *dev = priv->dev;
	struct devfreq_dev_profile *profile = priv->profile;
	struct devfreq_passive_data *passive_data;
	int ret;

	passive_data = devm_kzalloc(dev, sizeof(*passive_data), GFP_KERNEL);
	if (!passive_data)
		return -ENOMEM;
	passive_data->parent = devfreq_get_devfreq_by_phandle(dev, 0);
	if (IS_ERR(passive_data->parent)) {
		ret = PTR_ERR(passive_data->parent);
		dev_err(dev, "devfreq_get_devfreq_by_phandle() returns %d\n", ret);
		return ret;
	}

	priv->gov_data = passive_data;

	profile->target         = busfreq_target;
	profile->get_cur_freq   = busfreq_get_cur_freq;
	profile->polling_ms     = 1000;
	profile->initial_freq   = priv->cur_freq;
	return 0;
}

static int busfreq_setup_devfreq(struct busfreq_data *priv)
{
	struct device *dev = priv->dev;
	struct device_node *np = dev->of_node;
	struct devfreq_dev_profile *profile;
	int ret;

	priv->profile = devm_kzalloc(dev, sizeof(*profile), GFP_KERNEL);
	if (!priv->profile)
		return -ENOMEM;
	profile = priv->profile;

	ret = of_property_read_string(np, "method", &priv->gov_name);
	if (ret) {
		dev_err(dev, "invalid governor\n");
		return ret;
	}

	if (!strncmp("ltl", priv->gov_name, 3)) {
		priv->gov_id = BUSFREQ_GOV_LTL;
		ret = busfreq_setup_ltl(priv);
		if (ret) {
			dev_err(dev, "busfreq_setup_ltl() returns %d\n", ret);
			return ret;
		}
	} else if (!strncmp("passive", priv->gov_name, 7)) {
		priv->gov_id = BUSFREQ_GOV_PASSIVE;
		ret = busfreq_setup_passive(priv);
		if (ret) {
			dev_err(dev, "busfreq_setup_passive() returns %d\n", ret);
			return ret;
		}
	} else {
		dev_err(dev, "invalid governor name: %s\n", priv->gov_name);
		return -EINVAL;
	}
	return 0;
}

static int busfreq_setup_freq(struct busfreq_data *priv)
{
	struct device *dev = priv->dev;
	struct dev_pm_opp *opp;
	int ret = 0;
	unsigned long target_freq;

	priv->cur_freq = clk_get_rate(priv->clk);

	rcu_read_lock();

	target_freq = 0;
	opp = dev_pm_opp_find_freq_ceil(dev, &target_freq);
	if (IS_ERR(opp)) {
		ret = PTR_ERR(opp);
		dev_err(dev, "failed to get min_freq\n");
		goto error;
	}
	priv->min_freq = target_freq;

	target_freq = ULONG_MAX;
	opp = dev_pm_opp_find_freq_floor(dev, &target_freq);
	if (IS_ERR(opp)) {
		ret = PTR_ERR(opp);
		dev_err(dev, "failed to get max_freq\n");
		goto error;
	}
	priv->max_freq = target_freq;

	opp = dev_pm_opp_get_suspend_opp(dev);
	if (IS_ERR(opp)) {
		dev_warn(dev, "invalid suspend_freq, use max_freq\n");
		priv->suspend_freq = priv->max_freq;
	} else
		priv->suspend_freq = dev_pm_opp_get_freq(opp);
error:
	rcu_read_unlock();

	dev_info(dev, "cur_freq = %lu\n", priv->cur_freq);
	dev_info(dev, "max_freq = %lu Hz\n", priv->max_freq);
	dev_info(dev, "min_freq = %lu Hz\n", priv->min_freq);
	dev_info(dev, "suspend_freq = %lu Hz\n", priv->suspend_freq);

	return ret;

}

static int busfreq_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct busfreq_data *priv;
	int ret;

	dev_info(dev, "%s\n", __func__);

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	priv->dev = dev;

	ret = busfreq_add_edevs(priv);
	if (ret)
		return ret;

	priv->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->clk)) {
		ret = PTR_ERR(priv->clk);
		dev_err(dev, "clk_get() returns %d\n", ret);
		return ret;
	}

	ret = dev_pm_opp_of_add_table(dev);
	if (ret) {
		dev_err(dev, "dev_pm_opp_of_add_table() returns %d\n", ret);
		return ret;
	}

	ret = busfreq_setup_freq(priv);
	if (ret)
		goto remove_table;

	ret = busfreq_setup_devfreq(priv);
	if (ret)
		goto remove_table;

	priv->devfreq = devm_devfreq_add_device(dev,
					        priv->profile,
						priv->gov_name,
						priv->gov_data);
	if (IS_ERR(priv->devfreq)) {
		ret = PTR_ERR(priv->devfreq);
		dev_err(dev, "devfreq_add_device() returns %d\n", ret);
		goto remove_table;
	}

	platform_set_drvdata(pdev, priv);
	busfreq_enable_edev(priv);
	return 0;

remove_table:
	dev_pm_opp_of_remove_table(dev);
	return ret;
}

static const struct of_device_id busfreq_ids[] = {
	{ .compatible = "realtek,busfreq", },
	{}
};

static struct platform_driver busfreq_driver = {
	.driver = {
		.owner = THIS_MODULE,
		.name  = "rtk-busfreq",
		.pm = &busfreq_pm_ops,
		.of_match_table = busfreq_ids,
	},
	.probe = busfreq_probe,
};

static int __init busfreq_init(void)
{
	return platform_driver_register(&busfreq_driver);
}
late_initcall(busfreq_init);

