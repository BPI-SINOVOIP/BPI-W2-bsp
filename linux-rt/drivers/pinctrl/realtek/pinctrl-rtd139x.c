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

#include "pinctrl-rtd139x.h"
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

#ifdef CONFIG_RTK_XEN_SUPPORT
#include <xen/xen.h>
#endif

static u32 *pinctrl_reg_values;

static const struct RTK_pinctrl_desc rtk139x_pinctrl_data = {
	.pins = rtk_pins,
	.npins = ARRAY_SIZE(rtk_pins),
};

static void RTK_pmx_set(struct pinctrl_dev *pctldev,
	unsigned int pin, u8 config)
{
	struct RTK_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	void __iomem *addr;
	u32 val;
	u32 mask;

	if (pin_regmap[pin].pmux_regoff == PMUX_UNSUPPORT)
		return;

	if (pin_regmap[pin].pmux_base != PMUX_BASE_ISO)
		RTK_PINCTRL_ERR("[%s] Unknow pmux_base\n", __func__);
	addr = pctl->iso_membase + pin_regmap[pin].pmux_regoff;

	RTK_PINCTRL_DBG("[%s] Addr(0x%08llx), bit=%u, config=%u",
		__func__, (u64)addr, pin_regmap[pin].pmux_regbit, config);

	val = readl(addr);
	mask =	pin_regmap[pin].pmux_regbitmsk << pin_regmap[pin].pmux_regbit;
	writel(((val & ~mask) | (config << pin_regmap[pin].pmux_regbit)), addr);

	RTK_PINCTRL_DBG("[%s] Addr(0x%08llx) final_val=0x%08x",
			__func__, (u64)addr, readl(addr));

}

static struct RTK_pinctrl_group *
RTK_pinctrl_find_group_by_name(struct RTK_pinctrl *pctl, const char *group)
{
	int i;

	RTK_PINCTRL_DBG("[%s] name = %s", __func__, group);
	for (i = 0; i < pctl->ngroups; i++) {
		struct RTK_pinctrl_group *grp = pctl->groups + i;

		if (!strcmp(grp->name, group))
			return grp;
	}

	return NULL;
}

static struct RTK_pinctrl_function *
RTK_pinctrl_find_function_by_name(struct RTK_pinctrl *pctl,
				    const char *name)
{
	struct RTK_pinctrl_function *func = pctl->functions;
	int i;
	/*RTK_PINCTRL_DBG("[%s]", __func__);*/
	for (i = 0; i < pctl->nfunctions; i++) {
		if (!func[i].name)
			break;

		if (!strcmp(func[i].name, name))
			return func + i;
	}

	return NULL;
}

static struct RTK_desc_function *
RTK_pinctrl_desc_find_function_by_name(struct RTK_pinctrl *pctl,
					 const char *pin_name,
					 const char *func_name)
{
	int i;

	RTK_PINCTRL_DBG("[%s] pin_name=%s, func_name=%s",
			__func__, pin_name, func_name);
	for (i = 0; i < pctl->desc->npins; i++) {
		const struct RTK_desc_pin *pin = pctl->desc->pins + i;

		if (!strcmp(pin->pin.name, pin_name)) {
			struct RTK_desc_function *func = pin->functions;

			while (func->name) {
				if (!strcmp(func->name, func_name))
					return func;

				func++;
			}
		}
	}

	return NULL;
}

static int RTK_pctrl_get_groups_count(struct pinctrl_dev *pctldev)
{
	struct RTK_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	RTK_PINCTRL_DBG("[%s] pctl->ngroups=%d",
			__func__, pctl->ngroups);
	return pctl->ngroups;
}

static const char *RTK_pctrl_get_group_name(struct pinctrl_dev *pctldev,
					      unsigned int group)
{
	struct RTK_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	/*RTK_PINCTRL_DBG("[%s] group.name=%s",
	 *		__func__, pctl->groups[group].name);
	 */
	return pctl->groups[group].name;
}

