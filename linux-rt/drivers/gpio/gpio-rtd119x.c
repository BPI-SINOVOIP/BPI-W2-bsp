//#include <asm/mach/irq.h>

#include <linux/gpio.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/io.h>

//#include <asm/mach/irq.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>

//#include <linux/irqdomain.h>
#include <linux/irqchip/chained_irq.h>
#include <linux/slab.h>
#include <linux/interrupt.h>

#include <linux/pinctrl/consumer.h>

#include <linux/of_device.h>
#include <linux/platform_device.h>

//#include <linux/of.h>
#include <linux/of_gpio.h>

#include "gpio-rtd119x.h"

#define GPIO_REG_OFST(id)       ((id >> 5)<<2)
#define GPIO_REG_BIT(id)        (id & 0x1F)	// reg bit = id % 32
#define GPIO_INT_REG_OFST(id)   ((id/31)<<2)
#define GPIO_INT_REG_BIT(id)    ((id%31)+1)

/*TODO :
 intc mux tempary define the first irq number in this mux is 160, end in 160+63
 misc gpio int mux tempary define the first irq number in this mux is 160+64 , end in 160+64+59
 iso gpio int mux tempary define the first irq number in this mux is 160+64+60 , end in 160+64+60+19*/
static const struct rtk119x_gpio_groups rtk_gpio_grps_array[] = {
	{
		.group_name = "rtk_misc_gpio",
		.linux_irq_base = 224,//160(predefine base)+64(intc_mux)
		.gpio_isr_deassert_offset = 0x00100000,	//Bit20
		.gpio_isr_assert_offset = 0x00080000,	//Bit19
		.reg_isr_off = 0xc,						//MIS_ISR
		.reg_umsk_isr_gpa_off = 0x40,			//MIS_UMSK_ISR_GP0A
		.reg_umsk_isr_gpda_off = 0x54,			//MIS_UMSK_ISR_GP0DA
		.reg_dir_off = 0x0,		//MIS_GP0DIR
		.reg_dato_off = 0x10,	//MIS_GP0DATO
		.reg_dati_off = 0x20,	//MIS_GP0DATI
		.reg_ie_off = 0x30,		//MIS_GP0IE
		.reg_dp_off = 0x40,		//MIS_GP0DP
		.reg_deb_off = 0x50,	//MIS_GPDEB
	},
	{
		.group_name = "rtk_iso_gpio",
#ifndef CONFIG_MACH_RTK1192
		.linux_irq_base = 284,//160(predefine base)+64(intc_mux)+60(misc_gpio)
#else
		.linux_irq_base = 327,//160(predefine base)+64(intc_mux)+103(misc_gpio)
#endif
		.gpio_isr_deassert_offset = 0x00100000,	//Bit20
		.gpio_isr_assert_offset = 0x00080000,	//Bit19
		.reg_isr_off = 0x0,						//ISO_ISR
		.reg_umsk_isr_gpa_off = 0x8,			//ISO_UMSK_ISR_GPA
		.reg_umsk_isr_gpda_off = 0xc,			//ISO_UMSK_ISR_GPDA
		.reg_dir_off = 0x0,		//ISO_GPDIR
		.reg_dato_off = 0x4,	//ISO_GPDATO
		.reg_dati_off = 0x8,	//ISO_GPDATI
		.reg_ie_off = 0xc,		//ISO_GPIE
		.reg_dp_off = 0x10,		//ISO_GPDP
		.reg_deb_off = 0x14,	//ISO_GPDEB
	 }
};

static const struct rtk119x_gpio_desc rtk_gpio_desc = {
	.groups = rtk_gpio_grps_array,
	.ngroups = ARRAY_SIZE(rtk_gpio_grps_array)
};

static void __inline iowrite_reg_bit(volatile void *reg, unsigned char bit, unsigned char val)
{
	if (val)
		iowrite32(ioread32(reg) | (0x1 << bit), reg);
	else
		iowrite32(ioread32(reg) & ~(0x1 << bit), reg);
}

#define ioread_reg_bit(reg, bits)    ((ioread32(reg) >> (bits)) & 0x1)
#define chip2controller(chip)	container_of(chip, struct rtk119x_gpio_controller, chip)

int gpio_chk_irq_enable(struct rtk119x_gpio_controller *p_rtk_gpio_ctl, unsigned int irq)
{
	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);

	return ioread_reg_bit(((volatile void *)(p_rtk_gpio_ctl->reg_ie) + GPIO_REG_OFST(irq)), GPIO_REG_BIT(irq));
}

static void gpio_irq_disable(struct irq_data *d)
{
	struct rtk119x_gpio_controller *p_rtk_gpio_ctl = (struct rtk119x_gpio_controller *)(d->chip_data);
	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);

	iowrite_reg_bit(((volatile void *)p_rtk_gpio_ctl->reg_ie + GPIO_REG_OFST(d->hwirq)), GPIO_REG_BIT(d->hwirq), 0);
}

