/*===========*@date:2015/3/6===========*/

#ifndef _DFE_REG_H_INCLUDED_
#define _DFE_REG_H_INCLUDED_


#define REG_DFE_EN_L0                                                 0xf00
#define REG_DFE_EN_L0_reg_addr                                        "0x98034f00"
#define REG_DFE_EN_L0_reg                                             0x98034f00
#define REG_DFE_EN_L0_inst_addr                                       "0x03C0"
#define REG_DFE_EN_L0_inst                                            0x03C0
#define set_REG_DFE_EN_L0_reg(data)                                   (*((volatile unsigned int*)REG_DFE_EN_L0_reg)=data)
#define get_REG_DFE_EN_L0_reg                                         (*((volatile unsigned int*)REG_DFE_EN_L0_reg))
#define REG_DFE_EN_L0_clk_inv_lane0_shift                             (31)
#define REG_DFE_EN_L0_timer_ctrl_en_lane0_shift                       (30)
#define REG_DFE_EN_L0_reduce_adapt_gain_lane0_shift                   (28)
#define REG_DFE_EN_L0_rl_det_en_lane0_shift                           (27)
#define REG_DFE_EN_L0_rl_det_mode_lane0_shift                         (26)
#define REG_DFE_EN_L0_rl_threshold_lane0_shift                        (24)
#define REG_DFE_EN_L0_dfe_adapt_en_lane0_shift                        (16)
#define REG_DFE_EN_L0_le_min_lane0_shift                              (11)
#define REG_DFE_EN_L0_le_init_lane0_shift                             (6)
#define REG_DFE_EN_L0_tap4_init_lane0_shift                           (0)
#define REG_DFE_EN_L0_clk_inv_lane0_mask                              (0x80000000)
#define REG_DFE_EN_L0_timer_ctrl_en_lane0_mask                        (0x40000000)
#define REG_DFE_EN_L0_reduce_adapt_gain_lane0_mask                    (0x30000000)
#define REG_DFE_EN_L0_rl_det_en_lane0_mask                            (0x08000000)
#define REG_DFE_EN_L0_rl_det_mode_lane0_mask                          (0x04000000)
#define REG_DFE_EN_L0_rl_threshold_lane0_mask                         (0x03000000)
#define REG_DFE_EN_L0_dfe_adapt_en_lane0_mask                         (0x00FF0000)
#define REG_DFE_EN_L0_le_min_lane0_mask                               (0x0000F800)
#define REG_DFE_EN_L0_le_init_lane0_mask                              (0x000007C0)
#define REG_DFE_EN_L0_tap4_init_lane0_mask                            (0x0000003F)
#define REG_DFE_EN_L0_clk_inv_lane0(data)                             (0x80000000&((data)<<31))
#define REG_DFE_EN_L0_timer_ctrl_en_lane0(data)                       (0x40000000&((data)<<30))
#define REG_DFE_EN_L0_reduce_adapt_gain_lane0(data)                   (0x30000000&((data)<<28))
#define REG_DFE_EN_L0_rl_det_en_lane0(data)                           (0x08000000&((data)<<27))
#define REG_DFE_EN_L0_rl_det_mode_lane0(data)                         (0x04000000&((data)<<26))
#define REG_DFE_EN_L0_rl_threshold_lane0(data)                        (0x03000000&((data)<<24))
#define REG_DFE_EN_L0_dfe_adapt_en_lane0(data)                        (0x00FF0000&((data)<<16))
#define REG_DFE_EN_L0_le_min_lane0(data)                              (0x0000F800&((data)<<11))
#define REG_DFE_EN_L0_le_init_lane0(data)                             (0x000007C0&((data)<<6))
#define REG_DFE_EN_L0_tap4_init_lane0(data)                           (0x0000003F&(data))
#define REG_DFE_EN_L0_get_clk_inv_lane0(data)                         ((0x80000000&(data))>>31)
#define REG_DFE_EN_L0_get_timer_ctrl_en_lane0(data)                   ((0x40000000&(data))>>30)
#define REG_DFE_EN_L0_get_reduce_adapt_gain_lane0(data)               ((0x30000000&(data))>>28)
#define REG_DFE_EN_L0_get_rl_det_en_lane0(data)                       ((0x08000000&(data))>>27)
#define REG_DFE_EN_L0_get_rl_det_mode_lane0(data)                     ((0x04000000&(data))>>26)
#define REG_DFE_EN_L0_get_rl_threshold_lane0(data)                    ((0x03000000&(data))>>24)
#define REG_DFE_EN_L0_get_dfe_adapt_en_lane0(data)                    ((0x00FF0000&(data))>>16)
#define REG_DFE_EN_L0_get_le_min_lane0(data)                          ((0x0000F800&(data))>>11)
#define REG_DFE_EN_L0_get_le_init_lane0(data)                         ((0x000007C0&(data))>>6)
#define REG_DFE_EN_L0_get_tap4_init_lane0(data)                       (0x0000003F&(data))
#define REG_dfe_adapt_en_lane0_TAP0									_BIT16
#define REG_dfe_adapt_en_lane0_TAP1 								_BIT17
#define REG_dfe_adapt_en_lane0_TAP2 								_BIT18
#define REG_dfe_adapt_en_lane0_TAP3 								_BIT19
#define REG_dfe_adapt_en_lane0_TAP4 								_BIT20
#define REG_dfe_adapt_en_lane0_SERVO								_BIT21
#define REG_dfe_adapt_en_lane0_Vth									_BIT22
#define REG_dfe_adapt_en_lane0_LE									_BIT23


#define REG_DFE_INIT0_L0                                              0xf04
#define REG_DFE_INIT0_L0_reg_addr                                     "0x98034f04"
#define REG_DFE_INIT0_L0_reg                                          0x98034f04
#define REG_DFE_INIT0_L0_inst_addr                                    "0x03C1"
#define REG_DFE_INIT0_L0_inst                                         0x03C1
#define set_REG_DFE_INIT0_L0_reg(data)                                (*((volatile unsigned int*)REG_DFE_INIT0_L0_reg)=data)
#define get_REG_DFE_INIT0_L0_reg                                      (*((volatile unsigned int*)REG_DFE_INIT0_L0_reg))
#define REG_DFE_INIT0_L0_tap3_init_lane0_shift                        (26)
#define REG_DFE_INIT0_L0_tap2_init_lane0_shift                        (20)
#define REG_DFE_INIT0_L0_tap1_init_lane0_shift                        (14)
#define REG_DFE_INIT0_L0_tap0_init_lane0_shift                        (9)
#define REG_DFE_INIT0_L0_servo_init_lane0_shift                       (4)
#define REG_DFE_INIT0_L0_vth_init_lane0_shift                         (0)
#define REG_DFE_INIT0_L0_tap3_init_lane0_mask                         (0xFC000000)
#define REG_DFE_INIT0_L0_tap2_init_lane0_mask                         (0x03F00000)
#define REG_DFE_INIT0_L0_tap1_init_lane0_mask                         (0x000FC000)
#define REG_DFE_INIT0_L0_tap0_init_lane0_mask                         (0x00003E00)
#define REG_DFE_INIT0_L0_servo_init_lane0_mask                        (0x000001F0)
#define REG_DFE_INIT0_L0_vth_init_lane0_mask                          (0x0000000F)
#define REG_DFE_INIT0_L0_tap3_init_lane0(data)                        (0xFC000000&((data)<<26))
#define REG_DFE_INIT0_L0_tap2_init_lane0(data)                        (0x03F00000&((data)<<20))
#define REG_DFE_INIT0_L0_tap1_init_lane0(data)                        (0x000FC000&((data)<<14))
#define REG_DFE_INIT0_L0_tap0_init_lane0(data)                        (0x00003E00&((data)<<9))
#define REG_DFE_INIT0_L0_servo_init_lane0(data)                       (0x000001F0&((data)<<4))
#define REG_DFE_INIT0_L0_vth_init_lane0(data)                         (0x0000000F&(data))
#define REG_DFE_INIT0_L0_get_tap3_init_lane0(data)                    ((0xFC000000&(data))>>26)
#define REG_DFE_INIT0_L0_get_tap2_init_lane0(data)                    ((0x03F00000&(data))>>20)
#define REG_DFE_INIT0_L0_get_tap1_init_lane0(data)                    ((0x000FC000&(data))>>14)
#define REG_DFE_INIT0_L0_get_tap0_init_lane0(data)                    ((0x00003E00&(data))>>9)
#define REG_DFE_INIT0_L0_get_servo_init_lane0(data)                   ((0x000001F0&(data))>>4)
#define REG_DFE_INIT0_L0_get_vth_init_lane0(data)                     (0x0000000F&(data))


