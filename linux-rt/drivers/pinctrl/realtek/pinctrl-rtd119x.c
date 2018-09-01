/*
 * Realtek pin controller driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include <linux/io.h>
#include <linux/clk.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/pinctrl/consumer.h>
#include <linux/pinctrl/machine.h>
#include <linux/pinctrl/pinctrl.h>
#include <linux/pinctrl/pinconf-generic.h>
#include <linux/pinctrl/pinmux.h>
#include <linux/platform_device.h>
#include <linux/slab.h>

#include "../core.h"
#ifndef CONFIG_MACH_RTK1192
#include "pinctrl-rtd119x.h"
#else
#include "pinctrl-rtk1192.h"
#endif

static const struct RTK119X_pinctrl_desc rtk119x_pinctrl_data = {
	.pins = rtk119x_pins,
	.npins = ARRAY_SIZE(rtk119x_pins),
};

static void RTK119X_pmx_set(struct pinctrl_dev *pctldev,unsigned pin,u8 config)
{
	struct RTK119X_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	void __iomem *addr;
	u32 val;
	u32 mask ;

#ifdef CONFIG_MACH_RTK1192
	if(pin_regmap[pin].pmux_regoff == PMUX_UNSUPPORT)
		return;
#endif

	if ( pin < PINS_OF_CRTBANK)
		addr = pctl->crt_membase + pin_regmap[pin].pmux_regoff;
	 else
		addr = pctl->iso_membase + pin_regmap[pin].pmux_regoff;

	RTK_debug("[%s]  %s   %d  addr=%x, bit=%d ,config = %x	 \n ",__FILE__,__FUNCTION__, __LINE__,(u32)addr ,pin_regmap[pin].pmux_regbit ,config);

	val = readl(addr);
	mask =	pin_regmap[pin].pmux_regbitmsk << pin_regmap[pin].pmux_regbit;
	writel(((val & ~mask) | (config << pin_regmap[pin].pmux_regbit)),  addr);

	RTK_debug("[%s]  %s   %d  addr=%x , bit=%d ,final_val = %x	 \n ",__FILE__,__FUNCTION__, __LINE__,(u32)addr,pin_regmap[pin].pmux_regbit ,readl(addr) );

}

static struct RTK119X_pinctrl_group *
RTK119X_pinctrl_find_group_by_name(struct RTK119X_pinctrl *pctl, const char *group)
{
	int i;
	RTK_debug("[%s]  %s   %d  name = %s \n ",__FILE__,__FUNCTION__, __LINE__,group);
	for (i = 0; i < pctl->ngroups; i++) {
		struct RTK119X_pinctrl_group *grp = pctl->groups + i;

		if (!strcmp(grp->name, group))
			return grp;
	}

	return NULL;
}

static struct RTK119X_pinctrl_function *
RTK119X_pinctrl_find_function_by_name(struct RTK119X_pinctrl *pctl,
				    const char *name)
{
	struct RTK119X_pinctrl_function *func = pctl->functions;
	int i;
//	RTK_debug("[%s]  %s   %d \n ",__FILE__,__FUNCTION__, __LINE__);
	for (i = 0; i < pctl->nfunctions; i++) {
		if (!func[i].name)
			break;

		if (!strcmp(func[i].name, name))
			return func + i;
	}

	return NULL;
}

static struct RTK119X_desc_function *
RTK119X_pinctrl_desc_find_function_by_name(struct RTK119X_pinctrl *pctl,
					 const char *pin_name,
					 const char *func_name)
{
	int i;
	RTK_debug("[%s]  %s   %d  pin_name=%s, func_name=%s\n ",__FILE__,__FUNCTION__, __LINE__, pin_name,func_name);
	for (i = 0; i < pctl->desc->npins; i++) {
		const struct RTK119X_desc_pin *pin = pctl->desc->pins + i;

		if (!strcmp(pin->pin.name, pin_name)) {
			struct RTK119X_desc_function *func = pin->functions;

			while (func->name) {
				if (!strcmp(func->name, func_name))
					return func;

				func++;
			}
		}
	}

	return NULL;
}

static int RTK119X_pctrl_get_groups_count(struct pinctrl_dev *pctldev)
{
	struct RTK119X_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	RTK_debug("[%s]  %s   %d pctl->ngroups=%d \n ",__FILE__,__FUNCTION__, __LINE__, pctl->ngroups);
	return pctl->ngroups;
}

static const char *RTK119X_pctrl_get_group_name(struct pinctrl_dev *pctldev,
					      unsigned group)
{
	struct RTK119X_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	RTK_debug("[%s]  %s   %d group].name=%s \n ",__FILE__,__FUNCTION__, __LINE__,pctl->groups[group].name);
	return pctl->groups[group].name;
}

static int RTK119X_pctrl_get_group_pins(struct pinctrl_dev *pctldev,
				      unsigned group,
				      const unsigned **pins,
				      unsigned *num_pins)
{
	struct RTK119X_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	RTK_debug("[%s]  %s   %d \n ",__FILE__,__FUNCTION__, __LINE__);
	*pins = (unsigned *)&pctl->groups[group].pin;
	*num_pins = 1;

	return 0;
}

static int RTK119X_pctrl_dt_node_to_map(struct pinctrl_dev *pctldev,
				      struct device_node *node,
				      struct pinctrl_map **map,
				      unsigned *num_maps)
{
	struct RTK119X_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	unsigned long *pinconfig;
	struct property *prop;
	const char *function;
	const char *group;
	int ret, nmaps, i = 0;
	u32 val;
	RTK_debug("[%s]  %s   %d \n ",__FILE__,__FUNCTION__, __LINE__);
	*map = NULL;
	*num_maps = 0;

	ret = of_property_read_string(node, "rtk119x,function", &function);
	if (ret) {
		printk(
			"missing rtk119x,function property in node %s\n",
			node->name);
		return -EINVAL;
	}

	nmaps = of_property_count_strings(node, "rtk119x,pins") * 2;
	if (nmaps < 0) {
		printk(
			"missing rtk119x,pins property in node %s\n",
			node->name);
		return -EINVAL;
	}

	*map = kmalloc(nmaps * sizeof(struct pinctrl_map), GFP_KERNEL);
	if (!map)
		return -ENOMEM;

	of_property_for_each_string(node, "rtk119x,pins", prop, group) {
		struct RTK119X_pinctrl_group *grp =
			RTK119X_pinctrl_find_group_by_name(pctl, group);
		int j = 0, configlen = 0;

		if (!grp) {
			printk( "unknown pin %s", group);
			continue;
		}

		if (!RTK119X_pinctrl_desc_find_function_by_name(pctl,
							      grp->name,
							      function)) {
			printk( "unsupported function %s on pin %s",
				function, group);
			continue;
		}

		(*map)[i].type = PIN_MAP_TYPE_MUX_GROUP;
		(*map)[i].data.mux.group = group;
		(*map)[i].data.mux.function = function;

		i++;

		(*map)[i].type = PIN_MAP_TYPE_CONFIGS_GROUP;
		(*map)[i].data.configs.group_or_pin = group;

		if (of_find_property(node, "rtk119x,schmitt", NULL))
			configlen++;
		if (of_find_property(node, "rtk119x,drive", NULL))
			configlen++;
		if (of_find_property(node, "rtk119x,pull_en", NULL))
			configlen++;
		if (of_find_property(node, "rtk119x,pull_sel", NULL))
			configlen++;


		pinconfig = kzalloc(configlen * sizeof(*pinconfig), GFP_KERNEL);

		if (!of_property_read_u32(node, "rtk119x,schmitt", &val)) {
			u16 schmitt_enable;
			if (val==0)
				schmitt_enable = 0;
			else
				schmitt_enable = 1;
			
			pinconfig[j++] = pinconf_to_config_packed(PIN_CONFIG_INPUT_SCHMITT_ENABLE, schmitt_enable);
		}

		if (!of_property_read_u32(node, "rtk119x,drive", &val)) {
			pinconfig[j++] = pinconf_to_config_packed(PIN_CONFIG_DRIVE_STRENGTH, val);
		}

		if (!of_property_read_u32(node, "rtk119x,pull_en", &val)) {
			enum pin_config_param pull= PIN_CONFIG_END;
			if (val == 0)
				pull = PIN_CONFIG_BIAS_DISABLE;
			else if(val == 1)
				pull = PIN_CONFIG_DRIVE_PUSH_PULL;
			pinconfig[j++] = pinconf_to_config_packed(pull, 0);
		}

		if (!of_property_read_u32(node, "rtk119x,pull_sel", &val)) {
			enum pin_config_param pull = PIN_CONFIG_END;
			if (val == 0)
				pull = PIN_CONFIG_BIAS_PULL_DOWN;
			else if (val == 1)
				pull = PIN_CONFIG_BIAS_PULL_UP;
			pinconfig[j++] = pinconf_to_config_packed(pull, 1);
		}
		RTK_debug("[%s]  %s   %d \n ",__FILE__,__FUNCTION__, __LINE__);
		(*map)[i].data.configs.configs = pinconfig;
		(*map)[i].data.configs.num_configs = configlen;

		i++;
	}

	*num_maps = nmaps;

	return 0;
}

static void RTK119X_pctrl_dt_free_map(struct pinctrl_dev *pctldev,
				    struct pinctrl_map *map,
				    unsigned num_maps)
{
	int i;
	RTK_debug("[%s]  %s   %d \n ",__FILE__,__FUNCTION__, __LINE__);
	for (i = 0; i < num_maps; i++) {
		if (map[i].type == PIN_MAP_TYPE_CONFIGS_GROUP)
			kfree(map[i].data.configs.configs);
	}

	kfree(map);
}

static const struct pinctrl_ops RTK119X_pctrl_ops = {
	.dt_node_to_map		= RTK119X_pctrl_dt_node_to_map,
	.dt_free_map		= RTK119X_pctrl_dt_free_map,
	.get_groups_count	= RTK119X_pctrl_get_groups_count,
	.get_group_name		= RTK119X_pctrl_get_group_name,
	.get_group_pins		= RTK119X_pctrl_get_group_pins,
};

static int RTK119X_pconf_group_get(struct pinctrl_dev *pctldev,
				 unsigned group,
				 unsigned long *config)
{
	struct RTK119X_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	RTK_debug("[%s]  %s   %d \n ",__FILE__,__FUNCTION__, __LINE__);
	*config = pctl->groups[group].config;

	return 0;
}

static int RTK119X_pconf_group_set(struct pinctrl_dev *pctldev,
				 unsigned group,
				 unsigned long config)
{
	struct RTK119X_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct RTK119X_pinctrl_group *g = &pctl->groups[group];
	u32 val, mask;
	u16 strength;
	u8 set_val;
	void __iomem *addr;
	RTK_debug("[%s]  %s   %d   g->pin=%d    g->name =%s  config = %lx \n ",__FILE__,__FUNCTION__, __LINE__,g->pin,g->name,config);

	if(pin_regmap[g->pin].pcof_regoff == PCOF_UNSUPPORT)
	{
		RTK_debug("[pinctrl] g->pin(%d) g->name(%s) not support pin config\n",g->pin,g->name);
		g->config = config;
		return 0;
	}

	if ( g->pin < PINS_OF_CRTBANK)
		addr = pctl->crt_membase + pin_regmap[g->pin].pcof_regoff;
	 else
		addr = pctl->iso_membase + pin_regmap[g->pin].pcof_regoff;


	switch (pinconf_to_config_param(config)) {

		case PIN_CONFIG_INPUT_SCHMITT:
			break;
		case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
			set_val = pinconf_to_config_argument(config);
			if(set_val)
				set_val = 1;
			else
				set_val = 0;

			val = readl(addr);
			mask =  1 << (pin_regmap[g->pin].pcof_regbit + RTK119X_PCONF_SCHM);
			writel(((val & ~mask)|(set_val<<(pin_regmap[g->pin].pcof_regbit+RTK119X_PCONF_SCHM))), addr);
			break;


		case PIN_CONFIG_DRIVE_STRENGTH:
			strength = pinconf_to_config_argument(config);
			switch(pin_regmap[g->pin].pcof_cur_strgh)
			{
				case PADDRI_4_8:
					if(strength == 4) set_val = 0;
					else if(strength == 8) set_val = 1;
					else return -EINVAL;
					break;
				case PADDRI_2_4:
					if(strength == 2) set_val = 0;
					else if(strength == 4) set_val = 1;
					else return -EINVAL;
					break;
				case PADDRI_UNSUPPORT:
				default:
					return -EINVAL;
					break;
			}

			val = readl(addr);
			mask =  1 << (pin_regmap[g->pin].pcof_regbit + RTK119X_PCONF_CURR);
			writel(((val & ~mask)|(set_val<<(pin_regmap[g->pin].pcof_regbit+RTK119X_PCONF_CURR))), addr);
			break;
		case PIN_CONFIG_DRIVE_PUSH_PULL :
			val = readl(addr);
			mask =  1 << (pin_regmap[g->pin].pcof_regbit + RTK119X_PCONF_PULEN);
			writel(((val & ~mask)|(1<<(pin_regmap[g->pin].pcof_regbit+RTK119X_PCONF_PULEN))), addr);
			break;

		case PIN_CONFIG_BIAS_DISABLE :
			val = readl(addr);
			mask =  1 << (pin_regmap[g->pin].pcof_regbit + RTK119X_PCONF_PULEN);
			writel(((val & ~mask)|(0<<(pin_regmap[g->pin].pcof_regbit+RTK119X_PCONF_PULEN))), addr);
			break;
		case PIN_CONFIG_BIAS_PULL_UP:
			val = readl(addr);
			mask =  1 << (pin_regmap[g->pin].pcof_regbit + RTK119X_PCONF_PULSEL);
			writel(((val & ~mask)|(1<<(pin_regmap[g->pin].pcof_regbit+RTK119X_PCONF_PULSEL))), addr);
			break;
		case PIN_CONFIG_BIAS_PULL_DOWN:
			val = readl(addr);
			mask =  1 << (pin_regmap[g->pin].pcof_regbit + RTK119X_PCONF_PULSEL);
			writel(((val & ~mask)|(0<<(pin_regmap[g->pin].pcof_regbit+RTK119X_PCONF_PULSEL))), addr);

			break;
		default:
			break;
	}

	/* cache the config value */
	g->config = config;
	return 0;
}

