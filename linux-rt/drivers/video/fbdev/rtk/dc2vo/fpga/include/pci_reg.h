/**************************************************************
// Spec Version                  : 0.0.3
// Parser Version                : MAR_Parser_1.0
// CModelGen Version             : 1.0 2006.04.18
// Naming Rule                   : Module_Register_Name
// Firmware Header Generate Date : 2007/11/25
***************************************************************/


#ifndef _PCI_REG_H_INCLUDED_
#define _PCI_REG_H_INCLUDED_
#ifdef  _PCI_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     slave_on_16_00:1;
unsigned int     reserved_1:15;
unsigned int     bridge_mode_0_00:1;
}DVR_GNR_MODE;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     loopback_cmd_22_04:1;
unsigned int     loopback_en_21_04:1;
unsigned int     neg_sample_en_20_04:1;
unsigned int     clk_run_en_19_04:1;
unsigned int     pci_inta_en_18_04:1;
unsigned int     intp_dev_en_17_04:1;
unsigned int     config_en_16_04:1;
unsigned int     reserved_1:6;
unsigned int     slave_unlimit_rd_9_04:1;
unsigned int     slave_unlimit_wr_8_04:1;
unsigned int     reserved_2:1;
unsigned int     master_read_size_6to4_04:3;
unsigned int     reserved_3:2;
unsigned int     master_unlimit_rd_1_04:1;
unsigned int     master_unlimit_wr_0_04:1;
}DVR_GNR_EN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     intp_rdir_7_08:1;
unsigned int     intp_wdir_6_08:1;
unsigned int     intp_mst_5_08:1;
unsigned int     intp_slv_4_08:1;
unsigned int     intp_pci_3_08:1;
unsigned int     intp_cfg_2_08:1;
unsigned int     intp_mio_1_08:1;
unsigned int     intp_dma_0_08:1;
}DVR_GNR_INT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     go_ct_0_0c:1;
}DVR_CFG_CT;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     type_en_8_10:1;
unsigned int     byte_cnt_7to4_10:4;
unsigned int     intp_en_3_10:1;
unsigned int     error_en_2_10:1;
unsigned int     byte_en_1_10:1;
unsigned int     wrrd_en_0_10:1;
}DVR_CFG_EN;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     error_st_1_14:1;
unsigned int     done_st_0_14:1;
}DVR_CFG_ST;

typedef struct 
{
unsigned int     space_addr_31to0_18:32;
}DVR_CFG_ADDR;

typedef struct 
{
unsigned int     space_wdata_31to0_1c:32;
}DVR_CFG_WDATA;

typedef struct 
{
unsigned int     space_rdata_31to0_20:32;
}DVR_CFG_RDATA;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     go_ct_0_24:1;
}DVR_MIO_CT;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     error_st_1_28:1;
unsigned int     done_st_0_28:1;
}DVR_MIO_ST;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     byte_cnt_8to5_2c:4;
unsigned int     intp_en_4_2c:1;
unsigned int     error_en_3_2c:1;
unsigned int     byte_en_2_2c:1;
unsigned int     wrrd_en_1_2c:1;
unsigned int     type_en_0_2c:1;
}DVR_MIO_EN;

typedef struct 
{
unsigned int     pci_addr_31to0_30:32;
}DVR_MIO_ADDR;

typedef struct 
{
unsigned int     pci_wdata_31to0_34:32;
}DVR_MIO_WDATA;

typedef struct 
{
unsigned int     pci_rdata_31to0_38:32;
}DVR_MIO_RDATA;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     go_ct_0_3c:1;
}DVR_DMA_CT;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     idle_st_5_40:1;
unsigned int     sin_dma_done_st_4_40:1;
unsigned int     desc_dma_done_st_3_40:1;
unsigned int     desc_empty_st_2_40:1;
unsigned int     pci_error_st_1_40:1;
unsigned int     desc_error_st_0_40:1;
}DVR_DMA_ST;

typedef struct 
{
unsigned int     intv_cnt_31to16_44:16;
unsigned int     reserved_0:4;
unsigned int     intp_done_en_11_44:1;
unsigned int     intp_empty_en_10_44:1;
unsigned int     intp_pci_error_en_9_44:1;
unsigned int     intp_desc_error_en_8_44:1;
unsigned int     reserved_1:4;
unsigned int     intv_en_3_44:1;
unsigned int     go_en_2_44:1;
unsigned int     mode_en_1_44:1;
unsigned int     desc_en_0_44:1;
}DVR_DMA_EN;

typedef struct 
{
unsigned int     addr_31to0_48:32;
}DVR_DMA_PCI;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     addr_27to0_4c:28;
}DVR_DMA_DDR;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     byte_cnt_23to0_50:24;
}DVR_DMA_CNT;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     base_ptr_27to0_54:28;
}DVR_DMA_DES0;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     limit_ptr_27to0_58:28;
}DVR_DMA_DES1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     wr_ptr_27to0_5c:28;
}DVR_DMA_DES2;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     rd_ptr_27to0_60:28;
}DVR_DMA_DES3;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     stop_ct_8_64:1;
unsigned int     reserved_1:7;
unsigned int     idle_st_0_64:1;
}DVR_SOFT_RST;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pci_master_busy_st_7_68:1;
unsigned int     pci_slave_busy_st_6_68:1;
unsigned int     mio_cfg_busy_st_5_68:1;
unsigned int     dma_busy_st_4_68:1;
unsigned int     reserved_1:2;
unsigned int     pci_clk_lock_st_1_68:1;
unsigned int     pci_clk_st_0_68:1;
}DVR_CLK_ST;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     pci_int_req_8_6c:1;
unsigned int     reserved_1:3;
unsigned int     clk_run_req_4_6c:1;
unsigned int     reserved_2:3;
unsigned int     pci_clk_lock_en_0_6c:1;
}DVR_SPC_CT;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     pci_int_st_16_70:1;
unsigned int     reserved_1:15;
unsigned int     clk_run_st_0_70:1;
}DVR_SPC_ST;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     dbg_sel1:6;
unsigned int     dbg_sel0:6;
unsigned int     dbg_en:1;
}DVR_DBG;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     rerror_st_1_78:1;
unsigned int     werror_st_0_78:1;
}DVR_DIR_ST;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     error_ack_read_1_7c:1;
unsigned int     intp_en_0_7c:1;
}DVR_DIR_EN;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     dev_ddr_done_st_0_80:1;
}DVR_DEV_ST;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     dev_start_0_84:1;
}DVR_DEV_CT;

typedef struct 
{
unsigned int     dev_ddr_addr_31to0_88:32;
}DVR_DEV_DDR;

typedef struct 
{
unsigned int     dev_pci_addr_31to0_8c:32;
}DVR_DEV_PCI;

typedef struct 
{
unsigned int     dev_ddr_cnt_31to0_90:32;
}DVR_DEV_CNT;

typedef struct 
{
unsigned int     test_reg:32;
}DVR_TMP0_REG;

typedef struct 
{
unsigned int     test_reg:32;
}DVR_TMP1_REG;

typedef struct 
{
unsigned int     reg1:16;
unsigned int     reg0:16;
}DVR_SCTCH;

typedef struct 
{
unsigned int     reg1_16to31_00:16;
unsigned int     reg0_0to15_00:16;
}PCI_SCTCH;

typedef struct 
{
unsigned int     retry_cnt_0to15_04:16;
unsigned int     reserved_0:15;
unsigned int     retry_cnt_en_0_04:1;
}PCI_GNR_EN1;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     master_rd_burst_25to26_08:2;
unsigned int     master_wr_inv_24_08:1;
unsigned int     reserved_1:1;
unsigned int     spc_cyc_en_22_08:1;
unsigned int     retry_int_en_21_08:1;
unsigned int     mon_int_en_20_08:1;
unsigned int     pme_int_en_19_08:1;
unsigned int     inta_int_en_18_08:1;
unsigned int     serr_int_en_17_08:1;
unsigned int     perr_int_en_16_08:1;
unsigned int     reserved_2:1;
unsigned int     lat_timer_en_14_08:1;
unsigned int     pci_mon_en_13_08:1;
unsigned int     park_dev_12o11_08:2;
unsigned int     bus_park_en_10_08:1;
unsigned int     slave_b2b_en_9_08:1;
unsigned int     66mhz_en_8_08:1;
unsigned int     reserved_3:1;
unsigned int     xbus_ba_en_6_08:1;
unsigned int     sbus_tran_en_5_08:1;
unsigned int     sbus_ba_en_4_08:1;
unsigned int     dbus_tran_en_3_08:1;
unsigned int     dbus_ba_en_2_08:1;
unsigned int     rbus_tran_en_1_08:1;
unsigned int     rbus_ba_en_0_08:1;
}PCI_GNR_EN2;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     spc_cyc_msn_17to16_0c:2;
unsigned int     reserved_1:9;
unsigned int     spc_cyc_erro_6_0c:1;
unsigned int     retry_error_5_0c:1;
unsigned int     mon_error_4_0c:1;
unsigned int     serr_error_3_0c:1;
unsigned int     perr_error_2_0c:1;
unsigned int     slave_error_1_0c:1;
unsigned int     master_error_0_0c:1;
}PCI_GNR_ST;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     intp_spc_cyc_6_10:1;
unsigned int     intp_retry_5_10:1;
unsigned int     intp_mon_4_10:1;
unsigned int     intp_pme_3_10:1;
unsigned int     intp_genr_2_10:1;
unsigned int     intp_serr_1_10:1;
unsigned int     intp_perr_0_10:1;
}PCI_GNR_INT;

typedef struct 
{
unsigned int     rbus_mask_31to28_14:4;
unsigned int     rbus_mask_27to8_14:20;
unsigned int     reserved_0:8;
}PCI_MASK0;

typedef struct 
{
unsigned int     rbus_transl_31to8_18:24;
unsigned int     reserved_0:8;
}PCI_TRANSL0;

typedef struct 
{
unsigned int     dbus_mask_31to28_1c:4;
unsigned int     dbus_mask_27to8_1c:20;
unsigned int     reserved_0:8;
}PCI_MASK1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     dbus_transl_27to8_20:20;
unsigned int     reserved_1:8;
}PCI_TRANSL1;

typedef struct 
{
unsigned int     sbus_mask_31to28_24:4;
unsigned int     sbus_mask_27to8_24:20;
unsigned int     reserved_0:8;
}PCI_MASK2;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     sbus_transl_27to8_28:20;
unsigned int     reserved_1:8;
}PCI_TRANSL2;

typedef struct 
{
unsigned int     addr_error_31to0_2c:32;
}PCI_MST_ERR0;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     cmd_error_3to0_30:4;
}PCI_MST_ERR1;

typedef struct 
{
unsigned int     addr_error_31to0_34:32;
}PCI_SLV_ERR0;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     cmd_error_3to0_38:4;
}PCI_SLV_ERR1;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     error_clear_16_40:1;
unsigned int     reserved_1:1;
unsigned int     erro_msn_14to13_40:2;
unsigned int     pci_stop_12_3c:1;
unsigned int     pci_trdy_11_3c:1;
unsigned int     pci_devsel_10_3c:1;
unsigned int     pci_irdy_9_3c:1;
unsigned int     pci_frame_8_3c:1;
unsigned int     reserved_2:8;
}PCI_MON_ST;

typedef struct 
{
unsigned int     test_reg:32;
}PCI_TMP_REG;

typedef struct 
{
unsigned int     dev_id:16;
unsigned int     ven_id:16;
}CFG_00H;

typedef struct 
{
unsigned int     detec_par_error:1;
unsigned int     signal_sys_error:1;
unsigned int     rec_master_abort:1;
unsigned int     rec_target_abort:1;
unsigned int     sig_tar_abort:1;
unsigned int     devsel_timer:2;
unsigned int     master_par_error:1;
unsigned int     fast_b2b_cap:1;
unsigned int     reserved_0:1;
unsigned int     a66mhz:1;
unsigned int     capability_list:1;
unsigned int     int_status:1;
unsigned int     reserved_1:8;
unsigned int     interrupt_disable:1;
unsigned int     fast_b2b:1;
unsigned int     serr_enable:1;
unsigned int     reserved_2:1;
unsigned int     parity_error_resp:1;
unsigned int     reserved_3:1;
unsigned int     mwie:1;
unsigned int     reserved_4:1;
unsigned int     bus_master:1;
unsigned int     mm_space:1;
unsigned int     io_space:1;
}CFG_04H;

typedef struct 
{
unsigned int     class_code:24;
unsigned int     Rev_id:8;
}CFG_08H;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     reserved_1:8;
unsigned int     latency_timer:8;
unsigned int     cacheline_size:8;
}CFG_0CH;

typedef struct 
{
unsigned int     reg_ba:27;
unsigned int     reserved_0:4;
unsigned int     space_bit:1;
}CFG_10H;

typedef struct 
{
unsigned int     dbus_ba:24;
unsigned int     reserved_0:7;
unsigned int     space_bit:1;
}CFG_14H;

typedef struct 
{
unsigned int     rbus_ba:24;
unsigned int     reserved_0:7;
unsigned int     space_bit:1;
}CFG_18H;

typedef struct 
{
unsigned int     sbus_ba:24;
unsigned int     reserved_0:7;
unsigned int     space_bit:1;
}CFG_1CH;

typedef struct 
{
unsigned int     sub_id:16;
unsigned int     sub_ven_id:16;
}CFG_2CH;

typedef struct 
{
unsigned int     max_Lat:8;
unsigned int     min_gnt:8;
unsigned int     interrupt_pin:8;
unsigned int     interrupt_line:8;
}CFG_3CH;

#endif

#define DVR_GNR_MODE                                                                 0x18017000
#define DVR_GNR_MODE_reg_addr                                                        "0xB8017000"
#define DVR_GNR_MODE_reg                                                             0xB8017000
#define DVR_GNR_MODE_inst_adr                                                        "0x0000"
#define DVR_GNR_MODE_inst                                                            0x0000
#define DVR_GNR_MODE_slave_on_16_00_shift                                            (16)
#define DVR_GNR_MODE_slave_on_16_00_mask                                             (0x00010000)
#define DVR_GNR_MODE_slave_on_16_00(data)                                            (0x00010000&((data)<<16))
#define DVR_GNR_MODE_slave_on_16_00_src(data)                                        ((0x00010000&(data))>>16)
#define DVR_GNR_MODE_bridge_mode_0_00_shift                                          (0)
#define DVR_GNR_MODE_bridge_mode_0_00_mask                                           (0x00000001)
#define DVR_GNR_MODE_bridge_mode_0_00(data)                                          (0x00000001&((data)<<0))
#define DVR_GNR_MODE_bridge_mode_0_00_src(data)                                      ((0x00000001&(data))>>0)


