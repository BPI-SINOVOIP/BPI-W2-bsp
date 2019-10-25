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

#include <linux/notifier.h>
#include <linux/clk-provider.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");

static ATOMIC_NOTIFIER_HEAD(rtk_clk_notifier);

void rtk_clk_notify(struct clk *clk, unsigned int long event)
{
	atomic_notifier_call_chain(&rtk_clk_notifier, event, clk);
}

int rtk_clk_notifier_register(struct notifier_block *nb)
{
	return atomic_notifier_chain_register(&rtk_clk_notifier, nb);
}
EXPORT_SYMBOL_GPL(rtk_clk_notifier_register);

int rtk_clk_notifier_unregister(struct notifier_block *nb)
{
        return atomic_notifier_chain_unregister(&rtk_clk_notifier, nb);
}
EXPORT_SYMBOL_GPL(rtk_clk_notifier_unregister);