static int RTK_pctrl_get_group_pins(struct pinctrl_dev *pctldev,
				      unsigned int group,
				      const unsigned int **pins,
				      unsigned int *num_pins)
{
	struct RTK_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	RTK_PINCTRL_DBG("[%s]", __func__);
	*pins = (unsigned int *)&pctl->groups[group].pin;
	*num_pins = 1;

	return 0;
}

static int RTK_pctrl_dt_node_to_map(struct pinctrl_dev *pctldev,
				      struct device_node *node,
				      struct pinctrl_map **map,
				      unsigned int *num_maps)
{
	struct RTK_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	unsigned long *pinconfig;
	struct property *prop;
	const char *function;
	const char *group;
	int ret, nmaps, i = 0;
	u32 val;

	RTK_PINCTRL_DBG("[%s]", __func__);

	*map = NULL;
	*num_maps = 0;

	ret = of_property_read_string(node, "realtek,function", &function);
	if (ret) {
		printk(
			"missing realtek,function property in node %s\n",
			node->name);
		return -EINVAL;
	}

	nmaps = of_property_count_strings(node, "realtek,pins") * 2;
	if (nmaps < 0) {
		printk(
			"missing realtek,pins property in node %s\n",
			node->name);
		return -EINVAL;
	}

	*map = kmalloc_array(nmaps, sizeof(struct pinctrl_map), GFP_KERNEL);
	if (!map)
		return -ENOMEM;

	of_property_for_each_string(node, "realtek,pins", prop, group) {
		struct RTK_pinctrl_group *grp =
			RTK_pinctrl_find_group_by_name(pctl, group);
		int j = 0, configlen = 0;

		if (!grp) {
			printk("unknown pin %s", group);
			continue;
		}

		if (!RTK_pinctrl_desc_find_function_by_name(pctl,
							      grp->name,
							      function)) {
			printk("unsupported function %s on pin %s",
				function, group);
			continue;
		}

		(*map)[i].type = PIN_MAP_TYPE_MUX_GROUP;
		(*map)[i].data.mux.group = group;
		(*map)[i].data.mux.function = function;

		i++;

		(*map)[i].type = PIN_MAP_TYPE_CONFIGS_GROUP;
		(*map)[i].data.configs.group_or_pin = group;

		if (of_find_property(node, "realtek,schmitt", NULL))
			configlen++;
		if (of_find_property(node, "realtek,drive", NULL))
			configlen++;
		if (of_find_property(node, "realtek,pull_en", NULL))
			configlen++;
		if (of_find_property(node, "realtek,pull_sel", NULL))
			configlen++;

		RTK_PINCTRL_DBG("[%s] configlen %d", __func__, configlen);

		if (configlen) {
			pinconfig = kcalloc(configlen,
					sizeof(*pinconfig), GFP_KERNEL);
		} else {
			/* Prevent failed to register map default*/
			configlen = 1;
			pinconfig = kzalloc(1 * sizeof(*pinconfig), GFP_KERNEL);
			pinconfig[j++] = pinconf_to_config_packed
						(PIN_CONFIG_END, 0);
		}

		if (!of_property_read_u32(node, "realtek,schmitt", &val)) {
			u16 schmitt_enable;

			if (val == 0)
				schmitt_enable = 0;
			else
				schmitt_enable = 1;

			pinconfig[j++] = pinconf_to_config_packed
					(PIN_CONFIG_INPUT_SCHMITT_ENABLE,
					schmitt_enable);
		}

		if (!of_property_read_u32(node, "realtek,drive", &val)) {
			pinconfig[j++] = pinconf_to_config_packed
					(PIN_CONFIG_DRIVE_STRENGTH, val);
		}

		if (!of_property_read_u32(node, "realtek,pull_en", &val)) {
			enum pin_config_param pull = PIN_CONFIG_END;

			if (val == 0)
				pull = PIN_CONFIG_BIAS_DISABLE;
			else if (val == 1)
				pull = PIN_CONFIG_DRIVE_PUSH_PULL;
			pinconfig[j++] = pinconf_to_config_packed(pull, 0);
		}

		if (!of_property_read_u32(node, "realtek,pull_sel", &val)) {
			enum pin_config_param pull = PIN_CONFIG_END;

			if (val == 0)
				pull = PIN_CONFIG_BIAS_PULL_DOWN;
			else if (val == 1)
				pull = PIN_CONFIG_BIAS_PULL_UP;
			pinconfig[j++] = pinconf_to_config_packed(pull, 1);
		}

		(*map)[i].data.configs.configs = pinconfig;
		(*map)[i].data.configs.num_configs = configlen;

		i++;
	}

	*num_maps = nmaps;

	return 0;
}