#define REG_DFE_INIT1_L0                                              0xf08
#define REG_DFE_INIT1_L0_reg_addr                                     "0x98034f08"
#define REG_DFE_INIT1_L0_reg                                          0x98034f08
#define REG_DFE_INIT1_L0_inst_addr                                    "0x03C2"
#define REG_DFE_INIT1_L0_inst                                         0x03C2
#define set_REG_DFE_INIT1_L0_reg(data)                                (*((volatile unsigned int*)REG_DFE_INIT1_L0_reg)=data)
#define get_REG_DFE_INIT1_L0_reg                                      (*((volatile unsigned int*)REG_DFE_INIT1_L0_reg))
#define REG_DFE_INIT1_L0_load_in_init_lane0_shift                     (24)
#define REG_DFE_INIT1_L0_init1_rev1_lane0_shift                       (18)
#define REG_DFE_INIT1_L0_de_video_inv_lane0_shift                     (17)
#define REG_DFE_INIT1_L0_de_packet_inv_lane0_shift                    (16)
#define REG_DFE_INIT1_L0_de_video_en_lane0_shift                      (15)
#define REG_DFE_INIT1_L0_de_packet_en_lane0_shift                     (14)
#define REG_DFE_INIT1_L0_init1_rev0_lane0_shift                       (0)
#define REG_DFE_INIT1_L0_load_in_init_lane0_mask                      (0xFF000000)
#define REG_DFE_INIT1_L0_init1_rev1_lane0_mask                        (0x00FC0000)
#define REG_DFE_INIT1_L0_de_video_inv_lane0_mask                      (0x00020000)
#define REG_DFE_INIT1_L0_de_packet_inv_lane0_mask                     (0x00010000)
#define REG_DFE_INIT1_L0_de_video_en_lane0_mask                       (0x00008000)
#define REG_DFE_INIT1_L0_de_packet_en_lane0_mask                      (0x00004000)
#define REG_DFE_INIT1_L0_init1_rev0_lane0_mask                        (0x00003FFF)
#define REG_DFE_INIT1_L0_load_in_init_lane0(data)                     (0xFF000000&((data)<<24))
#define REG_DFE_INIT1_L0_init1_rev1_lane0(data)                       (0x00FC0000&((data)<<18))
#define REG_DFE_INIT1_L0_de_video_inv_lane0(data)                     (0x00020000&((data)<<17))
#define REG_DFE_INIT1_L0_de_packet_inv_lane0(data)                    (0x00010000&((data)<<16))
#define REG_DFE_INIT1_L0_de_video_en_lane0(data)                      (0x00008000&((data)<<15))
#define REG_DFE_INIT1_L0_de_packet_en_lane0(data)                     (0x00004000&((data)<<14))
#define REG_DFE_INIT1_L0_init1_rev0_lane0(data)                       (0x00003FFF&(data))
#define REG_DFE_INIT1_L0_get_load_in_init_lane0(data)                 ((0xFF000000&(data))>>24)
#define REG_DFE_INIT1_L0_get_init1_rev1_lane0(data)                   ((0x00FC0000&(data))>>18)
#define REG_DFE_INIT1_L0_get_de_video_inv_lane0(data)                 ((0x00020000&(data))>>17)
#define REG_DFE_INIT1_L0_get_de_packet_inv_lane0(data)                ((0x00010000&(data))>>16)
#define REG_DFE_INIT1_L0_get_de_video_en_lane0(data)                  ((0x00008000&(data))>>15)
#define REG_DFE_INIT1_L0_get_de_packet_en_lane0(data)                 ((0x00004000&(data))>>14)
#define REG_DFE_INIT1_L0_get_init1_rev0_lane0(data)                   (0x00003FFF&(data))
#define load_in_init_lane0_LE										(_BIT31)
#define load_in_init_lane0_vth										(_BIT30)
#define load_in_init_lane0_tap1										(_BIT25)
#define load_in_init_lane0_tap0										(_BIT24)


#define REG_DFE_EN_L1                                                 0xf10
#define REG_DFE_EN_L1_reg_addr                                        "0x98034f10"
#define REG_DFE_EN_L1_reg                                             0x98034f10
#define REG_DFE_EN_L1_inst_addr                                       "0x03C4"
#define REG_DFE_EN_L1_inst                                            0x03C4
#define set_REG_DFE_EN_L1_reg(data)                                   (*((volatile unsigned int*)REG_DFE_EN_L1_reg)=data)
#define get_REG_DFE_EN_L1_reg                                         (*((volatile unsigned int*)REG_DFE_EN_L1_reg))
#define REG_DFE_EN_L1_clk_inv_lane1_shift                             (31)
#define REG_DFE_EN_L1_timer_ctrl_en_lane1_shift                       (30)
#define REG_DFE_EN_L1_reduce_adapt_gain_lane1_shift                   (28)
#define REG_DFE_EN_L1_rl_det_en_lane1_shift                           (27)
#define REG_DFE_EN_L1_rl_det_mode_lane1_shift                         (26)
#define REG_DFE_EN_L1_rl_threshold_lane1_shift                        (24)
#define REG_DFE_EN_L1_dfe_adapt_en_lane1_shift                        (16)
#define REG_DFE_EN_L1_le_min_lane1_shift                              (11)
#define REG_DFE_EN_L1_le_init_lane1_shift                             (6)
#define REG_DFE_EN_L1_tap4_init_lane1_shift                           (0)
#define REG_DFE_EN_L1_clk_inv_lane1_mask                              (0x80000000)
#define REG_DFE_EN_L1_timer_ctrl_en_lane1_mask                        (0x40000000)
#define REG_DFE_EN_L1_reduce_adapt_gain_lane1_mask                    (0x30000000)
#define REG_DFE_EN_L1_rl_det_en_lane1_mask                            (0x08000000)
#define REG_DFE_EN_L1_rl_det_mode_lane1_mask                          (0x04000000)
#define REG_DFE_EN_L1_rl_threshold_lane1_mask                         (0x03000000)
#define REG_DFE_EN_L1_dfe_adapt_en_lane1_mask                         (0x00FF0000)
#define REG_DFE_EN_L1_le_min_lane1_mask                               (0x0000F800)
#define REG_DFE_EN_L1_le_init_lane1_mask                              (0x000007C0)
#define REG_DFE_EN_L1_tap4_init_lane1_mask                            (0x0000003F)
#define REG_DFE_EN_L1_clk_inv_lane1(data)                             (0x80000000&((data)<<31))
#define REG_DFE_EN_L1_timer_ctrl_en_lane1(data)                       (0x40000000&((data)<<30))
#define REG_DFE_EN_L1_reduce_adapt_gain_lane1(data)                   (0x30000000&((data)<<28))
#define REG_DFE_EN_L1_rl_det_en_lane1(data)                           (0x08000000&((data)<<27))
#define REG_DFE_EN_L1_rl_det_mode_lane1(data)                         (0x04000000&((data)<<26))
#define REG_DFE_EN_L1_rl_threshold_lane1(data)                        (0x03000000&((data)<<24))
#define REG_DFE_EN_L1_dfe_adapt_en_lane1(data)                        (0x00FF0000&((data)<<16))
#define REG_DFE_EN_L1_le_min_lane1(data)                              (0x0000F800&((data)<<11))
#define REG_DFE_EN_L1_le_init_lane1(data)                             (0x000007C0&((data)<<6))
#define REG_DFE_EN_L1_tap4_init_lane1(data)                           (0x0000003F&(data))
#define REG_DFE_EN_L1_get_clk_inv_lane1(data)                         ((0x80000000&(data))>>31)
#define REG_DFE_EN_L1_get_timer_ctrl_en_lane1(data)                   ((0x40000000&(data))>>30)
#define REG_DFE_EN_L1_get_reduce_adapt_gain_lane1(data)               ((0x30000000&(data))>>28)
#define REG_DFE_EN_L1_get_rl_det_en_lane1(data)                       ((0x08000000&(data))>>27)
#define REG_DFE_EN_L1_get_rl_det_mode_lane1(data)                     ((0x04000000&(data))>>26)
#define REG_DFE_EN_L1_get_rl_threshold_lane1(data)                    ((0x03000000&(data))>>24)
#define REG_DFE_EN_L1_get_dfe_adapt_en_lane1(data)                    ((0x00FF0000&(data))>>16)
#define REG_DFE_EN_L1_get_le_min_lane1(data)                          ((0x0000F800&(data))>>11)
#define REG_DFE_EN_L1_get_le_init_lane1(data)                         ((0x000007C0&(data))>>6)
#define REG_DFE_EN_L1_get_tap4_init_lane1(data)                       (0x0000003F&(data))
#define REG_dfe_adapt_en_lane1_TAP0									_BIT16
#define REG_dfe_adapt_en_lane1_TAP1 								_BIT17
#define REG_dfe_adapt_en_lane1_TAP2 								_BIT18
#define REG_dfe_adapt_en_lane1_TAP3 								_BIT19
#define REG_dfe_adapt_en_lane1_TAP4 								_BIT20
#define REG_dfe_adapt_en_lane1_SERVO								_BIT21
#define REG_dfe_adapt_en_lane1_Vth									_BIT22
#define REG_dfe_adapt_en_lane1_LE									_BIT23


