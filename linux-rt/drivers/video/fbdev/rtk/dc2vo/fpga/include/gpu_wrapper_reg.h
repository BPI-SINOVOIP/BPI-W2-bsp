/**************************************************************
// Spec Version                  : unknown
// Parser Version                : DVR_Parser_6.5
// CModelGen Version             : 5.0 2009.04.09
// Naming Rule                   :  Register_Name
// Naming Rule                   : Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/6/27 14:1:58
***************************************************************/


#ifndef _GPU_WRAPPER_REG_H_INCLUDED_
#define _GPU_WRAPPER_REG_H_INCLUDED_
#ifdef  _GPU_WRAPPER_USE_STRUCT
typedef struct 
{
unsigned int     wcmd_kn:5;
unsigned int     rcmd_kn:5;
unsigned int     outstd_wcmd:5;
unsigned int     outstd_rcmd:5;
unsigned int     grp_lmt:5;
unsigned int     grp_size:3;
unsigned int     cmd_reorder_en:1;
unsigned int     burst_lmt:1;
unsigned int     grp_wen:1;
unsigned int     grp_ren:1;
}GPU_WRAPPER;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     chk_rdfifo_mod:1;
unsigned int     rcmd_chk_rdfifo_num:2;
unsigned int     rcmd_chk_rdfifo:1;
unsigned int     wcmd_wait_wd:1;
}CHK_RDFIFO;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     BIST_MODE13:1;
unsigned int     BIST_MODE12:1;
unsigned int     BIST_MODE11:1;
unsigned int     BIST_MODE10:1;
unsigned int     BIST_MODE9:1;
unsigned int     BIST_MODE8:1;
unsigned int     BIST_MODE7:1;
unsigned int     BIST_MODE6:1;
unsigned int     BIST_MODE5:1;
unsigned int     BIST_MODE4:1;
unsigned int     BIST_MODE3:1;
unsigned int     BIST_MODE2:1;
unsigned int     BIST_MODE1:1;
}BIST_MODE;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     DRF_TEST_RESUME13:1;
unsigned int     DRF_TEST_RESUME12:1;
unsigned int     DRF_TEST_RESUME11:1;
unsigned int     DRF_TEST_RESUME10:1;
unsigned int     DRF_TEST_RESUME9:1;
unsigned int     DRF_TEST_RESUME8:1;
unsigned int     DRF_TEST_RESUME7:1;
unsigned int     DRF_TEST_RESUME6:1;
unsigned int     DRF_TEST_RESUME5:1;
unsigned int     DRF_TEST_RESUME4:1;
unsigned int     DRF_TEST_RESUME3:1;
unsigned int     DRF_TEST_RESUME2:1;
unsigned int     DRF_TEST_RESUME1:1;
unsigned int     DRF_BIST_MODE13:1;
unsigned int     DRF_BIST_MODE12:1;
unsigned int     DRF_BIST_MODE11:1;
unsigned int     DRF_BIST_MODE10:1;
unsigned int     DRF_BIST_MODE9:1;
unsigned int     DRF_BIST_MODE8:1;
unsigned int     DRF_BIST_MODE7:1;
unsigned int     DRF_BIST_MODE6:1;
unsigned int     DRF_BIST_MODE5:1;
unsigned int     DRF_BIST_MODE4:1;
unsigned int     DRF_BIST_MODE3:1;
unsigned int     DRF_BIST_MODE2:1;
unsigned int     DRF_BIST_MODE1:1;
}DRF_BIST_MODE;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     DRF_START_PAUSE1:1;
unsigned int     DRF_BIST_FAIL1_9:1;
unsigned int     DRF_BIST_FAIL1_8:1;
unsigned int     DRF_BIST_FAIL1_7:1;
unsigned int     DRF_BIST_FAIL1_6:1;
unsigned int     DRF_BIST_FAIL1_5:1;
unsigned int     DRF_BIST_FAIL1_4:1;
unsigned int     DRF_BIST_FAIL1_3:1;
unsigned int     DRF_BIST_FAIL1_2:1;
unsigned int     DRF_BIST_FAIL1_1:1;
unsigned int     DRF_BIST_FAIL1_0:1;
unsigned int     DRF_BIST_DONE1:1;
unsigned int     BIST_FAIL1_9:1;
unsigned int     BIST_FAIL1_8:1;
unsigned int     BIST_FAIL1_7:1;
unsigned int     BIST_FAIL1_6:1;
unsigned int     BIST_FAIL1_5:1;
unsigned int     BIST_FAIL1_4:1;
unsigned int     BIST_FAIL1_3:1;
unsigned int     BIST_FAIL1_2:1;
unsigned int     BIST_FAIL1_1:1;
unsigned int     BIST_FAIL1_0:1;
unsigned int     BIST_DONE1:1;
}BIST_RESULT1;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     DRF_START_PAUSE2:1;
unsigned int     DRF_BIST_FAIL2_9:1;
unsigned int     DRF_BIST_FAIL2_8:1;
unsigned int     DRF_BIST_FAIL2_7:1;
unsigned int     DRF_BIST_FAIL2_6:1;
unsigned int     DRF_BIST_FAIL2_5:1;
unsigned int     DRF_BIST_FAIL2_4:1;
unsigned int     DRF_BIST_FAIL2_3:1;
unsigned int     DRF_BIST_FAIL2_2:1;
unsigned int     DRF_BIST_FAIL2_1:1;
unsigned int     DRF_BIST_FAIL2_0:1;
unsigned int     DRF_BIST_DONE2:1;
unsigned int     BIST_FAIL2_9:1;
unsigned int     BIST_FAIL2_8:1;
unsigned int     BIST_FAIL2_7:1;
unsigned int     BIST_FAIL2_6:1;
unsigned int     BIST_FAIL2_5:1;
unsigned int     BIST_FAIL2_4:1;
unsigned int     BIST_FAIL2_3:1;
unsigned int     BIST_FAIL2_2:1;
unsigned int     BIST_FAIL2_1:1;
unsigned int     BIST_FAIL2_0:1;
unsigned int     BIST_DONE2:1;
}BIST_RESULT2;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     DRF_START_PAUSE3:1;
unsigned int     DRF_BIST_FAIL3_6:1;
unsigned int     DRF_BIST_FAIL3_5:1;
unsigned int     DRF_BIST_FAIL3_4:1;
unsigned int     DRF_BIST_FAIL3_3:1;
unsigned int     DRF_BIST_FAIL3_2:1;
unsigned int     DRF_BIST_FAIL3_1:1;
unsigned int     DRF_BIST_FAIL3_0:1;
unsigned int     DRF_BIST_DONE3:1;
unsigned int     BIST_FAIL3_6:1;
unsigned int     BIST_FAIL3_5:1;
unsigned int     BIST_FAIL3_4:1;
unsigned int     BIST_FAIL3_3:1;
unsigned int     BIST_FAIL3_2:1;
unsigned int     BIST_FAIL3_1:1;
unsigned int     BIST_FAIL3_0:1;
unsigned int     BIST_DONE3:1;
}BIST_RESULT3;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     DRF_START_PAUSE4:1;
unsigned int     DRF_BIST_FAIL4_6:1;
unsigned int     DRF_BIST_FAIL4_5:1;
unsigned int     DRF_BIST_FAIL4_4:1;
unsigned int     DRF_BIST_FAIL4_3:1;
unsigned int     DRF_BIST_FAIL4_2:1;
unsigned int     DRF_BIST_FAIL4_1:1;
unsigned int     DRF_BIST_FAIL4_0:1;
unsigned int     DRF_BIST_DONE4:1;
unsigned int     BIST_FAIL4_6:1;
unsigned int     BIST_FAIL4_5:1;
unsigned int     BIST_FAIL4_4:1;
unsigned int     BIST_FAIL4_3:1;
unsigned int     BIST_FAIL4_2:1;
unsigned int     BIST_FAIL4_1:1;
unsigned int     BIST_FAIL4_0:1;
unsigned int     BIST_DONE4:1;
}BIST_RESULT4;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     DRF_START_PAUSE5:1;
unsigned int     DRF_BIST_FAIL5_9:1;
unsigned int     DRF_BIST_FAIL5_8:1;
unsigned int     DRF_BIST_FAIL5_7:1;
unsigned int     DRF_BIST_FAIL5_6:1;
unsigned int     DRF_BIST_FAIL5_5:1;
unsigned int     DRF_BIST_FAIL5_4:1;
unsigned int     DRF_BIST_FAIL5_3:1;
unsigned int     DRF_BIST_FAIL5_2:1;
unsigned int     DRF_BIST_FAIL5_1:1;
unsigned int     DRF_BIST_FAIL5_0:1;
unsigned int     DRF_BIST_DONE5:1;
unsigned int     BIST_FAIL5_9:1;
unsigned int     BIST_FAIL5_8:1;
unsigned int     BIST_FAIL5_7:1;
unsigned int     BIST_FAIL5_6:1;
unsigned int     BIST_FAIL5_5:1;
unsigned int     BIST_FAIL5_4:1;
unsigned int     BIST_FAIL5_3:1;
unsigned int     BIST_FAIL5_2:1;
unsigned int     BIST_FAIL5_1:1;
unsigned int     BIST_FAIL5_0:1;
unsigned int     BIST_DONE5:1;
}BIST_RESULT5;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     DRF_START_PAUSE6:1;
unsigned int     DRF_BIST_FAIL6_9:1;
unsigned int     DRF_BIST_FAIL6_8:1;
unsigned int     DRF_BIST_FAIL6_7:1;
unsigned int     DRF_BIST_FAIL6_6:1;
unsigned int     DRF_BIST_FAIL6_5:1;
unsigned int     DRF_BIST_FAIL6_4:1;
unsigned int     DRF_BIST_FAIL6_3:1;
unsigned int     DRF_BIST_FAIL6_2:1;
unsigned int     DRF_BIST_FAIL6_1:1;
unsigned int     DRF_BIST_FAIL6_0:1;
unsigned int     DRF_BIST_DONE6:1;
unsigned int     BIST_FAIL6_9:1;
unsigned int     BIST_FAIL6_8:1;
unsigned int     BIST_FAIL6_7:1;
unsigned int     BIST_FAIL6_6:1;
unsigned int     BIST_FAIL6_5:1;
unsigned int     BIST_FAIL6_4:1;
unsigned int     BIST_FAIL6_3:1;
unsigned int     BIST_FAIL6_2:1;
unsigned int     BIST_FAIL6_1:1;
unsigned int     BIST_FAIL6_0:1;
unsigned int     BIST_DONE6:1;
}BIST_RESULT6;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     DRF_START_PAUSE7:1;
unsigned int     DRF_BIST_FAIL7_6:1;
unsigned int     DRF_BIST_FAIL7_5:1;
unsigned int     DRF_BIST_FAIL7_4:1;
unsigned int     DRF_BIST_FAIL7_3:1;
unsigned int     DRF_BIST_FAIL7_2:1;
unsigned int     DRF_BIST_FAIL7_1:1;
unsigned int     DRF_BIST_FAIL7_0:1;
unsigned int     DRF_BIST_DONE7:1;
unsigned int     BIST_FAIL7_6:1;
unsigned int     BIST_FAIL7_5:1;
unsigned int     BIST_FAIL7_4:1;
unsigned int     BIST_FAIL7_3:1;
unsigned int     BIST_FAIL7_2:1;
unsigned int     BIST_FAIL7_1:1;
unsigned int     BIST_FAIL7_0:1;
unsigned int     BIST_DONE7:1;
}BIST_RESULT7;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     DRF_START_PAUSE8:1;
unsigned int     DRF_BIST_FAIL8_6:1;
unsigned int     DRF_BIST_FAIL8_5:1;
unsigned int     DRF_BIST_FAIL8_4:1;
unsigned int     DRF_BIST_FAIL8_3:1;
unsigned int     DRF_BIST_FAIL8_2:1;
unsigned int     DRF_BIST_FAIL8_1:1;
unsigned int     DRF_BIST_FAIL8_0:1;
unsigned int     DRF_BIST_DONE8:1;
unsigned int     BIST_FAIL8_6:1;
unsigned int     BIST_FAIL8_5:1;
unsigned int     BIST_FAIL8_4:1;
unsigned int     BIST_FAIL8_3:1;
unsigned int     BIST_FAIL8_2:1;
unsigned int     BIST_FAIL8_1:1;
unsigned int     BIST_FAIL8_0:1;
unsigned int     BIST_DONE8:1;
}BIST_RESULT8;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     DRF_START_PAUSE9:1;
unsigned int     DRF_BIST_FAIL9_6:1;
unsigned int     DRF_BIST_FAIL9_5:1;
unsigned int     DRF_BIST_FAIL9_4:1;
unsigned int     DRF_BIST_FAIL9_3:1;
unsigned int     DRF_BIST_FAIL9_2:1;
unsigned int     DRF_BIST_FAIL9_1:1;
unsigned int     DRF_BIST_FAIL9_0:1;
unsigned int     DRF_BIST_DONE9:1;
unsigned int     BIST_FAIL9_6:1;
unsigned int     BIST_FAIL9_5:1;
unsigned int     BIST_FAIL9_4:1;
unsigned int     BIST_FAIL9_3:1;
unsigned int     BIST_FAIL9_2:1;
unsigned int     BIST_FAIL9_1:1;
unsigned int     BIST_FAIL9_0:1;
unsigned int     BIST_DONE9:1;
}BIST_RESULT9;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     DRF_START_PAUSE10:1;
unsigned int     DRF_BIST_FAIL10_7:1;
unsigned int     DRF_BIST_FAIL10_6:1;
unsigned int     DRF_BIST_FAIL10_5:1;
unsigned int     DRF_BIST_FAIL10_4:1;
unsigned int     DRF_BIST_FAIL10_3:1;
unsigned int     DRF_BIST_FAIL10_2:1;
unsigned int     DRF_BIST_FAIL10_1:1;
unsigned int     DRF_BIST_FAIL10_0:1;
unsigned int     DRF_BIST_DONE10:1;
unsigned int     BIST_FAIL10_7:1;
unsigned int     BIST_FAIL10_6:1;
unsigned int     BIST_FAIL10_5:1;
unsigned int     BIST_FAIL10_4:1;
unsigned int     BIST_FAIL10_3:1;
unsigned int     BIST_FAIL10_2:1;
unsigned int     BIST_FAIL10_1:1;
unsigned int     BIST_FAIL10_0:1;
unsigned int     BIST_DONE10:1;
}BIST_RESULT10;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     DRF_START_PAUSE11:1;
unsigned int     DRF_BIST_FAIL11_3:1;
unsigned int     DRF_BIST_FAIL11_2:1;
unsigned int     DRF_BIST_FAIL11_1:1;
unsigned int     DRF_BIST_FAIL11_0:1;
unsigned int     DRF_BIST_DONE11:1;
unsigned int     BIST_FAIL11_3:1;
unsigned int     BIST_FAIL11_2:1;
unsigned int     BIST_FAIL11_1:1;
unsigned int     BIST_FAIL11_0:1;
unsigned int     BIST_DONE11:1;
}BIST_RESULT11;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     DRF_START_PAUSE12:1;
unsigned int     DRF_BIST_FAIL12_1:1;
unsigned int     DRF_BIST_FAIL12_0:1;
unsigned int     DRF_BIST_DONE12:1;
unsigned int     BIST_FAIL12_1:1;
unsigned int     BIST_FAIL12_0:1;
unsigned int     BIST_DONE12:1;
}BIST_RESULT12;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     DRF_START_PAUSE13:1;
unsigned int     DRF_BIST_FAIL13_0:1;
unsigned int     DRF_BIST_DONE13:1;
unsigned int     BIST_FAIL13_0:1;
unsigned int     BIST_DONE13:1;
}BIST_RESULT13;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     sram_rm:4;
unsigned int     sram_rme:1;
}BIST_RESULT13;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     dbg_sel:1;
unsigned int     dbg_sel1:4;
unsigned int     dbg_sel0:4;
}DEBUGPORTS;

typedef struct 
{
unsigned int     dummy_reg0:32;
}DUMMYREGISTERS0;

typedef struct 
{
unsigned int     dummy_reg1:32;
}DUMMYREGISTERS1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     c35_data_in:20;
unsigned int     reserved_1:2;
unsigned int     c35_speed_en:1;
unsigned int     c35_wire_sel:1;
unsigned int     c35_ro_sel:3;
unsigned int     c35_dss_rst_n:1;
}DSS_C35_9D5T_CTRL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     c35_count_out:20;
unsigned int     reserved_1:2;
unsigned int     c35_wsort_go:1;
unsigned int     c35_ready:1;
}DSS_C35_9D5T_STATUS;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     c35_dbgo:16;
}DSS_C35_9D5T_DEBUG;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     c35d5_data_in:20;
unsigned int     reserved_1:2;
unsigned int     c35d5_speed_en:1;
unsigned int     c35d5_wire_sel:1;
unsigned int     c35d5_ro_sel:3;
unsigned int     c35d5_dss_rst_n:1;
}DSS_C35D5_9D5T_CTRL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     c35d5_count_out:20;
unsigned int     reserved_1:2;
unsigned int     c35d5_wsort_go:1;
unsigned int     c35d5_ready:1;
}DSS_C35D5_9D5T_STATUS;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     c35d5_dbgo:16;
}DSS_C35D5_9D5T_DEBUG;

#endif

#define GPU_WRAPPER                                                                  0x18036000
#define GPU_WRAPPER_reg_addr                                                         "0xB8036000"
#define GPU_WRAPPER_reg                                                              0xB8036000
#define set_GPU_WRAPPER_reg(data)   (*((volatile unsigned int*) GPU_WRAPPER_reg)=data)
#define get_GPU_WRAPPER_reg   (*((volatile unsigned int*) GPU_WRAPPER_reg))
#define GPU_WRAPPER_inst_adr                                                         "0x0000"
#define GPU_WRAPPER_inst                                                             0x0000
#define GPU_WRAPPER_wcmd_kn_shift                                                    (27)
#define GPU_WRAPPER_wcmd_kn_mask                                                     (0xF8000000)
#define GPU_WRAPPER_wcmd_kn(data)                                                    (0xF8000000&((data)<<27))
#define GPU_WRAPPER_wcmd_kn_src(data)                                                ((0xF8000000&(data))>>27)
#define GPU_WRAPPER_get_wcmd_kn(data)                                                ((0xF8000000&(data))>>27)
#define GPU_WRAPPER_rcmd_kn_shift                                                    (22)
#define GPU_WRAPPER_rcmd_kn_mask                                                     (0x07C00000)
#define GPU_WRAPPER_rcmd_kn(data)                                                    (0x07C00000&((data)<<22))
#define GPU_WRAPPER_rcmd_kn_src(data)                                                ((0x07C00000&(data))>>22)
#define GPU_WRAPPER_get_rcmd_kn(data)                                                ((0x07C00000&(data))>>22)
#define GPU_WRAPPER_outstd_wcmd_shift                                                (17)
#define GPU_WRAPPER_outstd_wcmd_mask                                                 (0x003E0000)
#define GPU_WRAPPER_outstd_wcmd(data)                                                (0x003E0000&((data)<<17))
#define GPU_WRAPPER_outstd_wcmd_src(data)                                            ((0x003E0000&(data))>>17)
#define GPU_WRAPPER_get_outstd_wcmd(data)                                            ((0x003E0000&(data))>>17)
#define GPU_WRAPPER_outstd_rcmd_shift                                                (12)
#define GPU_WRAPPER_outstd_rcmd_mask                                                 (0x0001F000)
#define GPU_WRAPPER_outstd_rcmd(data)                                                (0x0001F000&((data)<<12))
#define GPU_WRAPPER_outstd_rcmd_src(data)                                            ((0x0001F000&(data))>>12)
#define GPU_WRAPPER_get_outstd_rcmd(data)                                            ((0x0001F000&(data))>>12)
#define GPU_WRAPPER_grp_lmt_shift                                                    (7)
#define GPU_WRAPPER_grp_lmt_mask                                                     (0x00000F80)
#define GPU_WRAPPER_grp_lmt(data)                                                    (0x00000F80&((data)<<7))
#define GPU_WRAPPER_grp_lmt_src(data)                                                ((0x00000F80&(data))>>7)
#define GPU_WRAPPER_get_grp_lmt(data)                                                ((0x00000F80&(data))>>7)
#define GPU_WRAPPER_grp_size_shift                                                   (4)
#define GPU_WRAPPER_grp_size_mask                                                    (0x00000070)
#define GPU_WRAPPER_grp_size(data)                                                   (0x00000070&((data)<<4))
#define GPU_WRAPPER_grp_size_src(data)                                               ((0x00000070&(data))>>4)
#define GPU_WRAPPER_get_grp_size(data)                                               ((0x00000070&(data))>>4)
#define GPU_WRAPPER_cmd_reorder_en_shift                                             (3)
#define GPU_WRAPPER_cmd_reorder_en_mask                                              (0x00000008)
#define GPU_WRAPPER_cmd_reorder_en(data)                                             (0x00000008&((data)<<3))
#define GPU_WRAPPER_cmd_reorder_en_src(data)                                         ((0x00000008&(data))>>3)
#define GPU_WRAPPER_get_cmd_reorder_en(data)                                         ((0x00000008&(data))>>3)
#define GPU_WRAPPER_burst_lmt_shift                                                  (2)
#define GPU_WRAPPER_burst_lmt_mask                                                   (0x00000004)
#define GPU_WRAPPER_burst_lmt(data)                                                  (0x00000004&((data)<<2))
#define GPU_WRAPPER_burst_lmt_src(data)                                              ((0x00000004&(data))>>2)
#define GPU_WRAPPER_get_burst_lmt(data)                                              ((0x00000004&(data))>>2)
#define GPU_WRAPPER_grp_wen_shift                                                    (1)
#define GPU_WRAPPER_grp_wen_mask                                                     (0x00000002)
#define GPU_WRAPPER_grp_wen(data)                                                    (0x00000002&((data)<<1))
#define GPU_WRAPPER_grp_wen_src(data)                                                ((0x00000002&(data))>>1)
#define GPU_WRAPPER_get_grp_wen(data)                                                ((0x00000002&(data))>>1)
#define GPU_WRAPPER_grp_ren_shift                                                    (0)
#define GPU_WRAPPER_grp_ren_mask                                                     (0x00000001)
#define GPU_WRAPPER_grp_ren(data)                                                    (0x00000001&((data)<<0))
#define GPU_WRAPPER_grp_ren_src(data)                                                ((0x00000001&(data))>>0)
#define GPU_WRAPPER_get_grp_ren(data)                                                ((0x00000001&(data))>>0)