static void gpio_irq_enable(struct irq_data *d)
{
	struct rtk119x_gpio_controller *p_rtk_gpio_ctl = (struct rtk119x_gpio_controller *)(d->chip_data);
    unsigned long irq_flag;
    unsigned int gpio_int_flag;
    RTK_debug("[%s]  %s  line: %d  irq=%d ,hwirq=%ld  ,of_node->name=%s \n", __FILE__, __FUNCTION__, __LINE__, d->irq, d->hwirq,
            d->domain->of_node->name);

    spin_lock_irqsave(&p_rtk_gpio_ctl->lock, irq_flag);
    //Clear assert/de-assert interrupt flag
    gpio_int_flag = 0x1 << GPIO_INT_REG_BIT(d->hwirq);
    if(ioread32(p_rtk_gpio_ctl->regs_umsk_isr_gpa+GPIO_INT_REG_OFST(d->hwirq))&gpio_int_flag)
    {
        RTK_debug("[%s]  %s  line: %d, Wrte Reg(0x%08x) Val(0x%08x)\n",__FILE__, __FUNCTION__, __LINE__,p_rtk_gpio_ctl->regs_umsk_isr_gpa+GPIO_INT_REG_OFST(d->hwirq),gpio_int_flag);
        iowrite32(gpio_int_flag,p_rtk_gpio_ctl->regs_umsk_isr_gpa+GPIO_INT_REG_OFST(d->hwirq));
    }
    if(ioread32(p_rtk_gpio_ctl->regs_umsk_isr_gpda+GPIO_INT_REG_OFST(d->hwirq))&gpio_int_flag)
    {
        RTK_debug("[%s]  %s  line: %d, Wrte Reg(0x%08x) Val(0x%08x)\n",__FILE__, __FUNCTION__, __LINE__,p_rtk_gpio_ctl->regs_umsk_isr_gpda+GPIO_INT_REG_OFST(d->hwirq),gpio_int_flag);
        iowrite32(gpio_int_flag,p_rtk_gpio_ctl->regs_umsk_isr_gpda+GPIO_INT_REG_OFST(d->hwirq));
    }

    //Enable interrupt
    iowrite_reg_bit(((volatile void *)p_rtk_gpio_ctl->reg_ie + GPIO_REG_OFST(d->hwirq)), GPIO_REG_BIT(d->hwirq), 1);
    spin_unlock_irqrestore(&p_rtk_gpio_ctl->lock, irq_flag);

	RTK_debug("[%s]  %s  line: %d  reg_ie[%x]= %x \n", __FILE__, __FUNCTION__, __LINE__,
			  (unsigned int)(p_rtk_gpio_ctl->reg_ie + GPIO_REG_OFST(d->hwirq)),
			  ioread32(p_rtk_gpio_ctl->reg_ie + GPIO_REG_OFST(d->hwirq)));
}

static int gpio_irq_type(struct irq_data *d, unsigned trigger)
{
	struct rtk119x_gpio_controller *p_rtk_gpio_ctl = (struct rtk119x_gpio_controller *)(d->chip_data);
	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);
	switch(trigger)
	{
		case IRQ_TYPE_EDGE_RISING://	1
		RTK_debug("[%s]%sline: %d \n",__FILE__,__FUNCTION__,__LINE__);
		iowrite_reg_bit(((volatile void *)p_rtk_gpio_ctl->reg_dp + GPIO_REG_OFST(d->hwirq)), GPIO_REG_BIT(d->hwirq), 1); 
		clear_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_deassert_enable_flag + GPIO_REG_OFST(d->hwirq));
		set_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_assert_enable_flag + GPIO_REG_OFST(d->hwirq));
		break;

		case IRQ_TYPE_EDGE_FALLING://	2
		RTK_debug("[%s]%sline: %d \n",__FILE__,__FUNCTION__,__LINE__);
		iowrite_reg_bit(((volatile void *)p_rtk_gpio_ctl->reg_dp + GPIO_REG_OFST(d->hwirq)), GPIO_REG_BIT(d->hwirq), 1); 
		set_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_deassert_enable_flag + GPIO_REG_OFST(d->hwirq));
		clear_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_assert_enable_flag + GPIO_REG_OFST(d->hwirq));
		break;

		case IRQ_TYPE_LEVEL_HIGH://	4
		RTK_debug("[%s]%sline: %d \n",__FILE__,__FUNCTION__,__LINE__);
		iowrite_reg_bit(((volatile void *)p_rtk_gpio_ctl->reg_dp + GPIO_REG_OFST(d->hwirq)), GPIO_REG_BIT(d->hwirq), 1); 
		clear_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_deassert_enable_flag + GPIO_REG_OFST(d->hwirq));
		set_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_assert_enable_flag + GPIO_REG_OFST(d->hwirq));
		break;

		case IRQ_TYPE_LEVEL_LOW://	8
		RTK_debug("[%s]%sline: %d \n",__FILE__,__FUNCTION__,__LINE__);
		iowrite_reg_bit(((volatile void *)p_rtk_gpio_ctl->reg_dp + GPIO_REG_OFST(d->hwirq)), GPIO_REG_BIT(d->hwirq), 0); 
		clear_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_deassert_enable_flag + GPIO_REG_OFST(d->hwirq));
		set_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_assert_enable_flag + GPIO_REG_OFST(d->hwirq));
		break;

		case IRQ_TYPE_EDGE_BOTH://	(IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING)
		case IRQ_TYPE_NONE:	//		0
		default:
		RTK_debug("[%s]%sline: %d \n",__FILE__,__FUNCTION__,__LINE__);
		iowrite_reg_bit(((volatile void *)p_rtk_gpio_ctl->reg_dp + GPIO_REG_OFST(d->hwirq)), GPIO_REG_BIT(d->hwirq), 1); 
		set_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_deassert_enable_flag + GPIO_REG_OFST(d->hwirq));
		set_bit(GPIO_REG_BIT(d->hwirq), (unsigned long *)&p_rtk_gpio_ctl->gpio_isr_assert_enable_flag + GPIO_REG_OFST(d->hwirq));
		break;

	}

	return 0;

}

