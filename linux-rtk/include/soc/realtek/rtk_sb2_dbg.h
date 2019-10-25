/*
 * rtk_sb2_dbg.h - Realtek SB2 Debug API
 *
 * Copyright (C) 2019 Realtek Semiconductor Corporation
 * Copyright (C) 2019 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __SOC_REALTEK_SB2_DGB_H
#define __SOC_REALTEK_SB2_DGB_H

#include <linux/ktime.h>

enum {
	SB2_DBG_SOURCE_SCPU,
	SB2_DBG_SOURCE_ACPU,
	SB2_DBG_SOURCE_PCPU,
};

enum {
	SB2_DBG_ACCESS_WRITE,
	SB2_DBG_ACCESS_READ,
	SB2_DBG_ACCESS_DATA,
	SB2_DBG_ACCESS_INSTRUCTION,
};

struct sb2_dbg_event_data {
	u32 raw_ints;
	u32 cpu;
	u32 rw;
	u32 di;
	u32 addr;
	ktime_t cur_time;
};

enum {
	SB2_INV_SCPU_SWC,
	SB2_INV_SCPU,
	SB2_INV_ACPU,
	SB2_INV_PCPU,
};

struct sb2_inv_event_data {
	u32 raw_ints;
	u32 addr;
	u32 inv_cpu;
	u32 timeout_th;
	ktime_t cur_time;
};

int sb2_dbg_register_dbg_notifier(struct notifier_block *nb);
int sb2_dbg_unregister_dbg_notifier(struct notifier_block *nb);
int sb2_dbg_register_inv_notifier(struct notifier_block *nb);
int sb2_dbg_unregister_inv_notifier(struct notifier_block *nb);

void sb2_dbg_disable_default_handlers(void);
void sb2_dbg_enable_default_handlers(void);
static inline void sb2_dbg_add_default_handlers(void)
{
	sb2_dbg_enable_default_handlers();
}
static inline void sb2_dbg_remove_default_handlers(void)
{
	sb2_dbg_disable_default_handlers();
}

int sb2_dbg_ready(void);
int sb2_dbg_disable_mem_monitor(int i);
int sb2_dbg_scpu_monitor(int which, u32 start, u32 end, u32 d_i, u32 r_w);
int sb2_dbg_acpu_monitor(int which, u32 start, u32 end, u32 d_i, u32 r_w);

#endif