#define DVR_GNR_EN                                                                   0x18017004
#define DVR_GNR_EN_reg_addr                                                          "0xB8017004"
#define DVR_GNR_EN_reg                                                               0xB8017004
#define DVR_GNR_EN_inst_adr                                                          "0x0001"
#define DVR_GNR_EN_inst                                                              0x0001
#define DVR_GNR_EN_loopback_cmd_22_04_shift                                          (22)
#define DVR_GNR_EN_loopback_cmd_22_04_mask                                           (0x00400000)
#define DVR_GNR_EN_loopback_cmd_22_04(data)                                          (0x00400000&((data)<<22))
#define DVR_GNR_EN_loopback_cmd_22_04_src(data)                                      ((0x00400000&(data))>>22)
#define DVR_GNR_EN_loopback_en_21_04_shift                                           (21)
#define DVR_GNR_EN_loopback_en_21_04_mask                                            (0x00200000)
#define DVR_GNR_EN_loopback_en_21_04(data)                                           (0x00200000&((data)<<21))
#define DVR_GNR_EN_loopback_en_21_04_src(data)                                       ((0x00200000&(data))>>21)
#define DVR_GNR_EN_neg_sample_en_20_04_shift                                         (20)
#define DVR_GNR_EN_neg_sample_en_20_04_mask                                          (0x00100000)
#define DVR_GNR_EN_neg_sample_en_20_04(data)                                         (0x00100000&((data)<<20))
#define DVR_GNR_EN_neg_sample_en_20_04_src(data)                                     ((0x00100000&(data))>>20)
#define DVR_GNR_EN_clk_run_en_19_04_shift                                            (19)
#define DVR_GNR_EN_clk_run_en_19_04_mask                                             (0x00080000)
#define DVR_GNR_EN_clk_run_en_19_04(data)                                            (0x00080000&((data)<<19))
#define DVR_GNR_EN_clk_run_en_19_04_src(data)                                        ((0x00080000&(data))>>19)
#define DVR_GNR_EN_pci_inta_en_18_04_shift                                           (18)
#define DVR_GNR_EN_pci_inta_en_18_04_mask                                            (0x00040000)
#define DVR_GNR_EN_pci_inta_en_18_04(data)                                           (0x00040000&((data)<<18))
#define DVR_GNR_EN_pci_inta_en_18_04_src(data)                                       ((0x00040000&(data))>>18)
#define DVR_GNR_EN_intp_dev_en_17_04_shift                                           (17)
#define DVR_GNR_EN_intp_dev_en_17_04_mask                                            (0x00020000)
#define DVR_GNR_EN_intp_dev_en_17_04(data)                                           (0x00020000&((data)<<17))
#define DVR_GNR_EN_intp_dev_en_17_04_src(data)                                       ((0x00020000&(data))>>17)
#define DVR_GNR_EN_config_en_16_04_shift                                             (16)
#define DVR_GNR_EN_config_en_16_04_mask                                              (0x00010000)
#define DVR_GNR_EN_config_en_16_04(data)                                             (0x00010000&((data)<<16))
#define DVR_GNR_EN_config_en_16_04_src(data)                                         ((0x00010000&(data))>>16)
#define DVR_GNR_EN_slave_unlimit_rd_9_04_shift                                       (9)
#define DVR_GNR_EN_slave_unlimit_rd_9_04_mask                                        (0x00000200)
#define DVR_GNR_EN_slave_unlimit_rd_9_04(data)                                       (0x00000200&((data)<<9))
#define DVR_GNR_EN_slave_unlimit_rd_9_04_src(data)                                   ((0x00000200&(data))>>9)
#define DVR_GNR_EN_slave_unlimit_wr_8_04_shift                                       (8)
#define DVR_GNR_EN_slave_unlimit_wr_8_04_mask                                        (0x00000100)
#define DVR_GNR_EN_slave_unlimit_wr_8_04(data)                                       (0x00000100&((data)<<8))
#define DVR_GNR_EN_slave_unlimit_wr_8_04_src(data)                                   ((0x00000100&(data))>>8)
#define DVR_GNR_EN_master_read_size_6to4_04_shift                                    (4)
#define DVR_GNR_EN_master_read_size_6to4_04_mask                                     (0x00000070)
#define DVR_GNR_EN_master_read_size_6to4_04(data)                                    (0x00000070&((data)<<4))
#define DVR_GNR_EN_master_read_size_6to4_04_src(data)                                ((0x00000070&(data))>>4)
#define DVR_GNR_EN_master_unlimit_rd_1_04_shift                                      (1)
#define DVR_GNR_EN_master_unlimit_rd_1_04_mask                                       (0x00000002)
#define DVR_GNR_EN_master_unlimit_rd_1_04(data)                                      (0x00000002&((data)<<1))
#define DVR_GNR_EN_master_unlimit_rd_1_04_src(data)                                  ((0x00000002&(data))>>1)
#define DVR_GNR_EN_master_unlimit_wr_0_04_shift                                      (0)
#define DVR_GNR_EN_master_unlimit_wr_0_04_mask                                       (0x00000001)
#define DVR_GNR_EN_master_unlimit_wr_0_04(data)                                      (0x00000001&((data)<<0))
#define DVR_GNR_EN_master_unlimit_wr_0_04_src(data)                                  ((0x00000001&(data))>>0)


#define DVR_GNR_INT                                                                  0x18017008
#define DVR_GNR_INT_reg_addr                                                         "0xB8017008"
#define DVR_GNR_INT_reg                                                              0xB8017008
#define DVR_GNR_INT_inst_adr                                                         "0x0002"
#define DVR_GNR_INT_inst                                                             0x0002
#define DVR_GNR_INT_intp_rdir_7_08_shift                                             (7)
#define DVR_GNR_INT_intp_rdir_7_08_mask                                              (0x00000080)
#define DVR_GNR_INT_intp_rdir_7_08(data)                                             (0x00000080&((data)<<7))
#define DVR_GNR_INT_intp_rdir_7_08_src(data)                                         ((0x00000080&(data))>>7)
#define DVR_GNR_INT_intp_wdir_6_08_shift                                             (6)
#define DVR_GNR_INT_intp_wdir_6_08_mask                                              (0x00000040)
#define DVR_GNR_INT_intp_wdir_6_08(data)                                             (0x00000040&((data)<<6))
#define DVR_GNR_INT_intp_wdir_6_08_src(data)                                         ((0x00000040&(data))>>6)
#define DVR_GNR_INT_intp_mst_5_08_shift                                              (5)
#define DVR_GNR_INT_intp_mst_5_08_mask                                               (0x00000020)
#define DVR_GNR_INT_intp_mst_5_08(data)                                              (0x00000020&((data)<<5))
#define DVR_GNR_INT_intp_mst_5_08_src(data)                                          ((0x00000020&(data))>>5)
#define DVR_GNR_INT_intp_slv_4_08_shift                                              (4)
#define DVR_GNR_INT_intp_slv_4_08_mask                                               (0x00000010)
#define DVR_GNR_INT_intp_slv_4_08(data)                                              (0x00000010&((data)<<4))
#define DVR_GNR_INT_intp_slv_4_08_src(data)                                          ((0x00000010&(data))>>4)
#define DVR_GNR_INT_intp_pci_3_08_shift                                              (3)
#define DVR_GNR_INT_intp_pci_3_08_mask                                               (0x00000008)
#define DVR_GNR_INT_intp_pci_3_08(data)                                              (0x00000008&((data)<<3))
#define DVR_GNR_INT_intp_pci_3_08_src(data)                                          ((0x00000008&(data))>>3)
#define DVR_GNR_INT_intp_cfg_2_08_shift                                              (2)
#define DVR_GNR_INT_intp_cfg_2_08_mask                                               (0x00000004)
#define DVR_GNR_INT_intp_cfg_2_08(data)                                              (0x00000004&((data)<<2))
#define DVR_GNR_INT_intp_cfg_2_08_src(data)                                          ((0x00000004&(data))>>2)
#define DVR_GNR_INT_intp_mio_1_08_shift                                              (1)
#define DVR_GNR_INT_intp_mio_1_08_mask                                               (0x00000002)
#define DVR_GNR_INT_intp_mio_1_08(data)                                              (0x00000002&((data)<<1))
#define DVR_GNR_INT_intp_mio_1_08_src(data)                                          ((0x00000002&(data))>>1)
#define DVR_GNR_INT_intp_dma_0_08_shift                                              (0)
#define DVR_GNR_INT_intp_dma_0_08_mask                                               (0x00000001)
#define DVR_GNR_INT_intp_dma_0_08(data)                                              (0x00000001&((data)<<0))
#define DVR_GNR_INT_intp_dma_0_08_src(data)                                          ((0x00000001&(data))>>0)


#define DVR_CFG_CT                                                                   0x1801700C
#define DVR_CFG_CT_reg_addr                                                          "0xB801700C"
#define DVR_CFG_CT_reg                                                               0xB801700C
#define DVR_CFG_CT_inst_adr                                                          "0x0003"
#define DVR_CFG_CT_inst                                                              0x0003
#define DVR_CFG_CT_go_ct_0_0c_shift                                                  (0)
#define DVR_CFG_CT_go_ct_0_0c_mask                                                   (0x00000001)
#define DVR_CFG_CT_go_ct_0_0c(data)                                                  (0x00000001&((data)<<0))
#define DVR_CFG_CT_go_ct_0_0c_src(data)                                              ((0x00000001&(data))>>0)


#define DVR_CFG_EN                                                                   0x18017010
#define DVR_CFG_EN_reg_addr                                                          "0xB8017010"
#define DVR_CFG_EN_reg                                                               0xB8017010
#define DVR_CFG_EN_inst_adr                                                          "0x0004"
#define DVR_CFG_EN_inst                                                              0x0004
#define DVR_CFG_EN_type_en_8_10_shift                                                (8)
#define DVR_CFG_EN_type_en_8_10_mask                                                 (0x00000100)
#define DVR_CFG_EN_type_en_8_10(data)                                                (0x00000100&((data)<<8))
#define DVR_CFG_EN_type_en_8_10_src(data)                                            ((0x00000100&(data))>>8)
#define DVR_CFG_EN_byte_cnt_7to4_10_shift                                            (4)
#define DVR_CFG_EN_byte_cnt_7to4_10_mask                                             (0x000000F0)
#define DVR_CFG_EN_byte_cnt_7to4_10(data)                                            (0x000000F0&((data)<<4))
#define DVR_CFG_EN_byte_cnt_7to4_10_src(data)                                        ((0x000000F0&(data))>>4)
#define DVR_CFG_EN_intp_en_3_10_shift                                                (3)
#define DVR_CFG_EN_intp_en_3_10_mask                                                 (0x00000008)
#define DVR_CFG_EN_intp_en_3_10(data)                                                (0x00000008&((data)<<3))
#define DVR_CFG_EN_intp_en_3_10_src(data)                                            ((0x00000008&(data))>>3)
#define DVR_CFG_EN_error_en_2_10_shift                                               (2)
#define DVR_CFG_EN_error_en_2_10_mask                                                (0x00000004)
#define DVR_CFG_EN_error_en_2_10(data)                                               (0x00000004&((data)<<2))
#define DVR_CFG_EN_error_en_2_10_src(data)                                           ((0x00000004&(data))>>2)
#define DVR_CFG_EN_byte_en_1_10_shift                                                (1)
#define DVR_CFG_EN_byte_en_1_10_mask                                                 (0x00000002)
#define DVR_CFG_EN_byte_en_1_10(data)                                                (0x00000002&((data)<<1))
#define DVR_CFG_EN_byte_en_1_10_src(data)                                            ((0x00000002&(data))>>1)
#define DVR_CFG_EN_wrrd_en_0_10_shift                                                (0)
#define DVR_CFG_EN_wrrd_en_0_10_mask                                                 (0x00000001)
#define DVR_CFG_EN_wrrd_en_0_10(data)                                                (0x00000001&((data)<<0))
#define DVR_CFG_EN_wrrd_en_0_10_src(data)                                            ((0x00000001&(data))>>0)


#define DVR_CFG_ST                                                                   0x18017014
#define DVR_CFG_ST_reg_addr                                                          "0xB8017014"
#define DVR_CFG_ST_reg                                                               0xB8017014
#define DVR_CFG_ST_inst_adr                                                          "0x0005"
#define DVR_CFG_ST_inst                                                              0x0005
#define DVR_CFG_ST_error_st_1_14_shift                                               (1)
#define DVR_CFG_ST_error_st_1_14_mask                                                (0x00000002)
#define DVR_CFG_ST_error_st_1_14(data)                                               (0x00000002&((data)<<1))
#define DVR_CFG_ST_error_st_1_14_src(data)                                           ((0x00000002&(data))>>1)
#define DVR_CFG_ST_done_st_0_14_shift                                                (0)
#define DVR_CFG_ST_done_st_0_14_mask                                                 (0x00000001)
#define DVR_CFG_ST_done_st_0_14(data)                                                (0x00000001&((data)<<0))
#define DVR_CFG_ST_done_st_0_14_src(data)                                            ((0x00000001&(data))>>0)


#define DVR_CFG_ADDR                                                                 0x18017018
#define DVR_CFG_ADDR_reg_addr                                                        "0xB8017018"
#define DVR_CFG_ADDR_reg                                                             0xB8017018
#define DVR_CFG_ADDR_inst_adr                                                        "0x0006"
#define DVR_CFG_ADDR_inst                                                            0x0006
#define DVR_CFG_ADDR_space_addr_31to0_18_shift                                       (0)
#define DVR_CFG_ADDR_space_addr_31to0_18_mask                                        (0xFFFFFFFF)
#define DVR_CFG_ADDR_space_addr_31to0_18(data)                                       (0xFFFFFFFF&((data)<<0))
#define DVR_CFG_ADDR_space_addr_31to0_18_src(data)                                   ((0xFFFFFFFF&(data))>>0)


