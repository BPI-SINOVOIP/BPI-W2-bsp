/**************************************************************
// Spec Version                  : 0.3
// Parser Version                : DVR_Parser_6.8(110516)
// CModelGen Version             : 5.0 2009.04.09
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2011/12/23 11:59:49
***************************************************************/


#ifndef _SE_REG_H_INCLUDED_
#define _SE_REG_H_INCLUDED_
#ifdef  _SE_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     base:27;
unsigned int     reserved_1:4;
}SE_CMDBASE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     limit:27;
unsigned int     reserved_1:4;
}SE_CMDLMT;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     rptr:27;
unsigned int     reserved_1:4;
}SE_CMDRPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     wptr:27;
unsigned int     reserved_1:4;
}SE_CMDWPTR;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     srwordcnt:7;
}SE_SRWORDCNT;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     Pri3:2;
unsigned int     Pri2:2;
unsigned int     Pri1:2;
}SE_Q_PRIORITY;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     write_enable10:1;
unsigned int     rounding_en:1;
unsigned int     write_enable8:1;
unsigned int     big_endian_o:1;
unsigned int     write_enable7:1;
unsigned int     big_endian_i2:1;
unsigned int     write_enable6:1;
unsigned int     big_endian_i1:1;
unsigned int     write_enable5:1;
unsigned int     alpha_loc2:1;
unsigned int     reserved_1:6;
unsigned int     write_enable2:1;
unsigned int     alpha_loc:1;
unsigned int     write_enable1:1;
unsigned int     Format:4;
}SE_CLR_FMT;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     color_key:24;
}SE_COLOR_KEY;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     dst_color_key:24;
}SE_DST_COLOR_KEY;

typedef struct 
{
unsigned int     src_color:32;
}SE_SRC_COLOR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     src_alpha:8;
}SE_SRC_ALPHA;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dest_alpha:8;
}SE_DEST_ALPHA;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rslt_alpha:8;
}SE_RSLT_ALPHA;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     baddr:31;
}SE_BADDR1;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     interleave:1;
unsigned int     pitch:16;
}SE_PITCH1;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     baddr:31;
}SE_BADDR2;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     interleave:1;
unsigned int     pitch:16;
}SE_PITCH2;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     baddr:31;
}SE_BADDR3;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     interleave:1;
unsigned int     pitch:16;
}SE_PITCH3;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     clipen:1;
unsigned int     xmin:12;
unsigned int     xmax:12;
}SE_CLIP_XCOOR1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     ymin:12;
unsigned int     ymax:12;
}SE_CLIP_YCOOR1;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     clipen:1;
unsigned int     xmin:12;
unsigned int     xmax:12;
}SE_CLIP_XCOOR2;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     ymin:12;
unsigned int     ymax:12;
}SE_CLIP_YCOOR2;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     clipen:1;
unsigned int     xmin:12;
unsigned int     xmax:12;
}SE_CLIP_XCOOR3;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     ymin:12;
unsigned int     ymax:12;
}SE_CLIP_YCOOR3;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     clut_lock_st:2;
}SE_CLUT_LOCK_ST;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     hdown:1;
unsigned int     vdown:1;
unsigned int     hup:1;
unsigned int     vup:1;
}SE_CONVSCALING;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     m01:13;
unsigned int     m00:13;
}SE_CONVCOEF1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     m10:13;
unsigned int     m02:13;
}SE_CONVCOEF2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     m12:13;
unsigned int     m11:13;
}SE_CONVCOEF3;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     m21:13;
unsigned int     m20:13;
}SE_CONVCOEF4;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     m22:13;
}SE_CONVCOEF5;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     a2:10;
unsigned int     a1:10;
unsigned int     a0:10;
}SE_CONVCOEF6;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     color_key:24;
}SE_FCV_BITBLIT_COLOR_KEY;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     src_clr_add_red:9;
unsigned int     reserved_1:7;
unsigned int     src_clr_mul_red:9;
}SE_SRC_CLR_RED;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     src_clr_add_green:9;
unsigned int     reserved_1:7;
unsigned int     src_clr_mul_green:9;
}SE_SRC_CLR_GREEN;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     src_clr_add_blue:9;
unsigned int     reserved_1:7;
unsigned int     src_clr_mul_blue:9;
}SE_SRC_CLR_BLUE;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     src_clr_add_alpha:9;
unsigned int     reserved_1:7;
unsigned int     src_clr_mul_alpha:9;
}SE_SRC_CLR_ALPHA;

typedef struct 
{
unsigned int     auto_dir_en:1;
unsigned int     vo_plane:1;
unsigned int     before_vo_cur:1;
unsigned int     after_vo_cur:1;
unsigned int     vbi:1;
unsigned int     vo_osd_plane:1;
unsigned int     reserved_0:14;
unsigned int     margin_VOtoSE:12;
}SE_SYNC_VO_MARGIN;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     VO_current_y:12;
}SE_SYNC_VO_LOCATION;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     repl_alpha:1;
unsigned int     repl_color:1;
unsigned int     ref_alpha:1;
unsigned int     htype:2;
unsigned int     vtype:1;
unsigned int     hodd:1;
unsigned int     vodd:1;
}SE_STRETCH;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     H_scaling_iniph:4;
unsigned int     H_scaling_dph_msb:4;
unsigned int     H_scaling_dph_lsb:14;
}SE_HDHS;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     V_scaling_iniph:4;
unsigned int     V_scaling_dph_msb:4;
unsigned int     V_scaling_dph_lsb:14;
}SE_VDHS;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     hcoef:14;
}SE_HCOEF1;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     hcoef:14;
}SE_HCOEF1_32;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     vcoef:14;
}SE_VCOEF1;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     vcoef:14;
}SE_VCOEF1_16;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     hcoef:14;
}SE_HCOEF2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     hcoef:14;
}SE_HCOEF2_32;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     vcoef:14;
}SE_VCOEF2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     vcoef:14;
}SE_VCOEF2_16;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     hcoef:14;
}SE_HCOEF3;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     hcoef:14;
}SE_HCOEF3_32;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     vcoef:14;
}SE_VCOEF3;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     vcoef:14;
}SE_VCOEF3_16;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     color_key:24;
}SE_SC_BITBLIT_COLOR_KEY;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     endiswap:1;
unsigned int     go:1;
unsigned int     write_data:1;
}SE_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     idle:1;
}SE_IDLE;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     sel3:1;
unsigned int     sel2:1;
unsigned int     sel1:1;
}SE_INTSEL;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     vo_sync_err:1;
unsigned int     fmt_err:1;
unsigned int     reserved_1:12;
unsigned int     com_empty:1;
unsigned int     com_err:1;
unsigned int     sync:1;
unsigned int     write_data:1;
}SE_INTS;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     vo_sync_err:1;
unsigned int     fmt_err:1;
unsigned int     reserved_1:12;
unsigned int     com_empty:1;
unsigned int     com_err:1;
unsigned int     sync:1;
unsigned int     write_data:1;
}SE_INTE;

typedef struct 
{
unsigned int     instcnt_l:32;
}SE_INSTCNT_L;

typedef struct 
{
unsigned int     instcnt_h:32;
}SE_INSTCNT_H;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     radr:8;
}SE_CLUT_RADR;

typedef struct 
{
unsigned int     value:32;
}SE_CLUT_VALUE;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     dbg_en:1;
unsigned int     dbg_module_sel1:4;
unsigned int     dbg_module_sel0:4;
unsigned int     reserved_1:3;
unsigned int     dbg_sel1:5;
unsigned int     reserved_2:3;
unsigned int     dbg_sel0:5;
}SE_DBG;

typedef struct 
{
unsigned int     Reg1:16;
unsigned int     Reg0:16;
}SE_SCTCH;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     Gcra_en:1;
}SE_GCRA_CTRL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Gcra_req_num:24;
}SE_GCRA_REQ_CNT;

typedef struct 
{
unsigned int     Gcra_tim_cnt:32;
}SE_GCRA_TIM_CNT;

typedef struct 
{
unsigned int     Gcra_tim_thr:32;
}SE_GCRA_TIM_THR;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Gcra_req_thr:24;
}SE_GCRA_REQ_THR;

#endif

#define SE_CMDBASE_0                                                                 0x1800C000
#define SE_CMDBASE_1                                                                 0x1800C004
#define SE_CMDBASE_2                                                                 0x1800C008
#define SE_CMDBASE_0_reg_addr                                                        "0xB800C000"
#define SE_CMDBASE_1_reg_addr                                                        "0xB800C004"
#define SE_CMDBASE_2_reg_addr                                                        "0xB800C008"
#define SE_CMDBASE_0_reg                                                             0xB800C000
#define SE_CMDBASE_1_reg                                                             0xB800C004
#define SE_CMDBASE_2_reg                                                             0xB800C008
#define set_SE_CMDBASE_0_reg(data)   (*((volatile unsigned int*) SE_CMDBASE_0_reg)=data)
#define set_SE_CMDBASE_1_reg(data)   (*((volatile unsigned int*) SE_CMDBASE_1_reg)=data)
#define set_SE_CMDBASE_2_reg(data)   (*((volatile unsigned int*) SE_CMDBASE_2_reg)=data)
#define get_SE_CMDBASE_0_reg   (*((volatile unsigned int*) SE_CMDBASE_0_reg))
#define get_SE_CMDBASE_1_reg   (*((volatile unsigned int*) SE_CMDBASE_1_reg))
#define get_SE_CMDBASE_2_reg   (*((volatile unsigned int*) SE_CMDBASE_2_reg))
#define SE_CMDBASE_0_inst_adr                                                        "0x0000"
#define SE_CMDBASE_1_inst_adr                                                        "0x0001"
#define SE_CMDBASE_2_inst_adr                                                        "0x0002"
#define SE_CMDBASE_0_inst                                                            0x0000
#define SE_CMDBASE_1_inst                                                            0x0001
#define SE_CMDBASE_2_inst                                                            0x0002
#define SE_CMDBASE_base_shift                                                        (4)
#define SE_CMDBASE_base_mask                                                         (0x7FFFFFF0)
#define SE_CMDBASE_base(data)                                                        (0x7FFFFFF0&((data)<<4))
#define SE_CMDBASE_base_src(data)                                                    ((0x7FFFFFF0&(data))>>4)
#define SE_CMDBASE_get_base(data)                                                    ((0x7FFFFFF0&(data))>>4)


#define SE_CMDLMT_0                                                                  0x1800C00C
#define SE_CMDLMT_1                                                                  0x1800C010
#define SE_CMDLMT_2                                                                  0x1800C014
#define SE_CMDLMT_0_reg_addr                                                         "0xB800C00C"
#define SE_CMDLMT_1_reg_addr                                                         "0xB800C010"
#define SE_CMDLMT_2_reg_addr                                                         "0xB800C014"
#define SE_CMDLMT_0_reg                                                              0xB800C00C
#define SE_CMDLMT_1_reg                                                              0xB800C010
#define SE_CMDLMT_2_reg                                                              0xB800C014
#define set_SE_CMDLMT_0_reg(data)   (*((volatile unsigned int*) SE_CMDLMT_0_reg)=data)
#define set_SE_CMDLMT_1_reg(data)   (*((volatile unsigned int*) SE_CMDLMT_1_reg)=data)
#define set_SE_CMDLMT_2_reg(data)   (*((volatile unsigned int*) SE_CMDLMT_2_reg)=data)
#define get_SE_CMDLMT_0_reg   (*((volatile unsigned int*) SE_CMDLMT_0_reg))
#define get_SE_CMDLMT_1_reg   (*((volatile unsigned int*) SE_CMDLMT_1_reg))
#define get_SE_CMDLMT_2_reg   (*((volatile unsigned int*) SE_CMDLMT_2_reg))
#define SE_CMDLMT_0_inst_adr                                                         "0x0003"
#define SE_CMDLMT_1_inst_adr                                                         "0x0004"
#define SE_CMDLMT_2_inst_adr                                                         "0x0005"
#define SE_CMDLMT_0_inst                                                             0x0003
#define SE_CMDLMT_1_inst                                                             0x0004
#define SE_CMDLMT_2_inst                                                             0x0005
#define SE_CMDLMT_limit_shift                                                        (4)
#define SE_CMDLMT_limit_mask                                                         (0x7FFFFFF0)
#define SE_CMDLMT_limit(data)                                                        (0x7FFFFFF0&((data)<<4))
#define SE_CMDLMT_limit_src(data)                                                    ((0x7FFFFFF0&(data))>>4)
#define SE_CMDLMT_get_limit(data)                                                    ((0x7FFFFFF0&(data))>>4)


#define SE_CMDRPTR_0                                                                 0x1800C018
#define SE_CMDRPTR_1                                                                 0x1800C01C
#define SE_CMDRPTR_2                                                                 0x1800C020
#define SE_CMDRPTR_0_reg_addr                                                        "0xB800C018"
#define SE_CMDRPTR_1_reg_addr                                                        "0xB800C01C"
#define SE_CMDRPTR_2_reg_addr                                                        "0xB800C020"
#define SE_CMDRPTR_0_reg                                                             0xB800C018
#define SE_CMDRPTR_1_reg                                                             0xB800C01C
#define SE_CMDRPTR_2_reg                                                             0xB800C020
#define set_SE_CMDRPTR_0_reg(data)   (*((volatile unsigned int*) SE_CMDRPTR_0_reg)=data)
#define set_SE_CMDRPTR_1_reg(data)   (*((volatile unsigned int*) SE_CMDRPTR_1_reg)=data)
#define set_SE_CMDRPTR_2_reg(data)   (*((volatile unsigned int*) SE_CMDRPTR_2_reg)=data)
#define get_SE_CMDRPTR_0_reg   (*((volatile unsigned int*) SE_CMDRPTR_0_reg))
#define get_SE_CMDRPTR_1_reg   (*((volatile unsigned int*) SE_CMDRPTR_1_reg))
#define get_SE_CMDRPTR_2_reg   (*((volatile unsigned int*) SE_CMDRPTR_2_reg))
#define SE_CMDRPTR_0_inst_adr                                                        "0x0006"
#define SE_CMDRPTR_1_inst_adr                                                        "0x0007"
#define SE_CMDRPTR_2_inst_adr                                                        "0x0008"
#define SE_CMDRPTR_0_inst                                                            0x0006
#define SE_CMDRPTR_1_inst                                                            0x0007
#define SE_CMDRPTR_2_inst                                                            0x0008
#define SE_CMDRPTR_rptr_shift                                                        (4)
#define SE_CMDRPTR_rptr_mask                                                         (0x7FFFFFF0)
#define SE_CMDRPTR_rptr(data)                                                        (0x7FFFFFF0&((data)<<4))
#define SE_CMDRPTR_rptr_src(data)                                                    ((0x7FFFFFF0&(data))>>4)
#define SE_CMDRPTR_get_rptr(data)                                                    ((0x7FFFFFF0&(data))>>4)


#define SE_CMDWPTR_0                                                                 0x1800C024
#define SE_CMDWPTR_1                                                                 0x1800C028
#define SE_CMDWPTR_2                                                                 0x1800C02C
#define SE_CMDWPTR_0_reg_addr                                                        "0xB800C024"
#define SE_CMDWPTR_1_reg_addr                                                        "0xB800C028"
#define SE_CMDWPTR_2_reg_addr                                                        "0xB800C02C"
#define SE_CMDWPTR_0_reg                                                             0xB800C024
#define SE_CMDWPTR_1_reg                                                             0xB800C028
#define SE_CMDWPTR_2_reg                                                             0xB800C02C
#define set_SE_CMDWPTR_0_reg(data)   (*((volatile unsigned int*) SE_CMDWPTR_0_reg)=data)
#define set_SE_CMDWPTR_1_reg(data)   (*((volatile unsigned int*) SE_CMDWPTR_1_reg)=data)
#define set_SE_CMDWPTR_2_reg(data)   (*((volatile unsigned int*) SE_CMDWPTR_2_reg)=data)
#define get_SE_CMDWPTR_0_reg   (*((volatile unsigned int*) SE_CMDWPTR_0_reg))
#define get_SE_CMDWPTR_1_reg   (*((volatile unsigned int*) SE_CMDWPTR_1_reg))
#define get_SE_CMDWPTR_2_reg   (*((volatile unsigned int*) SE_CMDWPTR_2_reg))
#define SE_CMDWPTR_0_inst_adr                                                        "0x0009"
#define SE_CMDWPTR_1_inst_adr                                                        "0x000A"
#define SE_CMDWPTR_2_inst_adr                                                        "0x000B"
#define SE_CMDWPTR_0_inst                                                            0x0009
#define SE_CMDWPTR_1_inst                                                            0x000A
#define SE_CMDWPTR_2_inst                                                            0x000B
#define SE_CMDWPTR_wptr_shift                                                        (4)
#define SE_CMDWPTR_wptr_mask                                                         (0x7FFFFFF0)
#define SE_CMDWPTR_wptr(data)                                                        (0x7FFFFFF0&((data)<<4))
#define SE_CMDWPTR_wptr_src(data)                                                    ((0x7FFFFFF0&(data))>>4)
#define SE_CMDWPTR_get_wptr(data)                                                    ((0x7FFFFFF0&(data))>>4)


#define SE_SRWORDCNT_0                                                               0x1800C030
#define SE_SRWORDCNT_1                                                               0x1800C034
#define SE_SRWORDCNT_2                                                               0x1800C038
#define SE_SRWORDCNT_0_reg_addr                                                      "0xB800C030"
#define SE_SRWORDCNT_1_reg_addr                                                      "0xB800C034"
#define SE_SRWORDCNT_2_reg_addr                                                      "0xB800C038"
#define SE_SRWORDCNT_0_reg                                                           0xB800C030
#define SE_SRWORDCNT_1_reg                                                           0xB800C034
#define SE_SRWORDCNT_2_reg                                                           0xB800C038
#define set_SE_SRWORDCNT_0_reg(data)   (*((volatile unsigned int*) SE_SRWORDCNT_0_reg)=data)
#define set_SE_SRWORDCNT_1_reg(data)   (*((volatile unsigned int*) SE_SRWORDCNT_1_reg)=data)
#define set_SE_SRWORDCNT_2_reg(data)   (*((volatile unsigned int*) SE_SRWORDCNT_2_reg)=data)
#define get_SE_SRWORDCNT_0_reg   (*((volatile unsigned int*) SE_SRWORDCNT_0_reg))
#define get_SE_SRWORDCNT_1_reg   (*((volatile unsigned int*) SE_SRWORDCNT_1_reg))
#define get_SE_SRWORDCNT_2_reg   (*((volatile unsigned int*) SE_SRWORDCNT_2_reg))
#define SE_SRWORDCNT_0_inst_adr                                                      "0x000C"
#define SE_SRWORDCNT_1_inst_adr                                                      "0x000D"
#define SE_SRWORDCNT_2_inst_adr                                                      "0x000E"
#define SE_SRWORDCNT_0_inst                                                          0x000C
#define SE_SRWORDCNT_1_inst                                                          0x000D
#define SE_SRWORDCNT_2_inst                                                          0x000E
#define SE_SRWORDCNT_srwordcnt_shift                                                 (0)
#define SE_SRWORDCNT_srwordcnt_mask                                                  (0x0000007F)
#define SE_SRWORDCNT_srwordcnt(data)                                                 (0x0000007F&((data)<<0))
#define SE_SRWORDCNT_srwordcnt_src(data)                                             ((0x0000007F&(data))>>0)
#define SE_SRWORDCNT_get_srwordcnt(data)                                             ((0x0000007F&(data))>>0)


#define SE_Q_PRIORITY                                                                0x1800C03C
#define SE_Q_PRIORITY_reg_addr                                                       "0xB800C03C"
#define SE_Q_PRIORITY_reg                                                            0xB800C03C
#define set_SE_Q_PRIORITY_reg(data)   (*((volatile unsigned int*) SE_Q_PRIORITY_reg)=data)
#define get_SE_Q_PRIORITY_reg   (*((volatile unsigned int*) SE_Q_PRIORITY_reg))
#define SE_Q_PRIORITY_inst_adr                                                       "0x000F"
#define SE_Q_PRIORITY_inst                                                           0x000F
#define SE_Q_PRIORITY_Pri3_shift                                                     (4)
#define SE_Q_PRIORITY_Pri3_mask                                                      (0x00000030)
#define SE_Q_PRIORITY_Pri3(data)                                                     (0x00000030&((data)<<4))
#define SE_Q_PRIORITY_Pri3_src(data)                                                 ((0x00000030&(data))>>4)
#define SE_Q_PRIORITY_get_Pri3(data)                                                 ((0x00000030&(data))>>4)
#define SE_Q_PRIORITY_Pri2_shift                                                     (2)
#define SE_Q_PRIORITY_Pri2_mask                                                      (0x0000000C)
#define SE_Q_PRIORITY_Pri2(data)                                                     (0x0000000C&((data)<<2))
#define SE_Q_PRIORITY_Pri2_src(data)                                                 ((0x0000000C&(data))>>2)
#define SE_Q_PRIORITY_get_Pri2(data)                                                 ((0x0000000C&(data))>>2)
#define SE_Q_PRIORITY_Pri1_shift                                                     (0)
#define SE_Q_PRIORITY_Pri1_mask                                                      (0x00000003)
#define SE_Q_PRIORITY_Pri1(data)                                                     (0x00000003&((data)<<0))
#define SE_Q_PRIORITY_Pri1_src(data)                                                 ((0x00000003&(data))>>0)
#define SE_Q_PRIORITY_get_Pri1(data)                                                 ((0x00000003&(data))>>0)


#define SE_CLR_FMT_0                                                                 0x1800C040
#define SE_CLR_FMT_1                                                                 0x1800C044
#define SE_CLR_FMT_2                                                                 0x1800C048
#define SE_CLR_FMT_0_reg_addr                                                        "0xB800C040"
#define SE_CLR_FMT_1_reg_addr                                                        "0xB800C044"
#define SE_CLR_FMT_2_reg_addr                                                        "0xB800C048"
#define SE_CLR_FMT_0_reg                                                             0xB800C040
#define SE_CLR_FMT_1_reg                                                             0xB800C044
#define SE_CLR_FMT_2_reg                                                             0xB800C048
#define set_SE_CLR_FMT_0_reg(data)   (*((volatile unsigned int*) SE_CLR_FMT_0_reg)=data)
#define set_SE_CLR_FMT_1_reg(data)   (*((volatile unsigned int*) SE_CLR_FMT_1_reg)=data)
#define set_SE_CLR_FMT_2_reg(data)   (*((volatile unsigned int*) SE_CLR_FMT_2_reg)=data)
#define get_SE_CLR_FMT_0_reg   (*((volatile unsigned int*) SE_CLR_FMT_0_reg))
#define get_SE_CLR_FMT_1_reg   (*((volatile unsigned int*) SE_CLR_FMT_1_reg))
#define get_SE_CLR_FMT_2_reg   (*((volatile unsigned int*) SE_CLR_FMT_2_reg))
#define SE_CLR_FMT_0_inst_adr                                                        "0x0010"
#define SE_CLR_FMT_1_inst_adr                                                        "0x0011"
#define SE_CLR_FMT_2_inst_adr                                                        "0x0012"
#define SE_CLR_FMT_0_inst                                                            0x0010
#define SE_CLR_FMT_1_inst                                                            0x0011
#define SE_CLR_FMT_2_inst                                                            0x0012
#define SE_CLR_FMT_write_enable10_shift                                              (22)
#define SE_CLR_FMT_write_enable10_mask                                               (0x00400000)
#define SE_CLR_FMT_write_enable10(data)                                              (0x00400000&((data)<<22))
#define SE_CLR_FMT_write_enable10_src(data)                                          ((0x00400000&(data))>>22)
#define SE_CLR_FMT_get_write_enable10(data)                                          ((0x00400000&(data))>>22)
#define SE_CLR_FMT_rounding_en_shift                                                 (21)
#define SE_CLR_FMT_rounding_en_mask                                                  (0x00200000)
#define SE_CLR_FMT_rounding_en(data)                                                 (0x00200000&((data)<<21))
#define SE_CLR_FMT_rounding_en_src(data)                                             ((0x00200000&(data))>>21)
#define SE_CLR_FMT_get_rounding_en(data)                                             ((0x00200000&(data))>>21)
#define SE_CLR_FMT_write_enable8_shift                                               (20)
#define SE_CLR_FMT_write_enable8_mask                                                (0x00100000)
#define SE_CLR_FMT_write_enable8(data)                                               (0x00100000&((data)<<20))
#define SE_CLR_FMT_write_enable8_src(data)                                           ((0x00100000&(data))>>20)
#define SE_CLR_FMT_get_write_enable8(data)                                           ((0x00100000&(data))>>20)
#define SE_CLR_FMT_big_endian_o_shift                                                (19)
#define SE_CLR_FMT_big_endian_o_mask                                                 (0x00080000)
#define SE_CLR_FMT_big_endian_o(data)                                                (0x00080000&((data)<<19))
#define SE_CLR_FMT_big_endian_o_src(data)                                            ((0x00080000&(data))>>19)
#define SE_CLR_FMT_get_big_endian_o(data)                                            ((0x00080000&(data))>>19)
#define SE_CLR_FMT_write_enable7_shift                                               (18)
#define SE_CLR_FMT_write_enable7_mask                                                (0x00040000)
#define SE_CLR_FMT_write_enable7(data)                                               (0x00040000&((data)<<18))
#define SE_CLR_FMT_write_enable7_src(data)                                           ((0x00040000&(data))>>18)
#define SE_CLR_FMT_get_write_enable7(data)                                           ((0x00040000&(data))>>18)
#define SE_CLR_FMT_big_endian_i2_shift                                               (17)
#define SE_CLR_FMT_big_endian_i2_mask                                                (0x00020000)
#define SE_CLR_FMT_big_endian_i2(data)                                               (0x00020000&((data)<<17))
#define SE_CLR_FMT_big_endian_i2_src(data)                                           ((0x00020000&(data))>>17)
#define SE_CLR_FMT_get_big_endian_i2(data)                                           ((0x00020000&(data))>>17)
#define SE_CLR_FMT_write_enable6_shift                                               (16)
#define SE_CLR_FMT_write_enable6_mask                                                (0x00010000)
#define SE_CLR_FMT_write_enable6(data)                                               (0x00010000&((data)<<16))
#define SE_CLR_FMT_write_enable6_src(data)                                           ((0x00010000&(data))>>16)
#define SE_CLR_FMT_get_write_enable6(data)                                           ((0x00010000&(data))>>16)
#define SE_CLR_FMT_big_endian_i1_shift                                               (15)
#define SE_CLR_FMT_big_endian_i1_mask                                                (0x00008000)
#define SE_CLR_FMT_big_endian_i1(data)                                               (0x00008000&((data)<<15))
#define SE_CLR_FMT_big_endian_i1_src(data)                                           ((0x00008000&(data))>>15)
#define SE_CLR_FMT_get_big_endian_i1(data)                                           ((0x00008000&(data))>>15)
#define SE_CLR_FMT_write_enable5_shift                                               (14)
#define SE_CLR_FMT_write_enable5_mask                                                (0x00004000)
#define SE_CLR_FMT_write_enable5(data)                                               (0x00004000&((data)<<14))
#define SE_CLR_FMT_write_enable5_src(data)                                           ((0x00004000&(data))>>14)
#define SE_CLR_FMT_get_write_enable5(data)                                           ((0x00004000&(data))>>14)
#define SE_CLR_FMT_alpha_loc2_shift                                                  (13)
#define SE_CLR_FMT_alpha_loc2_mask                                                   (0x00002000)
#define SE_CLR_FMT_alpha_loc2(data)                                                  (0x00002000&((data)<<13))
#define SE_CLR_FMT_alpha_loc2_src(data)                                              ((0x00002000&(data))>>13)
#define SE_CLR_FMT_get_alpha_loc2(data)                                              ((0x00002000&(data))>>13)
#define SE_CLR_FMT_write_enable2_shift                                               (6)
#define SE_CLR_FMT_write_enable2_mask                                                (0x00000040)
#define SE_CLR_FMT_write_enable2(data)                                               (0x00000040&((data)<<6))
#define SE_CLR_FMT_write_enable2_src(data)                                           ((0x00000040&(data))>>6)
#define SE_CLR_FMT_get_write_enable2(data)                                           ((0x00000040&(data))>>6)
#define SE_CLR_FMT_alpha_loc_shift                                                   (5)
#define SE_CLR_FMT_alpha_loc_mask                                                    (0x00000020)
#define SE_CLR_FMT_alpha_loc(data)                                                   (0x00000020&((data)<<5))
#define SE_CLR_FMT_alpha_loc_src(data)                                               ((0x00000020&(data))>>5)
#define SE_CLR_FMT_get_alpha_loc(data)                                               ((0x00000020&(data))>>5)
#define SE_CLR_FMT_write_enable1_shift                                               (4)
#define SE_CLR_FMT_write_enable1_mask                                                (0x00000010)
#define SE_CLR_FMT_write_enable1(data)                                               (0x00000010&((data)<<4))
#define SE_CLR_FMT_write_enable1_src(data)                                           ((0x00000010&(data))>>4)
#define SE_CLR_FMT_get_write_enable1(data)                                           ((0x00000010&(data))>>4)
#define SE_CLR_FMT_Format_shift                                                      (0)
#define SE_CLR_FMT_Format_mask                                                       (0x0000000F)
#define SE_CLR_FMT_Format(data)                                                      (0x0000000F&((data)<<0))
#define SE_CLR_FMT_Format_src(data)                                                  ((0x0000000F&(data))>>0)
#define SE_CLR_FMT_get_Format(data)                                                  ((0x0000000F&(data))>>0)


#define SE_COLOR_KEY_0                                                               0x1800C04C
#define SE_COLOR_KEY_1                                                               0x1800C050
#define SE_COLOR_KEY_2                                                               0x1800C054
#define SE_COLOR_KEY_0_reg_addr                                                      "0xB800C04C"
#define SE_COLOR_KEY_1_reg_addr                                                      "0xB800C050"
#define SE_COLOR_KEY_2_reg_addr                                                      "0xB800C054"
#define SE_COLOR_KEY_0_reg                                                           0xB800C04C
#define SE_COLOR_KEY_1_reg                                                           0xB800C050
#define SE_COLOR_KEY_2_reg                                                           0xB800C054
#define set_SE_COLOR_KEY_0_reg(data)   (*((volatile unsigned int*) SE_COLOR_KEY_0_reg)=data)
#define set_SE_COLOR_KEY_1_reg(data)   (*((volatile unsigned int*) SE_COLOR_KEY_1_reg)=data)
#define set_SE_COLOR_KEY_2_reg(data)   (*((volatile unsigned int*) SE_COLOR_KEY_2_reg)=data)
#define get_SE_COLOR_KEY_0_reg   (*((volatile unsigned int*) SE_COLOR_KEY_0_reg))
#define get_SE_COLOR_KEY_1_reg   (*((volatile unsigned int*) SE_COLOR_KEY_1_reg))
#define get_SE_COLOR_KEY_2_reg   (*((volatile unsigned int*) SE_COLOR_KEY_2_reg))
#define SE_COLOR_KEY_0_inst_adr                                                      "0x0013"
#define SE_COLOR_KEY_1_inst_adr                                                      "0x0014"
#define SE_COLOR_KEY_2_inst_adr                                                      "0x0015"
#define SE_COLOR_KEY_0_inst                                                          0x0013
#define SE_COLOR_KEY_1_inst                                                          0x0014
#define SE_COLOR_KEY_2_inst                                                          0x0015
#define SE_COLOR_KEY_color_key_shift                                                 (0)
#define SE_COLOR_KEY_color_key_mask                                                  (0x00FFFFFF)
#define SE_COLOR_KEY_color_key(data)                                                 (0x00FFFFFF&((data)<<0))
#define SE_COLOR_KEY_color_key_src(data)                                             ((0x00FFFFFF&(data))>>0)
#define SE_COLOR_KEY_get_color_key(data)                                             ((0x00FFFFFF&(data))>>0)


#define SE_DST_COLOR_KEY_0                                                           0x1800C54C
#define SE_DST_COLOR_KEY_1                                                           0x1800C550
#define SE_DST_COLOR_KEY_2                                                           0x1800C554
#define SE_DST_COLOR_KEY_0_reg_addr                                                  "0xB800C54C"
#define SE_DST_COLOR_KEY_1_reg_addr                                                  "0xB800C550"
#define SE_DST_COLOR_KEY_2_reg_addr                                                  "0xB800C554"
#define SE_DST_COLOR_KEY_0_reg                                                       0xB800C54C
#define SE_DST_COLOR_KEY_1_reg                                                       0xB800C550
#define SE_DST_COLOR_KEY_2_reg                                                       0xB800C554
#define set_SE_DST_COLOR_KEY_0_reg(data)   (*((volatile unsigned int*) SE_DST_COLOR_KEY_0_reg)=data)
#define set_SE_DST_COLOR_KEY_1_reg(data)   (*((volatile unsigned int*) SE_DST_COLOR_KEY_1_reg)=data)
#define set_SE_DST_COLOR_KEY_2_reg(data)   (*((volatile unsigned int*) SE_DST_COLOR_KEY_2_reg)=data)
#define get_SE_DST_COLOR_KEY_0_reg   (*((volatile unsigned int*) SE_DST_COLOR_KEY_0_reg))
#define get_SE_DST_COLOR_KEY_1_reg   (*((volatile unsigned int*) SE_DST_COLOR_KEY_1_reg))
#define get_SE_DST_COLOR_KEY_2_reg   (*((volatile unsigned int*) SE_DST_COLOR_KEY_2_reg))
#define SE_DST_COLOR_KEY_0_inst_adr                                                  "0x0053"
#define SE_DST_COLOR_KEY_1_inst_adr                                                  "0x0054"
#define SE_DST_COLOR_KEY_2_inst_adr                                                  "0x0055"
#define SE_DST_COLOR_KEY_0_inst                                                      0x0053
#define SE_DST_COLOR_KEY_1_inst                                                      0x0054
#define SE_DST_COLOR_KEY_2_inst                                                      0x0055
#define SE_DST_COLOR_KEY_dst_color_key_shift                                         (0)
#define SE_DST_COLOR_KEY_dst_color_key_mask                                          (0x00FFFFFF)
#define SE_DST_COLOR_KEY_dst_color_key(data)                                         (0x00FFFFFF&((data)<<0))
#define SE_DST_COLOR_KEY_dst_color_key_src(data)                                     ((0x00FFFFFF&(data))>>0)
#define SE_DST_COLOR_KEY_get_dst_color_key(data)                                     ((0x00FFFFFF&(data))>>0)


#define SE_SRC_COLOR_0                                                               0x1800C058
#define SE_SRC_COLOR_1                                                               0x1800C05C
#define SE_SRC_COLOR_2                                                               0x1800C060
#define SE_SRC_COLOR_0_reg_addr                                                      "0xB800C058"
#define SE_SRC_COLOR_1_reg_addr                                                      "0xB800C05C"
#define SE_SRC_COLOR_2_reg_addr                                                      "0xB800C060"
#define SE_SRC_COLOR_0_reg                                                           0xB800C058
#define SE_SRC_COLOR_1_reg                                                           0xB800C05C
#define SE_SRC_COLOR_2_reg                                                           0xB800C060
#define set_SE_SRC_COLOR_0_reg(data)   (*((volatile unsigned int*) SE_SRC_COLOR_0_reg)=data)
#define set_SE_SRC_COLOR_1_reg(data)   (*((volatile unsigned int*) SE_SRC_COLOR_1_reg)=data)
#define set_SE_SRC_COLOR_2_reg(data)   (*((volatile unsigned int*) SE_SRC_COLOR_2_reg)=data)
#define get_SE_SRC_COLOR_0_reg   (*((volatile unsigned int*) SE_SRC_COLOR_0_reg))
#define get_SE_SRC_COLOR_1_reg   (*((volatile unsigned int*) SE_SRC_COLOR_1_reg))
#define get_SE_SRC_COLOR_2_reg   (*((volatile unsigned int*) SE_SRC_COLOR_2_reg))
#define SE_SRC_COLOR_0_inst_adr                                                      "0x0016"
#define SE_SRC_COLOR_1_inst_adr                                                      "0x0017"
#define SE_SRC_COLOR_2_inst_adr                                                      "0x0018"
#define SE_SRC_COLOR_0_inst                                                          0x0016
#define SE_SRC_COLOR_1_inst                                                          0x0017
#define SE_SRC_COLOR_2_inst                                                          0x0018
#define SE_SRC_COLOR_src_color_shift                                                 (0)
#define SE_SRC_COLOR_src_color_mask                                                  (0xFFFFFFFF)
#define SE_SRC_COLOR_src_color(data)                                                 (0xFFFFFFFF&((data)<<0))
#define SE_SRC_COLOR_src_color_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define SE_SRC_COLOR_get_src_color(data)                                             ((0xFFFFFFFF&(data))>>0)


#define SE_SRC_ALPHA_0                                                               0x1800C070
#define SE_SRC_ALPHA_1                                                               0x1800C074
#define SE_SRC_ALPHA_2                                                               0x1800C078
#define SE_SRC_ALPHA_0_reg_addr                                                      "0xB800C070"
#define SE_SRC_ALPHA_1_reg_addr                                                      "0xB800C074"
#define SE_SRC_ALPHA_2_reg_addr                                                      "0xB800C078"
#define SE_SRC_ALPHA_0_reg                                                           0xB800C070
#define SE_SRC_ALPHA_1_reg                                                           0xB800C074
#define SE_SRC_ALPHA_2_reg                                                           0xB800C078
#define set_SE_SRC_ALPHA_0_reg(data)   (*((volatile unsigned int*) SE_SRC_ALPHA_0_reg)=data)
#define set_SE_SRC_ALPHA_1_reg(data)   (*((volatile unsigned int*) SE_SRC_ALPHA_1_reg)=data)
#define set_SE_SRC_ALPHA_2_reg(data)   (*((volatile unsigned int*) SE_SRC_ALPHA_2_reg)=data)
#define get_SE_SRC_ALPHA_0_reg   (*((volatile unsigned int*) SE_SRC_ALPHA_0_reg))
#define get_SE_SRC_ALPHA_1_reg   (*((volatile unsigned int*) SE_SRC_ALPHA_1_reg))
#define get_SE_SRC_ALPHA_2_reg   (*((volatile unsigned int*) SE_SRC_ALPHA_2_reg))
#define SE_SRC_ALPHA_0_inst_adr                                                      "0x001C"
#define SE_SRC_ALPHA_1_inst_adr                                                      "0x001D"
#define SE_SRC_ALPHA_2_inst_adr                                                      "0x001E"
#define SE_SRC_ALPHA_0_inst                                                          0x001C
#define SE_SRC_ALPHA_1_inst                                                          0x001D
#define SE_SRC_ALPHA_2_inst                                                          0x001E
#define SE_SRC_ALPHA_src_alpha_shift                                                 (0)
#define SE_SRC_ALPHA_src_alpha_mask                                                  (0x000000FF)
#define SE_SRC_ALPHA_src_alpha(data)                                                 (0x000000FF&((data)<<0))
#define SE_SRC_ALPHA_src_alpha_src(data)                                             ((0x000000FF&(data))>>0)
#define SE_SRC_ALPHA_get_src_alpha(data)                                             ((0x000000FF&(data))>>0)


#define SE_DEST_ALPHA_0                                                              0x1800C07C
#define SE_DEST_ALPHA_1                                                              0x1800C080
#define SE_DEST_ALPHA_2                                                              0x1800C084
#define SE_DEST_ALPHA_0_reg_addr                                                     "0xB800C07C"
#define SE_DEST_ALPHA_1_reg_addr                                                     "0xB800C080"
#define SE_DEST_ALPHA_2_reg_addr                                                     "0xB800C084"
#define SE_DEST_ALPHA_0_reg                                                          0xB800C07C
#define SE_DEST_ALPHA_1_reg                                                          0xB800C080
#define SE_DEST_ALPHA_2_reg                                                          0xB800C084
#define set_SE_DEST_ALPHA_0_reg(data)   (*((volatile unsigned int*) SE_DEST_ALPHA_0_reg)=data)
#define set_SE_DEST_ALPHA_1_reg(data)   (*((volatile unsigned int*) SE_DEST_ALPHA_1_reg)=data)
#define set_SE_DEST_ALPHA_2_reg(data)   (*((volatile unsigned int*) SE_DEST_ALPHA_2_reg)=data)
#define get_SE_DEST_ALPHA_0_reg   (*((volatile unsigned int*) SE_DEST_ALPHA_0_reg))
#define get_SE_DEST_ALPHA_1_reg   (*((volatile unsigned int*) SE_DEST_ALPHA_1_reg))
#define get_SE_DEST_ALPHA_2_reg   (*((volatile unsigned int*) SE_DEST_ALPHA_2_reg))
#define SE_DEST_ALPHA_0_inst_adr                                                     "0x001F"
#define SE_DEST_ALPHA_1_inst_adr                                                     "0x0020"
#define SE_DEST_ALPHA_2_inst_adr                                                     "0x0021"
#define SE_DEST_ALPHA_0_inst                                                         0x001F
#define SE_DEST_ALPHA_1_inst                                                         0x0020
#define SE_DEST_ALPHA_2_inst                                                         0x0021
#define SE_DEST_ALPHA_dest_alpha_shift                                               (0)
#define SE_DEST_ALPHA_dest_alpha_mask                                                (0x000000FF)
#define SE_DEST_ALPHA_dest_alpha(data)                                               (0x000000FF&((data)<<0))
#define SE_DEST_ALPHA_dest_alpha_src(data)                                           ((0x000000FF&(data))>>0)
#define SE_DEST_ALPHA_get_dest_alpha(data)                                           ((0x000000FF&(data))>>0)


#define SE_RSLT_ALPHA_0                                                              0x1800C088
#define SE_RSLT_ALPHA_1                                                              0x1800C08C
#define SE_RSLT_ALPHA_2                                                              0x1800C090
#define SE_RSLT_ALPHA_0_reg_addr                                                     "0xB800C088"
#define SE_RSLT_ALPHA_1_reg_addr                                                     "0xB800C08C"
#define SE_RSLT_ALPHA_2_reg_addr                                                     "0xB800C090"
#define SE_RSLT_ALPHA_0_reg                                                          0xB800C088
#define SE_RSLT_ALPHA_1_reg                                                          0xB800C08C
#define SE_RSLT_ALPHA_2_reg                                                          0xB800C090
#define set_SE_RSLT_ALPHA_0_reg(data)   (*((volatile unsigned int*) SE_RSLT_ALPHA_0_reg)=data)
#define set_SE_RSLT_ALPHA_1_reg(data)   (*((volatile unsigned int*) SE_RSLT_ALPHA_1_reg)=data)
#define set_SE_RSLT_ALPHA_2_reg(data)   (*((volatile unsigned int*) SE_RSLT_ALPHA_2_reg)=data)
#define get_SE_RSLT_ALPHA_0_reg   (*((volatile unsigned int*) SE_RSLT_ALPHA_0_reg))
#define get_SE_RSLT_ALPHA_1_reg   (*((volatile unsigned int*) SE_RSLT_ALPHA_1_reg))
#define get_SE_RSLT_ALPHA_2_reg   (*((volatile unsigned int*) SE_RSLT_ALPHA_2_reg))
#define SE_RSLT_ALPHA_0_inst_adr                                                     "0x0022"
#define SE_RSLT_ALPHA_1_inst_adr                                                     "0x0023"
#define SE_RSLT_ALPHA_2_inst_adr                                                     "0x0024"
#define SE_RSLT_ALPHA_0_inst                                                         0x0022
#define SE_RSLT_ALPHA_1_inst                                                         0x0023
#define SE_RSLT_ALPHA_2_inst                                                         0x0024
#define SE_RSLT_ALPHA_rslt_alpha_shift                                               (0)
#define SE_RSLT_ALPHA_rslt_alpha_mask                                                (0x000000FF)
#define SE_RSLT_ALPHA_rslt_alpha(data)                                               (0x000000FF&((data)<<0))
#define SE_RSLT_ALPHA_rslt_alpha_src(data)                                           ((0x000000FF&(data))>>0)
#define SE_RSLT_ALPHA_get_rslt_alpha(data)                                           ((0x000000FF&(data))>>0)


#define SE_BADDR1_0                                                                  0x1800C094
#define SE_BADDR1_1                                                                  0x1800C098
#define SE_BADDR1_2                                                                  0x1800C09C
#define SE_BADDR1_3                                                                  0x1800C0A0
#define SE_BADDR1_0_reg_addr                                                         "0xB800C094"
#define SE_BADDR1_1_reg_addr                                                         "0xB800C098"
#define SE_BADDR1_2_reg_addr                                                         "0xB800C09C"
#define SE_BADDR1_3_reg_addr                                                         "0xB800C0A0"
#define SE_BADDR1_0_reg                                                              0xB800C094
#define SE_BADDR1_1_reg                                                              0xB800C098
#define SE_BADDR1_2_reg                                                              0xB800C09C
#define SE_BADDR1_3_reg                                                              0xB800C0A0
#define set_SE_BADDR1_0_reg(data)   (*((volatile unsigned int*) SE_BADDR1_0_reg)=data)
#define set_SE_BADDR1_1_reg(data)   (*((volatile unsigned int*) SE_BADDR1_1_reg)=data)
#define set_SE_BADDR1_2_reg(data)   (*((volatile unsigned int*) SE_BADDR1_2_reg)=data)
#define set_SE_BADDR1_3_reg(data)   (*((volatile unsigned int*) SE_BADDR1_3_reg)=data)
#define get_SE_BADDR1_0_reg   (*((volatile unsigned int*) SE_BADDR1_0_reg))
#define get_SE_BADDR1_1_reg   (*((volatile unsigned int*) SE_BADDR1_1_reg))
#define get_SE_BADDR1_2_reg   (*((volatile unsigned int*) SE_BADDR1_2_reg))
#define get_SE_BADDR1_3_reg   (*((volatile unsigned int*) SE_BADDR1_3_reg))
#define SE_BADDR1_0_inst_adr                                                         "0x0025"
#define SE_BADDR1_1_inst_adr                                                         "0x0026"
#define SE_BADDR1_2_inst_adr                                                         "0x0027"
#define SE_BADDR1_3_inst_adr                                                         "0x0028"
#define SE_BADDR1_0_inst                                                             0x0025
#define SE_BADDR1_1_inst                                                             0x0026
#define SE_BADDR1_2_inst                                                             0x0027
#define SE_BADDR1_3_inst                                                             0x0028
#define SE_BADDR1_baddr_shift                                                        (0)
#define SE_BADDR1_baddr_mask                                                         (0x7FFFFFFF)
#define SE_BADDR1_baddr(data)                                                        (0x7FFFFFFF&((data)<<0))
#define SE_BADDR1_baddr_src(data)                                                    ((0x7FFFFFFF&(data))>>0)
#define SE_BADDR1_get_baddr(data)                                                    ((0x7FFFFFFF&(data))>>0)


#define SE_PITCH1_0                                                                  0x1800C0A4
#define SE_PITCH1_1                                                                  0x1800C0A8
#define SE_PITCH1_2                                                                  0x1800C0AC
#define SE_PITCH1_3                                                                  0x1800C0B0
#define SE_PITCH1_0_reg_addr                                                         "0xB800C0A4"
#define SE_PITCH1_1_reg_addr                                                         "0xB800C0A8"
#define SE_PITCH1_2_reg_addr                                                         "0xB800C0AC"
#define SE_PITCH1_3_reg_addr                                                         "0xB800C0B0"
#define SE_PITCH1_0_reg                                                              0xB800C0A4
#define SE_PITCH1_1_reg                                                              0xB800C0A8
#define SE_PITCH1_2_reg                                                              0xB800C0AC
#define SE_PITCH1_3_reg                                                              0xB800C0B0
#define set_SE_PITCH1_0_reg(data)   (*((volatile unsigned int*) SE_PITCH1_0_reg)=data)
#define set_SE_PITCH1_1_reg(data)   (*((volatile unsigned int*) SE_PITCH1_1_reg)=data)
#define set_SE_PITCH1_2_reg(data)   (*((volatile unsigned int*) SE_PITCH1_2_reg)=data)
#define set_SE_PITCH1_3_reg(data)   (*((volatile unsigned int*) SE_PITCH1_3_reg)=data)
#define get_SE_PITCH1_0_reg   (*((volatile unsigned int*) SE_PITCH1_0_reg))
#define get_SE_PITCH1_1_reg   (*((volatile unsigned int*) SE_PITCH1_1_reg))
#define get_SE_PITCH1_2_reg   (*((volatile unsigned int*) SE_PITCH1_2_reg))
#define get_SE_PITCH1_3_reg   (*((volatile unsigned int*) SE_PITCH1_3_reg))
#define SE_PITCH1_0_inst_adr                                                         "0x0029"
#define SE_PITCH1_1_inst_adr                                                         "0x002A"
#define SE_PITCH1_2_inst_adr                                                         "0x002B"
#define SE_PITCH1_3_inst_adr                                                         "0x002C"
#define SE_PITCH1_0_inst                                                             0x0029
#define SE_PITCH1_1_inst                                                             0x002A
#define SE_PITCH1_2_inst                                                             0x002B
#define SE_PITCH1_3_inst                                                             0x002C
#define SE_PITCH1_interleave_shift                                                   (16)
#define SE_PITCH1_interleave_mask                                                    (0x00010000)
#define SE_PITCH1_interleave(data)                                                   (0x00010000&((data)<<16))
#define SE_PITCH1_interleave_src(data)                                               ((0x00010000&(data))>>16)
#define SE_PITCH1_get_interleave(data)                                               ((0x00010000&(data))>>16)
#define SE_PITCH1_pitch_shift                                                        (0)
#define SE_PITCH1_pitch_mask                                                         (0x0000FFFF)
#define SE_PITCH1_pitch(data)                                                        (0x0000FFFF&((data)<<0))
#define SE_PITCH1_pitch_src(data)                                                    ((0x0000FFFF&(data))>>0)
#define SE_PITCH1_get_pitch(data)                                                    ((0x0000FFFF&(data))>>0)


#define SE_BADDR2_0                                                                  0x1800C0B4
#define SE_BADDR2_1                                                                  0x1800C0B8
#define SE_BADDR2_2                                                                  0x1800C0BC
#define SE_BADDR2_3                                                                  0x1800C0C0
#define SE_BADDR2_0_reg_addr                                                         "0xB800C0B4"
#define SE_BADDR2_1_reg_addr                                                         "0xB800C0B8"
#define SE_BADDR2_2_reg_addr                                                         "0xB800C0BC"
#define SE_BADDR2_3_reg_addr                                                         "0xB800C0C0"
#define SE_BADDR2_0_reg                                                              0xB800C0B4
#define SE_BADDR2_1_reg                                                              0xB800C0B8
#define SE_BADDR2_2_reg                                                              0xB800C0BC
#define SE_BADDR2_3_reg                                                              0xB800C0C0
#define set_SE_BADDR2_0_reg(data)   (*((volatile unsigned int*) SE_BADDR2_0_reg)=data)
#define set_SE_BADDR2_1_reg(data)   (*((volatile unsigned int*) SE_BADDR2_1_reg)=data)
#define set_SE_BADDR2_2_reg(data)   (*((volatile unsigned int*) SE_BADDR2_2_reg)=data)
#define set_SE_BADDR2_3_reg(data)   (*((volatile unsigned int*) SE_BADDR2_3_reg)=data)
#define get_SE_BADDR2_0_reg   (*((volatile unsigned int*) SE_BADDR2_0_reg))
#define get_SE_BADDR2_1_reg   (*((volatile unsigned int*) SE_BADDR2_1_reg))
#define get_SE_BADDR2_2_reg   (*((volatile unsigned int*) SE_BADDR2_2_reg))
#define get_SE_BADDR2_3_reg   (*((volatile unsigned int*) SE_BADDR2_3_reg))
#define SE_BADDR2_0_inst_adr                                                         "0x002D"
#define SE_BADDR2_1_inst_adr                                                         "0x002E"
#define SE_BADDR2_2_inst_adr                                                         "0x002F"
#define SE_BADDR2_3_inst_adr                                                         "0x0030"
#define SE_BADDR2_0_inst                                                             0x002D
#define SE_BADDR2_1_inst                                                             0x002E
#define SE_BADDR2_2_inst                                                             0x002F
#define SE_BADDR2_3_inst                                                             0x0030
#define SE_BADDR2_baddr_shift                                                        (0)
#define SE_BADDR2_baddr_mask                                                         (0x7FFFFFFF)
#define SE_BADDR2_baddr(data)                                                        (0x7FFFFFFF&((data)<<0))
#define SE_BADDR2_baddr_src(data)                                                    ((0x7FFFFFFF&(data))>>0)
#define SE_BADDR2_get_baddr(data)                                                    ((0x7FFFFFFF&(data))>>0)


#define SE_PITCH2_0                                                                  0x1800C0C4
#define SE_PITCH2_1                                                                  0x1800C0C8
#define SE_PITCH2_2                                                                  0x1800C0CC
#define SE_PITCH2_3                                                                  0x1800C0D0
#define SE_PITCH2_0_reg_addr                                                         "0xB800C0C4"
#define SE_PITCH2_1_reg_addr                                                         "0xB800C0C8"
#define SE_PITCH2_2_reg_addr                                                         "0xB800C0CC"
#define SE_PITCH2_3_reg_addr                                                         "0xB800C0D0"
#define SE_PITCH2_0_reg                                                              0xB800C0C4
#define SE_PITCH2_1_reg                                                              0xB800C0C8
#define SE_PITCH2_2_reg                                                              0xB800C0CC
#define SE_PITCH2_3_reg                                                              0xB800C0D0
#define set_SE_PITCH2_0_reg(data)   (*((volatile unsigned int*) SE_PITCH2_0_reg)=data)
#define set_SE_PITCH2_1_reg(data)   (*((volatile unsigned int*) SE_PITCH2_1_reg)=data)
#define set_SE_PITCH2_2_reg(data)   (*((volatile unsigned int*) SE_PITCH2_2_reg)=data)
#define set_SE_PITCH2_3_reg(data)   (*((volatile unsigned int*) SE_PITCH2_3_reg)=data)
#define get_SE_PITCH2_0_reg   (*((volatile unsigned int*) SE_PITCH2_0_reg))
#define get_SE_PITCH2_1_reg   (*((volatile unsigned int*) SE_PITCH2_1_reg))
#define get_SE_PITCH2_2_reg   (*((volatile unsigned int*) SE_PITCH2_2_reg))
#define get_SE_PITCH2_3_reg   (*((volatile unsigned int*) SE_PITCH2_3_reg))
#define SE_PITCH2_0_inst_adr                                                         "0x0031"
#define SE_PITCH2_1_inst_adr                                                         "0x0032"
#define SE_PITCH2_2_inst_adr                                                         "0x0033"
#define SE_PITCH2_3_inst_adr                                                         "0x0034"
#define SE_PITCH2_0_inst                                                             0x0031
#define SE_PITCH2_1_inst                                                             0x0032
#define SE_PITCH2_2_inst                                                             0x0033
#define SE_PITCH2_3_inst                                                             0x0034
#define SE_PITCH2_interleave_shift                                                   (16)
#define SE_PITCH2_interleave_mask                                                    (0x00010000)
#define SE_PITCH2_interleave(data)                                                   (0x00010000&((data)<<16))
#define SE_PITCH2_interleave_src(data)                                               ((0x00010000&(data))>>16)
#define SE_PITCH2_get_interleave(data)                                               ((0x00010000&(data))>>16)
#define SE_PITCH2_pitch_shift                                                        (0)
#define SE_PITCH2_pitch_mask                                                         (0x0000FFFF)
#define SE_PITCH2_pitch(data)                                                        (0x0000FFFF&((data)<<0))
#define SE_PITCH2_pitch_src(data)                                                    ((0x0000FFFF&(data))>>0)
#define SE_PITCH2_get_pitch(data)                                                    ((0x0000FFFF&(data))>>0)


#define SE_BADDR3_0                                                                  0x1800C0D4
#define SE_BADDR3_1                                                                  0x1800C0D8
#define SE_BADDR3_2                                                                  0x1800C0DC
#define SE_BADDR3_3                                                                  0x1800C0E0
#define SE_BADDR3_0_reg_addr                                                         "0xB800C0D4"
#define SE_BADDR3_1_reg_addr                                                         "0xB800C0D8"
#define SE_BADDR3_2_reg_addr                                                         "0xB800C0DC"
#define SE_BADDR3_3_reg_addr                                                         "0xB800C0E0"
#define SE_BADDR3_0_reg                                                              0xB800C0D4
#define SE_BADDR3_1_reg                                                              0xB800C0D8
#define SE_BADDR3_2_reg                                                              0xB800C0DC
#define SE_BADDR3_3_reg                                                              0xB800C0E0
#define set_SE_BADDR3_0_reg(data)   (*((volatile unsigned int*) SE_BADDR3_0_reg)=data)
#define set_SE_BADDR3_1_reg(data)   (*((volatile unsigned int*) SE_BADDR3_1_reg)=data)
#define set_SE_BADDR3_2_reg(data)   (*((volatile unsigned int*) SE_BADDR3_2_reg)=data)
#define set_SE_BADDR3_3_reg(data)   (*((volatile unsigned int*) SE_BADDR3_3_reg)=data)
#define get_SE_BADDR3_0_reg   (*((volatile unsigned int*) SE_BADDR3_0_reg))
#define get_SE_BADDR3_1_reg   (*((volatile unsigned int*) SE_BADDR3_1_reg))
#define get_SE_BADDR3_2_reg   (*((volatile unsigned int*) SE_BADDR3_2_reg))
#define get_SE_BADDR3_3_reg   (*((volatile unsigned int*) SE_BADDR3_3_reg))
#define SE_BADDR3_0_inst_adr                                                         "0x0035"
#define SE_BADDR3_1_inst_adr                                                         "0x0036"
#define SE_BADDR3_2_inst_adr                                                         "0x0037"
#define SE_BADDR3_3_inst_adr                                                         "0x0038"
#define SE_BADDR3_0_inst                                                             0x0035
#define SE_BADDR3_1_inst                                                             0x0036
#define SE_BADDR3_2_inst                                                             0x0037
#define SE_BADDR3_3_inst                                                             0x0038
#define SE_BADDR3_baddr_shift                                                        (0)
#define SE_BADDR3_baddr_mask                                                         (0x7FFFFFFF)
#define SE_BADDR3_baddr(data)                                                        (0x7FFFFFFF&((data)<<0))
#define SE_BADDR3_baddr_src(data)                                                    ((0x7FFFFFFF&(data))>>0)
#define SE_BADDR3_get_baddr(data)                                                    ((0x7FFFFFFF&(data))>>0)


#define SE_PITCH3_0                                                                  0x1800C0E4
#define SE_PITCH3_1                                                                  0x1800C0E8
#define SE_PITCH3_2                                                                  0x1800C0EC
#define SE_PITCH3_3                                                                  0x1800C0F0
#define SE_PITCH3_0_reg_addr                                                         "0xB800C0E4"
#define SE_PITCH3_1_reg_addr                                                         "0xB800C0E8"
#define SE_PITCH3_2_reg_addr                                                         "0xB800C0EC"
#define SE_PITCH3_3_reg_addr                                                         "0xB800C0F0"
#define SE_PITCH3_0_reg                                                              0xB800C0E4
#define SE_PITCH3_1_reg                                                              0xB800C0E8
#define SE_PITCH3_2_reg                                                              0xB800C0EC
#define SE_PITCH3_3_reg                                                              0xB800C0F0
#define set_SE_PITCH3_0_reg(data)   (*((volatile unsigned int*) SE_PITCH3_0_reg)=data)
#define set_SE_PITCH3_1_reg(data)   (*((volatile unsigned int*) SE_PITCH3_1_reg)=data)
#define set_SE_PITCH3_2_reg(data)   (*((volatile unsigned int*) SE_PITCH3_2_reg)=data)
#define set_SE_PITCH3_3_reg(data)   (*((volatile unsigned int*) SE_PITCH3_3_reg)=data)
#define get_SE_PITCH3_0_reg   (*((volatile unsigned int*) SE_PITCH3_0_reg))
#define get_SE_PITCH3_1_reg   (*((volatile unsigned int*) SE_PITCH3_1_reg))
#define get_SE_PITCH3_2_reg   (*((volatile unsigned int*) SE_PITCH3_2_reg))
#define get_SE_PITCH3_3_reg   (*((volatile unsigned int*) SE_PITCH3_3_reg))
#define SE_PITCH3_0_inst_adr                                                         "0x0039"
#define SE_PITCH3_1_inst_adr                                                         "0x003A"
#define SE_PITCH3_2_inst_adr                                                         "0x003B"
#define SE_PITCH3_3_inst_adr                                                         "0x003C"
#define SE_PITCH3_0_inst                                                             0x0039
#define SE_PITCH3_1_inst                                                             0x003A
#define SE_PITCH3_2_inst                                                             0x003B
#define SE_PITCH3_3_inst                                                             0x003C
#define SE_PITCH3_interleave_shift                                                   (16)
#define SE_PITCH3_interleave_mask                                                    (0x00010000)
#define SE_PITCH3_interleave(data)                                                   (0x00010000&((data)<<16))
#define SE_PITCH3_interleave_src(data)                                               ((0x00010000&(data))>>16)
#define SE_PITCH3_get_interleave(data)                                               ((0x00010000&(data))>>16)
#define SE_PITCH3_pitch_shift                                                        (0)
#define SE_PITCH3_pitch_mask                                                         (0x0000FFFF)
#define SE_PITCH3_pitch(data)                                                        (0x0000FFFF&((data)<<0))
#define SE_PITCH3_pitch_src(data)                                                    ((0x0000FFFF&(data))>>0)
#define SE_PITCH3_get_pitch(data)                                                    ((0x0000FFFF&(data))>>0)


#define SE_CLIP_XCOOR1_0                                                             0x1800C128
#define SE_CLIP_XCOOR1_1                                                             0x1800C12C
#define SE_CLIP_XCOOR1_2                                                             0x1800C130
#define SE_CLIP_XCOOR1_3                                                             0x1800C134
#define SE_CLIP_XCOOR1_0_reg_addr                                                    "0xB800C128"
#define SE_CLIP_XCOOR1_1_reg_addr                                                    "0xB800C12C"
#define SE_CLIP_XCOOR1_2_reg_addr                                                    "0xB800C130"
#define SE_CLIP_XCOOR1_3_reg_addr                                                    "0xB800C134"
#define SE_CLIP_XCOOR1_0_reg                                                         0xB800C128
#define SE_CLIP_XCOOR1_1_reg                                                         0xB800C12C
#define SE_CLIP_XCOOR1_2_reg                                                         0xB800C130
#define SE_CLIP_XCOOR1_3_reg                                                         0xB800C134
#define set_SE_CLIP_XCOOR1_0_reg(data)   (*((volatile unsigned int*) SE_CLIP_XCOOR1_0_reg)=data)
#define set_SE_CLIP_XCOOR1_1_reg(data)   (*((volatile unsigned int*) SE_CLIP_XCOOR1_1_reg)=data)
#define set_SE_CLIP_XCOOR1_2_reg(data)   (*((volatile unsigned int*) SE_CLIP_XCOOR1_2_reg)=data)
#define set_SE_CLIP_XCOOR1_3_reg(data)   (*((volatile unsigned int*) SE_CLIP_XCOOR1_3_reg)=data)
#define get_SE_CLIP_XCOOR1_0_reg   (*((volatile unsigned int*) SE_CLIP_XCOOR1_0_reg))
#define get_SE_CLIP_XCOOR1_1_reg   (*((volatile unsigned int*) SE_CLIP_XCOOR1_1_reg))
#define get_SE_CLIP_XCOOR1_2_reg   (*((volatile unsigned int*) SE_CLIP_XCOOR1_2_reg))
#define get_SE_CLIP_XCOOR1_3_reg   (*((volatile unsigned int*) SE_CLIP_XCOOR1_3_reg))
#define SE_CLIP_XCOOR1_0_inst_adr                                                    "0x004A"
#define SE_CLIP_XCOOR1_1_inst_adr                                                    "0x004B"
#define SE_CLIP_XCOOR1_2_inst_adr                                                    "0x004C"
#define SE_CLIP_XCOOR1_3_inst_adr                                                    "0x004D"
#define SE_CLIP_XCOOR1_0_inst                                                        0x004A
#define SE_CLIP_XCOOR1_1_inst                                                        0x004B
#define SE_CLIP_XCOOR1_2_inst                                                        0x004C
#define SE_CLIP_XCOOR1_3_inst                                                        0x004D
#define SE_CLIP_XCOOR1_clipen_shift                                                  (24)
#define SE_CLIP_XCOOR1_clipen_mask                                                   (0x01000000)
#define SE_CLIP_XCOOR1_clipen(data)                                                  (0x01000000&((data)<<24))
#define SE_CLIP_XCOOR1_clipen_src(data)                                              ((0x01000000&(data))>>24)
#define SE_CLIP_XCOOR1_get_clipen(data)                                              ((0x01000000&(data))>>24)
#define SE_CLIP_XCOOR1_xmin_shift                                                    (12)
#define SE_CLIP_XCOOR1_xmin_mask                                                     (0x00FFF000)
#define SE_CLIP_XCOOR1_xmin(data)                                                    (0x00FFF000&((data)<<12))
#define SE_CLIP_XCOOR1_xmin_src(data)                                                ((0x00FFF000&(data))>>12)
#define SE_CLIP_XCOOR1_get_xmin(data)                                                ((0x00FFF000&(data))>>12)
#define SE_CLIP_XCOOR1_xmax_shift                                                    (0)
#define SE_CLIP_XCOOR1_xmax_mask                                                     (0x00000FFF)
#define SE_CLIP_XCOOR1_xmax(data)                                                    (0x00000FFF&((data)<<0))
#define SE_CLIP_XCOOR1_xmax_src(data)                                                ((0x00000FFF&(data))>>0)
#define SE_CLIP_XCOOR1_get_xmax(data)                                                ((0x00000FFF&(data))>>0)


#define SE_CLIP_YCOOR1_0                                                             0x1800C138
#define SE_CLIP_YCOOR1_1                                                             0x1800C13C
#define SE_CLIP_YCOOR1_2                                                             0x1800C140
#define SE_CLIP_YCOOR1_3                                                             0x1800C144
#define SE_CLIP_YCOOR1_0_reg_addr                                                    "0xB800C138"
#define SE_CLIP_YCOOR1_1_reg_addr                                                    "0xB800C13C"
#define SE_CLIP_YCOOR1_2_reg_addr                                                    "0xB800C140"
#define SE_CLIP_YCOOR1_3_reg_addr                                                    "0xB800C144"
#define SE_CLIP_YCOOR1_0_reg                                                         0xB800C138
#define SE_CLIP_YCOOR1_1_reg                                                         0xB800C13C
#define SE_CLIP_YCOOR1_2_reg                                                         0xB800C140
#define SE_CLIP_YCOOR1_3_reg                                                         0xB800C144
#define set_SE_CLIP_YCOOR1_0_reg(data)   (*((volatile unsigned int*) SE_CLIP_YCOOR1_0_reg)=data)
#define set_SE_CLIP_YCOOR1_1_reg(data)   (*((volatile unsigned int*) SE_CLIP_YCOOR1_1_reg)=data)
#define set_SE_CLIP_YCOOR1_2_reg(data)   (*((volatile unsigned int*) SE_CLIP_YCOOR1_2_reg)=data)
#define set_SE_CLIP_YCOOR1_3_reg(data)   (*((volatile unsigned int*) SE_CLIP_YCOOR1_3_reg)=data)
#define get_SE_CLIP_YCOOR1_0_reg   (*((volatile unsigned int*) SE_CLIP_YCOOR1_0_reg))
#define get_SE_CLIP_YCOOR1_1_reg   (*((volatile unsigned int*) SE_CLIP_YCOOR1_1_reg))
#define get_SE_CLIP_YCOOR1_2_reg   (*((volatile unsigned int*) SE_CLIP_YCOOR1_2_reg))
#define get_SE_CLIP_YCOOR1_3_reg   (*((volatile unsigned int*) SE_CLIP_YCOOR1_3_reg))
#define SE_CLIP_YCOOR1_0_inst_adr                                                    "0x004E"
#define SE_CLIP_YCOOR1_1_inst_adr                                                    "0x004F"
#define SE_CLIP_YCOOR1_2_inst_adr                                                    "0x0050"
#define SE_CLIP_YCOOR1_3_inst_adr                                                    "0x0051"
#define SE_CLIP_YCOOR1_0_inst                                                        0x004E
#define SE_CLIP_YCOOR1_1_inst                                                        0x004F
#define SE_CLIP_YCOOR1_2_inst                                                        0x0050
#define SE_CLIP_YCOOR1_3_inst                                                        0x0051
#define SE_CLIP_YCOOR1_ymin_shift                                                    (12)
#define SE_CLIP_YCOOR1_ymin_mask                                                     (0x00FFF000)
#define SE_CLIP_YCOOR1_ymin(data)                                                    (0x00FFF000&((data)<<12))
#define SE_CLIP_YCOOR1_ymin_src(data)                                                ((0x00FFF000&(data))>>12)
#define SE_CLIP_YCOOR1_get_ymin(data)                                                ((0x00FFF000&(data))>>12)
#define SE_CLIP_YCOOR1_ymax_shift                                                    (0)
#define SE_CLIP_YCOOR1_ymax_mask                                                     (0x00000FFF)
#define SE_CLIP_YCOOR1_ymax(data)                                                    (0x00000FFF&((data)<<0))
#define SE_CLIP_YCOOR1_ymax_src(data)                                                ((0x00000FFF&(data))>>0)
#define SE_CLIP_YCOOR1_get_ymax(data)                                                ((0x00000FFF&(data))>>0)


#define SE_CLIP_XCOOR2_0                                                             0x1800C148
#define SE_CLIP_XCOOR2_1                                                             0x1800C14C
#define SE_CLIP_XCOOR2_2                                                             0x1800C150
#define SE_CLIP_XCOOR2_3                                                             0x1800C154
#define SE_CLIP_XCOOR2_0_reg_addr                                                    "0xB800C148"
#define SE_CLIP_XCOOR2_1_reg_addr                                                    "0xB800C14C"
#define SE_CLIP_XCOOR2_2_reg_addr                                                    "0xB800C150"
#define SE_CLIP_XCOOR2_3_reg_addr                                                    "0xB800C154"
#define SE_CLIP_XCOOR2_0_reg                                                         0xB800C148
#define SE_CLIP_XCOOR2_1_reg                                                         0xB800C14C
#define SE_CLIP_XCOOR2_2_reg                                                         0xB800C150
#define SE_CLIP_XCOOR2_3_reg                                                         0xB800C154
#define set_SE_CLIP_XCOOR2_0_reg(data)   (*((volatile unsigned int*) SE_CLIP_XCOOR2_0_reg)=data)
#define set_SE_CLIP_XCOOR2_1_reg(data)   (*((volatile unsigned int*) SE_CLIP_XCOOR2_1_reg)=data)
#define set_SE_CLIP_XCOOR2_2_reg(data)   (*((volatile unsigned int*) SE_CLIP_XCOOR2_2_reg)=data)
#define set_SE_CLIP_XCOOR2_3_reg(data)   (*((volatile unsigned int*) SE_CLIP_XCOOR2_3_reg)=data)
#define get_SE_CLIP_XCOOR2_0_reg   (*((volatile unsigned int*) SE_CLIP_XCOOR2_0_reg))
#define get_SE_CLIP_XCOOR2_1_reg   (*((volatile unsigned int*) SE_CLIP_XCOOR2_1_reg))
#define get_SE_CLIP_XCOOR2_2_reg   (*((volatile unsigned int*) SE_CLIP_XCOOR2_2_reg))
#define get_SE_CLIP_XCOOR2_3_reg   (*((volatile unsigned int*) SE_CLIP_XCOOR2_3_reg))
#define SE_CLIP_XCOOR2_0_inst_adr                                                    "0x0052"
#define SE_CLIP_XCOOR2_1_inst_adr                                                    "0x0053"
#define SE_CLIP_XCOOR2_2_inst_adr                                                    "0x0054"
#define SE_CLIP_XCOOR2_3_inst_adr                                                    "0x0055"
#define SE_CLIP_XCOOR2_0_inst                                                        0x0052
#define SE_CLIP_XCOOR2_1_inst                                                        0x0053
#define SE_CLIP_XCOOR2_2_inst                                                        0x0054
#define SE_CLIP_XCOOR2_3_inst                                                        0x0055
#define SE_CLIP_XCOOR2_clipen_shift                                                  (24)
#define SE_CLIP_XCOOR2_clipen_mask                                                   (0x01000000)
#define SE_CLIP_XCOOR2_clipen(data)                                                  (0x01000000&((data)<<24))
#define SE_CLIP_XCOOR2_clipen_src(data)                                              ((0x01000000&(data))>>24)
#define SE_CLIP_XCOOR2_get_clipen(data)                                              ((0x01000000&(data))>>24)
#define SE_CLIP_XCOOR2_xmin_shift                                                    (12)
#define SE_CLIP_XCOOR2_xmin_mask                                                     (0x00FFF000)
#define SE_CLIP_XCOOR2_xmin(data)                                                    (0x00FFF000&((data)<<12))
#define SE_CLIP_XCOOR2_xmin_src(data)                                                ((0x00FFF000&(data))>>12)
#define SE_CLIP_XCOOR2_get_xmin(data)                                                ((0x00FFF000&(data))>>12)
#define SE_CLIP_XCOOR2_xmax_shift                                                    (0)
#define SE_CLIP_XCOOR2_xmax_mask                                                     (0x00000FFF)
#define SE_CLIP_XCOOR2_xmax(data)                                                    (0x00000FFF&((data)<<0))
#define SE_CLIP_XCOOR2_xmax_src(data)                                                ((0x00000FFF&(data))>>0)
#define SE_CLIP_XCOOR2_get_xmax(data)                                                ((0x00000FFF&(data))>>0)


#define SE_CLIP_YCOOR2_0                                                             0x1800C158
#define SE_CLIP_YCOOR2_1                                                             0x1800C15C
#define SE_CLIP_YCOOR2_2                                                             0x1800C160
#define SE_CLIP_YCOOR2_3                                                             0x1800C164
#define SE_CLIP_YCOOR2_0_reg_addr                                                    "0xB800C158"
#define SE_CLIP_YCOOR2_1_reg_addr                                                    "0xB800C15C"
#define SE_CLIP_YCOOR2_2_reg_addr                                                    "0xB800C160"
#define SE_CLIP_YCOOR2_3_reg_addr                                                    "0xB800C164"
#define SE_CLIP_YCOOR2_0_reg                                                         0xB800C158
#define SE_CLIP_YCOOR2_1_reg                                                         0xB800C15C
#define SE_CLIP_YCOOR2_2_reg                                                         0xB800C160
#define SE_CLIP_YCOOR2_3_reg                                                         0xB800C164
#define set_SE_CLIP_YCOOR2_0_reg(data)   (*((volatile unsigned int*) SE_CLIP_YCOOR2_0_reg)=data)
#define set_SE_CLIP_YCOOR2_1_reg(data)   (*((volatile unsigned int*) SE_CLIP_YCOOR2_1_reg)=data)
#define set_SE_CLIP_YCOOR2_2_reg(data)   (*((volatile unsigned int*) SE_CLIP_YCOOR2_2_reg)=data)
#define set_SE_CLIP_YCOOR2_3_reg(data)   (*((volatile unsigned int*) SE_CLIP_YCOOR2_3_reg)=data)
#define get_SE_CLIP_YCOOR2_0_reg   (*((volatile unsigned int*) SE_CLIP_YCOOR2_0_reg))
#define get_SE_CLIP_YCOOR2_1_reg   (*((volatile unsigned int*) SE_CLIP_YCOOR2_1_reg))
#define get_SE_CLIP_YCOOR2_2_reg   (*((volatile unsigned int*) SE_CLIP_YCOOR2_2_reg))
#define get_SE_CLIP_YCOOR2_3_reg   (*((volatile unsigned int*) SE_CLIP_YCOOR2_3_reg))
#define SE_CLIP_YCOOR2_0_inst_adr                                                    "0x0056"
#define SE_CLIP_YCOOR2_1_inst_adr                                                    "0x0057"
#define SE_CLIP_YCOOR2_2_inst_adr                                                    "0x0058"
#define SE_CLIP_YCOOR2_3_inst_adr                                                    "0x0059"
#define SE_CLIP_YCOOR2_0_inst                                                        0x0056
#define SE_CLIP_YCOOR2_1_inst                                                        0x0057
#define SE_CLIP_YCOOR2_2_inst                                                        0x0058
#define SE_CLIP_YCOOR2_3_inst                                                        0x0059
#define SE_CLIP_YCOOR2_ymin_shift                                                    (12)
#define SE_CLIP_YCOOR2_ymin_mask                                                     (0x00FFF000)
#define SE_CLIP_YCOOR2_ymin(data)                                                    (0x00FFF000&((data)<<12))
#define SE_CLIP_YCOOR2_ymin_src(data)                                                ((0x00FFF000&(data))>>12)
#define SE_CLIP_YCOOR2_get_ymin(data)                                                ((0x00FFF000&(data))>>12)
#define SE_CLIP_YCOOR2_ymax_shift                                                    (0)
#define SE_CLIP_YCOOR2_ymax_mask                                                     (0x00000FFF)
#define SE_CLIP_YCOOR2_ymax(data)                                                    (0x00000FFF&((data)<<0))
#define SE_CLIP_YCOOR2_ymax_src(data)                                                ((0x00000FFF&(data))>>0)
#define SE_CLIP_YCOOR2_get_ymax(data)                                                ((0x00000FFF&(data))>>0)


#define SE_CLIP_XCOOR3_0                                                             0x1800C168
#define SE_CLIP_XCOOR3_1                                                             0x1800C16C
#define SE_CLIP_XCOOR3_2                                                             0x1800C170
#define SE_CLIP_XCOOR3_3                                                             0x1800C174
#define SE_CLIP_XCOOR3_0_reg_addr                                                    "0xB800C168"
#define SE_CLIP_XCOOR3_1_reg_addr                                                    "0xB800C16C"
#define SE_CLIP_XCOOR3_2_reg_addr                                                    "0xB800C170"
#define SE_CLIP_XCOOR3_3_reg_addr                                                    "0xB800C174"
#define SE_CLIP_XCOOR3_0_reg                                                         0xB800C168
#define SE_CLIP_XCOOR3_1_reg                                                         0xB800C16C
#define SE_CLIP_XCOOR3_2_reg                                                         0xB800C170
#define SE_CLIP_XCOOR3_3_reg                                                         0xB800C174
#define set_SE_CLIP_XCOOR3_0_reg(data)   (*((volatile unsigned int*) SE_CLIP_XCOOR3_0_reg)=data)
#define set_SE_CLIP_XCOOR3_1_reg(data)   (*((volatile unsigned int*) SE_CLIP_XCOOR3_1_reg)=data)
#define set_SE_CLIP_XCOOR3_2_reg(data)   (*((volatile unsigned int*) SE_CLIP_XCOOR3_2_reg)=data)
#define set_SE_CLIP_XCOOR3_3_reg(data)   (*((volatile unsigned int*) SE_CLIP_XCOOR3_3_reg)=data)
#define get_SE_CLIP_XCOOR3_0_reg   (*((volatile unsigned int*) SE_CLIP_XCOOR3_0_reg))
#define get_SE_CLIP_XCOOR3_1_reg   (*((volatile unsigned int*) SE_CLIP_XCOOR3_1_reg))
#define get_SE_CLIP_XCOOR3_2_reg   (*((volatile unsigned int*) SE_CLIP_XCOOR3_2_reg))
#define get_SE_CLIP_XCOOR3_3_reg   (*((volatile unsigned int*) SE_CLIP_XCOOR3_3_reg))
#define SE_CLIP_XCOOR3_0_inst_adr                                                    "0x005A"
#define SE_CLIP_XCOOR3_1_inst_adr                                                    "0x005B"
#define SE_CLIP_XCOOR3_2_inst_adr                                                    "0x005C"
#define SE_CLIP_XCOOR3_3_inst_adr                                                    "0x005D"
#define SE_CLIP_XCOOR3_0_inst                                                        0x005A
#define SE_CLIP_XCOOR3_1_inst                                                        0x005B
#define SE_CLIP_XCOOR3_2_inst                                                        0x005C
#define SE_CLIP_XCOOR3_3_inst                                                        0x005D
#define SE_CLIP_XCOOR3_clipen_shift                                                  (24)
#define SE_CLIP_XCOOR3_clipen_mask                                                   (0x01000000)
#define SE_CLIP_XCOOR3_clipen(data)                                                  (0x01000000&((data)<<24))
#define SE_CLIP_XCOOR3_clipen_src(data)                                              ((0x01000000&(data))>>24)
#define SE_CLIP_XCOOR3_get_clipen(data)                                              ((0x01000000&(data))>>24)
#define SE_CLIP_XCOOR3_xmin_shift                                                    (12)
#define SE_CLIP_XCOOR3_xmin_mask                                                     (0x00FFF000)
#define SE_CLIP_XCOOR3_xmin(data)                                                    (0x00FFF000&((data)<<12))
#define SE_CLIP_XCOOR3_xmin_src(data)                                                ((0x00FFF000&(data))>>12)
#define SE_CLIP_XCOOR3_get_xmin(data)                                                ((0x00FFF000&(data))>>12)
#define SE_CLIP_XCOOR3_xmax_shift                                                    (0)
#define SE_CLIP_XCOOR3_xmax_mask                                                     (0x00000FFF)
#define SE_CLIP_XCOOR3_xmax(data)                                                    (0x00000FFF&((data)<<0))
#define SE_CLIP_XCOOR3_xmax_src(data)                                                ((0x00000FFF&(data))>>0)
#define SE_CLIP_XCOOR3_get_xmax(data)                                                ((0x00000FFF&(data))>>0)


#define SE_CLIP_YCOOR3_0                                                             0x1800C178
#define SE_CLIP_YCOOR3_1                                                             0x1800C17C
#define SE_CLIP_YCOOR3_2                                                             0x1800C180
#define SE_CLIP_YCOOR3_3                                                             0x1800C184
#define SE_CLIP_YCOOR3_0_reg_addr                                                    "0xB800C178"
#define SE_CLIP_YCOOR3_1_reg_addr                                                    "0xB800C17C"
#define SE_CLIP_YCOOR3_2_reg_addr                                                    "0xB800C180"
#define SE_CLIP_YCOOR3_3_reg_addr                                                    "0xB800C184"
#define SE_CLIP_YCOOR3_0_reg                                                         0xB800C178
#define SE_CLIP_YCOOR3_1_reg                                                         0xB800C17C
#define SE_CLIP_YCOOR3_2_reg                                                         0xB800C180
#define SE_CLIP_YCOOR3_3_reg                                                         0xB800C184
#define set_SE_CLIP_YCOOR3_0_reg(data)   (*((volatile unsigned int*) SE_CLIP_YCOOR3_0_reg)=data)
#define set_SE_CLIP_YCOOR3_1_reg(data)   (*((volatile unsigned int*) SE_CLIP_YCOOR3_1_reg)=data)
#define set_SE_CLIP_YCOOR3_2_reg(data)   (*((volatile unsigned int*) SE_CLIP_YCOOR3_2_reg)=data)
#define set_SE_CLIP_YCOOR3_3_reg(data)   (*((volatile unsigned int*) SE_CLIP_YCOOR3_3_reg)=data)
#define get_SE_CLIP_YCOOR3_0_reg   (*((volatile unsigned int*) SE_CLIP_YCOOR3_0_reg))
#define get_SE_CLIP_YCOOR3_1_reg   (*((volatile unsigned int*) SE_CLIP_YCOOR3_1_reg))
#define get_SE_CLIP_YCOOR3_2_reg   (*((volatile unsigned int*) SE_CLIP_YCOOR3_2_reg))
#define get_SE_CLIP_YCOOR3_3_reg   (*((volatile unsigned int*) SE_CLIP_YCOOR3_3_reg))
#define SE_CLIP_YCOOR3_0_inst_adr                                                    "0x005E"
#define SE_CLIP_YCOOR3_1_inst_adr                                                    "0x005F"
#define SE_CLIP_YCOOR3_2_inst_adr                                                    "0x0060"
#define SE_CLIP_YCOOR3_3_inst_adr                                                    "0x0061"
#define SE_CLIP_YCOOR3_0_inst                                                        0x005E
#define SE_CLIP_YCOOR3_1_inst                                                        0x005F
#define SE_CLIP_YCOOR3_2_inst                                                        0x0060
#define SE_CLIP_YCOOR3_3_inst                                                        0x0061
#define SE_CLIP_YCOOR3_ymin_shift                                                    (12)
#define SE_CLIP_YCOOR3_ymin_mask                                                     (0x00FFF000)
#define SE_CLIP_YCOOR3_ymin(data)                                                    (0x00FFF000&((data)<<12))
#define SE_CLIP_YCOOR3_ymin_src(data)                                                ((0x00FFF000&(data))>>12)
#define SE_CLIP_YCOOR3_get_ymin(data)                                                ((0x00FFF000&(data))>>12)
#define SE_CLIP_YCOOR3_ymax_shift                                                    (0)
#define SE_CLIP_YCOOR3_ymax_mask                                                     (0x00000FFF)
#define SE_CLIP_YCOOR3_ymax(data)                                                    (0x00000FFF&((data)<<0))
#define SE_CLIP_YCOOR3_ymax_src(data)                                                ((0x00000FFF&(data))>>0)
#define SE_CLIP_YCOOR3_get_ymax(data)                                                ((0x00000FFF&(data))>>0)


#define SE_CLUT_LOCK_ST                                                              0x1800C4C8
#define SE_CLUT_LOCK_ST_reg_addr                                                     "0xB800C4C8"
#define SE_CLUT_LOCK_ST_reg                                                          0xB800C4C8
#define set_SE_CLUT_LOCK_ST_reg(data)   (*((volatile unsigned int*) SE_CLUT_LOCK_ST_reg)=data)
#define get_SE_CLUT_LOCK_ST_reg   (*((volatile unsigned int*) SE_CLUT_LOCK_ST_reg))
#define SE_CLUT_LOCK_ST_inst_adr                                                     "0x0032"
#define SE_CLUT_LOCK_ST_inst                                                         0x0032
#define SE_CLUT_LOCK_ST_clut_lock_st_shift                                           (0)
#define SE_CLUT_LOCK_ST_clut_lock_st_mask                                            (0x00000003)
#define SE_CLUT_LOCK_ST_clut_lock_st(data)                                           (0x00000003&((data)<<0))
#define SE_CLUT_LOCK_ST_clut_lock_st_src(data)                                       ((0x00000003&(data))>>0)
#define SE_CLUT_LOCK_ST_get_clut_lock_st(data)                                       ((0x00000003&(data))>>0)


#define SE_CONVSCALING_0                                                             0x1800C188
#define SE_CONVSCALING_1                                                             0x1800C18C
#define SE_CONVSCALING_2                                                             0x1800C190
#define SE_CONVSCALING_0_reg_addr                                                    "0xB800C188"
#define SE_CONVSCALING_1_reg_addr                                                    "0xB800C18C"
#define SE_CONVSCALING_2_reg_addr                                                    "0xB800C190"
#define SE_CONVSCALING_0_reg                                                         0xB800C188
#define SE_CONVSCALING_1_reg                                                         0xB800C18C
#define SE_CONVSCALING_2_reg                                                         0xB800C190
#define set_SE_CONVSCALING_0_reg(data)   (*((volatile unsigned int*) SE_CONVSCALING_0_reg)=data)
#define set_SE_CONVSCALING_1_reg(data)   (*((volatile unsigned int*) SE_CONVSCALING_1_reg)=data)
#define set_SE_CONVSCALING_2_reg(data)   (*((volatile unsigned int*) SE_CONVSCALING_2_reg)=data)
#define get_SE_CONVSCALING_0_reg   (*((volatile unsigned int*) SE_CONVSCALING_0_reg))
#define get_SE_CONVSCALING_1_reg   (*((volatile unsigned int*) SE_CONVSCALING_1_reg))
#define get_SE_CONVSCALING_2_reg   (*((volatile unsigned int*) SE_CONVSCALING_2_reg))
#define SE_CONVSCALING_0_inst_adr                                                    "0x0062"
#define SE_CONVSCALING_1_inst_adr                                                    "0x0063"
#define SE_CONVSCALING_2_inst_adr                                                    "0x0064"
#define SE_CONVSCALING_0_inst                                                        0x0062
#define SE_CONVSCALING_1_inst                                                        0x0063
#define SE_CONVSCALING_2_inst                                                        0x0064
#define SE_CONVSCALING_hdown_shift                                                   (3)
#define SE_CONVSCALING_hdown_mask                                                    (0x00000008)
#define SE_CONVSCALING_hdown(data)                                                   (0x00000008&((data)<<3))
#define SE_CONVSCALING_hdown_src(data)                                               ((0x00000008&(data))>>3)
#define SE_CONVSCALING_get_hdown(data)                                               ((0x00000008&(data))>>3)
#define SE_CONVSCALING_vdown_shift                                                   (2)
#define SE_CONVSCALING_vdown_mask                                                    (0x00000004)
#define SE_CONVSCALING_vdown(data)                                                   (0x00000004&((data)<<2))
#define SE_CONVSCALING_vdown_src(data)                                               ((0x00000004&(data))>>2)
#define SE_CONVSCALING_get_vdown(data)                                               ((0x00000004&(data))>>2)
#define SE_CONVSCALING_hup_shift                                                     (1)
#define SE_CONVSCALING_hup_mask                                                      (0x00000002)
#define SE_CONVSCALING_hup(data)                                                     (0x00000002&((data)<<1))
#define SE_CONVSCALING_hup_src(data)                                                 ((0x00000002&(data))>>1)
#define SE_CONVSCALING_get_hup(data)                                                 ((0x00000002&(data))>>1)
#define SE_CONVSCALING_vup_shift                                                     (0)
#define SE_CONVSCALING_vup_mask                                                      (0x00000001)
#define SE_CONVSCALING_vup(data)                                                     (0x00000001&((data)<<0))
#define SE_CONVSCALING_vup_src(data)                                                 ((0x00000001&(data))>>0)
#define SE_CONVSCALING_get_vup(data)                                                 ((0x00000001&(data))>>0)


#define SE_CONVCOEF1_0                                                               0x1800C194
#define SE_CONVCOEF1_1                                                               0x1800C198
#define SE_CONVCOEF1_2                                                               0x1800C19C
#define SE_CONVCOEF1_0_reg_addr                                                      "0xB800C194"
#define SE_CONVCOEF1_1_reg_addr                                                      "0xB800C198"
#define SE_CONVCOEF1_2_reg_addr                                                      "0xB800C19C"
#define SE_CONVCOEF1_0_reg                                                           0xB800C194
#define SE_CONVCOEF1_1_reg                                                           0xB800C198
#define SE_CONVCOEF1_2_reg                                                           0xB800C19C
#define set_SE_CONVCOEF1_0_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF1_0_reg)=data)
#define set_SE_CONVCOEF1_1_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF1_1_reg)=data)
#define set_SE_CONVCOEF1_2_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF1_2_reg)=data)
#define get_SE_CONVCOEF1_0_reg   (*((volatile unsigned int*) SE_CONVCOEF1_0_reg))
#define get_SE_CONVCOEF1_1_reg   (*((volatile unsigned int*) SE_CONVCOEF1_1_reg))
#define get_SE_CONVCOEF1_2_reg   (*((volatile unsigned int*) SE_CONVCOEF1_2_reg))
#define SE_CONVCOEF1_0_inst_adr                                                      "0x0065"
#define SE_CONVCOEF1_1_inst_adr                                                      "0x0066"
#define SE_CONVCOEF1_2_inst_adr                                                      "0x0067"
#define SE_CONVCOEF1_0_inst                                                          0x0065
#define SE_CONVCOEF1_1_inst                                                          0x0066
#define SE_CONVCOEF1_2_inst                                                          0x0067
#define SE_CONVCOEF1_m01_shift                                                       (13)
#define SE_CONVCOEF1_m01_mask                                                        (0x03FFE000)
#define SE_CONVCOEF1_m01(data)                                                       (0x03FFE000&((data)<<13))
#define SE_CONVCOEF1_m01_src(data)                                                   ((0x03FFE000&(data))>>13)
#define SE_CONVCOEF1_get_m01(data)                                                   ((0x03FFE000&(data))>>13)
#define SE_CONVCOEF1_m00_shift                                                       (0)
#define SE_CONVCOEF1_m00_mask                                                        (0x00001FFF)
#define SE_CONVCOEF1_m00(data)                                                       (0x00001FFF&((data)<<0))
#define SE_CONVCOEF1_m00_src(data)                                                   ((0x00001FFF&(data))>>0)
#define SE_CONVCOEF1_get_m00(data)                                                   ((0x00001FFF&(data))>>0)


#define SE_CONVCOEF2_0                                                               0x1800C1A0
#define SE_CONVCOEF2_1                                                               0x1800C1A4
#define SE_CONVCOEF2_2                                                               0x1800C1A8
#define SE_CONVCOEF2_0_reg_addr                                                      "0xB800C1A0"
#define SE_CONVCOEF2_1_reg_addr                                                      "0xB800C1A4"
#define SE_CONVCOEF2_2_reg_addr                                                      "0xB800C1A8"
#define SE_CONVCOEF2_0_reg                                                           0xB800C1A0
#define SE_CONVCOEF2_1_reg                                                           0xB800C1A4
#define SE_CONVCOEF2_2_reg                                                           0xB800C1A8
#define set_SE_CONVCOEF2_0_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF2_0_reg)=data)
#define set_SE_CONVCOEF2_1_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF2_1_reg)=data)
#define set_SE_CONVCOEF2_2_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF2_2_reg)=data)
#define get_SE_CONVCOEF2_0_reg   (*((volatile unsigned int*) SE_CONVCOEF2_0_reg))
#define get_SE_CONVCOEF2_1_reg   (*((volatile unsigned int*) SE_CONVCOEF2_1_reg))
#define get_SE_CONVCOEF2_2_reg   (*((volatile unsigned int*) SE_CONVCOEF2_2_reg))
#define SE_CONVCOEF2_0_inst_adr                                                      "0x0068"
#define SE_CONVCOEF2_1_inst_adr                                                      "0x0069"
#define SE_CONVCOEF2_2_inst_adr                                                      "0x006A"
#define SE_CONVCOEF2_0_inst                                                          0x0068
#define SE_CONVCOEF2_1_inst                                                          0x0069
#define SE_CONVCOEF2_2_inst                                                          0x006A
#define SE_CONVCOEF2_m10_shift                                                       (13)
#define SE_CONVCOEF2_m10_mask                                                        (0x03FFE000)
#define SE_CONVCOEF2_m10(data)                                                       (0x03FFE000&((data)<<13))
#define SE_CONVCOEF2_m10_src(data)                                                   ((0x03FFE000&(data))>>13)
#define SE_CONVCOEF2_get_m10(data)                                                   ((0x03FFE000&(data))>>13)
#define SE_CONVCOEF2_m02_shift                                                       (0)
#define SE_CONVCOEF2_m02_mask                                                        (0x00001FFF)
#define SE_CONVCOEF2_m02(data)                                                       (0x00001FFF&((data)<<0))
#define SE_CONVCOEF2_m02_src(data)                                                   ((0x00001FFF&(data))>>0)
#define SE_CONVCOEF2_get_m02(data)                                                   ((0x00001FFF&(data))>>0)


#define SE_CONVCOEF3_0                                                               0x1800C1AC
#define SE_CONVCOEF3_1                                                               0x1800C1B0
#define SE_CONVCOEF3_2                                                               0x1800C1B4
#define SE_CONVCOEF3_0_reg_addr                                                      "0xB800C1AC"
#define SE_CONVCOEF3_1_reg_addr                                                      "0xB800C1B0"
#define SE_CONVCOEF3_2_reg_addr                                                      "0xB800C1B4"
#define SE_CONVCOEF3_0_reg                                                           0xB800C1AC
#define SE_CONVCOEF3_1_reg                                                           0xB800C1B0
#define SE_CONVCOEF3_2_reg                                                           0xB800C1B4
#define set_SE_CONVCOEF3_0_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF3_0_reg)=data)
#define set_SE_CONVCOEF3_1_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF3_1_reg)=data)
#define set_SE_CONVCOEF3_2_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF3_2_reg)=data)
#define get_SE_CONVCOEF3_0_reg   (*((volatile unsigned int*) SE_CONVCOEF3_0_reg))
#define get_SE_CONVCOEF3_1_reg   (*((volatile unsigned int*) SE_CONVCOEF3_1_reg))
#define get_SE_CONVCOEF3_2_reg   (*((volatile unsigned int*) SE_CONVCOEF3_2_reg))
#define SE_CONVCOEF3_0_inst_adr                                                      "0x006B"
#define SE_CONVCOEF3_1_inst_adr                                                      "0x006C"
#define SE_CONVCOEF3_2_inst_adr                                                      "0x006D"
#define SE_CONVCOEF3_0_inst                                                          0x006B
#define SE_CONVCOEF3_1_inst                                                          0x006C
#define SE_CONVCOEF3_2_inst                                                          0x006D
#define SE_CONVCOEF3_m12_shift                                                       (13)
#define SE_CONVCOEF3_m12_mask                                                        (0x03FFE000)
#define SE_CONVCOEF3_m12(data)                                                       (0x03FFE000&((data)<<13))
#define SE_CONVCOEF3_m12_src(data)                                                   ((0x03FFE000&(data))>>13)
#define SE_CONVCOEF3_get_m12(data)                                                   ((0x03FFE000&(data))>>13)
#define SE_CONVCOEF3_m11_shift                                                       (0)
#define SE_CONVCOEF3_m11_mask                                                        (0x00001FFF)
#define SE_CONVCOEF3_m11(data)                                                       (0x00001FFF&((data)<<0))
#define SE_CONVCOEF3_m11_src(data)                                                   ((0x00001FFF&(data))>>0)
#define SE_CONVCOEF3_get_m11(data)                                                   ((0x00001FFF&(data))>>0)


#define SE_CONVCOEF4_0                                                               0x1800C1B8
#define SE_CONVCOEF4_1                                                               0x1800C1BC
#define SE_CONVCOEF4_2                                                               0x1800C1C0
#define SE_CONVCOEF4_0_reg_addr                                                      "0xB800C1B8"
#define SE_CONVCOEF4_1_reg_addr                                                      "0xB800C1BC"
#define SE_CONVCOEF4_2_reg_addr                                                      "0xB800C1C0"
#define SE_CONVCOEF4_0_reg                                                           0xB800C1B8
#define SE_CONVCOEF4_1_reg                                                           0xB800C1BC
#define SE_CONVCOEF4_2_reg                                                           0xB800C1C0
#define set_SE_CONVCOEF4_0_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF4_0_reg)=data)
#define set_SE_CONVCOEF4_1_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF4_1_reg)=data)
#define set_SE_CONVCOEF4_2_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF4_2_reg)=data)
#define get_SE_CONVCOEF4_0_reg   (*((volatile unsigned int*) SE_CONVCOEF4_0_reg))
#define get_SE_CONVCOEF4_1_reg   (*((volatile unsigned int*) SE_CONVCOEF4_1_reg))
#define get_SE_CONVCOEF4_2_reg   (*((volatile unsigned int*) SE_CONVCOEF4_2_reg))
#define SE_CONVCOEF4_0_inst_adr                                                      "0x006E"
#define SE_CONVCOEF4_1_inst_adr                                                      "0x006F"
#define SE_CONVCOEF4_2_inst_adr                                                      "0x0070"
#define SE_CONVCOEF4_0_inst                                                          0x006E
#define SE_CONVCOEF4_1_inst                                                          0x006F
#define SE_CONVCOEF4_2_inst                                                          0x0070
#define SE_CONVCOEF4_m21_shift                                                       (13)
#define SE_CONVCOEF4_m21_mask                                                        (0x03FFE000)
#define SE_CONVCOEF4_m21(data)                                                       (0x03FFE000&((data)<<13))
#define SE_CONVCOEF4_m21_src(data)                                                   ((0x03FFE000&(data))>>13)
#define SE_CONVCOEF4_get_m21(data)                                                   ((0x03FFE000&(data))>>13)
#define SE_CONVCOEF4_m20_shift                                                       (0)
#define SE_CONVCOEF4_m20_mask                                                        (0x00001FFF)
#define SE_CONVCOEF4_m20(data)                                                       (0x00001FFF&((data)<<0))
#define SE_CONVCOEF4_m20_src(data)                                                   ((0x00001FFF&(data))>>0)
#define SE_CONVCOEF4_get_m20(data)                                                   ((0x00001FFF&(data))>>0)


#define SE_CONVCOEF5_0                                                               0x1800C1C4
#define SE_CONVCOEF5_1                                                               0x1800C1C8
#define SE_CONVCOEF5_2                                                               0x1800C1CC
#define SE_CONVCOEF5_0_reg_addr                                                      "0xB800C1C4"
#define SE_CONVCOEF5_1_reg_addr                                                      "0xB800C1C8"
#define SE_CONVCOEF5_2_reg_addr                                                      "0xB800C1CC"
#define SE_CONVCOEF5_0_reg                                                           0xB800C1C4
#define SE_CONVCOEF5_1_reg                                                           0xB800C1C8
#define SE_CONVCOEF5_2_reg                                                           0xB800C1CC
#define set_SE_CONVCOEF5_0_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF5_0_reg)=data)
#define set_SE_CONVCOEF5_1_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF5_1_reg)=data)
#define set_SE_CONVCOEF5_2_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF5_2_reg)=data)
#define get_SE_CONVCOEF5_0_reg   (*((volatile unsigned int*) SE_CONVCOEF5_0_reg))
#define get_SE_CONVCOEF5_1_reg   (*((volatile unsigned int*) SE_CONVCOEF5_1_reg))
#define get_SE_CONVCOEF5_2_reg   (*((volatile unsigned int*) SE_CONVCOEF5_2_reg))
#define SE_CONVCOEF5_0_inst_adr                                                      "0x0071"
#define SE_CONVCOEF5_1_inst_adr                                                      "0x0072"
#define SE_CONVCOEF5_2_inst_adr                                                      "0x0073"
#define SE_CONVCOEF5_0_inst                                                          0x0071
#define SE_CONVCOEF5_1_inst                                                          0x0072
#define SE_CONVCOEF5_2_inst                                                          0x0073
#define SE_CONVCOEF5_m22_shift                                                       (0)
#define SE_CONVCOEF5_m22_mask                                                        (0x00001FFF)
#define SE_CONVCOEF5_m22(data)                                                       (0x00001FFF&((data)<<0))
#define SE_CONVCOEF5_m22_src(data)                                                   ((0x00001FFF&(data))>>0)
#define SE_CONVCOEF5_get_m22(data)                                                   ((0x00001FFF&(data))>>0)


#define SE_CONVCOEF6_0                                                               0x1800C1D0
#define SE_CONVCOEF6_1                                                               0x1800C1D4
#define SE_CONVCOEF6_2                                                               0x1800C1D8
#define SE_CONVCOEF6_0_reg_addr                                                      "0xB800C1D0"
#define SE_CONVCOEF6_1_reg_addr                                                      "0xB800C1D4"
#define SE_CONVCOEF6_2_reg_addr                                                      "0xB800C1D8"
#define SE_CONVCOEF6_0_reg                                                           0xB800C1D0
#define SE_CONVCOEF6_1_reg                                                           0xB800C1D4
#define SE_CONVCOEF6_2_reg                                                           0xB800C1D8
#define set_SE_CONVCOEF6_0_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF6_0_reg)=data)
#define set_SE_CONVCOEF6_1_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF6_1_reg)=data)
#define set_SE_CONVCOEF6_2_reg(data)   (*((volatile unsigned int*) SE_CONVCOEF6_2_reg)=data)
#define get_SE_CONVCOEF6_0_reg   (*((volatile unsigned int*) SE_CONVCOEF6_0_reg))
#define get_SE_CONVCOEF6_1_reg   (*((volatile unsigned int*) SE_CONVCOEF6_1_reg))
#define get_SE_CONVCOEF6_2_reg   (*((volatile unsigned int*) SE_CONVCOEF6_2_reg))
#define SE_CONVCOEF6_0_inst_adr                                                      "0x0074"
#define SE_CONVCOEF6_1_inst_adr                                                      "0x0075"
#define SE_CONVCOEF6_2_inst_adr                                                      "0x0076"
#define SE_CONVCOEF6_0_inst                                                          0x0074
#define SE_CONVCOEF6_1_inst                                                          0x0075
#define SE_CONVCOEF6_2_inst                                                          0x0076
#define SE_CONVCOEF6_a2_shift                                                        (20)
#define SE_CONVCOEF6_a2_mask                                                         (0x3FF00000)
#define SE_CONVCOEF6_a2(data)                                                        (0x3FF00000&((data)<<20))
#define SE_CONVCOEF6_a2_src(data)                                                    ((0x3FF00000&(data))>>20)
#define SE_CONVCOEF6_get_a2(data)                                                    ((0x3FF00000&(data))>>20)
#define SE_CONVCOEF6_a1_shift                                                        (10)
#define SE_CONVCOEF6_a1_mask                                                         (0x000FFC00)
#define SE_CONVCOEF6_a1(data)                                                        (0x000FFC00&((data)<<10))
#define SE_CONVCOEF6_a1_src(data)                                                    ((0x000FFC00&(data))>>10)
#define SE_CONVCOEF6_get_a1(data)                                                    ((0x000FFC00&(data))>>10)
#define SE_CONVCOEF6_a0_shift                                                        (0)
#define SE_CONVCOEF6_a0_mask                                                         (0x000003FF)
#define SE_CONVCOEF6_a0(data)                                                        (0x000003FF&((data)<<0))
#define SE_CONVCOEF6_a0_src(data)                                                    ((0x000003FF&(data))>>0)
#define SE_CONVCOEF6_get_a0(data)                                                    ((0x000003FF&(data))>>0)


#define SE_FCV_BITBLIT_COLOR_KEY_0                                                   0x1800C4BC
#define SE_FCV_BITBLIT_COLOR_KEY_1                                                   0x1800C4C0
#define SE_FCV_BITBLIT_COLOR_KEY_2                                                   0x1800C4C4
#define SE_FCV_BITBLIT_COLOR_KEY_0_reg_addr                                          "0xB800C4BC"
#define SE_FCV_BITBLIT_COLOR_KEY_1_reg_addr                                          "0xB800C4C0"
#define SE_FCV_BITBLIT_COLOR_KEY_2_reg_addr                                          "0xB800C4C4"
#define SE_FCV_BITBLIT_COLOR_KEY_0_reg                                               0xB800C4BC
#define SE_FCV_BITBLIT_COLOR_KEY_1_reg                                               0xB800C4C0
#define SE_FCV_BITBLIT_COLOR_KEY_2_reg                                               0xB800C4C4
#define set_SE_FCV_BITBLIT_COLOR_KEY_0_reg(data)   (*((volatile unsigned int*) SE_FCV_BITBLIT_COLOR_KEY_0_reg)=data)
#define set_SE_FCV_BITBLIT_COLOR_KEY_1_reg(data)   (*((volatile unsigned int*) SE_FCV_BITBLIT_COLOR_KEY_1_reg)=data)
#define set_SE_FCV_BITBLIT_COLOR_KEY_2_reg(data)   (*((volatile unsigned int*) SE_FCV_BITBLIT_COLOR_KEY_2_reg)=data)
#define get_SE_FCV_BITBLIT_COLOR_KEY_0_reg   (*((volatile unsigned int*) SE_FCV_BITBLIT_COLOR_KEY_0_reg))
#define get_SE_FCV_BITBLIT_COLOR_KEY_1_reg   (*((volatile unsigned int*) SE_FCV_BITBLIT_COLOR_KEY_1_reg))
#define get_SE_FCV_BITBLIT_COLOR_KEY_2_reg   (*((volatile unsigned int*) SE_FCV_BITBLIT_COLOR_KEY_2_reg))
#define SE_FCV_BITBLIT_COLOR_KEY_0_inst_adr                                          "0x002F"
#define SE_FCV_BITBLIT_COLOR_KEY_1_inst_adr                                          "0x0030"
#define SE_FCV_BITBLIT_COLOR_KEY_2_inst_adr                                          "0x0031"
#define SE_FCV_BITBLIT_COLOR_KEY_0_inst                                              0x002F
#define SE_FCV_BITBLIT_COLOR_KEY_1_inst                                              0x0030
#define SE_FCV_BITBLIT_COLOR_KEY_2_inst                                              0x0031
#define SE_FCV_BITBLIT_COLOR_KEY_color_key_shift                                     (0)
#define SE_FCV_BITBLIT_COLOR_KEY_color_key_mask                                      (0x00FFFFFF)
#define SE_FCV_BITBLIT_COLOR_KEY_color_key(data)                                     (0x00FFFFFF&((data)<<0))
#define SE_FCV_BITBLIT_COLOR_KEY_color_key_src(data)                                 ((0x00FFFFFF&(data))>>0)
#define SE_FCV_BITBLIT_COLOR_KEY_get_color_key(data)                                 ((0x00FFFFFF&(data))>>0)


#define SE_SRC_CLR_RED_0                                                             0x1800C51C
#define SE_SRC_CLR_RED_1                                                             0x1800C520
#define SE_SRC_CLR_RED_2                                                             0x1800C524
#define SE_SRC_CLR_RED_0_reg_addr                                                    "0xB800C51C"
#define SE_SRC_CLR_RED_1_reg_addr                                                    "0xB800C520"
#define SE_SRC_CLR_RED_2_reg_addr                                                    "0xB800C524"
#define SE_SRC_CLR_RED_0_reg                                                         0xB800C51C
#define SE_SRC_CLR_RED_1_reg                                                         0xB800C520
#define SE_SRC_CLR_RED_2_reg                                                         0xB800C524
#define set_SE_SRC_CLR_RED_0_reg(data)   (*((volatile unsigned int*) SE_SRC_CLR_RED_0_reg)=data)
#define set_SE_SRC_CLR_RED_1_reg(data)   (*((volatile unsigned int*) SE_SRC_CLR_RED_1_reg)=data)
#define set_SE_SRC_CLR_RED_2_reg(data)   (*((volatile unsigned int*) SE_SRC_CLR_RED_2_reg)=data)
#define get_SE_SRC_CLR_RED_0_reg   (*((volatile unsigned int*) SE_SRC_CLR_RED_0_reg))
#define get_SE_SRC_CLR_RED_1_reg   (*((volatile unsigned int*) SE_SRC_CLR_RED_1_reg))
#define get_SE_SRC_CLR_RED_2_reg   (*((volatile unsigned int*) SE_SRC_CLR_RED_2_reg))
#define SE_SRC_CLR_RED_0_inst_adr                                                    "0x0047"
#define SE_SRC_CLR_RED_1_inst_adr                                                    "0x0048"
#define SE_SRC_CLR_RED_2_inst_adr                                                    "0x0049"
#define SE_SRC_CLR_RED_0_inst                                                        0x0047
#define SE_SRC_CLR_RED_1_inst                                                        0x0048
#define SE_SRC_CLR_RED_2_inst                                                        0x0049
#define SE_SRC_CLR_RED_src_clr_add_red_shift                                         (16)
#define SE_SRC_CLR_RED_src_clr_add_red_mask                                          (0x01FF0000)
#define SE_SRC_CLR_RED_src_clr_add_red(data)                                         (0x01FF0000&((data)<<16))
#define SE_SRC_CLR_RED_src_clr_add_red_src(data)                                     ((0x01FF0000&(data))>>16)
#define SE_SRC_CLR_RED_get_src_clr_add_red(data)                                     ((0x01FF0000&(data))>>16)
#define SE_SRC_CLR_RED_src_clr_mul_red_shift                                         (0)
#define SE_SRC_CLR_RED_src_clr_mul_red_mask                                          (0x000001FF)
#define SE_SRC_CLR_RED_src_clr_mul_red(data)                                         (0x000001FF&((data)<<0))
#define SE_SRC_CLR_RED_src_clr_mul_red_src(data)                                     ((0x000001FF&(data))>>0)
#define SE_SRC_CLR_RED_get_src_clr_mul_red(data)                                     ((0x000001FF&(data))>>0)


#define SE_SRC_CLR_GREEN_0                                                           0x1800C528
#define SE_SRC_CLR_GREEN_1                                                           0x1800C52C
#define SE_SRC_CLR_GREEN_2                                                           0x1800C530
#define SE_SRC_CLR_GREEN_0_reg_addr                                                  "0xB800C528"
#define SE_SRC_CLR_GREEN_1_reg_addr                                                  "0xB800C52C"
#define SE_SRC_CLR_GREEN_2_reg_addr                                                  "0xB800C530"
#define SE_SRC_CLR_GREEN_0_reg                                                       0xB800C528
#define SE_SRC_CLR_GREEN_1_reg                                                       0xB800C52C
#define SE_SRC_CLR_GREEN_2_reg                                                       0xB800C530
#define set_SE_SRC_CLR_GREEN_0_reg(data)   (*((volatile unsigned int*) SE_SRC_CLR_GREEN_0_reg)=data)
#define set_SE_SRC_CLR_GREEN_1_reg(data)   (*((volatile unsigned int*) SE_SRC_CLR_GREEN_1_reg)=data)
#define set_SE_SRC_CLR_GREEN_2_reg(data)   (*((volatile unsigned int*) SE_SRC_CLR_GREEN_2_reg)=data)
#define get_SE_SRC_CLR_GREEN_0_reg   (*((volatile unsigned int*) SE_SRC_CLR_GREEN_0_reg))
#define get_SE_SRC_CLR_GREEN_1_reg   (*((volatile unsigned int*) SE_SRC_CLR_GREEN_1_reg))
#define get_SE_SRC_CLR_GREEN_2_reg   (*((volatile unsigned int*) SE_SRC_CLR_GREEN_2_reg))
#define SE_SRC_CLR_GREEN_0_inst_adr                                                  "0x004A"
#define SE_SRC_CLR_GREEN_1_inst_adr                                                  "0x004B"
#define SE_SRC_CLR_GREEN_2_inst_adr                                                  "0x004C"
#define SE_SRC_CLR_GREEN_0_inst                                                      0x004A
#define SE_SRC_CLR_GREEN_1_inst                                                      0x004B
#define SE_SRC_CLR_GREEN_2_inst                                                      0x004C
#define SE_SRC_CLR_GREEN_src_clr_add_green_shift                                     (16)
#define SE_SRC_CLR_GREEN_src_clr_add_green_mask                                      (0x01FF0000)
#define SE_SRC_CLR_GREEN_src_clr_add_green(data)                                     (0x01FF0000&((data)<<16))
#define SE_SRC_CLR_GREEN_src_clr_add_green_src(data)                                 ((0x01FF0000&(data))>>16)
#define SE_SRC_CLR_GREEN_get_src_clr_add_green(data)                                 ((0x01FF0000&(data))>>16)
#define SE_SRC_CLR_GREEN_src_clr_mul_green_shift                                     (0)
#define SE_SRC_CLR_GREEN_src_clr_mul_green_mask                                      (0x000001FF)
#define SE_SRC_CLR_GREEN_src_clr_mul_green(data)                                     (0x000001FF&((data)<<0))
#define SE_SRC_CLR_GREEN_src_clr_mul_green_src(data)                                 ((0x000001FF&(data))>>0)
#define SE_SRC_CLR_GREEN_get_src_clr_mul_green(data)                                 ((0x000001FF&(data))>>0)


#define SE_SRC_CLR_BLUE_0                                                            0x1800C534
#define SE_SRC_CLR_BLUE_1                                                            0x1800C538
#define SE_SRC_CLR_BLUE_2                                                            0x1800C53C
#define SE_SRC_CLR_BLUE_0_reg_addr                                                   "0xB800C534"
#define SE_SRC_CLR_BLUE_1_reg_addr                                                   "0xB800C538"
#define SE_SRC_CLR_BLUE_2_reg_addr                                                   "0xB800C53C"
#define SE_SRC_CLR_BLUE_0_reg                                                        0xB800C534
#define SE_SRC_CLR_BLUE_1_reg                                                        0xB800C538
#define SE_SRC_CLR_BLUE_2_reg                                                        0xB800C53C
#define set_SE_SRC_CLR_BLUE_0_reg(data)   (*((volatile unsigned int*) SE_SRC_CLR_BLUE_0_reg)=data)
#define set_SE_SRC_CLR_BLUE_1_reg(data)   (*((volatile unsigned int*) SE_SRC_CLR_BLUE_1_reg)=data)
#define set_SE_SRC_CLR_BLUE_2_reg(data)   (*((volatile unsigned int*) SE_SRC_CLR_BLUE_2_reg)=data)
#define get_SE_SRC_CLR_BLUE_0_reg   (*((volatile unsigned int*) SE_SRC_CLR_BLUE_0_reg))
#define get_SE_SRC_CLR_BLUE_1_reg   (*((volatile unsigned int*) SE_SRC_CLR_BLUE_1_reg))
#define get_SE_SRC_CLR_BLUE_2_reg   (*((volatile unsigned int*) SE_SRC_CLR_BLUE_2_reg))
#define SE_SRC_CLR_BLUE_0_inst_adr                                                   "0x004D"
#define SE_SRC_CLR_BLUE_1_inst_adr                                                   "0x004E"
#define SE_SRC_CLR_BLUE_2_inst_adr                                                   "0x004F"
#define SE_SRC_CLR_BLUE_0_inst                                                       0x004D
#define SE_SRC_CLR_BLUE_1_inst                                                       0x004E
#define SE_SRC_CLR_BLUE_2_inst                                                       0x004F
#define SE_SRC_CLR_BLUE_src_clr_add_blue_shift                                       (16)
#define SE_SRC_CLR_BLUE_src_clr_add_blue_mask                                        (0x01FF0000)
#define SE_SRC_CLR_BLUE_src_clr_add_blue(data)                                       (0x01FF0000&((data)<<16))
#define SE_SRC_CLR_BLUE_src_clr_add_blue_src(data)                                   ((0x01FF0000&(data))>>16)
#define SE_SRC_CLR_BLUE_get_src_clr_add_blue(data)                                   ((0x01FF0000&(data))>>16)
#define SE_SRC_CLR_BLUE_src_clr_mul_blue_shift                                       (0)
#define SE_SRC_CLR_BLUE_src_clr_mul_blue_mask                                        (0x000001FF)
#define SE_SRC_CLR_BLUE_src_clr_mul_blue(data)                                       (0x000001FF&((data)<<0))
#define SE_SRC_CLR_BLUE_src_clr_mul_blue_src(data)                                   ((0x000001FF&(data))>>0)
#define SE_SRC_CLR_BLUE_get_src_clr_mul_blue(data)                                   ((0x000001FF&(data))>>0)


#define SE_SRC_CLR_ALPHA_0                                                           0x1800C540
#define SE_SRC_CLR_ALPHA_1                                                           0x1800C544
#define SE_SRC_CLR_ALPHA_2                                                           0x1800C548
#define SE_SRC_CLR_ALPHA_0_reg_addr                                                  "0xB800C540"
#define SE_SRC_CLR_ALPHA_1_reg_addr                                                  "0xB800C544"
#define SE_SRC_CLR_ALPHA_2_reg_addr                                                  "0xB800C548"
#define SE_SRC_CLR_ALPHA_0_reg                                                       0xB800C540
#define SE_SRC_CLR_ALPHA_1_reg                                                       0xB800C544
#define SE_SRC_CLR_ALPHA_2_reg                                                       0xB800C548
#define set_SE_SRC_CLR_ALPHA_0_reg(data)   (*((volatile unsigned int*) SE_SRC_CLR_ALPHA_0_reg)=data)
#define set_SE_SRC_CLR_ALPHA_1_reg(data)   (*((volatile unsigned int*) SE_SRC_CLR_ALPHA_1_reg)=data)
#define set_SE_SRC_CLR_ALPHA_2_reg(data)   (*((volatile unsigned int*) SE_SRC_CLR_ALPHA_2_reg)=data)
#define get_SE_SRC_CLR_ALPHA_0_reg   (*((volatile unsigned int*) SE_SRC_CLR_ALPHA_0_reg))
#define get_SE_SRC_CLR_ALPHA_1_reg   (*((volatile unsigned int*) SE_SRC_CLR_ALPHA_1_reg))
#define get_SE_SRC_CLR_ALPHA_2_reg   (*((volatile unsigned int*) SE_SRC_CLR_ALPHA_2_reg))
#define SE_SRC_CLR_ALPHA_0_inst_adr                                                  "0x0050"
#define SE_SRC_CLR_ALPHA_1_inst_adr                                                  "0x0051"
#define SE_SRC_CLR_ALPHA_2_inst_adr                                                  "0x0052"
#define SE_SRC_CLR_ALPHA_0_inst                                                      0x0050
#define SE_SRC_CLR_ALPHA_1_inst                                                      0x0051
#define SE_SRC_CLR_ALPHA_2_inst                                                      0x0052
#define SE_SRC_CLR_ALPHA_src_clr_add_alpha_shift                                     (16)
#define SE_SRC_CLR_ALPHA_src_clr_add_alpha_mask                                      (0x01FF0000)
#define SE_SRC_CLR_ALPHA_src_clr_add_alpha(data)                                     (0x01FF0000&((data)<<16))
#define SE_SRC_CLR_ALPHA_src_clr_add_alpha_src(data)                                 ((0x01FF0000&(data))>>16)
#define SE_SRC_CLR_ALPHA_get_src_clr_add_alpha(data)                                 ((0x01FF0000&(data))>>16)
#define SE_SRC_CLR_ALPHA_src_clr_mul_alpha_shift                                     (0)
#define SE_SRC_CLR_ALPHA_src_clr_mul_alpha_mask                                      (0x000001FF)
#define SE_SRC_CLR_ALPHA_src_clr_mul_alpha(data)                                     (0x000001FF&((data)<<0))
#define SE_SRC_CLR_ALPHA_src_clr_mul_alpha_src(data)                                 ((0x000001FF&(data))>>0)
#define SE_SRC_CLR_ALPHA_get_src_clr_mul_alpha(data)                                 ((0x000001FF&(data))>>0)


#define SE_SYNC_VO_MARGIN_0                                                          0x1800C4E0
#define SE_SYNC_VO_MARGIN_1                                                          0x1800C4E4
#define SE_SYNC_VO_MARGIN_2                                                          0x1800C4E8
#define SE_SYNC_VO_MARGIN_0_reg_addr                                                 "0xB800C4E0"
#define SE_SYNC_VO_MARGIN_1_reg_addr                                                 "0xB800C4E4"
#define SE_SYNC_VO_MARGIN_2_reg_addr                                                 "0xB800C4E8"
#define SE_SYNC_VO_MARGIN_0_reg                                                      0xB800C4E0
#define SE_SYNC_VO_MARGIN_1_reg                                                      0xB800C4E4
#define SE_SYNC_VO_MARGIN_2_reg                                                      0xB800C4E8
#define set_SE_SYNC_VO_MARGIN_0_reg(data)   (*((volatile unsigned int*) SE_SYNC_VO_MARGIN_0_reg)=data)
#define set_SE_SYNC_VO_MARGIN_1_reg(data)   (*((volatile unsigned int*) SE_SYNC_VO_MARGIN_1_reg)=data)
#define set_SE_SYNC_VO_MARGIN_2_reg(data)   (*((volatile unsigned int*) SE_SYNC_VO_MARGIN_2_reg)=data)
#define get_SE_SYNC_VO_MARGIN_0_reg   (*((volatile unsigned int*) SE_SYNC_VO_MARGIN_0_reg))
#define get_SE_SYNC_VO_MARGIN_1_reg   (*((volatile unsigned int*) SE_SYNC_VO_MARGIN_1_reg))
#define get_SE_SYNC_VO_MARGIN_2_reg   (*((volatile unsigned int*) SE_SYNC_VO_MARGIN_2_reg))
#define SE_SYNC_VO_MARGIN_0_inst_adr                                                 "0x0038"
#define SE_SYNC_VO_MARGIN_1_inst_adr                                                 "0x0039"
#define SE_SYNC_VO_MARGIN_2_inst_adr                                                 "0x003A"
#define SE_SYNC_VO_MARGIN_0_inst                                                     0x0038
#define SE_SYNC_VO_MARGIN_1_inst                                                     0x0039
#define SE_SYNC_VO_MARGIN_2_inst                                                     0x003A
#define SE_SYNC_VO_MARGIN_auto_dir_en_shift                                          (31)
#define SE_SYNC_VO_MARGIN_auto_dir_en_mask                                           (0x80000000)
#define SE_SYNC_VO_MARGIN_auto_dir_en(data)                                          (0x80000000&((data)<<31))
#define SE_SYNC_VO_MARGIN_auto_dir_en_src(data)                                      ((0x80000000&(data))>>31)
#define SE_SYNC_VO_MARGIN_get_auto_dir_en(data)                                      ((0x80000000&(data))>>31)
#define SE_SYNC_VO_MARGIN_vo_plane_shift                                             (30)
#define SE_SYNC_VO_MARGIN_vo_plane_mask                                              (0x40000000)
#define SE_SYNC_VO_MARGIN_vo_plane(data)                                             (0x40000000&((data)<<30))
#define SE_SYNC_VO_MARGIN_vo_plane_src(data)                                         ((0x40000000&(data))>>30)
#define SE_SYNC_VO_MARGIN_get_vo_plane(data)                                         ((0x40000000&(data))>>30)
#define SE_SYNC_VO_MARGIN_before_vo_cur_shift                                        (29)
#define SE_SYNC_VO_MARGIN_before_vo_cur_mask                                         (0x20000000)
#define SE_SYNC_VO_MARGIN_before_vo_cur(data)                                        (0x20000000&((data)<<29))
#define SE_SYNC_VO_MARGIN_before_vo_cur_src(data)                                    ((0x20000000&(data))>>29)
#define SE_SYNC_VO_MARGIN_get_before_vo_cur(data)                                    ((0x20000000&(data))>>29)
#define SE_SYNC_VO_MARGIN_after_vo_cur_shift                                         (28)
#define SE_SYNC_VO_MARGIN_after_vo_cur_mask                                          (0x10000000)
#define SE_SYNC_VO_MARGIN_after_vo_cur(data)                                         (0x10000000&((data)<<28))
#define SE_SYNC_VO_MARGIN_after_vo_cur_src(data)                                     ((0x10000000&(data))>>28)
#define SE_SYNC_VO_MARGIN_get_after_vo_cur(data)                                     ((0x10000000&(data))>>28)
#define SE_SYNC_VO_MARGIN_vbi_shift                                                  (27)
#define SE_SYNC_VO_MARGIN_vbi_mask                                                   (0x08000000)
#define SE_SYNC_VO_MARGIN_vbi(data)                                                  (0x08000000&((data)<<27))
#define SE_SYNC_VO_MARGIN_vbi_src(data)                                              ((0x08000000&(data))>>27)
#define SE_SYNC_VO_MARGIN_get_vbi(data)                                              ((0x08000000&(data))>>27)
#define SE_SYNC_VO_MARGIN_vo_osd_plane_shift                                         (26)
#define SE_SYNC_VO_MARGIN_vo_osd_plane_mask                                          (0x04000000)
#define SE_SYNC_VO_MARGIN_vo_osd_plane(data)                                         (0x04000000&((data)<<26))
#define SE_SYNC_VO_MARGIN_vo_osd_plane_src(data)                                     ((0x04000000&(data))>>26)
#define SE_SYNC_VO_MARGIN_get_vo_osd_plane(data)                                     ((0x04000000&(data))>>26)
#define SE_SYNC_VO_MARGIN_margin_VOtoSE_shift                                        (0)
#define SE_SYNC_VO_MARGIN_margin_VOtoSE_mask                                         (0x00000FFF)
#define SE_SYNC_VO_MARGIN_margin_VOtoSE(data)                                        (0x00000FFF&((data)<<0))
#define SE_SYNC_VO_MARGIN_margin_VOtoSE_src(data)                                    ((0x00000FFF&(data))>>0)
#define SE_SYNC_VO_MARGIN_get_margin_VOtoSE(data)                                    ((0x00000FFF&(data))>>0)


#define SE_SYNC_VO_LOCATION_0                                                        0x1800C4F8
#define SE_SYNC_VO_LOCATION_1                                                        0x1800C4FC
#define SE_SYNC_VO_LOCATION_2                                                        0x1800C500
#define SE_SYNC_VO_LOCATION_0_reg_addr                                               "0xB800C4F8"
#define SE_SYNC_VO_LOCATION_1_reg_addr                                               "0xB800C4FC"
#define SE_SYNC_VO_LOCATION_2_reg_addr                                               "0xB800C500"
#define SE_SYNC_VO_LOCATION_0_reg                                                    0xB800C4F8
#define SE_SYNC_VO_LOCATION_1_reg                                                    0xB800C4FC
#define SE_SYNC_VO_LOCATION_2_reg                                                    0xB800C500
#define set_SE_SYNC_VO_LOCATION_0_reg(data)   (*((volatile unsigned int*) SE_SYNC_VO_LOCATION_0_reg)=data)
#define set_SE_SYNC_VO_LOCATION_1_reg(data)   (*((volatile unsigned int*) SE_SYNC_VO_LOCATION_1_reg)=data)
#define set_SE_SYNC_VO_LOCATION_2_reg(data)   (*((volatile unsigned int*) SE_SYNC_VO_LOCATION_2_reg)=data)
#define get_SE_SYNC_VO_LOCATION_0_reg   (*((volatile unsigned int*) SE_SYNC_VO_LOCATION_0_reg))
#define get_SE_SYNC_VO_LOCATION_1_reg   (*((volatile unsigned int*) SE_SYNC_VO_LOCATION_1_reg))
#define get_SE_SYNC_VO_LOCATION_2_reg   (*((volatile unsigned int*) SE_SYNC_VO_LOCATION_2_reg))
#define SE_SYNC_VO_LOCATION_0_inst_adr                                               "0x003E"
#define SE_SYNC_VO_LOCATION_1_inst_adr                                               "0x003F"
#define SE_SYNC_VO_LOCATION_2_inst_adr                                               "0x0040"
#define SE_SYNC_VO_LOCATION_0_inst                                                   0x003E
#define SE_SYNC_VO_LOCATION_1_inst                                                   0x003F
#define SE_SYNC_VO_LOCATION_2_inst                                                   0x0040
#define SE_SYNC_VO_LOCATION_VO_current_y_shift                                       (0)
#define SE_SYNC_VO_LOCATION_VO_current_y_mask                                        (0x00000FFF)
#define SE_SYNC_VO_LOCATION_VO_current_y(data)                                       (0x00000FFF&((data)<<0))
#define SE_SYNC_VO_LOCATION_VO_current_y_src(data)                                   ((0x00000FFF&(data))>>0)
#define SE_SYNC_VO_LOCATION_get_VO_current_y(data)                                   ((0x00000FFF&(data))>>0)


#define SE_STRETCH_0                                                                 0x1800C1DC
#define SE_STRETCH_1                                                                 0x1800C1E0
#define SE_STRETCH_2                                                                 0x1800C1E4
#define SE_STRETCH_0_reg_addr                                                        "0xB800C1DC"
#define SE_STRETCH_1_reg_addr                                                        "0xB800C1E0"
#define SE_STRETCH_2_reg_addr                                                        "0xB800C1E4"
#define SE_STRETCH_0_reg                                                             0xB800C1DC
#define SE_STRETCH_1_reg                                                             0xB800C1E0
#define SE_STRETCH_2_reg                                                             0xB800C1E4
#define set_SE_STRETCH_0_reg(data)   (*((volatile unsigned int*) SE_STRETCH_0_reg)=data)
#define set_SE_STRETCH_1_reg(data)   (*((volatile unsigned int*) SE_STRETCH_1_reg)=data)
#define set_SE_STRETCH_2_reg(data)   (*((volatile unsigned int*) SE_STRETCH_2_reg)=data)
#define get_SE_STRETCH_0_reg   (*((volatile unsigned int*) SE_STRETCH_0_reg))
#define get_SE_STRETCH_1_reg   (*((volatile unsigned int*) SE_STRETCH_1_reg))
#define get_SE_STRETCH_2_reg   (*((volatile unsigned int*) SE_STRETCH_2_reg))
#define SE_STRETCH_0_inst_adr                                                        "0x0077"
#define SE_STRETCH_1_inst_adr                                                        "0x0078"
#define SE_STRETCH_2_inst_adr                                                        "0x0079"
#define SE_STRETCH_0_inst                                                            0x0077
#define SE_STRETCH_1_inst                                                            0x0078
#define SE_STRETCH_2_inst                                                            0x0079
#define SE_STRETCH_repl_alpha_shift                                                  (7)
#define SE_STRETCH_repl_alpha_mask                                                   (0x00000080)
#define SE_STRETCH_repl_alpha(data)                                                  (0x00000080&((data)<<7))
#define SE_STRETCH_repl_alpha_src(data)                                              ((0x00000080&(data))>>7)
#define SE_STRETCH_get_repl_alpha(data)                                              ((0x00000080&(data))>>7)
#define SE_STRETCH_repl_color_shift                                                  (6)
#define SE_STRETCH_repl_color_mask                                                   (0x00000040)
#define SE_STRETCH_repl_color(data)                                                  (0x00000040&((data)<<6))
#define SE_STRETCH_repl_color_src(data)                                              ((0x00000040&(data))>>6)
#define SE_STRETCH_get_repl_color(data)                                              ((0x00000040&(data))>>6)
#define SE_STRETCH_ref_alpha_shift                                                   (5)
#define SE_STRETCH_ref_alpha_mask                                                    (0x00000020)
#define SE_STRETCH_ref_alpha(data)                                                   (0x00000020&((data)<<5))
#define SE_STRETCH_ref_alpha_src(data)                                               ((0x00000020&(data))>>5)
#define SE_STRETCH_get_ref_alpha(data)                                               ((0x00000020&(data))>>5)
#define SE_STRETCH_htype_shift                                                       (3)
#define SE_STRETCH_htype_mask                                                        (0x00000018)
#define SE_STRETCH_htype(data)                                                       (0x00000018&((data)<<3))
#define SE_STRETCH_htype_src(data)                                                   ((0x00000018&(data))>>3)
#define SE_STRETCH_get_htype(data)                                                   ((0x00000018&(data))>>3)
#define SE_STRETCH_vtype_shift                                                       (2)
#define SE_STRETCH_vtype_mask                                                        (0x00000004)
#define SE_STRETCH_vtype(data)                                                       (0x00000004&((data)<<2))
#define SE_STRETCH_vtype_src(data)                                                   ((0x00000004&(data))>>2)
#define SE_STRETCH_get_vtype(data)                                                   ((0x00000004&(data))>>2)
#define SE_STRETCH_hodd_shift                                                        (1)
#define SE_STRETCH_hodd_mask                                                         (0x00000002)
#define SE_STRETCH_hodd(data)                                                        (0x00000002&((data)<<1))
#define SE_STRETCH_hodd_src(data)                                                    ((0x00000002&(data))>>1)
#define SE_STRETCH_get_hodd(data)                                                    ((0x00000002&(data))>>1)
#define SE_STRETCH_vodd_shift                                                        (0)
#define SE_STRETCH_vodd_mask                                                         (0x00000001)
#define SE_STRETCH_vodd(data)                                                        (0x00000001&((data)<<0))
#define SE_STRETCH_vodd_src(data)                                                    ((0x00000001&(data))>>0)
#define SE_STRETCH_get_vodd(data)                                                    ((0x00000001&(data))>>0)


#define SE_HDHS_0                                                                    0x1800C1E8
#define SE_HDHS_1                                                                    0x1800C1EC
#define SE_HDHS_2                                                                    0x1800C1F0
#define SE_HDHS_0_reg_addr                                                           "0xB800C1E8"
#define SE_HDHS_1_reg_addr                                                           "0xB800C1EC"
#define SE_HDHS_2_reg_addr                                                           "0xB800C1F0"
#define SE_HDHS_0_reg                                                                0xB800C1E8
#define SE_HDHS_1_reg                                                                0xB800C1EC
#define SE_HDHS_2_reg                                                                0xB800C1F0
#define set_SE_HDHS_0_reg(data)   (*((volatile unsigned int*) SE_HDHS_0_reg)=data)
#define set_SE_HDHS_1_reg(data)   (*((volatile unsigned int*) SE_HDHS_1_reg)=data)
#define set_SE_HDHS_2_reg(data)   (*((volatile unsigned int*) SE_HDHS_2_reg)=data)
#define get_SE_HDHS_0_reg   (*((volatile unsigned int*) SE_HDHS_0_reg))
#define get_SE_HDHS_1_reg   (*((volatile unsigned int*) SE_HDHS_1_reg))
#define get_SE_HDHS_2_reg   (*((volatile unsigned int*) SE_HDHS_2_reg))
#define SE_HDHS_0_inst_adr                                                           "0x007A"
#define SE_HDHS_1_inst_adr                                                           "0x007B"
#define SE_HDHS_2_inst_adr                                                           "0x007C"
#define SE_HDHS_0_inst                                                               0x007A
#define SE_HDHS_1_inst                                                               0x007B
#define SE_HDHS_2_inst                                                               0x007C
#define SE_HDHS_H_scaling_iniph_shift                                                (18)
#define SE_HDHS_H_scaling_iniph_mask                                                 (0x003C0000)
#define SE_HDHS_H_scaling_iniph(data)                                                (0x003C0000&((data)<<18))
#define SE_HDHS_H_scaling_iniph_src(data)                                            ((0x003C0000&(data))>>18)
#define SE_HDHS_get_H_scaling_iniph(data)                                            ((0x003C0000&(data))>>18)
#define SE_HDHS_H_scaling_dph_msb_shift                                              (14)
#define SE_HDHS_H_scaling_dph_msb_mask                                               (0x0003C000)
#define SE_HDHS_H_scaling_dph_msb(data)                                              (0x0003C000&((data)<<14))
#define SE_HDHS_H_scaling_dph_msb_src(data)                                          ((0x0003C000&(data))>>14)
#define SE_HDHS_get_H_scaling_dph_msb(data)                                          ((0x0003C000&(data))>>14)
#define SE_HDHS_H_scaling_dph_lsb_shift                                              (0)
#define SE_HDHS_H_scaling_dph_lsb_mask                                               (0x00003FFF)
#define SE_HDHS_H_scaling_dph_lsb(data)                                              (0x00003FFF&((data)<<0))
#define SE_HDHS_H_scaling_dph_lsb_src(data)                                          ((0x00003FFF&(data))>>0)
#define SE_HDHS_get_H_scaling_dph_lsb(data)                                          ((0x00003FFF&(data))>>0)


#define SE_VDHS_0                                                                    0x1800C1F4
#define SE_VDHS_1                                                                    0x1800C1F8
#define SE_VDHS_2                                                                    0x1800C1FC
#define SE_VDHS_0_reg_addr                                                           "0xB800C1F4"
#define SE_VDHS_1_reg_addr                                                           "0xB800C1F8"
#define SE_VDHS_2_reg_addr                                                           "0xB800C1FC"
#define SE_VDHS_0_reg                                                                0xB800C1F4
#define SE_VDHS_1_reg                                                                0xB800C1F8
#define SE_VDHS_2_reg                                                                0xB800C1FC
#define set_SE_VDHS_0_reg(data)   (*((volatile unsigned int*) SE_VDHS_0_reg)=data)
#define set_SE_VDHS_1_reg(data)   (*((volatile unsigned int*) SE_VDHS_1_reg)=data)
#define set_SE_VDHS_2_reg(data)   (*((volatile unsigned int*) SE_VDHS_2_reg)=data)
#define get_SE_VDHS_0_reg   (*((volatile unsigned int*) SE_VDHS_0_reg))
#define get_SE_VDHS_1_reg   (*((volatile unsigned int*) SE_VDHS_1_reg))
#define get_SE_VDHS_2_reg   (*((volatile unsigned int*) SE_VDHS_2_reg))
#define SE_VDHS_0_inst_adr                                                           "0x007D"
#define SE_VDHS_1_inst_adr                                                           "0x007E"
#define SE_VDHS_2_inst_adr                                                           "0x007F"
#define SE_VDHS_0_inst                                                               0x007D
#define SE_VDHS_1_inst                                                               0x007E
#define SE_VDHS_2_inst                                                               0x007F
#define SE_VDHS_V_scaling_iniph_shift                                                (18)
#define SE_VDHS_V_scaling_iniph_mask                                                 (0x003C0000)
#define SE_VDHS_V_scaling_iniph(data)                                                (0x003C0000&((data)<<18))
#define SE_VDHS_V_scaling_iniph_src(data)                                            ((0x003C0000&(data))>>18)
#define SE_VDHS_get_V_scaling_iniph(data)                                            ((0x003C0000&(data))>>18)
#define SE_VDHS_V_scaling_dph_msb_shift                                              (14)
#define SE_VDHS_V_scaling_dph_msb_mask                                               (0x0003C000)
#define SE_VDHS_V_scaling_dph_msb(data)                                              (0x0003C000&((data)<<14))
#define SE_VDHS_V_scaling_dph_msb_src(data)                                          ((0x0003C000&(data))>>14)
#define SE_VDHS_get_V_scaling_dph_msb(data)                                          ((0x0003C000&(data))>>14)
#define SE_VDHS_V_scaling_dph_lsb_shift                                              (0)
#define SE_VDHS_V_scaling_dph_lsb_mask                                               (0x00003FFF)
#define SE_VDHS_V_scaling_dph_lsb(data)                                              (0x00003FFF&((data)<<0))
#define SE_VDHS_V_scaling_dph_lsb_src(data)                                          ((0x00003FFF&(data))>>0)
#define SE_VDHS_get_V_scaling_dph_lsb(data)                                          ((0x00003FFF&(data))>>0)


#define SE_HCOEF1_0                                                                  0x1800C200
#define SE_HCOEF1_1                                                                  0x1800C204
#define SE_HCOEF1_2                                                                  0x1800C208
#define SE_HCOEF1_3                                                                  0x1800C20C
#define SE_HCOEF1_4                                                                  0x1800C210
#define SE_HCOEF1_5                                                                  0x1800C214
#define SE_HCOEF1_6                                                                  0x1800C218
#define SE_HCOEF1_7                                                                  0x1800C21C
#define SE_HCOEF1_8                                                                  0x1800C220
#define SE_HCOEF1_9                                                                  0x1800C224
#define SE_HCOEF1_10                                                                  0x1800C228
#define SE_HCOEF1_11                                                                  0x1800C22C
#define SE_HCOEF1_12                                                                  0x1800C230
#define SE_HCOEF1_13                                                                  0x1800C234
#define SE_HCOEF1_14                                                                  0x1800C238
#define SE_HCOEF1_15                                                                  0x1800C23C
#define SE_HCOEF1_16                                                                  0x1800C240
#define SE_HCOEF1_17                                                                  0x1800C244
#define SE_HCOEF1_18                                                                  0x1800C248
#define SE_HCOEF1_19                                                                  0x1800C24C
#define SE_HCOEF1_20                                                                  0x1800C250
#define SE_HCOEF1_21                                                                  0x1800C254
#define SE_HCOEF1_22                                                                  0x1800C258
#define SE_HCOEF1_23                                                                  0x1800C25C
#define SE_HCOEF1_24                                                                  0x1800C260
#define SE_HCOEF1_25                                                                  0x1800C264
#define SE_HCOEF1_26                                                                  0x1800C268
#define SE_HCOEF1_27                                                                  0x1800C26C
#define SE_HCOEF1_28                                                                  0x1800C270
#define SE_HCOEF1_29                                                                  0x1800C274
#define SE_HCOEF1_30                                                                  0x1800C278
#define SE_HCOEF1_31                                                                  0x1800C27C
#define SE_HCOEF1_0_reg_addr                                                         "0xB800C200"
#define SE_HCOEF1_1_reg_addr                                                         "0xB800C204"
#define SE_HCOEF1_2_reg_addr                                                         "0xB800C208"
#define SE_HCOEF1_3_reg_addr                                                         "0xB800C20C"
#define SE_HCOEF1_4_reg_addr                                                         "0xB800C210"
#define SE_HCOEF1_5_reg_addr                                                         "0xB800C214"
#define SE_HCOEF1_6_reg_addr                                                         "0xB800C218"
#define SE_HCOEF1_7_reg_addr                                                         "0xB800C21C"
#define SE_HCOEF1_8_reg_addr                                                         "0xB800C220"
#define SE_HCOEF1_9_reg_addr                                                         "0xB800C224"
#define SE_HCOEF1_10_reg_addr                                                         "0xB800C228"
#define SE_HCOEF1_11_reg_addr                                                         "0xB800C22C"
#define SE_HCOEF1_12_reg_addr                                                         "0xB800C230"
#define SE_HCOEF1_13_reg_addr                                                         "0xB800C234"
#define SE_HCOEF1_14_reg_addr                                                         "0xB800C238"
#define SE_HCOEF1_15_reg_addr                                                         "0xB800C23C"
#define SE_HCOEF1_16_reg_addr                                                         "0xB800C240"
#define SE_HCOEF1_17_reg_addr                                                         "0xB800C244"
#define SE_HCOEF1_18_reg_addr                                                         "0xB800C248"
#define SE_HCOEF1_19_reg_addr                                                         "0xB800C24C"
#define SE_HCOEF1_20_reg_addr                                                         "0xB800C250"
#define SE_HCOEF1_21_reg_addr                                                         "0xB800C254"
#define SE_HCOEF1_22_reg_addr                                                         "0xB800C258"
#define SE_HCOEF1_23_reg_addr                                                         "0xB800C25C"
#define SE_HCOEF1_24_reg_addr                                                         "0xB800C260"
#define SE_HCOEF1_25_reg_addr                                                         "0xB800C264"
#define SE_HCOEF1_26_reg_addr                                                         "0xB800C268"
#define SE_HCOEF1_27_reg_addr                                                         "0xB800C26C"
#define SE_HCOEF1_28_reg_addr                                                         "0xB800C270"
#define SE_HCOEF1_29_reg_addr                                                         "0xB800C274"
#define SE_HCOEF1_30_reg_addr                                                         "0xB800C278"
#define SE_HCOEF1_31_reg_addr                                                         "0xB800C27C"
#define SE_HCOEF1_0_reg                                                              0xB800C200
#define SE_HCOEF1_1_reg                                                              0xB800C204
#define SE_HCOEF1_2_reg                                                              0xB800C208
#define SE_HCOEF1_3_reg                                                              0xB800C20C
#define SE_HCOEF1_4_reg                                                              0xB800C210
#define SE_HCOEF1_5_reg                                                              0xB800C214
#define SE_HCOEF1_6_reg                                                              0xB800C218
#define SE_HCOEF1_7_reg                                                              0xB800C21C
#define SE_HCOEF1_8_reg                                                              0xB800C220
#define SE_HCOEF1_9_reg                                                              0xB800C224
#define SE_HCOEF1_10_reg                                                              0xB800C228
#define SE_HCOEF1_11_reg                                                              0xB800C22C
#define SE_HCOEF1_12_reg                                                              0xB800C230
#define SE_HCOEF1_13_reg                                                              0xB800C234
#define SE_HCOEF1_14_reg                                                              0xB800C238
#define SE_HCOEF1_15_reg                                                              0xB800C23C
#define SE_HCOEF1_16_reg                                                              0xB800C240
#define SE_HCOEF1_17_reg                                                              0xB800C244
#define SE_HCOEF1_18_reg                                                              0xB800C248
#define SE_HCOEF1_19_reg                                                              0xB800C24C
#define SE_HCOEF1_20_reg                                                              0xB800C250
#define SE_HCOEF1_21_reg                                                              0xB800C254
#define SE_HCOEF1_22_reg                                                              0xB800C258
#define SE_HCOEF1_23_reg                                                              0xB800C25C
#define SE_HCOEF1_24_reg                                                              0xB800C260
#define SE_HCOEF1_25_reg                                                              0xB800C264
#define SE_HCOEF1_26_reg                                                              0xB800C268
#define SE_HCOEF1_27_reg                                                              0xB800C26C
#define SE_HCOEF1_28_reg                                                              0xB800C270
#define SE_HCOEF1_29_reg                                                              0xB800C274
#define SE_HCOEF1_30_reg                                                              0xB800C278
#define SE_HCOEF1_31_reg                                                              0xB800C27C
#define set_SE_HCOEF1_0_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_0_reg)=data)
#define set_SE_HCOEF1_1_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_1_reg)=data)
#define set_SE_HCOEF1_2_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_2_reg)=data)
#define set_SE_HCOEF1_3_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_3_reg)=data)
#define set_SE_HCOEF1_4_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_4_reg)=data)
#define set_SE_HCOEF1_5_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_5_reg)=data)
#define set_SE_HCOEF1_6_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_6_reg)=data)
#define set_SE_HCOEF1_7_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_7_reg)=data)
#define set_SE_HCOEF1_8_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_8_reg)=data)
#define set_SE_HCOEF1_9_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_9_reg)=data)
#define set_SE_HCOEF1_10_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_10_reg)=data)
#define set_SE_HCOEF1_11_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_11_reg)=data)
#define set_SE_HCOEF1_12_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_12_reg)=data)
#define set_SE_HCOEF1_13_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_13_reg)=data)
#define set_SE_HCOEF1_14_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_14_reg)=data)
#define set_SE_HCOEF1_15_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_15_reg)=data)
#define set_SE_HCOEF1_16_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_16_reg)=data)
#define set_SE_HCOEF1_17_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_17_reg)=data)
#define set_SE_HCOEF1_18_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_18_reg)=data)
#define set_SE_HCOEF1_19_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_19_reg)=data)
#define set_SE_HCOEF1_20_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_20_reg)=data)
#define set_SE_HCOEF1_21_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_21_reg)=data)
#define set_SE_HCOEF1_22_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_22_reg)=data)
#define set_SE_HCOEF1_23_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_23_reg)=data)
#define set_SE_HCOEF1_24_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_24_reg)=data)
#define set_SE_HCOEF1_25_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_25_reg)=data)
#define set_SE_HCOEF1_26_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_26_reg)=data)
#define set_SE_HCOEF1_27_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_27_reg)=data)
#define set_SE_HCOEF1_28_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_28_reg)=data)
#define set_SE_HCOEF1_29_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_29_reg)=data)
#define set_SE_HCOEF1_30_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_30_reg)=data)
#define set_SE_HCOEF1_31_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_31_reg)=data)
#define get_SE_HCOEF1_0_reg   (*((volatile unsigned int*) SE_HCOEF1_0_reg))
#define get_SE_HCOEF1_1_reg   (*((volatile unsigned int*) SE_HCOEF1_1_reg))
#define get_SE_HCOEF1_2_reg   (*((volatile unsigned int*) SE_HCOEF1_2_reg))
#define get_SE_HCOEF1_3_reg   (*((volatile unsigned int*) SE_HCOEF1_3_reg))
#define get_SE_HCOEF1_4_reg   (*((volatile unsigned int*) SE_HCOEF1_4_reg))
#define get_SE_HCOEF1_5_reg   (*((volatile unsigned int*) SE_HCOEF1_5_reg))
#define get_SE_HCOEF1_6_reg   (*((volatile unsigned int*) SE_HCOEF1_6_reg))
#define get_SE_HCOEF1_7_reg   (*((volatile unsigned int*) SE_HCOEF1_7_reg))
#define get_SE_HCOEF1_8_reg   (*((volatile unsigned int*) SE_HCOEF1_8_reg))
#define get_SE_HCOEF1_9_reg   (*((volatile unsigned int*) SE_HCOEF1_9_reg))
#define get_SE_HCOEF1_10_reg   (*((volatile unsigned int*) SE_HCOEF1_10_reg))
#define get_SE_HCOEF1_11_reg   (*((volatile unsigned int*) SE_HCOEF1_11_reg))
#define get_SE_HCOEF1_12_reg   (*((volatile unsigned int*) SE_HCOEF1_12_reg))
#define get_SE_HCOEF1_13_reg   (*((volatile unsigned int*) SE_HCOEF1_13_reg))
#define get_SE_HCOEF1_14_reg   (*((volatile unsigned int*) SE_HCOEF1_14_reg))
#define get_SE_HCOEF1_15_reg   (*((volatile unsigned int*) SE_HCOEF1_15_reg))
#define get_SE_HCOEF1_16_reg   (*((volatile unsigned int*) SE_HCOEF1_16_reg))
#define get_SE_HCOEF1_17_reg   (*((volatile unsigned int*) SE_HCOEF1_17_reg))
#define get_SE_HCOEF1_18_reg   (*((volatile unsigned int*) SE_HCOEF1_18_reg))
#define get_SE_HCOEF1_19_reg   (*((volatile unsigned int*) SE_HCOEF1_19_reg))
#define get_SE_HCOEF1_20_reg   (*((volatile unsigned int*) SE_HCOEF1_20_reg))
#define get_SE_HCOEF1_21_reg   (*((volatile unsigned int*) SE_HCOEF1_21_reg))
#define get_SE_HCOEF1_22_reg   (*((volatile unsigned int*) SE_HCOEF1_22_reg))
#define get_SE_HCOEF1_23_reg   (*((volatile unsigned int*) SE_HCOEF1_23_reg))
#define get_SE_HCOEF1_24_reg   (*((volatile unsigned int*) SE_HCOEF1_24_reg))
#define get_SE_HCOEF1_25_reg   (*((volatile unsigned int*) SE_HCOEF1_25_reg))
#define get_SE_HCOEF1_26_reg   (*((volatile unsigned int*) SE_HCOEF1_26_reg))
#define get_SE_HCOEF1_27_reg   (*((volatile unsigned int*) SE_HCOEF1_27_reg))
#define get_SE_HCOEF1_28_reg   (*((volatile unsigned int*) SE_HCOEF1_28_reg))
#define get_SE_HCOEF1_29_reg   (*((volatile unsigned int*) SE_HCOEF1_29_reg))
#define get_SE_HCOEF1_30_reg   (*((volatile unsigned int*) SE_HCOEF1_30_reg))
#define get_SE_HCOEF1_31_reg   (*((volatile unsigned int*) SE_HCOEF1_31_reg))
#define SE_HCOEF1_0_inst_adr                                                         "0x0080"
#define SE_HCOEF1_1_inst_adr                                                         "0x0081"
#define SE_HCOEF1_2_inst_adr                                                         "0x0082"
#define SE_HCOEF1_3_inst_adr                                                         "0x0083"
#define SE_HCOEF1_4_inst_adr                                                         "0x0084"
#define SE_HCOEF1_5_inst_adr                                                         "0x0085"
#define SE_HCOEF1_6_inst_adr                                                         "0x0086"
#define SE_HCOEF1_7_inst_adr                                                         "0x0087"
#define SE_HCOEF1_8_inst_adr                                                         "0x0088"
#define SE_HCOEF1_9_inst_adr                                                         "0x0089"
#define SE_HCOEF1_10_inst_adr                                                         "0x008A"
#define SE_HCOEF1_11_inst_adr                                                         "0x008B"
#define SE_HCOEF1_12_inst_adr                                                         "0x008C"
#define SE_HCOEF1_13_inst_adr                                                         "0x008D"
#define SE_HCOEF1_14_inst_adr                                                         "0x008E"
#define SE_HCOEF1_15_inst_adr                                                         "0x008F"
#define SE_HCOEF1_16_inst_adr                                                         "0x0090"
#define SE_HCOEF1_17_inst_adr                                                         "0x0091"
#define SE_HCOEF1_18_inst_adr                                                         "0x0092"
#define SE_HCOEF1_19_inst_adr                                                         "0x0093"
#define SE_HCOEF1_20_inst_adr                                                         "0x0094"
#define SE_HCOEF1_21_inst_adr                                                         "0x0095"
#define SE_HCOEF1_22_inst_adr                                                         "0x0096"
#define SE_HCOEF1_23_inst_adr                                                         "0x0097"
#define SE_HCOEF1_24_inst_adr                                                         "0x0098"
#define SE_HCOEF1_25_inst_adr                                                         "0x0099"
#define SE_HCOEF1_26_inst_adr                                                         "0x009A"
#define SE_HCOEF1_27_inst_adr                                                         "0x009B"
#define SE_HCOEF1_28_inst_adr                                                         "0x009C"
#define SE_HCOEF1_29_inst_adr                                                         "0x009D"
#define SE_HCOEF1_30_inst_adr                                                         "0x009E"
#define SE_HCOEF1_31_inst_adr                                                         "0x009F"
#define SE_HCOEF1_0_inst                                                             0x0080
#define SE_HCOEF1_1_inst                                                             0x0081
#define SE_HCOEF1_2_inst                                                             0x0082
#define SE_HCOEF1_3_inst                                                             0x0083
#define SE_HCOEF1_4_inst                                                             0x0084
#define SE_HCOEF1_5_inst                                                             0x0085
#define SE_HCOEF1_6_inst                                                             0x0086
#define SE_HCOEF1_7_inst                                                             0x0087
#define SE_HCOEF1_8_inst                                                             0x0088
#define SE_HCOEF1_9_inst                                                             0x0089
#define SE_HCOEF1_10_inst                                                             0x008A
#define SE_HCOEF1_11_inst                                                             0x008B
#define SE_HCOEF1_12_inst                                                             0x008C
#define SE_HCOEF1_13_inst                                                             0x008D
#define SE_HCOEF1_14_inst                                                             0x008E
#define SE_HCOEF1_15_inst                                                             0x008F
#define SE_HCOEF1_16_inst                                                             0x0090
#define SE_HCOEF1_17_inst                                                             0x0091
#define SE_HCOEF1_18_inst                                                             0x0092
#define SE_HCOEF1_19_inst                                                             0x0093
#define SE_HCOEF1_20_inst                                                             0x0094
#define SE_HCOEF1_21_inst                                                             0x0095
#define SE_HCOEF1_22_inst                                                             0x0096
#define SE_HCOEF1_23_inst                                                             0x0097
#define SE_HCOEF1_24_inst                                                             0x0098
#define SE_HCOEF1_25_inst                                                             0x0099
#define SE_HCOEF1_26_inst                                                             0x009A
#define SE_HCOEF1_27_inst                                                             0x009B
#define SE_HCOEF1_28_inst                                                             0x009C
#define SE_HCOEF1_29_inst                                                             0x009D
#define SE_HCOEF1_30_inst                                                             0x009E
#define SE_HCOEF1_31_inst                                                             0x009F
#define SE_HCOEF1_hcoef_shift                                                        (0)
#define SE_HCOEF1_hcoef_mask                                                         (0x00003FFF)
#define SE_HCOEF1_hcoef(data)                                                        (0x00003FFF&((data)<<0))
#define SE_HCOEF1_hcoef_src(data)                                                    ((0x00003FFF&(data))>>0)
#define SE_HCOEF1_get_hcoef(data)                                                    ((0x00003FFF&(data))>>0)


#define SE_HCOEF1_32_0                                                               0x1800C558
#define SE_HCOEF1_32_1                                                               0x1800C55C
#define SE_HCOEF1_32_2                                                               0x1800C560
#define SE_HCOEF1_32_3                                                               0x1800C564
#define SE_HCOEF1_32_4                                                               0x1800C568
#define SE_HCOEF1_32_5                                                               0x1800C56C
#define SE_HCOEF1_32_6                                                               0x1800C570
#define SE_HCOEF1_32_7                                                               0x1800C574
#define SE_HCOEF1_32_8                                                               0x1800C578
#define SE_HCOEF1_32_9                                                               0x1800C57C
#define SE_HCOEF1_32_10                                                               0x1800C580
#define SE_HCOEF1_32_11                                                               0x1800C584
#define SE_HCOEF1_32_12                                                               0x1800C588
#define SE_HCOEF1_32_13                                                               0x1800C58C
#define SE_HCOEF1_32_14                                                               0x1800C590
#define SE_HCOEF1_32_15                                                               0x1800C594
#define SE_HCOEF1_32_16                                                               0x1800C598
#define SE_HCOEF1_32_17                                                               0x1800C59C
#define SE_HCOEF1_32_18                                                               0x1800C5A0
#define SE_HCOEF1_32_19                                                               0x1800C5A4
#define SE_HCOEF1_32_20                                                               0x1800C5A8
#define SE_HCOEF1_32_21                                                               0x1800C5AC
#define SE_HCOEF1_32_22                                                               0x1800C5B0
#define SE_HCOEF1_32_23                                                               0x1800C5B4
#define SE_HCOEF1_32_24                                                               0x1800C5B8
#define SE_HCOEF1_32_25                                                               0x1800C5BC
#define SE_HCOEF1_32_26                                                               0x1800C5C0
#define SE_HCOEF1_32_27                                                               0x1800C5C4
#define SE_HCOEF1_32_28                                                               0x1800C5C8
#define SE_HCOEF1_32_29                                                               0x1800C5CC
#define SE_HCOEF1_32_30                                                               0x1800C5D0
#define SE_HCOEF1_32_31                                                               0x1800C5D4
#define SE_HCOEF1_32_0_reg_addr                                                      "0xB800C558"
#define SE_HCOEF1_32_1_reg_addr                                                      "0xB800C55C"
#define SE_HCOEF1_32_2_reg_addr                                                      "0xB800C560"
#define SE_HCOEF1_32_3_reg_addr                                                      "0xB800C564"
#define SE_HCOEF1_32_4_reg_addr                                                      "0xB800C568"
#define SE_HCOEF1_32_5_reg_addr                                                      "0xB800C56C"
#define SE_HCOEF1_32_6_reg_addr                                                      "0xB800C570"
#define SE_HCOEF1_32_7_reg_addr                                                      "0xB800C574"
#define SE_HCOEF1_32_8_reg_addr                                                      "0xB800C578"
#define SE_HCOEF1_32_9_reg_addr                                                      "0xB800C57C"
#define SE_HCOEF1_32_10_reg_addr                                                      "0xB800C580"
#define SE_HCOEF1_32_11_reg_addr                                                      "0xB800C584"
#define SE_HCOEF1_32_12_reg_addr                                                      "0xB800C588"
#define SE_HCOEF1_32_13_reg_addr                                                      "0xB800C58C"
#define SE_HCOEF1_32_14_reg_addr                                                      "0xB800C590"
#define SE_HCOEF1_32_15_reg_addr                                                      "0xB800C594"
#define SE_HCOEF1_32_16_reg_addr                                                      "0xB800C598"
#define SE_HCOEF1_32_17_reg_addr                                                      "0xB800C59C"
#define SE_HCOEF1_32_18_reg_addr                                                      "0xB800C5A0"
#define SE_HCOEF1_32_19_reg_addr                                                      "0xB800C5A4"
#define SE_HCOEF1_32_20_reg_addr                                                      "0xB800C5A8"
#define SE_HCOEF1_32_21_reg_addr                                                      "0xB800C5AC"
#define SE_HCOEF1_32_22_reg_addr                                                      "0xB800C5B0"
#define SE_HCOEF1_32_23_reg_addr                                                      "0xB800C5B4"
#define SE_HCOEF1_32_24_reg_addr                                                      "0xB800C5B8"
#define SE_HCOEF1_32_25_reg_addr                                                      "0xB800C5BC"
#define SE_HCOEF1_32_26_reg_addr                                                      "0xB800C5C0"
#define SE_HCOEF1_32_27_reg_addr                                                      "0xB800C5C4"
#define SE_HCOEF1_32_28_reg_addr                                                      "0xB800C5C8"
#define SE_HCOEF1_32_29_reg_addr                                                      "0xB800C5CC"
#define SE_HCOEF1_32_30_reg_addr                                                      "0xB800C5D0"
#define SE_HCOEF1_32_31_reg_addr                                                      "0xB800C5D4"
#define SE_HCOEF1_32_0_reg                                                           0xB800C558
#define SE_HCOEF1_32_1_reg                                                           0xB800C55C
#define SE_HCOEF1_32_2_reg                                                           0xB800C560
#define SE_HCOEF1_32_3_reg                                                           0xB800C564
#define SE_HCOEF1_32_4_reg                                                           0xB800C568
#define SE_HCOEF1_32_5_reg                                                           0xB800C56C
#define SE_HCOEF1_32_6_reg                                                           0xB800C570
#define SE_HCOEF1_32_7_reg                                                           0xB800C574
#define SE_HCOEF1_32_8_reg                                                           0xB800C578
#define SE_HCOEF1_32_9_reg                                                           0xB800C57C
#define SE_HCOEF1_32_10_reg                                                           0xB800C580
#define SE_HCOEF1_32_11_reg                                                           0xB800C584
#define SE_HCOEF1_32_12_reg                                                           0xB800C588
#define SE_HCOEF1_32_13_reg                                                           0xB800C58C
#define SE_HCOEF1_32_14_reg                                                           0xB800C590
#define SE_HCOEF1_32_15_reg                                                           0xB800C594
#define SE_HCOEF1_32_16_reg                                                           0xB800C598
#define SE_HCOEF1_32_17_reg                                                           0xB800C59C
#define SE_HCOEF1_32_18_reg                                                           0xB800C5A0
#define SE_HCOEF1_32_19_reg                                                           0xB800C5A4
#define SE_HCOEF1_32_20_reg                                                           0xB800C5A8
#define SE_HCOEF1_32_21_reg                                                           0xB800C5AC
#define SE_HCOEF1_32_22_reg                                                           0xB800C5B0
#define SE_HCOEF1_32_23_reg                                                           0xB800C5B4
#define SE_HCOEF1_32_24_reg                                                           0xB800C5B8
#define SE_HCOEF1_32_25_reg                                                           0xB800C5BC
#define SE_HCOEF1_32_26_reg                                                           0xB800C5C0
#define SE_HCOEF1_32_27_reg                                                           0xB800C5C4
#define SE_HCOEF1_32_28_reg                                                           0xB800C5C8
#define SE_HCOEF1_32_29_reg                                                           0xB800C5CC
#define SE_HCOEF1_32_30_reg                                                           0xB800C5D0
#define SE_HCOEF1_32_31_reg                                                           0xB800C5D4
#define set_SE_HCOEF1_32_0_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_0_reg)=data)
#define set_SE_HCOEF1_32_1_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_1_reg)=data)
#define set_SE_HCOEF1_32_2_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_2_reg)=data)
#define set_SE_HCOEF1_32_3_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_3_reg)=data)
#define set_SE_HCOEF1_32_4_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_4_reg)=data)
#define set_SE_HCOEF1_32_5_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_5_reg)=data)
#define set_SE_HCOEF1_32_6_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_6_reg)=data)
#define set_SE_HCOEF1_32_7_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_7_reg)=data)
#define set_SE_HCOEF1_32_8_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_8_reg)=data)
#define set_SE_HCOEF1_32_9_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_9_reg)=data)
#define set_SE_HCOEF1_32_10_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_10_reg)=data)
#define set_SE_HCOEF1_32_11_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_11_reg)=data)
#define set_SE_HCOEF1_32_12_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_12_reg)=data)
#define set_SE_HCOEF1_32_13_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_13_reg)=data)
#define set_SE_HCOEF1_32_14_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_14_reg)=data)
#define set_SE_HCOEF1_32_15_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_15_reg)=data)
#define set_SE_HCOEF1_32_16_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_16_reg)=data)
#define set_SE_HCOEF1_32_17_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_17_reg)=data)
#define set_SE_HCOEF1_32_18_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_18_reg)=data)
#define set_SE_HCOEF1_32_19_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_19_reg)=data)
#define set_SE_HCOEF1_32_20_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_20_reg)=data)
#define set_SE_HCOEF1_32_21_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_21_reg)=data)
#define set_SE_HCOEF1_32_22_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_22_reg)=data)
#define set_SE_HCOEF1_32_23_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_23_reg)=data)
#define set_SE_HCOEF1_32_24_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_24_reg)=data)
#define set_SE_HCOEF1_32_25_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_25_reg)=data)
#define set_SE_HCOEF1_32_26_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_26_reg)=data)
#define set_SE_HCOEF1_32_27_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_27_reg)=data)
#define set_SE_HCOEF1_32_28_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_28_reg)=data)
#define set_SE_HCOEF1_32_29_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_29_reg)=data)
#define set_SE_HCOEF1_32_30_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_30_reg)=data)
#define set_SE_HCOEF1_32_31_reg(data)   (*((volatile unsigned int*) SE_HCOEF1_32_31_reg)=data)
#define get_SE_HCOEF1_32_0_reg   (*((volatile unsigned int*) SE_HCOEF1_32_0_reg))
#define get_SE_HCOEF1_32_1_reg   (*((volatile unsigned int*) SE_HCOEF1_32_1_reg))
#define get_SE_HCOEF1_32_2_reg   (*((volatile unsigned int*) SE_HCOEF1_32_2_reg))
#define get_SE_HCOEF1_32_3_reg   (*((volatile unsigned int*) SE_HCOEF1_32_3_reg))
#define get_SE_HCOEF1_32_4_reg   (*((volatile unsigned int*) SE_HCOEF1_32_4_reg))
#define get_SE_HCOEF1_32_5_reg   (*((volatile unsigned int*) SE_HCOEF1_32_5_reg))
#define get_SE_HCOEF1_32_6_reg   (*((volatile unsigned int*) SE_HCOEF1_32_6_reg))
#define get_SE_HCOEF1_32_7_reg   (*((volatile unsigned int*) SE_HCOEF1_32_7_reg))
#define get_SE_HCOEF1_32_8_reg   (*((volatile unsigned int*) SE_HCOEF1_32_8_reg))
#define get_SE_HCOEF1_32_9_reg   (*((volatile unsigned int*) SE_HCOEF1_32_9_reg))
#define get_SE_HCOEF1_32_10_reg   (*((volatile unsigned int*) SE_HCOEF1_32_10_reg))
#define get_SE_HCOEF1_32_11_reg   (*((volatile unsigned int*) SE_HCOEF1_32_11_reg))
#define get_SE_HCOEF1_32_12_reg   (*((volatile unsigned int*) SE_HCOEF1_32_12_reg))
#define get_SE_HCOEF1_32_13_reg   (*((volatile unsigned int*) SE_HCOEF1_32_13_reg))
#define get_SE_HCOEF1_32_14_reg   (*((volatile unsigned int*) SE_HCOEF1_32_14_reg))
#define get_SE_HCOEF1_32_15_reg   (*((volatile unsigned int*) SE_HCOEF1_32_15_reg))
#define get_SE_HCOEF1_32_16_reg   (*((volatile unsigned int*) SE_HCOEF1_32_16_reg))
#define get_SE_HCOEF1_32_17_reg   (*((volatile unsigned int*) SE_HCOEF1_32_17_reg))
#define get_SE_HCOEF1_32_18_reg   (*((volatile unsigned int*) SE_HCOEF1_32_18_reg))
#define get_SE_HCOEF1_32_19_reg   (*((volatile unsigned int*) SE_HCOEF1_32_19_reg))
#define get_SE_HCOEF1_32_20_reg   (*((volatile unsigned int*) SE_HCOEF1_32_20_reg))
#define get_SE_HCOEF1_32_21_reg   (*((volatile unsigned int*) SE_HCOEF1_32_21_reg))
#define get_SE_HCOEF1_32_22_reg   (*((volatile unsigned int*) SE_HCOEF1_32_22_reg))
#define get_SE_HCOEF1_32_23_reg   (*((volatile unsigned int*) SE_HCOEF1_32_23_reg))
#define get_SE_HCOEF1_32_24_reg   (*((volatile unsigned int*) SE_HCOEF1_32_24_reg))
#define get_SE_HCOEF1_32_25_reg   (*((volatile unsigned int*) SE_HCOEF1_32_25_reg))
#define get_SE_HCOEF1_32_26_reg   (*((volatile unsigned int*) SE_HCOEF1_32_26_reg))
#define get_SE_HCOEF1_32_27_reg   (*((volatile unsigned int*) SE_HCOEF1_32_27_reg))
#define get_SE_HCOEF1_32_28_reg   (*((volatile unsigned int*) SE_HCOEF1_32_28_reg))
#define get_SE_HCOEF1_32_29_reg   (*((volatile unsigned int*) SE_HCOEF1_32_29_reg))
#define get_SE_HCOEF1_32_30_reg   (*((volatile unsigned int*) SE_HCOEF1_32_30_reg))
#define get_SE_HCOEF1_32_31_reg   (*((volatile unsigned int*) SE_HCOEF1_32_31_reg))
#define SE_HCOEF1_32_0_inst_adr                                                      "0x0056"
#define SE_HCOEF1_32_1_inst_adr                                                      "0x0057"
#define SE_HCOEF1_32_2_inst_adr                                                      "0x0058"
#define SE_HCOEF1_32_3_inst_adr                                                      "0x0059"
#define SE_HCOEF1_32_4_inst_adr                                                      "0x005A"
#define SE_HCOEF1_32_5_inst_adr                                                      "0x005B"
#define SE_HCOEF1_32_6_inst_adr                                                      "0x005C"
#define SE_HCOEF1_32_7_inst_adr                                                      "0x005D"
#define SE_HCOEF1_32_8_inst_adr                                                      "0x005E"
#define SE_HCOEF1_32_9_inst_adr                                                      "0x005F"
#define SE_HCOEF1_32_10_inst_adr                                                      "0x0060"
#define SE_HCOEF1_32_11_inst_adr                                                      "0x0061"
#define SE_HCOEF1_32_12_inst_adr                                                      "0x0062"
#define SE_HCOEF1_32_13_inst_adr                                                      "0x0063"
#define SE_HCOEF1_32_14_inst_adr                                                      "0x0064"
#define SE_HCOEF1_32_15_inst_adr                                                      "0x0065"
#define SE_HCOEF1_32_16_inst_adr                                                      "0x0066"
#define SE_HCOEF1_32_17_inst_adr                                                      "0x0067"
#define SE_HCOEF1_32_18_inst_adr                                                      "0x0068"
#define SE_HCOEF1_32_19_inst_adr                                                      "0x0069"
#define SE_HCOEF1_32_20_inst_adr                                                      "0x006A"
#define SE_HCOEF1_32_21_inst_adr                                                      "0x006B"
#define SE_HCOEF1_32_22_inst_adr                                                      "0x006C"
#define SE_HCOEF1_32_23_inst_adr                                                      "0x006D"
#define SE_HCOEF1_32_24_inst_adr                                                      "0x006E"
#define SE_HCOEF1_32_25_inst_adr                                                      "0x006F"
#define SE_HCOEF1_32_26_inst_adr                                                      "0x0070"
#define SE_HCOEF1_32_27_inst_adr                                                      "0x0071"
#define SE_HCOEF1_32_28_inst_adr                                                      "0x0072"
#define SE_HCOEF1_32_29_inst_adr                                                      "0x0073"
#define SE_HCOEF1_32_30_inst_adr                                                      "0x0074"
#define SE_HCOEF1_32_31_inst_adr                                                      "0x0075"
#define SE_HCOEF1_32_0_inst                                                          0x0056
#define SE_HCOEF1_32_1_inst                                                          0x0057
#define SE_HCOEF1_32_2_inst                                                          0x0058
#define SE_HCOEF1_32_3_inst                                                          0x0059
#define SE_HCOEF1_32_4_inst                                                          0x005A
#define SE_HCOEF1_32_5_inst                                                          0x005B
#define SE_HCOEF1_32_6_inst                                                          0x005C
#define SE_HCOEF1_32_7_inst                                                          0x005D
#define SE_HCOEF1_32_8_inst                                                          0x005E
#define SE_HCOEF1_32_9_inst                                                          0x005F
#define SE_HCOEF1_32_10_inst                                                          0x0060
#define SE_HCOEF1_32_11_inst                                                          0x0061
#define SE_HCOEF1_32_12_inst                                                          0x0062
#define SE_HCOEF1_32_13_inst                                                          0x0063
#define SE_HCOEF1_32_14_inst                                                          0x0064
#define SE_HCOEF1_32_15_inst                                                          0x0065
#define SE_HCOEF1_32_16_inst                                                          0x0066
#define SE_HCOEF1_32_17_inst                                                          0x0067
#define SE_HCOEF1_32_18_inst                                                          0x0068
#define SE_HCOEF1_32_19_inst                                                          0x0069
#define SE_HCOEF1_32_20_inst                                                          0x006A
#define SE_HCOEF1_32_21_inst                                                          0x006B
#define SE_HCOEF1_32_22_inst                                                          0x006C
#define SE_HCOEF1_32_23_inst                                                          0x006D
#define SE_HCOEF1_32_24_inst                                                          0x006E
#define SE_HCOEF1_32_25_inst                                                          0x006F
#define SE_HCOEF1_32_26_inst                                                          0x0070
#define SE_HCOEF1_32_27_inst                                                          0x0071
#define SE_HCOEF1_32_28_inst                                                          0x0072
#define SE_HCOEF1_32_29_inst                                                          0x0073
#define SE_HCOEF1_32_30_inst                                                          0x0074
#define SE_HCOEF1_32_31_inst                                                          0x0075
#define SE_HCOEF1_32_hcoef_shift                                                     (0)
#define SE_HCOEF1_32_hcoef_mask                                                      (0x00003FFF)
#define SE_HCOEF1_32_hcoef(data)                                                     (0x00003FFF&((data)<<0))
#define SE_HCOEF1_32_hcoef_src(data)                                                 ((0x00003FFF&(data))>>0)
#define SE_HCOEF1_32_get_hcoef(data)                                                 ((0x00003FFF&(data))>>0)


#define SE_VCOEF1_0                                                                  0x1800C280
#define SE_VCOEF1_1                                                                  0x1800C284
#define SE_VCOEF1_2                                                                  0x1800C288
#define SE_VCOEF1_3                                                                  0x1800C28C
#define SE_VCOEF1_4                                                                  0x1800C290
#define SE_VCOEF1_5                                                                  0x1800C294
#define SE_VCOEF1_6                                                                  0x1800C298
#define SE_VCOEF1_7                                                                  0x1800C29C
#define SE_VCOEF1_8                                                                  0x1800C2A0
#define SE_VCOEF1_9                                                                  0x1800C2A4
#define SE_VCOEF1_10                                                                  0x1800C2A8
#define SE_VCOEF1_11                                                                  0x1800C2AC
#define SE_VCOEF1_12                                                                  0x1800C2B0
#define SE_VCOEF1_13                                                                  0x1800C2B4
#define SE_VCOEF1_14                                                                  0x1800C2B8
#define SE_VCOEF1_15                                                                  0x1800C2BC
#define SE_VCOEF1_0_reg_addr                                                         "0xB800C280"
#define SE_VCOEF1_1_reg_addr                                                         "0xB800C284"
#define SE_VCOEF1_2_reg_addr                                                         "0xB800C288"
#define SE_VCOEF1_3_reg_addr                                                         "0xB800C28C"
#define SE_VCOEF1_4_reg_addr                                                         "0xB800C290"
#define SE_VCOEF1_5_reg_addr                                                         "0xB800C294"
#define SE_VCOEF1_6_reg_addr                                                         "0xB800C298"
#define SE_VCOEF1_7_reg_addr                                                         "0xB800C29C"
#define SE_VCOEF1_8_reg_addr                                                         "0xB800C2A0"
#define SE_VCOEF1_9_reg_addr                                                         "0xB800C2A4"
#define SE_VCOEF1_10_reg_addr                                                         "0xB800C2A8"
#define SE_VCOEF1_11_reg_addr                                                         "0xB800C2AC"
#define SE_VCOEF1_12_reg_addr                                                         "0xB800C2B0"
#define SE_VCOEF1_13_reg_addr                                                         "0xB800C2B4"
#define SE_VCOEF1_14_reg_addr                                                         "0xB800C2B8"
#define SE_VCOEF1_15_reg_addr                                                         "0xB800C2BC"
#define SE_VCOEF1_0_reg                                                              0xB800C280
#define SE_VCOEF1_1_reg                                                              0xB800C284
#define SE_VCOEF1_2_reg                                                              0xB800C288
#define SE_VCOEF1_3_reg                                                              0xB800C28C
#define SE_VCOEF1_4_reg                                                              0xB800C290
#define SE_VCOEF1_5_reg                                                              0xB800C294
#define SE_VCOEF1_6_reg                                                              0xB800C298
#define SE_VCOEF1_7_reg                                                              0xB800C29C
#define SE_VCOEF1_8_reg                                                              0xB800C2A0
#define SE_VCOEF1_9_reg                                                              0xB800C2A4
#define SE_VCOEF1_10_reg                                                              0xB800C2A8
#define SE_VCOEF1_11_reg                                                              0xB800C2AC
#define SE_VCOEF1_12_reg                                                              0xB800C2B0
#define SE_VCOEF1_13_reg                                                              0xB800C2B4
#define SE_VCOEF1_14_reg                                                              0xB800C2B8
#define SE_VCOEF1_15_reg                                                              0xB800C2BC
#define set_SE_VCOEF1_0_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_0_reg)=data)
#define set_SE_VCOEF1_1_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_1_reg)=data)
#define set_SE_VCOEF1_2_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_2_reg)=data)
#define set_SE_VCOEF1_3_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_3_reg)=data)
#define set_SE_VCOEF1_4_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_4_reg)=data)
#define set_SE_VCOEF1_5_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_5_reg)=data)
#define set_SE_VCOEF1_6_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_6_reg)=data)
#define set_SE_VCOEF1_7_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_7_reg)=data)
#define set_SE_VCOEF1_8_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_8_reg)=data)
#define set_SE_VCOEF1_9_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_9_reg)=data)
#define set_SE_VCOEF1_10_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_10_reg)=data)
#define set_SE_VCOEF1_11_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_11_reg)=data)
#define set_SE_VCOEF1_12_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_12_reg)=data)
#define set_SE_VCOEF1_13_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_13_reg)=data)
#define set_SE_VCOEF1_14_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_14_reg)=data)
#define set_SE_VCOEF1_15_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_15_reg)=data)
#define get_SE_VCOEF1_0_reg   (*((volatile unsigned int*) SE_VCOEF1_0_reg))
#define get_SE_VCOEF1_1_reg   (*((volatile unsigned int*) SE_VCOEF1_1_reg))
#define get_SE_VCOEF1_2_reg   (*((volatile unsigned int*) SE_VCOEF1_2_reg))
#define get_SE_VCOEF1_3_reg   (*((volatile unsigned int*) SE_VCOEF1_3_reg))
#define get_SE_VCOEF1_4_reg   (*((volatile unsigned int*) SE_VCOEF1_4_reg))
#define get_SE_VCOEF1_5_reg   (*((volatile unsigned int*) SE_VCOEF1_5_reg))
#define get_SE_VCOEF1_6_reg   (*((volatile unsigned int*) SE_VCOEF1_6_reg))
#define get_SE_VCOEF1_7_reg   (*((volatile unsigned int*) SE_VCOEF1_7_reg))
#define get_SE_VCOEF1_8_reg   (*((volatile unsigned int*) SE_VCOEF1_8_reg))
#define get_SE_VCOEF1_9_reg   (*((volatile unsigned int*) SE_VCOEF1_9_reg))
#define get_SE_VCOEF1_10_reg   (*((volatile unsigned int*) SE_VCOEF1_10_reg))
#define get_SE_VCOEF1_11_reg   (*((volatile unsigned int*) SE_VCOEF1_11_reg))
#define get_SE_VCOEF1_12_reg   (*((volatile unsigned int*) SE_VCOEF1_12_reg))
#define get_SE_VCOEF1_13_reg   (*((volatile unsigned int*) SE_VCOEF1_13_reg))
#define get_SE_VCOEF1_14_reg   (*((volatile unsigned int*) SE_VCOEF1_14_reg))
#define get_SE_VCOEF1_15_reg   (*((volatile unsigned int*) SE_VCOEF1_15_reg))
#define SE_VCOEF1_0_inst_adr                                                         "0x00A0"
#define SE_VCOEF1_1_inst_adr                                                         "0x00A1"
#define SE_VCOEF1_2_inst_adr                                                         "0x00A2"
#define SE_VCOEF1_3_inst_adr                                                         "0x00A3"
#define SE_VCOEF1_4_inst_adr                                                         "0x00A4"
#define SE_VCOEF1_5_inst_adr                                                         "0x00A5"
#define SE_VCOEF1_6_inst_adr                                                         "0x00A6"
#define SE_VCOEF1_7_inst_adr                                                         "0x00A7"
#define SE_VCOEF1_8_inst_adr                                                         "0x00A8"
#define SE_VCOEF1_9_inst_adr                                                         "0x00A9"
#define SE_VCOEF1_10_inst_adr                                                         "0x00AA"
#define SE_VCOEF1_11_inst_adr                                                         "0x00AB"
#define SE_VCOEF1_12_inst_adr                                                         "0x00AC"
#define SE_VCOEF1_13_inst_adr                                                         "0x00AD"
#define SE_VCOEF1_14_inst_adr                                                         "0x00AE"
#define SE_VCOEF1_15_inst_adr                                                         "0x00AF"
#define SE_VCOEF1_0_inst                                                             0x00A0
#define SE_VCOEF1_1_inst                                                             0x00A1
#define SE_VCOEF1_2_inst                                                             0x00A2
#define SE_VCOEF1_3_inst                                                             0x00A3
#define SE_VCOEF1_4_inst                                                             0x00A4
#define SE_VCOEF1_5_inst                                                             0x00A5
#define SE_VCOEF1_6_inst                                                             0x00A6
#define SE_VCOEF1_7_inst                                                             0x00A7
#define SE_VCOEF1_8_inst                                                             0x00A8
#define SE_VCOEF1_9_inst                                                             0x00A9
#define SE_VCOEF1_10_inst                                                             0x00AA
#define SE_VCOEF1_11_inst                                                             0x00AB
#define SE_VCOEF1_12_inst                                                             0x00AC
#define SE_VCOEF1_13_inst                                                             0x00AD
#define SE_VCOEF1_14_inst                                                             0x00AE
#define SE_VCOEF1_15_inst                                                             0x00AF
#define SE_VCOEF1_vcoef_shift                                                        (0)
#define SE_VCOEF1_vcoef_mask                                                         (0x00003FFF)
#define SE_VCOEF1_vcoef(data)                                                        (0x00003FFF&((data)<<0))
#define SE_VCOEF1_vcoef_src(data)                                                    ((0x00003FFF&(data))>>0)
#define SE_VCOEF1_get_vcoef(data)                                                    ((0x00003FFF&(data))>>0)


#define SE_VCOEF1_16_0                                                               0x1800C5D8
#define SE_VCOEF1_16_1                                                               0x1800C5DC
#define SE_VCOEF1_16_2                                                               0x1800C5E0
#define SE_VCOEF1_16_3                                                               0x1800C5E4
#define SE_VCOEF1_16_4                                                               0x1800C5E8
#define SE_VCOEF1_16_5                                                               0x1800C5EC
#define SE_VCOEF1_16_6                                                               0x1800C5F0
#define SE_VCOEF1_16_7                                                               0x1800C5F4
#define SE_VCOEF1_16_8                                                               0x1800C5F8
#define SE_VCOEF1_16_9                                                               0x1800C5FC
#define SE_VCOEF1_16_10                                                               0x1800C600
#define SE_VCOEF1_16_11                                                               0x1800C604
#define SE_VCOEF1_16_12                                                               0x1800C608
#define SE_VCOEF1_16_13                                                               0x1800C60C
#define SE_VCOEF1_16_14                                                               0x1800C610
#define SE_VCOEF1_16_15                                                               0x1800C614
#define SE_VCOEF1_16_0_reg_addr                                                      "0xB800C5D8"
#define SE_VCOEF1_16_1_reg_addr                                                      "0xB800C5DC"
#define SE_VCOEF1_16_2_reg_addr                                                      "0xB800C5E0"
#define SE_VCOEF1_16_3_reg_addr                                                      "0xB800C5E4"
#define SE_VCOEF1_16_4_reg_addr                                                      "0xB800C5E8"
#define SE_VCOEF1_16_5_reg_addr                                                      "0xB800C5EC"
#define SE_VCOEF1_16_6_reg_addr                                                      "0xB800C5F0"
#define SE_VCOEF1_16_7_reg_addr                                                      "0xB800C5F4"
#define SE_VCOEF1_16_8_reg_addr                                                      "0xB800C5F8"
#define SE_VCOEF1_16_9_reg_addr                                                      "0xB800C5FC"
#define SE_VCOEF1_16_10_reg_addr                                                      "0xB800C600"
#define SE_VCOEF1_16_11_reg_addr                                                      "0xB800C604"
#define SE_VCOEF1_16_12_reg_addr                                                      "0xB800C608"
#define SE_VCOEF1_16_13_reg_addr                                                      "0xB800C60C"
#define SE_VCOEF1_16_14_reg_addr                                                      "0xB800C610"
#define SE_VCOEF1_16_15_reg_addr                                                      "0xB800C614"
#define SE_VCOEF1_16_0_reg                                                           0xB800C5D8
#define SE_VCOEF1_16_1_reg                                                           0xB800C5DC
#define SE_VCOEF1_16_2_reg                                                           0xB800C5E0
#define SE_VCOEF1_16_3_reg                                                           0xB800C5E4
#define SE_VCOEF1_16_4_reg                                                           0xB800C5E8
#define SE_VCOEF1_16_5_reg                                                           0xB800C5EC
#define SE_VCOEF1_16_6_reg                                                           0xB800C5F0
#define SE_VCOEF1_16_7_reg                                                           0xB800C5F4
#define SE_VCOEF1_16_8_reg                                                           0xB800C5F8
#define SE_VCOEF1_16_9_reg                                                           0xB800C5FC
#define SE_VCOEF1_16_10_reg                                                           0xB800C600
#define SE_VCOEF1_16_11_reg                                                           0xB800C604
#define SE_VCOEF1_16_12_reg                                                           0xB800C608
#define SE_VCOEF1_16_13_reg                                                           0xB800C60C
#define SE_VCOEF1_16_14_reg                                                           0xB800C610
#define SE_VCOEF1_16_15_reg                                                           0xB800C614
#define set_SE_VCOEF1_16_0_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_0_reg)=data)
#define set_SE_VCOEF1_16_1_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_1_reg)=data)
#define set_SE_VCOEF1_16_2_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_2_reg)=data)
#define set_SE_VCOEF1_16_3_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_3_reg)=data)
#define set_SE_VCOEF1_16_4_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_4_reg)=data)
#define set_SE_VCOEF1_16_5_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_5_reg)=data)
#define set_SE_VCOEF1_16_6_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_6_reg)=data)
#define set_SE_VCOEF1_16_7_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_7_reg)=data)
#define set_SE_VCOEF1_16_8_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_8_reg)=data)
#define set_SE_VCOEF1_16_9_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_9_reg)=data)
#define set_SE_VCOEF1_16_10_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_10_reg)=data)
#define set_SE_VCOEF1_16_11_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_11_reg)=data)
#define set_SE_VCOEF1_16_12_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_12_reg)=data)
#define set_SE_VCOEF1_16_13_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_13_reg)=data)
#define set_SE_VCOEF1_16_14_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_14_reg)=data)
#define set_SE_VCOEF1_16_15_reg(data)   (*((volatile unsigned int*) SE_VCOEF1_16_15_reg)=data)
#define get_SE_VCOEF1_16_0_reg   (*((volatile unsigned int*) SE_VCOEF1_16_0_reg))
#define get_SE_VCOEF1_16_1_reg   (*((volatile unsigned int*) SE_VCOEF1_16_1_reg))
#define get_SE_VCOEF1_16_2_reg   (*((volatile unsigned int*) SE_VCOEF1_16_2_reg))
#define get_SE_VCOEF1_16_3_reg   (*((volatile unsigned int*) SE_VCOEF1_16_3_reg))
#define get_SE_VCOEF1_16_4_reg   (*((volatile unsigned int*) SE_VCOEF1_16_4_reg))
#define get_SE_VCOEF1_16_5_reg   (*((volatile unsigned int*) SE_VCOEF1_16_5_reg))
#define get_SE_VCOEF1_16_6_reg   (*((volatile unsigned int*) SE_VCOEF1_16_6_reg))
#define get_SE_VCOEF1_16_7_reg   (*((volatile unsigned int*) SE_VCOEF1_16_7_reg))
#define get_SE_VCOEF1_16_8_reg   (*((volatile unsigned int*) SE_VCOEF1_16_8_reg))
#define get_SE_VCOEF1_16_9_reg   (*((volatile unsigned int*) SE_VCOEF1_16_9_reg))
#define get_SE_VCOEF1_16_10_reg   (*((volatile unsigned int*) SE_VCOEF1_16_10_reg))
#define get_SE_VCOEF1_16_11_reg   (*((volatile unsigned int*) SE_VCOEF1_16_11_reg))
#define get_SE_VCOEF1_16_12_reg   (*((volatile unsigned int*) SE_VCOEF1_16_12_reg))
#define get_SE_VCOEF1_16_13_reg   (*((volatile unsigned int*) SE_VCOEF1_16_13_reg))
#define get_SE_VCOEF1_16_14_reg   (*((volatile unsigned int*) SE_VCOEF1_16_14_reg))
#define get_SE_VCOEF1_16_15_reg   (*((volatile unsigned int*) SE_VCOEF1_16_15_reg))
#define SE_VCOEF1_16_0_inst_adr                                                      "0x0076"
#define SE_VCOEF1_16_1_inst_adr                                                      "0x0077"
#define SE_VCOEF1_16_2_inst_adr                                                      "0x0078"
#define SE_VCOEF1_16_3_inst_adr                                                      "0x0079"
#define SE_VCOEF1_16_4_inst_adr                                                      "0x007A"
#define SE_VCOEF1_16_5_inst_adr                                                      "0x007B"
#define SE_VCOEF1_16_6_inst_adr                                                      "0x007C"
#define SE_VCOEF1_16_7_inst_adr                                                      "0x007D"
#define SE_VCOEF1_16_8_inst_adr                                                      "0x007E"
#define SE_VCOEF1_16_9_inst_adr                                                      "0x007F"
#define SE_VCOEF1_16_10_inst_adr                                                      "0x0080"
#define SE_VCOEF1_16_11_inst_adr                                                      "0x0081"
#define SE_VCOEF1_16_12_inst_adr                                                      "0x0082"
#define SE_VCOEF1_16_13_inst_adr                                                      "0x0083"
#define SE_VCOEF1_16_14_inst_adr                                                      "0x0084"
#define SE_VCOEF1_16_15_inst_adr                                                      "0x0085"
#define SE_VCOEF1_16_0_inst                                                          0x0076
#define SE_VCOEF1_16_1_inst                                                          0x0077
#define SE_VCOEF1_16_2_inst                                                          0x0078
#define SE_VCOEF1_16_3_inst                                                          0x0079
#define SE_VCOEF1_16_4_inst                                                          0x007A
#define SE_VCOEF1_16_5_inst                                                          0x007B
#define SE_VCOEF1_16_6_inst                                                          0x007C
#define SE_VCOEF1_16_7_inst                                                          0x007D
#define SE_VCOEF1_16_8_inst                                                          0x007E
#define SE_VCOEF1_16_9_inst                                                          0x007F
#define SE_VCOEF1_16_10_inst                                                          0x0080
#define SE_VCOEF1_16_11_inst                                                          0x0081
#define SE_VCOEF1_16_12_inst                                                          0x0082
#define SE_VCOEF1_16_13_inst                                                          0x0083
#define SE_VCOEF1_16_14_inst                                                          0x0084
#define SE_VCOEF1_16_15_inst                                                          0x0085
#define SE_VCOEF1_16_vcoef_shift                                                     (0)
#define SE_VCOEF1_16_vcoef_mask                                                      (0x00003FFF)
#define SE_VCOEF1_16_vcoef(data)                                                     (0x00003FFF&((data)<<0))
#define SE_VCOEF1_16_vcoef_src(data)                                                 ((0x00003FFF&(data))>>0)
#define SE_VCOEF1_16_get_vcoef(data)                                                 ((0x00003FFF&(data))>>0)


#define SE_HCOEF2_0                                                                  0x1800C2C0
#define SE_HCOEF2_1                                                                  0x1800C2C4
#define SE_HCOEF2_2                                                                  0x1800C2C8
#define SE_HCOEF2_3                                                                  0x1800C2CC
#define SE_HCOEF2_4                                                                  0x1800C2D0
#define SE_HCOEF2_5                                                                  0x1800C2D4
#define SE_HCOEF2_6                                                                  0x1800C2D8
#define SE_HCOEF2_7                                                                  0x1800C2DC
#define SE_HCOEF2_8                                                                  0x1800C2E0
#define SE_HCOEF2_9                                                                  0x1800C2E4
#define SE_HCOEF2_10                                                                  0x1800C2E8
#define SE_HCOEF2_11                                                                  0x1800C2EC
#define SE_HCOEF2_12                                                                  0x1800C2F0
#define SE_HCOEF2_13                                                                  0x1800C2F4
#define SE_HCOEF2_14                                                                  0x1800C2F8
#define SE_HCOEF2_15                                                                  0x1800C2FC
#define SE_HCOEF2_16                                                                  0x1800C300
#define SE_HCOEF2_17                                                                  0x1800C304
#define SE_HCOEF2_18                                                                  0x1800C308
#define SE_HCOEF2_19                                                                  0x1800C30C
#define SE_HCOEF2_20                                                                  0x1800C310
#define SE_HCOEF2_21                                                                  0x1800C314
#define SE_HCOEF2_22                                                                  0x1800C318
#define SE_HCOEF2_23                                                                  0x1800C31C
#define SE_HCOEF2_24                                                                  0x1800C320
#define SE_HCOEF2_25                                                                  0x1800C324
#define SE_HCOEF2_26                                                                  0x1800C328
#define SE_HCOEF2_27                                                                  0x1800C32C
#define SE_HCOEF2_28                                                                  0x1800C330
#define SE_HCOEF2_29                                                                  0x1800C334
#define SE_HCOEF2_30                                                                  0x1800C338
#define SE_HCOEF2_31                                                                  0x1800C33C
#define SE_HCOEF2_0_reg_addr                                                         "0xB800C2C0"
#define SE_HCOEF2_1_reg_addr                                                         "0xB800C2C4"
#define SE_HCOEF2_2_reg_addr                                                         "0xB800C2C8"
#define SE_HCOEF2_3_reg_addr                                                         "0xB800C2CC"
#define SE_HCOEF2_4_reg_addr                                                         "0xB800C2D0"
#define SE_HCOEF2_5_reg_addr                                                         "0xB800C2D4"
#define SE_HCOEF2_6_reg_addr                                                         "0xB800C2D8"
#define SE_HCOEF2_7_reg_addr                                                         "0xB800C2DC"
#define SE_HCOEF2_8_reg_addr                                                         "0xB800C2E0"
#define SE_HCOEF2_9_reg_addr                                                         "0xB800C2E4"
#define SE_HCOEF2_10_reg_addr                                                         "0xB800C2E8"
#define SE_HCOEF2_11_reg_addr                                                         "0xB800C2EC"
#define SE_HCOEF2_12_reg_addr                                                         "0xB800C2F0"
#define SE_HCOEF2_13_reg_addr                                                         "0xB800C2F4"
#define SE_HCOEF2_14_reg_addr                                                         "0xB800C2F8"
#define SE_HCOEF2_15_reg_addr                                                         "0xB800C2FC"
#define SE_HCOEF2_16_reg_addr                                                         "0xB800C300"
#define SE_HCOEF2_17_reg_addr                                                         "0xB800C304"
#define SE_HCOEF2_18_reg_addr                                                         "0xB800C308"
#define SE_HCOEF2_19_reg_addr                                                         "0xB800C30C"
#define SE_HCOEF2_20_reg_addr                                                         "0xB800C310"
#define SE_HCOEF2_21_reg_addr                                                         "0xB800C314"
#define SE_HCOEF2_22_reg_addr                                                         "0xB800C318"
#define SE_HCOEF2_23_reg_addr                                                         "0xB800C31C"
#define SE_HCOEF2_24_reg_addr                                                         "0xB800C320"
#define SE_HCOEF2_25_reg_addr                                                         "0xB800C324"
#define SE_HCOEF2_26_reg_addr                                                         "0xB800C328"
#define SE_HCOEF2_27_reg_addr                                                         "0xB800C32C"
#define SE_HCOEF2_28_reg_addr                                                         "0xB800C330"
#define SE_HCOEF2_29_reg_addr                                                         "0xB800C334"
#define SE_HCOEF2_30_reg_addr                                                         "0xB800C338"
#define SE_HCOEF2_31_reg_addr                                                         "0xB800C33C"
#define SE_HCOEF2_0_reg                                                              0xB800C2C0
#define SE_HCOEF2_1_reg                                                              0xB800C2C4
#define SE_HCOEF2_2_reg                                                              0xB800C2C8
#define SE_HCOEF2_3_reg                                                              0xB800C2CC
#define SE_HCOEF2_4_reg                                                              0xB800C2D0
#define SE_HCOEF2_5_reg                                                              0xB800C2D4
#define SE_HCOEF2_6_reg                                                              0xB800C2D8
#define SE_HCOEF2_7_reg                                                              0xB800C2DC
#define SE_HCOEF2_8_reg                                                              0xB800C2E0
#define SE_HCOEF2_9_reg                                                              0xB800C2E4
#define SE_HCOEF2_10_reg                                                              0xB800C2E8
#define SE_HCOEF2_11_reg                                                              0xB800C2EC
#define SE_HCOEF2_12_reg                                                              0xB800C2F0
#define SE_HCOEF2_13_reg                                                              0xB800C2F4
#define SE_HCOEF2_14_reg                                                              0xB800C2F8
#define SE_HCOEF2_15_reg                                                              0xB800C2FC
#define SE_HCOEF2_16_reg                                                              0xB800C300
#define SE_HCOEF2_17_reg                                                              0xB800C304
#define SE_HCOEF2_18_reg                                                              0xB800C308
#define SE_HCOEF2_19_reg                                                              0xB800C30C
#define SE_HCOEF2_20_reg                                                              0xB800C310
#define SE_HCOEF2_21_reg                                                              0xB800C314
#define SE_HCOEF2_22_reg                                                              0xB800C318
#define SE_HCOEF2_23_reg                                                              0xB800C31C
#define SE_HCOEF2_24_reg                                                              0xB800C320
#define SE_HCOEF2_25_reg                                                              0xB800C324
#define SE_HCOEF2_26_reg                                                              0xB800C328
#define SE_HCOEF2_27_reg                                                              0xB800C32C
#define SE_HCOEF2_28_reg                                                              0xB800C330
#define SE_HCOEF2_29_reg                                                              0xB800C334
#define SE_HCOEF2_30_reg                                                              0xB800C338
#define SE_HCOEF2_31_reg                                                              0xB800C33C
#define set_SE_HCOEF2_0_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_0_reg)=data)
#define set_SE_HCOEF2_1_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_1_reg)=data)
#define set_SE_HCOEF2_2_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_2_reg)=data)
#define set_SE_HCOEF2_3_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_3_reg)=data)
#define set_SE_HCOEF2_4_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_4_reg)=data)
#define set_SE_HCOEF2_5_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_5_reg)=data)
#define set_SE_HCOEF2_6_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_6_reg)=data)
#define set_SE_HCOEF2_7_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_7_reg)=data)
#define set_SE_HCOEF2_8_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_8_reg)=data)
#define set_SE_HCOEF2_9_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_9_reg)=data)
#define set_SE_HCOEF2_10_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_10_reg)=data)
#define set_SE_HCOEF2_11_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_11_reg)=data)
#define set_SE_HCOEF2_12_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_12_reg)=data)
#define set_SE_HCOEF2_13_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_13_reg)=data)
#define set_SE_HCOEF2_14_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_14_reg)=data)
#define set_SE_HCOEF2_15_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_15_reg)=data)
#define set_SE_HCOEF2_16_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_16_reg)=data)
#define set_SE_HCOEF2_17_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_17_reg)=data)
#define set_SE_HCOEF2_18_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_18_reg)=data)
#define set_SE_HCOEF2_19_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_19_reg)=data)
#define set_SE_HCOEF2_20_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_20_reg)=data)
#define set_SE_HCOEF2_21_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_21_reg)=data)
#define set_SE_HCOEF2_22_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_22_reg)=data)
#define set_SE_HCOEF2_23_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_23_reg)=data)
#define set_SE_HCOEF2_24_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_24_reg)=data)
#define set_SE_HCOEF2_25_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_25_reg)=data)
#define set_SE_HCOEF2_26_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_26_reg)=data)
#define set_SE_HCOEF2_27_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_27_reg)=data)
#define set_SE_HCOEF2_28_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_28_reg)=data)
#define set_SE_HCOEF2_29_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_29_reg)=data)
#define set_SE_HCOEF2_30_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_30_reg)=data)
#define set_SE_HCOEF2_31_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_31_reg)=data)
#define get_SE_HCOEF2_0_reg   (*((volatile unsigned int*) SE_HCOEF2_0_reg))
#define get_SE_HCOEF2_1_reg   (*((volatile unsigned int*) SE_HCOEF2_1_reg))
#define get_SE_HCOEF2_2_reg   (*((volatile unsigned int*) SE_HCOEF2_2_reg))
#define get_SE_HCOEF2_3_reg   (*((volatile unsigned int*) SE_HCOEF2_3_reg))
#define get_SE_HCOEF2_4_reg   (*((volatile unsigned int*) SE_HCOEF2_4_reg))
#define get_SE_HCOEF2_5_reg   (*((volatile unsigned int*) SE_HCOEF2_5_reg))
#define get_SE_HCOEF2_6_reg   (*((volatile unsigned int*) SE_HCOEF2_6_reg))
#define get_SE_HCOEF2_7_reg   (*((volatile unsigned int*) SE_HCOEF2_7_reg))
#define get_SE_HCOEF2_8_reg   (*((volatile unsigned int*) SE_HCOEF2_8_reg))
#define get_SE_HCOEF2_9_reg   (*((volatile unsigned int*) SE_HCOEF2_9_reg))
#define get_SE_HCOEF2_10_reg   (*((volatile unsigned int*) SE_HCOEF2_10_reg))
#define get_SE_HCOEF2_11_reg   (*((volatile unsigned int*) SE_HCOEF2_11_reg))
#define get_SE_HCOEF2_12_reg   (*((volatile unsigned int*) SE_HCOEF2_12_reg))
#define get_SE_HCOEF2_13_reg   (*((volatile unsigned int*) SE_HCOEF2_13_reg))
#define get_SE_HCOEF2_14_reg   (*((volatile unsigned int*) SE_HCOEF2_14_reg))
#define get_SE_HCOEF2_15_reg   (*((volatile unsigned int*) SE_HCOEF2_15_reg))
#define get_SE_HCOEF2_16_reg   (*((volatile unsigned int*) SE_HCOEF2_16_reg))
#define get_SE_HCOEF2_17_reg   (*((volatile unsigned int*) SE_HCOEF2_17_reg))
#define get_SE_HCOEF2_18_reg   (*((volatile unsigned int*) SE_HCOEF2_18_reg))
#define get_SE_HCOEF2_19_reg   (*((volatile unsigned int*) SE_HCOEF2_19_reg))
#define get_SE_HCOEF2_20_reg   (*((volatile unsigned int*) SE_HCOEF2_20_reg))
#define get_SE_HCOEF2_21_reg   (*((volatile unsigned int*) SE_HCOEF2_21_reg))
#define get_SE_HCOEF2_22_reg   (*((volatile unsigned int*) SE_HCOEF2_22_reg))
#define get_SE_HCOEF2_23_reg   (*((volatile unsigned int*) SE_HCOEF2_23_reg))
#define get_SE_HCOEF2_24_reg   (*((volatile unsigned int*) SE_HCOEF2_24_reg))
#define get_SE_HCOEF2_25_reg   (*((volatile unsigned int*) SE_HCOEF2_25_reg))
#define get_SE_HCOEF2_26_reg   (*((volatile unsigned int*) SE_HCOEF2_26_reg))
#define get_SE_HCOEF2_27_reg   (*((volatile unsigned int*) SE_HCOEF2_27_reg))
#define get_SE_HCOEF2_28_reg   (*((volatile unsigned int*) SE_HCOEF2_28_reg))
#define get_SE_HCOEF2_29_reg   (*((volatile unsigned int*) SE_HCOEF2_29_reg))
#define get_SE_HCOEF2_30_reg   (*((volatile unsigned int*) SE_HCOEF2_30_reg))
#define get_SE_HCOEF2_31_reg   (*((volatile unsigned int*) SE_HCOEF2_31_reg))
#define SE_HCOEF2_0_inst_adr                                                         "0x00B0"
#define SE_HCOEF2_1_inst_adr                                                         "0x00B1"
#define SE_HCOEF2_2_inst_adr                                                         "0x00B2"
#define SE_HCOEF2_3_inst_adr                                                         "0x00B3"
#define SE_HCOEF2_4_inst_adr                                                         "0x00B4"
#define SE_HCOEF2_5_inst_adr                                                         "0x00B5"
#define SE_HCOEF2_6_inst_adr                                                         "0x00B6"
#define SE_HCOEF2_7_inst_adr                                                         "0x00B7"
#define SE_HCOEF2_8_inst_adr                                                         "0x00B8"
#define SE_HCOEF2_9_inst_adr                                                         "0x00B9"
#define SE_HCOEF2_10_inst_adr                                                         "0x00BA"
#define SE_HCOEF2_11_inst_adr                                                         "0x00BB"
#define SE_HCOEF2_12_inst_adr                                                         "0x00BC"
#define SE_HCOEF2_13_inst_adr                                                         "0x00BD"
#define SE_HCOEF2_14_inst_adr                                                         "0x00BE"
#define SE_HCOEF2_15_inst_adr                                                         "0x00BF"
#define SE_HCOEF2_16_inst_adr                                                         "0x00C0"
#define SE_HCOEF2_17_inst_adr                                                         "0x00C1"
#define SE_HCOEF2_18_inst_adr                                                         "0x00C2"
#define SE_HCOEF2_19_inst_adr                                                         "0x00C3"
#define SE_HCOEF2_20_inst_adr                                                         "0x00C4"
#define SE_HCOEF2_21_inst_adr                                                         "0x00C5"
#define SE_HCOEF2_22_inst_adr                                                         "0x00C6"
#define SE_HCOEF2_23_inst_adr                                                         "0x00C7"
#define SE_HCOEF2_24_inst_adr                                                         "0x00C8"
#define SE_HCOEF2_25_inst_adr                                                         "0x00C9"
#define SE_HCOEF2_26_inst_adr                                                         "0x00CA"
#define SE_HCOEF2_27_inst_adr                                                         "0x00CB"
#define SE_HCOEF2_28_inst_adr                                                         "0x00CC"
#define SE_HCOEF2_29_inst_adr                                                         "0x00CD"
#define SE_HCOEF2_30_inst_adr                                                         "0x00CE"
#define SE_HCOEF2_31_inst_adr                                                         "0x00CF"
#define SE_HCOEF2_0_inst                                                             0x00B0
#define SE_HCOEF2_1_inst                                                             0x00B1
#define SE_HCOEF2_2_inst                                                             0x00B2
#define SE_HCOEF2_3_inst                                                             0x00B3
#define SE_HCOEF2_4_inst                                                             0x00B4
#define SE_HCOEF2_5_inst                                                             0x00B5
#define SE_HCOEF2_6_inst                                                             0x00B6
#define SE_HCOEF2_7_inst                                                             0x00B7
#define SE_HCOEF2_8_inst                                                             0x00B8
#define SE_HCOEF2_9_inst                                                             0x00B9
#define SE_HCOEF2_10_inst                                                             0x00BA
#define SE_HCOEF2_11_inst                                                             0x00BB
#define SE_HCOEF2_12_inst                                                             0x00BC
#define SE_HCOEF2_13_inst                                                             0x00BD
#define SE_HCOEF2_14_inst                                                             0x00BE
#define SE_HCOEF2_15_inst                                                             0x00BF
#define SE_HCOEF2_16_inst                                                             0x00C0
#define SE_HCOEF2_17_inst                                                             0x00C1
#define SE_HCOEF2_18_inst                                                             0x00C2
#define SE_HCOEF2_19_inst                                                             0x00C3
#define SE_HCOEF2_20_inst                                                             0x00C4
#define SE_HCOEF2_21_inst                                                             0x00C5
#define SE_HCOEF2_22_inst                                                             0x00C6
#define SE_HCOEF2_23_inst                                                             0x00C7
#define SE_HCOEF2_24_inst                                                             0x00C8
#define SE_HCOEF2_25_inst                                                             0x00C9
#define SE_HCOEF2_26_inst                                                             0x00CA
#define SE_HCOEF2_27_inst                                                             0x00CB
#define SE_HCOEF2_28_inst                                                             0x00CC
#define SE_HCOEF2_29_inst                                                             0x00CD
#define SE_HCOEF2_30_inst                                                             0x00CE
#define SE_HCOEF2_31_inst                                                             0x00CF
#define SE_HCOEF2_hcoef_shift                                                        (0)
#define SE_HCOEF2_hcoef_mask                                                         (0x00003FFF)
#define SE_HCOEF2_hcoef(data)                                                        (0x00003FFF&((data)<<0))
#define SE_HCOEF2_hcoef_src(data)                                                    ((0x00003FFF&(data))>>0)
#define SE_HCOEF2_get_hcoef(data)                                                    ((0x00003FFF&(data))>>0)


#define SE_HCOEF2_32_0                                                               0x1800C618
#define SE_HCOEF2_32_1                                                               0x1800C61C
#define SE_HCOEF2_32_2                                                               0x1800C620
#define SE_HCOEF2_32_3                                                               0x1800C624
#define SE_HCOEF2_32_4                                                               0x1800C628
#define SE_HCOEF2_32_5                                                               0x1800C62C
#define SE_HCOEF2_32_6                                                               0x1800C630
#define SE_HCOEF2_32_7                                                               0x1800C634
#define SE_HCOEF2_32_8                                                               0x1800C638
#define SE_HCOEF2_32_9                                                               0x1800C63C
#define SE_HCOEF2_32_10                                                               0x1800C640
#define SE_HCOEF2_32_11                                                               0x1800C644
#define SE_HCOEF2_32_12                                                               0x1800C648
#define SE_HCOEF2_32_13                                                               0x1800C64C
#define SE_HCOEF2_32_14                                                               0x1800C650
#define SE_HCOEF2_32_15                                                               0x1800C654
#define SE_HCOEF2_32_16                                                               0x1800C658
#define SE_HCOEF2_32_17                                                               0x1800C65C
#define SE_HCOEF2_32_18                                                               0x1800C660
#define SE_HCOEF2_32_19                                                               0x1800C664
#define SE_HCOEF2_32_20                                                               0x1800C668
#define SE_HCOEF2_32_21                                                               0x1800C66C
#define SE_HCOEF2_32_22                                                               0x1800C670
#define SE_HCOEF2_32_23                                                               0x1800C674
#define SE_HCOEF2_32_24                                                               0x1800C678
#define SE_HCOEF2_32_25                                                               0x1800C67C
#define SE_HCOEF2_32_26                                                               0x1800C680
#define SE_HCOEF2_32_27                                                               0x1800C684
#define SE_HCOEF2_32_28                                                               0x1800C688
#define SE_HCOEF2_32_29                                                               0x1800C68C
#define SE_HCOEF2_32_30                                                               0x1800C690
#define SE_HCOEF2_32_31                                                               0x1800C694
#define SE_HCOEF2_32_0_reg_addr                                                      "0xB800C618"
#define SE_HCOEF2_32_1_reg_addr                                                      "0xB800C61C"
#define SE_HCOEF2_32_2_reg_addr                                                      "0xB800C620"
#define SE_HCOEF2_32_3_reg_addr                                                      "0xB800C624"
#define SE_HCOEF2_32_4_reg_addr                                                      "0xB800C628"
#define SE_HCOEF2_32_5_reg_addr                                                      "0xB800C62C"
#define SE_HCOEF2_32_6_reg_addr                                                      "0xB800C630"
#define SE_HCOEF2_32_7_reg_addr                                                      "0xB800C634"
#define SE_HCOEF2_32_8_reg_addr                                                      "0xB800C638"
#define SE_HCOEF2_32_9_reg_addr                                                      "0xB800C63C"
#define SE_HCOEF2_32_10_reg_addr                                                      "0xB800C640"
#define SE_HCOEF2_32_11_reg_addr                                                      "0xB800C644"
#define SE_HCOEF2_32_12_reg_addr                                                      "0xB800C648"
#define SE_HCOEF2_32_13_reg_addr                                                      "0xB800C64C"
#define SE_HCOEF2_32_14_reg_addr                                                      "0xB800C650"
#define SE_HCOEF2_32_15_reg_addr                                                      "0xB800C654"
#define SE_HCOEF2_32_16_reg_addr                                                      "0xB800C658"
#define SE_HCOEF2_32_17_reg_addr                                                      "0xB800C65C"
#define SE_HCOEF2_32_18_reg_addr                                                      "0xB800C660"
#define SE_HCOEF2_32_19_reg_addr                                                      "0xB800C664"
#define SE_HCOEF2_32_20_reg_addr                                                      "0xB800C668"
#define SE_HCOEF2_32_21_reg_addr                                                      "0xB800C66C"
#define SE_HCOEF2_32_22_reg_addr                                                      "0xB800C670"
#define SE_HCOEF2_32_23_reg_addr                                                      "0xB800C674"
#define SE_HCOEF2_32_24_reg_addr                                                      "0xB800C678"
#define SE_HCOEF2_32_25_reg_addr                                                      "0xB800C67C"
#define SE_HCOEF2_32_26_reg_addr                                                      "0xB800C680"
#define SE_HCOEF2_32_27_reg_addr                                                      "0xB800C684"
#define SE_HCOEF2_32_28_reg_addr                                                      "0xB800C688"
#define SE_HCOEF2_32_29_reg_addr                                                      "0xB800C68C"
#define SE_HCOEF2_32_30_reg_addr                                                      "0xB800C690"
#define SE_HCOEF2_32_31_reg_addr                                                      "0xB800C694"
#define SE_HCOEF2_32_0_reg                                                           0xB800C618
#define SE_HCOEF2_32_1_reg                                                           0xB800C61C
#define SE_HCOEF2_32_2_reg                                                           0xB800C620
#define SE_HCOEF2_32_3_reg                                                           0xB800C624
#define SE_HCOEF2_32_4_reg                                                           0xB800C628
#define SE_HCOEF2_32_5_reg                                                           0xB800C62C
#define SE_HCOEF2_32_6_reg                                                           0xB800C630
#define SE_HCOEF2_32_7_reg                                                           0xB800C634
#define SE_HCOEF2_32_8_reg                                                           0xB800C638
#define SE_HCOEF2_32_9_reg                                                           0xB800C63C
#define SE_HCOEF2_32_10_reg                                                           0xB800C640
#define SE_HCOEF2_32_11_reg                                                           0xB800C644
#define SE_HCOEF2_32_12_reg                                                           0xB800C648
#define SE_HCOEF2_32_13_reg                                                           0xB800C64C
#define SE_HCOEF2_32_14_reg                                                           0xB800C650
#define SE_HCOEF2_32_15_reg                                                           0xB800C654
#define SE_HCOEF2_32_16_reg                                                           0xB800C658
#define SE_HCOEF2_32_17_reg                                                           0xB800C65C
#define SE_HCOEF2_32_18_reg                                                           0xB800C660
#define SE_HCOEF2_32_19_reg                                                           0xB800C664
#define SE_HCOEF2_32_20_reg                                                           0xB800C668
#define SE_HCOEF2_32_21_reg                                                           0xB800C66C
#define SE_HCOEF2_32_22_reg                                                           0xB800C670
#define SE_HCOEF2_32_23_reg                                                           0xB800C674
#define SE_HCOEF2_32_24_reg                                                           0xB800C678
#define SE_HCOEF2_32_25_reg                                                           0xB800C67C
#define SE_HCOEF2_32_26_reg                                                           0xB800C680
#define SE_HCOEF2_32_27_reg                                                           0xB800C684
#define SE_HCOEF2_32_28_reg                                                           0xB800C688
#define SE_HCOEF2_32_29_reg                                                           0xB800C68C
#define SE_HCOEF2_32_30_reg                                                           0xB800C690
#define SE_HCOEF2_32_31_reg                                                           0xB800C694
#define set_SE_HCOEF2_32_0_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_0_reg)=data)
#define set_SE_HCOEF2_32_1_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_1_reg)=data)
#define set_SE_HCOEF2_32_2_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_2_reg)=data)
#define set_SE_HCOEF2_32_3_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_3_reg)=data)
#define set_SE_HCOEF2_32_4_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_4_reg)=data)
#define set_SE_HCOEF2_32_5_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_5_reg)=data)
#define set_SE_HCOEF2_32_6_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_6_reg)=data)
#define set_SE_HCOEF2_32_7_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_7_reg)=data)
#define set_SE_HCOEF2_32_8_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_8_reg)=data)
#define set_SE_HCOEF2_32_9_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_9_reg)=data)
#define set_SE_HCOEF2_32_10_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_10_reg)=data)
#define set_SE_HCOEF2_32_11_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_11_reg)=data)
#define set_SE_HCOEF2_32_12_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_12_reg)=data)
#define set_SE_HCOEF2_32_13_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_13_reg)=data)
#define set_SE_HCOEF2_32_14_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_14_reg)=data)
#define set_SE_HCOEF2_32_15_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_15_reg)=data)
#define set_SE_HCOEF2_32_16_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_16_reg)=data)
#define set_SE_HCOEF2_32_17_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_17_reg)=data)
#define set_SE_HCOEF2_32_18_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_18_reg)=data)
#define set_SE_HCOEF2_32_19_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_19_reg)=data)
#define set_SE_HCOEF2_32_20_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_20_reg)=data)
#define set_SE_HCOEF2_32_21_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_21_reg)=data)
#define set_SE_HCOEF2_32_22_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_22_reg)=data)
#define set_SE_HCOEF2_32_23_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_23_reg)=data)
#define set_SE_HCOEF2_32_24_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_24_reg)=data)
#define set_SE_HCOEF2_32_25_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_25_reg)=data)
#define set_SE_HCOEF2_32_26_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_26_reg)=data)
#define set_SE_HCOEF2_32_27_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_27_reg)=data)
#define set_SE_HCOEF2_32_28_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_28_reg)=data)
#define set_SE_HCOEF2_32_29_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_29_reg)=data)
#define set_SE_HCOEF2_32_30_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_30_reg)=data)
#define set_SE_HCOEF2_32_31_reg(data)   (*((volatile unsigned int*) SE_HCOEF2_32_31_reg)=data)
#define get_SE_HCOEF2_32_0_reg   (*((volatile unsigned int*) SE_HCOEF2_32_0_reg))
#define get_SE_HCOEF2_32_1_reg   (*((volatile unsigned int*) SE_HCOEF2_32_1_reg))
#define get_SE_HCOEF2_32_2_reg   (*((volatile unsigned int*) SE_HCOEF2_32_2_reg))
#define get_SE_HCOEF2_32_3_reg   (*((volatile unsigned int*) SE_HCOEF2_32_3_reg))
#define get_SE_HCOEF2_32_4_reg   (*((volatile unsigned int*) SE_HCOEF2_32_4_reg))
#define get_SE_HCOEF2_32_5_reg   (*((volatile unsigned int*) SE_HCOEF2_32_5_reg))
#define get_SE_HCOEF2_32_6_reg   (*((volatile unsigned int*) SE_HCOEF2_32_6_reg))
#define get_SE_HCOEF2_32_7_reg   (*((volatile unsigned int*) SE_HCOEF2_32_7_reg))
#define get_SE_HCOEF2_32_8_reg   (*((volatile unsigned int*) SE_HCOEF2_32_8_reg))
#define get_SE_HCOEF2_32_9_reg   (*((volatile unsigned int*) SE_HCOEF2_32_9_reg))
#define get_SE_HCOEF2_32_10_reg   (*((volatile unsigned int*) SE_HCOEF2_32_10_reg))
#define get_SE_HCOEF2_32_11_reg   (*((volatile unsigned int*) SE_HCOEF2_32_11_reg))
#define get_SE_HCOEF2_32_12_reg   (*((volatile unsigned int*) SE_HCOEF2_32_12_reg))
#define get_SE_HCOEF2_32_13_reg   (*((volatile unsigned int*) SE_HCOEF2_32_13_reg))
#define get_SE_HCOEF2_32_14_reg   (*((volatile unsigned int*) SE_HCOEF2_32_14_reg))
#define get_SE_HCOEF2_32_15_reg   (*((volatile unsigned int*) SE_HCOEF2_32_15_reg))
#define get_SE_HCOEF2_32_16_reg   (*((volatile unsigned int*) SE_HCOEF2_32_16_reg))
#define get_SE_HCOEF2_32_17_reg   (*((volatile unsigned int*) SE_HCOEF2_32_17_reg))
#define get_SE_HCOEF2_32_18_reg   (*((volatile unsigned int*) SE_HCOEF2_32_18_reg))
#define get_SE_HCOEF2_32_19_reg   (*((volatile unsigned int*) SE_HCOEF2_32_19_reg))
#define get_SE_HCOEF2_32_20_reg   (*((volatile unsigned int*) SE_HCOEF2_32_20_reg))
#define get_SE_HCOEF2_32_21_reg   (*((volatile unsigned int*) SE_HCOEF2_32_21_reg))
#define get_SE_HCOEF2_32_22_reg   (*((volatile unsigned int*) SE_HCOEF2_32_22_reg))
#define get_SE_HCOEF2_32_23_reg   (*((volatile unsigned int*) SE_HCOEF2_32_23_reg))
#define get_SE_HCOEF2_32_24_reg   (*((volatile unsigned int*) SE_HCOEF2_32_24_reg))
#define get_SE_HCOEF2_32_25_reg   (*((volatile unsigned int*) SE_HCOEF2_32_25_reg))
#define get_SE_HCOEF2_32_26_reg   (*((volatile unsigned int*) SE_HCOEF2_32_26_reg))
#define get_SE_HCOEF2_32_27_reg   (*((volatile unsigned int*) SE_HCOEF2_32_27_reg))
#define get_SE_HCOEF2_32_28_reg   (*((volatile unsigned int*) SE_HCOEF2_32_28_reg))
#define get_SE_HCOEF2_32_29_reg   (*((volatile unsigned int*) SE_HCOEF2_32_29_reg))
#define get_SE_HCOEF2_32_30_reg   (*((volatile unsigned int*) SE_HCOEF2_32_30_reg))
#define get_SE_HCOEF2_32_31_reg   (*((volatile unsigned int*) SE_HCOEF2_32_31_reg))
#define SE_HCOEF2_32_0_inst_adr                                                      "0x0086"
#define SE_HCOEF2_32_1_inst_adr                                                      "0x0087"
#define SE_HCOEF2_32_2_inst_adr                                                      "0x0088"
#define SE_HCOEF2_32_3_inst_adr                                                      "0x0089"
#define SE_HCOEF2_32_4_inst_adr                                                      "0x008A"
#define SE_HCOEF2_32_5_inst_adr                                                      "0x008B"
#define SE_HCOEF2_32_6_inst_adr                                                      "0x008C"
#define SE_HCOEF2_32_7_inst_adr                                                      "0x008D"
#define SE_HCOEF2_32_8_inst_adr                                                      "0x008E"
#define SE_HCOEF2_32_9_inst_adr                                                      "0x008F"
#define SE_HCOEF2_32_10_inst_adr                                                      "0x0090"
#define SE_HCOEF2_32_11_inst_adr                                                      "0x0091"
#define SE_HCOEF2_32_12_inst_adr                                                      "0x0092"
#define SE_HCOEF2_32_13_inst_adr                                                      "0x0093"
#define SE_HCOEF2_32_14_inst_adr                                                      "0x0094"
#define SE_HCOEF2_32_15_inst_adr                                                      "0x0095"
#define SE_HCOEF2_32_16_inst_adr                                                      "0x0096"
#define SE_HCOEF2_32_17_inst_adr                                                      "0x0097"
#define SE_HCOEF2_32_18_inst_adr                                                      "0x0098"
#define SE_HCOEF2_32_19_inst_adr                                                      "0x0099"
#define SE_HCOEF2_32_20_inst_adr                                                      "0x009A"
#define SE_HCOEF2_32_21_inst_adr                                                      "0x009B"
#define SE_HCOEF2_32_22_inst_adr                                                      "0x009C"
#define SE_HCOEF2_32_23_inst_adr                                                      "0x009D"
#define SE_HCOEF2_32_24_inst_adr                                                      "0x009E"
#define SE_HCOEF2_32_25_inst_adr                                                      "0x009F"
#define SE_HCOEF2_32_26_inst_adr                                                      "0x00A0"
#define SE_HCOEF2_32_27_inst_adr                                                      "0x00A1"
#define SE_HCOEF2_32_28_inst_adr                                                      "0x00A2"
#define SE_HCOEF2_32_29_inst_adr                                                      "0x00A3"
#define SE_HCOEF2_32_30_inst_adr                                                      "0x00A4"
#define SE_HCOEF2_32_31_inst_adr                                                      "0x00A5"
#define SE_HCOEF2_32_0_inst                                                          0x0086
#define SE_HCOEF2_32_1_inst                                                          0x0087
#define SE_HCOEF2_32_2_inst                                                          0x0088
#define SE_HCOEF2_32_3_inst                                                          0x0089
#define SE_HCOEF2_32_4_inst                                                          0x008A
#define SE_HCOEF2_32_5_inst                                                          0x008B
#define SE_HCOEF2_32_6_inst                                                          0x008C
#define SE_HCOEF2_32_7_inst                                                          0x008D
#define SE_HCOEF2_32_8_inst                                                          0x008E
#define SE_HCOEF2_32_9_inst                                                          0x008F
#define SE_HCOEF2_32_10_inst                                                          0x0090
#define SE_HCOEF2_32_11_inst                                                          0x0091
#define SE_HCOEF2_32_12_inst                                                          0x0092
#define SE_HCOEF2_32_13_inst                                                          0x0093
#define SE_HCOEF2_32_14_inst                                                          0x0094
#define SE_HCOEF2_32_15_inst                                                          0x0095
#define SE_HCOEF2_32_16_inst                                                          0x0096
#define SE_HCOEF2_32_17_inst                                                          0x0097
#define SE_HCOEF2_32_18_inst                                                          0x0098
#define SE_HCOEF2_32_19_inst                                                          0x0099
#define SE_HCOEF2_32_20_inst                                                          0x009A
#define SE_HCOEF2_32_21_inst                                                          0x009B
#define SE_HCOEF2_32_22_inst                                                          0x009C
#define SE_HCOEF2_32_23_inst                                                          0x009D
#define SE_HCOEF2_32_24_inst                                                          0x009E
#define SE_HCOEF2_32_25_inst                                                          0x009F
#define SE_HCOEF2_32_26_inst                                                          0x00A0
#define SE_HCOEF2_32_27_inst                                                          0x00A1
#define SE_HCOEF2_32_28_inst                                                          0x00A2
#define SE_HCOEF2_32_29_inst                                                          0x00A3
#define SE_HCOEF2_32_30_inst                                                          0x00A4
#define SE_HCOEF2_32_31_inst                                                          0x00A5
#define SE_HCOEF2_32_hcoef_shift                                                     (0)
#define SE_HCOEF2_32_hcoef_mask                                                      (0x00003FFF)
#define SE_HCOEF2_32_hcoef(data)                                                     (0x00003FFF&((data)<<0))
#define SE_HCOEF2_32_hcoef_src(data)                                                 ((0x00003FFF&(data))>>0)
#define SE_HCOEF2_32_get_hcoef(data)                                                 ((0x00003FFF&(data))>>0)


#define SE_VCOEF2_0                                                                  0x1800C340
#define SE_VCOEF2_1                                                                  0x1800C344
#define SE_VCOEF2_2                                                                  0x1800C348
#define SE_VCOEF2_3                                                                  0x1800C34C
#define SE_VCOEF2_4                                                                  0x1800C350
#define SE_VCOEF2_5                                                                  0x1800C354
#define SE_VCOEF2_6                                                                  0x1800C358
#define SE_VCOEF2_7                                                                  0x1800C35C
#define SE_VCOEF2_8                                                                  0x1800C360
#define SE_VCOEF2_9                                                                  0x1800C364
#define SE_VCOEF2_10                                                                  0x1800C368
#define SE_VCOEF2_11                                                                  0x1800C36C
#define SE_VCOEF2_12                                                                  0x1800C370
#define SE_VCOEF2_13                                                                  0x1800C374
#define SE_VCOEF2_14                                                                  0x1800C378
#define SE_VCOEF2_15                                                                  0x1800C37C
#define SE_VCOEF2_0_reg_addr                                                         "0xB800C340"
#define SE_VCOEF2_1_reg_addr                                                         "0xB800C344"
#define SE_VCOEF2_2_reg_addr                                                         "0xB800C348"
#define SE_VCOEF2_3_reg_addr                                                         "0xB800C34C"
#define SE_VCOEF2_4_reg_addr                                                         "0xB800C350"
#define SE_VCOEF2_5_reg_addr                                                         "0xB800C354"
#define SE_VCOEF2_6_reg_addr                                                         "0xB800C358"
#define SE_VCOEF2_7_reg_addr                                                         "0xB800C35C"
#define SE_VCOEF2_8_reg_addr                                                         "0xB800C360"
#define SE_VCOEF2_9_reg_addr                                                         "0xB800C364"
#define SE_VCOEF2_10_reg_addr                                                         "0xB800C368"
#define SE_VCOEF2_11_reg_addr                                                         "0xB800C36C"
#define SE_VCOEF2_12_reg_addr                                                         "0xB800C370"
#define SE_VCOEF2_13_reg_addr                                                         "0xB800C374"
#define SE_VCOEF2_14_reg_addr                                                         "0xB800C378"
#define SE_VCOEF2_15_reg_addr                                                         "0xB800C37C"
#define SE_VCOEF2_0_reg                                                              0xB800C340
#define SE_VCOEF2_1_reg                                                              0xB800C344
#define SE_VCOEF2_2_reg                                                              0xB800C348
#define SE_VCOEF2_3_reg                                                              0xB800C34C
#define SE_VCOEF2_4_reg                                                              0xB800C350
#define SE_VCOEF2_5_reg                                                              0xB800C354
#define SE_VCOEF2_6_reg                                                              0xB800C358
#define SE_VCOEF2_7_reg                                                              0xB800C35C
#define SE_VCOEF2_8_reg                                                              0xB800C360
#define SE_VCOEF2_9_reg                                                              0xB800C364
#define SE_VCOEF2_10_reg                                                              0xB800C368
#define SE_VCOEF2_11_reg                                                              0xB800C36C
#define SE_VCOEF2_12_reg                                                              0xB800C370
#define SE_VCOEF2_13_reg                                                              0xB800C374
#define SE_VCOEF2_14_reg                                                              0xB800C378
#define SE_VCOEF2_15_reg                                                              0xB800C37C
#define set_SE_VCOEF2_0_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_0_reg)=data)
#define set_SE_VCOEF2_1_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_1_reg)=data)
#define set_SE_VCOEF2_2_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_2_reg)=data)
#define set_SE_VCOEF2_3_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_3_reg)=data)
#define set_SE_VCOEF2_4_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_4_reg)=data)
#define set_SE_VCOEF2_5_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_5_reg)=data)
#define set_SE_VCOEF2_6_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_6_reg)=data)
#define set_SE_VCOEF2_7_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_7_reg)=data)
#define set_SE_VCOEF2_8_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_8_reg)=data)
#define set_SE_VCOEF2_9_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_9_reg)=data)
#define set_SE_VCOEF2_10_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_10_reg)=data)
#define set_SE_VCOEF2_11_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_11_reg)=data)
#define set_SE_VCOEF2_12_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_12_reg)=data)
#define set_SE_VCOEF2_13_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_13_reg)=data)
#define set_SE_VCOEF2_14_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_14_reg)=data)
#define set_SE_VCOEF2_15_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_15_reg)=data)
#define get_SE_VCOEF2_0_reg   (*((volatile unsigned int*) SE_VCOEF2_0_reg))
#define get_SE_VCOEF2_1_reg   (*((volatile unsigned int*) SE_VCOEF2_1_reg))
#define get_SE_VCOEF2_2_reg   (*((volatile unsigned int*) SE_VCOEF2_2_reg))
#define get_SE_VCOEF2_3_reg   (*((volatile unsigned int*) SE_VCOEF2_3_reg))
#define get_SE_VCOEF2_4_reg   (*((volatile unsigned int*) SE_VCOEF2_4_reg))
#define get_SE_VCOEF2_5_reg   (*((volatile unsigned int*) SE_VCOEF2_5_reg))
#define get_SE_VCOEF2_6_reg   (*((volatile unsigned int*) SE_VCOEF2_6_reg))
#define get_SE_VCOEF2_7_reg   (*((volatile unsigned int*) SE_VCOEF2_7_reg))
#define get_SE_VCOEF2_8_reg   (*((volatile unsigned int*) SE_VCOEF2_8_reg))
#define get_SE_VCOEF2_9_reg   (*((volatile unsigned int*) SE_VCOEF2_9_reg))
#define get_SE_VCOEF2_10_reg   (*((volatile unsigned int*) SE_VCOEF2_10_reg))
#define get_SE_VCOEF2_11_reg   (*((volatile unsigned int*) SE_VCOEF2_11_reg))
#define get_SE_VCOEF2_12_reg   (*((volatile unsigned int*) SE_VCOEF2_12_reg))
#define get_SE_VCOEF2_13_reg   (*((volatile unsigned int*) SE_VCOEF2_13_reg))
#define get_SE_VCOEF2_14_reg   (*((volatile unsigned int*) SE_VCOEF2_14_reg))
#define get_SE_VCOEF2_15_reg   (*((volatile unsigned int*) SE_VCOEF2_15_reg))
#define SE_VCOEF2_0_inst_adr                                                         "0x00D0"
#define SE_VCOEF2_1_inst_adr                                                         "0x00D1"
#define SE_VCOEF2_2_inst_adr                                                         "0x00D2"
#define SE_VCOEF2_3_inst_adr                                                         "0x00D3"
#define SE_VCOEF2_4_inst_adr                                                         "0x00D4"
#define SE_VCOEF2_5_inst_adr                                                         "0x00D5"
#define SE_VCOEF2_6_inst_adr                                                         "0x00D6"
#define SE_VCOEF2_7_inst_adr                                                         "0x00D7"
#define SE_VCOEF2_8_inst_adr                                                         "0x00D8"
#define SE_VCOEF2_9_inst_adr                                                         "0x00D9"
#define SE_VCOEF2_10_inst_adr                                                         "0x00DA"
#define SE_VCOEF2_11_inst_adr                                                         "0x00DB"
#define SE_VCOEF2_12_inst_adr                                                         "0x00DC"
#define SE_VCOEF2_13_inst_adr                                                         "0x00DD"
#define SE_VCOEF2_14_inst_adr                                                         "0x00DE"
#define SE_VCOEF2_15_inst_adr                                                         "0x00DF"
#define SE_VCOEF2_0_inst                                                             0x00D0
#define SE_VCOEF2_1_inst                                                             0x00D1
#define SE_VCOEF2_2_inst                                                             0x00D2
#define SE_VCOEF2_3_inst                                                             0x00D3
#define SE_VCOEF2_4_inst                                                             0x00D4
#define SE_VCOEF2_5_inst                                                             0x00D5
#define SE_VCOEF2_6_inst                                                             0x00D6
#define SE_VCOEF2_7_inst                                                             0x00D7
#define SE_VCOEF2_8_inst                                                             0x00D8
#define SE_VCOEF2_9_inst                                                             0x00D9
#define SE_VCOEF2_10_inst                                                             0x00DA
#define SE_VCOEF2_11_inst                                                             0x00DB
#define SE_VCOEF2_12_inst                                                             0x00DC
#define SE_VCOEF2_13_inst                                                             0x00DD
#define SE_VCOEF2_14_inst                                                             0x00DE
#define SE_VCOEF2_15_inst                                                             0x00DF
#define SE_VCOEF2_vcoef_shift                                                        (0)
#define SE_VCOEF2_vcoef_mask                                                         (0x00003FFF)
#define SE_VCOEF2_vcoef(data)                                                        (0x00003FFF&((data)<<0))
#define SE_VCOEF2_vcoef_src(data)                                                    ((0x00003FFF&(data))>>0)
#define SE_VCOEF2_get_vcoef(data)                                                    ((0x00003FFF&(data))>>0)


#define SE_VCOEF2_16_0                                                               0x1800C698
#define SE_VCOEF2_16_1                                                               0x1800C69C
#define SE_VCOEF2_16_2                                                               0x1800C6A0
#define SE_VCOEF2_16_3                                                               0x1800C6A4
#define SE_VCOEF2_16_4                                                               0x1800C6A8
#define SE_VCOEF2_16_5                                                               0x1800C6AC
#define SE_VCOEF2_16_6                                                               0x1800C6B0
#define SE_VCOEF2_16_7                                                               0x1800C6B4
#define SE_VCOEF2_16_8                                                               0x1800C6B8
#define SE_VCOEF2_16_9                                                               0x1800C6BC
#define SE_VCOEF2_16_10                                                               0x1800C6C0
#define SE_VCOEF2_16_11                                                               0x1800C6C4
#define SE_VCOEF2_16_12                                                               0x1800C6C8
#define SE_VCOEF2_16_13                                                               0x1800C6CC
#define SE_VCOEF2_16_14                                                               0x1800C6D0
#define SE_VCOEF2_16_15                                                               0x1800C6D4
#define SE_VCOEF2_16_0_reg_addr                                                      "0xB800C698"
#define SE_VCOEF2_16_1_reg_addr                                                      "0xB800C69C"
#define SE_VCOEF2_16_2_reg_addr                                                      "0xB800C6A0"
#define SE_VCOEF2_16_3_reg_addr                                                      "0xB800C6A4"
#define SE_VCOEF2_16_4_reg_addr                                                      "0xB800C6A8"
#define SE_VCOEF2_16_5_reg_addr                                                      "0xB800C6AC"
#define SE_VCOEF2_16_6_reg_addr                                                      "0xB800C6B0"
#define SE_VCOEF2_16_7_reg_addr                                                      "0xB800C6B4"
#define SE_VCOEF2_16_8_reg_addr                                                      "0xB800C6B8"
#define SE_VCOEF2_16_9_reg_addr                                                      "0xB800C6BC"
#define SE_VCOEF2_16_10_reg_addr                                                      "0xB800C6C0"
#define SE_VCOEF2_16_11_reg_addr                                                      "0xB800C6C4"
#define SE_VCOEF2_16_12_reg_addr                                                      "0xB800C6C8"
#define SE_VCOEF2_16_13_reg_addr                                                      "0xB800C6CC"
#define SE_VCOEF2_16_14_reg_addr                                                      "0xB800C6D0"
#define SE_VCOEF2_16_15_reg_addr                                                      "0xB800C6D4"
#define SE_VCOEF2_16_0_reg                                                           0xB800C698
#define SE_VCOEF2_16_1_reg                                                           0xB800C69C
#define SE_VCOEF2_16_2_reg                                                           0xB800C6A0
#define SE_VCOEF2_16_3_reg                                                           0xB800C6A4
#define SE_VCOEF2_16_4_reg                                                           0xB800C6A8
#define SE_VCOEF2_16_5_reg                                                           0xB800C6AC
#define SE_VCOEF2_16_6_reg                                                           0xB800C6B0
#define SE_VCOEF2_16_7_reg                                                           0xB800C6B4
#define SE_VCOEF2_16_8_reg                                                           0xB800C6B8
#define SE_VCOEF2_16_9_reg                                                           0xB800C6BC
#define SE_VCOEF2_16_10_reg                                                           0xB800C6C0
#define SE_VCOEF2_16_11_reg                                                           0xB800C6C4
#define SE_VCOEF2_16_12_reg                                                           0xB800C6C8
#define SE_VCOEF2_16_13_reg                                                           0xB800C6CC
#define SE_VCOEF2_16_14_reg                                                           0xB800C6D0
#define SE_VCOEF2_16_15_reg                                                           0xB800C6D4
#define set_SE_VCOEF2_16_0_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_0_reg)=data)
#define set_SE_VCOEF2_16_1_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_1_reg)=data)
#define set_SE_VCOEF2_16_2_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_2_reg)=data)
#define set_SE_VCOEF2_16_3_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_3_reg)=data)
#define set_SE_VCOEF2_16_4_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_4_reg)=data)
#define set_SE_VCOEF2_16_5_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_5_reg)=data)
#define set_SE_VCOEF2_16_6_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_6_reg)=data)
#define set_SE_VCOEF2_16_7_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_7_reg)=data)
#define set_SE_VCOEF2_16_8_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_8_reg)=data)
#define set_SE_VCOEF2_16_9_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_9_reg)=data)
#define set_SE_VCOEF2_16_10_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_10_reg)=data)
#define set_SE_VCOEF2_16_11_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_11_reg)=data)
#define set_SE_VCOEF2_16_12_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_12_reg)=data)
#define set_SE_VCOEF2_16_13_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_13_reg)=data)
#define set_SE_VCOEF2_16_14_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_14_reg)=data)
#define set_SE_VCOEF2_16_15_reg(data)   (*((volatile unsigned int*) SE_VCOEF2_16_15_reg)=data)
#define get_SE_VCOEF2_16_0_reg   (*((volatile unsigned int*) SE_VCOEF2_16_0_reg))
#define get_SE_VCOEF2_16_1_reg   (*((volatile unsigned int*) SE_VCOEF2_16_1_reg))
#define get_SE_VCOEF2_16_2_reg   (*((volatile unsigned int*) SE_VCOEF2_16_2_reg))
#define get_SE_VCOEF2_16_3_reg   (*((volatile unsigned int*) SE_VCOEF2_16_3_reg))
#define get_SE_VCOEF2_16_4_reg   (*((volatile unsigned int*) SE_VCOEF2_16_4_reg))
#define get_SE_VCOEF2_16_5_reg   (*((volatile unsigned int*) SE_VCOEF2_16_5_reg))
#define get_SE_VCOEF2_16_6_reg   (*((volatile unsigned int*) SE_VCOEF2_16_6_reg))
#define get_SE_VCOEF2_16_7_reg   (*((volatile unsigned int*) SE_VCOEF2_16_7_reg))
#define get_SE_VCOEF2_16_8_reg   (*((volatile unsigned int*) SE_VCOEF2_16_8_reg))
#define get_SE_VCOEF2_16_9_reg   (*((volatile unsigned int*) SE_VCOEF2_16_9_reg))
#define get_SE_VCOEF2_16_10_reg   (*((volatile unsigned int*) SE_VCOEF2_16_10_reg))
#define get_SE_VCOEF2_16_11_reg   (*((volatile unsigned int*) SE_VCOEF2_16_11_reg))
#define get_SE_VCOEF2_16_12_reg   (*((volatile unsigned int*) SE_VCOEF2_16_12_reg))
#define get_SE_VCOEF2_16_13_reg   (*((volatile unsigned int*) SE_VCOEF2_16_13_reg))
#define get_SE_VCOEF2_16_14_reg   (*((volatile unsigned int*) SE_VCOEF2_16_14_reg))
#define get_SE_VCOEF2_16_15_reg   (*((volatile unsigned int*) SE_VCOEF2_16_15_reg))
#define SE_VCOEF2_16_0_inst_adr                                                      "0x00A6"
#define SE_VCOEF2_16_1_inst_adr                                                      "0x00A7"
#define SE_VCOEF2_16_2_inst_adr                                                      "0x00A8"
#define SE_VCOEF2_16_3_inst_adr                                                      "0x00A9"
#define SE_VCOEF2_16_4_inst_adr                                                      "0x00AA"
#define SE_VCOEF2_16_5_inst_adr                                                      "0x00AB"
#define SE_VCOEF2_16_6_inst_adr                                                      "0x00AC"
#define SE_VCOEF2_16_7_inst_adr                                                      "0x00AD"
#define SE_VCOEF2_16_8_inst_adr                                                      "0x00AE"
#define SE_VCOEF2_16_9_inst_adr                                                      "0x00AF"
#define SE_VCOEF2_16_10_inst_adr                                                      "0x00B0"
#define SE_VCOEF2_16_11_inst_adr                                                      "0x00B1"
#define SE_VCOEF2_16_12_inst_adr                                                      "0x00B2"
#define SE_VCOEF2_16_13_inst_adr                                                      "0x00B3"
#define SE_VCOEF2_16_14_inst_adr                                                      "0x00B4"
#define SE_VCOEF2_16_15_inst_adr                                                      "0x00B5"
#define SE_VCOEF2_16_0_inst                                                          0x00A6
#define SE_VCOEF2_16_1_inst                                                          0x00A7
#define SE_VCOEF2_16_2_inst                                                          0x00A8
#define SE_VCOEF2_16_3_inst                                                          0x00A9
#define SE_VCOEF2_16_4_inst                                                          0x00AA
#define SE_VCOEF2_16_5_inst                                                          0x00AB
#define SE_VCOEF2_16_6_inst                                                          0x00AC
#define SE_VCOEF2_16_7_inst                                                          0x00AD
#define SE_VCOEF2_16_8_inst                                                          0x00AE
#define SE_VCOEF2_16_9_inst                                                          0x00AF
#define SE_VCOEF2_16_10_inst                                                          0x00B0
#define SE_VCOEF2_16_11_inst                                                          0x00B1
#define SE_VCOEF2_16_12_inst                                                          0x00B2
#define SE_VCOEF2_16_13_inst                                                          0x00B3
#define SE_VCOEF2_16_14_inst                                                          0x00B4
#define SE_VCOEF2_16_15_inst                                                          0x00B5
#define SE_VCOEF2_16_vcoef_shift                                                     (0)
#define SE_VCOEF2_16_vcoef_mask                                                      (0x00003FFF)
#define SE_VCOEF2_16_vcoef(data)                                                     (0x00003FFF&((data)<<0))
#define SE_VCOEF2_16_vcoef_src(data)                                                 ((0x00003FFF&(data))>>0)
#define SE_VCOEF2_16_get_vcoef(data)                                                 ((0x00003FFF&(data))>>0)


#define SE_HCOEF3_0                                                                  0x1800C380
#define SE_HCOEF3_1                                                                  0x1800C384
#define SE_HCOEF3_2                                                                  0x1800C388
#define SE_HCOEF3_3                                                                  0x1800C38C
#define SE_HCOEF3_4                                                                  0x1800C390
#define SE_HCOEF3_5                                                                  0x1800C394
#define SE_HCOEF3_6                                                                  0x1800C398
#define SE_HCOEF3_7                                                                  0x1800C39C
#define SE_HCOEF3_8                                                                  0x1800C3A0
#define SE_HCOEF3_9                                                                  0x1800C3A4
#define SE_HCOEF3_10                                                                  0x1800C3A8
#define SE_HCOEF3_11                                                                  0x1800C3AC
#define SE_HCOEF3_12                                                                  0x1800C3B0
#define SE_HCOEF3_13                                                                  0x1800C3B4
#define SE_HCOEF3_14                                                                  0x1800C3B8
#define SE_HCOEF3_15                                                                  0x1800C3BC
#define SE_HCOEF3_16                                                                  0x1800C3C0
#define SE_HCOEF3_17                                                                  0x1800C3C4
#define SE_HCOEF3_18                                                                  0x1800C3C8
#define SE_HCOEF3_19                                                                  0x1800C3CC
#define SE_HCOEF3_20                                                                  0x1800C3D0
#define SE_HCOEF3_21                                                                  0x1800C3D4
#define SE_HCOEF3_22                                                                  0x1800C3D8
#define SE_HCOEF3_23                                                                  0x1800C3DC
#define SE_HCOEF3_24                                                                  0x1800C3E0
#define SE_HCOEF3_25                                                                  0x1800C3E4
#define SE_HCOEF3_26                                                                  0x1800C3E8
#define SE_HCOEF3_27                                                                  0x1800C3EC
#define SE_HCOEF3_28                                                                  0x1800C3F0
#define SE_HCOEF3_29                                                                  0x1800C3F4
#define SE_HCOEF3_30                                                                  0x1800C3F8
#define SE_HCOEF3_31                                                                  0x1800C3FC
#define SE_HCOEF3_0_reg_addr                                                         "0xB800C380"
#define SE_HCOEF3_1_reg_addr                                                         "0xB800C384"
#define SE_HCOEF3_2_reg_addr                                                         "0xB800C388"
#define SE_HCOEF3_3_reg_addr                                                         "0xB800C38C"
#define SE_HCOEF3_4_reg_addr                                                         "0xB800C390"
#define SE_HCOEF3_5_reg_addr                                                         "0xB800C394"
#define SE_HCOEF3_6_reg_addr                                                         "0xB800C398"
#define SE_HCOEF3_7_reg_addr                                                         "0xB800C39C"
#define SE_HCOEF3_8_reg_addr                                                         "0xB800C3A0"
#define SE_HCOEF3_9_reg_addr                                                         "0xB800C3A4"
#define SE_HCOEF3_10_reg_addr                                                         "0xB800C3A8"
#define SE_HCOEF3_11_reg_addr                                                         "0xB800C3AC"
#define SE_HCOEF3_12_reg_addr                                                         "0xB800C3B0"
#define SE_HCOEF3_13_reg_addr                                                         "0xB800C3B4"
#define SE_HCOEF3_14_reg_addr                                                         "0xB800C3B8"
#define SE_HCOEF3_15_reg_addr                                                         "0xB800C3BC"
#define SE_HCOEF3_16_reg_addr                                                         "0xB800C3C0"
#define SE_HCOEF3_17_reg_addr                                                         "0xB800C3C4"
#define SE_HCOEF3_18_reg_addr                                                         "0xB800C3C8"
#define SE_HCOEF3_19_reg_addr                                                         "0xB800C3CC"
#define SE_HCOEF3_20_reg_addr                                                         "0xB800C3D0"
#define SE_HCOEF3_21_reg_addr                                                         "0xB800C3D4"
#define SE_HCOEF3_22_reg_addr                                                         "0xB800C3D8"
#define SE_HCOEF3_23_reg_addr                                                         "0xB800C3DC"
#define SE_HCOEF3_24_reg_addr                                                         "0xB800C3E0"
#define SE_HCOEF3_25_reg_addr                                                         "0xB800C3E4"
#define SE_HCOEF3_26_reg_addr                                                         "0xB800C3E8"
#define SE_HCOEF3_27_reg_addr                                                         "0xB800C3EC"
#define SE_HCOEF3_28_reg_addr                                                         "0xB800C3F0"
#define SE_HCOEF3_29_reg_addr                                                         "0xB800C3F4"
#define SE_HCOEF3_30_reg_addr                                                         "0xB800C3F8"
#define SE_HCOEF3_31_reg_addr                                                         "0xB800C3FC"
#define SE_HCOEF3_0_reg                                                              0xB800C380
#define SE_HCOEF3_1_reg                                                              0xB800C384
#define SE_HCOEF3_2_reg                                                              0xB800C388
#define SE_HCOEF3_3_reg                                                              0xB800C38C
#define SE_HCOEF3_4_reg                                                              0xB800C390
#define SE_HCOEF3_5_reg                                                              0xB800C394
#define SE_HCOEF3_6_reg                                                              0xB800C398
#define SE_HCOEF3_7_reg                                                              0xB800C39C
#define SE_HCOEF3_8_reg                                                              0xB800C3A0
#define SE_HCOEF3_9_reg                                                              0xB800C3A4
#define SE_HCOEF3_10_reg                                                              0xB800C3A8
#define SE_HCOEF3_11_reg                                                              0xB800C3AC
#define SE_HCOEF3_12_reg                                                              0xB800C3B0
#define SE_HCOEF3_13_reg                                                              0xB800C3B4
#define SE_HCOEF3_14_reg                                                              0xB800C3B8
#define SE_HCOEF3_15_reg                                                              0xB800C3BC
#define SE_HCOEF3_16_reg                                                              0xB800C3C0
#define SE_HCOEF3_17_reg                                                              0xB800C3C4
#define SE_HCOEF3_18_reg                                                              0xB800C3C8
#define SE_HCOEF3_19_reg                                                              0xB800C3CC
#define SE_HCOEF3_20_reg                                                              0xB800C3D0
#define SE_HCOEF3_21_reg                                                              0xB800C3D4
#define SE_HCOEF3_22_reg                                                              0xB800C3D8
#define SE_HCOEF3_23_reg                                                              0xB800C3DC
#define SE_HCOEF3_24_reg                                                              0xB800C3E0
#define SE_HCOEF3_25_reg                                                              0xB800C3E4
#define SE_HCOEF3_26_reg                                                              0xB800C3E8
#define SE_HCOEF3_27_reg                                                              0xB800C3EC
#define SE_HCOEF3_28_reg                                                              0xB800C3F0
#define SE_HCOEF3_29_reg                                                              0xB800C3F4
#define SE_HCOEF3_30_reg                                                              0xB800C3F8
#define SE_HCOEF3_31_reg                                                              0xB800C3FC
#define set_SE_HCOEF3_0_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_0_reg)=data)
#define set_SE_HCOEF3_1_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_1_reg)=data)
#define set_SE_HCOEF3_2_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_2_reg)=data)
#define set_SE_HCOEF3_3_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_3_reg)=data)
#define set_SE_HCOEF3_4_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_4_reg)=data)
#define set_SE_HCOEF3_5_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_5_reg)=data)
#define set_SE_HCOEF3_6_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_6_reg)=data)
#define set_SE_HCOEF3_7_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_7_reg)=data)
#define set_SE_HCOEF3_8_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_8_reg)=data)
#define set_SE_HCOEF3_9_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_9_reg)=data)
#define set_SE_HCOEF3_10_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_10_reg)=data)
#define set_SE_HCOEF3_11_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_11_reg)=data)
#define set_SE_HCOEF3_12_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_12_reg)=data)
#define set_SE_HCOEF3_13_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_13_reg)=data)
#define set_SE_HCOEF3_14_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_14_reg)=data)
#define set_SE_HCOEF3_15_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_15_reg)=data)
#define set_SE_HCOEF3_16_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_16_reg)=data)
#define set_SE_HCOEF3_17_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_17_reg)=data)
#define set_SE_HCOEF3_18_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_18_reg)=data)
#define set_SE_HCOEF3_19_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_19_reg)=data)
#define set_SE_HCOEF3_20_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_20_reg)=data)
#define set_SE_HCOEF3_21_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_21_reg)=data)
#define set_SE_HCOEF3_22_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_22_reg)=data)
#define set_SE_HCOEF3_23_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_23_reg)=data)
#define set_SE_HCOEF3_24_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_24_reg)=data)
#define set_SE_HCOEF3_25_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_25_reg)=data)
#define set_SE_HCOEF3_26_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_26_reg)=data)
#define set_SE_HCOEF3_27_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_27_reg)=data)
#define set_SE_HCOEF3_28_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_28_reg)=data)
#define set_SE_HCOEF3_29_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_29_reg)=data)
#define set_SE_HCOEF3_30_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_30_reg)=data)
#define set_SE_HCOEF3_31_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_31_reg)=data)
#define get_SE_HCOEF3_0_reg   (*((volatile unsigned int*) SE_HCOEF3_0_reg))
#define get_SE_HCOEF3_1_reg   (*((volatile unsigned int*) SE_HCOEF3_1_reg))
#define get_SE_HCOEF3_2_reg   (*((volatile unsigned int*) SE_HCOEF3_2_reg))
#define get_SE_HCOEF3_3_reg   (*((volatile unsigned int*) SE_HCOEF3_3_reg))
#define get_SE_HCOEF3_4_reg   (*((volatile unsigned int*) SE_HCOEF3_4_reg))
#define get_SE_HCOEF3_5_reg   (*((volatile unsigned int*) SE_HCOEF3_5_reg))
#define get_SE_HCOEF3_6_reg   (*((volatile unsigned int*) SE_HCOEF3_6_reg))
#define get_SE_HCOEF3_7_reg   (*((volatile unsigned int*) SE_HCOEF3_7_reg))
#define get_SE_HCOEF3_8_reg   (*((volatile unsigned int*) SE_HCOEF3_8_reg))
#define get_SE_HCOEF3_9_reg   (*((volatile unsigned int*) SE_HCOEF3_9_reg))
#define get_SE_HCOEF3_10_reg   (*((volatile unsigned int*) SE_HCOEF3_10_reg))
#define get_SE_HCOEF3_11_reg   (*((volatile unsigned int*) SE_HCOEF3_11_reg))
#define get_SE_HCOEF3_12_reg   (*((volatile unsigned int*) SE_HCOEF3_12_reg))
#define get_SE_HCOEF3_13_reg   (*((volatile unsigned int*) SE_HCOEF3_13_reg))
#define get_SE_HCOEF3_14_reg   (*((volatile unsigned int*) SE_HCOEF3_14_reg))
#define get_SE_HCOEF3_15_reg   (*((volatile unsigned int*) SE_HCOEF3_15_reg))
#define get_SE_HCOEF3_16_reg   (*((volatile unsigned int*) SE_HCOEF3_16_reg))
#define get_SE_HCOEF3_17_reg   (*((volatile unsigned int*) SE_HCOEF3_17_reg))
#define get_SE_HCOEF3_18_reg   (*((volatile unsigned int*) SE_HCOEF3_18_reg))
#define get_SE_HCOEF3_19_reg   (*((volatile unsigned int*) SE_HCOEF3_19_reg))
#define get_SE_HCOEF3_20_reg   (*((volatile unsigned int*) SE_HCOEF3_20_reg))
#define get_SE_HCOEF3_21_reg   (*((volatile unsigned int*) SE_HCOEF3_21_reg))
#define get_SE_HCOEF3_22_reg   (*((volatile unsigned int*) SE_HCOEF3_22_reg))
#define get_SE_HCOEF3_23_reg   (*((volatile unsigned int*) SE_HCOEF3_23_reg))
#define get_SE_HCOEF3_24_reg   (*((volatile unsigned int*) SE_HCOEF3_24_reg))
#define get_SE_HCOEF3_25_reg   (*((volatile unsigned int*) SE_HCOEF3_25_reg))
#define get_SE_HCOEF3_26_reg   (*((volatile unsigned int*) SE_HCOEF3_26_reg))
#define get_SE_HCOEF3_27_reg   (*((volatile unsigned int*) SE_HCOEF3_27_reg))
#define get_SE_HCOEF3_28_reg   (*((volatile unsigned int*) SE_HCOEF3_28_reg))
#define get_SE_HCOEF3_29_reg   (*((volatile unsigned int*) SE_HCOEF3_29_reg))
#define get_SE_HCOEF3_30_reg   (*((volatile unsigned int*) SE_HCOEF3_30_reg))
#define get_SE_HCOEF3_31_reg   (*((volatile unsigned int*) SE_HCOEF3_31_reg))
#define SE_HCOEF3_0_inst_adr                                                         "0x00E0"
#define SE_HCOEF3_1_inst_adr                                                         "0x00E1"
#define SE_HCOEF3_2_inst_adr                                                         "0x00E2"
#define SE_HCOEF3_3_inst_adr                                                         "0x00E3"
#define SE_HCOEF3_4_inst_adr                                                         "0x00E4"
#define SE_HCOEF3_5_inst_adr                                                         "0x00E5"
#define SE_HCOEF3_6_inst_adr                                                         "0x00E6"
#define SE_HCOEF3_7_inst_adr                                                         "0x00E7"
#define SE_HCOEF3_8_inst_adr                                                         "0x00E8"
#define SE_HCOEF3_9_inst_adr                                                         "0x00E9"
#define SE_HCOEF3_10_inst_adr                                                         "0x00EA"
#define SE_HCOEF3_11_inst_adr                                                         "0x00EB"
#define SE_HCOEF3_12_inst_adr                                                         "0x00EC"
#define SE_HCOEF3_13_inst_adr                                                         "0x00ED"
#define SE_HCOEF3_14_inst_adr                                                         "0x00EE"
#define SE_HCOEF3_15_inst_adr                                                         "0x00EF"
#define SE_HCOEF3_16_inst_adr                                                         "0x00F0"
#define SE_HCOEF3_17_inst_adr                                                         "0x00F1"
#define SE_HCOEF3_18_inst_adr                                                         "0x00F2"
#define SE_HCOEF3_19_inst_adr                                                         "0x00F3"
#define SE_HCOEF3_20_inst_adr                                                         "0x00F4"
#define SE_HCOEF3_21_inst_adr                                                         "0x00F5"
#define SE_HCOEF3_22_inst_adr                                                         "0x00F6"
#define SE_HCOEF3_23_inst_adr                                                         "0x00F7"
#define SE_HCOEF3_24_inst_adr                                                         "0x00F8"
#define SE_HCOEF3_25_inst_adr                                                         "0x00F9"
#define SE_HCOEF3_26_inst_adr                                                         "0x00FA"
#define SE_HCOEF3_27_inst_adr                                                         "0x00FB"
#define SE_HCOEF3_28_inst_adr                                                         "0x00FC"
#define SE_HCOEF3_29_inst_adr                                                         "0x00FD"
#define SE_HCOEF3_30_inst_adr                                                         "0x00FE"
#define SE_HCOEF3_31_inst_adr                                                         "0x00FF"
#define SE_HCOEF3_0_inst                                                             0x00E0
#define SE_HCOEF3_1_inst                                                             0x00E1
#define SE_HCOEF3_2_inst                                                             0x00E2
#define SE_HCOEF3_3_inst                                                             0x00E3
#define SE_HCOEF3_4_inst                                                             0x00E4
#define SE_HCOEF3_5_inst                                                             0x00E5
#define SE_HCOEF3_6_inst                                                             0x00E6
#define SE_HCOEF3_7_inst                                                             0x00E7
#define SE_HCOEF3_8_inst                                                             0x00E8
#define SE_HCOEF3_9_inst                                                             0x00E9
#define SE_HCOEF3_10_inst                                                             0x00EA
#define SE_HCOEF3_11_inst                                                             0x00EB
#define SE_HCOEF3_12_inst                                                             0x00EC
#define SE_HCOEF3_13_inst                                                             0x00ED
#define SE_HCOEF3_14_inst                                                             0x00EE
#define SE_HCOEF3_15_inst                                                             0x00EF
#define SE_HCOEF3_16_inst                                                             0x00F0
#define SE_HCOEF3_17_inst                                                             0x00F1
#define SE_HCOEF3_18_inst                                                             0x00F2
#define SE_HCOEF3_19_inst                                                             0x00F3
#define SE_HCOEF3_20_inst                                                             0x00F4
#define SE_HCOEF3_21_inst                                                             0x00F5
#define SE_HCOEF3_22_inst                                                             0x00F6
#define SE_HCOEF3_23_inst                                                             0x00F7
#define SE_HCOEF3_24_inst                                                             0x00F8
#define SE_HCOEF3_25_inst                                                             0x00F9
#define SE_HCOEF3_26_inst                                                             0x00FA
#define SE_HCOEF3_27_inst                                                             0x00FB
#define SE_HCOEF3_28_inst                                                             0x00FC
#define SE_HCOEF3_29_inst                                                             0x00FD
#define SE_HCOEF3_30_inst                                                             0x00FE
#define SE_HCOEF3_31_inst                                                             0x00FF
#define SE_HCOEF3_hcoef_shift                                                        (0)
#define SE_HCOEF3_hcoef_mask                                                         (0x00003FFF)
#define SE_HCOEF3_hcoef(data)                                                        (0x00003FFF&((data)<<0))
#define SE_HCOEF3_hcoef_src(data)                                                    ((0x00003FFF&(data))>>0)
#define SE_HCOEF3_get_hcoef(data)                                                    ((0x00003FFF&(data))>>0)


#define SE_HCOEF3_32_0                                                               0x1800C6D8
#define SE_HCOEF3_32_1                                                               0x1800C6DC
#define SE_HCOEF3_32_2                                                               0x1800C6E0
#define SE_HCOEF3_32_3                                                               0x1800C6E4
#define SE_HCOEF3_32_4                                                               0x1800C6E8
#define SE_HCOEF3_32_5                                                               0x1800C6EC
#define SE_HCOEF3_32_6                                                               0x1800C6F0
#define SE_HCOEF3_32_7                                                               0x1800C6F4
#define SE_HCOEF3_32_8                                                               0x1800C6F8
#define SE_HCOEF3_32_9                                                               0x1800C6FC
#define SE_HCOEF3_32_10                                                               0x1800C700
#define SE_HCOEF3_32_11                                                               0x1800C704
#define SE_HCOEF3_32_12                                                               0x1800C708
#define SE_HCOEF3_32_13                                                               0x1800C70C
#define SE_HCOEF3_32_14                                                               0x1800C710
#define SE_HCOEF3_32_15                                                               0x1800C714
#define SE_HCOEF3_32_16                                                               0x1800C718
#define SE_HCOEF3_32_17                                                               0x1800C71C
#define SE_HCOEF3_32_18                                                               0x1800C720
#define SE_HCOEF3_32_19                                                               0x1800C724
#define SE_HCOEF3_32_20                                                               0x1800C728
#define SE_HCOEF3_32_21                                                               0x1800C72C
#define SE_HCOEF3_32_22                                                               0x1800C730
#define SE_HCOEF3_32_23                                                               0x1800C734
#define SE_HCOEF3_32_24                                                               0x1800C738
#define SE_HCOEF3_32_25                                                               0x1800C73C
#define SE_HCOEF3_32_26                                                               0x1800C740
#define SE_HCOEF3_32_27                                                               0x1800C744
#define SE_HCOEF3_32_28                                                               0x1800C748
#define SE_HCOEF3_32_29                                                               0x1800C74C
#define SE_HCOEF3_32_30                                                               0x1800C750
#define SE_HCOEF3_32_31                                                               0x1800C754
#define SE_HCOEF3_32_0_reg_addr                                                      "0xB800C6D8"
#define SE_HCOEF3_32_1_reg_addr                                                      "0xB800C6DC"
#define SE_HCOEF3_32_2_reg_addr                                                      "0xB800C6E0"
#define SE_HCOEF3_32_3_reg_addr                                                      "0xB800C6E4"
#define SE_HCOEF3_32_4_reg_addr                                                      "0xB800C6E8"
#define SE_HCOEF3_32_5_reg_addr                                                      "0xB800C6EC"
#define SE_HCOEF3_32_6_reg_addr                                                      "0xB800C6F0"
#define SE_HCOEF3_32_7_reg_addr                                                      "0xB800C6F4"
#define SE_HCOEF3_32_8_reg_addr                                                      "0xB800C6F8"
#define SE_HCOEF3_32_9_reg_addr                                                      "0xB800C6FC"
#define SE_HCOEF3_32_10_reg_addr                                                      "0xB800C700"
#define SE_HCOEF3_32_11_reg_addr                                                      "0xB800C704"
#define SE_HCOEF3_32_12_reg_addr                                                      "0xB800C708"
#define SE_HCOEF3_32_13_reg_addr                                                      "0xB800C70C"
#define SE_HCOEF3_32_14_reg_addr                                                      "0xB800C710"
#define SE_HCOEF3_32_15_reg_addr                                                      "0xB800C714"
#define SE_HCOEF3_32_16_reg_addr                                                      "0xB800C718"
#define SE_HCOEF3_32_17_reg_addr                                                      "0xB800C71C"
#define SE_HCOEF3_32_18_reg_addr                                                      "0xB800C720"
#define SE_HCOEF3_32_19_reg_addr                                                      "0xB800C724"
#define SE_HCOEF3_32_20_reg_addr                                                      "0xB800C728"
#define SE_HCOEF3_32_21_reg_addr                                                      "0xB800C72C"
#define SE_HCOEF3_32_22_reg_addr                                                      "0xB800C730"
#define SE_HCOEF3_32_23_reg_addr                                                      "0xB800C734"
#define SE_HCOEF3_32_24_reg_addr                                                      "0xB800C738"
#define SE_HCOEF3_32_25_reg_addr                                                      "0xB800C73C"
#define SE_HCOEF3_32_26_reg_addr                                                      "0xB800C740"
#define SE_HCOEF3_32_27_reg_addr                                                      "0xB800C744"
#define SE_HCOEF3_32_28_reg_addr                                                      "0xB800C748"
#define SE_HCOEF3_32_29_reg_addr                                                      "0xB800C74C"
#define SE_HCOEF3_32_30_reg_addr                                                      "0xB800C750"
#define SE_HCOEF3_32_31_reg_addr                                                      "0xB800C754"
#define SE_HCOEF3_32_0_reg                                                           0xB800C6D8
#define SE_HCOEF3_32_1_reg                                                           0xB800C6DC
#define SE_HCOEF3_32_2_reg                                                           0xB800C6E0
#define SE_HCOEF3_32_3_reg                                                           0xB800C6E4
#define SE_HCOEF3_32_4_reg                                                           0xB800C6E8
#define SE_HCOEF3_32_5_reg                                                           0xB800C6EC
#define SE_HCOEF3_32_6_reg                                                           0xB800C6F0
#define SE_HCOEF3_32_7_reg                                                           0xB800C6F4
#define SE_HCOEF3_32_8_reg                                                           0xB800C6F8
#define SE_HCOEF3_32_9_reg                                                           0xB800C6FC
#define SE_HCOEF3_32_10_reg                                                           0xB800C700
#define SE_HCOEF3_32_11_reg                                                           0xB800C704
#define SE_HCOEF3_32_12_reg                                                           0xB800C708
#define SE_HCOEF3_32_13_reg                                                           0xB800C70C
#define SE_HCOEF3_32_14_reg                                                           0xB800C710
#define SE_HCOEF3_32_15_reg                                                           0xB800C714
#define SE_HCOEF3_32_16_reg                                                           0xB800C718
#define SE_HCOEF3_32_17_reg                                                           0xB800C71C
#define SE_HCOEF3_32_18_reg                                                           0xB800C720
#define SE_HCOEF3_32_19_reg                                                           0xB800C724
#define SE_HCOEF3_32_20_reg                                                           0xB800C728
#define SE_HCOEF3_32_21_reg                                                           0xB800C72C
#define SE_HCOEF3_32_22_reg                                                           0xB800C730
#define SE_HCOEF3_32_23_reg                                                           0xB800C734
#define SE_HCOEF3_32_24_reg                                                           0xB800C738
#define SE_HCOEF3_32_25_reg                                                           0xB800C73C
#define SE_HCOEF3_32_26_reg                                                           0xB800C740
#define SE_HCOEF3_32_27_reg                                                           0xB800C744
#define SE_HCOEF3_32_28_reg                                                           0xB800C748
#define SE_HCOEF3_32_29_reg                                                           0xB800C74C
#define SE_HCOEF3_32_30_reg                                                           0xB800C750
#define SE_HCOEF3_32_31_reg                                                           0xB800C754
#define set_SE_HCOEF3_32_0_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_0_reg)=data)
#define set_SE_HCOEF3_32_1_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_1_reg)=data)
#define set_SE_HCOEF3_32_2_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_2_reg)=data)
#define set_SE_HCOEF3_32_3_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_3_reg)=data)
#define set_SE_HCOEF3_32_4_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_4_reg)=data)
#define set_SE_HCOEF3_32_5_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_5_reg)=data)
#define set_SE_HCOEF3_32_6_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_6_reg)=data)
#define set_SE_HCOEF3_32_7_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_7_reg)=data)
#define set_SE_HCOEF3_32_8_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_8_reg)=data)
#define set_SE_HCOEF3_32_9_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_9_reg)=data)
#define set_SE_HCOEF3_32_10_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_10_reg)=data)
#define set_SE_HCOEF3_32_11_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_11_reg)=data)
#define set_SE_HCOEF3_32_12_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_12_reg)=data)
#define set_SE_HCOEF3_32_13_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_13_reg)=data)
#define set_SE_HCOEF3_32_14_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_14_reg)=data)
#define set_SE_HCOEF3_32_15_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_15_reg)=data)
#define set_SE_HCOEF3_32_16_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_16_reg)=data)
#define set_SE_HCOEF3_32_17_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_17_reg)=data)
#define set_SE_HCOEF3_32_18_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_18_reg)=data)
#define set_SE_HCOEF3_32_19_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_19_reg)=data)
#define set_SE_HCOEF3_32_20_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_20_reg)=data)
#define set_SE_HCOEF3_32_21_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_21_reg)=data)
#define set_SE_HCOEF3_32_22_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_22_reg)=data)
#define set_SE_HCOEF3_32_23_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_23_reg)=data)
#define set_SE_HCOEF3_32_24_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_24_reg)=data)
#define set_SE_HCOEF3_32_25_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_25_reg)=data)
#define set_SE_HCOEF3_32_26_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_26_reg)=data)
#define set_SE_HCOEF3_32_27_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_27_reg)=data)
#define set_SE_HCOEF3_32_28_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_28_reg)=data)
#define set_SE_HCOEF3_32_29_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_29_reg)=data)
#define set_SE_HCOEF3_32_30_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_30_reg)=data)
#define set_SE_HCOEF3_32_31_reg(data)   (*((volatile unsigned int*) SE_HCOEF3_32_31_reg)=data)
#define get_SE_HCOEF3_32_0_reg   (*((volatile unsigned int*) SE_HCOEF3_32_0_reg))
#define get_SE_HCOEF3_32_1_reg   (*((volatile unsigned int*) SE_HCOEF3_32_1_reg))
#define get_SE_HCOEF3_32_2_reg   (*((volatile unsigned int*) SE_HCOEF3_32_2_reg))
#define get_SE_HCOEF3_32_3_reg   (*((volatile unsigned int*) SE_HCOEF3_32_3_reg))
#define get_SE_HCOEF3_32_4_reg   (*((volatile unsigned int*) SE_HCOEF3_32_4_reg))
#define get_SE_HCOEF3_32_5_reg   (*((volatile unsigned int*) SE_HCOEF3_32_5_reg))
#define get_SE_HCOEF3_32_6_reg   (*((volatile unsigned int*) SE_HCOEF3_32_6_reg))
#define get_SE_HCOEF3_32_7_reg   (*((volatile unsigned int*) SE_HCOEF3_32_7_reg))
#define get_SE_HCOEF3_32_8_reg   (*((volatile unsigned int*) SE_HCOEF3_32_8_reg))
#define get_SE_HCOEF3_32_9_reg   (*((volatile unsigned int*) SE_HCOEF3_32_9_reg))
#define get_SE_HCOEF3_32_10_reg   (*((volatile unsigned int*) SE_HCOEF3_32_10_reg))
#define get_SE_HCOEF3_32_11_reg   (*((volatile unsigned int*) SE_HCOEF3_32_11_reg))
#define get_SE_HCOEF3_32_12_reg   (*((volatile unsigned int*) SE_HCOEF3_32_12_reg))
#define get_SE_HCOEF3_32_13_reg   (*((volatile unsigned int*) SE_HCOEF3_32_13_reg))
#define get_SE_HCOEF3_32_14_reg   (*((volatile unsigned int*) SE_HCOEF3_32_14_reg))
#define get_SE_HCOEF3_32_15_reg   (*((volatile unsigned int*) SE_HCOEF3_32_15_reg))
#define get_SE_HCOEF3_32_16_reg   (*((volatile unsigned int*) SE_HCOEF3_32_16_reg))
#define get_SE_HCOEF3_32_17_reg   (*((volatile unsigned int*) SE_HCOEF3_32_17_reg))
#define get_SE_HCOEF3_32_18_reg   (*((volatile unsigned int*) SE_HCOEF3_32_18_reg))
#define get_SE_HCOEF3_32_19_reg   (*((volatile unsigned int*) SE_HCOEF3_32_19_reg))
#define get_SE_HCOEF3_32_20_reg   (*((volatile unsigned int*) SE_HCOEF3_32_20_reg))
#define get_SE_HCOEF3_32_21_reg   (*((volatile unsigned int*) SE_HCOEF3_32_21_reg))
#define get_SE_HCOEF3_32_22_reg   (*((volatile unsigned int*) SE_HCOEF3_32_22_reg))
#define get_SE_HCOEF3_32_23_reg   (*((volatile unsigned int*) SE_HCOEF3_32_23_reg))
#define get_SE_HCOEF3_32_24_reg   (*((volatile unsigned int*) SE_HCOEF3_32_24_reg))
#define get_SE_HCOEF3_32_25_reg   (*((volatile unsigned int*) SE_HCOEF3_32_25_reg))
#define get_SE_HCOEF3_32_26_reg   (*((volatile unsigned int*) SE_HCOEF3_32_26_reg))
#define get_SE_HCOEF3_32_27_reg   (*((volatile unsigned int*) SE_HCOEF3_32_27_reg))
#define get_SE_HCOEF3_32_28_reg   (*((volatile unsigned int*) SE_HCOEF3_32_28_reg))
#define get_SE_HCOEF3_32_29_reg   (*((volatile unsigned int*) SE_HCOEF3_32_29_reg))
#define get_SE_HCOEF3_32_30_reg   (*((volatile unsigned int*) SE_HCOEF3_32_30_reg))
#define get_SE_HCOEF3_32_31_reg   (*((volatile unsigned int*) SE_HCOEF3_32_31_reg))
#define SE_HCOEF3_32_0_inst_adr                                                      "0x00B6"
#define SE_HCOEF3_32_1_inst_adr                                                      "0x00B7"
#define SE_HCOEF3_32_2_inst_adr                                                      "0x00B8"
#define SE_HCOEF3_32_3_inst_adr                                                      "0x00B9"
#define SE_HCOEF3_32_4_inst_adr                                                      "0x00BA"
#define SE_HCOEF3_32_5_inst_adr                                                      "0x00BB"
#define SE_HCOEF3_32_6_inst_adr                                                      "0x00BC"
#define SE_HCOEF3_32_7_inst_adr                                                      "0x00BD"
#define SE_HCOEF3_32_8_inst_adr                                                      "0x00BE"
#define SE_HCOEF3_32_9_inst_adr                                                      "0x00BF"
#define SE_HCOEF3_32_10_inst_adr                                                      "0x00C0"
#define SE_HCOEF3_32_11_inst_adr                                                      "0x00C1"
#define SE_HCOEF3_32_12_inst_adr                                                      "0x00C2"
#define SE_HCOEF3_32_13_inst_adr                                                      "0x00C3"
#define SE_HCOEF3_32_14_inst_adr                                                      "0x00C4"
#define SE_HCOEF3_32_15_inst_adr                                                      "0x00C5"
#define SE_HCOEF3_32_16_inst_adr                                                      "0x00C6"
#define SE_HCOEF3_32_17_inst_adr                                                      "0x00C7"
#define SE_HCOEF3_32_18_inst_adr                                                      "0x00C8"
#define SE_HCOEF3_32_19_inst_adr                                                      "0x00C9"
#define SE_HCOEF3_32_20_inst_adr                                                      "0x00CA"
#define SE_HCOEF3_32_21_inst_adr                                                      "0x00CB"
#define SE_HCOEF3_32_22_inst_adr                                                      "0x00CC"
#define SE_HCOEF3_32_23_inst_adr                                                      "0x00CD"
#define SE_HCOEF3_32_24_inst_adr                                                      "0x00CE"
#define SE_HCOEF3_32_25_inst_adr                                                      "0x00CF"
#define SE_HCOEF3_32_26_inst_adr                                                      "0x00D0"
#define SE_HCOEF3_32_27_inst_adr                                                      "0x00D1"
#define SE_HCOEF3_32_28_inst_adr                                                      "0x00D2"
#define SE_HCOEF3_32_29_inst_adr                                                      "0x00D3"
#define SE_HCOEF3_32_30_inst_adr                                                      "0x00D4"
#define SE_HCOEF3_32_31_inst_adr                                                      "0x00D5"
#define SE_HCOEF3_32_0_inst                                                          0x00B6
#define SE_HCOEF3_32_1_inst                                                          0x00B7
#define SE_HCOEF3_32_2_inst                                                          0x00B8
#define SE_HCOEF3_32_3_inst                                                          0x00B9
#define SE_HCOEF3_32_4_inst                                                          0x00BA
#define SE_HCOEF3_32_5_inst                                                          0x00BB
#define SE_HCOEF3_32_6_inst                                                          0x00BC
#define SE_HCOEF3_32_7_inst                                                          0x00BD
#define SE_HCOEF3_32_8_inst                                                          0x00BE
#define SE_HCOEF3_32_9_inst                                                          0x00BF
#define SE_HCOEF3_32_10_inst                                                          0x00C0
#define SE_HCOEF3_32_11_inst                                                          0x00C1
#define SE_HCOEF3_32_12_inst                                                          0x00C2
#define SE_HCOEF3_32_13_inst                                                          0x00C3
#define SE_HCOEF3_32_14_inst                                                          0x00C4
#define SE_HCOEF3_32_15_inst                                                          0x00C5
#define SE_HCOEF3_32_16_inst                                                          0x00C6
#define SE_HCOEF3_32_17_inst                                                          0x00C7
#define SE_HCOEF3_32_18_inst                                                          0x00C8
#define SE_HCOEF3_32_19_inst                                                          0x00C9
#define SE_HCOEF3_32_20_inst                                                          0x00CA
#define SE_HCOEF3_32_21_inst                                                          0x00CB
#define SE_HCOEF3_32_22_inst                                                          0x00CC
#define SE_HCOEF3_32_23_inst                                                          0x00CD
#define SE_HCOEF3_32_24_inst                                                          0x00CE
#define SE_HCOEF3_32_25_inst                                                          0x00CF
#define SE_HCOEF3_32_26_inst                                                          0x00D0
#define SE_HCOEF3_32_27_inst                                                          0x00D1
#define SE_HCOEF3_32_28_inst                                                          0x00D2
#define SE_HCOEF3_32_29_inst                                                          0x00D3
#define SE_HCOEF3_32_30_inst                                                          0x00D4
#define SE_HCOEF3_32_31_inst                                                          0x00D5
#define SE_HCOEF3_32_hcoef_shift                                                     (0)
#define SE_HCOEF3_32_hcoef_mask                                                      (0x00003FFF)
#define SE_HCOEF3_32_hcoef(data)                                                     (0x00003FFF&((data)<<0))
#define SE_HCOEF3_32_hcoef_src(data)                                                 ((0x00003FFF&(data))>>0)
#define SE_HCOEF3_32_get_hcoef(data)                                                 ((0x00003FFF&(data))>>0)


#define SE_VCOEF3_0                                                                  0x1800C400
#define SE_VCOEF3_1                                                                  0x1800C404
#define SE_VCOEF3_2                                                                  0x1800C408
#define SE_VCOEF3_3                                                                  0x1800C40C
#define SE_VCOEF3_4                                                                  0x1800C410
#define SE_VCOEF3_5                                                                  0x1800C414
#define SE_VCOEF3_6                                                                  0x1800C418
#define SE_VCOEF3_7                                                                  0x1800C41C
#define SE_VCOEF3_8                                                                  0x1800C420
#define SE_VCOEF3_9                                                                  0x1800C424
#define SE_VCOEF3_10                                                                  0x1800C428
#define SE_VCOEF3_11                                                                  0x1800C42C
#define SE_VCOEF3_12                                                                  0x1800C430
#define SE_VCOEF3_13                                                                  0x1800C434
#define SE_VCOEF3_14                                                                  0x1800C438
#define SE_VCOEF3_15                                                                  0x1800C43C
#define SE_VCOEF3_0_reg_addr                                                         "0xB800C400"
#define SE_VCOEF3_1_reg_addr                                                         "0xB800C404"
#define SE_VCOEF3_2_reg_addr                                                         "0xB800C408"
#define SE_VCOEF3_3_reg_addr                                                         "0xB800C40C"
#define SE_VCOEF3_4_reg_addr                                                         "0xB800C410"
#define SE_VCOEF3_5_reg_addr                                                         "0xB800C414"
#define SE_VCOEF3_6_reg_addr                                                         "0xB800C418"
#define SE_VCOEF3_7_reg_addr                                                         "0xB800C41C"
#define SE_VCOEF3_8_reg_addr                                                         "0xB800C420"
#define SE_VCOEF3_9_reg_addr                                                         "0xB800C424"
#define SE_VCOEF3_10_reg_addr                                                         "0xB800C428"
#define SE_VCOEF3_11_reg_addr                                                         "0xB800C42C"
#define SE_VCOEF3_12_reg_addr                                                         "0xB800C430"
#define SE_VCOEF3_13_reg_addr                                                         "0xB800C434"
#define SE_VCOEF3_14_reg_addr                                                         "0xB800C438"
#define SE_VCOEF3_15_reg_addr                                                         "0xB800C43C"
#define SE_VCOEF3_0_reg                                                              0xB800C400
#define SE_VCOEF3_1_reg                                                              0xB800C404
#define SE_VCOEF3_2_reg                                                              0xB800C408
#define SE_VCOEF3_3_reg                                                              0xB800C40C
#define SE_VCOEF3_4_reg                                                              0xB800C410
#define SE_VCOEF3_5_reg                                                              0xB800C414
#define SE_VCOEF3_6_reg                                                              0xB800C418
#define SE_VCOEF3_7_reg                                                              0xB800C41C
#define SE_VCOEF3_8_reg                                                              0xB800C420
#define SE_VCOEF3_9_reg                                                              0xB800C424
#define SE_VCOEF3_10_reg                                                              0xB800C428
#define SE_VCOEF3_11_reg                                                              0xB800C42C
#define SE_VCOEF3_12_reg                                                              0xB800C430
#define SE_VCOEF3_13_reg                                                              0xB800C434
#define SE_VCOEF3_14_reg                                                              0xB800C438
#define SE_VCOEF3_15_reg                                                              0xB800C43C
#define set_SE_VCOEF3_0_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_0_reg)=data)
#define set_SE_VCOEF3_1_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_1_reg)=data)
#define set_SE_VCOEF3_2_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_2_reg)=data)
#define set_SE_VCOEF3_3_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_3_reg)=data)
#define set_SE_VCOEF3_4_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_4_reg)=data)
#define set_SE_VCOEF3_5_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_5_reg)=data)
#define set_SE_VCOEF3_6_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_6_reg)=data)
#define set_SE_VCOEF3_7_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_7_reg)=data)
#define set_SE_VCOEF3_8_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_8_reg)=data)
#define set_SE_VCOEF3_9_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_9_reg)=data)
#define set_SE_VCOEF3_10_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_10_reg)=data)
#define set_SE_VCOEF3_11_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_11_reg)=data)
#define set_SE_VCOEF3_12_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_12_reg)=data)
#define set_SE_VCOEF3_13_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_13_reg)=data)
#define set_SE_VCOEF3_14_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_14_reg)=data)
#define set_SE_VCOEF3_15_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_15_reg)=data)
#define get_SE_VCOEF3_0_reg   (*((volatile unsigned int*) SE_VCOEF3_0_reg))
#define get_SE_VCOEF3_1_reg   (*((volatile unsigned int*) SE_VCOEF3_1_reg))
#define get_SE_VCOEF3_2_reg   (*((volatile unsigned int*) SE_VCOEF3_2_reg))
#define get_SE_VCOEF3_3_reg   (*((volatile unsigned int*) SE_VCOEF3_3_reg))
#define get_SE_VCOEF3_4_reg   (*((volatile unsigned int*) SE_VCOEF3_4_reg))
#define get_SE_VCOEF3_5_reg   (*((volatile unsigned int*) SE_VCOEF3_5_reg))
#define get_SE_VCOEF3_6_reg   (*((volatile unsigned int*) SE_VCOEF3_6_reg))
#define get_SE_VCOEF3_7_reg   (*((volatile unsigned int*) SE_VCOEF3_7_reg))
#define get_SE_VCOEF3_8_reg   (*((volatile unsigned int*) SE_VCOEF3_8_reg))
#define get_SE_VCOEF3_9_reg   (*((volatile unsigned int*) SE_VCOEF3_9_reg))
#define get_SE_VCOEF3_10_reg   (*((volatile unsigned int*) SE_VCOEF3_10_reg))
#define get_SE_VCOEF3_11_reg   (*((volatile unsigned int*) SE_VCOEF3_11_reg))
#define get_SE_VCOEF3_12_reg   (*((volatile unsigned int*) SE_VCOEF3_12_reg))
#define get_SE_VCOEF3_13_reg   (*((volatile unsigned int*) SE_VCOEF3_13_reg))
#define get_SE_VCOEF3_14_reg   (*((volatile unsigned int*) SE_VCOEF3_14_reg))
#define get_SE_VCOEF3_15_reg   (*((volatile unsigned int*) SE_VCOEF3_15_reg))
#define SE_VCOEF3_0_inst_adr                                                         "0x0000"
#define SE_VCOEF3_1_inst_adr                                                         "0x0001"
#define SE_VCOEF3_2_inst_adr                                                         "0x0002"
#define SE_VCOEF3_3_inst_adr                                                         "0x0003"
#define SE_VCOEF3_4_inst_adr                                                         "0x0004"
#define SE_VCOEF3_5_inst_adr                                                         "0x0005"
#define SE_VCOEF3_6_inst_adr                                                         "0x0006"
#define SE_VCOEF3_7_inst_adr                                                         "0x0007"
#define SE_VCOEF3_8_inst_adr                                                         "0x0008"
#define SE_VCOEF3_9_inst_adr                                                         "0x0009"
#define SE_VCOEF3_10_inst_adr                                                         "0x000A"
#define SE_VCOEF3_11_inst_adr                                                         "0x000B"
#define SE_VCOEF3_12_inst_adr                                                         "0x000C"
#define SE_VCOEF3_13_inst_adr                                                         "0x000D"
#define SE_VCOEF3_14_inst_adr                                                         "0x000E"
#define SE_VCOEF3_15_inst_adr                                                         "0x000F"
#define SE_VCOEF3_0_inst                                                             0x0000
#define SE_VCOEF3_1_inst                                                             0x0001
#define SE_VCOEF3_2_inst                                                             0x0002
#define SE_VCOEF3_3_inst                                                             0x0003
#define SE_VCOEF3_4_inst                                                             0x0004
#define SE_VCOEF3_5_inst                                                             0x0005
#define SE_VCOEF3_6_inst                                                             0x0006
#define SE_VCOEF3_7_inst                                                             0x0007
#define SE_VCOEF3_8_inst                                                             0x0008
#define SE_VCOEF3_9_inst                                                             0x0009
#define SE_VCOEF3_10_inst                                                             0x000A
#define SE_VCOEF3_11_inst                                                             0x000B
#define SE_VCOEF3_12_inst                                                             0x000C
#define SE_VCOEF3_13_inst                                                             0x000D
#define SE_VCOEF3_14_inst                                                             0x000E
#define SE_VCOEF3_15_inst                                                             0x000F
#define SE_VCOEF3_vcoef_shift                                                        (0)
#define SE_VCOEF3_vcoef_mask                                                         (0x00003FFF)
#define SE_VCOEF3_vcoef(data)                                                        (0x00003FFF&((data)<<0))
#define SE_VCOEF3_vcoef_src(data)                                                    ((0x00003FFF&(data))>>0)
#define SE_VCOEF3_get_vcoef(data)                                                    ((0x00003FFF&(data))>>0)


#define SE_VCOEF3_16_0                                                               0x1800C758
#define SE_VCOEF3_16_1                                                               0x1800C75C
#define SE_VCOEF3_16_2                                                               0x1800C760
#define SE_VCOEF3_16_3                                                               0x1800C764
#define SE_VCOEF3_16_4                                                               0x1800C768
#define SE_VCOEF3_16_5                                                               0x1800C76C
#define SE_VCOEF3_16_6                                                               0x1800C770
#define SE_VCOEF3_16_7                                                               0x1800C774
#define SE_VCOEF3_16_8                                                               0x1800C778
#define SE_VCOEF3_16_9                                                               0x1800C77C
#define SE_VCOEF3_16_10                                                               0x1800C780
#define SE_VCOEF3_16_11                                                               0x1800C784
#define SE_VCOEF3_16_12                                                               0x1800C788
#define SE_VCOEF3_16_13                                                               0x1800C78C
#define SE_VCOEF3_16_14                                                               0x1800C790
#define SE_VCOEF3_16_15                                                               0x1800C794
#define SE_VCOEF3_16_0_reg_addr                                                      "0xB800C758"
#define SE_VCOEF3_16_1_reg_addr                                                      "0xB800C75C"
#define SE_VCOEF3_16_2_reg_addr                                                      "0xB800C760"
#define SE_VCOEF3_16_3_reg_addr                                                      "0xB800C764"
#define SE_VCOEF3_16_4_reg_addr                                                      "0xB800C768"
#define SE_VCOEF3_16_5_reg_addr                                                      "0xB800C76C"
#define SE_VCOEF3_16_6_reg_addr                                                      "0xB800C770"
#define SE_VCOEF3_16_7_reg_addr                                                      "0xB800C774"
#define SE_VCOEF3_16_8_reg_addr                                                      "0xB800C778"
#define SE_VCOEF3_16_9_reg_addr                                                      "0xB800C77C"
#define SE_VCOEF3_16_10_reg_addr                                                      "0xB800C780"
#define SE_VCOEF3_16_11_reg_addr                                                      "0xB800C784"
#define SE_VCOEF3_16_12_reg_addr                                                      "0xB800C788"
#define SE_VCOEF3_16_13_reg_addr                                                      "0xB800C78C"
#define SE_VCOEF3_16_14_reg_addr                                                      "0xB800C790"
#define SE_VCOEF3_16_15_reg_addr                                                      "0xB800C794"
#define SE_VCOEF3_16_0_reg                                                           0xB800C758
#define SE_VCOEF3_16_1_reg                                                           0xB800C75C
#define SE_VCOEF3_16_2_reg                                                           0xB800C760
#define SE_VCOEF3_16_3_reg                                                           0xB800C764
#define SE_VCOEF3_16_4_reg                                                           0xB800C768
#define SE_VCOEF3_16_5_reg                                                           0xB800C76C
#define SE_VCOEF3_16_6_reg                                                           0xB800C770
#define SE_VCOEF3_16_7_reg                                                           0xB800C774
#define SE_VCOEF3_16_8_reg                                                           0xB800C778
#define SE_VCOEF3_16_9_reg                                                           0xB800C77C
#define SE_VCOEF3_16_10_reg                                                           0xB800C780
#define SE_VCOEF3_16_11_reg                                                           0xB800C784
#define SE_VCOEF3_16_12_reg                                                           0xB800C788
#define SE_VCOEF3_16_13_reg                                                           0xB800C78C
#define SE_VCOEF3_16_14_reg                                                           0xB800C790
#define SE_VCOEF3_16_15_reg                                                           0xB800C794
#define set_SE_VCOEF3_16_0_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_0_reg)=data)
#define set_SE_VCOEF3_16_1_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_1_reg)=data)
#define set_SE_VCOEF3_16_2_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_2_reg)=data)
#define set_SE_VCOEF3_16_3_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_3_reg)=data)
#define set_SE_VCOEF3_16_4_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_4_reg)=data)
#define set_SE_VCOEF3_16_5_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_5_reg)=data)
#define set_SE_VCOEF3_16_6_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_6_reg)=data)
#define set_SE_VCOEF3_16_7_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_7_reg)=data)
#define set_SE_VCOEF3_16_8_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_8_reg)=data)
#define set_SE_VCOEF3_16_9_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_9_reg)=data)
#define set_SE_VCOEF3_16_10_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_10_reg)=data)
#define set_SE_VCOEF3_16_11_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_11_reg)=data)
#define set_SE_VCOEF3_16_12_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_12_reg)=data)
#define set_SE_VCOEF3_16_13_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_13_reg)=data)
#define set_SE_VCOEF3_16_14_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_14_reg)=data)
#define set_SE_VCOEF3_16_15_reg(data)   (*((volatile unsigned int*) SE_VCOEF3_16_15_reg)=data)
#define get_SE_VCOEF3_16_0_reg   (*((volatile unsigned int*) SE_VCOEF3_16_0_reg))
#define get_SE_VCOEF3_16_1_reg   (*((volatile unsigned int*) SE_VCOEF3_16_1_reg))
#define get_SE_VCOEF3_16_2_reg   (*((volatile unsigned int*) SE_VCOEF3_16_2_reg))
#define get_SE_VCOEF3_16_3_reg   (*((volatile unsigned int*) SE_VCOEF3_16_3_reg))
#define get_SE_VCOEF3_16_4_reg   (*((volatile unsigned int*) SE_VCOEF3_16_4_reg))
#define get_SE_VCOEF3_16_5_reg   (*((volatile unsigned int*) SE_VCOEF3_16_5_reg))
#define get_SE_VCOEF3_16_6_reg   (*((volatile unsigned int*) SE_VCOEF3_16_6_reg))
#define get_SE_VCOEF3_16_7_reg   (*((volatile unsigned int*) SE_VCOEF3_16_7_reg))
#define get_SE_VCOEF3_16_8_reg   (*((volatile unsigned int*) SE_VCOEF3_16_8_reg))
#define get_SE_VCOEF3_16_9_reg   (*((volatile unsigned int*) SE_VCOEF3_16_9_reg))
#define get_SE_VCOEF3_16_10_reg   (*((volatile unsigned int*) SE_VCOEF3_16_10_reg))
#define get_SE_VCOEF3_16_11_reg   (*((volatile unsigned int*) SE_VCOEF3_16_11_reg))
#define get_SE_VCOEF3_16_12_reg   (*((volatile unsigned int*) SE_VCOEF3_16_12_reg))
#define get_SE_VCOEF3_16_13_reg   (*((volatile unsigned int*) SE_VCOEF3_16_13_reg))
#define get_SE_VCOEF3_16_14_reg   (*((volatile unsigned int*) SE_VCOEF3_16_14_reg))
#define get_SE_VCOEF3_16_15_reg   (*((volatile unsigned int*) SE_VCOEF3_16_15_reg))
#define SE_VCOEF3_16_0_inst_adr                                                      "0x00D6"
#define SE_VCOEF3_16_1_inst_adr                                                      "0x00D7"
#define SE_VCOEF3_16_2_inst_adr                                                      "0x00D8"
#define SE_VCOEF3_16_3_inst_adr                                                      "0x00D9"
#define SE_VCOEF3_16_4_inst_adr                                                      "0x00DA"
#define SE_VCOEF3_16_5_inst_adr                                                      "0x00DB"
#define SE_VCOEF3_16_6_inst_adr                                                      "0x00DC"
#define SE_VCOEF3_16_7_inst_adr                                                      "0x00DD"
#define SE_VCOEF3_16_8_inst_adr                                                      "0x00DE"
#define SE_VCOEF3_16_9_inst_adr                                                      "0x00DF"
#define SE_VCOEF3_16_10_inst_adr                                                      "0x00E0"
#define SE_VCOEF3_16_11_inst_adr                                                      "0x00E1"
#define SE_VCOEF3_16_12_inst_adr                                                      "0x00E2"
#define SE_VCOEF3_16_13_inst_adr                                                      "0x00E3"
#define SE_VCOEF3_16_14_inst_adr                                                      "0x00E4"
#define SE_VCOEF3_16_15_inst_adr                                                      "0x00E5"
#define SE_VCOEF3_16_0_inst                                                          0x00D6
#define SE_VCOEF3_16_1_inst                                                          0x00D7
#define SE_VCOEF3_16_2_inst                                                          0x00D8
#define SE_VCOEF3_16_3_inst                                                          0x00D9
#define SE_VCOEF3_16_4_inst                                                          0x00DA
#define SE_VCOEF3_16_5_inst                                                          0x00DB
#define SE_VCOEF3_16_6_inst                                                          0x00DC
#define SE_VCOEF3_16_7_inst                                                          0x00DD
#define SE_VCOEF3_16_8_inst                                                          0x00DE
#define SE_VCOEF3_16_9_inst                                                          0x00DF
#define SE_VCOEF3_16_10_inst                                                          0x00E0
#define SE_VCOEF3_16_11_inst                                                          0x00E1
#define SE_VCOEF3_16_12_inst                                                          0x00E2
#define SE_VCOEF3_16_13_inst                                                          0x00E3
#define SE_VCOEF3_16_14_inst                                                          0x00E4
#define SE_VCOEF3_16_15_inst                                                          0x00E5
#define SE_VCOEF3_16_vcoef_shift                                                     (0)
#define SE_VCOEF3_16_vcoef_mask                                                      (0x00003FFF)
#define SE_VCOEF3_16_vcoef(data)                                                     (0x00003FFF&((data)<<0))
#define SE_VCOEF3_16_vcoef_src(data)                                                 ((0x00003FFF&(data))>>0)
#define SE_VCOEF3_16_get_vcoef(data)                                                 ((0x00003FFF&(data))>>0)


#define SE_SC_BITBLIT_COLOR_KEY_0                                                    0x1800C4EC
#define SE_SC_BITBLIT_COLOR_KEY_1                                                    0x1800C4F0
#define SE_SC_BITBLIT_COLOR_KEY_2                                                    0x1800C4F4
#define SE_SC_BITBLIT_COLOR_KEY_0_reg_addr                                           "0xB800C4EC"
#define SE_SC_BITBLIT_COLOR_KEY_1_reg_addr                                           "0xB800C4F0"
#define SE_SC_BITBLIT_COLOR_KEY_2_reg_addr                                           "0xB800C4F4"
#define SE_SC_BITBLIT_COLOR_KEY_0_reg                                                0xB800C4EC
#define SE_SC_BITBLIT_COLOR_KEY_1_reg                                                0xB800C4F0
#define SE_SC_BITBLIT_COLOR_KEY_2_reg                                                0xB800C4F4
#define set_SE_SC_BITBLIT_COLOR_KEY_0_reg(data)   (*((volatile unsigned int*) SE_SC_BITBLIT_COLOR_KEY_0_reg)=data)
#define set_SE_SC_BITBLIT_COLOR_KEY_1_reg(data)   (*((volatile unsigned int*) SE_SC_BITBLIT_COLOR_KEY_1_reg)=data)
#define set_SE_SC_BITBLIT_COLOR_KEY_2_reg(data)   (*((volatile unsigned int*) SE_SC_BITBLIT_COLOR_KEY_2_reg)=data)
#define get_SE_SC_BITBLIT_COLOR_KEY_0_reg   (*((volatile unsigned int*) SE_SC_BITBLIT_COLOR_KEY_0_reg))
#define get_SE_SC_BITBLIT_COLOR_KEY_1_reg   (*((volatile unsigned int*) SE_SC_BITBLIT_COLOR_KEY_1_reg))
#define get_SE_SC_BITBLIT_COLOR_KEY_2_reg   (*((volatile unsigned int*) SE_SC_BITBLIT_COLOR_KEY_2_reg))
#define SE_SC_BITBLIT_COLOR_KEY_0_inst_adr                                           "0x003B"
#define SE_SC_BITBLIT_COLOR_KEY_1_inst_adr                                           "0x003C"
#define SE_SC_BITBLIT_COLOR_KEY_2_inst_adr                                           "0x003D"
#define SE_SC_BITBLIT_COLOR_KEY_0_inst                                               0x003B
#define SE_SC_BITBLIT_COLOR_KEY_1_inst                                               0x003C
#define SE_SC_BITBLIT_COLOR_KEY_2_inst                                               0x003D
#define SE_SC_BITBLIT_COLOR_KEY_color_key_shift                                      (0)
#define SE_SC_BITBLIT_COLOR_KEY_color_key_mask                                       (0x00FFFFFF)
#define SE_SC_BITBLIT_COLOR_KEY_color_key(data)                                      (0x00FFFFFF&((data)<<0))
#define SE_SC_BITBLIT_COLOR_KEY_color_key_src(data)                                  ((0x00FFFFFF&(data))>>0)
#define SE_SC_BITBLIT_COLOR_KEY_get_color_key(data)                                  ((0x00FFFFFF&(data))>>0)


#define SE_CTRL_0                                                                    0x1800C458
#define SE_CTRL_1                                                                    0x1800C45C
#define SE_CTRL_2                                                                    0x1800C460
#define SE_CTRL_0_reg_addr                                                           "0xB800C458"
#define SE_CTRL_1_reg_addr                                                           "0xB800C45C"
#define SE_CTRL_2_reg_addr                                                           "0xB800C460"
#define SE_CTRL_0_reg                                                                0xB800C458
#define SE_CTRL_1_reg                                                                0xB800C45C
#define SE_CTRL_2_reg                                                                0xB800C460
#define set_SE_CTRL_0_reg(data)   (*((volatile unsigned int*) SE_CTRL_0_reg)=data)
#define set_SE_CTRL_1_reg(data)   (*((volatile unsigned int*) SE_CTRL_1_reg)=data)
#define set_SE_CTRL_2_reg(data)   (*((volatile unsigned int*) SE_CTRL_2_reg)=data)
#define get_SE_CTRL_0_reg   (*((volatile unsigned int*) SE_CTRL_0_reg))
#define get_SE_CTRL_1_reg   (*((volatile unsigned int*) SE_CTRL_1_reg))
#define get_SE_CTRL_2_reg   (*((volatile unsigned int*) SE_CTRL_2_reg))
#define SE_CTRL_0_inst_adr                                                           "0x0016"
#define SE_CTRL_1_inst_adr                                                           "0x0017"
#define SE_CTRL_2_inst_adr                                                           "0x0018"
#define SE_CTRL_0_inst                                                               0x0016
#define SE_CTRL_1_inst                                                               0x0017
#define SE_CTRL_2_inst                                                               0x0018
#define SE_CTRL_endiswap_shift                                                       (2)
#define SE_CTRL_endiswap_mask                                                        (0x00000004)
#define SE_CTRL_endiswap(data)                                                       (0x00000004&((data)<<2))
#define SE_CTRL_endiswap_src(data)                                                   ((0x00000004&(data))>>2)
#define SE_CTRL_get_endiswap(data)                                                   ((0x00000004&(data))>>2)
#define SE_CTRL_go_shift                                                             (1)
#define SE_CTRL_go_mask                                                              (0x00000002)
#define SE_CTRL_go(data)                                                             (0x00000002&((data)<<1))
#define SE_CTRL_go_src(data)                                                         ((0x00000002&(data))>>1)
#define SE_CTRL_get_go(data)                                                         ((0x00000002&(data))>>1)
#define SE_CTRL_write_data_shift                                                     (0)
#define SE_CTRL_write_data_mask                                                      (0x00000001)
#define SE_CTRL_write_data(data)                                                     (0x00000001&((data)<<0))
#define SE_CTRL_write_data_src(data)                                                 ((0x00000001&(data))>>0)
#define SE_CTRL_get_write_data(data)                                                 ((0x00000001&(data))>>0)


#define SE_IDLE_0                                                                    0x1800C464
#define SE_IDLE_1                                                                    0x1800C468
#define SE_IDLE_2                                                                    0x1800C46C
#define SE_IDLE_0_reg_addr                                                           "0xB800C464"
#define SE_IDLE_1_reg_addr                                                           "0xB800C468"
#define SE_IDLE_2_reg_addr                                                           "0xB800C46C"
#define SE_IDLE_0_reg                                                                0xB800C464
#define SE_IDLE_1_reg                                                                0xB800C468
#define SE_IDLE_2_reg                                                                0xB800C46C
#define set_SE_IDLE_0_reg(data)   (*((volatile unsigned int*) SE_IDLE_0_reg)=data)
#define set_SE_IDLE_1_reg(data)   (*((volatile unsigned int*) SE_IDLE_1_reg)=data)
#define set_SE_IDLE_2_reg(data)   (*((volatile unsigned int*) SE_IDLE_2_reg)=data)
#define get_SE_IDLE_0_reg   (*((volatile unsigned int*) SE_IDLE_0_reg))
#define get_SE_IDLE_1_reg   (*((volatile unsigned int*) SE_IDLE_1_reg))
#define get_SE_IDLE_2_reg   (*((volatile unsigned int*) SE_IDLE_2_reg))
#define SE_IDLE_0_inst_adr                                                           "0x0019"
#define SE_IDLE_1_inst_adr                                                           "0x001A"
#define SE_IDLE_2_inst_adr                                                           "0x001B"
#define SE_IDLE_0_inst                                                               0x0019
#define SE_IDLE_1_inst                                                               0x001A
#define SE_IDLE_2_inst                                                               0x001B
#define SE_IDLE_idle_shift                                                           (0)
#define SE_IDLE_idle_mask                                                            (0x00000001)
#define SE_IDLE_idle(data)                                                           (0x00000001&((data)<<0))
#define SE_IDLE_idle_src(data)                                                       ((0x00000001&(data))>>0)
#define SE_IDLE_get_idle(data)                                                       ((0x00000001&(data))>>0)


#define SE_INTSEL                                                                    0x1800C470
#define SE_INTSEL_reg_addr                                                           "0xB800C470"
#define SE_INTSEL_reg                                                                0xB800C470
#define set_SE_INTSEL_reg(data)   (*((volatile unsigned int*) SE_INTSEL_reg)=data)
#define get_SE_INTSEL_reg   (*((volatile unsigned int*) SE_INTSEL_reg))
#define SE_INTSEL_inst_adr                                                           "0x001C"
#define SE_INTSEL_inst                                                               0x001C
#define SE_INTSEL_sel3_shift                                                         (2)
#define SE_INTSEL_sel3_mask                                                          (0x00000004)
#define SE_INTSEL_sel3(data)                                                         (0x00000004&((data)<<2))
#define SE_INTSEL_sel3_src(data)                                                     ((0x00000004&(data))>>2)
#define SE_INTSEL_get_sel3(data)                                                     ((0x00000004&(data))>>2)
#define SE_INTSEL_sel2_shift                                                         (1)
#define SE_INTSEL_sel2_mask                                                          (0x00000002)
#define SE_INTSEL_sel2(data)                                                         (0x00000002&((data)<<1))
#define SE_INTSEL_sel2_src(data)                                                     ((0x00000002&(data))>>1)
#define SE_INTSEL_get_sel2(data)                                                     ((0x00000002&(data))>>1)
#define SE_INTSEL_sel1_shift                                                         (0)
#define SE_INTSEL_sel1_mask                                                          (0x00000001)
#define SE_INTSEL_sel1(data)                                                         (0x00000001&((data)<<0))
#define SE_INTSEL_sel1_src(data)                                                     ((0x00000001&(data))>>0)
#define SE_INTSEL_get_sel1(data)                                                     ((0x00000001&(data))>>0)


#define SE_INTS_0                                                                    0x1800C474
#define SE_INTS_1                                                                    0x1800C478
#define SE_INTS_2                                                                    0x1800C47C
#define SE_INTS_0_reg_addr                                                           "0xB800C474"
#define SE_INTS_1_reg_addr                                                           "0xB800C478"
#define SE_INTS_2_reg_addr                                                           "0xB800C47C"
#define SE_INTS_0_reg                                                                0xB800C474
#define SE_INTS_1_reg                                                                0xB800C478
#define SE_INTS_2_reg                                                                0xB800C47C
#define set_SE_INTS_0_reg(data)   (*((volatile unsigned int*) SE_INTS_0_reg)=data)
#define set_SE_INTS_1_reg(data)   (*((volatile unsigned int*) SE_INTS_1_reg)=data)
#define set_SE_INTS_2_reg(data)   (*((volatile unsigned int*) SE_INTS_2_reg)=data)
#define get_SE_INTS_0_reg   (*((volatile unsigned int*) SE_INTS_0_reg))
#define get_SE_INTS_1_reg   (*((volatile unsigned int*) SE_INTS_1_reg))
#define get_SE_INTS_2_reg   (*((volatile unsigned int*) SE_INTS_2_reg))
#define SE_INTS_0_inst_adr                                                           "0x001D"
#define SE_INTS_1_inst_adr                                                           "0x001E"
#define SE_INTS_2_inst_adr                                                           "0x001F"
#define SE_INTS_0_inst                                                               0x001D
#define SE_INTS_1_inst                                                               0x001E
#define SE_INTS_2_inst                                                               0x001F
#define SE_INTS_vo_sync_err_shift                                                    (17)
#define SE_INTS_vo_sync_err_mask                                                     (0x00020000)
#define SE_INTS_vo_sync_err(data)                                                    (0x00020000&((data)<<17))
#define SE_INTS_vo_sync_err_src(data)                                                ((0x00020000&(data))>>17)
#define SE_INTS_get_vo_sync_err(data)                                                ((0x00020000&(data))>>17)
#define SE_INTS_fmt_err_shift                                                        (16)
#define SE_INTS_fmt_err_mask                                                         (0x00010000)
#define SE_INTS_fmt_err(data)                                                        (0x00010000&((data)<<16))
#define SE_INTS_fmt_err_src(data)                                                    ((0x00010000&(data))>>16)
#define SE_INTS_get_fmt_err(data)                                                    ((0x00010000&(data))>>16)
#define SE_INTS_com_empty_shift                                                      (3)
#define SE_INTS_com_empty_mask                                                       (0x00000008)
#define SE_INTS_com_empty(data)                                                      (0x00000008&((data)<<3))
#define SE_INTS_com_empty_src(data)                                                  ((0x00000008&(data))>>3)
#define SE_INTS_get_com_empty(data)                                                  ((0x00000008&(data))>>3)
#define SE_INTS_com_err_shift                                                        (2)
#define SE_INTS_com_err_mask                                                         (0x00000004)
#define SE_INTS_com_err(data)                                                        (0x00000004&((data)<<2))
#define SE_INTS_com_err_src(data)                                                    ((0x00000004&(data))>>2)
#define SE_INTS_get_com_err(data)                                                    ((0x00000004&(data))>>2)
#define SE_INTS_sync_shift                                                           (1)
#define SE_INTS_sync_mask                                                            (0x00000002)
#define SE_INTS_sync(data)                                                           (0x00000002&((data)<<1))
#define SE_INTS_sync_src(data)                                                       ((0x00000002&(data))>>1)
#define SE_INTS_get_sync(data)                                                       ((0x00000002&(data))>>1)
#define SE_INTS_write_data_shift                                                     (0)
#define SE_INTS_write_data_mask                                                      (0x00000001)
#define SE_INTS_write_data(data)                                                     (0x00000001&((data)<<0))
#define SE_INTS_write_data_src(data)                                                 ((0x00000001&(data))>>0)
#define SE_INTS_get_write_data(data)                                                 ((0x00000001&(data))>>0)


#define SE_INTE_0                                                                    0x1800C480
#define SE_INTE_1                                                                    0x1800C484
#define SE_INTE_2                                                                    0x1800C488
#define SE_INTE_0_reg_addr                                                           "0xB800C480"
#define SE_INTE_1_reg_addr                                                           "0xB800C484"
#define SE_INTE_2_reg_addr                                                           "0xB800C488"
#define SE_INTE_0_reg                                                                0xB800C480
#define SE_INTE_1_reg                                                                0xB800C484
#define SE_INTE_2_reg                                                                0xB800C488
#define set_SE_INTE_0_reg(data)   (*((volatile unsigned int*) SE_INTE_0_reg)=data)
#define set_SE_INTE_1_reg(data)   (*((volatile unsigned int*) SE_INTE_1_reg)=data)
#define set_SE_INTE_2_reg(data)   (*((volatile unsigned int*) SE_INTE_2_reg)=data)
#define get_SE_INTE_0_reg   (*((volatile unsigned int*) SE_INTE_0_reg))
#define get_SE_INTE_1_reg   (*((volatile unsigned int*) SE_INTE_1_reg))
#define get_SE_INTE_2_reg   (*((volatile unsigned int*) SE_INTE_2_reg))
#define SE_INTE_0_inst_adr                                                           "0x0020"
#define SE_INTE_1_inst_adr                                                           "0x0021"
#define SE_INTE_2_inst_adr                                                           "0x0022"
#define SE_INTE_0_inst                                                               0x0020
#define SE_INTE_1_inst                                                               0x0021
#define SE_INTE_2_inst                                                               0x0022
#define SE_INTE_vo_sync_err_shift                                                    (17)
#define SE_INTE_vo_sync_err_mask                                                     (0x00020000)
#define SE_INTE_vo_sync_err(data)                                                    (0x00020000&((data)<<17))
#define SE_INTE_vo_sync_err_src(data)                                                ((0x00020000&(data))>>17)
#define SE_INTE_get_vo_sync_err(data)                                                ((0x00020000&(data))>>17)
#define SE_INTE_fmt_err_shift                                                        (16)
#define SE_INTE_fmt_err_mask                                                         (0x00010000)
#define SE_INTE_fmt_err(data)                                                        (0x00010000&((data)<<16))
#define SE_INTE_fmt_err_src(data)                                                    ((0x00010000&(data))>>16)
#define SE_INTE_get_fmt_err(data)                                                    ((0x00010000&(data))>>16)
#define SE_INTE_com_empty_shift                                                      (3)
#define SE_INTE_com_empty_mask                                                       (0x00000008)
#define SE_INTE_com_empty(data)                                                      (0x00000008&((data)<<3))
#define SE_INTE_com_empty_src(data)                                                  ((0x00000008&(data))>>3)
#define SE_INTE_get_com_empty(data)                                                  ((0x00000008&(data))>>3)
#define SE_INTE_com_err_shift                                                        (2)
#define SE_INTE_com_err_mask                                                         (0x00000004)
#define SE_INTE_com_err(data)                                                        (0x00000004&((data)<<2))
#define SE_INTE_com_err_src(data)                                                    ((0x00000004&(data))>>2)
#define SE_INTE_get_com_err(data)                                                    ((0x00000004&(data))>>2)
#define SE_INTE_sync_shift                                                           (1)
#define SE_INTE_sync_mask                                                            (0x00000002)
#define SE_INTE_sync(data)                                                           (0x00000002&((data)<<1))
#define SE_INTE_sync_src(data)                                                       ((0x00000002&(data))>>1)
#define SE_INTE_get_sync(data)                                                       ((0x00000002&(data))>>1)
#define SE_INTE_write_data_shift                                                     (0)
#define SE_INTE_write_data_mask                                                      (0x00000001)
#define SE_INTE_write_data(data)                                                     (0x00000001&((data)<<0))
#define SE_INTE_write_data_src(data)                                                 ((0x00000001&(data))>>0)
#define SE_INTE_get_write_data(data)                                                 ((0x00000001&(data))>>0)


#define SE_INSTCNT_L_0                                                               0x1800C48C
#define SE_INSTCNT_L_1                                                               0x1800C490
#define SE_INSTCNT_L_2                                                               0x1800C494
#define SE_INSTCNT_L_0_reg_addr                                                      "0xB800C48C"
#define SE_INSTCNT_L_1_reg_addr                                                      "0xB800C490"
#define SE_INSTCNT_L_2_reg_addr                                                      "0xB800C494"
#define SE_INSTCNT_L_0_reg                                                           0xB800C48C
#define SE_INSTCNT_L_1_reg                                                           0xB800C490
#define SE_INSTCNT_L_2_reg                                                           0xB800C494
#define set_SE_INSTCNT_L_0_reg(data)   (*((volatile unsigned int*) SE_INSTCNT_L_0_reg)=data)
#define set_SE_INSTCNT_L_1_reg(data)   (*((volatile unsigned int*) SE_INSTCNT_L_1_reg)=data)
#define set_SE_INSTCNT_L_2_reg(data)   (*((volatile unsigned int*) SE_INSTCNT_L_2_reg)=data)
#define get_SE_INSTCNT_L_0_reg   (*((volatile unsigned int*) SE_INSTCNT_L_0_reg))
#define get_SE_INSTCNT_L_1_reg   (*((volatile unsigned int*) SE_INSTCNT_L_1_reg))
#define get_SE_INSTCNT_L_2_reg   (*((volatile unsigned int*) SE_INSTCNT_L_2_reg))
#define SE_INSTCNT_L_0_inst_adr                                                      "0x0023"
#define SE_INSTCNT_L_1_inst_adr                                                      "0x0024"
#define SE_INSTCNT_L_2_inst_adr                                                      "0x0025"
#define SE_INSTCNT_L_0_inst                                                          0x0023
#define SE_INSTCNT_L_1_inst                                                          0x0024
#define SE_INSTCNT_L_2_inst                                                          0x0025
#define SE_INSTCNT_L_instcnt_l_shift                                                 (0)
#define SE_INSTCNT_L_instcnt_l_mask                                                  (0xFFFFFFFF)
#define SE_INSTCNT_L_instcnt_l(data)                                                 (0xFFFFFFFF&((data)<<0))
#define SE_INSTCNT_L_instcnt_l_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define SE_INSTCNT_L_get_instcnt_l(data)                                             ((0xFFFFFFFF&(data))>>0)


#define SE_INSTCNT_H_0                                                               0x1800C510
#define SE_INSTCNT_H_1                                                               0x1800C514
#define SE_INSTCNT_H_2                                                               0x1800C518
#define SE_INSTCNT_H_0_reg_addr                                                      "0xB800C510"
#define SE_INSTCNT_H_1_reg_addr                                                      "0xB800C514"
#define SE_INSTCNT_H_2_reg_addr                                                      "0xB800C518"
#define SE_INSTCNT_H_0_reg                                                           0xB800C510
#define SE_INSTCNT_H_1_reg                                                           0xB800C514
#define SE_INSTCNT_H_2_reg                                                           0xB800C518
#define set_SE_INSTCNT_H_0_reg(data)   (*((volatile unsigned int*) SE_INSTCNT_H_0_reg)=data)
#define set_SE_INSTCNT_H_1_reg(data)   (*((volatile unsigned int*) SE_INSTCNT_H_1_reg)=data)
#define set_SE_INSTCNT_H_2_reg(data)   (*((volatile unsigned int*) SE_INSTCNT_H_2_reg)=data)
#define get_SE_INSTCNT_H_0_reg   (*((volatile unsigned int*) SE_INSTCNT_H_0_reg))
#define get_SE_INSTCNT_H_1_reg   (*((volatile unsigned int*) SE_INSTCNT_H_1_reg))
#define get_SE_INSTCNT_H_2_reg   (*((volatile unsigned int*) SE_INSTCNT_H_2_reg))
#define SE_INSTCNT_H_0_inst_adr                                                      "0x0044"
#define SE_INSTCNT_H_1_inst_adr                                                      "0x0045"
#define SE_INSTCNT_H_2_inst_adr                                                      "0x0046"
#define SE_INSTCNT_H_0_inst                                                          0x0044
#define SE_INSTCNT_H_1_inst                                                          0x0045
#define SE_INSTCNT_H_2_inst                                                          0x0046
#define SE_INSTCNT_H_instcnt_h_shift                                                 (0)
#define SE_INSTCNT_H_instcnt_h_mask                                                  (0xFFFFFFFF)
#define SE_INSTCNT_H_instcnt_h(data)                                                 (0xFFFFFFFF&((data)<<0))
#define SE_INSTCNT_H_instcnt_h_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define SE_INSTCNT_H_get_instcnt_h(data)                                             ((0xFFFFFFFF&(data))>>0)


#define SE_CLUT_RADR                                                                 0x1800C498
#define SE_CLUT_RADR_reg_addr                                                        "0xB800C498"
#define SE_CLUT_RADR_reg                                                             0xB800C498
#define set_SE_CLUT_RADR_reg(data)   (*((volatile unsigned int*) SE_CLUT_RADR_reg)=data)
#define get_SE_CLUT_RADR_reg   (*((volatile unsigned int*) SE_CLUT_RADR_reg))
#define SE_CLUT_RADR_inst_adr                                                        "0x0026"
#define SE_CLUT_RADR_inst                                                            0x0026
#define SE_CLUT_RADR_radr_shift                                                      (0)
#define SE_CLUT_RADR_radr_mask                                                       (0x000000FF)
#define SE_CLUT_RADR_radr(data)                                                      (0x000000FF&((data)<<0))
#define SE_CLUT_RADR_radr_src(data)                                                  ((0x000000FF&(data))>>0)
#define SE_CLUT_RADR_get_radr(data)                                                  ((0x000000FF&(data))>>0)


#define SE_CLUT_VALUE                                                                0x1800C49C
#define SE_CLUT_VALUE_reg_addr                                                       "0xB800C49C"
#define SE_CLUT_VALUE_reg                                                            0xB800C49C
#define set_SE_CLUT_VALUE_reg(data)   (*((volatile unsigned int*) SE_CLUT_VALUE_reg)=data)
#define get_SE_CLUT_VALUE_reg   (*((volatile unsigned int*) SE_CLUT_VALUE_reg))
#define SE_CLUT_VALUE_inst_adr                                                       "0x0027"
#define SE_CLUT_VALUE_inst                                                           0x0027
#define SE_CLUT_VALUE_value_shift                                                    (0)
#define SE_CLUT_VALUE_value_mask                                                     (0xFFFFFFFF)
#define SE_CLUT_VALUE_value(data)                                                    (0xFFFFFFFF&((data)<<0))
#define SE_CLUT_VALUE_value_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define SE_CLUT_VALUE_get_value(data)                                                ((0xFFFFFFFF&(data))>>0)


#define SE_DBG                                                                       0x1800C4A0
#define SE_DBG_reg_addr                                                              "0xB800C4A0"
#define SE_DBG_reg                                                                   0xB800C4A0
#define set_SE_DBG_reg(data)   (*((volatile unsigned int*) SE_DBG_reg)=data)
#define get_SE_DBG_reg   (*((volatile unsigned int*) SE_DBG_reg))
#define SE_DBG_inst_adr                                                              "0x0028"
#define SE_DBG_inst                                                                  0x0028
#define SE_DBG_dbg_en_shift                                                          (24)
#define SE_DBG_dbg_en_mask                                                           (0x01000000)
#define SE_DBG_dbg_en(data)                                                          (0x01000000&((data)<<24))
#define SE_DBG_dbg_en_src(data)                                                      ((0x01000000&(data))>>24)
#define SE_DBG_get_dbg_en(data)                                                      ((0x01000000&(data))>>24)
#define SE_DBG_dbg_module_sel1_shift                                                 (20)
#define SE_DBG_dbg_module_sel1_mask                                                  (0x00F00000)
#define SE_DBG_dbg_module_sel1(data)                                                 (0x00F00000&((data)<<20))
#define SE_DBG_dbg_module_sel1_src(data)                                             ((0x00F00000&(data))>>20)
#define SE_DBG_get_dbg_module_sel1(data)                                             ((0x00F00000&(data))>>20)
#define SE_DBG_dbg_module_sel0_shift                                                 (16)
#define SE_DBG_dbg_module_sel0_mask                                                  (0x000F0000)
#define SE_DBG_dbg_module_sel0(data)                                                 (0x000F0000&((data)<<16))
#define SE_DBG_dbg_module_sel0_src(data)                                             ((0x000F0000&(data))>>16)
#define SE_DBG_get_dbg_module_sel0(data)                                             ((0x000F0000&(data))>>16)
#define SE_DBG_dbg_sel1_shift                                                        (8)
#define SE_DBG_dbg_sel1_mask                                                         (0x00001F00)
#define SE_DBG_dbg_sel1(data)                                                        (0x00001F00&((data)<<8))
#define SE_DBG_dbg_sel1_src(data)                                                    ((0x00001F00&(data))>>8)
#define SE_DBG_get_dbg_sel1(data)                                                    ((0x00001F00&(data))>>8)
#define SE_DBG_dbg_sel0_shift                                                        (0)
#define SE_DBG_dbg_sel0_mask                                                         (0x0000001F)
#define SE_DBG_dbg_sel0(data)                                                        (0x0000001F&((data)<<0))
#define SE_DBG_dbg_sel0_src(data)                                                    ((0x0000001F&(data))>>0)
#define SE_DBG_get_dbg_sel0(data)                                                    ((0x0000001F&(data))>>0)


#define SE_SCTCH                                                                     0x1800C4A4
#define SE_SCTCH_reg_addr                                                            "0xB800C4A4"
#define SE_SCTCH_reg                                                                 0xB800C4A4
#define set_SE_SCTCH_reg(data)   (*((volatile unsigned int*) SE_SCTCH_reg)=data)
#define get_SE_SCTCH_reg   (*((volatile unsigned int*) SE_SCTCH_reg))
#define SE_SCTCH_inst_adr                                                            "0x0029"
#define SE_SCTCH_inst                                                                0x0029
#define SE_SCTCH_Reg1_shift                                                          (16)
#define SE_SCTCH_Reg1_mask                                                           (0xFFFF0000)
#define SE_SCTCH_Reg1(data)                                                          (0xFFFF0000&((data)<<16))
#define SE_SCTCH_Reg1_src(data)                                                      ((0xFFFF0000&(data))>>16)
#define SE_SCTCH_get_Reg1(data)                                                      ((0xFFFF0000&(data))>>16)
#define SE_SCTCH_Reg0_shift                                                          (0)
#define SE_SCTCH_Reg0_mask                                                           (0x0000FFFF)
#define SE_SCTCH_Reg0(data)                                                          (0x0000FFFF&((data)<<0))
#define SE_SCTCH_Reg0_src(data)                                                      ((0x0000FFFF&(data))>>0)
#define SE_SCTCH_get_Reg0(data)                                                      ((0x0000FFFF&(data))>>0)


#define SE_GCRA_CTRL                                                                 0x1800C4A8
#define SE_GCRA_CTRL_reg_addr                                                        "0xB800C4A8"
#define SE_GCRA_CTRL_reg                                                             0xB800C4A8
#define set_SE_GCRA_CTRL_reg(data)   (*((volatile unsigned int*) SE_GCRA_CTRL_reg)=data)
#define get_SE_GCRA_CTRL_reg   (*((volatile unsigned int*) SE_GCRA_CTRL_reg))
#define SE_GCRA_CTRL_inst_adr                                                        "0x002A"
#define SE_GCRA_CTRL_inst                                                            0x002A
#define SE_GCRA_CTRL_Gcra_en_shift                                                   (0)
#define SE_GCRA_CTRL_Gcra_en_mask                                                    (0x00000001)
#define SE_GCRA_CTRL_Gcra_en(data)                                                   (0x00000001&((data)<<0))
#define SE_GCRA_CTRL_Gcra_en_src(data)                                               ((0x00000001&(data))>>0)
#define SE_GCRA_CTRL_get_Gcra_en(data)                                               ((0x00000001&(data))>>0)


#define SE_GCRA_REQ_CNT                                                              0x1800C4AC
#define SE_GCRA_REQ_CNT_reg_addr                                                     "0xB800C4AC"
#define SE_GCRA_REQ_CNT_reg                                                          0xB800C4AC
#define set_SE_GCRA_REQ_CNT_reg(data)   (*((volatile unsigned int*) SE_GCRA_REQ_CNT_reg)=data)
#define get_SE_GCRA_REQ_CNT_reg   (*((volatile unsigned int*) SE_GCRA_REQ_CNT_reg))
#define SE_GCRA_REQ_CNT_inst_adr                                                     "0x002B"
#define SE_GCRA_REQ_CNT_inst                                                         0x002B
#define SE_GCRA_REQ_CNT_Gcra_req_num_shift                                           (0)
#define SE_GCRA_REQ_CNT_Gcra_req_num_mask                                            (0x00FFFFFF)
#define SE_GCRA_REQ_CNT_Gcra_req_num(data)                                           (0x00FFFFFF&((data)<<0))
#define SE_GCRA_REQ_CNT_Gcra_req_num_src(data)                                       ((0x00FFFFFF&(data))>>0)
#define SE_GCRA_REQ_CNT_get_Gcra_req_num(data)                                       ((0x00FFFFFF&(data))>>0)


#define SE_GCRA_TIM_CNT                                                              0x1800C4B0
#define SE_GCRA_TIM_CNT_reg_addr                                                     "0xB800C4B0"
#define SE_GCRA_TIM_CNT_reg                                                          0xB800C4B0
#define set_SE_GCRA_TIM_CNT_reg(data)   (*((volatile unsigned int*) SE_GCRA_TIM_CNT_reg)=data)
#define get_SE_GCRA_TIM_CNT_reg   (*((volatile unsigned int*) SE_GCRA_TIM_CNT_reg))
#define SE_GCRA_TIM_CNT_inst_adr                                                     "0x002C"
#define SE_GCRA_TIM_CNT_inst                                                         0x002C
#define SE_GCRA_TIM_CNT_Gcra_tim_cnt_shift                                           (0)
#define SE_GCRA_TIM_CNT_Gcra_tim_cnt_mask                                            (0xFFFFFFFF)
#define SE_GCRA_TIM_CNT_Gcra_tim_cnt(data)                                           (0xFFFFFFFF&((data)<<0))
#define SE_GCRA_TIM_CNT_Gcra_tim_cnt_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define SE_GCRA_TIM_CNT_get_Gcra_tim_cnt(data)                                       ((0xFFFFFFFF&(data))>>0)


#define SE_GCRA_TIM_THR                                                              0x1800C4B4
#define SE_GCRA_TIM_THR_reg_addr                                                     "0xB800C4B4"
#define SE_GCRA_TIM_THR_reg                                                          0xB800C4B4
#define set_SE_GCRA_TIM_THR_reg(data)   (*((volatile unsigned int*) SE_GCRA_TIM_THR_reg)=data)
#define get_SE_GCRA_TIM_THR_reg   (*((volatile unsigned int*) SE_GCRA_TIM_THR_reg))
#define SE_GCRA_TIM_THR_inst_adr                                                     "0x002D"
#define SE_GCRA_TIM_THR_inst                                                         0x002D
#define SE_GCRA_TIM_THR_Gcra_tim_thr_shift                                           (0)
#define SE_GCRA_TIM_THR_Gcra_tim_thr_mask                                            (0xFFFFFFFF)
#define SE_GCRA_TIM_THR_Gcra_tim_thr(data)                                           (0xFFFFFFFF&((data)<<0))
#define SE_GCRA_TIM_THR_Gcra_tim_thr_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define SE_GCRA_TIM_THR_get_Gcra_tim_thr(data)                                       ((0xFFFFFFFF&(data))>>0)


#define SE_GCRA_REQ_THR                                                              0x1800C4B8
#define SE_GCRA_REQ_THR_reg_addr                                                     "0xB800C4B8"
#define SE_GCRA_REQ_THR_reg                                                          0xB800C4B8
#define set_SE_GCRA_REQ_THR_reg(data)   (*((volatile unsigned int*) SE_GCRA_REQ_THR_reg)=data)
#define get_SE_GCRA_REQ_THR_reg   (*((volatile unsigned int*) SE_GCRA_REQ_THR_reg))
#define SE_GCRA_REQ_THR_inst_adr                                                     "0x002E"
#define SE_GCRA_REQ_THR_inst                                                         0x002E
#define SE_GCRA_REQ_THR_Gcra_req_thr_shift                                           (0)
#define SE_GCRA_REQ_THR_Gcra_req_thr_mask                                            (0x00FFFFFF)
#define SE_GCRA_REQ_THR_Gcra_req_thr(data)                                           (0x00FFFFFF&((data)<<0))
#define SE_GCRA_REQ_THR_Gcra_req_thr_src(data)                                       ((0x00FFFFFF&(data))>>0)
#define SE_GCRA_REQ_THR_get_Gcra_req_thr(data)                                       ((0x00FFFFFF&(data))>>0)


#endif
