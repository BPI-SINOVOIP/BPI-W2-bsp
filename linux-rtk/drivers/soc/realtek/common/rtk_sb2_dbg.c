/*
 * rtk_sb2_dbg.c - bus debug driver
 *
 * Copyright (c) 2017-2019 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/notifier.h>
#include <linux/ktime.h>
#include <linux/debugfs.h>
#include <asm/system_misc.h>

#include <soc/realtek/rtk_sb2_dbg.h>
#include "include/rtk_sb2.h"

#define DRIVER_NAME "RTK_SB2_DBG"
#define sb2_info(fmt, ...)  pr_info("[%s] " fmt, DRIVER_NAME, ##__VA_ARGS__)
#define sb2_err(fmt, ...)   pr_err("[%s] " fmt, DRIVER_NAME, ##__VA_ARGS__)
#define sb2_err_hl(fmt, ...)   pr_err("\033[0;31m[%s] " fmt "\033[m\n", DRIVER_NAME, ##__VA_ARGS__)
#define sb2_dbg(fmt, ...)   pr_debug("[%s] " fmt, DRIVER_NAME, ##__VA_ARGS__)

static int sb2_default_handler_enable = 1;
static struct sb2_data *sb2_data;
static ATOMIC_NOTIFIER_HEAD(sb2_dbg_notifier);
static ATOMIC_NOTIFIER_HEAD(sb2_inv_notifier);
static const char *inv_cpu_str[] = {
	[SB2_INV_SCPU_SWC] = "SCPU security world",
	[SB2_INV_SCPU]     = "SCPU",
	[SB2_INV_ACPU]     = "ACPU",
	[SB2_INV_PCPU]     = "PCPU",
};


int sb2_dbg_register_dbg_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_register(&sb2_dbg_notifier, nb);
}
EXPORT_SYMBOL_GPL(sb2_dbg_register_dbg_notifier);

int sb2_dbg_unregister_dbg_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_unregister(&sb2_dbg_notifier, nb);
}
EXPORT_SYMBOL_GPL(sb2_dbg_unregister_dbg_notifier);

static void __notify_dbg_int(struct sb2_dbg_event_data *data)
{
	atomic_notifier_call_chain(&sb2_dbg_notifier, 0, data);
}

int sb2_dbg_register_inv_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_register(&sb2_inv_notifier, nb);
}
EXPORT_SYMBOL_GPL(sb2_dbg_register_inv_notifier);

int sb2_dbg_unregister_inv_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_unregister(&sb2_inv_notifier, nb);
}
EXPORT_SYMBOL_GPL(sb2_dbg_unregister_inv_notifier);

static void __notify_inv_int(struct sb2_inv_event_data *data)
{
	atomic_notifier_call_chain(&sb2_inv_notifier, 0, data);
}

static int sb2_dbg_default_inv_callback(struct notifier_block *nb, unsigned long action, void *data)
{
	struct sb2_inv_event_data *d = data;

	if (!sb2_default_handler_enable)
		return NOTIFY_DONE;

	sb2_err("sb2 get int 0x%08x from SB2_INV_INTSTAT\n", d->raw_ints);
	sb2_err_hl("Invalid access issued by %s", inv_cpu_str[d->inv_cpu]);
	sb2_err_hl("Invalid address is 0x%x", d->addr);
	sb2_err("Timeout threshold(0x%08x)\n", d->timeout_th);
	return NOTIFY_OK;
}

static struct notifier_block sb2_dbg_default_inv_nb = {
	.notifier_call = sb2_dbg_default_inv_callback,
	.priority = -1,
};

static int sb2_dbg_default_dbg_callback(struct notifier_block *nb, unsigned long action, void *data)
{
	struct sb2_dbg_event_data *d = data;

	if (!sb2_default_handler_enable)
		return NOTIFY_DONE;

	sb2_err("sb2 get int 0x%08x from SB2_DBG_INT\n", d->raw_ints);
	return NOTIFY_OK;
}

static struct notifier_block sb2_dbg_default_dbg_nb = {
	.notifier_call = sb2_dbg_default_dbg_callback,
	.priority = -1,
};

void sb2_dbg_disable_default_handlers(void)
{
	sb2_default_handler_enable = 0;
}
EXPORT_SYMBOL_GPL(sb2_dbg_add_default_handlers);

void sb2_dbg_enable_default_handlers(void)
{
	sb2_default_handler_enable = 1;
}
EXPORT_SYMBOL_GPL(sb2_dbg_remove_default_handlers);

int sb2_dbg_ready(void)
{
	return sb2_data != NULL;
}
EXPORT_SYMBOL_GPL(sb2_dbg_ready);

int sb2_dbg_disable_mem_monitor(int i)
{
	if (!sb2_dbg_ready())
		return -ENODEV;

	sb2_write(sb2_data, SB2_DBG_CTRL_REG0 + i * 4,
		CLR_DBG_ACPU_CHK_EN | CLR_DBG_SCPU_CHK_EN | CLR_DBG_EN);
	return 0;
}
EXPORT_SYMBOL(sb2_dbg_disable_mem_monitor);

static int sb2_dbg_set_mem_monitor(int i, u32 start, u32 end, u32 flags)
{
	if (!sb2_dbg_ready())
		return -ENODEV;

	/* disable this set first */
	sb2_dbg_disable_mem_monitor(i);

	sb2_info("%s: dbg%d addr %08x-%08x flag %08x\n", __func__,
		i, start, end, flags);
	sb2_write(sb2_data, SB2_DBG_START_REG0 + i * 4, start);
	sb2_write(sb2_data, SB2_DBG_END_REG0 + i * 4, end);
	sb2_write(sb2_data, SB2_DBG_CTRL_REG0 + i * 4,  flags);
	return 0;
}

