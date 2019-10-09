/**************************************************************
// Spec Version                  : 1.0.6
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/4/24 15:17:21
***************************************************************/


#ifndef _PIF_REG_H_INCLUDED_
#define _PIF_REG_H_INCLUDED_
#ifdef  _PIF_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     int_prog:1;
unsigned int     dh_inv:1;
unsigned int     dv_inv:1;
}TIMEGEN_CTRL;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     dh_width:12;
}DH_WIDTH;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     dh_total:12;
unsigned int     reserved_1:4;
unsigned int     dh_total_last_line:12;
}DH_TOTAL;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     dh_den_sta:12;
unsigned int     reserved_1:4;
unsigned int     dh_den_end:12;
}DH_DEN_START_END;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     dv_den_sta_field1:12;
unsigned int     reserved_1:4;
unsigned int     dv_den_end_field1:12;
}DV_DEN_START_END_FIELD1;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     dv_total:12;
}DV_TOTAL;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     dv_vs_sta_field1:12;
unsigned int     reserved_1:4;
unsigned int     dv_vs_end_field1:12;
}DV_VS_START_END_FIELD1;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     dh_vs_adj_field1:12;
}DH_VS_ADJ_FIELD1;

typedef struct 
{
unsigned int     int_en:1;
unsigned int     reserved_0:19;
unsigned int     dv_sync_int:12;
}DV_SYNC_INT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     neg:1;
}PIF_CTRL0;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     lvds_dbg_sel1:7;
unsigned int     lvds_dbg_sel0:7;
unsigned int     lvds_dbg_enable:1;
}LVDS_DBG;

#endif

#define TIMEGEN_CTRL                                                                 0x18009800
#define TIMEGEN_CTRL_reg_addr                                                        "0xB8009800"
#define TIMEGEN_CTRL_reg                                                             0xB8009800
#define set_TIMEGEN_CTRL_reg(data)   (*((volatile unsigned int*) TIMEGEN_CTRL_reg)=data)
#define get_TIMEGEN_CTRL_reg   (*((volatile unsigned int*) TIMEGEN_CTRL_reg))
#define TIMEGEN_CTRL_inst_adr                                                        "0x0000"
#define TIMEGEN_CTRL_inst                                                            0x0000
#define TIMEGEN_CTRL_int_prog_shift                                                  (2)
#define TIMEGEN_CTRL_int_prog_mask                                                   (0x00000004)
#define TIMEGEN_CTRL_int_prog(data)                                                  (0x00000004&((data)<<2))
#define TIMEGEN_CTRL_int_prog_src(data)                                              ((0x00000004&(data))>>2)
#define TIMEGEN_CTRL_get_int_prog(data)                                              ((0x00000004&(data))>>2)
#define TIMEGEN_CTRL_dh_inv_shift                                                    (1)
#define TIMEGEN_CTRL_dh_inv_mask                                                     (0x00000002)
#define TIMEGEN_CTRL_dh_inv(data)                                                    (0x00000002&((data)<<1))
#define TIMEGEN_CTRL_dh_inv_src(data)                                                ((0x00000002&(data))>>1)
#define TIMEGEN_CTRL_get_dh_inv(data)                                                ((0x00000002&(data))>>1)
#define TIMEGEN_CTRL_dv_inv_shift                                                    (0)
#define TIMEGEN_CTRL_dv_inv_mask                                                     (0x00000001)
#define TIMEGEN_CTRL_dv_inv(data)                                                    (0x00000001&((data)<<0))
#define TIMEGEN_CTRL_dv_inv_src(data)                                                ((0x00000001&(data))>>0)
#define TIMEGEN_CTRL_get_dv_inv(data)                                                ((0x00000001&(data))>>0)


#define DH_WIDTH                                                                     0x18009804
#define DH_WIDTH_reg_addr                                                            "0xB8009804"
#define DH_WIDTH_reg                                                                 0xB8009804
#define set_DH_WIDTH_reg(data)   (*((volatile unsigned int*) DH_WIDTH_reg)=data)
#define get_DH_WIDTH_reg   (*((volatile unsigned int*) DH_WIDTH_reg))
#define DH_WIDTH_inst_adr                                                            "0x0001"
#define DH_WIDTH_inst                                                                0x0001
#define DH_WIDTH_dh_width_shift                                                      (0)
#define DH_WIDTH_dh_width_mask                                                       (0x00000FFF)
#define DH_WIDTH_dh_width(data)                                                      (0x00000FFF&((data)<<0))
#define DH_WIDTH_dh_width_src(data)                                                  ((0x00000FFF&(data))>>0)
#define DH_WIDTH_get_dh_width(data)                                                  ((0x00000FFF&(data))>>0)