static void gpio_irq_handler(unsigned irq, struct irq_desc *desc)
{
	struct rtk119x_gpio_controller *p_rtk_gpio_ctl;

//  struct irq_chip *chip = irq_get_chip(irq);
	unsigned int gpioNr, reg_ofst, i;
	unsigned int event;
	unsigned int status;
//  unsigned int mux_irq;
	unsigned int hw_irq=12345678, linux_irq;
	unsigned int irq_had_fired = 0 ;

	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);

#if 0
//gpio test start
	mux_irq = 60 + 15;
	generic_handle_irq(irq_find_mapping(irq_mux_domain, mux_irq));
	return;
//gpio test end
#endif

	p_rtk_gpio_ctl = (struct rtk119x_gpio_controller *)irq_desc_get_handler_data(desc);	//rtk119x_gpio_controller for MISC or ISO
//  chained_irq_enter(chip, desc);

	/*get interrupt status */
	event = ioread32(p_rtk_gpio_ctl->reg_isr) & (p_rtk_gpio_ctl->gpio_isr_deassert_offset | p_rtk_gpio_ctl->gpio_isr_assert_offset);
	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);
	if (event == 0)
		return;

	/*handle gpio deassert */
	if (event & (p_rtk_gpio_ctl->gpio_isr_deassert_offset))
	{
		gpioNr = 0;
		reg_ofst = 0;
		RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);
		while (gpioNr < (p_rtk_gpio_ctl->chip.ngpio))	//less than MISC gpio number(60) or ISO gpio number(20)
		{
			status = ioread32(p_rtk_gpio_ctl->regs_umsk_isr_gpda + reg_ofst) >> 1;	//get regs_umsk_isr_gpda0 or regs_umsk_isr_gpda1
			iowrite32(status << 1, p_rtk_gpio_ctl->regs_umsk_isr_gpda + reg_ofst);

			i = gpioNr;
			while (status && i < (p_rtk_gpio_ctl->chip.ngpio))	//    i<MISC gpio number(60) or ISO gpio number(20)
			{
				//printk("status = %08x\n", status);
				if ((status & 0x1) && gpio_chk_irq_enable(p_rtk_gpio_ctl, i))
				{
					/*
					   mux_irq = p_rtk_gpio_ctl->chip.base + i;                         //d->chip.base = 0 for MISC,  d->chip.base = 60 for ISO
					   generic_handle_irq(irq_find_mapping(p_rtk_gpio_ctl->irq_mux_domain, mux_irq));
					 */
					hw_irq = i;
					linux_irq = irq_find_mapping(p_rtk_gpio_ctl->irq_mux_domain, hw_irq);
					if (linux_irq)
					{
						RTK_debug("[%s]%s  line: %d \n",__FILE__,__FUNCTION__,__LINE__);
						RTK_debug("hw_irq = %d,  deassertflg[%x] = %x \n",hw_irq,((unsigned int)((p_rtk_gpio_ctl->gpio_isr_deassert_enable_flag) + GPIO_REG_OFST(hw_irq))), (*((p_rtk_gpio_ctl->gpio_isr_deassert_enable_flag) + GPIO_REG_OFST(hw_irq))));
						if ( (1<<GPIO_REG_BIT(hw_irq)) & (*((p_rtk_gpio_ctl->gpio_isr_deassert_enable_flag) + GPIO_REG_OFST(hw_irq)))  )
						{
							generic_handle_irq(linux_irq);
							irq_had_fired++;
						}
					}
					else
					{
						printk(KERN_ERR "%s can not specified linux irq number for hwirq=%d .", __func__, hw_irq);
					}
				}
				i++;
				status >>= 1;
				RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);
			}

			gpioNr += 31;
			reg_ofst += 4;
			RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);
		}
	}

	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);
	/*handle gpio assert */
	if (event & (p_rtk_gpio_ctl->gpio_isr_assert_offset))
	{
		gpioNr = 0;
		reg_ofst = 0;
		RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);
		while (gpioNr < (p_rtk_gpio_ctl->chip.ngpio))
		{
			status = ioread32(p_rtk_gpio_ctl->regs_umsk_isr_gpa + reg_ofst) >> 1;
			iowrite32(status << 1, p_rtk_gpio_ctl->regs_umsk_isr_gpa + reg_ofst);

			i = gpioNr;
			//printk("GPIO DEASSERT : %p = %08x\n", UMSK_ISR_GPDA + reg_ofst, status);

			while (status && i < (p_rtk_gpio_ctl->chip.ngpio))
			{
				if ((status & 0x1) && gpio_chk_irq_enable(p_rtk_gpio_ctl, i))
				{
					/*
					   mux_irq = p_rtk_gpio_ctl->chip.base + i;
					   generic_handle_irq(irq_find_mapping(p_rtk_gpio_ctl->irq_mux_domain, mux_irq));
					 */
					hw_irq = i;
					linux_irq = irq_find_mapping(p_rtk_gpio_ctl->irq_mux_domain, hw_irq);
					if (linux_irq)
					{
						RTK_debug("[%s]%s  line: %d \n",__FILE__,__FUNCTION__,__LINE__);
						RTK_debug("hw_irq = %d,  assertflg[%x] = %x \n",hw_irq,((unsigned int)((p_rtk_gpio_ctl->gpio_isr_assert_enable_flag) + GPIO_REG_OFST(hw_irq))), (*((p_rtk_gpio_ctl->gpio_isr_assert_enable_flag) + GPIO_REG_OFST(hw_irq))));
						if ( (1<<GPIO_REG_BIT(hw_irq)) & (*((p_rtk_gpio_ctl->gpio_isr_assert_enable_flag) + GPIO_REG_OFST(hw_irq)))  )
						{
							RTK_debug("[%s]%s  line: %d \n",__FILE__,__FUNCTION__,__LINE__);
							generic_handle_irq(linux_irq);
							irq_had_fired++;
						}
					}
					else
					{
						printk(KERN_ERR "%s can not specified linux irq number for hwirq=%d .", __func__, hw_irq);
					}
				}
				i++;
				status >>= 1;
				RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);
			}
			gpioNr += 31;
			reg_ofst += 4;
			RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);
		}
	}


	RTK_debug("[%s]%s  line: %d  irq_had_fired = %d\n",__FILE__,__FUNCTION__,__LINE__,irq_had_fired);
	iowrite32(event, p_rtk_gpio_ctl->reg_isr);
	if(!irq_had_fired)
		RTK_debug("%s gpio irq (hwirq=%d) has triggered but no dispatch to user handler (12345678 mean something Wrong) .\n", __func__, hw_irq);
	return ;

}

