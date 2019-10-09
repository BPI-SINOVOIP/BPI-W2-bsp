/**************************************************************
// Spec Version                  : 0.0.1
// Parser Version                : MAR_Parser_1.0
// CModelGen Version             : 4.1 2009.03.10
// Naming Rule                   : Register_Name_reg
// Firmware Header Generate Date : 2009/5/9
***************************************************************/


#ifndef _PCIE_REG_H_INCLUDED_
#define _PCIE_REG_H_INCLUDED_
#ifdef  _PCIE_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     phy_mdio_oe:1;
unsigned int     phy_mdio_rstN:1;
unsigned int     app_init_rst:1;
unsigned int     reserved_1:6;
unsigned int     loopback_en:1;
unsigned int     dir_req_info_en:1;
unsigned int     rx_lane_reversal_en:1;
unsigned int     tx_lane_reversal_en:1;
unsigned int     indir_cfg_en:1;
unsigned int     dir_cfg_en:1;
unsigned int     rcv_addr0_en:1;
unsigned int     rcv_addr1_en:1;
unsigned int     app_ltssm_en:1;
unsigned int     rcv_trans_en:1;
}PCIE_SYS_CTR;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     pcie_legacy_msi_en:1;
unsigned int     pme_msi_intp_en:1;
unsigned int     aer_rc_err_msi_intp_en:1;
unsigned int     cfg_sys_err_rc_intp_en:1;
unsigned int     pm_to_ack_intp_en:1;
unsigned int     vendor_msg_intp_en:1;
unsigned int     rtgt_error_intp_en:1;
unsigned int     rtgt_timeout_intp_en:1;
unsigned int     rcpl_error_intp_en:1;
unsigned int     rcpl_timeout_intp_en:1;
unsigned int     dir_error_intp_en:1;
unsigned int     indir_cfg_intp_en:1;
unsigned int     indir_mio_intp_en:1;
}PCIE_INT_CTR;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     pcie_legacy_msi_int:1;
unsigned int     pm_to_ack_int:1;
unsigned int     cfg_sys_err_rc_int:1;
unsigned int     pcie_legacy_int:1;
unsigned int     cfg_radm_vendor_msg_int:1;
unsigned int     cfg_pme_msi:1;
unsigned int     cfg_pme_int:1;
unsigned int     cfg_aer_rc_err_msi:1;
unsigned int     cfg_aer_rc_err_int:1;
unsigned int     intp_rtgt:1;
unsigned int     intp_rcpl:1;
unsigned int     intp_dir_cfg:1;
unsigned int     intp_dir_mio:1;
unsigned int     intp_cfg:1;
unsigned int     intp_mio:1;
}PCIE_GNR_INT;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     intp_intd:1;
unsigned int     intp_intc:1;
unsigned int     intp_intb:1;
unsigned int     intp_inta:1;
}PCIE_PCIE_INT;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     dbi_io_access:1;
unsigned int     dbi_rom_access:1;
unsigned int     dbi_bar_num:3;
unsigned int     dbi_func_num:3;
unsigned int     dbi_cs2_access:1;
unsigned int     dbi_cmd_access:1;
}PCIE_DBI_CTR;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     req_info_align:1;
unsigned int     req_info_attr:2;
unsigned int     req_info_ep:1;
unsigned int     req_info_tc:3;
unsigned int     req_info_type:5;
unsigned int     req_info_fmt:2;
}PCIE_INDIR_CTR;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     req_info_align:1;
unsigned int     req_info_attr:2;
unsigned int     req_info_ep:1;
unsigned int     req_info_tc:3;
unsigned int     req_info_type:5;
unsigned int     req_info_fmt:2;
}PCIE_DIR_CTR;

typedef struct 
{
unsigned int     data:16;
unsigned int     phy_addr:3;
unsigned int     phy_reg_addr:5;
unsigned int     mdio_busy:1;
unsigned int     mdio_st:2;
unsigned int     mdio_rdy:1;
unsigned int     mclk_rate:2;
unsigned int     mdio_srst:1;
unsigned int     mdio_rdwr:1;
}PCIE_MDIO_CTR;

typedef struct 
{
unsigned int     rtrans_base_addr:32;
}PCIE_PCIE_BASE0;

typedef struct 
{
unsigned int     rtrans_base_addr:32;
}PCIE_PCIE_BASE1;

typedef struct 
{
unsigned int     rtrans_mask:32;
}PCIE_PCIE_MASK0;

typedef struct 
{
unsigned int     rtrans_mask:32;
}PCIE_PCIE_MASK1;

typedef struct 
{
unsigned int     rtrans_addr_in:32;
}PCIE_PCIE_TRAN0;

typedef struct 
{
unsigned int     rtrans_addr_in:32;
}PCIE_PCIE_TRAN1;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     go_ct:1;
}PCIE_CFG_CT;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     bus_num:8;
unsigned int     dev_num:5;
unsigned int     fun_num:3;
unsigned int     byte_cnt:4;
unsigned int     reserved_1:1;
unsigned int     error_en:1;
unsigned int     byte_en:1;
unsigned int     wrrd_en:1;
}PCIE_CFG_EN;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     error_st:1;
unsigned int     done_st:1;
}PCIE_CFG_ST;

typedef struct 
{
unsigned int     space_addr:32;
}PCIE_CFG_ADDR;

typedef struct 
{
unsigned int     space_wdata:32;
}PCIE_CFG_WDATA;

typedef struct 
{
unsigned int     space_rdata:32;
}PCIE_CFG_RDATA;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     go_ct:1;
}PCIE_MIO_CT;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     error_st:1;
unsigned int     done_st:1;
}PCIE_MIO_ST;

typedef struct 
{
unsigned int     timeout_cnt_value:24;
unsigned int     byte_cnt:4;
unsigned int     reserved_0:1;
unsigned int     error_en:1;
unsigned int     byte_en:1;
unsigned int     wrrd_en:1;
}PCIE_MIO_EN;

typedef struct 
{
unsigned int     pcie_addr:32;
}PCIE_MIO_ADDR;

typedef struct 
{
unsigned int     pcie_wdata:32;
}PCIE_MIO_WDATA;

typedef struct 
{
unsigned int     pcie_rdata:32;
}PCIE_MIO_RDATA;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     RX50_LINK:1;
unsigned int     POW_PCIEX:1;
unsigned int     SEL0_125M:1;
unsigned int     REG_PLLDVR:3;
unsigned int     CLK_SEL:1;
}PCIE_PHY_CTR;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     app_pmxmt_turnoff:1;
unsigned int     p1_clk_req_en:1;
unsigned int     low_power_enable:1;
unsigned int     sys_aux_pwr_det:1;
unsigned int     app_ready_enter_123:1;
unsigned int     app_req_exit_11:1;
unsigned int     app_req_enter_11:1;
}PCIE_PWR_CTR;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     dbg_sel1:6;
unsigned int     dbg_sel0:6;
unsigned int     dbg_en:1;
}PCIE_PCIE_DBG;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     cfg_rerror_st:1;
unsigned int     mio_rerror_st:1;
}PCIE_DIR_ST;

typedef struct 
{
unsigned int     timeout_cnt_value:24;
unsigned int     reserved_0:7;
unsigned int     timeout_en:1;
}PCIE_DIR_EN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rcpl_status:3;
unsigned int     rcpl_error_st:1;
unsigned int     tlp_abort_st:1;
unsigned int     dllp_abort_st:1;
unsigned int     ecrc_error_st:1;
unsigned int     rcpl_timeout_st:1;
}PCIE_RCPL_ST;

typedef struct 
{
unsigned int     nor_error_addr:32;
}PCIE_RCPL_ADR;

typedef struct 
{
unsigned int     to_error_addr:32;
}PCIE_RCPL_TOUT0;

typedef struct 
{
unsigned int     timeout_num:3;
unsigned int     timeout_tc:3;
unsigned int     timeout_attr:2;
unsigned int     timeout_len:12;
unsigned int     reserved_0:4;
unsigned int     timeout_tag:8;
}PCIE_RCPL_TOUT1;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     rcpl_compl_st:1;
unsigned int     tlp_abort_st:1;
unsigned int     dllp_abort_st:1;
unsigned int     ecrc_error_st:1;
unsigned int     rcpl_timeout_st:1;
}PCIE_RTGT_ST;

typedef struct 
{
unsigned int     nor_error_addr:32;
}PCIE_RTGT_ADR;

typedef struct 
{
unsigned int     to_error_addr:32;
}PCIE_RTGT_TOUT0;

typedef struct 
{
unsigned int     timeout_num:3;
unsigned int     timeout_tc:3;
unsigned int     timeout_attr:2;
unsigned int     timeout_len:12;
unsigned int     reserved_0:4;
unsigned int     timeout_tag:8;
}PCIE_RTGT_TOUT1;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     cfg_sys_err_rc:1;
}PCIE_AERRO_ST;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     cfg_aer_int_msg_num:5;
unsigned int     cfg_aer_rc_err_msi:1;
}PCIE_AEMSI_ST;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     radm_pm_to_ack:1;
}PCIE_PME_ST;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     cfg_cap_int_msg_num:5;
unsigned int     cfg_pme_msi:1;
}PCIE_PMMSI_ST;

typedef struct 
{
unsigned int     radm_msg_req_id:16;
unsigned int     reserved_0:15;
unsigned int     radm_vendor_msg:1;
}PCIE_VEN_MSG0;

typedef struct 
{
unsigned int     radm_msg_payload:32;
}PCIE_VEN_MSG1;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     rdlh_link_up:1;
unsigned int     pm_xtlh_block_tlp:1;
unsigned int     cfg_bus_master_en:1;
unsigned int     cfg_pm_no_soft_rst:1;
unsigned int     xmlh_link_up:1;
unsigned int     link_req_rst_not:1;
unsigned int     xmlh_ltssm_state:5;
unsigned int     pm_curnt_state:3;
unsigned int     clk_req_n:1;
}PCIE_MAC_ST;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     unlock_msg_trigger:1;
}PCIE_UNLOCK_MSG;

typedef struct 
{
unsigned int     reg1:16;
unsigned int     reg0:16;
}PCIE_SCTCH;

typedef struct 
{
unsigned int     rw_data:32;
}PCIE_LOOP_DATA;

typedef struct 
{
unsigned int     msi_check_addr:30;
unsigned int     reserved_0:2;
}PCIE_MSI_TRAN;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     msi_data_st:1;
unsigned int     msi_data:16;
}PCIE_MSI_DATA;

typedef struct 
{
unsigned int     test_reg:32;
}PCIE_TMP_REG;

#endif

#define PCIE_SYS_CTR                                                                 0x18017A00
#define PCIE_SYS_CTR_reg_addr                                                        "0xB8017A00"
#define PCIE_SYS_CTR_reg                                                             0xB8017A00
#define set_PCIE_SYS_CTR_reg(data)   (*((volatile unsigned int*) PCIE_SYS_CTR_reg)=data)
#define get_PCIE_SYS_CTR_reg   (*((volatile unsigned int*) PCIE_SYS_CTR_reg))
#define PCIE_SYS_CTR_inst_adr                                                        "0x0080"
#define PCIE_SYS_CTR_inst                                                            0x0080
#define PCIE_SYS_CTR_phy_mdio_oe_shift                                               (18)
#define PCIE_SYS_CTR_phy_mdio_oe_mask                                                (0x00040000)
#define PCIE_SYS_CTR_phy_mdio_oe(data)                                               (0x00040000&((data)<<18))
#define PCIE_SYS_CTR_phy_mdio_oe_src(data)                                           ((0x00040000&(data))>>18)
#define PCIE_SYS_CTR_get_phy_mdio_oe(data)                                           ((0x00040000&(data))>>18)
#define PCIE_SYS_CTR_phy_mdio_rstN_shift                                             (17)
#define PCIE_SYS_CTR_phy_mdio_rstN_mask                                              (0x00020000)
#define PCIE_SYS_CTR_phy_mdio_rstN(data)                                             (0x00020000&((data)<<17))
#define PCIE_SYS_CTR_phy_mdio_rstN_src(data)                                         ((0x00020000&(data))>>17)
#define PCIE_SYS_CTR_get_phy_mdio_rstN(data)                                         ((0x00020000&(data))>>17)
#define PCIE_SYS_CTR_app_init_rst_shift                                              (16)
#define PCIE_SYS_CTR_app_init_rst_mask                                               (0x00010000)
#define PCIE_SYS_CTR_app_init_rst(data)                                              (0x00010000&((data)<<16))
#define PCIE_SYS_CTR_app_init_rst_src(data)                                          ((0x00010000&(data))>>16)
#define PCIE_SYS_CTR_get_app_init_rst(data)                                          ((0x00010000&(data))>>16)
#define PCIE_SYS_CTR_loopback_en_shift                                               (9)
#define PCIE_SYS_CTR_loopback_en_mask                                                (0x00000200)
#define PCIE_SYS_CTR_loopback_en(data)                                               (0x00000200&((data)<<9))
#define PCIE_SYS_CTR_loopback_en_src(data)                                           ((0x00000200&(data))>>9)
#define PCIE_SYS_CTR_get_loopback_en(data)                                           ((0x00000200&(data))>>9)
#define PCIE_SYS_CTR_dir_req_info_en_shift                                           (8)
#define PCIE_SYS_CTR_dir_req_info_en_mask                                            (0x00000100)
#define PCIE_SYS_CTR_dir_req_info_en(data)                                           (0x00000100&((data)<<8))
#define PCIE_SYS_CTR_dir_req_info_en_src(data)                                       ((0x00000100&(data))>>8)
#define PCIE_SYS_CTR_get_dir_req_info_en(data)                                       ((0x00000100&(data))>>8)
#define PCIE_SYS_CTR_rx_lane_reversal_en_shift                                       (7)
#define PCIE_SYS_CTR_rx_lane_reversal_en_mask                                        (0x00000080)
#define PCIE_SYS_CTR_rx_lane_reversal_en(data)                                       (0x00000080&((data)<<7))
#define PCIE_SYS_CTR_rx_lane_reversal_en_src(data)                                   ((0x00000080&(data))>>7)
#define PCIE_SYS_CTR_get_rx_lane_reversal_en(data)                                   ((0x00000080&(data))>>7)
#define PCIE_SYS_CTR_tx_lane_reversal_en_shift                                       (6)
#define PCIE_SYS_CTR_tx_lane_reversal_en_mask                                        (0x00000040)
#define PCIE_SYS_CTR_tx_lane_reversal_en(data)                                       (0x00000040&((data)<<6))
#define PCIE_SYS_CTR_tx_lane_reversal_en_src(data)                                   ((0x00000040&(data))>>6)
#define PCIE_SYS_CTR_get_tx_lane_reversal_en(data)                                   ((0x00000040&(data))>>6)
#define PCIE_SYS_CTR_indir_cfg_en_shift                                              (5)
#define PCIE_SYS_CTR_indir_cfg_en_mask                                               (0x00000020)
#define PCIE_SYS_CTR_indir_cfg_en(data)                                              (0x00000020&((data)<<5))
#define PCIE_SYS_CTR_indir_cfg_en_src(data)                                          ((0x00000020&(data))>>5)
#define PCIE_SYS_CTR_get_indir_cfg_en(data)                                          ((0x00000020&(data))>>5)
#define PCIE_SYS_CTR_dir_cfg_en_shift                                                (4)
#define PCIE_SYS_CTR_dir_cfg_en_mask                                                 (0x00000010)
#define PCIE_SYS_CTR_dir_cfg_en(data)                                                (0x00000010&((data)<<4))
#define PCIE_SYS_CTR_dir_cfg_en_src(data)                                            ((0x00000010&(data))>>4)
#define PCIE_SYS_CTR_get_dir_cfg_en(data)                                            ((0x00000010&(data))>>4)
#define PCIE_SYS_CTR_rcv_addr0_en_shift                                              (3)
#define PCIE_SYS_CTR_rcv_addr0_en_mask                                               (0x00000008)
#define PCIE_SYS_CTR_rcv_addr0_en(data)                                              (0x00000008&((data)<<3))
#define PCIE_SYS_CTR_rcv_addr0_en_src(data)                                          ((0x00000008&(data))>>3)
#define PCIE_SYS_CTR_get_rcv_addr0_en(data)                                          ((0x00000008&(data))>>3)
#define PCIE_SYS_CTR_rcv_addr1_en_shift                                              (2)
#define PCIE_SYS_CTR_rcv_addr1_en_mask                                               (0x00000004)
#define PCIE_SYS_CTR_rcv_addr1_en(data)                                              (0x00000004&((data)<<2))
#define PCIE_SYS_CTR_rcv_addr1_en_src(data)                                          ((0x00000004&(data))>>2)
#define PCIE_SYS_CTR_get_rcv_addr1_en(data)                                          ((0x00000004&(data))>>2)
#define PCIE_SYS_CTR_app_ltssm_en_shift                                              (1)
#define PCIE_SYS_CTR_app_ltssm_en_mask                                               (0x00000002)
#define PCIE_SYS_CTR_app_ltssm_en(data)                                              (0x00000002&((data)<<1))
#define PCIE_SYS_CTR_app_ltssm_en_src(data)                                          ((0x00000002&(data))>>1)
#define PCIE_SYS_CTR_get_app_ltssm_en(data)                                          ((0x00000002&(data))>>1)
#define PCIE_SYS_CTR_rcv_trans_en_shift                                              (0)
#define PCIE_SYS_CTR_rcv_trans_en_mask                                               (0x00000001)
#define PCIE_SYS_CTR_rcv_trans_en(data)                                              (0x00000001&((data)<<0))
#define PCIE_SYS_CTR_rcv_trans_en_src(data)                                          ((0x00000001&(data))>>0)
#define PCIE_SYS_CTR_get_rcv_trans_en(data)                                          ((0x00000001&(data))>>0)


