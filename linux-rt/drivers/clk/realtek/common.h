/*
 * common.h - Realtek Clock Common
 *
 * Copyright (C) 2016-2018 Realtek Semiconductor Corporation
 * Copyright (C) 2016-2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __CLK_REALTEK_COMMON_H
#define __CLK_REALTEK_COMMON_H

#include <linux/bitops.h>
#include <linux/clk-provider.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/regmap.h>

/**
 * struct clk_reg - a clk core with hardware register access, which is provided
 * ether a direct regsiter or a regmap register access. The regmap provides a
 * safe register aceess, when the registers are shared by modules or firmwares.
 *
 * @hw:             handle between common and hardware-specific interfaces
 * @flags:          clk_reg flags
 * @reg:            a pointor for direct register access
 * @regmap:         a remap for register access, which provides safe register
 *                  aceess
 * @offset:         the offset between @regmap and @reg
 * @private_offset: valid if flags CLK_REG_FAST_ACCESS configured. indicates
 *                  the bonadary of shared registers. When the offset is above
 *                  private_offset, access the register directly, instead of
 *                  using regmap.
 *
 * Flags:
 * CLK_REG_FAST_ACCESS - use fast access
 */
struct clk_reg {
	struct clk_hw hw;
	unsigned long flags;
	void __iomem *reg;
	struct regmap *regmap;
	int offset;
	int private_offset;
};

#define to_clk_reg(_hw) container_of(_hw, struct clk_reg, hw)
#define __clk_reg_hw(_ptr)  ((_ptr)->hw)

#define CLK_REG_INIT()  {{}, 0, 0, 0, 0, 0 }

/* flags */
#define CLK_REG_FAST_ACCESS    BIT(3)


static inline bool of_clk_is_ignore_unused(struct device_node *np,
	const char *name)
{
	return of_property_match_string(np, "ignore-unused-clocks", name) >= 0;
}

static inline bool of_clk_is_ignore_pm(struct device_node *np,
	const char *name)
{
	return of_property_match_string(np, "ignore-pm-clocks", name) >= 0;
}

static inline bool of_clk_is_invalid(struct device_node *np,
	const char *name)
{
	return of_property_match_string(np, "invalid-clocks", name) >= 0;
}

/**
 * struct clk_reg_init_data - init data of clk_reg
 */
struct clk_reg_init_data {
	unsigned long flags;
	void __iomem *reg;
	struct regmap *regmap;
	int offset;
	int private_offset;
};

static inline void clk_reg_init(struct clk_reg *b, struct clk_reg_init_data *i)
{
	b->flags = i->flags;
	b->regmap = i->regmap;
	b->reg = i->reg;
	b->offset = i->offset;
	b->private_offset = i->private_offset;
}

static inline bool clk_reg_offset_is_shared(struct clk_reg *b,
	unsigned int offset)
{
	if (!(b->flags & CLK_REG_FAST_ACCESS))
		return true;
	if ((b->offset + offset) < b->private_offset)
		return true;
	return false;
}

static inline void clk_reg_write(struct clk_reg *b, unsigned int offset,
	unsigned int val)
{
	if (b->regmap && clk_reg_offset_is_shared(b, offset))
		regmap_write(b->regmap, b->offset + offset, val);
	else if (b->reg)
		writel(val, b->reg + offset);
	else
		WARN_ON(1);
}

static inline unsigned int clk_reg_read(struct clk_reg *b, unsigned int offset)
{
	unsigned int val = 0;

	if (b->regmap && clk_reg_offset_is_shared(b, offset))
		regmap_read(b->regmap, b->offset + offset, &val);
	else if (b->reg)
		val = readl(b->reg + offset);
	else
		WARN_ON(1);
	return val;
}

static inline void clk_reg_update(struct clk_reg *b, unsigned int offset,
	unsigned int mask, unsigned int val)
{
	if (b->regmap && clk_reg_offset_is_shared(b, offset)) {
		regmap_update_bits(b->regmap, b->offset + offset, mask, val);
	} else if (b->reg) {
		unsigned int rval;

		rval = readl(b->reg + offset);
		rval = (rval & ~mask) | (val & mask);
		writel(rval, b->reg + offset);
	} else {
		WARN_ON(1);
	}
}

/* offset check */
#define CLK_OFFSET_INVALID  -1
#define CLK_OFFSET_IS_VALID(_off)    ((_off) != CLK_OFFSET_INVALID)

