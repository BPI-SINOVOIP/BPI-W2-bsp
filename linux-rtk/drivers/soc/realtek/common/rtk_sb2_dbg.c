/*
 * rtk_sb2_dbg.c - bus debug driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
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
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <asm/system_misc.h>

#include "include/reg_sb2.h"

#define DRIVER_NAME "RTK_SB2_DBG"

static void __iomem *iobase;

#ifdef CONFIG_OPTEE
static void swc_write(u32 value, u32 address)
{
	asm volatile("mov x1, %0" : :"r"(address): "cc");
	asm volatile("mov x2, %0" : :"r"(value) : "cc");
	asm volatile("ldr x0, =0x8400ff07" : : : "cc");
	asm volatile("isb" : : : "cc");
	asm volatile("smc #0" : : : "cc");
	asm volatile("isb" : : : "cc");
	udelay(5);
}

static u32 swc_read(u32 address)
{
	u32 tmp;

	asm volatile("mov x1, %0" : :"r"(address): "cc");
	asm volatile("ldr x0, =0x8400ff06" : : : "cc");
	asm volatile("isb" : : : "cc");
	asm volatile("smc #0" : : : "cc");
	asm volatile("isb" : : : "cc");
	asm volatile("mov %0, x0" : "=r"(tmp): : "cc");
	udelay(5);
	return tmp;
}
#endif /* TEE*/

irqreturn_t isr_sb2_dbg(int irq, void *pdev)
{
	struct pt_regs *regs;
	u32 intr;

#ifdef CONFIG_OPTEE
	intr = swc_read(0x9801A000 | 0x4E0);
#else
	intr = readl(SB2_DBG_INT);
#endif

	regs = get_irq_regs();

	if (intr & ((1 << 4) | (1 << 10) | (1 << 6) | (1 << 12))) {
		u32 cause, addr, s_a_cpu;
		char buf[128];

		pr_err("[%s] sb2 get int 0x%08x from SB2_DBG_INT\n", DRIVER_NAME, intr);

#ifdef CONFIG_OPTEE
		swc_write((1 << 9) | (1 << 7) | 1, 0x9801A4E0);
#else
		writel((1 << 9) | (1 << 7) | 1, SB2_DBG_INT);
#endif

		s_a_cpu = (intr & (1<<10)) ? 1 : 2;	/* SCPU:1, ACPU:2 */

#ifdef CONFIG_OPTEE
		addr = (s_a_cpu == 1) ?
			swc_read(0x9801A000 | 0x4C0) :
			swc_read(0x9801A000 | 0x4B8);
#else
		addr = (s_a_cpu == 1) ? readl(SB2_DBG_ADDR_SYSTEM) :
			readl(SB2_DBG_ADDR_AUDIO);
#endif

#ifdef CONFIG_OPTEE
		cause = swc_read(0x9801A000 | 0x4C8);
#else
		cause = readl(SB2_DBG_ADDR1);
#endif
		cause = (s_a_cpu == 1) ? (cause >> 2) : (cause >> 4);

		sprintf(buf, "Memory 0x%08x trashed by %sCPU with %s %s\n", addr,
				(s_a_cpu == 1) ? "S" : "A",
				(cause & 1) ? "D" : "I", 
				(cause & 2) ? "W" : "R");

		die(buf, regs, 0);

		return IRQ_HANDLED;
	}

#ifdef CONFIG_OPTEE
	intr = swc_read(0x9801A000 | 0x008);
#else
	intr = readl(SB2_INV_INTSTAT);
#endif

	if (intr & (SWCIVA_INT | ACIVA_INT | SCIVA_INT)) {

		pr_err("[%s] sb2 get int 0x%08x from SB2_INV_INTSTAT\n", DRIVER_NAME, intr);

#ifdef CONFIG_OPTEE
		swc_write(SWCIVA_INT | ACIVA_INT | SCIVA_INT | WRITE_DATA_0, 0x9801A000 | 0x008);
#else
		writel( SWCIVA_INT | ACIVA_INT | SCIVA_INT | WRITE_DATA_0, SB2_INV_INTSTAT);
#endif

		if (intr & SWCIVA_INT)
			pr_err("\033[0;31m[%s] Invalid access issued by SCPU security world\033[m\n", DRIVER_NAME) ;

		if (intr & ACIVA_INT)
			pr_err("\033[0;31m[%s] Invalid access issued by Audio\033[m\n", DRIVER_NAME) ;

		if (intr & SCIVA_INT)
			pr_err("\033[0;31m[%s] Invalid access issued by SCPU\033[m\n", DRIVER_NAME) ;
#ifdef CONFIG_OPTEE
		pr_err("\033[0;31m[%s] Invalid address is 0x%x \033[m\n", DRIVER_NAME, swc_read(0x9801A000 | 0x00c));
		pr_err("[%s] Timeout threshold(0x%08x)\n", DRIVER_NAME, swc_read(0x9801A000 | 0x010));
#else
		pr_err("\033[0;31m[%s] Invalid address is 0x%x \033[m\n", DRIVER_NAME, readl(SB2_INV_ADDR));
		pr_err("[%s] Timeout threshold(0x%08x)\n", DRIVER_NAME, readl(SB2_DEBUG_REG));
		//show_regs(regs);
#endif

		return IRQ_HANDLED;

	}
	return IRQ_NONE;
}

