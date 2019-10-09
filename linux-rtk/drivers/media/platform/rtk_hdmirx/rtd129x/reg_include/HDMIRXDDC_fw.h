// This file is generated using the spec version 1.39, firmware template version 1.39and SRIF Parser                                                                                source code SVN rev:802                    Version flow no.:1.1.66
#ifndef _DDC_REG_H_INCLUDED_
#define _DDC_REG_H_INCLUDED_

#define DDC2_I2C_CR                                                   0x00
#define DDC2_I2C_CR_reg_addr                                          "0x98037704"

#define DDC2_I2C_SR1                                                  0x04
#define DDC2_I2C_SR1_reg_addr                                         "0x98037704"
#define DDC2_I2C_SR1_reg                                              0x98037704
#define DDC2_I2C_SR1_inst_addr                                        "0x01C1"
#define DDC2_I2C_SR1_inst                                             0x01C1
#define DDC2_I2C_SR1_cmderr_shift                                     (7)
#define DDC2_I2C_SR1_finish_shift                                     (4)
#define DDC2_I2C_SR1_timeout_shift                                    (3)
#define DDC2_I2C_SR1_cmderr_mask                                      (0x00000080)
#define DDC2_I2C_SR1_finish_mask                                      (0x00000010)
#define DDC2_I2C_SR1_timeout_mask                                     (0x00000008)
#define DDC2_I2C_SR1_cmderr(data)                                     (0x00000080&((data)<<7))
#define DDC2_I2C_SR1_finish(data)                                     (0x00000010&((data)<<4))
#define DDC2_I2C_SR1_timeout(data)                                    (0x00000008&((data)<<3))
#define DDC2_I2C_SR1_get_cmderr(data)                                 ((0x00000080&(data))>>7)
#define DDC2_I2C_SR1_get_finish(data)                                 ((0x00000010&(data))>>4)
#define DDC2_I2C_SR1_get_timeout(data)                                ((0x00000008&(data))>>3)


#define DDC2_I2C_TR                                                   0x08
#define DDC2_I2C_TR_reg_addr                                          "0x98037708"
#define DDC2_I2C_TR_reg                                               0x98037708
#define DDC2_I2C_TR_inst_addr                                         "0x01C2"
#define DDC2_I2C_TR_inst                                              0x01C2
#define DDC2_I2C_TR_timeout_val_shift                                 (0)
#define DDC2_I2C_TR_timeout_val_mask                                  (0x000000FF)
#define DDC2_I2C_TR_timeout_val(data)                                 (0x000000FF&(data))
#define DDC2_I2C_TR_get_timeout_val(data)                             (0x000000FF&(data))


#define DDC2_EDID_CR                                                  0x0c
#define DDC2_EDID_CR_reg_addr                                         "0x9803770c"
#define DDC2_EDID_CR_reg                                              0x9803770c
#define DDC2_EDID_CR_inst_addr                                        "0x01C3"
#define DDC2_EDID_CR_inst                                             0x01C3
#define DDC2_EDID_CR_edid_address_shift                               (5)
#define DDC2_EDID_CR_finish_int_en_shift                              (4)
#define DDC2_EDID_CR_ddc2_force_shift                                 (3)
#define DDC2_EDID_CR_ddc2b_force_shift                                (2)
#define DDC2_EDID_CR_edid_srwen_shift                                 (1)
#define DDC2_EDID_CR_edid_en_shift                                    (0)
#define DDC2_EDID_CR_edid_address_mask                                (0x000000E0)
#define DDC2_EDID_CR_finish_int_en_mask                               (0x00000010)
#define DDC2_EDID_CR_ddc2_force_mask                                  (0x00000008)
#define DDC2_EDID_CR_ddc2b_force_mask                                 (0x00000004)
#define DDC2_EDID_CR_edid_srwen_mask                                  (0x00000002)
#define DDC2_EDID_CR_edid_en_mask                                     (0x00000001)
#define DDC2_EDID_CR_edid_address(data)                               (0x000000E0&((data)<<5))
#define DDC2_EDID_CR_finish_int_en(data)                              (0x00000010&((data)<<4))
#define DDC2_EDID_CR_ddc2_force(data)                                 (0x00000008&((data)<<3))
#define DDC2_EDID_CR_ddc2b_force(data)                                (0x00000004&((data)<<2))
#define DDC2_EDID_CR_edid_srwen(data)                                 (0x00000002&((data)<<1))
#define DDC2_EDID_CR_edid_en(data)                                    (0x00000001&(data))
#define DDC2_EDID_CR_get_edid_address(data)                           ((0x000000E0&(data))>>5)
#define DDC2_EDID_CR_get_finish_int_en(data)                          ((0x00000010&(data))>>4)
#define DDC2_EDID_CR_get_ddc2_force(data)                             ((0x00000008&(data))>>3)
#define DDC2_EDID_CR_get_ddc2b_force(data)                            ((0x00000004&(data))>>2)
#define DDC2_EDID_CR_get_edid_srwen(data)                             ((0x00000002&(data))>>1)
#define DDC2_EDID_CR_get_edid_en(data)                                (0x00000001&(data))


#define DDC2_DDC_VCR                                                  0x10
#define DDC2_DDC_VCR_reg_addr                                         "0x98037710"
#define DDC2_DDC_VCR_reg                                              0x98037710
#define DDC2_DDC_VCR_inst_addr                                        "0x01C4"
#define DDC2_DDC_VCR_inst                                             0x01C4
#define DDC2_DDC_VCR_ddc2_vcount_shift                                (0)
#define DDC2_DDC_VCR_ddc2_vcount_mask                                 (0x000000FF)
#define DDC2_DDC_VCR_ddc2_vcount(data)                                (0x000000FF&(data))
#define DDC2_DDC_VCR_get_ddc2_vcount(data)                            (0x000000FF&(data))