#define REG_DFE_INIT0_L1                                              0xf14
#define REG_DFE_INIT0_L1_reg_addr                                     "0x98034f14"
#define REG_DFE_INIT0_L1_reg                                          0x98034f14
#define REG_DFE_INIT0_L1_inst_addr                                    "0x03C5"
#define REG_DFE_INIT0_L1_inst                                         0x03C5
#define set_REG_DFE_INIT0_L1_reg(data)                                (*((volatile unsigned int*)REG_DFE_INIT0_L1_reg)=data)
#define get_REG_DFE_INIT0_L1_reg                                      (*((volatile unsigned int*)REG_DFE_INIT0_L1_reg))
#define REG_DFE_INIT0_L1_tap3_init_lane1_shift                        (26)
#define REG_DFE_INIT0_L1_tap2_init_lane1_shift                        (20)
#define REG_DFE_INIT0_L1_tap1_init_lane1_shift                        (14)
#define REG_DFE_INIT0_L1_tap0_init_lane1_shift                        (9)
#define REG_DFE_INIT0_L1_servo_init_lane1_shift                       (4)
#define REG_DFE_INIT0_L1_vth_init_lane1_shift                         (0)
#define REG_DFE_INIT0_L1_tap3_init_lane1_mask                         (0xFC000000)
#define REG_DFE_INIT0_L1_tap2_init_lane1_mask                         (0x03F00000)
#define REG_DFE_INIT0_L1_tap1_init_lane1_mask                         (0x000FC000)
#define REG_DFE_INIT0_L1_tap0_init_lane1_mask                         (0x00003E00)
#define REG_DFE_INIT0_L1_servo_init_lane1_mask                        (0x000001F0)
#define REG_DFE_INIT0_L1_vth_init_lane1_mask                          (0x0000000F)
#define REG_DFE_INIT0_L1_tap3_init_lane1(data)                        (0xFC000000&((data)<<26))
#define REG_DFE_INIT0_L1_tap2_init_lane1(data)                        (0x03F00000&((data)<<20))
#define REG_DFE_INIT0_L1_tap1_init_lane1(data)                        (0x000FC000&((data)<<14))
#define REG_DFE_INIT0_L1_tap0_init_lane1(data)                        (0x00003E00&((data)<<9))
#define REG_DFE_INIT0_L1_servo_init_lane1(data)                       (0x000001F0&((data)<<4))
#define REG_DFE_INIT0_L1_vth_init_lane1(data)                         (0x0000000F&(data))
#define REG_DFE_INIT0_L1_get_tap3_init_lane1(data)                    ((0xFC000000&(data))>>26)
#define REG_DFE_INIT0_L1_get_tap2_init_lane1(data)                    ((0x03F00000&(data))>>20)
#define REG_DFE_INIT0_L1_get_tap1_init_lane1(data)                    ((0x000FC000&(data))>>14)
#define REG_DFE_INIT0_L1_get_tap0_init_lane1(data)                    ((0x00003E00&(data))>>9)
#define REG_DFE_INIT0_L1_get_servo_init_lane1(data)                   ((0x000001F0&(data))>>4)
#define REG_DFE_INIT0_L1_get_vth_init_lane1(data)                     (0x0000000F&(data))


#define REG_DFE_INIT1_L1                                              0xf18
#define REG_DFE_INIT1_L1_reg_addr                                     "0x98034f18"
#define REG_DFE_INIT1_L1_reg                                          0x98034f18
#define REG_DFE_INIT1_L1_inst_addr                                    "0x03C6"
#define REG_DFE_INIT1_L1_inst                                         0x03C6
#define set_REG_DFE_INIT1_L1_reg(data)                                (*((volatile unsigned int*)REG_DFE_INIT1_L1_reg)=data)
#define get_REG_DFE_INIT1_L1_reg                                      (*((volatile unsigned int*)REG_DFE_INIT1_L1_reg))
#define REG_DFE_INIT1_L1_load_in_init_lane1_shift                     (24)
#define REG_DFE_INIT1_L1_init1_rev1_lane1_shift                       (18)
#define REG_DFE_INIT1_L1_de_video_inv_lane1_shift                     (17)
#define REG_DFE_INIT1_L1_de_packet_inv_lane1_shift                    (16)
#define REG_DFE_INIT1_L1_de_video_en_lane1_shift                      (15)
#define REG_DFE_INIT1_L1_de_packet_en_lane1_shift                     (14)
#define REG_DFE_INIT1_L1_init1_rev0_lane1_shift                       (0)
#define REG_DFE_INIT1_L1_load_in_init_lane1_mask                      (0xFF000000)
#define REG_DFE_INIT1_L1_init1_rev1_lane1_mask                        (0x00FC0000)
#define REG_DFE_INIT1_L1_de_video_inv_lane1_mask                      (0x00020000)
#define REG_DFE_INIT1_L1_de_packet_inv_lane1_mask                     (0x00010000)
#define REG_DFE_INIT1_L1_de_video_en_lane1_mask                       (0x00008000)
#define REG_DFE_INIT1_L1_de_packet_en_lane1_mask                      (0x00004000)
#define REG_DFE_INIT1_L1_init1_rev0_lane1_mask                        (0x00003FFF)
#define REG_DFE_INIT1_L1_load_in_init_lane1(data)                     (0xFF000000&((data)<<24))
#define REG_DFE_INIT1_L1_init1_rev1_lane1(data)                       (0x00FC0000&((data)<<18))
#define REG_DFE_INIT1_L1_de_video_inv_lane1(data)                     (0x00020000&((data)<<17))
#define REG_DFE_INIT1_L1_de_packet_inv_lane1(data)                    (0x00010000&((data)<<16))
#define REG_DFE_INIT1_L1_de_video_en_lane1(data)                      (0x00008000&((data)<<15))
#define REG_DFE_INIT1_L1_de_packet_en_lane1(data)                     (0x00004000&((data)<<14))
#define REG_DFE_INIT1_L1_init1_rev0_lane1(data)                       (0x00003FFF&(data))
#define REG_DFE_INIT1_L1_get_load_in_init_lane1(data)                 ((0xFF000000&(data))>>24)
#define REG_DFE_INIT1_L1_get_init1_rev1_lane1(data)                   ((0x00FC0000&(data))>>18)
#define REG_DFE_INIT1_L1_get_de_video_inv_lane1(data)                 ((0x00020000&(data))>>17)
#define REG_DFE_INIT1_L1_get_de_packet_inv_lane1(data)                ((0x00010000&(data))>>16)
#define REG_DFE_INIT1_L1_get_de_video_en_lane1(data)                  ((0x00008000&(data))>>15)
#define REG_DFE_INIT1_L1_get_de_packet_en_lane1(data)                 ((0x00004000&(data))>>14)
#define REG_DFE_INIT1_L1_get_init1_rev0_lane1(data)                   (0x00003FFF&(data))