#define DH_TOTAL                                                                     0x18009808
#define DH_TOTAL_reg_addr                                                            "0xB8009808"
#define DH_TOTAL_reg                                                                 0xB8009808
#define set_DH_TOTAL_reg(data)   (*((volatile unsigned int*) DH_TOTAL_reg)=data)
#define get_DH_TOTAL_reg   (*((volatile unsigned int*) DH_TOTAL_reg))
#define DH_TOTAL_inst_adr                                                            "0x0002"
#define DH_TOTAL_inst                                                                0x0002
#define DH_TOTAL_dh_total_shift                                                      (16)
#define DH_TOTAL_dh_total_mask                                                       (0x0FFF0000)
#define DH_TOTAL_dh_total(data)                                                      (0x0FFF0000&((data)<<16))
#define DH_TOTAL_dh_total_src(data)                                                  ((0x0FFF0000&(data))>>16)
#define DH_TOTAL_get_dh_total(data)                                                  ((0x0FFF0000&(data))>>16)
#define DH_TOTAL_dh_total_last_line_shift                                            (0)
#define DH_TOTAL_dh_total_last_line_mask                                             (0x00000FFF)
#define DH_TOTAL_dh_total_last_line(data)                                            (0x00000FFF&((data)<<0))
#define DH_TOTAL_dh_total_last_line_src(data)                                        ((0x00000FFF&(data))>>0)
#define DH_TOTAL_get_dh_total_last_line(data)                                        ((0x00000FFF&(data))>>0)


#define DH_DEN_START_END                                                             0x1800980c
#define DH_DEN_START_END_reg_addr                                                    "0xB800980C"
#define DH_DEN_START_END_reg                                                         0xB800980C
#define set_DH_DEN_START_END_reg(data)   (*((volatile unsigned int*) DH_DEN_START_END_reg)=data)
#define get_DH_DEN_START_END_reg   (*((volatile unsigned int*) DH_DEN_START_END_reg))
#define DH_DEN_START_END_inst_adr                                                    "0x0003"
#define DH_DEN_START_END_inst                                                        0x0003
#define DH_DEN_START_END_dh_den_sta_shift                                            (16)
#define DH_DEN_START_END_dh_den_sta_mask                                             (0x0FFF0000)
#define DH_DEN_START_END_dh_den_sta(data)                                            (0x0FFF0000&((data)<<16))
#define DH_DEN_START_END_dh_den_sta_src(data)                                        ((0x0FFF0000&(data))>>16)
#define DH_DEN_START_END_get_dh_den_sta(data)                                        ((0x0FFF0000&(data))>>16)
#define DH_DEN_START_END_dh_den_end_shift                                            (0)
#define DH_DEN_START_END_dh_den_end_mask                                             (0x00000FFF)
#define DH_DEN_START_END_dh_den_end(data)                                            (0x00000FFF&((data)<<0))
#define DH_DEN_START_END_dh_den_end_src(data)                                        ((0x00000FFF&(data))>>0)
#define DH_DEN_START_END_get_dh_den_end(data)                                        ((0x00000FFF&(data))>>0)


#define DV_DEN_START_END_FIELD1                                                      0x18009810
#define DV_DEN_START_END_FIELD1_reg_addr                                             "0xB8009810"
#define DV_DEN_START_END_FIELD1_reg                                                  0xB8009810
#define set_DV_DEN_START_END_FIELD1_reg(data)   (*((volatile unsigned int*) DV_DEN_START_END_FIELD1_reg)=data)
#define get_DV_DEN_START_END_FIELD1_reg   (*((volatile unsigned int*) DV_DEN_START_END_FIELD1_reg))
#define DV_DEN_START_END_FIELD1_inst_adr                                             "0x0004"
#define DV_DEN_START_END_FIELD1_inst                                                 0x0004
#define DV_DEN_START_END_FIELD1_dv_den_sta_field1_shift                              (16)
#define DV_DEN_START_END_FIELD1_dv_den_sta_field1_mask                               (0x0FFF0000)
#define DV_DEN_START_END_FIELD1_dv_den_sta_field1(data)                              (0x0FFF0000&((data)<<16))
#define DV_DEN_START_END_FIELD1_dv_den_sta_field1_src(data)                          ((0x0FFF0000&(data))>>16)
#define DV_DEN_START_END_FIELD1_get_dv_den_sta_field1(data)                          ((0x0FFF0000&(data))>>16)
#define DV_DEN_START_END_FIELD1_dv_den_end_field1_shift                              (0)
#define DV_DEN_START_END_FIELD1_dv_den_end_field1_mask                               (0x00000FFF)
#define DV_DEN_START_END_FIELD1_dv_den_end_field1(data)                              (0x00000FFF&((data)<<0))
#define DV_DEN_START_END_FIELD1_dv_den_end_field1_src(data)                          ((0x00000FFF&(data))>>0)
#define DV_DEN_START_END_FIELD1_get_dv_den_end_field1(data)                          ((0x00000FFF&(data))>>0)


