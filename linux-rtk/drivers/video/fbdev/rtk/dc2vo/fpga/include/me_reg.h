/**************************************************************
// Spec Version                  : 0.0.5
// Parser Version                : MAR_Parser_1.0
// CModelGen Version             : 1.0 2006.04.18
// Naming Rule                   : Module_Register_Name_reg
// Firmware Header Generate Date : 2008/4/3
***************************************************************/


#ifndef _ME_REG_H_INCLUDED_
#define _ME_REG_H_INCLUDED_
#ifdef  _ME_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     err:1;
unsigned int     reserved_1:4;
unsigned int     qs:1;
unsigned int     rnd:1;
unsigned int     fmt1:1;
unsigned int     fmt0:1;
unsigned int     reserved_2:2;
unsigned int     mbl1:1;
unsigned int     mbl0:1;
unsigned int     ints:1;
unsigned int     inte:1;
unsigned int     disable_mp:1;
unsigned int     tw:1;
unsigned int     tms:1;
unsigned int     tbs:1;
unsigned int     go:1;
unsigned int     write_data:1;
}ME_CTRL;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     addr:28;
}ME_CMDADDR;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     addr:28;
}ME_RLTADDR;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     fld:1;
unsigned int     reserved_1:1;
unsigned int     ti:7;
unsigned int     reserved_2:1;
unsigned int     bi:7;
}ME_TSETA;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     y:11;
unsigned int     xinc:4;
unsigned int     reserved_1:1;
unsigned int     x:11;
}ME_TSETB;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     fld:1;
unsigned int     reserved_1:1;
unsigned int     ti:7;
unsigned int     reserved_2:1;
unsigned int     bi:7;
}ME_RSETA;

typedef struct 
{
unsigned int     mvys:2;
unsigned int     reserved_0:6;
unsigned int     mvxs:2;
unsigned int     reserved_1:6;
unsigned int     mvx:8;
unsigned int     mvy:8;
}ME_RSETB;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     y:11;
unsigned int     xinc:4;
unsigned int     reserved_1:1;
unsigned int     x:11;
}ME_RSETC;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     rh:11;
unsigned int     reserved_1:5;
unsigned int     rw:11;
}ME_RSETD;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     tsy:11;
unsigned int     reserved_1:5;
unsigned int     tsx:11;
}ME_RSETE;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     tey:11;
unsigned int     reserved_1:5;
unsigned int     tex:11;
}ME_RSETF;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     bsy:11;
unsigned int     reserved_1:5;
unsigned int     bsx:11;
}ME_RSETG;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     bey:11;
unsigned int     reserved_1:5;
unsigned int     bex:11;
}ME_RSETH;

typedef struct 
{
unsigned int     stage:1;
unsigned int     half:2;
unsigned int     mvce:1;
unsigned int     hdrlt:1;
unsigned int     mvcfp:3;
unsigned int     mvcf:8;
unsigned int     zmvp:1;
unsigned int     hdsad:1;
unsigned int     can:2;
unsigned int     bk8x8:1;
unsigned int     bscale:3;
unsigned int     zmvb:8;
}ME_MSETA;

typedef struct 
{
unsigned int     mvcb:8;
unsigned int     mvct:8;
unsigned int     reserved_0:1;
unsigned int     ryadj:1;
unsigned int     ry:6;
unsigned int     reserved_1:1;
unsigned int     rxadj:1;
unsigned int     rx:6;
}ME_MSETB;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     write_enable3:1;
unsigned int     sel1:3;
unsigned int     write_enable2:1;
unsigned int     sel0:3;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}ME_DBG;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     addr:28;
}ME_MVM_BASE;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     skip_sad:1;
unsigned int     reserved_1:7;
unsigned int     len:6;
unsigned int     reserved_2:1;
unsigned int     rstfmt:1;
}ME_MVM_LEN;

#endif