#define PCIE_INT_CTR                                                                 0x18017A04
#define PCIE_INT_CTR_reg_addr                                                        "0xB8017A04"
#define PCIE_INT_CTR_reg                                                             0xB8017A04
#define set_PCIE_INT_CTR_reg(data)   (*((volatile unsigned int*) PCIE_INT_CTR_reg)=data)
#define get_PCIE_INT_CTR_reg   (*((volatile unsigned int*) PCIE_INT_CTR_reg))
#define PCIE_INT_CTR_inst_adr                                                        "0x0081"
#define PCIE_INT_CTR_inst                                                            0x0081
#define PCIE_INT_CTR_pcie_legacy_msi_en_shift                                        (12)
#define PCIE_INT_CTR_pcie_legacy_msi_en_mask                                         (0x00001000)
#define PCIE_INT_CTR_pcie_legacy_msi_en(data)                                        (0x00001000&((data)<<12))
#define PCIE_INT_CTR_pcie_legacy_msi_en_src(data)                                    ((0x00001000&(data))>>12)
#define PCIE_INT_CTR_get_pcie_legacy_msi_en(data)                                    ((0x00001000&(data))>>12)
#define PCIE_INT_CTR_pme_msi_intp_en_shift                                           (11)
#define PCIE_INT_CTR_pme_msi_intp_en_mask                                            (0x00000800)
#define PCIE_INT_CTR_pme_msi_intp_en(data)                                           (0x00000800&((data)<<11))
#define PCIE_INT_CTR_pme_msi_intp_en_src(data)                                       ((0x00000800&(data))>>11)
#define PCIE_INT_CTR_get_pme_msi_intp_en(data)                                       ((0x00000800&(data))>>11)
#define PCIE_INT_CTR_aer_rc_err_msi_intp_en_shift                                    (10)
#define PCIE_INT_CTR_aer_rc_err_msi_intp_en_mask                                     (0x00000400)
#define PCIE_INT_CTR_aer_rc_err_msi_intp_en(data)                                    (0x00000400&((data)<<10))
#define PCIE_INT_CTR_aer_rc_err_msi_intp_en_src(data)                                ((0x00000400&(data))>>10)
#define PCIE_INT_CTR_get_aer_rc_err_msi_intp_en(data)                                ((0x00000400&(data))>>10)
#define PCIE_INT_CTR_cfg_sys_err_rc_intp_en_shift                                    (9)
#define PCIE_INT_CTR_cfg_sys_err_rc_intp_en_mask                                     (0x00000200)
#define PCIE_INT_CTR_cfg_sys_err_rc_intp_en(data)                                    (0x00000200&((data)<<9))
#define PCIE_INT_CTR_cfg_sys_err_rc_intp_en_src(data)                                ((0x00000200&(data))>>9)
#define PCIE_INT_CTR_get_cfg_sys_err_rc_intp_en(data)                                ((0x00000200&(data))>>9)
#define PCIE_INT_CTR_pm_to_ack_intp_en_shift                                         (8)
#define PCIE_INT_CTR_pm_to_ack_intp_en_mask                                          (0x00000100)
#define PCIE_INT_CTR_pm_to_ack_intp_en(data)                                         (0x00000100&((data)<<8))
#define PCIE_INT_CTR_pm_to_ack_intp_en_src(data)                                     ((0x00000100&(data))>>8)
#define PCIE_INT_CTR_get_pm_to_ack_intp_en(data)                                     ((0x00000100&(data))>>8)
#define PCIE_INT_CTR_vendor_msg_intp_en_shift                                        (7)
#define PCIE_INT_CTR_vendor_msg_intp_en_mask                                         (0x00000080)
#define PCIE_INT_CTR_vendor_msg_intp_en(data)                                        (0x00000080&((data)<<7))
#define PCIE_INT_CTR_vendor_msg_intp_en_src(data)                                    ((0x00000080&(data))>>7)
#define PCIE_INT_CTR_get_vendor_msg_intp_en(data)                                    ((0x00000080&(data))>>7)
#define PCIE_INT_CTR_rtgt_error_intp_en_shift                                        (6)
#define PCIE_INT_CTR_rtgt_error_intp_en_mask                                         (0x00000040)
#define PCIE_INT_CTR_rtgt_error_intp_en(data)                                        (0x00000040&((data)<<6))
#define PCIE_INT_CTR_rtgt_error_intp_en_src(data)                                    ((0x00000040&(data))>>6)
#define PCIE_INT_CTR_get_rtgt_error_intp_en(data)                                    ((0x00000040&(data))>>6)
#define PCIE_INT_CTR_rtgt_timeout_intp_en_shift                                      (5)
#define PCIE_INT_CTR_rtgt_timeout_intp_en_mask                                       (0x00000020)
#define PCIE_INT_CTR_rtgt_timeout_intp_en(data)                                      (0x00000020&((data)<<5))
#define PCIE_INT_CTR_rtgt_timeout_intp_en_src(data)                                  ((0x00000020&(data))>>5)
#define PCIE_INT_CTR_get_rtgt_timeout_intp_en(data)                                  ((0x00000020&(data))>>5)
#define PCIE_INT_CTR_rcpl_error_intp_en_shift                                        (4)
#define PCIE_INT_CTR_rcpl_error_intp_en_mask                                         (0x00000010)
#define PCIE_INT_CTR_rcpl_error_intp_en(data)                                        (0x00000010&((data)<<4))
#define PCIE_INT_CTR_rcpl_error_intp_en_src(data)                                    ((0x00000010&(data))>>4)
#define PCIE_INT_CTR_get_rcpl_error_intp_en(data)                                    ((0x00000010&(data))>>4)
#define PCIE_INT_CTR_rcpl_timeout_intp_en_shift                                      (3)
#define PCIE_INT_CTR_rcpl_timeout_intp_en_mask                                       (0x00000008)
#define PCIE_INT_CTR_rcpl_timeout_intp_en(data)                                      (0x00000008&((data)<<3))
#define PCIE_INT_CTR_rcpl_timeout_intp_en_src(data)                                  ((0x00000008&(data))>>3)
#define PCIE_INT_CTR_get_rcpl_timeout_intp_en(data)                                  ((0x00000008&(data))>>3)
#define PCIE_INT_CTR_dir_error_intp_en_shift                                         (2)
#define PCIE_INT_CTR_dir_error_intp_en_mask                                          (0x00000004)
#define PCIE_INT_CTR_dir_error_intp_en(data)                                         (0x00000004&((data)<<2))
#define PCIE_INT_CTR_dir_error_intp_en_src(data)                                     ((0x00000004&(data))>>2)
#define PCIE_INT_CTR_get_dir_error_intp_en(data)                                     ((0x00000004&(data))>>2)
#define PCIE_INT_CTR_indir_cfg_intp_en_shift                                         (1)
#define PCIE_INT_CTR_indir_cfg_intp_en_mask                                          (0x00000002)
#define PCIE_INT_CTR_indir_cfg_intp_en(data)                                         (0x00000002&((data)<<1))
#define PCIE_INT_CTR_indir_cfg_intp_en_src(data)                                     ((0x00000002&(data))>>1)
#define PCIE_INT_CTR_get_indir_cfg_intp_en(data)                                     ((0x00000002&(data))>>1)
#define PCIE_INT_CTR_indir_mio_intp_en_shift                                         (0)
#define PCIE_INT_CTR_indir_mio_intp_en_mask                                          (0x00000001)
#define PCIE_INT_CTR_indir_mio_intp_en(data)                                         (0x00000001&((data)<<0))
#define PCIE_INT_CTR_indir_mio_intp_en_src(data)                                     ((0x00000001&(data))>>0)
#define PCIE_INT_CTR_get_indir_mio_intp_en(data)                                     ((0x00000001&(data))>>0)


#define PCIE_GNR_INT                                                                 0x18017A08
#define PCIE_GNR_INT_reg_addr                                                        "0xB8017A08"
#define PCIE_GNR_INT_reg                                                             0xB8017A08
#define set_PCIE_GNR_INT_reg(data)   (*((volatile unsigned int*) PCIE_GNR_INT_reg)=data)
#define get_PCIE_GNR_INT_reg   (*((volatile unsigned int*) PCIE_GNR_INT_reg))
#define PCIE_GNR_INT_inst_adr                                                        "0x0082"
#define PCIE_GNR_INT_inst                                                            0x0082
#define PCIE_GNR_INT_pcie_legacy_msi_int_shift                                       (14)
#define PCIE_GNR_INT_pcie_legacy_msi_int_mask                                        (0x00004000)
#define PCIE_GNR_INT_pcie_legacy_msi_int(data)                                       (0x00004000&((data)<<14))
#define PCIE_GNR_INT_pcie_legacy_msi_int_src(data)                                   ((0x00004000&(data))>>14)
#define PCIE_GNR_INT_get_pcie_legacy_msi_int(data)                                   ((0x00004000&(data))>>14)
#define PCIE_GNR_INT_pm_to_ack_int_shift                                             (13)
#define PCIE_GNR_INT_pm_to_ack_int_mask                                              (0x00002000)
#define PCIE_GNR_INT_pm_to_ack_int(data)                                             (0x00002000&((data)<<13))
#define PCIE_GNR_INT_pm_to_ack_int_src(data)                                         ((0x00002000&(data))>>13)
#define PCIE_GNR_INT_get_pm_to_ack_int(data)                                         ((0x00002000&(data))>>13)
#define PCIE_GNR_INT_cfg_sys_err_rc_int_shift                                        (12)
#define PCIE_GNR_INT_cfg_sys_err_rc_int_mask                                         (0x00001000)
#define PCIE_GNR_INT_cfg_sys_err_rc_int(data)                                        (0x00001000&((data)<<12))
#define PCIE_GNR_INT_cfg_sys_err_rc_int_src(data)                                    ((0x00001000&(data))>>12)
#define PCIE_GNR_INT_get_cfg_sys_err_rc_int(data)                                    ((0x00001000&(data))>>12)
#define PCIE_GNR_INT_pcie_legacy_int_shift                                           (11)
#define PCIE_GNR_INT_pcie_legacy_int_mask                                            (0x00000800)
#define PCIE_GNR_INT_pcie_legacy_int(data)                                           (0x00000800&((data)<<11))
#define PCIE_GNR_INT_pcie_legacy_int_src(data)                                       ((0x00000800&(data))>>11)
#define PCIE_GNR_INT_get_pcie_legacy_int(data)                                       ((0x00000800&(data))>>11)
#define PCIE_GNR_INT_cfg_radm_vendor_msg_int_shift                                   (10)
#define PCIE_GNR_INT_cfg_radm_vendor_msg_int_mask                                    (0x00000400)
#define PCIE_GNR_INT_cfg_radm_vendor_msg_int(data)                                   (0x00000400&((data)<<10))
#define PCIE_GNR_INT_cfg_radm_vendor_msg_int_src(data)                               ((0x00000400&(data))>>10)
#define PCIE_GNR_INT_get_cfg_radm_vendor_msg_int(data)                               ((0x00000400&(data))>>10)
#define PCIE_GNR_INT_cfg_pme_msi_shift                                               (9)
#define PCIE_GNR_INT_cfg_pme_msi_mask                                                (0x00000200)
#define PCIE_GNR_INT_cfg_pme_msi(data)                                               (0x00000200&((data)<<9))
#define PCIE_GNR_INT_cfg_pme_msi_src(data)                                           ((0x00000200&(data))>>9)
#define PCIE_GNR_INT_get_cfg_pme_msi(data)                                           ((0x00000200&(data))>>9)
#define PCIE_GNR_INT_cfg_pme_int_shift                                               (8)
#define PCIE_GNR_INT_cfg_pme_int_mask                                                (0x00000100)
#define PCIE_GNR_INT_cfg_pme_int(data)                                               (0x00000100&((data)<<8))
#define PCIE_GNR_INT_cfg_pme_int_src(data)                                           ((0x00000100&(data))>>8)
#define PCIE_GNR_INT_get_cfg_pme_int(data)                                           ((0x00000100&(data))>>8)
#define PCIE_GNR_INT_cfg_aer_rc_err_msi_shift                                        (7)
#define PCIE_GNR_INT_cfg_aer_rc_err_msi_mask                                         (0x00000080)
#define PCIE_GNR_INT_cfg_aer_rc_err_msi(data)                                        (0x00000080&((data)<<7))
#define PCIE_GNR_INT_cfg_aer_rc_err_msi_src(data)                                    ((0x00000080&(data))>>7)
#define PCIE_GNR_INT_get_cfg_aer_rc_err_msi(data)                                    ((0x00000080&(data))>>7)
#define PCIE_GNR_INT_cfg_aer_rc_err_int_shift                                        (6)
#define PCIE_GNR_INT_cfg_aer_rc_err_int_mask                                         (0x00000040)
#define PCIE_GNR_INT_cfg_aer_rc_err_int(data)                                        (0x00000040&((data)<<6))
#define PCIE_GNR_INT_cfg_aer_rc_err_int_src(data)                                    ((0x00000040&(data))>>6)
#define PCIE_GNR_INT_get_cfg_aer_rc_err_int(data)                                    ((0x00000040&(data))>>6)
#define PCIE_GNR_INT_intp_rtgt_shift                                                 (5)
#define PCIE_GNR_INT_intp_rtgt_mask                                                  (0x00000020)
#define PCIE_GNR_INT_intp_rtgt(data)                                                 (0x00000020&((data)<<5))
#define PCIE_GNR_INT_intp_rtgt_src(data)                                             ((0x00000020&(data))>>5)
#define PCIE_GNR_INT_get_intp_rtgt(data)                                             ((0x00000020&(data))>>5)
#define PCIE_GNR_INT_intp_rcpl_shift                                                 (4)
#define PCIE_GNR_INT_intp_rcpl_mask                                                  (0x00000010)
#define PCIE_GNR_INT_intp_rcpl(data)                                                 (0x00000010&((data)<<4))
#define PCIE_GNR_INT_intp_rcpl_src(data)                                             ((0x00000010&(data))>>4)
#define PCIE_GNR_INT_get_intp_rcpl(data)                                             ((0x00000010&(data))>>4)
#define PCIE_GNR_INT_intp_dir_cfg_shift                                              (3)
#define PCIE_GNR_INT_intp_dir_cfg_mask                                               (0x00000008)
#define PCIE_GNR_INT_intp_dir_cfg(data)                                              (0x00000008&((data)<<3))
#define PCIE_GNR_INT_intp_dir_cfg_src(data)                                          ((0x00000008&(data))>>3)
#define PCIE_GNR_INT_get_intp_dir_cfg(data)                                          ((0x00000008&(data))>>3)
#define PCIE_GNR_INT_intp_dir_mio_shift                                              (2)
#define PCIE_GNR_INT_intp_dir_mio_mask                                               (0x00000004)
#define PCIE_GNR_INT_intp_dir_mio(data)                                              (0x00000004&((data)<<2))
#define PCIE_GNR_INT_intp_dir_mio_src(data)                                          ((0x00000004&(data))>>2)
#define PCIE_GNR_INT_get_intp_dir_mio(data)                                          ((0x00000004&(data))>>2)
#define PCIE_GNR_INT_intp_cfg_shift                                                  (1)
#define PCIE_GNR_INT_intp_cfg_mask                                                   (0x00000002)
#define PCIE_GNR_INT_intp_cfg(data)                                                  (0x00000002&((data)<<1))
#define PCIE_GNR_INT_intp_cfg_src(data)                                              ((0x00000002&(data))>>1)
#define PCIE_GNR_INT_get_intp_cfg(data)                                              ((0x00000002&(data))>>1)
#define PCIE_GNR_INT_intp_mio_shift                                                  (0)
#define PCIE_GNR_INT_intp_mio_mask                                                   (0x00000001)
#define PCIE_GNR_INT_intp_mio(data)                                                  (0x00000001&((data)<<0))
#define PCIE_GNR_INT_intp_mio_src(data)                                              ((0x00000001&(data))>>0)
#define PCIE_GNR_INT_get_intp_mio(data)                                              ((0x00000001&(data))>>0)


