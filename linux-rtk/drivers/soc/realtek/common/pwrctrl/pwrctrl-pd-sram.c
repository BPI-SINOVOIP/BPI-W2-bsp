/*
 * pwrctrl-pd-sram.c - SRAM PD
 *
 * Copyright (C) 2017-2019 Realtek Semiconductor Corporation
 * Copyright (C) 2017-2019 Cheng-Yu Lee <cylee12@realtek.com>
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

static int rtk_sram_power_init(struct power_control *pwrctrl);

static inline unsigned long rtk_sram_power_lock(struct rtk_sram_pd *spd)
{
	unsigned long flags = 0;

	if (spd->lock)
		spin_lock_irqsave(spd->lock, flags);
	return flags;
}

static inline void rtk_sram_power_unlock(struct rtk_sram_pd *spd,
					 unsigned long flags)
{
	if (spd->lock)
		spin_unlock_irqrestore(spd->lock, flags);
}

#define SRAM_PWR0 0x0
#define SRAM_PWR1 0x4
#define SRAM_PWR2 0x8
#define SRAM_PWR3 0xC
#define SRAM_PWR4 0x10
#define SRAM_PWR5 0x14
#define SRAM_PWR6 0x18

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

static int rtk_sram_power_on(struct power_control *pwrctrl)
{
	struct rtk_sram_pd *spd = pc_to_rtk_sram_pd(pwrctrl);
	unsigned int val;
	unsigned long flags;
	int ret;
	u32 pwr4, pwr5;

	pr_debug("%s: %s\n", pwrctrl->name, __func__);
	pwr4 = spd->pwr_offset + SRAM_PWR4;
	pwr5 = spd->pwr5_offset ? spd->pwr5_offset : (spd->pwr_offset + SRAM_PWR5);

	flags = rtk_sram_power_lock(spd);

	val = (spd->last_sd_ch << 8) | 0x0;
	writel(val, spd->base + pwr4);

	ret = sram_wait_for_int(readl(spd->base + pwr5) == 0x4, 500);
	if (ret == -ETIME)
		pr_warn("%s: %s: sram_int timeout\n", pwrctrl->name, __func__);
	writel(0x4, spd->base + pwr5);

	rtk_sram_power_unlock(spd, flags);
	return 0;
}

static int rtk_sram_power_off(struct power_control *pwrctrl)
{
	struct rtk_sram_pd *spd = pc_to_rtk_sram_pd(pwrctrl);
	unsigned int val;
	unsigned long flags;
	int ret;
	u32 pwr4, pwr5;

	pr_debug("%s: %s\n", pwrctrl->name, __func__);
	pwr4 = spd->pwr_offset + SRAM_PWR4;
	pwr5 = spd->pwr5_offset ? spd->pwr5_offset : (spd->pwr_offset + SRAM_PWR5);

	flags = rtk_sram_power_lock(spd);

	val = (spd->last_sd_ch << 8) | 0x1;
	writel(val, spd->base + pwr4);

	ret = sram_wait_for_int(readl(spd->base + pwr5) == 0x4, 500);
	if (ret == -ETIME)
		pr_warn("%s: %s: sram_int timeout\n", pwrctrl->name, __func__);
	writel(0x4, spd->base + pwr5);

	rtk_sram_power_unlock(spd, flags);

	return 0;
}

static int rtk_sram_is_powered_on(struct power_control *pwrctrl)
{
	struct rtk_sram_pd *spd = pc_to_rtk_sram_pd(pwrctrl);
	u32 pwr4 = spd->pwr_offset + SRAM_PWR4;

	return (readl(spd->base + pwr4) & 1) == 0;
}

static int rtk_sram_power_off_unused(struct power_control *pwrctrl)
{
	pr_info("%s: %s\n", pwrctrl->name, __func__);
	return pwrctrl->ops->power_off(pwrctrl);
}

const struct power_control_ops rtk_sram_power_ops = {
	.power_off        = rtk_sram_power_off,
	.power_on         = rtk_sram_power_on,
	.is_powered_on    = rtk_sram_is_powered_on,
	.init             = rtk_sram_power_init,
	.power_off_unused = rtk_sram_power_off_unused,
};

static void rtk_sram_async_power_off_timeout(unsigned long data)
{
	struct power_control *pwrctrl = (struct power_control *)data;
	struct rtk_sram_pd *spd = pc_to_rtk_sram_pd(pwrctrl);

	__power_control_notify_power_off_start(pwrctrl);

	spin_lock(&spd->timer_lock);
	pr_debug("%s: %s\n", pwrctrl->name, __func__);
	rtk_sram_power_off(pwrctrl);
	spin_unlock(&spd->timer_lock);

	__power_control_notify_power_off_done(pwrctrl);
}

static int rtk_sram_async_power_off(struct power_control *pwrctrl)
{
	struct rtk_sram_pd *spd = pc_to_rtk_sram_pd(pwrctrl);
	unsigned long flags;
	u64 expired_jiffies;

	spin_lock_irqsave(&spd->timer_lock, flags);

	pr_debug("%s: %s\n", pwrctrl->name, __func__);

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

static int rtk_sram_async_power_on(struct power_control *pwrctrl)
{
	struct rtk_sram_pd *spd = pc_to_rtk_sram_pd(pwrctrl);
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&spd->timer_lock, flags);

	pr_debug("%s: %s\n", pwrctrl->name, __func__);
	del_timer(&spd->timer);
	ret = rtk_sram_is_powered_on(pwrctrl);
	if (ret == 1)
		goto done;
	ret = rtk_sram_power_on(pwrctrl);
done:
	spin_unlock_irqrestore(&spd->timer_lock, flags);
	return ret;
}

static int rtk_sram_async_power_notifier(struct notifier_block *nb,
					 unsigned long action,
					 void *unused)
{
	struct rtk_sram_pd *spd = container_of(nb, struct rtk_sram_pd, pm_nb);
	struct power_control *pwrctrl = &spd->core.pc;

	if (action == RTK_PD_PM_SUSPEND_LATE) {
		pr_debug("%s: %s: power_off\n", pwrctrl->name, __func__);
		del_timer(&spd->timer);
		rtk_sram_power_off(pwrctrl);
		return NOTIFY_OK;
	}

	return NOTIFY_DONE;
}

static int rtk_sram_power_init(struct power_control *pwrctrl)
{
	struct rtk_sram_pd *spd = pc_to_rtk_sram_pd(pwrctrl);

	if ((spd->core.flags & RTK_PD_NO_GENPD) && pwrctrl->ops == &rtk_sram_async_power_ops) {
		WARN_ON(spd->expired_time == 0);
		pr_debug("%s: %s: init_timer\n", pwrctrl->name, __func__);
		spin_lock_init(&spd->timer_lock);
		init_timer(&spd->timer);
		spd->timer.function = rtk_sram_async_power_off_timeout;
		spd->timer.data = (unsigned long)pwrctrl;
		spd->pm_nb.notifier_call = rtk_sram_async_power_notifier;
		pwrctrl->flags |= POWER_CONTROL_FLAG_ASYNC_POWER_OFF;
		pwrctrl->flags |= POWER_CONTROL_FLAG_SHARED_POWER;
		pwrctrl_pd_register_pm_notifier(&spd->pm_nb);
	}
	return 0;
}

const struct power_control_ops rtk_sram_async_power_ops = {
	.power_off        = rtk_sram_async_power_off,
	.power_on         = rtk_sram_async_power_on,
	.is_powered_on    = rtk_sram_is_powered_on,
	.init             = rtk_sram_power_init,
	.power_off_unused = rtk_sram_power_off_unused,
};

