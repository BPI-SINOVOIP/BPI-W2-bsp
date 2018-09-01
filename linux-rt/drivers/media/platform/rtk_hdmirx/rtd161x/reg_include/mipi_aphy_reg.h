/*
 * mipi_aphy_reg.h - RTK hdmi rx driver header file
 *
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */


#ifndef _MIPI_APHY_REG_H_INCLUDED_
#define _MIPI_APHY_REG_H_INCLUDED_

#define MIPI_APHY_REG0                                                               0x00
#define MIPI_APHY_REG0_reg_addr                                                      "0x98004000"
#define MIPI_APHY_REG0_reg                                                           0x98004000
#define set_MIPI_APHY_REG0_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG0_reg)=data)
#define get_MIPI_APHY_REG0_reg   (*((volatile unsigned int*) MIPI_APHY_REG0_reg))
#define MIPI_APHY_REG0_inst_adr                                                      "0x0000"
#define MIPI_APHY_REG0_inst                                                          0x0000
#define MIPI_APHY_REG0_R50_CAL_RG_shift                                              (0)
#define MIPI_APHY_REG0_R50_CAL_RG_mask                                               (0x0000003F)
#define MIPI_APHY_REG0_R50_CAL_RG(data)                                              (0x0000003F&((data)<<0))
#define MIPI_APHY_REG0_R50_CAL_RG_src(data)                                          ((0x0000003F&(data))>>0)
#define MIPI_APHY_REG0_get_R50_CAL_RG(data)                                          ((0x0000003F&(data))>>0)


#define MIPI_APHY_REG1                                                               0x04
#define MIPI_APHY_REG1_reg_addr                                                      "0x98004004"
#define MIPI_APHY_REG1_reg                                                           0x98004004
#define set_MIPI_APHY_REG1_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG1_reg)=data)
#define get_MIPI_APHY_REG1_reg   (*((volatile unsigned int*) MIPI_APHY_REG1_reg))
#define MIPI_APHY_REG1_inst_adr                                                      "0x0001"
#define MIPI_APHY_REG1_inst                                                          0x0001
#define MIPI_APHY_REG1_EN_SKW_shift                                                  (7)
#define MIPI_APHY_REG1_EN_SKW_mask                                                   (0x00000080)
#define MIPI_APHY_REG1_EN_SKW(data)                                                  (0x00000080&((data)<<7))
#define MIPI_APHY_REG1_EN_SKW_src(data)                                              ((0x00000080&(data))>>7)
#define MIPI_APHY_REG1_get_EN_SKW(data)                                              ((0x00000080&(data))>>7)
#define MIPI_APHY_REG1_EN_AUTO_SKW_shift                                             (6)
#define MIPI_APHY_REG1_EN_AUTO_SKW_mask                                              (0x00000040)
#define MIPI_APHY_REG1_EN_AUTO_SKW(data)                                             (0x00000040&((data)<<6))
#define MIPI_APHY_REG1_EN_AUTO_SKW_src(data)                                         ((0x00000040&(data))>>6)
#define MIPI_APHY_REG1_get_EN_AUTO_SKW(data)                                         ((0x00000040&(data))>>6)
#define MIPI_APHY_REG1_PAUSEB_SKW_CAL_shift                                          (5)
#define MIPI_APHY_REG1_PAUSEB_SKW_CAL_mask                                           (0x00000020)
#define MIPI_APHY_REG1_PAUSEB_SKW_CAL(data)                                          (0x00000020&((data)<<5))
#define MIPI_APHY_REG1_PAUSEB_SKW_CAL_src(data)                                      ((0x00000020&(data))>>5)
#define MIPI_APHY_REG1_get_PAUSEB_SKW_CAL(data)                                      ((0x00000020&(data))>>5)
#define MIPI_APHY_REG1_EN_AUTO_STPB_SKW_CAL_RG_shift                                 (4)
#define MIPI_APHY_REG1_EN_AUTO_STPB_SKW_CAL_RG_mask                                  (0x00000010)
#define MIPI_APHY_REG1_EN_AUTO_STPB_SKW_CAL_RG(data)                                 (0x00000010&((data)<<4))
#define MIPI_APHY_REG1_EN_AUTO_STPB_SKW_CAL_RG_src(data)                             ((0x00000010&(data))>>4)
#define MIPI_APHY_REG1_get_EN_AUTO_STPB_SKW_CAL_RG(data)                             ((0x00000010&(data))>>4)
#define MIPI_APHY_REG1_EN_OSK_shift                                                  (3)
#define MIPI_APHY_REG1_EN_OSK_mask                                                   (0x00000008)
#define MIPI_APHY_REG1_EN_OSK(data)                                                  (0x00000008&((data)<<3))
#define MIPI_APHY_REG1_EN_OSK_src(data)                                              ((0x00000008&(data))>>3)
#define MIPI_APHY_REG1_get_EN_OSK(data)                                              ((0x00000008&(data))>>3)
#define MIPI_APHY_REG1_EN_AUTO_OSK_shift                                             (2)
#define MIPI_APHY_REG1_EN_AUTO_OSK_mask                                              (0x00000004)
#define MIPI_APHY_REG1_EN_AUTO_OSK(data)                                             (0x00000004&((data)<<2))
#define MIPI_APHY_REG1_EN_AUTO_OSK_src(data)                                         ((0x00000004&(data))>>2)
#define MIPI_APHY_REG1_get_EN_AUTO_OSK(data)                                         ((0x00000004&(data))>>2)
#define MIPI_APHY_REG1_EN_R50_CAL_RG_shift                                           (1)
#define MIPI_APHY_REG1_EN_R50_CAL_RG_mask                                            (0x00000002)
#define MIPI_APHY_REG1_EN_R50_CAL_RG(data)                                           (0x00000002&((data)<<1))
#define MIPI_APHY_REG1_EN_R50_CAL_RG_src(data)                                       ((0x00000002&(data))>>1)
#define MIPI_APHY_REG1_get_EN_R50_CAL_RG(data)                                       ((0x00000002&(data))>>1)
#define MIPI_APHY_REG1_EN_R50_AUTO_CAL_RG_shift                                      (0)
#define MIPI_APHY_REG1_EN_R50_AUTO_CAL_RG_mask                                       (0x00000001)
#define MIPI_APHY_REG1_EN_R50_AUTO_CAL_RG(data)                                      (0x00000001&((data)<<0))
#define MIPI_APHY_REG1_EN_R50_AUTO_CAL_RG_src(data)                                  ((0x00000001&(data))>>0)
#define MIPI_APHY_REG1_get_EN_R50_AUTO_CAL_RG(data)                                  ((0x00000001&(data))>>0)