#define DDC2_EDID_IMSWSAR                                             0x14
#define DDC2_EDID_IMSWSAR_reg_addr                                    "0x98037714"
#define DDC2_EDID_IMSWSAR_reg                                         0x98037714
#define DDC2_EDID_IMSWSAR_inst_addr                                   "0x01C5"
#define DDC2_EDID_IMSWSAR_inst                                        0x01C5
#define DDC2_EDID_IMSWSAR_edid_sadr_shift                             (0)
#define DDC2_EDID_IMSWSAR_edid_sadr_mask                              (0x000000FF)
#define DDC2_EDID_IMSWSAR_edid_sadr(data)                             (0x000000FF&(data))
#define DDC2_EDID_IMSWSAR_get_edid_sadr(data)                         (0x000000FF&(data))


#define DDC2_EDID_IMSWEAR                                             0x18
#define DDC2_EDID_IMSWEAR_reg_addr                                    "0x98037718"
#define DDC2_EDID_IMSWEAR_reg                                         0x98037718
#define DDC2_EDID_IMSWEAR_inst_addr                                   "0x01C6"
#define DDC2_EDID_IMSWEAR_inst                                        0x01C6
#define DDC2_EDID_IMSWEAR_edid_eadr_shift                             (0)
#define DDC2_EDID_IMSWEAR_edid_eadr_mask                              (0x000000FF)
#define DDC2_EDID_IMSWEAR_edid_eadr(data)                             (0x000000FF&(data))
#define DDC2_EDID_IMSWEAR_get_edid_eadr(data)                         (0x000000FF&(data))


#define DDC2_EDID_IR                                                  0x1c
#define DDC2_EDID_IR_reg_addr                                         "0x9803771c"
#define DDC2_EDID_IR_reg                                              0x9803771c
#define DDC2_EDID_IR_inst_addr                                        "0x01C7"
#define DDC2_EDID_IR_inst                                             0x01C7
#define DDC2_EDID_IR_edidmode_shift                                   (6)
#define DDC2_EDID_IR_edidsubaddress_shift                             (5)
#define DDC2_EDID_IR_edidstop_shift                                   (4)
#define DDC2_EDID_IR_i2c_m_rd_st_ie_shift                             (3)
#define DDC2_EDID_IR_i2c_m_rd_sp_ie_shift                             (2)
#define DDC2_EDID_IR_edidsubaddress_ie_shift                          (1)
#define DDC2_EDID_IR_edidstop_ie_shift                                (0)
#define DDC2_EDID_IR_edidmode_mask                                    (0x00000040)
#define DDC2_EDID_IR_edidsubaddress_mask                              (0x00000020)
#define DDC2_EDID_IR_edidstop_mask                                    (0x00000010)
#define DDC2_EDID_IR_i2c_m_rd_st_ie_mask                              (0x00000008)
#define DDC2_EDID_IR_i2c_m_rd_sp_ie_mask                              (0x00000004)
#define DDC2_EDID_IR_edidsubaddress_ie_mask                           (0x00000002)
#define DDC2_EDID_IR_edidstop_ie_mask                                 (0x00000001)
#define DDC2_EDID_IR_edidmode(data)                                   (0x00000040&((data)<<6))
#define DDC2_EDID_IR_edidsubaddress(data)                             (0x00000020&((data)<<5))
#define DDC2_EDID_IR_edidstop(data)                                   (0x00000010&((data)<<4))
#define DDC2_EDID_IR_i2c_m_rd_st_ie(data)                             (0x00000008&((data)<<3))
#define DDC2_EDID_IR_i2c_m_rd_sp_ie(data)                             (0x00000004&((data)<<2))
#define DDC2_EDID_IR_edidsubaddress_ie(data)                          (0x00000002&((data)<<1))
#define DDC2_EDID_IR_edidstop_ie(data)                                (0x00000001&(data))
#define DDC2_EDID_IR_get_edidmode(data)                               ((0x00000040&(data))>>6)
#define DDC2_EDID_IR_get_edidsubaddress(data)                         ((0x00000020&(data))>>5)
#define DDC2_EDID_IR_get_edidstop(data)                               ((0x00000010&(data))>>4)
#define DDC2_EDID_IR_get_i2c_m_rd_st_ie(data)                         ((0x00000008&(data))>>3)
#define DDC2_EDID_IR_get_i2c_m_rd_sp_ie(data)                         ((0x00000004&(data))>>2)
#define DDC2_EDID_IR_get_edidsubaddress_ie(data)                      ((0x00000002&(data))>>1)
#define DDC2_EDID_IR_get_edidstop_ie(data)                            (0x00000001&(data))


#define DDC2_DDC_SIR                                                  0x20
#define DDC2_DDC_SIR_reg_addr                                         "0x98037720"
#define DDC2_DDC_SIR_reg                                              0x98037720
#define DDC2_DDC_SIR_inst_addr                                        "0x01C8"
#define DDC2_DDC_SIR_inst                                             0x01C8
#define DDC2_DDC_SIR_edidap_shift                                     (0)
#define DDC2_DDC_SIR_edidap_mask                                      (0x000000FF)
#define DDC2_DDC_SIR_edidap(data)                                     (0x000000FF&(data))
#define DDC2_DDC_SIR_get_edidap(data)                                 (0x000000FF&(data))


#define DDC2_DDC_SAP                                                  0x24
#define DDC2_DDC_SAP_reg_addr                                         "0x98037724"
#define DDC2_DDC_SAP_reg                                              0x98037724
#define DDC2_DDC_SAP_inst_addr                                        "0x01C9"
#define DDC2_DDC_SAP_inst                                             0x01C9
#define DDC2_DDC_SAP_ediddp_shift                                     (0)
#define DDC2_DDC_SAP_ediddp_mask                                      (0x000000FF)
#define DDC2_DDC_SAP_ediddp(data)                                     (0x000000FF&(data))
#define DDC2_DDC_SAP_get_ediddp(data)                                 (0x000000FF&(data))


