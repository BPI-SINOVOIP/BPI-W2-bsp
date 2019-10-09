/*
 * rtd139x_restart.c - restart function
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/delay.h>
#include <linux/io.h>

#include <asm/system_misc.h>

static void __iomem * wdt_base;
static int wdt_oe;
static void __iomem * rst_ctrl_base;
unsigned int rst_ctrl_reg_offset = 0;

#define WDT_CLR 4
#define WDT_CTL 0
#define WDT_OVERFLOW 0xC
#define WDT_NMI 8
#define WDT_RSTB_CNT 0x40
#define WDT_OE 0x44 //0x980076C4

#define RESET_MAGIC 0xAABBCC00

typedef enum{
	RESET_ACTION_NO_ACTION = 0,
	RESET_ACTION_FASTBOOT,
	RESET_ACTION_RECOVERY,
	RESET_ACTION_GOLDEN,
	RESET_ACTION_ABNORMAL = 0xff,
}RESET_ACTION;

static void setup_restart_action(RESET_ACTION action)
{
	unsigned int reset_action = RESET_MAGIC;

	if (!rst_ctrl_base) {
		pr_err("%s, Skip set reset action\n", __func__);
		return;
	}

	reset_action |= action;
	writel(reset_action, rst_ctrl_base + rst_ctrl_reg_offset);
}

void rtk_machine_restart(char mode, const char *cmd)
{
	if (cmd) {
		if (!strncmp("bootloader", cmd, 11)) {
			setup_restart_action(RESET_ACTION_FASTBOOT);
		} else if (!strncmp("recovery", cmd, 9)) {
			setup_restart_action(RESET_ACTION_RECOVERY);
		} else {
			setup_restart_action(RESET_ACTION_NO_ACTION);
		}
	} else {
		setup_restart_action(RESET_ACTION_NO_ACTION);
	}

	if (wdt_oe >= 0)
		writel(wdt_oe, wdt_base + WDT_OE);

	writel(0x00800000, wdt_base + WDT_RSTB_CNT);
	writel(BIT(0), wdt_base + WDT_CLR);
	writel(0x00800000, wdt_base + WDT_OVERFLOW);
	writel(0x000000FF, wdt_base + WDT_CTL);

	while (1)
		mdelay(100);
}

static struct of_device_id rtk_restart_ids[] = {
	{.compatible = "realtek,rtk-watchdog", .data = rtk_machine_restart},
	{}
};

static struct of_device_id rtk_reset_control_ids[] = {
	{.compatible = "Realtek,rtk-rstctrl"},
	{}
};

static int rtk_setup_restart(void)
{
	const struct of_device_id *of_id;
	struct device_node *np;

#ifdef CONFIG_RTK_XEN_SUPPORT
	if (xen_domain() && !xen_initial_domain()) {
		pr_info("%s: skip under DomU\n", __func__);
		return 0;
	}
#endif
	/* setup Watchdog */
	np = of_find_matching_node(NULL, rtk_restart_ids);
	if (WARN(!np, "Unable to setup watchdog restart"))
		return 1;

	wdt_base = of_iomap(np, 0);
	WARN(!wdt_base, "failed to map IO base for watchdog");

	if (of_property_read_u32_index(np, "rst-oe", 0, &wdt_oe))
		wdt_oe = -1;

	of_id = of_match_node(rtk_restart_ids, np);
	WARN(!of_id, "restart not available");

	arm_pm_restart = of_id->data;

	/* setup Reset Control */
	np = of_find_matching_node(NULL, rtk_reset_control_ids);
	if (WARN(!np, "Unable to setup reset-control"))
		return 1;

	rst_ctrl_base = of_iomap(np, 0);
	WARN(!rst_ctrl_base, "failed to map IO base for reset-control");

	if (of_property_read_u32_index(np, "rst-reg-offset", 0, &rst_ctrl_reg_offset)) {
		pr_err("reset-control rst-reg-offset not defined");
		rst_ctrl_base = NULL;
		return 1;
	}

	printk("rst-control : base %p, offset 0x%x\n", rst_ctrl_base, rst_ctrl_reg_offset);
	setup_restart_action(RESET_ACTION_ABNORMAL);

	return 0;
}