/*
 * which: 0~7, which register set
 * d_i: SB2_DBG_MONITOR_DATA|SB2_DBG_MONITOR_INST
 * r_w: SB2_DBG_MONITOR_READ|SB2_DBG_MONITOR_WRITE
 */
int sb2_dbg_scpu_monitor(int which, u32 start, u32 end, u32 d_i, u32 r_w)
{
	return sb2_dbg_set_mem_monitor(which, start, end,
		CLR_DBG_ACPU_CHK_EN | SET_DBG_SCPU_CHK_EN | SET_DBG_EN |
		d_i | r_w);
}
EXPORT_SYMBOL(sb2_dbg_scpu_monitor);

int sb2_dbg_acpu_monitor(int which, u32 start, u32 end, u32 d_i, u32 r_w)
{
	return sb2_dbg_set_mem_monitor(which, start, end,
		SET_DBG_ACPU_CHK_EN | CLR_DBG_SCPU_CHK_EN | SET_DBG_EN |
		d_i | r_w);
}
EXPORT_SYMBOL(sb2_dbg_acpu_monitor);

static irqreturn_t sb2_dbg_int_handler(int irq, void *id)
{
	struct platform_device *pdev = id;
	struct sb2_data *data = platform_get_drvdata(pdev);
	u32 val;
	u32 intr;
	ktime_t cur = ktime_get();

	intr = sb2_read(data, SB2_DBG_INT);
	if (intr & (SB2_SCPU_NEG_INT | SB2_SCPU_INT | SB2_ACPU_NEG_INT | SB2_ACPU_INT)) {
		struct sb2_dbg_event_data d;

		/* clear ints */
		sb2_write(data, SB2_DBG_INT, SB2_SCPU_INT_EN | SB2_ACPU_INT_EN | WRITE_DATA_1);

		d.raw_ints = intr;
		d.cur_time = cur;
		val = sb2_read(data, SB2_DBG_ADDR1);
		if (intr & SB2_SCPU_INT) {
			d.cpu = SB2_DBG_SOURCE_SCPU;
			d.addr = sb2_read(data, SB2_DBG_ADDR_SYSTEM);
			val >>= 2;
		} else if (intr & SB2_ACPU_INT) {
			d.cpu = SB2_DBG_SOURCE_ACPU;
			d.addr = sb2_read(data, SB2_DBG_ADDR_AUDIO);
			val >>= 4;
		} else if (intr & SB2_PCPU_INT) {
			d.cpu = SB2_DBG_SOURCE_PCPU;
			d.addr = sb2_read(data, SB2_DBG_ADDR_PCPU);
			val >>= 6;
		}
		d.rw = (val & 0x2) ? SB2_DBG_ACCESS_WRITE : SB2_DBG_ACCESS_READ;
		d.di = (val & 0x1) ? SB2_DBG_ACCESS_DATA : SB2_DBG_ACCESS_INSTRUCTION;
		__notify_dbg_int(&d);

		return IRQ_HANDLED;
	}

	intr = sb2_read(data, SB2_INV_INTSTAT);
	if (intr & (SWCIVA_INT | ACIVA_INT | SCIVA_INT | PCIVA_INT)) {
		struct sb2_inv_event_data d;

		/* clear ints */
		sb2_write(data, SB2_INV_INTSTAT, SWCIVA_INT | ACIVA_INT | SCIVA_INT | PCIVA_INT | WRITE_DATA_0);

		d.raw_ints   = intr;
		d.cur_time   = cur;
		d.addr       = sb2_read(data, SB2_INV_ADDR);
		d.timeout_th = sb2_read(data, SB2_DEBUG_REG);
		if (intr & SWCIVA_INT)
			d.inv_cpu = SB2_INV_SCPU_SWC;
		else if (intr & ACIVA_INT)
			d.inv_cpu = SB2_INV_ACPU;
		else if (intr & SCIVA_INT)
			d.inv_cpu = SB2_INV_SCPU;
		else if (intr & PCIVA_INT)
			d.inv_cpu = SB2_INV_PCPU;
		__notify_inv_int(&d);

		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}

static void sb2_set_l4_icg(struct sb2_data *data)
{
	if (IS_ENABLED(CONFIG_ARCH_RTD139x)) {
		sb2_write(data, SB2_RBUS_ICG1, 0xffffffff);
		sb2_write(data, SB2_RBUS_ICG2, 0x000fe7ff);
		sb2_write(data, SB2_RBUS_ICG3, 0x03ff003f);
	} else if (IS_ENABLED(CONFIG_ARCH_RTD16xx)) {
		sb2_write(data, SB2_RBUS_ICG1, 0xffffffff);
		sb2_write(data, SB2_RBUS_ICG2, 0xffffffff);
		sb2_write(data, SB2_RBUS_ICG3, 0xf73f007f);
	}
}

static void sb2_enable_interrupt(struct sb2_data *data)
{
	/* Enable SB2 interrupt */
	sb2_write(data, SB2_DBG_INT, SB2_ACPU_INT_EN | SB2_SCPU_INT_EN | SB2_PCPU_INT_EN | WRITE_DATA_1);
	sb2_write(data, SB2_INV_INTSTAT, SWCIVA_INT | ACIVA_INT | SCIVA_INT | PCIVA_INT | WRITE_DATA_0);
	sb2_write(data, SB2_INV_INTEN, SWCIVAIRQ_EN | ACIVAIRQ_EN | SCIVAIRQ_EN | PCIVAIRQ_EN | WRITE_DATA_1 | sb2_read(data, SB2_INV_INTEN));
}

static void sb2_disable_interrupt(struct sb2_data *data)
{
	sb2_write(data, SB2_DBG_INT, 0);
}

static int sb2_dbg_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct sb2_data *data;
	struct device_node *np = dev->of_node;
	int ret;

	sb2_info("%s\n", __func__);

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->irq = irq_of_parse_and_map(np, 0);
	if (!data->irq) {
		sb2_err("failed to parse irq\n");
		return -ENXIO;
	}

	ret = devm_request_irq(dev, data->irq, sb2_dbg_int_handler, IRQF_SHARED, "sb2_dbg", pdev);
	if (ret) {
		sb2_err("request_irq() returns %d\n", ret);
		return -ENXIO;
	}

	ret = of_sb2_data_init(np, data, 0);
	if (ret) {
		sb2_err("of_sb2_data_init() returns %d\n", ret);
		return ret;
	}
	sb2_data = data;

	sb2_info("info 0x%x\n", sb2_read(data, SB2_CHIP_INFO));
	sb2_info("use smc %x\n", SB2_USE_SMCCALL);

	sb2_dbg_register_dbg_notifier(&sb2_dbg_default_dbg_nb);
	sb2_dbg_register_inv_notifier(&sb2_dbg_default_inv_nb);
	debugfs_create_u32("sb2_default_handlers_enable", 0644, NULL,
			   &sb2_default_handler_enable);

	platform_set_drvdata(pdev, data);
	sb2_set_l4_icg(data);
	sb2_enable_interrupt(data);
	return 0;
}

