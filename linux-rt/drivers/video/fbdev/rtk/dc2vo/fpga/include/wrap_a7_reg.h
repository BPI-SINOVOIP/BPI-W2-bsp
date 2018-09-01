/**************************************************************
// Spec Version                  : unknown
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/7/21 2:27:52
***************************************************************/


#ifndef _WRAP_A7_REG_H_INCLUDED_
#define _WRAP_A7_REG_H_INCLUDED_
#ifdef  _WRAP_A7_USE_STRUCT
typedef struct 
{
unsigned int     dc_remote_wdata_num:4;
unsigned int     dc_remote_cmd_num:4;
unsigned int     dbus_wr_conti_thresh:4;
unsigned int     dbus_rd_conti_thresh:4;
unsigned int     reserved_0:1;
unsigned int     dbus_rw_reorder_en:1;
unsigned int     wcmd_bufable_sel:2;
unsigned int     wr_outstand_num:4;
unsigned int     reserved_1:3;
unsigned int     rd_outstand_num:5;
}WRAP_CTRL;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     scpu_dbg_sel_top:4;
unsigned int     reserved_1:5;
unsigned int     scpu_dbg_mode_sel:3;
unsigned int     scpu_dbg_sel_cp:4;
unsigned int     scpu_dbg_sel_dc:4;
unsigned int     scpu_dbg_sel_sb2:4;
unsigned int     scpu_dbg_sel:4;
}A7_DEBUG_CTRL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     loop_en_sw:1;
unsigned int     loop_en_src:1;
}A7_TEST_LOOP_ENABLE;

typedef struct 
{
unsigned int     data_0:32;
}DUMMY;

typedef struct 
{
unsigned int     data_1:32;
}DUMMY;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     EVENTI:1;
unsigned int     reserved_1:3;
unsigned int     CLKENTRC:1;
unsigned int     CLKENAPB:1;
unsigned int     CLKENATB:1;
unsigned int     CLKENAPBCS:1;
unsigned int     CLKENATBCS:1;
unsigned int     reserved_2:3;
unsigned int     nSOCDEBUGRESET:1;
unsigned int     nETMRESET:2;
unsigned int     nDBGRESET:2;
unsigned int     reserved_3:2;
unsigned int     nCORERESET:2;
unsigned int     reserved_4:1;
unsigned int     nCOREPORESET:1;
unsigned int     nL2RESET:1;
unsigned int     L2RSTDISABLE:1;
}A7_CTRL;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     EVENTO:1;
unsigned int     reserved_1:10;
unsigned int     STANDBYWFIL2:1;
unsigned int     STANDBYWFE:2;
unsigned int     STANDBYWFI:2;
}A7_STAT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     AXIERRIRQ:1;
unsigned int     reserved_1:5;
unsigned int     PMUIRQ:2;
}A7_STAT;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     cfgsdisable_i:1;
unsigned int     cp15disable_i:2;
}A7_SEC_CTRL;

typedef struct 
{
unsigned int     TRACKCLK_SEL:16;
unsigned int     reserved_0:13;
unsigned int     TRACKCLK_DCLK_SEL:1;
unsigned int     reserved_1:2;
}A7_TRACKCLK_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     TSCLKCHANGE:1;
}A7_TSCLK_CTRL;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     data_in:20;
unsigned int     reserved_1:2;
unsigned int     speed_en:1;
unsigned int     wire_sel:1;
unsigned int     ro_sel:3;
unsigned int     dss_rst_n:1;
}A7_DSS_C35_12D5T_CTRL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     count_out:20;
unsigned int     reserved_1:2;
unsigned int     wsort_go:1;
unsigned int     ready:1;
}A7_DSS_C35_12D5T_STATUS;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     dbgo:16;
}A7_DSS_C35_12D5T_DEBUG;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     data_in:20;
unsigned int     reserved_1:2;
unsigned int     speed_en:1;
unsigned int     wire_sel:1;
unsigned int     ro_sel:3;
unsigned int     dss_rst_n:1;
}A7_DSS_C35D5_12D5T_CTRL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     count_out:20;
unsigned int     reserved_1:2;
unsigned int     wsort_go:1;
unsigned int     ready:1;
}A7_DSS_C35D5_12D5T_STATUS;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     dbgo:16;
}A7_DSS_C35D5_12D5T_DEBUG;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     data_sel:2;
unsigned int     addr:4;
unsigned int     read_en:1;
unsigned int     hold:1;
unsigned int     csm_en:1;
unsigned int     acc_mode:1;
unsigned int     in_sel:2;
unsigned int     reserved_1:1;
unsigned int     rstn:1;
}A7_CSM0_CTRL;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     data_sel:2;
unsigned int     addr:4;
unsigned int     read_en:1;
unsigned int     hold:1;
unsigned int     csm_en:1;
unsigned int     acc_mode:1;
unsigned int     in_sel:2;
unsigned int     reserved_1:1;
unsigned int     rstn:1;
}A7_CSM1_CTRL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     csm1_ready:1;
unsigned int     csm0_ready:1;
}A7_CSM_STATUS;

typedef struct 
{
unsigned int     data_output:32;
}A7_CSM0_DO_STATUS;

typedef struct 
{
unsigned int     data_output:32;
}A7_CSM1_DO_STATUS;

typedef struct 
{
unsigned int     dbg_start_addr_m1:32;
}DBG_START;

typedef struct 
{
unsigned int     dbg_end_addr_m1:32;
}DBG_END;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     write_en2:1;
unsigned int     dbg_wr_chk_m1:2;
unsigned int     write_en1:1;
unsigned int     dbg_en_m1:1;
}DBG_CTRL;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     scpu_int_m1:1;
unsigned int     scpu_int_en_m1:1;
unsigned int     scpu_neg_int_m1:1;
unsigned int     scpu_neg_int_en_m1:1;
unsigned int     write_data:1;
}DBG_INT;

typedef struct 
{
unsigned int     dbg_addr_m1:32;
}DBG_ADDR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     scpu_dbg_write_m1:1;
}DBG_ADDR1;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     scu_mbist_mode:1;
unsigned int     idata_mbist_mode:1;
unsigned int     itag_mbist_mode:1;
unsigned int     ddata_mbist_mode:1;
unsigned int     dtag_mbist_mode:1;
unsigned int     ddrity_mbist_mode:1;
unsigned int     tlb_mbist_mode:1;
}BIST_MODE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     drf_mbist_mode:1;
}DRF_BIST_MODE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     drf_test_resume:1;
}DRF_TEST_RESUME;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     MBISTACK:1;
unsigned int     scu_mbist_done:1;
unsigned int     idata_mbist_done:1;
unsigned int     itag_mbist_done:1;
unsigned int     ddata_mbist_done:1;
unsigned int     dtag_mbist_done:1;
unsigned int     ddirty_mbist_done:1;
unsigned int     tlb_mbist_done:1;
}CPU_BIST_DONE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     drf_mbist_done:1;
}CPU_DRF_BIST_DONE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     drf_start_pause:1;
}CPU_DRF_START_PAUSE;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     cpu0_scu_mbist_fail_G:1;
unsigned int     cpu0_idata_mbist_fail_G:1;
unsigned int     cpu0_itag_mbist_fail_G:1;
unsigned int     cpu0_ddata_mbist_fail_G:1;
unsigned int     cpu0_dtag_mbist_fail_G:1;
unsigned int     cpu0_ddrity_mbist_fail_G:1;
unsigned int     cpu0_tlb_mbist_fail_G:1;
}CPU0_BIST_FAIL_GROUP;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     cpu1_scu_mbist_fail_G:1;
unsigned int     cpu1_idata_mbist_fail_G:1;
unsigned int     cpu1_itag_mbist_fail_G:1;
unsigned int     cpu1_ddata_mbist_fail_G:1;
unsigned int     cpu1_dtag_mbist_fail_G:1;
unsigned int     cpu1_ddrity_mbist_fail_G:1;
unsigned int     cpu1_tlb_mbist_fail_G:1;
}CPU1_BIST_FAIL_GROUP;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     cpu0_scu_drf_mbist_fail_G:1;
unsigned int     cpu0_idata_drf_mbist_fail_G:1;
unsigned int     cpu0_itag_drf_mbist_fail_G:1;
unsigned int     cpu0_ddata_drf_mbist_fail_G:1;
unsigned int     cpu0_dtag_drf_mbist_fail_G:1;
unsigned int     cpu0_ddrity_drf_mbist_fail_G:1;
unsigned int     cpu0_tlb_drf_mbist_fail_G:1;
}CPU0_DRF_BIST_FAIL_GROUP;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     cpu1_scu_drf_mbist_fail_G:1;
unsigned int     cpu1_idata_drf_mbist_fail_G:1;
unsigned int     cpu1_itag_drf_mbist_fail_G:1;
unsigned int     cpu1_ddata_drf_mbist_fail_G:1;
unsigned int     cpu1_dtag_drf_mbist_fail_G:1;
unsigned int     cpu1_ddrity_drf_mbist_fail_G:1;
unsigned int     cpu1_tlb_drf_mbist_fail_G:1;
}CPU1_DRF_BIST_FAIL_GROUP;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     cpu0_idata_mbist_fail:2;
}CPU0_IDATA_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     cpu1_idata_mbist_fail:2;
}CPU1_IDATA_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     cpu0_idata_drf_mbist_fail:2;
}CPU0_IDATA_DRF_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     cpu1_idata_drf_mbist_fail:2;
}CPU1_IDATA_DRF_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     cpu0_itag_mbist_fail:2;
}CPU0_ITAG_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     cpu1_itag_mbist_fail:2;
}CPU1_ITAG_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     cpu0_itag_drf_mbist_fail:2;
}CPU0_ITAG_DRF_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     cpu1_itag_drf_mbist_fail:2;
}CPU1_ITAG_DRF_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     cpu0_ddata_mbist_fail:8;
}CPU0_DDATA_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     cpu1_ddata_mbist_fail:8;
}CPU1_DDATA_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     cpu0_ddata_drf_mbist_fail:8;
}CPU0_DDATA_DRF_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     cpu1_ddata_drf_mbist_fail:8;
}CPU1_DDATA_DRF_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     cpu0_dtag_mbist_fail:4;
}CPU0_DTAG_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     cpu1_dtag_mbist_fail:4;
}CPU1_DTAG_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     cpu0_dtag_drf_mbist_fail:4;
}CPU0_DTAG_DRF_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     cpu1_dtag_drf_mbist_fail:4;
}CPU1_DTAG_DRF_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     cpu0_ddrity_mbist_fail:1;
}CPU0_DDRITY_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     cpu1_ddrity_mbist_fail:1;
}CPU1_DDRITY_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     cpu0_ddrity_drf_mbist_fail:1;
}CPU0_DDRITY_DRF_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     cpu1_ddrity_drf_mbist_fail:1;
}CPU1_DDRITY_DRF_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     cpu0_scu_mbist_fail:4;
}CPU0_SCU_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     cpu1_scu_mbist_fail:4;
}CPU1_SCU_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     cpu0_scu_drf_mbist_fail:4;
}CPU0_SCU_DRF_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     cpu1_scu_drf_mbist_fail:4;
}CPU1_SCU_DRF_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     cpu0_tlb_mbist_fail:2;
}CPU0_TLB_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     cpu1_tlb_mbist_fail:2;
}CPU1_TLB_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     cpu0_tlb_drf_mbist_fail:2;
}CPU0_TLB_DRF_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     cpu1_tlb_drf_mbist_fail:2;
}CPU1_TLB_DRF_BIST_FAIL;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     MBIST_RSTN:1;
unsigned int     L2_TAG_BIST_RSTN:1;
unsigned int     L2_DATA_PWR_RSTN:1;
unsigned int     L2_DATA_BISR_RSTN:1;
}L2_BIST_BISR_RSTN;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     L2_DATA_HOLD_REMAP:1;
}HOLD_REMAP;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     L2_DATA_SECOND_RUN_EN:1;
}SECOND_RUN_EN;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     L2_TAG_BIST_MODE:1;
unsigned int     L2_TAG_DRF_BIST_MODE:1;
unsigned int     reserved_1:1;
unsigned int     L2_DATA_DRF_BISR_MODE:1;
}DRF_BIST_BISR_MODE;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     L2_TAG_DRF_TEST_RESUME:1;
unsigned int     L2_DATA_DRF_BISR_TEST_RESUME:1;
}DRF_BISR_TEST_RESUME;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     L2_DATA_BISR_REPAIRED:1;
}BISR_REPAIR;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     L2_TAG_BIST_DONE:1;
unsigned int     L2_DATA_BISR_DONE:1;
}BISR_DONE;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     L2_TAG_DRF_BIST_DONE:1;
unsigned int     L2_DATA_DRF_BISR_DONE:1;
}DRF_BISR_DONE;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     L2_TAG_DRF_START_PAUSE:1;
unsigned int     L2_DATA_DRF_BISR_START_PAUSE:1;
}DRF_START_PAUSE;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     L2_TAG_BIST_FAIL_G:1;
unsigned int     L2_DATA_BISR_FAIL_G:1;
}BISR_FAIL_GROUP;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     L2_DATA_BISR_FAIL:8;
}BISR_FAIL_DATA_SEP;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     L2_TAG_BIST_FAIL:8;
}BISR_FAIL_TAG_SEP;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     L2_TAG_DRF_BIST_FAIL_G:1;
unsigned int     L2_DATA_DRF_BISR_FAIL_G:1;
}DRF_BISR_FAIL_GROUP;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     L2_DATA_DRF_BISR_FAIL:8;
}DRF_BISR_FAIL_DATA_SEP;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     L2_TAG_DRF_BIST_FAIL:8;
}DRF_BISR_FAIL_TAG_SEP;

typedef struct 
{
unsigned int     L2_DATA_BISR_OUT_31_0:32;
}L2_DATA_BISR_OUT_1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     L2_DATA_BISR_OUT_55_32:24;
}L2_DATA_BISR_OUT_2;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     scu_ram_RME:1;
unsigned int     idata_ram_RME:1;
unsigned int     itag_ram_RME:1;
unsigned int     ddata_ram_RME:1;
unsigned int     dtag_ram_RME:1;
unsigned int     ddrity_ram_RME:1;
unsigned int     tlb_ram_RME:1;
}SRAM_RME;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     scu_ram_RM:4;
unsigned int     idata_ram_RM:4;
unsigned int     itag_ram_RM:4;
unsigned int     ddata_ram_RM:4;
unsigned int     dtag_ram_RM:4;
unsigned int     ddrity_ram_RM:4;
unsigned int     tlb_ram_RM:4;
}SRAM_RM;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     RME_L2_TAG:1;
unsigned int     RME_L2_DATA:1;
}L2_SRAM_RME;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     RM_L2_TAG:4;
unsigned int     RM_L2_DATA:4;
}L2_SRAM_RM;

#endif

#define WRAP_CTRL                                                                    0x1801D000
#define WRAP_CTRL_reg_addr                                                           "0xB801D000"
#define WRAP_CTRL_reg                                                                0xB801D000
#define set_WRAP_CTRL_reg(data)   (*((volatile unsigned int*) WRAP_CTRL_reg)=data)
#define get_WRAP_CTRL_reg   (*((volatile unsigned int*) WRAP_CTRL_reg))
#define WRAP_CTRL_inst_adr                                                           "0x0000"
#define WRAP_CTRL_inst                                                               0x0000
#define WRAP_CTRL_dc_remote_wdata_num_shift                                          (28)
#define WRAP_CTRL_dc_remote_wdata_num_mask                                           (0xF0000000)
#define WRAP_CTRL_dc_remote_wdata_num(data)                                          (0xF0000000&((data)<<28))
#define WRAP_CTRL_dc_remote_wdata_num_src(data)                                      ((0xF0000000&(data))>>28)
#define WRAP_CTRL_get_dc_remote_wdata_num(data)                                      ((0xF0000000&(data))>>28)
#define WRAP_CTRL_dc_remote_cmd_num_shift                                            (24)
#define WRAP_CTRL_dc_remote_cmd_num_mask                                             (0x0F000000)
#define WRAP_CTRL_dc_remote_cmd_num(data)                                            (0x0F000000&((data)<<24))
#define WRAP_CTRL_dc_remote_cmd_num_src(data)                                        ((0x0F000000&(data))>>24)
#define WRAP_CTRL_get_dc_remote_cmd_num(data)                                        ((0x0F000000&(data))>>24)
#define WRAP_CTRL_dbus_wr_conti_thresh_shift                                         (20)
#define WRAP_CTRL_dbus_wr_conti_thresh_mask                                          (0x00F00000)
#define WRAP_CTRL_dbus_wr_conti_thresh(data)                                         (0x00F00000&((data)<<20))
#define WRAP_CTRL_dbus_wr_conti_thresh_src(data)                                     ((0x00F00000&(data))>>20)
#define WRAP_CTRL_get_dbus_wr_conti_thresh(data)                                     ((0x00F00000&(data))>>20)
#define WRAP_CTRL_dbus_rd_conti_thresh_shift                                         (16)
#define WRAP_CTRL_dbus_rd_conti_thresh_mask                                          (0x000F0000)
#define WRAP_CTRL_dbus_rd_conti_thresh(data)                                         (0x000F0000&((data)<<16))
#define WRAP_CTRL_dbus_rd_conti_thresh_src(data)                                     ((0x000F0000&(data))>>16)
#define WRAP_CTRL_get_dbus_rd_conti_thresh(data)                                     ((0x000F0000&(data))>>16)
#define WRAP_CTRL_dbus_rw_reorder_en_shift                                           (14)
#define WRAP_CTRL_dbus_rw_reorder_en_mask                                            (0x00004000)
#define WRAP_CTRL_dbus_rw_reorder_en(data)                                           (0x00004000&((data)<<14))
#define WRAP_CTRL_dbus_rw_reorder_en_src(data)                                       ((0x00004000&(data))>>14)
#define WRAP_CTRL_get_dbus_rw_reorder_en(data)                                       ((0x00004000&(data))>>14)
#define WRAP_CTRL_wcmd_bufable_sel_shift                                             (12)
#define WRAP_CTRL_wcmd_bufable_sel_mask                                              (0x00003000)
#define WRAP_CTRL_wcmd_bufable_sel(data)                                             (0x00003000&((data)<<12))
#define WRAP_CTRL_wcmd_bufable_sel_src(data)                                         ((0x00003000&(data))>>12)
#define WRAP_CTRL_get_wcmd_bufable_sel(data)                                         ((0x00003000&(data))>>12)
#define WRAP_CTRL_wr_outstand_num_shift                                              (8)
#define WRAP_CTRL_wr_outstand_num_mask                                               (0x00000F00)
#define WRAP_CTRL_wr_outstand_num(data)                                              (0x00000F00&((data)<<8))
#define WRAP_CTRL_wr_outstand_num_src(data)                                          ((0x00000F00&(data))>>8)
#define WRAP_CTRL_get_wr_outstand_num(data)                                          ((0x00000F00&(data))>>8)
#define WRAP_CTRL_rd_outstand_num_shift                                              (0)
#define WRAP_CTRL_rd_outstand_num_mask                                               (0x0000001F)
#define WRAP_CTRL_rd_outstand_num(data)                                              (0x0000001F&((data)<<0))
#define WRAP_CTRL_rd_outstand_num_src(data)                                          ((0x0000001F&(data))>>0)
#define WRAP_CTRL_get_rd_outstand_num(data)                                          ((0x0000001F&(data))>>0)


#define A7_DEBUG_CTRL                                                                0x1801D004
#define A7_DEBUG_CTRL_reg_addr                                                       "0xB801D004"
#define A7_DEBUG_CTRL_reg                                                            0xB801D004
#define set_A7_DEBUG_CTRL_reg(data)   (*((volatile unsigned int*) A7_DEBUG_CTRL_reg)=data)
#define get_A7_DEBUG_CTRL_reg   (*((volatile unsigned int*) A7_DEBUG_CTRL_reg))
#define A7_DEBUG_CTRL_inst_adr                                                       "0x0001"
#define A7_DEBUG_CTRL_inst                                                           0x0001
#define A7_DEBUG_CTRL_scpu_dbg_sel_top_shift                                         (24)
#define A7_DEBUG_CTRL_scpu_dbg_sel_top_mask                                          (0x0F000000)
#define A7_DEBUG_CTRL_scpu_dbg_sel_top(data)                                         (0x0F000000&((data)<<24))
#define A7_DEBUG_CTRL_scpu_dbg_sel_top_src(data)                                     ((0x0F000000&(data))>>24)
#define A7_DEBUG_CTRL_get_scpu_dbg_sel_top(data)                                     ((0x0F000000&(data))>>24)
#define A7_DEBUG_CTRL_scpu_dbg_mode_sel_shift                                        (16)
#define A7_DEBUG_CTRL_scpu_dbg_mode_sel_mask                                         (0x00070000)
#define A7_DEBUG_CTRL_scpu_dbg_mode_sel(data)                                        (0x00070000&((data)<<16))
#define A7_DEBUG_CTRL_scpu_dbg_mode_sel_src(data)                                    ((0x00070000&(data))>>16)
#define A7_DEBUG_CTRL_get_scpu_dbg_mode_sel(data)                                    ((0x00070000&(data))>>16)
#define A7_DEBUG_CTRL_scpu_dbg_sel_cp_shift                                          (12)
#define A7_DEBUG_CTRL_scpu_dbg_sel_cp_mask                                           (0x0000F000)
#define A7_DEBUG_CTRL_scpu_dbg_sel_cp(data)                                          (0x0000F000&((data)<<12))
#define A7_DEBUG_CTRL_scpu_dbg_sel_cp_src(data)                                      ((0x0000F000&(data))>>12)
#define A7_DEBUG_CTRL_get_scpu_dbg_sel_cp(data)                                      ((0x0000F000&(data))>>12)
#define A7_DEBUG_CTRL_scpu_dbg_sel_dc_shift                                          (8)
#define A7_DEBUG_CTRL_scpu_dbg_sel_dc_mask                                           (0x00000F00)
#define A7_DEBUG_CTRL_scpu_dbg_sel_dc(data)                                          (0x00000F00&((data)<<8))
#define A7_DEBUG_CTRL_scpu_dbg_sel_dc_src(data)                                      ((0x00000F00&(data))>>8)
#define A7_DEBUG_CTRL_get_scpu_dbg_sel_dc(data)                                      ((0x00000F00&(data))>>8)
#define A7_DEBUG_CTRL_scpu_dbg_sel_sb2_shift                                         (4)
#define A7_DEBUG_CTRL_scpu_dbg_sel_sb2_mask                                          (0x000000F0)
#define A7_DEBUG_CTRL_scpu_dbg_sel_sb2(data)                                         (0x000000F0&((data)<<4))
#define A7_DEBUG_CTRL_scpu_dbg_sel_sb2_src(data)                                     ((0x000000F0&(data))>>4)
#define A7_DEBUG_CTRL_get_scpu_dbg_sel_sb2(data)                                     ((0x000000F0&(data))>>4)
#define A7_DEBUG_CTRL_scpu_dbg_sel_shift                                             (0)
#define A7_DEBUG_CTRL_scpu_dbg_sel_mask                                              (0x0000000F)
#define A7_DEBUG_CTRL_scpu_dbg_sel(data)                                             (0x0000000F&((data)<<0))
#define A7_DEBUG_CTRL_scpu_dbg_sel_src(data)                                         ((0x0000000F&(data))>>0)
#define A7_DEBUG_CTRL_get_scpu_dbg_sel(data)                                         ((0x0000000F&(data))>>0)


#define A7_TEST_LOOP_ENABLE                                                          0x1801D008
#define A7_TEST_LOOP_ENABLE_reg_addr                                                 "0xB801D008"
#define A7_TEST_LOOP_ENABLE_reg                                                      0xB801D008
#define set_A7_TEST_LOOP_ENABLE_reg(data)   (*((volatile unsigned int*) A7_TEST_LOOP_ENABLE_reg)=data)
#define get_A7_TEST_LOOP_ENABLE_reg   (*((volatile unsigned int*) A7_TEST_LOOP_ENABLE_reg))
#define A7_TEST_LOOP_ENABLE_inst_adr                                                 "0x0002"
#define A7_TEST_LOOP_ENABLE_inst                                                     0x0002
#define A7_TEST_LOOP_ENABLE_loop_en_sw_shift                                         (1)
#define A7_TEST_LOOP_ENABLE_loop_en_sw_mask                                          (0x00000002)
#define A7_TEST_LOOP_ENABLE_loop_en_sw(data)                                         (0x00000002&((data)<<1))
#define A7_TEST_LOOP_ENABLE_loop_en_sw_src(data)                                     ((0x00000002&(data))>>1)
#define A7_TEST_LOOP_ENABLE_get_loop_en_sw(data)                                     ((0x00000002&(data))>>1)
#define A7_TEST_LOOP_ENABLE_loop_en_src_shift                                        (0)
#define A7_TEST_LOOP_ENABLE_loop_en_src_mask                                         (0x00000001)
#define A7_TEST_LOOP_ENABLE_loop_en_src(data)                                        (0x00000001&((data)<<0))
#define A7_TEST_LOOP_ENABLE_loop_en_src_src(data)                                    ((0x00000001&(data))>>0)
#define A7_TEST_LOOP_ENABLE_get_loop_en_src(data)                                    ((0x00000001&(data))>>0)


