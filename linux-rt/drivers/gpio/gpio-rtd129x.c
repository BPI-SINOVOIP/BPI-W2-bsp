/*
 * Realtek GPIO driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include <linux/gpio.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/irqdomain.h>
#include <linux/irqchip/chained_irq.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/pinctrl/consumer.h>
#include <linux/irqchip.h>

#ifdef CONFIG_RTK_XEN_SUPPORT
#include <xen/xen.h>
#endif

#include "gpio-rtd129x.h"

#define GPIO_REG_OFST(id)       (id >> 5) // (id/32)
#define GPIO_REG_BIT(id)        (id & 0x1F)	// id % 32
#define GPIO_INT_REG_OFST(id)   (id/31)
#define GPIO_INT_REG_BIT(id)    ((id%31)+1)

/* intc mux tempary define the first irq number in this mux is 160 */
static const struct rtk_gpio_groups rtk_gpio_grps_array[] = {
	{
		.group_name = "rtk_misc_gpio",
		.group_index = 0,
		/*160(predefine base)+64(intc_mux)*/
		.linux_irq_base = 224,
		/*Bit20, de-assert interrupt flag*/
		.gpio_isr_deassert_int = 0x00100000,
		/*Bit19, assert interrupt flag*/
		.gpio_isr_assert_int = 0x00080000,
		/*MIS_ISR*/
		.reg_isr_off = 0xc,
		/* MIS_UMSK_ISR_GP0A, UMSK_ISR_GP1A, UMSK_ISR_GP2A, UMSK_ISR_GP3A */
		.reg_umsk_isr_gpa_off = {0x40, 0x44, 0xa4, 0xb8},
		/* MIS_UMSK_ISR_GP0DA, UMSK_ISR_GP1DA, UMSK_ISR_GP2DA, UMSK_ISR_GP3DA*/
		.reg_umsk_isr_gpda_off = {0x54, 0x58, 0xa8, 0xbc},
		/* MIS_GP0DIR, GP1DIR, GP2DIR, GP3DIR */
		.reg_dir_off = {0x00, 0x04, 0x08, 0x0c},
		/* MIS_GP0DATO, GP1DATO, GP2DATO, GP3DATO */
		.reg_dato_off = {0x10, 0x14, 0x18, 0x1c},
		/* MIS_GP0DATI, GP1DATI, GP2DATI, GP3DATI */
		.reg_dati_off = {0x20, 0x24, 0x28, 0x2c},
		/* MIS_GP0IE, GP1IE, GP2IE, GP3IE */
		.reg_ie_off = {0x30, 0x34, 0x38, 0x3c},
		/* MIS_GP0DP, GP1DP, GP2DP, GP3DP */
		.reg_dp_off = {0x40, 0x44, 0x48, 0x4c},
		/*MIS_GPDEB*/
		.reg_deb_off = 0x50,
	},
	{
		.group_name = "rtk_iso_gpio",
		.group_index = 1,
		/*160(predefine base)+64(intc_mux)+101(misc_gpio)*/
		.linux_irq_base = 325,
		/*Bit20, de-assert interrupt flag*/
		.gpio_isr_deassert_int = 0x00100000,
		/*Bit19, assert interrupt flag*/
		.gpio_isr_assert_int = 0x00080000,
		/*ISO_ISR*/
		.reg_isr_off = 0x0,
		/* ISO_UMSK_ISR_GPA0, UMSK_ISR_GPA1 */
		.reg_umsk_isr_gpa_off = {0x08, 0xe0},
		/* ISO_UMSK_ISR_GPDA0, UMSK_ISR_GPDA1 */
		.reg_umsk_isr_gpda_off = {0x0c, 0xe4},
		/* ISO_GPDIR, GPDIR_1 */
		.reg_dir_off = {0x00, 0x18},
		/* ISO_GPDATO, GPDATO_1 */
		.reg_dato_off = {0x04, 0x1c},
		/* ISO_GPDATI, GPDATI_1 */
		.reg_dati_off = {0x08, 0x20},
		/* ISO_GPIE, GPIE_1 */
		.reg_ie_off = {0x0c, 0x24},
		/* ISO_GPDP, GPDP_1 */
		.reg_dp_off = {0x10, 0x28},
		/*ISO_GPDEB*/
		.reg_deb_off = 0x14,
	}
};

static const u32 rtk_gpio_ngroups = ARRAY_SIZE(rtk_gpio_grps_array);

