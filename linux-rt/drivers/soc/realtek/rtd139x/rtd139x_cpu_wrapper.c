/*
 * rtd139x_cpu_wrapper.c
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * Author: Chih-Feng Tai <james.tai@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/printk.h>
#include <linux/delay.h>
#include <linux/debugfs.h>
#include <linux/init.h>
#include <linux/smp.h>
#include <linux/types.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/memblock.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/of_irq.h>
#include <linux/delay.h>
#include <asm/io.h>
#include <asm/cacheflush.h>
#include <asm/cpu_ops.h>
#include <asm/cputype.h>
#include <asm/io.h>
#include <asm/smp_plat.h>

#include <asm/system_misc.h>

#include "../common/include/debug.h"

#define DBG_INT 0x230
#define DBG_ADDR 0x234
#define DBG_ADDR_MODE 0x238

#define CR_M (1 << 0) /* MMU enable */
#define CR_C (1 << 2) /* Dcache enable */

static void __iomem *scpu_wrap_addr;

static inline unsigned int current_el(void)
{
	unsigned int el;

	asm volatile("mrs %0, CurrentEL" : "=r" (el) : : "cc");
	return el >> 2;
}

static inline void set_sctlr(unsigned int val)
{
	unsigned int el;
	el = current_el();

	if (el == 1)
		asm volatile("msr sctlr_el1, %0" : : "r" (val) : "cc");
	else if (el == 2)
		asm volatile("msr sctlr_el2, %0" : : "r" (val) : "cc");
	else
		asm volatile("msr sctlr_el3, %0" : : "r" (val) : "cc");

	asm volatile("isb");
}

static inline unsigned int get_sctlr(void)
{
	unsigned int el, val;
	el = current_el();

	if (el == 1)
		asm volatile("mrs %0, sctlr_el1" : "=r" (val) : : "cc");
	else if (el == 2)
		asm volatile("mrs %0, sctlr_el2" : "=r" (val) : : "cc");
	else
		asm volatile("mrs %0, sctlr_el3" : "=r" (val) : : "cc");
	return val;
}

void dcache_disable(void)
{
	u32 sctlr;
	sctlr = get_sctlr();

	/* if cache isn't enabled no need to disable */
	if (!(sctlr & CR_C) && !(sctlr & CR_M))
		return;

	set_sctlr(sctlr & ~(CR_C|CR_M));
	flush_cache_all();
}

void _rtk_cpu_power_up(int cpu){

	u32 tmp = 0;

	/* 5. Wait for SMPEN to be set */

	/* 6. Assert DBGPWRDUP HIGH to allow external debug
	 * access to the core. */
	tmp = readl(scpu_wrap_addr + 0x100);
	tmp |= 1UL << (24 + cpu);
	writel(tmp, scpu_wrap_addr + 0x100);
}
EXPORT_SYMBOL(_rtk_cpu_power_up);

void rtk_cpu_power_up(int cpu)
{
	u32 tmp = 0;

	/* 1. Assert nCPUPORESET LOW. Ensure DBGPWRDUP is held LOW to prevent
	 * any external debug access to the core. */
	tmp = readl(scpu_wrap_addr + 0x100);
	tmp &= ~(1UL << (24 + cpu));
	writel(tmp, scpu_wrap_addr + 0x100);

	/* 2. Apply power to the PDCPU power domain. Keep the state of the
	 * signals nCPUPORESET and DBGPWRDUP LOW. */
	tmp = readl(scpu_wrap_addr + 0x538);
	tmp |= 1UL << (4 + cpu);
	writel(tmp, scpu_wrap_addr + 0x538);

	tmp = readl(scpu_wrap_addr + 0x538);
	tmp |= 1UL << (8 + cpu);
	writel(tmp, scpu_wrap_addr + 0x538);

	mdelay(3);

	tmp = readl(scpu_wrap_addr + 0x53C);
	if((unlikely((tmp >> (4 + cpu)) & 0x1) != 0x1)) {
		pr_err("%s: 0x9801D53C = %x\n", __func__, readl(scpu_wrap_addr + 0x53C));
	}

	/* 3. Release the core output clamps */
	tmp = readl(scpu_wrap_addr + 0x538);
	tmp &= ~(1UL << (0 + cpu));
	writel(tmp, scpu_wrap_addr + 0x538);

	/* 4. Dessert resets: nCOREPORESET, nCORERESET */
	tmp = readl(scpu_wrap_addr + 0x100);
	tmp |= 1UL << (0 + cpu);
	tmp |= 1UL << (4 + cpu);
	writel(tmp, scpu_wrap_addr + 0x100);
}
EXPORT_SYMBOL(rtk_cpu_power_up);

