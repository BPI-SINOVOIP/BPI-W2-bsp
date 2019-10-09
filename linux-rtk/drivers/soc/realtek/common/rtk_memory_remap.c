/*
 * rtk_memory_remap.c
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#include <linux/atomic.h>
#include <linux/dmi.h>
#include <linux/efi.h>
#include <linux/export.h>
#include <linux/memblock.h>
#include <linux/mm_types.h>
#include <linux/bootmem.h>
#include <linux/of.h>
#include <linux/of_fdt.h>
#include <linux/of_address.h>
#include <linux/of_reserved_mem.h>
#include <linux/preempt.h>
#include <linux/rbtree.h>
#include <linux/rwsem.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/mmu_context.h>
#include <asm/cacheflush.h>
#include <asm/tlbflush.h>
#include <asm/mmu.h>
#include <asm/pgtable.h>

#include <soc/realtek/memory.h>

#define DRIVER_NAME "RTK_MEM_REMAP"

#ifdef CONFIG_RTK_RPC
extern volatile void __iomem *rpc_ringbuf_base;
extern volatile void __iomem *rpc_common_base;
#endif /* CONFIG_RTK_RPC */

#ifdef CONFIG_RTK_RBUS_BARRIER
extern void __iomem *rbus_addr;
extern int rtk_rbus_barrier_flag;
#endif /* CONFIG_RTK_RBUS_BARRIER */

extern struct of_device_id __rtk_mem_remap_of_table[];

#if 0 // enable if FDT use property "mem_remap" - start

static const struct of_device_id __rtk_mem_remap_of_table_sentinel
	__used __section(__rtk_mem_remap_of_table_end);

#ifdef CONFIG_RTK_RBUS_BARRIER
static void rtk_get_rbus_addr(struct device_node *np)
{
	rbus_addr = of_iomap(np, 0);
	if (rbus_addr)
	rtk_rbus_barrier_flag = 1;
}
#endif /* CONFIG_RTK_RBUS_BARRIER */

#define REALTEK_MAP_OF_DECLARE(name, compat, fn) \
	OF_DECLARE_1(rtk_mem_remap, name, compat, fn)

static void rtk_mem_remap_init(struct device_node *np)
{
#ifdef CONFIG_RTK_RBUS_BARRIER
	rtk_get_rbus_addr(np);
#endif /* CONFIG_RTK_RBUS_BARRIER */

#ifdef CONFIG_RTK_RPC
	rpc_ringbuf_base = (void *)(u64)of_iomap(np, 5);
	rpc_common_base = (void *)(u64)of_iomap(np, 1);
#endif /* CONFIG_RTK_RPC */

	pr_info("[%s] initialized\n", DRIVER_NAME);
}

static void rtk_mem_remap_parent_init(struct device_node *np)
{
	struct device_node *child;
#ifdef CONFIG_RTK_RBUS_BARRIER
	child = of_get_child_by_name(np, "rbus");
	if (child)
		rbus_addr = of_iomap(child, 0);

	if (rbus_addr)
		rtk_rbus_barrier_flag = 1;
#endif /* CONFIG_RTK_RBUS_BARRIER */

#ifdef CONFIG_RTK_RPC
	child = of_get_child_by_name(np, "ringbuf");
	if (child)
		rpc_ringbuf_base = of_iomap(child, 0);

	child = of_get_child_by_name(np, "common");
	if (child)
		rpc_common_base = of_iomap(child, 0);
#endif /* CONFIG_RTK_RPC */

	pr_info("[%s] initialized\n", DRIVER_NAME);
}

void __init rtk_mem_remap_of_init(void)
{
	struct device_node *np;
	unsigned int rtk_mem_remap = 0;

	for_each_compatible_node(np, NULL, "Realtek,rtk1295-mem_remap") {
		if (of_get_child_count(np) >= 3) {
			rtk_mem_remap_parent_init(np);
			rtk_mem_remap++;
			break;
		}
		rtk_mem_remap_init(np);
		rtk_mem_remap++;
	}

	if (!rtk_mem_remap)
		pr_crit("%s: no matching rtk_mem_remap found\n", __func__);
}

REALTEK_MAP_OF_DECLARE(realtek_memory_remap, "Realtek,rtk1295-mem_remap", rtk_mem_remap_init);

#endif // enable if FDT use property "mem_remap" - end