#define ME_CTRL                                                                      0x18009000
#define ME_CTRL_reg_addr                                                             "0xB8009000"
#define ME_CTRL_reg                                                                  0xB8009000
#define ME_CTRL_inst_adr                                                             "0x0000"
#define ME_CTRL_inst                                                                 0x0000
#define ME_CTRL_err_shift                                                            (20)
#define ME_CTRL_err_mask                                                             (0x00100000)
#define ME_CTRL_err(data)                                                            (0x00100000&((data)<<20))
#define ME_CTRL_err_src(data)                                                        ((0x00100000&(data))>>20)
#define ME_CTRL_get_err(data)                                                        ((0x00100000&(data))>>20)
#define ME_CTRL_qs_shift                                                             (15)
#define ME_CTRL_qs_mask                                                              (0x00008000)
#define ME_CTRL_qs(data)                                                             (0x00008000&((data)<<15))
#define ME_CTRL_qs_src(data)                                                         ((0x00008000&(data))>>15)
#define ME_CTRL_get_qs(data)                                                         ((0x00008000&(data))>>15)
#define ME_CTRL_rnd_shift                                                            (14)
#define ME_CTRL_rnd_mask                                                             (0x00004000)
#define ME_CTRL_rnd(data)                                                            (0x00004000&((data)<<14))
#define ME_CTRL_rnd_src(data)                                                        ((0x00004000&(data))>>14)
#define ME_CTRL_get_rnd(data)                                                        ((0x00004000&(data))>>14)
#define ME_CTRL_fmt1_shift                                                           (13)
#define ME_CTRL_fmt1_mask                                                            (0x00002000)
#define ME_CTRL_fmt1(data)                                                           (0x00002000&((data)<<13))
#define ME_CTRL_fmt1_src(data)                                                       ((0x00002000&(data))>>13)
#define ME_CTRL_get_fmt1(data)                                                       ((0x00002000&(data))>>13)
#define ME_CTRL_fmt0_shift                                                           (12)
#define ME_CTRL_fmt0_mask                                                            (0x00001000)
#define ME_CTRL_fmt0(data)                                                           (0x00001000&((data)<<12))
#define ME_CTRL_fmt0_src(data)                                                       ((0x00001000&(data))>>12)
#define ME_CTRL_get_fmt0(data)                                                       ((0x00001000&(data))>>12)
#define ME_CTRL_mbl1_shift                                                           (9)
#define ME_CTRL_mbl1_mask                                                            (0x00000200)
#define ME_CTRL_mbl1(data)                                                           (0x00000200&((data)<<9))
#define ME_CTRL_mbl1_src(data)                                                       ((0x00000200&(data))>>9)
#define ME_CTRL_get_mbl1(data)                                                       ((0x00000200&(data))>>9)
#define ME_CTRL_mbl0_shift                                                           (8)
#define ME_CTRL_mbl0_mask                                                            (0x00000100)
#define ME_CTRL_mbl0(data)                                                           (0x00000100&((data)<<8))
#define ME_CTRL_mbl0_src(data)                                                       ((0x00000100&(data))>>8)
#define ME_CTRL_get_mbl0(data)                                                       ((0x00000100&(data))>>8)
#define ME_CTRL_ints_shift                                                           (7)
#define ME_CTRL_ints_mask                                                            (0x00000080)
#define ME_CTRL_ints(data)                                                           (0x00000080&((data)<<7))
#define ME_CTRL_ints_src(data)                                                       ((0x00000080&(data))>>7)
#define ME_CTRL_get_ints(data)                                                       ((0x00000080&(data))>>7)
#define ME_CTRL_inte_shift                                                           (6)
#define ME_CTRL_inte_mask                                                            (0x00000040)
#define ME_CTRL_inte(data)                                                           (0x00000040&((data)<<6))
#define ME_CTRL_inte_src(data)                                                       ((0x00000040&(data))>>6)
#define ME_CTRL_get_inte(data)                                                       ((0x00000040&(data))>>6)
#define ME_CTRL_disable_mp_shift                                                     (5)
#define ME_CTRL_disable_mp_mask                                                      (0x00000020)
#define ME_CTRL_disable_mp(data)                                                     (0x00000020&((data)<<5))
#define ME_CTRL_disable_mp_src(data)                                                 ((0x00000020&(data))>>5)
#define ME_CTRL_get_disable_mp(data)                                                 ((0x00000020&(data))>>5)
#define ME_CTRL_tw_shift                                                             (4)
#define ME_CTRL_tw_mask                                                              (0x00000010)
#define ME_CTRL_tw(data)                                                             (0x00000010&((data)<<4))
#define ME_CTRL_tw_src(data)                                                         ((0x00000010&(data))>>4)
#define ME_CTRL_get_tw(data)                                                         ((0x00000010&(data))>>4)
#define ME_CTRL_tms_shift                                                            (3)
#define ME_CTRL_tms_mask                                                             (0x00000008)
#define ME_CTRL_tms(data)                                                            (0x00000008&((data)<<3))
#define ME_CTRL_tms_src(data)                                                        ((0x00000008&(data))>>3)
#define ME_CTRL_get_tms(data)                                                        ((0x00000008&(data))>>3)
#define ME_CTRL_tbs_shift                                                            (2)
#define ME_CTRL_tbs_mask                                                             (0x00000004)
#define ME_CTRL_tbs(data)                                                            (0x00000004&((data)<<2))
#define ME_CTRL_tbs_src(data)                                                        ((0x00000004&(data))>>2)
#define ME_CTRL_get_tbs(data)                                                        ((0x00000004&(data))>>2)
#define ME_CTRL_go_shift                                                             (1)
#define ME_CTRL_go_mask                                                              (0x00000002)
#define ME_CTRL_go(data)                                                             (0x00000002&((data)<<1))
#define ME_CTRL_go_src(data)                                                         ((0x00000002&(data))>>1)
#define ME_CTRL_get_go(data)                                                         ((0x00000002&(data))>>1)
#define ME_CTRL_write_data_shift                                                     (0)
#define ME_CTRL_write_data_mask                                                      (0x00000001)
#define ME_CTRL_write_data(data)                                                     (0x00000001&((data)<<0))
#define ME_CTRL_write_data_src(data)                                                 ((0x00000001&(data))>>0)
#define ME_CTRL_get_write_data(data)                                                 ((0x00000001&(data))>>0)


#define ME_CMDADDR                                                                   0x18009010
#define ME_CMDADDR_reg_addr                                                          "0xB8009010"
#define ME_CMDADDR_reg                                                               0xB8009010
#define ME_CMDADDR_inst_adr                                                          "0x0004"
#define ME_CMDADDR_inst                                                              0x0004
#define ME_CMDADDR_addr_shift                                                        (0)
#define ME_CMDADDR_addr_mask                                                         (0x0FFFFFFF)
#define ME_CMDADDR_addr(data)                                                        (0x0FFFFFFF&((data)<<0))
#define ME_CMDADDR_addr_src(data)                                                    ((0x0FFFFFFF&(data))>>0)
#define ME_CMDADDR_get_addr(data)                                                    ((0x0FFFFFFF&(data))>>0)