static u32 gpio_get_reg_offset(u32 group_index, u32 reg_type, u32 pin)
{
	u32 reg_index, reg_offset = UNKNOW_OFFSET;
	const struct rtk_gpio_groups *p_rtk_gpio_grp = NULL;

	if ((reg_type == GP_REG_UMSK_ISR_GPA) ||
		(reg_type == GP_REG_UMSK_ISR_GPDA))
		reg_index = GPIO_INT_REG_OFST(pin);
	else
		reg_index = GPIO_REG_OFST(pin);

	if (reg_index >= GPIO_REG_ARRAY_SIZE)
		return reg_offset;

	if (group_index < rtk_gpio_ngroups)
		p_rtk_gpio_grp = &rtk_gpio_grps_array[group_index];

	if (!p_rtk_gpio_grp)
		return reg_offset;

	switch (reg_type) {
	case GP_REG_UMSK_ISR_GPA:
		reg_offset = p_rtk_gpio_grp->reg_umsk_isr_gpa_off[reg_index];
		break;
	case GP_REG_UMSK_ISR_GPDA:
		reg_offset = p_rtk_gpio_grp->reg_umsk_isr_gpda_off[reg_index];
		break;
	case GP_REG_DIR:
		reg_offset = p_rtk_gpio_grp->reg_dir_off[reg_index];
		break;
	case GP_REG_DATO:
		reg_offset = p_rtk_gpio_grp->reg_dato_off[reg_index];
		break;
	case GP_REG_DATI:
		reg_offset = p_rtk_gpio_grp->reg_dati_off[reg_index];
		break;
	case GP_REG_IE:
		reg_offset = p_rtk_gpio_grp->reg_ie_off[reg_index];
		break;
	case GP_REG_DP:
		reg_offset = p_rtk_gpio_grp->reg_dp_off[reg_index];
		break;
	default:
		RTK_GPIO_DBG("[%s] Unknow type", __func__);
	}

	return reg_offset;
}

static inline void iowrite_reg_bit(void *reg,
				unsigned char bit, unsigned char val)
{
	if (val)
		writel(readl(reg) | (0x1 << bit), reg);
	else
		writel(readl(reg) & ~(0x1 << bit), reg);
}

#define ioread_reg_bit(reg, bits)    ((readl(reg) >> (bits)) & 0x1)
#define chip2controller(chip)	\
	container_of(chip, struct rtk_gpio_controller, chip)

int gpio_chk_irq_enable(struct rtk_gpio_controller *p_rtk_gpio_ctl, u32 irq)
{
	u32 ie_offset;

	RTK_GPIO_DBG("[%s] irq(%u)", __func__, irq);
	ie_offset = gpio_get_reg_offset(p_rtk_gpio_ctl->group_index,
					GP_REG_IE, irq);

	return ioread_reg_bit(((void *)(p_rtk_gpio_ctl->gpio_regs_base)
					+ ie_offset), GPIO_REG_BIT(irq));
}

static void gpio_irq_disable(struct irq_data *d)
{
	u32 ie_offset;
	struct rtk_gpio_controller *p_rtk_gpio_ctl =
			(struct rtk_gpio_controller *)(d->chip_data);

	RTK_GPIO_DBG("[%s] d->hwirq(%lu)", __func__, d->hwirq);

	ie_offset = gpio_get_reg_offset(p_rtk_gpio_ctl->group_index,
					GP_REG_IE, d->hwirq);

	iowrite_reg_bit(((void *)p_rtk_gpio_ctl->gpio_regs_base +
					ie_offset), GPIO_REG_BIT(d->hwirq), 0);
}

static void gpio_irq_enable(struct irq_data *d)
{
	struct rtk_gpio_controller *p_rtk_gpio_ctl =
				(struct rtk_gpio_controller *)(d->chip_data);
	unsigned long irq_flag;
	u32 gpa_offset, gpada_offset, ie_offset, gpio_int_flag;

	RTK_GPIO_DBG("[%s] irq number(%u), hwirq(%lu), group(%s)",
			__func__, d->irq, d->hwirq, d->domain->name);

	spin_lock_irqsave(&p_rtk_gpio_ctl->lock, irq_flag);
	gpio_int_flag = 0x1 << GPIO_INT_REG_BIT(d->hwirq);

	gpa_offset = gpio_get_reg_offset(p_rtk_gpio_ctl->group_index,
					GP_REG_UMSK_ISR_GPA, d->hwirq);
	gpada_offset = gpio_get_reg_offset(p_rtk_gpio_ctl->group_index,
					GP_REG_UMSK_ISR_GPDA, d->hwirq);
	ie_offset = gpio_get_reg_offset(p_rtk_gpio_ctl->group_index,
					GP_REG_IE, d->hwirq);

	if ((gpa_offset != UNKNOW_OFFSET) && (gpada_offset != UNKNOW_OFFSET)
		&& (ie_offset != UNKNOW_OFFSET)) {
		/*Clear assert interrupt flag*/
		if (readl(p_rtk_gpio_ctl->irq_regs_base+gpa_offset)
			& gpio_int_flag) {
			RTK_GPIO_DBG("[%s] Wrte Reg(0x%08llx) Val(0x%08x)",
				__func__,
				(u64)(p_rtk_gpio_ctl->irq_regs_base+gpa_offset),
				gpio_int_flag);
			writel(gpio_int_flag,
				p_rtk_gpio_ctl->irq_regs_base + gpa_offset);
		}

		/*Clear de-assert interrupt flag*/
		if (readl(p_rtk_gpio_ctl->irq_regs_base+gpada_offset)
			& gpio_int_flag) {
			RTK_GPIO_DBG("[%s] Wrte Reg(0x%08llx) Val(0x%08x)",
				__func__,
				(u64)(p_rtk_gpio_ctl->irq_regs_base+gpada_offset),
				gpio_int_flag);
			writel(gpio_int_flag,
				p_rtk_gpio_ctl->irq_regs_base + gpada_offset);
		}

		/*Enable interrupt*/
		iowrite_reg_bit(((void *)p_rtk_gpio_ctl->gpio_regs_base
				+ie_offset), GPIO_REG_BIT(d->hwirq), 1);
		RTK_GPIO_DBG("[%s] Reg_ie[0x%08llx]= 0x%08x", __func__,
			  (u64)(p_rtk_gpio_ctl->gpio_regs_base+ie_offset),
			  readl(p_rtk_gpio_ctl->gpio_regs_base+ie_offset));
	}
	spin_unlock_irqrestore(&p_rtk_gpio_ctl->lock, irq_flag);

}

