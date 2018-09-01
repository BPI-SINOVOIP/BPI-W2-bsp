// This file is generated using the spec version 0.9, firmware template version 1.38and DVR_Parser_0.3
#ifndef _SP_REG_H_INCLUDED_
#define _SP_REG_H_INCLUDED_

//#define  _SP_USE_STRUCT
#ifdef _SP_USE_STRUCT

typedef struct
{
    unsigned int    reserved_0:28;
    unsigned int    m3_run:1;
    unsigned int    m3_sel:4;
    unsigned int    reserved_1:3;
    unsigned int    m2_run:1;
    unsigned int    m2_sel:4;
    unsigned int    reserved_2:3;
    unsigned int    m1_run:1;
    unsigned int    m1_sel:4;
    unsigned int    reserved_3:3;
    unsigned int    m0_run:1;
    unsigned int    m0_sel:4;
}sp_PM_CNTL;

typedef struct
{
    unsigned int    cnt_lo:32;
}sp_PM_CNT_LO;

typedef struct
{
    unsigned int    reserved_0:0;
    unsigned int    cnt_hi:16;
}sp_PM_CNT_HI;
#endif

#define SP_PM_CNTL                                                    0x18003000
#define SP_PM_CNTL_reg_addr                                           "0xB8003000"
#define SP_PM_CNTL_reg                                                0xB8003000
#define SP_PM_CNTL_inst_addr                                          "0x0000"
#define SP_PM_CNTL_inst                                               0x0000
#define SP_PM_CNTL_m3_run_shift                                       (28)
#define SP_PM_CNTL_m3_sel_shift                                       (24)
#define SP_PM_CNTL_m2_run_shift                                       (20)
#define SP_PM_CNTL_m2_sel_shift                                       (16)
#define SP_PM_CNTL_m1_run_shift                                       (12)
#define SP_PM_CNTL_m1_sel_shift                                       (8)
#define SP_PM_CNTL_m0_run_shift                                       (4)
#define SP_PM_CNTL_m0_sel_shift                                       (0)
#define SP_PM_CNTL_m3_run_mask                                        (0x10000000)
#define SP_PM_CNTL_m3_sel_mask                                        (0x0F000000)
#define SP_PM_CNTL_m2_run_mask                                        (0x00100000)
#define SP_PM_CNTL_m2_sel_mask                                        (0x000F0000)
#define SP_PM_CNTL_m1_run_mask                                        (0x00001000)
#define SP_PM_CNTL_m1_sel_mask                                        (0x00000F00)
#define SP_PM_CNTL_m0_run_mask                                        (0x00000010)
#define SP_PM_CNTL_m0_sel_mask                                        (0x0000000F)
#define SP_PM_CNTL_m3_run(data)                                       (0x10000000&((data)<<28))
#define SP_PM_CNTL_m3_sel(data)                                       (0x0F000000&((data)<<24))
#define SP_PM_CNTL_m2_run(data)                                       (0x00100000&((data)<<20))
#define SP_PM_CNTL_m2_sel(data)                                       (0x000F0000&((data)<<16))
#define SP_PM_CNTL_m1_run(data)                                       (0x00001000&((data)<<12))
#define SP_PM_CNTL_m1_sel(data)                                       (0x00000F00&((data)<<8))
#define SP_PM_CNTL_m0_run(data)                                       (0x00000010&((data)<<4))
#define SP_PM_CNTL_m0_sel(data)                                       (0x0000000F&(data))
#define SP_PM_CNTL_get_m3_run(data)                                   ((0x10000000&(data))>>28)
#define SP_PM_CNTL_get_m3_sel(data)                                   ((0x0F000000&(data))>>24)
#define SP_PM_CNTL_get_m2_run(data)                                   ((0x00100000&(data))>>20)
#define SP_PM_CNTL_get_m2_sel(data)                                   ((0x000F0000&(data))>>16)
#define SP_PM_CNTL_get_m1_run(data)                                   ((0x00001000&(data))>>12)
#define SP_PM_CNTL_get_m1_sel(data)                                   ((0x00000F00&(data))>>8)
#define SP_PM_CNTL_get_m0_run(data)                                   ((0x00000010&(data))>>4)
#define SP_PM_CNTL_get_m0_sel(data)                                   (0x0000000F&(data))