#define REG_DFE_EN_L2                                                 0xf20
#define REG_DFE_EN_L2_reg_addr                                        "0x98034f20"
#define REG_DFE_EN_L2_reg                                             0x98034f20
#define REG_DFE_EN_L2_inst_addr                                       "0x03C8"
#define REG_DFE_EN_L2_inst                                            0x03C8
#define set_REG_DFE_EN_L2_reg(data)                                   (*((volatile unsigned int*)REG_DFE_EN_L2_reg)=data)
#define get_REG_DFE_EN_L2_reg                                         (*((volatile unsigned int*)REG_DFE_EN_L2_reg))
#define REG_DFE_EN_L2_clk_inv_lane2_shift                             (31)
#define REG_DFE_EN_L2_timer_ctrl_en_lane2_shift                       (30)
#define REG_DFE_EN_L2_reduce_adapt_gain_lane2_shift                   (28)
#define REG_DFE_EN_L2_rl_det_en_lane2_shift                           (27)
#define REG_DFE_EN_L2_rl_det_mode_lane2_shift                         (26)
#define REG_DFE_EN_L2_rl_threshold_lane2_shift                        (24)
#define REG_DFE_EN_L2_dfe_adapt_en_lane2_shift                        (16)
#define REG_DFE_EN_L2_le_min_lane2_shift                              (11)
#define REG_DFE_EN_L2_le_init_lane2_shift                             (6)
#define REG_DFE_EN_L2_tap4_init_lane2_shift                           (0)
#define REG_DFE_EN_L2_clk_inv_lane2_mask                              (0x80000000)
#define REG_DFE_EN_L2_timer_ctrl_en_lane2_mask                        (0x40000000)
#define REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask                    (0x30000000)
#define REG_DFE_EN_L2_rl_det_en_lane2_mask                            (0x08000000)
#define REG_DFE_EN_L2_rl_det_mode_lane2_mask                          (0x04000000)
#define REG_DFE_EN_L2_rl_threshold_lane2_mask                         (0x03000000)
#define REG_DFE_EN_L2_dfe_adapt_en_lane2_mask                         (0x00FF0000)
#define REG_DFE_EN_L2_le_min_lane2_mask                               (0x0000F800)
#define REG_DFE_EN_L2_le_init_lane2_mask                              (0x000007C0)
#define REG_DFE_EN_L2_tap4_init_lane2_mask                            (0x0000003F)
#define REG_DFE_EN_L2_clk_inv_lane2(data)                             (0x80000000&((data)<<31))
#define REG_DFE_EN_L2_timer_ctrl_en_lane2(data)                       (0x40000000&((data)<<30))
#define REG_DFE_EN_L2_reduce_adapt_gain_lane2(data)                   (0x30000000&((data)<<28))
#define REG_DFE_EN_L2_rl_det_en_lane2(data)                           (0x08000000&((data)<<27))
#define REG_DFE_EN_L2_rl_det_mode_lane2(data)                         (0x04000000&((data)<<26))
#define REG_DFE_EN_L2_rl_threshold_lane2(data)                        (0x03000000&((data)<<24))
#define REG_DFE_EN_L2_dfe_adapt_en_lane2(data)                        (0x00FF0000&((data)<<16))
#define REG_DFE_EN_L2_le_min_lane2(data)                              (0x0000F800&((data)<<11))
#define REG_DFE_EN_L2_le_init_lane2(data)                             (0x000007C0&((data)<<6))
#define REG_DFE_EN_L2_tap4_init_lane2(data)                           (0x0000003F&(data))
#define REG_DFE_EN_L2_get_clk_inv_lane2(data)                         ((0x80000000&(data))>>31)
#define REG_DFE_EN_L2_get_timer_ctrl_en_lane2(data)                   ((0x40000000&(data))>>30)
#define REG_DFE_EN_L2_get_reduce_adapt_gain_lane2(data)               ((0x30000000&(data))>>28)
#define REG_DFE_EN_L2_get_rl_det_en_lane2(data)                       ((0x08000000&(data))>>27)
#define REG_DFE_EN_L2_get_rl_det_mode_lane2(data)                     ((0x04000000&(data))>>26)
#define REG_DFE_EN_L2_get_rl_threshold_lane2(data)                    ((0x03000000&(data))>>24)
#define REG_DFE_EN_L2_get_dfe_adapt_en_lane2(data)                    ((0x00FF0000&(data))>>16)
#define REG_DFE_EN_L2_get_le_min_lane2(data)                          ((0x0000F800&(data))>>11)
#define REG_DFE_EN_L2_get_le_init_lane2(data)                         ((0x000007C0&(data))>>6)
#define REG_DFE_EN_L2_get_tap4_init_lane2(data)                       (0x0000003F&(data))
#define REG_dfe_adapt_en_lane2_TAP0 								_BIT16
#define REG_dfe_adapt_en_lane2_TAP1 								_BIT17
#define REG_dfe_adapt_en_lane2_TAP2 								_BIT18
#define REG_dfe_adapt_en_lane2_TAP3 								_BIT19
#define REG_dfe_adapt_en_lane2_TAP4 								_BIT20
#define REG_dfe_adapt_en_lane2_SERVO								_BIT21
#define REG_dfe_adapt_en_lane2_Vth									_BIT22
#define REG_dfe_adapt_en_lane2_LE									_BIT23


#define REG_DFE_INIT0_L2                                              0xf24
#define REG_DFE_INIT0_L2_reg_addr                                     "0x98034f24"
#define REG_DFE_INIT0_L2_reg                                          0x98034f24
#define REG_DFE_INIT0_L2_inst_addr                                    "0x03C9"
#define REG_DFE_INIT0_L2_inst                                         0x03C9
#define set_REG_DFE_INIT0_L2_reg(data)                                (*((volatile unsigned int*)REG_DFE_INIT0_L2_reg)=data)
#define get_REG_DFE_INIT0_L2_reg                                      (*((volatile unsigned int*)REG_DFE_INIT0_L2_reg))
#define REG_DFE_INIT0_L2_tap3_init_lane2_shift                        (26)
#define REG_DFE_INIT0_L2_tap2_init_lane2_shift                        (20)
#define REG_DFE_INIT0_L2_tap1_init_lane2_shift                        (14)
#define REG_DFE_INIT0_L2_tap0_init_lane2_shift                        (9)
#define REG_DFE_INIT0_L2_servo_init_lane2_shift                       (4)
#define REG_DFE_INIT0_L2_vth_init_lane2_shift                         (0)
#define REG_DFE_INIT0_L2_tap3_init_lane2_mask                         (0xFC000000)
#define REG_DFE_INIT0_L2_tap2_init_lane2_mask                         (0x03F00000)
#define REG_DFE_INIT0_L2_tap1_init_lane2_mask                         (0x000FC000)
#define REG_DFE_INIT0_L2_tap0_init_lane2_mask                         (0x00003E00)
#define REG_DFE_INIT0_L2_servo_init_lane2_mask                        (0x000001F0)
#define REG_DFE_INIT0_L2_vth_init_lane2_mask                          (0x0000000F)
#define REG_DFE_INIT0_L2_tap3_init_lane2(data)                        (0xFC000000&((data)<<26))
#define REG_DFE_INIT0_L2_tap2_init_lane2(data)                        (0x03F00000&((data)<<20))
#define REG_DFE_INIT0_L2_tap1_init_lane2(data)                        (0x000FC000&((data)<<14))
#define REG_DFE_INIT0_L2_tap0_init_lane2(data)                        (0x00003E00&((data)<<9))
#define REG_DFE_INIT0_L2_servo_init_lane2(data)                       (0x000001F0&((data)<<4))
#define REG_DFE_INIT0_L2_vth_init_lane2(data)                         (0x0000000F&(data))
#define REG_DFE_INIT0_L2_get_tap3_init_lane2(data)                    ((0xFC000000&(data))>>26)
#define REG_DFE_INIT0_L2_get_tap2_init_lane2(data)                    ((0x03F00000&(data))>>20)
#define REG_DFE_INIT0_L2_get_tap1_init_lane2(data)                    ((0x000FC000&(data))>>14)
#define REG_DFE_INIT0_L2_get_tap0_init_lane2(data)                    ((0x00003E00&(data))>>9)
#define REG_DFE_INIT0_L2_get_servo_init_lane2(data)                   ((0x000001F0&(data))>>4)
#define REG_DFE_INIT0_L2_get_vth_init_lane2(data)                     (0x0000000F&(data))