static int gpio_irq_type(struct irq_data *d, unsigned int trigger)
{
	u32 dp_offset;

	struct rtk_gpio_controller *p_rtk_gpio_ctl =
		(struct rtk_gpio_controller *)(d->chip_data);

	dp_offset = gpio_get_reg_offset(p_rtk_gpio_ctl->group_index,
					GP_REG_DP, d->hwirq);

	switch (trigger) {
	case IRQ_TYPE_EDGE_RISING:
	case IRQ_TYPE_LEVEL_HIGH:
		RTK_GPIO_DBG("[%s] Pin(%lu) IRQ_TYPE_EDGE_RISING",
				__func__, d->hwirq);
		iowrite_reg_bit(((void *)p_rtk_gpio_ctl->gpio_regs_base
				+ dp_offset), GPIO_REG_BIT(d->hwirq), 1);
		clear_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_deassert_enable_flag[GPIO_REG_OFST(d->hwirq)]);
		set_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_assert_enable_flag[GPIO_REG_OFST(d->hwirq)]);
		break;

	case IRQ_TYPE_EDGE_FALLING:
	case IRQ_TYPE_LEVEL_LOW:
		RTK_GPIO_DBG("[%s] Pin(%lu) IRQ_TYPE_EDGE_FALLING", __func__, d->hwirq);
		iowrite_reg_bit(((void *)p_rtk_gpio_ctl->gpio_regs_base + dp_offset), GPIO_REG_BIT(d->hwirq), 0);
		clear_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_deassert_enable_flag[GPIO_REG_OFST(d->hwirq)]);
		set_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_assert_enable_flag[GPIO_REG_OFST(d->hwirq)]);
		break;

	case IRQ_TYPE_EDGE_BOTH:
	case IRQ_TYPE_NONE:
	default:
		RTK_GPIO_DBG("[%s] Pin(%lu) trigger(%u)", __func__, d->hwirq, trigger);
		iowrite_reg_bit(((void *)p_rtk_gpio_ctl->gpio_regs_base + dp_offset), GPIO_REG_BIT(d->hwirq), 1);
		set_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_deassert_enable_flag[GPIO_REG_OFST(d->hwirq)]);
		set_bit(GPIO_REG_BIT(d->hwirq),
			(unsigned long *)&p_rtk_gpio_ctl->gpio_isr_assert_enable_flag[GPIO_REG_OFST(d->hwirq)]);
		break;

	}

	return 0;

}

