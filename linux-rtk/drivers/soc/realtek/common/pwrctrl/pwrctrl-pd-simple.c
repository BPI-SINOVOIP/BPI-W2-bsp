/*
 * pwrctrl-pd-simple.c - Simple PD
 *
 * Copyright (C) 2019 Realtek Semiconductor Corporation
 * Copyright (C) 2019 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/io.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <soc/realtek/power-control.h>
#include "pwrctrl_driver.h"
#include "pwrctrl-pd.h"

static inline unsigned long simple_power_lock(struct simple_pd *spd)
{
	unsigned long flags = 0;

	if (spd->lock)
		spin_lock_irqsave(spd->lock, flags);
	return flags;
}

static inline void simple_power_unlock(struct simple_pd *spd,
					unsigned long flags)
{
	if (spd->lock)
		spin_unlock_irqrestore(spd->lock, flags);
}

static int simple_power_on(struct power_control *pwrctrl)
{
	struct simple_pd *spd = pc_to_simple_pd(pwrctrl);
	unsigned long flags;
	u32 val;

	pr_debug("%s: %s\n", pwrctrl->name, __func__);

	flags = simple_power_lock(spd);
	val = readl(spd->base + spd->offset);
	val = (val & ~spd->mask) | (spd->val_on & spd->mask);
	writel(val, spd->base + spd->offset);
	simple_power_unlock(spd, flags);

	return 0;
}

static int simple_power_off(struct power_control *pwrctrl)
{
	struct simple_pd *spd = pc_to_simple_pd(pwrctrl);
	unsigned long flags;
	u32 val;

	pr_debug("%s: %s\n", pwrctrl->name, __func__);

	flags = simple_power_lock(spd);
	val = readl(spd->base + spd->offset);
	val = (val & ~spd->mask) | (spd->val_off & spd->mask);
	writel(val, spd->base + spd->offset);
	simple_power_unlock(spd, flags);

	return 0;
}

static int simple_is_powered_on(struct power_control *pwrctrl)
{
	struct simple_pd *spd = pc_to_simple_pd(pwrctrl);

	return (readl(spd->base + spd->offset) & spd->mask) ==
	       (spd->val_on & spd->mask);
}

const struct power_control_ops simple_power_ops = {
	.power_off     = simple_power_off,
	.power_on      = simple_power_on,
	.is_powered_on = simple_is_powered_on,
};

/* power chain */
int simple_pd_add_power_chain(struct simple_pd *pd,
			      struct power_control *pwrctrl,
			      notifier_fn_t func)
{
	struct power_chain *pcx;
	int ret;

	if (!pd->pch) {
		pd->pch = kzalloc(sizeof(*pd->pch), GFP_KERNEL);
		if (!pd->pch)
			return -ENOMEM;
		INIT_LIST_HEAD(&pd->pch->list);
	}
	pcx = kzalloc(sizeof(*pcx), GFP_KERNEL);
	if (!pcx)
		return -ENOMEM;

	pcx->self = &pd->core.pc;
	pcx->ref  = pwrctrl;
	pcx->power_nb.notifier_call = func;
	ret = power_control_register_notifier(pcx->ref, &pcx->power_nb);
	if (ret) {
		pr_err("%s: power_control_register_notifier() returns %d\n",
			pcx->ref->name, ret);
		kfree(pcx);
		return ret;
	}

	/* let the ref power-control controls currnet power-control */
	power_control_get_internal(pcx->self);

	list_add(&pcx->list, &pd->pch->list);
	return 0;
}

void simple_pd_remove_power_chains(struct simple_pd *pd)
{
	struct power_chain *c, *n;

	if (!pd->pch)
		return;

	list_for_each_entry_safe(c, n, &pd->pch->list, list) {
		/* undo power_control_get_internal() */
		power_control_put_internal(c->self);

		power_control_unregister_notifier(c->ref, &c->power_nb);
		list_del(&c->list);
		kfree(c);
	}
	kfree(pd->pch);
	pd->pch = NULL;
}