#define CHK_RDFIFO                                                                   0x18036004
#define CHK_RDFIFO_reg_addr                                                          "0xB8036004"
#define CHK_RDFIFO_reg                                                               0xB8036004
#define set_CHK_RDFIFO_reg(data)   (*((volatile unsigned int*) CHK_RDFIFO_reg)=data)
#define get_CHK_RDFIFO_reg   (*((volatile unsigned int*) CHK_RDFIFO_reg))
#define CHK_RDFIFO_inst_adr                                                          "0x0001"
#define CHK_RDFIFO_inst                                                              0x0001
#define CHK_RDFIFO_chk_rdfifo_mod_shift                                              (4)
#define CHK_RDFIFO_chk_rdfifo_mod_mask                                               (0x00000010)
#define CHK_RDFIFO_chk_rdfifo_mod(data)                                              (0x00000010&((data)<<4))
#define CHK_RDFIFO_chk_rdfifo_mod_src(data)                                          ((0x00000010&(data))>>4)
#define CHK_RDFIFO_get_chk_rdfifo_mod(data)                                          ((0x00000010&(data))>>4)
#define CHK_RDFIFO_rcmd_chk_rdfifo_num_shift                                         (2)
#define CHK_RDFIFO_rcmd_chk_rdfifo_num_mask                                          (0x0000000C)
#define CHK_RDFIFO_rcmd_chk_rdfifo_num(data)                                         (0x0000000C&((data)<<2))
#define CHK_RDFIFO_rcmd_chk_rdfifo_num_src(data)                                     ((0x0000000C&(data))>>2)
#define CHK_RDFIFO_get_rcmd_chk_rdfifo_num(data)                                     ((0x0000000C&(data))>>2)
#define CHK_RDFIFO_rcmd_chk_rdfifo_shift                                             (1)
#define CHK_RDFIFO_rcmd_chk_rdfifo_mask                                              (0x00000002)
#define CHK_RDFIFO_rcmd_chk_rdfifo(data)                                             (0x00000002&((data)<<1))
#define CHK_RDFIFO_rcmd_chk_rdfifo_src(data)                                         ((0x00000002&(data))>>1)
#define CHK_RDFIFO_get_rcmd_chk_rdfifo(data)                                         ((0x00000002&(data))>>1)
#define CHK_RDFIFO_wcmd_wait_wd_shift                                                (0)
#define CHK_RDFIFO_wcmd_wait_wd_mask                                                 (0x00000001)
#define CHK_RDFIFO_wcmd_wait_wd(data)                                                (0x00000001&((data)<<0))
#define CHK_RDFIFO_wcmd_wait_wd_src(data)                                            ((0x00000001&(data))>>0)
#define CHK_RDFIFO_get_wcmd_wait_wd(data)                                            ((0x00000001&(data))>>0)


#define BIST_MODE                                                                    0x18036008
#define BIST_MODE_reg_addr                                                           "0xB8036008"
#define BIST_MODE_reg                                                                0xB8036008
#define set_BIST_MODE_reg(data)   (*((volatile unsigned int*) BIST_MODE_reg)=data)
#define get_BIST_MODE_reg   (*((volatile unsigned int*) BIST_MODE_reg))
#define BIST_MODE_inst_adr                                                           "0x0002"
#define BIST_MODE_inst                                                               0x0002
#define BIST_MODE_BIST_MODE13_shift                                                  (12)
#define BIST_MODE_BIST_MODE13_mask                                                   (0x00001000)
#define BIST_MODE_BIST_MODE13(data)                                                  (0x00001000&((data)<<12))
#define BIST_MODE_BIST_MODE13_src(data)                                              ((0x00001000&(data))>>12)
#define BIST_MODE_get_BIST_MODE13(data)                                              ((0x00001000&(data))>>12)
#define BIST_MODE_BIST_MODE12_shift                                                  (11)
#define BIST_MODE_BIST_MODE12_mask                                                   (0x00000800)
#define BIST_MODE_BIST_MODE12(data)                                                  (0x00000800&((data)<<11))
#define BIST_MODE_BIST_MODE12_src(data)                                              ((0x00000800&(data))>>11)
#define BIST_MODE_get_BIST_MODE12(data)                                              ((0x00000800&(data))>>11)
#define BIST_MODE_BIST_MODE11_shift                                                  (10)
#define BIST_MODE_BIST_MODE11_mask                                                   (0x00000400)
#define BIST_MODE_BIST_MODE11(data)                                                  (0x00000400&((data)<<10))
#define BIST_MODE_BIST_MODE11_src(data)                                              ((0x00000400&(data))>>10)
#define BIST_MODE_get_BIST_MODE11(data)                                              ((0x00000400&(data))>>10)
#define BIST_MODE_BIST_MODE10_shift                                                  (9)
#define BIST_MODE_BIST_MODE10_mask                                                   (0x00000200)
#define BIST_MODE_BIST_MODE10(data)                                                  (0x00000200&((data)<<9))
#define BIST_MODE_BIST_MODE10_src(data)                                              ((0x00000200&(data))>>9)
#define BIST_MODE_get_BIST_MODE10(data)                                              ((0x00000200&(data))>>9)
#define BIST_MODE_BIST_MODE9_shift                                                   (8)
#define BIST_MODE_BIST_MODE9_mask                                                    (0x00000100)
#define BIST_MODE_BIST_MODE9(data)                                                   (0x00000100&((data)<<8))
#define BIST_MODE_BIST_MODE9_src(data)                                               ((0x00000100&(data))>>8)
#define BIST_MODE_get_BIST_MODE9(data)                                               ((0x00000100&(data))>>8)
#define BIST_MODE_BIST_MODE8_shift                                                   (7)
#define BIST_MODE_BIST_MODE8_mask                                                    (0x00000080)
#define BIST_MODE_BIST_MODE8(data)                                                   (0x00000080&((data)<<7))
#define BIST_MODE_BIST_MODE8_src(data)                                               ((0x00000080&(data))>>7)
#define BIST_MODE_get_BIST_MODE8(data)                                               ((0x00000080&(data))>>7)
#define BIST_MODE_BIST_MODE7_shift                                                   (6)
#define BIST_MODE_BIST_MODE7_mask                                                    (0x00000040)
#define BIST_MODE_BIST_MODE7(data)                                                   (0x00000040&((data)<<6))
#define BIST_MODE_BIST_MODE7_src(data)                                               ((0x00000040&(data))>>6)
#define BIST_MODE_get_BIST_MODE7(data)                                               ((0x00000040&(data))>>6)
#define BIST_MODE_BIST_MODE6_shift                                                   (5)
#define BIST_MODE_BIST_MODE6_mask                                                    (0x00000020)
#define BIST_MODE_BIST_MODE6(data)                                                   (0x00000020&((data)<<5))
#define BIST_MODE_BIST_MODE6_src(data)                                               ((0x00000020&(data))>>5)
#define BIST_MODE_get_BIST_MODE6(data)                                               ((0x00000020&(data))>>5)
#define BIST_MODE_BIST_MODE5_shift                                                   (4)
#define BIST_MODE_BIST_MODE5_mask                                                    (0x00000010)
#define BIST_MODE_BIST_MODE5(data)                                                   (0x00000010&((data)<<4))
#define BIST_MODE_BIST_MODE5_src(data)                                               ((0x00000010&(data))>>4)
#define BIST_MODE_get_BIST_MODE5(data)                                               ((0x00000010&(data))>>4)
#define BIST_MODE_BIST_MODE4_shift                                                   (3)
#define BIST_MODE_BIST_MODE4_mask                                                    (0x00000008)
#define BIST_MODE_BIST_MODE4(data)                                                   (0x00000008&((data)<<3))
#define BIST_MODE_BIST_MODE4_src(data)                                               ((0x00000008&(data))>>3)
#define BIST_MODE_get_BIST_MODE4(data)                                               ((0x00000008&(data))>>3)
#define BIST_MODE_BIST_MODE3_shift                                                   (2)
#define BIST_MODE_BIST_MODE3_mask                                                    (0x00000004)
#define BIST_MODE_BIST_MODE3(data)                                                   (0x00000004&((data)<<2))
#define BIST_MODE_BIST_MODE3_src(data)                                               ((0x00000004&(data))>>2)
#define BIST_MODE_get_BIST_MODE3(data)                                               ((0x00000004&(data))>>2)
#define BIST_MODE_BIST_MODE2_shift                                                   (1)
#define BIST_MODE_BIST_MODE2_mask                                                    (0x00000002)
#define BIST_MODE_BIST_MODE2(data)                                                   (0x00000002&((data)<<1))
#define BIST_MODE_BIST_MODE2_src(data)                                               ((0x00000002&(data))>>1)
#define BIST_MODE_get_BIST_MODE2(data)                                               ((0x00000002&(data))>>1)
#define BIST_MODE_BIST_MODE1_shift                                                   (0)
#define BIST_MODE_BIST_MODE1_mask                                                    (0x00000001)
#define BIST_MODE_BIST_MODE1(data)                                                   (0x00000001&((data)<<0))
#define BIST_MODE_BIST_MODE1_src(data)                                               ((0x00000001&(data))>>0)
#define BIST_MODE_get_BIST_MODE1(data)                                               ((0x00000001&(data))>>0)


#define DRF_BIST_MODE                                                                0x1803600C
#define DRF_BIST_MODE_reg_addr                                                       "0xB803600C"
#define DRF_BIST_MODE_reg                                                            0xB803600C
#define set_DRF_BIST_MODE_reg(data)   (*((volatile unsigned int*) DRF_BIST_MODE_reg)=data)
#define get_DRF_BIST_MODE_reg   (*((volatile unsigned int*) DRF_BIST_MODE_reg))
#define DRF_BIST_MODE_inst_adr                                                       "0x0003"
#define DRF_BIST_MODE_inst                                                           0x0003
#define DRF_BIST_MODE_DRF_TEST_RESUME13_shift                                        (25)
#define DRF_BIST_MODE_DRF_TEST_RESUME13_mask                                         (0x02000000)
#define DRF_BIST_MODE_DRF_TEST_RESUME13(data)                                        (0x02000000&((data)<<25))
#define DRF_BIST_MODE_DRF_TEST_RESUME13_src(data)                                    ((0x02000000&(data))>>25)
#define DRF_BIST_MODE_get_DRF_TEST_RESUME13(data)                                    ((0x02000000&(data))>>25)
#define DRF_BIST_MODE_DRF_TEST_RESUME12_shift                                        (24)
#define DRF_BIST_MODE_DRF_TEST_RESUME12_mask                                         (0x01000000)
#define DRF_BIST_MODE_DRF_TEST_RESUME12(data)                                        (0x01000000&((data)<<24))
#define DRF_BIST_MODE_DRF_TEST_RESUME12_src(data)                                    ((0x01000000&(data))>>24)
#define DRF_BIST_MODE_get_DRF_TEST_RESUME12(data)                                    ((0x01000000&(data))>>24)
#define DRF_BIST_MODE_DRF_TEST_RESUME11_shift                                        (23)
#define DRF_BIST_MODE_DRF_TEST_RESUME11_mask                                         (0x00800000)
#define DRF_BIST_MODE_DRF_TEST_RESUME11(data)                                        (0x00800000&((data)<<23))
#define DRF_BIST_MODE_DRF_TEST_RESUME11_src(data)                                    ((0x00800000&(data))>>23)
#define DRF_BIST_MODE_get_DRF_TEST_RESUME11(data)                                    ((0x00800000&(data))>>23)
#define DRF_BIST_MODE_DRF_TEST_RESUME10_shift                                        (22)
#define DRF_BIST_MODE_DRF_TEST_RESUME10_mask                                         (0x00400000)
#define DRF_BIST_MODE_DRF_TEST_RESUME10(data)                                        (0x00400000&((data)<<22))
#define DRF_BIST_MODE_DRF_TEST_RESUME10_src(data)                                    ((0x00400000&(data))>>22)
#define DRF_BIST_MODE_get_DRF_TEST_RESUME10(data)                                    ((0x00400000&(data))>>22)
#define DRF_BIST_MODE_DRF_TEST_RESUME9_shift                                         (21)
#define DRF_BIST_MODE_DRF_TEST_RESUME9_mask                                          (0x00200000)
#define DRF_BIST_MODE_DRF_TEST_RESUME9(data)                                         (0x00200000&((data)<<21))
#define DRF_BIST_MODE_DRF_TEST_RESUME9_src(data)                                     ((0x00200000&(data))>>21)
#define DRF_BIST_MODE_get_DRF_TEST_RESUME9(data)                                     ((0x00200000&(data))>>21)
#define DRF_BIST_MODE_DRF_TEST_RESUME8_shift                                         (20)
#define DRF_BIST_MODE_DRF_TEST_RESUME8_mask                                          (0x00100000)
#define DRF_BIST_MODE_DRF_TEST_RESUME8(data)                                         (0x00100000&((data)<<20))
#define DRF_BIST_MODE_DRF_TEST_RESUME8_src(data)                                     ((0x00100000&(data))>>20)
#define DRF_BIST_MODE_get_DRF_TEST_RESUME8(data)                                     ((0x00100000&(data))>>20)
#define DRF_BIST_MODE_DRF_TEST_RESUME7_shift                                         (19)
#define DRF_BIST_MODE_DRF_TEST_RESUME7_mask                                          (0x00080000)
#define DRF_BIST_MODE_DRF_TEST_RESUME7(data)                                         (0x00080000&((data)<<19))
#define DRF_BIST_MODE_DRF_TEST_RESUME7_src(data)                                     ((0x00080000&(data))>>19)
#define DRF_BIST_MODE_get_DRF_TEST_RESUME7(data)                                     ((0x00080000&(data))>>19)
#define DRF_BIST_MODE_DRF_TEST_RESUME6_shift                                         (18)
#define DRF_BIST_MODE_DRF_TEST_RESUME6_mask                                          (0x00040000)
#define DRF_BIST_MODE_DRF_TEST_RESUME6(data)                                         (0x00040000&((data)<<18))
#define DRF_BIST_MODE_DRF_TEST_RESUME6_src(data)                                     ((0x00040000&(data))>>18)
#define DRF_BIST_MODE_get_DRF_TEST_RESUME6(data)                                     ((0x00040000&(data))>>18)
#define DRF_BIST_MODE_DRF_TEST_RESUME5_shift                                         (17)
#define DRF_BIST_MODE_DRF_TEST_RESUME5_mask                                          (0x00020000)
#define DRF_BIST_MODE_DRF_TEST_RESUME5(data)                                         (0x00020000&((data)<<17))
#define DRF_BIST_MODE_DRF_TEST_RESUME5_src(data)                                     ((0x00020000&(data))>>17)
#define DRF_BIST_MODE_get_DRF_TEST_RESUME5(data)                                     ((0x00020000&(data))>>17)
#define DRF_BIST_MODE_DRF_TEST_RESUME4_shift                                         (16)
#define DRF_BIST_MODE_DRF_TEST_RESUME4_mask                                          (0x00010000)
#define DRF_BIST_MODE_DRF_TEST_RESUME4(data)                                         (0x00010000&((data)<<16))
#define DRF_BIST_MODE_DRF_TEST_RESUME4_src(data)                                     ((0x00010000&(data))>>16)
#define DRF_BIST_MODE_get_DRF_TEST_RESUME4(data)                                     ((0x00010000&(data))>>16)
#define DRF_BIST_MODE_DRF_TEST_RESUME3_shift                                         (15)
#define DRF_BIST_MODE_DRF_TEST_RESUME3_mask                                          (0x00008000)
#define DRF_BIST_MODE_DRF_TEST_RESUME3(data)                                         (0x00008000&((data)<<15))
#define DRF_BIST_MODE_DRF_TEST_RESUME3_src(data)                                     ((0x00008000&(data))>>15)
#define DRF_BIST_MODE_get_DRF_TEST_RESUME3(data)                                     ((0x00008000&(data))>>15)
#define DRF_BIST_MODE_DRF_TEST_RESUME2_shift                                         (14)
#define DRF_BIST_MODE_DRF_TEST_RESUME2_mask                                          (0x00004000)
#define DRF_BIST_MODE_DRF_TEST_RESUME2(data)                                         (0x00004000&((data)<<14))
#define DRF_BIST_MODE_DRF_TEST_RESUME2_src(data)                                     ((0x00004000&(data))>>14)
#define DRF_BIST_MODE_get_DRF_TEST_RESUME2(data)                                     ((0x00004000&(data))>>14)
#define DRF_BIST_MODE_DRF_TEST_RESUME1_shift                                         (13)
#define DRF_BIST_MODE_DRF_TEST_RESUME1_mask                                          (0x00002000)
#define DRF_BIST_MODE_DRF_TEST_RESUME1(data)                                         (0x00002000&((data)<<13))
#define DRF_BIST_MODE_DRF_TEST_RESUME1_src(data)                                     ((0x00002000&(data))>>13)
#define DRF_BIST_MODE_get_DRF_TEST_RESUME1(data)                                     ((0x00002000&(data))>>13)
#define DRF_BIST_MODE_DRF_BIST_MODE13_shift                                          (12)
#define DRF_BIST_MODE_DRF_BIST_MODE13_mask                                           (0x00001000)
#define DRF_BIST_MODE_DRF_BIST_MODE13(data)                                          (0x00001000&((data)<<12))
#define DRF_BIST_MODE_DRF_BIST_MODE13_src(data)                                      ((0x00001000&(data))>>12)
#define DRF_BIST_MODE_get_DRF_BIST_MODE13(data)                                      ((0x00001000&(data))>>12)
#define DRF_BIST_MODE_DRF_BIST_MODE12_shift                                          (11)
#define DRF_BIST_MODE_DRF_BIST_MODE12_mask                                           (0x00000800)
#define DRF_BIST_MODE_DRF_BIST_MODE12(data)                                          (0x00000800&((data)<<11))
#define DRF_BIST_MODE_DRF_BIST_MODE12_src(data)                                      ((0x00000800&(data))>>11)
#define DRF_BIST_MODE_get_DRF_BIST_MODE12(data)                                      ((0x00000800&(data))>>11)
#define DRF_BIST_MODE_DRF_BIST_MODE11_shift                                          (10)
#define DRF_BIST_MODE_DRF_BIST_MODE11_mask                                           (0x00000400)
#define DRF_BIST_MODE_DRF_BIST_MODE11(data)                                          (0x00000400&((data)<<10))
#define DRF_BIST_MODE_DRF_BIST_MODE11_src(data)                                      ((0x00000400&(data))>>10)
#define DRF_BIST_MODE_get_DRF_BIST_MODE11(data)                                      ((0x00000400&(data))>>10)
#define DRF_BIST_MODE_DRF_BIST_MODE10_shift                                          (9)
#define DRF_BIST_MODE_DRF_BIST_MODE10_mask                                           (0x00000200)
#define DRF_BIST_MODE_DRF_BIST_MODE10(data)                                          (0x00000200&((data)<<9))
#define DRF_BIST_MODE_DRF_BIST_MODE10_src(data)                                      ((0x00000200&(data))>>9)
#define DRF_BIST_MODE_get_DRF_BIST_MODE10(data)                                      ((0x00000200&(data))>>9)
#define DRF_BIST_MODE_DRF_BIST_MODE9_shift                                           (8)
#define DRF_BIST_MODE_DRF_BIST_MODE9_mask                                            (0x00000100)
#define DRF_BIST_MODE_DRF_BIST_MODE9(data)                                           (0x00000100&((data)<<8))
#define DRF_BIST_MODE_DRF_BIST_MODE9_src(data)                                       ((0x00000100&(data))>>8)
#define DRF_BIST_MODE_get_DRF_BIST_MODE9(data)                                       ((0x00000100&(data))>>8)
#define DRF_BIST_MODE_DRF_BIST_MODE8_shift                                           (7)
#define DRF_BIST_MODE_DRF_BIST_MODE8_mask                                            (0x00000080)
#define DRF_BIST_MODE_DRF_BIST_MODE8(data)                                           (0x00000080&((data)<<7))
#define DRF_BIST_MODE_DRF_BIST_MODE8_src(data)                                       ((0x00000080&(data))>>7)
#define DRF_BIST_MODE_get_DRF_BIST_MODE8(data)                                       ((0x00000080&(data))>>7)
#define DRF_BIST_MODE_DRF_BIST_MODE7_shift                                           (6)
#define DRF_BIST_MODE_DRF_BIST_MODE7_mask                                            (0x00000040)
#define DRF_BIST_MODE_DRF_BIST_MODE7(data)                                           (0x00000040&((data)<<6))
#define DRF_BIST_MODE_DRF_BIST_MODE7_src(data)                                       ((0x00000040&(data))>>6)
#define DRF_BIST_MODE_get_DRF_BIST_MODE7(data)                                       ((0x00000040&(data))>>6)
#define DRF_BIST_MODE_DRF_BIST_MODE6_shift                                           (5)
#define DRF_BIST_MODE_DRF_BIST_MODE6_mask                                            (0x00000020)
#define DRF_BIST_MODE_DRF_BIST_MODE6(data)                                           (0x00000020&((data)<<5))
#define DRF_BIST_MODE_DRF_BIST_MODE6_src(data)                                       ((0x00000020&(data))>>5)
#define DRF_BIST_MODE_get_DRF_BIST_MODE6(data)                                       ((0x00000020&(data))>>5)
#define DRF_BIST_MODE_DRF_BIST_MODE5_shift                                           (4)
#define DRF_BIST_MODE_DRF_BIST_MODE5_mask                                            (0x00000010)
#define DRF_BIST_MODE_DRF_BIST_MODE5(data)                                           (0x00000010&((data)<<4))
#define DRF_BIST_MODE_DRF_BIST_MODE5_src(data)                                       ((0x00000010&(data))>>4)
#define DRF_BIST_MODE_get_DRF_BIST_MODE5(data)                                       ((0x00000010&(data))>>4)
#define DRF_BIST_MODE_DRF_BIST_MODE4_shift                                           (3)
#define DRF_BIST_MODE_DRF_BIST_MODE4_mask                                            (0x00000008)
#define DRF_BIST_MODE_DRF_BIST_MODE4(data)                                           (0x00000008&((data)<<3))
#define DRF_BIST_MODE_DRF_BIST_MODE4_src(data)                                       ((0x00000008&(data))>>3)
#define DRF_BIST_MODE_get_DRF_BIST_MODE4(data)                                       ((0x00000008&(data))>>3)
#define DRF_BIST_MODE_DRF_BIST_MODE3_shift                                           (2)
#define DRF_BIST_MODE_DRF_BIST_MODE3_mask                                            (0x00000004)
#define DRF_BIST_MODE_DRF_BIST_MODE3(data)                                           (0x00000004&((data)<<2))
#define DRF_BIST_MODE_DRF_BIST_MODE3_src(data)                                       ((0x00000004&(data))>>2)
#define DRF_BIST_MODE_get_DRF_BIST_MODE3(data)                                       ((0x00000004&(data))>>2)
#define DRF_BIST_MODE_DRF_BIST_MODE2_shift                                           (1)
#define DRF_BIST_MODE_DRF_BIST_MODE2_mask                                            (0x00000002)
#define DRF_BIST_MODE_DRF_BIST_MODE2(data)                                           (0x00000002&((data)<<1))
#define DRF_BIST_MODE_DRF_BIST_MODE2_src(data)                                       ((0x00000002&(data))>>1)
#define DRF_BIST_MODE_get_DRF_BIST_MODE2(data)                                       ((0x00000002&(data))>>1)
#define DRF_BIST_MODE_DRF_BIST_MODE1_shift                                           (0)
#define DRF_BIST_MODE_DRF_BIST_MODE1_mask                                            (0x00000001)
#define DRF_BIST_MODE_DRF_BIST_MODE1(data)                                           (0x00000001&((data)<<0))
#define DRF_BIST_MODE_DRF_BIST_MODE1_src(data)                                       ((0x00000001&(data))>>0)
#define DRF_BIST_MODE_get_DRF_BIST_MODE1(data)                                       ((0x00000001&(data))>>0)