__maybe_unused static int mux_irq_domain_xlate(struct irq_domain *d,
											   struct device_node *controller,
											   const u32 * intspec, unsigned int intsize,
											   unsigned long *out_hwirq, unsigned int *out_type)
{
	RTK_debug("[%s]  %s  line: %d device_node.name = %s \n", __FILE__, __FUNCTION__, __LINE__, controller->name);

	if (/*d->of_node*/to_of_node(d->fwnode) != controller)
		return -EINVAL;

	if (intsize < 1)
		return -EINVAL;

	*out_hwirq = intspec[0];
	*out_type = 0;
	RTK_debug("[%s]  %s  line: %d out_hwirq = %ld \n", __FILE__, __FUNCTION__, __LINE__, *out_hwirq);
	return 0;
}

static int mux_irq_domain_map(struct irq_domain *d, unsigned int irq, irq_hw_number_t hw)
{
	struct rtk119x_gpio_controller *p_rtk_gpio_ctl = d->host_data;
	RTK_debug("[%s]  %s  line: %d   irq=%d , irq_hw_number=%d\n", __FILE__, __FUNCTION__, __LINE__, irq, (unsigned int)hw);

	if (!p_rtk_gpio_ctl)
	{
		RTK_debug("[%s]  %s  line: %d  p_rtk_gpio_ctl is NULL\n", __FILE__, __FUNCTION__, __LINE__);
		return -EINVAL;
	}
	RTK_debug("[%s]  %s  line: %d  p_rtk_gpio_ctl =%x bank_assert_irq =%d ,reg_ie= %x \n", __FILE__, __FUNCTION__, __LINE__,
			  (unsigned int)p_rtk_gpio_ctl, (unsigned int)p_rtk_gpio_ctl->bank_assert_irq, (unsigned int)p_rtk_gpio_ctl->reg_ie);

	irq_set_chip(irq, &p_rtk_gpio_ctl->gp_irq_chip);
	irq_set_chip_data(irq, (__force void *)p_rtk_gpio_ctl);
	irq_set_handler_data(irq, p_rtk_gpio_ctl);
	irq_set_handler(irq, handle_simple_irq);
	//set_irq_flags(irq, IRQF_VALID);

	return 0;
}

static struct irq_domain_ops mux_irq_domain_ops = {
	.xlate = mux_irq_domain_xlate,
	.map = mux_irq_domain_map,
};