#define DUMMY_0                                                                      0x1801D010
#define DUMMY_1                                                                      0x1801D014
#define DUMMY_0_reg_addr                                                             "0xB801D010"
#define DUMMY_1_reg_addr                                                             "0xB801D014"
#define DUMMY_0_reg                                                                  0xB801D010
#define DUMMY_1_reg                                                                  0xB801D014
#define set_DUMMY_0_reg(data)   (*((volatile unsigned int*) DUMMY_0_reg)=data)
#define set_DUMMY_1_reg(data)   (*((volatile unsigned int*) DUMMY_1_reg)=data)
#define get_DUMMY_0_reg   (*((volatile unsigned int*) DUMMY_0_reg))
#define get_DUMMY_1_reg   (*((volatile unsigned int*) DUMMY_1_reg))
#define DUMMY_0_inst_adr                                                             "0x0004"
#define DUMMY_1_inst_adr                                                             "0x0005"
#define DUMMY_0_inst                                                                 0x0004
#define DUMMY_1_inst                                                                 0x0005
#define DUMMY_data_0_shift                                                           (0)
#define DUMMY_data_0_mask                                                            (0xFFFFFFFF)
#define DUMMY_data_0(data)                                                           (0xFFFFFFFF&((data)<<0))
#define DUMMY_data_0_src(data)                                                       ((0xFFFFFFFF&(data))>>0)
#define DUMMY_get_data_0(data)                                                       ((0xFFFFFFFF&(data))>>0)


#define DUMMY_0                                                                      0x1801D018
#define DUMMY_1                                                                      0x1801D01C
#define DUMMY_0_reg_addr                                                             "0xB801D018"
#define DUMMY_1_reg_addr                                                             "0xB801D01C"
#define DUMMY_0_reg                                                                  0xB801D018
#define DUMMY_1_reg                                                                  0xB801D01C
#define set_DUMMY_0_reg(data)   (*((volatile unsigned int*) DUMMY_0_reg)=data)
#define set_DUMMY_1_reg(data)   (*((volatile unsigned int*) DUMMY_1_reg)=data)
#define get_DUMMY_0_reg   (*((volatile unsigned int*) DUMMY_0_reg))
#define get_DUMMY_1_reg   (*((volatile unsigned int*) DUMMY_1_reg))
#define DUMMY_0_inst_adr                                                             "0x0006"
#define DUMMY_1_inst_adr                                                             "0x0007"
#define DUMMY_0_inst                                                                 0x0006
#define DUMMY_1_inst                                                                 0x0007
#define DUMMY_data_1_shift                                                           (0)
#define DUMMY_data_1_mask                                                            (0xFFFFFFFF)
#define DUMMY_data_1(data)                                                           (0xFFFFFFFF&((data)<<0))
#define DUMMY_data_1_src(data)                                                       ((0xFFFFFFFF&(data))>>0)
#define DUMMY_get_data_1(data)                                                       ((0xFFFFFFFF&(data))>>0)


#define A7_CTRL                                                                      0x1801D100
#define A7_CTRL_reg_addr                                                             "0xB801D100"
#define A7_CTRL_reg                                                                  0xB801D100
#define set_A7_CTRL_reg(data)   (*((volatile unsigned int*) A7_CTRL_reg)=data)
#define get_A7_CTRL_reg   (*((volatile unsigned int*) A7_CTRL_reg))
#define A7_CTRL_inst_adr                                                             "0x0040"
#define A7_CTRL_inst                                                                 0x0040
#define A7_CTRL_EVENTI_shift                                                         (24)
#define A7_CTRL_EVENTI_mask                                                          (0x01000000)
#define A7_CTRL_EVENTI(data)                                                         (0x01000000&((data)<<24))
#define A7_CTRL_EVENTI_src(data)                                                     ((0x01000000&(data))>>24)
#define A7_CTRL_get_EVENTI(data)                                                     ((0x01000000&(data))>>24)
#define A7_CTRL_CLKENTRC_shift                                                       (20)
#define A7_CTRL_CLKENTRC_mask                                                        (0x00100000)
#define A7_CTRL_CLKENTRC(data)                                                       (0x00100000&((data)<<20))
#define A7_CTRL_CLKENTRC_src(data)                                                   ((0x00100000&(data))>>20)
#define A7_CTRL_get_CLKENTRC(data)                                                   ((0x00100000&(data))>>20)
#define A7_CTRL_CLKENAPB_shift                                                       (19)
#define A7_CTRL_CLKENAPB_mask                                                        (0x00080000)
#define A7_CTRL_CLKENAPB(data)                                                       (0x00080000&((data)<<19))
#define A7_CTRL_CLKENAPB_src(data)                                                   ((0x00080000&(data))>>19)
#define A7_CTRL_get_CLKENAPB(data)                                                   ((0x00080000&(data))>>19)
#define A7_CTRL_CLKENATB_shift                                                       (18)
#define A7_CTRL_CLKENATB_mask                                                        (0x00040000)
#define A7_CTRL_CLKENATB(data)                                                       (0x00040000&((data)<<18))
#define A7_CTRL_CLKENATB_src(data)                                                   ((0x00040000&(data))>>18)
#define A7_CTRL_get_CLKENATB(data)                                                   ((0x00040000&(data))>>18)
#define A7_CTRL_CLKENAPBCS_shift                                                     (17)
#define A7_CTRL_CLKENAPBCS_mask                                                      (0x00020000)
#define A7_CTRL_CLKENAPBCS(data)                                                     (0x00020000&((data)<<17))
#define A7_CTRL_CLKENAPBCS_src(data)                                                 ((0x00020000&(data))>>17)
#define A7_CTRL_get_CLKENAPBCS(data)                                                 ((0x00020000&(data))>>17)
#define A7_CTRL_CLKENATBCS_shift                                                     (16)
#define A7_CTRL_CLKENATBCS_mask                                                      (0x00010000)
#define A7_CTRL_CLKENATBCS(data)                                                     (0x00010000&((data)<<16))
#define A7_CTRL_CLKENATBCS_src(data)                                                 ((0x00010000&(data))>>16)
#define A7_CTRL_get_CLKENATBCS(data)                                                 ((0x00010000&(data))>>16)
#define A7_CTRL_nSOCDEBUGRESET_shift                                                 (12)
#define A7_CTRL_nSOCDEBUGRESET_mask                                                  (0x00001000)
#define A7_CTRL_nSOCDEBUGRESET(data)                                                 (0x00001000&((data)<<12))
#define A7_CTRL_nSOCDEBUGRESET_src(data)                                             ((0x00001000&(data))>>12)
#define A7_CTRL_get_nSOCDEBUGRESET(data)                                             ((0x00001000&(data))>>12)
#define A7_CTRL_nETMRESET_shift                                                      (10)
#define A7_CTRL_nETMRESET_mask                                                       (0x00000C00)
#define A7_CTRL_nETMRESET(data)                                                      (0x00000C00&((data)<<10))
#define A7_CTRL_nETMRESET_src(data)                                                  ((0x00000C00&(data))>>10)
#define A7_CTRL_get_nETMRESET(data)                                                  ((0x00000C00&(data))>>10)
#define A7_CTRL_nDBGRESET_shift                                                      (8)
#define A7_CTRL_nDBGRESET_mask                                                       (0x00000300)
#define A7_CTRL_nDBGRESET(data)                                                      (0x00000300&((data)<<8))
#define A7_CTRL_nDBGRESET_src(data)                                                  ((0x00000300&(data))>>8)
#define A7_CTRL_get_nDBGRESET(data)                                                  ((0x00000300&(data))>>8)
#define A7_CTRL_nCORERESET_shift                                                     (4)
#define A7_CTRL_nCORERESET_mask                                                      (0x00000030)
#define A7_CTRL_nCORERESET(data)                                                     (0x00000030&((data)<<4))
#define A7_CTRL_nCORERESET_src(data)                                                 ((0x00000030&(data))>>4)
#define A7_CTRL_get_nCORERESET(data)                                                 ((0x00000030&(data))>>4)
#define A7_CTRL_nCOREPORESET_shift                                                   (2)
#define A7_CTRL_nCOREPORESET_mask                                                    (0x00000004)
#define A7_CTRL_nCOREPORESET(data)                                                   (0x00000004&((data)<<2))
#define A7_CTRL_nCOREPORESET_src(data)                                               ((0x00000004&(data))>>2)
#define A7_CTRL_get_nCOREPORESET(data)                                               ((0x00000004&(data))>>2)
#define A7_CTRL_nL2RESET_shift                                                       (1)
#define A7_CTRL_nL2RESET_mask                                                        (0x00000002)
#define A7_CTRL_nL2RESET(data)                                                       (0x00000002&((data)<<1))
#define A7_CTRL_nL2RESET_src(data)                                                   ((0x00000002&(data))>>1)
#define A7_CTRL_get_nL2RESET(data)                                                   ((0x00000002&(data))>>1)
#define A7_CTRL_L2RSTDISABLE_shift                                                   (0)
#define A7_CTRL_L2RSTDISABLE_mask                                                    (0x00000001)
#define A7_CTRL_L2RSTDISABLE(data)                                                   (0x00000001&((data)<<0))
#define A7_CTRL_L2RSTDISABLE_src(data)                                               ((0x00000001&(data))>>0)
#define A7_CTRL_get_L2RSTDISABLE(data)                                               ((0x00000001&(data))>>0)


#define A7_STAT                                                                      0x1801D104
#define A7_STAT_reg_addr                                                             "0xB801D104"
#define A7_STAT_reg                                                                  0xB801D104
#define set_A7_STAT_reg(data)   (*((volatile unsigned int*) A7_STAT_reg)=data)
#define get_A7_STAT_reg   (*((volatile unsigned int*) A7_STAT_reg))
#define A7_STAT_inst_adr                                                             "0x0041"
#define A7_STAT_inst                                                                 0x0041
#define A7_STAT_EVENTO_shift                                                         (15)
#define A7_STAT_EVENTO_mask                                                          (0x00008000)
#define A7_STAT_EVENTO(data)                                                         (0x00008000&((data)<<15))
#define A7_STAT_EVENTO_src(data)                                                     ((0x00008000&(data))>>15)
#define A7_STAT_get_EVENTO(data)                                                     ((0x00008000&(data))>>15)
#define A7_STAT_STANDBYWFIL2_shift                                                   (4)
#define A7_STAT_STANDBYWFIL2_mask                                                    (0x00000010)
#define A7_STAT_STANDBYWFIL2(data)                                                   (0x00000010&((data)<<4))
#define A7_STAT_STANDBYWFIL2_src(data)                                               ((0x00000010&(data))>>4)
#define A7_STAT_get_STANDBYWFIL2(data)                                               ((0x00000010&(data))>>4)
#define A7_STAT_STANDBYWFE_shift                                                     (2)
#define A7_STAT_STANDBYWFE_mask                                                      (0x0000000C)
#define A7_STAT_STANDBYWFE(data)                                                     (0x0000000C&((data)<<2))
#define A7_STAT_STANDBYWFE_src(data)                                                 ((0x0000000C&(data))>>2)
#define A7_STAT_get_STANDBYWFE(data)                                                 ((0x0000000C&(data))>>2)
#define A7_STAT_STANDBYWFI_shift                                                     (0)
#define A7_STAT_STANDBYWFI_mask                                                      (0x00000003)
#define A7_STAT_STANDBYWFI(data)                                                     (0x00000003&((data)<<0))
#define A7_STAT_STANDBYWFI_src(data)                                                 ((0x00000003&(data))>>0)
#define A7_STAT_get_STANDBYWFI(data)                                                 ((0x00000003&(data))>>0)


#define A7_STAT                                                                      0x1801D108
#define A7_STAT_reg_addr                                                             "0xB801D108"
#define A7_STAT_reg                                                                  0xB801D108
#define set_A7_STAT_reg(data)   (*((volatile unsigned int*) A7_STAT_reg)=data)
#define get_A7_STAT_reg   (*((volatile unsigned int*) A7_STAT_reg))
#define A7_STAT_inst_adr                                                             "0x0042"
#define A7_STAT_inst                                                                 0x0042
#define A7_STAT_AXIERRIRQ_shift                                                      (7)
#define A7_STAT_AXIERRIRQ_mask                                                       (0x00000080)
#define A7_STAT_AXIERRIRQ(data)                                                      (0x00000080&((data)<<7))
#define A7_STAT_AXIERRIRQ_src(data)                                                  ((0x00000080&(data))>>7)
#define A7_STAT_get_AXIERRIRQ(data)                                                  ((0x00000080&(data))>>7)
#define A7_STAT_PMUIRQ_shift                                                         (0)
#define A7_STAT_PMUIRQ_mask                                                          (0x00000003)
#define A7_STAT_PMUIRQ(data)                                                         (0x00000003&((data)<<0))
#define A7_STAT_PMUIRQ_src(data)                                                     ((0x00000003&(data))>>0)
#define A7_STAT_get_PMUIRQ(data)                                                     ((0x00000003&(data))>>0)


#define A7_SEC_CTRL                                                                  0x1801D10C
#define A7_SEC_CTRL_reg_addr                                                         "0xB801D10C"
#define A7_SEC_CTRL_reg                                                              0xB801D10C
#define set_A7_SEC_CTRL_reg(data)   (*((volatile unsigned int*) A7_SEC_CTRL_reg)=data)
#define get_A7_SEC_CTRL_reg   (*((volatile unsigned int*) A7_SEC_CTRL_reg))
#define A7_SEC_CTRL_inst_adr                                                         "0x0043"
#define A7_SEC_CTRL_inst                                                             0x0043
#define A7_SEC_CTRL_cfgsdisable_i_shift                                              (2)
#define A7_SEC_CTRL_cfgsdisable_i_mask                                               (0x00000004)
#define A7_SEC_CTRL_cfgsdisable_i(data)                                              (0x00000004&((data)<<2))
#define A7_SEC_CTRL_cfgsdisable_i_src(data)                                          ((0x00000004&(data))>>2)
#define A7_SEC_CTRL_get_cfgsdisable_i(data)                                          ((0x00000004&(data))>>2)
#define A7_SEC_CTRL_cp15disable_i_shift                                              (0)
#define A7_SEC_CTRL_cp15disable_i_mask                                               (0x00000003)
#define A7_SEC_CTRL_cp15disable_i(data)                                              (0x00000003&((data)<<0))
#define A7_SEC_CTRL_cp15disable_i_src(data)                                          ((0x00000003&(data))>>0)
#define A7_SEC_CTRL_get_cp15disable_i(data)                                          ((0x00000003&(data))>>0)


#define A7_TRACKCLK_CTRL                                                             0x1801D110
#define A7_TRACKCLK_CTRL_reg_addr                                                    "0xB801D110"
#define A7_TRACKCLK_CTRL_reg                                                         0xB801D110
#define set_A7_TRACKCLK_CTRL_reg(data)   (*((volatile unsigned int*) A7_TRACKCLK_CTRL_reg)=data)
#define get_A7_TRACKCLK_CTRL_reg   (*((volatile unsigned int*) A7_TRACKCLK_CTRL_reg))
#define A7_TRACKCLK_CTRL_inst_adr                                                    "0x0044"
#define A7_TRACKCLK_CTRL_inst                                                        0x0044
#define A7_TRACKCLK_CTRL_TRACKCLK_SEL_shift                                          (16)
#define A7_TRACKCLK_CTRL_TRACKCLK_SEL_mask                                           (0xFFFF0000)
#define A7_TRACKCLK_CTRL_TRACKCLK_SEL(data)                                          (0xFFFF0000&((data)<<16))
#define A7_TRACKCLK_CTRL_TRACKCLK_SEL_src(data)                                      ((0xFFFF0000&(data))>>16)
#define A7_TRACKCLK_CTRL_get_TRACKCLK_SEL(data)                                      ((0xFFFF0000&(data))>>16)
#define A7_TRACKCLK_CTRL_TRACKCLK_DCLK_SEL_shift                                     (2)
#define A7_TRACKCLK_CTRL_TRACKCLK_DCLK_SEL_mask                                      (0x00000004)
#define A7_TRACKCLK_CTRL_TRACKCLK_DCLK_SEL(data)                                     (0x00000004&((data)<<2))
#define A7_TRACKCLK_CTRL_TRACKCLK_DCLK_SEL_src(data)                                 ((0x00000004&(data))>>2)
#define A7_TRACKCLK_CTRL_get_TRACKCLK_DCLK_SEL(data)                                 ((0x00000004&(data))>>2)


#define A7_TSCLK_CTRL                                                                0x1801D114
#define A7_TSCLK_CTRL_reg_addr                                                       "0xB801D114"
#define A7_TSCLK_CTRL_reg                                                            0xB801D114
#define set_A7_TSCLK_CTRL_reg(data)   (*((volatile unsigned int*) A7_TSCLK_CTRL_reg)=data)
#define get_A7_TSCLK_CTRL_reg   (*((volatile unsigned int*) A7_TSCLK_CTRL_reg))
#define A7_TSCLK_CTRL_inst_adr                                                       "0x0045"
#define A7_TSCLK_CTRL_inst                                                           0x0045
#define A7_TSCLK_CTRL_TSCLKCHANGE_shift                                              (0)
#define A7_TSCLK_CTRL_TSCLKCHANGE_mask                                               (0x00000001)
#define A7_TSCLK_CTRL_TSCLKCHANGE(data)                                              (0x00000001&((data)<<0))
#define A7_TSCLK_CTRL_TSCLKCHANGE_src(data)                                          ((0x00000001&(data))>>0)
#define A7_TSCLK_CTRL_get_TSCLKCHANGE(data)                                          ((0x00000001&(data))>>0)


#define A7_DSS_C35_12D5T_CTRL                                                        0x1801D120
#define A7_DSS_C35_12D5T_CTRL_reg_addr                                               "0xB801D120"
#define A7_DSS_C35_12D5T_CTRL_reg                                                    0xB801D120
#define set_A7_DSS_C35_12D5T_CTRL_reg(data)   (*((volatile unsigned int*) A7_DSS_C35_12D5T_CTRL_reg)=data)
#define get_A7_DSS_C35_12D5T_CTRL_reg   (*((volatile unsigned int*) A7_DSS_C35_12D5T_CTRL_reg))
#define A7_DSS_C35_12D5T_CTRL_inst_adr                                               "0x0048"
#define A7_DSS_C35_12D5T_CTRL_inst                                                   0x0048
#define A7_DSS_C35_12D5T_CTRL_data_in_shift                                          (8)
#define A7_DSS_C35_12D5T_CTRL_data_in_mask                                           (0x0FFFFF00)
#define A7_DSS_C35_12D5T_CTRL_data_in(data)                                          (0x0FFFFF00&((data)<<8))
#define A7_DSS_C35_12D5T_CTRL_data_in_src(data)                                      ((0x0FFFFF00&(data))>>8)
#define A7_DSS_C35_12D5T_CTRL_get_data_in(data)                                      ((0x0FFFFF00&(data))>>8)
#define A7_DSS_C35_12D5T_CTRL_speed_en_shift                                         (5)
#define A7_DSS_C35_12D5T_CTRL_speed_en_mask                                          (0x00000020)
#define A7_DSS_C35_12D5T_CTRL_speed_en(data)                                         (0x00000020&((data)<<5))
#define A7_DSS_C35_12D5T_CTRL_speed_en_src(data)                                     ((0x00000020&(data))>>5)
#define A7_DSS_C35_12D5T_CTRL_get_speed_en(data)                                     ((0x00000020&(data))>>5)
#define A7_DSS_C35_12D5T_CTRL_wire_sel_shift                                         (4)
#define A7_DSS_C35_12D5T_CTRL_wire_sel_mask                                          (0x00000010)
#define A7_DSS_C35_12D5T_CTRL_wire_sel(data)                                         (0x00000010&((data)<<4))
#define A7_DSS_C35_12D5T_CTRL_wire_sel_src(data)                                     ((0x00000010&(data))>>4)
#define A7_DSS_C35_12D5T_CTRL_get_wire_sel(data)                                     ((0x00000010&(data))>>4)
#define A7_DSS_C35_12D5T_CTRL_ro_sel_shift                                           (1)
#define A7_DSS_C35_12D5T_CTRL_ro_sel_mask                                            (0x0000000E)
#define A7_DSS_C35_12D5T_CTRL_ro_sel(data)                                           (0x0000000E&((data)<<1))
#define A7_DSS_C35_12D5T_CTRL_ro_sel_src(data)                                       ((0x0000000E&(data))>>1)
#define A7_DSS_C35_12D5T_CTRL_get_ro_sel(data)                                       ((0x0000000E&(data))>>1)
#define A7_DSS_C35_12D5T_CTRL_dss_rst_n_shift                                        (0)
#define A7_DSS_C35_12D5T_CTRL_dss_rst_n_mask                                         (0x00000001)
#define A7_DSS_C35_12D5T_CTRL_dss_rst_n(data)                                        (0x00000001&((data)<<0))
#define A7_DSS_C35_12D5T_CTRL_dss_rst_n_src(data)                                    ((0x00000001&(data))>>0)
#define A7_DSS_C35_12D5T_CTRL_get_dss_rst_n(data)                                    ((0x00000001&(data))>>0)


#define A7_DSS_C35_12D5T_STATUS                                                      0x1801D124
#define A7_DSS_C35_12D5T_STATUS_reg_addr                                             "0xB801D124"
#define A7_DSS_C35_12D5T_STATUS_reg                                                  0xB801D124
#define set_A7_DSS_C35_12D5T_STATUS_reg(data)   (*((volatile unsigned int*) A7_DSS_C35_12D5T_STATUS_reg)=data)
#define get_A7_DSS_C35_12D5T_STATUS_reg   (*((volatile unsigned int*) A7_DSS_C35_12D5T_STATUS_reg))
#define A7_DSS_C35_12D5T_STATUS_inst_adr                                             "0x0049"
#define A7_DSS_C35_12D5T_STATUS_inst                                                 0x0049
#define A7_DSS_C35_12D5T_STATUS_count_out_shift                                      (4)
#define A7_DSS_C35_12D5T_STATUS_count_out_mask                                       (0x00FFFFF0)
#define A7_DSS_C35_12D5T_STATUS_count_out(data)                                      (0x00FFFFF0&((data)<<4))
#define A7_DSS_C35_12D5T_STATUS_count_out_src(data)                                  ((0x00FFFFF0&(data))>>4)
#define A7_DSS_C35_12D5T_STATUS_get_count_out(data)                                  ((0x00FFFFF0&(data))>>4)
#define A7_DSS_C35_12D5T_STATUS_wsort_go_shift                                       (1)
#define A7_DSS_C35_12D5T_STATUS_wsort_go_mask                                        (0x00000002)
#define A7_DSS_C35_12D5T_STATUS_wsort_go(data)                                       (0x00000002&((data)<<1))
#define A7_DSS_C35_12D5T_STATUS_wsort_go_src(data)                                   ((0x00000002&(data))>>1)
#define A7_DSS_C35_12D5T_STATUS_get_wsort_go(data)                                   ((0x00000002&(data))>>1)
#define A7_DSS_C35_12D5T_STATUS_ready_shift                                          (0)
#define A7_DSS_C35_12D5T_STATUS_ready_mask                                           (0x00000001)
#define A7_DSS_C35_12D5T_STATUS_ready(data)                                          (0x00000001&((data)<<0))
#define A7_DSS_C35_12D5T_STATUS_ready_src(data)                                      ((0x00000001&(data))>>0)
#define A7_DSS_C35_12D5T_STATUS_get_ready(data)                                      ((0x00000001&(data))>>0)