/**
 * struct clk_composite_init_data - init data of clk_reg type composite clock.
 *
 * init data for registering an internal clk_mmio_gate
 * @gate_offset
 * @gate_shift
 * @gate_flags
 *
 * init data for registering an internal clk_mmio_mux
 * @mux_offset
 * @mux_width
 * @mux_width
 * @parent_names
 * @num_parents
 *
 * - common
 * @flags:  clk flags
 * @name:   name of a clk
 * @clk:    the registered clk
 */
struct clk_composite_init_data {
	int gate_offset;
	int gate_shift;
	unsigned int gate_flags;
	int mux_offset;
	int mux_width;
	int mux_shift;
	const char **parent_names;
	int num_parents;
	unsigned long flags;
	const char *name;
	struct clk *clk;
};

#ifdef CONFIG_COMMON_CLK_REALTEK_DEBUG
bool is_clk_debug_enabled(void);
#else /* !CONFIG_COMMON_CLK_REALTEK_DEBUG */
static inline bool is_clk_debug_enabled(void)
{
	return false;
}
#endif /* CONFIG_COMMON_CLK_REALTEK_DEBUG */

/**
 * struct clk_pm_data - for saving clk pm state
 *
 * @clk         pointer to the struct clk
 * @flags:      indicates the field(s) to save
 * @parent:     saved parent for clk_mux
 * @rate:       saved rate for clk_rate
 * @enable_cnt: saved enable count for clk_gate
 *
 * Flags:
 * CLK_PM_SUSPEND_RATE   - save clk_rate when suspending
 * CLK_PM_SUSPEND_PARENT - save clk_parent when suspending
 * CLK_PM_SUSPEND_ENABLE - save clk_enable_cnt when suspending
 */
struct clk_pm_data {
	struct clk *clk;
	unsigned int flags;
	struct clk *parent;
	unsigned long rate;
	int enable_cnt;
};

#define CLK_PM_SUSPEND_RATE     BIT(0)
#define CLK_PM_SUSPEND_PARENT   BIT(1)
#define CLK_PM_SUSPEND_ENABLE   BIT(2)

#ifdef CONFIG_PM
int clk_pm_init(struct clk *clk, struct clk_pm_data *pm_data,
	unsigned int pm_flags);
int clk_pm_data_save(struct clk_pm_data *pm_data);
int clk_pm_data_restore(struct clk_pm_data *pm_data);
#else /* CONFIG_PM */
static inline int clk_pm_init(struct clk *clk, struct clk_pm_data *pm_data,
	unsigned int pm_flags)
{
	return 0;
}

static inline int clk_pm_data_save(struct clk_pm_data *pm_data)
{
	return 0;
}

static inline int clk_pm_data_restore(struct clk_pm_data *pm_data)
{
	return 0;
}
#endif /* CONFIG_PM */

/**
 * struct cc_desc - description of clock controller
 *
 * @init_data      init data of clk_reg
 * @data           onecell data of clock provider
 * @pm_data        data of clk_pm
 */
struct cc_desc {
	struct clk_reg_init_data init_data;
	struct clk_onecell_data data;
#ifdef CONFIG_PM
	struct clk_pm_data *pm_data;
#endif
};

static inline struct cc_desc *devm_cc_alloc(struct device *dev, int max_clk)
{
	struct cc_desc *ccd;

	ccd = devm_kzalloc(dev, sizeof(*ccd), GFP_KERNEL);
	if (!ccd)
		return NULL;

	ccd->data.clk_num = max_clk;
	ccd->data.clks = devm_kcalloc(dev, max_clk,
		sizeof(*ccd->data.clks), GFP_KERNEL);
	if (!ccd->data.clks)
		return NULL;
#ifdef CONFIG_PM
	ccd->pm_data = devm_kcalloc(dev, max_clk,
		sizeof(*ccd->pm_data), GFP_KERNEL);
	if (!ccd->pm_data)
		return NULL;
#endif
	return ccd;
}

int cc_init_hw(struct device *dev, struct cc_desc *ccd, int cc_index,
	struct clk_hw *hw);
int cc_init_composite_clk(struct device *dev, struct cc_desc *ccd,
	int cc_index, struct clk_composite_init_data *init);

/*
 * platform specific functions
 */

/**
 * cc_init_clocks - platform specific init function, should init data and
 *                  pm_data in cc_desc for platform driver.
 *
 * @dev - deivce of cc with cc_desc in drvier data
 */
int cc_init_clocks(struct device *dev);

/**
 * cc_clock_num - returns clock number in the platform cc
 */
int cc_clock_num(void);

#endif /* __CLK_REALTEK_COMMON_H */