#define BIST_RESULT1                                                                 0x18036010
#define BIST_RESULT1_reg_addr                                                        "0xB8036010"
#define BIST_RESULT1_reg                                                             0xB8036010
#define set_BIST_RESULT1_reg(data)   (*((volatile unsigned int*) BIST_RESULT1_reg)=data)
#define get_BIST_RESULT1_reg   (*((volatile unsigned int*) BIST_RESULT1_reg))
#define BIST_RESULT1_inst_adr                                                        "0x0004"
#define BIST_RESULT1_inst                                                            0x0004
#define BIST_RESULT1_DRF_START_PAUSE1_shift                                          (22)
#define BIST_RESULT1_DRF_START_PAUSE1_mask                                           (0x00400000)
#define BIST_RESULT1_DRF_START_PAUSE1(data)                                          (0x00400000&((data)<<22))
#define BIST_RESULT1_DRF_START_PAUSE1_src(data)                                      ((0x00400000&(data))>>22)
#define BIST_RESULT1_get_DRF_START_PAUSE1(data)                                      ((0x00400000&(data))>>22)
#define BIST_RESULT1_DRF_BIST_FAIL1_9_shift                                          (21)
#define BIST_RESULT1_DRF_BIST_FAIL1_9_mask                                           (0x00200000)
#define BIST_RESULT1_DRF_BIST_FAIL1_9(data)                                          (0x00200000&((data)<<21))
#define BIST_RESULT1_DRF_BIST_FAIL1_9_src(data)                                      ((0x00200000&(data))>>21)
#define BIST_RESULT1_get_DRF_BIST_FAIL1_9(data)                                      ((0x00200000&(data))>>21)
#define BIST_RESULT1_DRF_BIST_FAIL1_8_shift                                          (20)
#define BIST_RESULT1_DRF_BIST_FAIL1_8_mask                                           (0x00100000)
#define BIST_RESULT1_DRF_BIST_FAIL1_8(data)                                          (0x00100000&((data)<<20))
#define BIST_RESULT1_DRF_BIST_FAIL1_8_src(data)                                      ((0x00100000&(data))>>20)
#define BIST_RESULT1_get_DRF_BIST_FAIL1_8(data)                                      ((0x00100000&(data))>>20)
#define BIST_RESULT1_DRF_BIST_FAIL1_7_shift                                          (19)
#define BIST_RESULT1_DRF_BIST_FAIL1_7_mask                                           (0x00080000)
#define BIST_RESULT1_DRF_BIST_FAIL1_7(data)                                          (0x00080000&((data)<<19))
#define BIST_RESULT1_DRF_BIST_FAIL1_7_src(data)                                      ((0x00080000&(data))>>19)
#define BIST_RESULT1_get_DRF_BIST_FAIL1_7(data)                                      ((0x00080000&(data))>>19)
#define BIST_RESULT1_DRF_BIST_FAIL1_6_shift                                          (18)
#define BIST_RESULT1_DRF_BIST_FAIL1_6_mask                                           (0x00040000)
#define BIST_RESULT1_DRF_BIST_FAIL1_6(data)                                          (0x00040000&((data)<<18))
#define BIST_RESULT1_DRF_BIST_FAIL1_6_src(data)                                      ((0x00040000&(data))>>18)
#define BIST_RESULT1_get_DRF_BIST_FAIL1_6(data)                                      ((0x00040000&(data))>>18)
#define BIST_RESULT1_DRF_BIST_FAIL1_5_shift                                          (17)
#define BIST_RESULT1_DRF_BIST_FAIL1_5_mask                                           (0x00020000)
#define BIST_RESULT1_DRF_BIST_FAIL1_5(data)                                          (0x00020000&((data)<<17))
#define BIST_RESULT1_DRF_BIST_FAIL1_5_src(data)                                      ((0x00020000&(data))>>17)
#define BIST_RESULT1_get_DRF_BIST_FAIL1_5(data)                                      ((0x00020000&(data))>>17)
#define BIST_RESULT1_DRF_BIST_FAIL1_4_shift                                          (16)
#define BIST_RESULT1_DRF_BIST_FAIL1_4_mask                                           (0x00010000)
#define BIST_RESULT1_DRF_BIST_FAIL1_4(data)                                          (0x00010000&((data)<<16))
#define BIST_RESULT1_DRF_BIST_FAIL1_4_src(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT1_get_DRF_BIST_FAIL1_4(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT1_DRF_BIST_FAIL1_3_shift                                          (15)
#define BIST_RESULT1_DRF_BIST_FAIL1_3_mask                                           (0x00008000)
#define BIST_RESULT1_DRF_BIST_FAIL1_3(data)                                          (0x00008000&((data)<<15))
#define BIST_RESULT1_DRF_BIST_FAIL1_3_src(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT1_get_DRF_BIST_FAIL1_3(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT1_DRF_BIST_FAIL1_2_shift                                          (14)
#define BIST_RESULT1_DRF_BIST_FAIL1_2_mask                                           (0x00004000)
#define BIST_RESULT1_DRF_BIST_FAIL1_2(data)                                          (0x00004000&((data)<<14))
#define BIST_RESULT1_DRF_BIST_FAIL1_2_src(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT1_get_DRF_BIST_FAIL1_2(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT1_DRF_BIST_FAIL1_1_shift                                          (13)
#define BIST_RESULT1_DRF_BIST_FAIL1_1_mask                                           (0x00002000)
#define BIST_RESULT1_DRF_BIST_FAIL1_1(data)                                          (0x00002000&((data)<<13))
#define BIST_RESULT1_DRF_BIST_FAIL1_1_src(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT1_get_DRF_BIST_FAIL1_1(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT1_DRF_BIST_FAIL1_0_shift                                          (12)
#define BIST_RESULT1_DRF_BIST_FAIL1_0_mask                                           (0x00001000)
#define BIST_RESULT1_DRF_BIST_FAIL1_0(data)                                          (0x00001000&((data)<<12))
#define BIST_RESULT1_DRF_BIST_FAIL1_0_src(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT1_get_DRF_BIST_FAIL1_0(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT1_DRF_BIST_DONE1_shift                                            (11)
#define BIST_RESULT1_DRF_BIST_DONE1_mask                                             (0x00000800)
#define BIST_RESULT1_DRF_BIST_DONE1(data)                                            (0x00000800&((data)<<11))
#define BIST_RESULT1_DRF_BIST_DONE1_src(data)                                        ((0x00000800&(data))>>11)
#define BIST_RESULT1_get_DRF_BIST_DONE1(data)                                        ((0x00000800&(data))>>11)
#define BIST_RESULT1_BIST_FAIL1_9_shift                                              (10)
#define BIST_RESULT1_BIST_FAIL1_9_mask                                               (0x00000400)
#define BIST_RESULT1_BIST_FAIL1_9(data)                                              (0x00000400&((data)<<10))
#define BIST_RESULT1_BIST_FAIL1_9_src(data)                                          ((0x00000400&(data))>>10)
#define BIST_RESULT1_get_BIST_FAIL1_9(data)                                          ((0x00000400&(data))>>10)
#define BIST_RESULT1_BIST_FAIL1_8_shift                                              (9)
#define BIST_RESULT1_BIST_FAIL1_8_mask                                               (0x00000200)
#define BIST_RESULT1_BIST_FAIL1_8(data)                                              (0x00000200&((data)<<9))
#define BIST_RESULT1_BIST_FAIL1_8_src(data)                                          ((0x00000200&(data))>>9)
#define BIST_RESULT1_get_BIST_FAIL1_8(data)                                          ((0x00000200&(data))>>9)
#define BIST_RESULT1_BIST_FAIL1_7_shift                                              (8)
#define BIST_RESULT1_BIST_FAIL1_7_mask                                               (0x00000100)
#define BIST_RESULT1_BIST_FAIL1_7(data)                                              (0x00000100&((data)<<8))
#define BIST_RESULT1_BIST_FAIL1_7_src(data)                                          ((0x00000100&(data))>>8)
#define BIST_RESULT1_get_BIST_FAIL1_7(data)                                          ((0x00000100&(data))>>8)
#define BIST_RESULT1_BIST_FAIL1_6_shift                                              (7)
#define BIST_RESULT1_BIST_FAIL1_6_mask                                               (0x00000080)
#define BIST_RESULT1_BIST_FAIL1_6(data)                                              (0x00000080&((data)<<7))
#define BIST_RESULT1_BIST_FAIL1_6_src(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT1_get_BIST_FAIL1_6(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT1_BIST_FAIL1_5_shift                                              (6)
#define BIST_RESULT1_BIST_FAIL1_5_mask                                               (0x00000040)
#define BIST_RESULT1_BIST_FAIL1_5(data)                                              (0x00000040&((data)<<6))
#define BIST_RESULT1_BIST_FAIL1_5_src(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT1_get_BIST_FAIL1_5(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT1_BIST_FAIL1_4_shift                                              (5)
#define BIST_RESULT1_BIST_FAIL1_4_mask                                               (0x00000020)
#define BIST_RESULT1_BIST_FAIL1_4(data)                                              (0x00000020&((data)<<5))
#define BIST_RESULT1_BIST_FAIL1_4_src(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT1_get_BIST_FAIL1_4(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT1_BIST_FAIL1_3_shift                                              (4)
#define BIST_RESULT1_BIST_FAIL1_3_mask                                               (0x00000010)
#define BIST_RESULT1_BIST_FAIL1_3(data)                                              (0x00000010&((data)<<4))
#define BIST_RESULT1_BIST_FAIL1_3_src(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT1_get_BIST_FAIL1_3(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT1_BIST_FAIL1_2_shift                                              (3)
#define BIST_RESULT1_BIST_FAIL1_2_mask                                               (0x00000008)
#define BIST_RESULT1_BIST_FAIL1_2(data)                                              (0x00000008&((data)<<3))
#define BIST_RESULT1_BIST_FAIL1_2_src(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT1_get_BIST_FAIL1_2(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT1_BIST_FAIL1_1_shift                                              (2)
#define BIST_RESULT1_BIST_FAIL1_1_mask                                               (0x00000004)
#define BIST_RESULT1_BIST_FAIL1_1(data)                                              (0x00000004&((data)<<2))
#define BIST_RESULT1_BIST_FAIL1_1_src(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT1_get_BIST_FAIL1_1(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT1_BIST_FAIL1_0_shift                                              (1)
#define BIST_RESULT1_BIST_FAIL1_0_mask                                               (0x00000002)
#define BIST_RESULT1_BIST_FAIL1_0(data)                                              (0x00000002&((data)<<1))
#define BIST_RESULT1_BIST_FAIL1_0_src(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT1_get_BIST_FAIL1_0(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT1_BIST_DONE1_shift                                                (0)
#define BIST_RESULT1_BIST_DONE1_mask                                                 (0x00000001)
#define BIST_RESULT1_BIST_DONE1(data)                                                (0x00000001&((data)<<0))
#define BIST_RESULT1_BIST_DONE1_src(data)                                            ((0x00000001&(data))>>0)
#define BIST_RESULT1_get_BIST_DONE1(data)                                            ((0x00000001&(data))>>0)


#define BIST_RESULT2                                                                 0x18036014
#define BIST_RESULT2_reg_addr                                                        "0xB8036014"
#define BIST_RESULT2_reg                                                             0xB8036014
#define set_BIST_RESULT2_reg(data)   (*((volatile unsigned int*) BIST_RESULT2_reg)=data)
#define get_BIST_RESULT2_reg   (*((volatile unsigned int*) BIST_RESULT2_reg))
#define BIST_RESULT2_inst_adr                                                        "0x0005"
#define BIST_RESULT2_inst                                                            0x0005
#define BIST_RESULT2_DRF_START_PAUSE2_shift                                          (22)
#define BIST_RESULT2_DRF_START_PAUSE2_mask                                           (0x00400000)
#define BIST_RESULT2_DRF_START_PAUSE2(data)                                          (0x00400000&((data)<<22))
#define BIST_RESULT2_DRF_START_PAUSE2_src(data)                                      ((0x00400000&(data))>>22)
#define BIST_RESULT2_get_DRF_START_PAUSE2(data)                                      ((0x00400000&(data))>>22)
#define BIST_RESULT2_DRF_BIST_FAIL2_9_shift                                          (21)
#define BIST_RESULT2_DRF_BIST_FAIL2_9_mask                                           (0x00200000)
#define BIST_RESULT2_DRF_BIST_FAIL2_9(data)                                          (0x00200000&((data)<<21))
#define BIST_RESULT2_DRF_BIST_FAIL2_9_src(data)                                      ((0x00200000&(data))>>21)
#define BIST_RESULT2_get_DRF_BIST_FAIL2_9(data)                                      ((0x00200000&(data))>>21)
#define BIST_RESULT2_DRF_BIST_FAIL2_8_shift                                          (20)
#define BIST_RESULT2_DRF_BIST_FAIL2_8_mask                                           (0x00100000)
#define BIST_RESULT2_DRF_BIST_FAIL2_8(data)                                          (0x00100000&((data)<<20))
#define BIST_RESULT2_DRF_BIST_FAIL2_8_src(data)                                      ((0x00100000&(data))>>20)
#define BIST_RESULT2_get_DRF_BIST_FAIL2_8(data)                                      ((0x00100000&(data))>>20)
#define BIST_RESULT2_DRF_BIST_FAIL2_7_shift                                          (19)
#define BIST_RESULT2_DRF_BIST_FAIL2_7_mask                                           (0x00080000)
#define BIST_RESULT2_DRF_BIST_FAIL2_7(data)                                          (0x00080000&((data)<<19))
#define BIST_RESULT2_DRF_BIST_FAIL2_7_src(data)                                      ((0x00080000&(data))>>19)
#define BIST_RESULT2_get_DRF_BIST_FAIL2_7(data)                                      ((0x00080000&(data))>>19)
#define BIST_RESULT2_DRF_BIST_FAIL2_6_shift                                          (18)
#define BIST_RESULT2_DRF_BIST_FAIL2_6_mask                                           (0x00040000)
#define BIST_RESULT2_DRF_BIST_FAIL2_6(data)                                          (0x00040000&((data)<<18))
#define BIST_RESULT2_DRF_BIST_FAIL2_6_src(data)                                      ((0x00040000&(data))>>18)
#define BIST_RESULT2_get_DRF_BIST_FAIL2_6(data)                                      ((0x00040000&(data))>>18)
#define BIST_RESULT2_DRF_BIST_FAIL2_5_shift                                          (17)
#define BIST_RESULT2_DRF_BIST_FAIL2_5_mask                                           (0x00020000)
#define BIST_RESULT2_DRF_BIST_FAIL2_5(data)                                          (0x00020000&((data)<<17))
#define BIST_RESULT2_DRF_BIST_FAIL2_5_src(data)                                      ((0x00020000&(data))>>17)
#define BIST_RESULT2_get_DRF_BIST_FAIL2_5(data)                                      ((0x00020000&(data))>>17)
#define BIST_RESULT2_DRF_BIST_FAIL2_4_shift                                          (16)
#define BIST_RESULT2_DRF_BIST_FAIL2_4_mask                                           (0x00010000)
#define BIST_RESULT2_DRF_BIST_FAIL2_4(data)                                          (0x00010000&((data)<<16))
#define BIST_RESULT2_DRF_BIST_FAIL2_4_src(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT2_get_DRF_BIST_FAIL2_4(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT2_DRF_BIST_FAIL2_3_shift                                          (15)
#define BIST_RESULT2_DRF_BIST_FAIL2_3_mask                                           (0x00008000)
#define BIST_RESULT2_DRF_BIST_FAIL2_3(data)                                          (0x00008000&((data)<<15))
#define BIST_RESULT2_DRF_BIST_FAIL2_3_src(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT2_get_DRF_BIST_FAIL2_3(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT2_DRF_BIST_FAIL2_2_shift                                          (14)
#define BIST_RESULT2_DRF_BIST_FAIL2_2_mask                                           (0x00004000)
#define BIST_RESULT2_DRF_BIST_FAIL2_2(data)                                          (0x00004000&((data)<<14))
#define BIST_RESULT2_DRF_BIST_FAIL2_2_src(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT2_get_DRF_BIST_FAIL2_2(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT2_DRF_BIST_FAIL2_1_shift                                          (13)
#define BIST_RESULT2_DRF_BIST_FAIL2_1_mask                                           (0x00002000)
#define BIST_RESULT2_DRF_BIST_FAIL2_1(data)                                          (0x00002000&((data)<<13))
#define BIST_RESULT2_DRF_BIST_FAIL2_1_src(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT2_get_DRF_BIST_FAIL2_1(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT2_DRF_BIST_FAIL2_0_shift                                          (12)
#define BIST_RESULT2_DRF_BIST_FAIL2_0_mask                                           (0x00001000)
#define BIST_RESULT2_DRF_BIST_FAIL2_0(data)                                          (0x00001000&((data)<<12))
#define BIST_RESULT2_DRF_BIST_FAIL2_0_src(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT2_get_DRF_BIST_FAIL2_0(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT2_DRF_BIST_DONE2_shift                                            (11)
#define BIST_RESULT2_DRF_BIST_DONE2_mask                                             (0x00000800)
#define BIST_RESULT2_DRF_BIST_DONE2(data)                                            (0x00000800&((data)<<11))
#define BIST_RESULT2_DRF_BIST_DONE2_src(data)                                        ((0x00000800&(data))>>11)
#define BIST_RESULT2_get_DRF_BIST_DONE2(data)                                        ((0x00000800&(data))>>11)
#define BIST_RESULT2_BIST_FAIL2_9_shift                                              (10)
#define BIST_RESULT2_BIST_FAIL2_9_mask                                               (0x00000400)
#define BIST_RESULT2_BIST_FAIL2_9(data)                                              (0x00000400&((data)<<10))
#define BIST_RESULT2_BIST_FAIL2_9_src(data)                                          ((0x00000400&(data))>>10)
#define BIST_RESULT2_get_BIST_FAIL2_9(data)                                          ((0x00000400&(data))>>10)
#define BIST_RESULT2_BIST_FAIL2_8_shift                                              (9)
#define BIST_RESULT2_BIST_FAIL2_8_mask                                               (0x00000200)
#define BIST_RESULT2_BIST_FAIL2_8(data)                                              (0x00000200&((data)<<9))
#define BIST_RESULT2_BIST_FAIL2_8_src(data)                                          ((0x00000200&(data))>>9)
#define BIST_RESULT2_get_BIST_FAIL2_8(data)                                          ((0x00000200&(data))>>9)
#define BIST_RESULT2_BIST_FAIL2_7_shift                                              (8)
#define BIST_RESULT2_BIST_FAIL2_7_mask                                               (0x00000100)
#define BIST_RESULT2_BIST_FAIL2_7(data)                                              (0x00000100&((data)<<8))
#define BIST_RESULT2_BIST_FAIL2_7_src(data)                                          ((0x00000100&(data))>>8)
#define BIST_RESULT2_get_BIST_FAIL2_7(data)                                          ((0x00000100&(data))>>8)
#define BIST_RESULT2_BIST_FAIL2_6_shift                                              (7)
#define BIST_RESULT2_BIST_FAIL2_6_mask                                               (0x00000080)
#define BIST_RESULT2_BIST_FAIL2_6(data)                                              (0x00000080&((data)<<7))
#define BIST_RESULT2_BIST_FAIL2_6_src(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT2_get_BIST_FAIL2_6(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT2_BIST_FAIL2_5_shift                                              (6)
#define BIST_RESULT2_BIST_FAIL2_5_mask                                               (0x00000040)
#define BIST_RESULT2_BIST_FAIL2_5(data)                                              (0x00000040&((data)<<6))
#define BIST_RESULT2_BIST_FAIL2_5_src(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT2_get_BIST_FAIL2_5(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT2_BIST_FAIL2_4_shift                                              (5)
#define BIST_RESULT2_BIST_FAIL2_4_mask                                               (0x00000020)
#define BIST_RESULT2_BIST_FAIL2_4(data)                                              (0x00000020&((data)<<5))
#define BIST_RESULT2_BIST_FAIL2_4_src(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT2_get_BIST_FAIL2_4(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT2_BIST_FAIL2_3_shift                                              (4)
#define BIST_RESULT2_BIST_FAIL2_3_mask                                               (0x00000010)
#define BIST_RESULT2_BIST_FAIL2_3(data)                                              (0x00000010&((data)<<4))
#define BIST_RESULT2_BIST_FAIL2_3_src(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT2_get_BIST_FAIL2_3(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT2_BIST_FAIL2_2_shift                                              (3)
#define BIST_RESULT2_BIST_FAIL2_2_mask                                               (0x00000008)
#define BIST_RESULT2_BIST_FAIL2_2(data)                                              (0x00000008&((data)<<3))
#define BIST_RESULT2_BIST_FAIL2_2_src(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT2_get_BIST_FAIL2_2(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT2_BIST_FAIL2_1_shift                                              (2)
#define BIST_RESULT2_BIST_FAIL2_1_mask                                               (0x00000004)
#define BIST_RESULT2_BIST_FAIL2_1(data)                                              (0x00000004&((data)<<2))
#define BIST_RESULT2_BIST_FAIL2_1_src(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT2_get_BIST_FAIL2_1(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT2_BIST_FAIL2_0_shift                                              (1)
#define BIST_RESULT2_BIST_FAIL2_0_mask                                               (0x00000002)
#define BIST_RESULT2_BIST_FAIL2_0(data)                                              (0x00000002&((data)<<1))
#define BIST_RESULT2_BIST_FAIL2_0_src(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT2_get_BIST_FAIL2_0(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT2_BIST_DONE2_shift                                                (0)
#define BIST_RESULT2_BIST_DONE2_mask                                                 (0x00000001)
#define BIST_RESULT2_BIST_DONE2(data)                                                (0x00000001&((data)<<0))
#define BIST_RESULT2_BIST_DONE2_src(data)                                            ((0x00000001&(data))>>0)
#define BIST_RESULT2_get_BIST_DONE2(data)                                            ((0x00000001&(data))>>0)


