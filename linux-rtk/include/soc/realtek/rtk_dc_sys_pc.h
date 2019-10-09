/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __SOC_REALTEK_DCSYS_PC_H__
#define __SOC_REALTEK_DCSYS_PC_H__

enum DC_PC_BRIDGE_ID {
	DC_PC_BRIDGE_ID_VO      = 0x0,
	DC_PC_BRIDGE_ID_SB0     = 0x1,
	DC_PC_BRIDGE_ID_SB1     = 0x2,
	DC_PC_BRIDGE_ID_GPU     = 0x3,
	DC_PC_BRIDGE_ID_AVK_CPU = 0x4,
	DC_PC_BRIDGE_ID_SB3     = 0x5,
	DC_PC_BRIDGE_ID_VE      = 0x6,
	DC_PC_BRIDGE_ID_SE      = 0x7,
	DC_PC_BRIDGE_ID_MIPI    = 0x8,
	DC_PC_BRIDGE_ID_SATA    = 0x9,
	DC_PC_BRIDGE_ID_SB4     = 0xa,
	DC_PC_BRIDGE_ID_DIP     = 0xb,
	DC_PC_BRIDGE_ID_HSE     = 0xc,
};

#define __BID(_id) ((_id) << 3)

enum DC_PC_PROG_ID {
	/* VO */
	DC_PC_PROG_ID_VO       = __BID(DC_PC_BRIDGE_ID_VO) | 0x0,
	/* SB0 */
	DC_PC_PROG_ID_AIO      = __BID(DC_PC_BRIDGE_ID_SB0) | 0x2,
	/* SB1 */
	DC_PC_PROG_ID_CP       = __BID(DC_PC_BRIDGE_ID_SB1) | 0x1,
	DC_PC_PROG_ID_NAT      = __BID(DC_PC_BRIDGE_ID_SB1) | 0x2, /* 129x */
	DC_PC_PROG_ID_MD       = __BID(DC_PC_BRIDGE_ID_SB1) | 0x3,
	DC_PC_PROG_ID_NAT2     = __BID(DC_PC_BRIDGE_ID_SB1) | 0x4, /* 129x */
	DC_PC_PROG_ID_JPEG     = __BID(DC_PC_BRIDGE_ID_SB1) | 0x5,
	DC_PC_PROG_ID_TP       = __BID(DC_PC_BRIDGE_ID_SB1) | 0x7,
	/* GPU */
	DC_PC_PROG_ID_GPU      = __BID(DC_PC_BRIDGE_ID_GPU) | 0x1,
	/* AVK_CPU */
	DC_PC_PROG_ID_SCPU     = __BID(DC_PC_BRIDGE_ID_AVK_CPU) | 0x0,
	DC_PC_PROG_ID_KCPU     = __BID(DC_PC_BRIDGE_ID_AVK_CPU) | 0x1, /* 129x */
	DC_PC_PROG_ID_HIF      = __BID(DC_PC_BRIDGE_ID_AVK_CPU) | 0x2, /* 139x */
	DC_PC_PROG_ID_ACPU     = __BID(DC_PC_BRIDGE_ID_AVK_CPU) | 0x3,
	DC_PC_PROG_ID_SCPU_SWC = __BID(DC_PC_BRIDGE_ID_AVK_CPU) | 0x5, /* 139x */
	/* SB3 */
	DC_PC_PROG_ID_AEE      = __BID(DC_PC_BRIDGE_ID_SB3) | 0x0,
	DC_PC_PROG_ID_ADE      = __BID(DC_PC_BRIDGE_ID_SB3) | 0x1,
	DC_PC_PROG_ID_USB      = __BID(DC_PC_BRIDGE_ID_SB3) | 0x2,
	DC_PC_PROG_ID_SD       = __BID(DC_PC_BRIDGE_ID_SB3) | 0x3, /* 139x */
	DC_PC_PROG_ID_PCIE     = __BID(DC_PC_BRIDGE_ID_SB3) | 0x4, /* 139x */
	DC_PC_PROG_ID_SDIO     = __BID(DC_PC_BRIDGE_ID_SB3) | 0x5, /* 139x */
	DC_PC_PROG_ID_ETN      = __BID(DC_PC_BRIDGE_ID_SB3) | 0x6,
	/* VE */
	DC_PC_PROG_ID_VE1      = __BID(DC_PC_BRIDGE_ID_VE) | 0x0,
	DC_PC_PROG_ID_VE2      = __BID(DC_PC_BRIDGE_ID_VE) | 0x1,
	DC_PC_PROG_ID_VE3      = __BID(DC_PC_BRIDGE_ID_VE) | 0x2,
	/* SE */
	DC_PC_PROG_ID_SE       = __BID(DC_PC_BRIDGE_ID_SE) | 0x0,
	/* MIPI */
	DC_PC_PROG_ID_MIPI     = __BID(DC_PC_BRIDGE_ID_MIPI) | 0x0,
	/* SATA */
	DC_PC_PROG_ID_SATA     = __BID(DC_PC_BRIDGE_ID_SATA) | 0x0,
	/* SB4 */
	DC_PC_PROG_ID_CR       = __BID(DC_PC_BRIDGE_ID_SB4) | 0x0, /* 129x */
	DC_PC_PROG_ID_EMMC     = __BID(DC_PC_BRIDGE_ID_SB4) | 0x0, /* 139x */
	DC_PC_PROG_ID_NF       = __BID(DC_PC_BRIDGE_ID_SB4) | 0x3,
	DC_PC_PROG_ID_PCIE0    = __BID(DC_PC_BRIDGE_ID_SB4) | 0x4, /* 129x */
	DC_PC_PROG_ID_PCIE1    = __BID(DC_PC_BRIDGE_ID_SB4) | 0x6, /* 129x */
	/* DIP */
	DC_PC_PROG_ID_DIP      = __BID(DC_PC_BRIDGE_ID_DIP) | 0x0, /* 139x */
	/* HSE */
	DC_PC_PROG_ID_HSE_REE  = __BID(DC_PC_BRIDGE_ID_HSE) | 0x0, /* 139x */
	DC_PC_PROG_ID_HSE_TEE  = __BID(DC_PC_BRIDGE_ID_HSE) | 0x5, /* 139x */
};

