/**************************************************************
// Spec Version                  : 0.08
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/6/5 15:7:51
***************************************************************/


#ifndef _DC_SYS_REG_H_INCLUDED_
#define _DC_SYS_REG_H_INCLUDED_
#ifdef  _DC_SYS_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     pict_width_scale:6;
unsigned int     pict_init_page:17;
}DC_PICT_SET;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     dram_8g_used:1;
unsigned int     dram_4g_used:1;
unsigned int     ddr3_512_used:1;
unsigned int     dram_2g_used:1;
unsigned int     pre_arb_scheme_sel:1;
unsigned int     ve_cmd_grp_disable:1;
unsigned int     ddr3_mapping_en:1;
unsigned int     reserved_1:1;
unsigned int     self_lookback_mode:1;
unsigned int     mem_num:1;
unsigned int     reserved_2:1;
unsigned int     page_size:2;
unsigned int     pre_arb_rd_cnt:8;
unsigned int     pre_arb_wr_cnt:8;
}DC_SYS_MISC;

typedef struct 
{
unsigned int     scpu_pri:4;
unsigned int     mipi_pri:4;
unsigned int     reserved_0:4;
unsigned int     vo_high_pri:4;
unsigned int     reserved_1:4;
unsigned int     sb1_high_pri:4;
unsigned int     reserved_2:4;
unsigned int     sb0_pri:4;
}PRIORITY_CTRL_0;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     sb3_high_pri:4;
unsigned int     reserved_1:4;
unsigned int     vo_low_pri:4;
unsigned int     reserved_2:4;
unsigned int     sb1_low_pri:4;
unsigned int     reserved_3:4;
unsigned int     avk_cpu_pri:4;
}PRIORITY_CTRL_1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     gde_pri:4;
unsigned int     reserved_1:4;
unsigned int     se_pri:4;
unsigned int     reserved_2:4;
unsigned int     sb3_low_pri:4;
unsigned int     reserved_3:4;
unsigned int     ve_pri:4;
}PRIORITY_CTRL_2;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     vo_low_tag:2;
unsigned int     reserved_1:2;
unsigned int     sb1_low_tag:2;
unsigned int     reserved_2:2;
unsigned int     se_tag:2;
unsigned int     reserved_3:2;
unsigned int     avk_cpu_tag:2;
unsigned int     reserved_4:2;
unsigned int     ve_tag:2;
}REORDER_CTRL_0;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     sb0_tag:2;
unsigned int     reserved_1:2;
unsigned int     sb1_high_tag:2;
unsigned int     reserved_2:2;
unsigned int     vo_high_tag:2;
unsigned int     reserved_3:2;
unsigned int     sb3_high_tag:2;
unsigned int     reserved_4:2;
unsigned int     sb3_low_tag:2;
}REORDER_CTRL_1;

typedef struct 
{
unsigned int     split_wait:4;
unsigned int     arbit_los:4;
unsigned int     reserved_0:1;
unsigned int     short_lxy:7;
unsigned int     live_split:8;
unsigned int     reserved_1:6;
unsigned int     live_cflit:1;
unsigned int     queue_flush:1;
}DC_PROS_CTRL;

typedef struct 
{
unsigned int     pict_set_num:8;
unsigned int     pict_offset_rd:1;
unsigned int     reserved_0:3;
unsigned int     pict_set_offset_y:10;
unsigned int     pict_set_offset_x:10;
}DC_PICT_SET_OFFSET;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     req_pending:1;
unsigned int     req_id:11;
}DC_REQ_STATUS;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     qfifo_cnt_full_threshold:5;
unsigned int     full_cmd_count:4;
unsigned int     pre_tra_rd_cnt:10;
unsigned int     pre_tra_wr_cnt:10;
}DC_SYS_MISC2;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     gpu_wdata_queue_flush:1;
unsigned int     reserved_1:1;
unsigned int     reserved_2:1;
unsigned int     reserved_3:1;
unsigned int     enable_arb_delay_by_tv_sb1_grant:1;
unsigned int     gpu_cmd_queue_flush:1;
unsigned int     gde_cmd_grp_disable:1;
}DC_SYS_MISC3;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     pc_go:1;
}DC_PC_CTRL;

typedef struct 
{
unsigned int     pc_tota_mon_num:32;
}DC_PC_TOTA_MON_NUM;

typedef struct 
{
unsigned int     pc_tota_ack_num:32;
}DC_PC_TOTA_ACK_NUM;

typedef struct 
{
unsigned int     pc_tota_idl_num:32;
}DC_PC_TOTA_IDL_NUM;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en_3:1;
unsigned int     pc_sysh_prog2_sel:7;
unsigned int     reserved_1:1;
unsigned int     write_en_2:1;
unsigned int     pc_sysh_prog1_sel:7;
unsigned int     reserved_2:1;
unsigned int     write_en_1:1;
unsigned int     pc_sysh_prog0_sel:7;
}DC_PC_SYSH_PROG_CTRL;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en_3:1;
unsigned int     pc_sys_prog2_sel:7;
unsigned int     reserved_1:1;
unsigned int     write_en_2:1;
unsigned int     pc_sys_prog1_sel:7;
unsigned int     reserved_2:1;
unsigned int     write_en_1:1;
unsigned int     pc_sys_prog0_sel:7;
}DC_PC_SYS_PROG_CTRL;

typedef struct 
{
unsigned int     sysh_prog0_acc_lat:32;
}DC_PC_SYSH_PROG_0_ACC_LAT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     sysh_prog0_max_lat:16;
}DC_PC_SYSH_PROG_0_MAX_LAT;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     sysh_prog0_req_num:24;
}DC_PC_SYSH_PROG_0_REQ_NUM;

typedef struct 
{
unsigned int     sysh_prog0_ack_num:32;
}DC_PC_SYSH_PROG_0_ACK_NUM;

typedef struct 
{
unsigned int     sysh_prog1_acc_lat:32;
}DC_PC_SYSH_PROG_1_ACC_LAT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     sysh_prog1_max_lat:16;
}DC_PC_SYSH_PROG_1_MAX_LAT;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     sysh_prog1_req_num:24;
}DC_PC_SYSH_PROG_1_REQ_NUM;

typedef struct 
{
unsigned int     sysh_prog1_ack_num:32;
}DC_PC_SYSH_PROG_1_ACK_NUM;

typedef struct 
{
unsigned int     sysh_prog2_acc_lat:32;
}DC_PC_SYSH_PROG_2_ACC_LAT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     sysh_prog2_max_lat:16;
}DC_PC_SYSH_PROG_2_MAX_LAT;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     sysh_prog2_req_num:24;
}DC_PC_SYSH_PROG_2_REQ_NUM;

typedef struct 
{
unsigned int     sysh_prog2_ack_num:32;
}DC_PC_SYSH_PROG_2_ACK_NUM;

typedef struct 
{
unsigned int     sys_prog0_acc_lat:32;
}DC_PC_SYS_PROG_0_ACC_LAT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     sys_prog0_max_lat:16;
}DC_PC_SYS_PROG_0_MAX_LAT;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     sys_prog0_req_num:24;
}DC_PC_SYS_PROG_0_REQ_NUM;

typedef struct 
{
unsigned int     sys_prog0_ack_num:32;
}DC_PC_SYS_PROG_0_ACK_NUM;

typedef struct 
{
unsigned int     sys_prog1_acc_lat:32;
}DC_PC_SYS_PROG_1_ACC_LAT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     sys_prog1_max_lat:16;
}DC_PC_SYS_PROG_1_MAX_LAT;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     sys_prog1_req_num:24;
}DC_PC_SYS_PROG_1_REQ_NUM;

typedef struct 
{
unsigned int     sys_prog1_ack_num:32;
}DC_PC_SYS_PROG_1_ACK_NUM;

typedef struct 
{
unsigned int     sys_prog2_acc_lat:32;
}DC_PC_SYS_PROG_2_ACC_LAT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     sys_prog2_max_lat:16;
}DC_PC_SYS_PROG_2_MAX_LAT;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     sys_prog2_req_num:24;
}DC_PC_SYS_PROG_2_REQ_NUM;

typedef struct 
{
unsigned int     sys_prog2_ack_num:32;
}DC_PC_SYS_PROG_2_ACK_NUM;

typedef struct 
{
unsigned int     sfmode_pattern0:32;
}SFMODE_PATTERN0;

typedef struct 
{
unsigned int     sfmode_pattern1:32;
}SFMODE_PATTERN1;

typedef struct 
{
unsigned int     sfmode_pattern2:32;
}SFMODE_PATTERN2;

typedef struct 
{
unsigned int     sfmode_pattern3:32;
}SFMODE_PATTERN3;

typedef struct 
{
unsigned int     sfmode_cmp_rlt0:32;
}SFMODE_CMP_RLT0;

typedef struct 
{
unsigned int     sfmode_cmp_rlt1:32;
}SFMODE_CMP_RLT1;

typedef struct 
{
unsigned int     sfmode_cmp_rlt2:32;
}SFMODE_CMP_RLT2;

typedef struct 
{
unsigned int     sfmode_cmp_rlt3:32;
}SFMODE_CMP_RLT3;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     disable_2nd_channel:1;
unsigned int     full_transfer:1;
}DC_64_WRITE_BUF_CTRL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     sync_cmd_cnt_threshold:3;
unsigned int     cmd_buf_threshold:4;
unsigned int     disable_2nd_channel:1;
unsigned int     ever_full:1;
unsigned int     ever_reach_threshold:1;
unsigned int     max_buf_level:7;
unsigned int     grant_stop_level:7;
}DC_64_READ_BUF_CTRL;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     pict_set_int_cpu:2;
unsigned int     int_enable:1;
unsigned int     ever_set_as_odd:1;
unsigned int     enable:1;
}DC_PIC_OFFSET_X_DETECTION;

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
}PHY_BIST_RM;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     mbist_st:1;
unsigned int     bist_fail:1;
unsigned int     bist_done:1;
}PHY_BIST0_ST;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     drf_start_pause:1;
unsigned int     reserved_1:14;
unsigned int     drf_fail:1;
unsigned int     drf_done:1;
}PHY_DRF0_ST;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     mbist_st:1;
unsigned int     bist_fail:1;
unsigned int     bist_done:1;
}PHY_BIST1_ST;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     drf_start_pause:1;
unsigned int     reserved_1:14;
unsigned int     drf_fail:1;
unsigned int     drf_done:1;
}PHY_DRF1_ST;

typedef struct 
{
unsigned int     bist_en_0:1;
unsigned int     drf_bist_en_0:1;
unsigned int     drf_test_resume_0:1;
unsigned int     bist_en_1:1;
unsigned int     drf_bist_en_1:1;
unsigned int     drf_test_resume_1:1;
unsigned int     reserved_0:5;
unsigned int     DVSE_A:1;
unsigned int     DVS_A_3:1;
unsigned int     DVS_A_2:1;
unsigned int     DVS_A_1:1;
unsigned int     DVS_A_0:1;
unsigned int     reserved_1:8;
unsigned int     reserved_2:3;
unsigned int     DVSE:1;
unsigned int     DVS_3:1;
unsigned int     DVS_2:1;
unsigned int     DVS_1:1;
unsigned int     DVS_0:1;
}BIST_RM;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     mbist_st:1;
unsigned int     bist_fail1:1;
unsigned int     bist_fail0:1;
unsigned int     bist_done:1;
}BIST0_ST;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     drf_start_pause:1;
unsigned int     reserved_1:13;
unsigned int     drf_fail1:1;
unsigned int     drf_fail0:1;
unsigned int     drf_done:1;
}DRF0_ST;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     mbist_st:1;
unsigned int     bist_fail0:1;
unsigned int     bist_done:1;
}BIST1_ST;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     drf_start_pause:1;
unsigned int     reserved_1:14;
unsigned int     drf_fail0:1;
unsigned int     drf_done:1;
}DRF1_ST;

typedef struct 
{
unsigned int     dummy_reg0:32;
}DUMMY_REG0;

typedef struct 
{
unsigned int     dummy_reg1:32;
}DUMMY_REG1;

typedef struct 
{
unsigned int     dummy_reg2:32;
}DUMMY_REG2;

typedef struct 
{
unsigned int     dummy_reg3:32;
}DUMMY_REG3;

typedef struct 
{
unsigned int     mem_type:2;
unsigned int     saddr:26;
unsigned int     reserved_0:4;
}DC_MT_SADDR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     eaddr:26;
unsigned int     reserved_1:5;
}DC_MT_EADDR;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_enable0:1;
unsigned int     access_type_0:2;
unsigned int     access_type_1:2;
unsigned int     access_type_2:2;
unsigned int     access_type_3:2;
unsigned int     write_enable1:1;
unsigned int     int1:1;
unsigned int     write_enable2:1;
unsigned int     int2:1;
unsigned int     write_enable3:1;
unsigned int     int3:1;
unsigned int     write_enable4:1;
unsigned int     cpu:2;
unsigned int     int1_en:1;
unsigned int     int2_en:1;
unsigned int     int3_en:1;
unsigned int     write_enable5:1;
unsigned int     mode:2;
}DC_MT_MODE;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     module_ID_0:7;
unsigned int     module_ID_1:7;
unsigned int     module_ID_2:7;
unsigned int     module_ID_3:7;
}DC_MT_TABLE;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     ever_trap:1;
unsigned int     module_ID:7;
unsigned int     addcmd:14;
}DC_MT_ADDCMD_HI;

typedef struct 
{
unsigned int     addcmd:32;
}DC_MT_ADDCMD_LO;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     enable_block_info:1;
unsigned int     disable_cross_range_check:1;
}DC_MT_MISC;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     write_enable4:1;
unsigned int     error_cmd_int_cpu:2;
unsigned int     write_enable3:1;
unsigned int     error_cmd_int_en:1;
unsigned int     write_enable2:1;
unsigned int     error_cmd_swap_en:1;
unsigned int     write_enable1:1;
unsigned int     error_cmd_detection_en:1;
}DC_EC_CTRL;

typedef struct 
{
unsigned int     error_cmd_int:1;
unsigned int     error_cmd_ever_trap:1;
unsigned int     trap_case:8;
unsigned int     Addcmd_hi:22;
}DC_EC_ADDCMD_HI;

typedef struct 
{
unsigned int     Addcmd_lo:32;
}DC_EC_ADDCMD_LO;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     write_enable3:1;
unsigned int     tag_check_int_cpu:2;
unsigned int     write_enable2:1;
unsigned int     tag_check_int_en:1;
unsigned int     write_enable1:1;
unsigned int     tag_check_en:1;
}DC_RD_TAG_CHECK;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     rd_tag_mismatch_ever:1;
unsigned int     rd_tag_mismatch_int:1;
}DC_RD_TAG_CHECK_ST;

typedef struct 
{
unsigned int     write_enable0:1;
unsigned int     rd_only_0_sel:1;
unsigned int     blk_protect_0_sel:1;
unsigned int     protect_0_sel:1;
unsigned int     write_enable1:1;
unsigned int     rd_only_3_en:1;
unsigned int     rd_only_2_en:1;
unsigned int     rd_only_1_en:1;
unsigned int     rd_only_0_en:1;
unsigned int     write_enable2:1;
unsigned int     blk_protect_1_wpro_en:1;
unsigned int     blk_protect_0_wpro_en:1;
unsigned int     blk_protect_1_en:1;
unsigned int     blk_protect_0_en:1;
unsigned int     write_enable3:1;
unsigned int     protect_7_wpro_en:1;
unsigned int     protect_6_wpro_en:1;
unsigned int     protect_5_wpro_en:1;
unsigned int     protect_4_wpro_en:1;
unsigned int     protect_3_wpro_en:1;
unsigned int     protect_2_wpro_en:1;
unsigned int     protect_1_wpro_en:1;
unsigned int     protect_0_wpro_en:1;
unsigned int     write_enable4:1;
unsigned int     protect_7_en:1;
unsigned int     protect_6_en:1;
unsigned int     protect_5_en:1;
unsigned int     protect_4_en:1;
unsigned int     protect_3_en:1;
unsigned int     protect_2_en:1;
unsigned int     protect_1_en:1;
unsigned int     protect_0_en:1;
}DC_MEM_PROTECT_CTRL;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     y_limit:1;
unsigned int     bank_remap_enable:1;
unsigned int     tp_scramble_en:1;
unsigned int     video_dec_scramble_en:1;
unsigned int     audio_scramble_en:1;
unsigned int     scpu_scramble_en:1;
unsigned int     scramble_all_en:1;
unsigned int     scramble_7_en:1;
unsigned int     scramble_6_en:1;
unsigned int     scramble_5_en:1;
unsigned int     scramble_4_en:1;
unsigned int     scramble_3_en:1;
unsigned int     scramble_2_en:1;
unsigned int     scramble_1_en:1;
unsigned int     scramble_0_en:1;
}DC_MEM_SCRAMBLE_CTRL;

typedef struct 
{
unsigned int     saddr0:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_SADDR0;

typedef struct 
{
unsigned int     eaddr0:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_EADDR0;

typedef struct 
{
unsigned int     saddr1:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_SADDR1;

typedef struct 
{
unsigned int     eaddr1:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_EADDR1;

typedef struct 
{
unsigned int     saddr2:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_SADDR2;

typedef struct 
{
unsigned int     eaddr2:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_EADDR2;

typedef struct 
{
unsigned int     saddr3:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_SADDR3;

typedef struct 
{
unsigned int     eaddr3:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_EADDR3;

typedef struct 
{
unsigned int     saddr4:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_SADDR4;

typedef struct 
{
unsigned int     eaddr4:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_EADDR4;

typedef struct 
{
unsigned int     saddr5:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_SADDR5;

typedef struct 
{
unsigned int     eaddr5:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_EADDR5;

typedef struct 
{
unsigned int     saddr6:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_SADDR6;

typedef struct 
{
unsigned int     eaddr6:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_EADDR6;

typedef struct 
{
unsigned int     saddr7:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_SADDR7;

typedef struct 
{
unsigned int     eaddr7:20;
unsigned int     reserved_0:12;
}DC_MEM_PROTECT_EADDR7;

typedef struct 
{
unsigned int     saddr0:20;
unsigned int     reserved_0:12;
}DC_BLK_PROTECT_SADDR0;

typedef struct 
{
unsigned int     eaddr0:20;
unsigned int     reserved_0:12;
}DC_BLK_PROTECT_EADDR0;

typedef struct 
{
unsigned int     saddr1:20;
unsigned int     reserved_0:12;
}DC_BLK_PROTECT_SADDR1;

typedef struct 
{
unsigned int     eaddr1:20;
unsigned int     reserved_0:12;
}DC_BLK_PROTECT_EADDR1;

typedef struct 
{
unsigned int     saddr0:20;
unsigned int     reserved_0:12;
}DC_RO_PROTECT_SADDR0;

typedef struct 
{
unsigned int     eaddr0:20;
unsigned int     reserved_0:12;
}DC_RO_PROTECT_EADDR0;

typedef struct 
{
unsigned int     saddr1:20;
unsigned int     reserved_0:12;
}DC_RO_PROTECT_SADDR1;

typedef struct 
{
unsigned int     eaddr1:20;
unsigned int     reserved_0:12;
}DC_RO_PROTECT_EADDR1;

typedef struct 
{
unsigned int     saddr2:20;
unsigned int     reserved_0:12;
}DC_RO_PROTECT_SADDR2;

typedef struct 
{
unsigned int     eaddr2:20;
unsigned int     reserved_0:12;
}DC_RO_PROTECT_EADDR2;

typedef struct 
{
unsigned int     saddr3:20;
unsigned int     reserved_0:12;
}DC_RO_PROTECT_SADDR3;

typedef struct 
{
unsigned int     eaddr3:20;
unsigned int     reserved_0:12;
}DC_RO_PROTECT_EADDR3;

typedef struct 
{
unsigned int     saddr0:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_SADDR0;

typedef struct 
{
unsigned int     eaddr0:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_EADDR0;

typedef struct 
{
unsigned int     saddr1:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_SADDR1;

typedef struct 
{
unsigned int     eaddr1:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_EADDR1;

typedef struct 
{
unsigned int     saddr2:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_SADDR2;

typedef struct 
{
unsigned int     eaddr2:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_EADDR2;

typedef struct 
{
unsigned int     saddr3:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_SADDR3;

typedef struct 
{
unsigned int     eaddr3:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_EADDR3;

typedef struct 
{
unsigned int     saddr4:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_SADDR4;

typedef struct 
{
unsigned int     eaddr4:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_EADDR4;

typedef struct 
{
unsigned int     saddr5:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_SADDR5;

typedef struct 
{
unsigned int     eaddr5:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_EADDR5;

typedef struct 
{
unsigned int     saddr6:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_SADDR6;

typedef struct 
{
unsigned int     eaddr6:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_EADDR6;

typedef struct 
{
unsigned int     saddr7:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_SADDR7;

typedef struct 
{
unsigned int     eaddr7:20;
unsigned int     reserved_0:12;
}DC_MEM_SCRAMBLE_EADDR7;

typedef struct 
{
unsigned int     md_tee_protect_en:8;
unsigned int     cp_tee_protect_en:8;
unsigned int     vo_protect_en:8;
unsigned int     nf_tee_protect_en:8;
}DC_MEM_PROTECT_ID_CTRL_0;

typedef struct 
{
unsigned int     scpu_tee_protect_en:8;
unsigned int     acpu_protect_en:8;
unsigned int     video_protect_en:8;
unsigned int     audio_protect_en:8;
}DC_MEM_PROTECT_ID_CTRL_1;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     scpu_tee_blk_protect_en:2;
unsigned int     acpu_blk_protect_en:2;
unsigned int     video_blk_protect_en:2;
unsigned int     audio_blk_protect_en:2;
unsigned int     md_tee_blk_protect_en:2;
unsigned int     cp_tee_blk_protect_en:2;
unsigned int     vo_blk_protect_en:2;
unsigned int     nf_tee_blk_protect_en:2;
}DC_MEM_PROTECT_ID_CTRL_2;

typedef struct 
{
unsigned int     scpu_tee_ro_protect_en:4;
unsigned int     acpu_ro_protect_en:4;
unsigned int     video_ro_protect_en:4;
unsigned int     audio_ro_protect_en:4;
unsigned int     md_tee_ro_protect_en:4;
unsigned int     cp_tee_ro_protect_en:4;
unsigned int     vo_ro_protect_en:4;
unsigned int     nf_tee_ro_protect_en:4;
}DC_MEM_PROTECT_ID_CTRL_3;

typedef struct 
{
unsigned int     blk_pict_set_chk_en_0:32;
}DC_MEM_PROTECT_PICT_CTRL_0;

typedef struct 
{
unsigned int     blk_pict_set_chk_en_1:32;
}DC_MEM_PROTECT_PICT_CTRL_1;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     dram_16g_used:1;
unsigned int     dram_8g_used:1;
unsigned int     dram_4g_used:1;
unsigned int     dram_2g_used:1;
unsigned int     dram_1g_used:1;
unsigned int     dram_512_used:1;
}DC_SECURE_MISC;

typedef struct 
{
unsigned int     write_enable9:1;
unsigned int     int_kcpu_key_up_en:1;
unsigned int     write_enable8:1;
unsigned int     int_kcpu_key_up:1;
unsigned int     write_enable7:1;
unsigned int     key_up_status:3;
unsigned int     write_enable6:1;
unsigned int     scramble_int_en:1;
unsigned int     write_enable5:1;
unsigned int     scramble_int:1;
unsigned int     write_enable4:1;
unsigned int     scramble_id:7;
unsigned int     write_enable3:1;
unsigned int     protect_int_en:1;
unsigned int     write_enable2:1;
unsigned int     protect_int:1;
unsigned int     write_enable1:1;
unsigned int     protect_id:7;
}DC_MEM_INT;

typedef struct 
{
unsigned int     write_enable10:1;
unsigned int     x_overflow_int_en:1;
unsigned int     write_enable9:1;
unsigned int     x_overflow_int:1;
unsigned int     write_enable8:1;
unsigned int     y_overflow_int_en:1;
unsigned int     write_enable7:1;
unsigned int     y_overflow_int:1;
unsigned int     write_enable6:1;
unsigned int     scramble_align_int_en:1;
unsigned int     write_enable5:1;
unsigned int     scramble_align_int:1;
unsigned int     write_enable4:1;
unsigned int     blk_picset_int_en:1;
unsigned int     write_enable3:1;
unsigned int     blk_picset_int:1;
unsigned int     reserved_0:3;
unsigned int     write_enable2:1;
unsigned int     region:3;
unsigned int     write_enable1:1;
unsigned int     pict_set_num:8;
}DC_MEM_OTHER_INT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     blk_overflow_k_en:1;
unsigned int     blk_overflow_s_en:1;
unsigned int     blk_protect_k_en:1;
unsigned int     blk_protect_s_en:1;
unsigned int     error_k_en:1;
unsigned int     error_s_en:1;
unsigned int     mem_trash_k_en:1;
unsigned int     mem_trash_s_en:1;
}DC_INT_SEL;

#endif

#define DC_PICT_SET                                                                  0x18008000
#define DC_PICT_SET_reg_addr                                                         "0xB8008000"
#define DC_PICT_SET_reg                                                              0xB8008000
#define set_DC_PICT_SET_reg(data)   (*((volatile unsigned int*) DC_PICT_SET_reg)=data)
#define get_DC_PICT_SET_reg   (*((volatile unsigned int*) DC_PICT_SET_reg))
#define DC_PICT_SET_inst_adr                                                         "0x0000"
#define DC_PICT_SET_inst                                                             0x0000
#define DC_PICT_SET_pict_width_scale_shift                                           (17)
#define DC_PICT_SET_pict_width_scale_mask                                            (0x007E0000)
#define DC_PICT_SET_pict_width_scale(data)                                           (0x007E0000&((data)<<17))
#define DC_PICT_SET_pict_width_scale_src(data)                                       ((0x007E0000&(data))>>17)
#define DC_PICT_SET_get_pict_width_scale(data)                                       ((0x007E0000&(data))>>17)
#define DC_PICT_SET_pict_init_page_shift                                             (0)
#define DC_PICT_SET_pict_init_page_mask                                              (0x0001FFFF)
#define DC_PICT_SET_pict_init_page(data)                                             (0x0001FFFF&((data)<<0))
#define DC_PICT_SET_pict_init_page_src(data)                                         ((0x0001FFFF&(data))>>0)
#define DC_PICT_SET_get_pict_init_page(data)                                         ((0x0001FFFF&(data))>>0)


#define DC_SYS_MISC                                                                  0x18008004
#define DC_SYS_MISC_reg_addr                                                         "0xB8008004"
#define DC_SYS_MISC_reg                                                              0xB8008004
#define set_DC_SYS_MISC_reg(data)   (*((volatile unsigned int*) DC_SYS_MISC_reg)=data)
#define get_DC_SYS_MISC_reg   (*((volatile unsigned int*) DC_SYS_MISC_reg))
#define DC_SYS_MISC_inst_adr                                                         "0x0001"
#define DC_SYS_MISC_inst                                                             0x0001
#define DC_SYS_MISC_dram_8g_used_shift                                               (28)
#define DC_SYS_MISC_dram_8g_used_mask                                                (0x10000000)
#define DC_SYS_MISC_dram_8g_used(data)                                               (0x10000000&((data)<<28))
#define DC_SYS_MISC_dram_8g_used_src(data)                                           ((0x10000000&(data))>>28)
#define DC_SYS_MISC_get_dram_8g_used(data)                                           ((0x10000000&(data))>>28)
#define DC_SYS_MISC_dram_4g_used_shift                                               (27)
#define DC_SYS_MISC_dram_4g_used_mask                                                (0x08000000)
#define DC_SYS_MISC_dram_4g_used(data)                                               (0x08000000&((data)<<27))
#define DC_SYS_MISC_dram_4g_used_src(data)                                           ((0x08000000&(data))>>27)
#define DC_SYS_MISC_get_dram_4g_used(data)                                           ((0x08000000&(data))>>27)
#define DC_SYS_MISC_ddr3_512_used_shift                                              (26)
#define DC_SYS_MISC_ddr3_512_used_mask                                               (0x04000000)
#define DC_SYS_MISC_ddr3_512_used(data)                                              (0x04000000&((data)<<26))
#define DC_SYS_MISC_ddr3_512_used_src(data)                                          ((0x04000000&(data))>>26)
#define DC_SYS_MISC_get_ddr3_512_used(data)                                          ((0x04000000&(data))>>26)
#define DC_SYS_MISC_dram_2g_used_shift                                               (25)
#define DC_SYS_MISC_dram_2g_used_mask                                                (0x02000000)
#define DC_SYS_MISC_dram_2g_used(data)                                               (0x02000000&((data)<<25))
#define DC_SYS_MISC_dram_2g_used_src(data)                                           ((0x02000000&(data))>>25)
#define DC_SYS_MISC_get_dram_2g_used(data)                                           ((0x02000000&(data))>>25)
#define DC_SYS_MISC_pre_arb_scheme_sel_shift                                         (24)
#define DC_SYS_MISC_pre_arb_scheme_sel_mask                                          (0x01000000)
#define DC_SYS_MISC_pre_arb_scheme_sel(data)                                         (0x01000000&((data)<<24))
#define DC_SYS_MISC_pre_arb_scheme_sel_src(data)                                     ((0x01000000&(data))>>24)
#define DC_SYS_MISC_get_pre_arb_scheme_sel(data)                                     ((0x01000000&(data))>>24)
#define DC_SYS_MISC_ve_cmd_grp_disable_shift                                         (23)
#define DC_SYS_MISC_ve_cmd_grp_disable_mask                                          (0x00800000)
#define DC_SYS_MISC_ve_cmd_grp_disable(data)                                         (0x00800000&((data)<<23))
#define DC_SYS_MISC_ve_cmd_grp_disable_src(data)                                     ((0x00800000&(data))>>23)
#define DC_SYS_MISC_get_ve_cmd_grp_disable(data)                                     ((0x00800000&(data))>>23)
#define DC_SYS_MISC_ddr3_mapping_en_shift                                            (22)
#define DC_SYS_MISC_ddr3_mapping_en_mask                                             (0x00400000)
#define DC_SYS_MISC_ddr3_mapping_en(data)                                            (0x00400000&((data)<<22))
#define DC_SYS_MISC_ddr3_mapping_en_src(data)                                        ((0x00400000&(data))>>22)
#define DC_SYS_MISC_get_ddr3_mapping_en(data)                                        ((0x00400000&(data))>>22)
#define DC_SYS_MISC_self_lookback_mode_shift                                         (20)
#define DC_SYS_MISC_self_lookback_mode_mask                                          (0x00100000)
#define DC_SYS_MISC_self_lookback_mode(data)                                         (0x00100000&((data)<<20))
#define DC_SYS_MISC_self_lookback_mode_src(data)                                     ((0x00100000&(data))>>20)
#define DC_SYS_MISC_get_self_lookback_mode(data)                                     ((0x00100000&(data))>>20)
#define DC_SYS_MISC_mem_num_shift                                                    (19)
#define DC_SYS_MISC_mem_num_mask                                                     (0x00080000)
#define DC_SYS_MISC_mem_num(data)                                                    (0x00080000&((data)<<19))
#define DC_SYS_MISC_mem_num_src(data)                                                ((0x00080000&(data))>>19)
#define DC_SYS_MISC_get_mem_num(data)                                                ((0x00080000&(data))>>19)
#define DC_SYS_MISC_page_size_shift                                                  (16)
#define DC_SYS_MISC_page_size_mask                                                   (0x00030000)
#define DC_SYS_MISC_page_size(data)                                                  (0x00030000&((data)<<16))
#define DC_SYS_MISC_page_size_src(data)                                              ((0x00030000&(data))>>16)
#define DC_SYS_MISC_get_page_size(data)                                              ((0x00030000&(data))>>16)
#define DC_SYS_MISC_pre_arb_rd_cnt_shift                                             (8)
#define DC_SYS_MISC_pre_arb_rd_cnt_mask                                              (0x0000FF00)
#define DC_SYS_MISC_pre_arb_rd_cnt(data)                                             (0x0000FF00&((data)<<8))
#define DC_SYS_MISC_pre_arb_rd_cnt_src(data)                                         ((0x0000FF00&(data))>>8)
#define DC_SYS_MISC_get_pre_arb_rd_cnt(data)                                         ((0x0000FF00&(data))>>8)
#define DC_SYS_MISC_pre_arb_wr_cnt_shift                                             (0)
#define DC_SYS_MISC_pre_arb_wr_cnt_mask                                              (0x000000FF)
#define DC_SYS_MISC_pre_arb_wr_cnt(data)                                             (0x000000FF&((data)<<0))
#define DC_SYS_MISC_pre_arb_wr_cnt_src(data)                                         ((0x000000FF&(data))>>0)
#define DC_SYS_MISC_get_pre_arb_wr_cnt(data)                                         ((0x000000FF&(data))>>0)


#define PRIORITY_CTRL_0                                                              0x18008008
#define PRIORITY_CTRL_0_reg_addr                                                     "0xB8008008"
#define PRIORITY_CTRL_0_reg                                                          0xB8008008
#define set_PRIORITY_CTRL_0_reg(data)   (*((volatile unsigned int*) PRIORITY_CTRL_0_reg)=data)
#define get_PRIORITY_CTRL_0_reg   (*((volatile unsigned int*) PRIORITY_CTRL_0_reg))
#define PRIORITY_CTRL_0_inst_adr                                                     "0x0002"
#define PRIORITY_CTRL_0_inst                                                         0x0002
#define PRIORITY_CTRL_0_scpu_pri_shift                                               (28)
#define PRIORITY_CTRL_0_scpu_pri_mask                                                (0xF0000000)
#define PRIORITY_CTRL_0_scpu_pri(data)                                               (0xF0000000&((data)<<28))
#define PRIORITY_CTRL_0_scpu_pri_src(data)                                           ((0xF0000000&(data))>>28)
#define PRIORITY_CTRL_0_get_scpu_pri(data)                                           ((0xF0000000&(data))>>28)
#define PRIORITY_CTRL_0_mipi_pri_shift                                               (24)
#define PRIORITY_CTRL_0_mipi_pri_mask                                                (0x0F000000)
#define PRIORITY_CTRL_0_mipi_pri(data)                                               (0x0F000000&((data)<<24))
#define PRIORITY_CTRL_0_mipi_pri_src(data)                                           ((0x0F000000&(data))>>24)
#define PRIORITY_CTRL_0_get_mipi_pri(data)                                           ((0x0F000000&(data))>>24)
#define PRIORITY_CTRL_0_vo_high_pri_shift                                            (16)
#define PRIORITY_CTRL_0_vo_high_pri_mask                                             (0x000F0000)
#define PRIORITY_CTRL_0_vo_high_pri(data)                                            (0x000F0000&((data)<<16))
#define PRIORITY_CTRL_0_vo_high_pri_src(data)                                        ((0x000F0000&(data))>>16)
#define PRIORITY_CTRL_0_get_vo_high_pri(data)                                        ((0x000F0000&(data))>>16)
#define PRIORITY_CTRL_0_sb1_high_pri_shift                                           (8)
#define PRIORITY_CTRL_0_sb1_high_pri_mask                                            (0x00000F00)
#define PRIORITY_CTRL_0_sb1_high_pri(data)                                           (0x00000F00&((data)<<8))
#define PRIORITY_CTRL_0_sb1_high_pri_src(data)                                       ((0x00000F00&(data))>>8)
#define PRIORITY_CTRL_0_get_sb1_high_pri(data)                                       ((0x00000F00&(data))>>8)
#define PRIORITY_CTRL_0_sb0_pri_shift                                                (0)
#define PRIORITY_CTRL_0_sb0_pri_mask                                                 (0x0000000F)
#define PRIORITY_CTRL_0_sb0_pri(data)                                                (0x0000000F&((data)<<0))
#define PRIORITY_CTRL_0_sb0_pri_src(data)                                            ((0x0000000F&(data))>>0)
#define PRIORITY_CTRL_0_get_sb0_pri(data)                                            ((0x0000000F&(data))>>0)


#define PRIORITY_CTRL_1                                                              0x1800800C
#define PRIORITY_CTRL_1_reg_addr                                                     "0xB800800C"
#define PRIORITY_CTRL_1_reg                                                          0xB800800C
#define set_PRIORITY_CTRL_1_reg(data)   (*((volatile unsigned int*) PRIORITY_CTRL_1_reg)=data)
#define get_PRIORITY_CTRL_1_reg   (*((volatile unsigned int*) PRIORITY_CTRL_1_reg))
#define PRIORITY_CTRL_1_inst_adr                                                     "0x0003"
#define PRIORITY_CTRL_1_inst                                                         0x0003
#define PRIORITY_CTRL_1_sb3_high_pri_shift                                           (24)
#define PRIORITY_CTRL_1_sb3_high_pri_mask                                            (0x0F000000)
#define PRIORITY_CTRL_1_sb3_high_pri(data)                                           (0x0F000000&((data)<<24))
#define PRIORITY_CTRL_1_sb3_high_pri_src(data)                                       ((0x0F000000&(data))>>24)
#define PRIORITY_CTRL_1_get_sb3_high_pri(data)                                       ((0x0F000000&(data))>>24)
#define PRIORITY_CTRL_1_vo_low_pri_shift                                             (16)
#define PRIORITY_CTRL_1_vo_low_pri_mask                                              (0x000F0000)
#define PRIORITY_CTRL_1_vo_low_pri(data)                                             (0x000F0000&((data)<<16))
#define PRIORITY_CTRL_1_vo_low_pri_src(data)                                         ((0x000F0000&(data))>>16)
#define PRIORITY_CTRL_1_get_vo_low_pri(data)                                         ((0x000F0000&(data))>>16)
#define PRIORITY_CTRL_1_sb1_low_pri_shift                                            (8)
#define PRIORITY_CTRL_1_sb1_low_pri_mask                                             (0x00000F00)
#define PRIORITY_CTRL_1_sb1_low_pri(data)                                            (0x00000F00&((data)<<8))
#define PRIORITY_CTRL_1_sb1_low_pri_src(data)                                        ((0x00000F00&(data))>>8)
#define PRIORITY_CTRL_1_get_sb1_low_pri(data)                                        ((0x00000F00&(data))>>8)
#define PRIORITY_CTRL_1_avk_cpu_pri_shift                                            (0)
#define PRIORITY_CTRL_1_avk_cpu_pri_mask                                             (0x0000000F)
#define PRIORITY_CTRL_1_avk_cpu_pri(data)                                            (0x0000000F&((data)<<0))
#define PRIORITY_CTRL_1_avk_cpu_pri_src(data)                                        ((0x0000000F&(data))>>0)
#define PRIORITY_CTRL_1_get_avk_cpu_pri(data)                                        ((0x0000000F&(data))>>0)


#define PRIORITY_CTRL_2                                                              0x18008010
#define PRIORITY_CTRL_2_reg_addr                                                     "0xB8008010"
#define PRIORITY_CTRL_2_reg                                                          0xB8008010
#define set_PRIORITY_CTRL_2_reg(data)   (*((volatile unsigned int*) PRIORITY_CTRL_2_reg)=data)
#define get_PRIORITY_CTRL_2_reg   (*((volatile unsigned int*) PRIORITY_CTRL_2_reg))
#define PRIORITY_CTRL_2_inst_adr                                                     "0x0004"
#define PRIORITY_CTRL_2_inst                                                         0x0004
#define PRIORITY_CTRL_2_gde_pri_shift                                                (24)
#define PRIORITY_CTRL_2_gde_pri_mask                                                 (0x0F000000)
#define PRIORITY_CTRL_2_gde_pri(data)                                                (0x0F000000&((data)<<24))
#define PRIORITY_CTRL_2_gde_pri_src(data)                                            ((0x0F000000&(data))>>24)
#define PRIORITY_CTRL_2_get_gde_pri(data)                                            ((0x0F000000&(data))>>24)
#define PRIORITY_CTRL_2_se_pri_shift                                                 (16)
#define PRIORITY_CTRL_2_se_pri_mask                                                  (0x000F0000)
#define PRIORITY_CTRL_2_se_pri(data)                                                 (0x000F0000&((data)<<16))
#define PRIORITY_CTRL_2_se_pri_src(data)                                             ((0x000F0000&(data))>>16)
#define PRIORITY_CTRL_2_get_se_pri(data)                                             ((0x000F0000&(data))>>16)
#define PRIORITY_CTRL_2_sb3_low_pri_shift                                            (8)
#define PRIORITY_CTRL_2_sb3_low_pri_mask                                             (0x00000F00)
#define PRIORITY_CTRL_2_sb3_low_pri(data)                                            (0x00000F00&((data)<<8))
#define PRIORITY_CTRL_2_sb3_low_pri_src(data)                                        ((0x00000F00&(data))>>8)
#define PRIORITY_CTRL_2_get_sb3_low_pri(data)                                        ((0x00000F00&(data))>>8)
#define PRIORITY_CTRL_2_ve_pri_shift                                                 (0)
#define PRIORITY_CTRL_2_ve_pri_mask                                                  (0x0000000F)
#define PRIORITY_CTRL_2_ve_pri(data)                                                 (0x0000000F&((data)<<0))
#define PRIORITY_CTRL_2_ve_pri_src(data)                                             ((0x0000000F&(data))>>0)
#define PRIORITY_CTRL_2_get_ve_pri(data)                                             ((0x0000000F&(data))>>0)


#define REORDER_CTRL_0                                                               0x18008014
#define REORDER_CTRL_0_reg_addr                                                      "0xB8008014"
#define REORDER_CTRL_0_reg                                                           0xB8008014
#define set_REORDER_CTRL_0_reg(data)   (*((volatile unsigned int*) REORDER_CTRL_0_reg)=data)
#define get_REORDER_CTRL_0_reg   (*((volatile unsigned int*) REORDER_CTRL_0_reg))
#define REORDER_CTRL_0_inst_adr                                                      "0x0005"
#define REORDER_CTRL_0_inst                                                          0x0005
#define REORDER_CTRL_0_vo_low_tag_shift                                              (16)
#define REORDER_CTRL_0_vo_low_tag_mask                                               (0x00030000)
#define REORDER_CTRL_0_vo_low_tag(data)                                              (0x00030000&((data)<<16))
#define REORDER_CTRL_0_vo_low_tag_src(data)                                          ((0x00030000&(data))>>16)
#define REORDER_CTRL_0_get_vo_low_tag(data)                                          ((0x00030000&(data))>>16)
#define REORDER_CTRL_0_sb1_low_tag_shift                                             (12)
#define REORDER_CTRL_0_sb1_low_tag_mask                                              (0x00003000)
#define REORDER_CTRL_0_sb1_low_tag(data)                                             (0x00003000&((data)<<12))
#define REORDER_CTRL_0_sb1_low_tag_src(data)                                         ((0x00003000&(data))>>12)
#define REORDER_CTRL_0_get_sb1_low_tag(data)                                         ((0x00003000&(data))>>12)
#define REORDER_CTRL_0_se_tag_shift                                                  (8)
#define REORDER_CTRL_0_se_tag_mask                                                   (0x00000300)
#define REORDER_CTRL_0_se_tag(data)                                                  (0x00000300&((data)<<8))
#define REORDER_CTRL_0_se_tag_src(data)                                              ((0x00000300&(data))>>8)
#define REORDER_CTRL_0_get_se_tag(data)                                              ((0x00000300&(data))>>8)
#define REORDER_CTRL_0_avk_cpu_tag_shift                                             (4)
#define REORDER_CTRL_0_avk_cpu_tag_mask                                              (0x00000030)
#define REORDER_CTRL_0_avk_cpu_tag(data)                                             (0x00000030&((data)<<4))
#define REORDER_CTRL_0_avk_cpu_tag_src(data)                                         ((0x00000030&(data))>>4)
#define REORDER_CTRL_0_get_avk_cpu_tag(data)                                         ((0x00000030&(data))>>4)
#define REORDER_CTRL_0_ve_tag_shift                                                  (0)
#define REORDER_CTRL_0_ve_tag_mask                                                   (0x00000003)
#define REORDER_CTRL_0_ve_tag(data)                                                  (0x00000003&((data)<<0))
#define REORDER_CTRL_0_ve_tag_src(data)                                              ((0x00000003&(data))>>0)
#define REORDER_CTRL_0_get_ve_tag(data)                                              ((0x00000003&(data))>>0)


#define REORDER_CTRL_1                                                               0x18008018
#define REORDER_CTRL_1_reg_addr                                                      "0xB8008018"
#define REORDER_CTRL_1_reg                                                           0xB8008018
#define set_REORDER_CTRL_1_reg(data)   (*((volatile unsigned int*) REORDER_CTRL_1_reg)=data)
#define get_REORDER_CTRL_1_reg   (*((volatile unsigned int*) REORDER_CTRL_1_reg))
#define REORDER_CTRL_1_inst_adr                                                      "0x0006"
#define REORDER_CTRL_1_inst                                                          0x0006
#define REORDER_CTRL_1_sb0_tag_shift                                                 (16)
#define REORDER_CTRL_1_sb0_tag_mask                                                  (0x00030000)
#define REORDER_CTRL_1_sb0_tag(data)                                                 (0x00030000&((data)<<16))
#define REORDER_CTRL_1_sb0_tag_src(data)                                             ((0x00030000&(data))>>16)
#define REORDER_CTRL_1_get_sb0_tag(data)                                             ((0x00030000&(data))>>16)
#define REORDER_CTRL_1_sb1_high_tag_shift                                            (12)
#define REORDER_CTRL_1_sb1_high_tag_mask                                             (0x00003000)
#define REORDER_CTRL_1_sb1_high_tag(data)                                            (0x00003000&((data)<<12))
#define REORDER_CTRL_1_sb1_high_tag_src(data)                                        ((0x00003000&(data))>>12)
#define REORDER_CTRL_1_get_sb1_high_tag(data)                                        ((0x00003000&(data))>>12)
#define REORDER_CTRL_1_vo_high_tag_shift                                             (8)
#define REORDER_CTRL_1_vo_high_tag_mask                                              (0x00000300)
#define REORDER_CTRL_1_vo_high_tag(data)                                             (0x00000300&((data)<<8))
#define REORDER_CTRL_1_vo_high_tag_src(data)                                         ((0x00000300&(data))>>8)
#define REORDER_CTRL_1_get_vo_high_tag(data)                                         ((0x00000300&(data))>>8)
#define REORDER_CTRL_1_sb3_high_tag_shift                                            (4)
#define REORDER_CTRL_1_sb3_high_tag_mask                                             (0x00000030)
#define REORDER_CTRL_1_sb3_high_tag(data)                                            (0x00000030&((data)<<4))
#define REORDER_CTRL_1_sb3_high_tag_src(data)                                        ((0x00000030&(data))>>4)
#define REORDER_CTRL_1_get_sb3_high_tag(data)                                        ((0x00000030&(data))>>4)
#define REORDER_CTRL_1_sb3_low_tag_shift                                             (0)
#define REORDER_CTRL_1_sb3_low_tag_mask                                              (0x00000003)
#define REORDER_CTRL_1_sb3_low_tag(data)                                             (0x00000003&((data)<<0))
#define REORDER_CTRL_1_sb3_low_tag_src(data)                                         ((0x00000003&(data))>>0)
#define REORDER_CTRL_1_get_sb3_low_tag(data)                                         ((0x00000003&(data))>>0)


#define DC_PROS_CTRL                                                                 0x1800801C
#define DC_PROS_CTRL_reg_addr                                                        "0xB800801C"
#define DC_PROS_CTRL_reg                                                             0xB800801C
#define set_DC_PROS_CTRL_reg(data)   (*((volatile unsigned int*) DC_PROS_CTRL_reg)=data)
#define get_DC_PROS_CTRL_reg   (*((volatile unsigned int*) DC_PROS_CTRL_reg))
#define DC_PROS_CTRL_inst_adr                                                        "0x0007"
#define DC_PROS_CTRL_inst                                                            0x0007
#define DC_PROS_CTRL_split_wait_shift                                                (28)
#define DC_PROS_CTRL_split_wait_mask                                                 (0xF0000000)
#define DC_PROS_CTRL_split_wait(data)                                                (0xF0000000&((data)<<28))
#define DC_PROS_CTRL_split_wait_src(data)                                            ((0xF0000000&(data))>>28)
#define DC_PROS_CTRL_get_split_wait(data)                                            ((0xF0000000&(data))>>28)
#define DC_PROS_CTRL_arbit_los_shift                                                 (24)
#define DC_PROS_CTRL_arbit_los_mask                                                  (0x0F000000)
#define DC_PROS_CTRL_arbit_los(data)                                                 (0x0F000000&((data)<<24))
#define DC_PROS_CTRL_arbit_los_src(data)                                             ((0x0F000000&(data))>>24)
#define DC_PROS_CTRL_get_arbit_los(data)                                             ((0x0F000000&(data))>>24)
#define DC_PROS_CTRL_short_lxy_shift                                                 (16)
#define DC_PROS_CTRL_short_lxy_mask                                                  (0x007F0000)
#define DC_PROS_CTRL_short_lxy(data)                                                 (0x007F0000&((data)<<16))
#define DC_PROS_CTRL_short_lxy_src(data)                                             ((0x007F0000&(data))>>16)
#define DC_PROS_CTRL_get_short_lxy(data)                                             ((0x007F0000&(data))>>16)
#define DC_PROS_CTRL_live_split_shift                                                (8)
#define DC_PROS_CTRL_live_split_mask                                                 (0x0000FF00)
#define DC_PROS_CTRL_live_split(data)                                                (0x0000FF00&((data)<<8))
#define DC_PROS_CTRL_live_split_src(data)                                            ((0x0000FF00&(data))>>8)
#define DC_PROS_CTRL_get_live_split(data)                                            ((0x0000FF00&(data))>>8)
#define DC_PROS_CTRL_live_cflit_shift                                                (1)
#define DC_PROS_CTRL_live_cflit_mask                                                 (0x00000002)
#define DC_PROS_CTRL_live_cflit(data)                                                (0x00000002&((data)<<1))
#define DC_PROS_CTRL_live_cflit_src(data)                                            ((0x00000002&(data))>>1)
#define DC_PROS_CTRL_get_live_cflit(data)                                            ((0x00000002&(data))>>1)
#define DC_PROS_CTRL_queue_flush_shift                                               (0)
#define DC_PROS_CTRL_queue_flush_mask                                                (0x00000001)
#define DC_PROS_CTRL_queue_flush(data)                                               (0x00000001&((data)<<0))
#define DC_PROS_CTRL_queue_flush_src(data)                                           ((0x00000001&(data))>>0)
#define DC_PROS_CTRL_get_queue_flush(data)                                           ((0x00000001&(data))>>0)


#define DC_PICT_SET_OFFSET                                                           0x18008020
#define DC_PICT_SET_OFFSET_reg_addr                                                  "0xB8008020"
#define DC_PICT_SET_OFFSET_reg                                                       0xB8008020
#define set_DC_PICT_SET_OFFSET_reg(data)   (*((volatile unsigned int*) DC_PICT_SET_OFFSET_reg)=data)
#define get_DC_PICT_SET_OFFSET_reg   (*((volatile unsigned int*) DC_PICT_SET_OFFSET_reg))
#define DC_PICT_SET_OFFSET_inst_adr                                                  "0x0008"
#define DC_PICT_SET_OFFSET_inst                                                      0x0008
#define DC_PICT_SET_OFFSET_pict_set_num_shift                                        (24)
#define DC_PICT_SET_OFFSET_pict_set_num_mask                                         (0xFF000000)
#define DC_PICT_SET_OFFSET_pict_set_num(data)                                        (0xFF000000&((data)<<24))
#define DC_PICT_SET_OFFSET_pict_set_num_src(data)                                    ((0xFF000000&(data))>>24)
#define DC_PICT_SET_OFFSET_get_pict_set_num(data)                                    ((0xFF000000&(data))>>24)
#define DC_PICT_SET_OFFSET_pict_offset_rd_shift                                      (23)
#define DC_PICT_SET_OFFSET_pict_offset_rd_mask                                       (0x00800000)
#define DC_PICT_SET_OFFSET_pict_offset_rd(data)                                      (0x00800000&((data)<<23))
#define DC_PICT_SET_OFFSET_pict_offset_rd_src(data)                                  ((0x00800000&(data))>>23)
#define DC_PICT_SET_OFFSET_get_pict_offset_rd(data)                                  ((0x00800000&(data))>>23)
#define DC_PICT_SET_OFFSET_pict_set_offset_y_shift                                   (10)
#define DC_PICT_SET_OFFSET_pict_set_offset_y_mask                                    (0x000FFC00)
#define DC_PICT_SET_OFFSET_pict_set_offset_y(data)                                   (0x000FFC00&((data)<<10))
#define DC_PICT_SET_OFFSET_pict_set_offset_y_src(data)                               ((0x000FFC00&(data))>>10)
#define DC_PICT_SET_OFFSET_get_pict_set_offset_y(data)                               ((0x000FFC00&(data))>>10)
#define DC_PICT_SET_OFFSET_pict_set_offset_x_shift                                   (0)
#define DC_PICT_SET_OFFSET_pict_set_offset_x_mask                                    (0x000003FF)
#define DC_PICT_SET_OFFSET_pict_set_offset_x(data)                                   (0x000003FF&((data)<<0))
#define DC_PICT_SET_OFFSET_pict_set_offset_x_src(data)                               ((0x000003FF&(data))>>0)
#define DC_PICT_SET_OFFSET_get_pict_set_offset_x(data)                               ((0x000003FF&(data))>>0)


#define DC_REQ_STATUS                                                                0x18008024
#define DC_REQ_STATUS_reg_addr                                                       "0xB8008024"
#define DC_REQ_STATUS_reg                                                            0xB8008024
#define set_DC_REQ_STATUS_reg(data)   (*((volatile unsigned int*) DC_REQ_STATUS_reg)=data)
#define get_DC_REQ_STATUS_reg   (*((volatile unsigned int*) DC_REQ_STATUS_reg))
#define DC_REQ_STATUS_inst_adr                                                       "0x0009"
#define DC_REQ_STATUS_inst                                                           0x0009
#define DC_REQ_STATUS_req_pending_shift                                              (11)
#define DC_REQ_STATUS_req_pending_mask                                               (0x00000800)
#define DC_REQ_STATUS_req_pending(data)                                              (0x00000800&((data)<<11))
#define DC_REQ_STATUS_req_pending_src(data)                                          ((0x00000800&(data))>>11)
#define DC_REQ_STATUS_get_req_pending(data)                                          ((0x00000800&(data))>>11)
#define DC_REQ_STATUS_req_id_shift                                                   (0)
#define DC_REQ_STATUS_req_id_mask                                                    (0x000007FF)
#define DC_REQ_STATUS_req_id(data)                                                   (0x000007FF&((data)<<0))
#define DC_REQ_STATUS_req_id_src(data)                                               ((0x000007FF&(data))>>0)
#define DC_REQ_STATUS_get_req_id(data)                                               ((0x000007FF&(data))>>0)


#define DC_SYS_MISC2                                                                 0x18008028
#define DC_SYS_MISC2_reg_addr                                                        "0xB8008028"
#define DC_SYS_MISC2_reg                                                             0xB8008028
#define set_DC_SYS_MISC2_reg(data)   (*((volatile unsigned int*) DC_SYS_MISC2_reg)=data)
#define get_DC_SYS_MISC2_reg   (*((volatile unsigned int*) DC_SYS_MISC2_reg))
#define DC_SYS_MISC2_inst_adr                                                        "0x000A"
#define DC_SYS_MISC2_inst                                                            0x000A
#define DC_SYS_MISC2_qfifo_cnt_full_threshold_shift                                  (24)
#define DC_SYS_MISC2_qfifo_cnt_full_threshold_mask                                   (0x1F000000)
#define DC_SYS_MISC2_qfifo_cnt_full_threshold(data)                                  (0x1F000000&((data)<<24))
#define DC_SYS_MISC2_qfifo_cnt_full_threshold_src(data)                              ((0x1F000000&(data))>>24)
#define DC_SYS_MISC2_get_qfifo_cnt_full_threshold(data)                              ((0x1F000000&(data))>>24)
#define DC_SYS_MISC2_full_cmd_count_shift                                            (20)
#define DC_SYS_MISC2_full_cmd_count_mask                                             (0x00F00000)
#define DC_SYS_MISC2_full_cmd_count(data)                                            (0x00F00000&((data)<<20))
#define DC_SYS_MISC2_full_cmd_count_src(data)                                        ((0x00F00000&(data))>>20)
#define DC_SYS_MISC2_get_full_cmd_count(data)                                        ((0x00F00000&(data))>>20)
#define DC_SYS_MISC2_pre_tra_rd_cnt_shift                                            (10)
#define DC_SYS_MISC2_pre_tra_rd_cnt_mask                                             (0x000FFC00)
#define DC_SYS_MISC2_pre_tra_rd_cnt(data)                                            (0x000FFC00&((data)<<10))
#define DC_SYS_MISC2_pre_tra_rd_cnt_src(data)                                        ((0x000FFC00&(data))>>10)
#define DC_SYS_MISC2_get_pre_tra_rd_cnt(data)                                        ((0x000FFC00&(data))>>10)
#define DC_SYS_MISC2_pre_tra_wr_cnt_shift                                            (0)
#define DC_SYS_MISC2_pre_tra_wr_cnt_mask                                             (0x000003FF)
#define DC_SYS_MISC2_pre_tra_wr_cnt(data)                                            (0x000003FF&((data)<<0))
#define DC_SYS_MISC2_pre_tra_wr_cnt_src(data)                                        ((0x000003FF&(data))>>0)
#define DC_SYS_MISC2_get_pre_tra_wr_cnt(data)                                        ((0x000003FF&(data))>>0)


#define DC_SYS_MISC3                                                                 0x1800802C
#define DC_SYS_MISC3_reg_addr                                                        "0xB800802C"
#define DC_SYS_MISC3_reg                                                             0xB800802C
#define set_DC_SYS_MISC3_reg(data)   (*((volatile unsigned int*) DC_SYS_MISC3_reg)=data)
#define get_DC_SYS_MISC3_reg   (*((volatile unsigned int*) DC_SYS_MISC3_reg))
#define DC_SYS_MISC3_inst_adr                                                        "0x000B"
#define DC_SYS_MISC3_inst                                                            0x000B
#define DC_SYS_MISC3_gpu_wdata_queue_flush_shift                                     (6)
#define DC_SYS_MISC3_gpu_wdata_queue_flush_mask                                      (0x00000040)
#define DC_SYS_MISC3_gpu_wdata_queue_flush(data)                                     (0x00000040&((data)<<6))
#define DC_SYS_MISC3_gpu_wdata_queue_flush_src(data)                                 ((0x00000040&(data))>>6)
#define DC_SYS_MISC3_get_gpu_wdata_queue_flush(data)                                 ((0x00000040&(data))>>6)
#define DC_SYS_MISC3_enable_arb_delay_by_tv_sb1_grant_shift                          (2)
#define DC_SYS_MISC3_enable_arb_delay_by_tv_sb1_grant_mask                           (0x00000004)
#define DC_SYS_MISC3_enable_arb_delay_by_tv_sb1_grant(data)                          (0x00000004&((data)<<2))
#define DC_SYS_MISC3_enable_arb_delay_by_tv_sb1_grant_src(data)                      ((0x00000004&(data))>>2)
#define DC_SYS_MISC3_get_enable_arb_delay_by_tv_sb1_grant(data)                      ((0x00000004&(data))>>2)
#define DC_SYS_MISC3_gpu_cmd_queue_flush_shift                                       (1)
#define DC_SYS_MISC3_gpu_cmd_queue_flush_mask                                        (0x00000002)
#define DC_SYS_MISC3_gpu_cmd_queue_flush(data)                                       (0x00000002&((data)<<1))
#define DC_SYS_MISC3_gpu_cmd_queue_flush_src(data)                                   ((0x00000002&(data))>>1)
#define DC_SYS_MISC3_get_gpu_cmd_queue_flush(data)                                   ((0x00000002&(data))>>1)
#define DC_SYS_MISC3_gde_cmd_grp_disable_shift                                       (0)
#define DC_SYS_MISC3_gde_cmd_grp_disable_mask                                        (0x00000001)
#define DC_SYS_MISC3_gde_cmd_grp_disable(data)                                       (0x00000001&((data)<<0))
#define DC_SYS_MISC3_gde_cmd_grp_disable_src(data)                                   ((0x00000001&(data))>>0)
#define DC_SYS_MISC3_get_gde_cmd_grp_disable(data)                                   ((0x00000001&(data))>>0)


#define DC_PC_CTRL                                                                   0x18008030
#define DC_PC_CTRL_reg_addr                                                          "0xB8008030"
#define DC_PC_CTRL_reg                                                               0xB8008030
#define set_DC_PC_CTRL_reg(data)   (*((volatile unsigned int*) DC_PC_CTRL_reg)=data)
#define get_DC_PC_CTRL_reg   (*((volatile unsigned int*) DC_PC_CTRL_reg))
#define DC_PC_CTRL_inst_adr                                                          "0x000C"
#define DC_PC_CTRL_inst                                                              0x000C
#define DC_PC_CTRL_pc_go_shift                                                       (0)
#define DC_PC_CTRL_pc_go_mask                                                        (0x00000001)
#define DC_PC_CTRL_pc_go(data)                                                       (0x00000001&((data)<<0))
#define DC_PC_CTRL_pc_go_src(data)                                                   ((0x00000001&(data))>>0)
#define DC_PC_CTRL_get_pc_go(data)                                                   ((0x00000001&(data))>>0)


#define DC_PC_TOTA_MON_NUM                                                           0x18008034
#define DC_PC_TOTA_MON_NUM_reg_addr                                                  "0xB8008034"
#define DC_PC_TOTA_MON_NUM_reg                                                       0xB8008034
#define set_DC_PC_TOTA_MON_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_TOTA_MON_NUM_reg)=data)
#define get_DC_PC_TOTA_MON_NUM_reg   (*((volatile unsigned int*) DC_PC_TOTA_MON_NUM_reg))
#define DC_PC_TOTA_MON_NUM_inst_adr                                                  "0x000D"
#define DC_PC_TOTA_MON_NUM_inst                                                      0x000D
#define DC_PC_TOTA_MON_NUM_pc_tota_mon_num_shift                                     (0)
#define DC_PC_TOTA_MON_NUM_pc_tota_mon_num_mask                                      (0xFFFFFFFF)
#define DC_PC_TOTA_MON_NUM_pc_tota_mon_num(data)                                     (0xFFFFFFFF&((data)<<0))
#define DC_PC_TOTA_MON_NUM_pc_tota_mon_num_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define DC_PC_TOTA_MON_NUM_get_pc_tota_mon_num(data)                                 ((0xFFFFFFFF&(data))>>0)


#define DC_PC_TOTA_ACK_NUM                                                           0x18008038
#define DC_PC_TOTA_ACK_NUM_reg_addr                                                  "0xB8008038"
#define DC_PC_TOTA_ACK_NUM_reg                                                       0xB8008038
#define set_DC_PC_TOTA_ACK_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_TOTA_ACK_NUM_reg)=data)
#define get_DC_PC_TOTA_ACK_NUM_reg   (*((volatile unsigned int*) DC_PC_TOTA_ACK_NUM_reg))
#define DC_PC_TOTA_ACK_NUM_inst_adr                                                  "0x000E"
#define DC_PC_TOTA_ACK_NUM_inst                                                      0x000E
#define DC_PC_TOTA_ACK_NUM_pc_tota_ack_num_shift                                     (0)
#define DC_PC_TOTA_ACK_NUM_pc_tota_ack_num_mask                                      (0xFFFFFFFF)
#define DC_PC_TOTA_ACK_NUM_pc_tota_ack_num(data)                                     (0xFFFFFFFF&((data)<<0))
#define DC_PC_TOTA_ACK_NUM_pc_tota_ack_num_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define DC_PC_TOTA_ACK_NUM_get_pc_tota_ack_num(data)                                 ((0xFFFFFFFF&(data))>>0)


#define DC_PC_TOTA_IDL_NUM                                                           0x1800803C
#define DC_PC_TOTA_IDL_NUM_reg_addr                                                  "0xB800803C"
#define DC_PC_TOTA_IDL_NUM_reg                                                       0xB800803C
#define set_DC_PC_TOTA_IDL_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_TOTA_IDL_NUM_reg)=data)
#define get_DC_PC_TOTA_IDL_NUM_reg   (*((volatile unsigned int*) DC_PC_TOTA_IDL_NUM_reg))
#define DC_PC_TOTA_IDL_NUM_inst_adr                                                  "0x000F"
#define DC_PC_TOTA_IDL_NUM_inst                                                      0x000F
#define DC_PC_TOTA_IDL_NUM_pc_tota_idl_num_shift                                     (0)
#define DC_PC_TOTA_IDL_NUM_pc_tota_idl_num_mask                                      (0xFFFFFFFF)
#define DC_PC_TOTA_IDL_NUM_pc_tota_idl_num(data)                                     (0xFFFFFFFF&((data)<<0))
#define DC_PC_TOTA_IDL_NUM_pc_tota_idl_num_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define DC_PC_TOTA_IDL_NUM_get_pc_tota_idl_num(data)                                 ((0xFFFFFFFF&(data))>>0)


#define DC_PC_SYSH_PROG_CTRL                                                         0x18008040
#define DC_PC_SYSH_PROG_CTRL_reg_addr                                                "0xB8008040"
#define DC_PC_SYSH_PROG_CTRL_reg                                                     0xB8008040
#define set_DC_PC_SYSH_PROG_CTRL_reg(data)   (*((volatile unsigned int*) DC_PC_SYSH_PROG_CTRL_reg)=data)
#define get_DC_PC_SYSH_PROG_CTRL_reg   (*((volatile unsigned int*) DC_PC_SYSH_PROG_CTRL_reg))
#define DC_PC_SYSH_PROG_CTRL_inst_adr                                                "0x0010"
#define DC_PC_SYSH_PROG_CTRL_inst                                                    0x0010
#define DC_PC_SYSH_PROG_CTRL_write_en_3_shift                                        (25)
#define DC_PC_SYSH_PROG_CTRL_write_en_3_mask                                         (0x02000000)
#define DC_PC_SYSH_PROG_CTRL_write_en_3(data)                                        (0x02000000&((data)<<25))
#define DC_PC_SYSH_PROG_CTRL_write_en_3_src(data)                                    ((0x02000000&(data))>>25)
#define DC_PC_SYSH_PROG_CTRL_get_write_en_3(data)                                    ((0x02000000&(data))>>25)
#define DC_PC_SYSH_PROG_CTRL_pc_sysh_prog2_sel_shift                                 (18)
#define DC_PC_SYSH_PROG_CTRL_pc_sysh_prog2_sel_mask                                  (0x01FC0000)
#define DC_PC_SYSH_PROG_CTRL_pc_sysh_prog2_sel(data)                                 (0x01FC0000&((data)<<18))
#define DC_PC_SYSH_PROG_CTRL_pc_sysh_prog2_sel_src(data)                             ((0x01FC0000&(data))>>18)
#define DC_PC_SYSH_PROG_CTRL_get_pc_sysh_prog2_sel(data)                             ((0x01FC0000&(data))>>18)
#define DC_PC_SYSH_PROG_CTRL_write_en_2_shift                                        (16)
#define DC_PC_SYSH_PROG_CTRL_write_en_2_mask                                         (0x00010000)
#define DC_PC_SYSH_PROG_CTRL_write_en_2(data)                                        (0x00010000&((data)<<16))
#define DC_PC_SYSH_PROG_CTRL_write_en_2_src(data)                                    ((0x00010000&(data))>>16)
#define DC_PC_SYSH_PROG_CTRL_get_write_en_2(data)                                    ((0x00010000&(data))>>16)
#define DC_PC_SYSH_PROG_CTRL_pc_sysh_prog1_sel_shift                                 (9)
#define DC_PC_SYSH_PROG_CTRL_pc_sysh_prog1_sel_mask                                  (0x0000FE00)
#define DC_PC_SYSH_PROG_CTRL_pc_sysh_prog1_sel(data)                                 (0x0000FE00&((data)<<9))
#define DC_PC_SYSH_PROG_CTRL_pc_sysh_prog1_sel_src(data)                             ((0x0000FE00&(data))>>9)
#define DC_PC_SYSH_PROG_CTRL_get_pc_sysh_prog1_sel(data)                             ((0x0000FE00&(data))>>9)
#define DC_PC_SYSH_PROG_CTRL_write_en_1_shift                                        (7)
#define DC_PC_SYSH_PROG_CTRL_write_en_1_mask                                         (0x00000080)
#define DC_PC_SYSH_PROG_CTRL_write_en_1(data)                                        (0x00000080&((data)<<7))
#define DC_PC_SYSH_PROG_CTRL_write_en_1_src(data)                                    ((0x00000080&(data))>>7)
#define DC_PC_SYSH_PROG_CTRL_get_write_en_1(data)                                    ((0x00000080&(data))>>7)
#define DC_PC_SYSH_PROG_CTRL_pc_sysh_prog0_sel_shift                                 (0)
#define DC_PC_SYSH_PROG_CTRL_pc_sysh_prog0_sel_mask                                  (0x0000007F)
#define DC_PC_SYSH_PROG_CTRL_pc_sysh_prog0_sel(data)                                 (0x0000007F&((data)<<0))
#define DC_PC_SYSH_PROG_CTRL_pc_sysh_prog0_sel_src(data)                             ((0x0000007F&(data))>>0)
#define DC_PC_SYSH_PROG_CTRL_get_pc_sysh_prog0_sel(data)                             ((0x0000007F&(data))>>0)


#define DC_PC_SYS_PROG_CTRL                                                          0x18008044
#define DC_PC_SYS_PROG_CTRL_reg_addr                                                 "0xB8008044"
#define DC_PC_SYS_PROG_CTRL_reg                                                      0xB8008044
#define set_DC_PC_SYS_PROG_CTRL_reg(data)   (*((volatile unsigned int*) DC_PC_SYS_PROG_CTRL_reg)=data)
#define get_DC_PC_SYS_PROG_CTRL_reg   (*((volatile unsigned int*) DC_PC_SYS_PROG_CTRL_reg))
#define DC_PC_SYS_PROG_CTRL_inst_adr                                                 "0x0011"
#define DC_PC_SYS_PROG_CTRL_inst                                                     0x0011
#define DC_PC_SYS_PROG_CTRL_write_en_3_shift                                         (25)
#define DC_PC_SYS_PROG_CTRL_write_en_3_mask                                          (0x02000000)
#define DC_PC_SYS_PROG_CTRL_write_en_3(data)                                         (0x02000000&((data)<<25))
#define DC_PC_SYS_PROG_CTRL_write_en_3_src(data)                                     ((0x02000000&(data))>>25)
#define DC_PC_SYS_PROG_CTRL_get_write_en_3(data)                                     ((0x02000000&(data))>>25)
#define DC_PC_SYS_PROG_CTRL_pc_sys_prog2_sel_shift                                   (18)
#define DC_PC_SYS_PROG_CTRL_pc_sys_prog2_sel_mask                                    (0x01FC0000)
#define DC_PC_SYS_PROG_CTRL_pc_sys_prog2_sel(data)                                   (0x01FC0000&((data)<<18))
#define DC_PC_SYS_PROG_CTRL_pc_sys_prog2_sel_src(data)                               ((0x01FC0000&(data))>>18)
#define DC_PC_SYS_PROG_CTRL_get_pc_sys_prog2_sel(data)                               ((0x01FC0000&(data))>>18)
#define DC_PC_SYS_PROG_CTRL_write_en_2_shift                                         (16)
#define DC_PC_SYS_PROG_CTRL_write_en_2_mask                                          (0x00010000)
#define DC_PC_SYS_PROG_CTRL_write_en_2(data)                                         (0x00010000&((data)<<16))
#define DC_PC_SYS_PROG_CTRL_write_en_2_src(data)                                     ((0x00010000&(data))>>16)
#define DC_PC_SYS_PROG_CTRL_get_write_en_2(data)                                     ((0x00010000&(data))>>16)
#define DC_PC_SYS_PROG_CTRL_pc_sys_prog1_sel_shift                                   (9)
#define DC_PC_SYS_PROG_CTRL_pc_sys_prog1_sel_mask                                    (0x0000FE00)
#define DC_PC_SYS_PROG_CTRL_pc_sys_prog1_sel(data)                                   (0x0000FE00&((data)<<9))
#define DC_PC_SYS_PROG_CTRL_pc_sys_prog1_sel_src(data)                               ((0x0000FE00&(data))>>9)
#define DC_PC_SYS_PROG_CTRL_get_pc_sys_prog1_sel(data)                               ((0x0000FE00&(data))>>9)
#define DC_PC_SYS_PROG_CTRL_write_en_1_shift                                         (7)
#define DC_PC_SYS_PROG_CTRL_write_en_1_mask                                          (0x00000080)
#define DC_PC_SYS_PROG_CTRL_write_en_1(data)                                         (0x00000080&((data)<<7))
#define DC_PC_SYS_PROG_CTRL_write_en_1_src(data)                                     ((0x00000080&(data))>>7)
#define DC_PC_SYS_PROG_CTRL_get_write_en_1(data)                                     ((0x00000080&(data))>>7)
#define DC_PC_SYS_PROG_CTRL_pc_sys_prog0_sel_shift                                   (0)
#define DC_PC_SYS_PROG_CTRL_pc_sys_prog0_sel_mask                                    (0x0000007F)
#define DC_PC_SYS_PROG_CTRL_pc_sys_prog0_sel(data)                                   (0x0000007F&((data)<<0))
#define DC_PC_SYS_PROG_CTRL_pc_sys_prog0_sel_src(data)                               ((0x0000007F&(data))>>0)
#define DC_PC_SYS_PROG_CTRL_get_pc_sys_prog0_sel(data)                               ((0x0000007F&(data))>>0)


#define DC_PC_SYSH_PROG_0_ACC_LAT                                                    0x18008050
#define DC_PC_SYSH_PROG_0_ACC_LAT_reg_addr                                           "0xB8008050"
#define DC_PC_SYSH_PROG_0_ACC_LAT_reg                                                0xB8008050
#define set_DC_PC_SYSH_PROG_0_ACC_LAT_reg(data)   (*((volatile unsigned int*) DC_PC_SYSH_PROG_0_ACC_LAT_reg)=data)
#define get_DC_PC_SYSH_PROG_0_ACC_LAT_reg   (*((volatile unsigned int*) DC_PC_SYSH_PROG_0_ACC_LAT_reg))
#define DC_PC_SYSH_PROG_0_ACC_LAT_inst_adr                                           "0x0014"
#define DC_PC_SYSH_PROG_0_ACC_LAT_inst                                               0x0014
#define DC_PC_SYSH_PROG_0_ACC_LAT_sysh_prog0_acc_lat_shift                           (0)
#define DC_PC_SYSH_PROG_0_ACC_LAT_sysh_prog0_acc_lat_mask                            (0xFFFFFFFF)
#define DC_PC_SYSH_PROG_0_ACC_LAT_sysh_prog0_acc_lat(data)                           (0xFFFFFFFF&((data)<<0))
#define DC_PC_SYSH_PROG_0_ACC_LAT_sysh_prog0_acc_lat_src(data)                       ((0xFFFFFFFF&(data))>>0)
#define DC_PC_SYSH_PROG_0_ACC_LAT_get_sysh_prog0_acc_lat(data)                       ((0xFFFFFFFF&(data))>>0)


#define DC_PC_SYSH_PROG_0_MAX_LAT                                                    0x18008054
#define DC_PC_SYSH_PROG_0_MAX_LAT_reg_addr                                           "0xB8008054"
#define DC_PC_SYSH_PROG_0_MAX_LAT_reg                                                0xB8008054
#define set_DC_PC_SYSH_PROG_0_MAX_LAT_reg(data)   (*((volatile unsigned int*) DC_PC_SYSH_PROG_0_MAX_LAT_reg)=data)
#define get_DC_PC_SYSH_PROG_0_MAX_LAT_reg   (*((volatile unsigned int*) DC_PC_SYSH_PROG_0_MAX_LAT_reg))
#define DC_PC_SYSH_PROG_0_MAX_LAT_inst_adr                                           "0x0015"
#define DC_PC_SYSH_PROG_0_MAX_LAT_inst                                               0x0015
#define DC_PC_SYSH_PROG_0_MAX_LAT_sysh_prog0_max_lat_shift                           (0)
#define DC_PC_SYSH_PROG_0_MAX_LAT_sysh_prog0_max_lat_mask                            (0x0000FFFF)
#define DC_PC_SYSH_PROG_0_MAX_LAT_sysh_prog0_max_lat(data)                           (0x0000FFFF&((data)<<0))
#define DC_PC_SYSH_PROG_0_MAX_LAT_sysh_prog0_max_lat_src(data)                       ((0x0000FFFF&(data))>>0)
#define DC_PC_SYSH_PROG_0_MAX_LAT_get_sysh_prog0_max_lat(data)                       ((0x0000FFFF&(data))>>0)


#define DC_PC_SYSH_PROG_0_REQ_NUM                                                    0x18008058
#define DC_PC_SYSH_PROG_0_REQ_NUM_reg_addr                                           "0xB8008058"
#define DC_PC_SYSH_PROG_0_REQ_NUM_reg                                                0xB8008058
#define set_DC_PC_SYSH_PROG_0_REQ_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_SYSH_PROG_0_REQ_NUM_reg)=data)
#define get_DC_PC_SYSH_PROG_0_REQ_NUM_reg   (*((volatile unsigned int*) DC_PC_SYSH_PROG_0_REQ_NUM_reg))
#define DC_PC_SYSH_PROG_0_REQ_NUM_inst_adr                                           "0x0016"
#define DC_PC_SYSH_PROG_0_REQ_NUM_inst                                               0x0016
#define DC_PC_SYSH_PROG_0_REQ_NUM_sysh_prog0_req_num_shift                           (0)
#define DC_PC_SYSH_PROG_0_REQ_NUM_sysh_prog0_req_num_mask                            (0x00FFFFFF)
#define DC_PC_SYSH_PROG_0_REQ_NUM_sysh_prog0_req_num(data)                           (0x00FFFFFF&((data)<<0))
#define DC_PC_SYSH_PROG_0_REQ_NUM_sysh_prog0_req_num_src(data)                       ((0x00FFFFFF&(data))>>0)
#define DC_PC_SYSH_PROG_0_REQ_NUM_get_sysh_prog0_req_num(data)                       ((0x00FFFFFF&(data))>>0)


#define DC_PC_SYSH_PROG_0_ACK_NUM                                                    0x1800805C
#define DC_PC_SYSH_PROG_0_ACK_NUM_reg_addr                                           "0xB800805C"
#define DC_PC_SYSH_PROG_0_ACK_NUM_reg                                                0xB800805C
#define set_DC_PC_SYSH_PROG_0_ACK_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_SYSH_PROG_0_ACK_NUM_reg)=data)
#define get_DC_PC_SYSH_PROG_0_ACK_NUM_reg   (*((volatile unsigned int*) DC_PC_SYSH_PROG_0_ACK_NUM_reg))
#define DC_PC_SYSH_PROG_0_ACK_NUM_inst_adr                                           "0x0017"
#define DC_PC_SYSH_PROG_0_ACK_NUM_inst                                               0x0017
#define DC_PC_SYSH_PROG_0_ACK_NUM_sysh_prog0_ack_num_shift                           (0)
#define DC_PC_SYSH_PROG_0_ACK_NUM_sysh_prog0_ack_num_mask                            (0xFFFFFFFF)
#define DC_PC_SYSH_PROG_0_ACK_NUM_sysh_prog0_ack_num(data)                           (0xFFFFFFFF&((data)<<0))
#define DC_PC_SYSH_PROG_0_ACK_NUM_sysh_prog0_ack_num_src(data)                       ((0xFFFFFFFF&(data))>>0)
#define DC_PC_SYSH_PROG_0_ACK_NUM_get_sysh_prog0_ack_num(data)                       ((0xFFFFFFFF&(data))>>0)


#define DC_PC_SYSH_PROG_1_ACC_LAT                                                    0x18008060
#define DC_PC_SYSH_PROG_1_ACC_LAT_reg_addr                                           "0xB8008060"
#define DC_PC_SYSH_PROG_1_ACC_LAT_reg                                                0xB8008060
#define set_DC_PC_SYSH_PROG_1_ACC_LAT_reg(data)   (*((volatile unsigned int*) DC_PC_SYSH_PROG_1_ACC_LAT_reg)=data)
#define get_DC_PC_SYSH_PROG_1_ACC_LAT_reg   (*((volatile unsigned int*) DC_PC_SYSH_PROG_1_ACC_LAT_reg))
#define DC_PC_SYSH_PROG_1_ACC_LAT_inst_adr                                           "0x0018"
#define DC_PC_SYSH_PROG_1_ACC_LAT_inst                                               0x0018
#define DC_PC_SYSH_PROG_1_ACC_LAT_sysh_prog1_acc_lat_shift                           (0)
#define DC_PC_SYSH_PROG_1_ACC_LAT_sysh_prog1_acc_lat_mask                            (0xFFFFFFFF)
#define DC_PC_SYSH_PROG_1_ACC_LAT_sysh_prog1_acc_lat(data)                           (0xFFFFFFFF&((data)<<0))
#define DC_PC_SYSH_PROG_1_ACC_LAT_sysh_prog1_acc_lat_src(data)                       ((0xFFFFFFFF&(data))>>0)
#define DC_PC_SYSH_PROG_1_ACC_LAT_get_sysh_prog1_acc_lat(data)                       ((0xFFFFFFFF&(data))>>0)


#define DC_PC_SYSH_PROG_1_MAX_LAT                                                    0x18008064
#define DC_PC_SYSH_PROG_1_MAX_LAT_reg_addr                                           "0xB8008064"
#define DC_PC_SYSH_PROG_1_MAX_LAT_reg                                                0xB8008064
#define set_DC_PC_SYSH_PROG_1_MAX_LAT_reg(data)   (*((volatile unsigned int*) DC_PC_SYSH_PROG_1_MAX_LAT_reg)=data)
#define get_DC_PC_SYSH_PROG_1_MAX_LAT_reg   (*((volatile unsigned int*) DC_PC_SYSH_PROG_1_MAX_LAT_reg))
#define DC_PC_SYSH_PROG_1_MAX_LAT_inst_adr                                           "0x0019"
#define DC_PC_SYSH_PROG_1_MAX_LAT_inst                                               0x0019
#define DC_PC_SYSH_PROG_1_MAX_LAT_sysh_prog1_max_lat_shift                           (0)
#define DC_PC_SYSH_PROG_1_MAX_LAT_sysh_prog1_max_lat_mask                            (0x0000FFFF)
#define DC_PC_SYSH_PROG_1_MAX_LAT_sysh_prog1_max_lat(data)                           (0x0000FFFF&((data)<<0))
#define DC_PC_SYSH_PROG_1_MAX_LAT_sysh_prog1_max_lat_src(data)                       ((0x0000FFFF&(data))>>0)
#define DC_PC_SYSH_PROG_1_MAX_LAT_get_sysh_prog1_max_lat(data)                       ((0x0000FFFF&(data))>>0)


#define DC_PC_SYSH_PROG_1_REQ_NUM                                                    0x18008068
#define DC_PC_SYSH_PROG_1_REQ_NUM_reg_addr                                           "0xB8008068"
#define DC_PC_SYSH_PROG_1_REQ_NUM_reg                                                0xB8008068
#define set_DC_PC_SYSH_PROG_1_REQ_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_SYSH_PROG_1_REQ_NUM_reg)=data)
#define get_DC_PC_SYSH_PROG_1_REQ_NUM_reg   (*((volatile unsigned int*) DC_PC_SYSH_PROG_1_REQ_NUM_reg))
#define DC_PC_SYSH_PROG_1_REQ_NUM_inst_adr                                           "0x001A"
#define DC_PC_SYSH_PROG_1_REQ_NUM_inst                                               0x001A
#define DC_PC_SYSH_PROG_1_REQ_NUM_sysh_prog1_req_num_shift                           (0)
#define DC_PC_SYSH_PROG_1_REQ_NUM_sysh_prog1_req_num_mask                            (0x00FFFFFF)
#define DC_PC_SYSH_PROG_1_REQ_NUM_sysh_prog1_req_num(data)                           (0x00FFFFFF&((data)<<0))
#define DC_PC_SYSH_PROG_1_REQ_NUM_sysh_prog1_req_num_src(data)                       ((0x00FFFFFF&(data))>>0)
#define DC_PC_SYSH_PROG_1_REQ_NUM_get_sysh_prog1_req_num(data)                       ((0x00FFFFFF&(data))>>0)


#define DC_PC_SYSH_PROG_1_ACK_NUM                                                    0x1800806C
#define DC_PC_SYSH_PROG_1_ACK_NUM_reg_addr                                           "0xB800806C"
#define DC_PC_SYSH_PROG_1_ACK_NUM_reg                                                0xB800806C
#define set_DC_PC_SYSH_PROG_1_ACK_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_SYSH_PROG_1_ACK_NUM_reg)=data)
#define get_DC_PC_SYSH_PROG_1_ACK_NUM_reg   (*((volatile unsigned int*) DC_PC_SYSH_PROG_1_ACK_NUM_reg))
#define DC_PC_SYSH_PROG_1_ACK_NUM_inst_adr                                           "0x001B"
#define DC_PC_SYSH_PROG_1_ACK_NUM_inst                                               0x001B
#define DC_PC_SYSH_PROG_1_ACK_NUM_sysh_prog1_ack_num_shift                           (0)
#define DC_PC_SYSH_PROG_1_ACK_NUM_sysh_prog1_ack_num_mask                            (0xFFFFFFFF)
#define DC_PC_SYSH_PROG_1_ACK_NUM_sysh_prog1_ack_num(data)                           (0xFFFFFFFF&((data)<<0))
#define DC_PC_SYSH_PROG_1_ACK_NUM_sysh_prog1_ack_num_src(data)                       ((0xFFFFFFFF&(data))>>0)
#define DC_PC_SYSH_PROG_1_ACK_NUM_get_sysh_prog1_ack_num(data)                       ((0xFFFFFFFF&(data))>>0)


#define DC_PC_SYSH_PROG_2_ACC_LAT                                                    0x18008070
#define DC_PC_SYSH_PROG_2_ACC_LAT_reg_addr                                           "0xB8008070"
#define DC_PC_SYSH_PROG_2_ACC_LAT_reg                                                0xB8008070
#define set_DC_PC_SYSH_PROG_2_ACC_LAT_reg(data)   (*((volatile unsigned int*) DC_PC_SYSH_PROG_2_ACC_LAT_reg)=data)
#define get_DC_PC_SYSH_PROG_2_ACC_LAT_reg   (*((volatile unsigned int*) DC_PC_SYSH_PROG_2_ACC_LAT_reg))
#define DC_PC_SYSH_PROG_2_ACC_LAT_inst_adr                                           "0x001C"
#define DC_PC_SYSH_PROG_2_ACC_LAT_inst                                               0x001C
#define DC_PC_SYSH_PROG_2_ACC_LAT_sysh_prog2_acc_lat_shift                           (0)
#define DC_PC_SYSH_PROG_2_ACC_LAT_sysh_prog2_acc_lat_mask                            (0xFFFFFFFF)
#define DC_PC_SYSH_PROG_2_ACC_LAT_sysh_prog2_acc_lat(data)                           (0xFFFFFFFF&((data)<<0))
#define DC_PC_SYSH_PROG_2_ACC_LAT_sysh_prog2_acc_lat_src(data)                       ((0xFFFFFFFF&(data))>>0)
#define DC_PC_SYSH_PROG_2_ACC_LAT_get_sysh_prog2_acc_lat(data)                       ((0xFFFFFFFF&(data))>>0)


#define DC_PC_SYSH_PROG_2_MAX_LAT                                                    0x18008074
#define DC_PC_SYSH_PROG_2_MAX_LAT_reg_addr                                           "0xB8008074"
#define DC_PC_SYSH_PROG_2_MAX_LAT_reg                                                0xB8008074
#define set_DC_PC_SYSH_PROG_2_MAX_LAT_reg(data)   (*((volatile unsigned int*) DC_PC_SYSH_PROG_2_MAX_LAT_reg)=data)
#define get_DC_PC_SYSH_PROG_2_MAX_LAT_reg   (*((volatile unsigned int*) DC_PC_SYSH_PROG_2_MAX_LAT_reg))
#define DC_PC_SYSH_PROG_2_MAX_LAT_inst_adr                                           "0x001D"
#define DC_PC_SYSH_PROG_2_MAX_LAT_inst                                               0x001D
#define DC_PC_SYSH_PROG_2_MAX_LAT_sysh_prog2_max_lat_shift                           (0)
#define DC_PC_SYSH_PROG_2_MAX_LAT_sysh_prog2_max_lat_mask                            (0x0000FFFF)
#define DC_PC_SYSH_PROG_2_MAX_LAT_sysh_prog2_max_lat(data)                           (0x0000FFFF&((data)<<0))
#define DC_PC_SYSH_PROG_2_MAX_LAT_sysh_prog2_max_lat_src(data)                       ((0x0000FFFF&(data))>>0)
#define DC_PC_SYSH_PROG_2_MAX_LAT_get_sysh_prog2_max_lat(data)                       ((0x0000FFFF&(data))>>0)


#define DC_PC_SYSH_PROG_2_REQ_NUM                                                    0x18008078
#define DC_PC_SYSH_PROG_2_REQ_NUM_reg_addr                                           "0xB8008078"
#define DC_PC_SYSH_PROG_2_REQ_NUM_reg                                                0xB8008078
#define set_DC_PC_SYSH_PROG_2_REQ_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_SYSH_PROG_2_REQ_NUM_reg)=data)
#define get_DC_PC_SYSH_PROG_2_REQ_NUM_reg   (*((volatile unsigned int*) DC_PC_SYSH_PROG_2_REQ_NUM_reg))
#define DC_PC_SYSH_PROG_2_REQ_NUM_inst_adr                                           "0x001E"
#define DC_PC_SYSH_PROG_2_REQ_NUM_inst                                               0x001E
#define DC_PC_SYSH_PROG_2_REQ_NUM_sysh_prog2_req_num_shift                           (0)
#define DC_PC_SYSH_PROG_2_REQ_NUM_sysh_prog2_req_num_mask                            (0x00FFFFFF)
#define DC_PC_SYSH_PROG_2_REQ_NUM_sysh_prog2_req_num(data)                           (0x00FFFFFF&((data)<<0))
#define DC_PC_SYSH_PROG_2_REQ_NUM_sysh_prog2_req_num_src(data)                       ((0x00FFFFFF&(data))>>0)
#define DC_PC_SYSH_PROG_2_REQ_NUM_get_sysh_prog2_req_num(data)                       ((0x00FFFFFF&(data))>>0)


#define DC_PC_SYSH_PROG_2_ACK_NUM                                                    0x1800807C
#define DC_PC_SYSH_PROG_2_ACK_NUM_reg_addr                                           "0xB800807C"
#define DC_PC_SYSH_PROG_2_ACK_NUM_reg                                                0xB800807C
#define set_DC_PC_SYSH_PROG_2_ACK_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_SYSH_PROG_2_ACK_NUM_reg)=data)
#define get_DC_PC_SYSH_PROG_2_ACK_NUM_reg   (*((volatile unsigned int*) DC_PC_SYSH_PROG_2_ACK_NUM_reg))
#define DC_PC_SYSH_PROG_2_ACK_NUM_inst_adr                                           "0x001F"
#define DC_PC_SYSH_PROG_2_ACK_NUM_inst                                               0x001F
#define DC_PC_SYSH_PROG_2_ACK_NUM_sysh_prog2_ack_num_shift                           (0)
#define DC_PC_SYSH_PROG_2_ACK_NUM_sysh_prog2_ack_num_mask                            (0xFFFFFFFF)
#define DC_PC_SYSH_PROG_2_ACK_NUM_sysh_prog2_ack_num(data)                           (0xFFFFFFFF&((data)<<0))
#define DC_PC_SYSH_PROG_2_ACK_NUM_sysh_prog2_ack_num_src(data)                       ((0xFFFFFFFF&(data))>>0)
#define DC_PC_SYSH_PROG_2_ACK_NUM_get_sysh_prog2_ack_num(data)                       ((0xFFFFFFFF&(data))>>0)


#define DC_PC_SYS_PROG_0_ACC_LAT                                                     0x18008090
#define DC_PC_SYS_PROG_0_ACC_LAT_reg_addr                                            "0xB8008090"
#define DC_PC_SYS_PROG_0_ACC_LAT_reg                                                 0xB8008090
#define set_DC_PC_SYS_PROG_0_ACC_LAT_reg(data)   (*((volatile unsigned int*) DC_PC_SYS_PROG_0_ACC_LAT_reg)=data)
#define get_DC_PC_SYS_PROG_0_ACC_LAT_reg   (*((volatile unsigned int*) DC_PC_SYS_PROG_0_ACC_LAT_reg))
#define DC_PC_SYS_PROG_0_ACC_LAT_inst_adr                                            "0x0024"
#define DC_PC_SYS_PROG_0_ACC_LAT_inst                                                0x0024
#define DC_PC_SYS_PROG_0_ACC_LAT_sys_prog0_acc_lat_shift                             (0)
#define DC_PC_SYS_PROG_0_ACC_LAT_sys_prog0_acc_lat_mask                              (0xFFFFFFFF)
#define DC_PC_SYS_PROG_0_ACC_LAT_sys_prog0_acc_lat(data)                             (0xFFFFFFFF&((data)<<0))
#define DC_PC_SYS_PROG_0_ACC_LAT_sys_prog0_acc_lat_src(data)                         ((0xFFFFFFFF&(data))>>0)
#define DC_PC_SYS_PROG_0_ACC_LAT_get_sys_prog0_acc_lat(data)                         ((0xFFFFFFFF&(data))>>0)


#define DC_PC_SYS_PROG_0_MAX_LAT                                                     0x18008094
#define DC_PC_SYS_PROG_0_MAX_LAT_reg_addr                                            "0xB8008094"
#define DC_PC_SYS_PROG_0_MAX_LAT_reg                                                 0xB8008094
#define set_DC_PC_SYS_PROG_0_MAX_LAT_reg(data)   (*((volatile unsigned int*) DC_PC_SYS_PROG_0_MAX_LAT_reg)=data)
#define get_DC_PC_SYS_PROG_0_MAX_LAT_reg   (*((volatile unsigned int*) DC_PC_SYS_PROG_0_MAX_LAT_reg))
#define DC_PC_SYS_PROG_0_MAX_LAT_inst_adr                                            "0x0025"
#define DC_PC_SYS_PROG_0_MAX_LAT_inst                                                0x0025
#define DC_PC_SYS_PROG_0_MAX_LAT_sys_prog0_max_lat_shift                             (0)
#define DC_PC_SYS_PROG_0_MAX_LAT_sys_prog0_max_lat_mask                              (0x0000FFFF)
#define DC_PC_SYS_PROG_0_MAX_LAT_sys_prog0_max_lat(data)                             (0x0000FFFF&((data)<<0))
#define DC_PC_SYS_PROG_0_MAX_LAT_sys_prog0_max_lat_src(data)                         ((0x0000FFFF&(data))>>0)
#define DC_PC_SYS_PROG_0_MAX_LAT_get_sys_prog0_max_lat(data)                         ((0x0000FFFF&(data))>>0)


#define DC_PC_SYS_PROG_0_REQ_NUM                                                     0x18008098
#define DC_PC_SYS_PROG_0_REQ_NUM_reg_addr                                            "0xB8008098"
#define DC_PC_SYS_PROG_0_REQ_NUM_reg                                                 0xB8008098
#define set_DC_PC_SYS_PROG_0_REQ_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_SYS_PROG_0_REQ_NUM_reg)=data)
#define get_DC_PC_SYS_PROG_0_REQ_NUM_reg   (*((volatile unsigned int*) DC_PC_SYS_PROG_0_REQ_NUM_reg))
#define DC_PC_SYS_PROG_0_REQ_NUM_inst_adr                                            "0x0026"
#define DC_PC_SYS_PROG_0_REQ_NUM_inst                                                0x0026
#define DC_PC_SYS_PROG_0_REQ_NUM_sys_prog0_req_num_shift                             (0)
#define DC_PC_SYS_PROG_0_REQ_NUM_sys_prog0_req_num_mask                              (0x00FFFFFF)
#define DC_PC_SYS_PROG_0_REQ_NUM_sys_prog0_req_num(data)                             (0x00FFFFFF&((data)<<0))
#define DC_PC_SYS_PROG_0_REQ_NUM_sys_prog0_req_num_src(data)                         ((0x00FFFFFF&(data))>>0)
#define DC_PC_SYS_PROG_0_REQ_NUM_get_sys_prog0_req_num(data)                         ((0x00FFFFFF&(data))>>0)


#define DC_PC_SYS_PROG_0_ACK_NUM                                                     0x1800809C
#define DC_PC_SYS_PROG_0_ACK_NUM_reg_addr                                            "0xB800809C"
#define DC_PC_SYS_PROG_0_ACK_NUM_reg                                                 0xB800809C
#define set_DC_PC_SYS_PROG_0_ACK_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_SYS_PROG_0_ACK_NUM_reg)=data)
#define get_DC_PC_SYS_PROG_0_ACK_NUM_reg   (*((volatile unsigned int*) DC_PC_SYS_PROG_0_ACK_NUM_reg))
#define DC_PC_SYS_PROG_0_ACK_NUM_inst_adr                                            "0x0027"
#define DC_PC_SYS_PROG_0_ACK_NUM_inst                                                0x0027
#define DC_PC_SYS_PROG_0_ACK_NUM_sys_prog0_ack_num_shift                             (0)
#define DC_PC_SYS_PROG_0_ACK_NUM_sys_prog0_ack_num_mask                              (0xFFFFFFFF)
#define DC_PC_SYS_PROG_0_ACK_NUM_sys_prog0_ack_num(data)                             (0xFFFFFFFF&((data)<<0))
#define DC_PC_SYS_PROG_0_ACK_NUM_sys_prog0_ack_num_src(data)                         ((0xFFFFFFFF&(data))>>0)
#define DC_PC_SYS_PROG_0_ACK_NUM_get_sys_prog0_ack_num(data)                         ((0xFFFFFFFF&(data))>>0)


#define DC_PC_SYS_PROG_1_ACC_LAT                                                     0x180080A0
#define DC_PC_SYS_PROG_1_ACC_LAT_reg_addr                                            "0xB80080A0"
#define DC_PC_SYS_PROG_1_ACC_LAT_reg                                                 0xB80080A0
#define set_DC_PC_SYS_PROG_1_ACC_LAT_reg(data)   (*((volatile unsigned int*) DC_PC_SYS_PROG_1_ACC_LAT_reg)=data)
#define get_DC_PC_SYS_PROG_1_ACC_LAT_reg   (*((volatile unsigned int*) DC_PC_SYS_PROG_1_ACC_LAT_reg))
#define DC_PC_SYS_PROG_1_ACC_LAT_inst_adr                                            "0x0028"
#define DC_PC_SYS_PROG_1_ACC_LAT_inst                                                0x0028
#define DC_PC_SYS_PROG_1_ACC_LAT_sys_prog1_acc_lat_shift                             (0)
#define DC_PC_SYS_PROG_1_ACC_LAT_sys_prog1_acc_lat_mask                              (0xFFFFFFFF)
#define DC_PC_SYS_PROG_1_ACC_LAT_sys_prog1_acc_lat(data)                             (0xFFFFFFFF&((data)<<0))
#define DC_PC_SYS_PROG_1_ACC_LAT_sys_prog1_acc_lat_src(data)                         ((0xFFFFFFFF&(data))>>0)
#define DC_PC_SYS_PROG_1_ACC_LAT_get_sys_prog1_acc_lat(data)                         ((0xFFFFFFFF&(data))>>0)


#define DC_PC_SYS_PROG_1_MAX_LAT                                                     0x180080A4
#define DC_PC_SYS_PROG_1_MAX_LAT_reg_addr                                            "0xB80080A4"
#define DC_PC_SYS_PROG_1_MAX_LAT_reg                                                 0xB80080A4
#define set_DC_PC_SYS_PROG_1_MAX_LAT_reg(data)   (*((volatile unsigned int*) DC_PC_SYS_PROG_1_MAX_LAT_reg)=data)
#define get_DC_PC_SYS_PROG_1_MAX_LAT_reg   (*((volatile unsigned int*) DC_PC_SYS_PROG_1_MAX_LAT_reg))
#define DC_PC_SYS_PROG_1_MAX_LAT_inst_adr                                            "0x0029"
#define DC_PC_SYS_PROG_1_MAX_LAT_inst                                                0x0029
#define DC_PC_SYS_PROG_1_MAX_LAT_sys_prog1_max_lat_shift                             (0)
#define DC_PC_SYS_PROG_1_MAX_LAT_sys_prog1_max_lat_mask                              (0x0000FFFF)
#define DC_PC_SYS_PROG_1_MAX_LAT_sys_prog1_max_lat(data)                             (0x0000FFFF&((data)<<0))
#define DC_PC_SYS_PROG_1_MAX_LAT_sys_prog1_max_lat_src(data)                         ((0x0000FFFF&(data))>>0)
#define DC_PC_SYS_PROG_1_MAX_LAT_get_sys_prog1_max_lat(data)                         ((0x0000FFFF&(data))>>0)


#define DC_PC_SYS_PROG_1_REQ_NUM                                                     0x180080A8
#define DC_PC_SYS_PROG_1_REQ_NUM_reg_addr                                            "0xB80080A8"
#define DC_PC_SYS_PROG_1_REQ_NUM_reg                                                 0xB80080A8
#define set_DC_PC_SYS_PROG_1_REQ_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_SYS_PROG_1_REQ_NUM_reg)=data)
#define get_DC_PC_SYS_PROG_1_REQ_NUM_reg   (*((volatile unsigned int*) DC_PC_SYS_PROG_1_REQ_NUM_reg))
#define DC_PC_SYS_PROG_1_REQ_NUM_inst_adr                                            "0x002A"
#define DC_PC_SYS_PROG_1_REQ_NUM_inst                                                0x002A
#define DC_PC_SYS_PROG_1_REQ_NUM_sys_prog1_req_num_shift                             (0)
#define DC_PC_SYS_PROG_1_REQ_NUM_sys_prog1_req_num_mask                              (0x00FFFFFF)
#define DC_PC_SYS_PROG_1_REQ_NUM_sys_prog1_req_num(data)                             (0x00FFFFFF&((data)<<0))
#define DC_PC_SYS_PROG_1_REQ_NUM_sys_prog1_req_num_src(data)                         ((0x00FFFFFF&(data))>>0)
#define DC_PC_SYS_PROG_1_REQ_NUM_get_sys_prog1_req_num(data)                         ((0x00FFFFFF&(data))>>0)


#define DC_PC_SYS_PROG_1_ACK_NUM                                                     0x180080AC
#define DC_PC_SYS_PROG_1_ACK_NUM_reg_addr                                            "0xB80080AC"
#define DC_PC_SYS_PROG_1_ACK_NUM_reg                                                 0xB80080AC
#define set_DC_PC_SYS_PROG_1_ACK_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_SYS_PROG_1_ACK_NUM_reg)=data)
#define get_DC_PC_SYS_PROG_1_ACK_NUM_reg   (*((volatile unsigned int*) DC_PC_SYS_PROG_1_ACK_NUM_reg))
#define DC_PC_SYS_PROG_1_ACK_NUM_inst_adr                                            "0x002B"
#define DC_PC_SYS_PROG_1_ACK_NUM_inst                                                0x002B
#define DC_PC_SYS_PROG_1_ACK_NUM_sys_prog1_ack_num_shift                             (0)
#define DC_PC_SYS_PROG_1_ACK_NUM_sys_prog1_ack_num_mask                              (0xFFFFFFFF)
#define DC_PC_SYS_PROG_1_ACK_NUM_sys_prog1_ack_num(data)                             (0xFFFFFFFF&((data)<<0))
#define DC_PC_SYS_PROG_1_ACK_NUM_sys_prog1_ack_num_src(data)                         ((0xFFFFFFFF&(data))>>0)
#define DC_PC_SYS_PROG_1_ACK_NUM_get_sys_prog1_ack_num(data)                         ((0xFFFFFFFF&(data))>>0)


#define DC_PC_SYS_PROG_2_ACC_LAT                                                     0x180080B0
#define DC_PC_SYS_PROG_2_ACC_LAT_reg_addr                                            "0xB80080B0"
#define DC_PC_SYS_PROG_2_ACC_LAT_reg                                                 0xB80080B0
#define set_DC_PC_SYS_PROG_2_ACC_LAT_reg(data)   (*((volatile unsigned int*) DC_PC_SYS_PROG_2_ACC_LAT_reg)=data)
#define get_DC_PC_SYS_PROG_2_ACC_LAT_reg   (*((volatile unsigned int*) DC_PC_SYS_PROG_2_ACC_LAT_reg))
#define DC_PC_SYS_PROG_2_ACC_LAT_inst_adr                                            "0x002C"
#define DC_PC_SYS_PROG_2_ACC_LAT_inst                                                0x002C
#define DC_PC_SYS_PROG_2_ACC_LAT_sys_prog2_acc_lat_shift                             (0)
#define DC_PC_SYS_PROG_2_ACC_LAT_sys_prog2_acc_lat_mask                              (0xFFFFFFFF)
#define DC_PC_SYS_PROG_2_ACC_LAT_sys_prog2_acc_lat(data)                             (0xFFFFFFFF&((data)<<0))
#define DC_PC_SYS_PROG_2_ACC_LAT_sys_prog2_acc_lat_src(data)                         ((0xFFFFFFFF&(data))>>0)
#define DC_PC_SYS_PROG_2_ACC_LAT_get_sys_prog2_acc_lat(data)                         ((0xFFFFFFFF&(data))>>0)


#define DC_PC_SYS_PROG_2_MAX_LAT                                                     0x180080B4
#define DC_PC_SYS_PROG_2_MAX_LAT_reg_addr                                            "0xB80080B4"
#define DC_PC_SYS_PROG_2_MAX_LAT_reg                                                 0xB80080B4
#define set_DC_PC_SYS_PROG_2_MAX_LAT_reg(data)   (*((volatile unsigned int*) DC_PC_SYS_PROG_2_MAX_LAT_reg)=data)
#define get_DC_PC_SYS_PROG_2_MAX_LAT_reg   (*((volatile unsigned int*) DC_PC_SYS_PROG_2_MAX_LAT_reg))
#define DC_PC_SYS_PROG_2_MAX_LAT_inst_adr                                            "0x002D"
#define DC_PC_SYS_PROG_2_MAX_LAT_inst                                                0x002D
#define DC_PC_SYS_PROG_2_MAX_LAT_sys_prog2_max_lat_shift                             (0)
#define DC_PC_SYS_PROG_2_MAX_LAT_sys_prog2_max_lat_mask                              (0x0000FFFF)
#define DC_PC_SYS_PROG_2_MAX_LAT_sys_prog2_max_lat(data)                             (0x0000FFFF&((data)<<0))
#define DC_PC_SYS_PROG_2_MAX_LAT_sys_prog2_max_lat_src(data)                         ((0x0000FFFF&(data))>>0)
#define DC_PC_SYS_PROG_2_MAX_LAT_get_sys_prog2_max_lat(data)                         ((0x0000FFFF&(data))>>0)


#define DC_PC_SYS_PROG_2_REQ_NUM                                                     0x180080B8
#define DC_PC_SYS_PROG_2_REQ_NUM_reg_addr                                            "0xB80080B8"
#define DC_PC_SYS_PROG_2_REQ_NUM_reg                                                 0xB80080B8
#define set_DC_PC_SYS_PROG_2_REQ_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_SYS_PROG_2_REQ_NUM_reg)=data)
#define get_DC_PC_SYS_PROG_2_REQ_NUM_reg   (*((volatile unsigned int*) DC_PC_SYS_PROG_2_REQ_NUM_reg))
#define DC_PC_SYS_PROG_2_REQ_NUM_inst_adr                                            "0x002E"
#define DC_PC_SYS_PROG_2_REQ_NUM_inst                                                0x002E
#define DC_PC_SYS_PROG_2_REQ_NUM_sys_prog2_req_num_shift                             (0)
#define DC_PC_SYS_PROG_2_REQ_NUM_sys_prog2_req_num_mask                              (0x00FFFFFF)
#define DC_PC_SYS_PROG_2_REQ_NUM_sys_prog2_req_num(data)                             (0x00FFFFFF&((data)<<0))
#define DC_PC_SYS_PROG_2_REQ_NUM_sys_prog2_req_num_src(data)                         ((0x00FFFFFF&(data))>>0)
#define DC_PC_SYS_PROG_2_REQ_NUM_get_sys_prog2_req_num(data)                         ((0x00FFFFFF&(data))>>0)


#define DC_PC_SYS_PROG_2_ACK_NUM                                                     0x180080BC
#define DC_PC_SYS_PROG_2_ACK_NUM_reg_addr                                            "0xB80080BC"
#define DC_PC_SYS_PROG_2_ACK_NUM_reg                                                 0xB80080BC
#define set_DC_PC_SYS_PROG_2_ACK_NUM_reg(data)   (*((volatile unsigned int*) DC_PC_SYS_PROG_2_ACK_NUM_reg)=data)
#define get_DC_PC_SYS_PROG_2_ACK_NUM_reg   (*((volatile unsigned int*) DC_PC_SYS_PROG_2_ACK_NUM_reg))
#define DC_PC_SYS_PROG_2_ACK_NUM_inst_adr                                            "0x002F"
#define DC_PC_SYS_PROG_2_ACK_NUM_inst                                                0x002F
#define DC_PC_SYS_PROG_2_ACK_NUM_sys_prog2_ack_num_shift                             (0)
#define DC_PC_SYS_PROG_2_ACK_NUM_sys_prog2_ack_num_mask                              (0xFFFFFFFF)
#define DC_PC_SYS_PROG_2_ACK_NUM_sys_prog2_ack_num(data)                             (0xFFFFFFFF&((data)<<0))
#define DC_PC_SYS_PROG_2_ACK_NUM_sys_prog2_ack_num_src(data)                         ((0xFFFFFFFF&(data))>>0)
#define DC_PC_SYS_PROG_2_ACK_NUM_get_sys_prog2_ack_num(data)                         ((0xFFFFFFFF&(data))>>0)


#define SFMODE_PATTERN0                                                              0x180080C0
#define SFMODE_PATTERN0_reg_addr                                                     "0xB80080C0"
#define SFMODE_PATTERN0_reg                                                          0xB80080C0
#define set_SFMODE_PATTERN0_reg(data)   (*((volatile unsigned int*) SFMODE_PATTERN0_reg)=data)
#define get_SFMODE_PATTERN0_reg   (*((volatile unsigned int*) SFMODE_PATTERN0_reg))
#define SFMODE_PATTERN0_inst_adr                                                     "0x0030"
#define SFMODE_PATTERN0_inst                                                         0x0030
#define SFMODE_PATTERN0_sfmode_pattern0_shift                                        (0)
#define SFMODE_PATTERN0_sfmode_pattern0_mask                                         (0xFFFFFFFF)
#define SFMODE_PATTERN0_sfmode_pattern0(data)                                        (0xFFFFFFFF&((data)<<0))
#define SFMODE_PATTERN0_sfmode_pattern0_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define SFMODE_PATTERN0_get_sfmode_pattern0(data)                                    ((0xFFFFFFFF&(data))>>0)


#define SFMODE_PATTERN1                                                              0x180080C4
#define SFMODE_PATTERN1_reg_addr                                                     "0xB80080C4"
#define SFMODE_PATTERN1_reg                                                          0xB80080C4
#define set_SFMODE_PATTERN1_reg(data)   (*((volatile unsigned int*) SFMODE_PATTERN1_reg)=data)
#define get_SFMODE_PATTERN1_reg   (*((volatile unsigned int*) SFMODE_PATTERN1_reg))
#define SFMODE_PATTERN1_inst_adr                                                     "0x0031"
#define SFMODE_PATTERN1_inst                                                         0x0031
#define SFMODE_PATTERN1_sfmode_pattern1_shift                                        (0)
#define SFMODE_PATTERN1_sfmode_pattern1_mask                                         (0xFFFFFFFF)
#define SFMODE_PATTERN1_sfmode_pattern1(data)                                        (0xFFFFFFFF&((data)<<0))
#define SFMODE_PATTERN1_sfmode_pattern1_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define SFMODE_PATTERN1_get_sfmode_pattern1(data)                                    ((0xFFFFFFFF&(data))>>0)


#define SFMODE_PATTERN2                                                              0x180080C8
#define SFMODE_PATTERN2_reg_addr                                                     "0xB80080C8"
#define SFMODE_PATTERN2_reg                                                          0xB80080C8
#define set_SFMODE_PATTERN2_reg(data)   (*((volatile unsigned int*) SFMODE_PATTERN2_reg)=data)
#define get_SFMODE_PATTERN2_reg   (*((volatile unsigned int*) SFMODE_PATTERN2_reg))
#define SFMODE_PATTERN2_inst_adr                                                     "0x0032"
#define SFMODE_PATTERN2_inst                                                         0x0032
#define SFMODE_PATTERN2_sfmode_pattern2_shift                                        (0)
#define SFMODE_PATTERN2_sfmode_pattern2_mask                                         (0xFFFFFFFF)
#define SFMODE_PATTERN2_sfmode_pattern2(data)                                        (0xFFFFFFFF&((data)<<0))
#define SFMODE_PATTERN2_sfmode_pattern2_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define SFMODE_PATTERN2_get_sfmode_pattern2(data)                                    ((0xFFFFFFFF&(data))>>0)


#define SFMODE_PATTERN3                                                              0x180080CC
#define SFMODE_PATTERN3_reg_addr                                                     "0xB80080CC"
#define SFMODE_PATTERN3_reg                                                          0xB80080CC
#define set_SFMODE_PATTERN3_reg(data)   (*((volatile unsigned int*) SFMODE_PATTERN3_reg)=data)
#define get_SFMODE_PATTERN3_reg   (*((volatile unsigned int*) SFMODE_PATTERN3_reg))
#define SFMODE_PATTERN3_inst_adr                                                     "0x0033"
#define SFMODE_PATTERN3_inst                                                         0x0033
#define SFMODE_PATTERN3_sfmode_pattern3_shift                                        (0)
#define SFMODE_PATTERN3_sfmode_pattern3_mask                                         (0xFFFFFFFF)
#define SFMODE_PATTERN3_sfmode_pattern3(data)                                        (0xFFFFFFFF&((data)<<0))
#define SFMODE_PATTERN3_sfmode_pattern3_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define SFMODE_PATTERN3_get_sfmode_pattern3(data)                                    ((0xFFFFFFFF&(data))>>0)


#define SFMODE_CMP_RLT0                                                              0x180080D0
#define SFMODE_CMP_RLT0_reg_addr                                                     "0xB80080D0"
#define SFMODE_CMP_RLT0_reg                                                          0xB80080D0
#define set_SFMODE_CMP_RLT0_reg(data)   (*((volatile unsigned int*) SFMODE_CMP_RLT0_reg)=data)
#define get_SFMODE_CMP_RLT0_reg   (*((volatile unsigned int*) SFMODE_CMP_RLT0_reg))
#define SFMODE_CMP_RLT0_inst_adr                                                     "0x0034"
#define SFMODE_CMP_RLT0_inst                                                         0x0034
#define SFMODE_CMP_RLT0_sfmode_cmp_rlt0_shift                                        (0)
#define SFMODE_CMP_RLT0_sfmode_cmp_rlt0_mask                                         (0xFFFFFFFF)
#define SFMODE_CMP_RLT0_sfmode_cmp_rlt0(data)                                        (0xFFFFFFFF&((data)<<0))
#define SFMODE_CMP_RLT0_sfmode_cmp_rlt0_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define SFMODE_CMP_RLT0_get_sfmode_cmp_rlt0(data)                                    ((0xFFFFFFFF&(data))>>0)


#define SFMODE_CMP_RLT1                                                              0x180080D4
#define SFMODE_CMP_RLT1_reg_addr                                                     "0xB80080D4"
#define SFMODE_CMP_RLT1_reg                                                          0xB80080D4
#define set_SFMODE_CMP_RLT1_reg(data)   (*((volatile unsigned int*) SFMODE_CMP_RLT1_reg)=data)
#define get_SFMODE_CMP_RLT1_reg   (*((volatile unsigned int*) SFMODE_CMP_RLT1_reg))
#define SFMODE_CMP_RLT1_inst_adr                                                     "0x0035"
#define SFMODE_CMP_RLT1_inst                                                         0x0035
#define SFMODE_CMP_RLT1_sfmode_cmp_rlt1_shift                                        (0)
#define SFMODE_CMP_RLT1_sfmode_cmp_rlt1_mask                                         (0xFFFFFFFF)
#define SFMODE_CMP_RLT1_sfmode_cmp_rlt1(data)                                        (0xFFFFFFFF&((data)<<0))
#define SFMODE_CMP_RLT1_sfmode_cmp_rlt1_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define SFMODE_CMP_RLT1_get_sfmode_cmp_rlt1(data)                                    ((0xFFFFFFFF&(data))>>0)


#define SFMODE_CMP_RLT2                                                              0x180080D8
#define SFMODE_CMP_RLT2_reg_addr                                                     "0xB80080D8"
#define SFMODE_CMP_RLT2_reg                                                          0xB80080D8
#define set_SFMODE_CMP_RLT2_reg(data)   (*((volatile unsigned int*) SFMODE_CMP_RLT2_reg)=data)
#define get_SFMODE_CMP_RLT2_reg   (*((volatile unsigned int*) SFMODE_CMP_RLT2_reg))
#define SFMODE_CMP_RLT2_inst_adr                                                     "0x0036"
#define SFMODE_CMP_RLT2_inst                                                         0x0036
#define SFMODE_CMP_RLT2_sfmode_cmp_rlt2_shift                                        (0)
#define SFMODE_CMP_RLT2_sfmode_cmp_rlt2_mask                                         (0xFFFFFFFF)
#define SFMODE_CMP_RLT2_sfmode_cmp_rlt2(data)                                        (0xFFFFFFFF&((data)<<0))
#define SFMODE_CMP_RLT2_sfmode_cmp_rlt2_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define SFMODE_CMP_RLT2_get_sfmode_cmp_rlt2(data)                                    ((0xFFFFFFFF&(data))>>0)


#define SFMODE_CMP_RLT3                                                              0x180080DC
#define SFMODE_CMP_RLT3_reg_addr                                                     "0xB80080DC"
#define SFMODE_CMP_RLT3_reg                                                          0xB80080DC
#define set_SFMODE_CMP_RLT3_reg(data)   (*((volatile unsigned int*) SFMODE_CMP_RLT3_reg)=data)
#define get_SFMODE_CMP_RLT3_reg   (*((volatile unsigned int*) SFMODE_CMP_RLT3_reg))
#define SFMODE_CMP_RLT3_inst_adr                                                     "0x0037"
#define SFMODE_CMP_RLT3_inst                                                         0x0037
#define SFMODE_CMP_RLT3_sfmode_cmp_rlt3_shift                                        (0)
#define SFMODE_CMP_RLT3_sfmode_cmp_rlt3_mask                                         (0xFFFFFFFF)
#define SFMODE_CMP_RLT3_sfmode_cmp_rlt3(data)                                        (0xFFFFFFFF&((data)<<0))
#define SFMODE_CMP_RLT3_sfmode_cmp_rlt3_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define SFMODE_CMP_RLT3_get_sfmode_cmp_rlt3(data)                                    ((0xFFFFFFFF&(data))>>0)


#define DC_64_WRITE_BUF_CTRL                                                         0x180080E0
#define DC_64_WRITE_BUF_CTRL_reg_addr                                                "0xB80080E0"
#define DC_64_WRITE_BUF_CTRL_reg                                                     0xB80080E0
#define set_DC_64_WRITE_BUF_CTRL_reg(data)   (*((volatile unsigned int*) DC_64_WRITE_BUF_CTRL_reg)=data)
#define get_DC_64_WRITE_BUF_CTRL_reg   (*((volatile unsigned int*) DC_64_WRITE_BUF_CTRL_reg))
#define DC_64_WRITE_BUF_CTRL_inst_adr                                                "0x0038"
#define DC_64_WRITE_BUF_CTRL_inst                                                    0x0038
#define DC_64_WRITE_BUF_CTRL_disable_2nd_channel_shift                               (1)
#define DC_64_WRITE_BUF_CTRL_disable_2nd_channel_mask                                (0x00000002)
#define DC_64_WRITE_BUF_CTRL_disable_2nd_channel(data)                               (0x00000002&((data)<<1))
#define DC_64_WRITE_BUF_CTRL_disable_2nd_channel_src(data)                           ((0x00000002&(data))>>1)
#define DC_64_WRITE_BUF_CTRL_get_disable_2nd_channel(data)                           ((0x00000002&(data))>>1)
#define DC_64_WRITE_BUF_CTRL_full_transfer_shift                                     (0)
#define DC_64_WRITE_BUF_CTRL_full_transfer_mask                                      (0x00000001)
#define DC_64_WRITE_BUF_CTRL_full_transfer(data)                                     (0x00000001&((data)<<0))
#define DC_64_WRITE_BUF_CTRL_full_transfer_src(data)                                 ((0x00000001&(data))>>0)
#define DC_64_WRITE_BUF_CTRL_get_full_transfer(data)                                 ((0x00000001&(data))>>0)


#define DC_64_READ_BUF_CTRL                                                          0x180080E4
#define DC_64_READ_BUF_CTRL_reg_addr                                                 "0xB80080E4"
#define DC_64_READ_BUF_CTRL_reg                                                      0xB80080E4
#define set_DC_64_READ_BUF_CTRL_reg(data)   (*((volatile unsigned int*) DC_64_READ_BUF_CTRL_reg)=data)
#define get_DC_64_READ_BUF_CTRL_reg   (*((volatile unsigned int*) DC_64_READ_BUF_CTRL_reg))
#define DC_64_READ_BUF_CTRL_inst_adr                                                 "0x0039"
#define DC_64_READ_BUF_CTRL_inst                                                     0x0039
#define DC_64_READ_BUF_CTRL_sync_cmd_cnt_threshold_shift                             (21)
#define DC_64_READ_BUF_CTRL_sync_cmd_cnt_threshold_mask                              (0x00E00000)
#define DC_64_READ_BUF_CTRL_sync_cmd_cnt_threshold(data)                             (0x00E00000&((data)<<21))
#define DC_64_READ_BUF_CTRL_sync_cmd_cnt_threshold_src(data)                         ((0x00E00000&(data))>>21)
#define DC_64_READ_BUF_CTRL_get_sync_cmd_cnt_threshold(data)                         ((0x00E00000&(data))>>21)
#define DC_64_READ_BUF_CTRL_cmd_buf_threshold_shift                                  (17)
#define DC_64_READ_BUF_CTRL_cmd_buf_threshold_mask                                   (0x001E0000)
#define DC_64_READ_BUF_CTRL_cmd_buf_threshold(data)                                  (0x001E0000&((data)<<17))
#define DC_64_READ_BUF_CTRL_cmd_buf_threshold_src(data)                              ((0x001E0000&(data))>>17)
#define DC_64_READ_BUF_CTRL_get_cmd_buf_threshold(data)                              ((0x001E0000&(data))>>17)
#define DC_64_READ_BUF_CTRL_disable_2nd_channel_shift                                (16)
#define DC_64_READ_BUF_CTRL_disable_2nd_channel_mask                                 (0x00010000)
#define DC_64_READ_BUF_CTRL_disable_2nd_channel(data)                                (0x00010000&((data)<<16))
#define DC_64_READ_BUF_CTRL_disable_2nd_channel_src(data)                            ((0x00010000&(data))>>16)
#define DC_64_READ_BUF_CTRL_get_disable_2nd_channel(data)                            ((0x00010000&(data))>>16)
#define DC_64_READ_BUF_CTRL_ever_full_shift                                          (15)
#define DC_64_READ_BUF_CTRL_ever_full_mask                                           (0x00008000)
#define DC_64_READ_BUF_CTRL_ever_full(data)                                          (0x00008000&((data)<<15))
#define DC_64_READ_BUF_CTRL_ever_full_src(data)                                      ((0x00008000&(data))>>15)
#define DC_64_READ_BUF_CTRL_get_ever_full(data)                                      ((0x00008000&(data))>>15)
#define DC_64_READ_BUF_CTRL_ever_reach_threshold_shift                               (14)
#define DC_64_READ_BUF_CTRL_ever_reach_threshold_mask                                (0x00004000)
#define DC_64_READ_BUF_CTRL_ever_reach_threshold(data)                               (0x00004000&((data)<<14))
#define DC_64_READ_BUF_CTRL_ever_reach_threshold_src(data)                           ((0x00004000&(data))>>14)
#define DC_64_READ_BUF_CTRL_get_ever_reach_threshold(data)                           ((0x00004000&(data))>>14)
#define DC_64_READ_BUF_CTRL_max_buf_level_shift                                      (7)
#define DC_64_READ_BUF_CTRL_max_buf_level_mask                                       (0x00003F80)
#define DC_64_READ_BUF_CTRL_max_buf_level(data)                                      (0x00003F80&((data)<<7))
#define DC_64_READ_BUF_CTRL_max_buf_level_src(data)                                  ((0x00003F80&(data))>>7)
#define DC_64_READ_BUF_CTRL_get_max_buf_level(data)                                  ((0x00003F80&(data))>>7)
#define DC_64_READ_BUF_CTRL_grant_stop_level_shift                                   (0)
#define DC_64_READ_BUF_CTRL_grant_stop_level_mask                                    (0x0000007F)
#define DC_64_READ_BUF_CTRL_grant_stop_level(data)                                   (0x0000007F&((data)<<0))
#define DC_64_READ_BUF_CTRL_grant_stop_level_src(data)                               ((0x0000007F&(data))>>0)
#define DC_64_READ_BUF_CTRL_get_grant_stop_level(data)                               ((0x0000007F&(data))>>0)


#define DC_PIC_OFFSET_X_DETECTION                                                    0x18008110
#define DC_PIC_OFFSET_X_DETECTION_reg_addr                                           "0xB8008110"
#define DC_PIC_OFFSET_X_DETECTION_reg                                                0xB8008110
#define set_DC_PIC_OFFSET_X_DETECTION_reg(data)   (*((volatile unsigned int*) DC_PIC_OFFSET_X_DETECTION_reg)=data)
#define get_DC_PIC_OFFSET_X_DETECTION_reg   (*((volatile unsigned int*) DC_PIC_OFFSET_X_DETECTION_reg))
#define DC_PIC_OFFSET_X_DETECTION_inst_adr                                           "0x0044"
#define DC_PIC_OFFSET_X_DETECTION_inst                                               0x0044
#define DC_PIC_OFFSET_X_DETECTION_pict_set_int_cpu_shift                             (3)
#define DC_PIC_OFFSET_X_DETECTION_pict_set_int_cpu_mask                              (0x00000018)
#define DC_PIC_OFFSET_X_DETECTION_pict_set_int_cpu(data)                             (0x00000018&((data)<<3))
#define DC_PIC_OFFSET_X_DETECTION_pict_set_int_cpu_src(data)                         ((0x00000018&(data))>>3)
#define DC_PIC_OFFSET_X_DETECTION_get_pict_set_int_cpu(data)                         ((0x00000018&(data))>>3)
#define DC_PIC_OFFSET_X_DETECTION_int_enable_shift                                   (2)
#define DC_PIC_OFFSET_X_DETECTION_int_enable_mask                                    (0x00000004)
#define DC_PIC_OFFSET_X_DETECTION_int_enable(data)                                   (0x00000004&((data)<<2))
#define DC_PIC_OFFSET_X_DETECTION_int_enable_src(data)                               ((0x00000004&(data))>>2)
#define DC_PIC_OFFSET_X_DETECTION_get_int_enable(data)                               ((0x00000004&(data))>>2)
#define DC_PIC_OFFSET_X_DETECTION_ever_set_as_odd_shift                              (1)
#define DC_PIC_OFFSET_X_DETECTION_ever_set_as_odd_mask                               (0x00000002)
#define DC_PIC_OFFSET_X_DETECTION_ever_set_as_odd(data)                              (0x00000002&((data)<<1))
#define DC_PIC_OFFSET_X_DETECTION_ever_set_as_odd_src(data)                          ((0x00000002&(data))>>1)
#define DC_PIC_OFFSET_X_DETECTION_get_ever_set_as_odd(data)                          ((0x00000002&(data))>>1)
#define DC_PIC_OFFSET_X_DETECTION_enable_shift                                       (0)
#define DC_PIC_OFFSET_X_DETECTION_enable_mask                                        (0x00000001)
#define DC_PIC_OFFSET_X_DETECTION_enable(data)                                       (0x00000001&((data)<<0))
#define DC_PIC_OFFSET_X_DETECTION_enable_src(data)                                   ((0x00000001&(data))>>0)
#define DC_PIC_OFFSET_X_DETECTION_get_enable(data)                                   ((0x00000001&(data))>>0)


#define PHY_BIST_RM                                                                  0x180081B0
#define PHY_BIST_RM_reg_addr                                                         "0xB80081B0"
#define PHY_BIST_RM_reg                                                              0xB80081B0
#define set_PHY_BIST_RM_reg(data)   (*((volatile unsigned int*) PHY_BIST_RM_reg)=data)
#define get_PHY_BIST_RM_reg   (*((volatile unsigned int*) PHY_BIST_RM_reg))
#define PHY_BIST_RM_inst_adr                                                         "0x006C"
#define PHY_BIST_RM_inst                                                             0x006C
#define PHY_BIST_RM_bist_en_0_shift                                                  (16)
#define PHY_BIST_RM_bist_en_0_mask                                                   (0x00010000)
#define PHY_BIST_RM_bist_en_0(data)                                                  (0x00010000&((data)<<16))
#define PHY_BIST_RM_bist_en_0_src(data)                                              ((0x00010000&(data))>>16)
#define PHY_BIST_RM_get_bist_en_0(data)                                              ((0x00010000&(data))>>16)
#define PHY_BIST_RM_drf_bist_en_0_shift                                              (15)
#define PHY_BIST_RM_drf_bist_en_0_mask                                               (0x00008000)
#define PHY_BIST_RM_drf_bist_en_0(data)                                              (0x00008000&((data)<<15))
#define PHY_BIST_RM_drf_bist_en_0_src(data)                                          ((0x00008000&(data))>>15)
#define PHY_BIST_RM_get_drf_bist_en_0(data)                                          ((0x00008000&(data))>>15)
#define PHY_BIST_RM_drf_test_resume_0_shift                                          (14)
#define PHY_BIST_RM_drf_test_resume_0_mask                                           (0x00004000)
#define PHY_BIST_RM_drf_test_resume_0(data)                                          (0x00004000&((data)<<14))
#define PHY_BIST_RM_drf_test_resume_0_src(data)                                      ((0x00004000&(data))>>14)
#define PHY_BIST_RM_get_drf_test_resume_0(data)                                      ((0x00004000&(data))>>14)
#define PHY_BIST_RM_RMEA_shift                                                       (12)
#define PHY_BIST_RM_RMEA_mask                                                        (0x00001000)
#define PHY_BIST_RM_RMEA(data)                                                       (0x00001000&((data)<<12))
#define PHY_BIST_RM_RMEA_src(data)                                                   ((0x00001000&(data))>>12)
#define PHY_BIST_RM_get_RMEA(data)                                                   ((0x00001000&(data))>>12)
#define PHY_BIST_RM_RMA_3_shift                                                      (11)
#define PHY_BIST_RM_RMA_3_mask                                                       (0x00000800)
#define PHY_BIST_RM_RMA_3(data)                                                      (0x00000800&((data)<<11))
#define PHY_BIST_RM_RMA_3_src(data)                                                  ((0x00000800&(data))>>11)
#define PHY_BIST_RM_get_RMA_3(data)                                                  ((0x00000800&(data))>>11)
#define PHY_BIST_RM_RMA_2_shift                                                      (10)
#define PHY_BIST_RM_RMA_2_mask                                                       (0x00000400)
#define PHY_BIST_RM_RMA_2(data)                                                      (0x00000400&((data)<<10))
#define PHY_BIST_RM_RMA_2_src(data)                                                  ((0x00000400&(data))>>10)
#define PHY_BIST_RM_get_RMA_2(data)                                                  ((0x00000400&(data))>>10)
#define PHY_BIST_RM_RMA_1_shift                                                      (9)
#define PHY_BIST_RM_RMA_1_mask                                                       (0x00000200)
#define PHY_BIST_RM_RMA_1(data)                                                      (0x00000200&((data)<<9))
#define PHY_BIST_RM_RMA_1_src(data)                                                  ((0x00000200&(data))>>9)
#define PHY_BIST_RM_get_RMA_1(data)                                                  ((0x00000200&(data))>>9)
#define PHY_BIST_RM_RMA_0_shift                                                      (8)
#define PHY_BIST_RM_RMA_0_mask                                                       (0x00000100)
#define PHY_BIST_RM_RMA_0(data)                                                      (0x00000100&((data)<<8))
#define PHY_BIST_RM_RMA_0_src(data)                                                  ((0x00000100&(data))>>8)
#define PHY_BIST_RM_get_RMA_0(data)                                                  ((0x00000100&(data))>>8)
#define PHY_BIST_RM_RMEB_shift                                                       (4)
#define PHY_BIST_RM_RMEB_mask                                                        (0x00000010)
#define PHY_BIST_RM_RMEB(data)                                                       (0x00000010&((data)<<4))
#define PHY_BIST_RM_RMEB_src(data)                                                   ((0x00000010&(data))>>4)
#define PHY_BIST_RM_get_RMEB(data)                                                   ((0x00000010&(data))>>4)
#define PHY_BIST_RM_RMB_3_shift                                                      (3)
#define PHY_BIST_RM_RMB_3_mask                                                       (0x00000008)
#define PHY_BIST_RM_RMB_3(data)                                                      (0x00000008&((data)<<3))
#define PHY_BIST_RM_RMB_3_src(data)                                                  ((0x00000008&(data))>>3)
#define PHY_BIST_RM_get_RMB_3(data)                                                  ((0x00000008&(data))>>3)
#define PHY_BIST_RM_RMB_2_shift                                                      (2)
#define PHY_BIST_RM_RMB_2_mask                                                       (0x00000004)
#define PHY_BIST_RM_RMB_2(data)                                                      (0x00000004&((data)<<2))
#define PHY_BIST_RM_RMB_2_src(data)                                                  ((0x00000004&(data))>>2)
#define PHY_BIST_RM_get_RMB_2(data)                                                  ((0x00000004&(data))>>2)
#define PHY_BIST_RM_RMB_1_shift                                                      (1)
#define PHY_BIST_RM_RMB_1_mask                                                       (0x00000002)
#define PHY_BIST_RM_RMB_1(data)                                                      (0x00000002&((data)<<1))
#define PHY_BIST_RM_RMB_1_src(data)                                                  ((0x00000002&(data))>>1)
#define PHY_BIST_RM_get_RMB_1(data)                                                  ((0x00000002&(data))>>1)
#define PHY_BIST_RM_RMB_0_shift                                                      (0)
#define PHY_BIST_RM_RMB_0_mask                                                       (0x00000001)
#define PHY_BIST_RM_RMB_0(data)                                                      (0x00000001&((data)<<0))
#define PHY_BIST_RM_RMB_0_src(data)                                                  ((0x00000001&(data))>>0)
#define PHY_BIST_RM_get_RMB_0(data)                                                  ((0x00000001&(data))>>0)


#define PHY_BIST0_ST                                                                 0x180081B4
#define PHY_BIST0_ST_reg_addr                                                        "0xB80081B4"
#define PHY_BIST0_ST_reg                                                             0xB80081B4
#define set_PHY_BIST0_ST_reg(data)   (*((volatile unsigned int*) PHY_BIST0_ST_reg)=data)
#define get_PHY_BIST0_ST_reg   (*((volatile unsigned int*) PHY_BIST0_ST_reg))
#define PHY_BIST0_ST_inst_adr                                                        "0x006D"
#define PHY_BIST0_ST_inst                                                            0x006D
#define PHY_BIST0_ST_mbist_st_shift                                                  (2)
#define PHY_BIST0_ST_mbist_st_mask                                                   (0x00000004)
#define PHY_BIST0_ST_mbist_st(data)                                                  (0x00000004&((data)<<2))
#define PHY_BIST0_ST_mbist_st_src(data)                                              ((0x00000004&(data))>>2)
#define PHY_BIST0_ST_get_mbist_st(data)                                              ((0x00000004&(data))>>2)
#define PHY_BIST0_ST_bist_fail_shift                                                 (1)
#define PHY_BIST0_ST_bist_fail_mask                                                  (0x00000002)
#define PHY_BIST0_ST_bist_fail(data)                                                 (0x00000002&((data)<<1))
#define PHY_BIST0_ST_bist_fail_src(data)                                             ((0x00000002&(data))>>1)
#define PHY_BIST0_ST_get_bist_fail(data)                                             ((0x00000002&(data))>>1)
#define PHY_BIST0_ST_bist_done_shift                                                 (0)
#define PHY_BIST0_ST_bist_done_mask                                                  (0x00000001)
#define PHY_BIST0_ST_bist_done(data)                                                 (0x00000001&((data)<<0))
#define PHY_BIST0_ST_bist_done_src(data)                                             ((0x00000001&(data))>>0)
#define PHY_BIST0_ST_get_bist_done(data)                                             ((0x00000001&(data))>>0)


#define PHY_DRF0_ST                                                                  0x180081B8
#define PHY_DRF0_ST_reg_addr                                                         "0xB80081B8"
#define PHY_DRF0_ST_reg                                                              0xB80081B8
#define set_PHY_DRF0_ST_reg(data)   (*((volatile unsigned int*) PHY_DRF0_ST_reg)=data)
#define get_PHY_DRF0_ST_reg   (*((volatile unsigned int*) PHY_DRF0_ST_reg))
#define PHY_DRF0_ST_inst_adr                                                         "0x006E"
#define PHY_DRF0_ST_inst                                                             0x006E
#define PHY_DRF0_ST_drf_start_pause_shift                                            (16)
#define PHY_DRF0_ST_drf_start_pause_mask                                             (0x00010000)
#define PHY_DRF0_ST_drf_start_pause(data)                                            (0x00010000&((data)<<16))
#define PHY_DRF0_ST_drf_start_pause_src(data)                                        ((0x00010000&(data))>>16)
#define PHY_DRF0_ST_get_drf_start_pause(data)                                        ((0x00010000&(data))>>16)
#define PHY_DRF0_ST_drf_fail_shift                                                   (1)
#define PHY_DRF0_ST_drf_fail_mask                                                    (0x00000002)
#define PHY_DRF0_ST_drf_fail(data)                                                   (0x00000002&((data)<<1))
#define PHY_DRF0_ST_drf_fail_src(data)                                               ((0x00000002&(data))>>1)
#define PHY_DRF0_ST_get_drf_fail(data)                                               ((0x00000002&(data))>>1)
#define PHY_DRF0_ST_drf_done_shift                                                   (0)
#define PHY_DRF0_ST_drf_done_mask                                                    (0x00000001)
#define PHY_DRF0_ST_drf_done(data)                                                   (0x00000001&((data)<<0))
#define PHY_DRF0_ST_drf_done_src(data)                                               ((0x00000001&(data))>>0)
#define PHY_DRF0_ST_get_drf_done(data)                                               ((0x00000001&(data))>>0)


#define PHY_BIST1_ST                                                                 0x180081BC
#define PHY_BIST1_ST_reg_addr                                                        "0xB80081BC"
#define PHY_BIST1_ST_reg                                                             0xB80081BC
#define set_PHY_BIST1_ST_reg(data)   (*((volatile unsigned int*) PHY_BIST1_ST_reg)=data)
#define get_PHY_BIST1_ST_reg   (*((volatile unsigned int*) PHY_BIST1_ST_reg))
#define PHY_BIST1_ST_inst_adr                                                        "0x006F"
#define PHY_BIST1_ST_inst                                                            0x006F
#define PHY_BIST1_ST_mbist_st_shift                                                  (2)
#define PHY_BIST1_ST_mbist_st_mask                                                   (0x00000004)
#define PHY_BIST1_ST_mbist_st(data)                                                  (0x00000004&((data)<<2))
#define PHY_BIST1_ST_mbist_st_src(data)                                              ((0x00000004&(data))>>2)
#define PHY_BIST1_ST_get_mbist_st(data)                                              ((0x00000004&(data))>>2)
#define PHY_BIST1_ST_bist_fail_shift                                                 (1)
#define PHY_BIST1_ST_bist_fail_mask                                                  (0x00000002)
#define PHY_BIST1_ST_bist_fail(data)                                                 (0x00000002&((data)<<1))
#define PHY_BIST1_ST_bist_fail_src(data)                                             ((0x00000002&(data))>>1)
#define PHY_BIST1_ST_get_bist_fail(data)                                             ((0x00000002&(data))>>1)
#define PHY_BIST1_ST_bist_done_shift                                                 (0)
#define PHY_BIST1_ST_bist_done_mask                                                  (0x00000001)
#define PHY_BIST1_ST_bist_done(data)                                                 (0x00000001&((data)<<0))
#define PHY_BIST1_ST_bist_done_src(data)                                             ((0x00000001&(data))>>0)
#define PHY_BIST1_ST_get_bist_done(data)                                             ((0x00000001&(data))>>0)


#define PHY_DRF1_ST                                                                  0x180081C0
#define PHY_DRF1_ST_reg_addr                                                         "0xB80081C0"
#define PHY_DRF1_ST_reg                                                              0xB80081C0
#define set_PHY_DRF1_ST_reg(data)   (*((volatile unsigned int*) PHY_DRF1_ST_reg)=data)
#define get_PHY_DRF1_ST_reg   (*((volatile unsigned int*) PHY_DRF1_ST_reg))
#define PHY_DRF1_ST_inst_adr                                                         "0x0070"
#define PHY_DRF1_ST_inst                                                             0x0070
#define PHY_DRF1_ST_drf_start_pause_shift                                            (16)
#define PHY_DRF1_ST_drf_start_pause_mask                                             (0x00010000)
#define PHY_DRF1_ST_drf_start_pause(data)                                            (0x00010000&((data)<<16))
#define PHY_DRF1_ST_drf_start_pause_src(data)                                        ((0x00010000&(data))>>16)
#define PHY_DRF1_ST_get_drf_start_pause(data)                                        ((0x00010000&(data))>>16)
#define PHY_DRF1_ST_drf_fail_shift                                                   (1)
#define PHY_DRF1_ST_drf_fail_mask                                                    (0x00000002)
#define PHY_DRF1_ST_drf_fail(data)                                                   (0x00000002&((data)<<1))
#define PHY_DRF1_ST_drf_fail_src(data)                                               ((0x00000002&(data))>>1)
#define PHY_DRF1_ST_get_drf_fail(data)                                               ((0x00000002&(data))>>1)
#define PHY_DRF1_ST_drf_done_shift                                                   (0)
#define PHY_DRF1_ST_drf_done_mask                                                    (0x00000001)
#define PHY_DRF1_ST_drf_done(data)                                                   (0x00000001&((data)<<0))
#define PHY_DRF1_ST_drf_done_src(data)                                               ((0x00000001&(data))>>0)
#define PHY_DRF1_ST_get_drf_done(data)                                               ((0x00000001&(data))>>0)


#define BIST_RM                                                                      0x180081D0
#define BIST_RM_reg_addr                                                             "0xB80081D0"
#define BIST_RM_reg                                                                  0xB80081D0
#define set_BIST_RM_reg(data)   (*((volatile unsigned int*) BIST_RM_reg)=data)
#define get_BIST_RM_reg   (*((volatile unsigned int*) BIST_RM_reg))
#define BIST_RM_inst_adr                                                             "0x0074"
#define BIST_RM_inst                                                                 0x0074
#define BIST_RM_bist_en_0_shift                                                      (31)
#define BIST_RM_bist_en_0_mask                                                       (0x80000000)
#define BIST_RM_bist_en_0(data)                                                      (0x80000000&((data)<<31))
#define BIST_RM_bist_en_0_src(data)                                                  ((0x80000000&(data))>>31)
#define BIST_RM_get_bist_en_0(data)                                                  ((0x80000000&(data))>>31)
#define BIST_RM_drf_bist_en_0_shift                                                  (30)
#define BIST_RM_drf_bist_en_0_mask                                                   (0x40000000)
#define BIST_RM_drf_bist_en_0(data)                                                  (0x40000000&((data)<<30))
#define BIST_RM_drf_bist_en_0_src(data)                                              ((0x40000000&(data))>>30)
#define BIST_RM_get_drf_bist_en_0(data)                                              ((0x40000000&(data))>>30)
#define BIST_RM_drf_test_resume_0_shift                                              (29)
#define BIST_RM_drf_test_resume_0_mask                                               (0x20000000)
#define BIST_RM_drf_test_resume_0(data)                                              (0x20000000&((data)<<29))
#define BIST_RM_drf_test_resume_0_src(data)                                          ((0x20000000&(data))>>29)
#define BIST_RM_get_drf_test_resume_0(data)                                          ((0x20000000&(data))>>29)
#define BIST_RM_bist_en_1_shift                                                      (28)
#define BIST_RM_bist_en_1_mask                                                       (0x10000000)
#define BIST_RM_bist_en_1(data)                                                      (0x10000000&((data)<<28))
#define BIST_RM_bist_en_1_src(data)                                                  ((0x10000000&(data))>>28)
#define BIST_RM_get_bist_en_1(data)                                                  ((0x10000000&(data))>>28)
#define BIST_RM_drf_bist_en_1_shift                                                  (27)
#define BIST_RM_drf_bist_en_1_mask                                                   (0x08000000)
#define BIST_RM_drf_bist_en_1(data)                                                  (0x08000000&((data)<<27))
#define BIST_RM_drf_bist_en_1_src(data)                                              ((0x08000000&(data))>>27)
#define BIST_RM_get_drf_bist_en_1(data)                                              ((0x08000000&(data))>>27)
#define BIST_RM_drf_test_resume_1_shift                                              (26)
#define BIST_RM_drf_test_resume_1_mask                                               (0x04000000)
#define BIST_RM_drf_test_resume_1(data)                                              (0x04000000&((data)<<26))
#define BIST_RM_drf_test_resume_1_src(data)                                          ((0x04000000&(data))>>26)
#define BIST_RM_get_drf_test_resume_1(data)                                          ((0x04000000&(data))>>26)
#define BIST_RM_DVSE_A_shift                                                         (20)
#define BIST_RM_DVSE_A_mask                                                          (0x00100000)
#define BIST_RM_DVSE_A(data)                                                         (0x00100000&((data)<<20))
#define BIST_RM_DVSE_A_src(data)                                                     ((0x00100000&(data))>>20)
#define BIST_RM_get_DVSE_A(data)                                                     ((0x00100000&(data))>>20)
#define BIST_RM_DVS_A_3_shift                                                        (19)
#define BIST_RM_DVS_A_3_mask                                                         (0x00080000)
#define BIST_RM_DVS_A_3(data)                                                        (0x00080000&((data)<<19))
#define BIST_RM_DVS_A_3_src(data)                                                    ((0x00080000&(data))>>19)
#define BIST_RM_get_DVS_A_3(data)                                                    ((0x00080000&(data))>>19)
#define BIST_RM_DVS_A_2_shift                                                        (18)
#define BIST_RM_DVS_A_2_mask                                                         (0x00040000)
#define BIST_RM_DVS_A_2(data)                                                        (0x00040000&((data)<<18))
#define BIST_RM_DVS_A_2_src(data)                                                    ((0x00040000&(data))>>18)
#define BIST_RM_get_DVS_A_2(data)                                                    ((0x00040000&(data))>>18)
#define BIST_RM_DVS_A_1_shift                                                        (17)
#define BIST_RM_DVS_A_1_mask                                                         (0x00020000)
#define BIST_RM_DVS_A_1(data)                                                        (0x00020000&((data)<<17))
#define BIST_RM_DVS_A_1_src(data)                                                    ((0x00020000&(data))>>17)
#define BIST_RM_get_DVS_A_1(data)                                                    ((0x00020000&(data))>>17)
#define BIST_RM_DVS_A_0_shift                                                        (16)
#define BIST_RM_DVS_A_0_mask                                                         (0x00010000)
#define BIST_RM_DVS_A_0(data)                                                        (0x00010000&((data)<<16))
#define BIST_RM_DVS_A_0_src(data)                                                    ((0x00010000&(data))>>16)
#define BIST_RM_get_DVS_A_0(data)                                                    ((0x00010000&(data))>>16)
#define BIST_RM_DVSE_shift                                                           (4)
#define BIST_RM_DVSE_mask                                                            (0x00000010)
#define BIST_RM_DVSE(data)                                                           (0x00000010&((data)<<4))
#define BIST_RM_DVSE_src(data)                                                       ((0x00000010&(data))>>4)
#define BIST_RM_get_DVSE(data)                                                       ((0x00000010&(data))>>4)
#define BIST_RM_DVS_3_shift                                                          (3)
#define BIST_RM_DVS_3_mask                                                           (0x00000008)
#define BIST_RM_DVS_3(data)                                                          (0x00000008&((data)<<3))
#define BIST_RM_DVS_3_src(data)                                                      ((0x00000008&(data))>>3)
#define BIST_RM_get_DVS_3(data)                                                      ((0x00000008&(data))>>3)
#define BIST_RM_DVS_2_shift                                                          (2)
#define BIST_RM_DVS_2_mask                                                           (0x00000004)
#define BIST_RM_DVS_2(data)                                                          (0x00000004&((data)<<2))
#define BIST_RM_DVS_2_src(data)                                                      ((0x00000004&(data))>>2)
#define BIST_RM_get_DVS_2(data)                                                      ((0x00000004&(data))>>2)
#define BIST_RM_DVS_1_shift                                                          (1)
#define BIST_RM_DVS_1_mask                                                           (0x00000002)
#define BIST_RM_DVS_1(data)                                                          (0x00000002&((data)<<1))
#define BIST_RM_DVS_1_src(data)                                                      ((0x00000002&(data))>>1)
#define BIST_RM_get_DVS_1(data)                                                      ((0x00000002&(data))>>1)
#define BIST_RM_DVS_0_shift                                                          (0)
#define BIST_RM_DVS_0_mask                                                           (0x00000001)
#define BIST_RM_DVS_0(data)                                                          (0x00000001&((data)<<0))
#define BIST_RM_DVS_0_src(data)                                                      ((0x00000001&(data))>>0)
#define BIST_RM_get_DVS_0(data)                                                      ((0x00000001&(data))>>0)


#define BIST0_ST                                                                     0x180081D4
#define BIST0_ST_reg_addr                                                            "0xB80081D4"
#define BIST0_ST_reg                                                                 0xB80081D4
#define set_BIST0_ST_reg(data)   (*((volatile unsigned int*) BIST0_ST_reg)=data)
#define get_BIST0_ST_reg   (*((volatile unsigned int*) BIST0_ST_reg))
#define BIST0_ST_inst_adr                                                            "0x0075"
#define BIST0_ST_inst                                                                0x0075
#define BIST0_ST_mbist_st_shift                                                      (3)
#define BIST0_ST_mbist_st_mask                                                       (0x00000008)
#define BIST0_ST_mbist_st(data)                                                      (0x00000008&((data)<<3))
#define BIST0_ST_mbist_st_src(data)                                                  ((0x00000008&(data))>>3)
#define BIST0_ST_get_mbist_st(data)                                                  ((0x00000008&(data))>>3)
#define BIST0_ST_bist_fail1_shift                                                    (2)
#define BIST0_ST_bist_fail1_mask                                                     (0x00000004)
#define BIST0_ST_bist_fail1(data)                                                    (0x00000004&((data)<<2))
#define BIST0_ST_bist_fail1_src(data)                                                ((0x00000004&(data))>>2)
#define BIST0_ST_get_bist_fail1(data)                                                ((0x00000004&(data))>>2)
#define BIST0_ST_bist_fail0_shift                                                    (1)
#define BIST0_ST_bist_fail0_mask                                                     (0x00000002)
#define BIST0_ST_bist_fail0(data)                                                    (0x00000002&((data)<<1))
#define BIST0_ST_bist_fail0_src(data)                                                ((0x00000002&(data))>>1)
#define BIST0_ST_get_bist_fail0(data)                                                ((0x00000002&(data))>>1)
#define BIST0_ST_bist_done_shift                                                     (0)
#define BIST0_ST_bist_done_mask                                                      (0x00000001)
#define BIST0_ST_bist_done(data)                                                     (0x00000001&((data)<<0))
#define BIST0_ST_bist_done_src(data)                                                 ((0x00000001&(data))>>0)
#define BIST0_ST_get_bist_done(data)                                                 ((0x00000001&(data))>>0)


#define DRF0_ST                                                                      0x180081D8
#define DRF0_ST_reg_addr                                                             "0xB80081D8"
#define DRF0_ST_reg                                                                  0xB80081D8
#define set_DRF0_ST_reg(data)   (*((volatile unsigned int*) DRF0_ST_reg)=data)
#define get_DRF0_ST_reg   (*((volatile unsigned int*) DRF0_ST_reg))
#define DRF0_ST_inst_adr                                                             "0x0076"
#define DRF0_ST_inst                                                                 0x0076
#define DRF0_ST_drf_start_pause_shift                                                (16)
#define DRF0_ST_drf_start_pause_mask                                                 (0x00010000)
#define DRF0_ST_drf_start_pause(data)                                                (0x00010000&((data)<<16))
#define DRF0_ST_drf_start_pause_src(data)                                            ((0x00010000&(data))>>16)
#define DRF0_ST_get_drf_start_pause(data)                                            ((0x00010000&(data))>>16)
#define DRF0_ST_drf_fail1_shift                                                      (2)
#define DRF0_ST_drf_fail1_mask                                                       (0x00000004)
#define DRF0_ST_drf_fail1(data)                                                      (0x00000004&((data)<<2))
#define DRF0_ST_drf_fail1_src(data)                                                  ((0x00000004&(data))>>2)
#define DRF0_ST_get_drf_fail1(data)                                                  ((0x00000004&(data))>>2)
#define DRF0_ST_drf_fail0_shift                                                      (1)
#define DRF0_ST_drf_fail0_mask                                                       (0x00000002)
#define DRF0_ST_drf_fail0(data)                                                      (0x00000002&((data)<<1))
#define DRF0_ST_drf_fail0_src(data)                                                  ((0x00000002&(data))>>1)
#define DRF0_ST_get_drf_fail0(data)                                                  ((0x00000002&(data))>>1)
#define DRF0_ST_drf_done_shift                                                       (0)
#define DRF0_ST_drf_done_mask                                                        (0x00000001)
#define DRF0_ST_drf_done(data)                                                       (0x00000001&((data)<<0))
#define DRF0_ST_drf_done_src(data)                                                   ((0x00000001&(data))>>0)
#define DRF0_ST_get_drf_done(data)                                                   ((0x00000001&(data))>>0)


#define BIST1_ST                                                                     0x180081DC
#define BIST1_ST_reg_addr                                                            "0xB80081DC"
#define BIST1_ST_reg                                                                 0xB80081DC
#define set_BIST1_ST_reg(data)   (*((volatile unsigned int*) BIST1_ST_reg)=data)
#define get_BIST1_ST_reg   (*((volatile unsigned int*) BIST1_ST_reg))
#define BIST1_ST_inst_adr                                                            "0x0077"
#define BIST1_ST_inst                                                                0x0077
#define BIST1_ST_mbist_st_shift                                                      (2)
#define BIST1_ST_mbist_st_mask                                                       (0x00000004)
#define BIST1_ST_mbist_st(data)                                                      (0x00000004&((data)<<2))
#define BIST1_ST_mbist_st_src(data)                                                  ((0x00000004&(data))>>2)
#define BIST1_ST_get_mbist_st(data)                                                  ((0x00000004&(data))>>2)
#define BIST1_ST_bist_fail0_shift                                                    (1)
#define BIST1_ST_bist_fail0_mask                                                     (0x00000002)
#define BIST1_ST_bist_fail0(data)                                                    (0x00000002&((data)<<1))
#define BIST1_ST_bist_fail0_src(data)                                                ((0x00000002&(data))>>1)
#define BIST1_ST_get_bist_fail0(data)                                                ((0x00000002&(data))>>1)
#define BIST1_ST_bist_done_shift                                                     (0)
#define BIST1_ST_bist_done_mask                                                      (0x00000001)
#define BIST1_ST_bist_done(data)                                                     (0x00000001&((data)<<0))
#define BIST1_ST_bist_done_src(data)                                                 ((0x00000001&(data))>>0)
#define BIST1_ST_get_bist_done(data)                                                 ((0x00000001&(data))>>0)


#define DRF1_ST                                                                      0x180081E0
#define DRF1_ST_reg_addr                                                             "0xB80081E0"
#define DRF1_ST_reg                                                                  0xB80081E0
#define set_DRF1_ST_reg(data)   (*((volatile unsigned int*) DRF1_ST_reg)=data)
#define get_DRF1_ST_reg   (*((volatile unsigned int*) DRF1_ST_reg))
#define DRF1_ST_inst_adr                                                             "0x0078"
#define DRF1_ST_inst                                                                 0x0078
#define DRF1_ST_drf_start_pause_shift                                                (16)
#define DRF1_ST_drf_start_pause_mask                                                 (0x00010000)
#define DRF1_ST_drf_start_pause(data)                                                (0x00010000&((data)<<16))
#define DRF1_ST_drf_start_pause_src(data)                                            ((0x00010000&(data))>>16)
#define DRF1_ST_get_drf_start_pause(data)                                            ((0x00010000&(data))>>16)
#define DRF1_ST_drf_fail0_shift                                                      (1)
#define DRF1_ST_drf_fail0_mask                                                       (0x00000002)
#define DRF1_ST_drf_fail0(data)                                                      (0x00000002&((data)<<1))
#define DRF1_ST_drf_fail0_src(data)                                                  ((0x00000002&(data))>>1)
#define DRF1_ST_get_drf_fail0(data)                                                  ((0x00000002&(data))>>1)
#define DRF1_ST_drf_done_shift                                                       (0)
#define DRF1_ST_drf_done_mask                                                        (0x00000001)
#define DRF1_ST_drf_done(data)                                                       (0x00000001&((data)<<0))
#define DRF1_ST_drf_done_src(data)                                                   ((0x00000001&(data))>>0)
#define DRF1_ST_get_drf_done(data)                                                   ((0x00000001&(data))>>0)


#define DUMMY_REG0                                                                   0x180081F0
#define DUMMY_REG0_reg_addr                                                          "0xB80081F0"
#define DUMMY_REG0_reg                                                               0xB80081F0
#define set_DUMMY_REG0_reg(data)   (*((volatile unsigned int*) DUMMY_REG0_reg)=data)
#define get_DUMMY_REG0_reg   (*((volatile unsigned int*) DUMMY_REG0_reg))
#define DUMMY_REG0_inst_adr                                                          "0x007C"
#define DUMMY_REG0_inst                                                              0x007C
#define DUMMY_REG0_dummy_reg0_shift                                                  (0)
#define DUMMY_REG0_dummy_reg0_mask                                                   (0xFFFFFFFF)
#define DUMMY_REG0_dummy_reg0(data)                                                  (0xFFFFFFFF&((data)<<0))
#define DUMMY_REG0_dummy_reg0_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define DUMMY_REG0_get_dummy_reg0(data)                                              ((0xFFFFFFFF&(data))>>0)


#define DUMMY_REG1                                                                   0x180081F4
#define DUMMY_REG1_reg_addr                                                          "0xB80081F4"
#define DUMMY_REG1_reg                                                               0xB80081F4
#define set_DUMMY_REG1_reg(data)   (*((volatile unsigned int*) DUMMY_REG1_reg)=data)
#define get_DUMMY_REG1_reg   (*((volatile unsigned int*) DUMMY_REG1_reg))
#define DUMMY_REG1_inst_adr                                                          "0x007D"
#define DUMMY_REG1_inst                                                              0x007D
#define DUMMY_REG1_dummy_reg1_shift                                                  (0)
#define DUMMY_REG1_dummy_reg1_mask                                                   (0xFFFFFFFF)
#define DUMMY_REG1_dummy_reg1(data)                                                  (0xFFFFFFFF&((data)<<0))
#define DUMMY_REG1_dummy_reg1_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define DUMMY_REG1_get_dummy_reg1(data)                                              ((0xFFFFFFFF&(data))>>0)


#define DUMMY_REG2                                                                   0x180081F8
#define DUMMY_REG2_reg_addr                                                          "0xB80081F8"
#define DUMMY_REG2_reg                                                               0xB80081F8
#define set_DUMMY_REG2_reg(data)   (*((volatile unsigned int*) DUMMY_REG2_reg)=data)
#define get_DUMMY_REG2_reg   (*((volatile unsigned int*) DUMMY_REG2_reg))
#define DUMMY_REG2_inst_adr                                                          "0x007E"
#define DUMMY_REG2_inst                                                              0x007E
#define DUMMY_REG2_dummy_reg2_shift                                                  (0)
#define DUMMY_REG2_dummy_reg2_mask                                                   (0xFFFFFFFF)
#define DUMMY_REG2_dummy_reg2(data)                                                  (0xFFFFFFFF&((data)<<0))
#define DUMMY_REG2_dummy_reg2_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define DUMMY_REG2_get_dummy_reg2(data)                                              ((0xFFFFFFFF&(data))>>0)


#define DUMMY_REG3                                                                   0x180081FC
#define DUMMY_REG3_reg_addr                                                          "0xB80081FC"
#define DUMMY_REG3_reg                                                               0xB80081FC
#define set_DUMMY_REG3_reg(data)   (*((volatile unsigned int*) DUMMY_REG3_reg)=data)
#define get_DUMMY_REG3_reg   (*((volatile unsigned int*) DUMMY_REG3_reg))
#define DUMMY_REG3_inst_adr                                                          "0x007F"
#define DUMMY_REG3_inst                                                              0x007F
#define DUMMY_REG3_dummy_reg3_shift                                                  (0)
#define DUMMY_REG3_dummy_reg3_mask                                                   (0xFFFFFFFF)
#define DUMMY_REG3_dummy_reg3(data)                                                  (0xFFFFFFFF&((data)<<0))
#define DUMMY_REG3_dummy_reg3_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define DUMMY_REG3_get_dummy_reg3(data)                                              ((0xFFFFFFFF&(data))>>0)


#define DC_MT_SADDR_0                                                                0x18008200
#define DC_MT_SADDR_1                                                                0x18008204
#define DC_MT_SADDR_2                                                                0x18008208
#define DC_MT_SADDR_3                                                                0x1800820C
#define DC_MT_SADDR_4                                                                0x18008210
#define DC_MT_SADDR_5                                                                0x18008214
#define DC_MT_SADDR_6                                                                0x18008218
#define DC_MT_SADDR_7                                                                0x1800821C
#define DC_MT_SADDR_0_reg_addr                                                       "0xB8008200"
#define DC_MT_SADDR_1_reg_addr                                                       "0xB8008204"
#define DC_MT_SADDR_2_reg_addr                                                       "0xB8008208"
#define DC_MT_SADDR_3_reg_addr                                                       "0xB800820C"
#define DC_MT_SADDR_4_reg_addr                                                       "0xB8008210"
#define DC_MT_SADDR_5_reg_addr                                                       "0xB8008214"
#define DC_MT_SADDR_6_reg_addr                                                       "0xB8008218"
#define DC_MT_SADDR_7_reg_addr                                                       "0xB800821C"
#define DC_MT_SADDR_0_reg                                                            0xB8008200
#define DC_MT_SADDR_1_reg                                                            0xB8008204
#define DC_MT_SADDR_2_reg                                                            0xB8008208
#define DC_MT_SADDR_3_reg                                                            0xB800820C
#define DC_MT_SADDR_4_reg                                                            0xB8008210
#define DC_MT_SADDR_5_reg                                                            0xB8008214
#define DC_MT_SADDR_6_reg                                                            0xB8008218
#define DC_MT_SADDR_7_reg                                                            0xB800821C
#define set_DC_MT_SADDR_0_reg(data)   (*((volatile unsigned int*) DC_MT_SADDR_0_reg)=data)
#define set_DC_MT_SADDR_1_reg(data)   (*((volatile unsigned int*) DC_MT_SADDR_1_reg)=data)
#define set_DC_MT_SADDR_2_reg(data)   (*((volatile unsigned int*) DC_MT_SADDR_2_reg)=data)
#define set_DC_MT_SADDR_3_reg(data)   (*((volatile unsigned int*) DC_MT_SADDR_3_reg)=data)
#define set_DC_MT_SADDR_4_reg(data)   (*((volatile unsigned int*) DC_MT_SADDR_4_reg)=data)
#define set_DC_MT_SADDR_5_reg(data)   (*((volatile unsigned int*) DC_MT_SADDR_5_reg)=data)
#define set_DC_MT_SADDR_6_reg(data)   (*((volatile unsigned int*) DC_MT_SADDR_6_reg)=data)
#define set_DC_MT_SADDR_7_reg(data)   (*((volatile unsigned int*) DC_MT_SADDR_7_reg)=data)
#define get_DC_MT_SADDR_0_reg   (*((volatile unsigned int*) DC_MT_SADDR_0_reg))
#define get_DC_MT_SADDR_1_reg   (*((volatile unsigned int*) DC_MT_SADDR_1_reg))
#define get_DC_MT_SADDR_2_reg   (*((volatile unsigned int*) DC_MT_SADDR_2_reg))
#define get_DC_MT_SADDR_3_reg   (*((volatile unsigned int*) DC_MT_SADDR_3_reg))
#define get_DC_MT_SADDR_4_reg   (*((volatile unsigned int*) DC_MT_SADDR_4_reg))
#define get_DC_MT_SADDR_5_reg   (*((volatile unsigned int*) DC_MT_SADDR_5_reg))
#define get_DC_MT_SADDR_6_reg   (*((volatile unsigned int*) DC_MT_SADDR_6_reg))
#define get_DC_MT_SADDR_7_reg   (*((volatile unsigned int*) DC_MT_SADDR_7_reg))
#define DC_MT_SADDR_0_inst_adr                                                       "0x0080"
#define DC_MT_SADDR_1_inst_adr                                                       "0x0081"
#define DC_MT_SADDR_2_inst_adr                                                       "0x0082"
#define DC_MT_SADDR_3_inst_adr                                                       "0x0083"
#define DC_MT_SADDR_4_inst_adr                                                       "0x0084"
#define DC_MT_SADDR_5_inst_adr                                                       "0x0085"
#define DC_MT_SADDR_6_inst_adr                                                       "0x0086"
#define DC_MT_SADDR_7_inst_adr                                                       "0x0087"
#define DC_MT_SADDR_0_inst                                                           0x0080
#define DC_MT_SADDR_1_inst                                                           0x0081
#define DC_MT_SADDR_2_inst                                                           0x0082
#define DC_MT_SADDR_3_inst                                                           0x0083
#define DC_MT_SADDR_4_inst                                                           0x0084
#define DC_MT_SADDR_5_inst                                                           0x0085
#define DC_MT_SADDR_6_inst                                                           0x0086
#define DC_MT_SADDR_7_inst                                                           0x0087
#define DC_MT_SADDR_mem_type_shift                                                   (30)
#define DC_MT_SADDR_mem_type_mask                                                    (0xC0000000)
#define DC_MT_SADDR_mem_type(data)                                                   (0xC0000000&((data)<<30))
#define DC_MT_SADDR_mem_type_src(data)                                               ((0xC0000000&(data))>>30)
#define DC_MT_SADDR_get_mem_type(data)                                               ((0xC0000000&(data))>>30)
#define DC_MT_SADDR_saddr_shift                                                      (4)
#define DC_MT_SADDR_saddr_mask                                                       (0x3FFFFFF0)
#define DC_MT_SADDR_saddr(data)                                                      (0x3FFFFFF0&((data)<<4))
#define DC_MT_SADDR_saddr_src(data)                                                  ((0x3FFFFFF0&(data))>>4)
#define DC_MT_SADDR_get_saddr(data)                                                  ((0x3FFFFFF0&(data))>>4)


#define DC_MT_EADDR_0                                                                0x18008220
#define DC_MT_EADDR_1                                                                0x18008224
#define DC_MT_EADDR_2                                                                0x18008228
#define DC_MT_EADDR_3                                                                0x1800822C
#define DC_MT_EADDR_4                                                                0x18008230
#define DC_MT_EADDR_5                                                                0x18008234
#define DC_MT_EADDR_6                                                                0x18008238
#define DC_MT_EADDR_7                                                                0x1800823C
#define DC_MT_EADDR_0_reg_addr                                                       "0xB8008220"
#define DC_MT_EADDR_1_reg_addr                                                       "0xB8008224"
#define DC_MT_EADDR_2_reg_addr                                                       "0xB8008228"
#define DC_MT_EADDR_3_reg_addr                                                       "0xB800822C"
#define DC_MT_EADDR_4_reg_addr                                                       "0xB8008230"
#define DC_MT_EADDR_5_reg_addr                                                       "0xB8008234"
#define DC_MT_EADDR_6_reg_addr                                                       "0xB8008238"
#define DC_MT_EADDR_7_reg_addr                                                       "0xB800823C"
#define DC_MT_EADDR_0_reg                                                            0xB8008220
#define DC_MT_EADDR_1_reg                                                            0xB8008224
#define DC_MT_EADDR_2_reg                                                            0xB8008228
#define DC_MT_EADDR_3_reg                                                            0xB800822C
#define DC_MT_EADDR_4_reg                                                            0xB8008230
#define DC_MT_EADDR_5_reg                                                            0xB8008234
#define DC_MT_EADDR_6_reg                                                            0xB8008238
#define DC_MT_EADDR_7_reg                                                            0xB800823C
#define set_DC_MT_EADDR_0_reg(data)   (*((volatile unsigned int*) DC_MT_EADDR_0_reg)=data)
#define set_DC_MT_EADDR_1_reg(data)   (*((volatile unsigned int*) DC_MT_EADDR_1_reg)=data)
#define set_DC_MT_EADDR_2_reg(data)   (*((volatile unsigned int*) DC_MT_EADDR_2_reg)=data)
#define set_DC_MT_EADDR_3_reg(data)   (*((volatile unsigned int*) DC_MT_EADDR_3_reg)=data)
#define set_DC_MT_EADDR_4_reg(data)   (*((volatile unsigned int*) DC_MT_EADDR_4_reg)=data)
#define set_DC_MT_EADDR_5_reg(data)   (*((volatile unsigned int*) DC_MT_EADDR_5_reg)=data)
#define set_DC_MT_EADDR_6_reg(data)   (*((volatile unsigned int*) DC_MT_EADDR_6_reg)=data)
#define set_DC_MT_EADDR_7_reg(data)   (*((volatile unsigned int*) DC_MT_EADDR_7_reg)=data)
#define get_DC_MT_EADDR_0_reg   (*((volatile unsigned int*) DC_MT_EADDR_0_reg))
#define get_DC_MT_EADDR_1_reg   (*((volatile unsigned int*) DC_MT_EADDR_1_reg))
#define get_DC_MT_EADDR_2_reg   (*((volatile unsigned int*) DC_MT_EADDR_2_reg))
#define get_DC_MT_EADDR_3_reg   (*((volatile unsigned int*) DC_MT_EADDR_3_reg))
#define get_DC_MT_EADDR_4_reg   (*((volatile unsigned int*) DC_MT_EADDR_4_reg))
#define get_DC_MT_EADDR_5_reg   (*((volatile unsigned int*) DC_MT_EADDR_5_reg))
#define get_DC_MT_EADDR_6_reg   (*((volatile unsigned int*) DC_MT_EADDR_6_reg))
#define get_DC_MT_EADDR_7_reg   (*((volatile unsigned int*) DC_MT_EADDR_7_reg))
#define DC_MT_EADDR_0_inst_adr                                                       "0x0088"
#define DC_MT_EADDR_1_inst_adr                                                       "0x0089"
#define DC_MT_EADDR_2_inst_adr                                                       "0x008A"
#define DC_MT_EADDR_3_inst_adr                                                       "0x008B"
#define DC_MT_EADDR_4_inst_adr                                                       "0x008C"
#define DC_MT_EADDR_5_inst_adr                                                       "0x008D"
#define DC_MT_EADDR_6_inst_adr                                                       "0x008E"
#define DC_MT_EADDR_7_inst_adr                                                       "0x008F"
#define DC_MT_EADDR_0_inst                                                           0x0088
#define DC_MT_EADDR_1_inst                                                           0x0089
#define DC_MT_EADDR_2_inst                                                           0x008A
#define DC_MT_EADDR_3_inst                                                           0x008B
#define DC_MT_EADDR_4_inst                                                           0x008C
#define DC_MT_EADDR_5_inst                                                           0x008D
#define DC_MT_EADDR_6_inst                                                           0x008E
#define DC_MT_EADDR_7_inst                                                           0x008F
#define DC_MT_EADDR_eaddr_shift                                                      (5)
#define DC_MT_EADDR_eaddr_mask                                                       (0x7FFFFFE0)
#define DC_MT_EADDR_eaddr(data)                                                      (0x7FFFFFE0&((data)<<5))
#define DC_MT_EADDR_eaddr_src(data)                                                  ((0x7FFFFFE0&(data))>>5)
#define DC_MT_EADDR_get_eaddr(data)                                                  ((0x7FFFFFE0&(data))>>5)


#define DC_MT_MODE_0                                                                 0x18008240
#define DC_MT_MODE_1                                                                 0x18008244
#define DC_MT_MODE_2                                                                 0x18008248
#define DC_MT_MODE_3                                                                 0x1800824C
#define DC_MT_MODE_4                                                                 0x18008250
#define DC_MT_MODE_5                                                                 0x18008254
#define DC_MT_MODE_6                                                                 0x18008258
#define DC_MT_MODE_7                                                                 0x1800825C
#define DC_MT_MODE_0_reg_addr                                                        "0xB8008240"
#define DC_MT_MODE_1_reg_addr                                                        "0xB8008244"
#define DC_MT_MODE_2_reg_addr                                                        "0xB8008248"
#define DC_MT_MODE_3_reg_addr                                                        "0xB800824C"
#define DC_MT_MODE_4_reg_addr                                                        "0xB8008250"
#define DC_MT_MODE_5_reg_addr                                                        "0xB8008254"
#define DC_MT_MODE_6_reg_addr                                                        "0xB8008258"
#define DC_MT_MODE_7_reg_addr                                                        "0xB800825C"
#define DC_MT_MODE_0_reg                                                             0xB8008240
#define DC_MT_MODE_1_reg                                                             0xB8008244
#define DC_MT_MODE_2_reg                                                             0xB8008248
#define DC_MT_MODE_3_reg                                                             0xB800824C
#define DC_MT_MODE_4_reg                                                             0xB8008250
#define DC_MT_MODE_5_reg                                                             0xB8008254
#define DC_MT_MODE_6_reg                                                             0xB8008258
#define DC_MT_MODE_7_reg                                                             0xB800825C
#define set_DC_MT_MODE_0_reg(data)   (*((volatile unsigned int*) DC_MT_MODE_0_reg)=data)
#define set_DC_MT_MODE_1_reg(data)   (*((volatile unsigned int*) DC_MT_MODE_1_reg)=data)
#define set_DC_MT_MODE_2_reg(data)   (*((volatile unsigned int*) DC_MT_MODE_2_reg)=data)
#define set_DC_MT_MODE_3_reg(data)   (*((volatile unsigned int*) DC_MT_MODE_3_reg)=data)
#define set_DC_MT_MODE_4_reg(data)   (*((volatile unsigned int*) DC_MT_MODE_4_reg)=data)
#define set_DC_MT_MODE_5_reg(data)   (*((volatile unsigned int*) DC_MT_MODE_5_reg)=data)
#define set_DC_MT_MODE_6_reg(data)   (*((volatile unsigned int*) DC_MT_MODE_6_reg)=data)
#define set_DC_MT_MODE_7_reg(data)   (*((volatile unsigned int*) DC_MT_MODE_7_reg)=data)
#define get_DC_MT_MODE_0_reg   (*((volatile unsigned int*) DC_MT_MODE_0_reg))
#define get_DC_MT_MODE_1_reg   (*((volatile unsigned int*) DC_MT_MODE_1_reg))
#define get_DC_MT_MODE_2_reg   (*((volatile unsigned int*) DC_MT_MODE_2_reg))
#define get_DC_MT_MODE_3_reg   (*((volatile unsigned int*) DC_MT_MODE_3_reg))
#define get_DC_MT_MODE_4_reg   (*((volatile unsigned int*) DC_MT_MODE_4_reg))
#define get_DC_MT_MODE_5_reg   (*((volatile unsigned int*) DC_MT_MODE_5_reg))
#define get_DC_MT_MODE_6_reg   (*((volatile unsigned int*) DC_MT_MODE_6_reg))
#define get_DC_MT_MODE_7_reg   (*((volatile unsigned int*) DC_MT_MODE_7_reg))
#define DC_MT_MODE_0_inst_adr                                                        "0x0090"
#define DC_MT_MODE_1_inst_adr                                                        "0x0091"
#define DC_MT_MODE_2_inst_adr                                                        "0x0092"
#define DC_MT_MODE_3_inst_adr                                                        "0x0093"
#define DC_MT_MODE_4_inst_adr                                                        "0x0094"
#define DC_MT_MODE_5_inst_adr                                                        "0x0095"
#define DC_MT_MODE_6_inst_adr                                                        "0x0096"
#define DC_MT_MODE_7_inst_adr                                                        "0x0097"
#define DC_MT_MODE_0_inst                                                            0x0090
#define DC_MT_MODE_1_inst                                                            0x0091
#define DC_MT_MODE_2_inst                                                            0x0092
#define DC_MT_MODE_3_inst                                                            0x0093
#define DC_MT_MODE_4_inst                                                            0x0094
#define DC_MT_MODE_5_inst                                                            0x0095
#define DC_MT_MODE_6_inst                                                            0x0096
#define DC_MT_MODE_7_inst                                                            0x0097
#define DC_MT_MODE_write_enable0_shift                                               (23)
#define DC_MT_MODE_write_enable0_mask                                                (0x00800000)
#define DC_MT_MODE_write_enable0(data)                                               (0x00800000&((data)<<23))
#define DC_MT_MODE_write_enable0_src(data)                                           ((0x00800000&(data))>>23)
#define DC_MT_MODE_get_write_enable0(data)                                           ((0x00800000&(data))>>23)
#define DC_MT_MODE_access_type_0_shift                                               (21)
#define DC_MT_MODE_access_type_0_mask                                                (0x00600000)
#define DC_MT_MODE_access_type_0(data)                                               (0x00600000&((data)<<21))
#define DC_MT_MODE_access_type_0_src(data)                                           ((0x00600000&(data))>>21)
#define DC_MT_MODE_get_access_type_0(data)                                           ((0x00600000&(data))>>21)
#define DC_MT_MODE_access_type_1_shift                                               (19)
#define DC_MT_MODE_access_type_1_mask                                                (0x00180000)
#define DC_MT_MODE_access_type_1(data)                                               (0x00180000&((data)<<19))
#define DC_MT_MODE_access_type_1_src(data)                                           ((0x00180000&(data))>>19)
#define DC_MT_MODE_get_access_type_1(data)                                           ((0x00180000&(data))>>19)
#define DC_MT_MODE_access_type_2_shift                                               (17)
#define DC_MT_MODE_access_type_2_mask                                                (0x00060000)
#define DC_MT_MODE_access_type_2(data)                                               (0x00060000&((data)<<17))
#define DC_MT_MODE_access_type_2_src(data)                                           ((0x00060000&(data))>>17)
#define DC_MT_MODE_get_access_type_2(data)                                           ((0x00060000&(data))>>17)
#define DC_MT_MODE_access_type_3_shift                                               (15)
#define DC_MT_MODE_access_type_3_mask                                                (0x00018000)
#define DC_MT_MODE_access_type_3(data)                                               (0x00018000&((data)<<15))
#define DC_MT_MODE_access_type_3_src(data)                                           ((0x00018000&(data))>>15)
#define DC_MT_MODE_get_access_type_3(data)                                           ((0x00018000&(data))>>15)
#define DC_MT_MODE_write_enable1_shift                                               (14)
#define DC_MT_MODE_write_enable1_mask                                                (0x00004000)
#define DC_MT_MODE_write_enable1(data)                                               (0x00004000&((data)<<14))
#define DC_MT_MODE_write_enable1_src(data)                                           ((0x00004000&(data))>>14)
#define DC_MT_MODE_get_write_enable1(data)                                           ((0x00004000&(data))>>14)
#define DC_MT_MODE_int1_shift                                                        (13)
#define DC_MT_MODE_int1_mask                                                         (0x00002000)
#define DC_MT_MODE_int1(data)                                                        (0x00002000&((data)<<13))
#define DC_MT_MODE_int1_src(data)                                                    ((0x00002000&(data))>>13)
#define DC_MT_MODE_get_int1(data)                                                    ((0x00002000&(data))>>13)
#define DC_MT_MODE_write_enable2_shift                                               (12)
#define DC_MT_MODE_write_enable2_mask                                                (0x00001000)
#define DC_MT_MODE_write_enable2(data)                                               (0x00001000&((data)<<12))
#define DC_MT_MODE_write_enable2_src(data)                                           ((0x00001000&(data))>>12)
#define DC_MT_MODE_get_write_enable2(data)                                           ((0x00001000&(data))>>12)
#define DC_MT_MODE_int2_shift                                                        (11)
#define DC_MT_MODE_int2_mask                                                         (0x00000800)
#define DC_MT_MODE_int2(data)                                                        (0x00000800&((data)<<11))
#define DC_MT_MODE_int2_src(data)                                                    ((0x00000800&(data))>>11)
#define DC_MT_MODE_get_int2(data)                                                    ((0x00000800&(data))>>11)
#define DC_MT_MODE_write_enable3_shift                                               (10)
#define DC_MT_MODE_write_enable3_mask                                                (0x00000400)
#define DC_MT_MODE_write_enable3(data)                                               (0x00000400&((data)<<10))
#define DC_MT_MODE_write_enable3_src(data)                                           ((0x00000400&(data))>>10)
#define DC_MT_MODE_get_write_enable3(data)                                           ((0x00000400&(data))>>10)
#define DC_MT_MODE_int3_shift                                                        (9)
#define DC_MT_MODE_int3_mask                                                         (0x00000200)
#define DC_MT_MODE_int3(data)                                                        (0x00000200&((data)<<9))
#define DC_MT_MODE_int3_src(data)                                                    ((0x00000200&(data))>>9)
#define DC_MT_MODE_get_int3(data)                                                    ((0x00000200&(data))>>9)
#define DC_MT_MODE_write_enable4_shift                                               (8)
#define DC_MT_MODE_write_enable4_mask                                                (0x00000100)
#define DC_MT_MODE_write_enable4(data)                                               (0x00000100&((data)<<8))
#define DC_MT_MODE_write_enable4_src(data)                                           ((0x00000100&(data))>>8)
#define DC_MT_MODE_get_write_enable4(data)                                           ((0x00000100&(data))>>8)
#define DC_MT_MODE_cpu_shift                                                         (6)
#define DC_MT_MODE_cpu_mask                                                          (0x000000C0)
#define DC_MT_MODE_cpu(data)                                                         (0x000000C0&((data)<<6))
#define DC_MT_MODE_cpu_src(data)                                                     ((0x000000C0&(data))>>6)
#define DC_MT_MODE_get_cpu(data)                                                     ((0x000000C0&(data))>>6)
#define DC_MT_MODE_int1_en_shift                                                     (5)
#define DC_MT_MODE_int1_en_mask                                                      (0x00000020)
#define DC_MT_MODE_int1_en(data)                                                     (0x00000020&((data)<<5))
#define DC_MT_MODE_int1_en_src(data)                                                 ((0x00000020&(data))>>5)
#define DC_MT_MODE_get_int1_en(data)                                                 ((0x00000020&(data))>>5)
#define DC_MT_MODE_int2_en_shift                                                     (4)
#define DC_MT_MODE_int2_en_mask                                                      (0x00000010)
#define DC_MT_MODE_int2_en(data)                                                     (0x00000010&((data)<<4))
#define DC_MT_MODE_int2_en_src(data)                                                 ((0x00000010&(data))>>4)
#define DC_MT_MODE_get_int2_en(data)                                                 ((0x00000010&(data))>>4)
#define DC_MT_MODE_int3_en_shift                                                     (3)
#define DC_MT_MODE_int3_en_mask                                                      (0x00000008)
#define DC_MT_MODE_int3_en(data)                                                     (0x00000008&((data)<<3))
#define DC_MT_MODE_int3_en_src(data)                                                 ((0x00000008&(data))>>3)
#define DC_MT_MODE_get_int3_en(data)                                                 ((0x00000008&(data))>>3)
#define DC_MT_MODE_write_enable5_shift                                               (2)
#define DC_MT_MODE_write_enable5_mask                                                (0x00000004)
#define DC_MT_MODE_write_enable5(data)                                               (0x00000004&((data)<<2))
#define DC_MT_MODE_write_enable5_src(data)                                           ((0x00000004&(data))>>2)
#define DC_MT_MODE_get_write_enable5(data)                                           ((0x00000004&(data))>>2)
#define DC_MT_MODE_mode_shift                                                        (0)
#define DC_MT_MODE_mode_mask                                                         (0x00000003)
#define DC_MT_MODE_mode(data)                                                        (0x00000003&((data)<<0))
#define DC_MT_MODE_mode_src(data)                                                    ((0x00000003&(data))>>0)
#define DC_MT_MODE_get_mode(data)                                                    ((0x00000003&(data))>>0)


#define DC_MT_TABLE_0                                                                0x18008260
#define DC_MT_TABLE_1                                                                0x18008264
#define DC_MT_TABLE_2                                                                0x18008268
#define DC_MT_TABLE_3                                                                0x1800826C
#define DC_MT_TABLE_4                                                                0x18008270
#define DC_MT_TABLE_5                                                                0x18008274
#define DC_MT_TABLE_6                                                                0x18008278
#define DC_MT_TABLE_7                                                                0x1800827C
#define DC_MT_TABLE_0_reg_addr                                                       "0xB8008260"
#define DC_MT_TABLE_1_reg_addr                                                       "0xB8008264"
#define DC_MT_TABLE_2_reg_addr                                                       "0xB8008268"
#define DC_MT_TABLE_3_reg_addr                                                       "0xB800826C"
#define DC_MT_TABLE_4_reg_addr                                                       "0xB8008270"
#define DC_MT_TABLE_5_reg_addr                                                       "0xB8008274"
#define DC_MT_TABLE_6_reg_addr                                                       "0xB8008278"
#define DC_MT_TABLE_7_reg_addr                                                       "0xB800827C"
#define DC_MT_TABLE_0_reg                                                            0xB8008260
#define DC_MT_TABLE_1_reg                                                            0xB8008264
#define DC_MT_TABLE_2_reg                                                            0xB8008268
#define DC_MT_TABLE_3_reg                                                            0xB800826C
#define DC_MT_TABLE_4_reg                                                            0xB8008270
#define DC_MT_TABLE_5_reg                                                            0xB8008274
#define DC_MT_TABLE_6_reg                                                            0xB8008278
#define DC_MT_TABLE_7_reg                                                            0xB800827C
#define set_DC_MT_TABLE_0_reg(data)   (*((volatile unsigned int*) DC_MT_TABLE_0_reg)=data)
#define set_DC_MT_TABLE_1_reg(data)   (*((volatile unsigned int*) DC_MT_TABLE_1_reg)=data)
#define set_DC_MT_TABLE_2_reg(data)   (*((volatile unsigned int*) DC_MT_TABLE_2_reg)=data)
#define set_DC_MT_TABLE_3_reg(data)   (*((volatile unsigned int*) DC_MT_TABLE_3_reg)=data)
#define set_DC_MT_TABLE_4_reg(data)   (*((volatile unsigned int*) DC_MT_TABLE_4_reg)=data)
#define set_DC_MT_TABLE_5_reg(data)   (*((volatile unsigned int*) DC_MT_TABLE_5_reg)=data)
#define set_DC_MT_TABLE_6_reg(data)   (*((volatile unsigned int*) DC_MT_TABLE_6_reg)=data)
#define set_DC_MT_TABLE_7_reg(data)   (*((volatile unsigned int*) DC_MT_TABLE_7_reg)=data)
#define get_DC_MT_TABLE_0_reg   (*((volatile unsigned int*) DC_MT_TABLE_0_reg))
#define get_DC_MT_TABLE_1_reg   (*((volatile unsigned int*) DC_MT_TABLE_1_reg))
#define get_DC_MT_TABLE_2_reg   (*((volatile unsigned int*) DC_MT_TABLE_2_reg))
#define get_DC_MT_TABLE_3_reg   (*((volatile unsigned int*) DC_MT_TABLE_3_reg))
#define get_DC_MT_TABLE_4_reg   (*((volatile unsigned int*) DC_MT_TABLE_4_reg))
#define get_DC_MT_TABLE_5_reg   (*((volatile unsigned int*) DC_MT_TABLE_5_reg))
#define get_DC_MT_TABLE_6_reg   (*((volatile unsigned int*) DC_MT_TABLE_6_reg))
#define get_DC_MT_TABLE_7_reg   (*((volatile unsigned int*) DC_MT_TABLE_7_reg))
#define DC_MT_TABLE_0_inst_adr                                                       "0x0098"
#define DC_MT_TABLE_1_inst_adr                                                       "0x0099"
#define DC_MT_TABLE_2_inst_adr                                                       "0x009A"
#define DC_MT_TABLE_3_inst_adr                                                       "0x009B"
#define DC_MT_TABLE_4_inst_adr                                                       "0x009C"
#define DC_MT_TABLE_5_inst_adr                                                       "0x009D"
#define DC_MT_TABLE_6_inst_adr                                                       "0x009E"
#define DC_MT_TABLE_7_inst_adr                                                       "0x009F"
#define DC_MT_TABLE_0_inst                                                           0x0098
#define DC_MT_TABLE_1_inst                                                           0x0099
#define DC_MT_TABLE_2_inst                                                           0x009A
#define DC_MT_TABLE_3_inst                                                           0x009B
#define DC_MT_TABLE_4_inst                                                           0x009C
#define DC_MT_TABLE_5_inst                                                           0x009D
#define DC_MT_TABLE_6_inst                                                           0x009E
#define DC_MT_TABLE_7_inst                                                           0x009F
#define DC_MT_TABLE_module_ID_0_shift                                                (21)
#define DC_MT_TABLE_module_ID_0_mask                                                 (0x0FE00000)
#define DC_MT_TABLE_module_ID_0(data)                                                (0x0FE00000&((data)<<21))
#define DC_MT_TABLE_module_ID_0_src(data)                                            ((0x0FE00000&(data))>>21)
#define DC_MT_TABLE_get_module_ID_0(data)                                            ((0x0FE00000&(data))>>21)
#define DC_MT_TABLE_module_ID_1_shift                                                (14)
#define DC_MT_TABLE_module_ID_1_mask                                                 (0x001FC000)
#define DC_MT_TABLE_module_ID_1(data)                                                (0x001FC000&((data)<<14))
#define DC_MT_TABLE_module_ID_1_src(data)                                            ((0x001FC000&(data))>>14)
#define DC_MT_TABLE_get_module_ID_1(data)                                            ((0x001FC000&(data))>>14)
#define DC_MT_TABLE_module_ID_2_shift                                                (7)
#define DC_MT_TABLE_module_ID_2_mask                                                 (0x00003F80)
#define DC_MT_TABLE_module_ID_2(data)                                                (0x00003F80&((data)<<7))
#define DC_MT_TABLE_module_ID_2_src(data)                                            ((0x00003F80&(data))>>7)
#define DC_MT_TABLE_get_module_ID_2(data)                                            ((0x00003F80&(data))>>7)
#define DC_MT_TABLE_module_ID_3_shift                                                (0)
#define DC_MT_TABLE_module_ID_3_mask                                                 (0x0000007F)
#define DC_MT_TABLE_module_ID_3(data)                                                (0x0000007F&((data)<<0))
#define DC_MT_TABLE_module_ID_3_src(data)                                            ((0x0000007F&(data))>>0)
#define DC_MT_TABLE_get_module_ID_3(data)                                            ((0x0000007F&(data))>>0)


#define DC_MT_ADDCMD_HI_0                                                            0x18008280
#define DC_MT_ADDCMD_HI_1                                                            0x18008284
#define DC_MT_ADDCMD_HI_2                                                            0x18008288
#define DC_MT_ADDCMD_HI_3                                                            0x1800828C
#define DC_MT_ADDCMD_HI_4                                                            0x18008290
#define DC_MT_ADDCMD_HI_5                                                            0x18008294
#define DC_MT_ADDCMD_HI_6                                                            0x18008298
#define DC_MT_ADDCMD_HI_7                                                            0x1800829C
#define DC_MT_ADDCMD_HI_0_reg_addr                                                   "0xB8008280"
#define DC_MT_ADDCMD_HI_1_reg_addr                                                   "0xB8008284"
#define DC_MT_ADDCMD_HI_2_reg_addr                                                   "0xB8008288"
#define DC_MT_ADDCMD_HI_3_reg_addr                                                   "0xB800828C"
#define DC_MT_ADDCMD_HI_4_reg_addr                                                   "0xB8008290"
#define DC_MT_ADDCMD_HI_5_reg_addr                                                   "0xB8008294"
#define DC_MT_ADDCMD_HI_6_reg_addr                                                   "0xB8008298"
#define DC_MT_ADDCMD_HI_7_reg_addr                                                   "0xB800829C"
#define DC_MT_ADDCMD_HI_0_reg                                                        0xB8008280
#define DC_MT_ADDCMD_HI_1_reg                                                        0xB8008284
#define DC_MT_ADDCMD_HI_2_reg                                                        0xB8008288
#define DC_MT_ADDCMD_HI_3_reg                                                        0xB800828C
#define DC_MT_ADDCMD_HI_4_reg                                                        0xB8008290
#define DC_MT_ADDCMD_HI_5_reg                                                        0xB8008294
#define DC_MT_ADDCMD_HI_6_reg                                                        0xB8008298
#define DC_MT_ADDCMD_HI_7_reg                                                        0xB800829C
#define set_DC_MT_ADDCMD_HI_0_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_0_reg)=data)
#define set_DC_MT_ADDCMD_HI_1_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_1_reg)=data)
#define set_DC_MT_ADDCMD_HI_2_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_2_reg)=data)
#define set_DC_MT_ADDCMD_HI_3_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_3_reg)=data)
#define set_DC_MT_ADDCMD_HI_4_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_4_reg)=data)
#define set_DC_MT_ADDCMD_HI_5_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_5_reg)=data)
#define set_DC_MT_ADDCMD_HI_6_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_6_reg)=data)
#define set_DC_MT_ADDCMD_HI_7_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_7_reg)=data)
#define get_DC_MT_ADDCMD_HI_0_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_0_reg))
#define get_DC_MT_ADDCMD_HI_1_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_1_reg))
#define get_DC_MT_ADDCMD_HI_2_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_2_reg))
#define get_DC_MT_ADDCMD_HI_3_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_3_reg))
#define get_DC_MT_ADDCMD_HI_4_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_4_reg))
#define get_DC_MT_ADDCMD_HI_5_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_5_reg))
#define get_DC_MT_ADDCMD_HI_6_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_6_reg))
#define get_DC_MT_ADDCMD_HI_7_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_HI_7_reg))
#define DC_MT_ADDCMD_HI_0_inst_adr                                                   "0x00A0"
#define DC_MT_ADDCMD_HI_1_inst_adr                                                   "0x00A1"
#define DC_MT_ADDCMD_HI_2_inst_adr                                                   "0x00A2"
#define DC_MT_ADDCMD_HI_3_inst_adr                                                   "0x00A3"
#define DC_MT_ADDCMD_HI_4_inst_adr                                                   "0x00A4"
#define DC_MT_ADDCMD_HI_5_inst_adr                                                   "0x00A5"
#define DC_MT_ADDCMD_HI_6_inst_adr                                                   "0x00A6"
#define DC_MT_ADDCMD_HI_7_inst_adr                                                   "0x00A7"
#define DC_MT_ADDCMD_HI_0_inst                                                       0x00A0
#define DC_MT_ADDCMD_HI_1_inst                                                       0x00A1
#define DC_MT_ADDCMD_HI_2_inst                                                       0x00A2
#define DC_MT_ADDCMD_HI_3_inst                                                       0x00A3
#define DC_MT_ADDCMD_HI_4_inst                                                       0x00A4
#define DC_MT_ADDCMD_HI_5_inst                                                       0x00A5
#define DC_MT_ADDCMD_HI_6_inst                                                       0x00A6
#define DC_MT_ADDCMD_HI_7_inst                                                       0x00A7
#define DC_MT_ADDCMD_HI_ever_trap_shift                                              (21)
#define DC_MT_ADDCMD_HI_ever_trap_mask                                               (0x00200000)
#define DC_MT_ADDCMD_HI_ever_trap(data)                                              (0x00200000&((data)<<21))
#define DC_MT_ADDCMD_HI_ever_trap_src(data)                                          ((0x00200000&(data))>>21)
#define DC_MT_ADDCMD_HI_get_ever_trap(data)                                          ((0x00200000&(data))>>21)
#define DC_MT_ADDCMD_HI_module_ID_shift                                              (14)
#define DC_MT_ADDCMD_HI_module_ID_mask                                               (0x001FC000)
#define DC_MT_ADDCMD_HI_module_ID(data)                                              (0x001FC000&((data)<<14))
#define DC_MT_ADDCMD_HI_module_ID_src(data)                                          ((0x001FC000&(data))>>14)
#define DC_MT_ADDCMD_HI_get_module_ID(data)                                          ((0x001FC000&(data))>>14)
#define DC_MT_ADDCMD_HI_addcmd_shift                                                 (0)
#define DC_MT_ADDCMD_HI_addcmd_mask                                                  (0x00003FFF)
#define DC_MT_ADDCMD_HI_addcmd(data)                                                 (0x00003FFF&((data)<<0))
#define DC_MT_ADDCMD_HI_addcmd_src(data)                                             ((0x00003FFF&(data))>>0)
#define DC_MT_ADDCMD_HI_get_addcmd(data)                                             ((0x00003FFF&(data))>>0)


#define DC_MT_ADDCMD_LO_0                                                            0x180082A0
#define DC_MT_ADDCMD_LO_1                                                            0x180082A4
#define DC_MT_ADDCMD_LO_2                                                            0x180082A8
#define DC_MT_ADDCMD_LO_3                                                            0x180082AC
#define DC_MT_ADDCMD_LO_4                                                            0x180082B0
#define DC_MT_ADDCMD_LO_5                                                            0x180082B4
#define DC_MT_ADDCMD_LO_6                                                            0x180082B8
#define DC_MT_ADDCMD_LO_7                                                            0x180082BC
#define DC_MT_ADDCMD_LO_0_reg_addr                                                   "0xB80082A0"
#define DC_MT_ADDCMD_LO_1_reg_addr                                                   "0xB80082A4"
#define DC_MT_ADDCMD_LO_2_reg_addr                                                   "0xB80082A8"
#define DC_MT_ADDCMD_LO_3_reg_addr                                                   "0xB80082AC"
#define DC_MT_ADDCMD_LO_4_reg_addr                                                   "0xB80082B0"
#define DC_MT_ADDCMD_LO_5_reg_addr                                                   "0xB80082B4"
#define DC_MT_ADDCMD_LO_6_reg_addr                                                   "0xB80082B8"
#define DC_MT_ADDCMD_LO_7_reg_addr                                                   "0xB80082BC"
#define DC_MT_ADDCMD_LO_0_reg                                                        0xB80082A0
#define DC_MT_ADDCMD_LO_1_reg                                                        0xB80082A4
#define DC_MT_ADDCMD_LO_2_reg                                                        0xB80082A8
#define DC_MT_ADDCMD_LO_3_reg                                                        0xB80082AC
#define DC_MT_ADDCMD_LO_4_reg                                                        0xB80082B0
#define DC_MT_ADDCMD_LO_5_reg                                                        0xB80082B4
#define DC_MT_ADDCMD_LO_6_reg                                                        0xB80082B8
#define DC_MT_ADDCMD_LO_7_reg                                                        0xB80082BC
#define set_DC_MT_ADDCMD_LO_0_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_0_reg)=data)
#define set_DC_MT_ADDCMD_LO_1_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_1_reg)=data)
#define set_DC_MT_ADDCMD_LO_2_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_2_reg)=data)
#define set_DC_MT_ADDCMD_LO_3_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_3_reg)=data)
#define set_DC_MT_ADDCMD_LO_4_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_4_reg)=data)
#define set_DC_MT_ADDCMD_LO_5_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_5_reg)=data)
#define set_DC_MT_ADDCMD_LO_6_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_6_reg)=data)
#define set_DC_MT_ADDCMD_LO_7_reg(data)   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_7_reg)=data)
#define get_DC_MT_ADDCMD_LO_0_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_0_reg))
#define get_DC_MT_ADDCMD_LO_1_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_1_reg))
#define get_DC_MT_ADDCMD_LO_2_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_2_reg))
#define get_DC_MT_ADDCMD_LO_3_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_3_reg))
#define get_DC_MT_ADDCMD_LO_4_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_4_reg))
#define get_DC_MT_ADDCMD_LO_5_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_5_reg))
#define get_DC_MT_ADDCMD_LO_6_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_6_reg))
#define get_DC_MT_ADDCMD_LO_7_reg   (*((volatile unsigned int*) DC_MT_ADDCMD_LO_7_reg))
#define DC_MT_ADDCMD_LO_0_inst_adr                                                   "0x00A8"
#define DC_MT_ADDCMD_LO_1_inst_adr                                                   "0x00A9"
#define DC_MT_ADDCMD_LO_2_inst_adr                                                   "0x00AA"
#define DC_MT_ADDCMD_LO_3_inst_adr                                                   "0x00AB"
#define DC_MT_ADDCMD_LO_4_inst_adr                                                   "0x00AC"
#define DC_MT_ADDCMD_LO_5_inst_adr                                                   "0x00AD"
#define DC_MT_ADDCMD_LO_6_inst_adr                                                   "0x00AE"
#define DC_MT_ADDCMD_LO_7_inst_adr                                                   "0x00AF"
#define DC_MT_ADDCMD_LO_0_inst                                                       0x00A8
#define DC_MT_ADDCMD_LO_1_inst                                                       0x00A9
#define DC_MT_ADDCMD_LO_2_inst                                                       0x00AA
#define DC_MT_ADDCMD_LO_3_inst                                                       0x00AB
#define DC_MT_ADDCMD_LO_4_inst                                                       0x00AC
#define DC_MT_ADDCMD_LO_5_inst                                                       0x00AD
#define DC_MT_ADDCMD_LO_6_inst                                                       0x00AE
#define DC_MT_ADDCMD_LO_7_inst                                                       0x00AF
#define DC_MT_ADDCMD_LO_addcmd_shift                                                 (0)
#define DC_MT_ADDCMD_LO_addcmd_mask                                                  (0xFFFFFFFF)
#define DC_MT_ADDCMD_LO_addcmd(data)                                                 (0xFFFFFFFF&((data)<<0))
#define DC_MT_ADDCMD_LO_addcmd_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define DC_MT_ADDCMD_LO_get_addcmd(data)                                             ((0xFFFFFFFF&(data))>>0)


#define DC_MT_MISC                                                                   0x180082C0
#define DC_MT_MISC_reg_addr                                                          "0xB80082C0"
#define DC_MT_MISC_reg                                                               0xB80082C0
#define set_DC_MT_MISC_reg(data)   (*((volatile unsigned int*) DC_MT_MISC_reg)=data)
#define get_DC_MT_MISC_reg   (*((volatile unsigned int*) DC_MT_MISC_reg))
#define DC_MT_MISC_inst_adr                                                          "0x00B0"
#define DC_MT_MISC_inst                                                              0x00B0
#define DC_MT_MISC_enable_block_info_shift                                           (1)
#define DC_MT_MISC_enable_block_info_mask                                            (0x00000002)
#define DC_MT_MISC_enable_block_info(data)                                           (0x00000002&((data)<<1))
#define DC_MT_MISC_enable_block_info_src(data)                                       ((0x00000002&(data))>>1)
#define DC_MT_MISC_get_enable_block_info(data)                                       ((0x00000002&(data))>>1)
#define DC_MT_MISC_disable_cross_range_check_shift                                   (0)
#define DC_MT_MISC_disable_cross_range_check_mask                                    (0x00000001)
#define DC_MT_MISC_disable_cross_range_check(data)                                   (0x00000001&((data)<<0))
#define DC_MT_MISC_disable_cross_range_check_src(data)                               ((0x00000001&(data))>>0)
#define DC_MT_MISC_get_disable_cross_range_check(data)                               ((0x00000001&(data))>>0)


#define DC_EC_CTRL                                                                   0x18008300
#define DC_EC_CTRL_reg_addr                                                          "0xB8008300"
#define DC_EC_CTRL_reg                                                               0xB8008300
#define set_DC_EC_CTRL_reg(data)   (*((volatile unsigned int*) DC_EC_CTRL_reg)=data)
#define get_DC_EC_CTRL_reg   (*((volatile unsigned int*) DC_EC_CTRL_reg))
#define DC_EC_CTRL_inst_adr                                                          "0x00C0"
#define DC_EC_CTRL_inst                                                              0x00C0
#define DC_EC_CTRL_write_enable4_shift                                               (8)
#define DC_EC_CTRL_write_enable4_mask                                                (0x00000100)
#define DC_EC_CTRL_write_enable4(data)                                               (0x00000100&((data)<<8))
#define DC_EC_CTRL_write_enable4_src(data)                                           ((0x00000100&(data))>>8)
#define DC_EC_CTRL_get_write_enable4(data)                                           ((0x00000100&(data))>>8)
#define DC_EC_CTRL_error_cmd_int_cpu_shift                                           (6)
#define DC_EC_CTRL_error_cmd_int_cpu_mask                                            (0x000000C0)
#define DC_EC_CTRL_error_cmd_int_cpu(data)                                           (0x000000C0&((data)<<6))
#define DC_EC_CTRL_error_cmd_int_cpu_src(data)                                       ((0x000000C0&(data))>>6)
#define DC_EC_CTRL_get_error_cmd_int_cpu(data)                                       ((0x000000C0&(data))>>6)
#define DC_EC_CTRL_write_enable3_shift                                               (5)
#define DC_EC_CTRL_write_enable3_mask                                                (0x00000020)
#define DC_EC_CTRL_write_enable3(data)                                               (0x00000020&((data)<<5))
#define DC_EC_CTRL_write_enable3_src(data)                                           ((0x00000020&(data))>>5)
#define DC_EC_CTRL_get_write_enable3(data)                                           ((0x00000020&(data))>>5)
#define DC_EC_CTRL_error_cmd_int_en_shift                                            (4)
#define DC_EC_CTRL_error_cmd_int_en_mask                                             (0x00000010)
#define DC_EC_CTRL_error_cmd_int_en(data)                                            (0x00000010&((data)<<4))
#define DC_EC_CTRL_error_cmd_int_en_src(data)                                        ((0x00000010&(data))>>4)
#define DC_EC_CTRL_get_error_cmd_int_en(data)                                        ((0x00000010&(data))>>4)
#define DC_EC_CTRL_write_enable2_shift                                               (3)
#define DC_EC_CTRL_write_enable2_mask                                                (0x00000008)
#define DC_EC_CTRL_write_enable2(data)                                               (0x00000008&((data)<<3))
#define DC_EC_CTRL_write_enable2_src(data)                                           ((0x00000008&(data))>>3)
#define DC_EC_CTRL_get_write_enable2(data)                                           ((0x00000008&(data))>>3)
#define DC_EC_CTRL_error_cmd_swap_en_shift                                           (2)
#define DC_EC_CTRL_error_cmd_swap_en_mask                                            (0x00000004)
#define DC_EC_CTRL_error_cmd_swap_en(data)                                           (0x00000004&((data)<<2))
#define DC_EC_CTRL_error_cmd_swap_en_src(data)                                       ((0x00000004&(data))>>2)
#define DC_EC_CTRL_get_error_cmd_swap_en(data)                                       ((0x00000004&(data))>>2)
#define DC_EC_CTRL_write_enable1_shift                                               (1)
#define DC_EC_CTRL_write_enable1_mask                                                (0x00000002)
#define DC_EC_CTRL_write_enable1(data)                                               (0x00000002&((data)<<1))
#define DC_EC_CTRL_write_enable1_src(data)                                           ((0x00000002&(data))>>1)
#define DC_EC_CTRL_get_write_enable1(data)                                           ((0x00000002&(data))>>1)
#define DC_EC_CTRL_error_cmd_detection_en_shift                                      (0)
#define DC_EC_CTRL_error_cmd_detection_en_mask                                       (0x00000001)
#define DC_EC_CTRL_error_cmd_detection_en(data)                                      (0x00000001&((data)<<0))
#define DC_EC_CTRL_error_cmd_detection_en_src(data)                                  ((0x00000001&(data))>>0)
#define DC_EC_CTRL_get_error_cmd_detection_en(data)                                  ((0x00000001&(data))>>0)


#define DC_EC_ADDCMD_HI                                                              0x18008304
#define DC_EC_ADDCMD_HI_reg_addr                                                     "0xB8008304"
#define DC_EC_ADDCMD_HI_reg                                                          0xB8008304
#define set_DC_EC_ADDCMD_HI_reg(data)   (*((volatile unsigned int*) DC_EC_ADDCMD_HI_reg)=data)
#define get_DC_EC_ADDCMD_HI_reg   (*((volatile unsigned int*) DC_EC_ADDCMD_HI_reg))
#define DC_EC_ADDCMD_HI_inst_adr                                                     "0x00C1"
#define DC_EC_ADDCMD_HI_inst                                                         0x00C1
#define DC_EC_ADDCMD_HI_error_cmd_int_shift                                          (31)
#define DC_EC_ADDCMD_HI_error_cmd_int_mask                                           (0x80000000)
#define DC_EC_ADDCMD_HI_error_cmd_int(data)                                          (0x80000000&((data)<<31))
#define DC_EC_ADDCMD_HI_error_cmd_int_src(data)                                      ((0x80000000&(data))>>31)
#define DC_EC_ADDCMD_HI_get_error_cmd_int(data)                                      ((0x80000000&(data))>>31)
#define DC_EC_ADDCMD_HI_error_cmd_ever_trap_shift                                    (30)
#define DC_EC_ADDCMD_HI_error_cmd_ever_trap_mask                                     (0x40000000)
#define DC_EC_ADDCMD_HI_error_cmd_ever_trap(data)                                    (0x40000000&((data)<<30))
#define DC_EC_ADDCMD_HI_error_cmd_ever_trap_src(data)                                ((0x40000000&(data))>>30)
#define DC_EC_ADDCMD_HI_get_error_cmd_ever_trap(data)                                ((0x40000000&(data))>>30)
#define DC_EC_ADDCMD_HI_trap_case_shift                                              (22)
#define DC_EC_ADDCMD_HI_trap_case_mask                                               (0x3FC00000)
#define DC_EC_ADDCMD_HI_trap_case(data)                                              (0x3FC00000&((data)<<22))
#define DC_EC_ADDCMD_HI_trap_case_src(data)                                          ((0x3FC00000&(data))>>22)
#define DC_EC_ADDCMD_HI_get_trap_case(data)                                          ((0x3FC00000&(data))>>22)
#define DC_EC_ADDCMD_HI_Addcmd_hi_shift                                              (0)
#define DC_EC_ADDCMD_HI_Addcmd_hi_mask                                               (0x003FFFFF)
#define DC_EC_ADDCMD_HI_Addcmd_hi(data)                                              (0x003FFFFF&((data)<<0))
#define DC_EC_ADDCMD_HI_Addcmd_hi_src(data)                                          ((0x003FFFFF&(data))>>0)
#define DC_EC_ADDCMD_HI_get_Addcmd_hi(data)                                          ((0x003FFFFF&(data))>>0)


#define DC_EC_ADDCMD_LO                                                              0x18008308
#define DC_EC_ADDCMD_LO_reg_addr                                                     "0xB8008308"
#define DC_EC_ADDCMD_LO_reg                                                          0xB8008308
#define set_DC_EC_ADDCMD_LO_reg(data)   (*((volatile unsigned int*) DC_EC_ADDCMD_LO_reg)=data)
#define get_DC_EC_ADDCMD_LO_reg   (*((volatile unsigned int*) DC_EC_ADDCMD_LO_reg))
#define DC_EC_ADDCMD_LO_inst_adr                                                     "0x00C2"
#define DC_EC_ADDCMD_LO_inst                                                         0x00C2
#define DC_EC_ADDCMD_LO_Addcmd_lo_shift                                              (0)
#define DC_EC_ADDCMD_LO_Addcmd_lo_mask                                               (0xFFFFFFFF)
#define DC_EC_ADDCMD_LO_Addcmd_lo(data)                                              (0xFFFFFFFF&((data)<<0))
#define DC_EC_ADDCMD_LO_Addcmd_lo_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define DC_EC_ADDCMD_LO_get_Addcmd_lo(data)                                          ((0xFFFFFFFF&(data))>>0)


#define DC_RD_TAG_CHECK                                                              0x1800830C
#define DC_RD_TAG_CHECK_reg_addr                                                     "0xB800830C"
#define DC_RD_TAG_CHECK_reg                                                          0xB800830C
#define set_DC_RD_TAG_CHECK_reg(data)   (*((volatile unsigned int*) DC_RD_TAG_CHECK_reg)=data)
#define get_DC_RD_TAG_CHECK_reg   (*((volatile unsigned int*) DC_RD_TAG_CHECK_reg))
#define DC_RD_TAG_CHECK_inst_adr                                                     "0x00C3"
#define DC_RD_TAG_CHECK_inst                                                         0x00C3
#define DC_RD_TAG_CHECK_write_enable3_shift                                          (6)
#define DC_RD_TAG_CHECK_write_enable3_mask                                           (0x00000040)
#define DC_RD_TAG_CHECK_write_enable3(data)                                          (0x00000040&((data)<<6))
#define DC_RD_TAG_CHECK_write_enable3_src(data)                                      ((0x00000040&(data))>>6)
#define DC_RD_TAG_CHECK_get_write_enable3(data)                                      ((0x00000040&(data))>>6)
#define DC_RD_TAG_CHECK_tag_check_int_cpu_shift                                      (4)
#define DC_RD_TAG_CHECK_tag_check_int_cpu_mask                                       (0x00000030)
#define DC_RD_TAG_CHECK_tag_check_int_cpu(data)                                      (0x00000030&((data)<<4))
#define DC_RD_TAG_CHECK_tag_check_int_cpu_src(data)                                  ((0x00000030&(data))>>4)
#define DC_RD_TAG_CHECK_get_tag_check_int_cpu(data)                                  ((0x00000030&(data))>>4)
#define DC_RD_TAG_CHECK_write_enable2_shift                                          (3)
#define DC_RD_TAG_CHECK_write_enable2_mask                                           (0x00000008)
#define DC_RD_TAG_CHECK_write_enable2(data)                                          (0x00000008&((data)<<3))
#define DC_RD_TAG_CHECK_write_enable2_src(data)                                      ((0x00000008&(data))>>3)
#define DC_RD_TAG_CHECK_get_write_enable2(data)                                      ((0x00000008&(data))>>3)
#define DC_RD_TAG_CHECK_tag_check_int_en_shift                                       (2)
#define DC_RD_TAG_CHECK_tag_check_int_en_mask                                        (0x00000004)
#define DC_RD_TAG_CHECK_tag_check_int_en(data)                                       (0x00000004&((data)<<2))
#define DC_RD_TAG_CHECK_tag_check_int_en_src(data)                                   ((0x00000004&(data))>>2)
#define DC_RD_TAG_CHECK_get_tag_check_int_en(data)                                   ((0x00000004&(data))>>2)
#define DC_RD_TAG_CHECK_write_enable1_shift                                          (1)
#define DC_RD_TAG_CHECK_write_enable1_mask                                           (0x00000002)
#define DC_RD_TAG_CHECK_write_enable1(data)                                          (0x00000002&((data)<<1))
#define DC_RD_TAG_CHECK_write_enable1_src(data)                                      ((0x00000002&(data))>>1)
#define DC_RD_TAG_CHECK_get_write_enable1(data)                                      ((0x00000002&(data))>>1)
#define DC_RD_TAG_CHECK_tag_check_en_shift                                           (0)
#define DC_RD_TAG_CHECK_tag_check_en_mask                                            (0x00000001)
#define DC_RD_TAG_CHECK_tag_check_en(data)                                           (0x00000001&((data)<<0))
#define DC_RD_TAG_CHECK_tag_check_en_src(data)                                       ((0x00000001&(data))>>0)
#define DC_RD_TAG_CHECK_get_tag_check_en(data)                                       ((0x00000001&(data))>>0)


#define DC_RD_TAG_CHECK_ST                                                           0x18008310
#define DC_RD_TAG_CHECK_ST_reg_addr                                                  "0xB8008310"
#define DC_RD_TAG_CHECK_ST_reg                                                       0xB8008310
#define set_DC_RD_TAG_CHECK_ST_reg(data)   (*((volatile unsigned int*) DC_RD_TAG_CHECK_ST_reg)=data)
#define get_DC_RD_TAG_CHECK_ST_reg   (*((volatile unsigned int*) DC_RD_TAG_CHECK_ST_reg))
#define DC_RD_TAG_CHECK_ST_inst_adr                                                  "0x00C4"
#define DC_RD_TAG_CHECK_ST_inst                                                      0x00C4
#define DC_RD_TAG_CHECK_ST_rd_tag_mismatch_ever_shift                                (1)
#define DC_RD_TAG_CHECK_ST_rd_tag_mismatch_ever_mask                                 (0x00000002)
#define DC_RD_TAG_CHECK_ST_rd_tag_mismatch_ever(data)                                (0x00000002&((data)<<1))
#define DC_RD_TAG_CHECK_ST_rd_tag_mismatch_ever_src(data)                            ((0x00000002&(data))>>1)
#define DC_RD_TAG_CHECK_ST_get_rd_tag_mismatch_ever(data)                            ((0x00000002&(data))>>1)
#define DC_RD_TAG_CHECK_ST_rd_tag_mismatch_int_shift                                 (0)
#define DC_RD_TAG_CHECK_ST_rd_tag_mismatch_int_mask                                  (0x00000001)
#define DC_RD_TAG_CHECK_ST_rd_tag_mismatch_int(data)                                 (0x00000001&((data)<<0))
#define DC_RD_TAG_CHECK_ST_rd_tag_mismatch_int_src(data)                             ((0x00000001&(data))>>0)
#define DC_RD_TAG_CHECK_ST_get_rd_tag_mismatch_int(data)                             ((0x00000001&(data))>>0)


#define DC_MEM_PROTECT_CTRL                                                          0x18008400
#define DC_MEM_PROTECT_CTRL_reg_addr                                                 "0xB8008400"
#define DC_MEM_PROTECT_CTRL_reg                                                      0xB8008400
#define set_DC_MEM_PROTECT_CTRL_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_CTRL_reg)=data)
#define get_DC_MEM_PROTECT_CTRL_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_CTRL_reg))
#define DC_MEM_PROTECT_CTRL_inst_adr                                                 "0x0000"
#define DC_MEM_PROTECT_CTRL_inst                                                     0x0000
#define DC_MEM_PROTECT_CTRL_write_enable0_shift                                      (31)
#define DC_MEM_PROTECT_CTRL_write_enable0_mask                                       (0x80000000)
#define DC_MEM_PROTECT_CTRL_write_enable0(data)                                      (0x80000000&((data)<<31))
#define DC_MEM_PROTECT_CTRL_write_enable0_src(data)                                  ((0x80000000&(data))>>31)
#define DC_MEM_PROTECT_CTRL_get_write_enable0(data)                                  ((0x80000000&(data))>>31)
#define DC_MEM_PROTECT_CTRL_rd_only_0_sel_shift                                      (30)
#define DC_MEM_PROTECT_CTRL_rd_only_0_sel_mask                                       (0x40000000)
#define DC_MEM_PROTECT_CTRL_rd_only_0_sel(data)                                      (0x40000000&((data)<<30))
#define DC_MEM_PROTECT_CTRL_rd_only_0_sel_src(data)                                  ((0x40000000&(data))>>30)
#define DC_MEM_PROTECT_CTRL_get_rd_only_0_sel(data)                                  ((0x40000000&(data))>>30)
#define DC_MEM_PROTECT_CTRL_blk_protect_0_sel_shift                                  (29)
#define DC_MEM_PROTECT_CTRL_blk_protect_0_sel_mask                                   (0x20000000)
#define DC_MEM_PROTECT_CTRL_blk_protect_0_sel(data)                                  (0x20000000&((data)<<29))
#define DC_MEM_PROTECT_CTRL_blk_protect_0_sel_src(data)                              ((0x20000000&(data))>>29)
#define DC_MEM_PROTECT_CTRL_get_blk_protect_0_sel(data)                              ((0x20000000&(data))>>29)
#define DC_MEM_PROTECT_CTRL_protect_0_sel_shift                                      (28)
#define DC_MEM_PROTECT_CTRL_protect_0_sel_mask                                       (0x10000000)
#define DC_MEM_PROTECT_CTRL_protect_0_sel(data)                                      (0x10000000&((data)<<28))
#define DC_MEM_PROTECT_CTRL_protect_0_sel_src(data)                                  ((0x10000000&(data))>>28)
#define DC_MEM_PROTECT_CTRL_get_protect_0_sel(data)                                  ((0x10000000&(data))>>28)
#define DC_MEM_PROTECT_CTRL_write_enable1_shift                                      (27)
#define DC_MEM_PROTECT_CTRL_write_enable1_mask                                       (0x08000000)
#define DC_MEM_PROTECT_CTRL_write_enable1(data)                                      (0x08000000&((data)<<27))
#define DC_MEM_PROTECT_CTRL_write_enable1_src(data)                                  ((0x08000000&(data))>>27)
#define DC_MEM_PROTECT_CTRL_get_write_enable1(data)                                  ((0x08000000&(data))>>27)
#define DC_MEM_PROTECT_CTRL_rd_only_3_en_shift                                       (26)
#define DC_MEM_PROTECT_CTRL_rd_only_3_en_mask                                        (0x04000000)
#define DC_MEM_PROTECT_CTRL_rd_only_3_en(data)                                       (0x04000000&((data)<<26))
#define DC_MEM_PROTECT_CTRL_rd_only_3_en_src(data)                                   ((0x04000000&(data))>>26)
#define DC_MEM_PROTECT_CTRL_get_rd_only_3_en(data)                                   ((0x04000000&(data))>>26)
#define DC_MEM_PROTECT_CTRL_rd_only_2_en_shift                                       (25)
#define DC_MEM_PROTECT_CTRL_rd_only_2_en_mask                                        (0x02000000)
#define DC_MEM_PROTECT_CTRL_rd_only_2_en(data)                                       (0x02000000&((data)<<25))
#define DC_MEM_PROTECT_CTRL_rd_only_2_en_src(data)                                   ((0x02000000&(data))>>25)
#define DC_MEM_PROTECT_CTRL_get_rd_only_2_en(data)                                   ((0x02000000&(data))>>25)
#define DC_MEM_PROTECT_CTRL_rd_only_1_en_shift                                       (24)
#define DC_MEM_PROTECT_CTRL_rd_only_1_en_mask                                        (0x01000000)
#define DC_MEM_PROTECT_CTRL_rd_only_1_en(data)                                       (0x01000000&((data)<<24))
#define DC_MEM_PROTECT_CTRL_rd_only_1_en_src(data)                                   ((0x01000000&(data))>>24)
#define DC_MEM_PROTECT_CTRL_get_rd_only_1_en(data)                                   ((0x01000000&(data))>>24)
#define DC_MEM_PROTECT_CTRL_rd_only_0_en_shift                                       (23)
#define DC_MEM_PROTECT_CTRL_rd_only_0_en_mask                                        (0x00800000)
#define DC_MEM_PROTECT_CTRL_rd_only_0_en(data)                                       (0x00800000&((data)<<23))
#define DC_MEM_PROTECT_CTRL_rd_only_0_en_src(data)                                   ((0x00800000&(data))>>23)
#define DC_MEM_PROTECT_CTRL_get_rd_only_0_en(data)                                   ((0x00800000&(data))>>23)
#define DC_MEM_PROTECT_CTRL_write_enable2_shift                                      (22)
#define DC_MEM_PROTECT_CTRL_write_enable2_mask                                       (0x00400000)
#define DC_MEM_PROTECT_CTRL_write_enable2(data)                                      (0x00400000&((data)<<22))
#define DC_MEM_PROTECT_CTRL_write_enable2_src(data)                                  ((0x00400000&(data))>>22)
#define DC_MEM_PROTECT_CTRL_get_write_enable2(data)                                  ((0x00400000&(data))>>22)
#define DC_MEM_PROTECT_CTRL_blk_protect_1_wpro_en_shift                              (21)
#define DC_MEM_PROTECT_CTRL_blk_protect_1_wpro_en_mask                               (0x00200000)
#define DC_MEM_PROTECT_CTRL_blk_protect_1_wpro_en(data)                              (0x00200000&((data)<<21))
#define DC_MEM_PROTECT_CTRL_blk_protect_1_wpro_en_src(data)                          ((0x00200000&(data))>>21)
#define DC_MEM_PROTECT_CTRL_get_blk_protect_1_wpro_en(data)                          ((0x00200000&(data))>>21)
#define DC_MEM_PROTECT_CTRL_blk_protect_0_wpro_en_shift                              (20)
#define DC_MEM_PROTECT_CTRL_blk_protect_0_wpro_en_mask                               (0x00100000)
#define DC_MEM_PROTECT_CTRL_blk_protect_0_wpro_en(data)                              (0x00100000&((data)<<20))
#define DC_MEM_PROTECT_CTRL_blk_protect_0_wpro_en_src(data)                          ((0x00100000&(data))>>20)
#define DC_MEM_PROTECT_CTRL_get_blk_protect_0_wpro_en(data)                          ((0x00100000&(data))>>20)
#define DC_MEM_PROTECT_CTRL_blk_protect_1_en_shift                                   (19)
#define DC_MEM_PROTECT_CTRL_blk_protect_1_en_mask                                    (0x00080000)
#define DC_MEM_PROTECT_CTRL_blk_protect_1_en(data)                                   (0x00080000&((data)<<19))
#define DC_MEM_PROTECT_CTRL_blk_protect_1_en_src(data)                               ((0x00080000&(data))>>19)
#define DC_MEM_PROTECT_CTRL_get_blk_protect_1_en(data)                               ((0x00080000&(data))>>19)
#define DC_MEM_PROTECT_CTRL_blk_protect_0_en_shift                                   (18)
#define DC_MEM_PROTECT_CTRL_blk_protect_0_en_mask                                    (0x00040000)
#define DC_MEM_PROTECT_CTRL_blk_protect_0_en(data)                                   (0x00040000&((data)<<18))
#define DC_MEM_PROTECT_CTRL_blk_protect_0_en_src(data)                               ((0x00040000&(data))>>18)
#define DC_MEM_PROTECT_CTRL_get_blk_protect_0_en(data)                               ((0x00040000&(data))>>18)
#define DC_MEM_PROTECT_CTRL_write_enable3_shift                                      (17)
#define DC_MEM_PROTECT_CTRL_write_enable3_mask                                       (0x00020000)
#define DC_MEM_PROTECT_CTRL_write_enable3(data)                                      (0x00020000&((data)<<17))
#define DC_MEM_PROTECT_CTRL_write_enable3_src(data)                                  ((0x00020000&(data))>>17)
#define DC_MEM_PROTECT_CTRL_get_write_enable3(data)                                  ((0x00020000&(data))>>17)
#define DC_MEM_PROTECT_CTRL_protect_7_wpro_en_shift                                  (16)
#define DC_MEM_PROTECT_CTRL_protect_7_wpro_en_mask                                   (0x00010000)
#define DC_MEM_PROTECT_CTRL_protect_7_wpro_en(data)                                  (0x00010000&((data)<<16))
#define DC_MEM_PROTECT_CTRL_protect_7_wpro_en_src(data)                              ((0x00010000&(data))>>16)
#define DC_MEM_PROTECT_CTRL_get_protect_7_wpro_en(data)                              ((0x00010000&(data))>>16)
#define DC_MEM_PROTECT_CTRL_protect_6_wpro_en_shift                                  (15)
#define DC_MEM_PROTECT_CTRL_protect_6_wpro_en_mask                                   (0x00008000)
#define DC_MEM_PROTECT_CTRL_protect_6_wpro_en(data)                                  (0x00008000&((data)<<15))
#define DC_MEM_PROTECT_CTRL_protect_6_wpro_en_src(data)                              ((0x00008000&(data))>>15)
#define DC_MEM_PROTECT_CTRL_get_protect_6_wpro_en(data)                              ((0x00008000&(data))>>15)
#define DC_MEM_PROTECT_CTRL_protect_5_wpro_en_shift                                  (14)
#define DC_MEM_PROTECT_CTRL_protect_5_wpro_en_mask                                   (0x00004000)
#define DC_MEM_PROTECT_CTRL_protect_5_wpro_en(data)                                  (0x00004000&((data)<<14))
#define DC_MEM_PROTECT_CTRL_protect_5_wpro_en_src(data)                              ((0x00004000&(data))>>14)
#define DC_MEM_PROTECT_CTRL_get_protect_5_wpro_en(data)                              ((0x00004000&(data))>>14)
#define DC_MEM_PROTECT_CTRL_protect_4_wpro_en_shift                                  (13)
#define DC_MEM_PROTECT_CTRL_protect_4_wpro_en_mask                                   (0x00002000)
#define DC_MEM_PROTECT_CTRL_protect_4_wpro_en(data)                                  (0x00002000&((data)<<13))
#define DC_MEM_PROTECT_CTRL_protect_4_wpro_en_src(data)                              ((0x00002000&(data))>>13)
#define DC_MEM_PROTECT_CTRL_get_protect_4_wpro_en(data)                              ((0x00002000&(data))>>13)
#define DC_MEM_PROTECT_CTRL_protect_3_wpro_en_shift                                  (12)
#define DC_MEM_PROTECT_CTRL_protect_3_wpro_en_mask                                   (0x00001000)
#define DC_MEM_PROTECT_CTRL_protect_3_wpro_en(data)                                  (0x00001000&((data)<<12))
#define DC_MEM_PROTECT_CTRL_protect_3_wpro_en_src(data)                              ((0x00001000&(data))>>12)
#define DC_MEM_PROTECT_CTRL_get_protect_3_wpro_en(data)                              ((0x00001000&(data))>>12)
#define DC_MEM_PROTECT_CTRL_protect_2_wpro_en_shift                                  (11)
#define DC_MEM_PROTECT_CTRL_protect_2_wpro_en_mask                                   (0x00000800)
#define DC_MEM_PROTECT_CTRL_protect_2_wpro_en(data)                                  (0x00000800&((data)<<11))
#define DC_MEM_PROTECT_CTRL_protect_2_wpro_en_src(data)                              ((0x00000800&(data))>>11)
#define DC_MEM_PROTECT_CTRL_get_protect_2_wpro_en(data)                              ((0x00000800&(data))>>11)
#define DC_MEM_PROTECT_CTRL_protect_1_wpro_en_shift                                  (10)
#define DC_MEM_PROTECT_CTRL_protect_1_wpro_en_mask                                   (0x00000400)
#define DC_MEM_PROTECT_CTRL_protect_1_wpro_en(data)                                  (0x00000400&((data)<<10))
#define DC_MEM_PROTECT_CTRL_protect_1_wpro_en_src(data)                              ((0x00000400&(data))>>10)
#define DC_MEM_PROTECT_CTRL_get_protect_1_wpro_en(data)                              ((0x00000400&(data))>>10)
#define DC_MEM_PROTECT_CTRL_protect_0_wpro_en_shift                                  (9)
#define DC_MEM_PROTECT_CTRL_protect_0_wpro_en_mask                                   (0x00000200)
#define DC_MEM_PROTECT_CTRL_protect_0_wpro_en(data)                                  (0x00000200&((data)<<9))
#define DC_MEM_PROTECT_CTRL_protect_0_wpro_en_src(data)                              ((0x00000200&(data))>>9)
#define DC_MEM_PROTECT_CTRL_get_protect_0_wpro_en(data)                              ((0x00000200&(data))>>9)
#define DC_MEM_PROTECT_CTRL_write_enable4_shift                                      (8)
#define DC_MEM_PROTECT_CTRL_write_enable4_mask                                       (0x00000100)
#define DC_MEM_PROTECT_CTRL_write_enable4(data)                                      (0x00000100&((data)<<8))
#define DC_MEM_PROTECT_CTRL_write_enable4_src(data)                                  ((0x00000100&(data))>>8)
#define DC_MEM_PROTECT_CTRL_get_write_enable4(data)                                  ((0x00000100&(data))>>8)
#define DC_MEM_PROTECT_CTRL_protect_7_en_shift                                       (7)
#define DC_MEM_PROTECT_CTRL_protect_7_en_mask                                        (0x00000080)
#define DC_MEM_PROTECT_CTRL_protect_7_en(data)                                       (0x00000080&((data)<<7))
#define DC_MEM_PROTECT_CTRL_protect_7_en_src(data)                                   ((0x00000080&(data))>>7)
#define DC_MEM_PROTECT_CTRL_get_protect_7_en(data)                                   ((0x00000080&(data))>>7)
#define DC_MEM_PROTECT_CTRL_protect_6_en_shift                                       (6)
#define DC_MEM_PROTECT_CTRL_protect_6_en_mask                                        (0x00000040)
#define DC_MEM_PROTECT_CTRL_protect_6_en(data)                                       (0x00000040&((data)<<6))
#define DC_MEM_PROTECT_CTRL_protect_6_en_src(data)                                   ((0x00000040&(data))>>6)
#define DC_MEM_PROTECT_CTRL_get_protect_6_en(data)                                   ((0x00000040&(data))>>6)
#define DC_MEM_PROTECT_CTRL_protect_5_en_shift                                       (5)
#define DC_MEM_PROTECT_CTRL_protect_5_en_mask                                        (0x00000020)
#define DC_MEM_PROTECT_CTRL_protect_5_en(data)                                       (0x00000020&((data)<<5))
#define DC_MEM_PROTECT_CTRL_protect_5_en_src(data)                                   ((0x00000020&(data))>>5)
#define DC_MEM_PROTECT_CTRL_get_protect_5_en(data)                                   ((0x00000020&(data))>>5)
#define DC_MEM_PROTECT_CTRL_protect_4_en_shift                                       (4)
#define DC_MEM_PROTECT_CTRL_protect_4_en_mask                                        (0x00000010)
#define DC_MEM_PROTECT_CTRL_protect_4_en(data)                                       (0x00000010&((data)<<4))
#define DC_MEM_PROTECT_CTRL_protect_4_en_src(data)                                   ((0x00000010&(data))>>4)
#define DC_MEM_PROTECT_CTRL_get_protect_4_en(data)                                   ((0x00000010&(data))>>4)
#define DC_MEM_PROTECT_CTRL_protect_3_en_shift                                       (3)
#define DC_MEM_PROTECT_CTRL_protect_3_en_mask                                        (0x00000008)
#define DC_MEM_PROTECT_CTRL_protect_3_en(data)                                       (0x00000008&((data)<<3))
#define DC_MEM_PROTECT_CTRL_protect_3_en_src(data)                                   ((0x00000008&(data))>>3)
#define DC_MEM_PROTECT_CTRL_get_protect_3_en(data)                                   ((0x00000008&(data))>>3)
#define DC_MEM_PROTECT_CTRL_protect_2_en_shift                                       (2)
#define DC_MEM_PROTECT_CTRL_protect_2_en_mask                                        (0x00000004)
#define DC_MEM_PROTECT_CTRL_protect_2_en(data)                                       (0x00000004&((data)<<2))
#define DC_MEM_PROTECT_CTRL_protect_2_en_src(data)                                   ((0x00000004&(data))>>2)
#define DC_MEM_PROTECT_CTRL_get_protect_2_en(data)                                   ((0x00000004&(data))>>2)
#define DC_MEM_PROTECT_CTRL_protect_1_en_shift                                       (1)
#define DC_MEM_PROTECT_CTRL_protect_1_en_mask                                        (0x00000002)
#define DC_MEM_PROTECT_CTRL_protect_1_en(data)                                       (0x00000002&((data)<<1))
#define DC_MEM_PROTECT_CTRL_protect_1_en_src(data)                                   ((0x00000002&(data))>>1)
#define DC_MEM_PROTECT_CTRL_get_protect_1_en(data)                                   ((0x00000002&(data))>>1)
#define DC_MEM_PROTECT_CTRL_protect_0_en_shift                                       (0)
#define DC_MEM_PROTECT_CTRL_protect_0_en_mask                                        (0x00000001)
#define DC_MEM_PROTECT_CTRL_protect_0_en(data)                                       (0x00000001&((data)<<0))
#define DC_MEM_PROTECT_CTRL_protect_0_en_src(data)                                   ((0x00000001&(data))>>0)
#define DC_MEM_PROTECT_CTRL_get_protect_0_en(data)                                   ((0x00000001&(data))>>0)


#define DC_MEM_SCRAMBLE_CTRL                                                         0x18008404
#define DC_MEM_SCRAMBLE_CTRL_reg_addr                                                "0xB8008404"
#define DC_MEM_SCRAMBLE_CTRL_reg                                                     0xB8008404
#define set_DC_MEM_SCRAMBLE_CTRL_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_CTRL_reg)=data)
#define get_DC_MEM_SCRAMBLE_CTRL_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_CTRL_reg))
#define DC_MEM_SCRAMBLE_CTRL_inst_adr                                                "0x0001"
#define DC_MEM_SCRAMBLE_CTRL_inst                                                    0x0001
#define DC_MEM_SCRAMBLE_CTRL_y_limit_shift                                           (14)
#define DC_MEM_SCRAMBLE_CTRL_y_limit_mask                                            (0x00004000)
#define DC_MEM_SCRAMBLE_CTRL_y_limit(data)                                           (0x00004000&((data)<<14))
#define DC_MEM_SCRAMBLE_CTRL_y_limit_src(data)                                       ((0x00004000&(data))>>14)
#define DC_MEM_SCRAMBLE_CTRL_get_y_limit(data)                                       ((0x00004000&(data))>>14)
#define DC_MEM_SCRAMBLE_CTRL_bank_remap_enable_shift                                 (13)
#define DC_MEM_SCRAMBLE_CTRL_bank_remap_enable_mask                                  (0x00002000)
#define DC_MEM_SCRAMBLE_CTRL_bank_remap_enable(data)                                 (0x00002000&((data)<<13))
#define DC_MEM_SCRAMBLE_CTRL_bank_remap_enable_src(data)                             ((0x00002000&(data))>>13)
#define DC_MEM_SCRAMBLE_CTRL_get_bank_remap_enable(data)                             ((0x00002000&(data))>>13)
#define DC_MEM_SCRAMBLE_CTRL_tp_scramble_en_shift                                    (12)
#define DC_MEM_SCRAMBLE_CTRL_tp_scramble_en_mask                                     (0x00001000)
#define DC_MEM_SCRAMBLE_CTRL_tp_scramble_en(data)                                    (0x00001000&((data)<<12))
#define DC_MEM_SCRAMBLE_CTRL_tp_scramble_en_src(data)                                ((0x00001000&(data))>>12)
#define DC_MEM_SCRAMBLE_CTRL_get_tp_scramble_en(data)                                ((0x00001000&(data))>>12)
#define DC_MEM_SCRAMBLE_CTRL_video_dec_scramble_en_shift                             (11)
#define DC_MEM_SCRAMBLE_CTRL_video_dec_scramble_en_mask                              (0x00000800)
#define DC_MEM_SCRAMBLE_CTRL_video_dec_scramble_en(data)                             (0x00000800&((data)<<11))
#define DC_MEM_SCRAMBLE_CTRL_video_dec_scramble_en_src(data)                         ((0x00000800&(data))>>11)
#define DC_MEM_SCRAMBLE_CTRL_get_video_dec_scramble_en(data)                         ((0x00000800&(data))>>11)
#define DC_MEM_SCRAMBLE_CTRL_audio_scramble_en_shift                                 (10)
#define DC_MEM_SCRAMBLE_CTRL_audio_scramble_en_mask                                  (0x00000400)
#define DC_MEM_SCRAMBLE_CTRL_audio_scramble_en(data)                                 (0x00000400&((data)<<10))
#define DC_MEM_SCRAMBLE_CTRL_audio_scramble_en_src(data)                             ((0x00000400&(data))>>10)
#define DC_MEM_SCRAMBLE_CTRL_get_audio_scramble_en(data)                             ((0x00000400&(data))>>10)
#define DC_MEM_SCRAMBLE_CTRL_scpu_scramble_en_shift                                  (9)
#define DC_MEM_SCRAMBLE_CTRL_scpu_scramble_en_mask                                   (0x00000200)
#define DC_MEM_SCRAMBLE_CTRL_scpu_scramble_en(data)                                  (0x00000200&((data)<<9))
#define DC_MEM_SCRAMBLE_CTRL_scpu_scramble_en_src(data)                              ((0x00000200&(data))>>9)
#define DC_MEM_SCRAMBLE_CTRL_get_scpu_scramble_en(data)                              ((0x00000200&(data))>>9)
#define DC_MEM_SCRAMBLE_CTRL_scramble_all_en_shift                                   (8)
#define DC_MEM_SCRAMBLE_CTRL_scramble_all_en_mask                                    (0x00000100)
#define DC_MEM_SCRAMBLE_CTRL_scramble_all_en(data)                                   (0x00000100&((data)<<8))
#define DC_MEM_SCRAMBLE_CTRL_scramble_all_en_src(data)                               ((0x00000100&(data))>>8)
#define DC_MEM_SCRAMBLE_CTRL_get_scramble_all_en(data)                               ((0x00000100&(data))>>8)
#define DC_MEM_SCRAMBLE_CTRL_scramble_7_en_shift                                     (7)
#define DC_MEM_SCRAMBLE_CTRL_scramble_7_en_mask                                      (0x00000080)
#define DC_MEM_SCRAMBLE_CTRL_scramble_7_en(data)                                     (0x00000080&((data)<<7))
#define DC_MEM_SCRAMBLE_CTRL_scramble_7_en_src(data)                                 ((0x00000080&(data))>>7)
#define DC_MEM_SCRAMBLE_CTRL_get_scramble_7_en(data)                                 ((0x00000080&(data))>>7)
#define DC_MEM_SCRAMBLE_CTRL_scramble_6_en_shift                                     (6)
#define DC_MEM_SCRAMBLE_CTRL_scramble_6_en_mask                                      (0x00000040)
#define DC_MEM_SCRAMBLE_CTRL_scramble_6_en(data)                                     (0x00000040&((data)<<6))
#define DC_MEM_SCRAMBLE_CTRL_scramble_6_en_src(data)                                 ((0x00000040&(data))>>6)
#define DC_MEM_SCRAMBLE_CTRL_get_scramble_6_en(data)                                 ((0x00000040&(data))>>6)
#define DC_MEM_SCRAMBLE_CTRL_scramble_5_en_shift                                     (5)
#define DC_MEM_SCRAMBLE_CTRL_scramble_5_en_mask                                      (0x00000020)
#define DC_MEM_SCRAMBLE_CTRL_scramble_5_en(data)                                     (0x00000020&((data)<<5))
#define DC_MEM_SCRAMBLE_CTRL_scramble_5_en_src(data)                                 ((0x00000020&(data))>>5)
#define DC_MEM_SCRAMBLE_CTRL_get_scramble_5_en(data)                                 ((0x00000020&(data))>>5)
#define DC_MEM_SCRAMBLE_CTRL_scramble_4_en_shift                                     (4)
#define DC_MEM_SCRAMBLE_CTRL_scramble_4_en_mask                                      (0x00000010)
#define DC_MEM_SCRAMBLE_CTRL_scramble_4_en(data)                                     (0x00000010&((data)<<4))
#define DC_MEM_SCRAMBLE_CTRL_scramble_4_en_src(data)                                 ((0x00000010&(data))>>4)
#define DC_MEM_SCRAMBLE_CTRL_get_scramble_4_en(data)                                 ((0x00000010&(data))>>4)
#define DC_MEM_SCRAMBLE_CTRL_scramble_3_en_shift                                     (3)
#define DC_MEM_SCRAMBLE_CTRL_scramble_3_en_mask                                      (0x00000008)
#define DC_MEM_SCRAMBLE_CTRL_scramble_3_en(data)                                     (0x00000008&((data)<<3))
#define DC_MEM_SCRAMBLE_CTRL_scramble_3_en_src(data)                                 ((0x00000008&(data))>>3)
#define DC_MEM_SCRAMBLE_CTRL_get_scramble_3_en(data)                                 ((0x00000008&(data))>>3)
#define DC_MEM_SCRAMBLE_CTRL_scramble_2_en_shift                                     (2)
#define DC_MEM_SCRAMBLE_CTRL_scramble_2_en_mask                                      (0x00000004)
#define DC_MEM_SCRAMBLE_CTRL_scramble_2_en(data)                                     (0x00000004&((data)<<2))
#define DC_MEM_SCRAMBLE_CTRL_scramble_2_en_src(data)                                 ((0x00000004&(data))>>2)
#define DC_MEM_SCRAMBLE_CTRL_get_scramble_2_en(data)                                 ((0x00000004&(data))>>2)
#define DC_MEM_SCRAMBLE_CTRL_scramble_1_en_shift                                     (1)
#define DC_MEM_SCRAMBLE_CTRL_scramble_1_en_mask                                      (0x00000002)
#define DC_MEM_SCRAMBLE_CTRL_scramble_1_en(data)                                     (0x00000002&((data)<<1))
#define DC_MEM_SCRAMBLE_CTRL_scramble_1_en_src(data)                                 ((0x00000002&(data))>>1)
#define DC_MEM_SCRAMBLE_CTRL_get_scramble_1_en(data)                                 ((0x00000002&(data))>>1)
#define DC_MEM_SCRAMBLE_CTRL_scramble_0_en_shift                                     (0)
#define DC_MEM_SCRAMBLE_CTRL_scramble_0_en_mask                                      (0x00000001)
#define DC_MEM_SCRAMBLE_CTRL_scramble_0_en(data)                                     (0x00000001&((data)<<0))
#define DC_MEM_SCRAMBLE_CTRL_scramble_0_en_src(data)                                 ((0x00000001&(data))>>0)
#define DC_MEM_SCRAMBLE_CTRL_get_scramble_0_en(data)                                 ((0x00000001&(data))>>0)


#define DC_MEM_PROTECT_SADDR0                                                        0x18008408
#define DC_MEM_PROTECT_SADDR0_reg_addr                                               "0xB8008408"
#define DC_MEM_PROTECT_SADDR0_reg                                                    0xB8008408
#define set_DC_MEM_PROTECT_SADDR0_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR0_reg)=data)
#define get_DC_MEM_PROTECT_SADDR0_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR0_reg))
#define DC_MEM_PROTECT_SADDR0_inst_adr                                               "0x0002"
#define DC_MEM_PROTECT_SADDR0_inst                                                   0x0002
#define DC_MEM_PROTECT_SADDR0_saddr0_shift                                           (12)
#define DC_MEM_PROTECT_SADDR0_saddr0_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_SADDR0_saddr0(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_SADDR0_saddr0_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_SADDR0_get_saddr0(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_EADDR0                                                        0x1800840C
#define DC_MEM_PROTECT_EADDR0_reg_addr                                               "0xB800840C"
#define DC_MEM_PROTECT_EADDR0_reg                                                    0xB800840C
#define set_DC_MEM_PROTECT_EADDR0_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR0_reg)=data)
#define get_DC_MEM_PROTECT_EADDR0_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR0_reg))
#define DC_MEM_PROTECT_EADDR0_inst_adr                                               "0x0003"
#define DC_MEM_PROTECT_EADDR0_inst                                                   0x0003
#define DC_MEM_PROTECT_EADDR0_eaddr0_shift                                           (12)
#define DC_MEM_PROTECT_EADDR0_eaddr0_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_EADDR0_eaddr0(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_EADDR0_eaddr0_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_EADDR0_get_eaddr0(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_SADDR1                                                        0x18008410
#define DC_MEM_PROTECT_SADDR1_reg_addr                                               "0xB8008410"
#define DC_MEM_PROTECT_SADDR1_reg                                                    0xB8008410
#define set_DC_MEM_PROTECT_SADDR1_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR1_reg)=data)
#define get_DC_MEM_PROTECT_SADDR1_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR1_reg))
#define DC_MEM_PROTECT_SADDR1_inst_adr                                               "0x0004"
#define DC_MEM_PROTECT_SADDR1_inst                                                   0x0004
#define DC_MEM_PROTECT_SADDR1_saddr1_shift                                           (12)
#define DC_MEM_PROTECT_SADDR1_saddr1_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_SADDR1_saddr1(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_SADDR1_saddr1_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_SADDR1_get_saddr1(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_EADDR1                                                        0x18008414
#define DC_MEM_PROTECT_EADDR1_reg_addr                                               "0xB8008414"
#define DC_MEM_PROTECT_EADDR1_reg                                                    0xB8008414
#define set_DC_MEM_PROTECT_EADDR1_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR1_reg)=data)
#define get_DC_MEM_PROTECT_EADDR1_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR1_reg))
#define DC_MEM_PROTECT_EADDR1_inst_adr                                               "0x0005"
#define DC_MEM_PROTECT_EADDR1_inst                                                   0x0005
#define DC_MEM_PROTECT_EADDR1_eaddr1_shift                                           (12)
#define DC_MEM_PROTECT_EADDR1_eaddr1_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_EADDR1_eaddr1(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_EADDR1_eaddr1_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_EADDR1_get_eaddr1(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_SADDR2                                                        0x18008418
#define DC_MEM_PROTECT_SADDR2_reg_addr                                               "0xB8008418"
#define DC_MEM_PROTECT_SADDR2_reg                                                    0xB8008418
#define set_DC_MEM_PROTECT_SADDR2_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR2_reg)=data)
#define get_DC_MEM_PROTECT_SADDR2_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR2_reg))
#define DC_MEM_PROTECT_SADDR2_inst_adr                                               "0x0006"
#define DC_MEM_PROTECT_SADDR2_inst                                                   0x0006
#define DC_MEM_PROTECT_SADDR2_saddr2_shift                                           (12)
#define DC_MEM_PROTECT_SADDR2_saddr2_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_SADDR2_saddr2(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_SADDR2_saddr2_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_SADDR2_get_saddr2(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_EADDR2                                                        0x1800841C
#define DC_MEM_PROTECT_EADDR2_reg_addr                                               "0xB800841C"
#define DC_MEM_PROTECT_EADDR2_reg                                                    0xB800841C
#define set_DC_MEM_PROTECT_EADDR2_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR2_reg)=data)
#define get_DC_MEM_PROTECT_EADDR2_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR2_reg))
#define DC_MEM_PROTECT_EADDR2_inst_adr                                               "0x0007"
#define DC_MEM_PROTECT_EADDR2_inst                                                   0x0007
#define DC_MEM_PROTECT_EADDR2_eaddr2_shift                                           (12)
#define DC_MEM_PROTECT_EADDR2_eaddr2_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_EADDR2_eaddr2(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_EADDR2_eaddr2_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_EADDR2_get_eaddr2(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_SADDR3                                                        0x18008420
#define DC_MEM_PROTECT_SADDR3_reg_addr                                               "0xB8008420"
#define DC_MEM_PROTECT_SADDR3_reg                                                    0xB8008420
#define set_DC_MEM_PROTECT_SADDR3_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR3_reg)=data)
#define get_DC_MEM_PROTECT_SADDR3_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR3_reg))
#define DC_MEM_PROTECT_SADDR3_inst_adr                                               "0x0008"
#define DC_MEM_PROTECT_SADDR3_inst                                                   0x0008
#define DC_MEM_PROTECT_SADDR3_saddr3_shift                                           (12)
#define DC_MEM_PROTECT_SADDR3_saddr3_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_SADDR3_saddr3(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_SADDR3_saddr3_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_SADDR3_get_saddr3(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_EADDR3                                                        0x18008424
#define DC_MEM_PROTECT_EADDR3_reg_addr                                               "0xB8008424"
#define DC_MEM_PROTECT_EADDR3_reg                                                    0xB8008424
#define set_DC_MEM_PROTECT_EADDR3_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR3_reg)=data)
#define get_DC_MEM_PROTECT_EADDR3_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR3_reg))
#define DC_MEM_PROTECT_EADDR3_inst_adr                                               "0x0009"
#define DC_MEM_PROTECT_EADDR3_inst                                                   0x0009
#define DC_MEM_PROTECT_EADDR3_eaddr3_shift                                           (12)
#define DC_MEM_PROTECT_EADDR3_eaddr3_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_EADDR3_eaddr3(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_EADDR3_eaddr3_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_EADDR3_get_eaddr3(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_SADDR4                                                        0x18008428
#define DC_MEM_PROTECT_SADDR4_reg_addr                                               "0xB8008428"
#define DC_MEM_PROTECT_SADDR4_reg                                                    0xB8008428
#define set_DC_MEM_PROTECT_SADDR4_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR4_reg)=data)
#define get_DC_MEM_PROTECT_SADDR4_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR4_reg))
#define DC_MEM_PROTECT_SADDR4_inst_adr                                               "0x000A"
#define DC_MEM_PROTECT_SADDR4_inst                                                   0x000A
#define DC_MEM_PROTECT_SADDR4_saddr4_shift                                           (12)
#define DC_MEM_PROTECT_SADDR4_saddr4_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_SADDR4_saddr4(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_SADDR4_saddr4_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_SADDR4_get_saddr4(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_EADDR4                                                        0x1800842C
#define DC_MEM_PROTECT_EADDR4_reg_addr                                               "0xB800842C"
#define DC_MEM_PROTECT_EADDR4_reg                                                    0xB800842C
#define set_DC_MEM_PROTECT_EADDR4_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR4_reg)=data)
#define get_DC_MEM_PROTECT_EADDR4_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR4_reg))
#define DC_MEM_PROTECT_EADDR4_inst_adr                                               "0x000B"
#define DC_MEM_PROTECT_EADDR4_inst                                                   0x000B
#define DC_MEM_PROTECT_EADDR4_eaddr4_shift                                           (12)
#define DC_MEM_PROTECT_EADDR4_eaddr4_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_EADDR4_eaddr4(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_EADDR4_eaddr4_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_EADDR4_get_eaddr4(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_SADDR5                                                        0x18008430
#define DC_MEM_PROTECT_SADDR5_reg_addr                                               "0xB8008430"
#define DC_MEM_PROTECT_SADDR5_reg                                                    0xB8008430
#define set_DC_MEM_PROTECT_SADDR5_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR5_reg)=data)
#define get_DC_MEM_PROTECT_SADDR5_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR5_reg))
#define DC_MEM_PROTECT_SADDR5_inst_adr                                               "0x000C"
#define DC_MEM_PROTECT_SADDR5_inst                                                   0x000C
#define DC_MEM_PROTECT_SADDR5_saddr5_shift                                           (12)
#define DC_MEM_PROTECT_SADDR5_saddr5_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_SADDR5_saddr5(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_SADDR5_saddr5_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_SADDR5_get_saddr5(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_EADDR5                                                        0x18008434
#define DC_MEM_PROTECT_EADDR5_reg_addr                                               "0xB8008434"
#define DC_MEM_PROTECT_EADDR5_reg                                                    0xB8008434
#define set_DC_MEM_PROTECT_EADDR5_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR5_reg)=data)
#define get_DC_MEM_PROTECT_EADDR5_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR5_reg))
#define DC_MEM_PROTECT_EADDR5_inst_adr                                               "0x000D"
#define DC_MEM_PROTECT_EADDR5_inst                                                   0x000D
#define DC_MEM_PROTECT_EADDR5_eaddr5_shift                                           (12)
#define DC_MEM_PROTECT_EADDR5_eaddr5_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_EADDR5_eaddr5(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_EADDR5_eaddr5_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_EADDR5_get_eaddr5(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_SADDR6                                                        0x18008438
#define DC_MEM_PROTECT_SADDR6_reg_addr                                               "0xB8008438"
#define DC_MEM_PROTECT_SADDR6_reg                                                    0xB8008438
#define set_DC_MEM_PROTECT_SADDR6_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR6_reg)=data)
#define get_DC_MEM_PROTECT_SADDR6_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR6_reg))
#define DC_MEM_PROTECT_SADDR6_inst_adr                                               "0x000E"
#define DC_MEM_PROTECT_SADDR6_inst                                                   0x000E
#define DC_MEM_PROTECT_SADDR6_saddr6_shift                                           (12)
#define DC_MEM_PROTECT_SADDR6_saddr6_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_SADDR6_saddr6(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_SADDR6_saddr6_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_SADDR6_get_saddr6(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_EADDR6                                                        0x1800843C
#define DC_MEM_PROTECT_EADDR6_reg_addr                                               "0xB800843C"
#define DC_MEM_PROTECT_EADDR6_reg                                                    0xB800843C
#define set_DC_MEM_PROTECT_EADDR6_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR6_reg)=data)
#define get_DC_MEM_PROTECT_EADDR6_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR6_reg))
#define DC_MEM_PROTECT_EADDR6_inst_adr                                               "0x000F"
#define DC_MEM_PROTECT_EADDR6_inst                                                   0x000F
#define DC_MEM_PROTECT_EADDR6_eaddr6_shift                                           (12)
#define DC_MEM_PROTECT_EADDR6_eaddr6_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_EADDR6_eaddr6(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_EADDR6_eaddr6_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_EADDR6_get_eaddr6(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_SADDR7                                                        0x18008440
#define DC_MEM_PROTECT_SADDR7_reg_addr                                               "0xB8008440"
#define DC_MEM_PROTECT_SADDR7_reg                                                    0xB8008440
#define set_DC_MEM_PROTECT_SADDR7_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR7_reg)=data)
#define get_DC_MEM_PROTECT_SADDR7_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_SADDR7_reg))
#define DC_MEM_PROTECT_SADDR7_inst_adr                                               "0x0010"
#define DC_MEM_PROTECT_SADDR7_inst                                                   0x0010
#define DC_MEM_PROTECT_SADDR7_saddr7_shift                                           (12)
#define DC_MEM_PROTECT_SADDR7_saddr7_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_SADDR7_saddr7(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_SADDR7_saddr7_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_SADDR7_get_saddr7(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_EADDR7                                                        0x18008444
#define DC_MEM_PROTECT_EADDR7_reg_addr                                               "0xB8008444"
#define DC_MEM_PROTECT_EADDR7_reg                                                    0xB8008444
#define set_DC_MEM_PROTECT_EADDR7_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR7_reg)=data)
#define get_DC_MEM_PROTECT_EADDR7_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_EADDR7_reg))
#define DC_MEM_PROTECT_EADDR7_inst_adr                                               "0x0011"
#define DC_MEM_PROTECT_EADDR7_inst                                                   0x0011
#define DC_MEM_PROTECT_EADDR7_eaddr7_shift                                           (12)
#define DC_MEM_PROTECT_EADDR7_eaddr7_mask                                            (0xFFFFF000)
#define DC_MEM_PROTECT_EADDR7_eaddr7(data)                                           (0xFFFFF000&((data)<<12))
#define DC_MEM_PROTECT_EADDR7_eaddr7_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_MEM_PROTECT_EADDR7_get_eaddr7(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_BLK_PROTECT_SADDR0                                                        0x18008448
#define DC_BLK_PROTECT_SADDR0_reg_addr                                               "0xB8008448"
#define DC_BLK_PROTECT_SADDR0_reg                                                    0xB8008448
#define set_DC_BLK_PROTECT_SADDR0_reg(data)   (*((volatile unsigned int*) DC_BLK_PROTECT_SADDR0_reg)=data)
#define get_DC_BLK_PROTECT_SADDR0_reg   (*((volatile unsigned int*) DC_BLK_PROTECT_SADDR0_reg))
#define DC_BLK_PROTECT_SADDR0_inst_adr                                               "0x0012"
#define DC_BLK_PROTECT_SADDR0_inst                                                   0x0012
#define DC_BLK_PROTECT_SADDR0_saddr0_shift                                           (12)
#define DC_BLK_PROTECT_SADDR0_saddr0_mask                                            (0xFFFFF000)
#define DC_BLK_PROTECT_SADDR0_saddr0(data)                                           (0xFFFFF000&((data)<<12))
#define DC_BLK_PROTECT_SADDR0_saddr0_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_BLK_PROTECT_SADDR0_get_saddr0(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_BLK_PROTECT_EADDR0                                                        0x1800844C
#define DC_BLK_PROTECT_EADDR0_reg_addr                                               "0xB800844C"
#define DC_BLK_PROTECT_EADDR0_reg                                                    0xB800844C
#define set_DC_BLK_PROTECT_EADDR0_reg(data)   (*((volatile unsigned int*) DC_BLK_PROTECT_EADDR0_reg)=data)
#define get_DC_BLK_PROTECT_EADDR0_reg   (*((volatile unsigned int*) DC_BLK_PROTECT_EADDR0_reg))
#define DC_BLK_PROTECT_EADDR0_inst_adr                                               "0x0013"
#define DC_BLK_PROTECT_EADDR0_inst                                                   0x0013
#define DC_BLK_PROTECT_EADDR0_eaddr0_shift                                           (12)
#define DC_BLK_PROTECT_EADDR0_eaddr0_mask                                            (0xFFFFF000)
#define DC_BLK_PROTECT_EADDR0_eaddr0(data)                                           (0xFFFFF000&((data)<<12))
#define DC_BLK_PROTECT_EADDR0_eaddr0_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_BLK_PROTECT_EADDR0_get_eaddr0(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_BLK_PROTECT_SADDR1                                                        0x18008450
#define DC_BLK_PROTECT_SADDR1_reg_addr                                               "0xB8008450"
#define DC_BLK_PROTECT_SADDR1_reg                                                    0xB8008450
#define set_DC_BLK_PROTECT_SADDR1_reg(data)   (*((volatile unsigned int*) DC_BLK_PROTECT_SADDR1_reg)=data)
#define get_DC_BLK_PROTECT_SADDR1_reg   (*((volatile unsigned int*) DC_BLK_PROTECT_SADDR1_reg))
#define DC_BLK_PROTECT_SADDR1_inst_adr                                               "0x0014"
#define DC_BLK_PROTECT_SADDR1_inst                                                   0x0014
#define DC_BLK_PROTECT_SADDR1_saddr1_shift                                           (12)
#define DC_BLK_PROTECT_SADDR1_saddr1_mask                                            (0xFFFFF000)
#define DC_BLK_PROTECT_SADDR1_saddr1(data)                                           (0xFFFFF000&((data)<<12))
#define DC_BLK_PROTECT_SADDR1_saddr1_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_BLK_PROTECT_SADDR1_get_saddr1(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_BLK_PROTECT_EADDR1                                                        0x18008454
#define DC_BLK_PROTECT_EADDR1_reg_addr                                               "0xB8008454"
#define DC_BLK_PROTECT_EADDR1_reg                                                    0xB8008454
#define set_DC_BLK_PROTECT_EADDR1_reg(data)   (*((volatile unsigned int*) DC_BLK_PROTECT_EADDR1_reg)=data)
#define get_DC_BLK_PROTECT_EADDR1_reg   (*((volatile unsigned int*) DC_BLK_PROTECT_EADDR1_reg))
#define DC_BLK_PROTECT_EADDR1_inst_adr                                               "0x0015"
#define DC_BLK_PROTECT_EADDR1_inst                                                   0x0015
#define DC_BLK_PROTECT_EADDR1_eaddr1_shift                                           (12)
#define DC_BLK_PROTECT_EADDR1_eaddr1_mask                                            (0xFFFFF000)
#define DC_BLK_PROTECT_EADDR1_eaddr1(data)                                           (0xFFFFF000&((data)<<12))
#define DC_BLK_PROTECT_EADDR1_eaddr1_src(data)                                       ((0xFFFFF000&(data))>>12)
#define DC_BLK_PROTECT_EADDR1_get_eaddr1(data)                                       ((0xFFFFF000&(data))>>12)


#define DC_RO_PROTECT_SADDR0                                                         0x18008458
#define DC_RO_PROTECT_SADDR0_reg_addr                                                "0xB8008458"
#define DC_RO_PROTECT_SADDR0_reg                                                     0xB8008458
#define set_DC_RO_PROTECT_SADDR0_reg(data)   (*((volatile unsigned int*) DC_RO_PROTECT_SADDR0_reg)=data)
#define get_DC_RO_PROTECT_SADDR0_reg   (*((volatile unsigned int*) DC_RO_PROTECT_SADDR0_reg))
#define DC_RO_PROTECT_SADDR0_inst_adr                                                "0x0016"
#define DC_RO_PROTECT_SADDR0_inst                                                    0x0016
#define DC_RO_PROTECT_SADDR0_saddr0_shift                                            (12)
#define DC_RO_PROTECT_SADDR0_saddr0_mask                                             (0xFFFFF000)
#define DC_RO_PROTECT_SADDR0_saddr0(data)                                            (0xFFFFF000&((data)<<12))
#define DC_RO_PROTECT_SADDR0_saddr0_src(data)                                        ((0xFFFFF000&(data))>>12)
#define DC_RO_PROTECT_SADDR0_get_saddr0(data)                                        ((0xFFFFF000&(data))>>12)


#define DC_RO_PROTECT_EADDR0                                                         0x1800845C
#define DC_RO_PROTECT_EADDR0_reg_addr                                                "0xB800845C"
#define DC_RO_PROTECT_EADDR0_reg                                                     0xB800845C
#define set_DC_RO_PROTECT_EADDR0_reg(data)   (*((volatile unsigned int*) DC_RO_PROTECT_EADDR0_reg)=data)
#define get_DC_RO_PROTECT_EADDR0_reg   (*((volatile unsigned int*) DC_RO_PROTECT_EADDR0_reg))
#define DC_RO_PROTECT_EADDR0_inst_adr                                                "0x0017"
#define DC_RO_PROTECT_EADDR0_inst                                                    0x0017
#define DC_RO_PROTECT_EADDR0_eaddr0_shift                                            (12)
#define DC_RO_PROTECT_EADDR0_eaddr0_mask                                             (0xFFFFF000)
#define DC_RO_PROTECT_EADDR0_eaddr0(data)                                            (0xFFFFF000&((data)<<12))
#define DC_RO_PROTECT_EADDR0_eaddr0_src(data)                                        ((0xFFFFF000&(data))>>12)
#define DC_RO_PROTECT_EADDR0_get_eaddr0(data)                                        ((0xFFFFF000&(data))>>12)


#define DC_RO_PROTECT_SADDR1                                                         0x18008460
#define DC_RO_PROTECT_SADDR1_reg_addr                                                "0xB8008460"
#define DC_RO_PROTECT_SADDR1_reg                                                     0xB8008460
#define set_DC_RO_PROTECT_SADDR1_reg(data)   (*((volatile unsigned int*) DC_RO_PROTECT_SADDR1_reg)=data)
#define get_DC_RO_PROTECT_SADDR1_reg   (*((volatile unsigned int*) DC_RO_PROTECT_SADDR1_reg))
#define DC_RO_PROTECT_SADDR1_inst_adr                                                "0x0018"
#define DC_RO_PROTECT_SADDR1_inst                                                    0x0018
#define DC_RO_PROTECT_SADDR1_saddr1_shift                                            (12)
#define DC_RO_PROTECT_SADDR1_saddr1_mask                                             (0xFFFFF000)
#define DC_RO_PROTECT_SADDR1_saddr1(data)                                            (0xFFFFF000&((data)<<12))
#define DC_RO_PROTECT_SADDR1_saddr1_src(data)                                        ((0xFFFFF000&(data))>>12)
#define DC_RO_PROTECT_SADDR1_get_saddr1(data)                                        ((0xFFFFF000&(data))>>12)


#define DC_RO_PROTECT_EADDR1                                                         0x18008464
#define DC_RO_PROTECT_EADDR1_reg_addr                                                "0xB8008464"
#define DC_RO_PROTECT_EADDR1_reg                                                     0xB8008464
#define set_DC_RO_PROTECT_EADDR1_reg(data)   (*((volatile unsigned int*) DC_RO_PROTECT_EADDR1_reg)=data)
#define get_DC_RO_PROTECT_EADDR1_reg   (*((volatile unsigned int*) DC_RO_PROTECT_EADDR1_reg))
#define DC_RO_PROTECT_EADDR1_inst_adr                                                "0x0019"
#define DC_RO_PROTECT_EADDR1_inst                                                    0x0019
#define DC_RO_PROTECT_EADDR1_eaddr1_shift                                            (12)
#define DC_RO_PROTECT_EADDR1_eaddr1_mask                                             (0xFFFFF000)
#define DC_RO_PROTECT_EADDR1_eaddr1(data)                                            (0xFFFFF000&((data)<<12))
#define DC_RO_PROTECT_EADDR1_eaddr1_src(data)                                        ((0xFFFFF000&(data))>>12)
#define DC_RO_PROTECT_EADDR1_get_eaddr1(data)                                        ((0xFFFFF000&(data))>>12)


#define DC_RO_PROTECT_SADDR2                                                         0x18008468
#define DC_RO_PROTECT_SADDR2_reg_addr                                                "0xB8008468"
#define DC_RO_PROTECT_SADDR2_reg                                                     0xB8008468
#define set_DC_RO_PROTECT_SADDR2_reg(data)   (*((volatile unsigned int*) DC_RO_PROTECT_SADDR2_reg)=data)
#define get_DC_RO_PROTECT_SADDR2_reg   (*((volatile unsigned int*) DC_RO_PROTECT_SADDR2_reg))
#define DC_RO_PROTECT_SADDR2_inst_adr                                                "0x001A"
#define DC_RO_PROTECT_SADDR2_inst                                                    0x001A
#define DC_RO_PROTECT_SADDR2_saddr2_shift                                            (12)
#define DC_RO_PROTECT_SADDR2_saddr2_mask                                             (0xFFFFF000)
#define DC_RO_PROTECT_SADDR2_saddr2(data)                                            (0xFFFFF000&((data)<<12))
#define DC_RO_PROTECT_SADDR2_saddr2_src(data)                                        ((0xFFFFF000&(data))>>12)
#define DC_RO_PROTECT_SADDR2_get_saddr2(data)                                        ((0xFFFFF000&(data))>>12)


#define DC_RO_PROTECT_EADDR2                                                         0x1800846C
#define DC_RO_PROTECT_EADDR2_reg_addr                                                "0xB800846C"
#define DC_RO_PROTECT_EADDR2_reg                                                     0xB800846C
#define set_DC_RO_PROTECT_EADDR2_reg(data)   (*((volatile unsigned int*) DC_RO_PROTECT_EADDR2_reg)=data)
#define get_DC_RO_PROTECT_EADDR2_reg   (*((volatile unsigned int*) DC_RO_PROTECT_EADDR2_reg))
#define DC_RO_PROTECT_EADDR2_inst_adr                                                "0x001B"
#define DC_RO_PROTECT_EADDR2_inst                                                    0x001B
#define DC_RO_PROTECT_EADDR2_eaddr2_shift                                            (12)
#define DC_RO_PROTECT_EADDR2_eaddr2_mask                                             (0xFFFFF000)
#define DC_RO_PROTECT_EADDR2_eaddr2(data)                                            (0xFFFFF000&((data)<<12))
#define DC_RO_PROTECT_EADDR2_eaddr2_src(data)                                        ((0xFFFFF000&(data))>>12)
#define DC_RO_PROTECT_EADDR2_get_eaddr2(data)                                        ((0xFFFFF000&(data))>>12)


#define DC_RO_PROTECT_SADDR3                                                         0x18008470
#define DC_RO_PROTECT_SADDR3_reg_addr                                                "0xB8008470"
#define DC_RO_PROTECT_SADDR3_reg                                                     0xB8008470
#define set_DC_RO_PROTECT_SADDR3_reg(data)   (*((volatile unsigned int*) DC_RO_PROTECT_SADDR3_reg)=data)
#define get_DC_RO_PROTECT_SADDR3_reg   (*((volatile unsigned int*) DC_RO_PROTECT_SADDR3_reg))
#define DC_RO_PROTECT_SADDR3_inst_adr                                                "0x001C"
#define DC_RO_PROTECT_SADDR3_inst                                                    0x001C
#define DC_RO_PROTECT_SADDR3_saddr3_shift                                            (12)
#define DC_RO_PROTECT_SADDR3_saddr3_mask                                             (0xFFFFF000)
#define DC_RO_PROTECT_SADDR3_saddr3(data)                                            (0xFFFFF000&((data)<<12))
#define DC_RO_PROTECT_SADDR3_saddr3_src(data)                                        ((0xFFFFF000&(data))>>12)
#define DC_RO_PROTECT_SADDR3_get_saddr3(data)                                        ((0xFFFFF000&(data))>>12)


#define DC_RO_PROTECT_EADDR3                                                         0x18008474
#define DC_RO_PROTECT_EADDR3_reg_addr                                                "0xB8008474"
#define DC_RO_PROTECT_EADDR3_reg                                                     0xB8008474
#define set_DC_RO_PROTECT_EADDR3_reg(data)   (*((volatile unsigned int*) DC_RO_PROTECT_EADDR3_reg)=data)
#define get_DC_RO_PROTECT_EADDR3_reg   (*((volatile unsigned int*) DC_RO_PROTECT_EADDR3_reg))
#define DC_RO_PROTECT_EADDR3_inst_adr                                                "0x001D"
#define DC_RO_PROTECT_EADDR3_inst                                                    0x001D
#define DC_RO_PROTECT_EADDR3_eaddr3_shift                                            (12)
#define DC_RO_PROTECT_EADDR3_eaddr3_mask                                             (0xFFFFF000)
#define DC_RO_PROTECT_EADDR3_eaddr3(data)                                            (0xFFFFF000&((data)<<12))
#define DC_RO_PROTECT_EADDR3_eaddr3_src(data)                                        ((0xFFFFF000&(data))>>12)
#define DC_RO_PROTECT_EADDR3_get_eaddr3(data)                                        ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_SADDR0                                                       0x18008478
#define DC_MEM_SCRAMBLE_SADDR0_reg_addr                                              "0xB8008478"
#define DC_MEM_SCRAMBLE_SADDR0_reg                                                   0xB8008478
#define set_DC_MEM_SCRAMBLE_SADDR0_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR0_reg)=data)
#define get_DC_MEM_SCRAMBLE_SADDR0_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR0_reg))
#define DC_MEM_SCRAMBLE_SADDR0_inst_adr                                              "0x001E"
#define DC_MEM_SCRAMBLE_SADDR0_inst                                                  0x001E
#define DC_MEM_SCRAMBLE_SADDR0_saddr0_shift                                          (12)
#define DC_MEM_SCRAMBLE_SADDR0_saddr0_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_SADDR0_saddr0(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_SADDR0_saddr0_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_SADDR0_get_saddr0(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_EADDR0                                                       0x1800847C
#define DC_MEM_SCRAMBLE_EADDR0_reg_addr                                              "0xB800847C"
#define DC_MEM_SCRAMBLE_EADDR0_reg                                                   0xB800847C
#define set_DC_MEM_SCRAMBLE_EADDR0_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR0_reg)=data)
#define get_DC_MEM_SCRAMBLE_EADDR0_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR0_reg))
#define DC_MEM_SCRAMBLE_EADDR0_inst_adr                                              "0x001F"
#define DC_MEM_SCRAMBLE_EADDR0_inst                                                  0x001F
#define DC_MEM_SCRAMBLE_EADDR0_eaddr0_shift                                          (12)
#define DC_MEM_SCRAMBLE_EADDR0_eaddr0_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_EADDR0_eaddr0(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_EADDR0_eaddr0_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_EADDR0_get_eaddr0(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_SADDR1                                                       0x18008480
#define DC_MEM_SCRAMBLE_SADDR1_reg_addr                                              "0xB8008480"
#define DC_MEM_SCRAMBLE_SADDR1_reg                                                   0xB8008480
#define set_DC_MEM_SCRAMBLE_SADDR1_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR1_reg)=data)
#define get_DC_MEM_SCRAMBLE_SADDR1_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR1_reg))
#define DC_MEM_SCRAMBLE_SADDR1_inst_adr                                              "0x0020"
#define DC_MEM_SCRAMBLE_SADDR1_inst                                                  0x0020
#define DC_MEM_SCRAMBLE_SADDR1_saddr1_shift                                          (12)
#define DC_MEM_SCRAMBLE_SADDR1_saddr1_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_SADDR1_saddr1(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_SADDR1_saddr1_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_SADDR1_get_saddr1(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_EADDR1                                                       0x18008484
#define DC_MEM_SCRAMBLE_EADDR1_reg_addr                                              "0xB8008484"
#define DC_MEM_SCRAMBLE_EADDR1_reg                                                   0xB8008484
#define set_DC_MEM_SCRAMBLE_EADDR1_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR1_reg)=data)
#define get_DC_MEM_SCRAMBLE_EADDR1_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR1_reg))
#define DC_MEM_SCRAMBLE_EADDR1_inst_adr                                              "0x0021"
#define DC_MEM_SCRAMBLE_EADDR1_inst                                                  0x0021
#define DC_MEM_SCRAMBLE_EADDR1_eaddr1_shift                                          (12)
#define DC_MEM_SCRAMBLE_EADDR1_eaddr1_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_EADDR1_eaddr1(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_EADDR1_eaddr1_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_EADDR1_get_eaddr1(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_SADDR2                                                       0x18008488
#define DC_MEM_SCRAMBLE_SADDR2_reg_addr                                              "0xB8008488"
#define DC_MEM_SCRAMBLE_SADDR2_reg                                                   0xB8008488
#define set_DC_MEM_SCRAMBLE_SADDR2_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR2_reg)=data)
#define get_DC_MEM_SCRAMBLE_SADDR2_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR2_reg))
#define DC_MEM_SCRAMBLE_SADDR2_inst_adr                                              "0x0022"
#define DC_MEM_SCRAMBLE_SADDR2_inst                                                  0x0022
#define DC_MEM_SCRAMBLE_SADDR2_saddr2_shift                                          (12)
#define DC_MEM_SCRAMBLE_SADDR2_saddr2_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_SADDR2_saddr2(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_SADDR2_saddr2_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_SADDR2_get_saddr2(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_EADDR2                                                       0x1800848C
#define DC_MEM_SCRAMBLE_EADDR2_reg_addr                                              "0xB800848C"
#define DC_MEM_SCRAMBLE_EADDR2_reg                                                   0xB800848C
#define set_DC_MEM_SCRAMBLE_EADDR2_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR2_reg)=data)
#define get_DC_MEM_SCRAMBLE_EADDR2_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR2_reg))
#define DC_MEM_SCRAMBLE_EADDR2_inst_adr                                              "0x0023"
#define DC_MEM_SCRAMBLE_EADDR2_inst                                                  0x0023
#define DC_MEM_SCRAMBLE_EADDR2_eaddr2_shift                                          (12)
#define DC_MEM_SCRAMBLE_EADDR2_eaddr2_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_EADDR2_eaddr2(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_EADDR2_eaddr2_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_EADDR2_get_eaddr2(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_SADDR3                                                       0x18008490
#define DC_MEM_SCRAMBLE_SADDR3_reg_addr                                              "0xB8008490"
#define DC_MEM_SCRAMBLE_SADDR3_reg                                                   0xB8008490
#define set_DC_MEM_SCRAMBLE_SADDR3_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR3_reg)=data)
#define get_DC_MEM_SCRAMBLE_SADDR3_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR3_reg))
#define DC_MEM_SCRAMBLE_SADDR3_inst_adr                                              "0x0024"
#define DC_MEM_SCRAMBLE_SADDR3_inst                                                  0x0024
#define DC_MEM_SCRAMBLE_SADDR3_saddr3_shift                                          (12)
#define DC_MEM_SCRAMBLE_SADDR3_saddr3_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_SADDR3_saddr3(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_SADDR3_saddr3_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_SADDR3_get_saddr3(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_EADDR3                                                       0x18008494
#define DC_MEM_SCRAMBLE_EADDR3_reg_addr                                              "0xB8008494"
#define DC_MEM_SCRAMBLE_EADDR3_reg                                                   0xB8008494
#define set_DC_MEM_SCRAMBLE_EADDR3_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR3_reg)=data)
#define get_DC_MEM_SCRAMBLE_EADDR3_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR3_reg))
#define DC_MEM_SCRAMBLE_EADDR3_inst_adr                                              "0x0025"
#define DC_MEM_SCRAMBLE_EADDR3_inst                                                  0x0025
#define DC_MEM_SCRAMBLE_EADDR3_eaddr3_shift                                          (12)
#define DC_MEM_SCRAMBLE_EADDR3_eaddr3_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_EADDR3_eaddr3(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_EADDR3_eaddr3_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_EADDR3_get_eaddr3(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_SADDR4                                                       0x18008498
#define DC_MEM_SCRAMBLE_SADDR4_reg_addr                                              "0xB8008498"
#define DC_MEM_SCRAMBLE_SADDR4_reg                                                   0xB8008498
#define set_DC_MEM_SCRAMBLE_SADDR4_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR4_reg)=data)
#define get_DC_MEM_SCRAMBLE_SADDR4_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR4_reg))
#define DC_MEM_SCRAMBLE_SADDR4_inst_adr                                              "0x0026"
#define DC_MEM_SCRAMBLE_SADDR4_inst                                                  0x0026
#define DC_MEM_SCRAMBLE_SADDR4_saddr4_shift                                          (12)
#define DC_MEM_SCRAMBLE_SADDR4_saddr4_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_SADDR4_saddr4(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_SADDR4_saddr4_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_SADDR4_get_saddr4(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_EADDR4                                                       0x1800849C
#define DC_MEM_SCRAMBLE_EADDR4_reg_addr                                              "0xB800849C"
#define DC_MEM_SCRAMBLE_EADDR4_reg                                                   0xB800849C
#define set_DC_MEM_SCRAMBLE_EADDR4_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR4_reg)=data)
#define get_DC_MEM_SCRAMBLE_EADDR4_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR4_reg))
#define DC_MEM_SCRAMBLE_EADDR4_inst_adr                                              "0x0027"
#define DC_MEM_SCRAMBLE_EADDR4_inst                                                  0x0027
#define DC_MEM_SCRAMBLE_EADDR4_eaddr4_shift                                          (12)
#define DC_MEM_SCRAMBLE_EADDR4_eaddr4_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_EADDR4_eaddr4(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_EADDR4_eaddr4_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_EADDR4_get_eaddr4(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_SADDR5                                                       0x180084A0
#define DC_MEM_SCRAMBLE_SADDR5_reg_addr                                              "0xB80084A0"
#define DC_MEM_SCRAMBLE_SADDR5_reg                                                   0xB80084A0
#define set_DC_MEM_SCRAMBLE_SADDR5_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR5_reg)=data)
#define get_DC_MEM_SCRAMBLE_SADDR5_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR5_reg))
#define DC_MEM_SCRAMBLE_SADDR5_inst_adr                                              "0x0028"
#define DC_MEM_SCRAMBLE_SADDR5_inst                                                  0x0028
#define DC_MEM_SCRAMBLE_SADDR5_saddr5_shift                                          (12)
#define DC_MEM_SCRAMBLE_SADDR5_saddr5_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_SADDR5_saddr5(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_SADDR5_saddr5_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_SADDR5_get_saddr5(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_EADDR5                                                       0x180084A4
#define DC_MEM_SCRAMBLE_EADDR5_reg_addr                                              "0xB80084A4"
#define DC_MEM_SCRAMBLE_EADDR5_reg                                                   0xB80084A4
#define set_DC_MEM_SCRAMBLE_EADDR5_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR5_reg)=data)
#define get_DC_MEM_SCRAMBLE_EADDR5_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR5_reg))
#define DC_MEM_SCRAMBLE_EADDR5_inst_adr                                              "0x0029"
#define DC_MEM_SCRAMBLE_EADDR5_inst                                                  0x0029
#define DC_MEM_SCRAMBLE_EADDR5_eaddr5_shift                                          (12)
#define DC_MEM_SCRAMBLE_EADDR5_eaddr5_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_EADDR5_eaddr5(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_EADDR5_eaddr5_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_EADDR5_get_eaddr5(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_SADDR6                                                       0x180084A8
#define DC_MEM_SCRAMBLE_SADDR6_reg_addr                                              "0xB80084A8"
#define DC_MEM_SCRAMBLE_SADDR6_reg                                                   0xB80084A8
#define set_DC_MEM_SCRAMBLE_SADDR6_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR6_reg)=data)
#define get_DC_MEM_SCRAMBLE_SADDR6_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR6_reg))
#define DC_MEM_SCRAMBLE_SADDR6_inst_adr                                              "0x002A"
#define DC_MEM_SCRAMBLE_SADDR6_inst                                                  0x002A
#define DC_MEM_SCRAMBLE_SADDR6_saddr6_shift                                          (12)
#define DC_MEM_SCRAMBLE_SADDR6_saddr6_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_SADDR6_saddr6(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_SADDR6_saddr6_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_SADDR6_get_saddr6(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_EADDR6                                                       0x180084AC
#define DC_MEM_SCRAMBLE_EADDR6_reg_addr                                              "0xB80084AC"
#define DC_MEM_SCRAMBLE_EADDR6_reg                                                   0xB80084AC
#define set_DC_MEM_SCRAMBLE_EADDR6_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR6_reg)=data)
#define get_DC_MEM_SCRAMBLE_EADDR6_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR6_reg))
#define DC_MEM_SCRAMBLE_EADDR6_inst_adr                                              "0x002B"
#define DC_MEM_SCRAMBLE_EADDR6_inst                                                  0x002B
#define DC_MEM_SCRAMBLE_EADDR6_eaddr6_shift                                          (12)
#define DC_MEM_SCRAMBLE_EADDR6_eaddr6_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_EADDR6_eaddr6(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_EADDR6_eaddr6_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_EADDR6_get_eaddr6(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_SADDR7                                                       0x180084B0
#define DC_MEM_SCRAMBLE_SADDR7_reg_addr                                              "0xB80084B0"
#define DC_MEM_SCRAMBLE_SADDR7_reg                                                   0xB80084B0
#define set_DC_MEM_SCRAMBLE_SADDR7_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR7_reg)=data)
#define get_DC_MEM_SCRAMBLE_SADDR7_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_SADDR7_reg))
#define DC_MEM_SCRAMBLE_SADDR7_inst_adr                                              "0x002C"
#define DC_MEM_SCRAMBLE_SADDR7_inst                                                  0x002C
#define DC_MEM_SCRAMBLE_SADDR7_saddr7_shift                                          (12)
#define DC_MEM_SCRAMBLE_SADDR7_saddr7_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_SADDR7_saddr7(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_SADDR7_saddr7_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_SADDR7_get_saddr7(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_SCRAMBLE_EADDR7                                                       0x180084B4
#define DC_MEM_SCRAMBLE_EADDR7_reg_addr                                              "0xB80084B4"
#define DC_MEM_SCRAMBLE_EADDR7_reg                                                   0xB80084B4
#define set_DC_MEM_SCRAMBLE_EADDR7_reg(data)   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR7_reg)=data)
#define get_DC_MEM_SCRAMBLE_EADDR7_reg   (*((volatile unsigned int*) DC_MEM_SCRAMBLE_EADDR7_reg))
#define DC_MEM_SCRAMBLE_EADDR7_inst_adr                                              "0x002D"
#define DC_MEM_SCRAMBLE_EADDR7_inst                                                  0x002D
#define DC_MEM_SCRAMBLE_EADDR7_eaddr7_shift                                          (12)
#define DC_MEM_SCRAMBLE_EADDR7_eaddr7_mask                                           (0xFFFFF000)
#define DC_MEM_SCRAMBLE_EADDR7_eaddr7(data)                                          (0xFFFFF000&((data)<<12))
#define DC_MEM_SCRAMBLE_EADDR7_eaddr7_src(data)                                      ((0xFFFFF000&(data))>>12)
#define DC_MEM_SCRAMBLE_EADDR7_get_eaddr7(data)                                      ((0xFFFFF000&(data))>>12)


#define DC_MEM_PROTECT_ID_CTRL_0                                                     0x180084B8
#define DC_MEM_PROTECT_ID_CTRL_0_reg_addr                                            "0xB80084B8"
#define DC_MEM_PROTECT_ID_CTRL_0_reg                                                 0xB80084B8
#define set_DC_MEM_PROTECT_ID_CTRL_0_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_ID_CTRL_0_reg)=data)
#define get_DC_MEM_PROTECT_ID_CTRL_0_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_ID_CTRL_0_reg))
#define DC_MEM_PROTECT_ID_CTRL_0_inst_adr                                            "0x002E"
#define DC_MEM_PROTECT_ID_CTRL_0_inst                                                0x002E
#define DC_MEM_PROTECT_ID_CTRL_0_md_tee_protect_en_shift                             (24)
#define DC_MEM_PROTECT_ID_CTRL_0_md_tee_protect_en_mask                              (0xFF000000)
#define DC_MEM_PROTECT_ID_CTRL_0_md_tee_protect_en(data)                             (0xFF000000&((data)<<24))
#define DC_MEM_PROTECT_ID_CTRL_0_md_tee_protect_en_src(data)                         ((0xFF000000&(data))>>24)
#define DC_MEM_PROTECT_ID_CTRL_0_get_md_tee_protect_en(data)                         ((0xFF000000&(data))>>24)
#define DC_MEM_PROTECT_ID_CTRL_0_cp_tee_protect_en_shift                             (16)
#define DC_MEM_PROTECT_ID_CTRL_0_cp_tee_protect_en_mask                              (0x00FF0000)
#define DC_MEM_PROTECT_ID_CTRL_0_cp_tee_protect_en(data)                             (0x00FF0000&((data)<<16))
#define DC_MEM_PROTECT_ID_CTRL_0_cp_tee_protect_en_src(data)                         ((0x00FF0000&(data))>>16)
#define DC_MEM_PROTECT_ID_CTRL_0_get_cp_tee_protect_en(data)                         ((0x00FF0000&(data))>>16)
#define DC_MEM_PROTECT_ID_CTRL_0_vo_protect_en_shift                                 (8)
#define DC_MEM_PROTECT_ID_CTRL_0_vo_protect_en_mask                                  (0x0000FF00)
#define DC_MEM_PROTECT_ID_CTRL_0_vo_protect_en(data)                                 (0x0000FF00&((data)<<8))
#define DC_MEM_PROTECT_ID_CTRL_0_vo_protect_en_src(data)                             ((0x0000FF00&(data))>>8)
#define DC_MEM_PROTECT_ID_CTRL_0_get_vo_protect_en(data)                             ((0x0000FF00&(data))>>8)
#define DC_MEM_PROTECT_ID_CTRL_0_nf_tee_protect_en_shift                             (0)
#define DC_MEM_PROTECT_ID_CTRL_0_nf_tee_protect_en_mask                              (0x000000FF)
#define DC_MEM_PROTECT_ID_CTRL_0_nf_tee_protect_en(data)                             (0x000000FF&((data)<<0))
#define DC_MEM_PROTECT_ID_CTRL_0_nf_tee_protect_en_src(data)                         ((0x000000FF&(data))>>0)
#define DC_MEM_PROTECT_ID_CTRL_0_get_nf_tee_protect_en(data)                         ((0x000000FF&(data))>>0)


#define DC_MEM_PROTECT_ID_CTRL_1                                                     0x180084BC
#define DC_MEM_PROTECT_ID_CTRL_1_reg_addr                                            "0xB80084BC"
#define DC_MEM_PROTECT_ID_CTRL_1_reg                                                 0xB80084BC
#define set_DC_MEM_PROTECT_ID_CTRL_1_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_ID_CTRL_1_reg)=data)
#define get_DC_MEM_PROTECT_ID_CTRL_1_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_ID_CTRL_1_reg))
#define DC_MEM_PROTECT_ID_CTRL_1_inst_adr                                            "0x002F"
#define DC_MEM_PROTECT_ID_CTRL_1_inst                                                0x002F
#define DC_MEM_PROTECT_ID_CTRL_1_scpu_tee_protect_en_shift                           (24)
#define DC_MEM_PROTECT_ID_CTRL_1_scpu_tee_protect_en_mask                            (0xFF000000)
#define DC_MEM_PROTECT_ID_CTRL_1_scpu_tee_protect_en(data)                           (0xFF000000&((data)<<24))
#define DC_MEM_PROTECT_ID_CTRL_1_scpu_tee_protect_en_src(data)                       ((0xFF000000&(data))>>24)
#define DC_MEM_PROTECT_ID_CTRL_1_get_scpu_tee_protect_en(data)                       ((0xFF000000&(data))>>24)
#define DC_MEM_PROTECT_ID_CTRL_1_acpu_protect_en_shift                               (16)
#define DC_MEM_PROTECT_ID_CTRL_1_acpu_protect_en_mask                                (0x00FF0000)
#define DC_MEM_PROTECT_ID_CTRL_1_acpu_protect_en(data)                               (0x00FF0000&((data)<<16))
#define DC_MEM_PROTECT_ID_CTRL_1_acpu_protect_en_src(data)                           ((0x00FF0000&(data))>>16)
#define DC_MEM_PROTECT_ID_CTRL_1_get_acpu_protect_en(data)                           ((0x00FF0000&(data))>>16)
#define DC_MEM_PROTECT_ID_CTRL_1_video_protect_en_shift                              (8)
#define DC_MEM_PROTECT_ID_CTRL_1_video_protect_en_mask                               (0x0000FF00)
#define DC_MEM_PROTECT_ID_CTRL_1_video_protect_en(data)                              (0x0000FF00&((data)<<8))
#define DC_MEM_PROTECT_ID_CTRL_1_video_protect_en_src(data)                          ((0x0000FF00&(data))>>8)
#define DC_MEM_PROTECT_ID_CTRL_1_get_video_protect_en(data)                          ((0x0000FF00&(data))>>8)
#define DC_MEM_PROTECT_ID_CTRL_1_audio_protect_en_shift                              (0)
#define DC_MEM_PROTECT_ID_CTRL_1_audio_protect_en_mask                               (0x000000FF)
#define DC_MEM_PROTECT_ID_CTRL_1_audio_protect_en(data)                              (0x000000FF&((data)<<0))
#define DC_MEM_PROTECT_ID_CTRL_1_audio_protect_en_src(data)                          ((0x000000FF&(data))>>0)
#define DC_MEM_PROTECT_ID_CTRL_1_get_audio_protect_en(data)                          ((0x000000FF&(data))>>0)


#define DC_MEM_PROTECT_ID_CTRL_2                                                     0x180084C0
#define DC_MEM_PROTECT_ID_CTRL_2_reg_addr                                            "0xB80084C0"
#define DC_MEM_PROTECT_ID_CTRL_2_reg                                                 0xB80084C0
#define set_DC_MEM_PROTECT_ID_CTRL_2_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_ID_CTRL_2_reg)=data)
#define get_DC_MEM_PROTECT_ID_CTRL_2_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_ID_CTRL_2_reg))
#define DC_MEM_PROTECT_ID_CTRL_2_inst_adr                                            "0x0030"
#define DC_MEM_PROTECT_ID_CTRL_2_inst                                                0x0030
#define DC_MEM_PROTECT_ID_CTRL_2_scpu_tee_blk_protect_en_shift                       (14)
#define DC_MEM_PROTECT_ID_CTRL_2_scpu_tee_blk_protect_en_mask                        (0x0000C000)
#define DC_MEM_PROTECT_ID_CTRL_2_scpu_tee_blk_protect_en(data)                       (0x0000C000&((data)<<14))
#define DC_MEM_PROTECT_ID_CTRL_2_scpu_tee_blk_protect_en_src(data)                   ((0x0000C000&(data))>>14)
#define DC_MEM_PROTECT_ID_CTRL_2_get_scpu_tee_blk_protect_en(data)                   ((0x0000C000&(data))>>14)
#define DC_MEM_PROTECT_ID_CTRL_2_acpu_blk_protect_en_shift                           (12)
#define DC_MEM_PROTECT_ID_CTRL_2_acpu_blk_protect_en_mask                            (0x00003000)
#define DC_MEM_PROTECT_ID_CTRL_2_acpu_blk_protect_en(data)                           (0x00003000&((data)<<12))
#define DC_MEM_PROTECT_ID_CTRL_2_acpu_blk_protect_en_src(data)                       ((0x00003000&(data))>>12)
#define DC_MEM_PROTECT_ID_CTRL_2_get_acpu_blk_protect_en(data)                       ((0x00003000&(data))>>12)
#define DC_MEM_PROTECT_ID_CTRL_2_video_blk_protect_en_shift                          (10)
#define DC_MEM_PROTECT_ID_CTRL_2_video_blk_protect_en_mask                           (0x00000C00)
#define DC_MEM_PROTECT_ID_CTRL_2_video_blk_protect_en(data)                          (0x00000C00&((data)<<10))
#define DC_MEM_PROTECT_ID_CTRL_2_video_blk_protect_en_src(data)                      ((0x00000C00&(data))>>10)
#define DC_MEM_PROTECT_ID_CTRL_2_get_video_blk_protect_en(data)                      ((0x00000C00&(data))>>10)
#define DC_MEM_PROTECT_ID_CTRL_2_audio_blk_protect_en_shift                          (8)
#define DC_MEM_PROTECT_ID_CTRL_2_audio_blk_protect_en_mask                           (0x00000300)
#define DC_MEM_PROTECT_ID_CTRL_2_audio_blk_protect_en(data)                          (0x00000300&((data)<<8))
#define DC_MEM_PROTECT_ID_CTRL_2_audio_blk_protect_en_src(data)                      ((0x00000300&(data))>>8)
#define DC_MEM_PROTECT_ID_CTRL_2_get_audio_blk_protect_en(data)                      ((0x00000300&(data))>>8)
#define DC_MEM_PROTECT_ID_CTRL_2_md_tee_blk_protect_en_shift                         (6)
#define DC_MEM_PROTECT_ID_CTRL_2_md_tee_blk_protect_en_mask                          (0x000000C0)
#define DC_MEM_PROTECT_ID_CTRL_2_md_tee_blk_protect_en(data)                         (0x000000C0&((data)<<6))
#define DC_MEM_PROTECT_ID_CTRL_2_md_tee_blk_protect_en_src(data)                     ((0x000000C0&(data))>>6)
#define DC_MEM_PROTECT_ID_CTRL_2_get_md_tee_blk_protect_en(data)                     ((0x000000C0&(data))>>6)
#define DC_MEM_PROTECT_ID_CTRL_2_cp_tee_blk_protect_en_shift                         (4)
#define DC_MEM_PROTECT_ID_CTRL_2_cp_tee_blk_protect_en_mask                          (0x00000030)
#define DC_MEM_PROTECT_ID_CTRL_2_cp_tee_blk_protect_en(data)                         (0x00000030&((data)<<4))
#define DC_MEM_PROTECT_ID_CTRL_2_cp_tee_blk_protect_en_src(data)                     ((0x00000030&(data))>>4)
#define DC_MEM_PROTECT_ID_CTRL_2_get_cp_tee_blk_protect_en(data)                     ((0x00000030&(data))>>4)
#define DC_MEM_PROTECT_ID_CTRL_2_vo_blk_protect_en_shift                             (2)
#define DC_MEM_PROTECT_ID_CTRL_2_vo_blk_protect_en_mask                              (0x0000000C)
#define DC_MEM_PROTECT_ID_CTRL_2_vo_blk_protect_en(data)                             (0x0000000C&((data)<<2))
#define DC_MEM_PROTECT_ID_CTRL_2_vo_blk_protect_en_src(data)                         ((0x0000000C&(data))>>2)
#define DC_MEM_PROTECT_ID_CTRL_2_get_vo_blk_protect_en(data)                         ((0x0000000C&(data))>>2)
#define DC_MEM_PROTECT_ID_CTRL_2_nf_tee_blk_protect_en_shift                         (0)
#define DC_MEM_PROTECT_ID_CTRL_2_nf_tee_blk_protect_en_mask                          (0x00000003)
#define DC_MEM_PROTECT_ID_CTRL_2_nf_tee_blk_protect_en(data)                         (0x00000003&((data)<<0))
#define DC_MEM_PROTECT_ID_CTRL_2_nf_tee_blk_protect_en_src(data)                     ((0x00000003&(data))>>0)
#define DC_MEM_PROTECT_ID_CTRL_2_get_nf_tee_blk_protect_en(data)                     ((0x00000003&(data))>>0)


#define DC_MEM_PROTECT_ID_CTRL_3                                                     0x180084C4
#define DC_MEM_PROTECT_ID_CTRL_3_reg_addr                                            "0xB80084C4"
#define DC_MEM_PROTECT_ID_CTRL_3_reg                                                 0xB80084C4
#define set_DC_MEM_PROTECT_ID_CTRL_3_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_ID_CTRL_3_reg)=data)
#define get_DC_MEM_PROTECT_ID_CTRL_3_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_ID_CTRL_3_reg))
#define DC_MEM_PROTECT_ID_CTRL_3_inst_adr                                            "0x0031"
#define DC_MEM_PROTECT_ID_CTRL_3_inst                                                0x0031
#define DC_MEM_PROTECT_ID_CTRL_3_scpu_tee_ro_protect_en_shift                        (28)
#define DC_MEM_PROTECT_ID_CTRL_3_scpu_tee_ro_protect_en_mask                         (0xF0000000)
#define DC_MEM_PROTECT_ID_CTRL_3_scpu_tee_ro_protect_en(data)                        (0xF0000000&((data)<<28))
#define DC_MEM_PROTECT_ID_CTRL_3_scpu_tee_ro_protect_en_src(data)                    ((0xF0000000&(data))>>28)
#define DC_MEM_PROTECT_ID_CTRL_3_get_scpu_tee_ro_protect_en(data)                    ((0xF0000000&(data))>>28)
#define DC_MEM_PROTECT_ID_CTRL_3_acpu_ro_protect_en_shift                            (24)
#define DC_MEM_PROTECT_ID_CTRL_3_acpu_ro_protect_en_mask                             (0x0F000000)
#define DC_MEM_PROTECT_ID_CTRL_3_acpu_ro_protect_en(data)                            (0x0F000000&((data)<<24))
#define DC_MEM_PROTECT_ID_CTRL_3_acpu_ro_protect_en_src(data)                        ((0x0F000000&(data))>>24)
#define DC_MEM_PROTECT_ID_CTRL_3_get_acpu_ro_protect_en(data)                        ((0x0F000000&(data))>>24)
#define DC_MEM_PROTECT_ID_CTRL_3_video_ro_protect_en_shift                           (20)
#define DC_MEM_PROTECT_ID_CTRL_3_video_ro_protect_en_mask                            (0x00F00000)
#define DC_MEM_PROTECT_ID_CTRL_3_video_ro_protect_en(data)                           (0x00F00000&((data)<<20))
#define DC_MEM_PROTECT_ID_CTRL_3_video_ro_protect_en_src(data)                       ((0x00F00000&(data))>>20)
#define DC_MEM_PROTECT_ID_CTRL_3_get_video_ro_protect_en(data)                       ((0x00F00000&(data))>>20)
#define DC_MEM_PROTECT_ID_CTRL_3_audio_ro_protect_en_shift                           (16)
#define DC_MEM_PROTECT_ID_CTRL_3_audio_ro_protect_en_mask                            (0x000F0000)
#define DC_MEM_PROTECT_ID_CTRL_3_audio_ro_protect_en(data)                           (0x000F0000&((data)<<16))
#define DC_MEM_PROTECT_ID_CTRL_3_audio_ro_protect_en_src(data)                       ((0x000F0000&(data))>>16)
#define DC_MEM_PROTECT_ID_CTRL_3_get_audio_ro_protect_en(data)                       ((0x000F0000&(data))>>16)
#define DC_MEM_PROTECT_ID_CTRL_3_md_tee_ro_protect_en_shift                          (12)
#define DC_MEM_PROTECT_ID_CTRL_3_md_tee_ro_protect_en_mask                           (0x0000F000)
#define DC_MEM_PROTECT_ID_CTRL_3_md_tee_ro_protect_en(data)                          (0x0000F000&((data)<<12))
#define DC_MEM_PROTECT_ID_CTRL_3_md_tee_ro_protect_en_src(data)                      ((0x0000F000&(data))>>12)
#define DC_MEM_PROTECT_ID_CTRL_3_get_md_tee_ro_protect_en(data)                      ((0x0000F000&(data))>>12)
#define DC_MEM_PROTECT_ID_CTRL_3_cp_tee_ro_protect_en_shift                          (8)
#define DC_MEM_PROTECT_ID_CTRL_3_cp_tee_ro_protect_en_mask                           (0x00000F00)
#define DC_MEM_PROTECT_ID_CTRL_3_cp_tee_ro_protect_en(data)                          (0x00000F00&((data)<<8))
#define DC_MEM_PROTECT_ID_CTRL_3_cp_tee_ro_protect_en_src(data)                      ((0x00000F00&(data))>>8)
#define DC_MEM_PROTECT_ID_CTRL_3_get_cp_tee_ro_protect_en(data)                      ((0x00000F00&(data))>>8)
#define DC_MEM_PROTECT_ID_CTRL_3_vo_ro_protect_en_shift                              (4)
#define DC_MEM_PROTECT_ID_CTRL_3_vo_ro_protect_en_mask                               (0x000000F0)
#define DC_MEM_PROTECT_ID_CTRL_3_vo_ro_protect_en(data)                              (0x000000F0&((data)<<4))
#define DC_MEM_PROTECT_ID_CTRL_3_vo_ro_protect_en_src(data)                          ((0x000000F0&(data))>>4)
#define DC_MEM_PROTECT_ID_CTRL_3_get_vo_ro_protect_en(data)                          ((0x000000F0&(data))>>4)
#define DC_MEM_PROTECT_ID_CTRL_3_nf_tee_ro_protect_en_shift                          (0)
#define DC_MEM_PROTECT_ID_CTRL_3_nf_tee_ro_protect_en_mask                           (0x0000000F)
#define DC_MEM_PROTECT_ID_CTRL_3_nf_tee_ro_protect_en(data)                          (0x0000000F&((data)<<0))
#define DC_MEM_PROTECT_ID_CTRL_3_nf_tee_ro_protect_en_src(data)                      ((0x0000000F&(data))>>0)
#define DC_MEM_PROTECT_ID_CTRL_3_get_nf_tee_ro_protect_en(data)                      ((0x0000000F&(data))>>0)


#define DC_MEM_PROTECT_PICT_CTRL_0                                                   0x180084C8
#define DC_MEM_PROTECT_PICT_CTRL_0_reg_addr                                          "0xB80084C8"
#define DC_MEM_PROTECT_PICT_CTRL_0_reg                                               0xB80084C8
#define set_DC_MEM_PROTECT_PICT_CTRL_0_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_PICT_CTRL_0_reg)=data)
#define get_DC_MEM_PROTECT_PICT_CTRL_0_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_PICT_CTRL_0_reg))
#define DC_MEM_PROTECT_PICT_CTRL_0_inst_adr                                          "0x0032"
#define DC_MEM_PROTECT_PICT_CTRL_0_inst                                              0x0032
#define DC_MEM_PROTECT_PICT_CTRL_0_blk_pict_set_chk_en_0_shift                       (0)
#define DC_MEM_PROTECT_PICT_CTRL_0_blk_pict_set_chk_en_0_mask                        (0xFFFFFFFF)
#define DC_MEM_PROTECT_PICT_CTRL_0_blk_pict_set_chk_en_0(data)                       (0xFFFFFFFF&((data)<<0))
#define DC_MEM_PROTECT_PICT_CTRL_0_blk_pict_set_chk_en_0_src(data)                   ((0xFFFFFFFF&(data))>>0)
#define DC_MEM_PROTECT_PICT_CTRL_0_get_blk_pict_set_chk_en_0(data)                   ((0xFFFFFFFF&(data))>>0)


#define DC_MEM_PROTECT_PICT_CTRL_1                                                   0x180084CC
#define DC_MEM_PROTECT_PICT_CTRL_1_reg_addr                                          "0xB80084CC"
#define DC_MEM_PROTECT_PICT_CTRL_1_reg                                               0xB80084CC
#define set_DC_MEM_PROTECT_PICT_CTRL_1_reg(data)   (*((volatile unsigned int*) DC_MEM_PROTECT_PICT_CTRL_1_reg)=data)
#define get_DC_MEM_PROTECT_PICT_CTRL_1_reg   (*((volatile unsigned int*) DC_MEM_PROTECT_PICT_CTRL_1_reg))
#define DC_MEM_PROTECT_PICT_CTRL_1_inst_adr                                          "0x0033"
#define DC_MEM_PROTECT_PICT_CTRL_1_inst                                              0x0033
#define DC_MEM_PROTECT_PICT_CTRL_1_blk_pict_set_chk_en_1_shift                       (0)
#define DC_MEM_PROTECT_PICT_CTRL_1_blk_pict_set_chk_en_1_mask                        (0xFFFFFFFF)
#define DC_MEM_PROTECT_PICT_CTRL_1_blk_pict_set_chk_en_1(data)                       (0xFFFFFFFF&((data)<<0))
#define DC_MEM_PROTECT_PICT_CTRL_1_blk_pict_set_chk_en_1_src(data)                   ((0xFFFFFFFF&(data))>>0)
#define DC_MEM_PROTECT_PICT_CTRL_1_get_blk_pict_set_chk_en_1(data)                   ((0xFFFFFFFF&(data))>>0)


#define DC_SECURE_MISC                                                               0x18008740
#define DC_SECURE_MISC_reg_addr                                                      "0xB8008740"
#define DC_SECURE_MISC_reg                                                           0xB8008740
#define set_DC_SECURE_MISC_reg(data)   (*((volatile unsigned int*) DC_SECURE_MISC_reg)=data)
#define get_DC_SECURE_MISC_reg   (*((volatile unsigned int*) DC_SECURE_MISC_reg))
#define DC_SECURE_MISC_inst_adr                                                      "0x00D0"
#define DC_SECURE_MISC_inst                                                          0x00D0
#define DC_SECURE_MISC_dram_16g_used_shift                                           (5)
#define DC_SECURE_MISC_dram_16g_used_mask                                            (0x00000020)
#define DC_SECURE_MISC_dram_16g_used(data)                                           (0x00000020&((data)<<5))
#define DC_SECURE_MISC_dram_16g_used_src(data)                                       ((0x00000020&(data))>>5)
#define DC_SECURE_MISC_get_dram_16g_used(data)                                       ((0x00000020&(data))>>5)
#define DC_SECURE_MISC_dram_8g_used_shift                                            (4)
#define DC_SECURE_MISC_dram_8g_used_mask                                             (0x00000010)
#define DC_SECURE_MISC_dram_8g_used(data)                                            (0x00000010&((data)<<4))
#define DC_SECURE_MISC_dram_8g_used_src(data)                                        ((0x00000010&(data))>>4)
#define DC_SECURE_MISC_get_dram_8g_used(data)                                        ((0x00000010&(data))>>4)
#define DC_SECURE_MISC_dram_4g_used_shift                                            (3)
#define DC_SECURE_MISC_dram_4g_used_mask                                             (0x00000008)
#define DC_SECURE_MISC_dram_4g_used(data)                                            (0x00000008&((data)<<3))
#define DC_SECURE_MISC_dram_4g_used_src(data)                                        ((0x00000008&(data))>>3)
#define DC_SECURE_MISC_get_dram_4g_used(data)                                        ((0x00000008&(data))>>3)
#define DC_SECURE_MISC_dram_2g_used_shift                                            (2)
#define DC_SECURE_MISC_dram_2g_used_mask                                             (0x00000004)
#define DC_SECURE_MISC_dram_2g_used(data)                                            (0x00000004&((data)<<2))
#define DC_SECURE_MISC_dram_2g_used_src(data)                                        ((0x00000004&(data))>>2)
#define DC_SECURE_MISC_get_dram_2g_used(data)                                        ((0x00000004&(data))>>2)
#define DC_SECURE_MISC_dram_1g_used_shift                                            (1)
#define DC_SECURE_MISC_dram_1g_used_mask                                             (0x00000002)
#define DC_SECURE_MISC_dram_1g_used(data)                                            (0x00000002&((data)<<1))
#define DC_SECURE_MISC_dram_1g_used_src(data)                                        ((0x00000002&(data))>>1)
#define DC_SECURE_MISC_get_dram_1g_used(data)                                        ((0x00000002&(data))>>1)
#define DC_SECURE_MISC_dram_512_used_shift                                           (0)
#define DC_SECURE_MISC_dram_512_used_mask                                            (0x00000001)
#define DC_SECURE_MISC_dram_512_used(data)                                           (0x00000001&((data)<<0))
#define DC_SECURE_MISC_dram_512_used_src(data)                                       ((0x00000001&(data))>>0)
#define DC_SECURE_MISC_get_dram_512_used(data)                                       ((0x00000001&(data))>>0)


#define DC_MEM_INT                                                                   0x18008750
#define DC_MEM_INT_reg_addr                                                          "0xB8008750"
#define DC_MEM_INT_reg                                                               0xB8008750
#define set_DC_MEM_INT_reg(data)   (*((volatile unsigned int*) DC_MEM_INT_reg)=data)
#define get_DC_MEM_INT_reg   (*((volatile unsigned int*) DC_MEM_INT_reg))
#define DC_MEM_INT_inst_adr                                                          "0x00D4"
#define DC_MEM_INT_inst                                                              0x00D4
#define DC_MEM_INT_write_enable9_shift                                               (31)
#define DC_MEM_INT_write_enable9_mask                                                (0x80000000)
#define DC_MEM_INT_write_enable9(data)                                               (0x80000000&((data)<<31))
#define DC_MEM_INT_write_enable9_src(data)                                           ((0x80000000&(data))>>31)
#define DC_MEM_INT_get_write_enable9(data)                                           ((0x80000000&(data))>>31)
#define DC_MEM_INT_int_kcpu_key_up_en_shift                                          (30)
#define DC_MEM_INT_int_kcpu_key_up_en_mask                                           (0x40000000)
#define DC_MEM_INT_int_kcpu_key_up_en(data)                                          (0x40000000&((data)<<30))
#define DC_MEM_INT_int_kcpu_key_up_en_src(data)                                      ((0x40000000&(data))>>30)
#define DC_MEM_INT_get_int_kcpu_key_up_en(data)                                      ((0x40000000&(data))>>30)
#define DC_MEM_INT_write_enable8_shift                                               (29)
#define DC_MEM_INT_write_enable8_mask                                                (0x20000000)
#define DC_MEM_INT_write_enable8(data)                                               (0x20000000&((data)<<29))
#define DC_MEM_INT_write_enable8_src(data)                                           ((0x20000000&(data))>>29)
#define DC_MEM_INT_get_write_enable8(data)                                           ((0x20000000&(data))>>29)
#define DC_MEM_INT_int_kcpu_key_up_shift                                             (28)
#define DC_MEM_INT_int_kcpu_key_up_mask                                              (0x10000000)
#define DC_MEM_INT_int_kcpu_key_up(data)                                             (0x10000000&((data)<<28))
#define DC_MEM_INT_int_kcpu_key_up_src(data)                                         ((0x10000000&(data))>>28)
#define DC_MEM_INT_get_int_kcpu_key_up(data)                                         ((0x10000000&(data))>>28)
#define DC_MEM_INT_write_enable7_shift                                               (27)
#define DC_MEM_INT_write_enable7_mask                                                (0x08000000)
#define DC_MEM_INT_write_enable7(data)                                               (0x08000000&((data)<<27))
#define DC_MEM_INT_write_enable7_src(data)                                           ((0x08000000&(data))>>27)
#define DC_MEM_INT_get_write_enable7(data)                                           ((0x08000000&(data))>>27)
#define DC_MEM_INT_key_up_status_shift                                               (24)
#define DC_MEM_INT_key_up_status_mask                                                (0x07000000)
#define DC_MEM_INT_key_up_status(data)                                               (0x07000000&((data)<<24))
#define DC_MEM_INT_key_up_status_src(data)                                           ((0x07000000&(data))>>24)
#define DC_MEM_INT_get_key_up_status(data)                                           ((0x07000000&(data))>>24)
#define DC_MEM_INT_write_enable6_shift                                               (23)
#define DC_MEM_INT_write_enable6_mask                                                (0x00800000)
#define DC_MEM_INT_write_enable6(data)                                               (0x00800000&((data)<<23))
#define DC_MEM_INT_write_enable6_src(data)                                           ((0x00800000&(data))>>23)
#define DC_MEM_INT_get_write_enable6(data)                                           ((0x00800000&(data))>>23)
#define DC_MEM_INT_scramble_int_en_shift                                             (22)
#define DC_MEM_INT_scramble_int_en_mask                                              (0x00400000)
#define DC_MEM_INT_scramble_int_en(data)                                             (0x00400000&((data)<<22))
#define DC_MEM_INT_scramble_int_en_src(data)                                         ((0x00400000&(data))>>22)
#define DC_MEM_INT_get_scramble_int_en(data)                                         ((0x00400000&(data))>>22)
#define DC_MEM_INT_write_enable5_shift                                               (21)
#define DC_MEM_INT_write_enable5_mask                                                (0x00200000)
#define DC_MEM_INT_write_enable5(data)                                               (0x00200000&((data)<<21))
#define DC_MEM_INT_write_enable5_src(data)                                           ((0x00200000&(data))>>21)
#define DC_MEM_INT_get_write_enable5(data)                                           ((0x00200000&(data))>>21)
#define DC_MEM_INT_scramble_int_shift                                                (20)
#define DC_MEM_INT_scramble_int_mask                                                 (0x00100000)
#define DC_MEM_INT_scramble_int(data)                                                (0x00100000&((data)<<20))
#define DC_MEM_INT_scramble_int_src(data)                                            ((0x00100000&(data))>>20)
#define DC_MEM_INT_get_scramble_int(data)                                            ((0x00100000&(data))>>20)
#define DC_MEM_INT_write_enable4_shift                                               (19)
#define DC_MEM_INT_write_enable4_mask                                                (0x00080000)
#define DC_MEM_INT_write_enable4(data)                                               (0x00080000&((data)<<19))
#define DC_MEM_INT_write_enable4_src(data)                                           ((0x00080000&(data))>>19)
#define DC_MEM_INT_get_write_enable4(data)                                           ((0x00080000&(data))>>19)
#define DC_MEM_INT_scramble_id_shift                                                 (12)
#define DC_MEM_INT_scramble_id_mask                                                  (0x0007F000)
#define DC_MEM_INT_scramble_id(data)                                                 (0x0007F000&((data)<<12))
#define DC_MEM_INT_scramble_id_src(data)                                             ((0x0007F000&(data))>>12)
#define DC_MEM_INT_get_scramble_id(data)                                             ((0x0007F000&(data))>>12)
#define DC_MEM_INT_write_enable3_shift                                               (11)
#define DC_MEM_INT_write_enable3_mask                                                (0x00000800)
#define DC_MEM_INT_write_enable3(data)                                               (0x00000800&((data)<<11))
#define DC_MEM_INT_write_enable3_src(data)                                           ((0x00000800&(data))>>11)
#define DC_MEM_INT_get_write_enable3(data)                                           ((0x00000800&(data))>>11)
#define DC_MEM_INT_protect_int_en_shift                                              (10)
#define DC_MEM_INT_protect_int_en_mask                                               (0x00000400)
#define DC_MEM_INT_protect_int_en(data)                                              (0x00000400&((data)<<10))
#define DC_MEM_INT_protect_int_en_src(data)                                          ((0x00000400&(data))>>10)
#define DC_MEM_INT_get_protect_int_en(data)                                          ((0x00000400&(data))>>10)
#define DC_MEM_INT_write_enable2_shift                                               (9)
#define DC_MEM_INT_write_enable2_mask                                                (0x00000200)
#define DC_MEM_INT_write_enable2(data)                                               (0x00000200&((data)<<9))
#define DC_MEM_INT_write_enable2_src(data)                                           ((0x00000200&(data))>>9)
#define DC_MEM_INT_get_write_enable2(data)                                           ((0x00000200&(data))>>9)
#define DC_MEM_INT_protect_int_shift                                                 (8)
#define DC_MEM_INT_protect_int_mask                                                  (0x00000100)
#define DC_MEM_INT_protect_int(data)                                                 (0x00000100&((data)<<8))
#define DC_MEM_INT_protect_int_src(data)                                             ((0x00000100&(data))>>8)
#define DC_MEM_INT_get_protect_int(data)                                             ((0x00000100&(data))>>8)
#define DC_MEM_INT_write_enable1_shift                                               (7)
#define DC_MEM_INT_write_enable1_mask                                                (0x00000080)
#define DC_MEM_INT_write_enable1(data)                                               (0x00000080&((data)<<7))
#define DC_MEM_INT_write_enable1_src(data)                                           ((0x00000080&(data))>>7)
#define DC_MEM_INT_get_write_enable1(data)                                           ((0x00000080&(data))>>7)
#define DC_MEM_INT_protect_id_shift                                                  (0)
#define DC_MEM_INT_protect_id_mask                                                   (0x0000007F)
#define DC_MEM_INT_protect_id(data)                                                  (0x0000007F&((data)<<0))
#define DC_MEM_INT_protect_id_src(data)                                              ((0x0000007F&(data))>>0)
#define DC_MEM_INT_get_protect_id(data)                                              ((0x0000007F&(data))>>0)


#define DC_MEM_OTHER_INT                                                             0x18008754
#define DC_MEM_OTHER_INT_reg_addr                                                    "0xB8008754"
#define DC_MEM_OTHER_INT_reg                                                         0xB8008754
#define set_DC_MEM_OTHER_INT_reg(data)   (*((volatile unsigned int*) DC_MEM_OTHER_INT_reg)=data)
#define get_DC_MEM_OTHER_INT_reg   (*((volatile unsigned int*) DC_MEM_OTHER_INT_reg))
#define DC_MEM_OTHER_INT_inst_adr                                                    "0x00D5"
#define DC_MEM_OTHER_INT_inst                                                        0x00D5
#define DC_MEM_OTHER_INT_write_enable10_shift                                        (31)
#define DC_MEM_OTHER_INT_write_enable10_mask                                         (0x80000000)
#define DC_MEM_OTHER_INT_write_enable10(data)                                        (0x80000000&((data)<<31))
#define DC_MEM_OTHER_INT_write_enable10_src(data)                                    ((0x80000000&(data))>>31)
#define DC_MEM_OTHER_INT_get_write_enable10(data)                                    ((0x80000000&(data))>>31)
#define DC_MEM_OTHER_INT_x_overflow_int_en_shift                                     (30)
#define DC_MEM_OTHER_INT_x_overflow_int_en_mask                                      (0x40000000)
#define DC_MEM_OTHER_INT_x_overflow_int_en(data)                                     (0x40000000&((data)<<30))
#define DC_MEM_OTHER_INT_x_overflow_int_en_src(data)                                 ((0x40000000&(data))>>30)
#define DC_MEM_OTHER_INT_get_x_overflow_int_en(data)                                 ((0x40000000&(data))>>30)
#define DC_MEM_OTHER_INT_write_enable9_shift                                         (29)
#define DC_MEM_OTHER_INT_write_enable9_mask                                          (0x20000000)
#define DC_MEM_OTHER_INT_write_enable9(data)                                         (0x20000000&((data)<<29))
#define DC_MEM_OTHER_INT_write_enable9_src(data)                                     ((0x20000000&(data))>>29)
#define DC_MEM_OTHER_INT_get_write_enable9(data)                                     ((0x20000000&(data))>>29)
#define DC_MEM_OTHER_INT_x_overflow_int_shift                                        (28)
#define DC_MEM_OTHER_INT_x_overflow_int_mask                                         (0x10000000)
#define DC_MEM_OTHER_INT_x_overflow_int(data)                                        (0x10000000&((data)<<28))
#define DC_MEM_OTHER_INT_x_overflow_int_src(data)                                    ((0x10000000&(data))>>28)
#define DC_MEM_OTHER_INT_get_x_overflow_int(data)                                    ((0x10000000&(data))>>28)
#define DC_MEM_OTHER_INT_write_enable8_shift                                         (27)
#define DC_MEM_OTHER_INT_write_enable8_mask                                          (0x08000000)
#define DC_MEM_OTHER_INT_write_enable8(data)                                         (0x08000000&((data)<<27))
#define DC_MEM_OTHER_INT_write_enable8_src(data)                                     ((0x08000000&(data))>>27)
#define DC_MEM_OTHER_INT_get_write_enable8(data)                                     ((0x08000000&(data))>>27)
#define DC_MEM_OTHER_INT_y_overflow_int_en_shift                                     (26)
#define DC_MEM_OTHER_INT_y_overflow_int_en_mask                                      (0x04000000)
#define DC_MEM_OTHER_INT_y_overflow_int_en(data)                                     (0x04000000&((data)<<26))
#define DC_MEM_OTHER_INT_y_overflow_int_en_src(data)                                 ((0x04000000&(data))>>26)
#define DC_MEM_OTHER_INT_get_y_overflow_int_en(data)                                 ((0x04000000&(data))>>26)
#define DC_MEM_OTHER_INT_write_enable7_shift                                         (25)
#define DC_MEM_OTHER_INT_write_enable7_mask                                          (0x02000000)
#define DC_MEM_OTHER_INT_write_enable7(data)                                         (0x02000000&((data)<<25))
#define DC_MEM_OTHER_INT_write_enable7_src(data)                                     ((0x02000000&(data))>>25)
#define DC_MEM_OTHER_INT_get_write_enable7(data)                                     ((0x02000000&(data))>>25)
#define DC_MEM_OTHER_INT_y_overflow_int_shift                                        (24)
#define DC_MEM_OTHER_INT_y_overflow_int_mask                                         (0x01000000)
#define DC_MEM_OTHER_INT_y_overflow_int(data)                                        (0x01000000&((data)<<24))
#define DC_MEM_OTHER_INT_y_overflow_int_src(data)                                    ((0x01000000&(data))>>24)
#define DC_MEM_OTHER_INT_get_y_overflow_int(data)                                    ((0x01000000&(data))>>24)
#define DC_MEM_OTHER_INT_write_enable6_shift                                         (23)
#define DC_MEM_OTHER_INT_write_enable6_mask                                          (0x00800000)
#define DC_MEM_OTHER_INT_write_enable6(data)                                         (0x00800000&((data)<<23))
#define DC_MEM_OTHER_INT_write_enable6_src(data)                                     ((0x00800000&(data))>>23)
#define DC_MEM_OTHER_INT_get_write_enable6(data)                                     ((0x00800000&(data))>>23)
#define DC_MEM_OTHER_INT_scramble_align_int_en_shift                                 (22)
#define DC_MEM_OTHER_INT_scramble_align_int_en_mask                                  (0x00400000)
#define DC_MEM_OTHER_INT_scramble_align_int_en(data)                                 (0x00400000&((data)<<22))
#define DC_MEM_OTHER_INT_scramble_align_int_en_src(data)                             ((0x00400000&(data))>>22)
#define DC_MEM_OTHER_INT_get_scramble_align_int_en(data)                             ((0x00400000&(data))>>22)
#define DC_MEM_OTHER_INT_write_enable5_shift                                         (21)
#define DC_MEM_OTHER_INT_write_enable5_mask                                          (0x00200000)
#define DC_MEM_OTHER_INT_write_enable5(data)                                         (0x00200000&((data)<<21))
#define DC_MEM_OTHER_INT_write_enable5_src(data)                                     ((0x00200000&(data))>>21)
#define DC_MEM_OTHER_INT_get_write_enable5(data)                                     ((0x00200000&(data))>>21)
#define DC_MEM_OTHER_INT_scramble_align_int_shift                                    (20)
#define DC_MEM_OTHER_INT_scramble_align_int_mask                                     (0x00100000)
#define DC_MEM_OTHER_INT_scramble_align_int(data)                                    (0x00100000&((data)<<20))
#define DC_MEM_OTHER_INT_scramble_align_int_src(data)                                ((0x00100000&(data))>>20)
#define DC_MEM_OTHER_INT_get_scramble_align_int(data)                                ((0x00100000&(data))>>20)
#define DC_MEM_OTHER_INT_write_enable4_shift                                         (19)
#define DC_MEM_OTHER_INT_write_enable4_mask                                          (0x00080000)
#define DC_MEM_OTHER_INT_write_enable4(data)                                         (0x00080000&((data)<<19))
#define DC_MEM_OTHER_INT_write_enable4_src(data)                                     ((0x00080000&(data))>>19)
#define DC_MEM_OTHER_INT_get_write_enable4(data)                                     ((0x00080000&(data))>>19)
#define DC_MEM_OTHER_INT_blk_picset_int_en_shift                                     (18)
#define DC_MEM_OTHER_INT_blk_picset_int_en_mask                                      (0x00040000)
#define DC_MEM_OTHER_INT_blk_picset_int_en(data)                                     (0x00040000&((data)<<18))
#define DC_MEM_OTHER_INT_blk_picset_int_en_src(data)                                 ((0x00040000&(data))>>18)
#define DC_MEM_OTHER_INT_get_blk_picset_int_en(data)                                 ((0x00040000&(data))>>18)
#define DC_MEM_OTHER_INT_write_enable3_shift                                         (17)
#define DC_MEM_OTHER_INT_write_enable3_mask                                          (0x00020000)
#define DC_MEM_OTHER_INT_write_enable3(data)                                         (0x00020000&((data)<<17))
#define DC_MEM_OTHER_INT_write_enable3_src(data)                                     ((0x00020000&(data))>>17)
#define DC_MEM_OTHER_INT_get_write_enable3(data)                                     ((0x00020000&(data))>>17)
#define DC_MEM_OTHER_INT_blk_picset_int_shift                                        (16)
#define DC_MEM_OTHER_INT_blk_picset_int_mask                                         (0x00010000)
#define DC_MEM_OTHER_INT_blk_picset_int(data)                                        (0x00010000&((data)<<16))
#define DC_MEM_OTHER_INT_blk_picset_int_src(data)                                    ((0x00010000&(data))>>16)
#define DC_MEM_OTHER_INT_get_blk_picset_int(data)                                    ((0x00010000&(data))>>16)
#define DC_MEM_OTHER_INT_write_enable2_shift                                         (12)
#define DC_MEM_OTHER_INT_write_enable2_mask                                          (0x00001000)
#define DC_MEM_OTHER_INT_write_enable2(data)                                         (0x00001000&((data)<<12))
#define DC_MEM_OTHER_INT_write_enable2_src(data)                                     ((0x00001000&(data))>>12)
#define DC_MEM_OTHER_INT_get_write_enable2(data)                                     ((0x00001000&(data))>>12)
#define DC_MEM_OTHER_INT_region_shift                                                (9)
#define DC_MEM_OTHER_INT_region_mask                                                 (0x00000E00)
#define DC_MEM_OTHER_INT_region(data)                                                (0x00000E00&((data)<<9))
#define DC_MEM_OTHER_INT_region_src(data)                                            ((0x00000E00&(data))>>9)
#define DC_MEM_OTHER_INT_get_region(data)                                            ((0x00000E00&(data))>>9)
#define DC_MEM_OTHER_INT_write_enable1_shift                                         (8)
#define DC_MEM_OTHER_INT_write_enable1_mask                                          (0x00000100)
#define DC_MEM_OTHER_INT_write_enable1(data)                                         (0x00000100&((data)<<8))
#define DC_MEM_OTHER_INT_write_enable1_src(data)                                     ((0x00000100&(data))>>8)
#define DC_MEM_OTHER_INT_get_write_enable1(data)                                     ((0x00000100&(data))>>8)
#define DC_MEM_OTHER_INT_pict_set_num_shift                                          (0)
#define DC_MEM_OTHER_INT_pict_set_num_mask                                           (0x000000FF)
#define DC_MEM_OTHER_INT_pict_set_num(data)                                          (0x000000FF&((data)<<0))
#define DC_MEM_OTHER_INT_pict_set_num_src(data)                                      ((0x000000FF&(data))>>0)
#define DC_MEM_OTHER_INT_get_pict_set_num(data)                                      ((0x000000FF&(data))>>0)


#define DC_INT_SEL                                                                   0x18008758
#define DC_INT_SEL_reg_addr                                                          "0xB8008758"
#define DC_INT_SEL_reg                                                               0xB8008758
#define set_DC_INT_SEL_reg(data)   (*((volatile unsigned int*) DC_INT_SEL_reg)=data)
#define get_DC_INT_SEL_reg   (*((volatile unsigned int*) DC_INT_SEL_reg))
#define DC_INT_SEL_inst_adr                                                          "0x00D6"
#define DC_INT_SEL_inst                                                              0x00D6
#define DC_INT_SEL_blk_overflow_k_en_shift                                           (7)
#define DC_INT_SEL_blk_overflow_k_en_mask                                            (0x00000080)
#define DC_INT_SEL_blk_overflow_k_en(data)                                           (0x00000080&((data)<<7))
#define DC_INT_SEL_blk_overflow_k_en_src(data)                                       ((0x00000080&(data))>>7)
#define DC_INT_SEL_get_blk_overflow_k_en(data)                                       ((0x00000080&(data))>>7)
#define DC_INT_SEL_blk_overflow_s_en_shift                                           (6)
#define DC_INT_SEL_blk_overflow_s_en_mask                                            (0x00000040)
#define DC_INT_SEL_blk_overflow_s_en(data)                                           (0x00000040&((data)<<6))
#define DC_INT_SEL_blk_overflow_s_en_src(data)                                       ((0x00000040&(data))>>6)
#define DC_INT_SEL_get_blk_overflow_s_en(data)                                       ((0x00000040&(data))>>6)
#define DC_INT_SEL_blk_protect_k_en_shift                                            (5)
#define DC_INT_SEL_blk_protect_k_en_mask                                             (0x00000020)
#define DC_INT_SEL_blk_protect_k_en(data)                                            (0x00000020&((data)<<5))
#define DC_INT_SEL_blk_protect_k_en_src(data)                                        ((0x00000020&(data))>>5)
#define DC_INT_SEL_get_blk_protect_k_en(data)                                        ((0x00000020&(data))>>5)
#define DC_INT_SEL_blk_protect_s_en_shift                                            (4)
#define DC_INT_SEL_blk_protect_s_en_mask                                             (0x00000010)
#define DC_INT_SEL_blk_protect_s_en(data)                                            (0x00000010&((data)<<4))
#define DC_INT_SEL_blk_protect_s_en_src(data)                                        ((0x00000010&(data))>>4)
#define DC_INT_SEL_get_blk_protect_s_en(data)                                        ((0x00000010&(data))>>4)
#define DC_INT_SEL_error_k_en_shift                                                  (3)
#define DC_INT_SEL_error_k_en_mask                                                   (0x00000008)
#define DC_INT_SEL_error_k_en(data)                                                  (0x00000008&((data)<<3))
#define DC_INT_SEL_error_k_en_src(data)                                              ((0x00000008&(data))>>3)
#define DC_INT_SEL_get_error_k_en(data)                                              ((0x00000008&(data))>>3)
#define DC_INT_SEL_error_s_en_shift                                                  (2)
#define DC_INT_SEL_error_s_en_mask                                                   (0x00000004)
#define DC_INT_SEL_error_s_en(data)                                                  (0x00000004&((data)<<2))
#define DC_INT_SEL_error_s_en_src(data)                                              ((0x00000004&(data))>>2)
#define DC_INT_SEL_get_error_s_en(data)                                              ((0x00000004&(data))>>2)
#define DC_INT_SEL_mem_trash_k_en_shift                                              (1)
#define DC_INT_SEL_mem_trash_k_en_mask                                               (0x00000002)
#define DC_INT_SEL_mem_trash_k_en(data)                                              (0x00000002&((data)<<1))
#define DC_INT_SEL_mem_trash_k_en_src(data)                                          ((0x00000002&(data))>>1)
#define DC_INT_SEL_get_mem_trash_k_en(data)                                          ((0x00000002&(data))>>1)
#define DC_INT_SEL_mem_trash_s_en_shift                                              (0)
#define DC_INT_SEL_mem_trash_s_en_mask                                               (0x00000001)
#define DC_INT_SEL_mem_trash_s_en(data)                                              (0x00000001&((data)<<0))
#define DC_INT_SEL_mem_trash_s_en_src(data)                                          ((0x00000001&(data))>>0)
#define DC_INT_SEL_get_mem_trash_s_en(data)                                          ((0x00000001&(data))>>0)


#endif