static void gpio_irq_handler(struct irq_desc *desc)
{
	struct rtk_gpio_controller *p_rtk_gpio_ctl;
	u32 gpada_offset, gpa_offset;
	u32 gpioNr, i;
	u32 event, status;
	u32 hw_irq = 12345678, linux_irq;
	u32 irq_had_fired = 0;

	RTK_GPIO_DBG("[%s]", __func__);

	p_rtk_gpio_ctl = (struct rtk_gpio_controller *)irq_desc_get_handler_data(desc);	/*rtk_gpio_controller for MISC or ISO*/

	/* Get interrupt status */
	event = readl(p_rtk_gpio_ctl->reg_isr) & (p_rtk_gpio_ctl->gpio_isr_deassert_int | p_rtk_gpio_ctl->gpio_isr_assert_int);
	RTK_GPIO_DBG("[%s] event(0x%08x)", __func__, event);
	if (event == 0)
		return;

	/* Handle gpio deassert */
	if (event & (p_rtk_gpio_ctl->gpio_isr_deassert_int)) {
		gpioNr = 0;
		RTK_GPIO_DBG("[%s] de-assert interrupt", __func__);
		while (gpioNr < (p_rtk_gpio_ctl->chip.ngpio)) {
			gpada_offset = gpio_get_reg_offset(p_rtk_gpio_ctl->group_index, GP_REG_UMSK_ISR_GPDA, gpioNr);

			status = readl(p_rtk_gpio_ctl->irq_regs_base + gpada_offset) >> 1;	/*get regs_umsk_isr_gpda0 or regs_umsk_isr_gpda1*/
			writel(status << 1, p_rtk_gpio_ctl->irq_regs_base + gpada_offset);

			i = gpioNr;
			while (status && i < (p_rtk_gpio_ctl->chip.ngpio)) {	/*i<MISC gpio number(60) or ISO gpio number(20)*/
				/*printk("status = %08x\n", status);*/
				if ((status & 0x1) && gpio_chk_irq_enable(p_rtk_gpio_ctl, i)) {
					hw_irq = i;
					linux_irq = irq_find_mapping(p_rtk_gpio_ctl->irq_mux_domain, hw_irq);
					if (linux_irq) {
						RTK_GPIO_DBG("[%s] line: %d", __func__, __LINE__);
						RTK_GPIO_DBG("hw_irq = %d,  deassertflg[0x%08llx] = %x", hw_irq, (u64)(&p_rtk_gpio_ctl->gpio_isr_deassert_enable_flag[GPIO_REG_OFST(hw_irq)]), p_rtk_gpio_ctl->gpio_isr_deassert_enable_flag[GPIO_REG_OFST(hw_irq)]);
						if ((1<<GPIO_REG_BIT(hw_irq)) & (p_rtk_gpio_ctl->gpio_isr_deassert_enable_flag[GPIO_REG_OFST(hw_irq)])) {
							generic_handle_irq(linux_irq);
							irq_had_fired++;
						}
					} else {
						pr_err("%s can not specified linux irq number for hwirq=%d .", __func__, hw_irq);
					}
				}
				i++;
				status >>= 1;
				RTK_GPIO_DBG("[%s] line: %d", __func__, __LINE__);
			}

			gpioNr += 31;
			RTK_GPIO_DBG("[%s] line: %d", __func__, __LINE__);
		}

	}

	RTK_GPIO_DBG("[%s] line: %d", __func__, __LINE__);

	/* Handle gpio assert */
	if (event & (p_rtk_gpio_ctl->gpio_isr_assert_int)) {
		gpioNr = 0;
		RTK_GPIO_DBG("[%s] assert interrupt", __func__);
		while (gpioNr < (p_rtk_gpio_ctl->chip.ngpio)) {
			gpa_offset = gpio_get_reg_offset(p_rtk_gpio_ctl->group_index, GP_REG_UMSK_ISR_GPA, gpioNr);

			status = readl(p_rtk_gpio_ctl->irq_regs_base + gpa_offset) >> 1;
			writel(status << 1, p_rtk_gpio_ctl->irq_regs_base + gpa_offset);

			i = gpioNr;
			while (status && i < (p_rtk_gpio_ctl->chip.ngpio)) {
				if ((status & 0x1) && gpio_chk_irq_enable(p_rtk_gpio_ctl, i)) {
					hw_irq = i;
					linux_irq = irq_find_mapping(p_rtk_gpio_ctl->irq_mux_domain, hw_irq);
					if (linux_irq) {
						RTK_GPIO_DBG("[%s] line: %d", __func__, __LINE__);
						RTK_GPIO_DBG("hw_irq = %d,  assertflg[0x%08llx] = %x", hw_irq, (u64)(&p_rtk_gpio_ctl->gpio_isr_assert_enable_flag[GPIO_REG_OFST(hw_irq)]), p_rtk_gpio_ctl->gpio_isr_assert_enable_flag[GPIO_REG_OFST(hw_irq)]);
						if ((1<<GPIO_REG_BIT(hw_irq)) & (p_rtk_gpio_ctl->gpio_isr_assert_enable_flag[GPIO_REG_OFST(hw_irq)])) {
							RTK_GPIO_DBG("[%s]%s  line: %d", __FILE__, __func__, __LINE__);
							generic_handle_irq(linux_irq);
							irq_had_fired++;
						}
					} else {
						pr_err("%s can not specified linux irq number for hwirq=%d .", __func__, hw_irq);
					}
				}
				i++;
				status >>= 1;
				RTK_GPIO_DBG("[%s] line: %d", __func__, __LINE__);
			}
			gpioNr += 31;
			RTK_GPIO_DBG("[%s] line: %d", __func__, __LINE__);
		}
	}


	RTK_GPIO_DBG("[%s] irq_had_fired = %d", __func__, irq_had_fired);
	writel(event, p_rtk_gpio_ctl->reg_isr);
	if (!irq_had_fired)
		RTK_GPIO_DBG("%s gpio irq(hwirq=%d) has triggered but no dispatch",
				__func__, hw_irq);
		RTK_GPIO_DBG("to user handler (12345678 mean something Wrong)");
	return;

}

static __maybe_unused int
	mux_irq_domain_xlate(struct irq_domain *d,
		struct device_node *controller, const u32 *intspec, u32 intsize,
		unsigned long *out_hwirq, u32 *out_type)
{
	RTK_GPIO_DBG("[%s] device_node.name = %s", __func__, controller->name);

	if (/*d->of_node*/to_of_node(d->fwnode) != controller)
		return -EINVAL;

	if (intsize < 1)
		return -EINVAL;

	*out_hwirq = intspec[0];
	*out_type = 0;
	RTK_GPIO_DBG("[%s] out_hwirq = %ld", __func__, *out_hwirq);
	return 0;
}


static int mux_irq_domain_map(struct irq_domain *d, u32 irq, irq_hw_number_t hw)
{
	struct rtk_gpio_controller *p_rtk_gpio_ctl = d->host_data;

	RTK_GPIO_DBG("[%s] irq=%d , irq_hw_number=%d", __func__, irq, (u32)hw);

	if (!p_rtk_gpio_ctl) {
		RTK_GPIO_DBG("[%s] p_rtk_gpio_ctl is NULL", __func__);
		return -EINVAL;
	}

	irq_set_chip(irq, &p_rtk_gpio_ctl->gp_irq_chip);
	irq_set_chip_data(irq, (__force void *)p_rtk_gpio_ctl);
	irq_set_handler_data(irq, p_rtk_gpio_ctl);
	irq_set_handler(irq, handle_simple_irq);
	//set_irq_flags(irq, IRQF_VALID);

	return 0;
}