static const struct pinconf_ops RTK119X_pconf_ops = {
	.pin_config_group_get	= RTK119X_pconf_group_get,
	.pin_config_group_set	= RTK119X_pconf_group_set,
};

static int RTK119X_pmx_get_funcs_cnt(struct pinctrl_dev *pctldev)
{
	struct RTK119X_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	RTK_debug("[%s]  %s   %d pctl->nfunctions =%d \n ",__FILE__,__FUNCTION__, __LINE__,pctl->nfunctions);
	return pctl->nfunctions;
}

static const char *RTK119X_pmx_get_func_name(struct pinctrl_dev *pctldev,
					   unsigned function)
{
	struct RTK119X_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	RTK_debug("[%s]  %s   %d function[%d] = %s\n ",__FILE__,__FUNCTION__, __LINE__, function,pctl->functions[function].name);
	return pctl->functions[function].name;
}

static int RTK119X_pmx_get_func_groups(struct pinctrl_dev *pctldev,
				     unsigned function,
				     const char * const **groups,
				     unsigned * const num_groups)
{
	struct RTK119X_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	RTK_debug("[%s]  %s   %d \n ",__FILE__,__FUNCTION__, __LINE__);
	*groups = pctl->functions[function].groups;
	*num_groups = pctl->functions[function].ngroups;

	return 0;
}

