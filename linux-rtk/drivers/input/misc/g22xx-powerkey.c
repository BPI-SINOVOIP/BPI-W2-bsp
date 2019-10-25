/*
 * GMT-G22XX series PMIC Powerkey Driver
 *
 * Copyright (C) 2019 Realtek Semiconductor Corporation
 *
 * Author:
 *      Cheng-Yu Lee <cylee12@realtek.com>
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

#include <linux/debugfs.h>
#include <linux/input.h>
#include <linux/input-polldev.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <linux/input-polldev.h>
#include <linux/of.h>
#include <linux/mfd/g22xx.h>
#include <linux/mfd/g2227.h>
#include <linux/ktime.h>
#include <linux/pm.h>

#define DEFAULT_POLLING_MS    (250)

enum {
	G22XX_LPOFF_TO_DO,
	G22XX_ENLPOFF,
	G22XX_TIME_IT,
	G22XX_TIME_LP,
	G22XX_TIME_LPOFF,
	G22XX_MASK_PWRKEY,
	G22XX_MASK_LP,
	G22XX_MASK_IT,
	G22XX_MAX,
};

struct g22xx_powerkey_data {
	struct device *dev;
	struct g22xx_device *gdev;
	struct dentry *d;
	struct input_polled_dev *ipdev;

	struct regmap_field *regs[G22XX_MAX];

	u32 state;
	u32 lp_emu_left;
	ktime_t it_timestamp;

	/* config */
	u32 lp_hw_en:1;
	u32 lp_sw_en:1;
	u32 it_sw_en:1;
	u32 lpoff_sel:2;
	u32 lpoff_act:1;
	u32 lp_sel:2;
	u32 it_sel:2;
	u32 lp_time;
	u32 lp_timeout;
};

static struct reg_field g22xx_powerkey_fields[] = {
	[G22XX_LPOFF_TO_DO] =  REG_FIELD(G2227_REG_PWRKEY, 7, 7),
	[G22XX_ENLPOFF]     =  REG_FIELD(G2227_REG_PWRKEY, 6, 6),
	[G22XX_TIME_IT]     =  REG_FIELD(G2227_REG_PWRKEY, 4, 5),
	[G22XX_TIME_LP]     =  REG_FIELD(G2227_REG_PWRKEY, 2, 3),
	[G22XX_TIME_LPOFF]  =  REG_FIELD(G2227_REG_PWRKEY, 0, 1),
	[G22XX_MASK_PWRKEY] =  REG_FIELD(G2227_REG_INTR_MASK, 5, 5),
	[G22XX_MASK_LP]     =  REG_FIELD(G2227_REG_INTR_MASK, 4, 4),
	[G22XX_MASK_IT]     =  REG_FIELD(G2227_REG_INTR_MASK, 3, 3),
};

static void g22xx_powerkey_set_config(struct g22xx_powerkey_data *pdata,
				      u32 id,
				      u32 val)
{
	regmap_field_write(pdata->regs[id], val);
}

static int g22xx_powerkey_show(struct seq_file *s, void *data)
{
	struct g22xx_powerkey_data *pdata = s->private;
	struct regmap *r = pdata->gdev->regmap;
	u32 val;
	int ret;

	ret = regmap_read(r, G2227_REG_PWRKEY, &val);
	if (ret) {
		seq_puts(s, "faield to read REG_PWRKEY");
		return 0;
	}

	seq_printf(s, "TIME_LPOFF=%x\n", val & 0x3);
	val >>= 2;
	seq_printf(s, "TIME_LP=%x\n", val & 0x3);
	val >>= 2;
	seq_printf(s, "TIME_IT=%x\n", val & 0x3);
	val >>= 2;
	seq_printf(s, "ENLPOFF=%x\n", val & 0x1);
	val >>= 1;
	seq_printf(s, "LPOFF_TO_DO=%x\n", val & 0x1);

	ret = regmap_read(r, G2227_REG_INTR_MASK, &val);
	if (ret) {
		seq_puts(s, "faield to read REG_INTR_MASK");
		return 0;
	}
	val >>= 3;
	seq_printf(s, "MASK_IT=%x\n", val & 1);
	val >>= 1;
	seq_printf(s, "MASK_LP=%x\n", val & 1);
	val >>= 1;
	seq_printf(s, "MASK_PWRKEY=%x\n", val & 1);

	return 0;
}