#define PCIE_PCIE_INT                                                                0x18017A0C
#define PCIE_PCIE_INT_reg_addr                                                       "0xB8017A0C"
#define PCIE_PCIE_INT_reg                                                            0xB8017A0C
#define set_PCIE_PCIE_INT_reg(data)   (*((volatile unsigned int*) PCIE_PCIE_INT_reg)=data)
#define get_PCIE_PCIE_INT_reg   (*((volatile unsigned int*) PCIE_PCIE_INT_reg))
#define PCIE_PCIE_INT_inst_adr                                                       "0x0083"
#define PCIE_PCIE_INT_inst                                                           0x0083
#define PCIE_PCIE_INT_intp_intd_shift                                                (3)
#define PCIE_PCIE_INT_intp_intd_mask                                                 (0x00000008)
#define PCIE_PCIE_INT_intp_intd(data)                                                (0x00000008&((data)<<3))
#define PCIE_PCIE_INT_intp_intd_src(data)                                            ((0x00000008&(data))>>3)
#define PCIE_PCIE_INT_get_intp_intd(data)                                            ((0x00000008&(data))>>3)
#define PCIE_PCIE_INT_intp_intc_shift                                                (2)
#define PCIE_PCIE_INT_intp_intc_mask                                                 (0x00000004)
#define PCIE_PCIE_INT_intp_intc(data)                                                (0x00000004&((data)<<2))
#define PCIE_PCIE_INT_intp_intc_src(data)                                            ((0x00000004&(data))>>2)
#define PCIE_PCIE_INT_get_intp_intc(data)                                            ((0x00000004&(data))>>2)
#define PCIE_PCIE_INT_intp_intb_shift                                                (1)
#define PCIE_PCIE_INT_intp_intb_mask                                                 (0x00000002)
#define PCIE_PCIE_INT_intp_intb(data)                                                (0x00000002&((data)<<1))
#define PCIE_PCIE_INT_intp_intb_src(data)                                            ((0x00000002&(data))>>1)
#define PCIE_PCIE_INT_get_intp_intb(data)                                            ((0x00000002&(data))>>1)
#define PCIE_PCIE_INT_intp_inta_shift                                                (0)
#define PCIE_PCIE_INT_intp_inta_mask                                                 (0x00000001)
#define PCIE_PCIE_INT_intp_inta(data)                                                (0x00000001&((data)<<0))
#define PCIE_PCIE_INT_intp_inta_src(data)                                            ((0x00000001&(data))>>0)
#define PCIE_PCIE_INT_get_intp_inta(data)                                            ((0x00000001&(data))>>0)


#define PCIE_DBI_CTR                                                                 0x18017A10
#define PCIE_DBI_CTR_reg_addr                                                        "0xB8017A10"
#define PCIE_DBI_CTR_reg                                                             0xB8017A10
#define set_PCIE_DBI_CTR_reg(data)   (*((volatile unsigned int*) PCIE_DBI_CTR_reg)=data)
#define get_PCIE_DBI_CTR_reg   (*((volatile unsigned int*) PCIE_DBI_CTR_reg))
#define PCIE_DBI_CTR_inst_adr                                                        "0x0084"
#define PCIE_DBI_CTR_inst                                                            0x0084
#define PCIE_DBI_CTR_dbi_io_access_shift                                             (9)
#define PCIE_DBI_CTR_dbi_io_access_mask                                              (0x00000200)
#define PCIE_DBI_CTR_dbi_io_access(data)                                             (0x00000200&((data)<<9))
#define PCIE_DBI_CTR_dbi_io_access_src(data)                                         ((0x00000200&(data))>>9)
#define PCIE_DBI_CTR_get_dbi_io_access(data)                                         ((0x00000200&(data))>>9)
#define PCIE_DBI_CTR_dbi_rom_access_shift                                            (8)
#define PCIE_DBI_CTR_dbi_rom_access_mask                                             (0x00000100)
#define PCIE_DBI_CTR_dbi_rom_access(data)                                            (0x00000100&((data)<<8))
#define PCIE_DBI_CTR_dbi_rom_access_src(data)                                        ((0x00000100&(data))>>8)
#define PCIE_DBI_CTR_get_dbi_rom_access(data)                                        ((0x00000100&(data))>>8)
#define PCIE_DBI_CTR_dbi_bar_num_shift                                               (5)
#define PCIE_DBI_CTR_dbi_bar_num_mask                                                (0x000000E0)
#define PCIE_DBI_CTR_dbi_bar_num(data)                                               (0x000000E0&((data)<<5))
#define PCIE_DBI_CTR_dbi_bar_num_src(data)                                           ((0x000000E0&(data))>>5)
#define PCIE_DBI_CTR_get_dbi_bar_num(data)                                           ((0x000000E0&(data))>>5)
#define PCIE_DBI_CTR_dbi_func_num_shift                                              (2)
#define PCIE_DBI_CTR_dbi_func_num_mask                                               (0x0000001C)
#define PCIE_DBI_CTR_dbi_func_num(data)                                              (0x0000001C&((data)<<2))
#define PCIE_DBI_CTR_dbi_func_num_src(data)                                          ((0x0000001C&(data))>>2)
#define PCIE_DBI_CTR_get_dbi_func_num(data)                                          ((0x0000001C&(data))>>2)
#define PCIE_DBI_CTR_dbi_cs2_access_shift                                            (1)
#define PCIE_DBI_CTR_dbi_cs2_access_mask                                             (0x00000002)
#define PCIE_DBI_CTR_dbi_cs2_access(data)                                            (0x00000002&((data)<<1))
#define PCIE_DBI_CTR_dbi_cs2_access_src(data)                                        ((0x00000002&(data))>>1)
#define PCIE_DBI_CTR_get_dbi_cs2_access(data)                                        ((0x00000002&(data))>>1)
#define PCIE_DBI_CTR_dbi_cmd_access_shift                                            (0)
#define PCIE_DBI_CTR_dbi_cmd_access_mask                                             (0x00000001)
#define PCIE_DBI_CTR_dbi_cmd_access(data)                                            (0x00000001&((data)<<0))
#define PCIE_DBI_CTR_dbi_cmd_access_src(data)                                        ((0x00000001&(data))>>0)
#define PCIE_DBI_CTR_get_dbi_cmd_access(data)                                        ((0x00000001&(data))>>0)


#define PCIE_INDIR_CTR                                                               0x18017A14
#define PCIE_INDIR_CTR_reg_addr                                                      "0xB8017A14"
#define PCIE_INDIR_CTR_reg                                                           0xB8017A14
#define set_PCIE_INDIR_CTR_reg(data)   (*((volatile unsigned int*) PCIE_INDIR_CTR_reg)=data)
#define get_PCIE_INDIR_CTR_reg   (*((volatile unsigned int*) PCIE_INDIR_CTR_reg))
#define PCIE_INDIR_CTR_inst_adr                                                      "0x0085"
#define PCIE_INDIR_CTR_inst                                                          0x0085
#define PCIE_INDIR_CTR_req_info_align_shift                                          (13)
#define PCIE_INDIR_CTR_req_info_align_mask                                           (0x00002000)
#define PCIE_INDIR_CTR_req_info_align(data)                                          (0x00002000&((data)<<13))
#define PCIE_INDIR_CTR_req_info_align_src(data)                                      ((0x00002000&(data))>>13)
#define PCIE_INDIR_CTR_get_req_info_align(data)                                      ((0x00002000&(data))>>13)
#define PCIE_INDIR_CTR_req_info_attr_shift                                           (11)
#define PCIE_INDIR_CTR_req_info_attr_mask                                            (0x00001800)
#define PCIE_INDIR_CTR_req_info_attr(data)                                           (0x00001800&((data)<<11))
#define PCIE_INDIR_CTR_req_info_attr_src(data)                                       ((0x00001800&(data))>>11)
#define PCIE_INDIR_CTR_get_req_info_attr(data)                                       ((0x00001800&(data))>>11)
#define PCIE_INDIR_CTR_req_info_ep_shift                                             (10)
#define PCIE_INDIR_CTR_req_info_ep_mask                                              (0x00000400)
#define PCIE_INDIR_CTR_req_info_ep(data)                                             (0x00000400&((data)<<10))
#define PCIE_INDIR_CTR_req_info_ep_src(data)                                         ((0x00000400&(data))>>10)
#define PCIE_INDIR_CTR_get_req_info_ep(data)                                         ((0x00000400&(data))>>10)
#define PCIE_INDIR_CTR_req_info_tc_shift                                             (7)
#define PCIE_INDIR_CTR_req_info_tc_mask                                              (0x00000380)
#define PCIE_INDIR_CTR_req_info_tc(data)                                             (0x00000380&((data)<<7))
#define PCIE_INDIR_CTR_req_info_tc_src(data)                                         ((0x00000380&(data))>>7)
#define PCIE_INDIR_CTR_get_req_info_tc(data)                                         ((0x00000380&(data))>>7)
#define PCIE_INDIR_CTR_req_info_type_shift                                           (2)
#define PCIE_INDIR_CTR_req_info_type_mask                                            (0x0000007C)
#define PCIE_INDIR_CTR_req_info_type(data)                                           (0x0000007C&((data)<<2))
#define PCIE_INDIR_CTR_req_info_type_src(data)                                       ((0x0000007C&(data))>>2)
#define PCIE_INDIR_CTR_get_req_info_type(data)                                       ((0x0000007C&(data))>>2)
#define PCIE_INDIR_CTR_req_info_fmt_shift                                            (0)
#define PCIE_INDIR_CTR_req_info_fmt_mask                                             (0x00000003)
#define PCIE_INDIR_CTR_req_info_fmt(data)                                            (0x00000003&((data)<<0))
#define PCIE_INDIR_CTR_req_info_fmt_src(data)                                        ((0x00000003&(data))>>0)
#define PCIE_INDIR_CTR_get_req_info_fmt(data)                                        ((0x00000003&(data))>>0)


#define PCIE_DIR_CTR                                                                 0x18017A18
#define PCIE_DIR_CTR_reg_addr                                                        "0xB8017A18"
#define PCIE_DIR_CTR_reg                                                             0xB8017A18
#define set_PCIE_DIR_CTR_reg(data)   (*((volatile unsigned int*) PCIE_DIR_CTR_reg)=data)
#define get_PCIE_DIR_CTR_reg   (*((volatile unsigned int*) PCIE_DIR_CTR_reg))
#define PCIE_DIR_CTR_inst_adr                                                        "0x0086"
#define PCIE_DIR_CTR_inst                                                            0x0086
#define PCIE_DIR_CTR_req_info_align_shift                                            (13)
#define PCIE_DIR_CTR_req_info_align_mask                                             (0x00002000)
#define PCIE_DIR_CTR_req_info_align(data)                                            (0x00002000&((data)<<13))
#define PCIE_DIR_CTR_req_info_align_src(data)                                        ((0x00002000&(data))>>13)
#define PCIE_DIR_CTR_get_req_info_align(data)                                        ((0x00002000&(data))>>13)
#define PCIE_DIR_CTR_req_info_attr_shift                                             (11)
#define PCIE_DIR_CTR_req_info_attr_mask                                              (0x00001800)
#define PCIE_DIR_CTR_req_info_attr(data)                                             (0x00001800&((data)<<11))
#define PCIE_DIR_CTR_req_info_attr_src(data)                                         ((0x00001800&(data))>>11)
#define PCIE_DIR_CTR_get_req_info_attr(data)                                         ((0x00001800&(data))>>11)
#define PCIE_DIR_CTR_req_info_ep_shift                                               (10)
#define PCIE_DIR_CTR_req_info_ep_mask                                                (0x00000400)
#define PCIE_DIR_CTR_req_info_ep(data)                                               (0x00000400&((data)<<10))
#define PCIE_DIR_CTR_req_info_ep_src(data)                                           ((0x00000400&(data))>>10)
#define PCIE_DIR_CTR_get_req_info_ep(data)                                           ((0x00000400&(data))>>10)
#define PCIE_DIR_CTR_req_info_tc_shift                                               (7)
#define PCIE_DIR_CTR_req_info_tc_mask                                                (0x00000380)
#define PCIE_DIR_CTR_req_info_tc(data)                                               (0x00000380&((data)<<7))
#define PCIE_DIR_CTR_req_info_tc_src(data)                                           ((0x00000380&(data))>>7)
#define PCIE_DIR_CTR_get_req_info_tc(data)                                           ((0x00000380&(data))>>7)
#define PCIE_DIR_CTR_req_info_type_shift                                             (2)
#define PCIE_DIR_CTR_req_info_type_mask                                              (0x0000007C)
#define PCIE_DIR_CTR_req_info_type(data)                                             (0x0000007C&((data)<<2))
#define PCIE_DIR_CTR_req_info_type_src(data)                                         ((0x0000007C&(data))>>2)
#define PCIE_DIR_CTR_get_req_info_type(data)                                         ((0x0000007C&(data))>>2)
#define PCIE_DIR_CTR_req_info_fmt_shift                                              (0)
#define PCIE_DIR_CTR_req_info_fmt_mask                                               (0x00000003)
#define PCIE_DIR_CTR_req_info_fmt(data)                                              (0x00000003&((data)<<0))
#define PCIE_DIR_CTR_req_info_fmt_src(data)                                          ((0x00000003&(data))>>0)
#define PCIE_DIR_CTR_get_req_info_fmt(data)                                          ((0x00000003&(data))>>0)


#define PCIE_MDIO_CTR                                                                0x18017A1C
#define PCIE_MDIO_CTR_reg_addr                                                       "0xB8017A1C"
#define PCIE_MDIO_CTR_reg                                                            0xB8017A1C
#define set_PCIE_MDIO_CTR_reg(data)   (*((volatile unsigned int*) PCIE_MDIO_CTR_reg)=data)
#define get_PCIE_MDIO_CTR_reg   (*((volatile unsigned int*) PCIE_MDIO_CTR_reg))
#define PCIE_MDIO_CTR_inst_adr                                                       "0x0087"
#define PCIE_MDIO_CTR_inst                                                           0x0087
#define PCIE_MDIO_CTR_data_shift                                                     (16)
#define PCIE_MDIO_CTR_data_mask                                                      (0xFFFF0000)
#define PCIE_MDIO_CTR_data(data)                                                     (0xFFFF0000&((data)<<16))
#define PCIE_MDIO_CTR_data_src(data)                                                 ((0xFFFF0000&(data))>>16)
#define PCIE_MDIO_CTR_get_data(data)                                                 ((0xFFFF0000&(data))>>16)
#define PCIE_MDIO_CTR_phy_addr_shift                                                 (13)
#define PCIE_MDIO_CTR_phy_addr_mask                                                  (0x0000E000)
#define PCIE_MDIO_CTR_phy_addr(data)                                                 (0x0000E000&((data)<<13))
#define PCIE_MDIO_CTR_phy_addr_src(data)                                             ((0x0000E000&(data))>>13)
#define PCIE_MDIO_CTR_get_phy_addr(data)                                             ((0x0000E000&(data))>>13)
#define PCIE_MDIO_CTR_phy_reg_addr_shift                                             (8)
#define PCIE_MDIO_CTR_phy_reg_addr_mask                                              (0x00001F00)
#define PCIE_MDIO_CTR_phy_reg_addr(data)                                             (0x00001F00&((data)<<8))
#define PCIE_MDIO_CTR_phy_reg_addr_src(data)                                         ((0x00001F00&(data))>>8)
#define PCIE_MDIO_CTR_get_phy_reg_addr(data)                                         ((0x00001F00&(data))>>8)
#define PCIE_MDIO_CTR_mdio_busy_shift                                                (7)
#define PCIE_MDIO_CTR_mdio_busy_mask                                                 (0x00000080)
#define PCIE_MDIO_CTR_mdio_busy(data)                                                (0x00000080&((data)<<7))
#define PCIE_MDIO_CTR_mdio_busy_src(data)                                            ((0x00000080&(data))>>7)
#define PCIE_MDIO_CTR_get_mdio_busy(data)                                            ((0x00000080&(data))>>7)
#define PCIE_MDIO_CTR_mdio_st_shift                                                  (5)
#define PCIE_MDIO_CTR_mdio_st_mask                                                   (0x00000060)
#define PCIE_MDIO_CTR_mdio_st(data)                                                  (0x00000060&((data)<<5))
#define PCIE_MDIO_CTR_mdio_st_src(data)                                              ((0x00000060&(data))>>5)
#define PCIE_MDIO_CTR_get_mdio_st(data)                                              ((0x00000060&(data))>>5)
#define PCIE_MDIO_CTR_mdio_rdy_shift                                                 (4)
#define PCIE_MDIO_CTR_mdio_rdy_mask                                                  (0x00000010)
#define PCIE_MDIO_CTR_mdio_rdy(data)                                                 (0x00000010&((data)<<4))
#define PCIE_MDIO_CTR_mdio_rdy_src(data)                                             ((0x00000010&(data))>>4)
#define PCIE_MDIO_CTR_get_mdio_rdy(data)                                             ((0x00000010&(data))>>4)
#define PCIE_MDIO_CTR_mclk_rate_shift                                                (2)
#define PCIE_MDIO_CTR_mclk_rate_mask                                                 (0x0000000C)
#define PCIE_MDIO_CTR_mclk_rate(data)                                                (0x0000000C&((data)<<2))
#define PCIE_MDIO_CTR_mclk_rate_src(data)                                            ((0x0000000C&(data))>>2)
#define PCIE_MDIO_CTR_get_mclk_rate(data)                                            ((0x0000000C&(data))>>2)
#define PCIE_MDIO_CTR_mdio_srst_shift                                                (1)
#define PCIE_MDIO_CTR_mdio_srst_mask                                                 (0x00000002)
#define PCIE_MDIO_CTR_mdio_srst(data)                                                (0x00000002&((data)<<1))
#define PCIE_MDIO_CTR_mdio_srst_src(data)                                            ((0x00000002&(data))>>1)
#define PCIE_MDIO_CTR_get_mdio_srst(data)                                            ((0x00000002&(data))>>1)
#define PCIE_MDIO_CTR_mdio_rdwr_shift                                                (0)
#define PCIE_MDIO_CTR_mdio_rdwr_mask                                                 (0x00000001)
#define PCIE_MDIO_CTR_mdio_rdwr(data)                                                (0x00000001&((data)<<0))
#define PCIE_MDIO_CTR_mdio_rdwr_src(data)                                            ((0x00000001&(data))>>0)
#define PCIE_MDIO_CTR_get_mdio_rdwr(data)                                            ((0x00000001&(data))>>0)