static void RTK_pctrl_dt_free_map(struct pinctrl_dev *pctldev,
				    struct pinctrl_map *map,
				    unsigned int num_maps)
{
	int i;

	RTK_PINCTRL_DBG("[%s]", __func__);
	for (i = 0; i < num_maps; i++) {
		if (map[i].type == PIN_MAP_TYPE_CONFIGS_GROUP)
			kfree(map[i].data.configs.configs);
	}

	kfree(map);
}

static void RTK_pctrl_dbg_show(struct pinctrl_dev *pctldev, struct seq_file *s,
			  unsigned offset)
{
	struct RTK_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct RTK_desc_function *func = rtk_pins[offset].functions;
	void __iomem *addr;
	u32 val;
	u32 mask;
	u8 pin_val;
	int is_map;

	if(pin_regmap[offset].pmux_regoff == PMUX_UNSUPPORT)
		return;

	addr = pctl->iso_membase + pin_regmap[offset].pmux_regoff;
	val = readl(addr);
	mask =pin_regmap[offset].pmux_regbitmsk << pin_regmap[offset].pmux_regbit;
	pin_val = (val & mask) >> pin_regmap[offset].pmux_regbit;

	is_map = 0;
	seq_printf(s, "function: ");
	while (func->name) {
		if (func->muxval == pin_val) {
			is_map = 1;
			seq_printf(s, "[%s] ",func->name);
		} else {
			seq_printf(s, "%s ",func->name);
		}
		func++;
	}
	if (!is_map)
		seq_printf(s, "[not defined] ");
}


static const struct pinctrl_ops RTK_pctrl_ops = {
	.dt_node_to_map		= RTK_pctrl_dt_node_to_map,
	.dt_free_map		= RTK_pctrl_dt_free_map,
	.get_groups_count	= RTK_pctrl_get_groups_count,
	.get_group_name		= RTK_pctrl_get_group_name,
	.get_group_pins		= RTK_pctrl_get_group_pins,
	.pin_dbg_show		= RTK_pctrl_dbg_show,
};

static int RTK_pconf_parse_conf(struct pinctrl_dev *pctldev,
	unsigned int pin, enum pin_config_param param,
	enum pin_config_param arg)
{
	void __iomem *addr;
	u8 set_val;
	u16 strength;
	u32 val, mask;
	struct RTK_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	RTK_PINCTRL_DBG("[%s] pin=%u, config_param=%u, config_argument=%u",
			__func__, pin, param, arg);

	if (pin_regmap[pin].pcof_regoff == PCOF_UNSUPPORT)
		return 0;
	if (pin_regmap[pin].pmux_base != PMUX_BASE_ISO)
		RTK_PINCTRL_ERR("[%s] Unknow pmux_base\n", __func__);
	addr = pctl->iso_membase + pin_regmap[pin].pcof_regoff;