#define DDC2_DDC_BISTCR                                               0x28
#define DDC2_DDC_BISTCR_reg_addr                                      "0x98037728"
#define DDC2_DDC_BISTCR_reg                                           0x98037728
#define DDC2_DDC_BISTCR_inst_addr                                     "0x01CA"
#define DDC2_DDC_BISTCR_inst                                          0x01CA
#define DDC2_DDC_BISTCR_ddc_bist_rme_shift                            (4)
#define DDC2_DDC_BISTCR_ddc_bist_rm_shift                             (0)
#define DDC2_DDC_BISTCR_ddc_bist_rme_mask                             (0x00000010)
#define DDC2_DDC_BISTCR_ddc_bist_rm_mask                              (0x0000000F)
#define DDC2_DDC_BISTCR_ddc_bist_rme(data)                            (0x00000010&((data)<<4))
#define DDC2_DDC_BISTCR_ddc_bist_rm(data)                             (0x0000000F&(data))
#define DDC2_DDC_BISTCR_get_ddc_bist_rme(data)                        ((0x00000010&(data))>>4)
#define DDC2_DDC_BISTCR_get_ddc_bist_rm(data)                         (0x0000000F&(data))


#define DDC2_DDC_SCR                                                  0x2c
#define DDC2_DDC_SCR_reg_addr                                         "0x9803772c"
#define DDC2_DDC_SCR_reg                                              0x9803772c
#define DDC2_DDC_SCR_inst_addr                                        "0x01CB"
#define DDC2_DDC_SCR_inst                                             0x01CB
#define DDC2_DDC_SCR_segpt_latie_shift                                (7)
#define DDC2_DDC_SCR_dataoutputdelay_sel_shift                        (4)
#define DDC2_DDC_SCR_i2c_m_rd_st_sts_shift                            (2)
#define DDC2_DDC_SCR_i2c_m_rd_sp_sts_shift                            (1)
#define DDC2_DDC_SCR_sgid_en_shift                                    (0)
#define DDC2_DDC_SCR_segpt_latie_mask                                 (0x00000080)
#define DDC2_DDC_SCR_dataoutputdelay_sel_mask                         (0x00000070)
#define DDC2_DDC_SCR_i2c_m_rd_st_sts_mask                             (0x00000004)
#define DDC2_DDC_SCR_i2c_m_rd_sp_sts_mask                             (0x00000002)
#define DDC2_DDC_SCR_sgid_en_mask                                     (0x00000001)
#define DDC2_DDC_SCR_segpt_latie(data)                                (0x00000080&((data)<<7))
#define DDC2_DDC_SCR_dataoutputdelay_sel(data)                        (0x00000070&((data)<<4))
#define DDC2_DDC_SCR_i2c_m_rd_st_sts(data)                            (0x00000004&((data)<<2))
#define DDC2_DDC_SCR_i2c_m_rd_sp_sts(data)                            (0x00000002&((data)<<1))
#define DDC2_DDC_SCR_sgid_en(data)                                    (0x00000001&(data))
#define DDC2_DDC_SCR_get_segpt_latie(data)                            ((0x00000080&(data))>>7)
#define DDC2_DDC_SCR_get_dataoutputdelay_sel(data)                    ((0x00000070&(data))>>4)
#define DDC2_DDC_SCR_get_i2c_m_rd_st_sts(data)                        ((0x00000004&(data))>>2)
#define DDC2_DDC_SCR_get_i2c_m_rd_sp_sts(data)                        ((0x00000002&(data))>>1)
#define DDC2_DDC_SCR_get_sgid_en(data)                                (0x00000001&(data))


#define DDC2_DDC_SSAR                                                 0x30
#define DDC2_DDC_SSAR_reg_addr                                        "0x98037730"
#define DDC2_DDC_SSAR_reg                                             0x98037730
#define DDC2_DDC_SSAR_inst_addr                                       "0x01CC"
#define DDC2_DDC_SSAR_inst                                            0x01CC
#define DDC2_DDC_SSAR_sgid_address_shift                              (1)
#define DDC2_DDC_SSAR_sgid_dtrden_shift                               (0)
#define DDC2_DDC_SSAR_sgid_address_mask                               (0x000000FE)
#define DDC2_DDC_SSAR_sgid_dtrden_mask                                (0x00000001)
#define DDC2_DDC_SSAR_sgid_address(data)                              (0x000000FE&((data)<<1))
#define DDC2_DDC_SSAR_sgid_dtrden(data)                               (0x00000001&(data))
#define DDC2_DDC_SSAR_get_sgid_address(data)                          ((0x000000FE&(data))>>1)
#define DDC2_DDC_SSAR_get_sgid_dtrden(data)                           (0x00000001&(data))


#define DDC2_DDC_SPR                                                  0x34
#define DDC2_DDC_SPR_reg_addr                                         "0x98037734"
#define DDC2_DDC_SPR_reg                                              0x98037734
#define DDC2_DDC_SPR_inst_addr                                        "0x01CD"
#define DDC2_DDC_SPR_inst                                             0x01CD
#define DDC2_DDC_SPR_segpt_latched_shift                              (7)
#define DDC2_DDC_SPR_seg_pt_shift                                     (0)
#define DDC2_DDC_SPR_segpt_latched_mask                               (0x00000080)
#define DDC2_DDC_SPR_seg_pt_mask                                      (0x0000007F)
#define DDC2_DDC_SPR_segpt_latched(data)                              (0x00000080&((data)<<7))
#define DDC2_DDC_SPR_seg_pt(data)                                     (0x0000007F&(data))
#define DDC2_DDC_SPR_get_segpt_latched(data)                          ((0x00000080&(data))>>7)
#define DDC2_DDC_SPR_get_seg_pt(data)                                 (0x0000007F&(data))


