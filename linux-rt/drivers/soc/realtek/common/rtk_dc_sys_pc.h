/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __SOC_REALTEK_DCSYS_PC_PRIV_H__
#define __SOC_REALTEK_DCSYS_PC_PRIV_H__

#define DC_PC_BASE            0x98008000
#define DC_PC_CTRL                 0x030
#define DC_PC_TOTA_MON_NUM_0       0x034
#define DC_PC_TOTA_ACK_NUM_0       0x038
#define DC_PC_TOTA_IDL_NUM_0       0x03c
#define DC_PC_TOTA_MON_NUM_1       0x040
#define DC_PC_TOTA_ACK_NUM_1       0x044
#define DC_PC_TOTA_IDL_NUM_1       0x048

#define DC_PC_SYSH_PROG_CTRL       0x050
#define DC_PC_SYSH_PROG_CTRL_2     0x500
#define DC_PC_SYSH_PROG_CTRL_3     0x504
#define DC_PC_SYS_PROG_CTRL        0x054

#define DC_PC_SYSH_PROG_0_ACC_LAT  0x060
#define DC_PC_SYSH_PROG_0_MAX_LAT  0x064
#define DC_PC_SYSH_PROG_0_REQ_NUM  0x068
#define DC_PC_SYSH_PROG_0_ACK_NUM  0x06c
#define DC_PC_SYSH_PROG_1_ACC_LAT  0x070
#define DC_PC_SYSH_PROG_1_MAX_LAT  0x074
#define DC_PC_SYSH_PROG_1_REQ_NUM  0x078
#define DC_PC_SYSH_PROG_1_ACK_NUM  0x07c
#define DC_PC_SYSH_PROG_2_ACC_LAT  0x080
#define DC_PC_SYSH_PROG_2_MAX_LAT  0x084
#define DC_PC_SYSH_PROG_2_REQ_NUM  0x088
#define DC_PC_SYSH_PROG_2_ACK_NUM  0x08c

#define DC_PC_SYSH_PROG_3_ACC_LAT  0x510
#define DC_PC_SYSH_PROG_3_MAX_LAT  0x514
#define DC_PC_SYSH_PROG_3_REQ_NUM  0x518
#define DC_PC_SYSH_PROG_3_ACK_NUM  0x51c
#define DC_PC_SYSH_PROG_4_ACC_LAT  0x520
#define DC_PC_SYSH_PROG_4_MAX_LAT  0x524
#define DC_PC_SYSH_PROG_4_REQ_NUM  0x528
#define DC_PC_SYSH_PROG_4_ACK_NUM  0x52c
#define DC_PC_SYSH_PROG_5_ACC_LAT  0x530
#define DC_PC_SYSH_PROG_5_MAX_LAT  0x534
#define DC_PC_SYSH_PROG_5_REQ_NUM  0x538
#define DC_PC_SYSH_PROG_5_ACK_NUM  0x53c

#define DC_PC_SYSH_PROG_6_ACC_LAT  0x540
#define DC_PC_SYSH_PROG_6_MAX_LAT  0x544
#define DC_PC_SYSH_PROG_6_REQ_NUM  0x548
#define DC_PC_SYSH_PROG_6_ACK_NUM  0x54c
#define DC_PC_SYSH_PROG_7_ACC_LAT  0x550
#define DC_PC_SYSH_PROG_7_MAX_LAT  0x554
#define DC_PC_SYSH_PROG_7_REQ_NUM  0x558
#define DC_PC_SYSH_PROG_7_ACK_NUM  0x55c

#define DC_PC_SYS_PROG_0_ACC_LAT   0x090
#define DC_PC_SYS_PROG_0_MAX_LAT   0x094
#define DC_PC_SYS_PROG_0_REQ_NUM   0x098
#define DC_PC_SYS_PROG_0_ACK_NUM   0x09c
#define DC_PC_SYS_PROG_1_ACC_LAT   0x0a0
#define DC_PC_SYS_PROG_1_MAX_LAT   0x0a4
#define DC_PC_SYS_PROG_1_REQ_NUM   0x0a8
#define DC_PC_SYS_PROG_1_ACK_NUM   0x0ac
#define DC_PC_SYS_PROG_2_ACC_LAT   0x0b0
#define DC_PC_SYS_PROG_2_MAX_LAT   0x0b4
#define DC_PC_SYS_PROG_2_REQ_NUM   0x0b8
#define DC_PC_SYS_PROG_2_ACK_NUM   0x0bc

enum DC_PC_REGFIELD_ID {
	PC_SYSH_PROG0_SEL = 0,
	PC_SYSH_PROG0_DC_SEL,
	PC_SYSH_PROG1_SEL,
	PC_SYSH_PROG1_DC_SEL,
	PC_SYSH_PROG2_SEL,
	PC_SYSH_PROG2_DC_SEL,
	PC_SYSH_PROG3_SEL,
	PC_SYSH_PROG3_DC_SEL,
	PC_SYSH_PROG4_SEL,
	PC_SYSH_PROG4_DC_SEL,
	PC_SYSH_PROG5_SEL,
	PC_SYSH_PROG5_DC_SEL,
	PC_SYSH_PROG6_SEL,
	PC_SYSH_PROG6_DC_SEL,
	PC_SYSH_PROG7_SEL,
	PC_SYSH_PROG7_DC_SEL,
	PC_SYS_PROG0_SEL,
	PC_SYS_PROG1_SEL,
	PC_SYS_PROG2_SEL,
};

#include <linux/types.h>

struct device;
struct clk;
struct dcsys_pc;

struct dcsys_pc_core {
	void *base;
	int status;

	struct clk *ref;
	u64 start;
	u64 stop;
	u64 start_cnt;

	struct mutex lock;
	struct dcsys_pc *owner;
	struct list_head list;
	struct srcu_notifier_head notifier_list;
};

struct dcsys_pc {
	struct device *dev;
	struct list_head list;
};

int dcsys_pc_set_regfield(int rf_id, unsigned int val);
int dcsys_pc_get_regfield(int rf_id, unsigned int *val);

int dcsys_pc_get_reg(int offset, unsigned int *val);

#ifdef CONFIG_RTK_DC_SYS_PC_DEBUGFS
void dcsys_pc_debugfs_init(struct device *dev);
#else
static inline void dcsys_pc_debugfs_init(struct device *dev)
{}
#endif

#endif

