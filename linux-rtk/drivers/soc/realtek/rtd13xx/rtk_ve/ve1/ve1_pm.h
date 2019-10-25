/*
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
#ifndef __VE1_PM_H
#define __VE1_PM_H

#include <linux/atomic.h>
#include <linux/notifier.h>

struct clk;
struct reset_control;
struct power_control;

struct ve_pd_desc {
	const char *name;
	int has_rstc_bist:1;
	int has_rstc:1;
	int has_power:1;
};

struct ve_pd_data {
	int idx;
	struct clk *clk;
	struct reset_control *rstc;
	struct reset_control *rstc_bist;
	struct power_control *pctrl;
	struct notifier_block pc_nb;
	atomic_t power_cnt;
};

int ve_pd_init(struct device *dev, int idx);
void ve_pd_exit(struct device *dev, int idx);
int ve_pd_power_on(int idx);
int ve_pd_power_off(int idx);
int ve_pd_reset_control_reset(int idx);
int ve_pd_clk_parent_match(int idx, const char *clk_name);
int ve_pd_clk_set_parent(int idx, const char *parent_name);
int ve_pd_clk_set_rate(int idx, unsigned long rate);
unsigned long ve_pd_clk_get_rate(int idx);

#endif
