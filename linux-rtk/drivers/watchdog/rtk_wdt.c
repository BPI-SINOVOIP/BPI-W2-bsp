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
#include <linux/interrupt.h>
#include <linux/sysrq.h>
#include <soc/realtek/rtk_wdt.h>

#define TCWCR 0x0
#define TCWTR 0x4
#define TCWNMI 0x8
#define TCWOV 0xc


#define MSK_ISR	0x0c


#define TCWOV_RSTB_CNT 0x40
#define TCWOV_RSTB_PAD 0x44
static int watchdog_oe = -1;

#define ISO_WDT_CLK (27000000) /* 27 MHz */
#define ISO_WDT_1MS_CNT (27000)

struct rtk_wdt {
	struct watchdog_device wdt;
	struct clk *clk;
	unsigned long rate;
	struct notifier_block restart_nb;
	void __iomem *wdt_base;
	void __iomem *misc_base;
	void __iomem *iso_base;
	unsigned int expire;
	int 	irq;
	struct notifier_block iso_reset_nb;
	struct notifier_block sysrq_nb;
};

typedef enum {
	WAKE_PWR = 0,
	WAKE_SOFT,
	WAKE_WDT,
	WAKE_BUTTON,
} WAKE_UP_REAONS;

static WAKE_UP_REAONS wake_up_reason = WAKE_PWR;
struct rtk_wdt *rtk_wdt_p = NULL;
static ATOMIC_NOTIFIER_HEAD(rtk_wdt_notifier_chain);

int rtk_wdt_register_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_register(&rtk_wdt_notifier_chain, nb);
}
EXPORT_SYMBOL_GPL(rtk_wdt_register_notifier);

int rtk_wdt_unregister_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_unregister(&rtk_wdt_notifier_chain, nb);
}
EXPORT_SYMBOL_GPL(rtk_wdt_unregister_notifier);

static int __rtk_wdt_notify(void)
{
	return atomic_notifier_call_chain(&rtk_wdt_notifier_chain, 0 , NULL);
}

static int wakeupreason_config(char *str)
{
	if (!str)
		return -EINVAL;
	if (strcmp(str, "software") == 0)
		wake_up_reason = WAKE_SOFT;
	else if (strcmp(str, "watchdog") == 0)
		wake_up_reason = WAKE_WDT;
	else
		pr_err("%s: invalid wakeupreason \"%s\"\n", __func__, str);

	return 0;
}
early_param("wakeupreason", wakeupreason_config);

static int rtk_wdt_start(struct watchdog_device *wdd)
{
	int ret = 0;
	struct rtk_wdt *wdt = container_of(wdd, struct rtk_wdt, wdt);
	void __iomem *base = wdt->iso_base;

	if (base)	
		writel(0x00800000, base + TCWOV_RSTB_CNT);

	base = wdt->wdt_base;	
	writel(0x800000FF, base + TCWCR);                           /* enable Watchdog & NMI */  

	wdt->expire = wdd->timeout + ktime_to_timespec(ktime_get()).tv_sec;	
	return ret;
}

static int rtk_wdt_stop(struct watchdog_device *wdd)
{
	int ret = 0;
	struct rtk_wdt *wdt = container_of(wdd, struct rtk_wdt, wdt);
	void __iomem *base = wdt->wdt_base;

	writel(0xA5, base + TCWCR );

	return ret;
}

static int rtk_wdt_ping(struct watchdog_device *wdd)
{
	int ret = 0;
	struct rtk_wdt *wdt = container_of(wdd, struct rtk_wdt, wdt);
	void __iomem *base = wdt->wdt_base;

	writel(0x01, base + TCWTR);
	wdt->expire = wdd->timeout + ktime_to_timespec(ktime_get()).tv_sec;	

	return ret;
}

static int rtk_wdt_set_timeout(struct watchdog_device *wdd,
	unsigned int timeout)
{
	int ret = 0;
	struct rtk_wdt *wdt = container_of(wdd, struct rtk_wdt, wdt);
	void __iomem *base = wdt->wdt_base;

	writel(0xA5, base + TCWCR);
	writel(0x01, base + TCWTR);
	writel((timeout * 1000 * ISO_WDT_1MS_CNT), base + TCWOV);
	writel(0x800000FF, base + TCWCR);                           /* enable Watchdog & NMI */  

	wdd->timeout = timeout;	
	wdt->expire = wdd->timeout + ktime_to_timespec(ktime_get()).tv_sec;	

	return ret;
}


