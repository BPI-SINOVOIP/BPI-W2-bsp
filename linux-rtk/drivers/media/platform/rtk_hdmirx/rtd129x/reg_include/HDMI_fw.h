/*===========*@date:2015/3/6===========*/

#ifndef _HDMI_RX_REG_H_INCLUDED_
#define _HDMI_RX_REG_H_INCLUDED_

#define TMDS_MSR0                                                     0x000
#define TMDS_MSR0_reg_addr                                            "0x98034000"
#define TMDS_MSR0_reg                                                 0x98034000
#define TMDS_MSR0_inst_addr                                           "0x0000"
#define TMDS_MSR0_inst                                                0x0000
#define set_TMDS_MSR0_reg(data)                                       (*((volatile unsigned int*)TMDS_MSR0_reg)=data)
#define get_TMDS_MSR0_reg                                             (*((volatile unsigned int*)TMDS_MSR0_reg))
#define TMDS_MSR0_tmm_shift                                           (7)
#define TMDS_MSR0_mt_shift                                            (4)
#define TMDS_MSR0_ncp_shift                                           (0)
#define TMDS_MSR0_tmm_mask                                            (0x00000080)
#define TMDS_MSR0_mt_mask                                             (0x00000070)
#define TMDS_MSR0_ncp_mask                                            (0x0000000F)
#define TMDS_MSR0_tmm(data)                                           (0x00000080&((data)<<7))
#define TMDS_MSR0_mt(data)                                            (0x00000070&((data)<<4))
#define TMDS_MSR0_ncp(data)                                           (0x0000000F&(data))
#define TMDS_MSR0_get_tmm(data)                                       ((0x00000080&(data))>>7)
#define TMDS_MSR0_get_mt(data)                                        ((0x00000070&(data))>>4)
#define TMDS_MSR0_get_ncp(data)                                       (0x0000000F&(data))


#define TMDS_MSR1                                                     0x004
#define TMDS_MSR1_reg_addr                                            "0x98034004"
#define TMDS_MSR1_reg                                                 0x98034004
#define TMDS_MSR1_inst_addr                                           "0x0001"
#define TMDS_MSR1_inst                                                0x0001
#define set_TMDS_MSR1_reg(data)                                       (*((volatile unsigned int*)TMDS_MSR1_reg)=data)
#define get_TMDS_MSR1_reg                                             (*((volatile unsigned int*)TMDS_MSR1_reg))
#define TMDS_MSR1_tms_shift                                           (12)
#define TMDS_MSR1_mrs_shift                                           (10)
#define TMDS_MSR1_ms_shift                                            (8)
#define TMDS_MSR1_ctc_shift                                           (7)
#define TMDS_MSR1_vmr_shift                                           (0)
#define TMDS_MSR1_tms_mask                                            (0x00001000)
#define TMDS_MSR1_mrs_mask                                            (0x00000C00)
#define TMDS_MSR1_ms_mask                                             (0x00000300)
#define TMDS_MSR1_ctc_mask                                            (0x00000080)
#define TMDS_MSR1_vmr_mask                                            (0x0000007F)
#define TMDS_MSR1_tms(data)                                           (0x00001000&((data)<<12))
#define TMDS_MSR1_mrs(data)                                           (0x00000C00&((data)<<10))
#define TMDS_MSR1_ms(data)                                            (0x00000300&((data)<<8))
#define TMDS_MSR1_ctc(data)                                           (0x00000080&((data)<<7))
#define TMDS_MSR1_vmr(data)                                           (0x0000007F&(data))
#define TMDS_MSR1_get_tms(data)                                       ((0x00001000&(data))>>12)
#define TMDS_MSR1_get_mrs(data)                                       ((0x00000C00&(data))>>10)
#define TMDS_MSR1_get_ms(data)                                        ((0x00000300&(data))>>8)
#define TMDS_MSR1_get_ctc(data)                                       ((0x00000080&(data))>>7)
#define TMDS_MSR1_get_vmr(data)                                       (0x0000007F&(data))


#define TMDS_CRCC                                                     0x008
#define TMDS_CRCC_reg_addr                                            "0x98034008"
#define TMDS_CRCC_reg                                                 0x98034008
#define TMDS_CRCC_inst_addr                                           "0x0002"
#define TMDS_CRCC_inst                                                0x0002
#define set_TMDS_CRCC_reg(data)                                       (*((volatile unsigned int*)TMDS_CRCC_reg)=data)
#define get_TMDS_CRCC_reg                                             (*((volatile unsigned int*)TMDS_CRCC_reg))
#define TMDS_CRCC_crc_r_en_shift                                      (7)
#define TMDS_CRCC_crc_g_en_shift                                      (6)
#define TMDS_CRCC_crc_b_en_shift                                      (5)
#define TMDS_CRCC_crc_done_shift                                      (4)
#define TMDS_CRCC_crc_nonstable_shift                                 (3)
#define TMDS_CRCC_crcts_shift                                         (1)
#define TMDS_CRCC_crcc_shift                                          (0)
#define TMDS_CRCC_crc_r_en_mask                                       (0x00000080)
#define TMDS_CRCC_crc_g_en_mask                                       (0x00000040)
#define TMDS_CRCC_crc_b_en_mask                                       (0x00000020)
#define TMDS_CRCC_crc_done_mask                                       (0x00000010)
#define TMDS_CRCC_crc_nonstable_mask                                  (0x00000008)
#define TMDS_CRCC_crcts_mask                                          (0x00000006)
#define TMDS_CRCC_crcc_mask                                           (0x00000001)
#define TMDS_CRCC_crc_r_en(data)                                      (0x00000080&((data)<<7))
#define TMDS_CRCC_crc_g_en(data)                                      (0x00000040&((data)<<6))
#define TMDS_CRCC_crc_b_en(data)                                      (0x00000020&((data)<<5))
#define TMDS_CRCC_crc_done(data)                                      (0x00000010&((data)<<4))
#define TMDS_CRCC_crc_nonstable(data)                                 (0x00000008&((data)<<3))
#define TMDS_CRCC_crcts(data)                                         (0x00000006&((data)<<1))
#define TMDS_CRCC_crcc(data)                                          (0x00000001&(data))
#define TMDS_CRCC_get_crc_r_en(data)                                  ((0x00000080&(data))>>7)
#define TMDS_CRCC_get_crc_g_en(data)                                  ((0x00000040&(data))>>6)
#define TMDS_CRCC_get_crc_b_en(data)                                  ((0x00000020&(data))>>5)
#define TMDS_CRCC_get_crc_done(data)                                  ((0x00000010&(data))>>4)
#define TMDS_CRCC_get_crc_nonstable(data)                             ((0x00000008&(data))>>3)
#define TMDS_CRCC_get_crcts(data)                                     ((0x00000006&(data))>>1)
#define TMDS_CRCC_get_crcc(data)                                      (0x00000001&(data))


#define TMDS_CRCO0                                                    0x00c
#define TMDS_CRCO0_reg_addr                                           "0x9803400c"
#define TMDS_CRCO0_reg                                                0x9803400c
#define TMDS_CRCO0_inst_addr                                          "0x0003"
#define TMDS_CRCO0_inst                                               0x0003
#define set_TMDS_CRCO0_reg(data)                                      (*((volatile unsigned int*)TMDS_CRCO0_reg)=data)
#define get_TMDS_CRCO0_reg                                            (*((volatile unsigned int*)TMDS_CRCO0_reg))
#define TMDS_CRCO0_crcob2_3_shift                                     (16)
#define TMDS_CRCO0_crcob2_2_shift                                     (8)
#define TMDS_CRCO0_crcob2_1_shift                                     (0)
#define TMDS_CRCO0_crcob2_3_mask                                      (0x00FF0000)
#define TMDS_CRCO0_crcob2_2_mask                                      (0x0000FF00)
#define TMDS_CRCO0_crcob2_1_mask                                      (0x000000FF)
#define TMDS_CRCO0_crcob2_3(data)                                     (0x00FF0000&((data)<<16))
#define TMDS_CRCO0_crcob2_2(data)                                     (0x0000FF00&((data)<<8))
#define TMDS_CRCO0_crcob2_1(data)                                     (0x000000FF&(data))
#define TMDS_CRCO0_get_crcob2_3(data)                                 ((0x00FF0000&(data))>>16)
#define TMDS_CRCO0_get_crcob2_2(data)                                 ((0x0000FF00&(data))>>8)
#define TMDS_CRCO0_get_crcob2_1(data)                                 (0x000000FF&(data))


#define TMDS_CRCO1                                                    0x010
#define TMDS_CRCO1_reg_addr                                           "0x98034010"
#define TMDS_CRCO1_reg                                                0x98034010
#define TMDS_CRCO1_inst_addr                                          "0x0004"
#define TMDS_CRCO1_inst                                               0x0004
#define set_TMDS_CRCO1_reg(data)                                      (*((volatile unsigned int*)TMDS_CRCO1_reg)=data)
#define get_TMDS_CRCO1_reg                                            (*((volatile unsigned int*)TMDS_CRCO1_reg))
#define TMDS_CRCO1_crcob2_6_shift                                     (16)
#define TMDS_CRCO1_crcob2_5_shift                                     (8)
#define TMDS_CRCO1_crcob2_4_shift                                     (0)
#define TMDS_CRCO1_crcob2_6_mask                                      (0x00FF0000)
#define TMDS_CRCO1_crcob2_5_mask                                      (0x0000FF00)
#define TMDS_CRCO1_crcob2_4_mask                                      (0x000000FF)
#define TMDS_CRCO1_crcob2_6(data)                                     (0x00FF0000&((data)<<16))
#define TMDS_CRCO1_crcob2_5(data)                                     (0x0000FF00&((data)<<8))
#define TMDS_CRCO1_crcob2_4(data)                                     (0x000000FF&(data))
#define TMDS_CRCO1_get_crcob2_6(data)                                 ((0x00FF0000&(data))>>16)
#define TMDS_CRCO1_get_crcob2_5(data)                                 ((0x0000FF00&(data))>>8)
#define TMDS_CRCO1_get_crcob2_4(data)                                 (0x000000FF&(data))


#define TMDS_CTRL                                                     0x014
#define TMDS_CTRL_reg_addr                                            "0x98034014"
#define TMDS_CTRL_reg                                                 0x98034014
#define TMDS_CTRL_inst_addr                                           "0x0005"
#define TMDS_CTRL_inst                                                0x0005
#define set_TMDS_CTRL_reg(data)                                       (*((volatile unsigned int*)TMDS_CTRL_reg)=data)
#define get_TMDS_CTRL_reg                                             (*((volatile unsigned int*)TMDS_CTRL_reg))
#define TMDS_CTRL_bcd_shift                                           (7)
#define TMDS_CTRL_gcd_shift                                           (6)
#define TMDS_CTRL_rcd_shift                                           (5)
#define TMDS_CTRL_ho_shift                                            (4)
#define TMDS_CTRL_yo_shift                                            (3)
#define TMDS_CTRL_dummy_2_0_shift                                     (0)
#define TMDS_CTRL_bcd_mask                                            (0x00000080)
#define TMDS_CTRL_gcd_mask                                            (0x00000040)
#define TMDS_CTRL_rcd_mask                                            (0x00000020)
#define TMDS_CTRL_ho_mask                                             (0x00000010)
#define TMDS_CTRL_yo_mask                                             (0x00000008)
#define TMDS_CTRL_dummy_2_0_mask                                      (0x00000007)
#define TMDS_CTRL_bcd(data)                                           (0x00000080&((data)<<7))
#define TMDS_CTRL_gcd(data)                                           (0x00000040&((data)<<6))
#define TMDS_CTRL_rcd(data)                                           (0x00000020&((data)<<5))
#define TMDS_CTRL_ho(data)                                            (0x00000010&((data)<<4))
#define TMDS_CTRL_yo(data)                                            (0x00000008&((data)<<3))
#define TMDS_CTRL_dummy_2_0(data)                                     (0x00000007&(data))
#define TMDS_CTRL_get_bcd(data)                                       ((0x00000080&(data))>>7)
#define TMDS_CTRL_get_gcd(data)                                       ((0x00000040&(data))>>6)
#define TMDS_CTRL_get_rcd(data)                                       ((0x00000020&(data))>>5)
#define TMDS_CTRL_get_ho(data)                                        ((0x00000010&(data))>>4)
#define TMDS_CTRL_get_yo(data)                                        ((0x00000008&(data))>>3)
#define TMDS_CTRL_get_dummy_2_0(data)                                 (0x00000007&(data))


#define TMDS_OUTCTL                                                   0x018
#define TMDS_OUTCTL_reg_addr                                          "0x98034018"
#define TMDS_OUTCTL_reg                                               0x98034018
#define TMDS_OUTCTL_inst_addr                                         "0x0006"
#define TMDS_OUTCTL_inst                                              0x0006
#define set_TMDS_OUTCTL_reg(data)                                     (*((volatile unsigned int*)TMDS_OUTCTL_reg)=data)
#define get_TMDS_OUTCTL_reg                                           (*((volatile unsigned int*)TMDS_OUTCTL_reg))
#define TMDS_OUTCTL_trcoe_r_shift                                     (13)
#define TMDS_OUTCTL_tgcoe_r_shift                                     (12)
#define TMDS_OUTCTL_tbcoe_r_shift                                     (11)
#define TMDS_OUTCTL_ocke_r_shift                                      (10)
#define TMDS_OUTCTL_aoe_shift                                         (9)
#define TMDS_OUTCTL_trcoe_shift                                       (8)
#define TMDS_OUTCTL_tgcoe_shift                                       (7)
#define TMDS_OUTCTL_tbcoe_shift                                       (6)
#define TMDS_OUTCTL_ocke_shift                                        (5)
#define TMDS_OUTCTL_ockie_shift                                       (4)
#define TMDS_OUTCTL_dummy_3_shift                                     (3)
#define TMDS_OUTCTL_dummy_2_shift                                     (2)
#define TMDS_OUTCTL_dummy_1_shift                                     (1)
#define TMDS_OUTCTL_dummy_0_shift                                     (0)
#define TMDS_OUTCTL_trcoe_r_mask                                      (0x00002000)
#define TMDS_OUTCTL_tgcoe_r_mask                                      (0x00001000)
#define TMDS_OUTCTL_tbcoe_r_mask                                      (0x00000800)
#define TMDS_OUTCTL_ocke_r_mask                                       (0x00000400)
#define TMDS_OUTCTL_aoe_mask                                          (0x00000200)
#define TMDS_OUTCTL_trcoe_mask                                        (0x00000100)
#define TMDS_OUTCTL_tgcoe_mask                                        (0x00000080)
#define TMDS_OUTCTL_tbcoe_mask                                        (0x00000040)
#define TMDS_OUTCTL_ocke_mask                                         (0x00000020)
#define TMDS_OUTCTL_ockie_mask                                        (0x00000010)
#define TMDS_OUTCTL_dummy_3_mask                                      (0x00000008)
#define TMDS_OUTCTL_dummy_2_mask                                      (0x00000004)
#define TMDS_OUTCTL_dummy_1_mask                                      (0x00000002)
#define TMDS_OUTCTL_dummy_0_mask                                      (0x00000001)
#define TMDS_OUTCTL_trcoe_r(data)                                     (0x00002000&((data)<<13))
#define TMDS_OUTCTL_tgcoe_r(data)                                     (0x00001000&((data)<<12))
#define TMDS_OUTCTL_tbcoe_r(data)                                     (0x00000800&((data)<<11))
#define TMDS_OUTCTL_ocke_r(data)                                      (0x00000400&((data)<<10))
#define TMDS_OUTCTL_aoe(data)                                         (0x00000200&((data)<<9))
#define TMDS_OUTCTL_trcoe(data)                                       (0x00000100&((data)<<8))
#define TMDS_OUTCTL_tgcoe(data)                                       (0x00000080&((data)<<7))
#define TMDS_OUTCTL_tbcoe(data)                                       (0x00000040&((data)<<6))
#define TMDS_OUTCTL_ocke(data)                                        (0x00000020&((data)<<5))
#define TMDS_OUTCTL_ockie(data)                                       (0x00000010&((data)<<4))
#define TMDS_OUTCTL_dummy_3(data)                                     (0x00000008&((data)<<3))
#define TMDS_OUTCTL_dummy_2(data)                                     (0x00000004&((data)<<2))
#define TMDS_OUTCTL_dummy_1(data)                                     (0x00000002&((data)<<1))
#define TMDS_OUTCTL_dummy_0(data)                                     (0x00000001&(data))
#define TMDS_OUTCTL_get_trcoe_r(data)                                 ((0x00002000&(data))>>13)
#define TMDS_OUTCTL_get_tgcoe_r(data)                                 ((0x00001000&(data))>>12)
#define TMDS_OUTCTL_get_tbcoe_r(data)                                 ((0x00000800&(data))>>11)
#define TMDS_OUTCTL_get_ocke_r(data)                                  ((0x00000400&(data))>>10)
#define TMDS_OUTCTL_get_aoe(data)                                     ((0x00000200&(data))>>9)
#define TMDS_OUTCTL_get_trcoe(data)                                   ((0x00000100&(data))>>8)
#define TMDS_OUTCTL_get_tgcoe(data)                                   ((0x00000080&(data))>>7)
#define TMDS_OUTCTL_get_tbcoe(data)                                   ((0x00000040&(data))>>6)
#define TMDS_OUTCTL_get_ocke(data)                                    ((0x00000020&(data))>>5)
#define TMDS_OUTCTL_get_ockie(data)                                   ((0x00000010&(data))>>4)
#define TMDS_OUTCTL_get_dummy_3(data)                                 ((0x00000008&(data))>>3)
#define TMDS_OUTCTL_get_dummy_2(data)                                 ((0x00000004&(data))>>2)
#define TMDS_OUTCTL_get_dummy_1(data)                                 ((0x00000002&(data))>>1)
#define TMDS_OUTCTL_get_dummy_0(data)                                 (0x00000001&(data))


#define TMDS_PWDCTL                                                   0x01c
#define TMDS_PWDCTL_reg_addr                                          "0x9803401c"
#define TMDS_PWDCTL_reg                                               0x9803401c
#define TMDS_PWDCTL_inst_addr                                         "0x0007"
#define TMDS_PWDCTL_inst                                              0x0007
#define set_TMDS_PWDCTL_reg(data)                                     (*((volatile unsigned int*)TMDS_PWDCTL_reg)=data)
#define get_TMDS_PWDCTL_reg                                           (*((volatile unsigned int*)TMDS_PWDCTL_reg))
#define TMDS_PWDCTL_ecc_r_shift                                       (31)
#define TMDS_PWDCTL_erip_r_shift                                      (30)
#define TMDS_PWDCTL_egip_r_shift                                      (29)
#define TMDS_PWDCTL_ebip_r_shift                                      (28)
#define TMDS_PWDCTL_dummy_27_10_shift                                 (10)
#define TMDS_PWDCTL_video_preamble_off_en_shift                       (9)
#define TMDS_PWDCTL_hs_width_sel_shift                                (8)
#define TMDS_PWDCTL_deo_shift                                         (7)
#define TMDS_PWDCTL_brcw_shift                                        (6)
#define TMDS_PWDCTL_pnsw_shift                                        (5)
#define TMDS_PWDCTL_iccaf_shift                                       (4)
#define TMDS_PWDCTL_ecc_shift                                         (3)
#define TMDS_PWDCTL_erip_shift                                        (2)
#define TMDS_PWDCTL_egip_shift                                        (1)
#define TMDS_PWDCTL_ebip_shift                                        (0)
#define TMDS_PWDCTL_ecc_r_mask                                        (0x80000000)
#define TMDS_PWDCTL_erip_r_mask                                       (0x40000000)
#define TMDS_PWDCTL_egip_r_mask                                       (0x20000000)
#define TMDS_PWDCTL_ebip_r_mask                                       (0x10000000)
#define TMDS_PWDCTL_dummy_27_10_mask                                  (0x0FFFFC00)
#define TMDS_PWDCTL_video_preamble_off_en_mask                        (0x00000200)
#define TMDS_PWDCTL_hs_width_sel_mask                                 (0x00000100)
#define TMDS_PWDCTL_deo_mask                                          (0x00000080)
#define TMDS_PWDCTL_brcw_mask                                         (0x00000040)
#define TMDS_PWDCTL_pnsw_mask                                         (0x00000020)
#define TMDS_PWDCTL_iccaf_mask                                        (0x00000010)
#define TMDS_PWDCTL_ecc_mask                                          (0x00000008)
#define TMDS_PWDCTL_erip_mask                                         (0x00000004)
#define TMDS_PWDCTL_egip_mask                                         (0x00000002)
#define TMDS_PWDCTL_ebip_mask                                         (0x00000001)
#define TMDS_PWDCTL_ecc_r(data)                                       (0x80000000&((data)<<31))
#define TMDS_PWDCTL_erip_r(data)                                      (0x40000000&((data)<<30))
#define TMDS_PWDCTL_egip_r(data)                                      (0x20000000&((data)<<29))
#define TMDS_PWDCTL_ebip_r(data)                                      (0x10000000&((data)<<28))
#define TMDS_PWDCTL_dummy_27_10(data)                                 (0x0FFFFC00&((data)<<10))
#define TMDS_PWDCTL_video_preamble_off_en(data)                       (0x00000200&((data)<<9))
#define TMDS_PWDCTL_hs_width_sel(data)                                (0x00000100&((data)<<8))
#define TMDS_PWDCTL_deo(data)                                         (0x00000080&((data)<<7))
#define TMDS_PWDCTL_brcw(data)                                        (0x00000040&((data)<<6))
#define TMDS_PWDCTL_pnsw(data)                                        (0x00000020&((data)<<5))
#define TMDS_PWDCTL_iccaf(data)                                       (0x00000010&((data)<<4))
#define TMDS_PWDCTL_ecc(data)                                         (0x00000008&((data)<<3))
#define TMDS_PWDCTL_erip(data)                                        (0x00000004&((data)<<2))
#define TMDS_PWDCTL_egip(data)                                        (0x00000002&((data)<<1))
#define TMDS_PWDCTL_ebip(data)                                        (0x00000001&(data))
#define TMDS_PWDCTL_get_ecc_r(data)                                   ((0x80000000&(data))>>31)
#define TMDS_PWDCTL_get_erip_r(data)                                  ((0x40000000&(data))>>30)
#define TMDS_PWDCTL_get_egip_r(data)                                  ((0x20000000&(data))>>29)
#define TMDS_PWDCTL_get_ebip_r(data)                                  ((0x10000000&(data))>>28)
#define TMDS_PWDCTL_get_dummy_27_10(data)                             ((0x0FFFFC00&(data))>>10)
#define TMDS_PWDCTL_get_video_preamble_off_en(data)                   ((0x00000200&(data))>>9)
#define TMDS_PWDCTL_get_hs_width_sel(data)                            ((0x00000100&(data))>>8)
#define TMDS_PWDCTL_get_deo(data)                                     ((0x00000080&(data))>>7)
#define TMDS_PWDCTL_get_brcw(data)                                    ((0x00000040&(data))>>6)
#define TMDS_PWDCTL_get_pnsw(data)                                    ((0x00000020&(data))>>5)
#define TMDS_PWDCTL_get_iccaf(data)                                   ((0x00000010&(data))>>4)
#define TMDS_PWDCTL_get_ecc(data)                                     ((0x00000008&(data))>>3)
#define TMDS_PWDCTL_get_erip(data)                                    ((0x00000004&(data))>>2)
#define TMDS_PWDCTL_get_egip(data)                                    ((0x00000002&(data))>>1)
#define TMDS_PWDCTL_get_ebip(data)                                    (0x00000001&(data))


#define TMDS_Z0CC                                                     0x020
#define TMDS_Z0CC_reg_addr                                            "0x98034020"
#define TMDS_Z0CC_reg                                                 0x98034020
#define TMDS_Z0CC_inst_addr                                           "0x0008"
#define TMDS_Z0CC_inst                                                0x0008
#define set_TMDS_Z0CC_reg(data)                                       (*((volatile unsigned int*)TMDS_Z0CC_reg)=data)
#define get_TMDS_Z0CC_reg                                             (*((volatile unsigned int*)TMDS_Z0CC_reg))
#define TMDS_Z0CC_hde_shift                                           (0)
#define TMDS_Z0CC_hde_mask                                            (0x00000001)
#define TMDS_Z0CC_hde(data)                                           (0x00000001&(data))
#define TMDS_Z0CC_get_hde(data)                                       (0x00000001&(data))


#define TMDS_CPS                                                      0x024
#define TMDS_CPS_reg_addr                                             "0x98034024"
#define TMDS_CPS_reg                                                  0x98034024
#define TMDS_CPS_inst_addr                                            "0x0009"
#define TMDS_CPS_inst                                                 0x0009
#define set_TMDS_CPS_reg(data)                                        (*((volatile unsigned int*)TMDS_CPS_reg)=data)
#define get_TMDS_CPS_reg                                              (*((volatile unsigned int*)TMDS_CPS_reg))
#define TMDS_CPS_pll_div2_en_shift                                    (9)
#define TMDS_CPS_no_clk_in_shift                                      (8)
#define TMDS_CPS_clkv_meas_sel_shift                                  (6)
#define TMDS_CPS_de_inv_disable_shift                                 (5)
#define TMDS_CPS_de_err_pulse_en_shift                                (4)
#define TMDS_CPS_clr_infoframe_dvi_shift                              (3)
#define TMDS_CPS_auto_dvi2hdmi_shift                                  (2)
#define TMDS_CPS_dummy_1_0_shift                                      (0)
#define TMDS_CPS_pll_div2_en_mask                                     (0x00000200)
#define TMDS_CPS_no_clk_in_mask                                       (0x00000100)
#define TMDS_CPS_clkv_meas_sel_mask                                   (0x000000C0)
#define TMDS_CPS_de_inv_disable_mask                                  (0x00000020)
#define TMDS_CPS_de_err_pulse_en_mask                                 (0x00000010)
#define TMDS_CPS_clr_infoframe_dvi_mask                               (0x00000008)
#define TMDS_CPS_auto_dvi2hdmi_mask                                   (0x00000004)
#define TMDS_CPS_dummy_1_0_mask                                       (0x00000003)
#define TMDS_CPS_pll_div2_en(data)                                    (0x00000200&((data)<<9))
#define TMDS_CPS_no_clk_in(data)                                      (0x00000100&((data)<<8))
#define TMDS_CPS_clkv_meas_sel(data)                                  (0x000000C0&((data)<<6))
#define TMDS_CPS_de_inv_disable(data)                                 (0x00000020&((data)<<5))
#define TMDS_CPS_de_err_pulse_en(data)                                (0x00000010&((data)<<4))
#define TMDS_CPS_clr_infoframe_dvi(data)                              (0x00000008&((data)<<3))
#define TMDS_CPS_auto_dvi2hdmi(data)                                  (0x00000004&((data)<<2))
#define TMDS_CPS_dummy_1_0(data)                                      (0x00000003&(data))
#define TMDS_CPS_get_pll_div2_en(data)                                ((0x00000200&(data))>>9)
#define TMDS_CPS_get_no_clk_in(data)                                  ((0x00000100&(data))>>8)
#define TMDS_CPS_get_clkv_meas_sel(data)                              ((0x000000C0&(data))>>6)
#define TMDS_CPS_get_de_inv_disable(data)                             ((0x00000020&(data))>>5)
#define TMDS_CPS_get_de_err_pulse_en(data)                            ((0x00000010&(data))>>4)
#define TMDS_CPS_get_clr_infoframe_dvi(data)                          ((0x00000008&(data))>>3)
#define TMDS_CPS_get_auto_dvi2hdmi(data)                              ((0x00000004&(data))>>2)
#define TMDS_CPS_get_dummy_1_0(data)                                  (0x00000003&(data))


#define TMDS_UDC                                                      0x028
#define TMDS_UDC_reg_addr                                             "0x98034028"
#define TMDS_UDC_reg                                                  0x98034028
#define TMDS_UDC_inst_addr                                            "0x000A"
#define TMDS_UDC_inst                                                 0x000A
#define set_TMDS_UDC_reg(data)                                        (*((volatile unsigned int*)TMDS_UDC_reg)=data)
#define get_TMDS_UDC_reg                                              (*((volatile unsigned int*)TMDS_UDC_reg))
#define TMDS_UDC_debug_sel_shift                                      (4)
#define TMDS_UDC_dummy_3_shift                                        (3)
#define TMDS_UDC_cptest_shift                                         (2)
#define TMDS_UDC_hmtm_shift                                           (0)
#define TMDS_UDC_debug_sel_mask                                       (0x000003F0)
#define TMDS_UDC_dummy_3_mask                                         (0x00000008)
#define TMDS_UDC_cptest_mask                                          (0x00000004)
#define TMDS_UDC_hmtm_mask                                            (0x00000003)
#define TMDS_UDC_debug_sel(data)                                      (0x000003F0&((data)<<4))
#define TMDS_UDC_dummy_3(data)                                        (0x00000008&((data)<<3))
#define TMDS_UDC_cptest(data)                                         (0x00000004&((data)<<2))
#define TMDS_UDC_hmtm(data)                                           (0x00000003&(data))
#define TMDS_UDC_get_debug_sel(data)                                  ((0x000003F0&(data))>>4)
#define TMDS_UDC_get_dummy_3(data)                                    ((0x00000008&(data))>>3)
#define TMDS_UDC_get_cptest(data)                                     ((0x00000004&(data))>>2)
#define TMDS_UDC_get_hmtm(data)                                       (0x00000003&(data))


#define TMDS_ERRC                                                     0x02c
#define TMDS_ERRC_reg_addr                                            "0x9803402c"
#define TMDS_ERRC_reg                                                 0x9803402c
#define TMDS_ERRC_inst_addr                                           "0x000B"
#define TMDS_ERRC_inst                                                0x000B
#define set_TMDS_ERRC_reg(data)                                       (*((volatile unsigned int*)TMDS_ERRC_reg)=data)
#define get_TMDS_ERRC_reg                                             (*((volatile unsigned int*)TMDS_ERRC_reg))
#define TMDS_ERRC_nl_shift                                            (0)
#define TMDS_ERRC_nl_mask                                             (0x00000007)
#define TMDS_ERRC_nl(data)                                            (0x00000007&(data))
#define TMDS_ERRC_get_nl(data)                                        (0x00000007&(data))


#define TMDS_OUT_CTRL                                                 0x030
#define TMDS_OUT_CTRL_reg_addr                                        "0x98034030"
#define TMDS_OUT_CTRL_reg                                             0x98034030
#define TMDS_OUT_CTRL_inst_addr                                       "0x000C"
#define TMDS_OUT_CTRL_inst                                            0x000C
#define set_TMDS_OUT_CTRL_reg(data)                                   (*((volatile unsigned int*)TMDS_OUT_CTRL_reg)=data)
#define get_TMDS_OUT_CTRL_reg                                         (*((volatile unsigned int*)TMDS_OUT_CTRL_reg))
#define TMDS_OUT_CTRL_tmds_bypass_shift                               (7)
#define TMDS_OUT_CTRL_dummy_6_0_shift                                 (0)
#define TMDS_OUT_CTRL_tmds_bypass_mask                                (0x00000080)
#define TMDS_OUT_CTRL_dummy_6_0_mask                                  (0x0000007F)
#define TMDS_OUT_CTRL_tmds_bypass(data)                               (0x00000080&((data)<<7))
#define TMDS_OUT_CTRL_dummy_6_0(data)                                 (0x0000007F&(data))
#define TMDS_OUT_CTRL_get_tmds_bypass(data)                           ((0x00000080&(data))>>7)
#define TMDS_OUT_CTRL_get_dummy_6_0(data)                             (0x0000007F&(data))


#define TMDS_ROUT                                                     0x034
#define TMDS_ROUT_reg_addr                                            "0x98034034"
#define TMDS_ROUT_reg                                                 0x98034034
#define TMDS_ROUT_inst_addr                                           "0x000D"
#define TMDS_ROUT_inst                                                0x000D
#define set_TMDS_ROUT_reg(data)                                       (*((volatile unsigned int*)TMDS_ROUT_reg)=data)
#define get_TMDS_ROUT_reg                                             (*((volatile unsigned int*)TMDS_ROUT_reg))
#define TMDS_ROUT_tmds_rout_h_shift                                   (8)
#define TMDS_ROUT_tmds_rout_l_shift                                   (0)
#define TMDS_ROUT_tmds_rout_h_mask                                    (0x0000FF00)
#define TMDS_ROUT_tmds_rout_l_mask                                    (0x000000FF)
#define TMDS_ROUT_tmds_rout_h(data)                                   (0x0000FF00&((data)<<8))
#define TMDS_ROUT_tmds_rout_l(data)                                   (0x000000FF&(data))
#define TMDS_ROUT_get_tmds_rout_h(data)                               ((0x0000FF00&(data))>>8)
#define TMDS_ROUT_get_tmds_rout_l(data)                               (0x000000FF&(data))


#define TMDS_GOUT                                                     0x038
#define TMDS_GOUT_reg_addr                                            "0x98034038"
#define TMDS_GOUT_reg                                                 0x98034038
#define TMDS_GOUT_inst_addr                                           "0x000E"
#define TMDS_GOUT_inst                                                0x000E
#define set_TMDS_GOUT_reg(data)                                       (*((volatile unsigned int*)TMDS_GOUT_reg)=data)
#define get_TMDS_GOUT_reg                                             (*((volatile unsigned int*)TMDS_GOUT_reg))
#define TMDS_GOUT_tmds_gout_h_shift                                   (8)
#define TMDS_GOUT_tmds_gout_l_shift                                   (0)
#define TMDS_GOUT_tmds_gout_h_mask                                    (0x0000FF00)
#define TMDS_GOUT_tmds_gout_l_mask                                    (0x000000FF)
#define TMDS_GOUT_tmds_gout_h(data)                                   (0x0000FF00&((data)<<8))
#define TMDS_GOUT_tmds_gout_l(data)                                   (0x000000FF&(data))
#define TMDS_GOUT_get_tmds_gout_h(data)                               ((0x0000FF00&(data))>>8)
#define TMDS_GOUT_get_tmds_gout_l(data)                               (0x000000FF&(data))


#define TMDS_BOUT                                                     0x03c
#define TMDS_BOUT_reg_addr                                            "0x9803403c"
#define TMDS_BOUT_reg                                                 0x9803403c
#define TMDS_BOUT_inst_addr                                           "0x000F"
#define TMDS_BOUT_inst                                                0x000F
#define set_TMDS_BOUT_reg(data)                                       (*((volatile unsigned int*)TMDS_BOUT_reg)=data)
#define get_TMDS_BOUT_reg                                             (*((volatile unsigned int*)TMDS_BOUT_reg))
#define TMDS_BOUT_tmds_bout_h_shift                                   (8)
#define TMDS_BOUT_tmds_bout_l_shift                                   (0)
#define TMDS_BOUT_tmds_bout_h_mask                                    (0x0000FF00)
#define TMDS_BOUT_tmds_bout_l_mask                                    (0x000000FF)
#define TMDS_BOUT_tmds_bout_h(data)                                   (0x0000FF00&((data)<<8))
#define TMDS_BOUT_tmds_bout_l(data)                                   (0x000000FF&(data))
#define TMDS_BOUT_get_tmds_bout_h(data)                               ((0x0000FF00&(data))>>8)
#define TMDS_BOUT_get_tmds_bout_l(data)                               (0x000000FF&(data))


#define TMDS_DPC0                                                     0x040
#define TMDS_DPC0_reg_addr                                            "0x98034040"
#define TMDS_DPC0_reg                                                 0x98034040
#define TMDS_DPC0_inst_addr                                           "0x0010"
#define TMDS_DPC0_inst                                                0x0010
#define set_TMDS_DPC0_reg(data)                                       (*((volatile unsigned int*)TMDS_DPC0_reg)=data)
#define get_TMDS_DPC0_reg                                             (*((volatile unsigned int*)TMDS_DPC0_reg))
#define TMDS_DPC0_dpc_pp_valid_shift                                  (9)
#define TMDS_DPC0_dpc_default_ph_shift                                (8)
#define TMDS_DPC0_dpc_pp_shift                                        (4)
#define TMDS_DPC0_dpc_cd_shift                                        (0)
#define TMDS_DPC0_dpc_pp_valid_mask                                   (0x00000200)
#define TMDS_DPC0_dpc_default_ph_mask                                 (0x00000100)
#define TMDS_DPC0_dpc_pp_mask                                         (0x000000F0)
#define TMDS_DPC0_dpc_cd_mask                                         (0x0000000F)
#define TMDS_DPC0_dpc_pp_valid(data)                                  (0x00000200&((data)<<9))
#define TMDS_DPC0_dpc_default_ph(data)                                (0x00000100&((data)<<8))
#define TMDS_DPC0_dpc_pp(data)                                        (0x000000F0&((data)<<4))
#define TMDS_DPC0_dpc_cd(data)                                        (0x0000000F&(data))
#define TMDS_DPC0_get_dpc_pp_valid(data)                              ((0x00000200&(data))>>9)
#define TMDS_DPC0_get_dpc_default_ph(data)                            ((0x00000100&(data))>>8)
#define TMDS_DPC0_get_dpc_pp(data)                                    ((0x000000F0&(data))>>4)
#define TMDS_DPC0_get_dpc_cd(data)                                    (0x0000000F&(data))


#define TMDS_DPC1                                                     0x044
#define TMDS_DPC1_reg_addr                                            "0x98034044"
#define TMDS_DPC1_reg                                                 0x98034044
#define TMDS_DPC1_inst_addr                                           "0x0011"
#define TMDS_DPC1_inst                                                0x0011
#define set_TMDS_DPC1_reg(data)                                       (*((volatile unsigned int*)TMDS_DPC1_reg)=data)
#define get_TMDS_DPC1_reg                                             (*((volatile unsigned int*)TMDS_DPC1_reg))
#define TMDS_DPC1_dpc_cd_chg_flag_shift                               (18)
#define TMDS_DPC1_dpc_cd_chg_wd_en_shift                              (17)
#define TMDS_DPC1_dpc_cd_chg_int_en_shift                             (16)
#define TMDS_DPC1_dummy_15_11_shift                                   (11)
#define TMDS_DPC1_dpc_auto_shift                                      (10)
#define TMDS_DPC1_dpc_pp_valid_fw_shift                               (9)
#define TMDS_DPC1_dpc_default_ph_fw_shift                             (8)
#define TMDS_DPC1_dpc_pp_fw_shift                                     (4)
#define TMDS_DPC1_dpc_cd_fw_shift                                     (0)
#define TMDS_DPC1_dpc_cd_chg_flag_mask                                (0x00040000)
#define TMDS_DPC1_dpc_cd_chg_wd_en_mask                               (0x00020000)
#define TMDS_DPC1_dpc_cd_chg_int_en_mask                              (0x00010000)
#define TMDS_DPC1_dummy_15_11_mask                                    (0x0000F800)
#define TMDS_DPC1_dpc_auto_mask                                       (0x00000400)
#define TMDS_DPC1_dpc_pp_valid_fw_mask                                (0x00000200)
#define TMDS_DPC1_dpc_default_ph_fw_mask                              (0x00000100)
#define TMDS_DPC1_dpc_pp_fw_mask                                      (0x000000F0)
#define TMDS_DPC1_dpc_cd_fw_mask                                      (0x0000000F)
#define TMDS_DPC1_dpc_cd_chg_flag(data)                               (0x00040000&((data)<<18))
#define TMDS_DPC1_dpc_cd_chg_wd_en(data)                              (0x00020000&((data)<<17))
#define TMDS_DPC1_dpc_cd_chg_int_en(data)                             (0x00010000&((data)<<16))
#define TMDS_DPC1_dummy_15_11(data)                                   (0x0000F800&((data)<<11))
#define TMDS_DPC1_dpc_auto(data)                                      (0x00000400&((data)<<10))
#define TMDS_DPC1_dpc_pp_valid_fw(data)                               (0x00000200&((data)<<9))
#define TMDS_DPC1_dpc_default_ph_fw(data)                             (0x00000100&((data)<<8))
#define TMDS_DPC1_dpc_pp_fw(data)                                     (0x000000F0&((data)<<4))
#define TMDS_DPC1_dpc_cd_fw(data)                                     (0x0000000F&(data))
#define TMDS_DPC1_get_dpc_cd_chg_flag(data)                           ((0x00040000&(data))>>18)
#define TMDS_DPC1_get_dpc_cd_chg_wd_en(data)                          ((0x00020000&(data))>>17)
#define TMDS_DPC1_get_dpc_cd_chg_int_en(data)                         ((0x00010000&(data))>>16)
#define TMDS_DPC1_get_dummy_15_11(data)                               ((0x0000F800&(data))>>11)
#define TMDS_DPC1_get_dpc_auto(data)                                  ((0x00000400&(data))>>10)
#define TMDS_DPC1_get_dpc_pp_valid_fw(data)                           ((0x00000200&(data))>>9)
#define TMDS_DPC1_get_dpc_default_ph_fw(data)                         ((0x00000100&(data))>>8)
#define TMDS_DPC1_get_dpc_pp_fw(data)                                 ((0x000000F0&(data))>>4)
#define TMDS_DPC1_get_dpc_cd_fw(data)                                 (0x0000000F&(data))


#define TMDS_DPC_SET0                                                 0x048
#define TMDS_DPC_SET0_reg_addr                                        "0x98034048"
#define TMDS_DPC_SET0_reg                                             0x98034048
#define TMDS_DPC_SET0_inst_addr                                       "0x0012"
#define TMDS_DPC_SET0_inst                                            0x0012
#define set_TMDS_DPC_SET0_reg(data)                                   (*((volatile unsigned int*)TMDS_DPC_SET0_reg)=data)
#define get_TMDS_DPC_SET0_reg                                         (*((volatile unsigned int*)TMDS_DPC_SET0_reg))
#define TMDS_DPC_SET0_dpc_bypass_dis_shift                            (8)
#define TMDS_DPC_SET0_dpc_en_shift                                    (7)
#define TMDS_DPC_SET0_phase_errcnt_in_shift                           (4)
#define TMDS_DPC_SET0_phase_clrcnt_in_shift                           (1)
#define TMDS_DPC_SET0_phase_clr_sel_shift                             (0)
#define TMDS_DPC_SET0_dpc_bypass_dis_mask                             (0x00000100)
#define TMDS_DPC_SET0_dpc_en_mask                                     (0x00000080)
#define TMDS_DPC_SET0_phase_errcnt_in_mask                            (0x00000070)
#define TMDS_DPC_SET0_phase_clrcnt_in_mask                            (0x0000000E)
#define TMDS_DPC_SET0_phase_clr_sel_mask                              (0x00000001)
#define TMDS_DPC_SET0_dpc_bypass_dis(data)                            (0x00000100&((data)<<8))
#define TMDS_DPC_SET0_dpc_en(data)                                    (0x00000080&((data)<<7))
#define TMDS_DPC_SET0_phase_errcnt_in(data)                           (0x00000070&((data)<<4))
#define TMDS_DPC_SET0_phase_clrcnt_in(data)                           (0x0000000E&((data)<<1))
#define TMDS_DPC_SET0_phase_clr_sel(data)                             (0x00000001&(data))
#define TMDS_DPC_SET0_get_dpc_bypass_dis(data)                        ((0x00000100&(data))>>8)
#define TMDS_DPC_SET0_get_dpc_en(data)                                ((0x00000080&(data))>>7)
#define TMDS_DPC_SET0_get_phase_errcnt_in(data)                       ((0x00000070&(data))>>4)
#define TMDS_DPC_SET0_get_phase_clrcnt_in(data)                       ((0x0000000E&(data))>>1)
#define TMDS_DPC_SET0_get_phase_clr_sel(data)                         (0x00000001&(data))


#define TMDS_DPC_SET1                                                 0x04c
#define TMDS_DPC_SET1_reg_addr                                        "0x9803404c"
#define TMDS_DPC_SET1_reg                                             0x9803404c
#define TMDS_DPC_SET1_inst_addr                                       "0x0013"
#define TMDS_DPC_SET1_inst                                            0x0013
#define set_TMDS_DPC_SET1_reg(data)                                   (*((volatile unsigned int*)TMDS_DPC_SET1_reg)=data)
#define get_TMDS_DPC_SET1_reg                                         (*((volatile unsigned int*)TMDS_DPC_SET1_reg))
#define TMDS_DPC_SET1_set_full_noti_shift                             (4)
#define TMDS_DPC_SET1_set_empty_noti_shift                            (0)
#define TMDS_DPC_SET1_set_full_noti_mask                              (0x000000F0)
#define TMDS_DPC_SET1_set_empty_noti_mask                             (0x0000000F)
#define TMDS_DPC_SET1_set_full_noti(data)                             (0x000000F0&((data)<<4))
#define TMDS_DPC_SET1_set_empty_noti(data)                            (0x0000000F&(data))
#define TMDS_DPC_SET1_get_set_full_noti(data)                         ((0x000000F0&(data))>>4)
#define TMDS_DPC_SET1_get_set_empty_noti(data)                        (0x0000000F&(data))


#define TMDS_DPC_SET2                                                 0x050
#define TMDS_DPC_SET2_reg_addr                                        "0x98034050"
#define TMDS_DPC_SET2_reg                                             0x98034050
#define TMDS_DPC_SET2_inst_addr                                       "0x0014"
#define TMDS_DPC_SET2_inst                                            0x0014
#define set_TMDS_DPC_SET2_reg(data)                                   (*((volatile unsigned int*)TMDS_DPC_SET2_reg)=data)
#define get_TMDS_DPC_SET2_reg                                         (*((volatile unsigned int*)TMDS_DPC_SET2_reg))
#define TMDS_DPC_SET2_fifo_errcnt_in_shift                            (5)
#define TMDS_DPC_SET2_clr_phase_flag_shift                            (4)
#define TMDS_DPC_SET2_clr_fifo_flag_shift                             (3)
#define TMDS_DPC_SET2_dpc_phase_ok_shift                              (2)
#define TMDS_DPC_SET2_dpc_phase_err_flag_shift                        (1)
#define TMDS_DPC_SET2_dpc_fifo_err_flag_shift                         (0)
#define TMDS_DPC_SET2_fifo_errcnt_in_mask                             (0x000000E0)
#define TMDS_DPC_SET2_clr_phase_flag_mask                             (0x00000010)
#define TMDS_DPC_SET2_clr_fifo_flag_mask                              (0x00000008)
#define TMDS_DPC_SET2_dpc_phase_ok_mask                               (0x00000004)
#define TMDS_DPC_SET2_dpc_phase_err_flag_mask                         (0x00000002)
#define TMDS_DPC_SET2_dpc_fifo_err_flag_mask                          (0x00000001)
#define TMDS_DPC_SET2_fifo_errcnt_in(data)                            (0x000000E0&((data)<<5))
#define TMDS_DPC_SET2_clr_phase_flag(data)                            (0x00000010&((data)<<4))
#define TMDS_DPC_SET2_clr_fifo_flag(data)                             (0x00000008&((data)<<3))
#define TMDS_DPC_SET2_dpc_phase_ok(data)                              (0x00000004&((data)<<2))
#define TMDS_DPC_SET2_dpc_phase_err_flag(data)                        (0x00000002&((data)<<1))
#define TMDS_DPC_SET2_dpc_fifo_err_flag(data)                         (0x00000001&(data))
#define TMDS_DPC_SET2_get_fifo_errcnt_in(data)                        ((0x000000E0&(data))>>5)
#define TMDS_DPC_SET2_get_clr_phase_flag(data)                        ((0x00000010&(data))>>4)
#define TMDS_DPC_SET2_get_clr_fifo_flag(data)                         ((0x00000008&(data))>>3)
#define TMDS_DPC_SET2_get_dpc_phase_ok(data)                          ((0x00000004&(data))>>2)
#define TMDS_DPC_SET2_get_dpc_phase_err_flag(data)                    ((0x00000002&(data))>>1)
#define TMDS_DPC_SET2_get_dpc_fifo_err_flag(data)                     (0x00000001&(data))


#define TMDS_DPC_SET3                                                 0x054
#define TMDS_DPC_SET3_reg_addr                                        "0x98034054"
#define TMDS_DPC_SET3_reg                                             0x98034054
#define TMDS_DPC_SET3_inst_addr                                       "0x0015"
#define TMDS_DPC_SET3_inst                                            0x0015
#define set_TMDS_DPC_SET3_reg(data)                                   (*((volatile unsigned int*)TMDS_DPC_SET3_reg)=data)
#define get_TMDS_DPC_SET3_reg                                         (*((volatile unsigned int*)TMDS_DPC_SET3_reg))
#define TMDS_DPC_SET3_dpc_fifo_over_flag_shift                        (7)
#define TMDS_DPC_SET3_dpc_fifo_under_flag_shift                       (6)
#define TMDS_DPC_SET3_dpc_fifo_over_xflag_shift                       (5)
#define TMDS_DPC_SET3_dpc_fifo_under_xflag_shift                      (4)
#define TMDS_DPC_SET3_dpc_fifo_over_flag_mask                         (0x00000080)
#define TMDS_DPC_SET3_dpc_fifo_under_flag_mask                        (0x00000040)
#define TMDS_DPC_SET3_dpc_fifo_over_xflag_mask                        (0x00000020)
#define TMDS_DPC_SET3_dpc_fifo_under_xflag_mask                       (0x00000010)
#define TMDS_DPC_SET3_dpc_fifo_over_flag(data)                        (0x00000080&((data)<<7))
#define TMDS_DPC_SET3_dpc_fifo_under_flag(data)                       (0x00000040&((data)<<6))
#define TMDS_DPC_SET3_dpc_fifo_over_xflag(data)                       (0x00000020&((data)<<5))
#define TMDS_DPC_SET3_dpc_fifo_under_xflag(data)                      (0x00000010&((data)<<4))
#define TMDS_DPC_SET3_get_dpc_fifo_over_flag(data)                    ((0x00000080&(data))>>7)
#define TMDS_DPC_SET3_get_dpc_fifo_under_flag(data)                   ((0x00000040&(data))>>6)
#define TMDS_DPC_SET3_get_dpc_fifo_over_xflag(data)                   ((0x00000020&(data))>>5)
#define TMDS_DPC_SET3_get_dpc_fifo_under_xflag(data)                  ((0x00000010&(data))>>4)


#define TMDS_DET_CTL                                                  0x058
#define TMDS_DET_CTL_reg_addr                                         "0x98034058"
#define TMDS_DET_CTL_reg                                              0x98034058
#define TMDS_DET_CTL_inst_addr                                        "0x0016"
#define TMDS_DET_CTL_inst                                             0x0016
#define set_TMDS_DET_CTL_reg(data)                                    (*((volatile unsigned int*)TMDS_DET_CTL_reg)=data)
#define get_TMDS_DET_CTL_reg                                          (*((volatile unsigned int*)TMDS_DET_CTL_reg))
#define TMDS_DET_CTL_de_sel_shift                                     (28)
#define TMDS_DET_CTL_tran_err_thrd_shift                              (24)
#define TMDS_DET_CTL_neg_de_err_thrd_shift                            (20)
#define TMDS_DET_CTL_pos_de_err_thrd_shift                            (16)
#define TMDS_DET_CTL_dummy_15_shift                                   (15)
#define TMDS_DET_CTL_neg_de_lowbd_shift                               (8)
#define TMDS_DET_CTL_dummy_7_6_shift                                  (6)
#define TMDS_DET_CTL_pos_de_lowbd_shift                               (0)
#define TMDS_DET_CTL_de_sel_mask                                      (0x10000000)
#define TMDS_DET_CTL_tran_err_thrd_mask                               (0x0F000000)
#define TMDS_DET_CTL_neg_de_err_thrd_mask                             (0x00F00000)
#define TMDS_DET_CTL_pos_de_err_thrd_mask                             (0x000F0000)
#define TMDS_DET_CTL_dummy_15_mask                                    (0x00008000)
#define TMDS_DET_CTL_neg_de_lowbd_mask                                (0x00007F00)
#define TMDS_DET_CTL_dummy_7_6_mask                                   (0x000000C0)
#define TMDS_DET_CTL_pos_de_lowbd_mask                                (0x0000003F)
#define TMDS_DET_CTL_de_sel(data)                                     (0x10000000&((data)<<28))
#define TMDS_DET_CTL_tran_err_thrd(data)                              (0x0F000000&((data)<<24))
#define TMDS_DET_CTL_neg_de_err_thrd(data)                            (0x00F00000&((data)<<20))
#define TMDS_DET_CTL_pos_de_err_thrd(data)                            (0x000F0000&((data)<<16))
#define TMDS_DET_CTL_dummy_15(data)                                   (0x00008000&((data)<<15))
#define TMDS_DET_CTL_neg_de_lowbd(data)                               (0x00007F00&((data)<<8))
#define TMDS_DET_CTL_dummy_7_6(data)                                  (0x000000C0&((data)<<6))
#define TMDS_DET_CTL_pos_de_lowbd(data)                               (0x0000003F&(data))
#define TMDS_DET_CTL_get_de_sel(data)                                 ((0x10000000&(data))>>28)
#define TMDS_DET_CTL_get_tran_err_thrd(data)                          ((0x0F000000&(data))>>24)
#define TMDS_DET_CTL_get_neg_de_err_thrd(data)                        ((0x00F00000&(data))>>20)
#define TMDS_DET_CTL_get_pos_de_err_thrd(data)                        ((0x000F0000&(data))>>16)
#define TMDS_DET_CTL_get_dummy_15(data)                               ((0x00008000&(data))>>15)
#define TMDS_DET_CTL_get_neg_de_lowbd(data)                           ((0x00007F00&(data))>>8)
#define TMDS_DET_CTL_get_dummy_7_6(data)                              ((0x000000C0&(data))>>6)
#define TMDS_DET_CTL_get_pos_de_lowbd(data)                           (0x0000003F&(data))


#define TMDS_DET_STS                                                  0x05c
#define TMDS_DET_STS_reg_addr                                         "0x9803405c"
#define TMDS_DET_STS_reg                                              0x9803405c
#define TMDS_DET_STS_inst_addr                                        "0x0017"
#define TMDS_DET_STS_inst                                             0x0017
#define set_TMDS_DET_STS_reg(data)                                    (*((volatile unsigned int*)TMDS_DET_STS_reg)=data)
#define get_TMDS_DET_STS_reg                                          (*((volatile unsigned int*)TMDS_DET_STS_reg))
#define TMDS_DET_STS_red_tran_err_flag_shift                          (8)
#define TMDS_DET_STS_grn_tran_err_flag_shift                          (7)
#define TMDS_DET_STS_blu_tran_err_flag_shift                          (6)
#define TMDS_DET_STS_red_pos_de_err_flag_shift                        (5)
#define TMDS_DET_STS_grn_pos_de_err_flag_shift                        (4)
#define TMDS_DET_STS_blu_pos_de_err_flag_shift                        (3)
#define TMDS_DET_STS_red_neg_de_err_flag_shift                        (2)
#define TMDS_DET_STS_grn_neg_de_err_flag_shift                        (1)
#define TMDS_DET_STS_blu_neg_de_err_flag_shift                        (0)
#define TMDS_DET_STS_red_tran_err_flag_mask                           (0x00000100)
#define TMDS_DET_STS_grn_tran_err_flag_mask                           (0x00000080)
#define TMDS_DET_STS_blu_tran_err_flag_mask                           (0x00000040)
#define TMDS_DET_STS_red_pos_de_err_flag_mask                         (0x00000020)
#define TMDS_DET_STS_grn_pos_de_err_flag_mask                         (0x00000010)
#define TMDS_DET_STS_blu_pos_de_err_flag_mask                         (0x00000008)
#define TMDS_DET_STS_red_neg_de_err_flag_mask                         (0x00000004)
#define TMDS_DET_STS_grn_neg_de_err_flag_mask                         (0x00000002)
#define TMDS_DET_STS_blu_neg_de_err_flag_mask                         (0x00000001)
#define TMDS_DET_STS_red_tran_err_flag(data)                          (0x00000100&((data)<<8))
#define TMDS_DET_STS_grn_tran_err_flag(data)                          (0x00000080&((data)<<7))
#define TMDS_DET_STS_blu_tran_err_flag(data)                          (0x00000040&((data)<<6))
#define TMDS_DET_STS_red_pos_de_err_flag(data)                        (0x00000020&((data)<<5))
#define TMDS_DET_STS_grn_pos_de_err_flag(data)                        (0x00000010&((data)<<4))
#define TMDS_DET_STS_blu_pos_de_err_flag(data)                        (0x00000008&((data)<<3))
#define TMDS_DET_STS_red_neg_de_err_flag(data)                        (0x00000004&((data)<<2))
#define TMDS_DET_STS_grn_neg_de_err_flag(data)                        (0x00000002&((data)<<1))
#define TMDS_DET_STS_blu_neg_de_err_flag(data)                        (0x00000001&(data))
#define TMDS_DET_STS_get_red_tran_err_flag(data)                      ((0x00000100&(data))>>8)
#define TMDS_DET_STS_get_grn_tran_err_flag(data)                      ((0x00000080&(data))>>7)
#define TMDS_DET_STS_get_blu_tran_err_flag(data)                      ((0x00000040&(data))>>6)
#define TMDS_DET_STS_get_red_pos_de_err_flag(data)                    ((0x00000020&(data))>>5)
#define TMDS_DET_STS_get_grn_pos_de_err_flag(data)                    ((0x00000010&(data))>>4)
#define TMDS_DET_STS_get_blu_pos_de_err_flag(data)                    ((0x00000008&(data))>>3)
#define TMDS_DET_STS_get_red_neg_de_err_flag(data)                    ((0x00000004&(data))>>2)
#define TMDS_DET_STS_get_grn_neg_de_err_flag(data)                    ((0x00000002&(data))>>1)
#define TMDS_DET_STS_get_blu_neg_de_err_flag(data)                    (0x00000001&(data))


#define VIDEO_BIT_ERR_DET                                             0x060
#define VIDEO_BIT_ERR_DET_reg_addr                                    "0x98034060"
#define VIDEO_BIT_ERR_DET_reg                                         0x98034060
#define VIDEO_BIT_ERR_DET_inst_addr                                   "0x0018"
#define VIDEO_BIT_ERR_DET_inst                                        0x0018
#define set_VIDEO_BIT_ERR_DET_reg(data)                               (*((volatile unsigned int*)VIDEO_BIT_ERR_DET_reg)=data)
#define get_VIDEO_BIT_ERR_DET_reg                                     (*((volatile unsigned int*)VIDEO_BIT_ERR_DET_reg))
#define VIDEO_BIT_ERR_DET_thd_shift                                   (16)
#define VIDEO_BIT_ERR_DET_disparity_reset_mode_shift                  (12)
#define VIDEO_BIT_ERR_DET_irq_en_shift                                (11)
#define VIDEO_BIT_ERR_DET_reset_shift                                 (10)
#define VIDEO_BIT_ERR_DET_period_shift                                (4)
#define VIDEO_BIT_ERR_DET_ch_sel_shift                                (2)
#define VIDEO_BIT_ERR_DET_mode_shift                                  (1)
#define VIDEO_BIT_ERR_DET_en_shift                                    (0)
#define VIDEO_BIT_ERR_DET_thd_mask                                    (0xFFFF0000)
#define VIDEO_BIT_ERR_DET_disparity_reset_mode_mask                   (0x00001000)
#define VIDEO_BIT_ERR_DET_irq_en_mask                                 (0x00000800)
#define VIDEO_BIT_ERR_DET_reset_mask                                  (0x00000400)
#define VIDEO_BIT_ERR_DET_period_mask                                 (0x000003F0)
#define VIDEO_BIT_ERR_DET_ch_sel_mask                                 (0x0000000C)
#define VIDEO_BIT_ERR_DET_mode_mask                                   (0x00000002)
#define VIDEO_BIT_ERR_DET_en_mask                                     (0x00000001)
#define VIDEO_BIT_ERR_DET_thd(data)                                   (0xFFFF0000&((data)<<16))
#define VIDEO_BIT_ERR_DET_disparity_reset_mode(data)                  (0x00001000&((data)<<12))
#define VIDEO_BIT_ERR_DET_irq_en(data)                                (0x00000800&((data)<<11))
#define VIDEO_BIT_ERR_DET_reset(data)                                 (0x00000400&((data)<<10))
#define VIDEO_BIT_ERR_DET_period(data)                                (0x000003F0&((data)<<4))
#define VIDEO_BIT_ERR_DET_ch_sel(data)                                (0x0000000C&((data)<<2))
#define VIDEO_BIT_ERR_DET_mode(data)                                  (0x00000002&((data)<<1))
#define VIDEO_BIT_ERR_DET_en(data)                                    (0x00000001&(data))
#define VIDEO_BIT_ERR_DET_get_thd(data)                               ((0xFFFF0000&(data))>>16)
#define VIDEO_BIT_ERR_DET_get_disparity_reset_mode(data)              ((0x00001000&(data))>>12)
#define VIDEO_BIT_ERR_DET_get_irq_en(data)                            ((0x00000800&(data))>>11)
#define VIDEO_BIT_ERR_DET_get_reset(data)                             ((0x00000400&(data))>>10)
#define VIDEO_BIT_ERR_DET_get_period(data)                            ((0x000003F0&(data))>>4)
#define VIDEO_BIT_ERR_DET_get_ch_sel(data)                            ((0x0000000C&(data))>>2)
#define VIDEO_BIT_ERR_DET_get_mode(data)                              ((0x00000002&(data))>>1)
#define VIDEO_BIT_ERR_DET_get_en(data)                                (0x00000001&(data))


#define VIDEO_BIT_ERR_STATUS_B                                        0x064
#define VIDEO_BIT_ERR_STATUS_B_reg_addr                               "0x98034064"
#define VIDEO_BIT_ERR_STATUS_B_reg                                    0x98034064
#define VIDEO_BIT_ERR_STATUS_B_inst_addr                              "0x0019"
#define VIDEO_BIT_ERR_STATUS_B_inst                                   0x0019
#define set_VIDEO_BIT_ERR_STATUS_B_reg(data)                          (*((volatile unsigned int*)VIDEO_BIT_ERR_STATUS_B_reg)=data)
#define get_VIDEO_BIT_ERR_STATUS_B_reg                                (*((volatile unsigned int*)VIDEO_BIT_ERR_STATUS_B_reg))
#define VIDEO_BIT_ERR_STATUS_B_ad_max_b_shift                         (26)
#define VIDEO_BIT_ERR_STATUS_B_ad_min_b_shift                         (20)
#define VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b_shift                   (19)
#define VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b_shift                    (18)
#define VIDEO_BIT_ERR_STATUS_B_bit_err_b_shift                        (17)
#define VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b_shift                 (16)
#define VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_b_shift                    (0)
#define VIDEO_BIT_ERR_STATUS_B_ad_max_b_mask                          (0xFC000000)
#define VIDEO_BIT_ERR_STATUS_B_ad_min_b_mask                          (0x03F00000)
#define VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b_mask                    (0x00080000)
#define VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b_mask                     (0x00040000)
#define VIDEO_BIT_ERR_STATUS_B_bit_err_b_mask                         (0x00020000)
#define VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b_mask                  (0x00010000)
#define VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_b_mask                     (0x0000FFFF)
#define VIDEO_BIT_ERR_STATUS_B_ad_max_b(data)                         (0xFC000000&((data)<<26))
#define VIDEO_BIT_ERR_STATUS_B_ad_min_b(data)                         (0x03F00000&((data)<<20))
#define VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b(data)                   (0x00080000&((data)<<19))
#define VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b(data)                    (0x00040000&((data)<<18))
#define VIDEO_BIT_ERR_STATUS_B_bit_err_b(data)                        (0x00020000&((data)<<17))
#define VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b(data)                 (0x00010000&((data)<<16))
#define VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_b(data)                    (0x0000FFFF&(data))
#define VIDEO_BIT_ERR_STATUS_B_get_ad_max_b(data)                     ((0xFC000000&(data))>>26)
#define VIDEO_BIT_ERR_STATUS_B_get_ad_min_b(data)                     ((0x03F00000&(data))>>20)
#define VIDEO_BIT_ERR_STATUS_B_get_no_dis_reset_b(data)               ((0x00080000&(data))>>19)
#define VIDEO_BIT_ERR_STATUS_B_get_bit_err_thd_b(data)                ((0x00040000&(data))>>18)
#define VIDEO_BIT_ERR_STATUS_B_get_bit_err_b(data)                    ((0x00020000&(data))>>17)
#define VIDEO_BIT_ERR_STATUS_B_get_bit_err_cnt_of_b(data)             ((0x00010000&(data))>>16)
#define VIDEO_BIT_ERR_STATUS_B_get_bit_err_cnt_b(data)                (0x0000FFFF&(data))


#define VIDEO_BIT_ERR_STATUS_G                                        0x068
#define VIDEO_BIT_ERR_STATUS_G_reg_addr                               "0x98034068"
#define VIDEO_BIT_ERR_STATUS_G_reg                                    0x98034068
#define VIDEO_BIT_ERR_STATUS_G_inst_addr                              "0x001A"
#define VIDEO_BIT_ERR_STATUS_G_inst                                   0x001A
#define set_VIDEO_BIT_ERR_STATUS_G_reg(data)                          (*((volatile unsigned int*)VIDEO_BIT_ERR_STATUS_G_reg)=data)
#define get_VIDEO_BIT_ERR_STATUS_G_reg                                (*((volatile unsigned int*)VIDEO_BIT_ERR_STATUS_G_reg))
#define VIDEO_BIT_ERR_STATUS_G_ad_max_g_shift                         (26)
#define VIDEO_BIT_ERR_STATUS_G_ad_min_g_shift                         (20)
#define VIDEO_BIT_ERR_STATUS_G_no_dis_reset_g_shift                   (19)
#define VIDEO_BIT_ERR_STATUS_G_bit_err_thd_g_shift                    (18)
#define VIDEO_BIT_ERR_STATUS_G_bit_err_g_shift                        (17)
#define VIDEO_BIT_ERR_STATUS_G_bit_err_cnt_of_g_shift                 (16)
#define VIDEO_BIT_ERR_STATUS_G_bit_err_cnt_g_shift                    (0)
#define VIDEO_BIT_ERR_STATUS_G_ad_max_g_mask                          (0xFC000000)
#define VIDEO_BIT_ERR_STATUS_G_ad_min_g_mask                          (0x03F00000)
#define VIDEO_BIT_ERR_STATUS_G_no_dis_reset_g_mask                    (0x00080000)
#define VIDEO_BIT_ERR_STATUS_G_bit_err_thd_g_mask                     (0x00040000)
#define VIDEO_BIT_ERR_STATUS_G_bit_err_g_mask                         (0x00020000)
#define VIDEO_BIT_ERR_STATUS_G_bit_err_cnt_of_g_mask                  (0x00010000)
#define VIDEO_BIT_ERR_STATUS_G_bit_err_cnt_g_mask                     (0x0000FFFF)
#define VIDEO_BIT_ERR_STATUS_G_ad_max_g(data)                         (0xFC000000&((data)<<26))
#define VIDEO_BIT_ERR_STATUS_G_ad_min_g(data)                         (0x03F00000&((data)<<20))
#define VIDEO_BIT_ERR_STATUS_G_no_dis_reset_g(data)                   (0x00080000&((data)<<19))
#define VIDEO_BIT_ERR_STATUS_G_bit_err_thd_g(data)                    (0x00040000&((data)<<18))
#define VIDEO_BIT_ERR_STATUS_G_bit_err_g(data)                        (0x00020000&((data)<<17))
#define VIDEO_BIT_ERR_STATUS_G_bit_err_cnt_of_g(data)                 (0x00010000&((data)<<16))
#define VIDEO_BIT_ERR_STATUS_G_bit_err_cnt_g(data)                    (0x0000FFFF&(data))
#define VIDEO_BIT_ERR_STATUS_G_get_ad_max_g(data)                     ((0xFC000000&(data))>>26)
#define VIDEO_BIT_ERR_STATUS_G_get_ad_min_g(data)                     ((0x03F00000&(data))>>20)
#define VIDEO_BIT_ERR_STATUS_G_get_no_dis_reset_g(data)               ((0x00080000&(data))>>19)
#define VIDEO_BIT_ERR_STATUS_G_get_bit_err_thd_g(data)                ((0x00040000&(data))>>18)
#define VIDEO_BIT_ERR_STATUS_G_get_bit_err_g(data)                    ((0x00020000&(data))>>17)
#define VIDEO_BIT_ERR_STATUS_G_get_bit_err_cnt_of_g(data)             ((0x00010000&(data))>>16)
#define VIDEO_BIT_ERR_STATUS_G_get_bit_err_cnt_g(data)                (0x0000FFFF&(data))


#define VIDEO_BIT_ERR_STATUS_R                                        0x06c
#define VIDEO_BIT_ERR_STATUS_R_reg_addr                               "0x9803406c"
#define VIDEO_BIT_ERR_STATUS_R_reg                                    0x9803406c
#define VIDEO_BIT_ERR_STATUS_R_inst_addr                              "0x001B"
#define VIDEO_BIT_ERR_STATUS_R_inst                                   0x001B
#define set_VIDEO_BIT_ERR_STATUS_R_reg(data)                          (*((volatile unsigned int*)VIDEO_BIT_ERR_STATUS_R_reg)=data)
#define get_VIDEO_BIT_ERR_STATUS_R_reg                                (*((volatile unsigned int*)VIDEO_BIT_ERR_STATUS_R_reg))
#define VIDEO_BIT_ERR_STATUS_R_ad_max_r_shift                         (26)
#define VIDEO_BIT_ERR_STATUS_R_ad_min_r_shift                         (20)
#define VIDEO_BIT_ERR_STATUS_R_no_dis_reset_r_shift                   (19)
#define VIDEO_BIT_ERR_STATUS_R_bit_err_thd_r_shift                    (18)
#define VIDEO_BIT_ERR_STATUS_R_bit_err_r_shift                        (17)
#define VIDEO_BIT_ERR_STATUS_R_bit_err_cnt_of_r_shift                 (16)
#define VIDEO_BIT_ERR_STATUS_R_bit_err_cnt_r_shift                    (0)
#define VIDEO_BIT_ERR_STATUS_R_ad_max_r_mask                          (0xFC000000)
#define VIDEO_BIT_ERR_STATUS_R_ad_min_r_mask                          (0x03F00000)
#define VIDEO_BIT_ERR_STATUS_R_no_dis_reset_r_mask                    (0x00080000)
#define VIDEO_BIT_ERR_STATUS_R_bit_err_thd_r_mask                     (0x00040000)
#define VIDEO_BIT_ERR_STATUS_R_bit_err_r_mask                         (0x00020000)
#define VIDEO_BIT_ERR_STATUS_R_bit_err_cnt_of_r_mask                  (0x00010000)
#define VIDEO_BIT_ERR_STATUS_R_bit_err_cnt_r_mask                     (0x0000FFFF)
#define VIDEO_BIT_ERR_STATUS_R_ad_max_r(data)                         (0xFC000000&((data)<<26))
#define VIDEO_BIT_ERR_STATUS_R_ad_min_r(data)                         (0x03F00000&((data)<<20))
#define VIDEO_BIT_ERR_STATUS_R_no_dis_reset_r(data)                   (0x00080000&((data)<<19))
#define VIDEO_BIT_ERR_STATUS_R_bit_err_thd_r(data)                    (0x00040000&((data)<<18))
#define VIDEO_BIT_ERR_STATUS_R_bit_err_r(data)                        (0x00020000&((data)<<17))
#define VIDEO_BIT_ERR_STATUS_R_bit_err_cnt_of_r(data)                 (0x00010000&((data)<<16))
#define VIDEO_BIT_ERR_STATUS_R_bit_err_cnt_r(data)                    (0x0000FFFF&(data))
#define VIDEO_BIT_ERR_STATUS_R_get_ad_max_r(data)                     ((0xFC000000&(data))>>26)
#define VIDEO_BIT_ERR_STATUS_R_get_ad_min_r(data)                     ((0x03F00000&(data))>>20)
#define VIDEO_BIT_ERR_STATUS_R_get_no_dis_reset_r(data)               ((0x00080000&(data))>>19)
#define VIDEO_BIT_ERR_STATUS_R_get_bit_err_thd_r(data)                ((0x00040000&(data))>>18)
#define VIDEO_BIT_ERR_STATUS_R_get_bit_err_r(data)                    ((0x00020000&(data))>>17)
#define VIDEO_BIT_ERR_STATUS_R_get_bit_err_cnt_of_r(data)             ((0x00010000&(data))>>16)
#define VIDEO_BIT_ERR_STATUS_R_get_bit_err_cnt_r(data)                (0x0000FFFF&(data))


#define TERC4_ERR_DET                                                 0x070
#define TERC4_ERR_DET_reg_addr                                        "0x98034070"
#define TERC4_ERR_DET_reg                                             0x98034070
#define TERC4_ERR_DET_inst_addr                                       "0x001C"
#define TERC4_ERR_DET_inst                                            0x001C
#define set_TERC4_ERR_DET_reg(data)                                   (*((volatile unsigned int*)TERC4_ERR_DET_reg)=data)
#define get_TERC4_ERR_DET_reg                                         (*((volatile unsigned int*)TERC4_ERR_DET_reg))
#define TERC4_ERR_DET_terc4_thd_shift                                 (0)
#define TERC4_ERR_DET_terc4_thd_mask                                  (0x0000FFFF)
#define TERC4_ERR_DET_terc4_thd(data)                                 (0x0000FFFF&(data))
#define TERC4_ERR_DET_get_terc4_thd(data)                             (0x0000FFFF&(data))


#define TERC4_ERR_STATUS_B                                            0x074
#define TERC4_ERR_STATUS_B_reg_addr                                   "0x98034074"
#define TERC4_ERR_STATUS_B_reg                                        0x98034074
#define TERC4_ERR_STATUS_B_inst_addr                                  "0x001D"
#define TERC4_ERR_STATUS_B_inst                                       0x001D
#define set_TERC4_ERR_STATUS_B_reg(data)                              (*((volatile unsigned int*)TERC4_ERR_STATUS_B_reg)=data)
#define get_TERC4_ERR_STATUS_B_reg                                    (*((volatile unsigned int*)TERC4_ERR_STATUS_B_reg))
#define TERC4_ERR_STATUS_B_terc4_err_thd_b_shift                      (18)
#define TERC4_ERR_STATUS_B_terc4_err_b_shift                          (17)
#define TERC4_ERR_STATUS_B_terc4_err_cnt_of_b_shift                   (16)
#define TERC4_ERR_STATUS_B_terc4_err_cnt_b_shift                      (0)
#define TERC4_ERR_STATUS_B_terc4_err_thd_b_mask                       (0x00040000)
#define TERC4_ERR_STATUS_B_terc4_err_b_mask                           (0x00020000)
#define TERC4_ERR_STATUS_B_terc4_err_cnt_of_b_mask                    (0x00010000)
#define TERC4_ERR_STATUS_B_terc4_err_cnt_b_mask                       (0x0000FFFF)
#define TERC4_ERR_STATUS_B_terc4_err_thd_b(data)                      (0x00040000&((data)<<18))
#define TERC4_ERR_STATUS_B_terc4_err_b(data)                          (0x00020000&((data)<<17))
#define TERC4_ERR_STATUS_B_terc4_err_cnt_of_b(data)                   (0x00010000&((data)<<16))
#define TERC4_ERR_STATUS_B_terc4_err_cnt_b(data)                      (0x0000FFFF&(data))
#define TERC4_ERR_STATUS_B_get_terc4_err_thd_b(data)                  ((0x00040000&(data))>>18)
#define TERC4_ERR_STATUS_B_get_terc4_err_b(data)                      ((0x00020000&(data))>>17)
#define TERC4_ERR_STATUS_B_get_terc4_err_cnt_of_b(data)               ((0x00010000&(data))>>16)
#define TERC4_ERR_STATUS_B_get_terc4_err_cnt_b(data)                  (0x0000FFFF&(data))


#define TERC4_ERR_STATUS_G                                            0x078
#define TERC4_ERR_STATUS_G_reg_addr                                   "0x98034078"
#define TERC4_ERR_STATUS_G_reg                                        0x98034078
#define TERC4_ERR_STATUS_G_inst_addr                                  "0x001E"
#define TERC4_ERR_STATUS_G_inst                                       0x001E
#define set_TERC4_ERR_STATUS_G_reg(data)                              (*((volatile unsigned int*)TERC4_ERR_STATUS_G_reg)=data)
#define get_TERC4_ERR_STATUS_G_reg                                    (*((volatile unsigned int*)TERC4_ERR_STATUS_G_reg))
#define TERC4_ERR_STATUS_G_terc4_err_thd_g_shift                      (18)
#define TERC4_ERR_STATUS_G_terc4_err_g_shift                          (17)
#define TERC4_ERR_STATUS_G_terc4_err_cnt_of_g_shift                   (16)
#define TERC4_ERR_STATUS_G_terc4_err_cnt_g_shift                      (0)
#define TERC4_ERR_STATUS_G_terc4_err_thd_g_mask                       (0x00040000)
#define TERC4_ERR_STATUS_G_terc4_err_g_mask                           (0x00020000)
#define TERC4_ERR_STATUS_G_terc4_err_cnt_of_g_mask                    (0x00010000)
#define TERC4_ERR_STATUS_G_terc4_err_cnt_g_mask                       (0x0000FFFF)
#define TERC4_ERR_STATUS_G_terc4_err_thd_g(data)                      (0x00040000&((data)<<18))
#define TERC4_ERR_STATUS_G_terc4_err_g(data)                          (0x00020000&((data)<<17))
#define TERC4_ERR_STATUS_G_terc4_err_cnt_of_g(data)                   (0x00010000&((data)<<16))
#define TERC4_ERR_STATUS_G_terc4_err_cnt_g(data)                      (0x0000FFFF&(data))
#define TERC4_ERR_STATUS_G_get_terc4_err_thd_g(data)                  ((0x00040000&(data))>>18)
#define TERC4_ERR_STATUS_G_get_terc4_err_g(data)                      ((0x00020000&(data))>>17)
#define TERC4_ERR_STATUS_G_get_terc4_err_cnt_of_g(data)               ((0x00010000&(data))>>16)
#define TERC4_ERR_STATUS_G_get_terc4_err_cnt_g(data)                  (0x0000FFFF&(data))


#define TERC4_ERR_STATUS_R                                            0x07c
#define TERC4_ERR_STATUS_R_reg_addr                                   "0x9803407c"
#define TERC4_ERR_STATUS_R_reg                                        0x9803407c
#define TERC4_ERR_STATUS_R_inst_addr                                  "0x001F"
#define TERC4_ERR_STATUS_R_inst                                       0x001F
#define set_TERC4_ERR_STATUS_R_reg(data)                              (*((volatile unsigned int*)TERC4_ERR_STATUS_R_reg)=data)
#define get_TERC4_ERR_STATUS_R_reg                                    (*((volatile unsigned int*)TERC4_ERR_STATUS_R_reg))
#define TERC4_ERR_STATUS_R_terc4_err_thd_r_shift                      (18)
#define TERC4_ERR_STATUS_R_terc4_err_r_shift                          (17)
#define TERC4_ERR_STATUS_R_terc4_err_cnt_of_r_shift                   (16)
#define TERC4_ERR_STATUS_R_terc4_err_cnt_r_shift                      (0)
#define TERC4_ERR_STATUS_R_terc4_err_thd_r_mask                       (0x00040000)
#define TERC4_ERR_STATUS_R_terc4_err_r_mask                           (0x00020000)
#define TERC4_ERR_STATUS_R_terc4_err_cnt_of_r_mask                    (0x00010000)
#define TERC4_ERR_STATUS_R_terc4_err_cnt_r_mask                       (0x0000FFFF)
#define TERC4_ERR_STATUS_R_terc4_err_thd_r(data)                      (0x00040000&((data)<<18))
#define TERC4_ERR_STATUS_R_terc4_err_r(data)                          (0x00020000&((data)<<17))
#define TERC4_ERR_STATUS_R_terc4_err_cnt_of_r(data)                   (0x00010000&((data)<<16))
#define TERC4_ERR_STATUS_R_terc4_err_cnt_r(data)                      (0x0000FFFF&(data))
#define TERC4_ERR_STATUS_R_get_terc4_err_thd_r(data)                  ((0x00040000&(data))>>18)
#define TERC4_ERR_STATUS_R_get_terc4_err_r(data)                      ((0x00020000&(data))>>17)
#define TERC4_ERR_STATUS_R_get_terc4_err_cnt_of_r(data)               ((0x00010000&(data))>>16)
#define TERC4_ERR_STATUS_R_get_terc4_err_cnt_r(data)                  (0x0000FFFF&(data))


#define HDMI_SR                                                       0x080
#define HDMI_SR_reg_addr                                              "0x98034080"
#define HDMI_SR_reg                                                   0x98034080
#define HDMI_SR_inst_addr                                             "0x0020"
#define HDMI_SR_inst                                                  0x0020
#define set_HDMI_SR_reg(data)                                         (*((volatile unsigned int*)HDMI_SR_reg)=data)
#define get_HDMI_SR_reg                                               (*((volatile unsigned int*)HDMI_SR_reg))
#define HDMI_SR_avmute_bg_shift                                       (7)
#define HDMI_SR_avmute_shift                                          (6)
#define HDMI_SR_vic_shift                                             (5)
#define HDMI_SR_spdiftype_shift                                       (4)
#define HDMI_SR_pllsts_shift                                          (3)
#define HDMI_SR_afifoof_shift                                         (2)
#define HDMI_SR_afifouf_shift                                         (1)
#define HDMI_SR_mode_shift                                            (0)
#define HDMI_SR_avmute_bg_mask                                        (0x00000080)
#define HDMI_SR_avmute_mask                                           (0x00000040)
#define HDMI_SR_vic_mask                                              (0x00000020)
#define HDMI_SR_spdiftype_mask                                        (0x00000010)
#define HDMI_SR_pllsts_mask                                           (0x00000008)
#define HDMI_SR_afifoof_mask                                          (0x00000004)
#define HDMI_SR_afifouf_mask                                          (0x00000002)
#define HDMI_SR_mode_mask                                             (0x00000001)
#define HDMI_SR_avmute_bg(data)                                       (0x00000080&((data)<<7))
#define HDMI_SR_avmute(data)                                          (0x00000040&((data)<<6))
#define HDMI_SR_vic(data)                                             (0x00000020&((data)<<5))
#define HDMI_SR_spdiftype(data)                                       (0x00000010&((data)<<4))
#define HDMI_SR_pllsts(data)                                          (0x00000008&((data)<<3))
#define HDMI_SR_afifoof(data)                                         (0x00000004&((data)<<2))
#define HDMI_SR_afifouf(data)                                         (0x00000002&((data)<<1))
#define HDMI_SR_mode(data)                                            (0x00000001&(data))
#define HDMI_SR_get_avmute_bg(data)                                   ((0x00000080&(data))>>7)
#define HDMI_SR_get_avmute(data)                                      ((0x00000040&(data))>>6)
#define HDMI_SR_get_vic(data)                                         ((0x00000020&(data))>>5)
#define HDMI_SR_get_spdiftype(data)                                   ((0x00000010&(data))>>4)
#define HDMI_SR_get_pllsts(data)                                      ((0x00000008&(data))>>3)
#define HDMI_SR_get_afifoof(data)                                     ((0x00000004&(data))>>2)
#define HDMI_SR_get_afifouf(data)                                     ((0x00000002&(data))>>1)
#define HDMI_SR_get_mode(data)                                        (0x00000001&(data))


#define HDMI_GPVS                                                     0x084
#define HDMI_GPVS_reg_addr                                            "0x98034084"
#define HDMI_GPVS_reg                                                 0x98034084
#define HDMI_GPVS_inst_addr                                           "0x0021"
#define HDMI_GPVS_inst                                                0x0021
#define set_HDMI_GPVS_reg(data)                                       (*((volatile unsigned int*)HDMI_GPVS_reg)=data)
#define get_HDMI_GPVS_reg                                             (*((volatile unsigned int*)HDMI_GPVS_reg))
#define HDMI_GPVS_fvsps_shift                                         (14)
#define HDMI_GPVS_gmps_v_shift                                        (13)
#define HDMI_GPVS_vsps_v_shift                                        (12)
#define HDMI_GPVS_gmps_shift                                          (11)
#define HDMI_GPVS_vsps_shift                                          (10)
#define HDMI_GPVS_nps_shift                                           (9)
#define HDMI_GPVS_dummy_8_shift                                       (8)
#define HDMI_GPVS_dummy_7_shift                                       (7)
#define HDMI_GPVS_pis_6_shift                                         (6)
#define HDMI_GPVS_pis_5_shift                                         (5)
#define HDMI_GPVS_pvs_4_shift                                         (4)
#define HDMI_GPVS_pvs_3_shift                                         (3)
#define HDMI_GPVS_pvs_2_shift                                         (2)
#define HDMI_GPVS_pvs_1_shift                                         (1)
#define HDMI_GPVS_pvs_0_shift                                         (0)
#define HDMI_GPVS_fvsps_mask                                          (0x00004000)
#define HDMI_GPVS_gmps_v_mask                                         (0x00002000)
#define HDMI_GPVS_vsps_v_mask                                         (0x00001000)
#define HDMI_GPVS_gmps_mask                                           (0x00000800)
#define HDMI_GPVS_vsps_mask                                           (0x00000400)
#define HDMI_GPVS_nps_mask                                            (0x00000200)
#define HDMI_GPVS_dummy_8_mask                                        (0x00000100)
#define HDMI_GPVS_dummy_7_mask                                        (0x00000080)
#define HDMI_GPVS_pis_6_mask                                          (0x00000040)
#define HDMI_GPVS_pis_5_mask                                          (0x00000020)
#define HDMI_GPVS_pvs_4_mask                                          (0x00000010)
#define HDMI_GPVS_pvs_3_mask                                          (0x00000008)
#define HDMI_GPVS_pvs_2_mask                                          (0x00000004)
#define HDMI_GPVS_pvs_1_mask                                          (0x00000002)
#define HDMI_GPVS_pvs_0_mask                                          (0x00000001)
#define HDMI_GPVS_fvsps(data)                                         (0x00004000&((data)<<14))
#define HDMI_GPVS_gmps_v(data)                                        (0x00002000&((data)<<13))
#define HDMI_GPVS_vsps_v(data)                                        (0x00001000&((data)<<12))
#define HDMI_GPVS_gmps(data)                                          (0x00000800&((data)<<11))
#define HDMI_GPVS_vsps(data)                                          (0x00000400&((data)<<10))
#define HDMI_GPVS_nps(data)                                           (0x00000200&((data)<<9))
#define HDMI_GPVS_dummy_8(data)                                       (0x00000100&((data)<<8))
#define HDMI_GPVS_dummy_7(data)                                       (0x00000080&((data)<<7))
#define HDMI_GPVS_pis_6(data)                                         (0x00000040&((data)<<6))
#define HDMI_GPVS_pis_5(data)                                         (0x00000020&((data)<<5))
#define HDMI_GPVS_pvs_4(data)                                         (0x00000010&((data)<<4))
#define HDMI_GPVS_pvs_3(data)                                         (0x00000008&((data)<<3))
#define HDMI_GPVS_pvs_2(data)                                         (0x00000004&((data)<<2))
#define HDMI_GPVS_pvs_1(data)                                         (0x00000002&((data)<<1))
#define HDMI_GPVS_pvs_0(data)                                         (0x00000001&(data))
#define HDMI_GPVS_get_fvsps(data)                                     ((0x00004000&(data))>>14)
#define HDMI_GPVS_get_gmps_v(data)                                    ((0x00002000&(data))>>13)
#define HDMI_GPVS_get_vsps_v(data)                                    ((0x00001000&(data))>>12)
#define HDMI_GPVS_get_gmps(data)                                      ((0x00000800&(data))>>11)
#define HDMI_GPVS_get_vsps(data)                                      ((0x00000400&(data))>>10)
#define HDMI_GPVS_get_nps(data)                                       ((0x00000200&(data))>>9)
#define HDMI_GPVS_get_dummy_8(data)                                   ((0x00000100&(data))>>8)
#define HDMI_GPVS_get_dummy_7(data)                                   ((0x00000080&(data))>>7)
#define HDMI_GPVS_get_pis_6(data)                                     ((0x00000040&(data))>>6)
#define HDMI_GPVS_get_pis_5(data)                                     ((0x00000020&(data))>>5)
#define HDMI_GPVS_get_pvs_4(data)                                     ((0x00000010&(data))>>4)
#define HDMI_GPVS_get_pvs_3(data)                                     ((0x00000008&(data))>>3)
#define HDMI_GPVS_get_pvs_2(data)                                     ((0x00000004&(data))>>2)
#define HDMI_GPVS_get_pvs_1(data)                                     ((0x00000002&(data))>>1)
#define HDMI_GPVS_get_pvs_0(data)                                     (0x00000001&(data))


#define HDMI_PSAP                                                     0x088
#define HDMI_PSAP_reg_addr                                            "0x98034088"
#define HDMI_PSAP_reg                                                 0x98034088
#define HDMI_PSAP_inst_addr                                           "0x0022"
#define HDMI_PSAP_inst                                                0x0022
#define set_HDMI_PSAP_reg(data)                                       (*((volatile unsigned int*)HDMI_PSAP_reg)=data)
#define get_HDMI_PSAP_reg                                             (*((volatile unsigned int*)HDMI_PSAP_reg))
#define HDMI_PSAP_apss_shift                                          (0)
#define HDMI_PSAP_apss_mask                                           (0x000001FF)
#define HDMI_PSAP_apss(data)                                          (0x000001FF&(data))
#define HDMI_PSAP_get_apss(data)                                      (0x000001FF&(data))


#define HDMI_PSDP                                                     0x08c
#define HDMI_PSDP_reg_addr                                            "0x9803408c"
#define HDMI_PSDP_reg                                                 0x9803408c
#define HDMI_PSDP_inst_addr                                           "0x0023"
#define HDMI_PSDP_inst                                                0x0023
#define set_HDMI_PSDP_reg(data)                                       (*((volatile unsigned int*)HDMI_PSDP_reg)=data)
#define get_HDMI_PSDP_reg                                             (*((volatile unsigned int*)HDMI_PSDP_reg))
#define HDMI_PSDP_dpss_shift                                          (0)
#define HDMI_PSDP_dpss_mask                                           (0x000000FF)
#define HDMI_PSDP_dpss(data)                                          (0x000000FF&(data))
#define HDMI_PSDP_get_dpss(data)                                      (0x000000FF&(data))


#define HDMI_SCR                                                      0x090
#define HDMI_SCR_reg_addr                                             "0x98034090"
#define HDMI_SCR_reg                                                  0x98034090
#define HDMI_SCR_inst_addr                                            "0x0024"
#define HDMI_SCR_inst                                                 0x0024
#define set_HDMI_SCR_reg(data)                                        (*((volatile unsigned int*)HDMI_SCR_reg)=data)
#define get_HDMI_SCR_reg                                              (*((volatile unsigned int*)HDMI_SCR_reg))
#define HDMI_SCR_nval_shift                                           (8)
#define HDMI_SCR_no_vs_det_en_shift                                   (6)
#define HDMI_SCR_dvi_reset_ds_cm_en_shift                             (5)
#define HDMI_SCR_packet_ignore_shift                                  (4)
#define HDMI_SCR_mode_shift                                           (3)
#define HDMI_SCR_msmode_shift                                         (2)
#define HDMI_SCR_cabs_shift                                           (1)
#define HDMI_SCR_fcddip_shift                                         (0)
#define HDMI_SCR_nval_mask                                            (0x0000FF00)
#define HDMI_SCR_no_vs_det_en_mask                                    (0x00000040)
#define HDMI_SCR_dvi_reset_ds_cm_en_mask                              (0x00000020)
#define HDMI_SCR_packet_ignore_mask                                   (0x00000010)
#define HDMI_SCR_mode_mask                                            (0x00000008)
#define HDMI_SCR_msmode_mask                                          (0x00000004)
#define HDMI_SCR_cabs_mask                                            (0x00000002)
#define HDMI_SCR_fcddip_mask                                          (0x00000001)
#define HDMI_SCR_nval(data)                                           (0x0000FF00&((data)<<8))
#define HDMI_SCR_no_vs_det_en(data)                                   (0x00000040&((data)<<6))
#define HDMI_SCR_dvi_reset_ds_cm_en(data)                             (0x00000020&((data)<<5))
#define HDMI_SCR_packet_ignore(data)                                  (0x00000010&((data)<<4))
#define HDMI_SCR_mode(data)                                           (0x00000008&((data)<<3))
#define HDMI_SCR_msmode(data)                                         (0x00000004&((data)<<2))
#define HDMI_SCR_cabs(data)                                           (0x00000002&((data)<<1))
#define HDMI_SCR_fcddip(data)                                         (0x00000001&(data))
#define HDMI_SCR_get_nval(data)                                       ((0x0000FF00&(data))>>8)
#define HDMI_SCR_get_no_vs_det_en(data)                               ((0x00000040&(data))>>6)
#define HDMI_SCR_get_dvi_reset_ds_cm_en(data)                         ((0x00000020&(data))>>5)
#define HDMI_SCR_get_packet_ignore(data)                              ((0x00000010&(data))>>4)
#define HDMI_SCR_get_mode(data)                                       ((0x00000008&(data))>>3)
#define HDMI_SCR_get_msmode(data)                                     ((0x00000004&(data))>>2)
#define HDMI_SCR_get_cabs(data)                                       ((0x00000002&(data))>>1)
#define HDMI_SCR_get_fcddip(data)                                     (0x00000001&(data))


#define HDMI_BCHCR                                                    0x094
#define HDMI_BCHCR_reg_addr                                           "0x98034094"
#define HDMI_BCHCR_reg                                                0x98034094
#define HDMI_BCHCR_inst_addr                                          "0x0025"
#define HDMI_BCHCR_inst                                               0x0025
#define set_HDMI_BCHCR_reg(data)                                      (*((volatile unsigned int*)HDMI_BCHCR_reg)=data)
#define get_HDMI_BCHCR_reg                                            (*((volatile unsigned int*)HDMI_BCHCR_reg))
#define HDMI_BCHCR_spcss_shift                                        (5)
#define HDMI_BCHCR_enrwe_shift                                        (4)
#define HDMI_BCHCR_bche_shift                                         (3)
#define HDMI_BCHCR_bches_shift                                        (2)
#define HDMI_BCHCR_bches2_shift                                       (1)
#define HDMI_BCHCR_pe_shift                                           (0)
#define HDMI_BCHCR_spcss_mask                                         (0x00000020)
#define HDMI_BCHCR_enrwe_mask                                         (0x00000010)
#define HDMI_BCHCR_bche_mask                                          (0x00000008)
#define HDMI_BCHCR_bches_mask                                         (0x00000004)
#define HDMI_BCHCR_bches2_mask                                        (0x00000002)
#define HDMI_BCHCR_pe_mask                                            (0x00000001)
#define HDMI_BCHCR_spcss(data)                                        (0x00000020&((data)<<5))
#define HDMI_BCHCR_enrwe(data)                                        (0x00000010&((data)<<4))
#define HDMI_BCHCR_bche(data)                                         (0x00000008&((data)<<3))
#define HDMI_BCHCR_bches(data)                                        (0x00000004&((data)<<2))
#define HDMI_BCHCR_bches2(data)                                       (0x00000002&((data)<<1))
#define HDMI_BCHCR_pe(data)                                           (0x00000001&(data))
#define HDMI_BCHCR_get_spcss(data)                                    ((0x00000020&(data))>>5)
#define HDMI_BCHCR_get_enrwe(data)                                    ((0x00000010&(data))>>4)
#define HDMI_BCHCR_get_bche(data)                                     ((0x00000008&(data))>>3)
#define HDMI_BCHCR_get_bches(data)                                    ((0x00000004&(data))>>2)
#define HDMI_BCHCR_get_bches2(data)                                   ((0x00000002&(data))>>1)
#define HDMI_BCHCR_get_pe(data)                                       (0x00000001&(data))


#define HDMI_AVMCR                                                    0x098
#define HDMI_AVMCR_reg_addr                                           "0x98034098"
#define HDMI_AVMCR_reg                                                0x98034098
#define HDMI_AVMCR_inst_addr                                          "0x0026"
#define HDMI_AVMCR_inst                                               0x0026
#define set_HDMI_AVMCR_reg(data)                                      (*((volatile unsigned int*)HDMI_AVMCR_reg)=data)
#define get_HDMI_AVMCR_reg                                            (*((volatile unsigned int*)HDMI_AVMCR_reg))
#define HDMI_AVMCR_wd_ptg_en_shift                                    (10)
#define HDMI_AVMCR_wd_vclk_en_shift                                   (9)
#define HDMI_AVMCR_avmute_flag_shift                                  (8)
#define HDMI_AVMCR_avmute_win_en_shift                                (7)
#define HDMI_AVMCR_aoc_shift                                          (6)
#define HDMI_AVMCR_aomc_shift                                         (5)
#define HDMI_AVMCR_awd_shift                                          (4)
#define HDMI_AVMCR_ve_shift                                           (3)
#define HDMI_AVMCR_ampic_shift                                        (2)
#define HDMI_AVMCR_vdpic_shift                                        (1)
#define HDMI_AVMCR_nfpss_shift                                        (0)
#define HDMI_AVMCR_wd_ptg_en_mask                                     (0x00000400)
#define HDMI_AVMCR_wd_vclk_en_mask                                    (0x00000200)
#define HDMI_AVMCR_avmute_flag_mask                                   (0x00000100)
#define HDMI_AVMCR_avmute_win_en_mask                                 (0x00000080)
#define HDMI_AVMCR_aoc_mask                                           (0x00000040)
#define HDMI_AVMCR_aomc_mask                                          (0x00000020)
#define HDMI_AVMCR_awd_mask                                           (0x00000010)
#define HDMI_AVMCR_ve_mask                                            (0x00000008)
#define HDMI_AVMCR_ampic_mask                                         (0x00000004)
#define HDMI_AVMCR_vdpic_mask                                         (0x00000002)
#define HDMI_AVMCR_nfpss_mask                                         (0x00000001)
#define HDMI_AVMCR_wd_ptg_en(data)                                    (0x00000400&((data)<<10))
#define HDMI_AVMCR_wd_vclk_en(data)                                   (0x00000200&((data)<<9))
#define HDMI_AVMCR_avmute_flag(data)                                  (0x00000100&((data)<<8))
#define HDMI_AVMCR_avmute_win_en(data)                                (0x00000080&((data)<<7))
#define HDMI_AVMCR_aoc(data)                                          (0x00000040&((data)<<6))
#define HDMI_AVMCR_aomc(data)                                         (0x00000020&((data)<<5))
#define HDMI_AVMCR_awd(data)                                          (0x00000010&((data)<<4))
#define HDMI_AVMCR_ve(data)                                           (0x00000008&((data)<<3))
#define HDMI_AVMCR_ampic(data)                                        (0x00000004&((data)<<2))
#define HDMI_AVMCR_vdpic(data)                                        (0x00000002&((data)<<1))
#define HDMI_AVMCR_nfpss(data)                                        (0x00000001&(data))
#define HDMI_AVMCR_get_wd_ptg_en(data)                                ((0x00000400&(data))>>10)
#define HDMI_AVMCR_get_wd_vclk_en(data)                               ((0x00000200&(data))>>9)
#define HDMI_AVMCR_get_avmute_flag(data)                              ((0x00000100&(data))>>8)
#define HDMI_AVMCR_get_avmute_win_en(data)                            ((0x00000080&(data))>>7)
#define HDMI_AVMCR_get_aoc(data)                                      ((0x00000040&(data))>>6)
#define HDMI_AVMCR_get_aomc(data)                                     ((0x00000020&(data))>>5)
#define HDMI_AVMCR_get_awd(data)                                      ((0x00000010&(data))>>4)
#define HDMI_AVMCR_get_ve(data)                                       ((0x00000008&(data))>>3)
#define HDMI_AVMCR_get_ampic(data)                                    ((0x00000004&(data))>>2)
#define HDMI_AVMCR_get_vdpic(data)                                    ((0x00000002&(data))>>1)
#define HDMI_AVMCR_get_nfpss(data)                                    (0x00000001&(data))


#define HDMI_WDCR0                                                    0x09c
#define HDMI_WDCR0_reg_addr                                           "0x9803409c"
#define HDMI_WDCR0_reg                                                0x9803409c
#define HDMI_WDCR0_inst_addr                                          "0x0027"
#define HDMI_WDCR0_inst                                               0x0027
#define set_HDMI_WDCR0_reg(data)                                      (*((volatile unsigned int*)HDMI_WDCR0_reg)=data)
#define get_HDMI_WDCR0_reg                                            (*((volatile unsigned int*)HDMI_WDCR0_reg))
#define HDMI_WDCR0_wdm_shift                                          (27)
#define HDMI_WDCR0_wds_shift                                          (26)
#define HDMI_WDCR0_awdch_shift                                        (25)
#define HDMI_WDCR0_vwdch_shift                                        (24)
#define HDMI_WDCR0_vwdap_shift                                        (23)
#define HDMI_WDCR0_vwdlf_shift                                        (22)
#define HDMI_WDCR0_vwdafo_shift                                       (21)
#define HDMI_WDCR0_vwdafu_shift                                       (20)
#define HDMI_WDCR0_yv_shift                                           (16)
#define HDMI_WDCR0_awdck_shift                                        (15)
#define HDMI_WDCR0_awdlf_shift                                        (14)
#define HDMI_WDCR0_ch_st_sel_shift                                    (13)
#define HDMI_WDCR0_vwdact_shift                                       (12)
#define HDMI_WDCR0_xv_shift                                           (8)
#define HDMI_WDCR0_asmfe_shift                                        (7)
#define HDMI_WDCR0_load_d_shift                                       (6)
#define HDMI_WDCR0_bt_track_en_shift                                  (5)
#define HDMI_WDCR0_awdct_shift                                        (4)
#define HDMI_WDCR0_awdap_shift                                        (3)
#define HDMI_WDCR0_awdfo_shift                                        (2)
#define HDMI_WDCR0_awdfu_shift                                        (1)
#define HDMI_WDCR0_ct_shift                                           (0)
#define HDMI_WDCR0_wdm_mask                                           (0x08000000)
#define HDMI_WDCR0_wds_mask                                           (0x04000000)
#define HDMI_WDCR0_awdch_mask                                         (0x02000000)
#define HDMI_WDCR0_vwdch_mask                                         (0x01000000)
#define HDMI_WDCR0_vwdap_mask                                         (0x00800000)
#define HDMI_WDCR0_vwdlf_mask                                         (0x00400000)
#define HDMI_WDCR0_vwdafo_mask                                        (0x00200000)
#define HDMI_WDCR0_vwdafu_mask                                        (0x00100000)
#define HDMI_WDCR0_yv_mask                                            (0x000F0000)
#define HDMI_WDCR0_awdck_mask                                         (0x00008000)
#define HDMI_WDCR0_awdlf_mask                                         (0x00004000)
#define HDMI_WDCR0_ch_st_sel_mask                                     (0x00002000)
#define HDMI_WDCR0_vwdact_mask                                        (0x00001000)
#define HDMI_WDCR0_xv_mask                                            (0x00000F00)
#define HDMI_WDCR0_asmfe_mask                                         (0x00000080)
#define HDMI_WDCR0_load_d_mask                                        (0x00000040)
#define HDMI_WDCR0_bt_track_en_mask                                   (0x00000020)
#define HDMI_WDCR0_awdct_mask                                         (0x00000010)
#define HDMI_WDCR0_awdap_mask                                         (0x00000008)
#define HDMI_WDCR0_awdfo_mask                                         (0x00000004)
#define HDMI_WDCR0_awdfu_mask                                         (0x00000002)
#define HDMI_WDCR0_ct_mask                                            (0x00000001)
#define HDMI_WDCR0_wdm(data)                                          (0x08000000&((data)<<27))
#define HDMI_WDCR0_wds(data)                                          (0x04000000&((data)<<26))
#define HDMI_WDCR0_awdch(data)                                        (0x02000000&((data)<<25))
#define HDMI_WDCR0_vwdch(data)                                        (0x01000000&((data)<<24))
#define HDMI_WDCR0_vwdap(data)                                        (0x00800000&((data)<<23))
#define HDMI_WDCR0_vwdlf(data)                                        (0x00400000&((data)<<22))
#define HDMI_WDCR0_vwdafo(data)                                       (0x00200000&((data)<<21))
#define HDMI_WDCR0_vwdafu(data)                                       (0x00100000&((data)<<20))
#define HDMI_WDCR0_yv(data)                                           (0x000F0000&((data)<<16))
#define HDMI_WDCR0_awdck(data)                                        (0x00008000&((data)<<15))
#define HDMI_WDCR0_awdlf(data)                                        (0x00004000&((data)<<14))
#define HDMI_WDCR0_ch_st_sel(data)                                    (0x00002000&((data)<<13))
#define HDMI_WDCR0_vwdact(data)                                       (0x00001000&((data)<<12))
#define HDMI_WDCR0_xv(data)                                           (0x00000F00&((data)<<8))
#define HDMI_WDCR0_asmfe(data)                                        (0x00000080&((data)<<7))
#define HDMI_WDCR0_load_d(data)                                       (0x00000040&((data)<<6))
#define HDMI_WDCR0_bt_track_en(data)                                  (0x00000020&((data)<<5))
#define HDMI_WDCR0_awdct(data)                                        (0x00000010&((data)<<4))
#define HDMI_WDCR0_awdap(data)                                        (0x00000008&((data)<<3))
#define HDMI_WDCR0_awdfo(data)                                        (0x00000004&((data)<<2))
#define HDMI_WDCR0_awdfu(data)                                        (0x00000002&((data)<<1))
#define HDMI_WDCR0_ct(data)                                           (0x00000001&(data))
#define HDMI_WDCR0_get_wdm(data)                                      ((0x08000000&(data))>>27)
#define HDMI_WDCR0_get_wds(data)                                      ((0x04000000&(data))>>26)
#define HDMI_WDCR0_get_awdch(data)                                    ((0x02000000&(data))>>25)
#define HDMI_WDCR0_get_vwdch(data)                                    ((0x01000000&(data))>>24)
#define HDMI_WDCR0_get_vwdap(data)                                    ((0x00800000&(data))>>23)
#define HDMI_WDCR0_get_vwdlf(data)                                    ((0x00400000&(data))>>22)
#define HDMI_WDCR0_get_vwdafo(data)                                   ((0x00200000&(data))>>21)
#define HDMI_WDCR0_get_vwdafu(data)                                   ((0x00100000&(data))>>20)
#define HDMI_WDCR0_get_yv(data)                                       ((0x000F0000&(data))>>16)
#define HDMI_WDCR0_get_awdck(data)                                    ((0x00008000&(data))>>15)
#define HDMI_WDCR0_get_awdlf(data)                                    ((0x00004000&(data))>>14)
#define HDMI_WDCR0_get_ch_st_sel(data)                                ((0x00002000&(data))>>13)
#define HDMI_WDCR0_get_vwdact(data)                                   ((0x00001000&(data))>>12)
#define HDMI_WDCR0_get_xv(data)                                       ((0x00000F00&(data))>>8)
#define HDMI_WDCR0_get_asmfe(data)                                    ((0x00000080&(data))>>7)
#define HDMI_WDCR0_get_load_d(data)                                   ((0x00000040&(data))>>6)
#define HDMI_WDCR0_get_bt_track_en(data)                              ((0x00000020&(data))>>5)
#define HDMI_WDCR0_get_awdct(data)                                    ((0x00000010&(data))>>4)
#define HDMI_WDCR0_get_awdap(data)                                    ((0x00000008&(data))>>3)
#define HDMI_WDCR0_get_awdfo(data)                                    ((0x00000004&(data))>>2)
#define HDMI_WDCR0_get_awdfu(data)                                    ((0x00000002&(data))>>1)
#define HDMI_WDCR0_get_ct(data)                                       (0x00000001&(data))


#define HDMI_DBCR                                                     0x0a0
#define HDMI_DBCR_reg_addr                                            "0x980340a0"
#define HDMI_DBCR_reg                                                 0x980340a0
#define HDMI_DBCR_inst_addr                                           "0x0028"
#define HDMI_DBCR_inst                                                0x0028
#define set_HDMI_DBCR_reg(data)                                       (*((volatile unsigned int*)HDMI_DBCR_reg)=data)
#define get_HDMI_DBCR_reg                                             (*((volatile unsigned int*)HDMI_DBCR_reg))
#define HDMI_DBCR_aldbfv_shift                                        (3)
#define HDMI_DBCR_aldbfo_shift                                        (2)
#define HDMI_DBCR_aldbfu_shift                                        (1)
#define HDMI_DBCR_aldbpn_shift                                        (0)
#define HDMI_DBCR_aldbfv_mask                                         (0x00000008)
#define HDMI_DBCR_aldbfo_mask                                         (0x00000004)
#define HDMI_DBCR_aldbfu_mask                                         (0x00000002)
#define HDMI_DBCR_aldbpn_mask                                         (0x00000001)
#define HDMI_DBCR_aldbfv(data)                                        (0x00000008&((data)<<3))
#define HDMI_DBCR_aldbfo(data)                                        (0x00000004&((data)<<2))
#define HDMI_DBCR_aldbfu(data)                                        (0x00000002&((data)<<1))
#define HDMI_DBCR_aldbpn(data)                                        (0x00000001&(data))
#define HDMI_DBCR_get_aldbfv(data)                                    ((0x00000008&(data))>>3)
#define HDMI_DBCR_get_aldbfo(data)                                    ((0x00000004&(data))>>2)
#define HDMI_DBCR_get_aldbfu(data)                                    ((0x00000002&(data))>>1)
#define HDMI_DBCR_get_aldbpn(data)                                    (0x00000001&(data))


#define HDMI_AWDSR                                                    0x0a4
#define HDMI_AWDSR_reg_addr                                           "0x980340a4"
#define HDMI_AWDSR_reg                                                0x980340a4
#define HDMI_AWDSR_inst_addr                                          "0x0029"
#define HDMI_AWDSR_inst                                               0x0029
#define set_HDMI_AWDSR_reg(data)                                      (*((volatile unsigned int*)HDMI_AWDSR_reg)=data)
#define get_HDMI_AWDSR_reg                                            (*((volatile unsigned int*)HDMI_AWDSR_reg))
#define HDMI_AWDSR_awdpvsb_shift                                      (0)
#define HDMI_AWDSR_awdpvsb_mask                                       (0x0000007F)
#define HDMI_AWDSR_awdpvsb(data)                                      (0x0000007F&(data))
#define HDMI_AWDSR_get_awdpvsb(data)                                  (0x0000007F&(data))


#define HDMI_VWDSR                                                    0x0a8
#define HDMI_VWDSR_reg_addr                                           "0x980340a8"
#define HDMI_VWDSR_reg                                                0x980340a8
#define HDMI_VWDSR_inst_addr                                          "0x002A"
#define HDMI_VWDSR_inst                                               0x002A
#define set_HDMI_VWDSR_reg(data)                                      (*((volatile unsigned int*)HDMI_VWDSR_reg)=data)
#define get_HDMI_VWDSR_reg                                            (*((volatile unsigned int*)HDMI_VWDSR_reg))
#define HDMI_VWDSR_vwdpvsb_shift                                      (0)
#define HDMI_VWDSR_vwdpvsb_mask                                       (0x0000007F)
#define HDMI_VWDSR_vwdpvsb(data)                                      (0x0000007F&(data))
#define HDMI_VWDSR_get_vwdpvsb(data)                                  (0x0000007F&(data))


#define HDMI_PAMICR                                                   0x0ac
#define HDMI_PAMICR_reg_addr                                          "0x980340ac"
#define HDMI_PAMICR_reg                                               0x980340ac
#define HDMI_PAMICR_inst_addr                                         "0x002B"
#define HDMI_PAMICR_inst                                              0x002B
#define set_HDMI_PAMICR_reg(data)                                     (*((volatile unsigned int*)HDMI_PAMICR_reg)=data)
#define get_HDMI_PAMICR_reg                                           (*((volatile unsigned int*)HDMI_PAMICR_reg))
#define HDMI_PAMICR_icpvsb_shift                                      (0)
#define HDMI_PAMICR_icpvsb_mask                                       (0x0000007F)
#define HDMI_PAMICR_icpvsb(data)                                      (0x0000007F&(data))
#define HDMI_PAMICR_get_icpvsb(data)                                  (0x0000007F&(data))


#define HDMI_PTRSV1                                                   0x0b0
#define HDMI_PTRSV1_reg_addr                                          "0x980340b0"
#define HDMI_PTRSV1_reg                                               0x980340b0
#define HDMI_PTRSV1_inst_addr                                         "0x002C"
#define HDMI_PTRSV1_inst                                              0x002C
#define set_HDMI_PTRSV1_reg(data)                                     (*((volatile unsigned int*)HDMI_PTRSV1_reg)=data)
#define get_HDMI_PTRSV1_reg                                           (*((volatile unsigned int*)HDMI_PTRSV1_reg))
#define HDMI_PTRSV1_dummy_31_24_shift                                 (24)
#define HDMI_PTRSV1_dummy_23_16_shift                                 (16)
#define HDMI_PTRSV1_pt2_shift                                         (8)
#define HDMI_PTRSV1_pt1_shift                                         (0)
#define HDMI_PTRSV1_dummy_31_24_mask                                  (0xFF000000)
#define HDMI_PTRSV1_dummy_23_16_mask                                  (0x00FF0000)
#define HDMI_PTRSV1_pt2_mask                                          (0x0000FF00)
#define HDMI_PTRSV1_pt1_mask                                          (0x000000FF)
#define HDMI_PTRSV1_dummy_31_24(data)                                 (0xFF000000&((data)<<24))
#define HDMI_PTRSV1_dummy_23_16(data)                                 (0x00FF0000&((data)<<16))
#define HDMI_PTRSV1_pt2(data)                                         (0x0000FF00&((data)<<8))
#define HDMI_PTRSV1_pt1(data)                                         (0x000000FF&(data))
#define HDMI_PTRSV1_get_dummy_31_24(data)                             ((0xFF000000&(data))>>24)
#define HDMI_PTRSV1_get_dummy_23_16(data)                             ((0x00FF0000&(data))>>16)
#define HDMI_PTRSV1_get_pt2(data)                                     ((0x0000FF00&(data))>>8)
#define HDMI_PTRSV1_get_pt1(data)                                     (0x000000FF&(data))


#define HDMI_PVGCR0                                                   0x0b4
#define HDMI_PVGCR0_reg_addr                                          "0x980340b4"
#define HDMI_PVGCR0_reg                                               0x980340b4
#define HDMI_PVGCR0_inst_addr                                         "0x002D"
#define HDMI_PVGCR0_inst                                              0x002D
#define set_HDMI_PVGCR0_reg(data)                                     (*((volatile unsigned int*)HDMI_PVGCR0_reg)=data)
#define get_HDMI_PVGCR0_reg                                           (*((volatile unsigned int*)HDMI_PVGCR0_reg))
#define HDMI_PVGCR0_pvsef_shift                                       (0)
#define HDMI_PVGCR0_pvsef_mask                                        (0xFFFFFFFF)
#define HDMI_PVGCR0_pvsef(data)                                       (0xFFFFFFFF&(data))
#define HDMI_PVGCR0_get_pvsef(data)                                   (0xFFFFFFFF&(data))


#define HDMI_PVSR0                                                    0x0b8
#define HDMI_PVSR0_reg_addr                                           "0x980340b8"
#define HDMI_PVSR0_reg                                                0x980340b8
#define HDMI_PVSR0_inst_addr                                          "0x002E"
#define HDMI_PVSR0_inst                                               0x002E
#define set_HDMI_PVSR0_reg(data)                                      (*((volatile unsigned int*)HDMI_PVSR0_reg)=data)
#define get_HDMI_PVSR0_reg                                            (*((volatile unsigned int*)HDMI_PVSR0_reg))
#define HDMI_PVSR0_pvs_shift                                          (0)
#define HDMI_PVSR0_pvs_mask                                           (0xFFFFFFFF)
#define HDMI_PVSR0_pvs(data)                                          (0xFFFFFFFF&(data))
#define HDMI_PVSR0_get_pvs(data)                                      (0xFFFFFFFF&(data))


#define HDMI_VCR                                                      0x0bc
#define HDMI_VCR_reg_addr                                             "0x980340bc"
#define HDMI_VCR_reg                                                  0x980340bc
#define HDMI_VCR_inst_addr                                            "0x002F"
#define HDMI_VCR_inst                                                 0x002F
#define set_HDMI_VCR_reg(data)                                        (*((volatile unsigned int*)HDMI_VCR_reg)=data)
#define get_HDMI_VCR_reg                                              (*((volatile unsigned int*)HDMI_VCR_reg))
#define HDMI_VCR_cbus_ddc_chsel_shift                                 (28)
#define HDMI_VCR_hdmi_field_shift                                     (27)
#define HDMI_VCR_int_pro_chg_flag_shift                               (26)
#define HDMI_VCR_int_pro_chg_wd_en_shift                              (25)
#define HDMI_VCR_int_pro_chg_int_en_shift                             (24)
#define HDMI_VCR_hdcp_ddc_chsel_shift                                 (22)
#define HDMI_VCR_iclk_sel_shift                                       (20)
#define HDMI_VCR_csc_r_shift                                          (18)
#define HDMI_VCR_hdirq_shift                                          (17)
#define HDMI_VCR_csam_shift                                           (16)
#define HDMI_VCR_csc_shift                                            (14)
#define HDMI_VCR_field_decide_sel_shift                               (13)
#define HDMI_VCR_prdsam_shift                                         (12)
#define HDMI_VCR_dsc_r_shift                                          (8)
#define HDMI_VCR_eoi_shift                                            (7)
#define HDMI_VCR_eot_shift                                            (6)
#define HDMI_VCR_se_shift                                             (5)
#define HDMI_VCR_rs_shift                                             (4)
#define HDMI_VCR_dsc_shift                                            (0)
#define HDMI_VCR_cbus_ddc_chsel_mask                                  (0x10000000)
#define HDMI_VCR_hdmi_field_mask                                      (0x08000000)
#define HDMI_VCR_int_pro_chg_flag_mask                                (0x04000000)
#define HDMI_VCR_int_pro_chg_wd_en_mask                               (0x02000000)
#define HDMI_VCR_int_pro_chg_int_en_mask                              (0x01000000)
#define HDMI_VCR_hdcp_ddc_chsel_mask                                  (0x00C00000)
#define HDMI_VCR_iclk_sel_mask                                        (0x00300000)
#define HDMI_VCR_csc_r_mask                                           (0x000C0000)
#define HDMI_VCR_hdirq_mask                                           (0x00020000)
#define HDMI_VCR_csam_mask                                            (0x00010000)
#define HDMI_VCR_csc_mask                                             (0x0000C000)
#define HDMI_VCR_field_decide_sel_mask                                (0x00002000)
#define HDMI_VCR_prdsam_mask                                          (0x00001000)
#define HDMI_VCR_dsc_r_mask                                           (0x00000F00)
#define HDMI_VCR_eoi_mask                                             (0x00000080)
#define HDMI_VCR_eot_mask                                             (0x00000040)
#define HDMI_VCR_se_mask                                              (0x00000020)
#define HDMI_VCR_rs_mask                                              (0x00000010)
#define HDMI_VCR_dsc_mask                                             (0x0000000F)
#define HDMI_VCR_cbus_ddc_chsel(data)                                 (0x10000000&((data)<<28))
#define HDMI_VCR_hdmi_field(data)                                     (0x08000000&((data)<<27))
#define HDMI_VCR_int_pro_chg_flag(data)                               (0x04000000&((data)<<26))
#define HDMI_VCR_int_pro_chg_wd_en(data)                              (0x02000000&((data)<<25))
#define HDMI_VCR_int_pro_chg_int_en(data)                             (0x01000000&((data)<<24))
#define HDMI_VCR_hdcp_ddc_chsel(data)                                 (0x00C00000&((data)<<22))
#define HDMI_VCR_iclk_sel(data)                                       (0x00300000&((data)<<20))
#define HDMI_VCR_csc_r(data)                                          (0x000C0000&((data)<<18))
#define HDMI_VCR_hdirq(data)                                          (0x00020000&((data)<<17))
#define HDMI_VCR_csam(data)                                           (0x00010000&((data)<<16))
#define HDMI_VCR_csc(data)                                            (0x0000C000&((data)<<14))
#define HDMI_VCR_field_decide_sel(data)                               (0x00002000&((data)<<13))
#define HDMI_VCR_prdsam(data)                                         (0x00001000&((data)<<12))
#define HDMI_VCR_dsc_r(data)                                          (0x00000F00&((data)<<8))
#define HDMI_VCR_eoi(data)                                            (0x00000080&((data)<<7))
#define HDMI_VCR_eot(data)                                            (0x00000040&((data)<<6))
#define HDMI_VCR_se(data)                                             (0x00000020&((data)<<5))
#define HDMI_VCR_rs(data)                                             (0x00000010&((data)<<4))
#define HDMI_VCR_dsc(data)                                            (0x0000000F&(data))
#define HDMI_VCR_get_cbus_ddc_chsel(data)                             ((0x10000000&(data))>>28)
#define HDMI_VCR_get_hdmi_field(data)                                 ((0x08000000&(data))>>27)
#define HDMI_VCR_get_int_pro_chg_flag(data)                           ((0x04000000&(data))>>26)
#define HDMI_VCR_get_int_pro_chg_wd_en(data)                          ((0x02000000&(data))>>25)
#define HDMI_VCR_get_int_pro_chg_int_en(data)                         ((0x01000000&(data))>>24)
#define HDMI_VCR_get_hdcp_ddc_chsel(data)                             ((0x00C00000&(data))>>22)
#define HDMI_VCR_get_iclk_sel(data)                                   ((0x00300000&(data))>>20)
#define HDMI_VCR_get_csc_r(data)                                      ((0x000C0000&(data))>>18)
#define HDMI_VCR_get_hdirq(data)                                      ((0x00020000&(data))>>17)
#define HDMI_VCR_get_csam(data)                                       ((0x00010000&(data))>>16)
#define HDMI_VCR_get_csc(data)                                        ((0x0000C000&(data))>>14)
#define HDMI_VCR_get_field_decide_sel(data)                           ((0x00002000&(data))>>13)
#define HDMI_VCR_get_prdsam(data)                                     ((0x00001000&(data))>>12)
#define HDMI_VCR_get_dsc_r(data)                                      ((0x00000F00&(data))>>8)
#define HDMI_VCR_get_eoi(data)                                        ((0x00000080&(data))>>7)
#define HDMI_VCR_get_eot(data)                                        ((0x00000040&(data))>>6)
#define HDMI_VCR_get_se(data)                                         ((0x00000020&(data))>>5)
#define HDMI_VCR_get_rs(data)                                         ((0x00000010&(data))>>4)
#define HDMI_VCR_get_dsc(data)                                        (0x0000000F&(data))


#define HDMI_ACRCR                                                    0x0c0
#define HDMI_ACRCR_reg_addr                                           "0x980340c0"
#define HDMI_ACRCR_reg                                                0x980340c0
#define HDMI_ACRCR_inst_addr                                          "0x0030"
#define HDMI_ACRCR_inst                                               0x0030
#define set_HDMI_ACRCR_reg(data)                                      (*((volatile unsigned int*)HDMI_ACRCR_reg)=data)
#define get_HDMI_ACRCR_reg                                            (*((volatile unsigned int*)HDMI_ACRCR_reg))
#define HDMI_ACRCR_pucnr_shift                                        (1)
#define HDMI_ACRCR_pucsr_shift                                        (0)
#define HDMI_ACRCR_pucnr_mask                                         (0x00000002)
#define HDMI_ACRCR_pucsr_mask                                         (0x00000001)
#define HDMI_ACRCR_pucnr(data)                                        (0x00000002&((data)<<1))
#define HDMI_ACRCR_pucsr(data)                                        (0x00000001&(data))
#define HDMI_ACRCR_get_pucnr(data)                                    ((0x00000002&(data))>>1)
#define HDMI_ACRCR_get_pucsr(data)                                    (0x00000001&(data))


#define HDMI_ACRSR0                                                   0x0c4
#define HDMI_ACRSR0_reg_addr                                          "0x980340c4"
#define HDMI_ACRSR0_reg                                               0x980340c4
#define HDMI_ACRSR0_inst_addr                                         "0x0031"
#define HDMI_ACRSR0_inst                                              0x0031
#define set_HDMI_ACRSR0_reg(data)                                     (*((volatile unsigned int*)HDMI_ACRSR0_reg)=data)
#define get_HDMI_ACRSR0_reg                                           (*((volatile unsigned int*)HDMI_ACRSR0_reg))
#define HDMI_ACRSR0_cts_shift                                         (0)
#define HDMI_ACRSR0_cts_mask                                          (0x000FFFFF)
#define HDMI_ACRSR0_cts(data)                                         (0x000FFFFF&(data))
#define HDMI_ACRSR0_get_cts(data)                                     (0x000FFFFF&(data))


#define HDMI_ACRSR1                                                   0x0c8
#define HDMI_ACRSR1_reg_addr                                          "0x980340c8"
#define HDMI_ACRSR1_reg                                               0x980340c8
#define HDMI_ACRSR1_inst_addr                                         "0x0032"
#define HDMI_ACRSR1_inst                                              0x0032
#define set_HDMI_ACRSR1_reg(data)                                     (*((volatile unsigned int*)HDMI_ACRSR1_reg)=data)
#define get_HDMI_ACRSR1_reg                                           (*((volatile unsigned int*)HDMI_ACRSR1_reg))
#define HDMI_ACRSR1_n_shift                                           (0)
#define HDMI_ACRSR1_n_mask                                            (0x000FFFFF)
#define HDMI_ACRSR1_n(data)                                           (0x000FFFFF&(data))
#define HDMI_ACRSR1_get_n(data)                                       (0x000FFFFF&(data))


#define HDMI_ACS0                                                     0x0cc
#define HDMI_ACS0_reg_addr                                            "0x980340cc"
#define HDMI_ACS0_reg                                                 0x980340cc
#define HDMI_ACS0_inst_addr                                           "0x0033"
#define HDMI_ACS0_inst                                                0x0033
#define set_HDMI_ACS0_reg(data)                                       (*((volatile unsigned int*)HDMI_ACS0_reg)=data)
#define get_HDMI_ACS0_reg                                             (*((volatile unsigned int*)HDMI_ACS0_reg))
#define HDMI_ACS0_cs_shift                                            (0)
#define HDMI_ACS0_cs_mask                                             (0x0000FFFF)
#define HDMI_ACS0_cs(data)                                            (0x0000FFFF&(data))
#define HDMI_ACS0_get_cs(data)                                        (0x0000FFFF&(data))


#define HDMI_ACS1                                                     0x0d0
#define HDMI_ACS1_reg_addr                                            "0x980340d0"
#define HDMI_ACS1_reg                                                 0x980340d0
#define HDMI_ACS1_inst_addr                                           "0x0034"
#define HDMI_ACS1_inst                                                0x0034
#define set_HDMI_ACS1_reg(data)                                       (*((volatile unsigned int*)HDMI_ACS1_reg)=data)
#define get_HDMI_ACS1_reg                                             (*((volatile unsigned int*)HDMI_ACS1_reg))
#define HDMI_ACS1_cs_shift                                            (0)
#define HDMI_ACS1_cs_mask                                             (0x00FFFFFF)
#define HDMI_ACS1_cs(data)                                            (0x00FFFFFF&(data))
#define HDMI_ACS1_get_cs(data)                                        (0x00FFFFFF&(data))


#define HDMI_INTCR                                                    0x0d4
#define HDMI_INTCR_reg_addr                                           "0x980340d4"
#define HDMI_INTCR_reg                                                0x980340d4
#define HDMI_INTCR_inst_addr                                          "0x0035"
#define HDMI_INTCR_inst                                               0x0035
#define set_HDMI_INTCR_reg(data)                                      (*((volatile unsigned int*)HDMI_INTCR_reg)=data)
#define get_HDMI_INTCR_reg                                            (*((volatile unsigned int*)HDMI_INTCR_reg))
#define HDMI_INTCR_pending_shift                                      (7)
#define HDMI_INTCR_avmute_shift                                       (6)
#define HDMI_INTCR_fifod_shift                                        (5)
#define HDMI_INTCR_act_shift                                          (4)
#define HDMI_INTCR_apll_shift                                         (3)
#define HDMI_INTCR_afifoo_shift                                       (2)
#define HDMI_INTCR_afifou_shift                                       (1)
#define HDMI_INTCR_vc_shift                                           (0)
#define HDMI_INTCR_pending_mask                                       (0x00000080)
#define HDMI_INTCR_avmute_mask                                        (0x00000040)
#define HDMI_INTCR_fifod_mask                                         (0x00000020)
#define HDMI_INTCR_act_mask                                           (0x00000010)
#define HDMI_INTCR_apll_mask                                          (0x00000008)
#define HDMI_INTCR_afifoo_mask                                        (0x00000004)
#define HDMI_INTCR_afifou_mask                                        (0x00000002)
#define HDMI_INTCR_vc_mask                                            (0x00000001)
#define HDMI_INTCR_pending(data)                                      (0x00000080&((data)<<7))
#define HDMI_INTCR_avmute(data)                                       (0x00000040&((data)<<6))
#define HDMI_INTCR_fifod(data)                                        (0x00000020&((data)<<5))
#define HDMI_INTCR_act(data)                                          (0x00000010&((data)<<4))
#define HDMI_INTCR_apll(data)                                         (0x00000008&((data)<<3))
#define HDMI_INTCR_afifoo(data)                                       (0x00000004&((data)<<2))
#define HDMI_INTCR_afifou(data)                                       (0x00000002&((data)<<1))
#define HDMI_INTCR_vc(data)                                           (0x00000001&(data))
#define HDMI_INTCR_get_pending(data)                                  ((0x00000080&(data))>>7)
#define HDMI_INTCR_get_avmute(data)                                   ((0x00000040&(data))>>6)
#define HDMI_INTCR_get_fifod(data)                                    ((0x00000020&(data))>>5)
#define HDMI_INTCR_get_act(data)                                      ((0x00000010&(data))>>4)
#define HDMI_INTCR_get_apll(data)                                     ((0x00000008&(data))>>3)
#define HDMI_INTCR_get_afifoo(data)                                   ((0x00000004&(data))>>2)
#define HDMI_INTCR_get_afifou(data)                                   ((0x00000002&(data))>>1)
#define HDMI_INTCR_get_vc(data)                                       (0x00000001&(data))


#define HDMI_ALCR                                                     0x0d8
#define HDMI_ALCR_reg_addr                                            "0x980340d8"
#define HDMI_ALCR_reg                                                 0x980340d8
#define HDMI_ALCR_inst_addr                                           "0x0036"
#define HDMI_ALCR_inst                                                0x0036
#define set_HDMI_ALCR_reg(data)                                       (*((volatile unsigned int*)HDMI_ALCR_reg)=data)
#define get_HDMI_ALCR_reg                                             (*((volatile unsigned int*)HDMI_ALCR_reg))
#define HDMI_ALCR_lo1_shift                                           (6)
#define HDMI_ALCR_lo2_shift                                           (4)
#define HDMI_ALCR_lo3_shift                                           (2)
#define HDMI_ALCR_lo4_shift                                           (0)
#define HDMI_ALCR_lo1_mask                                            (0x000000C0)
#define HDMI_ALCR_lo2_mask                                            (0x00000030)
#define HDMI_ALCR_lo3_mask                                            (0x0000000C)
#define HDMI_ALCR_lo4_mask                                            (0x00000003)
#define HDMI_ALCR_lo1(data)                                           (0x000000C0&((data)<<6))
#define HDMI_ALCR_lo2(data)                                           (0x00000030&((data)<<4))
#define HDMI_ALCR_lo3(data)                                           (0x0000000C&((data)<<2))
#define HDMI_ALCR_lo4(data)                                           (0x00000003&(data))
#define HDMI_ALCR_get_lo1(data)                                       ((0x000000C0&(data))>>6)
#define HDMI_ALCR_get_lo2(data)                                       ((0x00000030&(data))>>4)
#define HDMI_ALCR_get_lo3(data)                                       ((0x0000000C&(data))>>2)
#define HDMI_ALCR_get_lo4(data)                                       (0x00000003&(data))


#define HDMI_AOCR                                                     0x0dc
#define HDMI_AOCR_reg_addr                                            "0x980340dc"
#define HDMI_AOCR_reg                                                 0x980340dc
#define HDMI_AOCR_inst_addr                                           "0x0037"
#define HDMI_AOCR_inst                                                0x0037
#define set_HDMI_AOCR_reg(data)                                       (*((volatile unsigned int*)HDMI_AOCR_reg)=data)
#define get_HDMI_AOCR_reg                                             (*((volatile unsigned int*)HDMI_AOCR_reg))
#define HDMI_AOCR_i2s_clk_en_dvi_shift                                (8)
#define HDMI_AOCR_spdifo1_shift                                       (7)
#define HDMI_AOCR_spdifo2_shift                                       (6)
#define HDMI_AOCR_spdifo3_shift                                       (5)
#define HDMI_AOCR_spdifo4_shift                                       (4)
#define HDMI_AOCR_i2so1_shift                                         (3)
#define HDMI_AOCR_i2so2_shift                                         (2)
#define HDMI_AOCR_i2so3_shift                                         (1)
#define HDMI_AOCR_i2so4_shift                                         (0)
#define HDMI_AOCR_i2s_clk_en_dvi_mask                                 (0x00000100)
#define HDMI_AOCR_spdifo1_mask                                        (0x00000080)
#define HDMI_AOCR_spdifo2_mask                                        (0x00000040)
#define HDMI_AOCR_spdifo3_mask                                        (0x00000020)
#define HDMI_AOCR_spdifo4_mask                                        (0x00000010)
#define HDMI_AOCR_i2so1_mask                                          (0x00000008)
#define HDMI_AOCR_i2so2_mask                                          (0x00000004)
#define HDMI_AOCR_i2so3_mask                                          (0x00000002)
#define HDMI_AOCR_i2so4_mask                                          (0x00000001)
#define HDMI_AOCR_i2s_clk_en_dvi(data)                                (0x00000100&((data)<<8))
#define HDMI_AOCR_spdifo1(data)                                       (0x00000080&((data)<<7))
#define HDMI_AOCR_spdifo2(data)                                       (0x00000040&((data)<<6))
#define HDMI_AOCR_spdifo3(data)                                       (0x00000020&((data)<<5))
#define HDMI_AOCR_spdifo4(data)                                       (0x00000010&((data)<<4))
#define HDMI_AOCR_i2so1(data)                                         (0x00000008&((data)<<3))
#define HDMI_AOCR_i2so2(data)                                         (0x00000004&((data)<<2))
#define HDMI_AOCR_i2so3(data)                                         (0x00000002&((data)<<1))
#define HDMI_AOCR_i2so4(data)                                         (0x00000001&(data))
#define HDMI_AOCR_get_i2s_clk_en_dvi(data)                            ((0x00000100&(data))>>8)
#define HDMI_AOCR_get_spdifo1(data)                                   ((0x00000080&(data))>>7)
#define HDMI_AOCR_get_spdifo2(data)                                   ((0x00000040&(data))>>6)
#define HDMI_AOCR_get_spdifo3(data)                                   ((0x00000020&(data))>>5)
#define HDMI_AOCR_get_spdifo4(data)                                   ((0x00000010&(data))>>4)
#define HDMI_AOCR_get_i2so1(data)                                     ((0x00000008&(data))>>3)
#define HDMI_AOCR_get_i2so2(data)                                     ((0x00000004&(data))>>2)
#define HDMI_AOCR_get_i2so3(data)                                     ((0x00000002&(data))>>1)
#define HDMI_AOCR_get_i2so4(data)                                     (0x00000001&(data))


#define HDMI_BCSR                                                     0x0e0
#define HDMI_BCSR_reg_addr                                            "0x980340e0"
#define HDMI_BCSR_reg                                                 0x980340e0
#define HDMI_BCSR_inst_addr                                           "0x0038"
#define HDMI_BCSR_inst                                                0x0038
#define set_HDMI_BCSR_reg(data)                                       (*((volatile unsigned int*)HDMI_BCSR_reg)=data)
#define get_HDMI_BCSR_reg                                             (*((volatile unsigned int*)HDMI_BCSR_reg))
#define HDMI_BCSR_nvlgb_shift                                         (5)
#define HDMI_BCSR_nalgb_shift                                         (4)
#define HDMI_BCSR_natgb_shift                                         (3)
#define HDMI_BCSR_ngb_shift                                           (2)
#define HDMI_BCSR_pe_shift                                            (1)
#define HDMI_BCSR_gcp_shift                                           (0)
#define HDMI_BCSR_nvlgb_mask                                          (0x00000020)
#define HDMI_BCSR_nalgb_mask                                          (0x00000010)
#define HDMI_BCSR_natgb_mask                                          (0x00000008)
#define HDMI_BCSR_ngb_mask                                            (0x00000004)
#define HDMI_BCSR_pe_mask                                             (0x00000002)
#define HDMI_BCSR_gcp_mask                                            (0x00000001)
#define HDMI_BCSR_nvlgb(data)                                         (0x00000020&((data)<<5))
#define HDMI_BCSR_nalgb(data)                                         (0x00000010&((data)<<4))
#define HDMI_BCSR_natgb(data)                                         (0x00000008&((data)<<3))
#define HDMI_BCSR_ngb(data)                                           (0x00000004&((data)<<2))
#define HDMI_BCSR_pe(data)                                            (0x00000002&((data)<<1))
#define HDMI_BCSR_gcp(data)                                           (0x00000001&(data))
#define HDMI_BCSR_get_nvlgb(data)                                     ((0x00000020&(data))>>5)
#define HDMI_BCSR_get_nalgb(data)                                     ((0x00000010&(data))>>4)
#define HDMI_BCSR_get_natgb(data)                                     ((0x00000008&(data))>>3)
#define HDMI_BCSR_get_ngb(data)                                       ((0x00000004&(data))>>2)
#define HDMI_BCSR_get_pe(data)                                        ((0x00000002&(data))>>1)
#define HDMI_BCSR_get_gcp(data)                                       (0x00000001&(data))


#define HDMI_ASR0                                                     0x0e4
#define HDMI_ASR0_reg_addr                                            "0x980340e4"
#define HDMI_ASR0_reg                                                 0x980340e4
#define HDMI_ASR0_inst_addr                                           "0x0039"
#define HDMI_ASR0_inst                                                0x0039
#define set_HDMI_ASR0_reg(data)                                       (*((volatile unsigned int*)HDMI_ASR0_reg)=data)
#define get_HDMI_ASR0_reg                                             (*((volatile unsigned int*)HDMI_ASR0_reg))
#define HDMI_ASR0_fsre_shift                                          (2)
#define HDMI_ASR0_fsif_shift                                          (1)
#define HDMI_ASR0_fscs_shift                                          (0)
#define HDMI_ASR0_fsre_mask                                           (0x00000004)
#define HDMI_ASR0_fsif_mask                                           (0x00000002)
#define HDMI_ASR0_fscs_mask                                           (0x00000001)
#define HDMI_ASR0_fsre(data)                                          (0x00000004&((data)<<2))
#define HDMI_ASR0_fsif(data)                                          (0x00000002&((data)<<1))
#define HDMI_ASR0_fscs(data)                                          (0x00000001&(data))
#define HDMI_ASR0_get_fsre(data)                                      ((0x00000004&(data))>>2)
#define HDMI_ASR0_get_fsif(data)                                      ((0x00000002&(data))>>1)
#define HDMI_ASR0_get_fscs(data)                                      (0x00000001&(data))


#define HDMI_ASR1                                                     0x0e8
#define HDMI_ASR1_reg_addr                                            "0x980340e8"
#define HDMI_ASR1_reg                                                 0x980340e8
#define HDMI_ASR1_inst_addr                                           "0x003A"
#define HDMI_ASR1_inst                                                0x003A
#define set_HDMI_ASR1_reg(data)                                       (*((volatile unsigned int*)HDMI_ASR1_reg)=data)
#define get_HDMI_ASR1_reg                                             (*((volatile unsigned int*)HDMI_ASR1_reg))
#define HDMI_ASR1_fbif_shift                                          (4)
#define HDMI_ASR1_fbcs_shift                                          (0)
#define HDMI_ASR1_fbif_mask                                           (0x00000070)
#define HDMI_ASR1_fbcs_mask                                           (0x0000000F)
#define HDMI_ASR1_fbif(data)                                          (0x00000070&((data)<<4))
#define HDMI_ASR1_fbcs(data)                                          (0x0000000F&(data))
#define HDMI_ASR1_get_fbif(data)                                      ((0x00000070&(data))>>4)
#define HDMI_ASR1_get_fbcs(data)                                      (0x0000000F&(data))


#define HDMI_VIDEO_FORMAT                                             0x0ec
#define HDMI_VIDEO_FORMAT_reg_addr                                    "0x980340ec"
#define HDMI_VIDEO_FORMAT_reg                                         0x980340ec
#define HDMI_VIDEO_FORMAT_inst_addr                                   "0x003B"
#define HDMI_VIDEO_FORMAT_inst                                        0x003B
#define set_HDMI_VIDEO_FORMAT_reg(data)                               (*((volatile unsigned int*)HDMI_VIDEO_FORMAT_reg)=data)
#define get_HDMI_VIDEO_FORMAT_reg                                     (*((volatile unsigned int*)HDMI_VIDEO_FORMAT_reg))
#define HDMI_VIDEO_FORMAT_hvf_shift                                   (8)
#define HDMI_VIDEO_FORMAT_hdmi_vic_shift                              (0)
#define HDMI_VIDEO_FORMAT_hvf_mask                                    (0x00000700)
#define HDMI_VIDEO_FORMAT_hdmi_vic_mask                               (0x000000FF)
#define HDMI_VIDEO_FORMAT_hvf(data)                                   (0x00000700&((data)<<8))
#define HDMI_VIDEO_FORMAT_hdmi_vic(data)                              (0x000000FF&(data))
#define HDMI_VIDEO_FORMAT_get_hvf(data)                               ((0x00000700&(data))>>8)
#define HDMI_VIDEO_FORMAT_get_hdmi_vic(data)                          (0x000000FF&(data))


#define HDMI_3D_FORMAT                                                0x0f0
#define HDMI_3D_FORMAT_reg_addr                                       "0x980340f0"
#define HDMI_3D_FORMAT_reg                                            0x980340f0
#define HDMI_3D_FORMAT_inst_addr                                      "0x003C"
#define HDMI_3D_FORMAT_inst                                           0x003C
#define set_HDMI_3D_FORMAT_reg(data)                                  (*((volatile unsigned int*)HDMI_3D_FORMAT_reg)=data)
#define get_HDMI_3D_FORMAT_reg                                        (*((volatile unsigned int*)HDMI_3D_FORMAT_reg))
#define HDMI_3D_FORMAT_hdmi_3d_ext_data_shift                         (12)
#define HDMI_3D_FORMAT_hdmi_3d_metadata_type_shift                    (9)
#define HDMI_3D_FORMAT_hdmi_3d_structure_shift                        (4)
#define HDMI_3D_FORMAT_hdmi_3d_meta_present_shift                     (3)
#define HDMI_3D_FORMAT_hdmi_3d_ext_data_mask                          (0x0000F000)
#define HDMI_3D_FORMAT_hdmi_3d_metadata_type_mask                     (0x00000E00)
#define HDMI_3D_FORMAT_hdmi_3d_structure_mask                         (0x000000F0)
#define HDMI_3D_FORMAT_hdmi_3d_meta_present_mask                      (0x00000008)
#define HDMI_3D_FORMAT_hdmi_3d_ext_data(data)                         (0x0000F000&((data)<<12))
#define HDMI_3D_FORMAT_hdmi_3d_metadata_type(data)                    (0x00000E00&((data)<<9))
#define HDMI_3D_FORMAT_hdmi_3d_structure(data)                        (0x000000F0&((data)<<4))
#define HDMI_3D_FORMAT_hdmi_3d_meta_present(data)                     (0x00000008&((data)<<3))
#define HDMI_3D_FORMAT_get_hdmi_3d_ext_data(data)                     ((0x0000F000&(data))>>12)
#define HDMI_3D_FORMAT_get_hdmi_3d_metadata_type(data)                ((0x00000E00&(data))>>9)
#define HDMI_3D_FORMAT_get_hdmi_3d_structure(data)                    ((0x000000F0&(data))>>4)
#define HDMI_3D_FORMAT_get_hdmi_3d_meta_present(data)                 ((0x00000008&(data))>>3)


#define HDMI_FVSI                                                     0x0f4
#define HDMI_FVSI_reg_addr                                            "0x980340f4"
#define HDMI_FVSI_reg                                                 0x980340f4
#define HDMI_FVSI_inst_addr                                           "0x003D"
#define HDMI_FVSI_inst                                                0x003D
#define set_HDMI_FVSI_reg(data)                                       (*((volatile unsigned int*)HDMI_FVSI_reg)=data)
#define get_HDMI_FVSI_reg                                             (*((volatile unsigned int*)HDMI_FVSI_reg))
#define HDMI_FVSI_info_3d_preferred2dview_shift                       (13)
#define HDMI_FVSI_info_3d_viewdependency_shift                        (11)
#define HDMI_FVSI_info_3d_dualview_shift                              (10)
#define HDMI_FVSI_info_3d_additionalinfo_present_shift                (9)
#define HDMI_FVSI_info_3d_f_ext_data_shift                            (5)
#define HDMI_FVSI_info_3d_f_structure_shift                           (1)
#define HDMI_FVSI_info_3d_valid_shift                                 (0)
#define HDMI_FVSI_info_3d_preferred2dview_mask                        (0x00006000)
#define HDMI_FVSI_info_3d_viewdependency_mask                         (0x00001800)
#define HDMI_FVSI_info_3d_dualview_mask                               (0x00000400)
#define HDMI_FVSI_info_3d_additionalinfo_present_mask                 (0x00000200)
#define HDMI_FVSI_info_3d_f_ext_data_mask                             (0x000001E0)
#define HDMI_FVSI_info_3d_f_structure_mask                            (0x0000001E)
#define HDMI_FVSI_info_3d_valid_mask                                  (0x00000001)
#define HDMI_FVSI_info_3d_preferred2dview(data)                       (0x00006000&((data)<<13))
#define HDMI_FVSI_info_3d_viewdependency(data)                        (0x00001800&((data)<<11))
#define HDMI_FVSI_info_3d_dualview(data)                              (0x00000400&((data)<<10))
#define HDMI_FVSI_info_3d_additionalinfo_present(data)                (0x00000200&((data)<<9))
#define HDMI_FVSI_info_3d_f_ext_data(data)                            (0x000001E0&((data)<<5))
#define HDMI_FVSI_info_3d_f_structure(data)                           (0x0000001E&((data)<<1))
#define HDMI_FVSI_info_3d_valid(data)                                 (0x00000001&(data))
#define HDMI_FVSI_get_info_3d_preferred2dview(data)                   ((0x00006000&(data))>>13)
#define HDMI_FVSI_get_info_3d_viewdependency(data)                    ((0x00001800&(data))>>11)
#define HDMI_FVSI_get_info_3d_dualview(data)                          ((0x00000400&(data))>>10)
#define HDMI_FVSI_get_info_3d_additionalinfo_present(data)            ((0x00000200&(data))>>9)
#define HDMI_FVSI_get_info_3d_f_ext_data(data)                        ((0x000001E0&(data))>>5)
#define HDMI_FVSI_get_info_3d_f_structure(data)                       ((0x0000001E&(data))>>1)
#define HDMI_FVSI_get_info_3d_valid(data)                             (0x00000001&(data))


#define CH_CR                                                         0x0f8
#define CH_CR_reg_addr                                                "0x980340f8"
#define CH_CR_reg                                                     0x980340f8
#define CH_CR_inst_addr                                               "0x003E"
#define CH_CR_inst                                                    0x003E
#define set_CH_CR_reg(data)                                           (*((volatile unsigned int*)CH_CR_reg)=data)
#define get_CH_CR_reg                                                 (*((volatile unsigned int*)CH_CR_reg))
#define CH_CR_r_ch_afifo_en_shift                                     (24)
#define CH_CR_g_ch_afifo_en_shift                                     (23)
#define CH_CR_b_ch_afifo_en_shift                                     (22)
#define CH_CR_ch_sync_sel_shift                                       (20)
#define CH_CR_dummy_19_17_shift                                       (17)
#define CH_CR_rden_thr_shift                                          (12)
#define CH_CR_dummy_11_9_shift                                        (9)
#define CH_CR_udwater_thr_shift                                       (4)
#define CH_CR_dummy_3_2_shift                                         (2)
#define CH_CR_flush_shift                                             (1)
#define CH_CR_ch_afifo_irq_en_shift                                   (0)
#define CH_CR_r_ch_afifo_en_mask                                      (0x01000000)
#define CH_CR_g_ch_afifo_en_mask                                      (0x00800000)
#define CH_CR_b_ch_afifo_en_mask                                      (0x00400000)
#define CH_CR_ch_sync_sel_mask                                        (0x00300000)
#define CH_CR_dummy_19_17_mask                                        (0x000E0000)
#define CH_CR_rden_thr_mask                                           (0x0001F000)
#define CH_CR_dummy_11_9_mask                                         (0x00000E00)
#define CH_CR_udwater_thr_mask                                        (0x000001F0)
#define CH_CR_dummy_3_2_mask                                          (0x0000000C)
#define CH_CR_flush_mask                                              (0x00000002)
#define CH_CR_ch_afifo_irq_en_mask                                    (0x00000001)
#define CH_CR_r_ch_afifo_en(data)                                     (0x01000000&((data)<<24))
#define CH_CR_g_ch_afifo_en(data)                                     (0x00800000&((data)<<23))
#define CH_CR_b_ch_afifo_en(data)                                     (0x00400000&((data)<<22))
#define CH_CR_ch_sync_sel(data)                                       (0x00300000&((data)<<20))
#define CH_CR_dummy_19_17(data)                                       (0x000E0000&((data)<<17))
#define CH_CR_rden_thr(data)                                          (0x0001F000&((data)<<12))
#define CH_CR_dummy_11_9(data)                                        (0x00000E00&((data)<<9))
#define CH_CR_udwater_thr(data)                                       (0x000001F0&((data)<<4))
#define CH_CR_dummy_3_2(data)                                         (0x0000000C&((data)<<2))
#define CH_CR_flush(data)                                             (0x00000002&((data)<<1))
#define CH_CR_ch_afifo_irq_en(data)                                   (0x00000001&(data))
#define CH_CR_get_r_ch_afifo_en(data)                                 ((0x01000000&(data))>>24)
#define CH_CR_get_g_ch_afifo_en(data)                                 ((0x00800000&(data))>>23)
#define CH_CR_get_b_ch_afifo_en(data)                                 ((0x00400000&(data))>>22)
#define CH_CR_get_ch_sync_sel(data)                                   ((0x00300000&(data))>>20)
#define CH_CR_get_dummy_19_17(data)                                   ((0x000E0000&(data))>>17)
#define CH_CR_get_rden_thr(data)                                      ((0x0001F000&(data))>>12)
#define CH_CR_get_dummy_11_9(data)                                    ((0x00000E00&(data))>>9)
#define CH_CR_get_udwater_thr(data)                                   ((0x000001F0&(data))>>4)
#define CH_CR_get_dummy_3_2(data)                                     ((0x0000000C&(data))>>2)
#define CH_CR_get_flush(data)                                         ((0x00000002&(data))>>1)
#define CH_CR_get_ch_afifo_irq_en(data)                               (0x00000001&(data))


#define CH_SR                                                         0x0fc
#define CH_SR_reg_addr                                                "0x980340fc"
#define CH_SR_reg                                                     0x980340fc
#define CH_SR_inst_addr                                               "0x003F"
#define CH_SR_inst                                                    0x003F
#define set_CH_SR_reg(data)                                           (*((volatile unsigned int*)CH_SR_reg)=data)
#define get_CH_SR_reg                                                 (*((volatile unsigned int*)CH_SR_reg))
#define CH_SR_rgb_de_align_flag_shift                                 (30)
#define CH_SR_r_rwclk_det_timeout_flag_shift                          (29)
#define CH_SR_r_wrclk_det_timeout_flag_shift                          (28)
#define CH_SR_g_rwclk_det_timeout_flag_shift                          (27)
#define CH_SR_g_wrclk_det_timeout_flag_shift                          (26)
#define CH_SR_b_rwclk_det_timeout_flag_shift                          (25)
#define CH_SR_b_wrclk_det_timeout_flag_shift                          (24)
#define CH_SR_r_rudflow_flag_shift                                    (23)
#define CH_SR_r_wovflow_flag_shift                                    (22)
#define CH_SR_r_rflush_flag_shift                                     (21)
#define CH_SR_r_rw_water_lv_shift                                     (16)
#define CH_SR_g_rudflow_flag_shift                                    (15)
#define CH_SR_g_wovflow_flag_shift                                    (14)
#define CH_SR_g_rflush_flag_shift                                     (13)
#define CH_SR_g_rw_water_lv_shift                                     (8)
#define CH_SR_b_rudflow_flag_shift                                    (7)
#define CH_SR_b_wovflow_flag_shift                                    (6)
#define CH_SR_b_rflush_flag_shift                                     (5)
#define CH_SR_b_rw_water_lv_shift                                     (0)
#define CH_SR_rgb_de_align_flag_mask                                  (0x40000000)
#define CH_SR_r_rwclk_det_timeout_flag_mask                           (0x20000000)
#define CH_SR_r_wrclk_det_timeout_flag_mask                           (0x10000000)
#define CH_SR_g_rwclk_det_timeout_flag_mask                           (0x08000000)
#define CH_SR_g_wrclk_det_timeout_flag_mask                           (0x04000000)
#define CH_SR_b_rwclk_det_timeout_flag_mask                           (0x02000000)
#define CH_SR_b_wrclk_det_timeout_flag_mask                           (0x01000000)
#define CH_SR_r_rudflow_flag_mask                                     (0x00800000)
#define CH_SR_r_wovflow_flag_mask                                     (0x00400000)
#define CH_SR_r_rflush_flag_mask                                      (0x00200000)
#define CH_SR_r_rw_water_lv_mask                                      (0x001F0000)
#define CH_SR_g_rudflow_flag_mask                                     (0x00008000)
#define CH_SR_g_wovflow_flag_mask                                     (0x00004000)
#define CH_SR_g_rflush_flag_mask                                      (0x00002000)
#define CH_SR_g_rw_water_lv_mask                                      (0x00001F00)
#define CH_SR_b_rudflow_flag_mask                                     (0x00000080)
#define CH_SR_b_wovflow_flag_mask                                     (0x00000040)
#define CH_SR_b_rflush_flag_mask                                      (0x00000020)
#define CH_SR_b_rw_water_lv_mask                                      (0x0000001F)
#define CH_SR_rgb_de_align_flag(data)                                 (0x40000000&((data)<<30))
#define CH_SR_r_rwclk_det_timeout_flag(data)                          (0x20000000&((data)<<29))
#define CH_SR_r_wrclk_det_timeout_flag(data)                          (0x10000000&((data)<<28))
#define CH_SR_g_rwclk_det_timeout_flag(data)                          (0x08000000&((data)<<27))
#define CH_SR_g_wrclk_det_timeout_flag(data)                          (0x04000000&((data)<<26))
#define CH_SR_b_rwclk_det_timeout_flag(data)                          (0x02000000&((data)<<25))
#define CH_SR_b_wrclk_det_timeout_flag(data)                          (0x01000000&((data)<<24))
#define CH_SR_r_rudflow_flag(data)                                    (0x00800000&((data)<<23))
#define CH_SR_r_wovflow_flag(data)                                    (0x00400000&((data)<<22))
#define CH_SR_r_rflush_flag(data)                                     (0x00200000&((data)<<21))
#define CH_SR_r_rw_water_lv(data)                                     (0x001F0000&((data)<<16))
#define CH_SR_g_rudflow_flag(data)                                    (0x00008000&((data)<<15))
#define CH_SR_g_wovflow_flag(data)                                    (0x00004000&((data)<<14))
#define CH_SR_g_rflush_flag(data)                                     (0x00002000&((data)<<13))
#define CH_SR_g_rw_water_lv(data)                                     (0x00001F00&((data)<<8))
#define CH_SR_b_rudflow_flag(data)                                    (0x00000080&((data)<<7))
#define CH_SR_b_wovflow_flag(data)                                    (0x00000040&((data)<<6))
#define CH_SR_b_rflush_flag(data)                                     (0x00000020&((data)<<5))
#define CH_SR_b_rw_water_lv(data)                                     (0x0000001F&(data))
#define CH_SR_get_rgb_de_align_flag(data)                             ((0x40000000&(data))>>30)
#define CH_SR_get_r_rwclk_det_timeout_flag(data)                      ((0x20000000&(data))>>29)
#define CH_SR_get_r_wrclk_det_timeout_flag(data)                      ((0x10000000&(data))>>28)
#define CH_SR_get_g_rwclk_det_timeout_flag(data)                      ((0x08000000&(data))>>27)
#define CH_SR_get_g_wrclk_det_timeout_flag(data)                      ((0x04000000&(data))>>26)
#define CH_SR_get_b_rwclk_det_timeout_flag(data)                      ((0x02000000&(data))>>25)
#define CH_SR_get_b_wrclk_det_timeout_flag(data)                      ((0x01000000&(data))>>24)
#define CH_SR_get_r_rudflow_flag(data)                                ((0x00800000&(data))>>23)
#define CH_SR_get_r_wovflow_flag(data)                                ((0x00400000&(data))>>22)
#define CH_SR_get_r_rflush_flag(data)                                 ((0x00200000&(data))>>21)
#define CH_SR_get_r_rw_water_lv(data)                                 ((0x001F0000&(data))>>16)
#define CH_SR_get_g_rudflow_flag(data)                                ((0x00008000&(data))>>15)
#define CH_SR_get_g_wovflow_flag(data)                                ((0x00004000&(data))>>14)
#define CH_SR_get_g_rflush_flag(data)                                 ((0x00002000&(data))>>13)
#define CH_SR_get_g_rw_water_lv(data)                                 ((0x00001F00&(data))>>8)
#define CH_SR_get_b_rudflow_flag(data)                                ((0x00000080&(data))>>7)
#define CH_SR_get_b_wovflow_flag(data)                                ((0x00000040&(data))>>6)
#define CH_SR_get_b_rflush_flag(data)                                 ((0x00000020&(data))>>5)
#define CH_SR_get_b_rw_water_lv(data)                                 (0x0000001F&(data))


#define AUDIO_SAMPLE_RATE_CHANGE_IRQ                                  0x100
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_reg_addr                         "0x98034100"
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_reg                              0x98034100
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_inst_addr                        "0x0040"
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_inst                             0x0040
#define set_AUDIO_SAMPLE_RATE_CHANGE_IRQ_reg(data)                    (*((volatile unsigned int*)AUDIO_SAMPLE_RATE_CHANGE_IRQ_reg)=data)
#define get_AUDIO_SAMPLE_RATE_CHANGE_IRQ_reg                          (*((volatile unsigned int*)AUDIO_SAMPLE_RATE_CHANGE_IRQ_reg))
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_en_ncts_chg_irq_shift            (3)
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_ncts_chg_irq_shift               (2)
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_en_ch_status_chg_irq_shift       (1)
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_ch_status_chg_irq_shift          (0)
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_en_ncts_chg_irq_mask             (0x00000008)
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_ncts_chg_irq_mask                (0x00000004)
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_en_ch_status_chg_irq_mask        (0x00000002)
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_ch_status_chg_irq_mask           (0x00000001)
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_en_ncts_chg_irq(data)            (0x00000008&((data)<<3))
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_ncts_chg_irq(data)               (0x00000004&((data)<<2))
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_en_ch_status_chg_irq(data)       (0x00000002&((data)<<1))
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_ch_status_chg_irq(data)          (0x00000001&(data))
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_get_en_ncts_chg_irq(data)        ((0x00000008&(data))>>3)
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_get_ncts_chg_irq(data)           ((0x00000004&(data))>>2)
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_get_en_ch_status_chg_irq(data)   ((0x00000002&(data))>>1)
#define AUDIO_SAMPLE_RATE_CHANGE_IRQ_get_ch_status_chg_irq(data)      (0x00000001&(data))


#define HIGH_BIT_RATE_AUDIO_PACKET                                    0x104
#define HIGH_BIT_RATE_AUDIO_PACKET_reg_addr                           "0x98034104"
#define HIGH_BIT_RATE_AUDIO_PACKET_reg                                0x98034104
#define HIGH_BIT_RATE_AUDIO_PACKET_inst_addr                          "0x0041"
#define HIGH_BIT_RATE_AUDIO_PACKET_inst                               0x0041
#define set_HIGH_BIT_RATE_AUDIO_PACKET_reg(data)                      (*((volatile unsigned int*)HIGH_BIT_RATE_AUDIO_PACKET_reg)=data)
#define get_HIGH_BIT_RATE_AUDIO_PACKET_reg                            (*((volatile unsigned int*)HIGH_BIT_RATE_AUDIO_PACKET_reg))
#define HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_manual_shift        (2)
#define HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_fw_shift            (1)
#define HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_shift               (0)
#define HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_manual_mask         (0x00000004)
#define HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_fw_mask             (0x00000002)
#define HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_mask                (0x00000001)
#define HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_manual(data)        (0x00000004&((data)<<2))
#define HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_fw(data)            (0x00000002&((data)<<1))
#define HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode(data)               (0x00000001&(data))
#define HIGH_BIT_RATE_AUDIO_PACKET_get_hbr_audio_mode_manual(data)    ((0x00000004&(data))>>2)
#define HIGH_BIT_RATE_AUDIO_PACKET_get_hbr_audio_mode_fw(data)        ((0x00000002&(data))>>1)
#define HIGH_BIT_RATE_AUDIO_PACKET_get_hbr_audio_mode(data)           (0x00000001&(data))


#define HDMI_AFCR                                                     0x108
#define HDMI_AFCR_reg_addr                                            "0x98034108"
#define HDMI_AFCR_reg                                                 0x98034108
#define HDMI_AFCR_inst_addr                                           "0x0042"
#define HDMI_AFCR_inst                                                0x0042
#define set_HDMI_AFCR_reg(data)                                       (*((volatile unsigned int*)HDMI_AFCR_reg)=data)
#define get_HDMI_AFCR_reg                                             (*((volatile unsigned int*)HDMI_AFCR_reg))
#define HDMI_AFCR_dummy_31_14_shift                                   (14)
#define HDMI_AFCR_gain_bypass_en_shift                                (13)
#define HDMI_AFCR_afifof_shift                                        (12)
#define HDMI_AFCR_afifoe_shift                                        (11)
#define HDMI_AFCR_afifowe_r_shift                                     (10)
#define HDMI_AFCR_afifore_r_shift                                     (8)
#define HDMI_AFCR_tst_i2s_sw_shift                                    (7)
#define HDMI_AFCR_aoem_shift                                          (6)
#define HDMI_AFCR_aoc_shift                                           (5)
#define HDMI_AFCR_audio_test_enable_shift                             (4)
#define HDMI_AFCR_mgc_shift                                           (3)
#define HDMI_AFCR_afifowe_shift                                       (2)
#define HDMI_AFCR_afifore_shift                                       (0)
#define HDMI_AFCR_dummy_31_14_mask                                    (0xFFFFC000)
#define HDMI_AFCR_gain_bypass_en_mask                                 (0x00002000)
#define HDMI_AFCR_afifof_mask                                         (0x00001000)
#define HDMI_AFCR_afifoe_mask                                         (0x00000800)
#define HDMI_AFCR_afifowe_r_mask                                      (0x00000400)
#define HDMI_AFCR_afifore_r_mask                                      (0x00000300)
#define HDMI_AFCR_tst_i2s_sw_mask                                     (0x00000080)
#define HDMI_AFCR_aoem_mask                                           (0x00000040)
#define HDMI_AFCR_aoc_mask                                            (0x00000020)
#define HDMI_AFCR_audio_test_enable_mask                              (0x00000010)
#define HDMI_AFCR_mgc_mask                                            (0x00000008)
#define HDMI_AFCR_afifowe_mask                                        (0x00000004)
#define HDMI_AFCR_afifore_mask                                        (0x00000003)
#define HDMI_AFCR_dummy_31_14(data)                                   (0xFFFFC000&((data)<<14))
#define HDMI_AFCR_gain_bypass_en(data)                                (0x00002000&((data)<<13))
#define HDMI_AFCR_afifof(data)                                        (0x00001000&((data)<<12))
#define HDMI_AFCR_afifoe(data)                                        (0x00000800&((data)<<11))
#define HDMI_AFCR_afifowe_r(data)                                     (0x00000400&((data)<<10))
#define HDMI_AFCR_afifore_r(data)                                     (0x00000300&((data)<<8))
#define HDMI_AFCR_tst_i2s_sw(data)                                    (0x00000080&((data)<<7))
#define HDMI_AFCR_aoem(data)                                          (0x00000040&((data)<<6))
#define HDMI_AFCR_aoc(data)                                           (0x00000020&((data)<<5))
#define HDMI_AFCR_audio_test_enable(data)                             (0x00000010&((data)<<4))
#define HDMI_AFCR_mgc(data)                                           (0x00000008&((data)<<3))
#define HDMI_AFCR_afifowe(data)                                       (0x00000004&((data)<<2))
#define HDMI_AFCR_afifore(data)                                       (0x00000003&(data))
#define HDMI_AFCR_get_dummy_31_14(data)                               ((0xFFFFC000&(data))>>14)
#define HDMI_AFCR_get_gain_bypass_en(data)                            ((0x00002000&(data))>>13)
#define HDMI_AFCR_get_afifof(data)                                    ((0x00001000&(data))>>12)
#define HDMI_AFCR_get_afifoe(data)                                    ((0x00000800&(data))>>11)
#define HDMI_AFCR_get_afifowe_r(data)                                 ((0x00000400&(data))>>10)
#define HDMI_AFCR_get_afifore_r(data)                                 ((0x00000300&(data))>>8)
#define HDMI_AFCR_get_tst_i2s_sw(data)                                ((0x00000080&(data))>>7)
#define HDMI_AFCR_get_aoem(data)                                      ((0x00000040&(data))>>6)
#define HDMI_AFCR_get_aoc(data)                                       ((0x00000020&(data))>>5)
#define HDMI_AFCR_get_audio_test_enable(data)                         ((0x00000010&(data))>>4)
#define HDMI_AFCR_get_mgc(data)                                       ((0x00000008&(data))>>3)
#define HDMI_AFCR_get_afifowe(data)                                   ((0x00000004&(data))>>2)
#define HDMI_AFCR_get_afifore(data)                                   (0x00000003&(data))
//For SW function
#define MHL_CTS_TEST_ON												_BIT31
#define MHL_CTS_TEST_PP_MODE										_BIT30
#define MHL_HDMI_SETPHY_BYPASS										_BIT29
#define MHL_HDMI_PHY_BYPASS											_BIT28
#define MHL_HDMI_Bit_Error_check									_BIT27
#define MHL3_RUN_6G													(_BIT26)
#define MHL3_RUN_3G													(_BIT25)
#define MHL3_RUN_1p5G												(_BIT25|_BIT26)
#define MHL3_RUN_16bit												(_BIT24)  /*_BIT24=1: 16bit; _BIT24=0: 24bit */
#define MHL3_BYPASS_CBUS_CLK										(_BIT23)
#define HDMI_6G_TEST												(_BIT22)
#define HDMI_Force_3G												(_BIT21)


#define HDMI_AFSR                                                     0x10c
#define HDMI_AFSR_reg_addr                                            "0x9803410c"
#define HDMI_AFSR_reg                                                 0x9803410c
#define HDMI_AFSR_inst_addr                                           "0x0043"
#define HDMI_AFSR_inst                                                0x0043
#define set_HDMI_AFSR_reg(data)                                       (*((volatile unsigned int*)HDMI_AFSR_reg)=data)
#define get_HDMI_AFSR_reg                                             (*((volatile unsigned int*)HDMI_AFSR_reg))
#define HDMI_AFSR_audio_bist_clksel_shift                             (0)
#define HDMI_AFSR_audio_bist_clksel_mask                              (0x00000001)
#define HDMI_AFSR_audio_bist_clksel(data)                             (0x00000001&(data))
#define HDMI_AFSR_get_audio_bist_clksel(data)                         (0x00000001&(data))


#define HDMI_MAGCR0                                                   0x110
#define HDMI_MAGCR0_reg_addr                                          "0x98034110"
#define HDMI_MAGCR0_reg                                               0x98034110
#define HDMI_MAGCR0_inst_addr                                         "0x0044"
#define HDMI_MAGCR0_inst                                              0x0044
#define set_HDMI_MAGCR0_reg(data)                                     (*((volatile unsigned int*)HDMI_MAGCR0_reg)=data)
#define get_HDMI_MAGCR0_reg                                           (*((volatile unsigned int*)HDMI_MAGCR0_reg))
#define HDMI_MAGCR0_agi_shift                                         (13)
#define HDMI_MAGCR0_agd_shift                                         (8)
#define HDMI_MAGCR0_mg_shift                                          (0)
#define HDMI_MAGCR0_agi_mask                                          (0x0000E000)
#define HDMI_MAGCR0_agd_mask                                          (0x00001F00)
#define HDMI_MAGCR0_mg_mask                                           (0x000000FF)
#define HDMI_MAGCR0_agi(data)                                         (0x0000E000&((data)<<13))
#define HDMI_MAGCR0_agd(data)                                         (0x00001F00&((data)<<8))
#define HDMI_MAGCR0_mg(data)                                          (0x000000FF&(data))
#define HDMI_MAGCR0_get_agi(data)                                     ((0x0000E000&(data))>>13)
#define HDMI_MAGCR0_get_agd(data)                                     ((0x00001F00&(data))>>8)
#define HDMI_MAGCR0_get_mg(data)                                      (0x000000FF&(data))


#define HDMI_MAG_M_FINAL                                              0x114
#define HDMI_MAG_M_FINAL_reg_addr                                     "0x98034114"
#define HDMI_MAG_M_FINAL_reg                                          0x98034114
#define HDMI_MAG_M_FINAL_inst_addr                                    "0x0045"
#define HDMI_MAG_M_FINAL_inst                                         0x0045
#define set_HDMI_MAG_M_FINAL_reg(data)                                (*((volatile unsigned int*)HDMI_MAG_M_FINAL_reg)=data)
#define get_HDMI_MAG_M_FINAL_reg                                      (*((volatile unsigned int*)HDMI_MAG_M_FINAL_reg))
#define HDMI_MAG_M_FINAL_ldp_time_shift                               (21)
#define HDMI_MAG_M_FINAL_ldp_time_mode_shift                          (20)
#define HDMI_MAG_M_FINAL_fg_r_shift                                   (12)
#define HDMI_MAG_M_FINAL_fg_l_shift                                   (4)
#define HDMI_MAG_M_FINAL_auto_dly_mod_shift                           (3)
#define HDMI_MAG_M_FINAL_fg_en_shift                                  (2)
#define HDMI_MAG_M_FINAL_ffg_l_shift                                  (1)
#define HDMI_MAG_M_FINAL_ffg_r_shift                                  (0)
#define HDMI_MAG_M_FINAL_ldp_time_mask                                (0x7FE00000)
#define HDMI_MAG_M_FINAL_ldp_time_mode_mask                           (0x00100000)
#define HDMI_MAG_M_FINAL_fg_r_mask                                    (0x000FF000)
#define HDMI_MAG_M_FINAL_fg_l_mask                                    (0x00000FF0)
#define HDMI_MAG_M_FINAL_auto_dly_mod_mask                            (0x00000008)
#define HDMI_MAG_M_FINAL_fg_en_mask                                   (0x00000004)
#define HDMI_MAG_M_FINAL_ffg_l_mask                                   (0x00000002)
#define HDMI_MAG_M_FINAL_ffg_r_mask                                   (0x00000001)
#define HDMI_MAG_M_FINAL_ldp_time(data)                               (0x7FE00000&((data)<<21))
#define HDMI_MAG_M_FINAL_ldp_time_mode(data)                          (0x00100000&((data)<<20))
#define HDMI_MAG_M_FINAL_fg_r(data)                                   (0x000FF000&((data)<<12))
#define HDMI_MAG_M_FINAL_fg_l(data)                                   (0x00000FF0&((data)<<4))
#define HDMI_MAG_M_FINAL_auto_dly_mod(data)                           (0x00000008&((data)<<3))
#define HDMI_MAG_M_FINAL_fg_en(data)                                  (0x00000004&((data)<<2))
#define HDMI_MAG_M_FINAL_ffg_l(data)                                  (0x00000002&((data)<<1))
#define HDMI_MAG_M_FINAL_ffg_r(data)                                  (0x00000001&(data))
#define HDMI_MAG_M_FINAL_get_ldp_time(data)                           ((0x7FE00000&(data))>>21)
#define HDMI_MAG_M_FINAL_get_ldp_time_mode(data)                      ((0x00100000&(data))>>20)
#define HDMI_MAG_M_FINAL_get_fg_r(data)                               ((0x000FF000&(data))>>12)
#define HDMI_MAG_M_FINAL_get_fg_l(data)                               ((0x00000FF0&(data))>>4)
#define HDMI_MAG_M_FINAL_get_auto_dly_mod(data)                       ((0x00000008&(data))>>3)
#define HDMI_MAG_M_FINAL_get_fg_en(data)                              ((0x00000004&(data))>>2)
#define HDMI_MAG_M_FINAL_get_ffg_l(data)                              ((0x00000002&(data))>>1)
#define HDMI_MAG_M_FINAL_get_ffg_r(data)                              (0x00000001&(data))


#define ZCD_CTRL                                                      0x118
#define ZCD_CTRL_reg_addr                                             "0x98034118"
#define ZCD_CTRL_reg                                                  0x98034118
#define ZCD_CTRL_inst_addr                                            "0x0046"
#define ZCD_CTRL_inst                                                 0x0046
#define set_ZCD_CTRL_reg(data)                                        (*((volatile unsigned int*)ZCD_CTRL_reg)=data)
#define get_ZCD_CTRL_reg                                              (*((volatile unsigned int*)ZCD_CTRL_reg))
#define ZCD_CTRL_zcd_ch7_done_shift                                   (23)
#define ZCD_CTRL_zcd_ch6_done_shift                                   (22)
#define ZCD_CTRL_zcd_ch5_done_shift                                   (21)
#define ZCD_CTRL_zcd_ch4_done_shift                                   (20)
#define ZCD_CTRL_zcd_ch3_done_shift                                   (19)
#define ZCD_CTRL_zcd_ch2_done_shift                                   (18)
#define ZCD_CTRL_zcd_ch1_done_shift                                   (17)
#define ZCD_CTRL_zcd_ch0_done_shift                                   (16)
#define ZCD_CTRL_zcd_timeout_shift                                    (8)
#define ZCD_CTRL_zcd_en_shift                                         (7)
#define ZCD_CTRL_zcd_sep_8ch_shift                                    (6)
#define ZCD_CTRL_zcd_sep_st_shift                                     (5)
#define ZCD_CTRL_dummy_4_0_shift                                      (0)
#define ZCD_CTRL_zcd_ch7_done_mask                                    (0x00800000)
#define ZCD_CTRL_zcd_ch6_done_mask                                    (0x00400000)
#define ZCD_CTRL_zcd_ch5_done_mask                                    (0x00200000)
#define ZCD_CTRL_zcd_ch4_done_mask                                    (0x00100000)
#define ZCD_CTRL_zcd_ch3_done_mask                                    (0x00080000)
#define ZCD_CTRL_zcd_ch2_done_mask                                    (0x00040000)
#define ZCD_CTRL_zcd_ch1_done_mask                                    (0x00020000)
#define ZCD_CTRL_zcd_ch0_done_mask                                    (0x00010000)
#define ZCD_CTRL_zcd_timeout_mask                                     (0x00007F00)
#define ZCD_CTRL_zcd_en_mask                                          (0x00000080)
#define ZCD_CTRL_zcd_sep_8ch_mask                                     (0x00000040)
#define ZCD_CTRL_zcd_sep_st_mask                                      (0x00000020)
#define ZCD_CTRL_dummy_4_0_mask                                       (0x0000001F)
#define ZCD_CTRL_zcd_ch7_done(data)                                   (0x00800000&((data)<<23))
#define ZCD_CTRL_zcd_ch6_done(data)                                   (0x00400000&((data)<<22))
#define ZCD_CTRL_zcd_ch5_done(data)                                   (0x00200000&((data)<<21))
#define ZCD_CTRL_zcd_ch4_done(data)                                   (0x00100000&((data)<<20))
#define ZCD_CTRL_zcd_ch3_done(data)                                   (0x00080000&((data)<<19))
#define ZCD_CTRL_zcd_ch2_done(data)                                   (0x00040000&((data)<<18))
#define ZCD_CTRL_zcd_ch1_done(data)                                   (0x00020000&((data)<<17))
#define ZCD_CTRL_zcd_ch0_done(data)                                   (0x00010000&((data)<<16))
#define ZCD_CTRL_zcd_timeout(data)                                    (0x00007F00&((data)<<8))
#define ZCD_CTRL_zcd_en(data)                                         (0x00000080&((data)<<7))
#define ZCD_CTRL_zcd_sep_8ch(data)                                    (0x00000040&((data)<<6))
#define ZCD_CTRL_zcd_sep_st(data)                                     (0x00000020&((data)<<5))
#define ZCD_CTRL_dummy_4_0(data)                                      (0x0000001F&(data))
#define ZCD_CTRL_get_zcd_ch7_done(data)                               ((0x00800000&(data))>>23)
#define ZCD_CTRL_get_zcd_ch6_done(data)                               ((0x00400000&(data))>>22)
#define ZCD_CTRL_get_zcd_ch5_done(data)                               ((0x00200000&(data))>>21)
#define ZCD_CTRL_get_zcd_ch4_done(data)                               ((0x00100000&(data))>>20)
#define ZCD_CTRL_get_zcd_ch3_done(data)                               ((0x00080000&(data))>>19)
#define ZCD_CTRL_get_zcd_ch2_done(data)                               ((0x00040000&(data))>>18)
#define ZCD_CTRL_get_zcd_ch1_done(data)                               ((0x00020000&(data))>>17)
#define ZCD_CTRL_get_zcd_ch0_done(data)                               ((0x00010000&(data))>>16)
#define ZCD_CTRL_get_zcd_timeout(data)                                ((0x00007F00&(data))>>8)
#define ZCD_CTRL_get_zcd_en(data)                                     ((0x00000080&(data))>>7)
#define ZCD_CTRL_get_zcd_sep_8ch(data)                                ((0x00000040&(data))>>6)
#define ZCD_CTRL_get_zcd_sep_st(data)                                 ((0x00000020&(data))>>5)
#define ZCD_CTRL_get_dummy_4_0(data)                                  (0x0000001F&(data))


#define AUDIO_FREQDET                                                 0x11c
#define AUDIO_FREQDET_reg_addr                                        "0x9803411c"
#define AUDIO_FREQDET_reg                                             0x9803411c
#define AUDIO_FREQDET_inst_addr                                       "0x0047"
#define AUDIO_FREQDET_inst                                            0x0047
#define set_AUDIO_FREQDET_reg(data)                                   (*((volatile unsigned int*)AUDIO_FREQDET_reg)=data)
#define get_AUDIO_FREQDET_reg                                         (*((volatile unsigned int*)AUDIO_FREQDET_reg))
#define AUDIO_FREQDET_xtal_div_shift                                  (24)
#define AUDIO_FREQDET_afreq_meas_result_shift                         (12)
#define AUDIO_FREQDET_afreq_meas_range_shift                          (9)
#define AUDIO_FREQDET_popup_afreq_meas_result_shift                   (8)
#define AUDIO_FREQDET_audio_freq_detect_shift                         (7)
#define AUDIO_FREQDET_auto_load_scode_shift                           (6)
#define AUDIO_FREQDET_awd_by_freqchange_shift                         (5)
#define AUDIO_FREQDET_awd_by_noaudio_shift                            (4)
#define AUDIO_FREQDET_irq_by_freqchange_shift                         (3)
#define AUDIO_FREQDET_irq_by_noaudio_shift                            (2)
#define AUDIO_FREQDET_freqchange_shift                                (1)
#define AUDIO_FREQDET_noaudio_shift                                   (0)
#define AUDIO_FREQDET_xtal_div_mask                                   (0xFF000000)
#define AUDIO_FREQDET_afreq_meas_result_mask                          (0x00FFF000)
#define AUDIO_FREQDET_afreq_meas_range_mask                           (0x00000E00)
#define AUDIO_FREQDET_popup_afreq_meas_result_mask                    (0x00000100)
#define AUDIO_FREQDET_audio_freq_detect_mask                          (0x00000080)
#define AUDIO_FREQDET_auto_load_scode_mask                            (0x00000040)
#define AUDIO_FREQDET_awd_by_freqchange_mask                          (0x00000020)
#define AUDIO_FREQDET_awd_by_noaudio_mask                             (0x00000010)
#define AUDIO_FREQDET_irq_by_freqchange_mask                          (0x00000008)
#define AUDIO_FREQDET_irq_by_noaudio_mask                             (0x00000004)
#define AUDIO_FREQDET_freqchange_mask                                 (0x00000002)
#define AUDIO_FREQDET_noaudio_mask                                    (0x00000001)
#define AUDIO_FREQDET_xtal_div(data)                                  (0xFF000000&((data)<<24))
#define AUDIO_FREQDET_afreq_meas_result(data)                         (0x00FFF000&((data)<<12))
#define AUDIO_FREQDET_afreq_meas_range(data)                          (0x00000E00&((data)<<9))
#define AUDIO_FREQDET_popup_afreq_meas_result(data)                   (0x00000100&((data)<<8))
#define AUDIO_FREQDET_audio_freq_detect(data)                         (0x00000080&((data)<<7))
#define AUDIO_FREQDET_auto_load_scode(data)                           (0x00000040&((data)<<6))
#define AUDIO_FREQDET_awd_by_freqchange(data)                         (0x00000020&((data)<<5))
#define AUDIO_FREQDET_awd_by_noaudio(data)                            (0x00000010&((data)<<4))
#define AUDIO_FREQDET_irq_by_freqchange(data)                         (0x00000008&((data)<<3))
#define AUDIO_FREQDET_irq_by_noaudio(data)                            (0x00000004&((data)<<2))
#define AUDIO_FREQDET_freqchange(data)                                (0x00000002&((data)<<1))
#define AUDIO_FREQDET_noaudio(data)                                   (0x00000001&(data))
#define AUDIO_FREQDET_get_xtal_div(data)                              ((0xFF000000&(data))>>24)
#define AUDIO_FREQDET_get_afreq_meas_result(data)                     ((0x00FFF000&(data))>>12)
#define AUDIO_FREQDET_get_afreq_meas_range(data)                      ((0x00000E00&(data))>>9)
#define AUDIO_FREQDET_get_popup_afreq_meas_result(data)               ((0x00000100&(data))>>8)
#define AUDIO_FREQDET_get_audio_freq_detect(data)                     ((0x00000080&(data))>>7)
#define AUDIO_FREQDET_get_auto_load_scode(data)                       ((0x00000040&(data))>>6)
#define AUDIO_FREQDET_get_awd_by_freqchange(data)                     ((0x00000020&(data))>>5)
#define AUDIO_FREQDET_get_awd_by_noaudio(data)                        ((0x00000010&(data))>>4)
#define AUDIO_FREQDET_get_irq_by_freqchange(data)                     ((0x00000008&(data))>>3)
#define AUDIO_FREQDET_get_irq_by_noaudio(data)                        ((0x00000004&(data))>>2)
#define AUDIO_FREQDET_get_freqchange(data)                            ((0x00000002&(data))>>1)
#define AUDIO_FREQDET_get_noaudio(data)                               (0x00000001&(data))


#define RANGE0_1                                                      0x120
#define RANGE0_1_reg_addr                                             "0x98034120"
#define RANGE0_1_reg                                                  0x98034120
#define RANGE0_1_inst_addr                                            "0x0048"
#define RANGE0_1_inst                                                 0x0048
#define set_RANGE0_1_reg(data)                                        (*((volatile unsigned int*)RANGE0_1_reg)=data)
#define get_RANGE0_1_reg                                              (*((volatile unsigned int*)RANGE0_1_reg))
#define RANGE0_1_range0_th_shift                                      (12)
#define RANGE0_1_range1_th_shift                                      (0)
#define RANGE0_1_range0_th_mask                                       (0x00FFF000)
#define RANGE0_1_range1_th_mask                                       (0x00000FFF)
#define RANGE0_1_range0_th(data)                                      (0x00FFF000&((data)<<12))
#define RANGE0_1_range1_th(data)                                      (0x00000FFF&(data))
#define RANGE0_1_get_range0_th(data)                                  ((0x00FFF000&(data))>>12)
#define RANGE0_1_get_range1_th(data)                                  (0x00000FFF&(data))


#define RANGE2_3                                                      0x124
#define RANGE2_3_reg_addr                                             "0x98034124"
#define RANGE2_3_reg                                                  0x98034124
#define RANGE2_3_inst_addr                                            "0x0049"
#define RANGE2_3_inst                                                 0x0049
#define set_RANGE2_3_reg(data)                                        (*((volatile unsigned int*)RANGE2_3_reg)=data)
#define get_RANGE2_3_reg                                              (*((volatile unsigned int*)RANGE2_3_reg))
#define RANGE2_3_range2_th_shift                                      (12)
#define RANGE2_3_range3_th_shift                                      (0)
#define RANGE2_3_range2_th_mask                                       (0x00FFF000)
#define RANGE2_3_range3_th_mask                                       (0x00000FFF)
#define RANGE2_3_range2_th(data)                                      (0x00FFF000&((data)<<12))
#define RANGE2_3_range3_th(data)                                      (0x00000FFF&(data))
#define RANGE2_3_get_range2_th(data)                                  ((0x00FFF000&(data))>>12)
#define RANGE2_3_get_range3_th(data)                                  (0x00000FFF&(data))


#define RANGE4_5                                                      0x128
#define RANGE4_5_reg_addr                                             "0x98034128"
#define RANGE4_5_reg                                                  0x98034128
#define RANGE4_5_inst_addr                                            "0x004A"
#define RANGE4_5_inst                                                 0x004A
#define set_RANGE4_5_reg(data)                                        (*((volatile unsigned int*)RANGE4_5_reg)=data)
#define get_RANGE4_5_reg                                              (*((volatile unsigned int*)RANGE4_5_reg))
#define RANGE4_5_range4_th_shift                                      (12)
#define RANGE4_5_range5_th_shift                                      (0)
#define RANGE4_5_range4_th_mask                                       (0x00FFF000)
#define RANGE4_5_range5_th_mask                                       (0x00000FFF)
#define RANGE4_5_range4_th(data)                                      (0x00FFF000&((data)<<12))
#define RANGE4_5_range5_th(data)                                      (0x00000FFF&(data))
#define RANGE4_5_get_range4_th(data)                                  ((0x00FFF000&(data))>>12)
#define RANGE4_5_get_range5_th(data)                                  (0x00000FFF&(data))


#define PRESET_S_CODE0                                                0x12c
#define PRESET_S_CODE0_reg_addr                                       "0x9803412c"
#define PRESET_S_CODE0_reg                                            0x9803412c
#define PRESET_S_CODE0_inst_addr                                      "0x004B"
#define PRESET_S_CODE0_inst                                           0x004B
#define set_PRESET_S_CODE0_reg(data)                                  (*((volatile unsigned int*)PRESET_S_CODE0_reg)=data)
#define get_PRESET_S_CODE0_reg                                        (*((volatile unsigned int*)PRESET_S_CODE0_reg))
#define PRESET_S_CODE0_pre_set_s1_code3_shift                         (31)
#define PRESET_S_CODE0_pre_set_s_code3_shift                          (24)
#define PRESET_S_CODE0_pre_set_s1_code2_shift                         (23)
#define PRESET_S_CODE0_pre_set_s_code2_shift                          (16)
#define PRESET_S_CODE0_pre_set_s1_code1_shift                         (15)
#define PRESET_S_CODE0_pre_set_s_code1_shift                          (8)
#define PRESET_S_CODE0_pre_set_s1_code0_shift                         (7)
#define PRESET_S_CODE0_pre_set_s_code0_shift                          (0)
#define PRESET_S_CODE0_pre_set_s1_code3_mask                          (0x80000000)
#define PRESET_S_CODE0_pre_set_s_code3_mask                           (0x7F000000)
#define PRESET_S_CODE0_pre_set_s1_code2_mask                          (0x00800000)
#define PRESET_S_CODE0_pre_set_s_code2_mask                           (0x007F0000)
#define PRESET_S_CODE0_pre_set_s1_code1_mask                          (0x00008000)
#define PRESET_S_CODE0_pre_set_s_code1_mask                           (0x00007F00)
#define PRESET_S_CODE0_pre_set_s1_code0_mask                          (0x00000080)
#define PRESET_S_CODE0_pre_set_s_code0_mask                           (0x0000007F)
#define PRESET_S_CODE0_pre_set_s1_code3(data)                         (0x80000000&((data)<<31))
#define PRESET_S_CODE0_pre_set_s_code3(data)                          (0x7F000000&((data)<<24))
#define PRESET_S_CODE0_pre_set_s1_code2(data)                         (0x00800000&((data)<<23))
#define PRESET_S_CODE0_pre_set_s_code2(data)                          (0x007F0000&((data)<<16))
#define PRESET_S_CODE0_pre_set_s1_code1(data)                         (0x00008000&((data)<<15))
#define PRESET_S_CODE0_pre_set_s_code1(data)                          (0x00007F00&((data)<<8))
#define PRESET_S_CODE0_pre_set_s1_code0(data)                         (0x00000080&((data)<<7))
#define PRESET_S_CODE0_pre_set_s_code0(data)                          (0x0000007F&(data))
#define PRESET_S_CODE0_get_pre_set_s1_code3(data)                     ((0x80000000&(data))>>31)
#define PRESET_S_CODE0_get_pre_set_s_code3(data)                      ((0x7F000000&(data))>>24)
#define PRESET_S_CODE0_get_pre_set_s1_code2(data)                     ((0x00800000&(data))>>23)
#define PRESET_S_CODE0_get_pre_set_s_code2(data)                      ((0x007F0000&(data))>>16)
#define PRESET_S_CODE0_get_pre_set_s1_code1(data)                     ((0x00008000&(data))>>15)
#define PRESET_S_CODE0_get_pre_set_s_code1(data)                      ((0x00007F00&(data))>>8)
#define PRESET_S_CODE0_get_pre_set_s1_code0(data)                     ((0x00000080&(data))>>7)
#define PRESET_S_CODE0_get_pre_set_s_code0(data)                      (0x0000007F&(data))


#define PRESET_S_CODE1                                                0x130
#define PRESET_S_CODE1_reg_addr                                       "0x98034130"
#define PRESET_S_CODE1_reg                                            0x98034130
#define PRESET_S_CODE1_inst_addr                                      "0x004C"
#define PRESET_S_CODE1_inst                                           0x004C
#define set_PRESET_S_CODE1_reg(data)                                  (*((volatile unsigned int*)PRESET_S_CODE1_reg)=data)
#define get_PRESET_S_CODE1_reg                                        (*((volatile unsigned int*)PRESET_S_CODE1_reg))
#define PRESET_S_CODE1_dp_abuf_wr_mod_en_shift                        (23)
#define PRESET_S_CODE1_auto_stop_trk_en_shift                         (22)
#define PRESET_S_CODE1_trk_mod_en_shift                               (21)
#define PRESET_S_CODE1_afsm_mod_en_shift                              (20)
#define PRESET_S_CODE1_pre_set_sm_code0_shift                         (15)
#define PRESET_S_CODE1_pre_set_sm_code1_shift                         (14)
#define PRESET_S_CODE1_pre_set_sm_code2_shift                         (13)
#define PRESET_S_CODE1_pre_set_sm_code3_shift                         (12)
#define PRESET_S_CODE1_pre_set_sm_code4_shift                         (11)
#define PRESET_S_CODE1_pre_set_s1_code4_shift                         (7)
#define PRESET_S_CODE1_pre_set_s_code4_shift                          (0)
#define PRESET_S_CODE1_dp_abuf_wr_mod_en_mask                         (0x00800000)
#define PRESET_S_CODE1_auto_stop_trk_en_mask                          (0x00400000)
#define PRESET_S_CODE1_trk_mod_en_mask                                (0x00200000)
#define PRESET_S_CODE1_afsm_mod_en_mask                               (0x00100000)
#define PRESET_S_CODE1_pre_set_sm_code0_mask                          (0x00008000)
#define PRESET_S_CODE1_pre_set_sm_code1_mask                          (0x00004000)
#define PRESET_S_CODE1_pre_set_sm_code2_mask                          (0x00002000)
#define PRESET_S_CODE1_pre_set_sm_code3_mask                          (0x00001000)
#define PRESET_S_CODE1_pre_set_sm_code4_mask                          (0x00000800)
#define PRESET_S_CODE1_pre_set_s1_code4_mask                          (0x00000080)
#define PRESET_S_CODE1_pre_set_s_code4_mask                           (0x0000007F)
#define PRESET_S_CODE1_dp_abuf_wr_mod_en(data)                        (0x00800000&((data)<<23))
#define PRESET_S_CODE1_auto_stop_trk_en(data)                         (0x00400000&((data)<<22))
#define PRESET_S_CODE1_trk_mod_en(data)                               (0x00200000&((data)<<21))
#define PRESET_S_CODE1_afsm_mod_en(data)                              (0x00100000&((data)<<20))
#define PRESET_S_CODE1_pre_set_sm_code0(data)                         (0x00008000&((data)<<15))
#define PRESET_S_CODE1_pre_set_sm_code1(data)                         (0x00004000&((data)<<14))
#define PRESET_S_CODE1_pre_set_sm_code2(data)                         (0x00002000&((data)<<13))
#define PRESET_S_CODE1_pre_set_sm_code3(data)                         (0x00001000&((data)<<12))
#define PRESET_S_CODE1_pre_set_sm_code4(data)                         (0x00000800&((data)<<11))
#define PRESET_S_CODE1_pre_set_s1_code4(data)                         (0x00000080&((data)<<7))
#define PRESET_S_CODE1_pre_set_s_code4(data)                          (0x0000007F&(data))
#define PRESET_S_CODE1_get_dp_abuf_wr_mod_en(data)                    ((0x00800000&(data))>>23)
#define PRESET_S_CODE1_get_auto_stop_trk_en(data)                     ((0x00400000&(data))>>22)
#define PRESET_S_CODE1_get_trk_mod_en(data)                           ((0x00200000&(data))>>21)
#define PRESET_S_CODE1_get_afsm_mod_en(data)                          ((0x00100000&(data))>>20)
#define PRESET_S_CODE1_get_pre_set_sm_code0(data)                     ((0x00008000&(data))>>15)
#define PRESET_S_CODE1_get_pre_set_sm_code1(data)                     ((0x00004000&(data))>>14)
#define PRESET_S_CODE1_get_pre_set_sm_code2(data)                     ((0x00002000&(data))>>13)
#define PRESET_S_CODE1_get_pre_set_sm_code3(data)                     ((0x00001000&(data))>>12)
#define PRESET_S_CODE1_get_pre_set_sm_code4(data)                     ((0x00000800&(data))>>11)
#define PRESET_S_CODE1_get_pre_set_s1_code4(data)                     ((0x00000080&(data))>>7)
#define PRESET_S_CODE1_get_pre_set_s_code4(data)                      (0x0000007F&(data))


#define PRBS_R_CTRL                                                   0x134
#define PRBS_R_CTRL_reg_addr                                          "0x98034134"
#define PRBS_R_CTRL_reg                                               0x98034134
#define PRBS_R_CTRL_inst_addr                                         "0x004D"
#define PRBS_R_CTRL_inst                                              0x004D
#define set_PRBS_R_CTRL_reg(data)                                     (*((volatile unsigned int*)PRBS_R_CTRL_reg)=data)
#define get_PRBS_R_CTRL_reg                                           (*((volatile unsigned int*)PRBS_R_CTRL_reg))
#define PRBS_R_CTRL_prbs23_rxen_shift                                 (28)
#define PRBS_R_CTRL_prbs_rxbist_err_cnt_shift                         (20)
#define PRBS_R_CTRL_prbs_err_cnt_shift                                (16)
#define PRBS_R_CTRL_prbs_bit_err_shift                                (4)
#define PRBS_R_CTRL_prbs_lock_shift                                   (3)
#define PRBS_R_CTRL_prbs_err_cnt_clr_shift                            (2)
#define PRBS_R_CTRL_prbs_reverse_shift                                (1)
#define PRBS_R_CTRL_prbs7_rxen_shift                                  (0)
#define PRBS_R_CTRL_prbs23_rxen_mask                                  (0x10000000)
#define PRBS_R_CTRL_prbs_rxbist_err_cnt_mask                          (0x0FF00000)
#define PRBS_R_CTRL_prbs_err_cnt_mask                                 (0x000F0000)
#define PRBS_R_CTRL_prbs_bit_err_mask                                 (0x00003FF0)
#define PRBS_R_CTRL_prbs_lock_mask                                    (0x00000008)
#define PRBS_R_CTRL_prbs_err_cnt_clr_mask                             (0x00000004)
#define PRBS_R_CTRL_prbs_reverse_mask                                 (0x00000002)
#define PRBS_R_CTRL_prbs7_rxen_mask                                   (0x00000001)
#define PRBS_R_CTRL_prbs23_rxen(data)                                 (0x10000000&((data)<<28))
#define PRBS_R_CTRL_prbs_rxbist_err_cnt(data)                         (0x0FF00000&((data)<<20))
#define PRBS_R_CTRL_prbs_err_cnt(data)                                (0x000F0000&((data)<<16))
#define PRBS_R_CTRL_prbs_bit_err(data)                                (0x00003FF0&((data)<<4))
#define PRBS_R_CTRL_prbs_lock(data)                                   (0x00000008&((data)<<3))
#define PRBS_R_CTRL_prbs_err_cnt_clr(data)                            (0x00000004&((data)<<2))
#define PRBS_R_CTRL_prbs_reverse(data)                                (0x00000002&((data)<<1))
#define PRBS_R_CTRL_prbs7_rxen(data)                                  (0x00000001&(data))
#define PRBS_R_CTRL_get_prbs23_rxen(data)                             ((0x10000000&(data))>>28)
#define PRBS_R_CTRL_get_prbs_rxbist_err_cnt(data)                     ((0x0FF00000&(data))>>20)
#define PRBS_R_CTRL_get_prbs_err_cnt(data)                            ((0x000F0000&(data))>>16)
#define PRBS_R_CTRL_get_prbs_bit_err(data)                            ((0x00003FF0&(data))>>4)
#define PRBS_R_CTRL_get_prbs_lock(data)                               ((0x00000008&(data))>>3)
#define PRBS_R_CTRL_get_prbs_err_cnt_clr(data)                        ((0x00000004&(data))>>2)
#define PRBS_R_CTRL_get_prbs_reverse(data)                            ((0x00000002&(data))>>1)
#define PRBS_R_CTRL_get_prbs7_rxen(data)                              (0x00000001&(data))


#define PRBS_G_CTRL                                                   0x138
#define PRBS_G_CTRL_reg_addr                                          "0x98034138"
#define PRBS_G_CTRL_reg                                               0x98034138
#define PRBS_G_CTRL_inst_addr                                         "0x004E"
#define PRBS_G_CTRL_inst                                              0x004E
#define set_PRBS_G_CTRL_reg(data)                                     (*((volatile unsigned int*)PRBS_G_CTRL_reg)=data)
#define get_PRBS_G_CTRL_reg                                           (*((volatile unsigned int*)PRBS_G_CTRL_reg))
#define PRBS_G_CTRL_prbs23_rxen_shift                                 (28)
#define PRBS_G_CTRL_prbs_rxbist_err_cnt_shift                         (20)
#define PRBS_G_CTRL_prbs_err_cnt_shift                                (16)
#define PRBS_G_CTRL_prbs_bit_err_shift                                (4)
#define PRBS_G_CTRL_prbs_lock_shift                                   (3)
#define PRBS_G_CTRL_prbs_err_cnt_clr_shift                            (2)
#define PRBS_G_CTRL_prbs_reverse_shift                                (1)
#define PRBS_G_CTRL_prbs7_rxen_shift                                  (0)
#define PRBS_G_CTRL_prbs23_rxen_mask                                  (0x10000000)
#define PRBS_G_CTRL_prbs_rxbist_err_cnt_mask                          (0x0FF00000)
#define PRBS_G_CTRL_prbs_err_cnt_mask                                 (0x000F0000)
#define PRBS_G_CTRL_prbs_bit_err_mask                                 (0x00003FF0)
#define PRBS_G_CTRL_prbs_lock_mask                                    (0x00000008)
#define PRBS_G_CTRL_prbs_err_cnt_clr_mask                             (0x00000004)
#define PRBS_G_CTRL_prbs_reverse_mask                                 (0x00000002)
#define PRBS_G_CTRL_prbs7_rxen_mask                                   (0x00000001)
#define PRBS_G_CTRL_prbs23_rxen(data)                                 (0x10000000&((data)<<28))
#define PRBS_G_CTRL_prbs_rxbist_err_cnt(data)                         (0x0FF00000&((data)<<20))
#define PRBS_G_CTRL_prbs_err_cnt(data)                                (0x000F0000&((data)<<16))
#define PRBS_G_CTRL_prbs_bit_err(data)                                (0x00003FF0&((data)<<4))
#define PRBS_G_CTRL_prbs_lock(data)                                   (0x00000008&((data)<<3))
#define PRBS_G_CTRL_prbs_err_cnt_clr(data)                            (0x00000004&((data)<<2))
#define PRBS_G_CTRL_prbs_reverse(data)                                (0x00000002&((data)<<1))
#define PRBS_G_CTRL_prbs7_rxen(data)                                  (0x00000001&(data))
#define PRBS_G_CTRL_get_prbs23_rxen(data)                             ((0x10000000&(data))>>28)
#define PRBS_G_CTRL_get_prbs_rxbist_err_cnt(data)                     ((0x0FF00000&(data))>>20)
#define PRBS_G_CTRL_get_prbs_err_cnt(data)                            ((0x000F0000&(data))>>16)
#define PRBS_G_CTRL_get_prbs_bit_err(data)                            ((0x00003FF0&(data))>>4)
#define PRBS_G_CTRL_get_prbs_lock(data)                               ((0x00000008&(data))>>3)
#define PRBS_G_CTRL_get_prbs_err_cnt_clr(data)                        ((0x00000004&(data))>>2)
#define PRBS_G_CTRL_get_prbs_reverse(data)                            ((0x00000002&(data))>>1)
#define PRBS_G_CTRL_get_prbs7_rxen(data)                              (0x00000001&(data))


#define PRBS_B_CTRL                                                   0x13c
#define PRBS_B_CTRL_reg_addr                                          "0x9803413c"
#define PRBS_B_CTRL_reg                                               0x9803413c
#define PRBS_B_CTRL_inst_addr                                         "0x004F"
#define PRBS_B_CTRL_inst                                              0x004F
#define set_PRBS_B_CTRL_reg(data)                                     (*((volatile unsigned int*)PRBS_B_CTRL_reg)=data)
#define get_PRBS_B_CTRL_reg                                           (*((volatile unsigned int*)PRBS_B_CTRL_reg))
#define PRBS_B_CTRL_prbs23_rxen_shift                                 (28)
#define PRBS_B_CTRL_prbs_rxbist_err_cnt_shift                         (20)
#define PRBS_B_CTRL_prbs_err_cnt_shift                                (16)
#define PRBS_B_CTRL_prbs_bit_err_shift                                (4)
#define PRBS_B_CTRL_prbs_lock_shift                                   (3)
#define PRBS_B_CTRL_prbs_err_cnt_clr_shift                            (2)
#define PRBS_B_CTRL_prbs_reverse_shift                                (1)
#define PRBS_B_CTRL_prbs7_rxen_shift                                  (0)
#define PRBS_B_CTRL_prbs23_rxen_mask                                  (0x10000000)
#define PRBS_B_CTRL_prbs_rxbist_err_cnt_mask                          (0x0FF00000)
#define PRBS_B_CTRL_prbs_err_cnt_mask                                 (0x000F0000)
#define PRBS_B_CTRL_prbs_bit_err_mask                                 (0x00003FF0)
#define PRBS_B_CTRL_prbs_lock_mask                                    (0x00000008)
#define PRBS_B_CTRL_prbs_err_cnt_clr_mask                             (0x00000004)
#define PRBS_B_CTRL_prbs_reverse_mask                                 (0x00000002)
#define PRBS_B_CTRL_prbs7_rxen_mask                                   (0x00000001)
#define PRBS_B_CTRL_prbs23_rxen(data)                                 (0x10000000&((data)<<28))
#define PRBS_B_CTRL_prbs_rxbist_err_cnt(data)                         (0x0FF00000&((data)<<20))
#define PRBS_B_CTRL_prbs_err_cnt(data)                                (0x000F0000&((data)<<16))
#define PRBS_B_CTRL_prbs_bit_err(data)                                (0x00003FF0&((data)<<4))
#define PRBS_B_CTRL_prbs_lock(data)                                   (0x00000008&((data)<<3))
#define PRBS_B_CTRL_prbs_err_cnt_clr(data)                            (0x00000004&((data)<<2))
#define PRBS_B_CTRL_prbs_reverse(data)                                (0x00000002&((data)<<1))
#define PRBS_B_CTRL_prbs7_rxen(data)                                  (0x00000001&(data))
#define PRBS_B_CTRL_get_prbs23_rxen(data)                             ((0x10000000&(data))>>28)
#define PRBS_B_CTRL_get_prbs_rxbist_err_cnt(data)                     ((0x0FF00000&(data))>>20)
#define PRBS_B_CTRL_get_prbs_err_cnt(data)                            ((0x000F0000&(data))>>16)
#define PRBS_B_CTRL_get_prbs_bit_err(data)                            ((0x00003FF0&(data))>>4)
#define PRBS_B_CTRL_get_prbs_lock(data)                               ((0x00000008&(data))>>3)
#define PRBS_B_CTRL_get_prbs_err_cnt_clr(data)                        ((0x00000004&(data))>>2)
#define PRBS_B_CTRL_get_prbs_reverse(data)                            ((0x00000002&(data))>>1)
#define PRBS_B_CTRL_get_prbs7_rxen(data)                              (0x00000001&(data))


#define HDMI_LEADING_GB_CMP_CTRL                                      0x140
#define HDMI_LEADING_GB_CMP_CTRL_reg_addr                             "0x98034140"
#define HDMI_LEADING_GB_CMP_CTRL_reg                                  0x98034140
#define HDMI_LEADING_GB_CMP_CTRL_inst_addr                            "0x0050"
#define HDMI_LEADING_GB_CMP_CTRL_inst                                 0x0050
#define set_HDMI_LEADING_GB_CMP_CTRL_reg(data)                        (*((volatile unsigned int*)HDMI_LEADING_GB_CMP_CTRL_reg)=data)
#define get_HDMI_LEADING_GB_CMP_CTRL_reg                              (*((volatile unsigned int*)HDMI_LEADING_GB_CMP_CTRL_reg))
#define HDMI_LEADING_GB_CMP_CTRL_cmp_err_flag_shift                   (30)
#define HDMI_LEADING_GB_CMP_CTRL_cmp_err_wd_en_shift                  (29)
#define HDMI_LEADING_GB_CMP_CTRL_cmp_err_int_en_shift                 (28)
#define HDMI_LEADING_GB_CMP_CTRL_preamble_shift                       (24)
#define HDMI_LEADING_GB_CMP_CTRL_cmp_value_shift                      (8)
#define HDMI_LEADING_GB_CMP_CTRL_dvi_mode_sel_shift                   (4)
#define HDMI_LEADING_GB_CMP_CTRL_channel_sel_shift                    (2)
#define HDMI_LEADING_GB_CMP_CTRL_lgb_cal_conti_shift                  (1)
#define HDMI_LEADING_GB_CMP_CTRL_lgb_cal_en_shift                     (0)
#define HDMI_LEADING_GB_CMP_CTRL_cmp_err_flag_mask                    (0x40000000)
#define HDMI_LEADING_GB_CMP_CTRL_cmp_err_wd_en_mask                   (0x20000000)
#define HDMI_LEADING_GB_CMP_CTRL_cmp_err_int_en_mask                  (0x10000000)
#define HDMI_LEADING_GB_CMP_CTRL_preamble_mask                        (0x0F000000)
#define HDMI_LEADING_GB_CMP_CTRL_cmp_value_mask                       (0x0003FF00)
#define HDMI_LEADING_GB_CMP_CTRL_dvi_mode_sel_mask                    (0x00000010)
#define HDMI_LEADING_GB_CMP_CTRL_channel_sel_mask                     (0x0000000C)
#define HDMI_LEADING_GB_CMP_CTRL_lgb_cal_conti_mask                   (0x00000002)
#define HDMI_LEADING_GB_CMP_CTRL_lgb_cal_en_mask                      (0x00000001)
#define HDMI_LEADING_GB_CMP_CTRL_cmp_err_flag(data)                   (0x40000000&((data)<<30))
#define HDMI_LEADING_GB_CMP_CTRL_cmp_err_wd_en(data)                  (0x20000000&((data)<<29))
#define HDMI_LEADING_GB_CMP_CTRL_cmp_err_int_en(data)                 (0x10000000&((data)<<28))
#define HDMI_LEADING_GB_CMP_CTRL_preamble(data)                       (0x0F000000&((data)<<24))
#define HDMI_LEADING_GB_CMP_CTRL_cmp_value(data)                      (0x0003FF00&((data)<<8))
#define HDMI_LEADING_GB_CMP_CTRL_dvi_mode_sel(data)                   (0x00000010&((data)<<4))
#define HDMI_LEADING_GB_CMP_CTRL_channel_sel(data)                    (0x0000000C&((data)<<2))
#define HDMI_LEADING_GB_CMP_CTRL_lgb_cal_conti(data)                  (0x00000002&((data)<<1))
#define HDMI_LEADING_GB_CMP_CTRL_lgb_cal_en(data)                     (0x00000001&(data))
#define HDMI_LEADING_GB_CMP_CTRL_get_cmp_err_flag(data)               ((0x40000000&(data))>>30)
#define HDMI_LEADING_GB_CMP_CTRL_get_cmp_err_wd_en(data)              ((0x20000000&(data))>>29)
#define HDMI_LEADING_GB_CMP_CTRL_get_cmp_err_int_en(data)             ((0x10000000&(data))>>28)
#define HDMI_LEADING_GB_CMP_CTRL_get_preamble(data)                   ((0x0F000000&(data))>>24)
#define HDMI_LEADING_GB_CMP_CTRL_get_cmp_value(data)                  ((0x0003FF00&(data))>>8)
#define HDMI_LEADING_GB_CMP_CTRL_get_dvi_mode_sel(data)               ((0x00000010&(data))>>4)
#define HDMI_LEADING_GB_CMP_CTRL_get_channel_sel(data)                ((0x0000000C&(data))>>2)
#define HDMI_LEADING_GB_CMP_CTRL_get_lgb_cal_conti(data)              ((0x00000002&(data))>>1)
#define HDMI_LEADING_GB_CMP_CTRL_get_lgb_cal_en(data)                 (0x00000001&(data))


#define HDMI_LEADING_GB_CMP_TIMES                                     0x144
#define HDMI_LEADING_GB_CMP_TIMES_reg_addr                            "0x98034144"
#define HDMI_LEADING_GB_CMP_TIMES_reg                                 0x98034144
#define HDMI_LEADING_GB_CMP_TIMES_inst_addr                           "0x0051"
#define HDMI_LEADING_GB_CMP_TIMES_inst                                0x0051
#define set_HDMI_LEADING_GB_CMP_TIMES_reg(data)                       (*((volatile unsigned int*)HDMI_LEADING_GB_CMP_TIMES_reg)=data)
#define get_HDMI_LEADING_GB_CMP_TIMES_reg                             (*((volatile unsigned int*)HDMI_LEADING_GB_CMP_TIMES_reg))
#define HDMI_LEADING_GB_CMP_TIMES_cmp_err_cnt_shift                   (16)
#define HDMI_LEADING_GB_CMP_TIMES_cmp_times_shift                     (0)
#define HDMI_LEADING_GB_CMP_TIMES_cmp_err_cnt_mask                    (0xFFFF0000)
#define HDMI_LEADING_GB_CMP_TIMES_cmp_times_mask                      (0x0000FFFF)
#define HDMI_LEADING_GB_CMP_TIMES_cmp_err_cnt(data)                   (0xFFFF0000&((data)<<16))
#define HDMI_LEADING_GB_CMP_TIMES_cmp_times(data)                     (0x0000FFFF&(data))
#define HDMI_LEADING_GB_CMP_TIMES_get_cmp_err_cnt(data)               ((0xFFFF0000&(data))>>16)
#define HDMI_LEADING_GB_CMP_TIMES_get_cmp_times(data)                 (0x0000FFFF&(data))


#define HDMI_LEADING_GB_CMP_CNT                                       0x148
#define HDMI_LEADING_GB_CMP_CNT_reg_addr                              "0x98034148"
#define HDMI_LEADING_GB_CMP_CNT_reg                                   0x98034148
#define HDMI_LEADING_GB_CMP_CNT_inst_addr                             "0x0052"
#define HDMI_LEADING_GB_CMP_CNT_inst                                  0x0052
#define set_HDMI_LEADING_GB_CMP_CNT_reg(data)                         (*((volatile unsigned int*)HDMI_LEADING_GB_CMP_CNT_reg)=data)
#define get_HDMI_LEADING_GB_CMP_CNT_reg                               (*((volatile unsigned int*)HDMI_LEADING_GB_CMP_CNT_reg))
#define HDMI_LEADING_GB_CMP_CNT_preamble_cmp_cnt_shift                (16)
#define HDMI_LEADING_GB_CMP_CNT_preamble_cmp_cnt_by_frame_shift       (0)
#define HDMI_LEADING_GB_CMP_CNT_preamble_cmp_cnt_mask                 (0xFFFF0000)
#define HDMI_LEADING_GB_CMP_CNT_preamble_cmp_cnt_by_frame_mask        (0x0000FFFF)
#define HDMI_LEADING_GB_CMP_CNT_preamble_cmp_cnt(data)                (0xFFFF0000&((data)<<16))
#define HDMI_LEADING_GB_CMP_CNT_preamble_cmp_cnt_by_frame(data)       (0x0000FFFF&(data))
#define HDMI_LEADING_GB_CMP_CNT_get_preamble_cmp_cnt(data)            ((0xFFFF0000&(data))>>16)
#define HDMI_LEADING_GB_CMP_CNT_get_preamble_cmp_cnt_by_frame(data)   (0x0000FFFF&(data))


#define AUDIO_CTS_UP_BOUND                                            0x14c
#define AUDIO_CTS_UP_BOUND_reg_addr                                   "0x9803414c"
#define AUDIO_CTS_UP_BOUND_reg                                        0x9803414c
#define AUDIO_CTS_UP_BOUND_inst_addr                                  "0x0053"
#define AUDIO_CTS_UP_BOUND_inst                                       0x0053
#define set_AUDIO_CTS_UP_BOUND_reg(data)                              (*((volatile unsigned int*)AUDIO_CTS_UP_BOUND_reg)=data)
#define get_AUDIO_CTS_UP_BOUND_reg                                    (*((volatile unsigned int*)AUDIO_CTS_UP_BOUND_reg))
#define AUDIO_CTS_UP_BOUND_cts_over_flag_shift                        (31)
#define AUDIO_CTS_UP_BOUND_cts_clip_en_shift                          (20)
#define AUDIO_CTS_UP_BOUND_cts_up_bound_shift                         (0)
#define AUDIO_CTS_UP_BOUND_cts_over_flag_mask                         (0x80000000)
#define AUDIO_CTS_UP_BOUND_cts_clip_en_mask                           (0x00100000)
#define AUDIO_CTS_UP_BOUND_cts_up_bound_mask                          (0x000FFFFF)
#define AUDIO_CTS_UP_BOUND_cts_over_flag(data)                        (0x80000000&((data)<<31))
#define AUDIO_CTS_UP_BOUND_cts_clip_en(data)                          (0x00100000&((data)<<20))
#define AUDIO_CTS_UP_BOUND_cts_up_bound(data)                         (0x000FFFFF&(data))
#define AUDIO_CTS_UP_BOUND_get_cts_over_flag(data)                    ((0x80000000&(data))>>31)
#define AUDIO_CTS_UP_BOUND_get_cts_clip_en(data)                      ((0x00100000&(data))>>20)
#define AUDIO_CTS_UP_BOUND_get_cts_up_bound(data)                     (0x000FFFFF&(data))


#define AUDIO_CTS_LOW_BOUND                                           0x150
#define AUDIO_CTS_LOW_BOUND_reg_addr                                  "0x98034150"
#define AUDIO_CTS_LOW_BOUND_reg                                       0x98034150
#define AUDIO_CTS_LOW_BOUND_inst_addr                                 "0x0054"
#define AUDIO_CTS_LOW_BOUND_inst                                      0x0054
#define set_AUDIO_CTS_LOW_BOUND_reg(data)                             (*((volatile unsigned int*)AUDIO_CTS_LOW_BOUND_reg)=data)
#define get_AUDIO_CTS_LOW_BOUND_reg                                   (*((volatile unsigned int*)AUDIO_CTS_LOW_BOUND_reg))
#define AUDIO_CTS_LOW_BOUND_cts_under_flag_shift                      (31)
#define AUDIO_CTS_LOW_BOUND_cts_low_bound_shift                       (0)
#define AUDIO_CTS_LOW_BOUND_cts_under_flag_mask                       (0x80000000)
#define AUDIO_CTS_LOW_BOUND_cts_low_bound_mask                        (0x000FFFFF)
#define AUDIO_CTS_LOW_BOUND_cts_under_flag(data)                      (0x80000000&((data)<<31))
#define AUDIO_CTS_LOW_BOUND_cts_low_bound(data)                       (0x000FFFFF&(data))
#define AUDIO_CTS_LOW_BOUND_get_cts_under_flag(data)                  ((0x80000000&(data))>>31)
#define AUDIO_CTS_LOW_BOUND_get_cts_low_bound(data)                   (0x000FFFFF&(data))


#define AUDIO_N_UP_BOUND                                              0x154
#define AUDIO_N_UP_BOUND_reg_addr                                     "0x98034154"
#define AUDIO_N_UP_BOUND_reg                                          0x98034154
#define AUDIO_N_UP_BOUND_inst_addr                                    "0x0055"
#define AUDIO_N_UP_BOUND_inst                                         0x0055
#define set_AUDIO_N_UP_BOUND_reg(data)                                (*((volatile unsigned int*)AUDIO_N_UP_BOUND_reg)=data)
#define get_AUDIO_N_UP_BOUND_reg                                      (*((volatile unsigned int*)AUDIO_N_UP_BOUND_reg))
#define AUDIO_N_UP_BOUND_n_over_flag_shift                            (31)
#define AUDIO_N_UP_BOUND_n_clip_en_shift                              (20)
#define AUDIO_N_UP_BOUND_n_up_bound_shift                             (0)
#define AUDIO_N_UP_BOUND_n_over_flag_mask                             (0x80000000)
#define AUDIO_N_UP_BOUND_n_clip_en_mask                               (0x00100000)
#define AUDIO_N_UP_BOUND_n_up_bound_mask                              (0x000FFFFF)
#define AUDIO_N_UP_BOUND_n_over_flag(data)                            (0x80000000&((data)<<31))
#define AUDIO_N_UP_BOUND_n_clip_en(data)                              (0x00100000&((data)<<20))
#define AUDIO_N_UP_BOUND_n_up_bound(data)                             (0x000FFFFF&(data))
#define AUDIO_N_UP_BOUND_get_n_over_flag(data)                        ((0x80000000&(data))>>31)
#define AUDIO_N_UP_BOUND_get_n_clip_en(data)                          ((0x00100000&(data))>>20)
#define AUDIO_N_UP_BOUND_get_n_up_bound(data)                         (0x000FFFFF&(data))


#define AUDIO_N_LOW_BOUND                                             0x158
#define AUDIO_N_LOW_BOUND_reg_addr                                    "0x98034158"
#define AUDIO_N_LOW_BOUND_reg                                         0x98034158
#define AUDIO_N_LOW_BOUND_inst_addr                                   "0x0056"
#define AUDIO_N_LOW_BOUND_inst                                        0x0056
#define set_AUDIO_N_LOW_BOUND_reg(data)                               (*((volatile unsigned int*)AUDIO_N_LOW_BOUND_reg)=data)
#define get_AUDIO_N_LOW_BOUND_reg                                     (*((volatile unsigned int*)AUDIO_N_LOW_BOUND_reg))
#define AUDIO_N_LOW_BOUND_n_under_flag_shift                          (31)
#define AUDIO_N_LOW_BOUND_n_low_bound_shift                           (0)
#define AUDIO_N_LOW_BOUND_n_under_flag_mask                           (0x80000000)
#define AUDIO_N_LOW_BOUND_n_low_bound_mask                            (0x000FFFFF)
#define AUDIO_N_LOW_BOUND_n_under_flag(data)                          (0x80000000&((data)<<31))
#define AUDIO_N_LOW_BOUND_n_low_bound(data)                           (0x000FFFFF&(data))
#define AUDIO_N_LOW_BOUND_get_n_under_flag(data)                      ((0x80000000&(data))>>31)
#define AUDIO_N_LOW_BOUND_get_n_low_bound(data)                       (0x000FFFFF&(data))


#define MHL_HDMI_MAC_CTRL                                             0x15c
#define MHL_HDMI_MAC_CTRL_reg_addr                                    "0x9803415c"
#define MHL_HDMI_MAC_CTRL_reg                                         0x9803415c
#define MHL_HDMI_MAC_CTRL_inst_addr                                   "0x0057"
#define MHL_HDMI_MAC_CTRL_inst                                        0x0057
#define set_MHL_HDMI_MAC_CTRL_reg(data)                               (*((volatile unsigned int*)MHL_HDMI_MAC_CTRL_reg)=data)
#define get_MHL_HDMI_MAC_CTRL_reg                                     (*((volatile unsigned int*)MHL_HDMI_MAC_CTRL_reg))
#define MHL_HDMI_MAC_CTRL_hporch_offset_shift                         (16)
#define MHL_HDMI_MAC_CTRL_dummy_15_14_shift                           (14)
#define MHL_HDMI_MAC_CTRL_en_packet_retiming_vsrst_shift              (13)
#define MHL_HDMI_MAC_CTRL_pp_mode_output_shift                        (12)
#define MHL_HDMI_MAC_CTRL_packet_mhl_en_shift                         (8)
#define MHL_HDMI_MAC_CTRL_xor_pixel_sel_shift                         (5)
#define MHL_HDMI_MAC_CTRL_cal_pixel_sel_shift                         (4)
#define MHL_HDMI_MAC_CTRL_ch_dec_pp_mode_en_shift                     (0)
#define MHL_HDMI_MAC_CTRL_hporch_offset_mask                          (0x03FF0000)
#define MHL_HDMI_MAC_CTRL_dummy_15_14_mask                            (0x0000C000)
#define MHL_HDMI_MAC_CTRL_en_packet_retiming_vsrst_mask               (0x00002000)
#define MHL_HDMI_MAC_CTRL_pp_mode_output_mask                         (0x00001000)
#define MHL_HDMI_MAC_CTRL_packet_mhl_en_mask                          (0x00000100)
#define MHL_HDMI_MAC_CTRL_xor_pixel_sel_mask                          (0x000000E0)
#define MHL_HDMI_MAC_CTRL_cal_pixel_sel_mask                          (0x00000010)
#define MHL_HDMI_MAC_CTRL_ch_dec_pp_mode_en_mask                      (0x00000001)
#define MHL_HDMI_MAC_CTRL_hporch_offset(data)                         (0x03FF0000&((data)<<16))
#define MHL_HDMI_MAC_CTRL_dummy_15_14(data)                           (0x0000C000&((data)<<14))
#define MHL_HDMI_MAC_CTRL_en_packet_retiming_vsrst(data)              (0x00002000&((data)<<13))
#define MHL_HDMI_MAC_CTRL_pp_mode_output(data)                        (0x00001000&((data)<<12))
#define MHL_HDMI_MAC_CTRL_packet_mhl_en(data)                         (0x00000100&((data)<<8))
#define MHL_HDMI_MAC_CTRL_xor_pixel_sel(data)                         (0x000000E0&((data)<<5))
#define MHL_HDMI_MAC_CTRL_cal_pixel_sel(data)                         (0x00000010&((data)<<4))
#define MHL_HDMI_MAC_CTRL_ch_dec_pp_mode_en(data)                     (0x00000001&(data))
#define MHL_HDMI_MAC_CTRL_get_hporch_offset(data)                     ((0x03FF0000&(data))>>16)
#define MHL_HDMI_MAC_CTRL_get_dummy_15_14(data)                       ((0x0000C000&(data))>>14)
#define MHL_HDMI_MAC_CTRL_get_en_packet_retiming_vsrst(data)          ((0x00002000&(data))>>13)
#define MHL_HDMI_MAC_CTRL_get_pp_mode_output(data)                    ((0x00001000&(data))>>12)
#define MHL_HDMI_MAC_CTRL_get_packet_mhl_en(data)                     ((0x00000100&(data))>>8)
#define MHL_HDMI_MAC_CTRL_get_xor_pixel_sel(data)                     ((0x000000E0&(data))>>5)
#define MHL_HDMI_MAC_CTRL_get_cal_pixel_sel(data)                     ((0x00000010&(data))>>4)
#define MHL_HDMI_MAC_CTRL_get_ch_dec_pp_mode_en(data)                 (0x00000001&(data))


#define MHL_3D_FORMAT                                                 0x160
#define MHL_3D_FORMAT_reg_addr                                        "0x98034160"
#define MHL_3D_FORMAT_reg                                             0x98034160
#define MHL_3D_FORMAT_inst_addr                                       "0x0058"
#define MHL_3D_FORMAT_inst                                            0x0058
#define set_MHL_3D_FORMAT_reg(data)                                   (*((volatile unsigned int*)MHL_3D_FORMAT_reg)=data)
#define get_MHL_3D_FORMAT_reg                                         (*((volatile unsigned int*)MHL_3D_FORMAT_reg))
#define MHL_3D_FORMAT_mhl_3d_fmt_shift                                (26)
#define MHL_3D_FORMAT_mhl_vid_shift                                   (24)
#define MHL_3D_FORMAT_oui_shift                                       (0)
#define MHL_3D_FORMAT_mhl_3d_fmt_mask                                 (0x3C000000)
#define MHL_3D_FORMAT_mhl_vid_mask                                    (0x03000000)
#define MHL_3D_FORMAT_oui_mask                                        (0x00FFFFFF)
#define MHL_3D_FORMAT_mhl_3d_fmt(data)                                (0x3C000000&((data)<<26))
#define MHL_3D_FORMAT_mhl_vid(data)                                   (0x03000000&((data)<<24))
#define MHL_3D_FORMAT_oui(data)                                       (0x00FFFFFF&(data))
#define MHL_3D_FORMAT_get_mhl_3d_fmt(data)                            ((0x3C000000&(data))>>26)
#define MHL_3D_FORMAT_get_mhl_vid(data)                               ((0x03000000&(data))>>24)
#define MHL_3D_FORMAT_get_oui(data)                                   (0x00FFFFFF&(data))


#define MHL_3P0_FORMAT0                                               0x164
#define MHL_3P0_FORMAT0_reg_addr                                      "0x98034164"
#define MHL_3P0_FORMAT0_reg                                           0x98034164
#define MHL_3P0_FORMAT0_inst_addr                                     "0x0059"
#define MHL_3P0_FORMAT0_inst                                          0x0059
#define set_MHL_3P0_FORMAT0_reg(data)                                 (*((volatile unsigned int*)MHL_3P0_FORMAT0_reg)=data)
#define get_MHL_3P0_FORMAT0_reg                                       (*((volatile unsigned int*)MHL_3P0_FORMAT0_reg))
#define MHL_3P0_FORMAT0_mhl_hev_fmt_shift                             (17)
#define MHL_3P0_FORMAT0_sep_aud_shift                                 (16)
#define MHL_3P0_FORMAT0_mhl_hev_fmt_type_shift                        (0)
#define MHL_3P0_FORMAT0_mhl_hev_fmt_mask                              (0x00060000)
#define MHL_3P0_FORMAT0_sep_aud_mask                                  (0x00010000)
#define MHL_3P0_FORMAT0_mhl_hev_fmt_type_mask                         (0x0000FFFF)
#define MHL_3P0_FORMAT0_mhl_hev_fmt(data)                             (0x00060000&((data)<<17))
#define MHL_3P0_FORMAT0_sep_aud(data)                                 (0x00010000&((data)<<16))
#define MHL_3P0_FORMAT0_mhl_hev_fmt_type(data)                        (0x0000FFFF&(data))
#define MHL_3P0_FORMAT0_get_mhl_hev_fmt(data)                         ((0x00060000&(data))>>17)
#define MHL_3P0_FORMAT0_get_sep_aud(data)                             ((0x00010000&(data))>>16)
#define MHL_3P0_FORMAT0_get_mhl_hev_fmt_type(data)                    (0x0000FFFF&(data))


#define MHL_3P0_FORMAT1                                               0x168
#define MHL_3P0_FORMAT1_reg_addr                                      "0x98034168"
#define MHL_3P0_FORMAT1_reg                                           0x98034168
#define MHL_3P0_FORMAT1_inst_addr                                     "0x005A"
#define MHL_3P0_FORMAT1_inst                                          0x005A
#define set_MHL_3P0_FORMAT1_reg(data)                                 (*((volatile unsigned int*)MHL_3P0_FORMAT1_reg)=data)
#define get_MHL_3P0_FORMAT1_reg                                       (*((volatile unsigned int*)MHL_3P0_FORMAT1_reg))
#define MHL_3P0_FORMAT1_acrfs_div_shift                               (21)
#define MHL_3P0_FORMAT1_av_delay_dir_shift                            (20)
#define MHL_3P0_FORMAT1_av_delay_sync_shift                           (0)
#define MHL_3P0_FORMAT1_acrfs_div_mask                                (0x00E00000)
#define MHL_3P0_FORMAT1_av_delay_dir_mask                             (0x00100000)
#define MHL_3P0_FORMAT1_av_delay_sync_mask                            (0x000FFFFF)
#define MHL_3P0_FORMAT1_acrfs_div(data)                               (0x00E00000&((data)<<21))
#define MHL_3P0_FORMAT1_av_delay_dir(data)                            (0x00100000&((data)<<20))
#define MHL_3P0_FORMAT1_av_delay_sync(data)                           (0x000FFFFF&(data))
#define MHL_3P0_FORMAT1_get_acrfs_div(data)                           ((0x00E00000&(data))>>21)
#define MHL_3P0_FORMAT1_get_av_delay_dir(data)                        ((0x00100000&(data))>>20)
#define MHL_3P0_FORMAT1_get_av_delay_sync(data)                       (0x000FFFFF&(data))


#define LIGHT_SLEEP                                                   0x170
#define LIGHT_SLEEP_reg_addr                                          "0x98034170"
#define LIGHT_SLEEP_reg                                               0x98034170
#define LIGHT_SLEEP_inst_addr                                         "0x005C"
#define LIGHT_SLEEP_inst                                              0x005C
#define set_LIGHT_SLEEP_reg(data)                                     (*((volatile unsigned int*)LIGHT_SLEEP_reg)=data)
#define get_LIGHT_SLEEP_reg                                           (*((volatile unsigned int*)LIGHT_SLEEP_reg))
#define LIGHT_SLEEP_yuv420_ls3_shift                                  (8)
#define LIGHT_SLEEP_yuv420_ls2_shift                                  (7)
#define LIGHT_SLEEP_yuv420_ls1_shift                                  (6)
#define LIGHT_SLEEP_yuv420_ls0_shift                                  (5)
#define LIGHT_SLEEP_hdcp_2p2_ls1_shift                                (4)
#define LIGHT_SLEEP_hdcp_2p2_ls0_shift                                (3)
#define LIGHT_SLEEP_hdcp_ksvfifo_ls_shift                             (2)
#define LIGHT_SLEEP_hdcp_ls_shift                                     (1)
#define LIGHT_SLEEP_audio_ls_shift                                    (0)
#define LIGHT_SLEEP_yuv420_ls3_mask                                   (0x00000100)
#define LIGHT_SLEEP_yuv420_ls2_mask                                   (0x00000080)
#define LIGHT_SLEEP_yuv420_ls1_mask                                   (0x00000040)
#define LIGHT_SLEEP_yuv420_ls0_mask                                   (0x00000020)
#define LIGHT_SLEEP_hdcp_2p2_ls1_mask                                 (0x00000010)
#define LIGHT_SLEEP_hdcp_2p2_ls0_mask                                 (0x00000008)
#define LIGHT_SLEEP_hdcp_ksvfifo_ls_mask                              (0x00000004)
#define LIGHT_SLEEP_hdcp_ls_mask                                      (0x00000002)
#define LIGHT_SLEEP_audio_ls_mask                                     (0x00000001)
#define LIGHT_SLEEP_yuv420_ls3(data)                                  (0x00000100&((data)<<8))
#define LIGHT_SLEEP_yuv420_ls2(data)                                  (0x00000080&((data)<<7))
#define LIGHT_SLEEP_yuv420_ls1(data)                                  (0x00000040&((data)<<6))
#define LIGHT_SLEEP_yuv420_ls0(data)                                  (0x00000020&((data)<<5))
#define LIGHT_SLEEP_hdcp_2p2_ls1(data)                                (0x00000010&((data)<<4))
#define LIGHT_SLEEP_hdcp_2p2_ls0(data)                                (0x00000008&((data)<<3))
#define LIGHT_SLEEP_hdcp_ksvfifo_ls(data)                             (0x00000004&((data)<<2))
#define LIGHT_SLEEP_hdcp_ls(data)                                     (0x00000002&((data)<<1))
#define LIGHT_SLEEP_audio_ls(data)                                    (0x00000001&(data))
#define LIGHT_SLEEP_get_yuv420_ls3(data)                              ((0x00000100&(data))>>8)
#define LIGHT_SLEEP_get_yuv420_ls2(data)                              ((0x00000080&(data))>>7)
#define LIGHT_SLEEP_get_yuv420_ls1(data)                              ((0x00000040&(data))>>6)
#define LIGHT_SLEEP_get_yuv420_ls0(data)                              ((0x00000020&(data))>>5)
#define LIGHT_SLEEP_get_hdcp_2p2_ls1(data)                            ((0x00000010&(data))>>4)
#define LIGHT_SLEEP_get_hdcp_2p2_ls0(data)                            ((0x00000008&(data))>>3)
#define LIGHT_SLEEP_get_hdcp_ksvfifo_ls(data)                         ((0x00000004&(data))>>2)
#define LIGHT_SLEEP_get_hdcp_ls(data)                                 ((0x00000002&(data))>>1)
#define LIGHT_SLEEP_get_audio_ls(data)                                (0x00000001&(data))


#define READ_MARGIN2                                                  0x174
#define READ_MARGIN2_reg_addr                                         "0x98034174"
#define READ_MARGIN2_reg                                              0x98034174
#define READ_MARGIN2_inst_addr                                        "0x005D"
#define READ_MARGIN2_inst                                             0x005D
#define set_READ_MARGIN2_reg(data)                                    (*((volatile unsigned int*)READ_MARGIN2_reg)=data)
#define get_READ_MARGIN2_reg                                          (*((volatile unsigned int*)READ_MARGIN2_reg))
#define READ_MARGIN2_yuv420_rm3_shift                                 (12)
#define READ_MARGIN2_yuv420_rm2_shift                                 (8)
#define READ_MARGIN2_yuv420_rm1_shift                                 (4)
#define READ_MARGIN2_yuv420_rm0_shift                                 (0)
#define READ_MARGIN2_yuv420_rm3_mask                                  (0x0000F000)
#define READ_MARGIN2_yuv420_rm2_mask                                  (0x00000F00)
#define READ_MARGIN2_yuv420_rm1_mask                                  (0x000000F0)
#define READ_MARGIN2_yuv420_rm0_mask                                  (0x0000000F)
#define READ_MARGIN2_yuv420_rm3(data)                                 (0x0000F000&((data)<<12))
#define READ_MARGIN2_yuv420_rm2(data)                                 (0x00000F00&((data)<<8))
#define READ_MARGIN2_yuv420_rm1(data)                                 (0x000000F0&((data)<<4))
#define READ_MARGIN2_yuv420_rm0(data)                                 (0x0000000F&(data))
#define READ_MARGIN2_get_yuv420_rm3(data)                             ((0x0000F000&(data))>>12)
#define READ_MARGIN2_get_yuv420_rm2(data)                             ((0x00000F00&(data))>>8)
#define READ_MARGIN2_get_yuv420_rm1(data)                             ((0x000000F0&(data))>>4)
#define READ_MARGIN2_get_yuv420_rm0(data)                             (0x0000000F&(data))


#define READ_MARGIN_ENABLE                                            0x178
#define READ_MARGIN_ENABLE_reg_addr                                   "0x98034178"
#define READ_MARGIN_ENABLE_reg                                        0x98034178
#define READ_MARGIN_ENABLE_inst_addr                                  "0x005E"
#define READ_MARGIN_ENABLE_inst                                       0x005E
#define set_READ_MARGIN_ENABLE_reg(data)                              (*((volatile unsigned int*)READ_MARGIN_ENABLE_reg)=data)
#define get_READ_MARGIN_ENABLE_reg                                    (*((volatile unsigned int*)READ_MARGIN_ENABLE_reg))
#define READ_MARGIN_ENABLE_yuv420_rme3_shift                          (8)
#define READ_MARGIN_ENABLE_yuv420_rme2_shift                          (7)
#define READ_MARGIN_ENABLE_yuv420_rme1_shift                          (6)
#define READ_MARGIN_ENABLE_yuv420_rme0_shift                          (5)
#define READ_MARGIN_ENABLE_hdcp_2p2_rme1_shift                        (4)
#define READ_MARGIN_ENABLE_hdcp_2p2_rme0_shift                        (3)
#define READ_MARGIN_ENABLE_hdcp_ksvfifo_rme_shift                     (2)
#define READ_MARGIN_ENABLE_hdcp_rme_shift                             (1)
#define READ_MARGIN_ENABLE_audio_rme_shift                            (0)
#define READ_MARGIN_ENABLE_yuv420_rme3_mask                           (0x00000100)
#define READ_MARGIN_ENABLE_yuv420_rme2_mask                           (0x00000080)
#define READ_MARGIN_ENABLE_yuv420_rme1_mask                           (0x00000040)
#define READ_MARGIN_ENABLE_yuv420_rme0_mask                           (0x00000020)
#define READ_MARGIN_ENABLE_hdcp_2p2_rme1_mask                         (0x00000010)
#define READ_MARGIN_ENABLE_hdcp_2p2_rme0_mask                         (0x00000008)
#define READ_MARGIN_ENABLE_hdcp_ksvfifo_rme_mask                      (0x00000004)
#define READ_MARGIN_ENABLE_hdcp_rme_mask                              (0x00000002)
#define READ_MARGIN_ENABLE_audio_rme_mask                             (0x00000001)
#define READ_MARGIN_ENABLE_yuv420_rme3(data)                          (0x00000100&((data)<<8))
#define READ_MARGIN_ENABLE_yuv420_rme2(data)                          (0x00000080&((data)<<7))
#define READ_MARGIN_ENABLE_yuv420_rme1(data)                          (0x00000040&((data)<<6))
#define READ_MARGIN_ENABLE_yuv420_rme0(data)                          (0x00000020&((data)<<5))
#define READ_MARGIN_ENABLE_hdcp_2p2_rme1(data)                        (0x00000010&((data)<<4))
#define READ_MARGIN_ENABLE_hdcp_2p2_rme0(data)                        (0x00000008&((data)<<3))
#define READ_MARGIN_ENABLE_hdcp_ksvfifo_rme(data)                     (0x00000004&((data)<<2))
#define READ_MARGIN_ENABLE_hdcp_rme(data)                             (0x00000002&((data)<<1))
#define READ_MARGIN_ENABLE_audio_rme(data)                            (0x00000001&(data))
#define READ_MARGIN_ENABLE_get_yuv420_rme3(data)                      ((0x00000100&(data))>>8)
#define READ_MARGIN_ENABLE_get_yuv420_rme2(data)                      ((0x00000080&(data))>>7)
#define READ_MARGIN_ENABLE_get_yuv420_rme1(data)                      ((0x00000040&(data))>>6)
#define READ_MARGIN_ENABLE_get_yuv420_rme0(data)                      ((0x00000020&(data))>>5)
#define READ_MARGIN_ENABLE_get_hdcp_2p2_rme1(data)                    ((0x00000010&(data))>>4)
#define READ_MARGIN_ENABLE_get_hdcp_2p2_rme0(data)                    ((0x00000008&(data))>>3)
#define READ_MARGIN_ENABLE_get_hdcp_ksvfifo_rme(data)                 ((0x00000004&(data))>>2)
#define READ_MARGIN_ENABLE_get_hdcp_rme(data)                         ((0x00000002&(data))>>1)
#define READ_MARGIN_ENABLE_get_audio_rme(data)                        (0x00000001&(data))


#define READ_MARGIN                                                   0x17c
#define READ_MARGIN_reg_addr                                          "0x9803417c"
#define READ_MARGIN_reg                                               0x9803417c
#define READ_MARGIN_inst_addr                                         "0x005F"
#define READ_MARGIN_inst                                              0x005F
#define set_READ_MARGIN_reg(data)                                     (*((volatile unsigned int*)READ_MARGIN_reg)=data)
#define get_READ_MARGIN_reg                                           (*((volatile unsigned int*)READ_MARGIN_reg))
#define READ_MARGIN_hdcp_2p2_rm1_shift                                (16)
#define READ_MARGIN_hdcp_2p2_rm0_shift                                (12)
#define READ_MARGIN_hdcp_ksvfifo_rm_shift                             (8)
#define READ_MARGIN_hdcp_rm_shift                                     (4)
#define READ_MARGIN_audio_rm_shift                                    (0)
#define READ_MARGIN_hdcp_2p2_rm1_mask                                 (0x000F0000)
#define READ_MARGIN_hdcp_2p2_rm0_mask                                 (0x0000F000)
#define READ_MARGIN_hdcp_ksvfifo_rm_mask                              (0x00000F00)
#define READ_MARGIN_hdcp_rm_mask                                      (0x000000F0)
#define READ_MARGIN_audio_rm_mask                                     (0x0000000F)
#define READ_MARGIN_hdcp_2p2_rm1(data)                                (0x000F0000&((data)<<16))
#define READ_MARGIN_hdcp_2p2_rm0(data)                                (0x0000F000&((data)<<12))
#define READ_MARGIN_hdcp_ksvfifo_rm(data)                             (0x00000F00&((data)<<8))
#define READ_MARGIN_hdcp_rm(data)                                     (0x000000F0&((data)<<4))
#define READ_MARGIN_audio_rm(data)                                    (0x0000000F&(data))
#define READ_MARGIN_get_hdcp_2p2_rm1(data)                            ((0x000F0000&(data))>>16)
#define READ_MARGIN_get_hdcp_2p2_rm0(data)                            ((0x0000F000&(data))>>12)
#define READ_MARGIN_get_hdcp_ksvfifo_rm(data)                         ((0x00000F00&(data))>>8)
#define READ_MARGIN_get_hdcp_rm(data)                                 ((0x000000F0&(data))>>4)
#define READ_MARGIN_get_audio_rm(data)                                (0x0000000F&(data))


#define BIST_MODE                                                     0x180
#define BIST_MODE_reg_addr                                            "0x98034180"
#define BIST_MODE_reg                                                 0x98034180
#define BIST_MODE_inst_addr                                           "0x0060"
#define BIST_MODE_inst                                                0x0060
#define set_BIST_MODE_reg(data)                                       (*((volatile unsigned int*)BIST_MODE_reg)=data)
#define get_BIST_MODE_reg                                             (*((volatile unsigned int*)BIST_MODE_reg))
#define BIST_MODE_yuv420_bist_en_shift                                (4)
#define BIST_MODE_hdcp_2p2_bist_en_shift                              (3)
#define BIST_MODE_hdcp_ksvfifo_bist_en_shift                          (2)
#define BIST_MODE_hdcp_bist_en_shift                                  (1)
#define BIST_MODE_audio_bist_en_shift                                 (0)
#define BIST_MODE_yuv420_bist_en_mask                                 (0x00000010)
#define BIST_MODE_hdcp_2p2_bist_en_mask                               (0x00000008)
#define BIST_MODE_hdcp_ksvfifo_bist_en_mask                           (0x00000004)
#define BIST_MODE_hdcp_bist_en_mask                                   (0x00000002)
#define BIST_MODE_audio_bist_en_mask                                  (0x00000001)
#define BIST_MODE_yuv420_bist_en(data)                                (0x00000010&((data)<<4))
#define BIST_MODE_hdcp_2p2_bist_en(data)                              (0x00000008&((data)<<3))
#define BIST_MODE_hdcp_ksvfifo_bist_en(data)                          (0x00000004&((data)<<2))
#define BIST_MODE_hdcp_bist_en(data)                                  (0x00000002&((data)<<1))
#define BIST_MODE_audio_bist_en(data)                                 (0x00000001&(data))
#define BIST_MODE_get_yuv420_bist_en(data)                            ((0x00000010&(data))>>4)
#define BIST_MODE_get_hdcp_2p2_bist_en(data)                          ((0x00000008&(data))>>3)
#define BIST_MODE_get_hdcp_ksvfifo_bist_en(data)                      ((0x00000004&(data))>>2)
#define BIST_MODE_get_hdcp_bist_en(data)                              ((0x00000002&(data))>>1)
#define BIST_MODE_get_audio_bist_en(data)                             (0x00000001&(data))


#define BIST_DONE                                                     0x184
#define BIST_DONE_reg_addr                                            "0x98034184"
#define BIST_DONE_reg                                                 0x98034184
#define BIST_DONE_inst_addr                                           "0x0061"
#define BIST_DONE_inst                                                0x0061
#define set_BIST_DONE_reg(data)                                       (*((volatile unsigned int*)BIST_DONE_reg)=data)
#define get_BIST_DONE_reg                                             (*((volatile unsigned int*)BIST_DONE_reg))
#define BIST_DONE_yuv420_bist_done_shift                              (4)
#define BIST_DONE_hdcp_2p2_bist_done_shift                            (3)
#define BIST_DONE_hdcp_ksvfifo_bist_done_shift                        (2)
#define BIST_DONE_hdcp_bist_done_shift                                (1)
#define BIST_DONE_audio_bist_done_shift                               (0)
#define BIST_DONE_yuv420_bist_done_mask                               (0x00000010)
#define BIST_DONE_hdcp_2p2_bist_done_mask                             (0x00000008)
#define BIST_DONE_hdcp_ksvfifo_bist_done_mask                         (0x00000004)
#define BIST_DONE_hdcp_bist_done_mask                                 (0x00000002)
#define BIST_DONE_audio_bist_done_mask                                (0x00000001)
#define BIST_DONE_yuv420_bist_done(data)                              (0x00000010&((data)<<4))
#define BIST_DONE_hdcp_2p2_bist_done(data)                            (0x00000008&((data)<<3))
#define BIST_DONE_hdcp_ksvfifo_bist_done(data)                        (0x00000004&((data)<<2))
#define BIST_DONE_hdcp_bist_done(data)                                (0x00000002&((data)<<1))
#define BIST_DONE_audio_bist_done(data)                               (0x00000001&(data))
#define BIST_DONE_get_yuv420_bist_done(data)                          ((0x00000010&(data))>>4)
#define BIST_DONE_get_hdcp_2p2_bist_done(data)                        ((0x00000008&(data))>>3)
#define BIST_DONE_get_hdcp_ksvfifo_bist_done(data)                    ((0x00000004&(data))>>2)
#define BIST_DONE_get_hdcp_bist_done(data)                            ((0x00000002&(data))>>1)
#define BIST_DONE_get_audio_bist_done(data)                           (0x00000001&(data))


#define BIST_FAIL                                                     0x188
#define BIST_FAIL_reg_addr                                            "0x98034188"
#define BIST_FAIL_reg                                                 0x98034188
#define BIST_FAIL_inst_addr                                           "0x0062"
#define BIST_FAIL_inst                                                0x0062
#define set_BIST_FAIL_reg(data)                                       (*((volatile unsigned int*)BIST_FAIL_reg)=data)
#define get_BIST_FAIL_reg                                             (*((volatile unsigned int*)BIST_FAIL_reg))
#define BIST_FAIL_yuv420_bist_fail_shift                              (4)
#define BIST_FAIL_hdcp_2p2_bist_fail_shift                            (3)
#define BIST_FAIL_hdcp_ksvfifo_bist_fail_shift                        (2)
#define BIST_FAIL_hdcp_bist_fail_shift                                (1)
#define BIST_FAIL_audio_bist_fail_shift                               (0)
#define BIST_FAIL_yuv420_bist_fail_mask                               (0x00000010)
#define BIST_FAIL_hdcp_2p2_bist_fail_mask                             (0x00000008)
#define BIST_FAIL_hdcp_ksvfifo_bist_fail_mask                         (0x00000004)
#define BIST_FAIL_hdcp_bist_fail_mask                                 (0x00000002)
#define BIST_FAIL_audio_bist_fail_mask                                (0x00000001)
#define BIST_FAIL_yuv420_bist_fail(data)                              (0x00000010&((data)<<4))
#define BIST_FAIL_hdcp_2p2_bist_fail(data)                            (0x00000008&((data)<<3))
#define BIST_FAIL_hdcp_ksvfifo_bist_fail(data)                        (0x00000004&((data)<<2))
#define BIST_FAIL_hdcp_bist_fail(data)                                (0x00000002&((data)<<1))
#define BIST_FAIL_audio_bist_fail(data)                               (0x00000001&(data))
#define BIST_FAIL_get_yuv420_bist_fail(data)                          ((0x00000010&(data))>>4)
#define BIST_FAIL_get_hdcp_2p2_bist_fail(data)                        ((0x00000008&(data))>>3)
#define BIST_FAIL_get_hdcp_ksvfifo_bist_fail(data)                    ((0x00000004&(data))>>2)
#define BIST_FAIL_get_hdcp_bist_fail(data)                            ((0x00000002&(data))>>1)
#define BIST_FAIL_get_audio_bist_fail(data)                           (0x00000001&(data))


#define DRF_MODE                                                      0x18c
#define DRF_MODE_reg_addr                                             "0x9803418c"
#define DRF_MODE_reg                                                  0x9803418c
#define DRF_MODE_inst_addr                                            "0x0063"
#define DRF_MODE_inst                                                 0x0063
#define set_DRF_MODE_reg(data)                                        (*((volatile unsigned int*)DRF_MODE_reg)=data)
#define get_DRF_MODE_reg                                              (*((volatile unsigned int*)DRF_MODE_reg))
#define DRF_MODE_yuv420_drf_mode_shift                                (4)
#define DRF_MODE_hdcp_2p2_drf_mode_shift                              (3)
#define DRF_MODE_hdcp_ksvfifo_drf_mode_shift                          (2)
#define DRF_MODE_hdcp_drf_mode_shift                                  (1)
#define DRF_MODE_audio_drf_mode_shift                                 (0)
#define DRF_MODE_yuv420_drf_mode_mask                                 (0x00000010)
#define DRF_MODE_hdcp_2p2_drf_mode_mask                               (0x00000008)
#define DRF_MODE_hdcp_ksvfifo_drf_mode_mask                           (0x00000004)
#define DRF_MODE_hdcp_drf_mode_mask                                   (0x00000002)
#define DRF_MODE_audio_drf_mode_mask                                  (0x00000001)
#define DRF_MODE_yuv420_drf_mode(data)                                (0x00000010&((data)<<4))
#define DRF_MODE_hdcp_2p2_drf_mode(data)                              (0x00000008&((data)<<3))
#define DRF_MODE_hdcp_ksvfifo_drf_mode(data)                          (0x00000004&((data)<<2))
#define DRF_MODE_hdcp_drf_mode(data)                                  (0x00000002&((data)<<1))
#define DRF_MODE_audio_drf_mode(data)                                 (0x00000001&(data))
#define DRF_MODE_get_yuv420_drf_mode(data)                            ((0x00000010&(data))>>4)
#define DRF_MODE_get_hdcp_2p2_drf_mode(data)                          ((0x00000008&(data))>>3)
#define DRF_MODE_get_hdcp_ksvfifo_drf_mode(data)                      ((0x00000004&(data))>>2)
#define DRF_MODE_get_hdcp_drf_mode(data)                              ((0x00000002&(data))>>1)
#define DRF_MODE_get_audio_drf_mode(data)                             (0x00000001&(data))


#define DRF_RESUME                                                    0x190
#define DRF_RESUME_reg_addr                                           "0x98034190"
#define DRF_RESUME_reg                                                0x98034190
#define DRF_RESUME_inst_addr                                          "0x0064"
#define DRF_RESUME_inst                                               0x0064
#define set_DRF_RESUME_reg(data)                                      (*((volatile unsigned int*)DRF_RESUME_reg)=data)
#define get_DRF_RESUME_reg                                            (*((volatile unsigned int*)DRF_RESUME_reg))
#define DRF_RESUME_yuv420_drf_resume_shift                            (4)
#define DRF_RESUME_hdcp_2p2_drf_resume_shift                          (3)
#define DRF_RESUME_hdcp_ksvfifo_drf_resume_shift                      (2)
#define DRF_RESUME_hdcp_drf_resume_shift                              (1)
#define DRF_RESUME_audio_drf_resume_shift                             (0)
#define DRF_RESUME_yuv420_drf_resume_mask                             (0x00000010)
#define DRF_RESUME_hdcp_2p2_drf_resume_mask                           (0x00000008)
#define DRF_RESUME_hdcp_ksvfifo_drf_resume_mask                       (0x00000004)
#define DRF_RESUME_hdcp_drf_resume_mask                               (0x00000002)
#define DRF_RESUME_audio_drf_resume_mask                              (0x00000001)
#define DRF_RESUME_yuv420_drf_resume(data)                            (0x00000010&((data)<<4))
#define DRF_RESUME_hdcp_2p2_drf_resume(data)                          (0x00000008&((data)<<3))
#define DRF_RESUME_hdcp_ksvfifo_drf_resume(data)                      (0x00000004&((data)<<2))
#define DRF_RESUME_hdcp_drf_resume(data)                              (0x00000002&((data)<<1))
#define DRF_RESUME_audio_drf_resume(data)                             (0x00000001&(data))
#define DRF_RESUME_get_yuv420_drf_resume(data)                        ((0x00000010&(data))>>4)
#define DRF_RESUME_get_hdcp_2p2_drf_resume(data)                      ((0x00000008&(data))>>3)
#define DRF_RESUME_get_hdcp_ksvfifo_drf_resume(data)                  ((0x00000004&(data))>>2)
#define DRF_RESUME_get_hdcp_drf_resume(data)                          ((0x00000002&(data))>>1)
#define DRF_RESUME_get_audio_drf_resume(data)                         (0x00000001&(data))


#define DRF_DONE                                                      0x194
#define DRF_DONE_reg_addr                                             "0x98034194"
#define DRF_DONE_reg                                                  0x98034194
#define DRF_DONE_inst_addr                                            "0x0065"
#define DRF_DONE_inst                                                 0x0065
#define set_DRF_DONE_reg(data)                                        (*((volatile unsigned int*)DRF_DONE_reg)=data)
#define get_DRF_DONE_reg                                              (*((volatile unsigned int*)DRF_DONE_reg))
#define DRF_DONE_yuv420_drf_done_shift                                (4)
#define DRF_DONE_hdcp_2p2_drf_done_shift                              (3)
#define DRF_DONE_hdcp_ksvfifo_drf_done_shift                          (2)
#define DRF_DONE_hdcp_drf_done_shift                                  (1)
#define DRF_DONE_audio_drf_done_shift                                 (0)
#define DRF_DONE_yuv420_drf_done_mask                                 (0x00000010)
#define DRF_DONE_hdcp_2p2_drf_done_mask                               (0x00000008)
#define DRF_DONE_hdcp_ksvfifo_drf_done_mask                           (0x00000004)
#define DRF_DONE_hdcp_drf_done_mask                                   (0x00000002)
#define DRF_DONE_audio_drf_done_mask                                  (0x00000001)
#define DRF_DONE_yuv420_drf_done(data)                                (0x00000010&((data)<<4))
#define DRF_DONE_hdcp_2p2_drf_done(data)                              (0x00000008&((data)<<3))
#define DRF_DONE_hdcp_ksvfifo_drf_done(data)                          (0x00000004&((data)<<2))
#define DRF_DONE_hdcp_drf_done(data)                                  (0x00000002&((data)<<1))
#define DRF_DONE_audio_drf_done(data)                                 (0x00000001&(data))
#define DRF_DONE_get_yuv420_drf_done(data)                            ((0x00000010&(data))>>4)
#define DRF_DONE_get_hdcp_2p2_drf_done(data)                          ((0x00000008&(data))>>3)
#define DRF_DONE_get_hdcp_ksvfifo_drf_done(data)                      ((0x00000004&(data))>>2)
#define DRF_DONE_get_hdcp_drf_done(data)                              ((0x00000002&(data))>>1)
#define DRF_DONE_get_audio_drf_done(data)                             (0x00000001&(data))


#define DRF_PAUSE                                                     0x198
#define DRF_PAUSE_reg_addr                                            "0x98034198"
#define DRF_PAUSE_reg                                                 0x98034198
#define DRF_PAUSE_inst_addr                                           "0x0066"
#define DRF_PAUSE_inst                                                0x0066
#define set_DRF_PAUSE_reg(data)                                       (*((volatile unsigned int*)DRF_PAUSE_reg)=data)
#define get_DRF_PAUSE_reg                                             (*((volatile unsigned int*)DRF_PAUSE_reg))
#define DRF_PAUSE_yuv420_drf_pause_shift                              (4)
#define DRF_PAUSE_hdcp_2p2_drf_pause_shift                            (3)
#define DRF_PAUSE_hdcp_ksvfifo_drf_pause_shift                        (2)
#define DRF_PAUSE_hdcp_drf_pause_shift                                (1)
#define DRF_PAUSE_audio_drf_pause_shift                               (0)
#define DRF_PAUSE_yuv420_drf_pause_mask                               (0x00000010)
#define DRF_PAUSE_hdcp_2p2_drf_pause_mask                             (0x00000008)
#define DRF_PAUSE_hdcp_ksvfifo_drf_pause_mask                         (0x00000004)
#define DRF_PAUSE_hdcp_drf_pause_mask                                 (0x00000002)
#define DRF_PAUSE_audio_drf_pause_mask                                (0x00000001)
#define DRF_PAUSE_yuv420_drf_pause(data)                              (0x00000010&((data)<<4))
#define DRF_PAUSE_hdcp_2p2_drf_pause(data)                            (0x00000008&((data)<<3))
#define DRF_PAUSE_hdcp_ksvfifo_drf_pause(data)                        (0x00000004&((data)<<2))
#define DRF_PAUSE_hdcp_drf_pause(data)                                (0x00000002&((data)<<1))
#define DRF_PAUSE_audio_drf_pause(data)                               (0x00000001&(data))
#define DRF_PAUSE_get_yuv420_drf_pause(data)                          ((0x00000010&(data))>>4)
#define DRF_PAUSE_get_hdcp_2p2_drf_pause(data)                        ((0x00000008&(data))>>3)
#define DRF_PAUSE_get_hdcp_ksvfifo_drf_pause(data)                    ((0x00000004&(data))>>2)
#define DRF_PAUSE_get_hdcp_drf_pause(data)                            ((0x00000002&(data))>>1)
#define DRF_PAUSE_get_audio_drf_pause(data)                           (0x00000001&(data))


#define DRF_FAIL                                                      0x19c
#define DRF_FAIL_reg_addr                                             "0x9803419c"
#define DRF_FAIL_reg                                                  0x9803419c
#define DRF_FAIL_inst_addr                                            "0x0067"
#define DRF_FAIL_inst                                                 0x0067
#define set_DRF_FAIL_reg(data)                                        (*((volatile unsigned int*)DRF_FAIL_reg)=data)
#define get_DRF_FAIL_reg                                              (*((volatile unsigned int*)DRF_FAIL_reg))
#define DRF_FAIL_yuv420_drf_fail_shift                                (4)
#define DRF_FAIL_hdcp_2p2_drf_fail_shift                              (3)
#define DRF_FAIL_hdcp_ksvfifo_drf_fail_shift                          (2)
#define DRF_FAIL_hdcp_drf_fail_shift                                  (1)
#define DRF_FAIL_audio_drf_fail_shift                                 (0)
#define DRF_FAIL_yuv420_drf_fail_mask                                 (0x00000010)
#define DRF_FAIL_hdcp_2p2_drf_fail_mask                               (0x00000008)
#define DRF_FAIL_hdcp_ksvfifo_drf_fail_mask                           (0x00000004)
#define DRF_FAIL_hdcp_drf_fail_mask                                   (0x00000002)
#define DRF_FAIL_audio_drf_fail_mask                                  (0x00000001)
#define DRF_FAIL_yuv420_drf_fail(data)                                (0x00000010&((data)<<4))
#define DRF_FAIL_hdcp_2p2_drf_fail(data)                              (0x00000008&((data)<<3))
#define DRF_FAIL_hdcp_ksvfifo_drf_fail(data)                          (0x00000004&((data)<<2))
#define DRF_FAIL_hdcp_drf_fail(data)                                  (0x00000002&((data)<<1))
#define DRF_FAIL_audio_drf_fail(data)                                 (0x00000001&(data))
#define DRF_FAIL_get_yuv420_drf_fail(data)                            ((0x00000010&(data))>>4)
#define DRF_FAIL_get_hdcp_2p2_drf_fail(data)                          ((0x00000008&(data))>>3)
#define DRF_FAIL_get_hdcp_ksvfifo_drf_fail(data)                      ((0x00000004&(data))>>2)
#define DRF_FAIL_get_hdcp_drf_fail(data)                              ((0x00000002&(data))>>1)
#define DRF_FAIL_get_audio_drf_fail(data)                             (0x00000001&(data))


#define PHY_FIFO_CR                                                   0x1a0
#define PHY_FIFO_CR_reg_addr                                          "0x980341a0"
#define PHY_FIFO_CR_reg                                               0x980341a0
#define PHY_FIFO_CR_inst_addr                                         "0x0068"
#define PHY_FIFO_CR_inst                                              0x0068
#define set_PHY_FIFO_CR_reg(data)                                     (*((volatile unsigned int*)PHY_FIFO_CR_reg)=data)
#define get_PHY_FIFO_CR_reg                                           (*((volatile unsigned int*)PHY_FIFO_CR_reg))
#define PHY_FIFO_CR_port2_rclk_inv_shift                              (30)
#define PHY_FIFO_CR_port2_gclk_inv_shift                              (29)
#define PHY_FIFO_CR_port2_bclk_inv_shift                              (28)
#define PHY_FIFO_CR_port1_rclk_inv_shift                              (27)
#define PHY_FIFO_CR_port1_gclk_inv_shift                              (26)
#define PHY_FIFO_CR_port1_bclk_inv_shift                              (25)
#define PHY_FIFO_CR_port0_rclk_inv_shift                              (24)
#define PHY_FIFO_CR_port0_gclk_inv_shift                              (23)
#define PHY_FIFO_CR_port0_bclk_inv_shift                              (22)
#define PHY_FIFO_CR_port_sel_shift                                    (20)
#define PHY_FIFO_CR_port2_r_flush_shift                               (19)
#define PHY_FIFO_CR_port2_r_afifo_en_shift                            (18)
#define PHY_FIFO_CR_port2_g_flush_shift                               (17)
#define PHY_FIFO_CR_port2_g_afifo_en_shift                            (16)
#define PHY_FIFO_CR_port2_b_flush_shift                               (15)
#define PHY_FIFO_CR_port2_b_afifo_en_shift                            (14)
#define PHY_FIFO_CR_dummy_13_shift                                    (13)
#define PHY_FIFO_CR_port1_r_flush_shift                               (12)
#define PHY_FIFO_CR_port1_r_afifo_en_shift                            (11)
#define PHY_FIFO_CR_port1_g_flush_shift                               (10)
#define PHY_FIFO_CR_port1_g_afifo_en_shift                            (9)
#define PHY_FIFO_CR_port1_b_flush_shift                               (8)
#define PHY_FIFO_CR_port1_b_afifo_en_shift                            (7)
#define PHY_FIFO_CR_dummy_6_shift                                     (6)
#define PHY_FIFO_CR_port0_r_flush_shift                               (5)
#define PHY_FIFO_CR_port0_r_afifo_en_shift                            (4)
#define PHY_FIFO_CR_port0_g_flush_shift                               (3)
#define PHY_FIFO_CR_port0_g_afifo_en_shift                            (2)
#define PHY_FIFO_CR_port0_b_flush_shift                               (1)
#define PHY_FIFO_CR_port0_b_afifo_en_shift                            (0)
#define PHY_FIFO_CR_port2_rclk_inv_mask                               (0x40000000)
#define PHY_FIFO_CR_port2_gclk_inv_mask                               (0x20000000)
#define PHY_FIFO_CR_port2_bclk_inv_mask                               (0x10000000)
#define PHY_FIFO_CR_port1_rclk_inv_mask                               (0x08000000)
#define PHY_FIFO_CR_port1_gclk_inv_mask                               (0x04000000)
#define PHY_FIFO_CR_port1_bclk_inv_mask                               (0x02000000)
#define PHY_FIFO_CR_port0_rclk_inv_mask                               (0x01000000)
#define PHY_FIFO_CR_port0_gclk_inv_mask                               (0x00800000)
#define PHY_FIFO_CR_port0_bclk_inv_mask                               (0x00400000)
#define PHY_FIFO_CR_port_sel_mask                                     (0x00300000)
#define PHY_FIFO_CR_port2_r_flush_mask                                (0x00080000)
#define PHY_FIFO_CR_port2_r_afifo_en_mask                             (0x00040000)
#define PHY_FIFO_CR_port2_g_flush_mask                                (0x00020000)
#define PHY_FIFO_CR_port2_g_afifo_en_mask                             (0x00010000)
#define PHY_FIFO_CR_port2_b_flush_mask                                (0x00008000)
#define PHY_FIFO_CR_port2_b_afifo_en_mask                             (0x00004000)
#define PHY_FIFO_CR_dummy_13_mask                                     (0x00002000)
#define PHY_FIFO_CR_port1_r_flush_mask                                (0x00001000)
#define PHY_FIFO_CR_port1_r_afifo_en_mask                             (0x00000800)
#define PHY_FIFO_CR_port1_g_flush_mask                                (0x00000400)
#define PHY_FIFO_CR_port1_g_afifo_en_mask                             (0x00000200)
#define PHY_FIFO_CR_port1_b_flush_mask                                (0x00000100)
#define PHY_FIFO_CR_port1_b_afifo_en_mask                             (0x00000080)
#define PHY_FIFO_CR_dummy_6_mask                                      (0x00000040)
#define PHY_FIFO_CR_port0_r_flush_mask                                (0x00000020)
#define PHY_FIFO_CR_port0_r_afifo_en_mask                             (0x00000010)
#define PHY_FIFO_CR_port0_g_flush_mask                                (0x00000008)
#define PHY_FIFO_CR_port0_g_afifo_en_mask                             (0x00000004)
#define PHY_FIFO_CR_port0_b_flush_mask                                (0x00000002)
#define PHY_FIFO_CR_port0_b_afifo_en_mask                             (0x00000001)
#define PHY_FIFO_CR_port2_rclk_inv(data)                              (0x40000000&((data)<<30))
#define PHY_FIFO_CR_port2_gclk_inv(data)                              (0x20000000&((data)<<29))
#define PHY_FIFO_CR_port2_bclk_inv(data)                              (0x10000000&((data)<<28))
#define PHY_FIFO_CR_port1_rclk_inv(data)                              (0x08000000&((data)<<27))
#define PHY_FIFO_CR_port1_gclk_inv(data)                              (0x04000000&((data)<<26))
#define PHY_FIFO_CR_port1_bclk_inv(data)                              (0x02000000&((data)<<25))
#define PHY_FIFO_CR_port0_rclk_inv(data)                              (0x01000000&((data)<<24))
#define PHY_FIFO_CR_port0_gclk_inv(data)                              (0x00800000&((data)<<23))
#define PHY_FIFO_CR_port0_bclk_inv(data)                              (0x00400000&((data)<<22))
#define PHY_FIFO_CR_port_sel(data)                                    (0x00300000&((data)<<20))
#define PHY_FIFO_CR_port2_r_flush(data)                               (0x00080000&((data)<<19))
#define PHY_FIFO_CR_port2_r_afifo_en(data)                            (0x00040000&((data)<<18))
#define PHY_FIFO_CR_port2_g_flush(data)                               (0x00020000&((data)<<17))
#define PHY_FIFO_CR_port2_g_afifo_en(data)                            (0x00010000&((data)<<16))
#define PHY_FIFO_CR_port2_b_flush(data)                               (0x00008000&((data)<<15))
#define PHY_FIFO_CR_port2_b_afifo_en(data)                            (0x00004000&((data)<<14))
#define PHY_FIFO_CR_dummy_13(data)                                    (0x00002000&((data)<<13))
#define PHY_FIFO_CR_port1_r_flush(data)                               (0x00001000&((data)<<12))
#define PHY_FIFO_CR_port1_r_afifo_en(data)                            (0x00000800&((data)<<11))
#define PHY_FIFO_CR_port1_g_flush(data)                               (0x00000400&((data)<<10))
#define PHY_FIFO_CR_port1_g_afifo_en(data)                            (0x00000200&((data)<<9))
#define PHY_FIFO_CR_port1_b_flush(data)                               (0x00000100&((data)<<8))
#define PHY_FIFO_CR_port1_b_afifo_en(data)                            (0x00000080&((data)<<7))
#define PHY_FIFO_CR_dummy_6(data)                                     (0x00000040&((data)<<6))
#define PHY_FIFO_CR_port0_r_flush(data)                               (0x00000020&((data)<<5))
#define PHY_FIFO_CR_port0_r_afifo_en(data)                            (0x00000010&((data)<<4))
#define PHY_FIFO_CR_port0_g_flush(data)                               (0x00000008&((data)<<3))
#define PHY_FIFO_CR_port0_g_afifo_en(data)                            (0x00000004&((data)<<2))
#define PHY_FIFO_CR_port0_b_flush(data)                               (0x00000002&((data)<<1))
#define PHY_FIFO_CR_port0_b_afifo_en(data)                            (0x00000001&(data))
#define PHY_FIFO_CR_get_port2_rclk_inv(data)                          ((0x40000000&(data))>>30)
#define PHY_FIFO_CR_get_port2_gclk_inv(data)                          ((0x20000000&(data))>>29)
#define PHY_FIFO_CR_get_port2_bclk_inv(data)                          ((0x10000000&(data))>>28)
#define PHY_FIFO_CR_get_port1_rclk_inv(data)                          ((0x08000000&(data))>>27)
#define PHY_FIFO_CR_get_port1_gclk_inv(data)                          ((0x04000000&(data))>>26)
#define PHY_FIFO_CR_get_port1_bclk_inv(data)                          ((0x02000000&(data))>>25)
#define PHY_FIFO_CR_get_port0_rclk_inv(data)                          ((0x01000000&(data))>>24)
#define PHY_FIFO_CR_get_port0_gclk_inv(data)                          ((0x00800000&(data))>>23)
#define PHY_FIFO_CR_get_port0_bclk_inv(data)                          ((0x00400000&(data))>>22)
#define PHY_FIFO_CR_get_port_sel(data)                                ((0x00300000&(data))>>20)
#define PHY_FIFO_CR_get_port2_r_flush(data)                           ((0x00080000&(data))>>19)
#define PHY_FIFO_CR_get_port2_r_afifo_en(data)                        ((0x00040000&(data))>>18)
#define PHY_FIFO_CR_get_port2_g_flush(data)                           ((0x00020000&(data))>>17)
#define PHY_FIFO_CR_get_port2_g_afifo_en(data)                        ((0x00010000&(data))>>16)
#define PHY_FIFO_CR_get_port2_b_flush(data)                           ((0x00008000&(data))>>15)
#define PHY_FIFO_CR_get_port2_b_afifo_en(data)                        ((0x00004000&(data))>>14)
#define PHY_FIFO_CR_get_dummy_13(data)                                ((0x00002000&(data))>>13)
#define PHY_FIFO_CR_get_port1_r_flush(data)                           ((0x00001000&(data))>>12)
#define PHY_FIFO_CR_get_port1_r_afifo_en(data)                        ((0x00000800&(data))>>11)
#define PHY_FIFO_CR_get_port1_g_flush(data)                           ((0x00000400&(data))>>10)
#define PHY_FIFO_CR_get_port1_g_afifo_en(data)                        ((0x00000200&(data))>>9)
#define PHY_FIFO_CR_get_port1_b_flush(data)                           ((0x00000100&(data))>>8)
#define PHY_FIFO_CR_get_port1_b_afifo_en(data)                        ((0x00000080&(data))>>7)
#define PHY_FIFO_CR_get_dummy_6(data)                                 ((0x00000040&(data))>>6)
#define PHY_FIFO_CR_get_port0_r_flush(data)                           ((0x00000020&(data))>>5)
#define PHY_FIFO_CR_get_port0_r_afifo_en(data)                        ((0x00000010&(data))>>4)
#define PHY_FIFO_CR_get_port0_g_flush(data)                           ((0x00000008&(data))>>3)
#define PHY_FIFO_CR_get_port0_g_afifo_en(data)                        ((0x00000004&(data))>>2)
#define PHY_FIFO_CR_get_port0_b_flush(data)                           ((0x00000002&(data))>>1)
#define PHY_FIFO_CR_get_port0_b_afifo_en(data)                        (0x00000001&(data))


#define PHY_FIFO_SR0                                                  0x1a4
#define PHY_FIFO_SR0_reg_addr                                         "0x980341a4"
#define PHY_FIFO_SR0_reg                                              0x980341a4
#define PHY_FIFO_SR0_inst_addr                                        "0x0069"
#define PHY_FIFO_SR0_inst                                             0x0069
#define set_PHY_FIFO_SR0_reg(data)                                    (*((volatile unsigned int*)PHY_FIFO_SR0_reg)=data)
#define get_PHY_FIFO_SR0_reg                                          (*((volatile unsigned int*)PHY_FIFO_SR0_reg))
#define PHY_FIFO_SR0_port1_r_wrclk_det_timeout_flag_shift             (29)
#define PHY_FIFO_SR0_port1_r_rwclk_det_timeout_flag_shift             (28)
#define PHY_FIFO_SR0_port1_r_wovflow_flag_shift                       (27)
#define PHY_FIFO_SR0_port1_r_rudflow_flag_shift                       (26)
#define PHY_FIFO_SR0_port1_r_rflush_flag_shift                        (25)
#define PHY_FIFO_SR0_port1_g_wrclk_det_timeout_flag_shift             (24)
#define PHY_FIFO_SR0_port1_g_rwclk_det_timeout_flag_shift             (23)
#define PHY_FIFO_SR0_port1_g_wovflow_flag_shift                       (22)
#define PHY_FIFO_SR0_port1_g_rudflow_flag_shift                       (21)
#define PHY_FIFO_SR0_port1_g_rflush_flag_shift                        (20)
#define PHY_FIFO_SR0_port1_b_wrclk_det_timeout_flag_shift             (19)
#define PHY_FIFO_SR0_port1_b_rwclk_det_timeout_flag_shift             (18)
#define PHY_FIFO_SR0_port1_b_wovflow_flag_shift                       (17)
#define PHY_FIFO_SR0_port1_b_rudflow_flag_shift                       (16)
#define PHY_FIFO_SR0_port1_b_rflush_flag_shift                        (15)
#define PHY_FIFO_SR0_port0_r_wrclk_det_timeout_flag_shift             (14)
#define PHY_FIFO_SR0_port0_r_rwclk_det_timeout_flag_shift             (13)
#define PHY_FIFO_SR0_port0_r_wovflow_flag_shift                       (12)
#define PHY_FIFO_SR0_port0_r_rudflow_flag_shift                       (11)
#define PHY_FIFO_SR0_port0_r_rflush_flag_shift                        (10)
#define PHY_FIFO_SR0_port0_g_wrclk_det_timeout_flag_shift             (9)
#define PHY_FIFO_SR0_port0_g_rwclk_det_timeout_flag_shift             (8)
#define PHY_FIFO_SR0_port0_g_wovflow_flag_shift                       (7)
#define PHY_FIFO_SR0_port0_g_rudflow_flag_shift                       (6)
#define PHY_FIFO_SR0_port0_g_rflush_flag_shift                        (5)
#define PHY_FIFO_SR0_port0_b_wrclk_det_timeout_flag_shift             (4)
#define PHY_FIFO_SR0_port0_b_rwclk_det_timeout_flag_shift             (3)
#define PHY_FIFO_SR0_port0_b_wovflow_flag_shift                       (2)
#define PHY_FIFO_SR0_port0_b_rudflow_flag_shift                       (1)
#define PHY_FIFO_SR0_port0_b_rflush_flag_shift                        (0)
#define PHY_FIFO_SR0_port1_r_wrclk_det_timeout_flag_mask              (0x20000000)
#define PHY_FIFO_SR0_port1_r_rwclk_det_timeout_flag_mask              (0x10000000)
#define PHY_FIFO_SR0_port1_r_wovflow_flag_mask                        (0x08000000)
#define PHY_FIFO_SR0_port1_r_rudflow_flag_mask                        (0x04000000)
#define PHY_FIFO_SR0_port1_r_rflush_flag_mask                         (0x02000000)
#define PHY_FIFO_SR0_port1_g_wrclk_det_timeout_flag_mask              (0x01000000)
#define PHY_FIFO_SR0_port1_g_rwclk_det_timeout_flag_mask              (0x00800000)
#define PHY_FIFO_SR0_port1_g_wovflow_flag_mask                        (0x00400000)
#define PHY_FIFO_SR0_port1_g_rudflow_flag_mask                        (0x00200000)
#define PHY_FIFO_SR0_port1_g_rflush_flag_mask                         (0x00100000)
#define PHY_FIFO_SR0_port1_b_wrclk_det_timeout_flag_mask              (0x00080000)
#define PHY_FIFO_SR0_port1_b_rwclk_det_timeout_flag_mask              (0x00040000)
#define PHY_FIFO_SR0_port1_b_wovflow_flag_mask                        (0x00020000)
#define PHY_FIFO_SR0_port1_b_rudflow_flag_mask                        (0x00010000)
#define PHY_FIFO_SR0_port1_b_rflush_flag_mask                         (0x00008000)
#define PHY_FIFO_SR0_port0_r_wrclk_det_timeout_flag_mask              (0x00004000)
#define PHY_FIFO_SR0_port0_r_rwclk_det_timeout_flag_mask              (0x00002000)
#define PHY_FIFO_SR0_port0_r_wovflow_flag_mask                        (0x00001000)
#define PHY_FIFO_SR0_port0_r_rudflow_flag_mask                        (0x00000800)
#define PHY_FIFO_SR0_port0_r_rflush_flag_mask                         (0x00000400)
#define PHY_FIFO_SR0_port0_g_wrclk_det_timeout_flag_mask              (0x00000200)
#define PHY_FIFO_SR0_port0_g_rwclk_det_timeout_flag_mask              (0x00000100)
#define PHY_FIFO_SR0_port0_g_wovflow_flag_mask                        (0x00000080)
#define PHY_FIFO_SR0_port0_g_rudflow_flag_mask                        (0x00000040)
#define PHY_FIFO_SR0_port0_g_rflush_flag_mask                         (0x00000020)
#define PHY_FIFO_SR0_port0_b_wrclk_det_timeout_flag_mask              (0x00000010)
#define PHY_FIFO_SR0_port0_b_rwclk_det_timeout_flag_mask              (0x00000008)
#define PHY_FIFO_SR0_port0_b_wovflow_flag_mask                        (0x00000004)
#define PHY_FIFO_SR0_port0_b_rudflow_flag_mask                        (0x00000002)
#define PHY_FIFO_SR0_port0_b_rflush_flag_mask                         (0x00000001)
#define PHY_FIFO_SR0_port1_r_wrclk_det_timeout_flag(data)             (0x20000000&((data)<<29))
#define PHY_FIFO_SR0_port1_r_rwclk_det_timeout_flag(data)             (0x10000000&((data)<<28))
#define PHY_FIFO_SR0_port1_r_wovflow_flag(data)                       (0x08000000&((data)<<27))
#define PHY_FIFO_SR0_port1_r_rudflow_flag(data)                       (0x04000000&((data)<<26))
#define PHY_FIFO_SR0_port1_r_rflush_flag(data)                        (0x02000000&((data)<<25))
#define PHY_FIFO_SR0_port1_g_wrclk_det_timeout_flag(data)             (0x01000000&((data)<<24))
#define PHY_FIFO_SR0_port1_g_rwclk_det_timeout_flag(data)             (0x00800000&((data)<<23))
#define PHY_FIFO_SR0_port1_g_wovflow_flag(data)                       (0x00400000&((data)<<22))
#define PHY_FIFO_SR0_port1_g_rudflow_flag(data)                       (0x00200000&((data)<<21))
#define PHY_FIFO_SR0_port1_g_rflush_flag(data)                        (0x00100000&((data)<<20))
#define PHY_FIFO_SR0_port1_b_wrclk_det_timeout_flag(data)             (0x00080000&((data)<<19))
#define PHY_FIFO_SR0_port1_b_rwclk_det_timeout_flag(data)             (0x00040000&((data)<<18))
#define PHY_FIFO_SR0_port1_b_wovflow_flag(data)                       (0x00020000&((data)<<17))
#define PHY_FIFO_SR0_port1_b_rudflow_flag(data)                       (0x00010000&((data)<<16))
#define PHY_FIFO_SR0_port1_b_rflush_flag(data)                        (0x00008000&((data)<<15))
#define PHY_FIFO_SR0_port0_r_wrclk_det_timeout_flag(data)             (0x00004000&((data)<<14))
#define PHY_FIFO_SR0_port0_r_rwclk_det_timeout_flag(data)             (0x00002000&((data)<<13))
#define PHY_FIFO_SR0_port0_r_wovflow_flag(data)                       (0x00001000&((data)<<12))
#define PHY_FIFO_SR0_port0_r_rudflow_flag(data)                       (0x00000800&((data)<<11))
#define PHY_FIFO_SR0_port0_r_rflush_flag(data)                        (0x00000400&((data)<<10))
#define PHY_FIFO_SR0_port0_g_wrclk_det_timeout_flag(data)             (0x00000200&((data)<<9))
#define PHY_FIFO_SR0_port0_g_rwclk_det_timeout_flag(data)             (0x00000100&((data)<<8))
#define PHY_FIFO_SR0_port0_g_wovflow_flag(data)                       (0x00000080&((data)<<7))
#define PHY_FIFO_SR0_port0_g_rudflow_flag(data)                       (0x00000040&((data)<<6))
#define PHY_FIFO_SR0_port0_g_rflush_flag(data)                        (0x00000020&((data)<<5))
#define PHY_FIFO_SR0_port0_b_wrclk_det_timeout_flag(data)             (0x00000010&((data)<<4))
#define PHY_FIFO_SR0_port0_b_rwclk_det_timeout_flag(data)             (0x00000008&((data)<<3))
#define PHY_FIFO_SR0_port0_b_wovflow_flag(data)                       (0x00000004&((data)<<2))
#define PHY_FIFO_SR0_port0_b_rudflow_flag(data)                       (0x00000002&((data)<<1))
#define PHY_FIFO_SR0_port0_b_rflush_flag(data)                        (0x00000001&(data))
#define PHY_FIFO_SR0_get_port1_r_wrclk_det_timeout_flag(data)         ((0x20000000&(data))>>29)
#define PHY_FIFO_SR0_get_port1_r_rwclk_det_timeout_flag(data)         ((0x10000000&(data))>>28)
#define PHY_FIFO_SR0_get_port1_r_wovflow_flag(data)                   ((0x08000000&(data))>>27)
#define PHY_FIFO_SR0_get_port1_r_rudflow_flag(data)                   ((0x04000000&(data))>>26)
#define PHY_FIFO_SR0_get_port1_r_rflush_flag(data)                    ((0x02000000&(data))>>25)
#define PHY_FIFO_SR0_get_port1_g_wrclk_det_timeout_flag(data)         ((0x01000000&(data))>>24)
#define PHY_FIFO_SR0_get_port1_g_rwclk_det_timeout_flag(data)         ((0x00800000&(data))>>23)
#define PHY_FIFO_SR0_get_port1_g_wovflow_flag(data)                   ((0x00400000&(data))>>22)
#define PHY_FIFO_SR0_get_port1_g_rudflow_flag(data)                   ((0x00200000&(data))>>21)
#define PHY_FIFO_SR0_get_port1_g_rflush_flag(data)                    ((0x00100000&(data))>>20)
#define PHY_FIFO_SR0_get_port1_b_wrclk_det_timeout_flag(data)         ((0x00080000&(data))>>19)
#define PHY_FIFO_SR0_get_port1_b_rwclk_det_timeout_flag(data)         ((0x00040000&(data))>>18)
#define PHY_FIFO_SR0_get_port1_b_wovflow_flag(data)                   ((0x00020000&(data))>>17)
#define PHY_FIFO_SR0_get_port1_b_rudflow_flag(data)                   ((0x00010000&(data))>>16)
#define PHY_FIFO_SR0_get_port1_b_rflush_flag(data)                    ((0x00008000&(data))>>15)
#define PHY_FIFO_SR0_get_port0_r_wrclk_det_timeout_flag(data)         ((0x00004000&(data))>>14)
#define PHY_FIFO_SR0_get_port0_r_rwclk_det_timeout_flag(data)         ((0x00002000&(data))>>13)
#define PHY_FIFO_SR0_get_port0_r_wovflow_flag(data)                   ((0x00001000&(data))>>12)
#define PHY_FIFO_SR0_get_port0_r_rudflow_flag(data)                   ((0x00000800&(data))>>11)
#define PHY_FIFO_SR0_get_port0_r_rflush_flag(data)                    ((0x00000400&(data))>>10)
#define PHY_FIFO_SR0_get_port0_g_wrclk_det_timeout_flag(data)         ((0x00000200&(data))>>9)
#define PHY_FIFO_SR0_get_port0_g_rwclk_det_timeout_flag(data)         ((0x00000100&(data))>>8)
#define PHY_FIFO_SR0_get_port0_g_wovflow_flag(data)                   ((0x00000080&(data))>>7)
#define PHY_FIFO_SR0_get_port0_g_rudflow_flag(data)                   ((0x00000040&(data))>>6)
#define PHY_FIFO_SR0_get_port0_g_rflush_flag(data)                    ((0x00000020&(data))>>5)
#define PHY_FIFO_SR0_get_port0_b_wrclk_det_timeout_flag(data)         ((0x00000010&(data))>>4)
#define PHY_FIFO_SR0_get_port0_b_rwclk_det_timeout_flag(data)         ((0x00000008&(data))>>3)
#define PHY_FIFO_SR0_get_port0_b_wovflow_flag(data)                   ((0x00000004&(data))>>2)
#define PHY_FIFO_SR0_get_port0_b_rudflow_flag(data)                   ((0x00000002&(data))>>1)
#define PHY_FIFO_SR0_get_port0_b_rflush_flag(data)                    (0x00000001&(data))


#define PHY_FIFO_SR1                                                  0x1a8
#define PHY_FIFO_SR1_reg_addr                                         "0x980341a8"
#define PHY_FIFO_SR1_reg                                              0x980341a8
#define PHY_FIFO_SR1_inst_addr                                        "0x006A"
#define PHY_FIFO_SR1_inst                                             0x006A
#define set_PHY_FIFO_SR1_reg(data)                                    (*((volatile unsigned int*)PHY_FIFO_SR1_reg)=data)
#define get_PHY_FIFO_SR1_reg                                          (*((volatile unsigned int*)PHY_FIFO_SR1_reg))
#define PHY_FIFO_SR1_port2_r_wrclk_det_timeout_flag_shift             (14)
#define PHY_FIFO_SR1_port2_r_rwclk_det_timeout_flag_shift             (13)
#define PHY_FIFO_SR1_port2_r_wovflow_flag_shift                       (12)
#define PHY_FIFO_SR1_port2_r_rudflow_flag_shift                       (11)
#define PHY_FIFO_SR1_port2_r_rflush_flag_shift                        (10)
#define PHY_FIFO_SR1_port2_g_wrclk_det_timeout_flag_shift             (9)
#define PHY_FIFO_SR1_port2_g_rwclk_det_timeout_flag_shift             (8)
#define PHY_FIFO_SR1_port2_g_wovflow_flag_shift                       (7)
#define PHY_FIFO_SR1_port2_g_rudflow_flag_shift                       (6)
#define PHY_FIFO_SR1_port2_g_rflush_flag_shift                        (5)
#define PHY_FIFO_SR1_port2_b_wrclk_det_timeout_flag_shift             (4)
#define PHY_FIFO_SR1_port2_b_rwclk_det_timeout_flag_shift             (3)
#define PHY_FIFO_SR1_port2_b_wovflow_flag_shift                       (2)
#define PHY_FIFO_SR1_port2_b_rudflow_flag_shift                       (1)
#define PHY_FIFO_SR1_port2_b_rflush_flag_shift                        (0)
#define PHY_FIFO_SR1_port2_r_wrclk_det_timeout_flag_mask              (0x00004000)
#define PHY_FIFO_SR1_port2_r_rwclk_det_timeout_flag_mask              (0x00002000)
#define PHY_FIFO_SR1_port2_r_wovflow_flag_mask                        (0x00001000)
#define PHY_FIFO_SR1_port2_r_rudflow_flag_mask                        (0x00000800)
#define PHY_FIFO_SR1_port2_r_rflush_flag_mask                         (0x00000400)
#define PHY_FIFO_SR1_port2_g_wrclk_det_timeout_flag_mask              (0x00000200)
#define PHY_FIFO_SR1_port2_g_rwclk_det_timeout_flag_mask              (0x00000100)
#define PHY_FIFO_SR1_port2_g_wovflow_flag_mask                        (0x00000080)
#define PHY_FIFO_SR1_port2_g_rudflow_flag_mask                        (0x00000040)
#define PHY_FIFO_SR1_port2_g_rflush_flag_mask                         (0x00000020)
#define PHY_FIFO_SR1_port2_b_wrclk_det_timeout_flag_mask              (0x00000010)
#define PHY_FIFO_SR1_port2_b_rwclk_det_timeout_flag_mask              (0x00000008)
#define PHY_FIFO_SR1_port2_b_wovflow_flag_mask                        (0x00000004)
#define PHY_FIFO_SR1_port2_b_rudflow_flag_mask                        (0x00000002)
#define PHY_FIFO_SR1_port2_b_rflush_flag_mask                         (0x00000001)
#define PHY_FIFO_SR1_port2_r_wrclk_det_timeout_flag(data)             (0x00004000&((data)<<14))
#define PHY_FIFO_SR1_port2_r_rwclk_det_timeout_flag(data)             (0x00002000&((data)<<13))
#define PHY_FIFO_SR1_port2_r_wovflow_flag(data)                       (0x00001000&((data)<<12))
#define PHY_FIFO_SR1_port2_r_rudflow_flag(data)                       (0x00000800&((data)<<11))
#define PHY_FIFO_SR1_port2_r_rflush_flag(data)                        (0x00000400&((data)<<10))
#define PHY_FIFO_SR1_port2_g_wrclk_det_timeout_flag(data)             (0x00000200&((data)<<9))
#define PHY_FIFO_SR1_port2_g_rwclk_det_timeout_flag(data)             (0x00000100&((data)<<8))
#define PHY_FIFO_SR1_port2_g_wovflow_flag(data)                       (0x00000080&((data)<<7))
#define PHY_FIFO_SR1_port2_g_rudflow_flag(data)                       (0x00000040&((data)<<6))
#define PHY_FIFO_SR1_port2_g_rflush_flag(data)                        (0x00000020&((data)<<5))
#define PHY_FIFO_SR1_port2_b_wrclk_det_timeout_flag(data)             (0x00000010&((data)<<4))
#define PHY_FIFO_SR1_port2_b_rwclk_det_timeout_flag(data)             (0x00000008&((data)<<3))
#define PHY_FIFO_SR1_port2_b_wovflow_flag(data)                       (0x00000004&((data)<<2))
#define PHY_FIFO_SR1_port2_b_rudflow_flag(data)                       (0x00000002&((data)<<1))
#define PHY_FIFO_SR1_port2_b_rflush_flag(data)                        (0x00000001&(data))
#define PHY_FIFO_SR1_get_port2_r_wrclk_det_timeout_flag(data)         ((0x00004000&(data))>>14)
#define PHY_FIFO_SR1_get_port2_r_rwclk_det_timeout_flag(data)         ((0x00002000&(data))>>13)
#define PHY_FIFO_SR1_get_port2_r_wovflow_flag(data)                   ((0x00001000&(data))>>12)
#define PHY_FIFO_SR1_get_port2_r_rudflow_flag(data)                   ((0x00000800&(data))>>11)
#define PHY_FIFO_SR1_get_port2_r_rflush_flag(data)                    ((0x00000400&(data))>>10)
#define PHY_FIFO_SR1_get_port2_g_wrclk_det_timeout_flag(data)         ((0x00000200&(data))>>9)
#define PHY_FIFO_SR1_get_port2_g_rwclk_det_timeout_flag(data)         ((0x00000100&(data))>>8)
#define PHY_FIFO_SR1_get_port2_g_wovflow_flag(data)                   ((0x00000080&(data))>>7)
#define PHY_FIFO_SR1_get_port2_g_rudflow_flag(data)                   ((0x00000040&(data))>>6)
#define PHY_FIFO_SR1_get_port2_g_rflush_flag(data)                    ((0x00000020&(data))>>5)
#define PHY_FIFO_SR1_get_port2_b_wrclk_det_timeout_flag(data)         ((0x00000010&(data))>>4)
#define PHY_FIFO_SR1_get_port2_b_rwclk_det_timeout_flag(data)         ((0x00000008&(data))>>3)
#define PHY_FIFO_SR1_get_port2_b_wovflow_flag(data)                   ((0x00000004&(data))>>2)
#define PHY_FIFO_SR1_get_port2_b_rudflow_flag(data)                   ((0x00000002&(data))>>1)
#define PHY_FIFO_SR1_get_port2_b_rflush_flag(data)                    (0x00000001&(data))


#define HDMI_CTS_FIFO_CTL                                             0x1ac
#define HDMI_CTS_FIFO_CTL_reg_addr                                    "0x980341ac"
#define HDMI_CTS_FIFO_CTL_reg                                         0x980341ac
#define HDMI_CTS_FIFO_CTL_inst_addr                                   "0x006B"
#define HDMI_CTS_FIFO_CTL_inst                                        0x006B
#define set_HDMI_CTS_FIFO_CTL_reg(data)                               (*((volatile unsigned int*)HDMI_CTS_FIFO_CTL_reg)=data)
#define get_HDMI_CTS_FIFO_CTL_reg                                     (*((volatile unsigned int*)HDMI_CTS_FIFO_CTL_reg))
#define HDMI_CTS_FIFO_CTL_force_ctsfifo_rstn_phy_dbgout_r_shift       (17)
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_bypass_phy_dbgout_r_shift        (16)
#define HDMI_CTS_FIFO_CTL_force_ctsfifo_rstn_phy_dbgout_g_shift       (15)
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_bypass_phy_dbgout_g_shift        (14)
#define HDMI_CTS_FIFO_CTL_force_ctsfifo_rstn_phy_dbgout_b_shift       (13)
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_bypass_phy_dbgout_b_shift        (12)
#define HDMI_CTS_FIFO_CTL_dummy_11_shift                              (11)
#define HDMI_CTS_FIFO_CTL_debug_select_shift                          (10)
#define HDMI_CTS_FIFO_CTL_hdmi_2x_out_sel_shift                       (8)
#define HDMI_CTS_FIFO_CTL_hdmi_test_sel_shift                         (4)
#define HDMI_CTS_FIFO_CTL_hdmi_out_sel_shift                          (3)
#define HDMI_CTS_FIFO_CTL_force_ctsfifo_rstn_hdmi_shift               (2)
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_vsrst_hdmi_shift                 (1)
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_bypass_hdmi_shift                (0)
#define HDMI_CTS_FIFO_CTL_force_ctsfifo_rstn_phy_dbgout_r_mask        (0x00020000)
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_bypass_phy_dbgout_r_mask         (0x00010000)
#define HDMI_CTS_FIFO_CTL_force_ctsfifo_rstn_phy_dbgout_g_mask        (0x00008000)
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_bypass_phy_dbgout_g_mask         (0x00004000)
#define HDMI_CTS_FIFO_CTL_force_ctsfifo_rstn_phy_dbgout_b_mask        (0x00002000)
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_bypass_phy_dbgout_b_mask         (0x00001000)
#define HDMI_CTS_FIFO_CTL_dummy_11_mask                               (0x00000800)
#define HDMI_CTS_FIFO_CTL_debug_select_mask                           (0x00000400)
#define HDMI_CTS_FIFO_CTL_hdmi_2x_out_sel_mask                        (0x00000300)
#define HDMI_CTS_FIFO_CTL_hdmi_test_sel_mask                          (0x000000F0)
#define HDMI_CTS_FIFO_CTL_hdmi_out_sel_mask                           (0x00000008)
#define HDMI_CTS_FIFO_CTL_force_ctsfifo_rstn_hdmi_mask                (0x00000004)
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_vsrst_hdmi_mask                  (0x00000002)
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_bypass_hdmi_mask                 (0x00000001)
#define HDMI_CTS_FIFO_CTL_force_ctsfifo_rstn_phy_dbgout_r(data)       (0x00020000&((data)<<17))
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_bypass_phy_dbgout_r(data)        (0x00010000&((data)<<16))
#define HDMI_CTS_FIFO_CTL_force_ctsfifo_rstn_phy_dbgout_g(data)       (0x00008000&((data)<<15))
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_bypass_phy_dbgout_g(data)        (0x00004000&((data)<<14))
#define HDMI_CTS_FIFO_CTL_force_ctsfifo_rstn_phy_dbgout_b(data)       (0x00002000&((data)<<13))
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_bypass_phy_dbgout_b(data)        (0x00001000&((data)<<12))
#define HDMI_CTS_FIFO_CTL_dummy_11(data)                              (0x00000800&((data)<<11))
#define HDMI_CTS_FIFO_CTL_debug_select(data)                          (0x00000400&((data)<<10))
#define HDMI_CTS_FIFO_CTL_hdmi_2x_out_sel(data)                       (0x00000300&((data)<<8))
#define HDMI_CTS_FIFO_CTL_hdmi_test_sel(data)                         (0x000000F0&((data)<<4))
#define HDMI_CTS_FIFO_CTL_hdmi_out_sel(data)                          (0x00000008&((data)<<3))
#define HDMI_CTS_FIFO_CTL_force_ctsfifo_rstn_hdmi(data)               (0x00000004&((data)<<2))
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_vsrst_hdmi(data)                 (0x00000002&((data)<<1))
#define HDMI_CTS_FIFO_CTL_en_ctsfifo_bypass_hdmi(data)                (0x00000001&(data))
#define HDMI_CTS_FIFO_CTL_get_force_ctsfifo_rstn_phy_dbgout_r(data)   ((0x00020000&(data))>>17)
#define HDMI_CTS_FIFO_CTL_get_en_ctsfifo_bypass_phy_dbgout_r(data)    ((0x00010000&(data))>>16)
#define HDMI_CTS_FIFO_CTL_get_force_ctsfifo_rstn_phy_dbgout_g(data)   ((0x00008000&(data))>>15)
#define HDMI_CTS_FIFO_CTL_get_en_ctsfifo_bypass_phy_dbgout_g(data)    ((0x00004000&(data))>>14)
#define HDMI_CTS_FIFO_CTL_get_force_ctsfifo_rstn_phy_dbgout_b(data)   ((0x00002000&(data))>>13)
#define HDMI_CTS_FIFO_CTL_get_en_ctsfifo_bypass_phy_dbgout_b(data)    ((0x00001000&(data))>>12)
#define HDMI_CTS_FIFO_CTL_get_dummy_11(data)                          ((0x00000800&(data))>>11)
#define HDMI_CTS_FIFO_CTL_get_debug_select(data)                      ((0x00000400&(data))>>10)
#define HDMI_CTS_FIFO_CTL_get_hdmi_2x_out_sel(data)                   ((0x00000300&(data))>>8)
#define HDMI_CTS_FIFO_CTL_get_hdmi_test_sel(data)                     ((0x000000F0&(data))>>4)
#define HDMI_CTS_FIFO_CTL_get_hdmi_out_sel(data)                      ((0x00000008&(data))>>3)
#define HDMI_CTS_FIFO_CTL_get_force_ctsfifo_rstn_hdmi(data)           ((0x00000004&(data))>>2)
#define HDMI_CTS_FIFO_CTL_get_en_ctsfifo_vsrst_hdmi(data)             ((0x00000002&(data))>>1)
#define HDMI_CTS_FIFO_CTL_get_en_ctsfifo_bypass_hdmi(data)            (0x00000001&(data))


#define CBUS_CLK_CTL                                                  0x1b0
#define CBUS_CLK_CTL_reg_addr                                         "0x980341b0"
#define CBUS_CLK_CTL_reg                                              0x980341b0
#define CBUS_CLK_CTL_inst_addr                                        "0x006C"
#define CBUS_CLK_CTL_inst                                             0x006C
#define set_CBUS_CLK_CTL_reg(data)                                    (*((volatile unsigned int*)CBUS_CLK_CTL_reg)=data)
#define get_CBUS_CLK_CTL_reg                                          (*((volatile unsigned int*)CBUS_CLK_CTL_reg))
#define CBUS_CLK_CTL_dummy_6_4_shift                                  (4)
#define CBUS_CLK_CTL_dummy_1_shift                                    (1)
#define CBUS_CLK_CTL_dummy_0_shift                                    (0)
#define CBUS_CLK_CTL_dummy_6_4_mask                                   (0x00000070)
#define CBUS_CLK_CTL_dummy_1_mask                                     (0x00000002)
#define CBUS_CLK_CTL_dummy_0_mask                                     (0x00000001)
#define CBUS_CLK_CTL_dummy_6_4(data)                                  (0x00000070&((data)<<4))
#define CBUS_CLK_CTL_dummy_1(data)                                    (0x00000002&((data)<<1))
#define CBUS_CLK_CTL_dummy_0(data)                                    (0x00000001&(data))
#define CBUS_CLK_CTL_get_dummy_6_4(data)                              ((0x00000070&(data))>>4)
#define CBUS_CLK_CTL_get_dummy_1(data)                                ((0x00000002&(data))>>1)
#define CBUS_CLK_CTL_get_dummy_0(data)                                (0x00000001&(data))


#define HDMI_2P0_CR                                                   0x1b4
#define HDMI_2P0_CR_reg_addr                                          "0x980341b4"
#define HDMI_2P0_CR_reg                                               0x980341b4
#define HDMI_2P0_CR_inst_addr                                         "0x006D"
#define HDMI_2P0_CR_inst                                              0x006D
#define set_HDMI_2P0_CR_reg(data)                                     (*((volatile unsigned int*)HDMI_2P0_CR_reg)=data)
#define get_HDMI_2P0_CR_reg                                           (*((volatile unsigned int*)HDMI_2P0_CR_reg))
#define HDMI_2P0_CR_gating_en_shift                                   (8)
#define HDMI_2P0_CR_ctr_char_num_shift                                (1)
#define HDMI_2P0_CR_hdmi_2p0_en_shift                                 (0)
#define HDMI_2P0_CR_gating_en_mask                                    (0x00000100)
#define HDMI_2P0_CR_ctr_char_num_mask                                 (0x000000FE)
#define HDMI_2P0_CR_hdmi_2p0_en_mask                                  (0x00000001)
#define HDMI_2P0_CR_gating_en(data)                                   (0x00000100&((data)<<8))
#define HDMI_2P0_CR_ctr_char_num(data)                                (0x000000FE&((data)<<1))
#define HDMI_2P0_CR_hdmi_2p0_en(data)                                 (0x00000001&(data))
#define HDMI_2P0_CR_get_gating_en(data)                               ((0x00000100&(data))>>8)
#define HDMI_2P0_CR_get_ctr_char_num(data)                            ((0x000000FE&(data))>>1)
#define HDMI_2P0_CR_get_hdmi_2p0_en(data)                             (0x00000001&(data))


#define SCR_CR                                                        0x1b8
#define SCR_CR_reg_addr                                               "0x980341b8"
#define SCR_CR_reg                                                    0x980341b8
#define SCR_CR_inst_addr                                              "0x006E"
#define SCR_CR_inst                                                   0x006E
#define set_SCR_CR_reg(data)                                          (*((volatile unsigned int*)SCR_CR_reg)=data)
#define get_SCR_CR_reg                                                (*((volatile unsigned int*)SCR_CR_reg))
#define SCR_CR_char_lock_shift                                        (17)
#define SCR_CR_uscr_fall_bound_err_r_shift                            (16)
#define SCR_CR_uscr_fall_bound_err_g_shift                            (15)
#define SCR_CR_uscr_fall_bound_err_b_shift                            (14)
#define SCR_CR_uscr_per_glitch_r_shift                                (13)
#define SCR_CR_uscr_per_glitch_g_shift                                (12)
#define SCR_CR_uscr_per_glitch_b_shift                                (11)
#define SCR_CR_uscr_char_flag_r_shift                                 (10)
#define SCR_CR_uscr_char_flag_g_shift                                 (9)
#define SCR_CR_uscr_char_flag_b_shift                                 (8)
#define SCR_CR_uscr_num_shift                                         (4)
#define SCR_CR_dummy_3_2_shift                                        (2)
#define SCR_CR_scr_en_fw_shift                                        (1)
#define SCR_CR_scr_auto_shift                                         (0)
#define SCR_CR_char_lock_mask                                         (0x00020000)
#define SCR_CR_uscr_fall_bound_err_r_mask                             (0x00010000)
#define SCR_CR_uscr_fall_bound_err_g_mask                             (0x00008000)
#define SCR_CR_uscr_fall_bound_err_b_mask                             (0x00004000)
#define SCR_CR_uscr_per_glitch_r_mask                                 (0x00002000)
#define SCR_CR_uscr_per_glitch_g_mask                                 (0x00001000)
#define SCR_CR_uscr_per_glitch_b_mask                                 (0x00000800)
#define SCR_CR_uscr_char_flag_r_mask                                  (0x00000400)
#define SCR_CR_uscr_char_flag_g_mask                                  (0x00000200)
#define SCR_CR_uscr_char_flag_b_mask                                  (0x00000100)
#define SCR_CR_uscr_num_mask                                          (0x000000F0)
#define SCR_CR_dummy_3_2_mask                                         (0x0000000C)
#define SCR_CR_scr_en_fw_mask                                         (0x00000002)
#define SCR_CR_scr_auto_mask                                          (0x00000001)
#define SCR_CR_char_lock(data)                                        (0x00020000&((data)<<17))
#define SCR_CR_uscr_fall_bound_err_r(data)                            (0x00010000&((data)<<16))
#define SCR_CR_uscr_fall_bound_err_g(data)                            (0x00008000&((data)<<15))
#define SCR_CR_uscr_fall_bound_err_b(data)                            (0x00004000&((data)<<14))
#define SCR_CR_uscr_per_glitch_r(data)                                (0x00002000&((data)<<13))
#define SCR_CR_uscr_per_glitch_g(data)                                (0x00001000&((data)<<12))
#define SCR_CR_uscr_per_glitch_b(data)                                (0x00000800&((data)<<11))
#define SCR_CR_uscr_char_flag_r(data)                                 (0x00000400&((data)<<10))
#define SCR_CR_uscr_char_flag_g(data)                                 (0x00000200&((data)<<9))
#define SCR_CR_uscr_char_flag_b(data)                                 (0x00000100&((data)<<8))
#define SCR_CR_uscr_num(data)                                         (0x000000F0&((data)<<4))
#define SCR_CR_dummy_3_2(data)                                        (0x0000000C&((data)<<2))
#define SCR_CR_scr_en_fw(data)                                        (0x00000002&((data)<<1))
#define SCR_CR_scr_auto(data)                                         (0x00000001&(data))
#define SCR_CR_get_char_lock(data)                                    ((0x00020000&(data))>>17)
#define SCR_CR_get_uscr_fall_bound_err_r(data)                        ((0x00010000&(data))>>16)
#define SCR_CR_get_uscr_fall_bound_err_g(data)                        ((0x00008000&(data))>>15)
#define SCR_CR_get_uscr_fall_bound_err_b(data)                        ((0x00004000&(data))>>14)
#define SCR_CR_get_uscr_per_glitch_r(data)                            ((0x00002000&(data))>>13)
#define SCR_CR_get_uscr_per_glitch_g(data)                            ((0x00001000&(data))>>12)
#define SCR_CR_get_uscr_per_glitch_b(data)                            ((0x00000800&(data))>>11)
#define SCR_CR_get_uscr_char_flag_r(data)                             ((0x00000400&(data))>>10)
#define SCR_CR_get_uscr_char_flag_g(data)                             ((0x00000200&(data))>>9)
#define SCR_CR_get_uscr_char_flag_b(data)                             ((0x00000100&(data))>>8)
#define SCR_CR_get_uscr_num(data)                                     ((0x000000F0&(data))>>4)
#define SCR_CR_get_dummy_3_2(data)                                    ((0x0000000C&(data))>>2)
#define SCR_CR_get_scr_en_fw(data)                                    ((0x00000002&(data))>>1)
#define SCR_CR_get_scr_auto(data)                                     (0x00000001&(data))


#define CERCR                                                         0x1bc
#define CERCR_reg_addr                                                "0x980341bc"
#define CERCR_reg                                                     0x980341bc
#define CERCR_inst_addr                                               "0x006F"
#define CERCR_inst                                                    0x006F
#define set_CERCR_reg(data)                                           (*((volatile unsigned int*)CERCR_reg)=data)
#define get_CERCR_reg                                                 (*((volatile unsigned int*)CERCR_reg))
#define CERCR_ch_locked_reset_shift                                   (28)
#define CERCR_ch2_over_max_err_num_shift                              (27)
#define CERCR_ch1_over_max_err_num_shift                              (26)
#define CERCR_ch0_over_max_err_num_shift                              (25)
#define CERCR_max_err_num_shift                                       (15)
#define CERCR_valid_reset_shift                                       (14)
#define CERCR_reset_err_det_shift                                     (13)
#define CERCR_keep_err_det_shift                                      (12)
#define CERCR_refer_implem_shift                                      (11)
#define CERCR_reset_shift                                             (10)
#define CERCR_period_shift                                            (4)
#define CERCR_dummy_3_2_shift                                         (2)
#define CERCR_mode_shift                                              (1)
#define CERCR_en_shift                                                (0)
#define CERCR_ch_locked_reset_mask                                    (0x10000000)
#define CERCR_ch2_over_max_err_num_mask                               (0x08000000)
#define CERCR_ch1_over_max_err_num_mask                               (0x04000000)
#define CERCR_ch0_over_max_err_num_mask                               (0x02000000)
#define CERCR_max_err_num_mask                                        (0x01FF8000)
#define CERCR_valid_reset_mask                                        (0x00004000)
#define CERCR_reset_err_det_mask                                      (0x00002000)
#define CERCR_keep_err_det_mask                                       (0x00001000)
#define CERCR_refer_implem_mask                                       (0x00000800)
#define CERCR_reset_mask                                              (0x00000400)
#define CERCR_period_mask                                             (0x000003F0)
#define CERCR_dummy_3_2_mask                                          (0x0000000C)
#define CERCR_mode_mask                                               (0x00000002)
#define CERCR_en_mask                                                 (0x00000001)
#define CERCR_ch_locked_reset(data)                                   (0x10000000&((data)<<28))
#define CERCR_ch2_over_max_err_num(data)                              (0x08000000&((data)<<27))
#define CERCR_ch1_over_max_err_num(data)                              (0x04000000&((data)<<26))
#define CERCR_ch0_over_max_err_num(data)                              (0x02000000&((data)<<25))
#define CERCR_max_err_num(data)                                       (0x01FF8000&((data)<<15))
#define CERCR_valid_reset(data)                                       (0x00004000&((data)<<14))
#define CERCR_reset_err_det(data)                                     (0x00002000&((data)<<13))
#define CERCR_keep_err_det(data)                                      (0x00001000&((data)<<12))
#define CERCR_refer_implem(data)                                      (0x00000800&((data)<<11))
#define CERCR_reset(data)                                             (0x00000400&((data)<<10))
#define CERCR_period(data)                                            (0x000003F0&((data)<<4))
#define CERCR_dummy_3_2(data)                                         (0x0000000C&((data)<<2))
#define CERCR_mode(data)                                              (0x00000002&((data)<<1))
#define CERCR_en(data)                                                (0x00000001&(data))
#define CERCR_get_ch_locked_reset(data)                               ((0x10000000&(data))>>28)
#define CERCR_get_ch2_over_max_err_num(data)                          ((0x08000000&(data))>>27)
#define CERCR_get_ch1_over_max_err_num(data)                          ((0x04000000&(data))>>26)
#define CERCR_get_ch0_over_max_err_num(data)                          ((0x02000000&(data))>>25)
#define CERCR_get_max_err_num(data)                                   ((0x01FF8000&(data))>>15)
#define CERCR_get_valid_reset(data)                                   ((0x00004000&(data))>>14)
#define CERCR_get_reset_err_det(data)                                 ((0x00002000&(data))>>13)
#define CERCR_get_keep_err_det(data)                                  ((0x00001000&(data))>>12)
#define CERCR_get_refer_implem(data)                                  ((0x00000800&(data))>>11)
#define CERCR_get_reset(data)                                         ((0x00000400&(data))>>10)
#define CERCR_get_period(data)                                        ((0x000003F0&(data))>>4)
#define CERCR_get_dummy_3_2(data)                                     ((0x0000000C&(data))>>2)
#define CERCR_get_mode(data)                                          ((0x00000002&(data))>>1)
#define CERCR_get_en(data)                                            (0x00000001&(data))


#define CERSR0                                                        0x1c0
#define CERSR0_reg_addr                                               "0x980341c0"
#define CERSR0_reg                                                    0x980341c0
#define CERSR0_inst_addr                                              "0x0070"
#define CERSR0_inst                                                   0x0070
#define set_CERSR0_reg(data)                                          (*((volatile unsigned int*)CERSR0_reg)=data)
#define get_CERSR0_reg                                                (*((volatile unsigned int*)CERSR0_reg))
#define CERSR0_err_cnt1_video_shift                                   (16)
#define CERSR0_err_cnt0_video_shift                                   (0)
#define CERSR0_err_cnt1_video_mask                                    (0x7FFF0000)
#define CERSR0_err_cnt0_video_mask                                    (0x00007FFF)
#define CERSR0_err_cnt1_video(data)                                   (0x7FFF0000&((data)<<16))
#define CERSR0_err_cnt0_video(data)                                   (0x00007FFF&(data))
#define CERSR0_get_err_cnt1_video(data)                               ((0x7FFF0000&(data))>>16)
#define CERSR0_get_err_cnt0_video(data)                               (0x00007FFF&(data))


#define CERSR1                                                        0x1c4
#define CERSR1_reg_addr                                               "0x980341c4"
#define CERSR1_reg                                                    0x980341c4
#define CERSR1_inst_addr                                              "0x0071"
#define CERSR1_inst                                                   0x0071
#define set_CERSR1_reg(data)                                          (*((volatile unsigned int*)CERSR1_reg)=data)
#define get_CERSR1_reg                                                (*((volatile unsigned int*)CERSR1_reg))
#define CERSR1_err_cnt0_pkt_shift                                     (16)
#define CERSR1_err_cnt2_video_shift                                   (0)
#define CERSR1_err_cnt0_pkt_mask                                      (0x7FFF0000)
#define CERSR1_err_cnt2_video_mask                                    (0x00007FFF)
#define CERSR1_err_cnt0_pkt(data)                                     (0x7FFF0000&((data)<<16))
#define CERSR1_err_cnt2_video(data)                                   (0x00007FFF&(data))
#define CERSR1_get_err_cnt0_pkt(data)                                 ((0x7FFF0000&(data))>>16)
#define CERSR1_get_err_cnt2_video(data)                               (0x00007FFF&(data))


#define CERSR2                                                        0x1c8
#define CERSR2_reg_addr                                               "0x980341c8"
#define CERSR2_reg                                                    0x980341c8
#define CERSR2_inst_addr                                              "0x0072"
#define CERSR2_inst                                                   0x0072
#define set_CERSR2_reg(data)                                          (*((volatile unsigned int*)CERSR2_reg)=data)
#define get_CERSR2_reg                                                (*((volatile unsigned int*)CERSR2_reg))
#define CERSR2_err_cnt2_pkt_shift                                     (16)
#define CERSR2_err_cnt1_pkt_shift                                     (0)
#define CERSR2_err_cnt2_pkt_mask                                      (0x7FFF0000)
#define CERSR2_err_cnt1_pkt_mask                                      (0x00007FFF)
#define CERSR2_err_cnt2_pkt(data)                                     (0x7FFF0000&((data)<<16))
#define CERSR2_err_cnt1_pkt(data)                                     (0x00007FFF&(data))
#define CERSR2_get_err_cnt2_pkt(data)                                 ((0x7FFF0000&(data))>>16)
#define CERSR2_get_err_cnt1_pkt(data)                                 (0x00007FFF&(data))


#define CERSR3                                                        0x1cc
#define CERSR3_reg_addr                                               "0x980341cc"
#define CERSR3_reg                                                    0x980341cc
#define CERSR3_inst_addr                                              "0x0073"
#define CERSR3_inst                                                   0x0073
#define set_CERSR3_reg(data)                                          (*((volatile unsigned int*)CERSR3_reg)=data)
#define get_CERSR3_reg                                                (*((volatile unsigned int*)CERSR3_reg))
#define CERSR3_err_cnt1_ctr_shift                                     (16)
#define CERSR3_err_cnt0_ctr_shift                                     (0)
#define CERSR3_err_cnt1_ctr_mask                                      (0x7FFF0000)
#define CERSR3_err_cnt0_ctr_mask                                      (0x00007FFF)
#define CERSR3_err_cnt1_ctr(data)                                     (0x7FFF0000&((data)<<16))
#define CERSR3_err_cnt0_ctr(data)                                     (0x00007FFF&(data))
#define CERSR3_get_err_cnt1_ctr(data)                                 ((0x7FFF0000&(data))>>16)
#define CERSR3_get_err_cnt0_ctr(data)                                 (0x00007FFF&(data))


#define CERSR4                                                        0x1d0
#define CERSR4_reg_addr                                               "0x980341d0"
#define CERSR4_reg                                                    0x980341d0
#define CERSR4_inst_addr                                              "0x0074"
#define CERSR4_inst                                                   0x0074
#define set_CERSR4_reg(data)                                          (*((volatile unsigned int*)CERSR4_reg)=data)
#define get_CERSR4_reg                                                (*((volatile unsigned int*)CERSR4_reg))
#define CERSR4_err_cnt2_ctr_shift                                     (0)
#define CERSR4_err_cnt2_ctr_mask                                      (0x00007FFF)
#define CERSR4_err_cnt2_ctr(data)                                     (0x00007FFF&(data))
#define CERSR4_get_err_cnt2_ctr(data)                                 (0x00007FFF&(data))


#define YUV420_CR                                                     0x1d4
#define YUV420_CR_reg_addr                                            "0x980341d4"
#define YUV420_CR_reg                                                 0x980341d4
#define YUV420_CR_inst_addr                                           "0x0075"
#define YUV420_CR_inst                                                0x0075
#define set_YUV420_CR_reg(data)                                       (*((volatile unsigned int*)YUV420_CR_reg)=data)
#define get_YUV420_CR_reg                                             (*((volatile unsigned int*)YUV420_CR_reg))
#define YUV420_CR_fifo_over_flag_shift                                (2)
#define YUV420_CR_fifo_under_flag_shift                               (1)
#define YUV420_CR_en_shift                                            (0)
#define YUV420_CR_fifo_over_flag_mask                                 (0x00000004)
#define YUV420_CR_fifo_under_flag_mask                                (0x00000002)
#define YUV420_CR_en_mask                                             (0x00000001)
#define YUV420_CR_fifo_over_flag(data)                                (0x00000004&((data)<<2))
#define YUV420_CR_fifo_under_flag(data)                               (0x00000002&((data)<<1))
#define YUV420_CR_en(data)                                            (0x00000001&(data))
#define YUV420_CR_get_fifo_over_flag(data)                            ((0x00000004&(data))>>2)
#define YUV420_CR_get_fifo_under_flag(data)                           ((0x00000002&(data))>>1)
#define YUV420_CR_get_en(data)                                        (0x00000001&(data))


#define SCDC_CR                                                       0x1d8
#define SCDC_CR_reg_addr                                              "0x980341d8"
#define SCDC_CR_reg                                                   0x980341d8
#define SCDC_CR_inst_addr                                             "0x0076"
#define SCDC_CR_inst                                                  0x0076
#define set_SCDC_CR_reg(data)                                         (*((volatile unsigned int*)SCDC_CR_reg)=data)
#define get_SCDC_CR_reg                                               (*((volatile unsigned int*)SCDC_CR_reg))
#define SCDC_CR_scdc_reset_shift                                      (5)
#define SCDC_CR_dummy_4_2_shift                                       (2)
#define SCDC_CR_maddf_shift                                           (1)
#define SCDC_CR_scdc_en_shift                                         (0)
#define SCDC_CR_scdc_reset_mask                                       (0x00000020)
#define SCDC_CR_dummy_4_2_mask                                        (0x0000001C)
#define SCDC_CR_maddf_mask                                            (0x00000002)
#define SCDC_CR_scdc_en_mask                                          (0x00000001)
#define SCDC_CR_scdc_reset(data)                                      (0x00000020&((data)<<5))
#define SCDC_CR_dummy_4_2(data)                                       (0x0000001C&((data)<<2))
#define SCDC_CR_maddf(data)                                           (0x00000002&((data)<<1))
#define SCDC_CR_scdc_en(data)                                         (0x00000001&(data))
#define SCDC_CR_get_scdc_reset(data)                                  ((0x00000020&(data))>>5)
#define SCDC_CR_get_dummy_4_2(data)                                   ((0x0000001C&(data))>>2)
#define SCDC_CR_get_maddf(data)                                       ((0x00000002&(data))>>1)
#define SCDC_CR_get_scdc_en(data)                                     (0x00000001&(data))


#define SCDC_PCR                                                      0x1dc
#define SCDC_PCR_reg_addr                                             "0x980341dc"
#define SCDC_PCR_reg                                                  0x980341dc
#define SCDC_PCR_inst_addr                                            "0x0077"
#define SCDC_PCR_inst                                                 0x0077
#define set_SCDC_PCR_reg(data)                                        (*((volatile unsigned int*)SCDC_PCR_reg)=data)
#define get_SCDC_PCR_reg                                              (*((volatile unsigned int*)SCDC_PCR_reg))
#define SCDC_PCR_timeout_flag_shift                                   (31)
#define SCDC_PCR_timeout_sel_shift                                    (29)
#define SCDC_PCR_status_flag_shift                                    (28)
#define SCDC_PCR_config_flag_shift                                    (27)
#define SCDC_PCR_scrambler_status_flag_shift                          (26)
#define SCDC_PCR_tmds_config_flag_shift                               (25)
#define SCDC_PCR_i2c_scl_dly_sel_shift                                (21)
#define SCDC_PCR_i2c_sda_dly_sel_shift                                (17)
#define SCDC_PCR_i2c_free_num_shift                                   (10)
#define SCDC_PCR_rr_retry_sel_shift                                   (8)
#define SCDC_PCR_dbnc_level_sel_shift                                 (7)
#define SCDC_PCR_dummy_6_1_shift                                      (1)
#define SCDC_PCR_apai_shift                                           (0)
#define SCDC_PCR_timeout_flag_mask                                    (0x80000000)
#define SCDC_PCR_timeout_sel_mask                                     (0x60000000)
#define SCDC_PCR_status_flag_mask                                     (0x10000000)
#define SCDC_PCR_config_flag_mask                                     (0x08000000)
#define SCDC_PCR_scrambler_status_flag_mask                           (0x04000000)
#define SCDC_PCR_tmds_config_flag_mask                                (0x02000000)
#define SCDC_PCR_i2c_scl_dly_sel_mask                                 (0x01E00000)
#define SCDC_PCR_i2c_sda_dly_sel_mask                                 (0x001E0000)
#define SCDC_PCR_i2c_free_num_mask                                    (0x0001FC00)
#define SCDC_PCR_rr_retry_sel_mask                                    (0x00000300)
#define SCDC_PCR_dbnc_level_sel_mask                                  (0x00000080)
#define SCDC_PCR_dummy_6_1_mask                                       (0x0000007E)
#define SCDC_PCR_apai_mask                                            (0x00000001)
#define SCDC_PCR_timeout_flag(data)                                   (0x80000000&((data)<<31))
#define SCDC_PCR_timeout_sel(data)                                    (0x60000000&((data)<<29))
#define SCDC_PCR_status_flag(data)                                    (0x10000000&((data)<<28))
#define SCDC_PCR_config_flag(data)                                    (0x08000000&((data)<<27))
#define SCDC_PCR_scrambler_status_flag(data)                          (0x04000000&((data)<<26))
#define SCDC_PCR_tmds_config_flag(data)                               (0x02000000&((data)<<25))
#define SCDC_PCR_i2c_scl_dly_sel(data)                                (0x01E00000&((data)<<21))
#define SCDC_PCR_i2c_sda_dly_sel(data)                                (0x001E0000&((data)<<17))
#define SCDC_PCR_i2c_free_num(data)                                   (0x0001FC00&((data)<<10))
#define SCDC_PCR_rr_retry_sel(data)                                   (0x00000300&((data)<<8))
#define SCDC_PCR_dbnc_level_sel(data)                                 (0x00000080&((data)<<7))
#define SCDC_PCR_dummy_6_1(data)                                      (0x0000007E&((data)<<1))
#define SCDC_PCR_apai(data)                                           (0x00000001&(data))
#define SCDC_PCR_get_timeout_flag(data)                               ((0x80000000&(data))>>31)
#define SCDC_PCR_get_timeout_sel(data)                                ((0x60000000&(data))>>29)
#define SCDC_PCR_get_status_flag(data)                                ((0x10000000&(data))>>28)
#define SCDC_PCR_get_config_flag(data)                                ((0x08000000&(data))>>27)
#define SCDC_PCR_get_scrambler_status_flag(data)                      ((0x04000000&(data))>>26)
#define SCDC_PCR_get_tmds_config_flag(data)                           ((0x02000000&(data))>>25)
#define SCDC_PCR_get_i2c_scl_dly_sel(data)                            ((0x01E00000&(data))>>21)
#define SCDC_PCR_get_i2c_sda_dly_sel(data)                            ((0x001E0000&(data))>>17)
#define SCDC_PCR_get_i2c_free_num(data)                               ((0x0001FC00&(data))>>10)
#define SCDC_PCR_get_rr_retry_sel(data)                               ((0x00000300&(data))>>8)
#define SCDC_PCR_get_dbnc_level_sel(data)                             ((0x00000080&(data))>>7)
#define SCDC_PCR_get_dummy_6_1(data)                                  ((0x0000007E&(data))>>1)
#define SCDC_PCR_get_apai(data)                                       (0x00000001&(data))


#define SCDC_AP                                                       0x1e0
#define SCDC_AP_reg_addr                                              "0x980341e0"
#define SCDC_AP_reg                                                   0x980341e0
#define SCDC_AP_inst_addr                                             "0x0078"
#define SCDC_AP_inst                                                  0x0078
#define set_SCDC_AP_reg(data)                                         (*((volatile unsigned int*)SCDC_AP_reg)=data)
#define get_SCDC_AP_reg                                               (*((volatile unsigned int*)SCDC_AP_reg))
#define SCDC_AP_ap1_shift                                             (0)
#define SCDC_AP_ap1_mask                                              (0x000000FF)
#define SCDC_AP_ap1(data)                                             (0x000000FF&(data))
#define SCDC_AP_get_ap1(data)                                         (0x000000FF&(data))


#define SCDC_DP                                                       0x1e4
#define SCDC_DP_reg_addr                                              "0x980341e4"
#define SCDC_DP_reg                                                   0x980341e4
#define SCDC_DP_inst_addr                                             "0x0079"
#define SCDC_DP_inst                                                  0x0079
#define set_SCDC_DP_reg(data)                                         (*((volatile unsigned int*)SCDC_DP_reg)=data)
#define get_SCDC_DP_reg                                               (*((volatile unsigned int*)SCDC_DP_reg))
#define SCDC_DP_dp1_shift                                             (0)
#define SCDC_DP_dp1_mask                                              (0x000000FF)
#define SCDC_DP_dp1(data)                                             (0x000000FF&(data))
#define SCDC_DP_get_dp1(data)                                         (0x000000FF&(data))


#define CLKDETCR                                                      0x1e8
#define CLKDETCR_reg_addr                                             "0x980341e8"
#define CLKDETCR_reg                                                  0x980341e8
#define CLKDETCR_inst_addr                                            "0x007A"
#define CLKDETCR_inst                                                 0x007A
#define set_CLKDETCR_reg(data)                                        (*((volatile unsigned int*)CLKDETCR_reg)=data)
#define get_CLKDETCR_reg                                              (*((volatile unsigned int*)CLKDETCR_reg))
#define CLKDETCR_clock_det_en_shift                                   (0)
#define CLKDETCR_clock_det_en_mask                                    (0x00000001)
#define CLKDETCR_clock_det_en(data)                                   (0x00000001&(data))
#define CLKDETCR_get_clock_det_en(data)                               (0x00000001&(data))


#define CLKDETSR                                                      0x1ec
#define CLKDETSR_reg_addr                                             "0x980341ec"
#define CLKDETSR_reg                                                  0x980341ec
#define CLKDETSR_inst_addr                                            "0x007B"
#define CLKDETSR_inst                                                 0x007B
#define set_CLKDETSR_reg(data)                                        (*((volatile unsigned int*)CLKDETSR_reg)=data)
#define get_CLKDETSR_reg                                              (*((volatile unsigned int*)CLKDETSR_reg))
#define CLKDETSR_en_tmds_chg_irq_shift                                (5)
#define CLKDETSR_tmds_chg_irq_shift                                   (4)
#define CLKDETSR_dummy_3_2_shift                                      (2)
#define CLKDETSR_clk_not_in_target_irq_en_shift                       (1)
#define CLKDETSR_clk_not_in_target_shift                              (0)
#define CLKDETSR_en_tmds_chg_irq_mask                                 (0x00000020)
#define CLKDETSR_tmds_chg_irq_mask                                    (0x00000010)
#define CLKDETSR_dummy_3_2_mask                                       (0x0000000C)
#define CLKDETSR_clk_not_in_target_irq_en_mask                        (0x00000002)
#define CLKDETSR_clk_not_in_target_mask                               (0x00000001)
#define CLKDETSR_en_tmds_chg_irq(data)                                (0x00000020&((data)<<5))
#define CLKDETSR_tmds_chg_irq(data)                                   (0x00000010&((data)<<4))
#define CLKDETSR_dummy_3_2(data)                                      (0x0000000C&((data)<<2))
#define CLKDETSR_clk_not_in_target_irq_en(data)                       (0x00000002&((data)<<1))
#define CLKDETSR_clk_not_in_target(data)                              (0x00000001&(data))
#define CLKDETSR_get_en_tmds_chg_irq(data)                            ((0x00000020&(data))>>5)
#define CLKDETSR_get_tmds_chg_irq(data)                               ((0x00000010&(data))>>4)
#define CLKDETSR_get_dummy_3_2(data)                                  ((0x0000000C&(data))>>2)
#define CLKDETSR_get_clk_not_in_target_irq_en(data)                   ((0x00000002&(data))>>1)
#define CLKDETSR_get_clk_not_in_target(data)                          (0x00000001&(data))


#define GDI_TMDSCLK_SETTING_00                                        0x1f0
#define GDI_TMDSCLK_SETTING_00_reg_addr                               "0x980341f0"
#define GDI_TMDSCLK_SETTING_00_reg                                    0x980341f0
#define GDI_TMDSCLK_SETTING_00_inst_addr                              "0x007C"
#define GDI_TMDSCLK_SETTING_00_inst                                   0x007C
#define set_GDI_TMDSCLK_SETTING_00_reg(data)                          (*((volatile unsigned int*)GDI_TMDSCLK_SETTING_00_reg)=data)
#define get_GDI_TMDSCLK_SETTING_00_reg                                (*((volatile unsigned int*)GDI_TMDSCLK_SETTING_00_reg))
#define GDI_TMDSCLK_SETTING_00_dclk_cnt_start_shift                   (16)
#define GDI_TMDSCLK_SETTING_00_dclk_cnt_end_shift                     (0)
#define GDI_TMDSCLK_SETTING_00_dclk_cnt_start_mask                    (0x0FFF0000)
#define GDI_TMDSCLK_SETTING_00_dclk_cnt_end_mask                      (0x00000FFF)
#define GDI_TMDSCLK_SETTING_00_dclk_cnt_start(data)                   (0x0FFF0000&((data)<<16))
#define GDI_TMDSCLK_SETTING_00_dclk_cnt_end(data)                     (0x00000FFF&(data))
#define GDI_TMDSCLK_SETTING_00_get_dclk_cnt_start(data)               ((0x0FFF0000&(data))>>16)
#define GDI_TMDSCLK_SETTING_00_get_dclk_cnt_end(data)                 (0x00000FFF&(data))


#define GDI_TMDSCLK_SETTING_01                                        0x1f4
#define GDI_TMDSCLK_SETTING_01_reg_addr                               "0x980341f4"
#define GDI_TMDSCLK_SETTING_01_reg                                    0x980341f4
#define GDI_TMDSCLK_SETTING_01_inst_addr                              "0x007D"
#define GDI_TMDSCLK_SETTING_01_inst                                   0x007D
#define set_GDI_TMDSCLK_SETTING_01_reg(data)                          (*((volatile unsigned int*)GDI_TMDSCLK_SETTING_01_reg)=data)
#define get_GDI_TMDSCLK_SETTING_01_reg                                (*((volatile unsigned int*)GDI_TMDSCLK_SETTING_01_reg))
#define GDI_TMDSCLK_SETTING_01_target_for_maximum_clk_counter_shift   (16)
#define GDI_TMDSCLK_SETTING_01_target_for_minimum_clk_counter_shift   (0)
#define GDI_TMDSCLK_SETTING_01_target_for_maximum_clk_counter_mask    (0x0FFF0000)
#define GDI_TMDSCLK_SETTING_01_target_for_minimum_clk_counter_mask    (0x00000FFF)
#define GDI_TMDSCLK_SETTING_01_target_for_maximum_clk_counter(data)   (0x0FFF0000&((data)<<16))
#define GDI_TMDSCLK_SETTING_01_target_for_minimum_clk_counter(data)   (0x00000FFF&(data))
#define GDI_TMDSCLK_SETTING_01_get_target_for_maximum_clk_counter(data)  ((0x0FFF0000&(data))>>16)
#define GDI_TMDSCLK_SETTING_01_get_target_for_minimum_clk_counter(data)  (0x00000FFF&(data))


#define GDI_TMDSCLK_SETTING_02                                        0x1f8
#define GDI_TMDSCLK_SETTING_02_reg_addr                               "0x980341f8"
#define GDI_TMDSCLK_SETTING_02_reg                                    0x980341f8
#define GDI_TMDSCLK_SETTING_02_inst_addr                              "0x007E"
#define GDI_TMDSCLK_SETTING_02_inst                                   0x007E
#define set_GDI_TMDSCLK_SETTING_02_reg(data)                          (*((volatile unsigned int*)GDI_TMDSCLK_SETTING_02_reg)=data)
#define get_GDI_TMDSCLK_SETTING_02_reg                                (*((volatile unsigned int*)GDI_TMDSCLK_SETTING_02_reg))
#define GDI_TMDSCLK_SETTING_02_clk_counter_err_threshold_shift        (8)
#define GDI_TMDSCLK_SETTING_02_clk_counter_debounce_shift             (0)
#define GDI_TMDSCLK_SETTING_02_clk_counter_err_threshold_mask         (0x00000F00)
#define GDI_TMDSCLK_SETTING_02_clk_counter_debounce_mask              (0x000000FF)
#define GDI_TMDSCLK_SETTING_02_clk_counter_err_threshold(data)        (0x00000F00&((data)<<8))
#define GDI_TMDSCLK_SETTING_02_clk_counter_debounce(data)             (0x000000FF&(data))
#define GDI_TMDSCLK_SETTING_02_get_clk_counter_err_threshold(data)    ((0x00000F00&(data))>>8)
#define GDI_TMDSCLK_SETTING_02_get_clk_counter_debounce(data)         (0x000000FF&(data))


#define HDCP_BIST                                                     0x200
#define HDCP_BIST_reg_addr                                            "0x98034200"
#define HDCP_BIST_reg                                                 0x98034200
#define HDCP_BIST_inst_addr                                           "0x0080"
#define HDCP_BIST_inst                                                0x0080
#define set_HDCP_BIST_reg(data)                                       (*((volatile unsigned int*)HDCP_BIST_reg)=data)
#define get_HDCP_BIST_reg                                             (*((volatile unsigned int*)HDCP_BIST_reg))


#define HDCP_CR                                                       0x204
#define HDCP_CR_reg_addr                                              "0x98034204"
#define HDCP_CR_reg                                                   0x98034204
#define HDCP_CR_inst_addr                                             "0x0081"
#define HDCP_CR_inst                                                  0x0081
#define set_HDCP_CR_reg(data)                                         (*((volatile unsigned int*)HDCP_CR_reg)=data)
#define get_HDCP_CR_reg                                               (*((volatile unsigned int*)HDCP_CR_reg))
#define HDCP_CR_namfe_shift                                           (7)
#define HDCP_CR_rpt_shift                                             (6)
#define HDCP_CR_ivsp_shift                                            (5)
#define HDCP_CR_invvs_shift                                           (4)
#define HDCP_CR_ivspm_shift                                           (3)
#define HDCP_CR_maddf_shift                                           (2)
#define HDCP_CR_dkapde_shift                                          (1)
#define HDCP_CR_hdcp_en_shift                                         (0)
#define HDCP_CR_namfe_mask                                            (0x00000080)
#define HDCP_CR_rpt_mask                                              (0x00000040)
#define HDCP_CR_ivsp_mask                                             (0x00000020)
#define HDCP_CR_invvs_mask                                            (0x00000010)
#define HDCP_CR_ivspm_mask                                            (0x00000008)
#define HDCP_CR_maddf_mask                                            (0x00000004)
#define HDCP_CR_dkapde_mask                                           (0x00000002)
#define HDCP_CR_hdcp_en_mask                                          (0x00000001)
#define HDCP_CR_namfe(data)                                           (0x00000080&((data)<<7))
#define HDCP_CR_rpt(data)                                             (0x00000040&((data)<<6))
#define HDCP_CR_ivsp(data)                                            (0x00000020&((data)<<5))
#define HDCP_CR_invvs(data)                                           (0x00000010&((data)<<4))
#define HDCP_CR_ivspm(data)                                           (0x00000008&((data)<<3))
#define HDCP_CR_maddf(data)                                           (0x00000004&((data)<<2))
#define HDCP_CR_dkapde(data)                                          (0x00000002&((data)<<1))
#define HDCP_CR_hdcp_en(data)                                         (0x00000001&(data))
#define HDCP_CR_get_namfe(data)                                       ((0x00000080&(data))>>7)
#define HDCP_CR_get_rpt(data)                                         ((0x00000040&(data))>>6)
#define HDCP_CR_get_ivsp(data)                                        ((0x00000020&(data))>>5)
#define HDCP_CR_get_invvs(data)                                       ((0x00000010&(data))>>4)
#define HDCP_CR_get_ivspm(data)                                       ((0x00000008&(data))>>3)
#define HDCP_CR_get_maddf(data)                                       ((0x00000004&(data))>>2)
#define HDCP_CR_get_dkapde(data)                                      ((0x00000002&(data))>>1)
#define HDCP_CR_get_hdcp_en(data)                                     (0x00000001&(data))


#define HDCP_DKAP                                                     0x208
#define HDCP_DKAP_reg_addr                                            "0x98034208"
#define HDCP_DKAP_reg                                                 0x98034208
#define HDCP_DKAP_inst_addr                                           "0x0082"
#define HDCP_DKAP_inst                                                0x0082
#define set_HDCP_DKAP_reg(data)                                       (*((volatile unsigned int*)HDCP_DKAP_reg)=data)
#define get_HDCP_DKAP_reg                                             (*((volatile unsigned int*)HDCP_DKAP_reg))
#define HDCP_DKAP_dkap_shift                                          (0)
#define HDCP_DKAP_dkap_mask                                           (0x000000FF)
#define HDCP_DKAP_dkap(data)                                          (0x000000FF&(data))
#define HDCP_DKAP_get_dkap(data)                                      (0x000000FF&(data))


#define HDCP_PCR                                                      0x20c
#define HDCP_PCR_reg_addr                                             "0x9803420c"
#define HDCP_PCR_reg                                                  0x9803420c
#define HDCP_PCR_inst_addr                                            "0x0083"
#define HDCP_PCR_inst                                                 0x0083
#define set_HDCP_PCR_reg(data)                                        (*((volatile unsigned int*)HDCP_PCR_reg)=data)
#define get_HDCP_PCR_reg                                              (*((volatile unsigned int*)HDCP_PCR_reg))
#define HDCP_PCR_iic_st_shift                                         (28)
#define HDCP_PCR_i2c_scl_dly_sel_shift                                (24)
#define HDCP_PCR_i2c_sda_dly_sel_shift                                (20)
#define HDCP_PCR_tune_up_down_shift                                   (17)
#define HDCP_PCR_tune_range_shift                                     (10)
#define HDCP_PCR_ddcdbnc_shift                                        (9)
#define HDCP_PCR_km_clk_sel_eco_shift                                 (8)
#define HDCP_PCR_dbnc_level_sel_shift                                 (7)
#define HDCP_PCR_km_clk_sel_shift                                     (6)
#define HDCP_PCR_hdcp_vs_sel_shift                                    (5)
#define HDCP_PCR_enc_tog_shift                                        (4)
#define HDCP_PCR_avmute_dis_shift                                     (3)
#define HDCP_PCR_dummy_2_shift                                        (2)
#define HDCP_PCR_apai_type_shift                                      (1)
#define HDCP_PCR_apai_shift                                           (0)
#define HDCP_PCR_iic_st_mask                                          (0x70000000)
#define HDCP_PCR_i2c_scl_dly_sel_mask                                 (0x0F000000)
#define HDCP_PCR_i2c_sda_dly_sel_mask                                 (0x00F00000)
#define HDCP_PCR_tune_up_down_mask                                    (0x00020000)
#define HDCP_PCR_tune_range_mask                                      (0x0001FC00)
#define HDCP_PCR_ddcdbnc_mask                                         (0x00000200)
#define HDCP_PCR_km_clk_sel_eco_mask                                  (0x00000100)
#define HDCP_PCR_dbnc_level_sel_mask                                  (0x00000080)
#define HDCP_PCR_km_clk_sel_mask                                      (0x00000040)
#define HDCP_PCR_hdcp_vs_sel_mask                                     (0x00000020)
#define HDCP_PCR_enc_tog_mask                                         (0x00000010)
#define HDCP_PCR_avmute_dis_mask                                      (0x00000008)
#define HDCP_PCR_dummy_2_mask                                         (0x00000004)
#define HDCP_PCR_apai_type_mask                                       (0x00000002)
#define HDCP_PCR_apai_mask                                            (0x00000001)
#define HDCP_PCR_iic_st(data)                                         (0x70000000&((data)<<28))
#define HDCP_PCR_i2c_scl_dly_sel(data)                                (0x0F000000&((data)<<24))
#define HDCP_PCR_i2c_sda_dly_sel(data)                                (0x00F00000&((data)<<20))
#define HDCP_PCR_tune_up_down(data)                                   (0x00020000&((data)<<17))
#define HDCP_PCR_tune_range(data)                                     (0x0001FC00&((data)<<10))
#define HDCP_PCR_ddcdbnc(data)                                        (0x00000200&((data)<<9))
#define HDCP_PCR_km_clk_sel_eco(data)                                 (0x00000100&((data)<<8))
#define HDCP_PCR_dbnc_level_sel(data)                                 (0x00000080&((data)<<7))
#define HDCP_PCR_km_clk_sel(data)                                     (0x00000040&((data)<<6))
#define HDCP_PCR_hdcp_vs_sel(data)                                    (0x00000020&((data)<<5))
#define HDCP_PCR_enc_tog(data)                                        (0x00000010&((data)<<4))
#define HDCP_PCR_avmute_dis(data)                                     (0x00000008&((data)<<3))
#define HDCP_PCR_dummy_2(data)                                        (0x00000004&((data)<<2))
#define HDCP_PCR_apai_type(data)                                      (0x00000002&((data)<<1))
#define HDCP_PCR_apai(data)                                           (0x00000001&(data))
#define HDCP_PCR_get_iic_st(data)                                     ((0x70000000&(data))>>28)
#define HDCP_PCR_get_i2c_scl_dly_sel(data)                            ((0x0F000000&(data))>>24)
#define HDCP_PCR_get_i2c_sda_dly_sel(data)                            ((0x00F00000&(data))>>20)
#define HDCP_PCR_get_tune_up_down(data)                               ((0x00020000&(data))>>17)
#define HDCP_PCR_get_tune_range(data)                                 ((0x0001FC00&(data))>>10)
#define HDCP_PCR_get_ddcdbnc(data)                                    ((0x00000200&(data))>>9)
#define HDCP_PCR_get_km_clk_sel_eco(data)                             ((0x00000100&(data))>>8)
#define HDCP_PCR_get_dbnc_level_sel(data)                             ((0x00000080&(data))>>7)
#define HDCP_PCR_get_km_clk_sel(data)                                 ((0x00000040&(data))>>6)
#define HDCP_PCR_get_hdcp_vs_sel(data)                                ((0x00000020&(data))>>5)
#define HDCP_PCR_get_enc_tog(data)                                    ((0x00000010&(data))>>4)
#define HDCP_PCR_get_avmute_dis(data)                                 ((0x00000008&(data))>>3)
#define HDCP_PCR_get_dummy_2(data)                                    ((0x00000004&(data))>>2)
#define HDCP_PCR_get_apai_type(data)                                  ((0x00000002&(data))>>1)
#define HDCP_PCR_get_apai(data)                                       (0x00000001&(data))


#define HDCP_FLAG1                                                    0x210
#define HDCP_FLAG1_reg_addr                                           "0x98034210"
#define HDCP_FLAG1_reg                                                0x98034210
#define HDCP_FLAG1_inst_addr                                          "0x0084"
#define HDCP_FLAG1_inst                                               0x0084
#define set_HDCP_FLAG1_reg(data)                                      (*((volatile unsigned int*)HDCP_FLAG1_reg)=data)
#define get_HDCP_FLAG1_reg                                            (*((volatile unsigned int*)HDCP_FLAG1_reg))
#define HDCP_FLAG1_wr_aksv_flag_shift                                 (4)
#define HDCP_FLAG1_rd_ri_flag_shift                                   (3)
#define HDCP_FLAG1_rd_bksv_flag_shift                                 (2)
#define HDCP_FLAG1_dummy_1_0_shift                                    (0)
#define HDCP_FLAG1_wr_aksv_flag_mask                                  (0x00000010)
#define HDCP_FLAG1_rd_ri_flag_mask                                    (0x00000008)
#define HDCP_FLAG1_rd_bksv_flag_mask                                  (0x00000004)
#define HDCP_FLAG1_dummy_1_0_mask                                     (0x00000003)
#define HDCP_FLAG1_wr_aksv_flag(data)                                 (0x00000010&((data)<<4))
#define HDCP_FLAG1_rd_ri_flag(data)                                   (0x00000008&((data)<<3))
#define HDCP_FLAG1_rd_bksv_flag(data)                                 (0x00000004&((data)<<2))
#define HDCP_FLAG1_dummy_1_0(data)                                    (0x00000003&(data))
#define HDCP_FLAG1_get_wr_aksv_flag(data)                             ((0x00000010&(data))>>4)
#define HDCP_FLAG1_get_rd_ri_flag(data)                               ((0x00000008&(data))>>3)
#define HDCP_FLAG1_get_rd_bksv_flag(data)                             ((0x00000004&(data))>>2)
#define HDCP_FLAG1_get_dummy_1_0(data)                                (0x00000003&(data))


#define HDCP_FLAG2                                                    0x214
#define HDCP_FLAG2_reg_addr                                           "0x98034214"
#define HDCP_FLAG2_reg                                                0x98034214
#define HDCP_FLAG2_inst_addr                                          "0x0085"
#define HDCP_FLAG2_inst                                               0x0085
#define set_HDCP_FLAG2_reg(data)                                      (*((volatile unsigned int*)HDCP_FLAG2_reg)=data)
#define get_HDCP_FLAG2_reg                                            (*((volatile unsigned int*)HDCP_FLAG2_reg))
#define HDCP_FLAG2_irq_aksv_en_shift                                  (4)
#define HDCP_FLAG2_irq_ri_en_shift                                    (3)
#define HDCP_FLAG2_irq_bksv_en_shift                                  (2)
#define HDCP_FLAG2_dummy_1_0_shift                                    (0)
#define HDCP_FLAG2_irq_aksv_en_mask                                   (0x00000010)
#define HDCP_FLAG2_irq_ri_en_mask                                     (0x00000008)
#define HDCP_FLAG2_irq_bksv_en_mask                                   (0x00000004)
#define HDCP_FLAG2_dummy_1_0_mask                                     (0x00000003)
#define HDCP_FLAG2_irq_aksv_en(data)                                  (0x00000010&((data)<<4))
#define HDCP_FLAG2_irq_ri_en(data)                                    (0x00000008&((data)<<3))
#define HDCP_FLAG2_irq_bksv_en(data)                                  (0x00000004&((data)<<2))
#define HDCP_FLAG2_dummy_1_0(data)                                    (0x00000003&(data))
#define HDCP_FLAG2_get_irq_aksv_en(data)                              ((0x00000010&(data))>>4)
#define HDCP_FLAG2_get_irq_ri_en(data)                                ((0x00000008&(data))>>3)
#define HDCP_FLAG2_get_irq_bksv_en(data)                              ((0x00000004&(data))>>2)
#define HDCP_FLAG2_get_dummy_1_0(data)                                (0x00000003&(data))


#define HDCP_AP                                                       0x218
#define HDCP_AP_reg_addr                                              "0x98034218"
#define HDCP_AP_reg                                                   0x98034218
#define HDCP_AP_inst_addr                                             "0x0086"
#define HDCP_AP_inst                                                  0x0086
#define set_HDCP_AP_reg(data)                                         (*((volatile unsigned int*)HDCP_AP_reg)=data)
#define get_HDCP_AP_reg                                               (*((volatile unsigned int*)HDCP_AP_reg))
#define HDCP_AP_ksvfifo_status_shift                                  (18)
#define HDCP_AP_dp_ksvfifo_ptr_shift                                  (8)
#define HDCP_AP_ap1_shift                                             (0)
#define HDCP_AP_ksvfifo_status_mask                                   (0x00040000)
#define HDCP_AP_dp_ksvfifo_ptr_mask                                   (0x0003FF00)
#define HDCP_AP_ap1_mask                                              (0x000000FF)
#define HDCP_AP_ksvfifo_status(data)                                  (0x00040000&((data)<<18))
#define HDCP_AP_dp_ksvfifo_ptr(data)                                  (0x0003FF00&((data)<<8))
#define HDCP_AP_ap1(data)                                             (0x000000FF&(data))
#define HDCP_AP_get_ksvfifo_status(data)                              ((0x00040000&(data))>>18)
#define HDCP_AP_get_dp_ksvfifo_ptr(data)                              ((0x0003FF00&(data))>>8)
#define HDCP_AP_get_ap1(data)                                         (0x000000FF&(data))


#define HDCP_DP                                                       0x21c
#define HDCP_DP_reg_addr                                              "0x9803421c"
#define HDCP_DP_reg                                                   0x9803421c
#define HDCP_DP_inst_addr                                             "0x0087"
#define HDCP_DP_inst                                                  0x0087
#define set_HDCP_DP_reg(data)                                         (*((volatile unsigned int*)HDCP_DP_reg)=data)
#define get_HDCP_DP_reg                                               (*((volatile unsigned int*)HDCP_DP_reg))
#define HDCP_DP_dp1_shift                                             (0)
#define HDCP_DP_dp1_mask                                              (0x000000FF)
#define HDCP_DP_dp1(data)                                             (0x000000FF&(data))
#define HDCP_DP_get_dp1(data)                                         (0x000000FF&(data))


#define HDCP_2P2_CR                                                   0x220
#define HDCP_2P2_CR_reg_addr                                          "0x98034220"
#define HDCP_2P2_CR_reg                                               0x98034220
#define HDCP_2P2_CR_inst_addr                                         "0x0088"
#define HDCP_2P2_CR_inst                                              0x0088
#define set_HDCP_2P2_CR_reg(data)                                     (*((volatile unsigned int*)HDCP_2P2_CR_reg)=data)
#define get_HDCP_2P2_CR_reg                                           (*((volatile unsigned int*)HDCP_2P2_CR_reg))
#define HDCP_2P2_CR_dummy_31_27_shift                                 (27)
#define HDCP_2P2_CR_fn_auto_inc_shift                                 (26)
#define HDCP_2P2_CR_apply_cp_fn_shift                                 (25)
#define HDCP_2P2_CR_ks_encoded_shift                                  (24)
#define HDCP_2P2_CR_switch_state_shift                                (12)
#define HDCP_2P2_CR_rpt_thr_unauth_shift                              (11)
#define HDCP_2P2_CR_fw_mode_riv_shift                                 (10)
#define HDCP_2P2_CR_apply_state_shift                                 (9)
#define HDCP_2P2_CR_mspai_shift                                       (8)
#define HDCP_2P2_CR_new_auth_device_shift                             (7)
#define HDCP_2P2_CR_verify_id_pass_shift                              (6)
#define HDCP_2P2_CR_verify_id_done_shift                              (5)
#define HDCP_2P2_CR_assemble_id_fail_shift                            (4)
#define HDCP_2P2_CR_downstream_done_shift                             (3)
#define HDCP_2P2_CR_ks_done_shift                                     (2)
#define HDCP_2P2_CR_switch_unauth_shift                               (1)
#define HDCP_2P2_CR_hdcp_2p2_en_shift                                 (0)
#define HDCP_2P2_CR_dummy_31_27_mask                                  (0xF8000000)
#define HDCP_2P2_CR_fn_auto_inc_mask                                  (0x04000000)
#define HDCP_2P2_CR_apply_cp_fn_mask                                  (0x02000000)
#define HDCP_2P2_CR_ks_encoded_mask                                   (0x01000000)
#define HDCP_2P2_CR_switch_state_mask                                 (0x00FFF000)
#define HDCP_2P2_CR_rpt_thr_unauth_mask                               (0x00000800)
#define HDCP_2P2_CR_fw_mode_riv_mask                                  (0x00000400)
#define HDCP_2P2_CR_apply_state_mask                                  (0x00000200)
#define HDCP_2P2_CR_mspai_mask                                        (0x00000100)
#define HDCP_2P2_CR_new_auth_device_mask                              (0x00000080)
#define HDCP_2P2_CR_verify_id_pass_mask                               (0x00000040)
#define HDCP_2P2_CR_verify_id_done_mask                               (0x00000020)
#define HDCP_2P2_CR_assemble_id_fail_mask                             (0x00000010)
#define HDCP_2P2_CR_downstream_done_mask                              (0x00000008)
#define HDCP_2P2_CR_ks_done_mask                                      (0x00000004)
#define HDCP_2P2_CR_switch_unauth_mask                                (0x00000002)
#define HDCP_2P2_CR_hdcp_2p2_en_mask                                  (0x00000001)
#define HDCP_2P2_CR_dummy_31_27(data)                                 (0xF8000000&((data)<<27))
#define HDCP_2P2_CR_fn_auto_inc(data)                                 (0x04000000&((data)<<26))
#define HDCP_2P2_CR_apply_cp_fn(data)                                 (0x02000000&((data)<<25))
#define HDCP_2P2_CR_ks_encoded(data)                                  (0x01000000&((data)<<24))
#define HDCP_2P2_CR_switch_state(data)                                (0x00FFF000&((data)<<12))
#define HDCP_2P2_CR_rpt_thr_unauth(data)                              (0x00000800&((data)<<11))
#define HDCP_2P2_CR_fw_mode_riv(data)                                 (0x00000400&((data)<<10))
#define HDCP_2P2_CR_apply_state(data)                                 (0x00000200&((data)<<9))
#define HDCP_2P2_CR_mspai(data)                                       (0x00000100&((data)<<8))
#define HDCP_2P2_CR_new_auth_device(data)                             (0x00000080&((data)<<7))
#define HDCP_2P2_CR_verify_id_pass(data)                              (0x00000040&((data)<<6))
#define HDCP_2P2_CR_verify_id_done(data)                              (0x00000020&((data)<<5))
#define HDCP_2P2_CR_assemble_id_fail(data)                            (0x00000010&((data)<<4))
#define HDCP_2P2_CR_downstream_done(data)                             (0x00000008&((data)<<3))
#define HDCP_2P2_CR_ks_done(data)                                     (0x00000004&((data)<<2))
#define HDCP_2P2_CR_switch_unauth(data)                               (0x00000002&((data)<<1))
#define HDCP_2P2_CR_hdcp_2p2_en(data)                                 (0x00000001&(data))
#define HDCP_2P2_CR_get_dummy_31_27(data)                             ((0xF8000000&(data))>>27)
#define HDCP_2P2_CR_get_fn_auto_inc(data)                             ((0x04000000&(data))>>26)
#define HDCP_2P2_CR_get_apply_cp_fn(data)                             ((0x02000000&(data))>>25)
#define HDCP_2P2_CR_get_ks_encoded(data)                              ((0x01000000&(data))>>24)
#define HDCP_2P2_CR_get_switch_state(data)                            ((0x00FFF000&(data))>>12)
#define HDCP_2P2_CR_get_rpt_thr_unauth(data)                          ((0x00000800&(data))>>11)
#define HDCP_2P2_CR_get_fw_mode_riv(data)                             ((0x00000400&(data))>>10)
#define HDCP_2P2_CR_get_apply_state(data)                             ((0x00000200&(data))>>9)
#define HDCP_2P2_CR_get_mspai(data)                                   ((0x00000100&(data))>>8)
#define HDCP_2P2_CR_get_new_auth_device(data)                         ((0x00000080&(data))>>7)
#define HDCP_2P2_CR_get_verify_id_pass(data)                          ((0x00000040&(data))>>6)
#define HDCP_2P2_CR_get_verify_id_done(data)                          ((0x00000020&(data))>>5)
#define HDCP_2P2_CR_get_assemble_id_fail(data)                        ((0x00000010&(data))>>4)
#define HDCP_2P2_CR_get_downstream_done(data)                         ((0x00000008&(data))>>3)
#define HDCP_2P2_CR_get_ks_done(data)                                 ((0x00000004&(data))>>2)
#define HDCP_2P2_CR_get_switch_unauth(data)                           ((0x00000002&(data))>>1)
#define HDCP_2P2_CR_get_hdcp_2p2_en(data)                             (0x00000001&(data))


#define HDCP_2P2_KS0                                                  0x224
#define HDCP_2P2_KS0_reg_addr                                         "0x98034224"
#define HDCP_2P2_KS0_reg                                              0x98034224
#define HDCP_2P2_KS0_inst_addr                                        "0x0089"
#define HDCP_2P2_KS0_inst                                             0x0089
#define set_HDCP_2P2_KS0_reg(data)                                    (*((volatile unsigned int*)HDCP_2P2_KS0_reg)=data)
#define get_HDCP_2P2_KS0_reg                                          (*((volatile unsigned int*)HDCP_2P2_KS0_reg))
#define HDCP_2P2_KS0_ks_shift                                         (0)
#define HDCP_2P2_KS0_ks_mask                                          (0xFFFFFFFF)
#define HDCP_2P2_KS0_ks(data)                                         (0xFFFFFFFF&(data))
#define HDCP_2P2_KS0_get_ks(data)                                     (0xFFFFFFFF&(data))


#define HDCP_2P2_KS1                                                  0x228
#define HDCP_2P2_KS1_reg_addr                                         "0x98034228"
#define HDCP_2P2_KS1_reg                                              0x98034228
#define HDCP_2P2_KS1_inst_addr                                        "0x008A"
#define HDCP_2P2_KS1_inst                                             0x008A
#define set_HDCP_2P2_KS1_reg(data)                                    (*((volatile unsigned int*)HDCP_2P2_KS1_reg)=data)
#define get_HDCP_2P2_KS1_reg                                          (*((volatile unsigned int*)HDCP_2P2_KS1_reg))
#define HDCP_2P2_KS1_ks_shift                                         (0)
#define HDCP_2P2_KS1_ks_mask                                          (0xFFFFFFFF)
#define HDCP_2P2_KS1_ks(data)                                         (0xFFFFFFFF&(data))
#define HDCP_2P2_KS1_get_ks(data)                                     (0xFFFFFFFF&(data))


#define HDCP_2P2_KS2                                                  0x22c
#define HDCP_2P2_KS2_reg_addr                                         "0x9803422c"
#define HDCP_2P2_KS2_reg                                              0x9803422c
#define HDCP_2P2_KS2_inst_addr                                        "0x008B"
#define HDCP_2P2_KS2_inst                                             0x008B
#define set_HDCP_2P2_KS2_reg(data)                                    (*((volatile unsigned int*)HDCP_2P2_KS2_reg)=data)
#define get_HDCP_2P2_KS2_reg                                          (*((volatile unsigned int*)HDCP_2P2_KS2_reg))
#define HDCP_2P2_KS2_ks_shift                                         (0)
#define HDCP_2P2_KS2_ks_mask                                          (0xFFFFFFFF)
#define HDCP_2P2_KS2_ks(data)                                         (0xFFFFFFFF&(data))
#define HDCP_2P2_KS2_get_ks(data)                                     (0xFFFFFFFF&(data))


#define HDCP_2P2_KS3                                                  0x230
#define HDCP_2P2_KS3_reg_addr                                         "0x98034230"
#define HDCP_2P2_KS3_reg                                              0x98034230
#define HDCP_2P2_KS3_inst_addr                                        "0x008C"
#define HDCP_2P2_KS3_inst                                             0x008C
#define set_HDCP_2P2_KS3_reg(data)                                    (*((volatile unsigned int*)HDCP_2P2_KS3_reg)=data)
#define get_HDCP_2P2_KS3_reg                                          (*((volatile unsigned int*)HDCP_2P2_KS3_reg))
#define HDCP_2P2_KS3_ks_shift                                         (0)
#define HDCP_2P2_KS3_ks_mask                                          (0xFFFFFFFF)
#define HDCP_2P2_KS3_ks(data)                                         (0xFFFFFFFF&(data))
#define HDCP_2P2_KS3_get_ks(data)                                     (0xFFFFFFFF&(data))


#define HDCP_2P2_LC0                                                  0x234
#define HDCP_2P2_LC0_reg_addr                                         "0x98034234"
#define HDCP_2P2_LC0_reg                                              0x98034234
#define HDCP_2P2_LC0_inst_addr                                        "0x008D"
#define HDCP_2P2_LC0_inst                                             0x008D
#define set_HDCP_2P2_LC0_reg(data)                                    (*((volatile unsigned int*)HDCP_2P2_LC0_reg)=data)
#define get_HDCP_2P2_LC0_reg                                          (*((volatile unsigned int*)HDCP_2P2_LC0_reg))
#define HDCP_2P2_LC0_lc_shift                                         (0)
#define HDCP_2P2_LC0_lc_mask                                          (0xFFFFFFFF)
#define HDCP_2P2_LC0_lc(data)                                         (0xFFFFFFFF&(data))
#define HDCP_2P2_LC0_get_lc(data)                                     (0xFFFFFFFF&(data))


#define HDCP_2P2_LC1                                                  0x238
#define HDCP_2P2_LC1_reg_addr                                         "0x98034238"
#define HDCP_2P2_LC1_reg                                              0x98034238
#define HDCP_2P2_LC1_inst_addr                                        "0x008E"
#define HDCP_2P2_LC1_inst                                             0x008E
#define set_HDCP_2P2_LC1_reg(data)                                    (*((volatile unsigned int*)HDCP_2P2_LC1_reg)=data)
#define get_HDCP_2P2_LC1_reg                                          (*((volatile unsigned int*)HDCP_2P2_LC1_reg))
#define HDCP_2P2_LC1_lc_shift                                         (0)
#define HDCP_2P2_LC1_lc_mask                                          (0xFFFFFFFF)
#define HDCP_2P2_LC1_lc(data)                                         (0xFFFFFFFF&(data))
#define HDCP_2P2_LC1_get_lc(data)                                     (0xFFFFFFFF&(data))


#define HDCP_2P2_LC2                                                  0x23c
#define HDCP_2P2_LC2_reg_addr                                         "0x9803423c"
#define HDCP_2P2_LC2_reg                                              0x9803423c
#define HDCP_2P2_LC2_inst_addr                                        "0x008F"
#define HDCP_2P2_LC2_inst                                             0x008F
#define set_HDCP_2P2_LC2_reg(data)                                    (*((volatile unsigned int*)HDCP_2P2_LC2_reg)=data)
#define get_HDCP_2P2_LC2_reg                                          (*((volatile unsigned int*)HDCP_2P2_LC2_reg))
#define HDCP_2P2_LC2_lc_shift                                         (0)
#define HDCP_2P2_LC2_lc_mask                                          (0xFFFFFFFF)
#define HDCP_2P2_LC2_lc(data)                                         (0xFFFFFFFF&(data))
#define HDCP_2P2_LC2_get_lc(data)                                     (0xFFFFFFFF&(data))


#define HDCP_2P2_LC3                                                  0x240
#define HDCP_2P2_LC3_reg_addr                                         "0x98034240"
#define HDCP_2P2_LC3_reg                                              0x98034240
#define HDCP_2P2_LC3_inst_addr                                        "0x0090"
#define HDCP_2P2_LC3_inst                                             0x0090
#define set_HDCP_2P2_LC3_reg(data)                                    (*((volatile unsigned int*)HDCP_2P2_LC3_reg)=data)
#define get_HDCP_2P2_LC3_reg                                          (*((volatile unsigned int*)HDCP_2P2_LC3_reg))
#define HDCP_2P2_LC3_lc_shift                                         (0)
#define HDCP_2P2_LC3_lc_mask                                          (0xFFFFFFFF)
#define HDCP_2P2_LC3_lc(data)                                         (0xFFFFFFFF&(data))
#define HDCP_2P2_LC3_get_lc(data)                                     (0xFFFFFFFF&(data))


#define HDCP_2P2_RIV0                                                 0x244
#define HDCP_2P2_RIV0_reg_addr                                        "0x98034244"
#define HDCP_2P2_RIV0_reg                                             0x98034244
#define HDCP_2P2_RIV0_inst_addr                                       "0x0091"
#define HDCP_2P2_RIV0_inst                                            0x0091
#define set_HDCP_2P2_RIV0_reg(data)                                   (*((volatile unsigned int*)HDCP_2P2_RIV0_reg)=data)
#define get_HDCP_2P2_RIV0_reg                                         (*((volatile unsigned int*)HDCP_2P2_RIV0_reg))
#define HDCP_2P2_RIV0_riv_shift                                       (0)
#define HDCP_2P2_RIV0_riv_mask                                        (0xFFFFFFFF)
#define HDCP_2P2_RIV0_riv(data)                                       (0xFFFFFFFF&(data))
#define HDCP_2P2_RIV0_get_riv(data)                                   (0xFFFFFFFF&(data))


#define HDCP_2P2_RIV1                                                 0x248
#define HDCP_2P2_RIV1_reg_addr                                        "0x98034248"
#define HDCP_2P2_RIV1_reg                                             0x98034248
#define HDCP_2P2_RIV1_inst_addr                                       "0x0092"
#define HDCP_2P2_RIV1_inst                                            0x0092
#define set_HDCP_2P2_RIV1_reg(data)                                   (*((volatile unsigned int*)HDCP_2P2_RIV1_reg)=data)
#define get_HDCP_2P2_RIV1_reg                                         (*((volatile unsigned int*)HDCP_2P2_RIV1_reg))
#define HDCP_2P2_RIV1_riv_shift                                       (0)
#define HDCP_2P2_RIV1_riv_mask                                        (0xFFFFFFFF)
#define HDCP_2P2_RIV1_riv(data)                                       (0xFFFFFFFF&(data))
#define HDCP_2P2_RIV1_get_riv(data)                                   (0xFFFFFFFF&(data))


#define HDCP_2P2_SR0                                                  0x24c
#define HDCP_2P2_SR0_reg_addr                                         "0x9803424c"
#define HDCP_2P2_SR0_reg                                              0x9803424c
#define HDCP_2P2_SR0_inst_addr                                        "0x0093"
#define HDCP_2P2_SR0_inst                                             0x0093
#define set_HDCP_2P2_SR0_reg(data)                                    (*((volatile unsigned int*)HDCP_2P2_SR0_reg)=data)
#define get_HDCP_2P2_SR0_reg                                          (*((volatile unsigned int*)HDCP_2P2_SR0_reg))
#define HDCP_2P2_SR0_frame_number_shift                               (22)
#define HDCP_2P2_SR0_irq_fn_compare_fail_shift                        (21)
#define HDCP_2P2_SR0_irq_crc_fail_shift                               (20)
#define HDCP_2P2_SR0_irq_no_cp_packet_shift                           (19)
#define HDCP_2P2_SR0_irq_msg_overwrite_shift                          (18)
#define HDCP_2P2_SR0_irq_unauth_chg_shift                             (17)
#define HDCP_2P2_SR0_irq_state_chg_shift                              (16)
#define HDCP_2P2_SR0_irq_rd_msg_done_shift                            (15)
#define HDCP_2P2_SR0_irq_wr_msg_done_shift                            (14)
#define HDCP_2P2_SR0_irq_rd_msg_start_shift                           (13)
#define HDCP_2P2_SR0_irq_wr_msg_start_shift                           (12)
#define HDCP_2P2_SR0_state_shift                                      (0)
#define HDCP_2P2_SR0_frame_number_mask                                (0x3FC00000)
#define HDCP_2P2_SR0_irq_fn_compare_fail_mask                         (0x00200000)
#define HDCP_2P2_SR0_irq_crc_fail_mask                                (0x00100000)
#define HDCP_2P2_SR0_irq_no_cp_packet_mask                            (0x00080000)
#define HDCP_2P2_SR0_irq_msg_overwrite_mask                           (0x00040000)
#define HDCP_2P2_SR0_irq_unauth_chg_mask                              (0x00020000)
#define HDCP_2P2_SR0_irq_state_chg_mask                               (0x00010000)
#define HDCP_2P2_SR0_irq_rd_msg_done_mask                             (0x00008000)
#define HDCP_2P2_SR0_irq_wr_msg_done_mask                             (0x00004000)
#define HDCP_2P2_SR0_irq_rd_msg_start_mask                            (0x00002000)
#define HDCP_2P2_SR0_irq_wr_msg_start_mask                            (0x00001000)
#define HDCP_2P2_SR0_state_mask                                       (0x00000FFF)
#define HDCP_2P2_SR0_frame_number(data)                               (0x3FC00000&((data)<<22))
#define HDCP_2P2_SR0_irq_fn_compare_fail(data)                        (0x00200000&((data)<<21))
#define HDCP_2P2_SR0_irq_crc_fail(data)                               (0x00100000&((data)<<20))
#define HDCP_2P2_SR0_irq_no_cp_packet(data)                           (0x00080000&((data)<<19))
#define HDCP_2P2_SR0_irq_msg_overwrite(data)                          (0x00040000&((data)<<18))
#define HDCP_2P2_SR0_irq_unauth_chg(data)                             (0x00020000&((data)<<17))
#define HDCP_2P2_SR0_irq_state_chg(data)                              (0x00010000&((data)<<16))
#define HDCP_2P2_SR0_irq_rd_msg_done(data)                            (0x00008000&((data)<<15))
#define HDCP_2P2_SR0_irq_wr_msg_done(data)                            (0x00004000&((data)<<14))
#define HDCP_2P2_SR0_irq_rd_msg_start(data)                           (0x00002000&((data)<<13))
#define HDCP_2P2_SR0_irq_wr_msg_start(data)                           (0x00001000&((data)<<12))
#define HDCP_2P2_SR0_state(data)                                      (0x00000FFF&(data))
#define HDCP_2P2_SR0_get_frame_number(data)                           ((0x3FC00000&(data))>>22)
#define HDCP_2P2_SR0_get_irq_fn_compare_fail(data)                    ((0x00200000&(data))>>21)
#define HDCP_2P2_SR0_get_irq_crc_fail(data)                           ((0x00100000&(data))>>20)
#define HDCP_2P2_SR0_get_irq_no_cp_packet(data)                       ((0x00080000&(data))>>19)
#define HDCP_2P2_SR0_get_irq_msg_overwrite(data)                      ((0x00040000&(data))>>18)
#define HDCP_2P2_SR0_get_irq_unauth_chg(data)                         ((0x00020000&(data))>>17)
#define HDCP_2P2_SR0_get_irq_state_chg(data)                          ((0x00010000&(data))>>16)
#define HDCP_2P2_SR0_get_irq_rd_msg_done(data)                        ((0x00008000&(data))>>15)
#define HDCP_2P2_SR0_get_irq_wr_msg_done(data)                        ((0x00004000&(data))>>14)
#define HDCP_2P2_SR0_get_irq_rd_msg_start(data)                       ((0x00002000&(data))>>13)
#define HDCP_2P2_SR0_get_irq_wr_msg_start(data)                       ((0x00001000&(data))>>12)
#define HDCP_2P2_SR0_get_state(data)                                  (0x00000FFF&(data))


#define HDCP_2P2_SR1                                                  0x250
#define HDCP_2P2_SR1_reg_addr                                         "0x98034250"
#define HDCP_2P2_SR1_reg                                              0x98034250
#define HDCP_2P2_SR1_inst_addr                                        "0x0094"
#define HDCP_2P2_SR1_inst                                             0x0094
#define set_HDCP_2P2_SR1_reg(data)                                    (*((volatile unsigned int*)HDCP_2P2_SR1_reg)=data)
#define get_HDCP_2P2_SR1_reg                                          (*((volatile unsigned int*)HDCP_2P2_SR1_reg))
#define HDCP_2P2_SR1_crc_fail_wd_en_shift                             (11)
#define HDCP_2P2_SR1_no_cp_packet_wd_en_shift                         (10)
#define HDCP_2P2_SR1_irq_fn_compare_fail_en_shift                     (9)
#define HDCP_2P2_SR1_irq_crc_fail_en_shift                            (8)
#define HDCP_2P2_SR1_irq_no_cp_packet_en_shift                        (7)
#define HDCP_2P2_SR1_irq_msg_overwrite_en_shift                       (6)
#define HDCP_2P2_SR1_irq_unauth_chg_en_shift                          (5)
#define HDCP_2P2_SR1_irq_state_chg_en_shift                           (4)
#define HDCP_2P2_SR1_irq_rd_msg_done_en_shift                         (3)
#define HDCP_2P2_SR1_irq_wr_msg_done_en_shift                         (2)
#define HDCP_2P2_SR1_irq_rd_msg_start_en_shift                        (1)
#define HDCP_2P2_SR1_irq_wr_msg_start_en_shift                        (0)
#define HDCP_2P2_SR1_crc_fail_wd_en_mask                              (0x00000800)
#define HDCP_2P2_SR1_no_cp_packet_wd_en_mask                          (0x00000400)
#define HDCP_2P2_SR1_irq_fn_compare_fail_en_mask                      (0x00000200)
#define HDCP_2P2_SR1_irq_crc_fail_en_mask                             (0x00000100)
#define HDCP_2P2_SR1_irq_no_cp_packet_en_mask                         (0x00000080)
#define HDCP_2P2_SR1_irq_msg_overwrite_en_mask                        (0x00000040)
#define HDCP_2P2_SR1_irq_unauth_chg_en_mask                           (0x00000020)
#define HDCP_2P2_SR1_irq_state_chg_en_mask                            (0x00000010)
#define HDCP_2P2_SR1_irq_rd_msg_done_en_mask                          (0x00000008)
#define HDCP_2P2_SR1_irq_wr_msg_done_en_mask                          (0x00000004)
#define HDCP_2P2_SR1_irq_rd_msg_start_en_mask                         (0x00000002)
#define HDCP_2P2_SR1_irq_wr_msg_start_en_mask                         (0x00000001)
#define HDCP_2P2_SR1_crc_fail_wd_en(data)                             (0x00000800&((data)<<11))
#define HDCP_2P2_SR1_no_cp_packet_wd_en(data)                         (0x00000400&((data)<<10))
#define HDCP_2P2_SR1_irq_fn_compare_fail_en(data)                     (0x00000200&((data)<<9))
#define HDCP_2P2_SR1_irq_crc_fail_en(data)                            (0x00000100&((data)<<8))
#define HDCP_2P2_SR1_irq_no_cp_packet_en(data)                        (0x00000080&((data)<<7))
#define HDCP_2P2_SR1_irq_msg_overwrite_en(data)                       (0x00000040&((data)<<6))
#define HDCP_2P2_SR1_irq_unauth_chg_en(data)                          (0x00000020&((data)<<5))
#define HDCP_2P2_SR1_irq_state_chg_en(data)                           (0x00000010&((data)<<4))
#define HDCP_2P2_SR1_irq_rd_msg_done_en(data)                         (0x00000008&((data)<<3))
#define HDCP_2P2_SR1_irq_wr_msg_done_en(data)                         (0x00000004&((data)<<2))
#define HDCP_2P2_SR1_irq_rd_msg_start_en(data)                        (0x00000002&((data)<<1))
#define HDCP_2P2_SR1_irq_wr_msg_start_en(data)                        (0x00000001&(data))
#define HDCP_2P2_SR1_get_crc_fail_wd_en(data)                         ((0x00000800&(data))>>11)
#define HDCP_2P2_SR1_get_no_cp_packet_wd_en(data)                     ((0x00000400&(data))>>10)
#define HDCP_2P2_SR1_get_irq_fn_compare_fail_en(data)                 ((0x00000200&(data))>>9)
#define HDCP_2P2_SR1_get_irq_crc_fail_en(data)                        ((0x00000100&(data))>>8)
#define HDCP_2P2_SR1_get_irq_no_cp_packet_en(data)                    ((0x00000080&(data))>>7)
#define HDCP_2P2_SR1_get_irq_msg_overwrite_en(data)                   ((0x00000040&(data))>>6)
#define HDCP_2P2_SR1_get_irq_unauth_chg_en(data)                      ((0x00000020&(data))>>5)
#define HDCP_2P2_SR1_get_irq_state_chg_en(data)                       ((0x00000010&(data))>>4)
#define HDCP_2P2_SR1_get_irq_rd_msg_done_en(data)                     ((0x00000008&(data))>>3)
#define HDCP_2P2_SR1_get_irq_wr_msg_done_en(data)                     ((0x00000004&(data))>>2)
#define HDCP_2P2_SR1_get_irq_rd_msg_start_en(data)                    ((0x00000002&(data))>>1)
#define HDCP_2P2_SR1_get_irq_wr_msg_start_en(data)                    (0x00000001&(data))


#define HDCP_MSAP                                                     0x254
#define HDCP_MSAP_reg_addr                                            "0x98034254"
#define HDCP_MSAP_reg                                                 0x98034254
#define HDCP_MSAP_inst_addr                                           "0x0095"
#define HDCP_MSAP_inst                                                0x0095
#define set_HDCP_MSAP_reg(data)                                       (*((volatile unsigned int*)HDCP_MSAP_reg)=data)
#define get_HDCP_MSAP_reg                                             (*((volatile unsigned int*)HDCP_MSAP_reg))
#define HDCP_MSAP_ap1_shift                                           (0)
#define HDCP_MSAP_ap1_mask                                            (0x000003FF)
#define HDCP_MSAP_ap1(data)                                           (0x000003FF&(data))
#define HDCP_MSAP_get_ap1(data)                                       (0x000003FF&(data))


#define HDCP_MSDP                                                     0x258
#define HDCP_MSDP_reg_addr                                            "0x98034258"
#define HDCP_MSDP_reg                                                 0x98034258
#define HDCP_MSDP_inst_addr                                           "0x0096"
#define HDCP_MSDP_inst                                                0x0096
#define set_HDCP_MSDP_reg(data)                                       (*((volatile unsigned int*)HDCP_MSDP_reg)=data)
#define get_HDCP_MSDP_reg                                             (*((volatile unsigned int*)HDCP_MSDP_reg))
#define HDCP_MSDP_dp1_shift                                           (0)
#define HDCP_MSDP_dp1_mask                                            (0x000000FF)
#define HDCP_MSDP_dp1(data)                                           (0x000000FF&(data))
#define HDCP_MSDP_get_dp1(data)                                       (0x000000FF&(data))


#define HDMI_CMCR                                                     0x300
#define HDMI_CMCR_reg_addr                                            "0x98034300"
#define HDMI_CMCR_reg                                                 0x98034300
#define HDMI_CMCR_inst_addr                                           "0x00C0"
#define HDMI_CMCR_inst                                                0x00C0
#define set_HDMI_CMCR_reg(data)                                       (*((volatile unsigned int*)HDMI_CMCR_reg)=data)
#define get_HDMI_CMCR_reg                                             (*((volatile unsigned int*)HDMI_CMCR_reg))
#define HDMI_CMCR_icmux_shift                                         (7)
#define HDMI_CMCR_ocs_shift                                           (5)
#define HDMI_CMCR_dbdcb_shift                                         (4)
#define HDMI_CMCR_dummy_3_0_shift                                     (0)
#define HDMI_CMCR_icmux_mask                                          (0x00000080)
#define HDMI_CMCR_ocs_mask                                            (0x00000060)
#define HDMI_CMCR_dbdcb_mask                                          (0x00000010)
#define HDMI_CMCR_dummy_3_0_mask                                      (0x0000000F)
#define HDMI_CMCR_icmux(data)                                         (0x00000080&((data)<<7))
#define HDMI_CMCR_ocs(data)                                           (0x00000060&((data)<<5))
#define HDMI_CMCR_dbdcb(data)                                         (0x00000010&((data)<<4))
#define HDMI_CMCR_dummy_3_0(data)                                     (0x0000000F&(data))
#define HDMI_CMCR_get_icmux(data)                                     ((0x00000080&(data))>>7)
#define HDMI_CMCR_get_ocs(data)                                       ((0x00000060&(data))>>5)
#define HDMI_CMCR_get_dbdcb(data)                                     ((0x00000010&(data))>>4)
#define HDMI_CMCR_get_dummy_3_0(data)                                 (0x0000000F&(data))


#define HDMI_MCAPR                                                    0x304
#define HDMI_MCAPR_reg_addr                                           "0x98034304"
#define HDMI_MCAPR_reg                                                0x98034304
#define HDMI_MCAPR_inst_addr                                          "0x00C1"
#define HDMI_MCAPR_inst                                               0x00C1
#define set_HDMI_MCAPR_reg(data)                                      (*((volatile unsigned int*)HDMI_MCAPR_reg)=data)
#define get_HDMI_MCAPR_reg                                            (*((volatile unsigned int*)HDMI_MCAPR_reg))
#define HDMI_MCAPR_dummy_7_0_shift                                    (0)
#define HDMI_MCAPR_dummy_7_0_mask                                     (0x000000FF)
#define HDMI_MCAPR_dummy_7_0(data)                                    (0x000000FF&(data))
#define HDMI_MCAPR_get_dummy_7_0(data)                                (0x000000FF&(data))


#define HDMI_SCAPR                                                    0x308
#define HDMI_SCAPR_reg_addr                                           "0x98034308"
#define HDMI_SCAPR_reg                                                0x98034308
#define HDMI_SCAPR_inst_addr                                          "0x00C2"
#define HDMI_SCAPR_inst                                               0x00C2
#define set_HDMI_SCAPR_reg(data)                                      (*((volatile unsigned int*)HDMI_SCAPR_reg)=data)
#define get_HDMI_SCAPR_reg                                            (*((volatile unsigned int*)HDMI_SCAPR_reg))
#define HDMI_SCAPR_s1_code_msb_r_shift                                (17)
#define HDMI_SCAPR_slc_r_shift                                        (16)
#define HDMI_SCAPR_sc_r_shift                                         (9)
#define HDMI_SCAPR_s1_code_msb_shift                                  (8)
#define HDMI_SCAPR_slc_shift                                          (7)
#define HDMI_SCAPR_sc_shift                                           (0)
#define HDMI_SCAPR_s1_code_msb_r_mask                                 (0x00020000)
#define HDMI_SCAPR_slc_r_mask                                         (0x00010000)
#define HDMI_SCAPR_sc_r_mask                                          (0x0000FE00)
#define HDMI_SCAPR_s1_code_msb_mask                                   (0x00000100)
#define HDMI_SCAPR_slc_mask                                           (0x00000080)
#define HDMI_SCAPR_sc_mask                                            (0x0000007F)
#define HDMI_SCAPR_s1_code_msb_r(data)                                (0x00020000&((data)<<17))
#define HDMI_SCAPR_slc_r(data)                                        (0x00010000&((data)<<16))
#define HDMI_SCAPR_sc_r(data)                                         (0x0000FE00&((data)<<9))
#define HDMI_SCAPR_s1_code_msb(data)                                  (0x00000100&((data)<<8))
#define HDMI_SCAPR_slc(data)                                          (0x00000080&((data)<<7))
#define HDMI_SCAPR_sc(data)                                           (0x0000007F&(data))
#define HDMI_SCAPR_get_s1_code_msb_r(data)                            ((0x00020000&(data))>>17)
#define HDMI_SCAPR_get_slc_r(data)                                    ((0x00010000&(data))>>16)
#define HDMI_SCAPR_get_sc_r(data)                                     ((0x0000FE00&(data))>>9)
#define HDMI_SCAPR_get_s1_code_msb(data)                              ((0x00000100&(data))>>8)
#define HDMI_SCAPR_get_slc(data)                                      ((0x00000080&(data))>>7)
#define HDMI_SCAPR_get_sc(data)                                       (0x0000007F&(data))


#define HDMI_DCAPR0                                                   0x30c
#define HDMI_DCAPR0_reg_addr                                          "0x9803430c"
#define HDMI_DCAPR0_reg                                               0x9803430c
#define HDMI_DCAPR0_inst_addr                                         "0x00C3"
#define HDMI_DCAPR0_inst                                              0x00C3
#define set_HDMI_DCAPR0_reg(data)                                     (*((volatile unsigned int*)HDMI_DCAPR0_reg)=data)
#define get_HDMI_DCAPR0_reg                                           (*((volatile unsigned int*)HDMI_DCAPR0_reg))
#define HDMI_DCAPR0_dcaprh_shift                                      (8)
#define HDMI_DCAPR0_dcaprl_shift                                      (0)
#define HDMI_DCAPR0_dcaprh_mask                                       (0x0000FF00)
#define HDMI_DCAPR0_dcaprl_mask                                       (0x000000FF)
#define HDMI_DCAPR0_dcaprh(data)                                      (0x0000FF00&((data)<<8))
#define HDMI_DCAPR0_dcaprl(data)                                      (0x000000FF&(data))
#define HDMI_DCAPR0_get_dcaprh(data)                                  ((0x0000FF00&(data))>>8)
#define HDMI_DCAPR0_get_dcaprl(data)                                  (0x000000FF&(data))


#define HDMI_PSCR                                                     0x310
#define HDMI_PSCR_reg_addr                                            "0x98034310"
#define HDMI_PSCR_reg                                                 0x98034310
#define HDMI_PSCR_inst_addr                                           "0x00C4"
#define HDMI_PSCR_inst                                                0x00C4
#define set_HDMI_PSCR_reg(data)                                       (*((volatile unsigned int*)HDMI_PSCR_reg)=data)
#define get_HDMI_PSCR_reg                                             (*((volatile unsigned int*)HDMI_PSCR_reg))
#define HDMI_PSCR_fdint_shift                                         (5)
#define HDMI_PSCR_etcn_shift                                          (4)
#define HDMI_PSCR_etfd_shift                                          (3)
#define HDMI_PSCR_etfbc_shift                                         (2)
#define HDMI_PSCR_pecs_shift                                          (0)
#define HDMI_PSCR_fdint_mask                                          (0x000000E0)
#define HDMI_PSCR_etcn_mask                                           (0x00000010)
#define HDMI_PSCR_etfd_mask                                           (0x00000008)
#define HDMI_PSCR_etfbc_mask                                          (0x00000004)
#define HDMI_PSCR_pecs_mask                                           (0x00000003)
#define HDMI_PSCR_fdint(data)                                         (0x000000E0&((data)<<5))
#define HDMI_PSCR_etcn(data)                                          (0x00000010&((data)<<4))
#define HDMI_PSCR_etfd(data)                                          (0x00000008&((data)<<3))
#define HDMI_PSCR_etfbc(data)                                         (0x00000004&((data)<<2))
#define HDMI_PSCR_pecs(data)                                          (0x00000003&(data))
#define HDMI_PSCR_get_fdint(data)                                     ((0x000000E0&(data))>>5)
#define HDMI_PSCR_get_etcn(data)                                      ((0x00000010&(data))>>4)
#define HDMI_PSCR_get_etfd(data)                                      ((0x00000008&(data))>>3)
#define HDMI_PSCR_get_etfbc(data)                                     ((0x00000004&(data))>>2)
#define HDMI_PSCR_get_pecs(data)                                      (0x00000003&(data))


#define HDMI_AFDD                                                     0x31c
#define HDMI_AFDD_reg_addr                                            "0x9803431c"
#define HDMI_AFDD_reg                                                 0x9803431c
#define HDMI_AFDD_inst_addr                                           "0x00C7"
#define HDMI_AFDD_inst                                                0x00C7
#define set_HDMI_AFDD_reg(data)                                       (*((volatile unsigned int*)HDMI_AFDD_reg)=data)
#define get_HDMI_AFDD_reg                                             (*((volatile unsigned int*)HDMI_AFDD_reg))
#define HDMI_AFDD_mfddf_shift                                         (24)
#define HDMI_AFDD_mfddr_shift                                         (16)
#define HDMI_AFDD_fddf_shift                                          (8)
#define HDMI_AFDD_fddr_shift                                          (0)
#define HDMI_AFDD_mfddf_mask                                          (0xFF000000)
#define HDMI_AFDD_mfddr_mask                                          (0x00FF0000)
#define HDMI_AFDD_fddf_mask                                           (0x0000FF00)
#define HDMI_AFDD_fddr_mask                                           (0x000000FF)
#define HDMI_AFDD_mfddf(data)                                         (0xFF000000&((data)<<24))
#define HDMI_AFDD_mfddr(data)                                         (0x00FF0000&((data)<<16))
#define HDMI_AFDD_fddf(data)                                          (0x0000FF00&((data)<<8))
#define HDMI_AFDD_fddr(data)                                          (0x000000FF&(data))
#define HDMI_AFDD_get_mfddf(data)                                     ((0xFF000000&(data))>>24)
#define HDMI_AFDD_get_mfddr(data)                                     ((0x00FF0000&(data))>>16)
#define HDMI_AFDD_get_fddf(data)                                      ((0x0000FF00&(data))>>8)
#define HDMI_AFDD_get_fddr(data)                                      (0x000000FF&(data))


#define HDMI_FTR                                                      0x320
#define HDMI_FTR_reg_addr                                             "0x98034320"
#define HDMI_FTR_reg                                                  0x98034320
#define HDMI_FTR_inst_addr                                            "0x00C8"
#define HDMI_FTR_inst                                                 0x00C8
#define set_HDMI_FTR_reg(data)                                        (*((volatile unsigned int*)HDMI_FTR_reg)=data)
#define get_HDMI_FTR_reg                                              (*((volatile unsigned int*)HDMI_FTR_reg))
#define HDMI_FTR_tl2der_shift                                         (6)
#define HDMI_FTR_tl2def_shift                                         (4)
#define HDMI_FTR_tt_shift                                             (0)
#define HDMI_FTR_tl2der_mask                                          (0x000000C0)
#define HDMI_FTR_tl2def_mask                                          (0x00000030)
#define HDMI_FTR_tt_mask                                              (0x0000000F)
#define HDMI_FTR_tl2der(data)                                         (0x000000C0&((data)<<6))
#define HDMI_FTR_tl2def(data)                                         (0x00000030&((data)<<4))
#define HDMI_FTR_tt(data)                                             (0x0000000F&(data))
#define HDMI_FTR_get_tl2der(data)                                     ((0x000000C0&(data))>>6)
#define HDMI_FTR_get_tl2def(data)                                     ((0x00000030&(data))>>4)
#define HDMI_FTR_get_tt(data)                                         (0x0000000F&(data))


#define HDMI_FBR                                                      0x324
#define HDMI_FBR_reg_addr                                             "0x98034324"
#define HDMI_FBR_reg                                                  0x98034324
#define HDMI_FBR_inst_addr                                            "0x00C9"
#define HDMI_FBR_inst                                                 0x00C9
#define set_HDMI_FBR_reg(data)                                        (*((volatile unsigned int*)HDMI_FBR_reg)=data)
#define get_HDMI_FBR_reg                                              (*((volatile unsigned int*)HDMI_FBR_reg))
#define HDMI_FBR_tfd_shift                                            (3)
#define HDMI_FBR_bad_shift                                            (0)
#define HDMI_FBR_tfd_mask                                             (0x000000F8)
#define HDMI_FBR_bad_mask                                             (0x00000007)
#define HDMI_FBR_tfd(data)                                            (0x000000F8&((data)<<3))
#define HDMI_FBR_bad(data)                                            (0x00000007&(data))
#define HDMI_FBR_get_tfd(data)                                        ((0x000000F8&(data))>>3)
#define HDMI_FBR_get_bad(data)                                        (0x00000007&(data))


#define HDMI_ICPSNCR0                                                 0x328
#define HDMI_ICPSNCR0_reg_addr                                        "0x98034328"
#define HDMI_ICPSNCR0_reg                                             0x98034328
#define HDMI_ICPSNCR0_inst_addr                                       "0x00CA"
#define HDMI_ICPSNCR0_inst                                            0x00CA
#define set_HDMI_ICPSNCR0_reg(data)                                   (*((volatile unsigned int*)HDMI_ICPSNCR0_reg)=data)
#define get_HDMI_ICPSNCR0_reg                                         (*((volatile unsigned int*)HDMI_ICPSNCR0_reg))
#define HDMI_ICPSNCR0_ich_shift                                       (8)
#define HDMI_ICPSNCR0_icl_shift                                       (0)
#define HDMI_ICPSNCR0_ich_mask                                        (0x0000FF00)
#define HDMI_ICPSNCR0_icl_mask                                        (0x000000FF)
#define HDMI_ICPSNCR0_ich(data)                                       (0x0000FF00&((data)<<8))
#define HDMI_ICPSNCR0_icl(data)                                       (0x000000FF&(data))
#define HDMI_ICPSNCR0_get_ich(data)                                   ((0x0000FF00&(data))>>8)
#define HDMI_ICPSNCR0_get_icl(data)                                   (0x000000FF&(data))


#define HDMI_PCPSNCR0                                                 0x32c
#define HDMI_PCPSNCR0_reg_addr                                        "0x9803432c"
#define HDMI_PCPSNCR0_reg                                             0x9803432c
#define HDMI_PCPSNCR0_inst_addr                                       "0x00CB"
#define HDMI_PCPSNCR0_inst                                            0x00CB
#define set_HDMI_PCPSNCR0_reg(data)                                   (*((volatile unsigned int*)HDMI_PCPSNCR0_reg)=data)
#define get_HDMI_PCPSNCR0_reg                                         (*((volatile unsigned int*)HDMI_PCPSNCR0_reg))
#define HDMI_PCPSNCR0_pch_shift                                       (8)
#define HDMI_PCPSNCR0_pcl_shift                                       (0)
#define HDMI_PCPSNCR0_pch_mask                                        (0x0000FF00)
#define HDMI_PCPSNCR0_pcl_mask                                        (0x000000FF)
#define HDMI_PCPSNCR0_pch(data)                                       (0x0000FF00&((data)<<8))
#define HDMI_PCPSNCR0_pcl(data)                                       (0x000000FF&(data))
#define HDMI_PCPSNCR0_get_pch(data)                                   ((0x0000FF00&(data))>>8)
#define HDMI_PCPSNCR0_get_pcl(data)                                   (0x000000FF&(data))


#define HDMI_ICTPSR0                                                  0x330
#define HDMI_ICTPSR0_reg_addr                                         "0x98034330"
#define HDMI_ICTPSR0_reg                                              0x98034330
#define HDMI_ICTPSR0_inst_addr                                        "0x00CC"
#define HDMI_ICTPSR0_inst                                             0x00CC
#define set_HDMI_ICTPSR0_reg(data)                                    (*((volatile unsigned int*)HDMI_ICTPSR0_reg)=data)
#define get_HDMI_ICTPSR0_reg                                          (*((volatile unsigned int*)HDMI_ICTPSR0_reg))
#define HDMI_ICTPSR0_icth_shift                                       (8)
#define HDMI_ICTPSR0_ictl_shift                                       (0)
#define HDMI_ICTPSR0_icth_mask                                        (0x0000FF00)
#define HDMI_ICTPSR0_ictl_mask                                        (0x000000FF)
#define HDMI_ICTPSR0_icth(data)                                       (0x0000FF00&((data)<<8))
#define HDMI_ICTPSR0_ictl(data)                                       (0x000000FF&(data))
#define HDMI_ICTPSR0_get_icth(data)                                   ((0x0000FF00&(data))>>8)
#define HDMI_ICTPSR0_get_ictl(data)                                   (0x000000FF&(data))


#define HDMI_PCTPSR0                                                  0x334
#define HDMI_PCTPSR0_reg_addr                                         "0x98034334"
#define HDMI_PCTPSR0_reg                                              0x98034334
#define HDMI_PCTPSR0_inst_addr                                        "0x00CD"
#define HDMI_PCTPSR0_inst                                             0x00CD
#define set_HDMI_PCTPSR0_reg(data)                                    (*((volatile unsigned int*)HDMI_PCTPSR0_reg)=data)
#define get_HDMI_PCTPSR0_reg                                          (*((volatile unsigned int*)HDMI_PCTPSR0_reg))
#define HDMI_PCTPSR0_pcth_shift                                       (8)
#define HDMI_PCTPSR0_pctl_shift                                       (0)
#define HDMI_PCTPSR0_pcth_mask                                        (0x0000FF00)
#define HDMI_PCTPSR0_pctl_mask                                        (0x000000FF)
#define HDMI_PCTPSR0_pcth(data)                                       (0x0000FF00&((data)<<8))
#define HDMI_PCTPSR0_pctl(data)                                       (0x000000FF&(data))
#define HDMI_PCTPSR0_get_pcth(data)                                   ((0x0000FF00&(data))>>8)
#define HDMI_PCTPSR0_get_pctl(data)                                   (0x000000FF&(data))


#define HDMI_ICBPSR0                                                  0x338
#define HDMI_ICBPSR0_reg_addr                                         "0x98034338"
#define HDMI_ICBPSR0_reg                                              0x98034338
#define HDMI_ICBPSR0_inst_addr                                        "0x00CE"
#define HDMI_ICBPSR0_inst                                             0x00CE
#define set_HDMI_ICBPSR0_reg(data)                                    (*((volatile unsigned int*)HDMI_ICBPSR0_reg)=data)
#define get_HDMI_ICBPSR0_reg                                          (*((volatile unsigned int*)HDMI_ICBPSR0_reg))
#define HDMI_ICBPSR0_icbh_shift                                       (8)
#define HDMI_ICBPSR0_icbl_shift                                       (0)
#define HDMI_ICBPSR0_icbh_mask                                        (0x0000FF00)
#define HDMI_ICBPSR0_icbl_mask                                        (0x000000FF)
#define HDMI_ICBPSR0_icbh(data)                                       (0x0000FF00&((data)<<8))
#define HDMI_ICBPSR0_icbl(data)                                       (0x000000FF&(data))
#define HDMI_ICBPSR0_get_icbh(data)                                   ((0x0000FF00&(data))>>8)
#define HDMI_ICBPSR0_get_icbl(data)                                   (0x000000FF&(data))


#define HDMI_PCBPSR0                                                  0x33c
#define HDMI_PCBPSR0_reg_addr                                         "0x9803433c"
#define HDMI_PCBPSR0_reg                                              0x9803433c
#define HDMI_PCBPSR0_inst_addr                                        "0x00CF"
#define HDMI_PCBPSR0_inst                                             0x00CF
#define set_HDMI_PCBPSR0_reg(data)                                    (*((volatile unsigned int*)HDMI_PCBPSR0_reg)=data)
#define get_HDMI_PCBPSR0_reg                                          (*((volatile unsigned int*)HDMI_PCBPSR0_reg))
#define HDMI_PCBPSR0_pcbh_shift                                       (8)
#define HDMI_PCBPSR0_pcbl_shift                                       (0)
#define HDMI_PCBPSR0_pcbh_mask                                        (0x0000FF00)
#define HDMI_PCBPSR0_pcbl_mask                                        (0x000000FF)
#define HDMI_PCBPSR0_pcbh(data)                                       (0x0000FF00&((data)<<8))
#define HDMI_PCBPSR0_pcbl(data)                                       (0x000000FF&(data))
#define HDMI_PCBPSR0_get_pcbh(data)                                   ((0x0000FF00&(data))>>8)
#define HDMI_PCBPSR0_get_pcbl(data)                                   (0x000000FF&(data))


#define HDMI_NTX1024TR0                                               0x340
#define HDMI_NTX1024TR0_reg_addr                                      "0x98034340"
#define HDMI_NTX1024TR0_reg                                           0x98034340
#define HDMI_NTX1024TR0_inst_addr                                     "0x00D0"
#define HDMI_NTX1024TR0_inst                                          0x00D0
#define set_HDMI_NTX1024TR0_reg(data)                                 (*((volatile unsigned int*)HDMI_NTX1024TR0_reg)=data)
#define get_HDMI_NTX1024TR0_reg                                       (*((volatile unsigned int*)HDMI_NTX1024TR0_reg))
#define HDMI_NTX1024TR0_rm_shift                                      (12)
#define HDMI_NTX1024TR0_nt_shift                                      (0)
#define HDMI_NTX1024TR0_rm_mask                                       (0x00001000)
#define HDMI_NTX1024TR0_nt_mask                                       (0x00000FFF)
#define HDMI_NTX1024TR0_rm(data)                                      (0x00001000&((data)<<12))
#define HDMI_NTX1024TR0_nt(data)                                      (0x00000FFF&(data))
#define HDMI_NTX1024TR0_get_rm(data)                                  ((0x00001000&(data))>>12)
#define HDMI_NTX1024TR0_get_nt(data)                                  (0x00000FFF&(data))


#define HDMI_STBPR                                                    0x344
#define HDMI_STBPR_reg_addr                                           "0x98034344"
#define HDMI_STBPR_reg                                                0x98034344
#define HDMI_STBPR_inst_addr                                          "0x00D1"
#define HDMI_STBPR_inst                                               0x00D1
#define set_HDMI_STBPR_reg(data)                                      (*((volatile unsigned int*)HDMI_STBPR_reg)=data)
#define get_HDMI_STBPR_reg                                            (*((volatile unsigned int*)HDMI_STBPR_reg))
#define HDMI_STBPR_ftb_shift                                          (0)
#define HDMI_STBPR_ftb_mask                                           (0x000000FF)
#define HDMI_STBPR_ftb(data)                                          (0x000000FF&(data))
#define HDMI_STBPR_get_ftb(data)                                      (0x000000FF&(data))


#define HDMI_NCPER                                                    0x348
#define HDMI_NCPER_reg_addr                                           "0x98034348"
#define HDMI_NCPER_reg                                                0x98034348
#define HDMI_NCPER_inst_addr                                          "0x00D2"
#define HDMI_NCPER_inst                                               0x00D2
#define set_HDMI_NCPER_reg(data)                                      (*((volatile unsigned int*)HDMI_NCPER_reg)=data)
#define get_HDMI_NCPER_reg                                            (*((volatile unsigned int*)HDMI_NCPER_reg))
#define HDMI_NCPER_ncper_shift                                        (0)
#define HDMI_NCPER_ncper_mask                                         (0x000000FF)
#define HDMI_NCPER_ncper(data)                                        (0x000000FF&(data))
#define HDMI_NCPER_get_ncper(data)                                    (0x000000FF&(data))


#define HDMI_PETR                                                     0x34c
#define HDMI_PETR_reg_addr                                            "0x9803434c"
#define HDMI_PETR_reg                                                 0x9803434c
#define HDMI_PETR_inst_addr                                           "0x00D3"
#define HDMI_PETR_inst                                                0x00D3
#define set_HDMI_PETR_reg(data)                                       (*((volatile unsigned int*)HDMI_PETR_reg)=data)
#define get_HDMI_PETR_reg                                             (*((volatile unsigned int*)HDMI_PETR_reg))
#define HDMI_PETR_petr_shift                                          (0)
#define HDMI_PETR_petr_mask                                           (0x000000FF)
#define HDMI_PETR_petr(data)                                          (0x000000FF&(data))
#define HDMI_PETR_get_petr(data)                                      (0x000000FF&(data))


#define HDMI_AAPNR                                                    0x350
#define HDMI_AAPNR_reg_addr                                           "0x98034350"
#define HDMI_AAPNR_reg                                                0x98034350
#define HDMI_AAPNR_inst_addr                                          "0x00D4"
#define HDMI_AAPNR_inst                                               0x00D4
#define set_HDMI_AAPNR_reg(data)                                      (*((volatile unsigned int*)HDMI_AAPNR_reg)=data)
#define get_HDMI_AAPNR_reg                                            (*((volatile unsigned int*)HDMI_AAPNR_reg))
#define HDMI_AAPNR_cmvtc_shift                                        (7)
#define HDMI_AAPNR_cmvbc_shift                                        (6)
#define HDMI_AAPNR_ssdmou_shift                                       (5)
#define HDMI_AAPNR_tef_shift                                          (4)
#define HDMI_AAPNR_w1c5_shift                                         (3)
#define HDMI_AAPNR_pem_shift                                          (2)
#define HDMI_AAPNR_esdm_shift                                         (1)
#define HDMI_AAPNR_dummy_0_shift                                      (0)
#define HDMI_AAPNR_cmvtc_mask                                         (0x00000080)
#define HDMI_AAPNR_cmvbc_mask                                         (0x00000040)
#define HDMI_AAPNR_ssdmou_mask                                        (0x00000020)
#define HDMI_AAPNR_tef_mask                                           (0x00000010)
#define HDMI_AAPNR_w1c5_mask                                          (0x00000008)
#define HDMI_AAPNR_pem_mask                                           (0x00000004)
#define HDMI_AAPNR_esdm_mask                                          (0x00000002)
#define HDMI_AAPNR_dummy_0_mask                                       (0x00000001)
#define HDMI_AAPNR_cmvtc(data)                                        (0x00000080&((data)<<7))
#define HDMI_AAPNR_cmvbc(data)                                        (0x00000040&((data)<<6))
#define HDMI_AAPNR_ssdmou(data)                                       (0x00000020&((data)<<5))
#define HDMI_AAPNR_tef(data)                                          (0x00000010&((data)<<4))
#define HDMI_AAPNR_w1c5(data)                                         (0x00000008&((data)<<3))
#define HDMI_AAPNR_pem(data)                                          (0x00000004&((data)<<2))
#define HDMI_AAPNR_esdm(data)                                         (0x00000002&((data)<<1))
#define HDMI_AAPNR_dummy_0(data)                                      (0x00000001&(data))
#define HDMI_AAPNR_get_cmvtc(data)                                    ((0x00000080&(data))>>7)
#define HDMI_AAPNR_get_cmvbc(data)                                    ((0x00000040&(data))>>6)
#define HDMI_AAPNR_get_ssdmou(data)                                   ((0x00000020&(data))>>5)
#define HDMI_AAPNR_get_tef(data)                                      ((0x00000010&(data))>>4)
#define HDMI_AAPNR_get_w1c5(data)                                     ((0x00000008&(data))>>3)
#define HDMI_AAPNR_get_pem(data)                                      ((0x00000004&(data))>>2)
#define HDMI_AAPNR_get_esdm(data)                                     ((0x00000002&(data))>>1)
#define HDMI_AAPNR_get_dummy_0(data)                                  (0x00000001&(data))


#define HDMI_APDMCR                                                   0x354
#define HDMI_APDMCR_reg_addr                                          "0x98034354"
#define HDMI_APDMCR_reg                                               0x98034354
#define HDMI_APDMCR_inst_addr                                         "0x00D5"
#define HDMI_APDMCR_inst                                              0x00D5
#define set_HDMI_APDMCR_reg(data)                                     (*((volatile unsigned int*)HDMI_APDMCR_reg)=data)
#define get_HDMI_APDMCR_reg                                           (*((volatile unsigned int*)HDMI_APDMCR_reg))
#define HDMI_APDMCR_dummy_7_shift                                     (7)
#define HDMI_APDMCR_dummy_6_shift                                     (6)
#define HDMI_APDMCR_edm_shift                                         (5)
#define HDMI_APDMCR_pst_shift                                         (4)
#define HDMI_APDMCR_psc_shift                                         (0)
#define HDMI_APDMCR_dummy_7_mask                                      (0x00000080)
#define HDMI_APDMCR_dummy_6_mask                                      (0x00000040)
#define HDMI_APDMCR_edm_mask                                          (0x00000020)
#define HDMI_APDMCR_pst_mask                                          (0x00000010)
#define HDMI_APDMCR_psc_mask                                          (0x0000000F)
#define HDMI_APDMCR_dummy_7(data)                                     (0x00000080&((data)<<7))
#define HDMI_APDMCR_dummy_6(data)                                     (0x00000040&((data)<<6))
#define HDMI_APDMCR_edm(data)                                         (0x00000020&((data)<<5))
#define HDMI_APDMCR_pst(data)                                         (0x00000010&((data)<<4))
#define HDMI_APDMCR_psc(data)                                         (0x0000000F&(data))
#define HDMI_APDMCR_get_dummy_7(data)                                 ((0x00000080&(data))>>7)
#define HDMI_APDMCR_get_dummy_6(data)                                 ((0x00000040&(data))>>6)
#define HDMI_APDMCR_get_edm(data)                                     ((0x00000020&(data))>>5)
#define HDMI_APDMCR_get_pst(data)                                     ((0x00000010&(data))>>4)
#define HDMI_APDMCR_get_psc(data)                                     (0x0000000F&(data))


#define HDMI_APTMCR0                                                  0x358
#define HDMI_APTMCR0_reg_addr                                         "0x98034358"
#define HDMI_APTMCR0_reg                                              0x98034358
#define HDMI_APTMCR0_inst_addr                                        "0x00D6"
#define HDMI_APTMCR0_inst                                             0x00D6
#define set_HDMI_APTMCR0_reg(data)                                    (*((volatile unsigned int*)HDMI_APTMCR0_reg)=data)
#define get_HDMI_APTMCR0_reg                                          (*((volatile unsigned int*)HDMI_APTMCR0_reg))
#define HDMI_APTMCR0_fps_shift                                        (4)
#define HDMI_APTMCR0_sps_shift                                        (0)
#define HDMI_APTMCR0_fps_mask                                         (0x000000F0)
#define HDMI_APTMCR0_sps_mask                                         (0x0000000F)
#define HDMI_APTMCR0_fps(data)                                        (0x000000F0&((data)<<4))
#define HDMI_APTMCR0_sps(data)                                        (0x0000000F&(data))
#define HDMI_APTMCR0_get_fps(data)                                    ((0x000000F0&(data))>>4)
#define HDMI_APTMCR0_get_sps(data)                                    (0x0000000F&(data))


#define HDMI_APTMCR1                                                  0x35c
#define HDMI_APTMCR1_reg_addr                                         "0x9803435c"
#define HDMI_APTMCR1_reg                                              0x9803435c
#define HDMI_APTMCR1_inst_addr                                        "0x00D7"
#define HDMI_APTMCR1_inst                                             0x00D7
#define set_HDMI_APTMCR1_reg(data)                                    (*((volatile unsigned int*)HDMI_APTMCR1_reg)=data)
#define get_HDMI_APTMCR1_reg                                          (*((volatile unsigned int*)HDMI_APTMCR1_reg))
#define HDMI_APTMCR1_plltm_shift                                      (6)
#define HDMI_APTMCR1_fpsd_shift                                       (5)
#define HDMI_APTMCR1_spsd_shift                                       (4)
#define HDMI_APTMCR1_nfpss_shift                                      (0)
#define HDMI_APTMCR1_plltm_mask                                       (0x00000040)
#define HDMI_APTMCR1_fpsd_mask                                        (0x00000020)
#define HDMI_APTMCR1_spsd_mask                                        (0x00000010)
#define HDMI_APTMCR1_nfpss_mask                                       (0x0000000F)
#define HDMI_APTMCR1_plltm(data)                                      (0x00000040&((data)<<6))
#define HDMI_APTMCR1_fpsd(data)                                       (0x00000020&((data)<<5))
#define HDMI_APTMCR1_spsd(data)                                       (0x00000010&((data)<<4))
#define HDMI_APTMCR1_nfpss(data)                                      (0x0000000F&(data))
#define HDMI_APTMCR1_get_plltm(data)                                  ((0x00000040&(data))>>6)
#define HDMI_APTMCR1_get_fpsd(data)                                   ((0x00000020&(data))>>5)
#define HDMI_APTMCR1_get_spsd(data)                                   ((0x00000010&(data))>>4)
#define HDMI_APTMCR1_get_nfpss(data)                                  (0x0000000F&(data))


#define HDMI_NPECR                                                    0x360
#define HDMI_NPECR_reg_addr                                           "0x98034360"
#define HDMI_NPECR_reg                                                0x98034360
#define HDMI_NPECR_inst_addr                                          "0x00D8"
#define HDMI_NPECR_inst                                               0x00D8
#define set_HDMI_NPECR_reg(data)                                      (*((volatile unsigned int*)HDMI_NPECR_reg)=data)
#define get_HDMI_NPECR_reg                                            (*((volatile unsigned int*)HDMI_NPECR_reg))
#define HDMI_NPECR_ncts_disable_pe_check_en_shift                     (31)
#define HDMI_NPECR_ncts_re_enable_off_en_shift                        (30)
#define HDMI_NPECR_ncts_disable_pe_check_status_shift                 (29)
#define HDMI_NPECR_ncts_disable_pe_check_irq_en_shift                 (28)
#define HDMI_NPECR_dummy_27_20_shift                                  (20)
#define HDMI_NPECR_ncts_disable_pe_check_cnt_shift                    (0)
#define HDMI_NPECR_ncts_disable_pe_check_en_mask                      (0x80000000)
#define HDMI_NPECR_ncts_re_enable_off_en_mask                         (0x40000000)
#define HDMI_NPECR_ncts_disable_pe_check_status_mask                  (0x20000000)
#define HDMI_NPECR_ncts_disable_pe_check_irq_en_mask                  (0x10000000)
#define HDMI_NPECR_dummy_27_20_mask                                   (0x0FF00000)
#define HDMI_NPECR_ncts_disable_pe_check_cnt_mask                     (0x000FFFFF)
#define HDMI_NPECR_ncts_disable_pe_check_en(data)                     (0x80000000&((data)<<31))
#define HDMI_NPECR_ncts_re_enable_off_en(data)                        (0x40000000&((data)<<30))
#define HDMI_NPECR_ncts_disable_pe_check_status(data)                 (0x20000000&((data)<<29))
#define HDMI_NPECR_ncts_disable_pe_check_irq_en(data)                 (0x10000000&((data)<<28))
#define HDMI_NPECR_dummy_27_20(data)                                  (0x0FF00000&((data)<<20))
#define HDMI_NPECR_ncts_disable_pe_check_cnt(data)                    (0x000FFFFF&(data))
#define HDMI_NPECR_get_ncts_disable_pe_check_en(data)                 ((0x80000000&(data))>>31)
#define HDMI_NPECR_get_ncts_re_enable_off_en(data)                    ((0x40000000&(data))>>30)
#define HDMI_NPECR_get_ncts_disable_pe_check_status(data)             ((0x20000000&(data))>>29)
#define HDMI_NPECR_get_ncts_disable_pe_check_irq_en(data)             ((0x10000000&(data))>>28)
#define HDMI_NPECR_get_dummy_27_20(data)                              ((0x0FF00000&(data))>>20)
#define HDMI_NPECR_get_ncts_disable_pe_check_cnt(data)                (0x000FFFFF&(data))


#define HDMI_NROR                                                     0x364
#define HDMI_NROR_reg_addr                                            "0x98034364"
#define HDMI_NROR_reg                                                 0x98034364
#define HDMI_NROR_inst_addr                                           "0x00D9"
#define HDMI_NROR_inst                                                0x00D9
#define set_HDMI_NROR_reg(data)                                       (*((volatile unsigned int*)HDMI_NROR_reg)=data)
#define get_HDMI_NROR_reg                                             (*((volatile unsigned int*)HDMI_NROR_reg))
#define HDMI_NROR_ncts_re_enable_off_start_shift                      (16)
#define HDMI_NROR_ncts_re_enable_off_end_shift                        (0)
#define HDMI_NROR_ncts_re_enable_off_start_mask                       (0xFFFF0000)
#define HDMI_NROR_ncts_re_enable_off_end_mask                         (0x0000FFFF)
#define HDMI_NROR_ncts_re_enable_off_start(data)                      (0xFFFF0000&((data)<<16))
#define HDMI_NROR_ncts_re_enable_off_end(data)                        (0x0000FFFF&(data))
#define HDMI_NROR_get_ncts_re_enable_off_start(data)                  ((0xFFFF0000&(data))>>16)
#define HDMI_NROR_get_ncts_re_enable_off_end(data)                    (0x0000FFFF&(data))


#define HDMI_NTX1024TR0_THRESHOLD                                     0x368
#define HDMI_NTX1024TR0_THRESHOLD_reg_addr                            "0x98034368"
#define HDMI_NTX1024TR0_THRESHOLD_reg                                 0x98034368
#define HDMI_NTX1024TR0_THRESHOLD_inst_addr                           "0x00DA"
#define HDMI_NTX1024TR0_THRESHOLD_inst                                0x00DA
#define set_HDMI_NTX1024TR0_THRESHOLD_reg(data)                       (*((volatile unsigned int*)HDMI_NTX1024TR0_THRESHOLD_reg)=data)
#define get_HDMI_NTX1024TR0_THRESHOLD_reg                             (*((volatile unsigned int*)HDMI_NTX1024TR0_THRESHOLD_reg))
#define HDMI_NTX1024TR0_THRESHOLD_over_threshold_shift                (31)
#define HDMI_NTX1024TR0_THRESHOLD_under_threshold_shift               (30)
#define HDMI_NTX1024TR0_THRESHOLD_wd_by_tmds_clk_shift                (29)
#define HDMI_NTX1024TR0_THRESHOLD_irq_by_tmds_clk_shift               (28)
#define HDMI_NTX1024TR0_THRESHOLD_nt_up_threshold_shift               (16)
#define HDMI_NTX1024TR0_THRESHOLD_nt_low_threshold_shift              (0)
#define HDMI_NTX1024TR0_THRESHOLD_over_threshold_mask                 (0x80000000)
#define HDMI_NTX1024TR0_THRESHOLD_under_threshold_mask                (0x40000000)
#define HDMI_NTX1024TR0_THRESHOLD_wd_by_tmds_clk_mask                 (0x20000000)
#define HDMI_NTX1024TR0_THRESHOLD_irq_by_tmds_clk_mask                (0x10000000)
#define HDMI_NTX1024TR0_THRESHOLD_nt_up_threshold_mask                (0x0FFF0000)
#define HDMI_NTX1024TR0_THRESHOLD_nt_low_threshold_mask               (0x00000FFF)
#define HDMI_NTX1024TR0_THRESHOLD_over_threshold(data)                (0x80000000&((data)<<31))
#define HDMI_NTX1024TR0_THRESHOLD_under_threshold(data)               (0x40000000&((data)<<30))
#define HDMI_NTX1024TR0_THRESHOLD_wd_by_tmds_clk(data)                (0x20000000&((data)<<29))
#define HDMI_NTX1024TR0_THRESHOLD_irq_by_tmds_clk(data)               (0x10000000&((data)<<28))
#define HDMI_NTX1024TR0_THRESHOLD_nt_up_threshold(data)               (0x0FFF0000&((data)<<16))
#define HDMI_NTX1024TR0_THRESHOLD_nt_low_threshold(data)              (0x00000FFF&(data))
#define HDMI_NTX1024TR0_THRESHOLD_get_over_threshold(data)            ((0x80000000&(data))>>31)
#define HDMI_NTX1024TR0_THRESHOLD_get_under_threshold(data)           ((0x40000000&(data))>>30)
#define HDMI_NTX1024TR0_THRESHOLD_get_wd_by_tmds_clk(data)            ((0x20000000&(data))>>29)
#define HDMI_NTX1024TR0_THRESHOLD_get_irq_by_tmds_clk(data)           ((0x10000000&(data))>>28)
#define HDMI_NTX1024TR0_THRESHOLD_get_nt_up_threshold(data)           ((0x0FFF0000&(data))>>16)
#define HDMI_NTX1024TR0_THRESHOLD_get_nt_low_threshold(data)          (0x00000FFF&(data))


#define HDMI_APLLCR0                                                  0x380
#define HDMI_APLLCR0_reg_addr                                         "0x98034380"
#define HDMI_APLLCR0_reg                                              0x98034380
#define HDMI_APLLCR0_inst_addr                                        "0x00E0"
#define HDMI_APLLCR0_inst                                             0x00E0
#define set_HDMI_APLLCR0_reg(data)                                    (*((volatile unsigned int*)HDMI_APLLCR0_reg)=data)
#define get_HDMI_APLLCR0_reg                                          (*((volatile unsigned int*)HDMI_APLLCR0_reg))
#define HDMI_APLLCR0_dpll_reg_shift                                   (30)
#define HDMI_APLLCR0_dpll_m_shift                                     (22)
#define HDMI_APLLCR0_dpll_reser_shift                                 (17)
#define HDMI_APLLCR0_dpll_bpsin_shift                                 (16)
#define HDMI_APLLCR0_dpll_o_shift                                     (14)
#define HDMI_APLLCR0_dpll_n_shift                                     (6)
#define HDMI_APLLCR0_dpll_rs_shift                                    (3)
#define HDMI_APLLCR0_dpll_ip_shift                                    (0)
#define HDMI_APLLCR0_dpll_reg_mask                                    (0xC0000000)
#define HDMI_APLLCR0_dpll_m_mask                                      (0x3FC00000)
#define HDMI_APLLCR0_dpll_reser_mask                                  (0x001E0000)
#define HDMI_APLLCR0_dpll_bpsin_mask                                  (0x00010000)
#define HDMI_APLLCR0_dpll_o_mask                                      (0x0000C000)
#define HDMI_APLLCR0_dpll_n_mask                                      (0x000001C0)
#define HDMI_APLLCR0_dpll_rs_mask                                     (0x00000038)
#define HDMI_APLLCR0_dpll_ip_mask                                     (0x00000007)
#define HDMI_APLLCR0_dpll_reg(data)                                   (0xC0000000&((data)<<30))
#define HDMI_APLLCR0_dpll_m(data)                                     (0x3FC00000&((data)<<22))
#define HDMI_APLLCR0_dpll_reser(data)                                 (0x001E0000&((data)<<17))
#define HDMI_APLLCR0_dpll_bpsin(data)                                 (0x00010000&((data)<<16))
#define HDMI_APLLCR0_dpll_o(data)                                     (0x0000C000&((data)<<14))
#define HDMI_APLLCR0_dpll_n(data)                                     (0x000001C0&((data)<<6))
#define HDMI_APLLCR0_dpll_rs(data)                                    (0x00000038&((data)<<3))
#define HDMI_APLLCR0_dpll_ip(data)                                    (0x00000007&(data))
#define HDMI_APLLCR0_get_dpll_reg(data)                               ((0xC0000000&(data))>>30)
#define HDMI_APLLCR0_get_dpll_m(data)                                 ((0x3FC00000&(data))>>22)
#define HDMI_APLLCR0_get_dpll_reser(data)                             ((0x001E0000&(data))>>17)
#define HDMI_APLLCR0_get_dpll_bpsin(data)                             ((0x00010000&(data))>>16)
#define HDMI_APLLCR0_get_dpll_o(data)                                 ((0x0000C000&(data))>>14)
#define HDMI_APLLCR0_get_dpll_n(data)                                 ((0x000001C0&(data))>>6)
#define HDMI_APLLCR0_get_dpll_rs(data)                                ((0x00000038&(data))>>3)
#define HDMI_APLLCR0_get_dpll_ip(data)                                (0x00000007&(data))


#define HDMI_APLLCR1                                                  0x384
#define HDMI_APLLCR1_reg_addr                                         "0x98034384"
#define HDMI_APLLCR1_reg                                              0x98034384
#define HDMI_APLLCR1_inst_addr                                        "0x00E1"
#define HDMI_APLLCR1_inst                                             0x00E1
#define set_HDMI_APLLCR1_reg(data)                                    (*((volatile unsigned int*)HDMI_APLLCR1_reg)=data)
#define get_HDMI_APLLCR1_reg                                          (*((volatile unsigned int*)HDMI_APLLCR1_reg))
#define HDMI_APLLCR1_dpll_cp_shift                                    (21)
#define HDMI_APLLCR1_dpll_seltst_shift                                (19)
#define HDMI_APLLCR1_dpll_cs_shift                                    (17)
#define HDMI_APLLCR1_dpll_reserve_shift                               (9)
#define HDMI_APLLCR1_dpll_bpspsw_shift                                (8)
#define HDMI_APLLCR1_dpll_wdo_shift                                   (7)
#define HDMI_APLLCR1_dpll_wdrst_shift                                 (6)
#define HDMI_APLLCR1_dpll_wdset_shift                                 (5)
#define HDMI_APLLCR1_dummy_4_shift                                    (4)
#define HDMI_APLLCR1_dpll_stoppsw_shift                               (3)
#define HDMI_APLLCR1_dpll_freeze_shift                                (2)
#define HDMI_APLLCR1_dpll_vcorstb_shift                               (1)
#define HDMI_APLLCR1_dpll_pow_shift                                   (0)
#define HDMI_APLLCR1_dpll_cp_mask                                     (0x00600000)
#define HDMI_APLLCR1_dpll_seltst_mask                                 (0x00180000)
#define HDMI_APLLCR1_dpll_cs_mask                                     (0x00060000)
#define HDMI_APLLCR1_dpll_reserve_mask                                (0x00000200)
#define HDMI_APLLCR1_dpll_bpspsw_mask                                 (0x00000100)
#define HDMI_APLLCR1_dpll_wdo_mask                                    (0x00000080)
#define HDMI_APLLCR1_dpll_wdrst_mask                                  (0x00000040)
#define HDMI_APLLCR1_dpll_wdset_mask                                  (0x00000020)
#define HDMI_APLLCR1_dummy_4_mask                                     (0x00000010)
#define HDMI_APLLCR1_dpll_stoppsw_mask                                (0x00000008)
#define HDMI_APLLCR1_dpll_freeze_mask                                 (0x00000004)
#define HDMI_APLLCR1_dpll_vcorstb_mask                                (0x00000002)
#define HDMI_APLLCR1_dpll_pow_mask                                    (0x00000001)
#define HDMI_APLLCR1_dpll_cp(data)                                    (0x00600000&((data)<<21))
#define HDMI_APLLCR1_dpll_seltst(data)                                (0x00180000&((data)<<19))
#define HDMI_APLLCR1_dpll_cs(data)                                    (0x00060000&((data)<<17))
#define HDMI_APLLCR1_dpll_reserve(data)                               (0x00000200&((data)<<9))
#define HDMI_APLLCR1_dpll_bpspsw(data)                                (0x00000100&((data)<<8))
#define HDMI_APLLCR1_dpll_wdo(data)                                   (0x00000080&((data)<<7))
#define HDMI_APLLCR1_dpll_wdrst(data)                                 (0x00000040&((data)<<6))
#define HDMI_APLLCR1_dpll_wdset(data)                                 (0x00000020&((data)<<5))
#define HDMI_APLLCR1_dummy_4(data)                                    (0x00000010&((data)<<4))
#define HDMI_APLLCR1_dpll_stoppsw(data)                               (0x00000008&((data)<<3))
#define HDMI_APLLCR1_dpll_freeze(data)                                (0x00000004&((data)<<2))
#define HDMI_APLLCR1_dpll_vcorstb(data)                               (0x00000002&((data)<<1))
#define HDMI_APLLCR1_dpll_pow(data)                                   (0x00000001&(data))
#define HDMI_APLLCR1_get_dpll_cp(data)                                ((0x00600000&(data))>>21)
#define HDMI_APLLCR1_get_dpll_seltst(data)                            ((0x00180000&(data))>>19)
#define HDMI_APLLCR1_get_dpll_cs(data)                                ((0x00060000&(data))>>17)
#define HDMI_APLLCR1_get_dpll_reserve(data)                           ((0x00000200&(data))>>9)
#define HDMI_APLLCR1_get_dpll_bpspsw(data)                            ((0x00000100&(data))>>8)
#define HDMI_APLLCR1_get_dpll_wdo(data)                               ((0x00000080&(data))>>7)
#define HDMI_APLLCR1_get_dpll_wdrst(data)                             ((0x00000040&(data))>>6)
#define HDMI_APLLCR1_get_dpll_wdset(data)                             ((0x00000020&(data))>>5)
#define HDMI_APLLCR1_get_dummy_4(data)                                ((0x00000010&(data))>>4)
#define HDMI_APLLCR1_get_dpll_stoppsw(data)                           ((0x00000008&(data))>>3)
#define HDMI_APLLCR1_get_dpll_freeze(data)                            ((0x00000004&(data))>>2)
#define HDMI_APLLCR1_get_dpll_vcorstb(data)                           ((0x00000002&(data))>>1)
#define HDMI_APLLCR1_get_dpll_pow(data)                               (0x00000001&(data))
#define HDMI_APLLCR1_dpll_CS_MASK									((1<<18)|(1<<17))
#define HDMI_APLLCR1_dpll_CS_20P									(0)
#define HDMI_APLLCR1_dpll_CS_25P									(1<<17)
#define HDMI_APLLCR1_dpll_CS_30P									(2<<17)
#define HDMI_APLLCR1_dpll_CS_35P									(3<<17)


#define HDMI_APLLCR2                                                  0x388
#define HDMI_APLLCR2_reg_addr                                         "0x98034388"
#define HDMI_APLLCR2_reg                                              0x98034388
#define HDMI_APLLCR2_inst_addr                                        "0x00E2"
#define HDMI_APLLCR2_inst                                             0x00E2
#define set_HDMI_APLLCR2_reg(data)                                    (*((volatile unsigned int*)HDMI_APLLCR2_reg)=data)
#define get_HDMI_APLLCR2_reg                                          (*((volatile unsigned int*)HDMI_APLLCR2_reg))
#define HDMI_APLLCR2_dpll_reloadm_shift                               (0)
#define HDMI_APLLCR2_dpll_reloadm_mask                                (0x00000001)
#define HDMI_APLLCR2_dpll_reloadm(data)                               (0x00000001&(data))
#define HDMI_APLLCR2_get_dpll_reloadm(data)                           (0x00000001&(data))


#define HDMI_APLLCR3                                                  0x38c
#define HDMI_APLLCR3_reg_addr                                         "0x9803438c"
#define HDMI_APLLCR3_reg                                              0x9803438c
#define HDMI_APLLCR3_inst_addr                                        "0x00E3"
#define HDMI_APLLCR3_inst                                             0x00E3
#define set_HDMI_APLLCR3_reg(data)                                    (*((volatile unsigned int*)HDMI_APLLCR3_reg)=data)
#define get_HDMI_APLLCR3_reg                                          (*((volatile unsigned int*)HDMI_APLLCR3_reg))
#define HDMI_APLLCR3_sum_c_samp_shift                                 (0)
#define HDMI_APLLCR3_sum_c_samp_mask                                  (0x0000FFFF)
#define HDMI_APLLCR3_sum_c_samp(data)                                 (0x0000FFFF&(data))
#define HDMI_APLLCR3_get_sum_c_samp(data)                             (0x0000FFFF&(data))


#define HDMI_APLL_TESTM                                               0x390
#define HDMI_APLL_TESTM_reg_addr                                      "0x98034390"
#define HDMI_APLL_TESTM_reg                                           0x98034390
#define HDMI_APLL_TESTM_inst_addr                                     "0x00E4"
#define HDMI_APLL_TESTM_inst                                          0x00E4
#define set_HDMI_APLL_TESTM_reg(data)                                 (*((volatile unsigned int*)HDMI_APLL_TESTM_reg)=data)
#define get_HDMI_APLL_TESTM_reg                                       (*((volatile unsigned int*)HDMI_APLL_TESTM_reg))
#define HDMI_APLL_TESTM_dpll_m_test_shift                             (22)
#define HDMI_APLL_TESTM_dpll_m_db_shift                               (1)
#define HDMI_APLL_TESTM_dpll_m_sel_shift                              (0)
#define HDMI_APLL_TESTM_dpll_m_test_mask                              (0x3FC00000)
#define HDMI_APLL_TESTM_dpll_m_db_mask                                (0x00000002)
#define HDMI_APLL_TESTM_dpll_m_sel_mask                               (0x00000001)
#define HDMI_APLL_TESTM_dpll_m_test(data)                             (0x3FC00000&((data)<<22))
#define HDMI_APLL_TESTM_dpll_m_db(data)                               (0x00000002&((data)<<1))
#define HDMI_APLL_TESTM_dpll_m_sel(data)                              (0x00000001&(data))
#define HDMI_APLL_TESTM_get_dpll_m_test(data)                         ((0x3FC00000&(data))>>22)
#define HDMI_APLL_TESTM_get_dpll_m_db(data)                           ((0x00000002&(data))>>1)
#define HDMI_APLL_TESTM_get_dpll_m_sel(data)                          (0x00000001&(data))


#define HDMI_VPLLCR0                                                  0x400
#define HDMI_VPLLCR0_reg_addr                                         "0x98034400"
#define HDMI_VPLLCR0_reg                                              0x98034400
#define HDMI_VPLLCR0_inst_addr                                        "0x0100"
#define HDMI_VPLLCR0_inst                                             0x0100
#define set_HDMI_VPLLCR0_reg(data)                                    (*((volatile unsigned int*)HDMI_VPLLCR0_reg)=data)
#define get_HDMI_VPLLCR0_reg                                          (*((volatile unsigned int*)HDMI_VPLLCR0_reg))
#define HDMI_VPLLCR0_dpll_reg_shift                                   (30)
#define HDMI_VPLLCR0_dpll_m_shift                                     (22)
#define HDMI_VPLLCR0_dpll_reser_shift                                 (17)
#define HDMI_VPLLCR0_dpll_bpsin_shift                                 (16)
#define HDMI_VPLLCR0_dpll_o_shift                                     (14)
#define HDMI_VPLLCR0_dpll_n_shift                                     (6)
#define HDMI_VPLLCR0_dpll_rs_shift                                    (3)
#define HDMI_VPLLCR0_dpll_ip_shift                                    (0)
#define HDMI_VPLLCR0_dpll_reg_mask                                    (0xC0000000)
#define HDMI_VPLLCR0_dpll_m_mask                                      (0x3FC00000)
#define HDMI_VPLLCR0_dpll_reser_mask                                  (0x001E0000)
#define HDMI_VPLLCR0_dpll_bpsin_mask                                  (0x00010000)
#define HDMI_VPLLCR0_dpll_o_mask                                      (0x0000C000)
#define HDMI_VPLLCR0_dpll_n_mask                                      (0x000001C0)
#define HDMI_VPLLCR0_dpll_rs_mask                                     (0x00000038)
#define HDMI_VPLLCR0_dpll_ip_mask                                     (0x00000007)
#define HDMI_VPLLCR0_dpll_reg(data)                                   (0xC0000000&((data)<<30))
#define HDMI_VPLLCR0_dpll_m(data)                                     (0x3FC00000&((data)<<22))
#define HDMI_VPLLCR0_dpll_reser(data)                                 (0x001E0000&((data)<<17))
#define HDMI_VPLLCR0_dpll_bpsin(data)                                 (0x00010000&((data)<<16))
#define HDMI_VPLLCR0_dpll_o(data)                                     (0x0000C000&((data)<<14))
#define HDMI_VPLLCR0_dpll_n(data)                                     (0x000001C0&((data)<<6))
#define HDMI_VPLLCR0_dpll_rs(data)                                    (0x00000038&((data)<<3))
#define HDMI_VPLLCR0_dpll_ip(data)                                    (0x00000007&(data))
#define HDMI_VPLLCR0_get_dpll_reg(data)                               ((0xC0000000&(data))>>30)
#define HDMI_VPLLCR0_get_dpll_m(data)                                 ((0x3FC00000&(data))>>22)
#define HDMI_VPLLCR0_get_dpll_reser(data)                             ((0x001E0000&(data))>>17)
#define HDMI_VPLLCR0_get_dpll_bpsin(data)                             ((0x00010000&(data))>>16)
#define HDMI_VPLLCR0_get_dpll_o(data)                                 ((0x0000C000&(data))>>14)
#define HDMI_VPLLCR0_get_dpll_n(data)                                 ((0x000001C0&(data))>>6)
#define HDMI_VPLLCR0_get_dpll_rs(data)                                ((0x00000038&(data))>>3)
#define HDMI_VPLLCR0_get_dpll_ip(data)                                (0x00000007&(data))


#define HDMI_VPLLCR1                                                  0x404
#define HDMI_VPLLCR1_reg_addr                                         "0x98034404"
#define HDMI_VPLLCR1_reg                                              0x98034404
#define HDMI_VPLLCR1_inst_addr                                        "0x0101"
#define HDMI_VPLLCR1_inst                                             0x0101
#define set_HDMI_VPLLCR1_reg(data)                                    (*((volatile unsigned int*)HDMI_VPLLCR1_reg)=data)
#define get_HDMI_VPLLCR1_reg                                          (*((volatile unsigned int*)HDMI_VPLLCR1_reg))
#define HDMI_VPLLCR1_dpll_cp_shift                                    (21)
#define HDMI_VPLLCR1_dpll_seltst_shift                                (19)
#define HDMI_VPLLCR1_dpll_cs_shift                                    (17)
#define HDMI_VPLLCR1_dpll_ldo_pow_shift                               (12)
#define HDMI_VPLLCR1_dpll_ldo_sel_shift                               (10)
#define HDMI_VPLLCR1_dpll_reserve_shift                               (9)
#define HDMI_VPLLCR1_dpll_bpspsw_shift                                (8)
#define HDMI_VPLLCR1_dpll_wdo_shift                                   (7)
#define HDMI_VPLLCR1_dpll_wdrst_shift                                 (6)
#define HDMI_VPLLCR1_dpll_wdset_shift                                 (5)
#define HDMI_VPLLCR1_dummy_4_shift                                    (4)
#define HDMI_VPLLCR1_dpll_stoppsw_shift                               (3)
#define HDMI_VPLLCR1_dpll_freeze_shift                                (2)
#define HDMI_VPLLCR1_dpll_vcorstb_shift                               (1)
#define HDMI_VPLLCR1_dpll_pow_shift                                   (0)
#define HDMI_VPLLCR1_dpll_cp_mask                                     (0x00600000)
#define HDMI_VPLLCR1_dpll_seltst_mask                                 (0x00180000)
#define HDMI_VPLLCR1_dpll_cs_mask                                     (0x00060000)
#define HDMI_VPLLCR1_dpll_ldo_pow_mask                                (0x00001000)
#define HDMI_VPLLCR1_dpll_ldo_sel_mask                                (0x00000C00)
#define HDMI_VPLLCR1_dpll_reserve_mask                                (0x00000200)
#define HDMI_VPLLCR1_dpll_bpspsw_mask                                 (0x00000100)
#define HDMI_VPLLCR1_dpll_wdo_mask                                    (0x00000080)
#define HDMI_VPLLCR1_dpll_wdrst_mask                                  (0x00000040)
#define HDMI_VPLLCR1_dpll_wdset_mask                                  (0x00000020)
#define HDMI_VPLLCR1_dummy_4_mask                                     (0x00000010)
#define HDMI_VPLLCR1_dpll_stoppsw_mask                                (0x00000008)
#define HDMI_VPLLCR1_dpll_freeze_mask                                 (0x00000004)
#define HDMI_VPLLCR1_dpll_vcorstb_mask                                (0x00000002)
#define HDMI_VPLLCR1_dpll_pow_mask                                    (0x00000001)
#define HDMI_VPLLCR1_dpll_cp(data)                                    (0x00600000&((data)<<21))
#define HDMI_VPLLCR1_dpll_seltst(data)                                (0x00180000&((data)<<19))
#define HDMI_VPLLCR1_dpll_cs(data)                                    (0x00060000&((data)<<17))
#define HDMI_VPLLCR1_dpll_ldo_pow(data)                               (0x00001000&((data)<<12))
#define HDMI_VPLLCR1_dpll_ldo_sel(data)                               (0x00000C00&((data)<<10))
#define HDMI_VPLLCR1_dpll_reserve(data)                               (0x00000200&((data)<<9))
#define HDMI_VPLLCR1_dpll_bpspsw(data)                                (0x00000100&((data)<<8))
#define HDMI_VPLLCR1_dpll_wdo(data)                                   (0x00000080&((data)<<7))
#define HDMI_VPLLCR1_dpll_wdrst(data)                                 (0x00000040&((data)<<6))
#define HDMI_VPLLCR1_dpll_wdset(data)                                 (0x00000020&((data)<<5))
#define HDMI_VPLLCR1_dummy_4(data)                                    (0x00000010&((data)<<4))
#define HDMI_VPLLCR1_dpll_stoppsw(data)                               (0x00000008&((data)<<3))
#define HDMI_VPLLCR1_dpll_freeze(data)                                (0x00000004&((data)<<2))
#define HDMI_VPLLCR1_dpll_vcorstb(data)                               (0x00000002&((data)<<1))
#define HDMI_VPLLCR1_dpll_pow(data)                                   (0x00000001&(data))
#define HDMI_VPLLCR1_get_dpll_cp(data)                                ((0x00600000&(data))>>21)
#define HDMI_VPLLCR1_get_dpll_seltst(data)                            ((0x00180000&(data))>>19)
#define HDMI_VPLLCR1_get_dpll_cs(data)                                ((0x00060000&(data))>>17)
#define HDMI_VPLLCR1_get_dpll_ldo_pow(data)                           ((0x00001000&(data))>>12)
#define HDMI_VPLLCR1_get_dpll_ldo_sel(data)                           ((0x00000C00&(data))>>10)
#define HDMI_VPLLCR1_get_dpll_reserve(data)                           ((0x00000200&(data))>>9)
#define HDMI_VPLLCR1_get_dpll_bpspsw(data)                            ((0x00000100&(data))>>8)
#define HDMI_VPLLCR1_get_dpll_wdo(data)                               ((0x00000080&(data))>>7)
#define HDMI_VPLLCR1_get_dpll_wdrst(data)                             ((0x00000040&(data))>>6)
#define HDMI_VPLLCR1_get_dpll_wdset(data)                             ((0x00000020&(data))>>5)
#define HDMI_VPLLCR1_get_dummy_4(data)                                ((0x00000010&(data))>>4)
#define HDMI_VPLLCR1_get_dpll_stoppsw(data)                           ((0x00000008&(data))>>3)
#define HDMI_VPLLCR1_get_dpll_freeze(data)                            ((0x00000004&(data))>>2)
#define HDMI_VPLLCR1_get_dpll_vcorstb(data)                           ((0x00000002&(data))>>1)
#define HDMI_VPLLCR1_get_dpll_pow(data)                               (0x00000001&(data))


#define HDMI_VPLLCR2                                                  0x408
#define HDMI_VPLLCR2_reg_addr                                         "0x98034408"
#define HDMI_VPLLCR2_reg                                              0x98034408
#define HDMI_VPLLCR2_inst_addr                                        "0x0102"
#define HDMI_VPLLCR2_inst                                             0x0102
#define set_HDMI_VPLLCR2_reg(data)                                    (*((volatile unsigned int*)HDMI_VPLLCR2_reg)=data)
#define get_HDMI_VPLLCR2_reg                                          (*((volatile unsigned int*)HDMI_VPLLCR2_reg))
#define HDMI_VPLLCR2_dpll_reloadm_shift                               (0)
#define HDMI_VPLLCR2_dpll_reloadm_mask                                (0x00000001)
#define HDMI_VPLLCR2_dpll_reloadm(data)                               (0x00000001&(data))
#define HDMI_VPLLCR2_get_dpll_reloadm(data)                           (0x00000001&(data))


#define MN_SCLKG_CTRL                                                 0x410
#define MN_SCLKG_CTRL_reg_addr                                        "0x98034410"
#define MN_SCLKG_CTRL_reg                                             0x98034410
#define MN_SCLKG_CTRL_inst_addr                                       "0x0104"
#define MN_SCLKG_CTRL_inst                                            0x0104
#define set_MN_SCLKG_CTRL_reg(data)                                   (*((volatile unsigned int*)MN_SCLKG_CTRL_reg)=data)
#define get_MN_SCLKG_CTRL_reg                                         (*((volatile unsigned int*)MN_SCLKG_CTRL_reg))
#define MN_SCLKG_CTRL_sclkg_pll_in_sel_shift                          (7)
#define MN_SCLKG_CTRL_sclkg_oclk_sel_shift                            (5)
#define MN_SCLKG_CTRL_sclkg_dbuf_shift                                (4)
#define MN_SCLKG_CTRL_dummy_3_0_shift                                 (0)
#define MN_SCLKG_CTRL_sclkg_pll_in_sel_mask                           (0x00000080)
#define MN_SCLKG_CTRL_sclkg_oclk_sel_mask                             (0x00000060)
#define MN_SCLKG_CTRL_sclkg_dbuf_mask                                 (0x00000010)
#define MN_SCLKG_CTRL_dummy_3_0_mask                                  (0x0000000F)
#define MN_SCLKG_CTRL_sclkg_pll_in_sel(data)                          (0x00000080&((data)<<7))
#define MN_SCLKG_CTRL_sclkg_oclk_sel(data)                            (0x00000060&((data)<<5))
#define MN_SCLKG_CTRL_sclkg_dbuf(data)                                (0x00000010&((data)<<4))
#define MN_SCLKG_CTRL_dummy_3_0(data)                                 (0x0000000F&(data))
#define MN_SCLKG_CTRL_get_sclkg_pll_in_sel(data)                      ((0x00000080&(data))>>7)
#define MN_SCLKG_CTRL_get_sclkg_oclk_sel(data)                        ((0x00000060&(data))>>5)
#define MN_SCLKG_CTRL_get_sclkg_dbuf(data)                            ((0x00000010&(data))>>4)
#define MN_SCLKG_CTRL_get_dummy_3_0(data)                             (0x0000000F&(data))


#define MN_SCLKG_DIVS                                                 0x414
#define MN_SCLKG_DIVS_reg_addr                                        "0x98034414"
#define MN_SCLKG_DIVS_reg                                             0x98034414
#define MN_SCLKG_DIVS_inst_addr                                       "0x0105"
#define MN_SCLKG_DIVS_inst                                            0x0105
#define set_MN_SCLKG_DIVS_reg(data)                                   (*((volatile unsigned int*)MN_SCLKG_DIVS_reg)=data)
#define get_MN_SCLKG_DIVS_reg                                         (*((volatile unsigned int*)MN_SCLKG_DIVS_reg))
#define MN_SCLKG_DIVS_sclkg_pll_div2_en_shift                         (7)
#define MN_SCLKG_DIVS_sclkg_pll_divs_shift                            (0)
#define MN_SCLKG_DIVS_sclkg_pll_div2_en_mask                          (0x00000080)
#define MN_SCLKG_DIVS_sclkg_pll_divs_mask                             (0x0000007F)
#define MN_SCLKG_DIVS_sclkg_pll_div2_en(data)                         (0x00000080&((data)<<7))
#define MN_SCLKG_DIVS_sclkg_pll_divs(data)                            (0x0000007F&(data))
#define MN_SCLKG_DIVS_get_sclkg_pll_div2_en(data)                     ((0x00000080&(data))>>7)
#define MN_SCLKG_DIVS_get_sclkg_pll_divs(data)                        (0x0000007F&(data))


#define MDD_CR                                                        0x500
#define MDD_CR_reg_addr                                               "0x98034500"
#define MDD_CR_reg                                                    0x98034500
#define MDD_CR_inst_addr                                              "0x0140"
#define MDD_CR_inst                                                   0x0140
#define set_MDD_CR_reg(data)                                          (*((volatile unsigned int*)MDD_CR_reg)=data)
#define get_MDD_CR_reg                                                (*((volatile unsigned int*)MDD_CR_reg))
#define MDD_CR_dummy_16_8_shift                                       (8)
#define MDD_CR_dummy_7_5_shift                                        (5)
#define MDD_CR_det_con_shift                                          (4)
#define MDD_CR_irq_det_chg_en_shift                                   (3)
#define MDD_CR_dummy_2_1_shift                                        (1)
#define MDD_CR_en_shift                                               (0)
#define MDD_CR_dummy_16_8_mask                                        (0x0001FF00)
#define MDD_CR_dummy_7_5_mask                                         (0x000000E0)
#define MDD_CR_det_con_mask                                           (0x00000010)
#define MDD_CR_irq_det_chg_en_mask                                    (0x00000008)
#define MDD_CR_dummy_2_1_mask                                         (0x00000006)
#define MDD_CR_en_mask                                                (0x00000001)
#define MDD_CR_dummy_16_8(data)                                       (0x0001FF00&((data)<<8))
#define MDD_CR_dummy_7_5(data)                                        (0x000000E0&((data)<<5))
#define MDD_CR_det_con(data)                                          (0x00000010&((data)<<4))
#define MDD_CR_irq_det_chg_en(data)                                   (0x00000008&((data)<<3))
#define MDD_CR_dummy_2_1(data)                                        (0x00000006&((data)<<1))
#define MDD_CR_en(data)                                               (0x00000001&(data))
#define MDD_CR_get_dummy_16_8(data)                                   ((0x0001FF00&(data))>>8)
#define MDD_CR_get_dummy_7_5(data)                                    ((0x000000E0&(data))>>5)
#define MDD_CR_get_det_con(data)                                      ((0x00000010&(data))>>4)
#define MDD_CR_get_irq_det_chg_en(data)                               ((0x00000008&(data))>>3)
#define MDD_CR_get_dummy_2_1(data)                                    ((0x00000006&(data))>>1)
#define MDD_CR_get_en(data)                                           (0x00000001&(data))


#define MDD_SR                                                        0x504
#define MDD_SR_reg_addr                                               "0x98034504"
#define MDD_SR_reg                                                    0x98034504
#define MDD_SR_inst_addr                                              "0x0141"
#define MDD_SR_inst                                                   0x0141
#define set_MDD_SR_reg(data)                                          (*((volatile unsigned int*)MDD_SR_reg)=data)
#define get_MDD_SR_reg                                                (*((volatile unsigned int*)MDD_SR_reg))
#define MDD_SR_det_result_chg_shift                                   (1)
#define MDD_SR_det_result_shift                                       (0)
#define MDD_SR_det_result_chg_mask                                    (0x00000002)
#define MDD_SR_det_result_mask                                        (0x00000001)
#define MDD_SR_det_result_chg(data)                                   (0x00000002&((data)<<1))
#define MDD_SR_det_result(data)                                       (0x00000001&(data))
#define MDD_SR_get_det_result_chg(data)                               ((0x00000002&(data))>>1)
#define MDD_SR_get_det_result(data)                                   (0x00000001&(data))
#endif