void rtk_cpu_power_down(int cpu)
{
	u32 tmp = 0;

	/* Step 1 to 6 is done in rtd139x_cpu_hotplug.S
	 * Wait for WFI in step 6. */
	tmp = readl(scpu_wrap_addr + 0x104);
	if (unlikely(((tmp >> cpu) & 0x1) != 0x1)) {
		pr_err("%s: Processor is not in WFI standby mode.\n", __func__);
		pr_err("0x9801D104 = %x\n", readl(scpu_wrap_addr + 0x104));
	}

	/* 7. Dessert DBGPWRDUP LOW.
	 * This prevents any external debug access to the core. */
	tmp = readl(scpu_wrap_addr + 0x100);
	tmp &= ~(1UL << (24 + cpu));
	writel(tmp, scpu_wrap_addr + 0x100);

	/* 8. Activate the core output clamps. */
	tmp = readl(scpu_wrap_addr + 0x538);
	tmp |= 1UL << (0 + cpu);
	writel(tmp, scpu_wrap_addr + 0x538);

	/* 9. Assert nCPUPORESET LOW */
	tmp = readl(scpu_wrap_addr + 0x100);
	tmp &= ~(1UL << (0 + cpu));
	tmp &= ~(1UL << (4 + cpu));
	writel(tmp, scpu_wrap_addr + 0x100);

	/* 10. Remove power from the PDCPU power domain. */
	tmp = readl(scpu_wrap_addr + 0x538);
	tmp &= ~(1UL << (4 + cpu));
	tmp &= ~(1UL << (8 + cpu));
	writel(tmp, scpu_wrap_addr + 0x538);
}
EXPORT_SYMBOL(rtk_cpu_power_down);

static int set_l4_icg(void *base)
{
	unsigned int val;

	val = readl(scpu_wrap_addr + 0x000);
	val |= 0xFF3C0000;
	writel(val, scpu_wrap_addr + 0x000);

	val = readl(scpu_wrap_addr + 0x100);
	val |= 0x8000000;
	writel(val, scpu_wrap_addr + 0x100);

	return 0;
}