int rtk119x_gpio_irq_setup(struct device_node *node, struct rtk119x_gpio_controller *p_rtk_gpio_ctl,
						   const struct rtk119x_gpio_groups *p_rtk_gpio_grp)
{
	int bank_deassert_irq, bank_assert_irq;

	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);

	p_rtk_gpio_ctl->gp_irq_chip.name = node->name;
	p_rtk_gpio_ctl->gp_irq_chip.irq_enable = gpio_irq_enable;
	p_rtk_gpio_ctl->gp_irq_chip.irq_disable = gpio_irq_disable;
	p_rtk_gpio_ctl->gp_irq_chip.irq_set_type = gpio_irq_type;
	p_rtk_gpio_ctl->gp_irq_chip.flags = IRQCHIP_SET_TYPE_MASKED;

	bank_assert_irq = irq_of_parse_and_map(node, 0);
	if (!bank_assert_irq)
	{
		printk(KERN_ALERT "Venus IR: fail to parse of irq.\n");
		return -ENXIO;
	}

	bank_deassert_irq = irq_of_parse_and_map(node, 1);
	if (!bank_deassert_irq)
	{
		printk(KERN_ALERT "Venus IR: fail to parse of irq.\n");
		return -ENXIO;
	}

	p_rtk_gpio_ctl->bank_assert_irq = bank_assert_irq;
	p_rtk_gpio_ctl->bank_deassert_irq = bank_deassert_irq;
	RTK_debug("[%s] %s  %d bank_assert_irq=%d \n", __FILE__, __FUNCTION__, __LINE__, p_rtk_gpio_ctl->bank_assert_irq);
	RTK_debug("[%s] %s  %d bank_deassert_irq=%d \n", __FILE__, __FUNCTION__, __LINE__, p_rtk_gpio_ctl->bank_deassert_irq);

	p_rtk_gpio_ctl->irq_mux_domain = irq_domain_add_simple(node, p_rtk_gpio_ctl->chip.ngpio,
														   p_rtk_gpio_ctl->linux_irq_base, &mux_irq_domain_ops, p_rtk_gpio_ctl);

	WARN(!p_rtk_gpio_ctl->irq_mux_domain, "IRQ domain init failed\n");

	irq_set_chained_handler(p_rtk_gpio_ctl->bank_deassert_irq,(irq_flow_handler_t)gpio_irq_handler);
	irq_set_handler_data(p_rtk_gpio_ctl->bank_deassert_irq, p_rtk_gpio_ctl);

	irq_set_chained_handler(p_rtk_gpio_ctl->bank_assert_irq, (irq_flow_handler_t)gpio_irq_handler);
	irq_set_handler_data(p_rtk_gpio_ctl->bank_assert_irq, p_rtk_gpio_ctl);
	return 0;
}

static inline int __rtk119x_direction(struct gpio_chip *chip, unsigned offset, bool out)
{
	struct rtk119x_gpio_controller *p_rtk_gpio_ctl = chip2controller(chip);
	unsigned int gpio_reg_offset = (offset / 32) * 4;

	unsigned long flags;
	u32 temp;
	u32 mask = 1 << (offset % 32);
	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);

	spin_lock_irqsave(&p_rtk_gpio_ctl->lock, flags);
	temp = __raw_readl((p_rtk_gpio_ctl->reg_dir) + gpio_reg_offset);
	if (out)
	{
		temp |= mask;
	}
	else
	{
		temp &= ~mask;
	}
	__raw_writel(temp, (p_rtk_gpio_ctl->reg_dir) + gpio_reg_offset);
	RTK_debug("[%s]  %s  line: %d  offset = %d  addr = 0x%08x  temp = 0x%08x \n", __FILE__, __FUNCTION__, __LINE__, offset,
			  (unsigned int)((p_rtk_gpio_ctl->reg_dir) + gpio_reg_offset), temp);
	spin_unlock_irqrestore(&p_rtk_gpio_ctl->lock, flags);

	return 0;
}

static int rtk119x_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct rtk119x_gpio_controller *p_rtk_gpio_ctl = chip2controller(chip);
	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);

	return ioread_reg_bit(((volatile void *)p_rtk_gpio_ctl->reg_dati + GPIO_REG_OFST(offset)), GPIO_REG_BIT(offset));

}

static void rtk119x_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct rtk119x_gpio_controller *p_rtk_gpio_ctl = chip2controller(chip);
	RTK_debug("[%s]  %s  line: %d  offset = %d  addr = %x  value = %d \n", __FILE__, __FUNCTION__, __LINE__, offset,
			  (unsigned int)((volatile void *)p_rtk_gpio_ctl->reg_dato + GPIO_REG_OFST(offset)), value);

	if (value)
		iowrite_reg_bit(((volatile void *)p_rtk_gpio_ctl->reg_dato + GPIO_REG_OFST(offset)), GPIO_REG_BIT(offset), 1);
	else
		iowrite_reg_bit(((volatile void *)p_rtk_gpio_ctl->reg_dato + GPIO_REG_OFST(offset)), GPIO_REG_BIT(offset), 0);
}

