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
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/system_misc.h>
#include <asm/system_info.h>

#include <mach/memory.h>

extern struct smp_operations rtd13xx_smp_ops;

static struct map_desc rtd13xx_io_desc[] __initdata = {
	{
	.virtual = (unsigned long) IOMEM(RBUS_BASE_VIRT),
	.pfn = __phys_to_pfn(RBUS_BASE_PHYS),
	.length = RBUS_BASE_SIZE,
	.type = MT_DEVICE,
	},
};

void __init rtd13xx_map_io(void)
{
	debug_ll_io_init();

	iotable_init(rtd13xx_io_desc, ARRAY_SIZE(rtd13xx_io_desc));
}

static const char * const rtd13xx_board_dt_compat[] = {
	"realtek,rtd1319",
	"realtek,hank",
	NULL,
};

static void __init rtk13xx_dt_init(void)
{
	of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);
}

bool __init rtd13xx_smp_init_ops(void)
{
	smp_set_ops(smp_ops(rtd13xx_smp_ops));
	return true;
}

DT_MACHINE_START(RTD1319, "Hank")
	.map_io = rtd13xx_map_io,
	.init_machine = rtk13xx_dt_init,
	.dt_compat = rtd13xx_board_dt_compat,
	.smp = smp_ops(rtd13xx_smp_ops),
	.smp_init = smp_init_ops(rtd13xx_smp_init_ops),
MACHINE_END
