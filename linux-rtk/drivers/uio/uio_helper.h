/*
 * Helper Macros for UIO
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __UIO_HELPER_H__
#define __UIO_HELPER_H__

#include <linux/clk.h>
#include <linux/dma-mapping.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/reset.h>
#include <linux/slab.h>
#include <linux/uio_driver.h>

static inline void *uio_get_mem(struct uio_info *info, int index)
{
	return info->mem[index].internal_addr;
}

static inline void uio_mem_print(struct device *dev, struct uio_mem *mem)
{
	dev_info(dev, "phys:%pa virt:0x%p size:%pa type:%d name:%s\n",
		&mem->addr, mem->internal_addr, &mem->size,
		mem->memtype, mem->name);
}

static inline int uio_mem_of_iomap(struct device *dev,
	struct uio_mem *mem, int index)
{
	struct resource res;
	struct device_node *np = dev->of_node;
	int ret;

	if (!np)
		return -EINVAL;

	ret = of_address_to_resource(np, index, &res);
	if (ret)
		return ret;

	mem->addr          = res.start;
	mem->size          = ALIGN(resource_size(&res), PAGE_SIZE);
	mem->internal_addr = ioremap(res.start, resource_size(&res));
	mem->memtype       = UIO_MEM_PHYS;
	return 0;
}

static inline void uio_mem_iounmap(struct device *dev, struct uio_mem *mem)
{
	if (!mem->internal_addr)
		return;

	iounmap(mem->internal_addr);
}

static inline int uio_mem_dma_alloc(struct device *dev, struct uio_mem *mem,
	size_t size, gfp_t flag)
{
	void *virt = NULL;
	dma_addr_t phys = 0;

	size = ALIGN(size, PAGE_SIZE);
	virt = dma_alloc_coherent(dev, size, &phys, flag);
	if (!virt)
		return -ENOMEM;

	mem->addr          = phys;
	mem->size          = size;
	mem->internal_addr = virt;
	mem->memtype       = UIO_MEM_PHYS;
	return 0;
}

static inline void uio_mem_dma_free(struct device *dev, struct uio_mem *mem)
{
	if (!mem->internal_addr)
		return;

	dma_free_coherent(dev, mem->size, mem->internal_addr, mem->addr);
}

static inline int uio_reset_control_deassert(struct device *dev,
	const char *id)
{
	struct reset_control *rstc;
	struct device_node *np = dev->of_node;

	if (!np)
		return -EINVAL;

	if (!of_get_property(np, "resets", NULL))
		return 0;

	rstc = reset_control_get(dev, id);
	if (IS_ERR(rstc))
		return PTR_ERR(rstc);
	reset_control_deassert(rstc);
	reset_control_put(rstc);

	return 0;
}

static inline int uio_reset_control_assert(struct device *dev,
	const char *id)
{
	struct reset_control *rstc;
	struct device_node *np = dev->of_node;

	if (!np)
		return -EINVAL;

	if (!of_get_property(np, "resets", NULL))
		return 0;

	rstc = reset_control_get(dev, id);
	if (IS_ERR(rstc))
		return PTR_ERR(rstc);
	reset_control_assert(rstc);
	reset_control_put(rstc);

	return 0;
}

#endif /* __UIO_HELPER_H__ */
