/*
 * hdcp_ddc.h - RTK hdcp tx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/ioctl.h>
#include <linux/types.h>

enum ddc_operation {
	DDC_READ,
	DDC_WRITE
};

/***********************/
/* DDC addresses  */
/***********************/
#define DDC_BKSV_ADDR           0x00
#define DDC_Ri_ADDR             0x08
#define DDC_AKSV_ADDR           0x10
#define DDC_AN_ADDR             0x18
#define DDC_V_ADDR              0x20
#define DDC_BCAPS_ADDR          0x40
#define DDC_BSTATUS_ADDR        0x41
#define DDC_KSV_FIFO_ADDR       0x43

#define DDC_BKSV_LEN            5
#define DDC_Ri_LEN              2
#define DDC_AKSV_LEN            5
#define DDC_AN_LEN              8
/* each Hx part of SHA-1 hash value V' is 4 bytes */
#define DDC_V_LEN               4
#define DDC_BCAPS_LEN           1
#define DDC_BSTATUS_LEN         2

#define DDC_BIT_REPEATER        6
/* Bit5:READY of Bcaps, KSV FIFO ready */
#define DDC_BIT_READY           5

#define DDC_BSTATUS0_MAX_DEVS   0x80
#define DDC_BSTATUS0_DEV_COUNT  0x7F
#define DDC_BSTATUS1_MAX_CASC   0x08


/* DDC access timeout in ms */
#define DDC_TIMEOUT     500
#define DDC_STOP_FRAME_BLOCKING_TIMEOUT (2*DDC_TIMEOUT)

#define MAX_DDC_ERR     5

/* Status / error codes */
#define DDC_OK                  0
#define DDC_ERROR               1


#define RD_FIELD_32(base, offset, start, end) \
	((RD_REG_32(base, offset) & FLD_MASK(start, end)) >> (end))


struct ddc {
	void __iomem *hdmi_wp_base_addr;
	struct mutex lock;
	spinlock_t spinlock;
};
extern struct ddc ddc;

/* DDC */
int ddc_read(int len, unsigned char start, unsigned char *buf);
int ddc_write(int len, unsigned char start, unsigned char *buf);

