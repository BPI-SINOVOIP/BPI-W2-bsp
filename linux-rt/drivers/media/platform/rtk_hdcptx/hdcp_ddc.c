/*
 * hdcp_ddc.c - RTK hdcp tx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/delay.h>
#include <linux/i2c.h>
#include "hdcp.h"

#define HDCP_I2C_SPEED I2C_M_LOW_SPEED_80

int ddc_write(int len, unsigned char start, unsigned char *buf)
{
	struct i2c_adapter *p_adap;
	unsigned char bus_id = 1;
	unsigned char *data;

	data = kzalloc((len+1)*sizeof(unsigned char), GFP_KERNEL);

	data[0] = start;
	memcpy(data+1, buf, len);

#if 0
	int i;

	for (i = 0; i < len+1; i++)
		HDCP_DEBUG("data[%d]=0x%x\n", i, data[i]);

	for (i = 0; i < len; i++)
		HDCP_DEBUG("buf[%d]=0x%x\n", i, buf[i]);
#endif

	struct i2c_msg msgs[] = {
		{
			.addr	= 0x3A,
			.flags	= HDCP_I2C_SPEED,
			.len	= len+1,
			.buf	= data,
		}
	};

	p_adap = i2c_get_adapter(bus_id);
	if (p_adap == NULL) {
		HDCP_ERROR("get adapter %d failed\n", bus_id);
		return -ENODEV;
	}

	if (i2c_transfer(p_adap, msgs, 1) == 1)
		return 0;

	return -ECOMM;
}

int ddc_read(int len, unsigned char start, unsigned char *buf)
{
	struct i2c_adapter *p_adap;
	unsigned char bus_id = 1;

	struct i2c_msg msgs[] = {
		{
			.addr	= 0x3A,
			.flags	= HDCP_I2C_SPEED,
			.len	= 1,
			.buf	= &start,
		}, {
			.addr	= 0x3A,
			.flags	= HDCP_I2C_SPEED | I2C_M_RD,
			.len	= len,
			.buf	= buf,
		}
	};

	p_adap = i2c_get_adapter(bus_id);
	if (p_adap == NULL) {
		HDCP_ERROR("hdcp get adapter %d failed\n", bus_id);
		return -ENODEV;
	}

	if (i2c_transfer(p_adap, msgs, 2) == 2)
		return 0;

	return -ECOMM;
}
