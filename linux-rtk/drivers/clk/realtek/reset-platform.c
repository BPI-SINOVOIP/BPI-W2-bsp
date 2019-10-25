/*
 * reset-platform.c - Realtek Reset Controller platform code
 *
 * Copyright (C) 2019 Realtek Semiconductor Corporation
 *
 * Author:
 *	Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/pm.h>
#include <linux/regmap.h>
#include <linux/reset.h>
#include <linux/reset-controller.h>
#include <linux/slab.h>
#include <linux/suspend.h>
#include <soc/realtek/rtk_mmio.h>
#include <dt-bindings/reset/rtk,reset.h>
#include <soc/realtek/rtk_chip.h>
#include "common.h"
#include "reset.h"

static inline u32 bits_to_set(struct rc_reg_desc *reg, u32 bits_to_set)
{
	return bits_to_set * (reg->write_en ? 3 : 1);
}

static inline u32 bits_to_clear(struct rc_reg_desc *reg, u32 bits_to_clear)
{
	return reg->write_en ? (bits_to_clear << 1) : 0;
}

static inline u32 bits_to_mask(struct rc_reg_desc *reg, u32 bits)
{
	return bits_to_set(reg, bits);
}

static inline u32 rc_reg_read(struct rc_platform_data *data,
			      struct rc_reg_desc *reg)
{
	u32 val = 0;

	if (data->regmap)
		regmap_read(data->regmap, data->offset + reg->offset, &val);
	else if (data->reg)
		val = readl(data->reg + reg->offset);
	else
		WARN_ON_ONCE(1);
	return val;
}

static inline void rc_reg_update_bits(struct rc_platform_data *data,
				      struct rc_reg_desc *reg,
				      u32 mask,
				      u32 val)
{
	dev_dbg(data->dev, "%s: offset=%03x: flags=%c, mask=%08x, val=%08x\n",
		__func__, reg->offset, reg->write_en ? 'w' : '-', mask, val);
	if (data->regmap) {
		regmap_update_bits(data->regmap, data->offset + reg->offset,
				   mask, val);
	} else if (data->reg) {
		unsigned int rval;

		rval = readl(data->reg + reg->offset);
		rval = (rval & ~mask) | (val & mask);
		writel(rval, data->reg + reg->offset);
	} else
		WARN_ON_ONCE(1);
}

static int rc_reset_assert(struct reset_controller_dev *rcdev,
			   unsigned long id)
{
	struct rc_platform_data *data = to_rc_platform_data(rcdev);
	struct rc_reg_desc *reg = &data->desc[RC_DESC_ID(id)];
	u32 val, mask;

	mask = bits_to_mask(reg, RC_RESET_BIT_MASK(id));
	val  = bits_to_clear(reg, RC_RESET_BIT_MASK(id));
	rc_reg_update_bits(data, reg, mask, val);
	return 0;
}

static int rc_reset_deassert(struct reset_controller_dev *rcdev,
			     unsigned long id)
{
	struct rc_platform_data *data = to_rc_platform_data(rcdev);
	struct rc_reg_desc *reg = &data->desc[RC_DESC_ID(id)];
	u32 val, mask;

	mask = bits_to_mask(reg, RC_RESET_BIT_MASK(id));
	val = bits_to_set(reg, RC_RESET_BIT_MASK(id));
	rc_reg_update_bits(data, reg, mask, val);
	return 0;
}

static int rc_reset_reset(struct reset_controller_dev *rcdev,
			  unsigned long id)
{
	int ret;

	ret = rc_reset_assert(rcdev, id);
	if (ret)
		return ret;
	return rc_reset_deassert(rcdev, id);
}

static int rc_reset_status(struct reset_controller_dev *rcdev,
			   unsigned long id)
{
	struct rc_platform_data *data = to_rc_platform_data(rcdev);
	struct rc_reg_desc *reg = &data->desc[RC_DESC_ID(id)];
	u32 val = 0;

	val = rc_reg_read(data, reg);
	return !(val & RC_RESET_BIT_MASK(id));
}

static struct reset_control_ops rc_ops = {
	.assert   = rc_reset_assert,
	.deassert = rc_reset_deassert,
	.reset    = rc_reset_reset,
	.status   = rc_reset_status,
};

static int rc_suspend(struct device *dev)
{
	struct rc_platform_data *data = dev_get_drvdata(dev);
	struct rc_reg_desc *desc;
	int i;

	dev_info(dev, "enter %s\n", __func__);
	for (i = 0; i < data->num_desc; i++) {
		desc = &data->desc[i];

		if (rc_is_invalid(desc))
			continue;

		desc->pm_data = rc_reg_read(data, desc);
		dev_info(dev, "%03x: suspend_val=%08x\n", desc->offset,
			desc->pm_data);
	}
	dev_info(dev, "exit %s\n", __func__);
	return 0;
}

static void rc_resume_desc(struct device *dev,
			   struct rc_platform_data *data,
			   struct rc_reg_desc *desc)
{
	u32 mask, val;

	if (rc_is_invalid(desc))
		return;

	dev_info(dev, "%03x: current=%08x, suspend=%08x\n", desc->offset,
		 rc_reg_read(data, desc), desc->pm_data);

	val = desc->pm_data | (desc->write_en ? 0xaaaaaaaa : 0);
	mask = ~bits_to_mask(desc, desc->pm_ignore_bits);
	dev_info(dev, "%03x: write mask=%08x, val=%08x\n", desc->offset, mask, val);

	/* apply reg-val */
	rc_reg_update_bits(data, desc, mask, val);

	dev_info(dev, "%03x: current=%08x\n", desc->offset,
		rc_reg_read(data, desc));
}