static int sb2_dbg_remove(struct platform_device *pdev)
{
	struct sb2_data *data = platform_get_drvdata(pdev);

	sb2_info("%s\n", __func__);
	sb2_disable_interrupt(data);
	sb2_data_fini(data);
	sb2_data = NULL;
	return 0;
}

static int sb2_dbg_suspend(struct device *dev)
{
	struct sb2_data *data = dev_get_drvdata(dev);

	sb2_info("Enter %s\n", __func__);
	sb2_disable_interrupt(data);
	sb2_info("Exit %s\n", __func__);
	return 0;
}

static int sb2_dbg_resume(struct device *dev)
{
	struct sb2_data *data = dev_get_drvdata(dev);

	sb2_info("Enter %s\n", __func__);
	sb2_enable_interrupt(data);
	sb2_info("Exit %s\n", __func__);
	return 0;
}

static struct dev_pm_ops sb2_pm_ops = {
	.suspend_noirq = sb2_dbg_suspend,
	.resume_noirq  = sb2_dbg_resume,
};

static const struct of_device_id rtk_sb2_match[] = {
	{.compatible = "Realtek,rtk-sb2"},
	{.compatible = "realtek,sysbrg2"},
	{},
};

static struct platform_driver rtk_sb2_driver = {
	.probe  = sb2_dbg_probe,
	.remove = sb2_dbg_remove,
	.driver = {
		.owner          = THIS_MODULE,
		.name           = DRIVER_NAME,
		.pm             = &sb2_pm_ops,
		.of_match_table = of_match_ptr(rtk_sb2_match),
	},
};

