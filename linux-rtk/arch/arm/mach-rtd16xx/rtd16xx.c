#include <linux/clk-provider.h>
#include <linux/clocksource.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/irqchip.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/io.h>
#include <linux/memblock.h>
#include <linux/delay.h>
#include <linux/clockchips.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/system_misc.h>
#include <asm/system_info.h>

#include <mach/memory.h>

extern struct smp_operations rtd16xx_smp_ops;

static struct map_desc rtd16xx_io_desc[] __initdata = {
	{
	.virtual = (unsigned long) IOMEM(RBUS_BASE_VIRT),
	.pfn = __phys_to_pfn(RBUS_BASE_PHYS),
	.length = RBUS_BASE_SIZE,
	.type = MT_DEVICE,
	},
};

void __init rtd16xx_map_io(void)
{
	debug_ll_io_init();

	iotable_init(rtd16xx_io_desc, ARRAY_SIZE(rtd16xx_io_desc));
}

static const char * const rtd16xx_board_dt_compat[] = {
	"realtek,rtd1619",
	NULL,
};

static void __init rtk16xx_dt_init(void)
{
	of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);
}

static void __init rtk16xx_timer_init(void)
{
#ifdef CONFIG_COMMON_CLK
	of_clk_init(NULL);
#endif
	clocksource_probe();
	tick_setup_hrtimer_broadcast();
}

bool __init rtd16xx_smp_init_ops(void)
{
	smp_set_ops(smp_ops(rtd16xx_smp_ops));
	return true;
}

DT_MACHINE_START(RTD1619, "Thor")
	.map_io = rtd16xx_map_io,
	.init_machine = rtk16xx_dt_init,
	.init_time = rtk16xx_timer_init,
	.dt_compat = rtd16xx_board_dt_compat,
	.smp = smp_ops(rtd16xx_smp_ops),
	.smp_init = smp_init_ops(rtd16xx_smp_init_ops),
MACHINE_END
