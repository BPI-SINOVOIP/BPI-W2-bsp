/*
 * rtk_dcsys.h
 *
 * Copyright (c) 2019 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#ifndef __RTK_DCSYS_H_INCLUDED
#define __RTK_DCSYS_H_INCLUDED

#define DCSYS_MISC                      (0x004)
#define DCSYS_PC_CTRL                   (0x030)
#define DCSYS_PC_TOTA_MON_NUM_0         (0x034)
#define DCSYS_PC_TOTA_ACK_NUM_0         (0x038)
#define DCSYS_PC_TOTA_IDL_NUM_0         (0x03c)
#define DCSYS_PC_TOTA_MON_NUM_1         (0x040)
#define DCSYS_PC_TOTA_ACK_NUM_1         (0x044)
#define DCSYS_PC_TOTA_IDL_NUM_1         (0x048)
#define DCSYS_PC_SYSH_PROG_CTRL         (0x050)
#define DCSYS_PC_SYSH_PROG_CTRL_2       (0x500)
#define DCSYS_PC_SYSH_PROG_CTRL_3       (0x504)
#define DCSYS_PC_SYS_PROG_CTRL          (0x054)
#define DCSYS_PC_SYSH_PROG_0_ACC_LAT    (0x060)
#define DCSYS_PC_SYSH_PROG_0_MAX_LAT    (0x064)
#define DCSYS_PC_SYSH_PROG_0_REQ_NUM    (0x068)
#define DCSYS_PC_SYSH_PROG_0_ACK_NUM    (0x06c)
#define DCSYS_PC_SYSH_PROG_1_ACC_LAT    (0x070)
#define DCSYS_PC_SYSH_PROG_1_MAX_LAT    (0x074)
#define DCSYS_PC_SYSH_PROG_1_REQ_NUM    (0x078)
#define DCSYS_PC_SYSH_PROG_1_ACK_NUM    (0x07c)
#define DCSYS_PC_SYSH_PROG_2_ACC_LAT    (0x080)
#define DCSYS_PC_SYSH_PROG_2_MAX_LAT    (0x084)
#define DCSYS_PC_SYSH_PROG_2_REQ_NUM    (0x088)
#define DCSYS_PC_SYSH_PROG_2_ACK_NUM    (0x08c)
#define DCSYS_PC_SYSH_PROG_3_ACC_LAT    (0x510)
#define DCSYS_PC_SYSH_PROG_3_MAX_LAT    (0x514)
#define DCSYS_PC_SYSH_PROG_3_REQ_NUM    (0x518)
#define DCSYS_PC_SYSH_PROG_3_ACK_NUM    (0x51c)
#define DCSYS_PC_SYSH_PROG_4_ACC_LAT    (0x520)
#define DCSYS_PC_SYSH_PROG_4_MAX_LAT    (0x524)
#define DCSYS_PC_SYSH_PROG_4_REQ_NUM    (0x528)
#define DCSYS_PC_SYSH_PROG_4_ACK_NUM    (0x52c)
#define DCSYS_PC_SYSH_PROG_5_ACC_LAT    (0x530)
#define DCSYS_PC_SYSH_PROG_5_MAX_LAT    (0x534)
#define DCSYS_PC_SYSH_PROG_5_REQ_NUM    (0x538)
#define DCSYS_PC_SYSH_PROG_5_ACK_NUM    (0x53c)
#define DCSYS_PC_SYSH_PROG_6_ACC_LAT    (0x540)
#define DCSYS_PC_SYSH_PROG_6_MAX_LAT    (0x544)
#define DCSYS_PC_SYSH_PROG_6_REQ_NUM    (0x548)
#define DCSYS_PC_SYSH_PROG_6_ACK_NUM    (0x54c)
#define DCSYS_PC_SYSH_PROG_7_ACC_LAT    (0x550)
#define DCSYS_PC_SYSH_PROG_7_MAX_LAT    (0x554)
#define DCSYS_PC_SYSH_PROG_7_REQ_NUM    (0x558)
#define DCSYS_PC_SYSH_PROG_7_ACK_NUM    (0x55c)
#define DCSYS_PC_SYS_PROG_0_ACC_LAT     (0x090)
#define DCSYS_PC_SYS_PROG_0_MAX_LAT     (0x094)
#define DCSYS_PC_SYS_PROG_0_REQ_NUM     (0x098)
#define DCSYS_PC_SYS_PROG_0_ACK_NUM     (0x09c)
#define DCSYS_PC_SYS_PROG_1_ACC_LAT     (0x0a0)
#define DCSYS_PC_SYS_PROG_1_MAX_LAT     (0x0a4)
#define DCSYS_PC_SYS_PROG_1_REQ_NUM     (0x0a8)
#define DCSYS_PC_SYS_PROG_1_ACK_NUM     (0x0ac)
#define DCSYS_PC_SYS_PROG_2_ACC_LAT     (0x0b0)
#define DCSYS_PC_SYS_PROG_2_MAX_LAT     (0x0b4)
#define DCSYS_PC_SYS_PROG_2_REQ_NUM     (0x0b8)
#define DCSYS_PC_SYS_PROG_2_ACK_NUM     (0x0bc)
#define DCSYS_PC_CMD_ANALYSIS_SEL       (0x560)
#define DCSYS_PC0_CMD_ANALYSIS_0        (0x564)
#define DCSYS_PC1_CMD_ANALYSIS_0        (0xA00)
#define DCSYS_PC2_CMD_ANALYSIS_0        (0xA74)
#define DCSYS_PC3_CMD_ANALYSIS_0        (0xAE8)

#define DCSYS_PC_SYSH_PROG_0_CTRL       DCSYS_PC_SYSH_PROG_CTRL
#define DCSYS_PC_SYSH_PROG_0_CTRL_MASK  (0xff)
#define DCSYS_PC_SYSH_PROG_1_CTRL       DCSYS_PC_SYSH_PROG_CTRL
#define DCSYS_PC_SYSH_PROG_1_CTRL_MASK  (0xff00)
#define DCSYS_PC_SYSH_PROG_2_CTRL       DCSYS_PC_SYSH_PROG_CTRL
#define DCSYS_PC_SYSH_PROG_2_CTRL_MASK  (0xff0000)
#define DCSYS_PC_SYSH_PROG_3_CTRL       DCSYS_PC_SYSH_PROG_CTRL_2
#define DCSYS_PC_SYSH_PROG_3_CTRL_MASK  (0xff)
#define DCSYS_PC_SYSH_PROG_4_CTRL       DCSYS_PC_SYSH_PROG_CTRL_2
#define DCSYS_PC_SYSH_PROG_4_CTRL_MASK  (0xff00)
#define DCSYS_PC_SYSH_PROG_5_CTRL       DCSYS_PC_SYSH_PROG_CTRL_2
#define DCSYS_PC_SYSH_PROG_5_CTRL_MASK  (0xff0000)
#define DCSYS_PC_SYSH_PROG_6_CTRL       DCSYS_PC_SYSH_PROG_CTRL_3
#define DCSYS_PC_SYSH_PROG_6_CTRL_MASK  (0xff)
#define DCSYS_PC_SYSH_PROG_7_CTRL       DCSYS_PC_SYSH_PROG_CTRL_3
#define DCSYS_PC_SYSH_PROG_7_CTRL_MASK  (0xff00)

#define DCSYS_PC_SYS_PROG_0_CTRL        DCSYS_PC_SYS_PROG_CTRL
#define DCSYS_PC_SYS_PROG_0_CTRL_MASK   (0xff)
#define DCSYS_PC_SYS_PROG_1_CTRL        DCSYS_PC_SYS_PROG_CTRL
#define DCSYS_PC_SYS_PROG_1_CTRL_MASK   (0xff00)
#define DCSYS_PC_SYS_PROG_2_CTRL        DCSYS_PC_SYS_PROG_CTRL
#define DCSYS_PC_SYS_PROG_2_CTRL_MASK   (0xff0000)

#define DCSYS_PC_CA_SEL_0_MASK          (0xf)
#define DCSYS_PC_CA_SEL_1_MASK          (0xf0)
#define DCSYS_PC_CA_SEL_2_MASK          (0xf00)
#define DCSYS_PC_CA_SEL_3_MASK          (0xf000)

#endif
