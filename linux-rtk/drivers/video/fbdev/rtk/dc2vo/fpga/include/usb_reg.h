/**************************************************************
// Spec Version                  : 0.0.2
// Parser Version                : MAR_Parser_1.0
// CModelGen Version             : 4.1 2009.03.10
// Naming Rule                   : Register_Name_reg
// Firmware Header Generate Date : 2010/7/27
***************************************************************/


#ifndef _USB_REG_H_INCLUDED_
#define _USB_REG_H_INCLUDED_
#ifdef  _USB_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     sram_debug_sel:1;
unsigned int     sram_debug_mode:1;
unsigned int     dbus_multi_req_disable:1;
unsigned int     dev_mode:1;
}WRAP_CTR;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     device_int:1;
unsigned int     host_int:1;
}GNR_INT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     reset_utmi_p0:1;
}USB2_PHY_UTMI;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     reset_pipe3_p0:1;
}USB3_PHY_PIPE;

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
}MDIO_CTR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     p0_vstatus_out:8;
}VSTATUS0_OUT;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     simulation_mode_p0:1;
unsigned int     force_hs_mode_p0:1;
unsigned int     test_rst_p0:1;
unsigned int     test_en_p0:1;
}SLP_BACK0_EN;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     test_speed_p0:2;
unsigned int     test_seed_p0:8;
unsigned int     test_psl_p0:2;
}SLP_BACK0_CTR;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     test_fail_p0:1;
unsigned int     test_done_p0:1;
}SLP_BACK0_ST;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     p0_usb2phy_slb_hs:1;
unsigned int     p0_usb2phy_force_slb:1;
}PHY2_SLB_EN;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     p0_usb2phy_slb_fail:1;
unsigned int     p0_usb2phy_slb_done:1;
}PHY2_SLB_ST;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     p0_suspend_r:1;
}USB2_SPD_CTR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     p0_pipe_bist_sel:2;
unsigned int     p0_pipe_bist_en:1;
}PHY3_SLB_EN;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     p0_usb3phy_slb_go:1;
}PHY3_SLB_CT;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     p0_usb3phy_slb_fail:1;
unsigned int     p0_usb3phy_slb_done:1;
}PHY3_SLB_ST;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     dbg_sel1:6;
unsigned int     dbg_sel0:6;
unsigned int     dbg_en:1;
}USB_DBG;

typedef struct 
{
unsigned int     reg1:16;
unsigned int     reg0:16;
}USB_SCTCH;

typedef struct 
{
unsigned int     test_sp_reg:32;
}USB_TMP_SP;

typedef struct 
{
unsigned int     test_reg:32;
}USB_TMP;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     host_utmiotg_vbusvalid:1;
unsigned int     host_fladj_30mhz:6;
unsigned int     host_ppc_present:1;
unsigned int     host_msi_enable:1;
unsigned int     host_pm_pw_state_req:2;
unsigned int     hub_port_over_current:4;
unsigned int     reserved_1:2;
unsigned int     hub_port_perm_attach:2;
unsigned int     reserved_2:2;
unsigned int     host_u2_port_disable:1;
unsigned int     host_u3_port_disable:1;
unsigned int     host_num_u2_port:4;
unsigned int     host_num_u3_port:4;
}HMAC_CTR0;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     host_current_power_state:2;
unsigned int     host_hub_vbus_ctrl:2;
}MAC3_HST_ST;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     dev_vbus_value:1;
unsigned int     dev_utmiotg_vbusvalid:1;
unsigned int     dev_pm_pw_state_req:2;
unsigned int     dev_fladj_30mhz:6;
unsigned int     dev_usb_outep_pkt_buff:16;
}DMAC_CTR0;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     dev_current_power_state:2;
}MAC3_DEV_ST;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     p0_DmPulldown:1;
unsigned int     p0_DpPulldown:1;
unsigned int     p0_IDPULLUP:1;
unsigned int     reserved_1:5;
unsigned int     p0_DmPulldown_sel:1;
unsigned int     p0_DpPulldown_sel:1;
unsigned int     p0_IDPULLUP_sel:1;
}USB2_PHY;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     done_st:1;
unsigned int     reserved_1:15;
unsigned int     go_ct:1;
}RAM_CTR;

typedef struct 
{
unsigned int     sram_addr:32;
}RAM_ADDR;

typedef struct 
{
unsigned int     ram_wdata:32;
}RAM_WDATA;

typedef struct 
{
unsigned int     ram_rdata:32;
}RAM_RDATA;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     p0_count_num:19;
}PHY0_ST;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     phy3_hperiod:3;
unsigned int     phy3_lperiod:3;
unsigned int     phy3_last:2;
unsigned int     host_ovr_current_value:1;
unsigned int     host_ovr_current_sel:1;
}USB3_OVR_CT;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     rstn_usb2_phy1:1;
unsigned int     rstn_usb2_phy0:1;
unsigned int     rstn_usb2:1;
}SOFT_RESET;

typedef struct 
{
unsigned int     usb_mac_ctrl:32;
}GBL_USB_CT;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     dbus_robin_enable:1;
unsigned int     cmd_full_number:2;
unsigned int     dbus_arb_priority:1;
}GBL_USB_ARB;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb2_bist_test_mode:1;
unsigned int     write_data:1;
}USB_BIST_MODE;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb2_bist_en:1;
unsigned int     write_data:1;
}USB_BIST_EN;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     usb2_2_bist_fail0:1;
unsigned int     usb2_2_bist_done:1;
unsigned int     usb2_bist_fail0:1;
unsigned int     usb2_bist_done:1;
}USB_BIST_ST;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb2_2_drf_start_pause:1;
unsigned int     usb2_drf_start_pause:1;
}USB_DRF_START;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     usb2_2_drf_test_resume:1;
unsigned int     usb2_drf_test_resume:1;
unsigned int     write_data:1;
}USB_DRF_RESUME;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb2_drf_bist_en:1;
unsigned int     write_data:1;
}USB_DRF_EN;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     usb2_2_drf_bist_fail0:1;
unsigned int     usb2_2_drf_bist_done:1;
unsigned int     usb2_drf_bist_fail0:1;
unsigned int     usb2_drf_bist_done:1;
}USB_DRF_ST;

#endif

#define WRAP_CTR                                                                     0x18013200
#define WRAP_CTR_reg_addr                                                            "0xB8013200"
#define WRAP_CTR_reg                                                                 0xB8013200
#define set_WRAP_CTR_reg(data)   (*((volatile unsigned int*) WRAP_CTR_reg)=data)
#define get_WRAP_CTR_reg   (*((volatile unsigned int*) WRAP_CTR_reg))
#define WRAP_CTR_inst_adr                                                            "0x0080"
#define WRAP_CTR_inst                                                                0x0080
#define WRAP_CTR_sram_debug_sel_shift                                                (3)
#define WRAP_CTR_sram_debug_sel_mask                                                 (0x00000008)
#define WRAP_CTR_sram_debug_sel(data)                                                (0x00000008&((data)<<3))
#define WRAP_CTR_sram_debug_sel_src(data)                                            ((0x00000008&(data))>>3)
#define WRAP_CTR_get_sram_debug_sel(data)                                            ((0x00000008&(data))>>3)
#define WRAP_CTR_sram_debug_mode_shift                                               (2)
#define WRAP_CTR_sram_debug_mode_mask                                                (0x00000004)
#define WRAP_CTR_sram_debug_mode(data)                                               (0x00000004&((data)<<2))
#define WRAP_CTR_sram_debug_mode_src(data)                                           ((0x00000004&(data))>>2)
#define WRAP_CTR_get_sram_debug_mode(data)                                           ((0x00000004&(data))>>2)
#define WRAP_CTR_dbus_multi_req_disable_shift                                        (1)
#define WRAP_CTR_dbus_multi_req_disable_mask                                         (0x00000002)
#define WRAP_CTR_dbus_multi_req_disable(data)                                        (0x00000002&((data)<<1))
#define WRAP_CTR_dbus_multi_req_disable_src(data)                                    ((0x00000002&(data))>>1)
#define WRAP_CTR_get_dbus_multi_req_disable(data)                                    ((0x00000002&(data))>>1)
#define WRAP_CTR_dev_mode_shift                                                      (0)
#define WRAP_CTR_dev_mode_mask                                                       (0x00000001)
#define WRAP_CTR_dev_mode(data)                                                      (0x00000001&((data)<<0))
#define WRAP_CTR_dev_mode_src(data)                                                  ((0x00000001&(data))>>0)
#define WRAP_CTR_get_dev_mode(data)                                                  ((0x00000001&(data))>>0)


#define GNR_INT                                                                      0x18013204
#define GNR_INT_reg_addr                                                             "0xB8013204"
#define GNR_INT_reg                                                                  0xB8013204
#define set_GNR_INT_reg(data)   (*((volatile unsigned int*) GNR_INT_reg)=data)
#define get_GNR_INT_reg   (*((volatile unsigned int*) GNR_INT_reg))
#define GNR_INT_inst_adr                                                             "0x0081"
#define GNR_INT_inst                                                                 0x0081
#define GNR_INT_device_int_shift                                                     (1)
#define GNR_INT_device_int_mask                                                      (0x00000002)
#define GNR_INT_device_int(data)                                                     (0x00000002&((data)<<1))
#define GNR_INT_device_int_src(data)                                                 ((0x00000002&(data))>>1)
#define GNR_INT_get_device_int(data)                                                 ((0x00000002&(data))>>1)
#define GNR_INT_host_int_shift                                                       (0)
#define GNR_INT_host_int_mask                                                        (0x00000001)
#define GNR_INT_host_int(data)                                                       (0x00000001&((data)<<0))
#define GNR_INT_host_int_src(data)                                                   ((0x00000001&(data))>>0)
#define GNR_INT_get_host_int(data)                                                   ((0x00000001&(data))>>0)


