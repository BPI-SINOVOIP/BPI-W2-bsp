/*
 * busfreq-rtk.c - Realtek Generic Bus DFS
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
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
#include <soc/realtek/rdbg.h>
#include <soc/realtek/rtk_devfreq.h>

struct rtk_busfreq {
	struct devfreq *devfreq;
	struct clk *clk;
	unsigned long cur_freq;

	/* pm runtime */
	int suspended;

	struct devfreq_event_dev **edev;
	int edev_count;
};

static inline unsigned long get_max_freq(struct rtk_busfreq *priv)
{
	int max_state = priv->devfreq->profile->max_state;

	return priv->devfreq->profile->freq_table[max_state - 1];
}

static inline unsigned long get_min_freq(struct rtk_busfreq *priv)
{
	return priv->devfreq->profile->freq_table[0];
}

static inline void __edev_enable(struct rtk_busfreq *priv)
{
	int i;
	int ret;

	for (i = 0; i < priv->edev_count; i++) {
		ret = devfreq_event_enable_edev(priv->edev[i]);
		if (ret)
			pr_err("%s: devfreq_event_enable_edev() returns %d\n",
				__func__, ret);
	}
}

static inline void __edev_disable(struct rtk_busfreq *priv)
{
	int i;
	int ret;

	for (i = 0; i < priv->edev_count; i++) {
		ret = devfreq_event_disable_edev(priv->edev[i]);
		if (ret)
			pr_err("%s: devfreq_event_disable_edev() returns %d\n",
				__func__, ret);
	}
}

static inline void __edev_set_event(struct rtk_busfreq *priv)
{
	int i;

	for (i = 0; i < priv->edev_count; i++)
		devfreq_event_set_event(priv->edev[i]);
}

static int rtk_busfreq_get_dev_status(struct device *dev,
	struct devfreq_dev_status *stat)
{
	struct rtk_busfreq *priv = dev_get_drvdata(dev);
	int i;
	int ret;
	int scaling;

	stat->current_frequency = priv->cur_freq;
	stat->busy_time  = 0;
	stat->total_time = 0;
	scaling = stat->current_frequency / get_min_freq(priv);

	for (i = 0; i < priv->edev_count; i++) {
		struct rtk_devfreq_event_data rdata;

		if (!priv->edev[i])
			continue;

		rtk_devfreq_event_data_init(&rdata);
		rdata.scaling = scaling;

		ret = devfreq_event_get_event(priv->edev[i], &rdata.data);
		if (ret) {
			dev_warn(dev, "failed to get event_data of edev%d: %d\n",
				i, ret);
			continue;
		}

		stat->busy_time += rdata.data.load_count;
		stat->total_time += rdata.data.total_count;
	}
	__edev_set_event(priv);

	return 0;
}

static int rtk_busfreq_passive_target(struct device *dev, unsigned long *freq,
	u32 flags)
{
	struct rtk_busfreq *priv = dev_get_drvdata(dev);

	if (priv->cur_freq == *freq)
		return 0;

	dev_dbg(dev, "%s: set freq to %lu\n", __func__, *freq);

	priv->cur_freq = *freq;
	clk_set_rate(priv->clk, *freq);
	return 0;
}

static int rtk_busfreq_get_cur_freq(struct device *dev, unsigned long *freq)
{
	struct rtk_busfreq *priv = dev_get_drvdata(dev);

	*freq = priv->cur_freq;
	return 0;
}

static int rtk_busfreq_target(struct device *dev, unsigned long *freq,
	u32 flags)
{
	struct rtk_busfreq *priv = dev_get_drvdata(dev);
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

	if (priv->cur_freq == new_freq)
		return 0;

	dev_dbg(dev, "%s: set freq to %lu\n", __func__, *freq);

	priv->cur_freq = new_freq;
	clk_set_rate(priv->clk, new_freq);

	return 0;
}

static int rtk_busfreq_suspend(struct device *dev)
{
	struct rtk_busfreq *priv = dev_get_drvdata(dev);

	dev_info(dev, "%s enter\n", __func__);

	if (priv->suspended)
		goto done;

	__edev_disable(priv);
	devfreq_suspend_device(priv->devfreq);

	if (IS_ENABLED(CONFIG_SUSPEND) && RTK_PM_STATE == PM_SUSPEND_STANDBY)
		clk_set_rate(priv->clk, get_min_freq(priv));
done:
	dev_info(dev, "%s exit\n", __func__);
	return 0;
}

static int rtk_busfreq_resume(struct device *dev)
{
	struct rtk_busfreq *priv = dev_get_drvdata(dev);

	dev_info(dev, "%s enter\n", __func__);

	if (priv->suspended)
		goto done;

	if (IS_ENABLED(CONFIG_SUSPEND) && RTK_PM_STATE == PM_SUSPEND_STANDBY)
		clk_set_rate(priv->clk, get_max_freq(priv));

	__edev_enable(priv);
	devfreq_resume_device(priv->devfreq);
done:
	dev_info(dev, "%s exit\n", __func__);
	return 0;
}

static int rtk_busfreq_runtime_suspend(struct device *dev)
{
	struct rtk_busfreq *priv = dev_get_drvdata(dev);

	dev_info(dev, "%s enter\n", __func__);

	if (priv->suspended)
		goto done;
	priv->suspended = 1;

	__edev_disable(priv);
	devfreq_suspend_device(priv->devfreq);

	clk_set_rate(priv->clk, get_max_freq(priv));
done:
	dev_info(dev, "%s exit\n", __func__);
	return 0;

}