#define ME_RLTADDR                                                                   0x18009014
#define ME_RLTADDR_reg_addr                                                          "0xB8009014"
#define ME_RLTADDR_reg                                                               0xB8009014
#define ME_RLTADDR_inst_adr                                                          "0x0005"
#define ME_RLTADDR_inst                                                              0x0005
#define ME_RLTADDR_addr_shift                                                        (0)
#define ME_RLTADDR_addr_mask                                                         (0x0FFFFFFF)
#define ME_RLTADDR_addr(data)                                                        (0x0FFFFFFF&((data)<<0))
#define ME_RLTADDR_addr_src(data)                                                    ((0x0FFFFFFF&(data))>>0)
#define ME_RLTADDR_get_addr(data)                                                    ((0x0FFFFFFF&(data))>>0)


#define ME_TSETA_0                                                                   0x18009018
#define ME_TSETA_1                                                                   0x1800901C
#define ME_TSETA_0_reg_addr                                                          "0xB8009018"
#define ME_TSETA_1_reg_addr                                                          "0xB800901C"
#define ME_TSETA_0_reg                                                               0xB8009018
#define ME_TSETA_1_reg                                                               0xB800901C
#define ME_TSETA_0_inst_adr                                                          "0x0006"
#define ME_TSETA_1_inst_adr                                                          "0x0007"
#define ME_TSETA_0_inst                                                              0x0006
#define ME_TSETA_1_inst                                                              0x0007
#define ME_TSETA_fld_shift                                                           (16)
#define ME_TSETA_fld_mask                                                            (0x00010000)
#define ME_TSETA_fld(data)                                                           (0x00010000&((data)<<16))
#define ME_TSETA_fld_src(data)                                                       ((0x00010000&(data))>>16)
#define ME_TSETA_get_fld(data)                                                       ((0x00010000&(data))>>16)
#define ME_TSETA_ti_shift                                                            (8)
#define ME_TSETA_ti_mask                                                             (0x00007F00)
#define ME_TSETA_ti(data)                                                            (0x00007F00&((data)<<8))
#define ME_TSETA_ti_src(data)                                                        ((0x00007F00&(data))>>8)
#define ME_TSETA_get_ti(data)                                                        ((0x00007F00&(data))>>8)
#define ME_TSETA_bi_shift                                                            (0)
#define ME_TSETA_bi_mask                                                             (0x0000007F)
#define ME_TSETA_bi(data)                                                            (0x0000007F&((data)<<0))
#define ME_TSETA_bi_src(data)                                                        ((0x0000007F&(data))>>0)
#define ME_TSETA_get_bi(data)                                                        ((0x0000007F&(data))>>0)


#define ME_TSETB_0                                                                   0x18009020
#define ME_TSETB_1                                                                   0x18009024
#define ME_TSETB_0_reg_addr                                                          "0xB8009020"
#define ME_TSETB_1_reg_addr                                                          "0xB8009024"
#define ME_TSETB_0_reg                                                               0xB8009020
#define ME_TSETB_1_reg                                                               0xB8009024
#define ME_TSETB_0_inst_adr                                                          "0x0008"
#define ME_TSETB_1_inst_adr                                                          "0x0009"
#define ME_TSETB_0_inst                                                              0x0008
#define ME_TSETB_1_inst                                                              0x0009
#define ME_TSETB_y_shift                                                             (16)
#define ME_TSETB_y_mask                                                              (0x07FF0000)
#define ME_TSETB_y(data)                                                             (0x07FF0000&((data)<<16))
#define ME_TSETB_y_src(data)                                                         ((0x07FF0000&(data))>>16)
#define ME_TSETB_get_y(data)                                                         ((0x07FF0000&(data))>>16)
#define ME_TSETB_xinc_shift                                                          (12)
#define ME_TSETB_xinc_mask                                                           (0x0000F000)
#define ME_TSETB_xinc(data)                                                          (0x0000F000&((data)<<12))
#define ME_TSETB_xinc_src(data)                                                      ((0x0000F000&(data))>>12)
#define ME_TSETB_get_xinc(data)                                                      ((0x0000F000&(data))>>12)
#define ME_TSETB_x_shift                                                             (0)
#define ME_TSETB_x_mask                                                              (0x000007FF)
#define ME_TSETB_x(data)                                                             (0x000007FF&((data)<<0))
#define ME_TSETB_x_src(data)                                                         ((0x000007FF&(data))>>0)
#define ME_TSETB_get_x(data)                                                         ((0x000007FF&(data))>>0)


#define ME_RSETA_0                                                                   0x18009028
#define ME_RSETA_1                                                                   0x1800902C
#define ME_RSETA_0_reg_addr                                                          "0xB8009028"
#define ME_RSETA_1_reg_addr                                                          "0xB800902C"
#define ME_RSETA_0_reg                                                               0xB8009028
#define ME_RSETA_1_reg                                                               0xB800902C
#define ME_RSETA_0_inst_adr                                                          "0x000A"
#define ME_RSETA_1_inst_adr                                                          "0x000B"
#define ME_RSETA_0_inst                                                              0x000A
#define ME_RSETA_1_inst                                                              0x000B
#define ME_RSETA_fld_shift                                                           (16)
#define ME_RSETA_fld_mask                                                            (0x00010000)
#define ME_RSETA_fld(data)                                                           (0x00010000&((data)<<16))
#define ME_RSETA_fld_src(data)                                                       ((0x00010000&(data))>>16)
#define ME_RSETA_get_fld(data)                                                       ((0x00010000&(data))>>16)
#define ME_RSETA_ti_shift                                                            (8)
#define ME_RSETA_ti_mask                                                             (0x00007F00)
#define ME_RSETA_ti(data)                                                            (0x00007F00&((data)<<8))
#define ME_RSETA_ti_src(data)                                                        ((0x00007F00&(data))>>8)
#define ME_RSETA_get_ti(data)                                                        ((0x00007F00&(data))>>8)
#define ME_RSETA_bi_shift                                                            (0)
#define ME_RSETA_bi_mask                                                             (0x0000007F)
#define ME_RSETA_bi(data)                                                            (0x0000007F&((data)<<0))
#define ME_RSETA_bi_src(data)                                                        ((0x0000007F&(data))>>0)
#define ME_RSETA_get_bi(data)                                                        ((0x0000007F&(data))>>0)