#define USB2_PHY_UTMI                                                                0x18013208
#define USB2_PHY_UTMI_reg_addr                                                       "0xB8013208"
#define USB2_PHY_UTMI_reg                                                            0xB8013208
#define set_USB2_PHY_UTMI_reg(data)   (*((volatile unsigned int*) USB2_PHY_UTMI_reg)=data)
#define get_USB2_PHY_UTMI_reg   (*((volatile unsigned int*) USB2_PHY_UTMI_reg))
#define USB2_PHY_UTMI_inst_adr                                                       "0x0082"
#define USB2_PHY_UTMI_inst                                                           0x0082
#define USB2_PHY_UTMI_reset_utmi_p0_shift                                            (0)
#define USB2_PHY_UTMI_reset_utmi_p0_mask                                             (0x00000001)
#define USB2_PHY_UTMI_reset_utmi_p0(data)                                            (0x00000001&((data)<<0))
#define USB2_PHY_UTMI_reset_utmi_p0_src(data)                                        ((0x00000001&(data))>>0)
#define USB2_PHY_UTMI_get_reset_utmi_p0(data)                                        ((0x00000001&(data))>>0)


#define USB3_PHY_PIPE                                                                0x1801320c
#define USB3_PHY_PIPE_reg_addr                                                       "0xB801320C"
#define USB3_PHY_PIPE_reg                                                            0xB801320C
#define set_USB3_PHY_PIPE_reg(data)   (*((volatile unsigned int*) USB3_PHY_PIPE_reg)=data)
#define get_USB3_PHY_PIPE_reg   (*((volatile unsigned int*) USB3_PHY_PIPE_reg))
#define USB3_PHY_PIPE_inst_adr                                                       "0x0083"
#define USB3_PHY_PIPE_inst                                                           0x0083
#define USB3_PHY_PIPE_reset_pipe3_p0_shift                                           (0)
#define USB3_PHY_PIPE_reset_pipe3_p0_mask                                            (0x00000001)
#define USB3_PHY_PIPE_reset_pipe3_p0(data)                                           (0x00000001&((data)<<0))
#define USB3_PHY_PIPE_reset_pipe3_p0_src(data)                                       ((0x00000001&(data))>>0)
#define USB3_PHY_PIPE_get_reset_pipe3_p0(data)                                       ((0x00000001&(data))>>0)


#define MDIO_CTR                                                                     0x18013210
#define MDIO_CTR_reg_addr                                                            "0xB8013210"
#define MDIO_CTR_reg                                                                 0xB8013210
#define set_MDIO_CTR_reg(data)   (*((volatile unsigned int*) MDIO_CTR_reg)=data)
#define get_MDIO_CTR_reg   (*((volatile unsigned int*) MDIO_CTR_reg))
#define MDIO_CTR_inst_adr                                                            "0x0084"
#define MDIO_CTR_inst                                                                0x0084
#define MDIO_CTR_data_shift                                                          (16)
#define MDIO_CTR_data_mask                                                           (0xFFFF0000)
#define MDIO_CTR_data(data)                                                          (0xFFFF0000&((data)<<16))
#define MDIO_CTR_data_src(data)                                                      ((0xFFFF0000&(data))>>16)
#define MDIO_CTR_get_data(data)                                                      ((0xFFFF0000&(data))>>16)
#define MDIO_CTR_phy_addr_shift                                                      (13)
#define MDIO_CTR_phy_addr_mask                                                       (0x0000E000)
#define MDIO_CTR_phy_addr(data)                                                      (0x0000E000&((data)<<13))
#define MDIO_CTR_phy_addr_src(data)                                                  ((0x0000E000&(data))>>13)
#define MDIO_CTR_get_phy_addr(data)                                                  ((0x0000E000&(data))>>13)
#define MDIO_CTR_phy_reg_addr_shift                                                  (8)
#define MDIO_CTR_phy_reg_addr_mask                                                   (0x00001F00)
#define MDIO_CTR_phy_reg_addr(data)                                                  (0x00001F00&((data)<<8))
#define MDIO_CTR_phy_reg_addr_src(data)                                              ((0x00001F00&(data))>>8)
#define MDIO_CTR_get_phy_reg_addr(data)                                              ((0x00001F00&(data))>>8)
#define MDIO_CTR_mdio_busy_shift                                                     (7)
#define MDIO_CTR_mdio_busy_mask                                                      (0x00000080)
#define MDIO_CTR_mdio_busy(data)                                                     (0x00000080&((data)<<7))
#define MDIO_CTR_mdio_busy_src(data)                                                 ((0x00000080&(data))>>7)
#define MDIO_CTR_get_mdio_busy(data)                                                 ((0x00000080&(data))>>7)
#define MDIO_CTR_mdio_st_shift                                                       (5)
#define MDIO_CTR_mdio_st_mask                                                        (0x00000060)
#define MDIO_CTR_mdio_st(data)                                                       (0x00000060&((data)<<5))
#define MDIO_CTR_mdio_st_src(data)                                                   ((0x00000060&(data))>>5)
#define MDIO_CTR_get_mdio_st(data)                                                   ((0x00000060&(data))>>5)
#define MDIO_CTR_mdio_rdy_shift                                                      (4)
#define MDIO_CTR_mdio_rdy_mask                                                       (0x00000010)
#define MDIO_CTR_mdio_rdy(data)                                                      (0x00000010&((data)<<4))
#define MDIO_CTR_mdio_rdy_src(data)                                                  ((0x00000010&(data))>>4)
#define MDIO_CTR_get_mdio_rdy(data)                                                  ((0x00000010&(data))>>4)
#define MDIO_CTR_mclk_rate_shift                                                     (2)
#define MDIO_CTR_mclk_rate_mask                                                      (0x0000000C)
#define MDIO_CTR_mclk_rate(data)                                                     (0x0000000C&((data)<<2))
#define MDIO_CTR_mclk_rate_src(data)                                                 ((0x0000000C&(data))>>2)
#define MDIO_CTR_get_mclk_rate(data)                                                 ((0x0000000C&(data))>>2)
#define MDIO_CTR_mdio_srst_shift                                                     (1)
#define MDIO_CTR_mdio_srst_mask                                                      (0x00000002)
#define MDIO_CTR_mdio_srst(data)                                                     (0x00000002&((data)<<1))
#define MDIO_CTR_mdio_srst_src(data)                                                 ((0x00000002&(data))>>1)
#define MDIO_CTR_get_mdio_srst(data)                                                 ((0x00000002&(data))>>1)
#define MDIO_CTR_mdio_rdwr_shift                                                     (0)
#define MDIO_CTR_mdio_rdwr_mask                                                      (0x00000001)
#define MDIO_CTR_mdio_rdwr(data)                                                     (0x00000001&((data)<<0))
#define MDIO_CTR_mdio_rdwr_src(data)                                                 ((0x00000001&(data))>>0)
#define MDIO_CTR_get_mdio_rdwr(data)                                                 ((0x00000001&(data))>>0)


#define VSTATUS0_OUT                                                                 0x18013214
#define VSTATUS0_OUT_reg_addr                                                        "0xB8013214"
#define VSTATUS0_OUT_reg                                                             0xB8013214
#define set_VSTATUS0_OUT_reg(data)   (*((volatile unsigned int*) VSTATUS0_OUT_reg)=data)
#define get_VSTATUS0_OUT_reg   (*((volatile unsigned int*) VSTATUS0_OUT_reg))
#define VSTATUS0_OUT_inst_adr                                                        "0x0085"
#define VSTATUS0_OUT_inst                                                            0x0085
#define VSTATUS0_OUT_p0_vstatus_out_shift                                            (0)
#define VSTATUS0_OUT_p0_vstatus_out_mask                                             (0x000000FF)
#define VSTATUS0_OUT_p0_vstatus_out(data)                                            (0x000000FF&((data)<<0))
#define VSTATUS0_OUT_p0_vstatus_out_src(data)                                        ((0x000000FF&(data))>>0)
#define VSTATUS0_OUT_get_p0_vstatus_out(data)                                        ((0x000000FF&(data))>>0)


#define SLP_BACK0_EN                                                                 0x18013218
#define SLP_BACK0_EN_reg_addr                                                        "0xB8013218"
#define SLP_BACK0_EN_reg                                                             0xB8013218
#define set_SLP_BACK0_EN_reg(data)   (*((volatile unsigned int*) SLP_BACK0_EN_reg)=data)
#define get_SLP_BACK0_EN_reg   (*((volatile unsigned int*) SLP_BACK0_EN_reg))
#define SLP_BACK0_EN_inst_adr                                                        "0x0086"
#define SLP_BACK0_EN_inst                                                            0x0086
#define SLP_BACK0_EN_simulation_mode_p0_shift                                        (3)
#define SLP_BACK0_EN_simulation_mode_p0_mask                                         (0x00000008)
#define SLP_BACK0_EN_simulation_mode_p0(data)                                        (0x00000008&((data)<<3))
#define SLP_BACK0_EN_simulation_mode_p0_src(data)                                    ((0x00000008&(data))>>3)
#define SLP_BACK0_EN_get_simulation_mode_p0(data)                                    ((0x00000008&(data))>>3)
#define SLP_BACK0_EN_force_hs_mode_p0_shift                                          (2)
#define SLP_BACK0_EN_force_hs_mode_p0_mask                                           (0x00000004)
#define SLP_BACK0_EN_force_hs_mode_p0(data)                                          (0x00000004&((data)<<2))
#define SLP_BACK0_EN_force_hs_mode_p0_src(data)                                      ((0x00000004&(data))>>2)
#define SLP_BACK0_EN_get_force_hs_mode_p0(data)                                      ((0x00000004&(data))>>2)
#define SLP_BACK0_EN_test_rst_p0_shift                                               (1)
#define SLP_BACK0_EN_test_rst_p0_mask                                                (0x00000002)
#define SLP_BACK0_EN_test_rst_p0(data)                                               (0x00000002&((data)<<1))
#define SLP_BACK0_EN_test_rst_p0_src(data)                                           ((0x00000002&(data))>>1)
#define SLP_BACK0_EN_get_test_rst_p0(data)                                           ((0x00000002&(data))>>1)
#define SLP_BACK0_EN_test_en_p0_shift                                                (0)
#define SLP_BACK0_EN_test_en_p0_mask                                                 (0x00000001)
#define SLP_BACK0_EN_test_en_p0(data)                                                (0x00000001&((data)<<0))
#define SLP_BACK0_EN_test_en_p0_src(data)                                            ((0x00000001&(data))>>0)
#define SLP_BACK0_EN_get_test_en_p0(data)                                            ((0x00000001&(data))>>0)