static const struct irq_domain_ops mux_irq_domain_ops = {
	.xlate = mux_irq_domain_xlate,
	.map = mux_irq_domain_map,
};

int rtk_gpio_irq_setup(struct device_node *node,
	struct rtk_gpio_controller *p_rtk_gpio_ctl,
	const struct rtk_gpio_groups *p_rtk_gpio_grp)
{
	unsigned int bank_deassert_irq, bank_assert_irq;

	RTK_GPIO_DBG("[%s]", __func__);

	p_rtk_gpio_ctl->gp_irq_chip.name = node->name;
	p_rtk_gpio_ctl->gp_irq_chip.irq_enable = gpio_irq_enable;
	p_rtk_gpio_ctl->gp_irq_chip.irq_disable = gpio_irq_disable;
	p_rtk_gpio_ctl->gp_irq_chip.irq_set_type = gpio_irq_type;
	p_rtk_gpio_ctl->gp_irq_chip.flags = IRQCHIP_SET_TYPE_MASKED;

	bank_assert_irq = irq_of_parse_and_map(node, 0);
	if (!bank_assert_irq) {
		pr_alert("[GPIO] Fail to parse of irq.\n");
		return -ENXIO;
	}

	bank_deassert_irq = irq_of_parse_and_map(node, 1);
	if (!bank_deassert_irq) {
		pr_alert("[GPIO] Fail to parse of irq.\n");
		return -ENXIO;
	}

	p_rtk_gpio_ctl->bank_assert_irq = bank_assert_irq;
	p_rtk_gpio_ctl->bank_deassert_irq = bank_deassert_irq;
	RTK_GPIO_DBG("[%s] bank_assert_irq=%d", __func__,
			p_rtk_gpio_ctl->bank_assert_irq);
	RTK_GPIO_DBG("[%s] bank_deassert_irq=%d", __func__,
			p_rtk_gpio_ctl->bank_deassert_irq);

	p_rtk_gpio_ctl->irq_mux_domain = irq_domain_add_simple(node,
			p_rtk_gpio_ctl->chip.ngpio,
			p_rtk_gpio_ctl->linux_irq_base,
			&mux_irq_domain_ops, p_rtk_gpio_ctl);

	WARN(!p_rtk_gpio_ctl->irq_mux_domain, "IRQ domain init failed\n");

	irq_set_chained_handler(p_rtk_gpio_ctl->bank_deassert_irq,
				(irq_flow_handler_t)gpio_irq_handler);
	irq_set_handler_data(p_rtk_gpio_ctl->bank_deassert_irq, p_rtk_gpio_ctl);

	irq_set_chained_handler(p_rtk_gpio_ctl->bank_assert_irq,
				(irq_flow_handler_t)gpio_irq_handler);
	irq_set_handler_data(p_rtk_gpio_ctl->bank_assert_irq, p_rtk_gpio_ctl);
	return 0;
}

static inline int __rtk_gpio_direction(struct gpio_chip *chip,
	unsigned int offset, bool out)
{
	u32 dir_offset;
	struct rtk_gpio_controller *p_rtk_gpio_ctl = chip2controller(chip);
	unsigned long flags;
	u32 temp;
	u32 mask = 1 << (offset % 32);

	RTK_GPIO_DBG("[%s] offset(%u) out(%u)", __func__, offset, out);

	dir_offset = gpio_get_reg_offset(p_rtk_gpio_ctl->group_index,
					GP_REG_DIR, offset);

	spin_lock_irqsave(&p_rtk_gpio_ctl->lock, flags);
	temp = __raw_readl((p_rtk_gpio_ctl->gpio_regs_base) + dir_offset);
	if (out)
		temp |= mask;
	else
		temp &= ~mask;

	__raw_writel(temp, (p_rtk_gpio_ctl->gpio_regs_base) + dir_offset);
	RTK_GPIO_DBG("[%s] offset(%u)  addr(0x%08llx)  temp(0x%08x)",
			__func__, offset,
			(u64)((p_rtk_gpio_ctl->gpio_regs_base) + dir_offset),
			temp);
	spin_unlock_irqrestore(&p_rtk_gpio_ctl->lock, flags);

	return 0;
}

static int rtk_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	u32 dati_offset, dato_offset, dir_offset;
	u32 temp, value;
	u32 mask = 1 << (offset % 32);
	struct rtk_gpio_controller *p_rtk_gpio_ctl = chip2controller(chip);

	RTK_GPIO_DBG("[%s] offset(%u)", __func__, offset);

	dir_offset = gpio_get_reg_offset(p_rtk_gpio_ctl->group_index,
					GP_REG_DIR, offset);
	temp = __raw_readl((p_rtk_gpio_ctl->gpio_regs_base) + dir_offset);
	if (temp & mask) {  /*direction out*/
		dato_offset = gpio_get_reg_offset(p_rtk_gpio_ctl->group_index,
						GP_REG_DATO, offset);
		value = ioread_reg_bit(((void *)p_rtk_gpio_ctl->gpio_regs_base +
					dato_offset), GPIO_REG_BIT(offset));
	} else {  /*direction in*/
		dati_offset = gpio_get_reg_offset(p_rtk_gpio_ctl->group_index,
						GP_REG_DATI, offset);
		value = ioread_reg_bit(((void *)p_rtk_gpio_ctl->gpio_regs_base +
					dati_offset), GPIO_REG_BIT(offset));
	}

	return value;
}

