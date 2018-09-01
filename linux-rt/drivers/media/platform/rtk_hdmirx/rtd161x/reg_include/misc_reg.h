/*
 * misc_reg.h - RTK hdmi rx driver header file
 *
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#define MIS_SCPU_CLK90K_LO                                                           0x40
#define MIS_SCPU_CLK90K_LO_reg_addr                                                  "0x9801B540"
#define MIS_SCPU_CLK90K_LO_reg                                                       0x9801B540
#define set_MIS_SCPU_CLK90K_LO_reg(data)   (*((volatile unsigned int*) MIS_SCPU_CLK90K_LO_reg)=data)
#define get_MIS_SCPU_CLK90K_LO_reg   (*((volatile unsigned int*) MIS_SCPU_CLK90K_LO_reg))
#define MIS_SCPU_CLK90K_LO_inst_adr                                                  "0x0050"
#define MIS_SCPU_CLK90K_LO_inst                                                      0x0050
#define MIS_SCPU_CLK90K_LO_val_shift                                                 (0)
#define MIS_SCPU_CLK90K_LO_val_mask                                                  (0xFFFFFFFF)
#define MIS_SCPU_CLK90K_LO_val(data)                                                 (0xFFFFFFFF&((data)<<0))
#define MIS_SCPU_CLK90K_LO_val_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define MIS_SCPU_CLK90K_LO_get_val(data)                                             ((0xFFFFFFFF&(data))>>0)
 
 
#define MIS_SCPU_CLK90K_HI                                                           0x44
#define MIS_SCPU_CLK90K_HI_reg_addr                                                  "0x9801B544"
#define MIS_SCPU_CLK90K_HI_reg                                                       0x9801B544
#define set_MIS_SCPU_CLK90K_HI_reg(data)   (*((volatile unsigned int*) MIS_SCPU_CLK90K_HI_reg)=data)
#define get_MIS_SCPU_CLK90K_HI_reg   (*((volatile unsigned int*) MIS_SCPU_CLK90K_HI_reg))
#define MIS_SCPU_CLK90K_HI_inst_adr                                                  "0x0051"
#define MIS_SCPU_CLK90K_HI_inst                                                      0x0051
#define MIS_SCPU_CLK90K_HI_val_shift                                                 (0)
#define MIS_SCPU_CLK90K_HI_val_mask                                                  (0x0000FFFF)
#define MIS_SCPU_CLK90K_HI_val(data)                                                 (0x0000FFFF&((data)<<0))
#define MIS_SCPU_CLK90K_HI_val_src(data)                                             ((0x0000FFFF&(data))>>0)
#define MIS_SCPU_CLK90K_HI_get_val(data)                                             ((0x0000FFFF&(data))>>0)

