/*
 * This file is based on 'drivers/base/regmap/regmap-mmio.c'
 *
 * Copyright (c) 2018, Realtek Semiconductor Corporation
 *
 * Author:
 *      Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/err.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <linux/arm-smccc.h>
#include <soc/realtek/rtk_regmap.h>

#define RTK_REGMAP_NAME_LENGTH          30

struct rtk_regmap_mmio_context {
	void __iomem *regs;
	const struct secure_register_desc *descs;
	u32 num_descs;
	u32 addr;
	char name[RTK_REGMAP_NAME_LENGTH];
};

enum {
	SWC_READ,
	SWC_WRITE,
};

#ifdef CONFIG_RTK_REGMAP_SECURE_MMIO

static void swc_write(struct rtk_regmap_mmio_context *ctx,
		      const struct secure_register_desc *desc,
		      u32 val)
{
	struct arm_smccc_res res;

	switch (desc->fmt) {
	case SMCCC_FMT_CMD:
		arm_smccc_smc(desc->wcmd, val, 0, 0, 0, 0, 0, 0, &res);
		break;
	case SMCCC_FMT_CMD_PHYS:
		arm_smccc_smc(desc->wcmd, ctx->addr + desc->offset, val, 0, 0,
			0, 0, 0, &res);
		break;
	}
}

static u32 swc_read(struct rtk_regmap_mmio_context *ctx,
		    const struct secure_register_desc *desc)
{
	struct arm_smccc_res res;

	switch (desc->fmt) {
	case SMCCC_FMT_CMD:
		arm_smccc_smc(desc->rcmd, 0, 0, 0, 0, 0, 0, 0, &res);
		break;
	case SMCCC_FMT_CMD_PHYS:
		arm_smccc_smc(desc->rcmd, ctx->addr + desc->offset, 0, 0, 0, 0,
			0, 0, &res);
		break;
	}
	return res.a0;
}

static const
struct secure_register_desc *find_desc(struct rtk_regmap_mmio_context *ctx,
				       u32 reg,
				       u32 type)
{
	u32 i;

	if (!ctx->descs)
		return NULL;

	for (i = 0; i < ctx->num_descs; i++) {
		const struct secure_register_desc *desc = &ctx->descs[i];

		if (desc->offset == reg) {
			switch (type) {
			case SWC_READ:
				return desc->rcmd ? desc : NULL;
			case SWC_WRITE:
				return desc->wcmd ? desc : NULL;
			default:
				return NULL;
			}
		}
	}
	return NULL;
}

#else

static void swc_write(struct rtk_regmap_mmio_context *ctx,
		      const struct secure_register_desc *desc,
		      u32 val)
{
	BUG();
}

static u32 swc_read(struct rtk_regmap_mmio_context *ctx,
		    const struct secure_register_desc *desc)
{
	BUG();
	return 0;
}

static inline const
struct secure_register_desc *find_desc(struct rtk_regmap_mmio_context *ctx,
				       u32 reg,
				       u32 type)
{
	return NULL;
}

#endif /* CONFIG_RTK_REGMAP_SECURE_MMIO */

static int rtk_regmap_mmio_write(void *context,
				 unsigned int reg,
				 unsigned int val)
{
	struct rtk_regmap_mmio_context *ctx = context;
	const struct secure_register_desc *desc = NULL;

	desc = find_desc(ctx, reg, SWC_WRITE);
	pr_debug("%s: type=W, off=%03x, val=%08x, flag=%c\n",
		ctx->name, reg, val, desc != NULL ? 'S' : '-');
	if (desc)
		swc_write(ctx, desc, val);
	else
		writel(val, ctx->regs + reg);
	return 0;
}

static int rtk_regmap_mmio_read(void *context,
				unsigned int reg,
				unsigned int *val)
{
	struct rtk_regmap_mmio_context *ctx = context;
	const struct secure_register_desc *desc = NULL;

	desc = find_desc(ctx, reg, SWC_READ);
	if (desc)
		*val = swc_read(ctx, desc);
	else
		*val = readl(ctx->regs + reg);
	pr_debug("%s: type=R, off=%03x, val=%08x, flag=%c\n",
		ctx->name, reg, *val, desc != NULL ? 'S' : '-');
	return 0;
}

static void rtk_regmap_mmio_free_context(void *context)
{
	struct rtk_regmap_mmio_context *ctx = context;

	kfree(ctx->descs);
	kfree(ctx);
}