#define REG_DFE_INIT1_L2                                              0xf28
#define REG_DFE_INIT1_L2_reg_addr                                     "0x98034f28"
#define REG_DFE_INIT1_L2_reg                                          0x98034f28
#define REG_DFE_INIT1_L2_inst_addr                                    "0x03CA"
#define REG_DFE_INIT1_L2_inst                                         0x03CA
#define set_REG_DFE_INIT1_L2_reg(data)                                (*((volatile unsigned int*)REG_DFE_INIT1_L2_reg)=data)
#define get_REG_DFE_INIT1_L2_reg                                      (*((volatile unsigned int*)REG_DFE_INIT1_L2_reg))
#define REG_DFE_INIT1_L2_load_in_init_lane2_shift                     (24)
#define REG_DFE_INIT1_L2_init1_rev1_lane2_shift                       (18)
#define REG_DFE_INIT1_L2_de_video_inv_lane2_shift                     (17)
#define REG_DFE_INIT1_L2_de_packet_inv_lane2_shift                    (16)
#define REG_DFE_INIT1_L2_de_video_en_lane2_shift                      (15)
#define REG_DFE_INIT1_L2_de_packet_en_lane2_shift                     (14)
#define REG_DFE_INIT1_L2_init1_rev0_lane2_shift                       (0)
#define REG_DFE_INIT1_L2_load_in_init_lane2_mask                      (0xFF000000)
#define REG_DFE_INIT1_L2_init1_rev1_lane2_mask                        (0x00FC0000)
#define REG_DFE_INIT1_L2_de_video_inv_lane2_mask                      (0x00020000)
#define REG_DFE_INIT1_L2_de_packet_inv_lane2_mask                     (0x00010000)
#define REG_DFE_INIT1_L2_de_video_en_lane2_mask                       (0x00008000)
#define REG_DFE_INIT1_L2_de_packet_en_lane2_mask                      (0x00004000)
#define REG_DFE_INIT1_L2_init1_rev0_lane2_mask                        (0x00003FFF)
#define REG_DFE_INIT1_L2_load_in_init_lane2(data)                     (0xFF000000&((data)<<24))
#define REG_DFE_INIT1_L2_init1_rev1_lane2(data)                       (0x00FC0000&((data)<<18))
#define REG_DFE_INIT1_L2_de_video_inv_lane2(data)                     (0x00020000&((data)<<17))
#define REG_DFE_INIT1_L2_de_packet_inv_lane2(data)                    (0x00010000&((data)<<16))
#define REG_DFE_INIT1_L2_de_video_en_lane2(data)                      (0x00008000&((data)<<15))
#define REG_DFE_INIT1_L2_de_packet_en_lane2(data)                     (0x00004000&((data)<<14))
#define REG_DFE_INIT1_L2_init1_rev0_lane2(data)                       (0x00003FFF&(data))
#define REG_DFE_INIT1_L2_get_load_in_init_lane2(data)                 ((0xFF000000&(data))>>24)
#define REG_DFE_INIT1_L2_get_init1_rev1_lane2(data)                   ((0x00FC0000&(data))>>18)
#define REG_DFE_INIT1_L2_get_de_video_inv_lane2(data)                 ((0x00020000&(data))>>17)
#define REG_DFE_INIT1_L2_get_de_packet_inv_lane2(data)                ((0x00010000&(data))>>16)
#define REG_DFE_INIT1_L2_get_de_video_en_lane2(data)                  ((0x00008000&(data))>>15)
#define REG_DFE_INIT1_L2_get_de_packet_en_lane2(data)                 ((0x00004000&(data))>>14)
#define REG_DFE_INIT1_L2_get_init1_rev0_lane2(data)                   (0x00003FFF&(data))


#define REG_DFE_MODE                                                  0xf30
#define REG_DFE_MODE_reg_addr                                         "0x98034f30"
#define REG_DFE_MODE_reg                                              0x98034f30
#define REG_DFE_MODE_inst_addr                                        "0x03CC"
#define REG_DFE_MODE_inst                                             0x03CC
#define set_REG_DFE_MODE_reg(data)                                    (*((volatile unsigned int*)REG_DFE_MODE_reg)=data)
#define get_REG_DFE_MODE_reg                                          (*((volatile unsigned int*)REG_DFE_MODE_reg))
#define REG_DFE_MODE_adapt_mode_shift                                 (30)
#define REG_DFE_MODE_edge_det_mode_shift                              (29)
#define REG_DFE_MODE_transition_only_shift                            (28)
#define REG_DFE_MODE_le_auto_reload_shift                             (27)
#define REG_DFE_MODE_tap1_delay_shift                                 (24)
#define REG_DFE_MODE_tap24_delay_shift                                (21)
#define REG_DFE_MODE_le_delay_shift                                   (18)
#define REG_DFE_MODE_servo_delay_shift                                (16)
#define REG_DFE_MODE_gray_en_shift                                    (8)
#define REG_DFE_MODE_dfe_adapt_rstb_shift                             (4)
#define REG_DFE_MODE_tap0_trans_shift                                 (3)
#define REG_DFE_MODE_tap0_notrans_shift                               (2)
#define REG_DFE_MODE_servo_notrans_shift                              (1)
#define REG_DFE_MODE_servo_trans_shift                                (0)
#define REG_DFE_MODE_adapt_mode_mask                                  (0xC0000000)
#define REG_DFE_MODE_edge_det_mode_mask                               (0x20000000)
#define REG_DFE_MODE_transition_only_mask                             (0x10000000)
#define REG_DFE_MODE_le_auto_reload_mask                              (0x08000000)
#define REG_DFE_MODE_tap1_delay_mask                                  (0x07000000)
#define REG_DFE_MODE_tap24_delay_mask                                 (0x00E00000)
#define REG_DFE_MODE_le_delay_mask                                    (0x001C0000)
#define REG_DFE_MODE_servo_delay_mask                                 (0x00030000)
#define REG_DFE_MODE_gray_en_mask                                     (0x0000FF00)
#define REG_DFE_MODE_dfe_adapt_rstb_mask                              (0x000000F0)
#define REG_DFE_MODE_tap0_trans_mask                                  (0x00000008)
#define REG_DFE_MODE_tap0_notrans_mask                                (0x00000004)
#define REG_DFE_MODE_servo_notrans_mask                               (0x00000002)
#define REG_DFE_MODE_servo_trans_mask                                 (0x00000001)
#define REG_DFE_MODE_adapt_mode(data)                                 (0xC0000000&((data)<<30))
#define REG_DFE_MODE_edge_det_mode(data)                              (0x20000000&((data)<<29))
#define REG_DFE_MODE_transition_only(data)                            (0x10000000&((data)<<28))
#define REG_DFE_MODE_le_auto_reload(data)                             (0x08000000&((data)<<27))
#define REG_DFE_MODE_tap1_delay(data)                                 (0x07000000&((data)<<24))
#define REG_DFE_MODE_tap24_delay(data)                                (0x00E00000&((data)<<21))
#define REG_DFE_MODE_le_delay(data)                                   (0x001C0000&((data)<<18))
#define REG_DFE_MODE_servo_delay(data)                                (0x00030000&((data)<<16))
#define REG_DFE_MODE_gray_en(data)                                    (0x0000FF00&((data)<<8))
#define REG_DFE_MODE_dfe_adapt_rstb(data)                             (0x000000F0&((data)<<4))
#define REG_DFE_MODE_tap0_trans(data)                                 (0x00000008&((data)<<3))
#define REG_DFE_MODE_tap0_notrans(data)                               (0x00000004&((data)<<2))
#define REG_DFE_MODE_servo_notrans(data)                              (0x00000002&((data)<<1))
#define REG_DFE_MODE_servo_trans(data)                                (0x00000001&(data))
#define REG_DFE_MODE_get_adapt_mode(data)                             ((0xC0000000&(data))>>30)
#define REG_DFE_MODE_get_edge_det_mode(data)                          ((0x20000000&(data))>>29)
#define REG_DFE_MODE_get_transition_only(data)                        ((0x10000000&(data))>>28)
#define REG_DFE_MODE_get_le_auto_reload(data)                         ((0x08000000&(data))>>27)
#define REG_DFE_MODE_get_tap1_delay(data)                             ((0x07000000&(data))>>24)
#define REG_DFE_MODE_get_tap24_delay(data)                            ((0x00E00000&(data))>>21)
#define REG_DFE_MODE_get_le_delay(data)                               ((0x001C0000&(data))>>18)
#define REG_DFE_MODE_get_servo_delay(data)                            ((0x00030000&(data))>>16)
#define REG_DFE_MODE_get_gray_en(data)                                ((0x0000FF00&(data))>>8)
#define REG_DFE_MODE_get_dfe_adapt_rstb(data)                         ((0x000000F0&(data))>>4)
#define REG_DFE_MODE_get_tap0_trans(data)                             ((0x00000008&(data))>>3)
#define REG_DFE_MODE_get_tap0_notrans(data)                           ((0x00000004&(data))>>2)
#define REG_DFE_MODE_get_servo_notrans(data)                          ((0x00000002&(data))>>1)
#define REG_DFE_MODE_get_servo_trans(data)                            (0x00000001&(data))


