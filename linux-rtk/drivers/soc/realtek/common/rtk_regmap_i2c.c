/*
 * rtk_regmap_i2c.c - Realtek Regmap I2C bus
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/regmap.h>
#include <linux/i2c.h>

#define to_bytep(_p)  ((unsigned char *)(_p))

static int rtk_regmap_i2c_write(void *context, const void *data, size_t count)
{
	struct i2c_client *i2c = context;
	int ret = 0;

	pr_debug("%s: reg = %02x val = %02x\n", __func__,
		to_bytep(data)[0], to_bytep(data)[1]);

	ret = i2c_master_send(i2c, data, count);

	if (ret == count)
		return 0;
	else if (ret < 0)
		return ret;
	else
		return -EIO;
}

static int rtk_regmap_i2c_read(void *context, const void *reg, size_t reg_size,
	void *val, size_t val_size)
{
	struct i2c_client *i2c = context;
	unsigned char _reg = *(unsigned char *)reg;
	struct i2c_msg xfer[2];
	int ret = 0;

	xfer[0].addr = i2c->addr;
	xfer[0].flags = 0;
	xfer[0].len = reg_size;
	xfer[0].buf = &_reg;

	xfer[1].addr = i2c->addr;
	xfer[1].flags = I2C_M_RD;
	xfer[1].len = val_size;
	xfer[1].buf = val;

	ret = i2c_transfer(i2c->adapter, xfer, 2);

	pr_debug("%s: reg = %02x val = %02x ret = %d\n", __func__,
		_reg, to_bytep(val)[0], ret);

	if (ret == 2)
		return 0;
	else if (ret < 0)
		return ret;
	else
		return -EIO;
}

static struct regmap_bus rtk_regmap_regmap_bus = {
	.write = rtk_regmap_i2c_write,
	.read  = rtk_regmap_i2c_read,
};

struct regmap *devm_rtk_regmap_i2c_init(struct device *dev,
	struct i2c_client *client, const struct regmap_config *config)
{
	return devm_regmap_init(dev, &rtk_regmap_regmap_bus, client, config);
}
EXPORT_SYMBOL_GPL(devm_rtk_regmap_i2c_init);