#define ME_RSETB_0                                                                   0x18009030
#define ME_RSETB_1                                                                   0x18009034
#define ME_RSETB_0_reg_addr                                                          "0xB8009030"
#define ME_RSETB_1_reg_addr                                                          "0xB8009034"
#define ME_RSETB_0_reg                                                               0xB8009030
#define ME_RSETB_1_reg                                                               0xB8009034
#define ME_RSETB_0_inst_adr                                                          "0x000C"
#define ME_RSETB_1_inst_adr                                                          "0x000D"
#define ME_RSETB_0_inst                                                              0x000C
#define ME_RSETB_1_inst                                                              0x000D
#define ME_RSETB_mvys_shift                                                          (30)
#define ME_RSETB_mvys_mask                                                           (0xC0000000)
#define ME_RSETB_mvys(data)                                                          (0xC0000000&((data)<<30))
#define ME_RSETB_mvys_src(data)                                                      ((0xC0000000&(data))>>30)
#define ME_RSETB_get_mvys(data)                                                      ((0xC0000000&(data))>>30)
#define ME_RSETB_mvxs_shift                                                          (22)
#define ME_RSETB_mvxs_mask                                                           (0x00C00000)
#define ME_RSETB_mvxs(data)                                                          (0x00C00000&((data)<<22))
#define ME_RSETB_mvxs_src(data)                                                      ((0x00C00000&(data))>>22)
#define ME_RSETB_get_mvxs(data)                                                      ((0x00C00000&(data))>>22)
#define ME_RSETB_mvx_shift                                                           (8)
#define ME_RSETB_mvx_mask                                                            (0x0000FF00)
#define ME_RSETB_mvx(data)                                                           (0x0000FF00&((data)<<8))
#define ME_RSETB_mvx_src(data)                                                       ((0x0000FF00&(data))>>8)
#define ME_RSETB_get_mvx(data)                                                       ((0x0000FF00&(data))>>8)
#define ME_RSETB_mvy_shift                                                           (0)
#define ME_RSETB_mvy_mask                                                            (0x000000FF)
#define ME_RSETB_mvy(data)                                                           (0x000000FF&((data)<<0))
#define ME_RSETB_mvy_src(data)                                                       ((0x000000FF&(data))>>0)
#define ME_RSETB_get_mvy(data)                                                       ((0x000000FF&(data))>>0)


#define ME_RSETC_0                                                                   0x18009038
#define ME_RSETC_1                                                                   0x1800903C
#define ME_RSETC_0_reg_addr                                                          "0xB8009038"
#define ME_RSETC_1_reg_addr                                                          "0xB800903C"
#define ME_RSETC_0_reg                                                               0xB8009038
#define ME_RSETC_1_reg                                                               0xB800903C
#define ME_RSETC_0_inst_adr                                                          "0x000E"
#define ME_RSETC_1_inst_adr                                                          "0x000F"
#define ME_RSETC_0_inst                                                              0x000E
#define ME_RSETC_1_inst                                                              0x000F
#define ME_RSETC_y_shift                                                             (16)
#define ME_RSETC_y_mask                                                              (0x07FF0000)
#define ME_RSETC_y(data)                                                             (0x07FF0000&((data)<<16))
#define ME_RSETC_y_src(data)                                                         ((0x07FF0000&(data))>>16)
#define ME_RSETC_get_y(data)                                                         ((0x07FF0000&(data))>>16)
#define ME_RSETC_xinc_shift                                                          (12)
#define ME_RSETC_xinc_mask                                                           (0x0000F000)
#define ME_RSETC_xinc(data)                                                          (0x0000F000&((data)<<12))
#define ME_RSETC_xinc_src(data)                                                      ((0x0000F000&(data))>>12)
#define ME_RSETC_get_xinc(data)                                                      ((0x0000F000&(data))>>12)
#define ME_RSETC_x_shift                                                             (0)
#define ME_RSETC_x_mask                                                              (0x000007FF)
#define ME_RSETC_x(data)                                                             (0x000007FF&((data)<<0))
#define ME_RSETC_x_src(data)                                                         ((0x000007FF&(data))>>0)
#define ME_RSETC_get_x(data)                                                         ((0x000007FF&(data))>>0)


#define ME_RSETD_0                                                                   0x18009040
#define ME_RSETD_1                                                                   0x18009044
#define ME_RSETD_0_reg_addr                                                          "0xB8009040"
#define ME_RSETD_1_reg_addr                                                          "0xB8009044"
#define ME_RSETD_0_reg                                                               0xB8009040
#define ME_RSETD_1_reg                                                               0xB8009044
#define ME_RSETD_0_inst_adr                                                          "0x0010"
#define ME_RSETD_1_inst_adr                                                          "0x0011"
#define ME_RSETD_0_inst                                                              0x0010
#define ME_RSETD_1_inst                                                              0x0011
#define ME_RSETD_rh_shift                                                            (16)
#define ME_RSETD_rh_mask                                                             (0x07FF0000)
#define ME_RSETD_rh(data)                                                            (0x07FF0000&((data)<<16))
#define ME_RSETD_rh_src(data)                                                        ((0x07FF0000&(data))>>16)
#define ME_RSETD_get_rh(data)                                                        ((0x07FF0000&(data))>>16)
#define ME_RSETD_rw_shift                                                            (0)
#define ME_RSETD_rw_mask                                                             (0x000007FF)
#define ME_RSETD_rw(data)                                                            (0x000007FF&((data)<<0))
#define ME_RSETD_rw_src(data)                                                        ((0x000007FF&(data))>>0)
#define ME_RSETD_get_rw(data)                                                        ((0x000007FF&(data))>>0)


