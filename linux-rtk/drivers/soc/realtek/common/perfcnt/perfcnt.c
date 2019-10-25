/*
 * Realtek Perfcnt Framework
 *
 * Copyright (C) 2017-2019 Realtek Semiconductor Corporation
 * Copyright (C) 2017-2019 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/list.h>
#include <linux/of.h>
#include <linux/mutex.h>
#include <linux/jiffies.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <soc/realtek/perfcnt.h>

static LIST_HEAD(perfcnt_list);
static DEFINE_MUTEX(perfcnt_lock);

int perfcnt_register(struct perfcnt_device *pcdev)
{
	if (!pcdev || !pcdev->dev || !pcdev->np || !pcdev->ops)
		return -EINVAL;

	if (!pcdev->ops->start || !pcdev->ops->stop || !pcdev->ops->get_data)
		return -EINVAL;

	mutex_lock(&perfcnt_lock);
	list_add(&pcdev->list, &perfcnt_list);
	mutex_unlock(&perfcnt_lock);

	INIT_LIST_HEAD(&pcdev->list_idle);
	INIT_LIST_HEAD(&pcdev->list_suspend);
	BLOCKING_INIT_NOTIFIER_HEAD(&pcdev->notifier);
	return 0;
}
EXPORT_SYMBOL_GPL(perfcnt_register);

void perfcnt_unregister(struct perfcnt_device *pcdev)
{
	if (!pcdev)
		return;

	WARN_ON(!list_empty(&pcdev->list_idle));
	WARN_ON(!list_empty(&pcdev->list_suspend));

	mutex_lock(&perfcnt_lock);
	list_del(&pcdev->list);
	mutex_unlock(&perfcnt_lock);
}
EXPORT_SYMBOL_GPL(perfcnt_unregister);

static struct perfcnt_device *of_perfcnt_device_get(struct device_node *np,
						    const char *id)
{
	int index = 0;
	struct perfcnt_device *pos;
	struct device_node *node;

	if (id)
		index = of_property_match_string(np, "perfcnt-names", id);

	node = of_parse_phandle(np, "perfcnts", index);
	if (!node)
		return ERR_PTR(-EINVAL);

	mutex_lock(&perfcnt_lock);
	list_for_each_entry(pos, &perfcnt_list, list)
		if (pos->np == node) {
			mutex_unlock(&perfcnt_lock);
			return pos;
		}
	mutex_unlock(&perfcnt_lock);
	return ERR_PTR(-ENODEV);
}


struct perfcnt *perfcnt_get(struct device *dev, const char *id)
{
	struct perfcnt_device *pcdev;
	struct perfcnt *pc;

	pcdev = of_perfcnt_device_get(dev->of_node, id);
	if (IS_ERR(pcdev))
		return ERR_CAST(pcdev);

	pc = kzalloc(sizeof(*pc), GFP_KERNEL);
	if (!pc)
		return ERR_PTR(-ENOMEM);

	pc->pcdev = pcdev;
	pc->dev   = dev;
	list_add(&pc->list, &pcdev->list_idle);
	return pc;
}
EXPORT_SYMBOL_GPL(perfcnt_get);

void perfcnt_put(struct perfcnt *pc)
{
	if (!pc)
		return;

	list_del(&pc->list);
	kfree(pc);
}
EXPORT_SYMBOL_GPL(perfcnt_put);

int perfcnt_start(struct perfcnt *pc)
{
	struct perfcnt_device *pcdev = pc->pcdev;

	if (pcdev->cur_pc != pc)
		return -EBUSY;

	pcdev->is_start = 1;
	pcdev->time_begin = get_jiffies_64();
	return pcdev->ops->start(pcdev);
}
EXPORT_SYMBOL_GPL(perfcnt_start);

int perfcnt_stop(struct perfcnt *pc)
{
	struct perfcnt_device *pcdev = pc->pcdev;

	if (pcdev->cur_pc != pc)
		return -EBUSY;

	pcdev->is_start = 0;
	pcdev->time_end = get_jiffies_64();
	return pcdev->ops->stop(pcdev);
}
EXPORT_SYMBOL_GPL(perfcnt_stop);

int perfcnt_last_duration(struct perfcnt *pc, u32 *period_ms)
{
	struct perfcnt_device *pcdev = pc->pcdev;

	if (pcdev->cur_pc != pc)
		return -EBUSY;

	if (pcdev->is_start)
		return -EINVAL;
	if (pcdev->time_begin == 0 && pcdev->time_end == 0)
		return -EINVAL;
	*period_ms = jiffies_to_msecs(pcdev->time_end - pcdev->time_begin);
	return 0;
}
EXPORT_SYMBOL_GPL(perfcnt_last_duration);

int perfcnt_reset(struct perfcnt *pc)
{
	struct perfcnt_device *pcdev = pc->pcdev;

	if (pcdev->cur_pc != pc)
		return -EBUSY;

	pcdev->is_start = 0;
	if (pcdev->ops->reset)
		return pcdev->ops->reset(pcdev);
	return -EINVAL;
}
EXPORT_SYMBOL_GPL(perfcnt_reset);

int perfcnt_set_conf(struct perfcnt *pc, u32 id, u32 conf)
{
	struct perfcnt_device *pcdev = pc->pcdev;

	if (pcdev->cur_pc != pc)
		return -EPERM;

	if (pcdev->ops->set_conf)
		return pcdev->ops->set_conf(pcdev, id, conf);
	return -EINVAL;
}
EXPORT_SYMBOL_GPL(perfcnt_set_conf);

int perfcnt_get_data(struct perfcnt *pc, u32 id, struct perfcnt_data *data)
{
	struct perfcnt_device *pcdev = pc->pcdev;

	if (pcdev->cur_pc != pc)
		return -EPERM;
	return pcdev->ops->get_data(pcdev, id, data);
}
EXPORT_SYMBOL_GPL(perfcnt_get_data);

int perfcnt_register_notifier(struct perfcnt *pc, struct notifier_block *nb)
{
	struct perfcnt_device *pcdev = pc->pcdev;

	return blocking_notifier_chain_register(&pcdev->notifier, nb);
}

EXPORT_SYMBOL_GPL(perfcnt_register_notifier);

int perfcnt_unregister_notifier(struct perfcnt *pc, struct notifier_block *nb)
{
	struct perfcnt_device *pcdev = pc->pcdev;

	return blocking_notifier_chain_unregister(&pcdev->notifier, nb);
}
EXPORT_SYMBOL_GPL(perfcnt_unregister_notifier);

static int _notifier_call_chain(struct perfcnt_device *pcdev,
				unsigned long event,
				void *data)
{
	return blocking_notifier_call_chain(&pcdev->notifier, event, data);
}

static int perfcnt_device_swap_perfcnts(struct perfcnt_device *pcdev,
				       struct perfcnt *new_pc,
				       struct perfcnt *old_pc)
{
	struct perfcnt_change_data pccd;
	int ret;

	pccd.old_pc = old_pc;
	pccd.new_pc = new_pc;
	ret = _notifier_call_chain(pcdev, PERFCNT_EVENT_PRE_CHANGE, &pccd);
	if (ret < 0)
		pr_warn("%s: PERFCNT_EVENT_PRE_CHANGE returns %d\n", __func__, ret);

	if (old_pc && pcdev->is_start)
		perfcnt_stop(old_pc);

	pcdev->cur_pc = new_pc;
	if (old_pc)
		list_move(&old_pc->list, &pcdev->list_suspend);
	if (new_pc)
		list_move(&new_pc->list, &pcdev->list_idle);

	ret = _notifier_call_chain(pcdev, PERFCNT_EVENT_POST_CHANGE, &pccd);
	if (ret < 0)
		pr_warn("%s: PERFCNT_EVENT_POST_CHANGE returns %d\n", __func__, ret);
	return 0;
}


int perfcnt_request(struct perfcnt *new_pc)
{
	struct perfcnt_device *pcdev = new_pc->pcdev;
	struct perfcnt *old_pc = pcdev->cur_pc;

	if (WARN_ON(new_pc == pcdev->cur_pc))
		return -EINVAL;

	return perfcnt_device_swap_perfcnts(pcdev, new_pc, old_pc);
}
EXPORT_SYMBOL_GPL(perfcnt_request);

int perfcnt_release(struct perfcnt *old_pc)
{
	struct perfcnt_device *pcdev = old_pc->pcdev;
	struct perfcnt *new_pc = NULL;

	if (WARN_ON(old_pc != pcdev->cur_pc))
		return -EINVAL;

	if (!list_empty(&pcdev->list_suspend))
		new_pc = list_first_entry(&pcdev->list_suspend, struct perfcnt, list);

	return perfcnt_device_swap_perfcnts(pcdev, new_pc, old_pc);
}
EXPORT_SYMBOL_GPL(perfcnt_release);

int perfcnt_suspend(struct perfcnt_device *pcdev)
{
	if (!pcdev->cur_pc)
		return 0;
	return perfcnt_release(pcdev->cur_pc);
}

int perfcnt_resume(struct perfcnt_device *pcdev)
{
	struct perfcnt *new_pc = NULL;

	if (!list_empty(&pcdev->list_suspend))
		new_pc = list_first_entry(&pcdev->list_suspend, struct perfcnt, list);
	if (new_pc)
		return perfcnt_request(new_pc);
	return 0;
}
