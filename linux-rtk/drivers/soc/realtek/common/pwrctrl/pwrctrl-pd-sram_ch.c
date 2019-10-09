/*
 * pwrctrl-pd-sram_ch.c - SRAM PD by Channel
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
#define sd_reg(_spd) (sram_reg(_spd) + SRAM_PWR2)
#define mux_reg(_spd) (sram_reg(_spd) + SRAM_PWR3)

static int rtk_sram_ch_power_on(struct power_control *pctrl)
{
	struct rtk_sram_ch_pd *spd = pc_to_rtk_sram_ch_pd(pctrl);
	unsigned int mask;
	unsigned int val;
	unsigned long flags;

	pr_debug("%s: %s\n", __func__, pctrl->name);

	mask = (BIT(spd->width)- 1) << spd->shift;

	spin_lock_irqsave(&rtk_pc_lock, flags);
	val = readl(sd_reg(spd));
	val &= ~mask;
	writel(val, sd_reg(spd));
	spin_unlock_irqrestore(&rtk_pc_lock, flags);

	return 0;
}

static int rtk_sram_ch_power_off(struct power_control *pctrl)
{
	struct rtk_sram_ch_pd *spd = pc_to_rtk_sram_ch_pd(pctrl);
	unsigned int mask;
	unsigned int val;
	unsigned long flags;

	pr_debug("%s: %s\n", __func__, pctrl->name);
	mask = (BIT(spd->width)- 1) << spd->shift;

	spin_lock_irqsave(&rtk_pc_lock, flags);

	val = readl(mux_reg(spd));
	val |= mask;
	writel(val, mux_reg(spd));

	val = readl(sd_reg(spd));
	val |= mask;
	writel(val, sd_reg(spd));

	spin_unlock_irqrestore(&rtk_pc_lock, flags);

	return 0;
}

static int rtk_sram_is_powered_on(struct power_control *pctrl)
{
	struct rtk_sram_ch_pd *spd = pc_to_rtk_sram_ch_pd(pctrl);
	unsigned int mask;
	unsigned int val;
	unsigned long flags;
	int ret;

	mask = (BIT(spd->width)- 1) << spd->shift;

	spin_lock_irqsave(&rtk_pc_lock, flags);
	val = readl(sd_reg(spd));
	ret = (val & mask) == 0;
	spin_unlock_irqrestore(&rtk_pc_lock, flags);

	return 0;
}

const struct power_control_ops rtk_sram_ch_ops = {
	.power_off = rtk_sram_ch_power_off,
	.power_on = rtk_sram_ch_power_on,
	.is_powered_on = rtk_sram_is_powered_on,
};

int rtk_sram_ch_pd_init(struct pwrctrl_pd *pd, void *initdata)
{
	struct pwrctrl_pd_initdata *data = initdata;
	struct rtk_sram_ch_pd *spd = container_of(pd, struct rtk_sram_ch_pd, core);

	spd->base = data->base;

	return 0;
}