#define ME_RSETE_0                                                                   0x18009048
#define ME_RSETE_1                                                                   0x1800904C
#define ME_RSETE_0_reg_addr                                                          "0xB8009048"
#define ME_RSETE_1_reg_addr                                                          "0xB800904C"
#define ME_RSETE_0_reg                                                               0xB8009048
#define ME_RSETE_1_reg                                                               0xB800904C
#define ME_RSETE_0_inst_adr                                                          "0x0012"
#define ME_RSETE_1_inst_adr                                                          "0x0013"
#define ME_RSETE_0_inst                                                              0x0012
#define ME_RSETE_1_inst                                                              0x0013
#define ME_RSETE_tsy_shift                                                           (16)
#define ME_RSETE_tsy_mask                                                            (0x07FF0000)
#define ME_RSETE_tsy(data)                                                           (0x07FF0000&((data)<<16))
#define ME_RSETE_tsy_src(data)                                                       ((0x07FF0000&(data))>>16)
#define ME_RSETE_get_tsy(data)                                                       ((0x07FF0000&(data))>>16)
#define ME_RSETE_tsx_shift                                                           (0)
#define ME_RSETE_tsx_mask                                                            (0x000007FF)
#define ME_RSETE_tsx(data)                                                           (0x000007FF&((data)<<0))
#define ME_RSETE_tsx_src(data)                                                       ((0x000007FF&(data))>>0)
#define ME_RSETE_get_tsx(data)                                                       ((0x000007FF&(data))>>0)


#define ME_RSETF_0                                                                   0x18009050
#define ME_RSETF_1                                                                   0x18009054
#define ME_RSETF_0_reg_addr                                                          "0xB8009050"
#define ME_RSETF_1_reg_addr                                                          "0xB8009054"
#define ME_RSETF_0_reg                                                               0xB8009050
#define ME_RSETF_1_reg                                                               0xB8009054
#define ME_RSETF_0_inst_adr                                                          "0x0014"
#define ME_RSETF_1_inst_adr                                                          "0x0015"
#define ME_RSETF_0_inst                                                              0x0014
#define ME_RSETF_1_inst                                                              0x0015
#define ME_RSETF_tey_shift                                                           (16)
#define ME_RSETF_tey_mask                                                            (0x07FF0000)
#define ME_RSETF_tey(data)                                                           (0x07FF0000&((data)<<16))
#define ME_RSETF_tey_src(data)                                                       ((0x07FF0000&(data))>>16)
#define ME_RSETF_get_tey(data)                                                       ((0x07FF0000&(data))>>16)
#define ME_RSETF_tex_shift                                                           (0)
#define ME_RSETF_tex_mask                                                            (0x000007FF)
#define ME_RSETF_tex(data)                                                           (0x000007FF&((data)<<0))
#define ME_RSETF_tex_src(data)                                                       ((0x000007FF&(data))>>0)
#define ME_RSETF_get_tex(data)                                                       ((0x000007FF&(data))>>0)


#define ME_RSETG_0                                                                   0x18009058
#define ME_RSETG_1                                                                   0x1800905C
#define ME_RSETG_0_reg_addr                                                          "0xB8009058"
#define ME_RSETG_1_reg_addr                                                          "0xB800905C"
#define ME_RSETG_0_reg                                                               0xB8009058
#define ME_RSETG_1_reg                                                               0xB800905C
#define ME_RSETG_0_inst_adr                                                          "0x0016"
#define ME_RSETG_1_inst_adr                                                          "0x0017"
#define ME_RSETG_0_inst                                                              0x0016
#define ME_RSETG_1_inst                                                              0x0017
#define ME_RSETG_bsy_shift                                                           (16)
#define ME_RSETG_bsy_mask                                                            (0x07FF0000)
#define ME_RSETG_bsy(data)                                                           (0x07FF0000&((data)<<16))
#define ME_RSETG_bsy_src(data)                                                       ((0x07FF0000&(data))>>16)
#define ME_RSETG_get_bsy(data)                                                       ((0x07FF0000&(data))>>16)
#define ME_RSETG_bsx_shift                                                           (0)
#define ME_RSETG_bsx_mask                                                            (0x000007FF)
#define ME_RSETG_bsx(data)                                                           (0x000007FF&((data)<<0))
#define ME_RSETG_bsx_src(data)                                                       ((0x000007FF&(data))>>0)
#define ME_RSETG_get_bsx(data)                                                       ((0x000007FF&(data))>>0)


