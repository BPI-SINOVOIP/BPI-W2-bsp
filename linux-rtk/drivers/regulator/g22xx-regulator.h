/*
 * g22xx-regulator.h - GMT-G22xx series Regulator
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __G22XX_REGULATOR_H__
#define __G22XX_REGULATOR_H__

#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regmap.h>
#include <linux/bitops.h>

struct g22xx_device {
	struct i2c_client *client;
	struct device *dev;
	struct regmap *regmap;
	struct regmap_field **maps;
};

struct g22xx_desc {
	struct regulator_desc desc;
	unsigned int flags;

	struct regmap_field *on;
	struct regmap_field *nvo;
	struct regmap_field *svo;
	struct regmap_field *nmode;
	struct regmap_field *smode;

	struct regulator_state state_mem;
	struct regulator_state state_coldboot;
	struct regulator_dev *rdev;

	int delay_volt_up;
};

#define to_g22xx_desc(_desc) container_of(_desc, struct g22xx_desc, desc)

/* flags */
#define G22XX_FLAG_TYPE_LDO   BIT(0)

#define G22XX_DESC(_id, _name, _vtbl) {      \
	.owner       = THIS_MODULE,          \
	.id          = _id,                  \
	.name        = _name,                \
	.ops         = &g22xx_regulator_ops, \
	.type        = REGULATOR_VOLTAGE,    \
	.of_match    = _name,                \
	.of_parse_cb = g22xx_of_parse_cb,    \
	.volt_table  = _vtbl,                \
	.n_voltages  = ARRAY_SIZE(_vtbl),    \
}

static inline const char *g22xx_desc_name(struct g22xx_desc *gd)
{
	return gd->desc.name;
}

static inline int g22xx_is_ldo(struct g22xx_desc *gd)
{
	return !!(gd->flags & G22XX_FLAG_TYPE_LDO);
}

struct g22xx_desc_initdata {
	const struct reg_field *regs;
	int idx_on;
	int idx_nvo;
	int idx_svo;
	int idx_nmode;
	int idx_smode;
};

#define G22XX_REG_FIELD_INVALID -1

#define G22XX_DESC_INITDATA(_chip, _name, _regs) { \
	.regs      = _regs, \
	.idx_on    = _chip ## _REG_FIELD_ ## _name ## _ON, \
	.idx_nvo   = _chip ## _REG_FIELD_ ## _name ## _NVO, \
	.idx_svo   = _chip ## _REG_FIELD_ ## _name ## _SVO, \
	.idx_nmode = _chip ## _REG_FIELD_ ## _name ## _NMODE, \
	.idx_smode = _chip ## _REG_FIELD_ ## _name ## _SMODE, \
}

#define G22XX_DESC_INITDATA_NO_VO(_chip, _name, _regs) { \
	.regs      = regs, \
	.idx_on    = _chip ## _REG_FIELD_ ## _name ## _ON, \
	.idx_nvo   = G22XX_REG_FIELD_INVALID, \
	.idx_svo   = G22XX_REG_FIELD_INVALID, \
	.idx_nmode = _chip ## _REG_FIELD_ ## _name ## _NMODE, \
	.idx_smode = _chip ## _REG_FIELD_ ## _name ## _SMODE, \
}

int g22xx_of_parse_cb(struct device_node *np, const struct regulator_desc *desc,
	struct regulator_config *config);
extern const struct regulator_ops g22xx_regulator_ops;
void g22xx_prepare_suspend_state(struct regulator_dev *rdev, int is_coldboot);
int g22xx_regulator_register(struct g22xx_device *gdev, struct g22xx_desc *gd,
	struct g22xx_desc_initdata *data);
int g22xx_setup_pm_power_off(struct device *dev, struct regmap_field *map);
bool g22xx_regcache_disabled(void);

#endif