static int rtk_wdt_set_pretimeout(struct watchdog_device *wdd,
	unsigned int timeout)
{
	int ret = 0;
	struct rtk_wdt *wdt = container_of(wdd, struct rtk_wdt, wdt);
	void __iomem *base = wdt->wdt_base;
	unsigned int tmp_timeout;

	if (timeout == 0) {
		/* disable NMI interrupt */
		writel(0x00, base + TCWCR);
		return ret;	
	}

	tmp_timeout = wdd->timeout - timeout ;

	writel(0xA5, base + TCWCR);
	writel(0x01, base + TCWTR);
	writel((tmp_timeout * 1000 * ISO_WDT_1MS_CNT), base + TCWNMI);
	writel(0x800000FF, base + TCWCR);                           /* enable Watchdog & NMI */  

	wdd->pretimeout = timeout;
	
	return ret;
}

static unsigned int rtk_wdt_gettimeleft(struct watchdog_device *wdd)
{
	struct rtk_wdt *wdt = container_of(wdd, struct rtk_wdt, wdt);

	return wdt->expire - ktime_to_timespec(ktime_get()).tv_sec;
}

static void  rtk_wdt_set_bootstatus(struct watchdog_device *wdd)
{
	switch (wake_up_reason) {
		case WAKE_PWR:
			wdd->bootstatus = WDIOF_POWERUNDER;
			break;
		case WAKE_SOFT:
			wdd->bootstatus = WDIOF_EXTERN1;
			break;
		case WAKE_WDT:
			wdd->bootstatus = WDIOF_CARDRESET;
			break;
		case WAKE_BUTTON:
			wdd->bootstatus = WDIOF_EXTERN2;
			break;
		default:
			pr_err("%s: invalid wake_up_reason %d\n", __func__, wake_up_reason);
			wdd->bootstatus = WDIOF_POWERUNDER;
	}
}

static int rtk_wdt_restart(struct notifier_block *nb, unsigned long action,
	void *data)
{
	struct rtk_wdt *wdt = container_of(nb, struct rtk_wdt, restart_nb);
	struct watchdog_device *wdd;
	void __iomem *base = wdt->wdt_base;
	u32 timeout = 20 * 1000;

	wdd = &(wdt->wdt); 
	writel(0xA5, base + TCWCR);
	writel(0x01, base + TCWTR);
	writel((timeout * ISO_WDT_1MS_CNT), base + TCWOV);
	writel(((timeout - 2) * ISO_WDT_1MS_CNT), base + TCWNMI);   /* for NMI */
	writel(0x800000FF, base + TCWCR);                           /* enable Watchdog & NMI */  

	wdt->wdt.timeout = 20;
	wdt->expire = wdd->timeout + ktime_to_timespec(ktime_get()).tv_sec;	

	msleep(150);
	return NOTIFY_DONE;
}

static irqreturn_t rtk_wdt_irq(int irq, void *devid)
{
        struct rtk_wdt *wdt = devid;
	void __iomem *base = wdt->misc_base;	
	int value = readl(base + MSK_ISR);
	/* check watchdog NMI INT status */
    	if(!(value & 0x04)) 
        	return IRQ_NONE;

	pr_err("%s WATCHDOG NMI INT \n", __func__);
	/* clear watchdog NMI INT status */
	writel(0x04, base + MSK_ISR);     

	rtk_wdt_stop(&(wdt->wdt));

	__rtk_wdt_notify();
        return IRQ_HANDLED;
}

static int rtk_wdt_sysrq_cb(struct notifier_block *nb,
			    unsigned long v, void *p)
{
	handle_sysrq('9');
	dump_stack();
	handle_sysrq('w');
	handle_sysrq('l');
	/* dump memory stats */
	handle_sysrq('m');
	handle_sysrq('p');
	handle_sysrq('q');
	/* dump scheduler state */
	handle_sysrq('t');
	handle_sysrq('z');
	return NOTIFY_OK;
}

static int rtk_wdt_iso_reset_cb(struct notifier_block *nb,
				unsigned long v, void *p)
{
	struct rtk_wdt *wdt = container_of(nb, struct rtk_wdt, iso_reset_nb);
	void *base = wdt->iso_base;

	mdelay(200);
	/* only ISO watchdog can handle oe ouptput , force us to use it instead of MISC watchdog*/
	writel(0xA5, base + TCWCR);
	writel(0x01, base + TCWTR);
	writel((0x0 * ISO_WDT_1MS_CNT), base + TCWOV);
	writel(0x000000FF, base + TCWCR);
	for (;;);
	return NOTIFY_OK;
}

int set_wdt_oe(void)
{
	if (watchdog_oe < 0)
		return -EINVAL;

	if (!rtk_wdt_p || !rtk_wdt_p->iso_base)
		return -ENXIO;

	writel(watchdog_oe, rtk_wdt_p->iso_base + TCWOV_RSTB_PAD);
	pr_info("[%s] set watchdog-oe to %d\n", KBUILD_MODNAME, watchdog_oe);

	return 0;
}
EXPORT_SYMBOL(set_wdt_oe);

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
	.set_pretimeout = rtk_wdt_set_pretimeout,
	.get_timeleft	= rtk_wdt_gettimeleft,

};

