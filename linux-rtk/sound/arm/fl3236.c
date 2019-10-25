/*
 * fl3236.c  --  FL3236 SPI driver
 *
 * Copyright 2018 Realtek Semiconductor Corp.
 * Author: YH HSIEH <yh_hsieh@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/input.h>
#include <linux/spi/spi.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/pm_qos.h>
#include <linux/sysfs.h>
#include <linux/clk.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/initval.h>
#include <linux/i2c.h>
#include <linux/of_gpio.h>
#include <soc/realtek/rtk_regmap.h>

int voice_direction_from_user = 0;
int fl3236_check_flag = 0;

static ssize_t fl3236_light_store(struct device *dev,
						struct device_attribute *attr,
						const char *buf,
						size_t count)
{
	unsigned long long direction;
	if(!kstrtoull(buf, 10, &direction))
		voice_direction_from_user = (int)direction;
	printk("%s before write %d\n", __func__, voice_direction_from_user);
	voice_direction_from_user = voice_direction_from_user - 180; //shift degree
	printk("%s after write %d\n", __func__, voice_direction_from_user);
	return count;
}

static ssize_t fl3236_light_show(struct device *dev,
					       struct device_attribute *attr,
					       char *buf)
{
	return 0;
}

static DEVICE_ATTR(light, 0644,
		   fl3236_light_show,
		   fl3236_light_store);

static struct attribute *fl3236_light_dev_attrs[] = {
	&dev_attr_light.attr,
	NULL
};

static const struct attribute_group fl3236_dev_group = {
	.name = "fl3236_light",
	.attrs = fl3236_light_dev_attrs,
};

static int fl3236_add_sysfs(struct device *dev)
{
	return sysfs_create_group(&dev->kobj, &fl3236_dev_group);
}

/*****************************************************************************
******* below fl3236 led i2c driver                                  *********
******************************************************************************
*/
static uint8_t voice_led_position_01 = 9;
static uint8_t voice_led_position_02 = 8;

static void convert_mic_position_to_led_position(int voice_direction) {

	if ( voice_direction > 0 && voice_direction <= 30 ) {
		voice_led_position_01 =  6;
		voice_led_position_02 =  5;
	} else if ( voice_direction > 30 && voice_direction <= 60 ) {
		voice_led_position_01 =  5;
		voice_led_position_02 =  4;
	} else if ( voice_direction > 60 && voice_direction <= 90 ) {
		voice_led_position_01 =  4;
		voice_led_position_02 =  3;
	} else if ( voice_direction > 90 && voice_direction <= 120 ) {
		voice_led_position_01 =  3;
		voice_led_position_02 =  2;
	} else if ( voice_direction > 120 && voice_direction <= 150 ) {
		voice_led_position_01 =  2;
		voice_led_position_02 =  1;
	} else if ( voice_direction > 150 && voice_direction <= 180 ) {
		voice_led_position_01 =  1;
		voice_led_position_02 =  12;
	} else if ( voice_direction >= -180 && voice_direction <= -150 ) {
		voice_led_position_01 =  12;
		voice_led_position_02 =  11;
	} else if ( voice_direction >= -150 && voice_direction <= -120 ) {
		voice_led_position_01 =  11;
		voice_led_position_02 =  10;
	} else if ( voice_direction >= -120 && voice_direction <= -90 ) {
		voice_led_position_01 =  10;
		voice_led_position_02 =  9;
	} else if ( voice_direction >= -90 && voice_direction <= -60 ) {
		voice_led_position_01 = 9;
		voice_led_position_02 = 8;
	} else if ( voice_direction >= -60 && voice_direction <= -30 ) {
		voice_led_position_01 = 8;
		voice_led_position_02 = 7;
	} else if ( voice_direction >= -30 && voice_direction <= -0 ) {
		voice_led_position_01 = 7;
		voice_led_position_02 = 6;
	} else {
		printk("unknown voice position:%d\r\n", voice_direction);
		voice_led_position_01 =  0xFF;
		voice_led_position_02 =  0xFF;
	}
}

struct fl3236_priv {

	struct regmap *regmap;
};

struct fl3236_priv *fl3236;

