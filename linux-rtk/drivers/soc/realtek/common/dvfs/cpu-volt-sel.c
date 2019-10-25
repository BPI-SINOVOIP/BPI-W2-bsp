/*
 * Realtek CPU volt sel
 *
 * Copyright (c) 2019, Realtek Semiconductor Corporation
 *
 * Author:
 *        Cheng-Yu Lee <cylee12@realtek.com>
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

#define pr_fmt(fmt) "cpu-volt-sel: " fmt

#include <linux/cpu.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/pm_opp.h>
#include <linux/module.h>
#include <soc/realtek/rtk_chip.h>
#include <soc/realtek/rtk_event.h>
#include <linux/clk.h>
#include <linux/notifier.h>

__maybe_unused
static int __chip_rev_to_prop_name(char *name, size_t size)
{
	unsigned int val;

	val = get_rtd_chip_revision();
	if ((val & 0xFFF) == 0) {
		pr_err("%s: invalid chip revision\n", __func__);
		return -EINVAL;
	}
	snprintf(name, size, "%x", val);
	return 0;
}

#define DSS7      0xA28

static const struct of_device_id rtk_scpu_wrapper_ids[] __initconst = {
	{.compatible = "Realtek,rtk-scpu_wrapper"},
	{}
};

__maybe_unused
static int __dss_to_prop_name(char *name, size_t size)
{
	struct device_node *np;
	void *base;
	unsigned int val;

	np = of_find_matching_node(NULL, rtk_scpu_wrapper_ids);
	if (!np) {
		pr_err("%s: failed to find device node\n", __func__);
		return -ENODEV;
	}

	base = of_iomap(np, 0);
	if (!base) {
		pr_err("%s: failed to ioremap\n", __func__);
		return -ENOMEM;
	}

	val = readl(base + DSS7) & 0xfffff;
	BUG_ON(val > 26000);
	if (val > 23000)
		snprintf(name, size, "ss");
	else
		snprintf(name, size, "tt");
	iounmap(base);
	return 0;
}

static int cpu_dev_set_prop_name(void)
{
	struct device *dev;
	char buf[20];
	int ret;

	/*
	 * NOTE: arm64 register cpu device in topology_init(),
	 *       which is in subsys_initcall.
	 */
	dev = get_cpu_device(0);
	if (!dev) {
		pr_err("failed to get cpu device\n");
		return -EINVAL;
	}

#if defined(CONFIG_RTK_CPU_VOLT_SEL_CHIP_REV)
	ret = __chip_rev_to_prop_name(buf, sizeof(buf));
#elif defined(CONFIG_RTK_CPU_VOLT_SEL_DSS)
	ret = __dss_to_prop_name(buf, sizeof(buf));
#else
	ret = -EINVAL;
#endif
	if (ret)
		return ret;

	pr_info("dev_pm_opp_set_prop_name: name=%s\n", buf);

	dev_pm_opp_set_prop_name(dev, buf);
	return 0;
}

static int cpu_volt_sel_cb(struct notifier_block *nb, unsigned long event,
			   void *data)
{
	struct clk *clk;
	bool match;

	if (event != CLK_EVENT_REGISTERED)
		return NOTIFY_DONE;

	clk = clk_get(NULL, "pll_scpu");
	if (IS_ERR_OR_NULL(clk))
		return NOTIFY_DONE;

	match = clk_is_match(clk, data);
	clk_put(clk);

	if (!match)
		return NOTIFY_DONE;

	cpu_dev_set_prop_name();

	return NOTIFY_OK;
}

struct notifier_block cpu_volt_sel_nb = {
	.notifier_call = cpu_volt_sel_cb,
};

static __init int cpu_volt_sel_init(void)
{
	struct clk *clk;

	clk = clk_get(NULL, "pll_scpu");
	if (IS_ERR_OR_NULL(clk)) {
		pr_info("pll_scpu not ready: register rtk-clk-event\n");
		rtk_clk_notifier_register(&cpu_volt_sel_nb);
		return 0;
	}
	clk_put(clk);
	return cpu_dev_set_prop_name();
}
subsys_initcall_sync(cpu_volt_sel_init);