static int rtk119x_direction_in(struct gpio_chip *chip, unsigned offset)
{
	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);

	return __rtk119x_direction(chip, offset, GP_DIRIN);
}

static int rtk119x_direction_out(struct gpio_chip *chip, unsigned offset, int value)
{
	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);

	rtk119x_gpio_set(chip, offset, value);
	return __rtk119x_direction(chip, offset, GP_DIROUT);
}

static int rtk119x_gpio_setdeb(struct gpio_chip *chip, unsigned offset, unsigned debounce/*microsecond(us)*/)
{
	struct rtk119x_gpio_controller *p_rtk_gpio_ctl = chip2controller(chip);
	RTK_debug("[%s]  %s  line: %d debounce = %d \n", __FILE__, __FUNCTION__, __LINE__, debounce);

	if(debounce>=30*1000){//30ms
		debounce = RTK119X_GPIO_DEBOUNCE_30ms;
	}else if(debounce>=20*1000){//20ms
		debounce = RTK119X_GPIO_DEBOUNCE_20ms;
	}else if(debounce>=10*1000){//10ms
		debounce = RTK119X_GPIO_DEBOUNCE_10ms;
	}else if(debounce>=1000){// 1ms
		debounce = RTK119X_GPIO_DEBOUNCE_1ms;
	}else if(debounce>=100){// 100us
		debounce = RTK119X_GPIO_DEBOUNCE_100us;
	}else{
		debounce = RTK119X_GPIO_DEBOUNCE_10us;
	}

	if (strcmp("rtk_misc_gpio", chip->label) == 0)
	{
		RTK_debug("[%s]  %s  line: %d debounce = %d  for rtk_misc_gpio \n", __FILE__, __FUNCTION__, __LINE__, debounce);
		iowrite32((0x8 | debounce) << ((offset >> 4) * 4), ((volatile void *)p_rtk_gpio_ctl->reg_deb));
		return 0;
	}
	else if (strcmp("rtk_iso_gpio", chip->label) == 0)
	{
		RTK_debug("[%s]  %s  line: %d debounce = %d  for rtk_iso_gpio \n", __FILE__, __FUNCTION__, __LINE__, debounce);
		iowrite32((0x8 | debounce), ((volatile void *)p_rtk_gpio_ctl->reg_deb));
		return 0;
	}

	return -EINVAL;
}

static int rtk119x_gpio_request(struct gpio_chip *chip, unsigned offset)
{
	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);

	return pinctrl_request_gpio(chip->base + offset);
}

static void rtk119x_gpio_free(struct gpio_chip *chip, unsigned offset)
{
	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);

	pinctrl_free_gpio(chip->base + offset);
}

static int rtk119x_gpio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	struct rtk119x_gpio_controller *p_rtk_gpio_ctl = chip2controller(chip);
	unsigned int linux_irq = 0;
	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);

	linux_irq = irq_create_mapping(p_rtk_gpio_ctl->irq_mux_domain, offset);
	RTK_debug("[%s]  %s  line: %d linux_irq = %d \n", __FILE__, __FUNCTION__, __LINE__, linux_irq);
//  linux_irq = irq_find_mapping(p_rtk_gpio_ctl->irq_mux_domain, offset);
	if (!linux_irq)
	{
		printk(KERN_ERR "%s can not specified linux irq number for hwirq=%d .\n", __func__, offset);
		return -EINVAL;
	}
	return linux_irq;
}

static int rtk119x_gpio_xlate(struct gpio_chip *gc, const struct of_phandle_args *gpiospec, u32 * flags)
{
	unsigned int pin;
	RTK_debug("[%s]  %s  line: %d base = %d \n", __FILE__, __FUNCTION__, __LINE__, gc->base);

//  RTK_debug("[%s]  %s  line: %d args[0]=%d  args[1]=%d   args[2]=%d\n",__FILE__,__FUNCTION__,__LINE__,gpiospec->args[0],gpiospec->args[1],gpiospec->args[2]);
	RTK_debug("[%s]  %s  line: %d args[0]=%d  \n", __FILE__, __FUNCTION__, __LINE__, gpiospec->args[0]);

	if (WARN_ON(gc->of_gpio_n_cells < 1))
		return -EINVAL;

	if (WARN_ON(gpiospec->args_count < gc->of_gpio_n_cells))
		return -EINVAL;

	if (gpiospec->args[0] > gc->ngpio)
		return -EINVAL;

	pin = gpiospec->args[0];

	if (gpiospec->args[1] == GP_DIRIN)	//gpio direction input
	{
		if (rtk119x_direction_in(gc, pin))
			printk(KERN_ERR "gpio_xlate: failed to set pin direction in\n");
	}
	else
	{
		if (gpiospec->args[2] == GP_LOW)	//gpio direction output low
		{
			if (rtk119x_direction_out(gc, pin, GP_LOW))
				printk(KERN_ERR "gpio_xlate: failed to set pin direction out \n");
		}
		else if (gpiospec->args[2] == GP_HIGH)
		{
			if (rtk119x_direction_out(gc, pin, GP_HIGH))	//gpio direction output high
				printk(KERN_ERR "gpio_xlate: failed to set pin direction out \n");
		}
		else
		{
			printk(KERN_ERR "gpio_xlate: failed to set pin direction out \n");
		}
	}

//  if (rtk119x_gpio_setdeb(gc, pin,gpiospec->args[2]))
//      printk(KERN_ERR"gpio_xlate: failed to set pin deb\n");

	return gpiospec->args[0];
}

