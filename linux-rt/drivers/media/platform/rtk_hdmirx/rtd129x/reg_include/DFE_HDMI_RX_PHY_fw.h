/*===========*@date:2015/3/6===========*/

#ifndef _DFE_HDMI_RX_PHY_REG_H_INCLUDED_
#define _DFE_HDMI_RX_PHY_REG_H_INCLUDED_

#define BG                                                            0xa00
#define BG_reg_addr                                                   "0x98034a00"
#define BG_reg                                                        0x98034a00
#define BG_inst_addr                                                  "0x0280"
#define BG_inst                                                       0x0280
#define set_BG_reg(data)                                              (*((volatile unsigned int*)BG_reg)=data)
#define get_BG_reg                                                    (*((volatile unsigned int*)BG_reg))
#define BG_reg_bg_rbgloop2_shift                                      (7)
#define BG_reg_bg_rbg_shift                                           (4)
#define BG_reg_bg_rbg2_shift                                          (2)
#define BG_reg_bg_pow_shift                                           (1)
#define BG_reg_bg_envbgup_shift                                       (0)
#define BG_reg_bg_rbgloop2_mask                                       (0x00000380)
#define BG_reg_bg_rbg_mask                                            (0x00000070)
#define BG_reg_bg_rbg2_mask                                           (0x0000000C)
#define BG_reg_bg_pow_mask                                            (0x00000002)
#define BG_reg_bg_envbgup_mask                                        (0x00000001)
#define BG_reg_bg_rbgloop2(data)                                      (0x00000380&((data)<<7))
#define BG_reg_bg_rbg(data)                                           (0x00000070&((data)<<4))
#define BG_reg_bg_rbg2(data)                                          (0x0000000C&((data)<<2))
#define BG_reg_bg_pow(data)                                           (0x00000002&((data)<<1))
#define BG_reg_bg_envbgup(data)                                       (0x00000001&(data))
#define BG_get_reg_bg_rbgloop2(data)                                  ((0x00000380&(data))>>7)
#define BG_get_reg_bg_rbg(data)                                       ((0x00000070&(data))>>4)
#define BG_get_reg_bg_rbg2(data)                                      ((0x0000000C&(data))>>2)
#define BG_get_reg_bg_pow(data)                                       ((0x00000002&(data))>>1)
#define BG_get_reg_bg_envbgup(data)                                   (0x00000001&(data))


#define MD                                                            0xa04
#define MD_reg_addr                                                   "0x98034a04"
#define MD_reg                                                        0x98034a04
#define MD_inst_addr                                                  "0x0281"
#define MD_inst                                                       0x0281
#define set_MD_reg(data)                                              (*((volatile unsigned int*)MD_reg)=data)
#define get_MD_reg                                                    (*((volatile unsigned int*)MD_reg))
#define MD_reg_ck_latch_shift                                         (4)
#define MD_reg_ck_cmp_shift                                           (3)
#define MD_reg_ck_ckdet_shift                                         (0)
#define MD_reg_ck_latch_mask                                          (0x00000010)
#define MD_reg_ck_cmp_mask                                            (0x00000008)
#define MD_reg_ck_ckdet_mask                                          (0x00000007)
#define MD_reg_ck_latch(data)                                         (0x00000010&((data)<<4))
#define MD_reg_ck_cmp(data)                                           (0x00000008&((data)<<3))
#define MD_reg_ck_ckdet(data)                                         (0x00000007&(data))
#define MD_get_reg_ck_latch(data)                                     ((0x00000010&(data))>>4)
#define MD_get_reg_ck_cmp(data)                                       ((0x00000008&(data))>>3)
#define MD_get_reg_ck_ckdet(data)                                     (0x00000007&(data))


#define LDO                                                           0xa08
#define LDO_reg_addr                                                  "0x98034a08"
#define LDO_reg                                                       0x98034a08
#define LDO_inst_addr                                                 "0x0282"
#define LDO_inst                                                      0x0282
#define set_LDO_reg(data)                                             (*((volatile unsigned int*)LDO_reg)=data)
#define get_LDO_reg                                                   (*((volatile unsigned int*)LDO_reg))
#define LDO_reg_p2_ldo_sel_shift                                      (7)
#define LDO_reg_p1_ldo_sel_shift                                      (5)
#define LDO_reg_p0_ldo_sel_shift                                      (3)
#define LDO_reg_p2_ldo_pow_shift                                      (2)
#define LDO_reg_p1_ldo_pow_shift                                      (1)
#define LDO_reg_p0_ldo_pow_shift                                      (0)
#define LDO_reg_p2_ldo_sel_mask                                       (0x00000180)
#define LDO_reg_p1_ldo_sel_mask                                       (0x00000060)
#define LDO_reg_p0_ldo_sel_mask                                       (0x00000018)
#define LDO_reg_p2_ldo_pow_mask                                       (0x00000004)
#define LDO_reg_p1_ldo_pow_mask                                       (0x00000002)
#define LDO_reg_p0_ldo_pow_mask                                       (0x00000001)
#define LDO_reg_p2_ldo_sel(data)                                      (0x00000180&((data)<<7))
#define LDO_reg_p1_ldo_sel(data)                                      (0x00000060&((data)<<5))
#define LDO_reg_p0_ldo_sel(data)                                      (0x00000018&((data)<<3))
#define LDO_reg_p2_ldo_pow(data)                                      (0x00000004&((data)<<2))
#define LDO_reg_p1_ldo_pow(data)                                      (0x00000002&((data)<<1))
#define LDO_reg_p0_ldo_pow(data)                                      (0x00000001&(data))
#define LDO_get_reg_p2_ldo_sel(data)                                  ((0x00000180&(data))>>7)
#define LDO_get_reg_p1_ldo_sel(data)                                  ((0x00000060&(data))>>5)
#define LDO_get_reg_p0_ldo_sel(data)                                  ((0x00000018&(data))>>3)
#define LDO_get_reg_p2_ldo_pow(data)                                  ((0x00000004&(data))>>2)
#define LDO_get_reg_p1_ldo_pow(data)                                  ((0x00000002&(data))>>1)
#define LDO_get_reg_p0_ldo_pow(data)                                  (0x00000001&(data))


#define MHL                                                           0xa0c
#define MHL_reg_addr                                                  "0x98034a0c"
#define MHL_reg                                                       0x98034a0c
#define MHL_inst_addr                                                 "0x0283"
#define MHL_inst                                                      0x0283
#define set_MHL_reg(data)                                             (*((volatile unsigned int*)MHL_reg)=data)
#define get_MHL_reg                                                   (*((volatile unsigned int*)MHL_reg))
#define MHL_reg_p2_mhl_hdmi_datasel_shift                             (9)
#define MHL_reg_p2_mhl_hdmi_cksel_shift                               (8)
#define MHL_reg_p2_mhl_pow_shift                                      (7)
#define MHL_reg_p1_mhl_hdmi_datasel_shift                             (6)
#define MHL_reg_p1_mhl_hdmi_cksel_shift                               (5)
#define MHL_reg_p1_mhl_pow_shift                                      (4)
#define MHL_reg_p0_mhl_hdmi_cksel_shift                               (3)
#define MHL_reg_p0_mhl_hdmi_datasel_shift                             (2)
#define MHL_reg_p0_mhl_pow_shift                                      (1)
#define MHL_reg_mhl_hdmisel_shift                                     (0)
#define MHL_reg_p2_mhl_hdmi_datasel_mask                              (0x00000200)
#define MHL_reg_p2_mhl_hdmi_cksel_mask                                (0x00000100)
#define MHL_reg_p2_mhl_pow_mask                                       (0x00000080)
#define MHL_reg_p1_mhl_hdmi_datasel_mask                              (0x00000040)
#define MHL_reg_p1_mhl_hdmi_cksel_mask                                (0x00000020)
#define MHL_reg_p1_mhl_pow_mask                                       (0x00000010)
#define MHL_reg_p0_mhl_hdmi_cksel_mask                                (0x00000008)
#define MHL_reg_p0_mhl_hdmi_datasel_mask                              (0x00000004)
#define MHL_reg_p0_mhl_pow_mask                                       (0x00000002)
#define MHL_reg_mhl_hdmisel_mask                                      (0x00000001)
#define MHL_reg_p2_mhl_hdmi_datasel(data)                             (0x00000200&((data)<<9))
#define MHL_reg_p2_mhl_hdmi_cksel(data)                               (0x00000100&((data)<<8))
#define MHL_reg_p2_mhl_pow(data)                                      (0x00000080&((data)<<7))
#define MHL_reg_p1_mhl_hdmi_datasel(data)                             (0x00000040&((data)<<6))
#define MHL_reg_p1_mhl_hdmi_cksel(data)                               (0x00000020&((data)<<5))
#define MHL_reg_p1_mhl_pow(data)                                      (0x00000010&((data)<<4))
#define MHL_reg_p0_mhl_hdmi_cksel(data)                               (0x00000008&((data)<<3))
#define MHL_reg_p0_mhl_hdmi_datasel(data)                             (0x00000004&((data)<<2))
#define MHL_reg_p0_mhl_pow(data)                                      (0x00000002&((data)<<1))
#define MHL_reg_mhl_hdmisel(data)                                     (0x00000001&(data))
#define MHL_get_reg_p2_mhl_hdmi_datasel(data)                         ((0x00000200&(data))>>9)
#define MHL_get_reg_p2_mhl_hdmi_cksel(data)                           ((0x00000100&(data))>>8)
#define MHL_get_reg_p2_mhl_pow(data)                                  ((0x00000080&(data))>>7)
#define MHL_get_reg_p1_mhl_hdmi_datasel(data)                         ((0x00000040&(data))>>6)
#define MHL_get_reg_p1_mhl_hdmi_cksel(data)                           ((0x00000020&(data))>>5)
#define MHL_get_reg_p1_mhl_pow(data)                                  ((0x00000010&(data))>>4)
#define MHL_get_reg_p0_mhl_hdmi_cksel(data)                           ((0x00000008&(data))>>3)
#define MHL_get_reg_p0_mhl_hdmi_datasel(data)                         ((0x00000004&(data))>>2)
#define MHL_get_reg_p0_mhl_pow(data)                                  ((0x00000002&(data))>>1)
#define MHL_get_reg_mhl_hdmisel(data)                                 (0x00000001&(data))


#define P0_ACDR1                                                      0xa10
#define P0_ACDR1_reg_addr                                             "0x98034a10"
#define P0_ACDR1_reg                                                  0x98034a10
#define P0_ACDR1_inst_addr                                            "0x0284"
#define P0_ACDR1_inst                                                 0x0284
#define set_P0_ACDR1_reg(data)                                        (*((volatile unsigned int*)P0_ACDR1_reg)=data)
#define get_P0_ACDR1_reg                                              (*((volatile unsigned int*)P0_ACDR1_reg))
#define P0_ACDR1_reg_p0_acdr_4_shift                                  (24)
#define P0_ACDR1_reg_p0_acdr_3_shift                                  (16)
#define P0_ACDR1_reg_p0_acdr_2_shift                                  (8)
#define P0_ACDR1_reg_p0_acdr_1_shift                                  (0)
#define P0_ACDR1_reg_p0_acdr_4_mask                                   (0xFF000000)
#define P0_ACDR1_reg_p0_acdr_3_mask                                   (0x00FF0000)
#define P0_ACDR1_reg_p0_acdr_2_mask                                   (0x0000FF00)
#define P0_ACDR1_reg_p0_acdr_1_mask                                   (0x000000FF)
#define P0_ACDR1_reg_p0_acdr_4(data)                                  (0xFF000000&((data)<<24))
#define P0_ACDR1_reg_p0_acdr_3(data)                                  (0x00FF0000&((data)<<16))
#define P0_ACDR1_reg_p0_acdr_2(data)                                  (0x0000FF00&((data)<<8))
#define P0_ACDR1_reg_p0_acdr_1(data)                                  (0x000000FF&(data))
#define P0_ACDR1_get_reg_p0_acdr_4(data)                              ((0xFF000000&(data))>>24)
#define P0_ACDR1_get_reg_p0_acdr_3(data)                              ((0x00FF0000&(data))>>16)
#define P0_ACDR1_get_reg_p0_acdr_2(data)                              ((0x0000FF00&(data))>>8)
#define P0_ACDR1_get_reg_p0_acdr_1(data)                              (0x000000FF&(data))


#define P0_ACDR2                                                      0xa14
#define P0_ACDR2_reg_addr                                             "0x98034a14"
#define P0_ACDR2_reg                                                  0x98034a14
#define P0_ACDR2_inst_addr                                            "0x0285"
#define P0_ACDR2_inst                                                 0x0285
#define set_P0_ACDR2_reg(data)                                        (*((volatile unsigned int*)P0_ACDR2_reg)=data)
#define get_P0_ACDR2_reg                                              (*((volatile unsigned int*)P0_ACDR2_reg))
#define P0_ACDR2_reg_p0_acdr_8_shift                                  (24)
#define P0_ACDR2_reg_p0_acdr_7_shift                                  (16)
#define P0_ACDR2_reg_p0_acdr_6_shift                                  (8)
#define P0_ACDR2_reg_p0_acdr_5_shift                                  (0)
#define P0_ACDR2_reg_p0_acdr_8_mask                                   (0xFF000000)
#define P0_ACDR2_reg_p0_acdr_7_mask                                   (0x00FF0000)
#define P0_ACDR2_reg_p0_acdr_6_mask                                   (0x0000FF00)
#define P0_ACDR2_reg_p0_acdr_5_mask                                   (0x000000FF)
#define P0_ACDR2_reg_p0_acdr_8(data)                                  (0xFF000000&((data)<<24))
#define P0_ACDR2_reg_p0_acdr_7(data)                                  (0x00FF0000&((data)<<16))
#define P0_ACDR2_reg_p0_acdr_6(data)                                  (0x0000FF00&((data)<<8))
#define P0_ACDR2_reg_p0_acdr_5(data)                                  (0x000000FF&(data))
#define P0_ACDR2_get_reg_p0_acdr_8(data)                              ((0xFF000000&(data))>>24)
#define P0_ACDR2_get_reg_p0_acdr_7(data)                              ((0x00FF0000&(data))>>16)
#define P0_ACDR2_get_reg_p0_acdr_6(data)                              ((0x0000FF00&(data))>>8)
#define P0_ACDR2_get_reg_p0_acdr_5(data)                              (0x000000FF&(data))


#define P0_B1                                                         0xa18
#define P0_B1_reg_addr                                                "0x98034a18"
#define P0_B1_reg                                                     0x98034a18
#define P0_B1_inst_addr                                               "0x0286"
#define P0_B1_inst                                                    0x0286
#define set_P0_B1_reg(data)                                           (*((volatile unsigned int*)P0_B1_reg)=data)
#define get_P0_B1_reg                                                 (*((volatile unsigned int*)P0_B1_reg))
#define P0_B1_reg_p0_b_4_shift                                        (24)
#define P0_B1_reg_p0_b_3_shift                                        (16)
#define P0_B1_reg_p0_b_2_shift                                        (8)
#define P0_B1_reg_p0_b_1_shift                                        (0)
#define P0_B1_reg_p0_b_4_mask                                         (0xFF000000)
#define P0_B1_reg_p0_b_3_mask                                         (0x00FF0000)
#define P0_B1_reg_p0_b_2_mask                                         (0x0000FF00)
#define P0_B1_reg_p0_b_1_mask                                         (0x000000FF)
#define P0_B1_reg_p0_b_4(data)                                        (0xFF000000&((data)<<24))
#define P0_B1_reg_p0_b_3(data)                                        (0x00FF0000&((data)<<16))
#define P0_B1_reg_p0_b_2(data)                                        (0x0000FF00&((data)<<8))
#define P0_B1_reg_p0_b_1(data)                                        (0x000000FF&(data))
#define P0_B1_get_reg_p0_b_4(data)                                    ((0xFF000000&(data))>>24)
#define P0_B1_get_reg_p0_b_3(data)                                    ((0x00FF0000&(data))>>16)
#define P0_B1_get_reg_p0_b_2(data)                                    ((0x0000FF00&(data))>>8)
#define P0_B1_get_reg_p0_b_1(data)                                    (0x000000FF&(data))
#define P0_b_1_inputoff												(_BIT0)
#define P0_b_1_FORE_KOFF_RANGE										(_BIT22|_BIT21)
#define P0_b_4_FORE_KOFF_AUTOK										(_BIT28)
#define P0_b_CLK_PIX2_RATE_SEL										(_BIT26)
#define P0_b_DEMUX_BBPD_RSTB										(_BIT25)
#define P0_b_4_FORE_POW_FORE_KOFF									(_BIT24)
#define P0_b_3_FORE_EN_FORE_KOFF									(_BIT23)


#define P0_B2                                                         0xa1c
#define P0_B2_reg_addr                                                "0x98034a1c"
#define P0_B2_reg                                                     0x98034a1c
#define P0_B2_inst_addr                                               "0x0287"
#define P0_B2_inst                                                    0x0287
#define set_P0_B2_reg(data)                                           (*((volatile unsigned int*)P0_B2_reg)=data)
#define get_P0_B2_reg                                                 (*((volatile unsigned int*)P0_B2_reg))
#define P0_B2_reg_p0_b_8_shift                                        (24)
#define P0_B2_reg_p0_b_7_shift                                        (16)
#define P0_B2_reg_p0_b_6_shift                                        (8)
#define P0_B2_reg_p0_b_5_shift                                        (0)
#define P0_B2_reg_p0_b_8_mask                                         (0xFF000000)
#define P0_B2_reg_p0_b_7_mask                                         (0x00FF0000)
#define P0_B2_reg_p0_b_6_mask                                         (0x0000FF00)
#define P0_B2_reg_p0_b_5_mask                                         (0x000000FF)
#define P0_B2_reg_p0_b_8(data)                                        (0xFF000000&((data)<<24))
#define P0_B2_reg_p0_b_7(data)                                        (0x00FF0000&((data)<<16))
#define P0_B2_reg_p0_b_6(data)                                        (0x0000FF00&((data)<<8))
#define P0_B2_reg_p0_b_5(data)                                        (0x000000FF&(data))
#define P0_B2_get_reg_p0_b_8(data)                                    ((0xFF000000&(data))>>24)
#define P0_B2_get_reg_p0_b_7(data)                                    ((0x00FF0000&(data))>>16)
#define P0_B2_get_reg_p0_b_6(data)                                    ((0x0000FF00&(data))>>8)
#define P0_B2_get_reg_p0_b_5(data)                                    (0x000000FF&(data))
#define P0_B2_reg_p0_b_8_PR_RATE_SEL_shift						(26)
#define P0_B2_reg_p0_b_8_DEMUX_shift							(29)
#define P0_B2_reg_p0_b_7_TAP0_ISEL_shift						(21)
#define P0_b_8_DEMUX											(_BIT29|_BIT30|_BIT31)
#define P0_b_8_PR_RATE_SEL										(_BIT26|_BIT27|_BIT28)
#define P0_b_8_POW_PR											(_BIT25)
#define P0_b_7_TAP0_ISEL										(_BIT21|_BIT22|_BIT23)
#define P0_b_7_TAP0_ISEL_400uA									(_BIT22|_BIT23)
#define P0_b_7_LEQ_ISEL											(_BIT18|_BIT19|_BIT20)
#define P0_b_7_LEQ_ISEL_400uA									(_BIT19|_BIT20)
#define P0_b_7_LEQ_ISEL_200uA									(_BIT20)
#define P0_b_7_PI_ISEL											(_BIT16|_BIT17)
#define P0_b_6_LEQ_BIT_RATE										(_BIT14|_BIT15)
#define P0_b_6_LEQ_BIT_RATE_HBR									(_BIT15)
#define P0_b_6_LEQ_BIT_RATE_MBR									(_BIT14)
#define P0_b_6_TAP0_HBR											(_BIT13)
#define P0_b_6_LEQ_PASSIVE_CORNER								(_BIT12|_BIT11)
#define P0_b_5_LEQ_CURRENT_ADJ									(_BIT3|_BIT4)
#define P0_b_5_LEQ_CURRENT_ADJ_1X								(_BIT3)
#define P0_b_5_LEQ_CURRENT_ADJ_1p25X							(_BIT4)
#define P0_b_5_EQ_POW											(_BIT0)


#define P0_B3                                                         0xa20
#define P0_B3_reg_addr                                                "0x98034a20"
#define P0_B3_reg                                                     0x98034a20
#define P0_B3_inst_addr                                               "0x0288"
#define P0_B3_inst                                                    0x0288
#define set_P0_B3_reg(data)                                           (*((volatile unsigned int*)P0_B3_reg)=data)
#define get_P0_B3_reg                                                 (*((volatile unsigned int*)P0_B3_reg))
#define P0_B3_reg_p0_b_12_shift                                       (24)
#define P0_B3_reg_p0_b_11_shift                                       (16)
#define P0_B3_reg_p0_b_10_shift                                       (8)
#define P0_B3_reg_p0_b_9_shift                                        (0)
#define P0_B3_reg_p0_b_12_mask                                        (0xFF000000)
#define P0_B3_reg_p0_b_11_mask                                        (0x00FF0000)
#define P0_B3_reg_p0_b_10_mask                                        (0x0000FF00)
#define P0_B3_reg_p0_b_9_mask                                         (0x000000FF)
#define P0_B3_reg_p0_b_12(data)                                       (0xFF000000&((data)<<24))
#define P0_B3_reg_p0_b_11(data)                                       (0x00FF0000&((data)<<16))
#define P0_B3_reg_p0_b_10(data)                                       (0x0000FF00&((data)<<8))
#define P0_B3_reg_p0_b_9(data)                                        (0x000000FF&(data))
#define P0_B3_get_reg_p0_b_12(data)                                   ((0xFF000000&(data))>>24)
#define P0_B3_get_reg_p0_b_11(data)                                   ((0x00FF0000&(data))>>16)
#define P0_B3_get_reg_p0_b_10(data)                                   ((0x0000FF00&(data))>>8)
#define P0_B3_get_reg_p0_b_9(data)                                    (0x000000FF&(data))
#define P0_B_DFE_TAPEN4321											(_BIT6|_BIT5|_BIT4|_BIT3)
#define P0_b_12_PR													(_BIT24|_BIT25)
#define P0_b_9_DFE_ADAPTION_POW_EN									(_BIT7)
#define P0_b_9_DFE_TAP_EN											(_BIT3|_BIT4|_BIT5|_BIT6)
#define P0_b_9_DFE_TAP1_EN											(_BIT3)
#define DFE_HDMI_RX_PHY_P0_b_tap_en(data)							(0x00000078&((data)<<3))
#define P0_b_11_ACDR_RATE_SEL_HALF_RATE								(_BIT16)
#define P0_b_10_DFE_SUMAMP_LP_MANUALOFF								(_BIT15)
#define P0_b_10_DFE_SUMAMP_ISEL_mask								(_BIT11|_BIT12|_BIT13)
#define P0_b_10_DFE_SUMAMP_ISEL_400uA								(_BIT13)
#define P0_b_10_DFE_PREAMP_ISEL_mask								(_BIT8|_BIT9|_BIT10)
#define P0_b_10_DFE_PREAMP_ISEL_400uA								(_BIT10)


#define P0_B4                                                         0xa24
#define P0_B4_reg_addr                                                "0x98034a24"
#define P0_B4_reg                                                     0x98034a24
#define P0_B4_inst_addr                                               "0x0289"
#define P0_B4_inst                                                    0x0289
#define set_P0_B4_reg(data)                                           (*((volatile unsigned int*)P0_B4_reg)=data)
#define get_P0_B4_reg                                                 (*((volatile unsigned int*)P0_B4_reg))
#define P0_B4_reg_p0_b_koff_sel_shift                                 (10)
#define P0_B4_reg_p0_b_koff_bound_shift                               (9)
#define P0_B4_reg_p0_b_koffok_shift                                   (8)
#define P0_B4_reg_p0_b_13_shift                                       (0)
#define P0_B4_reg_p0_b_koff_sel_mask                                  (0x00007C00)
#define P0_B4_reg_p0_b_koff_bound_mask                                (0x00000200)
#define P0_B4_reg_p0_b_koffok_mask                                    (0x00000100)
#define P0_B4_reg_p0_b_13_mask                                        (0x000000FF)
#define P0_B4_reg_p0_b_koff_sel(data)                                 (0x00007C00&((data)<<10))
#define P0_B4_reg_p0_b_koff_bound(data)                               (0x00000200&((data)<<9))
#define P0_B4_reg_p0_b_koffok(data)                                   (0x00000100&((data)<<8))
#define P0_B4_reg_p0_b_13(data)                                       (0x000000FF&(data))
#define P0_B4_get_reg_p0_b_koff_sel(data)                             ((0x00007C00&(data))>>10)
#define P0_B4_get_reg_p0_b_koff_bound(data)                           ((0x00000200&(data))>>9)
#define P0_B4_get_reg_p0_b_koffok(data)                               ((0x00000100&(data))>>8)
#define P0_B4_get_reg_p0_b_13(data)                                   (0x000000FF&(data))


#define P0_CK1                                                        0xa28
#define P0_CK1_reg_addr                                               "0x98034a28"
#define P0_CK1_reg                                                    0x98034a28
#define P0_CK1_inst_addr                                              "0x028A"
#define P0_CK1_inst                                                   0x028A
#define set_P0_CK1_reg(data)                                          (*((volatile unsigned int*)P0_CK1_reg)=data)
#define get_P0_CK1_reg                                                (*((volatile unsigned int*)P0_CK1_reg))
#define P0_CK1_reg_p0_ck_4_shift                                      (24)
#define P0_CK1_reg_p0_ck_3_CMU_N_code_shift						 	(18)
#define P0_CK1_reg_p0_ck_3_shift                                      (16)
#define P0_CK1_reg_p0_ck_2_shift                                      (8)
#define P0_CK1_reg_p0_ck_1_shift                                      (0)
#define P0_CK1_reg_p0_ck_4_mask                                       (0xFF000000)
#define P0_CK1_reg_p0_ck_3_mask                                       (0x00FF0000)
#define P0_CK1_reg_p0_ck_2_mask                                       (0x0000FF00)
#define P0_CK1_reg_p0_ck_1_mask                                       (0x000000FF)
#define P0_CK1_reg_p0_ck_4(data)                                      (0xFF000000&((data)<<24))
#define P0_CK1_reg_p0_ck_3(data)                                      (0x00FF0000&((data)<<16))
#define P0_CK1_reg_p0_ck_2(data)                                      (0x0000FF00&((data)<<8))
#define P0_CK1_reg_p0_ck_1(data)                                      (0x000000FF&(data))
#define P0_CK1_get_reg_p0_ck_4(data)                                  ((0xFF000000&(data))>>24)
#define P0_CK1_get_reg_p0_ck_3(data)                                  ((0x00FF0000&(data))>>16)
#define P0_CK1_get_reg_p0_ck_2(data)                                  ((0x0000FF00&(data))>>8)
#define P0_CK1_get_reg_p0_ck_1(data)                                  (0x000000FF&(data))
#define p0_ck_3_CMU_PREDIVN												(_BIT20|_BIT21|_BIT22|_BIT23)
#define p0_ck_3_CMU_N_code												(_BIT18|_BIT19)
#define p0_ck_2_CMU_CKIN_SEL											(_BIT12|_BIT13|_BIT14|_BIT15)
#define p0_CMU_CKOUT_SEL												(_BIT11)
#define p0_ck_2_CK_MD_REF_SEL											(_BIT9)
#define p0_ck_1_port_bias												(_BIT2)
#define p0_ck_1_CKAFE_POW												(_BIT1)


#define P0_CK2                                                        0xa2c
#define P0_CK2_reg_addr                                               "0x98034a2c"
#define P0_CK2_reg                                                    0x98034a2c
#define P0_CK2_inst_addr                                              "0x028B"
#define P0_CK2_inst                                                   0x028B
#define set_P0_CK2_reg(data)                                          (*((volatile unsigned int*)P0_CK2_reg)=data)
#define get_P0_CK2_reg                                                (*((volatile unsigned int*)P0_CK2_reg))
#define P0_CK2_reg_p0_ck_8_shift                                      (24)
#define P0_CK2_reg_p0_ck_7_shift                                      (16)
#define P0_CK2_reg_p0_ck_6_shift                                      (8)
#define P0_CK2_reg_p0_ck_5_shift                                      (0)
#define P0_CK2_reg_p0_ck_8_mask                                       (0xFF000000)
#define P0_CK2_reg_p0_ck_7_mask                                       (0x00FF0000)
#define P0_CK2_reg_p0_ck_6_mask                                       (0x0000FF00)
#define P0_CK2_reg_p0_ck_5_mask                                       (0x000000FF)
#define P0_CK2_reg_p0_ck_8(data)                                      (0xFF000000&((data)<<24))
#define P0_CK2_reg_p0_ck_7(data)                                      (0x00FF0000&((data)<<16))
#define P0_CK2_reg_p0_ck_6(data)                                      (0x0000FF00&((data)<<8))
#define P0_CK2_reg_p0_ck_5(data)                                      (0x000000FF&(data))
#define P0_CK2_get_reg_p0_ck_8(data)                                  ((0xFF000000&(data))>>24)
#define P0_CK2_get_reg_p0_ck_7(data)                                  ((0x00FF0000&(data))>>16)
#define P0_CK2_get_reg_p0_ck_6(data)                                  ((0x0000FF00&(data))>>8)
#define P0_CK2_get_reg_p0_ck_5(data)                                  (0x000000FF&(data))
#define P0_ck_8_LDO_EN												(_BIT25)
#define P0_ck_8_VSEL_LDO_A_mask										(_BIT29|_BIT30|_BIT31)
#define P0_ck_8_VSEL_LDO_D_mask										(_BIT26|_BIT27|_BIT28)
#define P0_ck_8_LDO_EN_mask											(_BIT25)
#define P0_ck_8_CMU_BPPSR_mask										(_BIT24)
#define P0_ck_7_CMU_BYPASS_PI_mask									(_BIT19)
#define P0_ck_7_CMU_PI_I_SEL_mask									(_BIT16|_BIT17|_BIT18)
#define P0_ck_6_CMU_BIG_KVCO_mask									(_BIT13)
#define P0_ck_6_CMU_EN_CAP_mask										(_BIT12)
#define P0_ck_6_CMU_SEL_CS_mask										(_BIT8|_BIT9|_BIT10)
#define P0_ck_5_CMU_SEL_PUMP_I_mask									(_BIT4|_BIT5|_BIT6|_BIT7)
#define P0_ck_5_CMU_SEL_R1_mask										(_BIT0|_BIT1|_BIT2)
#define DFE_HDMI_RX_PHY_P0_VSEL_LDO_D(data)							(0x1C000000&((data)<<26))
#define DFE_HDMI_RX_PHY_P0_CMU_BPPSR(data)							(0x01000000&((data)<<24))
#define DFE_HDMI_RX_PHY_P0_CMU_SEL_CS(data)							(0x00000700&((data)<<8))
#define DFE_HDMI_RX_PHY_P0_CMU_SEL_PUMP_I(data)						(0x000000F0&((data)<<4))
#define DFE_HDMI_RX_PHY_P0_CMU_SEL_R1(data)							(0x00000007&((data)<<0))
#define DFE_HDMI_RX_PHY_P0_VSEL_LDO_A(data)							(0xE0000000&((data)<<29))
#define DFE_HDMI_RX_PHY_P0_VSEL_LDO_D(data)							(0x1C000000&((data)<<26))
#define DFE_HDMI_RX_PHY_P0_CMU_BPPSR(data)							(0x01000000&((data)<<24))
#define DFE_HDMI_RX_PHY_P0_CMU_SEL_CS(data)							(0x00000700&((data)<<8))
#define DFE_HDMI_RX_PHY_P0_CMU_SEL_PUMP_I(data)						(0x000000F0&((data)<<4))
#define DFE_HDMI_RX_PHY_P0_CMU_SEL_R1(data)							(0x00000007&((data)<<0))


#define P0_CK3                                                        0xa30
#define P0_CK3_reg_addr                                               "0x98034a30"
#define P0_CK3_reg                                                    0x98034a30
#define P0_CK3_inst_addr                                              "0x028C"
#define P0_CK3_inst                                                   0x028C
#define set_P0_CK3_reg(data)                                          (*((volatile unsigned int*)P0_CK3_reg)=data)
#define get_P0_CK3_reg                                                (*((volatile unsigned int*)P0_CK3_reg))
#define P0_CK3_reg_p0_ck_12_shift                                     (24)
#define P0_CK3_reg_p0_ck_11_shift                                     (16)
#define P0_CK3_reg_p0_ck_10_shift                                     (8)
#define P0_CK3_reg_p0_ck_9_shift                                      (0)
#define P0_CK3_reg_p0_ck_12_mask                                      (0xFF000000)
#define P0_CK3_reg_p0_ck_11_mask                                      (0x00FF0000)
#define P0_CK3_reg_p0_ck_10_mask                                      (0x0000FF00)
#define P0_CK3_reg_p0_ck_9_mask                                       (0x000000FF)
#define P0_CK3_reg_p0_ck_12(data)                                     (0xFF000000&((data)<<24))
#define P0_CK3_reg_p0_ck_11(data)                                     (0x00FF0000&((data)<<16))
#define P0_CK3_reg_p0_ck_10(data)                                     (0x0000FF00&((data)<<8))
#define P0_CK3_reg_p0_ck_9(data)                                      (0x000000FF&(data))
#define P0_CK3_get_reg_p0_ck_12(data)                                 ((0xFF000000&(data))>>24)
#define P0_CK3_get_reg_p0_ck_11(data)                                 ((0x00FF0000&(data))>>16)
#define P0_CK3_get_reg_p0_ck_10(data)                                 ((0x0000FF00&(data))>>8)
#define P0_CK3_get_reg_p0_ck_9(data)                                  (0x000000FF&(data))
#define P0_ck_9_CMU_PFD_RSTB										(_BIT5)
#define P0_ck_9_CMU_WDRST											(_BIT2)


#define P0_CK4                                                        0xa34
#define P0_CK4_reg_addr                                               "0x98034a34"
#define P0_CK4_reg                                                    0x98034a34
#define P0_CK4_inst_addr                                              "0x028D"
#define P0_CK4_inst                                                   0x028D
#define set_P0_CK4_reg(data)                                          (*((volatile unsigned int*)P0_CK4_reg)=data)
#define get_P0_CK4_reg                                                (*((volatile unsigned int*)P0_CK4_reg))
#define P0_CK4_reg_p0_ck_13_shift                                     (0)
#define P0_CK4_reg_p0_ck_13_mask                                      (0x000000FF)
#define P0_CK4_reg_p0_ck_13(data)                                     (0x000000FF&(data))
#define P0_CK4_get_reg_p0_ck_13(data)                                 (0x000000FF&(data))


#define ENABLE                                                        0xa38
#define ENABLE_reg_addr                                               "0x98034a38"
#define ENABLE_reg                                                    0x98034a38
#define ENABLE_inst_addr                                              "0x028E"
#define ENABLE_inst                                                   0x028E
#define set_ENABLE_reg(data)                                          (*((volatile unsigned int*)ENABLE_reg)=data)
#define get_ENABLE_reg                                                (*((volatile unsigned int*)ENABLE_reg))
#define ENABLE_reg_p2_en_rx_shift                                     (18)
#define ENABLE_reg_p2_en_cmu_shift                                    (17)
#define ENABLE_reg_p2_en_cdr_shift                                    (14)
#define ENABLE_reg_p1_en_rx_shift                                     (11)
#define ENABLE_reg_p1_en_cmu_shift                                    (10)
#define ENABLE_reg_p1_en_cdr_shift                                    (7)
#define ENABLE_reg_p0_en_rx_shift                                     (4)
#define ENABLE_reg_p0_en_cmu_shift                                    (3)
#define ENABLE_reg_p0_en_cdr_shift                                    (0)
#define ENABLE_reg_p2_en_rx_mask                                      (0x001C0000)
#define ENABLE_reg_p2_en_cmu_mask                                     (0x00020000)
#define ENABLE_reg_p2_en_cdr_mask                                     (0x0001C000)
#define ENABLE_reg_p1_en_rx_mask                                      (0x00003800)
#define ENABLE_reg_p1_en_cmu_mask                                     (0x00000400)
#define ENABLE_reg_p1_en_cdr_mask                                     (0x00000380)
#define ENABLE_reg_p0_en_rx_mask                                      (0x00000070)
#define ENABLE_reg_p0_en_cmu_mask                                     (0x00000008)
#define ENABLE_reg_p0_en_cdr_mask                                     (0x00000007)
#define ENABLE_reg_p2_en_rx(data)                                     (0x001C0000&((data)<<18))
#define ENABLE_reg_p2_en_cmu(data)                                    (0x00020000&((data)<<17))
#define ENABLE_reg_p2_en_cdr(data)                                    (0x0001C000&((data)<<14))
#define ENABLE_reg_p1_en_rx(data)                                     (0x00003800&((data)<<11))
#define ENABLE_reg_p1_en_cmu(data)                                    (0x00000400&((data)<<10))
#define ENABLE_reg_p1_en_cdr(data)                                    (0x00000380&((data)<<7))
#define ENABLE_reg_p0_en_rx(data)                                     (0x00000070&((data)<<4))
#define ENABLE_reg_p0_en_cmu(data)                                    (0x00000008&((data)<<3))
#define ENABLE_reg_p0_en_cdr(data)                                    (0x00000007&(data))
#define ENABLE_get_reg_p2_en_rx(data)                                 ((0x001C0000&(data))>>18)
#define ENABLE_get_reg_p2_en_cmu(data)                                ((0x00020000&(data))>>17)
#define ENABLE_get_reg_p2_en_cdr(data)                                ((0x0001C000&(data))>>14)
#define ENABLE_get_reg_p1_en_rx(data)                                 ((0x00003800&(data))>>11)
#define ENABLE_get_reg_p1_en_cmu(data)                                ((0x00000400&(data))>>10)
#define ENABLE_get_reg_p1_en_cdr(data)                                ((0x00000380&(data))>>7)
#define ENABLE_get_reg_p0_en_rx(data)                                 ((0x00000070&(data))>>4)
#define ENABLE_get_reg_p0_en_cmu(data)                                ((0x00000008&(data))>>3)
#define ENABLE_get_reg_p0_en_cdr(data)                                (0x00000007&(data))


#define P0_G1                                                         0xa3c
#define P0_G1_reg_addr                                                "0x98034a3c"
#define P0_G1_reg                                                     0x98034a3c
#define P0_G1_inst_addr                                               "0x028F"
#define P0_G1_inst                                                    0x028F
#define set_P0_G1_reg(data)                                           (*((volatile unsigned int*)P0_G1_reg)=data)
#define get_P0_G1_reg                                                 (*((volatile unsigned int*)P0_G1_reg))
#define P0_G1_reg_p0_g_4_shift                                        (24)
#define P0_G1_reg_p0_g_3_shift                                        (16)
#define P0_G1_reg_p0_g_2_shift                                        (8)
#define P0_G1_reg_p0_g_1_shift                                        (0)
#define P0_G1_reg_p0_g_4_mask                                         (0xFF000000)
#define P0_G1_reg_p0_g_3_mask                                         (0x00FF0000)
#define P0_G1_reg_p0_g_2_mask                                         (0x0000FF00)
#define P0_G1_reg_p0_g_1_mask                                         (0x000000FF)
#define P0_G1_reg_p0_g_4(data)                                        (0xFF000000&((data)<<24))
#define P0_G1_reg_p0_g_3(data)                                        (0x00FF0000&((data)<<16))
#define P0_G1_reg_p0_g_2(data)                                        (0x0000FF00&((data)<<8))
#define P0_G1_reg_p0_g_1(data)                                        (0x000000FF&(data))
#define P0_G1_get_reg_p0_g_4(data)                                    ((0xFF000000&(data))>>24)
#define P0_G1_get_reg_p0_g_3(data)                                    ((0x00FF0000&(data))>>16)
#define P0_G1_get_reg_p0_g_2(data)                                    ((0x0000FF00&(data))>>8)
#define P0_G1_get_reg_p0_g_1(data)                                    (0x000000FF&(data))
#define P0_g_1_inputoff												(_BIT0)
#define P0_g_1_FORE_KOFF_RANGE										(_BIT22|_BIT21)
#define P0_g_4_FORE_KOFF_AUTOK										(_BIT28)
#define P0_g_CLK_PIX2_RATE_SEL										(_BIT26)
#define P0_g_DEMUX_BBPD_RSTB										(_BIT25)
#define P0_g_4_FORE_POW_FORE_KOFF									(_BIT24)
#define P0_g_3_FORE_EN_FORE_KOFF									(_BIT23)