static int RTK119X_pmx_enable(struct pinctrl_dev *pctldev,
			    unsigned function,
			    unsigned group)
{
	struct RTK119X_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct RTK119X_pinctrl_group *g = pctl->groups + group;
	struct RTK119X_pinctrl_function *func = pctl->functions + function;
	struct RTK119X_desc_function *desc =
		RTK119X_pinctrl_desc_find_function_by_name(pctl,
							 g->name,
							 func->name);
	RTK_debug("[%s]  %s   %d  g->name=%s ,func->name=%s  \n ",__FILE__,__FUNCTION__, __LINE__,g->name,func->name );
	if (!desc)
		return -EINVAL;

	RTK119X_pmx_set(pctldev, g->pin, desc->muxval);

	return 0;
}


static int
RTK119X_pmx_gpio_request_enable (struct pinctrl_dev *pctldev,
				    struct pinctrl_gpio_range *range,
				    unsigned offset)
{
	struct RTK119X_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct RTK119X_pinctrl_group *g = pctl->groups + offset;
	struct RTK119X_desc_function *desc;
	const char *func;
	int ret;
	func = "gpio";
	RTK_debug("[%s]  %s   %d gpio_offset = %d \n ",__FILE__,__FUNCTION__, __LINE__,offset);
	desc = RTK119X_pinctrl_desc_find_function_by_name(pctl,
							g->name,
							func);
	if (!desc) {
		ret = -EINVAL;
		goto error;
	}

	RTK119X_pmx_set(pctldev, offset, desc->muxval);

	ret = 0;

error:
	return ret;
}