void set_default_gpio(struct device_node *node)
{
    int num_gpios, n;

    num_gpios = of_gpio_count(node);
    if (num_gpios > 0)
    {
        for (n = 0; n < num_gpios; n++)
        {
            int gpio = of_get_gpio_flags(node, n, NULL);
            RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);
            if (gpio >= 0)
            {
                if (!gpio_is_valid(gpio))
                    pr_err("[GPIO] %s: gpio %d is not valid\n",  __FUNCTION__, gpio);

                if (gpio_request(gpio, node->name))
                    pr_err("[GPIO] %s: gpio %d is in use\n",  __FUNCTION__, gpio);

                gpio_free(gpio);
            }
            else
                pr_err("[GPIO] %s: Could not get gpio from of \n", __FUNCTION__);
        }
    }

}

static const struct of_device_id rtk119x_gpio_of_match[] = {
	{.compatible = "Realtek,rtk-misc-gpio-irq-mux",},
	{.compatible = "Realtek,rtk-iso-gpio-irq-mux",},
	{ /* Sentinel */ },
};

static int rtk119x_gpio_probe(struct platform_device *pdev)
{
	int i;
	void __iomem *irq_regs_base;
	void __iomem *gpio_regs_base;
	struct rtk119x_gpio_controller *p_rtk_gpio_ctl;
	const struct rtk119x_gpio_groups *p_rtk_gpio_grp = NULL;
	unsigned int gpio_numbers;
	unsigned int gpio_base;
	struct device_node *node = NULL;
	unsigned int num_gpios, n;

	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);
	node = pdev->dev.of_node;
	if (!node)
	{
		printk(KERN_ERR "rtk gpio: failed to allocate device structure.\n");
		return -ENODEV;
	}

	RTK_debug("[%s]  %s  line: %d   node name = [%s] \n", __FILE__, __FUNCTION__, __LINE__, node->name);

	p_rtk_gpio_ctl = kzalloc(sizeof(struct rtk119x_gpio_controller), GFP_KERNEL);
	if (!p_rtk_gpio_ctl)
	{
		printk(KERN_ERR "rtk gpio: failed to allocate device structure.\n");
		return -ENOMEM;
	}
	memset(p_rtk_gpio_ctl, 0, sizeof(struct rtk119x_gpio_groups));

	if (of_property_read_u32_array(node, "Realtek,gpio_numbers", &gpio_numbers, 1))
	{
		printk(KERN_ERR "Don't know gpio group number.\n");
		return -EINVAL;
	}

	if (of_property_read_u32_index(node, "Realtek,gpio_base", 0, &gpio_base))
	{
		printk(KERN_ERR "Don't know gpio group number.\n");
		return -EINVAL;
	}

	for (i = 0; i < rtk_gpio_desc.ngroups; i++)
	{
		if (strcmp(rtk_gpio_grps_array[i].group_name, node->name) == 0)
			p_rtk_gpio_grp = &rtk_gpio_grps_array[i];
	}

	if (!p_rtk_gpio_grp)
	{
		printk(KERN_ERR "Don't know gpio group name.\n");
		return -EINVAL;
	}

	RTK_debug("[%s]  %s  line: %d   node name = [%s] \n", __FILE__, __FUNCTION__, __LINE__, node->name);
	p_rtk_gpio_ctl->chip.label = node->name;
	p_rtk_gpio_ctl->chip.request = rtk119x_gpio_request;
	p_rtk_gpio_ctl->chip.free = rtk119x_gpio_free;
	p_rtk_gpio_ctl->chip.direction_input = rtk119x_direction_in;
	p_rtk_gpio_ctl->chip.get = rtk119x_gpio_get;
	p_rtk_gpio_ctl->chip.direction_output = rtk119x_direction_out;
	p_rtk_gpio_ctl->chip.set = rtk119x_gpio_set;
	p_rtk_gpio_ctl->chip.set_debounce = rtk119x_gpio_setdeb;
	p_rtk_gpio_ctl->chip.to_irq = rtk119x_gpio_to_irq;
	p_rtk_gpio_ctl->chip.base = gpio_base;
	p_rtk_gpio_ctl->chip.ngpio = gpio_numbers;
	p_rtk_gpio_ctl->chip.of_gpio_n_cells = 3;	//must be the same with     #gpio-cells = <> in dtb
	p_rtk_gpio_ctl->chip.of_xlate = rtk119x_gpio_xlate;
	p_rtk_gpio_ctl->chip.of_node = node;

	spin_lock_init(&p_rtk_gpio_ctl->lock);

	irq_regs_base = of_iomap(node, 0);
	if (!irq_regs_base)
	{
		printk(KERN_ERR "unable to map irq_regs_base registers\n");
		return -EINVAL;
	}

	gpio_regs_base = of_iomap(node, 1);
	if (!gpio_regs_base)
	{
		printk(KERN_ERR "unable to map gpio_regs_base registers\n");
		return -EINVAL;
	}

	p_rtk_gpio_ctl->gpio_isr_deassert_offset = p_rtk_gpio_grp->gpio_isr_deassert_offset;
	p_rtk_gpio_ctl->gpio_isr_assert_offset = p_rtk_gpio_grp->gpio_isr_assert_offset;
	p_rtk_gpio_ctl->linux_irq_base = p_rtk_gpio_grp->linux_irq_base;
	p_rtk_gpio_ctl->reg_isr = (void __iomem *)((unsigned int)irq_regs_base + p_rtk_gpio_grp->reg_isr_off);
	p_rtk_gpio_ctl->regs_umsk_isr_gpa = (void __iomem *)((unsigned int)irq_regs_base + p_rtk_gpio_grp->reg_umsk_isr_gpa_off);
	p_rtk_gpio_ctl->regs_umsk_isr_gpda = (void __iomem *)((unsigned int)irq_regs_base + p_rtk_gpio_grp->reg_umsk_isr_gpda_off);
	p_rtk_gpio_ctl->reg_dir = (void __iomem *)((unsigned int)gpio_regs_base + p_rtk_gpio_grp->reg_dir_off);
	p_rtk_gpio_ctl->reg_dato = (void __iomem *)((unsigned int)gpio_regs_base + p_rtk_gpio_grp->reg_dato_off);
	p_rtk_gpio_ctl->reg_dati = (void __iomem *)((unsigned int)gpio_regs_base + p_rtk_gpio_grp->reg_dati_off);
	p_rtk_gpio_ctl->reg_ie = (void __iomem *)((unsigned int)gpio_regs_base + p_rtk_gpio_grp->reg_ie_off);
	p_rtk_gpio_ctl->reg_dp = (void __iomem *)((unsigned int)gpio_regs_base + p_rtk_gpio_grp->reg_dp_off);
	p_rtk_gpio_ctl->reg_deb = (void __iomem *)((unsigned int)gpio_regs_base + p_rtk_gpio_grp->reg_deb_off);

	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);
	if (gpiochip_add(&p_rtk_gpio_ctl->chip))
	{
		printk("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);

	}
	RTK_debug("[%s]  %s  line: %d \n", __FILE__, __FUNCTION__, __LINE__);
	rtk119x_gpio_irq_setup(node, p_rtk_gpio_ctl, p_rtk_gpio_grp);

	platform_set_drvdata(pdev,p_rtk_gpio_ctl);

	/*TODO : need to implement gpio device tree */
	//  of_irq_init(rtk119x_gpio_mux_irq_match);

	/* Initial default gpios */
	set_default_gpio(node);

	return 0;
}