#define SP_PM_CNT_LO_0                                                0x18003008
#define SP_PM_CNT_LO_1                                                0x18003010
#define SP_PM_CNT_LO_2                                                0x18003018
#define SP_PM_CNT_LO_3                                                0x18003020
#define SP_PM_CNT_LO_0_reg_addr                                       "0xB8003008"
#define SP_PM_CNT_LO_1_reg_addr                                       "0xB8003010"
#define SP_PM_CNT_LO_2_reg_addr                                       "0xB8003018"
#define SP_PM_CNT_LO_3_reg_addr                                       "0xB8003020"
#define SP_PM_CNT_LO_0_reg                                            0xB8003008
#define SP_PM_CNT_LO_1_reg                                            0xB8003010
#define SP_PM_CNT_LO_2_reg                                            0xB8003018
#define SP_PM_CNT_LO_3_reg                                            0xB8003020
#define SP_PM_CNT_LO_0_inst_addr                                      "0x0002"
#define SP_PM_CNT_LO_0_inst                                           0x0002
#define SP_PM_CNT_LO_1_inst_addr                                      "0x0004"
#define SP_PM_CNT_LO_1_inst                                           0x0004
#define SP_PM_CNT_LO_2_inst_addr                                      "0x0006"
#define SP_PM_CNT_LO_2_inst                                           0x0006
#define SP_PM_CNT_LO_3_inst_addr                                      "0x0008"
#define SP_PM_CNT_LO_3_inst                                           0x0008
#define SP_PM_CNT_LO_cnt_lo_shift                                     (0)
#define SP_PM_CNT_LO_cnt_lo_mask                                      (0xFFFFFFFF)
#define SP_PM_CNT_LO_cnt_lo(data)                                     (0xFFFFFFFF&(data))
#define SP_PM_CNT_LO_get_cnt_lo(data)                                 (0xFFFFFFFF&(data))

#define SP_PM_CNT_HI_0                                                0x1800300C
#define SP_PM_CNT_HI_1                                                0x18003014
#define SP_PM_CNT_HI_2                                                0x1800301C
#define SP_PM_CNT_HI_3                                                0x18003024
#define SP_PM_CNT_HI_0_reg_addr                                       "0xB800300C"
#define SP_PM_CNT_HI_1_reg_addr                                       "0xB8003014"
#define SP_PM_CNT_HI_2_reg_addr                                       "0xB800301C"
#define SP_PM_CNT_HI_3_reg_addr                                       "0xB8003024"
#define SP_PM_CNT_HI_0_reg                                            0xB800300C
#define SP_PM_CNT_HI_1_reg                                            0xB8003014
#define SP_PM_CNT_HI_2_reg                                            0xB800301C
#define SP_PM_CNT_HI_3_reg                                            0xB8003024
#define SP_PM_CNT_HI_0_inst_addr                                      "0x0003"
#define SP_PM_CNT_HI_0_inst                                           0x0003
#define SP_PM_CNT_HI_1_inst_addr                                      "0x0005"
#define SP_PM_CNT_HI_1_inst                                           0x0005
#define SP_PM_CNT_HI_2_inst_addr                                      "0x0007"
#define SP_PM_CNT_HI_2_inst                                           0x0007
#define SP_PM_CNT_HI_3_inst_addr                                      "0x0009"
#define SP_PM_CNT_HI_3_inst                                           0x0009
#define SP_PM_CNT_HI_cnt_hi_shift                                     (0)
#define SP_PM_CNT_HI_cnt_hi_mask                                      (0x0000FFFF)
#define SP_PM_CNT_HI_cnt_hi(data)                                     (0x0000FFFF&(data))
#define SP_PM_CNT_HI_get_cnt_hi(data)                                 (0x0000FFFF&(data))
#endif