static int rtk_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np;
	struct rtk_wdt *rtk_wdt;
	struct resource *res;
	int ret = 0;
	int init_oe = 0;

	pr_err("[%s] %s enter\n", KBUILD_MODNAME, __func__);

	rtk_wdt = devm_kzalloc(&pdev->dev, sizeof(*rtk_wdt), GFP_KERNEL);
	if (!rtk_wdt)
		return -ENOMEM;

	if (WARN_ON(!(pdev->dev.of_node))) {
		pr_err("Error: No node\n");
		return -ENODEV;
	}

	np = pdev->dev.of_node;

	rtk_wdt->wdt_base =of_iomap(np, 0);
	if (IS_ERR(rtk_wdt->wdt_base))
		return PTR_ERR(rtk_wdt->wdt_base);

	rtk_wdt->iso_base = of_iomap(np, 2);
	if (IS_ERR(rtk_wdt->iso_base))
		return PTR_ERR(rtk_wdt->iso_base);

	/* set pin direction for pmic reset signal */
	if (!of_property_read_u32_index(np,
		"rst-oe-for-init", 0, &init_oe)) {
		pr_err("[%s] init_oe = 0x%x \n", KBUILD_MODNAME, init_oe);
		writel(0x00800000, rtk_wdt->iso_base + TCWOV_RSTB_CNT);
		writel(init_oe, rtk_wdt->iso_base + TCWOV_RSTB_PAD);
	}

	if (!of_property_read_u32_index(np,
		"rst-oe", 0, &watchdog_oe))
		pr_info("[%s] rst-oe = 0x%x\n", KBUILD_MODNAME, watchdog_oe);

	rtk_wdt->wdt.info = &rtk_wdt_info;
	rtk_wdt->wdt.ops = &rtk_wdt_ops;
	rtk_wdt->wdt.min_timeout = 1;
	rtk_wdt->wdt.max_timeout = 128;

	watchdog_init_timeout(&rtk_wdt->wdt, 0, &pdev->dev);

	/* Set default timeout value 20s*/
	rtk_wdt_set_timeout(&rtk_wdt->wdt, 20);
	rtk_wdt_set_pretimeout(&rtk_wdt->wdt, 8);
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

	rtk_wdt->iso_reset_nb.notifier_call = rtk_wdt_iso_reset_cb;
	rtk_wdt->iso_reset_nb.priority = RTK_WATCHDOG_NMI_PRI_ISO_RESET;
	ret = rtk_wdt_register_notifier(&rtk_wdt->iso_reset_nb);
	if (ret)
		dev_warn(dev, "failed to register rtk_wdt notifier: %d\n", ret);

	rtk_wdt->sysrq_nb.notifier_call = rtk_wdt_sysrq_cb;
	rtk_wdt->sysrq_nb.priority = RTK_WATCHDOG_NMI_PRI_SYSRQ;
	ret = rtk_wdt_register_notifier(&rtk_wdt->sysrq_nb);
	if (ret)
		dev_warn(dev, "failed to register rtk_wdt notifier: %d\n", ret);

	platform_set_drvdata(pdev, rtk_wdt);

	rtk_wdt->irq = platform_get_irq(pdev, 0);
        if (rtk_wdt->irq > 0) {
		/* ARM does not support NMI interrupt directly so software can configure
		 the GIC to come up a non-maskable interrupt.*/	
		ret = devm_request_irq(&pdev->dev, rtk_wdt->irq,
			rtk_wdt_irq, 0, pdev->name, rtk_wdt);
		if (ret < 0){
                        dev_err(&pdev->dev, "failed to request IRQ\n");
		}
		else {
			res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
			rtk_wdt->misc_base = devm_ioremap_resource(&pdev->dev, res);
			if (IS_ERR(rtk_wdt->misc_base))
				return PTR_ERR(rtk_wdt->misc_base);
		}
		
	}
	else {
        	dev_err(&pdev->dev, "no irq specified\n");
        }

	rtk_wdt_set_bootstatus(&rtk_wdt->wdt);
	rtk_wdt_p = rtk_wdt;

	pr_err("[%s] %s exit\n", KBUILD_MODNAME, __func__);

	return ret;
}

static int rtk_wdt_remove(struct platform_device *pdev)
{
	struct rtk_wdt *wdt = platform_get_drvdata(pdev);

	rtk_wdt_unregister_notifier(&wdt->sysrq_nb);
	rtk_wdt_unregister_notifier(&wdt->iso_reset_nb);
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
