/*
 * LTL Governor
 *
 * Copyright (C) 2019 Realtek Semiconductor Corporation
 * Copyright (C) 2019 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/errno.h>
#include <linux/module.h>
#include <linux/devfreq.h>
#include <linux/math64.h>
#include "../governor.h"
#include <soc/realtek/devfreq_gov_data.h>

#define DEFAULT_CAP_LONG      (200)
#define DEFAULT_TH_CAP        (60)
#define DEFAULT_TH_CAP_SHORT  (45)
#define DEFAULT_TH_CAP_LONG   (30)

#define weight(_v0, _w0, _v1, _w1)  \
	(((_v0) * (_w0) + (_v1) * (_w1)) / ((_w0) + (_w1)))

static int devfreq_ltl_func(struct devfreq *df,
			    unsigned long *freq)
{
	struct devfreq_dev_status *stat;
	struct devfreq_ltl_data *d = df->data;
	int th_cap = DEFAULT_TH_CAP;
	int th_cap_short = DEFAULT_TH_CAP_SHORT;
	int th_cap_long = DEFAULT_TH_CAP_LONG;
	int cap;
	int err;

	err = devfreq_update_stats(df);
	if (err)
		return err;

	stat = &df->last_status;
	*freq = UINT_MAX;

	if (!d)
		goto check;
	if (d->th_cap)
		th_cap = d->th_cap;
	if (d->th_cap_short)
		th_cap_short = d->th_cap_short;
	if (d->th_cap_long)
		th_cap_long = d->th_cap_long;

	cap = (stat->total_time - stat->busy_time) / 1000;
	if (!cap)
		goto check;

	d->weighted_cap_long = weight(cap, 5, d->weighted_cap_long, 95);
	d->weighted_cap_short = weight(cap, 50, d->weighted_cap_short, 50);
	pr_debug("%s: cap=%d, cap_s=%d, cap_l=%d\n",
		__func__, cap, d->weighted_cap_short, d->weighted_cap_long);
	d->prev_cap = cap;

	if (cap < th_cap
	    && d->weighted_cap_short < th_cap_short
	    && d->weighted_cap_long < th_cap_long)
		*freq = 0;
check:
	if (df->min_freq && *freq < df->min_freq)
		*freq = df->min_freq;
	if (df->max_freq && *freq > df->max_freq)
		*freq = df->max_freq;

	return 0;
}

static void devfreq_ltl_data_reset(struct devfreq_ltl_data *ltl_data)
{
	ltl_data->weighted_cap_long = ltl_data->th_cap_long * 2;
	if (!ltl_data->weighted_cap_long)
		ltl_data->weighted_cap_long = DEFAULT_CAP_LONG;
}

static int devfreq_ltl_notifier_call(struct notifier_block *nb,
				     unsigned long event,
				     void *ptr)
{
	struct devfreq_freqs *freqs = (struct devfreq_freqs *)ptr;
	struct devfreq_ltl_data *ltl_data = container_of(nb, struct devfreq_ltl_data, nb);

	switch (event) {
	case DEVFREQ_POSTCHANGE:
		if (freqs->old < freqs->new) {
			devfreq_ltl_data_reset(ltl_data);
			pr_debug("%s: reset weighted_cap_long=%d\n", __func__, ltl_data->weighted_cap_long);
		}
		break;

	}
	return NOTIFY_DONE;
}

static int devfreq_ltl_handler(struct devfreq *devfreq,
			       unsigned int event,
			       void *data)
{
	struct devfreq_ltl_data *ltl_data = devfreq->data;
	struct device *dev = devfreq->dev.parent;
	int ret;

	switch (event) {
	case DEVFREQ_GOV_START:
		ltl_data->nb.notifier_call = devfreq_ltl_notifier_call;
		ret = devm_devfreq_register_notifier(dev, devfreq, &ltl_data->nb,
			DEVFREQ_TRANSITION_NOTIFIER);
		if (ret)
			return ret;
		devfreq_ltl_data_reset(ltl_data);

		devfreq_monitor_start(devfreq);
		break;

	case DEVFREQ_GOV_STOP:
		devfreq_monitor_stop(devfreq);
		devm_devfreq_unregister_notifier(dev, devfreq, &ltl_data->nb,
			DEVFREQ_TRANSITION_NOTIFIER);
		break;

	case DEVFREQ_GOV_INTERVAL:
		devfreq_interval_update(devfreq, (unsigned int *)data);
		break;

	case DEVFREQ_GOV_SUSPEND:
		devfreq_monitor_suspend(devfreq);
		break;

	case DEVFREQ_GOV_RESUME:
		devfreq_ltl_data_reset(ltl_data);
		devfreq_monitor_resume(devfreq);
		break;

	default:
		break;
	}

	return 0;
}

static struct devfreq_governor devfreq_ltl = {
	.name = "ltl",
	.immutable = 1,
	.get_target_freq = devfreq_ltl_func,
	.event_handler = devfreq_ltl_handler,
};

static int __init devfreq_ltl_init(void)
{
	return devfreq_add_governor(&devfreq_ltl);
}
subsys_initcall(devfreq_ltl_init);

static void __exit devfreq_ltl_exit(void)
{
	int ret;

	ret = devfreq_remove_governor(&devfreq_ltl);
	if (ret)
		pr_err("%s: failed remove governor %d\n", __func__, ret);

	return;
}
module_exit(devfreq_ltl_exit);
MODULE_LICENSE("GPL");
