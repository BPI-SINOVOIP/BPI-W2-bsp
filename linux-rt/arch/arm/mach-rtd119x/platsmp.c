#include <linux/init.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/io.h>
#include <linux/memory.h>
#include <linux/smp.h>

#include <asm/smp_plat.h>
#include <asm/cacheflush.h>

void secondary_startup(void);
void rtk119x_secondary_startup(void);

static void write_pen_release(int val)
{
    pen_release = val;
    smp_wmb();
    __cpuc_flush_dcache_area((void*)&pen_release, sizeof(pen_release));
}

static DEFINE_SPINLOCK(cpu_lock);

static void rtk119x_secondary_init(unsigned int cpu)
{
    /* let primary processor know we are out of pen */
    write_pen_release(-1);

    /* syn with the boot thread */
    spin_lock(&cpu_lock);
    spin_unlock(&cpu_lock);
}

static int rtk119x_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
    unsigned long timeout;
    unsigned long phys_cpu = cpu_logical_map(cpu);

    spin_lock(&cpu_lock);

    write_pen_release(phys_cpu);

#ifndef CONFIG_ARM_NORMAL_WORLD_OS
    writel(readl(IOMEM(0xfe01d100)) | BIT(5), IOMEM(0xfe01d100));		// wrap_a7 issue nCORERESET
    writel(virt_to_phys(rtk119x_secondary_startup), IOMEM(0xfe007064));
#else
    writel(virt_to_phys(secondary_startup), IOMEM(0xfe007064));
#endif
    arch_send_wakeup_ipi_mask(cpumask_of(cpu));

    timeout = jiffies + (1*HZ);
    while (time_before(jiffies, timeout)) {
        smp_rmb();
        if (pen_release == -1)
            break;
        udelay(10);
    }

    /* now the 2nd core is starting up */
    spin_unlock(&cpu_lock);

    return pen_release != -1 ? -ENOSYS : 0;
}

void rtk119x_prepare_cpus(unsigned int max_cpus)
{
    int i;

    for (i=0; i<max_cpus; i++) {
        set_cpu_present(i, true);
    }
    smp_wmb();
}

static void __init rtk119x_init_cpus(void)
{
#ifndef CONFIG_ARM_NORMAL_WORLD_OS
    writel(readl(IOMEM(0xfe01d100)) & ~BIT(5), IOMEM(0xfe01d100));		// wrap_a7 issue nCORERESET
    writel(virt_to_phys(rtk119x_secondary_startup), IOMEM(0xfe007064));
#endif
}

extern void rtk119x_cpu_die(unsigned int cpu);

struct smp_operations rtk119x_smp_ops __initdata = {
    .smp_prepare_cpus		= rtk119x_prepare_cpus,
    .smp_init_cpus			= rtk119x_init_cpus,
    .smp_secondary_init		= rtk119x_secondary_init,
    .smp_boot_secondary		= rtk119x_boot_secondary,
#ifdef CONFIG_HOTPLUG_CPU
    .cpu_die			= rtk119x_cpu_die,
#endif
};