#define MIPI_APHY_REG2                                                               0x08
#define MIPI_APHY_REG2_reg_addr                                                      "0x98004008"
#define MIPI_APHY_REG2_reg                                                           0x98004008
#define set_MIPI_APHY_REG2_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG2_reg)=data)
#define get_MIPI_APHY_REG2_reg   (*((volatile unsigned int*) MIPI_APHY_REG2_reg))
#define MIPI_APHY_REG2_inst_adr                                                      "0x0002"
#define MIPI_APHY_REG2_inst                                                          0x0002
#define MIPI_APHY_REG2_SEL0_PAUSED_SKW_K_RG_shift                                    (7)
#define MIPI_APHY_REG2_SEL0_PAUSED_SKW_K_RG_mask                                     (0x00000080)
#define MIPI_APHY_REG2_SEL0_PAUSED_SKW_K_RG(data)                                    (0x00000080&((data)<<7))
#define MIPI_APHY_REG2_SEL0_PAUSED_SKW_K_RG_src(data)                                ((0x00000080&(data))>>7)
#define MIPI_APHY_REG2_get_SEL0_PAUSED_SKW_K_RG(data)                                ((0x00000080&(data))>>7)
#define MIPI_APHY_REG2_LGTH_D0_shift                                                 (4)
#define MIPI_APHY_REG2_LGTH_D0_mask                                                  (0x00000070)
#define MIPI_APHY_REG2_LGTH_D0(data)                                                 (0x00000070&((data)<<4))
#define MIPI_APHY_REG2_LGTH_D0_src(data)                                             ((0x00000070&(data))>>4)
#define MIPI_APHY_REG2_get_LGTH_D0(data)                                             ((0x00000070&(data))>>4)
#define MIPI_APHY_REG2_PDBH_k_shift                                                  (3)
#define MIPI_APHY_REG2_PDBH_k_mask                                                   (0x00000008)
#define MIPI_APHY_REG2_PDBH_k(data)                                                  (0x00000008&((data)<<3))
#define MIPI_APHY_REG2_PDBH_k_src(data)                                              ((0x00000008&(data))>>3)
#define MIPI_APHY_REG2_get_PDBH_k(data)                                              ((0x00000008&(data))>>3)
#define MIPI_APHY_REG2_PWDB_OSK_shift                                                (2)
#define MIPI_APHY_REG2_PWDB_OSK_mask                                                 (0x00000004)
#define MIPI_APHY_REG2_PWDB_OSK(data)                                                (0x00000004&((data)<<2))
#define MIPI_APHY_REG2_PWDB_OSK_src(data)                                            ((0x00000004&(data))>>2)
#define MIPI_APHY_REG2_get_PWDB_OSK(data)                                            ((0x00000004&(data))>>2)
#define MIPI_APHY_REG2_DOUBL_PUMP_shift                                              (1)
#define MIPI_APHY_REG2_DOUBL_PUMP_mask                                               (0x00000002)
#define MIPI_APHY_REG2_DOUBL_PUMP(data)                                              (0x00000002&((data)<<1))
#define MIPI_APHY_REG2_DOUBL_PUMP_src(data)                                          ((0x00000002&(data))>>1)
#define MIPI_APHY_REG2_get_DOUBL_PUMP(data)                                          ((0x00000002&(data))>>1)
#define MIPI_APHY_REG2_ENSEL_shift                                                   (0)
#define MIPI_APHY_REG2_ENSEL_mask                                                    (0x00000001)
#define MIPI_APHY_REG2_ENSEL(data)                                                   (0x00000001&((data)<<0))
#define MIPI_APHY_REG2_ENSEL_src(data)                                               ((0x00000001&(data))>>0)
#define MIPI_APHY_REG2_get_ENSEL(data)                                               ((0x00000001&(data))>>0)


#define MIPI_APHY_REG3                                                               0x0C
#define MIPI_APHY_REG3_reg_addr                                                      "0x9800400C"
#define MIPI_APHY_REG3_reg                                                           0x9800400C
#define set_MIPI_APHY_REG3_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG3_reg)=data)
#define get_MIPI_APHY_REG3_reg   (*((volatile unsigned int*) MIPI_APHY_REG3_reg))
#define MIPI_APHY_REG3_inst_adr                                                      "0x0003"
#define MIPI_APHY_REG3_inst                                                          0x0003
#define MIPI_APHY_REG3_HSPAMP0_RL_RG_shift                                           (0)
#define MIPI_APHY_REG3_HSPAMP0_RL_RG_mask                                            (0x0000003F)
#define MIPI_APHY_REG3_HSPAMP0_RL_RG(data)                                           (0x0000003F&((data)<<0))
#define MIPI_APHY_REG3_HSPAMP0_RL_RG_src(data)                                       ((0x0000003F&(data))>>0)
#define MIPI_APHY_REG3_get_HSPAMP0_RL_RG(data)                                       ((0x0000003F&(data))>>0)


