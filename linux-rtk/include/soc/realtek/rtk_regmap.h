/*
 * rtk_regmap.h - Realtek Regmap API
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __SOC_REALTEK_REGMAP_H
#define __SOC_REALTEK_REGMAP_H

struct i2c_client;

#ifdef CONFIG_RTK_REGMAP_I2C
struct regmap *devm_rtk_regmap_i2c_init(struct device *dev,
	struct i2c_client *client, const struct regmap_config *config);
#else /* !CONFIG_RTK_REGMAP_I2C */
static struct regmap *devm_rtk_regmap_i2c_init(struct device *dev,
	struct i2c_client *client, const struct regmap_config *config)
{
	return ERR_PTR(-ENOENT);
}
#endif /* CONFIG_RTK_REGMAP_I2C */

#endif