#define PCIE_PCIE_BASE0                                                              0x18017A20
#define PCIE_PCIE_BASE0_reg_addr                                                     "0xB8017A20"
#define PCIE_PCIE_BASE0_reg                                                          0xB8017A20
#define set_PCIE_PCIE_BASE0_reg(data)   (*((volatile unsigned int*) PCIE_PCIE_BASE0_reg)=data)
#define get_PCIE_PCIE_BASE0_reg   (*((volatile unsigned int*) PCIE_PCIE_BASE0_reg))
#define PCIE_PCIE_BASE0_inst_adr                                                     "0x0088"
#define PCIE_PCIE_BASE0_inst                                                         0x0088
#define PCIE_PCIE_BASE0_rtrans_base_addr_shift                                       (0)
#define PCIE_PCIE_BASE0_rtrans_base_addr_mask                                        (0xFFFFFFFF)
#define PCIE_PCIE_BASE0_rtrans_base_addr(data)                                       (0xFFFFFFFF&((data)<<0))
#define PCIE_PCIE_BASE0_rtrans_base_addr_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define PCIE_PCIE_BASE0_get_rtrans_base_addr(data)                                   ((0xFFFFFFFF&(data))>>0)


#define PCIE_PCIE_BASE1                                                              0x18017A24
#define PCIE_PCIE_BASE1_reg_addr                                                     "0xB8017A24"
#define PCIE_PCIE_BASE1_reg                                                          0xB8017A24
#define set_PCIE_PCIE_BASE1_reg(data)   (*((volatile unsigned int*) PCIE_PCIE_BASE1_reg)=data)
#define get_PCIE_PCIE_BASE1_reg   (*((volatile unsigned int*) PCIE_PCIE_BASE1_reg))
#define PCIE_PCIE_BASE1_inst_adr                                                     "0x0089"
#define PCIE_PCIE_BASE1_inst                                                         0x0089
#define PCIE_PCIE_BASE1_rtrans_base_addr_shift                                       (0)
#define PCIE_PCIE_BASE1_rtrans_base_addr_mask                                        (0xFFFFFFFF)
#define PCIE_PCIE_BASE1_rtrans_base_addr(data)                                       (0xFFFFFFFF&((data)<<0))
#define PCIE_PCIE_BASE1_rtrans_base_addr_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define PCIE_PCIE_BASE1_get_rtrans_base_addr(data)                                   ((0xFFFFFFFF&(data))>>0)


#define PCIE_PCIE_MASK0                                                              0x18017A28
#define PCIE_PCIE_MASK0_reg_addr                                                     "0xB8017A28"
#define PCIE_PCIE_MASK0_reg                                                          0xB8017A28
#define set_PCIE_PCIE_MASK0_reg(data)   (*((volatile unsigned int*) PCIE_PCIE_MASK0_reg)=data)
#define get_PCIE_PCIE_MASK0_reg   (*((volatile unsigned int*) PCIE_PCIE_MASK0_reg))
#define PCIE_PCIE_MASK0_inst_adr                                                     "0x008A"
#define PCIE_PCIE_MASK0_inst                                                         0x008A
#define PCIE_PCIE_MASK0_rtrans_mask_shift                                            (0)
#define PCIE_PCIE_MASK0_rtrans_mask_mask                                             (0xFFFFFFFF)
#define PCIE_PCIE_MASK0_rtrans_mask(data)                                            (0xFFFFFFFF&((data)<<0))
#define PCIE_PCIE_MASK0_rtrans_mask_src(data)                                        ((0xFFFFFFFF&(data))>>0)
#define PCIE_PCIE_MASK0_get_rtrans_mask(data)                                        ((0xFFFFFFFF&(data))>>0)


#define PCIE_PCIE_MASK1                                                              0x18017A2C
#define PCIE_PCIE_MASK1_reg_addr                                                     "0xB8017A2C"
#define PCIE_PCIE_MASK1_reg                                                          0xB8017A2C
#define set_PCIE_PCIE_MASK1_reg(data)   (*((volatile unsigned int*) PCIE_PCIE_MASK1_reg)=data)
#define get_PCIE_PCIE_MASK1_reg   (*((volatile unsigned int*) PCIE_PCIE_MASK1_reg))
#define PCIE_PCIE_MASK1_inst_adr                                                     "0x008B"
#define PCIE_PCIE_MASK1_inst                                                         0x008B
#define PCIE_PCIE_MASK1_rtrans_mask_shift                                            (0)
#define PCIE_PCIE_MASK1_rtrans_mask_mask                                             (0xFFFFFFFF)
#define PCIE_PCIE_MASK1_rtrans_mask(data)                                            (0xFFFFFFFF&((data)<<0))
#define PCIE_PCIE_MASK1_rtrans_mask_src(data)                                        ((0xFFFFFFFF&(data))>>0)
#define PCIE_PCIE_MASK1_get_rtrans_mask(data)                                        ((0xFFFFFFFF&(data))>>0)


#define PCIE_PCIE_TRAN0                                                              0x18017A30
#define PCIE_PCIE_TRAN0_reg_addr                                                     "0xB8017A30"
#define PCIE_PCIE_TRAN0_reg                                                          0xB8017A30
#define set_PCIE_PCIE_TRAN0_reg(data)   (*((volatile unsigned int*) PCIE_PCIE_TRAN0_reg)=data)
#define get_PCIE_PCIE_TRAN0_reg   (*((volatile unsigned int*) PCIE_PCIE_TRAN0_reg))
#define PCIE_PCIE_TRAN0_inst_adr                                                     "0x008C"
#define PCIE_PCIE_TRAN0_inst                                                         0x008C
#define PCIE_PCIE_TRAN0_rtrans_addr_in_shift                                         (0)
#define PCIE_PCIE_TRAN0_rtrans_addr_in_mask                                          (0xFFFFFFFF)
#define PCIE_PCIE_TRAN0_rtrans_addr_in(data)                                         (0xFFFFFFFF&((data)<<0))
#define PCIE_PCIE_TRAN0_rtrans_addr_in_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define PCIE_PCIE_TRAN0_get_rtrans_addr_in(data)                                     ((0xFFFFFFFF&(data))>>0)


#define PCIE_PCIE_TRAN1                                                              0x18017A34
#define PCIE_PCIE_TRAN1_reg_addr                                                     "0xB8017A34"
#define PCIE_PCIE_TRAN1_reg                                                          0xB8017A34
#define set_PCIE_PCIE_TRAN1_reg(data)   (*((volatile unsigned int*) PCIE_PCIE_TRAN1_reg)=data)
#define get_PCIE_PCIE_TRAN1_reg   (*((volatile unsigned int*) PCIE_PCIE_TRAN1_reg))
#define PCIE_PCIE_TRAN1_inst_adr                                                     "0x008D"
#define PCIE_PCIE_TRAN1_inst                                                         0x008D
#define PCIE_PCIE_TRAN1_rtrans_addr_in_shift                                         (0)
#define PCIE_PCIE_TRAN1_rtrans_addr_in_mask                                          (0xFFFFFFFF)
#define PCIE_PCIE_TRAN1_rtrans_addr_in(data)                                         (0xFFFFFFFF&((data)<<0))
#define PCIE_PCIE_TRAN1_rtrans_addr_in_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define PCIE_PCIE_TRAN1_get_rtrans_addr_in(data)                                     ((0xFFFFFFFF&(data))>>0)


#define PCIE_CFG_CT                                                                  0x18017A38
#define PCIE_CFG_CT_reg_addr                                                         "0xB8017A38"
#define PCIE_CFG_CT_reg                                                              0xB8017A38
#define set_PCIE_CFG_CT_reg(data)   (*((volatile unsigned int*) PCIE_CFG_CT_reg)=data)
#define get_PCIE_CFG_CT_reg   (*((volatile unsigned int*) PCIE_CFG_CT_reg))
#define PCIE_CFG_CT_inst_adr                                                         "0x008E"
#define PCIE_CFG_CT_inst                                                             0x008E
#define PCIE_CFG_CT_go_ct_shift                                                      (0)
#define PCIE_CFG_CT_go_ct_mask                                                       (0x00000001)
#define PCIE_CFG_CT_go_ct(data)                                                      (0x00000001&((data)<<0))
#define PCIE_CFG_CT_go_ct_src(data)                                                  ((0x00000001&(data))>>0)
#define PCIE_CFG_CT_get_go_ct(data)                                                  ((0x00000001&(data))>>0)


#define PCIE_CFG_EN                                                                  0x18017A3C
#define PCIE_CFG_EN_reg_addr                                                         "0xB8017A3C"
#define PCIE_CFG_EN_reg                                                              0xB8017A3C
#define set_PCIE_CFG_EN_reg(data)   (*((volatile unsigned int*) PCIE_CFG_EN_reg)=data)
#define get_PCIE_CFG_EN_reg   (*((volatile unsigned int*) PCIE_CFG_EN_reg))
#define PCIE_CFG_EN_inst_adr                                                         "0x008F"
#define PCIE_CFG_EN_inst                                                             0x008F
#define PCIE_CFG_EN_bus_num_shift                                                    (16)
#define PCIE_CFG_EN_bus_num_mask                                                     (0x00FF0000)
#define PCIE_CFG_EN_bus_num(data)                                                    (0x00FF0000&((data)<<16))
#define PCIE_CFG_EN_bus_num_src(data)                                                ((0x00FF0000&(data))>>16)
#define PCIE_CFG_EN_get_bus_num(data)                                                ((0x00FF0000&(data))>>16)
#define PCIE_CFG_EN_dev_num_shift                                                    (11)
#define PCIE_CFG_EN_dev_num_mask                                                     (0x0000F800)
#define PCIE_CFG_EN_dev_num(data)                                                    (0x0000F800&((data)<<11))
#define PCIE_CFG_EN_dev_num_src(data)                                                ((0x0000F800&(data))>>11)
#define PCIE_CFG_EN_get_dev_num(data)                                                ((0x0000F800&(data))>>11)
#define PCIE_CFG_EN_fun_num_shift                                                    (8)
#define PCIE_CFG_EN_fun_num_mask                                                     (0x00000700)
#define PCIE_CFG_EN_fun_num(data)                                                    (0x00000700&((data)<<8))
#define PCIE_CFG_EN_fun_num_src(data)                                                ((0x00000700&(data))>>8)
#define PCIE_CFG_EN_get_fun_num(data)                                                ((0x00000700&(data))>>8)
#define PCIE_CFG_EN_byte_cnt_shift                                                   (4)
#define PCIE_CFG_EN_byte_cnt_mask                                                    (0x000000F0)
#define PCIE_CFG_EN_byte_cnt(data)                                                   (0x000000F0&((data)<<4))
#define PCIE_CFG_EN_byte_cnt_src(data)                                               ((0x000000F0&(data))>>4)
#define PCIE_CFG_EN_get_byte_cnt(data)                                               ((0x000000F0&(data))>>4)
#define PCIE_CFG_EN_error_en_shift                                                   (2)
#define PCIE_CFG_EN_error_en_mask                                                    (0x00000004)
#define PCIE_CFG_EN_error_en(data)                                                   (0x00000004&((data)<<2))
#define PCIE_CFG_EN_error_en_src(data)                                               ((0x00000004&(data))>>2)
#define PCIE_CFG_EN_get_error_en(data)                                               ((0x00000004&(data))>>2)
#define PCIE_CFG_EN_byte_en_shift                                                    (1)
#define PCIE_CFG_EN_byte_en_mask                                                     (0x00000002)
#define PCIE_CFG_EN_byte_en(data)                                                    (0x00000002&((data)<<1))
#define PCIE_CFG_EN_byte_en_src(data)                                                ((0x00000002&(data))>>1)
#define PCIE_CFG_EN_get_byte_en(data)                                                ((0x00000002&(data))>>1)
#define PCIE_CFG_EN_wrrd_en_shift                                                    (0)
#define PCIE_CFG_EN_wrrd_en_mask                                                     (0x00000001)
#define PCIE_CFG_EN_wrrd_en(data)                                                    (0x00000001&((data)<<0))
#define PCIE_CFG_EN_wrrd_en_src(data)                                                ((0x00000001&(data))>>0)
#define PCIE_CFG_EN_get_wrrd_en(data)                                                ((0x00000001&(data))>>0)


#define PCIE_CFG_ST                                                                  0x18017A40
#define PCIE_CFG_ST_reg_addr                                                         "0xB8017A40"
#define PCIE_CFG_ST_reg                                                              0xB8017A40
#define set_PCIE_CFG_ST_reg(data)   (*((volatile unsigned int*) PCIE_CFG_ST_reg)=data)
#define get_PCIE_CFG_ST_reg   (*((volatile unsigned int*) PCIE_CFG_ST_reg))
#define PCIE_CFG_ST_inst_adr                                                         "0x0090"
#define PCIE_CFG_ST_inst                                                             0x0090
#define PCIE_CFG_ST_error_st_shift                                                   (1)
#define PCIE_CFG_ST_error_st_mask                                                    (0x00000002)
#define PCIE_CFG_ST_error_st(data)                                                   (0x00000002&((data)<<1))
#define PCIE_CFG_ST_error_st_src(data)                                               ((0x00000002&(data))>>1)
#define PCIE_CFG_ST_get_error_st(data)                                               ((0x00000002&(data))>>1)
#define PCIE_CFG_ST_done_st_shift                                                    (0)
#define PCIE_CFG_ST_done_st_mask                                                     (0x00000001)
#define PCIE_CFG_ST_done_st(data)                                                    (0x00000001&((data)<<0))
#define PCIE_CFG_ST_done_st_src(data)                                                ((0x00000001&(data))>>0)
#define PCIE_CFG_ST_get_done_st(data)                                                ((0x00000001&(data))>>0)


#define PCIE_CFG_ADDR                                                                0x18017A44
#define PCIE_CFG_ADDR_reg_addr                                                       "0xB8017A44"
#define PCIE_CFG_ADDR_reg                                                            0xB8017A44
#define set_PCIE_CFG_ADDR_reg(data)   (*((volatile unsigned int*) PCIE_CFG_ADDR_reg)=data)
#define get_PCIE_CFG_ADDR_reg   (*((volatile unsigned int*) PCIE_CFG_ADDR_reg))
#define PCIE_CFG_ADDR_inst_adr                                                       "0x0091"
#define PCIE_CFG_ADDR_inst                                                           0x0091
#define PCIE_CFG_ADDR_space_addr_shift                                               (0)
#define PCIE_CFG_ADDR_space_addr_mask                                                (0xFFFFFFFF)
#define PCIE_CFG_ADDR_space_addr(data)                                               (0xFFFFFFFF&((data)<<0))
#define PCIE_CFG_ADDR_space_addr_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define PCIE_CFG_ADDR_get_space_addr(data)                                           ((0xFFFFFFFF&(data))>>0)