#define P0_G2                                                         0xa40
#define P0_G2_reg_addr                                                "0x98034a40"
#define P0_G2_reg                                                     0x98034a40
#define P0_G2_inst_addr                                               "0x0290"
#define P0_G2_inst                                                    0x0290
#define set_P0_G2_reg(data)                                           (*((volatile unsigned int*)P0_G2_reg)=data)
#define get_P0_G2_reg                                                 (*((volatile unsigned int*)P0_G2_reg))
#define P0_G2_reg_p0_g_8_shift                                        (24)
#define P0_G2_reg_p0_g_7_shift                                        (16)
#define P0_G2_reg_p0_g_6_shift                                        (8)
#define P0_G2_reg_p0_g_5_shift                                        (0)
#define P0_G2_reg_p0_g_8_mask                                         (0xFF000000)
#define P0_G2_reg_p0_g_7_mask                                         (0x00FF0000)
#define P0_G2_reg_p0_g_6_mask                                         (0x0000FF00)
#define P0_G2_reg_p0_g_5_mask                                         (0x000000FF)
#define P0_G2_reg_p0_g_8(data)                                        (0xFF000000&((data)<<24))
#define P0_G2_reg_p0_g_7(data)                                        (0x00FF0000&((data)<<16))
#define P0_G2_reg_p0_g_6(data)                                        (0x0000FF00&((data)<<8))
#define P0_G2_reg_p0_g_5(data)                                        (0x000000FF&(data))
#define P0_G2_get_reg_p0_g_8(data)                                    ((0xFF000000&(data))>>24)
#define P0_G2_get_reg_p0_g_7(data)                                    ((0x00FF0000&(data))>>16)
#define P0_G2_get_reg_p0_g_6(data)                                    ((0x0000FF00&(data))>>8)
#define P0_G2_get_reg_p0_g_5(data)                                    (0x000000FF&(data))
#define P0_G2_reg_p0_g_8_PR_RATE_SEL_shift							(26)
#define P0_G2_reg_p0_g_8_DEMUX_shift								(29)
#define P0_G2_reg_p0_g_7_TAP0_ISEL_shift							(21)
#define P0_g_8_DEMUX												(_BIT29|_BIT30|_BIT31)
#define P0_g_8_PR_RATE_SEL											(_BIT26|_BIT27|_BIT28)
#define P0_g_8_POW_PR												(_BIT25)
#define P0_g_7_TAP0_ISEL											(_BIT21|_BIT22|_BIT23)
#define P0_g_7_TAP0_ISEL_400uA										(_BIT22|_BIT23)
#define P0_g_7_LEQ_ISEL												(_BIT18|_BIT19|_BIT20)
#define P0_g_7_LEQ_ISEL_400uA										(_BIT19|_BIT20)
#define P0_g_7_LEQ_ISEL_200uA										(_BIT20)
#define P0_g_7_PI_ISEL												(_BIT16|_BIT17)
#define P0_g_6_LEQ_BIT_RATE											(_BIT14|_BIT15)
#define P0_g_6_LEQ_BIT_RATE_HBR										(_BIT15)
#define P0_g_6_LEQ_BIT_RATE_MBR										(_BIT14)
#define P0_g_6_TAP0_HBR												(_BIT13)
#define P0_g_6_LEQ_PASSIVE_CORNER									(_BIT12|_BIT11)
#define P0_g_5_LEQ_CURRENT_ADJ										(_BIT3|_BIT4)
#define P0_g_5_LEQ_CURRENT_ADJ_1X									(_BIT3)
#define P0_g_5_LEQ_CURRENT_ADJ_1p25X								(_BIT4)
#define P0_g_5_EQ_POW												(_BIT0)


#define P0_G3                                                         0xa44
#define P0_G3_reg_addr                                                "0x98034a44"
#define P0_G3_reg                                                     0x98034a44
#define P0_G3_inst_addr                                               "0x0291"
#define P0_G3_inst                                                    0x0291
#define set_P0_G3_reg(data)                                           (*((volatile unsigned int*)P0_G3_reg)=data)
#define get_P0_G3_reg                                                 (*((volatile unsigned int*)P0_G3_reg))
#define P0_G3_reg_p0_g_12_shift                                       (24)
#define P0_G3_reg_p0_g_11_shift                                       (16)
#define P0_G3_reg_p0_g_10_shift                                       (8)
#define P0_G3_reg_p0_g_9_shift                                        (0)
#define P0_G3_reg_p0_g_12_mask                                        (0xFF000000)
#define P0_G3_reg_p0_g_11_mask                                        (0x00FF0000)
#define P0_G3_reg_p0_g_10_mask                                        (0x0000FF00)
#define P0_G3_reg_p0_g_9_mask                                         (0x000000FF)
#define P0_G3_reg_p0_g_12(data)                                       (0xFF000000&((data)<<24))
#define P0_G3_reg_p0_g_11(data)                                       (0x00FF0000&((data)<<16))
#define P0_G3_reg_p0_g_10(data)                                       (0x0000FF00&((data)<<8))
#define P0_G3_reg_p0_g_9(data)                                        (0x000000FF&(data))
#define P0_G3_get_reg_p0_g_12(data)                                   ((0xFF000000&(data))>>24)
#define P0_G3_get_reg_p0_g_11(data)                                   ((0x00FF0000&(data))>>16)
#define P0_G3_get_reg_p0_g_10(data)                                   ((0x0000FF00&(data))>>8)
#define P0_G3_get_reg_p0_g_9(data)                                    (0x000000FF&(data))
#define P0_G_DFE_TAPEN4321											(_BIT6|_BIT5|_BIT4|_BIT3)
#define P0_g_12_PR													(_BIT24|_BIT25)
#define P0_g_9_DFE_ADAPTION_POW_EN									(_BIT7)
#define P0_g_9_DFE_TAP_EN											(_BIT3|_BIT4|_BIT5|_BIT6)
#define P0_g_9_DFE_TAP1_EN											(_BIT3)
#define DFE_HDMI_RX_PHY_P0_g_tap_en(data)							(0x00000078&((data)<<3))
#define P0_g_11_ACDR_RATE_SEL_HALF_RATE 							(_BIT16)
#define P0_g_10_DFE_SUMAMP_LP_MANUALOFF								(_BIT15)
#define P0_g_10_DFE_SUMAMP_ISEL_mask								(_BIT11|_BIT12|_BIT13)
#define P0_g_10_DFE_SUMAMP_ISEL_400uA								(_BIT13)
#define P0_g_10_DFE_PREAMP_ISEL_mask								(_BIT8|_BIT9|_BIT10)
#define P0_g_10_DFE_PREAMP_ISEL_400uA								(_BIT10)


#define P0_G4                                                         0xa48
#define P0_G4_reg_addr                                                "0x98034a48"
#define P0_G4_reg                                                     0x98034a48
#define P0_G4_inst_addr                                               "0x0292"
#define P0_G4_inst                                                    0x0292
#define set_P0_G4_reg(data)                                           (*((volatile unsigned int*)P0_G4_reg)=data)
#define get_P0_G4_reg                                                 (*((volatile unsigned int*)P0_G4_reg))
#define P0_G4_reg_p0_g_koff_sel_shift                                 (10)
#define P0_G4_reg_p0_g_koff_bound_shift                               (9)
#define P0_G4_reg_p0_g_koffok_shift                                   (8)
#define P0_G4_reg_p0_g_13_shift                                       (0)
#define P0_G4_reg_p0_g_koff_sel_mask                                  (0x00007C00)
#define P0_G4_reg_p0_g_koff_bound_mask                                (0x00000200)
#define P0_G4_reg_p0_g_koffok_mask                                    (0x00000100)
#define P0_G4_reg_p0_g_13_mask                                        (0x000000FF)
#define P0_G4_reg_p0_g_koff_sel(data)                                 (0x00007C00&((data)<<10))
#define P0_G4_reg_p0_g_koff_bound(data)                               (0x00000200&((data)<<9))
#define P0_G4_reg_p0_g_koffok(data)                                   (0x00000100&((data)<<8))
#define P0_G4_reg_p0_g_13(data)                                       (0x000000FF&(data))
#define P0_G4_get_reg_p0_g_koff_sel(data)                             ((0x00007C00&(data))>>10)
#define P0_G4_get_reg_p0_g_koff_bound(data)                           ((0x00000200&(data))>>9)
#define P0_G4_get_reg_p0_g_koffok(data)                               ((0x00000100&(data))>>8)
#define P0_G4_get_reg_p0_g_13(data)                                   (0x000000FF&(data))


#define P0_R1                                                         0xa4c
#define P0_R1_reg_addr                                                "0x98034a4c"
#define P0_R1_reg                                                     0x98034a4c
#define P0_R1_inst_addr                                               "0x0293"
#define P0_R1_inst                                                    0x0293
#define set_P0_R1_reg(data)                                           (*((volatile unsigned int*)P0_R1_reg)=data)
#define get_P0_R1_reg                                                 (*((volatile unsigned int*)P0_R1_reg))
#define P0_R1_reg_p0_r_4_shift                                        (24)
#define P0_R1_reg_p0_r_3_shift                                        (16)
#define P0_R1_reg_p0_r_2_shift                                        (8)
#define P0_R1_reg_p0_r_1_shift                                        (0)
#define P0_R1_reg_p0_r_4_mask                                         (0xFF000000)
#define P0_R1_reg_p0_r_3_mask                                         (0x00FF0000)
#define P0_R1_reg_p0_r_2_mask                                         (0x0000FF00)
#define P0_R1_reg_p0_r_1_mask                                         (0x000000FF)
#define P0_R1_reg_p0_r_4(data)                                        (0xFF000000&((data)<<24))
#define P0_R1_reg_p0_r_3(data)                                        (0x00FF0000&((data)<<16))
#define P0_R1_reg_p0_r_2(data)                                        (0x0000FF00&((data)<<8))
#define P0_R1_reg_p0_r_1(data)                                        (0x000000FF&(data))
#define P0_R1_get_reg_p0_r_4(data)                                    ((0xFF000000&(data))>>24)
#define P0_R1_get_reg_p0_r_3(data)                                    ((0x00FF0000&(data))>>16)
#define P0_R1_get_reg_p0_r_2(data)                                    ((0x0000FF00&(data))>>8)
#define P0_R1_get_reg_p0_r_1(data)                                    (0x000000FF&(data))
#define  P0_r_4_FORE_KOFF_AUTOK										(_BIT28)
#define  P0_r_CLK_PIX2_RATE_SEL										(_BIT26)
#define  P0_r_1_FORE_KOFF_RANGE										(_BIT22|_BIT21)
#define  P0_r_1_inputoff											(_BIT0)
#define  P0_r_DEMUX_BBPD_RSTB										(_BIT25)
#define  P0_r_4_FORE_POW_FORE_KOFF									(_BIT24)
#define  P0_r_3_FORE_EN_FORE_KOFF									(_BIT23)


#define P0_R2                                                         0xa50
#define P0_R2_reg_addr                                                "0x98034a50"
#define P0_R2_reg                                                     0x98034a50
#define P0_R2_inst_addr                                               "0x0294"
#define P0_R2_inst                                                    0x0294
#define set_P0_R2_reg(data)                                           (*((volatile unsigned int*)P0_R2_reg)=data)
#define get_P0_R2_reg                                                 (*((volatile unsigned int*)P0_R2_reg))
#define P0_R2_reg_p0_r_8_shift                                        (24)
#define P0_R2_reg_p0_r_7_shift                                        (16)
#define P0_R2_reg_p0_r_6_shift                                        (8)
#define P0_R2_reg_p0_r_5_shift                                        (0)
#define P0_R2_reg_p0_r_8_mask                                         (0xFF000000)
#define P0_R2_reg_p0_r_7_mask                                         (0x00FF0000)
#define P0_R2_reg_p0_r_6_mask                                         (0x0000FF00)
#define P0_R2_reg_p0_r_5_mask                                         (0x000000FF)
#define P0_R2_reg_p0_r_8(data)                                        (0xFF000000&((data)<<24))
#define P0_R2_reg_p0_r_7(data)                                        (0x00FF0000&((data)<<16))
#define P0_R2_reg_p0_r_6(data)                                        (0x0000FF00&((data)<<8))
#define P0_R2_reg_p0_r_5(data)                                        (0x000000FF&(data))
#define P0_R2_get_reg_p0_r_8(data)                                    ((0xFF000000&(data))>>24)
#define P0_R2_get_reg_p0_r_7(data)                                    ((0x00FF0000&(data))>>16)
#define P0_R2_get_reg_p0_r_6(data)                                    ((0x0000FF00&(data))>>8)
#define P0_R2_get_reg_p0_r_5(data)                                    (0x000000FF&(data))
#define P0_R2_reg_p0_r_8_PR_RATE_SEL_shift							(26)
#define P0_R2_reg_p0_r_8_DEMUX_shift								(29)
#define P0_R2_reg_p0_r_7_TAP0_ISEL_shift							(21)
#define P0_r_8_DEMUX												(_BIT29|_BIT30|_BIT31)
#define P0_r_8_PR_RATE_SEL											(_BIT26|_BIT27|_BIT28)
#define P0_r_8_POW_PR												(_BIT25)
#define P0_r_7_TAP0_ISEL											(_BIT21|_BIT22|_BIT23)
#define P0_r_7_TAP0_ISEL_400uA										(_BIT22|_BIT23)
#define P0_r_7_LEQ_ISEL												(_BIT18|_BIT19|_BIT20)
#define P0_r_7_LEQ_ISEL_400uA										(_BIT19|_BIT20)
#define P0_r_7_LEQ_ISEL_200uA										(_BIT20)
#define P0_r_7_PI_ISEL												(_BIT16|_BIT17)
#define P0_r_6_LEQ_BIT_RATE											(_BIT14|_BIT15)
#define P0_r_6_LEQ_BIT_RATE_HBR										(_BIT15)
#define P0_r_6_LEQ_BIT_RATE_MBR										(_BIT14)
#define P0_r_6_TAP0_HBR												(_BIT13)
#define P0_r_6_LEQ_PASSIVE_CORNER									(_BIT12|_BIT11)
#define P0_r_5_LEQ_CURRENT_ADJ 										(_BIT3|_BIT4)
#define P0_r_5_LEQ_CURRENT_ADJ_1X									(_BIT3)
#define P0_r_5_LEQ_CURRENT_ADJ_1p25X								(_BIT4)
#define P0_r_5_EQ_POW												(_BIT0)


#define P0_R3                                                         0xa54
#define P0_R3_reg_addr                                                "0x98034a54"
#define P0_R3_reg                                                     0x98034a54
#define P0_R3_inst_addr                                               "0x0295"
#define P0_R3_inst                                                    0x0295
#define set_P0_R3_reg(data)                                           (*((volatile unsigned int*)P0_R3_reg)=data)
#define get_P0_R3_reg                                                 (*((volatile unsigned int*)P0_R3_reg))
#define P0_R3_reg_p0_r_12_shift                                       (24)
#define P0_R3_reg_p0_r_11_shift                                       (16)
#define P0_R3_reg_p0_r_10_shift                                       (8)
#define P0_R3_reg_p0_r_9_shift                                        (0)
#define P0_R3_reg_p0_r_12_mask                                        (0xFF000000)
#define P0_R3_reg_p0_r_11_mask                                        (0x00FF0000)
#define P0_R3_reg_p0_r_10_mask                                        (0x0000FF00)
#define P0_R3_reg_p0_r_9_mask                                         (0x000000FF)
#define P0_R3_reg_p0_r_12(data)                                       (0xFF000000&((data)<<24))
#define P0_R3_reg_p0_r_11(data)                                       (0x00FF0000&((data)<<16))
#define P0_R3_reg_p0_r_10(data)                                       (0x0000FF00&((data)<<8))
#define P0_R3_reg_p0_r_9(data)                                        (0x000000FF&(data))
#define P0_R3_get_reg_p0_r_12(data)                                   ((0xFF000000&(data))>>24)
#define P0_R3_get_reg_p0_r_11(data)                                   ((0x00FF0000&(data))>>16)
#define P0_R3_get_reg_p0_r_10(data)                                   ((0x0000FF00&(data))>>8)
#define P0_R3_get_reg_p0_r_9(data)                                    (0x000000FF&(data))
#define P0_R_DFE_TAPEN4321											(_BIT6|_BIT5|_BIT4|_BIT3)
#define P0_r_12_PR													(_BIT24|_BIT25)
#define P0_r_9_DFE_ADAPTION_POW_EN									(_BIT7)
#define P0_r_9_DFE_TAP_EN											(_BIT3|_BIT4|_BIT5|_BIT6)
#define P0_r_9_DFE_TAP1_EN											(_BIT3)
#define DFE_HDMI_RX_PHY_P0_r_tap_en(data)							(0x00000078&((data)<<3))
#define P0_r_11_ACDR_RATE_SEL										(_BIT24|_BIT25)
#define P0_r_11_ACDR_RATE_SEL_HALF_RATE								(_BIT16)
#define P0_r_10_DFE_SUMAMP_LP_MANUALOFF								(_BIT15)
#define P0_r_10_DFE_SUMAMP_ISEL_mask								(_BIT11|_BIT12|_BIT13)
#define P0_r_10_DFE_SUMAMP_ISEL_400uA								(_BIT13)
#define P0_r_10_DFE_PREAMP_ISEL_mask								(_BIT8|_BIT9|_BIT10)
#define P0_r_10_DFE_PREAMP_ISEL_400uA								(_BIT10)


#define P0_R4                                                         0xa58
#define P0_R4_reg_addr                                                "0x98034a58"
#define P0_R4_reg                                                     0x98034a58
#define P0_R4_inst_addr                                               "0x0296"
#define P0_R4_inst                                                    0x0296
#define set_P0_R4_reg(data)                                           (*((volatile unsigned int*)P0_R4_reg)=data)
#define get_P0_R4_reg                                                 (*((volatile unsigned int*)P0_R4_reg))
#define P0_R4_reg_p0_r_koff_sel_shift                                 (10)
#define P0_R4_reg_p0_r_koff_bound_shift                               (9)
#define P0_R4_reg_p0_r_koffok_shift                                   (8)
#define P0_R4_reg_p0_r_13_shift                                       (0)
#define P0_R4_reg_p0_r_koff_sel_mask                                  (0x00007C00)
#define P0_R4_reg_p0_r_koff_bound_mask                                (0x00000200)
#define P0_R4_reg_p0_r_koffok_mask                                    (0x00000100)
#define P0_R4_reg_p0_r_13_mask                                        (0x000000FF)
#define P0_R4_reg_p0_r_koff_sel(data)                                 (0x00007C00&((data)<<10))
#define P0_R4_reg_p0_r_koff_bound(data)                               (0x00000200&((data)<<9))
#define P0_R4_reg_p0_r_koffok(data)                                   (0x00000100&((data)<<8))
#define P0_R4_reg_p0_r_13(data)                                       (0x000000FF&(data))
#define P0_R4_get_reg_p0_r_koff_sel(data)                             ((0x00007C00&(data))>>10)
#define P0_R4_get_reg_p0_r_koff_bound(data)                           ((0x00000200&(data))>>9)
#define P0_R4_get_reg_p0_r_koffok(data)                               ((0x00000100&(data))>>8)
#define P0_R4_get_reg_p0_r_13(data)                                   (0x000000FF&(data))


#define P1_ACDR1                                                      0xa5c
#define P1_ACDR1_reg_addr                                             "0x98034a5c"
#define P1_ACDR1_reg                                                  0x98034a5c
#define P1_ACDR1_inst_addr                                            "0x0297"
#define P1_ACDR1_inst                                                 0x0297
#define set_P1_ACDR1_reg(data)                                        (*((volatile unsigned int*)P1_ACDR1_reg)=data)
#define get_P1_ACDR1_reg                                              (*((volatile unsigned int*)P1_ACDR1_reg))
#define P1_ACDR1_reg_p1_acdr_4_shift                                  (24)
#define P1_ACDR1_reg_p1_acdr_3_shift                                  (16)
#define P1_ACDR1_reg_p1_acdr_2_shift                                  (8)
#define P1_ACDR1_reg_p1_acdr_1_shift                                  (0)
#define P1_ACDR1_reg_p1_acdr_4_mask                                   (0xFF000000)
#define P1_ACDR1_reg_p1_acdr_3_mask                                   (0x00FF0000)
#define P1_ACDR1_reg_p1_acdr_2_mask                                   (0x0000FF00)
#define P1_ACDR1_reg_p1_acdr_1_mask                                   (0x000000FF)
#define P1_ACDR1_reg_p1_acdr_4(data)                                  (0xFF000000&((data)<<24))
#define P1_ACDR1_reg_p1_acdr_3(data)                                  (0x00FF0000&((data)<<16))
#define P1_ACDR1_reg_p1_acdr_2(data)                                  (0x0000FF00&((data)<<8))
#define P1_ACDR1_reg_p1_acdr_1(data)                                  (0x000000FF&(data))
#define P1_ACDR1_get_reg_p1_acdr_4(data)                              ((0xFF000000&(data))>>24)
#define P1_ACDR1_get_reg_p1_acdr_3(data)                              ((0x00FF0000&(data))>>16)
#define P1_ACDR1_get_reg_p1_acdr_2(data)                              ((0x0000FF00&(data))>>8)
#define P1_ACDR1_get_reg_p1_acdr_1(data)                              (0x000000FF&(data))


#define P1_ACDR2                                                      0xa60
#define P1_ACDR2_reg_addr                                             "0x98034a60"
#define P1_ACDR2_reg                                                  0x98034a60
#define P1_ACDR2_inst_addr                                            "0x0298"
#define P1_ACDR2_inst                                                 0x0298
#define set_P1_ACDR2_reg(data)                                        (*((volatile unsigned int*)P1_ACDR2_reg)=data)
#define get_P1_ACDR2_reg                                              (*((volatile unsigned int*)P1_ACDR2_reg))
#define P1_ACDR2_reg_p1_acdr_8_shift                                  (24)
#define P1_ACDR2_reg_p1_acdr_7_shift                                  (16)
#define P1_ACDR2_reg_p1_acdr_6_shift                                  (8)
#define P1_ACDR2_reg_p1_acdr_5_shift                                  (0)
#define P1_ACDR2_reg_p1_acdr_8_mask                                   (0xFF000000)
#define P1_ACDR2_reg_p1_acdr_7_mask                                   (0x00FF0000)
#define P1_ACDR2_reg_p1_acdr_6_mask                                   (0x0000FF00)
#define P1_ACDR2_reg_p1_acdr_5_mask                                   (0x000000FF)
#define P1_ACDR2_reg_p1_acdr_8(data)                                  (0xFF000000&((data)<<24))
#define P1_ACDR2_reg_p1_acdr_7(data)                                  (0x00FF0000&((data)<<16))
#define P1_ACDR2_reg_p1_acdr_6(data)                                  (0x0000FF00&((data)<<8))
#define P1_ACDR2_reg_p1_acdr_5(data)                                  (0x000000FF&(data))
#define P1_ACDR2_get_reg_p1_acdr_8(data)                              ((0xFF000000&(data))>>24)
#define P1_ACDR2_get_reg_p1_acdr_7(data)                              ((0x00FF0000&(data))>>16)
#define P1_ACDR2_get_reg_p1_acdr_6(data)                              ((0x0000FF00&(data))>>8)
#define P1_ACDR2_get_reg_p1_acdr_5(data)                              (0x000000FF&(data))


#define P1_B1                                                         0xa64
#define P1_B1_reg_addr                                                "0x98034a64"
#define P1_B1_reg                                                     0x98034a64
#define P1_B1_inst_addr                                               "0x0299"
#define P1_B1_inst                                                    0x0299
#define set_P1_B1_reg(data)                                           (*((volatile unsigned int*)P1_B1_reg)=data)
#define get_P1_B1_reg                                                 (*((volatile unsigned int*)P1_B1_reg))
#define P1_B1_reg_p1_b_4_shift                                        (24)
#define P1_B1_reg_p1_b_3_shift                                        (16)
#define P1_B1_reg_p1_b_2_shift                                        (8)
#define P1_B1_reg_p1_b_1_shift                                        (0)
#define P1_B1_reg_p1_b_4_mask                                         (0xFF000000)
#define P1_B1_reg_p1_b_3_mask                                         (0x00FF0000)
#define P1_B1_reg_p1_b_2_mask                                         (0x0000FF00)
#define P1_B1_reg_p1_b_1_mask                                         (0x000000FF)
#define P1_B1_reg_p1_b_4(data)                                        (0xFF000000&((data)<<24))
#define P1_B1_reg_p1_b_3(data)                                        (0x00FF0000&((data)<<16))
#define P1_B1_reg_p1_b_2(data)                                        (0x0000FF00&((data)<<8))
#define P1_B1_reg_p1_b_1(data)                                        (0x000000FF&(data))
#define P1_B1_get_reg_p1_b_4(data)                                    ((0xFF000000&(data))>>24)
#define P1_B1_get_reg_p1_b_3(data)                                    ((0x00FF0000&(data))>>16)
#define P1_B1_get_reg_p1_b_2(data)                                    ((0x0000FF00&(data))>>8)
#define P1_B1_get_reg_p1_b_1(data)                                    (0x000000FF&(data))
#define P1_b_1_B_LANE_INPUT_OFF											(_BIT0)
#define P1_b_3_B_FORE_KOFF_RANGE										(_BIT22|_BIT21)
#define P1_b_1_FORE_KOFF_ADJR											(_BIT16|_BIT17|_BIT18|_BIT19|_BIT20)
#define P1_b_2_LEQ_BIT_RATE_mask										(_BIT8|_BIT9)
#define P1_b_2_LEQ_BIT_RATE_MBR											(_BIT8)
#define P1_b_2_LEQ_BIT_RATE_HBR											(_BIT9)


#define P1_B2                                                         0xa68
#define P1_B2_reg_addr                                                "0x98034a68"
#define P1_B2_reg                                                     0x98034a68
#define P1_B2_inst_addr                                               "0x029A"
#define P1_B2_inst                                                    0x029A
#define set_P1_B2_reg(data)                                           (*((volatile unsigned int*)P1_B2_reg)=data)
#define get_P1_B2_reg                                                 (*((volatile unsigned int*)P1_B2_reg))
#define P1_B2_reg_p1_b_8_shift                                        (24)
#define P1_B2_reg_p1_b_7_shift                                        (16)
#define P1_B2_reg_p1_b_6_shift                                        (8)
#define P1_B2_reg_p1_b_5_shift                                        (0)
#define P1_B2_reg_p1_b_8_mask                                         (0xFF000000)
#define P1_B2_reg_p1_b_7_mask                                         (0x00FF0000)
#define P1_B2_reg_p1_b_6_mask                                         (0x0000FF00)
#define P1_B2_reg_p1_b_5_mask                                         (0x000000FF)
#define P1_B2_reg_p1_b_8(data)                                        (0xFF000000&((data)<<24))
#define P1_B2_reg_p1_b_7(data)                                        (0x00FF0000&((data)<<16))
#define P1_B2_reg_p1_b_6(data)                                        (0x0000FF00&((data)<<8))
#define P1_B2_reg_p1_b_5(data)                                        (0x000000FF&(data))
#define P1_B2_get_reg_p1_b_8(data)                                    ((0xFF000000&(data))>>24)
#define P1_B2_get_reg_p1_b_7(data)                                    ((0x00FF0000&(data))>>16)
#define P1_B2_get_reg_p1_b_6(data)                                    ((0x0000FF00&(data))>>8)
#define P1_B2_get_reg_p1_b_5(data)                                    (0x000000FF&(data))
#define  DFE_HDMI_RX_PHY_P1_B2_reg_p1_b_8_PR_RATE_SEL_shift			(26)
#define  DFE_HDMI_RX_PHY_P1_B2_reg_p1_b_8_DEMUX_shift				(29)
#define  DFE_HDMI_RX_PHY_P1_B2_reg_p1_b_7_TAP0_ISEL_shift			(21)
#define  P1_b_8_DEMUX												(_BIT29|_BIT30|_BIT31)
#define  P1_b_8_PR_RATE_SEL											(_BIT26|_BIT27|_BIT28)
#define  P1_b_8_POW_PR												_BIT25
#define  P1_b_8_BY_PASS_PR											_BIT24
#define  P1_b_7_TAP0_ISEL											(_BIT21|_BIT22|_BIT23)
#define  P1_b_7_TAP0_ISEL_400uA										(_BIT22|_BIT23)
#define  P1_b_7_LEQ_ISEL											(_BIT18|_BIT19|_BIT20)
#define  P1_b_7_LEQ_ISEL_400uA										(_BIT19|_BIT20)
#define  P1_b_7_LEQ_ISEL_200uA										(_BIT20)
#define  P1_b_7_PI_ISEL												(_BIT16|_BIT17)
#define  P1_b_6_LEQ_BIT_RATE										(_BIT14|_BIT15)
#define  P1_b_6_LEQ_BIT_RATE_HBR									(_BIT15)
#define  P1_b_6_LEQ_BIT_RATE_MBR									(_BIT14)
#define  P1_b_6_TAP0_HBR											(_BIT13)
#define  P1_b_6_LEQ_PASSIVE_CORNER									( _BIT11|_BIT12)
#define  P1_b_5_TAP0_CURRENT_ADJ									(_BIT3|_BIT4)
#define  P1_b_5_TAP0_CURRENT_ADJ_1X									(_BIT3)
#define  P1_b_5_TAP0_CURRENT_ADJ_1p25X								(_BIT4)
#define  P1_b_5_EQ_POW												_BIT0


#define P1_B3                                                         0xa6c
#define P1_B3_reg_addr                                                "0x98034a6c"
#define P1_B3_reg                                                     0x98034a6c
#define P1_B3_inst_addr                                               "0x029B"
#define P1_B3_inst                                                    0x029B
#define set_P1_B3_reg(data)                                           (*((volatile unsigned int*)P1_B3_reg)=data)
#define get_P1_B3_reg                                                 (*((volatile unsigned int*)P1_B3_reg))
#define P1_B3_reg_p1_b_12_shift                                       (24)
#define P1_B3_reg_p1_b_11_shift                                       (16)
#define P1_B3_reg_p1_b_10_shift                                       (8)
#define P1_B3_reg_p1_b_9_shift                                        (0)
#define P1_B3_reg_p1_b_12_mask                                        (0xFF000000)
#define P1_B3_reg_p1_b_11_mask                                        (0x00FF0000)
#define P1_B3_reg_p1_b_10_mask                                        (0x0000FF00)
#define P1_B3_reg_p1_b_9_mask                                         (0x000000FF)
#define P1_B3_reg_p1_b_12(data)                                       (0xFF000000&((data)<<24))
#define P1_B3_reg_p1_b_11(data)                                       (0x00FF0000&((data)<<16))
#define P1_B3_reg_p1_b_10(data)                                       (0x0000FF00&((data)<<8))
#define P1_B3_reg_p1_b_9(data)                                        (0x000000FF&(data))
#define P1_B3_get_reg_p1_b_12(data)                                   ((0xFF000000&(data))>>24)
#define P1_B3_get_reg_p1_b_11(data)                                   ((0x00FF0000&(data))>>16)
#define P1_B3_get_reg_p1_b_10(data)                                   ((0x0000FF00&(data))>>8)
#define P1_B3_get_reg_p1_b_9(data)                                    (0x000000FF&(data))
#define P1_B_DFE_TAPEN4321											(_BIT6|_BIT5|_BIT4|_BIT3)
#define P1_b_12_PR													(_BIT24|_BIT25)
#define P1_b_11_ACDR_RATE_SEL_HALF_RATE								(_BIT16)
#define P1_b_9_DFE_ADAPTION_POW_EN									(_BIT7)
#define P1_b_9_DFE_TAP_EN											(_BIT3|_BIT4|_BIT5|_BIT6)
#define P1_b_9_DFE_TAP1_EN											(_BIT3)
#define DFE_HDMI_RX_PHY_P1_b_tap_en(data)							(0x00000078&((data)<<3))



#define P1_B4                                                         0xa70
#define P1_B4_reg_addr                                                "0x98034a70"
#define P1_B4_reg                                                     0x98034a70
#define P1_B4_inst_addr                                               "0x029C"
#define P1_B4_inst                                                    0x029C
#define set_P1_B4_reg(data)                                           (*((volatile unsigned int*)P1_B4_reg)=data)
#define get_P1_B4_reg                                                 (*((volatile unsigned int*)P1_B4_reg))
#define P1_B4_reg_p1_b_koff_sel_shift                                 (10)
#define P1_B4_reg_p1_b_koff_bound_shift                               (9)
#define P1_B4_reg_p1_b_koffok_shift                                   (8)
#define P1_B4_reg_p1_b_13_shift                                       (0)
#define P1_B4_reg_p1_b_koff_sel_mask                                  (0x00007C00)
#define P1_B4_reg_p1_b_koff_bound_mask                                (0x00000200)
#define P1_B4_reg_p1_b_koffok_mask                                    (0x00000100)
#define P1_B4_reg_p1_b_13_mask                                        (0x000000FF)
#define P1_B4_reg_p1_b_koff_sel(data)                                 (0x00007C00&((data)<<10))
#define P1_B4_reg_p1_b_koff_bound(data)                               (0x00000200&((data)<<9))
#define P1_B4_reg_p1_b_koffok(data)                                   (0x00000100&((data)<<8))
#define P1_B4_reg_p1_b_13(data)                                       (0x000000FF&(data))
#define P1_B4_get_reg_p1_b_koff_sel(data)                             ((0x00007C00&(data))>>10)
#define P1_B4_get_reg_p1_b_koff_bound(data)                           ((0x00000200&(data))>>9)
#define P1_B4_get_reg_p1_b_koffok(data)                               ((0x00000100&(data))>>8)
#define P1_B4_get_reg_p1_b_13(data)                                   (0x000000FF&(data))


#define P1_CK1                                                        0xa74
#define P1_CK1_reg_addr                                               "0x98034a74"
#define P1_CK1_reg                                                    0x98034a74
#define P1_CK1_inst_addr                                              "0x029D"
#define P1_CK1_inst                                                   0x029D
#define set_P1_CK1_reg(data)                                          (*((volatile unsigned int*)P1_CK1_reg)=data)
#define get_P1_CK1_reg                                                (*((volatile unsigned int*)P1_CK1_reg))
#define P1_CK1_reg_p1_ck_4_shift                                      (24)
#define P1_CK1_reg_p1_ck_3_shift                                      (16)
#define P1_CK1_reg_p1_ck_2_shift                                      (8)
#define P1_CK1_reg_p1_ck_1_shift                                      (0)
#define P1_CK1_reg_p1_ck_4_mask                                       (0xFF000000)
#define P1_CK1_reg_p1_ck_3_mask                                       (0x00FF0000)
#define P1_CK1_reg_p1_ck_2_mask                                       (0x0000FF00)
#define P1_CK1_reg_p1_ck_1_mask                                       (0x000000FF)
#define P1_CK1_reg_p1_ck_4(data)                                      (0xFF000000&((data)<<24))
#define P1_CK1_reg_p1_ck_3(data)                                      (0x00FF0000&((data)<<16))
#define P1_CK1_reg_p1_ck_2(data)                                      (0x0000FF00&((data)<<8))
#define P1_CK1_reg_p1_ck_1(data)                                      (0x000000FF&(data))
#define P1_CK1_get_reg_p1_ck_4(data)                                  ((0xFF000000&(data))>>24)
#define P1_CK1_get_reg_p1_ck_3(data)                                  ((0x00FF0000&(data))>>16)
#define P1_CK1_get_reg_p1_ck_2(data)                                  ((0x0000FF00&(data))>>8)
#define P1_CK1_get_reg_p1_ck_1(data)                                  (0x000000FF&(data))
#define p1_ck_3_CMU_PREDIVN												(_BIT20|_BIT21|_BIT22|_BIT23)
#define p1_ck_3_CMU_N_code												(_BIT18|_BIT19)
#define p1_ck_2_CMU_CKIN_SEL											(_BIT12|_BIT13|_BIT14|_BIT15)
#define p1_CMU_CKOUT_SEL												(_BIT11)
#define p1_ck_2_CK_MD_REF_SEL											(_BIT9)
#define p1_ck_1_port_bias												(_BIT2)
#define p1_ck_1_CKAFE_POW												(_BIT1)


#define P1_CK2                                                        0xa78
#define P1_CK2_reg_addr                                               "0x98034a78"
#define P1_CK2_reg                                                    0x98034a78
#define P1_CK2_inst_addr                                              "0x029E"
#define P1_CK2_inst                                                   0x029E
#define set_P1_CK2_reg(data)                                          (*((volatile unsigned int*)P1_CK2_reg)=data)
#define get_P1_CK2_reg                                                (*((volatile unsigned int*)P1_CK2_reg))
#define P1_CK2_reg_p1_ck_8_shift                                      (24)
#define P1_CK2_reg_p1_ck_7_shift                                      (16)
#define P1_CK2_reg_p1_ck_6_shift                                      (8)
#define P1_CK2_reg_p1_ck_5_shift                                      (0)
#define P1_CK2_reg_p1_ck_8_mask                                       (0xFF000000)
#define P1_CK2_reg_p1_ck_7_mask                                       (0x00FF0000)
#define P1_CK2_reg_p1_ck_6_mask                                       (0x0000FF00)
#define P1_CK2_reg_p1_ck_5_mask                                       (0x000000FF)
#define P1_CK2_reg_p1_ck_8(data)                                      (0xFF000000&((data)<<24))
#define P1_CK2_reg_p1_ck_7(data)                                      (0x00FF0000&((data)<<16))
#define P1_CK2_reg_p1_ck_6(data)                                      (0x0000FF00&((data)<<8))
#define P1_CK2_reg_p1_ck_5(data)                                      (0x000000FF&(data))
#define P1_CK2_get_reg_p1_ck_8(data)                                  ((0xFF000000&(data))>>24)
#define P1_CK2_get_reg_p1_ck_7(data)                                  ((0x00FF0000&(data))>>16)
#define P1_CK2_get_reg_p1_ck_6(data)                                  ((0x0000FF00&(data))>>8)
#define P1_CK2_get_reg_p1_ck_5(data)                                  (0x000000FF&(data))
#define P1_ck_8_VSEL_LDO_A_mask										(_BIT29|_BIT30|_BIT31)
#define P1_ck_8_VSEL_LDO_D_mask										(_BIT26|_BIT27|_BIT28)
#define P1_ck_8_LDO_EN_mask											(_BIT25)
#define P1_ck_8_CMU_BPPSR_mask										(_BIT24)
#define P1_ck_7_CMU_BYPASS_PI_mask									(_BIT19)
#define P1_ck_7_CMU_PI_I_SEL_mask									(_BIT16|_BIT17|_BIT18)
#define P1_ck_6_CMU_BIG_KVCO_mask									(_BIT13)
#define P1_ck_6_CMU_EN_CAP_mask										(_BIT12)
#define P1_ck_6_CMU_SEL_CS_mask										(_BIT8|_BIT9|_BIT10)
#define P1_ck_5_CMU_SEL_PUMP_I_mask									(_BIT4|_BIT5|_BIT6|_BIT7)
#define P1_ck_5_CMU_SEL_R1_mask										(_BIT0|_BIT1|_BIT2)
#define DFE_HDMI_RX_PHY_P1_VSEL_LDO_D(data)							(0x1C000000&((data)<<26))
#define DFE_HDMI_RX_PHY_P1_CMU_BPPSR(data)							(0x01000000&((data)<<24))
#define DFE_HDMI_RX_PHY_P1_CMU_SEL_CS(data)							(0x00000700&((data)<<8))
#define DFE_HDMI_RX_PHY_P1_CMU_SEL_PUMP_I(data)						(0x000000F0&((data)<<4))
#define DFE_HDMI_RX_PHY_P1_CMU_SEL_R1(data)							(0x00000007&((data)<<0))