#define BIST_RESULT3                                                                 0x18036018
#define BIST_RESULT3_reg_addr                                                        "0xB8036018"
#define BIST_RESULT3_reg                                                             0xB8036018
#define set_BIST_RESULT3_reg(data)   (*((volatile unsigned int*) BIST_RESULT3_reg)=data)
#define get_BIST_RESULT3_reg   (*((volatile unsigned int*) BIST_RESULT3_reg))
#define BIST_RESULT3_inst_adr                                                        "0x0006"
#define BIST_RESULT3_inst                                                            0x0006
#define BIST_RESULT3_DRF_START_PAUSE3_shift                                          (16)
#define BIST_RESULT3_DRF_START_PAUSE3_mask                                           (0x00010000)
#define BIST_RESULT3_DRF_START_PAUSE3(data)                                          (0x00010000&((data)<<16))
#define BIST_RESULT3_DRF_START_PAUSE3_src(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT3_get_DRF_START_PAUSE3(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT3_DRF_BIST_FAIL3_6_shift                                          (15)
#define BIST_RESULT3_DRF_BIST_FAIL3_6_mask                                           (0x00008000)
#define BIST_RESULT3_DRF_BIST_FAIL3_6(data)                                          (0x00008000&((data)<<15))
#define BIST_RESULT3_DRF_BIST_FAIL3_6_src(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT3_get_DRF_BIST_FAIL3_6(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT3_DRF_BIST_FAIL3_5_shift                                          (14)
#define BIST_RESULT3_DRF_BIST_FAIL3_5_mask                                           (0x00004000)
#define BIST_RESULT3_DRF_BIST_FAIL3_5(data)                                          (0x00004000&((data)<<14))
#define BIST_RESULT3_DRF_BIST_FAIL3_5_src(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT3_get_DRF_BIST_FAIL3_5(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT3_DRF_BIST_FAIL3_4_shift                                          (13)
#define BIST_RESULT3_DRF_BIST_FAIL3_4_mask                                           (0x00002000)
#define BIST_RESULT3_DRF_BIST_FAIL3_4(data)                                          (0x00002000&((data)<<13))
#define BIST_RESULT3_DRF_BIST_FAIL3_4_src(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT3_get_DRF_BIST_FAIL3_4(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT3_DRF_BIST_FAIL3_3_shift                                          (12)
#define BIST_RESULT3_DRF_BIST_FAIL3_3_mask                                           (0x00001000)
#define BIST_RESULT3_DRF_BIST_FAIL3_3(data)                                          (0x00001000&((data)<<12))
#define BIST_RESULT3_DRF_BIST_FAIL3_3_src(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT3_get_DRF_BIST_FAIL3_3(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT3_DRF_BIST_FAIL3_2_shift                                          (11)
#define BIST_RESULT3_DRF_BIST_FAIL3_2_mask                                           (0x00000800)
#define BIST_RESULT3_DRF_BIST_FAIL3_2(data)                                          (0x00000800&((data)<<11))
#define BIST_RESULT3_DRF_BIST_FAIL3_2_src(data)                                      ((0x00000800&(data))>>11)
#define BIST_RESULT3_get_DRF_BIST_FAIL3_2(data)                                      ((0x00000800&(data))>>11)
#define BIST_RESULT3_DRF_BIST_FAIL3_1_shift                                          (10)
#define BIST_RESULT3_DRF_BIST_FAIL3_1_mask                                           (0x00000400)
#define BIST_RESULT3_DRF_BIST_FAIL3_1(data)                                          (0x00000400&((data)<<10))
#define BIST_RESULT3_DRF_BIST_FAIL3_1_src(data)                                      ((0x00000400&(data))>>10)
#define BIST_RESULT3_get_DRF_BIST_FAIL3_1(data)                                      ((0x00000400&(data))>>10)
#define BIST_RESULT3_DRF_BIST_FAIL3_0_shift                                          (9)
#define BIST_RESULT3_DRF_BIST_FAIL3_0_mask                                           (0x00000200)
#define BIST_RESULT3_DRF_BIST_FAIL3_0(data)                                          (0x00000200&((data)<<9))
#define BIST_RESULT3_DRF_BIST_FAIL3_0_src(data)                                      ((0x00000200&(data))>>9)
#define BIST_RESULT3_get_DRF_BIST_FAIL3_0(data)                                      ((0x00000200&(data))>>9)
#define BIST_RESULT3_DRF_BIST_DONE3_shift                                            (8)
#define BIST_RESULT3_DRF_BIST_DONE3_mask                                             (0x00000100)
#define BIST_RESULT3_DRF_BIST_DONE3(data)                                            (0x00000100&((data)<<8))
#define BIST_RESULT3_DRF_BIST_DONE3_src(data)                                        ((0x00000100&(data))>>8)
#define BIST_RESULT3_get_DRF_BIST_DONE3(data)                                        ((0x00000100&(data))>>8)
#define BIST_RESULT3_BIST_FAIL3_6_shift                                              (7)
#define BIST_RESULT3_BIST_FAIL3_6_mask                                               (0x00000080)
#define BIST_RESULT3_BIST_FAIL3_6(data)                                              (0x00000080&((data)<<7))
#define BIST_RESULT3_BIST_FAIL3_6_src(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT3_get_BIST_FAIL3_6(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT3_BIST_FAIL3_5_shift                                              (6)
#define BIST_RESULT3_BIST_FAIL3_5_mask                                               (0x00000040)
#define BIST_RESULT3_BIST_FAIL3_5(data)                                              (0x00000040&((data)<<6))
#define BIST_RESULT3_BIST_FAIL3_5_src(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT3_get_BIST_FAIL3_5(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT3_BIST_FAIL3_4_shift                                              (5)
#define BIST_RESULT3_BIST_FAIL3_4_mask                                               (0x00000020)
#define BIST_RESULT3_BIST_FAIL3_4(data)                                              (0x00000020&((data)<<5))
#define BIST_RESULT3_BIST_FAIL3_4_src(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT3_get_BIST_FAIL3_4(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT3_BIST_FAIL3_3_shift                                              (4)
#define BIST_RESULT3_BIST_FAIL3_3_mask                                               (0x00000010)
#define BIST_RESULT3_BIST_FAIL3_3(data)                                              (0x00000010&((data)<<4))
#define BIST_RESULT3_BIST_FAIL3_3_src(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT3_get_BIST_FAIL3_3(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT3_BIST_FAIL3_2_shift                                              (3)
#define BIST_RESULT3_BIST_FAIL3_2_mask                                               (0x00000008)
#define BIST_RESULT3_BIST_FAIL3_2(data)                                              (0x00000008&((data)<<3))
#define BIST_RESULT3_BIST_FAIL3_2_src(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT3_get_BIST_FAIL3_2(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT3_BIST_FAIL3_1_shift                                              (2)
#define BIST_RESULT3_BIST_FAIL3_1_mask                                               (0x00000004)
#define BIST_RESULT3_BIST_FAIL3_1(data)                                              (0x00000004&((data)<<2))
#define BIST_RESULT3_BIST_FAIL3_1_src(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT3_get_BIST_FAIL3_1(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT3_BIST_FAIL3_0_shift                                              (1)
#define BIST_RESULT3_BIST_FAIL3_0_mask                                               (0x00000002)
#define BIST_RESULT3_BIST_FAIL3_0(data)                                              (0x00000002&((data)<<1))
#define BIST_RESULT3_BIST_FAIL3_0_src(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT3_get_BIST_FAIL3_0(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT3_BIST_DONE3_shift                                                (0)
#define BIST_RESULT3_BIST_DONE3_mask                                                 (0x00000001)
#define BIST_RESULT3_BIST_DONE3(data)                                                (0x00000001&((data)<<0))
#define BIST_RESULT3_BIST_DONE3_src(data)                                            ((0x00000001&(data))>>0)
#define BIST_RESULT3_get_BIST_DONE3(data)                                            ((0x00000001&(data))>>0)


#define BIST_RESULT4                                                                 0x1803601C
#define BIST_RESULT4_reg_addr                                                        "0xB803601C"
#define BIST_RESULT4_reg                                                             0xB803601C
#define set_BIST_RESULT4_reg(data)   (*((volatile unsigned int*) BIST_RESULT4_reg)=data)
#define get_BIST_RESULT4_reg   (*((volatile unsigned int*) BIST_RESULT4_reg))
#define BIST_RESULT4_inst_adr                                                        "0x0007"
#define BIST_RESULT4_inst                                                            0x0007
#define BIST_RESULT4_DRF_START_PAUSE4_shift                                          (16)
#define BIST_RESULT4_DRF_START_PAUSE4_mask                                           (0x00010000)
#define BIST_RESULT4_DRF_START_PAUSE4(data)                                          (0x00010000&((data)<<16))
#define BIST_RESULT4_DRF_START_PAUSE4_src(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT4_get_DRF_START_PAUSE4(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT4_DRF_BIST_FAIL4_6_shift                                          (15)
#define BIST_RESULT4_DRF_BIST_FAIL4_6_mask                                           (0x00008000)
#define BIST_RESULT4_DRF_BIST_FAIL4_6(data)                                          (0x00008000&((data)<<15))
#define BIST_RESULT4_DRF_BIST_FAIL4_6_src(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT4_get_DRF_BIST_FAIL4_6(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT4_DRF_BIST_FAIL4_5_shift                                          (14)
#define BIST_RESULT4_DRF_BIST_FAIL4_5_mask                                           (0x00004000)
#define BIST_RESULT4_DRF_BIST_FAIL4_5(data)                                          (0x00004000&((data)<<14))
#define BIST_RESULT4_DRF_BIST_FAIL4_5_src(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT4_get_DRF_BIST_FAIL4_5(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT4_DRF_BIST_FAIL4_4_shift                                          (13)
#define BIST_RESULT4_DRF_BIST_FAIL4_4_mask                                           (0x00002000)
#define BIST_RESULT4_DRF_BIST_FAIL4_4(data)                                          (0x00002000&((data)<<13))
#define BIST_RESULT4_DRF_BIST_FAIL4_4_src(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT4_get_DRF_BIST_FAIL4_4(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT4_DRF_BIST_FAIL4_3_shift                                          (12)
#define BIST_RESULT4_DRF_BIST_FAIL4_3_mask                                           (0x00001000)
#define BIST_RESULT4_DRF_BIST_FAIL4_3(data)                                          (0x00001000&((data)<<12))
#define BIST_RESULT4_DRF_BIST_FAIL4_3_src(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT4_get_DRF_BIST_FAIL4_3(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT4_DRF_BIST_FAIL4_2_shift                                          (11)
#define BIST_RESULT4_DRF_BIST_FAIL4_2_mask                                           (0x00000800)
#define BIST_RESULT4_DRF_BIST_FAIL4_2(data)                                          (0x00000800&((data)<<11))
#define BIST_RESULT4_DRF_BIST_FAIL4_2_src(data)                                      ((0x00000800&(data))>>11)
#define BIST_RESULT4_get_DRF_BIST_FAIL4_2(data)                                      ((0x00000800&(data))>>11)
#define BIST_RESULT4_DRF_BIST_FAIL4_1_shift                                          (10)
#define BIST_RESULT4_DRF_BIST_FAIL4_1_mask                                           (0x00000400)
#define BIST_RESULT4_DRF_BIST_FAIL4_1(data)                                          (0x00000400&((data)<<10))
#define BIST_RESULT4_DRF_BIST_FAIL4_1_src(data)                                      ((0x00000400&(data))>>10)
#define BIST_RESULT4_get_DRF_BIST_FAIL4_1(data)                                      ((0x00000400&(data))>>10)
#define BIST_RESULT4_DRF_BIST_FAIL4_0_shift                                          (9)
#define BIST_RESULT4_DRF_BIST_FAIL4_0_mask                                           (0x00000200)
#define BIST_RESULT4_DRF_BIST_FAIL4_0(data)                                          (0x00000200&((data)<<9))
#define BIST_RESULT4_DRF_BIST_FAIL4_0_src(data)                                      ((0x00000200&(data))>>9)
#define BIST_RESULT4_get_DRF_BIST_FAIL4_0(data)                                      ((0x00000200&(data))>>9)
#define BIST_RESULT4_DRF_BIST_DONE4_shift                                            (8)
#define BIST_RESULT4_DRF_BIST_DONE4_mask                                             (0x00000100)
#define BIST_RESULT4_DRF_BIST_DONE4(data)                                            (0x00000100&((data)<<8))
#define BIST_RESULT4_DRF_BIST_DONE4_src(data)                                        ((0x00000100&(data))>>8)
#define BIST_RESULT4_get_DRF_BIST_DONE4(data)                                        ((0x00000100&(data))>>8)
#define BIST_RESULT4_BIST_FAIL4_6_shift                                              (7)
#define BIST_RESULT4_BIST_FAIL4_6_mask                                               (0x00000080)
#define BIST_RESULT4_BIST_FAIL4_6(data)                                              (0x00000080&((data)<<7))
#define BIST_RESULT4_BIST_FAIL4_6_src(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT4_get_BIST_FAIL4_6(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT4_BIST_FAIL4_5_shift                                              (6)
#define BIST_RESULT4_BIST_FAIL4_5_mask                                               (0x00000040)
#define BIST_RESULT4_BIST_FAIL4_5(data)                                              (0x00000040&((data)<<6))
#define BIST_RESULT4_BIST_FAIL4_5_src(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT4_get_BIST_FAIL4_5(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT4_BIST_FAIL4_4_shift                                              (5)
#define BIST_RESULT4_BIST_FAIL4_4_mask                                               (0x00000020)
#define BIST_RESULT4_BIST_FAIL4_4(data)                                              (0x00000020&((data)<<5))
#define BIST_RESULT4_BIST_FAIL4_4_src(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT4_get_BIST_FAIL4_4(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT4_BIST_FAIL4_3_shift                                              (4)
#define BIST_RESULT4_BIST_FAIL4_3_mask                                               (0x00000010)
#define BIST_RESULT4_BIST_FAIL4_3(data)                                              (0x00000010&((data)<<4))
#define BIST_RESULT4_BIST_FAIL4_3_src(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT4_get_BIST_FAIL4_3(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT4_BIST_FAIL4_2_shift                                              (3)
#define BIST_RESULT4_BIST_FAIL4_2_mask                                               (0x00000008)
#define BIST_RESULT4_BIST_FAIL4_2(data)                                              (0x00000008&((data)<<3))
#define BIST_RESULT4_BIST_FAIL4_2_src(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT4_get_BIST_FAIL4_2(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT4_BIST_FAIL4_1_shift                                              (2)
#define BIST_RESULT4_BIST_FAIL4_1_mask                                               (0x00000004)
#define BIST_RESULT4_BIST_FAIL4_1(data)                                              (0x00000004&((data)<<2))
#define BIST_RESULT4_BIST_FAIL4_1_src(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT4_get_BIST_FAIL4_1(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT4_BIST_FAIL4_0_shift                                              (1)
#define BIST_RESULT4_BIST_FAIL4_0_mask                                               (0x00000002)
#define BIST_RESULT4_BIST_FAIL4_0(data)                                              (0x00000002&((data)<<1))
#define BIST_RESULT4_BIST_FAIL4_0_src(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT4_get_BIST_FAIL4_0(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT4_BIST_DONE4_shift                                                (0)
#define BIST_RESULT4_BIST_DONE4_mask                                                 (0x00000001)
#define BIST_RESULT4_BIST_DONE4(data)                                                (0x00000001&((data)<<0))
#define BIST_RESULT4_BIST_DONE4_src(data)                                            ((0x00000001&(data))>>0)
#define BIST_RESULT4_get_BIST_DONE4(data)                                            ((0x00000001&(data))>>0)