#define DDC2_DDC_SFCR                                                 0x38
#define DDC2_DDC_SFCR_reg_addr                                        "0x98037738"
#define DDC2_DDC_SFCR_reg                                             0x98037738
#define DDC2_DDC_SFCR_inst_addr                                       "0x01CE"
#define DDC2_DDC_SFCR_inst                                            0x01CE
#define DDC2_DDC_SFCR_special_mode_shift                              (3)
#define DDC2_DDC_SFCR_doffpt_reset_shift                              (2)
#define DDC2_DDC_SFCR_diffpt_reset_shift                              (1)
#define DDC2_DDC_SFCR_ciid_en_shift                                   (0)
#define DDC2_DDC_SFCR_special_mode_mask                               (0x00000008)
#define DDC2_DDC_SFCR_doffpt_reset_mask                               (0x00000004)
#define DDC2_DDC_SFCR_diffpt_reset_mask                               (0x00000002)
#define DDC2_DDC_SFCR_ciid_en_mask                                    (0x00000001)
#define DDC2_DDC_SFCR_special_mode(data)                              (0x00000008&((data)<<3))
#define DDC2_DDC_SFCR_doffpt_reset(data)                              (0x00000004&((data)<<2))
#define DDC2_DDC_SFCR_diffpt_reset(data)                              (0x00000002&((data)<<1))
#define DDC2_DDC_SFCR_ciid_en(data)                                   (0x00000001&(data))
#define DDC2_DDC_SFCR_get_special_mode(data)                          ((0x00000008&(data))>>3)
#define DDC2_DDC_SFCR_get_doffpt_reset(data)                          ((0x00000004&(data))>>2)
#define DDC2_DDC_SFCR_get_diffpt_reset(data)                          ((0x00000002&(data))>>1)
#define DDC2_DDC_SFCR_get_ciid_en(data)                               (0x00000001&(data))


#define DDC2_DDC_SFSAR                                                0x3c
#define DDC2_DDC_SFSAR_reg_addr                                       "0x9803773c"
#define DDC2_DDC_SFSAR_reg                                            0x9803773c
#define DDC2_DDC_SFSAR_inst_addr                                      "0x01CF"
#define DDC2_DDC_SFSAR_inst                                           0x01CF
#define DDC2_DDC_SFSAR_ciid_address_shift                             (1)
#define DDC2_DDC_SFSAR_cirws_current_shift                            (0)
#define DDC2_DDC_SFSAR_ciid_address_mask                              (0x000000FE)
#define DDC2_DDC_SFSAR_cirws_current_mask                             (0x00000001)
#define DDC2_DDC_SFSAR_ciid_address(data)                             (0x000000FE&((data)<<1))
#define DDC2_DDC_SFSAR_cirws_current(data)                            (0x00000001&(data))
#define DDC2_DDC_SFSAR_get_ciid_address(data)                         ((0x000000FE&(data))>>1)
#define DDC2_DDC_SFSAR_get_cirws_current(data)                        (0x00000001&(data))


#define DDC2_DDC_SFDR                                                 0x40
#define DDC2_DDC_SFDR_reg_addr                                        "0x98037740"
#define DDC2_DDC_SFDR_reg                                             0x98037740
#define DDC2_DDC_SFDR_inst_addr                                       "0x01D0"
#define DDC2_DDC_SFDR_inst                                            0x01D0
#define DDC2_DDC_SFDR_ciiddp_shift                                    (0)
#define DDC2_DDC_SFDR_ciiddp_mask                                     (0x000000FF)
#define DDC2_DDC_SFDR_ciiddp(data)                                    (0x000000FF&(data))
#define DDC2_DDC_SFDR_get_ciiddp(data)                                (0x000000FF&(data))


#define DDC2_DDC_SFBSR                                                0x44
#define DDC2_DDC_SFBSR_reg_addr                                       "0x98037744"
#define DDC2_DDC_SFBSR_reg                                            0x98037744
#define DDC2_DDC_SFBSR_inst_addr                                      "0x01D1"
#define DDC2_DDC_SFBSR_inst                                           0x01D1
#define DDC2_DDC_SFBSR_cirws_2nd_shift                                (5)
#define DDC2_DDC_SFBSR_cirws_1st_shift                                (4)
#define DDC2_DDC_SFBSR_cippt_2nd_shift                                (3)
#define DDC2_DDC_SFBSR_cispt_2nd_shift                                (2)
#define DDC2_DDC_SFBSR_cippt_1st_shift                                (1)
#define DDC2_DDC_SFBSR_cispt_1st_shift                                (0)
#define DDC2_DDC_SFBSR_cirws_2nd_mask                                 (0x00000020)
#define DDC2_DDC_SFBSR_cirws_1st_mask                                 (0x00000010)
#define DDC2_DDC_SFBSR_cippt_2nd_mask                                 (0x00000008)
#define DDC2_DDC_SFBSR_cispt_2nd_mask                                 (0x00000004)
#define DDC2_DDC_SFBSR_cippt_1st_mask                                 (0x00000002)
#define DDC2_DDC_SFBSR_cispt_1st_mask                                 (0x00000001)
#define DDC2_DDC_SFBSR_cirws_2nd(data)                                (0x00000020&((data)<<5))
#define DDC2_DDC_SFBSR_cirws_1st(data)                                (0x00000010&((data)<<4))
#define DDC2_DDC_SFBSR_cippt_2nd(data)                                (0x00000008&((data)<<3))
#define DDC2_DDC_SFBSR_cispt_2nd(data)                                (0x00000004&((data)<<2))
#define DDC2_DDC_SFBSR_cippt_1st(data)                                (0x00000002&((data)<<1))
#define DDC2_DDC_SFBSR_cispt_1st(data)                                (0x00000001&(data))
#define DDC2_DDC_SFBSR_get_cirws_2nd(data)                            ((0x00000020&(data))>>5)
#define DDC2_DDC_SFBSR_get_cirws_1st(data)                            ((0x00000010&(data))>>4)
#define DDC2_DDC_SFBSR_get_cippt_2nd(data)                            ((0x00000008&(data))>>3)
#define DDC2_DDC_SFBSR_get_cispt_2nd(data)                            ((0x00000004&(data))>>2)
#define DDC2_DDC_SFBSR_get_cippt_1st(data)                            ((0x00000002&(data))>>1)
#define DDC2_DDC_SFBSR_get_cispt_1st(data)                            (0x00000001&(data))