#define P1_CK3                                                        0xa7c
#define P1_CK3_reg_addr                                               "0x98034a7c"
#define P1_CK3_reg                                                    0x98034a7c
#define P1_CK3_inst_addr                                              "0x029F"
#define P1_CK3_inst                                                   0x029F
#define set_P1_CK3_reg(data)                                          (*((volatile unsigned int*)P1_CK3_reg)=data)
#define get_P1_CK3_reg                                                (*((volatile unsigned int*)P1_CK3_reg))
#define P1_CK3_reg_p1_ck_12_shift                                     (24)
#define P1_CK3_reg_p1_ck_11_shift                                     (16)
#define P1_CK3_reg_p1_ck_10_shift                                     (8)
#define P1_CK3_reg_p1_ck_9_shift                                      (0)
#define P1_CK3_reg_p1_ck_12_mask                                      (0xFF000000)
#define P1_CK3_reg_p1_ck_11_mask                                      (0x00FF0000)
#define P1_CK3_reg_p1_ck_10_mask                                      (0x0000FF00)
#define P1_CK3_reg_p1_ck_9_mask                                       (0x000000FF)
#define P1_CK3_reg_p1_ck_12(data)                                     (0xFF000000&((data)<<24))
#define P1_CK3_reg_p1_ck_11(data)                                     (0x00FF0000&((data)<<16))
#define P1_CK3_reg_p1_ck_10(data)                                     (0x0000FF00&((data)<<8))
#define P1_CK3_reg_p1_ck_9(data)                                      (0x000000FF&(data))
#define P1_CK3_get_reg_p1_ck_12(data)                                 ((0xFF000000&(data))>>24)
#define P1_CK3_get_reg_p1_ck_11(data)                                 ((0x00FF0000&(data))>>16)
#define P1_CK3_get_reg_p1_ck_10(data)                                 ((0x0000FF00&(data))>>8)
#define P1_CK3_get_reg_p1_ck_9(data)                                  (0x000000FF&(data))
#define P1_ck_9_CMU_PFD_RSTB										(_BIT5)
#define P1_ck_9_CMU_WDRST											(_BIT2)


#define P1_CK4                                                        0xa80
#define P1_CK4_reg_addr                                               "0x98034a80"
#define P1_CK4_reg                                                    0x98034a80
#define P1_CK4_inst_addr                                              "0x02A0"
#define P1_CK4_inst                                                   0x02A0
#define set_P1_CK4_reg(data)                                          (*((volatile unsigned int*)P1_CK4_reg)=data)
#define get_P1_CK4_reg                                                (*((volatile unsigned int*)P1_CK4_reg))
#define P1_CK4_reg_p1_ck_13_shift                                     (0)
#define P1_CK4_reg_p1_ck_13_mask                                      (0x000000FF)
#define P1_CK4_reg_p1_ck_13(data)                                     (0x000000FF&(data))
#define P1_CK4_get_reg_p1_ck_13(data)                                 (0x000000FF&(data))


#define P1_G1                                                         0xa84
#define P1_G1_reg_addr                                                "0x98034a84"
#define P1_G1_reg                                                     0x98034a84
#define P1_G1_inst_addr                                               "0x02A1"
#define P1_G1_inst                                                    0x02A1
#define set_P1_G1_reg(data)                                           (*((volatile unsigned int*)P1_G1_reg)=data)
#define get_P1_G1_reg                                                 (*((volatile unsigned int*)P1_G1_reg))
#define P1_G1_reg_p1_g_4_shift                                        (24)
#define P1_G1_reg_p1_g_3_shift                                        (16)
#define P1_G1_reg_p1_g_2_shift                                        (8)
#define P1_G1_reg_p1_g_1_shift                                        (0)
#define P1_G1_reg_p1_g_4_mask                                         (0xFF000000)
#define P1_G1_reg_p1_g_3_mask                                         (0x00FF0000)
#define P1_G1_reg_p1_g_2_mask                                         (0x0000FF00)
#define P1_G1_reg_p1_g_1_mask                                         (0x000000FF)
#define P1_G1_reg_p1_g_4(data)                                        (0xFF000000&((data)<<24))
#define P1_G1_reg_p1_g_3(data)                                        (0x00FF0000&((data)<<16))
#define P1_G1_reg_p1_g_2(data)                                        (0x0000FF00&((data)<<8))
#define P1_G1_reg_p1_g_1(data)                                        (0x000000FF&(data))
#define P1_G1_get_reg_p1_g_4(data)                                    ((0xFF000000&(data))>>24)
#define P1_G1_get_reg_p1_g_3(data)                                    ((0x00FF0000&(data))>>16)
#define P1_G1_get_reg_p1_g_2(data)                                    ((0x0000FF00&(data))>>8)
#define P1_G1_get_reg_p1_g_1(data)                                    (0x000000FF&(data))
#define P1_g_1_G_LANE_INPUT_OFF										(_BIT0)
#define P1_g_2_LEQ_BIT_RATE_mask									(_BIT8|_BIT9)
#define P1_g_2_LEQ_BIT_RATE_MBR										(_BIT8)
#define P1_g_2_LEQ_BIT_RATE_HBR										(_BIT9)


#define P1_G2                                                         0xa88
#define P1_G2_reg_addr                                                "0x98034a88"
#define P1_G2_reg                                                     0x98034a88
#define P1_G2_inst_addr                                               "0x02A2"
#define P1_G2_inst                                                    0x02A2
#define set_P1_G2_reg(data)                                           (*((volatile unsigned int*)P1_G2_reg)=data)
#define get_P1_G2_reg                                                 (*((volatile unsigned int*)P1_G2_reg))
#define P1_G2_reg_p1_g_8_shift                                        (24)
#define P1_G2_reg_p1_g_7_shift                                        (16)
#define P1_G2_reg_p1_g_6_shift                                        (8)
#define P1_G2_reg_p1_g_5_shift                                        (0)
#define P1_G2_reg_p1_g_8_mask                                         (0xFF000000)
#define P1_G2_reg_p1_g_7_mask                                         (0x00FF0000)
#define P1_G2_reg_p1_g_6_mask                                         (0x0000FF00)
#define P1_G2_reg_p1_g_5_mask                                         (0x000000FF)
#define P1_G2_reg_p1_g_8(data)                                        (0xFF000000&((data)<<24))
#define P1_G2_reg_p1_g_7(data)                                        (0x00FF0000&((data)<<16))
#define P1_G2_reg_p1_g_6(data)                                        (0x0000FF00&((data)<<8))
#define P1_G2_reg_p1_g_5(data)                                        (0x000000FF&(data))
#define P1_G2_get_reg_p1_g_8(data)                                    ((0xFF000000&(data))>>24)
#define P1_G2_get_reg_p1_g_7(data)                                    ((0x00FF0000&(data))>>16)
#define P1_G2_get_reg_p1_g_6(data)                                    ((0x0000FF00&(data))>>8)
#define P1_G2_get_reg_p1_g_5(data)                                    (0x000000FF&(data))
#define DFE_HDMI_RX_PHY_P1_G2_reg_p1_g_8_PR_RATE_SEL_shift			(26)
#define DFE_HDMI_RX_PHY_P1_G2_reg_p1_g_8_DEMUX_shift				(29)
#define DFE_HDMI_RX_PHY_P1_G2_reg_p1_g_7_TAP0_ISEL_shift			(21)
#define P1_g_8_DEMUX												(_BIT29|_BIT30|_BIT31)
#define P1_g_8_PR_RATE_SEL											(_BIT26|_BIT27|_BIT28)
#define P1_g_8_POW_PR												_BIT25
#define P1_g_8_BY_PASS_PR											_BIT24
#define P1_g_7_TAP0_ISEL											(_BIT21|_BIT22|_BIT23)
#define P1_g_7_TAP0_ISEL_400uA										(_BIT22|_BIT23)
#define P1_g_7_LEQ_ISEL												(_BIT18|_BIT19|_BIT20)
#define P1_g_7_LEQ_ISEL_400uA										(_BIT19|_BIT20)
#define P1_g_7_PI_ISEL												(_BIT16|_BIT17)
#define P1_g_6_LEQ_BIT_RATE											(_BIT14|_BIT15)
#define P1_g_6_LEQ_BIT_RATE_HBR										(_BIT15)
#define P1_g_6_LEQ_BIT_RATE_MBR										(_BIT14)
#define P1_g_6_TAP0_HBR												(_BIT13)
#define P1_g_6_LEQ_PASSIVE_CORNER									(_BIT11|_BIT12)
#define P1_g_5_TAP0_CURRENT_ADJ										(_BIT3|_BIT4)
#define P1_g_5_TAP0_CURRENT_ADJ_1X									(_BIT3)
#define P1_g_5_TAP0_CURRENT_ADJ_1p25X								(_BIT4)
#define P1_g_5_EQ_POW												_BIT0


#define P1_G3                                                         0xa8c
#define P1_G3_reg_addr                                                "0x98034a8c"
#define P1_G3_reg                                                     0x98034a8c
#define P1_G3_inst_addr                                               "0x02A3"
#define P1_G3_inst                                                    0x02A3
#define set_P1_G3_reg(data)                                           (*((volatile unsigned int*)P1_G3_reg)=data)
#define get_P1_G3_reg                                                 (*((volatile unsigned int*)P1_G3_reg))
#define P1_G3_reg_p1_g_12_shift                                       (24)
#define P1_G3_reg_p1_g_11_shift                                       (16)
#define P1_G3_reg_p1_g_10_shift                                       (8)
#define P1_G3_reg_p1_g_9_shift                                        (0)
#define P1_G3_reg_p1_g_12_mask                                        (0xFF000000)
#define P1_G3_reg_p1_g_11_mask                                        (0x00FF0000)
#define P1_G3_reg_p1_g_10_mask                                        (0x0000FF00)
#define P1_G3_reg_p1_g_9_mask                                         (0x000000FF)
#define P1_G3_reg_p1_g_12(data)                                       (0xFF000000&((data)<<24))
#define P1_G3_reg_p1_g_11(data)                                       (0x00FF0000&((data)<<16))
#define P1_G3_reg_p1_g_10(data)                                       (0x0000FF00&((data)<<8))
#define P1_G3_reg_p1_g_9(data)                                        (0x000000FF&(data))
#define P1_G3_get_reg_p1_g_12(data)                                   ((0xFF000000&(data))>>24)
#define P1_G3_get_reg_p1_g_11(data)                                   ((0x00FF0000&(data))>>16)
#define P1_G3_get_reg_p1_g_10(data)                                   ((0x0000FF00&(data))>>8)
#define P1_G3_get_reg_p1_g_9(data)                                    (0x000000FF&(data))


#define P1_G4                                                         0xa90
#define P1_G4_reg_addr                                                "0x98034a90"
#define P1_G4_reg                                                     0x98034a90
#define P1_G4_inst_addr                                               "0x02A4"
#define P1_G4_inst                                                    0x02A4
#define set_P1_G4_reg(data)                                           (*((volatile unsigned int*)P1_G4_reg)=data)
#define get_P1_G4_reg                                                 (*((volatile unsigned int*)P1_G4_reg))
#define P1_G4_reg_p1_g_koff_sel_shift                                 (10)
#define P1_G4_reg_p1_g_koff_bound_shift                               (9)
#define P1_G4_reg_p1_g_koffok_shift                                   (8)
#define P1_G4_reg_p1_g_13_shift                                       (0)
#define P1_G4_reg_p1_g_koff_sel_mask                                  (0x00007C00)
#define P1_G4_reg_p1_g_koff_bound_mask                                (0x00000200)
#define P1_G4_reg_p1_g_koffok_mask                                    (0x00000100)
#define P1_G4_reg_p1_g_13_mask                                        (0x000000FF)
#define P1_G4_reg_p1_g_koff_sel(data)                                 (0x00007C00&((data)<<10))
#define P1_G4_reg_p1_g_koff_bound(data)                               (0x00000200&((data)<<9))
#define P1_G4_reg_p1_g_koffok(data)                                   (0x00000100&((data)<<8))
#define P1_G4_reg_p1_g_13(data)                                       (0x000000FF&(data))
#define P1_G4_get_reg_p1_g_koff_sel(data)                             ((0x00007C00&(data))>>10)
#define P1_G4_get_reg_p1_g_koff_bound(data)                           ((0x00000200&(data))>>9)
#define P1_G4_get_reg_p1_g_koffok(data)                               ((0x00000100&(data))>>8)
#define P1_G4_get_reg_p1_g_13(data)                                   (0x000000FF&(data))


#define P1_R1                                                         0xa94
#define P1_R1_reg_addr                                                "0x98034a94"
#define P1_R1_reg                                                     0x98034a94
#define P1_R1_inst_addr                                               "0x02A5"
#define P1_R1_inst                                                    0x02A5
#define set_P1_R1_reg(data)                                           (*((volatile unsigned int*)P1_R1_reg)=data)
#define get_P1_R1_reg                                                 (*((volatile unsigned int*)P1_R1_reg))
#define P1_R1_reg_p1_r_4_shift                                        (24)
#define P1_R1_reg_p1_r_3_shift                                        (16)
#define P1_R1_reg_p1_r_2_shift                                        (8)
#define P1_R1_reg_p1_r_1_shift                                        (0)
#define P1_R1_reg_p1_r_4_mask                                         (0xFF000000)
#define P1_R1_reg_p1_r_3_mask                                         (0x00FF0000)
#define P1_R1_reg_p1_r_2_mask                                         (0x0000FF00)
#define P1_R1_reg_p1_r_1_mask                                         (0x000000FF)
#define P1_R1_reg_p1_r_4(data)                                        (0xFF000000&((data)<<24))
#define P1_R1_reg_p1_r_3(data)                                        (0x00FF0000&((data)<<16))
#define P1_R1_reg_p1_r_2(data)                                        (0x0000FF00&((data)<<8))
#define P1_R1_reg_p1_r_1(data)                                        (0x000000FF&(data))
#define P1_R1_get_reg_p1_r_4(data)                                    ((0xFF000000&(data))>>24)
#define P1_R1_get_reg_p1_r_3(data)                                    ((0x00FF0000&(data))>>16)
#define P1_R1_get_reg_p1_r_2(data)                                    ((0x0000FF00&(data))>>8)
#define P1_R1_get_reg_p1_r_1(data)                                    (0x000000FF&(data))
#define P1_r_1_R_LANE_INPUT_OFF										(_BIT0)
#define P1_r_2_LEQ_BIT_RATE_mask									(_BIT8|_BIT9)
#define P1_r_2_LEQ_BIT_RATE_MBR										(_BIT8)
#define P1_r_2_LEQ_BIT_RATE_HBR										(_BIT9)


#define P1_R2                                                         0xa98
#define P1_R2_reg_addr                                                "0x98034a98"
#define P1_R2_reg                                                     0x98034a98
#define P1_R2_inst_addr                                               "0x02A6"
#define P1_R2_inst                                                    0x02A6
#define set_P1_R2_reg(data)                                           (*((volatile unsigned int*)P1_R2_reg)=data)
#define get_P1_R2_reg                                                 (*((volatile unsigned int*)P1_R2_reg))
#define P1_R2_reg_p1_r_8_shift                                        (24)
#define P1_R2_reg_p1_r_7_shift                                        (16)
#define P1_R2_reg_p1_r_6_shift                                        (8)
#define P1_R2_reg_p1_r_5_shift                                        (0)
#define P1_R2_reg_p1_r_8_mask                                         (0xFF000000)
#define P1_R2_reg_p1_r_7_mask                                         (0x00FF0000)
#define P1_R2_reg_p1_r_6_mask                                         (0x0000FF00)
#define P1_R2_reg_p1_r_5_mask                                         (0x000000FF)
#define P1_R2_reg_p1_r_8(data)                                        (0xFF000000&((data)<<24))
#define P1_R2_reg_p1_r_7(data)                                        (0x00FF0000&((data)<<16))
#define P1_R2_reg_p1_r_6(data)                                        (0x0000FF00&((data)<<8))
#define P1_R2_reg_p1_r_5(data)                                        (0x000000FF&(data))
#define P1_R2_get_reg_p1_r_8(data)                                    ((0xFF000000&(data))>>24)
#define P1_R2_get_reg_p1_r_7(data)                                    ((0x00FF0000&(data))>>16)
#define P1_R2_get_reg_p1_r_6(data)                                    ((0x0000FF00&(data))>>8)
#define P1_R2_get_reg_p1_r_5(data)                                    (0x000000FF&(data))
#define DFE_HDMI_RX_PHY_P1_R2_reg_p0_r_8_PR_RATE_SEL_shift			(26)
#define DFE_HDMI_RX_PHY_P1_R2_reg_p0_r_8_DEMUX_shift				(29)
#define DFE_HDMI_RX_PHY_P1_R2_reg_p0_r_7_TAP0_ISEL_shift			(21)
#define P1_r_8_DEMUX												(_BIT29|_BIT30|_BIT31)
#define P1_r_8_PR_RATE_SEL											(_BIT26|_BIT27|_BIT28)
#define P1_r_8_POW_PR												_BIT25
#define P1_r_8_BY_PASS_PR											_BIT24
#define P1_r_7_TAP0_ISEL											(_BIT21|_BIT22|_BIT23)
#define P1_r_7_TAP0_ISEL_400uA										(_BIT22|_BIT23)
#define P1_r_7_LEQ_ISEL												(_BIT18|_BIT19|_BIT20)
#define P1_r_7_LEQ_ISEL_400uA										(_BIT19|_BIT20)
#define P1_r_7_PI_ISEL												(_BIT16|_BIT17)
#define P1_r_6_LEQ_BIT_RATE											(_BIT14|_BIT15)
#define P1_r_6_LEQ_BIT_RATE_HBR										(_BIT15)
#define P1_r_6_LEQ_BIT_RATE_MBR										(_BIT14)
#define P1_r_6_TAP0_HBR												(_BIT13)
#define P1_r_6_LEQ_PASSIVE_CORNER									(_BIT12|_BIT11)
#define P1_r_5_TAP0_CURRENT_ADJ										(_BIT3|_BIT4)
#define P1_r_5_TAP0_CURRENT_ADJ_1X									(_BIT3)
#define P1_r_5_TAP0_CURRENT_ADJ_1p25X								(_BIT4)
#define P1_r_5_EQ_POW												_BIT0


#define P1_R3                                                         0xa9c
#define P1_R3_reg_addr                                                "0x98034a9c"
#define P1_R3_reg                                                     0x98034a9c
#define P1_R3_inst_addr                                               "0x02A7"
#define P1_R3_inst                                                    0x02A7
#define set_P1_R3_reg(data)                                           (*((volatile unsigned int*)P1_R3_reg)=data)
#define get_P1_R3_reg                                                 (*((volatile unsigned int*)P1_R3_reg))
#define P1_R3_reg_p1_r_12_shift                                       (24)
#define P1_R3_reg_p1_r_11_shift                                       (16)
#define P1_R3_reg_p1_r_10_shift                                       (8)
#define P1_R3_reg_p1_r_9_shift                                        (0)
#define P1_R3_reg_p1_r_12_mask                                        (0xFF000000)
#define P1_R3_reg_p1_r_11_mask                                        (0x00FF0000)
#define P1_R3_reg_p1_r_10_mask                                        (0x0000FF00)
#define P1_R3_reg_p1_r_9_mask                                         (0x000000FF)
#define P1_R3_reg_p1_r_12(data)                                       (0xFF000000&((data)<<24))
#define P1_R3_reg_p1_r_11(data)                                       (0x00FF0000&((data)<<16))
#define P1_R3_reg_p1_r_10(data)                                       (0x0000FF00&((data)<<8))
#define P1_R3_reg_p1_r_9(data)                                        (0x000000FF&(data))
#define P1_R3_get_reg_p1_r_12(data)                                   ((0xFF000000&(data))>>24)
#define P1_R3_get_reg_p1_r_11(data)                                   ((0x00FF0000&(data))>>16)
#define P1_R3_get_reg_p1_r_10(data)                                   ((0x0000FF00&(data))>>8)
#define P1_R3_get_reg_p1_r_9(data)                                    (0x000000FF&(data))


#define P1_R4                                                         0xaa0
#define P1_R4_reg_addr                                                "0x98034aa0"
#define P1_R4_reg                                                     0x98034aa0
#define P1_R4_inst_addr                                               "0x02A8"
#define P1_R4_inst                                                    0x02A8
#define set_P1_R4_reg(data)                                           (*((volatile unsigned int*)P1_R4_reg)=data)
#define get_P1_R4_reg                                                 (*((volatile unsigned int*)P1_R4_reg))
#define P1_R4_reg_p1_r_koff_sel_shift                                 (10)
#define P1_R4_reg_p1_r_koff_bound_shift                               (9)
#define P1_R4_reg_p1_r_koffok_shift                                   (8)
#define P1_R4_reg_p1_r_13_shift                                       (0)
#define P1_R4_reg_p1_r_koff_sel_mask                                  (0x00007C00)
#define P1_R4_reg_p1_r_koff_bound_mask                                (0x00000200)
#define P1_R4_reg_p1_r_koffok_mask                                    (0x00000100)
#define P1_R4_reg_p1_r_13_mask                                        (0x000000FF)
#define P1_R4_reg_p1_r_koff_sel(data)                                 (0x00007C00&((data)<<10))
#define P1_R4_reg_p1_r_koff_bound(data)                               (0x00000200&((data)<<9))
#define P1_R4_reg_p1_r_koffok(data)                                   (0x00000100&((data)<<8))
#define P1_R4_reg_p1_r_13(data)                                       (0x000000FF&(data))
#define P1_R4_get_reg_p1_r_koff_sel(data)                             ((0x00007C00&(data))>>10)
#define P1_R4_get_reg_p1_r_koff_bound(data)                           ((0x00000200&(data))>>9)
#define P1_R4_get_reg_p1_r_koffok(data)                               ((0x00000100&(data))>>8)
#define P1_R4_get_reg_p1_r_13(data)                                   (0x000000FF&(data))


#define P2_ACDR1                                                      0xaa4
#define P2_ACDR1_reg_addr                                             "0x98034aa4"
#define P2_ACDR1_reg                                                  0x98034aa4
#define P2_ACDR1_inst_addr                                            "0x02A9"
#define P2_ACDR1_inst                                                 0x02A9
#define set_P2_ACDR1_reg(data)                                        (*((volatile unsigned int*)P2_ACDR1_reg)=data)
#define get_P2_ACDR1_reg                                              (*((volatile unsigned int*)P2_ACDR1_reg))
#define P2_ACDR1_reg_p2_acdr_4_shift                                  (24)
#define P2_ACDR1_reg_p2_acdr_3_shift                                  (16)
#define P2_ACDR1_reg_p2_acdr_2_shift                                  (8)
#define P2_ACDR1_reg_p2_acdr_1_shift                                  (0)
#define P2_ACDR1_reg_p2_acdr_4_mask                                   (0xFF000000)
#define P2_ACDR1_reg_p2_acdr_3_mask                                   (0x00FF0000)
#define P2_ACDR1_reg_p2_acdr_2_mask                                   (0x0000FF00)
#define P2_ACDR1_reg_p2_acdr_1_mask                                   (0x000000FF)
#define P2_ACDR1_reg_p2_acdr_4(data)                                  (0xFF000000&((data)<<24))
#define P2_ACDR1_reg_p2_acdr_3(data)                                  (0x00FF0000&((data)<<16))
#define P2_ACDR1_reg_p2_acdr_2(data)                                  (0x0000FF00&((data)<<8))
#define P2_ACDR1_reg_p2_acdr_1(data)                                  (0x000000FF&(data))
#define P2_ACDR1_get_reg_p2_acdr_4(data)                              ((0xFF000000&(data))>>24)
#define P2_ACDR1_get_reg_p2_acdr_3(data)                              ((0x00FF0000&(data))>>16)
#define P2_ACDR1_get_reg_p2_acdr_2(data)                              ((0x0000FF00&(data))>>8)
#define P2_ACDR1_get_reg_p2_acdr_1(data)                              (0x000000FF&(data))


#define P2_ACDR2                                                      0xaa8
#define P2_ACDR2_reg_addr                                             "0x98034aa8"
#define P2_ACDR2_reg                                                  0x98034aa8
#define P2_ACDR2_inst_addr                                            "0x02AA"
#define P2_ACDR2_inst                                                 0x02AA
#define set_P2_ACDR2_reg(data)                                        (*((volatile unsigned int*)P2_ACDR2_reg)=data)
#define get_P2_ACDR2_reg                                              (*((volatile unsigned int*)P2_ACDR2_reg))
#define P2_ACDR2_reg_p2_acdr_8_shift                                  (24)
#define P2_ACDR2_reg_p2_acdr_7_shift                                  (16)
#define P2_ACDR2_reg_p2_acdr_6_shift                                  (8)
#define P2_ACDR2_reg_p2_acdr_5_shift                                  (0)
#define P2_ACDR2_reg_p2_acdr_8_mask                                   (0xFF000000)
#define P2_ACDR2_reg_p2_acdr_7_mask                                   (0x00FF0000)
#define P2_ACDR2_reg_p2_acdr_6_mask                                   (0x0000FF00)
#define P2_ACDR2_reg_p2_acdr_5_mask                                   (0x000000FF)
#define P2_ACDR2_reg_p2_acdr_8(data)                                  (0xFF000000&((data)<<24))
#define P2_ACDR2_reg_p2_acdr_7(data)                                  (0x00FF0000&((data)<<16))
#define P2_ACDR2_reg_p2_acdr_6(data)                                  (0x0000FF00&((data)<<8))
#define P2_ACDR2_reg_p2_acdr_5(data)                                  (0x000000FF&(data))
#define P2_ACDR2_get_reg_p2_acdr_8(data)                              ((0xFF000000&(data))>>24)
#define P2_ACDR2_get_reg_p2_acdr_7(data)                              ((0x00FF0000&(data))>>16)
#define P2_ACDR2_get_reg_p2_acdr_6(data)                              ((0x0000FF00&(data))>>8)
#define P2_ACDR2_get_reg_p2_acdr_5(data)                              (0x000000FF&(data))


#define P2_B1                                                         0xaac
#define P2_B1_reg_addr                                                "0x98034aac"
#define P2_B1_reg                                                     0x98034aac
#define P2_B1_inst_addr                                               "0x02AB"
#define P2_B1_inst                                                    0x02AB
#define set_P2_B1_reg(data)                                           (*((volatile unsigned int*)P2_B1_reg)=data)
#define get_P2_B1_reg                                                 (*((volatile unsigned int*)P2_B1_reg))
#define P2_B1_reg_p2_b_4_shift                                        (24)
#define P2_B1_reg_p2_b_3_shift                                        (16)
#define P2_B1_reg_p2_b_2_shift                                        (8)
#define P2_B1_reg_p2_b_1_shift                                        (0)
#define P2_B1_reg_p2_b_4_mask                                         (0xFF000000)
#define P2_B1_reg_p2_b_3_mask                                         (0x00FF0000)
#define P2_B1_reg_p2_b_2_mask                                         (0x0000FF00)
#define P2_B1_reg_p2_b_1_mask                                         (0x000000FF)
#define P2_B1_reg_p2_b_4(data)                                        (0xFF000000&((data)<<24))
#define P2_B1_reg_p2_b_3(data)                                        (0x00FF0000&((data)<<16))
#define P2_B1_reg_p2_b_2(data)                                        (0x0000FF00&((data)<<8))
#define P2_B1_reg_p2_b_1(data)                                        (0x000000FF&(data))
#define P2_B1_get_reg_p2_b_4(data)                                    ((0xFF000000&(data))>>24)
#define P2_B1_get_reg_p2_b_3(data)                                    ((0x00FF0000&(data))>>16)
#define P2_B1_get_reg_p2_b_2(data)                                    ((0x0000FF00&(data))>>8)
#define P2_B1_get_reg_p2_b_1(data)                                    (0x000000FF&(data))


#define P2_B2                                                         0xab0
#define P2_B2_reg_addr                                                "0x98034ab0"
#define P2_B2_reg                                                     0x98034ab0
#define P2_B2_inst_addr                                               "0x02AC"
#define P2_B2_inst                                                    0x02AC
#define set_P2_B2_reg(data)                                           (*((volatile unsigned int*)P2_B2_reg)=data)
#define get_P2_B2_reg                                                 (*((volatile unsigned int*)P2_B2_reg))
#define P2_B2_reg_p2_b_8_shift                                        (24)
#define P2_B2_reg_p2_b_7_shift                                        (16)
#define P2_B2_reg_p2_b_6_shift                                        (8)
#define P2_B2_reg_p2_b_5_shift                                        (0)
#define P2_B2_reg_p2_b_8_mask                                         (0xFF000000)
#define P2_B2_reg_p2_b_7_mask                                         (0x00FF0000)
#define P2_B2_reg_p2_b_6_mask                                         (0x0000FF00)
#define P2_B2_reg_p2_b_5_mask                                         (0x000000FF)
#define P2_B2_reg_p2_b_8(data)                                        (0xFF000000&((data)<<24))
#define P2_B2_reg_p2_b_7(data)                                        (0x00FF0000&((data)<<16))
#define P2_B2_reg_p2_b_6(data)                                        (0x0000FF00&((data)<<8))
#define P2_B2_reg_p2_b_5(data)                                        (0x000000FF&(data))
#define P2_B2_get_reg_p2_b_8(data)                                    ((0xFF000000&(data))>>24)
#define P2_B2_get_reg_p2_b_7(data)                                    ((0x00FF0000&(data))>>16)
#define P2_B2_get_reg_p2_b_6(data)                                    ((0x0000FF00&(data))>>8)
#define P2_B2_get_reg_p2_b_5(data)                                    (0x000000FF&(data))


#define P2_B3                                                         0xab4
#define P2_B3_reg_addr                                                "0x98034ab4"
#define P2_B3_reg                                                     0x98034ab4
#define P2_B3_inst_addr                                               "0x02AD"
#define P2_B3_inst                                                    0x02AD
#define set_P2_B3_reg(data)                                           (*((volatile unsigned int*)P2_B3_reg)=data)
#define get_P2_B3_reg                                                 (*((volatile unsigned int*)P2_B3_reg))
#define P2_B3_reg_p2_b_12_shift                                       (24)
#define P2_B3_reg_p2_b_11_shift                                       (16)
#define P2_B3_reg_p2_b_10_shift                                       (8)
#define P2_B3_reg_p2_b_9_shift                                        (0)
#define P2_B3_reg_p2_b_12_mask                                        (0xFF000000)
#define P2_B3_reg_p2_b_11_mask                                        (0x00FF0000)
#define P2_B3_reg_p2_b_10_mask                                        (0x0000FF00)
#define P2_B3_reg_p2_b_9_mask                                         (0x000000FF)
#define P2_B3_reg_p2_b_12(data)                                       (0xFF000000&((data)<<24))
#define P2_B3_reg_p2_b_11(data)                                       (0x00FF0000&((data)<<16))
#define P2_B3_reg_p2_b_10(data)                                       (0x0000FF00&((data)<<8))
#define P2_B3_reg_p2_b_9(data)                                        (0x000000FF&(data))
#define P2_B3_get_reg_p2_b_12(data)                                   ((0xFF000000&(data))>>24)
#define P2_B3_get_reg_p2_b_11(data)                                   ((0x00FF0000&(data))>>16)
#define P2_B3_get_reg_p2_b_10(data)                                   ((0x0000FF00&(data))>>8)
#define P2_B3_get_reg_p2_b_9(data)                                    (0x000000FF&(data))


#define P2_B4                                                         0xab8
#define P2_B4_reg_addr                                                "0x98034ab8"
#define P2_B4_reg                                                     0x98034ab8
#define P2_B4_inst_addr                                               "0x02AE"
#define P2_B4_inst                                                    0x02AE
#define set_P2_B4_reg(data)                                           (*((volatile unsigned int*)P2_B4_reg)=data)
#define get_P2_B4_reg                                                 (*((volatile unsigned int*)P2_B4_reg))
#define P2_B4_reg_p2_b_koff_sel_shift                                 (10)
#define P2_B4_reg_p2_b_koff_bound_shift                               (9)
#define P2_B4_reg_p2_b_koffok_shift                                   (8)
#define P2_B4_reg_p2_b_13_shift                                       (0)
#define P2_B4_reg_p2_b_koff_sel_mask                                  (0x00007C00)
#define P2_B4_reg_p2_b_koff_bound_mask                                (0x00000200)
#define P2_B4_reg_p2_b_koffok_mask                                    (0x00000100)
#define P2_B4_reg_p2_b_13_mask                                        (0x000000FF)
#define P2_B4_reg_p2_b_koff_sel(data)                                 (0x00007C00&((data)<<10))
#define P2_B4_reg_p2_b_koff_bound(data)                               (0x00000200&((data)<<9))
#define P2_B4_reg_p2_b_koffok(data)                                   (0x00000100&((data)<<8))
#define P2_B4_reg_p2_b_13(data)                                       (0x000000FF&(data))
#define P2_B4_get_reg_p2_b_koff_sel(data)                             ((0x00007C00&(data))>>10)
#define P2_B4_get_reg_p2_b_koff_bound(data)                           ((0x00000200&(data))>>9)
#define P2_B4_get_reg_p2_b_koffok(data)                               ((0x00000100&(data))>>8)
#define P2_B4_get_reg_p2_b_13(data)                                   (0x000000FF&(data))


#define P2_CK1                                                        0xabc
#define P2_CK1_reg_addr                                               "0x98034abc"
#define P2_CK1_reg                                                    0x98034abc
#define P2_CK1_inst_addr                                              "0x02AF"
#define P2_CK1_inst                                                   0x02AF
#define set_P2_CK1_reg(data)                                          (*((volatile unsigned int*)P2_CK1_reg)=data)
#define get_P2_CK1_reg                                                (*((volatile unsigned int*)P2_CK1_reg))
#define P2_CK1_reg_p2_ck_4_shift                                      (24)
#define P2_CK1_reg_p2_ck_3_shift                                      (16)
#define P2_CK1_reg_p2_ck_2_shift                                      (8)
#define P2_CK1_reg_p2_ck_1_shift                                      (0)
#define P2_CK1_reg_p2_ck_4_mask                                       (0xFF000000)
#define P2_CK1_reg_p2_ck_3_mask                                       (0x00FF0000)
#define P2_CK1_reg_p2_ck_2_mask                                       (0x0000FF00)
#define P2_CK1_reg_p2_ck_1_mask                                       (0x000000FF)
#define P2_CK1_reg_p2_ck_4(data)                                      (0xFF000000&((data)<<24))
#define P2_CK1_reg_p2_ck_3(data)                                      (0x00FF0000&((data)<<16))
#define P2_CK1_reg_p2_ck_2(data)                                      (0x0000FF00&((data)<<8))
#define P2_CK1_reg_p2_ck_1(data)                                      (0x000000FF&(data))
#define P2_CK1_get_reg_p2_ck_4(data)                                  ((0xFF000000&(data))>>24)
#define P2_CK1_get_reg_p2_ck_3(data)                                  ((0x00FF0000&(data))>>16)
#define P2_CK1_get_reg_p2_ck_2(data)                                  ((0x0000FF00&(data))>>8)
#define P2_CK1_get_reg_p2_ck_1(data)                                  (0x000000FF&(data))
#define p2_ck_3_CMU_N_code												(_BIT18|_BIT19)
#define p2_ck_2_CMU_CKIN_SEL											(_BIT12|_BIT13|_BIT14|_BIT15)
#define p2_CMU_CKOUT_SEL												(_BIT11)
#define p2_ck_2_CK_MD_REF_SEL											(_BIT9)
#define p2_ck_1_port_bias												(_BIT2)
#define p2_ck_1_CKAFE_POW												(_BIT1)


#define P2_CK2                                                        0xac0
#define P2_CK2_reg_addr                                               "0x98034ac0"
#define P2_CK2_reg                                                    0x98034ac0
#define P2_CK2_inst_addr                                              "0x02B0"
#define P2_CK2_inst                                                   0x02B0
#define set_P2_CK2_reg(data)                                          (*((volatile unsigned int*)P2_CK2_reg)=data)
#define get_P2_CK2_reg                                                (*((volatile unsigned int*)P2_CK2_reg))
#define P2_CK2_reg_p2_ck_8_shift                                      (24)
#define P2_CK2_reg_p2_ck_7_shift                                      (16)
#define P2_CK2_reg_p2_ck_6_shift                                      (8)
#define P2_CK2_reg_p2_ck_5_shift                                      (0)
#define P2_CK2_reg_p2_ck_8_mask                                       (0xFF000000)
#define P2_CK2_reg_p2_ck_7_mask                                       (0x00FF0000)
#define P2_CK2_reg_p2_ck_6_mask                                       (0x0000FF00)
#define P2_CK2_reg_p2_ck_5_mask                                       (0x000000FF)
#define P2_CK2_reg_p2_ck_8(data)                                      (0xFF000000&((data)<<24))
#define P2_CK2_reg_p2_ck_7(data)                                      (0x00FF0000&((data)<<16))
#define P2_CK2_reg_p2_ck_6(data)                                      (0x0000FF00&((data)<<8))
#define P2_CK2_reg_p2_ck_5(data)                                      (0x000000FF&(data))
#define P2_CK2_get_reg_p2_ck_8(data)                                  ((0xFF000000&(data))>>24)
#define P2_CK2_get_reg_p2_ck_7(data)                                  ((0x00FF0000&(data))>>16)
#define P2_CK2_get_reg_p2_ck_6(data)                                  ((0x0000FF00&(data))>>8)
#define P2_CK2_get_reg_p2_ck_5(data)                                  (0x000000FF&(data))