	switch (param) {
	case PIN_CONFIG_INPUT_SCHMITT:
		break;
	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		set_val = arg;
		if (set_val)
			set_val = 1;
		else
			set_val = 0;

		val = readl(addr);
		mask = 1 << (pin_regmap[pin].pcof_regbit + RTK_PCONF_SCHM);
		writel(((val & ~mask)|
			(set_val <<
			(pin_regmap[pin].pcof_regbit+RTK_PCONF_SCHM))),
			addr);
		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		strength = arg;
		switch (pin_regmap[pin].pcof_cur_strgh) {
		case PADDRI_4_8:
			if (strength == 4)
				set_val = 0;
			else if (strength == 8)
				set_val = 1;
			else
				return -EINVAL;
			break;
		case PADDRI_2_4:
			if (strength == 2)
				set_val = 0;
			else if (strength == 4)
				set_val = 1;
			else
				return -EINVAL;
			break;
		case PADDRI_UNSUPPORT:
		default:
			return -EINVAL;
		}
		val = readl(addr);
		mask = 1 << (pin_regmap[pin].pcof_regbit + RTK_PCONF_CURR);
		writel(((val & ~mask)|
			(set_val <<
			(pin_regmap[pin].pcof_regbit+RTK_PCONF_CURR))),
			addr);
		break;
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		val = readl(addr);
		mask = 1 << (pin_regmap[pin].pcof_regbit + RTK_PCONF_PULEN);
		writel(((val & ~mask)|
			(1 << (pin_regmap[pin].pcof_regbit+RTK_PCONF_PULEN))),
			addr);
		break;
	case PIN_CONFIG_BIAS_DISABLE:
		val = readl(addr);
		mask = 1 << (pin_regmap[pin].pcof_regbit + RTK_PCONF_PULEN);
		writel(((val & ~mask)|
			(0 << (pin_regmap[pin].pcof_regbit+RTK_PCONF_PULEN))),
			addr);
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		val = readl(addr);
		mask = 1 << (pin_regmap[pin].pcof_regbit + RTK_PCONF_PULSEL);
		writel(((val & ~mask)|
			(1 << (pin_regmap[pin].pcof_regbit+RTK_PCONF_PULSEL))),
			addr);
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		val = readl(addr);
		mask =	1 << (pin_regmap[pin].pcof_regbit + RTK_PCONF_PULSEL);
		writel(((val & ~mask)|
			(0 << (pin_regmap[pin].pcof_regbit+RTK_PCONF_PULSEL))),
			addr);
		break;
	default:
		break;
	}

	return 0;
}

static int RTK_pconf_group_get(struct pinctrl_dev *pctldev,
				 unsigned int group,
				 unsigned long *config)
{
	struct RTK_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	RTK_PINCTRL_DBG("[%s]", __func__);
	*config = pctl->groups[group].config;

	return 0;
}

static int RTK_pconf_group_set(struct pinctrl_dev *pctldev,
				 unsigned int group,
				 unsigned long *configs,
				 unsigned int num_configs)
{
	u32 i;
	struct RTK_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct RTK_pinctrl_group *g = &pctl->groups[group];

	RTK_PINCTRL_DBG("[%s] g->pin=%d, g->name =%s, num_configs = %u",
				__func__, g->pin, g->name, num_configs);

	if (pin_regmap[g->pin].pcof_regoff == PCOF_UNSUPPORT) {
		RTK_PINCTRL_DBG(
			"[%s] g->pin(%d) g->name(%s) not support pin config"
			, __func__, g->pin, g->name);
		g->config = configs[num_configs-1];
		return 0;
	}

	for (i = 0; i < num_configs; i++) {
		RTK_pconf_parse_conf(pctldev, g->pin,
			pinconf_to_config_param(configs[i]),
			pinconf_to_config_argument(configs[i]));

		g->config = configs[i];
	}

	return 0;
}

static const struct pinconf_ops RTK_pconf_ops = {
	.pin_config_group_get	= RTK_pconf_group_get,
	.pin_config_group_set	= RTK_pconf_group_set,
};

static int RTK_pmx_get_funcs_cnt(struct pinctrl_dev *pctldev)
{
	struct RTK_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	RTK_PINCTRL_DBG("[%s] pctl->nfunctions =%d",
			__func__, pctl->nfunctions);
	return pctl->nfunctions;
}

static const char *RTK_pmx_get_func_name(struct pinctrl_dev *pctldev,
					   unsigned int function)
{
	struct RTK_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	RTK_PINCTRL_DBG("[%s] function[%d] = %s", __func__,
			function, pctl->functions[function].name);
	return pctl->functions[function].name;
}