#define PCIE_CFG_WDATA                                                               0x18017A48
#define PCIE_CFG_WDATA_reg_addr                                                      "0xB8017A48"
#define PCIE_CFG_WDATA_reg                                                           0xB8017A48
#define set_PCIE_CFG_WDATA_reg(data)   (*((volatile unsigned int*) PCIE_CFG_WDATA_reg)=data)
#define get_PCIE_CFG_WDATA_reg   (*((volatile unsigned int*) PCIE_CFG_WDATA_reg))
#define PCIE_CFG_WDATA_inst_adr                                                      "0x0092"
#define PCIE_CFG_WDATA_inst                                                          0x0092
#define PCIE_CFG_WDATA_space_wdata_shift                                             (0)
#define PCIE_CFG_WDATA_space_wdata_mask                                              (0xFFFFFFFF)
#define PCIE_CFG_WDATA_space_wdata(data)                                             (0xFFFFFFFF&((data)<<0))
#define PCIE_CFG_WDATA_space_wdata_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define PCIE_CFG_WDATA_get_space_wdata(data)                                         ((0xFFFFFFFF&(data))>>0)


#define PCIE_CFG_RDATA                                                               0x18017A4C
#define PCIE_CFG_RDATA_reg_addr                                                      "0xB8017A4C"
#define PCIE_CFG_RDATA_reg                                                           0xB8017A4C
#define set_PCIE_CFG_RDATA_reg(data)   (*((volatile unsigned int*) PCIE_CFG_RDATA_reg)=data)
#define get_PCIE_CFG_RDATA_reg   (*((volatile unsigned int*) PCIE_CFG_RDATA_reg))
#define PCIE_CFG_RDATA_inst_adr                                                      "0x0093"
#define PCIE_CFG_RDATA_inst                                                          0x0093
#define PCIE_CFG_RDATA_space_rdata_shift                                             (0)
#define PCIE_CFG_RDATA_space_rdata_mask                                              (0xFFFFFFFF)
#define PCIE_CFG_RDATA_space_rdata(data)                                             (0xFFFFFFFF&((data)<<0))
#define PCIE_CFG_RDATA_space_rdata_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define PCIE_CFG_RDATA_get_space_rdata(data)                                         ((0xFFFFFFFF&(data))>>0)


#define PCIE_MIO_CT                                                                  0x18017A50
#define PCIE_MIO_CT_reg_addr                                                         "0xB8017A50"
#define PCIE_MIO_CT_reg                                                              0xB8017A50
#define set_PCIE_MIO_CT_reg(data)   (*((volatile unsigned int*) PCIE_MIO_CT_reg)=data)
#define get_PCIE_MIO_CT_reg   (*((volatile unsigned int*) PCIE_MIO_CT_reg))
#define PCIE_MIO_CT_inst_adr                                                         "0x0094"
#define PCIE_MIO_CT_inst                                                             0x0094
#define PCIE_MIO_CT_go_ct_shift                                                      (0)
#define PCIE_MIO_CT_go_ct_mask                                                       (0x00000001)
#define PCIE_MIO_CT_go_ct(data)                                                      (0x00000001&((data)<<0))
#define PCIE_MIO_CT_go_ct_src(data)                                                  ((0x00000001&(data))>>0)
#define PCIE_MIO_CT_get_go_ct(data)                                                  ((0x00000001&(data))>>0)


#define PCIE_MIO_ST                                                                  0x18017A54
#define PCIE_MIO_ST_reg_addr                                                         "0xB8017A54"
#define PCIE_MIO_ST_reg                                                              0xB8017A54
#define set_PCIE_MIO_ST_reg(data)   (*((volatile unsigned int*) PCIE_MIO_ST_reg)=data)
#define get_PCIE_MIO_ST_reg   (*((volatile unsigned int*) PCIE_MIO_ST_reg))
#define PCIE_MIO_ST_inst_adr                                                         "0x0095"
#define PCIE_MIO_ST_inst                                                             0x0095
#define PCIE_MIO_ST_error_st_shift                                                   (1)
#define PCIE_MIO_ST_error_st_mask                                                    (0x00000002)
#define PCIE_MIO_ST_error_st(data)                                                   (0x00000002&((data)<<1))
#define PCIE_MIO_ST_error_st_src(data)                                               ((0x00000002&(data))>>1)
#define PCIE_MIO_ST_get_error_st(data)                                               ((0x00000002&(data))>>1)
#define PCIE_MIO_ST_done_st_shift                                                    (0)
#define PCIE_MIO_ST_done_st_mask                                                     (0x00000001)
#define PCIE_MIO_ST_done_st(data)                                                    (0x00000001&((data)<<0))
#define PCIE_MIO_ST_done_st_src(data)                                                ((0x00000001&(data))>>0)
#define PCIE_MIO_ST_get_done_st(data)                                                ((0x00000001&(data))>>0)


#define PCIE_MIO_EN                                                                  0x18017A58
#define PCIE_MIO_EN_reg_addr                                                         "0xB8017A58"
#define PCIE_MIO_EN_reg                                                              0xB8017A58
#define set_PCIE_MIO_EN_reg(data)   (*((volatile unsigned int*) PCIE_MIO_EN_reg)=data)
#define get_PCIE_MIO_EN_reg   (*((volatile unsigned int*) PCIE_MIO_EN_reg))
#define PCIE_MIO_EN_inst_adr                                                         "0x0096"
#define PCIE_MIO_EN_inst                                                             0x0096
#define PCIE_MIO_EN_timeout_cnt_value_shift                                          (8)
#define PCIE_MIO_EN_timeout_cnt_value_mask                                           (0xFFFFFF00)
#define PCIE_MIO_EN_timeout_cnt_value(data)                                          (0xFFFFFF00&((data)<<8))
#define PCIE_MIO_EN_timeout_cnt_value_src(data)                                      ((0xFFFFFF00&(data))>>8)
#define PCIE_MIO_EN_get_timeout_cnt_value(data)                                      ((0xFFFFFF00&(data))>>8)
#define PCIE_MIO_EN_byte_cnt_shift                                                   (4)
#define PCIE_MIO_EN_byte_cnt_mask                                                    (0x000000F0)
#define PCIE_MIO_EN_byte_cnt(data)                                                   (0x000000F0&((data)<<4))
#define PCIE_MIO_EN_byte_cnt_src(data)                                               ((0x000000F0&(data))>>4)
#define PCIE_MIO_EN_get_byte_cnt(data)                                               ((0x000000F0&(data))>>4)
#define PCIE_MIO_EN_error_en_shift                                                   (2)
#define PCIE_MIO_EN_error_en_mask                                                    (0x00000004)
#define PCIE_MIO_EN_error_en(data)                                                   (0x00000004&((data)<<2))
#define PCIE_MIO_EN_error_en_src(data)                                               ((0x00000004&(data))>>2)
#define PCIE_MIO_EN_get_error_en(data)                                               ((0x00000004&(data))>>2)
#define PCIE_MIO_EN_byte_en_shift                                                    (1)
#define PCIE_MIO_EN_byte_en_mask                                                     (0x00000002)
#define PCIE_MIO_EN_byte_en(data)                                                    (0x00000002&((data)<<1))
#define PCIE_MIO_EN_byte_en_src(data)                                                ((0x00000002&(data))>>1)
#define PCIE_MIO_EN_get_byte_en(data)                                                ((0x00000002&(data))>>1)
#define PCIE_MIO_EN_wrrd_en_shift                                                    (0)
#define PCIE_MIO_EN_wrrd_en_mask                                                     (0x00000001)
#define PCIE_MIO_EN_wrrd_en(data)                                                    (0x00000001&((data)<<0))
#define PCIE_MIO_EN_wrrd_en_src(data)                                                ((0x00000001&(data))>>0)
#define PCIE_MIO_EN_get_wrrd_en(data)                                                ((0x00000001&(data))>>0)


#define PCIE_MIO_ADDR                                                                0x18017A5C
#define PCIE_MIO_ADDR_reg_addr                                                       "0xB8017A5C"
#define PCIE_MIO_ADDR_reg                                                            0xB8017A5C
#define set_PCIE_MIO_ADDR_reg(data)   (*((volatile unsigned int*) PCIE_MIO_ADDR_reg)=data)
#define get_PCIE_MIO_ADDR_reg   (*((volatile unsigned int*) PCIE_MIO_ADDR_reg))
#define PCIE_MIO_ADDR_inst_adr                                                       "0x0097"
#define PCIE_MIO_ADDR_inst                                                           0x0097
#define PCIE_MIO_ADDR_pcie_addr_shift                                                (0)
#define PCIE_MIO_ADDR_pcie_addr_mask                                                 (0xFFFFFFFF)
#define PCIE_MIO_ADDR_pcie_addr(data)                                                (0xFFFFFFFF&((data)<<0))
#define PCIE_MIO_ADDR_pcie_addr_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define PCIE_MIO_ADDR_get_pcie_addr(data)                                            ((0xFFFFFFFF&(data))>>0)


#define PCIE_MIO_WDATA                                                               0x18017A60
#define PCIE_MIO_WDATA_reg_addr                                                      "0xB8017A60"
#define PCIE_MIO_WDATA_reg                                                           0xB8017A60
#define set_PCIE_MIO_WDATA_reg(data)   (*((volatile unsigned int*) PCIE_MIO_WDATA_reg)=data)
#define get_PCIE_MIO_WDATA_reg   (*((volatile unsigned int*) PCIE_MIO_WDATA_reg))
#define PCIE_MIO_WDATA_inst_adr                                                      "0x0098"
#define PCIE_MIO_WDATA_inst                                                          0x0098
#define PCIE_MIO_WDATA_pcie_wdata_shift                                              (0)
#define PCIE_MIO_WDATA_pcie_wdata_mask                                               (0xFFFFFFFF)
#define PCIE_MIO_WDATA_pcie_wdata(data)                                              (0xFFFFFFFF&((data)<<0))
#define PCIE_MIO_WDATA_pcie_wdata_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define PCIE_MIO_WDATA_get_pcie_wdata(data)                                          ((0xFFFFFFFF&(data))>>0)


#define PCIE_MIO_RDATA                                                               0x18017A64
#define PCIE_MIO_RDATA_reg_addr                                                      "0xB8017A64"
#define PCIE_MIO_RDATA_reg                                                           0xB8017A64
#define set_PCIE_MIO_RDATA_reg(data)   (*((volatile unsigned int*) PCIE_MIO_RDATA_reg)=data)
#define get_PCIE_MIO_RDATA_reg   (*((volatile unsigned int*) PCIE_MIO_RDATA_reg))
#define PCIE_MIO_RDATA_inst_adr                                                      "0x0099"
#define PCIE_MIO_RDATA_inst                                                          0x0099
#define PCIE_MIO_RDATA_pcie_rdata_shift                                              (0)
#define PCIE_MIO_RDATA_pcie_rdata_mask                                               (0xFFFFFFFF)
#define PCIE_MIO_RDATA_pcie_rdata(data)                                              (0xFFFFFFFF&((data)<<0))
#define PCIE_MIO_RDATA_pcie_rdata_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define PCIE_MIO_RDATA_get_pcie_rdata(data)                                          ((0xFFFFFFFF&(data))>>0)


#define PCIE_PHY_CTR                                                                 0x18017A68
#define PCIE_PHY_CTR_reg_addr                                                        "0xB8017A68"
#define PCIE_PHY_CTR_reg                                                             0xB8017A68
#define set_PCIE_PHY_CTR_reg(data)   (*((volatile unsigned int*) PCIE_PHY_CTR_reg)=data)
#define get_PCIE_PHY_CTR_reg   (*((volatile unsigned int*) PCIE_PHY_CTR_reg))
#define PCIE_PHY_CTR_inst_adr                                                        "0x009A"
#define PCIE_PHY_CTR_inst                                                            0x009A
#define PCIE_PHY_CTR_RX50_LINK_shift                                                 (6)
#define PCIE_PHY_CTR_RX50_LINK_mask                                                  (0x00000040)
#define PCIE_PHY_CTR_RX50_LINK(data)                                                 (0x00000040&((data)<<6))
#define PCIE_PHY_CTR_RX50_LINK_src(data)                                             ((0x00000040&(data))>>6)
#define PCIE_PHY_CTR_get_RX50_LINK(data)                                             ((0x00000040&(data))>>6)
#define PCIE_PHY_CTR_POW_PCIEX_shift                                                 (5)
#define PCIE_PHY_CTR_POW_PCIEX_mask                                                  (0x00000020)
#define PCIE_PHY_CTR_POW_PCIEX(data)                                                 (0x00000020&((data)<<5))
#define PCIE_PHY_CTR_POW_PCIEX_src(data)                                             ((0x00000020&(data))>>5)
#define PCIE_PHY_CTR_get_POW_PCIEX(data)                                             ((0x00000020&(data))>>5)
#define PCIE_PHY_CTR_SEL0_125M_shift                                                 (4)
#define PCIE_PHY_CTR_SEL0_125M_mask                                                  (0x00000010)
#define PCIE_PHY_CTR_SEL0_125M(data)                                                 (0x00000010&((data)<<4))
#define PCIE_PHY_CTR_SEL0_125M_src(data)                                             ((0x00000010&(data))>>4)
#define PCIE_PHY_CTR_get_SEL0_125M(data)                                             ((0x00000010&(data))>>4)
#define PCIE_PHY_CTR_REG_PLLDVR_shift                                                (1)
#define PCIE_PHY_CTR_REG_PLLDVR_mask                                                 (0x0000000E)
#define PCIE_PHY_CTR_REG_PLLDVR(data)                                                (0x0000000E&((data)<<1))
#define PCIE_PHY_CTR_REG_PLLDVR_src(data)                                            ((0x0000000E&(data))>>1)
#define PCIE_PHY_CTR_get_REG_PLLDVR(data)                                            ((0x0000000E&(data))>>1)
#define PCIE_PHY_CTR_CLK_SEL_shift                                                   (0)
#define PCIE_PHY_CTR_CLK_SEL_mask                                                    (0x00000001)
#define PCIE_PHY_CTR_CLK_SEL(data)                                                   (0x00000001&((data)<<0))
#define PCIE_PHY_CTR_CLK_SEL_src(data)                                               ((0x00000001&(data))>>0)
#define PCIE_PHY_CTR_get_CLK_SEL(data)                                               ((0x00000001&(data))>>0)


#define PCIE_PWR_CTR                                                                 0x18017A6C
#define PCIE_PWR_CTR_reg_addr                                                        "0xB8017A6C"
#define PCIE_PWR_CTR_reg                                                             0xB8017A6C
#define set_PCIE_PWR_CTR_reg(data)   (*((volatile unsigned int*) PCIE_PWR_CTR_reg)=data)
#define get_PCIE_PWR_CTR_reg   (*((volatile unsigned int*) PCIE_PWR_CTR_reg))
#define PCIE_PWR_CTR_inst_adr                                                        "0x009B"
#define PCIE_PWR_CTR_inst                                                            0x009B
#define PCIE_PWR_CTR_app_pmxmt_turnoff_shift                                         (6)
#define PCIE_PWR_CTR_app_pmxmt_turnoff_mask                                          (0x00000040)
#define PCIE_PWR_CTR_app_pmxmt_turnoff(data)                                         (0x00000040&((data)<<6))
#define PCIE_PWR_CTR_app_pmxmt_turnoff_src(data)                                     ((0x00000040&(data))>>6)
#define PCIE_PWR_CTR_get_app_pmxmt_turnoff(data)                                     ((0x00000040&(data))>>6)
#define PCIE_PWR_CTR_p1_clk_req_en_shift                                             (5)
#define PCIE_PWR_CTR_p1_clk_req_en_mask                                              (0x00000020)
#define PCIE_PWR_CTR_p1_clk_req_en(data)                                             (0x00000020&((data)<<5))
#define PCIE_PWR_CTR_p1_clk_req_en_src(data)                                         ((0x00000020&(data))>>5)
#define PCIE_PWR_CTR_get_p1_clk_req_en(data)                                         ((0x00000020&(data))>>5)
#define PCIE_PWR_CTR_low_power_enable_shift                                          (4)
#define PCIE_PWR_CTR_low_power_enable_mask                                           (0x00000010)
#define PCIE_PWR_CTR_low_power_enable(data)                                          (0x00000010&((data)<<4))
#define PCIE_PWR_CTR_low_power_enable_src(data)                                      ((0x00000010&(data))>>4)
#define PCIE_PWR_CTR_get_low_power_enable(data)                                      ((0x00000010&(data))>>4)
#define PCIE_PWR_CTR_sys_aux_pwr_det_shift                                           (3)
#define PCIE_PWR_CTR_sys_aux_pwr_det_mask                                            (0x00000008)
#define PCIE_PWR_CTR_sys_aux_pwr_det(data)                                           (0x00000008&((data)<<3))
#define PCIE_PWR_CTR_sys_aux_pwr_det_src(data)                                       ((0x00000008&(data))>>3)
#define PCIE_PWR_CTR_get_sys_aux_pwr_det(data)                                       ((0x00000008&(data))>>3)
#define PCIE_PWR_CTR_app_ready_enter_123_shift                                       (2)
#define PCIE_PWR_CTR_app_ready_enter_123_mask                                        (0x00000004)
#define PCIE_PWR_CTR_app_ready_enter_123(data)                                       (0x00000004&((data)<<2))
#define PCIE_PWR_CTR_app_ready_enter_123_src(data)                                   ((0x00000004&(data))>>2)
#define PCIE_PWR_CTR_get_app_ready_enter_123(data)                                   ((0x00000004&(data))>>2)
#define PCIE_PWR_CTR_app_req_exit_11_shift                                           (1)
#define PCIE_PWR_CTR_app_req_exit_11_mask                                            (0x00000002)
#define PCIE_PWR_CTR_app_req_exit_11(data)                                           (0x00000002&((data)<<1))
#define PCIE_PWR_CTR_app_req_exit_11_src(data)                                       ((0x00000002&(data))>>1)
#define PCIE_PWR_CTR_get_app_req_exit_11(data)                                       ((0x00000002&(data))>>1)
#define PCIE_PWR_CTR_app_req_enter_11_shift                                          (0)
#define PCIE_PWR_CTR_app_req_enter_11_mask                                           (0x00000001)
#define PCIE_PWR_CTR_app_req_enter_11(data)                                          (0x00000001&((data)<<0))
#define PCIE_PWR_CTR_app_req_enter_11_src(data)                                      ((0x00000001&(data))>>0)
#define PCIE_PWR_CTR_get_app_req_enter_11(data)                                      ((0x00000001&(data))>>0)