#define P2_CK3                                                        0xac4
#define P2_CK3_reg_addr                                               "0x98034ac4"
#define P2_CK3_reg                                                    0x98034ac4
#define P2_CK3_inst_addr                                              "0x02B1"
#define P2_CK3_inst                                                   0x02B1
#define set_P2_CK3_reg(data)                                          (*((volatile unsigned int*)P2_CK3_reg)=data)
#define get_P2_CK3_reg                                                (*((volatile unsigned int*)P2_CK3_reg))
#define P2_CK3_reg_p2_ck_12_shift                                     (24)
#define P2_CK3_reg_p2_ck_11_shift                                     (16)
#define P2_CK3_reg_p2_ck_10_shift                                     (8)
#define P2_CK3_reg_p2_ck_9_shift                                      (0)
#define P2_CK3_reg_p2_ck_12_mask                                      (0xFF000000)
#define P2_CK3_reg_p2_ck_11_mask                                      (0x00FF0000)
#define P2_CK3_reg_p2_ck_10_mask                                      (0x0000FF00)
#define P2_CK3_reg_p2_ck_9_mask                                       (0x000000FF)
#define P2_CK3_reg_p2_ck_12(data)                                     (0xFF000000&((data)<<24))
#define P2_CK3_reg_p2_ck_11(data)                                     (0x00FF0000&((data)<<16))
#define P2_CK3_reg_p2_ck_10(data)                                     (0x0000FF00&((data)<<8))
#define P2_CK3_reg_p2_ck_9(data)                                      (0x000000FF&(data))
#define P2_CK3_get_reg_p2_ck_12(data)                                 ((0xFF000000&(data))>>24)
#define P2_CK3_get_reg_p2_ck_11(data)                                 ((0x00FF0000&(data))>>16)
#define P2_CK3_get_reg_p2_ck_10(data)                                 ((0x0000FF00&(data))>>8)
#define P2_CK3_get_reg_p2_ck_9(data)                                  (0x000000FF&(data))
#define P2_ck_9_CMU_PFD_RSTB										(_BIT5)
#define P2_ck_9_CMU_WDRST											(_BIT2)


#define P2_CK4                                                        0xac8
#define P2_CK4_reg_addr                                               "0x98034ac8"
#define P2_CK4_reg                                                    0x98034ac8
#define P2_CK4_inst_addr                                              "0x02B2"
#define P2_CK4_inst                                                   0x02B2
#define set_P2_CK4_reg(data)                                          (*((volatile unsigned int*)P2_CK4_reg)=data)
#define get_P2_CK4_reg                                                (*((volatile unsigned int*)P2_CK4_reg))
#define P2_CK4_reg_p2_ck_13_shift                                     (0)
#define P2_CK4_reg_p2_ck_13_mask                                      (0x000000FF)
#define P2_CK4_reg_p2_ck_13(data)                                     (0x000000FF&(data))
#define P2_CK4_get_reg_p2_ck_13(data)                                 (0x000000FF&(data))


#define P2_G1                                                         0xacc
#define P2_G1_reg_addr                                                "0x98034acc"
#define P2_G1_reg                                                     0x98034acc
#define P2_G1_inst_addr                                               "0x02B3"
#define P2_G1_inst                                                    0x02B3
#define set_P2_G1_reg(data)                                           (*((volatile unsigned int*)P2_G1_reg)=data)
#define get_P2_G1_reg                                                 (*((volatile unsigned int*)P2_G1_reg))
#define P2_G1_reg_p2_g_4_shift                                        (24)
#define P2_G1_reg_p2_g_3_shift                                        (16)
#define P2_G1_reg_p2_g_2_shift                                        (8)
#define P2_G1_reg_p2_g_1_shift                                        (0)
#define P2_G1_reg_p2_g_4_mask                                         (0xFF000000)
#define P2_G1_reg_p2_g_3_mask                                         (0x00FF0000)
#define P2_G1_reg_p2_g_2_mask                                         (0x0000FF00)
#define P2_G1_reg_p2_g_1_mask                                         (0x000000FF)
#define P2_G1_reg_p2_g_4(data)                                        (0xFF000000&((data)<<24))
#define P2_G1_reg_p2_g_3(data)                                        (0x00FF0000&((data)<<16))
#define P2_G1_reg_p2_g_2(data)                                        (0x0000FF00&((data)<<8))
#define P2_G1_reg_p2_g_1(data)                                        (0x000000FF&(data))
#define P2_G1_get_reg_p2_g_4(data)                                    ((0xFF000000&(data))>>24)
#define P2_G1_get_reg_p2_g_3(data)                                    ((0x00FF0000&(data))>>16)
#define P2_G1_get_reg_p2_g_2(data)                                    ((0x0000FF00&(data))>>8)
#define P2_G1_get_reg_p2_g_1(data)                                    (0x000000FF&(data))


#define P2_G2                                                         0xad0
#define P2_G2_reg_addr                                                "0x98034ad0"
#define P2_G2_reg                                                     0x98034ad0
#define P2_G2_inst_addr                                               "0x02B4"
#define P2_G2_inst                                                    0x02B4
#define set_P2_G2_reg(data)                                           (*((volatile unsigned int*)P2_G2_reg)=data)
#define get_P2_G2_reg                                                 (*((volatile unsigned int*)P2_G2_reg))
#define P2_G2_reg_p2_g_8_shift                                        (24)
#define P2_G2_reg_p2_g_7_shift                                        (16)
#define P2_G2_reg_p2_g_6_shift                                        (8)
#define P2_G2_reg_p2_g_5_shift                                        (0)
#define P2_G2_reg_p2_g_8_mask                                         (0xFF000000)
#define P2_G2_reg_p2_g_7_mask                                         (0x00FF0000)
#define P2_G2_reg_p2_g_6_mask                                         (0x0000FF00)
#define P2_G2_reg_p2_g_5_mask                                         (0x000000FF)
#define P2_G2_reg_p2_g_8(data)                                        (0xFF000000&((data)<<24))
#define P2_G2_reg_p2_g_7(data)                                        (0x00FF0000&((data)<<16))
#define P2_G2_reg_p2_g_6(data)                                        (0x0000FF00&((data)<<8))
#define P2_G2_reg_p2_g_5(data)                                        (0x000000FF&(data))
#define P2_G2_get_reg_p2_g_8(data)                                    ((0xFF000000&(data))>>24)
#define P2_G2_get_reg_p2_g_7(data)                                    ((0x00FF0000&(data))>>16)
#define P2_G2_get_reg_p2_g_6(data)                                    ((0x0000FF00&(data))>>8)
#define P2_G2_get_reg_p2_g_5(data)                                    (0x000000FF&(data))


#define P2_G3                                                         0xad4
#define P2_G3_reg_addr                                                "0x98034ad4"
#define P2_G3_reg                                                     0x98034ad4
#define P2_G3_inst_addr                                               "0x02B5"
#define P2_G3_inst                                                    0x02B5
#define set_P2_G3_reg(data)                                           (*((volatile unsigned int*)P2_G3_reg)=data)
#define get_P2_G3_reg                                                 (*((volatile unsigned int*)P2_G3_reg))
#define P2_G3_reg_p2_g_12_shift                                       (24)
#define P2_G3_reg_p2_g_11_shift                                       (16)
#define P2_G3_reg_p2_g_10_shift                                       (8)
#define P2_G3_reg_p2_g_9_shift                                        (0)
#define P2_G3_reg_p2_g_12_mask                                        (0xFF000000)
#define P2_G3_reg_p2_g_11_mask                                        (0x00FF0000)
#define P2_G3_reg_p2_g_10_mask                                        (0x0000FF00)
#define P2_G3_reg_p2_g_9_mask                                         (0x000000FF)
#define P2_G3_reg_p2_g_12(data)                                       (0xFF000000&((data)<<24))
#define P2_G3_reg_p2_g_11(data)                                       (0x00FF0000&((data)<<16))
#define P2_G3_reg_p2_g_10(data)                                       (0x0000FF00&((data)<<8))
#define P2_G3_reg_p2_g_9(data)                                        (0x000000FF&(data))
#define P2_G3_get_reg_p2_g_12(data)                                   ((0xFF000000&(data))>>24)
#define P2_G3_get_reg_p2_g_11(data)                                   ((0x00FF0000&(data))>>16)
#define P2_G3_get_reg_p2_g_10(data)                                   ((0x0000FF00&(data))>>8)
#define P2_G3_get_reg_p2_g_9(data)                                    (0x000000FF&(data))


#define P2_G4                                                         0xad8
#define P2_G4_reg_addr                                                "0x98034ad8"
#define P2_G4_reg                                                     0x98034ad8
#define P2_G4_inst_addr                                               "0x02B6"
#define P2_G4_inst                                                    0x02B6
#define set_P2_G4_reg(data)                                           (*((volatile unsigned int*)P2_G4_reg)=data)
#define get_P2_G4_reg                                                 (*((volatile unsigned int*)P2_G4_reg))
#define P2_G4_reg_p2_g_koff_sel_shift                                 (10)
#define P2_G4_reg_p2_g_koff_bound_shift                               (9)
#define P2_G4_reg_p2_g_koffok_shift                                   (8)
#define P2_G4_reg_p2_g_13_shift                                       (0)
#define P2_G4_reg_p2_g_koff_sel_mask                                  (0x00007C00)
#define P2_G4_reg_p2_g_koff_bound_mask                                (0x00000200)
#define P2_G4_reg_p2_g_koffok_mask                                    (0x00000100)
#define P2_G4_reg_p2_g_13_mask                                        (0x000000FF)
#define P2_G4_reg_p2_g_koff_sel(data)                                 (0x00007C00&((data)<<10))
#define P2_G4_reg_p2_g_koff_bound(data)                               (0x00000200&((data)<<9))
#define P2_G4_reg_p2_g_koffok(data)                                   (0x00000100&((data)<<8))
#define P2_G4_reg_p2_g_13(data)                                       (0x000000FF&(data))
#define P2_G4_get_reg_p2_g_koff_sel(data)                             ((0x00007C00&(data))>>10)
#define P2_G4_get_reg_p2_g_koff_bound(data)                           ((0x00000200&(data))>>9)
#define P2_G4_get_reg_p2_g_koffok(data)                               ((0x00000100&(data))>>8)
#define P2_G4_get_reg_p2_g_13(data)                                   (0x000000FF&(data))


#define P2_R1                                                         0xadc
#define P2_R1_reg_addr                                                "0x98034adc"
#define P2_R1_reg                                                     0x98034adc
#define P2_R1_inst_addr                                               "0x02B7"
#define P2_R1_inst                                                    0x02B7
#define set_P2_R1_reg(data)                                           (*((volatile unsigned int*)P2_R1_reg)=data)
#define get_P2_R1_reg                                                 (*((volatile unsigned int*)P2_R1_reg))
#define P2_R1_reg_p2_r_4_shift                                        (24)
#define P2_R1_reg_p2_r_3_shift                                        (16)
#define P2_R1_reg_p2_r_2_shift                                        (8)
#define P2_R1_reg_p2_r_1_shift                                        (0)
#define P2_R1_reg_p2_r_4_mask                                         (0xFF000000)
#define P2_R1_reg_p2_r_3_mask                                         (0x00FF0000)
#define P2_R1_reg_p2_r_2_mask                                         (0x0000FF00)
#define P2_R1_reg_p2_r_1_mask                                         (0x000000FF)
#define P2_R1_reg_p2_r_4(data)                                        (0xFF000000&((data)<<24))
#define P2_R1_reg_p2_r_3(data)                                        (0x00FF0000&((data)<<16))
#define P2_R1_reg_p2_r_2(data)                                        (0x0000FF00&((data)<<8))
#define P2_R1_reg_p2_r_1(data)                                        (0x000000FF&(data))
#define P2_R1_get_reg_p2_r_4(data)                                    ((0xFF000000&(data))>>24)
#define P2_R1_get_reg_p2_r_3(data)                                    ((0x00FF0000&(data))>>16)
#define P2_R1_get_reg_p2_r_2(data)                                    ((0x0000FF00&(data))>>8)
#define P2_R1_get_reg_p2_r_1(data)                                    (0x000000FF&(data))


#define P2_R2                                                         0xae0
#define P2_R2_reg_addr                                                "0x98034ae0"
#define P2_R2_reg                                                     0x98034ae0
#define P2_R2_inst_addr                                               "0x02B8"
#define P2_R2_inst                                                    0x02B8
#define set_P2_R2_reg(data)                                           (*((volatile unsigned int*)P2_R2_reg)=data)
#define get_P2_R2_reg                                                 (*((volatile unsigned int*)P2_R2_reg))
#define P2_R2_reg_p2_r_8_shift                                        (24)
#define P2_R2_reg_p2_r_7_shift                                        (16)
#define P2_R2_reg_p2_r_6_shift                                        (8)
#define P2_R2_reg_p2_r_5_shift                                        (0)
#define P2_R2_reg_p2_r_8_mask                                         (0xFF000000)
#define P2_R2_reg_p2_r_7_mask                                         (0x00FF0000)
#define P2_R2_reg_p2_r_6_mask                                         (0x0000FF00)
#define P2_R2_reg_p2_r_5_mask                                         (0x000000FF)
#define P2_R2_reg_p2_r_8(data)                                        (0xFF000000&((data)<<24))
#define P2_R2_reg_p2_r_7(data)                                        (0x00FF0000&((data)<<16))
#define P2_R2_reg_p2_r_6(data)                                        (0x0000FF00&((data)<<8))
#define P2_R2_reg_p2_r_5(data)                                        (0x000000FF&(data))
#define P2_R2_get_reg_p2_r_8(data)                                    ((0xFF000000&(data))>>24)
#define P2_R2_get_reg_p2_r_7(data)                                    ((0x00FF0000&(data))>>16)
#define P2_R2_get_reg_p2_r_6(data)                                    ((0x0000FF00&(data))>>8)
#define P2_R2_get_reg_p2_r_5(data)                                    (0x000000FF&(data))


#define P2_R3                                                         0xae4
#define P2_R3_reg_addr                                                "0x98034ae4"
#define P2_R3_reg                                                     0x98034ae4
#define P2_R3_inst_addr                                               "0x02B9"
#define P2_R3_inst                                                    0x02B9
#define set_P2_R3_reg(data)                                           (*((volatile unsigned int*)P2_R3_reg)=data)
#define get_P2_R3_reg                                                 (*((volatile unsigned int*)P2_R3_reg))
#define P2_R3_reg_p2_r_12_shift                                       (24)
#define P2_R3_reg_p2_r_11_shift                                       (16)
#define P2_R3_reg_p2_r_10_shift                                       (8)
#define P2_R3_reg_p2_r_9_shift                                        (0)
#define P2_R3_reg_p2_r_12_mask                                        (0xFF000000)
#define P2_R3_reg_p2_r_11_mask                                        (0x00FF0000)
#define P2_R3_reg_p2_r_10_mask                                        (0x0000FF00)
#define P2_R3_reg_p2_r_9_mask                                         (0x000000FF)
#define P2_R3_reg_p2_r_12(data)                                       (0xFF000000&((data)<<24))
#define P2_R3_reg_p2_r_11(data)                                       (0x00FF0000&((data)<<16))
#define P2_R3_reg_p2_r_10(data)                                       (0x0000FF00&((data)<<8))
#define P2_R3_reg_p2_r_9(data)                                        (0x000000FF&(data))
#define P2_R3_get_reg_p2_r_12(data)                                   ((0xFF000000&(data))>>24)
#define P2_R3_get_reg_p2_r_11(data)                                   ((0x00FF0000&(data))>>16)
#define P2_R3_get_reg_p2_r_10(data)                                   ((0x0000FF00&(data))>>8)
#define P2_R3_get_reg_p2_r_9(data)                                    (0x000000FF&(data))


#define P2_R4                                                         0xae8
#define P2_R4_reg_addr                                                "0x98034ae8"
#define P2_R4_reg                                                     0x98034ae8
#define P2_R4_inst_addr                                               "0x02BA"
#define P2_R4_inst                                                    0x02BA
#define set_P2_R4_reg(data)                                           (*((volatile unsigned int*)P2_R4_reg)=data)
#define get_P2_R4_reg                                                 (*((volatile unsigned int*)P2_R4_reg))
#define P2_R4_reg_p2_r_koff_sel_shift                                 (10)
#define P2_R4_reg_p2_r_koff_bound_shift                               (9)
#define P2_R4_reg_p2_r_koffok_shift                                   (8)
#define P2_R4_reg_p2_r_13_shift                                       (0)
#define P2_R4_reg_p2_r_koff_sel_mask                                  (0x00007C00)
#define P2_R4_reg_p2_r_koff_bound_mask                                (0x00000200)
#define P2_R4_reg_p2_r_koffok_mask                                    (0x00000100)
#define P2_R4_reg_p2_r_13_mask                                        (0x000000FF)
#define P2_R4_reg_p2_r_koff_sel(data)                                 (0x00007C00&((data)<<10))
#define P2_R4_reg_p2_r_koff_bound(data)                               (0x00000200&((data)<<9))
#define P2_R4_reg_p2_r_koffok(data)                                   (0x00000100&((data)<<8))
#define P2_R4_reg_p2_r_13(data)                                       (0x000000FF&(data))
#define P2_R4_get_reg_p2_r_koff_sel(data)                             ((0x00007C00&(data))>>10)
#define P2_R4_get_reg_p2_r_koff_bound(data)                           ((0x00000200&(data))>>9)
#define P2_R4_get_reg_p2_r_koffok(data)                               ((0x00000100&(data))>>8)
#define P2_R4_get_reg_p2_r_13(data)                                   (0x000000FF&(data))


#define TEST                                                          0xaec
#define TEST_reg_addr                                                 "0x98034aec"
#define TEST_reg                                                      0x98034aec
#define TEST_inst_addr                                                "0x02BB"
#define TEST_inst                                                     0x02BB
#define set_TEST_reg(data)                                            (*((volatile unsigned int*)TEST_reg)=data)
#define get_TEST_reg                                                  (*((volatile unsigned int*)TEST_reg))
#define TEST_reg_tst_spad_shift                                       (4)
#define TEST_reg_stst_shift                                           (0)
#define TEST_reg_tst_spad_mask                                        (0x00000010)
#define TEST_reg_stst_mask                                            (0x0000000F)
#define TEST_reg_tst_spad(data)                                       (0x00000010&((data)<<4))
#define TEST_reg_stst(data)                                           (0x0000000F&(data))
#define TEST_get_reg_tst_spad(data)                                   ((0x00000010&(data))>>4)
#define TEST_get_reg_stst(data)                                       (0x0000000F&(data))


#define TOP_IN                                                        0xaf0
#define TOP_IN_reg_addr                                               "0x98034af0"
#define TOP_IN_reg                                                    0x98034af0
#define TOP_IN_inst_addr                                              "0x02BC"
#define TOP_IN_inst                                                   0x02BC
#define set_TOP_IN_reg(data)                                          (*((volatile unsigned int*)TOP_IN_reg)=data)
#define get_TOP_IN_reg                                                (*((volatile unsigned int*)TOP_IN_reg))
#define TOP_IN_reg_top_in_4_shift                                     (24)
#define TOP_IN_reg_top_in_3_shift                                     (16)
#define TOP_IN_reg_top_in_2_shift                                     (8)
#define TOP_IN_reg_top_in_1_shift                                     (0)
#define TOP_IN_reg_top_in_4_mask                                      (0xFF000000)
#define TOP_IN_reg_top_in_3_mask                                      (0x00FF0000)
#define TOP_IN_reg_top_in_2_mask                                      (0x0000FF00)
#define TOP_IN_reg_top_in_1_mask                                      (0x000000FF)
#define TOP_IN_reg_top_in_4(data)                                     (0xFF000000&((data)<<24))
#define TOP_IN_reg_top_in_3(data)                                     (0x00FF0000&((data)<<16))
#define TOP_IN_reg_top_in_2(data)                                     (0x0000FF00&((data)<<8))
#define TOP_IN_reg_top_in_1(data)                                     (0x000000FF&(data))
#define TOP_IN_get_reg_top_in_4(data)                                 ((0xFF000000&(data))>>24)
#define TOP_IN_get_reg_top_in_3(data)                                 ((0x00FF0000&(data))>>16)
#define TOP_IN_get_reg_top_in_2(data)                                 ((0x0000FF00&(data))>>8)
#define TOP_IN_get_reg_top_in_1(data)                                 (0x000000FF&(data))


#define TOP_OUT                                                       0xaf4
#define TOP_OUT_reg_addr                                              "0x98034af4"
#define TOP_OUT_reg                                                   0x98034af4
#define TOP_OUT_inst_addr                                             "0x02BD"
#define TOP_OUT_inst                                                  0x02BD
#define set_TOP_OUT_reg(data)                                         (*((volatile unsigned int*)TOP_OUT_reg)=data)
#define get_TOP_OUT_reg                                               (*((volatile unsigned int*)TOP_OUT_reg))
#define TOP_OUT_reg_top_out_4_shift                                   (24)
#define TOP_OUT_reg_top_out_3_shift                                   (16)
#define TOP_OUT_reg_top_out_2_shift                                   (8)
#define TOP_OUT_reg_top_out_1_shift                                   (0)
#define TOP_OUT_reg_top_out_4_mask                                    (0xFF000000)
#define TOP_OUT_reg_top_out_3_mask                                    (0x00FF0000)
#define TOP_OUT_reg_top_out_2_mask                                    (0x0000FF00)
#define TOP_OUT_reg_top_out_1_mask                                    (0x000000FF)
#define TOP_OUT_reg_top_out_4(data)                                   (0xFF000000&((data)<<24))
#define TOP_OUT_reg_top_out_3(data)                                   (0x00FF0000&((data)<<16))
#define TOP_OUT_reg_top_out_2(data)                                   (0x0000FF00&((data)<<8))
#define TOP_OUT_reg_top_out_1(data)                                   (0x000000FF&(data))
#define TOP_OUT_get_reg_top_out_4(data)                               ((0xFF000000&(data))>>24)
#define TOP_OUT_get_reg_top_out_3(data)                               ((0x00FF0000&(data))>>16)
#define TOP_OUT_get_reg_top_out_2(data)                               ((0x0000FF00&(data))>>8)
#define TOP_OUT_get_reg_top_out_1(data)                               (0x000000FF&(data))


#define Z0K                                                           0xaf8
#define Z0K_reg_addr                                                  "0x98034af8"
#define Z0K_reg                                                       0x98034af8
#define Z0K_inst_addr                                                 "0x02BE"
#define Z0K_inst                                                      0x02BE
#define set_Z0K_reg(data)                                             (*((volatile unsigned int*)Z0K_reg)=data)
#define get_Z0K_reg                                                   (*((volatile unsigned int*)Z0K_reg))
#define Z0K_reg_z0_z0pow_shift                                        (28)
#define Z0K_reg_z0_stune_shift                                        (27)
#define Z0K_reg_z0_res_shift                                          (22)
#define Z0K_reg_z0_ok_shift                                           (21)
#define Z0K_reg_z0_entst_shift                                        (20)
#define Z0K_reg_z0_bound_shift                                        (19)
#define Z0K_reg_z0_adjr_2_shift                                       (14)
#define Z0K_reg_z0_adjr_1_shift                                       (9)
#define Z0K_reg_z0_adjr_0_shift                                       (4)
#define Z0K_reg_z0tst_shift                                           (0)
#define Z0K_reg_z0_z0pow_mask                                         (0x10000000)
#define Z0K_reg_z0_stune_mask                                         (0x08000000)
#define Z0K_reg_z0_res_mask                                           (0x07C00000)
#define Z0K_reg_z0_ok_mask                                            (0x00200000)
#define Z0K_reg_z0_entst_mask                                         (0x00100000)
#define Z0K_reg_z0_bound_mask                                         (0x00080000)
#define Z0K_reg_z0_adjr_2_mask                                        (0x0007C000)
#define Z0K_reg_z0_adjr_1_mask                                        (0x00003E00)
#define Z0K_reg_z0_adjr_0_mask                                        (0x000001F0)
#define Z0K_reg_z0tst_mask                                            (0x0000000F)
#define Z0K_reg_z0_z0pow(data)                                        (0x10000000&((data)<<28))
#define Z0K_reg_z0_stune(data)                                        (0x08000000&((data)<<27))
#define Z0K_reg_z0_res(data)                                          (0x07C00000&((data)<<22))
#define Z0K_reg_z0_ok(data)                                           (0x00200000&((data)<<21))
#define Z0K_reg_z0_entst(data)                                        (0x00100000&((data)<<20))
#define Z0K_reg_z0_bound(data)                                        (0x00080000&((data)<<19))
#define Z0K_reg_z0_adjr_2(data)                                       (0x0007C000&((data)<<14))
#define Z0K_reg_z0_adjr_1(data)                                       (0x00003E00&((data)<<9))
#define Z0K_reg_z0_adjr_0(data)                                       (0x000001F0&((data)<<4))
#define Z0K_reg_z0tst(data)                                           (0x0000000F&(data))
#define Z0K_get_reg_z0_z0pow(data)                                    ((0x10000000&(data))>>28)
#define Z0K_get_reg_z0_stune(data)                                    ((0x08000000&(data))>>27)
#define Z0K_get_reg_z0_res(data)                                      ((0x07C00000&(data))>>22)
#define Z0K_get_reg_z0_ok(data)                                       ((0x00200000&(data))>>21)
#define Z0K_get_reg_z0_entst(data)                                    ((0x00100000&(data))>>20)
#define Z0K_get_reg_z0_bound(data)                                    ((0x00080000&(data))>>19)
#define Z0K_get_reg_z0_adjr_2(data)                                   ((0x0007C000&(data))>>14)
#define Z0K_get_reg_z0_adjr_1(data)                                   ((0x00003E00&(data))>>9)
#define Z0K_get_reg_z0_adjr_0(data)                                   ((0x000001F0&(data))>>4)
#define Z0K_get_reg_z0tst(data)                                       (0x0000000F&(data))


#define Z0POW                                                         0xafc
#define Z0POW_reg_addr                                                "0x98034afc"
#define Z0POW_reg                                                     0x98034afc
#define Z0POW_inst_addr                                               "0x02BF"
#define Z0POW_inst                                                    0x02BF
#define set_Z0POW_reg(data)                                           (*((volatile unsigned int*)Z0POW_reg)=data)
#define get_Z0POW_reg                                                 (*((volatile unsigned int*)Z0POW_reg))
#define Z0POW_reg_ck_pixel_hdmirpt_div2_shift                         (21)
#define Z0POW_reg_z0_z300_sel_shift                                   (18)
#define Z0POW_reg_z0_z300pow_shift                                    (15)
#define Z0POW_reg_z0_z100_en_shift                                    (12)
#define Z0POW_reg_z0_z0pow_r_shift                                    (9)
#define Z0POW_reg_z0_z0pow_g_shift                                    (6)
#define Z0POW_reg_z0_z0pow_ck_shift                                   (3)
#define Z0POW_reg_z0_z0pow_b_shift                                    (0)
#define Z0POW_reg_ck_pixel_hdmirpt_div2_mask                          (0x00200000)
#define Z0POW_reg_z0_z300_sel_mask                                    (0x001C0000)
#define Z0POW_reg_z0_z300pow_mask                                     (0x00038000)
#define Z0POW_reg_z0_z100_en_mask                                     (0x00007000)
#define Z0POW_reg_z0_z0pow_r_mask                                     (0x00000E00)
#define Z0POW_reg_z0_z0pow_g_mask                                     (0x000001C0)
#define Z0POW_reg_z0_z0pow_ck_mask                                    (0x00000038)
#define Z0POW_reg_z0_z0pow_b_mask                                     (0x00000007)
#define Z0POW_reg_ck_pixel_hdmirpt_div2(data)                         (0x00200000&((data)<<21))
#define Z0POW_reg_z0_z300_sel(data)                                   (0x001C0000&((data)<<18))
#define Z0POW_reg_z0_z300pow(data)                                    (0x00038000&((data)<<15))
#define Z0POW_reg_z0_z100_en(data)                                    (0x00007000&((data)<<12))
#define Z0POW_reg_z0_z0pow_r(data)                                    (0x00000E00&((data)<<9))
#define Z0POW_reg_z0_z0pow_g(data)                                    (0x000001C0&((data)<<6))
#define Z0POW_reg_z0_z0pow_ck(data)                                   (0x00000038&((data)<<3))
#define Z0POW_reg_z0_z0pow_b(data)                                    (0x00000007&(data))
#define Z0POW_get_reg_ck_pixel_hdmirpt_div2(data)                     ((0x00200000&(data))>>21)
#define Z0POW_get_reg_z0_z300_sel(data)                               ((0x001C0000&(data))>>18)
#define Z0POW_get_reg_z0_z300pow(data)                                ((0x00038000&(data))>>15)
#define Z0POW_get_reg_z0_z100_en(data)                                ((0x00007000&(data))>>12)
#define Z0POW_get_reg_z0_z0pow_r(data)                                ((0x00000E00&(data))>>9)
#define Z0POW_get_reg_z0_z0pow_g(data)                                ((0x000001C0&(data))>>6)
#define Z0POW_get_reg_z0_z0pow_ck(data)                               ((0x00000038&(data))>>3)
#define Z0POW_get_reg_z0_z0pow_b(data)                                (0x00000007&(data))


#define MBIAS                                                         0xb00
#define MBIAS_reg_addr                                                "0x98034b00"
#define MBIAS_reg                                                     0x98034b00
#define MBIAS_inst_addr                                               "0x02C0"
#define MBIAS_inst                                                    0x02C0
#define MBIAS_reg_mbias_en_shift                                      (0)
#define MBIAS_reg_mbias_en_mask                                       (0x00000001)
#define MBIAS_reg_mbias_en(data)                                      (0x00000001&(data))
#define MBIAS_get_reg_mbias_en(data)                                  (0x00000001&(data))


#define HDMIRPT                                                       0xb04
#define HDMIRPT_reg_addr                                              "0x98034b04"
#define HDMIRPT_reg                                                   0x98034b04
#define HDMIRPT_inst_addr                                             "0x02C1"
#define HDMIRPT_inst                                                  0x02C1
#define HDMIRPT_reg_hdmirpt_ck_div2_shift                             (4)
#define HDMIRPT_reg_hdmirpt_ck_sel_shift                              (2)
#define HDMIRPT_reg_hdmirpt_hdmi2_shift                               (1)
#define HDMIRPT_reg_hdmirpt_en_shift                                  (0)
#define HDMIRPT_reg_hdmirpt_ck_div2_mask                              (0x00000010)
#define HDMIRPT_reg_hdmirpt_ck_sel_mask                               (0x0000000C)
#define HDMIRPT_reg_hdmirpt_hdmi2_mask                                (0x00000002)
#define HDMIRPT_reg_hdmirpt_en_mask                                   (0x00000001)
#define HDMIRPT_reg_hdmirpt_ck_div2(data)                             (0x00000010&((data)<<4))
#define HDMIRPT_reg_hdmirpt_ck_sel(data)                              (0x0000000C&((data)<<2))
#define HDMIRPT_reg_hdmirpt_hdmi2(data)                               (0x00000002&((data)<<1))
#define HDMIRPT_reg_hdmirpt_en(data)                                  (0x00000001&(data))
#define HDMIRPT_get_reg_hdmirpt_ck_div2(data)                         ((0x00000010&(data))>>4)
#define HDMIRPT_get_reg_hdmirpt_ck_sel(data)                          ((0x0000000C&(data))>>2)
#define HDMIRPT_get_reg_hdmirpt_hdmi2(data)                           ((0x00000002&(data))>>1)
#define HDMIRPT_get_reg_hdmirpt_en(data)                              (0x00000001&(data))


#define BYPASS                                                        0xb08
#define BYPASS_reg_addr                                               "0x98034b08"
#define BYPASS_reg                                                    0x98034b08
#define BYPASS_inst_addr                                              "0x02C2"
#define BYPASS_inst                                                   0x02C2
#define set_BYPASS_reg(data)                                          (*((volatile unsigned int*)BYPASS_reg)=data)
#define get_BYPASS_reg                                                (*((volatile unsigned int*)BYPASS_reg))
#define BYPASS_p2_bypass_ok_shift                                     (2)
#define BYPASS_p1_bypass_ok_shift                                     (1)
#define BYPASS_p0_bypass_ok_shift                                     (0)
#define BYPASS_p2_bypass_ok_mask                                      (0x00000004)
#define BYPASS_p1_bypass_ok_mask                                      (0x00000002)
#define BYPASS_p0_bypass_ok_mask                                      (0x00000001)
#define BYPASS_p2_bypass_ok(data)                                     (0x00000004&((data)<<2))
#define BYPASS_p1_bypass_ok(data)                                     (0x00000002&((data)<<1))
#define BYPASS_p0_bypass_ok(data)                                     (0x00000001&(data))
#define BYPASS_get_p2_bypass_ok(data)                                 ((0x00000004&(data))>>2)
#define BYPASS_get_p1_bypass_ok(data)                                 ((0x00000002&(data))>>1)
#define BYPASS_get_p0_bypass_ok(data)                                 (0x00000001&(data))


#define RST                                                           0xb0c
#define RST_reg_addr                                                  "0x98034b0c"
#define RST_reg                                                       0x98034b0c
#define RST_inst_addr                                                 "0x02C3"
#define RST_inst                                                      0x02C3
#define set_RST_reg(data)                                             (*((volatile unsigned int*)RST_reg)=data)
#define get_RST_reg                                                   (*((volatile unsigned int*)RST_reg))
#define RST_eye_monitor_rstn_shift                                    (19)
#define RST_dfe_rstn_n_shift                                          (18)
#define RST_reg_p2_acdr_rstb_fsm_shift                                (17)
#define RST_reg_p1_acdr_rstb_fsm_shift                                (16)
#define RST_reg_p0_acdr_rstb_fsm_shift                                (15)
#define RST_p2_ck_vcorstb_shift                                       (14)
#define RST_p1_ck_vcorstb_shift                                       (13)
#define RST_p0_ck_vcorstb_shift                                       (12)
#define RST_p2_ck_pllrstb_shift                                       (11)
#define RST_p1_ck_pllrstb_shift                                       (10)
#define RST_p0_ck_pllrstb_shift                                       (9)
#define RST_p2_r_demux_rstb_shift                                     (8)
#define RST_p2_g_demux_rstb_shift                                     (7)
#define RST_p2_b_demux_rstb_shift                                     (6)
#define RST_p1_r_demux_rstb_shift                                     (5)
#define RST_p1_g_demux_rstb_shift                                     (4)
#define RST_p1_b_demux_rstb_shift                                     (3)
#define RST_p0_r_demux_rstb_shift                                     (2)
#define RST_p0_g_demux_rstb_shift                                     (1)
#define RST_p0_b_demux_rstb_shift                                     (0)
#define RST_eye_monitor_rstn_mask                                     (0x00080000)
#define RST_dfe_rstn_n_mask                                           (0x00040000)
#define RST_reg_p2_acdr_rstb_fsm_mask                                 (0x00020000)
#define RST_reg_p1_acdr_rstb_fsm_mask                                 (0x00010000)
#define RST_reg_p0_acdr_rstb_fsm_mask                                 (0x00008000)
#define RST_p2_ck_vcorstb_mask                                        (0x00004000)
#define RST_p1_ck_vcorstb_mask                                        (0x00002000)
#define RST_p0_ck_vcorstb_mask                                        (0x00001000)
#define RST_p2_ck_pllrstb_mask                                        (0x00000800)
#define RST_p1_ck_pllrstb_mask                                        (0x00000400)
#define RST_p0_ck_pllrstb_mask                                        (0x00000200)
#define RST_p2_r_demux_rstb_mask                                      (0x00000100)
#define RST_p2_g_demux_rstb_mask                                      (0x00000080)
#define RST_p2_b_demux_rstb_mask                                      (0x00000040)
#define RST_p1_r_demux_rstb_mask                                      (0x00000020)
#define RST_p1_g_demux_rstb_mask                                      (0x00000010)
#define RST_p1_b_demux_rstb_mask                                      (0x00000008)
#define RST_p0_r_demux_rstb_mask                                      (0x00000004)
#define RST_p0_g_demux_rstb_mask                                      (0x00000002)
#define RST_p0_b_demux_rstb_mask                                      (0x00000001)
#define RST_eye_monitor_rstn(data)                                    (0x00080000&((data)<<19))
#define RST_dfe_rstn_n(data)                                          (0x00040000&((data)<<18))
#define RST_reg_p2_acdr_rstb_fsm(data)                                (0x00020000&((data)<<17))
#define RST_reg_p1_acdr_rstb_fsm(data)                                (0x00010000&((data)<<16))
#define RST_reg_p0_acdr_rstb_fsm(data)                                (0x00008000&((data)<<15))
#define RST_p2_ck_vcorstb(data)                                       (0x00004000&((data)<<14))
#define RST_p1_ck_vcorstb(data)                                       (0x00002000&((data)<<13))
#define RST_p0_ck_vcorstb(data)                                       (0x00001000&((data)<<12))
#define RST_p2_ck_pllrstb(data)                                       (0x00000800&((data)<<11))
#define RST_p1_ck_pllrstb(data)                                       (0x00000400&((data)<<10))
#define RST_p0_ck_pllrstb(data)                                       (0x00000200&((data)<<9))
#define RST_p2_r_demux_rstb(data)                                     (0x00000100&((data)<<8))
#define RST_p2_g_demux_rstb(data)                                     (0x00000080&((data)<<7))
#define RST_p2_b_demux_rstb(data)                                     (0x00000040&((data)<<6))
#define RST_p1_r_demux_rstb(data)                                     (0x00000020&((data)<<5))
#define RST_p1_g_demux_rstb(data)                                     (0x00000010&((data)<<4))
#define RST_p1_b_demux_rstb(data)                                     (0x00000008&((data)<<3))
#define RST_p0_r_demux_rstb(data)                                     (0x00000004&((data)<<2))
#define RST_p0_g_demux_rstb(data)                                     (0x00000002&((data)<<1))
#define RST_p0_b_demux_rstb(data)                                     (0x00000001&(data))
#define RST_get_eye_monitor_rstn(data)                                ((0x00080000&(data))>>19)
#define RST_get_dfe_rstn_n(data)                                      ((0x00040000&(data))>>18)
#define RST_get_reg_p2_acdr_rstb_fsm(data)                            ((0x00020000&(data))>>17)
#define RST_get_reg_p1_acdr_rstb_fsm(data)                            ((0x00010000&(data))>>16)
#define RST_get_reg_p0_acdr_rstb_fsm(data)                            ((0x00008000&(data))>>15)
#define RST_get_p2_ck_vcorstb(data)                                   ((0x00004000&(data))>>14)
#define RST_get_p1_ck_vcorstb(data)                                   ((0x00002000&(data))>>13)
#define RST_get_p0_ck_vcorstb(data)                                   ((0x00001000&(data))>>12)
#define RST_get_p2_ck_pllrstb(data)                                   ((0x00000800&(data))>>11)
#define RST_get_p1_ck_pllrstb(data)                                   ((0x00000400&(data))>>10)
#define RST_get_p0_ck_pllrstb(data)                                   ((0x00000200&(data))>>9)
#define RST_get_p2_r_demux_rstb(data)                                 ((0x00000100&(data))>>8)
#define RST_get_p2_g_demux_rstb(data)                                 ((0x00000080&(data))>>7)
#define RST_get_p2_b_demux_rstb(data)                                 ((0x00000040&(data))>>6)
#define RST_get_p1_r_demux_rstb(data)                                 ((0x00000020&(data))>>5)
#define RST_get_p1_g_demux_rstb(data)                                 ((0x00000010&(data))>>4)
#define RST_get_p1_b_demux_rstb(data)                                 ((0x00000008&(data))>>3)
#define RST_get_p0_r_demux_rstb(data)                                 ((0x00000004&(data))>>2)
#define RST_get_p0_g_demux_rstb(data)                                 ((0x00000002&(data))>>1)
#define RST_get_p0_b_demux_rstb(data)                                 (0x00000001&(data))


