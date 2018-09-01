/*
 * pwrctrl-pd-analog.c - Analog PD
 *
 * Copyright (C) 2017-2018 Realtek Semiconductor Corporation
 * Copyright (C) 2017-2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/pm_domain.h>
#include <linux/reset.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/suspend.h>
#include <soc/realtek/power-control.h>
#include <dt-bindings/power/rtk,power-rtd139x.h>
#include "pwrctrl_driver.h"
#include "pwrctrl-pd.h"

static DEFINE_SPINLOCK(rtk_pc_lock);

static inline void prepare(struct rtk_analog_pd *apd)
{
	struct clk *clk;
	struct reset_control *rstc;

	clk = of_clk_get_by_name(apd->np, apd->clk_name);
	if (!IS_ERR(clk)) {
		clk_prepare_enable(clk);
		clk_put(clk);
	}

	rstc = of_reset_control_get(apd->np, apd->rstn_name);
	if (!IS_ERR_OR_NULL(rstc)) {
		reset_control_deassert(rstc);
		reset_control_put(rstc);
	}
}

static inline void unprepare(struct rtk_analog_pd *apd)
{
	struct clk *clk;
	struct reset_control *rstc;

	clk = of_clk_get_by_name(apd->np, apd->clk_name);
	if (!IS_ERR(clk)) {
		clk_disable_unprepare(clk);
		clk_put(clk);
	}

	/*
	 * Using an excusive reset control. When a power-domain
	 * is attached to a device, the 'get' below will get
	 * successfully a reset control. After a driver is ready,
	 * the dirver should get and hold the reset control to
	 * make the 'get' below fail to get so the power-control
	 * is impossible to assert the reset control.
	 */
	rstc = of_reset_control_get(apd->np, apd->rstn_name);
	if (!IS_ERR_OR_NULL(rstc)) {
		reset_control_assert(rstc);
		reset_control_put(rstc);
	}
}

static int rtk_analog_power_on(struct power_control *pctrl)
{
	struct rtk_analog_pd *apd = pc_to_rtk_analog_pd(pctrl);
	void *reg = apd->base + apd->pwr_offset;
	unsigned int val;
	unsigned long flags;

	pr_debug("%s: %s\n", __func__, pctrl->name);

	prepare(apd);

	spin_lock_irqsave(&rtk_pc_lock, flags);

	val = (readl(reg) & ~0x1) | 1;
	writel(val, reg);

	spin_unlock_irqrestore(&rtk_pc_lock, flags);

	unprepare(apd);

	return 0;
}

static int rtk_analog_power_off(struct power_control *pctrl)
{
	struct rtk_analog_pd *apd = pc_to_rtk_analog_pd(pctrl);
	void *reg = apd->base + apd->pwr_offset;
	unsigned int val;
	unsigned long flags;

	pr_debug("%s: %s\n", __func__, pctrl->name);

	prepare(apd);

	spin_lock_irqsave(&rtk_pc_lock, flags);

	val = (readl(reg) & ~0x1) | 0;
	writel(val, reg);

	spin_unlock_irqrestore(&rtk_pc_lock, flags);

	unprepare(apd);

	return 0;
}

static int rtk_analog_is_powered_on(struct power_control *pctrl)
{
	struct rtk_analog_pd *apd = pc_to_rtk_analog_pd(pctrl);
	void *reg = apd->base + apd->pwr_offset;
	unsigned int val;
	unsigned long flags;

	prepare(apd);

	spin_lock_irqsave(&rtk_pc_lock, flags);

	val = readl(reg) & 0x1;

	spin_unlock_irqrestore(&rtk_pc_lock, flags);

	unprepare(apd);

	return val == 1;
}

const struct power_control_ops rtk_analog_ops = {
	.power_off = rtk_analog_power_off,
	.power_on = rtk_analog_power_on,
	.is_powered_on = rtk_analog_is_powered_on,
};

int rtk_analog_pd_init(struct pwrctrl_pd *pd, void *initdata)
{
	struct pwrctrl_pd_initdata *data = initdata;
	struct rtk_analog_pd *apd =
		container_of(pd, struct rtk_analog_pd, core);

	apd->base = data->base;
	apd->np = data->np;

	return 0;
}