#define A7_DSS_C35_12D5T_DEBUG                                                       0x1801D128
#define A7_DSS_C35_12D5T_DEBUG_reg_addr                                              "0xB801D128"
#define A7_DSS_C35_12D5T_DEBUG_reg                                                   0xB801D128
#define set_A7_DSS_C35_12D5T_DEBUG_reg(data)   (*((volatile unsigned int*) A7_DSS_C35_12D5T_DEBUG_reg)=data)
#define get_A7_DSS_C35_12D5T_DEBUG_reg   (*((volatile unsigned int*) A7_DSS_C35_12D5T_DEBUG_reg))
#define A7_DSS_C35_12D5T_DEBUG_inst_adr                                              "0x004A"
#define A7_DSS_C35_12D5T_DEBUG_inst                                                  0x004A
#define A7_DSS_C35_12D5T_DEBUG_dbgo_shift                                            (0)
#define A7_DSS_C35_12D5T_DEBUG_dbgo_mask                                             (0x0000FFFF)
#define A7_DSS_C35_12D5T_DEBUG_dbgo(data)                                            (0x0000FFFF&((data)<<0))
#define A7_DSS_C35_12D5T_DEBUG_dbgo_src(data)                                        ((0x0000FFFF&(data))>>0)
#define A7_DSS_C35_12D5T_DEBUG_get_dbgo(data)                                        ((0x0000FFFF&(data))>>0)


#define A7_DSS_C35D5_12D5T_CTRL                                                      0x1801D130
#define A7_DSS_C35D5_12D5T_CTRL_reg_addr                                             "0xB801D130"
#define A7_DSS_C35D5_12D5T_CTRL_reg                                                  0xB801D130
#define set_A7_DSS_C35D5_12D5T_CTRL_reg(data)   (*((volatile unsigned int*) A7_DSS_C35D5_12D5T_CTRL_reg)=data)
#define get_A7_DSS_C35D5_12D5T_CTRL_reg   (*((volatile unsigned int*) A7_DSS_C35D5_12D5T_CTRL_reg))
#define A7_DSS_C35D5_12D5T_CTRL_inst_adr                                             "0x004C"
#define A7_DSS_C35D5_12D5T_CTRL_inst                                                 0x004C
#define A7_DSS_C35D5_12D5T_CTRL_data_in_shift                                        (8)
#define A7_DSS_C35D5_12D5T_CTRL_data_in_mask                                         (0x0FFFFF00)
#define A7_DSS_C35D5_12D5T_CTRL_data_in(data)                                        (0x0FFFFF00&((data)<<8))
#define A7_DSS_C35D5_12D5T_CTRL_data_in_src(data)                                    ((0x0FFFFF00&(data))>>8)
#define A7_DSS_C35D5_12D5T_CTRL_get_data_in(data)                                    ((0x0FFFFF00&(data))>>8)
#define A7_DSS_C35D5_12D5T_CTRL_speed_en_shift                                       (5)
#define A7_DSS_C35D5_12D5T_CTRL_speed_en_mask                                        (0x00000020)
#define A7_DSS_C35D5_12D5T_CTRL_speed_en(data)                                       (0x00000020&((data)<<5))
#define A7_DSS_C35D5_12D5T_CTRL_speed_en_src(data)                                   ((0x00000020&(data))>>5)
#define A7_DSS_C35D5_12D5T_CTRL_get_speed_en(data)                                   ((0x00000020&(data))>>5)
#define A7_DSS_C35D5_12D5T_CTRL_wire_sel_shift                                       (4)
#define A7_DSS_C35D5_12D5T_CTRL_wire_sel_mask                                        (0x00000010)
#define A7_DSS_C35D5_12D5T_CTRL_wire_sel(data)                                       (0x00000010&((data)<<4))
#define A7_DSS_C35D5_12D5T_CTRL_wire_sel_src(data)                                   ((0x00000010&(data))>>4)
#define A7_DSS_C35D5_12D5T_CTRL_get_wire_sel(data)                                   ((0x00000010&(data))>>4)
#define A7_DSS_C35D5_12D5T_CTRL_ro_sel_shift                                         (1)
#define A7_DSS_C35D5_12D5T_CTRL_ro_sel_mask                                          (0x0000000E)
#define A7_DSS_C35D5_12D5T_CTRL_ro_sel(data)                                         (0x0000000E&((data)<<1))
#define A7_DSS_C35D5_12D5T_CTRL_ro_sel_src(data)                                     ((0x0000000E&(data))>>1)
#define A7_DSS_C35D5_12D5T_CTRL_get_ro_sel(data)                                     ((0x0000000E&(data))>>1)
#define A7_DSS_C35D5_12D5T_CTRL_dss_rst_n_shift                                      (0)
#define A7_DSS_C35D5_12D5T_CTRL_dss_rst_n_mask                                       (0x00000001)
#define A7_DSS_C35D5_12D5T_CTRL_dss_rst_n(data)                                      (0x00000001&((data)<<0))
#define A7_DSS_C35D5_12D5T_CTRL_dss_rst_n_src(data)                                  ((0x00000001&(data))>>0)
#define A7_DSS_C35D5_12D5T_CTRL_get_dss_rst_n(data)                                  ((0x00000001&(data))>>0)


#define A7_DSS_C35D5_12D5T_STATUS                                                    0x1801D134
#define A7_DSS_C35D5_12D5T_STATUS_reg_addr                                           "0xB801D134"
#define A7_DSS_C35D5_12D5T_STATUS_reg                                                0xB801D134
#define set_A7_DSS_C35D5_12D5T_STATUS_reg(data)   (*((volatile unsigned int*) A7_DSS_C35D5_12D5T_STATUS_reg)=data)
#define get_A7_DSS_C35D5_12D5T_STATUS_reg   (*((volatile unsigned int*) A7_DSS_C35D5_12D5T_STATUS_reg))
#define A7_DSS_C35D5_12D5T_STATUS_inst_adr                                           "0x004D"
#define A7_DSS_C35D5_12D5T_STATUS_inst                                               0x004D
#define A7_DSS_C35D5_12D5T_STATUS_count_out_shift                                    (4)
#define A7_DSS_C35D5_12D5T_STATUS_count_out_mask                                     (0x00FFFFF0)
#define A7_DSS_C35D5_12D5T_STATUS_count_out(data)                                    (0x00FFFFF0&((data)<<4))
#define A7_DSS_C35D5_12D5T_STATUS_count_out_src(data)                                ((0x00FFFFF0&(data))>>4)
#define A7_DSS_C35D5_12D5T_STATUS_get_count_out(data)                                ((0x00FFFFF0&(data))>>4)
#define A7_DSS_C35D5_12D5T_STATUS_wsort_go_shift                                     (1)
#define A7_DSS_C35D5_12D5T_STATUS_wsort_go_mask                                      (0x00000002)
#define A7_DSS_C35D5_12D5T_STATUS_wsort_go(data)                                     (0x00000002&((data)<<1))
#define A7_DSS_C35D5_12D5T_STATUS_wsort_go_src(data)                                 ((0x00000002&(data))>>1)
#define A7_DSS_C35D5_12D5T_STATUS_get_wsort_go(data)                                 ((0x00000002&(data))>>1)
#define A7_DSS_C35D5_12D5T_STATUS_ready_shift                                        (0)
#define A7_DSS_C35D5_12D5T_STATUS_ready_mask                                         (0x00000001)
#define A7_DSS_C35D5_12D5T_STATUS_ready(data)                                        (0x00000001&((data)<<0))
#define A7_DSS_C35D5_12D5T_STATUS_ready_src(data)                                    ((0x00000001&(data))>>0)
#define A7_DSS_C35D5_12D5T_STATUS_get_ready(data)                                    ((0x00000001&(data))>>0)


#define A7_DSS_C35D5_12D5T_DEBUG                                                     0x1801D138
#define A7_DSS_C35D5_12D5T_DEBUG_reg_addr                                            "0xB801D138"
#define A7_DSS_C35D5_12D5T_DEBUG_reg                                                 0xB801D138
#define set_A7_DSS_C35D5_12D5T_DEBUG_reg(data)   (*((volatile unsigned int*) A7_DSS_C35D5_12D5T_DEBUG_reg)=data)
#define get_A7_DSS_C35D5_12D5T_DEBUG_reg   (*((volatile unsigned int*) A7_DSS_C35D5_12D5T_DEBUG_reg))
#define A7_DSS_C35D5_12D5T_DEBUG_inst_adr                                            "0x004E"
#define A7_DSS_C35D5_12D5T_DEBUG_inst                                                0x004E
#define A7_DSS_C35D5_12D5T_DEBUG_dbgo_shift                                          (0)
#define A7_DSS_C35D5_12D5T_DEBUG_dbgo_mask                                           (0x0000FFFF)
#define A7_DSS_C35D5_12D5T_DEBUG_dbgo(data)                                          (0x0000FFFF&((data)<<0))
#define A7_DSS_C35D5_12D5T_DEBUG_dbgo_src(data)                                      ((0x0000FFFF&(data))>>0)
#define A7_DSS_C35D5_12D5T_DEBUG_get_dbgo(data)                                      ((0x0000FFFF&(data))>>0)


#define A7_CSM0_CTRL                                                                 0x1801D140
#define A7_CSM0_CTRL_reg_addr                                                        "0xB801D140"
#define A7_CSM0_CTRL_reg                                                             0xB801D140
#define set_A7_CSM0_CTRL_reg(data)   (*((volatile unsigned int*) A7_CSM0_CTRL_reg)=data)
#define get_A7_CSM0_CTRL_reg   (*((volatile unsigned int*) A7_CSM0_CTRL_reg))
#define A7_CSM0_CTRL_inst_adr                                                        "0x0050"
#define A7_CSM0_CTRL_inst                                                            0x0050
#define A7_CSM0_CTRL_data_sel_shift                                                  (12)
#define A7_CSM0_CTRL_data_sel_mask                                                   (0x00003000)
#define A7_CSM0_CTRL_data_sel(data)                                                  (0x00003000&((data)<<12))
#define A7_CSM0_CTRL_data_sel_src(data)                                              ((0x00003000&(data))>>12)
#define A7_CSM0_CTRL_get_data_sel(data)                                              ((0x00003000&(data))>>12)
#define A7_CSM0_CTRL_addr_shift                                                      (8)
#define A7_CSM0_CTRL_addr_mask                                                       (0x00000F00)
#define A7_CSM0_CTRL_addr(data)                                                      (0x00000F00&((data)<<8))
#define A7_CSM0_CTRL_addr_src(data)                                                  ((0x00000F00&(data))>>8)
#define A7_CSM0_CTRL_get_addr(data)                                                  ((0x00000F00&(data))>>8)
#define A7_CSM0_CTRL_read_en_shift                                                   (7)
#define A7_CSM0_CTRL_read_en_mask                                                    (0x00000080)
#define A7_CSM0_CTRL_read_en(data)                                                   (0x00000080&((data)<<7))
#define A7_CSM0_CTRL_read_en_src(data)                                               ((0x00000080&(data))>>7)
#define A7_CSM0_CTRL_get_read_en(data)                                               ((0x00000080&(data))>>7)
#define A7_CSM0_CTRL_hold_shift                                                      (6)
#define A7_CSM0_CTRL_hold_mask                                                       (0x00000040)
#define A7_CSM0_CTRL_hold(data)                                                      (0x00000040&((data)<<6))
#define A7_CSM0_CTRL_hold_src(data)                                                  ((0x00000040&(data))>>6)
#define A7_CSM0_CTRL_get_hold(data)                                                  ((0x00000040&(data))>>6)
#define A7_CSM0_CTRL_csm_en_shift                                                    (5)
#define A7_CSM0_CTRL_csm_en_mask                                                     (0x00000020)
#define A7_CSM0_CTRL_csm_en(data)                                                    (0x00000020&((data)<<5))
#define A7_CSM0_CTRL_csm_en_src(data)                                                ((0x00000020&(data))>>5)
#define A7_CSM0_CTRL_get_csm_en(data)                                                ((0x00000020&(data))>>5)
#define A7_CSM0_CTRL_acc_mode_shift                                                  (4)
#define A7_CSM0_CTRL_acc_mode_mask                                                   (0x00000010)
#define A7_CSM0_CTRL_acc_mode(data)                                                  (0x00000010&((data)<<4))
#define A7_CSM0_CTRL_acc_mode_src(data)                                              ((0x00000010&(data))>>4)
#define A7_CSM0_CTRL_get_acc_mode(data)                                              ((0x00000010&(data))>>4)
#define A7_CSM0_CTRL_in_sel_shift                                                    (2)
#define A7_CSM0_CTRL_in_sel_mask                                                     (0x0000000C)
#define A7_CSM0_CTRL_in_sel(data)                                                    (0x0000000C&((data)<<2))
#define A7_CSM0_CTRL_in_sel_src(data)                                                ((0x0000000C&(data))>>2)
#define A7_CSM0_CTRL_get_in_sel(data)                                                ((0x0000000C&(data))>>2)
#define A7_CSM0_CTRL_rstn_shift                                                      (0)
#define A7_CSM0_CTRL_rstn_mask                                                       (0x00000001)
#define A7_CSM0_CTRL_rstn(data)                                                      (0x00000001&((data)<<0))
#define A7_CSM0_CTRL_rstn_src(data)                                                  ((0x00000001&(data))>>0)
#define A7_CSM0_CTRL_get_rstn(data)                                                  ((0x00000001&(data))>>0)


#define A7_CSM1_CTRL                                                                 0x1801D144
#define A7_CSM1_CTRL_reg_addr                                                        "0xB801D144"
#define A7_CSM1_CTRL_reg                                                             0xB801D144
#define set_A7_CSM1_CTRL_reg(data)   (*((volatile unsigned int*) A7_CSM1_CTRL_reg)=data)
#define get_A7_CSM1_CTRL_reg   (*((volatile unsigned int*) A7_CSM1_CTRL_reg))
#define A7_CSM1_CTRL_inst_adr                                                        "0x0051"
#define A7_CSM1_CTRL_inst                                                            0x0051
#define A7_CSM1_CTRL_data_sel_shift                                                  (12)
#define A7_CSM1_CTRL_data_sel_mask                                                   (0x00003000)
#define A7_CSM1_CTRL_data_sel(data)                                                  (0x00003000&((data)<<12))
#define A7_CSM1_CTRL_data_sel_src(data)                                              ((0x00003000&(data))>>12)
#define A7_CSM1_CTRL_get_data_sel(data)                                              ((0x00003000&(data))>>12)
#define A7_CSM1_CTRL_addr_shift                                                      (8)
#define A7_CSM1_CTRL_addr_mask                                                       (0x00000F00)
#define A7_CSM1_CTRL_addr(data)                                                      (0x00000F00&((data)<<8))
#define A7_CSM1_CTRL_addr_src(data)                                                  ((0x00000F00&(data))>>8)
#define A7_CSM1_CTRL_get_addr(data)                                                  ((0x00000F00&(data))>>8)
#define A7_CSM1_CTRL_read_en_shift                                                   (7)
#define A7_CSM1_CTRL_read_en_mask                                                    (0x00000080)
#define A7_CSM1_CTRL_read_en(data)                                                   (0x00000080&((data)<<7))
#define A7_CSM1_CTRL_read_en_src(data)                                               ((0x00000080&(data))>>7)
#define A7_CSM1_CTRL_get_read_en(data)                                               ((0x00000080&(data))>>7)
#define A7_CSM1_CTRL_hold_shift                                                      (6)
#define A7_CSM1_CTRL_hold_mask                                                       (0x00000040)
#define A7_CSM1_CTRL_hold(data)                                                      (0x00000040&((data)<<6))
#define A7_CSM1_CTRL_hold_src(data)                                                  ((0x00000040&(data))>>6)
#define A7_CSM1_CTRL_get_hold(data)                                                  ((0x00000040&(data))>>6)
#define A7_CSM1_CTRL_csm_en_shift                                                    (5)
#define A7_CSM1_CTRL_csm_en_mask                                                     (0x00000020)
#define A7_CSM1_CTRL_csm_en(data)                                                    (0x00000020&((data)<<5))
#define A7_CSM1_CTRL_csm_en_src(data)                                                ((0x00000020&(data))>>5)
#define A7_CSM1_CTRL_get_csm_en(data)                                                ((0x00000020&(data))>>5)
#define A7_CSM1_CTRL_acc_mode_shift                                                  (4)
#define A7_CSM1_CTRL_acc_mode_mask                                                   (0x00000010)
#define A7_CSM1_CTRL_acc_mode(data)                                                  (0x00000010&((data)<<4))
#define A7_CSM1_CTRL_acc_mode_src(data)                                              ((0x00000010&(data))>>4)
#define A7_CSM1_CTRL_get_acc_mode(data)                                              ((0x00000010&(data))>>4)
#define A7_CSM1_CTRL_in_sel_shift                                                    (2)
#define A7_CSM1_CTRL_in_sel_mask                                                     (0x0000000C)
#define A7_CSM1_CTRL_in_sel(data)                                                    (0x0000000C&((data)<<2))
#define A7_CSM1_CTRL_in_sel_src(data)                                                ((0x0000000C&(data))>>2)
#define A7_CSM1_CTRL_get_in_sel(data)                                                ((0x0000000C&(data))>>2)
#define A7_CSM1_CTRL_rstn_shift                                                      (0)
#define A7_CSM1_CTRL_rstn_mask                                                       (0x00000001)
#define A7_CSM1_CTRL_rstn(data)                                                      (0x00000001&((data)<<0))
#define A7_CSM1_CTRL_rstn_src(data)                                                  ((0x00000001&(data))>>0)
#define A7_CSM1_CTRL_get_rstn(data)                                                  ((0x00000001&(data))>>0)


#define A7_CSM_STATUS                                                                0x1801D148
#define A7_CSM_STATUS_reg_addr                                                       "0xB801D148"
#define A7_CSM_STATUS_reg                                                            0xB801D148
#define set_A7_CSM_STATUS_reg(data)   (*((volatile unsigned int*) A7_CSM_STATUS_reg)=data)
#define get_A7_CSM_STATUS_reg   (*((volatile unsigned int*) A7_CSM_STATUS_reg))
#define A7_CSM_STATUS_inst_adr                                                       "0x0052"
#define A7_CSM_STATUS_inst                                                           0x0052
#define A7_CSM_STATUS_csm1_ready_shift                                               (1)
#define A7_CSM_STATUS_csm1_ready_mask                                                (0x00000002)
#define A7_CSM_STATUS_csm1_ready(data)                                               (0x00000002&((data)<<1))
#define A7_CSM_STATUS_csm1_ready_src(data)                                           ((0x00000002&(data))>>1)
#define A7_CSM_STATUS_get_csm1_ready(data)                                           ((0x00000002&(data))>>1)
#define A7_CSM_STATUS_csm0_ready_shift                                               (0)
#define A7_CSM_STATUS_csm0_ready_mask                                                (0x00000001)
#define A7_CSM_STATUS_csm0_ready(data)                                               (0x00000001&((data)<<0))
#define A7_CSM_STATUS_csm0_ready_src(data)                                           ((0x00000001&(data))>>0)
#define A7_CSM_STATUS_get_csm0_ready(data)                                           ((0x00000001&(data))>>0)


#define A7_CSM0_DO_STATUS                                                            0x1801D150
#define A7_CSM0_DO_STATUS_reg_addr                                                   "0xB801D150"
#define A7_CSM0_DO_STATUS_reg                                                        0xB801D150
#define set_A7_CSM0_DO_STATUS_reg(data)   (*((volatile unsigned int*) A7_CSM0_DO_STATUS_reg)=data)
#define get_A7_CSM0_DO_STATUS_reg   (*((volatile unsigned int*) A7_CSM0_DO_STATUS_reg))
#define A7_CSM0_DO_STATUS_inst_adr                                                   "0x0054"
#define A7_CSM0_DO_STATUS_inst                                                       0x0054
#define A7_CSM0_DO_STATUS_data_output_shift                                          (0)
#define A7_CSM0_DO_STATUS_data_output_mask                                           (0xFFFFFFFF)
#define A7_CSM0_DO_STATUS_data_output(data)                                          (0xFFFFFFFF&((data)<<0))
#define A7_CSM0_DO_STATUS_data_output_src(data)                                      ((0xFFFFFFFF&(data))>>0)
#define A7_CSM0_DO_STATUS_get_data_output(data)                                      ((0xFFFFFFFF&(data))>>0)


#define A7_CSM1_DO_STATUS                                                            0x1801D154
#define A7_CSM1_DO_STATUS_reg_addr                                                   "0xB801D154"
#define A7_CSM1_DO_STATUS_reg                                                        0xB801D154
#define set_A7_CSM1_DO_STATUS_reg(data)   (*((volatile unsigned int*) A7_CSM1_DO_STATUS_reg)=data)
#define get_A7_CSM1_DO_STATUS_reg   (*((volatile unsigned int*) A7_CSM1_DO_STATUS_reg))
#define A7_CSM1_DO_STATUS_inst_adr                                                   "0x0055"
#define A7_CSM1_DO_STATUS_inst                                                       0x0055
#define A7_CSM1_DO_STATUS_data_output_shift                                          (0)
#define A7_CSM1_DO_STATUS_data_output_mask                                           (0xFFFFFFFF)
#define A7_CSM1_DO_STATUS_data_output(data)                                          (0xFFFFFFFF&((data)<<0))
#define A7_CSM1_DO_STATUS_data_output_src(data)                                      ((0xFFFFFFFF&(data))>>0)
#define A7_CSM1_DO_STATUS_get_data_output(data)                                      ((0xFFFFFFFF&(data))>>0)


#define DBG_START_0                                                                  0x1801D200
#define DBG_START_1                                                                  0x1801D204
#define DBG_START_2                                                                  0x1801D208
#define DBG_START_3                                                                  0x1801D20C
#define DBG_START_0_reg_addr                                                         "0xB801D200"
#define DBG_START_1_reg_addr                                                         "0xB801D204"
#define DBG_START_2_reg_addr                                                         "0xB801D208"
#define DBG_START_3_reg_addr                                                         "0xB801D20C"
#define DBG_START_0_reg                                                              0xB801D200
#define DBG_START_1_reg                                                              0xB801D204
#define DBG_START_2_reg                                                              0xB801D208
#define DBG_START_3_reg                                                              0xB801D20C
#define set_DBG_START_0_reg(data)   (*((volatile unsigned int*) DBG_START_0_reg)=data)
#define set_DBG_START_1_reg(data)   (*((volatile unsigned int*) DBG_START_1_reg)=data)
#define set_DBG_START_2_reg(data)   (*((volatile unsigned int*) DBG_START_2_reg)=data)
#define set_DBG_START_3_reg(data)   (*((volatile unsigned int*) DBG_START_3_reg)=data)
#define get_DBG_START_0_reg   (*((volatile unsigned int*) DBG_START_0_reg))
#define get_DBG_START_1_reg   (*((volatile unsigned int*) DBG_START_1_reg))
#define get_DBG_START_2_reg   (*((volatile unsigned int*) DBG_START_2_reg))
#define get_DBG_START_3_reg   (*((volatile unsigned int*) DBG_START_3_reg))
#define DBG_START_0_inst_adr                                                         "0x0080"
#define DBG_START_1_inst_adr                                                         "0x0081"
#define DBG_START_2_inst_adr                                                         "0x0082"
#define DBG_START_3_inst_adr                                                         "0x0083"
#define DBG_START_0_inst                                                             0x0080
#define DBG_START_1_inst                                                             0x0081
#define DBG_START_2_inst                                                             0x0082
#define DBG_START_3_inst                                                             0x0083
#define DBG_START_dbg_start_addr_m1_shift                                            (0)
#define DBG_START_dbg_start_addr_m1_mask                                             (0xFFFFFFFF)
#define DBG_START_dbg_start_addr_m1(data)                                            (0xFFFFFFFF&((data)<<0))
#define DBG_START_dbg_start_addr_m1_src(data)                                        ((0xFFFFFFFF&(data))>>0)
#define DBG_START_get_dbg_start_addr_m1(data)                                        ((0xFFFFFFFF&(data))>>0)