#define REGD0                                                         0xb1c
#define REGD0_reg_addr                                                "0x98034b1c"
#define REGD0_reg                                                     0x98034b1c
#define REGD0_inst_addr                                               "0x02C7"
#define REGD0_inst                                                    0x02C7
#define set_REGD0_reg(data)                                           (*((volatile unsigned int*)REGD0_reg)=data)
#define get_REGD0_reg                                                 (*((volatile unsigned int*)REGD0_reg))
#define REGD0_p0_r_dig_rst_n_shift                                    (31)
#define REGD0_p0_g_dig_rst_n_shift                                    (30)
#define REGD0_p0_b_dig_rst_n_shift                                    (29)
#define REGD0_p0_r_cdr_rst_n_shift                                    (28)
#define REGD0_p0_g_cdr_rst_n_shift                                    (27)
#define REGD0_p0_b_cdr_rst_n_shift                                    (26)
#define REGD0_reg_p0_cdr_ckinv_r_shift                                (25)
#define REGD0_reg_p0_cdr_ckinv_g_shift                                (24)
#define REGD0_reg_p0_cdr_ckinv_b_shift                                (23)
#define REGD0_reg_p0_shift_inv_r_shift                                (22)
#define REGD0_reg_p0_shift_inv_g_shift                                (21)
#define REGD0_reg_p0_shift_inv_b_shift                                (20)
#define REGD0_reg_p0_rate_sel_shift                                   (17)
#define REGD0_reg_p0_kd_shift                                         (16)
#define REGD0_reg_p0_kp_shift                                         (8)
#define REGD0_reg_p0_ki_shift                                         (5)
#define REGD0_reg_p0_bypass_sdm_int_shift                             (4)
#define REGD0_reg_p0_data_order_shift                                 (3)
#define REGD0_reg_p0_infifo_cnt_shift                                 (0)
#define REGD0_p0_r_dig_rst_n_mask                                     (0x80000000)
#define REGD0_p0_g_dig_rst_n_mask                                     (0x40000000)
#define REGD0_p0_b_dig_rst_n_mask                                     (0x20000000)
#define REGD0_p0_r_cdr_rst_n_mask                                     (0x10000000)
#define REGD0_p0_g_cdr_rst_n_mask                                     (0x08000000)
#define REGD0_p0_b_cdr_rst_n_mask                                     (0x04000000)
#define REGD0_reg_p0_cdr_ckinv_r_mask                                 (0x02000000)
#define REGD0_reg_p0_cdr_ckinv_g_mask                                 (0x01000000)
#define REGD0_reg_p0_cdr_ckinv_b_mask                                 (0x00800000)
#define REGD0_reg_p0_shift_inv_r_mask                                 (0x00400000)
#define REGD0_reg_p0_shift_inv_g_mask                                 (0x00200000)
#define REGD0_reg_p0_shift_inv_b_mask                                 (0x00100000)
#define REGD0_reg_p0_rate_sel_mask                                    (0x000E0000)
#define REGD0_reg_p0_kd_mask                                          (0x00010000)
#define REGD0_reg_p0_kp_mask                                          (0x0000FF00)
#define REGD0_reg_p0_ki_mask                                          (0x000000E0)
#define REGD0_reg_p0_bypass_sdm_int_mask                              (0x00000010)
#define REGD0_reg_p0_data_order_mask                                  (0x00000008)
#define REGD0_reg_p0_infifo_cnt_mask                                  (0x00000007)
#define REGD0_p0_r_dig_rst_n(data)                                    (0x80000000&((data)<<31))
#define REGD0_p0_g_dig_rst_n(data)                                    (0x40000000&((data)<<30))
#define REGD0_p0_b_dig_rst_n(data)                                    (0x20000000&((data)<<29))
#define REGD0_p0_r_cdr_rst_n(data)                                    (0x10000000&((data)<<28))
#define REGD0_p0_g_cdr_rst_n(data)                                    (0x08000000&((data)<<27))
#define REGD0_p0_b_cdr_rst_n(data)                                    (0x04000000&((data)<<26))
#define REGD0_reg_p0_cdr_ckinv_r(data)                                (0x02000000&((data)<<25))
#define REGD0_reg_p0_cdr_ckinv_g(data)                                (0x01000000&((data)<<24))
#define REGD0_reg_p0_cdr_ckinv_b(data)                                (0x00800000&((data)<<23))
#define REGD0_reg_p0_shift_inv_r(data)                                (0x00400000&((data)<<22))
#define REGD0_reg_p0_shift_inv_g(data)                                (0x00200000&((data)<<21))
#define REGD0_reg_p0_shift_inv_b(data)                                (0x00100000&((data)<<20))
#define REGD0_reg_p0_rate_sel(data)                                   (0x000E0000&((data)<<17))
#define REGD0_reg_p0_kd(data)                                         (0x00010000&((data)<<16))
#define REGD0_reg_p0_kp(data)                                         (0x0000FF00&((data)<<8))
#define REGD0_reg_p0_ki(data)                                         (0x000000E0&((data)<<5))
#define REGD0_reg_p0_bypass_sdm_int(data)                             (0x00000010&((data)<<4))
#define REGD0_reg_p0_data_order(data)                                 (0x00000008&((data)<<3))
#define REGD0_reg_p0_infifo_cnt(data)                                 (0x00000007&(data))
#define REGD0_get_p0_r_dig_rst_n(data)                                ((0x80000000&(data))>>31)
#define REGD0_get_p0_g_dig_rst_n(data)                                ((0x40000000&(data))>>30)
#define REGD0_get_p0_b_dig_rst_n(data)                                ((0x20000000&(data))>>29)
#define REGD0_get_p0_r_cdr_rst_n(data)                                ((0x10000000&(data))>>28)
#define REGD0_get_p0_g_cdr_rst_n(data)                                ((0x08000000&(data))>>27)
#define REGD0_get_p0_b_cdr_rst_n(data)                                ((0x04000000&(data))>>26)
#define REGD0_get_reg_p0_cdr_ckinv_r(data)                            ((0x02000000&(data))>>25)
#define REGD0_get_reg_p0_cdr_ckinv_g(data)                            ((0x01000000&(data))>>24)
#define REGD0_get_reg_p0_cdr_ckinv_b(data)                            ((0x00800000&(data))>>23)
#define REGD0_get_reg_p0_shift_inv_r(data)                            ((0x00400000&(data))>>22)
#define REGD0_get_reg_p0_shift_inv_g(data)                            ((0x00200000&(data))>>21)
#define REGD0_get_reg_p0_shift_inv_b(data)                            ((0x00100000&(data))>>20)
#define REGD0_get_reg_p0_rate_sel(data)                               ((0x000E0000&(data))>>17)
#define REGD0_get_reg_p0_kd(data)                                     ((0x00010000&(data))>>16)
#define REGD0_get_reg_p0_kp(data)                                     ((0x0000FF00&(data))>>8)
#define REGD0_get_reg_p0_ki(data)                                     ((0x000000E0&(data))>>5)
#define REGD0_get_reg_p0_bypass_sdm_int(data)                         ((0x00000010&(data))>>4)
#define REGD0_get_reg_p0_data_order(data)                             ((0x00000008&(data))>>3)
#define REGD0_get_reg_p0_infifo_cnt(data)                             (0x00000007&(data))


#define REGD1                                                         0xb20
#define REGD1_reg_addr                                                "0x98034b20"
#define REGD1_reg                                                     0x98034b20
#define REGD1_inst_addr                                               "0x02C8"
#define REGD1_inst                                                    0x02C8
#define set_REGD1_reg(data)                                           (*((volatile unsigned int*)REGD1_reg)=data)
#define get_REGD1_reg                                                 (*((volatile unsigned int*)REGD1_reg))
#define REGD1_reg_p0_int_init_shift                                   (18)
#define REGD1_reg_p0_acc2_period_shift                                (8)
#define REGD1_reg_p0_squ_tri_shift                                    (7)
#define REGD1_reg_p0_acc2_manual_shift                                (6)
#define REGD1_reg_p0_testout_sel_shift                                (4)
#define REGD1_reg_p0_ercnt_en_shift                                   (3)
#define REGD1_reg_p0_edge_out_shift                                   (2)
#define REGD1_reg_p0_pi_m_mode_shift                                  (1)
#define REGD1_reg_p0_dyn_kp_en_shift                                  (0)
#define REGD1_reg_p0_int_init_mask                                    (0xFFFC0000)
#define REGD1_reg_p0_acc2_period_mask                                 (0x0003FF00)
#define REGD1_reg_p0_squ_tri_mask                                     (0x00000080)
#define REGD1_reg_p0_acc2_manual_mask                                 (0x00000040)
#define REGD1_reg_p0_testout_sel_mask                                 (0x00000030)
#define REGD1_reg_p0_ercnt_en_mask                                    (0x00000008)
#define REGD1_reg_p0_edge_out_mask                                    (0x00000004)
#define REGD1_reg_p0_pi_m_mode_mask                                   (0x00000002)
#define REGD1_reg_p0_dyn_kp_en_mask                                   (0x00000001)
#define REGD1_reg_p0_int_init(data)                                   (0xFFFC0000&((data)<<18))
#define REGD1_reg_p0_acc2_period(data)                                (0x0003FF00&((data)<<8))
#define REGD1_reg_p0_squ_tri(data)                                    (0x00000080&((data)<<7))
#define REGD1_reg_p0_acc2_manual(data)                                (0x00000040&((data)<<6))
#define REGD1_reg_p0_testout_sel(data)                                (0x00000030&((data)<<4))
#define REGD1_reg_p0_ercnt_en(data)                                   (0x00000008&((data)<<3))
#define REGD1_reg_p0_edge_out(data)                                   (0x00000004&((data)<<2))
#define REGD1_reg_p0_pi_m_mode(data)                                  (0x00000002&((data)<<1))
#define REGD1_reg_p0_dyn_kp_en(data)                                  (0x00000001&(data))
#define REGD1_get_reg_p0_int_init(data)                               ((0xFFFC0000&(data))>>18)
#define REGD1_get_reg_p0_acc2_period(data)                            ((0x0003FF00&(data))>>8)
#define REGD1_get_reg_p0_squ_tri(data)                                ((0x00000080&(data))>>7)
#define REGD1_get_reg_p0_acc2_manual(data)                            ((0x00000040&(data))>>6)
#define REGD1_get_reg_p0_testout_sel(data)                            ((0x00000030&(data))>>4)
#define REGD1_get_reg_p0_ercnt_en(data)                               ((0x00000008&(data))>>3)
#define REGD1_get_reg_p0_edge_out(data)                               ((0x00000004&(data))>>2)
#define REGD1_get_reg_p0_pi_m_mode(data)                              ((0x00000002&(data))>>1)
#define REGD1_get_reg_p0_dyn_kp_en(data)                              (0x00000001&(data))


#define REGD2                                                         0xb24
#define REGD2_reg_addr                                                "0x98034b24"
#define REGD2_reg                                                     0x98034b24
#define REGD2_inst_addr                                               "0x02C9"
#define REGD2_inst                                                    0x02C9
#define set_REGD2_reg(data)                                           (*((volatile unsigned int*)REGD2_reg)=data)
#define get_REGD2_reg                                                 (*((volatile unsigned int*)REGD2_reg))
#define REGD2_reg_p0_en_m_value_shift                                 (28)
#define REGD2_reg_p0_st_mode_shift                                    (27)
#define REGD2_reg_p0_timer_lpf_shift                                  (18)
#define REGD2_reg_p0_timer_eq_shift                                   (13)
#define REGD2_reg_p0_timer_ber_shift                                  (8)
#define REGD2_reg_p0_en_m_value_mask                                  (0xF0000000)
#define REGD2_reg_p0_st_mode_mask                                     (0x08000000)
#define REGD2_reg_p0_timer_lpf_mask                                   (0x007C0000)
#define REGD2_reg_p0_timer_eq_mask                                    (0x0003E000)
#define REGD2_reg_p0_timer_ber_mask                                   (0x00001F00)
#define REGD2_reg_p0_en_m_value(data)                                 (0xF0000000&((data)<<28))
#define REGD2_reg_p0_st_mode(data)                                    (0x08000000&((data)<<27))
#define REGD2_reg_p0_timer_lpf(data)                                  (0x007C0000&((data)<<18))
#define REGD2_reg_p0_timer_eq(data)                                   (0x0003E000&((data)<<13))
#define REGD2_reg_p0_timer_ber(data)                                  (0x00001F00&((data)<<8))
#define REGD2_get_reg_p0_en_m_value(data)                             ((0xF0000000&(data))>>28)
#define REGD2_get_reg_p0_st_mode(data)                                ((0x08000000&(data))>>27)
#define REGD2_get_reg_p0_timer_lpf(data)                              ((0x007C0000&(data))>>18)
#define REGD2_get_reg_p0_timer_eq(data)                               ((0x0003E000&(data))>>13)
#define REGD2_get_reg_p0_timer_ber(data)                              ((0x00001F00&(data))>>8)


#define REGD3                                                         0xb28
#define REGD3_reg_addr                                                "0x98034b28"
#define REGD3_reg                                                     0x98034b28
#define REGD3_inst_addr                                               "0x02CA"
#define REGD3_inst                                                    0x02CA
#define set_REGD3_reg(data)                                           (*((volatile unsigned int*)REGD3_reg)=data)
#define get_REGD3_reg                                                 (*((volatile unsigned int*)REGD3_reg))
#define REGD3_p0_st_ro_r_shift                                        (24)
#define REGD3_p0_en_ro_r_shift                                        (20)
#define REGD3_p0_st_ro_g_shift                                        (14)
#define REGD3_p0_en_ro_g_shift                                        (10)
#define REGD3_p0_st_ro_b_shift                                        (4)
#define REGD3_p0_en_ro_b_shift                                        (0)
#define REGD3_p0_st_ro_r_mask                                         (0x1F000000)
#define REGD3_p0_en_ro_r_mask                                         (0x00F00000)
#define REGD3_p0_st_ro_g_mask                                         (0x0007C000)
#define REGD3_p0_en_ro_g_mask                                         (0x00003C00)
#define REGD3_p0_st_ro_b_mask                                         (0x000001F0)
#define REGD3_p0_en_ro_b_mask                                         (0x0000000F)
#define REGD3_p0_st_ro_r(data)                                        (0x1F000000&((data)<<24))
#define REGD3_p0_en_ro_r(data)                                        (0x00F00000&((data)<<20))
#define REGD3_p0_st_ro_g(data)                                        (0x0007C000&((data)<<14))
#define REGD3_p0_en_ro_g(data)                                        (0x00003C00&((data)<<10))
#define REGD3_p0_st_ro_b(data)                                        (0x000001F0&((data)<<4))
#define REGD3_p0_en_ro_b(data)                                        (0x0000000F&(data))
#define REGD3_get_p0_st_ro_r(data)                                    ((0x1F000000&(data))>>24)
#define REGD3_get_p0_en_ro_r(data)                                    ((0x00F00000&(data))>>20)
#define REGD3_get_p0_st_ro_g(data)                                    ((0x0007C000&(data))>>14)
#define REGD3_get_p0_en_ro_g(data)                                    ((0x00003C00&(data))>>10)
#define REGD3_get_p0_st_ro_b(data)                                    ((0x000001F0&(data))>>4)
#define REGD3_get_p0_en_ro_b(data)                                    (0x0000000F&(data))


#define REGD4                                                         0xb2c
#define REGD4_reg_addr                                                "0x98034b2c"
#define REGD4_reg                                                     0x98034b2c
#define REGD4_inst_addr                                               "0x02CB"
#define REGD4_inst                                                    0x02CB
#define set_REGD4_reg(data)                                           (*((volatile unsigned int*)REGD4_reg)=data)
#define get_REGD4_reg                                                 (*((volatile unsigned int*)REGD4_reg))
#define REGD4_p0_er_count_r_shift                                     (20)
#define REGD4_p0_er_count_g_shift                                     (10)
#define REGD4_p0_er_count_b_shift                                     (0)
#define REGD4_p0_er_count_r_mask                                      (0x3FF00000)
#define REGD4_p0_er_count_g_mask                                      (0x000FFC00)
#define REGD4_p0_er_count_b_mask                                      (0x000003FF)
#define REGD4_p0_er_count_r(data)                                     (0x3FF00000&((data)<<20))
#define REGD4_p0_er_count_g(data)                                     (0x000FFC00&((data)<<10))
#define REGD4_p0_er_count_b(data)                                     (0x000003FF&(data))
#define REGD4_get_p0_er_count_r(data)                                 ((0x3FF00000&(data))>>20)
#define REGD4_get_p0_er_count_g(data)                                 ((0x000FFC00&(data))>>10)
#define REGD4_get_p0_er_count_b(data)                                 (0x000003FF&(data))


#define REGD5                                                         0xb30
#define REGD5_reg_addr                                                "0x98034b30"
#define REGD5_reg                                                     0x98034b30
#define REGD5_inst_addr                                               "0x02CC"
#define REGD5_inst                                                    0x02CC
#define set_REGD5_reg(data)                                           (*((volatile unsigned int*)REGD5_reg)=data)
#define get_REGD5_reg                                                 (*((volatile unsigned int*)REGD5_reg))
#define REGD5_p1_r_dig_rst_n_shift                                    (31)
#define REGD5_p1_g_dig_rst_n_shift                                    (30)
#define REGD5_p1_b_dig_rst_n_shift                                    (29)
#define REGD5_p1_r_cdr_rst_n_shift                                    (28)
#define REGD5_p1_g_cdr_rst_n_shift                                    (27)
#define REGD5_p1_b_cdr_rst_n_shift                                    (26)
#define REGD5_reg_p1_cdr_ckinv_r_shift                                (25)
#define REGD5_reg_p1_cdr_ckinv_g_shift                                (24)
#define REGD5_reg_p1_cdr_ckinv_b_shift                                (23)
#define REGD5_reg_p1_shift_inv_r_shift                                (22)
#define REGD5_reg_p1_shift_inv_g_shift                                (21)
#define REGD5_reg_p1_shift_inv_b_shift                                (20)
#define REGD5_reg_p1_rate_sel_shift                                   (17)
#define REGD5_reg_p1_kd_shift                                         (16)
#define REGD5_reg_p1_kp_shift                                         (8)
#define REGD5_reg_p1_ki_shift                                         (5)
#define REGD5_reg_p1_bypass_sdm_int_shift                             (4)
#define REGD5_reg_p1_data_order_shift                                 (3)
#define REGD5_reg_p1_infifo_cnt_shift                                 (0)
#define REGD5_p1_r_dig_rst_n_mask                                     (0x80000000)
#define REGD5_p1_g_dig_rst_n_mask                                     (0x40000000)
#define REGD5_p1_b_dig_rst_n_mask                                     (0x20000000)
#define REGD5_p1_r_cdr_rst_n_mask                                     (0x10000000)
#define REGD5_p1_g_cdr_rst_n_mask                                     (0x08000000)
#define REGD5_p1_b_cdr_rst_n_mask                                     (0x04000000)
#define REGD5_reg_p1_cdr_ckinv_r_mask                                 (0x02000000)
#define REGD5_reg_p1_cdr_ckinv_g_mask                                 (0x01000000)
#define REGD5_reg_p1_cdr_ckinv_b_mask                                 (0x00800000)
#define REGD5_reg_p1_shift_inv_r_mask                                 (0x00400000)
#define REGD5_reg_p1_shift_inv_g_mask                                 (0x00200000)
#define REGD5_reg_p1_shift_inv_b_mask                                 (0x00100000)
#define REGD5_reg_p1_rate_sel_mask                                    (0x000E0000)
#define REGD5_reg_p1_kd_mask                                          (0x00010000)
#define REGD5_reg_p1_kp_mask                                          (0x0000FF00)
#define REGD5_reg_p1_ki_mask                                          (0x000000E0)
#define REGD5_reg_p1_bypass_sdm_int_mask                              (0x00000010)
#define REGD5_reg_p1_data_order_mask                                  (0x00000008)
#define REGD5_reg_p1_infifo_cnt_mask                                  (0x00000007)
#define REGD5_p1_r_dig_rst_n(data)                                    (0x80000000&((data)<<31))
#define REGD5_p1_g_dig_rst_n(data)                                    (0x40000000&((data)<<30))
#define REGD5_p1_b_dig_rst_n(data)                                    (0x20000000&((data)<<29))
#define REGD5_p1_r_cdr_rst_n(data)                                    (0x10000000&((data)<<28))
#define REGD5_p1_g_cdr_rst_n(data)                                    (0x08000000&((data)<<27))
#define REGD5_p1_b_cdr_rst_n(data)                                    (0x04000000&((data)<<26))
#define REGD5_reg_p1_cdr_ckinv_r(data)                                (0x02000000&((data)<<25))
#define REGD5_reg_p1_cdr_ckinv_g(data)                                (0x01000000&((data)<<24))
#define REGD5_reg_p1_cdr_ckinv_b(data)                                (0x00800000&((data)<<23))
#define REGD5_reg_p1_shift_inv_r(data)                                (0x00400000&((data)<<22))
#define REGD5_reg_p1_shift_inv_g(data)                                (0x00200000&((data)<<21))
#define REGD5_reg_p1_shift_inv_b(data)                                (0x00100000&((data)<<20))
#define REGD5_reg_p1_rate_sel(data)                                   (0x000E0000&((data)<<17))
#define REGD5_reg_p1_kd(data)                                         (0x00010000&((data)<<16))
#define REGD5_reg_p1_kp(data)                                         (0x0000FF00&((data)<<8))
#define REGD5_reg_p1_ki(data)                                         (0x000000E0&((data)<<5))
#define REGD5_reg_p1_bypass_sdm_int(data)                             (0x00000010&((data)<<4))
#define REGD5_reg_p1_data_order(data)                                 (0x00000008&((data)<<3))
#define REGD5_reg_p1_infifo_cnt(data)                                 (0x00000007&(data))
#define REGD5_get_p1_r_dig_rst_n(data)                                ((0x80000000&(data))>>31)
#define REGD5_get_p1_g_dig_rst_n(data)                                ((0x40000000&(data))>>30)
#define REGD5_get_p1_b_dig_rst_n(data)                                ((0x20000000&(data))>>29)
#define REGD5_get_p1_r_cdr_rst_n(data)                                ((0x10000000&(data))>>28)
#define REGD5_get_p1_g_cdr_rst_n(data)                                ((0x08000000&(data))>>27)
#define REGD5_get_p1_b_cdr_rst_n(data)                                ((0x04000000&(data))>>26)
#define REGD5_get_reg_p1_cdr_ckinv_r(data)                            ((0x02000000&(data))>>25)
#define REGD5_get_reg_p1_cdr_ckinv_g(data)                            ((0x01000000&(data))>>24)
#define REGD5_get_reg_p1_cdr_ckinv_b(data)                            ((0x00800000&(data))>>23)
#define REGD5_get_reg_p1_shift_inv_r(data)                            ((0x00400000&(data))>>22)
#define REGD5_get_reg_p1_shift_inv_g(data)                            ((0x00200000&(data))>>21)
#define REGD5_get_reg_p1_shift_inv_b(data)                            ((0x00100000&(data))>>20)
#define REGD5_get_reg_p1_rate_sel(data)                               ((0x000E0000&(data))>>17)
#define REGD5_get_reg_p1_kd(data)                                     ((0x00010000&(data))>>16)
#define REGD5_get_reg_p1_kp(data)                                     ((0x0000FF00&(data))>>8)
#define REGD5_get_reg_p1_ki(data)                                     ((0x000000E0&(data))>>5)
#define REGD5_get_reg_p1_bypass_sdm_int(data)                         ((0x00000010&(data))>>4)
#define REGD5_get_reg_p1_data_order(data)                             ((0x00000008&(data))>>3)
#define REGD5_get_reg_p1_infifo_cnt(data)                             (0x00000007&(data))


#define REGD6                                                         0xb34
#define REGD6_reg_addr                                                "0x98034b34"
#define REGD6_reg                                                     0x98034b34
#define REGD6_inst_addr                                               "0x02CD"
#define REGD6_inst                                                    0x02CD
#define set_REGD6_reg(data)                                           (*((volatile unsigned int*)REGD6_reg)=data)
#define get_REGD6_reg                                                 (*((volatile unsigned int*)REGD6_reg))
#define REGD6_reg_p1_int_init_shift                                   (18)
#define REGD6_reg_p1_acc2_period_shift                                (8)
#define REGD6_reg_p1_squ_tri_shift                                    (7)
#define REGD6_reg_p1_acc2_manual_shift                                (6)
#define REGD6_reg_p1_testout_sel_shift                                (4)
#define REGD6_reg_p1_ercnt_en_shift                                   (3)
#define REGD6_reg_p1_edge_out_shift                                   (2)
#define REGD6_reg_p1_pi_m_mode_shift                                  (1)
#define REGD6_reg_p1_dyn_kp_en_shift                                  (0)
#define REGD6_reg_p1_int_init_mask                                    (0xFFFC0000)
#define REGD6_reg_p1_acc2_period_mask                                 (0x0003FF00)
#define REGD6_reg_p1_squ_tri_mask                                     (0x00000080)
#define REGD6_reg_p1_acc2_manual_mask                                 (0x00000040)
#define REGD6_reg_p1_testout_sel_mask                                 (0x00000030)
#define REGD6_reg_p1_ercnt_en_mask                                    (0x00000008)
#define REGD6_reg_p1_edge_out_mask                                    (0x00000004)
#define REGD6_reg_p1_pi_m_mode_mask                                   (0x00000002)
#define REGD6_reg_p1_dyn_kp_en_mask                                   (0x00000001)
#define REGD6_reg_p1_int_init(data)                                   (0xFFFC0000&((data)<<18))
#define REGD6_reg_p1_acc2_period(data)                                (0x0003FF00&((data)<<8))
#define REGD6_reg_p1_squ_tri(data)                                    (0x00000080&((data)<<7))
#define REGD6_reg_p1_acc2_manual(data)                                (0x00000040&((data)<<6))
#define REGD6_reg_p1_testout_sel(data)                                (0x00000030&((data)<<4))
#define REGD6_reg_p1_ercnt_en(data)                                   (0x00000008&((data)<<3))
#define REGD6_reg_p1_edge_out(data)                                   (0x00000004&((data)<<2))
#define REGD6_reg_p1_pi_m_mode(data)                                  (0x00000002&((data)<<1))
#define REGD6_reg_p1_dyn_kp_en(data)                                  (0x00000001&(data))
#define REGD6_get_reg_p1_int_init(data)                               ((0xFFFC0000&(data))>>18)
#define REGD6_get_reg_p1_acc2_period(data)                            ((0x0003FF00&(data))>>8)
#define REGD6_get_reg_p1_squ_tri(data)                                ((0x00000080&(data))>>7)
#define REGD6_get_reg_p1_acc2_manual(data)                            ((0x00000040&(data))>>6)
#define REGD6_get_reg_p1_testout_sel(data)                            ((0x00000030&(data))>>4)
#define REGD6_get_reg_p1_ercnt_en(data)                               ((0x00000008&(data))>>3)
#define REGD6_get_reg_p1_edge_out(data)                               ((0x00000004&(data))>>2)
#define REGD6_get_reg_p1_pi_m_mode(data)                              ((0x00000002&(data))>>1)
#define REGD6_get_reg_p1_dyn_kp_en(data)                              (0x00000001&(data))


#define REGD7                                                         0xb38
#define REGD7_reg_addr                                                "0x98034b38"
#define REGD7_reg                                                     0x98034b38
#define REGD7_inst_addr                                               "0x02CE"
#define REGD7_inst                                                    0x02CE
#define set_REGD7_reg(data)                                           (*((volatile unsigned int*)REGD7_reg)=data)
#define get_REGD7_reg                                                 (*((volatile unsigned int*)REGD7_reg))
#define REGD7_reg_p1_en_m_value_shift                                 (28)
#define REGD7_reg_p1_st_mode_shift                                    (27)
#define REGD7_reg_p1_timer_lpf_shift                                  (18)
#define REGD7_reg_p1_timer_eq_shift                                   (13)
#define REGD7_reg_p1_timer_ber_shift                                  (8)
#define REGD7_reg_p1_en_m_value_mask                                  (0xF0000000)
#define REGD7_reg_p1_st_mode_mask                                     (0x08000000)
#define REGD7_reg_p1_timer_lpf_mask                                   (0x007C0000)
#define REGD7_reg_p1_timer_eq_mask                                    (0x0003E000)
#define REGD7_reg_p1_timer_ber_mask                                   (0x00001F00)
#define REGD7_reg_p1_en_m_value(data)                                 (0xF0000000&((data)<<28))
#define REGD7_reg_p1_st_mode(data)                                    (0x08000000&((data)<<27))
#define REGD7_reg_p1_timer_lpf(data)                                  (0x007C0000&((data)<<18))
#define REGD7_reg_p1_timer_eq(data)                                   (0x0003E000&((data)<<13))
#define REGD7_reg_p1_timer_ber(data)                                  (0x00001F00&((data)<<8))
#define REGD7_get_reg_p1_en_m_value(data)                             ((0xF0000000&(data))>>28)
#define REGD7_get_reg_p1_st_mode(data)                                ((0x08000000&(data))>>27)
#define REGD7_get_reg_p1_timer_lpf(data)                              ((0x007C0000&(data))>>18)
#define REGD7_get_reg_p1_timer_eq(data)                               ((0x0003E000&(data))>>13)
#define REGD7_get_reg_p1_timer_ber(data)                              ((0x00001F00&(data))>>8)


#define REGD8                                                         0xb3c
#define REGD8_reg_addr                                                "0x98034b3c"
#define REGD8_reg                                                     0x98034b3c
#define REGD8_inst_addr                                               "0x02CF"
#define REGD8_inst                                                    0x02CF
#define set_REGD8_reg(data)                                           (*((volatile unsigned int*)REGD8_reg)=data)
#define get_REGD8_reg                                                 (*((volatile unsigned int*)REGD8_reg))
#define REGD8_p1_st_ro_r_shift                                        (24)
#define REGD8_p1_en_ro_r_shift                                        (20)
#define REGD8_p1_st_ro_g_shift                                        (14)
#define REGD8_p1_en_ro_g_shift                                        (10)
#define REGD8_p1_st_ro_b_shift                                        (4)
#define REGD8_p1_en_ro_b_shift                                        (0)
#define REGD8_p1_st_ro_r_mask                                         (0x1F000000)
#define REGD8_p1_en_ro_r_mask                                         (0x00F00000)
#define REGD8_p1_st_ro_g_mask                                         (0x0007C000)
#define REGD8_p1_en_ro_g_mask                                         (0x00003C00)
#define REGD8_p1_st_ro_b_mask                                         (0x000001F0)
#define REGD8_p1_en_ro_b_mask                                         (0x0000000F)
#define REGD8_p1_st_ro_r(data)                                        (0x1F000000&((data)<<24))
#define REGD8_p1_en_ro_r(data)                                        (0x00F00000&((data)<<20))
#define REGD8_p1_st_ro_g(data)                                        (0x0007C000&((data)<<14))
#define REGD8_p1_en_ro_g(data)                                        (0x00003C00&((data)<<10))
#define REGD8_p1_st_ro_b(data)                                        (0x000001F0&((data)<<4))
#define REGD8_p1_en_ro_b(data)                                        (0x0000000F&(data))
#define REGD8_get_p1_st_ro_r(data)                                    ((0x1F000000&(data))>>24)
#define REGD8_get_p1_en_ro_r(data)                                    ((0x00F00000&(data))>>20)
#define REGD8_get_p1_st_ro_g(data)                                    ((0x0007C000&(data))>>14)
#define REGD8_get_p1_en_ro_g(data)                                    ((0x00003C00&(data))>>10)
#define REGD8_get_p1_st_ro_b(data)                                    ((0x000001F0&(data))>>4)
#define REGD8_get_p1_en_ro_b(data)                                    (0x0000000F&(data))


#define REGD9                                                         0xb40
#define REGD9_reg_addr                                                "0x98034b40"
#define REGD9_reg                                                     0x98034b40
#define REGD9_inst_addr                                               "0x02D0"
#define REGD9_inst                                                    0x02D0
#define set_REGD9_reg(data)                                           (*((volatile unsigned int*)REGD9_reg)=data)
#define get_REGD9_reg                                                 (*((volatile unsigned int*)REGD9_reg))
#define REGD9_p1_er_count_r_shift                                     (20)
#define REGD9_p1_er_count_g_shift                                     (10)
#define REGD9_p1_er_count_b_shift                                     (0)
#define REGD9_p1_er_count_r_mask                                      (0x3FF00000)
#define REGD9_p1_er_count_g_mask                                      (0x000FFC00)
#define REGD9_p1_er_count_b_mask                                      (0x000003FF)
#define REGD9_p1_er_count_r(data)                                     (0x3FF00000&((data)<<20))
#define REGD9_p1_er_count_g(data)                                     (0x000FFC00&((data)<<10))
#define REGD9_p1_er_count_b(data)                                     (0x000003FF&(data))
#define REGD9_get_p1_er_count_r(data)                                 ((0x3FF00000&(data))>>20)
#define REGD9_get_p1_er_count_g(data)                                 ((0x000FFC00&(data))>>10)
#define REGD9_get_p1_er_count_b(data)                                 (0x000003FF&(data))


#define REGD10                                                        0xb44
#define REGD10_reg_addr                                               "0x98034b44"
#define REGD10_reg                                                    0x98034b44
#define REGD10_inst_addr                                              "0x02D1"
#define REGD10_inst                                                   0x02D1
#define set_REGD10_reg(data)                                          (*((volatile unsigned int*)REGD10_reg)=data)
#define get_REGD10_reg                                                (*((volatile unsigned int*)REGD10_reg))
#define REGD10_p2_r_dig_rst_n_shift                                   (31)
#define REGD10_p2_g_dig_rst_n_shift                                   (30)
#define REGD10_p2_b_dig_rst_n_shift                                   (29)
#define REGD10_p2_r_cdr_rst_n_shift                                   (28)
#define REGD10_p2_g_cdr_rst_n_shift                                   (27)
#define REGD10_p2_b_cdr_rst_n_shift                                   (26)
#define REGD10_reg_p2_cdr_ckinv_r_shift                               (25)
#define REGD10_reg_p2_cdr_ckinv_g_shift                               (24)
#define REGD10_reg_p2_cdr_ckinv_b_shift                               (23)
#define REGD10_reg_p2_shift_inv_r_shift                               (22)
#define REGD10_reg_p2_shift_inv_g_shift                               (21)
#define REGD10_reg_p2_shift_inv_b_shift                               (20)
#define REGD10_reg_p2_rate_sel_shift                                  (17)
#define REGD10_reg_p2_kd_shift                                        (16)
#define REGD10_reg_p2_kp_shift                                        (8)
#define REGD10_reg_p2_ki_shift                                        (5)
#define REGD10_reg_p2_bypass_sdm_int_shift                            (4)
#define REGD10_reg_p2_data_order_shift                                (3)
#define REGD10_reg_p2_infifo_cnt_shift                                (0)
#define REGD10_p2_r_dig_rst_n_mask                                    (0x80000000)
#define REGD10_p2_g_dig_rst_n_mask                                    (0x40000000)
#define REGD10_p2_b_dig_rst_n_mask                                    (0x20000000)
#define REGD10_p2_r_cdr_rst_n_mask                                    (0x10000000)
#define REGD10_p2_g_cdr_rst_n_mask                                    (0x08000000)
#define REGD10_p2_b_cdr_rst_n_mask                                    (0x04000000)
#define REGD10_reg_p2_cdr_ckinv_r_mask                                (0x02000000)
#define REGD10_reg_p2_cdr_ckinv_g_mask                                (0x01000000)
#define REGD10_reg_p2_cdr_ckinv_b_mask                                (0x00800000)
#define REGD10_reg_p2_shift_inv_r_mask                                (0x00400000)
#define REGD10_reg_p2_shift_inv_g_mask                                (0x00200000)
#define REGD10_reg_p2_shift_inv_b_mask                                (0x00100000)
#define REGD10_reg_p2_rate_sel_mask                                   (0x000E0000)
#define REGD10_reg_p2_kd_mask                                         (0x00010000)
#define REGD10_reg_p2_kp_mask                                         (0x0000FF00)
#define REGD10_reg_p2_ki_mask                                         (0x000000E0)
#define REGD10_reg_p2_bypass_sdm_int_mask                             (0x00000010)
#define REGD10_reg_p2_data_order_mask                                 (0x00000008)
#define REGD10_reg_p2_infifo_cnt_mask                                 (0x00000007)
#define REGD10_p2_r_dig_rst_n(data)                                   (0x80000000&((data)<<31))
#define REGD10_p2_g_dig_rst_n(data)                                   (0x40000000&((data)<<30))
#define REGD10_p2_b_dig_rst_n(data)                                   (0x20000000&((data)<<29))
#define REGD10_p2_r_cdr_rst_n(data)                                   (0x10000000&((data)<<28))
#define REGD10_p2_g_cdr_rst_n(data)                                   (0x08000000&((data)<<27))
#define REGD10_p2_b_cdr_rst_n(data)                                   (0x04000000&((data)<<26))
#define REGD10_reg_p2_cdr_ckinv_r(data)                               (0x02000000&((data)<<25))
#define REGD10_reg_p2_cdr_ckinv_g(data)                               (0x01000000&((data)<<24))
#define REGD10_reg_p2_cdr_ckinv_b(data)                               (0x00800000&((data)<<23))
#define REGD10_reg_p2_shift_inv_r(data)                               (0x00400000&((data)<<22))
#define REGD10_reg_p2_shift_inv_g(data)                               (0x00200000&((data)<<21))
#define REGD10_reg_p2_shift_inv_b(data)                               (0x00100000&((data)<<20))
#define REGD10_reg_p2_rate_sel(data)                                  (0x000E0000&((data)<<17))
#define REGD10_reg_p2_kd(data)                                        (0x00010000&((data)<<16))
#define REGD10_reg_p2_kp(data)                                        (0x0000FF00&((data)<<8))
#define REGD10_reg_p2_ki(data)                                        (0x000000E0&((data)<<5))
#define REGD10_reg_p2_bypass_sdm_int(data)                            (0x00000010&((data)<<4))
#define REGD10_reg_p2_data_order(data)                                (0x00000008&((data)<<3))
#define REGD10_reg_p2_infifo_cnt(data)                                (0x00000007&(data))
#define REGD10_get_p2_r_dig_rst_n(data)                               ((0x80000000&(data))>>31)
#define REGD10_get_p2_g_dig_rst_n(data)                               ((0x40000000&(data))>>30)
#define REGD10_get_p2_b_dig_rst_n(data)                               ((0x20000000&(data))>>29)
#define REGD10_get_p2_r_cdr_rst_n(data)                               ((0x10000000&(data))>>28)
#define REGD10_get_p2_g_cdr_rst_n(data)                               ((0x08000000&(data))>>27)
#define REGD10_get_p2_b_cdr_rst_n(data)                               ((0x04000000&(data))>>26)
#define REGD10_get_reg_p2_cdr_ckinv_r(data)                           ((0x02000000&(data))>>25)
#define REGD10_get_reg_p2_cdr_ckinv_g(data)                           ((0x01000000&(data))>>24)
#define REGD10_get_reg_p2_cdr_ckinv_b(data)                           ((0x00800000&(data))>>23)
#define REGD10_get_reg_p2_shift_inv_r(data)                           ((0x00400000&(data))>>22)
#define REGD10_get_reg_p2_shift_inv_g(data)                           ((0x00200000&(data))>>21)
#define REGD10_get_reg_p2_shift_inv_b(data)                           ((0x00100000&(data))>>20)
#define REGD10_get_reg_p2_rate_sel(data)                              ((0x000E0000&(data))>>17)
#define REGD10_get_reg_p2_kd(data)                                    ((0x00010000&(data))>>16)
#define REGD10_get_reg_p2_kp(data)                                    ((0x0000FF00&(data))>>8)
#define REGD10_get_reg_p2_ki(data)                                    ((0x000000E0&(data))>>5)
#define REGD10_get_reg_p2_bypass_sdm_int(data)                        ((0x00000010&(data))>>4)
#define REGD10_get_reg_p2_data_order(data)                            ((0x00000008&(data))>>3)
#define REGD10_get_reg_p2_infifo_cnt(data)                            (0x00000007&(data))