#define DVR_CFG_WDATA                                                                0x1801701C
#define DVR_CFG_WDATA_reg_addr                                                       "0xB801701C"
#define DVR_CFG_WDATA_reg                                                            0xB801701C
#define DVR_CFG_WDATA_inst_adr                                                       "0x0007"
#define DVR_CFG_WDATA_inst                                                           0x0007
#define DVR_CFG_WDATA_space_wdata_31to0_1c_shift                                     (0)
#define DVR_CFG_WDATA_space_wdata_31to0_1c_mask                                      (0xFFFFFFFF)
#define DVR_CFG_WDATA_space_wdata_31to0_1c(data)                                     (0xFFFFFFFF&((data)<<0))
#define DVR_CFG_WDATA_space_wdata_31to0_1c_src(data)                                 ((0xFFFFFFFF&(data))>>0)


#define DVR_CFG_RDATA                                                                0x18017020
#define DVR_CFG_RDATA_reg_addr                                                       "0xB8017020"
#define DVR_CFG_RDATA_reg                                                            0xB8017020
#define DVR_CFG_RDATA_inst_adr                                                       "0x0008"
#define DVR_CFG_RDATA_inst                                                           0x0008
#define DVR_CFG_RDATA_space_rdata_31to0_20_shift                                     (0)
#define DVR_CFG_RDATA_space_rdata_31to0_20_mask                                      (0xFFFFFFFF)
#define DVR_CFG_RDATA_space_rdata_31to0_20(data)                                     (0xFFFFFFFF&((data)<<0))
#define DVR_CFG_RDATA_space_rdata_31to0_20_src(data)                                 ((0xFFFFFFFF&(data))>>0)


#define DVR_MIO_CT                                                                   0x18017024
#define DVR_MIO_CT_reg_addr                                                          "0xB8017024"
#define DVR_MIO_CT_reg                                                               0xB8017024
#define DVR_MIO_CT_inst_adr                                                          "0x0009"
#define DVR_MIO_CT_inst                                                              0x0009
#define DVR_MIO_CT_go_ct_0_24_shift                                                  (0)
#define DVR_MIO_CT_go_ct_0_24_mask                                                   (0x00000001)
#define DVR_MIO_CT_go_ct_0_24(data)                                                  (0x00000001&((data)<<0))
#define DVR_MIO_CT_go_ct_0_24_src(data)                                              ((0x00000001&(data))>>0)


#define DVR_MIO_ST                                                                   0x18017028
#define DVR_MIO_ST_reg_addr                                                          "0xB8017028"
#define DVR_MIO_ST_reg                                                               0xB8017028
#define DVR_MIO_ST_inst_adr                                                          "0x000A"
#define DVR_MIO_ST_inst                                                              0x000A
#define DVR_MIO_ST_error_st_1_28_shift                                               (1)
#define DVR_MIO_ST_error_st_1_28_mask                                                (0x00000002)
#define DVR_MIO_ST_error_st_1_28(data)                                               (0x00000002&((data)<<1))
#define DVR_MIO_ST_error_st_1_28_src(data)                                           ((0x00000002&(data))>>1)
#define DVR_MIO_ST_done_st_0_28_shift                                                (0)
#define DVR_MIO_ST_done_st_0_28_mask                                                 (0x00000001)
#define DVR_MIO_ST_done_st_0_28(data)                                                (0x00000001&((data)<<0))
#define DVR_MIO_ST_done_st_0_28_src(data)                                            ((0x00000001&(data))>>0)


#define DVR_MIO_EN                                                                   0x1801702C
#define DVR_MIO_EN_reg_addr                                                          "0xB801702C"
#define DVR_MIO_EN_reg                                                               0xB801702C
#define DVR_MIO_EN_inst_adr                                                          "0x000B"
#define DVR_MIO_EN_inst                                                              0x000B
#define DVR_MIO_EN_byte_cnt_8to5_2c_shift                                            (5)
#define DVR_MIO_EN_byte_cnt_8to5_2c_mask                                             (0x000001E0)
#define DVR_MIO_EN_byte_cnt_8to5_2c(data)                                            (0x000001E0&((data)<<5))
#define DVR_MIO_EN_byte_cnt_8to5_2c_src(data)                                        ((0x000001E0&(data))>>5)
#define DVR_MIO_EN_intp_en_4_2c_shift                                                (4)
#define DVR_MIO_EN_intp_en_4_2c_mask                                                 (0x00000010)
#define DVR_MIO_EN_intp_en_4_2c(data)                                                (0x00000010&((data)<<4))
#define DVR_MIO_EN_intp_en_4_2c_src(data)                                            ((0x00000010&(data))>>4)
#define DVR_MIO_EN_error_en_3_2c_shift                                               (3)
#define DVR_MIO_EN_error_en_3_2c_mask                                                (0x00000008)
#define DVR_MIO_EN_error_en_3_2c(data)                                               (0x00000008&((data)<<3))
#define DVR_MIO_EN_error_en_3_2c_src(data)                                           ((0x00000008&(data))>>3)
#define DVR_MIO_EN_byte_en_2_2c_shift                                                (2)
#define DVR_MIO_EN_byte_en_2_2c_mask                                                 (0x00000004)
#define DVR_MIO_EN_byte_en_2_2c(data)                                                (0x00000004&((data)<<2))
#define DVR_MIO_EN_byte_en_2_2c_src(data)                                            ((0x00000004&(data))>>2)
#define DVR_MIO_EN_wrrd_en_1_2c_shift                                                (1)
#define DVR_MIO_EN_wrrd_en_1_2c_mask                                                 (0x00000002)
#define DVR_MIO_EN_wrrd_en_1_2c(data)                                                (0x00000002&((data)<<1))
#define DVR_MIO_EN_wrrd_en_1_2c_src(data)                                            ((0x00000002&(data))>>1)
#define DVR_MIO_EN_type_en_0_2c_shift                                                (0)
#define DVR_MIO_EN_type_en_0_2c_mask                                                 (0x00000001)
#define DVR_MIO_EN_type_en_0_2c(data)                                                (0x00000001&((data)<<0))
#define DVR_MIO_EN_type_en_0_2c_src(data)                                            ((0x00000001&(data))>>0)


#define DVR_MIO_ADDR                                                                 0x18017030
#define DVR_MIO_ADDR_reg_addr                                                        "0xB8017030"
#define DVR_MIO_ADDR_reg                                                             0xB8017030
#define DVR_MIO_ADDR_inst_adr                                                        "0x000C"
#define DVR_MIO_ADDR_inst                                                            0x000C
#define DVR_MIO_ADDR_pci_addr_31to0_30_shift                                         (0)
#define DVR_MIO_ADDR_pci_addr_31to0_30_mask                                          (0xFFFFFFFF)
#define DVR_MIO_ADDR_pci_addr_31to0_30(data)                                         (0xFFFFFFFF&((data)<<0))
#define DVR_MIO_ADDR_pci_addr_31to0_30_src(data)                                     ((0xFFFFFFFF&(data))>>0)


#define DVR_MIO_WDATA                                                                0x18017034
#define DVR_MIO_WDATA_reg_addr                                                       "0xB8017034"
#define DVR_MIO_WDATA_reg                                                            0xB8017034
#define DVR_MIO_WDATA_inst_adr                                                       "0x000D"
#define DVR_MIO_WDATA_inst                                                           0x000D
#define DVR_MIO_WDATA_pci_wdata_31to0_34_shift                                       (0)
#define DVR_MIO_WDATA_pci_wdata_31to0_34_mask                                        (0xFFFFFFFF)
#define DVR_MIO_WDATA_pci_wdata_31to0_34(data)                                       (0xFFFFFFFF&((data)<<0))
#define DVR_MIO_WDATA_pci_wdata_31to0_34_src(data)                                   ((0xFFFFFFFF&(data))>>0)


#define DVR_MIO_RDATA                                                                0x18017038
#define DVR_MIO_RDATA_reg_addr                                                       "0xB8017038"
#define DVR_MIO_RDATA_reg                                                            0xB8017038
#define DVR_MIO_RDATA_inst_adr                                                       "0x000E"
#define DVR_MIO_RDATA_inst                                                           0x000E
#define DVR_MIO_RDATA_pci_rdata_31to0_38_shift                                       (0)
#define DVR_MIO_RDATA_pci_rdata_31to0_38_mask                                        (0xFFFFFFFF)
#define DVR_MIO_RDATA_pci_rdata_31to0_38(data)                                       (0xFFFFFFFF&((data)<<0))
#define DVR_MIO_RDATA_pci_rdata_31to0_38_src(data)                                   ((0xFFFFFFFF&(data))>>0)


#define DVR_DMA_CT                                                                   0x1801703C
#define DVR_DMA_CT_reg_addr                                                          "0xB801703C"
#define DVR_DMA_CT_reg                                                               0xB801703C
#define DVR_DMA_CT_inst_adr                                                          "0x000F"
#define DVR_DMA_CT_inst                                                              0x000F
#define DVR_DMA_CT_go_ct_0_3c_shift                                                  (0)
#define DVR_DMA_CT_go_ct_0_3c_mask                                                   (0x00000001)
#define DVR_DMA_CT_go_ct_0_3c(data)                                                  (0x00000001&((data)<<0))
#define DVR_DMA_CT_go_ct_0_3c_src(data)                                              ((0x00000001&(data))>>0)


#define DVR_DMA_ST                                                                   0x18017040
#define DVR_DMA_ST_reg_addr                                                          "0xB8017040"
#define DVR_DMA_ST_reg                                                               0xB8017040
#define DVR_DMA_ST_inst_adr                                                          "0x0010"
#define DVR_DMA_ST_inst                                                              0x0010
#define DVR_DMA_ST_idle_st_5_40_shift                                                (5)
#define DVR_DMA_ST_idle_st_5_40_mask                                                 (0x00000020)
#define DVR_DMA_ST_idle_st_5_40(data)                                                (0x00000020&((data)<<5))
#define DVR_DMA_ST_idle_st_5_40_src(data)                                            ((0x00000020&(data))>>5)
#define DVR_DMA_ST_sin_dma_done_st_4_40_shift                                        (4)
#define DVR_DMA_ST_sin_dma_done_st_4_40_mask                                         (0x00000010)
#define DVR_DMA_ST_sin_dma_done_st_4_40(data)                                        (0x00000010&((data)<<4))
#define DVR_DMA_ST_sin_dma_done_st_4_40_src(data)                                    ((0x00000010&(data))>>4)
#define DVR_DMA_ST_desc_dma_done_st_3_40_shift                                       (3)
#define DVR_DMA_ST_desc_dma_done_st_3_40_mask                                        (0x00000008)
#define DVR_DMA_ST_desc_dma_done_st_3_40(data)                                       (0x00000008&((data)<<3))
#define DVR_DMA_ST_desc_dma_done_st_3_40_src(data)                                   ((0x00000008&(data))>>3)
#define DVR_DMA_ST_desc_empty_st_2_40_shift                                          (2)
#define DVR_DMA_ST_desc_empty_st_2_40_mask                                           (0x00000004)
#define DVR_DMA_ST_desc_empty_st_2_40(data)                                          (0x00000004&((data)<<2))
#define DVR_DMA_ST_desc_empty_st_2_40_src(data)                                      ((0x00000004&(data))>>2)
#define DVR_DMA_ST_pci_error_st_1_40_shift                                           (1)
#define DVR_DMA_ST_pci_error_st_1_40_mask                                            (0x00000002)
#define DVR_DMA_ST_pci_error_st_1_40(data)                                           (0x00000002&((data)<<1))
#define DVR_DMA_ST_pci_error_st_1_40_src(data)                                       ((0x00000002&(data))>>1)
#define DVR_DMA_ST_desc_error_st_0_40_shift                                          (0)
#define DVR_DMA_ST_desc_error_st_0_40_mask                                           (0x00000001)
#define DVR_DMA_ST_desc_error_st_0_40(data)                                          (0x00000001&((data)<<0))
#define DVR_DMA_ST_desc_error_st_0_40_src(data)                                      ((0x00000001&(data))>>0)


#define DVR_DMA_EN                                                                   0x18017044
#define DVR_DMA_EN_reg_addr                                                          "0xB8017044"
#define DVR_DMA_EN_reg                                                               0xB8017044
#define DVR_DMA_EN_inst_adr                                                          "0x0011"
#define DVR_DMA_EN_inst                                                              0x0011
#define DVR_DMA_EN_intv_cnt_31to16_44_shift                                          (16)
#define DVR_DMA_EN_intv_cnt_31to16_44_mask                                           (0xFFFF0000)
#define DVR_DMA_EN_intv_cnt_31to16_44(data)                                          (0xFFFF0000&((data)<<16))
#define DVR_DMA_EN_intv_cnt_31to16_44_src(data)                                      ((0xFFFF0000&(data))>>16)
#define DVR_DMA_EN_intp_done_en_11_44_shift                                          (11)
#define DVR_DMA_EN_intp_done_en_11_44_mask                                           (0x00000800)
#define DVR_DMA_EN_intp_done_en_11_44(data)                                          (0x00000800&((data)<<11))
#define DVR_DMA_EN_intp_done_en_11_44_src(data)                                      ((0x00000800&(data))>>11)
#define DVR_DMA_EN_intp_empty_en_10_44_shift                                         (10)
#define DVR_DMA_EN_intp_empty_en_10_44_mask                                          (0x00000400)
#define DVR_DMA_EN_intp_empty_en_10_44(data)                                         (0x00000400&((data)<<10))
#define DVR_DMA_EN_intp_empty_en_10_44_src(data)                                     ((0x00000400&(data))>>10)
#define DVR_DMA_EN_intp_pci_error_en_9_44_shift                                      (9)
#define DVR_DMA_EN_intp_pci_error_en_9_44_mask                                       (0x00000200)
#define DVR_DMA_EN_intp_pci_error_en_9_44(data)                                      (0x00000200&((data)<<9))
#define DVR_DMA_EN_intp_pci_error_en_9_44_src(data)                                  ((0x00000200&(data))>>9)
#define DVR_DMA_EN_intp_desc_error_en_8_44_shift                                     (8)
#define DVR_DMA_EN_intp_desc_error_en_8_44_mask                                      (0x00000100)
#define DVR_DMA_EN_intp_desc_error_en_8_44(data)                                     (0x00000100&((data)<<8))
#define DVR_DMA_EN_intp_desc_error_en_8_44_src(data)                                 ((0x00000100&(data))>>8)
#define DVR_DMA_EN_intv_en_3_44_shift                                                (3)
#define DVR_DMA_EN_intv_en_3_44_mask                                                 (0x00000008)
#define DVR_DMA_EN_intv_en_3_44(data)                                                (0x00000008&((data)<<3))
#define DVR_DMA_EN_intv_en_3_44_src(data)                                            ((0x00000008&(data))>>3)
#define DVR_DMA_EN_go_en_2_44_shift                                                  (2)
#define DVR_DMA_EN_go_en_2_44_mask                                                   (0x00000004)
#define DVR_DMA_EN_go_en_2_44(data)                                                  (0x00000004&((data)<<2))
#define DVR_DMA_EN_go_en_2_44_src(data)                                              ((0x00000004&(data))>>2)
#define DVR_DMA_EN_mode_en_1_44_shift                                                (1)
#define DVR_DMA_EN_mode_en_1_44_mask                                                 (0x00000002)
#define DVR_DMA_EN_mode_en_1_44(data)                                                (0x00000002&((data)<<1))
#define DVR_DMA_EN_mode_en_1_44_src(data)                                            ((0x00000002&(data))>>1)
#define DVR_DMA_EN_desc_en_0_44_shift                                                (0)
#define DVR_DMA_EN_desc_en_0_44_mask                                                 (0x00000001)
#define DVR_DMA_EN_desc_en_0_44(data)                                                (0x00000001&((data)<<0))
#define DVR_DMA_EN_desc_en_0_44_src(data)                                            ((0x00000001&(data))>>0)