#define DBG_END_0                                                                    0x1801D210
#define DBG_END_1                                                                    0x1801D214
#define DBG_END_2                                                                    0x1801D218
#define DBG_END_3                                                                    0x1801D21C
#define DBG_END_0_reg_addr                                                           "0xB801D210"
#define DBG_END_1_reg_addr                                                           "0xB801D214"
#define DBG_END_2_reg_addr                                                           "0xB801D218"
#define DBG_END_3_reg_addr                                                           "0xB801D21C"
#define DBG_END_0_reg                                                                0xB801D210
#define DBG_END_1_reg                                                                0xB801D214
#define DBG_END_2_reg                                                                0xB801D218
#define DBG_END_3_reg                                                                0xB801D21C
#define set_DBG_END_0_reg(data)   (*((volatile unsigned int*) DBG_END_0_reg)=data)
#define set_DBG_END_1_reg(data)   (*((volatile unsigned int*) DBG_END_1_reg)=data)
#define set_DBG_END_2_reg(data)   (*((volatile unsigned int*) DBG_END_2_reg)=data)
#define set_DBG_END_3_reg(data)   (*((volatile unsigned int*) DBG_END_3_reg)=data)
#define get_DBG_END_0_reg   (*((volatile unsigned int*) DBG_END_0_reg))
#define get_DBG_END_1_reg   (*((volatile unsigned int*) DBG_END_1_reg))
#define get_DBG_END_2_reg   (*((volatile unsigned int*) DBG_END_2_reg))
#define get_DBG_END_3_reg   (*((volatile unsigned int*) DBG_END_3_reg))
#define DBG_END_0_inst_adr                                                           "0x0084"
#define DBG_END_1_inst_adr                                                           "0x0085"
#define DBG_END_2_inst_adr                                                           "0x0086"
#define DBG_END_3_inst_adr                                                           "0x0087"
#define DBG_END_0_inst                                                               0x0084
#define DBG_END_1_inst                                                               0x0085
#define DBG_END_2_inst                                                               0x0086
#define DBG_END_3_inst                                                               0x0087
#define DBG_END_dbg_end_addr_m1_shift                                                (0)
#define DBG_END_dbg_end_addr_m1_mask                                                 (0xFFFFFFFF)
#define DBG_END_dbg_end_addr_m1(data)                                                (0xFFFFFFFF&((data)<<0))
#define DBG_END_dbg_end_addr_m1_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define DBG_END_get_dbg_end_addr_m1(data)                                            ((0xFFFFFFFF&(data))>>0)


#define DBG_CTRL_0                                                                   0x1801D220
#define DBG_CTRL_1                                                                   0x1801D224
#define DBG_CTRL_2                                                                   0x1801D228
#define DBG_CTRL_3                                                                   0x1801D22C
#define DBG_CTRL_0_reg_addr                                                          "0xB801D220"
#define DBG_CTRL_1_reg_addr                                                          "0xB801D224"
#define DBG_CTRL_2_reg_addr                                                          "0xB801D228"
#define DBG_CTRL_3_reg_addr                                                          "0xB801D22C"
#define DBG_CTRL_0_reg                                                               0xB801D220
#define DBG_CTRL_1_reg                                                               0xB801D224
#define DBG_CTRL_2_reg                                                               0xB801D228
#define DBG_CTRL_3_reg                                                               0xB801D22C
#define set_DBG_CTRL_0_reg(data)   (*((volatile unsigned int*) DBG_CTRL_0_reg)=data)
#define set_DBG_CTRL_1_reg(data)   (*((volatile unsigned int*) DBG_CTRL_1_reg)=data)
#define set_DBG_CTRL_2_reg(data)   (*((volatile unsigned int*) DBG_CTRL_2_reg)=data)
#define set_DBG_CTRL_3_reg(data)   (*((volatile unsigned int*) DBG_CTRL_3_reg)=data)
#define get_DBG_CTRL_0_reg   (*((volatile unsigned int*) DBG_CTRL_0_reg))
#define get_DBG_CTRL_1_reg   (*((volatile unsigned int*) DBG_CTRL_1_reg))
#define get_DBG_CTRL_2_reg   (*((volatile unsigned int*) DBG_CTRL_2_reg))
#define get_DBG_CTRL_3_reg   (*((volatile unsigned int*) DBG_CTRL_3_reg))
#define DBG_CTRL_0_inst_adr                                                          "0x0088"
#define DBG_CTRL_1_inst_adr                                                          "0x0089"
#define DBG_CTRL_2_inst_adr                                                          "0x008A"
#define DBG_CTRL_3_inst_adr                                                          "0x008B"
#define DBG_CTRL_0_inst                                                              0x0088
#define DBG_CTRL_1_inst                                                              0x0089
#define DBG_CTRL_2_inst                                                              0x008A
#define DBG_CTRL_3_inst                                                              0x008B
#define DBG_CTRL_write_en2_shift                                                     (4)
#define DBG_CTRL_write_en2_mask                                                      (0x00000010)
#define DBG_CTRL_write_en2(data)                                                     (0x00000010&((data)<<4))
#define DBG_CTRL_write_en2_src(data)                                                 ((0x00000010&(data))>>4)
#define DBG_CTRL_get_write_en2(data)                                                 ((0x00000010&(data))>>4)
#define DBG_CTRL_dbg_wr_chk_m1_shift                                                 (2)
#define DBG_CTRL_dbg_wr_chk_m1_mask                                                  (0x0000000C)
#define DBG_CTRL_dbg_wr_chk_m1(data)                                                 (0x0000000C&((data)<<2))
#define DBG_CTRL_dbg_wr_chk_m1_src(data)                                             ((0x0000000C&(data))>>2)
#define DBG_CTRL_get_dbg_wr_chk_m1(data)                                             ((0x0000000C&(data))>>2)
#define DBG_CTRL_write_en1_shift                                                     (1)
#define DBG_CTRL_write_en1_mask                                                      (0x00000002)
#define DBG_CTRL_write_en1(data)                                                     (0x00000002&((data)<<1))
#define DBG_CTRL_write_en1_src(data)                                                 ((0x00000002&(data))>>1)
#define DBG_CTRL_get_write_en1(data)                                                 ((0x00000002&(data))>>1)
#define DBG_CTRL_dbg_en_m1_shift                                                     (0)
#define DBG_CTRL_dbg_en_m1_mask                                                      (0x00000001)
#define DBG_CTRL_dbg_en_m1(data)                                                     (0x00000001&((data)<<0))
#define DBG_CTRL_dbg_en_m1_src(data)                                                 ((0x00000001&(data))>>0)
#define DBG_CTRL_get_dbg_en_m1(data)                                                 ((0x00000001&(data))>>0)


#define DBG_INT                                                                      0x1801D230
#define DBG_INT_reg_addr                                                             "0xB801D230"
#define DBG_INT_reg                                                                  0xB801D230
#define set_DBG_INT_reg(data)   (*((volatile unsigned int*) DBG_INT_reg)=data)
#define get_DBG_INT_reg   (*((volatile unsigned int*) DBG_INT_reg))
#define DBG_INT_inst_adr                                                             "0x008C"
#define DBG_INT_inst                                                                 0x008C
#define DBG_INT_scpu_int_m1_shift                                                    (4)
#define DBG_INT_scpu_int_m1_mask                                                     (0x00000010)
#define DBG_INT_scpu_int_m1(data)                                                    (0x00000010&((data)<<4))
#define DBG_INT_scpu_int_m1_src(data)                                                ((0x00000010&(data))>>4)
#define DBG_INT_get_scpu_int_m1(data)                                                ((0x00000010&(data))>>4)
#define DBG_INT_scpu_int_en_m1_shift                                                 (3)
#define DBG_INT_scpu_int_en_m1_mask                                                  (0x00000008)
#define DBG_INT_scpu_int_en_m1(data)                                                 (0x00000008&((data)<<3))
#define DBG_INT_scpu_int_en_m1_src(data)                                             ((0x00000008&(data))>>3)
#define DBG_INT_get_scpu_int_en_m1(data)                                             ((0x00000008&(data))>>3)
#define DBG_INT_scpu_neg_int_m1_shift                                                (2)
#define DBG_INT_scpu_neg_int_m1_mask                                                 (0x00000004)
#define DBG_INT_scpu_neg_int_m1(data)                                                (0x00000004&((data)<<2))
#define DBG_INT_scpu_neg_int_m1_src(data)                                            ((0x00000004&(data))>>2)
#define DBG_INT_get_scpu_neg_int_m1(data)                                            ((0x00000004&(data))>>2)
#define DBG_INT_scpu_neg_int_en_m1_shift                                             (1)
#define DBG_INT_scpu_neg_int_en_m1_mask                                              (0x00000002)
#define DBG_INT_scpu_neg_int_en_m1(data)                                             (0x00000002&((data)<<1))
#define DBG_INT_scpu_neg_int_en_m1_src(data)                                         ((0x00000002&(data))>>1)
#define DBG_INT_get_scpu_neg_int_en_m1(data)                                         ((0x00000002&(data))>>1)
#define DBG_INT_write_data_shift                                                     (0)
#define DBG_INT_write_data_mask                                                      (0x00000001)
#define DBG_INT_write_data(data)                                                     (0x00000001&((data)<<0))
#define DBG_INT_write_data_src(data)                                                 ((0x00000001&(data))>>0)
#define DBG_INT_get_write_data(data)                                                 ((0x00000001&(data))>>0)


#define DBG_ADDR                                                                     0x1801D234
#define DBG_ADDR_reg_addr                                                            "0xB801D234"
#define DBG_ADDR_reg                                                                 0xB801D234
#define set_DBG_ADDR_reg(data)   (*((volatile unsigned int*) DBG_ADDR_reg)=data)
#define get_DBG_ADDR_reg   (*((volatile unsigned int*) DBG_ADDR_reg))
#define DBG_ADDR_inst_adr                                                            "0x008D"
#define DBG_ADDR_inst                                                                0x008D
#define DBG_ADDR_dbg_addr_m1_shift                                                   (0)
#define DBG_ADDR_dbg_addr_m1_mask                                                    (0xFFFFFFFF)
#define DBG_ADDR_dbg_addr_m1(data)                                                   (0xFFFFFFFF&((data)<<0))
#define DBG_ADDR_dbg_addr_m1_src(data)                                               ((0xFFFFFFFF&(data))>>0)
#define DBG_ADDR_get_dbg_addr_m1(data)                                               ((0xFFFFFFFF&(data))>>0)


#define DBG_ADDR1                                                                    0x1801D238
#define DBG_ADDR1_reg_addr                                                           "0xB801D238"
#define DBG_ADDR1_reg                                                                0xB801D238
#define set_DBG_ADDR1_reg(data)   (*((volatile unsigned int*) DBG_ADDR1_reg)=data)
#define get_DBG_ADDR1_reg   (*((volatile unsigned int*) DBG_ADDR1_reg))
#define DBG_ADDR1_inst_adr                                                           "0x008E"
#define DBG_ADDR1_inst                                                               0x008E
#define DBG_ADDR1_scpu_dbg_write_m1_shift                                            (0)
#define DBG_ADDR1_scpu_dbg_write_m1_mask                                             (0x00000001)
#define DBG_ADDR1_scpu_dbg_write_m1(data)                                            (0x00000001&((data)<<0))
#define DBG_ADDR1_scpu_dbg_write_m1_src(data)                                        ((0x00000001&(data))>>0)
#define DBG_ADDR1_get_scpu_dbg_write_m1(data)                                        ((0x00000001&(data))>>0)


#define BIST_MODE                                                                    0x1801D300
#define BIST_MODE_reg_addr                                                           "0xB801D300"
#define BIST_MODE_reg                                                                0xB801D300
#define set_BIST_MODE_reg(data)   (*((volatile unsigned int*) BIST_MODE_reg)=data)
#define get_BIST_MODE_reg   (*((volatile unsigned int*) BIST_MODE_reg))
#define BIST_MODE_inst_adr                                                           "0x00C0"
#define BIST_MODE_inst                                                               0x00C0
#define BIST_MODE_scu_mbist_mode_shift                                               (6)
#define BIST_MODE_scu_mbist_mode_mask                                                (0x00000040)
#define BIST_MODE_scu_mbist_mode(data)                                               (0x00000040&((data)<<6))
#define BIST_MODE_scu_mbist_mode_src(data)                                           ((0x00000040&(data))>>6)
#define BIST_MODE_get_scu_mbist_mode(data)                                           ((0x00000040&(data))>>6)
#define BIST_MODE_idata_mbist_mode_shift                                             (5)
#define BIST_MODE_idata_mbist_mode_mask                                              (0x00000020)
#define BIST_MODE_idata_mbist_mode(data)                                             (0x00000020&((data)<<5))
#define BIST_MODE_idata_mbist_mode_src(data)                                         ((0x00000020&(data))>>5)
#define BIST_MODE_get_idata_mbist_mode(data)                                         ((0x00000020&(data))>>5)
#define BIST_MODE_itag_mbist_mode_shift                                              (4)
#define BIST_MODE_itag_mbist_mode_mask                                               (0x00000010)
#define BIST_MODE_itag_mbist_mode(data)                                              (0x00000010&((data)<<4))
#define BIST_MODE_itag_mbist_mode_src(data)                                          ((0x00000010&(data))>>4)
#define BIST_MODE_get_itag_mbist_mode(data)                                          ((0x00000010&(data))>>4)
#define BIST_MODE_ddata_mbist_mode_shift                                             (3)
#define BIST_MODE_ddata_mbist_mode_mask                                              (0x00000008)
#define BIST_MODE_ddata_mbist_mode(data)                                             (0x00000008&((data)<<3))
#define BIST_MODE_ddata_mbist_mode_src(data)                                         ((0x00000008&(data))>>3)
#define BIST_MODE_get_ddata_mbist_mode(data)                                         ((0x00000008&(data))>>3)
#define BIST_MODE_dtag_mbist_mode_shift                                              (2)
#define BIST_MODE_dtag_mbist_mode_mask                                               (0x00000004)
#define BIST_MODE_dtag_mbist_mode(data)                                              (0x00000004&((data)<<2))
#define BIST_MODE_dtag_mbist_mode_src(data)                                          ((0x00000004&(data))>>2)
#define BIST_MODE_get_dtag_mbist_mode(data)                                          ((0x00000004&(data))>>2)
#define BIST_MODE_ddrity_mbist_mode_shift                                            (1)
#define BIST_MODE_ddrity_mbist_mode_mask                                             (0x00000002)
#define BIST_MODE_ddrity_mbist_mode(data)                                            (0x00000002&((data)<<1))
#define BIST_MODE_ddrity_mbist_mode_src(data)                                        ((0x00000002&(data))>>1)
#define BIST_MODE_get_ddrity_mbist_mode(data)                                        ((0x00000002&(data))>>1)
#define BIST_MODE_tlb_mbist_mode_shift                                               (0)
#define BIST_MODE_tlb_mbist_mode_mask                                                (0x00000001)
#define BIST_MODE_tlb_mbist_mode(data)                                               (0x00000001&((data)<<0))
#define BIST_MODE_tlb_mbist_mode_src(data)                                           ((0x00000001&(data))>>0)
#define BIST_MODE_get_tlb_mbist_mode(data)                                           ((0x00000001&(data))>>0)


#define DRF_BIST_MODE                                                                0x1801D304
#define DRF_BIST_MODE_reg_addr                                                       "0xB801D304"
#define DRF_BIST_MODE_reg                                                            0xB801D304
#define set_DRF_BIST_MODE_reg(data)   (*((volatile unsigned int*) DRF_BIST_MODE_reg)=data)
#define get_DRF_BIST_MODE_reg   (*((volatile unsigned int*) DRF_BIST_MODE_reg))
#define DRF_BIST_MODE_inst_adr                                                       "0x00C1"
#define DRF_BIST_MODE_inst                                                           0x00C1
#define DRF_BIST_MODE_drf_mbist_mode_shift                                           (0)
#define DRF_BIST_MODE_drf_mbist_mode_mask                                            (0x00000001)
#define DRF_BIST_MODE_drf_mbist_mode(data)                                           (0x00000001&((data)<<0))
#define DRF_BIST_MODE_drf_mbist_mode_src(data)                                       ((0x00000001&(data))>>0)
#define DRF_BIST_MODE_get_drf_mbist_mode(data)                                       ((0x00000001&(data))>>0)


#define DRF_TEST_RESUME                                                              0x1801D308
#define DRF_TEST_RESUME_reg_addr                                                     "0xB801D308"
#define DRF_TEST_RESUME_reg                                                          0xB801D308
#define set_DRF_TEST_RESUME_reg(data)   (*((volatile unsigned int*) DRF_TEST_RESUME_reg)=data)
#define get_DRF_TEST_RESUME_reg   (*((volatile unsigned int*) DRF_TEST_RESUME_reg))
#define DRF_TEST_RESUME_inst_adr                                                     "0x00C2"
#define DRF_TEST_RESUME_inst                                                         0x00C2
#define DRF_TEST_RESUME_drf_test_resume_shift                                        (0)
#define DRF_TEST_RESUME_drf_test_resume_mask                                         (0x00000001)
#define DRF_TEST_RESUME_drf_test_resume(data)                                        (0x00000001&((data)<<0))
#define DRF_TEST_RESUME_drf_test_resume_src(data)                                    ((0x00000001&(data))>>0)
#define DRF_TEST_RESUME_get_drf_test_resume(data)                                    ((0x00000001&(data))>>0)


#define CPU_BIST_DONE                                                                0x1801D30C
#define CPU_BIST_DONE_reg_addr                                                       "0xB801D30C"
#define CPU_BIST_DONE_reg                                                            0xB801D30C
#define set_CPU_BIST_DONE_reg(data)   (*((volatile unsigned int*) CPU_BIST_DONE_reg)=data)
#define get_CPU_BIST_DONE_reg   (*((volatile unsigned int*) CPU_BIST_DONE_reg))
#define CPU_BIST_DONE_inst_adr                                                       "0x00C3"
#define CPU_BIST_DONE_inst                                                           0x00C3
#define CPU_BIST_DONE_MBISTACK_shift                                                 (7)
#define CPU_BIST_DONE_MBISTACK_mask                                                  (0x00000080)
#define CPU_BIST_DONE_MBISTACK(data)                                                 (0x00000080&((data)<<7))
#define CPU_BIST_DONE_MBISTACK_src(data)                                             ((0x00000080&(data))>>7)
#define CPU_BIST_DONE_get_MBISTACK(data)                                             ((0x00000080&(data))>>7)
#define CPU_BIST_DONE_scu_mbist_done_shift                                           (6)
#define CPU_BIST_DONE_scu_mbist_done_mask                                            (0x00000040)
#define CPU_BIST_DONE_scu_mbist_done(data)                                           (0x00000040&((data)<<6))
#define CPU_BIST_DONE_scu_mbist_done_src(data)                                       ((0x00000040&(data))>>6)
#define CPU_BIST_DONE_get_scu_mbist_done(data)                                       ((0x00000040&(data))>>6)
#define CPU_BIST_DONE_idata_mbist_done_shift                                         (5)
#define CPU_BIST_DONE_idata_mbist_done_mask                                          (0x00000020)
#define CPU_BIST_DONE_idata_mbist_done(data)                                         (0x00000020&((data)<<5))
#define CPU_BIST_DONE_idata_mbist_done_src(data)                                     ((0x00000020&(data))>>5)
#define CPU_BIST_DONE_get_idata_mbist_done(data)                                     ((0x00000020&(data))>>5)
#define CPU_BIST_DONE_itag_mbist_done_shift                                          (4)
#define CPU_BIST_DONE_itag_mbist_done_mask                                           (0x00000010)
#define CPU_BIST_DONE_itag_mbist_done(data)                                          (0x00000010&((data)<<4))
#define CPU_BIST_DONE_itag_mbist_done_src(data)                                      ((0x00000010&(data))>>4)
#define CPU_BIST_DONE_get_itag_mbist_done(data)                                      ((0x00000010&(data))>>4)
#define CPU_BIST_DONE_ddata_mbist_done_shift                                         (3)
#define CPU_BIST_DONE_ddata_mbist_done_mask                                          (0x00000008)
#define CPU_BIST_DONE_ddata_mbist_done(data)                                         (0x00000008&((data)<<3))
#define CPU_BIST_DONE_ddata_mbist_done_src(data)                                     ((0x00000008&(data))>>3)
#define CPU_BIST_DONE_get_ddata_mbist_done(data)                                     ((0x00000008&(data))>>3)
#define CPU_BIST_DONE_dtag_mbist_done_shift                                          (2)
#define CPU_BIST_DONE_dtag_mbist_done_mask                                           (0x00000004)
#define CPU_BIST_DONE_dtag_mbist_done(data)                                          (0x00000004&((data)<<2))
#define CPU_BIST_DONE_dtag_mbist_done_src(data)                                      ((0x00000004&(data))>>2)
#define CPU_BIST_DONE_get_dtag_mbist_done(data)                                      ((0x00000004&(data))>>2)
#define CPU_BIST_DONE_ddirty_mbist_done_shift                                        (1)
#define CPU_BIST_DONE_ddirty_mbist_done_mask                                         (0x00000002)
#define CPU_BIST_DONE_ddirty_mbist_done(data)                                        (0x00000002&((data)<<1))
#define CPU_BIST_DONE_ddirty_mbist_done_src(data)                                    ((0x00000002&(data))>>1)
#define CPU_BIST_DONE_get_ddirty_mbist_done(data)                                    ((0x00000002&(data))>>1)
#define CPU_BIST_DONE_tlb_mbist_done_shift                                           (0)
#define CPU_BIST_DONE_tlb_mbist_done_mask                                            (0x00000001)
#define CPU_BIST_DONE_tlb_mbist_done(data)                                           (0x00000001&((data)<<0))
#define CPU_BIST_DONE_tlb_mbist_done_src(data)                                       ((0x00000001&(data))>>0)
#define CPU_BIST_DONE_get_tlb_mbist_done(data)                                       ((0x00000001&(data))>>0)


#define CPU_DRF_BIST_DONE                                                            0x1801D310
#define CPU_DRF_BIST_DONE_reg_addr                                                   "0xB801D310"
#define CPU_DRF_BIST_DONE_reg                                                        0xB801D310
#define set_CPU_DRF_BIST_DONE_reg(data)   (*((volatile unsigned int*) CPU_DRF_BIST_DONE_reg)=data)
#define get_CPU_DRF_BIST_DONE_reg   (*((volatile unsigned int*) CPU_DRF_BIST_DONE_reg))
#define CPU_DRF_BIST_DONE_inst_adr                                                   "0x00C4"
#define CPU_DRF_BIST_DONE_inst                                                       0x00C4
#define CPU_DRF_BIST_DONE_drf_mbist_done_shift                                       (0)
#define CPU_DRF_BIST_DONE_drf_mbist_done_mask                                        (0x00000001)
#define CPU_DRF_BIST_DONE_drf_mbist_done(data)                                       (0x00000001&((data)<<0))
#define CPU_DRF_BIST_DONE_drf_mbist_done_src(data)                                   ((0x00000001&(data))>>0)
#define CPU_DRF_BIST_DONE_get_drf_mbist_done(data)                                   ((0x00000001&(data))>>0)


#define CPU_DRF_START_PAUSE                                                          0x1801D314
#define CPU_DRF_START_PAUSE_reg_addr                                                 "0xB801D314"
#define CPU_DRF_START_PAUSE_reg                                                      0xB801D314
#define set_CPU_DRF_START_PAUSE_reg(data)   (*((volatile unsigned int*) CPU_DRF_START_PAUSE_reg)=data)
#define get_CPU_DRF_START_PAUSE_reg   (*((volatile unsigned int*) CPU_DRF_START_PAUSE_reg))
#define CPU_DRF_START_PAUSE_inst_adr                                                 "0x00C5"
#define CPU_DRF_START_PAUSE_inst                                                     0x00C5
#define CPU_DRF_START_PAUSE_drf_start_pause_shift                                    (0)
#define CPU_DRF_START_PAUSE_drf_start_pause_mask                                     (0x00000001)
#define CPU_DRF_START_PAUSE_drf_start_pause(data)                                    (0x00000001&((data)<<0))
#define CPU_DRF_START_PAUSE_drf_start_pause_src(data)                                ((0x00000001&(data))>>0)
#define CPU_DRF_START_PAUSE_get_drf_start_pause(data)                                ((0x00000001&(data))>>0)