#define DV_TOTAL                                                                     0x18009818
#define DV_TOTAL_reg_addr                                                            "0xB8009818"
#define DV_TOTAL_reg                                                                 0xB8009818
#define set_DV_TOTAL_reg(data)   (*((volatile unsigned int*) DV_TOTAL_reg)=data)
#define get_DV_TOTAL_reg   (*((volatile unsigned int*) DV_TOTAL_reg))
#define DV_TOTAL_inst_adr                                                            "0x0006"
#define DV_TOTAL_inst                                                                0x0006
#define DV_TOTAL_dv_total_shift                                                      (0)
#define DV_TOTAL_dv_total_mask                                                       (0x00000FFF)
#define DV_TOTAL_dv_total(data)                                                      (0x00000FFF&((data)<<0))
#define DV_TOTAL_dv_total_src(data)                                                  ((0x00000FFF&(data))>>0)
#define DV_TOTAL_get_dv_total(data)                                                  ((0x00000FFF&(data))>>0)


#define DV_VS_START_END_FIELD1                                                       0x1800981c
#define DV_VS_START_END_FIELD1_reg_addr                                              "0xB800981C"
#define DV_VS_START_END_FIELD1_reg                                                   0xB800981C
#define set_DV_VS_START_END_FIELD1_reg(data)   (*((volatile unsigned int*) DV_VS_START_END_FIELD1_reg)=data)
#define get_DV_VS_START_END_FIELD1_reg   (*((volatile unsigned int*) DV_VS_START_END_FIELD1_reg))
#define DV_VS_START_END_FIELD1_inst_adr                                              "0x0007"
#define DV_VS_START_END_FIELD1_inst                                                  0x0007
#define DV_VS_START_END_FIELD1_dv_vs_sta_field1_shift                                (16)
#define DV_VS_START_END_FIELD1_dv_vs_sta_field1_mask                                 (0x0FFF0000)
#define DV_VS_START_END_FIELD1_dv_vs_sta_field1(data)                                (0x0FFF0000&((data)<<16))
#define DV_VS_START_END_FIELD1_dv_vs_sta_field1_src(data)                            ((0x0FFF0000&(data))>>16)
#define DV_VS_START_END_FIELD1_get_dv_vs_sta_field1(data)                            ((0x0FFF0000&(data))>>16)
#define DV_VS_START_END_FIELD1_dv_vs_end_field1_shift                                (0)
#define DV_VS_START_END_FIELD1_dv_vs_end_field1_mask                                 (0x00000FFF)
#define DV_VS_START_END_FIELD1_dv_vs_end_field1(data)                                (0x00000FFF&((data)<<0))
#define DV_VS_START_END_FIELD1_dv_vs_end_field1_src(data)                            ((0x00000FFF&(data))>>0)
#define DV_VS_START_END_FIELD1_get_dv_vs_end_field1(data)                            ((0x00000FFF&(data))>>0)


#define DH_VS_ADJ_FIELD1                                                             0x18009820
#define DH_VS_ADJ_FIELD1_reg_addr                                                    "0xB8009820"
#define DH_VS_ADJ_FIELD1_reg                                                         0xB8009820
#define set_DH_VS_ADJ_FIELD1_reg(data)   (*((volatile unsigned int*) DH_VS_ADJ_FIELD1_reg)=data)
#define get_DH_VS_ADJ_FIELD1_reg   (*((volatile unsigned int*) DH_VS_ADJ_FIELD1_reg))
#define DH_VS_ADJ_FIELD1_inst_adr                                                    "0x0008"
#define DH_VS_ADJ_FIELD1_inst                                                        0x0008
#define DH_VS_ADJ_FIELD1_dh_vs_adj_field1_shift                                      (0)
#define DH_VS_ADJ_FIELD1_dh_vs_adj_field1_mask                                       (0x00000FFF)
#define DH_VS_ADJ_FIELD1_dh_vs_adj_field1(data)                                      (0x00000FFF&((data)<<0))
#define DH_VS_ADJ_FIELD1_dh_vs_adj_field1_src(data)                                  ((0x00000FFF&(data))>>0)
#define DH_VS_ADJ_FIELD1_get_dh_vs_adj_field1(data)                                  ((0x00000FFF&(data))>>0)