#define DVR_DMA_PCI                                                                  0x18017048
#define DVR_DMA_PCI_reg_addr                                                         "0xB8017048"
#define DVR_DMA_PCI_reg                                                              0xB8017048
#define DVR_DMA_PCI_inst_adr                                                         "0x0012"
#define DVR_DMA_PCI_inst                                                             0x0012
#define DVR_DMA_PCI_addr_31to0_48_shift                                              (0)
#define DVR_DMA_PCI_addr_31to0_48_mask                                               (0xFFFFFFFF)
#define DVR_DMA_PCI_addr_31to0_48(data)                                              (0xFFFFFFFF&((data)<<0))
#define DVR_DMA_PCI_addr_31to0_48_src(data)                                          ((0xFFFFFFFF&(data))>>0)


#define DVR_DMA_DDR                                                                  0x1801704C
#define DVR_DMA_DDR_reg_addr                                                         "0xB801704C"
#define DVR_DMA_DDR_reg                                                              0xB801704C
#define DVR_DMA_DDR_inst_adr                                                         "0x0013"
#define DVR_DMA_DDR_inst                                                             0x0013
#define DVR_DMA_DDR_addr_27to0_4c_shift                                              (0)
#define DVR_DMA_DDR_addr_27to0_4c_mask                                               (0x0FFFFFFF)
#define DVR_DMA_DDR_addr_27to0_4c(data)                                              (0x0FFFFFFF&((data)<<0))
#define DVR_DMA_DDR_addr_27to0_4c_src(data)                                          ((0x0FFFFFFF&(data))>>0)


#define DVR_DMA_CNT                                                                  0x18017050
#define DVR_DMA_CNT_reg_addr                                                         "0xB8017050"
#define DVR_DMA_CNT_reg                                                              0xB8017050
#define DVR_DMA_CNT_inst_adr                                                         "0x0014"
#define DVR_DMA_CNT_inst                                                             0x0014
#define DVR_DMA_CNT_byte_cnt_23to0_50_shift                                          (0)
#define DVR_DMA_CNT_byte_cnt_23to0_50_mask                                           (0x00FFFFFF)
#define DVR_DMA_CNT_byte_cnt_23to0_50(data)                                          (0x00FFFFFF&((data)<<0))
#define DVR_DMA_CNT_byte_cnt_23to0_50_src(data)                                      ((0x00FFFFFF&(data))>>0)


#define DVR_DMA_DES0                                                                 0x18017054
#define DVR_DMA_DES0_reg_addr                                                        "0xB8017054"
#define DVR_DMA_DES0_reg                                                             0xB8017054
#define DVR_DMA_DES0_inst_adr                                                        "0x0015"
#define DVR_DMA_DES0_inst                                                            0x0015
#define DVR_DMA_DES0_base_ptr_27to0_54_shift                                         (0)
#define DVR_DMA_DES0_base_ptr_27to0_54_mask                                          (0x0FFFFFFF)
#define DVR_DMA_DES0_base_ptr_27to0_54(data)                                         (0x0FFFFFFF&((data)<<0))
#define DVR_DMA_DES0_base_ptr_27to0_54_src(data)                                     ((0x0FFFFFFF&(data))>>0)


#define DVR_DMA_DES1                                                                 0x18017058
#define DVR_DMA_DES1_reg_addr                                                        "0xB8017058"
#define DVR_DMA_DES1_reg                                                             0xB8017058
#define DVR_DMA_DES1_inst_adr                                                        "0x0016"
#define DVR_DMA_DES1_inst                                                            0x0016
#define DVR_DMA_DES1_limit_ptr_27to0_58_shift                                        (0)
#define DVR_DMA_DES1_limit_ptr_27to0_58_mask                                         (0x0FFFFFFF)
#define DVR_DMA_DES1_limit_ptr_27to0_58(data)                                        (0x0FFFFFFF&((data)<<0))
#define DVR_DMA_DES1_limit_ptr_27to0_58_src(data)                                    ((0x0FFFFFFF&(data))>>0)


#define DVR_DMA_DES2                                                                 0x1801705C
#define DVR_DMA_DES2_reg_addr                                                        "0xB801705C"
#define DVR_DMA_DES2_reg                                                             0xB801705C
#define DVR_DMA_DES2_inst_adr                                                        "0x0017"
#define DVR_DMA_DES2_inst                                                            0x0017
#define DVR_DMA_DES2_wr_ptr_27to0_5c_shift                                           (0)
#define DVR_DMA_DES2_wr_ptr_27to0_5c_mask                                            (0x0FFFFFFF)
#define DVR_DMA_DES2_wr_ptr_27to0_5c(data)                                           (0x0FFFFFFF&((data)<<0))
#define DVR_DMA_DES2_wr_ptr_27to0_5c_src(data)                                       ((0x0FFFFFFF&(data))>>0)


#define DVR_DMA_DES3                                                                 0x18017060
#define DVR_DMA_DES3_reg_addr                                                        "0xB8017060"
#define DVR_DMA_DES3_reg                                                             0xB8017060
#define DVR_DMA_DES3_inst_adr                                                        "0x0018"
#define DVR_DMA_DES3_inst                                                            0x0018
#define DVR_DMA_DES3_rd_ptr_27to0_60_shift                                           (0)
#define DVR_DMA_DES3_rd_ptr_27to0_60_mask                                            (0x0FFFFFFF)
#define DVR_DMA_DES3_rd_ptr_27to0_60(data)                                           (0x0FFFFFFF&((data)<<0))
#define DVR_DMA_DES3_rd_ptr_27to0_60_src(data)                                       ((0x0FFFFFFF&(data))>>0)


#define DVR_SOFT_RST                                                                 0x18017064
#define DVR_SOFT_RST_reg_addr                                                        "0xB8017064"
#define DVR_SOFT_RST_reg                                                             0xB8017064
#define DVR_SOFT_RST_inst_adr                                                        "0x0019"
#define DVR_SOFT_RST_inst                                                            0x0019
#define DVR_SOFT_RST_stop_ct_8_64_shift                                              (8)
#define DVR_SOFT_RST_stop_ct_8_64_mask                                               (0x00000100)
#define DVR_SOFT_RST_stop_ct_8_64(data)                                              (0x00000100&((data)<<8))
#define DVR_SOFT_RST_stop_ct_8_64_src(data)                                          ((0x00000100&(data))>>8)
#define DVR_SOFT_RST_idle_st_0_64_shift                                              (0)
#define DVR_SOFT_RST_idle_st_0_64_mask                                               (0x00000001)
#define DVR_SOFT_RST_idle_st_0_64(data)                                              (0x00000001&((data)<<0))
#define DVR_SOFT_RST_idle_st_0_64_src(data)                                          ((0x00000001&(data))>>0)


#define DVR_CLK_ST                                                                   0x18017068
#define DVR_CLK_ST_reg_addr                                                          "0xB8017068"
#define DVR_CLK_ST_reg                                                               0xB8017068
#define DVR_CLK_ST_inst_adr                                                          "0x001A"
#define DVR_CLK_ST_inst                                                              0x001A
#define DVR_CLK_ST_pci_master_busy_st_7_68_shift                                     (7)
#define DVR_CLK_ST_pci_master_busy_st_7_68_mask                                      (0x00000080)
#define DVR_CLK_ST_pci_master_busy_st_7_68(data)                                     (0x00000080&((data)<<7))
#define DVR_CLK_ST_pci_master_busy_st_7_68_src(data)                                 ((0x00000080&(data))>>7)
#define DVR_CLK_ST_pci_slave_busy_st_6_68_shift                                      (6)
#define DVR_CLK_ST_pci_slave_busy_st_6_68_mask                                       (0x00000040)
#define DVR_CLK_ST_pci_slave_busy_st_6_68(data)                                      (0x00000040&((data)<<6))
#define DVR_CLK_ST_pci_slave_busy_st_6_68_src(data)                                  ((0x00000040&(data))>>6)
#define DVR_CLK_ST_mio_cfg_busy_st_5_68_shift                                        (5)
#define DVR_CLK_ST_mio_cfg_busy_st_5_68_mask                                         (0x00000020)
#define DVR_CLK_ST_mio_cfg_busy_st_5_68(data)                                        (0x00000020&((data)<<5))
#define DVR_CLK_ST_mio_cfg_busy_st_5_68_src(data)                                    ((0x00000020&(data))>>5)
#define DVR_CLK_ST_dma_busy_st_4_68_shift                                            (4)
#define DVR_CLK_ST_dma_busy_st_4_68_mask                                             (0x00000010)
#define DVR_CLK_ST_dma_busy_st_4_68(data)                                            (0x00000010&((data)<<4))
#define DVR_CLK_ST_dma_busy_st_4_68_src(data)                                        ((0x00000010&(data))>>4)
#define DVR_CLK_ST_pci_clk_lock_st_1_68_shift                                        (1)
#define DVR_CLK_ST_pci_clk_lock_st_1_68_mask                                         (0x00000002)
#define DVR_CLK_ST_pci_clk_lock_st_1_68(data)                                        (0x00000002&((data)<<1))
#define DVR_CLK_ST_pci_clk_lock_st_1_68_src(data)                                    ((0x00000002&(data))>>1)
#define DVR_CLK_ST_pci_clk_st_0_68_shift                                             (0)
#define DVR_CLK_ST_pci_clk_st_0_68_mask                                              (0x00000001)
#define DVR_CLK_ST_pci_clk_st_0_68(data)                                             (0x00000001&((data)<<0))
#define DVR_CLK_ST_pci_clk_st_0_68_src(data)                                         ((0x00000001&(data))>>0)


#define DVR_SPC_CT                                                                   0x1801706C
#define DVR_SPC_CT_reg_addr                                                          "0xB801706C"
#define DVR_SPC_CT_reg                                                               0xB801706C
#define DVR_SPC_CT_inst_adr                                                          "0x001B"
#define DVR_SPC_CT_inst                                                              0x001B
#define DVR_SPC_CT_pci_int_req_8_6c_shift                                            (8)
#define DVR_SPC_CT_pci_int_req_8_6c_mask                                             (0x00000100)
#define DVR_SPC_CT_pci_int_req_8_6c(data)                                            (0x00000100&((data)<<8))
#define DVR_SPC_CT_pci_int_req_8_6c_src(data)                                        ((0x00000100&(data))>>8)
#define DVR_SPC_CT_clk_run_req_4_6c_shift                                            (4)
#define DVR_SPC_CT_clk_run_req_4_6c_mask                                             (0x00000010)
#define DVR_SPC_CT_clk_run_req_4_6c(data)                                            (0x00000010&((data)<<4))
#define DVR_SPC_CT_clk_run_req_4_6c_src(data)                                        ((0x00000010&(data))>>4)
#define DVR_SPC_CT_pci_clk_lock_en_0_6c_shift                                        (0)
#define DVR_SPC_CT_pci_clk_lock_en_0_6c_mask                                         (0x00000001)
#define DVR_SPC_CT_pci_clk_lock_en_0_6c(data)                                        (0x00000001&((data)<<0))
#define DVR_SPC_CT_pci_clk_lock_en_0_6c_src(data)                                    ((0x00000001&(data))>>0)


#define DVR_SPC_ST                                                                   0x18017070
#define DVR_SPC_ST_reg_addr                                                          "0xB8017070"
#define DVR_SPC_ST_reg                                                               0xB8017070
#define DVR_SPC_ST_inst_adr                                                          "0x001C"
#define DVR_SPC_ST_inst                                                              0x001C
#define DVR_SPC_ST_pci_int_st_16_70_shift                                            (16)
#define DVR_SPC_ST_pci_int_st_16_70_mask                                             (0x00010000)
#define DVR_SPC_ST_pci_int_st_16_70(data)                                            (0x00010000&((data)<<16))
#define DVR_SPC_ST_pci_int_st_16_70_src(data)                                        ((0x00010000&(data))>>16)
#define DVR_SPC_ST_clk_run_st_0_70_shift                                             (0)
#define DVR_SPC_ST_clk_run_st_0_70_mask                                              (0x00000001)
#define DVR_SPC_ST_clk_run_st_0_70(data)                                             (0x00000001&((data)<<0))
#define DVR_SPC_ST_clk_run_st_0_70_src(data)                                         ((0x00000001&(data))>>0)


#define DVR_DBG                                                                      0x18017074
#define DVR_DBG_reg_addr                                                             "0xB8017074"
#define DVR_DBG_reg                                                                  0xB8017074
#define DVR_DBG_inst_adr                                                             "0x001D"
#define DVR_DBG_inst                                                                 0x001D
#define DVR_DBG_dbg_sel1_shift                                                       (7)
#define DVR_DBG_dbg_sel1_mask                                                        (0x00001F80)
#define DVR_DBG_dbg_sel1(data)                                                       (0x00001F80&((data)<<7))
#define DVR_DBG_dbg_sel1_src(data)                                                   ((0x00001F80&(data))>>7)
#define DVR_DBG_dbg_sel0_shift                                                       (1)
#define DVR_DBG_dbg_sel0_mask                                                        (0x0000007E)
#define DVR_DBG_dbg_sel0(data)                                                       (0x0000007E&((data)<<1))
#define DVR_DBG_dbg_sel0_src(data)                                                   ((0x0000007E&(data))>>1)
#define DVR_DBG_dbg_en_shift                                                         (0)
#define DVR_DBG_dbg_en_mask                                                          (0x00000001)
#define DVR_DBG_dbg_en(data)                                                         (0x00000001&((data)<<0))
#define DVR_DBG_dbg_en_src(data)                                                     ((0x00000001&(data))>>0)