static void rtk_gpio_set(struct gpio_chip *chip, unsigned int offset, int value)
{
	u32 dato_offset;
	struct rtk_gpio_controller *p_rtk_gpio_ctl = chip2controller(chip);

	RTK_GPIO_DBG("[%s] offset(%u) value(%d)", __func__, offset, value);

	dato_offset = gpio_get_reg_offset(p_rtk_gpio_ctl->group_index,
					GP_REG_DATO, offset);

	if (value)
		iowrite_reg_bit(((void *)p_rtk_gpio_ctl->gpio_regs_base + dato_offset),
				GPIO_REG_BIT(offset), 1);
	else
		iowrite_reg_bit(((void *)p_rtk_gpio_ctl->gpio_regs_base + dato_offset),
				GPIO_REG_BIT(offset), 0);
}

static int rtk_gpio_direction_in(struct gpio_chip *chip, unsigned int offset)
{
	RTK_GPIO_DBG("[%s] offset(%u)", __func__, offset);

	return __rtk_gpio_direction(chip, offset, GP_DIRIN);
}

static int rtk_gpio_direction_out(struct gpio_chip *chip,
			unsigned int offset, int value)
{
	RTK_GPIO_DBG("[%s] offset(%u) value(%d)",
			__func__, offset, value);

	rtk_gpio_set(chip, offset, value);
	return __rtk_gpio_direction(chip, offset, GP_DIROUT);
}

static int rtk_gpio_get_direction(struct gpio_chip *chip, unsigned int offset)
{
	u32 dir_offset;
	u32 temp, dir;
	u32 mask = 1 << (offset % 32);
	struct rtk_gpio_controller *p_rtk_gpio_ctl = chip2controller(chip);

	RTK_GPIO_DBG("[%s] offset(%u)\n", __func__, offset);

	dir_offset = gpio_get_reg_offset(p_rtk_gpio_ctl->group_index, GP_REG_DIR, offset);
	temp = __raw_readl((p_rtk_gpio_ctl->gpio_regs_base) + dir_offset);
	dir = (temp & mask) ? 0 : 1;

	return dir;
}


static int rtk_gpio_setdeb(struct gpio_chip *chip,
	unsigned int offset, unsigned int debounce/*microsecond(us)*/)
{
	struct rtk_gpio_controller *p_rtk_gpio_ctl = chip2controller(chip);

	RTK_GPIO_DBG("[%s] offset(%u) debounce(%d)",
			__func__, offset, debounce);

	if (debounce >= 30*1000) {//30ms
		debounce = RTK_GPIO_DEBOUNCE_30ms;
	} else if (debounce >= 20*1000) {//20ms
		debounce = RTK_GPIO_DEBOUNCE_20ms;
	} else if (debounce >= 10*1000) {//10ms
		debounce = RTK_GPIO_DEBOUNCE_10ms;
	} else if (debounce >= 1000) {// 1ms
		debounce = RTK_GPIO_DEBOUNCE_1ms;
	} else if (debounce >= 100) {// 100us
		debounce = RTK_GPIO_DEBOUNCE_100us;
	} else {
		debounce = RTK_GPIO_DEBOUNCE_10us;
	}

	if (strcmp("rtk_misc_gpio", chip->label) == 0) {
		writel((0x8 | debounce) << ((offset >> 4) * 4),
			((void *)p_rtk_gpio_ctl->reg_deb));
		return 0;
	} else if (strcmp("rtk_iso_gpio", chip->label) == 0) {
		writel((0x8 | debounce),
			((void *)p_rtk_gpio_ctl->reg_deb));
		return 0;
	}
	RTK_GPIO_DBG("[%s] Fail", __func__);
	return -EINVAL;
}

static int rtk_gpio_request(struct gpio_chip *chip, unsigned int offset)
{
	RTK_GPIO_DBG("[%s] offset(%u)", __func__, offset);

	return pinctrl_request_gpio(chip->base + offset);
}

static void rtk_gpio_free(struct gpio_chip *chip, unsigned int offset)
{
	RTK_GPIO_DBG("[%s] offset(%u)", __func__, offset);

	pinctrl_free_gpio(chip->base + offset);
}

static int rtk_gpio_to_irq(struct gpio_chip *chip, unsigned int offset)
{
	struct rtk_gpio_controller *p_rtk_gpio_ctl = chip2controller(chip);
	u32 linux_irq = 0;

	linux_irq = irq_create_mapping(p_rtk_gpio_ctl->irq_mux_domain, offset);
	RTK_GPIO_DBG("[%s] offset(%u) linux_irq(%u)",
			__func__, offset, linux_irq);

	if (!linux_irq) {
		pr_err("%s can not specified linux irq number for hwirq=%d .\n",
			__func__, offset);
		return -EINVAL;
	}
	return linux_irq;
}