#define BIST_RESULT5                                                                 0x18036020
#define BIST_RESULT5_reg_addr                                                        "0xB8036020"
#define BIST_RESULT5_reg                                                             0xB8036020
#define set_BIST_RESULT5_reg(data)   (*((volatile unsigned int*) BIST_RESULT5_reg)=data)
#define get_BIST_RESULT5_reg   (*((volatile unsigned int*) BIST_RESULT5_reg))
#define BIST_RESULT5_inst_adr                                                        "0x0008"
#define BIST_RESULT5_inst                                                            0x0008
#define BIST_RESULT5_DRF_START_PAUSE5_shift                                          (22)
#define BIST_RESULT5_DRF_START_PAUSE5_mask                                           (0x00400000)
#define BIST_RESULT5_DRF_START_PAUSE5(data)                                          (0x00400000&((data)<<22))
#define BIST_RESULT5_DRF_START_PAUSE5_src(data)                                      ((0x00400000&(data))>>22)
#define BIST_RESULT5_get_DRF_START_PAUSE5(data)                                      ((0x00400000&(data))>>22)
#define BIST_RESULT5_DRF_BIST_FAIL5_9_shift                                          (21)
#define BIST_RESULT5_DRF_BIST_FAIL5_9_mask                                           (0x00200000)
#define BIST_RESULT5_DRF_BIST_FAIL5_9(data)                                          (0x00200000&((data)<<21))
#define BIST_RESULT5_DRF_BIST_FAIL5_9_src(data)                                      ((0x00200000&(data))>>21)
#define BIST_RESULT5_get_DRF_BIST_FAIL5_9(data)                                      ((0x00200000&(data))>>21)
#define BIST_RESULT5_DRF_BIST_FAIL5_8_shift                                          (20)
#define BIST_RESULT5_DRF_BIST_FAIL5_8_mask                                           (0x00100000)
#define BIST_RESULT5_DRF_BIST_FAIL5_8(data)                                          (0x00100000&((data)<<20))
#define BIST_RESULT5_DRF_BIST_FAIL5_8_src(data)                                      ((0x00100000&(data))>>20)
#define BIST_RESULT5_get_DRF_BIST_FAIL5_8(data)                                      ((0x00100000&(data))>>20)
#define BIST_RESULT5_DRF_BIST_FAIL5_7_shift                                          (19)
#define BIST_RESULT5_DRF_BIST_FAIL5_7_mask                                           (0x00080000)
#define BIST_RESULT5_DRF_BIST_FAIL5_7(data)                                          (0x00080000&((data)<<19))
#define BIST_RESULT5_DRF_BIST_FAIL5_7_src(data)                                      ((0x00080000&(data))>>19)
#define BIST_RESULT5_get_DRF_BIST_FAIL5_7(data)                                      ((0x00080000&(data))>>19)
#define BIST_RESULT5_DRF_BIST_FAIL5_6_shift                                          (18)
#define BIST_RESULT5_DRF_BIST_FAIL5_6_mask                                           (0x00040000)
#define BIST_RESULT5_DRF_BIST_FAIL5_6(data)                                          (0x00040000&((data)<<18))
#define BIST_RESULT5_DRF_BIST_FAIL5_6_src(data)                                      ((0x00040000&(data))>>18)
#define BIST_RESULT5_get_DRF_BIST_FAIL5_6(data)                                      ((0x00040000&(data))>>18)
#define BIST_RESULT5_DRF_BIST_FAIL5_5_shift                                          (17)
#define BIST_RESULT5_DRF_BIST_FAIL5_5_mask                                           (0x00020000)
#define BIST_RESULT5_DRF_BIST_FAIL5_5(data)                                          (0x00020000&((data)<<17))
#define BIST_RESULT5_DRF_BIST_FAIL5_5_src(data)                                      ((0x00020000&(data))>>17)
#define BIST_RESULT5_get_DRF_BIST_FAIL5_5(data)                                      ((0x00020000&(data))>>17)
#define BIST_RESULT5_DRF_BIST_FAIL5_4_shift                                          (16)
#define BIST_RESULT5_DRF_BIST_FAIL5_4_mask                                           (0x00010000)
#define BIST_RESULT5_DRF_BIST_FAIL5_4(data)                                          (0x00010000&((data)<<16))
#define BIST_RESULT5_DRF_BIST_FAIL5_4_src(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT5_get_DRF_BIST_FAIL5_4(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT5_DRF_BIST_FAIL5_3_shift                                          (15)
#define BIST_RESULT5_DRF_BIST_FAIL5_3_mask                                           (0x00008000)
#define BIST_RESULT5_DRF_BIST_FAIL5_3(data)                                          (0x00008000&((data)<<15))
#define BIST_RESULT5_DRF_BIST_FAIL5_3_src(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT5_get_DRF_BIST_FAIL5_3(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT5_DRF_BIST_FAIL5_2_shift                                          (14)
#define BIST_RESULT5_DRF_BIST_FAIL5_2_mask                                           (0x00004000)
#define BIST_RESULT5_DRF_BIST_FAIL5_2(data)                                          (0x00004000&((data)<<14))
#define BIST_RESULT5_DRF_BIST_FAIL5_2_src(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT5_get_DRF_BIST_FAIL5_2(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT5_DRF_BIST_FAIL5_1_shift                                          (13)
#define BIST_RESULT5_DRF_BIST_FAIL5_1_mask                                           (0x00002000)
#define BIST_RESULT5_DRF_BIST_FAIL5_1(data)                                          (0x00002000&((data)<<13))
#define BIST_RESULT5_DRF_BIST_FAIL5_1_src(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT5_get_DRF_BIST_FAIL5_1(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT5_DRF_BIST_FAIL5_0_shift                                          (12)
#define BIST_RESULT5_DRF_BIST_FAIL5_0_mask                                           (0x00001000)
#define BIST_RESULT5_DRF_BIST_FAIL5_0(data)                                          (0x00001000&((data)<<12))
#define BIST_RESULT5_DRF_BIST_FAIL5_0_src(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT5_get_DRF_BIST_FAIL5_0(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT5_DRF_BIST_DONE5_shift                                            (11)
#define BIST_RESULT5_DRF_BIST_DONE5_mask                                             (0x00000800)
#define BIST_RESULT5_DRF_BIST_DONE5(data)                                            (0x00000800&((data)<<11))
#define BIST_RESULT5_DRF_BIST_DONE5_src(data)                                        ((0x00000800&(data))>>11)
#define BIST_RESULT5_get_DRF_BIST_DONE5(data)                                        ((0x00000800&(data))>>11)
#define BIST_RESULT5_BIST_FAIL5_9_shift                                              (10)
#define BIST_RESULT5_BIST_FAIL5_9_mask                                               (0x00000400)
#define BIST_RESULT5_BIST_FAIL5_9(data)                                              (0x00000400&((data)<<10))
#define BIST_RESULT5_BIST_FAIL5_9_src(data)                                          ((0x00000400&(data))>>10)
#define BIST_RESULT5_get_BIST_FAIL5_9(data)                                          ((0x00000400&(data))>>10)
#define BIST_RESULT5_BIST_FAIL5_8_shift                                              (9)
#define BIST_RESULT5_BIST_FAIL5_8_mask                                               (0x00000200)
#define BIST_RESULT5_BIST_FAIL5_8(data)                                              (0x00000200&((data)<<9))
#define BIST_RESULT5_BIST_FAIL5_8_src(data)                                          ((0x00000200&(data))>>9)
#define BIST_RESULT5_get_BIST_FAIL5_8(data)                                          ((0x00000200&(data))>>9)
#define BIST_RESULT5_BIST_FAIL5_7_shift                                              (8)
#define BIST_RESULT5_BIST_FAIL5_7_mask                                               (0x00000100)
#define BIST_RESULT5_BIST_FAIL5_7(data)                                              (0x00000100&((data)<<8))
#define BIST_RESULT5_BIST_FAIL5_7_src(data)                                          ((0x00000100&(data))>>8)
#define BIST_RESULT5_get_BIST_FAIL5_7(data)                                          ((0x00000100&(data))>>8)
#define BIST_RESULT5_BIST_FAIL5_6_shift                                              (7)
#define BIST_RESULT5_BIST_FAIL5_6_mask                                               (0x00000080)
#define BIST_RESULT5_BIST_FAIL5_6(data)                                              (0x00000080&((data)<<7))
#define BIST_RESULT5_BIST_FAIL5_6_src(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT5_get_BIST_FAIL5_6(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT5_BIST_FAIL5_5_shift                                              (6)
#define BIST_RESULT5_BIST_FAIL5_5_mask                                               (0x00000040)
#define BIST_RESULT5_BIST_FAIL5_5(data)                                              (0x00000040&((data)<<6))
#define BIST_RESULT5_BIST_FAIL5_5_src(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT5_get_BIST_FAIL5_5(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT5_BIST_FAIL5_4_shift                                              (5)
#define BIST_RESULT5_BIST_FAIL5_4_mask                                               (0x00000020)
#define BIST_RESULT5_BIST_FAIL5_4(data)                                              (0x00000020&((data)<<5))
#define BIST_RESULT5_BIST_FAIL5_4_src(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT5_get_BIST_FAIL5_4(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT5_BIST_FAIL5_3_shift                                              (4)
#define BIST_RESULT5_BIST_FAIL5_3_mask                                               (0x00000010)
#define BIST_RESULT5_BIST_FAIL5_3(data)                                              (0x00000010&((data)<<4))
#define BIST_RESULT5_BIST_FAIL5_3_src(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT5_get_BIST_FAIL5_3(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT5_BIST_FAIL5_2_shift                                              (3)
#define BIST_RESULT5_BIST_FAIL5_2_mask                                               (0x00000008)
#define BIST_RESULT5_BIST_FAIL5_2(data)                                              (0x00000008&((data)<<3))
#define BIST_RESULT5_BIST_FAIL5_2_src(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT5_get_BIST_FAIL5_2(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT5_BIST_FAIL5_1_shift                                              (2)
#define BIST_RESULT5_BIST_FAIL5_1_mask                                               (0x00000004)
#define BIST_RESULT5_BIST_FAIL5_1(data)                                              (0x00000004&((data)<<2))
#define BIST_RESULT5_BIST_FAIL5_1_src(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT5_get_BIST_FAIL5_1(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT5_BIST_FAIL5_0_shift                                              (1)
#define BIST_RESULT5_BIST_FAIL5_0_mask                                               (0x00000002)
#define BIST_RESULT5_BIST_FAIL5_0(data)                                              (0x00000002&((data)<<1))
#define BIST_RESULT5_BIST_FAIL5_0_src(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT5_get_BIST_FAIL5_0(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT5_BIST_DONE5_shift                                                (0)
#define BIST_RESULT5_BIST_DONE5_mask                                                 (0x00000001)
#define BIST_RESULT5_BIST_DONE5(data)                                                (0x00000001&((data)<<0))
#define BIST_RESULT5_BIST_DONE5_src(data)                                            ((0x00000001&(data))>>0)
#define BIST_RESULT5_get_BIST_DONE5(data)                                            ((0x00000001&(data))>>0)


#define BIST_RESULT6                                                                 0x18036024
#define BIST_RESULT6_reg_addr                                                        "0xB8036024"
#define BIST_RESULT6_reg                                                             0xB8036024
#define set_BIST_RESULT6_reg(data)   (*((volatile unsigned int*) BIST_RESULT6_reg)=data)
#define get_BIST_RESULT6_reg   (*((volatile unsigned int*) BIST_RESULT6_reg))
#define BIST_RESULT6_inst_adr                                                        "0x0009"
#define BIST_RESULT6_inst                                                            0x0009
#define BIST_RESULT6_DRF_START_PAUSE6_shift                                          (22)
#define BIST_RESULT6_DRF_START_PAUSE6_mask                                           (0x00400000)
#define BIST_RESULT6_DRF_START_PAUSE6(data)                                          (0x00400000&((data)<<22))
#define BIST_RESULT6_DRF_START_PAUSE6_src(data)                                      ((0x00400000&(data))>>22)
#define BIST_RESULT6_get_DRF_START_PAUSE6(data)                                      ((0x00400000&(data))>>22)
#define BIST_RESULT6_DRF_BIST_FAIL6_9_shift                                          (21)
#define BIST_RESULT6_DRF_BIST_FAIL6_9_mask                                           (0x00200000)
#define BIST_RESULT6_DRF_BIST_FAIL6_9(data)                                          (0x00200000&((data)<<21))
#define BIST_RESULT6_DRF_BIST_FAIL6_9_src(data)                                      ((0x00200000&(data))>>21)
#define BIST_RESULT6_get_DRF_BIST_FAIL6_9(data)                                      ((0x00200000&(data))>>21)
#define BIST_RESULT6_DRF_BIST_FAIL6_8_shift                                          (20)
#define BIST_RESULT6_DRF_BIST_FAIL6_8_mask                                           (0x00100000)
#define BIST_RESULT6_DRF_BIST_FAIL6_8(data)                                          (0x00100000&((data)<<20))
#define BIST_RESULT6_DRF_BIST_FAIL6_8_src(data)                                      ((0x00100000&(data))>>20)
#define BIST_RESULT6_get_DRF_BIST_FAIL6_8(data)                                      ((0x00100000&(data))>>20)
#define BIST_RESULT6_DRF_BIST_FAIL6_7_shift                                          (19)
#define BIST_RESULT6_DRF_BIST_FAIL6_7_mask                                           (0x00080000)
#define BIST_RESULT6_DRF_BIST_FAIL6_7(data)                                          (0x00080000&((data)<<19))
#define BIST_RESULT6_DRF_BIST_FAIL6_7_src(data)                                      ((0x00080000&(data))>>19)
#define BIST_RESULT6_get_DRF_BIST_FAIL6_7(data)                                      ((0x00080000&(data))>>19)
#define BIST_RESULT6_DRF_BIST_FAIL6_6_shift                                          (18)
#define BIST_RESULT6_DRF_BIST_FAIL6_6_mask                                           (0x00040000)
#define BIST_RESULT6_DRF_BIST_FAIL6_6(data)                                          (0x00040000&((data)<<18))
#define BIST_RESULT6_DRF_BIST_FAIL6_6_src(data)                                      ((0x00040000&(data))>>18)
#define BIST_RESULT6_get_DRF_BIST_FAIL6_6(data)                                      ((0x00040000&(data))>>18)
#define BIST_RESULT6_DRF_BIST_FAIL6_5_shift                                          (17)
#define BIST_RESULT6_DRF_BIST_FAIL6_5_mask                                           (0x00020000)
#define BIST_RESULT6_DRF_BIST_FAIL6_5(data)                                          (0x00020000&((data)<<17))
#define BIST_RESULT6_DRF_BIST_FAIL6_5_src(data)                                      ((0x00020000&(data))>>17)
#define BIST_RESULT6_get_DRF_BIST_FAIL6_5(data)                                      ((0x00020000&(data))>>17)
#define BIST_RESULT6_DRF_BIST_FAIL6_4_shift                                          (16)
#define BIST_RESULT6_DRF_BIST_FAIL6_4_mask                                           (0x00010000)
#define BIST_RESULT6_DRF_BIST_FAIL6_4(data)                                          (0x00010000&((data)<<16))
#define BIST_RESULT6_DRF_BIST_FAIL6_4_src(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT6_get_DRF_BIST_FAIL6_4(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT6_DRF_BIST_FAIL6_3_shift                                          (15)
#define BIST_RESULT6_DRF_BIST_FAIL6_3_mask                                           (0x00008000)
#define BIST_RESULT6_DRF_BIST_FAIL6_3(data)                                          (0x00008000&((data)<<15))
#define BIST_RESULT6_DRF_BIST_FAIL6_3_src(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT6_get_DRF_BIST_FAIL6_3(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT6_DRF_BIST_FAIL6_2_shift                                          (14)
#define BIST_RESULT6_DRF_BIST_FAIL6_2_mask                                           (0x00004000)
#define BIST_RESULT6_DRF_BIST_FAIL6_2(data)                                          (0x00004000&((data)<<14))
#define BIST_RESULT6_DRF_BIST_FAIL6_2_src(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT6_get_DRF_BIST_FAIL6_2(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT6_DRF_BIST_FAIL6_1_shift                                          (13)
#define BIST_RESULT6_DRF_BIST_FAIL6_1_mask                                           (0x00002000)
#define BIST_RESULT6_DRF_BIST_FAIL6_1(data)                                          (0x00002000&((data)<<13))
#define BIST_RESULT6_DRF_BIST_FAIL6_1_src(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT6_get_DRF_BIST_FAIL6_1(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT6_DRF_BIST_FAIL6_0_shift                                          (12)
#define BIST_RESULT6_DRF_BIST_FAIL6_0_mask                                           (0x00001000)
#define BIST_RESULT6_DRF_BIST_FAIL6_0(data)                                          (0x00001000&((data)<<12))
#define BIST_RESULT6_DRF_BIST_FAIL6_0_src(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT6_get_DRF_BIST_FAIL6_0(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT6_DRF_BIST_DONE6_shift                                            (11)
#define BIST_RESULT6_DRF_BIST_DONE6_mask                                             (0x00000800)
#define BIST_RESULT6_DRF_BIST_DONE6(data)                                            (0x00000800&((data)<<11))
#define BIST_RESULT6_DRF_BIST_DONE6_src(data)                                        ((0x00000800&(data))>>11)
#define BIST_RESULT6_get_DRF_BIST_DONE6(data)                                        ((0x00000800&(data))>>11)
#define BIST_RESULT6_BIST_FAIL6_9_shift                                              (10)
#define BIST_RESULT6_BIST_FAIL6_9_mask                                               (0x00000400)
#define BIST_RESULT6_BIST_FAIL6_9(data)                                              (0x00000400&((data)<<10))
#define BIST_RESULT6_BIST_FAIL6_9_src(data)                                          ((0x00000400&(data))>>10)
#define BIST_RESULT6_get_BIST_FAIL6_9(data)                                          ((0x00000400&(data))>>10)
#define BIST_RESULT6_BIST_FAIL6_8_shift                                              (9)
#define BIST_RESULT6_BIST_FAIL6_8_mask                                               (0x00000200)
#define BIST_RESULT6_BIST_FAIL6_8(data)                                              (0x00000200&((data)<<9))
#define BIST_RESULT6_BIST_FAIL6_8_src(data)                                          ((0x00000200&(data))>>9)
#define BIST_RESULT6_get_BIST_FAIL6_8(data)                                          ((0x00000200&(data))>>9)
#define BIST_RESULT6_BIST_FAIL6_7_shift                                              (8)
#define BIST_RESULT6_BIST_FAIL6_7_mask                                               (0x00000100)
#define BIST_RESULT6_BIST_FAIL6_7(data)                                              (0x00000100&((data)<<8))
#define BIST_RESULT6_BIST_FAIL6_7_src(data)                                          ((0x00000100&(data))>>8)
#define BIST_RESULT6_get_BIST_FAIL6_7(data)                                          ((0x00000100&(data))>>8)
#define BIST_RESULT6_BIST_FAIL6_6_shift                                              (7)
#define BIST_RESULT6_BIST_FAIL6_6_mask                                               (0x00000080)
#define BIST_RESULT6_BIST_FAIL6_6(data)                                              (0x00000080&((data)<<7))
#define BIST_RESULT6_BIST_FAIL6_6_src(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT6_get_BIST_FAIL6_6(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT6_BIST_FAIL6_5_shift                                              (6)
#define BIST_RESULT6_BIST_FAIL6_5_mask                                               (0x00000040)
#define BIST_RESULT6_BIST_FAIL6_5(data)                                              (0x00000040&((data)<<6))
#define BIST_RESULT6_BIST_FAIL6_5_src(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT6_get_BIST_FAIL6_5(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT6_BIST_FAIL6_4_shift                                              (5)
#define BIST_RESULT6_BIST_FAIL6_4_mask                                               (0x00000020)
#define BIST_RESULT6_BIST_FAIL6_4(data)                                              (0x00000020&((data)<<5))
#define BIST_RESULT6_BIST_FAIL6_4_src(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT6_get_BIST_FAIL6_4(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT6_BIST_FAIL6_3_shift                                              (4)
#define BIST_RESULT6_BIST_FAIL6_3_mask                                               (0x00000010)
#define BIST_RESULT6_BIST_FAIL6_3(data)                                              (0x00000010&((data)<<4))
#define BIST_RESULT6_BIST_FAIL6_3_src(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT6_get_BIST_FAIL6_3(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT6_BIST_FAIL6_2_shift                                              (3)
#define BIST_RESULT6_BIST_FAIL6_2_mask                                               (0x00000008)
#define BIST_RESULT6_BIST_FAIL6_2(data)                                              (0x00000008&((data)<<3))
#define BIST_RESULT6_BIST_FAIL6_2_src(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT6_get_BIST_FAIL6_2(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT6_BIST_FAIL6_1_shift                                              (2)
#define BIST_RESULT6_BIST_FAIL6_1_mask                                               (0x00000004)
#define BIST_RESULT6_BIST_FAIL6_1(data)                                              (0x00000004&((data)<<2))
#define BIST_RESULT6_BIST_FAIL6_1_src(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT6_get_BIST_FAIL6_1(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT6_BIST_FAIL6_0_shift                                              (1)
#define BIST_RESULT6_BIST_FAIL6_0_mask                                               (0x00000002)
#define BIST_RESULT6_BIST_FAIL6_0(data)                                              (0x00000002&((data)<<1))
#define BIST_RESULT6_BIST_FAIL6_0_src(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT6_get_BIST_FAIL6_0(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT6_BIST_DONE6_shift                                                (0)
#define BIST_RESULT6_BIST_DONE6_mask                                                 (0x00000001)
#define BIST_RESULT6_BIST_DONE6(data)                                                (0x00000001&((data)<<0))
#define BIST_RESULT6_BIST_DONE6_src(data)                                            ((0x00000001&(data))>>0)
#define BIST_RESULT6_get_BIST_DONE6(data)                                            ((0x00000001&(data))>>0)