#define ME_RSETH_0                                                                   0x18009060
#define ME_RSETH_1                                                                   0x18009064
#define ME_RSETH_0_reg_addr                                                          "0xB8009060"
#define ME_RSETH_1_reg_addr                                                          "0xB8009064"
#define ME_RSETH_0_reg                                                               0xB8009060
#define ME_RSETH_1_reg                                                               0xB8009064
#define ME_RSETH_0_inst_adr                                                          "0x0018"
#define ME_RSETH_1_inst_adr                                                          "0x0019"
#define ME_RSETH_0_inst                                                              0x0018
#define ME_RSETH_1_inst                                                              0x0019
#define ME_RSETH_bey_shift                                                           (16)
#define ME_RSETH_bey_mask                                                            (0x07FF0000)
#define ME_RSETH_bey(data)                                                           (0x07FF0000&((data)<<16))
#define ME_RSETH_bey_src(data)                                                       ((0x07FF0000&(data))>>16)
#define ME_RSETH_get_bey(data)                                                       ((0x07FF0000&(data))>>16)
#define ME_RSETH_bex_shift                                                           (0)
#define ME_RSETH_bex_mask                                                            (0x000007FF)
#define ME_RSETH_bex(data)                                                           (0x000007FF&((data)<<0))
#define ME_RSETH_bex_src(data)                                                       ((0x000007FF&(data))>>0)
#define ME_RSETH_get_bex(data)                                                       ((0x000007FF&(data))>>0)


#define ME_MSETA_0                                                                   0x18009068
#define ME_MSETA_1                                                                   0x1800906C
#define ME_MSETA_2                                                                   0x18009070
#define ME_MSETA_3                                                                   0x18009074
#define ME_MSETA_0_reg_addr                                                          "0xB8009068"
#define ME_MSETA_1_reg_addr                                                          "0xB800906C"
#define ME_MSETA_2_reg_addr                                                          "0xB8009070"
#define ME_MSETA_3_reg_addr                                                          "0xB8009074"
#define ME_MSETA_0_reg                                                               0xB8009068
#define ME_MSETA_1_reg                                                               0xB800906C
#define ME_MSETA_2_reg                                                               0xB8009070
#define ME_MSETA_3_reg                                                               0xB8009074
#define ME_MSETA_0_inst_adr                                                          "0x001A"
#define ME_MSETA_1_inst_adr                                                          "0x001B"
#define ME_MSETA_2_inst_adr                                                          "0x001C"
#define ME_MSETA_3_inst_adr                                                          "0x001D"
#define ME_MSETA_0_inst                                                              0x001A
#define ME_MSETA_1_inst                                                              0x001B
#define ME_MSETA_2_inst                                                              0x001C
#define ME_MSETA_3_inst                                                              0x001D
#define ME_MSETA_stage_shift                                                         (31)
#define ME_MSETA_stage_mask                                                          (0x80000000)
#define ME_MSETA_stage(data)                                                         (0x80000000&((data)<<31))
#define ME_MSETA_stage_src(data)                                                     ((0x80000000&(data))>>31)
#define ME_MSETA_get_stage(data)                                                     ((0x80000000&(data))>>31)
#define ME_MSETA_half_shift                                                          (29)
#define ME_MSETA_half_mask                                                           (0x60000000)
#define ME_MSETA_half(data)                                                          (0x60000000&((data)<<29))
#define ME_MSETA_half_src(data)                                                      ((0x60000000&(data))>>29)
#define ME_MSETA_get_half(data)                                                      ((0x60000000&(data))>>29)
#define ME_MSETA_mvce_shift                                                          (28)
#define ME_MSETA_mvce_mask                                                           (0x10000000)
#define ME_MSETA_mvce(data)                                                          (0x10000000&((data)<<28))
#define ME_MSETA_mvce_src(data)                                                      ((0x10000000&(data))>>28)
#define ME_MSETA_get_mvce(data)                                                      ((0x10000000&(data))>>28)
#define ME_MSETA_hdrlt_shift                                                         (27)
#define ME_MSETA_hdrlt_mask                                                          (0x08000000)
#define ME_MSETA_hdrlt(data)                                                         (0x08000000&((data)<<27))
#define ME_MSETA_hdrlt_src(data)                                                     ((0x08000000&(data))>>27)
#define ME_MSETA_get_hdrlt(data)                                                     ((0x08000000&(data))>>27)
#define ME_MSETA_mvcfp_shift                                                         (24)
#define ME_MSETA_mvcfp_mask                                                          (0x07000000)
#define ME_MSETA_mvcfp(data)                                                         (0x07000000&((data)<<24))
#define ME_MSETA_mvcfp_src(data)                                                     ((0x07000000&(data))>>24)
#define ME_MSETA_get_mvcfp(data)                                                     ((0x07000000&(data))>>24)
#define ME_MSETA_mvcf_shift                                                          (16)
#define ME_MSETA_mvcf_mask                                                           (0x00FF0000)
#define ME_MSETA_mvcf(data)                                                          (0x00FF0000&((data)<<16))
#define ME_MSETA_mvcf_src(data)                                                      ((0x00FF0000&(data))>>16)
#define ME_MSETA_get_mvcf(data)                                                      ((0x00FF0000&(data))>>16)
#define ME_MSETA_zmvp_shift                                                          (15)
#define ME_MSETA_zmvp_mask                                                           (0x00008000)
#define ME_MSETA_zmvp(data)                                                          (0x00008000&((data)<<15))
#define ME_MSETA_zmvp_src(data)                                                      ((0x00008000&(data))>>15)
#define ME_MSETA_get_zmvp(data)                                                      ((0x00008000&(data))>>15)
#define ME_MSETA_hdsad_shift                                                         (14)
#define ME_MSETA_hdsad_mask                                                          (0x00004000)
#define ME_MSETA_hdsad(data)                                                         (0x00004000&((data)<<14))
#define ME_MSETA_hdsad_src(data)                                                     ((0x00004000&(data))>>14)
#define ME_MSETA_get_hdsad(data)                                                     ((0x00004000&(data))>>14)
#define ME_MSETA_can_shift                                                           (12)
#define ME_MSETA_can_mask                                                            (0x00003000)
#define ME_MSETA_can(data)                                                           (0x00003000&((data)<<12))
#define ME_MSETA_can_src(data)                                                       ((0x00003000&(data))>>12)
#define ME_MSETA_get_can(data)                                                       ((0x00003000&(data))>>12)
#define ME_MSETA_bk8x8_shift                                                         (11)
#define ME_MSETA_bk8x8_mask                                                          (0x00000800)
#define ME_MSETA_bk8x8(data)                                                         (0x00000800&((data)<<11))
#define ME_MSETA_bk8x8_src(data)                                                     ((0x00000800&(data))>>11)
#define ME_MSETA_get_bk8x8(data)                                                     ((0x00000800&(data))>>11)
#define ME_MSETA_bscale_shift                                                        (8)
#define ME_MSETA_bscale_mask                                                         (0x00000700)
#define ME_MSETA_bscale(data)                                                        (0x00000700&((data)<<8))
#define ME_MSETA_bscale_src(data)                                                    ((0x00000700&(data))>>8)
#define ME_MSETA_get_bscale(data)                                                    ((0x00000700&(data))>>8)
#define ME_MSETA_zmvb_shift                                                          (0)
#define ME_MSETA_zmvb_mask                                                           (0x000000FF)
#define ME_MSETA_zmvb(data)                                                          (0x000000FF&((data)<<0))
#define ME_MSETA_zmvb_src(data)                                                      ((0x000000FF&(data))>>0)
#define ME_MSETA_get_zmvb(data)                                                      ((0x000000FF&(data))>>0)