#define DVR_DIR_ST                                                                   0x18017078
#define DVR_DIR_ST_reg_addr                                                          "0xB8017078"
#define DVR_DIR_ST_reg                                                               0xB8017078
#define DVR_DIR_ST_inst_adr                                                          "0x001E"
#define DVR_DIR_ST_inst                                                              0x001E
#define DVR_DIR_ST_rerror_st_1_78_shift                                              (1)
#define DVR_DIR_ST_rerror_st_1_78_mask                                               (0x00000002)
#define DVR_DIR_ST_rerror_st_1_78(data)                                              (0x00000002&((data)<<1))
#define DVR_DIR_ST_rerror_st_1_78_src(data)                                          ((0x00000002&(data))>>1)
#define DVR_DIR_ST_werror_st_0_78_shift                                              (0)
#define DVR_DIR_ST_werror_st_0_78_mask                                               (0x00000001)
#define DVR_DIR_ST_werror_st_0_78(data)                                              (0x00000001&((data)<<0))
#define DVR_DIR_ST_werror_st_0_78_src(data)                                          ((0x00000001&(data))>>0)


#define DVR_DIR_EN                                                                   0x1801707C
#define DVR_DIR_EN_reg_addr                                                          "0xB801707C"
#define DVR_DIR_EN_reg                                                               0xB801707C
#define DVR_DIR_EN_inst_adr                                                          "0x001F"
#define DVR_DIR_EN_inst                                                              0x001F
#define DVR_DIR_EN_error_ack_read_1_7c_shift                                         (1)
#define DVR_DIR_EN_error_ack_read_1_7c_mask                                          (0x00000002)
#define DVR_DIR_EN_error_ack_read_1_7c(data)                                         (0x00000002&((data)<<1))
#define DVR_DIR_EN_error_ack_read_1_7c_src(data)                                     ((0x00000002&(data))>>1)
#define DVR_DIR_EN_intp_en_0_7c_shift                                                (0)
#define DVR_DIR_EN_intp_en_0_7c_mask                                                 (0x00000001)
#define DVR_DIR_EN_intp_en_0_7c(data)                                                (0x00000001&((data)<<0))
#define DVR_DIR_EN_intp_en_0_7c_src(data)                                            ((0x00000001&(data))>>0)


#define DVR_DEV_ST                                                                   0x18017080
#define DVR_DEV_ST_reg_addr                                                          "0xB8017080"
#define DVR_DEV_ST_reg                                                               0xB8017080
#define DVR_DEV_ST_inst_adr                                                          "0x0020"
#define DVR_DEV_ST_inst                                                              0x0020
#define DVR_DEV_ST_dev_ddr_done_st_0_80_shift                                        (0)
#define DVR_DEV_ST_dev_ddr_done_st_0_80_mask                                         (0x00000001)
#define DVR_DEV_ST_dev_ddr_done_st_0_80(data)                                        (0x00000001&((data)<<0))
#define DVR_DEV_ST_dev_ddr_done_st_0_80_src(data)                                    ((0x00000001&(data))>>0)


#define DVR_DEV_CT                                                                   0x18017084
#define DVR_DEV_CT_reg_addr                                                          "0xB8017084"
#define DVR_DEV_CT_reg                                                               0xB8017084
#define DVR_DEV_CT_inst_adr                                                          "0x0021"
#define DVR_DEV_CT_inst                                                              0x0021
#define DVR_DEV_CT_dev_start_0_84_shift                                              (0)
#define DVR_DEV_CT_dev_start_0_84_mask                                               (0x00000001)
#define DVR_DEV_CT_dev_start_0_84(data)                                              (0x00000001&((data)<<0))
#define DVR_DEV_CT_dev_start_0_84_src(data)                                          ((0x00000001&(data))>>0)


#define DVR_DEV_DDR                                                                  0x18017088
#define DVR_DEV_DDR_reg_addr                                                         "0xB8017088"
#define DVR_DEV_DDR_reg                                                              0xB8017088
#define DVR_DEV_DDR_inst_adr                                                         "0x0022"
#define DVR_DEV_DDR_inst                                                             0x0022
#define DVR_DEV_DDR_dev_ddr_addr_31to0_88_shift                                      (0)
#define DVR_DEV_DDR_dev_ddr_addr_31to0_88_mask                                       (0xFFFFFFFF)
#define DVR_DEV_DDR_dev_ddr_addr_31to0_88(data)                                      (0xFFFFFFFF&((data)<<0))
#define DVR_DEV_DDR_dev_ddr_addr_31to0_88_src(data)                                  ((0xFFFFFFFF&(data))>>0)


#define DVR_DEV_PCI                                                                  0x1801708C
#define DVR_DEV_PCI_reg_addr                                                         "0xB801708C"
#define DVR_DEV_PCI_reg                                                              0xB801708C
#define DVR_DEV_PCI_inst_adr                                                         "0x0023"
#define DVR_DEV_PCI_inst                                                             0x0023
#define DVR_DEV_PCI_dev_pci_addr_31to0_8c_shift                                      (0)
#define DVR_DEV_PCI_dev_pci_addr_31to0_8c_mask                                       (0xFFFFFFFF)
#define DVR_DEV_PCI_dev_pci_addr_31to0_8c(data)                                      (0xFFFFFFFF&((data)<<0))
#define DVR_DEV_PCI_dev_pci_addr_31to0_8c_src(data)                                  ((0xFFFFFFFF&(data))>>0)


#define DVR_DEV_CNT                                                                  0x18017090
#define DVR_DEV_CNT_reg_addr                                                         "0xB8017090"
#define DVR_DEV_CNT_reg                                                              0xB8017090
#define DVR_DEV_CNT_inst_adr                                                         "0x0024"
#define DVR_DEV_CNT_inst                                                             0x0024
#define DVR_DEV_CNT_dev_ddr_cnt_31to0_90_shift                                       (0)
#define DVR_DEV_CNT_dev_ddr_cnt_31to0_90_mask                                        (0xFFFFFFFF)
#define DVR_DEV_CNT_dev_ddr_cnt_31to0_90(data)                                       (0xFFFFFFFF&((data)<<0))
#define DVR_DEV_CNT_dev_ddr_cnt_31to0_90_src(data)                                   ((0xFFFFFFFF&(data))>>0)


#define DVR_TMP0_REG_0                                                               0x18017094
#define DVR_TMP0_REG_1                                                               0x18017098
#define DVR_TMP0_REG_2                                                               0x1801709C
#define DVR_TMP0_REG_0_reg_addr                                                      "0xB8017094"
#define DVR_TMP0_REG_1_reg_addr                                                      "0xB8017098"
#define DVR_TMP0_REG_2_reg_addr                                                      "0xB801709C"
#define DVR_TMP0_REG_0_reg                                                           0xB8017094
#define DVR_TMP0_REG_1_reg                                                           0xB8017098
#define DVR_TMP0_REG_2_reg                                                           0xB801709C
#define DVR_TMP0_REG_0_inst_adr                                                      "0x0025"
#define DVR_TMP0_REG_1_inst_adr                                                      "0x0026"
#define DVR_TMP0_REG_2_inst_adr                                                      "0x0027"
#define DVR_TMP0_REG_0_inst                                                          0x0025
#define DVR_TMP0_REG_1_inst                                                          0x0026
#define DVR_TMP0_REG_2_inst                                                          0x0027
#define DVR_TMP0_REG_test_reg_shift                                                  (0)
#define DVR_TMP0_REG_test_reg_mask                                                   (0xFFFFFFFF)
#define DVR_TMP0_REG_test_reg(data)                                                  (0xFFFFFFFF&((data)<<0))
#define DVR_TMP0_REG_test_reg_src(data)                                              ((0xFFFFFFFF&(data))>>0)


#define DVR_TMP1_REG_0                                                               0x180170A0
#define DVR_TMP1_REG_1                                                               0x180170A4
#define DVR_TMP1_REG_2                                                               0x180170A8
#define DVR_TMP1_REG_0_reg_addr                                                      "0xB80170A0"
#define DVR_TMP1_REG_1_reg_addr                                                      "0xB80170A4"
#define DVR_TMP1_REG_2_reg_addr                                                      "0xB80170A8"
#define DVR_TMP1_REG_0_reg                                                           0xB80170A0
#define DVR_TMP1_REG_1_reg                                                           0xB80170A4
#define DVR_TMP1_REG_2_reg                                                           0xB80170A8
#define DVR_TMP1_REG_0_inst_adr                                                      "0x0028"
#define DVR_TMP1_REG_1_inst_adr                                                      "0x0029"
#define DVR_TMP1_REG_2_inst_adr                                                      "0x002A"
#define DVR_TMP1_REG_0_inst                                                          0x0028
#define DVR_TMP1_REG_1_inst                                                          0x0029
#define DVR_TMP1_REG_2_inst                                                          0x002A
#define DVR_TMP1_REG_test_reg_shift                                                  (0)
#define DVR_TMP1_REG_test_reg_mask                                                   (0xFFFFFFFF)
#define DVR_TMP1_REG_test_reg(data)                                                  (0xFFFFFFFF&((data)<<0))
#define DVR_TMP1_REG_test_reg_src(data)                                              ((0xFFFFFFFF&(data))>>0)


#define DVR_SCTCH                                                                    0x180170AC
#define DVR_SCTCH_reg_addr                                                           "0xB80170AC"
#define DVR_SCTCH_reg                                                                0xB80170AC
#define DVR_SCTCH_inst_adr                                                           "0x002B"
#define DVR_SCTCH_inst                                                               0x002B
#define DVR_SCTCH_reg1_shift                                                         (16)
#define DVR_SCTCH_reg1_mask                                                          (0xFFFF0000)
#define DVR_SCTCH_reg1(data)                                                         (0xFFFF0000&((data)<<16))
#define DVR_SCTCH_reg1_src(data)                                                     ((0xFFFF0000&(data))>>16)
#define DVR_SCTCH_reg0_shift                                                         (0)
#define DVR_SCTCH_reg0_mask                                                          (0x0000FFFF)
#define DVR_SCTCH_reg0(data)                                                         (0x0000FFFF&((data)<<0))
#define DVR_SCTCH_reg0_src(data)                                                     ((0x0000FFFF&(data))>>0)


#define PCI_SCTCH                                                                    0x18017100
#define PCI_SCTCH_reg_addr                                                           "0xB8017100"
#define PCI_SCTCH_reg                                                                0xB8017100
#define PCI_SCTCH_inst_adr                                                           "0x0040"
#define PCI_SCTCH_inst                                                               0x0040
#define PCI_SCTCH_reg1_16to31_00_shift                                               (16)
#define PCI_SCTCH_reg1_16to31_00_mask                                                (0xFFFF0000)
#define PCI_SCTCH_reg1_16to31_00(data)                                               (0xFFFF0000&((data)<<16))
#define PCI_SCTCH_reg1_16to31_00_src(data)                                           ((0xFFFF0000&(data))>>16)
#define PCI_SCTCH_reg0_0to15_00_shift                                                (0)
#define PCI_SCTCH_reg0_0to15_00_mask                                                 (0x0000FFFF)
#define PCI_SCTCH_reg0_0to15_00(data)                                                (0x0000FFFF&((data)<<0))
#define PCI_SCTCH_reg0_0to15_00_src(data)                                            ((0x0000FFFF&(data))>>0)


#define PCI_GNR_EN1                                                                  0x18017104
#define PCI_GNR_EN1_reg_addr                                                         "0xB8017104"
#define PCI_GNR_EN1_reg                                                              0xB8017104
#define PCI_GNR_EN1_inst_adr                                                         "0x0041"
#define PCI_GNR_EN1_inst                                                             0x0041
#define PCI_GNR_EN1_retry_cnt_0to15_04_shift                                         (16)
#define PCI_GNR_EN1_retry_cnt_0to15_04_mask                                          (0xFFFF0000)
#define PCI_GNR_EN1_retry_cnt_0to15_04(data)                                         (0xFFFF0000&((data)<<16))
#define PCI_GNR_EN1_retry_cnt_0to15_04_src(data)                                     ((0xFFFF0000&(data))>>16)
#define PCI_GNR_EN1_retry_cnt_en_0_04_shift                                          (0)
#define PCI_GNR_EN1_retry_cnt_en_0_04_mask                                           (0x00000001)
#define PCI_GNR_EN1_retry_cnt_en_0_04(data)                                          (0x00000001&((data)<<0))
#define PCI_GNR_EN1_retry_cnt_en_0_04_src(data)                                      ((0x00000001&(data))>>0)


