/*
 *  dptx_reg.h - RTK display port driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _DPTX_REG_H_INCLUDED_
#define _DPTX_REG_H_INCLUDED_

#define _BIT0		0x00000001
#define _BIT1		0x00000002
#define _BIT2		0x00000004
#define _BIT3		0x00000008
#define _BIT4		0x00000010
#define _BIT5		0x00000020
#define _BIT6		0x00000040
#define _BIT7		0x00000080
#define _BIT8		0x00000100
#define _BIT9		0x00000200
#define _BIT10		0x00000400
#define _BIT11		0x00000800
#define _BIT12		0x00001000
#define _BIT13		0x00002000
#define _BIT14		0x00004000
#define _BIT15		0x00008000
#define _BIT16		0x00010000
#define _BIT17		0x00020000
#define _BIT18		0x00040000
#define _BIT19		0x00080000
#define _BIT20		0x00100000
#define _BIT21		0x00200000
#define _BIT22		0x00400000
#define _BIT23		0x00800000
#define _BIT24		0x01000000
#define _BIT25		0x02000000
#define _BIT26		0x04000000
#define _BIT27		0x08000000
#define _BIT28		0x10000000
#define _BIT29		0x20000000
#define _BIT30		0x40000000
#define _BIT31		0x80000000

//--------------------------------------
//        DPTX Digital PHY CTRL
//--------------------------------------

#define PBB_00_DP_PHY_CTRL                                          0x000
#define PBB_01_DPTX_ML_PAT_SEL                                      0x004
#define PBB_02_CUSTOM_PATTERN_0                                     0x008
#define PBB_03_CUSTOM_PATTERN_1                                     0x00C
#define PBB_04_CUSTOM_PATTERN_2                                     0x010
#define PBB_05_CUSTOM_PATTERN_3                                     0x014
#define PBB_06_CUSTOM_PATTERN_4                                     0x018
#define PBB_07_CUSTOM_PATTERN_5                                     0x01C
#define PBB_08_CUSTOM_PATTERN_6                                     0x020
#define PBB_09_CUSTOM_PATTERN_7                                     0x024
#define PBB_0A_CUSTOM_PATTERN_8                                     0x028
#define PBB_0B_CUSTOM_PATTERN_9                                     0x02C
#define PBB_0C_COMPLIANCE_EYE_PATTERN                               0x030
#define PBB_0D_DPTX_PHY_CTRL                                        0x034
#define PBB_0E_DPTX_LANE_SWAP                                       0x038
#define PBB_0F_DPTX_8B10B_TST                                       0x03C
#define PBB_10_DPTX_PHY_DUMMY                                       0x040
#define PBB_11_RIV0                                                 0x044
#define PBB_12_RIV1                                                 0x048
#define PBB_13_RIV2                                                 0x04C
#define PBB_14_RIV3                                                 0x050
#define PBB_15_RIV4                                                 0x054
#define PBB_16_RIV5                                                 0x058
#define PBB_17_RIV6                                                 0x05C
#define PBB_18_RIV7                                                 0x060
#define PBB_30_DPTX_HDCP_CTRL1                                      0x0C0
#define PBB_31_DPTX_HDCP_CTRL2                                      0x0C4
#define PBB_32_DP_HDCP_KEY_DL_PORT                                  0x0C8
#define PBB_33_DP_HDCP_KEY_OUTPUT                                   0x0CC
#define PBB_34_AN_BYTE_7                                            0x0D0
#define PBB_35_AN_BYTE_6                                            0x0D4
#define PBB_36_AN_BYTE_5                                            0x0D8
#define PBB_37_AN_BYTE_4                                            0x0DC
#define PBB_38_AN_BYTE_3                                            0x0E0
#define PBB_39_AN_BYTE_2                                            0x0E4
#define PBB_3A_AN_BYTE_1                                            0x0E8
#define PBB_3B_AN_BYTE_0                                            0x0EC
#define PBB_3C_M0_BYTE_7                                            0x0F0
#define PBB_3D_M0_BYTE_6                                            0x0F4
#define PBB_3E_M0_BYTE_5                                            0x0F8
#define PBB_3F_M0_BYTE_4                                            0x0FC
#define PBB_40_M0_BYTE_3                                            0x100
#define PBB_41_M0_BYTE_2                                            0x104
#define PBB_42_M0_BYTE_1                                            0x108
#define PBB_43_M0_BYTE_0                                            0x10C
#define PBB_44_KM_BYTE_6                                            0x110
#define PBB_45_KM_BYTE_5                                            0x114
#define PBB_46_KM_BYTE_4                                            0x118
#define PBB_47_KM_BYTE_3                                            0x11C
#define PBB_48_KM_BYTE_2                                            0x120
#define PBB_49_KM_BYTE_1                                            0x124
#define PBB_4A_KM_BYTE_0                                            0x128
#define PBB_4B_R0_BYTE_MSB                                          0x12C
#define PBB_4C_R0_BYTE_LSB                                          0x130
#define PBB_4D_RI_BYTE_MSB                                          0x134
#define PBB_4E_RI_BYTE_LSB                                          0x138
#define PBB_4F_BKSV_0                                               0x13C
#define PBB_50_BKSV_1                                               0x140
#define PBB_51_BKSV_2                                               0x144
#define PBB_52_BKSV_3                                               0x148
#define PBB_53_BKSV_4                                               0x14C
#define PBB_54_HDCP_TX_LIP_H                                        0x150
#define PBB_55_HDCP_TX_LIP_L                                        0x154
#define PBB_56_DP_HDCP_TX                                           0x158
#define PBB_57_DP_HDCP_BIST                                         0x15C
#define PBB_58_DP_HDCP_AN_SEED                                      0x160
#define PBB_59_HDCP_IRQ_EVENT                                       0x164
#define PBB_5A_DPTX_HDCP_TST                                        0x168
#define PBB_5B_DP_HDCP_TX_SHA_CTRL                                  0x16C
#define PBB_5C_DP_HDCP_TX_SHA_DATA_3                                0x170
#define PBB_5D_DP_HDCP_TX_SHA_DATA_2                                0x174
#define PBB_5E_DP_HDCP_TX_SHA_DATA_1                                0x178
#define PBB_5F_DP_HDCP_TX_SHA_DATA_0                                0x17C
#define PBB_60_DP_HDCP_TX_SHA_OUT_3                                 0x180
#define PBB_61_DP_HDCP_TX_SHA_OUT_2                                 0x184
#define PBB_62_DP_HDCP_TX_SHA_OUT_1                                 0x188
#define PBB_63_DP_HDCP_TX_SHA_OUT_0                                 0x18C
#define PBB_64_HDCP_ECF_BYTE0                                       0x190
#define PBB_65_HDCP_ECF_BYTE1                                       0x194
#define PBB_66_HDCP_ECF_BYTE2                                       0x198
#define PBB_67_HDCP_ECF_BYTE3                                       0x19C
#define PBB_68_HDCP_ECF_BYTE4                                       0x1A0
#define PBB_69_HDCP_ECF_BYTE5                                       0x1A4
#define PBB_6A_HDCP_ECF_BYTE6                                       0x1A8
#define PBB_6B_HDCP_ECF_BYTE7                                       0x1AC
#define PBB_6C_DP_STREAM_1_PBN                                      0x1B0
#define PBB_6D_DP_STREAM_2_PBN                                      0x1B4
#define PBB_6E_DP_STREAM_3_PBN                                      0x1B8
#define PBB_6F_DP_STREAM_4_PBN                                      0x1BC
#define PBB_80_HDCP_AES_CIPHER_KEY_15                               0x200
#define PBB_81_HDCP_AES_CIPHER_KEY_14                               0x204
#define PBB_82_HDCP_AES_CIPHER_KEY_13                               0x208
#define PBB_83_HDCP_AES_CIPHER_KEY_12                               0x20C
#define PBB_84_HDCP_AES_CIPHER_KEY_11                               0x210
#define PBB_85_HDCP_AES_CIPHER_KEY_10                               0x214
#define PBB_86_HDCP_AES_CIPHER_KEY_9                                0x218
#define PBB_87_HDCP_AES_CIPHER_KEY_8                                0x21C
#define PBB_88_HDCP_AES_CIPHER_KEY_7                                0x220
#define PBB_89_HDCP_AES_CIPHER_KEY_6                                0x224
#define PBB_8A_HDCP_AES_CIPHER_KEY_5                                0x228
#define PBB_8B_HDCP_AES_CIPHER_KEY_4                                0x22C
#define PBB_8C_HDCP_AES_CIPHER_KEY_3                                0x230
#define PBB_8D_HDCP_AES_CIPHER_KEY_2                                0x234
#define PBB_8E_HDCP_AES_CIPHER_KEY_1                                0x238
#define PBB_8F_HDCP_AES_CIPHER_KEY_0                                0x23C
#define PBB_90_HDCP22_CTRL                                          0x240
#define PBB_91_HDCP22_TYPE_AES_0                                    0x244
#define PBB_92_HDCP22_TYPE_AES_1                                    0x248
#define PBB_9A_DUMMY_1                                              0x268
#define PBB_9B_DUMMY_2                                              0x26C
#define PBB_9C_DUMMY_3                                              0x270



//--------------------------------------
//        DPTX HPD Detection
//--------------------------------------

#define PBB_70_HPD_CTRL                                             0x1C0
#define PBB_71_HPD_IRQ                                              0x1C4
#define PBB_72_HPD_IRQ_EN                                           0x1C8
#define PBB_73_HPD_TIMER1                                           0x1CC
#define PBB_74_HPD_TIMER2                                           0x1D0
#define PBB_75_HPD_TIMER3                                           0x1D4
#define PBB_76_HPD_TIMER4                                           0x1D8
#define PBB_77_HPD_TIMER5                                           0x1DC
#define PBB_78_HPD_TIMER6                                           0x1E0
#define PBB_79_HPD_TIMER7                                           0x1E4
#define PBB_7A_HPD_LONG0                                            0x1E8
#define PBB_7B_HPD_LONG1                                            0x1EC
#define PBB_7C_HPD_STATE                                            0x1F0
#define PBB_7D_RESERVED_0                                           0x1F4
#define PBB_7E_RESERVED_1                                           0x1F8



//--------------------------------------
//        DPTX link MAC
//--------------------------------------

#define PBB_A0_DP_MAC_CTRL                                          0x280
#define PBB_A1_DP_RESET_CTRL                                        0x284
#define PBB_A2_DP_DEBUG_CTRL                                        0x288
#define PBB_A3_DPTX_IRQ_CTRL                                        0x28C
#define PBB_A4_PG_FIFO_CTRL                                         0x290
#define PBB_A5_MAX_WL                                               0x294
#define PBB_A6_LFIFO_WL                                             0x298
#define PBB_A7_PG_INTERRUPT_CTRL                                    0x29C
#define PBB_A8_MN_VID_AUTO_EN_1                                     0x2A0
#define PBB_A9_MN_M_VID_H                                           0x2A4
#define PBB_AA_MN_M_VID_M                                           0x2A8
#define PBB_AB_MN_M_VID_L                                           0x2AC
#define PBB_AC_MN_N_VID_H                                           0x2B0
#define PBB_AD_MN_N_VID_M                                           0x2B4
#define PBB_AE_MN_N_VID_L                                           0x2B8
#define PBB_AF_MVID_AUTO_H                                          0x2BC
#define PBB_B0_MVID_AUTO_M                                          0x2C0
#define PBB_B1_MVID_AUTO_L                                          0x2C4
#define PBB_B2_NVID_ASYNC_M                                         0x2C8
#define PBB_B3_NVID_ASYNC_L                                         0x2CC
#define PBB_B4_MSA_CTRL                                             0x2D0
#define PBB_B5_MSA_MISC0                                            0x2D4
#define PBB_B6_MN_STRM_ATTR_MISC1                                   0x2D8
#define PBB_B7_MN_STRM_ATTR_HTT_M                                   0x2DC
#define PBB_B8_MN_STRM_ATTR_HTT_L                                   0x2E0
#define PBB_B9_MN_STRM_ATTR_HST_M                                   0x2E4
#define PBB_BA_MN_STRM_ATTR_HST_L                                   0x2E8
#define PBB_BB_MN_STRM_ATTR_HWD_M                                   0x2EC
#define PBB_BC_MN_STRM_ATTR_HWD_L                                   0x2F0
#define PBB_BD_MN_STRM_ATTR_HSW_M                                   0x2F4
#define PBB_BE_MN_STRM_ATTR_HSW_L                                   0x2F8
#define PBB_BF_MN_STRM_ATTR_VTTE_M                                  0x2FC
#define PBB_C0_MN_STRM_ATTR_VTTE_L                                  0x300
#define PBB_C1_MN_STRM_ATTR_VST_M                                   0x304
#define PBB_C2_MN_STRM_ATTR_VST_L                                   0x308
#define PBB_C3_MN_STRM_ATTR_VHT_M                                   0x30C
#define PBB_C4_MN_STRM_ATTR_VHT_L                                   0x310
#define PBB_C5_MN_STRM_ATTR_VSW_M                                   0x314
#define PBB_C6_MN_STRM_ATTR_VSW_L                                   0x318
#define PBB_C7_VBID                                                 0x31C
#define PBB_C8_VBID_FW_CTL                                          0x320
#define PBB_C9_ARBITER_CTRL                                         0x324
#define PBB_CA_V_DATA_PER_LINE0                                     0x328
#define PBB_CB_V_DATA_PER_LINE1                                     0x32C
#define PBB_CC_TU_SIZE                                              0x330
#define PBB_CD_TU_DATA_SIZE0                                        0x334
#define PBB_CE_TU_DATA_SIZE1                                        0x338
#define PBB_CF_HDEALY0                                              0x33C
#define PBB_D0_HDEALY1                                              0x340
#define PBB_D1_AUTO_HDEALY0                                         0x344
#define PBB_D2_AUTO_HDEALY1                                         0x348
#define PBB_D3_LFIFO_WL_SET                                         0x34C
#define PBB_D4_ARBITER_SEC_END_CNT_HB                               0x350
#define PBB_D5_ARBITER_SEC_END_CNT_LB                               0x354
#define PBB_D6_ARBITER_DEBUG                                        0x358
#define PBB_D7_DPTX_CTSFIFO_CTRL                                    0x35C
#define PBB_D8_DPTX_CTSFIFO_RSV1                                    0x360
#define PBB_D9_DPTX_TOP_CTL                                         0x364
#define PBB_DA_DPTX_TOP_RSV1                                        0x368
#define PBB_DB_DPTX_TOP_RSV2                                        0x36C
#define PBB_DC_ARBITER_MIN_H_BLANK_WIDTH_HB                         0x370
#define PBB_DD_ARBITER_MIN_H_BLANK_WIDTH_LB                         0x374
#define PBB_DE_ARBITER_INTERRUPT_CTRL                               0x378
#define PBB_DF_VESA_FMT_REGEN                                       0x37C
#define PBB_E0_DPTX_CLK_GEN                                         0x380
#define PBB_E1_PG_MBIST_CTRL                                        0x384
#define PBB_E2_PG_DRF_MBIST_CTRL                                    0x388
#define PBB_F0_ARBITER_SEC_IDLE_END_CNT                             0x3C0
#define PBB_F8_DPTX_TOP_RSV3                                        0x3E0
#define PBB_F9_DPTX_TOP_RSV4                                        0x3E4
#define PBB_FA_DPTX_TOP_RSV5                                        0x3E8
#define PBB_FB_DPTX_TOP_RSV6                                        0x3EC
#define PBB_FC_DPTX_TOP_RSV7                                        0x3F0
#define PBB_FD_DPTX_TOP_RSV8                                        0x3F4
#define PBB_FE_DPTX_TOP_RSV9                                        0x3F8
#define PBB_FF_DPTX_TOP_RSV10                                       0x3FC



//--------------------------------------
//        DPTX MAC CTRL1
//--------------------------------------

#define PBC_00_SEC_FUNCTION_CTRL                                    0x400
#define PBC_01_SEC_RESERVED_0                                       0x404
#define PBC_02_SEC_DBUF_CTRL                                        0x408
#define PBC_03_SEC_DEBUG                                            0x40C
#define PBC_04_SEC_PSR_DB0                                          0x410
#define PBC_05_SEC_PSR_DB1                                          0x414
#define PBC_06_SEC_PSR_DB2                                          0x418
#define PBC_07_SEC_PSR_DB3                                          0x41C
#define PBC_08_SEC_PSR_DB4                                          0x420
#define PBC_09_SEC_PSR_DB5                                          0x424
#define PBC_0A_SEC_PSR_DB6                                          0x428
#define PBC_0B_SEC_PSR_DB7                                          0x42C
#define PBC_0C_SEC_PSR_DB8                                          0x430
#define PBC_0D_SEC_PSR_DB9                                          0x434
#define PBC_0E_SEC_PSR_DB10                                         0x438
#define PBC_0F_SEC_PSR_DB11                                         0x43C
#define PBC_10_SEC_PSR_DB12                                         0x440
#define PBC_11_SEC_PSR_DB13                                         0x444
#define PBC_12_SEC_PSR_DB14                                         0x448
#define PBC_13_SEC_PSR_DB15                                         0x44C
#define PBC_14_SEC_RESERVED_1                                       0x450
#define PBC_15_SEC_RESERVED_2                                       0x454
#define PBC_16_SEC_RESERVED_3                                       0x458
#define PBC_17_SEC_RESERVED_4                                       0x45C
#define PBC_18_AUD_FUNCTION_CTRL1                                   0x460
#define PBC_19_AUD_PAYLOAD_B3                                       0x464
#define PBC_1A_DP_AUD_ID                                            0x468
#define PBC_1B_SEC_RESERVED_6                                       0x46C
#define PBC_1C_AUD_FIFO_CTRL                                        0x470
#define PBC_1D_AUD_LFIFO_MAX_WL                                     0x474
#define PBC_1E_AUD_LFIFO_WL                                         0x478
#define PBC_1F_AUD_INTERRUPT_CTRL                                   0x47C
#define PBC_20_AUD_TS_MAUD_H                                        0x480
#define PBC_21_AUD_TS_MAUD_M                                        0x484
#define PBC_22_AUD_TS_MAUD_L                                        0x488
#define PBC_23_AUD_TS_NAUD_H                                        0x48C
#define PBC_24_AUD_TS_NAUD_M                                        0x490
#define PBC_25_AUD_TS_NAUD_L                                        0x494
#define PBC_26_SEC_INFO_AUD_DB0                                     0x498
#define PBC_27_SEC_INFO_AUD_DB1                                     0x49C
#define PBC_28_SEC_INFO_AUD_DB2                                     0x4A0
#define PBC_29_SEC_INFO_AUD_DB3                                     0x4A4
#define PBC_2A_SEC_INFO_AUD_DB4                                     0x4A8
#define PBC_2B_SEC_INFO_AUD_DB5                                     0x4AC
#define PBC_2C_SEC_INFO_AUD_DB6                                     0x4B0
#define PBC_2D_SEC_INFO_AUD_DB7                                     0x4B4
#define PBC_2E_SEC_INFO_AUD_DB8                                     0x4B8
#define PBC_2F_SEC_INFO_AUD_DB9                                     0x4BC
#define PBC_30_SEC_INFO_AVI_DB0                                     0x4C0
#define PBC_31_SEC_INFO_AVI_DB1                                     0x4C4
#define PBC_32_SEC_INFO_AVI_DB2                                     0x4C8
#define PBC_33_SEC_INFO_AVI_DB3                                     0x4CC
#define PBC_34_SEC_INFO_AVI_DB4                                     0x4D0
#define PBC_35_SEC_INFO_AVI_DB5                                     0x4D4
#define PBC_36_SEC_INFO_AVI_DB6                                     0x4D8
#define PBC_37_SEC_INFO_AVI_DB7                                     0x4DC
#define PBC_38_SEC_INFO_AVI_DB8                                     0x4E0
#define PBC_39_SEC_INFO_AVI_DB9                                     0x4E4
#define PBC_3A_SEC_INFO_AVI_DB10                                    0x4E8
#define PBC_3B_SEC_INFO_AVI_DB11                                    0x4EC
#define PBC_3C_SEC_INFO_AVI_DB12                                    0x4F0
#define PBC_3D_SEC_INFO_MPEG_DB0                                    0x4F4
#define PBC_3E_SEC_INFO_MPEG_DB1                                    0x4F8
#define PBC_3F_SEC_INFO_MPEG_DB2                                    0x4FC
#define PBC_40_SEC_INFO_MPEG_DB3                                    0x500
#define PBC_41_SEC_INFO_MPEG_DB4                                    0x504
#define PBC_42_SEC_INFO_MPEG_DB5                                    0x508
#define PBC_43_SEC_INFO_MPEG_DB6                                    0x50C
#define PBC_44_SEC_INFO_MPEG_DB7                                    0x510
#define PBC_45_SEC_INFO_MPEG_DB8                                    0x514
#define PBC_46_SEC_INFO_MPEG_DB9                                    0x518
#define PBC_47_AUD_FUNCTION_CTRL2                                   0x51C
#define PBC_48_AUD_FUNCTION_CTRL3                                   0x520
#define PBC_49_MST_SEC_PKT_ID                                       0x524
#define PBC_4A_MST_SEC_PKT_HB3                                      0x528
#define PBC_4B_SEC_RS_DECODE_CTRL                                   0x52C
#define PBC_4C_SEC_AUD_FREQDET_CTRL                                 0x530
#define PBC_4D_SEC_AUD_XCLK_DIV                                     0x534
#define PBC_4E_SEC_AUD_FREQ_TIME                                    0x538
#define PBC_4F_SEC_AUD_SAMPLE_CNT_HB                                0x53C
#define PBC_50_SEC_AUD_SAMPLE_CNT_LB                                0x540
#define PBC_51_AUD_MBIST_CTRL                                       0x544
#define PBC_52_AUD_DRF_MBIST_CTRL                                   0x548
#define PBC_53_DP_INFO_FM_RSV0                                      0x54C
#define PBC_54_DP_INFO_FM_RSV1                                      0x550
#define PBC_55_DP_INFO_FM_ADR                                       0x554
#define PBC_56_DP_INFO_FM_DAT                                       0x558
#define PBC_57_RESERVED_57                                          0x55C
#define PBC_58_VSC_RX_DB0                                           0x560
#define PBC_59_VSC_RX_DB1                                           0x564
#define PBC_5A_VSC_RX_DB2                                           0x568
#define PBC_5B_VSC_RX_DB3                                           0x56C
#define PBC_5C_VSC_RX_DB4                                           0x570
#define PBC_5D_VSC_RX_DB5                                           0x574
#define PBC_5E_VSC_RX_DB6                                           0x578
#define PBC_5F_VSC_RX_DB7                                           0x57C
#define PBC_60_AUD_FREQ_TH_0                                        0x580
#define PBC_61_AUD_FREQ_TH_1                                        0x584
#define PBC_62_AUD_FREQ_TH_2                                        0x588
#define PBC_63_AUD_FREQ_TH_3                                        0x58C
#define PBC_64_AUD_FREQ_TH_4                                        0x590
#define PBC_65_AUD_FREQ_TH_5                                        0x594
#define PBC_66_AUD_FREQ_TH_6                                        0x598
#define PBC_67_RESERVED_67                                          0x59C
#define PBC_68_RESERVED_68                                          0x5A0
#define PBC_69_RESERVED_69                                          0x5A4
#define PBC_6A_VSC_CTRL_0                                           0x5A8
#define PBC_6B_VSC_RX_HB0                                           0x5AC
#define PBC_6C_VSC_RX_HB1                                           0x5B0
#define PBC_6D_VSC_RX_HB2                                           0x5B4
#define PBC_6E_VSC_RX_HB3                                           0x5B8
#define PBC_70_SEC_AWD_CTRL                                         0x5C0
#define PBC_71_SEC_AWD_STATUS_0                                     0x5C4
#define PBC_72_SEC_IRQ_CTRL0                                        0x5C8
#define PBC_73_SEC_PH_HB0                                           0x5CC
#define PBC_74_SEC_PH_HB1                                           0x5D0
#define PBC_75_SEC_PH_HB2                                           0x5D4
#define PBC_76_SEC_PH_HB3                                           0x5D8
#define PBC_77_SEC_PH_PB0                                           0x5DC
#define PBC_78_SEC_PH_PB1                                           0x5E0
#define PBC_79_SEC_PH_PB2                                           0x5E4
#define PBC_7A_SEC_PH_PB3                                           0x5E8
#define PBC_7B_SEC_PH_PACKET_TYPE                                   0x5EC
#define PBC_80_SEC_AWD_STATUS_1                                     0x600
#define PBC_81_DP_INFO_VAR_EN_M                                     0x604
#define PBC_82_DP_INFO_VAR_EN_L                                     0x608
#define PBC_83_DP_INFO_VAR_ST_M                                     0x60C
#define PBC_84_DP_INFO_VAR_ST_L                                     0x610
#define PBC_85_CH_STATUS_0                                          0x614
#define PBC_86_CH_STATUS_1                                          0x618
#define PBC_87_CH_STATUS_2                                          0x61C
#define PBC_88_CH_STATUS_3                                          0x620
#define PBC_89_CH_STATUS_4                                          0x624
#define PBC_8A_DP_AVWD_CTRL0                                        0x628
#define PBC_8B_RESERVED_8B                                          0x62C
#define PBC_8C_RESERVED_8C                                          0x630
#define PBC_8D_RESERVED_8D                                          0x634
#define PBC_8E_RESERVED_8E                                          0x638
#define PBC_8F_DPTX_I2S_CTRL                                        0x63C
#define PBC_90_SEC_IRQ_CTRL1                                        0x640
#define PBC_95_DUMMY_95                                             0x654
#define PBC_96_DUMMY_96                                             0x658
#define PBC_97_DUMMY_97                                             0x65C
#define PBC_98_DUMMY_98                                             0x660
#define PBC_99_DUMMY_99                                             0x664
#define PBC_9A_DUMMY_9A                                             0x668
#define PBC_9B_DUMMY_9B                                             0x66C
#define PBC_9C_DUMMY_9C                                             0x670



//--------------------------------------
//        DPTX link MAC
//--------------------------------------

#define PBC_A0_DPTX_PHY_CTRL0                                       0x680
#define PBC_A1_DPTX_PHY_CTRL1                                       0x684
#define PBC_A2_DPTX_RCV_DET0                                        0x688
#define PBC_A3_DPTX_RCV_DET1                                        0x68C
#define PBC_A4_DPTX_PN_SWAP                                         0x690
#define PBC_A7_DPTX_SFIFO_CTRL0                                     0x69C
#define PBC_A8_DPTX_SFIFO_CTRL1                                     0x6A0
#define PBC_A9_DPTX_SFIFO_LANE_SWAP0                                0x6A4
#define PBC_AA_DPTX_SFIFO_LANE_SWAP1                                0x6A8
#define PBC_AB_DPTX_SFIFO_INT_EN                                    0x6AC



//--------------------------------------
//        DPTX AUX Analog PHY CTRL
//--------------------------------------

#define PBD_60_DIG_TX_04                                            0x980
#define PBD_61_AUX_1                                                0x984
#define PBD_62_AUX_2                                                0x988
#define PBD_63_AUX_3                                                0x98C
#define PBD_64_AUX_4                                                0x990
#define PBD_65_AUX_5                                                0x994
#define PBD_66_AUX_6                                                0x998
#define PBD_67_DIG_TX_03                                            0x99C



//--------------------------------------
//        DPTX AUX MAC CTRL
//--------------------------------------

#define PBD_A0_AUX_TX_CTRL                                          0xA80
#define PBD_A1_AUX_TIMEOUT                                          0xA84
#define PBD_A2_AUX_FSM_STATUS                                       0xA88
#define PBD_A3_AUXTX_TRAN_CTRL                                      0xA8C
#define PBD_A4_AUXTX_REQ_CMD                                        0xA90
#define PBD_A5_AUXTX_REQ_ADDR_M                                     0xA94
#define PBD_A6_AUXTX_REQ_ADDR_L                                     0xA98
#define PBD_A7_AUXTX_REQ_LEN                                        0xA9C
#define PBD_A8_AUXTX_REQ_DATA                                       0xAA0
#define PBD_A9_AUX_REPLY_CMD                                        0xAA4
#define PBD_AA_AUX_REPLY_DATA                                       0xAA8
#define PBD_AB_AUX_FIFO_CTRL                                        0xAAC
#define PBD_AC_AUX_TX_FIFO_STATUS                                   0xAB0
#define PBD_AD_AUX_FIFO_RD_PTR                                      0xAB4
#define PBD_AE_AUX_FIFO_WR_PTR                                      0xAB8
#define PBD_AF_AUX_RETRY_1                                          0xABC
#define PBD_B0_AUX_RETRY_2                                          0xAC0
#define PBD_B1_AUX_IRQ_EVENT                                        0xAC4
#define PBD_B2_AUX_IRQ_EN                                           0xAC8
#define PBD_F0_AUX_DIG_PHY2                                         0xBC0
#define PBD_F1_AUX_DIG_PHY3                                         0xBC4
#define PBD_F2_AUX_DIG_PHY4                                         0xBC8
#define PBD_F3_AUX_DIG_PHY5                                         0xBCC
#define PBD_F4_AUX_DIG_PHY6                                         0xBD0
#define PBD_F5_AUX_DIG_PHY7                                         0xBD4
#define PBD_F6_AUX_DIG_PHY8                                         0xBD8
#define PBD_F7_AUX_DIG_PHY9                                         0xBDC
#define PBD_F8_AUX_DEBUG                                            0xBE0


//--------------------------------------
//        LVDS Combo AIF
//--------------------------------------
#define AIF_MISC		0x0
#define AIF_EDP1		0x40
#define AIF_EDP2		0x44
#define CT_CTRL			0x100
#define DH_WIDTH		0x404
#define DH_TOTAL		0x408
#define DH_DEN_START_END	0x40c
#define DV_DEN_START_END_F1	0x410
#define DV_TOTAL		0x418
#define DV_VS_START_END_F1	0x41c
#define DV_SYNC_INT		0x42c


//--------------------------------------
//       LVDS and EDP PLL Control Register
//--------------------------------------
#define DISP_PLL_DIV2	0x24
#define PLL_HDMI	0x190
#define PLL_HDMI_LDO1	0x230
#define PLL_EDP1	0x248
#define PLL_EDP2	0x24c
#define PLL_PIXEL1	0x250
#define PLL_PIXEL2	0x254

//--------------------------------------
//       EDP PLL_SSC_DIG Control Register
//--------------------------------------
#define PLL_SSC_DIG_EDP0	0x5e0
#define PLL_SSC_DIG_EDP1	0x5e4
#define PLL_SSC_DIG_EDP2	0x5e8
#define PLL_SSC_DIG_EDP3	0x5ec
#define PLL_SSC_DIG_EDP4	0x5f0
#define PLL_SSC_DIG_EDP5	0x5f4
#define PLL_SSC_DIG_EDP_DBG1	0x5f8
#define PLL_SSC_DIG_EDP_DBG2	0x5fc

//--------------------------------------
//       PIXEL PLL_SSC_DIG Control Register
//--------------------------------------
#define PLL_SSC_DIG_PIXEL0	0x600
#define PLL_SSC_DIG_PIXEL1	0x604
#define PLL_SSC_DIG_PIXEL2	0x608

#endif