#define DDC2_DDC_SFIBLR                                               0x48
#define DDC2_DDC_SFIBLR_reg_addr                                      "0x98037748"
#define DDC2_DDC_SFIBLR_reg                                           0x98037748
#define DDC2_DDC_SFIBLR_inst_addr                                     "0x01D2"
#define DDC2_DDC_SFIBLR_inst                                          0x01D2
#define DDC2_DDC_SFIBLR_ffdi_dlen_shift                               (0)
#define DDC2_DDC_SFIBLR_ffdi_dlen_mask                                (0x0000001F)
#define DDC2_DDC_SFIBLR_ffdi_dlen(data)                               (0x0000001F&(data))
#define DDC2_DDC_SFIBLR_get_ffdi_dlen(data)                           (0x0000001F&(data))


#define DDC2_DDC_SFIBRWPR                                             0x4c
#define DDC2_DDC_SFIBRWPR_reg_addr                                    "0x9803774c"
#define DDC2_DDC_SFIBRWPR_reg                                         0x9803774c
#define DDC2_DDC_SFIBRWPR_inst_addr                                   "0x01D3"
#define DDC2_DDC_SFIBRWPR_inst                                        0x01D3
#define DDC2_DDC_SFIBRWPR_diff_wpt_shift                              (4)
#define DDC2_DDC_SFIBRWPR_diff_rpt_shift                              (0)
#define DDC2_DDC_SFIBRWPR_diff_wpt_mask                               (0x000000F0)
#define DDC2_DDC_SFIBRWPR_diff_rpt_mask                               (0x0000000F)
#define DDC2_DDC_SFIBRWPR_diff_wpt(data)                              (0x000000F0&((data)<<4))
#define DDC2_DDC_SFIBRWPR_diff_rpt(data)                              (0x0000000F&(data))
#define DDC2_DDC_SFIBRWPR_get_diff_wpt(data)                          ((0x000000F0&(data))>>4)
#define DDC2_DDC_SFIBRWPR_get_diff_rpt(data)                          (0x0000000F&(data))


#define DDC2_DDC_SFIBSWPR                                             0x50
#define DDC2_DDC_SFIBSWPR_reg_addr                                    "0x98037750"
#define DDC2_DDC_SFIBSWPR_reg                                         0x98037750
#define DDC2_DDC_SFIBSWPR_inst_addr                                   "0x01D4"
#define DDC2_DDC_SFIBSWPR_inst                                        0x01D4
#define DDC2_DDC_SFIBSWPR_diffstop_pt_shift                           (0)
#define DDC2_DDC_SFIBSWPR_diffstop_pt_mask                            (0x0000000F)
#define DDC2_DDC_SFIBSWPR_diffstop_pt(data)                           (0x0000000F&(data))
#define DDC2_DDC_SFIBSWPR_get_diffstop_pt(data)                       (0x0000000F&(data))


#define DDC2_DDC_SFOBSR                                               0x54
#define DDC2_DDC_SFOBSR_reg_addr                                      "0x98037754"
#define DDC2_DDC_SFOBSR_reg                                           0x98037754
#define DDC2_DDC_SFOBSR_inst_addr                                     "0x01D5"
#define DDC2_DDC_SFOBSR_inst                                          0x01D5
#define DDC2_DDC_SFOBSR_ffdo_dlen_shift                               (0)
#define DDC2_DDC_SFOBSR_ffdo_dlen_mask                                (0x0000001F)
#define DDC2_DDC_SFOBSR_ffdo_dlen(data)                               (0x0000001F&(data))
#define DDC2_DDC_SFOBSR_get_ffdo_dlen(data)                           (0x0000001F&(data))


#define DDC2_DDC_SFOBRWPR                                             0x58
#define DDC2_DDC_SFOBRWPR_reg_addr                                    "0x98037758"
#define DDC2_DDC_SFOBRWPR_reg                                         0x98037758
#define DDC2_DDC_SFOBRWPR_inst_addr                                   "0x01D6"
#define DDC2_DDC_SFOBRWPR_inst                                        0x01D6
#define DDC2_DDC_SFOBRWPR_doff_wpt_shift                              (4)
#define DDC2_DDC_SFOBRWPR_doff_rpt_shift                              (0)
#define DDC2_DDC_SFOBRWPR_doff_wpt_mask                               (0x000000F0)
#define DDC2_DDC_SFOBRWPR_doff_rpt_mask                               (0x0000000F)
#define DDC2_DDC_SFOBRWPR_doff_wpt(data)                              (0x000000F0&((data)<<4))
#define DDC2_DDC_SFOBRWPR_doff_rpt(data)                              (0x0000000F&(data))
#define DDC2_DDC_SFOBRWPR_get_doff_wpt(data)                          ((0x000000F0&(data))>>4)
#define DDC2_DDC_SFOBRWPR_get_doff_rpt(data)                          (0x0000000F&(data))


