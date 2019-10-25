/*
 * Copyright (C) 2019 Realtek Semiconductor Corporation
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
 */

#ifndef __RTK_EVENT_H
#define __RTK_EVENT_H

struct notifier_block;

void rtk_clk_notify(struct clk *clk, unsigned int long event);
#define CLK_EVENT_REGISTERED            1

int rtk_clk_notifier_register(struct notifier_block *nb);
int rtk_clk_notifier_unregister(struct notifier_block *nb);


#endif /* __RTK_EVENT_H */
