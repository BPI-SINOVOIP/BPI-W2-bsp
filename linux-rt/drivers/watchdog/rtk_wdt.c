/*
 * rtk_wdt.c -  Realtek watchdog driver
 *
 * Copyright (c) 2018 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#include <linux/io.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/notifier.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/reboot.h>
#include <linux/regmap.h>
#include <linux/timer.h>
#include <linux/watchdog.h>

#define ISO_WDT_CTL 0x0
#define ISO_WDT_CLR 0x4
#define ISO_WDT_NMI 0x8
#define ISO_WDT_OVERFLOW 0xC
#define ISO_WDT_RSTB_CNT 0x40

#ifdef CONFIG_ARCH_RTD139x
#define ISO_WDT_RSTB_PAD 0x44
static int watchdog_oe;
#endif

#define ISO_WDT_CLK (27000000) /* 27 MHz */
#define ISO_WDT_1MS_CNT (27000)

struct rtk_wdt {
	struct watchdog_device wdt;
	struct clk *clk;
	unsigned long rate;
	struct notifier_block restart_nb;
	void __iomem *wdt_base;
};

static int rtk_wdt_start(struct watchdog_device *wdd)
{
	int ret = 0;
	struct rtk_wdt *wdt = container_of(wdd, struct rtk_wdt, wdt);
	void __iomem *base = wdt->wdt_base;

	writel(0x00800000, base + ISO_WDT_RSTB_CNT);
	writel(0xFF, base + ISO_WDT_CTL);

	return ret;
}

static int rtk_wdt_stop(struct watchdog_device *wdd)
{
	int ret = 0;
	struct rtk_wdt *wdt = container_of(wdd, struct rtk_wdt, wdt);
	void __iomem *base = wdt->wdt_base;

	writel(0xA5, base + ISO_WDT_CTL);

	return ret;
}

static int rtk_wdt_ping(struct watchdog_device *wdd)
{
	int ret = 0;
	struct rtk_wdt *wdt = container_of(wdd, struct rtk_wdt, wdt);
	void __iomem *base = wdt->wdt_base;

	writel(0x01, base + ISO_WDT_CLR);

	return ret;
}

static int rtk_wdt_set_timeout(struct watchdog_device *wdd,
	unsigned int timeout)
{
	int ret = 0;
	struct rtk_wdt *wdt = container_of(wdd, struct rtk_wdt, wdt);
	void __iomem *base = wdt->wdt_base;

	timeout = timeout * 1000;

	writel(0xA5, base + ISO_WDT_CTL);
	writel(0x01, base + ISO_WDT_CLR);
	writel((timeout * ISO_WDT_1MS_CNT), base + ISO_WDT_OVERFLOW);
	writel(0xFF, base + ISO_WDT_CTL);

	return ret;
}

static int rtk_wdt_restart(struct notifier_block *nb, unsigned long action,
	void *data)
{
	struct rtk_wdt *wdt = container_of(nb, struct rtk_wdt, restart_nb);
	void __iomem *base = wdt->wdt_base;
	u32 timeout = 20 * 1000;

	writel(0xA5, base + ISO_WDT_CTL);
	writel(0x01, base + ISO_WDT_CLR);
	writel((timeout * ISO_WDT_1MS_CNT), base + ISO_WDT_OVERFLOW);
	writel(0xFF, base + ISO_WDT_CTL);

	msleep(150);
	return NOTIFY_DONE;
}

static const struct watchdog_info rtk_wdt_info = {
	.identity = "Realtek watchdog",
	.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE,
};

static const struct watchdog_ops rtk_wdt_ops = {
	.owner = THIS_MODULE,
	.start = rtk_wdt_start,
	.stop = rtk_wdt_stop,
	.ping = rtk_wdt_ping,
	.set_timeout = rtk_wdt_set_timeout,
};

static int rtk_wdt_probe(struct platform_device *pdev)
{
	struct rtk_wdt *rtk_wdt;
	struct resource *res;
	int ret = 0;

	pr_info("[%s] %s enter\n", KBUILD_MODNAME, __func__);

	rtk_wdt = devm_kzalloc(&pdev->dev, sizeof(*rtk_wdt), GFP_KERNEL);
	if (!rtk_wdt)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	rtk_wdt->wdt_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(rtk_wdt->wdt_base))
		return PTR_ERR(rtk_wdt->wdt_base);

#ifdef CONFIG_ARCH_RTD139x
	if (of_property_read_u32_index(pdev->dev.of_node,
		"rst-oe-for-init", 0, &watchdog_oe))
		watchdog_oe = -1;

	 /* set pin direction for pmic reset signal */
	if (watchdog_oe >= 0)
		writel(watchdog_oe, rtk_wdt->wdt_base + ISO_WDT_RSTB_PAD);
#endif

	rtk_wdt->wdt.info = &rtk_wdt_info;
	rtk_wdt->wdt.ops = &rtk_wdt_ops;
	rtk_wdt->wdt.min_timeout = 1;
	rtk_wdt->wdt.max_timeout = 128;

	watchdog_init_timeout(&rtk_wdt->wdt, 0, &pdev->dev);

	/* Set default timeout value 20s*/
	rtk_wdt_set_timeout(&rtk_wdt->wdt, 20);
	rtk_wdt_stop(&rtk_wdt->wdt);

	watchdog_set_drvdata(&rtk_wdt->wdt, rtk_wdt);
	ret = watchdog_register_device(&rtk_wdt->wdt);
	if (ret) {
		dev_err(&pdev->dev, "cannot register watchdog device\n");
		return ret;
	}

	rtk_wdt->restart_nb.notifier_call = rtk_wdt_restart;
	ret = register_restart_handler(&rtk_wdt->restart_nb);
	if (ret)
		dev_err(&pdev->dev, "failed to setup restart handler\n");

	platform_set_drvdata(pdev, rtk_wdt);

	pr_info("[%s] %s exit\n", KBUILD_MODNAME, __func__);

	return ret;
}

static int rtk_wdt_remove(struct platform_device *pdev)
{
	struct rtk_wdt *wdt = platform_get_drvdata(pdev);

	unregister_restart_handler(&wdt->restart_nb);
	watchdog_unregister_device(&wdt->wdt);

	return 0;
}

static const struct of_device_id rtk_wdt_of_table[] = {
	{ .compatible = "realtek,rtk-watchdog" },
	{ },
};
MODULE_DEVICE_TABLE(of, rtk_wdt_of_table);

static struct platform_driver rtk_watchdog_driver = {
	.probe = rtk_wdt_probe,
	.remove = rtk_wdt_remove,
	.driver = {
		.name = KBUILD_MODNAME,
		.of_match_table = rtk_wdt_of_table,
	},
};
module_platform_driver(rtk_watchdog_driver);

MODULE_DESCRIPTION("Realtek Watchdog Driver");
MODULE_LICENSE("GPL v2");