#define DV_SYNC_INT                                                                  0x1800982c
#define DV_SYNC_INT_reg_addr                                                         "0xB800982C"
#define DV_SYNC_INT_reg                                                              0xB800982C
#define set_DV_SYNC_INT_reg(data)   (*((volatile unsigned int*) DV_SYNC_INT_reg)=data)
#define get_DV_SYNC_INT_reg   (*((volatile unsigned int*) DV_SYNC_INT_reg))
#define DV_SYNC_INT_inst_adr                                                         "0x000B"
#define DV_SYNC_INT_inst                                                             0x000B
#define DV_SYNC_INT_int_en_shift                                                     (31)
#define DV_SYNC_INT_int_en_mask                                                      (0x80000000)
#define DV_SYNC_INT_int_en(data)                                                     (0x80000000&((data)<<31))
#define DV_SYNC_INT_int_en_src(data)                                                 ((0x80000000&(data))>>31)
#define DV_SYNC_INT_get_int_en(data)                                                 ((0x80000000&(data))>>31)
#define DV_SYNC_INT_dv_sync_int_shift                                                (0)
#define DV_SYNC_INT_dv_sync_int_mask                                                 (0x00000FFF)
#define DV_SYNC_INT_dv_sync_int(data)                                                (0x00000FFF&((data)<<0))
#define DV_SYNC_INT_dv_sync_int_src(data)                                            ((0x00000FFF&(data))>>0)
#define DV_SYNC_INT_get_dv_sync_int(data)                                            ((0x00000FFF&(data))>>0)


#define PIF_CTRL0                                                                    0x18009844
#define PIF_CTRL0_reg_addr                                                           "0xB8009844"
#define PIF_CTRL0_reg                                                                0xB8009844
#define set_PIF_CTRL0_reg(data)   (*((volatile unsigned int*) PIF_CTRL0_reg)=data)
#define get_PIF_CTRL0_reg   (*((volatile unsigned int*) PIF_CTRL0_reg))
#define PIF_CTRL0_inst_adr                                                           "0x0011"
#define PIF_CTRL0_inst                                                               0x0011
#define PIF_CTRL0_neg_shift                                                          (0)
#define PIF_CTRL0_neg_mask                                                           (0x00000001)
#define PIF_CTRL0_neg(data)                                                          (0x00000001&((data)<<0))
#define PIF_CTRL0_neg_src(data)                                                      ((0x00000001&(data))>>0)
#define PIF_CTRL0_get_neg(data)                                                      ((0x00000001&(data))>>0)


#define LVDS_DBG                                                                     0x18009848
#define LVDS_DBG_reg_addr                                                            "0xB8009848"
#define LVDS_DBG_reg                                                                 0xB8009848
#define set_LVDS_DBG_reg(data)   (*((volatile unsigned int*) LVDS_DBG_reg)=data)
#define get_LVDS_DBG_reg   (*((volatile unsigned int*) LVDS_DBG_reg))
#define LVDS_DBG_inst_adr                                                            "0x0012"
#define LVDS_DBG_inst                                                                0x0012
#define LVDS_DBG_lvds_dbg_sel1_shift                                                 (8)
#define LVDS_DBG_lvds_dbg_sel1_mask                                                  (0x00007F00)
#define LVDS_DBG_lvds_dbg_sel1(data)                                                 (0x00007F00&((data)<<8))
#define LVDS_DBG_lvds_dbg_sel1_src(data)                                             ((0x00007F00&(data))>>8)
#define LVDS_DBG_get_lvds_dbg_sel1(data)                                             ((0x00007F00&(data))>>8)
#define LVDS_DBG_lvds_dbg_sel0_shift                                                 (1)
#define LVDS_DBG_lvds_dbg_sel0_mask                                                  (0x000000FE)
#define LVDS_DBG_lvds_dbg_sel0(data)                                                 (0x000000FE&((data)<<1))
#define LVDS_DBG_lvds_dbg_sel0_src(data)                                             ((0x000000FE&(data))>>1)
#define LVDS_DBG_get_lvds_dbg_sel0(data)                                             ((0x000000FE&(data))>>1)
#define LVDS_DBG_lvds_dbg_enable_shift                                               (0)
#define LVDS_DBG_lvds_dbg_enable_mask                                                (0x00000001)
#define LVDS_DBG_lvds_dbg_enable(data)                                               (0x00000001&((data)<<0))
#define LVDS_DBG_lvds_dbg_enable_src(data)                                           ((0x00000001&(data))>>0)
#define LVDS_DBG_get_lvds_dbg_enable(data)                                           ((0x00000001&(data))>>0)


#endif