#define CPU0_BIST_FAIL_GROUP                                                         0x1801D318
#define CPU0_BIST_FAIL_GROUP_reg_addr                                                "0xB801D318"
#define CPU0_BIST_FAIL_GROUP_reg                                                     0xB801D318
#define set_CPU0_BIST_FAIL_GROUP_reg(data)   (*((volatile unsigned int*) CPU0_BIST_FAIL_GROUP_reg)=data)
#define get_CPU0_BIST_FAIL_GROUP_reg   (*((volatile unsigned int*) CPU0_BIST_FAIL_GROUP_reg))
#define CPU0_BIST_FAIL_GROUP_inst_adr                                                "0x00C6"
#define CPU0_BIST_FAIL_GROUP_inst                                                    0x00C6
#define CPU0_BIST_FAIL_GROUP_cpu0_scu_mbist_fail_G_shift                             (6)
#define CPU0_BIST_FAIL_GROUP_cpu0_scu_mbist_fail_G_mask                              (0x00000040)
#define CPU0_BIST_FAIL_GROUP_cpu0_scu_mbist_fail_G(data)                             (0x00000040&((data)<<6))
#define CPU0_BIST_FAIL_GROUP_cpu0_scu_mbist_fail_G_src(data)                         ((0x00000040&(data))>>6)
#define CPU0_BIST_FAIL_GROUP_get_cpu0_scu_mbist_fail_G(data)                         ((0x00000040&(data))>>6)
#define CPU0_BIST_FAIL_GROUP_cpu0_idata_mbist_fail_G_shift                           (5)
#define CPU0_BIST_FAIL_GROUP_cpu0_idata_mbist_fail_G_mask                            (0x00000020)
#define CPU0_BIST_FAIL_GROUP_cpu0_idata_mbist_fail_G(data)                           (0x00000020&((data)<<5))
#define CPU0_BIST_FAIL_GROUP_cpu0_idata_mbist_fail_G_src(data)                       ((0x00000020&(data))>>5)
#define CPU0_BIST_FAIL_GROUP_get_cpu0_idata_mbist_fail_G(data)                       ((0x00000020&(data))>>5)
#define CPU0_BIST_FAIL_GROUP_cpu0_itag_mbist_fail_G_shift                            (4)
#define CPU0_BIST_FAIL_GROUP_cpu0_itag_mbist_fail_G_mask                             (0x00000010)
#define CPU0_BIST_FAIL_GROUP_cpu0_itag_mbist_fail_G(data)                            (0x00000010&((data)<<4))
#define CPU0_BIST_FAIL_GROUP_cpu0_itag_mbist_fail_G_src(data)                        ((0x00000010&(data))>>4)
#define CPU0_BIST_FAIL_GROUP_get_cpu0_itag_mbist_fail_G(data)                        ((0x00000010&(data))>>4)
#define CPU0_BIST_FAIL_GROUP_cpu0_ddata_mbist_fail_G_shift                           (3)
#define CPU0_BIST_FAIL_GROUP_cpu0_ddata_mbist_fail_G_mask                            (0x00000008)
#define CPU0_BIST_FAIL_GROUP_cpu0_ddata_mbist_fail_G(data)                           (0x00000008&((data)<<3))
#define CPU0_BIST_FAIL_GROUP_cpu0_ddata_mbist_fail_G_src(data)                       ((0x00000008&(data))>>3)
#define CPU0_BIST_FAIL_GROUP_get_cpu0_ddata_mbist_fail_G(data)                       ((0x00000008&(data))>>3)
#define CPU0_BIST_FAIL_GROUP_cpu0_dtag_mbist_fail_G_shift                            (2)
#define CPU0_BIST_FAIL_GROUP_cpu0_dtag_mbist_fail_G_mask                             (0x00000004)
#define CPU0_BIST_FAIL_GROUP_cpu0_dtag_mbist_fail_G(data)                            (0x00000004&((data)<<2))
#define CPU0_BIST_FAIL_GROUP_cpu0_dtag_mbist_fail_G_src(data)                        ((0x00000004&(data))>>2)
#define CPU0_BIST_FAIL_GROUP_get_cpu0_dtag_mbist_fail_G(data)                        ((0x00000004&(data))>>2)
#define CPU0_BIST_FAIL_GROUP_cpu0_ddrity_mbist_fail_G_shift                          (1)
#define CPU0_BIST_FAIL_GROUP_cpu0_ddrity_mbist_fail_G_mask                           (0x00000002)
#define CPU0_BIST_FAIL_GROUP_cpu0_ddrity_mbist_fail_G(data)                          (0x00000002&((data)<<1))
#define CPU0_BIST_FAIL_GROUP_cpu0_ddrity_mbist_fail_G_src(data)                      ((0x00000002&(data))>>1)
#define CPU0_BIST_FAIL_GROUP_get_cpu0_ddrity_mbist_fail_G(data)                      ((0x00000002&(data))>>1)
#define CPU0_BIST_FAIL_GROUP_cpu0_tlb_mbist_fail_G_shift                             (0)
#define CPU0_BIST_FAIL_GROUP_cpu0_tlb_mbist_fail_G_mask                              (0x00000001)
#define CPU0_BIST_FAIL_GROUP_cpu0_tlb_mbist_fail_G(data)                             (0x00000001&((data)<<0))
#define CPU0_BIST_FAIL_GROUP_cpu0_tlb_mbist_fail_G_src(data)                         ((0x00000001&(data))>>0)
#define CPU0_BIST_FAIL_GROUP_get_cpu0_tlb_mbist_fail_G(data)                         ((0x00000001&(data))>>0)


#define CPU1_BIST_FAIL_GROUP                                                         0x1801D31C
#define CPU1_BIST_FAIL_GROUP_reg_addr                                                "0xB801D31C"
#define CPU1_BIST_FAIL_GROUP_reg                                                     0xB801D31C
#define set_CPU1_BIST_FAIL_GROUP_reg(data)   (*((volatile unsigned int*) CPU1_BIST_FAIL_GROUP_reg)=data)
#define get_CPU1_BIST_FAIL_GROUP_reg   (*((volatile unsigned int*) CPU1_BIST_FAIL_GROUP_reg))
#define CPU1_BIST_FAIL_GROUP_inst_adr                                                "0x00C7"
#define CPU1_BIST_FAIL_GROUP_inst                                                    0x00C7
#define CPU1_BIST_FAIL_GROUP_cpu1_scu_mbist_fail_G_shift                             (6)
#define CPU1_BIST_FAIL_GROUP_cpu1_scu_mbist_fail_G_mask                              (0x00000040)
#define CPU1_BIST_FAIL_GROUP_cpu1_scu_mbist_fail_G(data)                             (0x00000040&((data)<<6))
#define CPU1_BIST_FAIL_GROUP_cpu1_scu_mbist_fail_G_src(data)                         ((0x00000040&(data))>>6)
#define CPU1_BIST_FAIL_GROUP_get_cpu1_scu_mbist_fail_G(data)                         ((0x00000040&(data))>>6)
#define CPU1_BIST_FAIL_GROUP_cpu1_idata_mbist_fail_G_shift                           (5)
#define CPU1_BIST_FAIL_GROUP_cpu1_idata_mbist_fail_G_mask                            (0x00000020)
#define CPU1_BIST_FAIL_GROUP_cpu1_idata_mbist_fail_G(data)                           (0x00000020&((data)<<5))
#define CPU1_BIST_FAIL_GROUP_cpu1_idata_mbist_fail_G_src(data)                       ((0x00000020&(data))>>5)
#define CPU1_BIST_FAIL_GROUP_get_cpu1_idata_mbist_fail_G(data)                       ((0x00000020&(data))>>5)
#define CPU1_BIST_FAIL_GROUP_cpu1_itag_mbist_fail_G_shift                            (4)
#define CPU1_BIST_FAIL_GROUP_cpu1_itag_mbist_fail_G_mask                             (0x00000010)
#define CPU1_BIST_FAIL_GROUP_cpu1_itag_mbist_fail_G(data)                            (0x00000010&((data)<<4))
#define CPU1_BIST_FAIL_GROUP_cpu1_itag_mbist_fail_G_src(data)                        ((0x00000010&(data))>>4)
#define CPU1_BIST_FAIL_GROUP_get_cpu1_itag_mbist_fail_G(data)                        ((0x00000010&(data))>>4)
#define CPU1_BIST_FAIL_GROUP_cpu1_ddata_mbist_fail_G_shift                           (3)
#define CPU1_BIST_FAIL_GROUP_cpu1_ddata_mbist_fail_G_mask                            (0x00000008)
#define CPU1_BIST_FAIL_GROUP_cpu1_ddata_mbist_fail_G(data)                           (0x00000008&((data)<<3))
#define CPU1_BIST_FAIL_GROUP_cpu1_ddata_mbist_fail_G_src(data)                       ((0x00000008&(data))>>3)
#define CPU1_BIST_FAIL_GROUP_get_cpu1_ddata_mbist_fail_G(data)                       ((0x00000008&(data))>>3)
#define CPU1_BIST_FAIL_GROUP_cpu1_dtag_mbist_fail_G_shift                            (2)
#define CPU1_BIST_FAIL_GROUP_cpu1_dtag_mbist_fail_G_mask                             (0x00000004)
#define CPU1_BIST_FAIL_GROUP_cpu1_dtag_mbist_fail_G(data)                            (0x00000004&((data)<<2))
#define CPU1_BIST_FAIL_GROUP_cpu1_dtag_mbist_fail_G_src(data)                        ((0x00000004&(data))>>2)
#define CPU1_BIST_FAIL_GROUP_get_cpu1_dtag_mbist_fail_G(data)                        ((0x00000004&(data))>>2)
#define CPU1_BIST_FAIL_GROUP_cpu1_ddrity_mbist_fail_G_shift                          (1)
#define CPU1_BIST_FAIL_GROUP_cpu1_ddrity_mbist_fail_G_mask                           (0x00000002)
#define CPU1_BIST_FAIL_GROUP_cpu1_ddrity_mbist_fail_G(data)                          (0x00000002&((data)<<1))
#define CPU1_BIST_FAIL_GROUP_cpu1_ddrity_mbist_fail_G_src(data)                      ((0x00000002&(data))>>1)
#define CPU1_BIST_FAIL_GROUP_get_cpu1_ddrity_mbist_fail_G(data)                      ((0x00000002&(data))>>1)
#define CPU1_BIST_FAIL_GROUP_cpu1_tlb_mbist_fail_G_shift                             (0)
#define CPU1_BIST_FAIL_GROUP_cpu1_tlb_mbist_fail_G_mask                              (0x00000001)
#define CPU1_BIST_FAIL_GROUP_cpu1_tlb_mbist_fail_G(data)                             (0x00000001&((data)<<0))
#define CPU1_BIST_FAIL_GROUP_cpu1_tlb_mbist_fail_G_src(data)                         ((0x00000001&(data))>>0)
#define CPU1_BIST_FAIL_GROUP_get_cpu1_tlb_mbist_fail_G(data)                         ((0x00000001&(data))>>0)


#define CPU0_DRF_BIST_FAIL_GROUP                                                     0x1801D320
#define CPU0_DRF_BIST_FAIL_GROUP_reg_addr                                            "0xB801D320"
#define CPU0_DRF_BIST_FAIL_GROUP_reg                                                 0xB801D320
#define set_CPU0_DRF_BIST_FAIL_GROUP_reg(data)   (*((volatile unsigned int*) CPU0_DRF_BIST_FAIL_GROUP_reg)=data)
#define get_CPU0_DRF_BIST_FAIL_GROUP_reg   (*((volatile unsigned int*) CPU0_DRF_BIST_FAIL_GROUP_reg))
#define CPU0_DRF_BIST_FAIL_GROUP_inst_adr                                            "0x00C8"
#define CPU0_DRF_BIST_FAIL_GROUP_inst                                                0x00C8
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_scu_drf_mbist_fail_G_shift                     (6)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_scu_drf_mbist_fail_G_mask                      (0x00000040)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_scu_drf_mbist_fail_G(data)                     (0x00000040&((data)<<6))
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_scu_drf_mbist_fail_G_src(data)                 ((0x00000040&(data))>>6)
#define CPU0_DRF_BIST_FAIL_GROUP_get_cpu0_scu_drf_mbist_fail_G(data)                 ((0x00000040&(data))>>6)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_idata_drf_mbist_fail_G_shift                   (5)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_idata_drf_mbist_fail_G_mask                    (0x00000020)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_idata_drf_mbist_fail_G(data)                   (0x00000020&((data)<<5))
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_idata_drf_mbist_fail_G_src(data)               ((0x00000020&(data))>>5)
#define CPU0_DRF_BIST_FAIL_GROUP_get_cpu0_idata_drf_mbist_fail_G(data)               ((0x00000020&(data))>>5)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_itag_drf_mbist_fail_G_shift                    (4)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_itag_drf_mbist_fail_G_mask                     (0x00000010)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_itag_drf_mbist_fail_G(data)                    (0x00000010&((data)<<4))
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_itag_drf_mbist_fail_G_src(data)                ((0x00000010&(data))>>4)
#define CPU0_DRF_BIST_FAIL_GROUP_get_cpu0_itag_drf_mbist_fail_G(data)                ((0x00000010&(data))>>4)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_ddata_drf_mbist_fail_G_shift                   (3)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_ddata_drf_mbist_fail_G_mask                    (0x00000008)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_ddata_drf_mbist_fail_G(data)                   (0x00000008&((data)<<3))
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_ddata_drf_mbist_fail_G_src(data)               ((0x00000008&(data))>>3)
#define CPU0_DRF_BIST_FAIL_GROUP_get_cpu0_ddata_drf_mbist_fail_G(data)               ((0x00000008&(data))>>3)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_dtag_drf_mbist_fail_G_shift                    (2)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_dtag_drf_mbist_fail_G_mask                     (0x00000004)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_dtag_drf_mbist_fail_G(data)                    (0x00000004&((data)<<2))
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_dtag_drf_mbist_fail_G_src(data)                ((0x00000004&(data))>>2)
#define CPU0_DRF_BIST_FAIL_GROUP_get_cpu0_dtag_drf_mbist_fail_G(data)                ((0x00000004&(data))>>2)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_ddrity_drf_mbist_fail_G_shift                  (1)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_ddrity_drf_mbist_fail_G_mask                   (0x00000002)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_ddrity_drf_mbist_fail_G(data)                  (0x00000002&((data)<<1))
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_ddrity_drf_mbist_fail_G_src(data)              ((0x00000002&(data))>>1)
#define CPU0_DRF_BIST_FAIL_GROUP_get_cpu0_ddrity_drf_mbist_fail_G(data)              ((0x00000002&(data))>>1)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_tlb_drf_mbist_fail_G_shift                     (0)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_tlb_drf_mbist_fail_G_mask                      (0x00000001)
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_tlb_drf_mbist_fail_G(data)                     (0x00000001&((data)<<0))
#define CPU0_DRF_BIST_FAIL_GROUP_cpu0_tlb_drf_mbist_fail_G_src(data)                 ((0x00000001&(data))>>0)
#define CPU0_DRF_BIST_FAIL_GROUP_get_cpu0_tlb_drf_mbist_fail_G(data)                 ((0x00000001&(data))>>0)


#define CPU1_DRF_BIST_FAIL_GROUP                                                     0x1801D324
#define CPU1_DRF_BIST_FAIL_GROUP_reg_addr                                            "0xB801D324"
#define CPU1_DRF_BIST_FAIL_GROUP_reg                                                 0xB801D324
#define set_CPU1_DRF_BIST_FAIL_GROUP_reg(data)   (*((volatile unsigned int*) CPU1_DRF_BIST_FAIL_GROUP_reg)=data)
#define get_CPU1_DRF_BIST_FAIL_GROUP_reg   (*((volatile unsigned int*) CPU1_DRF_BIST_FAIL_GROUP_reg))
#define CPU1_DRF_BIST_FAIL_GROUP_inst_adr                                            "0x00C9"
#define CPU1_DRF_BIST_FAIL_GROUP_inst                                                0x00C9
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_scu_drf_mbist_fail_G_shift                     (6)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_scu_drf_mbist_fail_G_mask                      (0x00000040)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_scu_drf_mbist_fail_G(data)                     (0x00000040&((data)<<6))
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_scu_drf_mbist_fail_G_src(data)                 ((0x00000040&(data))>>6)
#define CPU1_DRF_BIST_FAIL_GROUP_get_cpu1_scu_drf_mbist_fail_G(data)                 ((0x00000040&(data))>>6)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_idata_drf_mbist_fail_G_shift                   (5)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_idata_drf_mbist_fail_G_mask                    (0x00000020)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_idata_drf_mbist_fail_G(data)                   (0x00000020&((data)<<5))
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_idata_drf_mbist_fail_G_src(data)               ((0x00000020&(data))>>5)
#define CPU1_DRF_BIST_FAIL_GROUP_get_cpu1_idata_drf_mbist_fail_G(data)               ((0x00000020&(data))>>5)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_itag_drf_mbist_fail_G_shift                    (4)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_itag_drf_mbist_fail_G_mask                     (0x00000010)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_itag_drf_mbist_fail_G(data)                    (0x00000010&((data)<<4))
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_itag_drf_mbist_fail_G_src(data)                ((0x00000010&(data))>>4)
#define CPU1_DRF_BIST_FAIL_GROUP_get_cpu1_itag_drf_mbist_fail_G(data)                ((0x00000010&(data))>>4)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_ddata_drf_mbist_fail_G_shift                   (3)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_ddata_drf_mbist_fail_G_mask                    (0x00000008)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_ddata_drf_mbist_fail_G(data)                   (0x00000008&((data)<<3))
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_ddata_drf_mbist_fail_G_src(data)               ((0x00000008&(data))>>3)
#define CPU1_DRF_BIST_FAIL_GROUP_get_cpu1_ddata_drf_mbist_fail_G(data)               ((0x00000008&(data))>>3)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_dtag_drf_mbist_fail_G_shift                    (2)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_dtag_drf_mbist_fail_G_mask                     (0x00000004)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_dtag_drf_mbist_fail_G(data)                    (0x00000004&((data)<<2))
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_dtag_drf_mbist_fail_G_src(data)                ((0x00000004&(data))>>2)
#define CPU1_DRF_BIST_FAIL_GROUP_get_cpu1_dtag_drf_mbist_fail_G(data)                ((0x00000004&(data))>>2)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_ddrity_drf_mbist_fail_G_shift                  (1)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_ddrity_drf_mbist_fail_G_mask                   (0x00000002)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_ddrity_drf_mbist_fail_G(data)                  (0x00000002&((data)<<1))
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_ddrity_drf_mbist_fail_G_src(data)              ((0x00000002&(data))>>1)
#define CPU1_DRF_BIST_FAIL_GROUP_get_cpu1_ddrity_drf_mbist_fail_G(data)              ((0x00000002&(data))>>1)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_tlb_drf_mbist_fail_G_shift                     (0)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_tlb_drf_mbist_fail_G_mask                      (0x00000001)
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_tlb_drf_mbist_fail_G(data)                     (0x00000001&((data)<<0))
#define CPU1_DRF_BIST_FAIL_GROUP_cpu1_tlb_drf_mbist_fail_G_src(data)                 ((0x00000001&(data))>>0)
#define CPU1_DRF_BIST_FAIL_GROUP_get_cpu1_tlb_drf_mbist_fail_G(data)                 ((0x00000001&(data))>>0)


#define CPU0_IDATA_BIST_FAIL                                                         0x1801D328
#define CPU0_IDATA_BIST_FAIL_reg_addr                                                "0xB801D328"
#define CPU0_IDATA_BIST_FAIL_reg                                                     0xB801D328
#define set_CPU0_IDATA_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU0_IDATA_BIST_FAIL_reg)=data)
#define get_CPU0_IDATA_BIST_FAIL_reg   (*((volatile unsigned int*) CPU0_IDATA_BIST_FAIL_reg))
#define CPU0_IDATA_BIST_FAIL_inst_adr                                                "0x00CA"
#define CPU0_IDATA_BIST_FAIL_inst                                                    0x00CA
#define CPU0_IDATA_BIST_FAIL_cpu0_idata_mbist_fail_shift                             (0)
#define CPU0_IDATA_BIST_FAIL_cpu0_idata_mbist_fail_mask                              (0x00000003)
#define CPU0_IDATA_BIST_FAIL_cpu0_idata_mbist_fail(data)                             (0x00000003&((data)<<0))
#define CPU0_IDATA_BIST_FAIL_cpu0_idata_mbist_fail_src(data)                         ((0x00000003&(data))>>0)
#define CPU0_IDATA_BIST_FAIL_get_cpu0_idata_mbist_fail(data)                         ((0x00000003&(data))>>0)


#define CPU1_IDATA_BIST_FAIL                                                         0x1801D32C
#define CPU1_IDATA_BIST_FAIL_reg_addr                                                "0xB801D32C"
#define CPU1_IDATA_BIST_FAIL_reg                                                     0xB801D32C
#define set_CPU1_IDATA_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU1_IDATA_BIST_FAIL_reg)=data)
#define get_CPU1_IDATA_BIST_FAIL_reg   (*((volatile unsigned int*) CPU1_IDATA_BIST_FAIL_reg))
#define CPU1_IDATA_BIST_FAIL_inst_adr                                                "0x00CB"
#define CPU1_IDATA_BIST_FAIL_inst                                                    0x00CB
#define CPU1_IDATA_BIST_FAIL_cpu1_idata_mbist_fail_shift                             (0)
#define CPU1_IDATA_BIST_FAIL_cpu1_idata_mbist_fail_mask                              (0x00000003)
#define CPU1_IDATA_BIST_FAIL_cpu1_idata_mbist_fail(data)                             (0x00000003&((data)<<0))
#define CPU1_IDATA_BIST_FAIL_cpu1_idata_mbist_fail_src(data)                         ((0x00000003&(data))>>0)
#define CPU1_IDATA_BIST_FAIL_get_cpu1_idata_mbist_fail(data)                         ((0x00000003&(data))>>0)


#define CPU0_IDATA_DRF_BIST_FAIL                                                     0x1801D330
#define CPU0_IDATA_DRF_BIST_FAIL_reg_addr                                            "0xB801D330"
#define CPU0_IDATA_DRF_BIST_FAIL_reg                                                 0xB801D330
#define set_CPU0_IDATA_DRF_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU0_IDATA_DRF_BIST_FAIL_reg)=data)
#define get_CPU0_IDATA_DRF_BIST_FAIL_reg   (*((volatile unsigned int*) CPU0_IDATA_DRF_BIST_FAIL_reg))
#define CPU0_IDATA_DRF_BIST_FAIL_inst_adr                                            "0x00CC"
#define CPU0_IDATA_DRF_BIST_FAIL_inst                                                0x00CC
#define CPU0_IDATA_DRF_BIST_FAIL_cpu0_idata_drf_mbist_fail_shift                     (0)
#define CPU0_IDATA_DRF_BIST_FAIL_cpu0_idata_drf_mbist_fail_mask                      (0x00000003)
#define CPU0_IDATA_DRF_BIST_FAIL_cpu0_idata_drf_mbist_fail(data)                     (0x00000003&((data)<<0))
#define CPU0_IDATA_DRF_BIST_FAIL_cpu0_idata_drf_mbist_fail_src(data)                 ((0x00000003&(data))>>0)
#define CPU0_IDATA_DRF_BIST_FAIL_get_cpu0_idata_drf_mbist_fail(data)                 ((0x00000003&(data))>>0)


#define CPU1_IDATA_DRF_BIST_FAIL                                                     0x1801D334
#define CPU1_IDATA_DRF_BIST_FAIL_reg_addr                                            "0xB801D334"
#define CPU1_IDATA_DRF_BIST_FAIL_reg                                                 0xB801D334
#define set_CPU1_IDATA_DRF_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU1_IDATA_DRF_BIST_FAIL_reg)=data)
#define get_CPU1_IDATA_DRF_BIST_FAIL_reg   (*((volatile unsigned int*) CPU1_IDATA_DRF_BIST_FAIL_reg))
#define CPU1_IDATA_DRF_BIST_FAIL_inst_adr                                            "0x00CD"
#define CPU1_IDATA_DRF_BIST_FAIL_inst                                                0x00CD
#define CPU1_IDATA_DRF_BIST_FAIL_cpu1_idata_drf_mbist_fail_shift                     (0)
#define CPU1_IDATA_DRF_BIST_FAIL_cpu1_idata_drf_mbist_fail_mask                      (0x00000003)
#define CPU1_IDATA_DRF_BIST_FAIL_cpu1_idata_drf_mbist_fail(data)                     (0x00000003&((data)<<0))
#define CPU1_IDATA_DRF_BIST_FAIL_cpu1_idata_drf_mbist_fail_src(data)                 ((0x00000003&(data))>>0)
#define CPU1_IDATA_DRF_BIST_FAIL_get_cpu1_idata_drf_mbist_fail(data)                 ((0x00000003&(data))>>0)


