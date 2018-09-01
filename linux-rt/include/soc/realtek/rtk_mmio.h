/*
 * rtk_mmio.h -  Realtek Regmap-MMIO API.
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __SOC_REALTEK_MMIO_H
#define __SOC_REALTEK_MMIO_H

#include <linux/regmap.h>

struct device_node;

#ifdef CONFIG_RTK_MMIO
struct regmap *rtk_mmio_node_to_regmap(struct device_node *np);
#else
static inline struct regmap *rtk_mmio_node_to_regmap(struct device_node *np)
{
	return ERR_PTR(-ENOENT);
}
#endif

static inline struct regmap *of_get_rtk_mmio_regmap_with_offset(
	const struct device_node *np, int index, int *offset)
{
	struct of_phandle_args args;
	int ret;

	ret = of_parse_phandle_with_fixed_args(np, "realtek,mmio", 1,
		index, &args);
	if (ret)
		return ERR_PTR(ret);

	if (offset)
		*offset = args.args[0];

	return rtk_mmio_node_to_regmap(args.np);
}

static inline struct regmap *of_get_rtk_mmio_regmap(
	const struct device_node *np, int index)
{
	return of_get_rtk_mmio_regmap_with_offset(np, index, NULL);
}

#endif /* __SOC_REALTEK_RTD129X_MMIO_H */

