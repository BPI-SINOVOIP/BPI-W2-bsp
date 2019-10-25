/*
 * Generic Power Control as Power Doamin
 *
 * Copyright (C) 2017-2019 Realtek Semiconductor Corporation
 * Copyright (C) 2017-2019 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/of_address.h>
#include <linux/pm_runtime.h>
#include <linux/pm_domain.h>
#include <soc/realtek/power-control.h>
#include "pwrctrl_driver.h"
#include "pwrctrl-pd.h"

static LIST_HEAD(pm_list);
static ATOMIC_NOTIFIER_HEAD(pm_notifier_list);

static int pwrctrl_pd_power_on(struct generic_pm_domain *pd)
{
	struct pwrctrl_pd *core = pd_to_pwrctrl_pd(pd);

	pr_debug("%s: %s\n", pd->name, __func__);
	power_control_power_on(&core->pc);

	return 0;
}

static int pwrctrl_pd_power_off(struct generic_pm_domain *pd)
{
	struct pwrctrl_pd *core = pd_to_pwrctrl_pd(pd);

	pr_debug("%s: %s\n", pd->name, __func__);
	power_control_power_off(&core->pc);

	return 0;
}

static int pwrctrl_pd_attach_dev(struct generic_pm_domain *pd,
				 struct device *dev)
{
	pr_debug("%s: attach %s %s\n", pd->name,
		dev_driver_string(dev), dev_name(dev));
	return 0;
}

static void pwrctrl_pd_detach_dev(struct generic_pm_domain *pd,
				  struct device *dev)
{
	pr_debug("%s: detach %s %s\n", pd->name,
		dev_driver_string(dev), dev_name(dev));
}

static int  pwrctrl_pd_power_notifier(struct notifier_block *nb,
				      unsigned long action,
				      void *unused)
{
	struct pwrctrl_pd *core = container_of(nb, struct pwrctrl_pd, debug_nb);

	if (action != RTK_PD_PM_PREPARE && action != RTK_PD_PM_SUSPEND_NOIRQ)
		return NOTIFY_DONE;

	pr_info("%s: %s: power_state=%d\n", core->pd.name, __func__,
		power_control_is_powered_on(&core->pc));
	return NOTIFY_DONE;
}

void pwrctrl_pd_init(struct device *dev,
		     struct pwrctrl_pd *pd,
		     const struct pwrctrl_pd_initdata *data)
{
	int is_off = 1;

	/* init */
	pd->dev = dev;
	pd->debug_nb.notifier_call = pwrctrl_pd_power_notifier;
	pwrctrl_pd_register_pm_notifier(&pd->debug_nb);

	if (IS_ENABLED(CONFIG_POWER_CONTROL_PD_SRAM) &&
	   (pd->pc.ops == &rtk_sram_power_ops ||
	   pd->pc.ops == &rtk_sram_async_power_ops)) {
		struct rtk_sram_pd *spd = container_of(pd, struct rtk_sram_pd, core);

		spd->base = data->base;
	} else if (IS_ENABLED(CONFIG_POWER_CONTROL_PD_ANALOG) &&
		   pd->pc.ops == &rtk_analog_power_ops) {
		struct rtk_analog_pd *apd = container_of(pd, struct rtk_analog_pd, core);

		apd->base = data->base;
		apd->np = data->np;
	} else if (IS_ENABLED(CONFIG_POWER_CONTROL_PD_SRAM_CH) &&
		   pd->pc.ops == &rtk_sram_ch_power_ops) {
		struct rtk_sram_ch_pd *spd = container_of(pd, struct rtk_sram_ch_pd, core);

		spd->base = data->base;
	} else if (IS_ENABLED(CONFIG_POWER_CONTROL_PD_SIMPLE) &&
		  pd->pc.ops == &simple_power_ops) {
		struct simple_pd *spd = container_of(pd, struct simple_pd, core);

		spd->base = data->base;
	}

	/* setup power-control */
	power_control_init(&pd->pc);
	power_control_register(&pd->pc);
	if (pd->flags & RTK_PD_NO_GENPD) {
		pr_debug("%s: initialize as power_control %s\n",
			pd->pd.name, pd->pc.name);
		return;
	}

	/* since the power control is managed by genpd, increase the internal
	 * usage count to prevent power-control framework to control it.
	 */
	power_control_get_internal(&pd->pc);

	/* register genpd */
	is_off = !pd->pc.ops->is_powered_on(&pd->pc);
	pr_debug("%s: %s: default power is %s\n", pd->pd.name, __func__,
		is_off ? "off" : "on");

	pd->pd.attach_dev = pwrctrl_pd_attach_dev;
	pd->pd.detach_dev = pwrctrl_pd_detach_dev;
	pd->pd.power_on   = pwrctrl_pd_power_on;
	pd->pd.power_off  = pwrctrl_pd_power_off;

	pm_genpd_init(&pd->pd, NULL, is_off);
	list_add(&pd->list, &pm_list);
}

static void pwrctrl_pd_sync(struct device *dev)
{
	struct pwrctrl_pd *pd;

	/* sync state */
	list_for_each_entry(pd, &pm_list, list) {
		int st = power_control_is_powered_on(&pd->pc);

		if (st < 0)
			continue;

		if (pd->dev != dev)
			continue;

		if (pd->pd.status == GPD_STATE_POWER_OFF && st == 1) {
			pr_debug("%s: %s: power_off\n", pd->pd.name, __func__);
			power_control_power_off(&pd->pc);
		}

		if (pd->pd.status == GPD_STATE_ACTIVE && st == 0) {
			pr_debug("%s: %s: power_on\n", pd->pd.name, __func__);
			power_control_power_on(&pd->pc);
		}
	}
}