static int rtk_busfreq_runtime_resume(struct device *dev)
{
	struct rtk_busfreq *priv = dev_get_drvdata(dev);

	dev_info(dev, "%s enter\n", __func__);

	if (!priv->suspended)
		goto done;
	priv->suspended = 0;

	clk_set_rate(priv->clk, get_max_freq(priv));

	__edev_enable(priv);
	devfreq_resume_device(priv->devfreq);
done:
	dev_info(dev, "%s exit\n", __func__);
	return 0;
}

static const struct dev_pm_ops rtk_busfreq_pm_ops = {
	SET_LATE_SYSTEM_SLEEP_PM_OPS(rtk_busfreq_suspend, rtk_busfreq_resume)
	.runtime_suspend = rtk_busfreq_runtime_suspend,
	.runtime_resume = rtk_busfreq_runtime_resume,
};

struct rtk_busfreq_initdata {
	struct device_node *parent_np;
};

static int rtk_busfreq_parse_dt(struct device *dev,
	struct rtk_busfreq_initdata *data)
{
	struct rtk_busfreq *priv = dev_get_drvdata(dev);
	int ret;
	int i;

	priv->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->clk)) {
		ret = PTR_ERR(priv->clk);
		dev_err(dev, "failed to get clk: %d\n", ret);
		return ret;
	}

	ret = dev_pm_opp_of_add_table(dev);
	if (ret) {
		dev_err(dev, "failed to get OPP table: %d\n", ret);
		return ret;
	}

	data->parent_np = of_parse_phandle(dev->of_node, "devfreq", 0);
	if (data->parent_np)
		return 0;

	priv->edev_count = devfreq_event_get_edev_count(dev);
	if (priv->edev_count < 0)
		priv->edev_count = 0;

	priv->edev = devm_kcalloc(dev, priv->edev_count, sizeof(*priv->edev),
		GFP_KERNEL);
	for (i = 0; i < priv->edev_count; i++) {
		priv->edev[i] = devfreq_event_get_edev_by_phandle(dev, i);
		if (IS_ERR(priv->edev[i]))
			return -EPROBE_DEFER;
	}

	return 0;
}

static int rtk_busfreq_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct devfreq_dev_profile *profile;
	struct devfreq_passive_data *passive_data;
	struct rtk_busfreq *priv;
	struct rtk_busfreq_initdata data = {0};
	int ret;

	dev_info(dev, "%s\n", __func__);

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);

	ret = rtk_busfreq_parse_dt(dev, &data);
	if (ret)
		goto error;

	ret = -ENOMEM;
	profile = devm_kzalloc(dev, sizeof(*profile), GFP_KERNEL);
	if (!profile)
		goto error;

	if (data.parent_np)
		goto passive;

	profile->target         = rtk_busfreq_target;
	profile->get_dev_status = rtk_busfreq_get_dev_status;
	profile->get_cur_freq   = rtk_busfreq_get_cur_freq;
	profile->polling_ms     = 1000;
	profile->initial_freq   = clk_get_rate(priv->clk);

	priv->cur_freq = profile->initial_freq;

	priv->devfreq = devm_devfreq_add_device(dev, profile, "simple_ondemand",
		NULL);
	if (IS_ERR(priv->devfreq)) {
		ret = PTR_ERR(priv->devfreq);
		dev_err(dev, "failed to add devfreq dev: %d\n", ret);
		goto error;
	}

	goto done;

passive:
	profile->target         = rtk_busfreq_passive_target;
	profile->get_cur_freq   = rtk_busfreq_get_cur_freq;
	profile->polling_ms     = 1000;
	profile->initial_freq   = clk_get_rate(priv->clk);

	ret = -ENOMEM;
	passive_data = devm_kzalloc(dev, sizeof(*passive_data), GFP_KERNEL);
	if (!passive_data)
		goto error;
	passive_data->parent = devfreq_get_devfreq_by_phandle(dev, 0);

	priv->cur_freq = profile->initial_freq;
	priv->devfreq = devm_devfreq_add_device(dev, profile, "passive",
		passive_data);
	if (IS_ERR(priv->devfreq)) {
		ret = PTR_ERR(priv->devfreq);
		dev_err(dev, "failed to add devfreq dev: %d\n", ret);
		goto error;
	}

done:
	__edev_enable(priv);

	dev_dbg(dev, "bus dfs device registered: (%6ld KHz ~ %6ld KHz)\n",
		get_min_freq(priv), get_max_freq(priv));

	rpm_debug_sysfs_add(dev);
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);
	pm_runtime_get_noresume(dev);

	return 0;

error:
	dev_pm_opp_of_remove_table(dev);
	return ret;
}

static const struct of_device_id rtk_busfreq_ids[] = {
	{ .compatible = "realtek,busfreq", },
	{}
};

static struct platform_driver rtk_busfreq_driver = {
	.driver = {
		.name  = "rtk-busfreq",
		.of_match_table = rtk_busfreq_ids,
		.pm = &rtk_busfreq_pm_ops,
	},
	.probe = rtk_busfreq_probe,
};

static int __init rtk_busfreq_init(void)
{
	return platform_driver_register(&rtk_busfreq_driver);
}
late_initcall(rtk_busfreq_init);