#define DDC2_DDC_SFSR                                                 0x5c
#define DDC2_DDC_SFSR_reg_addr                                        "0x9803775c"
#define DDC2_DDC_SFSR_reg                                             0x9803775c
#define DDC2_DDC_SFSR_inst_addr                                       "0x01D7"
#define DDC2_DDC_SFSR_inst                                            0x01D7
#define DDC2_DDC_SFSR_ffdouf_st_shift                                 (7)
#define DDC2_DDC_SFSR_ffdiof_st_shift                                 (6)
#define DDC2_DDC_SFSR_ffdonf_st_shift                                 (5)
#define DDC2_DDC_SFSR_ffdoet_st_shift                                 (4)
#define DDC2_DDC_SFSR_ffdifu_st_shift                                 (3)
#define DDC2_DDC_SFSR_ffdine_st_shift                                 (2)
#define DDC2_DDC_SFSR_ffdouf_st_mask                                  (0x00000080)
#define DDC2_DDC_SFSR_ffdiof_st_mask                                  (0x00000040)
#define DDC2_DDC_SFSR_ffdonf_st_mask                                  (0x00000020)
#define DDC2_DDC_SFSR_ffdoet_st_mask                                  (0x00000010)
#define DDC2_DDC_SFSR_ffdifu_st_mask                                  (0x00000008)
#define DDC2_DDC_SFSR_ffdine_st_mask                                  (0x00000004)
#define DDC2_DDC_SFSR_ffdouf_st(data)                                 (0x00000080&((data)<<7))
#define DDC2_DDC_SFSR_ffdiof_st(data)                                 (0x00000040&((data)<<6))
#define DDC2_DDC_SFSR_ffdonf_st(data)                                 (0x00000020&((data)<<5))
#define DDC2_DDC_SFSR_ffdoet_st(data)                                 (0x00000010&((data)<<4))
#define DDC2_DDC_SFSR_ffdifu_st(data)                                 (0x00000008&((data)<<3))
#define DDC2_DDC_SFSR_ffdine_st(data)                                 (0x00000004&((data)<<2))
#define DDC2_DDC_SFSR_get_ffdouf_st(data)                             ((0x00000080&(data))>>7)
#define DDC2_DDC_SFSR_get_ffdiof_st(data)                             ((0x00000040&(data))>>6)
#define DDC2_DDC_SFSR_get_ffdonf_st(data)                             ((0x00000020&(data))>>5)
#define DDC2_DDC_SFSR_get_ffdoet_st(data)                             ((0x00000010&(data))>>4)
#define DDC2_DDC_SFSR_get_ffdifu_st(data)                             ((0x00000008&(data))>>3)
#define DDC2_DDC_SFSR_get_ffdine_st(data)                             ((0x00000004&(data))>>2)


#define DDC2_DDC_SFIR                                                 0x60
#define DDC2_DDC_SFIR_reg_addr                                        "0x98037760"
#define DDC2_DDC_SFIR_reg                                             0x98037760
#define DDC2_DDC_SFIR_inst_addr                                       "0x01D8"
#define DDC2_DDC_SFIR_inst                                            0x01D8
#define DDC2_DDC_SFIR_ffdouf_ie_shift                                 (7)
#define DDC2_DDC_SFIR_ffdiof_ie_shift                                 (6)
#define DDC2_DDC_SFIR_ffdonf_ie_shift                                 (5)
#define DDC2_DDC_SFIR_ffdoet_ie_shift                                 (4)
#define DDC2_DDC_SFIR_ffdifu_ie_shift                                 (3)
#define DDC2_DDC_SFIR_ffdine_ie_shift                                 (2)
#define DDC2_DDC_SFIR_cippt_ie_shift                                  (1)
#define DDC2_DDC_SFIR_cispt_ie_shift                                  (0)
#define DDC2_DDC_SFIR_ffdouf_ie_mask                                  (0x00000080)
#define DDC2_DDC_SFIR_ffdiof_ie_mask                                  (0x00000040)
#define DDC2_DDC_SFIR_ffdonf_ie_mask                                  (0x00000020)
#define DDC2_DDC_SFIR_ffdoet_ie_mask                                  (0x00000010)
#define DDC2_DDC_SFIR_ffdifu_ie_mask                                  (0x00000008)
#define DDC2_DDC_SFIR_ffdine_ie_mask                                  (0x00000004)
#define DDC2_DDC_SFIR_cippt_ie_mask                                   (0x00000002)
#define DDC2_DDC_SFIR_cispt_ie_mask                                   (0x00000001)
#define DDC2_DDC_SFIR_ffdouf_ie(data)                                 (0x00000080&((data)<<7))
#define DDC2_DDC_SFIR_ffdiof_ie(data)                                 (0x00000040&((data)<<6))
#define DDC2_DDC_SFIR_ffdonf_ie(data)                                 (0x00000020&((data)<<5))
#define DDC2_DDC_SFIR_ffdoet_ie(data)                                 (0x00000010&((data)<<4))
#define DDC2_DDC_SFIR_ffdifu_ie(data)                                 (0x00000008&((data)<<3))
#define DDC2_DDC_SFIR_ffdine_ie(data)                                 (0x00000004&((data)<<2))
#define DDC2_DDC_SFIR_cippt_ie(data)                                  (0x00000002&((data)<<1))
#define DDC2_DDC_SFIR_cispt_ie(data)                                  (0x00000001&(data))
#define DDC2_DDC_SFIR_get_ffdouf_ie(data)                             ((0x00000080&(data))>>7)
#define DDC2_DDC_SFIR_get_ffdiof_ie(data)                             ((0x00000040&(data))>>6)
#define DDC2_DDC_SFIR_get_ffdonf_ie(data)                             ((0x00000020&(data))>>5)
#define DDC2_DDC_SFIR_get_ffdoet_ie(data)                             ((0x00000010&(data))>>4)
#define DDC2_DDC_SFIR_get_ffdifu_ie(data)                             ((0x00000008&(data))>>3)
#define DDC2_DDC_SFIR_get_ffdine_ie(data)                             ((0x00000004&(data))>>2)
#define DDC2_DDC_SFIR_get_cippt_ie(data)                              ((0x00000002&(data))>>1)
#define DDC2_DDC_SFIR_get_cispt_ie(data)                              (0x00000001&(data))