#define MIPI_APHY_REG4                                                               0x10
#define MIPI_APHY_REG4_reg_addr                                                      "0x98004010"
#define MIPI_APHY_REG4_reg                                                           0x98004010
#define set_MIPI_APHY_REG4_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG4_reg)=data)
#define get_MIPI_APHY_REG4_reg   (*((volatile unsigned int*) MIPI_APHY_REG4_reg))
#define MIPI_APHY_REG4_inst_adr                                                      "0x0004"
#define MIPI_APHY_REG4_inst                                                          0x0004
#define MIPI_APHY_REG4_HSPAMP1_RL_RG_shift                                           (0)
#define MIPI_APHY_REG4_HSPAMP1_RL_RG_mask                                            (0x0000003F)
#define MIPI_APHY_REG4_HSPAMP1_RL_RG(data)                                           (0x0000003F&((data)<<0))
#define MIPI_APHY_REG4_HSPAMP1_RL_RG_src(data)                                       ((0x0000003F&(data))>>0)
#define MIPI_APHY_REG4_get_HSPAMP1_RL_RG(data)                                       ((0x0000003F&(data))>>0)


#define MIPI_APHY_REG5                                                               0x14
#define MIPI_APHY_REG5_reg_addr                                                      "0x98004014"
#define MIPI_APHY_REG5_reg                                                           0x98004014
#define set_MIPI_APHY_REG5_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG5_reg)=data)
#define get_MIPI_APHY_REG5_reg   (*((volatile unsigned int*) MIPI_APHY_REG5_reg))
#define MIPI_APHY_REG5_inst_adr                                                      "0x0005"
#define MIPI_APHY_REG5_inst                                                          0x0005
#define MIPI_APHY_REG5_SDATA0_SKW_RG_shift                                           (4)
#define MIPI_APHY_REG5_SDATA0_SKW_RG_mask                                            (0x000000F0)
#define MIPI_APHY_REG5_SDATA0_SKW_RG(data)                                           (0x000000F0&((data)<<4))
#define MIPI_APHY_REG5_SDATA0_SKW_RG_src(data)                                       ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG5_get_SDATA0_SKW_RG(data)                                       ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG5_SDATA1_SKW_RG_shift                                           (0)
#define MIPI_APHY_REG5_SDATA1_SKW_RG_mask                                            (0x0000000F)
#define MIPI_APHY_REG5_SDATA1_SKW_RG(data)                                           (0x0000000F&((data)<<0))
#define MIPI_APHY_REG5_SDATA1_SKW_RG_src(data)                                       ((0x0000000F&(data))>>0)
#define MIPI_APHY_REG5_get_SDATA1_SKW_RG(data)                                       ((0x0000000F&(data))>>0)


#define MIPI_APHY_REG6                                                               0x18
#define MIPI_APHY_REG6_reg_addr                                                      "0x98004018"
#define MIPI_APHY_REG6_reg                                                           0x98004018
#define set_MIPI_APHY_REG6_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG6_reg)=data)
#define get_MIPI_APHY_REG6_reg   (*((volatile unsigned int*) MIPI_APHY_REG6_reg))
#define MIPI_APHY_REG6_inst_adr                                                      "0x0006"
#define MIPI_APHY_REG6_inst                                                          0x0006
#define MIPI_APHY_REG6_SDATA2_SKW_RG_shift                                           (4)
#define MIPI_APHY_REG6_SDATA2_SKW_RG_mask                                            (0x000000F0)
#define MIPI_APHY_REG6_SDATA2_SKW_RG(data)                                           (0x000000F0&((data)<<4))
#define MIPI_APHY_REG6_SDATA2_SKW_RG_src(data)                                       ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG6_get_SDATA2_SKW_RG(data)                                       ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG6_SDATA3_SKW_RG_shift                                           (0)
#define MIPI_APHY_REG6_SDATA3_SKW_RG_mask                                            (0x0000000F)
#define MIPI_APHY_REG6_SDATA3_SKW_RG(data)                                           (0x0000000F&((data)<<0))
#define MIPI_APHY_REG6_SDATA3_SKW_RG_src(data)                                       ((0x0000000F&(data))>>0)
#define MIPI_APHY_REG6_get_SDATA3_SKW_RG(data)                                       ((0x0000000F&(data))>>0)


#define MIPI_APHY_REG7                                                               0x1C
#define MIPI_APHY_REG7_reg_addr                                                      "0x9800401C"
#define MIPI_APHY_REG7_reg                                                           0x9800401C
#define set_MIPI_APHY_REG7_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG7_reg)=data)
#define get_MIPI_APHY_REG7_reg   (*((volatile unsigned int*) MIPI_APHY_REG7_reg))
#define MIPI_APHY_REG7_inst_adr                                                      "0x0007"
#define MIPI_APHY_REG7_inst                                                          0x0007
#define MIPI_APHY_REG7_SCLK0_SKW_RG_shift                                            (4)
#define MIPI_APHY_REG7_SCLK0_SKW_RG_mask                                             (0x000000F0)
#define MIPI_APHY_REG7_SCLK0_SKW_RG(data)                                            (0x000000F0&((data)<<4))
#define MIPI_APHY_REG7_SCLK0_SKW_RG_src(data)                                        ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG7_get_SCLK0_SKW_RG(data)                                        ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG7_SCLK1_SKW_RG_shift                                            (0)
#define MIPI_APHY_REG7_SCLK1_SKW_RG_mask                                             (0x0000000F)
#define MIPI_APHY_REG7_SCLK1_SKW_RG(data)                                            (0x0000000F&((data)<<0))
#define MIPI_APHY_REG7_SCLK1_SKW_RG_src(data)                                        ((0x0000000F&(data))>>0)
#define MIPI_APHY_REG7_get_SCLK1_SKW_RG(data)                                        ((0x0000000F&(data))>>0)


