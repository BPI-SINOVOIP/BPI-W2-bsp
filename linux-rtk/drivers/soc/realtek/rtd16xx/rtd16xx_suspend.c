/*
 * rtd16xx_suspend.c - power management driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#include <linux/pm.h>
#include <linux/suspend.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/cpu.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/reboot.h>
#include <linux/clocksource.h>
#include <linux/clockchips.h>
#include <linux/cpu_pm.h>
#include <linux/vmalloc.h>
#include <linux/tick.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/irqchip/arm-gic.h>
#include <linux/psci.h>
#include <asm/system_misc.h>
#include <asm/cacheflush.h>
#include <asm/suspend.h>
#include <soc/realtek/memory.h>
#include <soc/realtek/rtk_cpu.h>
#include <uapi/linux/psci.h>

#include "rtd16xx_suspend.h"

#define DEV "RTD16xx_PM"
#define SUSPEND_VERSION_MASK(v) ((v&0xffff) << 16)
#define RTK_PM_DEBUG 1
#define RTK_DDR_CALIBRATION 0

static int suspend_version = 2;
extern unsigned int suspend_context;

void __iomem *RTK_CRT_BASE;
void __iomem *RTK_ISO_BASE;
void __iomem *RTK_SB2_BASE;

extern void rtk_ddr_calibration_save(void); /* save ddr rx calibration */
extern void rtk_ddr_calibration_restore(void); /* restore ddr rx calibration */
extern void psci_sys_reset(enum reboot_mode reboot_mode, const char *cmd);
extern void psci_sys_poweroff(void);
extern int psci_system_suspend(unsigned long wakeup_source);
extern void memory_check_begin(void);
extern void memory_check_end(void);
extern void hexdump(char *note, unsigned char *buf, unsigned int len);

struct suspend_param *pcpu_data;

extern char wu_en[SUSPEND_ISO_GPIO_SIZE];
extern char wu_act[SUSPEND_ISO_GPIO_SIZE];

static void rtk_acpu_set_flag(uint32_t flag)
{
	struct rtk_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT;

	writel(__cpu_to_be32(SUSPEND_VERSION_MASK(suspend_version)),
		&(ipc->suspend_mask));

	if (suspend_version == 1)
		writel(__cpu_to_be32(flag), &(ipc->suspend_flag));
	else
		writel(__cpu_to_be32(flag | AUTHOR_MASK(AUTHOR_SCPU)),
			&(ipc->suspend_flag));
}

static void rtk_notify_acpu(enum _notify_flag flag)
{
	pr_info("[%s] Notify ACPU, flag= %d\n", DEV, flag);

	switch (flag) {
	case NOTIFY_SUSPEND_TO_RAM:
	case NOTIFY_SUSPEND_TO_COOLBOOT:
	case NOTIFY_SUSPEND_TO_WFI:
		if (suspend_version == 1) {
			rtk_acpu_set_flag(0x000018ff);
			return;
		}
		break;
	case NOTIFY_RESUME_PLATFORM:
		if (suspend_version == 1) {
			rtk_acpu_set_flag(0x00000000);
			return;
		}
		break;
	default:
		if (suspend_version == 1)
			return;
		break;
	}

	rtk_acpu_set_flag(NOTIFY_MASK(flag));
}

static int rtk_suspend_wakeup_acpu(void)
{
	pr_info("[%s] Wakeup ACPU\n", DEV);

	writel(0x00000000, RTK_SB2_BASE + 0x138);
	__delay(1000);
	writel(0x00000008, RTK_CRT_BASE + 0x328);
	writel(0x0000ace7, RTK_CRT_BASE + 0x320);
	writel(0x0000000c, RTK_CRT_BASE + 0x328);
	__delay(1000);

	return 0;
}

static void rtk_sys_reset(enum reboot_mode reboot_mode, const char *cmd)
{
	pr_info("[%s] Power reset\n", DEV);

	rtk_notify_acpu(NOTIFY_SUSPEND_TO_COOLBOOT);

	psci_sys_reset(reboot_mode, cmd);
};

static void rtk_power_off(void)
{
	pr_info("[%s] Power off\n", DEV);

	rtk_notify_acpu(NOTIFY_SUSPEND_TO_COOLBOOT);

	psci_sys_poweroff();
};

static int rtk_suspend_standby(unsigned long unused)
{
	/*
	 * Todo:
	 * define PSCI command: S1 mode
	 */
	return 0;
}

