/*
 * rtd139x_spin_table.c - boot method
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
#include <asm/io.h>

#include <asm/cacheflush.h>
#include <asm/cpu_ops.h>
#include <asm/cputype.h>
#include <asm/io.h>
#include <asm/smp_plat.h>

#ifdef CONFIG_SMP

extern void rtk_cpu_power_up(int cpu);
extern void _rtk_cpu_power_up(int cpu);
extern void secondary_holding_pen(void);

void __cpu_do_lowpower(void);

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

		rtk_cpu_power_up(cpu);

		_rtk_cpu_power_up(cpu);

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
#ifndef CONFIG_RTK_VMX_ULTRA
	/*
	 * Set the fake core0 resume address to BL31
	 * to let Bl31 know slave cpu will resume
	 */
	asm volatile("isb" : : : "cc");
	asm volatile("ldr x1, =0x20000" : : : "cc");
	asm volatile("ldr x0, =0x8400ff04" : : : "cc");
	asm volatile("isb" : : : "cc");
	asm volatile("smc #0" : : : "cc");
	asm volatile("isb" : : : "cc");
#else
	__le64 __iomem *cpu0_resume_addr;
	cpu0_resume_addr = ioremap(0x98007660, sizeof(*cpu0_resume_addr));
	if (!cpu0_resume_addr)
		pr_err("smp_spin_table_cpu_die - fail to ioremap\n");
	writel_relaxed(0x20000, cpu0_resume_addr);
	__flush_dcache_area((__force void *)cpu0_resume_addr, sizeof(*cpu0_resume_addr));
	iounmap(cpu0_resume_addr);
#endif

	cpu_hotplug[cpu] = 1;
	flush_cache_all();
	setup_mm_for_reboot();
	__cpu_do_lowpower();
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