#define BIST_RESULT7                                                                 0x18036028
#define BIST_RESULT7_reg_addr                                                        "0xB8036028"
#define BIST_RESULT7_reg                                                             0xB8036028
#define set_BIST_RESULT7_reg(data)   (*((volatile unsigned int*) BIST_RESULT7_reg)=data)
#define get_BIST_RESULT7_reg   (*((volatile unsigned int*) BIST_RESULT7_reg))
#define BIST_RESULT7_inst_adr                                                        "0x000A"
#define BIST_RESULT7_inst                                                            0x000A
#define BIST_RESULT7_DRF_START_PAUSE7_shift                                          (16)
#define BIST_RESULT7_DRF_START_PAUSE7_mask                                           (0x00010000)
#define BIST_RESULT7_DRF_START_PAUSE7(data)                                          (0x00010000&((data)<<16))
#define BIST_RESULT7_DRF_START_PAUSE7_src(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT7_get_DRF_START_PAUSE7(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT7_DRF_BIST_FAIL7_6_shift                                          (15)
#define BIST_RESULT7_DRF_BIST_FAIL7_6_mask                                           (0x00008000)
#define BIST_RESULT7_DRF_BIST_FAIL7_6(data)                                          (0x00008000&((data)<<15))
#define BIST_RESULT7_DRF_BIST_FAIL7_6_src(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT7_get_DRF_BIST_FAIL7_6(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT7_DRF_BIST_FAIL7_5_shift                                          (14)
#define BIST_RESULT7_DRF_BIST_FAIL7_5_mask                                           (0x00004000)
#define BIST_RESULT7_DRF_BIST_FAIL7_5(data)                                          (0x00004000&((data)<<14))
#define BIST_RESULT7_DRF_BIST_FAIL7_5_src(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT7_get_DRF_BIST_FAIL7_5(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT7_DRF_BIST_FAIL7_4_shift                                          (13)
#define BIST_RESULT7_DRF_BIST_FAIL7_4_mask                                           (0x00002000)
#define BIST_RESULT7_DRF_BIST_FAIL7_4(data)                                          (0x00002000&((data)<<13))
#define BIST_RESULT7_DRF_BIST_FAIL7_4_src(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT7_get_DRF_BIST_FAIL7_4(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT7_DRF_BIST_FAIL7_3_shift                                          (12)
#define BIST_RESULT7_DRF_BIST_FAIL7_3_mask                                           (0x00001000)
#define BIST_RESULT7_DRF_BIST_FAIL7_3(data)                                          (0x00001000&((data)<<12))
#define BIST_RESULT7_DRF_BIST_FAIL7_3_src(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT7_get_DRF_BIST_FAIL7_3(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT7_DRF_BIST_FAIL7_2_shift                                          (11)
#define BIST_RESULT7_DRF_BIST_FAIL7_2_mask                                           (0x00000800)
#define BIST_RESULT7_DRF_BIST_FAIL7_2(data)                                          (0x00000800&((data)<<11))
#define BIST_RESULT7_DRF_BIST_FAIL7_2_src(data)                                      ((0x00000800&(data))>>11)
#define BIST_RESULT7_get_DRF_BIST_FAIL7_2(data)                                      ((0x00000800&(data))>>11)
#define BIST_RESULT7_DRF_BIST_FAIL7_1_shift                                          (10)
#define BIST_RESULT7_DRF_BIST_FAIL7_1_mask                                           (0x00000400)
#define BIST_RESULT7_DRF_BIST_FAIL7_1(data)                                          (0x00000400&((data)<<10))
#define BIST_RESULT7_DRF_BIST_FAIL7_1_src(data)                                      ((0x00000400&(data))>>10)
#define BIST_RESULT7_get_DRF_BIST_FAIL7_1(data)                                      ((0x00000400&(data))>>10)
#define BIST_RESULT7_DRF_BIST_FAIL7_0_shift                                          (9)
#define BIST_RESULT7_DRF_BIST_FAIL7_0_mask                                           (0x00000200)
#define BIST_RESULT7_DRF_BIST_FAIL7_0(data)                                          (0x00000200&((data)<<9))
#define BIST_RESULT7_DRF_BIST_FAIL7_0_src(data)                                      ((0x00000200&(data))>>9)
#define BIST_RESULT7_get_DRF_BIST_FAIL7_0(data)                                      ((0x00000200&(data))>>9)
#define BIST_RESULT7_DRF_BIST_DONE7_shift                                            (8)
#define BIST_RESULT7_DRF_BIST_DONE7_mask                                             (0x00000100)
#define BIST_RESULT7_DRF_BIST_DONE7(data)                                            (0x00000100&((data)<<8))
#define BIST_RESULT7_DRF_BIST_DONE7_src(data)                                        ((0x00000100&(data))>>8)
#define BIST_RESULT7_get_DRF_BIST_DONE7(data)                                        ((0x00000100&(data))>>8)
#define BIST_RESULT7_BIST_FAIL7_6_shift                                              (7)
#define BIST_RESULT7_BIST_FAIL7_6_mask                                               (0x00000080)
#define BIST_RESULT7_BIST_FAIL7_6(data)                                              (0x00000080&((data)<<7))
#define BIST_RESULT7_BIST_FAIL7_6_src(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT7_get_BIST_FAIL7_6(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT7_BIST_FAIL7_5_shift                                              (6)
#define BIST_RESULT7_BIST_FAIL7_5_mask                                               (0x00000040)
#define BIST_RESULT7_BIST_FAIL7_5(data)                                              (0x00000040&((data)<<6))
#define BIST_RESULT7_BIST_FAIL7_5_src(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT7_get_BIST_FAIL7_5(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT7_BIST_FAIL7_4_shift                                              (5)
#define BIST_RESULT7_BIST_FAIL7_4_mask                                               (0x00000020)
#define BIST_RESULT7_BIST_FAIL7_4(data)                                              (0x00000020&((data)<<5))
#define BIST_RESULT7_BIST_FAIL7_4_src(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT7_get_BIST_FAIL7_4(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT7_BIST_FAIL7_3_shift                                              (4)
#define BIST_RESULT7_BIST_FAIL7_3_mask                                               (0x00000010)
#define BIST_RESULT7_BIST_FAIL7_3(data)                                              (0x00000010&((data)<<4))
#define BIST_RESULT7_BIST_FAIL7_3_src(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT7_get_BIST_FAIL7_3(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT7_BIST_FAIL7_2_shift                                              (3)
#define BIST_RESULT7_BIST_FAIL7_2_mask                                               (0x00000008)
#define BIST_RESULT7_BIST_FAIL7_2(data)                                              (0x00000008&((data)<<3))
#define BIST_RESULT7_BIST_FAIL7_2_src(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT7_get_BIST_FAIL7_2(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT7_BIST_FAIL7_1_shift                                              (2)
#define BIST_RESULT7_BIST_FAIL7_1_mask                                               (0x00000004)
#define BIST_RESULT7_BIST_FAIL7_1(data)                                              (0x00000004&((data)<<2))
#define BIST_RESULT7_BIST_FAIL7_1_src(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT7_get_BIST_FAIL7_1(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT7_BIST_FAIL7_0_shift                                              (1)
#define BIST_RESULT7_BIST_FAIL7_0_mask                                               (0x00000002)
#define BIST_RESULT7_BIST_FAIL7_0(data)                                              (0x00000002&((data)<<1))
#define BIST_RESULT7_BIST_FAIL7_0_src(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT7_get_BIST_FAIL7_0(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT7_BIST_DONE7_shift                                                (0)
#define BIST_RESULT7_BIST_DONE7_mask                                                 (0x00000001)
#define BIST_RESULT7_BIST_DONE7(data)                                                (0x00000001&((data)<<0))
#define BIST_RESULT7_BIST_DONE7_src(data)                                            ((0x00000001&(data))>>0)
#define BIST_RESULT7_get_BIST_DONE7(data)                                            ((0x00000001&(data))>>0)


#define BIST_RESULT8                                                                 0x1803602C
#define BIST_RESULT8_reg_addr                                                        "0xB803602C"
#define BIST_RESULT8_reg                                                             0xB803602C
#define set_BIST_RESULT8_reg(data)   (*((volatile unsigned int*) BIST_RESULT8_reg)=data)
#define get_BIST_RESULT8_reg   (*((volatile unsigned int*) BIST_RESULT8_reg))
#define BIST_RESULT8_inst_adr                                                        "0x000B"
#define BIST_RESULT8_inst                                                            0x000B
#define BIST_RESULT8_DRF_START_PAUSE8_shift                                          (16)
#define BIST_RESULT8_DRF_START_PAUSE8_mask                                           (0x00010000)
#define BIST_RESULT8_DRF_START_PAUSE8(data)                                          (0x00010000&((data)<<16))
#define BIST_RESULT8_DRF_START_PAUSE8_src(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT8_get_DRF_START_PAUSE8(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT8_DRF_BIST_FAIL8_6_shift                                          (15)
#define BIST_RESULT8_DRF_BIST_FAIL8_6_mask                                           (0x00008000)
#define BIST_RESULT8_DRF_BIST_FAIL8_6(data)                                          (0x00008000&((data)<<15))
#define BIST_RESULT8_DRF_BIST_FAIL8_6_src(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT8_get_DRF_BIST_FAIL8_6(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT8_DRF_BIST_FAIL8_5_shift                                          (14)
#define BIST_RESULT8_DRF_BIST_FAIL8_5_mask                                           (0x00004000)
#define BIST_RESULT8_DRF_BIST_FAIL8_5(data)                                          (0x00004000&((data)<<14))
#define BIST_RESULT8_DRF_BIST_FAIL8_5_src(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT8_get_DRF_BIST_FAIL8_5(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT8_DRF_BIST_FAIL8_4_shift                                          (13)
#define BIST_RESULT8_DRF_BIST_FAIL8_4_mask                                           (0x00002000)
#define BIST_RESULT8_DRF_BIST_FAIL8_4(data)                                          (0x00002000&((data)<<13))
#define BIST_RESULT8_DRF_BIST_FAIL8_4_src(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT8_get_DRF_BIST_FAIL8_4(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT8_DRF_BIST_FAIL8_3_shift                                          (12)
#define BIST_RESULT8_DRF_BIST_FAIL8_3_mask                                           (0x00001000)
#define BIST_RESULT8_DRF_BIST_FAIL8_3(data)                                          (0x00001000&((data)<<12))
#define BIST_RESULT8_DRF_BIST_FAIL8_3_src(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT8_get_DRF_BIST_FAIL8_3(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT8_DRF_BIST_FAIL8_2_shift                                          (11)
#define BIST_RESULT8_DRF_BIST_FAIL8_2_mask                                           (0x00000800)
#define BIST_RESULT8_DRF_BIST_FAIL8_2(data)                                          (0x00000800&((data)<<11))
#define BIST_RESULT8_DRF_BIST_FAIL8_2_src(data)                                      ((0x00000800&(data))>>11)
#define BIST_RESULT8_get_DRF_BIST_FAIL8_2(data)                                      ((0x00000800&(data))>>11)
#define BIST_RESULT8_DRF_BIST_FAIL8_1_shift                                          (10)
#define BIST_RESULT8_DRF_BIST_FAIL8_1_mask                                           (0x00000400)
#define BIST_RESULT8_DRF_BIST_FAIL8_1(data)                                          (0x00000400&((data)<<10))
#define BIST_RESULT8_DRF_BIST_FAIL8_1_src(data)                                      ((0x00000400&(data))>>10)
#define BIST_RESULT8_get_DRF_BIST_FAIL8_1(data)                                      ((0x00000400&(data))>>10)
#define BIST_RESULT8_DRF_BIST_FAIL8_0_shift                                          (9)
#define BIST_RESULT8_DRF_BIST_FAIL8_0_mask                                           (0x00000200)
#define BIST_RESULT8_DRF_BIST_FAIL8_0(data)                                          (0x00000200&((data)<<9))
#define BIST_RESULT8_DRF_BIST_FAIL8_0_src(data)                                      ((0x00000200&(data))>>9)
#define BIST_RESULT8_get_DRF_BIST_FAIL8_0(data)                                      ((0x00000200&(data))>>9)
#define BIST_RESULT8_DRF_BIST_DONE8_shift                                            (8)
#define BIST_RESULT8_DRF_BIST_DONE8_mask                                             (0x00000100)
#define BIST_RESULT8_DRF_BIST_DONE8(data)                                            (0x00000100&((data)<<8))
#define BIST_RESULT8_DRF_BIST_DONE8_src(data)                                        ((0x00000100&(data))>>8)
#define BIST_RESULT8_get_DRF_BIST_DONE8(data)                                        ((0x00000100&(data))>>8)
#define BIST_RESULT8_BIST_FAIL8_6_shift                                              (7)
#define BIST_RESULT8_BIST_FAIL8_6_mask                                               (0x00000080)
#define BIST_RESULT8_BIST_FAIL8_6(data)                                              (0x00000080&((data)<<7))
#define BIST_RESULT8_BIST_FAIL8_6_src(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT8_get_BIST_FAIL8_6(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT8_BIST_FAIL8_5_shift                                              (6)
#define BIST_RESULT8_BIST_FAIL8_5_mask                                               (0x00000040)
#define BIST_RESULT8_BIST_FAIL8_5(data)                                              (0x00000040&((data)<<6))
#define BIST_RESULT8_BIST_FAIL8_5_src(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT8_get_BIST_FAIL8_5(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT8_BIST_FAIL8_4_shift                                              (5)
#define BIST_RESULT8_BIST_FAIL8_4_mask                                               (0x00000020)
#define BIST_RESULT8_BIST_FAIL8_4(data)                                              (0x00000020&((data)<<5))
#define BIST_RESULT8_BIST_FAIL8_4_src(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT8_get_BIST_FAIL8_4(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT8_BIST_FAIL8_3_shift                                              (4)
#define BIST_RESULT8_BIST_FAIL8_3_mask                                               (0x00000010)
#define BIST_RESULT8_BIST_FAIL8_3(data)                                              (0x00000010&((data)<<4))
#define BIST_RESULT8_BIST_FAIL8_3_src(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT8_get_BIST_FAIL8_3(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT8_BIST_FAIL8_2_shift                                              (3)
#define BIST_RESULT8_BIST_FAIL8_2_mask                                               (0x00000008)
#define BIST_RESULT8_BIST_FAIL8_2(data)                                              (0x00000008&((data)<<3))
#define BIST_RESULT8_BIST_FAIL8_2_src(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT8_get_BIST_FAIL8_2(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT8_BIST_FAIL8_1_shift                                              (2)
#define BIST_RESULT8_BIST_FAIL8_1_mask                                               (0x00000004)
#define BIST_RESULT8_BIST_FAIL8_1(data)                                              (0x00000004&((data)<<2))
#define BIST_RESULT8_BIST_FAIL8_1_src(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT8_get_BIST_FAIL8_1(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT8_BIST_FAIL8_0_shift                                              (1)
#define BIST_RESULT8_BIST_FAIL8_0_mask                                               (0x00000002)
#define BIST_RESULT8_BIST_FAIL8_0(data)                                              (0x00000002&((data)<<1))
#define BIST_RESULT8_BIST_FAIL8_0_src(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT8_get_BIST_FAIL8_0(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT8_BIST_DONE8_shift                                                (0)
#define BIST_RESULT8_BIST_DONE8_mask                                                 (0x00000001)
#define BIST_RESULT8_BIST_DONE8(data)                                                (0x00000001&((data)<<0))
#define BIST_RESULT8_BIST_DONE8_src(data)                                            ((0x00000001&(data))>>0)
#define BIST_RESULT8_get_BIST_DONE8(data)                                            ((0x00000001&(data))>>0)


#define BIST_RESULT9                                                                 0x18036030
#define BIST_RESULT9_reg_addr                                                        "0xB8036030"
#define BIST_RESULT9_reg                                                             0xB8036030
#define set_BIST_RESULT9_reg(data)   (*((volatile unsigned int*) BIST_RESULT9_reg)=data)
#define get_BIST_RESULT9_reg   (*((volatile unsigned int*) BIST_RESULT9_reg))
#define BIST_RESULT9_inst_adr                                                        "0x000C"
#define BIST_RESULT9_inst                                                            0x000C
#define BIST_RESULT9_DRF_START_PAUSE9_shift                                          (16)
#define BIST_RESULT9_DRF_START_PAUSE9_mask                                           (0x00010000)
#define BIST_RESULT9_DRF_START_PAUSE9(data)                                          (0x00010000&((data)<<16))
#define BIST_RESULT9_DRF_START_PAUSE9_src(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT9_get_DRF_START_PAUSE9(data)                                      ((0x00010000&(data))>>16)
#define BIST_RESULT9_DRF_BIST_FAIL9_6_shift                                          (15)
#define BIST_RESULT9_DRF_BIST_FAIL9_6_mask                                           (0x00008000)
#define BIST_RESULT9_DRF_BIST_FAIL9_6(data)                                          (0x00008000&((data)<<15))
#define BIST_RESULT9_DRF_BIST_FAIL9_6_src(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT9_get_DRF_BIST_FAIL9_6(data)                                      ((0x00008000&(data))>>15)
#define BIST_RESULT9_DRF_BIST_FAIL9_5_shift                                          (14)
#define BIST_RESULT9_DRF_BIST_FAIL9_5_mask                                           (0x00004000)
#define BIST_RESULT9_DRF_BIST_FAIL9_5(data)                                          (0x00004000&((data)<<14))
#define BIST_RESULT9_DRF_BIST_FAIL9_5_src(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT9_get_DRF_BIST_FAIL9_5(data)                                      ((0x00004000&(data))>>14)
#define BIST_RESULT9_DRF_BIST_FAIL9_4_shift                                          (13)
#define BIST_RESULT9_DRF_BIST_FAIL9_4_mask                                           (0x00002000)
#define BIST_RESULT9_DRF_BIST_FAIL9_4(data)                                          (0x00002000&((data)<<13))
#define BIST_RESULT9_DRF_BIST_FAIL9_4_src(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT9_get_DRF_BIST_FAIL9_4(data)                                      ((0x00002000&(data))>>13)
#define BIST_RESULT9_DRF_BIST_FAIL9_3_shift                                          (12)
#define BIST_RESULT9_DRF_BIST_FAIL9_3_mask                                           (0x00001000)
#define BIST_RESULT9_DRF_BIST_FAIL9_3(data)                                          (0x00001000&((data)<<12))
#define BIST_RESULT9_DRF_BIST_FAIL9_3_src(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT9_get_DRF_BIST_FAIL9_3(data)                                      ((0x00001000&(data))>>12)
#define BIST_RESULT9_DRF_BIST_FAIL9_2_shift                                          (11)
#define BIST_RESULT9_DRF_BIST_FAIL9_2_mask                                           (0x00000800)
#define BIST_RESULT9_DRF_BIST_FAIL9_2(data)                                          (0x00000800&((data)<<11))
#define BIST_RESULT9_DRF_BIST_FAIL9_2_src(data)                                      ((0x00000800&(data))>>11)
#define BIST_RESULT9_get_DRF_BIST_FAIL9_2(data)                                      ((0x00000800&(data))>>11)
#define BIST_RESULT9_DRF_BIST_FAIL9_1_shift                                          (10)
#define BIST_RESULT9_DRF_BIST_FAIL9_1_mask                                           (0x00000400)
#define BIST_RESULT9_DRF_BIST_FAIL9_1(data)                                          (0x00000400&((data)<<10))
#define BIST_RESULT9_DRF_BIST_FAIL9_1_src(data)                                      ((0x00000400&(data))>>10)
#define BIST_RESULT9_get_DRF_BIST_FAIL9_1(data)                                      ((0x00000400&(data))>>10)
#define BIST_RESULT9_DRF_BIST_FAIL9_0_shift                                          (9)
#define BIST_RESULT9_DRF_BIST_FAIL9_0_mask                                           (0x00000200)
#define BIST_RESULT9_DRF_BIST_FAIL9_0(data)                                          (0x00000200&((data)<<9))
#define BIST_RESULT9_DRF_BIST_FAIL9_0_src(data)                                      ((0x00000200&(data))>>9)
#define BIST_RESULT9_get_DRF_BIST_FAIL9_0(data)                                      ((0x00000200&(data))>>9)
#define BIST_RESULT9_DRF_BIST_DONE9_shift                                            (8)
#define BIST_RESULT9_DRF_BIST_DONE9_mask                                             (0x00000100)
#define BIST_RESULT9_DRF_BIST_DONE9(data)                                            (0x00000100&((data)<<8))
#define BIST_RESULT9_DRF_BIST_DONE9_src(data)                                        ((0x00000100&(data))>>8)
#define BIST_RESULT9_get_DRF_BIST_DONE9(data)                                        ((0x00000100&(data))>>8)
#define BIST_RESULT9_BIST_FAIL9_6_shift                                              (7)
#define BIST_RESULT9_BIST_FAIL9_6_mask                                               (0x00000080)
#define BIST_RESULT9_BIST_FAIL9_6(data)                                              (0x00000080&((data)<<7))
#define BIST_RESULT9_BIST_FAIL9_6_src(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT9_get_BIST_FAIL9_6(data)                                          ((0x00000080&(data))>>7)
#define BIST_RESULT9_BIST_FAIL9_5_shift                                              (6)
#define BIST_RESULT9_BIST_FAIL9_5_mask                                               (0x00000040)
#define BIST_RESULT9_BIST_FAIL9_5(data)                                              (0x00000040&((data)<<6))
#define BIST_RESULT9_BIST_FAIL9_5_src(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT9_get_BIST_FAIL9_5(data)                                          ((0x00000040&(data))>>6)
#define BIST_RESULT9_BIST_FAIL9_4_shift                                              (5)
#define BIST_RESULT9_BIST_FAIL9_4_mask                                               (0x00000020)
#define BIST_RESULT9_BIST_FAIL9_4(data)                                              (0x00000020&((data)<<5))
#define BIST_RESULT9_BIST_FAIL9_4_src(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT9_get_BIST_FAIL9_4(data)                                          ((0x00000020&(data))>>5)
#define BIST_RESULT9_BIST_FAIL9_3_shift                                              (4)
#define BIST_RESULT9_BIST_FAIL9_3_mask                                               (0x00000010)
#define BIST_RESULT9_BIST_FAIL9_3(data)                                              (0x00000010&((data)<<4))
#define BIST_RESULT9_BIST_FAIL9_3_src(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT9_get_BIST_FAIL9_3(data)                                          ((0x00000010&(data))>>4)
#define BIST_RESULT9_BIST_FAIL9_2_shift                                              (3)
#define BIST_RESULT9_BIST_FAIL9_2_mask                                               (0x00000008)
#define BIST_RESULT9_BIST_FAIL9_2(data)                                              (0x00000008&((data)<<3))
#define BIST_RESULT9_BIST_FAIL9_2_src(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT9_get_BIST_FAIL9_2(data)                                          ((0x00000008&(data))>>3)
#define BIST_RESULT9_BIST_FAIL9_1_shift                                              (2)
#define BIST_RESULT9_BIST_FAIL9_1_mask                                               (0x00000004)
#define BIST_RESULT9_BIST_FAIL9_1(data)                                              (0x00000004&((data)<<2))
#define BIST_RESULT9_BIST_FAIL9_1_src(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT9_get_BIST_FAIL9_1(data)                                          ((0x00000004&(data))>>2)
#define BIST_RESULT9_BIST_FAIL9_0_shift                                              (1)
#define BIST_RESULT9_BIST_FAIL9_0_mask                                               (0x00000002)
#define BIST_RESULT9_BIST_FAIL9_0(data)                                              (0x00000002&((data)<<1))
#define BIST_RESULT9_BIST_FAIL9_0_src(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT9_get_BIST_FAIL9_0(data)                                          ((0x00000002&(data))>>1)
#define BIST_RESULT9_BIST_DONE9_shift                                                (0)
#define BIST_RESULT9_BIST_DONE9_mask                                                 (0x00000001)
#define BIST_RESULT9_BIST_DONE9(data)                                                (0x00000001&((data)<<0))
#define BIST_RESULT9_BIST_DONE9_src(data)                                            ((0x00000001&(data))>>0)
#define BIST_RESULT9_get_BIST_DONE9(data)                                            ((0x00000001&(data))>>0)