static void __exit rtk_sb2_exit(void)
{
	platform_driver_unregister(&rtk_sb2_driver);
}
module_exit(rtk_sb2_exit);

static int __init rtk_sb2_init(void)
{
	return platform_driver_register(&rtk_sb2_driver);
}
arch_initcall(rtk_sb2_init);

MODULE_DESCRIPTION("Realtek SB2 driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtk-sb2");

#if 0
static int sb2_dbg_acpu_monitor_callback(struct notifier_block *nb, unsigned long action, void *data)
{
	struct sb2_dbg_event_data *d = data;
	struct pt_regs *regs;
	char buf[200];

	regs = get_irq_regs();
	sprintf(buf, "Memory 0x%08x trashed by %sCPU with %s %s\n", d->addr,
		(d->cpu == SB2_DBG_SOURCE_SCPU) ? "S" : "A",
		(d->di == SB2_DBG_ACCESS_DATA) ? "D" : "I",
		(d->rw == SB2_DBG_ACCESS_WRITE) ? "W" : "R");
	die(buf, regs, 0);
	return NOTIFY_OK;
}

struct notifier_block sb2_dbg_acpu_monitor_nb = {
	.notifier_call = sb2_dbg_acpu_monitor_callback,
};

static int __init sb2_dbg_init_acpu_monitor(void)
{
	sb2_info("memory monitor 0x98013b00 - 0x98013c00\n");
	sb2_dbg_acpu_monitor(4, 0x98013b00, 0x98013c00,
		SB2_DBG_MONITOR_DATA | SB2_DBG_MONITOR_INST,
		SB2_DBG_MONITOR_READ | SB2_DBG_MONITOR_WRITE);
	sb2_dbg_register_dbg_notifier(&sb2_dbg_acpu_monitor_nb);
	return 0;
}
late_initcall(sb2_dbg_init_acpu_monitor);
#endif