#define ME_MSETB_0                                                                   0x18009078
#define ME_MSETB_1                                                                   0x1800907C
#define ME_MSETB_2                                                                   0x18009080
#define ME_MSETB_3                                                                   0x18009084
#define ME_MSETB_0_reg_addr                                                          "0xB8009078"
#define ME_MSETB_1_reg_addr                                                          "0xB800907C"
#define ME_MSETB_2_reg_addr                                                          "0xB8009080"
#define ME_MSETB_3_reg_addr                                                          "0xB8009084"
#define ME_MSETB_0_reg                                                               0xB8009078
#define ME_MSETB_1_reg                                                               0xB800907C
#define ME_MSETB_2_reg                                                               0xB8009080
#define ME_MSETB_3_reg                                                               0xB8009084
#define ME_MSETB_0_inst_adr                                                          "0x001E"
#define ME_MSETB_1_inst_adr                                                          "0x001F"
#define ME_MSETB_2_inst_adr                                                          "0x0020"
#define ME_MSETB_3_inst_adr                                                          "0x0021"
#define ME_MSETB_0_inst                                                              0x001E
#define ME_MSETB_1_inst                                                              0x001F
#define ME_MSETB_2_inst                                                              0x0020
#define ME_MSETB_3_inst                                                              0x0021
#define ME_MSETB_mvcb_shift                                                          (24)
#define ME_MSETB_mvcb_mask                                                           (0xFF000000)
#define ME_MSETB_mvcb(data)                                                          (0xFF000000&((data)<<24))
#define ME_MSETB_mvcb_src(data)                                                      ((0xFF000000&(data))>>24)
#define ME_MSETB_get_mvcb(data)                                                      ((0xFF000000&(data))>>24)
#define ME_MSETB_mvct_shift                                                          (16)
#define ME_MSETB_mvct_mask                                                           (0x00FF0000)
#define ME_MSETB_mvct(data)                                                          (0x00FF0000&((data)<<16))
#define ME_MSETB_mvct_src(data)                                                      ((0x00FF0000&(data))>>16)
#define ME_MSETB_get_mvct(data)                                                      ((0x00FF0000&(data))>>16)
#define ME_MSETB_ryadj_shift                                                         (14)
#define ME_MSETB_ryadj_mask                                                          (0x00004000)
#define ME_MSETB_ryadj(data)                                                         (0x00004000&((data)<<14))
#define ME_MSETB_ryadj_src(data)                                                     ((0x00004000&(data))>>14)
#define ME_MSETB_get_ryadj(data)                                                     ((0x00004000&(data))>>14)
#define ME_MSETB_ry_shift                                                            (8)
#define ME_MSETB_ry_mask                                                             (0x00003F00)
#define ME_MSETB_ry(data)                                                            (0x00003F00&((data)<<8))
#define ME_MSETB_ry_src(data)                                                        ((0x00003F00&(data))>>8)
#define ME_MSETB_get_ry(data)                                                        ((0x00003F00&(data))>>8)
#define ME_MSETB_rxadj_shift                                                         (6)
#define ME_MSETB_rxadj_mask                                                          (0x00000040)
#define ME_MSETB_rxadj(data)                                                         (0x00000040&((data)<<6))
#define ME_MSETB_rxadj_src(data)                                                     ((0x00000040&(data))>>6)
#define ME_MSETB_get_rxadj(data)                                                     ((0x00000040&(data))>>6)
#define ME_MSETB_rx_shift                                                            (0)
#define ME_MSETB_rx_mask                                                             (0x0000003F)
#define ME_MSETB_rx(data)                                                            (0x0000003F&((data)<<0))
#define ME_MSETB_rx_src(data)                                                        ((0x0000003F&(data))>>0)
#define ME_MSETB_get_rx(data)                                                        ((0x0000003F&(data))>>0)


