/*
 *  rtk_irda.h - RTK irda driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __RTK_IRDA__H__
#define __RTK_IRDA__H__

#define IRCR_RESET		1<<31

#define IR_PSR_OFF		(0x00)
#define IR_PER_OFF		(0x04)
#define IR_SF_OFF		(0x08)
#define IR_DPIR_OFF		(0x0c)
#define IR_CR_OFF		(0x10)
#define IR_RP_OFF		(0x14)
#define IR_SR_OFF		(0x18)
#define IR_RAW_CTRL_OFF		(0x1c)
#define IR_RAW_FF_OFF		(0x20)
#define IR_RAW_SAMPLE_TIME_OFF	(0x24)
#define IR_RAW_WL_OFF		(0x28)
#define IR_RAW_DEB_OFF		(0x2c)
#define IR_PSR_UP_OFF		(0x30)
#define IR_PER_UP_OFF		(0x34)
#define IR_CTRL_RC6_OFF		(0x38)
#define IR_RP2_OFF		(0x3C)
#define IRTX_CFG_OFF		(0x40)
#define IRTX_TIM_OFF		(0x44)
#define IRTX_PWM_SETTING_OFF	(0x48)
#define IRTX_INT_EN_OFF		(0x4c)
#define IRTX_INT_ST_OFF		(0x50)
#define IRTX_FIFO_ST_OFF	(0x54)
#define IRTX_FIFO_OFF		(0x58)
#define IRRCMM_TIMING_OFF	(0x60)
#define IR_CR1_OFF		(0x64)
#define IRRCMM_APKB_OFF		(0x68)
#define IRRXRCLFIFO_OFF		(0x6C)
#define IRDIRECTV_TIMING1	(0x70)
#define IRDIRECTV_TIMING2	(0x74)
#define IRCOMCAST_TIMING	(0x78)
#define IR_RAW_SF		(0xC8)

#define IR_DVF			1<<0
#define IR_REPEAT		1<<1
#define IR_RAWDVF		1<<2
#define IR_RAWDOV		1<<3
#define IR_REPEAT_EN		1<<28

#define VENUS_IR_IOC_MAGIC			'r'
#define VENUS_IR_IOC_SET_IRIOTCDP		_IOW(VENUS_IR_IOC_MAGIC, 1, int)
#define VENUS_IR_IOC_FLUSH_IRRP			_IOW(VENUS_IR_IOC_MAGIC, 2, int)
#define VENUS_IR_IOC_SET_PROTOCOL		_IOW(VENUS_IR_IOC_MAGIC, 3, int)
#define VENUS_IR_IOC_SET_DEBOUNCE		_IOW(VENUS_IR_IOC_MAGIC, 4, int)
#define VENUS_IR_IOC_SET_IRPSR			_IOW(VENUS_IR_IOC_MAGIC, 5, int)
#define VENUS_IR_IOC_SET_IRPER			_IOW(VENUS_IR_IOC_MAGIC, 6, int)
#define VENUS_IR_IOC_SET_IRSF			_IOW(VENUS_IR_IOC_MAGIC, 7, int)
#define VENUS_IR_IOC_SET_IRCR			_IOW(VENUS_IR_IOC_MAGIC, 8, int)
#define VENUS_IR_IOC_SET_DRIVER_MODE		_IOW(VENUS_IR_IOC_MAGIC, 9, int)
#define VENUS_IR_IOC_SET_FIRST_REPEAT_DELAY	_IOW(VENUS_IR_IOC_MAGIC, 10, int)
#define VENUS_IRTX_IOC_SET_TX_TABLE		_IOW(VENUS_IR_IOC_MAGIC, 11, int)
#define VENUS_IRRX_RAW_STOP			_IOW(VENUS_IR_IOC_MAGIC, 12, int)

struct irda_wake_up_key {
	unsigned int protocol;
	unsigned int scancode_mask;
	unsigned int wakeup_scancode;
	unsigned int cus_mask;
	unsigned int cus_code;
};
struct ipc_shm_irda {
	unsigned int ipc_shm_ir_magic;
	unsigned int dev_count;
	struct irda_wake_up_key key_tbl[5];
};
#endif
