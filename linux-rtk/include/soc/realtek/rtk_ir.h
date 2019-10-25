/*
 * rtk_ir.h
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */
#ifndef __RTK_IR__H__
#define __RTK_IR__H__

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