#define SLP_BACK0_CTR                                                                0x1801321c
#define SLP_BACK0_CTR_reg_addr                                                       "0xB801321C"
#define SLP_BACK0_CTR_reg                                                            0xB801321C
#define set_SLP_BACK0_CTR_reg(data)   (*((volatile unsigned int*) SLP_BACK0_CTR_reg)=data)
#define get_SLP_BACK0_CTR_reg   (*((volatile unsigned int*) SLP_BACK0_CTR_reg))
#define SLP_BACK0_CTR_inst_adr                                                       "0x0087"
#define SLP_BACK0_CTR_inst                                                           0x0087
#define SLP_BACK0_CTR_test_speed_p0_shift                                            (10)
#define SLP_BACK0_CTR_test_speed_p0_mask                                             (0x00000C00)
#define SLP_BACK0_CTR_test_speed_p0(data)                                            (0x00000C00&((data)<<10))
#define SLP_BACK0_CTR_test_speed_p0_src(data)                                        ((0x00000C00&(data))>>10)
#define SLP_BACK0_CTR_get_test_speed_p0(data)                                        ((0x00000C00&(data))>>10)
#define SLP_BACK0_CTR_test_seed_p0_shift                                             (2)
#define SLP_BACK0_CTR_test_seed_p0_mask                                              (0x000003FC)
#define SLP_BACK0_CTR_test_seed_p0(data)                                             (0x000003FC&((data)<<2))
#define SLP_BACK0_CTR_test_seed_p0_src(data)                                         ((0x000003FC&(data))>>2)
#define SLP_BACK0_CTR_get_test_seed_p0(data)                                         ((0x000003FC&(data))>>2)
#define SLP_BACK0_CTR_test_psl_p0_shift                                              (0)
#define SLP_BACK0_CTR_test_psl_p0_mask                                               (0x00000003)
#define SLP_BACK0_CTR_test_psl_p0(data)                                              (0x00000003&((data)<<0))
#define SLP_BACK0_CTR_test_psl_p0_src(data)                                          ((0x00000003&(data))>>0)
#define SLP_BACK0_CTR_get_test_psl_p0(data)                                          ((0x00000003&(data))>>0)


#define SLP_BACK0_ST                                                                 0x18013220
#define SLP_BACK0_ST_reg_addr                                                        "0xB8013220"
#define SLP_BACK0_ST_reg                                                             0xB8013220
#define set_SLP_BACK0_ST_reg(data)   (*((volatile unsigned int*) SLP_BACK0_ST_reg)=data)
#define get_SLP_BACK0_ST_reg   (*((volatile unsigned int*) SLP_BACK0_ST_reg))
#define SLP_BACK0_ST_inst_adr                                                        "0x0088"
#define SLP_BACK0_ST_inst                                                            0x0088
#define SLP_BACK0_ST_test_fail_p0_shift                                              (1)
#define SLP_BACK0_ST_test_fail_p0_mask                                               (0x00000002)
#define SLP_BACK0_ST_test_fail_p0(data)                                              (0x00000002&((data)<<1))
#define SLP_BACK0_ST_test_fail_p0_src(data)                                          ((0x00000002&(data))>>1)
#define SLP_BACK0_ST_get_test_fail_p0(data)                                          ((0x00000002&(data))>>1)
#define SLP_BACK0_ST_test_done_p0_shift                                              (0)
#define SLP_BACK0_ST_test_done_p0_mask                                               (0x00000001)
#define SLP_BACK0_ST_test_done_p0(data)                                              (0x00000001&((data)<<0))
#define SLP_BACK0_ST_test_done_p0_src(data)                                          ((0x00000001&(data))>>0)
#define SLP_BACK0_ST_get_test_done_p0(data)                                          ((0x00000001&(data))>>0)


#define PHY2_SLB_EN                                                                  0x18013224
#define PHY2_SLB_EN_reg_addr                                                         "0xB8013224"
#define PHY2_SLB_EN_reg                                                              0xB8013224
#define set_PHY2_SLB_EN_reg(data)   (*((volatile unsigned int*) PHY2_SLB_EN_reg)=data)
#define get_PHY2_SLB_EN_reg   (*((volatile unsigned int*) PHY2_SLB_EN_reg))
#define PHY2_SLB_EN_inst_adr                                                         "0x0089"
#define PHY2_SLB_EN_inst                                                             0x0089
#define PHY2_SLB_EN_p0_usb2phy_slb_hs_shift                                          (1)
#define PHY2_SLB_EN_p0_usb2phy_slb_hs_mask                                           (0x00000002)
#define PHY2_SLB_EN_p0_usb2phy_slb_hs(data)                                          (0x00000002&((data)<<1))
#define PHY2_SLB_EN_p0_usb2phy_slb_hs_src(data)                                      ((0x00000002&(data))>>1)
#define PHY2_SLB_EN_get_p0_usb2phy_slb_hs(data)                                      ((0x00000002&(data))>>1)
#define PHY2_SLB_EN_p0_usb2phy_force_slb_shift                                       (0)
#define PHY2_SLB_EN_p0_usb2phy_force_slb_mask                                        (0x00000001)
#define PHY2_SLB_EN_p0_usb2phy_force_slb(data)                                       (0x00000001&((data)<<0))
#define PHY2_SLB_EN_p0_usb2phy_force_slb_src(data)                                   ((0x00000001&(data))>>0)
#define PHY2_SLB_EN_get_p0_usb2phy_force_slb(data)                                   ((0x00000001&(data))>>0)


#define PHY2_SLB_ST                                                                  0x18013228
#define PHY2_SLB_ST_reg_addr                                                         "0xB8013228"
#define PHY2_SLB_ST_reg                                                              0xB8013228
#define set_PHY2_SLB_ST_reg(data)   (*((volatile unsigned int*) PHY2_SLB_ST_reg)=data)
#define get_PHY2_SLB_ST_reg   (*((volatile unsigned int*) PHY2_SLB_ST_reg))
#define PHY2_SLB_ST_inst_adr                                                         "0x008A"
#define PHY2_SLB_ST_inst                                                             0x008A
#define PHY2_SLB_ST_p0_usb2phy_slb_fail_shift                                        (1)
#define PHY2_SLB_ST_p0_usb2phy_slb_fail_mask                                         (0x00000002)
#define PHY2_SLB_ST_p0_usb2phy_slb_fail(data)                                        (0x00000002&((data)<<1))
#define PHY2_SLB_ST_p0_usb2phy_slb_fail_src(data)                                    ((0x00000002&(data))>>1)
#define PHY2_SLB_ST_get_p0_usb2phy_slb_fail(data)                                    ((0x00000002&(data))>>1)
#define PHY2_SLB_ST_p0_usb2phy_slb_done_shift                                        (0)
#define PHY2_SLB_ST_p0_usb2phy_slb_done_mask                                         (0x00000001)
#define PHY2_SLB_ST_p0_usb2phy_slb_done(data)                                        (0x00000001&((data)<<0))
#define PHY2_SLB_ST_p0_usb2phy_slb_done_src(data)                                    ((0x00000001&(data))>>0)
#define PHY2_SLB_ST_get_p0_usb2phy_slb_done(data)                                    ((0x00000001&(data))>>0)


#define USB2_SPD_CTR                                                                 0x1801322c
#define USB2_SPD_CTR_reg_addr                                                        "0xB801322C"
#define USB2_SPD_CTR_reg                                                             0xB801322C
#define set_USB2_SPD_CTR_reg(data)   (*((volatile unsigned int*) USB2_SPD_CTR_reg)=data)
#define get_USB2_SPD_CTR_reg   (*((volatile unsigned int*) USB2_SPD_CTR_reg))
#define USB2_SPD_CTR_inst_adr                                                        "0x008B"
#define USB2_SPD_CTR_inst                                                            0x008B
#define USB2_SPD_CTR_p0_suspend_r_shift                                              (0)
#define USB2_SPD_CTR_p0_suspend_r_mask                                               (0x00000001)
#define USB2_SPD_CTR_p0_suspend_r(data)                                              (0x00000001&((data)<<0))
#define USB2_SPD_CTR_p0_suspend_r_src(data)                                          ((0x00000001&(data))>>0)
#define USB2_SPD_CTR_get_p0_suspend_r(data)                                          ((0x00000001&(data))>>0)


#define PHY3_SLB_EN                                                                  0x18013230
#define PHY3_SLB_EN_reg_addr                                                         "0xB8013230"
#define PHY3_SLB_EN_reg                                                              0xB8013230
#define set_PHY3_SLB_EN_reg(data)   (*((volatile unsigned int*) PHY3_SLB_EN_reg)=data)
#define get_PHY3_SLB_EN_reg   (*((volatile unsigned int*) PHY3_SLB_EN_reg))
#define PHY3_SLB_EN_inst_adr                                                         "0x008C"
#define PHY3_SLB_EN_inst                                                             0x008C
#define PHY3_SLB_EN_p0_pipe_bist_sel_shift                                           (1)
#define PHY3_SLB_EN_p0_pipe_bist_sel_mask                                            (0x00000006)
#define PHY3_SLB_EN_p0_pipe_bist_sel(data)                                           (0x00000006&((data)<<1))
#define PHY3_SLB_EN_p0_pipe_bist_sel_src(data)                                       ((0x00000006&(data))>>1)
#define PHY3_SLB_EN_get_p0_pipe_bist_sel(data)                                       ((0x00000006&(data))>>1)
#define PHY3_SLB_EN_p0_pipe_bist_en_shift                                            (0)
#define PHY3_SLB_EN_p0_pipe_bist_en_mask                                             (0x00000001)
#define PHY3_SLB_EN_p0_pipe_bist_en(data)                                            (0x00000001&((data)<<0))
#define PHY3_SLB_EN_p0_pipe_bist_en_src(data)                                        ((0x00000001&(data))>>0)
#define PHY3_SLB_EN_get_p0_pipe_bist_en(data)                                        ((0x00000001&(data))>>0)