#define BIST_RESULT10                                                                0x18036034
#define BIST_RESULT10_reg_addr                                                       "0xB8036034"
#define BIST_RESULT10_reg                                                            0xB8036034
#define set_BIST_RESULT10_reg(data)   (*((volatile unsigned int*) BIST_RESULT10_reg)=data)
#define get_BIST_RESULT10_reg   (*((volatile unsigned int*) BIST_RESULT10_reg))
#define BIST_RESULT10_inst_adr                                                       "0x000D"
#define BIST_RESULT10_inst                                                           0x000D
#define BIST_RESULT10_DRF_START_PAUSE10_shift                                        (18)
#define BIST_RESULT10_DRF_START_PAUSE10_mask                                         (0x00040000)
#define BIST_RESULT10_DRF_START_PAUSE10(data)                                        (0x00040000&((data)<<18))
#define BIST_RESULT10_DRF_START_PAUSE10_src(data)                                    ((0x00040000&(data))>>18)
#define BIST_RESULT10_get_DRF_START_PAUSE10(data)                                    ((0x00040000&(data))>>18)
#define BIST_RESULT10_DRF_BIST_FAIL10_7_shift                                        (17)
#define BIST_RESULT10_DRF_BIST_FAIL10_7_mask                                         (0x00020000)
#define BIST_RESULT10_DRF_BIST_FAIL10_7(data)                                        (0x00020000&((data)<<17))
#define BIST_RESULT10_DRF_BIST_FAIL10_7_src(data)                                    ((0x00020000&(data))>>17)
#define BIST_RESULT10_get_DRF_BIST_FAIL10_7(data)                                    ((0x00020000&(data))>>17)
#define BIST_RESULT10_DRF_BIST_FAIL10_6_shift                                        (16)
#define BIST_RESULT10_DRF_BIST_FAIL10_6_mask                                         (0x00010000)
#define BIST_RESULT10_DRF_BIST_FAIL10_6(data)                                        (0x00010000&((data)<<16))
#define BIST_RESULT10_DRF_BIST_FAIL10_6_src(data)                                    ((0x00010000&(data))>>16)
#define BIST_RESULT10_get_DRF_BIST_FAIL10_6(data)                                    ((0x00010000&(data))>>16)
#define BIST_RESULT10_DRF_BIST_FAIL10_5_shift                                        (15)
#define BIST_RESULT10_DRF_BIST_FAIL10_5_mask                                         (0x00008000)
#define BIST_RESULT10_DRF_BIST_FAIL10_5(data)                                        (0x00008000&((data)<<15))
#define BIST_RESULT10_DRF_BIST_FAIL10_5_src(data)                                    ((0x00008000&(data))>>15)
#define BIST_RESULT10_get_DRF_BIST_FAIL10_5(data)                                    ((0x00008000&(data))>>15)
#define BIST_RESULT10_DRF_BIST_FAIL10_4_shift                                        (14)
#define BIST_RESULT10_DRF_BIST_FAIL10_4_mask                                         (0x00004000)
#define BIST_RESULT10_DRF_BIST_FAIL10_4(data)                                        (0x00004000&((data)<<14))
#define BIST_RESULT10_DRF_BIST_FAIL10_4_src(data)                                    ((0x00004000&(data))>>14)
#define BIST_RESULT10_get_DRF_BIST_FAIL10_4(data)                                    ((0x00004000&(data))>>14)
#define BIST_RESULT10_DRF_BIST_FAIL10_3_shift                                        (13)
#define BIST_RESULT10_DRF_BIST_FAIL10_3_mask                                         (0x00002000)
#define BIST_RESULT10_DRF_BIST_FAIL10_3(data)                                        (0x00002000&((data)<<13))
#define BIST_RESULT10_DRF_BIST_FAIL10_3_src(data)                                    ((0x00002000&(data))>>13)
#define BIST_RESULT10_get_DRF_BIST_FAIL10_3(data)                                    ((0x00002000&(data))>>13)
#define BIST_RESULT10_DRF_BIST_FAIL10_2_shift                                        (12)
#define BIST_RESULT10_DRF_BIST_FAIL10_2_mask                                         (0x00001000)
#define BIST_RESULT10_DRF_BIST_FAIL10_2(data)                                        (0x00001000&((data)<<12))
#define BIST_RESULT10_DRF_BIST_FAIL10_2_src(data)                                    ((0x00001000&(data))>>12)
#define BIST_RESULT10_get_DRF_BIST_FAIL10_2(data)                                    ((0x00001000&(data))>>12)
#define BIST_RESULT10_DRF_BIST_FAIL10_1_shift                                        (11)
#define BIST_RESULT10_DRF_BIST_FAIL10_1_mask                                         (0x00000800)
#define BIST_RESULT10_DRF_BIST_FAIL10_1(data)                                        (0x00000800&((data)<<11))
#define BIST_RESULT10_DRF_BIST_FAIL10_1_src(data)                                    ((0x00000800&(data))>>11)
#define BIST_RESULT10_get_DRF_BIST_FAIL10_1(data)                                    ((0x00000800&(data))>>11)
#define BIST_RESULT10_DRF_BIST_FAIL10_0_shift                                        (10)
#define BIST_RESULT10_DRF_BIST_FAIL10_0_mask                                         (0x00000400)
#define BIST_RESULT10_DRF_BIST_FAIL10_0(data)                                        (0x00000400&((data)<<10))
#define BIST_RESULT10_DRF_BIST_FAIL10_0_src(data)                                    ((0x00000400&(data))>>10)
#define BIST_RESULT10_get_DRF_BIST_FAIL10_0(data)                                    ((0x00000400&(data))>>10)
#define BIST_RESULT10_DRF_BIST_DONE10_shift                                          (9)
#define BIST_RESULT10_DRF_BIST_DONE10_mask                                           (0x00000200)
#define BIST_RESULT10_DRF_BIST_DONE10(data)                                          (0x00000200&((data)<<9))
#define BIST_RESULT10_DRF_BIST_DONE10_src(data)                                      ((0x00000200&(data))>>9)
#define BIST_RESULT10_get_DRF_BIST_DONE10(data)                                      ((0x00000200&(data))>>9)
#define BIST_RESULT10_BIST_FAIL10_7_shift                                            (8)
#define BIST_RESULT10_BIST_FAIL10_7_mask                                             (0x00000100)
#define BIST_RESULT10_BIST_FAIL10_7(data)                                            (0x00000100&((data)<<8))
#define BIST_RESULT10_BIST_FAIL10_7_src(data)                                        ((0x00000100&(data))>>8)
#define BIST_RESULT10_get_BIST_FAIL10_7(data)                                        ((0x00000100&(data))>>8)
#define BIST_RESULT10_BIST_FAIL10_6_shift                                            (7)
#define BIST_RESULT10_BIST_FAIL10_6_mask                                             (0x00000080)
#define BIST_RESULT10_BIST_FAIL10_6(data)                                            (0x00000080&((data)<<7))
#define BIST_RESULT10_BIST_FAIL10_6_src(data)                                        ((0x00000080&(data))>>7)
#define BIST_RESULT10_get_BIST_FAIL10_6(data)                                        ((0x00000080&(data))>>7)
#define BIST_RESULT10_BIST_FAIL10_5_shift                                            (6)
#define BIST_RESULT10_BIST_FAIL10_5_mask                                             (0x00000040)
#define BIST_RESULT10_BIST_FAIL10_5(data)                                            (0x00000040&((data)<<6))
#define BIST_RESULT10_BIST_FAIL10_5_src(data)                                        ((0x00000040&(data))>>6)
#define BIST_RESULT10_get_BIST_FAIL10_5(data)                                        ((0x00000040&(data))>>6)
#define BIST_RESULT10_BIST_FAIL10_4_shift                                            (5)
#define BIST_RESULT10_BIST_FAIL10_4_mask                                             (0x00000020)
#define BIST_RESULT10_BIST_FAIL10_4(data)                                            (0x00000020&((data)<<5))
#define BIST_RESULT10_BIST_FAIL10_4_src(data)                                        ((0x00000020&(data))>>5)
#define BIST_RESULT10_get_BIST_FAIL10_4(data)                                        ((0x00000020&(data))>>5)
#define BIST_RESULT10_BIST_FAIL10_3_shift                                            (4)
#define BIST_RESULT10_BIST_FAIL10_3_mask                                             (0x00000010)
#define BIST_RESULT10_BIST_FAIL10_3(data)                                            (0x00000010&((data)<<4))
#define BIST_RESULT10_BIST_FAIL10_3_src(data)                                        ((0x00000010&(data))>>4)
#define BIST_RESULT10_get_BIST_FAIL10_3(data)                                        ((0x00000010&(data))>>4)
#define BIST_RESULT10_BIST_FAIL10_2_shift                                            (3)
#define BIST_RESULT10_BIST_FAIL10_2_mask                                             (0x00000008)
#define BIST_RESULT10_BIST_FAIL10_2(data)                                            (0x00000008&((data)<<3))
#define BIST_RESULT10_BIST_FAIL10_2_src(data)                                        ((0x00000008&(data))>>3)
#define BIST_RESULT10_get_BIST_FAIL10_2(data)                                        ((0x00000008&(data))>>3)
#define BIST_RESULT10_BIST_FAIL10_1_shift                                            (2)
#define BIST_RESULT10_BIST_FAIL10_1_mask                                             (0x00000004)
#define BIST_RESULT10_BIST_FAIL10_1(data)                                            (0x00000004&((data)<<2))
#define BIST_RESULT10_BIST_FAIL10_1_src(data)                                        ((0x00000004&(data))>>2)
#define BIST_RESULT10_get_BIST_FAIL10_1(data)                                        ((0x00000004&(data))>>2)
#define BIST_RESULT10_BIST_FAIL10_0_shift                                            (1)
#define BIST_RESULT10_BIST_FAIL10_0_mask                                             (0x00000002)
#define BIST_RESULT10_BIST_FAIL10_0(data)                                            (0x00000002&((data)<<1))
#define BIST_RESULT10_BIST_FAIL10_0_src(data)                                        ((0x00000002&(data))>>1)
#define BIST_RESULT10_get_BIST_FAIL10_0(data)                                        ((0x00000002&(data))>>1)
#define BIST_RESULT10_BIST_DONE10_shift                                              (0)
#define BIST_RESULT10_BIST_DONE10_mask                                               (0x00000001)
#define BIST_RESULT10_BIST_DONE10(data)                                              (0x00000001&((data)<<0))
#define BIST_RESULT10_BIST_DONE10_src(data)                                          ((0x00000001&(data))>>0)
#define BIST_RESULT10_get_BIST_DONE10(data)                                          ((0x00000001&(data))>>0)


#define BIST_RESULT11                                                                0x18036038
#define BIST_RESULT11_reg_addr                                                       "0xB8036038"
#define BIST_RESULT11_reg                                                            0xB8036038
#define set_BIST_RESULT11_reg(data)   (*((volatile unsigned int*) BIST_RESULT11_reg)=data)
#define get_BIST_RESULT11_reg   (*((volatile unsigned int*) BIST_RESULT11_reg))
#define BIST_RESULT11_inst_adr                                                       "0x000E"
#define BIST_RESULT11_inst                                                           0x000E
#define BIST_RESULT11_DRF_START_PAUSE11_shift                                        (10)
#define BIST_RESULT11_DRF_START_PAUSE11_mask                                         (0x00000400)
#define BIST_RESULT11_DRF_START_PAUSE11(data)                                        (0x00000400&((data)<<10))
#define BIST_RESULT11_DRF_START_PAUSE11_src(data)                                    ((0x00000400&(data))>>10)
#define BIST_RESULT11_get_DRF_START_PAUSE11(data)                                    ((0x00000400&(data))>>10)
#define BIST_RESULT11_DRF_BIST_FAIL11_3_shift                                        (9)
#define BIST_RESULT11_DRF_BIST_FAIL11_3_mask                                         (0x00000200)
#define BIST_RESULT11_DRF_BIST_FAIL11_3(data)                                        (0x00000200&((data)<<9))
#define BIST_RESULT11_DRF_BIST_FAIL11_3_src(data)                                    ((0x00000200&(data))>>9)
#define BIST_RESULT11_get_DRF_BIST_FAIL11_3(data)                                    ((0x00000200&(data))>>9)
#define BIST_RESULT11_DRF_BIST_FAIL11_2_shift                                        (8)
#define BIST_RESULT11_DRF_BIST_FAIL11_2_mask                                         (0x00000100)
#define BIST_RESULT11_DRF_BIST_FAIL11_2(data)                                        (0x00000100&((data)<<8))
#define BIST_RESULT11_DRF_BIST_FAIL11_2_src(data)                                    ((0x00000100&(data))>>8)
#define BIST_RESULT11_get_DRF_BIST_FAIL11_2(data)                                    ((0x00000100&(data))>>8)
#define BIST_RESULT11_DRF_BIST_FAIL11_1_shift                                        (7)
#define BIST_RESULT11_DRF_BIST_FAIL11_1_mask                                         (0x00000080)
#define BIST_RESULT11_DRF_BIST_FAIL11_1(data)                                        (0x00000080&((data)<<7))
#define BIST_RESULT11_DRF_BIST_FAIL11_1_src(data)                                    ((0x00000080&(data))>>7)
#define BIST_RESULT11_get_DRF_BIST_FAIL11_1(data)                                    ((0x00000080&(data))>>7)
#define BIST_RESULT11_DRF_BIST_FAIL11_0_shift                                        (6)
#define BIST_RESULT11_DRF_BIST_FAIL11_0_mask                                         (0x00000040)
#define BIST_RESULT11_DRF_BIST_FAIL11_0(data)                                        (0x00000040&((data)<<6))
#define BIST_RESULT11_DRF_BIST_FAIL11_0_src(data)                                    ((0x00000040&(data))>>6)
#define BIST_RESULT11_get_DRF_BIST_FAIL11_0(data)                                    ((0x00000040&(data))>>6)
#define BIST_RESULT11_DRF_BIST_DONE11_shift                                          (5)
#define BIST_RESULT11_DRF_BIST_DONE11_mask                                           (0x00000020)
#define BIST_RESULT11_DRF_BIST_DONE11(data)                                          (0x00000020&((data)<<5))
#define BIST_RESULT11_DRF_BIST_DONE11_src(data)                                      ((0x00000020&(data))>>5)
#define BIST_RESULT11_get_DRF_BIST_DONE11(data)                                      ((0x00000020&(data))>>5)
#define BIST_RESULT11_BIST_FAIL11_3_shift                                            (4)
#define BIST_RESULT11_BIST_FAIL11_3_mask                                             (0x00000010)
#define BIST_RESULT11_BIST_FAIL11_3(data)                                            (0x00000010&((data)<<4))
#define BIST_RESULT11_BIST_FAIL11_3_src(data)                                        ((0x00000010&(data))>>4)
#define BIST_RESULT11_get_BIST_FAIL11_3(data)                                        ((0x00000010&(data))>>4)
#define BIST_RESULT11_BIST_FAIL11_2_shift                                            (3)
#define BIST_RESULT11_BIST_FAIL11_2_mask                                             (0x00000008)
#define BIST_RESULT11_BIST_FAIL11_2(data)                                            (0x00000008&((data)<<3))
#define BIST_RESULT11_BIST_FAIL11_2_src(data)                                        ((0x00000008&(data))>>3)
#define BIST_RESULT11_get_BIST_FAIL11_2(data)                                        ((0x00000008&(data))>>3)
#define BIST_RESULT11_BIST_FAIL11_1_shift                                            (2)
#define BIST_RESULT11_BIST_FAIL11_1_mask                                             (0x00000004)
#define BIST_RESULT11_BIST_FAIL11_1(data)                                            (0x00000004&((data)<<2))
#define BIST_RESULT11_BIST_FAIL11_1_src(data)                                        ((0x00000004&(data))>>2)
#define BIST_RESULT11_get_BIST_FAIL11_1(data)                                        ((0x00000004&(data))>>2)
#define BIST_RESULT11_BIST_FAIL11_0_shift                                            (1)
#define BIST_RESULT11_BIST_FAIL11_0_mask                                             (0x00000002)
#define BIST_RESULT11_BIST_FAIL11_0(data)                                            (0x00000002&((data)<<1))
#define BIST_RESULT11_BIST_FAIL11_0_src(data)                                        ((0x00000002&(data))>>1)
#define BIST_RESULT11_get_BIST_FAIL11_0(data)                                        ((0x00000002&(data))>>1)
#define BIST_RESULT11_BIST_DONE11_shift                                              (0)
#define BIST_RESULT11_BIST_DONE11_mask                                               (0x00000001)
#define BIST_RESULT11_BIST_DONE11(data)                                              (0x00000001&((data)<<0))
#define BIST_RESULT11_BIST_DONE11_src(data)                                          ((0x00000001&(data))>>0)
#define BIST_RESULT11_get_BIST_DONE11(data)                                          ((0x00000001&(data))>>0)


#define BIST_RESULT12                                                                0x1803603C
#define BIST_RESULT12_reg_addr                                                       "0xB803603C"
#define BIST_RESULT12_reg                                                            0xB803603C
#define set_BIST_RESULT12_reg(data)   (*((volatile unsigned int*) BIST_RESULT12_reg)=data)
#define get_BIST_RESULT12_reg   (*((volatile unsigned int*) BIST_RESULT12_reg))
#define BIST_RESULT12_inst_adr                                                       "0x000F"
#define BIST_RESULT12_inst                                                           0x000F
#define BIST_RESULT12_DRF_START_PAUSE12_shift                                        (6)
#define BIST_RESULT12_DRF_START_PAUSE12_mask                                         (0x00000040)
#define BIST_RESULT12_DRF_START_PAUSE12(data)                                        (0x00000040&((data)<<6))
#define BIST_RESULT12_DRF_START_PAUSE12_src(data)                                    ((0x00000040&(data))>>6)
#define BIST_RESULT12_get_DRF_START_PAUSE12(data)                                    ((0x00000040&(data))>>6)
#define BIST_RESULT12_DRF_BIST_FAIL12_1_shift                                        (5)
#define BIST_RESULT12_DRF_BIST_FAIL12_1_mask                                         (0x00000020)
#define BIST_RESULT12_DRF_BIST_FAIL12_1(data)                                        (0x00000020&((data)<<5))
#define BIST_RESULT12_DRF_BIST_FAIL12_1_src(data)                                    ((0x00000020&(data))>>5)
#define BIST_RESULT12_get_DRF_BIST_FAIL12_1(data)                                    ((0x00000020&(data))>>5)
#define BIST_RESULT12_DRF_BIST_FAIL12_0_shift                                        (4)
#define BIST_RESULT12_DRF_BIST_FAIL12_0_mask                                         (0x00000010)
#define BIST_RESULT12_DRF_BIST_FAIL12_0(data)                                        (0x00000010&((data)<<4))
#define BIST_RESULT12_DRF_BIST_FAIL12_0_src(data)                                    ((0x00000010&(data))>>4)
#define BIST_RESULT12_get_DRF_BIST_FAIL12_0(data)                                    ((0x00000010&(data))>>4)
#define BIST_RESULT12_DRF_BIST_DONE12_shift                                          (3)
#define BIST_RESULT12_DRF_BIST_DONE12_mask                                           (0x00000008)
#define BIST_RESULT12_DRF_BIST_DONE12(data)                                          (0x00000008&((data)<<3))
#define BIST_RESULT12_DRF_BIST_DONE12_src(data)                                      ((0x00000008&(data))>>3)
#define BIST_RESULT12_get_DRF_BIST_DONE12(data)                                      ((0x00000008&(data))>>3)
#define BIST_RESULT12_BIST_FAIL12_1_shift                                            (2)
#define BIST_RESULT12_BIST_FAIL12_1_mask                                             (0x00000004)
#define BIST_RESULT12_BIST_FAIL12_1(data)                                            (0x00000004&((data)<<2))
#define BIST_RESULT12_BIST_FAIL12_1_src(data)                                        ((0x00000004&(data))>>2)
#define BIST_RESULT12_get_BIST_FAIL12_1(data)                                        ((0x00000004&(data))>>2)
#define BIST_RESULT12_BIST_FAIL12_0_shift                                            (1)
#define BIST_RESULT12_BIST_FAIL12_0_mask                                             (0x00000002)
#define BIST_RESULT12_BIST_FAIL12_0(data)                                            (0x00000002&((data)<<1))
#define BIST_RESULT12_BIST_FAIL12_0_src(data)                                        ((0x00000002&(data))>>1)
#define BIST_RESULT12_get_BIST_FAIL12_0(data)                                        ((0x00000002&(data))>>1)
#define BIST_RESULT12_BIST_DONE12_shift                                              (0)
#define BIST_RESULT12_BIST_DONE12_mask                                               (0x00000001)
#define BIST_RESULT12_BIST_DONE12(data)                                              (0x00000001&((data)<<0))
#define BIST_RESULT12_BIST_DONE12_src(data)                                          ((0x00000001&(data))>>0)
#define BIST_RESULT12_get_BIST_DONE12(data)                                          ((0x00000001&(data))>>0)


#define BIST_RESULT13                                                                0x18036040
#define BIST_RESULT13_reg_addr                                                       "0xB8036040"
#define BIST_RESULT13_reg                                                            0xB8036040
#define set_BIST_RESULT13_reg(data)   (*((volatile unsigned int*) BIST_RESULT13_reg)=data)
#define get_BIST_RESULT13_reg   (*((volatile unsigned int*) BIST_RESULT13_reg))
#define BIST_RESULT13_inst_adr                                                       "0x0010"
#define BIST_RESULT13_inst                                                           0x0010
#define BIST_RESULT13_DRF_START_PAUSE13_shift                                        (4)
#define BIST_RESULT13_DRF_START_PAUSE13_mask                                         (0x00000010)
#define BIST_RESULT13_DRF_START_PAUSE13(data)                                        (0x00000010&((data)<<4))
#define BIST_RESULT13_DRF_START_PAUSE13_src(data)                                    ((0x00000010&(data))>>4)
#define BIST_RESULT13_get_DRF_START_PAUSE13(data)                                    ((0x00000010&(data))>>4)
#define BIST_RESULT13_DRF_BIST_FAIL13_0_shift                                        (3)
#define BIST_RESULT13_DRF_BIST_FAIL13_0_mask                                         (0x00000008)
#define BIST_RESULT13_DRF_BIST_FAIL13_0(data)                                        (0x00000008&((data)<<3))
#define BIST_RESULT13_DRF_BIST_FAIL13_0_src(data)                                    ((0x00000008&(data))>>3)
#define BIST_RESULT13_get_DRF_BIST_FAIL13_0(data)                                    ((0x00000008&(data))>>3)
#define BIST_RESULT13_DRF_BIST_DONE13_shift                                          (2)
#define BIST_RESULT13_DRF_BIST_DONE13_mask                                           (0x00000004)
#define BIST_RESULT13_DRF_BIST_DONE13(data)                                          (0x00000004&((data)<<2))
#define BIST_RESULT13_DRF_BIST_DONE13_src(data)                                      ((0x00000004&(data))>>2)
#define BIST_RESULT13_get_DRF_BIST_DONE13(data)                                      ((0x00000004&(data))>>2)
#define BIST_RESULT13_BIST_FAIL13_0_shift                                            (1)
#define BIST_RESULT13_BIST_FAIL13_0_mask                                             (0x00000002)
#define BIST_RESULT13_BIST_FAIL13_0(data)                                            (0x00000002&((data)<<1))
#define BIST_RESULT13_BIST_FAIL13_0_src(data)                                        ((0x00000002&(data))>>1)
#define BIST_RESULT13_get_BIST_FAIL13_0(data)                                        ((0x00000002&(data))>>1)
#define BIST_RESULT13_BIST_DONE13_shift                                              (0)
#define BIST_RESULT13_BIST_DONE13_mask                                               (0x00000001)
#define BIST_RESULT13_BIST_DONE13(data)                                              (0x00000001&((data)<<0))
#define BIST_RESULT13_BIST_DONE13_src(data)                                          ((0x00000001&(data))>>0)
#define BIST_RESULT13_get_BIST_DONE13(data)                                          ((0x00000001&(data))>>0)