#define REGD11                                                        0xb48
#define REGD11_reg_addr                                               "0x98034b48"
#define REGD11_reg                                                    0x98034b48
#define REGD11_inst_addr                                              "0x02D2"
#define REGD11_inst                                                   0x02D2
#define set_REGD11_reg(data)                                          (*((volatile unsigned int*)REGD11_reg)=data)
#define get_REGD11_reg                                                (*((volatile unsigned int*)REGD11_reg))
#define REGD11_reg_p2_int_init_shift                                  (18)
#define REGD11_reg_p2_acc2_period_shift                               (8)
#define REGD11_reg_p2_squ_tri_shift                                   (7)
#define REGD11_reg_p2_acc2_manual_shift                               (6)
#define REGD11_reg_p2_testout_sel_shift                               (4)
#define REGD11_reg_p2_ercnt_en_shift                                  (3)
#define REGD11_reg_p2_edge_out_shift                                  (2)
#define REGD11_reg_p2_pi_m_mode_shift                                 (1)
#define REGD11_reg_p2_dyn_kp_en_shift                                 (0)
#define REGD11_reg_p2_int_init_mask                                   (0xFFFC0000)
#define REGD11_reg_p2_acc2_period_mask                                (0x0003FF00)
#define REGD11_reg_p2_squ_tri_mask                                    (0x00000080)
#define REGD11_reg_p2_acc2_manual_mask                                (0x00000040)
#define REGD11_reg_p2_testout_sel_mask                                (0x00000030)
#define REGD11_reg_p2_ercnt_en_mask                                   (0x00000008)
#define REGD11_reg_p2_edge_out_mask                                   (0x00000004)
#define REGD11_reg_p2_pi_m_mode_mask                                  (0x00000002)
#define REGD11_reg_p2_dyn_kp_en_mask                                  (0x00000001)
#define REGD11_reg_p2_int_init(data)                                  (0xFFFC0000&((data)<<18))
#define REGD11_reg_p2_acc2_period(data)                               (0x0003FF00&((data)<<8))
#define REGD11_reg_p2_squ_tri(data)                                   (0x00000080&((data)<<7))
#define REGD11_reg_p2_acc2_manual(data)                               (0x00000040&((data)<<6))
#define REGD11_reg_p2_testout_sel(data)                               (0x00000030&((data)<<4))
#define REGD11_reg_p2_ercnt_en(data)                                  (0x00000008&((data)<<3))
#define REGD11_reg_p2_edge_out(data)                                  (0x00000004&((data)<<2))
#define REGD11_reg_p2_pi_m_mode(data)                                 (0x00000002&((data)<<1))
#define REGD11_reg_p2_dyn_kp_en(data)                                 (0x00000001&(data))
#define REGD11_get_reg_p2_int_init(data)                              ((0xFFFC0000&(data))>>18)
#define REGD11_get_reg_p2_acc2_period(data)                           ((0x0003FF00&(data))>>8)
#define REGD11_get_reg_p2_squ_tri(data)                               ((0x00000080&(data))>>7)
#define REGD11_get_reg_p2_acc2_manual(data)                           ((0x00000040&(data))>>6)
#define REGD11_get_reg_p2_testout_sel(data)                           ((0x00000030&(data))>>4)
#define REGD11_get_reg_p2_ercnt_en(data)                              ((0x00000008&(data))>>3)
#define REGD11_get_reg_p2_edge_out(data)                              ((0x00000004&(data))>>2)
#define REGD11_get_reg_p2_pi_m_mode(data)                             ((0x00000002&(data))>>1)
#define REGD11_get_reg_p2_dyn_kp_en(data)                             (0x00000001&(data))


#define REGD12                                                        0xb4c
#define REGD12_reg_addr                                               "0x98034b4c"
#define REGD12_reg                                                    0x98034b4c
#define REGD12_inst_addr                                              "0x02D3"
#define REGD12_inst                                                   0x02D3
#define set_REGD12_reg(data)                                          (*((volatile unsigned int*)REGD12_reg)=data)
#define get_REGD12_reg                                                (*((volatile unsigned int*)REGD12_reg))
#define REGD12_reg_p2_en_m_value_shift                                (28)
#define REGD12_reg_p2_st_mode_shift                                   (27)
#define REGD12_reg_p2_timer_lpf_shift                                 (18)
#define REGD12_reg_p2_timer_eq_shift                                  (13)
#define REGD12_reg_p2_timer_ber_shift                                 (8)
#define REGD12_reg_p2_en_m_value_mask                                 (0xF0000000)
#define REGD12_reg_p2_st_mode_mask                                    (0x08000000)
#define REGD12_reg_p2_timer_lpf_mask                                  (0x007C0000)
#define REGD12_reg_p2_timer_eq_mask                                   (0x0003E000)
#define REGD12_reg_p2_timer_ber_mask                                  (0x00001F00)
#define REGD12_reg_p2_en_m_value(data)                                (0xF0000000&((data)<<28))
#define REGD12_reg_p2_st_mode(data)                                   (0x08000000&((data)<<27))
#define REGD12_reg_p2_timer_lpf(data)                                 (0x007C0000&((data)<<18))
#define REGD12_reg_p2_timer_eq(data)                                  (0x0003E000&((data)<<13))
#define REGD12_reg_p2_timer_ber(data)                                 (0x00001F00&((data)<<8))
#define REGD12_get_reg_p2_en_m_value(data)                            ((0xF0000000&(data))>>28)
#define REGD12_get_reg_p2_st_mode(data)                               ((0x08000000&(data))>>27)
#define REGD12_get_reg_p2_timer_lpf(data)                             ((0x007C0000&(data))>>18)
#define REGD12_get_reg_p2_timer_eq(data)                              ((0x0003E000&(data))>>13)
#define REGD12_get_reg_p2_timer_ber(data)                             ((0x00001F00&(data))>>8)


#define REGD13                                                        0xb50
#define REGD13_reg_addr                                               "0x98034b50"
#define REGD13_reg                                                    0x98034b50
#define REGD13_inst_addr                                              "0x02D4"
#define REGD13_inst                                                   0x02D4
#define set_REGD13_reg(data)                                          (*((volatile unsigned int*)REGD13_reg)=data)
#define get_REGD13_reg                                                (*((volatile unsigned int*)REGD13_reg))
#define REGD13_p2_st_ro_r_shift                                       (24)
#define REGD13_p2_en_ro_r_shift                                       (20)
#define REGD13_p2_st_ro_g_shift                                       (14)
#define REGD13_p2_en_ro_g_shift                                       (10)
#define REGD13_p2_st_ro_b_shift                                       (4)
#define REGD13_p2_en_ro_b_shift                                       (0)
#define REGD13_p2_st_ro_r_mask                                        (0x1F000000)
#define REGD13_p2_en_ro_r_mask                                        (0x00F00000)
#define REGD13_p2_st_ro_g_mask                                        (0x0007C000)
#define REGD13_p2_en_ro_g_mask                                        (0x00003C00)
#define REGD13_p2_st_ro_b_mask                                        (0x000001F0)
#define REGD13_p2_en_ro_b_mask                                        (0x0000000F)
#define REGD13_p2_st_ro_r(data)                                       (0x1F000000&((data)<<24))
#define REGD13_p2_en_ro_r(data)                                       (0x00F00000&((data)<<20))
#define REGD13_p2_st_ro_g(data)                                       (0x0007C000&((data)<<14))
#define REGD13_p2_en_ro_g(data)                                       (0x00003C00&((data)<<10))
#define REGD13_p2_st_ro_b(data)                                       (0x000001F0&((data)<<4))
#define REGD13_p2_en_ro_b(data)                                       (0x0000000F&(data))
#define REGD13_get_p2_st_ro_r(data)                                   ((0x1F000000&(data))>>24)
#define REGD13_get_p2_en_ro_r(data)                                   ((0x00F00000&(data))>>20)
#define REGD13_get_p2_st_ro_g(data)                                   ((0x0007C000&(data))>>14)
#define REGD13_get_p2_en_ro_g(data)                                   ((0x00003C00&(data))>>10)
#define REGD13_get_p2_st_ro_b(data)                                   ((0x000001F0&(data))>>4)
#define REGD13_get_p2_en_ro_b(data)                                   (0x0000000F&(data))


#define REGD14                                                        0xb54
#define REGD14_reg_addr                                               "0x98034b54"
#define REGD14_reg                                                    0x98034b54
#define REGD14_inst_addr                                              "0x02D5"
#define REGD14_inst                                                   0x02D5
#define set_REGD14_reg(data)                                          (*((volatile unsigned int*)REGD14_reg)=data)
#define get_REGD14_reg                                                (*((volatile unsigned int*)REGD14_reg))
#define REGD14_p2_er_count_r_shift                                    (20)
#define REGD14_p2_er_count_g_shift                                    (10)
#define REGD14_p2_er_count_b_shift                                    (0)
#define REGD14_p2_er_count_r_mask                                     (0x3FF00000)
#define REGD14_p2_er_count_g_mask                                     (0x000FFC00)
#define REGD14_p2_er_count_b_mask                                     (0x000003FF)
#define REGD14_p2_er_count_r(data)                                    (0x3FF00000&((data)<<20))
#define REGD14_p2_er_count_g(data)                                    (0x000FFC00&((data)<<10))
#define REGD14_p2_er_count_b(data)                                    (0x000003FF&(data))
#define REGD14_get_p2_er_count_r(data)                                ((0x3FF00000&(data))>>20)
#define REGD14_get_p2_er_count_g(data)                                ((0x000FFC00&(data))>>10)
#define REGD14_get_p2_er_count_b(data)                                (0x000003FF&(data))


#define REGD15                                                        0xb58
#define REGD15_reg_addr                                               "0x98034b58"
#define REGD15_reg                                                    0x98034b58
#define REGD15_inst_addr                                              "0x02D6"
#define REGD15_inst                                                   0x02D6
#define set_REGD15_reg(data)                                          (*((volatile unsigned int*)REGD15_reg)=data)
#define get_REGD15_reg                                                (*((volatile unsigned int*)REGD15_reg))
#define REGD15_reg_p0_bypass_clk_rdy_shift                            (31)
#define REGD15_reg_p0_bypass_eqen_rdy_shift                           (30)
#define REGD15_reg_p0_bypass_data_rdy_shift                           (29)
#define REGD15_reg_p0_bypass_pi_shift                                 (28)
#define REGD15_reg_p0_data_rdy_time_shift                             (24)
#define REGD15_reg_p0_en_clkout_manual_shift                          (23)
#define REGD15_reg_p0_en_eqen_manual_shift                            (22)
#define REGD15_reg_p0_en_data_manual_shift                            (21)
#define REGD15_reg_p0_eqen_rdy_time_shift                             (17)
#define REGD15_reg_p0_order_shift                                     (16)
#define REGD15_reg_p0_pll_wd_base_time_shift                          (13)
#define REGD15_reg_p0_pll_wd_en_shift                                 (12)
#define REGD15_reg_p0_pll_wd_rst_wid_shift                            (10)
#define REGD15_reg_p0_pll_wd_time_rdy_shift                           (8)
#define REGD15_reg_p0_acdr_l0_en_shift                                (7)
#define REGD15_reg_p0_bypass_eqen_rdy_l0_shift                        (6)
#define REGD15_reg_p0_bypass_data_rdy_l0_shift                        (5)
#define REGD15_reg_p0_en_eqen_manual_l0_shift                         (4)
#define REGD15_reg_p0_en_data_manual_l0_shift                         (3)
#define REGD15_p0_pll_wd_ckrdy_ro_shift                               (2)
#define REGD15_p0_pll_wd_rst_wc_shift                                 (1)
#define REGD15_p0_wdog_rst_n_shift                                    (0)
#define REGD15_reg_p0_bypass_clk_rdy_mask                             (0x80000000)
#define REGD15_reg_p0_bypass_eqen_rdy_mask                            (0x40000000)
#define REGD15_reg_p0_bypass_data_rdy_mask                            (0x20000000)
#define REGD15_reg_p0_bypass_pi_mask                                  (0x10000000)
#define REGD15_reg_p0_data_rdy_time_mask                              (0x0F000000)
#define REGD15_reg_p0_en_clkout_manual_mask                           (0x00800000)
#define REGD15_reg_p0_en_eqen_manual_mask                             (0x00400000)
#define REGD15_reg_p0_en_data_manual_mask                             (0x00200000)
#define REGD15_reg_p0_eqen_rdy_time_mask                              (0x001E0000)
#define REGD15_reg_p0_order_mask                                      (0x00010000)
#define REGD15_reg_p0_pll_wd_base_time_mask                           (0x0000E000)
#define REGD15_reg_p0_pll_wd_en_mask                                  (0x00001000)
#define REGD15_reg_p0_pll_wd_rst_wid_mask                             (0x00000C00)
#define REGD15_reg_p0_pll_wd_time_rdy_mask                            (0x00000300)
#define REGD15_reg_p0_acdr_l0_en_mask                                 (0x00000080)
#define REGD15_reg_p0_bypass_eqen_rdy_l0_mask                         (0x00000040)
#define REGD15_reg_p0_bypass_data_rdy_l0_mask                         (0x00000020)
#define REGD15_reg_p0_en_eqen_manual_l0_mask                          (0x00000010)
#define REGD15_reg_p0_en_data_manual_l0_mask                          (0x00000008)
#define REGD15_p0_pll_wd_ckrdy_ro_mask                                (0x00000004)
#define REGD15_p0_pll_wd_rst_wc_mask                                  (0x00000002)
#define REGD15_p0_wdog_rst_n_mask                                     (0x00000001)
#define REGD15_reg_p0_bypass_clk_rdy(data)                            (0x80000000&((data)<<31))
#define REGD15_reg_p0_bypass_eqen_rdy(data)                           (0x40000000&((data)<<30))
#define REGD15_reg_p0_bypass_data_rdy(data)                           (0x20000000&((data)<<29))
#define REGD15_reg_p0_bypass_pi(data)                                 (0x10000000&((data)<<28))
#define REGD15_reg_p0_data_rdy_time(data)                             (0x0F000000&((data)<<24))
#define REGD15_reg_p0_en_clkout_manual(data)                          (0x00800000&((data)<<23))
#define REGD15_reg_p0_en_eqen_manual(data)                            (0x00400000&((data)<<22))
#define REGD15_reg_p0_en_data_manual(data)                            (0x00200000&((data)<<21))
#define REGD15_reg_p0_eqen_rdy_time(data)                             (0x001E0000&((data)<<17))
#define REGD15_reg_p0_order(data)                                     (0x00010000&((data)<<16))
#define REGD15_reg_p0_pll_wd_base_time(data)                          (0x0000E000&((data)<<13))
#define REGD15_reg_p0_pll_wd_en(data)                                 (0x00001000&((data)<<12))
#define REGD15_reg_p0_pll_wd_rst_wid(data)                            (0x00000C00&((data)<<10))
#define REGD15_reg_p0_pll_wd_time_rdy(data)                           (0x00000300&((data)<<8))
#define REGD15_reg_p0_acdr_l0_en(data)                                (0x00000080&((data)<<7))
#define REGD15_reg_p0_bypass_eqen_rdy_l0(data)                        (0x00000040&((data)<<6))
#define REGD15_reg_p0_bypass_data_rdy_l0(data)                        (0x00000020&((data)<<5))
#define REGD15_reg_p0_en_eqen_manual_l0(data)                         (0x00000010&((data)<<4))
#define REGD15_reg_p0_en_data_manual_l0(data)                         (0x00000008&((data)<<3))
#define REGD15_p0_pll_wd_ckrdy_ro(data)                               (0x00000004&((data)<<2))
#define REGD15_p0_pll_wd_rst_wc(data)                                 (0x00000002&((data)<<1))
#define REGD15_p0_wdog_rst_n(data)                                    (0x00000001&(data))
#define REGD15_get_reg_p0_bypass_clk_rdy(data)                        ((0x80000000&(data))>>31)
#define REGD15_get_reg_p0_bypass_eqen_rdy(data)                       ((0x40000000&(data))>>30)
#define REGD15_get_reg_p0_bypass_data_rdy(data)                       ((0x20000000&(data))>>29)
#define REGD15_get_reg_p0_bypass_pi(data)                             ((0x10000000&(data))>>28)
#define REGD15_get_reg_p0_data_rdy_time(data)                         ((0x0F000000&(data))>>24)
#define REGD15_get_reg_p0_en_clkout_manual(data)                      ((0x00800000&(data))>>23)
#define REGD15_get_reg_p0_en_eqen_manual(data)                        ((0x00400000&(data))>>22)
#define REGD15_get_reg_p0_en_data_manual(data)                        ((0x00200000&(data))>>21)
#define REGD15_get_reg_p0_eqen_rdy_time(data)                         ((0x001E0000&(data))>>17)
#define REGD15_get_reg_p0_order(data)                                 ((0x00010000&(data))>>16)
#define REGD15_get_reg_p0_pll_wd_base_time(data)                      ((0x0000E000&(data))>>13)
#define REGD15_get_reg_p0_pll_wd_en(data)                             ((0x00001000&(data))>>12)
#define REGD15_get_reg_p0_pll_wd_rst_wid(data)                        ((0x00000C00&(data))>>10)
#define REGD15_get_reg_p0_pll_wd_time_rdy(data)                       ((0x00000300&(data))>>8)
#define REGD15_get_reg_p0_acdr_l0_en(data)                            ((0x00000080&(data))>>7)
#define REGD15_get_reg_p0_bypass_eqen_rdy_l0(data)                    ((0x00000040&(data))>>6)
#define REGD15_get_reg_p0_bypass_data_rdy_l0(data)                    ((0x00000020&(data))>>5)
#define REGD15_get_reg_p0_en_eqen_manual_l0(data)                     ((0x00000010&(data))>>4)
#define REGD15_get_reg_p0_en_data_manual_l0(data)                     ((0x00000008&(data))>>3)
#define REGD15_get_p0_pll_wd_ckrdy_ro(data)                           ((0x00000004&(data))>>2)
#define REGD15_get_p0_pll_wd_rst_wc(data)                             ((0x00000002&(data))>>1)
#define REGD15_get_p0_wdog_rst_n(data)                                (0x00000001&(data))


#define REGD16                                                        0xb5c
#define REGD16_reg_addr                                               "0x98034b5c"
#define REGD16_reg                                                    0x98034b5c
#define REGD16_inst_addr                                              "0x02D7"
#define REGD16_inst                                                   0x02D7
#define set_REGD16_reg(data)                                          (*((volatile unsigned int*)REGD16_reg)=data)
#define get_REGD16_reg                                                (*((volatile unsigned int*)REGD16_reg))
#define REGD16_reg_p0_wd_sdm_en_shift                                 (31)
#define REGD16_reg_p0_f_code_shift                                    (16)
#define REGD16_reg_p0_n_code_shift                                    (0)
#define REGD16_reg_p0_wd_sdm_en_mask                                  (0x80000000)
#define REGD16_reg_p0_f_code_mask                                     (0x0FFF0000)
#define REGD16_reg_p0_n_code_mask                                     (0x000001FF)
#define REGD16_reg_p0_wd_sdm_en(data)                                 (0x80000000&((data)<<31))
#define REGD16_reg_p0_f_code(data)                                    (0x0FFF0000&((data)<<16))
#define REGD16_reg_p0_n_code(data)                                    (0x000001FF&(data))
#define REGD16_get_reg_p0_wd_sdm_en(data)                             ((0x80000000&(data))>>31)
#define REGD16_get_reg_p0_f_code(data)                                ((0x0FFF0000&(data))>>16)
#define REGD16_get_reg_p0_n_code(data)                                (0x000001FF&(data))


#define REGD17                                                        0xb60
#define REGD17_reg_addr                                               "0x98034b60"
#define REGD17_reg                                                    0x98034b60
#define REGD17_inst_addr                                              "0x02D8"
#define REGD17_inst                                                   0x02D8
#define set_REGD17_reg(data)                                          (*((volatile unsigned int*)REGD17_reg)=data)
#define get_REGD17_reg                                                (*((volatile unsigned int*)REGD17_reg))
#define REGD17_reg_p1_bypass_clk_rdy_shift                            (31)
#define REGD17_reg_p1_bypass_eqen_rdy_shift                           (30)
#define REGD17_reg_p1_bypass_data_rdy_shift                           (29)
#define REGD17_reg_p1_bypass_pi_shift                                 (28)
#define REGD17_reg_p1_data_rdy_time_shift                             (24)
#define REGD17_reg_p1_en_clkout_manual_shift                          (23)
#define REGD17_reg_p1_en_eqen_manual_shift                            (22)
#define REGD17_reg_p1_en_data_manual_shift                            (21)
#define REGD17_reg_p1_eqen_rdy_time_shift                             (17)
#define REGD17_reg_p1_order_shift                                     (16)
#define REGD17_reg_p1_pll_wd_base_time_shift                          (13)
#define REGD17_reg_p1_pll_wd_en_shift                                 (12)
#define REGD17_reg_p1_pll_wd_rst_wid_shift                            (10)
#define REGD17_reg_p1_pll_wd_time_rdy_shift                           (8)
#define REGD17_reg_p1_acdr_l0_en_shift                                (7)
#define REGD17_reg_p1_bypass_eqen_rdy_l0_shift                        (6)
#define REGD17_reg_p1_bypass_data_rdy_l0_shift                        (5)
#define REGD17_reg_p1_en_eqen_manual_l0_shift                         (4)
#define REGD17_reg_p1_en_data_manual_l0_shift                         (3)
#define REGD17_p1_pll_wd_ckrdy_ro_shift                               (2)
#define REGD17_p1_pll_wd_rst_wc_shift                                 (1)
#define REGD17_p1_wdog_rst_n_shift                                    (0)
#define REGD17_reg_p1_bypass_clk_rdy_mask                             (0x80000000)
#define REGD17_reg_p1_bypass_eqen_rdy_mask                            (0x40000000)
#define REGD17_reg_p1_bypass_data_rdy_mask                            (0x20000000)
#define REGD17_reg_p1_bypass_pi_mask                                  (0x10000000)
#define REGD17_reg_p1_data_rdy_time_mask                              (0x0F000000)
#define REGD17_reg_p1_en_clkout_manual_mask                           (0x00800000)
#define REGD17_reg_p1_en_eqen_manual_mask                             (0x00400000)
#define REGD17_reg_p1_en_data_manual_mask                             (0x00200000)
#define REGD17_reg_p1_eqen_rdy_time_mask                              (0x001E0000)
#define REGD17_reg_p1_order_mask                                      (0x00010000)
#define REGD17_reg_p1_pll_wd_base_time_mask                           (0x0000E000)
#define REGD17_reg_p1_pll_wd_en_mask                                  (0x00001000)
#define REGD17_reg_p1_pll_wd_rst_wid_mask                             (0x00000C00)
#define REGD17_reg_p1_pll_wd_time_rdy_mask                            (0x00000300)
#define REGD17_reg_p1_acdr_l0_en_mask                                 (0x00000080)
#define REGD17_reg_p1_bypass_eqen_rdy_l0_mask                         (0x00000040)
#define REGD17_reg_p1_bypass_data_rdy_l0_mask                         (0x00000020)
#define REGD17_reg_p1_en_eqen_manual_l0_mask                          (0x00000010)
#define REGD17_reg_p1_en_data_manual_l0_mask                          (0x00000008)
#define REGD17_p1_pll_wd_ckrdy_ro_mask                                (0x00000004)
#define REGD17_p1_pll_wd_rst_wc_mask                                  (0x00000002)
#define REGD17_p1_wdog_rst_n_mask                                     (0x00000001)
#define REGD17_reg_p1_bypass_clk_rdy(data)                            (0x80000000&((data)<<31))
#define REGD17_reg_p1_bypass_eqen_rdy(data)                           (0x40000000&((data)<<30))
#define REGD17_reg_p1_bypass_data_rdy(data)                           (0x20000000&((data)<<29))
#define REGD17_reg_p1_bypass_pi(data)                                 (0x10000000&((data)<<28))
#define REGD17_reg_p1_data_rdy_time(data)                             (0x0F000000&((data)<<24))
#define REGD17_reg_p1_en_clkout_manual(data)                          (0x00800000&((data)<<23))
#define REGD17_reg_p1_en_eqen_manual(data)                            (0x00400000&((data)<<22))
#define REGD17_reg_p1_en_data_manual(data)                            (0x00200000&((data)<<21))
#define REGD17_reg_p1_eqen_rdy_time(data)                             (0x001E0000&((data)<<17))
#define REGD17_reg_p1_order(data)                                     (0x00010000&((data)<<16))
#define REGD17_reg_p1_pll_wd_base_time(data)                          (0x0000E000&((data)<<13))
#define REGD17_reg_p1_pll_wd_en(data)                                 (0x00001000&((data)<<12))
#define REGD17_reg_p1_pll_wd_rst_wid(data)                            (0x00000C00&((data)<<10))
#define REGD17_reg_p1_pll_wd_time_rdy(data)                           (0x00000300&((data)<<8))
#define REGD17_reg_p1_acdr_l0_en(data)                                (0x00000080&((data)<<7))
#define REGD17_reg_p1_bypass_eqen_rdy_l0(data)                        (0x00000040&((data)<<6))
#define REGD17_reg_p1_bypass_data_rdy_l0(data)                        (0x00000020&((data)<<5))
#define REGD17_reg_p1_en_eqen_manual_l0(data)                         (0x00000010&((data)<<4))
#define REGD17_reg_p1_en_data_manual_l0(data)                         (0x00000008&((data)<<3))
#define REGD17_p1_pll_wd_ckrdy_ro(data)                               (0x00000004&((data)<<2))
#define REGD17_p1_pll_wd_rst_wc(data)                                 (0x00000002&((data)<<1))
#define REGD17_p1_wdog_rst_n(data)                                    (0x00000001&(data))
#define REGD17_get_reg_p1_bypass_clk_rdy(data)                        ((0x80000000&(data))>>31)
#define REGD17_get_reg_p1_bypass_eqen_rdy(data)                       ((0x40000000&(data))>>30)
#define REGD17_get_reg_p1_bypass_data_rdy(data)                       ((0x20000000&(data))>>29)
#define REGD17_get_reg_p1_bypass_pi(data)                             ((0x10000000&(data))>>28)
#define REGD17_get_reg_p1_data_rdy_time(data)                         ((0x0F000000&(data))>>24)
#define REGD17_get_reg_p1_en_clkout_manual(data)                      ((0x00800000&(data))>>23)
#define REGD17_get_reg_p1_en_eqen_manual(data)                        ((0x00400000&(data))>>22)
#define REGD17_get_reg_p1_en_data_manual(data)                        ((0x00200000&(data))>>21)
#define REGD17_get_reg_p1_eqen_rdy_time(data)                         ((0x001E0000&(data))>>17)
#define REGD17_get_reg_p1_order(data)                                 ((0x00010000&(data))>>16)
#define REGD17_get_reg_p1_pll_wd_base_time(data)                      ((0x0000E000&(data))>>13)
#define REGD17_get_reg_p1_pll_wd_en(data)                             ((0x00001000&(data))>>12)
#define REGD17_get_reg_p1_pll_wd_rst_wid(data)                        ((0x00000C00&(data))>>10)
#define REGD17_get_reg_p1_pll_wd_time_rdy(data)                       ((0x00000300&(data))>>8)
#define REGD17_get_reg_p1_acdr_l0_en(data)                            ((0x00000080&(data))>>7)
#define REGD17_get_reg_p1_bypass_eqen_rdy_l0(data)                    ((0x00000040&(data))>>6)
#define REGD17_get_reg_p1_bypass_data_rdy_l0(data)                    ((0x00000020&(data))>>5)
#define REGD17_get_reg_p1_en_eqen_manual_l0(data)                     ((0x00000010&(data))>>4)
#define REGD17_get_reg_p1_en_data_manual_l0(data)                     ((0x00000008&(data))>>3)
#define REGD17_get_p1_pll_wd_ckrdy_ro(data)                           ((0x00000004&(data))>>2)
#define REGD17_get_p1_pll_wd_rst_wc(data)                             ((0x00000002&(data))>>1)
#define REGD17_get_p1_wdog_rst_n(data)                                (0x00000001&(data))


#define REGD18                                                        0xb64
#define REGD18_reg_addr                                               "0x98034b64"
#define REGD18_reg                                                    0x98034b64
#define REGD18_inst_addr                                              "0x02D9"
#define REGD18_inst                                                   0x02D9
#define set_REGD18_reg(data)                                          (*((volatile unsigned int*)REGD18_reg)=data)
#define get_REGD18_reg                                                (*((volatile unsigned int*)REGD18_reg))
#define REGD18_reg_p1_wd_sdm_en_shift                                 (31)
#define REGD18_reg_p1_f_code_shift                                    (16)
#define REGD18_reg_p1_n_code_shift                                    (0)
#define REGD18_reg_p1_wd_sdm_en_mask                                  (0x80000000)
#define REGD18_reg_p1_f_code_mask                                     (0x0FFF0000)
#define REGD18_reg_p1_n_code_mask                                     (0x000001FF)
#define REGD18_reg_p1_wd_sdm_en(data)                                 (0x80000000&((data)<<31))
#define REGD18_reg_p1_f_code(data)                                    (0x0FFF0000&((data)<<16))
#define REGD18_reg_p1_n_code(data)                                    (0x000001FF&(data))
#define REGD18_get_reg_p1_wd_sdm_en(data)                             ((0x80000000&(data))>>31)
#define REGD18_get_reg_p1_f_code(data)                                ((0x0FFF0000&(data))>>16)
#define REGD18_get_reg_p1_n_code(data)                                (0x000001FF&(data))


#define REGD19                                                        0xb68
#define REGD19_reg_addr                                               "0x98034b68"
#define REGD19_reg                                                    0x98034b68
#define REGD19_inst_addr                                              "0x02DA"
#define REGD19_inst                                                   0x02DA
#define set_REGD19_reg(data)                                          (*((volatile unsigned int*)REGD19_reg)=data)
#define get_REGD19_reg                                                (*((volatile unsigned int*)REGD19_reg))
#define REGD19_reg_p2_bypass_clk_rdy_shift                            (31)
#define REGD19_reg_p2_bypass_eqen_rdy_shift                           (30)
#define REGD19_reg_p2_bypass_data_rdy_shift                           (29)
#define REGD19_reg_p2_bypass_pi_shift                                 (28)
#define REGD19_reg_p2_data_rdy_time_shift                             (24)
#define REGD19_reg_p2_en_clkout_manual_shift                          (23)
#define REGD19_reg_p2_en_eqen_manual_shift                            (22)
#define REGD19_reg_p2_en_data_manual_shift                            (21)
#define REGD19_reg_p2_eqen_rdy_time_shift                             (17)
#define REGD19_reg_p2_order_shift                                     (16)
#define REGD19_reg_p2_pll_wd_base_time_shift                          (13)
#define REGD19_reg_p2_pll_wd_en_shift                                 (12)
#define REGD19_reg_p2_pll_wd_rst_wid_shift                            (10)
#define REGD19_reg_p2_pll_wd_time_rdy_shift                           (8)
#define REGD19_reg_p2_acdr_l0_en_shift                                (7)
#define REGD19_reg_p2_bypass_eqen_rdy_l0_shift                        (6)
#define REGD19_reg_p2_bypass_data_rdy_l0_shift                        (5)
#define REGD19_reg_p2_en_eqen_manual_l0_shift                         (4)
#define REGD19_reg_p2_en_data_manual_l0_shift                         (3)
#define REGD19_p2_pll_wd_ckrdy_ro_shift                               (2)
#define REGD19_p2_pll_wd_rst_wc_shift                                 (1)
#define REGD19_p2_wdog_rst_n_shift                                    (0)
#define REGD19_reg_p2_bypass_clk_rdy_mask                             (0x80000000)
#define REGD19_reg_p2_bypass_eqen_rdy_mask                            (0x40000000)
#define REGD19_reg_p2_bypass_data_rdy_mask                            (0x20000000)
#define REGD19_reg_p2_bypass_pi_mask                                  (0x10000000)
#define REGD19_reg_p2_data_rdy_time_mask                              (0x0F000000)
#define REGD19_reg_p2_en_clkout_manual_mask                           (0x00800000)
#define REGD19_reg_p2_en_eqen_manual_mask                             (0x00400000)
#define REGD19_reg_p2_en_data_manual_mask                             (0x00200000)
#define REGD19_reg_p2_eqen_rdy_time_mask                              (0x001E0000)
#define REGD19_reg_p2_order_mask                                      (0x00010000)
#define REGD19_reg_p2_pll_wd_base_time_mask                           (0x0000E000)
#define REGD19_reg_p2_pll_wd_en_mask                                  (0x00001000)
#define REGD19_reg_p2_pll_wd_rst_wid_mask                             (0x00000C00)
#define REGD19_reg_p2_pll_wd_time_rdy_mask                            (0x00000300)
#define REGD19_reg_p2_acdr_l0_en_mask                                 (0x00000080)
#define REGD19_reg_p2_bypass_eqen_rdy_l0_mask                         (0x00000040)
#define REGD19_reg_p2_bypass_data_rdy_l0_mask                         (0x00000020)
#define REGD19_reg_p2_en_eqen_manual_l0_mask                          (0x00000010)
#define REGD19_reg_p2_en_data_manual_l0_mask                          (0x00000008)
#define REGD19_p2_pll_wd_ckrdy_ro_mask                                (0x00000004)
#define REGD19_p2_pll_wd_rst_wc_mask                                  (0x00000002)
#define REGD19_p2_wdog_rst_n_mask                                     (0x00000001)
#define REGD19_reg_p2_bypass_clk_rdy(data)                            (0x80000000&((data)<<31))
#define REGD19_reg_p2_bypass_eqen_rdy(data)                           (0x40000000&((data)<<30))
#define REGD19_reg_p2_bypass_data_rdy(data)                           (0x20000000&((data)<<29))
#define REGD19_reg_p2_bypass_pi(data)                                 (0x10000000&((data)<<28))
#define REGD19_reg_p2_data_rdy_time(data)                             (0x0F000000&((data)<<24))
#define REGD19_reg_p2_en_clkout_manual(data)                          (0x00800000&((data)<<23))
#define REGD19_reg_p2_en_eqen_manual(data)                            (0x00400000&((data)<<22))
#define REGD19_reg_p2_en_data_manual(data)                            (0x00200000&((data)<<21))
#define REGD19_reg_p2_eqen_rdy_time(data)                             (0x001E0000&((data)<<17))
#define REGD19_reg_p2_order(data)                                     (0x00010000&((data)<<16))
#define REGD19_reg_p2_pll_wd_base_time(data)                          (0x0000E000&((data)<<13))
#define REGD19_reg_p2_pll_wd_en(data)                                 (0x00001000&((data)<<12))
#define REGD19_reg_p2_pll_wd_rst_wid(data)                            (0x00000C00&((data)<<10))
#define REGD19_reg_p2_pll_wd_time_rdy(data)                           (0x00000300&((data)<<8))
#define REGD19_reg_p2_acdr_l0_en(data)                                (0x00000080&((data)<<7))
#define REGD19_reg_p2_bypass_eqen_rdy_l0(data)                        (0x00000040&((data)<<6))
#define REGD19_reg_p2_bypass_data_rdy_l0(data)                        (0x00000020&((data)<<5))
#define REGD19_reg_p2_en_eqen_manual_l0(data)                         (0x00000010&((data)<<4))
#define REGD19_reg_p2_en_data_manual_l0(data)                         (0x00000008&((data)<<3))
#define REGD19_p2_pll_wd_ckrdy_ro(data)                               (0x00000004&((data)<<2))
#define REGD19_p2_pll_wd_rst_wc(data)                                 (0x00000002&((data)<<1))
#define REGD19_p2_wdog_rst_n(data)                                    (0x00000001&(data))
#define REGD19_get_reg_p2_bypass_clk_rdy(data)                        ((0x80000000&(data))>>31)
#define REGD19_get_reg_p2_bypass_eqen_rdy(data)                       ((0x40000000&(data))>>30)
#define REGD19_get_reg_p2_bypass_data_rdy(data)                       ((0x20000000&(data))>>29)
#define REGD19_get_reg_p2_bypass_pi(data)                             ((0x10000000&(data))>>28)
#define REGD19_get_reg_p2_data_rdy_time(data)                         ((0x0F000000&(data))>>24)
#define REGD19_get_reg_p2_en_clkout_manual(data)                      ((0x00800000&(data))>>23)
#define REGD19_get_reg_p2_en_eqen_manual(data)                        ((0x00400000&(data))>>22)
#define REGD19_get_reg_p2_en_data_manual(data)                        ((0x00200000&(data))>>21)
#define REGD19_get_reg_p2_eqen_rdy_time(data)                         ((0x001E0000&(data))>>17)
#define REGD19_get_reg_p2_order(data)                                 ((0x00010000&(data))>>16)
#define REGD19_get_reg_p2_pll_wd_base_time(data)                      ((0x0000E000&(data))>>13)
#define REGD19_get_reg_p2_pll_wd_en(data)                             ((0x00001000&(data))>>12)
#define REGD19_get_reg_p2_pll_wd_rst_wid(data)                        ((0x00000C00&(data))>>10)
#define REGD19_get_reg_p2_pll_wd_time_rdy(data)                       ((0x00000300&(data))>>8)
#define REGD19_get_reg_p2_acdr_l0_en(data)                            ((0x00000080&(data))>>7)
#define REGD19_get_reg_p2_bypass_eqen_rdy_l0(data)                    ((0x00000040&(data))>>6)
#define REGD19_get_reg_p2_bypass_data_rdy_l0(data)                    ((0x00000020&(data))>>5)
#define REGD19_get_reg_p2_en_eqen_manual_l0(data)                     ((0x00000010&(data))>>4)
#define REGD19_get_reg_p2_en_data_manual_l0(data)                     ((0x00000008&(data))>>3)
#define REGD19_get_p2_pll_wd_ckrdy_ro(data)                           ((0x00000004&(data))>>2)
#define REGD19_get_p2_pll_wd_rst_wc(data)                             ((0x00000002&(data))>>1)
#define REGD19_get_p2_wdog_rst_n(data)                                (0x00000001&(data))


#define REGD20                                                        0xb6c
#define REGD20_reg_addr                                               "0x98034b6c"
#define REGD20_reg                                                    0x98034b6c
#define REGD20_inst_addr                                              "0x02DB"
#define REGD20_inst                                                   0x02DB
#define set_REGD20_reg(data)                                          (*((volatile unsigned int*)REGD20_reg)=data)
#define get_REGD20_reg                                                (*((volatile unsigned int*)REGD20_reg))
#define REGD20_reg_p2_wd_sdm_en_shift                                 (31)
#define REGD20_reg_p2_f_code_shift                                    (16)
#define REGD20_reg_p2_n_code_shift                                    (0)
#define REGD20_reg_p2_wd_sdm_en_mask                                  (0x80000000)
#define REGD20_reg_p2_f_code_mask                                     (0x0FFF0000)
#define REGD20_reg_p2_n_code_mask                                     (0x000001FF)
#define REGD20_reg_p2_wd_sdm_en(data)                                 (0x80000000&((data)<<31))
#define REGD20_reg_p2_f_code(data)                                    (0x0FFF0000&((data)<<16))
#define REGD20_reg_p2_n_code(data)                                    (0x000001FF&(data))
#define REGD20_get_reg_p2_wd_sdm_en(data)                             ((0x80000000&(data))>>31)
#define REGD20_get_reg_p2_f_code(data)                                ((0x0FFF0000&(data))>>16)
#define REGD20_get_reg_p2_n_code(data)                                (0x000001FF&(data))