#define PHY3_SLB_CT                                                                  0x18013234
#define PHY3_SLB_CT_reg_addr                                                         "0xB8013234"
#define PHY3_SLB_CT_reg                                                              0xB8013234
#define set_PHY3_SLB_CT_reg(data)   (*((volatile unsigned int*) PHY3_SLB_CT_reg)=data)
#define get_PHY3_SLB_CT_reg   (*((volatile unsigned int*) PHY3_SLB_CT_reg))
#define PHY3_SLB_CT_inst_adr                                                         "0x008D"
#define PHY3_SLB_CT_inst                                                             0x008D
#define PHY3_SLB_CT_p0_usb3phy_slb_go_shift                                          (0)
#define PHY3_SLB_CT_p0_usb3phy_slb_go_mask                                           (0x00000001)
#define PHY3_SLB_CT_p0_usb3phy_slb_go(data)                                          (0x00000001&((data)<<0))
#define PHY3_SLB_CT_p0_usb3phy_slb_go_src(data)                                      ((0x00000001&(data))>>0)
#define PHY3_SLB_CT_get_p0_usb3phy_slb_go(data)                                      ((0x00000001&(data))>>0)


#define PHY3_SLB_ST                                                                  0x18013238
#define PHY3_SLB_ST_reg_addr                                                         "0xB8013238"
#define PHY3_SLB_ST_reg                                                              0xB8013238
#define set_PHY3_SLB_ST_reg(data)   (*((volatile unsigned int*) PHY3_SLB_ST_reg)=data)
#define get_PHY3_SLB_ST_reg   (*((volatile unsigned int*) PHY3_SLB_ST_reg))
#define PHY3_SLB_ST_inst_adr                                                         "0x008E"
#define PHY3_SLB_ST_inst                                                             0x008E
#define PHY3_SLB_ST_p0_usb3phy_slb_fail_shift                                        (1)
#define PHY3_SLB_ST_p0_usb3phy_slb_fail_mask                                         (0x00000002)
#define PHY3_SLB_ST_p0_usb3phy_slb_fail(data)                                        (0x00000002&((data)<<1))
#define PHY3_SLB_ST_p0_usb3phy_slb_fail_src(data)                                    ((0x00000002&(data))>>1)
#define PHY3_SLB_ST_get_p0_usb3phy_slb_fail(data)                                    ((0x00000002&(data))>>1)
#define PHY3_SLB_ST_p0_usb3phy_slb_done_shift                                        (0)
#define PHY3_SLB_ST_p0_usb3phy_slb_done_mask                                         (0x00000001)
#define PHY3_SLB_ST_p0_usb3phy_slb_done(data)                                        (0x00000001&((data)<<0))
#define PHY3_SLB_ST_p0_usb3phy_slb_done_src(data)                                    ((0x00000001&(data))>>0)
#define PHY3_SLB_ST_get_p0_usb3phy_slb_done(data)                                    ((0x00000001&(data))>>0)


#define USB_DBG                                                                      0x18013240
#define USB_DBG_reg_addr                                                             "0xB8013240"
#define USB_DBG_reg                                                                  0xB8013240
#define set_USB_DBG_reg(data)   (*((volatile unsigned int*) USB_DBG_reg)=data)
#define get_USB_DBG_reg   (*((volatile unsigned int*) USB_DBG_reg))
#define USB_DBG_inst_adr                                                             "0x0090"
#define USB_DBG_inst                                                                 0x0090
#define USB_DBG_dbg_sel1_shift                                                       (7)
#define USB_DBG_dbg_sel1_mask                                                        (0x00001F80)
#define USB_DBG_dbg_sel1(data)                                                       (0x00001F80&((data)<<7))
#define USB_DBG_dbg_sel1_src(data)                                                   ((0x00001F80&(data))>>7)
#define USB_DBG_get_dbg_sel1(data)                                                   ((0x00001F80&(data))>>7)
#define USB_DBG_dbg_sel0_shift                                                       (1)
#define USB_DBG_dbg_sel0_mask                                                        (0x0000007E)
#define USB_DBG_dbg_sel0(data)                                                       (0x0000007E&((data)<<1))
#define USB_DBG_dbg_sel0_src(data)                                                   ((0x0000007E&(data))>>1)
#define USB_DBG_get_dbg_sel0(data)                                                   ((0x0000007E&(data))>>1)
#define USB_DBG_dbg_en_shift                                                         (0)
#define USB_DBG_dbg_en_mask                                                          (0x00000001)
#define USB_DBG_dbg_en(data)                                                         (0x00000001&((data)<<0))
#define USB_DBG_dbg_en_src(data)                                                     ((0x00000001&(data))>>0)
#define USB_DBG_get_dbg_en(data)                                                     ((0x00000001&(data))>>0)


#define USB_SCTCH                                                                    0x18013244
#define USB_SCTCH_reg_addr                                                           "0xB8013244"
#define USB_SCTCH_reg                                                                0xB8013244
#define set_USB_SCTCH_reg(data)   (*((volatile unsigned int*) USB_SCTCH_reg)=data)
#define get_USB_SCTCH_reg   (*((volatile unsigned int*) USB_SCTCH_reg))
#define USB_SCTCH_inst_adr                                                           "0x0091"
#define USB_SCTCH_inst                                                               0x0091
#define USB_SCTCH_reg1_shift                                                         (16)
#define USB_SCTCH_reg1_mask                                                          (0xFFFF0000)
#define USB_SCTCH_reg1(data)                                                         (0xFFFF0000&((data)<<16))
#define USB_SCTCH_reg1_src(data)                                                     ((0xFFFF0000&(data))>>16)
#define USB_SCTCH_get_reg1(data)                                                     ((0xFFFF0000&(data))>>16)
#define USB_SCTCH_reg0_shift                                                         (0)
#define USB_SCTCH_reg0_mask                                                          (0x0000FFFF)
#define USB_SCTCH_reg0(data)                                                         (0x0000FFFF&((data)<<0))
#define USB_SCTCH_reg0_src(data)                                                     ((0x0000FFFF&(data))>>0)
#define USB_SCTCH_get_reg0(data)                                                     ((0x0000FFFF&(data))>>0)


#define USB_TMP_SP_0                                                                 0x18013248
#define USB_TMP_SP_1                                                                 0x1801324C
#define USB_TMP_SP_0_reg_addr                                                        "0xB8013248"
#define USB_TMP_SP_1_reg_addr                                                        "0xB801324C"
#define USB_TMP_SP_0_reg                                                             0xB8013248
#define USB_TMP_SP_1_reg                                                             0xB801324C
#define set_USB_TMP_SP_0_reg(data)   (*((volatile unsigned int*) USB_TMP_SP_0_reg)=data)
#define set_USB_TMP_SP_1_reg(data)   (*((volatile unsigned int*) USB_TMP_SP_1_reg)=data)
#define get_USB_TMP_SP_0_reg   (*((volatile unsigned int*) USB_TMP_SP_0_reg))
#define get_USB_TMP_SP_1_reg   (*((volatile unsigned int*) USB_TMP_SP_1_reg))
#define USB_TMP_SP_0_inst_adr                                                        "0x0092"
#define USB_TMP_SP_1_inst_adr                                                        "0x0093"
#define USB_TMP_SP_0_inst                                                            0x0092
#define USB_TMP_SP_1_inst                                                            0x0093
#define USB_TMP_SP_test_sp_reg_shift                                                 (0)
#define USB_TMP_SP_test_sp_reg_mask                                                  (0xFFFFFFFF)
#define USB_TMP_SP_test_sp_reg(data)                                                 (0xFFFFFFFF&((data)<<0))
#define USB_TMP_SP_test_sp_reg_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define USB_TMP_SP_get_test_sp_reg(data)                                             ((0xFFFFFFFF&(data))>>0)


