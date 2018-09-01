/**************************************************************
// Spec Version                  : 0.0.1
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/7/18 20:29:9
***************************************************************/


#ifndef _DC_PHY_REG_H_INCLUDED_
#define _DC_PHY_REG_H_INCLUDED_
#ifdef  _DC_PHY_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     tmras:9;
unsigned int     tmrcl:4;
unsigned int     tmcl:4;
unsigned int     reserved_1:1;
unsigned int     tmcl_rd:7;
}DC_PHY_TMCTRL0;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     tmrrd:5;
unsigned int     reserved_1:2;
unsigned int     tmrp:6;
unsigned int     reserved_2:2;
unsigned int     tmrcd:6;
unsigned int     tmrc:8;
}DC_PHY_TMCTRL1;

typedef struct 
{
unsigned int     tmrtw:2;
unsigned int     reserved_0:1;
unsigned int     tmccd:5;
unsigned int     reserved_1:1;
unsigned int     trtp:7;
unsigned int     reserved_2:3;
unsigned int     tmwtr:5;
unsigned int     reserved_3:2;
unsigned int     tmwr:6;
}DC_PHY_TMCTRL2;

typedef struct 
{
unsigned int     tmFAW:8;
unsigned int     reserved_0:2;
unsigned int     refcycle:10;
unsigned int     reserved_1:1;
unsigned int     tmrfc:11;
}DC_PHY_TMCTRL3;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     tAOND:6;
unsigned int     reserved_1:2;
unsigned int     tAOFD:6;
unsigned int     tmmod:8;
unsigned int     reserved_2:3;
unsigned int     tmmrd:5;
}DC_PHY_TMCTRL4;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     tzqoper:12;
unsigned int     tzqinit:12;
}DC_PHY_TMCTRL5;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     tdllk:12;
unsigned int     tzqcs:12;
}DC_PHY_TMCTRL6;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     ddr3_odt_dly_1T:1;
unsigned int     ddr3_odt_ext_1T:1;
unsigned int     ctrl_odt_en:1;
unsigned int     mars_odt_force_sel:1;
unsigned int     mars_odt_force_sig:1;
unsigned int     odt_force_sel:1;
unsigned int     odt_force_sig:1;
unsigned int     odt_en:1;
unsigned int     odt_dis:1;
unsigned int     reserved_1:5;
unsigned int     odt_en_lat:15;
}DC_PHY_ODT_CTRL;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     cal_rang:6;
unsigned int     cal_per:8;
}DC_PHY_CAL_CTRL2;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     exe_cal:1;
unsigned int     init:1;
unsigned int     sren:1;
unsigned int     srex:1;
unsigned int     exe_emr:1;
unsigned int     exe_mr:1;
}DC_PHY_DC_MIS2;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     rcd_not_eq:1;
unsigned int     tmrcdwr:4;
unsigned int     tmrp_all_add:2;
unsigned int     ap_wo_min_dly:1;
unsigned int     add_ht:1;
unsigned int     reserved_1:11;
unsigned int     ddr3:1;
}DC_PHY_DC_MIS;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     pre_dis:1;
unsigned int     reserved_1:9;
unsigned int     lbk_en:1;
unsigned int     reserved_2:2;
}DC_PHY_DC_MISA;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     tmrc_sel:1;
unsigned int     reserved_1:13;
unsigned int     cpu_rd_pri:2;
unsigned int     cpu_wr_pri:2;
unsigned int     en_rw_reord:1;
unsigned int     en_cpu_wro:1;
unsigned int     en_conflict_reord:1;
unsigned int     en_cpu_reord:1;
unsigned int     cpu_reord_thr:3;
unsigned int     en_low_reord:1;
unsigned int     dis_ap_cpu:1;
unsigned int     dis_ap_cti:1;
unsigned int     dis_ap_nor:1;
}DC_PHY_DC_MISB;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     tap_2group:1;
unsigned int     tap_mask:1;
unsigned int     fw_set:1;
unsigned int     tap_sel:1;
unsigned int     reserved_1:24;
}DC_PHY_DC_MISC;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     clear_set_sys:1;
unsigned int     clear_trig:1;
unsigned int     test_mode_sel:1;
}DC_PHY_DC_TEST_MODE_SEL;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_en_14:1;
unsigned int     ddr3_swap:1;
unsigned int     write_en_13:1;
unsigned int     end_500us:1;
unsigned int     write_en_12:1;
unsigned int     end_200us:1;
unsigned int     write_en_11:1;
unsigned int     fast_prechg:1;
unsigned int     write_en_10:1;
unsigned int     dis_cti:1;
unsigned int     write_en_9:1;
unsigned int     dis_8bank:1;
unsigned int     write_en_8:1;
unsigned int     use_tmmrd:1;
unsigned int     write_en_7:1;
unsigned int     dis_pre_all:1;
unsigned int     write_en_6:1;
unsigned int     ddr3_zqcl_short:1;
unsigned int     write_en_5:1;
unsigned int     ddr3_exe_zqcl:1;
unsigned int     write_en_4:1;
unsigned int     ddr3_exe_mr3:1;
unsigned int     write_en_3:1;
unsigned int     ddr3_exe_mr2:1;
unsigned int     write_en_2:1;
unsigned int     ddr3_exe_mr1:1;
unsigned int     write_en_1:1;
unsigned int     ddr3_exe_mr0:1;
unsigned int     write_en_0:1;
unsigned int     ddr3_init:1;
}DC_PHY_DC_DDR3_CTL;

typedef struct 
{
unsigned int     exmod_reg:16;
unsigned int     mod_reg:16;
}DC_PHY_MOD_REG;

typedef struct 
{
unsigned int     mod3_reg:16;
unsigned int     mod2_reg:16;
}DC_PHY_MOD23_REG;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     wfifo_rdy_gated:1;
unsigned int     reserved_1:3;
unsigned int     rdwr_use_full:1;
unsigned int     full_gated:1;
unsigned int     rfifo_thred:7;
}DC_PHY_RFIFO_CTL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     err_cti_cmd:1;
unsigned int     err_active:1;
}DC_PHY_ERR_STATUS;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     exe_prea:1;
unsigned int     dis_refresh:1;
unsigned int     trig_wr_level:1;
unsigned int     wr_level_rdy:1;
}DC_PHY_DC_WRITE_LEVEL;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     int_err_cticmd_en:1;
unsigned int     int_err_active_en:1;
unsigned int     int_vcpu_en:1;
unsigned int     int_acpu_en:1;
unsigned int     int_scpu_en:1;
}DC_PHY_INT_ENABLE;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     non_valid_maxcnt:1;
unsigned int     rfifo_cnt_max:7;
}DC_PHY_RFIFO_MAXCNT;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     par_st_1:5;
unsigned int     bank_act:8;
unsigned int     cmd_cnt:3;
unsigned int     par_st:10;
}DC_PHY_SM_STATUS;

typedef struct 
{
unsigned int     wfifo_sys_req_statistic_en:1;
unsigned int     wfifo_ddr_req_statistic_en:1;
unsigned int     clear_wfifo_record:1;
unsigned int     reserved_0:5;
unsigned int     wfifo_rd_cnt_et:8;
unsigned int     wfifo_rd_cnt_rl:8;
unsigned int     wfifo_wr_cnt_rl:8;
}DC_PHY_WFIFO_CNT;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     io_blk_dbg_mode:3;
unsigned int     reserved_1:1;
unsigned int     dbg_out_mod:3;
unsigned int     pad_tie_value:4;
unsigned int     shift_trig_mode:7;
unsigned int     rd_dbg_mod:3;
unsigned int     dbg_mod:6;
}DC_PHY_DC_DEBUG;

typedef struct 
{
unsigned int     post_trig_cnt:16;
unsigned int     pre_trig_cnt:16;
}DC_PHY_PRE_CNT;

typedef struct 
{
unsigned int     wfifo_sys_req_wait_total:32;
}DC_PHY_WFIFO_SYS_REQ_WAIT;

typedef struct 
{
unsigned int     wfifo_ddr_req_wait_total:32;
}DC_PHY_WFIFO_DDR_REQ_WAIT;

typedef struct 
{
unsigned int     wfifo_ddr_req_wait_max:16;
unsigned int     wfifo_sys_req_wait_max:16;
}DC_PHY_WFIFO_MAX_REQ_WAIT;

typedef struct 
{
unsigned int     wr_level_rdata:32;
}DC_PHY_DC_WRITE_LEVEL_DQ;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_1_0:6;
unsigned int     ph_sel_dq_pos_1_0:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_0_0:6;
unsigned int     ph_sel_dq_pos_0_0:6;
}DC_PHY_DQ0_1_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_3_0:6;
unsigned int     ph_sel_dq_pos_3_0:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_2_0:6;
unsigned int     ph_sel_dq_pos_2_0:6;
}DC_PHY_DQ2_3_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_5_0:6;
unsigned int     ph_sel_dq_pos_5_0:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_4_0:6;
unsigned int     ph_sel_dq_pos_4_0:6;
}DC_PHY_DQ4_5_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_7_0:6;
unsigned int     ph_sel_dq_pos_7_0:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_6_0:6;
unsigned int     ph_sel_dq_pos_6_0:6;
}DC_PHY_DQ6_7_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_1_1:6;
unsigned int     ph_sel_dq_pos_1_1:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_0_1:6;
unsigned int     ph_sel_dq_pos_0_1:6;
}DC_PHY_DQ8_9_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_3_1:6;
unsigned int     ph_sel_dq_pos_3_1:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_2_1:6;
unsigned int     ph_sel_dq_pos_2_1:6;
}DC_PHY_DQ10_11_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_5_1:6;
unsigned int     ph_sel_dq_pos_5_1:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_4_1:6;
unsigned int     ph_sel_dq_pos_4_1:6;
}DC_PHY_DQ12_13_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_7_1:6;
unsigned int     ph_sel_dq_pos_7_1:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_6_1:6;
unsigned int     ph_sel_dq_pos_6_1:6;
}DC_PHY_DQ14_15_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_1_2:6;
unsigned int     ph_sel_dq_pos_1_2:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_0_2:6;
unsigned int     ph_sel_dq_pos_0_2:6;
}DC_PHY_DQ16_17_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_3_2:6;
unsigned int     ph_sel_dq_pos_3_2:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_2_2:6;
unsigned int     ph_sel_dq_pos_2_2:6;
}DC_PHY_DQ18_19_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_5_2:6;
unsigned int     ph_sel_dq_pos_5_2:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_4_2:6;
unsigned int     ph_sel_dq_pos_4_2:6;
}DC_PHY_DQ20_21_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_7_2:6;
unsigned int     ph_sel_dq_pos_7_2:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_6_2:6;
unsigned int     ph_sel_dq_pos_6_2:6;
}DC_PHY_DQ22_23_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_1_3:6;
unsigned int     ph_sel_dq_pos_1_3:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_0_3:6;
unsigned int     ph_sel_dq_pos_0_3:6;
}DC_PHY_DQ24_25_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_3_3:6;
unsigned int     ph_sel_dq_pos_3_3:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_2_3:6;
unsigned int     ph_sel_dq_pos_2_3:6;
}DC_PHY_DQ26_27_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_5_3:6;
unsigned int     ph_sel_dq_pos_5_3:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_4_3:6;
unsigned int     ph_sel_dq_pos_4_3:6;
}DC_PHY_DQ28_29_DLYN;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ph_sel_dq_neg_7_3:6;
unsigned int     ph_sel_dq_pos_7_3:6;
unsigned int     reserved_1:4;
unsigned int     ph_sel_dq_neg_6_3:6;
unsigned int     ph_sel_dq_pos_6_3:6;
}DC_PHY_DQ30_31_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq1_neg_dlyn_0:6;
unsigned int     cal_dq1_pos_dlyn_0:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq0_neg_dlyn_0:6;
unsigned int     cal_dq0_pos_dlyn_0:6;
}DC_PHY_CAL0_1_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq3_neg_dlyn_0:6;
unsigned int     cal_dq3_pos_dlyn_0:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq2_neg_dlyn_0:6;
unsigned int     cal_dq2_pos_dlyn_0:6;
}DC_PHY_CAL2_3_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq5_neg_dlyn_0:6;
unsigned int     cal_dq5_pos_dlyn_0:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq4_neg_dlyn_0:6;
unsigned int     cal_dq4_pos_dlyn_0:6;
}DC_PHY_CAL4_5_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq7_neg_dlyn_0:6;
unsigned int     cal_dq7_pos_dlyn_0:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq6_neg_dlyn_0:6;
unsigned int     cal_dq6_pos_dlyn_0:6;
}DC_PHY_CAL6_7_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq1_neg_dlyn_1:6;
unsigned int     cal_dq1_pos_dlyn_1:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq0_neg_dlyn_1:6;
unsigned int     cal_dq0_pos_dlyn_1:6;
}DC_PHY_CAL8_9_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq3_neg_dlyn_1:6;
unsigned int     cal_dq3_pos_dlyn_1:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq2_neg_dlyn_1:6;
unsigned int     cal_dq2_pos_dlyn_1:6;
}DC_PHY_CAL10_11_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq5_neg_dlyn_1:6;
unsigned int     cal_dq5_pos_dlyn_1:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq4_neg_dlyn_1:6;
unsigned int     cal_dq4_pos_dlyn_1:6;
}DC_PHY_CAL12_13_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq7_neg_dlyn_1:6;
unsigned int     cal_dq7_pos_dlyn_1:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq6_neg_dlyn_1:6;
unsigned int     cal_dq6_pos_dlyn_1:6;
}DC_PHY_CAL14_15_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq1_neg_dlyn_2:6;
unsigned int     cal_dq1_pos_dlyn_2:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq0_neg_dlyn_2:6;
unsigned int     cal_dq0_pos_dlyn_2:6;
}DC_PHY_CAL16_17_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq3_neg_dlyn_2:6;
unsigned int     cal_dq3_pos_dlyn_2:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq2_neg_dlyn_2:6;
unsigned int     cal_dq2_pos_dlyn_2:6;
}DC_PHY_CAL18_19_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq5_neg_dlyn_2:6;
unsigned int     cal_dq5_pos_dlyn_2:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq4_neg_dlyn_2:6;
unsigned int     cal_dq4_pos_dlyn_2:6;
}DC_PHY_CAL20_21_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq7_neg_dlyn_2:6;
unsigned int     cal_dq7_pos_dlyn_2:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq6_neg_dlyn_2:6;
unsigned int     cal_dq6_pos_dlyn_2:6;
}DC_PHY_CAL22_23_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq1_neg_dlyn_3:6;
unsigned int     cal_dq1_pos_dlyn_3:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq0_neg_dlyn_3:6;
unsigned int     cal_dq0_pos_dlyn_3:6;
}DC_PHY_CAL24_25_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq3_neg_dlyn_3:6;
unsigned int     cal_dq3_pos_dlyn_3:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq2_neg_dlyn_3:6;
unsigned int     cal_dq2_pos_dlyn_3:6;
}DC_PHY_CAL26_27_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq5_neg_dlyn_3:6;
unsigned int     cal_dq5_pos_dlyn_3:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq4_neg_dlyn_3:6;
unsigned int     cal_dq4_pos_dlyn_3:6;
}DC_PHY_CAL28_29_DLYN;

typedef struct 
{
unsigned int     non_valid:1;
unsigned int     reserved_0:3;
unsigned int     cal_dq7_neg_dlyn_3:6;
unsigned int     cal_dq7_pos_dlyn_3:6;
unsigned int     reserved_1:4;
unsigned int     cal_dq6_neg_dlyn_3:6;
unsigned int     cal_dq6_pos_dlyn_3:6;
}DC_PHY_CAL30_31_DLYN;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     read_lat_sel:1;
unsigned int     read_lat:2;
unsigned int     ph_sel_read23:4;
unsigned int     ph_sel_read01:4;
unsigned int     reserved_1:3;
unsigned int     read_com_sel:1;
}DC_PHY_READ_COM_CTRL;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     pos_trig_sel:3;
unsigned int     reserved_1:1;
unsigned int     pre_trig_sel:3;
unsigned int     reserved_2:2;
unsigned int     sync_cal_dlyn:1;
unsigned int     auto_cal:1;
}DC_PHY_CAL_CTRL;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     gated_latch_sel:1;
unsigned int     clk_ddr_phy_mux_div2_0_ph_sel:1;
unsigned int     clk_ddr_div2_odd_1_ph_sel:1;
unsigned int     clk_ddr_div2_odd_0_ph_sel:1;
unsigned int     clk_ddr_div2_1_ph_sel:1;
unsigned int     clk_ddr_div2_0_ph_sel:1;
unsigned int     Tx_dlc_sel_dck_1:4;
unsigned int     reserved_1:2;
unsigned int     dqsf_dlyn:2;
unsigned int     Tx_dlc_sel_dck:4;
}DC_PHY_FIFO_DLYN;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     grp1_bk_oe:1;
unsigned int     grp1_addr1_oe:1;
unsigned int     grp1_addr_oe:1;
unsigned int     grp1_cke_oe:1;
unsigned int     grp1_ck_oe:1;
unsigned int     grp1_addr1_15_oe:1;
unsigned int     grp1_addr1_14_oe:1;
unsigned int     grp1_addr1_13_oe:1;
unsigned int     grp1_addr_15_oe:1;
unsigned int     grp1_addr_14_oe:1;
unsigned int     grp1_addr_13_oe:1;
unsigned int     reserved_1:1;
}DC_PHY_PAD_OE_CTL;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     iddq_0:13;
}DC_PHY_PAD_IDDQ0;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     refctrl_pdref:1;
unsigned int     reserved_1:1;
unsigned int     zctrl_ovrd_en:1;
unsigned int     zctrl_ovrd_data:22;
}DC_PHY_PAD_ZCTRL_OVRD;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ocd_mode:1;
unsigned int     dzq_up_sel:3;
unsigned int     dzq_auto_up:1;
unsigned int     zctrl_clk_sel:2;
unsigned int     zctrl_start:1;
unsigned int     dzq_ref_up:1;
unsigned int     ext_r240_sel:1;
unsigned int     rzq_zcomp_inv:1;
unsigned int     rzq_cal_en:1;
unsigned int     reserved_1:2;
unsigned int     zprog:14;
}DC_PHY_PAD_CTRL_PROG;

typedef struct 
{
unsigned int     zctrl_status:32;
}DC_PHY_PAD_ZCTRL_STATUS;

typedef struct 
{
unsigned int     dq_dly_sel0:32;
}DC_PHY_DQ_DLY_SEL0;

typedef struct 
{
unsigned int     dq_dly_sel1:32;
}DC_PHY_DQ_DLY_SEL1;

typedef struct 
{
unsigned int     dq_dly_sel2:32;
}DC_PHY_DQ_DLY_SEL2;

typedef struct 
{
unsigned int     dq_dly_sel3:32;
}DC_PHY_DQ_DLY_SEL3;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     dqs_oe_dly_sel:12;
}DC_PHY_DQS_OE_DLY_SEL;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     half_cycle_cal_sel:1;
unsigned int     half_cycle_ref_thr:8;
unsigned int     half_cycle_res_thr:6;
unsigned int     half_cycle_res_mod:2;
unsigned int     half_cycle_cal_en:1;
}DC_PHY_HALF_CYCLE_CAL_EN;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     half_cycle_cal_setting_3:6;
unsigned int     half_cycle_cal_setting_2:6;
unsigned int     half_cycle_cal_setting_1:6;
unsigned int     half_cycle_cal_setting_0:6;
}DC_PHY_HALF_CYCLE_CAL_SET;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     pupd_dly_mux_sel:2;
unsigned int     pupd_dly_num_sel:2;
unsigned int     pupd_dly_num_3:5;
unsigned int     pupd_dly_num_2:5;
unsigned int     pupd_dly_num_1:5;
unsigned int     pupd_dly_num_0:5;
}DC_PHY_PUPD_DLY_NUM;

typedef struct 
{
unsigned int     dqs3_det_0_dlyn:4;
unsigned int     dqs2_det_0_dlyn:4;
unsigned int     dqs1_det_0_dlyn:4;
unsigned int     dqs0_det_0_dlyn:4;
unsigned int     dqs3_en_0_dlyn:4;
unsigned int     dqs2_en_0_dlyn:4;
unsigned int     dqs1_en_0_dlyn:4;
unsigned int     dqs0_en_0_dlyn:4;
}DC_PHY_DQS_DLYN;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     pupd_mode:2;
unsigned int     cal_order:1;
unsigned int     cal_mode_split:1;
unsigned int     cal_zq_only:1;
unsigned int     cal_zq:1;
unsigned int     cal_all_rang_noml:1;
unsigned int     cal_all_rang_init:1;
unsigned int     auto_cal_en_noml:1;
unsigned int     auto_cal_en_init:1;
unsigned int     dqs_val_sel:1;
unsigned int     cal_mode:3;
unsigned int     dq_sel:1;
}DC_PHY_CAL_MODE;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     cal_ba:3;
unsigned int     cal_col:10;
unsigned int     cal_row:13;
}DC_PHY_CAL_ADDR;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     end_done_01_p:1;
unsigned int     start_done_01_p:1;
unsigned int     best_dly_01_p:6;
unsigned int     end_pt_01_p:6;
unsigned int     start_pt_01_p:6;
}DC_PHY_RESULT_CAL_TAP_0;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     end_done_01_n:1;
unsigned int     start_done_01_n:1;
unsigned int     best_dly_01_n:6;
unsigned int     end_pt_01_n:6;
unsigned int     start_pt_01_n:6;
}DC_PHY_RESULT_CAL_TAP_1;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     end_done_23_p:1;
unsigned int     start_done_23_p:1;
unsigned int     best_dly_23_p:6;
unsigned int     end_pt_23_p:6;
unsigned int     start_pt_23_p:6;
}DC_PHY_RESULT_CAL_TAP_2;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     end_done_23_n:1;
unsigned int     start_done_23_n:1;
unsigned int     best_dly_23_n:6;
unsigned int     end_pt_23_n:6;
unsigned int     start_pt_23_n:6;
}DC_PHY_RESULT_CAL_TAP_3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     wk_big_thr_23_n_odt:1;
unsigned int     wk_big_thr_23_p_odt:1;
unsigned int     wk_big_thr_01_n_odt:1;
unsigned int     wk_big_thr_01_p_odt:1;
unsigned int     wk_big_thr_23_n_dt:1;
unsigned int     wk_big_thr_23_p_dt:1;
unsigned int     wk_big_thr_01_n_dt:1;
unsigned int     wk_big_thr_01_p_dt:1;
}DC_PHY_RESULT_CAL_TAP_4;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     best_wk_01_n_odt:6;
unsigned int     reserved_1:2;
unsigned int     best_wk_01_p_odt:6;
unsigned int     reserved_2:2;
unsigned int     best_wk_01_n_dt:6;
unsigned int     reserved_3:2;
unsigned int     best_wk_01_p_dt:6;
}DC_PHY_RESULT_CAL_TAP_5;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     best_wk_23_n_odt:6;
unsigned int     reserved_1:2;
unsigned int     best_wk_23_p_odt:6;
unsigned int     reserved_2:2;
unsigned int     best_wk_23_n_dt:6;
unsigned int     reserved_3:2;
unsigned int     best_wk_23_p_dt:6;
}DC_PHY_RESULT_CAL_TAP_6;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     odt_diff_threshold:6;
unsigned int     reserved_1:2;
unsigned int     duty_diff_threshold:6;
unsigned int     cal_proc_done:1;
unsigned int     wk_threshold:6;
unsigned int     sync_rst_wk_thr:1;
}DC_PHY_SYNC_RST_WK;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sync_rst_fifo_pt:1;
}DC_PHY_SYNC_RST_FIFO_PT;

typedef struct 
{
unsigned int     cal_out_data_1:16;
unsigned int     cal_out_data_0:16;
}DC_PHY_CAL_OUT_DATA_A;

typedef struct 
{
unsigned int     cal_out_data_3:16;
unsigned int     cal_out_data_2:16;
}DC_PHY_CAL_OUT_DATA_B;

typedef struct 
{
unsigned int     cal_gld_data_1:16;
unsigned int     cal_gld_data_0:16;
}DC_PHY_CAL_GLD_DATA_A;

typedef struct 
{
unsigned int     cal_gld_data_3:16;
unsigned int     cal_gld_data_2:16;
}DC_PHY_CAL_GLD_DATA_B;

typedef struct 
{
unsigned int     id_cal_cnt_p_end:4;
unsigned int     id_cal_cnt_p_srt:4;
unsigned int     id_cal_cnt_n_end:4;
unsigned int     id_cal_cnt_n_srt:4;
unsigned int     odt_cal_cnt_p_end:4;
unsigned int     odt_cal_cnt_p_srt:4;
unsigned int     odt_cal_cnt_n_end:4;
unsigned int     odt_cal_cnt_n_srt:4;
}DC_PHY_CAL_CNT_CTRL;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     ddr_clk_1_mux_sel:1;
unsigned int     ddr_clk_0_mux_sel:1;
unsigned int     ddr_clk_1_2x_div2_ph_sel:1;
unsigned int     ddr_clk_0_2x_div2_ph_sel:1;
unsigned int     mck_dqs3_mux_sel:1;
unsigned int     mck_dqs2_mux_sel:1;
unsigned int     mck_dqs1_mux_sel:1;
unsigned int     mck_dqs0_mux_sel:1;
unsigned int     mck_dqs3_2x_div2_ph_sel:1;
unsigned int     mck_dqs2_2x_div2_ph_sel:1;
unsigned int     mck_dqs1_2x_div2_ph_sel:1;
unsigned int     mck_dqs0_2x_div2_ph_sel:1;
}DC_PHY_MUX2TO1_CTRL;

typedef struct 
{
unsigned int     dummy_reg:32;
}DC_PHY_DUMMY_REG;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     dt_set_0:16;
}DC_PHY_DT_SET0;

typedef struct 
{
unsigned int     dt_set_1:32;
}DC_PHY_DT_SET1;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     update_dqs:1;
unsigned int     update_dq:1;
}DC_PHY_DT_CTL;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     odt_23_n:3;
unsigned int     odt_23_p:3;
unsigned int     odt_01_n:3;
unsigned int     odt_01_p:3;
unsigned int     indt_23_n:2;
unsigned int     indt_23_p:2;
unsigned int     indt_01_n:2;
unsigned int     indt_01_p:2;
}DC_PHY_CAL_DT_RESULT;

typedef struct 
{
unsigned int     odt_ttcp_set_7_pre:4;
unsigned int     odt_ttcp_set_6_pre:4;
unsigned int     odt_ttcp_set_5_pre:4;
unsigned int     odt_ttcp_set_4_pre:4;
unsigned int     odt_ttcp_set_3_pre:4;
unsigned int     odt_ttcp_set_2_pre:4;
unsigned int     odt_ttcp_set_1_pre:4;
unsigned int     odt_ttcp_set_0_pre:4;
}DC_PHY_ODT_TTCP_SET_PRE;

typedef struct 
{
unsigned int     odt_ttcn_set_7_pre:4;
unsigned int     odt_ttcn_set_6_pre:4;
unsigned int     odt_ttcn_set_5_pre:4;
unsigned int     odt_ttcn_set_4_pre:4;
unsigned int     odt_ttcn_set_3_pre:4;
unsigned int     odt_ttcn_set_2_pre:4;
unsigned int     odt_ttcn_set_1_pre:4;
unsigned int     odt_ttcn_set_0_pre:4;
}DC_PHY_ODT_TTCN_SET_PRE;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     odt_ttfp_set_7_pre:3;
unsigned int     odt_ttfp_set_6_pre:3;
unsigned int     odt_ttfp_set_5_pre:3;
unsigned int     odt_ttfp_set_4_pre:3;
unsigned int     odt_ttfp_set_3_pre:3;
unsigned int     odt_ttfp_set_2_pre:3;
unsigned int     odt_ttfp_set_1_pre:3;
unsigned int     odt_ttfp_set_0_pre:3;
}DC_PHY_ODT_TTFP_SET_PRE;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     odt_ttfn_set_7_pre:3;
unsigned int     odt_ttfn_set_6_pre:3;
unsigned int     odt_ttfn_set_5_pre:3;
unsigned int     odt_ttfn_set_4_pre:3;
unsigned int     odt_ttfn_set_3_pre:3;
unsigned int     odt_ttfn_set_2_pre:3;
unsigned int     odt_ttfn_set_1_pre:3;
unsigned int     odt_ttfn_set_0_pre:3;
}DC_PHY_ODT_TTFN_SET_PRE;

typedef struct 
{
unsigned int     ocdp_set_7_pre:4;
unsigned int     ocdp_set_6_pre:4;
unsigned int     ocdp_set_5_pre:4;
unsigned int     ocdp_set_4_pre:4;
unsigned int     ocdp_set_3_pre:4;
unsigned int     ocdp_set_2_pre:4;
unsigned int     ocdp_set_1_pre:4;
unsigned int     ocdp_set_0_pre:4;
}DC_PHY_OCDP_SET_PRE;

typedef struct 
{
unsigned int     ocdn_set_7_pre:4;
unsigned int     ocdn_set_6_pre:4;
unsigned int     ocdn_set_5_pre:4;
unsigned int     ocdn_set_4_pre:4;
unsigned int     ocdn_set_3_pre:4;
unsigned int     ocdn_set_2_pre:4;
unsigned int     ocdn_set_1_pre:4;
unsigned int     ocdn_set_0_pre:4;
}DC_PHY_OCDN_SET_PRE;

typedef struct 
{
unsigned int     odt_ttcp_set_7:4;
unsigned int     odt_ttcp_set_6:4;
unsigned int     odt_ttcp_set_5:4;
unsigned int     odt_ttcp_set_4:4;
unsigned int     odt_ttcp_set_3:4;
unsigned int     odt_ttcp_set_2:4;
unsigned int     odt_ttcp_set_1:4;
unsigned int     odt_ttcp_set_0:4;
}DC_PHY_ODT_TTCP_SET;

typedef struct 
{
unsigned int     odt_ttcn_set_7:4;
unsigned int     odt_ttcn_set_6:4;
unsigned int     odt_ttcn_set_5:4;
unsigned int     odt_ttcn_set_4:4;
unsigned int     odt_ttcn_set_3:4;
unsigned int     odt_ttcn_set_2:4;
unsigned int     odt_ttcn_set_1:4;
unsigned int     odt_ttcn_set_0:4;
}DC_PHY_ODT_TTCN_SET;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     odt_ttfp_set_7:3;
unsigned int     odt_ttfp_set_6:3;
unsigned int     odt_ttfp_set_5:3;
unsigned int     odt_ttfp_set_4:3;
unsigned int     odt_ttfp_set_3:3;
unsigned int     odt_ttfp_set_2:3;
unsigned int     odt_ttfp_set_1:3;
unsigned int     odt_ttfp_set_0:3;
}DC_PHY_ODT_TTFP_SET;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     odt_ttfn_set_7:3;
unsigned int     odt_ttfn_set_6:3;
unsigned int     odt_ttfn_set_5:3;
unsigned int     odt_ttfn_set_4:3;
unsigned int     odt_ttfn_set_3:3;
unsigned int     odt_ttfn_set_2:3;
unsigned int     odt_ttfn_set_1:3;
unsigned int     odt_ttfn_set_0:3;
}DC_PHY_ODT_TTFN_SET;

typedef struct 
{
unsigned int     ocdp_set_7:4;
unsigned int     ocdp_set_6:4;
unsigned int     ocdp_set_5:4;
unsigned int     ocdp_set_4:4;
unsigned int     ocdp_set_3:4;
unsigned int     ocdp_set_2:4;
unsigned int     ocdp_set_1:4;
unsigned int     ocdp_set_0:4;
}DC_PHY_OCDP_SET;

typedef struct 
{
unsigned int     ocdn_set_7:4;
unsigned int     ocdn_set_6:4;
unsigned int     ocdn_set_5:4;
unsigned int     ocdn_set_4:4;
unsigned int     ocdn_set_3:4;
unsigned int     ocdn_set_2:4;
unsigned int     ocdn_set_1:4;
unsigned int     ocdn_set_0:4;
}DC_PHY_OCDN_SET;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     dq_3_ttcn_sel:3;
unsigned int     dq_2_ttcn_sel:3;
unsigned int     dq_1_ttcn_sel:3;
unsigned int     dq_0_ttcn_sel:3;
unsigned int     dq_3_ttcp_sel:3;
unsigned int     dq_2_ttcp_sel:3;
unsigned int     dq_1_ttcp_sel:3;
unsigned int     dq_0_ttcp_sel:3;
}DC_PHY_DQ_TTC_SEL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     dq_3_ttfn_sel:3;
unsigned int     dq_2_ttfn_sel:3;
unsigned int     dq_1_ttfn_sel:3;
unsigned int     dq_0_ttfn_sel:3;
unsigned int     dq_3_ttfp_sel:3;
unsigned int     dq_2_ttfp_sel:3;
unsigned int     dq_1_ttfp_sel:3;
unsigned int     dq_0_ttfp_sel:3;
}DC_PHY_DQ_TTF_SEL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     dq_3_ocdn_sel:3;
unsigned int     dq_2_ocdn_sel:3;
unsigned int     dq_1_ocdn_sel:3;
unsigned int     dq_0_ocdn_sel:3;
unsigned int     dq_3_ocdp_sel:3;
unsigned int     dq_2_ocdp_sel:3;
unsigned int     dq_1_ocdp_sel:3;
unsigned int     dq_0_ocdp_sel:3;
}DC_PHY_DQ_OCD_SEL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     dqs_p_3_ttcn_sel:3;
unsigned int     dqs_p_2_ttcn_sel:3;
unsigned int     dqs_p_1_ttcn_sel:3;
unsigned int     dqs_p_0_ttcn_sel:3;
unsigned int     dqs_p_3_ttcp_sel:3;
unsigned int     dqs_p_2_ttcp_sel:3;
unsigned int     dqs_p_1_ttcp_sel:3;
unsigned int     dqs_p_0_ttcp_sel:3;
}DC_PHY_DQS_P_TTC_SEL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     dqs_n_3_ttcn_sel:3;
unsigned int     dqs_n_2_ttcn_sel:3;
unsigned int     dqs_n_1_ttcn_sel:3;
unsigned int     dqs_n_0_ttcn_sel:3;
unsigned int     dqs_n_3_ttcp_sel:3;
unsigned int     dqs_n_2_ttcp_sel:3;
unsigned int     dqs_n_1_ttcp_sel:3;
unsigned int     dqs_n_0_ttcp_sel:3;
}DC_PHY_DQS_N_TTC_SEL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     dqs_p_3_ttfn_sel:3;
unsigned int     dqs_p_2_ttfn_sel:3;
unsigned int     dqs_p_1_ttfn_sel:3;
unsigned int     dqs_p_0_ttfn_sel:3;
unsigned int     dqs_p_3_ttfp_sel:3;
unsigned int     dqs_p_2_ttfp_sel:3;
unsigned int     dqs_p_1_ttfp_sel:3;
unsigned int     dqs_p_0_ttfp_sel:3;
}DC_PHY_DQS_P_TTF_SEL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     dqs_n_3_ttfn_sel:3;
unsigned int     dqs_n_2_ttfn_sel:3;
unsigned int     dqs_n_1_ttfn_sel:3;
unsigned int     dqs_n_0_ttfn_sel:3;
unsigned int     dqs_n_3_ttfp_sel:3;
unsigned int     dqs_n_2_ttfp_sel:3;
unsigned int     dqs_n_1_ttfp_sel:3;
unsigned int     dqs_n_0_ttfp_sel:3;
}DC_PHY_DQS_N_TTF_SEL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     dqs_p_3_ocdn_sel:3;
unsigned int     dqs_p_2_ocdn_sel:3;
unsigned int     dqs_p_1_ocdn_sel:3;
unsigned int     dqs_p_0_ocdn_sel:3;
unsigned int     dqs_p_3_ocdp_sel:3;
unsigned int     dqs_p_2_ocdp_sel:3;
unsigned int     dqs_p_1_ocdp_sel:3;
unsigned int     dqs_p_0_ocdp_sel:3;
}DC_PHY_DQS_P_OCD_SEL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     dqs_n_3_ocdn_sel:3;
unsigned int     dqs_n_2_ocdn_sel:3;
unsigned int     dqs_n_1_ocdn_sel:3;
unsigned int     dqs_n_0_ocdn_sel:3;
unsigned int     dqs_n_3_ocdp_sel:3;
unsigned int     dqs_n_2_ocdp_sel:3;
unsigned int     dqs_n_1_ocdp_sel:3;
unsigned int     dqs_n_0_ocdp_sel:3;
}DC_PHY_DQS_N_OCD_SEL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     adr_1_ocdn_sel:3;
unsigned int     adr_0_ocdn_sel:3;
unsigned int     cmd_1_ocdn_sel:3;
unsigned int     cmd_0_ocdn_sel:3;
unsigned int     adr_1_ocdp_sel:3;
unsigned int     adr_0_ocdp_sel:3;
unsigned int     cmd_1_ocdp_sel:3;
unsigned int     cmd_0_ocdp_sel:3;
}DC_PHY_ADR_OCD_SEL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     ck_n_1_ocdn_sel:3;
unsigned int     ck_n_0_ocdn_sel:3;
unsigned int     ck_n_1_ocdp_sel:3;
unsigned int     ck_n_0_ocdp_sel:3;
unsigned int     ck_p_1_ocdn_sel:3;
unsigned int     ck_p_0_ocdn_sel:3;
unsigned int     ck_p_1_ocdp_sel:3;
unsigned int     ck_p_0_ocdp_sel:3;
}DC_PHY_CK_OCD_SEL;

typedef struct 
{
unsigned int     pad_bus_0:32;
}DC_PHY_PAD_BUS_0;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     pad_bus_1:4;
}DC_PHY_PAD_BUS_1;

typedef struct 
{
unsigned int     dll_en_test:1;
unsigned int     dll_sc:3;
unsigned int     dll_sel_ipump:4;
unsigned int     dll_pfd_div:6;
unsigned int     dll_pre_divn:2;
unsigned int     dll_en_newpump:1;
unsigned int     dll_bin_dl2_ph_sel:5;
unsigned int     dll_bin_dl1_ph_sel:5;
unsigned int     dll_bin_dl0_ph_sel:5;
}DC_PHY_ANA_DLL_1;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     dll_en_3:1;
unsigned int     dll_en_2:1;
unsigned int     dll_en_1:1;
unsigned int     dll_en_0:1;
unsigned int     dll_dl_ph_sel:1;
unsigned int     dll_rdy_3:1;
unsigned int     dll_rdy_2:1;
unsigned int     dll_rdy_1:1;
unsigned int     dll_rdy_0:1;
unsigned int     dll_div_sel:2;
unsigned int     dll_ck_sel:1;
unsigned int     ana_dly_sel:1;
}DC_PHY_ANA_DLL_2;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     write_en_2:1;
unsigned int     lpddr_ck_en:1;
unsigned int     write_en_1:1;
unsigned int     mod_reg_read:1;
unsigned int     write_en_0:1;
unsigned int     mod_reg_write:1;
}DC_PHY_LPDDR_CTRL;

typedef struct 
{
unsigned int     mode_reg_rdata:8;
unsigned int     reserved_0:24;
}DC_PHY_LPDDR_RDAT;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     mode_reg_wdata:8;
unsigned int     mode_reg_addr:8;
unsigned int     reserved_1:1;
unsigned int     lpddr:1;
unsigned int     reserved_2:6;
}DC_PHY_LPDDR_MODE;

typedef struct 
{
unsigned int     ref_update_dly:6;
unsigned int     reserved_0:22;
unsigned int     zcomp_ctrl:4;
}DC_PHY_ZQCMP;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     zq_done:1;
unsigned int     rzq_done:1;
unsigned int     rzq_480code:5;
unsigned int     rzq_cal_done:1;
}DC_PHY_RZCTRL_STATUS;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     bist_en_0:1;
unsigned int     drf_bist_en_0:1;
unsigned int     drf_test_resume_0:1;
unsigned int     reserved_1:1;
unsigned int     RMEA:1;
unsigned int     RMA_3:1;
unsigned int     RMA_2:1;
unsigned int     RMA_1:1;
unsigned int     RMA_0:1;
unsigned int     reserved_2:3;
unsigned int     RMEB:1;
unsigned int     RMB_3:1;
unsigned int     RMB_2:1;
unsigned int     RMB_1:1;
unsigned int     RMB_0:1;
}DC_PHY_PHY_BIST_RM;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     mbist_st:1;
unsigned int     bist_fail:1;
unsigned int     bist_done:1;
}DC_PHY_PHY_BIST0_ST;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     drf_start_pause:1;
unsigned int     reserved_1:14;
unsigned int     drf_fail:1;
unsigned int     drf_done:1;
}DC_PHY_PHY_DRF0_ST;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     mbist_st:1;
unsigned int     bist_fail:1;
unsigned int     bist_done:1;
}DC_PHY_PHY_BIST1_ST;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     drf_start_pause:1;
unsigned int     reserved_1:14;
unsigned int     drf_fail:1;
unsigned int     drf_done:1;
}DC_PHY_PHY_DRF1_ST;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     wl_dqs3_oe_mux_sel:2;
unsigned int     wl_dqs2_oe_mux_sel:2;
unsigned int     wl_dqs1_oe_mux_sel:2;
unsigned int     wl_dqs0_oe_mux_sel:2;
unsigned int     wl_dqs3_mux_sel:2;
unsigned int     wl_dqs2_mux_sel:2;
unsigned int     wl_dqs1_mux_sel:2;
unsigned int     wl_dqs0_mux_sel:2;
}DC_PHY_WL_CTRL_0;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     wl_dq31to24_oe_mux_sel:2;
unsigned int     wl_dq23to16_oe_mux_sel:2;
unsigned int     wl_dq15to8_oe_mux_sel:2;
unsigned int     wl_dq7to0_oe_mux_sel:2;
unsigned int     wl_dq31to24_mux_sel:2;
unsigned int     wl_dq23to16_mux_sel:2;
unsigned int     wl_dq15to8_mux_sel:2;
unsigned int     wl_dq7to0_mux_sel:2;
}DC_PHY_WL_CTRL_1;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     fifo_arb_sel:1;
unsigned int     reserved_1:1;
unsigned int     cmdq_ch_fifo_cnt:3;
unsigned int     reserved_2:2;
unsigned int     cmdq_ch_fifo_rd_ptr:2;
unsigned int     reserved_3:2;
unsigned int     cmdq_ch_fifo_wr_ptr:2;
unsigned int     cmdq_ch_fifo_overflow:1;
unsigned int     cmdq_ch_fifo_underflow:1;
unsigned int     cmdq_ch_fifo_full:1;
unsigned int     cmdq_ch_fifo_empty:1;
unsigned int     cmdq_ch_fifo_thr:4;
unsigned int     cmdq_ch_fifo_overflow_clr:1;
unsigned int     cmdq_ch_fifo_underflow_clr:1;
unsigned int     cmdq_ch_clk_gated_en:1;
unsigned int     fifo_arb_dis:1;
}DC_PHY_FIFO_ARB_0;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     cmdq_ch_gnt_mst1_cmd_dis:1;
unsigned int     cmdq_ch_gnt_mst1_cti_dis:1;
unsigned int     reserved_1:2;
unsigned int     cmdq_ch_gnt_mst0_cmd_dis:1;
unsigned int     cmdq_ch_gnt_mst0_cti_dis:1;
}DC_PHY_FIFO_ARB_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     cmdq_ch_dbg_mod:8;
}DC_PHY_FIFO_ARB_2;

typedef struct 
{
unsigned int     cmdq_ch_dummy_0:32;
}DC_PHY_FIFO_ARB_3;

typedef struct 
{
unsigned int     cmdq_ch_gnt_st0:32;
}DC_PHY_FIFO_ARB_4;

typedef struct 
{
unsigned int     cmdq_ch_gnt_st1:32;
}DC_PHY_FIFO_ARB_5;

typedef struct 
{
unsigned int     cmdq_ch_gnt_st2:32;
}DC_PHY_FIFO_ARB_6;

typedef struct 
{
unsigned int     cmdq_ch_gnt_st3:32;
}DC_PHY_FIFO_ARB_7;

typedef struct 
{
unsigned int     cmdq_ch_gnt_st4:32;
}DC_PHY_FIFO_ARB_8;

typedef struct 
{
unsigned int     cmdq_ch_gnt_st5:32;
}DC_PHY_FIFO_ARB_9;

typedef struct 
{
unsigned int     cmdq_ch_gnt_st6:32;
}DC_PHY_FIFO_ARB_10;

typedef struct 
{
unsigned int     cmdq_ch_gnt_st7:32;
}DC_PHY_FIFO_ARB_11;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     wq_ch_fifo_rd_ptr:5;
unsigned int     reserved_1:3;
unsigned int     wq_ch_fifo_wr_ptr:5;
unsigned int     wq_ch_fifo_overflow:1;
unsigned int     wq_ch_fifo_underflow:1;
unsigned int     wq_ch_fifo_full:1;
unsigned int     wq_ch_fifo_empty:1;
unsigned int     reserved_2:2;
unsigned int     wq_ch_fifo_thr:6;
unsigned int     wq_ch_fifo_overflow_clr:1;
unsigned int     wq_ch_fifo_underflow_clr:1;
unsigned int     wq_ch_clk_gated_en:1;
unsigned int     reserved_3:1;
}DC_PHY_FIFO_ARB_12;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     wq_ch_dbg_mod:8;
unsigned int     reserved_1:2;
unsigned int     wq_ch_fifo_cnt:6;
}DC_PHY_FIFO_ARB_13;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     wq_ch_fifo_par_rd_ptr:5;
unsigned int     reserved_1:3;
unsigned int     wq_ch_fifo_par_wr_ptr:5;
unsigned int     wq_ch_fifo_par_overflow:1;
unsigned int     wq_ch_fifo_par_underflow:1;
unsigned int     wq_ch_fifo_par_full:1;
unsigned int     wq_ch_fifo_par_empty:1;
unsigned int     reserved_2:2;
unsigned int     wq_ch_fifo_par_thr:6;
unsigned int     wq_ch_fifo_par_overflow_clr:1;
unsigned int     wq_ch_fifo_par_underflow_clr:1;
unsigned int     reserved_3:2;
}DC_PHY_FIFO_ARB_14;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     wq_ch_fifo_par_cnt:6;
}DC_PHY_FIFO_ARB_15;

typedef struct 
{
unsigned int     wq_ch_dummy_0:32;
}DC_PHY_FIFO_ARB_16;

typedef struct 
{
unsigned int     wq_ch_st0:32;
}DC_PHY_FIFO_ARB_17;

typedef struct 
{
unsigned int     wq_ch_st1:32;
}DC_PHY_FIFO_ARB_18;

typedef struct 
{
unsigned int     wq_ch_st2:32;
}DC_PHY_FIFO_ARB_19;

typedef struct 
{
unsigned int     wq_ch_st3:32;
}DC_PHY_FIFO_ARB_20;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     rq_ch_fifo_rd_ptr:4;
unsigned int     reserved_1:4;
unsigned int     rq_ch_fifo_wr_ptr:4;
unsigned int     rq_ch_fifo_overflow:1;
unsigned int     rq_ch_fifo_underflow:1;
unsigned int     rq_ch_fifo_full:1;
unsigned int     rq_ch_fifo_empty:1;
unsigned int     reserved_2:3;
unsigned int     rq_ch_fifo_thr:5;
unsigned int     rq_ch_fifo_overflow_clr:1;
unsigned int     rq_ch_fifo_underflow_clr:1;
unsigned int     rq_ch_clk_gated_en:1;
unsigned int     reserved_3:1;
}DC_PHY_FIFO_ARB_21;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     rq_ch_fifo_cnt:5;
}DC_PHY_FIFO_ARB_22;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     wcol_adr_q_thr:5;
unsigned int     rq_ch_dbg_mod:8;
}DC_PHY_FIFO_ARB_23;

typedef struct 
{
unsigned int     rq_ch_dummy_0:32;
}DC_PHY_FIFO_ARB_24;

typedef struct 
{
unsigned int     rq_ch_st0:32;
}DC_PHY_FIFO_ARB_25;

typedef struct 
{
unsigned int     rq_ch_st1:32;
}DC_PHY_FIFO_ARB_26;

typedef struct 
{
unsigned int     rq_ch_st2:32;
}DC_PHY_FIFO_ARB_27;

typedef struct 
{
unsigned int     rq_ch_st3:32;
}DC_PHY_FIFO_ARB_28;

typedef struct 
{
unsigned int     dummy_0:32;
}DC_PHY_DUMMY_0;

typedef struct 
{
unsigned int     dummy_1:32;
}DC_PHY_DUMMY_1;

typedef struct 
{
unsigned int     dummy_2:32;
}DC_PHY_DUMMY_2;

typedef struct 
{
unsigned int     dummy_3:32;
}DC_PHY_DUMMY_3;

typedef struct 
{
unsigned int     dummy_4:32;
}DC_PHY_DUMMY_4;

typedef struct 
{
unsigned int     dummy_5:32;
}DC_PHY_DUMMY_5;

typedef struct 
{
unsigned int     dummy_6:32;
}DC_PHY_DUMMY_6;

typedef struct 
{
unsigned int     dummy_7:32;
}DC_PHY_DUMMY_7;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sc_en:1;
}DC_PHY_SC_CTRL;

typedef struct 
{
unsigned int     sc_key_1:16;
unsigned int     sc_key_0:16;
}DC_PHY_SC_KEY01;

typedef struct 
{
unsigned int     sc_key_3:16;
unsigned int     sc_key_2:16;
}DC_PHY_SC_KEY23;

typedef struct 
{
unsigned int     sc_key_5:16;
unsigned int     sc_key_4:16;
}DC_PHY_SC_KEY45;

typedef struct 
{
unsigned int     sc_key_7:16;
unsigned int     sc_key_6:16;
}DC_PHY_SC_KEY67;

typedef struct 
{
unsigned int     sc_key_9:16;
unsigned int     sc_key_8:16;
}DC_PHY_SC_KEY89;

typedef struct 
{
unsigned int     sc_key_b:16;
unsigned int     sc_key_a:16;
}DC_PHY_SC_KEYAB;

typedef struct 
{
unsigned int     sc_key_d:16;
unsigned int     sc_key_c:16;
}DC_PHY_SC_KEYCD;

typedef struct 
{
unsigned int     sc_key_f:16;
unsigned int     sc_key_e:16;
}DC_PHY_SC_KEYEF;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     issue_cmd_dly_1T:1;
}DC_PHY_CMD_DLY_1T;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     write_merge_en:1;
unsigned int     read_bypass_en:1;
}DC_PHY_EXP_LANE_CTRL;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     bank2_dlyn:3;
unsigned int     bank1_dlyn:3;
unsigned int     bank0_dlyn:3;
unsigned int     odt_dlyn:3;
unsigned int     cke_dlyn:3;
unsigned int     we_n_dlyn:3;
unsigned int     cas_n_dlyn:3;
unsigned int     ras_n_dlyn:3;
unsigned int     cs_n_dlyn:3;
}DC_PHY_CMD_DLYN_0;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     adr09_dlyn:3;
unsigned int     adr08_dlyn:3;
unsigned int     adr07_dlyn:3;
unsigned int     adr06_dlyn:3;
unsigned int     adr05_dlyn:3;
unsigned int     adr04_dlyn:3;
unsigned int     adr03_dlyn:3;
unsigned int     adr02_dlyn:3;
unsigned int     adr01_dlyn:3;
unsigned int     adr00_dlyn:3;
}DC_PHY_ADR_DLYN_0;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     adr5_ext_dlyn:3;
unsigned int     adr4_ext_dlyn:3;
unsigned int     adr15_dlyn:3;
unsigned int     adr14_dlyn:3;
unsigned int     adr13_dlyn:3;
unsigned int     adr12_dlyn:3;
unsigned int     adr11_dlyn:3;
unsigned int     adr10_dlyn:3;
}DC_PHY_ADR_DLYN_1;

typedef struct 
{
unsigned int     tota_mon_num:32;
}DC_PHY_SCPU_PC_TOTA_MON_NUM;

typedef struct 
{
unsigned int     tota_ack_num:32;
}DC_PHY_SCPU_PC_TOTA_ACK_NUM;

typedef struct 
{
unsigned int     tota_idl_num:32;
}DC_PHY_SCPU_PC_TOTA_IDL_NUM;

typedef struct 
{
unsigned int     acc_lat:32;
}DC_PHY_SCPU_PC_ACC_LAT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     max_lat:16;
}DC_PHY_SCPU_PC_MAX_LAT;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     req_num:24;
}DC_PHY_SCPU_PC_REQ_NUM;

typedef struct 
{
unsigned int     ack_num:32;
}DC_PHY_SCPU_PC_ACK_NUM;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     pc_go:1;
}DC_PHY_SCPU_PC_CTRL;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     gck_ext_cyc:6;
unsigned int     reserved_1:5;
unsigned int     par_gck_en:1;
unsigned int     fsm_gck_en:1;
unsigned int     ioblk_gck_en:1;
}DC_PHY_GCK_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     enable:1;
}DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0;

typedef struct 
{
unsigned int     timer_threshold:32;
}DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     count_threshold:24;
}DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     merge_num:24;
}DC_PHY_SCPU_PC_MERGE_NUM;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     wr_req_num:24;
}DC_PHY_SCPU_PC_WR_REQ_NUM;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     data_in:20;
unsigned int     reserved_1:2;
unsigned int     data_in_ready:1;
unsigned int     wire_sel:1;
unsigned int     ro_sel:3;
unsigned int     dss_rst_n:1;
}DC_PHY_SPEED_SENSOR_CTRL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     count_out:20;
unsigned int     reserved_1:2;
unsigned int     wsort_go:1;
unsigned int     ready:1;
}DC_PHY_SPEED_SENSOR_STATUS;

typedef struct 
{
unsigned int     ctrl_misc:32;
}DC_PHY_EXPRESS_LANE_CTRL_MISC;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     data_in:20;
unsigned int     reserved_1:2;
unsigned int     speed_en:1;
unsigned int     wire_sel:1;
unsigned int     ro_sel:3;
unsigned int     dss_rst_n:1;
}DC_PHY_DSS_C35_MISC;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     count_out:20;
unsigned int     reserved_1:2;
unsigned int     wsort_go:1;
unsigned int     ready:1;
}DC_PHY_DSS_C35_ST;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     data_in:20;
unsigned int     reserved_1:2;
unsigned int     speed_en:1;
unsigned int     wire_sel:1;
unsigned int     ro_sel:3;
unsigned int     dss_rst_n:1;
}DC_PHY_DSS_C35D5_MISC;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     count_out:20;
unsigned int     reserved_1:2;
unsigned int     wsort_go:1;
unsigned int     ready:1;
}DC_PHY_DSS_C35D5_ST;

typedef struct 
{
unsigned int     dbgo_c35d5:16;
unsigned int     dbgo_c35:16;
}DC_PHY_DSS_DBG;

#endif

#define DC_PHY_TMCTRL0                                                               0x18008800
#define DC_PHY_TMCTRL0_reg_addr                                                      "0xB8008800"
#define DC_PHY_TMCTRL0_reg                                                           0xB8008800
#define set_DC_PHY_TMCTRL0_reg(data)   (*((volatile unsigned int*) DC_PHY_TMCTRL0_reg)=data)
#define get_DC_PHY_TMCTRL0_reg   (*((volatile unsigned int*) DC_PHY_TMCTRL0_reg))
#define DC_PHY_TMCTRL0_inst_adr                                                      "0x0000"
#define DC_PHY_TMCTRL0_inst                                                          0x0000
#define DC_PHY_TMCTRL0_tmras_shift                                                   (16)
#define DC_PHY_TMCTRL0_tmras_mask                                                    (0x01FF0000)
#define DC_PHY_TMCTRL0_tmras(data)                                                   (0x01FF0000&((data)<<16))
#define DC_PHY_TMCTRL0_tmras_src(data)                                               ((0x01FF0000&(data))>>16)
#define DC_PHY_TMCTRL0_get_tmras(data)                                               ((0x01FF0000&(data))>>16)
#define DC_PHY_TMCTRL0_tmrcl_shift                                                   (12)
#define DC_PHY_TMCTRL0_tmrcl_mask                                                    (0x0000F000)
#define DC_PHY_TMCTRL0_tmrcl(data)                                                   (0x0000F000&((data)<<12))
#define DC_PHY_TMCTRL0_tmrcl_src(data)                                               ((0x0000F000&(data))>>12)
#define DC_PHY_TMCTRL0_get_tmrcl(data)                                               ((0x0000F000&(data))>>12)
#define DC_PHY_TMCTRL0_tmcl_shift                                                    (8)
#define DC_PHY_TMCTRL0_tmcl_mask                                                     (0x00000F00)
#define DC_PHY_TMCTRL0_tmcl(data)                                                    (0x00000F00&((data)<<8))
#define DC_PHY_TMCTRL0_tmcl_src(data)                                                ((0x00000F00&(data))>>8)
#define DC_PHY_TMCTRL0_get_tmcl(data)                                                ((0x00000F00&(data))>>8)
#define DC_PHY_TMCTRL0_tmcl_rd_shift                                                 (0)
#define DC_PHY_TMCTRL0_tmcl_rd_mask                                                  (0x0000007F)
#define DC_PHY_TMCTRL0_tmcl_rd(data)                                                 (0x0000007F&((data)<<0))
#define DC_PHY_TMCTRL0_tmcl_rd_src(data)                                             ((0x0000007F&(data))>>0)
#define DC_PHY_TMCTRL0_get_tmcl_rd(data)                                             ((0x0000007F&(data))>>0)


#define DC_PHY_TMCTRL1                                                               0x18008804
#define DC_PHY_TMCTRL1_reg_addr                                                      "0xB8008804"
#define DC_PHY_TMCTRL1_reg                                                           0xB8008804
#define set_DC_PHY_TMCTRL1_reg(data)   (*((volatile unsigned int*) DC_PHY_TMCTRL1_reg)=data)
#define get_DC_PHY_TMCTRL1_reg   (*((volatile unsigned int*) DC_PHY_TMCTRL1_reg))
#define DC_PHY_TMCTRL1_inst_adr                                                      "0x0001"
#define DC_PHY_TMCTRL1_inst                                                          0x0001
#define DC_PHY_TMCTRL1_tmrrd_shift                                                   (24)
#define DC_PHY_TMCTRL1_tmrrd_mask                                                    (0x1F000000)
#define DC_PHY_TMCTRL1_tmrrd(data)                                                   (0x1F000000&((data)<<24))
#define DC_PHY_TMCTRL1_tmrrd_src(data)                                               ((0x1F000000&(data))>>24)
#define DC_PHY_TMCTRL1_get_tmrrd(data)                                               ((0x1F000000&(data))>>24)
#define DC_PHY_TMCTRL1_tmrp_shift                                                    (16)
#define DC_PHY_TMCTRL1_tmrp_mask                                                     (0x003F0000)
#define DC_PHY_TMCTRL1_tmrp(data)                                                    (0x003F0000&((data)<<16))
#define DC_PHY_TMCTRL1_tmrp_src(data)                                                ((0x003F0000&(data))>>16)
#define DC_PHY_TMCTRL1_get_tmrp(data)                                                ((0x003F0000&(data))>>16)
#define DC_PHY_TMCTRL1_tmrcd_shift                                                   (8)
#define DC_PHY_TMCTRL1_tmrcd_mask                                                    (0x00003F00)
#define DC_PHY_TMCTRL1_tmrcd(data)                                                   (0x00003F00&((data)<<8))
#define DC_PHY_TMCTRL1_tmrcd_src(data)                                               ((0x00003F00&(data))>>8)
#define DC_PHY_TMCTRL1_get_tmrcd(data)                                               ((0x00003F00&(data))>>8)
#define DC_PHY_TMCTRL1_tmrc_shift                                                    (0)
#define DC_PHY_TMCTRL1_tmrc_mask                                                     (0x000000FF)
#define DC_PHY_TMCTRL1_tmrc(data)                                                    (0x000000FF&((data)<<0))
#define DC_PHY_TMCTRL1_tmrc_src(data)                                                ((0x000000FF&(data))>>0)
#define DC_PHY_TMCTRL1_get_tmrc(data)                                                ((0x000000FF&(data))>>0)


#define DC_PHY_TMCTRL2                                                               0x18008808
#define DC_PHY_TMCTRL2_reg_addr                                                      "0xB8008808"
#define DC_PHY_TMCTRL2_reg                                                           0xB8008808
#define set_DC_PHY_TMCTRL2_reg(data)   (*((volatile unsigned int*) DC_PHY_TMCTRL2_reg)=data)
#define get_DC_PHY_TMCTRL2_reg   (*((volatile unsigned int*) DC_PHY_TMCTRL2_reg))
#define DC_PHY_TMCTRL2_inst_adr                                                      "0x0002"
#define DC_PHY_TMCTRL2_inst                                                          0x0002
#define DC_PHY_TMCTRL2_tmrtw_shift                                                   (30)
#define DC_PHY_TMCTRL2_tmrtw_mask                                                    (0xC0000000)
#define DC_PHY_TMCTRL2_tmrtw(data)                                                   (0xC0000000&((data)<<30))
#define DC_PHY_TMCTRL2_tmrtw_src(data)                                               ((0xC0000000&(data))>>30)
#define DC_PHY_TMCTRL2_get_tmrtw(data)                                               ((0xC0000000&(data))>>30)
#define DC_PHY_TMCTRL2_tmccd_shift                                                   (24)
#define DC_PHY_TMCTRL2_tmccd_mask                                                    (0x1F000000)
#define DC_PHY_TMCTRL2_tmccd(data)                                                   (0x1F000000&((data)<<24))
#define DC_PHY_TMCTRL2_tmccd_src(data)                                               ((0x1F000000&(data))>>24)
#define DC_PHY_TMCTRL2_get_tmccd(data)                                               ((0x1F000000&(data))>>24)
#define DC_PHY_TMCTRL2_trtp_shift                                                    (16)
#define DC_PHY_TMCTRL2_trtp_mask                                                     (0x007F0000)
#define DC_PHY_TMCTRL2_trtp(data)                                                    (0x007F0000&((data)<<16))
#define DC_PHY_TMCTRL2_trtp_src(data)                                                ((0x007F0000&(data))>>16)
#define DC_PHY_TMCTRL2_get_trtp(data)                                                ((0x007F0000&(data))>>16)
#define DC_PHY_TMCTRL2_tmwtr_shift                                                   (8)
#define DC_PHY_TMCTRL2_tmwtr_mask                                                    (0x00001F00)
#define DC_PHY_TMCTRL2_tmwtr(data)                                                   (0x00001F00&((data)<<8))
#define DC_PHY_TMCTRL2_tmwtr_src(data)                                               ((0x00001F00&(data))>>8)
#define DC_PHY_TMCTRL2_get_tmwtr(data)                                               ((0x00001F00&(data))>>8)
#define DC_PHY_TMCTRL2_tmwr_shift                                                    (0)
#define DC_PHY_TMCTRL2_tmwr_mask                                                     (0x0000003F)
#define DC_PHY_TMCTRL2_tmwr(data)                                                    (0x0000003F&((data)<<0))
#define DC_PHY_TMCTRL2_tmwr_src(data)                                                ((0x0000003F&(data))>>0)
#define DC_PHY_TMCTRL2_get_tmwr(data)                                                ((0x0000003F&(data))>>0)


#define DC_PHY_TMCTRL3                                                               0x1800880c
#define DC_PHY_TMCTRL3_reg_addr                                                      "0xB800880C"
#define DC_PHY_TMCTRL3_reg                                                           0xB800880C
#define set_DC_PHY_TMCTRL3_reg(data)   (*((volatile unsigned int*) DC_PHY_TMCTRL3_reg)=data)
#define get_DC_PHY_TMCTRL3_reg   (*((volatile unsigned int*) DC_PHY_TMCTRL3_reg))
#define DC_PHY_TMCTRL3_inst_adr                                                      "0x0003"
#define DC_PHY_TMCTRL3_inst                                                          0x0003
#define DC_PHY_TMCTRL3_tmFAW_shift                                                   (24)
#define DC_PHY_TMCTRL3_tmFAW_mask                                                    (0xFF000000)
#define DC_PHY_TMCTRL3_tmFAW(data)                                                   (0xFF000000&((data)<<24))
#define DC_PHY_TMCTRL3_tmFAW_src(data)                                               ((0xFF000000&(data))>>24)
#define DC_PHY_TMCTRL3_get_tmFAW(data)                                               ((0xFF000000&(data))>>24)
#define DC_PHY_TMCTRL3_refcycle_shift                                                (12)
#define DC_PHY_TMCTRL3_refcycle_mask                                                 (0x003FF000)
#define DC_PHY_TMCTRL3_refcycle(data)                                                (0x003FF000&((data)<<12))
#define DC_PHY_TMCTRL3_refcycle_src(data)                                            ((0x003FF000&(data))>>12)
#define DC_PHY_TMCTRL3_get_refcycle(data)                                            ((0x003FF000&(data))>>12)
#define DC_PHY_TMCTRL3_tmrfc_shift                                                   (0)
#define DC_PHY_TMCTRL3_tmrfc_mask                                                    (0x000007FF)
#define DC_PHY_TMCTRL3_tmrfc(data)                                                   (0x000007FF&((data)<<0))
#define DC_PHY_TMCTRL3_tmrfc_src(data)                                               ((0x000007FF&(data))>>0)
#define DC_PHY_TMCTRL3_get_tmrfc(data)                                               ((0x000007FF&(data))>>0)


#define DC_PHY_TMCTRL4                                                               0x18008810
#define DC_PHY_TMCTRL4_reg_addr                                                      "0xB8008810"
#define DC_PHY_TMCTRL4_reg                                                           0xB8008810
#define set_DC_PHY_TMCTRL4_reg(data)   (*((volatile unsigned int*) DC_PHY_TMCTRL4_reg)=data)
#define get_DC_PHY_TMCTRL4_reg   (*((volatile unsigned int*) DC_PHY_TMCTRL4_reg))
#define DC_PHY_TMCTRL4_inst_adr                                                      "0x0004"
#define DC_PHY_TMCTRL4_inst                                                          0x0004
#define DC_PHY_TMCTRL4_tAOND_shift                                                   (24)
#define DC_PHY_TMCTRL4_tAOND_mask                                                    (0x3F000000)
#define DC_PHY_TMCTRL4_tAOND(data)                                                   (0x3F000000&((data)<<24))
#define DC_PHY_TMCTRL4_tAOND_src(data)                                               ((0x3F000000&(data))>>24)
#define DC_PHY_TMCTRL4_get_tAOND(data)                                               ((0x3F000000&(data))>>24)
#define DC_PHY_TMCTRL4_tAOFD_shift                                                   (16)
#define DC_PHY_TMCTRL4_tAOFD_mask                                                    (0x003F0000)
#define DC_PHY_TMCTRL4_tAOFD(data)                                                   (0x003F0000&((data)<<16))
#define DC_PHY_TMCTRL4_tAOFD_src(data)                                               ((0x003F0000&(data))>>16)
#define DC_PHY_TMCTRL4_get_tAOFD(data)                                               ((0x003F0000&(data))>>16)
#define DC_PHY_TMCTRL4_tmmod_shift                                                   (8)
#define DC_PHY_TMCTRL4_tmmod_mask                                                    (0x0000FF00)
#define DC_PHY_TMCTRL4_tmmod(data)                                                   (0x0000FF00&((data)<<8))
#define DC_PHY_TMCTRL4_tmmod_src(data)                                               ((0x0000FF00&(data))>>8)
#define DC_PHY_TMCTRL4_get_tmmod(data)                                               ((0x0000FF00&(data))>>8)
#define DC_PHY_TMCTRL4_tmmrd_shift                                                   (0)
#define DC_PHY_TMCTRL4_tmmrd_mask                                                    (0x0000001F)
#define DC_PHY_TMCTRL4_tmmrd(data)                                                   (0x0000001F&((data)<<0))
#define DC_PHY_TMCTRL4_tmmrd_src(data)                                               ((0x0000001F&(data))>>0)
#define DC_PHY_TMCTRL4_get_tmmrd(data)                                               ((0x0000001F&(data))>>0)


#define DC_PHY_TMCTRL5                                                               0x18008814
#define DC_PHY_TMCTRL5_reg_addr                                                      "0xB8008814"
#define DC_PHY_TMCTRL5_reg                                                           0xB8008814
#define set_DC_PHY_TMCTRL5_reg(data)   (*((volatile unsigned int*) DC_PHY_TMCTRL5_reg)=data)
#define get_DC_PHY_TMCTRL5_reg   (*((volatile unsigned int*) DC_PHY_TMCTRL5_reg))
#define DC_PHY_TMCTRL5_inst_adr                                                      "0x0005"
#define DC_PHY_TMCTRL5_inst                                                          0x0005
#define DC_PHY_TMCTRL5_tzqoper_shift                                                 (12)
#define DC_PHY_TMCTRL5_tzqoper_mask                                                  (0x00FFF000)
#define DC_PHY_TMCTRL5_tzqoper(data)                                                 (0x00FFF000&((data)<<12))
#define DC_PHY_TMCTRL5_tzqoper_src(data)                                             ((0x00FFF000&(data))>>12)
#define DC_PHY_TMCTRL5_get_tzqoper(data)                                             ((0x00FFF000&(data))>>12)
#define DC_PHY_TMCTRL5_tzqinit_shift                                                 (0)
#define DC_PHY_TMCTRL5_tzqinit_mask                                                  (0x00000FFF)
#define DC_PHY_TMCTRL5_tzqinit(data)                                                 (0x00000FFF&((data)<<0))
#define DC_PHY_TMCTRL5_tzqinit_src(data)                                             ((0x00000FFF&(data))>>0)
#define DC_PHY_TMCTRL5_get_tzqinit(data)                                             ((0x00000FFF&(data))>>0)


#define DC_PHY_TMCTRL6                                                               0x18008818
#define DC_PHY_TMCTRL6_reg_addr                                                      "0xB8008818"
#define DC_PHY_TMCTRL6_reg                                                           0xB8008818
#define set_DC_PHY_TMCTRL6_reg(data)   (*((volatile unsigned int*) DC_PHY_TMCTRL6_reg)=data)
#define get_DC_PHY_TMCTRL6_reg   (*((volatile unsigned int*) DC_PHY_TMCTRL6_reg))
#define DC_PHY_TMCTRL6_inst_adr                                                      "0x0006"
#define DC_PHY_TMCTRL6_inst                                                          0x0006
#define DC_PHY_TMCTRL6_tdllk_shift                                                   (12)
#define DC_PHY_TMCTRL6_tdllk_mask                                                    (0x00FFF000)
#define DC_PHY_TMCTRL6_tdllk(data)                                                   (0x00FFF000&((data)<<12))
#define DC_PHY_TMCTRL6_tdllk_src(data)                                               ((0x00FFF000&(data))>>12)
#define DC_PHY_TMCTRL6_get_tdllk(data)                                               ((0x00FFF000&(data))>>12)
#define DC_PHY_TMCTRL6_tzqcs_shift                                                   (0)
#define DC_PHY_TMCTRL6_tzqcs_mask                                                    (0x00000FFF)
#define DC_PHY_TMCTRL6_tzqcs(data)                                                   (0x00000FFF&((data)<<0))
#define DC_PHY_TMCTRL6_tzqcs_src(data)                                               ((0x00000FFF&(data))>>0)
#define DC_PHY_TMCTRL6_get_tzqcs(data)                                               ((0x00000FFF&(data))>>0)


#define DC_PHY_ODT_CTRL                                                              0x18008820
#define DC_PHY_ODT_CTRL_reg_addr                                                     "0xB8008820"
#define DC_PHY_ODT_CTRL_reg                                                          0xB8008820
#define set_DC_PHY_ODT_CTRL_reg(data)   (*((volatile unsigned int*) DC_PHY_ODT_CTRL_reg)=data)
#define get_DC_PHY_ODT_CTRL_reg   (*((volatile unsigned int*) DC_PHY_ODT_CTRL_reg))
#define DC_PHY_ODT_CTRL_inst_adr                                                     "0x0008"
#define DC_PHY_ODT_CTRL_inst                                                         0x0008
#define DC_PHY_ODT_CTRL_ddr3_odt_dly_1T_shift                                        (28)
#define DC_PHY_ODT_CTRL_ddr3_odt_dly_1T_mask                                         (0x10000000)
#define DC_PHY_ODT_CTRL_ddr3_odt_dly_1T(data)                                        (0x10000000&((data)<<28))
#define DC_PHY_ODT_CTRL_ddr3_odt_dly_1T_src(data)                                    ((0x10000000&(data))>>28)
#define DC_PHY_ODT_CTRL_get_ddr3_odt_dly_1T(data)                                    ((0x10000000&(data))>>28)
#define DC_PHY_ODT_CTRL_ddr3_odt_ext_1T_shift                                        (27)
#define DC_PHY_ODT_CTRL_ddr3_odt_ext_1T_mask                                         (0x08000000)
#define DC_PHY_ODT_CTRL_ddr3_odt_ext_1T(data)                                        (0x08000000&((data)<<27))
#define DC_PHY_ODT_CTRL_ddr3_odt_ext_1T_src(data)                                    ((0x08000000&(data))>>27)
#define DC_PHY_ODT_CTRL_get_ddr3_odt_ext_1T(data)                                    ((0x08000000&(data))>>27)
#define DC_PHY_ODT_CTRL_ctrl_odt_en_shift                                            (26)
#define DC_PHY_ODT_CTRL_ctrl_odt_en_mask                                             (0x04000000)
#define DC_PHY_ODT_CTRL_ctrl_odt_en(data)                                            (0x04000000&((data)<<26))
#define DC_PHY_ODT_CTRL_ctrl_odt_en_src(data)                                        ((0x04000000&(data))>>26)
#define DC_PHY_ODT_CTRL_get_ctrl_odt_en(data)                                        ((0x04000000&(data))>>26)
#define DC_PHY_ODT_CTRL_mars_odt_force_sel_shift                                     (25)
#define DC_PHY_ODT_CTRL_mars_odt_force_sel_mask                                      (0x02000000)
#define DC_PHY_ODT_CTRL_mars_odt_force_sel(data)                                     (0x02000000&((data)<<25))
#define DC_PHY_ODT_CTRL_mars_odt_force_sel_src(data)                                 ((0x02000000&(data))>>25)
#define DC_PHY_ODT_CTRL_get_mars_odt_force_sel(data)                                 ((0x02000000&(data))>>25)
#define DC_PHY_ODT_CTRL_mars_odt_force_sig_shift                                     (24)
#define DC_PHY_ODT_CTRL_mars_odt_force_sig_mask                                      (0x01000000)
#define DC_PHY_ODT_CTRL_mars_odt_force_sig(data)                                     (0x01000000&((data)<<24))
#define DC_PHY_ODT_CTRL_mars_odt_force_sig_src(data)                                 ((0x01000000&(data))>>24)
#define DC_PHY_ODT_CTRL_get_mars_odt_force_sig(data)                                 ((0x01000000&(data))>>24)
#define DC_PHY_ODT_CTRL_odt_force_sel_shift                                          (23)
#define DC_PHY_ODT_CTRL_odt_force_sel_mask                                           (0x00800000)
#define DC_PHY_ODT_CTRL_odt_force_sel(data)                                          (0x00800000&((data)<<23))
#define DC_PHY_ODT_CTRL_odt_force_sel_src(data)                                      ((0x00800000&(data))>>23)
#define DC_PHY_ODT_CTRL_get_odt_force_sel(data)                                      ((0x00800000&(data))>>23)
#define DC_PHY_ODT_CTRL_odt_force_sig_shift                                          (22)
#define DC_PHY_ODT_CTRL_odt_force_sig_mask                                           (0x00400000)
#define DC_PHY_ODT_CTRL_odt_force_sig(data)                                          (0x00400000&((data)<<22))
#define DC_PHY_ODT_CTRL_odt_force_sig_src(data)                                      ((0x00400000&(data))>>22)
#define DC_PHY_ODT_CTRL_get_odt_force_sig(data)                                      ((0x00400000&(data))>>22)
#define DC_PHY_ODT_CTRL_odt_en_shift                                                 (21)
#define DC_PHY_ODT_CTRL_odt_en_mask                                                  (0x00200000)
#define DC_PHY_ODT_CTRL_odt_en(data)                                                 (0x00200000&((data)<<21))
#define DC_PHY_ODT_CTRL_odt_en_src(data)                                             ((0x00200000&(data))>>21)
#define DC_PHY_ODT_CTRL_get_odt_en(data)                                             ((0x00200000&(data))>>21)
#define DC_PHY_ODT_CTRL_odt_dis_shift                                                (20)
#define DC_PHY_ODT_CTRL_odt_dis_mask                                                 (0x00100000)
#define DC_PHY_ODT_CTRL_odt_dis(data)                                                (0x00100000&((data)<<20))
#define DC_PHY_ODT_CTRL_odt_dis_src(data)                                            ((0x00100000&(data))>>20)
#define DC_PHY_ODT_CTRL_get_odt_dis(data)                                            ((0x00100000&(data))>>20)
#define DC_PHY_ODT_CTRL_odt_en_lat_shift                                             (0)
#define DC_PHY_ODT_CTRL_odt_en_lat_mask                                              (0x00007FFF)
#define DC_PHY_ODT_CTRL_odt_en_lat(data)                                             (0x00007FFF&((data)<<0))
#define DC_PHY_ODT_CTRL_odt_en_lat_src(data)                                         ((0x00007FFF&(data))>>0)
#define DC_PHY_ODT_CTRL_get_odt_en_lat(data)                                         ((0x00007FFF&(data))>>0)


#define DC_PHY_CAL_CTRL2                                                             0x18008824
#define DC_PHY_CAL_CTRL2_reg_addr                                                    "0xB8008824"
#define DC_PHY_CAL_CTRL2_reg                                                         0xB8008824
#define set_DC_PHY_CAL_CTRL2_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL_CTRL2_reg)=data)
#define get_DC_PHY_CAL_CTRL2_reg   (*((volatile unsigned int*) DC_PHY_CAL_CTRL2_reg))
#define DC_PHY_CAL_CTRL2_inst_adr                                                    "0x0009"
#define DC_PHY_CAL_CTRL2_inst                                                        0x0009
#define DC_PHY_CAL_CTRL2_cal_rang_shift                                              (8)
#define DC_PHY_CAL_CTRL2_cal_rang_mask                                               (0x00003F00)
#define DC_PHY_CAL_CTRL2_cal_rang(data)                                              (0x00003F00&((data)<<8))
#define DC_PHY_CAL_CTRL2_cal_rang_src(data)                                          ((0x00003F00&(data))>>8)
#define DC_PHY_CAL_CTRL2_get_cal_rang(data)                                          ((0x00003F00&(data))>>8)
#define DC_PHY_CAL_CTRL2_cal_per_shift                                               (0)
#define DC_PHY_CAL_CTRL2_cal_per_mask                                                (0x000000FF)
#define DC_PHY_CAL_CTRL2_cal_per(data)                                               (0x000000FF&((data)<<0))
#define DC_PHY_CAL_CTRL2_cal_per_src(data)                                           ((0x000000FF&(data))>>0)
#define DC_PHY_CAL_CTRL2_get_cal_per(data)                                           ((0x000000FF&(data))>>0)


#define DC_PHY_DC_MIS2                                                               0x18008828
#define DC_PHY_DC_MIS2_reg_addr                                                      "0xB8008828"
#define DC_PHY_DC_MIS2_reg                                                           0xB8008828
#define set_DC_PHY_DC_MIS2_reg(data)   (*((volatile unsigned int*) DC_PHY_DC_MIS2_reg)=data)
#define get_DC_PHY_DC_MIS2_reg   (*((volatile unsigned int*) DC_PHY_DC_MIS2_reg))
#define DC_PHY_DC_MIS2_inst_adr                                                      "0x000A"
#define DC_PHY_DC_MIS2_inst                                                          0x000A
#define DC_PHY_DC_MIS2_exe_cal_shift                                                 (5)
#define DC_PHY_DC_MIS2_exe_cal_mask                                                  (0x00000020)
#define DC_PHY_DC_MIS2_exe_cal(data)                                                 (0x00000020&((data)<<5))
#define DC_PHY_DC_MIS2_exe_cal_src(data)                                             ((0x00000020&(data))>>5)
#define DC_PHY_DC_MIS2_get_exe_cal(data)                                             ((0x00000020&(data))>>5)
#define DC_PHY_DC_MIS2_init_shift                                                    (4)
#define DC_PHY_DC_MIS2_init_mask                                                     (0x00000010)
#define DC_PHY_DC_MIS2_init(data)                                                    (0x00000010&((data)<<4))
#define DC_PHY_DC_MIS2_init_src(data)                                                ((0x00000010&(data))>>4)
#define DC_PHY_DC_MIS2_get_init(data)                                                ((0x00000010&(data))>>4)
#define DC_PHY_DC_MIS2_sren_shift                                                    (3)
#define DC_PHY_DC_MIS2_sren_mask                                                     (0x00000008)
#define DC_PHY_DC_MIS2_sren(data)                                                    (0x00000008&((data)<<3))
#define DC_PHY_DC_MIS2_sren_src(data)                                                ((0x00000008&(data))>>3)
#define DC_PHY_DC_MIS2_get_sren(data)                                                ((0x00000008&(data))>>3)
#define DC_PHY_DC_MIS2_srex_shift                                                    (2)
#define DC_PHY_DC_MIS2_srex_mask                                                     (0x00000004)
#define DC_PHY_DC_MIS2_srex(data)                                                    (0x00000004&((data)<<2))
#define DC_PHY_DC_MIS2_srex_src(data)                                                ((0x00000004&(data))>>2)
#define DC_PHY_DC_MIS2_get_srex(data)                                                ((0x00000004&(data))>>2)
#define DC_PHY_DC_MIS2_exe_emr_shift                                                 (1)
#define DC_PHY_DC_MIS2_exe_emr_mask                                                  (0x00000002)
#define DC_PHY_DC_MIS2_exe_emr(data)                                                 (0x00000002&((data)<<1))
#define DC_PHY_DC_MIS2_exe_emr_src(data)                                             ((0x00000002&(data))>>1)
#define DC_PHY_DC_MIS2_get_exe_emr(data)                                             ((0x00000002&(data))>>1)
#define DC_PHY_DC_MIS2_exe_mr_shift                                                  (0)
#define DC_PHY_DC_MIS2_exe_mr_mask                                                   (0x00000001)
#define DC_PHY_DC_MIS2_exe_mr(data)                                                  (0x00000001&((data)<<0))
#define DC_PHY_DC_MIS2_exe_mr_src(data)                                              ((0x00000001&(data))>>0)
#define DC_PHY_DC_MIS2_get_exe_mr(data)                                              ((0x00000001&(data))>>0)


#define DC_PHY_DC_MIS                                                                0x1800882c
#define DC_PHY_DC_MIS_reg_addr                                                       "0xB800882C"
#define DC_PHY_DC_MIS_reg                                                            0xB800882C
#define set_DC_PHY_DC_MIS_reg(data)   (*((volatile unsigned int*) DC_PHY_DC_MIS_reg)=data)
#define get_DC_PHY_DC_MIS_reg   (*((volatile unsigned int*) DC_PHY_DC_MIS_reg))
#define DC_PHY_DC_MIS_inst_adr                                                       "0x000B"
#define DC_PHY_DC_MIS_inst                                                           0x000B
#define DC_PHY_DC_MIS_rcd_not_eq_shift                                               (20)
#define DC_PHY_DC_MIS_rcd_not_eq_mask                                                (0x00100000)
#define DC_PHY_DC_MIS_rcd_not_eq(data)                                               (0x00100000&((data)<<20))
#define DC_PHY_DC_MIS_rcd_not_eq_src(data)                                           ((0x00100000&(data))>>20)
#define DC_PHY_DC_MIS_get_rcd_not_eq(data)                                           ((0x00100000&(data))>>20)
#define DC_PHY_DC_MIS_tmrcdwr_shift                                                  (16)
#define DC_PHY_DC_MIS_tmrcdwr_mask                                                   (0x000F0000)
#define DC_PHY_DC_MIS_tmrcdwr(data)                                                  (0x000F0000&((data)<<16))
#define DC_PHY_DC_MIS_tmrcdwr_src(data)                                              ((0x000F0000&(data))>>16)
#define DC_PHY_DC_MIS_get_tmrcdwr(data)                                              ((0x000F0000&(data))>>16)
#define DC_PHY_DC_MIS_tmrp_all_add_shift                                             (14)
#define DC_PHY_DC_MIS_tmrp_all_add_mask                                              (0x0000C000)
#define DC_PHY_DC_MIS_tmrp_all_add(data)                                             (0x0000C000&((data)<<14))
#define DC_PHY_DC_MIS_tmrp_all_add_src(data)                                         ((0x0000C000&(data))>>14)
#define DC_PHY_DC_MIS_get_tmrp_all_add(data)                                         ((0x0000C000&(data))>>14)
#define DC_PHY_DC_MIS_ap_wo_min_dly_shift                                            (13)
#define DC_PHY_DC_MIS_ap_wo_min_dly_mask                                             (0x00002000)
#define DC_PHY_DC_MIS_ap_wo_min_dly(data)                                            (0x00002000&((data)<<13))
#define DC_PHY_DC_MIS_ap_wo_min_dly_src(data)                                        ((0x00002000&(data))>>13)
#define DC_PHY_DC_MIS_get_ap_wo_min_dly(data)                                        ((0x00002000&(data))>>13)
#define DC_PHY_DC_MIS_add_ht_shift                                                   (12)
#define DC_PHY_DC_MIS_add_ht_mask                                                    (0x00001000)
#define DC_PHY_DC_MIS_add_ht(data)                                                   (0x00001000&((data)<<12))
#define DC_PHY_DC_MIS_add_ht_src(data)                                               ((0x00001000&(data))>>12)
#define DC_PHY_DC_MIS_get_add_ht(data)                                               ((0x00001000&(data))>>12)
#define DC_PHY_DC_MIS_ddr3_shift                                                     (0)
#define DC_PHY_DC_MIS_ddr3_mask                                                      (0x00000001)
#define DC_PHY_DC_MIS_ddr3(data)                                                     (0x00000001&((data)<<0))
#define DC_PHY_DC_MIS_ddr3_src(data)                                                 ((0x00000001&(data))>>0)
#define DC_PHY_DC_MIS_get_ddr3(data)                                                 ((0x00000001&(data))>>0)


#define DC_PHY_DC_MISA                                                               0x18008830
#define DC_PHY_DC_MISA_reg_addr                                                      "0xB8008830"
#define DC_PHY_DC_MISA_reg                                                           0xB8008830
#define set_DC_PHY_DC_MISA_reg(data)   (*((volatile unsigned int*) DC_PHY_DC_MISA_reg)=data)
#define get_DC_PHY_DC_MISA_reg   (*((volatile unsigned int*) DC_PHY_DC_MISA_reg))
#define DC_PHY_DC_MISA_inst_adr                                                      "0x000C"
#define DC_PHY_DC_MISA_inst                                                          0x000C
#define DC_PHY_DC_MISA_pre_dis_shift                                                 (12)
#define DC_PHY_DC_MISA_pre_dis_mask                                                  (0x00001000)
#define DC_PHY_DC_MISA_pre_dis(data)                                                 (0x00001000&((data)<<12))
#define DC_PHY_DC_MISA_pre_dis_src(data)                                             ((0x00001000&(data))>>12)
#define DC_PHY_DC_MISA_get_pre_dis(data)                                             ((0x00001000&(data))>>12)
#define DC_PHY_DC_MISA_lbk_en_shift                                                  (2)
#define DC_PHY_DC_MISA_lbk_en_mask                                                   (0x00000004)
#define DC_PHY_DC_MISA_lbk_en(data)                                                  (0x00000004&((data)<<2))
#define DC_PHY_DC_MISA_lbk_en_src(data)                                              ((0x00000004&(data))>>2)
#define DC_PHY_DC_MISA_get_lbk_en(data)                                              ((0x00000004&(data))>>2)


#define DC_PHY_DC_MISB                                                               0x18008834
#define DC_PHY_DC_MISB_reg_addr                                                      "0xB8008834"
#define DC_PHY_DC_MISB_reg                                                           0xB8008834
#define set_DC_PHY_DC_MISB_reg(data)   (*((volatile unsigned int*) DC_PHY_DC_MISB_reg)=data)
#define get_DC_PHY_DC_MISB_reg   (*((volatile unsigned int*) DC_PHY_DC_MISB_reg))
#define DC_PHY_DC_MISB_inst_adr                                                      "0x000D"
#define DC_PHY_DC_MISB_inst                                                          0x000D
#define DC_PHY_DC_MISB_tmrc_sel_shift                                                (28)
#define DC_PHY_DC_MISB_tmrc_sel_mask                                                 (0x10000000)
#define DC_PHY_DC_MISB_tmrc_sel(data)                                                (0x10000000&((data)<<28))
#define DC_PHY_DC_MISB_tmrc_sel_src(data)                                            ((0x10000000&(data))>>28)
#define DC_PHY_DC_MISB_get_tmrc_sel(data)                                            ((0x10000000&(data))>>28)
#define DC_PHY_DC_MISB_cpu_rd_pri_shift                                              (13)
#define DC_PHY_DC_MISB_cpu_rd_pri_mask                                               (0x00006000)
#define DC_PHY_DC_MISB_cpu_rd_pri(data)                                              (0x00006000&((data)<<13))
#define DC_PHY_DC_MISB_cpu_rd_pri_src(data)                                          ((0x00006000&(data))>>13)
#define DC_PHY_DC_MISB_get_cpu_rd_pri(data)                                          ((0x00006000&(data))>>13)
#define DC_PHY_DC_MISB_cpu_wr_pri_shift                                              (11)
#define DC_PHY_DC_MISB_cpu_wr_pri_mask                                               (0x00001800)
#define DC_PHY_DC_MISB_cpu_wr_pri(data)                                              (0x00001800&((data)<<11))
#define DC_PHY_DC_MISB_cpu_wr_pri_src(data)                                          ((0x00001800&(data))>>11)
#define DC_PHY_DC_MISB_get_cpu_wr_pri(data)                                          ((0x00001800&(data))>>11)
#define DC_PHY_DC_MISB_en_rw_reord_shift                                             (10)
#define DC_PHY_DC_MISB_en_rw_reord_mask                                              (0x00000400)
#define DC_PHY_DC_MISB_en_rw_reord(data)                                             (0x00000400&((data)<<10))
#define DC_PHY_DC_MISB_en_rw_reord_src(data)                                         ((0x00000400&(data))>>10)
#define DC_PHY_DC_MISB_get_en_rw_reord(data)                                         ((0x00000400&(data))>>10)
#define DC_PHY_DC_MISB_en_cpu_wro_shift                                              (9)
#define DC_PHY_DC_MISB_en_cpu_wro_mask                                               (0x00000200)
#define DC_PHY_DC_MISB_en_cpu_wro(data)                                              (0x00000200&((data)<<9))
#define DC_PHY_DC_MISB_en_cpu_wro_src(data)                                          ((0x00000200&(data))>>9)
#define DC_PHY_DC_MISB_get_en_cpu_wro(data)                                          ((0x00000200&(data))>>9)
#define DC_PHY_DC_MISB_en_conflict_reord_shift                                       (8)
#define DC_PHY_DC_MISB_en_conflict_reord_mask                                        (0x00000100)
#define DC_PHY_DC_MISB_en_conflict_reord(data)                                       (0x00000100&((data)<<8))
#define DC_PHY_DC_MISB_en_conflict_reord_src(data)                                   ((0x00000100&(data))>>8)
#define DC_PHY_DC_MISB_get_en_conflict_reord(data)                                   ((0x00000100&(data))>>8)
#define DC_PHY_DC_MISB_en_cpu_reord_shift                                            (7)
#define DC_PHY_DC_MISB_en_cpu_reord_mask                                             (0x00000080)
#define DC_PHY_DC_MISB_en_cpu_reord(data)                                            (0x00000080&((data)<<7))
#define DC_PHY_DC_MISB_en_cpu_reord_src(data)                                        ((0x00000080&(data))>>7)
#define DC_PHY_DC_MISB_get_en_cpu_reord(data)                                        ((0x00000080&(data))>>7)
#define DC_PHY_DC_MISB_cpu_reord_thr_shift                                           (4)
#define DC_PHY_DC_MISB_cpu_reord_thr_mask                                            (0x00000070)
#define DC_PHY_DC_MISB_cpu_reord_thr(data)                                           (0x00000070&((data)<<4))
#define DC_PHY_DC_MISB_cpu_reord_thr_src(data)                                       ((0x00000070&(data))>>4)
#define DC_PHY_DC_MISB_get_cpu_reord_thr(data)                                       ((0x00000070&(data))>>4)
#define DC_PHY_DC_MISB_en_low_reord_shift                                            (3)
#define DC_PHY_DC_MISB_en_low_reord_mask                                             (0x00000008)
#define DC_PHY_DC_MISB_en_low_reord(data)                                            (0x00000008&((data)<<3))
#define DC_PHY_DC_MISB_en_low_reord_src(data)                                        ((0x00000008&(data))>>3)
#define DC_PHY_DC_MISB_get_en_low_reord(data)                                        ((0x00000008&(data))>>3)
#define DC_PHY_DC_MISB_dis_ap_cpu_shift                                              (2)
#define DC_PHY_DC_MISB_dis_ap_cpu_mask                                               (0x00000004)
#define DC_PHY_DC_MISB_dis_ap_cpu(data)                                              (0x00000004&((data)<<2))
#define DC_PHY_DC_MISB_dis_ap_cpu_src(data)                                          ((0x00000004&(data))>>2)
#define DC_PHY_DC_MISB_get_dis_ap_cpu(data)                                          ((0x00000004&(data))>>2)
#define DC_PHY_DC_MISB_dis_ap_cti_shift                                              (1)
#define DC_PHY_DC_MISB_dis_ap_cti_mask                                               (0x00000002)
#define DC_PHY_DC_MISB_dis_ap_cti(data)                                              (0x00000002&((data)<<1))
#define DC_PHY_DC_MISB_dis_ap_cti_src(data)                                          ((0x00000002&(data))>>1)
#define DC_PHY_DC_MISB_get_dis_ap_cti(data)                                          ((0x00000002&(data))>>1)
#define DC_PHY_DC_MISB_dis_ap_nor_shift                                              (0)
#define DC_PHY_DC_MISB_dis_ap_nor_mask                                               (0x00000001)
#define DC_PHY_DC_MISB_dis_ap_nor(data)                                              (0x00000001&((data)<<0))
#define DC_PHY_DC_MISB_dis_ap_nor_src(data)                                          ((0x00000001&(data))>>0)
#define DC_PHY_DC_MISB_get_dis_ap_nor(data)                                          ((0x00000001&(data))>>0)


#define DC_PHY_DC_MISC                                                               0x18008838
#define DC_PHY_DC_MISC_reg_addr                                                      "0xB8008838"
#define DC_PHY_DC_MISC_reg                                                           0xB8008838
#define set_DC_PHY_DC_MISC_reg(data)   (*((volatile unsigned int*) DC_PHY_DC_MISC_reg)=data)
#define get_DC_PHY_DC_MISC_reg   (*((volatile unsigned int*) DC_PHY_DC_MISC_reg))
#define DC_PHY_DC_MISC_inst_adr                                                      "0x000E"
#define DC_PHY_DC_MISC_inst                                                          0x000E
#define DC_PHY_DC_MISC_tap_2group_shift                                              (27)
#define DC_PHY_DC_MISC_tap_2group_mask                                               (0x08000000)
#define DC_PHY_DC_MISC_tap_2group(data)                                              (0x08000000&((data)<<27))
#define DC_PHY_DC_MISC_tap_2group_src(data)                                          ((0x08000000&(data))>>27)
#define DC_PHY_DC_MISC_get_tap_2group(data)                                          ((0x08000000&(data))>>27)
#define DC_PHY_DC_MISC_tap_mask_shift                                                (26)
#define DC_PHY_DC_MISC_tap_mask_mask                                                 (0x04000000)
#define DC_PHY_DC_MISC_tap_mask(data)                                                (0x04000000&((data)<<26))
#define DC_PHY_DC_MISC_tap_mask_src(data)                                            ((0x04000000&(data))>>26)
#define DC_PHY_DC_MISC_get_tap_mask(data)                                            ((0x04000000&(data))>>26)
#define DC_PHY_DC_MISC_fw_set_shift                                                  (25)
#define DC_PHY_DC_MISC_fw_set_mask                                                   (0x02000000)
#define DC_PHY_DC_MISC_fw_set(data)                                                  (0x02000000&((data)<<25))
#define DC_PHY_DC_MISC_fw_set_src(data)                                              ((0x02000000&(data))>>25)
#define DC_PHY_DC_MISC_get_fw_set(data)                                              ((0x02000000&(data))>>25)
#define DC_PHY_DC_MISC_tap_sel_shift                                                 (24)
#define DC_PHY_DC_MISC_tap_sel_mask                                                  (0x01000000)
#define DC_PHY_DC_MISC_tap_sel(data)                                                 (0x01000000&((data)<<24))
#define DC_PHY_DC_MISC_tap_sel_src(data)                                             ((0x01000000&(data))>>24)
#define DC_PHY_DC_MISC_get_tap_sel(data)                                             ((0x01000000&(data))>>24)


#define DC_PHY_DC_TEST_MODE_SEL                                                      0x1800883c
#define DC_PHY_DC_TEST_MODE_SEL_reg_addr                                             "0xB800883C"
#define DC_PHY_DC_TEST_MODE_SEL_reg                                                  0xB800883C
#define set_DC_PHY_DC_TEST_MODE_SEL_reg(data)   (*((volatile unsigned int*) DC_PHY_DC_TEST_MODE_SEL_reg)=data)
#define get_DC_PHY_DC_TEST_MODE_SEL_reg   (*((volatile unsigned int*) DC_PHY_DC_TEST_MODE_SEL_reg))
#define DC_PHY_DC_TEST_MODE_SEL_inst_adr                                             "0x000F"
#define DC_PHY_DC_TEST_MODE_SEL_inst                                                 0x000F
#define DC_PHY_DC_TEST_MODE_SEL_clear_set_sys_shift                                  (2)
#define DC_PHY_DC_TEST_MODE_SEL_clear_set_sys_mask                                   (0x00000004)
#define DC_PHY_DC_TEST_MODE_SEL_clear_set_sys(data)                                  (0x00000004&((data)<<2))
#define DC_PHY_DC_TEST_MODE_SEL_clear_set_sys_src(data)                              ((0x00000004&(data))>>2)
#define DC_PHY_DC_TEST_MODE_SEL_get_clear_set_sys(data)                              ((0x00000004&(data))>>2)
#define DC_PHY_DC_TEST_MODE_SEL_clear_trig_shift                                     (1)
#define DC_PHY_DC_TEST_MODE_SEL_clear_trig_mask                                      (0x00000002)
#define DC_PHY_DC_TEST_MODE_SEL_clear_trig(data)                                     (0x00000002&((data)<<1))
#define DC_PHY_DC_TEST_MODE_SEL_clear_trig_src(data)                                 ((0x00000002&(data))>>1)
#define DC_PHY_DC_TEST_MODE_SEL_get_clear_trig(data)                                 ((0x00000002&(data))>>1)
#define DC_PHY_DC_TEST_MODE_SEL_test_mode_sel_shift                                  (0)
#define DC_PHY_DC_TEST_MODE_SEL_test_mode_sel_mask                                   (0x00000001)
#define DC_PHY_DC_TEST_MODE_SEL_test_mode_sel(data)                                  (0x00000001&((data)<<0))
#define DC_PHY_DC_TEST_MODE_SEL_test_mode_sel_src(data)                              ((0x00000001&(data))>>0)
#define DC_PHY_DC_TEST_MODE_SEL_get_test_mode_sel(data)                              ((0x00000001&(data))>>0)


#define DC_PHY_DC_DDR3_CTL                                                           0x18008840
#define DC_PHY_DC_DDR3_CTL_reg_addr                                                  "0xB8008840"
#define DC_PHY_DC_DDR3_CTL_reg                                                       0xB8008840
#define set_DC_PHY_DC_DDR3_CTL_reg(data)   (*((volatile unsigned int*) DC_PHY_DC_DDR3_CTL_reg)=data)
#define get_DC_PHY_DC_DDR3_CTL_reg   (*((volatile unsigned int*) DC_PHY_DC_DDR3_CTL_reg))
#define DC_PHY_DC_DDR3_CTL_inst_adr                                                  "0x0010"
#define DC_PHY_DC_DDR3_CTL_inst                                                      0x0010
#define DC_PHY_DC_DDR3_CTL_write_en_14_shift                                         (29)
#define DC_PHY_DC_DDR3_CTL_write_en_14_mask                                          (0x20000000)
#define DC_PHY_DC_DDR3_CTL_write_en_14(data)                                         (0x20000000&((data)<<29))
#define DC_PHY_DC_DDR3_CTL_write_en_14_src(data)                                     ((0x20000000&(data))>>29)
#define DC_PHY_DC_DDR3_CTL_get_write_en_14(data)                                     ((0x20000000&(data))>>29)
#define DC_PHY_DC_DDR3_CTL_ddr3_swap_shift                                           (28)
#define DC_PHY_DC_DDR3_CTL_ddr3_swap_mask                                            (0x10000000)
#define DC_PHY_DC_DDR3_CTL_ddr3_swap(data)                                           (0x10000000&((data)<<28))
#define DC_PHY_DC_DDR3_CTL_ddr3_swap_src(data)                                       ((0x10000000&(data))>>28)
#define DC_PHY_DC_DDR3_CTL_get_ddr3_swap(data)                                       ((0x10000000&(data))>>28)
#define DC_PHY_DC_DDR3_CTL_write_en_13_shift                                         (27)
#define DC_PHY_DC_DDR3_CTL_write_en_13_mask                                          (0x08000000)
#define DC_PHY_DC_DDR3_CTL_write_en_13(data)                                         (0x08000000&((data)<<27))
#define DC_PHY_DC_DDR3_CTL_write_en_13_src(data)                                     ((0x08000000&(data))>>27)
#define DC_PHY_DC_DDR3_CTL_get_write_en_13(data)                                     ((0x08000000&(data))>>27)
#define DC_PHY_DC_DDR3_CTL_end_500us_shift                                           (26)
#define DC_PHY_DC_DDR3_CTL_end_500us_mask                                            (0x04000000)
#define DC_PHY_DC_DDR3_CTL_end_500us(data)                                           (0x04000000&((data)<<26))
#define DC_PHY_DC_DDR3_CTL_end_500us_src(data)                                       ((0x04000000&(data))>>26)
#define DC_PHY_DC_DDR3_CTL_get_end_500us(data)                                       ((0x04000000&(data))>>26)
#define DC_PHY_DC_DDR3_CTL_write_en_12_shift                                         (25)
#define DC_PHY_DC_DDR3_CTL_write_en_12_mask                                          (0x02000000)
#define DC_PHY_DC_DDR3_CTL_write_en_12(data)                                         (0x02000000&((data)<<25))
#define DC_PHY_DC_DDR3_CTL_write_en_12_src(data)                                     ((0x02000000&(data))>>25)
#define DC_PHY_DC_DDR3_CTL_get_write_en_12(data)                                     ((0x02000000&(data))>>25)
#define DC_PHY_DC_DDR3_CTL_end_200us_shift                                           (24)
#define DC_PHY_DC_DDR3_CTL_end_200us_mask                                            (0x01000000)
#define DC_PHY_DC_DDR3_CTL_end_200us(data)                                           (0x01000000&((data)<<24))
#define DC_PHY_DC_DDR3_CTL_end_200us_src(data)                                       ((0x01000000&(data))>>24)
#define DC_PHY_DC_DDR3_CTL_get_end_200us(data)                                       ((0x01000000&(data))>>24)
#define DC_PHY_DC_DDR3_CTL_write_en_11_shift                                         (23)
#define DC_PHY_DC_DDR3_CTL_write_en_11_mask                                          (0x00800000)
#define DC_PHY_DC_DDR3_CTL_write_en_11(data)                                         (0x00800000&((data)<<23))
#define DC_PHY_DC_DDR3_CTL_write_en_11_src(data)                                     ((0x00800000&(data))>>23)
#define DC_PHY_DC_DDR3_CTL_get_write_en_11(data)                                     ((0x00800000&(data))>>23)
#define DC_PHY_DC_DDR3_CTL_fast_prechg_shift                                         (22)
#define DC_PHY_DC_DDR3_CTL_fast_prechg_mask                                          (0x00400000)
#define DC_PHY_DC_DDR3_CTL_fast_prechg(data)                                         (0x00400000&((data)<<22))
#define DC_PHY_DC_DDR3_CTL_fast_prechg_src(data)                                     ((0x00400000&(data))>>22)
#define DC_PHY_DC_DDR3_CTL_get_fast_prechg(data)                                     ((0x00400000&(data))>>22)
#define DC_PHY_DC_DDR3_CTL_write_en_10_shift                                         (21)
#define DC_PHY_DC_DDR3_CTL_write_en_10_mask                                          (0x00200000)
#define DC_PHY_DC_DDR3_CTL_write_en_10(data)                                         (0x00200000&((data)<<21))
#define DC_PHY_DC_DDR3_CTL_write_en_10_src(data)                                     ((0x00200000&(data))>>21)
#define DC_PHY_DC_DDR3_CTL_get_write_en_10(data)                                     ((0x00200000&(data))>>21)
#define DC_PHY_DC_DDR3_CTL_dis_cti_shift                                             (20)
#define DC_PHY_DC_DDR3_CTL_dis_cti_mask                                              (0x00100000)
#define DC_PHY_DC_DDR3_CTL_dis_cti(data)                                             (0x00100000&((data)<<20))
#define DC_PHY_DC_DDR3_CTL_dis_cti_src(data)                                         ((0x00100000&(data))>>20)
#define DC_PHY_DC_DDR3_CTL_get_dis_cti(data)                                         ((0x00100000&(data))>>20)
#define DC_PHY_DC_DDR3_CTL_write_en_9_shift                                          (19)
#define DC_PHY_DC_DDR3_CTL_write_en_9_mask                                           (0x00080000)
#define DC_PHY_DC_DDR3_CTL_write_en_9(data)                                          (0x00080000&((data)<<19))
#define DC_PHY_DC_DDR3_CTL_write_en_9_src(data)                                      ((0x00080000&(data))>>19)
#define DC_PHY_DC_DDR3_CTL_get_write_en_9(data)                                      ((0x00080000&(data))>>19)
#define DC_PHY_DC_DDR3_CTL_dis_8bank_shift                                           (18)
#define DC_PHY_DC_DDR3_CTL_dis_8bank_mask                                            (0x00040000)
#define DC_PHY_DC_DDR3_CTL_dis_8bank(data)                                           (0x00040000&((data)<<18))
#define DC_PHY_DC_DDR3_CTL_dis_8bank_src(data)                                       ((0x00040000&(data))>>18)
#define DC_PHY_DC_DDR3_CTL_get_dis_8bank(data)                                       ((0x00040000&(data))>>18)
#define DC_PHY_DC_DDR3_CTL_write_en_8_shift                                          (17)
#define DC_PHY_DC_DDR3_CTL_write_en_8_mask                                           (0x00020000)
#define DC_PHY_DC_DDR3_CTL_write_en_8(data)                                          (0x00020000&((data)<<17))
#define DC_PHY_DC_DDR3_CTL_write_en_8_src(data)                                      ((0x00020000&(data))>>17)
#define DC_PHY_DC_DDR3_CTL_get_write_en_8(data)                                      ((0x00020000&(data))>>17)
#define DC_PHY_DC_DDR3_CTL_use_tmmrd_shift                                           (16)
#define DC_PHY_DC_DDR3_CTL_use_tmmrd_mask                                            (0x00010000)
#define DC_PHY_DC_DDR3_CTL_use_tmmrd(data)                                           (0x00010000&((data)<<16))
#define DC_PHY_DC_DDR3_CTL_use_tmmrd_src(data)                                       ((0x00010000&(data))>>16)
#define DC_PHY_DC_DDR3_CTL_get_use_tmmrd(data)                                       ((0x00010000&(data))>>16)
#define DC_PHY_DC_DDR3_CTL_write_en_7_shift                                          (15)
#define DC_PHY_DC_DDR3_CTL_write_en_7_mask                                           (0x00008000)
#define DC_PHY_DC_DDR3_CTL_write_en_7(data)                                          (0x00008000&((data)<<15))
#define DC_PHY_DC_DDR3_CTL_write_en_7_src(data)                                      ((0x00008000&(data))>>15)
#define DC_PHY_DC_DDR3_CTL_get_write_en_7(data)                                      ((0x00008000&(data))>>15)
#define DC_PHY_DC_DDR3_CTL_dis_pre_all_shift                                         (14)
#define DC_PHY_DC_DDR3_CTL_dis_pre_all_mask                                          (0x00004000)
#define DC_PHY_DC_DDR3_CTL_dis_pre_all(data)                                         (0x00004000&((data)<<14))
#define DC_PHY_DC_DDR3_CTL_dis_pre_all_src(data)                                     ((0x00004000&(data))>>14)
#define DC_PHY_DC_DDR3_CTL_get_dis_pre_all(data)                                     ((0x00004000&(data))>>14)
#define DC_PHY_DC_DDR3_CTL_write_en_6_shift                                          (13)
#define DC_PHY_DC_DDR3_CTL_write_en_6_mask                                           (0x00002000)
#define DC_PHY_DC_DDR3_CTL_write_en_6(data)                                          (0x00002000&((data)<<13))
#define DC_PHY_DC_DDR3_CTL_write_en_6_src(data)                                      ((0x00002000&(data))>>13)
#define DC_PHY_DC_DDR3_CTL_get_write_en_6(data)                                      ((0x00002000&(data))>>13)
#define DC_PHY_DC_DDR3_CTL_ddr3_zqcl_short_shift                                     (12)
#define DC_PHY_DC_DDR3_CTL_ddr3_zqcl_short_mask                                      (0x00001000)
#define DC_PHY_DC_DDR3_CTL_ddr3_zqcl_short(data)                                     (0x00001000&((data)<<12))
#define DC_PHY_DC_DDR3_CTL_ddr3_zqcl_short_src(data)                                 ((0x00001000&(data))>>12)
#define DC_PHY_DC_DDR3_CTL_get_ddr3_zqcl_short(data)                                 ((0x00001000&(data))>>12)
#define DC_PHY_DC_DDR3_CTL_write_en_5_shift                                          (11)
#define DC_PHY_DC_DDR3_CTL_write_en_5_mask                                           (0x00000800)
#define DC_PHY_DC_DDR3_CTL_write_en_5(data)                                          (0x00000800&((data)<<11))
#define DC_PHY_DC_DDR3_CTL_write_en_5_src(data)                                      ((0x00000800&(data))>>11)
#define DC_PHY_DC_DDR3_CTL_get_write_en_5(data)                                      ((0x00000800&(data))>>11)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_zqcl_shift                                       (10)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_zqcl_mask                                        (0x00000400)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_zqcl(data)                                       (0x00000400&((data)<<10))
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_zqcl_src(data)                                   ((0x00000400&(data))>>10)
#define DC_PHY_DC_DDR3_CTL_get_ddr3_exe_zqcl(data)                                   ((0x00000400&(data))>>10)
#define DC_PHY_DC_DDR3_CTL_write_en_4_shift                                          (9)
#define DC_PHY_DC_DDR3_CTL_write_en_4_mask                                           (0x00000200)
#define DC_PHY_DC_DDR3_CTL_write_en_4(data)                                          (0x00000200&((data)<<9))
#define DC_PHY_DC_DDR3_CTL_write_en_4_src(data)                                      ((0x00000200&(data))>>9)
#define DC_PHY_DC_DDR3_CTL_get_write_en_4(data)                                      ((0x00000200&(data))>>9)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr3_shift                                        (8)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr3_mask                                         (0x00000100)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr3(data)                                        (0x00000100&((data)<<8))
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr3_src(data)                                    ((0x00000100&(data))>>8)
#define DC_PHY_DC_DDR3_CTL_get_ddr3_exe_mr3(data)                                    ((0x00000100&(data))>>8)
#define DC_PHY_DC_DDR3_CTL_write_en_3_shift                                          (7)
#define DC_PHY_DC_DDR3_CTL_write_en_3_mask                                           (0x00000080)
#define DC_PHY_DC_DDR3_CTL_write_en_3(data)                                          (0x00000080&((data)<<7))
#define DC_PHY_DC_DDR3_CTL_write_en_3_src(data)                                      ((0x00000080&(data))>>7)
#define DC_PHY_DC_DDR3_CTL_get_write_en_3(data)                                      ((0x00000080&(data))>>7)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr2_shift                                        (6)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr2_mask                                         (0x00000040)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr2(data)                                        (0x00000040&((data)<<6))
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr2_src(data)                                    ((0x00000040&(data))>>6)
#define DC_PHY_DC_DDR3_CTL_get_ddr3_exe_mr2(data)                                    ((0x00000040&(data))>>6)
#define DC_PHY_DC_DDR3_CTL_write_en_2_shift                                          (5)
#define DC_PHY_DC_DDR3_CTL_write_en_2_mask                                           (0x00000020)
#define DC_PHY_DC_DDR3_CTL_write_en_2(data)                                          (0x00000020&((data)<<5))
#define DC_PHY_DC_DDR3_CTL_write_en_2_src(data)                                      ((0x00000020&(data))>>5)
#define DC_PHY_DC_DDR3_CTL_get_write_en_2(data)                                      ((0x00000020&(data))>>5)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr1_shift                                        (4)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr1_mask                                         (0x00000010)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr1(data)                                        (0x00000010&((data)<<4))
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr1_src(data)                                    ((0x00000010&(data))>>4)
#define DC_PHY_DC_DDR3_CTL_get_ddr3_exe_mr1(data)                                    ((0x00000010&(data))>>4)
#define DC_PHY_DC_DDR3_CTL_write_en_1_shift                                          (3)
#define DC_PHY_DC_DDR3_CTL_write_en_1_mask                                           (0x00000008)
#define DC_PHY_DC_DDR3_CTL_write_en_1(data)                                          (0x00000008&((data)<<3))
#define DC_PHY_DC_DDR3_CTL_write_en_1_src(data)                                      ((0x00000008&(data))>>3)
#define DC_PHY_DC_DDR3_CTL_get_write_en_1(data)                                      ((0x00000008&(data))>>3)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr0_shift                                        (2)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr0_mask                                         (0x00000004)
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr0(data)                                        (0x00000004&((data)<<2))
#define DC_PHY_DC_DDR3_CTL_ddr3_exe_mr0_src(data)                                    ((0x00000004&(data))>>2)
#define DC_PHY_DC_DDR3_CTL_get_ddr3_exe_mr0(data)                                    ((0x00000004&(data))>>2)
#define DC_PHY_DC_DDR3_CTL_write_en_0_shift                                          (1)
#define DC_PHY_DC_DDR3_CTL_write_en_0_mask                                           (0x00000002)
#define DC_PHY_DC_DDR3_CTL_write_en_0(data)                                          (0x00000002&((data)<<1))
#define DC_PHY_DC_DDR3_CTL_write_en_0_src(data)                                      ((0x00000002&(data))>>1)
#define DC_PHY_DC_DDR3_CTL_get_write_en_0(data)                                      ((0x00000002&(data))>>1)
#define DC_PHY_DC_DDR3_CTL_ddr3_init_shift                                           (0)
#define DC_PHY_DC_DDR3_CTL_ddr3_init_mask                                            (0x00000001)
#define DC_PHY_DC_DDR3_CTL_ddr3_init(data)                                           (0x00000001&((data)<<0))
#define DC_PHY_DC_DDR3_CTL_ddr3_init_src(data)                                       ((0x00000001&(data))>>0)
#define DC_PHY_DC_DDR3_CTL_get_ddr3_init(data)                                       ((0x00000001&(data))>>0)


#define DC_PHY_MOD_REG                                                               0x18008844
#define DC_PHY_MOD_REG_reg_addr                                                      "0xB8008844"
#define DC_PHY_MOD_REG_reg                                                           0xB8008844
#define set_DC_PHY_MOD_REG_reg(data)   (*((volatile unsigned int*) DC_PHY_MOD_REG_reg)=data)
#define get_DC_PHY_MOD_REG_reg   (*((volatile unsigned int*) DC_PHY_MOD_REG_reg))
#define DC_PHY_MOD_REG_inst_adr                                                      "0x0011"
#define DC_PHY_MOD_REG_inst                                                          0x0011
#define DC_PHY_MOD_REG_exmod_reg_shift                                               (16)
#define DC_PHY_MOD_REG_exmod_reg_mask                                                (0xFFFF0000)
#define DC_PHY_MOD_REG_exmod_reg(data)                                               (0xFFFF0000&((data)<<16))
#define DC_PHY_MOD_REG_exmod_reg_src(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_MOD_REG_get_exmod_reg(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_MOD_REG_mod_reg_shift                                                 (0)
#define DC_PHY_MOD_REG_mod_reg_mask                                                  (0x0000FFFF)
#define DC_PHY_MOD_REG_mod_reg(data)                                                 (0x0000FFFF&((data)<<0))
#define DC_PHY_MOD_REG_mod_reg_src(data)                                             ((0x0000FFFF&(data))>>0)
#define DC_PHY_MOD_REG_get_mod_reg(data)                                             ((0x0000FFFF&(data))>>0)


#define DC_PHY_MOD23_REG                                                             0x18008848
#define DC_PHY_MOD23_REG_reg_addr                                                    "0xB8008848"
#define DC_PHY_MOD23_REG_reg                                                         0xB8008848
#define set_DC_PHY_MOD23_REG_reg(data)   (*((volatile unsigned int*) DC_PHY_MOD23_REG_reg)=data)
#define get_DC_PHY_MOD23_REG_reg   (*((volatile unsigned int*) DC_PHY_MOD23_REG_reg))
#define DC_PHY_MOD23_REG_inst_adr                                                    "0x0012"
#define DC_PHY_MOD23_REG_inst                                                        0x0012
#define DC_PHY_MOD23_REG_mod3_reg_shift                                              (16)
#define DC_PHY_MOD23_REG_mod3_reg_mask                                               (0xFFFF0000)
#define DC_PHY_MOD23_REG_mod3_reg(data)                                              (0xFFFF0000&((data)<<16))
#define DC_PHY_MOD23_REG_mod3_reg_src(data)                                          ((0xFFFF0000&(data))>>16)
#define DC_PHY_MOD23_REG_get_mod3_reg(data)                                          ((0xFFFF0000&(data))>>16)
#define DC_PHY_MOD23_REG_mod2_reg_shift                                              (0)
#define DC_PHY_MOD23_REG_mod2_reg_mask                                               (0x0000FFFF)
#define DC_PHY_MOD23_REG_mod2_reg(data)                                              (0x0000FFFF&((data)<<0))
#define DC_PHY_MOD23_REG_mod2_reg_src(data)                                          ((0x0000FFFF&(data))>>0)
#define DC_PHY_MOD23_REG_get_mod2_reg(data)                                          ((0x0000FFFF&(data))>>0)


#define DC_PHY_RFIFO_CTL                                                             0x1800884c
#define DC_PHY_RFIFO_CTL_reg_addr                                                    "0xB800884C"
#define DC_PHY_RFIFO_CTL_reg                                                         0xB800884C
#define set_DC_PHY_RFIFO_CTL_reg(data)   (*((volatile unsigned int*) DC_PHY_RFIFO_CTL_reg)=data)
#define get_DC_PHY_RFIFO_CTL_reg   (*((volatile unsigned int*) DC_PHY_RFIFO_CTL_reg))
#define DC_PHY_RFIFO_CTL_inst_adr                                                    "0x0013"
#define DC_PHY_RFIFO_CTL_inst                                                        0x0013
#define DC_PHY_RFIFO_CTL_wfifo_rdy_gated_shift                                       (12)
#define DC_PHY_RFIFO_CTL_wfifo_rdy_gated_mask                                        (0x00001000)
#define DC_PHY_RFIFO_CTL_wfifo_rdy_gated(data)                                       (0x00001000&((data)<<12))
#define DC_PHY_RFIFO_CTL_wfifo_rdy_gated_src(data)                                   ((0x00001000&(data))>>12)
#define DC_PHY_RFIFO_CTL_get_wfifo_rdy_gated(data)                                   ((0x00001000&(data))>>12)
#define DC_PHY_RFIFO_CTL_rdwr_use_full_shift                                         (8)
#define DC_PHY_RFIFO_CTL_rdwr_use_full_mask                                          (0x00000100)
#define DC_PHY_RFIFO_CTL_rdwr_use_full(data)                                         (0x00000100&((data)<<8))
#define DC_PHY_RFIFO_CTL_rdwr_use_full_src(data)                                     ((0x00000100&(data))>>8)
#define DC_PHY_RFIFO_CTL_get_rdwr_use_full(data)                                     ((0x00000100&(data))>>8)
#define DC_PHY_RFIFO_CTL_full_gated_shift                                            (7)
#define DC_PHY_RFIFO_CTL_full_gated_mask                                             (0x00000080)
#define DC_PHY_RFIFO_CTL_full_gated(data)                                            (0x00000080&((data)<<7))
#define DC_PHY_RFIFO_CTL_full_gated_src(data)                                        ((0x00000080&(data))>>7)
#define DC_PHY_RFIFO_CTL_get_full_gated(data)                                        ((0x00000080&(data))>>7)
#define DC_PHY_RFIFO_CTL_rfifo_thred_shift                                           (0)
#define DC_PHY_RFIFO_CTL_rfifo_thred_mask                                            (0x0000007F)
#define DC_PHY_RFIFO_CTL_rfifo_thred(data)                                           (0x0000007F&((data)<<0))
#define DC_PHY_RFIFO_CTL_rfifo_thred_src(data)                                       ((0x0000007F&(data))>>0)
#define DC_PHY_RFIFO_CTL_get_rfifo_thred(data)                                       ((0x0000007F&(data))>>0)


#define DC_PHY_ERR_STATUS                                                            0x18008850
#define DC_PHY_ERR_STATUS_reg_addr                                                   "0xB8008850"
#define DC_PHY_ERR_STATUS_reg                                                        0xB8008850
#define set_DC_PHY_ERR_STATUS_reg(data)   (*((volatile unsigned int*) DC_PHY_ERR_STATUS_reg)=data)
#define get_DC_PHY_ERR_STATUS_reg   (*((volatile unsigned int*) DC_PHY_ERR_STATUS_reg))
#define DC_PHY_ERR_STATUS_inst_adr                                                   "0x0014"
#define DC_PHY_ERR_STATUS_inst                                                       0x0014
#define DC_PHY_ERR_STATUS_err_cti_cmd_shift                                          (1)
#define DC_PHY_ERR_STATUS_err_cti_cmd_mask                                           (0x00000002)
#define DC_PHY_ERR_STATUS_err_cti_cmd(data)                                          (0x00000002&((data)<<1))
#define DC_PHY_ERR_STATUS_err_cti_cmd_src(data)                                      ((0x00000002&(data))>>1)
#define DC_PHY_ERR_STATUS_get_err_cti_cmd(data)                                      ((0x00000002&(data))>>1)
#define DC_PHY_ERR_STATUS_err_active_shift                                           (0)
#define DC_PHY_ERR_STATUS_err_active_mask                                            (0x00000001)
#define DC_PHY_ERR_STATUS_err_active(data)                                           (0x00000001&((data)<<0))
#define DC_PHY_ERR_STATUS_err_active_src(data)                                       ((0x00000001&(data))>>0)
#define DC_PHY_ERR_STATUS_get_err_active(data)                                       ((0x00000001&(data))>>0)


#define DC_PHY_DC_WRITE_LEVEL                                                        0x18008854
#define DC_PHY_DC_WRITE_LEVEL_reg_addr                                               "0xB8008854"
#define DC_PHY_DC_WRITE_LEVEL_reg                                                    0xB8008854
#define set_DC_PHY_DC_WRITE_LEVEL_reg(data)   (*((volatile unsigned int*) DC_PHY_DC_WRITE_LEVEL_reg)=data)
#define get_DC_PHY_DC_WRITE_LEVEL_reg   (*((volatile unsigned int*) DC_PHY_DC_WRITE_LEVEL_reg))
#define DC_PHY_DC_WRITE_LEVEL_inst_adr                                               "0x0015"
#define DC_PHY_DC_WRITE_LEVEL_inst                                                   0x0015
#define DC_PHY_DC_WRITE_LEVEL_exe_prea_shift                                         (3)
#define DC_PHY_DC_WRITE_LEVEL_exe_prea_mask                                          (0x00000008)
#define DC_PHY_DC_WRITE_LEVEL_exe_prea(data)                                         (0x00000008&((data)<<3))
#define DC_PHY_DC_WRITE_LEVEL_exe_prea_src(data)                                     ((0x00000008&(data))>>3)
#define DC_PHY_DC_WRITE_LEVEL_get_exe_prea(data)                                     ((0x00000008&(data))>>3)
#define DC_PHY_DC_WRITE_LEVEL_dis_refresh_shift                                      (2)
#define DC_PHY_DC_WRITE_LEVEL_dis_refresh_mask                                       (0x00000004)
#define DC_PHY_DC_WRITE_LEVEL_dis_refresh(data)                                      (0x00000004&((data)<<2))
#define DC_PHY_DC_WRITE_LEVEL_dis_refresh_src(data)                                  ((0x00000004&(data))>>2)
#define DC_PHY_DC_WRITE_LEVEL_get_dis_refresh(data)                                  ((0x00000004&(data))>>2)
#define DC_PHY_DC_WRITE_LEVEL_trig_wr_level_shift                                    (1)
#define DC_PHY_DC_WRITE_LEVEL_trig_wr_level_mask                                     (0x00000002)
#define DC_PHY_DC_WRITE_LEVEL_trig_wr_level(data)                                    (0x00000002&((data)<<1))
#define DC_PHY_DC_WRITE_LEVEL_trig_wr_level_src(data)                                ((0x00000002&(data))>>1)
#define DC_PHY_DC_WRITE_LEVEL_get_trig_wr_level(data)                                ((0x00000002&(data))>>1)
#define DC_PHY_DC_WRITE_LEVEL_wr_level_rdy_shift                                     (0)
#define DC_PHY_DC_WRITE_LEVEL_wr_level_rdy_mask                                      (0x00000001)
#define DC_PHY_DC_WRITE_LEVEL_wr_level_rdy(data)                                     (0x00000001&((data)<<0))
#define DC_PHY_DC_WRITE_LEVEL_wr_level_rdy_src(data)                                 ((0x00000001&(data))>>0)
#define DC_PHY_DC_WRITE_LEVEL_get_wr_level_rdy(data)                                 ((0x00000001&(data))>>0)


#define DC_PHY_INT_ENABLE                                                            0x18008858
#define DC_PHY_INT_ENABLE_reg_addr                                                   "0xB8008858"
#define DC_PHY_INT_ENABLE_reg                                                        0xB8008858
#define set_DC_PHY_INT_ENABLE_reg(data)   (*((volatile unsigned int*) DC_PHY_INT_ENABLE_reg)=data)
#define get_DC_PHY_INT_ENABLE_reg   (*((volatile unsigned int*) DC_PHY_INT_ENABLE_reg))
#define DC_PHY_INT_ENABLE_inst_adr                                                   "0x0016"
#define DC_PHY_INT_ENABLE_inst                                                       0x0016
#define DC_PHY_INT_ENABLE_int_err_cticmd_en_shift                                    (4)
#define DC_PHY_INT_ENABLE_int_err_cticmd_en_mask                                     (0x00000010)
#define DC_PHY_INT_ENABLE_int_err_cticmd_en(data)                                    (0x00000010&((data)<<4))
#define DC_PHY_INT_ENABLE_int_err_cticmd_en_src(data)                                ((0x00000010&(data))>>4)
#define DC_PHY_INT_ENABLE_get_int_err_cticmd_en(data)                                ((0x00000010&(data))>>4)
#define DC_PHY_INT_ENABLE_int_err_active_en_shift                                    (3)
#define DC_PHY_INT_ENABLE_int_err_active_en_mask                                     (0x00000008)
#define DC_PHY_INT_ENABLE_int_err_active_en(data)                                    (0x00000008&((data)<<3))
#define DC_PHY_INT_ENABLE_int_err_active_en_src(data)                                ((0x00000008&(data))>>3)
#define DC_PHY_INT_ENABLE_get_int_err_active_en(data)                                ((0x00000008&(data))>>3)
#define DC_PHY_INT_ENABLE_int_vcpu_en_shift                                          (2)
#define DC_PHY_INT_ENABLE_int_vcpu_en_mask                                           (0x00000004)
#define DC_PHY_INT_ENABLE_int_vcpu_en(data)                                          (0x00000004&((data)<<2))
#define DC_PHY_INT_ENABLE_int_vcpu_en_src(data)                                      ((0x00000004&(data))>>2)
#define DC_PHY_INT_ENABLE_get_int_vcpu_en(data)                                      ((0x00000004&(data))>>2)
#define DC_PHY_INT_ENABLE_int_acpu_en_shift                                          (1)
#define DC_PHY_INT_ENABLE_int_acpu_en_mask                                           (0x00000002)
#define DC_PHY_INT_ENABLE_int_acpu_en(data)                                          (0x00000002&((data)<<1))
#define DC_PHY_INT_ENABLE_int_acpu_en_src(data)                                      ((0x00000002&(data))>>1)
#define DC_PHY_INT_ENABLE_get_int_acpu_en(data)                                      ((0x00000002&(data))>>1)
#define DC_PHY_INT_ENABLE_int_scpu_en_shift                                          (0)
#define DC_PHY_INT_ENABLE_int_scpu_en_mask                                           (0x00000001)
#define DC_PHY_INT_ENABLE_int_scpu_en(data)                                          (0x00000001&((data)<<0))
#define DC_PHY_INT_ENABLE_int_scpu_en_src(data)                                      ((0x00000001&(data))>>0)
#define DC_PHY_INT_ENABLE_get_int_scpu_en(data)                                      ((0x00000001&(data))>>0)


#define DC_PHY_RFIFO_MAXCNT                                                          0x1800885c
#define DC_PHY_RFIFO_MAXCNT_reg_addr                                                 "0xB800885C"
#define DC_PHY_RFIFO_MAXCNT_reg                                                      0xB800885C
#define set_DC_PHY_RFIFO_MAXCNT_reg(data)   (*((volatile unsigned int*) DC_PHY_RFIFO_MAXCNT_reg)=data)
#define get_DC_PHY_RFIFO_MAXCNT_reg   (*((volatile unsigned int*) DC_PHY_RFIFO_MAXCNT_reg))
#define DC_PHY_RFIFO_MAXCNT_inst_adr                                                 "0x0017"
#define DC_PHY_RFIFO_MAXCNT_inst                                                     0x0017
#define DC_PHY_RFIFO_MAXCNT_non_valid_maxcnt_shift                                   (7)
#define DC_PHY_RFIFO_MAXCNT_non_valid_maxcnt_mask                                    (0x00000080)
#define DC_PHY_RFIFO_MAXCNT_non_valid_maxcnt(data)                                   (0x00000080&((data)<<7))
#define DC_PHY_RFIFO_MAXCNT_non_valid_maxcnt_src(data)                               ((0x00000080&(data))>>7)
#define DC_PHY_RFIFO_MAXCNT_get_non_valid_maxcnt(data)                               ((0x00000080&(data))>>7)
#define DC_PHY_RFIFO_MAXCNT_rfifo_cnt_max_shift                                      (0)
#define DC_PHY_RFIFO_MAXCNT_rfifo_cnt_max_mask                                       (0x0000007F)
#define DC_PHY_RFIFO_MAXCNT_rfifo_cnt_max(data)                                      (0x0000007F&((data)<<0))
#define DC_PHY_RFIFO_MAXCNT_rfifo_cnt_max_src(data)                                  ((0x0000007F&(data))>>0)
#define DC_PHY_RFIFO_MAXCNT_get_rfifo_cnt_max(data)                                  ((0x0000007F&(data))>>0)


#define DC_PHY_SM_STATUS                                                             0x18008860
#define DC_PHY_SM_STATUS_reg_addr                                                    "0xB8008860"
#define DC_PHY_SM_STATUS_reg                                                         0xB8008860
#define set_DC_PHY_SM_STATUS_reg(data)   (*((volatile unsigned int*) DC_PHY_SM_STATUS_reg)=data)
#define get_DC_PHY_SM_STATUS_reg   (*((volatile unsigned int*) DC_PHY_SM_STATUS_reg))
#define DC_PHY_SM_STATUS_inst_adr                                                    "0x0018"
#define DC_PHY_SM_STATUS_inst                                                        0x0018
#define DC_PHY_SM_STATUS_par_st_1_shift                                              (21)
#define DC_PHY_SM_STATUS_par_st_1_mask                                               (0x03E00000)
#define DC_PHY_SM_STATUS_par_st_1(data)                                              (0x03E00000&((data)<<21))
#define DC_PHY_SM_STATUS_par_st_1_src(data)                                          ((0x03E00000&(data))>>21)
#define DC_PHY_SM_STATUS_get_par_st_1(data)                                          ((0x03E00000&(data))>>21)
#define DC_PHY_SM_STATUS_bank_act_shift                                              (13)
#define DC_PHY_SM_STATUS_bank_act_mask                                               (0x001FE000)
#define DC_PHY_SM_STATUS_bank_act(data)                                              (0x001FE000&((data)<<13))
#define DC_PHY_SM_STATUS_bank_act_src(data)                                          ((0x001FE000&(data))>>13)
#define DC_PHY_SM_STATUS_get_bank_act(data)                                          ((0x001FE000&(data))>>13)
#define DC_PHY_SM_STATUS_cmd_cnt_shift                                               (10)
#define DC_PHY_SM_STATUS_cmd_cnt_mask                                                (0x00001C00)
#define DC_PHY_SM_STATUS_cmd_cnt(data)                                               (0x00001C00&((data)<<10))
#define DC_PHY_SM_STATUS_cmd_cnt_src(data)                                           ((0x00001C00&(data))>>10)
#define DC_PHY_SM_STATUS_get_cmd_cnt(data)                                           ((0x00001C00&(data))>>10)
#define DC_PHY_SM_STATUS_par_st_shift                                                (0)
#define DC_PHY_SM_STATUS_par_st_mask                                                 (0x000003FF)
#define DC_PHY_SM_STATUS_par_st(data)                                                (0x000003FF&((data)<<0))
#define DC_PHY_SM_STATUS_par_st_src(data)                                            ((0x000003FF&(data))>>0)
#define DC_PHY_SM_STATUS_get_par_st(data)                                            ((0x000003FF&(data))>>0)


#define DC_PHY_WFIFO_CNT                                                             0x18008864
#define DC_PHY_WFIFO_CNT_reg_addr                                                    "0xB8008864"
#define DC_PHY_WFIFO_CNT_reg                                                         0xB8008864
#define set_DC_PHY_WFIFO_CNT_reg(data)   (*((volatile unsigned int*) DC_PHY_WFIFO_CNT_reg)=data)
#define get_DC_PHY_WFIFO_CNT_reg   (*((volatile unsigned int*) DC_PHY_WFIFO_CNT_reg))
#define DC_PHY_WFIFO_CNT_inst_adr                                                    "0x0019"
#define DC_PHY_WFIFO_CNT_inst                                                        0x0019
#define DC_PHY_WFIFO_CNT_wfifo_sys_req_statistic_en_shift                            (31)
#define DC_PHY_WFIFO_CNT_wfifo_sys_req_statistic_en_mask                             (0x80000000)
#define DC_PHY_WFIFO_CNT_wfifo_sys_req_statistic_en(data)                            (0x80000000&((data)<<31))
#define DC_PHY_WFIFO_CNT_wfifo_sys_req_statistic_en_src(data)                        ((0x80000000&(data))>>31)
#define DC_PHY_WFIFO_CNT_get_wfifo_sys_req_statistic_en(data)                        ((0x80000000&(data))>>31)
#define DC_PHY_WFIFO_CNT_wfifo_ddr_req_statistic_en_shift                            (30)
#define DC_PHY_WFIFO_CNT_wfifo_ddr_req_statistic_en_mask                             (0x40000000)
#define DC_PHY_WFIFO_CNT_wfifo_ddr_req_statistic_en(data)                            (0x40000000&((data)<<30))
#define DC_PHY_WFIFO_CNT_wfifo_ddr_req_statistic_en_src(data)                        ((0x40000000&(data))>>30)
#define DC_PHY_WFIFO_CNT_get_wfifo_ddr_req_statistic_en(data)                        ((0x40000000&(data))>>30)
#define DC_PHY_WFIFO_CNT_clear_wfifo_record_shift                                    (29)
#define DC_PHY_WFIFO_CNT_clear_wfifo_record_mask                                     (0x20000000)
#define DC_PHY_WFIFO_CNT_clear_wfifo_record(data)                                    (0x20000000&((data)<<29))
#define DC_PHY_WFIFO_CNT_clear_wfifo_record_src(data)                                ((0x20000000&(data))>>29)
#define DC_PHY_WFIFO_CNT_get_clear_wfifo_record(data)                                ((0x20000000&(data))>>29)
#define DC_PHY_WFIFO_CNT_wfifo_rd_cnt_et_shift                                       (16)
#define DC_PHY_WFIFO_CNT_wfifo_rd_cnt_et_mask                                        (0x00FF0000)
#define DC_PHY_WFIFO_CNT_wfifo_rd_cnt_et(data)                                       (0x00FF0000&((data)<<16))
#define DC_PHY_WFIFO_CNT_wfifo_rd_cnt_et_src(data)                                   ((0x00FF0000&(data))>>16)
#define DC_PHY_WFIFO_CNT_get_wfifo_rd_cnt_et(data)                                   ((0x00FF0000&(data))>>16)
#define DC_PHY_WFIFO_CNT_wfifo_rd_cnt_rl_shift                                       (8)
#define DC_PHY_WFIFO_CNT_wfifo_rd_cnt_rl_mask                                        (0x0000FF00)
#define DC_PHY_WFIFO_CNT_wfifo_rd_cnt_rl(data)                                       (0x0000FF00&((data)<<8))
#define DC_PHY_WFIFO_CNT_wfifo_rd_cnt_rl_src(data)                                   ((0x0000FF00&(data))>>8)
#define DC_PHY_WFIFO_CNT_get_wfifo_rd_cnt_rl(data)                                   ((0x0000FF00&(data))>>8)
#define DC_PHY_WFIFO_CNT_wfifo_wr_cnt_rl_shift                                       (0)
#define DC_PHY_WFIFO_CNT_wfifo_wr_cnt_rl_mask                                        (0x000000FF)
#define DC_PHY_WFIFO_CNT_wfifo_wr_cnt_rl(data)                                       (0x000000FF&((data)<<0))
#define DC_PHY_WFIFO_CNT_wfifo_wr_cnt_rl_src(data)                                   ((0x000000FF&(data))>>0)
#define DC_PHY_WFIFO_CNT_get_wfifo_wr_cnt_rl(data)                                   ((0x000000FF&(data))>>0)


#define DC_PHY_DC_DEBUG                                                              0x18008868
#define DC_PHY_DC_DEBUG_reg_addr                                                     "0xB8008868"
#define DC_PHY_DC_DEBUG_reg                                                          0xB8008868
#define set_DC_PHY_DC_DEBUG_reg(data)   (*((volatile unsigned int*) DC_PHY_DC_DEBUG_reg)=data)
#define get_DC_PHY_DC_DEBUG_reg   (*((volatile unsigned int*) DC_PHY_DC_DEBUG_reg))
#define DC_PHY_DC_DEBUG_inst_adr                                                     "0x001A"
#define DC_PHY_DC_DEBUG_inst                                                         0x001A
#define DC_PHY_DC_DEBUG_io_blk_dbg_mode_shift                                        (24)
#define DC_PHY_DC_DEBUG_io_blk_dbg_mode_mask                                         (0x07000000)
#define DC_PHY_DC_DEBUG_io_blk_dbg_mode(data)                                        (0x07000000&((data)<<24))
#define DC_PHY_DC_DEBUG_io_blk_dbg_mode_src(data)                                    ((0x07000000&(data))>>24)
#define DC_PHY_DC_DEBUG_get_io_blk_dbg_mode(data)                                    ((0x07000000&(data))>>24)
#define DC_PHY_DC_DEBUG_dbg_out_mod_shift                                            (20)
#define DC_PHY_DC_DEBUG_dbg_out_mod_mask                                             (0x00700000)
#define DC_PHY_DC_DEBUG_dbg_out_mod(data)                                            (0x00700000&((data)<<20))
#define DC_PHY_DC_DEBUG_dbg_out_mod_src(data)                                        ((0x00700000&(data))>>20)
#define DC_PHY_DC_DEBUG_get_dbg_out_mod(data)                                        ((0x00700000&(data))>>20)
#define DC_PHY_DC_DEBUG_pad_tie_value_shift                                          (16)
#define DC_PHY_DC_DEBUG_pad_tie_value_mask                                           (0x000F0000)
#define DC_PHY_DC_DEBUG_pad_tie_value(data)                                          (0x000F0000&((data)<<16))
#define DC_PHY_DC_DEBUG_pad_tie_value_src(data)                                      ((0x000F0000&(data))>>16)
#define DC_PHY_DC_DEBUG_get_pad_tie_value(data)                                      ((0x000F0000&(data))>>16)
#define DC_PHY_DC_DEBUG_shift_trig_mode_shift                                        (9)
#define DC_PHY_DC_DEBUG_shift_trig_mode_mask                                         (0x0000FE00)
#define DC_PHY_DC_DEBUG_shift_trig_mode(data)                                        (0x0000FE00&((data)<<9))
#define DC_PHY_DC_DEBUG_shift_trig_mode_src(data)                                    ((0x0000FE00&(data))>>9)
#define DC_PHY_DC_DEBUG_get_shift_trig_mode(data)                                    ((0x0000FE00&(data))>>9)
#define DC_PHY_DC_DEBUG_rd_dbg_mod_shift                                             (6)
#define DC_PHY_DC_DEBUG_rd_dbg_mod_mask                                              (0x000001C0)
#define DC_PHY_DC_DEBUG_rd_dbg_mod(data)                                             (0x000001C0&((data)<<6))
#define DC_PHY_DC_DEBUG_rd_dbg_mod_src(data)                                         ((0x000001C0&(data))>>6)
#define DC_PHY_DC_DEBUG_get_rd_dbg_mod(data)                                         ((0x000001C0&(data))>>6)
#define DC_PHY_DC_DEBUG_dbg_mod_shift                                                (0)
#define DC_PHY_DC_DEBUG_dbg_mod_mask                                                 (0x0000003F)
#define DC_PHY_DC_DEBUG_dbg_mod(data)                                                (0x0000003F&((data)<<0))
#define DC_PHY_DC_DEBUG_dbg_mod_src(data)                                            ((0x0000003F&(data))>>0)
#define DC_PHY_DC_DEBUG_get_dbg_mod(data)                                            ((0x0000003F&(data))>>0)


#define DC_PHY_PRE_CNT                                                               0x1800886C
#define DC_PHY_PRE_CNT_reg_addr                                                      "0xB800886C"
#define DC_PHY_PRE_CNT_reg                                                           0xB800886C
#define set_DC_PHY_PRE_CNT_reg(data)   (*((volatile unsigned int*) DC_PHY_PRE_CNT_reg)=data)
#define get_DC_PHY_PRE_CNT_reg   (*((volatile unsigned int*) DC_PHY_PRE_CNT_reg))
#define DC_PHY_PRE_CNT_inst_adr                                                      "0x001B"
#define DC_PHY_PRE_CNT_inst                                                          0x001B
#define DC_PHY_PRE_CNT_post_trig_cnt_shift                                           (16)
#define DC_PHY_PRE_CNT_post_trig_cnt_mask                                            (0xFFFF0000)
#define DC_PHY_PRE_CNT_post_trig_cnt(data)                                           (0xFFFF0000&((data)<<16))
#define DC_PHY_PRE_CNT_post_trig_cnt_src(data)                                       ((0xFFFF0000&(data))>>16)
#define DC_PHY_PRE_CNT_get_post_trig_cnt(data)                                       ((0xFFFF0000&(data))>>16)
#define DC_PHY_PRE_CNT_pre_trig_cnt_shift                                            (0)
#define DC_PHY_PRE_CNT_pre_trig_cnt_mask                                             (0x0000FFFF)
#define DC_PHY_PRE_CNT_pre_trig_cnt(data)                                            (0x0000FFFF&((data)<<0))
#define DC_PHY_PRE_CNT_pre_trig_cnt_src(data)                                        ((0x0000FFFF&(data))>>0)
#define DC_PHY_PRE_CNT_get_pre_trig_cnt(data)                                        ((0x0000FFFF&(data))>>0)


#define DC_PHY_WFIFO_SYS_REQ_WAIT                                                    0x18008870
#define DC_PHY_WFIFO_SYS_REQ_WAIT_reg_addr                                           "0xB8008870"
#define DC_PHY_WFIFO_SYS_REQ_WAIT_reg                                                0xB8008870
#define set_DC_PHY_WFIFO_SYS_REQ_WAIT_reg(data)   (*((volatile unsigned int*) DC_PHY_WFIFO_SYS_REQ_WAIT_reg)=data)
#define get_DC_PHY_WFIFO_SYS_REQ_WAIT_reg   (*((volatile unsigned int*) DC_PHY_WFIFO_SYS_REQ_WAIT_reg))
#define DC_PHY_WFIFO_SYS_REQ_WAIT_inst_adr                                           "0x001C"
#define DC_PHY_WFIFO_SYS_REQ_WAIT_inst                                               0x001C
#define DC_PHY_WFIFO_SYS_REQ_WAIT_wfifo_sys_req_wait_total_shift                     (0)
#define DC_PHY_WFIFO_SYS_REQ_WAIT_wfifo_sys_req_wait_total_mask                      (0xFFFFFFFF)
#define DC_PHY_WFIFO_SYS_REQ_WAIT_wfifo_sys_req_wait_total(data)                     (0xFFFFFFFF&((data)<<0))
#define DC_PHY_WFIFO_SYS_REQ_WAIT_wfifo_sys_req_wait_total_src(data)                 ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_WFIFO_SYS_REQ_WAIT_get_wfifo_sys_req_wait_total(data)                 ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_WFIFO_DDR_REQ_WAIT                                                    0x18008874
#define DC_PHY_WFIFO_DDR_REQ_WAIT_reg_addr                                           "0xB8008874"
#define DC_PHY_WFIFO_DDR_REQ_WAIT_reg                                                0xB8008874
#define set_DC_PHY_WFIFO_DDR_REQ_WAIT_reg(data)   (*((volatile unsigned int*) DC_PHY_WFIFO_DDR_REQ_WAIT_reg)=data)
#define get_DC_PHY_WFIFO_DDR_REQ_WAIT_reg   (*((volatile unsigned int*) DC_PHY_WFIFO_DDR_REQ_WAIT_reg))
#define DC_PHY_WFIFO_DDR_REQ_WAIT_inst_adr                                           "0x001D"
#define DC_PHY_WFIFO_DDR_REQ_WAIT_inst                                               0x001D
#define DC_PHY_WFIFO_DDR_REQ_WAIT_wfifo_ddr_req_wait_total_shift                     (0)
#define DC_PHY_WFIFO_DDR_REQ_WAIT_wfifo_ddr_req_wait_total_mask                      (0xFFFFFFFF)
#define DC_PHY_WFIFO_DDR_REQ_WAIT_wfifo_ddr_req_wait_total(data)                     (0xFFFFFFFF&((data)<<0))
#define DC_PHY_WFIFO_DDR_REQ_WAIT_wfifo_ddr_req_wait_total_src(data)                 ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_WFIFO_DDR_REQ_WAIT_get_wfifo_ddr_req_wait_total(data)                 ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_WFIFO_MAX_REQ_WAIT                                                    0x18008878
#define DC_PHY_WFIFO_MAX_REQ_WAIT_reg_addr                                           "0xB8008878"
#define DC_PHY_WFIFO_MAX_REQ_WAIT_reg                                                0xB8008878
#define set_DC_PHY_WFIFO_MAX_REQ_WAIT_reg(data)   (*((volatile unsigned int*) DC_PHY_WFIFO_MAX_REQ_WAIT_reg)=data)
#define get_DC_PHY_WFIFO_MAX_REQ_WAIT_reg   (*((volatile unsigned int*) DC_PHY_WFIFO_MAX_REQ_WAIT_reg))
#define DC_PHY_WFIFO_MAX_REQ_WAIT_inst_adr                                           "0x001E"
#define DC_PHY_WFIFO_MAX_REQ_WAIT_inst                                               0x001E
#define DC_PHY_WFIFO_MAX_REQ_WAIT_wfifo_ddr_req_wait_max_shift                       (16)
#define DC_PHY_WFIFO_MAX_REQ_WAIT_wfifo_ddr_req_wait_max_mask                        (0xFFFF0000)
#define DC_PHY_WFIFO_MAX_REQ_WAIT_wfifo_ddr_req_wait_max(data)                       (0xFFFF0000&((data)<<16))
#define DC_PHY_WFIFO_MAX_REQ_WAIT_wfifo_ddr_req_wait_max_src(data)                   ((0xFFFF0000&(data))>>16)
#define DC_PHY_WFIFO_MAX_REQ_WAIT_get_wfifo_ddr_req_wait_max(data)                   ((0xFFFF0000&(data))>>16)
#define DC_PHY_WFIFO_MAX_REQ_WAIT_wfifo_sys_req_wait_max_shift                       (0)
#define DC_PHY_WFIFO_MAX_REQ_WAIT_wfifo_sys_req_wait_max_mask                        (0x0000FFFF)
#define DC_PHY_WFIFO_MAX_REQ_WAIT_wfifo_sys_req_wait_max(data)                       (0x0000FFFF&((data)<<0))
#define DC_PHY_WFIFO_MAX_REQ_WAIT_wfifo_sys_req_wait_max_src(data)                   ((0x0000FFFF&(data))>>0)
#define DC_PHY_WFIFO_MAX_REQ_WAIT_get_wfifo_sys_req_wait_max(data)                   ((0x0000FFFF&(data))>>0)


#define DC_PHY_DC_WRITE_LEVEL_DQ                                                     0x1800887c
#define DC_PHY_DC_WRITE_LEVEL_DQ_reg_addr                                            "0xB800887C"
#define DC_PHY_DC_WRITE_LEVEL_DQ_reg                                                 0xB800887C
#define set_DC_PHY_DC_WRITE_LEVEL_DQ_reg(data)   (*((volatile unsigned int*) DC_PHY_DC_WRITE_LEVEL_DQ_reg)=data)
#define get_DC_PHY_DC_WRITE_LEVEL_DQ_reg   (*((volatile unsigned int*) DC_PHY_DC_WRITE_LEVEL_DQ_reg))
#define DC_PHY_DC_WRITE_LEVEL_DQ_inst_adr                                            "0x001F"
#define DC_PHY_DC_WRITE_LEVEL_DQ_inst                                                0x001F
#define DC_PHY_DC_WRITE_LEVEL_DQ_wr_level_rdata_shift                                (0)
#define DC_PHY_DC_WRITE_LEVEL_DQ_wr_level_rdata_mask                                 (0xFFFFFFFF)
#define DC_PHY_DC_WRITE_LEVEL_DQ_wr_level_rdata(data)                                (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DC_WRITE_LEVEL_DQ_wr_level_rdata_src(data)                            ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DC_WRITE_LEVEL_DQ_get_wr_level_rdata(data)                            ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DQ0_1_DLYN                                                            0x18008880
#define DC_PHY_DQ0_1_DLYN_reg_addr                                                   "0xB8008880"
#define DC_PHY_DQ0_1_DLYN_reg                                                        0xB8008880
#define set_DC_PHY_DQ0_1_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ0_1_DLYN_reg)=data)
#define get_DC_PHY_DQ0_1_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ0_1_DLYN_reg))
#define DC_PHY_DQ0_1_DLYN_inst_adr                                                   "0x0020"
#define DC_PHY_DQ0_1_DLYN_inst                                                       0x0020
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_neg_1_0_shift                                    (22)
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_neg_1_0_mask                                     (0x0FC00000)
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_neg_1_0(data)                                    (0x0FC00000&((data)<<22))
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_neg_1_0_src(data)                                ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ0_1_DLYN_get_ph_sel_dq_neg_1_0(data)                                ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_pos_1_0_shift                                    (16)
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_pos_1_0_mask                                     (0x003F0000)
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_pos_1_0(data)                                    (0x003F0000&((data)<<16))
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_pos_1_0_src(data)                                ((0x003F0000&(data))>>16)
#define DC_PHY_DQ0_1_DLYN_get_ph_sel_dq_pos_1_0(data)                                ((0x003F0000&(data))>>16)
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_neg_0_0_shift                                    (6)
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_neg_0_0_mask                                     (0x00000FC0)
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_neg_0_0(data)                                    (0x00000FC0&((data)<<6))
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_neg_0_0_src(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ0_1_DLYN_get_ph_sel_dq_neg_0_0(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_pos_0_0_shift                                    (0)
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_pos_0_0_mask                                     (0x0000003F)
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_pos_0_0(data)                                    (0x0000003F&((data)<<0))
#define DC_PHY_DQ0_1_DLYN_ph_sel_dq_pos_0_0_src(data)                                ((0x0000003F&(data))>>0)
#define DC_PHY_DQ0_1_DLYN_get_ph_sel_dq_pos_0_0(data)                                ((0x0000003F&(data))>>0)


#define DC_PHY_DQ2_3_DLYN                                                            0x18008884
#define DC_PHY_DQ2_3_DLYN_reg_addr                                                   "0xB8008884"
#define DC_PHY_DQ2_3_DLYN_reg                                                        0xB8008884
#define set_DC_PHY_DQ2_3_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ2_3_DLYN_reg)=data)
#define get_DC_PHY_DQ2_3_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ2_3_DLYN_reg))
#define DC_PHY_DQ2_3_DLYN_inst_adr                                                   "0x0021"
#define DC_PHY_DQ2_3_DLYN_inst                                                       0x0021
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_neg_3_0_shift                                    (22)
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_neg_3_0_mask                                     (0x0FC00000)
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_neg_3_0(data)                                    (0x0FC00000&((data)<<22))
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_neg_3_0_src(data)                                ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ2_3_DLYN_get_ph_sel_dq_neg_3_0(data)                                ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_pos_3_0_shift                                    (16)
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_pos_3_0_mask                                     (0x003F0000)
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_pos_3_0(data)                                    (0x003F0000&((data)<<16))
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_pos_3_0_src(data)                                ((0x003F0000&(data))>>16)
#define DC_PHY_DQ2_3_DLYN_get_ph_sel_dq_pos_3_0(data)                                ((0x003F0000&(data))>>16)
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_neg_2_0_shift                                    (6)
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_neg_2_0_mask                                     (0x00000FC0)
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_neg_2_0(data)                                    (0x00000FC0&((data)<<6))
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_neg_2_0_src(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ2_3_DLYN_get_ph_sel_dq_neg_2_0(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_pos_2_0_shift                                    (0)
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_pos_2_0_mask                                     (0x0000003F)
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_pos_2_0(data)                                    (0x0000003F&((data)<<0))
#define DC_PHY_DQ2_3_DLYN_ph_sel_dq_pos_2_0_src(data)                                ((0x0000003F&(data))>>0)
#define DC_PHY_DQ2_3_DLYN_get_ph_sel_dq_pos_2_0(data)                                ((0x0000003F&(data))>>0)


#define DC_PHY_DQ4_5_DLYN                                                            0x18008888
#define DC_PHY_DQ4_5_DLYN_reg_addr                                                   "0xB8008888"
#define DC_PHY_DQ4_5_DLYN_reg                                                        0xB8008888
#define set_DC_PHY_DQ4_5_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ4_5_DLYN_reg)=data)
#define get_DC_PHY_DQ4_5_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ4_5_DLYN_reg))
#define DC_PHY_DQ4_5_DLYN_inst_adr                                                   "0x0022"
#define DC_PHY_DQ4_5_DLYN_inst                                                       0x0022
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_neg_5_0_shift                                    (22)
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_neg_5_0_mask                                     (0x0FC00000)
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_neg_5_0(data)                                    (0x0FC00000&((data)<<22))
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_neg_5_0_src(data)                                ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ4_5_DLYN_get_ph_sel_dq_neg_5_0(data)                                ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_pos_5_0_shift                                    (16)
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_pos_5_0_mask                                     (0x003F0000)
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_pos_5_0(data)                                    (0x003F0000&((data)<<16))
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_pos_5_0_src(data)                                ((0x003F0000&(data))>>16)
#define DC_PHY_DQ4_5_DLYN_get_ph_sel_dq_pos_5_0(data)                                ((0x003F0000&(data))>>16)
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_neg_4_0_shift                                    (6)
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_neg_4_0_mask                                     (0x00000FC0)
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_neg_4_0(data)                                    (0x00000FC0&((data)<<6))
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_neg_4_0_src(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ4_5_DLYN_get_ph_sel_dq_neg_4_0(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_pos_4_0_shift                                    (0)
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_pos_4_0_mask                                     (0x0000003F)
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_pos_4_0(data)                                    (0x0000003F&((data)<<0))
#define DC_PHY_DQ4_5_DLYN_ph_sel_dq_pos_4_0_src(data)                                ((0x0000003F&(data))>>0)
#define DC_PHY_DQ4_5_DLYN_get_ph_sel_dq_pos_4_0(data)                                ((0x0000003F&(data))>>0)


#define DC_PHY_DQ6_7_DLYN                                                            0x1800888C
#define DC_PHY_DQ6_7_DLYN_reg_addr                                                   "0xB800888C"
#define DC_PHY_DQ6_7_DLYN_reg                                                        0xB800888C
#define set_DC_PHY_DQ6_7_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ6_7_DLYN_reg)=data)
#define get_DC_PHY_DQ6_7_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ6_7_DLYN_reg))
#define DC_PHY_DQ6_7_DLYN_inst_adr                                                   "0x0023"
#define DC_PHY_DQ6_7_DLYN_inst                                                       0x0023
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_neg_7_0_shift                                    (22)
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_neg_7_0_mask                                     (0x0FC00000)
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_neg_7_0(data)                                    (0x0FC00000&((data)<<22))
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_neg_7_0_src(data)                                ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ6_7_DLYN_get_ph_sel_dq_neg_7_0(data)                                ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_pos_7_0_shift                                    (16)
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_pos_7_0_mask                                     (0x003F0000)
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_pos_7_0(data)                                    (0x003F0000&((data)<<16))
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_pos_7_0_src(data)                                ((0x003F0000&(data))>>16)
#define DC_PHY_DQ6_7_DLYN_get_ph_sel_dq_pos_7_0(data)                                ((0x003F0000&(data))>>16)
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_neg_6_0_shift                                    (6)
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_neg_6_0_mask                                     (0x00000FC0)
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_neg_6_0(data)                                    (0x00000FC0&((data)<<6))
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_neg_6_0_src(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ6_7_DLYN_get_ph_sel_dq_neg_6_0(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_pos_6_0_shift                                    (0)
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_pos_6_0_mask                                     (0x0000003F)
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_pos_6_0(data)                                    (0x0000003F&((data)<<0))
#define DC_PHY_DQ6_7_DLYN_ph_sel_dq_pos_6_0_src(data)                                ((0x0000003F&(data))>>0)
#define DC_PHY_DQ6_7_DLYN_get_ph_sel_dq_pos_6_0(data)                                ((0x0000003F&(data))>>0)


#define DC_PHY_DQ8_9_DLYN                                                            0x18008890
#define DC_PHY_DQ8_9_DLYN_reg_addr                                                   "0xB8008890"
#define DC_PHY_DQ8_9_DLYN_reg                                                        0xB8008890
#define set_DC_PHY_DQ8_9_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ8_9_DLYN_reg)=data)
#define get_DC_PHY_DQ8_9_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ8_9_DLYN_reg))
#define DC_PHY_DQ8_9_DLYN_inst_adr                                                   "0x0024"
#define DC_PHY_DQ8_9_DLYN_inst                                                       0x0024
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_neg_1_1_shift                                    (22)
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_neg_1_1_mask                                     (0x0FC00000)
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_neg_1_1(data)                                    (0x0FC00000&((data)<<22))
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_neg_1_1_src(data)                                ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ8_9_DLYN_get_ph_sel_dq_neg_1_1(data)                                ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_pos_1_1_shift                                    (16)
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_pos_1_1_mask                                     (0x003F0000)
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_pos_1_1(data)                                    (0x003F0000&((data)<<16))
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_pos_1_1_src(data)                                ((0x003F0000&(data))>>16)
#define DC_PHY_DQ8_9_DLYN_get_ph_sel_dq_pos_1_1(data)                                ((0x003F0000&(data))>>16)
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_neg_0_1_shift                                    (6)
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_neg_0_1_mask                                     (0x00000FC0)
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_neg_0_1(data)                                    (0x00000FC0&((data)<<6))
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_neg_0_1_src(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ8_9_DLYN_get_ph_sel_dq_neg_0_1(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_pos_0_1_shift                                    (0)
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_pos_0_1_mask                                     (0x0000003F)
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_pos_0_1(data)                                    (0x0000003F&((data)<<0))
#define DC_PHY_DQ8_9_DLYN_ph_sel_dq_pos_0_1_src(data)                                ((0x0000003F&(data))>>0)
#define DC_PHY_DQ8_9_DLYN_get_ph_sel_dq_pos_0_1(data)                                ((0x0000003F&(data))>>0)


#define DC_PHY_DQ10_11_DLYN                                                          0x18008894
#define DC_PHY_DQ10_11_DLYN_reg_addr                                                 "0xB8008894"
#define DC_PHY_DQ10_11_DLYN_reg                                                      0xB8008894
#define set_DC_PHY_DQ10_11_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ10_11_DLYN_reg)=data)
#define get_DC_PHY_DQ10_11_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ10_11_DLYN_reg))
#define DC_PHY_DQ10_11_DLYN_inst_adr                                                 "0x0025"
#define DC_PHY_DQ10_11_DLYN_inst                                                     0x0025
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_neg_3_1_shift                                  (22)
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_neg_3_1_mask                                   (0x0FC00000)
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_neg_3_1(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_neg_3_1_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ10_11_DLYN_get_ph_sel_dq_neg_3_1(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_pos_3_1_shift                                  (16)
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_pos_3_1_mask                                   (0x003F0000)
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_pos_3_1(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_pos_3_1_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ10_11_DLYN_get_ph_sel_dq_pos_3_1(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_neg_2_1_shift                                  (6)
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_neg_2_1_mask                                   (0x00000FC0)
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_neg_2_1(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_neg_2_1_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ10_11_DLYN_get_ph_sel_dq_neg_2_1(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_pos_2_1_shift                                  (0)
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_pos_2_1_mask                                   (0x0000003F)
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_pos_2_1(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_DQ10_11_DLYN_ph_sel_dq_pos_2_1_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_DQ10_11_DLYN_get_ph_sel_dq_pos_2_1(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_DQ12_13_DLYN                                                          0x1800889C
#define DC_PHY_DQ12_13_DLYN_reg_addr                                                 "0xB800889C"
#define DC_PHY_DQ12_13_DLYN_reg                                                      0xB800889C
#define set_DC_PHY_DQ12_13_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ12_13_DLYN_reg)=data)
#define get_DC_PHY_DQ12_13_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ12_13_DLYN_reg))
#define DC_PHY_DQ12_13_DLYN_inst_adr                                                 "0x0027"
#define DC_PHY_DQ12_13_DLYN_inst                                                     0x0027
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_neg_5_1_shift                                  (22)
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_neg_5_1_mask                                   (0x0FC00000)
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_neg_5_1(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_neg_5_1_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ12_13_DLYN_get_ph_sel_dq_neg_5_1(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_pos_5_1_shift                                  (16)
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_pos_5_1_mask                                   (0x003F0000)
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_pos_5_1(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_pos_5_1_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ12_13_DLYN_get_ph_sel_dq_pos_5_1(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_neg_4_1_shift                                  (6)
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_neg_4_1_mask                                   (0x00000FC0)
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_neg_4_1(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_neg_4_1_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ12_13_DLYN_get_ph_sel_dq_neg_4_1(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_pos_4_1_shift                                  (0)
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_pos_4_1_mask                                   (0x0000003F)
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_pos_4_1(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_DQ12_13_DLYN_ph_sel_dq_pos_4_1_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_DQ12_13_DLYN_get_ph_sel_dq_pos_4_1(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_DQ14_15_DLYN                                                          0x180088A0
#define DC_PHY_DQ14_15_DLYN_reg_addr                                                 "0xB80088A0"
#define DC_PHY_DQ14_15_DLYN_reg                                                      0xB80088A0
#define set_DC_PHY_DQ14_15_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ14_15_DLYN_reg)=data)
#define get_DC_PHY_DQ14_15_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ14_15_DLYN_reg))
#define DC_PHY_DQ14_15_DLYN_inst_adr                                                 "0x0028"
#define DC_PHY_DQ14_15_DLYN_inst                                                     0x0028
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_neg_7_1_shift                                  (22)
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_neg_7_1_mask                                   (0x0FC00000)
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_neg_7_1(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_neg_7_1_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ14_15_DLYN_get_ph_sel_dq_neg_7_1(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_pos_7_1_shift                                  (16)
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_pos_7_1_mask                                   (0x003F0000)
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_pos_7_1(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_pos_7_1_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ14_15_DLYN_get_ph_sel_dq_pos_7_1(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_neg_6_1_shift                                  (6)
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_neg_6_1_mask                                   (0x00000FC0)
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_neg_6_1(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_neg_6_1_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ14_15_DLYN_get_ph_sel_dq_neg_6_1(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_pos_6_1_shift                                  (0)
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_pos_6_1_mask                                   (0x0000003F)
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_pos_6_1(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_DQ14_15_DLYN_ph_sel_dq_pos_6_1_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_DQ14_15_DLYN_get_ph_sel_dq_pos_6_1(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_DQ16_17_DLYN                                                          0x180088A4
#define DC_PHY_DQ16_17_DLYN_reg_addr                                                 "0xB80088A4"
#define DC_PHY_DQ16_17_DLYN_reg                                                      0xB80088A4
#define set_DC_PHY_DQ16_17_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ16_17_DLYN_reg)=data)
#define get_DC_PHY_DQ16_17_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ16_17_DLYN_reg))
#define DC_PHY_DQ16_17_DLYN_inst_adr                                                 "0x0029"
#define DC_PHY_DQ16_17_DLYN_inst                                                     0x0029
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_neg_1_2_shift                                  (22)
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_neg_1_2_mask                                   (0x0FC00000)
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_neg_1_2(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_neg_1_2_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ16_17_DLYN_get_ph_sel_dq_neg_1_2(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_pos_1_2_shift                                  (16)
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_pos_1_2_mask                                   (0x003F0000)
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_pos_1_2(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_pos_1_2_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ16_17_DLYN_get_ph_sel_dq_pos_1_2(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_neg_0_2_shift                                  (6)
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_neg_0_2_mask                                   (0x00000FC0)
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_neg_0_2(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_neg_0_2_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ16_17_DLYN_get_ph_sel_dq_neg_0_2(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_pos_0_2_shift                                  (0)
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_pos_0_2_mask                                   (0x0000003F)
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_pos_0_2(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_DQ16_17_DLYN_ph_sel_dq_pos_0_2_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_DQ16_17_DLYN_get_ph_sel_dq_pos_0_2(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_DQ18_19_DLYN                                                          0x180088A8
#define DC_PHY_DQ18_19_DLYN_reg_addr                                                 "0xB80088A8"
#define DC_PHY_DQ18_19_DLYN_reg                                                      0xB80088A8
#define set_DC_PHY_DQ18_19_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ18_19_DLYN_reg)=data)
#define get_DC_PHY_DQ18_19_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ18_19_DLYN_reg))
#define DC_PHY_DQ18_19_DLYN_inst_adr                                                 "0x002A"
#define DC_PHY_DQ18_19_DLYN_inst                                                     0x002A
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_neg_3_2_shift                                  (22)
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_neg_3_2_mask                                   (0x0FC00000)
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_neg_3_2(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_neg_3_2_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ18_19_DLYN_get_ph_sel_dq_neg_3_2(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_pos_3_2_shift                                  (16)
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_pos_3_2_mask                                   (0x003F0000)
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_pos_3_2(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_pos_3_2_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ18_19_DLYN_get_ph_sel_dq_pos_3_2(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_neg_2_2_shift                                  (6)
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_neg_2_2_mask                                   (0x00000FC0)
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_neg_2_2(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_neg_2_2_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ18_19_DLYN_get_ph_sel_dq_neg_2_2(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_pos_2_2_shift                                  (0)
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_pos_2_2_mask                                   (0x0000003F)
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_pos_2_2(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_DQ18_19_DLYN_ph_sel_dq_pos_2_2_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_DQ18_19_DLYN_get_ph_sel_dq_pos_2_2(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_DQ20_21_DLYN                                                          0x180088AC
#define DC_PHY_DQ20_21_DLYN_reg_addr                                                 "0xB80088AC"
#define DC_PHY_DQ20_21_DLYN_reg                                                      0xB80088AC
#define set_DC_PHY_DQ20_21_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ20_21_DLYN_reg)=data)
#define get_DC_PHY_DQ20_21_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ20_21_DLYN_reg))
#define DC_PHY_DQ20_21_DLYN_inst_adr                                                 "0x002B"
#define DC_PHY_DQ20_21_DLYN_inst                                                     0x002B
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_neg_5_2_shift                                  (22)
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_neg_5_2_mask                                   (0x0FC00000)
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_neg_5_2(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_neg_5_2_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ20_21_DLYN_get_ph_sel_dq_neg_5_2(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_pos_5_2_shift                                  (16)
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_pos_5_2_mask                                   (0x003F0000)
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_pos_5_2(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_pos_5_2_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ20_21_DLYN_get_ph_sel_dq_pos_5_2(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_neg_4_2_shift                                  (6)
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_neg_4_2_mask                                   (0x00000FC0)
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_neg_4_2(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_neg_4_2_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ20_21_DLYN_get_ph_sel_dq_neg_4_2(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_pos_4_2_shift                                  (0)
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_pos_4_2_mask                                   (0x0000003F)
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_pos_4_2(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_DQ20_21_DLYN_ph_sel_dq_pos_4_2_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_DQ20_21_DLYN_get_ph_sel_dq_pos_4_2(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_DQ22_23_DLYN                                                          0x180088B0
#define DC_PHY_DQ22_23_DLYN_reg_addr                                                 "0xB80088B0"
#define DC_PHY_DQ22_23_DLYN_reg                                                      0xB80088B0
#define set_DC_PHY_DQ22_23_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ22_23_DLYN_reg)=data)
#define get_DC_PHY_DQ22_23_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ22_23_DLYN_reg))
#define DC_PHY_DQ22_23_DLYN_inst_adr                                                 "0x002C"
#define DC_PHY_DQ22_23_DLYN_inst                                                     0x002C
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_neg_7_2_shift                                  (22)
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_neg_7_2_mask                                   (0x0FC00000)
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_neg_7_2(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_neg_7_2_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ22_23_DLYN_get_ph_sel_dq_neg_7_2(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_pos_7_2_shift                                  (16)
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_pos_7_2_mask                                   (0x003F0000)
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_pos_7_2(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_pos_7_2_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ22_23_DLYN_get_ph_sel_dq_pos_7_2(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_neg_6_2_shift                                  (6)
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_neg_6_2_mask                                   (0x00000FC0)
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_neg_6_2(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_neg_6_2_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ22_23_DLYN_get_ph_sel_dq_neg_6_2(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_pos_6_2_shift                                  (0)
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_pos_6_2_mask                                   (0x0000003F)
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_pos_6_2(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_DQ22_23_DLYN_ph_sel_dq_pos_6_2_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_DQ22_23_DLYN_get_ph_sel_dq_pos_6_2(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_DQ24_25_DLYN                                                          0x180088B4
#define DC_PHY_DQ24_25_DLYN_reg_addr                                                 "0xB80088B4"
#define DC_PHY_DQ24_25_DLYN_reg                                                      0xB80088B4
#define set_DC_PHY_DQ24_25_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ24_25_DLYN_reg)=data)
#define get_DC_PHY_DQ24_25_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ24_25_DLYN_reg))
#define DC_PHY_DQ24_25_DLYN_inst_adr                                                 "0x002D"
#define DC_PHY_DQ24_25_DLYN_inst                                                     0x002D
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_neg_1_3_shift                                  (22)
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_neg_1_3_mask                                   (0x0FC00000)
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_neg_1_3(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_neg_1_3_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ24_25_DLYN_get_ph_sel_dq_neg_1_3(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_pos_1_3_shift                                  (16)
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_pos_1_3_mask                                   (0x003F0000)
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_pos_1_3(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_pos_1_3_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ24_25_DLYN_get_ph_sel_dq_pos_1_3(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_neg_0_3_shift                                  (6)
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_neg_0_3_mask                                   (0x00000FC0)
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_neg_0_3(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_neg_0_3_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ24_25_DLYN_get_ph_sel_dq_neg_0_3(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_pos_0_3_shift                                  (0)
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_pos_0_3_mask                                   (0x0000003F)
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_pos_0_3(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_DQ24_25_DLYN_ph_sel_dq_pos_0_3_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_DQ24_25_DLYN_get_ph_sel_dq_pos_0_3(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_DQ26_27_DLYN                                                          0x180088B8
#define DC_PHY_DQ26_27_DLYN_reg_addr                                                 "0xB80088B8"
#define DC_PHY_DQ26_27_DLYN_reg                                                      0xB80088B8
#define set_DC_PHY_DQ26_27_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ26_27_DLYN_reg)=data)
#define get_DC_PHY_DQ26_27_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ26_27_DLYN_reg))
#define DC_PHY_DQ26_27_DLYN_inst_adr                                                 "0x002E"
#define DC_PHY_DQ26_27_DLYN_inst                                                     0x002E
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_neg_3_3_shift                                  (22)
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_neg_3_3_mask                                   (0x0FC00000)
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_neg_3_3(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_neg_3_3_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ26_27_DLYN_get_ph_sel_dq_neg_3_3(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_pos_3_3_shift                                  (16)
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_pos_3_3_mask                                   (0x003F0000)
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_pos_3_3(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_pos_3_3_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ26_27_DLYN_get_ph_sel_dq_pos_3_3(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_neg_2_3_shift                                  (6)
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_neg_2_3_mask                                   (0x00000FC0)
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_neg_2_3(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_neg_2_3_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ26_27_DLYN_get_ph_sel_dq_neg_2_3(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_pos_2_3_shift                                  (0)
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_pos_2_3_mask                                   (0x0000003F)
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_pos_2_3(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_DQ26_27_DLYN_ph_sel_dq_pos_2_3_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_DQ26_27_DLYN_get_ph_sel_dq_pos_2_3(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_DQ28_29_DLYN                                                          0x180088BC
#define DC_PHY_DQ28_29_DLYN_reg_addr                                                 "0xB80088BC"
#define DC_PHY_DQ28_29_DLYN_reg                                                      0xB80088BC
#define set_DC_PHY_DQ28_29_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ28_29_DLYN_reg)=data)
#define get_DC_PHY_DQ28_29_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ28_29_DLYN_reg))
#define DC_PHY_DQ28_29_DLYN_inst_adr                                                 "0x002F"
#define DC_PHY_DQ28_29_DLYN_inst                                                     0x002F
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_neg_5_3_shift                                  (22)
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_neg_5_3_mask                                   (0x0FC00000)
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_neg_5_3(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_neg_5_3_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ28_29_DLYN_get_ph_sel_dq_neg_5_3(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_pos_5_3_shift                                  (16)
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_pos_5_3_mask                                   (0x003F0000)
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_pos_5_3(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_pos_5_3_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ28_29_DLYN_get_ph_sel_dq_pos_5_3(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_neg_4_3_shift                                  (6)
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_neg_4_3_mask                                   (0x00000FC0)
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_neg_4_3(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_neg_4_3_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ28_29_DLYN_get_ph_sel_dq_neg_4_3(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_pos_4_3_shift                                  (0)
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_pos_4_3_mask                                   (0x0000003F)
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_pos_4_3(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_DQ28_29_DLYN_ph_sel_dq_pos_4_3_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_DQ28_29_DLYN_get_ph_sel_dq_pos_4_3(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_DQ30_31_DLYN                                                          0x180088C0
#define DC_PHY_DQ30_31_DLYN_reg_addr                                                 "0xB80088C0"
#define DC_PHY_DQ30_31_DLYN_reg                                                      0xB80088C0
#define set_DC_PHY_DQ30_31_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ30_31_DLYN_reg)=data)
#define get_DC_PHY_DQ30_31_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQ30_31_DLYN_reg))
#define DC_PHY_DQ30_31_DLYN_inst_adr                                                 "0x0030"
#define DC_PHY_DQ30_31_DLYN_inst                                                     0x0030
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_neg_7_3_shift                                  (22)
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_neg_7_3_mask                                   (0x0FC00000)
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_neg_7_3(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_neg_7_3_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ30_31_DLYN_get_ph_sel_dq_neg_7_3(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_pos_7_3_shift                                  (16)
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_pos_7_3_mask                                   (0x003F0000)
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_pos_7_3(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_pos_7_3_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ30_31_DLYN_get_ph_sel_dq_pos_7_3(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_neg_6_3_shift                                  (6)
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_neg_6_3_mask                                   (0x00000FC0)
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_neg_6_3(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_neg_6_3_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ30_31_DLYN_get_ph_sel_dq_neg_6_3(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_pos_6_3_shift                                  (0)
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_pos_6_3_mask                                   (0x0000003F)
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_pos_6_3(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_DQ30_31_DLYN_ph_sel_dq_pos_6_3_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_DQ30_31_DLYN_get_ph_sel_dq_pos_6_3(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_CAL0_1_DLYN                                                           0x180088C4
#define DC_PHY_CAL0_1_DLYN_reg_addr                                                  "0xB80088C4"
#define DC_PHY_CAL0_1_DLYN_reg                                                       0xB80088C4
#define set_DC_PHY_CAL0_1_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL0_1_DLYN_reg)=data)
#define get_DC_PHY_CAL0_1_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL0_1_DLYN_reg))
#define DC_PHY_CAL0_1_DLYN_inst_adr                                                  "0x0031"
#define DC_PHY_CAL0_1_DLYN_inst                                                      0x0031
#define DC_PHY_CAL0_1_DLYN_non_valid_shift                                           (31)
#define DC_PHY_CAL0_1_DLYN_non_valid_mask                                            (0x80000000)
#define DC_PHY_CAL0_1_DLYN_non_valid(data)                                           (0x80000000&((data)<<31))
#define DC_PHY_CAL0_1_DLYN_non_valid_src(data)                                       ((0x80000000&(data))>>31)
#define DC_PHY_CAL0_1_DLYN_get_non_valid(data)                                       ((0x80000000&(data))>>31)
#define DC_PHY_CAL0_1_DLYN_cal_dq1_neg_dlyn_0_shift                                  (22)
#define DC_PHY_CAL0_1_DLYN_cal_dq1_neg_dlyn_0_mask                                   (0x0FC00000)
#define DC_PHY_CAL0_1_DLYN_cal_dq1_neg_dlyn_0(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_CAL0_1_DLYN_cal_dq1_neg_dlyn_0_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL0_1_DLYN_get_cal_dq1_neg_dlyn_0(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL0_1_DLYN_cal_dq1_pos_dlyn_0_shift                                  (16)
#define DC_PHY_CAL0_1_DLYN_cal_dq1_pos_dlyn_0_mask                                   (0x003F0000)
#define DC_PHY_CAL0_1_DLYN_cal_dq1_pos_dlyn_0(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_CAL0_1_DLYN_cal_dq1_pos_dlyn_0_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_CAL0_1_DLYN_get_cal_dq1_pos_dlyn_0(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_CAL0_1_DLYN_cal_dq0_neg_dlyn_0_shift                                  (6)
#define DC_PHY_CAL0_1_DLYN_cal_dq0_neg_dlyn_0_mask                                   (0x00000FC0)
#define DC_PHY_CAL0_1_DLYN_cal_dq0_neg_dlyn_0(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_CAL0_1_DLYN_cal_dq0_neg_dlyn_0_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL0_1_DLYN_get_cal_dq0_neg_dlyn_0(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL0_1_DLYN_cal_dq0_pos_dlyn_0_shift                                  (0)
#define DC_PHY_CAL0_1_DLYN_cal_dq0_pos_dlyn_0_mask                                   (0x0000003F)
#define DC_PHY_CAL0_1_DLYN_cal_dq0_pos_dlyn_0(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_CAL0_1_DLYN_cal_dq0_pos_dlyn_0_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_CAL0_1_DLYN_get_cal_dq0_pos_dlyn_0(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_CAL2_3_DLYN                                                           0x180088C8
#define DC_PHY_CAL2_3_DLYN_reg_addr                                                  "0xB80088C8"
#define DC_PHY_CAL2_3_DLYN_reg                                                       0xB80088C8
#define set_DC_PHY_CAL2_3_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL2_3_DLYN_reg)=data)
#define get_DC_PHY_CAL2_3_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL2_3_DLYN_reg))
#define DC_PHY_CAL2_3_DLYN_inst_adr                                                  "0x0032"
#define DC_PHY_CAL2_3_DLYN_inst                                                      0x0032
#define DC_PHY_CAL2_3_DLYN_non_valid_shift                                           (31)
#define DC_PHY_CAL2_3_DLYN_non_valid_mask                                            (0x80000000)
#define DC_PHY_CAL2_3_DLYN_non_valid(data)                                           (0x80000000&((data)<<31))
#define DC_PHY_CAL2_3_DLYN_non_valid_src(data)                                       ((0x80000000&(data))>>31)
#define DC_PHY_CAL2_3_DLYN_get_non_valid(data)                                       ((0x80000000&(data))>>31)
#define DC_PHY_CAL2_3_DLYN_cal_dq3_neg_dlyn_0_shift                                  (22)
#define DC_PHY_CAL2_3_DLYN_cal_dq3_neg_dlyn_0_mask                                   (0x0FC00000)
#define DC_PHY_CAL2_3_DLYN_cal_dq3_neg_dlyn_0(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_CAL2_3_DLYN_cal_dq3_neg_dlyn_0_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL2_3_DLYN_get_cal_dq3_neg_dlyn_0(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL2_3_DLYN_cal_dq3_pos_dlyn_0_shift                                  (16)
#define DC_PHY_CAL2_3_DLYN_cal_dq3_pos_dlyn_0_mask                                   (0x003F0000)
#define DC_PHY_CAL2_3_DLYN_cal_dq3_pos_dlyn_0(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_CAL2_3_DLYN_cal_dq3_pos_dlyn_0_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_CAL2_3_DLYN_get_cal_dq3_pos_dlyn_0(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_CAL2_3_DLYN_cal_dq2_neg_dlyn_0_shift                                  (6)
#define DC_PHY_CAL2_3_DLYN_cal_dq2_neg_dlyn_0_mask                                   (0x00000FC0)
#define DC_PHY_CAL2_3_DLYN_cal_dq2_neg_dlyn_0(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_CAL2_3_DLYN_cal_dq2_neg_dlyn_0_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL2_3_DLYN_get_cal_dq2_neg_dlyn_0(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL2_3_DLYN_cal_dq2_pos_dlyn_0_shift                                  (0)
#define DC_PHY_CAL2_3_DLYN_cal_dq2_pos_dlyn_0_mask                                   (0x0000003F)
#define DC_PHY_CAL2_3_DLYN_cal_dq2_pos_dlyn_0(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_CAL2_3_DLYN_cal_dq2_pos_dlyn_0_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_CAL2_3_DLYN_get_cal_dq2_pos_dlyn_0(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_CAL4_5_DLYN                                                           0x180088CC
#define DC_PHY_CAL4_5_DLYN_reg_addr                                                  "0xB80088CC"
#define DC_PHY_CAL4_5_DLYN_reg                                                       0xB80088CC
#define set_DC_PHY_CAL4_5_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL4_5_DLYN_reg)=data)
#define get_DC_PHY_CAL4_5_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL4_5_DLYN_reg))
#define DC_PHY_CAL4_5_DLYN_inst_adr                                                  "0x0033"
#define DC_PHY_CAL4_5_DLYN_inst                                                      0x0033
#define DC_PHY_CAL4_5_DLYN_non_valid_shift                                           (31)
#define DC_PHY_CAL4_5_DLYN_non_valid_mask                                            (0x80000000)
#define DC_PHY_CAL4_5_DLYN_non_valid(data)                                           (0x80000000&((data)<<31))
#define DC_PHY_CAL4_5_DLYN_non_valid_src(data)                                       ((0x80000000&(data))>>31)
#define DC_PHY_CAL4_5_DLYN_get_non_valid(data)                                       ((0x80000000&(data))>>31)
#define DC_PHY_CAL4_5_DLYN_cal_dq5_neg_dlyn_0_shift                                  (22)
#define DC_PHY_CAL4_5_DLYN_cal_dq5_neg_dlyn_0_mask                                   (0x0FC00000)
#define DC_PHY_CAL4_5_DLYN_cal_dq5_neg_dlyn_0(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_CAL4_5_DLYN_cal_dq5_neg_dlyn_0_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL4_5_DLYN_get_cal_dq5_neg_dlyn_0(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL4_5_DLYN_cal_dq5_pos_dlyn_0_shift                                  (16)
#define DC_PHY_CAL4_5_DLYN_cal_dq5_pos_dlyn_0_mask                                   (0x003F0000)
#define DC_PHY_CAL4_5_DLYN_cal_dq5_pos_dlyn_0(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_CAL4_5_DLYN_cal_dq5_pos_dlyn_0_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_CAL4_5_DLYN_get_cal_dq5_pos_dlyn_0(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_CAL4_5_DLYN_cal_dq4_neg_dlyn_0_shift                                  (6)
#define DC_PHY_CAL4_5_DLYN_cal_dq4_neg_dlyn_0_mask                                   (0x00000FC0)
#define DC_PHY_CAL4_5_DLYN_cal_dq4_neg_dlyn_0(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_CAL4_5_DLYN_cal_dq4_neg_dlyn_0_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL4_5_DLYN_get_cal_dq4_neg_dlyn_0(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL4_5_DLYN_cal_dq4_pos_dlyn_0_shift                                  (0)
#define DC_PHY_CAL4_5_DLYN_cal_dq4_pos_dlyn_0_mask                                   (0x0000003F)
#define DC_PHY_CAL4_5_DLYN_cal_dq4_pos_dlyn_0(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_CAL4_5_DLYN_cal_dq4_pos_dlyn_0_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_CAL4_5_DLYN_get_cal_dq4_pos_dlyn_0(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_CAL6_7_DLYN                                                           0x180088D0
#define DC_PHY_CAL6_7_DLYN_reg_addr                                                  "0xB80088D0"
#define DC_PHY_CAL6_7_DLYN_reg                                                       0xB80088D0
#define set_DC_PHY_CAL6_7_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL6_7_DLYN_reg)=data)
#define get_DC_PHY_CAL6_7_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL6_7_DLYN_reg))
#define DC_PHY_CAL6_7_DLYN_inst_adr                                                  "0x0034"
#define DC_PHY_CAL6_7_DLYN_inst                                                      0x0034
#define DC_PHY_CAL6_7_DLYN_non_valid_shift                                           (31)
#define DC_PHY_CAL6_7_DLYN_non_valid_mask                                            (0x80000000)
#define DC_PHY_CAL6_7_DLYN_non_valid(data)                                           (0x80000000&((data)<<31))
#define DC_PHY_CAL6_7_DLYN_non_valid_src(data)                                       ((0x80000000&(data))>>31)
#define DC_PHY_CAL6_7_DLYN_get_non_valid(data)                                       ((0x80000000&(data))>>31)
#define DC_PHY_CAL6_7_DLYN_cal_dq7_neg_dlyn_0_shift                                  (22)
#define DC_PHY_CAL6_7_DLYN_cal_dq7_neg_dlyn_0_mask                                   (0x0FC00000)
#define DC_PHY_CAL6_7_DLYN_cal_dq7_neg_dlyn_0(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_CAL6_7_DLYN_cal_dq7_neg_dlyn_0_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL6_7_DLYN_get_cal_dq7_neg_dlyn_0(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL6_7_DLYN_cal_dq7_pos_dlyn_0_shift                                  (16)
#define DC_PHY_CAL6_7_DLYN_cal_dq7_pos_dlyn_0_mask                                   (0x003F0000)
#define DC_PHY_CAL6_7_DLYN_cal_dq7_pos_dlyn_0(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_CAL6_7_DLYN_cal_dq7_pos_dlyn_0_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_CAL6_7_DLYN_get_cal_dq7_pos_dlyn_0(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_CAL6_7_DLYN_cal_dq6_neg_dlyn_0_shift                                  (6)
#define DC_PHY_CAL6_7_DLYN_cal_dq6_neg_dlyn_0_mask                                   (0x00000FC0)
#define DC_PHY_CAL6_7_DLYN_cal_dq6_neg_dlyn_0(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_CAL6_7_DLYN_cal_dq6_neg_dlyn_0_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL6_7_DLYN_get_cal_dq6_neg_dlyn_0(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL6_7_DLYN_cal_dq6_pos_dlyn_0_shift                                  (0)
#define DC_PHY_CAL6_7_DLYN_cal_dq6_pos_dlyn_0_mask                                   (0x0000003F)
#define DC_PHY_CAL6_7_DLYN_cal_dq6_pos_dlyn_0(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_CAL6_7_DLYN_cal_dq6_pos_dlyn_0_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_CAL6_7_DLYN_get_cal_dq6_pos_dlyn_0(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_CAL8_9_DLYN                                                           0x180088D4
#define DC_PHY_CAL8_9_DLYN_reg_addr                                                  "0xB80088D4"
#define DC_PHY_CAL8_9_DLYN_reg                                                       0xB80088D4
#define set_DC_PHY_CAL8_9_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL8_9_DLYN_reg)=data)
#define get_DC_PHY_CAL8_9_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL8_9_DLYN_reg))
#define DC_PHY_CAL8_9_DLYN_inst_adr                                                  "0x0035"
#define DC_PHY_CAL8_9_DLYN_inst                                                      0x0035
#define DC_PHY_CAL8_9_DLYN_non_valid_shift                                           (31)
#define DC_PHY_CAL8_9_DLYN_non_valid_mask                                            (0x80000000)
#define DC_PHY_CAL8_9_DLYN_non_valid(data)                                           (0x80000000&((data)<<31))
#define DC_PHY_CAL8_9_DLYN_non_valid_src(data)                                       ((0x80000000&(data))>>31)
#define DC_PHY_CAL8_9_DLYN_get_non_valid(data)                                       ((0x80000000&(data))>>31)
#define DC_PHY_CAL8_9_DLYN_cal_dq1_neg_dlyn_1_shift                                  (22)
#define DC_PHY_CAL8_9_DLYN_cal_dq1_neg_dlyn_1_mask                                   (0x0FC00000)
#define DC_PHY_CAL8_9_DLYN_cal_dq1_neg_dlyn_1(data)                                  (0x0FC00000&((data)<<22))
#define DC_PHY_CAL8_9_DLYN_cal_dq1_neg_dlyn_1_src(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL8_9_DLYN_get_cal_dq1_neg_dlyn_1(data)                              ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL8_9_DLYN_cal_dq1_pos_dlyn_1_shift                                  (16)
#define DC_PHY_CAL8_9_DLYN_cal_dq1_pos_dlyn_1_mask                                   (0x003F0000)
#define DC_PHY_CAL8_9_DLYN_cal_dq1_pos_dlyn_1(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_CAL8_9_DLYN_cal_dq1_pos_dlyn_1_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_CAL8_9_DLYN_get_cal_dq1_pos_dlyn_1(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_CAL8_9_DLYN_cal_dq0_neg_dlyn_1_shift                                  (6)
#define DC_PHY_CAL8_9_DLYN_cal_dq0_neg_dlyn_1_mask                                   (0x00000FC0)
#define DC_PHY_CAL8_9_DLYN_cal_dq0_neg_dlyn_1(data)                                  (0x00000FC0&((data)<<6))
#define DC_PHY_CAL8_9_DLYN_cal_dq0_neg_dlyn_1_src(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL8_9_DLYN_get_cal_dq0_neg_dlyn_1(data)                              ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL8_9_DLYN_cal_dq0_pos_dlyn_1_shift                                  (0)
#define DC_PHY_CAL8_9_DLYN_cal_dq0_pos_dlyn_1_mask                                   (0x0000003F)
#define DC_PHY_CAL8_9_DLYN_cal_dq0_pos_dlyn_1(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_CAL8_9_DLYN_cal_dq0_pos_dlyn_1_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_CAL8_9_DLYN_get_cal_dq0_pos_dlyn_1(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_CAL10_11_DLYN                                                         0x180088D8
#define DC_PHY_CAL10_11_DLYN_reg_addr                                                "0xB80088D8"
#define DC_PHY_CAL10_11_DLYN_reg                                                     0xB80088D8
#define set_DC_PHY_CAL10_11_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL10_11_DLYN_reg)=data)
#define get_DC_PHY_CAL10_11_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL10_11_DLYN_reg))
#define DC_PHY_CAL10_11_DLYN_inst_adr                                                "0x0036"
#define DC_PHY_CAL10_11_DLYN_inst                                                    0x0036
#define DC_PHY_CAL10_11_DLYN_non_valid_shift                                         (31)
#define DC_PHY_CAL10_11_DLYN_non_valid_mask                                          (0x80000000)
#define DC_PHY_CAL10_11_DLYN_non_valid(data)                                         (0x80000000&((data)<<31))
#define DC_PHY_CAL10_11_DLYN_non_valid_src(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL10_11_DLYN_get_non_valid(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL10_11_DLYN_cal_dq3_neg_dlyn_1_shift                                (22)
#define DC_PHY_CAL10_11_DLYN_cal_dq3_neg_dlyn_1_mask                                 (0x0FC00000)
#define DC_PHY_CAL10_11_DLYN_cal_dq3_neg_dlyn_1(data)                                (0x0FC00000&((data)<<22))
#define DC_PHY_CAL10_11_DLYN_cal_dq3_neg_dlyn_1_src(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL10_11_DLYN_get_cal_dq3_neg_dlyn_1(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL10_11_DLYN_cal_dq3_pos_dlyn_1_shift                                (16)
#define DC_PHY_CAL10_11_DLYN_cal_dq3_pos_dlyn_1_mask                                 (0x003F0000)
#define DC_PHY_CAL10_11_DLYN_cal_dq3_pos_dlyn_1(data)                                (0x003F0000&((data)<<16))
#define DC_PHY_CAL10_11_DLYN_cal_dq3_pos_dlyn_1_src(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL10_11_DLYN_get_cal_dq3_pos_dlyn_1(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL10_11_DLYN_cal_dq2_neg_dlyn_1_shift                                (6)
#define DC_PHY_CAL10_11_DLYN_cal_dq2_neg_dlyn_1_mask                                 (0x00000FC0)
#define DC_PHY_CAL10_11_DLYN_cal_dq2_neg_dlyn_1(data)                                (0x00000FC0&((data)<<6))
#define DC_PHY_CAL10_11_DLYN_cal_dq2_neg_dlyn_1_src(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL10_11_DLYN_get_cal_dq2_neg_dlyn_1(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL10_11_DLYN_cal_dq2_pos_dlyn_1_shift                                (0)
#define DC_PHY_CAL10_11_DLYN_cal_dq2_pos_dlyn_1_mask                                 (0x0000003F)
#define DC_PHY_CAL10_11_DLYN_cal_dq2_pos_dlyn_1(data)                                (0x0000003F&((data)<<0))
#define DC_PHY_CAL10_11_DLYN_cal_dq2_pos_dlyn_1_src(data)                            ((0x0000003F&(data))>>0)
#define DC_PHY_CAL10_11_DLYN_get_cal_dq2_pos_dlyn_1(data)                            ((0x0000003F&(data))>>0)


#define DC_PHY_CAL12_13_DLYN                                                         0x180088DC
#define DC_PHY_CAL12_13_DLYN_reg_addr                                                "0xB80088DC"
#define DC_PHY_CAL12_13_DLYN_reg                                                     0xB80088DC
#define set_DC_PHY_CAL12_13_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL12_13_DLYN_reg)=data)
#define get_DC_PHY_CAL12_13_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL12_13_DLYN_reg))
#define DC_PHY_CAL12_13_DLYN_inst_adr                                                "0x0037"
#define DC_PHY_CAL12_13_DLYN_inst                                                    0x0037
#define DC_PHY_CAL12_13_DLYN_non_valid_shift                                         (31)
#define DC_PHY_CAL12_13_DLYN_non_valid_mask                                          (0x80000000)
#define DC_PHY_CAL12_13_DLYN_non_valid(data)                                         (0x80000000&((data)<<31))
#define DC_PHY_CAL12_13_DLYN_non_valid_src(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL12_13_DLYN_get_non_valid(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL12_13_DLYN_cal_dq5_neg_dlyn_1_shift                                (22)
#define DC_PHY_CAL12_13_DLYN_cal_dq5_neg_dlyn_1_mask                                 (0x0FC00000)
#define DC_PHY_CAL12_13_DLYN_cal_dq5_neg_dlyn_1(data)                                (0x0FC00000&((data)<<22))
#define DC_PHY_CAL12_13_DLYN_cal_dq5_neg_dlyn_1_src(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL12_13_DLYN_get_cal_dq5_neg_dlyn_1(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL12_13_DLYN_cal_dq5_pos_dlyn_1_shift                                (16)
#define DC_PHY_CAL12_13_DLYN_cal_dq5_pos_dlyn_1_mask                                 (0x003F0000)
#define DC_PHY_CAL12_13_DLYN_cal_dq5_pos_dlyn_1(data)                                (0x003F0000&((data)<<16))
#define DC_PHY_CAL12_13_DLYN_cal_dq5_pos_dlyn_1_src(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL12_13_DLYN_get_cal_dq5_pos_dlyn_1(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL12_13_DLYN_cal_dq4_neg_dlyn_1_shift                                (6)
#define DC_PHY_CAL12_13_DLYN_cal_dq4_neg_dlyn_1_mask                                 (0x00000FC0)
#define DC_PHY_CAL12_13_DLYN_cal_dq4_neg_dlyn_1(data)                                (0x00000FC0&((data)<<6))
#define DC_PHY_CAL12_13_DLYN_cal_dq4_neg_dlyn_1_src(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL12_13_DLYN_get_cal_dq4_neg_dlyn_1(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL12_13_DLYN_cal_dq4_pos_dlyn_1_shift                                (0)
#define DC_PHY_CAL12_13_DLYN_cal_dq4_pos_dlyn_1_mask                                 (0x0000003F)
#define DC_PHY_CAL12_13_DLYN_cal_dq4_pos_dlyn_1(data)                                (0x0000003F&((data)<<0))
#define DC_PHY_CAL12_13_DLYN_cal_dq4_pos_dlyn_1_src(data)                            ((0x0000003F&(data))>>0)
#define DC_PHY_CAL12_13_DLYN_get_cal_dq4_pos_dlyn_1(data)                            ((0x0000003F&(data))>>0)


#define DC_PHY_CAL14_15_DLYN                                                         0x180088E0
#define DC_PHY_CAL14_15_DLYN_reg_addr                                                "0xB80088E0"
#define DC_PHY_CAL14_15_DLYN_reg                                                     0xB80088E0
#define set_DC_PHY_CAL14_15_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL14_15_DLYN_reg)=data)
#define get_DC_PHY_CAL14_15_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL14_15_DLYN_reg))
#define DC_PHY_CAL14_15_DLYN_inst_adr                                                "0x0038"
#define DC_PHY_CAL14_15_DLYN_inst                                                    0x0038
#define DC_PHY_CAL14_15_DLYN_non_valid_shift                                         (31)
#define DC_PHY_CAL14_15_DLYN_non_valid_mask                                          (0x80000000)
#define DC_PHY_CAL14_15_DLYN_non_valid(data)                                         (0x80000000&((data)<<31))
#define DC_PHY_CAL14_15_DLYN_non_valid_src(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL14_15_DLYN_get_non_valid(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL14_15_DLYN_cal_dq7_neg_dlyn_1_shift                                (22)
#define DC_PHY_CAL14_15_DLYN_cal_dq7_neg_dlyn_1_mask                                 (0x0FC00000)
#define DC_PHY_CAL14_15_DLYN_cal_dq7_neg_dlyn_1(data)                                (0x0FC00000&((data)<<22))
#define DC_PHY_CAL14_15_DLYN_cal_dq7_neg_dlyn_1_src(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL14_15_DLYN_get_cal_dq7_neg_dlyn_1(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL14_15_DLYN_cal_dq7_pos_dlyn_1_shift                                (16)
#define DC_PHY_CAL14_15_DLYN_cal_dq7_pos_dlyn_1_mask                                 (0x003F0000)
#define DC_PHY_CAL14_15_DLYN_cal_dq7_pos_dlyn_1(data)                                (0x003F0000&((data)<<16))
#define DC_PHY_CAL14_15_DLYN_cal_dq7_pos_dlyn_1_src(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL14_15_DLYN_get_cal_dq7_pos_dlyn_1(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL14_15_DLYN_cal_dq6_neg_dlyn_1_shift                                (6)
#define DC_PHY_CAL14_15_DLYN_cal_dq6_neg_dlyn_1_mask                                 (0x00000FC0)
#define DC_PHY_CAL14_15_DLYN_cal_dq6_neg_dlyn_1(data)                                (0x00000FC0&((data)<<6))
#define DC_PHY_CAL14_15_DLYN_cal_dq6_neg_dlyn_1_src(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL14_15_DLYN_get_cal_dq6_neg_dlyn_1(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL14_15_DLYN_cal_dq6_pos_dlyn_1_shift                                (0)
#define DC_PHY_CAL14_15_DLYN_cal_dq6_pos_dlyn_1_mask                                 (0x0000003F)
#define DC_PHY_CAL14_15_DLYN_cal_dq6_pos_dlyn_1(data)                                (0x0000003F&((data)<<0))
#define DC_PHY_CAL14_15_DLYN_cal_dq6_pos_dlyn_1_src(data)                            ((0x0000003F&(data))>>0)
#define DC_PHY_CAL14_15_DLYN_get_cal_dq6_pos_dlyn_1(data)                            ((0x0000003F&(data))>>0)


#define DC_PHY_CAL16_17_DLYN                                                         0x180088E4
#define DC_PHY_CAL16_17_DLYN_reg_addr                                                "0xB80088E4"
#define DC_PHY_CAL16_17_DLYN_reg                                                     0xB80088E4
#define set_DC_PHY_CAL16_17_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL16_17_DLYN_reg)=data)
#define get_DC_PHY_CAL16_17_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL16_17_DLYN_reg))
#define DC_PHY_CAL16_17_DLYN_inst_adr                                                "0x0039"
#define DC_PHY_CAL16_17_DLYN_inst                                                    0x0039
#define DC_PHY_CAL16_17_DLYN_non_valid_shift                                         (31)
#define DC_PHY_CAL16_17_DLYN_non_valid_mask                                          (0x80000000)
#define DC_PHY_CAL16_17_DLYN_non_valid(data)                                         (0x80000000&((data)<<31))
#define DC_PHY_CAL16_17_DLYN_non_valid_src(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL16_17_DLYN_get_non_valid(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL16_17_DLYN_cal_dq1_neg_dlyn_2_shift                                (22)
#define DC_PHY_CAL16_17_DLYN_cal_dq1_neg_dlyn_2_mask                                 (0x0FC00000)
#define DC_PHY_CAL16_17_DLYN_cal_dq1_neg_dlyn_2(data)                                (0x0FC00000&((data)<<22))
#define DC_PHY_CAL16_17_DLYN_cal_dq1_neg_dlyn_2_src(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL16_17_DLYN_get_cal_dq1_neg_dlyn_2(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL16_17_DLYN_cal_dq1_pos_dlyn_2_shift                                (16)
#define DC_PHY_CAL16_17_DLYN_cal_dq1_pos_dlyn_2_mask                                 (0x003F0000)
#define DC_PHY_CAL16_17_DLYN_cal_dq1_pos_dlyn_2(data)                                (0x003F0000&((data)<<16))
#define DC_PHY_CAL16_17_DLYN_cal_dq1_pos_dlyn_2_src(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL16_17_DLYN_get_cal_dq1_pos_dlyn_2(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL16_17_DLYN_cal_dq0_neg_dlyn_2_shift                                (6)
#define DC_PHY_CAL16_17_DLYN_cal_dq0_neg_dlyn_2_mask                                 (0x00000FC0)
#define DC_PHY_CAL16_17_DLYN_cal_dq0_neg_dlyn_2(data)                                (0x00000FC0&((data)<<6))
#define DC_PHY_CAL16_17_DLYN_cal_dq0_neg_dlyn_2_src(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL16_17_DLYN_get_cal_dq0_neg_dlyn_2(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL16_17_DLYN_cal_dq0_pos_dlyn_2_shift                                (0)
#define DC_PHY_CAL16_17_DLYN_cal_dq0_pos_dlyn_2_mask                                 (0x0000003F)
#define DC_PHY_CAL16_17_DLYN_cal_dq0_pos_dlyn_2(data)                                (0x0000003F&((data)<<0))
#define DC_PHY_CAL16_17_DLYN_cal_dq0_pos_dlyn_2_src(data)                            ((0x0000003F&(data))>>0)
#define DC_PHY_CAL16_17_DLYN_get_cal_dq0_pos_dlyn_2(data)                            ((0x0000003F&(data))>>0)


#define DC_PHY_CAL18_19_DLYN                                                         0x180088E8
#define DC_PHY_CAL18_19_DLYN_reg_addr                                                "0xB80088E8"
#define DC_PHY_CAL18_19_DLYN_reg                                                     0xB80088E8
#define set_DC_PHY_CAL18_19_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL18_19_DLYN_reg)=data)
#define get_DC_PHY_CAL18_19_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL18_19_DLYN_reg))
#define DC_PHY_CAL18_19_DLYN_inst_adr                                                "0x003A"
#define DC_PHY_CAL18_19_DLYN_inst                                                    0x003A
#define DC_PHY_CAL18_19_DLYN_non_valid_shift                                         (31)
#define DC_PHY_CAL18_19_DLYN_non_valid_mask                                          (0x80000000)
#define DC_PHY_CAL18_19_DLYN_non_valid(data)                                         (0x80000000&((data)<<31))
#define DC_PHY_CAL18_19_DLYN_non_valid_src(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL18_19_DLYN_get_non_valid(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL18_19_DLYN_cal_dq3_neg_dlyn_2_shift                                (22)
#define DC_PHY_CAL18_19_DLYN_cal_dq3_neg_dlyn_2_mask                                 (0x0FC00000)
#define DC_PHY_CAL18_19_DLYN_cal_dq3_neg_dlyn_2(data)                                (0x0FC00000&((data)<<22))
#define DC_PHY_CAL18_19_DLYN_cal_dq3_neg_dlyn_2_src(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL18_19_DLYN_get_cal_dq3_neg_dlyn_2(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL18_19_DLYN_cal_dq3_pos_dlyn_2_shift                                (16)
#define DC_PHY_CAL18_19_DLYN_cal_dq3_pos_dlyn_2_mask                                 (0x003F0000)
#define DC_PHY_CAL18_19_DLYN_cal_dq3_pos_dlyn_2(data)                                (0x003F0000&((data)<<16))
#define DC_PHY_CAL18_19_DLYN_cal_dq3_pos_dlyn_2_src(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL18_19_DLYN_get_cal_dq3_pos_dlyn_2(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL18_19_DLYN_cal_dq2_neg_dlyn_2_shift                                (6)
#define DC_PHY_CAL18_19_DLYN_cal_dq2_neg_dlyn_2_mask                                 (0x00000FC0)
#define DC_PHY_CAL18_19_DLYN_cal_dq2_neg_dlyn_2(data)                                (0x00000FC0&((data)<<6))
#define DC_PHY_CAL18_19_DLYN_cal_dq2_neg_dlyn_2_src(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL18_19_DLYN_get_cal_dq2_neg_dlyn_2(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL18_19_DLYN_cal_dq2_pos_dlyn_2_shift                                (0)
#define DC_PHY_CAL18_19_DLYN_cal_dq2_pos_dlyn_2_mask                                 (0x0000003F)
#define DC_PHY_CAL18_19_DLYN_cal_dq2_pos_dlyn_2(data)                                (0x0000003F&((data)<<0))
#define DC_PHY_CAL18_19_DLYN_cal_dq2_pos_dlyn_2_src(data)                            ((0x0000003F&(data))>>0)
#define DC_PHY_CAL18_19_DLYN_get_cal_dq2_pos_dlyn_2(data)                            ((0x0000003F&(data))>>0)


#define DC_PHY_CAL20_21_DLYN                                                         0x180088EC
#define DC_PHY_CAL20_21_DLYN_reg_addr                                                "0xB80088EC"
#define DC_PHY_CAL20_21_DLYN_reg                                                     0xB80088EC
#define set_DC_PHY_CAL20_21_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL20_21_DLYN_reg)=data)
#define get_DC_PHY_CAL20_21_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL20_21_DLYN_reg))
#define DC_PHY_CAL20_21_DLYN_inst_adr                                                "0x003B"
#define DC_PHY_CAL20_21_DLYN_inst                                                    0x003B
#define DC_PHY_CAL20_21_DLYN_non_valid_shift                                         (31)
#define DC_PHY_CAL20_21_DLYN_non_valid_mask                                          (0x80000000)
#define DC_PHY_CAL20_21_DLYN_non_valid(data)                                         (0x80000000&((data)<<31))
#define DC_PHY_CAL20_21_DLYN_non_valid_src(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL20_21_DLYN_get_non_valid(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL20_21_DLYN_cal_dq5_neg_dlyn_2_shift                                (22)
#define DC_PHY_CAL20_21_DLYN_cal_dq5_neg_dlyn_2_mask                                 (0x0FC00000)
#define DC_PHY_CAL20_21_DLYN_cal_dq5_neg_dlyn_2(data)                                (0x0FC00000&((data)<<22))
#define DC_PHY_CAL20_21_DLYN_cal_dq5_neg_dlyn_2_src(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL20_21_DLYN_get_cal_dq5_neg_dlyn_2(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL20_21_DLYN_cal_dq5_pos_dlyn_2_shift                                (16)
#define DC_PHY_CAL20_21_DLYN_cal_dq5_pos_dlyn_2_mask                                 (0x003F0000)
#define DC_PHY_CAL20_21_DLYN_cal_dq5_pos_dlyn_2(data)                                (0x003F0000&((data)<<16))
#define DC_PHY_CAL20_21_DLYN_cal_dq5_pos_dlyn_2_src(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL20_21_DLYN_get_cal_dq5_pos_dlyn_2(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL20_21_DLYN_cal_dq4_neg_dlyn_2_shift                                (6)
#define DC_PHY_CAL20_21_DLYN_cal_dq4_neg_dlyn_2_mask                                 (0x00000FC0)
#define DC_PHY_CAL20_21_DLYN_cal_dq4_neg_dlyn_2(data)                                (0x00000FC0&((data)<<6))
#define DC_PHY_CAL20_21_DLYN_cal_dq4_neg_dlyn_2_src(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL20_21_DLYN_get_cal_dq4_neg_dlyn_2(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL20_21_DLYN_cal_dq4_pos_dlyn_2_shift                                (0)
#define DC_PHY_CAL20_21_DLYN_cal_dq4_pos_dlyn_2_mask                                 (0x0000003F)
#define DC_PHY_CAL20_21_DLYN_cal_dq4_pos_dlyn_2(data)                                (0x0000003F&((data)<<0))
#define DC_PHY_CAL20_21_DLYN_cal_dq4_pos_dlyn_2_src(data)                            ((0x0000003F&(data))>>0)
#define DC_PHY_CAL20_21_DLYN_get_cal_dq4_pos_dlyn_2(data)                            ((0x0000003F&(data))>>0)


#define DC_PHY_CAL22_23_DLYN                                                         0x180088F0
#define DC_PHY_CAL22_23_DLYN_reg_addr                                                "0xB80088F0"
#define DC_PHY_CAL22_23_DLYN_reg                                                     0xB80088F0
#define set_DC_PHY_CAL22_23_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL22_23_DLYN_reg)=data)
#define get_DC_PHY_CAL22_23_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL22_23_DLYN_reg))
#define DC_PHY_CAL22_23_DLYN_inst_adr                                                "0x003C"
#define DC_PHY_CAL22_23_DLYN_inst                                                    0x003C
#define DC_PHY_CAL22_23_DLYN_non_valid_shift                                         (31)
#define DC_PHY_CAL22_23_DLYN_non_valid_mask                                          (0x80000000)
#define DC_PHY_CAL22_23_DLYN_non_valid(data)                                         (0x80000000&((data)<<31))
#define DC_PHY_CAL22_23_DLYN_non_valid_src(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL22_23_DLYN_get_non_valid(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL22_23_DLYN_cal_dq7_neg_dlyn_2_shift                                (22)
#define DC_PHY_CAL22_23_DLYN_cal_dq7_neg_dlyn_2_mask                                 (0x0FC00000)
#define DC_PHY_CAL22_23_DLYN_cal_dq7_neg_dlyn_2(data)                                (0x0FC00000&((data)<<22))
#define DC_PHY_CAL22_23_DLYN_cal_dq7_neg_dlyn_2_src(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL22_23_DLYN_get_cal_dq7_neg_dlyn_2(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL22_23_DLYN_cal_dq7_pos_dlyn_2_shift                                (16)
#define DC_PHY_CAL22_23_DLYN_cal_dq7_pos_dlyn_2_mask                                 (0x003F0000)
#define DC_PHY_CAL22_23_DLYN_cal_dq7_pos_dlyn_2(data)                                (0x003F0000&((data)<<16))
#define DC_PHY_CAL22_23_DLYN_cal_dq7_pos_dlyn_2_src(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL22_23_DLYN_get_cal_dq7_pos_dlyn_2(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL22_23_DLYN_cal_dq6_neg_dlyn_2_shift                                (6)
#define DC_PHY_CAL22_23_DLYN_cal_dq6_neg_dlyn_2_mask                                 (0x00000FC0)
#define DC_PHY_CAL22_23_DLYN_cal_dq6_neg_dlyn_2(data)                                (0x00000FC0&((data)<<6))
#define DC_PHY_CAL22_23_DLYN_cal_dq6_neg_dlyn_2_src(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL22_23_DLYN_get_cal_dq6_neg_dlyn_2(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL22_23_DLYN_cal_dq6_pos_dlyn_2_shift                                (0)
#define DC_PHY_CAL22_23_DLYN_cal_dq6_pos_dlyn_2_mask                                 (0x0000003F)
#define DC_PHY_CAL22_23_DLYN_cal_dq6_pos_dlyn_2(data)                                (0x0000003F&((data)<<0))
#define DC_PHY_CAL22_23_DLYN_cal_dq6_pos_dlyn_2_src(data)                            ((0x0000003F&(data))>>0)
#define DC_PHY_CAL22_23_DLYN_get_cal_dq6_pos_dlyn_2(data)                            ((0x0000003F&(data))>>0)


#define DC_PHY_CAL24_25_DLYN                                                         0x180088F4
#define DC_PHY_CAL24_25_DLYN_reg_addr                                                "0xB80088F4"
#define DC_PHY_CAL24_25_DLYN_reg                                                     0xB80088F4
#define set_DC_PHY_CAL24_25_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL24_25_DLYN_reg)=data)
#define get_DC_PHY_CAL24_25_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL24_25_DLYN_reg))
#define DC_PHY_CAL24_25_DLYN_inst_adr                                                "0x003D"
#define DC_PHY_CAL24_25_DLYN_inst                                                    0x003D
#define DC_PHY_CAL24_25_DLYN_non_valid_shift                                         (31)
#define DC_PHY_CAL24_25_DLYN_non_valid_mask                                          (0x80000000)
#define DC_PHY_CAL24_25_DLYN_non_valid(data)                                         (0x80000000&((data)<<31))
#define DC_PHY_CAL24_25_DLYN_non_valid_src(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL24_25_DLYN_get_non_valid(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL24_25_DLYN_cal_dq1_neg_dlyn_3_shift                                (22)
#define DC_PHY_CAL24_25_DLYN_cal_dq1_neg_dlyn_3_mask                                 (0x0FC00000)
#define DC_PHY_CAL24_25_DLYN_cal_dq1_neg_dlyn_3(data)                                (0x0FC00000&((data)<<22))
#define DC_PHY_CAL24_25_DLYN_cal_dq1_neg_dlyn_3_src(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL24_25_DLYN_get_cal_dq1_neg_dlyn_3(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL24_25_DLYN_cal_dq1_pos_dlyn_3_shift                                (16)
#define DC_PHY_CAL24_25_DLYN_cal_dq1_pos_dlyn_3_mask                                 (0x003F0000)
#define DC_PHY_CAL24_25_DLYN_cal_dq1_pos_dlyn_3(data)                                (0x003F0000&((data)<<16))
#define DC_PHY_CAL24_25_DLYN_cal_dq1_pos_dlyn_3_src(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL24_25_DLYN_get_cal_dq1_pos_dlyn_3(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL24_25_DLYN_cal_dq0_neg_dlyn_3_shift                                (6)
#define DC_PHY_CAL24_25_DLYN_cal_dq0_neg_dlyn_3_mask                                 (0x00000FC0)
#define DC_PHY_CAL24_25_DLYN_cal_dq0_neg_dlyn_3(data)                                (0x00000FC0&((data)<<6))
#define DC_PHY_CAL24_25_DLYN_cal_dq0_neg_dlyn_3_src(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL24_25_DLYN_get_cal_dq0_neg_dlyn_3(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL24_25_DLYN_cal_dq0_pos_dlyn_3_shift                                (0)
#define DC_PHY_CAL24_25_DLYN_cal_dq0_pos_dlyn_3_mask                                 (0x0000003F)
#define DC_PHY_CAL24_25_DLYN_cal_dq0_pos_dlyn_3(data)                                (0x0000003F&((data)<<0))
#define DC_PHY_CAL24_25_DLYN_cal_dq0_pos_dlyn_3_src(data)                            ((0x0000003F&(data))>>0)
#define DC_PHY_CAL24_25_DLYN_get_cal_dq0_pos_dlyn_3(data)                            ((0x0000003F&(data))>>0)


#define DC_PHY_CAL26_27_DLYN                                                         0x180088F8
#define DC_PHY_CAL26_27_DLYN_reg_addr                                                "0xB80088F8"
#define DC_PHY_CAL26_27_DLYN_reg                                                     0xB80088F8
#define set_DC_PHY_CAL26_27_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL26_27_DLYN_reg)=data)
#define get_DC_PHY_CAL26_27_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL26_27_DLYN_reg))
#define DC_PHY_CAL26_27_DLYN_inst_adr                                                "0x003E"
#define DC_PHY_CAL26_27_DLYN_inst                                                    0x003E
#define DC_PHY_CAL26_27_DLYN_non_valid_shift                                         (31)
#define DC_PHY_CAL26_27_DLYN_non_valid_mask                                          (0x80000000)
#define DC_PHY_CAL26_27_DLYN_non_valid(data)                                         (0x80000000&((data)<<31))
#define DC_PHY_CAL26_27_DLYN_non_valid_src(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL26_27_DLYN_get_non_valid(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL26_27_DLYN_cal_dq3_neg_dlyn_3_shift                                (22)
#define DC_PHY_CAL26_27_DLYN_cal_dq3_neg_dlyn_3_mask                                 (0x0FC00000)
#define DC_PHY_CAL26_27_DLYN_cal_dq3_neg_dlyn_3(data)                                (0x0FC00000&((data)<<22))
#define DC_PHY_CAL26_27_DLYN_cal_dq3_neg_dlyn_3_src(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL26_27_DLYN_get_cal_dq3_neg_dlyn_3(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL26_27_DLYN_cal_dq3_pos_dlyn_3_shift                                (16)
#define DC_PHY_CAL26_27_DLYN_cal_dq3_pos_dlyn_3_mask                                 (0x003F0000)
#define DC_PHY_CAL26_27_DLYN_cal_dq3_pos_dlyn_3(data)                                (0x003F0000&((data)<<16))
#define DC_PHY_CAL26_27_DLYN_cal_dq3_pos_dlyn_3_src(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL26_27_DLYN_get_cal_dq3_pos_dlyn_3(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL26_27_DLYN_cal_dq2_neg_dlyn_3_shift                                (6)
#define DC_PHY_CAL26_27_DLYN_cal_dq2_neg_dlyn_3_mask                                 (0x00000FC0)
#define DC_PHY_CAL26_27_DLYN_cal_dq2_neg_dlyn_3(data)                                (0x00000FC0&((data)<<6))
#define DC_PHY_CAL26_27_DLYN_cal_dq2_neg_dlyn_3_src(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL26_27_DLYN_get_cal_dq2_neg_dlyn_3(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL26_27_DLYN_cal_dq2_pos_dlyn_3_shift                                (0)
#define DC_PHY_CAL26_27_DLYN_cal_dq2_pos_dlyn_3_mask                                 (0x0000003F)
#define DC_PHY_CAL26_27_DLYN_cal_dq2_pos_dlyn_3(data)                                (0x0000003F&((data)<<0))
#define DC_PHY_CAL26_27_DLYN_cal_dq2_pos_dlyn_3_src(data)                            ((0x0000003F&(data))>>0)
#define DC_PHY_CAL26_27_DLYN_get_cal_dq2_pos_dlyn_3(data)                            ((0x0000003F&(data))>>0)


#define DC_PHY_CAL28_29_DLYN                                                         0x180088FC
#define DC_PHY_CAL28_29_DLYN_reg_addr                                                "0xB80088FC"
#define DC_PHY_CAL28_29_DLYN_reg                                                     0xB80088FC
#define set_DC_PHY_CAL28_29_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL28_29_DLYN_reg)=data)
#define get_DC_PHY_CAL28_29_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL28_29_DLYN_reg))
#define DC_PHY_CAL28_29_DLYN_inst_adr                                                "0x003F"
#define DC_PHY_CAL28_29_DLYN_inst                                                    0x003F
#define DC_PHY_CAL28_29_DLYN_non_valid_shift                                         (31)
#define DC_PHY_CAL28_29_DLYN_non_valid_mask                                          (0x80000000)
#define DC_PHY_CAL28_29_DLYN_non_valid(data)                                         (0x80000000&((data)<<31))
#define DC_PHY_CAL28_29_DLYN_non_valid_src(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL28_29_DLYN_get_non_valid(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL28_29_DLYN_cal_dq5_neg_dlyn_3_shift                                (22)
#define DC_PHY_CAL28_29_DLYN_cal_dq5_neg_dlyn_3_mask                                 (0x0FC00000)
#define DC_PHY_CAL28_29_DLYN_cal_dq5_neg_dlyn_3(data)                                (0x0FC00000&((data)<<22))
#define DC_PHY_CAL28_29_DLYN_cal_dq5_neg_dlyn_3_src(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL28_29_DLYN_get_cal_dq5_neg_dlyn_3(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL28_29_DLYN_cal_dq5_pos_dlyn_3_shift                                (16)
#define DC_PHY_CAL28_29_DLYN_cal_dq5_pos_dlyn_3_mask                                 (0x003F0000)
#define DC_PHY_CAL28_29_DLYN_cal_dq5_pos_dlyn_3(data)                                (0x003F0000&((data)<<16))
#define DC_PHY_CAL28_29_DLYN_cal_dq5_pos_dlyn_3_src(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL28_29_DLYN_get_cal_dq5_pos_dlyn_3(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL28_29_DLYN_cal_dq4_neg_dlyn_3_shift                                (6)
#define DC_PHY_CAL28_29_DLYN_cal_dq4_neg_dlyn_3_mask                                 (0x00000FC0)
#define DC_PHY_CAL28_29_DLYN_cal_dq4_neg_dlyn_3(data)                                (0x00000FC0&((data)<<6))
#define DC_PHY_CAL28_29_DLYN_cal_dq4_neg_dlyn_3_src(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL28_29_DLYN_get_cal_dq4_neg_dlyn_3(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL28_29_DLYN_cal_dq4_pos_dlyn_3_shift                                (0)
#define DC_PHY_CAL28_29_DLYN_cal_dq4_pos_dlyn_3_mask                                 (0x0000003F)
#define DC_PHY_CAL28_29_DLYN_cal_dq4_pos_dlyn_3(data)                                (0x0000003F&((data)<<0))
#define DC_PHY_CAL28_29_DLYN_cal_dq4_pos_dlyn_3_src(data)                            ((0x0000003F&(data))>>0)
#define DC_PHY_CAL28_29_DLYN_get_cal_dq4_pos_dlyn_3(data)                            ((0x0000003F&(data))>>0)


#define DC_PHY_CAL30_31_DLYN                                                         0x18008900
#define DC_PHY_CAL30_31_DLYN_reg_addr                                                "0xB8008900"
#define DC_PHY_CAL30_31_DLYN_reg                                                     0xB8008900
#define set_DC_PHY_CAL30_31_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL30_31_DLYN_reg)=data)
#define get_DC_PHY_CAL30_31_DLYN_reg   (*((volatile unsigned int*) DC_PHY_CAL30_31_DLYN_reg))
#define DC_PHY_CAL30_31_DLYN_inst_adr                                                "0x0040"
#define DC_PHY_CAL30_31_DLYN_inst                                                    0x0040
#define DC_PHY_CAL30_31_DLYN_non_valid_shift                                         (31)
#define DC_PHY_CAL30_31_DLYN_non_valid_mask                                          (0x80000000)
#define DC_PHY_CAL30_31_DLYN_non_valid(data)                                         (0x80000000&((data)<<31))
#define DC_PHY_CAL30_31_DLYN_non_valid_src(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL30_31_DLYN_get_non_valid(data)                                     ((0x80000000&(data))>>31)
#define DC_PHY_CAL30_31_DLYN_cal_dq7_neg_dlyn_3_shift                                (22)
#define DC_PHY_CAL30_31_DLYN_cal_dq7_neg_dlyn_3_mask                                 (0x0FC00000)
#define DC_PHY_CAL30_31_DLYN_cal_dq7_neg_dlyn_3(data)                                (0x0FC00000&((data)<<22))
#define DC_PHY_CAL30_31_DLYN_cal_dq7_neg_dlyn_3_src(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL30_31_DLYN_get_cal_dq7_neg_dlyn_3(data)                            ((0x0FC00000&(data))>>22)
#define DC_PHY_CAL30_31_DLYN_cal_dq7_pos_dlyn_3_shift                                (16)
#define DC_PHY_CAL30_31_DLYN_cal_dq7_pos_dlyn_3_mask                                 (0x003F0000)
#define DC_PHY_CAL30_31_DLYN_cal_dq7_pos_dlyn_3(data)                                (0x003F0000&((data)<<16))
#define DC_PHY_CAL30_31_DLYN_cal_dq7_pos_dlyn_3_src(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL30_31_DLYN_get_cal_dq7_pos_dlyn_3(data)                            ((0x003F0000&(data))>>16)
#define DC_PHY_CAL30_31_DLYN_cal_dq6_neg_dlyn_3_shift                                (6)
#define DC_PHY_CAL30_31_DLYN_cal_dq6_neg_dlyn_3_mask                                 (0x00000FC0)
#define DC_PHY_CAL30_31_DLYN_cal_dq6_neg_dlyn_3(data)                                (0x00000FC0&((data)<<6))
#define DC_PHY_CAL30_31_DLYN_cal_dq6_neg_dlyn_3_src(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL30_31_DLYN_get_cal_dq6_neg_dlyn_3(data)                            ((0x00000FC0&(data))>>6)
#define DC_PHY_CAL30_31_DLYN_cal_dq6_pos_dlyn_3_shift                                (0)
#define DC_PHY_CAL30_31_DLYN_cal_dq6_pos_dlyn_3_mask                                 (0x0000003F)
#define DC_PHY_CAL30_31_DLYN_cal_dq6_pos_dlyn_3(data)                                (0x0000003F&((data)<<0))
#define DC_PHY_CAL30_31_DLYN_cal_dq6_pos_dlyn_3_src(data)                            ((0x0000003F&(data))>>0)
#define DC_PHY_CAL30_31_DLYN_get_cal_dq6_pos_dlyn_3(data)                            ((0x0000003F&(data))>>0)


#define DC_PHY_READ_COM_CTRL                                                         0x18008904
#define DC_PHY_READ_COM_CTRL_reg_addr                                                "0xB8008904"
#define DC_PHY_READ_COM_CTRL_reg                                                     0xB8008904
#define set_DC_PHY_READ_COM_CTRL_reg(data)   (*((volatile unsigned int*) DC_PHY_READ_COM_CTRL_reg)=data)
#define get_DC_PHY_READ_COM_CTRL_reg   (*((volatile unsigned int*) DC_PHY_READ_COM_CTRL_reg))
#define DC_PHY_READ_COM_CTRL_inst_adr                                                "0x0041"
#define DC_PHY_READ_COM_CTRL_inst                                                    0x0041
#define DC_PHY_READ_COM_CTRL_read_lat_sel_shift                                      (14)
#define DC_PHY_READ_COM_CTRL_read_lat_sel_mask                                       (0x00004000)
#define DC_PHY_READ_COM_CTRL_read_lat_sel(data)                                      (0x00004000&((data)<<14))
#define DC_PHY_READ_COM_CTRL_read_lat_sel_src(data)                                  ((0x00004000&(data))>>14)
#define DC_PHY_READ_COM_CTRL_get_read_lat_sel(data)                                  ((0x00004000&(data))>>14)
#define DC_PHY_READ_COM_CTRL_read_lat_shift                                          (12)
#define DC_PHY_READ_COM_CTRL_read_lat_mask                                           (0x00003000)
#define DC_PHY_READ_COM_CTRL_read_lat(data)                                          (0x00003000&((data)<<12))
#define DC_PHY_READ_COM_CTRL_read_lat_src(data)                                      ((0x00003000&(data))>>12)
#define DC_PHY_READ_COM_CTRL_get_read_lat(data)                                      ((0x00003000&(data))>>12)
#define DC_PHY_READ_COM_CTRL_ph_sel_read23_shift                                     (8)
#define DC_PHY_READ_COM_CTRL_ph_sel_read23_mask                                      (0x00000F00)
#define DC_PHY_READ_COM_CTRL_ph_sel_read23(data)                                     (0x00000F00&((data)<<8))
#define DC_PHY_READ_COM_CTRL_ph_sel_read23_src(data)                                 ((0x00000F00&(data))>>8)
#define DC_PHY_READ_COM_CTRL_get_ph_sel_read23(data)                                 ((0x00000F00&(data))>>8)
#define DC_PHY_READ_COM_CTRL_ph_sel_read01_shift                                     (4)
#define DC_PHY_READ_COM_CTRL_ph_sel_read01_mask                                      (0x000000F0)
#define DC_PHY_READ_COM_CTRL_ph_sel_read01(data)                                     (0x000000F0&((data)<<4))
#define DC_PHY_READ_COM_CTRL_ph_sel_read01_src(data)                                 ((0x000000F0&(data))>>4)
#define DC_PHY_READ_COM_CTRL_get_ph_sel_read01(data)                                 ((0x000000F0&(data))>>4)
#define DC_PHY_READ_COM_CTRL_read_com_sel_shift                                      (0)
#define DC_PHY_READ_COM_CTRL_read_com_sel_mask                                       (0x00000001)
#define DC_PHY_READ_COM_CTRL_read_com_sel(data)                                      (0x00000001&((data)<<0))
#define DC_PHY_READ_COM_CTRL_read_com_sel_src(data)                                  ((0x00000001&(data))>>0)
#define DC_PHY_READ_COM_CTRL_get_read_com_sel(data)                                  ((0x00000001&(data))>>0)


#define DC_PHY_CAL_CTRL                                                              0x18008908
#define DC_PHY_CAL_CTRL_reg_addr                                                     "0xB8008908"
#define DC_PHY_CAL_CTRL_reg                                                          0xB8008908
#define set_DC_PHY_CAL_CTRL_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL_CTRL_reg)=data)
#define get_DC_PHY_CAL_CTRL_reg   (*((volatile unsigned int*) DC_PHY_CAL_CTRL_reg))
#define DC_PHY_CAL_CTRL_inst_adr                                                     "0x0042"
#define DC_PHY_CAL_CTRL_inst                                                         0x0042
#define DC_PHY_CAL_CTRL_pos_trig_sel_shift                                           (8)
#define DC_PHY_CAL_CTRL_pos_trig_sel_mask                                            (0x00000700)
#define DC_PHY_CAL_CTRL_pos_trig_sel(data)                                           (0x00000700&((data)<<8))
#define DC_PHY_CAL_CTRL_pos_trig_sel_src(data)                                       ((0x00000700&(data))>>8)
#define DC_PHY_CAL_CTRL_get_pos_trig_sel(data)                                       ((0x00000700&(data))>>8)
#define DC_PHY_CAL_CTRL_pre_trig_sel_shift                                           (4)
#define DC_PHY_CAL_CTRL_pre_trig_sel_mask                                            (0x00000070)
#define DC_PHY_CAL_CTRL_pre_trig_sel(data)                                           (0x00000070&((data)<<4))
#define DC_PHY_CAL_CTRL_pre_trig_sel_src(data)                                       ((0x00000070&(data))>>4)
#define DC_PHY_CAL_CTRL_get_pre_trig_sel(data)                                       ((0x00000070&(data))>>4)
#define DC_PHY_CAL_CTRL_sync_cal_dlyn_shift                                          (1)
#define DC_PHY_CAL_CTRL_sync_cal_dlyn_mask                                           (0x00000002)
#define DC_PHY_CAL_CTRL_sync_cal_dlyn(data)                                          (0x00000002&((data)<<1))
#define DC_PHY_CAL_CTRL_sync_cal_dlyn_src(data)                                      ((0x00000002&(data))>>1)
#define DC_PHY_CAL_CTRL_get_sync_cal_dlyn(data)                                      ((0x00000002&(data))>>1)
#define DC_PHY_CAL_CTRL_auto_cal_shift                                               (0)
#define DC_PHY_CAL_CTRL_auto_cal_mask                                                (0x00000001)
#define DC_PHY_CAL_CTRL_auto_cal(data)                                               (0x00000001&((data)<<0))
#define DC_PHY_CAL_CTRL_auto_cal_src(data)                                           ((0x00000001&(data))>>0)
#define DC_PHY_CAL_CTRL_get_auto_cal(data)                                           ((0x00000001&(data))>>0)


#define DC_PHY_FIFO_DLYN                                                             0x1800890C
#define DC_PHY_FIFO_DLYN_reg_addr                                                    "0xB800890C"
#define DC_PHY_FIFO_DLYN_reg                                                         0xB800890C
#define set_DC_PHY_FIFO_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_DLYN_reg)=data)
#define get_DC_PHY_FIFO_DLYN_reg   (*((volatile unsigned int*) DC_PHY_FIFO_DLYN_reg))
#define DC_PHY_FIFO_DLYN_inst_adr                                                    "0x0043"
#define DC_PHY_FIFO_DLYN_inst                                                        0x0043
#define DC_PHY_FIFO_DLYN_gated_latch_sel_shift                                       (17)
#define DC_PHY_FIFO_DLYN_gated_latch_sel_mask                                        (0x00020000)
#define DC_PHY_FIFO_DLYN_gated_latch_sel(data)                                       (0x00020000&((data)<<17))
#define DC_PHY_FIFO_DLYN_gated_latch_sel_src(data)                                   ((0x00020000&(data))>>17)
#define DC_PHY_FIFO_DLYN_get_gated_latch_sel(data)                                   ((0x00020000&(data))>>17)
#define DC_PHY_FIFO_DLYN_clk_ddr_phy_mux_div2_0_ph_sel_shift                         (16)
#define DC_PHY_FIFO_DLYN_clk_ddr_phy_mux_div2_0_ph_sel_mask                          (0x00010000)
#define DC_PHY_FIFO_DLYN_clk_ddr_phy_mux_div2_0_ph_sel(data)                         (0x00010000&((data)<<16))
#define DC_PHY_FIFO_DLYN_clk_ddr_phy_mux_div2_0_ph_sel_src(data)                     ((0x00010000&(data))>>16)
#define DC_PHY_FIFO_DLYN_get_clk_ddr_phy_mux_div2_0_ph_sel(data)                     ((0x00010000&(data))>>16)
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_odd_1_ph_sel_shift                             (15)
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_odd_1_ph_sel_mask                              (0x00008000)
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_odd_1_ph_sel(data)                             (0x00008000&((data)<<15))
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_odd_1_ph_sel_src(data)                         ((0x00008000&(data))>>15)
#define DC_PHY_FIFO_DLYN_get_clk_ddr_div2_odd_1_ph_sel(data)                         ((0x00008000&(data))>>15)
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_odd_0_ph_sel_shift                             (14)
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_odd_0_ph_sel_mask                              (0x00004000)
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_odd_0_ph_sel(data)                             (0x00004000&((data)<<14))
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_odd_0_ph_sel_src(data)                         ((0x00004000&(data))>>14)
#define DC_PHY_FIFO_DLYN_get_clk_ddr_div2_odd_0_ph_sel(data)                         ((0x00004000&(data))>>14)
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_1_ph_sel_shift                                 (13)
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_1_ph_sel_mask                                  (0x00002000)
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_1_ph_sel(data)                                 (0x00002000&((data)<<13))
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_1_ph_sel_src(data)                             ((0x00002000&(data))>>13)
#define DC_PHY_FIFO_DLYN_get_clk_ddr_div2_1_ph_sel(data)                             ((0x00002000&(data))>>13)
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_0_ph_sel_shift                                 (12)
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_0_ph_sel_mask                                  (0x00001000)
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_0_ph_sel(data)                                 (0x00001000&((data)<<12))
#define DC_PHY_FIFO_DLYN_clk_ddr_div2_0_ph_sel_src(data)                             ((0x00001000&(data))>>12)
#define DC_PHY_FIFO_DLYN_get_clk_ddr_div2_0_ph_sel(data)                             ((0x00001000&(data))>>12)
#define DC_PHY_FIFO_DLYN_Tx_dlc_sel_dck_1_shift                                      (8)
#define DC_PHY_FIFO_DLYN_Tx_dlc_sel_dck_1_mask                                       (0x00000F00)
#define DC_PHY_FIFO_DLYN_Tx_dlc_sel_dck_1(data)                                      (0x00000F00&((data)<<8))
#define DC_PHY_FIFO_DLYN_Tx_dlc_sel_dck_1_src(data)                                  ((0x00000F00&(data))>>8)
#define DC_PHY_FIFO_DLYN_get_Tx_dlc_sel_dck_1(data)                                  ((0x00000F00&(data))>>8)
#define DC_PHY_FIFO_DLYN_dqsf_dlyn_shift                                             (4)
#define DC_PHY_FIFO_DLYN_dqsf_dlyn_mask                                              (0x00000030)
#define DC_PHY_FIFO_DLYN_dqsf_dlyn(data)                                             (0x00000030&((data)<<4))
#define DC_PHY_FIFO_DLYN_dqsf_dlyn_src(data)                                         ((0x00000030&(data))>>4)
#define DC_PHY_FIFO_DLYN_get_dqsf_dlyn(data)                                         ((0x00000030&(data))>>4)
#define DC_PHY_FIFO_DLYN_Tx_dlc_sel_dck_shift                                        (0)
#define DC_PHY_FIFO_DLYN_Tx_dlc_sel_dck_mask                                         (0x0000000F)
#define DC_PHY_FIFO_DLYN_Tx_dlc_sel_dck(data)                                        (0x0000000F&((data)<<0))
#define DC_PHY_FIFO_DLYN_Tx_dlc_sel_dck_src(data)                                    ((0x0000000F&(data))>>0)
#define DC_PHY_FIFO_DLYN_get_Tx_dlc_sel_dck(data)                                    ((0x0000000F&(data))>>0)


#define DC_PHY_PAD_OE_CTL                                                            0x18008910
#define DC_PHY_PAD_OE_CTL_reg_addr                                                   "0xB8008910"
#define DC_PHY_PAD_OE_CTL_reg                                                        0xB8008910
#define set_DC_PHY_PAD_OE_CTL_reg(data)   (*((volatile unsigned int*) DC_PHY_PAD_OE_CTL_reg)=data)
#define get_DC_PHY_PAD_OE_CTL_reg   (*((volatile unsigned int*) DC_PHY_PAD_OE_CTL_reg))
#define DC_PHY_PAD_OE_CTL_inst_adr                                                   "0x0044"
#define DC_PHY_PAD_OE_CTL_inst                                                       0x0044
#define DC_PHY_PAD_OE_CTL_grp1_bk_oe_shift                                           (11)
#define DC_PHY_PAD_OE_CTL_grp1_bk_oe_mask                                            (0x00000800)
#define DC_PHY_PAD_OE_CTL_grp1_bk_oe(data)                                           (0x00000800&((data)<<11))
#define DC_PHY_PAD_OE_CTL_grp1_bk_oe_src(data)                                       ((0x00000800&(data))>>11)
#define DC_PHY_PAD_OE_CTL_get_grp1_bk_oe(data)                                       ((0x00000800&(data))>>11)
#define DC_PHY_PAD_OE_CTL_grp1_addr1_oe_shift                                        (10)
#define DC_PHY_PAD_OE_CTL_grp1_addr1_oe_mask                                         (0x00000400)
#define DC_PHY_PAD_OE_CTL_grp1_addr1_oe(data)                                        (0x00000400&((data)<<10))
#define DC_PHY_PAD_OE_CTL_grp1_addr1_oe_src(data)                                    ((0x00000400&(data))>>10)
#define DC_PHY_PAD_OE_CTL_get_grp1_addr1_oe(data)                                    ((0x00000400&(data))>>10)
#define DC_PHY_PAD_OE_CTL_grp1_addr_oe_shift                                         (9)
#define DC_PHY_PAD_OE_CTL_grp1_addr_oe_mask                                          (0x00000200)
#define DC_PHY_PAD_OE_CTL_grp1_addr_oe(data)                                         (0x00000200&((data)<<9))
#define DC_PHY_PAD_OE_CTL_grp1_addr_oe_src(data)                                     ((0x00000200&(data))>>9)
#define DC_PHY_PAD_OE_CTL_get_grp1_addr_oe(data)                                     ((0x00000200&(data))>>9)
#define DC_PHY_PAD_OE_CTL_grp1_cke_oe_shift                                          (8)
#define DC_PHY_PAD_OE_CTL_grp1_cke_oe_mask                                           (0x00000100)
#define DC_PHY_PAD_OE_CTL_grp1_cke_oe(data)                                          (0x00000100&((data)<<8))
#define DC_PHY_PAD_OE_CTL_grp1_cke_oe_src(data)                                      ((0x00000100&(data))>>8)
#define DC_PHY_PAD_OE_CTL_get_grp1_cke_oe(data)                                      ((0x00000100&(data))>>8)
#define DC_PHY_PAD_OE_CTL_grp1_ck_oe_shift                                           (7)
#define DC_PHY_PAD_OE_CTL_grp1_ck_oe_mask                                            (0x00000080)
#define DC_PHY_PAD_OE_CTL_grp1_ck_oe(data)                                           (0x00000080&((data)<<7))
#define DC_PHY_PAD_OE_CTL_grp1_ck_oe_src(data)                                       ((0x00000080&(data))>>7)
#define DC_PHY_PAD_OE_CTL_get_grp1_ck_oe(data)                                       ((0x00000080&(data))>>7)
#define DC_PHY_PAD_OE_CTL_grp1_addr1_15_oe_shift                                     (6)
#define DC_PHY_PAD_OE_CTL_grp1_addr1_15_oe_mask                                      (0x00000040)
#define DC_PHY_PAD_OE_CTL_grp1_addr1_15_oe(data)                                     (0x00000040&((data)<<6))
#define DC_PHY_PAD_OE_CTL_grp1_addr1_15_oe_src(data)                                 ((0x00000040&(data))>>6)
#define DC_PHY_PAD_OE_CTL_get_grp1_addr1_15_oe(data)                                 ((0x00000040&(data))>>6)
#define DC_PHY_PAD_OE_CTL_grp1_addr1_14_oe_shift                                     (5)
#define DC_PHY_PAD_OE_CTL_grp1_addr1_14_oe_mask                                      (0x00000020)
#define DC_PHY_PAD_OE_CTL_grp1_addr1_14_oe(data)                                     (0x00000020&((data)<<5))
#define DC_PHY_PAD_OE_CTL_grp1_addr1_14_oe_src(data)                                 ((0x00000020&(data))>>5)
#define DC_PHY_PAD_OE_CTL_get_grp1_addr1_14_oe(data)                                 ((0x00000020&(data))>>5)
#define DC_PHY_PAD_OE_CTL_grp1_addr1_13_oe_shift                                     (4)
#define DC_PHY_PAD_OE_CTL_grp1_addr1_13_oe_mask                                      (0x00000010)
#define DC_PHY_PAD_OE_CTL_grp1_addr1_13_oe(data)                                     (0x00000010&((data)<<4))
#define DC_PHY_PAD_OE_CTL_grp1_addr1_13_oe_src(data)                                 ((0x00000010&(data))>>4)
#define DC_PHY_PAD_OE_CTL_get_grp1_addr1_13_oe(data)                                 ((0x00000010&(data))>>4)
#define DC_PHY_PAD_OE_CTL_grp1_addr_15_oe_shift                                      (3)
#define DC_PHY_PAD_OE_CTL_grp1_addr_15_oe_mask                                       (0x00000008)
#define DC_PHY_PAD_OE_CTL_grp1_addr_15_oe(data)                                      (0x00000008&((data)<<3))
#define DC_PHY_PAD_OE_CTL_grp1_addr_15_oe_src(data)                                  ((0x00000008&(data))>>3)
#define DC_PHY_PAD_OE_CTL_get_grp1_addr_15_oe(data)                                  ((0x00000008&(data))>>3)
#define DC_PHY_PAD_OE_CTL_grp1_addr_14_oe_shift                                      (2)
#define DC_PHY_PAD_OE_CTL_grp1_addr_14_oe_mask                                       (0x00000004)
#define DC_PHY_PAD_OE_CTL_grp1_addr_14_oe(data)                                      (0x00000004&((data)<<2))
#define DC_PHY_PAD_OE_CTL_grp1_addr_14_oe_src(data)                                  ((0x00000004&(data))>>2)
#define DC_PHY_PAD_OE_CTL_get_grp1_addr_14_oe(data)                                  ((0x00000004&(data))>>2)
#define DC_PHY_PAD_OE_CTL_grp1_addr_13_oe_shift                                      (1)
#define DC_PHY_PAD_OE_CTL_grp1_addr_13_oe_mask                                       (0x00000002)
#define DC_PHY_PAD_OE_CTL_grp1_addr_13_oe(data)                                      (0x00000002&((data)<<1))
#define DC_PHY_PAD_OE_CTL_grp1_addr_13_oe_src(data)                                  ((0x00000002&(data))>>1)
#define DC_PHY_PAD_OE_CTL_get_grp1_addr_13_oe(data)                                  ((0x00000002&(data))>>1)


#define DC_PHY_PAD_IDDQ0                                                             0x18008918
#define DC_PHY_PAD_IDDQ0_reg_addr                                                    "0xB8008918"
#define DC_PHY_PAD_IDDQ0_reg                                                         0xB8008918
#define set_DC_PHY_PAD_IDDQ0_reg(data)   (*((volatile unsigned int*) DC_PHY_PAD_IDDQ0_reg)=data)
#define get_DC_PHY_PAD_IDDQ0_reg   (*((volatile unsigned int*) DC_PHY_PAD_IDDQ0_reg))
#define DC_PHY_PAD_IDDQ0_inst_adr                                                    "0x0046"
#define DC_PHY_PAD_IDDQ0_inst                                                        0x0046
#define DC_PHY_PAD_IDDQ0_iddq_0_shift                                                (0)
#define DC_PHY_PAD_IDDQ0_iddq_0_mask                                                 (0x00001FFF)
#define DC_PHY_PAD_IDDQ0_iddq_0(data)                                                (0x00001FFF&((data)<<0))
#define DC_PHY_PAD_IDDQ0_iddq_0_src(data)                                            ((0x00001FFF&(data))>>0)
#define DC_PHY_PAD_IDDQ0_get_iddq_0(data)                                            ((0x00001FFF&(data))>>0)


#define DC_PHY_PAD_ZCTRL_OVRD                                                        0x18008924
#define DC_PHY_PAD_ZCTRL_OVRD_reg_addr                                               "0xB8008924"
#define DC_PHY_PAD_ZCTRL_OVRD_reg                                                    0xB8008924
#define set_DC_PHY_PAD_ZCTRL_OVRD_reg(data)   (*((volatile unsigned int*) DC_PHY_PAD_ZCTRL_OVRD_reg)=data)
#define get_DC_PHY_PAD_ZCTRL_OVRD_reg   (*((volatile unsigned int*) DC_PHY_PAD_ZCTRL_OVRD_reg))
#define DC_PHY_PAD_ZCTRL_OVRD_inst_adr                                               "0x0049"
#define DC_PHY_PAD_ZCTRL_OVRD_inst                                                   0x0049
#define DC_PHY_PAD_ZCTRL_OVRD_refctrl_pdref_shift                                    (24)
#define DC_PHY_PAD_ZCTRL_OVRD_refctrl_pdref_mask                                     (0x01000000)
#define DC_PHY_PAD_ZCTRL_OVRD_refctrl_pdref(data)                                    (0x01000000&((data)<<24))
#define DC_PHY_PAD_ZCTRL_OVRD_refctrl_pdref_src(data)                                ((0x01000000&(data))>>24)
#define DC_PHY_PAD_ZCTRL_OVRD_get_refctrl_pdref(data)                                ((0x01000000&(data))>>24)
#define DC_PHY_PAD_ZCTRL_OVRD_zctrl_ovrd_en_shift                                    (22)
#define DC_PHY_PAD_ZCTRL_OVRD_zctrl_ovrd_en_mask                                     (0x00400000)
#define DC_PHY_PAD_ZCTRL_OVRD_zctrl_ovrd_en(data)                                    (0x00400000&((data)<<22))
#define DC_PHY_PAD_ZCTRL_OVRD_zctrl_ovrd_en_src(data)                                ((0x00400000&(data))>>22)
#define DC_PHY_PAD_ZCTRL_OVRD_get_zctrl_ovrd_en(data)                                ((0x00400000&(data))>>22)
#define DC_PHY_PAD_ZCTRL_OVRD_zctrl_ovrd_data_shift                                  (0)
#define DC_PHY_PAD_ZCTRL_OVRD_zctrl_ovrd_data_mask                                   (0x003FFFFF)
#define DC_PHY_PAD_ZCTRL_OVRD_zctrl_ovrd_data(data)                                  (0x003FFFFF&((data)<<0))
#define DC_PHY_PAD_ZCTRL_OVRD_zctrl_ovrd_data_src(data)                              ((0x003FFFFF&(data))>>0)
#define DC_PHY_PAD_ZCTRL_OVRD_get_zctrl_ovrd_data(data)                              ((0x003FFFFF&(data))>>0)


#define DC_PHY_PAD_CTRL_PROG                                                         0x18008928
#define DC_PHY_PAD_CTRL_PROG_reg_addr                                                "0xB8008928"
#define DC_PHY_PAD_CTRL_PROG_reg                                                     0xB8008928
#define set_DC_PHY_PAD_CTRL_PROG_reg(data)   (*((volatile unsigned int*) DC_PHY_PAD_CTRL_PROG_reg)=data)
#define get_DC_PHY_PAD_CTRL_PROG_reg   (*((volatile unsigned int*) DC_PHY_PAD_CTRL_PROG_reg))
#define DC_PHY_PAD_CTRL_PROG_inst_adr                                                "0x004A"
#define DC_PHY_PAD_CTRL_PROG_inst                                                    0x004A
#define DC_PHY_PAD_CTRL_PROG_ocd_mode_shift                                          (27)
#define DC_PHY_PAD_CTRL_PROG_ocd_mode_mask                                           (0x08000000)
#define DC_PHY_PAD_CTRL_PROG_ocd_mode(data)                                          (0x08000000&((data)<<27))
#define DC_PHY_PAD_CTRL_PROG_ocd_mode_src(data)                                      ((0x08000000&(data))>>27)
#define DC_PHY_PAD_CTRL_PROG_get_ocd_mode(data)                                      ((0x08000000&(data))>>27)
#define DC_PHY_PAD_CTRL_PROG_dzq_up_sel_shift                                        (24)
#define DC_PHY_PAD_CTRL_PROG_dzq_up_sel_mask                                         (0x07000000)
#define DC_PHY_PAD_CTRL_PROG_dzq_up_sel(data)                                        (0x07000000&((data)<<24))
#define DC_PHY_PAD_CTRL_PROG_dzq_up_sel_src(data)                                    ((0x07000000&(data))>>24)
#define DC_PHY_PAD_CTRL_PROG_get_dzq_up_sel(data)                                    ((0x07000000&(data))>>24)
#define DC_PHY_PAD_CTRL_PROG_dzq_auto_up_shift                                       (23)
#define DC_PHY_PAD_CTRL_PROG_dzq_auto_up_mask                                        (0x00800000)
#define DC_PHY_PAD_CTRL_PROG_dzq_auto_up(data)                                       (0x00800000&((data)<<23))
#define DC_PHY_PAD_CTRL_PROG_dzq_auto_up_src(data)                                   ((0x00800000&(data))>>23)
#define DC_PHY_PAD_CTRL_PROG_get_dzq_auto_up(data)                                   ((0x00800000&(data))>>23)
#define DC_PHY_PAD_CTRL_PROG_zctrl_clk_sel_shift                                     (21)
#define DC_PHY_PAD_CTRL_PROG_zctrl_clk_sel_mask                                      (0x00600000)
#define DC_PHY_PAD_CTRL_PROG_zctrl_clk_sel(data)                                     (0x00600000&((data)<<21))
#define DC_PHY_PAD_CTRL_PROG_zctrl_clk_sel_src(data)                                 ((0x00600000&(data))>>21)
#define DC_PHY_PAD_CTRL_PROG_get_zctrl_clk_sel(data)                                 ((0x00600000&(data))>>21)
#define DC_PHY_PAD_CTRL_PROG_zctrl_start_shift                                       (20)
#define DC_PHY_PAD_CTRL_PROG_zctrl_start_mask                                        (0x00100000)
#define DC_PHY_PAD_CTRL_PROG_zctrl_start(data)                                       (0x00100000&((data)<<20))
#define DC_PHY_PAD_CTRL_PROG_zctrl_start_src(data)                                   ((0x00100000&(data))>>20)
#define DC_PHY_PAD_CTRL_PROG_get_zctrl_start(data)                                   ((0x00100000&(data))>>20)
#define DC_PHY_PAD_CTRL_PROG_dzq_ref_up_shift                                        (19)
#define DC_PHY_PAD_CTRL_PROG_dzq_ref_up_mask                                         (0x00080000)
#define DC_PHY_PAD_CTRL_PROG_dzq_ref_up(data)                                        (0x00080000&((data)<<19))
#define DC_PHY_PAD_CTRL_PROG_dzq_ref_up_src(data)                                    ((0x00080000&(data))>>19)
#define DC_PHY_PAD_CTRL_PROG_get_dzq_ref_up(data)                                    ((0x00080000&(data))>>19)
#define DC_PHY_PAD_CTRL_PROG_ext_r240_sel_shift                                      (18)
#define DC_PHY_PAD_CTRL_PROG_ext_r240_sel_mask                                       (0x00040000)
#define DC_PHY_PAD_CTRL_PROG_ext_r240_sel(data)                                      (0x00040000&((data)<<18))
#define DC_PHY_PAD_CTRL_PROG_ext_r240_sel_src(data)                                  ((0x00040000&(data))>>18)
#define DC_PHY_PAD_CTRL_PROG_get_ext_r240_sel(data)                                  ((0x00040000&(data))>>18)
#define DC_PHY_PAD_CTRL_PROG_rzq_zcomp_inv_shift                                     (17)
#define DC_PHY_PAD_CTRL_PROG_rzq_zcomp_inv_mask                                      (0x00020000)
#define DC_PHY_PAD_CTRL_PROG_rzq_zcomp_inv(data)                                     (0x00020000&((data)<<17))
#define DC_PHY_PAD_CTRL_PROG_rzq_zcomp_inv_src(data)                                 ((0x00020000&(data))>>17)
#define DC_PHY_PAD_CTRL_PROG_get_rzq_zcomp_inv(data)                                 ((0x00020000&(data))>>17)
#define DC_PHY_PAD_CTRL_PROG_rzq_cal_en_shift                                        (16)
#define DC_PHY_PAD_CTRL_PROG_rzq_cal_en_mask                                         (0x00010000)
#define DC_PHY_PAD_CTRL_PROG_rzq_cal_en(data)                                        (0x00010000&((data)<<16))
#define DC_PHY_PAD_CTRL_PROG_rzq_cal_en_src(data)                                    ((0x00010000&(data))>>16)
#define DC_PHY_PAD_CTRL_PROG_get_rzq_cal_en(data)                                    ((0x00010000&(data))>>16)
#define DC_PHY_PAD_CTRL_PROG_zprog_shift                                             (0)
#define DC_PHY_PAD_CTRL_PROG_zprog_mask                                              (0x00003FFF)
#define DC_PHY_PAD_CTRL_PROG_zprog(data)                                             (0x00003FFF&((data)<<0))
#define DC_PHY_PAD_CTRL_PROG_zprog_src(data)                                         ((0x00003FFF&(data))>>0)
#define DC_PHY_PAD_CTRL_PROG_get_zprog(data)                                         ((0x00003FFF&(data))>>0)


#define DC_PHY_PAD_ZCTRL_STATUS                                                      0x1800892C
#define DC_PHY_PAD_ZCTRL_STATUS_reg_addr                                             "0xB800892C"
#define DC_PHY_PAD_ZCTRL_STATUS_reg                                                  0xB800892C
#define set_DC_PHY_PAD_ZCTRL_STATUS_reg(data)   (*((volatile unsigned int*) DC_PHY_PAD_ZCTRL_STATUS_reg)=data)
#define get_DC_PHY_PAD_ZCTRL_STATUS_reg   (*((volatile unsigned int*) DC_PHY_PAD_ZCTRL_STATUS_reg))
#define DC_PHY_PAD_ZCTRL_STATUS_inst_adr                                             "0x004B"
#define DC_PHY_PAD_ZCTRL_STATUS_inst                                                 0x004B
#define DC_PHY_PAD_ZCTRL_STATUS_zctrl_status_shift                                   (0)
#define DC_PHY_PAD_ZCTRL_STATUS_zctrl_status_mask                                    (0xFFFFFFFF)
#define DC_PHY_PAD_ZCTRL_STATUS_zctrl_status(data)                                   (0xFFFFFFFF&((data)<<0))
#define DC_PHY_PAD_ZCTRL_STATUS_zctrl_status_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_PAD_ZCTRL_STATUS_get_zctrl_status(data)                               ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DQ_DLY_SEL0                                                           0x18008930
#define DC_PHY_DQ_DLY_SEL0_reg_addr                                                  "0xB8008930"
#define DC_PHY_DQ_DLY_SEL0_reg                                                       0xB8008930
#define set_DC_PHY_DQ_DLY_SEL0_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ_DLY_SEL0_reg)=data)
#define get_DC_PHY_DQ_DLY_SEL0_reg   (*((volatile unsigned int*) DC_PHY_DQ_DLY_SEL0_reg))
#define DC_PHY_DQ_DLY_SEL0_inst_adr                                                  "0x004C"
#define DC_PHY_DQ_DLY_SEL0_inst                                                      0x004C
#define DC_PHY_DQ_DLY_SEL0_dq_dly_sel0_shift                                         (0)
#define DC_PHY_DQ_DLY_SEL0_dq_dly_sel0_mask                                          (0xFFFFFFFF)
#define DC_PHY_DQ_DLY_SEL0_dq_dly_sel0(data)                                         (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DQ_DLY_SEL0_dq_dly_sel0_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DQ_DLY_SEL0_get_dq_dly_sel0(data)                                     ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DQ_DLY_SEL1                                                           0x18008934
#define DC_PHY_DQ_DLY_SEL1_reg_addr                                                  "0xB8008934"
#define DC_PHY_DQ_DLY_SEL1_reg                                                       0xB8008934
#define set_DC_PHY_DQ_DLY_SEL1_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ_DLY_SEL1_reg)=data)
#define get_DC_PHY_DQ_DLY_SEL1_reg   (*((volatile unsigned int*) DC_PHY_DQ_DLY_SEL1_reg))
#define DC_PHY_DQ_DLY_SEL1_inst_adr                                                  "0x004D"
#define DC_PHY_DQ_DLY_SEL1_inst                                                      0x004D
#define DC_PHY_DQ_DLY_SEL1_dq_dly_sel1_shift                                         (0)
#define DC_PHY_DQ_DLY_SEL1_dq_dly_sel1_mask                                          (0xFFFFFFFF)
#define DC_PHY_DQ_DLY_SEL1_dq_dly_sel1(data)                                         (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DQ_DLY_SEL1_dq_dly_sel1_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DQ_DLY_SEL1_get_dq_dly_sel1(data)                                     ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DQ_DLY_SEL2                                                           0x18008938
#define DC_PHY_DQ_DLY_SEL2_reg_addr                                                  "0xB8008938"
#define DC_PHY_DQ_DLY_SEL2_reg                                                       0xB8008938
#define set_DC_PHY_DQ_DLY_SEL2_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ_DLY_SEL2_reg)=data)
#define get_DC_PHY_DQ_DLY_SEL2_reg   (*((volatile unsigned int*) DC_PHY_DQ_DLY_SEL2_reg))
#define DC_PHY_DQ_DLY_SEL2_inst_adr                                                  "0x004E"
#define DC_PHY_DQ_DLY_SEL2_inst                                                      0x004E
#define DC_PHY_DQ_DLY_SEL2_dq_dly_sel2_shift                                         (0)
#define DC_PHY_DQ_DLY_SEL2_dq_dly_sel2_mask                                          (0xFFFFFFFF)
#define DC_PHY_DQ_DLY_SEL2_dq_dly_sel2(data)                                         (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DQ_DLY_SEL2_dq_dly_sel2_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DQ_DLY_SEL2_get_dq_dly_sel2(data)                                     ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DQ_DLY_SEL3                                                           0x1800893C
#define DC_PHY_DQ_DLY_SEL3_reg_addr                                                  "0xB800893C"
#define DC_PHY_DQ_DLY_SEL3_reg                                                       0xB800893C
#define set_DC_PHY_DQ_DLY_SEL3_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ_DLY_SEL3_reg)=data)
#define get_DC_PHY_DQ_DLY_SEL3_reg   (*((volatile unsigned int*) DC_PHY_DQ_DLY_SEL3_reg))
#define DC_PHY_DQ_DLY_SEL3_inst_adr                                                  "0x004F"
#define DC_PHY_DQ_DLY_SEL3_inst                                                      0x004F
#define DC_PHY_DQ_DLY_SEL3_dq_dly_sel3_shift                                         (0)
#define DC_PHY_DQ_DLY_SEL3_dq_dly_sel3_mask                                          (0xFFFFFFFF)
#define DC_PHY_DQ_DLY_SEL3_dq_dly_sel3(data)                                         (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DQ_DLY_SEL3_dq_dly_sel3_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DQ_DLY_SEL3_get_dq_dly_sel3(data)                                     ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DQS_OE_DLY_SEL                                                        0x18008940
#define DC_PHY_DQS_OE_DLY_SEL_reg_addr                                               "0xB8008940"
#define DC_PHY_DQS_OE_DLY_SEL_reg                                                    0xB8008940
#define set_DC_PHY_DQS_OE_DLY_SEL_reg(data)   (*((volatile unsigned int*) DC_PHY_DQS_OE_DLY_SEL_reg)=data)
#define get_DC_PHY_DQS_OE_DLY_SEL_reg   (*((volatile unsigned int*) DC_PHY_DQS_OE_DLY_SEL_reg))
#define DC_PHY_DQS_OE_DLY_SEL_inst_adr                                               "0x0050"
#define DC_PHY_DQS_OE_DLY_SEL_inst                                                   0x0050
#define DC_PHY_DQS_OE_DLY_SEL_dqs_oe_dly_sel_shift                                   (0)
#define DC_PHY_DQS_OE_DLY_SEL_dqs_oe_dly_sel_mask                                    (0x00000FFF)
#define DC_PHY_DQS_OE_DLY_SEL_dqs_oe_dly_sel(data)                                   (0x00000FFF&((data)<<0))
#define DC_PHY_DQS_OE_DLY_SEL_dqs_oe_dly_sel_src(data)                               ((0x00000FFF&(data))>>0)
#define DC_PHY_DQS_OE_DLY_SEL_get_dqs_oe_dly_sel(data)                               ((0x00000FFF&(data))>>0)


#define DC_PHY_HALF_CYCLE_CAL_EN                                                     0x18008944
#define DC_PHY_HALF_CYCLE_CAL_EN_reg_addr                                            "0xB8008944"
#define DC_PHY_HALF_CYCLE_CAL_EN_reg                                                 0xB8008944
#define set_DC_PHY_HALF_CYCLE_CAL_EN_reg(data)   (*((volatile unsigned int*) DC_PHY_HALF_CYCLE_CAL_EN_reg)=data)
#define get_DC_PHY_HALF_CYCLE_CAL_EN_reg   (*((volatile unsigned int*) DC_PHY_HALF_CYCLE_CAL_EN_reg))
#define DC_PHY_HALF_CYCLE_CAL_EN_inst_adr                                            "0x0051"
#define DC_PHY_HALF_CYCLE_CAL_EN_inst                                                0x0051
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_cal_sel_shift                            (17)
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_cal_sel_mask                             (0x00020000)
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_cal_sel(data)                            (0x00020000&((data)<<17))
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_cal_sel_src(data)                        ((0x00020000&(data))>>17)
#define DC_PHY_HALF_CYCLE_CAL_EN_get_half_cycle_cal_sel(data)                        ((0x00020000&(data))>>17)
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_ref_thr_shift                            (9)
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_ref_thr_mask                             (0x0001FE00)
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_ref_thr(data)                            (0x0001FE00&((data)<<9))
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_ref_thr_src(data)                        ((0x0001FE00&(data))>>9)
#define DC_PHY_HALF_CYCLE_CAL_EN_get_half_cycle_ref_thr(data)                        ((0x0001FE00&(data))>>9)
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_res_thr_shift                            (3)
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_res_thr_mask                             (0x000001F8)
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_res_thr(data)                            (0x000001F8&((data)<<3))
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_res_thr_src(data)                        ((0x000001F8&(data))>>3)
#define DC_PHY_HALF_CYCLE_CAL_EN_get_half_cycle_res_thr(data)                        ((0x000001F8&(data))>>3)
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_res_mod_shift                            (1)
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_res_mod_mask                             (0x00000006)
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_res_mod(data)                            (0x00000006&((data)<<1))
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_res_mod_src(data)                        ((0x00000006&(data))>>1)
#define DC_PHY_HALF_CYCLE_CAL_EN_get_half_cycle_res_mod(data)                        ((0x00000006&(data))>>1)
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_cal_en_shift                             (0)
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_cal_en_mask                              (0x00000001)
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_cal_en(data)                             (0x00000001&((data)<<0))
#define DC_PHY_HALF_CYCLE_CAL_EN_half_cycle_cal_en_src(data)                         ((0x00000001&(data))>>0)
#define DC_PHY_HALF_CYCLE_CAL_EN_get_half_cycle_cal_en(data)                         ((0x00000001&(data))>>0)


#define DC_PHY_HALF_CYCLE_CAL_SET                                                    0x18008948
#define DC_PHY_HALF_CYCLE_CAL_SET_reg_addr                                           "0xB8008948"
#define DC_PHY_HALF_CYCLE_CAL_SET_reg                                                0xB8008948
#define set_DC_PHY_HALF_CYCLE_CAL_SET_reg(data)   (*((volatile unsigned int*) DC_PHY_HALF_CYCLE_CAL_SET_reg)=data)
#define get_DC_PHY_HALF_CYCLE_CAL_SET_reg   (*((volatile unsigned int*) DC_PHY_HALF_CYCLE_CAL_SET_reg))
#define DC_PHY_HALF_CYCLE_CAL_SET_inst_adr                                           "0x0052"
#define DC_PHY_HALF_CYCLE_CAL_SET_inst                                               0x0052
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_3_shift                     (18)
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_3_mask                      (0x00FC0000)
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_3(data)                     (0x00FC0000&((data)<<18))
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_3_src(data)                 ((0x00FC0000&(data))>>18)
#define DC_PHY_HALF_CYCLE_CAL_SET_get_half_cycle_cal_setting_3(data)                 ((0x00FC0000&(data))>>18)
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_2_shift                     (12)
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_2_mask                      (0x0003F000)
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_2(data)                     (0x0003F000&((data)<<12))
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_2_src(data)                 ((0x0003F000&(data))>>12)
#define DC_PHY_HALF_CYCLE_CAL_SET_get_half_cycle_cal_setting_2(data)                 ((0x0003F000&(data))>>12)
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_1_shift                     (6)
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_1_mask                      (0x00000FC0)
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_1(data)                     (0x00000FC0&((data)<<6))
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_1_src(data)                 ((0x00000FC0&(data))>>6)
#define DC_PHY_HALF_CYCLE_CAL_SET_get_half_cycle_cal_setting_1(data)                 ((0x00000FC0&(data))>>6)
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_0_shift                     (0)
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_0_mask                      (0x0000003F)
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_0(data)                     (0x0000003F&((data)<<0))
#define DC_PHY_HALF_CYCLE_CAL_SET_half_cycle_cal_setting_0_src(data)                 ((0x0000003F&(data))>>0)
#define DC_PHY_HALF_CYCLE_CAL_SET_get_half_cycle_cal_setting_0(data)                 ((0x0000003F&(data))>>0)


#define DC_PHY_PUPD_DLY_NUM                                                          0x1800894C
#define DC_PHY_PUPD_DLY_NUM_reg_addr                                                 "0xB800894C"
#define DC_PHY_PUPD_DLY_NUM_reg                                                      0xB800894C
#define set_DC_PHY_PUPD_DLY_NUM_reg(data)   (*((volatile unsigned int*) DC_PHY_PUPD_DLY_NUM_reg)=data)
#define get_DC_PHY_PUPD_DLY_NUM_reg   (*((volatile unsigned int*) DC_PHY_PUPD_DLY_NUM_reg))
#define DC_PHY_PUPD_DLY_NUM_inst_adr                                                 "0x0053"
#define DC_PHY_PUPD_DLY_NUM_inst                                                     0x0053
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_mux_sel_shift                                   (22)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_mux_sel_mask                                    (0x00C00000)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_mux_sel(data)                                   (0x00C00000&((data)<<22))
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_mux_sel_src(data)                               ((0x00C00000&(data))>>22)
#define DC_PHY_PUPD_DLY_NUM_get_pupd_dly_mux_sel(data)                               ((0x00C00000&(data))>>22)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_sel_shift                                   (20)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_sel_mask                                    (0x00300000)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_sel(data)                                   (0x00300000&((data)<<20))
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_sel_src(data)                               ((0x00300000&(data))>>20)
#define DC_PHY_PUPD_DLY_NUM_get_pupd_dly_num_sel(data)                               ((0x00300000&(data))>>20)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_3_shift                                     (15)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_3_mask                                      (0x000F8000)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_3(data)                                     (0x000F8000&((data)<<15))
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_3_src(data)                                 ((0x000F8000&(data))>>15)
#define DC_PHY_PUPD_DLY_NUM_get_pupd_dly_num_3(data)                                 ((0x000F8000&(data))>>15)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_2_shift                                     (10)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_2_mask                                      (0x00007C00)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_2(data)                                     (0x00007C00&((data)<<10))
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_2_src(data)                                 ((0x00007C00&(data))>>10)
#define DC_PHY_PUPD_DLY_NUM_get_pupd_dly_num_2(data)                                 ((0x00007C00&(data))>>10)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_1_shift                                     (5)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_1_mask                                      (0x000003E0)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_1(data)                                     (0x000003E0&((data)<<5))
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_1_src(data)                                 ((0x000003E0&(data))>>5)
#define DC_PHY_PUPD_DLY_NUM_get_pupd_dly_num_1(data)                                 ((0x000003E0&(data))>>5)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_0_shift                                     (0)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_0_mask                                      (0x0000001F)
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_0(data)                                     (0x0000001F&((data)<<0))
#define DC_PHY_PUPD_DLY_NUM_pupd_dly_num_0_src(data)                                 ((0x0000001F&(data))>>0)
#define DC_PHY_PUPD_DLY_NUM_get_pupd_dly_num_0(data)                                 ((0x0000001F&(data))>>0)


#define DC_PHY_DQS_DLYN                                                              0x18008950
#define DC_PHY_DQS_DLYN_reg_addr                                                     "0xB8008950"
#define DC_PHY_DQS_DLYN_reg                                                          0xB8008950
#define set_DC_PHY_DQS_DLYN_reg(data)   (*((volatile unsigned int*) DC_PHY_DQS_DLYN_reg)=data)
#define get_DC_PHY_DQS_DLYN_reg   (*((volatile unsigned int*) DC_PHY_DQS_DLYN_reg))
#define DC_PHY_DQS_DLYN_inst_adr                                                     "0x0054"
#define DC_PHY_DQS_DLYN_inst                                                         0x0054
#define DC_PHY_DQS_DLYN_dqs3_det_0_dlyn_shift                                        (28)
#define DC_PHY_DQS_DLYN_dqs3_det_0_dlyn_mask                                         (0xF0000000)
#define DC_PHY_DQS_DLYN_dqs3_det_0_dlyn(data)                                        (0xF0000000&((data)<<28))
#define DC_PHY_DQS_DLYN_dqs3_det_0_dlyn_src(data)                                    ((0xF0000000&(data))>>28)
#define DC_PHY_DQS_DLYN_get_dqs3_det_0_dlyn(data)                                    ((0xF0000000&(data))>>28)
#define DC_PHY_DQS_DLYN_dqs2_det_0_dlyn_shift                                        (24)
#define DC_PHY_DQS_DLYN_dqs2_det_0_dlyn_mask                                         (0x0F000000)
#define DC_PHY_DQS_DLYN_dqs2_det_0_dlyn(data)                                        (0x0F000000&((data)<<24))
#define DC_PHY_DQS_DLYN_dqs2_det_0_dlyn_src(data)                                    ((0x0F000000&(data))>>24)
#define DC_PHY_DQS_DLYN_get_dqs2_det_0_dlyn(data)                                    ((0x0F000000&(data))>>24)
#define DC_PHY_DQS_DLYN_dqs1_det_0_dlyn_shift                                        (20)
#define DC_PHY_DQS_DLYN_dqs1_det_0_dlyn_mask                                         (0x00F00000)
#define DC_PHY_DQS_DLYN_dqs1_det_0_dlyn(data)                                        (0x00F00000&((data)<<20))
#define DC_PHY_DQS_DLYN_dqs1_det_0_dlyn_src(data)                                    ((0x00F00000&(data))>>20)
#define DC_PHY_DQS_DLYN_get_dqs1_det_0_dlyn(data)                                    ((0x00F00000&(data))>>20)
#define DC_PHY_DQS_DLYN_dqs0_det_0_dlyn_shift                                        (16)
#define DC_PHY_DQS_DLYN_dqs0_det_0_dlyn_mask                                         (0x000F0000)
#define DC_PHY_DQS_DLYN_dqs0_det_0_dlyn(data)                                        (0x000F0000&((data)<<16))
#define DC_PHY_DQS_DLYN_dqs0_det_0_dlyn_src(data)                                    ((0x000F0000&(data))>>16)
#define DC_PHY_DQS_DLYN_get_dqs0_det_0_dlyn(data)                                    ((0x000F0000&(data))>>16)
#define DC_PHY_DQS_DLYN_dqs3_en_0_dlyn_shift                                         (12)
#define DC_PHY_DQS_DLYN_dqs3_en_0_dlyn_mask                                          (0x0000F000)
#define DC_PHY_DQS_DLYN_dqs3_en_0_dlyn(data)                                         (0x0000F000&((data)<<12))
#define DC_PHY_DQS_DLYN_dqs3_en_0_dlyn_src(data)                                     ((0x0000F000&(data))>>12)
#define DC_PHY_DQS_DLYN_get_dqs3_en_0_dlyn(data)                                     ((0x0000F000&(data))>>12)
#define DC_PHY_DQS_DLYN_dqs2_en_0_dlyn_shift                                         (8)
#define DC_PHY_DQS_DLYN_dqs2_en_0_dlyn_mask                                          (0x00000F00)
#define DC_PHY_DQS_DLYN_dqs2_en_0_dlyn(data)                                         (0x00000F00&((data)<<8))
#define DC_PHY_DQS_DLYN_dqs2_en_0_dlyn_src(data)                                     ((0x00000F00&(data))>>8)
#define DC_PHY_DQS_DLYN_get_dqs2_en_0_dlyn(data)                                     ((0x00000F00&(data))>>8)
#define DC_PHY_DQS_DLYN_dqs1_en_0_dlyn_shift                                         (4)
#define DC_PHY_DQS_DLYN_dqs1_en_0_dlyn_mask                                          (0x000000F0)
#define DC_PHY_DQS_DLYN_dqs1_en_0_dlyn(data)                                         (0x000000F0&((data)<<4))
#define DC_PHY_DQS_DLYN_dqs1_en_0_dlyn_src(data)                                     ((0x000000F0&(data))>>4)
#define DC_PHY_DQS_DLYN_get_dqs1_en_0_dlyn(data)                                     ((0x000000F0&(data))>>4)
#define DC_PHY_DQS_DLYN_dqs0_en_0_dlyn_shift                                         (0)
#define DC_PHY_DQS_DLYN_dqs0_en_0_dlyn_mask                                          (0x0000000F)
#define DC_PHY_DQS_DLYN_dqs0_en_0_dlyn(data)                                         (0x0000000F&((data)<<0))
#define DC_PHY_DQS_DLYN_dqs0_en_0_dlyn_src(data)                                     ((0x0000000F&(data))>>0)
#define DC_PHY_DQS_DLYN_get_dqs0_en_0_dlyn(data)                                     ((0x0000000F&(data))>>0)


#define DC_PHY_CAL_MODE                                                              0x18008954
#define DC_PHY_CAL_MODE_reg_addr                                                     "0xB8008954"
#define DC_PHY_CAL_MODE_reg                                                          0xB8008954
#define set_DC_PHY_CAL_MODE_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL_MODE_reg)=data)
#define get_DC_PHY_CAL_MODE_reg   (*((volatile unsigned int*) DC_PHY_CAL_MODE_reg))
#define DC_PHY_CAL_MODE_inst_adr                                                     "0x0055"
#define DC_PHY_CAL_MODE_inst                                                         0x0055
#define DC_PHY_CAL_MODE_pupd_mode_shift                                              (13)
#define DC_PHY_CAL_MODE_pupd_mode_mask                                               (0x00006000)
#define DC_PHY_CAL_MODE_pupd_mode(data)                                              (0x00006000&((data)<<13))
#define DC_PHY_CAL_MODE_pupd_mode_src(data)                                          ((0x00006000&(data))>>13)
#define DC_PHY_CAL_MODE_get_pupd_mode(data)                                          ((0x00006000&(data))>>13)
#define DC_PHY_CAL_MODE_cal_order_shift                                              (12)
#define DC_PHY_CAL_MODE_cal_order_mask                                               (0x00001000)
#define DC_PHY_CAL_MODE_cal_order(data)                                              (0x00001000&((data)<<12))
#define DC_PHY_CAL_MODE_cal_order_src(data)                                          ((0x00001000&(data))>>12)
#define DC_PHY_CAL_MODE_get_cal_order(data)                                          ((0x00001000&(data))>>12)
#define DC_PHY_CAL_MODE_cal_mode_split_shift                                         (11)
#define DC_PHY_CAL_MODE_cal_mode_split_mask                                          (0x00000800)
#define DC_PHY_CAL_MODE_cal_mode_split(data)                                         (0x00000800&((data)<<11))
#define DC_PHY_CAL_MODE_cal_mode_split_src(data)                                     ((0x00000800&(data))>>11)
#define DC_PHY_CAL_MODE_get_cal_mode_split(data)                                     ((0x00000800&(data))>>11)
#define DC_PHY_CAL_MODE_cal_zq_only_shift                                            (10)
#define DC_PHY_CAL_MODE_cal_zq_only_mask                                             (0x00000400)
#define DC_PHY_CAL_MODE_cal_zq_only(data)                                            (0x00000400&((data)<<10))
#define DC_PHY_CAL_MODE_cal_zq_only_src(data)                                        ((0x00000400&(data))>>10)
#define DC_PHY_CAL_MODE_get_cal_zq_only(data)                                        ((0x00000400&(data))>>10)
#define DC_PHY_CAL_MODE_cal_zq_shift                                                 (9)
#define DC_PHY_CAL_MODE_cal_zq_mask                                                  (0x00000200)
#define DC_PHY_CAL_MODE_cal_zq(data)                                                 (0x00000200&((data)<<9))
#define DC_PHY_CAL_MODE_cal_zq_src(data)                                             ((0x00000200&(data))>>9)
#define DC_PHY_CAL_MODE_get_cal_zq(data)                                             ((0x00000200&(data))>>9)
#define DC_PHY_CAL_MODE_cal_all_rang_noml_shift                                      (8)
#define DC_PHY_CAL_MODE_cal_all_rang_noml_mask                                       (0x00000100)
#define DC_PHY_CAL_MODE_cal_all_rang_noml(data)                                      (0x00000100&((data)<<8))
#define DC_PHY_CAL_MODE_cal_all_rang_noml_src(data)                                  ((0x00000100&(data))>>8)
#define DC_PHY_CAL_MODE_get_cal_all_rang_noml(data)                                  ((0x00000100&(data))>>8)
#define DC_PHY_CAL_MODE_cal_all_rang_init_shift                                      (7)
#define DC_PHY_CAL_MODE_cal_all_rang_init_mask                                       (0x00000080)
#define DC_PHY_CAL_MODE_cal_all_rang_init(data)                                      (0x00000080&((data)<<7))
#define DC_PHY_CAL_MODE_cal_all_rang_init_src(data)                                  ((0x00000080&(data))>>7)
#define DC_PHY_CAL_MODE_get_cal_all_rang_init(data)                                  ((0x00000080&(data))>>7)
#define DC_PHY_CAL_MODE_auto_cal_en_noml_shift                                       (6)
#define DC_PHY_CAL_MODE_auto_cal_en_noml_mask                                        (0x00000040)
#define DC_PHY_CAL_MODE_auto_cal_en_noml(data)                                       (0x00000040&((data)<<6))
#define DC_PHY_CAL_MODE_auto_cal_en_noml_src(data)                                   ((0x00000040&(data))>>6)
#define DC_PHY_CAL_MODE_get_auto_cal_en_noml(data)                                   ((0x00000040&(data))>>6)
#define DC_PHY_CAL_MODE_auto_cal_en_init_shift                                       (5)
#define DC_PHY_CAL_MODE_auto_cal_en_init_mask                                        (0x00000020)
#define DC_PHY_CAL_MODE_auto_cal_en_init(data)                                       (0x00000020&((data)<<5))
#define DC_PHY_CAL_MODE_auto_cal_en_init_src(data)                                   ((0x00000020&(data))>>5)
#define DC_PHY_CAL_MODE_get_auto_cal_en_init(data)                                   ((0x00000020&(data))>>5)
#define DC_PHY_CAL_MODE_dqs_val_sel_shift                                            (4)
#define DC_PHY_CAL_MODE_dqs_val_sel_mask                                             (0x00000010)
#define DC_PHY_CAL_MODE_dqs_val_sel(data)                                            (0x00000010&((data)<<4))
#define DC_PHY_CAL_MODE_dqs_val_sel_src(data)                                        ((0x00000010&(data))>>4)
#define DC_PHY_CAL_MODE_get_dqs_val_sel(data)                                        ((0x00000010&(data))>>4)
#define DC_PHY_CAL_MODE_cal_mode_shift                                               (1)
#define DC_PHY_CAL_MODE_cal_mode_mask                                                (0x0000000E)
#define DC_PHY_CAL_MODE_cal_mode(data)                                               (0x0000000E&((data)<<1))
#define DC_PHY_CAL_MODE_cal_mode_src(data)                                           ((0x0000000E&(data))>>1)
#define DC_PHY_CAL_MODE_get_cal_mode(data)                                           ((0x0000000E&(data))>>1)
#define DC_PHY_CAL_MODE_dq_sel_shift                                                 (0)
#define DC_PHY_CAL_MODE_dq_sel_mask                                                  (0x00000001)
#define DC_PHY_CAL_MODE_dq_sel(data)                                                 (0x00000001&((data)<<0))
#define DC_PHY_CAL_MODE_dq_sel_src(data)                                             ((0x00000001&(data))>>0)
#define DC_PHY_CAL_MODE_get_dq_sel(data)                                             ((0x00000001&(data))>>0)


#define DC_PHY_CAL_ADDR                                                              0x18008958
#define DC_PHY_CAL_ADDR_reg_addr                                                     "0xB8008958"
#define DC_PHY_CAL_ADDR_reg                                                          0xB8008958
#define set_DC_PHY_CAL_ADDR_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL_ADDR_reg)=data)
#define get_DC_PHY_CAL_ADDR_reg   (*((volatile unsigned int*) DC_PHY_CAL_ADDR_reg))
#define DC_PHY_CAL_ADDR_inst_adr                                                     "0x0056"
#define DC_PHY_CAL_ADDR_inst                                                         0x0056
#define DC_PHY_CAL_ADDR_cal_ba_shift                                                 (23)
#define DC_PHY_CAL_ADDR_cal_ba_mask                                                  (0x03800000)
#define DC_PHY_CAL_ADDR_cal_ba(data)                                                 (0x03800000&((data)<<23))
#define DC_PHY_CAL_ADDR_cal_ba_src(data)                                             ((0x03800000&(data))>>23)
#define DC_PHY_CAL_ADDR_get_cal_ba(data)                                             ((0x03800000&(data))>>23)
#define DC_PHY_CAL_ADDR_cal_col_shift                                                (13)
#define DC_PHY_CAL_ADDR_cal_col_mask                                                 (0x007FE000)
#define DC_PHY_CAL_ADDR_cal_col(data)                                                (0x007FE000&((data)<<13))
#define DC_PHY_CAL_ADDR_cal_col_src(data)                                            ((0x007FE000&(data))>>13)
#define DC_PHY_CAL_ADDR_get_cal_col(data)                                            ((0x007FE000&(data))>>13)
#define DC_PHY_CAL_ADDR_cal_row_shift                                                (0)
#define DC_PHY_CAL_ADDR_cal_row_mask                                                 (0x00001FFF)
#define DC_PHY_CAL_ADDR_cal_row(data)                                                (0x00001FFF&((data)<<0))
#define DC_PHY_CAL_ADDR_cal_row_src(data)                                            ((0x00001FFF&(data))>>0)
#define DC_PHY_CAL_ADDR_get_cal_row(data)                                            ((0x00001FFF&(data))>>0)


#define DC_PHY_RESULT_CAL_TAP_0                                                      0x1800895c
#define DC_PHY_RESULT_CAL_TAP_0_reg_addr                                             "0xB800895C"
#define DC_PHY_RESULT_CAL_TAP_0_reg                                                  0xB800895C
#define set_DC_PHY_RESULT_CAL_TAP_0_reg(data)   (*((volatile unsigned int*) DC_PHY_RESULT_CAL_TAP_0_reg)=data)
#define get_DC_PHY_RESULT_CAL_TAP_0_reg   (*((volatile unsigned int*) DC_PHY_RESULT_CAL_TAP_0_reg))
#define DC_PHY_RESULT_CAL_TAP_0_inst_adr                                             "0x0057"
#define DC_PHY_RESULT_CAL_TAP_0_inst                                                 0x0057
#define DC_PHY_RESULT_CAL_TAP_0_end_done_01_p_shift                                  (19)
#define DC_PHY_RESULT_CAL_TAP_0_end_done_01_p_mask                                   (0x00080000)
#define DC_PHY_RESULT_CAL_TAP_0_end_done_01_p(data)                                  (0x00080000&((data)<<19))
#define DC_PHY_RESULT_CAL_TAP_0_end_done_01_p_src(data)                              ((0x00080000&(data))>>19)
#define DC_PHY_RESULT_CAL_TAP_0_get_end_done_01_p(data)                              ((0x00080000&(data))>>19)
#define DC_PHY_RESULT_CAL_TAP_0_start_done_01_p_shift                                (18)
#define DC_PHY_RESULT_CAL_TAP_0_start_done_01_p_mask                                 (0x00040000)
#define DC_PHY_RESULT_CAL_TAP_0_start_done_01_p(data)                                (0x00040000&((data)<<18))
#define DC_PHY_RESULT_CAL_TAP_0_start_done_01_p_src(data)                            ((0x00040000&(data))>>18)
#define DC_PHY_RESULT_CAL_TAP_0_get_start_done_01_p(data)                            ((0x00040000&(data))>>18)
#define DC_PHY_RESULT_CAL_TAP_0_best_dly_01_p_shift                                  (12)
#define DC_PHY_RESULT_CAL_TAP_0_best_dly_01_p_mask                                   (0x0003F000)
#define DC_PHY_RESULT_CAL_TAP_0_best_dly_01_p(data)                                  (0x0003F000&((data)<<12))
#define DC_PHY_RESULT_CAL_TAP_0_best_dly_01_p_src(data)                              ((0x0003F000&(data))>>12)
#define DC_PHY_RESULT_CAL_TAP_0_get_best_dly_01_p(data)                              ((0x0003F000&(data))>>12)
#define DC_PHY_RESULT_CAL_TAP_0_end_pt_01_p_shift                                    (6)
#define DC_PHY_RESULT_CAL_TAP_0_end_pt_01_p_mask                                     (0x00000FC0)
#define DC_PHY_RESULT_CAL_TAP_0_end_pt_01_p(data)                                    (0x00000FC0&((data)<<6))
#define DC_PHY_RESULT_CAL_TAP_0_end_pt_01_p_src(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_RESULT_CAL_TAP_0_get_end_pt_01_p(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_RESULT_CAL_TAP_0_start_pt_01_p_shift                                  (0)
#define DC_PHY_RESULT_CAL_TAP_0_start_pt_01_p_mask                                   (0x0000003F)
#define DC_PHY_RESULT_CAL_TAP_0_start_pt_01_p(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_RESULT_CAL_TAP_0_start_pt_01_p_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_RESULT_CAL_TAP_0_get_start_pt_01_p(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_RESULT_CAL_TAP_1                                                      0x18008960
#define DC_PHY_RESULT_CAL_TAP_1_reg_addr                                             "0xB8008960"
#define DC_PHY_RESULT_CAL_TAP_1_reg                                                  0xB8008960
#define set_DC_PHY_RESULT_CAL_TAP_1_reg(data)   (*((volatile unsigned int*) DC_PHY_RESULT_CAL_TAP_1_reg)=data)
#define get_DC_PHY_RESULT_CAL_TAP_1_reg   (*((volatile unsigned int*) DC_PHY_RESULT_CAL_TAP_1_reg))
#define DC_PHY_RESULT_CAL_TAP_1_inst_adr                                             "0x0058"
#define DC_PHY_RESULT_CAL_TAP_1_inst                                                 0x0058
#define DC_PHY_RESULT_CAL_TAP_1_end_done_01_n_shift                                  (19)
#define DC_PHY_RESULT_CAL_TAP_1_end_done_01_n_mask                                   (0x00080000)
#define DC_PHY_RESULT_CAL_TAP_1_end_done_01_n(data)                                  (0x00080000&((data)<<19))
#define DC_PHY_RESULT_CAL_TAP_1_end_done_01_n_src(data)                              ((0x00080000&(data))>>19)
#define DC_PHY_RESULT_CAL_TAP_1_get_end_done_01_n(data)                              ((0x00080000&(data))>>19)
#define DC_PHY_RESULT_CAL_TAP_1_start_done_01_n_shift                                (18)
#define DC_PHY_RESULT_CAL_TAP_1_start_done_01_n_mask                                 (0x00040000)
#define DC_PHY_RESULT_CAL_TAP_1_start_done_01_n(data)                                (0x00040000&((data)<<18))
#define DC_PHY_RESULT_CAL_TAP_1_start_done_01_n_src(data)                            ((0x00040000&(data))>>18)
#define DC_PHY_RESULT_CAL_TAP_1_get_start_done_01_n(data)                            ((0x00040000&(data))>>18)
#define DC_PHY_RESULT_CAL_TAP_1_best_dly_01_n_shift                                  (12)
#define DC_PHY_RESULT_CAL_TAP_1_best_dly_01_n_mask                                   (0x0003F000)
#define DC_PHY_RESULT_CAL_TAP_1_best_dly_01_n(data)                                  (0x0003F000&((data)<<12))
#define DC_PHY_RESULT_CAL_TAP_1_best_dly_01_n_src(data)                              ((0x0003F000&(data))>>12)
#define DC_PHY_RESULT_CAL_TAP_1_get_best_dly_01_n(data)                              ((0x0003F000&(data))>>12)
#define DC_PHY_RESULT_CAL_TAP_1_end_pt_01_n_shift                                    (6)
#define DC_PHY_RESULT_CAL_TAP_1_end_pt_01_n_mask                                     (0x00000FC0)
#define DC_PHY_RESULT_CAL_TAP_1_end_pt_01_n(data)                                    (0x00000FC0&((data)<<6))
#define DC_PHY_RESULT_CAL_TAP_1_end_pt_01_n_src(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_RESULT_CAL_TAP_1_get_end_pt_01_n(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_RESULT_CAL_TAP_1_start_pt_01_n_shift                                  (0)
#define DC_PHY_RESULT_CAL_TAP_1_start_pt_01_n_mask                                   (0x0000003F)
#define DC_PHY_RESULT_CAL_TAP_1_start_pt_01_n(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_RESULT_CAL_TAP_1_start_pt_01_n_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_RESULT_CAL_TAP_1_get_start_pt_01_n(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_RESULT_CAL_TAP_2                                                      0x18008964
#define DC_PHY_RESULT_CAL_TAP_2_reg_addr                                             "0xB8008964"
#define DC_PHY_RESULT_CAL_TAP_2_reg                                                  0xB8008964
#define set_DC_PHY_RESULT_CAL_TAP_2_reg(data)   (*((volatile unsigned int*) DC_PHY_RESULT_CAL_TAP_2_reg)=data)
#define get_DC_PHY_RESULT_CAL_TAP_2_reg   (*((volatile unsigned int*) DC_PHY_RESULT_CAL_TAP_2_reg))
#define DC_PHY_RESULT_CAL_TAP_2_inst_adr                                             "0x0059"
#define DC_PHY_RESULT_CAL_TAP_2_inst                                                 0x0059
#define DC_PHY_RESULT_CAL_TAP_2_end_done_23_p_shift                                  (19)
#define DC_PHY_RESULT_CAL_TAP_2_end_done_23_p_mask                                   (0x00080000)
#define DC_PHY_RESULT_CAL_TAP_2_end_done_23_p(data)                                  (0x00080000&((data)<<19))
#define DC_PHY_RESULT_CAL_TAP_2_end_done_23_p_src(data)                              ((0x00080000&(data))>>19)
#define DC_PHY_RESULT_CAL_TAP_2_get_end_done_23_p(data)                              ((0x00080000&(data))>>19)
#define DC_PHY_RESULT_CAL_TAP_2_start_done_23_p_shift                                (18)
#define DC_PHY_RESULT_CAL_TAP_2_start_done_23_p_mask                                 (0x00040000)
#define DC_PHY_RESULT_CAL_TAP_2_start_done_23_p(data)                                (0x00040000&((data)<<18))
#define DC_PHY_RESULT_CAL_TAP_2_start_done_23_p_src(data)                            ((0x00040000&(data))>>18)
#define DC_PHY_RESULT_CAL_TAP_2_get_start_done_23_p(data)                            ((0x00040000&(data))>>18)
#define DC_PHY_RESULT_CAL_TAP_2_best_dly_23_p_shift                                  (12)
#define DC_PHY_RESULT_CAL_TAP_2_best_dly_23_p_mask                                   (0x0003F000)
#define DC_PHY_RESULT_CAL_TAP_2_best_dly_23_p(data)                                  (0x0003F000&((data)<<12))
#define DC_PHY_RESULT_CAL_TAP_2_best_dly_23_p_src(data)                              ((0x0003F000&(data))>>12)
#define DC_PHY_RESULT_CAL_TAP_2_get_best_dly_23_p(data)                              ((0x0003F000&(data))>>12)
#define DC_PHY_RESULT_CAL_TAP_2_end_pt_23_p_shift                                    (6)
#define DC_PHY_RESULT_CAL_TAP_2_end_pt_23_p_mask                                     (0x00000FC0)
#define DC_PHY_RESULT_CAL_TAP_2_end_pt_23_p(data)                                    (0x00000FC0&((data)<<6))
#define DC_PHY_RESULT_CAL_TAP_2_end_pt_23_p_src(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_RESULT_CAL_TAP_2_get_end_pt_23_p(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_RESULT_CAL_TAP_2_start_pt_23_p_shift                                  (0)
#define DC_PHY_RESULT_CAL_TAP_2_start_pt_23_p_mask                                   (0x0000003F)
#define DC_PHY_RESULT_CAL_TAP_2_start_pt_23_p(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_RESULT_CAL_TAP_2_start_pt_23_p_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_RESULT_CAL_TAP_2_get_start_pt_23_p(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_RESULT_CAL_TAP_3                                                      0x18008968
#define DC_PHY_RESULT_CAL_TAP_3_reg_addr                                             "0xB8008968"
#define DC_PHY_RESULT_CAL_TAP_3_reg                                                  0xB8008968
#define set_DC_PHY_RESULT_CAL_TAP_3_reg(data)   (*((volatile unsigned int*) DC_PHY_RESULT_CAL_TAP_3_reg)=data)
#define get_DC_PHY_RESULT_CAL_TAP_3_reg   (*((volatile unsigned int*) DC_PHY_RESULT_CAL_TAP_3_reg))
#define DC_PHY_RESULT_CAL_TAP_3_inst_adr                                             "0x005A"
#define DC_PHY_RESULT_CAL_TAP_3_inst                                                 0x005A
#define DC_PHY_RESULT_CAL_TAP_3_end_done_23_n_shift                                  (19)
#define DC_PHY_RESULT_CAL_TAP_3_end_done_23_n_mask                                   (0x00080000)
#define DC_PHY_RESULT_CAL_TAP_3_end_done_23_n(data)                                  (0x00080000&((data)<<19))
#define DC_PHY_RESULT_CAL_TAP_3_end_done_23_n_src(data)                              ((0x00080000&(data))>>19)
#define DC_PHY_RESULT_CAL_TAP_3_get_end_done_23_n(data)                              ((0x00080000&(data))>>19)
#define DC_PHY_RESULT_CAL_TAP_3_start_done_23_n_shift                                (18)
#define DC_PHY_RESULT_CAL_TAP_3_start_done_23_n_mask                                 (0x00040000)
#define DC_PHY_RESULT_CAL_TAP_3_start_done_23_n(data)                                (0x00040000&((data)<<18))
#define DC_PHY_RESULT_CAL_TAP_3_start_done_23_n_src(data)                            ((0x00040000&(data))>>18)
#define DC_PHY_RESULT_CAL_TAP_3_get_start_done_23_n(data)                            ((0x00040000&(data))>>18)
#define DC_PHY_RESULT_CAL_TAP_3_best_dly_23_n_shift                                  (12)
#define DC_PHY_RESULT_CAL_TAP_3_best_dly_23_n_mask                                   (0x0003F000)
#define DC_PHY_RESULT_CAL_TAP_3_best_dly_23_n(data)                                  (0x0003F000&((data)<<12))
#define DC_PHY_RESULT_CAL_TAP_3_best_dly_23_n_src(data)                              ((0x0003F000&(data))>>12)
#define DC_PHY_RESULT_CAL_TAP_3_get_best_dly_23_n(data)                              ((0x0003F000&(data))>>12)
#define DC_PHY_RESULT_CAL_TAP_3_end_pt_23_n_shift                                    (6)
#define DC_PHY_RESULT_CAL_TAP_3_end_pt_23_n_mask                                     (0x00000FC0)
#define DC_PHY_RESULT_CAL_TAP_3_end_pt_23_n(data)                                    (0x00000FC0&((data)<<6))
#define DC_PHY_RESULT_CAL_TAP_3_end_pt_23_n_src(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_RESULT_CAL_TAP_3_get_end_pt_23_n(data)                                ((0x00000FC0&(data))>>6)
#define DC_PHY_RESULT_CAL_TAP_3_start_pt_23_n_shift                                  (0)
#define DC_PHY_RESULT_CAL_TAP_3_start_pt_23_n_mask                                   (0x0000003F)
#define DC_PHY_RESULT_CAL_TAP_3_start_pt_23_n(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_RESULT_CAL_TAP_3_start_pt_23_n_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_RESULT_CAL_TAP_3_get_start_pt_23_n(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_RESULT_CAL_TAP_4                                                      0x1800896c
#define DC_PHY_RESULT_CAL_TAP_4_reg_addr                                             "0xB800896C"
#define DC_PHY_RESULT_CAL_TAP_4_reg                                                  0xB800896C
#define set_DC_PHY_RESULT_CAL_TAP_4_reg(data)   (*((volatile unsigned int*) DC_PHY_RESULT_CAL_TAP_4_reg)=data)
#define get_DC_PHY_RESULT_CAL_TAP_4_reg   (*((volatile unsigned int*) DC_PHY_RESULT_CAL_TAP_4_reg))
#define DC_PHY_RESULT_CAL_TAP_4_inst_adr                                             "0x005B"
#define DC_PHY_RESULT_CAL_TAP_4_inst                                                 0x005B
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_n_odt_shift                            (7)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_n_odt_mask                             (0x00000080)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_n_odt(data)                            (0x00000080&((data)<<7))
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_n_odt_src(data)                        ((0x00000080&(data))>>7)
#define DC_PHY_RESULT_CAL_TAP_4_get_wk_big_thr_23_n_odt(data)                        ((0x00000080&(data))>>7)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_p_odt_shift                            (6)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_p_odt_mask                             (0x00000040)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_p_odt(data)                            (0x00000040&((data)<<6))
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_p_odt_src(data)                        ((0x00000040&(data))>>6)
#define DC_PHY_RESULT_CAL_TAP_4_get_wk_big_thr_23_p_odt(data)                        ((0x00000040&(data))>>6)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_n_odt_shift                            (5)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_n_odt_mask                             (0x00000020)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_n_odt(data)                            (0x00000020&((data)<<5))
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_n_odt_src(data)                        ((0x00000020&(data))>>5)
#define DC_PHY_RESULT_CAL_TAP_4_get_wk_big_thr_01_n_odt(data)                        ((0x00000020&(data))>>5)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_p_odt_shift                            (4)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_p_odt_mask                             (0x00000010)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_p_odt(data)                            (0x00000010&((data)<<4))
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_p_odt_src(data)                        ((0x00000010&(data))>>4)
#define DC_PHY_RESULT_CAL_TAP_4_get_wk_big_thr_01_p_odt(data)                        ((0x00000010&(data))>>4)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_n_dt_shift                             (3)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_n_dt_mask                              (0x00000008)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_n_dt(data)                             (0x00000008&((data)<<3))
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_n_dt_src(data)                         ((0x00000008&(data))>>3)
#define DC_PHY_RESULT_CAL_TAP_4_get_wk_big_thr_23_n_dt(data)                         ((0x00000008&(data))>>3)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_p_dt_shift                             (2)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_p_dt_mask                              (0x00000004)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_p_dt(data)                             (0x00000004&((data)<<2))
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_23_p_dt_src(data)                         ((0x00000004&(data))>>2)
#define DC_PHY_RESULT_CAL_TAP_4_get_wk_big_thr_23_p_dt(data)                         ((0x00000004&(data))>>2)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_n_dt_shift                             (1)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_n_dt_mask                              (0x00000002)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_n_dt(data)                             (0x00000002&((data)<<1))
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_n_dt_src(data)                         ((0x00000002&(data))>>1)
#define DC_PHY_RESULT_CAL_TAP_4_get_wk_big_thr_01_n_dt(data)                         ((0x00000002&(data))>>1)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_p_dt_shift                             (0)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_p_dt_mask                              (0x00000001)
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_p_dt(data)                             (0x00000001&((data)<<0))
#define DC_PHY_RESULT_CAL_TAP_4_wk_big_thr_01_p_dt_src(data)                         ((0x00000001&(data))>>0)
#define DC_PHY_RESULT_CAL_TAP_4_get_wk_big_thr_01_p_dt(data)                         ((0x00000001&(data))>>0)


#define DC_PHY_RESULT_CAL_TAP_5                                                      0x18008970
#define DC_PHY_RESULT_CAL_TAP_5_reg_addr                                             "0xB8008970"
#define DC_PHY_RESULT_CAL_TAP_5_reg                                                  0xB8008970
#define set_DC_PHY_RESULT_CAL_TAP_5_reg(data)   (*((volatile unsigned int*) DC_PHY_RESULT_CAL_TAP_5_reg)=data)
#define get_DC_PHY_RESULT_CAL_TAP_5_reg   (*((volatile unsigned int*) DC_PHY_RESULT_CAL_TAP_5_reg))
#define DC_PHY_RESULT_CAL_TAP_5_inst_adr                                             "0x005C"
#define DC_PHY_RESULT_CAL_TAP_5_inst                                                 0x005C
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_n_odt_shift                               (24)
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_n_odt_mask                                (0x3F000000)
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_n_odt(data)                               (0x3F000000&((data)<<24))
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_n_odt_src(data)                           ((0x3F000000&(data))>>24)
#define DC_PHY_RESULT_CAL_TAP_5_get_best_wk_01_n_odt(data)                           ((0x3F000000&(data))>>24)
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_p_odt_shift                               (16)
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_p_odt_mask                                (0x003F0000)
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_p_odt(data)                               (0x003F0000&((data)<<16))
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_p_odt_src(data)                           ((0x003F0000&(data))>>16)
#define DC_PHY_RESULT_CAL_TAP_5_get_best_wk_01_p_odt(data)                           ((0x003F0000&(data))>>16)
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_n_dt_shift                                (8)
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_n_dt_mask                                 (0x00003F00)
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_n_dt(data)                                (0x00003F00&((data)<<8))
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_n_dt_src(data)                            ((0x00003F00&(data))>>8)
#define DC_PHY_RESULT_CAL_TAP_5_get_best_wk_01_n_dt(data)                            ((0x00003F00&(data))>>8)
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_p_dt_shift                                (0)
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_p_dt_mask                                 (0x0000003F)
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_p_dt(data)                                (0x0000003F&((data)<<0))
#define DC_PHY_RESULT_CAL_TAP_5_best_wk_01_p_dt_src(data)                            ((0x0000003F&(data))>>0)
#define DC_PHY_RESULT_CAL_TAP_5_get_best_wk_01_p_dt(data)                            ((0x0000003F&(data))>>0)


#define DC_PHY_RESULT_CAL_TAP_6                                                      0x18008974
#define DC_PHY_RESULT_CAL_TAP_6_reg_addr                                             "0xB8008974"
#define DC_PHY_RESULT_CAL_TAP_6_reg                                                  0xB8008974
#define set_DC_PHY_RESULT_CAL_TAP_6_reg(data)   (*((volatile unsigned int*) DC_PHY_RESULT_CAL_TAP_6_reg)=data)
#define get_DC_PHY_RESULT_CAL_TAP_6_reg   (*((volatile unsigned int*) DC_PHY_RESULT_CAL_TAP_6_reg))
#define DC_PHY_RESULT_CAL_TAP_6_inst_adr                                             "0x005D"
#define DC_PHY_RESULT_CAL_TAP_6_inst                                                 0x005D
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_n_odt_shift                               (24)
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_n_odt_mask                                (0x3F000000)
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_n_odt(data)                               (0x3F000000&((data)<<24))
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_n_odt_src(data)                           ((0x3F000000&(data))>>24)
#define DC_PHY_RESULT_CAL_TAP_6_get_best_wk_23_n_odt(data)                           ((0x3F000000&(data))>>24)
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_p_odt_shift                               (16)
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_p_odt_mask                                (0x003F0000)
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_p_odt(data)                               (0x003F0000&((data)<<16))
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_p_odt_src(data)                           ((0x003F0000&(data))>>16)
#define DC_PHY_RESULT_CAL_TAP_6_get_best_wk_23_p_odt(data)                           ((0x003F0000&(data))>>16)
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_n_dt_shift                                (8)
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_n_dt_mask                                 (0x00003F00)
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_n_dt(data)                                (0x00003F00&((data)<<8))
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_n_dt_src(data)                            ((0x00003F00&(data))>>8)
#define DC_PHY_RESULT_CAL_TAP_6_get_best_wk_23_n_dt(data)                            ((0x00003F00&(data))>>8)
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_p_dt_shift                                (0)
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_p_dt_mask                                 (0x0000003F)
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_p_dt(data)                                (0x0000003F&((data)<<0))
#define DC_PHY_RESULT_CAL_TAP_6_best_wk_23_p_dt_src(data)                            ((0x0000003F&(data))>>0)
#define DC_PHY_RESULT_CAL_TAP_6_get_best_wk_23_p_dt(data)                            ((0x0000003F&(data))>>0)


#define DC_PHY_SYNC_RST_WK                                                           0x18008978
#define DC_PHY_SYNC_RST_WK_reg_addr                                                  "0xB8008978"
#define DC_PHY_SYNC_RST_WK_reg                                                       0xB8008978
#define set_DC_PHY_SYNC_RST_WK_reg(data)   (*((volatile unsigned int*) DC_PHY_SYNC_RST_WK_reg)=data)
#define get_DC_PHY_SYNC_RST_WK_reg   (*((volatile unsigned int*) DC_PHY_SYNC_RST_WK_reg))
#define DC_PHY_SYNC_RST_WK_inst_adr                                                  "0x005E"
#define DC_PHY_SYNC_RST_WK_inst                                                      0x005E
#define DC_PHY_SYNC_RST_WK_odt_diff_threshold_shift                                  (16)
#define DC_PHY_SYNC_RST_WK_odt_diff_threshold_mask                                   (0x003F0000)
#define DC_PHY_SYNC_RST_WK_odt_diff_threshold(data)                                  (0x003F0000&((data)<<16))
#define DC_PHY_SYNC_RST_WK_odt_diff_threshold_src(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_SYNC_RST_WK_get_odt_diff_threshold(data)                              ((0x003F0000&(data))>>16)
#define DC_PHY_SYNC_RST_WK_duty_diff_threshold_shift                                 (8)
#define DC_PHY_SYNC_RST_WK_duty_diff_threshold_mask                                  (0x00003F00)
#define DC_PHY_SYNC_RST_WK_duty_diff_threshold(data)                                 (0x00003F00&((data)<<8))
#define DC_PHY_SYNC_RST_WK_duty_diff_threshold_src(data)                             ((0x00003F00&(data))>>8)
#define DC_PHY_SYNC_RST_WK_get_duty_diff_threshold(data)                             ((0x00003F00&(data))>>8)
#define DC_PHY_SYNC_RST_WK_cal_proc_done_shift                                       (7)
#define DC_PHY_SYNC_RST_WK_cal_proc_done_mask                                        (0x00000080)
#define DC_PHY_SYNC_RST_WK_cal_proc_done(data)                                       (0x00000080&((data)<<7))
#define DC_PHY_SYNC_RST_WK_cal_proc_done_src(data)                                   ((0x00000080&(data))>>7)
#define DC_PHY_SYNC_RST_WK_get_cal_proc_done(data)                                   ((0x00000080&(data))>>7)
#define DC_PHY_SYNC_RST_WK_wk_threshold_shift                                        (1)
#define DC_PHY_SYNC_RST_WK_wk_threshold_mask                                         (0x0000007E)
#define DC_PHY_SYNC_RST_WK_wk_threshold(data)                                        (0x0000007E&((data)<<1))
#define DC_PHY_SYNC_RST_WK_wk_threshold_src(data)                                    ((0x0000007E&(data))>>1)
#define DC_PHY_SYNC_RST_WK_get_wk_threshold(data)                                    ((0x0000007E&(data))>>1)
#define DC_PHY_SYNC_RST_WK_sync_rst_wk_thr_shift                                     (0)
#define DC_PHY_SYNC_RST_WK_sync_rst_wk_thr_mask                                      (0x00000001)
#define DC_PHY_SYNC_RST_WK_sync_rst_wk_thr(data)                                     (0x00000001&((data)<<0))
#define DC_PHY_SYNC_RST_WK_sync_rst_wk_thr_src(data)                                 ((0x00000001&(data))>>0)
#define DC_PHY_SYNC_RST_WK_get_sync_rst_wk_thr(data)                                 ((0x00000001&(data))>>0)


#define DC_PHY_SYNC_RST_FIFO_PT                                                      0x1800897C
#define DC_PHY_SYNC_RST_FIFO_PT_reg_addr                                             "0xB800897C"
#define DC_PHY_SYNC_RST_FIFO_PT_reg                                                  0xB800897C
#define set_DC_PHY_SYNC_RST_FIFO_PT_reg(data)   (*((volatile unsigned int*) DC_PHY_SYNC_RST_FIFO_PT_reg)=data)
#define get_DC_PHY_SYNC_RST_FIFO_PT_reg   (*((volatile unsigned int*) DC_PHY_SYNC_RST_FIFO_PT_reg))
#define DC_PHY_SYNC_RST_FIFO_PT_inst_adr                                             "0x005F"
#define DC_PHY_SYNC_RST_FIFO_PT_inst                                                 0x005F
#define DC_PHY_SYNC_RST_FIFO_PT_sync_rst_fifo_pt_shift                               (0)
#define DC_PHY_SYNC_RST_FIFO_PT_sync_rst_fifo_pt_mask                                (0x00000001)
#define DC_PHY_SYNC_RST_FIFO_PT_sync_rst_fifo_pt(data)                               (0x00000001&((data)<<0))
#define DC_PHY_SYNC_RST_FIFO_PT_sync_rst_fifo_pt_src(data)                           ((0x00000001&(data))>>0)
#define DC_PHY_SYNC_RST_FIFO_PT_get_sync_rst_fifo_pt(data)                           ((0x00000001&(data))>>0)


#define DC_PHY_CAL_OUT_DATA_A                                                        0x18008980
#define DC_PHY_CAL_OUT_DATA_A_reg_addr                                               "0xB8008980"
#define DC_PHY_CAL_OUT_DATA_A_reg                                                    0xB8008980
#define set_DC_PHY_CAL_OUT_DATA_A_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL_OUT_DATA_A_reg)=data)
#define get_DC_PHY_CAL_OUT_DATA_A_reg   (*((volatile unsigned int*) DC_PHY_CAL_OUT_DATA_A_reg))
#define DC_PHY_CAL_OUT_DATA_A_inst_adr                                               "0x0060"
#define DC_PHY_CAL_OUT_DATA_A_inst                                                   0x0060
#define DC_PHY_CAL_OUT_DATA_A_cal_out_data_1_shift                                   (16)
#define DC_PHY_CAL_OUT_DATA_A_cal_out_data_1_mask                                    (0xFFFF0000)
#define DC_PHY_CAL_OUT_DATA_A_cal_out_data_1(data)                                   (0xFFFF0000&((data)<<16))
#define DC_PHY_CAL_OUT_DATA_A_cal_out_data_1_src(data)                               ((0xFFFF0000&(data))>>16)
#define DC_PHY_CAL_OUT_DATA_A_get_cal_out_data_1(data)                               ((0xFFFF0000&(data))>>16)
#define DC_PHY_CAL_OUT_DATA_A_cal_out_data_0_shift                                   (0)
#define DC_PHY_CAL_OUT_DATA_A_cal_out_data_0_mask                                    (0x0000FFFF)
#define DC_PHY_CAL_OUT_DATA_A_cal_out_data_0(data)                                   (0x0000FFFF&((data)<<0))
#define DC_PHY_CAL_OUT_DATA_A_cal_out_data_0_src(data)                               ((0x0000FFFF&(data))>>0)
#define DC_PHY_CAL_OUT_DATA_A_get_cal_out_data_0(data)                               ((0x0000FFFF&(data))>>0)


#define DC_PHY_CAL_OUT_DATA_B                                                        0x18008984
#define DC_PHY_CAL_OUT_DATA_B_reg_addr                                               "0xB8008984"
#define DC_PHY_CAL_OUT_DATA_B_reg                                                    0xB8008984
#define set_DC_PHY_CAL_OUT_DATA_B_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL_OUT_DATA_B_reg)=data)
#define get_DC_PHY_CAL_OUT_DATA_B_reg   (*((volatile unsigned int*) DC_PHY_CAL_OUT_DATA_B_reg))
#define DC_PHY_CAL_OUT_DATA_B_inst_adr                                               "0x0061"
#define DC_PHY_CAL_OUT_DATA_B_inst                                                   0x0061
#define DC_PHY_CAL_OUT_DATA_B_cal_out_data_3_shift                                   (16)
#define DC_PHY_CAL_OUT_DATA_B_cal_out_data_3_mask                                    (0xFFFF0000)
#define DC_PHY_CAL_OUT_DATA_B_cal_out_data_3(data)                                   (0xFFFF0000&((data)<<16))
#define DC_PHY_CAL_OUT_DATA_B_cal_out_data_3_src(data)                               ((0xFFFF0000&(data))>>16)
#define DC_PHY_CAL_OUT_DATA_B_get_cal_out_data_3(data)                               ((0xFFFF0000&(data))>>16)
#define DC_PHY_CAL_OUT_DATA_B_cal_out_data_2_shift                                   (0)
#define DC_PHY_CAL_OUT_DATA_B_cal_out_data_2_mask                                    (0x0000FFFF)
#define DC_PHY_CAL_OUT_DATA_B_cal_out_data_2(data)                                   (0x0000FFFF&((data)<<0))
#define DC_PHY_CAL_OUT_DATA_B_cal_out_data_2_src(data)                               ((0x0000FFFF&(data))>>0)
#define DC_PHY_CAL_OUT_DATA_B_get_cal_out_data_2(data)                               ((0x0000FFFF&(data))>>0)


#define DC_PHY_CAL_GLD_DATA_A                                                        0x18008988
#define DC_PHY_CAL_GLD_DATA_A_reg_addr                                               "0xB8008988"
#define DC_PHY_CAL_GLD_DATA_A_reg                                                    0xB8008988
#define set_DC_PHY_CAL_GLD_DATA_A_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL_GLD_DATA_A_reg)=data)
#define get_DC_PHY_CAL_GLD_DATA_A_reg   (*((volatile unsigned int*) DC_PHY_CAL_GLD_DATA_A_reg))
#define DC_PHY_CAL_GLD_DATA_A_inst_adr                                               "0x0062"
#define DC_PHY_CAL_GLD_DATA_A_inst                                                   0x0062
#define DC_PHY_CAL_GLD_DATA_A_cal_gld_data_1_shift                                   (16)
#define DC_PHY_CAL_GLD_DATA_A_cal_gld_data_1_mask                                    (0xFFFF0000)
#define DC_PHY_CAL_GLD_DATA_A_cal_gld_data_1(data)                                   (0xFFFF0000&((data)<<16))
#define DC_PHY_CAL_GLD_DATA_A_cal_gld_data_1_src(data)                               ((0xFFFF0000&(data))>>16)
#define DC_PHY_CAL_GLD_DATA_A_get_cal_gld_data_1(data)                               ((0xFFFF0000&(data))>>16)
#define DC_PHY_CAL_GLD_DATA_A_cal_gld_data_0_shift                                   (0)
#define DC_PHY_CAL_GLD_DATA_A_cal_gld_data_0_mask                                    (0x0000FFFF)
#define DC_PHY_CAL_GLD_DATA_A_cal_gld_data_0(data)                                   (0x0000FFFF&((data)<<0))
#define DC_PHY_CAL_GLD_DATA_A_cal_gld_data_0_src(data)                               ((0x0000FFFF&(data))>>0)
#define DC_PHY_CAL_GLD_DATA_A_get_cal_gld_data_0(data)                               ((0x0000FFFF&(data))>>0)


#define DC_PHY_CAL_GLD_DATA_B                                                        0x1800898C
#define DC_PHY_CAL_GLD_DATA_B_reg_addr                                               "0xB800898C"
#define DC_PHY_CAL_GLD_DATA_B_reg                                                    0xB800898C
#define set_DC_PHY_CAL_GLD_DATA_B_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL_GLD_DATA_B_reg)=data)
#define get_DC_PHY_CAL_GLD_DATA_B_reg   (*((volatile unsigned int*) DC_PHY_CAL_GLD_DATA_B_reg))
#define DC_PHY_CAL_GLD_DATA_B_inst_adr                                               "0x0063"
#define DC_PHY_CAL_GLD_DATA_B_inst                                                   0x0063
#define DC_PHY_CAL_GLD_DATA_B_cal_gld_data_3_shift                                   (16)
#define DC_PHY_CAL_GLD_DATA_B_cal_gld_data_3_mask                                    (0xFFFF0000)
#define DC_PHY_CAL_GLD_DATA_B_cal_gld_data_3(data)                                   (0xFFFF0000&((data)<<16))
#define DC_PHY_CAL_GLD_DATA_B_cal_gld_data_3_src(data)                               ((0xFFFF0000&(data))>>16)
#define DC_PHY_CAL_GLD_DATA_B_get_cal_gld_data_3(data)                               ((0xFFFF0000&(data))>>16)
#define DC_PHY_CAL_GLD_DATA_B_cal_gld_data_2_shift                                   (0)
#define DC_PHY_CAL_GLD_DATA_B_cal_gld_data_2_mask                                    (0x0000FFFF)
#define DC_PHY_CAL_GLD_DATA_B_cal_gld_data_2(data)                                   (0x0000FFFF&((data)<<0))
#define DC_PHY_CAL_GLD_DATA_B_cal_gld_data_2_src(data)                               ((0x0000FFFF&(data))>>0)
#define DC_PHY_CAL_GLD_DATA_B_get_cal_gld_data_2(data)                               ((0x0000FFFF&(data))>>0)


#define DC_PHY_CAL_CNT_CTRL                                                          0x18008990
#define DC_PHY_CAL_CNT_CTRL_reg_addr                                                 "0xB8008990"
#define DC_PHY_CAL_CNT_CTRL_reg                                                      0xB8008990
#define set_DC_PHY_CAL_CNT_CTRL_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL_CNT_CTRL_reg)=data)
#define get_DC_PHY_CAL_CNT_CTRL_reg   (*((volatile unsigned int*) DC_PHY_CAL_CNT_CTRL_reg))
#define DC_PHY_CAL_CNT_CTRL_inst_adr                                                 "0x0064"
#define DC_PHY_CAL_CNT_CTRL_inst                                                     0x0064
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_p_end_shift                                   (28)
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_p_end_mask                                    (0xF0000000)
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_p_end(data)                                   (0xF0000000&((data)<<28))
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_p_end_src(data)                               ((0xF0000000&(data))>>28)
#define DC_PHY_CAL_CNT_CTRL_get_id_cal_cnt_p_end(data)                               ((0xF0000000&(data))>>28)
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_p_srt_shift                                   (24)
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_p_srt_mask                                    (0x0F000000)
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_p_srt(data)                                   (0x0F000000&((data)<<24))
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_p_srt_src(data)                               ((0x0F000000&(data))>>24)
#define DC_PHY_CAL_CNT_CTRL_get_id_cal_cnt_p_srt(data)                               ((0x0F000000&(data))>>24)
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_n_end_shift                                   (20)
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_n_end_mask                                    (0x00F00000)
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_n_end(data)                                   (0x00F00000&((data)<<20))
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_n_end_src(data)                               ((0x00F00000&(data))>>20)
#define DC_PHY_CAL_CNT_CTRL_get_id_cal_cnt_n_end(data)                               ((0x00F00000&(data))>>20)
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_n_srt_shift                                   (16)
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_n_srt_mask                                    (0x000F0000)
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_n_srt(data)                                   (0x000F0000&((data)<<16))
#define DC_PHY_CAL_CNT_CTRL_id_cal_cnt_n_srt_src(data)                               ((0x000F0000&(data))>>16)
#define DC_PHY_CAL_CNT_CTRL_get_id_cal_cnt_n_srt(data)                               ((0x000F0000&(data))>>16)
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_p_end_shift                                  (12)
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_p_end_mask                                   (0x0000F000)
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_p_end(data)                                  (0x0000F000&((data)<<12))
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_p_end_src(data)                              ((0x0000F000&(data))>>12)
#define DC_PHY_CAL_CNT_CTRL_get_odt_cal_cnt_p_end(data)                              ((0x0000F000&(data))>>12)
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_p_srt_shift                                  (8)
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_p_srt_mask                                   (0x00000F00)
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_p_srt(data)                                  (0x00000F00&((data)<<8))
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_p_srt_src(data)                              ((0x00000F00&(data))>>8)
#define DC_PHY_CAL_CNT_CTRL_get_odt_cal_cnt_p_srt(data)                              ((0x00000F00&(data))>>8)
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_n_end_shift                                  (4)
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_n_end_mask                                   (0x000000F0)
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_n_end(data)                                  (0x000000F0&((data)<<4))
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_n_end_src(data)                              ((0x000000F0&(data))>>4)
#define DC_PHY_CAL_CNT_CTRL_get_odt_cal_cnt_n_end(data)                              ((0x000000F0&(data))>>4)
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_n_srt_shift                                  (0)
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_n_srt_mask                                   (0x0000000F)
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_n_srt(data)                                  (0x0000000F&((data)<<0))
#define DC_PHY_CAL_CNT_CTRL_odt_cal_cnt_n_srt_src(data)                              ((0x0000000F&(data))>>0)
#define DC_PHY_CAL_CNT_CTRL_get_odt_cal_cnt_n_srt(data)                              ((0x0000000F&(data))>>0)


#define DC_PHY_MUX2TO1_CTRL                                                          0x18008994
#define DC_PHY_MUX2TO1_CTRL_reg_addr                                                 "0xB8008994"
#define DC_PHY_MUX2TO1_CTRL_reg                                                      0xB8008994
#define set_DC_PHY_MUX2TO1_CTRL_reg(data)   (*((volatile unsigned int*) DC_PHY_MUX2TO1_CTRL_reg)=data)
#define get_DC_PHY_MUX2TO1_CTRL_reg   (*((volatile unsigned int*) DC_PHY_MUX2TO1_CTRL_reg))
#define DC_PHY_MUX2TO1_CTRL_inst_adr                                                 "0x0065"
#define DC_PHY_MUX2TO1_CTRL_inst                                                     0x0065
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_1_mux_sel_shift                                  (11)
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_1_mux_sel_mask                                   (0x00000800)
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_1_mux_sel(data)                                  (0x00000800&((data)<<11))
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_1_mux_sel_src(data)                              ((0x00000800&(data))>>11)
#define DC_PHY_MUX2TO1_CTRL_get_ddr_clk_1_mux_sel(data)                              ((0x00000800&(data))>>11)
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_0_mux_sel_shift                                  (10)
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_0_mux_sel_mask                                   (0x00000400)
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_0_mux_sel(data)                                  (0x00000400&((data)<<10))
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_0_mux_sel_src(data)                              ((0x00000400&(data))>>10)
#define DC_PHY_MUX2TO1_CTRL_get_ddr_clk_0_mux_sel(data)                              ((0x00000400&(data))>>10)
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_1_2x_div2_ph_sel_shift                           (9)
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_1_2x_div2_ph_sel_mask                            (0x00000200)
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_1_2x_div2_ph_sel(data)                           (0x00000200&((data)<<9))
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_1_2x_div2_ph_sel_src(data)                       ((0x00000200&(data))>>9)
#define DC_PHY_MUX2TO1_CTRL_get_ddr_clk_1_2x_div2_ph_sel(data)                       ((0x00000200&(data))>>9)
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_0_2x_div2_ph_sel_shift                           (8)
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_0_2x_div2_ph_sel_mask                            (0x00000100)
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_0_2x_div2_ph_sel(data)                           (0x00000100&((data)<<8))
#define DC_PHY_MUX2TO1_CTRL_ddr_clk_0_2x_div2_ph_sel_src(data)                       ((0x00000100&(data))>>8)
#define DC_PHY_MUX2TO1_CTRL_get_ddr_clk_0_2x_div2_ph_sel(data)                       ((0x00000100&(data))>>8)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs3_mux_sel_shift                                   (7)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs3_mux_sel_mask                                    (0x00000080)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs3_mux_sel(data)                                   (0x00000080&((data)<<7))
#define DC_PHY_MUX2TO1_CTRL_mck_dqs3_mux_sel_src(data)                               ((0x00000080&(data))>>7)
#define DC_PHY_MUX2TO1_CTRL_get_mck_dqs3_mux_sel(data)                               ((0x00000080&(data))>>7)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs2_mux_sel_shift                                   (6)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs2_mux_sel_mask                                    (0x00000040)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs2_mux_sel(data)                                   (0x00000040&((data)<<6))
#define DC_PHY_MUX2TO1_CTRL_mck_dqs2_mux_sel_src(data)                               ((0x00000040&(data))>>6)
#define DC_PHY_MUX2TO1_CTRL_get_mck_dqs2_mux_sel(data)                               ((0x00000040&(data))>>6)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs1_mux_sel_shift                                   (5)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs1_mux_sel_mask                                    (0x00000020)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs1_mux_sel(data)                                   (0x00000020&((data)<<5))
#define DC_PHY_MUX2TO1_CTRL_mck_dqs1_mux_sel_src(data)                               ((0x00000020&(data))>>5)
#define DC_PHY_MUX2TO1_CTRL_get_mck_dqs1_mux_sel(data)                               ((0x00000020&(data))>>5)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs0_mux_sel_shift                                   (4)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs0_mux_sel_mask                                    (0x00000010)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs0_mux_sel(data)                                   (0x00000010&((data)<<4))
#define DC_PHY_MUX2TO1_CTRL_mck_dqs0_mux_sel_src(data)                               ((0x00000010&(data))>>4)
#define DC_PHY_MUX2TO1_CTRL_get_mck_dqs0_mux_sel(data)                               ((0x00000010&(data))>>4)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs3_2x_div2_ph_sel_shift                            (3)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs3_2x_div2_ph_sel_mask                             (0x00000008)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs3_2x_div2_ph_sel(data)                            (0x00000008&((data)<<3))
#define DC_PHY_MUX2TO1_CTRL_mck_dqs3_2x_div2_ph_sel_src(data)                        ((0x00000008&(data))>>3)
#define DC_PHY_MUX2TO1_CTRL_get_mck_dqs3_2x_div2_ph_sel(data)                        ((0x00000008&(data))>>3)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs2_2x_div2_ph_sel_shift                            (2)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs2_2x_div2_ph_sel_mask                             (0x00000004)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs2_2x_div2_ph_sel(data)                            (0x00000004&((data)<<2))
#define DC_PHY_MUX2TO1_CTRL_mck_dqs2_2x_div2_ph_sel_src(data)                        ((0x00000004&(data))>>2)
#define DC_PHY_MUX2TO1_CTRL_get_mck_dqs2_2x_div2_ph_sel(data)                        ((0x00000004&(data))>>2)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs1_2x_div2_ph_sel_shift                            (1)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs1_2x_div2_ph_sel_mask                             (0x00000002)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs1_2x_div2_ph_sel(data)                            (0x00000002&((data)<<1))
#define DC_PHY_MUX2TO1_CTRL_mck_dqs1_2x_div2_ph_sel_src(data)                        ((0x00000002&(data))>>1)
#define DC_PHY_MUX2TO1_CTRL_get_mck_dqs1_2x_div2_ph_sel(data)                        ((0x00000002&(data))>>1)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs0_2x_div2_ph_sel_shift                            (0)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs0_2x_div2_ph_sel_mask                             (0x00000001)
#define DC_PHY_MUX2TO1_CTRL_mck_dqs0_2x_div2_ph_sel(data)                            (0x00000001&((data)<<0))
#define DC_PHY_MUX2TO1_CTRL_mck_dqs0_2x_div2_ph_sel_src(data)                        ((0x00000001&(data))>>0)
#define DC_PHY_MUX2TO1_CTRL_get_mck_dqs0_2x_div2_ph_sel(data)                        ((0x00000001&(data))>>0)


#define DC_PHY_DUMMY_REG                                                             0x1800899C
#define DC_PHY_DUMMY_REG_reg_addr                                                    "0xB800899C"
#define DC_PHY_DUMMY_REG_reg                                                         0xB800899C
#define set_DC_PHY_DUMMY_REG_reg(data)   (*((volatile unsigned int*) DC_PHY_DUMMY_REG_reg)=data)
#define get_DC_PHY_DUMMY_REG_reg   (*((volatile unsigned int*) DC_PHY_DUMMY_REG_reg))
#define DC_PHY_DUMMY_REG_inst_adr                                                    "0x0067"
#define DC_PHY_DUMMY_REG_inst                                                        0x0067
#define DC_PHY_DUMMY_REG_dummy_reg_shift                                             (0)
#define DC_PHY_DUMMY_REG_dummy_reg_mask                                              (0xFFFFFFFF)
#define DC_PHY_DUMMY_REG_dummy_reg(data)                                             (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DUMMY_REG_dummy_reg_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DUMMY_REG_get_dummy_reg(data)                                         ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DT_SET0                                                               0x18008a00
#define DC_PHY_DT_SET0_reg_addr                                                      "0xB8008A00"
#define DC_PHY_DT_SET0_reg                                                           0xB8008A00
#define set_DC_PHY_DT_SET0_reg(data)   (*((volatile unsigned int*) DC_PHY_DT_SET0_reg)=data)
#define get_DC_PHY_DT_SET0_reg   (*((volatile unsigned int*) DC_PHY_DT_SET0_reg))
#define DC_PHY_DT_SET0_inst_adr                                                      "0x0080"
#define DC_PHY_DT_SET0_inst                                                          0x0080
#define DC_PHY_DT_SET0_dt_set_0_shift                                                (0)
#define DC_PHY_DT_SET0_dt_set_0_mask                                                 (0x0000FFFF)
#define DC_PHY_DT_SET0_dt_set_0(data)                                                (0x0000FFFF&((data)<<0))
#define DC_PHY_DT_SET0_dt_set_0_src(data)                                            ((0x0000FFFF&(data))>>0)
#define DC_PHY_DT_SET0_get_dt_set_0(data)                                            ((0x0000FFFF&(data))>>0)


#define DC_PHY_DT_SET1                                                               0x18008a04
#define DC_PHY_DT_SET1_reg_addr                                                      "0xB8008A04"
#define DC_PHY_DT_SET1_reg                                                           0xB8008A04
#define set_DC_PHY_DT_SET1_reg(data)   (*((volatile unsigned int*) DC_PHY_DT_SET1_reg)=data)
#define get_DC_PHY_DT_SET1_reg   (*((volatile unsigned int*) DC_PHY_DT_SET1_reg))
#define DC_PHY_DT_SET1_inst_adr                                                      "0x0081"
#define DC_PHY_DT_SET1_inst                                                          0x0081
#define DC_PHY_DT_SET1_dt_set_1_shift                                                (0)
#define DC_PHY_DT_SET1_dt_set_1_mask                                                 (0xFFFFFFFF)
#define DC_PHY_DT_SET1_dt_set_1(data)                                                (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DT_SET1_dt_set_1_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DT_SET1_get_dt_set_1(data)                                            ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DT_CTL                                                                0x18008a08
#define DC_PHY_DT_CTL_reg_addr                                                       "0xB8008A08"
#define DC_PHY_DT_CTL_reg                                                            0xB8008A08
#define set_DC_PHY_DT_CTL_reg(data)   (*((volatile unsigned int*) DC_PHY_DT_CTL_reg)=data)
#define get_DC_PHY_DT_CTL_reg   (*((volatile unsigned int*) DC_PHY_DT_CTL_reg))
#define DC_PHY_DT_CTL_inst_adr                                                       "0x0082"
#define DC_PHY_DT_CTL_inst                                                           0x0082
#define DC_PHY_DT_CTL_update_dqs_shift                                               (1)
#define DC_PHY_DT_CTL_update_dqs_mask                                                (0x00000002)
#define DC_PHY_DT_CTL_update_dqs(data)                                               (0x00000002&((data)<<1))
#define DC_PHY_DT_CTL_update_dqs_src(data)                                           ((0x00000002&(data))>>1)
#define DC_PHY_DT_CTL_get_update_dqs(data)                                           ((0x00000002&(data))>>1)
#define DC_PHY_DT_CTL_update_dq_shift                                                (0)
#define DC_PHY_DT_CTL_update_dq_mask                                                 (0x00000001)
#define DC_PHY_DT_CTL_update_dq(data)                                                (0x00000001&((data)<<0))
#define DC_PHY_DT_CTL_update_dq_src(data)                                            ((0x00000001&(data))>>0)
#define DC_PHY_DT_CTL_get_update_dq(data)                                            ((0x00000001&(data))>>0)


#define DC_PHY_CAL_DT_RESULT                                                         0x18008a0c
#define DC_PHY_CAL_DT_RESULT_reg_addr                                                "0xB8008A0C"
#define DC_PHY_CAL_DT_RESULT_reg                                                     0xB8008A0C
#define set_DC_PHY_CAL_DT_RESULT_reg(data)   (*((volatile unsigned int*) DC_PHY_CAL_DT_RESULT_reg)=data)
#define get_DC_PHY_CAL_DT_RESULT_reg   (*((volatile unsigned int*) DC_PHY_CAL_DT_RESULT_reg))
#define DC_PHY_CAL_DT_RESULT_inst_adr                                                "0x0083"
#define DC_PHY_CAL_DT_RESULT_inst                                                    0x0083
#define DC_PHY_CAL_DT_RESULT_odt_23_n_shift                                          (17)
#define DC_PHY_CAL_DT_RESULT_odt_23_n_mask                                           (0x000E0000)
#define DC_PHY_CAL_DT_RESULT_odt_23_n(data)                                          (0x000E0000&((data)<<17))
#define DC_PHY_CAL_DT_RESULT_odt_23_n_src(data)                                      ((0x000E0000&(data))>>17)
#define DC_PHY_CAL_DT_RESULT_get_odt_23_n(data)                                      ((0x000E0000&(data))>>17)
#define DC_PHY_CAL_DT_RESULT_odt_23_p_shift                                          (14)
#define DC_PHY_CAL_DT_RESULT_odt_23_p_mask                                           (0x0001C000)
#define DC_PHY_CAL_DT_RESULT_odt_23_p(data)                                          (0x0001C000&((data)<<14))
#define DC_PHY_CAL_DT_RESULT_odt_23_p_src(data)                                      ((0x0001C000&(data))>>14)
#define DC_PHY_CAL_DT_RESULT_get_odt_23_p(data)                                      ((0x0001C000&(data))>>14)
#define DC_PHY_CAL_DT_RESULT_odt_01_n_shift                                          (11)
#define DC_PHY_CAL_DT_RESULT_odt_01_n_mask                                           (0x00003800)
#define DC_PHY_CAL_DT_RESULT_odt_01_n(data)                                          (0x00003800&((data)<<11))
#define DC_PHY_CAL_DT_RESULT_odt_01_n_src(data)                                      ((0x00003800&(data))>>11)
#define DC_PHY_CAL_DT_RESULT_get_odt_01_n(data)                                      ((0x00003800&(data))>>11)
#define DC_PHY_CAL_DT_RESULT_odt_01_p_shift                                          (8)
#define DC_PHY_CAL_DT_RESULT_odt_01_p_mask                                           (0x00000700)
#define DC_PHY_CAL_DT_RESULT_odt_01_p(data)                                          (0x00000700&((data)<<8))
#define DC_PHY_CAL_DT_RESULT_odt_01_p_src(data)                                      ((0x00000700&(data))>>8)
#define DC_PHY_CAL_DT_RESULT_get_odt_01_p(data)                                      ((0x00000700&(data))>>8)
#define DC_PHY_CAL_DT_RESULT_indt_23_n_shift                                         (6)
#define DC_PHY_CAL_DT_RESULT_indt_23_n_mask                                          (0x000000C0)
#define DC_PHY_CAL_DT_RESULT_indt_23_n(data)                                         (0x000000C0&((data)<<6))
#define DC_PHY_CAL_DT_RESULT_indt_23_n_src(data)                                     ((0x000000C0&(data))>>6)
#define DC_PHY_CAL_DT_RESULT_get_indt_23_n(data)                                     ((0x000000C0&(data))>>6)
#define DC_PHY_CAL_DT_RESULT_indt_23_p_shift                                         (4)
#define DC_PHY_CAL_DT_RESULT_indt_23_p_mask                                          (0x00000030)
#define DC_PHY_CAL_DT_RESULT_indt_23_p(data)                                         (0x00000030&((data)<<4))
#define DC_PHY_CAL_DT_RESULT_indt_23_p_src(data)                                     ((0x00000030&(data))>>4)
#define DC_PHY_CAL_DT_RESULT_get_indt_23_p(data)                                     ((0x00000030&(data))>>4)
#define DC_PHY_CAL_DT_RESULT_indt_01_n_shift                                         (2)
#define DC_PHY_CAL_DT_RESULT_indt_01_n_mask                                          (0x0000000C)
#define DC_PHY_CAL_DT_RESULT_indt_01_n(data)                                         (0x0000000C&((data)<<2))
#define DC_PHY_CAL_DT_RESULT_indt_01_n_src(data)                                     ((0x0000000C&(data))>>2)
#define DC_PHY_CAL_DT_RESULT_get_indt_01_n(data)                                     ((0x0000000C&(data))>>2)
#define DC_PHY_CAL_DT_RESULT_indt_01_p_shift                                         (0)
#define DC_PHY_CAL_DT_RESULT_indt_01_p_mask                                          (0x00000003)
#define DC_PHY_CAL_DT_RESULT_indt_01_p(data)                                         (0x00000003&((data)<<0))
#define DC_PHY_CAL_DT_RESULT_indt_01_p_src(data)                                     ((0x00000003&(data))>>0)
#define DC_PHY_CAL_DT_RESULT_get_indt_01_p(data)                                     ((0x00000003&(data))>>0)


#define DC_PHY_ODT_TTCP_SET_PRE                                                      0x18008a10
#define DC_PHY_ODT_TTCP_SET_PRE_reg_addr                                             "0xB8008A10"
#define DC_PHY_ODT_TTCP_SET_PRE_reg                                                  0xB8008A10
#define set_DC_PHY_ODT_TTCP_SET_PRE_reg(data)   (*((volatile unsigned int*) DC_PHY_ODT_TTCP_SET_PRE_reg)=data)
#define get_DC_PHY_ODT_TTCP_SET_PRE_reg   (*((volatile unsigned int*) DC_PHY_ODT_TTCP_SET_PRE_reg))
#define DC_PHY_ODT_TTCP_SET_PRE_inst_adr                                             "0x0084"
#define DC_PHY_ODT_TTCP_SET_PRE_inst                                                 0x0084
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_7_pre_shift                             (28)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_7_pre_mask                              (0xF0000000)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_7_pre(data)                             (0xF0000000&((data)<<28))
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_7_pre_src(data)                         ((0xF0000000&(data))>>28)
#define DC_PHY_ODT_TTCP_SET_PRE_get_odt_ttcp_set_7_pre(data)                         ((0xF0000000&(data))>>28)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_6_pre_shift                             (24)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_6_pre_mask                              (0x0F000000)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_6_pre(data)                             (0x0F000000&((data)<<24))
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_6_pre_src(data)                         ((0x0F000000&(data))>>24)
#define DC_PHY_ODT_TTCP_SET_PRE_get_odt_ttcp_set_6_pre(data)                         ((0x0F000000&(data))>>24)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_5_pre_shift                             (20)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_5_pre_mask                              (0x00F00000)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_5_pre(data)                             (0x00F00000&((data)<<20))
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_5_pre_src(data)                         ((0x00F00000&(data))>>20)
#define DC_PHY_ODT_TTCP_SET_PRE_get_odt_ttcp_set_5_pre(data)                         ((0x00F00000&(data))>>20)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_4_pre_shift                             (16)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_4_pre_mask                              (0x000F0000)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_4_pre(data)                             (0x000F0000&((data)<<16))
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_4_pre_src(data)                         ((0x000F0000&(data))>>16)
#define DC_PHY_ODT_TTCP_SET_PRE_get_odt_ttcp_set_4_pre(data)                         ((0x000F0000&(data))>>16)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_3_pre_shift                             (12)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_3_pre_mask                              (0x0000F000)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_3_pre(data)                             (0x0000F000&((data)<<12))
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_3_pre_src(data)                         ((0x0000F000&(data))>>12)
#define DC_PHY_ODT_TTCP_SET_PRE_get_odt_ttcp_set_3_pre(data)                         ((0x0000F000&(data))>>12)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_2_pre_shift                             (8)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_2_pre_mask                              (0x00000F00)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_2_pre(data)                             (0x00000F00&((data)<<8))
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_2_pre_src(data)                         ((0x00000F00&(data))>>8)
#define DC_PHY_ODT_TTCP_SET_PRE_get_odt_ttcp_set_2_pre(data)                         ((0x00000F00&(data))>>8)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_1_pre_shift                             (4)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_1_pre_mask                              (0x000000F0)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_1_pre(data)                             (0x000000F0&((data)<<4))
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_1_pre_src(data)                         ((0x000000F0&(data))>>4)
#define DC_PHY_ODT_TTCP_SET_PRE_get_odt_ttcp_set_1_pre(data)                         ((0x000000F0&(data))>>4)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_0_pre_shift                             (0)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_0_pre_mask                              (0x0000000F)
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_0_pre(data)                             (0x0000000F&((data)<<0))
#define DC_PHY_ODT_TTCP_SET_PRE_odt_ttcp_set_0_pre_src(data)                         ((0x0000000F&(data))>>0)
#define DC_PHY_ODT_TTCP_SET_PRE_get_odt_ttcp_set_0_pre(data)                         ((0x0000000F&(data))>>0)


#define DC_PHY_ODT_TTCN_SET_PRE                                                      0x18008a14
#define DC_PHY_ODT_TTCN_SET_PRE_reg_addr                                             "0xB8008A14"
#define DC_PHY_ODT_TTCN_SET_PRE_reg                                                  0xB8008A14
#define set_DC_PHY_ODT_TTCN_SET_PRE_reg(data)   (*((volatile unsigned int*) DC_PHY_ODT_TTCN_SET_PRE_reg)=data)
#define get_DC_PHY_ODT_TTCN_SET_PRE_reg   (*((volatile unsigned int*) DC_PHY_ODT_TTCN_SET_PRE_reg))
#define DC_PHY_ODT_TTCN_SET_PRE_inst_adr                                             "0x0085"
#define DC_PHY_ODT_TTCN_SET_PRE_inst                                                 0x0085
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_7_pre_shift                             (28)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_7_pre_mask                              (0xF0000000)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_7_pre(data)                             (0xF0000000&((data)<<28))
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_7_pre_src(data)                         ((0xF0000000&(data))>>28)
#define DC_PHY_ODT_TTCN_SET_PRE_get_odt_ttcn_set_7_pre(data)                         ((0xF0000000&(data))>>28)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_6_pre_shift                             (24)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_6_pre_mask                              (0x0F000000)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_6_pre(data)                             (0x0F000000&((data)<<24))
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_6_pre_src(data)                         ((0x0F000000&(data))>>24)
#define DC_PHY_ODT_TTCN_SET_PRE_get_odt_ttcn_set_6_pre(data)                         ((0x0F000000&(data))>>24)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_5_pre_shift                             (20)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_5_pre_mask                              (0x00F00000)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_5_pre(data)                             (0x00F00000&((data)<<20))
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_5_pre_src(data)                         ((0x00F00000&(data))>>20)
#define DC_PHY_ODT_TTCN_SET_PRE_get_odt_ttcn_set_5_pre(data)                         ((0x00F00000&(data))>>20)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_4_pre_shift                             (16)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_4_pre_mask                              (0x000F0000)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_4_pre(data)                             (0x000F0000&((data)<<16))
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_4_pre_src(data)                         ((0x000F0000&(data))>>16)
#define DC_PHY_ODT_TTCN_SET_PRE_get_odt_ttcn_set_4_pre(data)                         ((0x000F0000&(data))>>16)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_3_pre_shift                             (12)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_3_pre_mask                              (0x0000F000)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_3_pre(data)                             (0x0000F000&((data)<<12))
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_3_pre_src(data)                         ((0x0000F000&(data))>>12)
#define DC_PHY_ODT_TTCN_SET_PRE_get_odt_ttcn_set_3_pre(data)                         ((0x0000F000&(data))>>12)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_2_pre_shift                             (8)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_2_pre_mask                              (0x00000F00)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_2_pre(data)                             (0x00000F00&((data)<<8))
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_2_pre_src(data)                         ((0x00000F00&(data))>>8)
#define DC_PHY_ODT_TTCN_SET_PRE_get_odt_ttcn_set_2_pre(data)                         ((0x00000F00&(data))>>8)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_1_pre_shift                             (4)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_1_pre_mask                              (0x000000F0)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_1_pre(data)                             (0x000000F0&((data)<<4))
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_1_pre_src(data)                         ((0x000000F0&(data))>>4)
#define DC_PHY_ODT_TTCN_SET_PRE_get_odt_ttcn_set_1_pre(data)                         ((0x000000F0&(data))>>4)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_0_pre_shift                             (0)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_0_pre_mask                              (0x0000000F)
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_0_pre(data)                             (0x0000000F&((data)<<0))
#define DC_PHY_ODT_TTCN_SET_PRE_odt_ttcn_set_0_pre_src(data)                         ((0x0000000F&(data))>>0)
#define DC_PHY_ODT_TTCN_SET_PRE_get_odt_ttcn_set_0_pre(data)                         ((0x0000000F&(data))>>0)


#define DC_PHY_ODT_TTFP_SET_PRE                                                      0x18008a18
#define DC_PHY_ODT_TTFP_SET_PRE_reg_addr                                             "0xB8008A18"
#define DC_PHY_ODT_TTFP_SET_PRE_reg                                                  0xB8008A18
#define set_DC_PHY_ODT_TTFP_SET_PRE_reg(data)   (*((volatile unsigned int*) DC_PHY_ODT_TTFP_SET_PRE_reg)=data)
#define get_DC_PHY_ODT_TTFP_SET_PRE_reg   (*((volatile unsigned int*) DC_PHY_ODT_TTFP_SET_PRE_reg))
#define DC_PHY_ODT_TTFP_SET_PRE_inst_adr                                             "0x0086"
#define DC_PHY_ODT_TTFP_SET_PRE_inst                                                 0x0086
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_7_pre_shift                             (21)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_7_pre_mask                              (0x00E00000)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_7_pre(data)                             (0x00E00000&((data)<<21))
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_7_pre_src(data)                         ((0x00E00000&(data))>>21)
#define DC_PHY_ODT_TTFP_SET_PRE_get_odt_ttfp_set_7_pre(data)                         ((0x00E00000&(data))>>21)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_6_pre_shift                             (18)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_6_pre_mask                              (0x001C0000)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_6_pre(data)                             (0x001C0000&((data)<<18))
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_6_pre_src(data)                         ((0x001C0000&(data))>>18)
#define DC_PHY_ODT_TTFP_SET_PRE_get_odt_ttfp_set_6_pre(data)                         ((0x001C0000&(data))>>18)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_5_pre_shift                             (15)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_5_pre_mask                              (0x00038000)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_5_pre(data)                             (0x00038000&((data)<<15))
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_5_pre_src(data)                         ((0x00038000&(data))>>15)
#define DC_PHY_ODT_TTFP_SET_PRE_get_odt_ttfp_set_5_pre(data)                         ((0x00038000&(data))>>15)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_4_pre_shift                             (12)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_4_pre_mask                              (0x00007000)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_4_pre(data)                             (0x00007000&((data)<<12))
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_4_pre_src(data)                         ((0x00007000&(data))>>12)
#define DC_PHY_ODT_TTFP_SET_PRE_get_odt_ttfp_set_4_pre(data)                         ((0x00007000&(data))>>12)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_3_pre_shift                             (9)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_3_pre_mask                              (0x00000E00)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_3_pre(data)                             (0x00000E00&((data)<<9))
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_3_pre_src(data)                         ((0x00000E00&(data))>>9)
#define DC_PHY_ODT_TTFP_SET_PRE_get_odt_ttfp_set_3_pre(data)                         ((0x00000E00&(data))>>9)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_2_pre_shift                             (6)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_2_pre_mask                              (0x000001C0)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_2_pre(data)                             (0x000001C0&((data)<<6))
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_2_pre_src(data)                         ((0x000001C0&(data))>>6)
#define DC_PHY_ODT_TTFP_SET_PRE_get_odt_ttfp_set_2_pre(data)                         ((0x000001C0&(data))>>6)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_1_pre_shift                             (3)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_1_pre_mask                              (0x00000038)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_1_pre(data)                             (0x00000038&((data)<<3))
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_1_pre_src(data)                         ((0x00000038&(data))>>3)
#define DC_PHY_ODT_TTFP_SET_PRE_get_odt_ttfp_set_1_pre(data)                         ((0x00000038&(data))>>3)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_0_pre_shift                             (0)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_0_pre_mask                              (0x00000007)
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_0_pre(data)                             (0x00000007&((data)<<0))
#define DC_PHY_ODT_TTFP_SET_PRE_odt_ttfp_set_0_pre_src(data)                         ((0x00000007&(data))>>0)
#define DC_PHY_ODT_TTFP_SET_PRE_get_odt_ttfp_set_0_pre(data)                         ((0x00000007&(data))>>0)


#define DC_PHY_ODT_TTFN_SET_PRE                                                      0x18008a1c
#define DC_PHY_ODT_TTFN_SET_PRE_reg_addr                                             "0xB8008A1C"
#define DC_PHY_ODT_TTFN_SET_PRE_reg                                                  0xB8008A1C
#define set_DC_PHY_ODT_TTFN_SET_PRE_reg(data)   (*((volatile unsigned int*) DC_PHY_ODT_TTFN_SET_PRE_reg)=data)
#define get_DC_PHY_ODT_TTFN_SET_PRE_reg   (*((volatile unsigned int*) DC_PHY_ODT_TTFN_SET_PRE_reg))
#define DC_PHY_ODT_TTFN_SET_PRE_inst_adr                                             "0x0087"
#define DC_PHY_ODT_TTFN_SET_PRE_inst                                                 0x0087
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_7_pre_shift                             (21)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_7_pre_mask                              (0x00E00000)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_7_pre(data)                             (0x00E00000&((data)<<21))
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_7_pre_src(data)                         ((0x00E00000&(data))>>21)
#define DC_PHY_ODT_TTFN_SET_PRE_get_odt_ttfn_set_7_pre(data)                         ((0x00E00000&(data))>>21)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_6_pre_shift                             (18)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_6_pre_mask                              (0x001C0000)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_6_pre(data)                             (0x001C0000&((data)<<18))
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_6_pre_src(data)                         ((0x001C0000&(data))>>18)
#define DC_PHY_ODT_TTFN_SET_PRE_get_odt_ttfn_set_6_pre(data)                         ((0x001C0000&(data))>>18)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_5_pre_shift                             (15)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_5_pre_mask                              (0x00038000)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_5_pre(data)                             (0x00038000&((data)<<15))
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_5_pre_src(data)                         ((0x00038000&(data))>>15)
#define DC_PHY_ODT_TTFN_SET_PRE_get_odt_ttfn_set_5_pre(data)                         ((0x00038000&(data))>>15)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_4_pre_shift                             (12)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_4_pre_mask                              (0x00007000)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_4_pre(data)                             (0x00007000&((data)<<12))
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_4_pre_src(data)                         ((0x00007000&(data))>>12)
#define DC_PHY_ODT_TTFN_SET_PRE_get_odt_ttfn_set_4_pre(data)                         ((0x00007000&(data))>>12)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_3_pre_shift                             (9)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_3_pre_mask                              (0x00000E00)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_3_pre(data)                             (0x00000E00&((data)<<9))
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_3_pre_src(data)                         ((0x00000E00&(data))>>9)
#define DC_PHY_ODT_TTFN_SET_PRE_get_odt_ttfn_set_3_pre(data)                         ((0x00000E00&(data))>>9)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_2_pre_shift                             (6)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_2_pre_mask                              (0x000001C0)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_2_pre(data)                             (0x000001C0&((data)<<6))
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_2_pre_src(data)                         ((0x000001C0&(data))>>6)
#define DC_PHY_ODT_TTFN_SET_PRE_get_odt_ttfn_set_2_pre(data)                         ((0x000001C0&(data))>>6)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_1_pre_shift                             (3)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_1_pre_mask                              (0x00000038)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_1_pre(data)                             (0x00000038&((data)<<3))
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_1_pre_src(data)                         ((0x00000038&(data))>>3)
#define DC_PHY_ODT_TTFN_SET_PRE_get_odt_ttfn_set_1_pre(data)                         ((0x00000038&(data))>>3)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_0_pre_shift                             (0)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_0_pre_mask                              (0x00000007)
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_0_pre(data)                             (0x00000007&((data)<<0))
#define DC_PHY_ODT_TTFN_SET_PRE_odt_ttfn_set_0_pre_src(data)                         ((0x00000007&(data))>>0)
#define DC_PHY_ODT_TTFN_SET_PRE_get_odt_ttfn_set_0_pre(data)                         ((0x00000007&(data))>>0)


#define DC_PHY_OCDP_SET_PRE                                                          0x18008a20
#define DC_PHY_OCDP_SET_PRE_reg_addr                                                 "0xB8008A20"
#define DC_PHY_OCDP_SET_PRE_reg                                                      0xB8008A20
#define set_DC_PHY_OCDP_SET_PRE_reg(data)   (*((volatile unsigned int*) DC_PHY_OCDP_SET_PRE_reg)=data)
#define get_DC_PHY_OCDP_SET_PRE_reg   (*((volatile unsigned int*) DC_PHY_OCDP_SET_PRE_reg))
#define DC_PHY_OCDP_SET_PRE_inst_adr                                                 "0x0088"
#define DC_PHY_OCDP_SET_PRE_inst                                                     0x0088
#define DC_PHY_OCDP_SET_PRE_ocdp_set_7_pre_shift                                     (28)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_7_pre_mask                                      (0xF0000000)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_7_pre(data)                                     (0xF0000000&((data)<<28))
#define DC_PHY_OCDP_SET_PRE_ocdp_set_7_pre_src(data)                                 ((0xF0000000&(data))>>28)
#define DC_PHY_OCDP_SET_PRE_get_ocdp_set_7_pre(data)                                 ((0xF0000000&(data))>>28)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_6_pre_shift                                     (24)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_6_pre_mask                                      (0x0F000000)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_6_pre(data)                                     (0x0F000000&((data)<<24))
#define DC_PHY_OCDP_SET_PRE_ocdp_set_6_pre_src(data)                                 ((0x0F000000&(data))>>24)
#define DC_PHY_OCDP_SET_PRE_get_ocdp_set_6_pre(data)                                 ((0x0F000000&(data))>>24)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_5_pre_shift                                     (20)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_5_pre_mask                                      (0x00F00000)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_5_pre(data)                                     (0x00F00000&((data)<<20))
#define DC_PHY_OCDP_SET_PRE_ocdp_set_5_pre_src(data)                                 ((0x00F00000&(data))>>20)
#define DC_PHY_OCDP_SET_PRE_get_ocdp_set_5_pre(data)                                 ((0x00F00000&(data))>>20)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_4_pre_shift                                     (16)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_4_pre_mask                                      (0x000F0000)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_4_pre(data)                                     (0x000F0000&((data)<<16))
#define DC_PHY_OCDP_SET_PRE_ocdp_set_4_pre_src(data)                                 ((0x000F0000&(data))>>16)
#define DC_PHY_OCDP_SET_PRE_get_ocdp_set_4_pre(data)                                 ((0x000F0000&(data))>>16)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_3_pre_shift                                     (12)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_3_pre_mask                                      (0x0000F000)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_3_pre(data)                                     (0x0000F000&((data)<<12))
#define DC_PHY_OCDP_SET_PRE_ocdp_set_3_pre_src(data)                                 ((0x0000F000&(data))>>12)
#define DC_PHY_OCDP_SET_PRE_get_ocdp_set_3_pre(data)                                 ((0x0000F000&(data))>>12)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_2_pre_shift                                     (8)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_2_pre_mask                                      (0x00000F00)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_2_pre(data)                                     (0x00000F00&((data)<<8))
#define DC_PHY_OCDP_SET_PRE_ocdp_set_2_pre_src(data)                                 ((0x00000F00&(data))>>8)
#define DC_PHY_OCDP_SET_PRE_get_ocdp_set_2_pre(data)                                 ((0x00000F00&(data))>>8)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_1_pre_shift                                     (4)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_1_pre_mask                                      (0x000000F0)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_1_pre(data)                                     (0x000000F0&((data)<<4))
#define DC_PHY_OCDP_SET_PRE_ocdp_set_1_pre_src(data)                                 ((0x000000F0&(data))>>4)
#define DC_PHY_OCDP_SET_PRE_get_ocdp_set_1_pre(data)                                 ((0x000000F0&(data))>>4)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_0_pre_shift                                     (0)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_0_pre_mask                                      (0x0000000F)
#define DC_PHY_OCDP_SET_PRE_ocdp_set_0_pre(data)                                     (0x0000000F&((data)<<0))
#define DC_PHY_OCDP_SET_PRE_ocdp_set_0_pre_src(data)                                 ((0x0000000F&(data))>>0)
#define DC_PHY_OCDP_SET_PRE_get_ocdp_set_0_pre(data)                                 ((0x0000000F&(data))>>0)


#define DC_PHY_OCDN_SET_PRE                                                          0x18008a24
#define DC_PHY_OCDN_SET_PRE_reg_addr                                                 "0xB8008A24"
#define DC_PHY_OCDN_SET_PRE_reg                                                      0xB8008A24
#define set_DC_PHY_OCDN_SET_PRE_reg(data)   (*((volatile unsigned int*) DC_PHY_OCDN_SET_PRE_reg)=data)
#define get_DC_PHY_OCDN_SET_PRE_reg   (*((volatile unsigned int*) DC_PHY_OCDN_SET_PRE_reg))
#define DC_PHY_OCDN_SET_PRE_inst_adr                                                 "0x0089"
#define DC_PHY_OCDN_SET_PRE_inst                                                     0x0089
#define DC_PHY_OCDN_SET_PRE_ocdn_set_7_pre_shift                                     (28)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_7_pre_mask                                      (0xF0000000)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_7_pre(data)                                     (0xF0000000&((data)<<28))
#define DC_PHY_OCDN_SET_PRE_ocdn_set_7_pre_src(data)                                 ((0xF0000000&(data))>>28)
#define DC_PHY_OCDN_SET_PRE_get_ocdn_set_7_pre(data)                                 ((0xF0000000&(data))>>28)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_6_pre_shift                                     (24)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_6_pre_mask                                      (0x0F000000)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_6_pre(data)                                     (0x0F000000&((data)<<24))
#define DC_PHY_OCDN_SET_PRE_ocdn_set_6_pre_src(data)                                 ((0x0F000000&(data))>>24)
#define DC_PHY_OCDN_SET_PRE_get_ocdn_set_6_pre(data)                                 ((0x0F000000&(data))>>24)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_5_pre_shift                                     (20)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_5_pre_mask                                      (0x00F00000)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_5_pre(data)                                     (0x00F00000&((data)<<20))
#define DC_PHY_OCDN_SET_PRE_ocdn_set_5_pre_src(data)                                 ((0x00F00000&(data))>>20)
#define DC_PHY_OCDN_SET_PRE_get_ocdn_set_5_pre(data)                                 ((0x00F00000&(data))>>20)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_4_pre_shift                                     (16)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_4_pre_mask                                      (0x000F0000)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_4_pre(data)                                     (0x000F0000&((data)<<16))
#define DC_PHY_OCDN_SET_PRE_ocdn_set_4_pre_src(data)                                 ((0x000F0000&(data))>>16)
#define DC_PHY_OCDN_SET_PRE_get_ocdn_set_4_pre(data)                                 ((0x000F0000&(data))>>16)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_3_pre_shift                                     (12)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_3_pre_mask                                      (0x0000F000)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_3_pre(data)                                     (0x0000F000&((data)<<12))
#define DC_PHY_OCDN_SET_PRE_ocdn_set_3_pre_src(data)                                 ((0x0000F000&(data))>>12)
#define DC_PHY_OCDN_SET_PRE_get_ocdn_set_3_pre(data)                                 ((0x0000F000&(data))>>12)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_2_pre_shift                                     (8)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_2_pre_mask                                      (0x00000F00)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_2_pre(data)                                     (0x00000F00&((data)<<8))
#define DC_PHY_OCDN_SET_PRE_ocdn_set_2_pre_src(data)                                 ((0x00000F00&(data))>>8)
#define DC_PHY_OCDN_SET_PRE_get_ocdn_set_2_pre(data)                                 ((0x00000F00&(data))>>8)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_1_pre_shift                                     (4)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_1_pre_mask                                      (0x000000F0)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_1_pre(data)                                     (0x000000F0&((data)<<4))
#define DC_PHY_OCDN_SET_PRE_ocdn_set_1_pre_src(data)                                 ((0x000000F0&(data))>>4)
#define DC_PHY_OCDN_SET_PRE_get_ocdn_set_1_pre(data)                                 ((0x000000F0&(data))>>4)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_0_pre_shift                                     (0)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_0_pre_mask                                      (0x0000000F)
#define DC_PHY_OCDN_SET_PRE_ocdn_set_0_pre(data)                                     (0x0000000F&((data)<<0))
#define DC_PHY_OCDN_SET_PRE_ocdn_set_0_pre_src(data)                                 ((0x0000000F&(data))>>0)
#define DC_PHY_OCDN_SET_PRE_get_ocdn_set_0_pre(data)                                 ((0x0000000F&(data))>>0)


#define DC_PHY_ODT_TTCP_SET                                                          0x18008a28
#define DC_PHY_ODT_TTCP_SET_reg_addr                                                 "0xB8008A28"
#define DC_PHY_ODT_TTCP_SET_reg                                                      0xB8008A28
#define set_DC_PHY_ODT_TTCP_SET_reg(data)   (*((volatile unsigned int*) DC_PHY_ODT_TTCP_SET_reg)=data)
#define get_DC_PHY_ODT_TTCP_SET_reg   (*((volatile unsigned int*) DC_PHY_ODT_TTCP_SET_reg))
#define DC_PHY_ODT_TTCP_SET_inst_adr                                                 "0x008A"
#define DC_PHY_ODT_TTCP_SET_inst                                                     0x008A
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_7_shift                                     (28)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_7_mask                                      (0xF0000000)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_7(data)                                     (0xF0000000&((data)<<28))
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_7_src(data)                                 ((0xF0000000&(data))>>28)
#define DC_PHY_ODT_TTCP_SET_get_odt_ttcp_set_7(data)                                 ((0xF0000000&(data))>>28)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_6_shift                                     (24)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_6_mask                                      (0x0F000000)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_6(data)                                     (0x0F000000&((data)<<24))
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_6_src(data)                                 ((0x0F000000&(data))>>24)
#define DC_PHY_ODT_TTCP_SET_get_odt_ttcp_set_6(data)                                 ((0x0F000000&(data))>>24)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_5_shift                                     (20)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_5_mask                                      (0x00F00000)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_5(data)                                     (0x00F00000&((data)<<20))
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_5_src(data)                                 ((0x00F00000&(data))>>20)
#define DC_PHY_ODT_TTCP_SET_get_odt_ttcp_set_5(data)                                 ((0x00F00000&(data))>>20)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_4_shift                                     (16)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_4_mask                                      (0x000F0000)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_4(data)                                     (0x000F0000&((data)<<16))
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_4_src(data)                                 ((0x000F0000&(data))>>16)
#define DC_PHY_ODT_TTCP_SET_get_odt_ttcp_set_4(data)                                 ((0x000F0000&(data))>>16)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_3_shift                                     (12)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_3_mask                                      (0x0000F000)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_3(data)                                     (0x0000F000&((data)<<12))
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_3_src(data)                                 ((0x0000F000&(data))>>12)
#define DC_PHY_ODT_TTCP_SET_get_odt_ttcp_set_3(data)                                 ((0x0000F000&(data))>>12)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_2_shift                                     (8)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_2_mask                                      (0x00000F00)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_2(data)                                     (0x00000F00&((data)<<8))
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_2_src(data)                                 ((0x00000F00&(data))>>8)
#define DC_PHY_ODT_TTCP_SET_get_odt_ttcp_set_2(data)                                 ((0x00000F00&(data))>>8)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_1_shift                                     (4)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_1_mask                                      (0x000000F0)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_1(data)                                     (0x000000F0&((data)<<4))
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_1_src(data)                                 ((0x000000F0&(data))>>4)
#define DC_PHY_ODT_TTCP_SET_get_odt_ttcp_set_1(data)                                 ((0x000000F0&(data))>>4)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_0_shift                                     (0)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_0_mask                                      (0x0000000F)
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_0(data)                                     (0x0000000F&((data)<<0))
#define DC_PHY_ODT_TTCP_SET_odt_ttcp_set_0_src(data)                                 ((0x0000000F&(data))>>0)
#define DC_PHY_ODT_TTCP_SET_get_odt_ttcp_set_0(data)                                 ((0x0000000F&(data))>>0)


#define DC_PHY_ODT_TTCN_SET                                                          0x18008a2c
#define DC_PHY_ODT_TTCN_SET_reg_addr                                                 "0xB8008A2C"
#define DC_PHY_ODT_TTCN_SET_reg                                                      0xB8008A2C
#define set_DC_PHY_ODT_TTCN_SET_reg(data)   (*((volatile unsigned int*) DC_PHY_ODT_TTCN_SET_reg)=data)
#define get_DC_PHY_ODT_TTCN_SET_reg   (*((volatile unsigned int*) DC_PHY_ODT_TTCN_SET_reg))
#define DC_PHY_ODT_TTCN_SET_inst_adr                                                 "0x008B"
#define DC_PHY_ODT_TTCN_SET_inst                                                     0x008B
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_7_shift                                     (28)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_7_mask                                      (0xF0000000)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_7(data)                                     (0xF0000000&((data)<<28))
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_7_src(data)                                 ((0xF0000000&(data))>>28)
#define DC_PHY_ODT_TTCN_SET_get_odt_ttcn_set_7(data)                                 ((0xF0000000&(data))>>28)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_6_shift                                     (24)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_6_mask                                      (0x0F000000)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_6(data)                                     (0x0F000000&((data)<<24))
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_6_src(data)                                 ((0x0F000000&(data))>>24)
#define DC_PHY_ODT_TTCN_SET_get_odt_ttcn_set_6(data)                                 ((0x0F000000&(data))>>24)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_5_shift                                     (20)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_5_mask                                      (0x00F00000)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_5(data)                                     (0x00F00000&((data)<<20))
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_5_src(data)                                 ((0x00F00000&(data))>>20)
#define DC_PHY_ODT_TTCN_SET_get_odt_ttcn_set_5(data)                                 ((0x00F00000&(data))>>20)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_4_shift                                     (16)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_4_mask                                      (0x000F0000)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_4(data)                                     (0x000F0000&((data)<<16))
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_4_src(data)                                 ((0x000F0000&(data))>>16)
#define DC_PHY_ODT_TTCN_SET_get_odt_ttcn_set_4(data)                                 ((0x000F0000&(data))>>16)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_3_shift                                     (12)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_3_mask                                      (0x0000F000)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_3(data)                                     (0x0000F000&((data)<<12))
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_3_src(data)                                 ((0x0000F000&(data))>>12)
#define DC_PHY_ODT_TTCN_SET_get_odt_ttcn_set_3(data)                                 ((0x0000F000&(data))>>12)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_2_shift                                     (8)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_2_mask                                      (0x00000F00)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_2(data)                                     (0x00000F00&((data)<<8))
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_2_src(data)                                 ((0x00000F00&(data))>>8)
#define DC_PHY_ODT_TTCN_SET_get_odt_ttcn_set_2(data)                                 ((0x00000F00&(data))>>8)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_1_shift                                     (4)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_1_mask                                      (0x000000F0)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_1(data)                                     (0x000000F0&((data)<<4))
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_1_src(data)                                 ((0x000000F0&(data))>>4)
#define DC_PHY_ODT_TTCN_SET_get_odt_ttcn_set_1(data)                                 ((0x000000F0&(data))>>4)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_0_shift                                     (0)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_0_mask                                      (0x0000000F)
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_0(data)                                     (0x0000000F&((data)<<0))
#define DC_PHY_ODT_TTCN_SET_odt_ttcn_set_0_src(data)                                 ((0x0000000F&(data))>>0)
#define DC_PHY_ODT_TTCN_SET_get_odt_ttcn_set_0(data)                                 ((0x0000000F&(data))>>0)


#define DC_PHY_ODT_TTFP_SET                                                          0x18008a30
#define DC_PHY_ODT_TTFP_SET_reg_addr                                                 "0xB8008A30"
#define DC_PHY_ODT_TTFP_SET_reg                                                      0xB8008A30
#define set_DC_PHY_ODT_TTFP_SET_reg(data)   (*((volatile unsigned int*) DC_PHY_ODT_TTFP_SET_reg)=data)
#define get_DC_PHY_ODT_TTFP_SET_reg   (*((volatile unsigned int*) DC_PHY_ODT_TTFP_SET_reg))
#define DC_PHY_ODT_TTFP_SET_inst_adr                                                 "0x008C"
#define DC_PHY_ODT_TTFP_SET_inst                                                     0x008C
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_7_shift                                     (21)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_7_mask                                      (0x00E00000)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_7(data)                                     (0x00E00000&((data)<<21))
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_7_src(data)                                 ((0x00E00000&(data))>>21)
#define DC_PHY_ODT_TTFP_SET_get_odt_ttfp_set_7(data)                                 ((0x00E00000&(data))>>21)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_6_shift                                     (18)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_6_mask                                      (0x001C0000)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_6(data)                                     (0x001C0000&((data)<<18))
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_6_src(data)                                 ((0x001C0000&(data))>>18)
#define DC_PHY_ODT_TTFP_SET_get_odt_ttfp_set_6(data)                                 ((0x001C0000&(data))>>18)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_5_shift                                     (15)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_5_mask                                      (0x00038000)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_5(data)                                     (0x00038000&((data)<<15))
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_5_src(data)                                 ((0x00038000&(data))>>15)
#define DC_PHY_ODT_TTFP_SET_get_odt_ttfp_set_5(data)                                 ((0x00038000&(data))>>15)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_4_shift                                     (12)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_4_mask                                      (0x00007000)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_4(data)                                     (0x00007000&((data)<<12))
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_4_src(data)                                 ((0x00007000&(data))>>12)
#define DC_PHY_ODT_TTFP_SET_get_odt_ttfp_set_4(data)                                 ((0x00007000&(data))>>12)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_3_shift                                     (9)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_3_mask                                      (0x00000E00)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_3(data)                                     (0x00000E00&((data)<<9))
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_3_src(data)                                 ((0x00000E00&(data))>>9)
#define DC_PHY_ODT_TTFP_SET_get_odt_ttfp_set_3(data)                                 ((0x00000E00&(data))>>9)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_2_shift                                     (6)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_2_mask                                      (0x000001C0)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_2(data)                                     (0x000001C0&((data)<<6))
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_2_src(data)                                 ((0x000001C0&(data))>>6)
#define DC_PHY_ODT_TTFP_SET_get_odt_ttfp_set_2(data)                                 ((0x000001C0&(data))>>6)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_1_shift                                     (3)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_1_mask                                      (0x00000038)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_1(data)                                     (0x00000038&((data)<<3))
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_1_src(data)                                 ((0x00000038&(data))>>3)
#define DC_PHY_ODT_TTFP_SET_get_odt_ttfp_set_1(data)                                 ((0x00000038&(data))>>3)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_0_shift                                     (0)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_0_mask                                      (0x00000007)
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_0(data)                                     (0x00000007&((data)<<0))
#define DC_PHY_ODT_TTFP_SET_odt_ttfp_set_0_src(data)                                 ((0x00000007&(data))>>0)
#define DC_PHY_ODT_TTFP_SET_get_odt_ttfp_set_0(data)                                 ((0x00000007&(data))>>0)


#define DC_PHY_ODT_TTFN_SET                                                          0x18008a34
#define DC_PHY_ODT_TTFN_SET_reg_addr                                                 "0xB8008A34"
#define DC_PHY_ODT_TTFN_SET_reg                                                      0xB8008A34
#define set_DC_PHY_ODT_TTFN_SET_reg(data)   (*((volatile unsigned int*) DC_PHY_ODT_TTFN_SET_reg)=data)
#define get_DC_PHY_ODT_TTFN_SET_reg   (*((volatile unsigned int*) DC_PHY_ODT_TTFN_SET_reg))
#define DC_PHY_ODT_TTFN_SET_inst_adr                                                 "0x008D"
#define DC_PHY_ODT_TTFN_SET_inst                                                     0x008D
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_7_shift                                     (21)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_7_mask                                      (0x00E00000)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_7(data)                                     (0x00E00000&((data)<<21))
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_7_src(data)                                 ((0x00E00000&(data))>>21)
#define DC_PHY_ODT_TTFN_SET_get_odt_ttfn_set_7(data)                                 ((0x00E00000&(data))>>21)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_6_shift                                     (18)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_6_mask                                      (0x001C0000)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_6(data)                                     (0x001C0000&((data)<<18))
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_6_src(data)                                 ((0x001C0000&(data))>>18)
#define DC_PHY_ODT_TTFN_SET_get_odt_ttfn_set_6(data)                                 ((0x001C0000&(data))>>18)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_5_shift                                     (15)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_5_mask                                      (0x00038000)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_5(data)                                     (0x00038000&((data)<<15))
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_5_src(data)                                 ((0x00038000&(data))>>15)
#define DC_PHY_ODT_TTFN_SET_get_odt_ttfn_set_5(data)                                 ((0x00038000&(data))>>15)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_4_shift                                     (12)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_4_mask                                      (0x00007000)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_4(data)                                     (0x00007000&((data)<<12))
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_4_src(data)                                 ((0x00007000&(data))>>12)
#define DC_PHY_ODT_TTFN_SET_get_odt_ttfn_set_4(data)                                 ((0x00007000&(data))>>12)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_3_shift                                     (9)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_3_mask                                      (0x00000E00)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_3(data)                                     (0x00000E00&((data)<<9))
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_3_src(data)                                 ((0x00000E00&(data))>>9)
#define DC_PHY_ODT_TTFN_SET_get_odt_ttfn_set_3(data)                                 ((0x00000E00&(data))>>9)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_2_shift                                     (6)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_2_mask                                      (0x000001C0)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_2(data)                                     (0x000001C0&((data)<<6))
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_2_src(data)                                 ((0x000001C0&(data))>>6)
#define DC_PHY_ODT_TTFN_SET_get_odt_ttfn_set_2(data)                                 ((0x000001C0&(data))>>6)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_1_shift                                     (3)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_1_mask                                      (0x00000038)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_1(data)                                     (0x00000038&((data)<<3))
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_1_src(data)                                 ((0x00000038&(data))>>3)
#define DC_PHY_ODT_TTFN_SET_get_odt_ttfn_set_1(data)                                 ((0x00000038&(data))>>3)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_0_shift                                     (0)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_0_mask                                      (0x00000007)
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_0(data)                                     (0x00000007&((data)<<0))
#define DC_PHY_ODT_TTFN_SET_odt_ttfn_set_0_src(data)                                 ((0x00000007&(data))>>0)
#define DC_PHY_ODT_TTFN_SET_get_odt_ttfn_set_0(data)                                 ((0x00000007&(data))>>0)


#define DC_PHY_OCDP_SET                                                              0x18008a38
#define DC_PHY_OCDP_SET_reg_addr                                                     "0xB8008A38"
#define DC_PHY_OCDP_SET_reg                                                          0xB8008A38
#define set_DC_PHY_OCDP_SET_reg(data)   (*((volatile unsigned int*) DC_PHY_OCDP_SET_reg)=data)
#define get_DC_PHY_OCDP_SET_reg   (*((volatile unsigned int*) DC_PHY_OCDP_SET_reg))
#define DC_PHY_OCDP_SET_inst_adr                                                     "0x008E"
#define DC_PHY_OCDP_SET_inst                                                         0x008E
#define DC_PHY_OCDP_SET_ocdp_set_7_shift                                             (28)
#define DC_PHY_OCDP_SET_ocdp_set_7_mask                                              (0xF0000000)
#define DC_PHY_OCDP_SET_ocdp_set_7(data)                                             (0xF0000000&((data)<<28))
#define DC_PHY_OCDP_SET_ocdp_set_7_src(data)                                         ((0xF0000000&(data))>>28)
#define DC_PHY_OCDP_SET_get_ocdp_set_7(data)                                         ((0xF0000000&(data))>>28)
#define DC_PHY_OCDP_SET_ocdp_set_6_shift                                             (24)
#define DC_PHY_OCDP_SET_ocdp_set_6_mask                                              (0x0F000000)
#define DC_PHY_OCDP_SET_ocdp_set_6(data)                                             (0x0F000000&((data)<<24))
#define DC_PHY_OCDP_SET_ocdp_set_6_src(data)                                         ((0x0F000000&(data))>>24)
#define DC_PHY_OCDP_SET_get_ocdp_set_6(data)                                         ((0x0F000000&(data))>>24)
#define DC_PHY_OCDP_SET_ocdp_set_5_shift                                             (20)
#define DC_PHY_OCDP_SET_ocdp_set_5_mask                                              (0x00F00000)
#define DC_PHY_OCDP_SET_ocdp_set_5(data)                                             (0x00F00000&((data)<<20))
#define DC_PHY_OCDP_SET_ocdp_set_5_src(data)                                         ((0x00F00000&(data))>>20)
#define DC_PHY_OCDP_SET_get_ocdp_set_5(data)                                         ((0x00F00000&(data))>>20)
#define DC_PHY_OCDP_SET_ocdp_set_4_shift                                             (16)
#define DC_PHY_OCDP_SET_ocdp_set_4_mask                                              (0x000F0000)
#define DC_PHY_OCDP_SET_ocdp_set_4(data)                                             (0x000F0000&((data)<<16))
#define DC_PHY_OCDP_SET_ocdp_set_4_src(data)                                         ((0x000F0000&(data))>>16)
#define DC_PHY_OCDP_SET_get_ocdp_set_4(data)                                         ((0x000F0000&(data))>>16)
#define DC_PHY_OCDP_SET_ocdp_set_3_shift                                             (12)
#define DC_PHY_OCDP_SET_ocdp_set_3_mask                                              (0x0000F000)
#define DC_PHY_OCDP_SET_ocdp_set_3(data)                                             (0x0000F000&((data)<<12))
#define DC_PHY_OCDP_SET_ocdp_set_3_src(data)                                         ((0x0000F000&(data))>>12)
#define DC_PHY_OCDP_SET_get_ocdp_set_3(data)                                         ((0x0000F000&(data))>>12)
#define DC_PHY_OCDP_SET_ocdp_set_2_shift                                             (8)
#define DC_PHY_OCDP_SET_ocdp_set_2_mask                                              (0x00000F00)
#define DC_PHY_OCDP_SET_ocdp_set_2(data)                                             (0x00000F00&((data)<<8))
#define DC_PHY_OCDP_SET_ocdp_set_2_src(data)                                         ((0x00000F00&(data))>>8)
#define DC_PHY_OCDP_SET_get_ocdp_set_2(data)                                         ((0x00000F00&(data))>>8)
#define DC_PHY_OCDP_SET_ocdp_set_1_shift                                             (4)
#define DC_PHY_OCDP_SET_ocdp_set_1_mask                                              (0x000000F0)
#define DC_PHY_OCDP_SET_ocdp_set_1(data)                                             (0x000000F0&((data)<<4))
#define DC_PHY_OCDP_SET_ocdp_set_1_src(data)                                         ((0x000000F0&(data))>>4)
#define DC_PHY_OCDP_SET_get_ocdp_set_1(data)                                         ((0x000000F0&(data))>>4)
#define DC_PHY_OCDP_SET_ocdp_set_0_shift                                             (0)
#define DC_PHY_OCDP_SET_ocdp_set_0_mask                                              (0x0000000F)
#define DC_PHY_OCDP_SET_ocdp_set_0(data)                                             (0x0000000F&((data)<<0))
#define DC_PHY_OCDP_SET_ocdp_set_0_src(data)                                         ((0x0000000F&(data))>>0)
#define DC_PHY_OCDP_SET_get_ocdp_set_0(data)                                         ((0x0000000F&(data))>>0)


#define DC_PHY_OCDN_SET                                                              0x18008a3c
#define DC_PHY_OCDN_SET_reg_addr                                                     "0xB8008A3C"
#define DC_PHY_OCDN_SET_reg                                                          0xB8008A3C
#define set_DC_PHY_OCDN_SET_reg(data)   (*((volatile unsigned int*) DC_PHY_OCDN_SET_reg)=data)
#define get_DC_PHY_OCDN_SET_reg   (*((volatile unsigned int*) DC_PHY_OCDN_SET_reg))
#define DC_PHY_OCDN_SET_inst_adr                                                     "0x008F"
#define DC_PHY_OCDN_SET_inst                                                         0x008F
#define DC_PHY_OCDN_SET_ocdn_set_7_shift                                             (28)
#define DC_PHY_OCDN_SET_ocdn_set_7_mask                                              (0xF0000000)
#define DC_PHY_OCDN_SET_ocdn_set_7(data)                                             (0xF0000000&((data)<<28))
#define DC_PHY_OCDN_SET_ocdn_set_7_src(data)                                         ((0xF0000000&(data))>>28)
#define DC_PHY_OCDN_SET_get_ocdn_set_7(data)                                         ((0xF0000000&(data))>>28)
#define DC_PHY_OCDN_SET_ocdn_set_6_shift                                             (24)
#define DC_PHY_OCDN_SET_ocdn_set_6_mask                                              (0x0F000000)
#define DC_PHY_OCDN_SET_ocdn_set_6(data)                                             (0x0F000000&((data)<<24))
#define DC_PHY_OCDN_SET_ocdn_set_6_src(data)                                         ((0x0F000000&(data))>>24)
#define DC_PHY_OCDN_SET_get_ocdn_set_6(data)                                         ((0x0F000000&(data))>>24)
#define DC_PHY_OCDN_SET_ocdn_set_5_shift                                             (20)
#define DC_PHY_OCDN_SET_ocdn_set_5_mask                                              (0x00F00000)
#define DC_PHY_OCDN_SET_ocdn_set_5(data)                                             (0x00F00000&((data)<<20))
#define DC_PHY_OCDN_SET_ocdn_set_5_src(data)                                         ((0x00F00000&(data))>>20)
#define DC_PHY_OCDN_SET_get_ocdn_set_5(data)                                         ((0x00F00000&(data))>>20)
#define DC_PHY_OCDN_SET_ocdn_set_4_shift                                             (16)
#define DC_PHY_OCDN_SET_ocdn_set_4_mask                                              (0x000F0000)
#define DC_PHY_OCDN_SET_ocdn_set_4(data)                                             (0x000F0000&((data)<<16))
#define DC_PHY_OCDN_SET_ocdn_set_4_src(data)                                         ((0x000F0000&(data))>>16)
#define DC_PHY_OCDN_SET_get_ocdn_set_4(data)                                         ((0x000F0000&(data))>>16)
#define DC_PHY_OCDN_SET_ocdn_set_3_shift                                             (12)
#define DC_PHY_OCDN_SET_ocdn_set_3_mask                                              (0x0000F000)
#define DC_PHY_OCDN_SET_ocdn_set_3(data)                                             (0x0000F000&((data)<<12))
#define DC_PHY_OCDN_SET_ocdn_set_3_src(data)                                         ((0x0000F000&(data))>>12)
#define DC_PHY_OCDN_SET_get_ocdn_set_3(data)                                         ((0x0000F000&(data))>>12)
#define DC_PHY_OCDN_SET_ocdn_set_2_shift                                             (8)
#define DC_PHY_OCDN_SET_ocdn_set_2_mask                                              (0x00000F00)
#define DC_PHY_OCDN_SET_ocdn_set_2(data)                                             (0x00000F00&((data)<<8))
#define DC_PHY_OCDN_SET_ocdn_set_2_src(data)                                         ((0x00000F00&(data))>>8)
#define DC_PHY_OCDN_SET_get_ocdn_set_2(data)                                         ((0x00000F00&(data))>>8)
#define DC_PHY_OCDN_SET_ocdn_set_1_shift                                             (4)
#define DC_PHY_OCDN_SET_ocdn_set_1_mask                                              (0x000000F0)
#define DC_PHY_OCDN_SET_ocdn_set_1(data)                                             (0x000000F0&((data)<<4))
#define DC_PHY_OCDN_SET_ocdn_set_1_src(data)                                         ((0x000000F0&(data))>>4)
#define DC_PHY_OCDN_SET_get_ocdn_set_1(data)                                         ((0x000000F0&(data))>>4)
#define DC_PHY_OCDN_SET_ocdn_set_0_shift                                             (0)
#define DC_PHY_OCDN_SET_ocdn_set_0_mask                                              (0x0000000F)
#define DC_PHY_OCDN_SET_ocdn_set_0(data)                                             (0x0000000F&((data)<<0))
#define DC_PHY_OCDN_SET_ocdn_set_0_src(data)                                         ((0x0000000F&(data))>>0)
#define DC_PHY_OCDN_SET_get_ocdn_set_0(data)                                         ((0x0000000F&(data))>>0)


#define DC_PHY_DQ_TTC_SEL                                                            0x18008a40
#define DC_PHY_DQ_TTC_SEL_reg_addr                                                   "0xB8008A40"
#define DC_PHY_DQ_TTC_SEL_reg                                                        0xB8008A40
#define set_DC_PHY_DQ_TTC_SEL_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ_TTC_SEL_reg)=data)
#define get_DC_PHY_DQ_TTC_SEL_reg   (*((volatile unsigned int*) DC_PHY_DQ_TTC_SEL_reg))
#define DC_PHY_DQ_TTC_SEL_inst_adr                                                   "0x0090"
#define DC_PHY_DQ_TTC_SEL_inst                                                       0x0090
#define DC_PHY_DQ_TTC_SEL_dq_3_ttcn_sel_shift                                        (21)
#define DC_PHY_DQ_TTC_SEL_dq_3_ttcn_sel_mask                                         (0x00E00000)
#define DC_PHY_DQ_TTC_SEL_dq_3_ttcn_sel(data)                                        (0x00E00000&((data)<<21))
#define DC_PHY_DQ_TTC_SEL_dq_3_ttcn_sel_src(data)                                    ((0x00E00000&(data))>>21)
#define DC_PHY_DQ_TTC_SEL_get_dq_3_ttcn_sel(data)                                    ((0x00E00000&(data))>>21)
#define DC_PHY_DQ_TTC_SEL_dq_2_ttcn_sel_shift                                        (18)
#define DC_PHY_DQ_TTC_SEL_dq_2_ttcn_sel_mask                                         (0x001C0000)
#define DC_PHY_DQ_TTC_SEL_dq_2_ttcn_sel(data)                                        (0x001C0000&((data)<<18))
#define DC_PHY_DQ_TTC_SEL_dq_2_ttcn_sel_src(data)                                    ((0x001C0000&(data))>>18)
#define DC_PHY_DQ_TTC_SEL_get_dq_2_ttcn_sel(data)                                    ((0x001C0000&(data))>>18)
#define DC_PHY_DQ_TTC_SEL_dq_1_ttcn_sel_shift                                        (15)
#define DC_PHY_DQ_TTC_SEL_dq_1_ttcn_sel_mask                                         (0x00038000)
#define DC_PHY_DQ_TTC_SEL_dq_1_ttcn_sel(data)                                        (0x00038000&((data)<<15))
#define DC_PHY_DQ_TTC_SEL_dq_1_ttcn_sel_src(data)                                    ((0x00038000&(data))>>15)
#define DC_PHY_DQ_TTC_SEL_get_dq_1_ttcn_sel(data)                                    ((0x00038000&(data))>>15)
#define DC_PHY_DQ_TTC_SEL_dq_0_ttcn_sel_shift                                        (12)
#define DC_PHY_DQ_TTC_SEL_dq_0_ttcn_sel_mask                                         (0x00007000)
#define DC_PHY_DQ_TTC_SEL_dq_0_ttcn_sel(data)                                        (0x00007000&((data)<<12))
#define DC_PHY_DQ_TTC_SEL_dq_0_ttcn_sel_src(data)                                    ((0x00007000&(data))>>12)
#define DC_PHY_DQ_TTC_SEL_get_dq_0_ttcn_sel(data)                                    ((0x00007000&(data))>>12)
#define DC_PHY_DQ_TTC_SEL_dq_3_ttcp_sel_shift                                        (9)
#define DC_PHY_DQ_TTC_SEL_dq_3_ttcp_sel_mask                                         (0x00000E00)
#define DC_PHY_DQ_TTC_SEL_dq_3_ttcp_sel(data)                                        (0x00000E00&((data)<<9))
#define DC_PHY_DQ_TTC_SEL_dq_3_ttcp_sel_src(data)                                    ((0x00000E00&(data))>>9)
#define DC_PHY_DQ_TTC_SEL_get_dq_3_ttcp_sel(data)                                    ((0x00000E00&(data))>>9)
#define DC_PHY_DQ_TTC_SEL_dq_2_ttcp_sel_shift                                        (6)
#define DC_PHY_DQ_TTC_SEL_dq_2_ttcp_sel_mask                                         (0x000001C0)
#define DC_PHY_DQ_TTC_SEL_dq_2_ttcp_sel(data)                                        (0x000001C0&((data)<<6))
#define DC_PHY_DQ_TTC_SEL_dq_2_ttcp_sel_src(data)                                    ((0x000001C0&(data))>>6)
#define DC_PHY_DQ_TTC_SEL_get_dq_2_ttcp_sel(data)                                    ((0x000001C0&(data))>>6)
#define DC_PHY_DQ_TTC_SEL_dq_1_ttcp_sel_shift                                        (3)
#define DC_PHY_DQ_TTC_SEL_dq_1_ttcp_sel_mask                                         (0x00000038)
#define DC_PHY_DQ_TTC_SEL_dq_1_ttcp_sel(data)                                        (0x00000038&((data)<<3))
#define DC_PHY_DQ_TTC_SEL_dq_1_ttcp_sel_src(data)                                    ((0x00000038&(data))>>3)
#define DC_PHY_DQ_TTC_SEL_get_dq_1_ttcp_sel(data)                                    ((0x00000038&(data))>>3)
#define DC_PHY_DQ_TTC_SEL_dq_0_ttcp_sel_shift                                        (0)
#define DC_PHY_DQ_TTC_SEL_dq_0_ttcp_sel_mask                                         (0x00000007)
#define DC_PHY_DQ_TTC_SEL_dq_0_ttcp_sel(data)                                        (0x00000007&((data)<<0))
#define DC_PHY_DQ_TTC_SEL_dq_0_ttcp_sel_src(data)                                    ((0x00000007&(data))>>0)
#define DC_PHY_DQ_TTC_SEL_get_dq_0_ttcp_sel(data)                                    ((0x00000007&(data))>>0)


#define DC_PHY_DQ_TTF_SEL                                                            0x18008a44
#define DC_PHY_DQ_TTF_SEL_reg_addr                                                   "0xB8008A44"
#define DC_PHY_DQ_TTF_SEL_reg                                                        0xB8008A44
#define set_DC_PHY_DQ_TTF_SEL_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ_TTF_SEL_reg)=data)
#define get_DC_PHY_DQ_TTF_SEL_reg   (*((volatile unsigned int*) DC_PHY_DQ_TTF_SEL_reg))
#define DC_PHY_DQ_TTF_SEL_inst_adr                                                   "0x0091"
#define DC_PHY_DQ_TTF_SEL_inst                                                       0x0091
#define DC_PHY_DQ_TTF_SEL_dq_3_ttfn_sel_shift                                        (21)
#define DC_PHY_DQ_TTF_SEL_dq_3_ttfn_sel_mask                                         (0x00E00000)
#define DC_PHY_DQ_TTF_SEL_dq_3_ttfn_sel(data)                                        (0x00E00000&((data)<<21))
#define DC_PHY_DQ_TTF_SEL_dq_3_ttfn_sel_src(data)                                    ((0x00E00000&(data))>>21)
#define DC_PHY_DQ_TTF_SEL_get_dq_3_ttfn_sel(data)                                    ((0x00E00000&(data))>>21)
#define DC_PHY_DQ_TTF_SEL_dq_2_ttfn_sel_shift                                        (18)
#define DC_PHY_DQ_TTF_SEL_dq_2_ttfn_sel_mask                                         (0x001C0000)
#define DC_PHY_DQ_TTF_SEL_dq_2_ttfn_sel(data)                                        (0x001C0000&((data)<<18))
#define DC_PHY_DQ_TTF_SEL_dq_2_ttfn_sel_src(data)                                    ((0x001C0000&(data))>>18)
#define DC_PHY_DQ_TTF_SEL_get_dq_2_ttfn_sel(data)                                    ((0x001C0000&(data))>>18)
#define DC_PHY_DQ_TTF_SEL_dq_1_ttfn_sel_shift                                        (15)
#define DC_PHY_DQ_TTF_SEL_dq_1_ttfn_sel_mask                                         (0x00038000)
#define DC_PHY_DQ_TTF_SEL_dq_1_ttfn_sel(data)                                        (0x00038000&((data)<<15))
#define DC_PHY_DQ_TTF_SEL_dq_1_ttfn_sel_src(data)                                    ((0x00038000&(data))>>15)
#define DC_PHY_DQ_TTF_SEL_get_dq_1_ttfn_sel(data)                                    ((0x00038000&(data))>>15)
#define DC_PHY_DQ_TTF_SEL_dq_0_ttfn_sel_shift                                        (12)
#define DC_PHY_DQ_TTF_SEL_dq_0_ttfn_sel_mask                                         (0x00007000)
#define DC_PHY_DQ_TTF_SEL_dq_0_ttfn_sel(data)                                        (0x00007000&((data)<<12))
#define DC_PHY_DQ_TTF_SEL_dq_0_ttfn_sel_src(data)                                    ((0x00007000&(data))>>12)
#define DC_PHY_DQ_TTF_SEL_get_dq_0_ttfn_sel(data)                                    ((0x00007000&(data))>>12)
#define DC_PHY_DQ_TTF_SEL_dq_3_ttfp_sel_shift                                        (9)
#define DC_PHY_DQ_TTF_SEL_dq_3_ttfp_sel_mask                                         (0x00000E00)
#define DC_PHY_DQ_TTF_SEL_dq_3_ttfp_sel(data)                                        (0x00000E00&((data)<<9))
#define DC_PHY_DQ_TTF_SEL_dq_3_ttfp_sel_src(data)                                    ((0x00000E00&(data))>>9)
#define DC_PHY_DQ_TTF_SEL_get_dq_3_ttfp_sel(data)                                    ((0x00000E00&(data))>>9)
#define DC_PHY_DQ_TTF_SEL_dq_2_ttfp_sel_shift                                        (6)
#define DC_PHY_DQ_TTF_SEL_dq_2_ttfp_sel_mask                                         (0x000001C0)
#define DC_PHY_DQ_TTF_SEL_dq_2_ttfp_sel(data)                                        (0x000001C0&((data)<<6))
#define DC_PHY_DQ_TTF_SEL_dq_2_ttfp_sel_src(data)                                    ((0x000001C0&(data))>>6)
#define DC_PHY_DQ_TTF_SEL_get_dq_2_ttfp_sel(data)                                    ((0x000001C0&(data))>>6)
#define DC_PHY_DQ_TTF_SEL_dq_1_ttfp_sel_shift                                        (3)
#define DC_PHY_DQ_TTF_SEL_dq_1_ttfp_sel_mask                                         (0x00000038)
#define DC_PHY_DQ_TTF_SEL_dq_1_ttfp_sel(data)                                        (0x00000038&((data)<<3))
#define DC_PHY_DQ_TTF_SEL_dq_1_ttfp_sel_src(data)                                    ((0x00000038&(data))>>3)
#define DC_PHY_DQ_TTF_SEL_get_dq_1_ttfp_sel(data)                                    ((0x00000038&(data))>>3)
#define DC_PHY_DQ_TTF_SEL_dq_0_ttfp_sel_shift                                        (0)
#define DC_PHY_DQ_TTF_SEL_dq_0_ttfp_sel_mask                                         (0x00000007)
#define DC_PHY_DQ_TTF_SEL_dq_0_ttfp_sel(data)                                        (0x00000007&((data)<<0))
#define DC_PHY_DQ_TTF_SEL_dq_0_ttfp_sel_src(data)                                    ((0x00000007&(data))>>0)
#define DC_PHY_DQ_TTF_SEL_get_dq_0_ttfp_sel(data)                                    ((0x00000007&(data))>>0)


#define DC_PHY_DQ_OCD_SEL                                                            0x18008a48
#define DC_PHY_DQ_OCD_SEL_reg_addr                                                   "0xB8008A48"
#define DC_PHY_DQ_OCD_SEL_reg                                                        0xB8008A48
#define set_DC_PHY_DQ_OCD_SEL_reg(data)   (*((volatile unsigned int*) DC_PHY_DQ_OCD_SEL_reg)=data)
#define get_DC_PHY_DQ_OCD_SEL_reg   (*((volatile unsigned int*) DC_PHY_DQ_OCD_SEL_reg))
#define DC_PHY_DQ_OCD_SEL_inst_adr                                                   "0x0092"
#define DC_PHY_DQ_OCD_SEL_inst                                                       0x0092
#define DC_PHY_DQ_OCD_SEL_dq_3_ocdn_sel_shift                                        (21)
#define DC_PHY_DQ_OCD_SEL_dq_3_ocdn_sel_mask                                         (0x00E00000)
#define DC_PHY_DQ_OCD_SEL_dq_3_ocdn_sel(data)                                        (0x00E00000&((data)<<21))
#define DC_PHY_DQ_OCD_SEL_dq_3_ocdn_sel_src(data)                                    ((0x00E00000&(data))>>21)
#define DC_PHY_DQ_OCD_SEL_get_dq_3_ocdn_sel(data)                                    ((0x00E00000&(data))>>21)
#define DC_PHY_DQ_OCD_SEL_dq_2_ocdn_sel_shift                                        (18)
#define DC_PHY_DQ_OCD_SEL_dq_2_ocdn_sel_mask                                         (0x001C0000)
#define DC_PHY_DQ_OCD_SEL_dq_2_ocdn_sel(data)                                        (0x001C0000&((data)<<18))
#define DC_PHY_DQ_OCD_SEL_dq_2_ocdn_sel_src(data)                                    ((0x001C0000&(data))>>18)
#define DC_PHY_DQ_OCD_SEL_get_dq_2_ocdn_sel(data)                                    ((0x001C0000&(data))>>18)
#define DC_PHY_DQ_OCD_SEL_dq_1_ocdn_sel_shift                                        (15)
#define DC_PHY_DQ_OCD_SEL_dq_1_ocdn_sel_mask                                         (0x00038000)
#define DC_PHY_DQ_OCD_SEL_dq_1_ocdn_sel(data)                                        (0x00038000&((data)<<15))
#define DC_PHY_DQ_OCD_SEL_dq_1_ocdn_sel_src(data)                                    ((0x00038000&(data))>>15)
#define DC_PHY_DQ_OCD_SEL_get_dq_1_ocdn_sel(data)                                    ((0x00038000&(data))>>15)
#define DC_PHY_DQ_OCD_SEL_dq_0_ocdn_sel_shift                                        (12)
#define DC_PHY_DQ_OCD_SEL_dq_0_ocdn_sel_mask                                         (0x00007000)
#define DC_PHY_DQ_OCD_SEL_dq_0_ocdn_sel(data)                                        (0x00007000&((data)<<12))
#define DC_PHY_DQ_OCD_SEL_dq_0_ocdn_sel_src(data)                                    ((0x00007000&(data))>>12)
#define DC_PHY_DQ_OCD_SEL_get_dq_0_ocdn_sel(data)                                    ((0x00007000&(data))>>12)
#define DC_PHY_DQ_OCD_SEL_dq_3_ocdp_sel_shift                                        (9)
#define DC_PHY_DQ_OCD_SEL_dq_3_ocdp_sel_mask                                         (0x00000E00)
#define DC_PHY_DQ_OCD_SEL_dq_3_ocdp_sel(data)                                        (0x00000E00&((data)<<9))
#define DC_PHY_DQ_OCD_SEL_dq_3_ocdp_sel_src(data)                                    ((0x00000E00&(data))>>9)
#define DC_PHY_DQ_OCD_SEL_get_dq_3_ocdp_sel(data)                                    ((0x00000E00&(data))>>9)
#define DC_PHY_DQ_OCD_SEL_dq_2_ocdp_sel_shift                                        (6)
#define DC_PHY_DQ_OCD_SEL_dq_2_ocdp_sel_mask                                         (0x000001C0)
#define DC_PHY_DQ_OCD_SEL_dq_2_ocdp_sel(data)                                        (0x000001C0&((data)<<6))
#define DC_PHY_DQ_OCD_SEL_dq_2_ocdp_sel_src(data)                                    ((0x000001C0&(data))>>6)
#define DC_PHY_DQ_OCD_SEL_get_dq_2_ocdp_sel(data)                                    ((0x000001C0&(data))>>6)
#define DC_PHY_DQ_OCD_SEL_dq_1_ocdp_sel_shift                                        (3)
#define DC_PHY_DQ_OCD_SEL_dq_1_ocdp_sel_mask                                         (0x00000038)
#define DC_PHY_DQ_OCD_SEL_dq_1_ocdp_sel(data)                                        (0x00000038&((data)<<3))
#define DC_PHY_DQ_OCD_SEL_dq_1_ocdp_sel_src(data)                                    ((0x00000038&(data))>>3)
#define DC_PHY_DQ_OCD_SEL_get_dq_1_ocdp_sel(data)                                    ((0x00000038&(data))>>3)
#define DC_PHY_DQ_OCD_SEL_dq_0_ocdp_sel_shift                                        (0)
#define DC_PHY_DQ_OCD_SEL_dq_0_ocdp_sel_mask                                         (0x00000007)
#define DC_PHY_DQ_OCD_SEL_dq_0_ocdp_sel(data)                                        (0x00000007&((data)<<0))
#define DC_PHY_DQ_OCD_SEL_dq_0_ocdp_sel_src(data)                                    ((0x00000007&(data))>>0)
#define DC_PHY_DQ_OCD_SEL_get_dq_0_ocdp_sel(data)                                    ((0x00000007&(data))>>0)


#define DC_PHY_DQS_P_TTC_SEL                                                         0x18008a4c
#define DC_PHY_DQS_P_TTC_SEL_reg_addr                                                "0xB8008A4C"
#define DC_PHY_DQS_P_TTC_SEL_reg                                                     0xB8008A4C
#define set_DC_PHY_DQS_P_TTC_SEL_reg(data)   (*((volatile unsigned int*) DC_PHY_DQS_P_TTC_SEL_reg)=data)
#define get_DC_PHY_DQS_P_TTC_SEL_reg   (*((volatile unsigned int*) DC_PHY_DQS_P_TTC_SEL_reg))
#define DC_PHY_DQS_P_TTC_SEL_inst_adr                                                "0x0093"
#define DC_PHY_DQS_P_TTC_SEL_inst                                                    0x0093
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_3_ttcn_sel_shift                                  (21)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_3_ttcn_sel_mask                                   (0x00E00000)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_3_ttcn_sel(data)                                  (0x00E00000&((data)<<21))
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_3_ttcn_sel_src(data)                              ((0x00E00000&(data))>>21)
#define DC_PHY_DQS_P_TTC_SEL_get_dqs_p_3_ttcn_sel(data)                              ((0x00E00000&(data))>>21)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_2_ttcn_sel_shift                                  (18)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_2_ttcn_sel_mask                                   (0x001C0000)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_2_ttcn_sel(data)                                  (0x001C0000&((data)<<18))
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_2_ttcn_sel_src(data)                              ((0x001C0000&(data))>>18)
#define DC_PHY_DQS_P_TTC_SEL_get_dqs_p_2_ttcn_sel(data)                              ((0x001C0000&(data))>>18)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_1_ttcn_sel_shift                                  (15)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_1_ttcn_sel_mask                                   (0x00038000)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_1_ttcn_sel(data)                                  (0x00038000&((data)<<15))
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_1_ttcn_sel_src(data)                              ((0x00038000&(data))>>15)
#define DC_PHY_DQS_P_TTC_SEL_get_dqs_p_1_ttcn_sel(data)                              ((0x00038000&(data))>>15)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_0_ttcn_sel_shift                                  (12)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_0_ttcn_sel_mask                                   (0x00007000)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_0_ttcn_sel(data)                                  (0x00007000&((data)<<12))
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_0_ttcn_sel_src(data)                              ((0x00007000&(data))>>12)
#define DC_PHY_DQS_P_TTC_SEL_get_dqs_p_0_ttcn_sel(data)                              ((0x00007000&(data))>>12)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_3_ttcp_sel_shift                                  (9)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_3_ttcp_sel_mask                                   (0x00000E00)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_3_ttcp_sel(data)                                  (0x00000E00&((data)<<9))
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_3_ttcp_sel_src(data)                              ((0x00000E00&(data))>>9)
#define DC_PHY_DQS_P_TTC_SEL_get_dqs_p_3_ttcp_sel(data)                              ((0x00000E00&(data))>>9)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_2_ttcp_sel_shift                                  (6)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_2_ttcp_sel_mask                                   (0x000001C0)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_2_ttcp_sel(data)                                  (0x000001C0&((data)<<6))
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_2_ttcp_sel_src(data)                              ((0x000001C0&(data))>>6)
#define DC_PHY_DQS_P_TTC_SEL_get_dqs_p_2_ttcp_sel(data)                              ((0x000001C0&(data))>>6)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_1_ttcp_sel_shift                                  (3)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_1_ttcp_sel_mask                                   (0x00000038)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_1_ttcp_sel(data)                                  (0x00000038&((data)<<3))
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_1_ttcp_sel_src(data)                              ((0x00000038&(data))>>3)
#define DC_PHY_DQS_P_TTC_SEL_get_dqs_p_1_ttcp_sel(data)                              ((0x00000038&(data))>>3)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_0_ttcp_sel_shift                                  (0)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_0_ttcp_sel_mask                                   (0x00000007)
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_0_ttcp_sel(data)                                  (0x00000007&((data)<<0))
#define DC_PHY_DQS_P_TTC_SEL_dqs_p_0_ttcp_sel_src(data)                              ((0x00000007&(data))>>0)
#define DC_PHY_DQS_P_TTC_SEL_get_dqs_p_0_ttcp_sel(data)                              ((0x00000007&(data))>>0)


#define DC_PHY_DQS_N_TTC_SEL                                                         0x18008a50
#define DC_PHY_DQS_N_TTC_SEL_reg_addr                                                "0xB8008A50"
#define DC_PHY_DQS_N_TTC_SEL_reg                                                     0xB8008A50
#define set_DC_PHY_DQS_N_TTC_SEL_reg(data)   (*((volatile unsigned int*) DC_PHY_DQS_N_TTC_SEL_reg)=data)
#define get_DC_PHY_DQS_N_TTC_SEL_reg   (*((volatile unsigned int*) DC_PHY_DQS_N_TTC_SEL_reg))
#define DC_PHY_DQS_N_TTC_SEL_inst_adr                                                "0x0094"
#define DC_PHY_DQS_N_TTC_SEL_inst                                                    0x0094
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_3_ttcn_sel_shift                                  (21)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_3_ttcn_sel_mask                                   (0x00E00000)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_3_ttcn_sel(data)                                  (0x00E00000&((data)<<21))
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_3_ttcn_sel_src(data)                              ((0x00E00000&(data))>>21)
#define DC_PHY_DQS_N_TTC_SEL_get_dqs_n_3_ttcn_sel(data)                              ((0x00E00000&(data))>>21)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_2_ttcn_sel_shift                                  (18)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_2_ttcn_sel_mask                                   (0x001C0000)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_2_ttcn_sel(data)                                  (0x001C0000&((data)<<18))
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_2_ttcn_sel_src(data)                              ((0x001C0000&(data))>>18)
#define DC_PHY_DQS_N_TTC_SEL_get_dqs_n_2_ttcn_sel(data)                              ((0x001C0000&(data))>>18)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_1_ttcn_sel_shift                                  (15)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_1_ttcn_sel_mask                                   (0x00038000)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_1_ttcn_sel(data)                                  (0x00038000&((data)<<15))
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_1_ttcn_sel_src(data)                              ((0x00038000&(data))>>15)
#define DC_PHY_DQS_N_TTC_SEL_get_dqs_n_1_ttcn_sel(data)                              ((0x00038000&(data))>>15)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_0_ttcn_sel_shift                                  (12)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_0_ttcn_sel_mask                                   (0x00007000)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_0_ttcn_sel(data)                                  (0x00007000&((data)<<12))
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_0_ttcn_sel_src(data)                              ((0x00007000&(data))>>12)
#define DC_PHY_DQS_N_TTC_SEL_get_dqs_n_0_ttcn_sel(data)                              ((0x00007000&(data))>>12)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_3_ttcp_sel_shift                                  (9)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_3_ttcp_sel_mask                                   (0x00000E00)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_3_ttcp_sel(data)                                  (0x00000E00&((data)<<9))
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_3_ttcp_sel_src(data)                              ((0x00000E00&(data))>>9)
#define DC_PHY_DQS_N_TTC_SEL_get_dqs_n_3_ttcp_sel(data)                              ((0x00000E00&(data))>>9)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_2_ttcp_sel_shift                                  (6)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_2_ttcp_sel_mask                                   (0x000001C0)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_2_ttcp_sel(data)                                  (0x000001C0&((data)<<6))
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_2_ttcp_sel_src(data)                              ((0x000001C0&(data))>>6)
#define DC_PHY_DQS_N_TTC_SEL_get_dqs_n_2_ttcp_sel(data)                              ((0x000001C0&(data))>>6)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_1_ttcp_sel_shift                                  (3)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_1_ttcp_sel_mask                                   (0x00000038)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_1_ttcp_sel(data)                                  (0x00000038&((data)<<3))
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_1_ttcp_sel_src(data)                              ((0x00000038&(data))>>3)
#define DC_PHY_DQS_N_TTC_SEL_get_dqs_n_1_ttcp_sel(data)                              ((0x00000038&(data))>>3)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_0_ttcp_sel_shift                                  (0)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_0_ttcp_sel_mask                                   (0x00000007)
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_0_ttcp_sel(data)                                  (0x00000007&((data)<<0))
#define DC_PHY_DQS_N_TTC_SEL_dqs_n_0_ttcp_sel_src(data)                              ((0x00000007&(data))>>0)
#define DC_PHY_DQS_N_TTC_SEL_get_dqs_n_0_ttcp_sel(data)                              ((0x00000007&(data))>>0)


#define DC_PHY_DQS_P_TTF_SEL                                                         0x18008a54
#define DC_PHY_DQS_P_TTF_SEL_reg_addr                                                "0xB8008A54"
#define DC_PHY_DQS_P_TTF_SEL_reg                                                     0xB8008A54
#define set_DC_PHY_DQS_P_TTF_SEL_reg(data)   (*((volatile unsigned int*) DC_PHY_DQS_P_TTF_SEL_reg)=data)
#define get_DC_PHY_DQS_P_TTF_SEL_reg   (*((volatile unsigned int*) DC_PHY_DQS_P_TTF_SEL_reg))
#define DC_PHY_DQS_P_TTF_SEL_inst_adr                                                "0x0095"
#define DC_PHY_DQS_P_TTF_SEL_inst                                                    0x0095
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_3_ttfn_sel_shift                                  (21)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_3_ttfn_sel_mask                                   (0x00E00000)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_3_ttfn_sel(data)                                  (0x00E00000&((data)<<21))
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_3_ttfn_sel_src(data)                              ((0x00E00000&(data))>>21)
#define DC_PHY_DQS_P_TTF_SEL_get_dqs_p_3_ttfn_sel(data)                              ((0x00E00000&(data))>>21)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_2_ttfn_sel_shift                                  (18)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_2_ttfn_sel_mask                                   (0x001C0000)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_2_ttfn_sel(data)                                  (0x001C0000&((data)<<18))
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_2_ttfn_sel_src(data)                              ((0x001C0000&(data))>>18)
#define DC_PHY_DQS_P_TTF_SEL_get_dqs_p_2_ttfn_sel(data)                              ((0x001C0000&(data))>>18)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_1_ttfn_sel_shift                                  (15)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_1_ttfn_sel_mask                                   (0x00038000)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_1_ttfn_sel(data)                                  (0x00038000&((data)<<15))
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_1_ttfn_sel_src(data)                              ((0x00038000&(data))>>15)
#define DC_PHY_DQS_P_TTF_SEL_get_dqs_p_1_ttfn_sel(data)                              ((0x00038000&(data))>>15)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_0_ttfn_sel_shift                                  (12)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_0_ttfn_sel_mask                                   (0x00007000)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_0_ttfn_sel(data)                                  (0x00007000&((data)<<12))
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_0_ttfn_sel_src(data)                              ((0x00007000&(data))>>12)
#define DC_PHY_DQS_P_TTF_SEL_get_dqs_p_0_ttfn_sel(data)                              ((0x00007000&(data))>>12)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_3_ttfp_sel_shift                                  (9)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_3_ttfp_sel_mask                                   (0x00000E00)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_3_ttfp_sel(data)                                  (0x00000E00&((data)<<9))
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_3_ttfp_sel_src(data)                              ((0x00000E00&(data))>>9)
#define DC_PHY_DQS_P_TTF_SEL_get_dqs_p_3_ttfp_sel(data)                              ((0x00000E00&(data))>>9)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_2_ttfp_sel_shift                                  (6)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_2_ttfp_sel_mask                                   (0x000001C0)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_2_ttfp_sel(data)                                  (0x000001C0&((data)<<6))
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_2_ttfp_sel_src(data)                              ((0x000001C0&(data))>>6)
#define DC_PHY_DQS_P_TTF_SEL_get_dqs_p_2_ttfp_sel(data)                              ((0x000001C0&(data))>>6)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_1_ttfp_sel_shift                                  (3)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_1_ttfp_sel_mask                                   (0x00000038)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_1_ttfp_sel(data)                                  (0x00000038&((data)<<3))
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_1_ttfp_sel_src(data)                              ((0x00000038&(data))>>3)
#define DC_PHY_DQS_P_TTF_SEL_get_dqs_p_1_ttfp_sel(data)                              ((0x00000038&(data))>>3)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_0_ttfp_sel_shift                                  (0)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_0_ttfp_sel_mask                                   (0x00000007)
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_0_ttfp_sel(data)                                  (0x00000007&((data)<<0))
#define DC_PHY_DQS_P_TTF_SEL_dqs_p_0_ttfp_sel_src(data)                              ((0x00000007&(data))>>0)
#define DC_PHY_DQS_P_TTF_SEL_get_dqs_p_0_ttfp_sel(data)                              ((0x00000007&(data))>>0)


#define DC_PHY_DQS_N_TTF_SEL                                                         0x18008a58
#define DC_PHY_DQS_N_TTF_SEL_reg_addr                                                "0xB8008A58"
#define DC_PHY_DQS_N_TTF_SEL_reg                                                     0xB8008A58
#define set_DC_PHY_DQS_N_TTF_SEL_reg(data)   (*((volatile unsigned int*) DC_PHY_DQS_N_TTF_SEL_reg)=data)
#define get_DC_PHY_DQS_N_TTF_SEL_reg   (*((volatile unsigned int*) DC_PHY_DQS_N_TTF_SEL_reg))
#define DC_PHY_DQS_N_TTF_SEL_inst_adr                                                "0x0096"
#define DC_PHY_DQS_N_TTF_SEL_inst                                                    0x0096
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_3_ttfn_sel_shift                                  (21)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_3_ttfn_sel_mask                                   (0x00E00000)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_3_ttfn_sel(data)                                  (0x00E00000&((data)<<21))
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_3_ttfn_sel_src(data)                              ((0x00E00000&(data))>>21)
#define DC_PHY_DQS_N_TTF_SEL_get_dqs_n_3_ttfn_sel(data)                              ((0x00E00000&(data))>>21)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_2_ttfn_sel_shift                                  (18)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_2_ttfn_sel_mask                                   (0x001C0000)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_2_ttfn_sel(data)                                  (0x001C0000&((data)<<18))
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_2_ttfn_sel_src(data)                              ((0x001C0000&(data))>>18)
#define DC_PHY_DQS_N_TTF_SEL_get_dqs_n_2_ttfn_sel(data)                              ((0x001C0000&(data))>>18)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_1_ttfn_sel_shift                                  (15)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_1_ttfn_sel_mask                                   (0x00038000)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_1_ttfn_sel(data)                                  (0x00038000&((data)<<15))
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_1_ttfn_sel_src(data)                              ((0x00038000&(data))>>15)
#define DC_PHY_DQS_N_TTF_SEL_get_dqs_n_1_ttfn_sel(data)                              ((0x00038000&(data))>>15)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_0_ttfn_sel_shift                                  (12)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_0_ttfn_sel_mask                                   (0x00007000)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_0_ttfn_sel(data)                                  (0x00007000&((data)<<12))
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_0_ttfn_sel_src(data)                              ((0x00007000&(data))>>12)
#define DC_PHY_DQS_N_TTF_SEL_get_dqs_n_0_ttfn_sel(data)                              ((0x00007000&(data))>>12)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_3_ttfp_sel_shift                                  (9)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_3_ttfp_sel_mask                                   (0x00000E00)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_3_ttfp_sel(data)                                  (0x00000E00&((data)<<9))
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_3_ttfp_sel_src(data)                              ((0x00000E00&(data))>>9)
#define DC_PHY_DQS_N_TTF_SEL_get_dqs_n_3_ttfp_sel(data)                              ((0x00000E00&(data))>>9)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_2_ttfp_sel_shift                                  (6)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_2_ttfp_sel_mask                                   (0x000001C0)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_2_ttfp_sel(data)                                  (0x000001C0&((data)<<6))
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_2_ttfp_sel_src(data)                              ((0x000001C0&(data))>>6)
#define DC_PHY_DQS_N_TTF_SEL_get_dqs_n_2_ttfp_sel(data)                              ((0x000001C0&(data))>>6)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_1_ttfp_sel_shift                                  (3)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_1_ttfp_sel_mask                                   (0x00000038)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_1_ttfp_sel(data)                                  (0x00000038&((data)<<3))
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_1_ttfp_sel_src(data)                              ((0x00000038&(data))>>3)
#define DC_PHY_DQS_N_TTF_SEL_get_dqs_n_1_ttfp_sel(data)                              ((0x00000038&(data))>>3)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_0_ttfp_sel_shift                                  (0)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_0_ttfp_sel_mask                                   (0x00000007)
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_0_ttfp_sel(data)                                  (0x00000007&((data)<<0))
#define DC_PHY_DQS_N_TTF_SEL_dqs_n_0_ttfp_sel_src(data)                              ((0x00000007&(data))>>0)
#define DC_PHY_DQS_N_TTF_SEL_get_dqs_n_0_ttfp_sel(data)                              ((0x00000007&(data))>>0)


#define DC_PHY_DQS_P_OCD_SEL                                                         0x18008a5c
#define DC_PHY_DQS_P_OCD_SEL_reg_addr                                                "0xB8008A5C"
#define DC_PHY_DQS_P_OCD_SEL_reg                                                     0xB8008A5C
#define set_DC_PHY_DQS_P_OCD_SEL_reg(data)   (*((volatile unsigned int*) DC_PHY_DQS_P_OCD_SEL_reg)=data)
#define get_DC_PHY_DQS_P_OCD_SEL_reg   (*((volatile unsigned int*) DC_PHY_DQS_P_OCD_SEL_reg))
#define DC_PHY_DQS_P_OCD_SEL_inst_adr                                                "0x0097"
#define DC_PHY_DQS_P_OCD_SEL_inst                                                    0x0097
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_3_ocdn_sel_shift                                  (21)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_3_ocdn_sel_mask                                   (0x00E00000)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_3_ocdn_sel(data)                                  (0x00E00000&((data)<<21))
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_3_ocdn_sel_src(data)                              ((0x00E00000&(data))>>21)
#define DC_PHY_DQS_P_OCD_SEL_get_dqs_p_3_ocdn_sel(data)                              ((0x00E00000&(data))>>21)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_2_ocdn_sel_shift                                  (18)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_2_ocdn_sel_mask                                   (0x001C0000)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_2_ocdn_sel(data)                                  (0x001C0000&((data)<<18))
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_2_ocdn_sel_src(data)                              ((0x001C0000&(data))>>18)
#define DC_PHY_DQS_P_OCD_SEL_get_dqs_p_2_ocdn_sel(data)                              ((0x001C0000&(data))>>18)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_1_ocdn_sel_shift                                  (15)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_1_ocdn_sel_mask                                   (0x00038000)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_1_ocdn_sel(data)                                  (0x00038000&((data)<<15))
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_1_ocdn_sel_src(data)                              ((0x00038000&(data))>>15)
#define DC_PHY_DQS_P_OCD_SEL_get_dqs_p_1_ocdn_sel(data)                              ((0x00038000&(data))>>15)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_0_ocdn_sel_shift                                  (12)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_0_ocdn_sel_mask                                   (0x00007000)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_0_ocdn_sel(data)                                  (0x00007000&((data)<<12))
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_0_ocdn_sel_src(data)                              ((0x00007000&(data))>>12)
#define DC_PHY_DQS_P_OCD_SEL_get_dqs_p_0_ocdn_sel(data)                              ((0x00007000&(data))>>12)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_3_ocdp_sel_shift                                  (9)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_3_ocdp_sel_mask                                   (0x00000E00)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_3_ocdp_sel(data)                                  (0x00000E00&((data)<<9))
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_3_ocdp_sel_src(data)                              ((0x00000E00&(data))>>9)
#define DC_PHY_DQS_P_OCD_SEL_get_dqs_p_3_ocdp_sel(data)                              ((0x00000E00&(data))>>9)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_2_ocdp_sel_shift                                  (6)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_2_ocdp_sel_mask                                   (0x000001C0)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_2_ocdp_sel(data)                                  (0x000001C0&((data)<<6))
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_2_ocdp_sel_src(data)                              ((0x000001C0&(data))>>6)
#define DC_PHY_DQS_P_OCD_SEL_get_dqs_p_2_ocdp_sel(data)                              ((0x000001C0&(data))>>6)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_1_ocdp_sel_shift                                  (3)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_1_ocdp_sel_mask                                   (0x00000038)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_1_ocdp_sel(data)                                  (0x00000038&((data)<<3))
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_1_ocdp_sel_src(data)                              ((0x00000038&(data))>>3)
#define DC_PHY_DQS_P_OCD_SEL_get_dqs_p_1_ocdp_sel(data)                              ((0x00000038&(data))>>3)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_0_ocdp_sel_shift                                  (0)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_0_ocdp_sel_mask                                   (0x00000007)
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_0_ocdp_sel(data)                                  (0x00000007&((data)<<0))
#define DC_PHY_DQS_P_OCD_SEL_dqs_p_0_ocdp_sel_src(data)                              ((0x00000007&(data))>>0)
#define DC_PHY_DQS_P_OCD_SEL_get_dqs_p_0_ocdp_sel(data)                              ((0x00000007&(data))>>0)


#define DC_PHY_DQS_N_OCD_SEL                                                         0x18008a60
#define DC_PHY_DQS_N_OCD_SEL_reg_addr                                                "0xB8008A60"
#define DC_PHY_DQS_N_OCD_SEL_reg                                                     0xB8008A60
#define set_DC_PHY_DQS_N_OCD_SEL_reg(data)   (*((volatile unsigned int*) DC_PHY_DQS_N_OCD_SEL_reg)=data)
#define get_DC_PHY_DQS_N_OCD_SEL_reg   (*((volatile unsigned int*) DC_PHY_DQS_N_OCD_SEL_reg))
#define DC_PHY_DQS_N_OCD_SEL_inst_adr                                                "0x0098"
#define DC_PHY_DQS_N_OCD_SEL_inst                                                    0x0098
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_3_ocdn_sel_shift                                  (21)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_3_ocdn_sel_mask                                   (0x00E00000)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_3_ocdn_sel(data)                                  (0x00E00000&((data)<<21))
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_3_ocdn_sel_src(data)                              ((0x00E00000&(data))>>21)
#define DC_PHY_DQS_N_OCD_SEL_get_dqs_n_3_ocdn_sel(data)                              ((0x00E00000&(data))>>21)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_2_ocdn_sel_shift                                  (18)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_2_ocdn_sel_mask                                   (0x001C0000)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_2_ocdn_sel(data)                                  (0x001C0000&((data)<<18))
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_2_ocdn_sel_src(data)                              ((0x001C0000&(data))>>18)
#define DC_PHY_DQS_N_OCD_SEL_get_dqs_n_2_ocdn_sel(data)                              ((0x001C0000&(data))>>18)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_1_ocdn_sel_shift                                  (15)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_1_ocdn_sel_mask                                   (0x00038000)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_1_ocdn_sel(data)                                  (0x00038000&((data)<<15))
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_1_ocdn_sel_src(data)                              ((0x00038000&(data))>>15)
#define DC_PHY_DQS_N_OCD_SEL_get_dqs_n_1_ocdn_sel(data)                              ((0x00038000&(data))>>15)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_0_ocdn_sel_shift                                  (12)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_0_ocdn_sel_mask                                   (0x00007000)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_0_ocdn_sel(data)                                  (0x00007000&((data)<<12))
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_0_ocdn_sel_src(data)                              ((0x00007000&(data))>>12)
#define DC_PHY_DQS_N_OCD_SEL_get_dqs_n_0_ocdn_sel(data)                              ((0x00007000&(data))>>12)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_3_ocdp_sel_shift                                  (9)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_3_ocdp_sel_mask                                   (0x00000E00)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_3_ocdp_sel(data)                                  (0x00000E00&((data)<<9))
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_3_ocdp_sel_src(data)                              ((0x00000E00&(data))>>9)
#define DC_PHY_DQS_N_OCD_SEL_get_dqs_n_3_ocdp_sel(data)                              ((0x00000E00&(data))>>9)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_2_ocdp_sel_shift                                  (6)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_2_ocdp_sel_mask                                   (0x000001C0)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_2_ocdp_sel(data)                                  (0x000001C0&((data)<<6))
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_2_ocdp_sel_src(data)                              ((0x000001C0&(data))>>6)
#define DC_PHY_DQS_N_OCD_SEL_get_dqs_n_2_ocdp_sel(data)                              ((0x000001C0&(data))>>6)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_1_ocdp_sel_shift                                  (3)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_1_ocdp_sel_mask                                   (0x00000038)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_1_ocdp_sel(data)                                  (0x00000038&((data)<<3))
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_1_ocdp_sel_src(data)                              ((0x00000038&(data))>>3)
#define DC_PHY_DQS_N_OCD_SEL_get_dqs_n_1_ocdp_sel(data)                              ((0x00000038&(data))>>3)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_0_ocdp_sel_shift                                  (0)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_0_ocdp_sel_mask                                   (0x00000007)
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_0_ocdp_sel(data)                                  (0x00000007&((data)<<0))
#define DC_PHY_DQS_N_OCD_SEL_dqs_n_0_ocdp_sel_src(data)                              ((0x00000007&(data))>>0)
#define DC_PHY_DQS_N_OCD_SEL_get_dqs_n_0_ocdp_sel(data)                              ((0x00000007&(data))>>0)


#define DC_PHY_ADR_OCD_SEL                                                           0x18008a64
#define DC_PHY_ADR_OCD_SEL_reg_addr                                                  "0xB8008A64"
#define DC_PHY_ADR_OCD_SEL_reg                                                       0xB8008A64
#define set_DC_PHY_ADR_OCD_SEL_reg(data)   (*((volatile unsigned int*) DC_PHY_ADR_OCD_SEL_reg)=data)
#define get_DC_PHY_ADR_OCD_SEL_reg   (*((volatile unsigned int*) DC_PHY_ADR_OCD_SEL_reg))
#define DC_PHY_ADR_OCD_SEL_inst_adr                                                  "0x0099"
#define DC_PHY_ADR_OCD_SEL_inst                                                      0x0099
#define DC_PHY_ADR_OCD_SEL_adr_1_ocdn_sel_shift                                      (21)
#define DC_PHY_ADR_OCD_SEL_adr_1_ocdn_sel_mask                                       (0x00E00000)
#define DC_PHY_ADR_OCD_SEL_adr_1_ocdn_sel(data)                                      (0x00E00000&((data)<<21))
#define DC_PHY_ADR_OCD_SEL_adr_1_ocdn_sel_src(data)                                  ((0x00E00000&(data))>>21)
#define DC_PHY_ADR_OCD_SEL_get_adr_1_ocdn_sel(data)                                  ((0x00E00000&(data))>>21)
#define DC_PHY_ADR_OCD_SEL_adr_0_ocdn_sel_shift                                      (18)
#define DC_PHY_ADR_OCD_SEL_adr_0_ocdn_sel_mask                                       (0x001C0000)
#define DC_PHY_ADR_OCD_SEL_adr_0_ocdn_sel(data)                                      (0x001C0000&((data)<<18))
#define DC_PHY_ADR_OCD_SEL_adr_0_ocdn_sel_src(data)                                  ((0x001C0000&(data))>>18)
#define DC_PHY_ADR_OCD_SEL_get_adr_0_ocdn_sel(data)                                  ((0x001C0000&(data))>>18)
#define DC_PHY_ADR_OCD_SEL_cmd_1_ocdn_sel_shift                                      (15)
#define DC_PHY_ADR_OCD_SEL_cmd_1_ocdn_sel_mask                                       (0x00038000)
#define DC_PHY_ADR_OCD_SEL_cmd_1_ocdn_sel(data)                                      (0x00038000&((data)<<15))
#define DC_PHY_ADR_OCD_SEL_cmd_1_ocdn_sel_src(data)                                  ((0x00038000&(data))>>15)
#define DC_PHY_ADR_OCD_SEL_get_cmd_1_ocdn_sel(data)                                  ((0x00038000&(data))>>15)
#define DC_PHY_ADR_OCD_SEL_cmd_0_ocdn_sel_shift                                      (12)
#define DC_PHY_ADR_OCD_SEL_cmd_0_ocdn_sel_mask                                       (0x00007000)
#define DC_PHY_ADR_OCD_SEL_cmd_0_ocdn_sel(data)                                      (0x00007000&((data)<<12))
#define DC_PHY_ADR_OCD_SEL_cmd_0_ocdn_sel_src(data)                                  ((0x00007000&(data))>>12)
#define DC_PHY_ADR_OCD_SEL_get_cmd_0_ocdn_sel(data)                                  ((0x00007000&(data))>>12)
#define DC_PHY_ADR_OCD_SEL_adr_1_ocdp_sel_shift                                      (9)
#define DC_PHY_ADR_OCD_SEL_adr_1_ocdp_sel_mask                                       (0x00000E00)
#define DC_PHY_ADR_OCD_SEL_adr_1_ocdp_sel(data)                                      (0x00000E00&((data)<<9))
#define DC_PHY_ADR_OCD_SEL_adr_1_ocdp_sel_src(data)                                  ((0x00000E00&(data))>>9)
#define DC_PHY_ADR_OCD_SEL_get_adr_1_ocdp_sel(data)                                  ((0x00000E00&(data))>>9)
#define DC_PHY_ADR_OCD_SEL_adr_0_ocdp_sel_shift                                      (6)
#define DC_PHY_ADR_OCD_SEL_adr_0_ocdp_sel_mask                                       (0x000001C0)
#define DC_PHY_ADR_OCD_SEL_adr_0_ocdp_sel(data)                                      (0x000001C0&((data)<<6))
#define DC_PHY_ADR_OCD_SEL_adr_0_ocdp_sel_src(data)                                  ((0x000001C0&(data))>>6)
#define DC_PHY_ADR_OCD_SEL_get_adr_0_ocdp_sel(data)                                  ((0x000001C0&(data))>>6)
#define DC_PHY_ADR_OCD_SEL_cmd_1_ocdp_sel_shift                                      (3)
#define DC_PHY_ADR_OCD_SEL_cmd_1_ocdp_sel_mask                                       (0x00000038)
#define DC_PHY_ADR_OCD_SEL_cmd_1_ocdp_sel(data)                                      (0x00000038&((data)<<3))
#define DC_PHY_ADR_OCD_SEL_cmd_1_ocdp_sel_src(data)                                  ((0x00000038&(data))>>3)
#define DC_PHY_ADR_OCD_SEL_get_cmd_1_ocdp_sel(data)                                  ((0x00000038&(data))>>3)
#define DC_PHY_ADR_OCD_SEL_cmd_0_ocdp_sel_shift                                      (0)
#define DC_PHY_ADR_OCD_SEL_cmd_0_ocdp_sel_mask                                       (0x00000007)
#define DC_PHY_ADR_OCD_SEL_cmd_0_ocdp_sel(data)                                      (0x00000007&((data)<<0))
#define DC_PHY_ADR_OCD_SEL_cmd_0_ocdp_sel_src(data)                                  ((0x00000007&(data))>>0)
#define DC_PHY_ADR_OCD_SEL_get_cmd_0_ocdp_sel(data)                                  ((0x00000007&(data))>>0)


#define DC_PHY_CK_OCD_SEL                                                            0x18008a68
#define DC_PHY_CK_OCD_SEL_reg_addr                                                   "0xB8008A68"
#define DC_PHY_CK_OCD_SEL_reg                                                        0xB8008A68
#define set_DC_PHY_CK_OCD_SEL_reg(data)   (*((volatile unsigned int*) DC_PHY_CK_OCD_SEL_reg)=data)
#define get_DC_PHY_CK_OCD_SEL_reg   (*((volatile unsigned int*) DC_PHY_CK_OCD_SEL_reg))
#define DC_PHY_CK_OCD_SEL_inst_adr                                                   "0x009A"
#define DC_PHY_CK_OCD_SEL_inst                                                       0x009A
#define DC_PHY_CK_OCD_SEL_ck_n_1_ocdn_sel_shift                                      (21)
#define DC_PHY_CK_OCD_SEL_ck_n_1_ocdn_sel_mask                                       (0x00E00000)
#define DC_PHY_CK_OCD_SEL_ck_n_1_ocdn_sel(data)                                      (0x00E00000&((data)<<21))
#define DC_PHY_CK_OCD_SEL_ck_n_1_ocdn_sel_src(data)                                  ((0x00E00000&(data))>>21)
#define DC_PHY_CK_OCD_SEL_get_ck_n_1_ocdn_sel(data)                                  ((0x00E00000&(data))>>21)
#define DC_PHY_CK_OCD_SEL_ck_n_0_ocdn_sel_shift                                      (18)
#define DC_PHY_CK_OCD_SEL_ck_n_0_ocdn_sel_mask                                       (0x001C0000)
#define DC_PHY_CK_OCD_SEL_ck_n_0_ocdn_sel(data)                                      (0x001C0000&((data)<<18))
#define DC_PHY_CK_OCD_SEL_ck_n_0_ocdn_sel_src(data)                                  ((0x001C0000&(data))>>18)
#define DC_PHY_CK_OCD_SEL_get_ck_n_0_ocdn_sel(data)                                  ((0x001C0000&(data))>>18)
#define DC_PHY_CK_OCD_SEL_ck_n_1_ocdp_sel_shift                                      (15)
#define DC_PHY_CK_OCD_SEL_ck_n_1_ocdp_sel_mask                                       (0x00038000)
#define DC_PHY_CK_OCD_SEL_ck_n_1_ocdp_sel(data)                                      (0x00038000&((data)<<15))
#define DC_PHY_CK_OCD_SEL_ck_n_1_ocdp_sel_src(data)                                  ((0x00038000&(data))>>15)
#define DC_PHY_CK_OCD_SEL_get_ck_n_1_ocdp_sel(data)                                  ((0x00038000&(data))>>15)
#define DC_PHY_CK_OCD_SEL_ck_n_0_ocdp_sel_shift                                      (12)
#define DC_PHY_CK_OCD_SEL_ck_n_0_ocdp_sel_mask                                       (0x00007000)
#define DC_PHY_CK_OCD_SEL_ck_n_0_ocdp_sel(data)                                      (0x00007000&((data)<<12))
#define DC_PHY_CK_OCD_SEL_ck_n_0_ocdp_sel_src(data)                                  ((0x00007000&(data))>>12)
#define DC_PHY_CK_OCD_SEL_get_ck_n_0_ocdp_sel(data)                                  ((0x00007000&(data))>>12)
#define DC_PHY_CK_OCD_SEL_ck_p_1_ocdn_sel_shift                                      (9)
#define DC_PHY_CK_OCD_SEL_ck_p_1_ocdn_sel_mask                                       (0x00000E00)
#define DC_PHY_CK_OCD_SEL_ck_p_1_ocdn_sel(data)                                      (0x00000E00&((data)<<9))
#define DC_PHY_CK_OCD_SEL_ck_p_1_ocdn_sel_src(data)                                  ((0x00000E00&(data))>>9)
#define DC_PHY_CK_OCD_SEL_get_ck_p_1_ocdn_sel(data)                                  ((0x00000E00&(data))>>9)
#define DC_PHY_CK_OCD_SEL_ck_p_0_ocdn_sel_shift                                      (6)
#define DC_PHY_CK_OCD_SEL_ck_p_0_ocdn_sel_mask                                       (0x000001C0)
#define DC_PHY_CK_OCD_SEL_ck_p_0_ocdn_sel(data)                                      (0x000001C0&((data)<<6))
#define DC_PHY_CK_OCD_SEL_ck_p_0_ocdn_sel_src(data)                                  ((0x000001C0&(data))>>6)
#define DC_PHY_CK_OCD_SEL_get_ck_p_0_ocdn_sel(data)                                  ((0x000001C0&(data))>>6)
#define DC_PHY_CK_OCD_SEL_ck_p_1_ocdp_sel_shift                                      (3)
#define DC_PHY_CK_OCD_SEL_ck_p_1_ocdp_sel_mask                                       (0x00000038)
#define DC_PHY_CK_OCD_SEL_ck_p_1_ocdp_sel(data)                                      (0x00000038&((data)<<3))
#define DC_PHY_CK_OCD_SEL_ck_p_1_ocdp_sel_src(data)                                  ((0x00000038&(data))>>3)
#define DC_PHY_CK_OCD_SEL_get_ck_p_1_ocdp_sel(data)                                  ((0x00000038&(data))>>3)
#define DC_PHY_CK_OCD_SEL_ck_p_0_ocdp_sel_shift                                      (0)
#define DC_PHY_CK_OCD_SEL_ck_p_0_ocdp_sel_mask                                       (0x00000007)
#define DC_PHY_CK_OCD_SEL_ck_p_0_ocdp_sel(data)                                      (0x00000007&((data)<<0))
#define DC_PHY_CK_OCD_SEL_ck_p_0_ocdp_sel_src(data)                                  ((0x00000007&(data))>>0)
#define DC_PHY_CK_OCD_SEL_get_ck_p_0_ocdp_sel(data)                                  ((0x00000007&(data))>>0)


#define DC_PHY_PAD_BUS_0                                                             0x18008b00
#define DC_PHY_PAD_BUS_0_reg_addr                                                    "0xB8008B00"
#define DC_PHY_PAD_BUS_0_reg                                                         0xB8008B00
#define set_DC_PHY_PAD_BUS_0_reg(data)   (*((volatile unsigned int*) DC_PHY_PAD_BUS_0_reg)=data)
#define get_DC_PHY_PAD_BUS_0_reg   (*((volatile unsigned int*) DC_PHY_PAD_BUS_0_reg))
#define DC_PHY_PAD_BUS_0_inst_adr                                                    "0x00C0"
#define DC_PHY_PAD_BUS_0_inst                                                        0x00C0
#define DC_PHY_PAD_BUS_0_pad_bus_0_shift                                             (0)
#define DC_PHY_PAD_BUS_0_pad_bus_0_mask                                              (0xFFFFFFFF)
#define DC_PHY_PAD_BUS_0_pad_bus_0(data)                                             (0xFFFFFFFF&((data)<<0))
#define DC_PHY_PAD_BUS_0_pad_bus_0_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_PAD_BUS_0_get_pad_bus_0(data)                                         ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_PAD_BUS_1                                                             0x18008b04
#define DC_PHY_PAD_BUS_1_reg_addr                                                    "0xB8008B04"
#define DC_PHY_PAD_BUS_1_reg                                                         0xB8008B04
#define set_DC_PHY_PAD_BUS_1_reg(data)   (*((volatile unsigned int*) DC_PHY_PAD_BUS_1_reg)=data)
#define get_DC_PHY_PAD_BUS_1_reg   (*((volatile unsigned int*) DC_PHY_PAD_BUS_1_reg))
#define DC_PHY_PAD_BUS_1_inst_adr                                                    "0x00C1"
#define DC_PHY_PAD_BUS_1_inst                                                        0x00C1
#define DC_PHY_PAD_BUS_1_pad_bus_1_shift                                             (0)
#define DC_PHY_PAD_BUS_1_pad_bus_1_mask                                              (0x0000000F)
#define DC_PHY_PAD_BUS_1_pad_bus_1(data)                                             (0x0000000F&((data)<<0))
#define DC_PHY_PAD_BUS_1_pad_bus_1_src(data)                                         ((0x0000000F&(data))>>0)
#define DC_PHY_PAD_BUS_1_get_pad_bus_1(data)                                         ((0x0000000F&(data))>>0)


#define DC_PHY_ANA_DLL_1                                                             0x18008b20
#define DC_PHY_ANA_DLL_1_reg_addr                                                    "0xB8008B20"
#define DC_PHY_ANA_DLL_1_reg                                                         0xB8008B20
#define set_DC_PHY_ANA_DLL_1_reg(data)   (*((volatile unsigned int*) DC_PHY_ANA_DLL_1_reg)=data)
#define get_DC_PHY_ANA_DLL_1_reg   (*((volatile unsigned int*) DC_PHY_ANA_DLL_1_reg))
#define DC_PHY_ANA_DLL_1_inst_adr                                                    "0x00C8"
#define DC_PHY_ANA_DLL_1_inst                                                        0x00C8
#define DC_PHY_ANA_DLL_1_dll_en_test_shift                                           (31)
#define DC_PHY_ANA_DLL_1_dll_en_test_mask                                            (0x80000000)
#define DC_PHY_ANA_DLL_1_dll_en_test(data)                                           (0x80000000&((data)<<31))
#define DC_PHY_ANA_DLL_1_dll_en_test_src(data)                                       ((0x80000000&(data))>>31)
#define DC_PHY_ANA_DLL_1_get_dll_en_test(data)                                       ((0x80000000&(data))>>31)
#define DC_PHY_ANA_DLL_1_dll_sc_shift                                                (28)
#define DC_PHY_ANA_DLL_1_dll_sc_mask                                                 (0x70000000)
#define DC_PHY_ANA_DLL_1_dll_sc(data)                                                (0x70000000&((data)<<28))
#define DC_PHY_ANA_DLL_1_dll_sc_src(data)                                            ((0x70000000&(data))>>28)
#define DC_PHY_ANA_DLL_1_get_dll_sc(data)                                            ((0x70000000&(data))>>28)
#define DC_PHY_ANA_DLL_1_dll_sel_ipump_shift                                         (24)
#define DC_PHY_ANA_DLL_1_dll_sel_ipump_mask                                          (0x0F000000)
#define DC_PHY_ANA_DLL_1_dll_sel_ipump(data)                                         (0x0F000000&((data)<<24))
#define DC_PHY_ANA_DLL_1_dll_sel_ipump_src(data)                                     ((0x0F000000&(data))>>24)
#define DC_PHY_ANA_DLL_1_get_dll_sel_ipump(data)                                     ((0x0F000000&(data))>>24)
#define DC_PHY_ANA_DLL_1_dll_pfd_div_shift                                           (18)
#define DC_PHY_ANA_DLL_1_dll_pfd_div_mask                                            (0x00FC0000)
#define DC_PHY_ANA_DLL_1_dll_pfd_div(data)                                           (0x00FC0000&((data)<<18))
#define DC_PHY_ANA_DLL_1_dll_pfd_div_src(data)                                       ((0x00FC0000&(data))>>18)
#define DC_PHY_ANA_DLL_1_get_dll_pfd_div(data)                                       ((0x00FC0000&(data))>>18)
#define DC_PHY_ANA_DLL_1_dll_pre_divn_shift                                          (16)
#define DC_PHY_ANA_DLL_1_dll_pre_divn_mask                                           (0x00030000)
#define DC_PHY_ANA_DLL_1_dll_pre_divn(data)                                          (0x00030000&((data)<<16))
#define DC_PHY_ANA_DLL_1_dll_pre_divn_src(data)                                      ((0x00030000&(data))>>16)
#define DC_PHY_ANA_DLL_1_get_dll_pre_divn(data)                                      ((0x00030000&(data))>>16)
#define DC_PHY_ANA_DLL_1_dll_en_newpump_shift                                        (15)
#define DC_PHY_ANA_DLL_1_dll_en_newpump_mask                                         (0x00008000)
#define DC_PHY_ANA_DLL_1_dll_en_newpump(data)                                        (0x00008000&((data)<<15))
#define DC_PHY_ANA_DLL_1_dll_en_newpump_src(data)                                    ((0x00008000&(data))>>15)
#define DC_PHY_ANA_DLL_1_get_dll_en_newpump(data)                                    ((0x00008000&(data))>>15)
#define DC_PHY_ANA_DLL_1_dll_bin_dl2_ph_sel_shift                                    (10)
#define DC_PHY_ANA_DLL_1_dll_bin_dl2_ph_sel_mask                                     (0x00007C00)
#define DC_PHY_ANA_DLL_1_dll_bin_dl2_ph_sel(data)                                    (0x00007C00&((data)<<10))
#define DC_PHY_ANA_DLL_1_dll_bin_dl2_ph_sel_src(data)                                ((0x00007C00&(data))>>10)
#define DC_PHY_ANA_DLL_1_get_dll_bin_dl2_ph_sel(data)                                ((0x00007C00&(data))>>10)
#define DC_PHY_ANA_DLL_1_dll_bin_dl1_ph_sel_shift                                    (5)
#define DC_PHY_ANA_DLL_1_dll_bin_dl1_ph_sel_mask                                     (0x000003E0)
#define DC_PHY_ANA_DLL_1_dll_bin_dl1_ph_sel(data)                                    (0x000003E0&((data)<<5))
#define DC_PHY_ANA_DLL_1_dll_bin_dl1_ph_sel_src(data)                                ((0x000003E0&(data))>>5)
#define DC_PHY_ANA_DLL_1_get_dll_bin_dl1_ph_sel(data)                                ((0x000003E0&(data))>>5)
#define DC_PHY_ANA_DLL_1_dll_bin_dl0_ph_sel_shift                                    (0)
#define DC_PHY_ANA_DLL_1_dll_bin_dl0_ph_sel_mask                                     (0x0000001F)
#define DC_PHY_ANA_DLL_1_dll_bin_dl0_ph_sel(data)                                    (0x0000001F&((data)<<0))
#define DC_PHY_ANA_DLL_1_dll_bin_dl0_ph_sel_src(data)                                ((0x0000001F&(data))>>0)
#define DC_PHY_ANA_DLL_1_get_dll_bin_dl0_ph_sel(data)                                ((0x0000001F&(data))>>0)


#define DC_PHY_ANA_DLL_2                                                             0x18008b24
#define DC_PHY_ANA_DLL_2_reg_addr                                                    "0xB8008B24"
#define DC_PHY_ANA_DLL_2_reg                                                         0xB8008B24
#define set_DC_PHY_ANA_DLL_2_reg(data)   (*((volatile unsigned int*) DC_PHY_ANA_DLL_2_reg)=data)
#define get_DC_PHY_ANA_DLL_2_reg   (*((volatile unsigned int*) DC_PHY_ANA_DLL_2_reg))
#define DC_PHY_ANA_DLL_2_inst_adr                                                    "0x00C9"
#define DC_PHY_ANA_DLL_2_inst                                                        0x00C9
#define DC_PHY_ANA_DLL_2_dll_en_3_shift                                              (12)
#define DC_PHY_ANA_DLL_2_dll_en_3_mask                                               (0x00001000)
#define DC_PHY_ANA_DLL_2_dll_en_3(data)                                              (0x00001000&((data)<<12))
#define DC_PHY_ANA_DLL_2_dll_en_3_src(data)                                          ((0x00001000&(data))>>12)
#define DC_PHY_ANA_DLL_2_get_dll_en_3(data)                                          ((0x00001000&(data))>>12)
#define DC_PHY_ANA_DLL_2_dll_en_2_shift                                              (11)
#define DC_PHY_ANA_DLL_2_dll_en_2_mask                                               (0x00000800)
#define DC_PHY_ANA_DLL_2_dll_en_2(data)                                              (0x00000800&((data)<<11))
#define DC_PHY_ANA_DLL_2_dll_en_2_src(data)                                          ((0x00000800&(data))>>11)
#define DC_PHY_ANA_DLL_2_get_dll_en_2(data)                                          ((0x00000800&(data))>>11)
#define DC_PHY_ANA_DLL_2_dll_en_1_shift                                              (10)
#define DC_PHY_ANA_DLL_2_dll_en_1_mask                                               (0x00000400)
#define DC_PHY_ANA_DLL_2_dll_en_1(data)                                              (0x00000400&((data)<<10))
#define DC_PHY_ANA_DLL_2_dll_en_1_src(data)                                          ((0x00000400&(data))>>10)
#define DC_PHY_ANA_DLL_2_get_dll_en_1(data)                                          ((0x00000400&(data))>>10)
#define DC_PHY_ANA_DLL_2_dll_en_0_shift                                              (9)
#define DC_PHY_ANA_DLL_2_dll_en_0_mask                                               (0x00000200)
#define DC_PHY_ANA_DLL_2_dll_en_0(data)                                              (0x00000200&((data)<<9))
#define DC_PHY_ANA_DLL_2_dll_en_0_src(data)                                          ((0x00000200&(data))>>9)
#define DC_PHY_ANA_DLL_2_get_dll_en_0(data)                                          ((0x00000200&(data))>>9)
#define DC_PHY_ANA_DLL_2_dll_dl_ph_sel_shift                                         (8)
#define DC_PHY_ANA_DLL_2_dll_dl_ph_sel_mask                                          (0x00000100)
#define DC_PHY_ANA_DLL_2_dll_dl_ph_sel(data)                                         (0x00000100&((data)<<8))
#define DC_PHY_ANA_DLL_2_dll_dl_ph_sel_src(data)                                     ((0x00000100&(data))>>8)
#define DC_PHY_ANA_DLL_2_get_dll_dl_ph_sel(data)                                     ((0x00000100&(data))>>8)
#define DC_PHY_ANA_DLL_2_dll_rdy_3_shift                                             (7)
#define DC_PHY_ANA_DLL_2_dll_rdy_3_mask                                              (0x00000080)
#define DC_PHY_ANA_DLL_2_dll_rdy_3(data)                                             (0x00000080&((data)<<7))
#define DC_PHY_ANA_DLL_2_dll_rdy_3_src(data)                                         ((0x00000080&(data))>>7)
#define DC_PHY_ANA_DLL_2_get_dll_rdy_3(data)                                         ((0x00000080&(data))>>7)
#define DC_PHY_ANA_DLL_2_dll_rdy_2_shift                                             (6)
#define DC_PHY_ANA_DLL_2_dll_rdy_2_mask                                              (0x00000040)
#define DC_PHY_ANA_DLL_2_dll_rdy_2(data)                                             (0x00000040&((data)<<6))
#define DC_PHY_ANA_DLL_2_dll_rdy_2_src(data)                                         ((0x00000040&(data))>>6)
#define DC_PHY_ANA_DLL_2_get_dll_rdy_2(data)                                         ((0x00000040&(data))>>6)
#define DC_PHY_ANA_DLL_2_dll_rdy_1_shift                                             (5)
#define DC_PHY_ANA_DLL_2_dll_rdy_1_mask                                              (0x00000020)
#define DC_PHY_ANA_DLL_2_dll_rdy_1(data)                                             (0x00000020&((data)<<5))
#define DC_PHY_ANA_DLL_2_dll_rdy_1_src(data)                                         ((0x00000020&(data))>>5)
#define DC_PHY_ANA_DLL_2_get_dll_rdy_1(data)                                         ((0x00000020&(data))>>5)
#define DC_PHY_ANA_DLL_2_dll_rdy_0_shift                                             (4)
#define DC_PHY_ANA_DLL_2_dll_rdy_0_mask                                              (0x00000010)
#define DC_PHY_ANA_DLL_2_dll_rdy_0(data)                                             (0x00000010&((data)<<4))
#define DC_PHY_ANA_DLL_2_dll_rdy_0_src(data)                                         ((0x00000010&(data))>>4)
#define DC_PHY_ANA_DLL_2_get_dll_rdy_0(data)                                         ((0x00000010&(data))>>4)
#define DC_PHY_ANA_DLL_2_dll_div_sel_shift                                           (2)
#define DC_PHY_ANA_DLL_2_dll_div_sel_mask                                            (0x0000000C)
#define DC_PHY_ANA_DLL_2_dll_div_sel(data)                                           (0x0000000C&((data)<<2))
#define DC_PHY_ANA_DLL_2_dll_div_sel_src(data)                                       ((0x0000000C&(data))>>2)
#define DC_PHY_ANA_DLL_2_get_dll_div_sel(data)                                       ((0x0000000C&(data))>>2)
#define DC_PHY_ANA_DLL_2_dll_ck_sel_shift                                            (1)
#define DC_PHY_ANA_DLL_2_dll_ck_sel_mask                                             (0x00000002)
#define DC_PHY_ANA_DLL_2_dll_ck_sel(data)                                            (0x00000002&((data)<<1))
#define DC_PHY_ANA_DLL_2_dll_ck_sel_src(data)                                        ((0x00000002&(data))>>1)
#define DC_PHY_ANA_DLL_2_get_dll_ck_sel(data)                                        ((0x00000002&(data))>>1)
#define DC_PHY_ANA_DLL_2_ana_dly_sel_shift                                           (0)
#define DC_PHY_ANA_DLL_2_ana_dly_sel_mask                                            (0x00000001)
#define DC_PHY_ANA_DLL_2_ana_dly_sel(data)                                           (0x00000001&((data)<<0))
#define DC_PHY_ANA_DLL_2_ana_dly_sel_src(data)                                       ((0x00000001&(data))>>0)
#define DC_PHY_ANA_DLL_2_get_ana_dly_sel(data)                                       ((0x00000001&(data))>>0)


#define DC_PHY_LPDDR_CTRL                                                            0x18008b28
#define DC_PHY_LPDDR_CTRL_reg_addr                                                   "0xB8008B28"
#define DC_PHY_LPDDR_CTRL_reg                                                        0xB8008B28
#define set_DC_PHY_LPDDR_CTRL_reg(data)   (*((volatile unsigned int*) DC_PHY_LPDDR_CTRL_reg)=data)
#define get_DC_PHY_LPDDR_CTRL_reg   (*((volatile unsigned int*) DC_PHY_LPDDR_CTRL_reg))
#define DC_PHY_LPDDR_CTRL_inst_adr                                                   "0x00CA"
#define DC_PHY_LPDDR_CTRL_inst                                                       0x00CA
#define DC_PHY_LPDDR_CTRL_write_en_2_shift                                           (5)
#define DC_PHY_LPDDR_CTRL_write_en_2_mask                                            (0x00000020)
#define DC_PHY_LPDDR_CTRL_write_en_2(data)                                           (0x00000020&((data)<<5))
#define DC_PHY_LPDDR_CTRL_write_en_2_src(data)                                       ((0x00000020&(data))>>5)
#define DC_PHY_LPDDR_CTRL_get_write_en_2(data)                                       ((0x00000020&(data))>>5)
#define DC_PHY_LPDDR_CTRL_lpddr_ck_en_shift                                          (4)
#define DC_PHY_LPDDR_CTRL_lpddr_ck_en_mask                                           (0x00000010)
#define DC_PHY_LPDDR_CTRL_lpddr_ck_en(data)                                          (0x00000010&((data)<<4))
#define DC_PHY_LPDDR_CTRL_lpddr_ck_en_src(data)                                      ((0x00000010&(data))>>4)
#define DC_PHY_LPDDR_CTRL_get_lpddr_ck_en(data)                                      ((0x00000010&(data))>>4)
#define DC_PHY_LPDDR_CTRL_write_en_1_shift                                           (3)
#define DC_PHY_LPDDR_CTRL_write_en_1_mask                                            (0x00000008)
#define DC_PHY_LPDDR_CTRL_write_en_1(data)                                           (0x00000008&((data)<<3))
#define DC_PHY_LPDDR_CTRL_write_en_1_src(data)                                       ((0x00000008&(data))>>3)
#define DC_PHY_LPDDR_CTRL_get_write_en_1(data)                                       ((0x00000008&(data))>>3)
#define DC_PHY_LPDDR_CTRL_mod_reg_read_shift                                         (2)
#define DC_PHY_LPDDR_CTRL_mod_reg_read_mask                                          (0x00000004)
#define DC_PHY_LPDDR_CTRL_mod_reg_read(data)                                         (0x00000004&((data)<<2))
#define DC_PHY_LPDDR_CTRL_mod_reg_read_src(data)                                     ((0x00000004&(data))>>2)
#define DC_PHY_LPDDR_CTRL_get_mod_reg_read(data)                                     ((0x00000004&(data))>>2)
#define DC_PHY_LPDDR_CTRL_write_en_0_shift                                           (1)
#define DC_PHY_LPDDR_CTRL_write_en_0_mask                                            (0x00000002)
#define DC_PHY_LPDDR_CTRL_write_en_0(data)                                           (0x00000002&((data)<<1))
#define DC_PHY_LPDDR_CTRL_write_en_0_src(data)                                       ((0x00000002&(data))>>1)
#define DC_PHY_LPDDR_CTRL_get_write_en_0(data)                                       ((0x00000002&(data))>>1)
#define DC_PHY_LPDDR_CTRL_mod_reg_write_shift                                        (0)
#define DC_PHY_LPDDR_CTRL_mod_reg_write_mask                                         (0x00000001)
#define DC_PHY_LPDDR_CTRL_mod_reg_write(data)                                        (0x00000001&((data)<<0))
#define DC_PHY_LPDDR_CTRL_mod_reg_write_src(data)                                    ((0x00000001&(data))>>0)
#define DC_PHY_LPDDR_CTRL_get_mod_reg_write(data)                                    ((0x00000001&(data))>>0)


#define DC_PHY_LPDDR_RDAT                                                            0x18008b2C
#define DC_PHY_LPDDR_RDAT_reg_addr                                                   "0xB8008B2C"
#define DC_PHY_LPDDR_RDAT_reg                                                        0xB8008B2C
#define set_DC_PHY_LPDDR_RDAT_reg(data)   (*((volatile unsigned int*) DC_PHY_LPDDR_RDAT_reg)=data)
#define get_DC_PHY_LPDDR_RDAT_reg   (*((volatile unsigned int*) DC_PHY_LPDDR_RDAT_reg))
#define DC_PHY_LPDDR_RDAT_inst_adr                                                   "0x00CB"
#define DC_PHY_LPDDR_RDAT_inst                                                       0x00CB
#define DC_PHY_LPDDR_RDAT_mode_reg_rdata_shift                                       (24)
#define DC_PHY_LPDDR_RDAT_mode_reg_rdata_mask                                        (0xFF000000)
#define DC_PHY_LPDDR_RDAT_mode_reg_rdata(data)                                       (0xFF000000&((data)<<24))
#define DC_PHY_LPDDR_RDAT_mode_reg_rdata_src(data)                                   ((0xFF000000&(data))>>24)
#define DC_PHY_LPDDR_RDAT_get_mode_reg_rdata(data)                                   ((0xFF000000&(data))>>24)


#define DC_PHY_LPDDR_MODE                                                            0x18008b30
#define DC_PHY_LPDDR_MODE_reg_addr                                                   "0xB8008B30"
#define DC_PHY_LPDDR_MODE_reg                                                        0xB8008B30
#define set_DC_PHY_LPDDR_MODE_reg(data)   (*((volatile unsigned int*) DC_PHY_LPDDR_MODE_reg)=data)
#define get_DC_PHY_LPDDR_MODE_reg   (*((volatile unsigned int*) DC_PHY_LPDDR_MODE_reg))
#define DC_PHY_LPDDR_MODE_inst_adr                                                   "0x00CC"
#define DC_PHY_LPDDR_MODE_inst                                                       0x00CC
#define DC_PHY_LPDDR_MODE_mode_reg_wdata_shift                                       (16)
#define DC_PHY_LPDDR_MODE_mode_reg_wdata_mask                                        (0x00FF0000)
#define DC_PHY_LPDDR_MODE_mode_reg_wdata(data)                                       (0x00FF0000&((data)<<16))
#define DC_PHY_LPDDR_MODE_mode_reg_wdata_src(data)                                   ((0x00FF0000&(data))>>16)
#define DC_PHY_LPDDR_MODE_get_mode_reg_wdata(data)                                   ((0x00FF0000&(data))>>16)
#define DC_PHY_LPDDR_MODE_mode_reg_addr_shift                                        (8)
#define DC_PHY_LPDDR_MODE_mode_reg_addr_mask                                         (0x0000FF00)
#define DC_PHY_LPDDR_MODE_mode_reg_addr(data)                                        (0x0000FF00&((data)<<8))
#define DC_PHY_LPDDR_MODE_mode_reg_addr_src(data)                                    ((0x0000FF00&(data))>>8)
#define DC_PHY_LPDDR_MODE_get_mode_reg_addr(data)                                    ((0x0000FF00&(data))>>8)
#define DC_PHY_LPDDR_MODE_lpddr_shift                                                (6)
#define DC_PHY_LPDDR_MODE_lpddr_mask                                                 (0x00000040)
#define DC_PHY_LPDDR_MODE_lpddr(data)                                                (0x00000040&((data)<<6))
#define DC_PHY_LPDDR_MODE_lpddr_src(data)                                            ((0x00000040&(data))>>6)
#define DC_PHY_LPDDR_MODE_get_lpddr(data)                                            ((0x00000040&(data))>>6)


#define DC_PHY_ZQCMP                                                                 0x18008b34
#define DC_PHY_ZQCMP_reg_addr                                                        "0xB8008B34"
#define DC_PHY_ZQCMP_reg                                                             0xB8008B34
#define set_DC_PHY_ZQCMP_reg(data)   (*((volatile unsigned int*) DC_PHY_ZQCMP_reg)=data)
#define get_DC_PHY_ZQCMP_reg   (*((volatile unsigned int*) DC_PHY_ZQCMP_reg))
#define DC_PHY_ZQCMP_inst_adr                                                        "0x00CD"
#define DC_PHY_ZQCMP_inst                                                            0x00CD
#define DC_PHY_ZQCMP_ref_update_dly_shift                                            (26)
#define DC_PHY_ZQCMP_ref_update_dly_mask                                             (0xFC000000)
#define DC_PHY_ZQCMP_ref_update_dly(data)                                            (0xFC000000&((data)<<26))
#define DC_PHY_ZQCMP_ref_update_dly_src(data)                                        ((0xFC000000&(data))>>26)
#define DC_PHY_ZQCMP_get_ref_update_dly(data)                                        ((0xFC000000&(data))>>26)
#define DC_PHY_ZQCMP_zcomp_ctrl_shift                                                (0)
#define DC_PHY_ZQCMP_zcomp_ctrl_mask                                                 (0x0000000F)
#define DC_PHY_ZQCMP_zcomp_ctrl(data)                                                (0x0000000F&((data)<<0))
#define DC_PHY_ZQCMP_zcomp_ctrl_src(data)                                            ((0x0000000F&(data))>>0)
#define DC_PHY_ZQCMP_get_zcomp_ctrl(data)                                            ((0x0000000F&(data))>>0)


#define DC_PHY_RZCTRL_STATUS                                                         0x18008b38
#define DC_PHY_RZCTRL_STATUS_reg_addr                                                "0xB8008B38"
#define DC_PHY_RZCTRL_STATUS_reg                                                     0xB8008B38
#define set_DC_PHY_RZCTRL_STATUS_reg(data)   (*((volatile unsigned int*) DC_PHY_RZCTRL_STATUS_reg)=data)
#define get_DC_PHY_RZCTRL_STATUS_reg   (*((volatile unsigned int*) DC_PHY_RZCTRL_STATUS_reg))
#define DC_PHY_RZCTRL_STATUS_inst_adr                                                "0x00CE"
#define DC_PHY_RZCTRL_STATUS_inst                                                    0x00CE
#define DC_PHY_RZCTRL_STATUS_zq_done_shift                                           (7)
#define DC_PHY_RZCTRL_STATUS_zq_done_mask                                            (0x00000080)
#define DC_PHY_RZCTRL_STATUS_zq_done(data)                                           (0x00000080&((data)<<7))
#define DC_PHY_RZCTRL_STATUS_zq_done_src(data)                                       ((0x00000080&(data))>>7)
#define DC_PHY_RZCTRL_STATUS_get_zq_done(data)                                       ((0x00000080&(data))>>7)
#define DC_PHY_RZCTRL_STATUS_rzq_done_shift                                          (6)
#define DC_PHY_RZCTRL_STATUS_rzq_done_mask                                           (0x00000040)
#define DC_PHY_RZCTRL_STATUS_rzq_done(data)                                          (0x00000040&((data)<<6))
#define DC_PHY_RZCTRL_STATUS_rzq_done_src(data)                                      ((0x00000040&(data))>>6)
#define DC_PHY_RZCTRL_STATUS_get_rzq_done(data)                                      ((0x00000040&(data))>>6)
#define DC_PHY_RZCTRL_STATUS_rzq_480code_shift                                       (1)
#define DC_PHY_RZCTRL_STATUS_rzq_480code_mask                                        (0x0000003E)
#define DC_PHY_RZCTRL_STATUS_rzq_480code(data)                                       (0x0000003E&((data)<<1))
#define DC_PHY_RZCTRL_STATUS_rzq_480code_src(data)                                   ((0x0000003E&(data))>>1)
#define DC_PHY_RZCTRL_STATUS_get_rzq_480code(data)                                   ((0x0000003E&(data))>>1)
#define DC_PHY_RZCTRL_STATUS_rzq_cal_done_shift                                      (0)
#define DC_PHY_RZCTRL_STATUS_rzq_cal_done_mask                                       (0x00000001)
#define DC_PHY_RZCTRL_STATUS_rzq_cal_done(data)                                      (0x00000001&((data)<<0))
#define DC_PHY_RZCTRL_STATUS_rzq_cal_done_src(data)                                  ((0x00000001&(data))>>0)
#define DC_PHY_RZCTRL_STATUS_get_rzq_cal_done(data)                                  ((0x00000001&(data))>>0)


#define DC_PHY_PHY_BIST_RM                                                           0x18008be0
#define DC_PHY_PHY_BIST_RM_reg_addr                                                  "0xB8008BE0"
#define DC_PHY_PHY_BIST_RM_reg                                                       0xB8008BE0
#define set_DC_PHY_PHY_BIST_RM_reg(data)   (*((volatile unsigned int*) DC_PHY_PHY_BIST_RM_reg)=data)
#define get_DC_PHY_PHY_BIST_RM_reg   (*((volatile unsigned int*) DC_PHY_PHY_BIST_RM_reg))
#define DC_PHY_PHY_BIST_RM_inst_adr                                                  "0x00F8"
#define DC_PHY_PHY_BIST_RM_inst                                                      0x00F8
#define DC_PHY_PHY_BIST_RM_bist_en_0_shift                                           (16)
#define DC_PHY_PHY_BIST_RM_bist_en_0_mask                                            (0x00010000)
#define DC_PHY_PHY_BIST_RM_bist_en_0(data)                                           (0x00010000&((data)<<16))
#define DC_PHY_PHY_BIST_RM_bist_en_0_src(data)                                       ((0x00010000&(data))>>16)
#define DC_PHY_PHY_BIST_RM_get_bist_en_0(data)                                       ((0x00010000&(data))>>16)
#define DC_PHY_PHY_BIST_RM_drf_bist_en_0_shift                                       (15)
#define DC_PHY_PHY_BIST_RM_drf_bist_en_0_mask                                        (0x00008000)
#define DC_PHY_PHY_BIST_RM_drf_bist_en_0(data)                                       (0x00008000&((data)<<15))
#define DC_PHY_PHY_BIST_RM_drf_bist_en_0_src(data)                                   ((0x00008000&(data))>>15)
#define DC_PHY_PHY_BIST_RM_get_drf_bist_en_0(data)                                   ((0x00008000&(data))>>15)
#define DC_PHY_PHY_BIST_RM_drf_test_resume_0_shift                                   (14)
#define DC_PHY_PHY_BIST_RM_drf_test_resume_0_mask                                    (0x00004000)
#define DC_PHY_PHY_BIST_RM_drf_test_resume_0(data)                                   (0x00004000&((data)<<14))
#define DC_PHY_PHY_BIST_RM_drf_test_resume_0_src(data)                               ((0x00004000&(data))>>14)
#define DC_PHY_PHY_BIST_RM_get_drf_test_resume_0(data)                               ((0x00004000&(data))>>14)
#define DC_PHY_PHY_BIST_RM_RMEA_shift                                                (12)
#define DC_PHY_PHY_BIST_RM_RMEA_mask                                                 (0x00001000)
#define DC_PHY_PHY_BIST_RM_RMEA(data)                                                (0x00001000&((data)<<12))
#define DC_PHY_PHY_BIST_RM_RMEA_src(data)                                            ((0x00001000&(data))>>12)
#define DC_PHY_PHY_BIST_RM_get_RMEA(data)                                            ((0x00001000&(data))>>12)
#define DC_PHY_PHY_BIST_RM_RMA_3_shift                                               (11)
#define DC_PHY_PHY_BIST_RM_RMA_3_mask                                                (0x00000800)
#define DC_PHY_PHY_BIST_RM_RMA_3(data)                                               (0x00000800&((data)<<11))
#define DC_PHY_PHY_BIST_RM_RMA_3_src(data)                                           ((0x00000800&(data))>>11)
#define DC_PHY_PHY_BIST_RM_get_RMA_3(data)                                           ((0x00000800&(data))>>11)
#define DC_PHY_PHY_BIST_RM_RMA_2_shift                                               (10)
#define DC_PHY_PHY_BIST_RM_RMA_2_mask                                                (0x00000400)
#define DC_PHY_PHY_BIST_RM_RMA_2(data)                                               (0x00000400&((data)<<10))
#define DC_PHY_PHY_BIST_RM_RMA_2_src(data)                                           ((0x00000400&(data))>>10)
#define DC_PHY_PHY_BIST_RM_get_RMA_2(data)                                           ((0x00000400&(data))>>10)
#define DC_PHY_PHY_BIST_RM_RMA_1_shift                                               (9)
#define DC_PHY_PHY_BIST_RM_RMA_1_mask                                                (0x00000200)
#define DC_PHY_PHY_BIST_RM_RMA_1(data)                                               (0x00000200&((data)<<9))
#define DC_PHY_PHY_BIST_RM_RMA_1_src(data)                                           ((0x00000200&(data))>>9)
#define DC_PHY_PHY_BIST_RM_get_RMA_1(data)                                           ((0x00000200&(data))>>9)
#define DC_PHY_PHY_BIST_RM_RMA_0_shift                                               (8)
#define DC_PHY_PHY_BIST_RM_RMA_0_mask                                                (0x00000100)
#define DC_PHY_PHY_BIST_RM_RMA_0(data)                                               (0x00000100&((data)<<8))
#define DC_PHY_PHY_BIST_RM_RMA_0_src(data)                                           ((0x00000100&(data))>>8)
#define DC_PHY_PHY_BIST_RM_get_RMA_0(data)                                           ((0x00000100&(data))>>8)
#define DC_PHY_PHY_BIST_RM_RMEB_shift                                                (4)
#define DC_PHY_PHY_BIST_RM_RMEB_mask                                                 (0x00000010)
#define DC_PHY_PHY_BIST_RM_RMEB(data)                                                (0x00000010&((data)<<4))
#define DC_PHY_PHY_BIST_RM_RMEB_src(data)                                            ((0x00000010&(data))>>4)
#define DC_PHY_PHY_BIST_RM_get_RMEB(data)                                            ((0x00000010&(data))>>4)
#define DC_PHY_PHY_BIST_RM_RMB_3_shift                                               (3)
#define DC_PHY_PHY_BIST_RM_RMB_3_mask                                                (0x00000008)
#define DC_PHY_PHY_BIST_RM_RMB_3(data)                                               (0x00000008&((data)<<3))
#define DC_PHY_PHY_BIST_RM_RMB_3_src(data)                                           ((0x00000008&(data))>>3)
#define DC_PHY_PHY_BIST_RM_get_RMB_3(data)                                           ((0x00000008&(data))>>3)
#define DC_PHY_PHY_BIST_RM_RMB_2_shift                                               (2)
#define DC_PHY_PHY_BIST_RM_RMB_2_mask                                                (0x00000004)
#define DC_PHY_PHY_BIST_RM_RMB_2(data)                                               (0x00000004&((data)<<2))
#define DC_PHY_PHY_BIST_RM_RMB_2_src(data)                                           ((0x00000004&(data))>>2)
#define DC_PHY_PHY_BIST_RM_get_RMB_2(data)                                           ((0x00000004&(data))>>2)
#define DC_PHY_PHY_BIST_RM_RMB_1_shift                                               (1)
#define DC_PHY_PHY_BIST_RM_RMB_1_mask                                                (0x00000002)
#define DC_PHY_PHY_BIST_RM_RMB_1(data)                                               (0x00000002&((data)<<1))
#define DC_PHY_PHY_BIST_RM_RMB_1_src(data)                                           ((0x00000002&(data))>>1)
#define DC_PHY_PHY_BIST_RM_get_RMB_1(data)                                           ((0x00000002&(data))>>1)
#define DC_PHY_PHY_BIST_RM_RMB_0_shift                                               (0)
#define DC_PHY_PHY_BIST_RM_RMB_0_mask                                                (0x00000001)
#define DC_PHY_PHY_BIST_RM_RMB_0(data)                                               (0x00000001&((data)<<0))
#define DC_PHY_PHY_BIST_RM_RMB_0_src(data)                                           ((0x00000001&(data))>>0)
#define DC_PHY_PHY_BIST_RM_get_RMB_0(data)                                           ((0x00000001&(data))>>0)


#define DC_PHY_PHY_BIST0_ST                                                          0x18008be4
#define DC_PHY_PHY_BIST0_ST_reg_addr                                                 "0xB8008BE4"
#define DC_PHY_PHY_BIST0_ST_reg                                                      0xB8008BE4
#define set_DC_PHY_PHY_BIST0_ST_reg(data)   (*((volatile unsigned int*) DC_PHY_PHY_BIST0_ST_reg)=data)
#define get_DC_PHY_PHY_BIST0_ST_reg   (*((volatile unsigned int*) DC_PHY_PHY_BIST0_ST_reg))
#define DC_PHY_PHY_BIST0_ST_inst_adr                                                 "0x00F9"
#define DC_PHY_PHY_BIST0_ST_inst                                                     0x00F9
#define DC_PHY_PHY_BIST0_ST_mbist_st_shift                                           (2)
#define DC_PHY_PHY_BIST0_ST_mbist_st_mask                                            (0x00000004)
#define DC_PHY_PHY_BIST0_ST_mbist_st(data)                                           (0x00000004&((data)<<2))
#define DC_PHY_PHY_BIST0_ST_mbist_st_src(data)                                       ((0x00000004&(data))>>2)
#define DC_PHY_PHY_BIST0_ST_get_mbist_st(data)                                       ((0x00000004&(data))>>2)
#define DC_PHY_PHY_BIST0_ST_bist_fail_shift                                          (1)
#define DC_PHY_PHY_BIST0_ST_bist_fail_mask                                           (0x00000002)
#define DC_PHY_PHY_BIST0_ST_bist_fail(data)                                          (0x00000002&((data)<<1))
#define DC_PHY_PHY_BIST0_ST_bist_fail_src(data)                                      ((0x00000002&(data))>>1)
#define DC_PHY_PHY_BIST0_ST_get_bist_fail(data)                                      ((0x00000002&(data))>>1)
#define DC_PHY_PHY_BIST0_ST_bist_done_shift                                          (0)
#define DC_PHY_PHY_BIST0_ST_bist_done_mask                                           (0x00000001)
#define DC_PHY_PHY_BIST0_ST_bist_done(data)                                          (0x00000001&((data)<<0))
#define DC_PHY_PHY_BIST0_ST_bist_done_src(data)                                      ((0x00000001&(data))>>0)
#define DC_PHY_PHY_BIST0_ST_get_bist_done(data)                                      ((0x00000001&(data))>>0)


#define DC_PHY_PHY_DRF0_ST                                                           0x18008be8
#define DC_PHY_PHY_DRF0_ST_reg_addr                                                  "0xB8008BE8"
#define DC_PHY_PHY_DRF0_ST_reg                                                       0xB8008BE8
#define set_DC_PHY_PHY_DRF0_ST_reg(data)   (*((volatile unsigned int*) DC_PHY_PHY_DRF0_ST_reg)=data)
#define get_DC_PHY_PHY_DRF0_ST_reg   (*((volatile unsigned int*) DC_PHY_PHY_DRF0_ST_reg))
#define DC_PHY_PHY_DRF0_ST_inst_adr                                                  "0x00FA"
#define DC_PHY_PHY_DRF0_ST_inst                                                      0x00FA
#define DC_PHY_PHY_DRF0_ST_drf_start_pause_shift                                     (16)
#define DC_PHY_PHY_DRF0_ST_drf_start_pause_mask                                      (0x00010000)
#define DC_PHY_PHY_DRF0_ST_drf_start_pause(data)                                     (0x00010000&((data)<<16))
#define DC_PHY_PHY_DRF0_ST_drf_start_pause_src(data)                                 ((0x00010000&(data))>>16)
#define DC_PHY_PHY_DRF0_ST_get_drf_start_pause(data)                                 ((0x00010000&(data))>>16)
#define DC_PHY_PHY_DRF0_ST_drf_fail_shift                                            (1)
#define DC_PHY_PHY_DRF0_ST_drf_fail_mask                                             (0x00000002)
#define DC_PHY_PHY_DRF0_ST_drf_fail(data)                                            (0x00000002&((data)<<1))
#define DC_PHY_PHY_DRF0_ST_drf_fail_src(data)                                        ((0x00000002&(data))>>1)
#define DC_PHY_PHY_DRF0_ST_get_drf_fail(data)                                        ((0x00000002&(data))>>1)
#define DC_PHY_PHY_DRF0_ST_drf_done_shift                                            (0)
#define DC_PHY_PHY_DRF0_ST_drf_done_mask                                             (0x00000001)
#define DC_PHY_PHY_DRF0_ST_drf_done(data)                                            (0x00000001&((data)<<0))
#define DC_PHY_PHY_DRF0_ST_drf_done_src(data)                                        ((0x00000001&(data))>>0)
#define DC_PHY_PHY_DRF0_ST_get_drf_done(data)                                        ((0x00000001&(data))>>0)


#define DC_PHY_PHY_BIST1_ST                                                          0x18008bec
#define DC_PHY_PHY_BIST1_ST_reg_addr                                                 "0xB8008BEC"
#define DC_PHY_PHY_BIST1_ST_reg                                                      0xB8008BEC
#define set_DC_PHY_PHY_BIST1_ST_reg(data)   (*((volatile unsigned int*) DC_PHY_PHY_BIST1_ST_reg)=data)
#define get_DC_PHY_PHY_BIST1_ST_reg   (*((volatile unsigned int*) DC_PHY_PHY_BIST1_ST_reg))
#define DC_PHY_PHY_BIST1_ST_inst_adr                                                 "0x00FB"
#define DC_PHY_PHY_BIST1_ST_inst                                                     0x00FB
#define DC_PHY_PHY_BIST1_ST_mbist_st_shift                                           (2)
#define DC_PHY_PHY_BIST1_ST_mbist_st_mask                                            (0x00000004)
#define DC_PHY_PHY_BIST1_ST_mbist_st(data)                                           (0x00000004&((data)<<2))
#define DC_PHY_PHY_BIST1_ST_mbist_st_src(data)                                       ((0x00000004&(data))>>2)
#define DC_PHY_PHY_BIST1_ST_get_mbist_st(data)                                       ((0x00000004&(data))>>2)
#define DC_PHY_PHY_BIST1_ST_bist_fail_shift                                          (1)
#define DC_PHY_PHY_BIST1_ST_bist_fail_mask                                           (0x00000002)
#define DC_PHY_PHY_BIST1_ST_bist_fail(data)                                          (0x00000002&((data)<<1))
#define DC_PHY_PHY_BIST1_ST_bist_fail_src(data)                                      ((0x00000002&(data))>>1)
#define DC_PHY_PHY_BIST1_ST_get_bist_fail(data)                                      ((0x00000002&(data))>>1)
#define DC_PHY_PHY_BIST1_ST_bist_done_shift                                          (0)
#define DC_PHY_PHY_BIST1_ST_bist_done_mask                                           (0x00000001)
#define DC_PHY_PHY_BIST1_ST_bist_done(data)                                          (0x00000001&((data)<<0))
#define DC_PHY_PHY_BIST1_ST_bist_done_src(data)                                      ((0x00000001&(data))>>0)
#define DC_PHY_PHY_BIST1_ST_get_bist_done(data)                                      ((0x00000001&(data))>>0)


#define DC_PHY_PHY_DRF1_ST                                                           0x18008bf0
#define DC_PHY_PHY_DRF1_ST_reg_addr                                                  "0xB8008BF0"
#define DC_PHY_PHY_DRF1_ST_reg                                                       0xB8008BF0
#define set_DC_PHY_PHY_DRF1_ST_reg(data)   (*((volatile unsigned int*) DC_PHY_PHY_DRF1_ST_reg)=data)
#define get_DC_PHY_PHY_DRF1_ST_reg   (*((volatile unsigned int*) DC_PHY_PHY_DRF1_ST_reg))
#define DC_PHY_PHY_DRF1_ST_inst_adr                                                  "0x00FC"
#define DC_PHY_PHY_DRF1_ST_inst                                                      0x00FC
#define DC_PHY_PHY_DRF1_ST_drf_start_pause_shift                                     (16)
#define DC_PHY_PHY_DRF1_ST_drf_start_pause_mask                                      (0x00010000)
#define DC_PHY_PHY_DRF1_ST_drf_start_pause(data)                                     (0x00010000&((data)<<16))
#define DC_PHY_PHY_DRF1_ST_drf_start_pause_src(data)                                 ((0x00010000&(data))>>16)
#define DC_PHY_PHY_DRF1_ST_get_drf_start_pause(data)                                 ((0x00010000&(data))>>16)
#define DC_PHY_PHY_DRF1_ST_drf_fail_shift                                            (1)
#define DC_PHY_PHY_DRF1_ST_drf_fail_mask                                             (0x00000002)
#define DC_PHY_PHY_DRF1_ST_drf_fail(data)                                            (0x00000002&((data)<<1))
#define DC_PHY_PHY_DRF1_ST_drf_fail_src(data)                                        ((0x00000002&(data))>>1)
#define DC_PHY_PHY_DRF1_ST_get_drf_fail(data)                                        ((0x00000002&(data))>>1)
#define DC_PHY_PHY_DRF1_ST_drf_done_shift                                            (0)
#define DC_PHY_PHY_DRF1_ST_drf_done_mask                                             (0x00000001)
#define DC_PHY_PHY_DRF1_ST_drf_done(data)                                            (0x00000001&((data)<<0))
#define DC_PHY_PHY_DRF1_ST_drf_done_src(data)                                        ((0x00000001&(data))>>0)
#define DC_PHY_PHY_DRF1_ST_get_drf_done(data)                                        ((0x00000001&(data))>>0)


#define DC_PHY_WL_CTRL_0                                                             0x18008c00
#define DC_PHY_WL_CTRL_0_reg_addr                                                    "0xB8008C00"
#define DC_PHY_WL_CTRL_0_reg                                                         0xB8008C00
#define set_DC_PHY_WL_CTRL_0_reg(data)   (*((volatile unsigned int*) DC_PHY_WL_CTRL_0_reg)=data)
#define get_DC_PHY_WL_CTRL_0_reg   (*((volatile unsigned int*) DC_PHY_WL_CTRL_0_reg))
#define DC_PHY_WL_CTRL_0_inst_adr                                                    "0x0000"
#define DC_PHY_WL_CTRL_0_inst                                                        0x0000
#define DC_PHY_WL_CTRL_0_wl_dqs3_oe_mux_sel_shift                                    (14)
#define DC_PHY_WL_CTRL_0_wl_dqs3_oe_mux_sel_mask                                     (0x0000C000)
#define DC_PHY_WL_CTRL_0_wl_dqs3_oe_mux_sel(data)                                    (0x0000C000&((data)<<14))
#define DC_PHY_WL_CTRL_0_wl_dqs3_oe_mux_sel_src(data)                                ((0x0000C000&(data))>>14)
#define DC_PHY_WL_CTRL_0_get_wl_dqs3_oe_mux_sel(data)                                ((0x0000C000&(data))>>14)
#define DC_PHY_WL_CTRL_0_wl_dqs2_oe_mux_sel_shift                                    (12)
#define DC_PHY_WL_CTRL_0_wl_dqs2_oe_mux_sel_mask                                     (0x00003000)
#define DC_PHY_WL_CTRL_0_wl_dqs2_oe_mux_sel(data)                                    (0x00003000&((data)<<12))
#define DC_PHY_WL_CTRL_0_wl_dqs2_oe_mux_sel_src(data)                                ((0x00003000&(data))>>12)
#define DC_PHY_WL_CTRL_0_get_wl_dqs2_oe_mux_sel(data)                                ((0x00003000&(data))>>12)
#define DC_PHY_WL_CTRL_0_wl_dqs1_oe_mux_sel_shift                                    (10)
#define DC_PHY_WL_CTRL_0_wl_dqs1_oe_mux_sel_mask                                     (0x00000C00)
#define DC_PHY_WL_CTRL_0_wl_dqs1_oe_mux_sel(data)                                    (0x00000C00&((data)<<10))
#define DC_PHY_WL_CTRL_0_wl_dqs1_oe_mux_sel_src(data)                                ((0x00000C00&(data))>>10)
#define DC_PHY_WL_CTRL_0_get_wl_dqs1_oe_mux_sel(data)                                ((0x00000C00&(data))>>10)
#define DC_PHY_WL_CTRL_0_wl_dqs0_oe_mux_sel_shift                                    (8)
#define DC_PHY_WL_CTRL_0_wl_dqs0_oe_mux_sel_mask                                     (0x00000300)
#define DC_PHY_WL_CTRL_0_wl_dqs0_oe_mux_sel(data)                                    (0x00000300&((data)<<8))
#define DC_PHY_WL_CTRL_0_wl_dqs0_oe_mux_sel_src(data)                                ((0x00000300&(data))>>8)
#define DC_PHY_WL_CTRL_0_get_wl_dqs0_oe_mux_sel(data)                                ((0x00000300&(data))>>8)
#define DC_PHY_WL_CTRL_0_wl_dqs3_mux_sel_shift                                       (6)
#define DC_PHY_WL_CTRL_0_wl_dqs3_mux_sel_mask                                        (0x000000C0)
#define DC_PHY_WL_CTRL_0_wl_dqs3_mux_sel(data)                                       (0x000000C0&((data)<<6))
#define DC_PHY_WL_CTRL_0_wl_dqs3_mux_sel_src(data)                                   ((0x000000C0&(data))>>6)
#define DC_PHY_WL_CTRL_0_get_wl_dqs3_mux_sel(data)                                   ((0x000000C0&(data))>>6)
#define DC_PHY_WL_CTRL_0_wl_dqs2_mux_sel_shift                                       (4)
#define DC_PHY_WL_CTRL_0_wl_dqs2_mux_sel_mask                                        (0x00000030)
#define DC_PHY_WL_CTRL_0_wl_dqs2_mux_sel(data)                                       (0x00000030&((data)<<4))
#define DC_PHY_WL_CTRL_0_wl_dqs2_mux_sel_src(data)                                   ((0x00000030&(data))>>4)
#define DC_PHY_WL_CTRL_0_get_wl_dqs2_mux_sel(data)                                   ((0x00000030&(data))>>4)
#define DC_PHY_WL_CTRL_0_wl_dqs1_mux_sel_shift                                       (2)
#define DC_PHY_WL_CTRL_0_wl_dqs1_mux_sel_mask                                        (0x0000000C)
#define DC_PHY_WL_CTRL_0_wl_dqs1_mux_sel(data)                                       (0x0000000C&((data)<<2))
#define DC_PHY_WL_CTRL_0_wl_dqs1_mux_sel_src(data)                                   ((0x0000000C&(data))>>2)
#define DC_PHY_WL_CTRL_0_get_wl_dqs1_mux_sel(data)                                   ((0x0000000C&(data))>>2)
#define DC_PHY_WL_CTRL_0_wl_dqs0_mux_sel_shift                                       (0)
#define DC_PHY_WL_CTRL_0_wl_dqs0_mux_sel_mask                                        (0x00000003)
#define DC_PHY_WL_CTRL_0_wl_dqs0_mux_sel(data)                                       (0x00000003&((data)<<0))
#define DC_PHY_WL_CTRL_0_wl_dqs0_mux_sel_src(data)                                   ((0x00000003&(data))>>0)
#define DC_PHY_WL_CTRL_0_get_wl_dqs0_mux_sel(data)                                   ((0x00000003&(data))>>0)


#define DC_PHY_WL_CTRL_1                                                             0x18008c04
#define DC_PHY_WL_CTRL_1_reg_addr                                                    "0xB8008C04"
#define DC_PHY_WL_CTRL_1_reg                                                         0xB8008C04
#define set_DC_PHY_WL_CTRL_1_reg(data)   (*((volatile unsigned int*) DC_PHY_WL_CTRL_1_reg)=data)
#define get_DC_PHY_WL_CTRL_1_reg   (*((volatile unsigned int*) DC_PHY_WL_CTRL_1_reg))
#define DC_PHY_WL_CTRL_1_inst_adr                                                    "0x0001"
#define DC_PHY_WL_CTRL_1_inst                                                        0x0001
#define DC_PHY_WL_CTRL_1_wl_dq31to24_oe_mux_sel_shift                                (14)
#define DC_PHY_WL_CTRL_1_wl_dq31to24_oe_mux_sel_mask                                 (0x0000C000)
#define DC_PHY_WL_CTRL_1_wl_dq31to24_oe_mux_sel(data)                                (0x0000C000&((data)<<14))
#define DC_PHY_WL_CTRL_1_wl_dq31to24_oe_mux_sel_src(data)                            ((0x0000C000&(data))>>14)
#define DC_PHY_WL_CTRL_1_get_wl_dq31to24_oe_mux_sel(data)                            ((0x0000C000&(data))>>14)
#define DC_PHY_WL_CTRL_1_wl_dq23to16_oe_mux_sel_shift                                (12)
#define DC_PHY_WL_CTRL_1_wl_dq23to16_oe_mux_sel_mask                                 (0x00003000)
#define DC_PHY_WL_CTRL_1_wl_dq23to16_oe_mux_sel(data)                                (0x00003000&((data)<<12))
#define DC_PHY_WL_CTRL_1_wl_dq23to16_oe_mux_sel_src(data)                            ((0x00003000&(data))>>12)
#define DC_PHY_WL_CTRL_1_get_wl_dq23to16_oe_mux_sel(data)                            ((0x00003000&(data))>>12)
#define DC_PHY_WL_CTRL_1_wl_dq15to8_oe_mux_sel_shift                                 (10)
#define DC_PHY_WL_CTRL_1_wl_dq15to8_oe_mux_sel_mask                                  (0x00000C00)
#define DC_PHY_WL_CTRL_1_wl_dq15to8_oe_mux_sel(data)                                 (0x00000C00&((data)<<10))
#define DC_PHY_WL_CTRL_1_wl_dq15to8_oe_mux_sel_src(data)                             ((0x00000C00&(data))>>10)
#define DC_PHY_WL_CTRL_1_get_wl_dq15to8_oe_mux_sel(data)                             ((0x00000C00&(data))>>10)
#define DC_PHY_WL_CTRL_1_wl_dq7to0_oe_mux_sel_shift                                  (8)
#define DC_PHY_WL_CTRL_1_wl_dq7to0_oe_mux_sel_mask                                   (0x00000300)
#define DC_PHY_WL_CTRL_1_wl_dq7to0_oe_mux_sel(data)                                  (0x00000300&((data)<<8))
#define DC_PHY_WL_CTRL_1_wl_dq7to0_oe_mux_sel_src(data)                              ((0x00000300&(data))>>8)
#define DC_PHY_WL_CTRL_1_get_wl_dq7to0_oe_mux_sel(data)                              ((0x00000300&(data))>>8)
#define DC_PHY_WL_CTRL_1_wl_dq31to24_mux_sel_shift                                   (6)
#define DC_PHY_WL_CTRL_1_wl_dq31to24_mux_sel_mask                                    (0x000000C0)
#define DC_PHY_WL_CTRL_1_wl_dq31to24_mux_sel(data)                                   (0x000000C0&((data)<<6))
#define DC_PHY_WL_CTRL_1_wl_dq31to24_mux_sel_src(data)                               ((0x000000C0&(data))>>6)
#define DC_PHY_WL_CTRL_1_get_wl_dq31to24_mux_sel(data)                               ((0x000000C0&(data))>>6)
#define DC_PHY_WL_CTRL_1_wl_dq23to16_mux_sel_shift                                   (4)
#define DC_PHY_WL_CTRL_1_wl_dq23to16_mux_sel_mask                                    (0x00000030)
#define DC_PHY_WL_CTRL_1_wl_dq23to16_mux_sel(data)                                   (0x00000030&((data)<<4))
#define DC_PHY_WL_CTRL_1_wl_dq23to16_mux_sel_src(data)                               ((0x00000030&(data))>>4)
#define DC_PHY_WL_CTRL_1_get_wl_dq23to16_mux_sel(data)                               ((0x00000030&(data))>>4)
#define DC_PHY_WL_CTRL_1_wl_dq15to8_mux_sel_shift                                    (2)
#define DC_PHY_WL_CTRL_1_wl_dq15to8_mux_sel_mask                                     (0x0000000C)
#define DC_PHY_WL_CTRL_1_wl_dq15to8_mux_sel(data)                                    (0x0000000C&((data)<<2))
#define DC_PHY_WL_CTRL_1_wl_dq15to8_mux_sel_src(data)                                ((0x0000000C&(data))>>2)
#define DC_PHY_WL_CTRL_1_get_wl_dq15to8_mux_sel(data)                                ((0x0000000C&(data))>>2)
#define DC_PHY_WL_CTRL_1_wl_dq7to0_mux_sel_shift                                     (0)
#define DC_PHY_WL_CTRL_1_wl_dq7to0_mux_sel_mask                                      (0x00000003)
#define DC_PHY_WL_CTRL_1_wl_dq7to0_mux_sel(data)                                     (0x00000003&((data)<<0))
#define DC_PHY_WL_CTRL_1_wl_dq7to0_mux_sel_src(data)                                 ((0x00000003&(data))>>0)
#define DC_PHY_WL_CTRL_1_get_wl_dq7to0_mux_sel(data)                                 ((0x00000003&(data))>>0)


#define DC_PHY_FIFO_ARB_0                                                            0x18008e00
#define DC_PHY_FIFO_ARB_0_reg_addr                                                   "0xB8008E00"
#define DC_PHY_FIFO_ARB_0_reg                                                        0xB8008E00
#define set_DC_PHY_FIFO_ARB_0_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_0_reg)=data)
#define get_DC_PHY_FIFO_ARB_0_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_0_reg))
#define DC_PHY_FIFO_ARB_0_inst_adr                                                   "0x0080"
#define DC_PHY_FIFO_ARB_0_inst                                                       0x0080
#define DC_PHY_FIFO_ARB_0_fifo_arb_sel_shift                                         (24)
#define DC_PHY_FIFO_ARB_0_fifo_arb_sel_mask                                          (0x01000000)
#define DC_PHY_FIFO_ARB_0_fifo_arb_sel(data)                                         (0x01000000&((data)<<24))
#define DC_PHY_FIFO_ARB_0_fifo_arb_sel_src(data)                                     ((0x01000000&(data))>>24)
#define DC_PHY_FIFO_ARB_0_get_fifo_arb_sel(data)                                     ((0x01000000&(data))>>24)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_cnt_shift                                     (20)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_cnt_mask                                      (0x00700000)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_cnt(data)                                     (0x00700000&((data)<<20))
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_cnt_src(data)                                 ((0x00700000&(data))>>20)
#define DC_PHY_FIFO_ARB_0_get_cmdq_ch_fifo_cnt(data)                                 ((0x00700000&(data))>>20)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_rd_ptr_shift                                  (16)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_rd_ptr_mask                                   (0x00030000)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_rd_ptr(data)                                  (0x00030000&((data)<<16))
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_rd_ptr_src(data)                              ((0x00030000&(data))>>16)
#define DC_PHY_FIFO_ARB_0_get_cmdq_ch_fifo_rd_ptr(data)                              ((0x00030000&(data))>>16)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_wr_ptr_shift                                  (12)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_wr_ptr_mask                                   (0x00003000)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_wr_ptr(data)                                  (0x00003000&((data)<<12))
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_wr_ptr_src(data)                              ((0x00003000&(data))>>12)
#define DC_PHY_FIFO_ARB_0_get_cmdq_ch_fifo_wr_ptr(data)                              ((0x00003000&(data))>>12)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_overflow_shift                                (11)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_overflow_mask                                 (0x00000800)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_overflow(data)                                (0x00000800&((data)<<11))
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_overflow_src(data)                            ((0x00000800&(data))>>11)
#define DC_PHY_FIFO_ARB_0_get_cmdq_ch_fifo_overflow(data)                            ((0x00000800&(data))>>11)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_underflow_shift                               (10)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_underflow_mask                                (0x00000400)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_underflow(data)                               (0x00000400&((data)<<10))
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_underflow_src(data)                           ((0x00000400&(data))>>10)
#define DC_PHY_FIFO_ARB_0_get_cmdq_ch_fifo_underflow(data)                           ((0x00000400&(data))>>10)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_full_shift                                    (9)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_full_mask                                     (0x00000200)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_full(data)                                    (0x00000200&((data)<<9))
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_full_src(data)                                ((0x00000200&(data))>>9)
#define DC_PHY_FIFO_ARB_0_get_cmdq_ch_fifo_full(data)                                ((0x00000200&(data))>>9)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_empty_shift                                   (8)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_empty_mask                                    (0x00000100)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_empty(data)                                   (0x00000100&((data)<<8))
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_empty_src(data)                               ((0x00000100&(data))>>8)
#define DC_PHY_FIFO_ARB_0_get_cmdq_ch_fifo_empty(data)                               ((0x00000100&(data))>>8)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_thr_shift                                     (4)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_thr_mask                                      (0x000000F0)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_thr(data)                                     (0x000000F0&((data)<<4))
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_thr_src(data)                                 ((0x000000F0&(data))>>4)
#define DC_PHY_FIFO_ARB_0_get_cmdq_ch_fifo_thr(data)                                 ((0x000000F0&(data))>>4)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_overflow_clr_shift                            (3)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_overflow_clr_mask                             (0x00000008)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_overflow_clr(data)                            (0x00000008&((data)<<3))
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_overflow_clr_src(data)                        ((0x00000008&(data))>>3)
#define DC_PHY_FIFO_ARB_0_get_cmdq_ch_fifo_overflow_clr(data)                        ((0x00000008&(data))>>3)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_underflow_clr_shift                           (2)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_underflow_clr_mask                            (0x00000004)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_underflow_clr(data)                           (0x00000004&((data)<<2))
#define DC_PHY_FIFO_ARB_0_cmdq_ch_fifo_underflow_clr_src(data)                       ((0x00000004&(data))>>2)
#define DC_PHY_FIFO_ARB_0_get_cmdq_ch_fifo_underflow_clr(data)                       ((0x00000004&(data))>>2)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_clk_gated_en_shift                                 (1)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_clk_gated_en_mask                                  (0x00000002)
#define DC_PHY_FIFO_ARB_0_cmdq_ch_clk_gated_en(data)                                 (0x00000002&((data)<<1))
#define DC_PHY_FIFO_ARB_0_cmdq_ch_clk_gated_en_src(data)                             ((0x00000002&(data))>>1)
#define DC_PHY_FIFO_ARB_0_get_cmdq_ch_clk_gated_en(data)                             ((0x00000002&(data))>>1)
#define DC_PHY_FIFO_ARB_0_fifo_arb_dis_shift                                         (0)
#define DC_PHY_FIFO_ARB_0_fifo_arb_dis_mask                                          (0x00000001)
#define DC_PHY_FIFO_ARB_0_fifo_arb_dis(data)                                         (0x00000001&((data)<<0))
#define DC_PHY_FIFO_ARB_0_fifo_arb_dis_src(data)                                     ((0x00000001&(data))>>0)
#define DC_PHY_FIFO_ARB_0_get_fifo_arb_dis(data)                                     ((0x00000001&(data))>>0)


#define DC_PHY_FIFO_ARB_1                                                            0x18008e04
#define DC_PHY_FIFO_ARB_1_reg_addr                                                   "0xB8008E04"
#define DC_PHY_FIFO_ARB_1_reg                                                        0xB8008E04
#define set_DC_PHY_FIFO_ARB_1_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_1_reg)=data)
#define get_DC_PHY_FIFO_ARB_1_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_1_reg))
#define DC_PHY_FIFO_ARB_1_inst_adr                                                   "0x0081"
#define DC_PHY_FIFO_ARB_1_inst                                                       0x0081
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst1_cmd_dis_shift                             (5)
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst1_cmd_dis_mask                              (0x00000020)
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst1_cmd_dis(data)                             (0x00000020&((data)<<5))
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst1_cmd_dis_src(data)                         ((0x00000020&(data))>>5)
#define DC_PHY_FIFO_ARB_1_get_cmdq_ch_gnt_mst1_cmd_dis(data)                         ((0x00000020&(data))>>5)
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst1_cti_dis_shift                             (4)
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst1_cti_dis_mask                              (0x00000010)
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst1_cti_dis(data)                             (0x00000010&((data)<<4))
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst1_cti_dis_src(data)                         ((0x00000010&(data))>>4)
#define DC_PHY_FIFO_ARB_1_get_cmdq_ch_gnt_mst1_cti_dis(data)                         ((0x00000010&(data))>>4)
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst0_cmd_dis_shift                             (1)
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst0_cmd_dis_mask                              (0x00000002)
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst0_cmd_dis(data)                             (0x00000002&((data)<<1))
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst0_cmd_dis_src(data)                         ((0x00000002&(data))>>1)
#define DC_PHY_FIFO_ARB_1_get_cmdq_ch_gnt_mst0_cmd_dis(data)                         ((0x00000002&(data))>>1)
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst0_cti_dis_shift                             (0)
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst0_cti_dis_mask                              (0x00000001)
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst0_cti_dis(data)                             (0x00000001&((data)<<0))
#define DC_PHY_FIFO_ARB_1_cmdq_ch_gnt_mst0_cti_dis_src(data)                         ((0x00000001&(data))>>0)
#define DC_PHY_FIFO_ARB_1_get_cmdq_ch_gnt_mst0_cti_dis(data)                         ((0x00000001&(data))>>0)


#define DC_PHY_FIFO_ARB_2                                                            0x18008e08
#define DC_PHY_FIFO_ARB_2_reg_addr                                                   "0xB8008E08"
#define DC_PHY_FIFO_ARB_2_reg                                                        0xB8008E08
#define set_DC_PHY_FIFO_ARB_2_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_2_reg)=data)
#define get_DC_PHY_FIFO_ARB_2_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_2_reg))
#define DC_PHY_FIFO_ARB_2_inst_adr                                                   "0x0082"
#define DC_PHY_FIFO_ARB_2_inst                                                       0x0082
#define DC_PHY_FIFO_ARB_2_cmdq_ch_dbg_mod_shift                                      (0)
#define DC_PHY_FIFO_ARB_2_cmdq_ch_dbg_mod_mask                                       (0x000000FF)
#define DC_PHY_FIFO_ARB_2_cmdq_ch_dbg_mod(data)                                      (0x000000FF&((data)<<0))
#define DC_PHY_FIFO_ARB_2_cmdq_ch_dbg_mod_src(data)                                  ((0x000000FF&(data))>>0)
#define DC_PHY_FIFO_ARB_2_get_cmdq_ch_dbg_mod(data)                                  ((0x000000FF&(data))>>0)


#define DC_PHY_FIFO_ARB_3                                                            0x18008e0c
#define DC_PHY_FIFO_ARB_3_reg_addr                                                   "0xB8008E0C"
#define DC_PHY_FIFO_ARB_3_reg                                                        0xB8008E0C
#define set_DC_PHY_FIFO_ARB_3_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_3_reg)=data)
#define get_DC_PHY_FIFO_ARB_3_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_3_reg))
#define DC_PHY_FIFO_ARB_3_inst_adr                                                   "0x0083"
#define DC_PHY_FIFO_ARB_3_inst                                                       0x0083
#define DC_PHY_FIFO_ARB_3_cmdq_ch_dummy_0_shift                                      (0)
#define DC_PHY_FIFO_ARB_3_cmdq_ch_dummy_0_mask                                       (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_3_cmdq_ch_dummy_0(data)                                      (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_3_cmdq_ch_dummy_0_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_3_get_cmdq_ch_dummy_0(data)                                  ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_4                                                            0x18008e10
#define DC_PHY_FIFO_ARB_4_reg_addr                                                   "0xB8008E10"
#define DC_PHY_FIFO_ARB_4_reg                                                        0xB8008E10
#define set_DC_PHY_FIFO_ARB_4_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_4_reg)=data)
#define get_DC_PHY_FIFO_ARB_4_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_4_reg))
#define DC_PHY_FIFO_ARB_4_inst_adr                                                   "0x0084"
#define DC_PHY_FIFO_ARB_4_inst                                                       0x0084
#define DC_PHY_FIFO_ARB_4_cmdq_ch_gnt_st0_shift                                      (0)
#define DC_PHY_FIFO_ARB_4_cmdq_ch_gnt_st0_mask                                       (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_4_cmdq_ch_gnt_st0(data)                                      (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_4_cmdq_ch_gnt_st0_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_4_get_cmdq_ch_gnt_st0(data)                                  ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_5                                                            0x18008e14
#define DC_PHY_FIFO_ARB_5_reg_addr                                                   "0xB8008E14"
#define DC_PHY_FIFO_ARB_5_reg                                                        0xB8008E14
#define set_DC_PHY_FIFO_ARB_5_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_5_reg)=data)
#define get_DC_PHY_FIFO_ARB_5_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_5_reg))
#define DC_PHY_FIFO_ARB_5_inst_adr                                                   "0x0085"
#define DC_PHY_FIFO_ARB_5_inst                                                       0x0085
#define DC_PHY_FIFO_ARB_5_cmdq_ch_gnt_st1_shift                                      (0)
#define DC_PHY_FIFO_ARB_5_cmdq_ch_gnt_st1_mask                                       (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_5_cmdq_ch_gnt_st1(data)                                      (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_5_cmdq_ch_gnt_st1_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_5_get_cmdq_ch_gnt_st1(data)                                  ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_6                                                            0x18008e18
#define DC_PHY_FIFO_ARB_6_reg_addr                                                   "0xB8008E18"
#define DC_PHY_FIFO_ARB_6_reg                                                        0xB8008E18
#define set_DC_PHY_FIFO_ARB_6_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_6_reg)=data)
#define get_DC_PHY_FIFO_ARB_6_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_6_reg))
#define DC_PHY_FIFO_ARB_6_inst_adr                                                   "0x0086"
#define DC_PHY_FIFO_ARB_6_inst                                                       0x0086
#define DC_PHY_FIFO_ARB_6_cmdq_ch_gnt_st2_shift                                      (0)
#define DC_PHY_FIFO_ARB_6_cmdq_ch_gnt_st2_mask                                       (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_6_cmdq_ch_gnt_st2(data)                                      (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_6_cmdq_ch_gnt_st2_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_6_get_cmdq_ch_gnt_st2(data)                                  ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_7                                                            0x18008e1c
#define DC_PHY_FIFO_ARB_7_reg_addr                                                   "0xB8008E1C"
#define DC_PHY_FIFO_ARB_7_reg                                                        0xB8008E1C
#define set_DC_PHY_FIFO_ARB_7_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_7_reg)=data)
#define get_DC_PHY_FIFO_ARB_7_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_7_reg))
#define DC_PHY_FIFO_ARB_7_inst_adr                                                   "0x0087"
#define DC_PHY_FIFO_ARB_7_inst                                                       0x0087
#define DC_PHY_FIFO_ARB_7_cmdq_ch_gnt_st3_shift                                      (0)
#define DC_PHY_FIFO_ARB_7_cmdq_ch_gnt_st3_mask                                       (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_7_cmdq_ch_gnt_st3(data)                                      (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_7_cmdq_ch_gnt_st3_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_7_get_cmdq_ch_gnt_st3(data)                                  ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_8                                                            0x18008e20
#define DC_PHY_FIFO_ARB_8_reg_addr                                                   "0xB8008E20"
#define DC_PHY_FIFO_ARB_8_reg                                                        0xB8008E20
#define set_DC_PHY_FIFO_ARB_8_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_8_reg)=data)
#define get_DC_PHY_FIFO_ARB_8_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_8_reg))
#define DC_PHY_FIFO_ARB_8_inst_adr                                                   "0x0088"
#define DC_PHY_FIFO_ARB_8_inst                                                       0x0088
#define DC_PHY_FIFO_ARB_8_cmdq_ch_gnt_st4_shift                                      (0)
#define DC_PHY_FIFO_ARB_8_cmdq_ch_gnt_st4_mask                                       (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_8_cmdq_ch_gnt_st4(data)                                      (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_8_cmdq_ch_gnt_st4_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_8_get_cmdq_ch_gnt_st4(data)                                  ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_9                                                            0x18008e24
#define DC_PHY_FIFO_ARB_9_reg_addr                                                   "0xB8008E24"
#define DC_PHY_FIFO_ARB_9_reg                                                        0xB8008E24
#define set_DC_PHY_FIFO_ARB_9_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_9_reg)=data)
#define get_DC_PHY_FIFO_ARB_9_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_9_reg))
#define DC_PHY_FIFO_ARB_9_inst_adr                                                   "0x0089"
#define DC_PHY_FIFO_ARB_9_inst                                                       0x0089
#define DC_PHY_FIFO_ARB_9_cmdq_ch_gnt_st5_shift                                      (0)
#define DC_PHY_FIFO_ARB_9_cmdq_ch_gnt_st5_mask                                       (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_9_cmdq_ch_gnt_st5(data)                                      (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_9_cmdq_ch_gnt_st5_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_9_get_cmdq_ch_gnt_st5(data)                                  ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_10                                                           0x18008e28
#define DC_PHY_FIFO_ARB_10_reg_addr                                                  "0xB8008E28"
#define DC_PHY_FIFO_ARB_10_reg                                                       0xB8008E28
#define set_DC_PHY_FIFO_ARB_10_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_10_reg)=data)
#define get_DC_PHY_FIFO_ARB_10_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_10_reg))
#define DC_PHY_FIFO_ARB_10_inst_adr                                                  "0x008A"
#define DC_PHY_FIFO_ARB_10_inst                                                      0x008A
#define DC_PHY_FIFO_ARB_10_cmdq_ch_gnt_st6_shift                                     (0)
#define DC_PHY_FIFO_ARB_10_cmdq_ch_gnt_st6_mask                                      (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_10_cmdq_ch_gnt_st6(data)                                     (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_10_cmdq_ch_gnt_st6_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_10_get_cmdq_ch_gnt_st6(data)                                 ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_11                                                           0x18008e2c
#define DC_PHY_FIFO_ARB_11_reg_addr                                                  "0xB8008E2C"
#define DC_PHY_FIFO_ARB_11_reg                                                       0xB8008E2C
#define set_DC_PHY_FIFO_ARB_11_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_11_reg)=data)
#define get_DC_PHY_FIFO_ARB_11_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_11_reg))
#define DC_PHY_FIFO_ARB_11_inst_adr                                                  "0x008B"
#define DC_PHY_FIFO_ARB_11_inst                                                      0x008B
#define DC_PHY_FIFO_ARB_11_cmdq_ch_gnt_st7_shift                                     (0)
#define DC_PHY_FIFO_ARB_11_cmdq_ch_gnt_st7_mask                                      (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_11_cmdq_ch_gnt_st7(data)                                     (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_11_cmdq_ch_gnt_st7_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_11_get_cmdq_ch_gnt_st7(data)                                 ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_12                                                           0x18008e30
#define DC_PHY_FIFO_ARB_12_reg_addr                                                  "0xB8008E30"
#define DC_PHY_FIFO_ARB_12_reg                                                       0xB8008E30
#define set_DC_PHY_FIFO_ARB_12_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_12_reg)=data)
#define get_DC_PHY_FIFO_ARB_12_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_12_reg))
#define DC_PHY_FIFO_ARB_12_inst_adr                                                  "0x008C"
#define DC_PHY_FIFO_ARB_12_inst                                                      0x008C
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_rd_ptr_shift                                   (24)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_rd_ptr_mask                                    (0x1F000000)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_rd_ptr(data)                                   (0x1F000000&((data)<<24))
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_rd_ptr_src(data)                               ((0x1F000000&(data))>>24)
#define DC_PHY_FIFO_ARB_12_get_wq_ch_fifo_rd_ptr(data)                               ((0x1F000000&(data))>>24)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_wr_ptr_shift                                   (16)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_wr_ptr_mask                                    (0x001F0000)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_wr_ptr(data)                                   (0x001F0000&((data)<<16))
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_wr_ptr_src(data)                               ((0x001F0000&(data))>>16)
#define DC_PHY_FIFO_ARB_12_get_wq_ch_fifo_wr_ptr(data)                               ((0x001F0000&(data))>>16)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_overflow_shift                                 (15)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_overflow_mask                                  (0x00008000)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_overflow(data)                                 (0x00008000&((data)<<15))
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_overflow_src(data)                             ((0x00008000&(data))>>15)
#define DC_PHY_FIFO_ARB_12_get_wq_ch_fifo_overflow(data)                             ((0x00008000&(data))>>15)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_underflow_shift                                (14)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_underflow_mask                                 (0x00004000)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_underflow(data)                                (0x00004000&((data)<<14))
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_underflow_src(data)                            ((0x00004000&(data))>>14)
#define DC_PHY_FIFO_ARB_12_get_wq_ch_fifo_underflow(data)                            ((0x00004000&(data))>>14)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_full_shift                                     (13)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_full_mask                                      (0x00002000)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_full(data)                                     (0x00002000&((data)<<13))
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_full_src(data)                                 ((0x00002000&(data))>>13)
#define DC_PHY_FIFO_ARB_12_get_wq_ch_fifo_full(data)                                 ((0x00002000&(data))>>13)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_empty_shift                                    (12)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_empty_mask                                     (0x00001000)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_empty(data)                                    (0x00001000&((data)<<12))
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_empty_src(data)                                ((0x00001000&(data))>>12)
#define DC_PHY_FIFO_ARB_12_get_wq_ch_fifo_empty(data)                                ((0x00001000&(data))>>12)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_thr_shift                                      (4)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_thr_mask                                       (0x000003F0)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_thr(data)                                      (0x000003F0&((data)<<4))
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_thr_src(data)                                  ((0x000003F0&(data))>>4)
#define DC_PHY_FIFO_ARB_12_get_wq_ch_fifo_thr(data)                                  ((0x000003F0&(data))>>4)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_overflow_clr_shift                             (3)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_overflow_clr_mask                              (0x00000008)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_overflow_clr(data)                             (0x00000008&((data)<<3))
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_overflow_clr_src(data)                         ((0x00000008&(data))>>3)
#define DC_PHY_FIFO_ARB_12_get_wq_ch_fifo_overflow_clr(data)                         ((0x00000008&(data))>>3)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_underflow_clr_shift                            (2)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_underflow_clr_mask                             (0x00000004)
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_underflow_clr(data)                            (0x00000004&((data)<<2))
#define DC_PHY_FIFO_ARB_12_wq_ch_fifo_underflow_clr_src(data)                        ((0x00000004&(data))>>2)
#define DC_PHY_FIFO_ARB_12_get_wq_ch_fifo_underflow_clr(data)                        ((0x00000004&(data))>>2)
#define DC_PHY_FIFO_ARB_12_wq_ch_clk_gated_en_shift                                  (1)
#define DC_PHY_FIFO_ARB_12_wq_ch_clk_gated_en_mask                                   (0x00000002)
#define DC_PHY_FIFO_ARB_12_wq_ch_clk_gated_en(data)                                  (0x00000002&((data)<<1))
#define DC_PHY_FIFO_ARB_12_wq_ch_clk_gated_en_src(data)                              ((0x00000002&(data))>>1)
#define DC_PHY_FIFO_ARB_12_get_wq_ch_clk_gated_en(data)                              ((0x00000002&(data))>>1)


#define DC_PHY_FIFO_ARB_13                                                           0x18008e34
#define DC_PHY_FIFO_ARB_13_reg_addr                                                  "0xB8008E34"
#define DC_PHY_FIFO_ARB_13_reg                                                       0xB8008E34
#define set_DC_PHY_FIFO_ARB_13_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_13_reg)=data)
#define get_DC_PHY_FIFO_ARB_13_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_13_reg))
#define DC_PHY_FIFO_ARB_13_inst_adr                                                  "0x008D"
#define DC_PHY_FIFO_ARB_13_inst                                                      0x008D
#define DC_PHY_FIFO_ARB_13_wq_ch_dbg_mod_shift                                       (8)
#define DC_PHY_FIFO_ARB_13_wq_ch_dbg_mod_mask                                        (0x0000FF00)
#define DC_PHY_FIFO_ARB_13_wq_ch_dbg_mod(data)                                       (0x0000FF00&((data)<<8))
#define DC_PHY_FIFO_ARB_13_wq_ch_dbg_mod_src(data)                                   ((0x0000FF00&(data))>>8)
#define DC_PHY_FIFO_ARB_13_get_wq_ch_dbg_mod(data)                                   ((0x0000FF00&(data))>>8)
#define DC_PHY_FIFO_ARB_13_wq_ch_fifo_cnt_shift                                      (0)
#define DC_PHY_FIFO_ARB_13_wq_ch_fifo_cnt_mask                                       (0x0000003F)
#define DC_PHY_FIFO_ARB_13_wq_ch_fifo_cnt(data)                                      (0x0000003F&((data)<<0))
#define DC_PHY_FIFO_ARB_13_wq_ch_fifo_cnt_src(data)                                  ((0x0000003F&(data))>>0)
#define DC_PHY_FIFO_ARB_13_get_wq_ch_fifo_cnt(data)                                  ((0x0000003F&(data))>>0)


#define DC_PHY_FIFO_ARB_14                                                           0x18008e38
#define DC_PHY_FIFO_ARB_14_reg_addr                                                  "0xB8008E38"
#define DC_PHY_FIFO_ARB_14_reg                                                       0xB8008E38
#define set_DC_PHY_FIFO_ARB_14_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_14_reg)=data)
#define get_DC_PHY_FIFO_ARB_14_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_14_reg))
#define DC_PHY_FIFO_ARB_14_inst_adr                                                  "0x008E"
#define DC_PHY_FIFO_ARB_14_inst                                                      0x008E
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_rd_ptr_shift                               (24)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_rd_ptr_mask                                (0x1F000000)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_rd_ptr(data)                               (0x1F000000&((data)<<24))
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_rd_ptr_src(data)                           ((0x1F000000&(data))>>24)
#define DC_PHY_FIFO_ARB_14_get_wq_ch_fifo_par_rd_ptr(data)                           ((0x1F000000&(data))>>24)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_wr_ptr_shift                               (16)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_wr_ptr_mask                                (0x001F0000)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_wr_ptr(data)                               (0x001F0000&((data)<<16))
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_wr_ptr_src(data)                           ((0x001F0000&(data))>>16)
#define DC_PHY_FIFO_ARB_14_get_wq_ch_fifo_par_wr_ptr(data)                           ((0x001F0000&(data))>>16)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_overflow_shift                             (15)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_overflow_mask                              (0x00008000)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_overflow(data)                             (0x00008000&((data)<<15))
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_overflow_src(data)                         ((0x00008000&(data))>>15)
#define DC_PHY_FIFO_ARB_14_get_wq_ch_fifo_par_overflow(data)                         ((0x00008000&(data))>>15)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_underflow_shift                            (14)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_underflow_mask                             (0x00004000)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_underflow(data)                            (0x00004000&((data)<<14))
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_underflow_src(data)                        ((0x00004000&(data))>>14)
#define DC_PHY_FIFO_ARB_14_get_wq_ch_fifo_par_underflow(data)                        ((0x00004000&(data))>>14)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_full_shift                                 (13)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_full_mask                                  (0x00002000)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_full(data)                                 (0x00002000&((data)<<13))
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_full_src(data)                             ((0x00002000&(data))>>13)
#define DC_PHY_FIFO_ARB_14_get_wq_ch_fifo_par_full(data)                             ((0x00002000&(data))>>13)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_empty_shift                                (12)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_empty_mask                                 (0x00001000)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_empty(data)                                (0x00001000&((data)<<12))
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_empty_src(data)                            ((0x00001000&(data))>>12)
#define DC_PHY_FIFO_ARB_14_get_wq_ch_fifo_par_empty(data)                            ((0x00001000&(data))>>12)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_thr_shift                                  (4)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_thr_mask                                   (0x000003F0)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_thr(data)                                  (0x000003F0&((data)<<4))
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_thr_src(data)                              ((0x000003F0&(data))>>4)
#define DC_PHY_FIFO_ARB_14_get_wq_ch_fifo_par_thr(data)                              ((0x000003F0&(data))>>4)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_overflow_clr_shift                         (3)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_overflow_clr_mask                          (0x00000008)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_overflow_clr(data)                         (0x00000008&((data)<<3))
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_overflow_clr_src(data)                     ((0x00000008&(data))>>3)
#define DC_PHY_FIFO_ARB_14_get_wq_ch_fifo_par_overflow_clr(data)                     ((0x00000008&(data))>>3)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_underflow_clr_shift                        (2)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_underflow_clr_mask                         (0x00000004)
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_underflow_clr(data)                        (0x00000004&((data)<<2))
#define DC_PHY_FIFO_ARB_14_wq_ch_fifo_par_underflow_clr_src(data)                    ((0x00000004&(data))>>2)
#define DC_PHY_FIFO_ARB_14_get_wq_ch_fifo_par_underflow_clr(data)                    ((0x00000004&(data))>>2)


#define DC_PHY_FIFO_ARB_15                                                           0x18008e3c
#define DC_PHY_FIFO_ARB_15_reg_addr                                                  "0xB8008E3C"
#define DC_PHY_FIFO_ARB_15_reg                                                       0xB8008E3C
#define set_DC_PHY_FIFO_ARB_15_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_15_reg)=data)
#define get_DC_PHY_FIFO_ARB_15_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_15_reg))
#define DC_PHY_FIFO_ARB_15_inst_adr                                                  "0x008F"
#define DC_PHY_FIFO_ARB_15_inst                                                      0x008F
#define DC_PHY_FIFO_ARB_15_wq_ch_fifo_par_cnt_shift                                  (0)
#define DC_PHY_FIFO_ARB_15_wq_ch_fifo_par_cnt_mask                                   (0x0000003F)
#define DC_PHY_FIFO_ARB_15_wq_ch_fifo_par_cnt(data)                                  (0x0000003F&((data)<<0))
#define DC_PHY_FIFO_ARB_15_wq_ch_fifo_par_cnt_src(data)                              ((0x0000003F&(data))>>0)
#define DC_PHY_FIFO_ARB_15_get_wq_ch_fifo_par_cnt(data)                              ((0x0000003F&(data))>>0)


#define DC_PHY_FIFO_ARB_16                                                           0x18008e40
#define DC_PHY_FIFO_ARB_16_reg_addr                                                  "0xB8008E40"
#define DC_PHY_FIFO_ARB_16_reg                                                       0xB8008E40
#define set_DC_PHY_FIFO_ARB_16_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_16_reg)=data)
#define get_DC_PHY_FIFO_ARB_16_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_16_reg))
#define DC_PHY_FIFO_ARB_16_inst_adr                                                  "0x0090"
#define DC_PHY_FIFO_ARB_16_inst                                                      0x0090
#define DC_PHY_FIFO_ARB_16_wq_ch_dummy_0_shift                                       (0)
#define DC_PHY_FIFO_ARB_16_wq_ch_dummy_0_mask                                        (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_16_wq_ch_dummy_0(data)                                       (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_16_wq_ch_dummy_0_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_16_get_wq_ch_dummy_0(data)                                   ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_17                                                           0x18008e44
#define DC_PHY_FIFO_ARB_17_reg_addr                                                  "0xB8008E44"
#define DC_PHY_FIFO_ARB_17_reg                                                       0xB8008E44
#define set_DC_PHY_FIFO_ARB_17_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_17_reg)=data)
#define get_DC_PHY_FIFO_ARB_17_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_17_reg))
#define DC_PHY_FIFO_ARB_17_inst_adr                                                  "0x0091"
#define DC_PHY_FIFO_ARB_17_inst                                                      0x0091
#define DC_PHY_FIFO_ARB_17_wq_ch_st0_shift                                           (0)
#define DC_PHY_FIFO_ARB_17_wq_ch_st0_mask                                            (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_17_wq_ch_st0(data)                                           (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_17_wq_ch_st0_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_17_get_wq_ch_st0(data)                                       ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_18                                                           0x18008e48
#define DC_PHY_FIFO_ARB_18_reg_addr                                                  "0xB8008E48"
#define DC_PHY_FIFO_ARB_18_reg                                                       0xB8008E48
#define set_DC_PHY_FIFO_ARB_18_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_18_reg)=data)
#define get_DC_PHY_FIFO_ARB_18_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_18_reg))
#define DC_PHY_FIFO_ARB_18_inst_adr                                                  "0x0092"
#define DC_PHY_FIFO_ARB_18_inst                                                      0x0092
#define DC_PHY_FIFO_ARB_18_wq_ch_st1_shift                                           (0)
#define DC_PHY_FIFO_ARB_18_wq_ch_st1_mask                                            (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_18_wq_ch_st1(data)                                           (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_18_wq_ch_st1_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_18_get_wq_ch_st1(data)                                       ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_19                                                           0x18008e4c
#define DC_PHY_FIFO_ARB_19_reg_addr                                                  "0xB8008E4C"
#define DC_PHY_FIFO_ARB_19_reg                                                       0xB8008E4C
#define set_DC_PHY_FIFO_ARB_19_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_19_reg)=data)
#define get_DC_PHY_FIFO_ARB_19_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_19_reg))
#define DC_PHY_FIFO_ARB_19_inst_adr                                                  "0x0093"
#define DC_PHY_FIFO_ARB_19_inst                                                      0x0093
#define DC_PHY_FIFO_ARB_19_wq_ch_st2_shift                                           (0)
#define DC_PHY_FIFO_ARB_19_wq_ch_st2_mask                                            (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_19_wq_ch_st2(data)                                           (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_19_wq_ch_st2_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_19_get_wq_ch_st2(data)                                       ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_20                                                           0x18008e50
#define DC_PHY_FIFO_ARB_20_reg_addr                                                  "0xB8008E50"
#define DC_PHY_FIFO_ARB_20_reg                                                       0xB8008E50
#define set_DC_PHY_FIFO_ARB_20_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_20_reg)=data)
#define get_DC_PHY_FIFO_ARB_20_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_20_reg))
#define DC_PHY_FIFO_ARB_20_inst_adr                                                  "0x0094"
#define DC_PHY_FIFO_ARB_20_inst                                                      0x0094
#define DC_PHY_FIFO_ARB_20_wq_ch_st3_shift                                           (0)
#define DC_PHY_FIFO_ARB_20_wq_ch_st3_mask                                            (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_20_wq_ch_st3(data)                                           (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_20_wq_ch_st3_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_20_get_wq_ch_st3(data)                                       ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_21                                                           0x18008e54
#define DC_PHY_FIFO_ARB_21_reg_addr                                                  "0xB8008E54"
#define DC_PHY_FIFO_ARB_21_reg                                                       0xB8008E54
#define set_DC_PHY_FIFO_ARB_21_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_21_reg)=data)
#define get_DC_PHY_FIFO_ARB_21_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_21_reg))
#define DC_PHY_FIFO_ARB_21_inst_adr                                                  "0x0095"
#define DC_PHY_FIFO_ARB_21_inst                                                      0x0095
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_rd_ptr_shift                                   (24)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_rd_ptr_mask                                    (0x0F000000)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_rd_ptr(data)                                   (0x0F000000&((data)<<24))
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_rd_ptr_src(data)                               ((0x0F000000&(data))>>24)
#define DC_PHY_FIFO_ARB_21_get_rq_ch_fifo_rd_ptr(data)                               ((0x0F000000&(data))>>24)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_wr_ptr_shift                                   (16)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_wr_ptr_mask                                    (0x000F0000)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_wr_ptr(data)                                   (0x000F0000&((data)<<16))
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_wr_ptr_src(data)                               ((0x000F0000&(data))>>16)
#define DC_PHY_FIFO_ARB_21_get_rq_ch_fifo_wr_ptr(data)                               ((0x000F0000&(data))>>16)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_overflow_shift                                 (15)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_overflow_mask                                  (0x00008000)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_overflow(data)                                 (0x00008000&((data)<<15))
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_overflow_src(data)                             ((0x00008000&(data))>>15)
#define DC_PHY_FIFO_ARB_21_get_rq_ch_fifo_overflow(data)                             ((0x00008000&(data))>>15)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_underflow_shift                                (14)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_underflow_mask                                 (0x00004000)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_underflow(data)                                (0x00004000&((data)<<14))
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_underflow_src(data)                            ((0x00004000&(data))>>14)
#define DC_PHY_FIFO_ARB_21_get_rq_ch_fifo_underflow(data)                            ((0x00004000&(data))>>14)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_full_shift                                     (13)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_full_mask                                      (0x00002000)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_full(data)                                     (0x00002000&((data)<<13))
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_full_src(data)                                 ((0x00002000&(data))>>13)
#define DC_PHY_FIFO_ARB_21_get_rq_ch_fifo_full(data)                                 ((0x00002000&(data))>>13)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_empty_shift                                    (12)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_empty_mask                                     (0x00001000)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_empty(data)                                    (0x00001000&((data)<<12))
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_empty_src(data)                                ((0x00001000&(data))>>12)
#define DC_PHY_FIFO_ARB_21_get_rq_ch_fifo_empty(data)                                ((0x00001000&(data))>>12)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_thr_shift                                      (4)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_thr_mask                                       (0x000001F0)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_thr(data)                                      (0x000001F0&((data)<<4))
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_thr_src(data)                                  ((0x000001F0&(data))>>4)
#define DC_PHY_FIFO_ARB_21_get_rq_ch_fifo_thr(data)                                  ((0x000001F0&(data))>>4)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_overflow_clr_shift                             (3)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_overflow_clr_mask                              (0x00000008)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_overflow_clr(data)                             (0x00000008&((data)<<3))
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_overflow_clr_src(data)                         ((0x00000008&(data))>>3)
#define DC_PHY_FIFO_ARB_21_get_rq_ch_fifo_overflow_clr(data)                         ((0x00000008&(data))>>3)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_underflow_clr_shift                            (2)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_underflow_clr_mask                             (0x00000004)
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_underflow_clr(data)                            (0x00000004&((data)<<2))
#define DC_PHY_FIFO_ARB_21_rq_ch_fifo_underflow_clr_src(data)                        ((0x00000004&(data))>>2)
#define DC_PHY_FIFO_ARB_21_get_rq_ch_fifo_underflow_clr(data)                        ((0x00000004&(data))>>2)
#define DC_PHY_FIFO_ARB_21_rq_ch_clk_gated_en_shift                                  (1)
#define DC_PHY_FIFO_ARB_21_rq_ch_clk_gated_en_mask                                   (0x00000002)
#define DC_PHY_FIFO_ARB_21_rq_ch_clk_gated_en(data)                                  (0x00000002&((data)<<1))
#define DC_PHY_FIFO_ARB_21_rq_ch_clk_gated_en_src(data)                              ((0x00000002&(data))>>1)
#define DC_PHY_FIFO_ARB_21_get_rq_ch_clk_gated_en(data)                              ((0x00000002&(data))>>1)


#define DC_PHY_FIFO_ARB_22                                                           0x18008e58
#define DC_PHY_FIFO_ARB_22_reg_addr                                                  "0xB8008E58"
#define DC_PHY_FIFO_ARB_22_reg                                                       0xB8008E58
#define set_DC_PHY_FIFO_ARB_22_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_22_reg)=data)
#define get_DC_PHY_FIFO_ARB_22_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_22_reg))
#define DC_PHY_FIFO_ARB_22_inst_adr                                                  "0x0096"
#define DC_PHY_FIFO_ARB_22_inst                                                      0x0096
#define DC_PHY_FIFO_ARB_22_rq_ch_fifo_cnt_shift                                      (0)
#define DC_PHY_FIFO_ARB_22_rq_ch_fifo_cnt_mask                                       (0x0000001F)
#define DC_PHY_FIFO_ARB_22_rq_ch_fifo_cnt(data)                                      (0x0000001F&((data)<<0))
#define DC_PHY_FIFO_ARB_22_rq_ch_fifo_cnt_src(data)                                  ((0x0000001F&(data))>>0)
#define DC_PHY_FIFO_ARB_22_get_rq_ch_fifo_cnt(data)                                  ((0x0000001F&(data))>>0)


#define DC_PHY_FIFO_ARB_23                                                           0x18008e5c
#define DC_PHY_FIFO_ARB_23_reg_addr                                                  "0xB8008E5C"
#define DC_PHY_FIFO_ARB_23_reg                                                       0xB8008E5C
#define set_DC_PHY_FIFO_ARB_23_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_23_reg)=data)
#define get_DC_PHY_FIFO_ARB_23_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_23_reg))
#define DC_PHY_FIFO_ARB_23_inst_adr                                                  "0x0097"
#define DC_PHY_FIFO_ARB_23_inst                                                      0x0097
#define DC_PHY_FIFO_ARB_23_wcol_adr_q_thr_shift                                      (8)
#define DC_PHY_FIFO_ARB_23_wcol_adr_q_thr_mask                                       (0x00001F00)
#define DC_PHY_FIFO_ARB_23_wcol_adr_q_thr(data)                                      (0x00001F00&((data)<<8))
#define DC_PHY_FIFO_ARB_23_wcol_adr_q_thr_src(data)                                  ((0x00001F00&(data))>>8)
#define DC_PHY_FIFO_ARB_23_get_wcol_adr_q_thr(data)                                  ((0x00001F00&(data))>>8)
#define DC_PHY_FIFO_ARB_23_rq_ch_dbg_mod_shift                                       (0)
#define DC_PHY_FIFO_ARB_23_rq_ch_dbg_mod_mask                                        (0x000000FF)
#define DC_PHY_FIFO_ARB_23_rq_ch_dbg_mod(data)                                       (0x000000FF&((data)<<0))
#define DC_PHY_FIFO_ARB_23_rq_ch_dbg_mod_src(data)                                   ((0x000000FF&(data))>>0)
#define DC_PHY_FIFO_ARB_23_get_rq_ch_dbg_mod(data)                                   ((0x000000FF&(data))>>0)


#define DC_PHY_FIFO_ARB_24                                                           0x18008e60
#define DC_PHY_FIFO_ARB_24_reg_addr                                                  "0xB8008E60"
#define DC_PHY_FIFO_ARB_24_reg                                                       0xB8008E60
#define set_DC_PHY_FIFO_ARB_24_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_24_reg)=data)
#define get_DC_PHY_FIFO_ARB_24_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_24_reg))
#define DC_PHY_FIFO_ARB_24_inst_adr                                                  "0x0098"
#define DC_PHY_FIFO_ARB_24_inst                                                      0x0098
#define DC_PHY_FIFO_ARB_24_rq_ch_dummy_0_shift                                       (0)
#define DC_PHY_FIFO_ARB_24_rq_ch_dummy_0_mask                                        (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_24_rq_ch_dummy_0(data)                                       (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_24_rq_ch_dummy_0_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_24_get_rq_ch_dummy_0(data)                                   ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_25                                                           0x18008e64
#define DC_PHY_FIFO_ARB_25_reg_addr                                                  "0xB8008E64"
#define DC_PHY_FIFO_ARB_25_reg                                                       0xB8008E64
#define set_DC_PHY_FIFO_ARB_25_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_25_reg)=data)
#define get_DC_PHY_FIFO_ARB_25_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_25_reg))
#define DC_PHY_FIFO_ARB_25_inst_adr                                                  "0x0099"
#define DC_PHY_FIFO_ARB_25_inst                                                      0x0099
#define DC_PHY_FIFO_ARB_25_rq_ch_st0_shift                                           (0)
#define DC_PHY_FIFO_ARB_25_rq_ch_st0_mask                                            (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_25_rq_ch_st0(data)                                           (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_25_rq_ch_st0_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_25_get_rq_ch_st0(data)                                       ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_26                                                           0x18008e68
#define DC_PHY_FIFO_ARB_26_reg_addr                                                  "0xB8008E68"
#define DC_PHY_FIFO_ARB_26_reg                                                       0xB8008E68
#define set_DC_PHY_FIFO_ARB_26_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_26_reg)=data)
#define get_DC_PHY_FIFO_ARB_26_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_26_reg))
#define DC_PHY_FIFO_ARB_26_inst_adr                                                  "0x009A"
#define DC_PHY_FIFO_ARB_26_inst                                                      0x009A
#define DC_PHY_FIFO_ARB_26_rq_ch_st1_shift                                           (0)
#define DC_PHY_FIFO_ARB_26_rq_ch_st1_mask                                            (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_26_rq_ch_st1(data)                                           (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_26_rq_ch_st1_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_26_get_rq_ch_st1(data)                                       ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_27                                                           0x18008e6c
#define DC_PHY_FIFO_ARB_27_reg_addr                                                  "0xB8008E6C"
#define DC_PHY_FIFO_ARB_27_reg                                                       0xB8008E6C
#define set_DC_PHY_FIFO_ARB_27_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_27_reg)=data)
#define get_DC_PHY_FIFO_ARB_27_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_27_reg))
#define DC_PHY_FIFO_ARB_27_inst_adr                                                  "0x009B"
#define DC_PHY_FIFO_ARB_27_inst                                                      0x009B
#define DC_PHY_FIFO_ARB_27_rq_ch_st2_shift                                           (0)
#define DC_PHY_FIFO_ARB_27_rq_ch_st2_mask                                            (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_27_rq_ch_st2(data)                                           (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_27_rq_ch_st2_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_27_get_rq_ch_st2(data)                                       ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_FIFO_ARB_28                                                           0x18008e70
#define DC_PHY_FIFO_ARB_28_reg_addr                                                  "0xB8008E70"
#define DC_PHY_FIFO_ARB_28_reg                                                       0xB8008E70
#define set_DC_PHY_FIFO_ARB_28_reg(data)   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_28_reg)=data)
#define get_DC_PHY_FIFO_ARB_28_reg   (*((volatile unsigned int*) DC_PHY_FIFO_ARB_28_reg))
#define DC_PHY_FIFO_ARB_28_inst_adr                                                  "0x009C"
#define DC_PHY_FIFO_ARB_28_inst                                                      0x009C
#define DC_PHY_FIFO_ARB_28_rq_ch_st3_shift                                           (0)
#define DC_PHY_FIFO_ARB_28_rq_ch_st3_mask                                            (0xFFFFFFFF)
#define DC_PHY_FIFO_ARB_28_rq_ch_st3(data)                                           (0xFFFFFFFF&((data)<<0))
#define DC_PHY_FIFO_ARB_28_rq_ch_st3_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_FIFO_ARB_28_get_rq_ch_st3(data)                                       ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DUMMY_0                                                               0x18008ee0
#define DC_PHY_DUMMY_0_reg_addr                                                      "0xB8008EE0"
#define DC_PHY_DUMMY_0_reg                                                           0xB8008EE0
#define set_DC_PHY_DUMMY_0_reg(data)   (*((volatile unsigned int*) DC_PHY_DUMMY_0_reg)=data)
#define get_DC_PHY_DUMMY_0_reg   (*((volatile unsigned int*) DC_PHY_DUMMY_0_reg))
#define DC_PHY_DUMMY_0_inst_adr                                                      "0x00B8"
#define DC_PHY_DUMMY_0_inst                                                          0x00B8
#define DC_PHY_DUMMY_0_dummy_0_shift                                                 (0)
#define DC_PHY_DUMMY_0_dummy_0_mask                                                  (0xFFFFFFFF)
#define DC_PHY_DUMMY_0_dummy_0(data)                                                 (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DUMMY_0_dummy_0_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DUMMY_0_get_dummy_0(data)                                             ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DUMMY_1                                                               0x18008ee4
#define DC_PHY_DUMMY_1_reg_addr                                                      "0xB8008EE4"
#define DC_PHY_DUMMY_1_reg                                                           0xB8008EE4
#define set_DC_PHY_DUMMY_1_reg(data)   (*((volatile unsigned int*) DC_PHY_DUMMY_1_reg)=data)
#define get_DC_PHY_DUMMY_1_reg   (*((volatile unsigned int*) DC_PHY_DUMMY_1_reg))
#define DC_PHY_DUMMY_1_inst_adr                                                      "0x00B9"
#define DC_PHY_DUMMY_1_inst                                                          0x00B9
#define DC_PHY_DUMMY_1_dummy_1_shift                                                 (0)
#define DC_PHY_DUMMY_1_dummy_1_mask                                                  (0xFFFFFFFF)
#define DC_PHY_DUMMY_1_dummy_1(data)                                                 (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DUMMY_1_dummy_1_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DUMMY_1_get_dummy_1(data)                                             ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DUMMY_2                                                               0x18008ee8
#define DC_PHY_DUMMY_2_reg_addr                                                      "0xB8008EE8"
#define DC_PHY_DUMMY_2_reg                                                           0xB8008EE8
#define set_DC_PHY_DUMMY_2_reg(data)   (*((volatile unsigned int*) DC_PHY_DUMMY_2_reg)=data)
#define get_DC_PHY_DUMMY_2_reg   (*((volatile unsigned int*) DC_PHY_DUMMY_2_reg))
#define DC_PHY_DUMMY_2_inst_adr                                                      "0x00BA"
#define DC_PHY_DUMMY_2_inst                                                          0x00BA
#define DC_PHY_DUMMY_2_dummy_2_shift                                                 (0)
#define DC_PHY_DUMMY_2_dummy_2_mask                                                  (0xFFFFFFFF)
#define DC_PHY_DUMMY_2_dummy_2(data)                                                 (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DUMMY_2_dummy_2_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DUMMY_2_get_dummy_2(data)                                             ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DUMMY_3                                                               0x18008eec
#define DC_PHY_DUMMY_3_reg_addr                                                      "0xB8008EEC"
#define DC_PHY_DUMMY_3_reg                                                           0xB8008EEC
#define set_DC_PHY_DUMMY_3_reg(data)   (*((volatile unsigned int*) DC_PHY_DUMMY_3_reg)=data)
#define get_DC_PHY_DUMMY_3_reg   (*((volatile unsigned int*) DC_PHY_DUMMY_3_reg))
#define DC_PHY_DUMMY_3_inst_adr                                                      "0x00BB"
#define DC_PHY_DUMMY_3_inst                                                          0x00BB
#define DC_PHY_DUMMY_3_dummy_3_shift                                                 (0)
#define DC_PHY_DUMMY_3_dummy_3_mask                                                  (0xFFFFFFFF)
#define DC_PHY_DUMMY_3_dummy_3(data)                                                 (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DUMMY_3_dummy_3_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DUMMY_3_get_dummy_3(data)                                             ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DUMMY_4                                                               0x18008ef0
#define DC_PHY_DUMMY_4_reg_addr                                                      "0xB8008EF0"
#define DC_PHY_DUMMY_4_reg                                                           0xB8008EF0
#define set_DC_PHY_DUMMY_4_reg(data)   (*((volatile unsigned int*) DC_PHY_DUMMY_4_reg)=data)
#define get_DC_PHY_DUMMY_4_reg   (*((volatile unsigned int*) DC_PHY_DUMMY_4_reg))
#define DC_PHY_DUMMY_4_inst_adr                                                      "0x00BC"
#define DC_PHY_DUMMY_4_inst                                                          0x00BC
#define DC_PHY_DUMMY_4_dummy_4_shift                                                 (0)
#define DC_PHY_DUMMY_4_dummy_4_mask                                                  (0xFFFFFFFF)
#define DC_PHY_DUMMY_4_dummy_4(data)                                                 (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DUMMY_4_dummy_4_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DUMMY_4_get_dummy_4(data)                                             ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DUMMY_5                                                               0x18008ef4
#define DC_PHY_DUMMY_5_reg_addr                                                      "0xB8008EF4"
#define DC_PHY_DUMMY_5_reg                                                           0xB8008EF4
#define set_DC_PHY_DUMMY_5_reg(data)   (*((volatile unsigned int*) DC_PHY_DUMMY_5_reg)=data)
#define get_DC_PHY_DUMMY_5_reg   (*((volatile unsigned int*) DC_PHY_DUMMY_5_reg))
#define DC_PHY_DUMMY_5_inst_adr                                                      "0x00BD"
#define DC_PHY_DUMMY_5_inst                                                          0x00BD
#define DC_PHY_DUMMY_5_dummy_5_shift                                                 (0)
#define DC_PHY_DUMMY_5_dummy_5_mask                                                  (0xFFFFFFFF)
#define DC_PHY_DUMMY_5_dummy_5(data)                                                 (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DUMMY_5_dummy_5_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DUMMY_5_get_dummy_5(data)                                             ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DUMMY_6                                                               0x18008ef8
#define DC_PHY_DUMMY_6_reg_addr                                                      "0xB8008EF8"
#define DC_PHY_DUMMY_6_reg                                                           0xB8008EF8
#define set_DC_PHY_DUMMY_6_reg(data)   (*((volatile unsigned int*) DC_PHY_DUMMY_6_reg)=data)
#define get_DC_PHY_DUMMY_6_reg   (*((volatile unsigned int*) DC_PHY_DUMMY_6_reg))
#define DC_PHY_DUMMY_6_inst_adr                                                      "0x00BE"
#define DC_PHY_DUMMY_6_inst                                                          0x00BE
#define DC_PHY_DUMMY_6_dummy_6_shift                                                 (0)
#define DC_PHY_DUMMY_6_dummy_6_mask                                                  (0xFFFFFFFF)
#define DC_PHY_DUMMY_6_dummy_6(data)                                                 (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DUMMY_6_dummy_6_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DUMMY_6_get_dummy_6(data)                                             ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DUMMY_7                                                               0x18008efc
#define DC_PHY_DUMMY_7_reg_addr                                                      "0xB8008EFC"
#define DC_PHY_DUMMY_7_reg                                                           0xB8008EFC
#define set_DC_PHY_DUMMY_7_reg(data)   (*((volatile unsigned int*) DC_PHY_DUMMY_7_reg)=data)
#define get_DC_PHY_DUMMY_7_reg   (*((volatile unsigned int*) DC_PHY_DUMMY_7_reg))
#define DC_PHY_DUMMY_7_inst_adr                                                      "0x00BF"
#define DC_PHY_DUMMY_7_inst                                                          0x00BF
#define DC_PHY_DUMMY_7_dummy_7_shift                                                 (0)
#define DC_PHY_DUMMY_7_dummy_7_mask                                                  (0xFFFFFFFF)
#define DC_PHY_DUMMY_7_dummy_7(data)                                                 (0xFFFFFFFF&((data)<<0))
#define DC_PHY_DUMMY_7_dummy_7_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_DUMMY_7_get_dummy_7(data)                                             ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_SC_CTRL                                                               0x18008f60
#define DC_PHY_SC_CTRL_reg_addr                                                      "0xB8008F60"
#define DC_PHY_SC_CTRL_reg                                                           0xB8008F60
#define set_DC_PHY_SC_CTRL_reg(data)   (*((volatile unsigned int*) DC_PHY_SC_CTRL_reg)=data)
#define get_DC_PHY_SC_CTRL_reg   (*((volatile unsigned int*) DC_PHY_SC_CTRL_reg))
#define DC_PHY_SC_CTRL_inst_adr                                                      "0x00D8"
#define DC_PHY_SC_CTRL_inst                                                          0x00D8
#define DC_PHY_SC_CTRL_sc_en_shift                                                   (0)
#define DC_PHY_SC_CTRL_sc_en_mask                                                    (0x00000001)
#define DC_PHY_SC_CTRL_sc_en(data)                                                   (0x00000001&((data)<<0))
#define DC_PHY_SC_CTRL_sc_en_src(data)                                               ((0x00000001&(data))>>0)
#define DC_PHY_SC_CTRL_get_sc_en(data)                                               ((0x00000001&(data))>>0)


#define DC_PHY_SC_KEY01                                                              0x18008f64
#define DC_PHY_SC_KEY01_reg_addr                                                     "0xB8008F64"
#define DC_PHY_SC_KEY01_reg                                                          0xB8008F64
#define set_DC_PHY_SC_KEY01_reg(data)   (*((volatile unsigned int*) DC_PHY_SC_KEY01_reg)=data)
#define get_DC_PHY_SC_KEY01_reg   (*((volatile unsigned int*) DC_PHY_SC_KEY01_reg))
#define DC_PHY_SC_KEY01_inst_adr                                                     "0x00D9"
#define DC_PHY_SC_KEY01_inst                                                         0x00D9
#define DC_PHY_SC_KEY01_sc_key_1_shift                                               (16)
#define DC_PHY_SC_KEY01_sc_key_1_mask                                                (0xFFFF0000)
#define DC_PHY_SC_KEY01_sc_key_1(data)                                               (0xFFFF0000&((data)<<16))
#define DC_PHY_SC_KEY01_sc_key_1_src(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEY01_get_sc_key_1(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEY01_sc_key_0_shift                                               (0)
#define DC_PHY_SC_KEY01_sc_key_0_mask                                                (0x0000FFFF)
#define DC_PHY_SC_KEY01_sc_key_0(data)                                               (0x0000FFFF&((data)<<0))
#define DC_PHY_SC_KEY01_sc_key_0_src(data)                                           ((0x0000FFFF&(data))>>0)
#define DC_PHY_SC_KEY01_get_sc_key_0(data)                                           ((0x0000FFFF&(data))>>0)


#define DC_PHY_SC_KEY23                                                              0x18008f68
#define DC_PHY_SC_KEY23_reg_addr                                                     "0xB8008F68"
#define DC_PHY_SC_KEY23_reg                                                          0xB8008F68
#define set_DC_PHY_SC_KEY23_reg(data)   (*((volatile unsigned int*) DC_PHY_SC_KEY23_reg)=data)
#define get_DC_PHY_SC_KEY23_reg   (*((volatile unsigned int*) DC_PHY_SC_KEY23_reg))
#define DC_PHY_SC_KEY23_inst_adr                                                     "0x00DA"
#define DC_PHY_SC_KEY23_inst                                                         0x00DA
#define DC_PHY_SC_KEY23_sc_key_3_shift                                               (16)
#define DC_PHY_SC_KEY23_sc_key_3_mask                                                (0xFFFF0000)
#define DC_PHY_SC_KEY23_sc_key_3(data)                                               (0xFFFF0000&((data)<<16))
#define DC_PHY_SC_KEY23_sc_key_3_src(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEY23_get_sc_key_3(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEY23_sc_key_2_shift                                               (0)
#define DC_PHY_SC_KEY23_sc_key_2_mask                                                (0x0000FFFF)
#define DC_PHY_SC_KEY23_sc_key_2(data)                                               (0x0000FFFF&((data)<<0))
#define DC_PHY_SC_KEY23_sc_key_2_src(data)                                           ((0x0000FFFF&(data))>>0)
#define DC_PHY_SC_KEY23_get_sc_key_2(data)                                           ((0x0000FFFF&(data))>>0)


#define DC_PHY_SC_KEY45                                                              0x18008f6c
#define DC_PHY_SC_KEY45_reg_addr                                                     "0xB8008F6C"
#define DC_PHY_SC_KEY45_reg                                                          0xB8008F6C
#define set_DC_PHY_SC_KEY45_reg(data)   (*((volatile unsigned int*) DC_PHY_SC_KEY45_reg)=data)
#define get_DC_PHY_SC_KEY45_reg   (*((volatile unsigned int*) DC_PHY_SC_KEY45_reg))
#define DC_PHY_SC_KEY45_inst_adr                                                     "0x00DB"
#define DC_PHY_SC_KEY45_inst                                                         0x00DB
#define DC_PHY_SC_KEY45_sc_key_5_shift                                               (16)
#define DC_PHY_SC_KEY45_sc_key_5_mask                                                (0xFFFF0000)
#define DC_PHY_SC_KEY45_sc_key_5(data)                                               (0xFFFF0000&((data)<<16))
#define DC_PHY_SC_KEY45_sc_key_5_src(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEY45_get_sc_key_5(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEY45_sc_key_4_shift                                               (0)
#define DC_PHY_SC_KEY45_sc_key_4_mask                                                (0x0000FFFF)
#define DC_PHY_SC_KEY45_sc_key_4(data)                                               (0x0000FFFF&((data)<<0))
#define DC_PHY_SC_KEY45_sc_key_4_src(data)                                           ((0x0000FFFF&(data))>>0)
#define DC_PHY_SC_KEY45_get_sc_key_4(data)                                           ((0x0000FFFF&(data))>>0)


#define DC_PHY_SC_KEY67                                                              0x18008f70
#define DC_PHY_SC_KEY67_reg_addr                                                     "0xB8008F70"
#define DC_PHY_SC_KEY67_reg                                                          0xB8008F70
#define set_DC_PHY_SC_KEY67_reg(data)   (*((volatile unsigned int*) DC_PHY_SC_KEY67_reg)=data)
#define get_DC_PHY_SC_KEY67_reg   (*((volatile unsigned int*) DC_PHY_SC_KEY67_reg))
#define DC_PHY_SC_KEY67_inst_adr                                                     "0x00DC"
#define DC_PHY_SC_KEY67_inst                                                         0x00DC
#define DC_PHY_SC_KEY67_sc_key_7_shift                                               (16)
#define DC_PHY_SC_KEY67_sc_key_7_mask                                                (0xFFFF0000)
#define DC_PHY_SC_KEY67_sc_key_7(data)                                               (0xFFFF0000&((data)<<16))
#define DC_PHY_SC_KEY67_sc_key_7_src(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEY67_get_sc_key_7(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEY67_sc_key_6_shift                                               (0)
#define DC_PHY_SC_KEY67_sc_key_6_mask                                                (0x0000FFFF)
#define DC_PHY_SC_KEY67_sc_key_6(data)                                               (0x0000FFFF&((data)<<0))
#define DC_PHY_SC_KEY67_sc_key_6_src(data)                                           ((0x0000FFFF&(data))>>0)
#define DC_PHY_SC_KEY67_get_sc_key_6(data)                                           ((0x0000FFFF&(data))>>0)


#define DC_PHY_SC_KEY89                                                              0x18008f74
#define DC_PHY_SC_KEY89_reg_addr                                                     "0xB8008F74"
#define DC_PHY_SC_KEY89_reg                                                          0xB8008F74
#define set_DC_PHY_SC_KEY89_reg(data)   (*((volatile unsigned int*) DC_PHY_SC_KEY89_reg)=data)
#define get_DC_PHY_SC_KEY89_reg   (*((volatile unsigned int*) DC_PHY_SC_KEY89_reg))
#define DC_PHY_SC_KEY89_inst_adr                                                     "0x00DD"
#define DC_PHY_SC_KEY89_inst                                                         0x00DD
#define DC_PHY_SC_KEY89_sc_key_9_shift                                               (16)
#define DC_PHY_SC_KEY89_sc_key_9_mask                                                (0xFFFF0000)
#define DC_PHY_SC_KEY89_sc_key_9(data)                                               (0xFFFF0000&((data)<<16))
#define DC_PHY_SC_KEY89_sc_key_9_src(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEY89_get_sc_key_9(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEY89_sc_key_8_shift                                               (0)
#define DC_PHY_SC_KEY89_sc_key_8_mask                                                (0x0000FFFF)
#define DC_PHY_SC_KEY89_sc_key_8(data)                                               (0x0000FFFF&((data)<<0))
#define DC_PHY_SC_KEY89_sc_key_8_src(data)                                           ((0x0000FFFF&(data))>>0)
#define DC_PHY_SC_KEY89_get_sc_key_8(data)                                           ((0x0000FFFF&(data))>>0)


#define DC_PHY_SC_KEYAB                                                              0x18008f78
#define DC_PHY_SC_KEYAB_reg_addr                                                     "0xB8008F78"
#define DC_PHY_SC_KEYAB_reg                                                          0xB8008F78
#define set_DC_PHY_SC_KEYAB_reg(data)   (*((volatile unsigned int*) DC_PHY_SC_KEYAB_reg)=data)
#define get_DC_PHY_SC_KEYAB_reg   (*((volatile unsigned int*) DC_PHY_SC_KEYAB_reg))
#define DC_PHY_SC_KEYAB_inst_adr                                                     "0x00DE"
#define DC_PHY_SC_KEYAB_inst                                                         0x00DE
#define DC_PHY_SC_KEYAB_sc_key_b_shift                                               (16)
#define DC_PHY_SC_KEYAB_sc_key_b_mask                                                (0xFFFF0000)
#define DC_PHY_SC_KEYAB_sc_key_b(data)                                               (0xFFFF0000&((data)<<16))
#define DC_PHY_SC_KEYAB_sc_key_b_src(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEYAB_get_sc_key_b(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEYAB_sc_key_a_shift                                               (0)
#define DC_PHY_SC_KEYAB_sc_key_a_mask                                                (0x0000FFFF)
#define DC_PHY_SC_KEYAB_sc_key_a(data)                                               (0x0000FFFF&((data)<<0))
#define DC_PHY_SC_KEYAB_sc_key_a_src(data)                                           ((0x0000FFFF&(data))>>0)
#define DC_PHY_SC_KEYAB_get_sc_key_a(data)                                           ((0x0000FFFF&(data))>>0)


#define DC_PHY_SC_KEYCD                                                              0x18008f7c
#define DC_PHY_SC_KEYCD_reg_addr                                                     "0xB8008F7C"
#define DC_PHY_SC_KEYCD_reg                                                          0xB8008F7C
#define set_DC_PHY_SC_KEYCD_reg(data)   (*((volatile unsigned int*) DC_PHY_SC_KEYCD_reg)=data)
#define get_DC_PHY_SC_KEYCD_reg   (*((volatile unsigned int*) DC_PHY_SC_KEYCD_reg))
#define DC_PHY_SC_KEYCD_inst_adr                                                     "0x00DF"
#define DC_PHY_SC_KEYCD_inst                                                         0x00DF
#define DC_PHY_SC_KEYCD_sc_key_d_shift                                               (16)
#define DC_PHY_SC_KEYCD_sc_key_d_mask                                                (0xFFFF0000)
#define DC_PHY_SC_KEYCD_sc_key_d(data)                                               (0xFFFF0000&((data)<<16))
#define DC_PHY_SC_KEYCD_sc_key_d_src(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEYCD_get_sc_key_d(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEYCD_sc_key_c_shift                                               (0)
#define DC_PHY_SC_KEYCD_sc_key_c_mask                                                (0x0000FFFF)
#define DC_PHY_SC_KEYCD_sc_key_c(data)                                               (0x0000FFFF&((data)<<0))
#define DC_PHY_SC_KEYCD_sc_key_c_src(data)                                           ((0x0000FFFF&(data))>>0)
#define DC_PHY_SC_KEYCD_get_sc_key_c(data)                                           ((0x0000FFFF&(data))>>0)


#define DC_PHY_SC_KEYEF                                                              0x18008f80
#define DC_PHY_SC_KEYEF_reg_addr                                                     "0xB8008F80"
#define DC_PHY_SC_KEYEF_reg                                                          0xB8008F80
#define set_DC_PHY_SC_KEYEF_reg(data)   (*((volatile unsigned int*) DC_PHY_SC_KEYEF_reg)=data)
#define get_DC_PHY_SC_KEYEF_reg   (*((volatile unsigned int*) DC_PHY_SC_KEYEF_reg))
#define DC_PHY_SC_KEYEF_inst_adr                                                     "0x00E0"
#define DC_PHY_SC_KEYEF_inst                                                         0x00E0
#define DC_PHY_SC_KEYEF_sc_key_f_shift                                               (16)
#define DC_PHY_SC_KEYEF_sc_key_f_mask                                                (0xFFFF0000)
#define DC_PHY_SC_KEYEF_sc_key_f(data)                                               (0xFFFF0000&((data)<<16))
#define DC_PHY_SC_KEYEF_sc_key_f_src(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEYEF_get_sc_key_f(data)                                           ((0xFFFF0000&(data))>>16)
#define DC_PHY_SC_KEYEF_sc_key_e_shift                                               (0)
#define DC_PHY_SC_KEYEF_sc_key_e_mask                                                (0x0000FFFF)
#define DC_PHY_SC_KEYEF_sc_key_e(data)                                               (0x0000FFFF&((data)<<0))
#define DC_PHY_SC_KEYEF_sc_key_e_src(data)                                           ((0x0000FFFF&(data))>>0)
#define DC_PHY_SC_KEYEF_get_sc_key_e(data)                                           ((0x0000FFFF&(data))>>0)


#define DC_PHY_CMD_DLY_1T                                                            0x18008f00
#define DC_PHY_CMD_DLY_1T_reg_addr                                                   "0xB8008F00"
#define DC_PHY_CMD_DLY_1T_reg                                                        0xB8008F00
#define set_DC_PHY_CMD_DLY_1T_reg(data)   (*((volatile unsigned int*) DC_PHY_CMD_DLY_1T_reg)=data)
#define get_DC_PHY_CMD_DLY_1T_reg   (*((volatile unsigned int*) DC_PHY_CMD_DLY_1T_reg))
#define DC_PHY_CMD_DLY_1T_inst_adr                                                   "0x00C0"
#define DC_PHY_CMD_DLY_1T_inst                                                       0x00C0
#define DC_PHY_CMD_DLY_1T_issue_cmd_dly_1T_shift                                     (0)
#define DC_PHY_CMD_DLY_1T_issue_cmd_dly_1T_mask                                      (0x00000001)
#define DC_PHY_CMD_DLY_1T_issue_cmd_dly_1T(data)                                     (0x00000001&((data)<<0))
#define DC_PHY_CMD_DLY_1T_issue_cmd_dly_1T_src(data)                                 ((0x00000001&(data))>>0)
#define DC_PHY_CMD_DLY_1T_get_issue_cmd_dly_1T(data)                                 ((0x00000001&(data))>>0)


#define DC_PHY_EXP_LANE_CTRL                                                         0x18008f04
#define DC_PHY_EXP_LANE_CTRL_reg_addr                                                "0xB8008F04"
#define DC_PHY_EXP_LANE_CTRL_reg                                                     0xB8008F04
#define set_DC_PHY_EXP_LANE_CTRL_reg(data)   (*((volatile unsigned int*) DC_PHY_EXP_LANE_CTRL_reg)=data)
#define get_DC_PHY_EXP_LANE_CTRL_reg   (*((volatile unsigned int*) DC_PHY_EXP_LANE_CTRL_reg))
#define DC_PHY_EXP_LANE_CTRL_inst_adr                                                "0x00C1"
#define DC_PHY_EXP_LANE_CTRL_inst                                                    0x00C1
#define DC_PHY_EXP_LANE_CTRL_write_merge_en_shift                                    (1)
#define DC_PHY_EXP_LANE_CTRL_write_merge_en_mask                                     (0x00000002)
#define DC_PHY_EXP_LANE_CTRL_write_merge_en(data)                                    (0x00000002&((data)<<1))
#define DC_PHY_EXP_LANE_CTRL_write_merge_en_src(data)                                ((0x00000002&(data))>>1)
#define DC_PHY_EXP_LANE_CTRL_get_write_merge_en(data)                                ((0x00000002&(data))>>1)
#define DC_PHY_EXP_LANE_CTRL_read_bypass_en_shift                                    (0)
#define DC_PHY_EXP_LANE_CTRL_read_bypass_en_mask                                     (0x00000001)
#define DC_PHY_EXP_LANE_CTRL_read_bypass_en(data)                                    (0x00000001&((data)<<0))
#define DC_PHY_EXP_LANE_CTRL_read_bypass_en_src(data)                                ((0x00000001&(data))>>0)
#define DC_PHY_EXP_LANE_CTRL_get_read_bypass_en(data)                                ((0x00000001&(data))>>0)


#define DC_PHY_CMD_DLYN_0                                                            0x18008F08
#define DC_PHY_CMD_DLYN_0_reg_addr                                                   "0xB8008F08"
#define DC_PHY_CMD_DLYN_0_reg                                                        0xB8008F08
#define set_DC_PHY_CMD_DLYN_0_reg(data)   (*((volatile unsigned int*) DC_PHY_CMD_DLYN_0_reg)=data)
#define get_DC_PHY_CMD_DLYN_0_reg   (*((volatile unsigned int*) DC_PHY_CMD_DLYN_0_reg))
#define DC_PHY_CMD_DLYN_0_inst_adr                                                   "0x00C2"
#define DC_PHY_CMD_DLYN_0_inst                                                       0x00C2
#define DC_PHY_CMD_DLYN_0_bank2_dlyn_shift                                           (24)
#define DC_PHY_CMD_DLYN_0_bank2_dlyn_mask                                            (0x07000000)
#define DC_PHY_CMD_DLYN_0_bank2_dlyn(data)                                           (0x07000000&((data)<<24))
#define DC_PHY_CMD_DLYN_0_bank2_dlyn_src(data)                                       ((0x07000000&(data))>>24)
#define DC_PHY_CMD_DLYN_0_get_bank2_dlyn(data)                                       ((0x07000000&(data))>>24)
#define DC_PHY_CMD_DLYN_0_bank1_dlyn_shift                                           (21)
#define DC_PHY_CMD_DLYN_0_bank1_dlyn_mask                                            (0x00E00000)
#define DC_PHY_CMD_DLYN_0_bank1_dlyn(data)                                           (0x00E00000&((data)<<21))
#define DC_PHY_CMD_DLYN_0_bank1_dlyn_src(data)                                       ((0x00E00000&(data))>>21)
#define DC_PHY_CMD_DLYN_0_get_bank1_dlyn(data)                                       ((0x00E00000&(data))>>21)
#define DC_PHY_CMD_DLYN_0_bank0_dlyn_shift                                           (18)
#define DC_PHY_CMD_DLYN_0_bank0_dlyn_mask                                            (0x001C0000)
#define DC_PHY_CMD_DLYN_0_bank0_dlyn(data)                                           (0x001C0000&((data)<<18))
#define DC_PHY_CMD_DLYN_0_bank0_dlyn_src(data)                                       ((0x001C0000&(data))>>18)
#define DC_PHY_CMD_DLYN_0_get_bank0_dlyn(data)                                       ((0x001C0000&(data))>>18)
#define DC_PHY_CMD_DLYN_0_odt_dlyn_shift                                             (15)
#define DC_PHY_CMD_DLYN_0_odt_dlyn_mask                                              (0x00038000)
#define DC_PHY_CMD_DLYN_0_odt_dlyn(data)                                             (0x00038000&((data)<<15))
#define DC_PHY_CMD_DLYN_0_odt_dlyn_src(data)                                         ((0x00038000&(data))>>15)
#define DC_PHY_CMD_DLYN_0_get_odt_dlyn(data)                                         ((0x00038000&(data))>>15)
#define DC_PHY_CMD_DLYN_0_cke_dlyn_shift                                             (12)
#define DC_PHY_CMD_DLYN_0_cke_dlyn_mask                                              (0x00007000)
#define DC_PHY_CMD_DLYN_0_cke_dlyn(data)                                             (0x00007000&((data)<<12))
#define DC_PHY_CMD_DLYN_0_cke_dlyn_src(data)                                         ((0x00007000&(data))>>12)
#define DC_PHY_CMD_DLYN_0_get_cke_dlyn(data)                                         ((0x00007000&(data))>>12)
#define DC_PHY_CMD_DLYN_0_we_n_dlyn_shift                                            (9)
#define DC_PHY_CMD_DLYN_0_we_n_dlyn_mask                                             (0x00000E00)
#define DC_PHY_CMD_DLYN_0_we_n_dlyn(data)                                            (0x00000E00&((data)<<9))
#define DC_PHY_CMD_DLYN_0_we_n_dlyn_src(data)                                        ((0x00000E00&(data))>>9)
#define DC_PHY_CMD_DLYN_0_get_we_n_dlyn(data)                                        ((0x00000E00&(data))>>9)
#define DC_PHY_CMD_DLYN_0_cas_n_dlyn_shift                                           (6)
#define DC_PHY_CMD_DLYN_0_cas_n_dlyn_mask                                            (0x000001C0)
#define DC_PHY_CMD_DLYN_0_cas_n_dlyn(data)                                           (0x000001C0&((data)<<6))
#define DC_PHY_CMD_DLYN_0_cas_n_dlyn_src(data)                                       ((0x000001C0&(data))>>6)
#define DC_PHY_CMD_DLYN_0_get_cas_n_dlyn(data)                                       ((0x000001C0&(data))>>6)
#define DC_PHY_CMD_DLYN_0_ras_n_dlyn_shift                                           (3)
#define DC_PHY_CMD_DLYN_0_ras_n_dlyn_mask                                            (0x00000038)
#define DC_PHY_CMD_DLYN_0_ras_n_dlyn(data)                                           (0x00000038&((data)<<3))
#define DC_PHY_CMD_DLYN_0_ras_n_dlyn_src(data)                                       ((0x00000038&(data))>>3)
#define DC_PHY_CMD_DLYN_0_get_ras_n_dlyn(data)                                       ((0x00000038&(data))>>3)
#define DC_PHY_CMD_DLYN_0_cs_n_dlyn_shift                                            (0)
#define DC_PHY_CMD_DLYN_0_cs_n_dlyn_mask                                             (0x00000007)
#define DC_PHY_CMD_DLYN_0_cs_n_dlyn(data)                                            (0x00000007&((data)<<0))
#define DC_PHY_CMD_DLYN_0_cs_n_dlyn_src(data)                                        ((0x00000007&(data))>>0)
#define DC_PHY_CMD_DLYN_0_get_cs_n_dlyn(data)                                        ((0x00000007&(data))>>0)


#define DC_PHY_ADR_DLYN_0                                                            0x18008F10
#define DC_PHY_ADR_DLYN_0_reg_addr                                                   "0xB8008F10"
#define DC_PHY_ADR_DLYN_0_reg                                                        0xB8008F10
#define set_DC_PHY_ADR_DLYN_0_reg(data)   (*((volatile unsigned int*) DC_PHY_ADR_DLYN_0_reg)=data)
#define get_DC_PHY_ADR_DLYN_0_reg   (*((volatile unsigned int*) DC_PHY_ADR_DLYN_0_reg))
#define DC_PHY_ADR_DLYN_0_inst_adr                                                   "0x00C4"
#define DC_PHY_ADR_DLYN_0_inst                                                       0x00C4
#define DC_PHY_ADR_DLYN_0_adr09_dlyn_shift                                           (27)
#define DC_PHY_ADR_DLYN_0_adr09_dlyn_mask                                            (0x38000000)
#define DC_PHY_ADR_DLYN_0_adr09_dlyn(data)                                           (0x38000000&((data)<<27))
#define DC_PHY_ADR_DLYN_0_adr09_dlyn_src(data)                                       ((0x38000000&(data))>>27)
#define DC_PHY_ADR_DLYN_0_get_adr09_dlyn(data)                                       ((0x38000000&(data))>>27)
#define DC_PHY_ADR_DLYN_0_adr08_dlyn_shift                                           (24)
#define DC_PHY_ADR_DLYN_0_adr08_dlyn_mask                                            (0x07000000)
#define DC_PHY_ADR_DLYN_0_adr08_dlyn(data)                                           (0x07000000&((data)<<24))
#define DC_PHY_ADR_DLYN_0_adr08_dlyn_src(data)                                       ((0x07000000&(data))>>24)
#define DC_PHY_ADR_DLYN_0_get_adr08_dlyn(data)                                       ((0x07000000&(data))>>24)
#define DC_PHY_ADR_DLYN_0_adr07_dlyn_shift                                           (21)
#define DC_PHY_ADR_DLYN_0_adr07_dlyn_mask                                            (0x00E00000)
#define DC_PHY_ADR_DLYN_0_adr07_dlyn(data)                                           (0x00E00000&((data)<<21))
#define DC_PHY_ADR_DLYN_0_adr07_dlyn_src(data)                                       ((0x00E00000&(data))>>21)
#define DC_PHY_ADR_DLYN_0_get_adr07_dlyn(data)                                       ((0x00E00000&(data))>>21)
#define DC_PHY_ADR_DLYN_0_adr06_dlyn_shift                                           (18)
#define DC_PHY_ADR_DLYN_0_adr06_dlyn_mask                                            (0x001C0000)
#define DC_PHY_ADR_DLYN_0_adr06_dlyn(data)                                           (0x001C0000&((data)<<18))
#define DC_PHY_ADR_DLYN_0_adr06_dlyn_src(data)                                       ((0x001C0000&(data))>>18)
#define DC_PHY_ADR_DLYN_0_get_adr06_dlyn(data)                                       ((0x001C0000&(data))>>18)
#define DC_PHY_ADR_DLYN_0_adr05_dlyn_shift                                           (15)
#define DC_PHY_ADR_DLYN_0_adr05_dlyn_mask                                            (0x00038000)
#define DC_PHY_ADR_DLYN_0_adr05_dlyn(data)                                           (0x00038000&((data)<<15))
#define DC_PHY_ADR_DLYN_0_adr05_dlyn_src(data)                                       ((0x00038000&(data))>>15)
#define DC_PHY_ADR_DLYN_0_get_adr05_dlyn(data)                                       ((0x00038000&(data))>>15)
#define DC_PHY_ADR_DLYN_0_adr04_dlyn_shift                                           (12)
#define DC_PHY_ADR_DLYN_0_adr04_dlyn_mask                                            (0x00007000)
#define DC_PHY_ADR_DLYN_0_adr04_dlyn(data)                                           (0x00007000&((data)<<12))
#define DC_PHY_ADR_DLYN_0_adr04_dlyn_src(data)                                       ((0x00007000&(data))>>12)
#define DC_PHY_ADR_DLYN_0_get_adr04_dlyn(data)                                       ((0x00007000&(data))>>12)
#define DC_PHY_ADR_DLYN_0_adr03_dlyn_shift                                           (9)
#define DC_PHY_ADR_DLYN_0_adr03_dlyn_mask                                            (0x00000E00)
#define DC_PHY_ADR_DLYN_0_adr03_dlyn(data)                                           (0x00000E00&((data)<<9))
#define DC_PHY_ADR_DLYN_0_adr03_dlyn_src(data)                                       ((0x00000E00&(data))>>9)
#define DC_PHY_ADR_DLYN_0_get_adr03_dlyn(data)                                       ((0x00000E00&(data))>>9)
#define DC_PHY_ADR_DLYN_0_adr02_dlyn_shift                                           (6)
#define DC_PHY_ADR_DLYN_0_adr02_dlyn_mask                                            (0x000001C0)
#define DC_PHY_ADR_DLYN_0_adr02_dlyn(data)                                           (0x000001C0&((data)<<6))
#define DC_PHY_ADR_DLYN_0_adr02_dlyn_src(data)                                       ((0x000001C0&(data))>>6)
#define DC_PHY_ADR_DLYN_0_get_adr02_dlyn(data)                                       ((0x000001C0&(data))>>6)
#define DC_PHY_ADR_DLYN_0_adr01_dlyn_shift                                           (3)
#define DC_PHY_ADR_DLYN_0_adr01_dlyn_mask                                            (0x00000038)
#define DC_PHY_ADR_DLYN_0_adr01_dlyn(data)                                           (0x00000038&((data)<<3))
#define DC_PHY_ADR_DLYN_0_adr01_dlyn_src(data)                                       ((0x00000038&(data))>>3)
#define DC_PHY_ADR_DLYN_0_get_adr01_dlyn(data)                                       ((0x00000038&(data))>>3)
#define DC_PHY_ADR_DLYN_0_adr00_dlyn_shift                                           (0)
#define DC_PHY_ADR_DLYN_0_adr00_dlyn_mask                                            (0x00000007)
#define DC_PHY_ADR_DLYN_0_adr00_dlyn(data)                                           (0x00000007&((data)<<0))
#define DC_PHY_ADR_DLYN_0_adr00_dlyn_src(data)                                       ((0x00000007&(data))>>0)
#define DC_PHY_ADR_DLYN_0_get_adr00_dlyn(data)                                       ((0x00000007&(data))>>0)


#define DC_PHY_ADR_DLYN_1                                                            0x18008F14
#define DC_PHY_ADR_DLYN_1_reg_addr                                                   "0xB8008F14"
#define DC_PHY_ADR_DLYN_1_reg                                                        0xB8008F14
#define set_DC_PHY_ADR_DLYN_1_reg(data)   (*((volatile unsigned int*) DC_PHY_ADR_DLYN_1_reg)=data)
#define get_DC_PHY_ADR_DLYN_1_reg   (*((volatile unsigned int*) DC_PHY_ADR_DLYN_1_reg))
#define DC_PHY_ADR_DLYN_1_inst_adr                                                   "0x00C5"
#define DC_PHY_ADR_DLYN_1_inst                                                       0x00C5
#define DC_PHY_ADR_DLYN_1_adr5_ext_dlyn_shift                                        (21)
#define DC_PHY_ADR_DLYN_1_adr5_ext_dlyn_mask                                         (0x00E00000)
#define DC_PHY_ADR_DLYN_1_adr5_ext_dlyn(data)                                        (0x00E00000&((data)<<21))
#define DC_PHY_ADR_DLYN_1_adr5_ext_dlyn_src(data)                                    ((0x00E00000&(data))>>21)
#define DC_PHY_ADR_DLYN_1_get_adr5_ext_dlyn(data)                                    ((0x00E00000&(data))>>21)
#define DC_PHY_ADR_DLYN_1_adr4_ext_dlyn_shift                                        (18)
#define DC_PHY_ADR_DLYN_1_adr4_ext_dlyn_mask                                         (0x001C0000)
#define DC_PHY_ADR_DLYN_1_adr4_ext_dlyn(data)                                        (0x001C0000&((data)<<18))
#define DC_PHY_ADR_DLYN_1_adr4_ext_dlyn_src(data)                                    ((0x001C0000&(data))>>18)
#define DC_PHY_ADR_DLYN_1_get_adr4_ext_dlyn(data)                                    ((0x001C0000&(data))>>18)
#define DC_PHY_ADR_DLYN_1_adr15_dlyn_shift                                           (15)
#define DC_PHY_ADR_DLYN_1_adr15_dlyn_mask                                            (0x00038000)
#define DC_PHY_ADR_DLYN_1_adr15_dlyn(data)                                           (0x00038000&((data)<<15))
#define DC_PHY_ADR_DLYN_1_adr15_dlyn_src(data)                                       ((0x00038000&(data))>>15)
#define DC_PHY_ADR_DLYN_1_get_adr15_dlyn(data)                                       ((0x00038000&(data))>>15)
#define DC_PHY_ADR_DLYN_1_adr14_dlyn_shift                                           (12)
#define DC_PHY_ADR_DLYN_1_adr14_dlyn_mask                                            (0x00007000)
#define DC_PHY_ADR_DLYN_1_adr14_dlyn(data)                                           (0x00007000&((data)<<12))
#define DC_PHY_ADR_DLYN_1_adr14_dlyn_src(data)                                       ((0x00007000&(data))>>12)
#define DC_PHY_ADR_DLYN_1_get_adr14_dlyn(data)                                       ((0x00007000&(data))>>12)
#define DC_PHY_ADR_DLYN_1_adr13_dlyn_shift                                           (9)
#define DC_PHY_ADR_DLYN_1_adr13_dlyn_mask                                            (0x00000E00)
#define DC_PHY_ADR_DLYN_1_adr13_dlyn(data)                                           (0x00000E00&((data)<<9))
#define DC_PHY_ADR_DLYN_1_adr13_dlyn_src(data)                                       ((0x00000E00&(data))>>9)
#define DC_PHY_ADR_DLYN_1_get_adr13_dlyn(data)                                       ((0x00000E00&(data))>>9)
#define DC_PHY_ADR_DLYN_1_adr12_dlyn_shift                                           (6)
#define DC_PHY_ADR_DLYN_1_adr12_dlyn_mask                                            (0x000001C0)
#define DC_PHY_ADR_DLYN_1_adr12_dlyn(data)                                           (0x000001C0&((data)<<6))
#define DC_PHY_ADR_DLYN_1_adr12_dlyn_src(data)                                       ((0x000001C0&(data))>>6)
#define DC_PHY_ADR_DLYN_1_get_adr12_dlyn(data)                                       ((0x000001C0&(data))>>6)
#define DC_PHY_ADR_DLYN_1_adr11_dlyn_shift                                           (3)
#define DC_PHY_ADR_DLYN_1_adr11_dlyn_mask                                            (0x00000038)
#define DC_PHY_ADR_DLYN_1_adr11_dlyn(data)                                           (0x00000038&((data)<<3))
#define DC_PHY_ADR_DLYN_1_adr11_dlyn_src(data)                                       ((0x00000038&(data))>>3)
#define DC_PHY_ADR_DLYN_1_get_adr11_dlyn(data)                                       ((0x00000038&(data))>>3)
#define DC_PHY_ADR_DLYN_1_adr10_dlyn_shift                                           (0)
#define DC_PHY_ADR_DLYN_1_adr10_dlyn_mask                                            (0x00000007)
#define DC_PHY_ADR_DLYN_1_adr10_dlyn(data)                                           (0x00000007&((data)<<0))
#define DC_PHY_ADR_DLYN_1_adr10_dlyn_src(data)                                       ((0x00000007&(data))>>0)
#define DC_PHY_ADR_DLYN_1_get_adr10_dlyn(data)                                       ((0x00000007&(data))>>0)


#define DC_PHY_SCPU_PC_TOTA_MON_NUM                                                  0x18008f18
#define DC_PHY_SCPU_PC_TOTA_MON_NUM_reg_addr                                         "0xB8008F18"
#define DC_PHY_SCPU_PC_TOTA_MON_NUM_reg                                              0xB8008F18
#define set_DC_PHY_SCPU_PC_TOTA_MON_NUM_reg(data)   (*((volatile unsigned int*) DC_PHY_SCPU_PC_TOTA_MON_NUM_reg)=data)
#define get_DC_PHY_SCPU_PC_TOTA_MON_NUM_reg   (*((volatile unsigned int*) DC_PHY_SCPU_PC_TOTA_MON_NUM_reg))
#define DC_PHY_SCPU_PC_TOTA_MON_NUM_inst_adr                                         "0x00C6"
#define DC_PHY_SCPU_PC_TOTA_MON_NUM_inst                                             0x00C6
#define DC_PHY_SCPU_PC_TOTA_MON_NUM_tota_mon_num_shift                               (0)
#define DC_PHY_SCPU_PC_TOTA_MON_NUM_tota_mon_num_mask                                (0xFFFFFFFF)
#define DC_PHY_SCPU_PC_TOTA_MON_NUM_tota_mon_num(data)                               (0xFFFFFFFF&((data)<<0))
#define DC_PHY_SCPU_PC_TOTA_MON_NUM_tota_mon_num_src(data)                           ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_SCPU_PC_TOTA_MON_NUM_get_tota_mon_num(data)                           ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_SCPU_PC_TOTA_ACK_NUM                                                  0x18008f1c
#define DC_PHY_SCPU_PC_TOTA_ACK_NUM_reg_addr                                         "0xB8008F1C"
#define DC_PHY_SCPU_PC_TOTA_ACK_NUM_reg                                              0xB8008F1C
#define set_DC_PHY_SCPU_PC_TOTA_ACK_NUM_reg(data)   (*((volatile unsigned int*) DC_PHY_SCPU_PC_TOTA_ACK_NUM_reg)=data)
#define get_DC_PHY_SCPU_PC_TOTA_ACK_NUM_reg   (*((volatile unsigned int*) DC_PHY_SCPU_PC_TOTA_ACK_NUM_reg))
#define DC_PHY_SCPU_PC_TOTA_ACK_NUM_inst_adr                                         "0x00C7"
#define DC_PHY_SCPU_PC_TOTA_ACK_NUM_inst                                             0x00C7
#define DC_PHY_SCPU_PC_TOTA_ACK_NUM_tota_ack_num_shift                               (0)
#define DC_PHY_SCPU_PC_TOTA_ACK_NUM_tota_ack_num_mask                                (0xFFFFFFFF)
#define DC_PHY_SCPU_PC_TOTA_ACK_NUM_tota_ack_num(data)                               (0xFFFFFFFF&((data)<<0))
#define DC_PHY_SCPU_PC_TOTA_ACK_NUM_tota_ack_num_src(data)                           ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_SCPU_PC_TOTA_ACK_NUM_get_tota_ack_num(data)                           ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_SCPU_PC_TOTA_IDL_NUM                                                  0x18008f20
#define DC_PHY_SCPU_PC_TOTA_IDL_NUM_reg_addr                                         "0xB8008F20"
#define DC_PHY_SCPU_PC_TOTA_IDL_NUM_reg                                              0xB8008F20
#define set_DC_PHY_SCPU_PC_TOTA_IDL_NUM_reg(data)   (*((volatile unsigned int*) DC_PHY_SCPU_PC_TOTA_IDL_NUM_reg)=data)
#define get_DC_PHY_SCPU_PC_TOTA_IDL_NUM_reg   (*((volatile unsigned int*) DC_PHY_SCPU_PC_TOTA_IDL_NUM_reg))
#define DC_PHY_SCPU_PC_TOTA_IDL_NUM_inst_adr                                         "0x00C8"
#define DC_PHY_SCPU_PC_TOTA_IDL_NUM_inst                                             0x00C8
#define DC_PHY_SCPU_PC_TOTA_IDL_NUM_tota_idl_num_shift                               (0)
#define DC_PHY_SCPU_PC_TOTA_IDL_NUM_tota_idl_num_mask                                (0xFFFFFFFF)
#define DC_PHY_SCPU_PC_TOTA_IDL_NUM_tota_idl_num(data)                               (0xFFFFFFFF&((data)<<0))
#define DC_PHY_SCPU_PC_TOTA_IDL_NUM_tota_idl_num_src(data)                           ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_SCPU_PC_TOTA_IDL_NUM_get_tota_idl_num(data)                           ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_SCPU_PC_ACC_LAT                                                       0x18008f24
#define DC_PHY_SCPU_PC_ACC_LAT_reg_addr                                              "0xB8008F24"
#define DC_PHY_SCPU_PC_ACC_LAT_reg                                                   0xB8008F24
#define set_DC_PHY_SCPU_PC_ACC_LAT_reg(data)   (*((volatile unsigned int*) DC_PHY_SCPU_PC_ACC_LAT_reg)=data)
#define get_DC_PHY_SCPU_PC_ACC_LAT_reg   (*((volatile unsigned int*) DC_PHY_SCPU_PC_ACC_LAT_reg))
#define DC_PHY_SCPU_PC_ACC_LAT_inst_adr                                              "0x00C9"
#define DC_PHY_SCPU_PC_ACC_LAT_inst                                                  0x00C9
#define DC_PHY_SCPU_PC_ACC_LAT_acc_lat_shift                                         (0)
#define DC_PHY_SCPU_PC_ACC_LAT_acc_lat_mask                                          (0xFFFFFFFF)
#define DC_PHY_SCPU_PC_ACC_LAT_acc_lat(data)                                         (0xFFFFFFFF&((data)<<0))
#define DC_PHY_SCPU_PC_ACC_LAT_acc_lat_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_SCPU_PC_ACC_LAT_get_acc_lat(data)                                     ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_SCPU_PC_MAX_LAT                                                       0x18008f28
#define DC_PHY_SCPU_PC_MAX_LAT_reg_addr                                              "0xB8008F28"
#define DC_PHY_SCPU_PC_MAX_LAT_reg                                                   0xB8008F28
#define set_DC_PHY_SCPU_PC_MAX_LAT_reg(data)   (*((volatile unsigned int*) DC_PHY_SCPU_PC_MAX_LAT_reg)=data)
#define get_DC_PHY_SCPU_PC_MAX_LAT_reg   (*((volatile unsigned int*) DC_PHY_SCPU_PC_MAX_LAT_reg))
#define DC_PHY_SCPU_PC_MAX_LAT_inst_adr                                              "0x00CA"
#define DC_PHY_SCPU_PC_MAX_LAT_inst                                                  0x00CA
#define DC_PHY_SCPU_PC_MAX_LAT_max_lat_shift                                         (0)
#define DC_PHY_SCPU_PC_MAX_LAT_max_lat_mask                                          (0x0000FFFF)
#define DC_PHY_SCPU_PC_MAX_LAT_max_lat(data)                                         (0x0000FFFF&((data)<<0))
#define DC_PHY_SCPU_PC_MAX_LAT_max_lat_src(data)                                     ((0x0000FFFF&(data))>>0)
#define DC_PHY_SCPU_PC_MAX_LAT_get_max_lat(data)                                     ((0x0000FFFF&(data))>>0)


#define DC_PHY_SCPU_PC_REQ_NUM                                                       0x18008f2c
#define DC_PHY_SCPU_PC_REQ_NUM_reg_addr                                              "0xB8008F2C"
#define DC_PHY_SCPU_PC_REQ_NUM_reg                                                   0xB8008F2C
#define set_DC_PHY_SCPU_PC_REQ_NUM_reg(data)   (*((volatile unsigned int*) DC_PHY_SCPU_PC_REQ_NUM_reg)=data)
#define get_DC_PHY_SCPU_PC_REQ_NUM_reg   (*((volatile unsigned int*) DC_PHY_SCPU_PC_REQ_NUM_reg))
#define DC_PHY_SCPU_PC_REQ_NUM_inst_adr                                              "0x00CB"
#define DC_PHY_SCPU_PC_REQ_NUM_inst                                                  0x00CB
#define DC_PHY_SCPU_PC_REQ_NUM_req_num_shift                                         (0)
#define DC_PHY_SCPU_PC_REQ_NUM_req_num_mask                                          (0x00FFFFFF)
#define DC_PHY_SCPU_PC_REQ_NUM_req_num(data)                                         (0x00FFFFFF&((data)<<0))
#define DC_PHY_SCPU_PC_REQ_NUM_req_num_src(data)                                     ((0x00FFFFFF&(data))>>0)
#define DC_PHY_SCPU_PC_REQ_NUM_get_req_num(data)                                     ((0x00FFFFFF&(data))>>0)


#define DC_PHY_SCPU_PC_ACK_NUM                                                       0x18008f30
#define DC_PHY_SCPU_PC_ACK_NUM_reg_addr                                              "0xB8008F30"
#define DC_PHY_SCPU_PC_ACK_NUM_reg                                                   0xB8008F30
#define set_DC_PHY_SCPU_PC_ACK_NUM_reg(data)   (*((volatile unsigned int*) DC_PHY_SCPU_PC_ACK_NUM_reg)=data)
#define get_DC_PHY_SCPU_PC_ACK_NUM_reg   (*((volatile unsigned int*) DC_PHY_SCPU_PC_ACK_NUM_reg))
#define DC_PHY_SCPU_PC_ACK_NUM_inst_adr                                              "0x00CC"
#define DC_PHY_SCPU_PC_ACK_NUM_inst                                                  0x00CC
#define DC_PHY_SCPU_PC_ACK_NUM_ack_num_shift                                         (0)
#define DC_PHY_SCPU_PC_ACK_NUM_ack_num_mask                                          (0xFFFFFFFF)
#define DC_PHY_SCPU_PC_ACK_NUM_ack_num(data)                                         (0xFFFFFFFF&((data)<<0))
#define DC_PHY_SCPU_PC_ACK_NUM_ack_num_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_SCPU_PC_ACK_NUM_get_ack_num(data)                                     ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_SCPU_PC_CTRL                                                          0x18008f34
#define DC_PHY_SCPU_PC_CTRL_reg_addr                                                 "0xB8008F34"
#define DC_PHY_SCPU_PC_CTRL_reg                                                      0xB8008F34
#define set_DC_PHY_SCPU_PC_CTRL_reg(data)   (*((volatile unsigned int*) DC_PHY_SCPU_PC_CTRL_reg)=data)
#define get_DC_PHY_SCPU_PC_CTRL_reg   (*((volatile unsigned int*) DC_PHY_SCPU_PC_CTRL_reg))
#define DC_PHY_SCPU_PC_CTRL_inst_adr                                                 "0x00CD"
#define DC_PHY_SCPU_PC_CTRL_inst                                                     0x00CD
#define DC_PHY_SCPU_PC_CTRL_pc_go_shift                                              (0)
#define DC_PHY_SCPU_PC_CTRL_pc_go_mask                                               (0x00000001)
#define DC_PHY_SCPU_PC_CTRL_pc_go(data)                                              (0x00000001&((data)<<0))
#define DC_PHY_SCPU_PC_CTRL_pc_go_src(data)                                          ((0x00000001&(data))>>0)
#define DC_PHY_SCPU_PC_CTRL_get_pc_go(data)                                          ((0x00000001&(data))>>0)


#define DC_PHY_GCK_CTRL                                                              0x18008f38
#define DC_PHY_GCK_CTRL_reg_addr                                                     "0xB8008F38"
#define DC_PHY_GCK_CTRL_reg                                                          0xB8008F38
#define set_DC_PHY_GCK_CTRL_reg(data)   (*((volatile unsigned int*) DC_PHY_GCK_CTRL_reg)=data)
#define get_DC_PHY_GCK_CTRL_reg   (*((volatile unsigned int*) DC_PHY_GCK_CTRL_reg))
#define DC_PHY_GCK_CTRL_inst_adr                                                     "0x00CE"
#define DC_PHY_GCK_CTRL_inst                                                         0x00CE
#define DC_PHY_GCK_CTRL_gck_ext_cyc_shift                                            (8)
#define DC_PHY_GCK_CTRL_gck_ext_cyc_mask                                             (0x00003F00)
#define DC_PHY_GCK_CTRL_gck_ext_cyc(data)                                            (0x00003F00&((data)<<8))
#define DC_PHY_GCK_CTRL_gck_ext_cyc_src(data)                                        ((0x00003F00&(data))>>8)
#define DC_PHY_GCK_CTRL_get_gck_ext_cyc(data)                                        ((0x00003F00&(data))>>8)
#define DC_PHY_GCK_CTRL_par_gck_en_shift                                             (2)
#define DC_PHY_GCK_CTRL_par_gck_en_mask                                              (0x00000004)
#define DC_PHY_GCK_CTRL_par_gck_en(data)                                             (0x00000004&((data)<<2))
#define DC_PHY_GCK_CTRL_par_gck_en_src(data)                                         ((0x00000004&(data))>>2)
#define DC_PHY_GCK_CTRL_get_par_gck_en(data)                                         ((0x00000004&(data))>>2)
#define DC_PHY_GCK_CTRL_fsm_gck_en_shift                                             (1)
#define DC_PHY_GCK_CTRL_fsm_gck_en_mask                                              (0x00000002)
#define DC_PHY_GCK_CTRL_fsm_gck_en(data)                                             (0x00000002&((data)<<1))
#define DC_PHY_GCK_CTRL_fsm_gck_en_src(data)                                         ((0x00000002&(data))>>1)
#define DC_PHY_GCK_CTRL_get_fsm_gck_en(data)                                         ((0x00000002&(data))>>1)
#define DC_PHY_GCK_CTRL_ioblk_gck_en_shift                                           (0)
#define DC_PHY_GCK_CTRL_ioblk_gck_en_mask                                            (0x00000001)
#define DC_PHY_GCK_CTRL_ioblk_gck_en(data)                                           (0x00000001&((data)<<0))
#define DC_PHY_GCK_CTRL_ioblk_gck_en_src(data)                                       ((0x00000001&(data))>>0)
#define DC_PHY_GCK_CTRL_get_ioblk_gck_en(data)                                       ((0x00000001&(data))>>0)


#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0                                              0x18008f3c
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0_reg_addr                                     "0xB8008F3C"
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0_reg                                          0xB8008F3C
#define set_DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0_reg(data)   (*((volatile unsigned int*) DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0_reg)=data)
#define get_DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0_reg   (*((volatile unsigned int*) DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0_reg))
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0_inst_adr                                     "0x00CF"
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0_inst                                         0x00CF
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0_enable_shift                                 (0)
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0_enable_mask                                  (0x00000001)
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0_enable(data)                                 (0x00000001&((data)<<0))
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0_enable_src(data)                             ((0x00000001&(data))>>0)
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_0_get_enable(data)                             ((0x00000001&(data))>>0)


#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1                                              0x18008f40
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1_reg_addr                                     "0xB8008F40"
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1_reg                                          0xB8008F40
#define set_DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1_reg(data)   (*((volatile unsigned int*) DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1_reg)=data)
#define get_DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1_reg   (*((volatile unsigned int*) DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1_reg))
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1_inst_adr                                     "0x00D0"
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1_inst                                         0x00D0
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1_timer_threshold_shift                        (0)
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1_timer_threshold_mask                         (0xFFFFFFFF)
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1_timer_threshold(data)                        (0xFFFFFFFF&((data)<<0))
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1_timer_threshold_src(data)                    ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_1_get_timer_threshold(data)                    ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2                                              0x18008f44
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2_reg_addr                                     "0xB8008F44"
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2_reg                                          0xB8008F44
#define set_DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2_reg(data)   (*((volatile unsigned int*) DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2_reg)=data)
#define get_DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2_reg   (*((volatile unsigned int*) DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2_reg))
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2_inst_adr                                     "0x00D1"
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2_inst                                         0x00D1
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2_count_threshold_shift                        (0)
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2_count_threshold_mask                         (0x00FFFFFF)
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2_count_threshold(data)                        (0x00FFFFFF&((data)<<0))
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2_count_threshold_src(data)                    ((0x00FFFFFF&(data))>>0)
#define DC_PHY_SCPU_LEAKY_BUCKET_CTRL_2_get_count_threshold(data)                    ((0x00FFFFFF&(data))>>0)


#define DC_PHY_SCPU_PC_MERGE_NUM                                                     0x18008f48
#define DC_PHY_SCPU_PC_MERGE_NUM_reg_addr                                            "0xB8008F48"
#define DC_PHY_SCPU_PC_MERGE_NUM_reg                                                 0xB8008F48
#define set_DC_PHY_SCPU_PC_MERGE_NUM_reg(data)   (*((volatile unsigned int*) DC_PHY_SCPU_PC_MERGE_NUM_reg)=data)
#define get_DC_PHY_SCPU_PC_MERGE_NUM_reg   (*((volatile unsigned int*) DC_PHY_SCPU_PC_MERGE_NUM_reg))
#define DC_PHY_SCPU_PC_MERGE_NUM_inst_adr                                            "0x00D2"
#define DC_PHY_SCPU_PC_MERGE_NUM_inst                                                0x00D2
#define DC_PHY_SCPU_PC_MERGE_NUM_merge_num_shift                                     (0)
#define DC_PHY_SCPU_PC_MERGE_NUM_merge_num_mask                                      (0x00FFFFFF)
#define DC_PHY_SCPU_PC_MERGE_NUM_merge_num(data)                                     (0x00FFFFFF&((data)<<0))
#define DC_PHY_SCPU_PC_MERGE_NUM_merge_num_src(data)                                 ((0x00FFFFFF&(data))>>0)
#define DC_PHY_SCPU_PC_MERGE_NUM_get_merge_num(data)                                 ((0x00FFFFFF&(data))>>0)


#define DC_PHY_SCPU_PC_WR_REQ_NUM                                                    0x18008f4c
#define DC_PHY_SCPU_PC_WR_REQ_NUM_reg_addr                                           "0xB8008F4C"
#define DC_PHY_SCPU_PC_WR_REQ_NUM_reg                                                0xB8008F4C
#define set_DC_PHY_SCPU_PC_WR_REQ_NUM_reg(data)   (*((volatile unsigned int*) DC_PHY_SCPU_PC_WR_REQ_NUM_reg)=data)
#define get_DC_PHY_SCPU_PC_WR_REQ_NUM_reg   (*((volatile unsigned int*) DC_PHY_SCPU_PC_WR_REQ_NUM_reg))
#define DC_PHY_SCPU_PC_WR_REQ_NUM_inst_adr                                           "0x00D3"
#define DC_PHY_SCPU_PC_WR_REQ_NUM_inst                                               0x00D3
#define DC_PHY_SCPU_PC_WR_REQ_NUM_wr_req_num_shift                                   (0)
#define DC_PHY_SCPU_PC_WR_REQ_NUM_wr_req_num_mask                                    (0x00FFFFFF)
#define DC_PHY_SCPU_PC_WR_REQ_NUM_wr_req_num(data)                                   (0x00FFFFFF&((data)<<0))
#define DC_PHY_SCPU_PC_WR_REQ_NUM_wr_req_num_src(data)                               ((0x00FFFFFF&(data))>>0)
#define DC_PHY_SCPU_PC_WR_REQ_NUM_get_wr_req_num(data)                               ((0x00FFFFFF&(data))>>0)


#define DC_PHY_SPEED_SENSOR_CTRL                                                     0x18008f50
#define DC_PHY_SPEED_SENSOR_CTRL_reg_addr                                            "0xB8008F50"
#define DC_PHY_SPEED_SENSOR_CTRL_reg                                                 0xB8008F50
#define set_DC_PHY_SPEED_SENSOR_CTRL_reg(data)   (*((volatile unsigned int*) DC_PHY_SPEED_SENSOR_CTRL_reg)=data)
#define get_DC_PHY_SPEED_SENSOR_CTRL_reg   (*((volatile unsigned int*) DC_PHY_SPEED_SENSOR_CTRL_reg))
#define DC_PHY_SPEED_SENSOR_CTRL_inst_adr                                            "0x00D4"
#define DC_PHY_SPEED_SENSOR_CTRL_inst                                                0x00D4
#define DC_PHY_SPEED_SENSOR_CTRL_data_in_shift                                       (8)
#define DC_PHY_SPEED_SENSOR_CTRL_data_in_mask                                        (0x0FFFFF00)
#define DC_PHY_SPEED_SENSOR_CTRL_data_in(data)                                       (0x0FFFFF00&((data)<<8))
#define DC_PHY_SPEED_SENSOR_CTRL_data_in_src(data)                                   ((0x0FFFFF00&(data))>>8)
#define DC_PHY_SPEED_SENSOR_CTRL_get_data_in(data)                                   ((0x0FFFFF00&(data))>>8)
#define DC_PHY_SPEED_SENSOR_CTRL_data_in_ready_shift                                 (5)
#define DC_PHY_SPEED_SENSOR_CTRL_data_in_ready_mask                                  (0x00000020)
#define DC_PHY_SPEED_SENSOR_CTRL_data_in_ready(data)                                 (0x00000020&((data)<<5))
#define DC_PHY_SPEED_SENSOR_CTRL_data_in_ready_src(data)                             ((0x00000020&(data))>>5)
#define DC_PHY_SPEED_SENSOR_CTRL_get_data_in_ready(data)                             ((0x00000020&(data))>>5)
#define DC_PHY_SPEED_SENSOR_CTRL_wire_sel_shift                                      (4)
#define DC_PHY_SPEED_SENSOR_CTRL_wire_sel_mask                                       (0x00000010)
#define DC_PHY_SPEED_SENSOR_CTRL_wire_sel(data)                                      (0x00000010&((data)<<4))
#define DC_PHY_SPEED_SENSOR_CTRL_wire_sel_src(data)                                  ((0x00000010&(data))>>4)
#define DC_PHY_SPEED_SENSOR_CTRL_get_wire_sel(data)                                  ((0x00000010&(data))>>4)
#define DC_PHY_SPEED_SENSOR_CTRL_ro_sel_shift                                        (1)
#define DC_PHY_SPEED_SENSOR_CTRL_ro_sel_mask                                         (0x0000000E)
#define DC_PHY_SPEED_SENSOR_CTRL_ro_sel(data)                                        (0x0000000E&((data)<<1))
#define DC_PHY_SPEED_SENSOR_CTRL_ro_sel_src(data)                                    ((0x0000000E&(data))>>1)
#define DC_PHY_SPEED_SENSOR_CTRL_get_ro_sel(data)                                    ((0x0000000E&(data))>>1)
#define DC_PHY_SPEED_SENSOR_CTRL_dss_rst_n_shift                                     (0)
#define DC_PHY_SPEED_SENSOR_CTRL_dss_rst_n_mask                                      (0x00000001)
#define DC_PHY_SPEED_SENSOR_CTRL_dss_rst_n(data)                                     (0x00000001&((data)<<0))
#define DC_PHY_SPEED_SENSOR_CTRL_dss_rst_n_src(data)                                 ((0x00000001&(data))>>0)
#define DC_PHY_SPEED_SENSOR_CTRL_get_dss_rst_n(data)                                 ((0x00000001&(data))>>0)


#define DC_PHY_SPEED_SENSOR_STATUS                                                   0x18008f54
#define DC_PHY_SPEED_SENSOR_STATUS_reg_addr                                          "0xB8008F54"
#define DC_PHY_SPEED_SENSOR_STATUS_reg                                               0xB8008F54
#define set_DC_PHY_SPEED_SENSOR_STATUS_reg(data)   (*((volatile unsigned int*) DC_PHY_SPEED_SENSOR_STATUS_reg)=data)
#define get_DC_PHY_SPEED_SENSOR_STATUS_reg   (*((volatile unsigned int*) DC_PHY_SPEED_SENSOR_STATUS_reg))
#define DC_PHY_SPEED_SENSOR_STATUS_inst_adr                                          "0x00D5"
#define DC_PHY_SPEED_SENSOR_STATUS_inst                                              0x00D5
#define DC_PHY_SPEED_SENSOR_STATUS_count_out_shift                                   (4)
#define DC_PHY_SPEED_SENSOR_STATUS_count_out_mask                                    (0x00FFFFF0)
#define DC_PHY_SPEED_SENSOR_STATUS_count_out(data)                                   (0x00FFFFF0&((data)<<4))
#define DC_PHY_SPEED_SENSOR_STATUS_count_out_src(data)                               ((0x00FFFFF0&(data))>>4)
#define DC_PHY_SPEED_SENSOR_STATUS_get_count_out(data)                               ((0x00FFFFF0&(data))>>4)
#define DC_PHY_SPEED_SENSOR_STATUS_wsort_go_shift                                    (1)
#define DC_PHY_SPEED_SENSOR_STATUS_wsort_go_mask                                     (0x00000002)
#define DC_PHY_SPEED_SENSOR_STATUS_wsort_go(data)                                    (0x00000002&((data)<<1))
#define DC_PHY_SPEED_SENSOR_STATUS_wsort_go_src(data)                                ((0x00000002&(data))>>1)
#define DC_PHY_SPEED_SENSOR_STATUS_get_wsort_go(data)                                ((0x00000002&(data))>>1)
#define DC_PHY_SPEED_SENSOR_STATUS_ready_shift                                       (0)
#define DC_PHY_SPEED_SENSOR_STATUS_ready_mask                                        (0x00000001)
#define DC_PHY_SPEED_SENSOR_STATUS_ready(data)                                       (0x00000001&((data)<<0))
#define DC_PHY_SPEED_SENSOR_STATUS_ready_src(data)                                   ((0x00000001&(data))>>0)
#define DC_PHY_SPEED_SENSOR_STATUS_get_ready(data)                                   ((0x00000001&(data))>>0)


#define DC_PHY_EXPRESS_LANE_CTRL_MISC                                                0x18008f58
#define DC_PHY_EXPRESS_LANE_CTRL_MISC_reg_addr                                       "0xB8008F58"
#define DC_PHY_EXPRESS_LANE_CTRL_MISC_reg                                            0xB8008F58
#define set_DC_PHY_EXPRESS_LANE_CTRL_MISC_reg(data)   (*((volatile unsigned int*) DC_PHY_EXPRESS_LANE_CTRL_MISC_reg)=data)
#define get_DC_PHY_EXPRESS_LANE_CTRL_MISC_reg   (*((volatile unsigned int*) DC_PHY_EXPRESS_LANE_CTRL_MISC_reg))
#define DC_PHY_EXPRESS_LANE_CTRL_MISC_inst_adr                                       "0x00D6"
#define DC_PHY_EXPRESS_LANE_CTRL_MISC_inst                                           0x00D6
#define DC_PHY_EXPRESS_LANE_CTRL_MISC_ctrl_misc_shift                                (0)
#define DC_PHY_EXPRESS_LANE_CTRL_MISC_ctrl_misc_mask                                 (0xFFFFFFFF)
#define DC_PHY_EXPRESS_LANE_CTRL_MISC_ctrl_misc(data)                                (0xFFFFFFFF&((data)<<0))
#define DC_PHY_EXPRESS_LANE_CTRL_MISC_ctrl_misc_src(data)                            ((0xFFFFFFFF&(data))>>0)
#define DC_PHY_EXPRESS_LANE_CTRL_MISC_get_ctrl_misc(data)                            ((0xFFFFFFFF&(data))>>0)


#define DC_PHY_DSS_C35_MISC                                                          0x18008f90
#define DC_PHY_DSS_C35_MISC_reg_addr                                                 "0xB8008F90"
#define DC_PHY_DSS_C35_MISC_reg                                                      0xB8008F90
#define set_DC_PHY_DSS_C35_MISC_reg(data)   (*((volatile unsigned int*) DC_PHY_DSS_C35_MISC_reg)=data)
#define get_DC_PHY_DSS_C35_MISC_reg   (*((volatile unsigned int*) DC_PHY_DSS_C35_MISC_reg))
#define DC_PHY_DSS_C35_MISC_inst_adr                                                 "0x00E4"
#define DC_PHY_DSS_C35_MISC_inst                                                     0x00E4
#define DC_PHY_DSS_C35_MISC_data_in_shift                                            (8)
#define DC_PHY_DSS_C35_MISC_data_in_mask                                             (0x0FFFFF00)
#define DC_PHY_DSS_C35_MISC_data_in(data)                                            (0x0FFFFF00&((data)<<8))
#define DC_PHY_DSS_C35_MISC_data_in_src(data)                                        ((0x0FFFFF00&(data))>>8)
#define DC_PHY_DSS_C35_MISC_get_data_in(data)                                        ((0x0FFFFF00&(data))>>8)
#define DC_PHY_DSS_C35_MISC_speed_en_shift                                           (5)
#define DC_PHY_DSS_C35_MISC_speed_en_mask                                            (0x00000020)
#define DC_PHY_DSS_C35_MISC_speed_en(data)                                           (0x00000020&((data)<<5))
#define DC_PHY_DSS_C35_MISC_speed_en_src(data)                                       ((0x00000020&(data))>>5)
#define DC_PHY_DSS_C35_MISC_get_speed_en(data)                                       ((0x00000020&(data))>>5)
#define DC_PHY_DSS_C35_MISC_wire_sel_shift                                           (4)
#define DC_PHY_DSS_C35_MISC_wire_sel_mask                                            (0x00000010)
#define DC_PHY_DSS_C35_MISC_wire_sel(data)                                           (0x00000010&((data)<<4))
#define DC_PHY_DSS_C35_MISC_wire_sel_src(data)                                       ((0x00000010&(data))>>4)
#define DC_PHY_DSS_C35_MISC_get_wire_sel(data)                                       ((0x00000010&(data))>>4)
#define DC_PHY_DSS_C35_MISC_ro_sel_shift                                             (1)
#define DC_PHY_DSS_C35_MISC_ro_sel_mask                                              (0x0000000E)
#define DC_PHY_DSS_C35_MISC_ro_sel(data)                                             (0x0000000E&((data)<<1))
#define DC_PHY_DSS_C35_MISC_ro_sel_src(data)                                         ((0x0000000E&(data))>>1)
#define DC_PHY_DSS_C35_MISC_get_ro_sel(data)                                         ((0x0000000E&(data))>>1)
#define DC_PHY_DSS_C35_MISC_dss_rst_n_shift                                          (0)
#define DC_PHY_DSS_C35_MISC_dss_rst_n_mask                                           (0x00000001)
#define DC_PHY_DSS_C35_MISC_dss_rst_n(data)                                          (0x00000001&((data)<<0))
#define DC_PHY_DSS_C35_MISC_dss_rst_n_src(data)                                      ((0x00000001&(data))>>0)
#define DC_PHY_DSS_C35_MISC_get_dss_rst_n(data)                                      ((0x00000001&(data))>>0)


#define DC_PHY_DSS_C35_ST                                                            0x18008f94
#define DC_PHY_DSS_C35_ST_reg_addr                                                   "0xB8008F94"
#define DC_PHY_DSS_C35_ST_reg                                                        0xB8008F94
#define set_DC_PHY_DSS_C35_ST_reg(data)   (*((volatile unsigned int*) DC_PHY_DSS_C35_ST_reg)=data)
#define get_DC_PHY_DSS_C35_ST_reg   (*((volatile unsigned int*) DC_PHY_DSS_C35_ST_reg))
#define DC_PHY_DSS_C35_ST_inst_adr                                                   "0x00E5"
#define DC_PHY_DSS_C35_ST_inst                                                       0x00E5
#define DC_PHY_DSS_C35_ST_count_out_shift                                            (4)
#define DC_PHY_DSS_C35_ST_count_out_mask                                             (0x00FFFFF0)
#define DC_PHY_DSS_C35_ST_count_out(data)                                            (0x00FFFFF0&((data)<<4))
#define DC_PHY_DSS_C35_ST_count_out_src(data)                                        ((0x00FFFFF0&(data))>>4)
#define DC_PHY_DSS_C35_ST_get_count_out(data)                                        ((0x00FFFFF0&(data))>>4)
#define DC_PHY_DSS_C35_ST_wsort_go_shift                                             (1)
#define DC_PHY_DSS_C35_ST_wsort_go_mask                                              (0x00000002)
#define DC_PHY_DSS_C35_ST_wsort_go(data)                                             (0x00000002&((data)<<1))
#define DC_PHY_DSS_C35_ST_wsort_go_src(data)                                         ((0x00000002&(data))>>1)
#define DC_PHY_DSS_C35_ST_get_wsort_go(data)                                         ((0x00000002&(data))>>1)
#define DC_PHY_DSS_C35_ST_ready_shift                                                (0)
#define DC_PHY_DSS_C35_ST_ready_mask                                                 (0x00000001)
#define DC_PHY_DSS_C35_ST_ready(data)                                                (0x00000001&((data)<<0))
#define DC_PHY_DSS_C35_ST_ready_src(data)                                            ((0x00000001&(data))>>0)
#define DC_PHY_DSS_C35_ST_get_ready(data)                                            ((0x00000001&(data))>>0)


#define DC_PHY_DSS_C35D5_MISC                                                        0x18008f98
#define DC_PHY_DSS_C35D5_MISC_reg_addr                                               "0xB8008F98"
#define DC_PHY_DSS_C35D5_MISC_reg                                                    0xB8008F98
#define set_DC_PHY_DSS_C35D5_MISC_reg(data)   (*((volatile unsigned int*) DC_PHY_DSS_C35D5_MISC_reg)=data)
#define get_DC_PHY_DSS_C35D5_MISC_reg   (*((volatile unsigned int*) DC_PHY_DSS_C35D5_MISC_reg))
#define DC_PHY_DSS_C35D5_MISC_inst_adr                                               "0x00E6"
#define DC_PHY_DSS_C35D5_MISC_inst                                                   0x00E6
#define DC_PHY_DSS_C35D5_MISC_data_in_shift                                          (8)
#define DC_PHY_DSS_C35D5_MISC_data_in_mask                                           (0x0FFFFF00)
#define DC_PHY_DSS_C35D5_MISC_data_in(data)                                          (0x0FFFFF00&((data)<<8))
#define DC_PHY_DSS_C35D5_MISC_data_in_src(data)                                      ((0x0FFFFF00&(data))>>8)
#define DC_PHY_DSS_C35D5_MISC_get_data_in(data)                                      ((0x0FFFFF00&(data))>>8)
#define DC_PHY_DSS_C35D5_MISC_speed_en_shift                                         (5)
#define DC_PHY_DSS_C35D5_MISC_speed_en_mask                                          (0x00000020)
#define DC_PHY_DSS_C35D5_MISC_speed_en(data)                                         (0x00000020&((data)<<5))
#define DC_PHY_DSS_C35D5_MISC_speed_en_src(data)                                     ((0x00000020&(data))>>5)
#define DC_PHY_DSS_C35D5_MISC_get_speed_en(data)                                     ((0x00000020&(data))>>5)
#define DC_PHY_DSS_C35D5_MISC_wire_sel_shift                                         (4)
#define DC_PHY_DSS_C35D5_MISC_wire_sel_mask                                          (0x00000010)
#define DC_PHY_DSS_C35D5_MISC_wire_sel(data)                                         (0x00000010&((data)<<4))
#define DC_PHY_DSS_C35D5_MISC_wire_sel_src(data)                                     ((0x00000010&(data))>>4)
#define DC_PHY_DSS_C35D5_MISC_get_wire_sel(data)                                     ((0x00000010&(data))>>4)
#define DC_PHY_DSS_C35D5_MISC_ro_sel_shift                                           (1)
#define DC_PHY_DSS_C35D5_MISC_ro_sel_mask                                            (0x0000000E)
#define DC_PHY_DSS_C35D5_MISC_ro_sel(data)                                           (0x0000000E&((data)<<1))
#define DC_PHY_DSS_C35D5_MISC_ro_sel_src(data)                                       ((0x0000000E&(data))>>1)
#define DC_PHY_DSS_C35D5_MISC_get_ro_sel(data)                                       ((0x0000000E&(data))>>1)
#define DC_PHY_DSS_C35D5_MISC_dss_rst_n_shift                                        (0)
#define DC_PHY_DSS_C35D5_MISC_dss_rst_n_mask                                         (0x00000001)
#define DC_PHY_DSS_C35D5_MISC_dss_rst_n(data)                                        (0x00000001&((data)<<0))
#define DC_PHY_DSS_C35D5_MISC_dss_rst_n_src(data)                                    ((0x00000001&(data))>>0)
#define DC_PHY_DSS_C35D5_MISC_get_dss_rst_n(data)                                    ((0x00000001&(data))>>0)


#define DC_PHY_DSS_C35D5_ST                                                          0x18008f9c
#define DC_PHY_DSS_C35D5_ST_reg_addr                                                 "0xB8008F9C"
#define DC_PHY_DSS_C35D5_ST_reg                                                      0xB8008F9C
#define set_DC_PHY_DSS_C35D5_ST_reg(data)   (*((volatile unsigned int*) DC_PHY_DSS_C35D5_ST_reg)=data)
#define get_DC_PHY_DSS_C35D5_ST_reg   (*((volatile unsigned int*) DC_PHY_DSS_C35D5_ST_reg))
#define DC_PHY_DSS_C35D5_ST_inst_adr                                                 "0x00E7"
#define DC_PHY_DSS_C35D5_ST_inst                                                     0x00E7
#define DC_PHY_DSS_C35D5_ST_count_out_shift                                          (4)
#define DC_PHY_DSS_C35D5_ST_count_out_mask                                           (0x00FFFFF0)
#define DC_PHY_DSS_C35D5_ST_count_out(data)                                          (0x00FFFFF0&((data)<<4))
#define DC_PHY_DSS_C35D5_ST_count_out_src(data)                                      ((0x00FFFFF0&(data))>>4)
#define DC_PHY_DSS_C35D5_ST_get_count_out(data)                                      ((0x00FFFFF0&(data))>>4)
#define DC_PHY_DSS_C35D5_ST_wsort_go_shift                                           (1)
#define DC_PHY_DSS_C35D5_ST_wsort_go_mask                                            (0x00000002)
#define DC_PHY_DSS_C35D5_ST_wsort_go(data)                                           (0x00000002&((data)<<1))
#define DC_PHY_DSS_C35D5_ST_wsort_go_src(data)                                       ((0x00000002&(data))>>1)
#define DC_PHY_DSS_C35D5_ST_get_wsort_go(data)                                       ((0x00000002&(data))>>1)
#define DC_PHY_DSS_C35D5_ST_ready_shift                                              (0)
#define DC_PHY_DSS_C35D5_ST_ready_mask                                               (0x00000001)
#define DC_PHY_DSS_C35D5_ST_ready(data)                                              (0x00000001&((data)<<0))
#define DC_PHY_DSS_C35D5_ST_ready_src(data)                                          ((0x00000001&(data))>>0)
#define DC_PHY_DSS_C35D5_ST_get_ready(data)                                          ((0x00000001&(data))>>0)


#define DC_PHY_DSS_DBG                                                               0x18008fa0
#define DC_PHY_DSS_DBG_reg_addr                                                      "0xB8008FA0"
#define DC_PHY_DSS_DBG_reg                                                           0xB8008FA0
#define set_DC_PHY_DSS_DBG_reg(data)   (*((volatile unsigned int*) DC_PHY_DSS_DBG_reg)=data)
#define get_DC_PHY_DSS_DBG_reg   (*((volatile unsigned int*) DC_PHY_DSS_DBG_reg))
#define DC_PHY_DSS_DBG_inst_adr                                                      "0x00E8"
#define DC_PHY_DSS_DBG_inst                                                          0x00E8
#define DC_PHY_DSS_DBG_dbgo_c35d5_shift                                              (16)
#define DC_PHY_DSS_DBG_dbgo_c35d5_mask                                               (0xFFFF0000)
#define DC_PHY_DSS_DBG_dbgo_c35d5(data)                                              (0xFFFF0000&((data)<<16))
#define DC_PHY_DSS_DBG_dbgo_c35d5_src(data)                                          ((0xFFFF0000&(data))>>16)
#define DC_PHY_DSS_DBG_get_dbgo_c35d5(data)                                          ((0xFFFF0000&(data))>>16)
#define DC_PHY_DSS_DBG_dbgo_c35_shift                                                (0)
#define DC_PHY_DSS_DBG_dbgo_c35_mask                                                 (0x0000FFFF)
#define DC_PHY_DSS_DBG_dbgo_c35(data)                                                (0x0000FFFF&((data)<<0))
#define DC_PHY_DSS_DBG_dbgo_c35_src(data)                                            ((0x0000FFFF&(data))>>0)
#define DC_PHY_DSS_DBG_get_dbgo_c35(data)                                            ((0x0000FFFF&(data))>>0)


#endif
