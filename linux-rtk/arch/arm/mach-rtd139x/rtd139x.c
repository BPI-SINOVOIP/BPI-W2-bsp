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

extern struct smp_operations rtd139x_smp_ops;

static struct map_desc rtd139x_io_desc[] __initdata = {
	{
	.virtual = (unsigned long) IOMEM(RBUS_BASE_VIRT),
	.pfn = __phys_to_pfn(RBUS_BASE_PHYS),
	.length = RBUS_BASE_SIZE,
	.type = MT_DEVICE,
	},
};

void __init rtd139x_map_io(void)
{
	debug_ll_io_init();

	iotable_init(rtd139x_io_desc, ARRAY_SIZE(rtd139x_io_desc));
}

static const char * const rtd139x_board_dt_compat[] = {
	"realtek,rtd1395",
	NULL,
};

static void __init rtk139x_dt_init(void)
{
	of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);
}

DT_MACHINE_START(RTD1395, "Hercules")
	.map_io = rtd139x_map_io,
	.init_machine = rtk139x_dt_init,
	.dt_compat = rtd139x_board_dt_compat,
	.smp = smp_ops(rtd139x_smp_ops),
MACHINE_END
