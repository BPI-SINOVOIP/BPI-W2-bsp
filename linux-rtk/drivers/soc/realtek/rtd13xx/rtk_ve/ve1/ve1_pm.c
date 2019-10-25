/*
 * ve1_pm.c - ve1 power management
 *
 * Copyright (c) 2019 Realtek Semiconductor Corporation
 *
 * Author:
 *      Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <linux/atomic.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/reset.h>
#include <soc/realtek/power-control.h>
#include "ve1_pm.h"

#define MAX_VE_PD_NUM 2

static const struct ve_pd_desc desc[MAX_VE_PD_NUM] = {
	{
		.name = "ve1",
		.has_rstc_bist = 1,
		.has_rstc = 1,
		.has_power = 1,
	},
	{
		.name = "ve3",
		.has_rstc_bist = 1,
		.has_rstc = 1,
		.has_power = 1,
	},
};

static struct ve_pd_data data[MAX_VE_PD_NUM];

static int ve_pd_power_callback(struct notifier_block *nb, unsigned long action,
				void *p)
{
	struct ve_pd_data *vpd = container_of(nb, struct ve_pd_data, pc_nb);

	if (action != POWER_CONTROL_ACTION_POST_POWER_ON)
		return NOTIFY_DONE;

	pr_debug("pd%d: %s: reset\n", vpd->idx, __func__);
	if (vpd->rstc)
		reset_control_reset(vpd->rstc);
	return NOTIFY_OK;
}

int ve_pd_init(struct device *dev, int idx)
{
	char name[20];
	const struct ve_pd_desc *d = &desc[idx];
	struct ve_pd_data *vpd = &data[idx];
	int ret;

	vpd->idx = idx;

	if (!d->has_power)
		goto ignore_init_power;

	snprintf(name, sizeof(name), "pctrl_%s", d->name);
	vpd->pctrl = power_control_get(name);
	if (IS_ERR(vpd->pctrl)) {
		ret = PTR_ERR(vpd->pctrl);
		dev_warn(dev, "pd%d: failed to get power_control %s: %d\n",
			 idx, name, ret);
		vpd->pctrl = NULL;
	}

	vpd->pc_nb.notifier_call = ve_pd_power_callback;
	power_control_register_notifier(vpd->pctrl, &vpd->pc_nb);

ignore_init_power:

	snprintf(name, sizeof(name), "clk_%s", d->name);
	vpd->clk = devm_clk_get(dev, name);
	if (IS_ERR(vpd->clk)) {
		ret = PTR_ERR(vpd->clk);
		dev_warn(dev, "pd%d: failed to get clk %s: %d\n",
			 idx, name, ret);
		vpd->clk = NULL;
	}

	if (!d->has_rstc)
		goto ignore_init_rstc;

	snprintf(name, sizeof(name), "%s", d->name);
	vpd->rstc = devm_reset_control_get(dev, name);
	if (IS_ERR(vpd->rstc)) {
		ret = PTR_ERR(vpd->rstc);
		dev_warn(dev, "pd%d: failed to get reset control %s: %d\n",
			 idx, name, ret);
		vpd->rstc = NULL;
	}

ignore_init_rstc:

	if (!d->has_rstc)
		goto ignore_init_rstc_bist;

	snprintf(name, sizeof(name), "%s_bist", d->name);
	vpd->rstc_bist = devm_reset_control_get(dev, name);
	if (IS_ERR(vpd->rstc_bist)) {
		ret = PTR_ERR(vpd->rstc_bist);
		dev_warn(dev, "pd%d: failed to get reset control %s: %d\n",
			 idx, name, ret);
		vpd->rstc_bist = NULL;
	}

ignore_init_rstc_bist:

	atomic_set(&vpd->power_cnt, 0);

	if (vpd->rstc)
		reset_control_deassert(vpd->rstc);
	if (vpd->rstc_bist)
		reset_control_deassert(vpd->rstc_bist);

	return 0;
}

void ve_pd_exit(struct device *dev, int idx)
{
	struct ve_pd_data *vpd = &data[idx];

	WARN(atomic_read(&vpd->power_cnt) != 0, "not power off\n");

	if (vpd->rstc)
		reset_control_assert(vpd->rstc);
	if (vpd->rstc_bist)
		reset_control_assert(vpd->rstc_bist);

	if (vpd->pctrl) {
		power_control_unregister_notifier(vpd->pctrl, &vpd->pc_nb);
		power_control_put(vpd->pctrl);
	}
}

int ve_pd_power_on(int idx)
{
	struct ve_pd_data *vpd = &data[idx];

	pr_debug("pd%d: %s\n", idx, __func__);

	if (atomic_inc_return(&vpd->power_cnt) != 1)
		return 0;

	pr_debug("pd%d: %s: power_cnt=%d\n", idx, __func__,
		atomic_read(&vpd->power_cnt));

	power_control_power_on(vpd->pctrl);
	clk_prepare_enable(vpd->clk);

	return 0;
}

int ve_pd_power_off(int idx)
{
	struct ve_pd_data *vpd = &data[idx];

	pr_debug("pd%d: %s\n", idx, __func__);

	if (atomic_dec_return(&vpd->power_cnt) != 0)
		return 0;

	pr_debug("pd%d: %s: power_cnt=%d\n", idx, __func__,
		atomic_read(&vpd->power_cnt));

	clk_disable_unprepare(vpd->clk);
	power_control_power_off(vpd->pctrl);
	return 0;
}


int ve_pd_reset_control_reset(int idx)
{
	struct ve_pd_data *vpd = &data[idx];

	if (WARN_ON(!vpd->rstc))
		return -EINVAL;

	return reset_control_reset(vpd->rstc);
}

int ve_pd_clk_set_parent(int idx, const char *parent_name)
{
	struct ve_pd_data *vpd = &data[idx];
	struct clk *clk;
	int ret;

	if (!parent_name)
		return -EINVAL;

	if (atomic_read(&vpd->power_cnt) != 0)
		return -EBUSY;

	clk = clk_get(NULL, parent_name);
	if (IS_ERR_OR_NULL(clk))
		return -EINVAL;

	pr_debug("pd%d: %s: parent=%s\n", idx, __func__, parent_name);

	ret = clk_set_parent(vpd->clk, clk);
	clk_put(clk);

	return ret;
}

int ve_pd_clk_parent_match(int idx, const char *clk_name)
{
	struct ve_pd_data *vpd = &data[idx];
	struct clk *clk;
	struct clk *pclk;
	bool is_match;

	if (!clk_name)
		return -EINVAL;

	clk = clk_get(NULL, clk_name);
	if (IS_ERR_OR_NULL(clk))
		return -EINVAL;

	pclk = clk_get_parent(vpd->clk);

	is_match = clk_is_match(pclk, clk);
	clk_put(clk);

	return is_match ? 1 : 0;
}


int ve_pd_clk_set_rate(int idx, unsigned long rate)
{
	struct ve_pd_data *vpd = &data[idx];
	struct clk *clk;
	struct clk *pclk;
	bool is_match;

	/* should not set rate if parent is clk_sysh */
	clk = clk_get(NULL, "clk_sysh");
	if (IS_ERR_OR_NULL(clk))
		return -EINVAL;

	pclk = clk_get_parent(vpd->clk);

	is_match = clk_is_match(pclk, clk);
	clk_put(clk);

	if (is_match)
		return -EPERM;

	pr_debug("pd%d: %s: rate=%ld\n", idx, __func__, rate);

	return clk_set_rate(vpd->clk, rate);
}

unsigned long ve_pd_clk_get_rate(int idx)
{
	struct ve_pd_data *vpd = &data[idx];

	return clk_get_rate(vpd->clk);
}