static int RTK_pmx_get_func_groups(struct pinctrl_dev *pctldev,
				     unsigned int function,
				     const char * const **groups,
				     unsigned int * const num_groups)
{
	struct RTK_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	RTK_PINCTRL_DBG("[%s]", __func__);
	*groups = pctl->functions[function].groups;
	*num_groups = pctl->functions[function].ngroups;

	return 0;
}

static int RTK_pmx_enable(struct pinctrl_dev *pctldev,
			    unsigned int function,
			    unsigned int group)
{
	struct RTK_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct RTK_pinctrl_group *g = pctl->groups + group;
	struct RTK_pinctrl_function *func = pctl->functions + function;
	struct RTK_desc_function *desc =
		RTK_pinctrl_desc_find_function_by_name(pctl,
							 g->name,
							 func->name);
	RTK_PINCTRL_DBG("[%s] g->name=%s, func->name=%s",
				__func__, g->name, func->name);
	if (!desc)
		return -EINVAL;

	RTK_pmx_set(pctldev, g->pin, desc->muxval);

	return 0;
}

void gpio_pinctrl_control(struct gpio_chip *gc, int gpio,
	int direction, int value)
{
	struct device_node *np = gc->of_node;
	struct of_phandle_args pinspec;
	struct pinctrl_dev *pctldev;
	int ret, pin;

	ret = of_parse_phandle_with_fixed_args(np, "gpio-ranges", 3,
					0, &pinspec);
	if (ret)
		RTK_PINCTRL_ERR("Can't get pinspec");

	pctldev = of_pinctrl_get(pinspec.np);
	pin = gpio + pinspec.args[1];

	if (direction) {
		if (value == 0 || value == 1) {
			RTK_pconf_parse_conf(pctldev, pin, PIN_CONFIG_BIAS_DISABLE, 0);
		} else if (value == 2 || value == 3) {
			RTK_pconf_parse_conf(pctldev, pin,
				PIN_CONFIG_DRIVE_PUSH_PULL, 0);
			RTK_pconf_parse_conf(pctldev, pin,
				PIN_CONFIG_BIAS_PULL_UP, 0);
		} else if (value == 4 || value == 5) {
			RTK_pconf_parse_conf(pctldev, pin,
				PIN_CONFIG_DRIVE_PUSH_PULL, 0);
			RTK_pconf_parse_conf(pctldev, pin,
				PIN_CONFIG_BIAS_PULL_DOWN, 0);
		}
	} else {
		if (value == 1) {
			RTK_pconf_parse_conf(pctldev, pin,
				PIN_CONFIG_DRIVE_PUSH_PULL, 0);
			RTK_pconf_parse_conf(pctldev, pin,
				PIN_CONFIG_BIAS_PULL_UP, 0);
		} else if (value == 0) {
			RTK_pconf_parse_conf(pctldev, pin,
				PIN_CONFIG_DRIVE_PUSH_PULL, 0);
			RTK_pconf_parse_conf(pctldev, pin,
				PIN_CONFIG_BIAS_PULL_DOWN, 0);
		} else if (value == 2) {
			RTK_pconf_parse_conf(pctldev, pin,
				PIN_CONFIG_BIAS_DISABLE, 0);
		}
	}
}

static int
RTK_pmx_gpio_request_enable(struct pinctrl_dev *pctldev,
				    struct pinctrl_gpio_range *range,
				    unsigned int offset)
{
	struct RTK_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct RTK_pinctrl_group *g = pctl->groups + offset;
	struct RTK_desc_function *desc;
	const char *func;
	int ret;

	func = "gpio";
	RTK_PINCTRL_DBG("[%s] gpio_offset=%u", __func__, offset);
	desc = RTK_pinctrl_desc_find_function_by_name(pctl,
							g->name,
							func);
	if (!desc) {
		ret = -EINVAL;
		RTK_PINCTRL_ERR(
			"Set gpio pinmux fail, Pin(%s) offset=%u\n"
			, g->name, offset);
		goto error;
	}

	RTK_pmx_set(pctldev, offset, desc->muxval);

	ret = 0;

error:
	return ret;
}

static void
RTK_pmx_gpio_disable_free(struct pinctrl_dev *pctldev,
				    struct pinctrl_gpio_range *range,
				    unsigned int offset)
{
	RTK_PINCTRL_DBG("[%s]", __func__);
/*TODO : need to add gpio related api*/
}