#define MIPI_APHY_REG8                                                               0x20
#define MIPI_APHY_REG8_reg_addr                                                      "0x98004020"
#define MIPI_APHY_REG8_reg                                                           0x98004020
#define set_MIPI_APHY_REG8_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG8_reg)=data)
#define get_MIPI_APHY_REG8_reg   (*((volatile unsigned int*) MIPI_APHY_REG8_reg))
#define MIPI_APHY_REG8_inst_adr                                                      "0x0008"
#define MIPI_APHY_REG8_inst                                                          0x0008
#define MIPI_APHY_REG8_SCLK2_SKW_RG_shift                                            (4)
#define MIPI_APHY_REG8_SCLK2_SKW_RG_mask                                             (0x000000F0)
#define MIPI_APHY_REG8_SCLK2_SKW_RG(data)                                            (0x000000F0&((data)<<4))
#define MIPI_APHY_REG8_SCLK2_SKW_RG_src(data)                                        ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG8_get_SCLK2_SKW_RG(data)                                        ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG8_SCLK3_SKW_RG_shift                                            (0)
#define MIPI_APHY_REG8_SCLK3_SKW_RG_mask                                             (0x0000000F)
#define MIPI_APHY_REG8_SCLK3_SKW_RG(data)                                            (0x0000000F&((data)<<0))
#define MIPI_APHY_REG8_SCLK3_SKW_RG_src(data)                                        ((0x0000000F&(data))>>0)
#define MIPI_APHY_REG8_get_SCLK3_SKW_RG(data)                                        ((0x0000000F&(data))>>0)


#define MIPI_APHY_REG9                                                               0x24
#define MIPI_APHY_REG9_reg_addr                                                      "0x98004024"
#define MIPI_APHY_REG9_reg                                                           0x98004024
#define set_MIPI_APHY_REG9_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG9_reg)=data)
#define get_MIPI_APHY_REG9_reg   (*((volatile unsigned int*) MIPI_APHY_REG9_reg))
#define MIPI_APHY_REG9_inst_adr                                                      "0x0009"
#define MIPI_APHY_REG9_inst                                                          0x0009
#define MIPI_APHY_REG9_HSAMPCK_RL_RG_shift                                           (0)
#define MIPI_APHY_REG9_HSAMPCK_RL_RG_mask                                            (0x0000003F)
#define MIPI_APHY_REG9_HSAMPCK_RL_RG(data)                                           (0x0000003F&((data)<<0))
#define MIPI_APHY_REG9_HSAMPCK_RL_RG_src(data)                                       ((0x0000003F&(data))>>0)
#define MIPI_APHY_REG9_get_HSAMPCK_RL_RG(data)                                       ((0x0000003F&(data))>>0)


#define MIPI_APHY_REG10                                                              0x28
#define MIPI_APHY_REG10_reg_addr                                                     "0x98004028"
#define MIPI_APHY_REG10_reg                                                          0x98004028
#define set_MIPI_APHY_REG10_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG10_reg)=data)
#define get_MIPI_APHY_REG10_reg   (*((volatile unsigned int*) MIPI_APHY_REG10_reg))
#define MIPI_APHY_REG10_inst_adr                                                     "0x000A"
#define MIPI_APHY_REG10_inst                                                         0x000A
#define MIPI_APHY_REG10_COUNT_RUN_shift                                              (0)
#define MIPI_APHY_REG10_COUNT_RUN_mask                                               (0x000000FF)
#define MIPI_APHY_REG10_COUNT_RUN(data)                                              (0x000000FF&((data)<<0))
#define MIPI_APHY_REG10_COUNT_RUN_src(data)                                          ((0x000000FF&(data))>>0)
#define MIPI_APHY_REG10_get_COUNT_RUN(data)                                          ((0x000000FF&(data))>>0)


#define MIPI_APHY_REG11                                                              0x2C
#define MIPI_APHY_REG11_reg_addr                                                     "0x9800402C"
#define MIPI_APHY_REG11_reg                                                          0x9800402C
#define set_MIPI_APHY_REG11_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG11_reg)=data)
#define get_MIPI_APHY_REG11_reg   (*((volatile unsigned int*) MIPI_APHY_REG11_reg))
#define MIPI_APHY_REG11_inst_adr                                                     "0x000B"
#define MIPI_APHY_REG11_inst                                                         0x000B
#define MIPI_APHY_REG11_COUNT_RUN_shift                                              (0)
#define MIPI_APHY_REG11_COUNT_RUN_mask                                               (0x00000001)
#define MIPI_APHY_REG11_COUNT_RUN(data)                                              (0x00000001&((data)<<0))
#define MIPI_APHY_REG11_COUNT_RUN_src(data)                                          ((0x00000001&(data))>>0)
#define MIPI_APHY_REG11_get_COUNT_RUN(data)                                          ((0x00000001&(data))>>0)