static int rtk_gpio_xlate(struct gpio_chip *gc,
	const struct of_phandle_args *gpiospec, u32 *flags)
{
	u32 pin;

	RTK_GPIO_DBG("[%s] base(%d), args[0]=%d",
			__func__, gc->base, gpiospec->args[0]);

	if (WARN_ON(gc->of_gpio_n_cells < 1))
		return -EINVAL;

	if (WARN_ON(gpiospec->args_count < gc->of_gpio_n_cells))
		return -EINVAL;

	if (gpiospec->args[0] > gc->ngpio)
		return -EINVAL;

	pin = gpiospec->args[0];

	if (gpiospec->args[1] == GP_DIRIN) {	//gpio direction input
		if (rtk_gpio_direction_in(gc, pin))
			pr_err("gpio_xlate: failed to set pin direction in\n");

		if (flags)//low active flag
			*flags = gpiospec->args[2];
	} else {
		if (gpiospec->args[2] == GP_LOW) {
			/*gpio direction output low*/
			if (rtk_gpio_direction_out(gc, pin, GP_LOW))
				pr_err("gpio_xlate: failed to set pin direction out\n");
		} else if (gpiospec->args[2] == GP_HIGH) {
			/*gpio direction output high*/
			if (rtk_gpio_direction_out(gc, pin, GP_HIGH))
				pr_err("gpio_xlate: failed to set pin direction out\n");
		} else {
			pr_err("gpio_xlate: failed to set pin direction out\n");
		}
	}

	return gpiospec->args[0];
}

void set_default_gpio(struct device_node *node)
{
	int num_gpios, n;

	num_gpios = of_gpio_count(node);
	if (num_gpios > 0) {
		for (n = 0; n < num_gpios; n++) {
			int gpio = of_get_gpio_flags(node, n, NULL);

			RTK_GPIO_DBG("[%s]  %s  line: %d",
					__FILE__, __func__, __LINE__);
			if (gpio >= 0) {
				if (!gpio_is_valid(gpio))
					pr_err("[GPIO] %s: gpio %d is not valid\n",
						__func__, gpio);

				if (gpio_request(gpio, node->name))
					pr_err("[GPIO] %s: gpio %d is in use\n",
						__func__, gpio);

				gpio_free(gpio);
			} else {
				pr_err("[GPIO] %s: Could not get gpio from of\n",
					__func__);
			}
		}
	} else {
		RTK_GPIO_INF("No default gpio need to set");
	}
}

static const struct of_device_id rtk_gpio_of_match[] = {
	{.compatible = "realtek,rtk-misc-gpio-irq-mux",},
	{.compatible = "realtek,rtk-iso-gpio-irq-mux",},
	{ /* Sentinel */ },
};