static void fl3236_set_led(uint8_t led_position_01, uint8_t  led_position_02, int on_off)
{
	/* pwm luminous intensity */
	regmap_write(fl3236->regmap, 0x01+(led_position_01-1)*3, 0x80);
	regmap_write(fl3236->regmap, 0x01+(led_position_02-1)*3, 0x80);
	regmap_write(fl3236->regmap, 0x01+(led_position_01-1)*3 + 1, 0x80);
	regmap_write(fl3236->regmap, 0x01+(led_position_02-1)*3 + 1, 0x80);
	regmap_write(fl3236->regmap, 0x01+(led_position_01-1)*3 + 2, 0x80);
	regmap_write(fl3236->regmap, 0x01+(led_position_02-1)*3 + 2, 0x80);

	/* LED Control */
	regmap_write(fl3236->regmap, 0x26+(led_position_01-1)*3, on_off);
	regmap_write(fl3236->regmap, 0x26+(led_position_02-1)*3, on_off);
	regmap_write(fl3236->regmap, 0x26+(led_position_01-1)*3 + 1, on_off);
	regmap_write(fl3236->regmap, 0x26+(led_position_02-1)*3 + 1, on_off);
	regmap_write(fl3236->regmap, 0x26+(led_position_01-1)*3 + 2, on_off);
	regmap_write(fl3236->regmap, 0x26+(led_position_02-1)*3 + 2, on_off);

	/* pwm Update */
	regmap_write(fl3236->regmap, 0x25, 0);
}

void fl3236_enable_light(void)
{
	int i;

	if(!fl3236_check_flag)
		return;

	/* all LED off */
	for (i = 1; i < 12 ; i++)
		fl3236_set_led(i, i+1, 0);

	/* Get the voice direction and show the light*/
	convert_mic_position_to_led_position(voice_direction_from_user);
	fl3236_set_led(voice_led_position_01, voice_led_position_02, 1);
}

void fl3236_disable_light(void)
{
	int i;

	if(!fl3236_check_flag)
		return;

	/* all LED off */
	for (i = 1; i < 12 ; i++)
		fl3236_set_led(i, i+1, 0);
}

static const struct regmap_config fl3236_regmap = {
	.reg_bits = 8,
	.val_bits = 8,
	.max_register = 0xffff,
};

static int fl3236_i2c_probe(struct i2c_client *i2c,
                             const struct i2c_device_id *id)
{
	int i;
	void __iomem	*pad_mux;

	pr_err("%s id->name =%s i2c->name=%s i2c->addr=0x%x \n", __func__, id->name, i2c->name, i2c->addr);
	fl3236 = devm_kzalloc(&i2c->dev, sizeof(struct fl3236_priv),
						GFP_KERNEL);
	if (fl3236 == NULL)
		return -ENOMEM;

	fl3236->regmap = devm_rtk_regmap_init_i2c(i2c, &fl3236_regmap);

	fl3236_add_sysfs(&i2c->dev);

	/* Set the hif_clf for sda 4 */
	pad_mux = ioremap(0x9804F000, 0x120);
	writel(0x75555554, pad_mux);

	/* Set the pad_mux for i2c sda 4 */
	pad_mux = ioremap(0x9804F004, 0x120);
	writel(0x2492924B, pad_mux);

	if (IS_ERR(fl3236->regmap))
		return PTR_ERR(fl3236->regmap);

	/* Reset */
	regmap_write(fl3236->regmap, 0x4f, 0);

	/* Normal operation */
	regmap_write(fl3236->regmap, 0x00, 1);

	/* all LED on */
	for (i = 1; i < 12 ; i++)
		fl3236_set_led(i, i+1, 1);

	mdelay(1000);

	for (i = 1; i < 12 ; i++)
		fl3236_set_led(i, i+1, 0);

	/* check fl3236 enable success */
	fl3236_check_flag = 1;

	return 0;
}

static const struct i2c_device_id fl3236_i2c_id[] = {
	{ "fl3236", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, fl3236_i2c_id);

static const struct of_device_id fl3236_of_id[] = {
	{ .compatible = "fl3236", },
	{ /* senitel */ }
};
MODULE_DEVICE_TABLE(of, fl3236_of_id);

static struct i2c_driver fl3236_i2c_driver = {
	.driver = {
		.name = "rtk,fl3236",
		.owner = THIS_MODULE,
	},
	.probe =    fl3236_i2c_probe,
//	.remove =   fl3236_i2c_remove,
	.id_table = fl3236_i2c_id,
};

module_i2c_driver(fl3236_i2c_driver);

MODULE_AUTHOR("YH HSIEH");
MODULE_DESCRIPTION("FL3236 Kernel Driver");
MODULE_LICENSE("GPL");