#define USB_TMP_0                                                                    0x18013250
#define USB_TMP_1                                                                    0x18013254
#define USB_TMP_2                                                                    0x18013258
#define USB_TMP_3                                                                    0x1801325C
#define USB_TMP_0_reg_addr                                                           "0xB8013250"
#define USB_TMP_1_reg_addr                                                           "0xB8013254"
#define USB_TMP_2_reg_addr                                                           "0xB8013258"
#define USB_TMP_3_reg_addr                                                           "0xB801325C"
#define USB_TMP_0_reg                                                                0xB8013250
#define USB_TMP_1_reg                                                                0xB8013254
#define USB_TMP_2_reg                                                                0xB8013258
#define USB_TMP_3_reg                                                                0xB801325C
#define set_USB_TMP_0_reg(data)   (*((volatile unsigned int*) USB_TMP_0_reg)=data)
#define set_USB_TMP_1_reg(data)   (*((volatile unsigned int*) USB_TMP_1_reg)=data)
#define set_USB_TMP_2_reg(data)   (*((volatile unsigned int*) USB_TMP_2_reg)=data)
#define set_USB_TMP_3_reg(data)   (*((volatile unsigned int*) USB_TMP_3_reg)=data)
#define get_USB_TMP_0_reg   (*((volatile unsigned int*) USB_TMP_0_reg))
#define get_USB_TMP_1_reg   (*((volatile unsigned int*) USB_TMP_1_reg))
#define get_USB_TMP_2_reg   (*((volatile unsigned int*) USB_TMP_2_reg))
#define get_USB_TMP_3_reg   (*((volatile unsigned int*) USB_TMP_3_reg))
#define USB_TMP_0_inst_adr                                                           "0x0094"
#define USB_TMP_1_inst_adr                                                           "0x0095"
#define USB_TMP_2_inst_adr                                                           "0x0096"
#define USB_TMP_3_inst_adr                                                           "0x0097"
#define USB_TMP_0_inst                                                               0x0094
#define USB_TMP_1_inst                                                               0x0095
#define USB_TMP_2_inst                                                               0x0096
#define USB_TMP_3_inst                                                               0x0097
#define USB_TMP_test_reg_shift                                                       (0)
#define USB_TMP_test_reg_mask                                                        (0xFFFFFFFF)
#define USB_TMP_test_reg(data)                                                       (0xFFFFFFFF&((data)<<0))
#define USB_TMP_test_reg_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define USB_TMP_get_test_reg(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define HMAC_CTR0                                                                    0x18013260
#define HMAC_CTR0_reg_addr                                                           "0xB8013260"
#define HMAC_CTR0_reg                                                                0xB8013260
#define set_HMAC_CTR0_reg(data)   (*((volatile unsigned int*) HMAC_CTR0_reg)=data)
#define get_HMAC_CTR0_reg   (*((volatile unsigned int*) HMAC_CTR0_reg))
#define HMAC_CTR0_inst_adr                                                           "0x0098"
#define HMAC_CTR0_inst                                                               0x0098
#define HMAC_CTR0_host_utmiotg_vbusvalid_shift                                       (30)
#define HMAC_CTR0_host_utmiotg_vbusvalid_mask                                        (0x40000000)
#define HMAC_CTR0_host_utmiotg_vbusvalid(data)                                       (0x40000000&((data)<<30))
#define HMAC_CTR0_host_utmiotg_vbusvalid_src(data)                                   ((0x40000000&(data))>>30)
#define HMAC_CTR0_get_host_utmiotg_vbusvalid(data)                                   ((0x40000000&(data))>>30)
#define HMAC_CTR0_host_fladj_30mhz_shift                                             (24)
#define HMAC_CTR0_host_fladj_30mhz_mask                                              (0x3F000000)
#define HMAC_CTR0_host_fladj_30mhz(data)                                             (0x3F000000&((data)<<24))
#define HMAC_CTR0_host_fladj_30mhz_src(data)                                         ((0x3F000000&(data))>>24)
#define HMAC_CTR0_get_host_fladj_30mhz(data)                                         ((0x3F000000&(data))>>24)
#define HMAC_CTR0_host_ppc_present_shift                                             (23)
#define HMAC_CTR0_host_ppc_present_mask                                              (0x00800000)
#define HMAC_CTR0_host_ppc_present(data)                                             (0x00800000&((data)<<23))
#define HMAC_CTR0_host_ppc_present_src(data)                                         ((0x00800000&(data))>>23)
#define HMAC_CTR0_get_host_ppc_present(data)                                         ((0x00800000&(data))>>23)
#define HMAC_CTR0_host_msi_enable_shift                                              (22)
#define HMAC_CTR0_host_msi_enable_mask                                               (0x00400000)
#define HMAC_CTR0_host_msi_enable(data)                                              (0x00400000&((data)<<22))
#define HMAC_CTR0_host_msi_enable_src(data)                                          ((0x00400000&(data))>>22)
#define HMAC_CTR0_get_host_msi_enable(data)                                          ((0x00400000&(data))>>22)
#define HMAC_CTR0_host_pm_pw_state_req_shift                                         (20)
#define HMAC_CTR0_host_pm_pw_state_req_mask                                          (0x00300000)
#define HMAC_CTR0_host_pm_pw_state_req(data)                                         (0x00300000&((data)<<20))
#define HMAC_CTR0_host_pm_pw_state_req_src(data)                                     ((0x00300000&(data))>>20)
#define HMAC_CTR0_get_host_pm_pw_state_req(data)                                     ((0x00300000&(data))>>20)
#define HMAC_CTR0_hub_port_over_current_shift                                        (16)
#define HMAC_CTR0_hub_port_over_current_mask                                         (0x000F0000)
#define HMAC_CTR0_hub_port_over_current(data)                                        (0x000F0000&((data)<<16))
#define HMAC_CTR0_hub_port_over_current_src(data)                                    ((0x000F0000&(data))>>16)
#define HMAC_CTR0_get_hub_port_over_current(data)                                    ((0x000F0000&(data))>>16)
#define HMAC_CTR0_hub_port_perm_attach_shift                                         (12)
#define HMAC_CTR0_hub_port_perm_attach_mask                                          (0x00003000)
#define HMAC_CTR0_hub_port_perm_attach(data)                                         (0x00003000&((data)<<12))
#define HMAC_CTR0_hub_port_perm_attach_src(data)                                     ((0x00003000&(data))>>12)
#define HMAC_CTR0_get_hub_port_perm_attach(data)                                     ((0x00003000&(data))>>12)
#define HMAC_CTR0_host_u2_port_disable_shift                                         (9)
#define HMAC_CTR0_host_u2_port_disable_mask                                          (0x00000200)
#define HMAC_CTR0_host_u2_port_disable(data)                                         (0x00000200&((data)<<9))
#define HMAC_CTR0_host_u2_port_disable_src(data)                                     ((0x00000200&(data))>>9)
#define HMAC_CTR0_get_host_u2_port_disable(data)                                     ((0x00000200&(data))>>9)
#define HMAC_CTR0_host_u3_port_disable_shift                                         (8)
#define HMAC_CTR0_host_u3_port_disable_mask                                          (0x00000100)
#define HMAC_CTR0_host_u3_port_disable(data)                                         (0x00000100&((data)<<8))
#define HMAC_CTR0_host_u3_port_disable_src(data)                                     ((0x00000100&(data))>>8)
#define HMAC_CTR0_get_host_u3_port_disable(data)                                     ((0x00000100&(data))>>8)
#define HMAC_CTR0_host_num_u2_port_shift                                             (4)
#define HMAC_CTR0_host_num_u2_port_mask                                              (0x000000F0)
#define HMAC_CTR0_host_num_u2_port(data)                                             (0x000000F0&((data)<<4))
#define HMAC_CTR0_host_num_u2_port_src(data)                                         ((0x000000F0&(data))>>4)
#define HMAC_CTR0_get_host_num_u2_port(data)                                         ((0x000000F0&(data))>>4)
#define HMAC_CTR0_host_num_u3_port_shift                                             (0)
#define HMAC_CTR0_host_num_u3_port_mask                                              (0x0000000F)
#define HMAC_CTR0_host_num_u3_port(data)                                             (0x0000000F&((data)<<0))
#define HMAC_CTR0_host_num_u3_port_src(data)                                         ((0x0000000F&(data))>>0)
#define HMAC_CTR0_get_host_num_u3_port(data)                                         ((0x0000000F&(data))>>0)


#define MAC3_HST_ST                                                                  0x18013264
#define MAC3_HST_ST_reg_addr                                                         "0xB8013264"
#define MAC3_HST_ST_reg                                                              0xB8013264
#define set_MAC3_HST_ST_reg(data)   (*((volatile unsigned int*) MAC3_HST_ST_reg)=data)
#define get_MAC3_HST_ST_reg   (*((volatile unsigned int*) MAC3_HST_ST_reg))
#define MAC3_HST_ST_inst_adr                                                         "0x0099"
#define MAC3_HST_ST_inst                                                             0x0099
#define MAC3_HST_ST_host_current_power_state_shift                                   (2)
#define MAC3_HST_ST_host_current_power_state_mask                                    (0x0000000C)
#define MAC3_HST_ST_host_current_power_state(data)                                   (0x0000000C&((data)<<2))
#define MAC3_HST_ST_host_current_power_state_src(data)                               ((0x0000000C&(data))>>2)
#define MAC3_HST_ST_get_host_current_power_state(data)                               ((0x0000000C&(data))>>2)
#define MAC3_HST_ST_host_hub_vbus_ctrl_shift                                         (0)
#define MAC3_HST_ST_host_hub_vbus_ctrl_mask                                          (0x00000003)
#define MAC3_HST_ST_host_hub_vbus_ctrl(data)                                         (0x00000003&((data)<<0))
#define MAC3_HST_ST_host_hub_vbus_ctrl_src(data)                                     ((0x00000003&(data))>>0)
#define MAC3_HST_ST_get_host_hub_vbus_ctrl(data)                                     ((0x00000003&(data))>>0)


#define DMAC_CTR0                                                                    0x18013268
#define DMAC_CTR0_reg_addr                                                           "0xB8013268"
#define DMAC_CTR0_reg                                                                0xB8013268
#define set_DMAC_CTR0_reg(data)   (*((volatile unsigned int*) DMAC_CTR0_reg)=data)
#define get_DMAC_CTR0_reg   (*((volatile unsigned int*) DMAC_CTR0_reg))
#define DMAC_CTR0_inst_adr                                                           "0x009A"
#define DMAC_CTR0_inst                                                               0x009A
#define DMAC_CTR0_dev_vbus_value_shift                                               (25)
#define DMAC_CTR0_dev_vbus_value_mask                                                (0x02000000)
#define DMAC_CTR0_dev_vbus_value(data)                                               (0x02000000&((data)<<25))
#define DMAC_CTR0_dev_vbus_value_src(data)                                           ((0x02000000&(data))>>25)
#define DMAC_CTR0_get_dev_vbus_value(data)                                           ((0x02000000&(data))>>25)
#define DMAC_CTR0_dev_utmiotg_vbusvalid_shift                                        (24)
#define DMAC_CTR0_dev_utmiotg_vbusvalid_mask                                         (0x01000000)
#define DMAC_CTR0_dev_utmiotg_vbusvalid(data)                                        (0x01000000&((data)<<24))
#define DMAC_CTR0_dev_utmiotg_vbusvalid_src(data)                                    ((0x01000000&(data))>>24)
#define DMAC_CTR0_get_dev_utmiotg_vbusvalid(data)                                    ((0x01000000&(data))>>24)
#define DMAC_CTR0_dev_pm_pw_state_req_shift                                          (22)
#define DMAC_CTR0_dev_pm_pw_state_req_mask                                           (0x00C00000)
#define DMAC_CTR0_dev_pm_pw_state_req(data)                                          (0x00C00000&((data)<<22))
#define DMAC_CTR0_dev_pm_pw_state_req_src(data)                                      ((0x00C00000&(data))>>22)
#define DMAC_CTR0_get_dev_pm_pw_state_req(data)                                      ((0x00C00000&(data))>>22)
#define DMAC_CTR0_dev_fladj_30mhz_shift                                              (16)
#define DMAC_CTR0_dev_fladj_30mhz_mask                                               (0x003F0000)
#define DMAC_CTR0_dev_fladj_30mhz(data)                                              (0x003F0000&((data)<<16))
#define DMAC_CTR0_dev_fladj_30mhz_src(data)                                          ((0x003F0000&(data))>>16)
#define DMAC_CTR0_get_dev_fladj_30mhz(data)                                          ((0x003F0000&(data))>>16)
#define DMAC_CTR0_dev_usb_outep_pkt_buff_shift                                       (0)
#define DMAC_CTR0_dev_usb_outep_pkt_buff_mask                                        (0x0000FFFF)
#define DMAC_CTR0_dev_usb_outep_pkt_buff(data)                                       (0x0000FFFF&((data)<<0))
#define DMAC_CTR0_dev_usb_outep_pkt_buff_src(data)                                   ((0x0000FFFF&(data))>>0)
#define DMAC_CTR0_get_dev_usb_outep_pkt_buff(data)                                   ((0x0000FFFF&(data))>>0)