static int rtk_gpio_probe(struct platform_device *pdev)
{
	int i;
	void __iomem *irq_regs_base;
	void __iomem *gpio_regs_base;
	struct rtk_gpio_controller *p_rtk_gpio_ctl;
	const struct rtk_gpio_groups *p_rtk_gpio_grp = NULL;
	u32 gpio_numbers;
	u32 gpio_base;
	struct device_node *node = NULL;

	RTK_GPIO_DBG("[%s]", __func__);
	node = pdev->dev.of_node;
	if (!node) {
		pr_err("rtk gpio: failed to allocate device structure.\n");
		return -ENODEV;
	}

	RTK_GPIO_DBG("[%s] node name = [%s]", __func__, node->name);

	p_rtk_gpio_ctl =
		kzalloc(sizeof(struct rtk_gpio_controller), GFP_KERNEL);
	if (!p_rtk_gpio_ctl) {
		pr_err("rtk gpio: failed to allocate device structure.\n");
		return -ENOMEM;
	}
	memset(p_rtk_gpio_ctl, 0, sizeof(struct rtk_gpio_groups));

	if (of_property_read_u32_array(node, "Realtek,gpio_numbers",
		&gpio_numbers, 1)) {
		pr_err("Don't know gpio group number.\n");
		return -EINVAL;
	}

	if (of_property_read_u32_index(node, "Realtek,gpio_base",
		0, &gpio_base)) {
		pr_err("Don't know gpio group number.\n");
		return -EINVAL;
	}

	for (i = 0; i < rtk_gpio_ngroups; i++) {
		if (strcmp(rtk_gpio_grps_array[i].group_name, node->name) == 0)
			p_rtk_gpio_grp = &rtk_gpio_grps_array[i];
	}

	if (!p_rtk_gpio_grp) {
		pr_err("Don't know gpio group name.\n");
		return -EINVAL;
	}

	p_rtk_gpio_ctl->chip.label = node->name;
	p_rtk_gpio_ctl->chip.request = rtk_gpio_request;
	p_rtk_gpio_ctl->chip.free = rtk_gpio_free;
	p_rtk_gpio_ctl->chip.direction_input = rtk_gpio_direction_in;
	p_rtk_gpio_ctl->chip.get = rtk_gpio_get;
	p_rtk_gpio_ctl->chip.get_direction= rtk_gpio_get_direction;
	p_rtk_gpio_ctl->chip.direction_output = rtk_gpio_direction_out;
	p_rtk_gpio_ctl->chip.set = rtk_gpio_set;
	p_rtk_gpio_ctl->chip.set_debounce = rtk_gpio_setdeb;
	p_rtk_gpio_ctl->chip.to_irq = rtk_gpio_to_irq;
	p_rtk_gpio_ctl->chip.base = gpio_base;
	p_rtk_gpio_ctl->chip.ngpio = gpio_numbers;
	/*must be the same with     #gpio-cells = <> in dtb*/
	p_rtk_gpio_ctl->chip.of_gpio_n_cells = 3;
	p_rtk_gpio_ctl->chip.of_xlate = rtk_gpio_xlate;
	p_rtk_gpio_ctl->chip.of_node = node;

	spin_lock_init(&p_rtk_gpio_ctl->lock);

	irq_regs_base = of_iomap(node, 0);
	if (!irq_regs_base) {
		pr_err("unable to map irq_regs_base registers\n");
		return -EINVAL;
	}

	gpio_regs_base = of_iomap(node, 1);
	if (!gpio_regs_base) {
		pr_err("unable to map gpio_regs_base registers\n");
		return -EINVAL;
	}

	p_rtk_gpio_ctl->gpio_isr_deassert_int =
				p_rtk_gpio_grp->gpio_isr_deassert_int;
	p_rtk_gpio_ctl->gpio_isr_assert_int =
				p_rtk_gpio_grp->gpio_isr_assert_int;
	p_rtk_gpio_ctl->linux_irq_base = p_rtk_gpio_grp->linux_irq_base;

	p_rtk_gpio_ctl->group_index = p_rtk_gpio_grp->group_index;
	p_rtk_gpio_ctl->irq_regs_base = (void __iomem *)irq_regs_base;
	p_rtk_gpio_ctl->gpio_regs_base = (void __iomem *)gpio_regs_base;
	p_rtk_gpio_ctl->reg_isr = (void __iomem *)irq_regs_base +
					p_rtk_gpio_grp->reg_isr_off;
	p_rtk_gpio_ctl->reg_deb = (void __iomem *)gpio_regs_base +
					p_rtk_gpio_grp->reg_deb_off;

	if (gpiochip_add(&p_rtk_gpio_ctl->chip))
		pr_info("[%s]  %s  line: %d\n", __FILE__, __func__, __LINE__);


	rtk_gpio_irq_setup(node, p_rtk_gpio_ctl, p_rtk_gpio_grp);

	platform_set_drvdata(pdev, p_rtk_gpio_ctl);

	/* Initial default gpios */
	set_default_gpio(node);

	return 0;
}

static int rtk_gpio_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct rtk_gpio_controller *p_rtk_gpio_ctl;

	p_rtk_gpio_ctl = platform_get_drvdata(pdev);

#ifdef CONFIG_RTK_XEN_SUPPORT
	if (xen_domain() && !xen_initial_domain()) {
		printk(KERN_INFO "[GPIO] skip %s in DomU, label(%s)\n", __func__, p_rtk_gpio_ctl->chip.label);
		return 0;
	}
#endif

	pr_info("[GPIO] Enter %s, label(%s)\n",
		__func__, p_rtk_gpio_ctl->chip.label);

	disable_irq(p_rtk_gpio_ctl->bank_assert_irq);
	disable_irq(p_rtk_gpio_ctl->bank_deassert_irq);

	pr_info("[GPIO] Exit %s\n", __func__);

	return 0;
}

static int rtk_gpio_resume(struct platform_device *pdev)
{
	struct rtk_gpio_controller *p_rtk_gpio_ctl;
	struct device_node *node;

	p_rtk_gpio_ctl = platform_get_drvdata(pdev);
	node = p_rtk_gpio_ctl->chip.of_node;

#ifdef CONFIG_RTK_XEN_SUPPORT
	if (xen_domain() && !xen_initial_domain()) {
		printk(KERN_INFO "[GPIO] skip %s in DomU, label(%s)\n", __func__, p_rtk_gpio_ctl->chip.label);
		return 0;
	}
#endif

	pr_info("[GPIO] Enter %s, label(%s)\n",
		__func__, p_rtk_gpio_ctl->chip.label);

	/* Initial default gpios */
	set_default_gpio(node);

	enable_irq(p_rtk_gpio_ctl->bank_assert_irq);
	enable_irq(p_rtk_gpio_ctl->bank_deassert_irq);

	pr_info("[GPIO] Exit %s\n", __func__);

	return 0;
}

static struct platform_driver rtk_gpio_driver = {
	.driver = {
			   .name = "rtk_gpio",
			   .owner = THIS_MODULE,
			   .of_match_table = rtk_gpio_of_match,
			   },
	.probe = rtk_gpio_probe,
	.suspend = rtk_gpio_suspend,
	.resume = rtk_gpio_resume,
};

static int rtk_gpio_drv_reg(void)
{
	return platform_driver_register(&rtk_gpio_driver);
}

postcore_initcall(rtk_gpio_drv_reg);
