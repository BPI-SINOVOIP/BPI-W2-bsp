/*
 * Power Control as Power Doamin
 *
 * Copyright (C) 2017-2019 Realtek Semiconductor Corporation
 * Copyright (C) 2017-2019 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __POWER_CONTROL_PD_H
#define __POWER_CONTROL_PD_H

#include <linux/pm_runtime.h>
#include <linux/pm_domain.h>
#include <linux/notifier.h>
#include <linux/spinlock.h>
#include <linux/timer.h>
#include <soc/realtek/power-control.h>
#include "pwrctrl_driver.h"

struct device;
struct device_node;

/**
 * struct pwrctrl_pd - core structure
 *
 * @pd: interface to genpd
 * @pc: interface to power_control
 * @dev: controller device
 * @list: node to all pd
 * @debug_nb: debug for pm state
 * @flags: control flags
 *
 * *** flags ***
 *  RTK_PD_NO_GENPD - don't init as a genpd
 */
struct pwrctrl_pd {
	struct generic_pm_domain pd;
	struct power_control pc;

	struct device *dev;
	struct list_head list;

	struct notifier_block debug_nb;
	unsigned int flags;
};

/* flags */
#define RTK_PD_NO_GENPD           BIT(0)

#define pd_to_pwrctrl_pd(_pd) container_of(_pd, struct pwrctrl_pd, pd)
#define pc_to_pwrctrl_pd(_pc) container_of(_pc, struct pwrctrl_pd, pc)

/* pm notify actions */
enum {
	RTK_PD_PM_PREPARE,
	RTK_PD_PM_SUSPEND,
	RTK_PD_PM_SUSPEND_LATE,
	RTK_PD_PM_SUSPEND_NOIRQ,
	RTK_PD_PM_RESUME_EARLY,
	RTK_PD_PM_RESUME,
};

struct pwrctrl_pd_initdata {
	struct device_node *np;
	void *base;
};

void pwrctrl_pd_init(struct device *dev,
		     struct pwrctrl_pd *pd,
		     const struct pwrctrl_pd_initdata *data);
void pwrctrl_pd_pm_notify(struct device *dev, int pd_pm_state);
int pwrctrl_pd_register_pm_notifier(struct notifier_block *nb);
void pwrctrl_pd_unregister_pm_notifier(struct notifier_block *nb);

static inline bool of_pwrctrl_pd_is_invalid(struct device_node *np,
					    const char *name)
{
	return of_property_match_string(np, "invalid-power-domains", name) >= 0;
}

/* sram pd */
struct rtk_sram_pd {
	struct pwrctrl_pd core;
	void *base;
	unsigned int pwr_offset;
	unsigned int pwr5_offset;
	unsigned int last_sd_ch;
	spinlock_t *lock;

	/* timer data */
	struct timer_list timer;
	int expired_time;
	spinlock_t timer_lock;
	struct notifier_block pm_nb;
};

#define pc_to_rtk_sram_pd(_pc) container_of(_pc, struct rtk_sram_pd, core.pc)
#define pd_to_rtk_sram_pd(_pd) container_of(_pd, struct rtk_sram_pd, core.pd)

extern const struct power_control_ops rtk_sram_power_ops;
extern const struct power_control_ops rtk_sram_async_power_ops;

/* sram ch pd */
struct rtk_sram_ch_pd {
	struct pwrctrl_pd core;
	void *base;
	unsigned int flags;
	unsigned int pwr_offset;
	int shift;
	int width;
};

#define pc_to_rtk_sram_ch_pd(_pc) container_of(_pc, struct rtk_sram_ch_pd, core.pc)
extern const struct power_control_ops rtk_sram_ch_power_ops;

/* analog pd */
struct rtk_analog_pd {
	struct pwrctrl_pd core;
	void *base;
	unsigned int pwr_offset;
	unsigned int flags;

	const char *clk_name;
	const char *rstn_name;
	struct device_node *np;
};

#define pc_to_rtk_analog_pd(_pc) container_of(_pc, struct rtk_analog_pd, core.pc)
extern const struct power_control_ops rtk_analog_power_ops;

struct power_chain_head;

/* simple pd */
struct simple_pd {
	struct pwrctrl_pd core;
	void *base;
	unsigned int offset;
	unsigned int mask;
	unsigned int val_on;
	unsigned int val_off;
	spinlock_t *lock;

	struct power_chain_head *pch;
};

#define pc_to_simple_pd(_pc) container_of(_pc, struct simple_pd, core.pc)
extern const struct power_control_ops simple_power_ops;

/* simple pd: power chain */
int simple_pd_add_power_chain(struct simple_pd *pd,
			      struct power_control *pwrctrl,
			      notifier_fn_t func);
