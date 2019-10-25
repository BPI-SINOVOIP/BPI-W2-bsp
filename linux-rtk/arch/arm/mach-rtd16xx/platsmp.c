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
#include <asm/barrier.h>
#include <soc/realtek/rtk_cpu.h>

#define BL31_CMD 0x8400ff04
#define BL31_DAT 0x00001619
#define RELEASE_ADDR 0x98007F30
#define CPUID 28

#define CPUPWRCTLR __ACCESS_CP15(c15, 0, c2, 7)

static u32 __iomem *cpu_release_virt;

static int rtd16xx_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	unsigned long entry_pa = __pa_symbol(secondary_startup);

	writel_relaxed(entry_pa | (cpu << CPUID), cpu_release_virt);

	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	return 0;
}

void rtd16xx_prepare_cpus(unsigned int max_cpus)
{
	struct device_node *np;
	int cpu;

	cpu_release_virt = ioremap(RELEASE_ADDR, sizeof(u32));

	for_each_possible_cpu(cpu) {

		np = of_get_cpu_node(cpu, NULL);
		if (!np)
			continue;

		set_cpu_present(cpu, true);
	}
}

#ifdef CONFIG_HOTPLUG_CPU

static void rtd16xx_cpu_die(unsigned int cpu)
{
	struct arm_smccc_res res;
	unsigned int cpu_pwr_ctrl;

	writel_relaxed(0x0, cpu_release_virt);

	/* notify BL31 cpu hotplug */
	arm_smccc_smc(BL31_CMD, BL31_DAT, 0, 0, 0, 0, 0, 0, &res);
	v7_exit_coherency_flush(louis);

	cpu_pwr_ctrl = read_sysreg(CPUPWRCTLR);
	cpu_pwr_ctrl |= 0x1;
	write_sysreg(cpu_pwr_ctrl, CPUPWRCTLR);

	dsb(sy);

	for (;;)
		wfi();
}
#endif

struct smp_operations rtd16xx_smp_ops __initdata = {
	.smp_prepare_cpus = rtd16xx_prepare_cpus,
	.smp_boot_secondary = rtd16xx_boot_secondary,
#ifdef CONFIG_HOTPLUG_CPU
	.cpu_die = rtd16xx_cpu_die,
#endif
};