#define MIPI_APHY_REG12                                                              0x30
#define MIPI_APHY_REG12_reg_addr                                                     "0x98004030"
#define MIPI_APHY_REG12_reg                                                          0x98004030
#define set_MIPI_APHY_REG12_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG12_reg)=data)
#define get_MIPI_APHY_REG12_reg   (*((volatile unsigned int*) MIPI_APHY_REG12_reg))
#define MIPI_APHY_REG12_inst_adr                                                     "0x000C"
#define MIPI_APHY_REG12_inst                                                         0x000C
#define MIPI_APHY_REG12_COUNT_RT_shift                                               (0)
#define MIPI_APHY_REG12_COUNT_RT_mask                                                (0x0000007F)
#define MIPI_APHY_REG12_COUNT_RT(data)                                               (0x0000007F&((data)<<0))
#define MIPI_APHY_REG12_COUNT_RT_src(data)                                           ((0x0000007F&(data))>>0)
#define MIPI_APHY_REG12_get_COUNT_RT(data)                                           ((0x0000007F&(data))>>0)


#define MIPI_APHY_REG13                                                              0x34
#define MIPI_APHY_REG13_reg_addr                                                     "0x98004034"
#define MIPI_APHY_REG13_reg                                                          0x98004034
#define set_MIPI_APHY_REG13_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG13_reg)=data)
#define get_MIPI_APHY_REG13_reg   (*((volatile unsigned int*) MIPI_APHY_REG13_reg))
#define MIPI_APHY_REG13_inst_adr                                                     "0x000D"
#define MIPI_APHY_REG13_inst                                                         0x000D
#define MIPI_APHY_REG13_HS_CM_shift                                                  (5)
#define MIPI_APHY_REG13_HS_CM_mask                                                   (0x000000E0)
#define MIPI_APHY_REG13_HS_CM(data)                                                  (0x000000E0&((data)<<5))
#define MIPI_APHY_REG13_HS_CM_src(data)                                              ((0x000000E0&(data))>>5)
#define MIPI_APHY_REG13_get_HS_CM(data)                                              ((0x000000E0&(data))>>5)
#define MIPI_APHY_REG13_COUNT_SEL_shift                                              (0)
#define MIPI_APHY_REG13_COUNT_SEL_mask                                               (0x0000001F)
#define MIPI_APHY_REG13_COUNT_SEL(data)                                              (0x0000001F&((data)<<0))
#define MIPI_APHY_REG13_COUNT_SEL_src(data)                                          ((0x0000001F&(data))>>0)
#define MIPI_APHY_REG13_get_COUNT_SEL(data)                                          ((0x0000001F&(data))>>0)


#define MIPI_APHY_REG14                                                              0x38
#define MIPI_APHY_REG14_reg_addr                                                     "0x98004038"
#define MIPI_APHY_REG14_reg                                                          0x98004038
#define set_MIPI_APHY_REG14_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG14_reg)=data)
#define get_MIPI_APHY_REG14_reg   (*((volatile unsigned int*) MIPI_APHY_REG14_reg))
#define MIPI_APHY_REG14_inst_adr                                                     "0x000E"
#define MIPI_APHY_REG14_inst                                                         0x000E
#define MIPI_APHY_REG14_CMP_REF_shift                                                (4)
#define MIPI_APHY_REG14_CMP_REF_mask                                                 (0x000000F0)
#define MIPI_APHY_REG14_CMP_REF(data)                                                (0x000000F0&((data)<<4))
#define MIPI_APHY_REG14_CMP_REF_src(data)                                            ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG14_get_CMP_REF(data)                                            ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG14_LPAMP_REF_shift                                              (0)
#define MIPI_APHY_REG14_LPAMP_REF_mask                                               (0x0000000F)
#define MIPI_APHY_REG14_LPAMP_REF(data)                                              (0x0000000F&((data)<<0))
#define MIPI_APHY_REG14_LPAMP_REF_src(data)                                          ((0x0000000F&(data))>>0)
#define MIPI_APHY_REG14_get_LPAMP_REF(data)                                          ((0x0000000F&(data))>>0)


#define MIPI_APHY_REG15                                                              0x3C
#define MIPI_APHY_REG15_reg_addr                                                     "0x9800403C"
#define MIPI_APHY_REG15_reg                                                          0x9800403C
#define set_MIPI_APHY_REG15_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG15_reg)=data)
#define get_MIPI_APHY_REG15_reg   (*((volatile unsigned int*) MIPI_APHY_REG15_reg))
#define MIPI_APHY_REG15_inst_adr                                                     "0x000F"
#define MIPI_APHY_REG15_inst                                                         0x000F
#define MIPI_APHY_REG15_adrst_sel_shift                                              (2)
#define MIPI_APHY_REG15_adrst_sel_mask                                               (0x0000000C)
#define MIPI_APHY_REG15_adrst_sel(data)                                              (0x0000000C&((data)<<2))
#define MIPI_APHY_REG15_adrst_sel_src(data)                                          ((0x0000000C&(data))>>2)
#define MIPI_APHY_REG15_get_adrst_sel(data)                                          ((0x0000000C&(data))>>2)
#define MIPI_APHY_REG15_SEL_DIV_RG_shift                                             (0)
#define MIPI_APHY_REG15_SEL_DIV_RG_mask                                              (0x00000003)
#define MIPI_APHY_REG15_SEL_DIV_RG(data)                                             (0x00000003&((data)<<0))
#define MIPI_APHY_REG15_SEL_DIV_RG_src(data)                                         ((0x00000003&(data))>>0)
#define MIPI_APHY_REG15_get_SEL_DIV_RG(data)                                         ((0x00000003&(data))>>0)