static void
RTK119X_pmx_gpio_disable_free (struct pinctrl_dev *pctldev,
				    struct pinctrl_gpio_range *range,
				    unsigned offset)
{
	RTK_debug("[%s]  %s   %d \n ",__FILE__,__FUNCTION__, __LINE__);
/*TODO : need to add gpio related api*/
	return ;
}



static const struct pinmux_ops RTK119X_pmx_ops = {
	.get_functions_count	= RTK119X_pmx_get_funcs_cnt,
	.get_function_name	= RTK119X_pmx_get_func_name,
	.get_function_groups	= RTK119X_pmx_get_func_groups,
	.set_mux		= RTK119X_pmx_enable,
	.gpio_request_enable = RTK119X_pmx_gpio_request_enable,
	.gpio_disable_free = RTK119X_pmx_gpio_disable_free,
};

static struct pinctrl_desc RTK119X_pctrl_desc = {
	.confops	= &RTK119X_pconf_ops,
	.pctlops	= &RTK119X_pctrl_ops,
	.pmxops		= &RTK119X_pmx_ops,
};
#if 0
static int RTK119X_pinctrl_gpio_request(struct gpio_chip *chip, unsigned offset)
{
	return pinctrl_request_gpio((unsigned)chip->base + offset);
}

static void RTK119X_pinctrl_gpio_free(struct gpio_chip *chip, unsigned offset)
{
	pinctrl_free_gpio((unsigned)chip->base + offset);
}