#define REGD21                                                        0xb70
#define REGD21_reg_addr                                               "0x98034b70"
#define REGD21_reg                                                    0x98034b70
#define REGD21_inst_addr                                              "0x02DC"
#define REGD21_inst                                                   0x02DC
#define set_REGD21_reg(data)                                          (*((volatile unsigned int*)REGD21_reg)=data)
#define get_REGD21_reg                                                (*((volatile unsigned int*)REGD21_reg))
#define REGD21_reg_p0_auto_mode_shift                                 (31)
#define REGD21_reg_p0_adp_en_manual_shift                             (30)
#define REGD21_reg_p0_cp_en_manual_shift                              (29)
#define REGD21_reg_p0_adap_eq_off_shift                               (28)
#define REGD21_reg_p0_adp_time_shift                                  (23)
#define REGD21_reg_p0_calib_time_shift                                (20)
#define REGD21_reg_p0_calib_manual_shift                              (19)
#define REGD21_reg_p0_calib_late_shift                                (18)
#define REGD21_reg_p0_vco_coarse_shift                                (11)
#define REGD21_reg_p0_divide_num_shift                                (4)
#define REGD21_reg_p0_init_time_shift                                 (1)
#define REGD21_reg_p0_auto_mode_mask                                  (0x80000000)
#define REGD21_reg_p0_adp_en_manual_mask                              (0x40000000)
#define REGD21_reg_p0_cp_en_manual_mask                               (0x20000000)
#define REGD21_reg_p0_adap_eq_off_mask                                (0x10000000)
#define REGD21_reg_p0_adp_time_mask                                   (0x0F800000)
#define REGD21_reg_p0_calib_time_mask                                 (0x00700000)
#define REGD21_reg_p0_calib_manual_mask                               (0x00080000)
#define REGD21_reg_p0_calib_late_mask                                 (0x00040000)
#define REGD21_reg_p0_vco_coarse_mask                                 (0x0003F800)
#define REGD21_reg_p0_divide_num_mask                                 (0x000007F0)
#define REGD21_reg_p0_init_time_mask                                  (0x0000000E)
#define REGD21_reg_p0_auto_mode(data)                                 (0x80000000&((data)<<31))
#define REGD21_reg_p0_adp_en_manual(data)                             (0x40000000&((data)<<30))
#define REGD21_reg_p0_cp_en_manual(data)                              (0x20000000&((data)<<29))
#define REGD21_reg_p0_adap_eq_off(data)                               (0x10000000&((data)<<28))
#define REGD21_reg_p0_adp_time(data)                                  (0x0F800000&((data)<<23))
#define REGD21_reg_p0_calib_time(data)                                (0x00700000&((data)<<20))
#define REGD21_reg_p0_calib_manual(data)                              (0x00080000&((data)<<19))
#define REGD21_reg_p0_calib_late(data)                                (0x00040000&((data)<<18))
#define REGD21_reg_p0_vco_coarse(data)                                (0x0003F800&((data)<<11))
#define REGD21_reg_p0_divide_num(data)                                (0x000007F0&((data)<<4))
#define REGD21_reg_p0_init_time(data)                                 (0x0000000E&((data)<<1))
#define REGD21_get_reg_p0_auto_mode(data)                             ((0x80000000&(data))>>31)
#define REGD21_get_reg_p0_adp_en_manual(data)                         ((0x40000000&(data))>>30)
#define REGD21_get_reg_p0_cp_en_manual(data)                          ((0x20000000&(data))>>29)
#define REGD21_get_reg_p0_adap_eq_off(data)                           ((0x10000000&(data))>>28)
#define REGD21_get_reg_p0_adp_time(data)                              ((0x0F800000&(data))>>23)
#define REGD21_get_reg_p0_calib_time(data)                            ((0x00700000&(data))>>20)
#define REGD21_get_reg_p0_calib_manual(data)                          ((0x00080000&(data))>>19)
#define REGD21_get_reg_p0_calib_late(data)                            ((0x00040000&(data))>>18)
#define REGD21_get_reg_p0_vco_coarse(data)                            ((0x0003F800&(data))>>11)
#define REGD21_get_reg_p0_divide_num(data)                            ((0x000007F0&(data))>>4)
#define REGD21_get_reg_p0_init_time(data)                             ((0x0000000E&(data))>>1)


#define REGD22                                                        0xb74
#define REGD22_reg_addr                                               "0x98034b74"
#define REGD22_reg                                                    0x98034b74
#define REGD22_inst_addr                                              "0x02DD"
#define REGD22_inst                                                   0x02DD
#define set_REGD22_reg(data)                                          (*((volatile unsigned int*)REGD22_reg)=data)
#define get_REGD22_reg                                                (*((volatile unsigned int*)REGD22_reg))
#define REGD22_reg_p0_lock_up_limit_shift                             (16)
#define REGD22_reg_p0_lock_dn_limit_shift                             (0)
#define REGD22_reg_p0_lock_up_limit_mask                              (0x07FF0000)
#define REGD22_reg_p0_lock_dn_limit_mask                              (0x000007FF)
#define REGD22_reg_p0_lock_up_limit(data)                             (0x07FF0000&((data)<<16))
#define REGD22_reg_p0_lock_dn_limit(data)                             (0x000007FF&(data))
#define REGD22_get_reg_p0_lock_up_limit(data)                         ((0x07FF0000&(data))>>16)
#define REGD22_get_reg_p0_lock_dn_limit(data)                         (0x000007FF&(data))


#define REGD23                                                        0xb78
#define REGD23_reg_addr                                               "0x98034b78"
#define REGD23_reg                                                    0x98034b78
#define REGD23_inst_addr                                              "0x02DE"
#define REGD23_inst                                                   0x02DE
#define set_REGD23_reg(data)                                          (*((volatile unsigned int*)REGD23_reg)=data)
#define get_REGD23_reg                                                (*((volatile unsigned int*)REGD23_reg))
#define REGD23_reg_p0_cdr_cp_shift                                    (12)
#define REGD23_reg_p0_cdr_r_shift                                     (6)
#define REGD23_reg_p0_cdr_c_shift                                     (4)
#define REGD23_reg_p0_vc_sel_shift                                    (2)
#define REGD23_reg_p0_calib_reset_sel_shift                           (1)
#define REGD23_reg_p0_cdr_cp_mask                                     (0xFFFFF000)
#define REGD23_reg_p0_cdr_r_mask                                      (0x00000FC0)
#define REGD23_reg_p0_cdr_c_mask                                      (0x00000030)
#define REGD23_reg_p0_vc_sel_mask                                     (0x0000000C)
#define REGD23_reg_p0_calib_reset_sel_mask                            (0x00000002)
#define REGD23_reg_p0_cdr_cp(data)                                    (0xFFFFF000&((data)<<12))
#define REGD23_reg_p0_cdr_r(data)                                     (0x00000FC0&((data)<<6))
#define REGD23_reg_p0_cdr_c(data)                                     (0x00000030&((data)<<4))
#define REGD23_reg_p0_vc_sel(data)                                    (0x0000000C&((data)<<2))
#define REGD23_reg_p0_calib_reset_sel(data)                           (0x00000002&((data)<<1))
#define REGD23_get_reg_p0_cdr_cp(data)                                ((0xFFFFF000&(data))>>12)
#define REGD23_get_reg_p0_cdr_r(data)                                 ((0x00000FC0&(data))>>6)
#define REGD23_get_reg_p0_cdr_c(data)                                 ((0x00000030&(data))>>4)
#define REGD23_get_reg_p0_vc_sel(data)                                ((0x0000000C&(data))>>2)
#define REGD23_get_reg_p0_calib_reset_sel(data)                       ((0x00000002&(data))>>1)


#define REGD24                                                        0xb7c
#define REGD24_reg_addr                                               "0x98034b7c"
#define REGD24_reg                                                    0x98034b7c
#define REGD24_inst_addr                                              "0x02DF"
#define REGD24_inst                                                   0x02DF
#define set_REGD24_reg(data)                                          (*((volatile unsigned int*)REGD24_reg)=data)
#define get_REGD24_reg                                                (*((volatile unsigned int*)REGD24_reg))
#define REGD24_reg_p0_slope_lv_up_shift                               (21)
#define REGD24_reg_p0_slope_lv_dn_shift                               (10)
#define REGD24_reg_p0_cp_time_shift                                   (5)
#define REGD24_reg_p0_timer_4_shift                                   (0)
#define REGD24_reg_p0_slope_lv_up_mask                                (0xFFE00000)
#define REGD24_reg_p0_slope_lv_dn_mask                                (0x001FFC00)
#define REGD24_reg_p0_cp_time_mask                                    (0x000003E0)
#define REGD24_reg_p0_timer_4_mask                                    (0x0000001F)
#define REGD24_reg_p0_slope_lv_up(data)                               (0xFFE00000&((data)<<21))
#define REGD24_reg_p0_slope_lv_dn(data)                               (0x001FFC00&((data)<<10))
#define REGD24_reg_p0_cp_time(data)                                   (0x000003E0&((data)<<5))
#define REGD24_reg_p0_timer_4(data)                                   (0x0000001F&(data))
#define REGD24_get_reg_p0_slope_lv_up(data)                           ((0xFFE00000&(data))>>21)
#define REGD24_get_reg_p0_slope_lv_dn(data)                           ((0x001FFC00&(data))>>10)
#define REGD24_get_reg_p0_cp_time(data)                               ((0x000003E0&(data))>>5)
#define REGD24_get_reg_p0_timer_4(data)                               (0x0000001F&(data))


#define REGD25                                                        0xb80
#define REGD25_reg_addr                                               "0x98034b80"
#define REGD25_reg                                                    0x98034b80
#define REGD25_inst_addr                                              "0x02E0"
#define REGD25_inst                                                   0x02E0
#define set_REGD25_reg(data)                                          (*((volatile unsigned int*)REGD25_reg)=data)
#define get_REGD25_reg                                                (*((volatile unsigned int*)REGD25_reg))
#define REGD25_reg_p0_slope_hv_up_shift                               (21)
#define REGD25_reg_p0_slope_hv_dn_shift                               (10)
#define REGD25_reg_p0_timer_5_shift                                   (9)
#define REGD25_reg_p0_timer_6_shift                                   (4)
#define REGD25_reg_p0_slope_hv_up_mask                                (0xFFE00000)
#define REGD25_reg_p0_slope_hv_dn_mask                                (0x001FFC00)
#define REGD25_reg_p0_timer_5_mask                                    (0x00000200)
#define REGD25_reg_p0_timer_6_mask                                    (0x000001F0)
#define REGD25_reg_p0_slope_hv_up(data)                               (0xFFE00000&((data)<<21))
#define REGD25_reg_p0_slope_hv_dn(data)                               (0x001FFC00&((data)<<10))
#define REGD25_reg_p0_timer_5(data)                                   (0x00000200&((data)<<9))
#define REGD25_reg_p0_timer_6(data)                                   (0x000001F0&((data)<<4))
#define REGD25_get_reg_p0_slope_hv_up(data)                           ((0xFFE00000&(data))>>21)
#define REGD25_get_reg_p0_slope_hv_dn(data)                           ((0x001FFC00&(data))>>10)
#define REGD25_get_reg_p0_timer_5(data)                               ((0x00000200&(data))>>9)
#define REGD25_get_reg_p0_timer_6(data)                               ((0x000001F0&(data))>>4)


#define REGD26                                                        0xb84
#define REGD26_reg_addr                                               "0x98034b84"
#define REGD26_reg                                                    0x98034b84
#define REGD26_inst_addr                                              "0x02E1"
#define REGD26_inst                                                   0x02E1
#define set_REGD26_reg(data)                                          (*((volatile unsigned int*)REGD26_reg)=data)
#define get_REGD26_reg                                                (*((volatile unsigned int*)REGD26_reg))
#define REGD26_reg_p0_start_en_manual_shift                           (31)
#define REGD26_reg_p0_pfd_en_manual_shift                             (30)
#define REGD26_reg_p0_pfd_time_shift                                  (25)
#define REGD26_reg_p0_pfd_bypass_shift                                (24)
#define REGD26_reg_p0_rxidle_bypass_shift                             (23)
#define REGD26_reg_p0_slope_manual_shift                              (22)
#define REGD26_reg_p0_slope_band_shift                                (17)
#define REGD26_reg_p0_old_mode_shift                                  (16)
#define REGD26_reg_p0_start_en_manual_mask                            (0x80000000)
#define REGD26_reg_p0_pfd_en_manual_mask                              (0x40000000)
#define REGD26_reg_p0_pfd_time_mask                                   (0x3E000000)
#define REGD26_reg_p0_pfd_bypass_mask                                 (0x01000000)
#define REGD26_reg_p0_rxidle_bypass_mask                              (0x00800000)
#define REGD26_reg_p0_slope_manual_mask                               (0x00400000)
#define REGD26_reg_p0_slope_band_mask                                 (0x003E0000)
#define REGD26_reg_p0_old_mode_mask                                   (0x00010000)
#define REGD26_reg_p0_start_en_manual(data)                           (0x80000000&((data)<<31))
#define REGD26_reg_p0_pfd_en_manual(data)                             (0x40000000&((data)<<30))
#define REGD26_reg_p0_pfd_time(data)                                  (0x3E000000&((data)<<25))
#define REGD26_reg_p0_pfd_bypass(data)                                (0x01000000&((data)<<24))
#define REGD26_reg_p0_rxidle_bypass(data)                             (0x00800000&((data)<<23))
#define REGD26_reg_p0_slope_manual(data)                              (0x00400000&((data)<<22))
#define REGD26_reg_p0_slope_band(data)                                (0x003E0000&((data)<<17))
#define REGD26_reg_p0_old_mode(data)                                  (0x00010000&((data)<<16))
#define REGD26_get_reg_p0_start_en_manual(data)                       ((0x80000000&(data))>>31)
#define REGD26_get_reg_p0_pfd_en_manual(data)                         ((0x40000000&(data))>>30)
#define REGD26_get_reg_p0_pfd_time(data)                              ((0x3E000000&(data))>>25)
#define REGD26_get_reg_p0_pfd_bypass(data)                            ((0x01000000&(data))>>24)
#define REGD26_get_reg_p0_rxidle_bypass(data)                         ((0x00800000&(data))>>23)
#define REGD26_get_reg_p0_slope_manual(data)                          ((0x00400000&(data))>>22)
#define REGD26_get_reg_p0_slope_band(data)                            ((0x003E0000&(data))>>17)
#define REGD26_get_reg_p0_old_mode(data)                              ((0x00010000&(data))>>16)


#define REGD27                                                        0xb88
#define REGD27_reg_addr                                               "0x98034b88"
#define REGD27_reg                                                    0x98034b88
#define REGD27_inst_addr                                              "0x02E2"
#define REGD27_inst                                                   0x02E2
#define set_REGD27_reg(data)                                          (*((volatile unsigned int*)REGD27_reg)=data)
#define get_REGD27_reg                                                (*((volatile unsigned int*)REGD27_reg))
#define REGD27_p0_fld_st_reg_shift                                    (27)
#define REGD27_p0_adp_en_fsm_reg_shift                                (26)
#define REGD27_p0_cp_en_fsm_reg_shift                                 (25)
#define REGD27_p0_coarse_fsm_reg_shift                                (18)
#define REGD27_p0_pfd_en_fsm_reg_shift                                (17)
#define REGD27_p0_slope_lv_reg_shift                                  (12)
#define REGD27_p0_slope_hv_reg_shift                                  (7)
#define REGD27_p0_slope_final_reg_shift                               (2)
#define REGD27_p0_fld_st_reg_mask                                     (0xF8000000)
#define REGD27_p0_adp_en_fsm_reg_mask                                 (0x04000000)
#define REGD27_p0_cp_en_fsm_reg_mask                                  (0x02000000)
#define REGD27_p0_coarse_fsm_reg_mask                                 (0x01FC0000)
#define REGD27_p0_pfd_en_fsm_reg_mask                                 (0x00020000)
#define REGD27_p0_slope_lv_reg_mask                                   (0x0001F000)
#define REGD27_p0_slope_hv_reg_mask                                   (0x00000F80)
#define REGD27_p0_slope_final_reg_mask                                (0x0000007C)
#define REGD27_p0_fld_st_reg(data)                                    (0xF8000000&((data)<<27))
#define REGD27_p0_adp_en_fsm_reg(data)                                (0x04000000&((data)<<26))
#define REGD27_p0_cp_en_fsm_reg(data)                                 (0x02000000&((data)<<25))
#define REGD27_p0_coarse_fsm_reg(data)                                (0x01FC0000&((data)<<18))
#define REGD27_p0_pfd_en_fsm_reg(data)                                (0x00020000&((data)<<17))
#define REGD27_p0_slope_lv_reg(data)                                  (0x0001F000&((data)<<12))
#define REGD27_p0_slope_hv_reg(data)                                  (0x00000F80&((data)<<7))
#define REGD27_p0_slope_final_reg(data)                               (0x0000007C&((data)<<2))
#define REGD27_get_p0_fld_st_reg(data)                                ((0xF8000000&(data))>>27)
#define REGD27_get_p0_adp_en_fsm_reg(data)                            ((0x04000000&(data))>>26)
#define REGD27_get_p0_cp_en_fsm_reg(data)                             ((0x02000000&(data))>>25)
#define REGD27_get_p0_coarse_fsm_reg(data)                            ((0x01FC0000&(data))>>18)
#define REGD27_get_p0_pfd_en_fsm_reg(data)                            ((0x00020000&(data))>>17)
#define REGD27_get_p0_slope_lv_reg(data)                              ((0x0001F000&(data))>>12)
#define REGD27_get_p0_slope_hv_reg(data)                              ((0x00000F80&(data))>>7)
#define REGD27_get_p0_slope_final_reg(data)                           ((0x0000007C&(data))>>2)


#define REGD28                                                        0xb8c
#define REGD28_reg_addr                                               "0x98034b8c"
#define REGD28_reg                                                    0x98034b8c
#define REGD28_inst_addr                                              "0x02E3"
#define REGD28_inst                                                   0x02E3
#define set_REGD28_reg(data)                                          (*((volatile unsigned int*)REGD28_reg)=data)
#define get_REGD28_reg                                                (*((volatile unsigned int*)REGD28_reg))
#define REGD28_reg_p1_auto_mode_shift                                 (31)
#define REGD28_reg_p1_adp_en_manual_shift                             (30)
#define REGD28_reg_p1_cp_en_manual_shift                              (29)
#define REGD28_reg_p1_adap_eq_off_shift                               (28)
#define REGD28_reg_p1_adp_time_shift                                  (23)
#define REGD28_reg_p1_calib_time_shift                                (20)
#define REGD28_reg_p1_calib_manual_shift                              (19)
#define REGD28_reg_p1_calib_late_shift                                (18)
#define REGD28_reg_p1_vco_coarse_shift                                (11)
#define REGD28_reg_p1_divide_num_shift                                (4)
#define REGD28_reg_p1_init_time_shift                                 (1)
#define REGD28_reg_p1_auto_mode_mask                                  (0x80000000)
#define REGD28_reg_p1_adp_en_manual_mask                              (0x40000000)
#define REGD28_reg_p1_cp_en_manual_mask                               (0x20000000)
#define REGD28_reg_p1_adap_eq_off_mask                                (0x10000000)
#define REGD28_reg_p1_adp_time_mask                                   (0x0F800000)
#define REGD28_reg_p1_calib_time_mask                                 (0x00700000)
#define REGD28_reg_p1_calib_manual_mask                               (0x00080000)
#define REGD28_reg_p1_calib_late_mask                                 (0x00040000)
#define REGD28_reg_p1_vco_coarse_mask                                 (0x0003F800)
#define REGD28_reg_p1_divide_num_mask                                 (0x000007F0)
#define REGD28_reg_p1_init_time_mask                                  (0x0000000E)
#define REGD28_reg_p1_auto_mode(data)                                 (0x80000000&((data)<<31))
#define REGD28_reg_p1_adp_en_manual(data)                             (0x40000000&((data)<<30))
#define REGD28_reg_p1_cp_en_manual(data)                              (0x20000000&((data)<<29))
#define REGD28_reg_p1_adap_eq_off(data)                               (0x10000000&((data)<<28))
#define REGD28_reg_p1_adp_time(data)                                  (0x0F800000&((data)<<23))
#define REGD28_reg_p1_calib_time(data)                                (0x00700000&((data)<<20))
#define REGD28_reg_p1_calib_manual(data)                              (0x00080000&((data)<<19))
#define REGD28_reg_p1_calib_late(data)                                (0x00040000&((data)<<18))
#define REGD28_reg_p1_vco_coarse(data)                                (0x0003F800&((data)<<11))
#define REGD28_reg_p1_divide_num(data)                                (0x000007F0&((data)<<4))
#define REGD28_reg_p1_init_time(data)                                 (0x0000000E&((data)<<1))
#define REGD28_get_reg_p1_auto_mode(data)                             ((0x80000000&(data))>>31)
#define REGD28_get_reg_p1_adp_en_manual(data)                         ((0x40000000&(data))>>30)
#define REGD28_get_reg_p1_cp_en_manual(data)                          ((0x20000000&(data))>>29)
#define REGD28_get_reg_p1_adap_eq_off(data)                           ((0x10000000&(data))>>28)
#define REGD28_get_reg_p1_adp_time(data)                              ((0x0F800000&(data))>>23)
#define REGD28_get_reg_p1_calib_time(data)                            ((0x00700000&(data))>>20)
#define REGD28_get_reg_p1_calib_manual(data)                          ((0x00080000&(data))>>19)
#define REGD28_get_reg_p1_calib_late(data)                            ((0x00040000&(data))>>18)
#define REGD28_get_reg_p1_vco_coarse(data)                            ((0x0003F800&(data))>>11)
#define REGD28_get_reg_p1_divide_num(data)                            ((0x000007F0&(data))>>4)
#define REGD28_get_reg_p1_init_time(data)                             ((0x0000000E&(data))>>1)


#define REGD29                                                        0xb90
#define REGD29_reg_addr                                               "0x98034b90"
#define REGD29_reg                                                    0x98034b90
#define REGD29_inst_addr                                              "0x02E4"
#define REGD29_inst                                                   0x02E4
#define set_REGD29_reg(data)                                          (*((volatile unsigned int*)REGD29_reg)=data)
#define get_REGD29_reg                                                (*((volatile unsigned int*)REGD29_reg))
#define REGD29_reg_p1_lock_up_limit_shift                             (16)
#define REGD29_reg_p1_lock_dn_limit_shift                             (0)
#define REGD29_reg_p1_lock_up_limit_mask                              (0x07FF0000)
#define REGD29_reg_p1_lock_dn_limit_mask                              (0x000007FF)
#define REGD29_reg_p1_lock_up_limit(data)                             (0x07FF0000&((data)<<16))
#define REGD29_reg_p1_lock_dn_limit(data)                             (0x000007FF&(data))
#define REGD29_get_reg_p1_lock_up_limit(data)                         ((0x07FF0000&(data))>>16)
#define REGD29_get_reg_p1_lock_dn_limit(data)                         (0x000007FF&(data))


#define REGD30                                                        0xb94
#define REGD30_reg_addr                                               "0x98034b94"
#define REGD30_reg                                                    0x98034b94
#define REGD30_inst_addr                                              "0x02E5"
#define REGD30_inst                                                   0x02E5
#define set_REGD30_reg(data)                                          (*((volatile unsigned int*)REGD30_reg)=data)
#define get_REGD30_reg                                                (*((volatile unsigned int*)REGD30_reg))
#define REGD30_reg_p1_cdr_cp_shift                                    (12)
#define REGD30_reg_p1_cdr_r_shift                                     (6)
#define REGD30_reg_p1_cdr_c_shift                                     (4)
#define REGD30_reg_p1_vc_sel_shift                                    (2)
#define REGD30_reg_p1_calib_reset_sel_shift                           (1)
#define REGD30_reg_p1_cdr_cp_mask                                     (0xFFFFF000)
#define REGD30_reg_p1_cdr_r_mask                                      (0x00000FC0)
#define REGD30_reg_p1_cdr_c_mask                                      (0x00000030)
#define REGD30_reg_p1_vc_sel_mask                                     (0x0000000C)
#define REGD30_reg_p1_calib_reset_sel_mask                            (0x00000002)
#define REGD30_reg_p1_cdr_cp(data)                                    (0xFFFFF000&((data)<<12))
#define REGD30_reg_p1_cdr_r(data)                                     (0x00000FC0&((data)<<6))
#define REGD30_reg_p1_cdr_c(data)                                     (0x00000030&((data)<<4))
#define REGD30_reg_p1_vc_sel(data)                                    (0x0000000C&((data)<<2))
#define REGD30_reg_p1_calib_reset_sel(data)                           (0x00000002&((data)<<1))
#define REGD30_get_reg_p1_cdr_cp(data)                                ((0xFFFFF000&(data))>>12)
#define REGD30_get_reg_p1_cdr_r(data)                                 ((0x00000FC0&(data))>>6)
#define REGD30_get_reg_p1_cdr_c(data)                                 ((0x00000030&(data))>>4)
#define REGD30_get_reg_p1_vc_sel(data)                                ((0x0000000C&(data))>>2)
#define REGD30_get_reg_p1_calib_reset_sel(data)                       ((0x00000002&(data))>>1)


#define REGD31                                                        0xb98
#define REGD31_reg_addr                                               "0x98034b98"
#define REGD31_reg                                                    0x98034b98
#define REGD31_inst_addr                                              "0x02E6"
#define REGD31_inst                                                   0x02E6
#define set_REGD31_reg(data)                                          (*((volatile unsigned int*)REGD31_reg)=data)
#define get_REGD31_reg                                                (*((volatile unsigned int*)REGD31_reg))
#define REGD31_reg_p1_slope_lv_up_shift                               (21)
#define REGD31_reg_p1_slope_lv_dn_shift                               (10)
#define REGD31_reg_p1_cp_time_shift                                   (5)
#define REGD31_reg_p1_timer_4_shift                                   (0)
#define REGD31_reg_p1_slope_lv_up_mask                                (0xFFE00000)
#define REGD31_reg_p1_slope_lv_dn_mask                                (0x001FFC00)
#define REGD31_reg_p1_cp_time_mask                                    (0x000003E0)
#define REGD31_reg_p1_timer_4_mask                                    (0x0000001F)
#define REGD31_reg_p1_slope_lv_up(data)                               (0xFFE00000&((data)<<21))
#define REGD31_reg_p1_slope_lv_dn(data)                               (0x001FFC00&((data)<<10))
#define REGD31_reg_p1_cp_time(data)                                   (0x000003E0&((data)<<5))
#define REGD31_reg_p1_timer_4(data)                                   (0x0000001F&(data))
#define REGD31_get_reg_p1_slope_lv_up(data)                           ((0xFFE00000&(data))>>21)
#define REGD31_get_reg_p1_slope_lv_dn(data)                           ((0x001FFC00&(data))>>10)
#define REGD31_get_reg_p1_cp_time(data)                               ((0x000003E0&(data))>>5)
#define REGD31_get_reg_p1_timer_4(data)                               (0x0000001F&(data))


#define REGD32                                                        0xb9c
#define REGD32_reg_addr                                               "0x98034b9c"
#define REGD32_reg                                                    0x98034b9c
#define REGD32_inst_addr                                              "0x02E7"
#define REGD32_inst                                                   0x02E7
#define set_REGD32_reg(data)                                          (*((volatile unsigned int*)REGD32_reg)=data)
#define get_REGD32_reg                                                (*((volatile unsigned int*)REGD32_reg))
#define REGD32_reg_p1_slope_hv_up_shift                               (21)
#define REGD32_reg_p1_slope_hv_dn_shift                               (10)
#define REGD32_reg_p1_timer_5_shift                                   (9)
#define REGD32_reg_p1_timer_6_shift                                   (4)
#define REGD32_reg_p1_slope_hv_up_mask                                (0xFFE00000)
#define REGD32_reg_p1_slope_hv_dn_mask                                (0x001FFC00)
#define REGD32_reg_p1_timer_5_mask                                    (0x00000200)
#define REGD32_reg_p1_timer_6_mask                                    (0x000001F0)
#define REGD32_reg_p1_slope_hv_up(data)                               (0xFFE00000&((data)<<21))
#define REGD32_reg_p1_slope_hv_dn(data)                               (0x001FFC00&((data)<<10))
#define REGD32_reg_p1_timer_5(data)                                   (0x00000200&((data)<<9))
#define REGD32_reg_p1_timer_6(data)                                   (0x000001F0&((data)<<4))
#define REGD32_get_reg_p1_slope_hv_up(data)                           ((0xFFE00000&(data))>>21)
#define REGD32_get_reg_p1_slope_hv_dn(data)                           ((0x001FFC00&(data))>>10)
#define REGD32_get_reg_p1_timer_5(data)                               ((0x00000200&(data))>>9)
#define REGD32_get_reg_p1_timer_6(data)                               ((0x000001F0&(data))>>4)


#define REGD33                                                        0xba0
#define REGD33_reg_addr                                               "0x98034ba0"
#define REGD33_reg                                                    0x98034ba0
#define REGD33_inst_addr                                              "0x02E8"
#define REGD33_inst                                                   0x02E8
#define set_REGD33_reg(data)                                          (*((volatile unsigned int*)REGD33_reg)=data)
#define get_REGD33_reg                                                (*((volatile unsigned int*)REGD33_reg))
#define REGD33_reg_p1_start_en_manual_shift                           (31)
#define REGD33_reg_p1_pfd_en_manual_shift                             (30)
#define REGD33_reg_p1_pfd_time_shift                                  (25)
#define REGD33_reg_p1_pfd_bypass_shift                                (24)
#define REGD33_reg_p1_rxidle_bypass_shift                             (23)
#define REGD33_reg_p1_slope_manual_shift                              (22)
#define REGD33_reg_p1_slope_band_shift                                (17)
#define REGD33_reg_p1_old_mode_shift                                  (16)
#define REGD33_reg_p1_start_en_manual_mask                            (0x80000000)
#define REGD33_reg_p1_pfd_en_manual_mask                              (0x40000000)
#define REGD33_reg_p1_pfd_time_mask                                   (0x3E000000)
#define REGD33_reg_p1_pfd_bypass_mask                                 (0x01000000)
#define REGD33_reg_p1_rxidle_bypass_mask                              (0x00800000)
#define REGD33_reg_p1_slope_manual_mask                               (0x00400000)
#define REGD33_reg_p1_slope_band_mask                                 (0x003E0000)
#define REGD33_reg_p1_old_mode_mask                                   (0x00010000)
#define REGD33_reg_p1_start_en_manual(data)                           (0x80000000&((data)<<31))
#define REGD33_reg_p1_pfd_en_manual(data)                             (0x40000000&((data)<<30))
#define REGD33_reg_p1_pfd_time(data)                                  (0x3E000000&((data)<<25))
#define REGD33_reg_p1_pfd_bypass(data)                                (0x01000000&((data)<<24))
#define REGD33_reg_p1_rxidle_bypass(data)                             (0x00800000&((data)<<23))
#define REGD33_reg_p1_slope_manual(data)                              (0x00400000&((data)<<22))
#define REGD33_reg_p1_slope_band(data)                                (0x003E0000&((data)<<17))
#define REGD33_reg_p1_old_mode(data)                                  (0x00010000&((data)<<16))
#define REGD33_get_reg_p1_start_en_manual(data)                       ((0x80000000&(data))>>31)
#define REGD33_get_reg_p1_pfd_en_manual(data)                         ((0x40000000&(data))>>30)
#define REGD33_get_reg_p1_pfd_time(data)                              ((0x3E000000&(data))>>25)
#define REGD33_get_reg_p1_pfd_bypass(data)                            ((0x01000000&(data))>>24)
#define REGD33_get_reg_p1_rxidle_bypass(data)                         ((0x00800000&(data))>>23)
#define REGD33_get_reg_p1_slope_manual(data)                          ((0x00400000&(data))>>22)
#define REGD33_get_reg_p1_slope_band(data)                            ((0x003E0000&(data))>>17)
#define REGD33_get_reg_p1_old_mode(data)                              ((0x00010000&(data))>>16)


#define REGD34                                                        0xba4
#define REGD34_reg_addr                                               "0x98034ba4"
#define REGD34_reg                                                    0x98034ba4
#define REGD34_inst_addr                                              "0x02E9"
#define REGD34_inst                                                   0x02E9
#define set_REGD34_reg(data)                                          (*((volatile unsigned int*)REGD34_reg)=data)
#define get_REGD34_reg                                                (*((volatile unsigned int*)REGD34_reg))
#define REGD34_p1_fld_st_reg_shift                                    (27)
#define REGD34_p1_adp_en_fsm_reg_shift                                (26)
#define REGD34_p1_cp_en_fsm_reg_shift                                 (25)
#define REGD34_p1_coarse_fsm_reg_shift                                (18)
#define REGD34_p1_pfd_en_fsm_reg_shift                                (17)
#define REGD34_p1_slope_lv_reg_shift                                  (12)
#define REGD34_p1_slope_hv_reg_shift                                  (7)
#define REGD34_p1_slope_final_reg_shift                               (2)
#define REGD34_p1_fld_st_reg_mask                                     (0xF8000000)
#define REGD34_p1_adp_en_fsm_reg_mask                                 (0x04000000)
#define REGD34_p1_cp_en_fsm_reg_mask                                  (0x02000000)
#define REGD34_p1_coarse_fsm_reg_mask                                 (0x01FC0000)
#define REGD34_p1_pfd_en_fsm_reg_mask                                 (0x00020000)
#define REGD34_p1_slope_lv_reg_mask                                   (0x0001F000)
#define REGD34_p1_slope_hv_reg_mask                                   (0x00000F80)
#define REGD34_p1_slope_final_reg_mask                                (0x0000007C)
#define REGD34_p1_fld_st_reg(data)                                    (0xF8000000&((data)<<27))
#define REGD34_p1_adp_en_fsm_reg(data)                                (0x04000000&((data)<<26))
#define REGD34_p1_cp_en_fsm_reg(data)                                 (0x02000000&((data)<<25))
#define REGD34_p1_coarse_fsm_reg(data)                                (0x01FC0000&((data)<<18))
#define REGD34_p1_pfd_en_fsm_reg(data)                                (0x00020000&((data)<<17))
#define REGD34_p1_slope_lv_reg(data)                                  (0x0001F000&((data)<<12))
#define REGD34_p1_slope_hv_reg(data)                                  (0x00000F80&((data)<<7))
#define REGD34_p1_slope_final_reg(data)                               (0x0000007C&((data)<<2))
#define REGD34_get_p1_fld_st_reg(data)                                ((0xF8000000&(data))>>27)
#define REGD34_get_p1_adp_en_fsm_reg(data)                            ((0x04000000&(data))>>26)
#define REGD34_get_p1_cp_en_fsm_reg(data)                             ((0x02000000&(data))>>25)
#define REGD34_get_p1_coarse_fsm_reg(data)                            ((0x01FC0000&(data))>>18)
#define REGD34_get_p1_pfd_en_fsm_reg(data)                            ((0x00020000&(data))>>17)
#define REGD34_get_p1_slope_lv_reg(data)                              ((0x0001F000&(data))>>12)
#define REGD34_get_p1_slope_hv_reg(data)                              ((0x00000F80&(data))>>7)
#define REGD34_get_p1_slope_final_reg(data)                           ((0x0000007C&(data))>>2)


#define REGD35                                                        0xba8
#define REGD35_reg_addr                                               "0x98034ba8"
#define REGD35_reg                                                    0x98034ba8
#define REGD35_inst_addr                                              "0x02EA"
#define REGD35_inst                                                   0x02EA
#define set_REGD35_reg(data)                                          (*((volatile unsigned int*)REGD35_reg)=data)
#define get_REGD35_reg                                                (*((volatile unsigned int*)REGD35_reg))
#define REGD35_reg_p2_auto_mode_shift                                 (31)
#define REGD35_reg_p2_adp_en_manual_shift                             (30)
#define REGD35_reg_p2_cp_en_manual_shift                              (29)
#define REGD35_reg_p2_adap_eq_off_shift                               (28)
#define REGD35_reg_p2_adp_time_shift                                  (23)
#define REGD35_reg_p2_calib_time_shift                                (20)
#define REGD35_reg_p2_calib_manual_shift                              (19)
#define REGD35_reg_p2_calib_late_shift                                (18)
#define REGD35_reg_p2_vco_coarse_shift                                (11)
#define REGD35_reg_p2_divide_num_shift                                (4)
#define REGD35_reg_p2_init_time_shift                                 (1)
#define REGD35_reg_p2_auto_mode_mask                                  (0x80000000)
#define REGD35_reg_p2_adp_en_manual_mask                              (0x40000000)
#define REGD35_reg_p2_cp_en_manual_mask                               (0x20000000)
#define REGD35_reg_p2_adap_eq_off_mask                                (0x10000000)
#define REGD35_reg_p2_adp_time_mask                                   (0x0F800000)
#define REGD35_reg_p2_calib_time_mask                                 (0x00700000)
#define REGD35_reg_p2_calib_manual_mask                               (0x00080000)
#define REGD35_reg_p2_calib_late_mask                                 (0x00040000)
#define REGD35_reg_p2_vco_coarse_mask                                 (0x0003F800)
#define REGD35_reg_p2_divide_num_mask                                 (0x000007F0)
#define REGD35_reg_p2_init_time_mask                                  (0x0000000E)
#define REGD35_reg_p2_auto_mode(data)                                 (0x80000000&((data)<<31))
#define REGD35_reg_p2_adp_en_manual(data)                             (0x40000000&((data)<<30))
#define REGD35_reg_p2_cp_en_manual(data)                              (0x20000000&((data)<<29))
#define REGD35_reg_p2_adap_eq_off(data)                               (0x10000000&((data)<<28))
#define REGD35_reg_p2_adp_time(data)                                  (0x0F800000&((data)<<23))
#define REGD35_reg_p2_calib_time(data)                                (0x00700000&((data)<<20))
#define REGD35_reg_p2_calib_manual(data)                              (0x00080000&((data)<<19))
#define REGD35_reg_p2_calib_late(data)                                (0x00040000&((data)<<18))
#define REGD35_reg_p2_vco_coarse(data)                                (0x0003F800&((data)<<11))
#define REGD35_reg_p2_divide_num(data)                                (0x000007F0&((data)<<4))
#define REGD35_reg_p2_init_time(data)                                 (0x0000000E&((data)<<1))
#define REGD35_get_reg_p2_auto_mode(data)                             ((0x80000000&(data))>>31)
#define REGD35_get_reg_p2_adp_en_manual(data)                         ((0x40000000&(data))>>30)
#define REGD35_get_reg_p2_cp_en_manual(data)                          ((0x20000000&(data))>>29)
#define REGD35_get_reg_p2_adap_eq_off(data)                           ((0x10000000&(data))>>28)
#define REGD35_get_reg_p2_adp_time(data)                              ((0x0F800000&(data))>>23)
#define REGD35_get_reg_p2_calib_time(data)                            ((0x00700000&(data))>>20)
#define REGD35_get_reg_p2_calib_manual(data)                          ((0x00080000&(data))>>19)
#define REGD35_get_reg_p2_calib_late(data)                            ((0x00040000&(data))>>18)
#define REGD35_get_reg_p2_vco_coarse(data)                            ((0x0003F800&(data))>>11)
#define REGD35_get_reg_p2_divide_num(data)                            ((0x000007F0&(data))>>4)
#define REGD35_get_reg_p2_init_time(data)                             ((0x0000000E&(data))>>1)