static const struct regmap_bus rtk_regmap_mmio = {
	.fast_io      = true,
	.reg_write    = rtk_regmap_mmio_write,
	.reg_read     = rtk_regmap_mmio_read,
	.free_context = rtk_regmap_mmio_free_context,
};

static struct rtk_regmap_mmio_context *
regmap_mmio_gen_context(struct device *dev,
			void __iomem *regs,
			const struct regmap_config *config)
{
	struct rtk_regmap_mmio_context *ctx;

	BUG_ON(config->reg_bits != 32);
	BUG_ON(config->pad_bits);
	BUG_ON(config->reg_stride != 4);

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return ERR_PTR(-ENOMEM);

	if (config->name)
		strlcpy(ctx->name, config->name, sizeof(ctx->name));
	ctx->regs = regs;

	return ctx;
}

struct regmap *__rtk_regmap_init_mmio(struct device *dev,
				      void __iomem *regs,
				      const struct regmap_config *config,
				      struct lock_class_key *lock_key,
				      const char *lock_name)
{
	struct rtk_regmap_mmio_context *ctx;

	ctx = regmap_mmio_gen_context(dev, regs, config);
	if (IS_ERR(ctx))
		return ERR_CAST(ctx);

	return __regmap_init(dev, &rtk_regmap_mmio, ctx, config, lock_key,
		lock_name);
}
EXPORT_SYMBOL_GPL(__rtk_regmap_init_mmio);

struct regmap *__devm_rtk_regmap_init_mmio(struct device *dev,
					   void __iomem *regs,
					   const struct regmap_config *config,
					   struct lock_class_key *lock_key,
					   const char *lock_name)
{
	struct rtk_regmap_mmio_context *ctx;

	ctx = regmap_mmio_gen_context(dev, regs, config);
	if (IS_ERR(ctx))
		return ERR_CAST(ctx);

	return __devm_regmap_init(dev, &rtk_regmap_mmio, ctx, config,
		lock_key, lock_name);
}
EXPORT_SYMBOL_GPL(__devm_rtk_regmap_init_mmio);

static struct rtk_regmap_mmio_context *
regmap_secure_mmio_gen_context(struct device *dev,
			       void __iomem *regs,
			       const struct rtk_regmap_config *config)
{
	struct rtk_regmap_mmio_context *ctx;

	ctx = regmap_mmio_gen_context(dev, regs, &config->config);
	if (IS_ERR(ctx))
		return ctx;
	if (!config->config.name)
		snprintf(ctx->name, sizeof(ctx->name), "regmap-mmio.%x",
			config->addr);

	ctx->addr = config->addr;
	ctx->num_descs = config->num_descs;
	ctx->descs = kmemdup(config->descs,
		sizeof(*config->descs) * config->num_descs, GFP_KERNEL);
	if (!ctx->descs) {
		rtk_regmap_mmio_free_context(ctx);
		return ERR_PTR(-ENOMEM);
	}

	return ctx;
}

struct regmap *
__rtk_regmap_init_secure_mmio(struct device *dev,
			      void __iomem *regs,
			      const struct rtk_regmap_config *config,
			      struct lock_class_key *lock_key,
			      const char *lock_name)
{
	struct rtk_regmap_mmio_context *ctx;

	ctx = regmap_secure_mmio_gen_context(dev, regs, config);
	if (IS_ERR(ctx))
		return ERR_CAST(ctx);

	return __regmap_init(dev, &rtk_regmap_mmio, ctx, &config->config,
		lock_key, lock_name);
}
EXPORT_SYMBOL_GPL(__rtk_regmap_init_secure_mmio);

struct regmap *
__devm_rtk_regmap_init_secure_mmio(struct device *dev,
				   void __iomem *regs,
				   const struct rtk_regmap_config *config,
				   struct lock_class_key *lock_key,
				   const char *lock_name)
{
	struct rtk_regmap_mmio_context *ctx;

	ctx = regmap_secure_mmio_gen_context(dev, regs, config);
	if (IS_ERR(ctx))
		return ERR_CAST(ctx);

	return __devm_regmap_init(dev, &rtk_regmap_mmio, ctx, &config->config,
		lock_key, lock_name);
}
EXPORT_SYMBOL_GPL(__devm_rtk_regmap_init_secure_mmio);

MODULE_LICENSE("GPL v2");