static int rtk119x_gpio_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct rtk119x_gpio_controller *p_rtk_gpio_ctl;
	p_rtk_gpio_ctl = platform_get_drvdata(pdev);

	pr_info("[GPIO] Enter %s, label(%s)\n",__FUNCTION__,p_rtk_gpio_ctl->chip.label);

	disable_irq(p_rtk_gpio_ctl->bank_assert_irq);
	disable_irq(p_rtk_gpio_ctl->bank_deassert_irq);

	pr_info("[GPIO] Exit %s\n",__FUNCTION__);

	return 0;
}

static int rtk119x_gpio_resume(struct platform_device *pdev)
{
	struct rtk119x_gpio_controller *p_rtk_gpio_ctl;
    struct device_node *node ;

	p_rtk_gpio_ctl = platform_get_drvdata(pdev);
    node = p_rtk_gpio_ctl->chip.of_node;

	pr_info("[GPIO] Enter %s, label(%s)\n",__FUNCTION__,p_rtk_gpio_ctl->chip.label);

    /* Initial default gpios */
    set_default_gpio(node);

	enable_irq(p_rtk_gpio_ctl->bank_assert_irq);
	enable_irq(p_rtk_gpio_ctl->bank_deassert_irq);

	pr_info("[GPIO] Exit %s\n",__FUNCTION__);

	return 0;
}

static struct platform_driver rtk119x_gpio_driver = {
	.driver = {
			   .name = "rtk119x-gpio",
			   .owner = THIS_MODULE,
			   .of_match_table = rtk119x_gpio_of_match,
			   },
	.probe = rtk119x_gpio_probe,
	.suspend = rtk119x_gpio_suspend,
	.resume = rtk119x_gpio_resume,
};

static int rtk119x_gpio_init(void)
{
	return platform_driver_register(&rtk119x_gpio_driver);
}

postcore_initcall(rtk119x_gpio_init);