#define PCI_GNR_EN2                                                                  0x18017108
#define PCI_GNR_EN2_reg_addr                                                         "0xB8017108"
#define PCI_GNR_EN2_reg                                                              0xB8017108
#define PCI_GNR_EN2_inst_adr                                                         "0x0042"
#define PCI_GNR_EN2_inst                                                             0x0042
#define PCI_GNR_EN2_master_rd_burst_25to26_08_shift                                  (25)
#define PCI_GNR_EN2_master_rd_burst_25to26_08_mask                                   (0x06000000)
#define PCI_GNR_EN2_master_rd_burst_25to26_08(data)                                  (0x06000000&((data)<<25))
#define PCI_GNR_EN2_master_rd_burst_25to26_08_src(data)                              ((0x06000000&(data))>>25)
#define PCI_GNR_EN2_master_wr_inv_24_08_shift                                        (24)
#define PCI_GNR_EN2_master_wr_inv_24_08_mask                                         (0x01000000)
#define PCI_GNR_EN2_master_wr_inv_24_08(data)                                        (0x01000000&((data)<<24))
#define PCI_GNR_EN2_master_wr_inv_24_08_src(data)                                    ((0x01000000&(data))>>24)
#define PCI_GNR_EN2_spc_cyc_en_22_08_shift                                           (22)
#define PCI_GNR_EN2_spc_cyc_en_22_08_mask                                            (0x00400000)
#define PCI_GNR_EN2_spc_cyc_en_22_08(data)                                           (0x00400000&((data)<<22))
#define PCI_GNR_EN2_spc_cyc_en_22_08_src(data)                                       ((0x00400000&(data))>>22)
#define PCI_GNR_EN2_retry_int_en_21_08_shift                                         (21)
#define PCI_GNR_EN2_retry_int_en_21_08_mask                                          (0x00200000)
#define PCI_GNR_EN2_retry_int_en_21_08(data)                                         (0x00200000&((data)<<21))
#define PCI_GNR_EN2_retry_int_en_21_08_src(data)                                     ((0x00200000&(data))>>21)
#define PCI_GNR_EN2_mon_int_en_20_08_shift                                           (20)
#define PCI_GNR_EN2_mon_int_en_20_08_mask                                            (0x00100000)
#define PCI_GNR_EN2_mon_int_en_20_08(data)                                           (0x00100000&((data)<<20))
#define PCI_GNR_EN2_mon_int_en_20_08_src(data)                                       ((0x00100000&(data))>>20)
#define PCI_GNR_EN2_pme_int_en_19_08_shift                                           (19)
#define PCI_GNR_EN2_pme_int_en_19_08_mask                                            (0x00080000)
#define PCI_GNR_EN2_pme_int_en_19_08(data)                                           (0x00080000&((data)<<19))
#define PCI_GNR_EN2_pme_int_en_19_08_src(data)                                       ((0x00080000&(data))>>19)
#define PCI_GNR_EN2_inta_int_en_18_08_shift                                          (18)
#define PCI_GNR_EN2_inta_int_en_18_08_mask                                           (0x00040000)
#define PCI_GNR_EN2_inta_int_en_18_08(data)                                          (0x00040000&((data)<<18))
#define PCI_GNR_EN2_inta_int_en_18_08_src(data)                                      ((0x00040000&(data))>>18)
#define PCI_GNR_EN2_serr_int_en_17_08_shift                                          (17)
#define PCI_GNR_EN2_serr_int_en_17_08_mask                                           (0x00020000)
#define PCI_GNR_EN2_serr_int_en_17_08(data)                                          (0x00020000&((data)<<17))
#define PCI_GNR_EN2_serr_int_en_17_08_src(data)                                      ((0x00020000&(data))>>17)
#define PCI_GNR_EN2_perr_int_en_16_08_shift                                          (16)
#define PCI_GNR_EN2_perr_int_en_16_08_mask                                           (0x00010000)
#define PCI_GNR_EN2_perr_int_en_16_08(data)                                          (0x00010000&((data)<<16))
#define PCI_GNR_EN2_perr_int_en_16_08_src(data)                                      ((0x00010000&(data))>>16)
#define PCI_GNR_EN2_lat_timer_en_14_08_shift                                         (14)
#define PCI_GNR_EN2_lat_timer_en_14_08_mask                                          (0x00004000)
#define PCI_GNR_EN2_lat_timer_en_14_08(data)                                         (0x00004000&((data)<<14))
#define PCI_GNR_EN2_lat_timer_en_14_08_src(data)                                     ((0x00004000&(data))>>14)
#define PCI_GNR_EN2_pci_mon_en_13_08_shift                                           (13)
#define PCI_GNR_EN2_pci_mon_en_13_08_mask                                            (0x00002000)
#define PCI_GNR_EN2_pci_mon_en_13_08(data)                                           (0x00002000&((data)<<13))
#define PCI_GNR_EN2_pci_mon_en_13_08_src(data)                                       ((0x00002000&(data))>>13)
#define PCI_GNR_EN2_park_dev_12o11_08_shift                                          (11)
#define PCI_GNR_EN2_park_dev_12o11_08_mask                                           (0x00001800)
#define PCI_GNR_EN2_park_dev_12o11_08(data)                                          (0x00001800&((data)<<11))
#define PCI_GNR_EN2_park_dev_12o11_08_src(data)                                      ((0x00001800&(data))>>11)
#define PCI_GNR_EN2_bus_park_en_10_08_shift                                          (10)
#define PCI_GNR_EN2_bus_park_en_10_08_mask                                           (0x00000400)
#define PCI_GNR_EN2_bus_park_en_10_08(data)                                          (0x00000400&((data)<<10))
#define PCI_GNR_EN2_bus_park_en_10_08_src(data)                                      ((0x00000400&(data))>>10)
#define PCI_GNR_EN2_slave_b2b_en_9_08_shift                                          (9)
#define PCI_GNR_EN2_slave_b2b_en_9_08_mask                                           (0x00000200)
#define PCI_GNR_EN2_slave_b2b_en_9_08(data)                                          (0x00000200&((data)<<9))
#define PCI_GNR_EN2_slave_b2b_en_9_08_src(data)                                      ((0x00000200&(data))>>9)
#define PCI_GNR_EN2_66mhz_en_8_08_shift                                              (8)
#define PCI_GNR_EN2_66mhz_en_8_08_mask                                               (0x00000100)
#define PCI_GNR_EN2_66mhz_en_8_08(data)                                              (0x00000100&((data)<<8))
#define PCI_GNR_EN2_66mhz_en_8_08_src(data)                                          ((0x00000100&(data))>>8)
#define PCI_GNR_EN2_xbus_ba_en_6_08_shift                                            (6)
#define PCI_GNR_EN2_xbus_ba_en_6_08_mask                                             (0x00000040)
#define PCI_GNR_EN2_xbus_ba_en_6_08(data)                                            (0x00000040&((data)<<6))
#define PCI_GNR_EN2_xbus_ba_en_6_08_src(data)                                        ((0x00000040&(data))>>6)
#define PCI_GNR_EN2_sbus_tran_en_5_08_shift                                          (5)
#define PCI_GNR_EN2_sbus_tran_en_5_08_mask                                           (0x00000020)
#define PCI_GNR_EN2_sbus_tran_en_5_08(data)                                          (0x00000020&((data)<<5))
#define PCI_GNR_EN2_sbus_tran_en_5_08_src(data)                                      ((0x00000020&(data))>>5)
#define PCI_GNR_EN2_sbus_ba_en_4_08_shift                                            (4)
#define PCI_GNR_EN2_sbus_ba_en_4_08_mask                                             (0x00000010)
#define PCI_GNR_EN2_sbus_ba_en_4_08(data)                                            (0x00000010&((data)<<4))
#define PCI_GNR_EN2_sbus_ba_en_4_08_src(data)                                        ((0x00000010&(data))>>4)
#define PCI_GNR_EN2_dbus_tran_en_3_08_shift                                          (3)
#define PCI_GNR_EN2_dbus_tran_en_3_08_mask                                           (0x00000008)
#define PCI_GNR_EN2_dbus_tran_en_3_08(data)                                          (0x00000008&((data)<<3))
#define PCI_GNR_EN2_dbus_tran_en_3_08_src(data)                                      ((0x00000008&(data))>>3)
#define PCI_GNR_EN2_dbus_ba_en_2_08_shift                                            (2)
#define PCI_GNR_EN2_dbus_ba_en_2_08_mask                                             (0x00000004)
#define PCI_GNR_EN2_dbus_ba_en_2_08(data)                                            (0x00000004&((data)<<2))
#define PCI_GNR_EN2_dbus_ba_en_2_08_src(data)                                        ((0x00000004&(data))>>2)
#define PCI_GNR_EN2_rbus_tran_en_1_08_shift                                          (1)
#define PCI_GNR_EN2_rbus_tran_en_1_08_mask                                           (0x00000002)
#define PCI_GNR_EN2_rbus_tran_en_1_08(data)                                          (0x00000002&((data)<<1))
#define PCI_GNR_EN2_rbus_tran_en_1_08_src(data)                                      ((0x00000002&(data))>>1)
#define PCI_GNR_EN2_rbus_ba_en_0_08_shift                                            (0)
#define PCI_GNR_EN2_rbus_ba_en_0_08_mask                                             (0x00000001)
#define PCI_GNR_EN2_rbus_ba_en_0_08(data)                                            (0x00000001&((data)<<0))
#define PCI_GNR_EN2_rbus_ba_en_0_08_src(data)                                        ((0x00000001&(data))>>0)


#define PCI_GNR_ST                                                                   0x1801710C
#define PCI_GNR_ST_reg_addr                                                          "0xB801710C"
#define PCI_GNR_ST_reg                                                               0xB801710C
#define PCI_GNR_ST_inst_adr                                                          "0x0043"
#define PCI_GNR_ST_inst                                                              0x0043
#define PCI_GNR_ST_spc_cyc_msn_17to16_0c_shift                                       (16)
#define PCI_GNR_ST_spc_cyc_msn_17to16_0c_mask                                        (0x00030000)
#define PCI_GNR_ST_spc_cyc_msn_17to16_0c(data)                                       (0x00030000&((data)<<16))
#define PCI_GNR_ST_spc_cyc_msn_17to16_0c_src(data)                                   ((0x00030000&(data))>>16)
#define PCI_GNR_ST_spc_cyc_erro_6_0c_shift                                           (6)
#define PCI_GNR_ST_spc_cyc_erro_6_0c_mask                                            (0x00000040)
#define PCI_GNR_ST_spc_cyc_erro_6_0c(data)                                           (0x00000040&((data)<<6))
#define PCI_GNR_ST_spc_cyc_erro_6_0c_src(data)                                       ((0x00000040&(data))>>6)
#define PCI_GNR_ST_retry_error_5_0c_shift                                            (5)
#define PCI_GNR_ST_retry_error_5_0c_mask                                             (0x00000020)
#define PCI_GNR_ST_retry_error_5_0c(data)                                            (0x00000020&((data)<<5))
#define PCI_GNR_ST_retry_error_5_0c_src(data)                                        ((0x00000020&(data))>>5)
#define PCI_GNR_ST_mon_error_4_0c_shift                                              (4)
#define PCI_GNR_ST_mon_error_4_0c_mask                                               (0x00000010)
#define PCI_GNR_ST_mon_error_4_0c(data)                                              (0x00000010&((data)<<4))
#define PCI_GNR_ST_mon_error_4_0c_src(data)                                          ((0x00000010&(data))>>4)
#define PCI_GNR_ST_serr_error_3_0c_shift                                             (3)
#define PCI_GNR_ST_serr_error_3_0c_mask                                              (0x00000008)
#define PCI_GNR_ST_serr_error_3_0c(data)                                             (0x00000008&((data)<<3))
#define PCI_GNR_ST_serr_error_3_0c_src(data)                                         ((0x00000008&(data))>>3)
#define PCI_GNR_ST_perr_error_2_0c_shift                                             (2)
#define PCI_GNR_ST_perr_error_2_0c_mask                                              (0x00000004)
#define PCI_GNR_ST_perr_error_2_0c(data)                                             (0x00000004&((data)<<2))
#define PCI_GNR_ST_perr_error_2_0c_src(data)                                         ((0x00000004&(data))>>2)
#define PCI_GNR_ST_slave_error_1_0c_shift                                            (1)
#define PCI_GNR_ST_slave_error_1_0c_mask                                             (0x00000002)
#define PCI_GNR_ST_slave_error_1_0c(data)                                            (0x00000002&((data)<<1))
#define PCI_GNR_ST_slave_error_1_0c_src(data)                                        ((0x00000002&(data))>>1)
#define PCI_GNR_ST_master_error_0_0c_shift                                           (0)
#define PCI_GNR_ST_master_error_0_0c_mask                                            (0x00000001)
#define PCI_GNR_ST_master_error_0_0c(data)                                           (0x00000001&((data)<<0))
#define PCI_GNR_ST_master_error_0_0c_src(data)                                       ((0x00000001&(data))>>0)


#define PCI_GNR_INT                                                                  0x18017110
#define PCI_GNR_INT_reg_addr                                                         "0xB8017110"
#define PCI_GNR_INT_reg                                                              0xB8017110
#define PCI_GNR_INT_inst_adr                                                         "0x0044"
#define PCI_GNR_INT_inst                                                             0x0044
#define PCI_GNR_INT_intp_spc_cyc_6_10_shift                                          (6)
#define PCI_GNR_INT_intp_spc_cyc_6_10_mask                                           (0x00000040)
#define PCI_GNR_INT_intp_spc_cyc_6_10(data)                                          (0x00000040&((data)<<6))
#define PCI_GNR_INT_intp_spc_cyc_6_10_src(data)                                      ((0x00000040&(data))>>6)
#define PCI_GNR_INT_intp_retry_5_10_shift                                            (5)
#define PCI_GNR_INT_intp_retry_5_10_mask                                             (0x00000020)
#define PCI_GNR_INT_intp_retry_5_10(data)                                            (0x00000020&((data)<<5))
#define PCI_GNR_INT_intp_retry_5_10_src(data)                                        ((0x00000020&(data))>>5)
#define PCI_GNR_INT_intp_mon_4_10_shift                                              (4)
#define PCI_GNR_INT_intp_mon_4_10_mask                                               (0x00000010)
#define PCI_GNR_INT_intp_mon_4_10(data)                                              (0x00000010&((data)<<4))
#define PCI_GNR_INT_intp_mon_4_10_src(data)                                          ((0x00000010&(data))>>4)
#define PCI_GNR_INT_intp_pme_3_10_shift                                              (3)
#define PCI_GNR_INT_intp_pme_3_10_mask                                               (0x00000008)
#define PCI_GNR_INT_intp_pme_3_10(data)                                              (0x00000008&((data)<<3))
#define PCI_GNR_INT_intp_pme_3_10_src(data)                                          ((0x00000008&(data))>>3)
#define PCI_GNR_INT_intp_genr_2_10_shift                                             (2)
#define PCI_GNR_INT_intp_genr_2_10_mask                                              (0x00000004)
#define PCI_GNR_INT_intp_genr_2_10(data)                                             (0x00000004&((data)<<2))
#define PCI_GNR_INT_intp_genr_2_10_src(data)                                         ((0x00000004&(data))>>2)
#define PCI_GNR_INT_intp_serr_1_10_shift                                             (1)
#define PCI_GNR_INT_intp_serr_1_10_mask                                              (0x00000002)
#define PCI_GNR_INT_intp_serr_1_10(data)                                             (0x00000002&((data)<<1))
#define PCI_GNR_INT_intp_serr_1_10_src(data)                                         ((0x00000002&(data))>>1)
#define PCI_GNR_INT_intp_perr_0_10_shift                                             (0)
#define PCI_GNR_INT_intp_perr_0_10_mask                                              (0x00000001)
#define PCI_GNR_INT_intp_perr_0_10(data)                                             (0x00000001&((data)<<0))
#define PCI_GNR_INT_intp_perr_0_10_src(data)                                         ((0x00000001&(data))>>0)


