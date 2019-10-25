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

#include <linux/regmap.h>
struct i2c_client;

/* i2c api */
struct regmap *__rtk_regmap_init_i2c(struct i2c_client *client,
				     const struct regmap_config *config,
				     struct lock_class_key *lock_key,
				     const char *lock_name);
struct regmap *__devm_rtk_regmap_init_i2c(struct i2c_client *client,
					  const struct regmap_config *config,
					  struct lock_class_key *lock_key,
					  const char *lock_name);

#define rtk_regmap_init_i2c(client, config)                             \
	__regmap_lockdep_wrapper(__rtk_regmap_init_i2c, #config,        \
		client, config)
#define devm_rtk_regmap_init_i2c(client, config)                        \
	__regmap_lockdep_wrapper(__devm_rtk_regmap_init_i2c, #config,	\
		client, config)

/* mmio api */
struct regmap *__rtk_regmap_init_mmio(struct device *dev,
				      void __iomem *regs,
				      const struct regmap_config *config,
				      struct lock_class_key *lock_key,
				      const char *lock_name);
struct regmap *__devm_rtk_regmap_init_mmio(struct device *dev,
					   void __iomem *regs,
					   const struct regmap_config *config,
					   struct lock_class_key *lock_key,
					   const char *lock_name);

#define rtk_regmap_init_mmio(dev, regs, config)                         \
	__regmap_lockdep_wrapper(__rtk_regmap_init_mmio, #config,       \
		dev, regs, config)
#define devm_rtk_regmap_init_mmio(dev, regs, config)                    \
	__regmap_lockdep_wrapper(__devm_rtk_regmap_init_mmio, #config,	\
		dev, regs, config)

/* secure mmio api */
enum {
	SMCCC_FMT_CMD,
	SMCCC_FMT_CMD_PHYS,
};

struct secure_register_desc {
	u32 offset;
	u32 wcmd;
	u32 rcmd;
	u32 fmt;
};

#define REG_DESC_OFFSET_INVALID  0xffffffff
#define DEFINE_REG_SMCCC(_off, _w, _r) \
	{ .offset = _off, .wcmd = _w, .rcmd = _r, .fmt = SMCCC_FMT_CMD, }
#define DEFINE_REG_SMCCC_PHYS(_off, _w, _r) \
	{ .offset = _off, .wcmd = _w, .rcmd = _r, .fmt = SMCCC_FMT_CMD_PHYS, }
#define DEFINE_REG_INVALID \
	{ .offset = REG_DESC_OFFSET_INVALID, }

struct rtk_regmap_config {
	struct regmap_config config;
	const struct secure_register_desc *descs;
	u32 num_descs;
	u32 addr;
};

struct regmap *__rtk_regmap_init_secure_mmio(struct device *dev,
					     void __iomem *regs,
					     const struct rtk_regmap_config *config,
					     struct lock_class_key *lock_key,
					     const char *lock_name);
struct regmap *__devm_rtk_regmap_init_secure_mmio(struct device *dev,
						  void __iomem *regs,
						  const struct rtk_regmap_config *config,
						  struct lock_class_key *lock_key,
						  const char *lock_name);

#define rtk_regmap_init_secure_mmio(dev, regs, config)                        \
	__regmap_lockdep_wrapper(__rtk_regmap_init_secure_mmio, #config,      \
		dev, regs, config)
#define devm_rtk_regmap_init_secure_mmio(dev, regs, config)                   \
	__regmap_lockdep_wrapper(__devm_rtk_regmap_init_secure_mmio, #config, \
		dev, regs, config)


#endif