#define MAC3_DEV_ST                                                                  0x1801326c
#define MAC3_DEV_ST_reg_addr                                                         "0xB801326C"
#define MAC3_DEV_ST_reg                                                              0xB801326C
#define set_MAC3_DEV_ST_reg(data)   (*((volatile unsigned int*) MAC3_DEV_ST_reg)=data)
#define get_MAC3_DEV_ST_reg   (*((volatile unsigned int*) MAC3_DEV_ST_reg))
#define MAC3_DEV_ST_inst_adr                                                         "0x009B"
#define MAC3_DEV_ST_inst                                                             0x009B
#define MAC3_DEV_ST_dev_current_power_state_shift                                    (0)
#define MAC3_DEV_ST_dev_current_power_state_mask                                     (0x00000003)
#define MAC3_DEV_ST_dev_current_power_state(data)                                    (0x00000003&((data)<<0))
#define MAC3_DEV_ST_dev_current_power_state_src(data)                                ((0x00000003&(data))>>0)
#define MAC3_DEV_ST_get_dev_current_power_state(data)                                ((0x00000003&(data))>>0)


#define USB2_PHY                                                                     0x18013270
#define USB2_PHY_reg_addr                                                            "0xB8013270"
#define USB2_PHY_reg                                                                 0xB8013270
#define set_USB2_PHY_reg(data)   (*((volatile unsigned int*) USB2_PHY_reg)=data)
#define get_USB2_PHY_reg   (*((volatile unsigned int*) USB2_PHY_reg))
#define USB2_PHY_inst_adr                                                            "0x009C"
#define USB2_PHY_inst                                                                0x009C
#define USB2_PHY_p0_DmPulldown_shift                                                 (10)
#define USB2_PHY_p0_DmPulldown_mask                                                  (0x00000400)
#define USB2_PHY_p0_DmPulldown(data)                                                 (0x00000400&((data)<<10))
#define USB2_PHY_p0_DmPulldown_src(data)                                             ((0x00000400&(data))>>10)
#define USB2_PHY_get_p0_DmPulldown(data)                                             ((0x00000400&(data))>>10)
#define USB2_PHY_p0_DpPulldown_shift                                                 (9)
#define USB2_PHY_p0_DpPulldown_mask                                                  (0x00000200)
#define USB2_PHY_p0_DpPulldown(data)                                                 (0x00000200&((data)<<9))
#define USB2_PHY_p0_DpPulldown_src(data)                                             ((0x00000200&(data))>>9)
#define USB2_PHY_get_p0_DpPulldown(data)                                             ((0x00000200&(data))>>9)
#define USB2_PHY_p0_IDPULLUP_shift                                                   (8)
#define USB2_PHY_p0_IDPULLUP_mask                                                    (0x00000100)
#define USB2_PHY_p0_IDPULLUP(data)                                                   (0x00000100&((data)<<8))
#define USB2_PHY_p0_IDPULLUP_src(data)                                               ((0x00000100&(data))>>8)
#define USB2_PHY_get_p0_IDPULLUP(data)                                               ((0x00000100&(data))>>8)
#define USB2_PHY_p0_DmPulldown_sel_shift                                             (2)
#define USB2_PHY_p0_DmPulldown_sel_mask                                              (0x00000004)
#define USB2_PHY_p0_DmPulldown_sel(data)                                             (0x00000004&((data)<<2))
#define USB2_PHY_p0_DmPulldown_sel_src(data)                                         ((0x00000004&(data))>>2)
#define USB2_PHY_get_p0_DmPulldown_sel(data)                                         ((0x00000004&(data))>>2)
#define USB2_PHY_p0_DpPulldown_sel_shift                                             (1)
#define USB2_PHY_p0_DpPulldown_sel_mask                                              (0x00000002)
#define USB2_PHY_p0_DpPulldown_sel(data)                                             (0x00000002&((data)<<1))
#define USB2_PHY_p0_DpPulldown_sel_src(data)                                         ((0x00000002&(data))>>1)
#define USB2_PHY_get_p0_DpPulldown_sel(data)                                         ((0x00000002&(data))>>1)
#define USB2_PHY_p0_IDPULLUP_sel_shift                                               (0)
#define USB2_PHY_p0_IDPULLUP_sel_mask                                                (0x00000001)
#define USB2_PHY_p0_IDPULLUP_sel(data)                                               (0x00000001&((data)<<0))
#define USB2_PHY_p0_IDPULLUP_sel_src(data)                                           ((0x00000001&(data))>>0)
#define USB2_PHY_get_p0_IDPULLUP_sel(data)                                           ((0x00000001&(data))>>0)


#define RAM_CTR                                                                      0x18013274
#define RAM_CTR_reg_addr                                                             "0xB8013274"
#define RAM_CTR_reg                                                                  0xB8013274
#define set_RAM_CTR_reg(data)   (*((volatile unsigned int*) RAM_CTR_reg)=data)
#define get_RAM_CTR_reg   (*((volatile unsigned int*) RAM_CTR_reg))
#define RAM_CTR_inst_adr                                                             "0x009D"
#define RAM_CTR_inst                                                                 0x009D
#define RAM_CTR_done_st_shift                                                        (16)
#define RAM_CTR_done_st_mask                                                         (0x00010000)
#define RAM_CTR_done_st(data)                                                        (0x00010000&((data)<<16))
#define RAM_CTR_done_st_src(data)                                                    ((0x00010000&(data))>>16)
#define RAM_CTR_get_done_st(data)                                                    ((0x00010000&(data))>>16)
#define RAM_CTR_go_ct_shift                                                          (0)
#define RAM_CTR_go_ct_mask                                                           (0x00000001)
#define RAM_CTR_go_ct(data)                                                          (0x00000001&((data)<<0))
#define RAM_CTR_go_ct_src(data)                                                      ((0x00000001&(data))>>0)
#define RAM_CTR_get_go_ct(data)                                                      ((0x00000001&(data))>>0)


#define RAM_ADDR                                                                     0x18013278
#define RAM_ADDR_reg_addr                                                            "0xB8013278"
#define RAM_ADDR_reg                                                                 0xB8013278
#define set_RAM_ADDR_reg(data)   (*((volatile unsigned int*) RAM_ADDR_reg)=data)
#define get_RAM_ADDR_reg   (*((volatile unsigned int*) RAM_ADDR_reg))
#define RAM_ADDR_inst_adr                                                            "0x009E"
#define RAM_ADDR_inst                                                                0x009E
#define RAM_ADDR_sram_addr_shift                                                     (0)
#define RAM_ADDR_sram_addr_mask                                                      (0xFFFFFFFF)
#define RAM_ADDR_sram_addr(data)                                                     (0xFFFFFFFF&((data)<<0))
#define RAM_ADDR_sram_addr_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define RAM_ADDR_get_sram_addr(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define RAM_WDATA                                                                    0x1801327C
#define RAM_WDATA_reg_addr                                                           "0xB801327C"
#define RAM_WDATA_reg                                                                0xB801327C
#define set_RAM_WDATA_reg(data)   (*((volatile unsigned int*) RAM_WDATA_reg)=data)
#define get_RAM_WDATA_reg   (*((volatile unsigned int*) RAM_WDATA_reg))
#define RAM_WDATA_inst_adr                                                           "0x009F"
#define RAM_WDATA_inst                                                               0x009F
#define RAM_WDATA_ram_wdata_shift                                                    (0)
#define RAM_WDATA_ram_wdata_mask                                                     (0xFFFFFFFF)
#define RAM_WDATA_ram_wdata(data)                                                    (0xFFFFFFFF&((data)<<0))
#define RAM_WDATA_ram_wdata_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define RAM_WDATA_get_ram_wdata(data)                                                ((0xFFFFFFFF&(data))>>0)


#define RAM_RDATA                                                                    0x18013280
#define RAM_RDATA_reg_addr                                                           "0xB8013280"
#define RAM_RDATA_reg                                                                0xB8013280
#define set_RAM_RDATA_reg(data)   (*((volatile unsigned int*) RAM_RDATA_reg)=data)
#define get_RAM_RDATA_reg   (*((volatile unsigned int*) RAM_RDATA_reg))
#define RAM_RDATA_inst_adr                                                           "0x00A0"
#define RAM_RDATA_inst                                                               0x00A0
#define RAM_RDATA_ram_rdata_shift                                                    (0)
#define RAM_RDATA_ram_rdata_mask                                                     (0xFFFFFFFF)
#define RAM_RDATA_ram_rdata(data)                                                    (0xFFFFFFFF&((data)<<0))
#define RAM_RDATA_ram_rdata_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define RAM_RDATA_get_ram_rdata(data)                                                ((0xFFFFFFFF&(data))>>0)


#define PHY0_ST                                                                      0x18013284
#define PHY0_ST_reg_addr                                                             "0xB8013284"
#define PHY0_ST_reg                                                                  0xB8013284
#define set_PHY0_ST_reg(data)   (*((volatile unsigned int*) PHY0_ST_reg)=data)
#define get_PHY0_ST_reg   (*((volatile unsigned int*) PHY0_ST_reg))
#define PHY0_ST_inst_adr                                                             "0x00A1"
#define PHY0_ST_inst                                                                 0x00A1
#define PHY0_ST_p0_count_num_shift                                                   (0)
#define PHY0_ST_p0_count_num_mask                                                    (0x0007FFFF)
#define PHY0_ST_p0_count_num(data)                                                   (0x0007FFFF&((data)<<0))
#define PHY0_ST_p0_count_num_src(data)                                               ((0x0007FFFF&(data))>>0)
#define PHY0_ST_get_p0_count_num(data)                                               ((0x0007FFFF&(data))>>0)


