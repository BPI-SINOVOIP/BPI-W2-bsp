/*
 * Power Control core & APIs
 *
 * Copyright (C) 2016-2017,2019 Realtek Semiconductor Corporation
 * Copyright (C) 2016-2017,2019 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define pr_fmt(fmt) "power_control: " fmt

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/spinlock.h>
#include <linux/mutex.h>
#include <linux/debugfs.h>
#include <linux/notifier.h>
#include <linux/atomic.h>
#include <soc/realtek/power-control.h>
#include "pwrctrl_driver.h"

MODULE_LICENSE("GPL");

static DEFINE_MUTEX(power_control_list_lock);
static LIST_HEAD(power_control_list);
static int power_control_add_debugfs(struct power_control *pwrctrl);
static void power_control_del_debugfs(struct power_control *pwrctrl);


int power_control_register_notifier(struct power_control *pwrctrl,
				    struct notifier_block *nb)
{
	return raw_notifier_chain_register(&pwrctrl->notifier_head, nb);
}
EXPORT_SYMBOL_GPL(power_control_register_notifier);

void power_control_unregister_notifier(struct power_control *pwrctrl,
				       struct notifier_block *nb)
{
	raw_notifier_chain_unregister(&pwrctrl->notifier_head, nb);
}
EXPORT_SYMBOL_GPL(power_control_unregister_notifier);

int __power_control_notify(struct power_control *pwrctrl, int action)
{
	return raw_notifier_call_chain(&pwrctrl->notifier_head, action, pwrctrl);
}
EXPORT_SYMBOL_GPL(__power_control_notify);

int power_control_power_on(struct power_control *pwrctrl)
{
	int ret = 0;
	int act;

	if (!pwrctrl)
		return -EINVAL;

	if (pwrctrl->flags & POWER_CONTROL_FLAG_SHARED_POWER) {
		pr_debug("%s: before on ref:%d\n", pwrctrl->name, atomic_read(&pwrctrl->power_cnt));
		if (atomic_inc_return(&pwrctrl->power_cnt) != 1)
			return 0;
	}
	__power_control_notify(pwrctrl, POWER_CONTROL_ACTION_PRE_POWER_ON);
	if (pwrctrl->ops->power_on)
		ret = pwrctrl->ops->power_on(pwrctrl);

	if (ret < 0)
		act = POWER_CONTROL_ACTION_POWER_ON_ABORT;
	else if (ret == 1)
		act = POWER_CONTROL_ACTION_POWER_ON_IGNORE;
	else
		act = POWER_CONTROL_ACTION_POST_POWER_ON;

	__power_control_notify(pwrctrl, act);
	return ret;
}
EXPORT_SYMBOL_GPL(power_control_power_on);

int power_control_power_off(struct power_control *pwrctrl)
{
	int ret = 0;

	if (!pwrctrl)
		return -EINVAL;

	if (pwrctrl->flags & POWER_CONTROL_FLAG_SHARED_POWER) {
		pr_debug("%s: before off ref:%d\n", pwrctrl->name, atomic_read(&pwrctrl->power_cnt));
		if (atomic_dec_return(&pwrctrl->power_cnt) != 0)
			return 0;
	}

	/* should be notify by implementation */
	if (!(pwrctrl->flags & POWER_CONTROL_FLAG_ASYNC_POWER_OFF))
		__power_control_notify(pwrctrl, POWER_CONTROL_ACTION_PRE_POWER_OFF);

	if (pwrctrl->ops->power_off)
		ret = pwrctrl->ops->power_off(pwrctrl);

	/* should be notify by implementation */
	if (!(pwrctrl->flags & POWER_CONTROL_FLAG_ASYNC_POWER_OFF))
		__power_control_notify(pwrctrl, POWER_CONTROL_ACTION_POST_POWER_OFF);
	return ret;
}
EXPORT_SYMBOL_GPL(power_control_power_off);

int __power_control_notify_power_off_start(struct power_control *pwrctrl)
{
	__power_control_notify(pwrctrl, POWER_CONTROL_ACTION_PRE_POWER_OFF);
	return 0;
}
EXPORT_SYMBOL_GPL(__power_control_notify_power_off_start);

int __power_control_notify_power_off_done(struct power_control *pwrctrl)
{
	__power_control_notify(pwrctrl, POWER_CONTROL_ACTION_POST_POWER_OFF);
	return 0;
}
EXPORT_SYMBOL_GPL(__power_control_notify_power_off_done);

int power_control_is_powered_on(struct power_control *pwrctrl)
{
	if (!pwrctrl)
		return -EINVAL;

	if (pwrctrl->ops->is_powered_on)
		return pwrctrl->ops->is_powered_on(pwrctrl);

	return -EINVAL;
}
EXPORT_SYMBOL_GPL(power_control_is_powered_on);