struct dcsys_pc_prog_data {
	int prog_sel;
	int dc_sel;
	unsigned int acc_lat;
	unsigned int max_lat;
	unsigned int req;
	unsigned int ack;
};

int dcsys_pc_prog_configure(int idx, int prog, int dc_sel);
int dcsys_pc_prog_get_data(int idx, struct dcsys_pc_prog_data *data);

struct dcsys_pc_global_data {
	unsigned int mon;
	unsigned int idl;
	unsigned int ack;
};

int dcsys_pc_global_get_data(int idx, struct dcsys_pc_global_data *data);


struct dcsys_pc;

struct dcsys_pc *dcsys_pc_simple_get(struct device *dev);
void dcsys_pc_put(struct dcsys_pc *pc);

#define DCSYS_PC_FORCE_SET  0x1
int dcsys_pc_set_owner(struct dcsys_pc *pc, unsigned int flags);
int dcsys_pc_clear_owner(struct dcsys_pc *pc);
int dcsys_pc_is_owner(struct dcsys_pc *pc);

int dcsys_pc_is_stopped(struct dcsys_pc *pc);
int dcsys_pc_start(struct dcsys_pc *pc);
int dcsys_pc_stop(struct dcsys_pc *pc);

#define DCSYS_PC_OWNER_SET      1
#define DCSYS_PC_OWNER_CLEAR    2
int dcsys_pc_register_notifier(struct notifier_block *nb);
int dcsys_pc_unregister_notifier(struct notifier_block *nb);

#endif