#define REGD36                                                        0xbac
#define REGD36_reg_addr                                               "0x98034bac"
#define REGD36_reg                                                    0x98034bac
#define REGD36_inst_addr                                              "0x02EB"
#define REGD36_inst                                                   0x02EB
#define set_REGD36_reg(data)                                          (*((volatile unsigned int*)REGD36_reg)=data)
#define get_REGD36_reg                                                (*((volatile unsigned int*)REGD36_reg))
#define REGD36_reg_p2_lock_up_limit_shift                             (16)
#define REGD36_reg_p2_lock_dn_limit_shift                             (0)
#define REGD36_reg_p2_lock_up_limit_mask                              (0x07FF0000)
#define REGD36_reg_p2_lock_dn_limit_mask                              (0x000007FF)
#define REGD36_reg_p2_lock_up_limit(data)                             (0x07FF0000&((data)<<16))
#define REGD36_reg_p2_lock_dn_limit(data)                             (0x000007FF&(data))
#define REGD36_get_reg_p2_lock_up_limit(data)                         ((0x07FF0000&(data))>>16)
#define REGD36_get_reg_p2_lock_dn_limit(data)                         (0x000007FF&(data))


#define REGD37                                                        0xbb0
#define REGD37_reg_addr                                               "0x98034bb0"
#define REGD37_reg                                                    0x98034bb0
#define REGD37_inst_addr                                              "0x02EC"
#define REGD37_inst                                                   0x02EC
#define set_REGD37_reg(data)                                          (*((volatile unsigned int*)REGD37_reg)=data)
#define get_REGD37_reg                                                (*((volatile unsigned int*)REGD37_reg))
#define REGD37_reg_p2_cdr_cp_shift                                    (12)
#define REGD37_reg_p2_cdr_r_shift                                     (6)
#define REGD37_reg_p2_cdr_c_shift                                     (4)
#define REGD37_reg_p2_vc_sel_shift                                    (2)
#define REGD37_reg_p2_calib_reset_sel_shift                           (1)
#define REGD37_reg_p2_cdr_cp_mask                                     (0xFFFFF000)
#define REGD37_reg_p2_cdr_r_mask                                      (0x00000FC0)
#define REGD37_reg_p2_cdr_c_mask                                      (0x00000030)
#define REGD37_reg_p2_vc_sel_mask                                     (0x0000000C)
#define REGD37_reg_p2_calib_reset_sel_mask                            (0x00000002)
#define REGD37_reg_p2_cdr_cp(data)                                    (0xFFFFF000&((data)<<12))
#define REGD37_reg_p2_cdr_r(data)                                     (0x00000FC0&((data)<<6))
#define REGD37_reg_p2_cdr_c(data)                                     (0x00000030&((data)<<4))
#define REGD37_reg_p2_vc_sel(data)                                    (0x0000000C&((data)<<2))
#define REGD37_reg_p2_calib_reset_sel(data)                           (0x00000002&((data)<<1))
#define REGD37_get_reg_p2_cdr_cp(data)                                ((0xFFFFF000&(data))>>12)
#define REGD37_get_reg_p2_cdr_r(data)                                 ((0x00000FC0&(data))>>6)
#define REGD37_get_reg_p2_cdr_c(data)                                 ((0x00000030&(data))>>4)
#define REGD37_get_reg_p2_vc_sel(data)                                ((0x0000000C&(data))>>2)
#define REGD37_get_reg_p2_calib_reset_sel(data)                       ((0x00000002&(data))>>1)


#define REGD38                                                        0xbb4
#define REGD38_reg_addr                                               "0x98034bb4"
#define REGD38_reg                                                    0x98034bb4
#define REGD38_inst_addr                                              "0x02ED"
#define REGD38_inst                                                   0x02ED
#define set_REGD38_reg(data)                                          (*((volatile unsigned int*)REGD38_reg)=data)
#define get_REGD38_reg                                                (*((volatile unsigned int*)REGD38_reg))
#define REGD38_reg_p2_slope_lv_up_shift                               (21)
#define REGD38_reg_p2_slope_lv_dn_shift                               (10)
#define REGD38_reg_p2_cp_time_shift                                   (5)
#define REGD38_reg_p2_timer_4_shift                                   (0)
#define REGD38_reg_p2_slope_lv_up_mask                                (0xFFE00000)
#define REGD38_reg_p2_slope_lv_dn_mask                                (0x001FFC00)
#define REGD38_reg_p2_cp_time_mask                                    (0x000003E0)
#define REGD38_reg_p2_timer_4_mask                                    (0x0000001F)
#define REGD38_reg_p2_slope_lv_up(data)                               (0xFFE00000&((data)<<21))
#define REGD38_reg_p2_slope_lv_dn(data)                               (0x001FFC00&((data)<<10))
#define REGD38_reg_p2_cp_time(data)                                   (0x000003E0&((data)<<5))
#define REGD38_reg_p2_timer_4(data)                                   (0x0000001F&(data))
#define REGD38_get_reg_p2_slope_lv_up(data)                           ((0xFFE00000&(data))>>21)
#define REGD38_get_reg_p2_slope_lv_dn(data)                           ((0x001FFC00&(data))>>10)
#define REGD38_get_reg_p2_cp_time(data)                               ((0x000003E0&(data))>>5)
#define REGD38_get_reg_p2_timer_4(data)                               (0x0000001F&(data))


#define REGD39                                                        0xbb8
#define REGD39_reg_addr                                               "0x98034bb8"
#define REGD39_reg                                                    0x98034bb8
#define REGD39_inst_addr                                              "0x02EE"
#define REGD39_inst                                                   0x02EE
#define set_REGD39_reg(data)                                          (*((volatile unsigned int*)REGD39_reg)=data)
#define get_REGD39_reg                                                (*((volatile unsigned int*)REGD39_reg))
#define REGD39_reg_p2_slope_hv_up_shift                               (21)
#define REGD39_reg_p2_slope_hv_dn_shift                               (10)
#define REGD39_reg_p2_timer_5_shift                                   (9)
#define REGD39_reg_p2_timer_6_shift                                   (4)
#define REGD39_reg_p2_slope_hv_up_mask                                (0xFFE00000)
#define REGD39_reg_p2_slope_hv_dn_mask                                (0x001FFC00)
#define REGD39_reg_p2_timer_5_mask                                    (0x00000200)
#define REGD39_reg_p2_timer_6_mask                                    (0x000001F0)
#define REGD39_reg_p2_slope_hv_up(data)                               (0xFFE00000&((data)<<21))
#define REGD39_reg_p2_slope_hv_dn(data)                               (0x001FFC00&((data)<<10))
#define REGD39_reg_p2_timer_5(data)                                   (0x00000200&((data)<<9))
#define REGD39_reg_p2_timer_6(data)                                   (0x000001F0&((data)<<4))
#define REGD39_get_reg_p2_slope_hv_up(data)                           ((0xFFE00000&(data))>>21)
#define REGD39_get_reg_p2_slope_hv_dn(data)                           ((0x001FFC00&(data))>>10)
#define REGD39_get_reg_p2_timer_5(data)                               ((0x00000200&(data))>>9)
#define REGD39_get_reg_p2_timer_6(data)                               ((0x000001F0&(data))>>4)


#define REGD40                                                        0xbbc
#define REGD40_reg_addr                                               "0x98034bbc"
#define REGD40_reg                                                    0x98034bbc
#define REGD40_inst_addr                                              "0x02EF"
#define REGD40_inst                                                   0x02EF
#define set_REGD40_reg(data)                                          (*((volatile unsigned int*)REGD40_reg)=data)
#define get_REGD40_reg                                                (*((volatile unsigned int*)REGD40_reg))
#define REGD40_reg_p2_start_en_manual_shift                           (31)
#define REGD40_reg_p2_pfd_en_manual_shift                             (30)
#define REGD40_reg_p2_pfd_time_shift                                  (25)
#define REGD40_reg_p2_pfd_bypass_shift                                (24)
#define REGD40_reg_p2_rxidle_bypass_shift                             (23)
#define REGD40_reg_p2_slope_manual_shift                              (22)
#define REGD40_reg_p2_slope_band_shift                                (17)
#define REGD40_reg_p2_old_mode_shift                                  (16)
#define REGD40_reg_p2_start_en_manual_mask                            (0x80000000)
#define REGD40_reg_p2_pfd_en_manual_mask                              (0x40000000)
#define REGD40_reg_p2_pfd_time_mask                                   (0x3E000000)
#define REGD40_reg_p2_pfd_bypass_mask                                 (0x01000000)
#define REGD40_reg_p2_rxidle_bypass_mask                              (0x00800000)
#define REGD40_reg_p2_slope_manual_mask                               (0x00400000)
#define REGD40_reg_p2_slope_band_mask                                 (0x003E0000)
#define REGD40_reg_p2_old_mode_mask                                   (0x00010000)
#define REGD40_reg_p2_start_en_manual(data)                           (0x80000000&((data)<<31))
#define REGD40_reg_p2_pfd_en_manual(data)                             (0x40000000&((data)<<30))
#define REGD40_reg_p2_pfd_time(data)                                  (0x3E000000&((data)<<25))
#define REGD40_reg_p2_pfd_bypass(data)                                (0x01000000&((data)<<24))
#define REGD40_reg_p2_rxidle_bypass(data)                             (0x00800000&((data)<<23))
#define REGD40_reg_p2_slope_manual(data)                              (0x00400000&((data)<<22))
#define REGD40_reg_p2_slope_band(data)                                (0x003E0000&((data)<<17))
#define REGD40_reg_p2_old_mode(data)                                  (0x00010000&((data)<<16))
#define REGD40_get_reg_p2_start_en_manual(data)                       ((0x80000000&(data))>>31)
#define REGD40_get_reg_p2_pfd_en_manual(data)                         ((0x40000000&(data))>>30)
#define REGD40_get_reg_p2_pfd_time(data)                              ((0x3E000000&(data))>>25)
#define REGD40_get_reg_p2_pfd_bypass(data)                            ((0x01000000&(data))>>24)
#define REGD40_get_reg_p2_rxidle_bypass(data)                         ((0x00800000&(data))>>23)
#define REGD40_get_reg_p2_slope_manual(data)                          ((0x00400000&(data))>>22)
#define REGD40_get_reg_p2_slope_band(data)                            ((0x003E0000&(data))>>17)
#define REGD40_get_reg_p2_old_mode(data)                              ((0x00010000&(data))>>16)


#define REGD41                                                        0xbc0
#define REGD41_reg_addr                                               "0x98034bc0"
#define REGD41_reg                                                    0x98034bc0
#define REGD41_inst_addr                                              "0x02F0"
#define REGD41_inst                                                   0x02F0
#define set_REGD41_reg(data)                                          (*((volatile unsigned int*)REGD41_reg)=data)
#define get_REGD41_reg                                                (*((volatile unsigned int*)REGD41_reg))
#define REGD41_p2_fld_st_reg_shift                                    (27)
#define REGD41_p2_adp_en_fsm_reg_shift                                (26)
#define REGD41_p2_cp_en_fsm_reg_shift                                 (25)
#define REGD41_p2_coarse_fsm_reg_shift                                (18)
#define REGD41_p2_pfd_en_fsm_reg_shift                                (17)
#define REGD41_p2_slope_lv_reg_shift                                  (12)
#define REGD41_p2_slope_hv_reg_shift                                  (7)
#define REGD41_p2_slope_final_reg_shift                               (2)
#define REGD41_p2_fld_st_reg_mask                                     (0xF8000000)
#define REGD41_p2_adp_en_fsm_reg_mask                                 (0x04000000)
#define REGD41_p2_cp_en_fsm_reg_mask                                  (0x02000000)
#define REGD41_p2_coarse_fsm_reg_mask                                 (0x01FC0000)
#define REGD41_p2_pfd_en_fsm_reg_mask                                 (0x00020000)
#define REGD41_p2_slope_lv_reg_mask                                   (0x0001F000)
#define REGD41_p2_slope_hv_reg_mask                                   (0x00000F80)
#define REGD41_p2_slope_final_reg_mask                                (0x0000007C)
#define REGD41_p2_fld_st_reg(data)                                    (0xF8000000&((data)<<27))
#define REGD41_p2_adp_en_fsm_reg(data)                                (0x04000000&((data)<<26))
#define REGD41_p2_cp_en_fsm_reg(data)                                 (0x02000000&((data)<<25))
#define REGD41_p2_coarse_fsm_reg(data)                                (0x01FC0000&((data)<<18))
#define REGD41_p2_pfd_en_fsm_reg(data)                                (0x00020000&((data)<<17))
#define REGD41_p2_slope_lv_reg(data)                                  (0x0001F000&((data)<<12))
#define REGD41_p2_slope_hv_reg(data)                                  (0x00000F80&((data)<<7))
#define REGD41_p2_slope_final_reg(data)                               (0x0000007C&((data)<<2))
#define REGD41_get_p2_fld_st_reg(data)                                ((0xF8000000&(data))>>27)
#define REGD41_get_p2_adp_en_fsm_reg(data)                            ((0x04000000&(data))>>26)
#define REGD41_get_p2_cp_en_fsm_reg(data)                             ((0x02000000&(data))>>25)
#define REGD41_get_p2_coarse_fsm_reg(data)                            ((0x01FC0000&(data))>>18)
#define REGD41_get_p2_pfd_en_fsm_reg(data)                            ((0x00020000&(data))>>17)
#define REGD41_get_p2_slope_lv_reg(data)                              ((0x0001F000&(data))>>12)
#define REGD41_get_p2_slope_hv_reg(data)                              ((0x00000F80&(data))>>7)
#define REGD41_get_p2_slope_final_reg(data)                           ((0x0000007C&(data))>>2)


#define REGD42                                                        0xbc4
#define REGD42_reg_addr                                               "0x98034bc4"
#define REGD42_reg                                                    0x98034bc4
#define REGD42_inst_addr                                              "0x02F1"
#define REGD42_inst                                                   0x02F1
#define set_REGD42_reg(data)                                          (*((volatile unsigned int*)REGD42_reg)=data)
#define get_REGD42_reg                                                (*((volatile unsigned int*)REGD42_reg))
#define REGD42_p0_ck_md_rstb_shift                                    (31)
#define REGD42_reg_p0_ck_md_threshold_shift                           (25)
#define REGD42_reg_p0_ck_md_debounce_shift                            (18)
#define REGD42_reg_p0_ck_md_sel_shift                                 (16)
#define REGD42_reg_p0_ck_md_auto_shift                                (15)
#define REGD42_reg_p0_ck_md_adj_shift                                 (11)
#define REGD42_reg_p0_ck_error_limit_shift                            (6)
#define REGD42_reg_p0_ck_md_reserved_shift                            (2)
#define REGD42_p0_ck_md_rstb_mask                                     (0x80000000)
#define REGD42_reg_p0_ck_md_threshold_mask                            (0x7E000000)
#define REGD42_reg_p0_ck_md_debounce_mask                             (0x01FC0000)
#define REGD42_reg_p0_ck_md_sel_mask                                  (0x00030000)
#define REGD42_reg_p0_ck_md_auto_mask                                 (0x00008000)
#define REGD42_reg_p0_ck_md_adj_mask                                  (0x00007800)
#define REGD42_reg_p0_ck_error_limit_mask                             (0x000007C0)
#define REGD42_reg_p0_ck_md_reserved_mask                             (0x0000003C)
#define REGD42_p0_ck_md_rstb(data)                                    (0x80000000&((data)<<31))
#define REGD42_reg_p0_ck_md_threshold(data)                           (0x7E000000&((data)<<25))
#define REGD42_reg_p0_ck_md_debounce(data)                            (0x01FC0000&((data)<<18))
#define REGD42_reg_p0_ck_md_sel(data)                                 (0x00030000&((data)<<16))
#define REGD42_reg_p0_ck_md_auto(data)                                (0x00008000&((data)<<15))
#define REGD42_reg_p0_ck_md_adj(data)                                 (0x00007800&((data)<<11))
#define REGD42_reg_p0_ck_error_limit(data)                            (0x000007C0&((data)<<6))
#define REGD42_reg_p0_ck_md_reserved(data)                            (0x0000003C&((data)<<2))
#define REGD42_get_p0_ck_md_rstb(data)                                ((0x80000000&(data))>>31)
#define REGD42_get_reg_p0_ck_md_threshold(data)                       ((0x7E000000&(data))>>25)
#define REGD42_get_reg_p0_ck_md_debounce(data)                        ((0x01FC0000&(data))>>18)
#define REGD42_get_reg_p0_ck_md_sel(data)                             ((0x00030000&(data))>>16)
#define REGD42_get_reg_p0_ck_md_auto(data)                            ((0x00008000&(data))>>15)
#define REGD42_get_reg_p0_ck_md_adj(data)                             ((0x00007800&(data))>>11)
#define REGD42_get_reg_p0_ck_error_limit(data)                        ((0x000007C0&(data))>>6)
#define REGD42_get_reg_p0_ck_md_reserved(data)                        ((0x0000003C&(data))>>2)


#define REGD43                                                        0xbc8
#define REGD43_reg_addr                                               "0x98034bc8"
#define REGD43_reg                                                    0x98034bc8
#define REGD43_inst_addr                                              "0x02F2"
#define REGD43_inst                                                   0x02F2
#define set_REGD43_reg(data)                                          (*((volatile unsigned int*)REGD43_reg)=data)
#define get_REGD43_reg                                                (*((volatile unsigned int*)REGD43_reg))
#define REGD43_p0_ck_md_count_shift                                   (19)
#define REGD43_p0_ck_rate_shift                                       (15)
#define REGD43_p0_unstable_count_shift                                (10)
#define REGD43_p0_ck_md_ok_shift                                      (9)
#define REGD43_p0_clock_unstable_flag_shift                           (8)
#define REGD43_p0_ck_md_count_mask                                    (0xFFF80000)
#define REGD43_p0_ck_rate_mask                                        (0x00078000)
#define REGD43_p0_unstable_count_mask                                 (0x00007C00)
#define REGD43_p0_ck_md_ok_mask                                       (0x00000200)
#define REGD43_p0_clock_unstable_flag_mask                            (0x00000100)
#define REGD43_p0_ck_md_count(data)                                   (0xFFF80000&((data)<<19))
#define REGD43_p0_ck_rate(data)                                       (0x00078000&((data)<<15))
#define REGD43_p0_unstable_count(data)                                (0x00007C00&((data)<<10))
#define REGD43_p0_ck_md_ok(data)                                      (0x00000200&((data)<<9))
#define REGD43_p0_clock_unstable_flag(data)                           (0x00000100&((data)<<8))
#define REGD43_get_p0_ck_md_count(data)                               ((0xFFF80000&(data))>>19)
#define REGD43_get_p0_ck_rate(data)                                   ((0x00078000&(data))>>15)
#define REGD43_get_p0_unstable_count(data)                            ((0x00007C00&(data))>>10)
#define REGD43_get_p0_ck_md_ok(data)                                  ((0x00000200&(data))>>9)
#define REGD43_get_p0_clock_unstable_flag(data)                       ((0x00000100&(data))>>8)


#define REGD44                                                        0xbcc
#define REGD44_reg_addr                                               "0x98034bcc"
#define REGD44_reg                                                    0x98034bcc
#define REGD44_inst_addr                                              "0x02F3"
#define REGD44_inst                                                   0x02F3
#define set_REGD44_reg(data)                                          (*((volatile unsigned int*)REGD44_reg)=data)
#define get_REGD44_reg                                                (*((volatile unsigned int*)REGD44_reg))
#define REGD44_p1_ck_md_rstb_shift                                    (31)
#define REGD44_reg_p1_ck_md_threshold_shift                           (25)
#define REGD44_reg_p1_ck_md_debounce_shift                            (18)
#define REGD44_reg_p1_ck_md_sel_shift                                 (16)
#define REGD44_reg_p1_ck_md_auto_shift                                (15)
#define REGD44_reg_p1_ck_md_adj_shift                                 (11)
#define REGD44_reg_p1_ck_error_limit_shift                            (6)
#define REGD44_reg_p1_ck_md_reserved_shift                            (2)
#define REGD44_p1_ck_md_rstb_mask                                     (0x80000000)
#define REGD44_reg_p1_ck_md_threshold_mask                            (0x7E000000)
#define REGD44_reg_p1_ck_md_debounce_mask                             (0x01FC0000)
#define REGD44_reg_p1_ck_md_sel_mask                                  (0x00030000)
#define REGD44_reg_p1_ck_md_auto_mask                                 (0x00008000)
#define REGD44_reg_p1_ck_md_adj_mask                                  (0x00007800)
#define REGD44_reg_p1_ck_error_limit_mask                             (0x000007C0)
#define REGD44_reg_p1_ck_md_reserved_mask                             (0x0000003C)
#define REGD44_p1_ck_md_rstb(data)                                    (0x80000000&((data)<<31))
#define REGD44_reg_p1_ck_md_threshold(data)                           (0x7E000000&((data)<<25))
#define REGD44_reg_p1_ck_md_debounce(data)                            (0x01FC0000&((data)<<18))
#define REGD44_reg_p1_ck_md_sel(data)                                 (0x00030000&((data)<<16))
#define REGD44_reg_p1_ck_md_auto(data)                                (0x00008000&((data)<<15))
#define REGD44_reg_p1_ck_md_adj(data)                                 (0x00007800&((data)<<11))
#define REGD44_reg_p1_ck_error_limit(data)                            (0x000007C0&((data)<<6))
#define REGD44_reg_p1_ck_md_reserved(data)                            (0x0000003C&((data)<<2))
#define REGD44_get_p1_ck_md_rstb(data)                                ((0x80000000&(data))>>31)
#define REGD44_get_reg_p1_ck_md_threshold(data)                       ((0x7E000000&(data))>>25)
#define REGD44_get_reg_p1_ck_md_debounce(data)                        ((0x01FC0000&(data))>>18)
#define REGD44_get_reg_p1_ck_md_sel(data)                             ((0x00030000&(data))>>16)
#define REGD44_get_reg_p1_ck_md_auto(data)                            ((0x00008000&(data))>>15)
#define REGD44_get_reg_p1_ck_md_adj(data)                             ((0x00007800&(data))>>11)
#define REGD44_get_reg_p1_ck_error_limit(data)                        ((0x000007C0&(data))>>6)
#define REGD44_get_reg_p1_ck_md_reserved(data)                        ((0x0000003C&(data))>>2)


#define REGD45                                                        0xbd0
#define REGD45_reg_addr                                               "0x98034bd0"
#define REGD45_reg                                                    0x98034bd0
#define REGD45_inst_addr                                              "0x02F4"
#define REGD45_inst                                                   0x02F4
#define set_REGD45_reg(data)                                          (*((volatile unsigned int*)REGD45_reg)=data)
#define get_REGD45_reg                                                (*((volatile unsigned int*)REGD45_reg))
#define REGD45_p1_ck_md_count_shift                                   (19)
#define REGD45_p1_ck_rate_shift                                       (15)
#define REGD45_p1_unstable_count_shift                                (10)
#define REGD45_p1_ck_md_ok_shift                                      (9)
#define REGD45_p1_clock_unstable_flag_shift                           (8)
#define REGD45_p1_ck_md_count_mask                                    (0xFFF80000)
#define REGD45_p1_ck_rate_mask                                        (0x00078000)
#define REGD45_p1_unstable_count_mask                                 (0x00007C00)
#define REGD45_p1_ck_md_ok_mask                                       (0x00000200)
#define REGD45_p1_clock_unstable_flag_mask                            (0x00000100)
#define REGD45_p1_ck_md_count(data)                                   (0xFFF80000&((data)<<19))
#define REGD45_p1_ck_rate(data)                                       (0x00078000&((data)<<15))
#define REGD45_p1_unstable_count(data)                                (0x00007C00&((data)<<10))
#define REGD45_p1_ck_md_ok(data)                                      (0x00000200&((data)<<9))
#define REGD45_p1_clock_unstable_flag(data)                           (0x00000100&((data)<<8))
#define REGD45_get_p1_ck_md_count(data)                               ((0xFFF80000&(data))>>19)
#define REGD45_get_p1_ck_rate(data)                                   ((0x00078000&(data))>>15)
#define REGD45_get_p1_unstable_count(data)                            ((0x00007C00&(data))>>10)
#define REGD45_get_p1_ck_md_ok(data)                                  ((0x00000200&(data))>>9)
#define REGD45_get_p1_clock_unstable_flag(data)                       ((0x00000100&(data))>>8)


#define REGD46                                                        0xbd4
#define REGD46_reg_addr                                               "0x98034bd4"
#define REGD46_reg                                                    0x98034bd4
#define REGD46_inst_addr                                              "0x02F5"
#define REGD46_inst                                                   0x02F5
#define set_REGD46_reg(data)                                          (*((volatile unsigned int*)REGD46_reg)=data)
#define get_REGD46_reg                                                (*((volatile unsigned int*)REGD46_reg))
#define REGD46_p2_ck_md_rstb_shift                                    (31)
#define REGD46_reg_p2_ck_md_threshold_shift                           (25)
#define REGD46_reg_p2_ck_md_debounce_shift                            (18)
#define REGD46_reg_p2_ck_md_sel_shift                                 (16)
#define REGD46_reg_p2_ck_md_auto_shift                                (15)
#define REGD46_reg_p2_ck_md_adj_shift                                 (11)
#define REGD46_reg_p2_ck_error_limit_shift                            (6)
#define REGD46_reg_p2_ck_md_reserved_shift                            (2)
#define REGD46_p2_ck_md_rstb_mask                                     (0x80000000)
#define REGD46_reg_p2_ck_md_threshold_mask                            (0x7E000000)
#define REGD46_reg_p2_ck_md_debounce_mask                             (0x01FC0000)
#define REGD46_reg_p2_ck_md_sel_mask                                  (0x00030000)
#define REGD46_reg_p2_ck_md_auto_mask                                 (0x00008000)
#define REGD46_reg_p2_ck_md_adj_mask                                  (0x00007800)
#define REGD46_reg_p2_ck_error_limit_mask                             (0x000007C0)
#define REGD46_reg_p2_ck_md_reserved_mask                             (0x0000003C)
#define REGD46_p2_ck_md_rstb(data)                                    (0x80000000&((data)<<31))
#define REGD46_reg_p2_ck_md_threshold(data)                           (0x7E000000&((data)<<25))
#define REGD46_reg_p2_ck_md_debounce(data)                            (0x01FC0000&((data)<<18))
#define REGD46_reg_p2_ck_md_sel(data)                                 (0x00030000&((data)<<16))
#define REGD46_reg_p2_ck_md_auto(data)                                (0x00008000&((data)<<15))
#define REGD46_reg_p2_ck_md_adj(data)                                 (0x00007800&((data)<<11))
#define REGD46_reg_p2_ck_error_limit(data)                            (0x000007C0&((data)<<6))
#define REGD46_reg_p2_ck_md_reserved(data)                            (0x0000003C&((data)<<2))
#define REGD46_get_p2_ck_md_rstb(data)                                ((0x80000000&(data))>>31)
#define REGD46_get_reg_p2_ck_md_threshold(data)                       ((0x7E000000&(data))>>25)
#define REGD46_get_reg_p2_ck_md_debounce(data)                        ((0x01FC0000&(data))>>18)
#define REGD46_get_reg_p2_ck_md_sel(data)                             ((0x00030000&(data))>>16)
#define REGD46_get_reg_p2_ck_md_auto(data)                            ((0x00008000&(data))>>15)
#define REGD46_get_reg_p2_ck_md_adj(data)                             ((0x00007800&(data))>>11)
#define REGD46_get_reg_p2_ck_error_limit(data)                        ((0x000007C0&(data))>>6)
#define REGD46_get_reg_p2_ck_md_reserved(data)                        ((0x0000003C&(data))>>2)


#define REGD47                                                        0xbd8
#define REGD47_reg_addr                                               "0x98034bd8"
#define REGD47_reg                                                    0x98034bd8
#define REGD47_inst_addr                                              "0x02F6"
#define REGD47_inst                                                   0x02F6
#define set_REGD47_reg(data)                                          (*((volatile unsigned int*)REGD47_reg)=data)
#define get_REGD47_reg                                                (*((volatile unsigned int*)REGD47_reg))
#define REGD47_p2_ck_md_count_shift                                   (19)
#define REGD47_p2_ck_rate_shift                                       (15)
#define REGD47_p2_unstable_count_shift                                (10)
#define REGD47_p2_ck_md_ok_shift                                      (9)
#define REGD47_p2_clock_unstable_flag_shift                           (8)
#define REGD47_p2_ck_md_count_mask                                    (0xFFF80000)
#define REGD47_p2_ck_rate_mask                                        (0x00078000)
#define REGD47_p2_unstable_count_mask                                 (0x00007C00)
#define REGD47_p2_ck_md_ok_mask                                       (0x00000200)
#define REGD47_p2_clock_unstable_flag_mask                            (0x00000100)
#define REGD47_p2_ck_md_count(data)                                   (0xFFF80000&((data)<<19))
#define REGD47_p2_ck_rate(data)                                       (0x00078000&((data)<<15))
#define REGD47_p2_unstable_count(data)                                (0x00007C00&((data)<<10))
#define REGD47_p2_ck_md_ok(data)                                      (0x00000200&((data)<<9))
#define REGD47_p2_clock_unstable_flag(data)                           (0x00000100&((data)<<8))
#define REGD47_get_p2_ck_md_count(data)                               ((0xFFF80000&(data))>>19)
#define REGD47_get_p2_ck_rate(data)                                   ((0x00078000&(data))>>15)
#define REGD47_get_p2_unstable_count(data)                            ((0x00007C00&(data))>>10)
#define REGD47_get_p2_ck_md_ok(data)                                  ((0x00000200&(data))>>9)
#define REGD47_get_p2_clock_unstable_flag(data)                       ((0x00000100&(data))>>8)


#define REGD48                                                        0xbdc
#define REGD48_reg_addr                                               "0x98034bdc"
#define REGD48_reg                                                    0x98034bdc
#define REGD48_inst_addr                                              "0x02F7"
#define REGD48_inst                                                   0x02F7
#define set_REGD48_reg(data)                                          (*((volatile unsigned int*)REGD48_reg)=data)
#define get_REGD48_reg                                                (*((volatile unsigned int*)REGD48_reg))
#define REGD48_reg_dig_debug_sel_shift                                (28)
#define REGD48_reg_dig_reserved_0_shift                               (20)
#define REGD48_reg_dig_reserved_1_shift                               (12)
#define REGD48_reg_dig_reserved_2_shift                               (4)
#define REGD48_reg_dig_debug_sel_mask                                 (0xF0000000)
#define REGD48_reg_dig_reserved_0_mask                                (0x0FF00000)
#define REGD48_reg_dig_reserved_1_mask                                (0x000FF000)
#define REGD48_reg_dig_reserved_2_mask                                (0x00000FF0)
#define REGD48_reg_dig_debug_sel(data)                                (0xF0000000&((data)<<28))
#define REGD48_reg_dig_reserved_0(data)                               (0x0FF00000&((data)<<20))
#define REGD48_reg_dig_reserved_1(data)                               (0x000FF000&((data)<<12))
#define REGD48_reg_dig_reserved_2(data)                               (0x00000FF0&((data)<<4))
#define REGD48_get_reg_dig_debug_sel(data)                            ((0xF0000000&(data))>>28)
#define REGD48_get_reg_dig_reserved_0(data)                           ((0x0FF00000&(data))>>20)
#define REGD48_get_reg_dig_reserved_1(data)                           ((0x000FF000&(data))>>12)
#define REGD48_get_reg_dig_reserved_2(data)                           ((0x00000FF0&(data))>>4)


#define REGD49                                                        0xbe0
#define REGD49_reg_addr                                               "0x98034be0"
#define REGD49_reg                                                    0x98034be0
#define REGD49_inst_addr                                              "0x02F8"
#define REGD49_inst                                                   0x02F8
#define set_REGD49_reg(data)                                          (*((volatile unsigned int*)REGD49_reg)=data)
#define get_REGD49_reg                                                (*((volatile unsigned int*)REGD49_reg))
#define REGD49_reg_p0_st_m_value_shift                                (0)
#define REGD49_reg_p0_st_m_value_mask                                 (0xFFFFFFFF)
#define REGD49_reg_p0_st_m_value(data)                                (0xFFFFFFFF&(data))
#define REGD49_get_reg_p0_st_m_value(data)                            (0xFFFFFFFF&(data))


#define REGD50                                                        0xbe4
#define REGD50_reg_addr                                               "0x98034be4"
#define REGD50_reg                                                    0x98034be4
#define REGD50_inst_addr                                              "0x02F9"
#define REGD50_inst                                                   0x02F9
#define set_REGD50_reg(data)                                          (*((volatile unsigned int*)REGD50_reg)=data)
#define get_REGD50_reg                                                (*((volatile unsigned int*)REGD50_reg))
#define REGD50_reg_p1_st_m_value_shift                                (0)
#define REGD50_reg_p1_st_m_value_mask                                 (0xFFFFFFFF)
#define REGD50_reg_p1_st_m_value(data)                                (0xFFFFFFFF&(data))
#define REGD50_get_reg_p1_st_m_value(data)                            (0xFFFFFFFF&(data))


#define REGD51                                                        0xbe8
#define REGD51_reg_addr                                               "0x98034be8"
#define REGD51_reg                                                    0x98034be8
#define REGD51_inst_addr                                              "0x02FA"
#define REGD51_inst                                                   0x02FA
#define set_REGD51_reg(data)                                          (*((volatile unsigned int*)REGD51_reg)=data)
#define get_REGD51_reg                                                (*((volatile unsigned int*)REGD51_reg))
#define REGD51_reg_p2_st_m_value_shift                                (0)
#define REGD51_reg_p2_st_m_value_mask                                 (0xFFFFFFFF)
#define REGD51_reg_p2_st_m_value(data)                                (0xFFFFFFFF&(data))
#define REGD51_get_reg_p2_st_m_value(data)                            (0xFFFFFFFF&(data))


#define REGD52                                                        0xbec
#define REGD52_reg_addr                                               "0x98034bec"
#define REGD52_reg                                                    0x98034bec
#define REGD52_inst_addr                                              "0x02FB"
#define REGD52_inst                                                   0x02FB
#define set_REGD52_reg(data)                                          (*((volatile unsigned int*)REGD52_reg)=data)
#define get_REGD52_reg                                                (*((volatile unsigned int*)REGD52_reg))
#define REGD52_reg_eye_monitor_ck_sel_shift                           (20)
#define REGD52_eye_monitor_dout_shift                                 (0)
#define REGD52_reg_eye_monitor_ck_sel_mask                            (0x00300000)
#define REGD52_eye_monitor_dout_mask                                  (0x0000FFFF)
#define REGD52_reg_eye_monitor_ck_sel(data)                           (0x00300000&((data)<<20))
#define REGD52_eye_monitor_dout(data)                                 (0x0000FFFF&(data))
#define REGD52_get_reg_eye_monitor_ck_sel(data)                       ((0x00300000&(data))>>20)
#define REGD52_get_eye_monitor_dout(data)                             (0x0000FFFF&(data))


#define REGD53                                                        0xbf0
#define REGD53_reg_addr                                               "0x98034bf0"
#define REGD53_reg                                                    0x98034bf0
#define REGD53_inst_addr                                              "0x02FC"
#define REGD53_inst                                                   0x02FC
#define set_REGD53_reg(data)                                          (*((volatile unsigned int*)REGD53_reg)=data)
#define get_REGD53_reg                                                (*((volatile unsigned int*)REGD53_reg))
#define REGD53_reg_p0_st_m_value_g_shift                              (0)
#define REGD53_reg_p0_st_m_value_g_mask                               (0xFFFFFFFF)
#define REGD53_reg_p0_st_m_value_g(data)                              (0xFFFFFFFF&(data))
#define REGD53_get_reg_p0_st_m_value_g(data)                          (0xFFFFFFFF&(data))


#define REGD54                                                        0xbf4
#define REGD54_reg_addr                                               "0x98034bf4"
#define REGD54_reg                                                    0x98034bf4
#define REGD54_inst_addr                                              "0x02FD"
#define REGD54_inst                                                   0x02FD
#define set_REGD54_reg(data)                                          (*((volatile unsigned int*)REGD54_reg)=data)
#define get_REGD54_reg                                                (*((volatile unsigned int*)REGD54_reg))
#define REGD54_reg_p1_st_m_value_g_shift                              (0)
#define REGD54_reg_p1_st_m_value_g_mask                               (0xFFFFFFFF)
#define REGD54_reg_p1_st_m_value_g(data)                              (0xFFFFFFFF&(data))
#define REGD54_get_reg_p1_st_m_value_g(data)                          (0xFFFFFFFF&(data))


#define REGD55                                                        0xbf8
#define REGD55_reg_addr                                               "0x98034bf8"
#define REGD55_reg                                                    0x98034bf8
#define REGD55_inst_addr                                              "0x02FE"
#define REGD55_inst                                                   0x02FE
#define set_REGD55_reg(data)                                          (*((volatile unsigned int*)REGD55_reg)=data)
#define get_REGD55_reg                                                (*((volatile unsigned int*)REGD55_reg))
#define REGD55_reg_p2_st_m_value_g_shift                              (0)
#define REGD55_reg_p2_st_m_value_g_mask                               (0xFFFFFFFF)
#define REGD55_reg_p2_st_m_value_g(data)                              (0xFFFFFFFF&(data))
#define REGD55_get_reg_p2_st_m_value_g(data)                          (0xFFFFFFFF&(data))


#define REGD56                                                        0xbfc
#define REGD56_reg_addr                                               "0x98034bfc"
#define REGD56_reg                                                    0x98034bfc
#define REGD56_inst_addr                                              "0x02FF"
#define REGD56_inst                                                   0x02FF
#define set_REGD56_reg(data)                                          (*((volatile unsigned int*)REGD56_reg)=data)
#define get_REGD56_reg                                                (*((volatile unsigned int*)REGD56_reg))
#define REGD56_reg_p0_st_m_value_b_shift                              (0)
#define REGD56_reg_p0_st_m_value_b_mask                               (0xFFFFFFFF)
#define REGD56_reg_p0_st_m_value_b(data)                              (0xFFFFFFFF&(data))
#define REGD56_get_reg_p0_st_m_value_b(data)                          (0xFFFFFFFF&(data))


#define REGD57                                                        0xc00
#define REGD57_reg_addr                                               "0x98034c00"
#define REGD57_reg                                                    0x98034c00
#define REGD57_inst_addr                                              "0x0300"
#define REGD57_inst                                                   0x0300
#define set_REGD57_reg(data)                                          (*((volatile unsigned int*)REGD57_reg)=data)
#define get_REGD57_reg                                                (*((volatile unsigned int*)REGD57_reg))
#define REGD57_reg_p1_st_m_value_b_shift                              (0)
#define REGD57_reg_p1_st_m_value_b_mask                               (0xFFFFFFFF)
#define REGD57_reg_p1_st_m_value_b(data)                              (0xFFFFFFFF&(data))
#define REGD57_get_reg_p1_st_m_value_b(data)                          (0xFFFFFFFF&(data))


#define REGD58                                                        0xc04
#define REGD58_reg_addr                                               "0x98034c04"
#define REGD58_reg                                                    0x98034c04
#define REGD58_inst_addr                                              "0x0301"
#define REGD58_inst                                                   0x0301
#define set_REGD58_reg(data)                                          (*((volatile unsigned int*)REGD58_reg)=data)
#define get_REGD58_reg                                                (*((volatile unsigned int*)REGD58_reg))
#define REGD58_reg_p2_st_m_value_b_shift                              (0)
#define REGD58_reg_p2_st_m_value_b_mask                               (0xFFFFFFFF)
#define REGD58_reg_p2_st_m_value_b(data)                              (0xFFFFFFFF&(data))
#define REGD58_get_reg_p2_st_m_value_b(data)                          (0xFFFFFFFF&(data))
#endif