static int g22xx_powerkey_open(struct inode *inode, struct file *file)
{
	return single_open(file, g22xx_powerkey_show, inode->i_private);
}

static const struct file_operations g22xx_powerkey_fops = {
	.owner   = THIS_MODULE,
	.open    = g22xx_powerkey_open,
	.read    = seq_read,
	.release = single_release,
};

enum {
	G22XX_STATE_DEFAULT,
	G22XX_STATE_IT_PRESSED,
};

enum {
	G22XX_ACT_NONE,
	G22XX_ACT_KEY_POWEY,
	G22XX_ACT_KEY_POWEY_LP,
};

static void g22xx_powerkey_poll(struct input_polled_dev *ipdev)
{
	struct g22xx_powerkey_data *pdata = ipdev->private;
	struct regmap *r = pdata->gdev->regmap;
	struct input_dev *idev = pdata->ipdev->input;
	struct device *dev = pdata->dev;
	ktime_t cur = ktime_get();
	u32 val, val_c;
	int ret;
	u32 next_state;
	u32 action;

	u32 pwrkey_it;
	u32 pwrkey_lp;
	u32 pwrkey;
	u32 ints;

	if (pdata->lp_emu_left > 0) {
		if (pdata->lp_emu_left-- == 1) {
			input_report_key(idev, KEY_POWER, 0);
			input_sync(idev);
			dev_dbg(dev, "pwrkey longpress stop\n");

			/* clear ints */
			regmap_read(r, 0x00, &val);
		}
		return;
	}

	ret = regmap_read(r, 0x00, &val);
	if (ret) {
		dev_warn(dev, "failed to read from regmap: %d\n", ret);
		return;
	}

	val_c = val;
	val >>= 3;
	pwrkey_it = val & 0x1;
	val >>= 1;
	pwrkey_lp = val & 0x1;
	val >>= 1;
	pwrkey = val & 0x1;
	val >>= 2;
	ints = val & 0x1;
	val = val_c;

	if (val != 0)
		dev_dbg(pdata->dev, "read=%02x, pwrkey_it=%d, pwrkey_lp=%d, pwrkey=%d, ints=%d\n",
			val, pwrkey_it, pwrkey_lp, pwrkey, ints);

	action = G22XX_ACT_NONE;
	next_state = pdata->state;
	switch (pdata->state) {
	case G22XX_STATE_DEFAULT:
		if (pwrkey_it == 1) {
			/* unnecessary to check when no sw lp */
			if (pdata->lp_sw_en == 0) {
				action = G22XX_ACT_KEY_POWEY;
			} else {
				next_state = G22XX_STATE_IT_PRESSED;
				pdata->it_timestamp = cur;
			}
		} else if (pwrkey_lp == 1) {
			action = G22XX_ACT_KEY_POWEY_LP;
		}
		break;

	case G22XX_STATE_IT_PRESSED:
		next_state = G22XX_STATE_DEFAULT;
		if (pwrkey == 1) {
			dev_dbg(dev, "state_it: pwrkey press\n");
			action = G22XX_ACT_KEY_POWEY;
		} else if (pwrkey_lp == 1) {
			dev_dbg(dev, "state_it: pwrkey long press\n");
			action = G22XX_ACT_KEY_POWEY_LP;
		} else if (ktime_ms_delta(cur, pdata->it_timestamp) >=
			   pdata->lp_timeout) {
			dev_dbg(dev, "state_it: pwrkey long press timeout\n");
			action = G22XX_ACT_KEY_POWEY;
		} else
			next_state = G22XX_STATE_IT_PRESSED;
		break;
	default:
		break;
	}
	pdata->state = next_state;

	switch (action) {
	case G22XX_ACT_KEY_POWEY_LP:
		dev_dbg(dev, "pwrkey longpress start\n");
		pdata->lp_emu_left = DIV_ROUND_UP(pdata->lp_time,
						  pdata->ipdev->poll_interval);
		input_report_key(idev, KEY_POWER, 1);
		input_sync(idev);
		break;
	case G22XX_ACT_KEY_POWEY:
		dev_dbg(dev, "pwrkey press\n");
		input_report_key(idev, KEY_POWER, 1);
		input_sync(idev);
		input_report_key(idev, KEY_POWER, 0);
		input_sync(idev);
		break;
	default:
		break;
	}
}

