/*
 * rtd13xx_spin_table.c - boot method
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * Author: Chih-Feng Tai <james.tai@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#include <linux/delay.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/smp.h>
#include <linux/types.h>
#include <linux/ioport.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/io.h>
#include <linux/memblock.h>
#include <linux/delay.h>
#include <linux/printk.h>
#include <linux/arm-smccc.h>
#include <asm/io.h>
#include <asm/cacheflush.h>
#include <asm/cpu_ops.h>
#include <asm/cputype.h>
#include <asm/io.h>
#include <asm/smp_plat.h>

#include "rtd13xx_cpu_hotplug.h"

#define BL31_CMD 0x8400ff04
#define BL31_DAT 0x00001319

#ifdef CONFIG_SMP

extern void _rtk_cpu_power_up(int cpu);
extern void secondary_holding_pen(void);

volatile unsigned long rtk_secondary_holding_pen_release = INVALID_HWID;

static phys_addr_t cpu_release_addr[NR_CPUS];
static int cpu_hotplug[NR_CPUS] = {0};
/*
 * Write rtk_secondary_holding_pen_release in a way that is guaranteed to be
 * visible to all observers, irrespective of whether they're taking part
 * in coherency or not.  This is necessary for the hotplug code to work
 * reliably.
 */
static void write_pen_release(u64 val)
{
	void *start = (void *)&rtk_secondary_holding_pen_release;
	unsigned long size = sizeof(rtk_secondary_holding_pen_release);

	rtk_secondary_holding_pen_release = val;
	__flush_dcache_area(start, size);
}

static int smp_spin_table_cpu_init(unsigned int cpu)
{

	struct device_node *dn;

	dn = of_get_cpu_node(cpu, NULL);
	if (!dn)
		return -ENODEV;

	/*
	 * Determine the address from which the CPU is polling.
	 */

	if(of_property_read_u64(dn, "cpu-release-addr", &cpu_release_addr[cpu])){
		pr_err("CPU %d: missing or invalid cpu-release-addr property\n", cpu);
		return -1;
	}

	return 0;
}

static int smp_spin_table_cpu_prepare(unsigned int cpu)
{
	__le64 __iomem *release_addr;

	/*
	 * The cpu-release-addr may or may not be inside the linear mapping.
	 * As ioremap_cache will either give us a new mapping or reuse the
	 * existing linear mapping, we can use it to cover both cases. In
	 * either case the memory will be MT_NORMAL.
	 */

	release_addr = ioremap(cpu_release_addr[cpu], sizeof(*release_addr));

	if (!release_addr)
		return -ENOMEM;

	/*
	 * We write the release address as LE regardless of the native
	 * endianess of the kernel. Therefore, any boot-loaders that
	 * read this address need to convert this address to the
	 * boot-loader's endianess before jumping. This is mandated by
	 * the boot protocol.
	 */
	writel_relaxed(__pa(secondary_holding_pen), release_addr);

	__flush_dcache_area((__force void *)release_addr, sizeof(*release_addr));

	/*
	 * Send an event to wake up the secondary CPU.
	 */
	sev();

	iounmap(release_addr);

	return 0;
}

static int smp_spin_table_cpu_boot(unsigned int cpu)
{
	if(cpu_hotplug[cpu] == 1){
		__le64 __iomem *release_addr;
		release_addr = ioremap(cpu_release_addr[cpu], sizeof(*release_addr));
		writel_relaxed(__pa(secondary_holding_pen), release_addr);

		__flush_dcache_area((__force void *)release_addr, sizeof(*release_addr));

		smp_send_reschedule(cpu);
		iounmap(release_addr);
	}

	/*
	 * Update the pen release flag.
	 */
	write_pen_release(cpu_logical_map(cpu));

	/*
	 * Send an event, causing the secondaries to read pen_release.
	 */

	sev();
	return 0;
}

#ifdef CONFIG_HOTPLUG_CPU
static int smp_spin_table_cpu_disable(unsigned int cpu)
{
	if (!cpu_release_addr[cpu])
		return -EOPNOTSUPP;

	return 0;
}

static void smp_spin_table_cpu_die(unsigned int cpu)
{
	struct arm_smccc_res res;

	/* notify BL31 cpu hotplug */
	arm_smccc_smc(BL31_CMD, BL31_DAT, 0, 0, 0, 0, 0, 0, &res);
	cpu_hotplug[cpu] = 1;
	cpu_do_lowpower(cpu_release_addr[cpu]);
}
#endif

const struct cpu_operations rtk_smp_spin_table_ops = {
	.name = "rtk-spin-table",
	.cpu_init = smp_spin_table_cpu_init,
	.cpu_prepare = smp_spin_table_cpu_prepare,
	.cpu_boot = smp_spin_table_cpu_boot,
#ifdef CONFIG_HOTPLUG_CPU
	.cpu_disable = smp_spin_table_cpu_disable,
	.cpu_die = smp_spin_table_cpu_die,
#endif
};

#endif /* CONFIG_SMP */