#define PCIE_PCIE_DBG                                                                0x18017A70
#define PCIE_PCIE_DBG_reg_addr                                                       "0xB8017A70"
#define PCIE_PCIE_DBG_reg                                                            0xB8017A70
#define set_PCIE_PCIE_DBG_reg(data)   (*((volatile unsigned int*) PCIE_PCIE_DBG_reg)=data)
#define get_PCIE_PCIE_DBG_reg   (*((volatile unsigned int*) PCIE_PCIE_DBG_reg))
#define PCIE_PCIE_DBG_inst_adr                                                       "0x009C"
#define PCIE_PCIE_DBG_inst                                                           0x009C
#define PCIE_PCIE_DBG_dbg_sel1_shift                                                 (7)
#define PCIE_PCIE_DBG_dbg_sel1_mask                                                  (0x00001F80)
#define PCIE_PCIE_DBG_dbg_sel1(data)                                                 (0x00001F80&((data)<<7))
#define PCIE_PCIE_DBG_dbg_sel1_src(data)                                             ((0x00001F80&(data))>>7)
#define PCIE_PCIE_DBG_get_dbg_sel1(data)                                             ((0x00001F80&(data))>>7)
#define PCIE_PCIE_DBG_dbg_sel0_shift                                                 (1)
#define PCIE_PCIE_DBG_dbg_sel0_mask                                                  (0x0000007E)
#define PCIE_PCIE_DBG_dbg_sel0(data)                                                 (0x0000007E&((data)<<1))
#define PCIE_PCIE_DBG_dbg_sel0_src(data)                                             ((0x0000007E&(data))>>1)
#define PCIE_PCIE_DBG_get_dbg_sel0(data)                                             ((0x0000007E&(data))>>1)
#define PCIE_PCIE_DBG_dbg_en_shift                                                   (0)
#define PCIE_PCIE_DBG_dbg_en_mask                                                    (0x00000001)
#define PCIE_PCIE_DBG_dbg_en(data)                                                   (0x00000001&((data)<<0))
#define PCIE_PCIE_DBG_dbg_en_src(data)                                               ((0x00000001&(data))>>0)
#define PCIE_PCIE_DBG_get_dbg_en(data)                                               ((0x00000001&(data))>>0)


#define PCIE_DIR_ST                                                                  0x18017A74
#define PCIE_DIR_ST_reg_addr                                                         "0xB8017A74"
#define PCIE_DIR_ST_reg                                                              0xB8017A74
#define set_PCIE_DIR_ST_reg(data)   (*((volatile unsigned int*) PCIE_DIR_ST_reg)=data)
#define get_PCIE_DIR_ST_reg   (*((volatile unsigned int*) PCIE_DIR_ST_reg))
#define PCIE_DIR_ST_inst_adr                                                         "0x009D"
#define PCIE_DIR_ST_inst                                                             0x009D
#define PCIE_DIR_ST_cfg_rerror_st_shift                                              (1)
#define PCIE_DIR_ST_cfg_rerror_st_mask                                               (0x00000002)
#define PCIE_DIR_ST_cfg_rerror_st(data)                                              (0x00000002&((data)<<1))
#define PCIE_DIR_ST_cfg_rerror_st_src(data)                                          ((0x00000002&(data))>>1)
#define PCIE_DIR_ST_get_cfg_rerror_st(data)                                          ((0x00000002&(data))>>1)
#define PCIE_DIR_ST_mio_rerror_st_shift                                              (0)
#define PCIE_DIR_ST_mio_rerror_st_mask                                               (0x00000001)
#define PCIE_DIR_ST_mio_rerror_st(data)                                              (0x00000001&((data)<<0))
#define PCIE_DIR_ST_mio_rerror_st_src(data)                                          ((0x00000001&(data))>>0)
#define PCIE_DIR_ST_get_mio_rerror_st(data)                                          ((0x00000001&(data))>>0)


#define PCIE_DIR_EN                                                                  0x18017A78
#define PCIE_DIR_EN_reg_addr                                                         "0xB8017A78"
#define PCIE_DIR_EN_reg                                                              0xB8017A78
#define set_PCIE_DIR_EN_reg(data)   (*((volatile unsigned int*) PCIE_DIR_EN_reg)=data)
#define get_PCIE_DIR_EN_reg   (*((volatile unsigned int*) PCIE_DIR_EN_reg))
#define PCIE_DIR_EN_inst_adr                                                         "0x009E"
#define PCIE_DIR_EN_inst                                                             0x009E
#define PCIE_DIR_EN_timeout_cnt_value_shift                                          (8)
#define PCIE_DIR_EN_timeout_cnt_value_mask                                           (0xFFFFFF00)
#define PCIE_DIR_EN_timeout_cnt_value(data)                                          (0xFFFFFF00&((data)<<8))
#define PCIE_DIR_EN_timeout_cnt_value_src(data)                                      ((0xFFFFFF00&(data))>>8)
#define PCIE_DIR_EN_get_timeout_cnt_value(data)                                      ((0xFFFFFF00&(data))>>8)
#define PCIE_DIR_EN_timeout_en_shift                                                 (0)
#define PCIE_DIR_EN_timeout_en_mask                                                  (0x00000001)
#define PCIE_DIR_EN_timeout_en(data)                                                 (0x00000001&((data)<<0))
#define PCIE_DIR_EN_timeout_en_src(data)                                             ((0x00000001&(data))>>0)
#define PCIE_DIR_EN_get_timeout_en(data)                                             ((0x00000001&(data))>>0)


#define PCIE_RCPL_ST                                                                 0x18017A7C
#define PCIE_RCPL_ST_reg_addr                                                        "0xB8017A7C"
#define PCIE_RCPL_ST_reg                                                             0xB8017A7C
#define set_PCIE_RCPL_ST_reg(data)   (*((volatile unsigned int*) PCIE_RCPL_ST_reg)=data)
#define get_PCIE_RCPL_ST_reg   (*((volatile unsigned int*) PCIE_RCPL_ST_reg))
#define PCIE_RCPL_ST_inst_adr                                                        "0x009F"
#define PCIE_RCPL_ST_inst                                                            0x009F
#define PCIE_RCPL_ST_rcpl_status_shift                                               (5)
#define PCIE_RCPL_ST_rcpl_status_mask                                                (0x000000E0)
#define PCIE_RCPL_ST_rcpl_status(data)                                               (0x000000E0&((data)<<5))
#define PCIE_RCPL_ST_rcpl_status_src(data)                                           ((0x000000E0&(data))>>5)
#define PCIE_RCPL_ST_get_rcpl_status(data)                                           ((0x000000E0&(data))>>5)
#define PCIE_RCPL_ST_rcpl_error_st_shift                                             (4)
#define PCIE_RCPL_ST_rcpl_error_st_mask                                              (0x00000010)
#define PCIE_RCPL_ST_rcpl_error_st(data)                                             (0x00000010&((data)<<4))
#define PCIE_RCPL_ST_rcpl_error_st_src(data)                                         ((0x00000010&(data))>>4)
#define PCIE_RCPL_ST_get_rcpl_error_st(data)                                         ((0x00000010&(data))>>4)
#define PCIE_RCPL_ST_tlp_abort_st_shift                                              (3)
#define PCIE_RCPL_ST_tlp_abort_st_mask                                               (0x00000008)
#define PCIE_RCPL_ST_tlp_abort_st(data)                                              (0x00000008&((data)<<3))
#define PCIE_RCPL_ST_tlp_abort_st_src(data)                                          ((0x00000008&(data))>>3)
#define PCIE_RCPL_ST_get_tlp_abort_st(data)                                          ((0x00000008&(data))>>3)
#define PCIE_RCPL_ST_dllp_abort_st_shift                                             (2)
#define PCIE_RCPL_ST_dllp_abort_st_mask                                              (0x00000004)
#define PCIE_RCPL_ST_dllp_abort_st(data)                                             (0x00000004&((data)<<2))
#define PCIE_RCPL_ST_dllp_abort_st_src(data)                                         ((0x00000004&(data))>>2)
#define PCIE_RCPL_ST_get_dllp_abort_st(data)                                         ((0x00000004&(data))>>2)
#define PCIE_RCPL_ST_ecrc_error_st_shift                                             (1)
#define PCIE_RCPL_ST_ecrc_error_st_mask                                              (0x00000002)
#define PCIE_RCPL_ST_ecrc_error_st(data)                                             (0x00000002&((data)<<1))
#define PCIE_RCPL_ST_ecrc_error_st_src(data)                                         ((0x00000002&(data))>>1)
#define PCIE_RCPL_ST_get_ecrc_error_st(data)                                         ((0x00000002&(data))>>1)
#define PCIE_RCPL_ST_rcpl_timeout_st_shift                                           (0)
#define PCIE_RCPL_ST_rcpl_timeout_st_mask                                            (0x00000001)
#define PCIE_RCPL_ST_rcpl_timeout_st(data)                                           (0x00000001&((data)<<0))
#define PCIE_RCPL_ST_rcpl_timeout_st_src(data)                                       ((0x00000001&(data))>>0)
#define PCIE_RCPL_ST_get_rcpl_timeout_st(data)                                       ((0x00000001&(data))>>0)


#define PCIE_RCPL_ADR                                                                0x18017A80
#define PCIE_RCPL_ADR_reg_addr                                                       "0xB8017A80"
#define PCIE_RCPL_ADR_reg                                                            0xB8017A80
#define set_PCIE_RCPL_ADR_reg(data)   (*((volatile unsigned int*) PCIE_RCPL_ADR_reg)=data)
#define get_PCIE_RCPL_ADR_reg   (*((volatile unsigned int*) PCIE_RCPL_ADR_reg))
#define PCIE_RCPL_ADR_inst_adr                                                       "0x00A0"
#define PCIE_RCPL_ADR_inst                                                           0x00A0
#define PCIE_RCPL_ADR_nor_error_addr_shift                                           (0)
#define PCIE_RCPL_ADR_nor_error_addr_mask                                            (0xFFFFFFFF)
#define PCIE_RCPL_ADR_nor_error_addr(data)                                           (0xFFFFFFFF&((data)<<0))
#define PCIE_RCPL_ADR_nor_error_addr_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define PCIE_RCPL_ADR_get_nor_error_addr(data)                                       ((0xFFFFFFFF&(data))>>0)


#define PCIE_RCPL_TOUT0                                                              0x18017A84
#define PCIE_RCPL_TOUT0_reg_addr                                                     "0xB8017A84"
#define PCIE_RCPL_TOUT0_reg                                                          0xB8017A84
#define set_PCIE_RCPL_TOUT0_reg(data)   (*((volatile unsigned int*) PCIE_RCPL_TOUT0_reg)=data)
#define get_PCIE_RCPL_TOUT0_reg   (*((volatile unsigned int*) PCIE_RCPL_TOUT0_reg))
#define PCIE_RCPL_TOUT0_inst_adr                                                     "0x00A1"
#define PCIE_RCPL_TOUT0_inst                                                         0x00A1
#define PCIE_RCPL_TOUT0_to_error_addr_shift                                          (0)
#define PCIE_RCPL_TOUT0_to_error_addr_mask                                           (0xFFFFFFFF)
#define PCIE_RCPL_TOUT0_to_error_addr(data)                                          (0xFFFFFFFF&((data)<<0))
#define PCIE_RCPL_TOUT0_to_error_addr_src(data)                                      ((0xFFFFFFFF&(data))>>0)
#define PCIE_RCPL_TOUT0_get_to_error_addr(data)                                      ((0xFFFFFFFF&(data))>>0)


#define PCIE_RCPL_TOUT1                                                              0x18017A88
#define PCIE_RCPL_TOUT1_reg_addr                                                     "0xB8017A88"
#define PCIE_RCPL_TOUT1_reg                                                          0xB8017A88
#define set_PCIE_RCPL_TOUT1_reg(data)   (*((volatile unsigned int*) PCIE_RCPL_TOUT1_reg)=data)
#define get_PCIE_RCPL_TOUT1_reg   (*((volatile unsigned int*) PCIE_RCPL_TOUT1_reg))
#define PCIE_RCPL_TOUT1_inst_adr                                                     "0x00A2"
#define PCIE_RCPL_TOUT1_inst                                                         0x00A2
#define PCIE_RCPL_TOUT1_timeout_num_shift                                            (29)
#define PCIE_RCPL_TOUT1_timeout_num_mask                                             (0xE0000000)
#define PCIE_RCPL_TOUT1_timeout_num(data)                                            (0xE0000000&((data)<<29))
#define PCIE_RCPL_TOUT1_timeout_num_src(data)                                        ((0xE0000000&(data))>>29)
#define PCIE_RCPL_TOUT1_get_timeout_num(data)                                        ((0xE0000000&(data))>>29)
#define PCIE_RCPL_TOUT1_timeout_tc_shift                                             (26)
#define PCIE_RCPL_TOUT1_timeout_tc_mask                                              (0x1C000000)
#define PCIE_RCPL_TOUT1_timeout_tc(data)                                             (0x1C000000&((data)<<26))
#define PCIE_RCPL_TOUT1_timeout_tc_src(data)                                         ((0x1C000000&(data))>>26)
#define PCIE_RCPL_TOUT1_get_timeout_tc(data)                                         ((0x1C000000&(data))>>26)
#define PCIE_RCPL_TOUT1_timeout_attr_shift                                           (24)
#define PCIE_RCPL_TOUT1_timeout_attr_mask                                            (0x03000000)
#define PCIE_RCPL_TOUT1_timeout_attr(data)                                           (0x03000000&((data)<<24))
#define PCIE_RCPL_TOUT1_timeout_attr_src(data)                                       ((0x03000000&(data))>>24)
#define PCIE_RCPL_TOUT1_get_timeout_attr(data)                                       ((0x03000000&(data))>>24)
#define PCIE_RCPL_TOUT1_timeout_len_shift                                            (12)
#define PCIE_RCPL_TOUT1_timeout_len_mask                                             (0x00FFF000)
#define PCIE_RCPL_TOUT1_timeout_len(data)                                            (0x00FFF000&((data)<<12))
#define PCIE_RCPL_TOUT1_timeout_len_src(data)                                        ((0x00FFF000&(data))>>12)
#define PCIE_RCPL_TOUT1_get_timeout_len(data)                                        ((0x00FFF000&(data))>>12)
#define PCIE_RCPL_TOUT1_timeout_tag_shift                                            (0)
#define PCIE_RCPL_TOUT1_timeout_tag_mask                                             (0x000000FF)
#define PCIE_RCPL_TOUT1_timeout_tag(data)                                            (0x000000FF&((data)<<0))
#define PCIE_RCPL_TOUT1_timeout_tag_src(data)                                        ((0x000000FF&(data))>>0)
#define PCIE_RCPL_TOUT1_get_timeout_tag(data)                                        ((0x000000FF&(data))>>0)