static int RTK119X_pinctrl_gpio_direction_input(struct gpio_chip *chip,
					unsigned offset)
{
	return pinctrl_gpio_direction_input((unsigned)chip->base + offset);
}

static int RTK119X_pinctrl_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct RTK119X_pinctrl *pctl = dev_get_drvdata(chip->dev);

	u32 reg = RTK119X_data_reg(offset);
	u8 index = RTK119X_data_offset(offset);
	u32 val = (readl(pctl->membase + reg) >> index) & DATA_PINS_MASK;

	return val;
}

static int RTK119X_pinctrl_gpio_direction_output(struct gpio_chip *chip,
					unsigned offset, int value)
{
	return pinctrl_gpio_direction_output((unsigned)chip->base + offset);
}

static void RTK119X_pinctrl_gpio_set(struct gpio_chip *chip,
				unsigned offset, int value)
{
	struct RTK119X_pinctrl *pctl = dev_get_drvdata(chip->dev);
	u32 reg = RTK119X_data_reg(offset);
	u8 index = RTK119X_data_offset(offset);

	writel((value & DATA_PINS_MASK) << index, pctl->membase + reg);
}

static int RTK119X_pinctrl_gpio_of_xlate(struct gpio_chip *gc,
				const struct of_phandle_args *gpiospec,
				u32 *flags)
{
	int pin, base;

	base = PINS_PER_BANK * gpiospec->args[0];
	pin = base + gpiospec->args[1];

	if (pin > ((unsigned)gc->base + gc->ngpio))
		return -EINVAL;

	if (flags)
		*flags = gpiospec->args[2];

	return pin;
}