#define USB3_OVR_CT                                                                  0x18013288
#define USB3_OVR_CT_reg_addr                                                         "0xB8013288"
#define USB3_OVR_CT_reg                                                              0xB8013288
#define set_USB3_OVR_CT_reg(data)   (*((volatile unsigned int*) USB3_OVR_CT_reg)=data)
#define get_USB3_OVR_CT_reg   (*((volatile unsigned int*) USB3_OVR_CT_reg))
#define USB3_OVR_CT_inst_adr                                                         "0x00A2"
#define USB3_OVR_CT_inst                                                             0x00A2
#define USB3_OVR_CT_phy3_hperiod_shift                                               (7)
#define USB3_OVR_CT_phy3_hperiod_mask                                                (0x00000380)
#define USB3_OVR_CT_phy3_hperiod(data)                                               (0x00000380&((data)<<7))
#define USB3_OVR_CT_phy3_hperiod_src(data)                                           ((0x00000380&(data))>>7)
#define USB3_OVR_CT_get_phy3_hperiod(data)                                           ((0x00000380&(data))>>7)
#define USB3_OVR_CT_phy3_lperiod_shift                                               (4)
#define USB3_OVR_CT_phy3_lperiod_mask                                                (0x00000070)
#define USB3_OVR_CT_phy3_lperiod(data)                                               (0x00000070&((data)<<4))
#define USB3_OVR_CT_phy3_lperiod_src(data)                                           ((0x00000070&(data))>>4)
#define USB3_OVR_CT_get_phy3_lperiod(data)                                           ((0x00000070&(data))>>4)
#define USB3_OVR_CT_phy3_last_shift                                                  (2)
#define USB3_OVR_CT_phy3_last_mask                                                   (0x0000000C)
#define USB3_OVR_CT_phy3_last(data)                                                  (0x0000000C&((data)<<2))
#define USB3_OVR_CT_phy3_last_src(data)                                              ((0x0000000C&(data))>>2)
#define USB3_OVR_CT_get_phy3_last(data)                                              ((0x0000000C&(data))>>2)
#define USB3_OVR_CT_host_ovr_current_value_shift                                     (1)
#define USB3_OVR_CT_host_ovr_current_value_mask                                      (0x00000002)
#define USB3_OVR_CT_host_ovr_current_value(data)                                     (0x00000002&((data)<<1))
#define USB3_OVR_CT_host_ovr_current_value_src(data)                                 ((0x00000002&(data))>>1)
#define USB3_OVR_CT_get_host_ovr_current_value(data)                                 ((0x00000002&(data))>>1)
#define USB3_OVR_CT_host_ovr_current_sel_shift                                       (0)
#define USB3_OVR_CT_host_ovr_current_sel_mask                                        (0x00000001)
#define USB3_OVR_CT_host_ovr_current_sel(data)                                       (0x00000001&((data)<<0))
#define USB3_OVR_CT_host_ovr_current_sel_src(data)                                   ((0x00000001&(data))>>0)
#define USB3_OVR_CT_get_host_ovr_current_sel(data)                                   ((0x00000001&(data))>>0)


#define SOFT_RESET                                                                   0x18013300
#define SOFT_RESET_reg_addr                                                          "0xB8013300"
#define SOFT_RESET_reg                                                               0xB8013300
#define set_SOFT_RESET_reg(data)   (*((volatile unsigned int*) SOFT_RESET_reg)=data)
#define get_SOFT_RESET_reg   (*((volatile unsigned int*) SOFT_RESET_reg))
#define SOFT_RESET_inst_adr                                                          "0x00C0"
#define SOFT_RESET_inst                                                              0x00C0
#define SOFT_RESET_rstn_usb2_phy1_shift                                              (2)
#define SOFT_RESET_rstn_usb2_phy1_mask                                               (0x00000004)
#define SOFT_RESET_rstn_usb2_phy1(data)                                              (0x00000004&((data)<<2))
#define SOFT_RESET_rstn_usb2_phy1_src(data)                                          ((0x00000004&(data))>>2)
#define SOFT_RESET_get_rstn_usb2_phy1(data)                                          ((0x00000004&(data))>>2)
#define SOFT_RESET_rstn_usb2_phy0_shift                                              (1)
#define SOFT_RESET_rstn_usb2_phy0_mask                                               (0x00000002)
#define SOFT_RESET_rstn_usb2_phy0(data)                                              (0x00000002&((data)<<1))
#define SOFT_RESET_rstn_usb2_phy0_src(data)                                          ((0x00000002&(data))>>1)
#define SOFT_RESET_get_rstn_usb2_phy0(data)                                          ((0x00000002&(data))>>1)
#define SOFT_RESET_rstn_usb2_shift                                                   (0)
#define SOFT_RESET_rstn_usb2_mask                                                    (0x00000001)
#define SOFT_RESET_rstn_usb2(data)                                                   (0x00000001&((data)<<0))
#define SOFT_RESET_rstn_usb2_src(data)                                               ((0x00000001&(data))>>0)
#define SOFT_RESET_get_rstn_usb2(data)                                               ((0x00000001&(data))>>0)


#define GBL_USB_CT                                                                   0x18013304
#define GBL_USB_CT_reg_addr                                                          "0xB8013304"
#define GBL_USB_CT_reg                                                               0xB8013304
#define set_GBL_USB_CT_reg(data)   (*((volatile unsigned int*) GBL_USB_CT_reg)=data)
#define get_GBL_USB_CT_reg   (*((volatile unsigned int*) GBL_USB_CT_reg))
#define GBL_USB_CT_inst_adr                                                          "0x00C1"
#define GBL_USB_CT_inst                                                              0x00C1
#define GBL_USB_CT_usb_mac_ctrl_shift                                                (0)
#define GBL_USB_CT_usb_mac_ctrl_mask                                                 (0xFFFFFFFF)
#define GBL_USB_CT_usb_mac_ctrl(data)                                                (0xFFFFFFFF&((data)<<0))
#define GBL_USB_CT_usb_mac_ctrl_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define GBL_USB_CT_get_usb_mac_ctrl(data)                                            ((0xFFFFFFFF&(data))>>0)


#define GBL_USB_ARB                                                                  0x18013308
#define GBL_USB_ARB_reg_addr                                                         "0xB8013308"
#define GBL_USB_ARB_reg                                                              0xB8013308
#define set_GBL_USB_ARB_reg(data)   (*((volatile unsigned int*) GBL_USB_ARB_reg)=data)
#define get_GBL_USB_ARB_reg   (*((volatile unsigned int*) GBL_USB_ARB_reg))
#define GBL_USB_ARB_inst_adr                                                         "0x00C2"
#define GBL_USB_ARB_inst                                                             0x00C2
#define GBL_USB_ARB_dbus_robin_enable_shift                                          (3)
#define GBL_USB_ARB_dbus_robin_enable_mask                                           (0x00000008)
#define GBL_USB_ARB_dbus_robin_enable(data)                                          (0x00000008&((data)<<3))
#define GBL_USB_ARB_dbus_robin_enable_src(data)                                      ((0x00000008&(data))>>3)
#define GBL_USB_ARB_get_dbus_robin_enable(data)                                      ((0x00000008&(data))>>3)
#define GBL_USB_ARB_cmd_full_number_shift                                            (1)
#define GBL_USB_ARB_cmd_full_number_mask                                             (0x00000006)
#define GBL_USB_ARB_cmd_full_number(data)                                            (0x00000006&((data)<<1))
#define GBL_USB_ARB_cmd_full_number_src(data)                                        ((0x00000006&(data))>>1)
#define GBL_USB_ARB_get_cmd_full_number(data)                                        ((0x00000006&(data))>>1)
#define GBL_USB_ARB_dbus_arb_priority_shift                                          (0)
#define GBL_USB_ARB_dbus_arb_priority_mask                                           (0x00000001)
#define GBL_USB_ARB_dbus_arb_priority(data)                                          (0x00000001&((data)<<0))
#define GBL_USB_ARB_dbus_arb_priority_src(data)                                      ((0x00000001&(data))>>0)
#define GBL_USB_ARB_get_dbus_arb_priority(data)                                      ((0x00000001&(data))>>0)


#define USB_BIST_MODE                                                                0x18013310
#define USB_BIST_MODE_reg_addr                                                       "0xB8013310"
#define USB_BIST_MODE_reg                                                            0xB8013310
#define set_USB_BIST_MODE_reg(data)   (*((volatile unsigned int*) USB_BIST_MODE_reg)=data)
#define get_USB_BIST_MODE_reg   (*((volatile unsigned int*) USB_BIST_MODE_reg))
#define USB_BIST_MODE_inst_adr                                                       "0x00C4"
#define USB_BIST_MODE_inst                                                           0x00C4
#define USB_BIST_MODE_usb2_bist_test_mode_shift                                      (1)
#define USB_BIST_MODE_usb2_bist_test_mode_mask                                       (0x00000002)
#define USB_BIST_MODE_usb2_bist_test_mode(data)                                      (0x00000002&((data)<<1))
#define USB_BIST_MODE_usb2_bist_test_mode_src(data)                                  ((0x00000002&(data))>>1)
#define USB_BIST_MODE_get_usb2_bist_test_mode(data)                                  ((0x00000002&(data))>>1)
#define USB_BIST_MODE_write_data_shift                                               (0)
#define USB_BIST_MODE_write_data_mask                                                (0x00000001)
#define USB_BIST_MODE_write_data(data)                                               (0x00000001&((data)<<0))
#define USB_BIST_MODE_write_data_src(data)                                           ((0x00000001&(data))>>0)
#define USB_BIST_MODE_get_write_data(data)                                           ((0x00000001&(data))>>0)