int power_control_init(struct power_control *pwrctrl)
{
	if (WARN_ON(!pwrctrl))
		return -ENODEV;

	if (pwrctrl->ops->init)
		return pwrctrl->ops->init(pwrctrl);
	return -EINVAL;
}
EXPORT_SYMBOL_GPL(power_control_init);

int power_control_get_internal(struct power_control *pwrctrl)
{
	atomic_inc(&pwrctrl->usage_cnt);
	return 0;
}

void power_control_put_internal(struct power_control *pwrctrl)
{
	atomic_dec(&pwrctrl->usage_cnt);
}

static struct power_control *__power_control_get(const char *name)
{
	struct power_control *ctrl = NULL;

	list_for_each_entry(ctrl, &power_control_list, list) {
		if (!strcmp(ctrl->name, name))
			return ctrl;
	}

	return NULL;
}

struct power_control *power_control_get(const char *name)
{
	struct power_control *ctrl;

	mutex_lock(&power_control_list_lock);
	ctrl = __power_control_get(name);
	mutex_unlock(&power_control_list_lock);

	if (!ctrl)
		return ctrl;

	atomic_inc(&ctrl->usage_cnt);
	return ctrl;
}
EXPORT_SYMBOL_GPL(power_control_get);

struct of_power_control_provider {
	struct list_head list;
	struct device_node *node;
	power_control_xlate_t xlate;
	void *data;
};

static LIST_HEAD(of_power_control_providers);
static DEFINE_MUTEX(of_power_control_provider_lock);

struct power_control *of_power_control_xlate_simple(struct of_phandle_args *args,
						    void *data)
{
	if (args->args_count != 0)
		return ERR_PTR(-EINVAL);
	return data;
}

struct power_control *of_power_control_xlate_onecell(struct of_phandle_args *args,
						     void *data)
{
	struct power_control_onecell_data *ctrl_data = data;
	unsigned int idx = args->args[0];

	if (args->args_count != 1)
		return ERR_PTR(-EINVAL);

	if (idx > ctrl_data->num_controls) {
		pr_err("%s: invalid index %u\n", __func__, idx);
		return ERR_PTR(-EINVAL);
	}

	if (!ctrl_data->controls[idx])
		return ERR_PTR(-ENOENT);

	return ctrl_data->controls[idx];
}

int of_power_control_add_provider(struct device_node *np,
				  power_control_xlate_t xlate,
				  void *data)
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

struct power_control *of_power_control_get_from_provider(struct of_phandle_args *args)
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

struct power_control *of_power_control_get_by_index(struct device_node *node,
						    int index)
{
	struct power_control *ctrl = NULL;

	mutex_lock(&power_control_list_lock);
	ctrl = __of_power_control_get_by_index(node, index);
	mutex_unlock(&power_control_list_lock);

	if (IS_ERR(ctrl))
		return ctrl;

	atomic_inc(&ctrl->usage_cnt);
	return ctrl;
}
EXPORT_SYMBOL_GPL(of_power_control_get_by_index);

struct power_control *of_power_control_get(struct device_node *node,
					   const char *id)
{
	int index = 0;

	if (id)
		index = of_property_match_string(node, "powerctrl-names", id);

	return of_power_control_get_by_index(node, index);
}
EXPORT_SYMBOL_GPL(of_power_control_get);

void power_control_put(struct power_control *pwrctrl)
{
	atomic_dec(&pwrctrl->usage_cnt);
}
EXPORT_SYMBOL_GPL(power_control_put);

int power_control_register(struct power_control *pwrctrl)
{
	int ret __maybe_unused;

	if (WARN_ON(!pwrctrl->ops))
		return -EINVAL;

	if (WARN_ON(!pwrctrl->name))
		return -EINVAL;

	mutex_lock(&power_control_list_lock);
	list_add(&pwrctrl->list, &power_control_list);
	mutex_unlock(&power_control_list_lock);

	atomic_set(&pwrctrl->usage_cnt, 0);
	atomic_set(&pwrctrl->power_cnt, 0);
#ifdef CONFIG_POWER_CONTROL_DEBUGFS
	ret = power_control_add_debugfs(pwrctrl);
	if (ret)
		pr_warn("%s: %s: failed to add debugfs: %d\n", pwrctrl->name,
			__func__, ret);
#endif
	RAW_INIT_NOTIFIER_HEAD(&pwrctrl->notifier_head);

	return 0;
}
EXPORT_SYMBOL_GPL(power_control_register);