#define PCI_MASK0                                                                    0x18017114
#define PCI_MASK0_reg_addr                                                           "0xB8017114"
#define PCI_MASK0_reg                                                                0xB8017114
#define PCI_MASK0_inst_adr                                                           "0x0045"
#define PCI_MASK0_inst                                                               0x0045
#define PCI_MASK0_rbus_mask_31to28_14_shift                                          (28)
#define PCI_MASK0_rbus_mask_31to28_14_mask                                           (0xF0000000)
#define PCI_MASK0_rbus_mask_31to28_14(data)                                          (0xF0000000&((data)<<28))
#define PCI_MASK0_rbus_mask_31to28_14_src(data)                                      ((0xF0000000&(data))>>28)
#define PCI_MASK0_rbus_mask_27to8_14_shift                                           (8)
#define PCI_MASK0_rbus_mask_27to8_14_mask                                            (0x0FFFFF00)
#define PCI_MASK0_rbus_mask_27to8_14(data)                                           (0x0FFFFF00&((data)<<8))
#define PCI_MASK0_rbus_mask_27to8_14_src(data)                                       ((0x0FFFFF00&(data))>>8)


#define PCI_TRANSL0                                                                  0x18017118
#define PCI_TRANSL0_reg_addr                                                         "0xB8017118"
#define PCI_TRANSL0_reg                                                              0xB8017118
#define PCI_TRANSL0_inst_adr                                                         "0x0046"
#define PCI_TRANSL0_inst                                                             0x0046
#define PCI_TRANSL0_rbus_transl_31to8_18_shift                                       (8)
#define PCI_TRANSL0_rbus_transl_31to8_18_mask                                        (0xFFFFFF00)
#define PCI_TRANSL0_rbus_transl_31to8_18(data)                                       (0xFFFFFF00&((data)<<8))
#define PCI_TRANSL0_rbus_transl_31to8_18_src(data)                                   ((0xFFFFFF00&(data))>>8)


#define PCI_MASK1                                                                    0x1801711C
#define PCI_MASK1_reg_addr                                                           "0xB801711C"
#define PCI_MASK1_reg                                                                0xB801711C
#define PCI_MASK1_inst_adr                                                           "0x0047"
#define PCI_MASK1_inst                                                               0x0047
#define PCI_MASK1_dbus_mask_31to28_1c_shift                                          (28)
#define PCI_MASK1_dbus_mask_31to28_1c_mask                                           (0xF0000000)
#define PCI_MASK1_dbus_mask_31to28_1c(data)                                          (0xF0000000&((data)<<28))
#define PCI_MASK1_dbus_mask_31to28_1c_src(data)                                      ((0xF0000000&(data))>>28)
#define PCI_MASK1_dbus_mask_27to8_1c_shift                                           (8)
#define PCI_MASK1_dbus_mask_27to8_1c_mask                                            (0x0FFFFF00)
#define PCI_MASK1_dbus_mask_27to8_1c(data)                                           (0x0FFFFF00&((data)<<8))
#define PCI_MASK1_dbus_mask_27to8_1c_src(data)                                       ((0x0FFFFF00&(data))>>8)


#define PCI_TRANSL1                                                                  0x18017120
#define PCI_TRANSL1_reg_addr                                                         "0xB8017120"
#define PCI_TRANSL1_reg                                                              0xB8017120
#define PCI_TRANSL1_inst_adr                                                         "0x0048"
#define PCI_TRANSL1_inst                                                             0x0048
#define PCI_TRANSL1_dbus_transl_27to8_20_shift                                       (8)
#define PCI_TRANSL1_dbus_transl_27to8_20_mask                                        (0x0FFFFF00)
#define PCI_TRANSL1_dbus_transl_27to8_20(data)                                       (0x0FFFFF00&((data)<<8))
#define PCI_TRANSL1_dbus_transl_27to8_20_src(data)                                   ((0x0FFFFF00&(data))>>8)


#define PCI_MASK2                                                                    0x18017124
#define PCI_MASK2_reg_addr                                                           "0xB8017124"
#define PCI_MASK2_reg                                                                0xB8017124
#define PCI_MASK2_inst_adr                                                           "0x0049"
#define PCI_MASK2_inst                                                               0x0049
#define PCI_MASK2_sbus_mask_31to28_24_shift                                          (28)
#define PCI_MASK2_sbus_mask_31to28_24_mask                                           (0xF0000000)
#define PCI_MASK2_sbus_mask_31to28_24(data)                                          (0xF0000000&((data)<<28))
#define PCI_MASK2_sbus_mask_31to28_24_src(data)                                      ((0xF0000000&(data))>>28)
#define PCI_MASK2_sbus_mask_27to8_24_shift                                           (8)
#define PCI_MASK2_sbus_mask_27to8_24_mask                                            (0x0FFFFF00)
#define PCI_MASK2_sbus_mask_27to8_24(data)                                           (0x0FFFFF00&((data)<<8))
#define PCI_MASK2_sbus_mask_27to8_24_src(data)                                       ((0x0FFFFF00&(data))>>8)


#define PCI_TRANSL2                                                                  0x18017128
#define PCI_TRANSL2_reg_addr                                                         "0xB8017128"
#define PCI_TRANSL2_reg                                                              0xB8017128
#define PCI_TRANSL2_inst_adr                                                         "0x004A"
#define PCI_TRANSL2_inst                                                             0x004A
#define PCI_TRANSL2_sbus_transl_27to8_28_shift                                       (8)
#define PCI_TRANSL2_sbus_transl_27to8_28_mask                                        (0x0FFFFF00)
#define PCI_TRANSL2_sbus_transl_27to8_28(data)                                       (0x0FFFFF00&((data)<<8))
#define PCI_TRANSL2_sbus_transl_27to8_28_src(data)                                   ((0x0FFFFF00&(data))>>8)


#define PCI_MST_ERR0                                                                 0x1801712C
#define PCI_MST_ERR0_reg_addr                                                        "0xB801712C"
#define PCI_MST_ERR0_reg                                                             0xB801712C
#define PCI_MST_ERR0_inst_adr                                                        "0x004B"
#define PCI_MST_ERR0_inst                                                            0x004B
#define PCI_MST_ERR0_addr_error_31to0_2c_shift                                       (0)
#define PCI_MST_ERR0_addr_error_31to0_2c_mask                                        (0xFFFFFFFF)
#define PCI_MST_ERR0_addr_error_31to0_2c(data)                                       (0xFFFFFFFF&((data)<<0))
#define PCI_MST_ERR0_addr_error_31to0_2c_src(data)                                   ((0xFFFFFFFF&(data))>>0)


#define PCI_MST_ERR1                                                                 0x18017130
#define PCI_MST_ERR1_reg_addr                                                        "0xB8017130"
#define PCI_MST_ERR1_reg                                                             0xB8017130
#define PCI_MST_ERR1_inst_adr                                                        "0x004C"
#define PCI_MST_ERR1_inst                                                            0x004C
#define PCI_MST_ERR1_cmd_error_3to0_30_shift                                         (0)
#define PCI_MST_ERR1_cmd_error_3to0_30_mask                                          (0x0000000F)
#define PCI_MST_ERR1_cmd_error_3to0_30(data)                                         (0x0000000F&((data)<<0))
#define PCI_MST_ERR1_cmd_error_3to0_30_src(data)                                     ((0x0000000F&(data))>>0)


#define PCI_SLV_ERR0                                                                 0x18017134
#define PCI_SLV_ERR0_reg_addr                                                        "0xB8017134"
#define PCI_SLV_ERR0_reg                                                             0xB8017134
#define PCI_SLV_ERR0_inst_adr                                                        "0x004D"
#define PCI_SLV_ERR0_inst                                                            0x004D
#define PCI_SLV_ERR0_addr_error_31to0_34_shift                                       (0)
#define PCI_SLV_ERR0_addr_error_31to0_34_mask                                        (0xFFFFFFFF)
#define PCI_SLV_ERR0_addr_error_31to0_34(data)                                       (0xFFFFFFFF&((data)<<0))
#define PCI_SLV_ERR0_addr_error_31to0_34_src(data)                                   ((0xFFFFFFFF&(data))>>0)


#define PCI_SLV_ERR1                                                                 0x18017138
#define PCI_SLV_ERR1_reg_addr                                                        "0xB8017138"
#define PCI_SLV_ERR1_reg                                                             0xB8017138
#define PCI_SLV_ERR1_inst_adr                                                        "0x004E"
#define PCI_SLV_ERR1_inst                                                            0x004E
#define PCI_SLV_ERR1_cmd_error_3to0_38_shift                                         (0)
#define PCI_SLV_ERR1_cmd_error_3to0_38_mask                                          (0x0000000F)
#define PCI_SLV_ERR1_cmd_error_3to0_38(data)                                         (0x0000000F&((data)<<0))
#define PCI_SLV_ERR1_cmd_error_3to0_38_src(data)                                     ((0x0000000F&(data))>>0)


#define PCI_MON_ST                                                                   0x1801713C
#define PCI_MON_ST_reg_addr                                                          "0xB801713C"
#define PCI_MON_ST_reg                                                               0xB801713C
#define PCI_MON_ST_inst_adr                                                          "0x004F"
#define PCI_MON_ST_inst                                                              0x004F
#define PCI_MON_ST_error_clear_16_40_shift                                           (16)
#define PCI_MON_ST_error_clear_16_40_mask                                            (0x00010000)
#define PCI_MON_ST_error_clear_16_40(data)                                           (0x00010000&((data)<<16))
#define PCI_MON_ST_error_clear_16_40_src(data)                                       ((0x00010000&(data))>>16)
#define PCI_MON_ST_erro_msn_14to13_40_shift                                          (13)
#define PCI_MON_ST_erro_msn_14to13_40_mask                                           (0x00006000)
#define PCI_MON_ST_erro_msn_14to13_40(data)                                          (0x00006000&((data)<<13))
#define PCI_MON_ST_erro_msn_14to13_40_src(data)                                      ((0x00006000&(data))>>13)
#define PCI_MON_ST_pci_stop_12_3c_shift                                              (12)
#define PCI_MON_ST_pci_stop_12_3c_mask                                               (0x00001000)
#define PCI_MON_ST_pci_stop_12_3c(data)                                              (0x00001000&((data)<<12))
#define PCI_MON_ST_pci_stop_12_3c_src(data)                                          ((0x00001000&(data))>>12)
#define PCI_MON_ST_pci_trdy_11_3c_shift                                              (11)
#define PCI_MON_ST_pci_trdy_11_3c_mask                                               (0x00000800)
#define PCI_MON_ST_pci_trdy_11_3c(data)                                              (0x00000800&((data)<<11))
#define PCI_MON_ST_pci_trdy_11_3c_src(data)                                          ((0x00000800&(data))>>11)
#define PCI_MON_ST_pci_devsel_10_3c_shift                                            (10)
#define PCI_MON_ST_pci_devsel_10_3c_mask                                             (0x00000400)
#define PCI_MON_ST_pci_devsel_10_3c(data)                                            (0x00000400&((data)<<10))
#define PCI_MON_ST_pci_devsel_10_3c_src(data)                                        ((0x00000400&(data))>>10)
#define PCI_MON_ST_pci_irdy_9_3c_shift                                               (9)
#define PCI_MON_ST_pci_irdy_9_3c_mask                                                (0x00000200)
#define PCI_MON_ST_pci_irdy_9_3c(data)                                               (0x00000200&((data)<<9))
#define PCI_MON_ST_pci_irdy_9_3c_src(data)                                           ((0x00000200&(data))>>9)
#define PCI_MON_ST_pci_frame_8_3c_shift                                              (8)
#define PCI_MON_ST_pci_frame_8_3c_mask                                               (0x00000100)
#define PCI_MON_ST_pci_frame_8_3c(data)                                              (0x00000100&((data)<<8))
#define PCI_MON_ST_pci_frame_8_3c_src(data)                                          ((0x00000100&(data))>>8)


#define PCI_TMP_REG_0                                                                0x18017140
#define PCI_TMP_REG_1                                                                0x18017144
#define PCI_TMP_REG_2                                                                0x18017148
#define PCI_TMP_REG_3                                                                0x1801714C
#define PCI_TMP_REG_0_reg_addr                                                       "0xB8017140"
#define PCI_TMP_REG_1_reg_addr                                                       "0xB8017144"
#define PCI_TMP_REG_2_reg_addr                                                       "0xB8017148"
#define PCI_TMP_REG_3_reg_addr                                                       "0xB801714C"
#define PCI_TMP_REG_0_reg                                                            0xB8017140
#define PCI_TMP_REG_1_reg                                                            0xB8017144
#define PCI_TMP_REG_2_reg                                                            0xB8017148
#define PCI_TMP_REG_3_reg                                                            0xB801714C
#define PCI_TMP_REG_0_inst_adr                                                       "0x0050"
#define PCI_TMP_REG_1_inst_adr                                                       "0x0051"
#define PCI_TMP_REG_2_inst_adr                                                       "0x0052"
#define PCI_TMP_REG_3_inst_adr                                                       "0x0053"
#define PCI_TMP_REG_0_inst                                                           0x0050
#define PCI_TMP_REG_1_inst                                                           0x0051
#define PCI_TMP_REG_2_inst                                                           0x0052
#define PCI_TMP_REG_3_inst                                                           0x0053
#define PCI_TMP_REG_test_reg_shift                                                   (0)
#define PCI_TMP_REG_test_reg_mask                                                    (0xFFFFFFFF)
#define PCI_TMP_REG_test_reg(data)                                                   (0xFFFFFFFF&((data)<<0))
#define PCI_TMP_REG_test_reg_src(data)                                               ((0xFFFFFFFF&(data))>>0)


#define CFG_00H                                                                      0x18017200
#define CFG_00H_reg_addr                                                             "0xB8017200"
#define CFG_00H_reg                                                                  0xB8017200
#define CFG_00H_inst_adr                                                             "0x0080"
#define CFG_00H_inst                                                                 0x0080
#define CFG_00H_dev_id_shift                                                         (16)
#define CFG_00H_dev_id_mask                                                          (0xFFFF0000)
#define CFG_00H_dev_id(data)                                                         (0xFFFF0000&((data)<<16))
#define CFG_00H_dev_id_src(data)                                                     ((0xFFFF0000&(data))>>16)
#define CFG_00H_ven_id_shift                                                         (0)
#define CFG_00H_ven_id_mask                                                          (0x0000FFFF)
#define CFG_00H_ven_id(data)                                                         (0x0000FFFF&((data)<<0))
#define CFG_00H_ven_id_src(data)                                                     ((0x0000FFFF&(data))>>0)