#define REG_DFE_GAIN                                                  0xf34
#define REG_DFE_GAIN_reg_addr                                         "0x98034f34"
#define REG_DFE_GAIN_reg                                              0x98034f34
#define REG_DFE_GAIN_inst_addr                                        "0x03CD"
#define REG_DFE_GAIN_inst                                             0x03CD
#define set_REG_DFE_GAIN_reg(data)                                    (*((volatile unsigned int*)REG_DFE_GAIN_reg)=data)
#define get_REG_DFE_GAIN_reg                                          (*((volatile unsigned int*)REG_DFE_GAIN_reg))
#define REG_DFE_GAIN_tap0_gain_shift                                  (29)
#define REG_DFE_GAIN_tap1_gain_shift                                  (26)
#define REG_DFE_GAIN_tap2_gain_shift                                  (23)
#define REG_DFE_GAIN_tap3_gain_shift                                  (20)
#define REG_DFE_GAIN_tap4_gain_shift                                  (17)
#define REG_DFE_GAIN_servo_gain_shift                                 (14)
#define REG_DFE_GAIN_le_gain1_shift                                   (11)
#define REG_DFE_GAIN_le_gain2_shift                                   (8)
#define REG_DFE_GAIN_le2_sign_shift                                   (7)
#define REG_DFE_GAIN_le_gain_prec_shift                               (4)
#define REG_DFE_GAIN_le_prec_sign_shift                               (3)
#define REG_DFE_GAIN_trans_rlength_shift                              (0)
#define REG_DFE_GAIN_tap0_gain_mask                                   (0xE0000000)
#define REG_DFE_GAIN_tap1_gain_mask                                   (0x1C000000)
#define REG_DFE_GAIN_tap2_gain_mask                                   (0x03800000)
#define REG_DFE_GAIN_tap3_gain_mask                                   (0x00700000)
#define REG_DFE_GAIN_tap4_gain_mask                                   (0x000E0000)
#define REG_DFE_GAIN_servo_gain_mask                                  (0x0001C000)
#define REG_DFE_GAIN_le_gain1_mask                                    (0x00003800)
#define REG_DFE_GAIN_le_gain2_mask                                    (0x00000700)
#define REG_DFE_GAIN_le2_sign_mask                                    (0x00000080)
#define REG_DFE_GAIN_le_gain_prec_mask                                (0x00000070)
#define REG_DFE_GAIN_le_prec_sign_mask                                (0x00000008)
#define REG_DFE_GAIN_trans_rlength_mask                               (0x00000007)
#define REG_DFE_GAIN_tap0_gain(data)                                  (0xE0000000&((data)<<29))
#define REG_DFE_GAIN_tap1_gain(data)                                  (0x1C000000&((data)<<26))
#define REG_DFE_GAIN_tap2_gain(data)                                  (0x03800000&((data)<<23))
#define REG_DFE_GAIN_tap3_gain(data)                                  (0x00700000&((data)<<20))
#define REG_DFE_GAIN_tap4_gain(data)                                  (0x000E0000&((data)<<17))
#define REG_DFE_GAIN_servo_gain(data)                                 (0x0001C000&((data)<<14))
#define REG_DFE_GAIN_le_gain1(data)                                   (0x00003800&((data)<<11))
#define REG_DFE_GAIN_le_gain2(data)                                   (0x00000700&((data)<<8))
#define REG_DFE_GAIN_le2_sign(data)                                   (0x00000080&((data)<<7))
#define REG_DFE_GAIN_le_gain_prec(data)                               (0x00000070&((data)<<4))
#define REG_DFE_GAIN_le_prec_sign(data)                               (0x00000008&((data)<<3))
#define REG_DFE_GAIN_trans_rlength(data)                              (0x00000007&(data))
#define REG_DFE_GAIN_get_tap0_gain(data)                              ((0xE0000000&(data))>>29)
#define REG_DFE_GAIN_get_tap1_gain(data)                              ((0x1C000000&(data))>>26)
#define REG_DFE_GAIN_get_tap2_gain(data)                              ((0x03800000&(data))>>23)
#define REG_DFE_GAIN_get_tap3_gain(data)                              ((0x00700000&(data))>>20)
#define REG_DFE_GAIN_get_tap4_gain(data)                              ((0x000E0000&(data))>>17)
#define REG_DFE_GAIN_get_servo_gain(data)                             ((0x0001C000&(data))>>14)
#define REG_DFE_GAIN_get_le_gain1(data)                               ((0x00003800&(data))>>11)
#define REG_DFE_GAIN_get_le_gain2(data)                               ((0x00000700&(data))>>8)
#define REG_DFE_GAIN_get_le2_sign(data)                               ((0x00000080&(data))>>7)
#define REG_DFE_GAIN_get_le_gain_prec(data)                           ((0x00000070&(data))>>4)
#define REG_DFE_GAIN_get_le_prec_sign(data)                           ((0x00000008&(data))>>3)
#define REG_DFE_GAIN_get_trans_rlength(data)                          (0x00000007&(data))