void power_control_unregister(struct power_control *pwrctrl)
{
	WARN_ON(atomic_read(&pwrctrl->usage_cnt) != 0);

#ifdef CONFIG_POWER_CONTROL_DEBUGFS
	power_control_del_debugfs(pwrctrl);
#endif

	mutex_lock(&power_control_list_lock);
	list_del(&pwrctrl->list);
	mutex_unlock(&power_control_list_lock);
}
EXPORT_SYMBOL_GPL(power_control_unregister);

static bool power_control_ignore_unused;
static int __init power_control_ignore_unused_setup(char *__unused)
{
	power_control_ignore_unused = true;
	return 0;
}
__setup("power_control_ignore_unused", power_control_ignore_unused_setup);

static int power_control_power_off_unused(void)
{
	struct power_control *ctrl = NULL;

	if (power_control_ignore_unused) {
		pr_warn("Not disabling unused power controls\n");
		return 0;
	}

	list_for_each_entry(ctrl, &power_control_list, list) {
		if (ctrl->flags & POWER_CONTROL_FLAG_IGNORE_UNUSED)
			continue;
		if (atomic_read(&ctrl->usage_cnt) != 0)
			continue;

		if (ctrl->ops->power_off_unused)
			ctrl->ops->power_off_unused(ctrl);
		else if (ctrl->ops->power_off)
			ctrl->ops->power_off(ctrl);
	}
	return 0;
}
late_initcall_sync(power_control_power_off_unused);

#ifdef CONFIG_POWER_CONTROL_DEBUGFS
static struct dentry *power_control_root;

static int power_control_summary_show(struct seq_file *s, void *data)
{
	struct power_control *ctrl;
	char pow_str[20];

	seq_printf(s, "%-28s %-9s\n", "POWER_CONTROL_NAME", "STATE");

	mutex_lock(&power_control_list_lock);

	list_for_each_entry(ctrl, &power_control_list, list) {
		int is_powered = power_control_is_powered_on(ctrl);

		if (is_powered < 0)
			snprintf(pow_str, sizeof(pow_str), "ERRNO(%d)",
				is_powered);
		else
			strncpy(pow_str, is_powered ? "ON" : "OFF",
				sizeof(pow_str));

		seq_printf(s, "%-28s %-9s\n", ctrl->name, pow_str);
	}

	mutex_unlock(&power_control_list_lock);

	return 0;

}

static int power_control_summary_open(struct inode *inode, struct file *file)
{
	return single_open(file, power_control_summary_show, NULL);
}

static const struct file_operations power_control_summary_ops = {
	.owner   = THIS_MODULE,
	.open    = power_control_summary_open,
	.read    = seq_read,
	.release = single_release,
};

static int __init power_control_debugfs_arch_init(void)
{
	power_control_root = debugfs_create_dir("power_control", NULL);
	if (!power_control_root) {
		pr_warn("%s: failed to init debugfs\n", __func__);
		return 0;
	}
	debugfs_create_file("power_control_summary", 0444,
		power_control_root, NULL, &power_control_summary_ops);
	return 0;
}
arch_initcall(power_control_debugfs_arch_init);

static int power_control_power_set(void *data, u64 val)
{
	struct power_control *pwrctrl = data;
	int is_powered = power_control_is_powered_on(pwrctrl);
	int ret = 0;

	if (val == 1 && is_powered == 0)
		power_control_power_on(pwrctrl);
	else if (val == 0 && is_powered == 1)
		power_control_power_off(pwrctrl);
	else
		ret = -EINVAL;
	return ret;
}
static int power_control_power_get(void *data, u64 *val)
{
	struct power_control *pwrctrl = data;
	int is_powered = power_control_is_powered_on(pwrctrl);

	*val = is_powered;
	return is_powered < 0 ? -EINVAL : 0;
}
DEFINE_SIMPLE_ATTRIBUTE(power_control_power_fops,
			power_control_power_get,
			power_control_power_set,
			"%lld\n");

static int power_control_add_debugfs(struct power_control *pwrctrl)
{
	struct dentry *d;

	if (!power_control_root)
		return -ENOENT;

	pwrctrl->debugfs = debugfs_create_dir(pwrctrl->name, power_control_root);
	if (!pwrctrl->debugfs)
		return -ENOMEM;

	d = debugfs_create_file("power", 0644, pwrctrl->debugfs, pwrctrl,
		&power_control_power_fops);
	if (!d)
		return -ENOMEM;
	return 0;
}

static void power_control_del_debugfs(struct power_control *pwrctrl)
{
	if (!pwrctrl->debugfs)
		return;
	debugfs_remove_recursive(pwrctrl->debugfs);
}
#endif