void simple_pd_remove_power_chains(struct simple_pd *pd);

struct power_chain_head {
	struct list_head list;
};

struct power_chain {
	struct list_head list;
	struct notifier_block power_nb;
	struct power_control *ref;
	struct power_control *self;
};

/* dummy pd */
struct dummy_pd {
	struct pwrctrl_pd core;
	struct device_node *np;
	int on;
};

#define pc_to_dummy_pd(_pc) \
	container_of(_pc, struct dummy_pd, core.pc)
extern const struct power_control_ops dummy_ops;

/* power-controller */
struct power_controller_data {
	struct pwrctrl_pd **ppds;
	int num_ppds;
	struct generic_pm_domain **pds;
	struct genpd_onecell_data pd_data;
	struct power_control **pcs;
	struct power_control_onecell_data pc_data;
	int (*ready)(struct power_controller_data *);
};

int power_controller_add_of_providers(struct device *dev,
				      struct power_controller_data *pcd);
int power_controller_init_pds(struct device *dev,
			      struct power_controller_data *pcd);
extern const struct dev_pm_ops power_controller_pm_ops;

/* helper macros */

#define INIT_SRAM_CH_PD(_name, _off, _shift, _width)        \
{                                                           \
	.core.pd.name = "sram_ch_" #_name,                  \
	.core.pc.name = "sram_ch_" #_name,                  \
	.core.pc.ops =  &rtk_sram_ch_power_ops,             \
	.pwr_offset = _off,                                 \
	.shift = _shift,                                    \
	.width = _width,                                    \
}

#define INIT_ISO_POWER_CONTROL(_name, _off, _mask, _lock)   \
{                                                           \
	.core.pd.name = "iso_" #_name,                      \
	.core.pc.name = "iso_" #_name,                      \
	.core.pc.ops = &simple_power_ops,                   \
	.core.flags = RTK_PD_NO_GENPD,                      \
	.offset = _off,                                     \
	.mask = _mask,                                      \
	.val_on = 0,                                        \
	.val_off = _mask,                                   \
	.lock = _lock,                                      \
}

#define __INIT_SRAM_COMM(_name, _off, _ch, _ops, _flags, _lock) \
	                                                    \
	.core.pd.name = #_name,                             \
	.core.pc.name = #_name,                             \
	.core.pc.ops = _ops,                                \
	.core.flags = _flags,                               \
	.pwr_offset = _off,                                 \
	.last_sd_ch = _ch,                                  \
	.lock = _lock,

#define INIT_SRAM_PD(_name, _off, _ch, _lock)               \
{                                                           \
	__INIT_SRAM_COMM(sram_ ## _name, _off, _ch,	    \
		&rtk_sram_power_ops, 0, _lock)              \
}

#define INIT_SRAM_POWER_CONTROL(_name, _off, _ch,  _lock)   \
{                                                           \
	__INIT_SRAM_COMM(pctrl_ ## _name, _off, _ch,        \
		&rtk_sram_power_ops, RTK_PD_NO_GENPD,       \
		_lock)                                      \
}

#define INIT_SRAM_ASYNC_POWER_CONTROL(_name, _off, _ch, _time, _lock) \
{                                                           \
	__INIT_SRAM_COMM(pctrl_ ## _name, _off, _ch,        \
		&rtk_sram_async_power_ops, RTK_PD_NO_GENPD, \
		_lock)                                      \
	.expired_time = _time,                              \
}

#define INIT_SRAM_NC_PD(_name, _off, _off1, _ch, _lock)     \
{                                                           \
	__INIT_SRAM_COMM(sram_ ## _name, _off, _ch,	    \
		&rtk_sram_power_ops, 0, _lock)              \
	.pwr5_offset = _off1,                               \
}

#define INIT_SRAM_NC_POWER_CONTROL(_name, _off, _off1, _ch, _lock) \
{                                                           \
	__INIT_SRAM_COMM(pctrl_ ## _name, _off, _ch,        \
		&rtk_sram_power_ops, RTK_PD_NO_GENPD,       \
		_lock)                                      \
	.pwr5_offset = _off1,                               \
}

#define INIT_SRAM_NC_ASYNC_POWER_CONTROL(_name, _off, _off1, _ch, _time, _lock) \
{                                                           \
	__INIT_SRAM_COMM(pctrl_ ## _name, _off, _ch,        \
		&rtk_sram_async_power_ops, RTK_PD_NO_GENPD, \
		_lock)                                      \
	.pwr5_offset = _off1,                               \
	.expired_time = _time,                              \
}

#endif