static const struct pinmux_ops RTK_pmx_ops = {
	.get_functions_count = RTK_pmx_get_funcs_cnt,
	.get_function_name = RTK_pmx_get_func_name,
	.get_function_groups = RTK_pmx_get_func_groups,
	.set_mux = RTK_pmx_enable,
	.gpio_request_enable = RTK_pmx_gpio_request_enable,
	.gpio_disable_free = RTK_pmx_gpio_disable_free,
};

static struct pinctrl_desc RTK_pctrl_desc = {
	.confops	= &RTK_pconf_ops,
	.pctlops	= &RTK_pctrl_ops,
	.pmxops		= &RTK_pmx_ops,
};


static const struct of_device_id RTK_pinctrl_match[] = {
	{ .compatible = "realtek,rtk139x-pinctrl",
		.data = (void *)&rtk139x_pinctrl_data },
	{ /* Sentinel */ },
};
MODULE_DEVICE_TABLE(of, RTK_pinctrl_match);

static int RTK_pinctrl_add_function(struct RTK_pinctrl *pctl,
					const char *name)
{
	struct RTK_pinctrl_function *func = pctl->functions;

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

static int RTK_pinctrl_build_state(struct platform_device *pdev)
{
	struct RTK_pinctrl *pctl = platform_get_drvdata(pdev);
	int i;

	RTK_PINCTRL_DBG("[%s]", __func__);
	pctl->ngroups = pctl->desc->npins;

	/* Allocate groups */
	pctl->groups = devm_kzalloc(&pdev->dev,
				    pctl->ngroups * sizeof(*pctl->groups),
				    GFP_KERNEL);
	if (!pctl->groups)
		return -ENOMEM;

	for (i = 0; i < pctl->desc->npins; i++) {
		const struct RTK_desc_pin *pin = pctl->desc->pins + i;
		struct RTK_pinctrl_group *group = pctl->groups + i;

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
		const struct RTK_desc_pin *pin = pctl->desc->pins + i;
		struct RTK_desc_function *func = pin->functions;

		while (func->name) {
			RTK_pinctrl_add_function(pctl, func->name);
			func++;
		}
	}

	pctl->functions = krealloc(pctl->functions,
				pctl->nfunctions * sizeof(*pctl->functions),
				GFP_KERNEL);

	for (i = 0; i < pctl->desc->npins; i++) {
		const struct RTK_desc_pin *pin = pctl->desc->pins + i;
		struct RTK_desc_function *func = pin->functions;

		while (func->name) {
			struct RTK_pinctrl_function *func_item;
			const char **func_grp;

			func_item = RTK_pinctrl_find_function_by_name(pctl,
								func->name);
			if (!func_item)
				return -EINVAL;

			if (!func_item->groups) {
				func_item->groups =
					devm_kzalloc(&pdev->dev,
						func_item->ngroups *
						sizeof(*func_item->groups),
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

static int RTK_pinctrl_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	const struct of_device_id *device;
	struct pinctrl_pin_desc *pins;
	struct RTK_pinctrl *pctl;
	int i, ret;

	RTK_PINCTRL_INF("driver init");

	pctl = devm_kzalloc(&pdev->dev, sizeof(*pctl), GFP_KERNEL);
	if (!pctl)
		return -ENOMEM;
	platform_set_drvdata(pdev, pctl);

	pctl->iso_membase = of_iomap(node, 0);
	if (!pctl->iso_membase) {
		RTK_PINCTRL_ERR("of_iomap iso_membase fail");
		return -ENOMEM;
	}

	RTK_PINCTRL_DBG("iso_membase(0x%p)", pctl->iso_membase);

	device = of_match_device(RTK_pinctrl_match, &pdev->dev);
	if (!device) {
		RTK_PINCTRL_ERR("of_match_device fail");
		return -ENODEV;
	}

	pctl->desc = (struct RTK_pinctrl_desc *)device->data;

	ret = RTK_pinctrl_build_state(pdev);
	if (ret) {
		RTK_PINCTRL_ERR("RTK_pinctrl_build_state fail");
		return ret;
	}

	pins = devm_kzalloc(&pdev->dev,
			    pctl->desc->npins * sizeof(*pins),
			    GFP_KERNEL);
	if (!pins) {
		RTK_PINCTRL_ERR("[%s]devm_kzalloc fail", __func__);
		return -ENOMEM;
	}

	for (i = 0; i < pctl->desc->npins; i++)
		pins[i] = pctl->desc->pins[i].pin;

	RTK_pctrl_desc.name = dev_name(&pdev->dev);
	RTK_pctrl_desc.owner = THIS_MODULE;
	RTK_pctrl_desc.pins = pins;
	RTK_pctrl_desc.npins = pctl->desc->npins;
	pctl->dev = &pdev->dev;
	pctl->pctl_dev = pinctrl_register(&RTK_pctrl_desc,
					  &pdev->dev, pctl);
	if (!pctl->pctl_dev) {
		RTK_PINCTRL_ERR("register pinctrl driver fail");
		return -EINVAL;
	}

	RTK_PINCTRL_INF("init done");

	return 0;
}

int RTK_pinctrl_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct RTK_pinctrl *pctl;
	void __iomem *addr;
	unsigned int i;
#ifdef CONFIG_RTK_XEN_SUPPORT
	if (xen_domain() && !xen_initial_domain()) {
		RTK_PINCTRL_INF("skip %s under DomU", __func__);
		return 0;
	}
#endif
	RTK_PINCTRL_INF("Enter %s", __func__);

	pctl = platform_get_drvdata(pdev);

	pinctrl_reg_values = kcalloc(ARRAY_SIZE(pinmux_reg_list), sizeof(u32),
				GFP_KERNEL);

	for (i = 0; i < ARRAY_SIZE(pinmux_reg_list); i++) {
		if (pinmux_reg_list[i].reg_base != PMUX_BASE_ISO)
			RTK_PINCTRL_ERR("[%s] Unknow pmux_base\n", __func__);
		addr = pctl->iso_membase + pinmux_reg_list[i].reg_offset;
		/*Store pinmux registers*/
		pinctrl_reg_values[i] = readl(addr);
	}

	RTK_PINCTRL_INF("Exit %s", __func__);
	return 0;
}

int RTK_pinctrl_resume(struct platform_device *pdev)
{
	struct RTK_pinctrl *pctl;
	void __iomem *addr;
	unsigned int i;

#ifdef CONFIG_RTK_XEN_SUPPORT
	if (xen_domain() && !xen_initial_domain()) {
		RTK_PINCTRL_INF("skip %s under DomU", __func__);
		return 0;
	}
#endif
	RTK_PINCTRL_INF("Enter %s", __func__);

	pctl = platform_get_drvdata(pdev);

	for (i = 0; i < ARRAY_SIZE(pinmux_reg_list); i++) {
		if (pinmux_reg_list[i].reg_base != PMUX_BASE_ISO)
			RTK_PINCTRL_ERR("[%s] Unknow pmux_base\n", __func__);
		addr = pctl->iso_membase + pinmux_reg_list[i].reg_offset;
		/*Restore pinmux registers*/
		writel(pinctrl_reg_values[i], addr);
	}

	kfree(pinctrl_reg_values);

	RTK_PINCTRL_INF("Exit %s", __func__);
	return 0;
}

static struct platform_driver RTK_pinctrl_driver = {
	.probe = RTK_pinctrl_probe,
	.driver = {
		.name = "rtk-pinctrl",
		.owner = THIS_MODULE,
		.of_match_table = RTK_pinctrl_match,
	},
	.suspend = RTK_pinctrl_suspend,
	.resume = RTK_pinctrl_resume,
};

static int  rtk_pinctrl_init(void)
{
	return platform_driver_register(&RTK_pinctrl_driver);
}
postcore_initcall(rtk_pinctrl_init);

MODULE_DESCRIPTION("RTK pinctrl driver");
MODULE_LICENSE("GPL");
