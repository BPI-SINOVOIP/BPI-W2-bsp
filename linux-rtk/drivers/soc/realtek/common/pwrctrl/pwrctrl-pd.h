/*
 * Power Control as Power Doamin
 *
 * Copyright (C) 2017-2018 Realtek Semiconductor Corporation
 * Copyright (C) 2017-2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __PWRCTRL_PD_H__
#define __PWRCTRL_PD_H__

#include <linux/pm_runtime.h>
#include <linux/pm_domain.h>
#include <linux/notifier.h>
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
 * @pm_prepare: original pm prepare callback, driver will fill it
 * @init: customized init function
 */
struct pwrctrl_pd {
	struct generic_pm_domain pd;
	struct power_control pc;

	struct device *dev;
	struct list_head list;

	/* callbacks */
	unsigned int flags;
	int (*init)(struct pwrctrl_pd *, void *);
};

#define RTK_PD_NO_GENPD           BIT(0)

#define pd_to_pwrctrl_pd(_pd) container_of(_pd, struct pwrctrl_pd, pd)
#define pc_to_pwrctrl_pd(_pc) container_of(_pc, struct pwrctrl_pd, pc)

struct pwrctrl_pd_initdata {
	void *base;
	struct device_node *np;
};

enum {
	RTK_PD_PM_SUSPEND,
	RTK_PD_PM_SUSPEND_LATE,
	RTK_PD_PM_RESUME_EARLY,
	RTK_PD_PM_RESUME,
};
void pwrctrl_pd_init(struct device *dev, struct pwrctrl_pd *pd,
	struct pwrctrl_pd_initdata *data);
void pwrctrl_pd_pm_notify(struct device *dev, int pd_pm_state);
int pwrctrl_pd_register_pm_notifier(struct notifier_block *nb);
void pwrctrl_pd_unregister_pm_notifier(struct notifier_block *nb);

static inline bool of_pwrctrl_pd_is_invalid(struct device_node *np,
	const char *name)
{
	return of_property_match_string(np, "invalid-power-domains", name)
		>= 0;
}

/* sram pd */
struct rtk_sram_pd {
	struct pwrctrl_pd core;
	void *base;
	unsigned int flags;
	unsigned int pwr_offset;
	unsigned int pwr5_offset;
	unsigned int last_sd_ch;
	unsigned int iso_offset;
	unsigned int iso_shift;

	unsigned int manual_mask;

	const char *rstn_name;
	struct device_node *np;

	struct timer_list timer;
	int expired_time;
	spinlock_t timer_lock;
	struct notifier_block pm_nb;
};

#define pc_to_rtk_sram_pd(_pc) container_of(_pc, struct rtk_sram_pd, core.pc)
#define pd_to_rtk_sram_pd(_pd) container_of(_pd, struct rtk_sram_pd, core.pd)

/* flags */
#define RTK_SRAM_PD_APPLY_MANUAL_MASK   0x1
#define RTK_SRAM_PD_NO_ISO_POW          0x2
#define RTK_SRAM_PD_NON_CONTIGUOUS_PWR  0x4

int rtk_sram_pd_init(struct pwrctrl_pd *pd, void *initdata);
extern const struct power_control_ops rtk_sram_ops;
extern const struct power_control_ops rtk_sram_async_ops;

/* sram ch pd */
struct rtk_sram_ch_pd {
	struct pwrctrl_pd core;
	void *base;
	unsigned int flags;
	unsigned int pwr_offset;
	int shift;
	int width;
};

#define pc_to_rtk_sram_ch_pd(_pc) \
	container_of(_pc, struct rtk_sram_ch_pd, core.pc)
#define pd_to_rtk_sram_ch_pd(_pd) \
	container_of(_pd, struct rtk_sram_ch_pd, core.pd)

int rtk_sram_ch_pd_init(struct pwrctrl_pd *pd, void *initdata);
extern const struct power_control_ops rtk_sram_ch_ops;

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

#define pc_to_rtk_analog_pd(_pc) \
	container_of(_pc, struct rtk_analog_pd, core.pc)
#define pd_to_rtk_analog_pd(_pd) \
	container_of(_pd, struct rtk_analog_pd, core.pd)

int rtk_analog_pd_init(struct pwrctrl_pd *pd, void *initdata);
extern const struct power_control_ops rtk_analog_ops;


/* dummy pd */
struct dummy_pd {
	struct pwrctrl_pd core;
	struct device_node *np;
	int on;
};

#define pc_to_dummy_pd(_pc) \
	container_of(_pc, struct dummy_pd, core.pc)
#define pd_to_dummy_pd(_pd) \
	container_of(_pd, struct dummy_pd, core.pd)

int dummy_pd_init(struct pwrctrl_pd *pd, void *initdata);
extern const struct power_control_ops dummy_ops;


/* power-controller */
struct power_controller_data {
	struct pwrctrl_pd **ppds;
	int num_ppds;
	struct generic_pm_domain **pds;
	struct genpd_onecell_data pd_data;
	struct power_control **pcs;
	struct power_control_onecell_data pc_data;
};

int power_controller_add_of_providers(struct device *dev,
	struct power_controller_data *pcd);
int power_controller_init_pds(struct device *dev,
	struct power_controller_data *pcd);

extern const struct dev_pm_ops power_controller_pm_ops;
#endif /* __PWRCTRL_PD_H__ */
