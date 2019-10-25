/*
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
 *
 */

#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/of_address.h>
#include "sensor.h"

/*
 * thermal sensor offset
 */
#define SC_DUMMY_1         0x604
#define TM_SENSOR_CTRL0    0xb00
#define TM_SENSOR_CTRL1    0xb04
#define TM_SENSOR_CTRL2    0xb08
#define TM_SENSOR_STATUS0  0xb40
#define TM_SENSOR_STATUS1  0xb44


static void rtd13xx_sensor_reset(struct thermal_sensor_device *tdev, int index)
{
	struct thermal_sensor *sen = &tdev->sensors[index];

	writel(0x08130000, sen->reg + TM_SENSOR_CTRL0);
	writel(0x003723ff, sen->reg + TM_SENSOR_CTRL1);
	writel(0x00011114, sen->reg + TM_SENSOR_CTRL2);
	writel(0x00031114, sen->reg + TM_SENSOR_CTRL2);
	writel(0xfffffffe, sen->reg + SC_DUMMY_1);
	sen->ts_reset = ktime_get();
}

static int rtd13xx_sensor_init(struct thermal_sensor_device *tdev, int index)
{
	struct thermal_sensor *sen = &tdev->sensors[index];

	sen->reg = of_iomap(tdev->dev->of_node, index);
	if (!sen->reg)
		return -ENOMEM;
	sen->available = true;

	rtd13xx_sensor_reset(tdev, index);
	return 0;
}

static void rtd13xx_sensor_exit(struct thermal_sensor_device *tdev,
	int index)
{
	struct thermal_sensor *sen = &tdev->sensors[index];

	if (!sen->available)
		return;

	sen->available = false;
	iounmap(sen->reg);
}

static inline int __hw_get_temp(void *reg)
{
	unsigned int val = readl(reg + TM_SENSOR_STATUS0);

	return __signext(18, val) * 1000 / 1024;
}

static inline int rtd13xx_sensor_get_temp(struct thermal_sensor_device *tdev,
	int index, int *temp)
{
	struct thermal_sensor *sen = &tdev->sensors[index];
	int t = 0;
	ktime_t delta;

	delta = ktime_sub(ktime_get(), sen->ts_reset);
	if (ktime_to_ms(delta) < 12) {
		u32 wait_ms = 12 - ktime_to_ms(delta);

		msleep(wait_ms);
		dev_dbg(tdev->dev, "wait %ums\n", wait_ms);
	}

	t = __hw_get_temp(sen->reg);

	if (t < -3000 || t > 150000) {
		dev_info(tdev->dev, "reset: temp=%d, status={%08x, %08x}\n",
			t, readl(sen->reg + TM_SENSOR_STATUS0),
			readl(sen->reg + TM_SENSOR_STATUS1));

		rtd13xx_sensor_reset(tdev, index);
		usleep_range(10000, 12000);
		t = __hw_get_temp(sen->reg);
	}
	*temp = t;

	return 0;
}

static const struct thermal_sensor_hw_ops rtd13xx_sensor_hw_ops = {
	.get_temp = rtd13xx_sensor_get_temp,
	.reset    = rtd13xx_sensor_reset,
	.init     = rtd13xx_sensor_init,
	.exit     = rtd13xx_sensor_exit,
};

const struct thermal_sensor_desc rtd13xx_sensor_desc = {
	.hw_ops = &rtd13xx_sensor_hw_ops,
	.num_sensors = 1,
};
