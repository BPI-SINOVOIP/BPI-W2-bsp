/*
 * irq-rtd139x.c - RTK irq mux driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/err.h>
#include <linux/export.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/syscore_ops.h>
#include <linux/slab.h>
#include <linux/irqdomain.h>
#include <linux/irqchip/chained_irq.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/irqchip.h>
#include <asm/hardirq.h>
#include <asm/exception.h>
#include <asm/irq.h>

#include "irq-rtd139x.h"

#define DEV_NAME "RTK_IRQ_MUX"

#ifdef CONFIG_RTK_XEN_SUPPORT
#define IRDA_HW_IRQ     37
#endif

static DEFINE_SPINLOCK(irq_mux_lock);

struct irq_mux_data {
	void __iomem *base;
	unsigned char index;
	unsigned int irq;
	unsigned int irq_offset;
	u32 intr_status;
	u32 intr_en;
};

static struct irq_domain *rtk_domain;

static void mux_mask_irq(struct irq_data *data)
{
	struct irq_mux_data *mux_data = irq_data_get_irq_chip_data(data);
	void __iomem *base;
	u32 reg_st;

	mux_data += (data->hwirq / IRQ_INMUX);
	base = mux_data->base;
	reg_st = mux_data->intr_status;

	__raw_writel(BIT(data->hwirq % IRQ_INMUX), base + reg_st);
}

static void mux_unmask_irq(struct irq_data *data)
{
	struct irq_mux_data *mux_data = irq_data_get_irq_chip_data(data);
	void __iomem *base;
	u32 reg_en;
	u8 en_offset;

	mux_data += (data->hwirq / IRQ_INMUX);
	base = mux_data->base;
	reg_en = mux_data->intr_en;

	en_offset = irq_map_tab[mux_data->index][data->hwirq % IRQ_INMUX];

	if ((en_offset != MISC_INT_RVD) && (en_offset != MISC_INT_FAIL)) {

		__raw_writel((__raw_readl(base + reg_en) |
			BIT(en_offset)), base + reg_en);

	} else if (en_offset == MISC_INT_FAIL) {
		pr_err("[%s] Enable irq(%lu) fail\n", DEV_NAME, data->hwirq);
	}

}

static void mux_disable_irq(struct irq_data *data)
{
	struct irq_mux_data *mux_data = irq_data_get_irq_chip_data(data);
	void __iomem *base;
	u32 reg_en;
	u8 en_offset;

#ifdef CONFIG_RTK_XEN_SUPPORT
	if (data->hwirq == IRDA_HW_IRQ && !xen_initial_domain()) {
		pr_info("%s:Skip IRDA on Guest Domain\n", __func__);
		return;
	}
#endif

	mux_data += (data->hwirq / IRQ_INMUX);
	base = mux_data->base;
	reg_en = mux_data->intr_en;

	en_offset = irq_map_tab[mux_data->index][data->hwirq % IRQ_INMUX];

	if ((en_offset != MISC_INT_RVD) && (en_offset != MISC_INT_FAIL)) {

		__raw_writel((__raw_readl(base + reg_en) &
				~BIT(en_offset)), base + reg_en);

	} else if (en_offset == MISC_INT_FAIL) {
		pr_err("[%s] Disable irq(%lu) fail\n", DEV_NAME, data->hwirq);
	}

}

#ifdef CONFIG_SMP
static int __maybe_unused mux_set_affinity(struct irq_data *d,
	const struct cpumask *mask_val,
	bool force)
{
	struct irq_mux_data *mux_data = irq_data_get_irq_chip_data(d);
	struct irq_chip *chip = irq_get_chip(mux_data->irq);
	struct irq_data *data = irq_get_irq_data(mux_data->irq);

	if (chip && chip->irq_set_affinity)
		return chip->irq_set_affinity(data, mask_val, force);
	else
		return -EINVAL;

}
#endif

static struct irq_chip mux_chip = {
	.name = DEV_NAME,
	.irq_mask = mux_mask_irq,
	.irq_unmask = mux_unmask_irq,
	.irq_disable = mux_disable_irq,
#ifdef CONFIG_SMP
	.irq_set_affinity = mux_set_affinity,
#endif
};

static void mux_irq_handle(struct irq_desc *desc)
{
	struct irq_mux_data *mux_data = irq_desc_get_handler_data(desc);
	struct irq_chip *chip = irq_desc_get_chip(desc);
	unsigned int irq = irq_desc_get_irq(desc);
	unsigned int tmp;
	int ret;
	unsigned int mux_irq;
	static u32 count;
	u8 en_offset;
	int i;
	unsigned int status, check_status;
	unsigned int enable;

	u32 reg_st = mux_data->intr_status;
	u32 reg_en = mux_data->intr_en;

	chained_irq_enter(chip, desc);

	spin_lock(&irq_mux_lock);
	enable = __raw_readl(mux_data->base + reg_en);
	status = __raw_readl(mux_data->base + reg_st);
	spin_unlock(&irq_mux_lock);

	for (i = 0 ; i < IRQ_INMUX ; i++) {
		if (status & BIT(i)) {
			en_offset = irq_map_tab[mux_data->index][i];
			mux_irq = mux_data->irq_offset + i;

			if ((en_offset < IRQ_INMUX) &&
				(enable & BIT(en_offset))) {

				tmp = irq_find_mapping(rtk_domain, mux_irq);
				ret = generic_handle_irq(tmp);

				if (ret != 0) {
					pr_err("[%s] irq(%u) desc is not found"
						"(st:0x%08x en:0x%08x)\n",
						DEV_NAME,
						mux_irq,
						status,
						enable);
				}
			} else if (en_offset == MISC_INT_RVD) {

				tmp = irq_find_mapping(rtk_domain, mux_irq);
				ret = generic_handle_irq(tmp);

				if (ret != 0) {
					pr_err("[%s] irq(%u) desc is not found"
						"(st:0x%08x en:0x%08x)\n",
						DEV_NAME,
						mux_irq,
						status,
						enable);
				}
			} else {
				pr_err("[%s] irq(%u) should not happen"
					"(st:0x%08x en:0x%08x)\n",
					DEV_NAME,
					mux_irq,
					status,
					enable);
			}
		}
	}

	/* as a transmission interface, SPI wont do too much here */
	if (irq == 1 && status | 0x08000000)
		goto out;

	spin_lock(&irq_mux_lock);
	check_status = __raw_readl(mux_data->base + reg_st);
	spin_unlock(&irq_mux_lock);

	if (check_status == status) {
		if (count > 1) {
			pr_err("[%s] (%u) %s irq status is not change"
				"clear it! (st:0x%08x en:0x%08x)\n",
				DEV_NAME,
				irq,
				mux_data->index ? "ISO" : "MISC",
				status,
				enable);
		} else {
			count++;
		}

		spin_lock(&irq_mux_lock);
		__raw_writel(BIT(__ffs(status)), mux_data->base + reg_st);
		spin_unlock(&irq_mux_lock);

	} else {
		count = 0;
	}