static int g22xx_powerkey_parse_dt(struct device_node *np,
				   struct g22xx_powerkey_data *pdata)
{
	const char *str;
	u32 val[3];

	pdata->lp_hw_en = pdata->lp_sw_en = 0;
	if (!of_property_read_string(np, "lp-handler", &str)) {
		if (!strncmp("hw", str, 2))
			pdata->lp_hw_en = 1;
		else if (!strncmp("sw", str, 2))
			pdata->lp_sw_en = 1;
	}

	pdata->it_sw_en = 0;
	if (!of_property_read_string(np, "it-handler", &str)) {
		if (!strncmp("sw", str, 2))
			pdata->it_sw_en = 1;
	}

	pdata->it_sel = 0;
	pdata->lp_sel = 1;
	pdata->lpoff_sel = 3;
	if (!of_property_read_u32_array(np, "time-sel", val, 3)) {
		pdata->it_sel = val[0];
		pdata->lp_sel = val[1];
		pdata->lpoff_sel = val[2];
	}

	pdata->lp_time = (pdata->lp_sel + 1) * 1000;
	pdata->lp_timeout = pdata->lp_time + DEFAULT_POLLING_MS + 1;

	pdata->lpoff_act = 1;
	if (!of_property_read_u32(np, "lpoff-act", val))
		pdata->lpoff_act = *val;

	dev_info(pdata->dev, "lp=%s, it=%s, sel=[%d,%d,%d]\n",
		pdata->lp_hw_en ? "hw" : (pdata->lp_sw_en ? "sw" : "none"),
		pdata->it_sw_en ? "sw" : "none",
		pdata->it_sel, pdata->lp_sel, pdata->lpoff_sel);

	return 0;
}

static int g22xx_powerkey_apply_config(struct g22xx_powerkey_data *pdata)
{
	if (pdata->lp_hw_en == 1) {
		g22xx_powerkey_set_config(pdata, G22XX_ENLPOFF, 1);
		g22xx_powerkey_set_config(pdata, G22XX_TIME_LPOFF,
					  pdata->lpoff_sel);
		g22xx_powerkey_set_config(pdata, G22XX_MASK_LP, 1);
		g22xx_powerkey_set_config(pdata, G22XX_LPOFF_TO_DO,
					  pdata->lpoff_act);
	} else if (pdata->lp_sw_en == 1) {
		g22xx_powerkey_set_config(pdata, G22XX_ENLPOFF, 0);
		g22xx_powerkey_set_config(pdata, G22XX_TIME_LP, pdata->lp_sel);
		g22xx_powerkey_set_config(pdata, G22XX_MASK_LP, 0);
	} else {
		g22xx_powerkey_set_config(pdata, G22XX_ENLPOFF, 0);
		g22xx_powerkey_set_config(pdata, G22XX_MASK_LP, 1);
	}

	if (pdata->it_sw_en == 1) {
		g22xx_powerkey_set_config(pdata, G22XX_TIME_IT, pdata->it_sel);
		g22xx_powerkey_set_config(pdata, G22XX_MASK_IT, 0);
	} else {
		g22xx_powerkey_set_config(pdata, G22XX_MASK_IT, 1);
	}

	return 0;
}

static int g22xx_powerkey_suspend(struct device *dev)
{
	struct g22xx_powerkey_data *pdata = dev_get_drvdata(dev);

	dev_info(dev, "enter %s\n", __func__);
	g22xx_powerkey_set_config(pdata, G22XX_ENLPOFF, 1);
	g22xx_powerkey_set_config(pdata, G22XX_LPOFF_TO_DO, pdata->lpoff_act);
	dev_info(dev, "exit %s\n", __func__);
	return 0;
}

