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
#include <mach/cpu.h>

extern struct smp_operations rtk119x_smp_ops;

unsigned long realtek_cpu_id;

static struct map_desc rtk119x_io_desc[] __initdata = {
    {
        .virtual	= (unsigned long) IOMEM(RBUS_BASE_VIRT),
        .pfn		= __phys_to_pfn(RBUS_BASE_PHYS),
        .length		= RBUS_BASE_SIZE,
        .type		= MT_DEVICE,
    },
    {
        .virtual	= (unsigned long) SYSTEM_GIC_BASE_VIRT,
        .pfn		= __phys_to_pfn(SYSTEM_GIC_BASE_PHYS),
        .length		= 0x10000,
        .type		= MT_DEVICE,
    },
    {
         /*
         * RPC ring buffer
         * 0xfc8000000 - 0x4000 = 0xfc7fc000
         */
        .virtual	= (unsigned long) IOMEM(RPC_RINGBUF_VIRT),
        .pfn		= __phys_to_pfn(RPC_RINGBUF_PHYS),
        .length		= RPC_RINGBUF_SIZE,
        .type		= MT_DEVICE,
    },
    {
        .virtual	= (unsigned long) IOMEM(RPC_COMM_VIRT),
        .pfn		= __phys_to_pfn(RPC_COMM_PHYS),
        .length		= RPC_COMM_SIZE,
        .type		= MT_DEVICE,
    },
    {
                .virtual        = (unsigned long) IOMEM(SPI_RBUS_VIRT),
                .pfn            = __phys_to_pfn(SPI_RBUS_PHYS),
                .length         = SPI_RBUS_SIZE,
                .type           = MT_DEVICE,
    }
};

void __init rtk119x_map_io(void)
{
    debug_ll_io_init();

    iotable_init(rtk119x_io_desc, ARRAY_SIZE(rtk119x_io_desc));
}

static int __init rtk_memblock_remove(phys_addr_t base, phys_addr_t size)
{
    int ret = memblock_remove(base, size);

    if (ret)
        printk(KERN_ERR "Failed to remove memory (%ld bytes at 0x%08lx)\n",
               (long)size, (unsigned long)base);
    else
        printk(KERN_INFO "remove memory (%ld bytes at 0x%08lx)\n",
               (long)size, (unsigned long)base);

    return ret;
}

void __init rtk_reserve(void)
{
    rtk_memblock_remove(RBUS_BASE_PHYS, 0x00100000);
    rtk_memblock_remove(PLAT_NOR_PHYS, PLAT_NOR_SIZE);
    rtk_memblock_remove(PLAT_SECURE_PHYS, PLAT_SECURE_SIZE);
}

static void __init rtk119x_dt_init(void)
{
    system_rev = readl(IOMEM(0xfe01A204));
    realtek_cpu_id = readl(IOMEM(0xfe01A200));

    of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);

    /* setting SCPU wrapper to force as buffable */
    writel(((readl(IOMEM(0xfe01d000)) & ~(0x3<<12)) | (0x1 <<12)), IOMEM(0xfe01d000));
    writel(0x1234, IOMEM(0xfe01a020));	/* latch */
}

static const char * const rtk119x_board_dt_compat[] = {
    "Realtek,rtd-119x",
    NULL,
};

static void __init rtk119x_timer_init(void)
{
    writel(0x1, IOMEM(0xff018000));

    of_clk_init(NULL);
    clocksource_probe();
}

// ------------------------ ~COMMON ---------------------------------
unsigned int realtek_rev(void)
{
    return (system_rev>>16);
}

DT_MACHINE_START(RTD119X_DT, "phoenix")
	.init_machine		= rtk119x_dt_init,
	.reserve		= rtk_reserve,
	.map_io			= rtk119x_map_io,
	.init_time		= rtk119x_timer_init,
	.dt_compat		= rtk119x_board_dt_compat,
	.smp                    = smp_ops(rtk119x_smp_ops),
MACHINE_END
