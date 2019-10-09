/*
 * rtd16xx_cpu_wrapper.c
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
#include <linux/smp.h>
#include <linux/types.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/memblock.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/of_irq.h>

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

static void __iomem *scpu_wrap_addr;

void rtk_cpu_power_up(int cpu)
{
	u32 tmp = 0;
	u32 flag1 = 0;
	u32 flag2 = 0;
	u32 cpu_offset = cpu * 4;

	/* 1. Apply power to the PDCPU power domain.
	 * Keep the state of the signals nCPUPORESET */
	tmp = readl(scpu_wrap_addr + 0x538);
	tmp |= 1UL << (0 + cpu);
	tmp |= 1UL << (8 + cpu);
	writel(tmp, scpu_wrap_addr + 0x538);

	do {
		tmp = readl(scpu_wrap_addr + 0x53C);
		flag1 = !((tmp >> (0 + cpu)) & 0x1);
		flag2 = !((tmp >> (8 + cpu)) & 0x1);
		if (flag1 || flag2) {
			pr_err("%s: CPU%d Power Mode Request is not ON\n",
				__func__, cpu);
			pr_err("%s: %x = %x\n", __func__,
				(0x9801d000 + 0x53C), tmp);
		}

	} while( flag1 ||flag2 );

	/* 2. Release the core output clamps. */
	tmp = readl(scpu_wrap_addr + 0x538);
	tmp &= ~(1UL << (16 + cpu));
	writel(tmp, scpu_wrap_addr + 0x538);

	/* 3. SCP setup core P-Channel corresponding PSTATE Register
	 * Request Power Mode to ON */
	tmp = readl(scpu_wrap_addr + (0x540 + cpu_offset));
	tmp &= 0x0000003F;
	tmp |= 0x00000008;
	writel(tmp, scpu_wrap_addr + (0x540 + cpu_offset));

	/* 4. De-assert CPU cores resets. */
	if (cpu < 4) {
		tmp = readl(scpu_wrap_addr + 0x100);
		tmp |= 1UL << (0 + cpu);
		tmp |= 1UL << (4 + cpu);
		writel(tmp, scpu_wrap_addr + 0x100);
	} else {
		tmp = readl(scpu_wrap_addr + 0x900);
		tmp |= 1UL << (0 + (cpu - 4));
		tmp |= 1UL << (4 + (cpu - 4));
		writel(tmp, scpu_wrap_addr + 0x900);
	}

}
EXPORT_SYMBOL(rtk_cpu_power_up);

void rtk_cpu_power_down(int cpu)
{
	u32 tmp = 0;
	u32 cpu_offset = cpu * 4;

	/* SCP polling core corresponding P-Channel PACTIVE Register,
	 * SC_CORE_PCHANNEL_STAT_ACK bit[10:0] is 0x0
	 * (Power Mode Request is OFF)
	 */
	do {
		tmp = readl(scpu_wrap_addr + (0x5C0 + cpu_offset));
		tmp = tmp & 0x000007FF;
		if (tmp != 0x00000000) {
			pr_err("%s: CPU%d Power Mode Request is not OFF\n",
				__func__, cpu);
			pr_err("%s: %x = %d \n",
				__func__, (0x9801d000 + 0x5C0 + cpu_offset),
				tmp);
		}
	} while (tmp != 0x00000000);

	/* SCP setup core P-Channel corresponding PSTATE Register,
	 * Set SC_CORE_PCHANNEL_CTRL bit[5:0] as 0x0
	 * (Request Power Mode to OFF)
	 *
	 * Set SC_CORE_PCHANNEL_CTRL bit[16] as 0x1
	 * to assert P-Channel Request
	 */
	tmp = readl(scpu_wrap_addr + (0x540 + cpu_offset));
	tmp &= 0xFFFFFFC0;
	tmp |= 1UL << 16;
	writel(tmp, scpu_wrap_addr + (0x540 + cpu_offset));

	/* Wait P-Channel Request is Accepted:
	 * Polling when SC_ CORE_PCHANNEL INT_STAT bit[8:0] is 0x1
	 * (only paccept is asserted),
	 * SC_CORE_PCHANNEL_STAT_ACK_TRIGGER bit[10:0] is 0x0
	 * (Power Mode Request is OFF).
	 */
	do {
		mdelay(1);
		tmp = readl(scpu_wrap_addr + (0x930 + cpu_offset));
		tmp &= 0x00000001;
		if (!tmp) {
			pr_err("%s: %x bit [8:0] is not 0x1, %x = %x\n",
				__func__,
				(0x9801d000 + 0x930 + cpu_offset),
				(0x9801d000 + 0x930 + cpu_offset), tmp);
		}
	} while (!tmp);

	do {
		tmp = readl(scpu_wrap_addr + (0x580 + cpu_offset));
		tmp &= 0x000007FF;
		if (tmp) {
			pr_err("%s: CPU%d Power Mode Request is not OFF\n",
				__func__, cpu);
			pr_err("%s: %x = %x\n", __func__,
				(0x9801d000 + 0x580 + cpu_offset), tmp);
		}
	} while (tmp);

	/*
	 * SCP set SCPU Power_CTRL rbus register to reach the
	 * requested power mode physical control.
	 */

	/* Activate the core output clamps. */
	tmp = readl(scpu_wrap_addr + 0x538);
	tmp |= 1UL << (16 + cpu);
	writel(tmp, scpu_wrap_addr + 0x538);

	/* Assert nCPUPORESET LOW. */
	if (cpu < 4) {
		tmp = readl(scpu_wrap_addr + 0x100);
		tmp &= ~(1UL << (0 + cpu));
		tmp &= ~(1UL << (4 + cpu));
		writel(tmp, scpu_wrap_addr + 0x100);
	} else {
		tmp = readl(scpu_wrap_addr + 0x900);
		tmp &= ~(1UL << (0 + (cpu - 4)));
		tmp &= ~(1UL << (4 + (cpu - 4)));
		writel(tmp, scpu_wrap_addr + 0x900);
	}

	/* Remove power from the PDCPU power domain. */
	tmp = readl(scpu_wrap_addr + 0x538);
	tmp &= ~(1UL << (0 + cpu));
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