void sb2_dbg_scpu_monitor(int which, u32 start, u32 end, u32 d_i, u32 r_w);
void sb2_dbg_acpu_monitor(int which, u32 start, u32 end, u32 d_i, u32 r_w);

static int set_l4_icg(void *base)
{
#ifdef CONFIG_OPTEE
	if (IS_ENABLED(CONFIG_ARCH_RTD139x)) {
		swc_write(0xffffffff, 0x9801A000 | 0x308);
		swc_write(0x000fe7ff, 0x9801A000 | 0x30C);
		swc_write(0x03ff003f, 0x9801A000 | 0x310);
	}
#else
	if (IS_ENABLED(CONFIG_ARCH_RTD139x)) {
		writel(0xffffffff, base + 0x308);
		writel(0x000fe7ff, base + 0x30C);
		writel(0x03ff003f, base + 0x310);
	}
#endif

	return 0;
}

static int sb2_dbg_init(struct platform_device *pdev)
{
	struct device_node *np;
	int sb2_irq;

	if (WARN_ON(!(pdev->dev.of_node))){
		pr_err("[%s] Error: No node\n", DRIVER_NAME);
		return -ENODEV;
	}

	np = pdev->dev.of_node;

	iobase = of_iomap(np, 0);

	sb2_irq = irq_of_parse_and_map(np, 0);

	set_l4_icg(iobase);

	if (!sb2_irq) {
		pr_err("[%s] irq parse fail\n", DRIVER_NAME);
		return -ENXIO;
	}

	if (request_irq(sb2_irq, isr_sb2_dbg, IRQF_SHARED, "sb2_dbg", pdev) != 0){
		pr_err("[%s] irq request fail\n", DRIVER_NAME);
		return -ENXIO;
	}

#ifdef CONFIG_OPTEE
	pr_info("[%s] Info 0x%x\n", DRIVER_NAME, swc_read(0x9801A000 | 0x204));
#else
	pr_info("[%s] Info 0x%x\n", DRIVER_NAME, readl(iobase + 0x204));
#endif

	pr_info("[%s] memory monitor 0x98013b00 - 0x98013c00\n", DRIVER_NAME);
	sb2_dbg_acpu_monitor(4, 0x98013b00, 0x98013c00, SB2_DBG_MONITOR_DATA|SB2_DBG_MONITOR_INST, SB2_DBG_MONITOR_READ|SB2_DBG_MONITOR_WRITE);

#ifdef CONFIG_OPTEE
	/* Enable SB2 interrupt */
	swc_write(SB2_ACPU_INT_EN | SB2_SCPU_INT_EN | WRITE_DATA_1, 0x9801A000 | 0x4E0);
	swc_write(SWCIVA_INT | ACIVA_INT | SCIVA_INT | WRITE_DATA_0 , 0x9801A000 | 0x008);
	swc_write(SWCIVAIRQ_EN | ACIVAIRQ_EN | SCIVAIRQ_EN | WRITE_DATA_1 | swc_read(0x9801A000 | 0x004), 0x9801A000 | 0x004);
#else
	/* Enable SB2 interrupt */
	writel(SB2_ACPU_INT_EN | SB2_SCPU_INT_EN | WRITE_DATA_1, SB2_DBG_INT);
	writel(SWCIVA_INT | ACIVA_INT | SCIVA_INT | WRITE_DATA_0 , SB2_INV_INTSTAT);
	writel(SWCIVAIRQ_EN | ACIVAIRQ_EN | SCIVAIRQ_EN | WRITE_DATA_1 | readl(SB2_INV_INTEN), SB2_INV_INTEN);
#endif
	pr_info("[%s] initialized\n", DRIVER_NAME);

	return 0;
}

static int sb2_dbg_exit(struct platform_device *pdev)
{
	struct device_node *np;
	int sb2_irq;

	pr_info("[%s] Exit\n", DRIVER_NAME);

	np = pdev->dev.of_node;
	sb2_irq = irq_of_parse_and_map(np, 0);

#ifdef CONFIG_OPTEE
	swc_write(0x0 , 0x9801A000 | 0x4E0);
#else
	/* Disable  SB2 interrupt */
	writel(0x0 , SB2_DBG_INT);
#endif

	free_irq(sb2_irq, NULL);

	return 0;
}

int sb2_dbg_suspend(struct device *dev)
{
	pr_info("[%s] Enter\n", DRIVER_NAME);

#ifdef CONFIG_OPTEE
	swc_write(0x0 , 0x9801A000 | 0x4E0);
#else
	/* Disable  SB2 interrupt */
	writel(0x0 , SB2_DBG_INT);
#endif

	pr_info("[%s] Exit\n", DRIVER_NAME);

	return 0;
}