irqreturn_t scpu_wrapper_isr(int irq, void *reg_base)
{
	struct pt_regs *regs;
	u32 intr = readl(scpu_wrap_addr + DBG_INT);
	u32 addr = readl(scpu_wrap_addr + DBG_ADDR);
	u32 cause = readl(scpu_wrap_addr + DBG_ADDR_MODE);
	char buf[128];

	regs = get_irq_regs();

	dbg_err("scpu wrapper get int 0x%08x", intr);
	if(intr & (BIT(4) | BIT(2))){
		writel((intr & ~(BIT(3)|BIT(1))), scpu_wrap_addr + DBG_INT);
		dbg_err("scpu addr:0x%08x mode:%s", addr, (cause & 1) ? "W" : "R");

		sprintf(buf, "[SCUP] Memory 0x%08x trashed with %s\n", addr,
				(cause & 1) ? "W" : "R");
		die(buf, regs, 0);

		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}

static const struct of_device_id rtk_scpu_wrapper_ids[] __initconst = {
	{.compatible = "Realtek,rtk-scpu_wrapper"},
	{},
};

void scpu_dbg_scpu_monitor(int which, u32 start, u32 end, u32 r_w);

static int __init scpu_wrapper_init(void)
{
	struct device_node *np;
	int irq = 0;
	int i = 0;

	np = of_find_matching_node(NULL, rtk_scpu_wrapper_ids);
	if(unlikely(np == NULL))
		return -1;

	irq = irq_of_parse_and_map(np, 0);

	scpu_wrap_addr = of_iomap(np, 0);
	dbg_info("scpu wrappee irq %d, scpu_wrap_addr 0x%08llx\n", irq, (u64)scpu_wrap_addr);

	of_node_put(np);

	if(request_irq(irq, scpu_wrapper_isr, IRQF_SHARED, "scpu_wrapper", scpu_wrap_addr) != 0){
		dbg_err("Cannot get IRQ\n");
		return -1;
	}

	/* clear dbg trap addr*/
	for(i = 0 ; i < 8 ; i++ )
		writel(0, scpu_wrap_addr + 0x200 + i * 4);
	writel(0x98000000, scpu_wrap_addr + 0x200);	// 1st set start
	writel(0x98000040, scpu_wrap_addr + 0x210);	// 1st set end

	writel(0x98000040, scpu_wrap_addr + 0x204);	// 2nd set start
	writel(0x98000080, scpu_wrap_addr + 0x214);	// 2nd set end

	writel(0x98000080, scpu_wrap_addr + 0x208);	// 3th set start
	writel(0x980000c0, scpu_wrap_addr + 0x218);	// 3th set end

	writel(0x980000c0, scpu_wrap_addr + 0x20c);	// 4th set start
	writel(0x98000100, scpu_wrap_addr + 0x21c);	// 4th set end

	writel(0x9, scpu_wrap_addr + DBG_INT);	// enable interrupt

	printk(KERN_INFO "[SCPU_WRAPPER] initialized\n");

	printk(KERN_INFO "[SCPU_WRAPPER][%s] memory monitor 0x98013b00 - 0x98013c00\n",__FUNCTION__);
	scpu_dbg_scpu_monitor(0, 0x98013b00, 0x98013c00, 0x0);

	set_l4_icg(scpu_wrap_addr);

	return 0;
}
late_initcall(scpu_wrapper_init);

void scpu_dbg_disable_mem_monitor(int which)
{
	void __iomem  *reg_ctrl;

	reg_ctrl = (void __iomem  *)(scpu_wrap_addr + 0x220);
	reg_ctrl += which;
	writel((1 << 13) | (1 << 9) | (1 << 1), reg_ctrl);
}
EXPORT_SYMBOL(scpu_dbg_disable_mem_monitor);

static void scpu_dbg_set_mem_monitor(int which, u32 start, u32 end, u32 flags)
{
	void __iomem  *reg_start;
	void __iomem  *reg_end;
	void __iomem  *reg_ctrl;

	/* disable this set first */
	scpu_dbg_disable_mem_monitor(which);

	reg_start = (void __iomem  *)(scpu_wrap_addr + 0x200 + which);
	reg_end = (void __iomem  *)(scpu_wrap_addr + 0x210 + which);
	reg_ctrl = (void __iomem  *)(scpu_wrap_addr + 0x220 + which);

	writel(start, reg_start);
	writel(end, reg_end);

	writel(flags, reg_ctrl);
}

/*
 * which: 0~7, which register set
 * d_i: SB2_DBG_MONITOR_DATA|SB2_DBG_MONITOR_INST
 * r_w: SB2_DBG_MONITOR_READ|SB2_DBG_MONITOR_WRITE
 */
void scpu_dbg_scpu_monitor(int which, u32 start, u32 end, u32 r_w)
{
	scpu_dbg_set_mem_monitor(which * 4, start, end, (3 << 8) | r_w | 3);
}
EXPORT_SYMBOL(scpu_dbg_scpu_monitor);