#define CPU0_ITAG_BIST_FAIL                                                          0x1801D338
#define CPU0_ITAG_BIST_FAIL_reg_addr                                                 "0xB801D338"
#define CPU0_ITAG_BIST_FAIL_reg                                                      0xB801D338
#define set_CPU0_ITAG_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU0_ITAG_BIST_FAIL_reg)=data)
#define get_CPU0_ITAG_BIST_FAIL_reg   (*((volatile unsigned int*) CPU0_ITAG_BIST_FAIL_reg))
#define CPU0_ITAG_BIST_FAIL_inst_adr                                                 "0x00CE"
#define CPU0_ITAG_BIST_FAIL_inst                                                     0x00CE
#define CPU0_ITAG_BIST_FAIL_cpu0_itag_mbist_fail_shift                               (0)
#define CPU0_ITAG_BIST_FAIL_cpu0_itag_mbist_fail_mask                                (0x00000003)
#define CPU0_ITAG_BIST_FAIL_cpu0_itag_mbist_fail(data)                               (0x00000003&((data)<<0))
#define CPU0_ITAG_BIST_FAIL_cpu0_itag_mbist_fail_src(data)                           ((0x00000003&(data))>>0)
#define CPU0_ITAG_BIST_FAIL_get_cpu0_itag_mbist_fail(data)                           ((0x00000003&(data))>>0)


#define CPU1_ITAG_BIST_FAIL                                                          0x1801D33C
#define CPU1_ITAG_BIST_FAIL_reg_addr                                                 "0xB801D33C"
#define CPU1_ITAG_BIST_FAIL_reg                                                      0xB801D33C
#define set_CPU1_ITAG_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU1_ITAG_BIST_FAIL_reg)=data)
#define get_CPU1_ITAG_BIST_FAIL_reg   (*((volatile unsigned int*) CPU1_ITAG_BIST_FAIL_reg))
#define CPU1_ITAG_BIST_FAIL_inst_adr                                                 "0x00CF"
#define CPU1_ITAG_BIST_FAIL_inst                                                     0x00CF
#define CPU1_ITAG_BIST_FAIL_cpu1_itag_mbist_fail_shift                               (0)
#define CPU1_ITAG_BIST_FAIL_cpu1_itag_mbist_fail_mask                                (0x00000003)
#define CPU1_ITAG_BIST_FAIL_cpu1_itag_mbist_fail(data)                               (0x00000003&((data)<<0))
#define CPU1_ITAG_BIST_FAIL_cpu1_itag_mbist_fail_src(data)                           ((0x00000003&(data))>>0)
#define CPU1_ITAG_BIST_FAIL_get_cpu1_itag_mbist_fail(data)                           ((0x00000003&(data))>>0)


#define CPU0_ITAG_DRF_BIST_FAIL                                                      0x1801D340
#define CPU0_ITAG_DRF_BIST_FAIL_reg_addr                                             "0xB801D340"
#define CPU0_ITAG_DRF_BIST_FAIL_reg                                                  0xB801D340
#define set_CPU0_ITAG_DRF_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU0_ITAG_DRF_BIST_FAIL_reg)=data)
#define get_CPU0_ITAG_DRF_BIST_FAIL_reg   (*((volatile unsigned int*) CPU0_ITAG_DRF_BIST_FAIL_reg))
#define CPU0_ITAG_DRF_BIST_FAIL_inst_adr                                             "0x00D0"
#define CPU0_ITAG_DRF_BIST_FAIL_inst                                                 0x00D0
#define CPU0_ITAG_DRF_BIST_FAIL_cpu0_itag_drf_mbist_fail_shift                       (0)
#define CPU0_ITAG_DRF_BIST_FAIL_cpu0_itag_drf_mbist_fail_mask                        (0x00000003)
#define CPU0_ITAG_DRF_BIST_FAIL_cpu0_itag_drf_mbist_fail(data)                       (0x00000003&((data)<<0))
#define CPU0_ITAG_DRF_BIST_FAIL_cpu0_itag_drf_mbist_fail_src(data)                   ((0x00000003&(data))>>0)
#define CPU0_ITAG_DRF_BIST_FAIL_get_cpu0_itag_drf_mbist_fail(data)                   ((0x00000003&(data))>>0)


#define CPU1_ITAG_DRF_BIST_FAIL                                                      0x1801D344
#define CPU1_ITAG_DRF_BIST_FAIL_reg_addr                                             "0xB801D344"
#define CPU1_ITAG_DRF_BIST_FAIL_reg                                                  0xB801D344
#define set_CPU1_ITAG_DRF_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU1_ITAG_DRF_BIST_FAIL_reg)=data)
#define get_CPU1_ITAG_DRF_BIST_FAIL_reg   (*((volatile unsigned int*) CPU1_ITAG_DRF_BIST_FAIL_reg))
#define CPU1_ITAG_DRF_BIST_FAIL_inst_adr                                             "0x00D1"
#define CPU1_ITAG_DRF_BIST_FAIL_inst                                                 0x00D1
#define CPU1_ITAG_DRF_BIST_FAIL_cpu1_itag_drf_mbist_fail_shift                       (0)
#define CPU1_ITAG_DRF_BIST_FAIL_cpu1_itag_drf_mbist_fail_mask                        (0x00000003)
#define CPU1_ITAG_DRF_BIST_FAIL_cpu1_itag_drf_mbist_fail(data)                       (0x00000003&((data)<<0))
#define CPU1_ITAG_DRF_BIST_FAIL_cpu1_itag_drf_mbist_fail_src(data)                   ((0x00000003&(data))>>0)
#define CPU1_ITAG_DRF_BIST_FAIL_get_cpu1_itag_drf_mbist_fail(data)                   ((0x00000003&(data))>>0)


#define CPU0_DDATA_BIST_FAIL                                                         0x1801D348
#define CPU0_DDATA_BIST_FAIL_reg_addr                                                "0xB801D348"
#define CPU0_DDATA_BIST_FAIL_reg                                                     0xB801D348
#define set_CPU0_DDATA_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU0_DDATA_BIST_FAIL_reg)=data)
#define get_CPU0_DDATA_BIST_FAIL_reg   (*((volatile unsigned int*) CPU0_DDATA_BIST_FAIL_reg))
#define CPU0_DDATA_BIST_FAIL_inst_adr                                                "0x00D2"
#define CPU0_DDATA_BIST_FAIL_inst                                                    0x00D2
#define CPU0_DDATA_BIST_FAIL_cpu0_ddata_mbist_fail_shift                             (0)
#define CPU0_DDATA_BIST_FAIL_cpu0_ddata_mbist_fail_mask                              (0x000000FF)
#define CPU0_DDATA_BIST_FAIL_cpu0_ddata_mbist_fail(data)                             (0x000000FF&((data)<<0))
#define CPU0_DDATA_BIST_FAIL_cpu0_ddata_mbist_fail_src(data)                         ((0x000000FF&(data))>>0)
#define CPU0_DDATA_BIST_FAIL_get_cpu0_ddata_mbist_fail(data)                         ((0x000000FF&(data))>>0)


#define CPU1_DDATA_BIST_FAIL                                                         0x1801D34C
#define CPU1_DDATA_BIST_FAIL_reg_addr                                                "0xB801D34C"
#define CPU1_DDATA_BIST_FAIL_reg                                                     0xB801D34C
#define set_CPU1_DDATA_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU1_DDATA_BIST_FAIL_reg)=data)
#define get_CPU1_DDATA_BIST_FAIL_reg   (*((volatile unsigned int*) CPU1_DDATA_BIST_FAIL_reg))
#define CPU1_DDATA_BIST_FAIL_inst_adr                                                "0x00D3"
#define CPU1_DDATA_BIST_FAIL_inst                                                    0x00D3
#define CPU1_DDATA_BIST_FAIL_cpu1_ddata_mbist_fail_shift                             (0)
#define CPU1_DDATA_BIST_FAIL_cpu1_ddata_mbist_fail_mask                              (0x000000FF)
#define CPU1_DDATA_BIST_FAIL_cpu1_ddata_mbist_fail(data)                             (0x000000FF&((data)<<0))
#define CPU1_DDATA_BIST_FAIL_cpu1_ddata_mbist_fail_src(data)                         ((0x000000FF&(data))>>0)
#define CPU1_DDATA_BIST_FAIL_get_cpu1_ddata_mbist_fail(data)                         ((0x000000FF&(data))>>0)


#define CPU0_DDATA_DRF_BIST_FAIL                                                     0x1801D350
#define CPU0_DDATA_DRF_BIST_FAIL_reg_addr                                            "0xB801D350"
#define CPU0_DDATA_DRF_BIST_FAIL_reg                                                 0xB801D350
#define set_CPU0_DDATA_DRF_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU0_DDATA_DRF_BIST_FAIL_reg)=data)
#define get_CPU0_DDATA_DRF_BIST_FAIL_reg   (*((volatile unsigned int*) CPU0_DDATA_DRF_BIST_FAIL_reg))
#define CPU0_DDATA_DRF_BIST_FAIL_inst_adr                                            "0x00D4"
#define CPU0_DDATA_DRF_BIST_FAIL_inst                                                0x00D4
#define CPU0_DDATA_DRF_BIST_FAIL_cpu0_ddata_drf_mbist_fail_shift                     (0)
#define CPU0_DDATA_DRF_BIST_FAIL_cpu0_ddata_drf_mbist_fail_mask                      (0x000000FF)
#define CPU0_DDATA_DRF_BIST_FAIL_cpu0_ddata_drf_mbist_fail(data)                     (0x000000FF&((data)<<0))
#define CPU0_DDATA_DRF_BIST_FAIL_cpu0_ddata_drf_mbist_fail_src(data)                 ((0x000000FF&(data))>>0)
#define CPU0_DDATA_DRF_BIST_FAIL_get_cpu0_ddata_drf_mbist_fail(data)                 ((0x000000FF&(data))>>0)


#define CPU1_DDATA_DRF_BIST_FAIL                                                     0x1801D354
#define CPU1_DDATA_DRF_BIST_FAIL_reg_addr                                            "0xB801D354"
#define CPU1_DDATA_DRF_BIST_FAIL_reg                                                 0xB801D354
#define set_CPU1_DDATA_DRF_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU1_DDATA_DRF_BIST_FAIL_reg)=data)
#define get_CPU1_DDATA_DRF_BIST_FAIL_reg   (*((volatile unsigned int*) CPU1_DDATA_DRF_BIST_FAIL_reg))
#define CPU1_DDATA_DRF_BIST_FAIL_inst_adr                                            "0x00D5"
#define CPU1_DDATA_DRF_BIST_FAIL_inst                                                0x00D5
#define CPU1_DDATA_DRF_BIST_FAIL_cpu1_ddata_drf_mbist_fail_shift                     (0)
#define CPU1_DDATA_DRF_BIST_FAIL_cpu1_ddata_drf_mbist_fail_mask                      (0x000000FF)
#define CPU1_DDATA_DRF_BIST_FAIL_cpu1_ddata_drf_mbist_fail(data)                     (0x000000FF&((data)<<0))
#define CPU1_DDATA_DRF_BIST_FAIL_cpu1_ddata_drf_mbist_fail_src(data)                 ((0x000000FF&(data))>>0)
#define CPU1_DDATA_DRF_BIST_FAIL_get_cpu1_ddata_drf_mbist_fail(data)                 ((0x000000FF&(data))>>0)


#define CPU0_DTAG_BIST_FAIL                                                          0x1801D358
#define CPU0_DTAG_BIST_FAIL_reg_addr                                                 "0xB801D358"
#define CPU0_DTAG_BIST_FAIL_reg                                                      0xB801D358
#define set_CPU0_DTAG_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU0_DTAG_BIST_FAIL_reg)=data)
#define get_CPU0_DTAG_BIST_FAIL_reg   (*((volatile unsigned int*) CPU0_DTAG_BIST_FAIL_reg))
#define CPU0_DTAG_BIST_FAIL_inst_adr                                                 "0x00D6"
#define CPU0_DTAG_BIST_FAIL_inst                                                     0x00D6
#define CPU0_DTAG_BIST_FAIL_cpu0_dtag_mbist_fail_shift                               (0)
#define CPU0_DTAG_BIST_FAIL_cpu0_dtag_mbist_fail_mask                                (0x0000000F)
#define CPU0_DTAG_BIST_FAIL_cpu0_dtag_mbist_fail(data)                               (0x0000000F&((data)<<0))
#define CPU0_DTAG_BIST_FAIL_cpu0_dtag_mbist_fail_src(data)                           ((0x0000000F&(data))>>0)
#define CPU0_DTAG_BIST_FAIL_get_cpu0_dtag_mbist_fail(data)                           ((0x0000000F&(data))>>0)


#define CPU1_DTAG_BIST_FAIL                                                          0x1801D35C
#define CPU1_DTAG_BIST_FAIL_reg_addr                                                 "0xB801D35C"
#define CPU1_DTAG_BIST_FAIL_reg                                                      0xB801D35C
#define set_CPU1_DTAG_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU1_DTAG_BIST_FAIL_reg)=data)
#define get_CPU1_DTAG_BIST_FAIL_reg   (*((volatile unsigned int*) CPU1_DTAG_BIST_FAIL_reg))
#define CPU1_DTAG_BIST_FAIL_inst_adr                                                 "0x00D7"
#define CPU1_DTAG_BIST_FAIL_inst                                                     0x00D7
#define CPU1_DTAG_BIST_FAIL_cpu1_dtag_mbist_fail_shift                               (0)
#define CPU1_DTAG_BIST_FAIL_cpu1_dtag_mbist_fail_mask                                (0x0000000F)
#define CPU1_DTAG_BIST_FAIL_cpu1_dtag_mbist_fail(data)                               (0x0000000F&((data)<<0))
#define CPU1_DTAG_BIST_FAIL_cpu1_dtag_mbist_fail_src(data)                           ((0x0000000F&(data))>>0)
#define CPU1_DTAG_BIST_FAIL_get_cpu1_dtag_mbist_fail(data)                           ((0x0000000F&(data))>>0)


#define CPU0_DTAG_DRF_BIST_FAIL                                                      0x1801D360
#define CPU0_DTAG_DRF_BIST_FAIL_reg_addr                                             "0xB801D360"
#define CPU0_DTAG_DRF_BIST_FAIL_reg                                                  0xB801D360
#define set_CPU0_DTAG_DRF_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU0_DTAG_DRF_BIST_FAIL_reg)=data)
#define get_CPU0_DTAG_DRF_BIST_FAIL_reg   (*((volatile unsigned int*) CPU0_DTAG_DRF_BIST_FAIL_reg))
#define CPU0_DTAG_DRF_BIST_FAIL_inst_adr                                             "0x00D8"
#define CPU0_DTAG_DRF_BIST_FAIL_inst                                                 0x00D8
#define CPU0_DTAG_DRF_BIST_FAIL_cpu0_dtag_drf_mbist_fail_shift                       (0)
#define CPU0_DTAG_DRF_BIST_FAIL_cpu0_dtag_drf_mbist_fail_mask                        (0x0000000F)
#define CPU0_DTAG_DRF_BIST_FAIL_cpu0_dtag_drf_mbist_fail(data)                       (0x0000000F&((data)<<0))
#define CPU0_DTAG_DRF_BIST_FAIL_cpu0_dtag_drf_mbist_fail_src(data)                   ((0x0000000F&(data))>>0)
#define CPU0_DTAG_DRF_BIST_FAIL_get_cpu0_dtag_drf_mbist_fail(data)                   ((0x0000000F&(data))>>0)


#define CPU1_DTAG_DRF_BIST_FAIL                                                      0x1801D364
#define CPU1_DTAG_DRF_BIST_FAIL_reg_addr                                             "0xB801D364"
#define CPU1_DTAG_DRF_BIST_FAIL_reg                                                  0xB801D364
#define set_CPU1_DTAG_DRF_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU1_DTAG_DRF_BIST_FAIL_reg)=data)
#define get_CPU1_DTAG_DRF_BIST_FAIL_reg   (*((volatile unsigned int*) CPU1_DTAG_DRF_BIST_FAIL_reg))
#define CPU1_DTAG_DRF_BIST_FAIL_inst_adr                                             "0x00D9"
#define CPU1_DTAG_DRF_BIST_FAIL_inst                                                 0x00D9
#define CPU1_DTAG_DRF_BIST_FAIL_cpu1_dtag_drf_mbist_fail_shift                       (0)
#define CPU1_DTAG_DRF_BIST_FAIL_cpu1_dtag_drf_mbist_fail_mask                        (0x0000000F)
#define CPU1_DTAG_DRF_BIST_FAIL_cpu1_dtag_drf_mbist_fail(data)                       (0x0000000F&((data)<<0))
#define CPU1_DTAG_DRF_BIST_FAIL_cpu1_dtag_drf_mbist_fail_src(data)                   ((0x0000000F&(data))>>0)
#define CPU1_DTAG_DRF_BIST_FAIL_get_cpu1_dtag_drf_mbist_fail(data)                   ((0x0000000F&(data))>>0)


#define CPU0_DDRITY_BIST_FAIL                                                        0x1801D368
#define CPU0_DDRITY_BIST_FAIL_reg_addr                                               "0xB801D368"
#define CPU0_DDRITY_BIST_FAIL_reg                                                    0xB801D368
#define set_CPU0_DDRITY_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU0_DDRITY_BIST_FAIL_reg)=data)
#define get_CPU0_DDRITY_BIST_FAIL_reg   (*((volatile unsigned int*) CPU0_DDRITY_BIST_FAIL_reg))
#define CPU0_DDRITY_BIST_FAIL_inst_adr                                               "0x00DA"
#define CPU0_DDRITY_BIST_FAIL_inst                                                   0x00DA
#define CPU0_DDRITY_BIST_FAIL_cpu0_ddrity_mbist_fail_shift                           (0)
#define CPU0_DDRITY_BIST_FAIL_cpu0_ddrity_mbist_fail_mask                            (0x00000001)
#define CPU0_DDRITY_BIST_FAIL_cpu0_ddrity_mbist_fail(data)                           (0x00000001&((data)<<0))
#define CPU0_DDRITY_BIST_FAIL_cpu0_ddrity_mbist_fail_src(data)                       ((0x00000001&(data))>>0)
#define CPU0_DDRITY_BIST_FAIL_get_cpu0_ddrity_mbist_fail(data)                       ((0x00000001&(data))>>0)


#define CPU1_DDRITY_BIST_FAIL                                                        0x1801D36C
#define CPU1_DDRITY_BIST_FAIL_reg_addr                                               "0xB801D36C"
#define CPU1_DDRITY_BIST_FAIL_reg                                                    0xB801D36C
#define set_CPU1_DDRITY_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU1_DDRITY_BIST_FAIL_reg)=data)
#define get_CPU1_DDRITY_BIST_FAIL_reg   (*((volatile unsigned int*) CPU1_DDRITY_BIST_FAIL_reg))
#define CPU1_DDRITY_BIST_FAIL_inst_adr                                               "0x00DB"
#define CPU1_DDRITY_BIST_FAIL_inst                                                   0x00DB
#define CPU1_DDRITY_BIST_FAIL_cpu1_ddrity_mbist_fail_shift                           (0)
#define CPU1_DDRITY_BIST_FAIL_cpu1_ddrity_mbist_fail_mask                            (0x00000001)
#define CPU1_DDRITY_BIST_FAIL_cpu1_ddrity_mbist_fail(data)                           (0x00000001&((data)<<0))
#define CPU1_DDRITY_BIST_FAIL_cpu1_ddrity_mbist_fail_src(data)                       ((0x00000001&(data))>>0)
#define CPU1_DDRITY_BIST_FAIL_get_cpu1_ddrity_mbist_fail(data)                       ((0x00000001&(data))>>0)


#define CPU0_DDRITY_DRF_BIST_FAIL                                                    0x1801D370
#define CPU0_DDRITY_DRF_BIST_FAIL_reg_addr                                           "0xB801D370"
#define CPU0_DDRITY_DRF_BIST_FAIL_reg                                                0xB801D370
#define set_CPU0_DDRITY_DRF_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU0_DDRITY_DRF_BIST_FAIL_reg)=data)
#define get_CPU0_DDRITY_DRF_BIST_FAIL_reg   (*((volatile unsigned int*) CPU0_DDRITY_DRF_BIST_FAIL_reg))
#define CPU0_DDRITY_DRF_BIST_FAIL_inst_adr                                           "0x00DC"
#define CPU0_DDRITY_DRF_BIST_FAIL_inst                                               0x00DC
#define CPU0_DDRITY_DRF_BIST_FAIL_cpu0_ddrity_drf_mbist_fail_shift                   (0)
#define CPU0_DDRITY_DRF_BIST_FAIL_cpu0_ddrity_drf_mbist_fail_mask                    (0x00000001)
#define CPU0_DDRITY_DRF_BIST_FAIL_cpu0_ddrity_drf_mbist_fail(data)                   (0x00000001&((data)<<0))
#define CPU0_DDRITY_DRF_BIST_FAIL_cpu0_ddrity_drf_mbist_fail_src(data)               ((0x00000001&(data))>>0)
#define CPU0_DDRITY_DRF_BIST_FAIL_get_cpu0_ddrity_drf_mbist_fail(data)               ((0x00000001&(data))>>0)


#define CPU1_DDRITY_DRF_BIST_FAIL                                                    0x1801D374
#define CPU1_DDRITY_DRF_BIST_FAIL_reg_addr                                           "0xB801D374"
#define CPU1_DDRITY_DRF_BIST_FAIL_reg                                                0xB801D374
#define set_CPU1_DDRITY_DRF_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU1_DDRITY_DRF_BIST_FAIL_reg)=data)
#define get_CPU1_DDRITY_DRF_BIST_FAIL_reg   (*((volatile unsigned int*) CPU1_DDRITY_DRF_BIST_FAIL_reg))
#define CPU1_DDRITY_DRF_BIST_FAIL_inst_adr                                           "0x00DD"
#define CPU1_DDRITY_DRF_BIST_FAIL_inst                                               0x00DD
#define CPU1_DDRITY_DRF_BIST_FAIL_cpu1_ddrity_drf_mbist_fail_shift                   (0)
#define CPU1_DDRITY_DRF_BIST_FAIL_cpu1_ddrity_drf_mbist_fail_mask                    (0x00000001)
#define CPU1_DDRITY_DRF_BIST_FAIL_cpu1_ddrity_drf_mbist_fail(data)                   (0x00000001&((data)<<0))
#define CPU1_DDRITY_DRF_BIST_FAIL_cpu1_ddrity_drf_mbist_fail_src(data)               ((0x00000001&(data))>>0)
#define CPU1_DDRITY_DRF_BIST_FAIL_get_cpu1_ddrity_drf_mbist_fail(data)               ((0x00000001&(data))>>0)


#define CPU0_SCU_BIST_FAIL                                                           0x1801D378
#define CPU0_SCU_BIST_FAIL_reg_addr                                                  "0xB801D378"
#define CPU0_SCU_BIST_FAIL_reg                                                       0xB801D378
#define set_CPU0_SCU_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU0_SCU_BIST_FAIL_reg)=data)
#define get_CPU0_SCU_BIST_FAIL_reg   (*((volatile unsigned int*) CPU0_SCU_BIST_FAIL_reg))
#define CPU0_SCU_BIST_FAIL_inst_adr                                                  "0x00DE"
#define CPU0_SCU_BIST_FAIL_inst                                                      0x00DE
#define CPU0_SCU_BIST_FAIL_cpu0_scu_mbist_fail_shift                                 (0)
#define CPU0_SCU_BIST_FAIL_cpu0_scu_mbist_fail_mask                                  (0x0000000F)
#define CPU0_SCU_BIST_FAIL_cpu0_scu_mbist_fail(data)                                 (0x0000000F&((data)<<0))
#define CPU0_SCU_BIST_FAIL_cpu0_scu_mbist_fail_src(data)                             ((0x0000000F&(data))>>0)
#define CPU0_SCU_BIST_FAIL_get_cpu0_scu_mbist_fail(data)                             ((0x0000000F&(data))>>0)