static struct gpio_chip RTK119X_pinctrl_gpio_chip = {
	.owner			= THIS_MODULE,
	.request		= RTK119X_pinctrl_gpio_request,
	.free			= RTK119X_pinctrl_gpio_free,
	.direction_input	= RTK119X_pinctrl_gpio_direction_input,
	.direction_output	= RTK119X_pinctrl_gpio_direction_output,
	.get			= RTK119X_pinctrl_gpio_get,
	.set			= RTK119X_pinctrl_gpio_set,
	.of_xlate		= RTK119X_pinctrl_gpio_of_xlate,
	.of_gpio_n_cells	= 3,
	.can_sleep		= 0,
};
#endif

static struct of_device_id RTK119X_pinctrl_match[] = {
	{ .compatible = "rtk119x,rtk119x-pinctrl", .data = (void *)&rtk119x_pinctrl_data },
	{ /* Sentinel */ },
};
MODULE_DEVICE_TABLE(of, RTK119X_pinctrl_match);

static int RTK119X_pinctrl_add_function(struct RTK119X_pinctrl *pctl,
					const char *name)
{
	struct RTK119X_pinctrl_function *func = pctl->functions;
	while (func->name) {
		/* function already there */
		if (strcmp(func->name, name) == 0) {
			func->ngroups++;
			return -EEXIST;
		}
		func++;
	}
	
	func->name = name;
	func->ngroups = 1;

	pctl->nfunctions++;

	return 0;
}

static int RTK119X_pinctrl_build_state(struct platform_device *pdev)
{
	struct RTK119X_pinctrl *pctl = platform_get_drvdata(pdev);
	int i;
	RTK_debug("[%s]  %s   %d \n ",__FILE__,__FUNCTION__, __LINE__);
	pctl->ngroups = pctl->desc->npins;

	/* Allocate groups */
	pctl->groups = devm_kzalloc(&pdev->dev,
				    pctl->ngroups * sizeof(*pctl->groups),
				    GFP_KERNEL);
	if (!pctl->groups)
		return -ENOMEM;

	for (i = 0; i < pctl->desc->npins; i++) {
		const struct RTK119X_desc_pin *pin = pctl->desc->pins + i;
		struct RTK119X_pinctrl_group *group = pctl->groups + i;

		group->name = pin->pin.name;
		group->pin = pin->pin.number;
	}

	/*
	 * We suppose that we won't have any more functions than pins,
	 * we'll reallocate that later anyway
	 */
	pctl->functions = devm_kzalloc(&pdev->dev,
				pctl->desc->npins * sizeof(*pctl->functions),
				GFP_KERNEL);
	if (!pctl->functions)
		return -ENOMEM;

	/* Count functions and their associated groups */
	for (i = 0; i < pctl->desc->npins; i++) {
		const struct RTK119X_desc_pin *pin = pctl->desc->pins + i;
		struct RTK119X_desc_function *func = pin->functions;

		while (func->name) {
			RTK119X_pinctrl_add_function(pctl, func->name);
			func++;
		}
	}

	pctl->functions = krealloc(pctl->functions,
				pctl->nfunctions * sizeof(*pctl->functions),
				GFP_KERNEL);

	for (i = 0; i < pctl->desc->npins; i++) {
		const struct RTK119X_desc_pin *pin = pctl->desc->pins + i;
		struct RTK119X_desc_function *func = pin->functions;

		while (func->name) {
			struct RTK119X_pinctrl_function *func_item;
			const char **func_grp;

			func_item = RTK119X_pinctrl_find_function_by_name(pctl,
									func->name);
			if (!func_item)
				return -EINVAL;

			if (!func_item->groups) {
				func_item->groups =
					devm_kzalloc(&pdev->dev,
						     func_item->ngroups * sizeof(*func_item->groups),
						     GFP_KERNEL);
				if (!func_item->groups)
					return -ENOMEM;
			}

			func_grp = func_item->groups;
			while (*func_grp)
				func_grp++;

			*func_grp = pin->pin.name;
			func++;
		}
	}

	return 0;
}