#define REG_DFE_LIMIT0                                                0xf38
#define REG_DFE_LIMIT0_reg_addr                                       "0x98034f38"
#define REG_DFE_LIMIT0_reg                                            0x98034f38
#define REG_DFE_LIMIT0_inst_addr                                      "0x03CE"
#define REG_DFE_LIMIT0_inst                                           0x03CE
#define set_REG_DFE_LIMIT0_reg(data)                                  (*((volatile unsigned int*)REG_DFE_LIMIT0_reg)=data)
#define get_REG_DFE_LIMIT0_reg                                        (*((volatile unsigned int*)REG_DFE_LIMIT0_reg))
#define REG_DFE_LIMIT0_tap0_max_shift                                 (27)
#define REG_DFE_LIMIT0_tap1_min_shift                                 (21)
#define REG_DFE_LIMIT0_tap2_max_shift                                 (16)
#define REG_DFE_LIMIT0_tap2_min_shift                                 (11)
#define REG_DFE_LIMIT0_tap3_max_shift                                 (6)
#define REG_DFE_LIMIT0_tap3_min_shift                                 (1)
#define REG_DFE_LIMIT0_edge_last_notrans_shift                        (0)
#define REG_DFE_LIMIT0_tap0_max_mask                                  (0xF8000000)
#define REG_DFE_LIMIT0_tap1_min_mask                                  (0x07E00000)
#define REG_DFE_LIMIT0_tap2_max_mask                                  (0x001F0000)
#define REG_DFE_LIMIT0_tap2_min_mask                                  (0x0000F800)
#define REG_DFE_LIMIT0_tap3_max_mask                                  (0x000007C0)
#define REG_DFE_LIMIT0_tap3_min_mask                                  (0x0000003E)
#define REG_DFE_LIMIT0_edge_last_notrans_mask                         (0x00000001)
#define REG_DFE_LIMIT0_tap0_max(data)                                 (0xF8000000&((data)<<27))
#define REG_DFE_LIMIT0_tap1_min(data)                                 (0x07E00000&((data)<<21))
#define REG_DFE_LIMIT0_tap2_max(data)                                 (0x001F0000&((data)<<16))
#define REG_DFE_LIMIT0_tap2_min(data)                                 (0x0000F800&((data)<<11))
#define REG_DFE_LIMIT0_tap3_max(data)                                 (0x000007C0&((data)<<6))
#define REG_DFE_LIMIT0_tap3_min(data)                                 (0x0000003E&((data)<<1))
#define REG_DFE_LIMIT0_edge_last_notrans(data)                        (0x00000001&(data))
#define REG_DFE_LIMIT0_get_tap0_max(data)                             ((0xF8000000&(data))>>27)
#define REG_DFE_LIMIT0_get_tap1_min(data)                             ((0x07E00000&(data))>>21)
#define REG_DFE_LIMIT0_get_tap2_max(data)                             ((0x001F0000&(data))>>16)
#define REG_DFE_LIMIT0_get_tap2_min(data)                             ((0x0000F800&(data))>>11)
#define REG_DFE_LIMIT0_get_tap3_max(data)                             ((0x000007C0&(data))>>6)
#define REG_DFE_LIMIT0_get_tap3_min(data)                             ((0x0000003E&(data))>>1)
#define REG_DFE_LIMIT0_get_edge_last_notrans(data)                    (0x00000001&(data))


#define REG_DFE_LIMIT1                                                0xf3c
#define REG_DFE_LIMIT1_reg_addr                                       "0x98034f3c"
#define REG_DFE_LIMIT1_reg                                            0x98034f3c
#define REG_DFE_LIMIT1_inst_addr                                      "0x03CF"
#define REG_DFE_LIMIT1_inst                                           0x03CF
#define set_REG_DFE_LIMIT1_reg(data)                                  (*((volatile unsigned int*)REG_DFE_LIMIT1_reg)=data)
#define get_REG_DFE_LIMIT1_reg                                        (*((volatile unsigned int*)REG_DFE_LIMIT1_reg))
#define REG_DFE_LIMIT1_tap4_max_shift                                 (27)
#define REG_DFE_LIMIT1_tap4_min_shift                                 (22)
#define REG_DFE_LIMIT1_vth_min_shift                                  (19)
#define REG_DFE_LIMIT1_vth_max_shift                                  (15)
#define REG_DFE_LIMIT1_vth_threshold_shift                            (12)
#define REG_DFE_LIMIT1_tap0_threshold_shift                           (8)
#define REG_DFE_LIMIT1_tap0_adjust_shift                              (6)
#define REG_DFE_LIMIT1_tap1_trans_shift                               (5)
#define REG_DFE_LIMIT1_limit1_rev_shift                               (0)
#define REG_DFE_LIMIT1_tap4_max_mask                                  (0xF8000000)
#define REG_DFE_LIMIT1_tap4_min_mask                                  (0x07C00000)
#define REG_DFE_LIMIT1_vth_min_mask                                   (0x00380000)
#define REG_DFE_LIMIT1_vth_max_mask                                   (0x00078000)
#define REG_DFE_LIMIT1_vth_threshold_mask                             (0x00007000)
#define REG_DFE_LIMIT1_tap0_threshold_mask                            (0x00000F00)
#define REG_DFE_LIMIT1_tap0_adjust_mask                               (0x000000C0)
#define REG_DFE_LIMIT1_tap1_trans_mask                                (0x00000020)
#define REG_DFE_LIMIT1_limit1_rev_mask                                (0x0000001F)
#define REG_DFE_LIMIT1_tap4_max(data)                                 (0xF8000000&((data)<<27))
#define REG_DFE_LIMIT1_tap4_min(data)                                 (0x07C00000&((data)<<22))
#define REG_DFE_LIMIT1_vth_min(data)                                  (0x00380000&((data)<<19))
#define REG_DFE_LIMIT1_vth_max(data)                                  (0x00078000&((data)<<15))
#define REG_DFE_LIMIT1_vth_threshold(data)                            (0x00007000&((data)<<12))
#define REG_DFE_LIMIT1_tap0_threshold(data)                           (0x00000F00&((data)<<8))
#define REG_DFE_LIMIT1_tap0_adjust(data)                              (0x000000C0&((data)<<6))
#define REG_DFE_LIMIT1_tap1_trans(data)                               (0x00000020&((data)<<5))
#define REG_DFE_LIMIT1_limit1_rev(data)                               (0x0000001F&(data))
#define REG_DFE_LIMIT1_get_tap4_max(data)                             ((0xF8000000&(data))>>27)
#define REG_DFE_LIMIT1_get_tap4_min(data)                             ((0x07C00000&(data))>>22)
#define REG_DFE_LIMIT1_get_vth_min(data)                              ((0x00380000&(data))>>19)
#define REG_DFE_LIMIT1_get_vth_max(data)                              ((0x00078000&(data))>>15)
#define REG_DFE_LIMIT1_get_vth_threshold(data)                        ((0x00007000&(data))>>12)
#define REG_DFE_LIMIT1_get_tap0_threshold(data)                       ((0x00000F00&(data))>>8)
#define REG_DFE_LIMIT1_get_tap0_adjust(data)                          ((0x000000C0&(data))>>6)
#define REG_DFE_LIMIT1_get_tap1_trans(data)                           ((0x00000020&(data))>>5)
#define REG_DFE_LIMIT1_get_limit1_rev(data)                           (0x0000001F&(data))


#define REG_DFE_LIMIT2                                                0xf40
#define REG_DFE_LIMIT2_reg_addr                                       "0x98034f40"
#define REG_DFE_LIMIT2_reg                                            0x98034f40
#define REG_DFE_LIMIT2_inst_addr                                      "0x03D0"
#define REG_DFE_LIMIT2_inst                                           0x03D0
#define set_REG_DFE_LIMIT2_reg(data)                                  (*((volatile unsigned int*)REG_DFE_LIMIT2_reg)=data)
#define get_REG_DFE_LIMIT2_reg                                        (*((volatile unsigned int*)REG_DFE_LIMIT2_reg))
#define REG_DFE_LIMIT2_servo_divisor_shift                            (26)
#define REG_DFE_LIMIT2_tap_divisor_shift                              (20)
#define REG_DFE_LIMIT2_vth_divisor_shift                              (16)
#define REG_DFE_LIMIT2_limit2_rev_shift                               (0)
#define REG_DFE_LIMIT2_servo_divisor_mask                             (0xFC000000)
#define REG_DFE_LIMIT2_tap_divisor_mask                               (0x03F00000)
#define REG_DFE_LIMIT2_vth_divisor_mask                               (0x000F0000)
#define REG_DFE_LIMIT2_limit2_rev_mask                                (0x0000FFFF)
#define REG_DFE_LIMIT2_servo_divisor(data)                            (0xFC000000&((data)<<26))
#define REG_DFE_LIMIT2_tap_divisor(data)                              (0x03F00000&((data)<<20))
#define REG_DFE_LIMIT2_vth_divisor(data)                              (0x000F0000&((data)<<16))
#define REG_DFE_LIMIT2_limit2_rev(data)                               (0x0000FFFF&(data))
#define REG_DFE_LIMIT2_get_servo_divisor(data)                        ((0xFC000000&(data))>>26)
#define REG_DFE_LIMIT2_get_tap_divisor(data)                          ((0x03F00000&(data))>>20)
#define REG_DFE_LIMIT2_get_vth_divisor(data)                          ((0x000F0000&(data))>>16)
#define REG_DFE_LIMIT2_get_limit2_rev(data)                           (0x0000FFFF&(data))