#define CPU1_SCU_BIST_FAIL                                                           0x1801D37C
#define CPU1_SCU_BIST_FAIL_reg_addr                                                  "0xB801D37C"
#define CPU1_SCU_BIST_FAIL_reg                                                       0xB801D37C
#define set_CPU1_SCU_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU1_SCU_BIST_FAIL_reg)=data)
#define get_CPU1_SCU_BIST_FAIL_reg   (*((volatile unsigned int*) CPU1_SCU_BIST_FAIL_reg))
#define CPU1_SCU_BIST_FAIL_inst_adr                                                  "0x00DF"
#define CPU1_SCU_BIST_FAIL_inst                                                      0x00DF
#define CPU1_SCU_BIST_FAIL_cpu1_scu_mbist_fail_shift                                 (0)
#define CPU1_SCU_BIST_FAIL_cpu1_scu_mbist_fail_mask                                  (0x0000000F)
#define CPU1_SCU_BIST_FAIL_cpu1_scu_mbist_fail(data)                                 (0x0000000F&((data)<<0))
#define CPU1_SCU_BIST_FAIL_cpu1_scu_mbist_fail_src(data)                             ((0x0000000F&(data))>>0)
#define CPU1_SCU_BIST_FAIL_get_cpu1_scu_mbist_fail(data)                             ((0x0000000F&(data))>>0)


#define CPU0_SCU_DRF_BIST_FAIL                                                       0x1801D380
#define CPU0_SCU_DRF_BIST_FAIL_reg_addr                                              "0xB801D380"
#define CPU0_SCU_DRF_BIST_FAIL_reg                                                   0xB801D380
#define set_CPU0_SCU_DRF_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU0_SCU_DRF_BIST_FAIL_reg)=data)
#define get_CPU0_SCU_DRF_BIST_FAIL_reg   (*((volatile unsigned int*) CPU0_SCU_DRF_BIST_FAIL_reg))
#define CPU0_SCU_DRF_BIST_FAIL_inst_adr                                              "0x00E0"
#define CPU0_SCU_DRF_BIST_FAIL_inst                                                  0x00E0
#define CPU0_SCU_DRF_BIST_FAIL_cpu0_scu_drf_mbist_fail_shift                         (0)
#define CPU0_SCU_DRF_BIST_FAIL_cpu0_scu_drf_mbist_fail_mask                          (0x0000000F)
#define CPU0_SCU_DRF_BIST_FAIL_cpu0_scu_drf_mbist_fail(data)                         (0x0000000F&((data)<<0))
#define CPU0_SCU_DRF_BIST_FAIL_cpu0_scu_drf_mbist_fail_src(data)                     ((0x0000000F&(data))>>0)
#define CPU0_SCU_DRF_BIST_FAIL_get_cpu0_scu_drf_mbist_fail(data)                     ((0x0000000F&(data))>>0)


#define CPU1_SCU_DRF_BIST_FAIL                                                       0x1801D384
#define CPU1_SCU_DRF_BIST_FAIL_reg_addr                                              "0xB801D384"
#define CPU1_SCU_DRF_BIST_FAIL_reg                                                   0xB801D384
#define set_CPU1_SCU_DRF_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU1_SCU_DRF_BIST_FAIL_reg)=data)
#define get_CPU1_SCU_DRF_BIST_FAIL_reg   (*((volatile unsigned int*) CPU1_SCU_DRF_BIST_FAIL_reg))
#define CPU1_SCU_DRF_BIST_FAIL_inst_adr                                              "0x00E1"
#define CPU1_SCU_DRF_BIST_FAIL_inst                                                  0x00E1
#define CPU1_SCU_DRF_BIST_FAIL_cpu1_scu_drf_mbist_fail_shift                         (0)
#define CPU1_SCU_DRF_BIST_FAIL_cpu1_scu_drf_mbist_fail_mask                          (0x0000000F)
#define CPU1_SCU_DRF_BIST_FAIL_cpu1_scu_drf_mbist_fail(data)                         (0x0000000F&((data)<<0))
#define CPU1_SCU_DRF_BIST_FAIL_cpu1_scu_drf_mbist_fail_src(data)                     ((0x0000000F&(data))>>0)
#define CPU1_SCU_DRF_BIST_FAIL_get_cpu1_scu_drf_mbist_fail(data)                     ((0x0000000F&(data))>>0)


#define CPU0_TLB_BIST_FAIL                                                           0x1801D388
#define CPU0_TLB_BIST_FAIL_reg_addr                                                  "0xB801D388"
#define CPU0_TLB_BIST_FAIL_reg                                                       0xB801D388
#define set_CPU0_TLB_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU0_TLB_BIST_FAIL_reg)=data)
#define get_CPU0_TLB_BIST_FAIL_reg   (*((volatile unsigned int*) CPU0_TLB_BIST_FAIL_reg))
#define CPU0_TLB_BIST_FAIL_inst_adr                                                  "0x00E2"
#define CPU0_TLB_BIST_FAIL_inst                                                      0x00E2
#define CPU0_TLB_BIST_FAIL_cpu0_tlb_mbist_fail_shift                                 (0)
#define CPU0_TLB_BIST_FAIL_cpu0_tlb_mbist_fail_mask                                  (0x00000003)
#define CPU0_TLB_BIST_FAIL_cpu0_tlb_mbist_fail(data)                                 (0x00000003&((data)<<0))
#define CPU0_TLB_BIST_FAIL_cpu0_tlb_mbist_fail_src(data)                             ((0x00000003&(data))>>0)
#define CPU0_TLB_BIST_FAIL_get_cpu0_tlb_mbist_fail(data)                             ((0x00000003&(data))>>0)


#define CPU1_TLB_BIST_FAIL                                                           0x1801D38C
#define CPU1_TLB_BIST_FAIL_reg_addr                                                  "0xB801D38C"
#define CPU1_TLB_BIST_FAIL_reg                                                       0xB801D38C
#define set_CPU1_TLB_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU1_TLB_BIST_FAIL_reg)=data)
#define get_CPU1_TLB_BIST_FAIL_reg   (*((volatile unsigned int*) CPU1_TLB_BIST_FAIL_reg))
#define CPU1_TLB_BIST_FAIL_inst_adr                                                  "0x00E3"
#define CPU1_TLB_BIST_FAIL_inst                                                      0x00E3
#define CPU1_TLB_BIST_FAIL_cpu1_tlb_mbist_fail_shift                                 (0)
#define CPU1_TLB_BIST_FAIL_cpu1_tlb_mbist_fail_mask                                  (0x00000003)
#define CPU1_TLB_BIST_FAIL_cpu1_tlb_mbist_fail(data)                                 (0x00000003&((data)<<0))
#define CPU1_TLB_BIST_FAIL_cpu1_tlb_mbist_fail_src(data)                             ((0x00000003&(data))>>0)
#define CPU1_TLB_BIST_FAIL_get_cpu1_tlb_mbist_fail(data)                             ((0x00000003&(data))>>0)


#define CPU0_TLB_DRF_BIST_FAIL                                                       0x1801D390
#define CPU0_TLB_DRF_BIST_FAIL_reg_addr                                              "0xB801D390"
#define CPU0_TLB_DRF_BIST_FAIL_reg                                                   0xB801D390
#define set_CPU0_TLB_DRF_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU0_TLB_DRF_BIST_FAIL_reg)=data)
#define get_CPU0_TLB_DRF_BIST_FAIL_reg   (*((volatile unsigned int*) CPU0_TLB_DRF_BIST_FAIL_reg))
#define CPU0_TLB_DRF_BIST_FAIL_inst_adr                                              "0x00E4"
#define CPU0_TLB_DRF_BIST_FAIL_inst                                                  0x00E4
#define CPU0_TLB_DRF_BIST_FAIL_cpu0_tlb_drf_mbist_fail_shift                         (0)
#define CPU0_TLB_DRF_BIST_FAIL_cpu0_tlb_drf_mbist_fail_mask                          (0x00000003)
#define CPU0_TLB_DRF_BIST_FAIL_cpu0_tlb_drf_mbist_fail(data)                         (0x00000003&((data)<<0))
#define CPU0_TLB_DRF_BIST_FAIL_cpu0_tlb_drf_mbist_fail_src(data)                     ((0x00000003&(data))>>0)
#define CPU0_TLB_DRF_BIST_FAIL_get_cpu0_tlb_drf_mbist_fail(data)                     ((0x00000003&(data))>>0)


#define CPU1_TLB_DRF_BIST_FAIL                                                       0x1801D394
#define CPU1_TLB_DRF_BIST_FAIL_reg_addr                                              "0xB801D394"
#define CPU1_TLB_DRF_BIST_FAIL_reg                                                   0xB801D394
#define set_CPU1_TLB_DRF_BIST_FAIL_reg(data)   (*((volatile unsigned int*) CPU1_TLB_DRF_BIST_FAIL_reg)=data)
#define get_CPU1_TLB_DRF_BIST_FAIL_reg   (*((volatile unsigned int*) CPU1_TLB_DRF_BIST_FAIL_reg))
#define CPU1_TLB_DRF_BIST_FAIL_inst_adr                                              "0x00E5"
#define CPU1_TLB_DRF_BIST_FAIL_inst                                                  0x00E5
#define CPU1_TLB_DRF_BIST_FAIL_cpu1_tlb_drf_mbist_fail_shift                         (0)
#define CPU1_TLB_DRF_BIST_FAIL_cpu1_tlb_drf_mbist_fail_mask                          (0x00000003)
#define CPU1_TLB_DRF_BIST_FAIL_cpu1_tlb_drf_mbist_fail(data)                         (0x00000003&((data)<<0))
#define CPU1_TLB_DRF_BIST_FAIL_cpu1_tlb_drf_mbist_fail_src(data)                     ((0x00000003&(data))>>0)
#define CPU1_TLB_DRF_BIST_FAIL_get_cpu1_tlb_drf_mbist_fail(data)                     ((0x00000003&(data))>>0)


#define L2_BIST_BISR_RSTN                                                            0x1801D400
#define L2_BIST_BISR_RSTN_reg_addr                                                   "0xB801D400"
#define L2_BIST_BISR_RSTN_reg                                                        0xB801D400
#define set_L2_BIST_BISR_RSTN_reg(data)   (*((volatile unsigned int*) L2_BIST_BISR_RSTN_reg)=data)
#define get_L2_BIST_BISR_RSTN_reg   (*((volatile unsigned int*) L2_BIST_BISR_RSTN_reg))
#define L2_BIST_BISR_RSTN_inst_adr                                                   "0x0000"
#define L2_BIST_BISR_RSTN_inst                                                       0x0000
#define L2_BIST_BISR_RSTN_MBIST_RSTN_shift                                           (3)
#define L2_BIST_BISR_RSTN_MBIST_RSTN_mask                                            (0x00000008)
#define L2_BIST_BISR_RSTN_MBIST_RSTN(data)                                           (0x00000008&((data)<<3))
#define L2_BIST_BISR_RSTN_MBIST_RSTN_src(data)                                       ((0x00000008&(data))>>3)
#define L2_BIST_BISR_RSTN_get_MBIST_RSTN(data)                                       ((0x00000008&(data))>>3)
#define L2_BIST_BISR_RSTN_L2_TAG_BIST_RSTN_shift                                     (2)
#define L2_BIST_BISR_RSTN_L2_TAG_BIST_RSTN_mask                                      (0x00000004)
#define L2_BIST_BISR_RSTN_L2_TAG_BIST_RSTN(data)                                     (0x00000004&((data)<<2))
#define L2_BIST_BISR_RSTN_L2_TAG_BIST_RSTN_src(data)                                 ((0x00000004&(data))>>2)
#define L2_BIST_BISR_RSTN_get_L2_TAG_BIST_RSTN(data)                                 ((0x00000004&(data))>>2)
#define L2_BIST_BISR_RSTN_L2_DATA_PWR_RSTN_shift                                     (1)
#define L2_BIST_BISR_RSTN_L2_DATA_PWR_RSTN_mask                                      (0x00000002)
#define L2_BIST_BISR_RSTN_L2_DATA_PWR_RSTN(data)                                     (0x00000002&((data)<<1))
#define L2_BIST_BISR_RSTN_L2_DATA_PWR_RSTN_src(data)                                 ((0x00000002&(data))>>1)
#define L2_BIST_BISR_RSTN_get_L2_DATA_PWR_RSTN(data)                                 ((0x00000002&(data))>>1)
#define L2_BIST_BISR_RSTN_L2_DATA_BISR_RSTN_shift                                    (0)
#define L2_BIST_BISR_RSTN_L2_DATA_BISR_RSTN_mask                                     (0x00000001)
#define L2_BIST_BISR_RSTN_L2_DATA_BISR_RSTN(data)                                    (0x00000001&((data)<<0))
#define L2_BIST_BISR_RSTN_L2_DATA_BISR_RSTN_src(data)                                ((0x00000001&(data))>>0)
#define L2_BIST_BISR_RSTN_get_L2_DATA_BISR_RSTN(data)                                ((0x00000001&(data))>>0)


#define HOLD_REMAP                                                                   0x1801D404
#define HOLD_REMAP_reg_addr                                                          "0xB801D404"
#define HOLD_REMAP_reg                                                               0xB801D404
#define set_HOLD_REMAP_reg(data)   (*((volatile unsigned int*) HOLD_REMAP_reg)=data)
#define get_HOLD_REMAP_reg   (*((volatile unsigned int*) HOLD_REMAP_reg))
#define HOLD_REMAP_inst_adr                                                          "0x0001"
#define HOLD_REMAP_inst                                                              0x0001
#define HOLD_REMAP_L2_DATA_HOLD_REMAP_shift                                          (0)
#define HOLD_REMAP_L2_DATA_HOLD_REMAP_mask                                           (0x00000001)
#define HOLD_REMAP_L2_DATA_HOLD_REMAP(data)                                          (0x00000001&((data)<<0))
#define HOLD_REMAP_L2_DATA_HOLD_REMAP_src(data)                                      ((0x00000001&(data))>>0)
#define HOLD_REMAP_get_L2_DATA_HOLD_REMAP(data)                                      ((0x00000001&(data))>>0)


#define SECOND_RUN_EN                                                                0x1801D408
#define SECOND_RUN_EN_reg_addr                                                       "0xB801D408"
#define SECOND_RUN_EN_reg                                                            0xB801D408
#define set_SECOND_RUN_EN_reg(data)   (*((volatile unsigned int*) SECOND_RUN_EN_reg)=data)
#define get_SECOND_RUN_EN_reg   (*((volatile unsigned int*) SECOND_RUN_EN_reg))
#define SECOND_RUN_EN_inst_adr                                                       "0x0002"
#define SECOND_RUN_EN_inst                                                           0x0002
#define SECOND_RUN_EN_L2_DATA_SECOND_RUN_EN_shift                                    (0)
#define SECOND_RUN_EN_L2_DATA_SECOND_RUN_EN_mask                                     (0x00000001)
#define SECOND_RUN_EN_L2_DATA_SECOND_RUN_EN(data)                                    (0x00000001&((data)<<0))
#define SECOND_RUN_EN_L2_DATA_SECOND_RUN_EN_src(data)                                ((0x00000001&(data))>>0)
#define SECOND_RUN_EN_get_L2_DATA_SECOND_RUN_EN(data)                                ((0x00000001&(data))>>0)


#define DRF_BIST_BISR_MODE                                                           0x1801D40C
#define DRF_BIST_BISR_MODE_reg_addr                                                  "0xB801D40C"
#define DRF_BIST_BISR_MODE_reg                                                       0xB801D40C
#define set_DRF_BIST_BISR_MODE_reg(data)   (*((volatile unsigned int*) DRF_BIST_BISR_MODE_reg)=data)
#define get_DRF_BIST_BISR_MODE_reg   (*((volatile unsigned int*) DRF_BIST_BISR_MODE_reg))
#define DRF_BIST_BISR_MODE_inst_adr                                                  "0x0003"
#define DRF_BIST_BISR_MODE_inst                                                      0x0003
#define DRF_BIST_BISR_MODE_L2_TAG_BIST_MODE_shift                                    (3)
#define DRF_BIST_BISR_MODE_L2_TAG_BIST_MODE_mask                                     (0x00000008)
#define DRF_BIST_BISR_MODE_L2_TAG_BIST_MODE(data)                                    (0x00000008&((data)<<3))
#define DRF_BIST_BISR_MODE_L2_TAG_BIST_MODE_src(data)                                ((0x00000008&(data))>>3)
#define DRF_BIST_BISR_MODE_get_L2_TAG_BIST_MODE(data)                                ((0x00000008&(data))>>3)
#define DRF_BIST_BISR_MODE_L2_TAG_DRF_BIST_MODE_shift                                (2)
#define DRF_BIST_BISR_MODE_L2_TAG_DRF_BIST_MODE_mask                                 (0x00000004)
#define DRF_BIST_BISR_MODE_L2_TAG_DRF_BIST_MODE(data)                                (0x00000004&((data)<<2))
#define DRF_BIST_BISR_MODE_L2_TAG_DRF_BIST_MODE_src(data)                            ((0x00000004&(data))>>2)
#define DRF_BIST_BISR_MODE_get_L2_TAG_DRF_BIST_MODE(data)                            ((0x00000004&(data))>>2)
#define DRF_BIST_BISR_MODE_L2_DATA_DRF_BISR_MODE_shift                               (0)
#define DRF_BIST_BISR_MODE_L2_DATA_DRF_BISR_MODE_mask                                (0x00000001)
#define DRF_BIST_BISR_MODE_L2_DATA_DRF_BISR_MODE(data)                               (0x00000001&((data)<<0))
#define DRF_BIST_BISR_MODE_L2_DATA_DRF_BISR_MODE_src(data)                           ((0x00000001&(data))>>0)
#define DRF_BIST_BISR_MODE_get_L2_DATA_DRF_BISR_MODE(data)                           ((0x00000001&(data))>>0)


#define DRF_BISR_TEST_RESUME                                                         0x1801D410
#define DRF_BISR_TEST_RESUME_reg_addr                                                "0xB801D410"
#define DRF_BISR_TEST_RESUME_reg                                                     0xB801D410
#define set_DRF_BISR_TEST_RESUME_reg(data)   (*((volatile unsigned int*) DRF_BISR_TEST_RESUME_reg)=data)
#define get_DRF_BISR_TEST_RESUME_reg   (*((volatile unsigned int*) DRF_BISR_TEST_RESUME_reg))
#define DRF_BISR_TEST_RESUME_inst_adr                                                "0x0004"
#define DRF_BISR_TEST_RESUME_inst                                                    0x0004
#define DRF_BISR_TEST_RESUME_L2_TAG_DRF_TEST_RESUME_shift                            (1)
#define DRF_BISR_TEST_RESUME_L2_TAG_DRF_TEST_RESUME_mask                             (0x00000002)
#define DRF_BISR_TEST_RESUME_L2_TAG_DRF_TEST_RESUME(data)                            (0x00000002&((data)<<1))
#define DRF_BISR_TEST_RESUME_L2_TAG_DRF_TEST_RESUME_src(data)                        ((0x00000002&(data))>>1)
#define DRF_BISR_TEST_RESUME_get_L2_TAG_DRF_TEST_RESUME(data)                        ((0x00000002&(data))>>1)
#define DRF_BISR_TEST_RESUME_L2_DATA_DRF_BISR_TEST_RESUME_shift                      (0)
#define DRF_BISR_TEST_RESUME_L2_DATA_DRF_BISR_TEST_RESUME_mask                       (0x00000001)
#define DRF_BISR_TEST_RESUME_L2_DATA_DRF_BISR_TEST_RESUME(data)                      (0x00000001&((data)<<0))
#define DRF_BISR_TEST_RESUME_L2_DATA_DRF_BISR_TEST_RESUME_src(data)                  ((0x00000001&(data))>>0)
#define DRF_BISR_TEST_RESUME_get_L2_DATA_DRF_BISR_TEST_RESUME(data)                  ((0x00000001&(data))>>0)


#define BISR_REPAIR                                                                  0x1801D414
#define BISR_REPAIR_reg_addr                                                         "0xB801D414"
#define BISR_REPAIR_reg                                                              0xB801D414
#define set_BISR_REPAIR_reg(data)   (*((volatile unsigned int*) BISR_REPAIR_reg)=data)
#define get_BISR_REPAIR_reg   (*((volatile unsigned int*) BISR_REPAIR_reg))
#define BISR_REPAIR_inst_adr                                                         "0x0005"
#define BISR_REPAIR_inst                                                             0x0005
#define BISR_REPAIR_L2_DATA_BISR_REPAIRED_shift                                      (0)
#define BISR_REPAIR_L2_DATA_BISR_REPAIRED_mask                                       (0x00000001)
#define BISR_REPAIR_L2_DATA_BISR_REPAIRED(data)                                      (0x00000001&((data)<<0))
#define BISR_REPAIR_L2_DATA_BISR_REPAIRED_src(data)                                  ((0x00000001&(data))>>0)
#define BISR_REPAIR_get_L2_DATA_BISR_REPAIRED(data)                                  ((0x00000001&(data))>>0)


#define BISR_DONE                                                                    0x1801D418
#define BISR_DONE_reg_addr                                                           "0xB801D418"
#define BISR_DONE_reg                                                                0xB801D418
#define set_BISR_DONE_reg(data)   (*((volatile unsigned int*) BISR_DONE_reg)=data)
#define get_BISR_DONE_reg   (*((volatile unsigned int*) BISR_DONE_reg))
#define BISR_DONE_inst_adr                                                           "0x0006"
#define BISR_DONE_inst                                                               0x0006
#define BISR_DONE_L2_TAG_BIST_DONE_shift                                             (1)
#define BISR_DONE_L2_TAG_BIST_DONE_mask                                              (0x00000002)
#define BISR_DONE_L2_TAG_BIST_DONE(data)                                             (0x00000002&((data)<<1))
#define BISR_DONE_L2_TAG_BIST_DONE_src(data)                                         ((0x00000002&(data))>>1)
#define BISR_DONE_get_L2_TAG_BIST_DONE(data)                                         ((0x00000002&(data))>>1)
#define BISR_DONE_L2_DATA_BISR_DONE_shift                                            (0)
#define BISR_DONE_L2_DATA_BISR_DONE_mask                                             (0x00000001)
#define BISR_DONE_L2_DATA_BISR_DONE(data)                                            (0x00000001&((data)<<0))
#define BISR_DONE_L2_DATA_BISR_DONE_src(data)                                        ((0x00000001&(data))>>0)
#define BISR_DONE_get_L2_DATA_BISR_DONE(data)                                        ((0x00000001&(data))>>0)


#define DRF_BISR_DONE                                                                0x1801D41C
#define DRF_BISR_DONE_reg_addr                                                       "0xB801D41C"
#define DRF_BISR_DONE_reg                                                            0xB801D41C
#define set_DRF_BISR_DONE_reg(data)   (*((volatile unsigned int*) DRF_BISR_DONE_reg)=data)
#define get_DRF_BISR_DONE_reg   (*((volatile unsigned int*) DRF_BISR_DONE_reg))
#define DRF_BISR_DONE_inst_adr                                                       "0x0007"
#define DRF_BISR_DONE_inst                                                           0x0007
#define DRF_BISR_DONE_L2_TAG_DRF_BIST_DONE_shift                                     (1)
#define DRF_BISR_DONE_L2_TAG_DRF_BIST_DONE_mask                                      (0x00000002)
#define DRF_BISR_DONE_L2_TAG_DRF_BIST_DONE(data)                                     (0x00000002&((data)<<1))
#define DRF_BISR_DONE_L2_TAG_DRF_BIST_DONE_src(data)                                 ((0x00000002&(data))>>1)
#define DRF_BISR_DONE_get_L2_TAG_DRF_BIST_DONE(data)                                 ((0x00000002&(data))>>1)
#define DRF_BISR_DONE_L2_DATA_DRF_BISR_DONE_shift                                    (0)
#define DRF_BISR_DONE_L2_DATA_DRF_BISR_DONE_mask                                     (0x00000001)
#define DRF_BISR_DONE_L2_DATA_DRF_BISR_DONE(data)                                    (0x00000001&((data)<<0))
#define DRF_BISR_DONE_L2_DATA_DRF_BISR_DONE_src(data)                                ((0x00000001&(data))>>0)
#define DRF_BISR_DONE_get_L2_DATA_DRF_BISR_DONE(data)                                ((0x00000001&(data))>>0)