static int rtk_suspend_mem(unsigned long pcpu_data)
{
#if RTK_PM_DEBUG
	pr_info("[%s] CPU Resume vaddr: 0x%08lx paddr: 0x%08lx\n",
		DEV, (unsigned long)cpu_resume,
		(unsigned long)__pa(cpu_resume));

	hexdump("CPU Resume Entry Dump:",
		(unsigned char *) cpu_resume, 0x100);
#endif /* RTK_PM_DEBUG */

	return psci_system_suspend(pcpu_data);
}

static int rtk_suspend_enter(suspend_state_t state)
{
	int ret = 0;

	switch (state) {
	case PM_SUSPEND_STANDBY:
		rtk_notify_acpu(NOTIFY_SUSPEND_TO_WFI);
		cpu_suspend(0, rtk_suspend_standby);
		break;
	case PM_SUSPEND_MEM:
		rtk_notify_acpu(NOTIFY_SUSPEND_TO_RAM);
		cpu_suspend(__pa(pcpu_data), rtk_suspend_mem);
		break;
	default:
		ret = -EINVAL;
		break;
	}

#if RTK_PM_DEBUG
	memory_check_end();
#endif /* RTK_PM_DEBUG */

#if RTK_DDR_CALIBRATION
	rtk_ddr_calibration_restore();
#endif /* RTK_DDR_CALIBRATION */

	writel(readl(RTK_ISO_BASE + 0x0418) | BIT(0), RTK_ISO_BASE + 0x0418);
	writel(readl(RTK_ISO_BASE + 0x0410) & ~BIT(10), RTK_ISO_BASE + 0x0410);

	return ret;
}

static int rtk_suspend_valid(suspend_state_t state)
{
	return state == PM_SUSPEND_MEM || state == PM_SUSPEND_STANDBY;
}

static int rtk_suspend_begin(suspend_state_t suspend_state)
{
	int ret = 0;
	int i = 0;

	pr_info("[%s] Suspend Begin\n", DEV);

	for(i = 0 ; i < SUSPEND_ISO_GPIO_SIZE ; i++){
		pcpu_data->wu_gpio_en[i] = wu_en[i];
		pcpu_data->wu_gpio_act[i] = wu_act[i];
	}

#if RTK_PM_DEBUG
	memory_check_begin();
#endif /* RTK_PM_DEBUG */

#if RTK_DDR_CALIBRATION
	rtk_ddr_calibration_save();
#endif /* RTK_DDR_CALIBRATION */

	cpu_idle_poll_ctrl(true);

	return ret;
}

static void rtk_suspend_wake(void)
{
	pr_info("[%s] Platform Wake\n", DEV);

	rtk_suspend_wakeup_acpu();

	suspend_context++;

	rtk_notify_acpu(NOTIFY_RESUME_PLATFORM);
}

static void rtk_suspend_end(void)
{
	pr_info("[%s] Suspend End\n", DEV);

	rtk_notify_acpu(NOTIFY_RESUME_END);

	cpu_idle_poll_ctrl(false);
}

const struct platform_suspend_ops rtk_suspend_ops = {
	.begin = rtk_suspend_begin,
	.end = rtk_suspend_end,
	.enter = rtk_suspend_enter,
	.valid = rtk_suspend_valid,
	.wake = rtk_suspend_wake,
};

int __init rtk_suspend_init(void)
{
	struct device_node *pm_nd = NULL;
	const u32 *prop;
	int size;
	int temp;

	pr_info("[%s] Initial Power Management\n", DEV);

	pcpu_data = kmalloc(sizeof(struct suspend_param), GFP_KERNEL);

	pm_nd = of_find_compatible_node(NULL, NULL, "realtek,pm");

	RTK_CRT_BASE = of_iomap(pm_nd, 0);
	RTK_ISO_BASE = of_iomap(pm_nd, 1);
	RTK_SB2_BASE = of_iomap(pm_nd, 2);

	if (pm_nd && of_device_is_available(pm_nd)) {
		/* Wakeup Flags */
		prop = of_get_property(pm_nd, "wakeup-flags", &size);
		temp = of_read_number(prop, 1);
		if (temp < 0) {
			pr_err("[%s] wakeup flags set default value!\n", DEV);
			pcpu_data->wakeup_source = fWAKEUP_ON_IR |
					fWAKEUP_ON_GPIO | fWAKEUP_ON_ALARM |
					fWAKEUP_ON_CEC;
		} else
			pcpu_data->wakeup_source = temp;

		pr_info("[%s] wakeup flags = 0x%x\n", DEV,
			pcpu_data->wakeup_source);
	}

	rtk_acpu_set_flag(0x00000000);
	suspend_set_ops(&rtk_suspend_ops);
	pm_power_off = rtk_power_off;
	arm_pm_restart = rtk_sys_reset;

	return 0;
}

subsys_initcall(rtk_suspend_init);