#define MIPI_APHY_REG16                                                              0x40
#define MIPI_APHY_REG16_reg_addr                                                     "0x98004040"
#define MIPI_APHY_REG16_reg                                                          0x98004040
#define set_MIPI_APHY_REG16_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG16_reg)=data)
#define get_MIPI_APHY_REG16_reg   (*((volatile unsigned int*) MIPI_APHY_REG16_reg))
#define MIPI_APHY_REG16_inst_adr                                                     "0x0010"
#define MIPI_APHY_REG16_inst                                                         0x0010
#define MIPI_APHY_REG16_HSAMP3_RL_2RG_shift                                          (0)
#define MIPI_APHY_REG16_HSAMP3_RL_2RG_mask                                           (0x0000003F)
#define MIPI_APHY_REG16_HSAMP3_RL_2RG(data)                                          (0x0000003F&((data)<<0))
#define MIPI_APHY_REG16_HSAMP3_RL_2RG_src(data)                                      ((0x0000003F&(data))>>0)
#define MIPI_APHY_REG16_get_HSAMP3_RL_2RG(data)                                      ((0x0000003F&(data))>>0)


#define MIPI_APHY_REG17                                                              0x44
#define MIPI_APHY_REG17_reg_addr                                                     "0x98004044"
#define MIPI_APHY_REG17_reg                                                          0x98004044
#define set_MIPI_APHY_REG17_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG17_reg)=data)
#define get_MIPI_APHY_REG17_reg   (*((volatile unsigned int*) MIPI_APHY_REG17_reg))
#define MIPI_APHY_REG17_inst_adr                                                     "0x0011"
#define MIPI_APHY_REG17_inst                                                         0x0011
#define MIPI_APHY_REG17_HSAMP2_RL_2RG_shift                                          (0)
#define MIPI_APHY_REG17_HSAMP2_RL_2RG_mask                                           (0x0000003F)
#define MIPI_APHY_REG17_HSAMP2_RL_2RG(data)                                          (0x0000003F&((data)<<0))
#define MIPI_APHY_REG17_HSAMP2_RL_2RG_src(data)                                      ((0x0000003F&(data))>>0)
#define MIPI_APHY_REG17_get_HSAMP2_RL_2RG(data)                                      ((0x0000003F&(data))>>0)


#define MIPI_APHY_REG18                                                              0x48
#define MIPI_APHY_REG18_reg_addr                                                     "0x98004048"
#define MIPI_APHY_REG18_reg                                                          0x98004048
#define set_MIPI_APHY_REG18_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG18_reg)=data)
#define get_MIPI_APHY_REG18_reg   (*((volatile unsigned int*) MIPI_APHY_REG18_reg))
#define MIPI_APHY_REG18_inst_adr                                                     "0x0012"
#define MIPI_APHY_REG18_inst                                                         0x0012
#define MIPI_APHY_REG18_HSAMP1_RL_2RG_shift                                          (0)
#define MIPI_APHY_REG18_HSAMP1_RL_2RG_mask                                           (0x0000003F)
#define MIPI_APHY_REG18_HSAMP1_RL_2RG(data)                                          (0x0000003F&((data)<<0))
#define MIPI_APHY_REG18_HSAMP1_RL_2RG_src(data)                                      ((0x0000003F&(data))>>0)
#define MIPI_APHY_REG18_get_HSAMP1_RL_2RG(data)                                      ((0x0000003F&(data))>>0)


#define MIPI_APHY_REG19                                                              0x4C
#define MIPI_APHY_REG19_reg_addr                                                     "0x9800404C"
#define MIPI_APHY_REG19_reg                                                          0x9800404C
#define set_MIPI_APHY_REG19_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG19_reg)=data)
#define get_MIPI_APHY_REG19_reg   (*((volatile unsigned int*) MIPI_APHY_REG19_reg))
#define MIPI_APHY_REG19_inst_adr                                                     "0x0013"
#define MIPI_APHY_REG19_inst                                                         0x0013
#define MIPI_APHY_REG19_HSAMP0_RL_2RG_shift                                          (0)
#define MIPI_APHY_REG19_HSAMP0_RL_2RG_mask                                           (0x0000003F)
#define MIPI_APHY_REG19_HSAMP0_RL_2RG(data)                                          (0x0000003F&((data)<<0))
#define MIPI_APHY_REG19_HSAMP0_RL_2RG_src(data)                                      ((0x0000003F&(data))>>0)
#define MIPI_APHY_REG19_get_HSAMP0_RL_2RG(data)                                      ((0x0000003F&(data))>>0)


#define MIPI_APHY_REG20                                                              0x50
#define MIPI_APHY_REG20_reg_addr                                                     "0x98004050"
#define MIPI_APHY_REG20_reg                                                          0x98004050
#define set_MIPI_APHY_REG20_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG20_reg)=data)
#define get_MIPI_APHY_REG20_reg   (*((volatile unsigned int*) MIPI_APHY_REG20_reg))
#define MIPI_APHY_REG20_inst_adr                                                     "0x0014"
#define MIPI_APHY_REG20_inst                                                         0x0014
#define MIPI_APHY_REG20_HSAMPCK_RL_2RG_shift                                         (0)
#define MIPI_APHY_REG20_HSAMPCK_RL_2RG_mask                                          (0x0000003F)
#define MIPI_APHY_REG20_HSAMPCK_RL_2RG(data)                                         (0x0000003F&((data)<<0))
#define MIPI_APHY_REG20_HSAMPCK_RL_2RG_src(data)                                     ((0x0000003F&(data))>>0)
#define MIPI_APHY_REG20_get_HSAMPCK_RL_2RG(data)                                     ((0x0000003F&(data))>>0)