static int g22xx_powerkey_resume(struct device *dev)
{
	struct g22xx_powerkey_data *pdata = dev_get_drvdata(dev);

	dev_info(dev, "enter %s\n", __func__);
	g22xx_powerkey_apply_config(pdata);
	dev_info(dev, "exit %s\n", __func__);
	return 0;
}

static const struct dev_pm_ops g22xx_powerkey_pm_ops = {
	.suspend = g22xx_powerkey_suspend,
	.resume  = g22xx_powerkey_resume,
};

static int g22xx_powerkey_probe(struct platform_device *pdev)
{
	struct g22xx_powerkey_data *pdata;
	struct device *dev = &pdev->dev;
	struct g22xx_device *gdev = dev_get_drvdata(dev->parent);
	struct input_dev *idev;
	int ret;
	int i;

	if (!dev->of_node || !of_device_is_available(dev->of_node))
		return -ENODEV;

	if (!gdev) {
		dev_err(dev, "no parent device\n");
		return -EINVAL;
	}

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;


	pdata->ipdev = devm_input_allocate_polled_device(dev);
	if (!pdata->ipdev)
		return -ENOMEM;

	for (i = 0; i < G22XX_MAX; i++) {
		pdata->regs[i] = devm_regmap_field_alloc(dev, gdev->regmap,
						g22xx_powerkey_fields[i]);
		if (IS_ERR(pdata->regs[i])) {
			ret = PTR_ERR(pdata->regs[i]);
			dev_err(dev, "failed to alloc regmap field %d: %d\n", i,
				ret);
			return ret;
		}
	}

	pdata->dev = dev;
	pdata->gdev = gdev;
	g22xx_powerkey_parse_dt(dev->of_node, pdata);
	g22xx_powerkey_apply_config(pdata);

	if (!pdata->lp_sw_en && !pdata->it_sw_en)
		goto no_input_polldev;

	pdata->ipdev->poll = g22xx_powerkey_poll;
	pdata->ipdev->poll_interval = DEFAULT_POLLING_MS;
	pdata->ipdev->private = pdata;

	idev = pdata->ipdev->input;
	idev->name = "g22xx-powerkey";
	idev->phys = "g22xx-powerkey/input0";
	idev->id.bustype = BUS_HOST;
	idev->dev.parent = dev;
	input_set_capability(idev, EV_KEY, KEY_POWER);

	ret = input_register_polled_device(pdata->ipdev);
	if (ret) {
		dev_err(dev, "failed to register input polled device\n");
		return ret;
	}
no_input_polldev:
	pdata->d = debugfs_create_file("g22xx_powerkey_info", 0444, NULL, pdata,
				       &g22xx_powerkey_fops);
	if (!pdata->d)
		dev_warn(dev, "debugfs_create_file() failed\n");
	platform_set_drvdata(pdev, pdata);
	dev_info(dev, "initialized\n");
	return 0;
}

static int g22xx_powerkey_remove(struct platform_device *pdev)
{
	struct g22xx_powerkey_data *pdata = platform_get_drvdata(pdev);
	struct device *dev = &pdev->dev;

	platform_set_drvdata(pdev, NULL);
	debugfs_remove(pdata->d);
	if (pdata->lp_sw_en || pdata->it_sw_en)
		input_unregister_polled_device(pdata->ipdev);
	dev_info(dev, "removed\n");
	return 0;
}

static const struct of_device_id g22xx_powerkey_ids[] = {
	{ .compatible = "gmt,g22xx-powerkey", },
	{}
};

static struct platform_driver g22xx_powerkey_driver = {
	.probe = g22xx_powerkey_probe,
	.remove = g22xx_powerkey_remove,
	.driver = {
		.name = "g22xx-powerkey",
		.of_match_table = g22xx_powerkey_ids,
		.pm = &g22xx_powerkey_pm_ops,
	},
};
module_platform_driver(g22xx_powerkey_driver);