#define CFG_04H                                                                      0x18017204
#define CFG_04H_reg_addr                                                             "0xB8017204"
#define CFG_04H_reg                                                                  0xB8017204
#define CFG_04H_inst_adr                                                             "0x0081"
#define CFG_04H_inst                                                                 0x0081
#define CFG_04H_detec_par_error_shift                                                (31)
#define CFG_04H_detec_par_error_mask                                                 (0x80000000)
#define CFG_04H_detec_par_error(data)                                                (0x80000000&((data)<<31))
#define CFG_04H_detec_par_error_src(data)                                            ((0x80000000&(data))>>31)
#define CFG_04H_signal_sys_error_shift                                               (30)
#define CFG_04H_signal_sys_error_mask                                                (0x40000000)
#define CFG_04H_signal_sys_error(data)                                               (0x40000000&((data)<<30))
#define CFG_04H_signal_sys_error_src(data)                                           ((0x40000000&(data))>>30)
#define CFG_04H_rec_master_abort_shift                                               (29)
#define CFG_04H_rec_master_abort_mask                                                (0x20000000)
#define CFG_04H_rec_master_abort(data)                                               (0x20000000&((data)<<29))
#define CFG_04H_rec_master_abort_src(data)                                           ((0x20000000&(data))>>29)
#define CFG_04H_rec_target_abort_shift                                               (28)
#define CFG_04H_rec_target_abort_mask                                                (0x10000000)
#define CFG_04H_rec_target_abort(data)                                               (0x10000000&((data)<<28))
#define CFG_04H_rec_target_abort_src(data)                                           ((0x10000000&(data))>>28)
#define CFG_04H_sig_tar_abort_shift                                                  (27)
#define CFG_04H_sig_tar_abort_mask                                                   (0x08000000)
#define CFG_04H_sig_tar_abort(data)                                                  (0x08000000&((data)<<27))
#define CFG_04H_sig_tar_abort_src(data)                                              ((0x08000000&(data))>>27)
#define CFG_04H_devsel_timer_shift                                                   (25)
#define CFG_04H_devsel_timer_mask                                                    (0x06000000)
#define CFG_04H_devsel_timer(data)                                                   (0x06000000&((data)<<25))
#define CFG_04H_devsel_timer_src(data)                                               ((0x06000000&(data))>>25)
#define CFG_04H_master_par_error_shift                                               (24)
#define CFG_04H_master_par_error_mask                                                (0x01000000)
#define CFG_04H_master_par_error(data)                                               (0x01000000&((data)<<24))
#define CFG_04H_master_par_error_src(data)                                           ((0x01000000&(data))>>24)
#define CFG_04H_fast_b2b_cap_shift                                                   (23)
#define CFG_04H_fast_b2b_cap_mask                                                    (0x00800000)
#define CFG_04H_fast_b2b_cap(data)                                                   (0x00800000&((data)<<23))
#define CFG_04H_fast_b2b_cap_src(data)                                               ((0x00800000&(data))>>23)
#define CFG_04H_a66mhz_shift                                                         (21)
#define CFG_04H_a66mhz_mask                                                          (0x00200000)
#define CFG_04H_a66mhz(data)                                                         (0x00200000&((data)<<21))
#define CFG_04H_a66mhz_src(data)                                                     ((0x00200000&(data))>>21)
#define CFG_04H_capability_list_shift                                                (20)
#define CFG_04H_capability_list_mask                                                 (0x00100000)
#define CFG_04H_capability_list(data)                                                (0x00100000&((data)<<20))
#define CFG_04H_capability_list_src(data)                                            ((0x00100000&(data))>>20)
#define CFG_04H_int_status_shift                                                     (19)
#define CFG_04H_int_status_mask                                                      (0x00080000)
#define CFG_04H_int_status(data)                                                     (0x00080000&((data)<<19))
#define CFG_04H_int_status_src(data)                                                 ((0x00080000&(data))>>19)
#define CFG_04H_interrupt_disable_shift                                              (10)
#define CFG_04H_interrupt_disable_mask                                               (0x00000400)
#define CFG_04H_interrupt_disable(data)                                              (0x00000400&((data)<<10))
#define CFG_04H_interrupt_disable_src(data)                                          ((0x00000400&(data))>>10)
#define CFG_04H_fast_b2b_shift                                                       (9)
#define CFG_04H_fast_b2b_mask                                                        (0x00000200)
#define CFG_04H_fast_b2b(data)                                                       (0x00000200&((data)<<9))
#define CFG_04H_fast_b2b_src(data)                                                   ((0x00000200&(data))>>9)
#define CFG_04H_serr_enable_shift                                                    (8)
#define CFG_04H_serr_enable_mask                                                     (0x00000100)
#define CFG_04H_serr_enable(data)                                                    (0x00000100&((data)<<8))
#define CFG_04H_serr_enable_src(data)                                                ((0x00000100&(data))>>8)
#define CFG_04H_parity_error_resp_shift                                              (6)
#define CFG_04H_parity_error_resp_mask                                               (0x00000040)
#define CFG_04H_parity_error_resp(data)                                              (0x00000040&((data)<<6))
#define CFG_04H_parity_error_resp_src(data)                                          ((0x00000040&(data))>>6)
#define CFG_04H_mwie_shift                                                           (4)
#define CFG_04H_mwie_mask                                                            (0x00000010)
#define CFG_04H_mwie(data)                                                           (0x00000010&((data)<<4))
#define CFG_04H_mwie_src(data)                                                       ((0x00000010&(data))>>4)
#define CFG_04H_bus_master_shift                                                     (2)
#define CFG_04H_bus_master_mask                                                      (0x00000004)
#define CFG_04H_bus_master(data)                                                     (0x00000004&((data)<<2))
#define CFG_04H_bus_master_src(data)                                                 ((0x00000004&(data))>>2)
#define CFG_04H_mm_space_shift                                                       (1)
#define CFG_04H_mm_space_mask                                                        (0x00000002)
#define CFG_04H_mm_space(data)                                                       (0x00000002&((data)<<1))
#define CFG_04H_mm_space_src(data)                                                   ((0x00000002&(data))>>1)
#define CFG_04H_io_space_shift                                                       (0)
#define CFG_04H_io_space_mask                                                        (0x00000001)
#define CFG_04H_io_space(data)                                                       (0x00000001&((data)<<0))
#define CFG_04H_io_space_src(data)                                                   ((0x00000001&(data))>>0)


#define CFG_08H                                                                      0x18017208
#define CFG_08H_reg_addr                                                             "0xB8017208"
#define CFG_08H_reg                                                                  0xB8017208
#define CFG_08H_inst_adr                                                             "0x0082"
#define CFG_08H_inst                                                                 0x0082
#define CFG_08H_class_code_shift                                                     (8)
#define CFG_08H_class_code_mask                                                      (0xFFFFFF00)
#define CFG_08H_class_code(data)                                                     (0xFFFFFF00&((data)<<8))
#define CFG_08H_class_code_src(data)                                                 ((0xFFFFFF00&(data))>>8)
#define CFG_08H_Rev_id_shift                                                         (0)
#define CFG_08H_Rev_id_mask                                                          (0x000000FF)
#define CFG_08H_Rev_id(data)                                                         (0x000000FF&((data)<<0))
#define CFG_08H_Rev_id_src(data)                                                     ((0x000000FF&(data))>>0)


#define CFG_0CH                                                                      0x1801720C
#define CFG_0CH_reg_addr                                                             "0xB801720C"
#define CFG_0CH_reg                                                                  0xB801720C
#define CFG_0CH_inst_adr                                                             "0x0083"
#define CFG_0CH_inst                                                                 0x0083
#define CFG_0CH_latency_timer_shift                                                  (8)
#define CFG_0CH_latency_timer_mask                                                   (0x0000FF00)
#define CFG_0CH_latency_timer(data)                                                  (0x0000FF00&((data)<<8))
#define CFG_0CH_latency_timer_src(data)                                              ((0x0000FF00&(data))>>8)
#define CFG_0CH_cacheline_size_shift                                                 (0)
#define CFG_0CH_cacheline_size_mask                                                  (0x000000FF)
#define CFG_0CH_cacheline_size(data)                                                 (0x000000FF&((data)<<0))
#define CFG_0CH_cacheline_size_src(data)                                             ((0x000000FF&(data))>>0)


#define CFG_10H                                                                      0x18017210
#define CFG_10H_reg_addr                                                             "0xB8017210"
#define CFG_10H_reg                                                                  0xB8017210
#define CFG_10H_inst_adr                                                             "0x0084"
#define CFG_10H_inst                                                                 0x0084
#define CFG_10H_reg_ba_shift                                                         (5)
#define CFG_10H_reg_ba_mask                                                          (0xFFFFFFE0)
#define CFG_10H_reg_ba(data)                                                         (0xFFFFFFE0&((data)<<5))
#define CFG_10H_reg_ba_src(data)                                                     ((0xFFFFFFE0&(data))>>5)
#define CFG_10H_space_bit_shift                                                      (0)
#define CFG_10H_space_bit_mask                                                       (0x00000001)
#define CFG_10H_space_bit(data)                                                      (0x00000001&((data)<<0))
#define CFG_10H_space_bit_src(data)                                                  ((0x00000001&(data))>>0)


#define CFG_14H                                                                      0x18017214
#define CFG_14H_reg_addr                                                             "0xB8017214"
#define CFG_14H_reg                                                                  0xB8017214
#define CFG_14H_inst_adr                                                             "0x0085"
#define CFG_14H_inst                                                                 0x0085
#define CFG_14H_dbus_ba_shift                                                        (8)
#define CFG_14H_dbus_ba_mask                                                         (0xFFFFFF00)
#define CFG_14H_dbus_ba(data)                                                        (0xFFFFFF00&((data)<<8))
#define CFG_14H_dbus_ba_src(data)                                                    ((0xFFFFFF00&(data))>>8)
#define CFG_14H_space_bit_shift                                                      (0)
#define CFG_14H_space_bit_mask                                                       (0x00000001)
#define CFG_14H_space_bit(data)                                                      (0x00000001&((data)<<0))
#define CFG_14H_space_bit_src(data)                                                  ((0x00000001&(data))>>0)


#define CFG_18H                                                                      0x18017218
#define CFG_18H_reg_addr                                                             "0xB8017218"
#define CFG_18H_reg                                                                  0xB8017218
#define CFG_18H_inst_adr                                                             "0x0086"
#define CFG_18H_inst                                                                 0x0086
#define CFG_18H_rbus_ba_shift                                                        (8)
#define CFG_18H_rbus_ba_mask                                                         (0xFFFFFF00)
#define CFG_18H_rbus_ba(data)                                                        (0xFFFFFF00&((data)<<8))
#define CFG_18H_rbus_ba_src(data)                                                    ((0xFFFFFF00&(data))>>8)
#define CFG_18H_space_bit_shift                                                      (0)
#define CFG_18H_space_bit_mask                                                       (0x00000001)
#define CFG_18H_space_bit(data)                                                      (0x00000001&((data)<<0))
#define CFG_18H_space_bit_src(data)                                                  ((0x00000001&(data))>>0)


#define CFG_1CH                                                                      0x1801721C
#define CFG_1CH_reg_addr                                                             "0xB801721C"
#define CFG_1CH_reg                                                                  0xB801721C
#define CFG_1CH_inst_adr                                                             "0x0087"
#define CFG_1CH_inst                                                                 0x0087
#define CFG_1CH_sbus_ba_shift                                                        (8)
#define CFG_1CH_sbus_ba_mask                                                         (0xFFFFFF00)
#define CFG_1CH_sbus_ba(data)                                                        (0xFFFFFF00&((data)<<8))
#define CFG_1CH_sbus_ba_src(data)                                                    ((0xFFFFFF00&(data))>>8)
#define CFG_1CH_space_bit_shift                                                      (0)
#define CFG_1CH_space_bit_mask                                                       (0x00000001)
#define CFG_1CH_space_bit(data)                                                      (0x00000001&((data)<<0))
#define CFG_1CH_space_bit_src(data)                                                  ((0x00000001&(data))>>0)


#define CFG_2CH                                                                      0x1801722C
#define CFG_2CH_reg_addr                                                             "0xB801722C"
#define CFG_2CH_reg                                                                  0xB801722C
#define CFG_2CH_inst_adr                                                             "0x008B"
#define CFG_2CH_inst                                                                 0x008B
#define CFG_2CH_sub_id_shift                                                         (16)
#define CFG_2CH_sub_id_mask                                                          (0xFFFF0000)
#define CFG_2CH_sub_id(data)                                                         (0xFFFF0000&((data)<<16))
#define CFG_2CH_sub_id_src(data)                                                     ((0xFFFF0000&(data))>>16)
#define CFG_2CH_sub_ven_id_shift                                                     (0)
#define CFG_2CH_sub_ven_id_mask                                                      (0x0000FFFF)
#define CFG_2CH_sub_ven_id(data)                                                     (0x0000FFFF&((data)<<0))
#define CFG_2CH_sub_ven_id_src(data)                                                 ((0x0000FFFF&(data))>>0)


#define CFG_3CH                                                                      0x1801723C
#define CFG_3CH_reg_addr                                                             "0xB801723C"
#define CFG_3CH_reg                                                                  0xB801723C
#define CFG_3CH_inst_adr                                                             "0x008F"
#define CFG_3CH_inst                                                                 0x008F
#define CFG_3CH_max_Lat_shift                                                        (24)
#define CFG_3CH_max_Lat_mask                                                         (0xFF000000)
#define CFG_3CH_max_Lat(data)                                                        (0xFF000000&((data)<<24))
#define CFG_3CH_max_Lat_src(data)                                                    ((0xFF000000&(data))>>24)
#define CFG_3CH_min_gnt_shift                                                        (16)
#define CFG_3CH_min_gnt_mask                                                         (0x00FF0000)
#define CFG_3CH_min_gnt(data)                                                        (0x00FF0000&((data)<<16))
#define CFG_3CH_min_gnt_src(data)                                                    ((0x00FF0000&(data))>>16)
#define CFG_3CH_interrupt_pin_shift                                                  (8)
#define CFG_3CH_interrupt_pin_mask                                                   (0x0000FF00)
#define CFG_3CH_interrupt_pin(data)                                                  (0x0000FF00&((data)<<8))
#define CFG_3CH_interrupt_pin_src(data)                                              ((0x0000FF00&(data))>>8)
#define CFG_3CH_interrupt_line_shift                                                 (0)
#define CFG_3CH_interrupt_line_mask                                                  (0x000000FF)
#define CFG_3CH_interrupt_line(data)                                                 (0x000000FF&((data)<<0))
#define CFG_3CH_interrupt_line_src(data)                                             ((0x000000FF&(data))>>0)


#endif
