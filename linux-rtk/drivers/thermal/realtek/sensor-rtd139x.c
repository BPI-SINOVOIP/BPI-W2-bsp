/*
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 * Copyright (C) 2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/of_address.h>
#include "sensor.h"

/*
 * thermal sensor offset
 */
#define TM_SENSOR_CTRL0    0x00
#define TM_SENSOR_CTRL1    0x04
#define TM_SENSOR_CTRL2    0x08
#define TM_SENSOR_CTRL3    0x0C
#define TM_SENSOR_CTRL4    0x10
#define TM_SENSOR_CTRL5    0x14
#define TM_SENSOR_STATUS1  0x18
#define TM_SENSOR_STATUS2  0x1C

static void rtd139x_sensor_reset(struct thermal_sensor_device *tdev, int index)
{
	struct thermal_sensor *sen = &tdev->sensors[index];

	writel(0x11904000, sen->reg + TM_SENSOR_CTRL2);
	writel(0x11924000, sen->reg + TM_SENSOR_CTRL2);
	usleep_range(25000, 26000);

}

static int rtd139x_sensor_init(struct thermal_sensor_device *tdev, int index)
{
	struct thermal_sensor *sen = &tdev->sensors[index];

	sen->reg = of_iomap(tdev->dev->of_node, index);
	if (!sen->reg)
		return -ENOMEM;
	sen->available = true;

	writel(0x081fc000, sen->reg + TM_SENSOR_CTRL0);
	writel(0x05772000, sen->reg + TM_SENSOR_CTRL1);
	writel(0x11824000, sen->reg + TM_SENSOR_CTRL2);
	writel(0x11924000, sen->reg + TM_SENSOR_CTRL2);
	udelay(6);
	return 0;
}

static void rtd139x_sensor_exit(struct thermal_sensor_device *tdev,
	int index)
{
	struct thermal_sensor *sen = &tdev->sensors[index];

	if (!sen->available)
		return;

	sen->available = false;
	iounmap(sen->reg);
}

static inline int _SIGN_EXT(int sign_bit, unsigned int val)
{
	return (0 - (BIT(sign_bit) & val)) | val;
}

static inline int __hw_get_temp(void *reg)
{
	unsigned int val = readl(reg + TM_SENSOR_STATUS1);

	return _SIGN_EXT(18, val) * 1000 / 1024;
}

static inline int rtd139x_sensor_get_temp(struct thermal_sensor_device *tdev,
	int index, int *temp)
{
	struct thermal_sensor *sen = &tdev->sensors[index];
	int t = 0;

	t = __hw_get_temp(sen->reg);

	if (t < -3000 || t > 150000) {
		dev_info(tdev->dev, "reset: temp=%d, status={%08x, %08x}\n",
			t, readl(sen->reg + TM_SENSOR_STATUS1),
			readl(sen->reg + TM_SENSOR_STATUS2));

		rtd139x_sensor_reset(tdev, index);
		t = __hw_get_temp(sen->reg);
	}
	*temp = t;

	return 0;
}

static const struct thermal_sensor_hw_ops rtd139x_sensor_hw_ops = {
	.get_temp = rtd139x_sensor_get_temp,
	.reset    = rtd139x_sensor_reset,
	.init     = rtd139x_sensor_init,
	.exit     = rtd139x_sensor_exit,
};

const struct thermal_sensor_desc rtd139x_sensor_desc = {
	.hw_ops = &rtd139x_sensor_hw_ops,
	.num_sensors = 1,
};