#define MIPI_APHY_REG21                                                              0x54
#define MIPI_APHY_REG21_reg_addr                                                     "0x98004054"
#define MIPI_APHY_REG21_reg                                                          0x98004054
#define set_MIPI_APHY_REG21_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG21_reg)=data)
#define get_MIPI_APHY_REG21_reg   (*((volatile unsigned int*) MIPI_APHY_REG21_reg))
#define MIPI_APHY_REG21_inst_adr                                                     "0x0015"
#define MIPI_APHY_REG21_inst                                                         0x0015
#define MIPI_APHY_REG21_CLK0_DLY_CODE_2RG_shift                                      (4)
#define MIPI_APHY_REG21_CLK0_DLY_CODE_2RG_mask                                       (0x000000F0)
#define MIPI_APHY_REG21_CLK0_DLY_CODE_2RG(data)                                      (0x000000F0&((data)<<4))
#define MIPI_APHY_REG21_CLK0_DLY_CODE_2RG_src(data)                                  ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG21_get_CLK0_DLY_CODE_2RG(data)                                  ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG21_CLK1_DLY_CODE_2RG_shift                                      (0)
#define MIPI_APHY_REG21_CLK1_DLY_CODE_2RG_mask                                       (0x0000000F)
#define MIPI_APHY_REG21_CLK1_DLY_CODE_2RG(data)                                      (0x0000000F&((data)<<0))
#define MIPI_APHY_REG21_CLK1_DLY_CODE_2RG_src(data)                                  ((0x0000000F&(data))>>0)
#define MIPI_APHY_REG21_get_CLK1_DLY_CODE_2RG(data)                                  ((0x0000000F&(data))>>0)


#define MIPI_APHY_REG22                                                              0x58
#define MIPI_APHY_REG22_reg_addr                                                     "0x98004058"
#define MIPI_APHY_REG22_reg                                                          0x98004058
#define set_MIPI_APHY_REG22_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG22_reg)=data)
#define get_MIPI_APHY_REG22_reg   (*((volatile unsigned int*) MIPI_APHY_REG22_reg))
#define MIPI_APHY_REG22_inst_adr                                                     "0x0016"
#define MIPI_APHY_REG22_inst                                                         0x0016
#define MIPI_APHY_REG22_CLK2_DLY_CODE_2RG_shift                                      (4)
#define MIPI_APHY_REG22_CLK2_DLY_CODE_2RG_mask                                       (0x000000F0)
#define MIPI_APHY_REG22_CLK2_DLY_CODE_2RG(data)                                      (0x000000F0&((data)<<4))
#define MIPI_APHY_REG22_CLK2_DLY_CODE_2RG_src(data)                                  ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG22_get_CLK2_DLY_CODE_2RG(data)                                  ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG22_CLK3_DLY_CODE_2RG_shift                                      (0)
#define MIPI_APHY_REG22_CLK3_DLY_CODE_2RG_mask                                       (0x0000000F)
#define MIPI_APHY_REG22_CLK3_DLY_CODE_2RG(data)                                      (0x0000000F&((data)<<0))
#define MIPI_APHY_REG22_CLK3_DLY_CODE_2RG_src(data)                                  ((0x0000000F&(data))>>0)
#define MIPI_APHY_REG22_get_CLK3_DLY_CODE_2RG(data)                                  ((0x0000000F&(data))>>0)


#define MIPI_APHY_REG23                                                              0x5C
#define MIPI_APHY_REG23_reg_addr                                                     "0x9800405C"
#define MIPI_APHY_REG23_reg                                                          0x9800405C
#define set_MIPI_APHY_REG23_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG23_reg)=data)
#define get_MIPI_APHY_REG23_reg   (*((volatile unsigned int*) MIPI_APHY_REG23_reg))
#define MIPI_APHY_REG23_inst_adr                                                     "0x0017"
#define MIPI_APHY_REG23_inst                                                         0x0017
#define MIPI_APHY_REG23_DATA0_DLY_CODE_2RG_shift                                     (4)
#define MIPI_APHY_REG23_DATA0_DLY_CODE_2RG_mask                                      (0x000000F0)
#define MIPI_APHY_REG23_DATA0_DLY_CODE_2RG(data)                                     (0x000000F0&((data)<<4))
#define MIPI_APHY_REG23_DATA0_DLY_CODE_2RG_src(data)                                 ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG23_get_DATA0_DLY_CODE_2RG(data)                                 ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG23_DATA1_DLY_CODE_2RG_shift                                     (0)
#define MIPI_APHY_REG23_DATA1_DLY_CODE_2RG_mask                                      (0x0000000F)
#define MIPI_APHY_REG23_DATA1_DLY_CODE_2RG(data)                                     (0x0000000F&((data)<<0))
#define MIPI_APHY_REG23_DATA1_DLY_CODE_2RG_src(data)                                 ((0x0000000F&(data))>>0)
#define MIPI_APHY_REG23_get_DATA1_DLY_CODE_2RG(data)                                 ((0x0000000F&(data))>>0)


#define MIPI_APHY_REG24                                                              0x60
#define MIPI_APHY_REG24_reg_addr                                                     "0x98004060"
#define MIPI_APHY_REG24_reg                                                          0x98004060
#define set_MIPI_APHY_REG24_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG24_reg)=data)
#define get_MIPI_APHY_REG24_reg   (*((volatile unsigned int*) MIPI_APHY_REG24_reg))
#define MIPI_APHY_REG24_inst_adr                                                     "0x0018"
#define MIPI_APHY_REG24_inst                                                         0x0018
#define MIPI_APHY_REG24_DATA2_DLY_CODE_2RG_shift                                     (4)
#define MIPI_APHY_REG24_DATA2_DLY_CODE_2RG_mask                                      (0x000000F0)
#define MIPI_APHY_REG24_DATA2_DLY_CODE_2RG(data)                                     (0x000000F0&((data)<<4))
#define MIPI_APHY_REG24_DATA2_DLY_CODE_2RG_src(data)                                 ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG24_get_DATA2_DLY_CODE_2RG(data)                                 ((0x000000F0&(data))>>4)
#define MIPI_APHY_REG24_DATA3_DLY_CODE_2RG_shift                                     (0)
#define MIPI_APHY_REG24_DATA3_DLY_CODE_2RG_mask                                      (0x0000000F)
#define MIPI_APHY_REG24_DATA3_DLY_CODE_2RG(data)                                     (0x0000000F&((data)<<0))
#define MIPI_APHY_REG24_DATA3_DLY_CODE_2RG_src(data)                                 ((0x0000000F&(data))>>0)
#define MIPI_APHY_REG24_get_DATA3_DLY_CODE_2RG(data)                                 ((0x0000000F&(data))>>0)