int sb2_dbg_resume(struct device *dev)
{
	pr_info("[%s] Resume enter\n", DRIVER_NAME);

#ifdef CONFIG_OPTEE
	/* Enable SB2 interrupt */
	swc_write(SB2_ACPU_INT_EN | SB2_SCPU_INT_EN | WRITE_DATA_1, 0x9801A000 | 0x4E0);
	swc_write(SWCIVA_INT | ACIVA_INT | SCIVA_INT | WRITE_DATA_0 , 0x9801A000 | 0x008);
	swc_write(SWCIVAIRQ_EN | ACIVAIRQ_EN | SCIVAIRQ_EN | WRITE_DATA_1 | swc_read(0x9801A000 | 0x004), 0x9801A000 | 0x004);
#else
	/* Enable SB2 interrupt */
	writel(SB2_ACPU_INT_EN | SB2_SCPU_INT_EN | WRITE_DATA_1, SB2_DBG_INT);
	writel(SWCIVA_INT | ACIVA_INT | SCIVA_INT | WRITE_DATA_0 , SB2_INV_INTSTAT);
	writel(SWCIVAIRQ_EN | ACIVAIRQ_EN | SCIVAIRQ_EN | WRITE_DATA_1 | readl(SB2_INV_INTEN), SB2_INV_INTEN);
#endif
	pr_info("[%s] Resume exit\n", DRIVER_NAME);

	return 0;
}

void sb2_dbg_disable_mem_monitor(int which)
{
#ifdef CONFIG_OPTEE
	swc_write((1 << 13) | (1 << 9) | (1 << 1), 0x9801A000 | 0x498 | (which * 4));
#else
	u32 *reg_ctrl = (u32 *) SB2_DBG_CTRL_REG0;

	reg_ctrl += which;

	writel((1 << 13) | (1 << 9) | (1 << 1), reg_ctrl);
#endif
}
EXPORT_SYMBOL(sb2_dbg_disable_mem_monitor);

static void sb2_dbg_set_mem_monitor(int which, u32 start, u32 end, u32 flags)
{

#ifndef CONFIG_OPTEE
	u32 *reg_start, *reg_end, *reg_ctrl;
#endif

	/* disable this set first */
	sb2_dbg_disable_mem_monitor(which);

#ifdef CONFIG_OPTEE
	swc_write(start, 0x9801A000 | 0x458 | (which * 4));
	swc_write(end, 0x9801A000 | 0x478 | (which * 4));
	swc_write(flags, 0x9801A000 | 0x498 | (which * 4));
#else
	reg_start = ((u32 *) SB2_DBG_START_REG0) + which;
	reg_end = ((u32 *) SB2_DBG_END_REG0) + which;
	reg_ctrl = ((u32 *) SB2_DBG_CTRL_REG0) + which;

	writel(start, reg_start);
	writel(end, reg_end);
	writel(flags, reg_ctrl);
#endif
	/*
	pr_info("sb2 0x%08x=0x%08x\n", (u32)reg_ctrl, readl(reg_ctrl));
	pr_info("sb2 0x%08x=0x%08x\n", (u32)reg_start, readl(reg_start));
	pr_info("sb2 0x%08x=0x%08x\n", (u32)reg_end, readl(reg_end));
	pr_info("sb2 0x%08x=0x%08x\n", (u32)SB2_DBG_INT, readl(SB2_DBG_INT));
	*/
}

/*
 * which: 0~7, which register set
 * d_i: SB2_DBG_MONITOR_DATA|SB2_DBG_MONITOR_INST
 * r_w: SB2_DBG_MONITOR_READ|SB2_DBG_MONITOR_WRITE
 */
void sb2_dbg_scpu_monitor(int which, u32 start, u32 end, u32 d_i, u32 r_w)
{
	sb2_dbg_set_mem_monitor(which, start, end, (1 << 13) | (3 << 8) | d_i | r_w | 3);
}
EXPORT_SYMBOL(sb2_dbg_scpu_monitor);

void sb2_dbg_acpu_monitor(int which, u32 start, u32 end, u32 d_i, u32 r_w)
{
	sb2_dbg_set_mem_monitor(which, start, end, (3 << 12) | (1 << 9) | d_i | r_w | 3);
}
EXPORT_SYMBOL(sb2_dbg_acpu_monitor);

static struct dev_pm_ops sb2_pm_ops = {
	.suspend_noirq = sb2_dbg_suspend,
	.resume_noirq = sb2_dbg_resume,
};

static const struct of_device_id rtk_sb2_match[] = {
	{.compatible = "Realtek,rtk-sb2"},
	{},
};

static struct platform_driver rtk129x_sb2_driver = {
	.probe = sb2_dbg_init,
	.remove = sb2_dbg_exit,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.pm = &sb2_pm_ops,
		.of_match_table = of_match_ptr(rtk_sb2_match),
	},
};

static void __exit rtk_sb2_exit(void)
{
	platform_driver_unregister(&rtk129x_sb2_driver);
}
module_exit(rtk_sb2_exit);

static int __init rtk_sb2_init(void)
{
	return platform_driver_register(&rtk129x_sb2_driver);
}
arch_initcall(rtk_sb2_init);

MODULE_DESCRIPTION("Realtek SB2 driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtk129x-sb2");

