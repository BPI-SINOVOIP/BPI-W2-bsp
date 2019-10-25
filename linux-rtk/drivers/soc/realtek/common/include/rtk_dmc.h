/*
 * rtk_dmc.h
 *
 * Copyright (c) 2019 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#ifndef __RTK_DMC_H_INCLUDED
#define __RTK_DMC_H_INCLUDED

#define DMC_OFFSET                      (0x800)
#define DMC_SCH_INDEX                   (DMC_OFFSET + 0x300)
#define DMC_SCH_DATA                    (DMC_OFFSET + 0x304)

#define DMC_SYS_CTRL                    (0x30)
#define DMC_MISC                        (0x31)
#define DMC_CPU_GPU_AXI_AGENT           (0x32)
#define DMC_CPU_GPU_SCH                 (0x33)
#define DMC_RD_BW_ALLOC                 (0x34)
#define DMC_WR_BW_ALLOC                 (0x35)
#define DMC_PC_CTRL                     (0x36)
#define DMC_PC_CPU_REQ_NUM              (0x37)
#define DMC_PC_CPU_ACC_LAT              (0x38)
#define DMC_PC_GPU_REQ_NUM              (0x39)
#define DMC_PC_GPU_ACC_LAT              (0x3a)

static inline bool dmc_valid_reg(u32 reg)
{
	return DMC_SYS_CTRL <= reg && reg <= DMC_PC_GPU_ACC_LAT;
}

#endif