#define BIST_RESULT13                                                                0x18036044
#define BIST_RESULT13_reg_addr                                                       "0xB8036044"
#define BIST_RESULT13_reg                                                            0xB8036044
#define set_BIST_RESULT13_reg(data)   (*((volatile unsigned int*) BIST_RESULT13_reg)=data)
#define get_BIST_RESULT13_reg   (*((volatile unsigned int*) BIST_RESULT13_reg))
#define BIST_RESULT13_inst_adr                                                       "0x0011"
#define BIST_RESULT13_inst                                                           0x0011
#define BIST_RESULT13_sram_rm_shift                                                  (1)
#define BIST_RESULT13_sram_rm_mask                                                   (0x0000001E)
#define BIST_RESULT13_sram_rm(data)                                                  (0x0000001E&((data)<<1))
#define BIST_RESULT13_sram_rm_src(data)                                              ((0x0000001E&(data))>>1)
#define BIST_RESULT13_get_sram_rm(data)                                              ((0x0000001E&(data))>>1)
#define BIST_RESULT13_sram_rme_shift                                                 (0)
#define BIST_RESULT13_sram_rme_mask                                                  (0x00000001)
#define BIST_RESULT13_sram_rme(data)                                                 (0x00000001&((data)<<0))
#define BIST_RESULT13_sram_rme_src(data)                                             ((0x00000001&(data))>>0)
#define BIST_RESULT13_get_sram_rme(data)                                             ((0x00000001&(data))>>0)


#define DEBUGPORTS                                                                   0x18036048
#define DEBUGPORTS_reg_addr                                                          "0xB8036048"
#define DEBUGPORTS_reg                                                               0xB8036048
#define set_DEBUGPORTS_reg(data)   (*((volatile unsigned int*) DEBUGPORTS_reg)=data)
#define get_DEBUGPORTS_reg   (*((volatile unsigned int*) DEBUGPORTS_reg))
#define DEBUGPORTS_inst_adr                                                          "0x0012"
#define DEBUGPORTS_inst                                                              0x0012
#define DEBUGPORTS_dbg_sel_shift                                                     (8)
#define DEBUGPORTS_dbg_sel_mask                                                      (0x00000100)
#define DEBUGPORTS_dbg_sel(data)                                                     (0x00000100&((data)<<8))
#define DEBUGPORTS_dbg_sel_src(data)                                                 ((0x00000100&(data))>>8)
#define DEBUGPORTS_get_dbg_sel(data)                                                 ((0x00000100&(data))>>8)
#define DEBUGPORTS_dbg_sel1_shift                                                    (4)
#define DEBUGPORTS_dbg_sel1_mask                                                     (0x000000F0)
#define DEBUGPORTS_dbg_sel1(data)                                                    (0x000000F0&((data)<<4))
#define DEBUGPORTS_dbg_sel1_src(data)                                                ((0x000000F0&(data))>>4)
#define DEBUGPORTS_get_dbg_sel1(data)                                                ((0x000000F0&(data))>>4)
#define DEBUGPORTS_dbg_sel0_shift                                                    (0)
#define DEBUGPORTS_dbg_sel0_mask                                                     (0x0000000F)
#define DEBUGPORTS_dbg_sel0(data)                                                    (0x0000000F&((data)<<0))
#define DEBUGPORTS_dbg_sel0_src(data)                                                ((0x0000000F&(data))>>0)
#define DEBUGPORTS_get_dbg_sel0(data)                                                ((0x0000000F&(data))>>0)


#define DUMMYREGISTERS0                                                              0x1803604C
#define DUMMYREGISTERS0_reg_addr                                                     "0xB803604C"
#define DUMMYREGISTERS0_reg                                                          0xB803604C
#define set_DUMMYREGISTERS0_reg(data)   (*((volatile unsigned int*) DUMMYREGISTERS0_reg)=data)
#define get_DUMMYREGISTERS0_reg   (*((volatile unsigned int*) DUMMYREGISTERS0_reg))
#define DUMMYREGISTERS0_inst_adr                                                     "0x0013"
#define DUMMYREGISTERS0_inst                                                         0x0013
#define DUMMYREGISTERS0_dummy_reg0_shift                                             (0)
#define DUMMYREGISTERS0_dummy_reg0_mask                                              (0xFFFFFFFF)
#define DUMMYREGISTERS0_dummy_reg0(data)                                             (0xFFFFFFFF&((data)<<0))
#define DUMMYREGISTERS0_dummy_reg0_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define DUMMYREGISTERS0_get_dummy_reg0(data)                                         ((0xFFFFFFFF&(data))>>0)


#define DUMMYREGISTERS1                                                              0x18036050
#define DUMMYREGISTERS1_reg_addr                                                     "0xB8036050"
#define DUMMYREGISTERS1_reg                                                          0xB8036050
#define set_DUMMYREGISTERS1_reg(data)   (*((volatile unsigned int*) DUMMYREGISTERS1_reg)=data)
#define get_DUMMYREGISTERS1_reg   (*((volatile unsigned int*) DUMMYREGISTERS1_reg))
#define DUMMYREGISTERS1_inst_adr                                                     "0x0014"
#define DUMMYREGISTERS1_inst                                                         0x0014
#define DUMMYREGISTERS1_dummy_reg1_shift                                             (0)
#define DUMMYREGISTERS1_dummy_reg1_mask                                              (0xFFFFFFFF)
#define DUMMYREGISTERS1_dummy_reg1(data)                                             (0xFFFFFFFF&((data)<<0))
#define DUMMYREGISTERS1_dummy_reg1_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define DUMMYREGISTERS1_get_dummy_reg1(data)                                         ((0xFFFFFFFF&(data))>>0)


#define DSS_C35_9D5T_CTRL                                                            0x18036054
#define DSS_C35_9D5T_CTRL_reg_addr                                                   "0xB8036054"
#define DSS_C35_9D5T_CTRL_reg                                                        0xB8036054
#define set_DSS_C35_9D5T_CTRL_reg(data)   (*((volatile unsigned int*) DSS_C35_9D5T_CTRL_reg)=data)
#define get_DSS_C35_9D5T_CTRL_reg   (*((volatile unsigned int*) DSS_C35_9D5T_CTRL_reg))
#define DSS_C35_9D5T_CTRL_inst_adr                                                   "0x0015"
#define DSS_C35_9D5T_CTRL_inst                                                       0x0015
#define DSS_C35_9D5T_CTRL_c35_data_in_shift                                          (8)
#define DSS_C35_9D5T_CTRL_c35_data_in_mask                                           (0x0FFFFF00)
#define DSS_C35_9D5T_CTRL_c35_data_in(data)                                          (0x0FFFFF00&((data)<<8))
#define DSS_C35_9D5T_CTRL_c35_data_in_src(data)                                      ((0x0FFFFF00&(data))>>8)
#define DSS_C35_9D5T_CTRL_get_c35_data_in(data)                                      ((0x0FFFFF00&(data))>>8)
#define DSS_C35_9D5T_CTRL_c35_speed_en_shift                                         (5)
#define DSS_C35_9D5T_CTRL_c35_speed_en_mask                                          (0x00000020)
#define DSS_C35_9D5T_CTRL_c35_speed_en(data)                                         (0x00000020&((data)<<5))
#define DSS_C35_9D5T_CTRL_c35_speed_en_src(data)                                     ((0x00000020&(data))>>5)
#define DSS_C35_9D5T_CTRL_get_c35_speed_en(data)                                     ((0x00000020&(data))>>5)
#define DSS_C35_9D5T_CTRL_c35_wire_sel_shift                                         (4)
#define DSS_C35_9D5T_CTRL_c35_wire_sel_mask                                          (0x00000010)
#define DSS_C35_9D5T_CTRL_c35_wire_sel(data)                                         (0x00000010&((data)<<4))
#define DSS_C35_9D5T_CTRL_c35_wire_sel_src(data)                                     ((0x00000010&(data))>>4)
#define DSS_C35_9D5T_CTRL_get_c35_wire_sel(data)                                     ((0x00000010&(data))>>4)
#define DSS_C35_9D5T_CTRL_c35_ro_sel_shift                                           (1)
#define DSS_C35_9D5T_CTRL_c35_ro_sel_mask                                            (0x0000000E)
#define DSS_C35_9D5T_CTRL_c35_ro_sel(data)                                           (0x0000000E&((data)<<1))
#define DSS_C35_9D5T_CTRL_c35_ro_sel_src(data)                                       ((0x0000000E&(data))>>1)
#define DSS_C35_9D5T_CTRL_get_c35_ro_sel(data)                                       ((0x0000000E&(data))>>1)
#define DSS_C35_9D5T_CTRL_c35_dss_rst_n_shift                                        (0)
#define DSS_C35_9D5T_CTRL_c35_dss_rst_n_mask                                         (0x00000001)
#define DSS_C35_9D5T_CTRL_c35_dss_rst_n(data)                                        (0x00000001&((data)<<0))
#define DSS_C35_9D5T_CTRL_c35_dss_rst_n_src(data)                                    ((0x00000001&(data))>>0)
#define DSS_C35_9D5T_CTRL_get_c35_dss_rst_n(data)                                    ((0x00000001&(data))>>0)


#define DSS_C35_9D5T_STATUS                                                          0x18036058
#define DSS_C35_9D5T_STATUS_reg_addr                                                 "0xB8036058"
#define DSS_C35_9D5T_STATUS_reg                                                      0xB8036058
#define set_DSS_C35_9D5T_STATUS_reg(data)   (*((volatile unsigned int*) DSS_C35_9D5T_STATUS_reg)=data)
#define get_DSS_C35_9D5T_STATUS_reg   (*((volatile unsigned int*) DSS_C35_9D5T_STATUS_reg))
#define DSS_C35_9D5T_STATUS_inst_adr                                                 "0x0016"
#define DSS_C35_9D5T_STATUS_inst                                                     0x0016
#define DSS_C35_9D5T_STATUS_c35_count_out_shift                                      (4)
#define DSS_C35_9D5T_STATUS_c35_count_out_mask                                       (0x00FFFFF0)
#define DSS_C35_9D5T_STATUS_c35_count_out(data)                                      (0x00FFFFF0&((data)<<4))
#define DSS_C35_9D5T_STATUS_c35_count_out_src(data)                                  ((0x00FFFFF0&(data))>>4)
#define DSS_C35_9D5T_STATUS_get_c35_count_out(data)                                  ((0x00FFFFF0&(data))>>4)
#define DSS_C35_9D5T_STATUS_c35_wsort_go_shift                                       (1)
#define DSS_C35_9D5T_STATUS_c35_wsort_go_mask                                        (0x00000002)
#define DSS_C35_9D5T_STATUS_c35_wsort_go(data)                                       (0x00000002&((data)<<1))
#define DSS_C35_9D5T_STATUS_c35_wsort_go_src(data)                                   ((0x00000002&(data))>>1)
#define DSS_C35_9D5T_STATUS_get_c35_wsort_go(data)                                   ((0x00000002&(data))>>1)
#define DSS_C35_9D5T_STATUS_c35_ready_shift                                          (0)
#define DSS_C35_9D5T_STATUS_c35_ready_mask                                           (0x00000001)
#define DSS_C35_9D5T_STATUS_c35_ready(data)                                          (0x00000001&((data)<<0))
#define DSS_C35_9D5T_STATUS_c35_ready_src(data)                                      ((0x00000001&(data))>>0)
#define DSS_C35_9D5T_STATUS_get_c35_ready(data)                                      ((0x00000001&(data))>>0)


#define DSS_C35_9D5T_DEBUG                                                           0x1803605C
#define DSS_C35_9D5T_DEBUG_reg_addr                                                  "0xB803605C"
#define DSS_C35_9D5T_DEBUG_reg                                                       0xB803605C
#define set_DSS_C35_9D5T_DEBUG_reg(data)   (*((volatile unsigned int*) DSS_C35_9D5T_DEBUG_reg)=data)
#define get_DSS_C35_9D5T_DEBUG_reg   (*((volatile unsigned int*) DSS_C35_9D5T_DEBUG_reg))
#define DSS_C35_9D5T_DEBUG_inst_adr                                                  "0x0017"
#define DSS_C35_9D5T_DEBUG_inst                                                      0x0017
#define DSS_C35_9D5T_DEBUG_c35_dbgo_shift                                            (0)
#define DSS_C35_9D5T_DEBUG_c35_dbgo_mask                                             (0x0000FFFF)
#define DSS_C35_9D5T_DEBUG_c35_dbgo(data)                                            (0x0000FFFF&((data)<<0))
#define DSS_C35_9D5T_DEBUG_c35_dbgo_src(data)                                        ((0x0000FFFF&(data))>>0)
#define DSS_C35_9D5T_DEBUG_get_c35_dbgo(data)                                        ((0x0000FFFF&(data))>>0)


#define DSS_C35D5_9D5T_CTRL                                                          0x18036060
#define DSS_C35D5_9D5T_CTRL_reg_addr                                                 "0xB8036060"
#define DSS_C35D5_9D5T_CTRL_reg                                                      0xB8036060
#define set_DSS_C35D5_9D5T_CTRL_reg(data)   (*((volatile unsigned int*) DSS_C35D5_9D5T_CTRL_reg)=data)
#define get_DSS_C35D5_9D5T_CTRL_reg   (*((volatile unsigned int*) DSS_C35D5_9D5T_CTRL_reg))
#define DSS_C35D5_9D5T_CTRL_inst_adr                                                 "0x0018"
#define DSS_C35D5_9D5T_CTRL_inst                                                     0x0018
#define DSS_C35D5_9D5T_CTRL_c35d5_data_in_shift                                      (8)
#define DSS_C35D5_9D5T_CTRL_c35d5_data_in_mask                                       (0x0FFFFF00)
#define DSS_C35D5_9D5T_CTRL_c35d5_data_in(data)                                      (0x0FFFFF00&((data)<<8))
#define DSS_C35D5_9D5T_CTRL_c35d5_data_in_src(data)                                  ((0x0FFFFF00&(data))>>8)
#define DSS_C35D5_9D5T_CTRL_get_c35d5_data_in(data)                                  ((0x0FFFFF00&(data))>>8)
#define DSS_C35D5_9D5T_CTRL_c35d5_speed_en_shift                                     (5)
#define DSS_C35D5_9D5T_CTRL_c35d5_speed_en_mask                                      (0x00000020)
#define DSS_C35D5_9D5T_CTRL_c35d5_speed_en(data)                                     (0x00000020&((data)<<5))
#define DSS_C35D5_9D5T_CTRL_c35d5_speed_en_src(data)                                 ((0x00000020&(data))>>5)
#define DSS_C35D5_9D5T_CTRL_get_c35d5_speed_en(data)                                 ((0x00000020&(data))>>5)
#define DSS_C35D5_9D5T_CTRL_c35d5_wire_sel_shift                                     (4)
#define DSS_C35D5_9D5T_CTRL_c35d5_wire_sel_mask                                      (0x00000010)
#define DSS_C35D5_9D5T_CTRL_c35d5_wire_sel(data)                                     (0x00000010&((data)<<4))
#define DSS_C35D5_9D5T_CTRL_c35d5_wire_sel_src(data)                                 ((0x00000010&(data))>>4)
#define DSS_C35D5_9D5T_CTRL_get_c35d5_wire_sel(data)                                 ((0x00000010&(data))>>4)
#define DSS_C35D5_9D5T_CTRL_c35d5_ro_sel_shift                                       (1)
#define DSS_C35D5_9D5T_CTRL_c35d5_ro_sel_mask                                        (0x0000000E)
#define DSS_C35D5_9D5T_CTRL_c35d5_ro_sel(data)                                       (0x0000000E&((data)<<1))
#define DSS_C35D5_9D5T_CTRL_c35d5_ro_sel_src(data)                                   ((0x0000000E&(data))>>1)
#define DSS_C35D5_9D5T_CTRL_get_c35d5_ro_sel(data)                                   ((0x0000000E&(data))>>1)
#define DSS_C35D5_9D5T_CTRL_c35d5_dss_rst_n_shift                                    (0)
#define DSS_C35D5_9D5T_CTRL_c35d5_dss_rst_n_mask                                     (0x00000001)
#define DSS_C35D5_9D5T_CTRL_c35d5_dss_rst_n(data)                                    (0x00000001&((data)<<0))
#define DSS_C35D5_9D5T_CTRL_c35d5_dss_rst_n_src(data)                                ((0x00000001&(data))>>0)
#define DSS_C35D5_9D5T_CTRL_get_c35d5_dss_rst_n(data)                                ((0x00000001&(data))>>0)


#define DSS_C35D5_9D5T_STATUS                                                        0x18036064
#define DSS_C35D5_9D5T_STATUS_reg_addr                                               "0xB8036064"
#define DSS_C35D5_9D5T_STATUS_reg                                                    0xB8036064
#define set_DSS_C35D5_9D5T_STATUS_reg(data)   (*((volatile unsigned int*) DSS_C35D5_9D5T_STATUS_reg)=data)
#define get_DSS_C35D5_9D5T_STATUS_reg   (*((volatile unsigned int*) DSS_C35D5_9D5T_STATUS_reg))
#define DSS_C35D5_9D5T_STATUS_inst_adr                                               "0x0019"
#define DSS_C35D5_9D5T_STATUS_inst                                                   0x0019
#define DSS_C35D5_9D5T_STATUS_c35d5_count_out_shift                                  (4)
#define DSS_C35D5_9D5T_STATUS_c35d5_count_out_mask                                   (0x00FFFFF0)
#define DSS_C35D5_9D5T_STATUS_c35d5_count_out(data)                                  (0x00FFFFF0&((data)<<4))
#define DSS_C35D5_9D5T_STATUS_c35d5_count_out_src(data)                              ((0x00FFFFF0&(data))>>4)
#define DSS_C35D5_9D5T_STATUS_get_c35d5_count_out(data)                              ((0x00FFFFF0&(data))>>4)
#define DSS_C35D5_9D5T_STATUS_c35d5_wsort_go_shift                                   (1)
#define DSS_C35D5_9D5T_STATUS_c35d5_wsort_go_mask                                    (0x00000002)
#define DSS_C35D5_9D5T_STATUS_c35d5_wsort_go(data)                                   (0x00000002&((data)<<1))
#define DSS_C35D5_9D5T_STATUS_c35d5_wsort_go_src(data)                               ((0x00000002&(data))>>1)
#define DSS_C35D5_9D5T_STATUS_get_c35d5_wsort_go(data)                               ((0x00000002&(data))>>1)
#define DSS_C35D5_9D5T_STATUS_c35d5_ready_shift                                      (0)
#define DSS_C35D5_9D5T_STATUS_c35d5_ready_mask                                       (0x00000001)
#define DSS_C35D5_9D5T_STATUS_c35d5_ready(data)                                      (0x00000001&((data)<<0))
#define DSS_C35D5_9D5T_STATUS_c35d5_ready_src(data)                                  ((0x00000001&(data))>>0)
#define DSS_C35D5_9D5T_STATUS_get_c35d5_ready(data)                                  ((0x00000001&(data))>>0)


#define DSS_C35D5_9D5T_DEBUG                                                         0x18036068
#define DSS_C35D5_9D5T_DEBUG_reg_addr                                                "0xB8036068"
#define DSS_C35D5_9D5T_DEBUG_reg                                                     0xB8036068
#define set_DSS_C35D5_9D5T_DEBUG_reg(data)   (*((volatile unsigned int*) DSS_C35D5_9D5T_DEBUG_reg)=data)
#define get_DSS_C35D5_9D5T_DEBUG_reg   (*((volatile unsigned int*) DSS_C35D5_9D5T_DEBUG_reg))
#define DSS_C35D5_9D5T_DEBUG_inst_adr                                                "0x001A"
#define DSS_C35D5_9D5T_DEBUG_inst                                                    0x001A
#define DSS_C35D5_9D5T_DEBUG_c35d5_dbgo_shift                                        (0)
#define DSS_C35D5_9D5T_DEBUG_c35d5_dbgo_mask                                         (0x0000FFFF)
#define DSS_C35D5_9D5T_DEBUG_c35d5_dbgo(data)                                        (0x0000FFFF&((data)<<0))
#define DSS_C35D5_9D5T_DEBUG_c35d5_dbgo_src(data)                                    ((0x0000FFFF&(data))>>0)
#define DSS_C35D5_9D5T_DEBUG_get_c35d5_dbgo(data)                                    ((0x0000FFFF&(data))>>0)


#endif
