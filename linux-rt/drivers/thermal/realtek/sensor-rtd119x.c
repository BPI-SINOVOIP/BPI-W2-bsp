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
#include <linux/nvmem-consumer.h>
#include <linux/of_address.h>
#include <linux/slab.h>
#include "sensor.h"

static void rtd119x_sensor_reset(struct thermal_sensor_device *tdev, int index)
{
}

static int rtd119x_sensor_init(struct thermal_sensor_device *tdev, int index)
{
	struct thermal_sensor *sen = &tdev->sensors[index];
	struct device_node *np = tdev->dev->of_node;
	char cell_name[20];
	struct nvmem_cell *cell;
	unsigned char *buf;
	size_t buf_size;

	sen->reg = of_iomap(np, index);
	if (!sen->reg)
		return -ENOMEM;
	sen->available = true;

	sprintf(cell_name, "calibration%d", index);
	cell = nvmem_cell_get(tdev->dev, cell_name);
	if (IS_ERR(cell)) {
		dev_warn(tdev->dev, "nvmem_cell_get() returns %ld\n",
			PTR_ERR(cell));
		goto done;
	}
	buf = nvmem_cell_read(cell, &buf_size);
	nvmem_cell_put(cell);
	dev_info(tdev->dev, "sensor%d: calibration=%d\n",index, (int)buf[0]);
	sen->calibration_data = (int)buf[0] * 1000;
	kfree(buf);
done:
	return 0;
}

static void rtd119x_sensor_exit(struct thermal_sensor_device *tdev, int index)
{
	struct thermal_sensor *sen = &tdev->sensors[index];

	if (!sen->available)
		return;
	sen->available = false;
	iounmap(sen->reg);
}

static inline int rtd119x_sensor_get_temp(struct thermal_sensor_device *tdev,
	int index, int *temp)
{
	struct thermal_sensor *sen = &tdev->sensors[index];
	int i;
	u64 t;
	u32 val, cmp_data;

	if (!sen->available)
		return -EINVAL;

	/* enable */
	writel(0x0000c80c, sen->reg);
	usleep_range(15, 25);

	/* thermal detect */
	for (i = 6; i >= 0; i--) {
		val = readl(sen->reg);
		cmp_data = BIT(i + 5);
		writel(cmp_data | val, sen->reg);
		usleep_range(15, 25);

		val = readl(sen->reg);
		if ((val & BIT(16)) == 0)
			writel(~cmp_data & val, sen->reg);
	}

	/* get temperture */
	val = readl(sen->reg);
	t = (val >> 5) & 0x7f;
	t *= 1000;
	t -= sen->calibration_data;
	t = (t * 165) / 128;
	if (sen->calibration_data)
		t += 25 * 1000;
	else
		t -= 47 * 1000;

	dev_dbg(tdev->dev, "sensor%d: reg=%05x, t=%lld, calibration_data=%d\n",
		index, val, t, sen->calibration_data);
	*temp = (int)t;
	return 0;
}

static const struct thermal_sensor_hw_ops rtd119x_hw_ops = {
	.get_temp = rtd119x_sensor_get_temp,
	.reset    = rtd119x_sensor_reset,
	.init     = rtd119x_sensor_init,
	.exit     = rtd119x_sensor_exit,
};

const struct thermal_sensor_desc rtd119x_sensor_desc = {
	.hw_ops = &rtd119x_hw_ops,
	.num_sensors = 2,
};

