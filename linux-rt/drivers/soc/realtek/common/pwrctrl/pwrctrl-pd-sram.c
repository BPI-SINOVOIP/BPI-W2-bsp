/*
 * pwrctrl-pd-sram.c - SRAM PD
 *
 * Copyright (C) 2017-2018 Realtek Semiconductor Corporation
 * Copyright (C) 2017-2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/delay.h>
#include <linux/io.h>
#include <linux/reset.h>
#include <linux/spinlock.h>
#include <soc/realtek/power-control.h>
#include "pwrctrl_driver.h"
#include "pwrctrl-pd.h"

static DEFINE_SPINLOCK(rtk_pc_lock);

#define SRAM_PWR0 0x0
#define SRAM_PWR1 0x4
#define SRAM_PWR2 0x8
#define SRAM_PWR3 0xC
#define SRAM_PWR4 0x10
#define SRAM_PWR5 0x14
#define SRAM_PWR6 0x18

#define sram_reg(_spd) ((_spd)->base + (_spd)->pwr_offset)
#define pwr3_reg(_spd) (sram_reg(_spd) + SRAM_PWR3)
#define pwr4_reg(_spd) (sram_reg(_spd) + SRAM_PWR4)
#define pwr5_reg(_spd) (sram_reg(_spd) + SRAM_PWR5)
#define iso_reg(_spd) ((_spd)->base + (_spd)->iso_offset)

static int of_device_reset(struct device_node *np, const char *rstn_name)
{
	struct reset_control *rstc;

	if (!rstn_name)
		return 0;

	rstc = of_reset_control_get(np, rstn_name);
	if (IS_ERR_OR_NULL(rstc)) {
		pr_err("%s: reset_control_get() for %s returns: %ld\n",
			np->name, rstn_name, PTR_ERR(rstc));
		return -EINVAL;
	}
	reset_control_reset(rstc);
	reset_control_put(rstc);
	return 0;
}

#define sram_wait_for_int(cond, timeout_us)     \
({                                              \
	int ret = 0;                            \
	int retry = timeout_us;                 \
						\
	for (;;) {                              \
		if (cond)                       \
			break;                  \
		udelay(1);                      \
		if (--retry > 0)                \
			continue;               \
		ret = -ETIME;                   \
		break;                          \
	}                                       \
						\
	ret;                                    \
})

static int rtk_sram_power_on(struct power_control *pctrl)
{
	struct rtk_sram_pd *spd = pc_to_rtk_sram_pd(pctrl);
	unsigned int val;
	unsigned long flags;
	int ret;
	void *pwr5;

	pr_debug("%s: %s\n", pctrl->name, __func__);

	spin_lock_irqsave(&rtk_pc_lock, flags);

	val = (spd->last_sd_ch << 8) | 0x0;
	writel(val, pwr4_reg(spd));

	pwr5 = pwr5_reg(spd);
	if (spd->flags & RTK_SRAM_PD_NON_CONTIGUOUS_PWR)
		pwr5 = spd->base + spd->pwr5_offset;

	ret = sram_wait_for_int(readl(pwr5) == 0x4, 500);
	if (ret == -ETIME)
		pr_warn("%s: %s: sram_int timeout\n", pctrl->name, __func__);
	writel(0x4, pwr5);

	of_device_reset(spd->np, spd->rstn_name);

	if (!(spd->flags & RTK_SRAM_PD_NO_ISO_POW)) {
		val = readl(iso_reg(spd)) & (~BIT(spd->iso_shift));
		writel(val, iso_reg(spd));
	}

	spin_unlock_irqrestore(&rtk_pc_lock, flags);

	return 0;
}

static int rtk_sram_power_off(struct power_control *pctrl)
{
	struct rtk_sram_pd *spd = pc_to_rtk_sram_pd(pctrl);
	unsigned int val;
	unsigned long flags;
	int ret;
	void *pwr5;

	pr_debug("%s: %s\n", pctrl->name, __func__);

	spin_lock_irqsave(&rtk_pc_lock, flags);

	if (!(spd->flags & RTK_SRAM_PD_NO_ISO_POW)) {
		val = readl(iso_reg(spd)) | BIT(spd->iso_shift);
		writel(val, iso_reg(spd));
	}

	val = (spd->last_sd_ch << 8) | 0x1;
	writel(val, pwr4_reg(spd));

	pwr5 = pwr5_reg(spd);
	if (spd->flags & RTK_SRAM_PD_NON_CONTIGUOUS_PWR)
		pwr5 = spd->base + spd->pwr5_offset;

	ret = sram_wait_for_int(readl(pwr5) == 0x4, 500);
	if (ret == -ETIME)
		pr_warn("%s: %s: sram_int timeout\n", pctrl->name, __func__);
	writel(0x4, pwr5);

	spin_unlock_irqrestore(&rtk_pc_lock, flags);

	return 0;
}

static int rtk_sram_is_powered_on(struct power_control *pctrl)
{
	struct rtk_sram_pd *spd = pc_to_rtk_sram_pd(pctrl);

	return (readl(pwr4_reg(spd)) & 1) == 0;
}

const struct power_control_ops rtk_sram_ops = {
	.power_off = rtk_sram_power_off,
	.power_on = rtk_sram_power_on,
	.is_powered_on = rtk_sram_is_powered_on,
};

static void rtk_sram_async_power_off_timeout(unsigned long data)
{
	struct power_control *pctrl = (struct power_control *)data;
	struct rtk_sram_pd *spd = pc_to_rtk_sram_pd(pctrl);

	spin_lock(&spd->timer_lock);
	pr_debug("%s: %s\n", pctrl->name, __func__);
	rtk_sram_power_off(pctrl);
	spin_unlock(&spd->timer_lock);
}

static int rtk_sram_async_power_off(struct power_control *pctrl)
{
	struct rtk_sram_pd *spd = pc_to_rtk_sram_pd(pctrl);
	unsigned long flags;
	u64 expired_jiffies;

	spin_lock_irqsave(&spd->timer_lock, flags);

	pr_debug("%s: %s\n", pctrl->name, __func__);

	expired_jiffies = msecs_to_jiffies(spd->expired_time * 1000);
	if (!timer_pending(&spd->timer)) {
		spd->timer.expires = get_jiffies_64() + expired_jiffies;
		add_timer(&spd->timer);
	} else {
		mod_timer(&spd->timer, get_jiffies_64() + expired_jiffies);
	}

	spin_unlock_irqrestore(&spd->timer_lock, flags);

	return 0;
}

static int rtk_sram_async_power_on(struct power_control *pctrl)
{
	struct rtk_sram_pd *spd = pc_to_rtk_sram_pd(pctrl);
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&spd->timer_lock, flags);

	pr_debug("%s: %s\n", pctrl->name, __func__);
	del_timer(&spd->timer);
	ret = rtk_sram_is_powered_on(pctrl);
	if (ret == 1)
		goto done;
	ret = rtk_sram_power_on(pctrl);
done:
	spin_unlock_irqrestore(&spd->timer_lock, flags);
	return ret;
}

static int rtk_sram_async_power_notifier(struct notifier_block *nb,
	unsigned long action, void *unused)
{
	struct rtk_sram_pd *spd = container_of(nb, struct rtk_sram_pd, pm_nb);
	struct power_control *pctrl = &spd->core.pc;

	if (action == RTK_PD_PM_SUSPEND_LATE) {
		pr_debug("%s: %s: power_off\n", pctrl->name, __func__);
		del_timer(&spd->timer);
		rtk_sram_power_off(pctrl);
		return NOTIFY_OK;
	}

	return NOTIFY_DONE;
}

const struct power_control_ops rtk_sram_async_ops = {
	.power_off = rtk_sram_async_power_off,
	.power_on = rtk_sram_async_power_on,
	.is_powered_on = rtk_sram_is_powered_on,
};

int rtk_sram_pd_init(struct pwrctrl_pd *pd, void *initdata)
{
	struct pwrctrl_pd_initdata *data = initdata;
	struct rtk_sram_pd *spd = container_of(pd, struct rtk_sram_pd, core);

	spd->base = data->base;
	spd->np = data->np;

	if (spd->flags & RTK_SRAM_PD_APPLY_MANUAL_MASK)
		writel(spd->manual_mask, pwr3_reg(spd));

	if ((pd->flags & RTK_PD_NO_GENPD) &&
		pd->pc.ops == &rtk_sram_async_ops) {
		WARN_ON(spd->expired_time == 0);
		pr_debug("%s: %s: init_timer\n", pd->pc.name, __func__);
		spin_lock_init(&spd->timer_lock);
		init_timer(&spd->timer);
		spd->timer.function = rtk_sram_async_power_off_timeout;
		spd->timer.data = (unsigned long)&pd->pc;
		spd->pm_nb.notifier_call = rtk_sram_async_power_notifier;
		pwrctrl_pd_register_pm_notifier(&spd->pm_nb);
	}
	return 0;
}