#define REG_DFE_READBACK                                              0xf44
#define REG_DFE_READBACK_reg_addr                                     "0x98034f44"
#define REG_DFE_READBACK_reg                                          0x98034f44
#define REG_DFE_READBACK_inst_addr                                    "0x03D1"
#define REG_DFE_READBACK_inst                                         0x03D1
#define set_REG_DFE_READBACK_reg(data)                                (*((volatile unsigned int*)REG_DFE_READBACK_reg)=data)
#define get_REG_DFE_READBACK_reg                                      (*((volatile unsigned int*)REG_DFE_READBACK_reg))
#define REG_DFE_READBACK_record_limit_en_shift                        (31)
#define REG_DFE_READBACK_lane_sel_shift                               (29)
#define REG_DFE_READBACK_limit_sel_shift                              (24)
#define REG_DFE_READBACK_limit_data_shift                             (16)
#define REG_DFE_READBACK_coef_sel_shift                               (8)
#define REG_DFE_READBACK_coef_data_shift                              (0)
#define REG_DFE_READBACK_record_limit_en_mask                         (0x80000000)
#define REG_DFE_READBACK_lane_sel_mask                                (0x60000000)
#define REG_DFE_READBACK_limit_sel_mask                               (0x1F000000)
#define REG_DFE_READBACK_limit_data_mask                              (0x00FF0000)
#define REG_DFE_READBACK_coef_sel_mask                                (0x0000FF00)
#define REG_DFE_READBACK_coef_data_mask                               (0x000000FF)
#define REG_DFE_READBACK_record_limit_en(data)                        (0x80000000&((data)<<31))
#define REG_DFE_READBACK_lane_sel(data)                               (0x60000000&((data)<<29))
#define REG_DFE_READBACK_limit_sel(data)                              (0x1F000000&((data)<<24))
#define REG_DFE_READBACK_limit_data(data)                             (0x00FF0000&((data)<<16))
#define REG_DFE_READBACK_coef_sel(data)                               (0x0000FF00&((data)<<8))
#define REG_DFE_READBACK_coef_data(data)                              (0x000000FF&(data))
#define REG_DFE_READBACK_get_record_limit_en(data)                    ((0x80000000&(data))>>31)
#define REG_DFE_READBACK_get_lane_sel(data)                           ((0x60000000&(data))>>29)
#define REG_DFE_READBACK_get_limit_sel(data)                          ((0x1F000000&(data))>>24)
#define REG_DFE_READBACK_get_limit_data(data)                         ((0x00FF0000&(data))>>16)
#define REG_DFE_READBACK_get_coef_sel(data)                           ((0x0000FF00&(data))>>8)
#define REG_DFE_READBACK_get_coef_data(data)                          (0x000000FF&(data))
#define limit_set_lane_mask											(_BIT30|_BIT29)
#define limit_set_lane_shift										(29)
#define limit_set_mask												(_BIT28|_BIT27|_BIT26|_BIT25|_BIT24)
#define limit_sel(data)												(limit_set_mask&((data)<<24))
#define get_Tap0_max(data)											((0x1F0000&(data))>>16)
#define get_Tap0_min(data)											((0x1F0000&(data))>>16)
#define get_Tap1_max(data)											((0x3F0000&(data))>>16)
#define get_Tap1_min(data)											((0x3F0000&(data))>>16)
#define get_LEQ_max(data)											((0x1F0000&(data))>>16)
#define get_LEQ_min(data)											((0x1F0000&(data))>>16)
#define coef_set_lane_mask											(_BIT15|_BIT14)
#define coef_set_lane_shift											(14)
#define coef_set_mask												(_BIT13|_BIT12|_BIT11|_BIT10|_BIT9|_BIT8)
#define coef_sel(data)												(coef_set_mask&((data)<<8))
#define get_VTH_coef(data)											(0xF&(data))
#define get_TAP0_coef(data)											(0x1F&(data))
#define get_TAP1_coef(data)											(0x3F&(data))
#define get_TAP2_coef_sign(data)									(0x20&(data))
#define get_TAP2_coef(data)											(0x1F&(data))
#define get_TAP3_coef_sign(data)									(0x20&(data))
#define get_TAP3_coef(data)											(0x1F&(data))
#define get_TAP4_coef_sign(data)									(0x20&(data))
#define get_TAP4_coef(data)											(0x1F&(data))
#define get_SERVO_coef(data)										(0x1F&(data))
#define get_LE1_coef(data)											(0x1F&(data))
#define get_CurrentStep_coef(data)									((0x30&(data))>>4)
#define get_BufferMode_coef(data)									((0xc0&(data))>>6)


#define REG_DFE_FLAG                                                  0xf48
#define REG_DFE_FLAG_reg_addr                                         "0x98034f48"
#define REG_DFE_FLAG_reg                                              0x98034f48
#define REG_DFE_FLAG_inst_addr                                        "0x03D2"
#define REG_DFE_FLAG_inst                                             0x03D2
#define set_REG_DFE_FLAG_reg(data)                                    (*((volatile unsigned int*)REG_DFE_FLAG_reg)=data)
#define get_REG_DFE_FLAG_reg                                          (*((volatile unsigned int*)REG_DFE_FLAG_reg))
#define REG_DFE_FLAG_adapt_fail_flag_shift                            (28)
#define REG_DFE_FLAG_adapt_swing_max_flag_shift                       (24)
#define REG_DFE_FLAG_flag_rev1_shift                                  (12)
#define REG_DFE_FLAG_flag_rev2_shift                                  (0)
#define REG_DFE_FLAG_adapt_fail_flag_mask                             (0xF0000000)
#define REG_DFE_FLAG_adapt_swing_max_flag_mask                        (0x0F000000)
#define REG_DFE_FLAG_flag_rev1_mask                                   (0x00FFF000)
#define REG_DFE_FLAG_flag_rev2_mask                                   (0x00000FFF)
#define REG_DFE_FLAG_adapt_fail_flag(data)                            (0xF0000000&((data)<<28))
#define REG_DFE_FLAG_adapt_swing_max_flag(data)                       (0x0F000000&((data)<<24))
#define REG_DFE_FLAG_flag_rev1(data)                                  (0x00FFF000&((data)<<12))
#define REG_DFE_FLAG_flag_rev2(data)                                  (0x00000FFF&(data))
#define REG_DFE_FLAG_get_adapt_fail_flag(data)                        ((0xF0000000&(data))>>28)
#define REG_DFE_FLAG_get_adapt_swing_max_flag(data)                   ((0x0F000000&(data))>>24)
#define REG_DFE_FLAG_get_flag_rev1(data)                              ((0x00FFF000&(data))>>12)
#define REG_DFE_FLAG_get_flag_rev2(data)                              (0x00000FFF&(data))


#define REG_DFE_DEBUG                                                 0xf50
#define REG_DFE_DEBUG_reg_addr                                        "0x98034f50"
#define REG_DFE_DEBUG_reg                                             0x98034f50
#define REG_DFE_DEBUG_inst_addr                                       "0x03D4"
#define REG_DFE_DEBUG_inst                                            0x03D4
#define set_REG_DFE_DEBUG_reg(data)                                   (*((volatile unsigned int*)REG_DFE_DEBUG_reg)=data)
#define get_REG_DFE_DEBUG_reg                                         (*((volatile unsigned int*)REG_DFE_DEBUG_reg))
#define REG_DFE_DEBUG_debug_rev_shift                                 (5)
#define REG_DFE_DEBUG_debug_sel_shift                                 (0)
#define REG_DFE_DEBUG_debug_rev_mask                                  (0xFFFFFFE0)
#define REG_DFE_DEBUG_debug_sel_mask                                  (0x0000001F)
#define REG_DFE_DEBUG_debug_rev(data)                                 (0xFFFFFFE0&((data)<<5))
#define REG_DFE_DEBUG_debug_sel(data)                                 (0x0000001F&(data))
#define REG_DFE_DEBUG_get_debug_rev(data)                             ((0xFFFFFFE0&(data))>>5)
#define REG_DFE_DEBUG_get_debug_sel(data)                             (0x0000001F&(data))
#endif