static int rc_resume(struct device *dev)
{
	struct rc_platform_data *data = dev_get_drvdata(dev);
	int i;

	dev_info(dev, "enter %s\n", __func__);
	for (i = 0; i < data->num_desc; i++)
		rc_resume_desc(dev, data, &data->desc[i]);
	dev_info(dev, "exit %s\n", __func__);
	return 0;
}

const struct dev_pm_ops rc_pm_ops = {
	.suspend_noirq = rc_suspend,
	.resume_noirq  = rc_resume,
};

static int rc_of_reset_xlate(struct reset_controller_dev *rcdev,
				  const struct of_phandle_args *reset_spec)
{
	struct rc_platform_data *data = to_rc_platform_data(rcdev);
	int val;

	val = reset_spec->args[0];
	if (val >= rcdev->nr_resets)
		return -EINVAL;

	if (data->id_xlate)
		return data->id_xlate(data, val);
	return val;
}

static int rc_of_config_io_mem(struct device *dev,
			       struct rc_platform_data *data)
{
	struct device_node *np = dev->of_node;
	struct regmap *regmap;
	int offset = 0;
	struct resource r;
	int ret;


	regmap = of_get_rtk_mmio_regmap_with_offset(np, 0, &offset);
	if (regmap) {
		data->regmap = regmap;
		data->offset = offset;
		return 0;
	}

	ret = of_address_to_resource(np, 0, &r);
	if (ret)
		return ret;
	data->reg = devm_ioremap(dev, r.start, resource_size(&r));
	return data->reg ? 0 : -ENOMEM;
}


int rc_probe_platform(struct platform_device *pdev,
		      struct rc_platform_data *data)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int ret;

	ret = rc_of_config_io_mem(dev, data);
	if (ret) {
		dev_err(dev, "failed to get io mem: %d\n", ret);
		return ret;
	}

	dev_info(dev, "io mem type is %s\n",
			data->regmap ? "regmap" : "direct");
	data->dev = dev;
	data->chip_rev = get_rtd_chip_revision();

	data->rcdev.owner = THIS_MODULE;
	data->rcdev.ops = &rc_ops;
	data->rcdev.of_node = np;
	data->rcdev.nr_resets = 0xffff;
	data->rcdev.of_reset_n_cells = 1;
	data->rcdev.of_xlate = rc_of_reset_xlate;
	ret = reset_controller_register(&data->rcdev);
	if (ret) {
		dev_err(dev, "failed to register controller: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, data);
	dev_info(dev, "initialized\n");
	return 0;
}