static int RTK119X_pinctrl_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	const struct of_device_id *device;
	struct pinctrl_pin_desc *pins;
	struct RTK119X_pinctrl *pctl;
	int i, ret;

	RTK_debug(KERN_ERR "[%s]  %s   %d \n ",__FILE__,__FUNCTION__, __LINE__);
	pctl = devm_kzalloc(&pdev->dev, sizeof(*pctl), GFP_KERNEL);
	if (!pctl)
		return -ENOMEM;
	platform_set_drvdata(pdev, pctl);

	pctl->crt_membase = of_iomap(node, 0);
	if (!pctl->crt_membase)
		return -ENOMEM;

	pctl->iso_membase = of_iomap(node, 1);
	if (!pctl->iso_membase)
		return -ENOMEM;

	device = of_match_device(RTK119X_pinctrl_match, &pdev->dev);
	if (!device)
		return -ENODEV;

	pctl->desc = (struct RTK119X_pinctrl_desc *)device->data;

	ret = RTK119X_pinctrl_build_state(pdev);
	if (ret) {
		dev_err(&pdev->dev, "dt probe failed: %d\n", ret);
		return ret;
	}

	pins = devm_kzalloc(&pdev->dev,
			    pctl->desc->npins * sizeof(*pins),
			    GFP_KERNEL);
	if (!pins)
		return -ENOMEM;

	for (i = 0; i < pctl->desc->npins; i++)
		pins[i] = pctl->desc->pins[i].pin;

	RTK119X_pctrl_desc.name = dev_name(&pdev->dev);
	RTK119X_pctrl_desc.owner = THIS_MODULE;
	RTK119X_pctrl_desc.pins = pins;
	RTK119X_pctrl_desc.npins = pctl->desc->npins;
	pctl->dev = &pdev->dev;
	pctl->pctl_dev = pinctrl_register(&RTK119X_pctrl_desc,
					  &pdev->dev, pctl);
	if (!pctl->pctl_dev) {
		dev_err(&pdev->dev, "couldn't register pinctrl driver\n");
		return -EINVAL;
	}

/*
	pctl->chip = devm_kzalloc(&pdev->dev, sizeof(*pctl->chip), GFP_KERNEL);
	if (!pctl->chip) {
		ret = -ENOMEM;
		goto pinctrl_error;
	}

	last_pin = pctl->desc->pins[pctl->desc->npins - 1].pin.number;


	pctl->chip = &RTK119X_pinctrl_gpio_chip;
	pctl->chip->ngpio = round_up(last_pin, PINS_PER_BANK);
	pctl->chip->label = dev_name(&pdev->dev);
	pctl->chip->dev = &pdev->dev;
	pctl->chip->base = 0;

	ret = gpiochip_add(pctl->chip);
	if (ret)
		goto pinctrl_error;
*/

/*TODO : gpio should add range to pinctrl   victor*/
/*
	for (i = 0; i < pctl->desc->npins; i++) {
		const struct RTK119X_desc_pin *pin = pctl->desc->pins + i;

		ret = gpiochip_add_pin_range(pctl->chip, dev_name(&pdev->dev),
					     pin->pin.number,
					     pin->pin.number, 1);
		if (ret)
			goto gpiochip_error;
	}


	clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(clk)) {
		ret = PTR_ERR(clk);
		goto gpiochip_error;
	}

	clk_prepare_enable(clk);

	dev_info(&pdev->dev, "initialized rtk119x PIO driver\n");
*/
	return 0;
/*
gpiochip_error:
	if (gpiochip_remove(pctl->chip))
		dev_err(&pdev->dev, "failed to remove gpio chip\n");
pinctrl_error:

	pinctrl_unregister(pctl->pctl_dev);
	return ret;
*/
}

static struct platform_driver RTK119X_pinctrl_driver = {
	.probe = RTK119X_pinctrl_probe,
	.driver = {
		.name = "rtk119x-pinctrl",
		.owner = THIS_MODULE,
		.of_match_table = RTK119X_pinctrl_match,
	},
};
//early_platform_init("RTK119XPinctrlDriver", &RTK119X_pinctrl_driver);



static int  rtk119x_pinctrl_init(void)
{
	return platform_driver_register(&RTK119X_pinctrl_driver);
}
postcore_initcall(rtk119x_pinctrl_init);
//module_platform_driver(RTK119X_pinctrl_driver);
//module_platform_driver(RTK119X_pinctrl_driver);

MODULE_DESCRIPTION("RTK119x pinctrl driver");
MODULE_LICENSE("GPL");