int pwrctrl_pd_register_pm_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_register(&pm_notifier_list, nb);
}

void pwrctrl_pd_unregister_pm_notifier(struct notifier_block *nb)
{
	atomic_notifier_chain_unregister(&pm_notifier_list, nb);
}

static int __pwrctrl_pd_pm_notify(struct device *dev, int pd_pm_state)
{
	return atomic_notifier_call_chain(&pm_notifier_list, pd_pm_state, dev);
}

void pwrctrl_pd_pm_notify(struct device *dev, int pd_pm_state)
{
	int ret;
	const char *ststr;

	switch (pd_pm_state) {
	case RTK_PD_PM_RESUME_EARLY:
		ststr = "resume_early";
		pwrctrl_pd_sync(dev);
		break;
	case RTK_PD_PM_RESUME:
		ststr = "resume";
		break;
	case RTK_PD_PM_PREPARE:
		ststr = "prepare";
		break;
	case RTK_PD_PM_SUSPEND:
		ststr = "suspend";
		break;
	case RTK_PD_PM_SUSPEND_LATE:
		ststr = "suspend_late";
		break;
	case RTK_PD_PM_SUSPEND_NOIRQ:
		ststr = "suspend_noirq";
		break;
	default:
		dev_err(dev, "unknown state: %d\n", pd_pm_state);
		return;
	}
	ret = __pwrctrl_pd_pm_notify(dev, pd_pm_state);
	dev_info(dev, "%s: pm_state=%s returns %d\n", __func__, ststr, ret);
}

/* add power-control of-provider and power-domain of-provider */
int power_controller_add_of_providers(struct device *dev,
				      struct power_controller_data *pcd)
{
	struct device_node *np = dev->of_node;
	int i;
	int ret;

	pcd->pd_data.domains = devm_kcalloc(dev, pcd->num_ppds,
		sizeof(*pcd->pd_data.domains), GFP_KERNEL);
	if (!pcd->pd_data.domains)
		return -ENOMEM;
	pcd->pd_data.num_domains = pcd->num_ppds;

	pcd->pc_data.controls = devm_kcalloc(dev, pcd->num_ppds,
		sizeof(*pcd->pc_data.controls), GFP_KERNEL);
	if (!pcd->pc_data.controls)
		return -ENOMEM;
	pcd->pc_data.num_controls = pcd->num_ppds;


	for (i = 0; i < pcd->num_ppds; i++) {
		if (!pcd->ppds[i])
			continue;

		if (!(pcd->ppds[i]->flags & RTK_PD_NO_GENPD))
			pcd->pd_data.domains[i] = &pcd->ppds[i]->pd;
		pcd->pc_data.controls[i] = &pcd->ppds[i]->pc;
	}

	ret = of_genpd_add_provider_onecell(np, &pcd->pd_data);
	WARN(ret, "of_genpd_add_provider_onecell() returns %d\n", ret);
	ret = of_power_control_add_provider(np, of_power_control_xlate_onecell,
		&pcd->pc_data);
	WARN(ret, "of_power_control_add_provider() returns %d\n", ret);
	return 0;
}

int power_controller_init_pds(struct device *dev,
			      struct power_controller_data *pcd)
{
	struct device_node *np = dev->of_node;
	struct pwrctrl_pd_initdata data;
	int i;
	int ret;

	data.base = of_iomap(np, 0);
	data.np = np;

	for (i = 0; i < pcd->num_ppds; i++) {
		if (!pcd->ppds[i])
			continue;

		if (of_pwrctrl_pd_is_invalid(np, pcd->ppds[i]->pd.name)) {
			dev_notice(dev, "%s: not in current domain\n",
				pcd->ppds[i]->pd.name);
			pcd->ppds[i] = NULL;
			continue;
		}

		pwrctrl_pd_init(dev, pcd->ppds[i], &data);
	}

	ret = power_controller_add_of_providers(dev, pcd);
	WARN(ret, "power_controller_add_of_providers() returns %d\n", ret);

	if (pcd->ready)
		pcd->ready(pcd);
	return 0;

}

static int power_controller_prepare(struct device *dev)
{
	dev_info(dev, "Enter %s\n", __func__);
	pwrctrl_pd_pm_notify(dev, RTK_PD_PM_PREPARE);
	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static int power_controller_suspend(struct device *dev)
{
	dev_info(dev, "Enter %s\n", __func__);
	pwrctrl_pd_pm_notify(dev, RTK_PD_PM_SUSPEND);
	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static int power_controller_suspend_late(struct device *dev)
{
	dev_info(dev, "Enter %s\n", __func__);
	pwrctrl_pd_pm_notify(dev, RTK_PD_PM_SUSPEND_LATE);
	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static int power_controller_suspend_noirq(struct device *dev)
{
	dev_info(dev, "Enter %s\n", __func__);
	pwrctrl_pd_pm_notify(dev, RTK_PD_PM_SUSPEND_NOIRQ);
	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static int power_controller_resume_early(struct device *dev)
{
	dev_info(dev, "Enter %s\n", __func__);
	pwrctrl_pd_pm_notify(dev, RTK_PD_PM_RESUME_EARLY);
	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static int power_controller_resume(struct device *dev)
{
	dev_info(dev, "Enter %s\n", __func__);
	pwrctrl_pd_pm_notify(dev, RTK_PD_PM_RESUME);
	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

const struct dev_pm_ops power_controller_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(power_controller_suspend,
				power_controller_resume)
	SET_LATE_SYSTEM_SLEEP_PM_OPS(power_controller_suspend_late,
				     power_controller_resume_early)
	.prepare = power_controller_prepare,
	.suspend_noirq = power_controller_suspend_noirq,
};
