/*
 * Realtek DDR Bandwidth Event
 *
 * Copyright (C) 2017-2019 Realtek Semiconductor Corporation
 * Copyright (C) 2017-2019 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/devfreq-event.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/atomic.h>
#include <soc/realtek/perfcnt.h>
#include <soc/realtek/dcsys.h>
#include <soc/realtek/dmc.h>

struct bw_event;

struct bw_perfcnt_ops {
	int (*set_conf)(struct bw_event *);
	int (*get_load)(struct bw_event *, unsigned long *, unsigned long *, u32);
};

struct bw_event {
	struct device *dev;
	struct perfcnt *pc;
	const struct bw_perfcnt_ops *ops;
	u32 has_dc1;
	struct devfreq_event_dev *edev;
	atomic_t start_cnt;
	struct notifier_block nb;
};

#define BYTE_PER_REQ   16
#define SEL_VO         0x00

static u32 bw_to_kbyte(u32 byte, u32 interval_ms)
{
	u64 val = byte;

	if (interval_ms) {
		val *= 1000;
		val /= interval_ms;
	}
	return (u32)val / 1024;
}

static int bw_dcsys_set_conf(struct bw_event *data)
{
	perfcnt_set_conf(data->pc, DCSYS_PERFCNT_ID_SYSH_0, SEL_VO | DCSYS_PROG_DCSEL_DC0);
	perfcnt_set_conf(data->pc, DCSYS_PERFCNT_ID_SYSH_1, SEL_VO | DCSYS_PROG_DCSEL_DC1);
	return 0;
}

static int bw_dcsys_get_load(struct bw_event *data,
			     unsigned long *load,
			     unsigned long *total,
			     u32 interval)

{

	struct perfcnt_data dc0;
	struct perfcnt_data dc0_vo;
	struct perfcnt_data dc1;
	struct perfcnt_data dc1_vo;
	int ret;

	*load = *total = 0;

	ret = perfcnt_get_data(data->pc, DCSYS_PERFCNT_ID_TOTAL_0, &dc0);
	if (!ret)
		*total += bw_to_kbyte(dc0.data[1] * BYTE_PER_REQ, interval);
	ret = perfcnt_get_data(data->pc, DCSYS_PERFCNT_ID_SYSH_0, &dc0_vo);
	if (!ret)
		*load += bw_to_kbyte(dc0_vo.data[3] * BYTE_PER_REQ, interval);

	if (!data->has_dc1)
		return 0;

	ret = perfcnt_get_data(data->pc, DCSYS_PERFCNT_ID_TOTAL_1, &dc1);
	if (!ret)
		*total += bw_to_kbyte(dc1.data[1] * BYTE_PER_REQ, interval);
	ret = perfcnt_get_data(data->pc, DCSYS_PERFCNT_ID_SYSH_1, &dc1_vo);
	if (!ret)
		*load += bw_to_kbyte(dc1_vo.data[3] * BYTE_PER_REQ, interval);
	return 0;
}

static const struct bw_perfcnt_ops bw_dcsys_ops = {
	.set_conf = bw_dcsys_set_conf,
	.get_load = bw_dcsys_get_load,
};

static int bw_dmc_get_load(struct bw_event *data,
			   unsigned long *load,
			   unsigned long *total,
			   u32 interval)
{
	struct perfcnt_data dmc_cpu;
	struct perfcnt_data dmc_gpu;
	int ret;

	*load = *total = 0;

	ret = perfcnt_get_data(data->pc, DMC_PERFCNT_ID_CPU, &dmc_cpu);
	if (!ret)
		*total += bw_to_kbyte(dmc_cpu.data[0] * BYTE_PER_REQ, interval);
	ret = perfcnt_get_data(data->pc, DMC_PERFCNT_ID_GPU, &dmc_gpu);
	if (!ret)
		*total += bw_to_kbyte(dmc_gpu.data[0] * BYTE_PER_REQ, interval);
	return 0;
}

static const struct bw_perfcnt_ops bw_dmc_ops = {
	.get_load = bw_dmc_get_load,
};

static int bw_event_start(struct bw_event *data)
{
	int ret = 0;

	if (atomic_inc_return(&data->start_cnt) != 1)
		return -EBUSY;

	if (data->ops->set_conf)
		data->ops->set_conf(data);

	ret = perfcnt_start(data->pc);
	if (ret)
		pr_warn("perfcnt_start() returns %d\n", ret);
	return 0;
}

static int bw_event_stop(struct bw_event *data)
{
	int ret;

	if (atomic_dec_return(&data->start_cnt) != 0)
		return -EBUSY;

	ret = perfcnt_stop(data->pc);
	if (ret)
		pr_warn("perfcnt_stop() returns %d\n", ret);
	return 0;
}

static int bw_evnet_perfcnt_notifier(struct notifier_block *nb,
				     unsigned long action,
				     void *d)
{
	struct bw_event *data = container_of(nb, struct bw_event, nb);
	struct perfcnt_change_data *pccd = d;

	switch (action) {
	case PERFCNT_EVENT_PRE_CHANGE:
		if (pccd->old_pc != data->pc)
			break;
		dev_info(data->dev, "perfcnt suspend\n");
		bw_event_stop(data);
		break;
	case PERFCNT_EVENT_POST_CHANGE:
		if (pccd->new_pc != data->pc)
			break;
		dev_info(data->dev, "perfcnt resume\n");
		bw_event_start(data);
		break;
	}
	return NOTIFY_OK;
}

static int bw_event_get_event(struct devfreq_event_dev *edev,
			      struct devfreq_event_data *edata)
{
	struct bw_event *data = edev->desc->driver_data;
	int ret;
	u32 interval_ms;

	edata->load_count  = 0;
	edata->total_count = 0;

	ret = bw_event_stop(data);
	if (ret)
		return ret == -EBUSY ? 0 : ret;

	perfcnt_last_duration(data->pc, &interval_ms);
	data->ops->get_load(data, &edata->load_count, &edata->total_count,
		interval_ms);
	return 0;
}

static int bw_event_set_event(struct devfreq_event_dev *edev)
{
	struct bw_event *data = edev->desc->driver_data;
	int ret;

	ret = bw_event_start(data);
	if (ret == -EBUSY)
		return 0;
	return ret;
}

static int bw_event_enable(struct devfreq_event_dev *edev)
{
	struct bw_event *data = edev->desc->driver_data;
	int ret = 0;

	perfcnt_request(data->pc);

	//ret = bw_event_start(data);
	//if (ret == -EBUSY)
	//	return 0;
	return ret;
}

static int bw_event_disable(struct devfreq_event_dev *edev)
{
	struct bw_event *data = edev->desc->driver_data;
	int ret = 0;

	perfcnt_release(data->pc);

	//ret = bw_event_stop(data);
	//if (ret == -EBUSY)
	//	return 0;
	return ret;
}

static int bw_event_reset(struct devfreq_event_dev *edev)
{
	struct bw_event *data = edev->desc->driver_data;

	atomic_set(&data->start_cnt, 0);
	return 0;
}

static const struct devfreq_event_ops bw_event_ops = {
	.enable    = bw_event_enable,
	.disable   = bw_event_disable,
	.set_event = bw_event_set_event,
	.get_event = bw_event_get_event,
	.reset     = bw_event_reset,
};

static const struct of_device_id bw_event_ids[];

static int bw_event_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	const struct of_device_id *id;
	const struct bw_perfcnt_ops *ops;
	struct devfreq_event_desc *desc;

	struct bw_event *data;
	int ret;

	dev_info(dev, "%s\n", __func__);
	if (!of_device_is_compatible(np, "devfreq-event"))
		return -EINVAL;

	id = of_match_node(bw_event_ids, np);
	if (id)
		ops = id->data;
	if (!id || !ops)
		return -EINVAL;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	desc = devm_kzalloc(dev, sizeof(*desc),GFP_KERNEL);
	if (!desc)
		return -ENOMEM;

	desc->name = np->name;
	desc->ops = &bw_event_ops;
	desc->driver_data = data;

	atomic_set(&data->start_cnt, 0);
	data->dev = dev;
	data->ops = ops;
	data->pc = perfcnt_get(dev, NULL);
	if (IS_ERR(data->pc)) {
		ret = PTR_ERR(data->pc);
		dev_err(dev, "perfcnt_get() returns %d\n", ret);
		return ret;
	}

	data->nb.notifier_call = bw_evnet_perfcnt_notifier;
	perfcnt_register_notifier(data->pc, &data->nb);

	data->edev = devfreq_event_add_edev(&pdev->dev, desc);
	if (IS_ERR(data->edev)) {
		ret = PTR_ERR(data->edev);
		goto error;
	}
	return 0;

error:
	perfcnt_put(data->pc);
	return ret;
}

static const struct of_device_id bw_event_ids[] = {
	{ .compatible = "realtek,bw-event-dcsys", .data = &bw_dcsys_ops, },
	{ .compatible = "realtek,bw-event-dmc", .data = &bw_dmc_ops, },
	{}
};

static struct platform_driver bw_event_driver = {
	.driver = {
		.name  = "rtk-bw-event",
		.of_match_table = bw_event_ids,
	},
	.probe = bw_event_probe,
};

static int __init bw_event_init(void)
{
	return platform_driver_register(&bw_event_driver);
}
device_initcall(bw_event_init);