#define USB_BIST_EN                                                                  0x18013314
#define USB_BIST_EN_reg_addr                                                         "0xB8013314"
#define USB_BIST_EN_reg                                                              0xB8013314
#define set_USB_BIST_EN_reg(data)   (*((volatile unsigned int*) USB_BIST_EN_reg)=data)
#define get_USB_BIST_EN_reg   (*((volatile unsigned int*) USB_BIST_EN_reg))
#define USB_BIST_EN_inst_adr                                                         "0x00C5"
#define USB_BIST_EN_inst                                                             0x00C5
#define USB_BIST_EN_usb2_bist_en_shift                                               (1)
#define USB_BIST_EN_usb2_bist_en_mask                                                (0x00000002)
#define USB_BIST_EN_usb2_bist_en(data)                                               (0x00000002&((data)<<1))
#define USB_BIST_EN_usb2_bist_en_src(data)                                           ((0x00000002&(data))>>1)
#define USB_BIST_EN_get_usb2_bist_en(data)                                           ((0x00000002&(data))>>1)
#define USB_BIST_EN_write_data_shift                                                 (0)
#define USB_BIST_EN_write_data_mask                                                  (0x00000001)
#define USB_BIST_EN_write_data(data)                                                 (0x00000001&((data)<<0))
#define USB_BIST_EN_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define USB_BIST_EN_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define USB_BIST_ST                                                                  0x18013318
#define USB_BIST_ST_reg_addr                                                         "0xB8013318"
#define USB_BIST_ST_reg                                                              0xB8013318
#define set_USB_BIST_ST_reg(data)   (*((volatile unsigned int*) USB_BIST_ST_reg)=data)
#define get_USB_BIST_ST_reg   (*((volatile unsigned int*) USB_BIST_ST_reg))
#define USB_BIST_ST_inst_adr                                                         "0x00C6"
#define USB_BIST_ST_inst                                                             0x00C6
#define USB_BIST_ST_usb2_2_bist_fail0_shift                                          (3)
#define USB_BIST_ST_usb2_2_bist_fail0_mask                                           (0x00000008)
#define USB_BIST_ST_usb2_2_bist_fail0(data)                                          (0x00000008&((data)<<3))
#define USB_BIST_ST_usb2_2_bist_fail0_src(data)                                      ((0x00000008&(data))>>3)
#define USB_BIST_ST_get_usb2_2_bist_fail0(data)                                      ((0x00000008&(data))>>3)
#define USB_BIST_ST_usb2_2_bist_done_shift                                           (2)
#define USB_BIST_ST_usb2_2_bist_done_mask                                            (0x00000004)
#define USB_BIST_ST_usb2_2_bist_done(data)                                           (0x00000004&((data)<<2))
#define USB_BIST_ST_usb2_2_bist_done_src(data)                                       ((0x00000004&(data))>>2)
#define USB_BIST_ST_get_usb2_2_bist_done(data)                                       ((0x00000004&(data))>>2)
#define USB_BIST_ST_usb2_bist_fail0_shift                                            (1)
#define USB_BIST_ST_usb2_bist_fail0_mask                                             (0x00000002)
#define USB_BIST_ST_usb2_bist_fail0(data)                                            (0x00000002&((data)<<1))
#define USB_BIST_ST_usb2_bist_fail0_src(data)                                        ((0x00000002&(data))>>1)
#define USB_BIST_ST_get_usb2_bist_fail0(data)                                        ((0x00000002&(data))>>1)
#define USB_BIST_ST_usb2_bist_done_shift                                             (0)
#define USB_BIST_ST_usb2_bist_done_mask                                              (0x00000001)
#define USB_BIST_ST_usb2_bist_done(data)                                             (0x00000001&((data)<<0))
#define USB_BIST_ST_usb2_bist_done_src(data)                                         ((0x00000001&(data))>>0)
#define USB_BIST_ST_get_usb2_bist_done(data)                                         ((0x00000001&(data))>>0)


#define USB_DRF_START                                                                0x1801331c
#define USB_DRF_START_reg_addr                                                       "0xB801331C"
#define USB_DRF_START_reg                                                            0xB801331C
#define set_USB_DRF_START_reg(data)   (*((volatile unsigned int*) USB_DRF_START_reg)=data)
#define get_USB_DRF_START_reg   (*((volatile unsigned int*) USB_DRF_START_reg))
#define USB_DRF_START_inst_adr                                                       "0x00C7"
#define USB_DRF_START_inst                                                           0x00C7
#define USB_DRF_START_usb2_2_drf_start_pause_shift                                   (1)
#define USB_DRF_START_usb2_2_drf_start_pause_mask                                    (0x00000002)
#define USB_DRF_START_usb2_2_drf_start_pause(data)                                   (0x00000002&((data)<<1))
#define USB_DRF_START_usb2_2_drf_start_pause_src(data)                               ((0x00000002&(data))>>1)
#define USB_DRF_START_get_usb2_2_drf_start_pause(data)                               ((0x00000002&(data))>>1)
#define USB_DRF_START_usb2_drf_start_pause_shift                                     (0)
#define USB_DRF_START_usb2_drf_start_pause_mask                                      (0x00000001)
#define USB_DRF_START_usb2_drf_start_pause(data)                                     (0x00000001&((data)<<0))
#define USB_DRF_START_usb2_drf_start_pause_src(data)                                 ((0x00000001&(data))>>0)
#define USB_DRF_START_get_usb2_drf_start_pause(data)                                 ((0x00000001&(data))>>0)


#define USB_DRF_RESUME                                                               0x18013320
#define USB_DRF_RESUME_reg_addr                                                      "0xB8013320"
#define USB_DRF_RESUME_reg                                                           0xB8013320
#define set_USB_DRF_RESUME_reg(data)   (*((volatile unsigned int*) USB_DRF_RESUME_reg)=data)
#define get_USB_DRF_RESUME_reg   (*((volatile unsigned int*) USB_DRF_RESUME_reg))
#define USB_DRF_RESUME_inst_adr                                                      "0x00C8"
#define USB_DRF_RESUME_inst                                                          0x00C8
#define USB_DRF_RESUME_usb2_2_drf_test_resume_shift                                  (2)
#define USB_DRF_RESUME_usb2_2_drf_test_resume_mask                                   (0x00000004)
#define USB_DRF_RESUME_usb2_2_drf_test_resume(data)                                  (0x00000004&((data)<<2))
#define USB_DRF_RESUME_usb2_2_drf_test_resume_src(data)                              ((0x00000004&(data))>>2)
#define USB_DRF_RESUME_get_usb2_2_drf_test_resume(data)                              ((0x00000004&(data))>>2)
#define USB_DRF_RESUME_usb2_drf_test_resume_shift                                    (1)
#define USB_DRF_RESUME_usb2_drf_test_resume_mask                                     (0x00000002)
#define USB_DRF_RESUME_usb2_drf_test_resume(data)                                    (0x00000002&((data)<<1))
#define USB_DRF_RESUME_usb2_drf_test_resume_src(data)                                ((0x00000002&(data))>>1)
#define USB_DRF_RESUME_get_usb2_drf_test_resume(data)                                ((0x00000002&(data))>>1)
#define USB_DRF_RESUME_write_data_shift                                              (0)
#define USB_DRF_RESUME_write_data_mask                                               (0x00000001)
#define USB_DRF_RESUME_write_data(data)                                              (0x00000001&((data)<<0))
#define USB_DRF_RESUME_write_data_src(data)                                          ((0x00000001&(data))>>0)
#define USB_DRF_RESUME_get_write_data(data)                                          ((0x00000001&(data))>>0)


#define USB_DRF_EN                                                                   0x18013324
#define USB_DRF_EN_reg_addr                                                          "0xB8013324"
#define USB_DRF_EN_reg                                                               0xB8013324
#define set_USB_DRF_EN_reg(data)   (*((volatile unsigned int*) USB_DRF_EN_reg)=data)
#define get_USB_DRF_EN_reg   (*((volatile unsigned int*) USB_DRF_EN_reg))
#define USB_DRF_EN_inst_adr                                                          "0x00C9"
#define USB_DRF_EN_inst                                                              0x00C9
#define USB_DRF_EN_usb2_drf_bist_en_shift                                            (1)
#define USB_DRF_EN_usb2_drf_bist_en_mask                                             (0x00000002)
#define USB_DRF_EN_usb2_drf_bist_en(data)                                            (0x00000002&((data)<<1))
#define USB_DRF_EN_usb2_drf_bist_en_src(data)                                        ((0x00000002&(data))>>1)
#define USB_DRF_EN_get_usb2_drf_bist_en(data)                                        ((0x00000002&(data))>>1)
#define USB_DRF_EN_write_data_shift                                                  (0)
#define USB_DRF_EN_write_data_mask                                                   (0x00000001)
#define USB_DRF_EN_write_data(data)                                                  (0x00000001&((data)<<0))
#define USB_DRF_EN_write_data_src(data)                                              ((0x00000001&(data))>>0)
#define USB_DRF_EN_get_write_data(data)                                              ((0x00000001&(data))>>0)


#define USB_DRF_ST                                                                   0x18013328
#define USB_DRF_ST_reg_addr                                                          "0xB8013328"
#define USB_DRF_ST_reg                                                               0xB8013328
#define set_USB_DRF_ST_reg(data)   (*((volatile unsigned int*) USB_DRF_ST_reg)=data)
#define get_USB_DRF_ST_reg   (*((volatile unsigned int*) USB_DRF_ST_reg))
#define USB_DRF_ST_inst_adr                                                          "0x00CA"
#define USB_DRF_ST_inst                                                              0x00CA
#define USB_DRF_ST_usb2_2_drf_bist_fail0_shift                                       (3)
#define USB_DRF_ST_usb2_2_drf_bist_fail0_mask                                        (0x00000008)
#define USB_DRF_ST_usb2_2_drf_bist_fail0(data)                                       (0x00000008&((data)<<3))
#define USB_DRF_ST_usb2_2_drf_bist_fail0_src(data)                                   ((0x00000008&(data))>>3)
#define USB_DRF_ST_get_usb2_2_drf_bist_fail0(data)                                   ((0x00000008&(data))>>3)
#define USB_DRF_ST_usb2_2_drf_bist_done_shift                                        (2)
#define USB_DRF_ST_usb2_2_drf_bist_done_mask                                         (0x00000004)
#define USB_DRF_ST_usb2_2_drf_bist_done(data)                                        (0x00000004&((data)<<2))
#define USB_DRF_ST_usb2_2_drf_bist_done_src(data)                                    ((0x00000004&(data))>>2)
#define USB_DRF_ST_get_usb2_2_drf_bist_done(data)                                    ((0x00000004&(data))>>2)
#define USB_DRF_ST_usb2_drf_bist_fail0_shift                                         (1)
#define USB_DRF_ST_usb2_drf_bist_fail0_mask                                          (0x00000002)
#define USB_DRF_ST_usb2_drf_bist_fail0(data)                                         (0x00000002&((data)<<1))
#define USB_DRF_ST_usb2_drf_bist_fail0_src(data)                                     ((0x00000002&(data))>>1)
#define USB_DRF_ST_get_usb2_drf_bist_fail0(data)                                     ((0x00000002&(data))>>1)
#define USB_DRF_ST_usb2_drf_bist_done_shift                                          (0)
#define USB_DRF_ST_usb2_drf_bist_done_mask                                           (0x00000001)
#define USB_DRF_ST_usb2_drf_bist_done(data)                                          (0x00000001&((data)<<0))
#define USB_DRF_ST_usb2_drf_bist_done_src(data)                                      ((0x00000001&(data))>>0)
#define USB_DRF_ST_get_usb2_drf_bist_done(data)                                      ((0x00000001&(data))>>0)


#endif
