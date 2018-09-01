/*
 * Power Control core & APIs
 *
 * Copyright (C) 2016-2017 Realtek Semiconductor Corporation
 * Copyright (C) 2016-2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/spinlock.h>
#include "pwrctrl_driver.h"

DEFINE_MUTEX(power_control_list_lock);
LIST_HEAD(power_control_list);

const char *power_control_get_name(struct power_control *pctrl)
{
	if (!pctrl)
		return NULL;
	return pctrl->name;
}
EXPORT_SYMBOL(power_control_get_name);

int power_control_power_on(struct power_control *pctrl)
{
	int ret = 0;

	if (!pctrl)
		return -EINVAL;

	if (pctrl->ops->power_on)
		ret = pctrl->ops->power_on(pctrl);

	__power_control_stat_update(pctrl, POWER_CONTROL_ACT_CALL_ON);
	return ret;
}
EXPORT_SYMBOL(power_control_power_on);

int power_control_power_off(struct power_control *pctrl)
{
	int ret = 0;

	if (!pctrl)
		return -EINVAL;

	if (pctrl->ops->power_off)
		ret = pctrl->ops->power_off(pctrl);

	__power_control_stat_update(pctrl, POWER_CONTROL_ACT_CALL_OFF);
	return ret;
}
EXPORT_SYMBOL(power_control_power_off);

int power_control_is_powered_on(struct power_control *pctrl)
{
	if (!pctrl)
		return -EINVAL;

	if (pctrl->ops->is_powered_on)
		return pctrl->ops->is_powered_on(pctrl);

	return -EINVAL;
}
EXPORT_SYMBOL(power_control_is_powered_on);

struct power_control *__power_control_get(const char *name)
{
	struct power_control *ctrl = NULL;
	struct list_head *it = NULL;

	list_for_each(it, &power_control_list) {
		ctrl = to_power_control(it);
		if (!strcmp(ctrl->name, name))
			return ctrl;
	}

	return NULL;
}
EXPORT_SYMBOL(__power_control_get);

struct power_control *power_control_get(const char *name)
{
	struct power_control *ctrl;

	__list_lock();
	ctrl = __power_control_get(name);
	__list_unlock();
	return ctrl;
}
EXPORT_SYMBOL(power_control_get);

struct of_power_control_provider {
	struct list_head list;
	struct device_node *node;
	power_control_xlate_t xlate;
	void *data;
};

static LIST_HEAD(of_power_control_providers);
static DEFINE_MUTEX(of_power_control_provider_lock);

struct power_control *of_power_control_xlate_simple(
	struct of_phandle_args *args, void *data)
{
	if (args->args_count != 0)
		return ERR_PTR(-EINVAL);
	return data;
}

struct power_control *of_power_control_xlate_onecell(
	struct of_phandle_args *args, void *data)
{
	struct power_control_onecell_data *ctrl_data = data;
	unsigned int idx = args->args[0];

	if (args->args_count != 1)
		return ERR_PTR(-EINVAL);

	if (idx > ctrl_data->num_controls) {
		pr_err("%s: invalid power control index %u\n", __func__, idx);
		return ERR_PTR(-EINVAL);
	}

	if (!ctrl_data->controls[idx])
		return ERR_PTR(-ENOENT);

	return ctrl_data->controls[idx];
}

int of_power_control_add_provider(struct device_node *np,
	power_control_xlate_t xlate, void *data)
{
	struct of_power_control_provider *pp;

	pp = kzalloc(sizeof(*pp), GFP_KERNEL);
	if (!pp)
		return -ENOMEM;

	pp->node = np;
	pp->data = data;
	pp->xlate = xlate;

	mutex_lock(&of_power_control_provider_lock);
	list_add(&pp->list, &of_power_control_providers);
	mutex_unlock(&of_power_control_provider_lock);
	return 0;
}

void of_power_control_del_provider(struct device_node *np)
{
	struct of_power_control_provider *pp;

	mutex_lock(&of_power_control_provider_lock);
	list_for_each_entry(pp, &of_power_control_providers, list) {
		if (pp->node == np) {
			list_del(&pp->list);
			of_node_put(pp->node);
			kfree(pp);
			break;
		}
	}
	mutex_unlock(&of_power_control_provider_lock);
}

struct power_control *of_power_control_get_from_provider(
	struct of_phandle_args *args)
{
	struct power_control *ctrl = ERR_PTR(-ENOENT);
	struct of_power_control_provider *provider;


	mutex_lock(&of_power_control_provider_lock);
	list_for_each_entry(provider, &of_power_control_providers, list) {
		if (provider->node == args->np)
			ctrl = provider->xlate(args, provider->data);
		if (!IS_ERR(ctrl))
			break;
	}
	mutex_unlock(&of_power_control_provider_lock);

	return ctrl;
}

struct power_control *__of_power_control_get_by_index(struct device_node *node,
	int index)
{
	struct of_phandle_args args;
	int ret;

	ret = of_parse_phandle_with_args(node, "powerctrls", "#powerctrl-cells",
		index, &args);
	if (ret)
		return ERR_PTR(ret);

	return of_power_control_get_from_provider(&args);
}
EXPORT_SYMBOL(__of_power_control_get_by_index);

struct power_control *of_power_control_get_by_index(struct device_node *node,
	int index)
{
	struct power_control *ctrl = NULL;

	__list_lock();
	ctrl = __of_power_control_get_by_index(node, index);
	__list_unlock();

	return ctrl;
}
EXPORT_SYMBOL(of_power_control_get_by_index);

struct power_control *__of_power_control_get(struct device_node *node,
	const char *id)
{
	int index = 0;

	if (id)
		index = of_property_match_string(node, "powerctrl-names", id);

	return __of_power_control_get_by_index(node, index);
}
EXPORT_SYMBOL(__of_power_control_get);

struct power_control *of_power_control_get(struct device_node *node,
	const char *id)
{
	int index = 0;

	if (id)
		index = of_property_match_string(node, "powerctrl-names", id);

	return of_power_control_get_by_index(node, index);
}
EXPORT_SYMBOL(of_power_control_get);

bool power_control_is_match(const struct power_control *a,
	const struct power_control *b)
{
	return a == b;
}
EXPORT_SYMBOL(power_control_is_match);

int power_control_register(struct power_control *pctrl)
{
	__list_lock();
	list_add(&pctrl->list, &power_control_list);
	__list_unlock();

	if (pctrl->of_node)
		of_power_control_add_provider(pctrl->of_node,
			of_power_control_xlate_simple, pctrl);

	return 0;
}
EXPORT_SYMBOL(power_control_register);

void power_control_unregister(struct power_control *pctrl)
{
	if (pctrl->of_node)
		of_power_control_del_provider(pctrl->of_node);

	__list_lock();
	list_del(&pctrl->list);
	__list_unlock();
}
EXPORT_SYMBOL(power_control_unregister);