#define DDC2_DDC_FSMS                                                 0x64
#define DDC2_DDC_FSMS_reg_addr                                        "0x98037764"
#define DDC2_DDC_FSMS_reg                                             0x98037764
#define DDC2_DDC_FSMS_inst_addr                                       "0x01D9"
#define DDC2_DDC_FSMS_inst                                            0x01D9
#define DDC2_DDC_FSMS_cmdfsm_st_shift                                 (0)
#define DDC2_DDC_FSMS_cmdfsm_st_mask                                  (0x000000FF)
#define DDC2_DDC_FSMS_cmdfsm_st(data)                                 (0x000000FF&(data))
#define DDC2_DDC_FSMS_get_cmdfsm_st(data)                             (0x000000FF&(data))


#define DDC2_DDC_DUMMY                                                0x68
#define DDC2_DDC_DUMMY_reg_addr                                       "0x98037768"
#define DDC2_DDC_DUMMY_reg                                            0x98037768
#define DDC2_DDC_DUMMY_inst_addr                                      "0x01DA"
#define DDC2_DDC_DUMMY_inst                                           0x01DA
#define DDC2_DDC_DUMMY_dummy98037768_7_0_shift                        (0)
#define DDC2_DDC_DUMMY_dummy98037768_7_0_mask                         (0x000000FF)
#define DDC2_DDC_DUMMY_dummy98037768_7_0(data)                        (0x000000FF&(data))
#define DDC2_DDC_DUMMY_get_dummy98037768_7_0(data)                    (0x000000FF&(data))


#define DDC2_DDC_EDID_SRAM_READ_IRQ_EN                                0x70
#define DDC2_DDC_EDID_SRAM_READ_IRQ_EN_reg_addr                       "0x98037770"
#define DDC2_DDC_EDID_SRAM_READ_IRQ_EN_reg                            0x98037770
#define DDC2_DDC_EDID_SRAM_READ_IRQ_EN_inst_addr                      "0x01DC"
#define DDC2_DDC_EDID_SRAM_READ_IRQ_EN_inst                           0x01DC
#define DDC2_DDC_EDID_SRAM_READ_IRQ_EN_start_irq_en_shift             (1)
#define DDC2_DDC_EDID_SRAM_READ_IRQ_EN_stop_irq_en_shift              (0)
#define DDC2_DDC_EDID_SRAM_READ_IRQ_EN_start_irq_en_mask              (0x00000002)
#define DDC2_DDC_EDID_SRAM_READ_IRQ_EN_stop_irq_en_mask               (0x00000001)
#define DDC2_DDC_EDID_SRAM_READ_IRQ_EN_start_irq_en(data)             (0x00000002&((data)<<1))
#define DDC2_DDC_EDID_SRAM_READ_IRQ_EN_stop_irq_en(data)              (0x00000001&(data))
#define DDC2_DDC_EDID_SRAM_READ_IRQ_EN_get_start_irq_en(data)         ((0x00000002&(data))>>1)
#define DDC2_DDC_EDID_SRAM_READ_IRQ_EN_get_stop_irq_en(data)          (0x00000001&(data))


#define DDC2_DDC_EDID_SRAM_READ_AUX                                   0x74
#define DDC2_DDC_EDID_SRAM_READ_AUX_reg_addr                          "0x98037774"
#define DDC2_DDC_EDID_SRAM_READ_AUX_reg                               0x98037774
#define DDC2_DDC_EDID_SRAM_READ_AUX_inst_addr                         "0x01DD"
#define DDC2_DDC_EDID_SRAM_READ_AUX_inst                              0x01DD
#define DDC2_DDC_EDID_SRAM_READ_AUX_start_shift                       (1)
#define DDC2_DDC_EDID_SRAM_READ_AUX_stop_shift                        (0)
#define DDC2_DDC_EDID_SRAM_READ_AUX_start_mask                        (0x00000002)
#define DDC2_DDC_EDID_SRAM_READ_AUX_stop_mask                         (0x00000001)
#define DDC2_DDC_EDID_SRAM_READ_AUX_start(data)                       (0x00000002&((data)<<1))
#define DDC2_DDC_EDID_SRAM_READ_AUX_stop(data)                        (0x00000001&(data))
#define DDC2_DDC_EDID_SRAM_READ_AUX_get_start(data)                   ((0x00000002&(data))>>1)
#define DDC2_DDC_EDID_SRAM_READ_AUX_get_stop(data)                    (0x00000001&(data))


#define DDC2_DDC_BIST_MODE                                            0x78
#define DDC2_DDC_BIST_MODE_reg_addr                                   "0x98037778"
#define DDC2_DDC_BIST_MODE_reg                                        0x98037778
#define DDC2_DDC_BIST_MODE_inst_addr                                  "0x01DE"
#define DDC2_DDC_BIST_MODE_inst                                       0x01DE
#define DDC2_DDC_BIST_MODE_ddc_bist_mode_shift                        (0)
#define DDC2_DDC_BIST_MODE_ddc_bist_mode_mask                         (0x00000001)
#define DDC2_DDC_BIST_MODE_ddc_bist_mode(data)                        (0x00000001&(data))
#define DDC2_DDC_BIST_MODE_get_ddc_bist_mode(data)                    (0x00000001&(data))