#define DRF_START_PAUSE                                                              0x1801D420
#define DRF_START_PAUSE_reg_addr                                                     "0xB801D420"
#define DRF_START_PAUSE_reg                                                          0xB801D420
#define set_DRF_START_PAUSE_reg(data)   (*((volatile unsigned int*) DRF_START_PAUSE_reg)=data)
#define get_DRF_START_PAUSE_reg   (*((volatile unsigned int*) DRF_START_PAUSE_reg))
#define DRF_START_PAUSE_inst_adr                                                     "0x0008"
#define DRF_START_PAUSE_inst                                                         0x0008
#define DRF_START_PAUSE_L2_TAG_DRF_START_PAUSE_shift                                 (1)
#define DRF_START_PAUSE_L2_TAG_DRF_START_PAUSE_mask                                  (0x00000002)
#define DRF_START_PAUSE_L2_TAG_DRF_START_PAUSE(data)                                 (0x00000002&((data)<<1))
#define DRF_START_PAUSE_L2_TAG_DRF_START_PAUSE_src(data)                             ((0x00000002&(data))>>1)
#define DRF_START_PAUSE_get_L2_TAG_DRF_START_PAUSE(data)                             ((0x00000002&(data))>>1)
#define DRF_START_PAUSE_L2_DATA_DRF_BISR_START_PAUSE_shift                           (0)
#define DRF_START_PAUSE_L2_DATA_DRF_BISR_START_PAUSE_mask                            (0x00000001)
#define DRF_START_PAUSE_L2_DATA_DRF_BISR_START_PAUSE(data)                           (0x00000001&((data)<<0))
#define DRF_START_PAUSE_L2_DATA_DRF_BISR_START_PAUSE_src(data)                       ((0x00000001&(data))>>0)
#define DRF_START_PAUSE_get_L2_DATA_DRF_BISR_START_PAUSE(data)                       ((0x00000001&(data))>>0)


#define BISR_FAIL_GROUP                                                              0x1801D424
#define BISR_FAIL_GROUP_reg_addr                                                     "0xB801D424"
#define BISR_FAIL_GROUP_reg                                                          0xB801D424
#define set_BISR_FAIL_GROUP_reg(data)   (*((volatile unsigned int*) BISR_FAIL_GROUP_reg)=data)
#define get_BISR_FAIL_GROUP_reg   (*((volatile unsigned int*) BISR_FAIL_GROUP_reg))
#define BISR_FAIL_GROUP_inst_adr                                                     "0x0009"
#define BISR_FAIL_GROUP_inst                                                         0x0009
#define BISR_FAIL_GROUP_L2_TAG_BIST_FAIL_G_shift                                     (1)
#define BISR_FAIL_GROUP_L2_TAG_BIST_FAIL_G_mask                                      (0x00000002)
#define BISR_FAIL_GROUP_L2_TAG_BIST_FAIL_G(data)                                     (0x00000002&((data)<<1))
#define BISR_FAIL_GROUP_L2_TAG_BIST_FAIL_G_src(data)                                 ((0x00000002&(data))>>1)
#define BISR_FAIL_GROUP_get_L2_TAG_BIST_FAIL_G(data)                                 ((0x00000002&(data))>>1)
#define BISR_FAIL_GROUP_L2_DATA_BISR_FAIL_G_shift                                    (0)
#define BISR_FAIL_GROUP_L2_DATA_BISR_FAIL_G_mask                                     (0x00000001)
#define BISR_FAIL_GROUP_L2_DATA_BISR_FAIL_G(data)                                    (0x00000001&((data)<<0))
#define BISR_FAIL_GROUP_L2_DATA_BISR_FAIL_G_src(data)                                ((0x00000001&(data))>>0)
#define BISR_FAIL_GROUP_get_L2_DATA_BISR_FAIL_G(data)                                ((0x00000001&(data))>>0)


#define BISR_FAIL_DATA_SEP                                                           0x1801D428
#define BISR_FAIL_DATA_SEP_reg_addr                                                  "0xB801D428"
#define BISR_FAIL_DATA_SEP_reg                                                       0xB801D428
#define set_BISR_FAIL_DATA_SEP_reg(data)   (*((volatile unsigned int*) BISR_FAIL_DATA_SEP_reg)=data)
#define get_BISR_FAIL_DATA_SEP_reg   (*((volatile unsigned int*) BISR_FAIL_DATA_SEP_reg))
#define BISR_FAIL_DATA_SEP_inst_adr                                                  "0x000A"
#define BISR_FAIL_DATA_SEP_inst                                                      0x000A
#define BISR_FAIL_DATA_SEP_L2_DATA_BISR_FAIL_shift                                   (0)
#define BISR_FAIL_DATA_SEP_L2_DATA_BISR_FAIL_mask                                    (0x000000FF)
#define BISR_FAIL_DATA_SEP_L2_DATA_BISR_FAIL(data)                                   (0x000000FF&((data)<<0))
#define BISR_FAIL_DATA_SEP_L2_DATA_BISR_FAIL_src(data)                               ((0x000000FF&(data))>>0)
#define BISR_FAIL_DATA_SEP_get_L2_DATA_BISR_FAIL(data)                               ((0x000000FF&(data))>>0)


#define BISR_FAIL_TAG_SEP                                                            0x1801D42C
#define BISR_FAIL_TAG_SEP_reg_addr                                                   "0xB801D42C"
#define BISR_FAIL_TAG_SEP_reg                                                        0xB801D42C
#define set_BISR_FAIL_TAG_SEP_reg(data)   (*((volatile unsigned int*) BISR_FAIL_TAG_SEP_reg)=data)
#define get_BISR_FAIL_TAG_SEP_reg   (*((volatile unsigned int*) BISR_FAIL_TAG_SEP_reg))
#define BISR_FAIL_TAG_SEP_inst_adr                                                   "0x000B"
#define BISR_FAIL_TAG_SEP_inst                                                       0x000B
#define BISR_FAIL_TAG_SEP_L2_TAG_BIST_FAIL_shift                                     (0)
#define BISR_FAIL_TAG_SEP_L2_TAG_BIST_FAIL_mask                                      (0x000000FF)
#define BISR_FAIL_TAG_SEP_L2_TAG_BIST_FAIL(data)                                     (0x000000FF&((data)<<0))
#define BISR_FAIL_TAG_SEP_L2_TAG_BIST_FAIL_src(data)                                 ((0x000000FF&(data))>>0)
#define BISR_FAIL_TAG_SEP_get_L2_TAG_BIST_FAIL(data)                                 ((0x000000FF&(data))>>0)


#define DRF_BISR_FAIL_GROUP                                                          0x1801D430
#define DRF_BISR_FAIL_GROUP_reg_addr                                                 "0xB801D430"
#define DRF_BISR_FAIL_GROUP_reg                                                      0xB801D430
#define set_DRF_BISR_FAIL_GROUP_reg(data)   (*((volatile unsigned int*) DRF_BISR_FAIL_GROUP_reg)=data)
#define get_DRF_BISR_FAIL_GROUP_reg   (*((volatile unsigned int*) DRF_BISR_FAIL_GROUP_reg))
#define DRF_BISR_FAIL_GROUP_inst_adr                                                 "0x000C"
#define DRF_BISR_FAIL_GROUP_inst                                                     0x000C
#define DRF_BISR_FAIL_GROUP_L2_TAG_DRF_BIST_FAIL_G_shift                             (1)
#define DRF_BISR_FAIL_GROUP_L2_TAG_DRF_BIST_FAIL_G_mask                              (0x00000002)
#define DRF_BISR_FAIL_GROUP_L2_TAG_DRF_BIST_FAIL_G(data)                             (0x00000002&((data)<<1))
#define DRF_BISR_FAIL_GROUP_L2_TAG_DRF_BIST_FAIL_G_src(data)                         ((0x00000002&(data))>>1)
#define DRF_BISR_FAIL_GROUP_get_L2_TAG_DRF_BIST_FAIL_G(data)                         ((0x00000002&(data))>>1)
#define DRF_BISR_FAIL_GROUP_L2_DATA_DRF_BISR_FAIL_G_shift                            (0)
#define DRF_BISR_FAIL_GROUP_L2_DATA_DRF_BISR_FAIL_G_mask                             (0x00000001)
#define DRF_BISR_FAIL_GROUP_L2_DATA_DRF_BISR_FAIL_G(data)                            (0x00000001&((data)<<0))
#define DRF_BISR_FAIL_GROUP_L2_DATA_DRF_BISR_FAIL_G_src(data)                        ((0x00000001&(data))>>0)
#define DRF_BISR_FAIL_GROUP_get_L2_DATA_DRF_BISR_FAIL_G(data)                        ((0x00000001&(data))>>0)


#define DRF_BISR_FAIL_DATA_SEP                                                       0x1801D434
#define DRF_BISR_FAIL_DATA_SEP_reg_addr                                              "0xB801D434"
#define DRF_BISR_FAIL_DATA_SEP_reg                                                   0xB801D434
#define set_DRF_BISR_FAIL_DATA_SEP_reg(data)   (*((volatile unsigned int*) DRF_BISR_FAIL_DATA_SEP_reg)=data)
#define get_DRF_BISR_FAIL_DATA_SEP_reg   (*((volatile unsigned int*) DRF_BISR_FAIL_DATA_SEP_reg))
#define DRF_BISR_FAIL_DATA_SEP_inst_adr                                              "0x000D"
#define DRF_BISR_FAIL_DATA_SEP_inst                                                  0x000D
#define DRF_BISR_FAIL_DATA_SEP_L2_DATA_DRF_BISR_FAIL_shift                           (0)
#define DRF_BISR_FAIL_DATA_SEP_L2_DATA_DRF_BISR_FAIL_mask                            (0x000000FF)
#define DRF_BISR_FAIL_DATA_SEP_L2_DATA_DRF_BISR_FAIL(data)                           (0x000000FF&((data)<<0))
#define DRF_BISR_FAIL_DATA_SEP_L2_DATA_DRF_BISR_FAIL_src(data)                       ((0x000000FF&(data))>>0)
#define DRF_BISR_FAIL_DATA_SEP_get_L2_DATA_DRF_BISR_FAIL(data)                       ((0x000000FF&(data))>>0)


#define DRF_BISR_FAIL_TAG_SEP                                                        0x1801D438
#define DRF_BISR_FAIL_TAG_SEP_reg_addr                                               "0xB801D438"
#define DRF_BISR_FAIL_TAG_SEP_reg                                                    0xB801D438
#define set_DRF_BISR_FAIL_TAG_SEP_reg(data)   (*((volatile unsigned int*) DRF_BISR_FAIL_TAG_SEP_reg)=data)
#define get_DRF_BISR_FAIL_TAG_SEP_reg   (*((volatile unsigned int*) DRF_BISR_FAIL_TAG_SEP_reg))
#define DRF_BISR_FAIL_TAG_SEP_inst_adr                                               "0x000E"
#define DRF_BISR_FAIL_TAG_SEP_inst                                                   0x000E
#define DRF_BISR_FAIL_TAG_SEP_L2_TAG_DRF_BIST_FAIL_shift                             (0)
#define DRF_BISR_FAIL_TAG_SEP_L2_TAG_DRF_BIST_FAIL_mask                              (0x000000FF)
#define DRF_BISR_FAIL_TAG_SEP_L2_TAG_DRF_BIST_FAIL(data)                             (0x000000FF&((data)<<0))
#define DRF_BISR_FAIL_TAG_SEP_L2_TAG_DRF_BIST_FAIL_src(data)                         ((0x000000FF&(data))>>0)
#define DRF_BISR_FAIL_TAG_SEP_get_L2_TAG_DRF_BIST_FAIL(data)                         ((0x000000FF&(data))>>0)


#define L2_DATA_BISR_OUT_1                                                           0x1801D43C
#define L2_DATA_BISR_OUT_1_reg_addr                                                  "0xB801D43C"
#define L2_DATA_BISR_OUT_1_reg                                                       0xB801D43C
#define set_L2_DATA_BISR_OUT_1_reg(data)   (*((volatile unsigned int*) L2_DATA_BISR_OUT_1_reg)=data)
#define get_L2_DATA_BISR_OUT_1_reg   (*((volatile unsigned int*) L2_DATA_BISR_OUT_1_reg))
#define L2_DATA_BISR_OUT_1_inst_adr                                                  "0x000F"
#define L2_DATA_BISR_OUT_1_inst                                                      0x000F
#define L2_DATA_BISR_OUT_1_L2_DATA_BISR_OUT_31_0_shift                               (0)
#define L2_DATA_BISR_OUT_1_L2_DATA_BISR_OUT_31_0_mask                                (0xFFFFFFFF)
#define L2_DATA_BISR_OUT_1_L2_DATA_BISR_OUT_31_0(data)                               (0xFFFFFFFF&((data)<<0))
#define L2_DATA_BISR_OUT_1_L2_DATA_BISR_OUT_31_0_src(data)                           ((0xFFFFFFFF&(data))>>0)
#define L2_DATA_BISR_OUT_1_get_L2_DATA_BISR_OUT_31_0(data)                           ((0xFFFFFFFF&(data))>>0)


#define L2_DATA_BISR_OUT_2                                                           0x1801D440
#define L2_DATA_BISR_OUT_2_reg_addr                                                  "0xB801D440"
#define L2_DATA_BISR_OUT_2_reg                                                       0xB801D440
#define set_L2_DATA_BISR_OUT_2_reg(data)   (*((volatile unsigned int*) L2_DATA_BISR_OUT_2_reg)=data)
#define get_L2_DATA_BISR_OUT_2_reg   (*((volatile unsigned int*) L2_DATA_BISR_OUT_2_reg))
#define L2_DATA_BISR_OUT_2_inst_adr                                                  "0x0010"
#define L2_DATA_BISR_OUT_2_inst                                                      0x0010
#define L2_DATA_BISR_OUT_2_L2_DATA_BISR_OUT_55_32_shift                              (0)
#define L2_DATA_BISR_OUT_2_L2_DATA_BISR_OUT_55_32_mask                               (0x00FFFFFF)
#define L2_DATA_BISR_OUT_2_L2_DATA_BISR_OUT_55_32(data)                              (0x00FFFFFF&((data)<<0))
#define L2_DATA_BISR_OUT_2_L2_DATA_BISR_OUT_55_32_src(data)                          ((0x00FFFFFF&(data))>>0)
#define L2_DATA_BISR_OUT_2_get_L2_DATA_BISR_OUT_55_32(data)                          ((0x00FFFFFF&(data))>>0)


#define SRAM_RME                                                                     0x1801D480
#define SRAM_RME_reg_addr                                                            "0xB801D480"
#define SRAM_RME_reg                                                                 0xB801D480
#define set_SRAM_RME_reg(data)   (*((volatile unsigned int*) SRAM_RME_reg)=data)
#define get_SRAM_RME_reg   (*((volatile unsigned int*) SRAM_RME_reg))
#define SRAM_RME_inst_adr                                                            "0x0020"
#define SRAM_RME_inst                                                                0x0020
#define SRAM_RME_scu_ram_RME_shift                                                   (6)
#define SRAM_RME_scu_ram_RME_mask                                                    (0x00000040)
#define SRAM_RME_scu_ram_RME(data)                                                   (0x00000040&((data)<<6))
#define SRAM_RME_scu_ram_RME_src(data)                                               ((0x00000040&(data))>>6)
#define SRAM_RME_get_scu_ram_RME(data)                                               ((0x00000040&(data))>>6)
#define SRAM_RME_idata_ram_RME_shift                                                 (5)
#define SRAM_RME_idata_ram_RME_mask                                                  (0x00000020)
#define SRAM_RME_idata_ram_RME(data)                                                 (0x00000020&((data)<<5))
#define SRAM_RME_idata_ram_RME_src(data)                                             ((0x00000020&(data))>>5)
#define SRAM_RME_get_idata_ram_RME(data)                                             ((0x00000020&(data))>>5)
#define SRAM_RME_itag_ram_RME_shift                                                  (4)
#define SRAM_RME_itag_ram_RME_mask                                                   (0x00000010)
#define SRAM_RME_itag_ram_RME(data)                                                  (0x00000010&((data)<<4))
#define SRAM_RME_itag_ram_RME_src(data)                                              ((0x00000010&(data))>>4)
#define SRAM_RME_get_itag_ram_RME(data)                                              ((0x00000010&(data))>>4)
#define SRAM_RME_ddata_ram_RME_shift                                                 (3)
#define SRAM_RME_ddata_ram_RME_mask                                                  (0x00000008)
#define SRAM_RME_ddata_ram_RME(data)                                                 (0x00000008&((data)<<3))
#define SRAM_RME_ddata_ram_RME_src(data)                                             ((0x00000008&(data))>>3)
#define SRAM_RME_get_ddata_ram_RME(data)                                             ((0x00000008&(data))>>3)
#define SRAM_RME_dtag_ram_RME_shift                                                  (2)
#define SRAM_RME_dtag_ram_RME_mask                                                   (0x00000004)
#define SRAM_RME_dtag_ram_RME(data)                                                  (0x00000004&((data)<<2))
#define SRAM_RME_dtag_ram_RME_src(data)                                              ((0x00000004&(data))>>2)
#define SRAM_RME_get_dtag_ram_RME(data)                                              ((0x00000004&(data))>>2)
#define SRAM_RME_ddrity_ram_RME_shift                                                (1)
#define SRAM_RME_ddrity_ram_RME_mask                                                 (0x00000002)
#define SRAM_RME_ddrity_ram_RME(data)                                                (0x00000002&((data)<<1))
#define SRAM_RME_ddrity_ram_RME_src(data)                                            ((0x00000002&(data))>>1)
#define SRAM_RME_get_ddrity_ram_RME(data)                                            ((0x00000002&(data))>>1)
#define SRAM_RME_tlb_ram_RME_shift                                                   (0)
#define SRAM_RME_tlb_ram_RME_mask                                                    (0x00000001)
#define SRAM_RME_tlb_ram_RME(data)                                                   (0x00000001&((data)<<0))
#define SRAM_RME_tlb_ram_RME_src(data)                                               ((0x00000001&(data))>>0)
#define SRAM_RME_get_tlb_ram_RME(data)                                               ((0x00000001&(data))>>0)


#define SRAM_RM                                                                      0x1801D484
#define SRAM_RM_reg_addr                                                             "0xB801D484"
#define SRAM_RM_reg                                                                  0xB801D484
#define set_SRAM_RM_reg(data)   (*((volatile unsigned int*) SRAM_RM_reg)=data)
#define get_SRAM_RM_reg   (*((volatile unsigned int*) SRAM_RM_reg))
#define SRAM_RM_inst_adr                                                             "0x0021"
#define SRAM_RM_inst                                                                 0x0021
#define SRAM_RM_scu_ram_RM_shift                                                     (24)
#define SRAM_RM_scu_ram_RM_mask                                                      (0x0F000000)
#define SRAM_RM_scu_ram_RM(data)                                                     (0x0F000000&((data)<<24))
#define SRAM_RM_scu_ram_RM_src(data)                                                 ((0x0F000000&(data))>>24)
#define SRAM_RM_get_scu_ram_RM(data)                                                 ((0x0F000000&(data))>>24)
#define SRAM_RM_idata_ram_RM_shift                                                   (20)
#define SRAM_RM_idata_ram_RM_mask                                                    (0x00F00000)
#define SRAM_RM_idata_ram_RM(data)                                                   (0x00F00000&((data)<<20))
#define SRAM_RM_idata_ram_RM_src(data)                                               ((0x00F00000&(data))>>20)
#define SRAM_RM_get_idata_ram_RM(data)                                               ((0x00F00000&(data))>>20)
#define SRAM_RM_itag_ram_RM_shift                                                    (16)
#define SRAM_RM_itag_ram_RM_mask                                                     (0x000F0000)
#define SRAM_RM_itag_ram_RM(data)                                                    (0x000F0000&((data)<<16))
#define SRAM_RM_itag_ram_RM_src(data)                                                ((0x000F0000&(data))>>16)
#define SRAM_RM_get_itag_ram_RM(data)                                                ((0x000F0000&(data))>>16)
#define SRAM_RM_ddata_ram_RM_shift                                                   (12)
#define SRAM_RM_ddata_ram_RM_mask                                                    (0x0000F000)
#define SRAM_RM_ddata_ram_RM(data)                                                   (0x0000F000&((data)<<12))
#define SRAM_RM_ddata_ram_RM_src(data)                                               ((0x0000F000&(data))>>12)
#define SRAM_RM_get_ddata_ram_RM(data)                                               ((0x0000F000&(data))>>12)
#define SRAM_RM_dtag_ram_RM_shift                                                    (8)
#define SRAM_RM_dtag_ram_RM_mask                                                     (0x00000F00)
#define SRAM_RM_dtag_ram_RM(data)                                                    (0x00000F00&((data)<<8))
#define SRAM_RM_dtag_ram_RM_src(data)                                                ((0x00000F00&(data))>>8)
#define SRAM_RM_get_dtag_ram_RM(data)                                                ((0x00000F00&(data))>>8)
#define SRAM_RM_ddrity_ram_RM_shift                                                  (4)
#define SRAM_RM_ddrity_ram_RM_mask                                                   (0x000000F0)
#define SRAM_RM_ddrity_ram_RM(data)                                                  (0x000000F0&((data)<<4))
#define SRAM_RM_ddrity_ram_RM_src(data)                                              ((0x000000F0&(data))>>4)
#define SRAM_RM_get_ddrity_ram_RM(data)                                              ((0x000000F0&(data))>>4)
#define SRAM_RM_tlb_ram_RM_shift                                                     (0)
#define SRAM_RM_tlb_ram_RM_mask                                                      (0x0000000F)
#define SRAM_RM_tlb_ram_RM(data)                                                     (0x0000000F&((data)<<0))
#define SRAM_RM_tlb_ram_RM_src(data)                                                 ((0x0000000F&(data))>>0)
#define SRAM_RM_get_tlb_ram_RM(data)                                                 ((0x0000000F&(data))>>0)


#define L2_SRAM_RME                                                                  0x1801D48C
#define L2_SRAM_RME_reg_addr                                                         "0xB801D48C"
#define L2_SRAM_RME_reg                                                              0xB801D48C
#define set_L2_SRAM_RME_reg(data)   (*((volatile unsigned int*) L2_SRAM_RME_reg)=data)
#define get_L2_SRAM_RME_reg   (*((volatile unsigned int*) L2_SRAM_RME_reg))
#define L2_SRAM_RME_inst_adr                                                         "0x0023"
#define L2_SRAM_RME_inst                                                             0x0023
#define L2_SRAM_RME_RME_L2_TAG_shift                                                 (1)
#define L2_SRAM_RME_RME_L2_TAG_mask                                                  (0x00000002)
#define L2_SRAM_RME_RME_L2_TAG(data)                                                 (0x00000002&((data)<<1))
#define L2_SRAM_RME_RME_L2_TAG_src(data)                                             ((0x00000002&(data))>>1)
#define L2_SRAM_RME_get_RME_L2_TAG(data)                                             ((0x00000002&(data))>>1)
#define L2_SRAM_RME_RME_L2_DATA_shift                                                (0)
#define L2_SRAM_RME_RME_L2_DATA_mask                                                 (0x00000001)
#define L2_SRAM_RME_RME_L2_DATA(data)                                                (0x00000001&((data)<<0))
#define L2_SRAM_RME_RME_L2_DATA_src(data)                                            ((0x00000001&(data))>>0)
#define L2_SRAM_RME_get_RME_L2_DATA(data)                                            ((0x00000001&(data))>>0)


#define L2_SRAM_RM                                                                   0x1801D490
#define L2_SRAM_RM_reg_addr                                                          "0xB801D490"
#define L2_SRAM_RM_reg                                                               0xB801D490
#define set_L2_SRAM_RM_reg(data)   (*((volatile unsigned int*) L2_SRAM_RM_reg)=data)
#define get_L2_SRAM_RM_reg   (*((volatile unsigned int*) L2_SRAM_RM_reg))
#define L2_SRAM_RM_inst_adr                                                          "0x0024"
#define L2_SRAM_RM_inst                                                              0x0024
#define L2_SRAM_RM_RM_L2_TAG_shift                                                   (4)
#define L2_SRAM_RM_RM_L2_TAG_mask                                                    (0x000000F0)
#define L2_SRAM_RM_RM_L2_TAG(data)                                                   (0x000000F0&((data)<<4))
#define L2_SRAM_RM_RM_L2_TAG_src(data)                                               ((0x000000F0&(data))>>4)
#define L2_SRAM_RM_get_RM_L2_TAG(data)                                               ((0x000000F0&(data))>>4)
#define L2_SRAM_RM_RM_L2_DATA_shift                                                  (0)
#define L2_SRAM_RM_RM_L2_DATA_mask                                                   (0x0000000F)
#define L2_SRAM_RM_RM_L2_DATA(data)                                                  (0x0000000F&((data)<<0))
#define L2_SRAM_RM_RM_L2_DATA_src(data)                                              ((0x0000000F&(data))>>0)
#define L2_SRAM_RM_get_RM_L2_DATA(data)                                              ((0x0000000F&(data))>>0)


#endif