out:
	chained_irq_exit(chip, desc);
}

static int mux_irq_domain_xlate(struct irq_domain *d,
	struct device_node *controller,
	const u32 *intspec,
	unsigned int intsize,
	unsigned long *out_hwirq,
	unsigned int *out_type)
{
	if (controller != irq_domain_get_of_node(d))
		return -EINVAL;

	if (intsize < 2)
		return -EINVAL;

	*out_hwirq = intspec[0] * IRQ_INMUX + intspec[1];
	*out_type = 0;

	return 0;
}

static int mux_irq_domain_map(struct irq_domain *d,
						unsigned int irq,
						irq_hw_number_t hw)
{
	struct irq_mux_data *data = d->host_data;

	irq_set_chip_and_handler(irq, &mux_chip, handle_level_irq);
	irq_set_chip_data(irq, data);
	irq_set_probe(irq);

	return 0;
}

static const struct irq_domain_ops mux_irq_domain_ops = {
	.xlate = mux_irq_domain_xlate,
	.map = mux_irq_domain_map,
};

static void __init mux_init_each(struct irq_mux_data *mux_data,
	void __iomem *base,
	u32 irq, u32 status,
	u32 enable, int nr)
{
	mux_data->base = base;
	mux_data->index = nr;
	mux_data->irq = irq;
	mux_data->irq_offset = nr * IRQ_INMUX;
	mux_data->intr_status = status;
	mux_data->intr_en = enable;

#ifndef CONFIG_RTK_XEN_SUPPORT  // UART is handled at hypervisor, clear bit will cause console stop
	__raw_writel((__raw_readl(base + enable) & ~BIT(2)), base + enable);
	__raw_writel(BIT(2), base + status);
#endif

	irq_set_chained_handler_and_data(irq, mux_irq_handle, mux_data);

}

#ifdef CONFIG_OF
static int __init mux_of_init(struct device_node *np,
	struct device_node *parent)
{
	int i;
	u32 nr_irq = 1;
	struct irq_mux_data *mux_data;
	void __iomem *base;
	u32 irq;
	u32 status, enable;

	if (WARN_ON(!np))
		return -ENODEV;

	if (of_property_read_u32(np, "Realtek,mux-nr", &nr_irq))
		pr_err("[%s] can not specified mux number", DEV_NAME);

	mux_data = kcalloc(nr_irq, sizeof(*mux_data), GFP_KERNEL);

	/*
	 * TODO : tempary define the first irq number
	 * in this mux is 160, end in 160+64
	 */
	rtk_domain = irq_domain_add_simple(np,
		(nr_irq * IRQ_INMUX),
		160,
		&mux_irq_domain_ops,
		mux_data);

	if (!rtk_domain)
		pr_warn("[%s] IRQ domain init failed\n", DEV_NAME);

	for (i = 0; i < nr_irq; i++) {
		base = of_iomap(np, i);

		if (!base)
			pr_warn("[%s] unable to map IRQ base registers\n",
				DEV_NAME);


		irq = irq_of_parse_and_map(np, i);

		if (!irq)
			pr_warn("[%s] can not map IRQ\n", DEV_NAME);

		of_property_read_u32_index(np, "intr-status", i, &status);
		of_property_read_u32_index(np, "intr-en", i, &enable);

		mux_init_each(mux_data, base, irq, status, enable, i);

		mux_data++;
	}

	return 0;
}

IRQCHIP_DECLARE(rtk_irq_mux, "Realtek,rtk-irq-mux", mux_of_init);
#endif