#define DDC2_DDC_BIST_DONE                                            0x7c
#define DDC2_DDC_BIST_DONE_reg_addr                                   "0x9803777c"
#define DDC2_DDC_BIST_DONE_reg                                        0x9803777c
#define DDC2_DDC_BIST_DONE_inst_addr                                  "0x01DF"
#define DDC2_DDC_BIST_DONE_inst                                       0x01DF
#define DDC2_DDC_BIST_DONE_ddc_bist_done_shift                        (0)
#define DDC2_DDC_BIST_DONE_ddc_bist_done_mask                         (0x00000001)
#define DDC2_DDC_BIST_DONE_ddc_bist_done(data)                        (0x00000001&(data))
#define DDC2_DDC_BIST_DONE_get_ddc_bist_done(data)                    (0x00000001&(data))


#define DDC2_DDC_BIST_FAIL                                            0x80
#define DDC2_DDC_BIST_FAIL_reg_addr                                   "0x98037780"
#define DDC2_DDC_BIST_FAIL_reg                                        0x98037780
#define DDC2_DDC_BIST_FAIL_inst_addr                                  "0x01E0"
#define DDC2_DDC_BIST_FAIL_inst                                       0x01E0
#define DDC2_DDC_BIST_FAIL_ddc_bist_fail_shift                        (0)
#define DDC2_DDC_BIST_FAIL_ddc_bist_fail_mask                         (0x00000001)
#define DDC2_DDC_BIST_FAIL_ddc_bist_fail(data)                        (0x00000001&(data))
#define DDC2_DDC_BIST_FAIL_get_ddc_bist_fail(data)                    (0x00000001&(data))


#define DDC2_DDC_DRF_MODE                                             0x84
#define DDC2_DDC_DRF_MODE_reg_addr                                    "0x98037784"
#define DDC2_DDC_DRF_MODE_reg                                         0x98037784
#define DDC2_DDC_DRF_MODE_inst_addr                                   "0x01E1"
#define DDC2_DDC_DRF_MODE_inst                                        0x01E1
#define DDC2_DDC_DRF_MODE_ddc_drf_mode_shift                          (0)
#define DDC2_DDC_DRF_MODE_ddc_drf_mode_mask                           (0x00000001)
#define DDC2_DDC_DRF_MODE_ddc_drf_mode(data)                          (0x00000001&(data))
#define DDC2_DDC_DRF_MODE_get_ddc_drf_mode(data)                      (0x00000001&(data))


#define DDC2_DDC_DRF_RESUME                                           0x88
#define DDC2_DDC_DRF_RESUME_reg_addr                                  "0x98037788"
#define DDC2_DDC_DRF_RESUME_reg                                       0x98037788
#define DDC2_DDC_DRF_RESUME_inst_addr                                 "0x01E2"
#define DDC2_DDC_DRF_RESUME_inst                                      0x01E2
#define DDC2_DDC_DRF_RESUME_ddc_drf_resume_shift                      (0)
#define DDC2_DDC_DRF_RESUME_ddc_drf_resume_mask                       (0x00000001)
#define DDC2_DDC_DRF_RESUME_ddc_drf_resume(data)                      (0x00000001&(data))
#define DDC2_DDC_DRF_RESUME_get_ddc_drf_resume(data)                  (0x00000001&(data))


#define DDC2_DDC_DRF_DONE                                             0x8c
#define DDC2_DDC_DRF_DONE_reg_addr                                    "0x9803778c"
#define DDC2_DDC_DRF_DONE_reg                                         0x9803778c
#define DDC2_DDC_DRF_DONE_inst_addr                                   "0x01E3"
#define DDC2_DDC_DRF_DONE_inst                                        0x01E3
#define DDC2_DDC_DRF_DONE_ddc_drf_done_shift                          (0)
#define DDC2_DDC_DRF_DONE_ddc_drf_done_mask                           (0x00000001)
#define DDC2_DDC_DRF_DONE_ddc_drf_done(data)                          (0x00000001&(data))
#define DDC2_DDC_DRF_DONE_get_ddc_drf_done(data)                      (0x00000001&(data))


#define DDC2_DDC_DRF_PAUSE                                            0x90
#define DDC2_DDC_DRF_PAUSE_reg_addr                                   "0x98037790"
#define DDC2_DDC_DRF_PAUSE_reg                                        0x98037790
#define DDC2_DDC_DRF_PAUSE_inst_addr                                  "0x01E4"
#define DDC2_DDC_DRF_PAUSE_inst                                       0x01E4
#define DDC2_DDC_DRF_PAUSE_ddc_drf_pause_shift                        (0)
#define DDC2_DDC_DRF_PAUSE_ddc_drf_pause_mask                         (0x00000001)
#define DDC2_DDC_DRF_PAUSE_ddc_drf_pause(data)                        (0x00000001&(data))
#define DDC2_DDC_DRF_PAUSE_get_ddc_drf_pause(data)                    (0x00000001&(data))


#define DDC2_DDC_DRF_FAIL                                             0x94
#define DDC2_DDC_DRF_FAIL_reg_addr                                    "0x98037794"
#define DDC2_DDC_DRF_FAIL_reg                                         0x98037794
#define DDC2_DDC_DRF_FAIL_inst_addr                                   "0x01E5"
#define DDC2_DDC_DRF_FAIL_inst                                        0x01E5
#define DDC2_DDC_DRF_FAIL_ddc_drf_fail_shift                          (0)
#define DDC2_DDC_DRF_FAIL_ddc_drf_fail_mask                           (0x00000001)
#define DDC2_DDC_DRF_FAIL_ddc_drf_fail(data)                          (0x00000001&(data))
#define DDC2_DDC_DRF_FAIL_get_ddc_drf_fail(data)                      (0x00000001&(data))
#endif//_DDC_REG_H_INCLUDED_