arch_initcall(rtk_setup_restart);

#if defined(CONFIG_RTK_XEN_SUPPORT) && defined(CONFIG_RTK_RPC)
#include <xen/xen.h>
#include <xen/xen-ops.h>
#include <soc/realtek/rtk_ipc_shm.h>

void rtk_xen_acpu_notify(int state)
{
	struct rtk_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT;
	unsigned int reg = __be32_to_cpu(readl(&ipc->xen_domu_boot_st));
	int ret = -1, max_loop = 10;
	if ((XEN_DOMU_BOOT_ST_MAGIC_KEY_MASK & reg) != XEN_DOMU_BOOT_ST_MAGIC_KEY_MASK) {
		pr_err("[%s] Magic ERR!\n", __func__);
		goto err;
	}

	reg = 0;
	reg |= XEN_DOMU_BOOT_ST_MAGIC_KEY_MASK;
	reg |= XEN_DOMU_BOOT_ST_VERSION_SET(XEN_DOMU_BOOT_ST_VERSION);
	reg |= XEN_DOMU_BOOT_ST_AUTHOR_SET(XEN_DOMU_BOOT_ST_AUTHOR_SCPU);
	reg |= XEN_DOMU_BOOT_ST_STATE_SET(state);
	writel(__cpu_to_be32(reg), &ipc->xen_domu_boot_st);

	do {
		reg = __be32_to_cpu(readl(&ipc->xen_domu_boot_st));
		if (XEN_DOMU_BOOT_ST_AUTHOR_GET(reg) == XEN_DOMU_BOOT_ST_AUTHOR_ACPU &&
		    XEN_DOMU_BOOT_ST_STATE_GET(reg) == XEN_DOMU_BOOT_ST_STATE_ACPU_ENTER_IDLE)
			break;

		if (max_loop-- <= 0) {
			pr_err("[%s] Timeout waiting ACPU respond!\n", __func__);
			goto err;
		}

		 mdelay(100);
	} while(1);

	reg = 0;
	reg |= XEN_DOMU_BOOT_ST_MAGIC_KEY_MASK;
	reg |= XEN_DOMU_BOOT_ST_VERSION_SET(XEN_DOMU_BOOT_ST_VERSION);
	reg |= XEN_DOMU_BOOT_ST_AUTHOR_SET(XEN_DOMU_BOOT_ST_AUTHOR_SCPU);
	reg |= XEN_DOMU_BOOT_ST_STATE_SET(XEN_DOMU_BOOT_ST_STATE_SCPU_WAIT_DONE);
	writel(__cpu_to_be32(reg), &ipc->xen_domu_boot_st);

	ret = 0;
err:
	if (ret)
		printk("[%s] Error! xen_domu_boot_st=0x%08x\n", __func__, reg);
	return;
}

void rtk_xen_restart_notify(void)
{
	rtk_xen_acpu_notify(XEN_DOMU_BOOT_ST_STATE_SCPU_RESTART);
}

void rtk_xen_power_off_notify(void)
{
	rtk_xen_acpu_notify(XEN_DOMU_BOOT_ST_STATE_SCPU_POWOFF);
}

static int rtk_xen_setup_restart(void)
{
	struct rtk_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT;
	unsigned int reg = 0;

	if (xen_initial_domain())
		return 0;

	reg |= XEN_DOMU_BOOT_ST_MAGIC_KEY_MASK;
	reg |= XEN_DOMU_BOOT_ST_VERSION_SET(XEN_DOMU_BOOT_ST_VERSION);
	reg |= XEN_DOMU_BOOT_ST_AUTHOR_SET(XEN_DOMU_BOOT_ST_AUTHOR_SCPU);
	reg |= XEN_DOMU_BOOT_ST_STATE_SET(XEN_DOMU_BOOT_ST_STATE_SCPU_BOOT);
	writel(__cpu_to_be32(reg), &ipc->xen_domu_boot_st);

	xen_pre_restart = rtk_xen_restart_notify;
	xen_pre_power_off = rtk_xen_power_off_notify;
	return 0;
}

late_initcall(rtk_xen_setup_restart);
#endif /* End of CONFIG_RTK_XEN_SUPPORT && CONFIG_RTK_RPC */