#define PCIE_RTGT_ST                                                                 0x18017A8C
#define PCIE_RTGT_ST_reg_addr                                                        "0xB8017A8C"
#define PCIE_RTGT_ST_reg                                                             0xB8017A8C
#define set_PCIE_RTGT_ST_reg(data)   (*((volatile unsigned int*) PCIE_RTGT_ST_reg)=data)
#define get_PCIE_RTGT_ST_reg   (*((volatile unsigned int*) PCIE_RTGT_ST_reg))
#define PCIE_RTGT_ST_inst_adr                                                        "0x00A3"
#define PCIE_RTGT_ST_inst                                                            0x00A3
#define PCIE_RTGT_ST_rcpl_compl_st_shift                                             (4)
#define PCIE_RTGT_ST_rcpl_compl_st_mask                                              (0x00000010)
#define PCIE_RTGT_ST_rcpl_compl_st(data)                                             (0x00000010&((data)<<4))
#define PCIE_RTGT_ST_rcpl_compl_st_src(data)                                         ((0x00000010&(data))>>4)
#define PCIE_RTGT_ST_get_rcpl_compl_st(data)                                         ((0x00000010&(data))>>4)
#define PCIE_RTGT_ST_tlp_abort_st_shift                                              (3)
#define PCIE_RTGT_ST_tlp_abort_st_mask                                               (0x00000008)
#define PCIE_RTGT_ST_tlp_abort_st(data)                                              (0x00000008&((data)<<3))
#define PCIE_RTGT_ST_tlp_abort_st_src(data)                                          ((0x00000008&(data))>>3)
#define PCIE_RTGT_ST_get_tlp_abort_st(data)                                          ((0x00000008&(data))>>3)
#define PCIE_RTGT_ST_dllp_abort_st_shift                                             (2)
#define PCIE_RTGT_ST_dllp_abort_st_mask                                              (0x00000004)
#define PCIE_RTGT_ST_dllp_abort_st(data)                                             (0x00000004&((data)<<2))
#define PCIE_RTGT_ST_dllp_abort_st_src(data)                                         ((0x00000004&(data))>>2)
#define PCIE_RTGT_ST_get_dllp_abort_st(data)                                         ((0x00000004&(data))>>2)
#define PCIE_RTGT_ST_ecrc_error_st_shift                                             (1)
#define PCIE_RTGT_ST_ecrc_error_st_mask                                              (0x00000002)
#define PCIE_RTGT_ST_ecrc_error_st(data)                                             (0x00000002&((data)<<1))
#define PCIE_RTGT_ST_ecrc_error_st_src(data)                                         ((0x00000002&(data))>>1)
#define PCIE_RTGT_ST_get_ecrc_error_st(data)                                         ((0x00000002&(data))>>1)
#define PCIE_RTGT_ST_rcpl_timeout_st_shift                                           (0)
#define PCIE_RTGT_ST_rcpl_timeout_st_mask                                            (0x00000001)
#define PCIE_RTGT_ST_rcpl_timeout_st(data)                                           (0x00000001&((data)<<0))
#define PCIE_RTGT_ST_rcpl_timeout_st_src(data)                                       ((0x00000001&(data))>>0)
#define PCIE_RTGT_ST_get_rcpl_timeout_st(data)                                       ((0x00000001&(data))>>0)


#define PCIE_RTGT_ADR                                                                0x18017A90
#define PCIE_RTGT_ADR_reg_addr                                                       "0xB8017A90"
#define PCIE_RTGT_ADR_reg                                                            0xB8017A90
#define set_PCIE_RTGT_ADR_reg(data)   (*((volatile unsigned int*) PCIE_RTGT_ADR_reg)=data)
#define get_PCIE_RTGT_ADR_reg   (*((volatile unsigned int*) PCIE_RTGT_ADR_reg))
#define PCIE_RTGT_ADR_inst_adr                                                       "0x00A4"
#define PCIE_RTGT_ADR_inst                                                           0x00A4
#define PCIE_RTGT_ADR_nor_error_addr_shift                                           (0)
#define PCIE_RTGT_ADR_nor_error_addr_mask                                            (0xFFFFFFFF)
#define PCIE_RTGT_ADR_nor_error_addr(data)                                           (0xFFFFFFFF&((data)<<0))
#define PCIE_RTGT_ADR_nor_error_addr_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define PCIE_RTGT_ADR_get_nor_error_addr(data)                                       ((0xFFFFFFFF&(data))>>0)


#define PCIE_RTGT_TOUT0                                                              0x18017A94
#define PCIE_RTGT_TOUT0_reg_addr                                                     "0xB8017A94"
#define PCIE_RTGT_TOUT0_reg                                                          0xB8017A94
#define set_PCIE_RTGT_TOUT0_reg(data)   (*((volatile unsigned int*) PCIE_RTGT_TOUT0_reg)=data)
#define get_PCIE_RTGT_TOUT0_reg   (*((volatile unsigned int*) PCIE_RTGT_TOUT0_reg))
#define PCIE_RTGT_TOUT0_inst_adr                                                     "0x00A5"
#define PCIE_RTGT_TOUT0_inst                                                         0x00A5
#define PCIE_RTGT_TOUT0_to_error_addr_shift                                          (0)
#define PCIE_RTGT_TOUT0_to_error_addr_mask                                           (0xFFFFFFFF)
#define PCIE_RTGT_TOUT0_to_error_addr(data)                                          (0xFFFFFFFF&((data)<<0))
#define PCIE_RTGT_TOUT0_to_error_addr_src(data)                                      ((0xFFFFFFFF&(data))>>0)
#define PCIE_RTGT_TOUT0_get_to_error_addr(data)                                      ((0xFFFFFFFF&(data))>>0)


#define PCIE_RTGT_TOUT1                                                              0x18017A98
#define PCIE_RTGT_TOUT1_reg_addr                                                     "0xB8017A98"
#define PCIE_RTGT_TOUT1_reg                                                          0xB8017A98
#define set_PCIE_RTGT_TOUT1_reg(data)   (*((volatile unsigned int*) PCIE_RTGT_TOUT1_reg)=data)
#define get_PCIE_RTGT_TOUT1_reg   (*((volatile unsigned int*) PCIE_RTGT_TOUT1_reg))
#define PCIE_RTGT_TOUT1_inst_adr                                                     "0x00A6"
#define PCIE_RTGT_TOUT1_inst                                                         0x00A6
#define PCIE_RTGT_TOUT1_timeout_num_shift                                            (29)
#define PCIE_RTGT_TOUT1_timeout_num_mask                                             (0xE0000000)
#define PCIE_RTGT_TOUT1_timeout_num(data)                                            (0xE0000000&((data)<<29))
#define PCIE_RTGT_TOUT1_timeout_num_src(data)                                        ((0xE0000000&(data))>>29)
#define PCIE_RTGT_TOUT1_get_timeout_num(data)                                        ((0xE0000000&(data))>>29)
#define PCIE_RTGT_TOUT1_timeout_tc_shift                                             (26)
#define PCIE_RTGT_TOUT1_timeout_tc_mask                                              (0x1C000000)
#define PCIE_RTGT_TOUT1_timeout_tc(data)                                             (0x1C000000&((data)<<26))
#define PCIE_RTGT_TOUT1_timeout_tc_src(data)                                         ((0x1C000000&(data))>>26)
#define PCIE_RTGT_TOUT1_get_timeout_tc(data)                                         ((0x1C000000&(data))>>26)
#define PCIE_RTGT_TOUT1_timeout_attr_shift                                           (24)
#define PCIE_RTGT_TOUT1_timeout_attr_mask                                            (0x03000000)
#define PCIE_RTGT_TOUT1_timeout_attr(data)                                           (0x03000000&((data)<<24))
#define PCIE_RTGT_TOUT1_timeout_attr_src(data)                                       ((0x03000000&(data))>>24)
#define PCIE_RTGT_TOUT1_get_timeout_attr(data)                                       ((0x03000000&(data))>>24)
#define PCIE_RTGT_TOUT1_timeout_len_shift                                            (12)
#define PCIE_RTGT_TOUT1_timeout_len_mask                                             (0x00FFF000)
#define PCIE_RTGT_TOUT1_timeout_len(data)                                            (0x00FFF000&((data)<<12))
#define PCIE_RTGT_TOUT1_timeout_len_src(data)                                        ((0x00FFF000&(data))>>12)
#define PCIE_RTGT_TOUT1_get_timeout_len(data)                                        ((0x00FFF000&(data))>>12)
#define PCIE_RTGT_TOUT1_timeout_tag_shift                                            (0)
#define PCIE_RTGT_TOUT1_timeout_tag_mask                                             (0x000000FF)
#define PCIE_RTGT_TOUT1_timeout_tag(data)                                            (0x000000FF&((data)<<0))
#define PCIE_RTGT_TOUT1_timeout_tag_src(data)                                        ((0x000000FF&(data))>>0)
#define PCIE_RTGT_TOUT1_get_timeout_tag(data)                                        ((0x000000FF&(data))>>0)


#define PCIE_AERRO_ST                                                                0x18017A9C
#define PCIE_AERRO_ST_reg_addr                                                       "0xB8017A9C"
#define PCIE_AERRO_ST_reg                                                            0xB8017A9C
#define set_PCIE_AERRO_ST_reg(data)   (*((volatile unsigned int*) PCIE_AERRO_ST_reg)=data)
#define get_PCIE_AERRO_ST_reg   (*((volatile unsigned int*) PCIE_AERRO_ST_reg))
#define PCIE_AERRO_ST_inst_adr                                                       "0x00A7"
#define PCIE_AERRO_ST_inst                                                           0x00A7
#define PCIE_AERRO_ST_cfg_sys_err_rc_shift                                           (0)
#define PCIE_AERRO_ST_cfg_sys_err_rc_mask                                            (0x00000001)
#define PCIE_AERRO_ST_cfg_sys_err_rc(data)                                           (0x00000001&((data)<<0))
#define PCIE_AERRO_ST_cfg_sys_err_rc_src(data)                                       ((0x00000001&(data))>>0)
#define PCIE_AERRO_ST_get_cfg_sys_err_rc(data)                                       ((0x00000001&(data))>>0)


#define PCIE_AEMSI_ST                                                                0x18017AA0
#define PCIE_AEMSI_ST_reg_addr                                                       "0xB8017AA0"
#define PCIE_AEMSI_ST_reg                                                            0xB8017AA0
#define set_PCIE_AEMSI_ST_reg(data)   (*((volatile unsigned int*) PCIE_AEMSI_ST_reg)=data)
#define get_PCIE_AEMSI_ST_reg   (*((volatile unsigned int*) PCIE_AEMSI_ST_reg))
#define PCIE_AEMSI_ST_inst_adr                                                       "0x00A8"
#define PCIE_AEMSI_ST_inst                                                           0x00A8
#define PCIE_AEMSI_ST_cfg_aer_int_msg_num_shift                                      (1)
#define PCIE_AEMSI_ST_cfg_aer_int_msg_num_mask                                       (0x0000003E)
#define PCIE_AEMSI_ST_cfg_aer_int_msg_num(data)                                      (0x0000003E&((data)<<1))
#define PCIE_AEMSI_ST_cfg_aer_int_msg_num_src(data)                                  ((0x0000003E&(data))>>1)
#define PCIE_AEMSI_ST_get_cfg_aer_int_msg_num(data)                                  ((0x0000003E&(data))>>1)
#define PCIE_AEMSI_ST_cfg_aer_rc_err_msi_shift                                       (0)
#define PCIE_AEMSI_ST_cfg_aer_rc_err_msi_mask                                        (0x00000001)
#define PCIE_AEMSI_ST_cfg_aer_rc_err_msi(data)                                       (0x00000001&((data)<<0))
#define PCIE_AEMSI_ST_cfg_aer_rc_err_msi_src(data)                                   ((0x00000001&(data))>>0)
#define PCIE_AEMSI_ST_get_cfg_aer_rc_err_msi(data)                                   ((0x00000001&(data))>>0)


#define PCIE_PME_ST                                                                  0x18017AA4
#define PCIE_PME_ST_reg_addr                                                         "0xB8017AA4"
#define PCIE_PME_ST_reg                                                              0xB8017AA4
#define set_PCIE_PME_ST_reg(data)   (*((volatile unsigned int*) PCIE_PME_ST_reg)=data)
#define get_PCIE_PME_ST_reg   (*((volatile unsigned int*) PCIE_PME_ST_reg))
#define PCIE_PME_ST_inst_adr                                                         "0x00A9"
#define PCIE_PME_ST_inst                                                             0x00A9
#define PCIE_PME_ST_radm_pm_to_ack_shift                                             (0)
#define PCIE_PME_ST_radm_pm_to_ack_mask                                              (0x00000001)
#define PCIE_PME_ST_radm_pm_to_ack(data)                                             (0x00000001&((data)<<0))
#define PCIE_PME_ST_radm_pm_to_ack_src(data)                                         ((0x00000001&(data))>>0)
#define PCIE_PME_ST_get_radm_pm_to_ack(data)                                         ((0x00000001&(data))>>0)


#define PCIE_PMMSI_ST                                                                0x18017AA8
#define PCIE_PMMSI_ST_reg_addr                                                       "0xB8017AA8"
#define PCIE_PMMSI_ST_reg                                                            0xB8017AA8
#define set_PCIE_PMMSI_ST_reg(data)   (*((volatile unsigned int*) PCIE_PMMSI_ST_reg)=data)
#define get_PCIE_PMMSI_ST_reg   (*((volatile unsigned int*) PCIE_PMMSI_ST_reg))
#define PCIE_PMMSI_ST_inst_adr                                                       "0x00AA"
#define PCIE_PMMSI_ST_inst                                                           0x00AA
#define PCIE_PMMSI_ST_cfg_cap_int_msg_num_shift                                      (1)
#define PCIE_PMMSI_ST_cfg_cap_int_msg_num_mask                                       (0x0000003E)
#define PCIE_PMMSI_ST_cfg_cap_int_msg_num(data)                                      (0x0000003E&((data)<<1))
#define PCIE_PMMSI_ST_cfg_cap_int_msg_num_src(data)                                  ((0x0000003E&(data))>>1)
#define PCIE_PMMSI_ST_get_cfg_cap_int_msg_num(data)                                  ((0x0000003E&(data))>>1)
#define PCIE_PMMSI_ST_cfg_pme_msi_shift                                              (0)
#define PCIE_PMMSI_ST_cfg_pme_msi_mask                                               (0x00000001)
#define PCIE_PMMSI_ST_cfg_pme_msi(data)                                              (0x00000001&((data)<<0))
#define PCIE_PMMSI_ST_cfg_pme_msi_src(data)                                          ((0x00000001&(data))>>0)
#define PCIE_PMMSI_ST_get_cfg_pme_msi(data)                                          ((0x00000001&(data))>>0)


#define PCIE_VEN_MSG0                                                                0x18017AAC
#define PCIE_VEN_MSG0_reg_addr                                                       "0xB8017AAC"
#define PCIE_VEN_MSG0_reg                                                            0xB8017AAC
#define set_PCIE_VEN_MSG0_reg(data)   (*((volatile unsigned int*) PCIE_VEN_MSG0_reg)=data)
#define get_PCIE_VEN_MSG0_reg   (*((volatile unsigned int*) PCIE_VEN_MSG0_reg))
#define PCIE_VEN_MSG0_inst_adr                                                       "0x00AB"
#define PCIE_VEN_MSG0_inst                                                           0x00AB
#define PCIE_VEN_MSG0_radm_msg_req_id_shift                                          (16)
#define PCIE_VEN_MSG0_radm_msg_req_id_mask                                           (0xFFFF0000)
#define PCIE_VEN_MSG0_radm_msg_req_id(data)                                          (0xFFFF0000&((data)<<16))
#define PCIE_VEN_MSG0_radm_msg_req_id_src(data)                                      ((0xFFFF0000&(data))>>16)
#define PCIE_VEN_MSG0_get_radm_msg_req_id(data)                                      ((0xFFFF0000&(data))>>16)
#define PCIE_VEN_MSG0_radm_vendor_msg_shift                                          (0)
#define PCIE_VEN_MSG0_radm_vendor_msg_mask                                           (0x00000001)
#define PCIE_VEN_MSG0_radm_vendor_msg(data)                                          (0x00000001&((data)<<0))
#define PCIE_VEN_MSG0_radm_vendor_msg_src(data)                                      ((0x00000001&(data))>>0)
#define PCIE_VEN_MSG0_get_radm_vendor_msg(data)                                      ((0x00000001&(data))>>0)


#define PCIE_VEN_MSG1                                                                0x18017AB0
#define PCIE_VEN_MSG1_reg_addr                                                       "0xB8017AB0"
#define PCIE_VEN_MSG1_reg                                                            0xB8017AB0
#define set_PCIE_VEN_MSG1_reg(data)   (*((volatile unsigned int*) PCIE_VEN_MSG1_reg)=data)
#define get_PCIE_VEN_MSG1_reg   (*((volatile unsigned int*) PCIE_VEN_MSG1_reg))
#define PCIE_VEN_MSG1_inst_adr                                                       "0x00AC"
#define PCIE_VEN_MSG1_inst                                                           0x00AC
#define PCIE_VEN_MSG1_radm_msg_payload_shift                                         (0)
#define PCIE_VEN_MSG1_radm_msg_payload_mask                                          (0xFFFFFFFF)
#define PCIE_VEN_MSG1_radm_msg_payload(data)                                         (0xFFFFFFFF&((data)<<0))
#define PCIE_VEN_MSG1_radm_msg_payload_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define PCIE_VEN_MSG1_get_radm_msg_payload(data)                                     ((0xFFFFFFFF&(data))>>0)


