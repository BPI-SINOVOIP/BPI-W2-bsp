#include <linux/init.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/io.h>
#include <linux/memory.h>
#include <linux/smp.h>
#include <linux/of.h>
#include <linux/arm-smccc.h>
#include <asm/smp_plat.h>
#include <asm/cacheflush.h>
#include <asm/cp15.h>
#include <soc/realtek/rtk_cpu.h>

#define BL31_CMD 0x8400ff04
#define BL31_DAT 0x00001319

void rtd13xx_secondary_startup(void);

extern void cpu_do_lowpower(unsigned long secondary_entry_addr);

static int cpu_hotplug = 0;

static DEFINE_SPINLOCK(cpu_lock);

static void write_pen_release(int val)
{
	pen_release = val;
	smp_wmb();
	sync_cache_w(&pen_release);
}

static void rtd13xx_secondary_init(unsigned int cpu)
{
	/* let primary processor know we are out of pen */
	write_pen_release(-1);

	/* syn with the boot thread */
	spin_lock(&cpu_lock);
	spin_unlock(&cpu_lock);
}

static int rtd13xx_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	unsigned long timeout;
	unsigned long phys_cpu = cpu_logical_map(cpu);

	if(cpu_hotplug == 1){
		arch_send_wakeup_ipi_mask(cpumask_of(cpu));
	}

	write_pen_release(phys_cpu);

	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	timeout = jiffies + (1*HZ);
	while(time_before(jiffies, timeout)) {
		smp_wmb();
		if (pen_release == -1)
			break;
		udelay(10);
	}

	return pen_release != -1 ? -ENOSYS : 0;
}

void rtd13xx_prepare_cpus(unsigned int max_cpus)
{
	int i;

	for (i = 0 ; i < max_cpus ; i++) {
		set_cpu_present(i, true);
	}

	smp_wmb();
}

static void __init rtd13xx_init_cpus(void)
{
	void __iomem *rbus_base;

	rbus_base = ioremap(0x98007F30, 0x10);

	writel(virt_to_phys(rtd13xx_secondary_startup), rbus_base);

	iounmap(rbus_base);
}

#ifdef CONFIG_HOTPLUG_CPU

static void rtd13xx_cpu_die(unsigned int cpu)
{
	struct arm_smccc_res res;

	/* notify BL31 cpu hotplug */
	arm_smccc_smc(BL31_CMD, BL31_DAT, 0, 0, 0, 0, 0, 0, &res);
	cpu_hotplug = 1;
	v7_exit_coherency_flush(louis);

	cpu_do_lowpower(0x98007F30);
}
#endif

struct smp_operations rtd13xx_smp_ops __initdata = {
	.smp_prepare_cpus = rtd13xx_prepare_cpus,
	.smp_init_cpus = rtd13xx_init_cpus,
	.smp_secondary_init = rtd13xx_secondary_init,
	.smp_boot_secondary = rtd13xx_boot_secondary,
#ifdef CONFIG_HOTPLUG_CPU
	.cpu_die = rtd13xx_cpu_die,
#endif
};