#define MIPI_APHY_REG25                                                              0x64
#define MIPI_APHY_REG25_reg_addr                                                     "0x98004064"
#define MIPI_APHY_REG25_reg                                                          0x98004064
#define set_MIPI_APHY_REG25_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG25_reg)=data)
#define get_MIPI_APHY_REG25_reg   (*((volatile unsigned int*) MIPI_APHY_REG25_reg))
#define MIPI_APHY_REG25_inst_adr                                                     "0x0019"
#define MIPI_APHY_REG25_inst                                                         0x0019
#define MIPI_APHY_REG25_R50_CAL_OK_2RG_shift                                         (7)
#define MIPI_APHY_REG25_R50_CAL_OK_2RG_mask                                          (0x00000080)
#define MIPI_APHY_REG25_R50_CAL_OK_2RG(data)                                         (0x00000080&((data)<<7))
#define MIPI_APHY_REG25_R50_CAL_OK_2RG_src(data)                                     ((0x00000080&(data))>>7)
#define MIPI_APHY_REG25_get_R50_CAL_OK_2RG(data)                                     ((0x00000080&(data))>>7)
#define MIPI_APHY_REG25_R50_CAL_2RG_shift                                            (0)
#define MIPI_APHY_REG25_R50_CAL_2RG_mask                                             (0x0000003F)
#define MIPI_APHY_REG25_R50_CAL_2RG(data)                                            (0x0000003F&((data)<<0))
#define MIPI_APHY_REG25_R50_CAL_2RG_src(data)                                        ((0x0000003F&(data))>>0)
#define MIPI_APHY_REG25_get_R50_CAL_2RG(data)                                        ((0x0000003F&(data))>>0)


#define MIPI_APHY_REG26                                                              0x68
#define MIPI_APHY_REG26_reg_addr                                                     "0x98004068"
#define MIPI_APHY_REG26_reg                                                          0x98004068
#define set_MIPI_APHY_REG26_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG26_reg)=data)
#define get_MIPI_APHY_REG26_reg   (*((volatile unsigned int*) MIPI_APHY_REG26_reg))
#define MIPI_APHY_REG26_inst_adr                                                     "0x001A"
#define MIPI_APHY_REG26_inst                                                         0x001A
#define MIPI_APHY_REG26_LANE_OK_shift                                                (0)
#define MIPI_APHY_REG26_LANE_OK_mask                                                 (0x0000000F)
#define MIPI_APHY_REG26_LANE_OK(data)                                                (0x0000000F&((data)<<0))
#define MIPI_APHY_REG26_LANE_OK_src(data)                                            ((0x0000000F&(data))>>0)
#define MIPI_APHY_REG26_get_LANE_OK(data)                                            ((0x0000000F&(data))>>0)


#define MIPI_APHY_REG27                                                              0x84
#define MIPI_APHY_REG27_reg_addr                                                     "0x98004084"
#define MIPI_APHY_REG27_reg                                                          0x98004084
#define set_MIPI_APHY_REG27_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG27_reg)=data)
#define get_MIPI_APHY_REG27_reg   (*((volatile unsigned int*) MIPI_APHY_REG27_reg))
#define MIPI_APHY_REG27_inst_adr                                                     "0x0021"
#define MIPI_APHY_REG27_inst                                                         0x0021
#define MIPI_APHY_REG27_HSPAMP2_RL_RG_shift                                          (0)
#define MIPI_APHY_REG27_HSPAMP2_RL_RG_mask                                           (0x0000003F)
#define MIPI_APHY_REG27_HSPAMP2_RL_RG(data)                                          (0x0000003F&((data)<<0))
#define MIPI_APHY_REG27_HSPAMP2_RL_RG_src(data)                                      ((0x0000003F&(data))>>0)
#define MIPI_APHY_REG27_get_HSPAMP2_RL_RG(data)                                      ((0x0000003F&(data))>>0)


#define MIPI_APHY_REG28                                                              0x88
#define MIPI_APHY_REG28_reg_addr                                                     "0x98004088"
#define MIPI_APHY_REG28_reg                                                          0x98004088
#define set_MIPI_APHY_REG28_reg(data)   (*((volatile unsigned int*) MIPI_APHY_REG28_reg)=data)
#define get_MIPI_APHY_REG28_reg   (*((volatile unsigned int*) MIPI_APHY_REG28_reg))
#define MIPI_APHY_REG28_inst_adr                                                     "0x0022"
#define MIPI_APHY_REG28_inst                                                         0x0022
#define MIPI_APHY_REG28_HSPAMP3_RL_RG_shift                                          (0)
#define MIPI_APHY_REG28_HSPAMP3_RL_RG_mask                                           (0x0000003F)
#define MIPI_APHY_REG28_HSPAMP3_RL_RG(data)                                          (0x0000003F&((data)<<0))
#define MIPI_APHY_REG28_HSPAMP3_RL_RG_src(data)                                      ((0x0000003F&(data))>>0)
#define MIPI_APHY_REG28_get_HSPAMP3_RL_RG(data)                                      ((0x0000003F&(data))>>0)


#endif