#define VT100_NONE	"\033[m\n"
#define VT100_LIGHT_RED	"\033[1;31m"
#define MYDBG_LEVEL	KERN_INFO

void __init rsvmem_remap(struct reserved_mem *rmem)
{
	unsigned long node = rmem->fdt_node;
	void * ret_iomap;
	const char *type;
	const char *save_remap_name;
	printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, rmem->name %s"
		VT100_NONE, __FUNCTION__, __LINE__, rmem->name);
	type = of_get_flat_dt_prop(node, "compatible", NULL);
	if (!type) {
		printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, no compatible prop"
			VT100_NONE, __FUNCTION__, __LINE__);
		return;
	}
	printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, type %s"
		VT100_NONE, __FUNCTION__, __LINE__, type);
	if( strcmp(type, "rsvmem-remap") != 0 ) {
		printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, value is not match"
			VT100_NONE, __FUNCTION__, __LINE__);
		return;
	}
	if( !rmem->size ) {
		printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, size is zero"
			VT100_NONE, __FUNCTION__, __LINE__);
		return;
	}
	printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, ioremap(%llx,%llx)"
		VT100_NONE, __FUNCTION__, __LINE__, rmem->base, rmem->size);
	ret_iomap = ioremap(rmem->base, rmem->size);;
	if( !ret_iomap ) {
		printk(KERN_ERR VT100_LIGHT_RED "%s %d, ioremap(%llx,%llx)"
			VT100_NONE, __FUNCTION__, __LINE__,
			rmem->base, rmem->size);
		printk(KERN_ERR VT100_LIGHT_RED "%s %d, ioremap failed"
			VT100_NONE, __FUNCTION__, __LINE__);

		return;
	}
	printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, remap addr %p"
		VT100_NONE, __FUNCTION__, __LINE__, ret_iomap);

	save_remap_name = of_get_flat_dt_prop(node, "save_remap_name", NULL);
	if (!save_remap_name) {
		printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, no save_remap_name prop"
			VT100_NONE, __FUNCTION__, __LINE__);
		return;
	}
	printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, save_remap_name %s"
		VT100_NONE, __FUNCTION__, __LINE__, save_remap_name);

	if( strcmp(save_remap_name, "rbus") == 0 ) {
		printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, save rbus_addr"
			VT100_NONE, __FUNCTION__, __LINE__);
#ifdef CONFIG_RTK_RBUS_BARRIER
		rbus_addr = ret_iomap;
#endif
		if (of_get_flat_dt_prop(node, "rtk_rbus_barrier_flag", NULL) ) {
			printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, "
				"set rtk_rbus_barrier_flag to 1"
				VT100_NONE, __FUNCTION__, __LINE__);
#ifdef CONFIG_RTK_RBUS_BARRIER
			rtk_rbus_barrier_flag = 1;
#endif
		}
	}
	if( strcmp(save_remap_name, "common") == 0 ) {
		printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, save rpc_common_base"
			VT100_NONE, __FUNCTION__, __LINE__);
#ifdef CONFIG_RTK_RPC
		rpc_common_base = ret_iomap;
#endif
	}
	if( strcmp(save_remap_name, "ringbuf") == 0 ) {
		printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, save rpc_ringbuf_base"
			VT100_NONE, __FUNCTION__, __LINE__);
#ifdef CONFIG_RTK_RPC
		rpc_ringbuf_base = ret_iomap;
#endif
	}
	printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, init %s/%s done"
		VT100_NONE, __FUNCTION__, __LINE__, rmem->name, save_remap_name);
}

void __init rtk_mem_remap_of_init_by_DT(struct reserved_mem *rmem, int rmem_count)
{
	int i;
	printk(MYDBG_LEVEL VT100_LIGHT_RED "rmem_count: %d"
		VT100_NONE, rmem_count);
	for (i = 0; i < rmem_count; i++) {
		printk(MYDBG_LEVEL "\n");
		rsvmem_remap(&rmem[i]);
	}
}

static void __init rsvmem_remap_setup(struct reserved_mem *rmem)
{
#if 1
	printk(MYDBG_LEVEL VT100_LIGHT_RED "%s %d, not remap %s now"
		VT100_NONE, __FUNCTION__, __LINE__, rmem->name);
#else
	// can not remap due to mm not ready
	rsvmem_remap(rmem);
#endif
}

RESERVEDMEM_OF_DECLARE(rsvmem_remap, "rsvmem-remap", rsvmem_remap_setup);