#define ME_DBG                                                                       0x18009088
#define ME_DBG_reg_addr                                                              "0xB8009088"
#define ME_DBG_reg                                                                   0xB8009088
#define ME_DBG_inst_adr                                                              "0x0022"
#define ME_DBG_inst                                                                  0x0022
#define ME_DBG_write_enable3_shift                                                   (9)
#define ME_DBG_write_enable3_mask                                                    (0x00000200)
#define ME_DBG_write_enable3(data)                                                   (0x00000200&((data)<<9))
#define ME_DBG_write_enable3_src(data)                                               ((0x00000200&(data))>>9)
#define ME_DBG_get_write_enable3(data)                                               ((0x00000200&(data))>>9)
#define ME_DBG_sel1_shift                                                            (6)
#define ME_DBG_sel1_mask                                                             (0x000001C0)
#define ME_DBG_sel1(data)                                                            (0x000001C0&((data)<<6))
#define ME_DBG_sel1_src(data)                                                        ((0x000001C0&(data))>>6)
#define ME_DBG_get_sel1(data)                                                        ((0x000001C0&(data))>>6)
#define ME_DBG_write_enable2_shift                                                   (5)
#define ME_DBG_write_enable2_mask                                                    (0x00000020)
#define ME_DBG_write_enable2(data)                                                   (0x00000020&((data)<<5))
#define ME_DBG_write_enable2_src(data)                                               ((0x00000020&(data))>>5)
#define ME_DBG_get_write_enable2(data)                                               ((0x00000020&(data))>>5)
#define ME_DBG_sel0_shift                                                            (2)
#define ME_DBG_sel0_mask                                                             (0x0000001C)
#define ME_DBG_sel0(data)                                                            (0x0000001C&((data)<<2))
#define ME_DBG_sel0_src(data)                                                        ((0x0000001C&(data))>>2)
#define ME_DBG_get_sel0(data)                                                        ((0x0000001C&(data))>>2)
#define ME_DBG_write_enable1_shift                                                   (1)
#define ME_DBG_write_enable1_mask                                                    (0x00000002)
#define ME_DBG_write_enable1(data)                                                   (0x00000002&((data)<<1))
#define ME_DBG_write_enable1_src(data)                                               ((0x00000002&(data))>>1)
#define ME_DBG_get_write_enable1(data)                                               ((0x00000002&(data))>>1)
#define ME_DBG_enable_shift                                                          (0)
#define ME_DBG_enable_mask                                                           (0x00000001)
#define ME_DBG_enable(data)                                                          (0x00000001&((data)<<0))
#define ME_DBG_enable_src(data)                                                      ((0x00000001&(data))>>0)
#define ME_DBG_get_enable(data)                                                      ((0x00000001&(data))>>0)


#define ME_MVM_BASE_0                                                                0x1800908C
#define ME_MVM_BASE_1                                                                0x18009090
#define ME_MVM_BASE_0_reg_addr                                                       "0xB800908C"
#define ME_MVM_BASE_1_reg_addr                                                       "0xB8009090"
#define ME_MVM_BASE_0_reg                                                            0xB800908C
#define ME_MVM_BASE_1_reg                                                            0xB8009090
#define ME_MVM_BASE_0_inst_adr                                                       "0x0023"
#define ME_MVM_BASE_1_inst_adr                                                       "0x0024"
#define ME_MVM_BASE_0_inst                                                           0x0023
#define ME_MVM_BASE_1_inst                                                           0x0024
#define ME_MVM_BASE_addr_shift                                                       (0)
#define ME_MVM_BASE_addr_mask                                                        (0x0FFFFFFF)
#define ME_MVM_BASE_addr(data)                                                       (0x0FFFFFFF&((data)<<0))
#define ME_MVM_BASE_addr_src(data)                                                   ((0x0FFFFFFF&(data))>>0)
#define ME_MVM_BASE_get_addr(data)                                                   ((0x0FFFFFFF&(data))>>0)


#define ME_MVM_LEN_0                                                                 0x18009094
#define ME_MVM_LEN_1                                                                 0x18009098
#define ME_MVM_LEN_0_reg_addr                                                        "0xB8009094"
#define ME_MVM_LEN_1_reg_addr                                                        "0xB8009098"
#define ME_MVM_LEN_0_reg                                                             0xB8009094
#define ME_MVM_LEN_1_reg                                                             0xB8009098
#define ME_MVM_LEN_0_inst_adr                                                        "0x0025"
#define ME_MVM_LEN_1_inst_adr                                                        "0x0026"
#define ME_MVM_LEN_0_inst                                                            0x0025
#define ME_MVM_LEN_1_inst                                                            0x0026
#define ME_MVM_LEN_skip_sad_shift                                                    (15)
#define ME_MVM_LEN_skip_sad_mask                                                     (0x00008000)
#define ME_MVM_LEN_skip_sad(data)                                                    (0x00008000&((data)<<15))
#define ME_MVM_LEN_skip_sad_src(data)                                                ((0x00008000&(data))>>15)
#define ME_MVM_LEN_get_skip_sad(data)                                                ((0x00008000&(data))>>15)
#define ME_MVM_LEN_len_shift                                                         (2)
#define ME_MVM_LEN_len_mask                                                          (0x000000FC)
#define ME_MVM_LEN_len(data)                                                         (0x000000FC&((data)<<2))
#define ME_MVM_LEN_len_src(data)                                                     ((0x000000FC&(data))>>2)
#define ME_MVM_LEN_get_len(data)                                                     ((0x000000FC&(data))>>2)
#define ME_MVM_LEN_rstfmt_shift                                                      (0)
#define ME_MVM_LEN_rstfmt_mask                                                       (0x00000001)
#define ME_MVM_LEN_rstfmt(data)                                                      (0x00000001&((data)<<0))
#define ME_MVM_LEN_rstfmt_src(data)                                                  ((0x00000001&(data))>>0)
#define ME_MVM_LEN_get_rstfmt(data)                                                  ((0x00000001&(data))>>0)


#endif