#define PCIE_MAC_ST                                                                  0x18017AB4
#define PCIE_MAC_ST_reg_addr                                                         "0xB8017AB4"
#define PCIE_MAC_ST_reg                                                              0xB8017AB4
#define set_PCIE_MAC_ST_reg(data)   (*((volatile unsigned int*) PCIE_MAC_ST_reg)=data)
#define get_PCIE_MAC_ST_reg   (*((volatile unsigned int*) PCIE_MAC_ST_reg))
#define PCIE_MAC_ST_inst_adr                                                         "0x00AD"
#define PCIE_MAC_ST_inst                                                             0x00AD
#define PCIE_MAC_ST_rdlh_link_up_shift                                               (14)
#define PCIE_MAC_ST_rdlh_link_up_mask                                                (0x00004000)
#define PCIE_MAC_ST_rdlh_link_up(data)                                               (0x00004000&((data)<<14))
#define PCIE_MAC_ST_rdlh_link_up_src(data)                                           ((0x00004000&(data))>>14)
#define PCIE_MAC_ST_get_rdlh_link_up(data)                                           ((0x00004000&(data))>>14)
#define PCIE_MAC_ST_pm_xtlh_block_tlp_shift                                          (13)
#define PCIE_MAC_ST_pm_xtlh_block_tlp_mask                                           (0x00002000)
#define PCIE_MAC_ST_pm_xtlh_block_tlp(data)                                          (0x00002000&((data)<<13))
#define PCIE_MAC_ST_pm_xtlh_block_tlp_src(data)                                      ((0x00002000&(data))>>13)
#define PCIE_MAC_ST_get_pm_xtlh_block_tlp(data)                                      ((0x00002000&(data))>>13)
#define PCIE_MAC_ST_cfg_bus_master_en_shift                                          (12)
#define PCIE_MAC_ST_cfg_bus_master_en_mask                                           (0x00001000)
#define PCIE_MAC_ST_cfg_bus_master_en(data)                                          (0x00001000&((data)<<12))
#define PCIE_MAC_ST_cfg_bus_master_en_src(data)                                      ((0x00001000&(data))>>12)
#define PCIE_MAC_ST_get_cfg_bus_master_en(data)                                      ((0x00001000&(data))>>12)
#define PCIE_MAC_ST_cfg_pm_no_soft_rst_shift                                         (11)
#define PCIE_MAC_ST_cfg_pm_no_soft_rst_mask                                          (0x00000800)
#define PCIE_MAC_ST_cfg_pm_no_soft_rst(data)                                         (0x00000800&((data)<<11))
#define PCIE_MAC_ST_cfg_pm_no_soft_rst_src(data)                                     ((0x00000800&(data))>>11)
#define PCIE_MAC_ST_get_cfg_pm_no_soft_rst(data)                                     ((0x00000800&(data))>>11)
#define PCIE_MAC_ST_xmlh_link_up_shift                                               (10)
#define PCIE_MAC_ST_xmlh_link_up_mask                                                (0x00000400)
#define PCIE_MAC_ST_xmlh_link_up(data)                                               (0x00000400&((data)<<10))
#define PCIE_MAC_ST_xmlh_link_up_src(data)                                           ((0x00000400&(data))>>10)
#define PCIE_MAC_ST_get_xmlh_link_up(data)                                           ((0x00000400&(data))>>10)
#define PCIE_MAC_ST_link_req_rst_not_shift                                           (9)
#define PCIE_MAC_ST_link_req_rst_not_mask                                            (0x00000200)
#define PCIE_MAC_ST_link_req_rst_not(data)                                           (0x00000200&((data)<<9))
#define PCIE_MAC_ST_link_req_rst_not_src(data)                                       ((0x00000200&(data))>>9)
#define PCIE_MAC_ST_get_link_req_rst_not(data)                                       ((0x00000200&(data))>>9)
#define PCIE_MAC_ST_xmlh_ltssm_state_shift                                           (4)
#define PCIE_MAC_ST_xmlh_ltssm_state_mask                                            (0x000001F0)
#define PCIE_MAC_ST_xmlh_ltssm_state(data)                                           (0x000001F0&((data)<<4))
#define PCIE_MAC_ST_xmlh_ltssm_state_src(data)                                       ((0x000001F0&(data))>>4)
#define PCIE_MAC_ST_get_xmlh_ltssm_state(data)                                       ((0x000001F0&(data))>>4)
#define PCIE_MAC_ST_pm_curnt_state_shift                                             (1)
#define PCIE_MAC_ST_pm_curnt_state_mask                                              (0x0000000E)
#define PCIE_MAC_ST_pm_curnt_state(data)                                             (0x0000000E&((data)<<1))
#define PCIE_MAC_ST_pm_curnt_state_src(data)                                         ((0x0000000E&(data))>>1)
#define PCIE_MAC_ST_get_pm_curnt_state(data)                                         ((0x0000000E&(data))>>1)
#define PCIE_MAC_ST_clk_req_n_shift                                                  (0)
#define PCIE_MAC_ST_clk_req_n_mask                                                   (0x00000001)
#define PCIE_MAC_ST_clk_req_n(data)                                                  (0x00000001&((data)<<0))
#define PCIE_MAC_ST_clk_req_n_src(data)                                              ((0x00000001&(data))>>0)
#define PCIE_MAC_ST_get_clk_req_n(data)                                              ((0x00000001&(data))>>0)


#define PCIE_UNLOCK_MSG                                                              0x18017AB8
#define PCIE_UNLOCK_MSG_reg_addr                                                     "0xB8017AB8"
#define PCIE_UNLOCK_MSG_reg                                                          0xB8017AB8
#define set_PCIE_UNLOCK_MSG_reg(data)   (*((volatile unsigned int*) PCIE_UNLOCK_MSG_reg)=data)
#define get_PCIE_UNLOCK_MSG_reg   (*((volatile unsigned int*) PCIE_UNLOCK_MSG_reg))
#define PCIE_UNLOCK_MSG_inst_adr                                                     "0x00AE"
#define PCIE_UNLOCK_MSG_inst                                                         0x00AE
#define PCIE_UNLOCK_MSG_unlock_msg_trigger_shift                                     (0)
#define PCIE_UNLOCK_MSG_unlock_msg_trigger_mask                                      (0x00000001)
#define PCIE_UNLOCK_MSG_unlock_msg_trigger(data)                                     (0x00000001&((data)<<0))
#define PCIE_UNLOCK_MSG_unlock_msg_trigger_src(data)                                 ((0x00000001&(data))>>0)
#define PCIE_UNLOCK_MSG_get_unlock_msg_trigger(data)                                 ((0x00000001&(data))>>0)


#define PCIE_SCTCH                                                                   0x18017ABC
#define PCIE_SCTCH_reg_addr                                                          "0xB8017ABC"
#define PCIE_SCTCH_reg                                                               0xB8017ABC
#define set_PCIE_SCTCH_reg(data)   (*((volatile unsigned int*) PCIE_SCTCH_reg)=data)
#define get_PCIE_SCTCH_reg   (*((volatile unsigned int*) PCIE_SCTCH_reg))
#define PCIE_SCTCH_inst_adr                                                          "0x00AF"
#define PCIE_SCTCH_inst                                                              0x00AF
#define PCIE_SCTCH_reg1_shift                                                        (16)
#define PCIE_SCTCH_reg1_mask                                                         (0xFFFF0000)
#define PCIE_SCTCH_reg1(data)                                                        (0xFFFF0000&((data)<<16))
#define PCIE_SCTCH_reg1_src(data)                                                    ((0xFFFF0000&(data))>>16)
#define PCIE_SCTCH_get_reg1(data)                                                    ((0xFFFF0000&(data))>>16)
#define PCIE_SCTCH_reg0_shift                                                        (0)
#define PCIE_SCTCH_reg0_mask                                                         (0x0000FFFF)
#define PCIE_SCTCH_reg0(data)                                                        (0x0000FFFF&((data)<<0))
#define PCIE_SCTCH_reg0_src(data)                                                    ((0x0000FFFF&(data))>>0)
#define PCIE_SCTCH_get_reg0(data)                                                    ((0x0000FFFF&(data))>>0)


#define PCIE_LOOP_DATA_0                                                             0x18017AC0
#define PCIE_LOOP_DATA_1                                                             0x18017AC4
#define PCIE_LOOP_DATA_2                                                             0x18017AC8
#define PCIE_LOOP_DATA_3                                                             0x18017ACC
#define PCIE_LOOP_DATA_0_reg_addr                                                    "0xB8017AC0"
#define PCIE_LOOP_DATA_1_reg_addr                                                    "0xB8017AC4"
#define PCIE_LOOP_DATA_2_reg_addr                                                    "0xB8017AC8"
#define PCIE_LOOP_DATA_3_reg_addr                                                    "0xB8017ACC"
#define PCIE_LOOP_DATA_0_reg                                                         0xB8017AC0
#define PCIE_LOOP_DATA_1_reg                                                         0xB8017AC4
#define PCIE_LOOP_DATA_2_reg                                                         0xB8017AC8
#define PCIE_LOOP_DATA_3_reg                                                         0xB8017ACC
#define set_PCIE_LOOP_DATA_0_reg(data)   (*((volatile unsigned int*) PCIE_LOOP_DATA_0_reg)=data)
#define set_PCIE_LOOP_DATA_1_reg(data)   (*((volatile unsigned int*) PCIE_LOOP_DATA_1_reg)=data)
#define set_PCIE_LOOP_DATA_2_reg(data)   (*((volatile unsigned int*) PCIE_LOOP_DATA_2_reg)=data)
#define set_PCIE_LOOP_DATA_3_reg(data)   (*((volatile unsigned int*) PCIE_LOOP_DATA_3_reg)=data)
#define get_PCIE_LOOP_DATA_0_reg   (*((volatile unsigned int*) PCIE_LOOP_DATA_0_reg))
#define get_PCIE_LOOP_DATA_1_reg   (*((volatile unsigned int*) PCIE_LOOP_DATA_1_reg))
#define get_PCIE_LOOP_DATA_2_reg   (*((volatile unsigned int*) PCIE_LOOP_DATA_2_reg))
#define get_PCIE_LOOP_DATA_3_reg   (*((volatile unsigned int*) PCIE_LOOP_DATA_3_reg))
#define PCIE_LOOP_DATA_0_inst_adr                                                    "0x00B0"
#define PCIE_LOOP_DATA_1_inst_adr                                                    "0x00B1"
#define PCIE_LOOP_DATA_2_inst_adr                                                    "0x00B2"
#define PCIE_LOOP_DATA_3_inst_adr                                                    "0x00B3"
#define PCIE_LOOP_DATA_0_inst                                                        0x00B0
#define PCIE_LOOP_DATA_1_inst                                                        0x00B1
#define PCIE_LOOP_DATA_2_inst                                                        0x00B2
#define PCIE_LOOP_DATA_3_inst                                                        0x00B3
#define PCIE_LOOP_DATA_rw_data_shift                                                 (0)
#define PCIE_LOOP_DATA_rw_data_mask                                                  (0xFFFFFFFF)
#define PCIE_LOOP_DATA_rw_data(data)                                                 (0xFFFFFFFF&((data)<<0))
#define PCIE_LOOP_DATA_rw_data_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define PCIE_LOOP_DATA_get_rw_data(data)                                             ((0xFFFFFFFF&(data))>>0)


#define PCIE_MSI_TRAN                                                                0x18017AD0
#define PCIE_MSI_TRAN_reg_addr                                                       "0xB8017AD0"
#define PCIE_MSI_TRAN_reg                                                            0xB8017AD0
#define set_PCIE_MSI_TRAN_reg(data)   (*((volatile unsigned int*) PCIE_MSI_TRAN_reg)=data)
#define get_PCIE_MSI_TRAN_reg   (*((volatile unsigned int*) PCIE_MSI_TRAN_reg))
#define PCIE_MSI_TRAN_inst_adr                                                       "0x00B4"
#define PCIE_MSI_TRAN_inst                                                           0x00B4
#define PCIE_MSI_TRAN_msi_check_addr_shift                                           (2)
#define PCIE_MSI_TRAN_msi_check_addr_mask                                            (0xFFFFFFFC)
#define PCIE_MSI_TRAN_msi_check_addr(data)                                           (0xFFFFFFFC&((data)<<2))
#define PCIE_MSI_TRAN_msi_check_addr_src(data)                                       ((0xFFFFFFFC&(data))>>2)
#define PCIE_MSI_TRAN_get_msi_check_addr(data)                                       ((0xFFFFFFFC&(data))>>2)


#define PCIE_MSI_DATA                                                                0x18017AD4
#define PCIE_MSI_DATA_reg_addr                                                       "0xB8017AD4"
#define PCIE_MSI_DATA_reg                                                            0xB8017AD4
#define set_PCIE_MSI_DATA_reg(data)   (*((volatile unsigned int*) PCIE_MSI_DATA_reg)=data)
#define get_PCIE_MSI_DATA_reg   (*((volatile unsigned int*) PCIE_MSI_DATA_reg))
#define PCIE_MSI_DATA_inst_adr                                                       "0x00B5"
#define PCIE_MSI_DATA_inst                                                           0x00B5
#define PCIE_MSI_DATA_msi_data_st_shift                                              (16)
#define PCIE_MSI_DATA_msi_data_st_mask                                               (0x00010000)
#define PCIE_MSI_DATA_msi_data_st(data)                                              (0x00010000&((data)<<16))
#define PCIE_MSI_DATA_msi_data_st_src(data)                                          ((0x00010000&(data))>>16)
#define PCIE_MSI_DATA_get_msi_data_st(data)                                          ((0x00010000&(data))>>16)
#define PCIE_MSI_DATA_msi_data_shift                                                 (0)
#define PCIE_MSI_DATA_msi_data_mask                                                  (0x0000FFFF)
#define PCIE_MSI_DATA_msi_data(data)                                                 (0x0000FFFF&((data)<<0))
#define PCIE_MSI_DATA_msi_data_src(data)                                             ((0x0000FFFF&(data))>>0)
#define PCIE_MSI_DATA_get_msi_data(data)                                             ((0x0000FFFF&(data))>>0)


#define PCIE_TMP_REG_0                                                               0x18017AD8
#define PCIE_TMP_REG_1                                                               0x18017ADC
#define PCIE_TMP_REG_2                                                               0x18017AE0
#define PCIE_TMP_REG_3                                                               0x18017AE4
#define PCIE_TMP_REG_0_reg_addr                                                      "0xB8017AD8"
#define PCIE_TMP_REG_1_reg_addr                                                      "0xB8017ADC"
#define PCIE_TMP_REG_2_reg_addr                                                      "0xB8017AE0"
#define PCIE_TMP_REG_3_reg_addr                                                      "0xB8017AE4"
#define PCIE_TMP_REG_0_reg                                                           0xB8017AD8
#define PCIE_TMP_REG_1_reg                                                           0xB8017ADC
#define PCIE_TMP_REG_2_reg                                                           0xB8017AE0
#define PCIE_TMP_REG_3_reg                                                           0xB8017AE4
#define set_PCIE_TMP_REG_0_reg(data)   (*((volatile unsigned int*) PCIE_TMP_REG_0_reg)=data)
#define set_PCIE_TMP_REG_1_reg(data)   (*((volatile unsigned int*) PCIE_TMP_REG_1_reg)=data)
#define set_PCIE_TMP_REG_2_reg(data)   (*((volatile unsigned int*) PCIE_TMP_REG_2_reg)=data)
#define set_PCIE_TMP_REG_3_reg(data)   (*((volatile unsigned int*) PCIE_TMP_REG_3_reg)=data)
#define get_PCIE_TMP_REG_0_reg   (*((volatile unsigned int*) PCIE_TMP_REG_0_reg))
#define get_PCIE_TMP_REG_1_reg   (*((volatile unsigned int*) PCIE_TMP_REG_1_reg))
#define get_PCIE_TMP_REG_2_reg   (*((volatile unsigned int*) PCIE_TMP_REG_2_reg))
#define get_PCIE_TMP_REG_3_reg   (*((volatile unsigned int*) PCIE_TMP_REG_3_reg))
#define PCIE_TMP_REG_0_inst_adr                                                      "0x00B6"
#define PCIE_TMP_REG_1_inst_adr                                                      "0x00B7"
#define PCIE_TMP_REG_2_inst_adr                                                      "0x00B8"
#define PCIE_TMP_REG_3_inst_adr                                                      "0x00B9"
#define PCIE_TMP_REG_0_inst                                                          0x00B6
#define PCIE_TMP_REG_1_inst                                                          0x00B7
#define PCIE_TMP_REG_2_inst                                                          0x00B8
#define PCIE_TMP_REG_3_inst                                                          0x00B9
#define PCIE_TMP_REG_test_reg_shift                                                  (0)
#define PCIE_TMP_REG_test_reg_mask                                                   (0xFFFFFFFF)
#define PCIE_TMP_REG_test_reg(data)                                                  (0xFFFFFFFF&((data)<<0))
#define PCIE_TMP_REG_test_reg_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define PCIE_TMP_REG_get_test_reg(data)                                              ((0xFFFFFFFF&(data))>>0)


#endif
