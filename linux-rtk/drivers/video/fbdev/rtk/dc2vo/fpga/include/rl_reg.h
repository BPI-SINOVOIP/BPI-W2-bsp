/**************************************************************
// Spec Version                  : 0.2
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2012/6/22 11:40:34
***************************************************************/


#ifndef _RL_REG_H_INCLUDED_
#define _RL_REG_H_INCLUDED_
#ifdef  _RL_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     disppic_h:13;
unsigned int     reserved_1:1;
unsigned int     disppic_w:14;
unsigned int     Cur_RANGEREDFRM:1;
}RL_RLCNTL;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     write_enable3:1;
unsigned int     rmem_wptr_rst:1;
unsigned int     write_enable2:1;
unsigned int     ldmc_bypass:1;
unsigned int     pred_enable:1;
unsigned int     ldmc_enable:1;
unsigned int     write_enable1:1;
unsigned int     manual_thresh_ena:1;
unsigned int     RM_threshold:6;
}RL_RLCNTL2;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     PicType:3;
unsigned int     reserved_1:3;
unsigned int     First_mb:1;
unsigned int     reserved_2:3;
unsigned int     Cur_mb_x:9;
unsigned int     Cur_mb_y:8;
}RL_CCPAR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     mb_field_decoding_flag:1;
unsigned int     Mb_partition:9;
}RL_H264CCPAR;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     IntraMB_flag:1;
unsigned int     Intra_flag:5;
unsigned int     SubMB_partition:12;
unsigned int     mvtype:2;
unsigned int     FIELDTX:1;
unsigned int     OVERFLAG:1;
}RL_VC1CCPAR;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     Chroma_predict_part0:2;
unsigned int     Chroma_predict_part1:2;
unsigned int     Chroma_predict_part2:2;
unsigned int     Chroma_predict_part3:2;
unsigned int     Inter_predict_part0:2;
unsigned int     Inter_predict_part1:2;
unsigned int     Inter_predict_part2:2;
unsigned int     Inter_predict_part3:2;
}RL_POPAR;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ref_RANGEREDFRM:1;
unsigned int     bottom_field_flag:1;
unsigned int     lu_addr_index:7;
unsigned int     ch_addr_index:7;
}RL_L0REFDMA;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ref_RANGEREDFRM:1;
unsigned int     bottom_field_flag:1;
unsigned int     lu_addr_index:7;
unsigned int     ch_addr_index:7;
}RL_L1REFDMA;

typedef struct 
{
unsigned int     write_enable3:1;
unsigned int     Trigger_status:1;
unsigned int     Zero_w_lr:2;
unsigned int     write_enable2:1;
unsigned int     Trigger_select:4;
unsigned int     reserved_0:2;
unsigned int     Trigger_cond_mb_x:9;
unsigned int     Trigger_cond_mb_y:8;
unsigned int     write_enable1:1;
unsigned int     Debug_port_sel:3;
}RL_DBG_SEL;

typedef struct 
{
unsigned int     Tbl_cnt:16;
unsigned int     Trigger_tbl_cnt:16;
}RL_DBG_STS0;

typedef struct 
{
unsigned int     DBG_STS:32;
}RL_DBG_STS1;

typedef struct 
{
unsigned int     DBG_STS:32;
}RL_DBG_STS2;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     Intr:1;
unsigned int     Value:28;
}RL_INTR_THRES;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     MVBUF_write_address:7;
}RL_MVBUF_WADD;

typedef struct 
{
unsigned int     MVBUF_read_write_data:32;
}RL_MVBUF_DATA;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     MVBUF_read_address:7;
}RL_MVBUF_RADD;

typedef struct 
{
unsigned int     write_enable3:1;
unsigned int     MVBUF_hdr:7;
unsigned int     reserved_0:3;
unsigned int     write_enable2:1;
unsigned int     MVBUF_pred_rptr:8;
unsigned int     reserved_1:3;
unsigned int     write_enable1:1;
unsigned int     MVBUF_mvd_wptr:8;
}RL_MVBUF_STS0;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     write_enable1:1;
unsigned int     MVBUF_rl_rptr:8;
}RL_MVBUF_STS1;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     write_enable2:1;
unsigned int     Vg_en:2;
unsigned int     write_enable1:1;
unsigned int     Ref_pic_cnt:1;
}RL_CACHE_SET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     Cah_en:1;
}RL_CACHE_EN;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     Cah_inv:1;
}RL_CACHE_INV;

typedef struct 
{
unsigned int     Cah_pindx0_LumL0:8;
unsigned int     Cah_pindx1_LumL1:8;
unsigned int     Cah_pindx2_ChrL0:8;
unsigned int     Cah_pindx3_ChrL1:8;
}RL_CAH_PINDX;

#endif

#define RL_RLCNTL                                                                    0x1800EC00
#define RL_RLCNTL_reg_addr                                                           "0xB800EC00"
#define RL_RLCNTL_reg                                                                0xB800EC00
#define set_RL_RLCNTL_reg(data)   (*((volatile unsigned int*) RL_RLCNTL_reg)=data)
#define get_RL_RLCNTL_reg   (*((volatile unsigned int*) RL_RLCNTL_reg))
#define RL_RLCNTL_inst_adr                                                           "0x0000"
#define RL_RLCNTL_inst                                                               0x0000
#define RL_RLCNTL_disppic_h_shift                                                    (16)
#define RL_RLCNTL_disppic_h_mask                                                     (0x1FFF0000)
#define RL_RLCNTL_disppic_h(data)                                                    (0x1FFF0000&((data)<<16))
#define RL_RLCNTL_disppic_h_src(data)                                                ((0x1FFF0000&(data))>>16)
#define RL_RLCNTL_get_disppic_h(data)                                                ((0x1FFF0000&(data))>>16)
#define RL_RLCNTL_disppic_w_shift                                                    (1)
#define RL_RLCNTL_disppic_w_mask                                                     (0x00007FFE)
#define RL_RLCNTL_disppic_w(data)                                                    (0x00007FFE&((data)<<1))
#define RL_RLCNTL_disppic_w_src(data)                                                ((0x00007FFE&(data))>>1)
#define RL_RLCNTL_get_disppic_w(data)                                                ((0x00007FFE&(data))>>1)
#define RL_RLCNTL_Cur_RANGEREDFRM_shift                                              (0)
#define RL_RLCNTL_Cur_RANGEREDFRM_mask                                               (0x00000001)
#define RL_RLCNTL_Cur_RANGEREDFRM(data)                                              (0x00000001&((data)<<0))
#define RL_RLCNTL_Cur_RANGEREDFRM_src(data)                                          ((0x00000001&(data))>>0)
#define RL_RLCNTL_get_Cur_RANGEREDFRM(data)                                          ((0x00000001&(data))>>0)


#define RL_RLCNTL2                                                                   0x1800EC04
#define RL_RLCNTL2_reg_addr                                                          "0xB800EC04"
#define RL_RLCNTL2_reg                                                               0xB800EC04
#define set_RL_RLCNTL2_reg(data)   (*((volatile unsigned int*) RL_RLCNTL2_reg)=data)
#define get_RL_RLCNTL2_reg   (*((volatile unsigned int*) RL_RLCNTL2_reg))
#define RL_RLCNTL2_inst_adr                                                          "0x0001"
#define RL_RLCNTL2_inst                                                              0x0001
#define RL_RLCNTL2_write_enable3_shift                                               (13)
#define RL_RLCNTL2_write_enable3_mask                                                (0x00002000)
#define RL_RLCNTL2_write_enable3(data)                                               (0x00002000&((data)<<13))
#define RL_RLCNTL2_write_enable3_src(data)                                           ((0x00002000&(data))>>13)
#define RL_RLCNTL2_get_write_enable3(data)                                           ((0x00002000&(data))>>13)
#define RL_RLCNTL2_rmem_wptr_rst_shift                                               (12)
#define RL_RLCNTL2_rmem_wptr_rst_mask                                                (0x00001000)
#define RL_RLCNTL2_rmem_wptr_rst(data)                                               (0x00001000&((data)<<12))
#define RL_RLCNTL2_rmem_wptr_rst_src(data)                                           ((0x00001000&(data))>>12)
#define RL_RLCNTL2_get_rmem_wptr_rst(data)                                           ((0x00001000&(data))>>12)
#define RL_RLCNTL2_write_enable2_shift                                               (11)
#define RL_RLCNTL2_write_enable2_mask                                                (0x00000800)
#define RL_RLCNTL2_write_enable2(data)                                               (0x00000800&((data)<<11))
#define RL_RLCNTL2_write_enable2_src(data)                                           ((0x00000800&(data))>>11)
#define RL_RLCNTL2_get_write_enable2(data)                                           ((0x00000800&(data))>>11)
#define RL_RLCNTL2_ldmc_bypass_shift                                                 (10)
#define RL_RLCNTL2_ldmc_bypass_mask                                                  (0x00000400)
#define RL_RLCNTL2_ldmc_bypass(data)                                                 (0x00000400&((data)<<10))
#define RL_RLCNTL2_ldmc_bypass_src(data)                                             ((0x00000400&(data))>>10)
#define RL_RLCNTL2_get_ldmc_bypass(data)                                             ((0x00000400&(data))>>10)
#define RL_RLCNTL2_pred_enable_shift                                                 (9)
#define RL_RLCNTL2_pred_enable_mask                                                  (0x00000200)
#define RL_RLCNTL2_pred_enable(data)                                                 (0x00000200&((data)<<9))
#define RL_RLCNTL2_pred_enable_src(data)                                             ((0x00000200&(data))>>9)
#define RL_RLCNTL2_get_pred_enable(data)                                             ((0x00000200&(data))>>9)
#define RL_RLCNTL2_ldmc_enable_shift                                                 (8)
#define RL_RLCNTL2_ldmc_enable_mask                                                  (0x00000100)
#define RL_RLCNTL2_ldmc_enable(data)                                                 (0x00000100&((data)<<8))
#define RL_RLCNTL2_ldmc_enable_src(data)                                             ((0x00000100&(data))>>8)
#define RL_RLCNTL2_get_ldmc_enable(data)                                             ((0x00000100&(data))>>8)
#define RL_RLCNTL2_write_enable1_shift                                               (7)
#define RL_RLCNTL2_write_enable1_mask                                                (0x00000080)
#define RL_RLCNTL2_write_enable1(data)                                               (0x00000080&((data)<<7))
#define RL_RLCNTL2_write_enable1_src(data)                                           ((0x00000080&(data))>>7)
#define RL_RLCNTL2_get_write_enable1(data)                                           ((0x00000080&(data))>>7)
#define RL_RLCNTL2_manual_thresh_ena_shift                                           (6)
#define RL_RLCNTL2_manual_thresh_ena_mask                                            (0x00000040)
#define RL_RLCNTL2_manual_thresh_ena(data)                                           (0x00000040&((data)<<6))
#define RL_RLCNTL2_manual_thresh_ena_src(data)                                       ((0x00000040&(data))>>6)
#define RL_RLCNTL2_get_manual_thresh_ena(data)                                       ((0x00000040&(data))>>6)
#define RL_RLCNTL2_RM_threshold_shift                                                (0)
#define RL_RLCNTL2_RM_threshold_mask                                                 (0x0000003F)
#define RL_RLCNTL2_RM_threshold(data)                                                (0x0000003F&((data)<<0))
#define RL_RLCNTL2_RM_threshold_src(data)                                            ((0x0000003F&(data))>>0)
#define RL_RLCNTL2_get_RM_threshold(data)                                            ((0x0000003F&(data))>>0)


#define RL_CCPAR                                                                     0x1800EC08
#define RL_CCPAR_reg_addr                                                            "0xB800EC08"
#define RL_CCPAR_reg                                                                 0xB800EC08
#define set_RL_CCPAR_reg(data)   (*((volatile unsigned int*) RL_CCPAR_reg)=data)
#define get_RL_CCPAR_reg   (*((volatile unsigned int*) RL_CCPAR_reg))
#define RL_CCPAR_inst_adr                                                            "0x0002"
#define RL_CCPAR_inst                                                                0x0002
#define RL_CCPAR_PicType_shift                                                       (24)
#define RL_CCPAR_PicType_mask                                                        (0x07000000)
#define RL_CCPAR_PicType(data)                                                       (0x07000000&((data)<<24))
#define RL_CCPAR_PicType_src(data)                                                   ((0x07000000&(data))>>24)
#define RL_CCPAR_get_PicType(data)                                                   ((0x07000000&(data))>>24)
#define RL_CCPAR_First_mb_shift                                                      (20)
#define RL_CCPAR_First_mb_mask                                                       (0x00100000)
#define RL_CCPAR_First_mb(data)                                                      (0x00100000&((data)<<20))
#define RL_CCPAR_First_mb_src(data)                                                  ((0x00100000&(data))>>20)
#define RL_CCPAR_get_First_mb(data)                                                  ((0x00100000&(data))>>20)
#define RL_CCPAR_Cur_mb_x_shift                                                      (8)
#define RL_CCPAR_Cur_mb_x_mask                                                       (0x0001FF00)
#define RL_CCPAR_Cur_mb_x(data)                                                      (0x0001FF00&((data)<<8))
#define RL_CCPAR_Cur_mb_x_src(data)                                                  ((0x0001FF00&(data))>>8)
#define RL_CCPAR_get_Cur_mb_x(data)                                                  ((0x0001FF00&(data))>>8)
#define RL_CCPAR_Cur_mb_y_shift                                                      (0)
#define RL_CCPAR_Cur_mb_y_mask                                                       (0x000000FF)
#define RL_CCPAR_Cur_mb_y(data)                                                      (0x000000FF&((data)<<0))
#define RL_CCPAR_Cur_mb_y_src(data)                                                  ((0x000000FF&(data))>>0)
#define RL_CCPAR_get_Cur_mb_y(data)                                                  ((0x000000FF&(data))>>0)


#define RL_H264CCPAR                                                                 0x1800EC0C
#define RL_H264CCPAR_reg_addr                                                        "0xB800EC0C"
#define RL_H264CCPAR_reg                                                             0xB800EC0C
#define set_RL_H264CCPAR_reg(data)   (*((volatile unsigned int*) RL_H264CCPAR_reg)=data)
#define get_RL_H264CCPAR_reg   (*((volatile unsigned int*) RL_H264CCPAR_reg))
#define RL_H264CCPAR_inst_adr                                                        "0x0003"
#define RL_H264CCPAR_inst                                                            0x0003
#define RL_H264CCPAR_mb_field_decoding_flag_shift                                    (9)
#define RL_H264CCPAR_mb_field_decoding_flag_mask                                     (0x00000200)
#define RL_H264CCPAR_mb_field_decoding_flag(data)                                    (0x00000200&((data)<<9))
#define RL_H264CCPAR_mb_field_decoding_flag_src(data)                                ((0x00000200&(data))>>9)
#define RL_H264CCPAR_get_mb_field_decoding_flag(data)                                ((0x00000200&(data))>>9)
#define RL_H264CCPAR_Mb_partition_shift                                              (0)
#define RL_H264CCPAR_Mb_partition_mask                                               (0x000001FF)
#define RL_H264CCPAR_Mb_partition(data)                                              (0x000001FF&((data)<<0))
#define RL_H264CCPAR_Mb_partition_src(data)                                          ((0x000001FF&(data))>>0)
#define RL_H264CCPAR_get_Mb_partition(data)                                          ((0x000001FF&(data))>>0)


#define RL_VC1CCPAR                                                                  0x1800EC10
#define RL_VC1CCPAR_reg_addr                                                         "0xB800EC10"
#define RL_VC1CCPAR_reg                                                              0xB800EC10
#define set_RL_VC1CCPAR_reg(data)   (*((volatile unsigned int*) RL_VC1CCPAR_reg)=data)
#define get_RL_VC1CCPAR_reg   (*((volatile unsigned int*) RL_VC1CCPAR_reg))
#define RL_VC1CCPAR_inst_adr                                                         "0x0004"
#define RL_VC1CCPAR_inst                                                             0x0004
#define RL_VC1CCPAR_IntraMB_flag_shift                                               (21)
#define RL_VC1CCPAR_IntraMB_flag_mask                                                (0x00200000)
#define RL_VC1CCPAR_IntraMB_flag(data)                                               (0x00200000&((data)<<21))
#define RL_VC1CCPAR_IntraMB_flag_src(data)                                           ((0x00200000&(data))>>21)
#define RL_VC1CCPAR_get_IntraMB_flag(data)                                           ((0x00200000&(data))>>21)
#define RL_VC1CCPAR_Intra_flag_shift                                                 (16)
#define RL_VC1CCPAR_Intra_flag_mask                                                  (0x001F0000)
#define RL_VC1CCPAR_Intra_flag(data)                                                 (0x001F0000&((data)<<16))
#define RL_VC1CCPAR_Intra_flag_src(data)                                             ((0x001F0000&(data))>>16)
#define RL_VC1CCPAR_get_Intra_flag(data)                                             ((0x001F0000&(data))>>16)
#define RL_VC1CCPAR_SubMB_partition_shift                                            (4)
#define RL_VC1CCPAR_SubMB_partition_mask                                             (0x0000FFF0)
#define RL_VC1CCPAR_SubMB_partition(data)                                            (0x0000FFF0&((data)<<4))
#define RL_VC1CCPAR_SubMB_partition_src(data)                                        ((0x0000FFF0&(data))>>4)
#define RL_VC1CCPAR_get_SubMB_partition(data)                                        ((0x0000FFF0&(data))>>4)
#define RL_VC1CCPAR_mvtype_shift                                                     (2)
#define RL_VC1CCPAR_mvtype_mask                                                      (0x0000000C)
#define RL_VC1CCPAR_mvtype(data)                                                     (0x0000000C&((data)<<2))
#define RL_VC1CCPAR_mvtype_src(data)                                                 ((0x0000000C&(data))>>2)
#define RL_VC1CCPAR_get_mvtype(data)                                                 ((0x0000000C&(data))>>2)
#define RL_VC1CCPAR_FIELDTX_shift                                                    (1)
#define RL_VC1CCPAR_FIELDTX_mask                                                     (0x00000002)
#define RL_VC1CCPAR_FIELDTX(data)                                                    (0x00000002&((data)<<1))
#define RL_VC1CCPAR_FIELDTX_src(data)                                                ((0x00000002&(data))>>1)
#define RL_VC1CCPAR_get_FIELDTX(data)                                                ((0x00000002&(data))>>1)
#define RL_VC1CCPAR_OVERFLAG_shift                                                   (0)
#define RL_VC1CCPAR_OVERFLAG_mask                                                    (0x00000001)
#define RL_VC1CCPAR_OVERFLAG(data)                                                   (0x00000001&((data)<<0))
#define RL_VC1CCPAR_OVERFLAG_src(data)                                               ((0x00000001&(data))>>0)
#define RL_VC1CCPAR_get_OVERFLAG(data)                                               ((0x00000001&(data))>>0)


#define RL_POPAR                                                                     0x1800EC14
#define RL_POPAR_reg_addr                                                            "0xB800EC14"
#define RL_POPAR_reg                                                                 0xB800EC14
#define set_RL_POPAR_reg(data)   (*((volatile unsigned int*) RL_POPAR_reg)=data)
#define get_RL_POPAR_reg   (*((volatile unsigned int*) RL_POPAR_reg))
#define RL_POPAR_inst_adr                                                            "0x0005"
#define RL_POPAR_inst                                                                0x0005
#define RL_POPAR_Chroma_predict_part0_shift                                          (14)
#define RL_POPAR_Chroma_predict_part0_mask                                           (0x0000C000)
#define RL_POPAR_Chroma_predict_part0(data)                                          (0x0000C000&((data)<<14))
#define RL_POPAR_Chroma_predict_part0_src(data)                                      ((0x0000C000&(data))>>14)
#define RL_POPAR_get_Chroma_predict_part0(data)                                      ((0x0000C000&(data))>>14)
#define RL_POPAR_Chroma_predict_part1_shift                                          (12)
#define RL_POPAR_Chroma_predict_part1_mask                                           (0x00003000)
#define RL_POPAR_Chroma_predict_part1(data)                                          (0x00003000&((data)<<12))
#define RL_POPAR_Chroma_predict_part1_src(data)                                      ((0x00003000&(data))>>12)
#define RL_POPAR_get_Chroma_predict_part1(data)                                      ((0x00003000&(data))>>12)
#define RL_POPAR_Chroma_predict_part2_shift                                          (10)
#define RL_POPAR_Chroma_predict_part2_mask                                           (0x00000C00)
#define RL_POPAR_Chroma_predict_part2(data)                                          (0x00000C00&((data)<<10))
#define RL_POPAR_Chroma_predict_part2_src(data)                                      ((0x00000C00&(data))>>10)
#define RL_POPAR_get_Chroma_predict_part2(data)                                      ((0x00000C00&(data))>>10)
#define RL_POPAR_Chroma_predict_part3_shift                                          (8)
#define RL_POPAR_Chroma_predict_part3_mask                                           (0x00000300)
#define RL_POPAR_Chroma_predict_part3(data)                                          (0x00000300&((data)<<8))
#define RL_POPAR_Chroma_predict_part3_src(data)                                      ((0x00000300&(data))>>8)
#define RL_POPAR_get_Chroma_predict_part3(data)                                      ((0x00000300&(data))>>8)
#define RL_POPAR_Inter_predict_part0_shift                                           (6)
#define RL_POPAR_Inter_predict_part0_mask                                            (0x000000C0)
#define RL_POPAR_Inter_predict_part0(data)                                           (0x000000C0&((data)<<6))
#define RL_POPAR_Inter_predict_part0_src(data)                                       ((0x000000C0&(data))>>6)
#define RL_POPAR_get_Inter_predict_part0(data)                                       ((0x000000C0&(data))>>6)
#define RL_POPAR_Inter_predict_part1_shift                                           (4)
#define RL_POPAR_Inter_predict_part1_mask                                            (0x00000030)
#define RL_POPAR_Inter_predict_part1(data)                                           (0x00000030&((data)<<4))
#define RL_POPAR_Inter_predict_part1_src(data)                                       ((0x00000030&(data))>>4)
#define RL_POPAR_get_Inter_predict_part1(data)                                       ((0x00000030&(data))>>4)
#define RL_POPAR_Inter_predict_part2_shift                                           (2)
#define RL_POPAR_Inter_predict_part2_mask                                            (0x0000000C)
#define RL_POPAR_Inter_predict_part2(data)                                           (0x0000000C&((data)<<2))
#define RL_POPAR_Inter_predict_part2_src(data)                                       ((0x0000000C&(data))>>2)
#define RL_POPAR_get_Inter_predict_part2(data)                                       ((0x0000000C&(data))>>2)
#define RL_POPAR_Inter_predict_part3_shift                                           (0)
#define RL_POPAR_Inter_predict_part3_mask                                            (0x00000003)
#define RL_POPAR_Inter_predict_part3(data)                                           (0x00000003&((data)<<0))
#define RL_POPAR_Inter_predict_part3_src(data)                                       ((0x00000003&(data))>>0)
#define RL_POPAR_get_Inter_predict_part3(data)                                       ((0x00000003&(data))>>0)


#define RL_L0REFDMA_0                                                                0x1800E500
#define RL_L0REFDMA_1                                                                0x1800E504
#define RL_L0REFDMA_2                                                                0x1800E508
#define RL_L0REFDMA_3                                                                0x1800E50C
#define RL_L0REFDMA_4                                                                0x1800E510
#define RL_L0REFDMA_5                                                                0x1800E514
#define RL_L0REFDMA_6                                                                0x1800E518
#define RL_L0REFDMA_7                                                                0x1800E51C
#define RL_L0REFDMA_8                                                                0x1800E520
#define RL_L0REFDMA_9                                                                0x1800E524
#define RL_L0REFDMA_10                                                                0x1800E528
#define RL_L0REFDMA_11                                                                0x1800E52C
#define RL_L0REFDMA_12                                                                0x1800E530
#define RL_L0REFDMA_13                                                                0x1800E534
#define RL_L0REFDMA_14                                                                0x1800E538
#define RL_L0REFDMA_15                                                                0x1800E53C
#define RL_L0REFDMA_16                                                                0x1800E540
#define RL_L0REFDMA_17                                                                0x1800E544
#define RL_L0REFDMA_18                                                                0x1800E548
#define RL_L0REFDMA_19                                                                0x1800E54C
#define RL_L0REFDMA_20                                                                0x1800E550
#define RL_L0REFDMA_21                                                                0x1800E554
#define RL_L0REFDMA_22                                                                0x1800E558
#define RL_L0REFDMA_23                                                                0x1800E55C
#define RL_L0REFDMA_24                                                                0x1800E560
#define RL_L0REFDMA_25                                                                0x1800E564
#define RL_L0REFDMA_26                                                                0x1800E568
#define RL_L0REFDMA_27                                                                0x1800E56C
#define RL_L0REFDMA_28                                                                0x1800E570
#define RL_L0REFDMA_29                                                                0x1800E574
#define RL_L0REFDMA_30                                                                0x1800E578
#define RL_L0REFDMA_31                                                                0x1800E57C
#define RL_L0REFDMA_0_reg_addr                                                       "0xB800E500"
#define RL_L0REFDMA_1_reg_addr                                                       "0xB800E504"
#define RL_L0REFDMA_2_reg_addr                                                       "0xB800E508"
#define RL_L0REFDMA_3_reg_addr                                                       "0xB800E50C"
#define RL_L0REFDMA_4_reg_addr                                                       "0xB800E510"
#define RL_L0REFDMA_5_reg_addr                                                       "0xB800E514"
#define RL_L0REFDMA_6_reg_addr                                                       "0xB800E518"
#define RL_L0REFDMA_7_reg_addr                                                       "0xB800E51C"
#define RL_L0REFDMA_8_reg_addr                                                       "0xB800E520"
#define RL_L0REFDMA_9_reg_addr                                                       "0xB800E524"
#define RL_L0REFDMA_10_reg_addr                                                       "0xB800E528"
#define RL_L0REFDMA_11_reg_addr                                                       "0xB800E52C"
#define RL_L0REFDMA_12_reg_addr                                                       "0xB800E530"
#define RL_L0REFDMA_13_reg_addr                                                       "0xB800E534"
#define RL_L0REFDMA_14_reg_addr                                                       "0xB800E538"
#define RL_L0REFDMA_15_reg_addr                                                       "0xB800E53C"
#define RL_L0REFDMA_16_reg_addr                                                       "0xB800E540"
#define RL_L0REFDMA_17_reg_addr                                                       "0xB800E544"
#define RL_L0REFDMA_18_reg_addr                                                       "0xB800E548"
#define RL_L0REFDMA_19_reg_addr                                                       "0xB800E54C"
#define RL_L0REFDMA_20_reg_addr                                                       "0xB800E550"
#define RL_L0REFDMA_21_reg_addr                                                       "0xB800E554"
#define RL_L0REFDMA_22_reg_addr                                                       "0xB800E558"
#define RL_L0REFDMA_23_reg_addr                                                       "0xB800E55C"
#define RL_L0REFDMA_24_reg_addr                                                       "0xB800E560"
#define RL_L0REFDMA_25_reg_addr                                                       "0xB800E564"
#define RL_L0REFDMA_26_reg_addr                                                       "0xB800E568"
#define RL_L0REFDMA_27_reg_addr                                                       "0xB800E56C"
#define RL_L0REFDMA_28_reg_addr                                                       "0xB800E570"
#define RL_L0REFDMA_29_reg_addr                                                       "0xB800E574"
#define RL_L0REFDMA_30_reg_addr                                                       "0xB800E578"
#define RL_L0REFDMA_31_reg_addr                                                       "0xB800E57C"
#define RL_L0REFDMA_0_reg                                                            0xB800E500
#define RL_L0REFDMA_1_reg                                                            0xB800E504
#define RL_L0REFDMA_2_reg                                                            0xB800E508
#define RL_L0REFDMA_3_reg                                                            0xB800E50C
#define RL_L0REFDMA_4_reg                                                            0xB800E510
#define RL_L0REFDMA_5_reg                                                            0xB800E514
#define RL_L0REFDMA_6_reg                                                            0xB800E518
#define RL_L0REFDMA_7_reg                                                            0xB800E51C
#define RL_L0REFDMA_8_reg                                                            0xB800E520
#define RL_L0REFDMA_9_reg                                                            0xB800E524
#define RL_L0REFDMA_10_reg                                                            0xB800E528
#define RL_L0REFDMA_11_reg                                                            0xB800E52C
#define RL_L0REFDMA_12_reg                                                            0xB800E530
#define RL_L0REFDMA_13_reg                                                            0xB800E534
#define RL_L0REFDMA_14_reg                                                            0xB800E538
#define RL_L0REFDMA_15_reg                                                            0xB800E53C
#define RL_L0REFDMA_16_reg                                                            0xB800E540
#define RL_L0REFDMA_17_reg                                                            0xB800E544
#define RL_L0REFDMA_18_reg                                                            0xB800E548
#define RL_L0REFDMA_19_reg                                                            0xB800E54C
#define RL_L0REFDMA_20_reg                                                            0xB800E550
#define RL_L0REFDMA_21_reg                                                            0xB800E554
#define RL_L0REFDMA_22_reg                                                            0xB800E558
#define RL_L0REFDMA_23_reg                                                            0xB800E55C
#define RL_L0REFDMA_24_reg                                                            0xB800E560
#define RL_L0REFDMA_25_reg                                                            0xB800E564
#define RL_L0REFDMA_26_reg                                                            0xB800E568
#define RL_L0REFDMA_27_reg                                                            0xB800E56C
#define RL_L0REFDMA_28_reg                                                            0xB800E570
#define RL_L0REFDMA_29_reg                                                            0xB800E574
#define RL_L0REFDMA_30_reg                                                            0xB800E578
#define RL_L0REFDMA_31_reg                                                            0xB800E57C
#define set_RL_L0REFDMA_0_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_0_reg)=data)
#define set_RL_L0REFDMA_1_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_1_reg)=data)
#define set_RL_L0REFDMA_2_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_2_reg)=data)
#define set_RL_L0REFDMA_3_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_3_reg)=data)
#define set_RL_L0REFDMA_4_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_4_reg)=data)
#define set_RL_L0REFDMA_5_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_5_reg)=data)
#define set_RL_L0REFDMA_6_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_6_reg)=data)
#define set_RL_L0REFDMA_7_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_7_reg)=data)
#define set_RL_L0REFDMA_8_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_8_reg)=data)
#define set_RL_L0REFDMA_9_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_9_reg)=data)
#define set_RL_L0REFDMA_10_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_10_reg)=data)
#define set_RL_L0REFDMA_11_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_11_reg)=data)
#define set_RL_L0REFDMA_12_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_12_reg)=data)
#define set_RL_L0REFDMA_13_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_13_reg)=data)
#define set_RL_L0REFDMA_14_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_14_reg)=data)
#define set_RL_L0REFDMA_15_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_15_reg)=data)
#define set_RL_L0REFDMA_16_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_16_reg)=data)
#define set_RL_L0REFDMA_17_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_17_reg)=data)
#define set_RL_L0REFDMA_18_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_18_reg)=data)
#define set_RL_L0REFDMA_19_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_19_reg)=data)
#define set_RL_L0REFDMA_20_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_20_reg)=data)
#define set_RL_L0REFDMA_21_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_21_reg)=data)
#define set_RL_L0REFDMA_22_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_22_reg)=data)
#define set_RL_L0REFDMA_23_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_23_reg)=data)
#define set_RL_L0REFDMA_24_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_24_reg)=data)
#define set_RL_L0REFDMA_25_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_25_reg)=data)
#define set_RL_L0REFDMA_26_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_26_reg)=data)
#define set_RL_L0REFDMA_27_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_27_reg)=data)
#define set_RL_L0REFDMA_28_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_28_reg)=data)
#define set_RL_L0REFDMA_29_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_29_reg)=data)
#define set_RL_L0REFDMA_30_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_30_reg)=data)
#define set_RL_L0REFDMA_31_reg(data)   (*((volatile unsigned int*) RL_L0REFDMA_31_reg)=data)
#define get_RL_L0REFDMA_0_reg   (*((volatile unsigned int*) RL_L0REFDMA_0_reg))
#define get_RL_L0REFDMA_1_reg   (*((volatile unsigned int*) RL_L0REFDMA_1_reg))
#define get_RL_L0REFDMA_2_reg   (*((volatile unsigned int*) RL_L0REFDMA_2_reg))
#define get_RL_L0REFDMA_3_reg   (*((volatile unsigned int*) RL_L0REFDMA_3_reg))
#define get_RL_L0REFDMA_4_reg   (*((volatile unsigned int*) RL_L0REFDMA_4_reg))
#define get_RL_L0REFDMA_5_reg   (*((volatile unsigned int*) RL_L0REFDMA_5_reg))
#define get_RL_L0REFDMA_6_reg   (*((volatile unsigned int*) RL_L0REFDMA_6_reg))
#define get_RL_L0REFDMA_7_reg   (*((volatile unsigned int*) RL_L0REFDMA_7_reg))
#define get_RL_L0REFDMA_8_reg   (*((volatile unsigned int*) RL_L0REFDMA_8_reg))
#define get_RL_L0REFDMA_9_reg   (*((volatile unsigned int*) RL_L0REFDMA_9_reg))
#define get_RL_L0REFDMA_10_reg   (*((volatile unsigned int*) RL_L0REFDMA_10_reg))
#define get_RL_L0REFDMA_11_reg   (*((volatile unsigned int*) RL_L0REFDMA_11_reg))
#define get_RL_L0REFDMA_12_reg   (*((volatile unsigned int*) RL_L0REFDMA_12_reg))
#define get_RL_L0REFDMA_13_reg   (*((volatile unsigned int*) RL_L0REFDMA_13_reg))
#define get_RL_L0REFDMA_14_reg   (*((volatile unsigned int*) RL_L0REFDMA_14_reg))
#define get_RL_L0REFDMA_15_reg   (*((volatile unsigned int*) RL_L0REFDMA_15_reg))
#define get_RL_L0REFDMA_16_reg   (*((volatile unsigned int*) RL_L0REFDMA_16_reg))
#define get_RL_L0REFDMA_17_reg   (*((volatile unsigned int*) RL_L0REFDMA_17_reg))
#define get_RL_L0REFDMA_18_reg   (*((volatile unsigned int*) RL_L0REFDMA_18_reg))
#define get_RL_L0REFDMA_19_reg   (*((volatile unsigned int*) RL_L0REFDMA_19_reg))
#define get_RL_L0REFDMA_20_reg   (*((volatile unsigned int*) RL_L0REFDMA_20_reg))
#define get_RL_L0REFDMA_21_reg   (*((volatile unsigned int*) RL_L0REFDMA_21_reg))
#define get_RL_L0REFDMA_22_reg   (*((volatile unsigned int*) RL_L0REFDMA_22_reg))
#define get_RL_L0REFDMA_23_reg   (*((volatile unsigned int*) RL_L0REFDMA_23_reg))
#define get_RL_L0REFDMA_24_reg   (*((volatile unsigned int*) RL_L0REFDMA_24_reg))
#define get_RL_L0REFDMA_25_reg   (*((volatile unsigned int*) RL_L0REFDMA_25_reg))
#define get_RL_L0REFDMA_26_reg   (*((volatile unsigned int*) RL_L0REFDMA_26_reg))
#define get_RL_L0REFDMA_27_reg   (*((volatile unsigned int*) RL_L0REFDMA_27_reg))
#define get_RL_L0REFDMA_28_reg   (*((volatile unsigned int*) RL_L0REFDMA_28_reg))
#define get_RL_L0REFDMA_29_reg   (*((volatile unsigned int*) RL_L0REFDMA_29_reg))
#define get_RL_L0REFDMA_30_reg   (*((volatile unsigned int*) RL_L0REFDMA_30_reg))
#define get_RL_L0REFDMA_31_reg   (*((volatile unsigned int*) RL_L0REFDMA_31_reg))
#define RL_L0REFDMA_0_inst_adr                                                       "0x0040"
#define RL_L0REFDMA_1_inst_adr                                                       "0x0041"
#define RL_L0REFDMA_2_inst_adr                                                       "0x0042"
#define RL_L0REFDMA_3_inst_adr                                                       "0x0043"
#define RL_L0REFDMA_4_inst_adr                                                       "0x0044"
#define RL_L0REFDMA_5_inst_adr                                                       "0x0045"
#define RL_L0REFDMA_6_inst_adr                                                       "0x0046"
#define RL_L0REFDMA_7_inst_adr                                                       "0x0047"
#define RL_L0REFDMA_8_inst_adr                                                       "0x0048"
#define RL_L0REFDMA_9_inst_adr                                                       "0x0049"
#define RL_L0REFDMA_10_inst_adr                                                       "0x004A"
#define RL_L0REFDMA_11_inst_adr                                                       "0x004B"
#define RL_L0REFDMA_12_inst_adr                                                       "0x004C"
#define RL_L0REFDMA_13_inst_adr                                                       "0x004D"
#define RL_L0REFDMA_14_inst_adr                                                       "0x004E"
#define RL_L0REFDMA_15_inst_adr                                                       "0x004F"
#define RL_L0REFDMA_16_inst_adr                                                       "0x0050"
#define RL_L0REFDMA_17_inst_adr                                                       "0x0051"
#define RL_L0REFDMA_18_inst_adr                                                       "0x0052"
#define RL_L0REFDMA_19_inst_adr                                                       "0x0053"
#define RL_L0REFDMA_20_inst_adr                                                       "0x0054"
#define RL_L0REFDMA_21_inst_adr                                                       "0x0055"
#define RL_L0REFDMA_22_inst_adr                                                       "0x0056"
#define RL_L0REFDMA_23_inst_adr                                                       "0x0057"
#define RL_L0REFDMA_24_inst_adr                                                       "0x0058"
#define RL_L0REFDMA_25_inst_adr                                                       "0x0059"
#define RL_L0REFDMA_26_inst_adr                                                       "0x005A"
#define RL_L0REFDMA_27_inst_adr                                                       "0x005B"
#define RL_L0REFDMA_28_inst_adr                                                       "0x005C"
#define RL_L0REFDMA_29_inst_adr                                                       "0x005D"
#define RL_L0REFDMA_30_inst_adr                                                       "0x005E"
#define RL_L0REFDMA_31_inst_adr                                                       "0x005F"
#define RL_L0REFDMA_0_inst                                                           0x0040
#define RL_L0REFDMA_1_inst                                                           0x0041
#define RL_L0REFDMA_2_inst                                                           0x0042
#define RL_L0REFDMA_3_inst                                                           0x0043
#define RL_L0REFDMA_4_inst                                                           0x0044
#define RL_L0REFDMA_5_inst                                                           0x0045
#define RL_L0REFDMA_6_inst                                                           0x0046
#define RL_L0REFDMA_7_inst                                                           0x0047
#define RL_L0REFDMA_8_inst                                                           0x0048
#define RL_L0REFDMA_9_inst                                                           0x0049
#define RL_L0REFDMA_10_inst                                                           0x004A
#define RL_L0REFDMA_11_inst                                                           0x004B
#define RL_L0REFDMA_12_inst                                                           0x004C
#define RL_L0REFDMA_13_inst                                                           0x004D
#define RL_L0REFDMA_14_inst                                                           0x004E
#define RL_L0REFDMA_15_inst                                                           0x004F
#define RL_L0REFDMA_16_inst                                                           0x0050
#define RL_L0REFDMA_17_inst                                                           0x0051
#define RL_L0REFDMA_18_inst                                                           0x0052
#define RL_L0REFDMA_19_inst                                                           0x0053
#define RL_L0REFDMA_20_inst                                                           0x0054
#define RL_L0REFDMA_21_inst                                                           0x0055
#define RL_L0REFDMA_22_inst                                                           0x0056
#define RL_L0REFDMA_23_inst                                                           0x0057
#define RL_L0REFDMA_24_inst                                                           0x0058
#define RL_L0REFDMA_25_inst                                                           0x0059
#define RL_L0REFDMA_26_inst                                                           0x005A
#define RL_L0REFDMA_27_inst                                                           0x005B
#define RL_L0REFDMA_28_inst                                                           0x005C
#define RL_L0REFDMA_29_inst                                                           0x005D
#define RL_L0REFDMA_30_inst                                                           0x005E
#define RL_L0REFDMA_31_inst                                                           0x005F
#define RL_L0REFDMA_ref_RANGEREDFRM_shift                                            (15)
#define RL_L0REFDMA_ref_RANGEREDFRM_mask                                             (0x00008000)
#define RL_L0REFDMA_ref_RANGEREDFRM(data)                                            (0x00008000&((data)<<15))
#define RL_L0REFDMA_ref_RANGEREDFRM_src(data)                                        ((0x00008000&(data))>>15)
#define RL_L0REFDMA_get_ref_RANGEREDFRM(data)                                        ((0x00008000&(data))>>15)
#define RL_L0REFDMA_bottom_field_flag_shift                                          (14)
#define RL_L0REFDMA_bottom_field_flag_mask                                           (0x00004000)
#define RL_L0REFDMA_bottom_field_flag(data)                                          (0x00004000&((data)<<14))
#define RL_L0REFDMA_bottom_field_flag_src(data)                                      ((0x00004000&(data))>>14)
#define RL_L0REFDMA_get_bottom_field_flag(data)                                      ((0x00004000&(data))>>14)
#define RL_L0REFDMA_lu_addr_index_shift                                              (7)
#define RL_L0REFDMA_lu_addr_index_mask                                               (0x00003F80)
#define RL_L0REFDMA_lu_addr_index(data)                                              (0x00003F80&((data)<<7))
#define RL_L0REFDMA_lu_addr_index_src(data)                                          ((0x00003F80&(data))>>7)
#define RL_L0REFDMA_get_lu_addr_index(data)                                          ((0x00003F80&(data))>>7)
#define RL_L0REFDMA_ch_addr_index_shift                                              (0)
#define RL_L0REFDMA_ch_addr_index_mask                                               (0x0000007F)
#define RL_L0REFDMA_ch_addr_index(data)                                              (0x0000007F&((data)<<0))
#define RL_L0REFDMA_ch_addr_index_src(data)                                          ((0x0000007F&(data))>>0)
#define RL_L0REFDMA_get_ch_addr_index(data)                                          ((0x0000007F&(data))>>0)


#define RL_L1REFDMA_0                                                                0x1800E580
#define RL_L1REFDMA_1                                                                0x1800E584
#define RL_L1REFDMA_2                                                                0x1800E588
#define RL_L1REFDMA_3                                                                0x1800E58C
#define RL_L1REFDMA_4                                                                0x1800E590
#define RL_L1REFDMA_5                                                                0x1800E594
#define RL_L1REFDMA_6                                                                0x1800E598
#define RL_L1REFDMA_7                                                                0x1800E59C
#define RL_L1REFDMA_8                                                                0x1800E5A0
#define RL_L1REFDMA_9                                                                0x1800E5A4
#define RL_L1REFDMA_10                                                                0x1800E5A8
#define RL_L1REFDMA_11                                                                0x1800E5AC
#define RL_L1REFDMA_12                                                                0x1800E5B0
#define RL_L1REFDMA_13                                                                0x1800E5B4
#define RL_L1REFDMA_14                                                                0x1800E5B8
#define RL_L1REFDMA_15                                                                0x1800E5BC
#define RL_L1REFDMA_16                                                                0x1800E5C0
#define RL_L1REFDMA_17                                                                0x1800E5C4
#define RL_L1REFDMA_18                                                                0x1800E5C8
#define RL_L1REFDMA_19                                                                0x1800E5CC
#define RL_L1REFDMA_20                                                                0x1800E5D0
#define RL_L1REFDMA_21                                                                0x1800E5D4
#define RL_L1REFDMA_22                                                                0x1800E5D8
#define RL_L1REFDMA_23                                                                0x1800E5DC
#define RL_L1REFDMA_24                                                                0x1800E5E0
#define RL_L1REFDMA_25                                                                0x1800E5E4
#define RL_L1REFDMA_26                                                                0x1800E5E8
#define RL_L1REFDMA_27                                                                0x1800E5EC
#define RL_L1REFDMA_28                                                                0x1800E5F0
#define RL_L1REFDMA_29                                                                0x1800E5F4
#define RL_L1REFDMA_30                                                                0x1800E5F8
#define RL_L1REFDMA_31                                                                0x1800E5FC
#define RL_L1REFDMA_0_reg_addr                                                       "0xB800E580"
#define RL_L1REFDMA_1_reg_addr                                                       "0xB800E584"
#define RL_L1REFDMA_2_reg_addr                                                       "0xB800E588"
#define RL_L1REFDMA_3_reg_addr                                                       "0xB800E58C"
#define RL_L1REFDMA_4_reg_addr                                                       "0xB800E590"
#define RL_L1REFDMA_5_reg_addr                                                       "0xB800E594"
#define RL_L1REFDMA_6_reg_addr                                                       "0xB800E598"
#define RL_L1REFDMA_7_reg_addr                                                       "0xB800E59C"
#define RL_L1REFDMA_8_reg_addr                                                       "0xB800E5A0"
#define RL_L1REFDMA_9_reg_addr                                                       "0xB800E5A4"
#define RL_L1REFDMA_10_reg_addr                                                       "0xB800E5A8"
#define RL_L1REFDMA_11_reg_addr                                                       "0xB800E5AC"
#define RL_L1REFDMA_12_reg_addr                                                       "0xB800E5B0"
#define RL_L1REFDMA_13_reg_addr                                                       "0xB800E5B4"
#define RL_L1REFDMA_14_reg_addr                                                       "0xB800E5B8"
#define RL_L1REFDMA_15_reg_addr                                                       "0xB800E5BC"
#define RL_L1REFDMA_16_reg_addr                                                       "0xB800E5C0"
#define RL_L1REFDMA_17_reg_addr                                                       "0xB800E5C4"
#define RL_L1REFDMA_18_reg_addr                                                       "0xB800E5C8"
#define RL_L1REFDMA_19_reg_addr                                                       "0xB800E5CC"
#define RL_L1REFDMA_20_reg_addr                                                       "0xB800E5D0"
#define RL_L1REFDMA_21_reg_addr                                                       "0xB800E5D4"
#define RL_L1REFDMA_22_reg_addr                                                       "0xB800E5D8"
#define RL_L1REFDMA_23_reg_addr                                                       "0xB800E5DC"
#define RL_L1REFDMA_24_reg_addr                                                       "0xB800E5E0"
#define RL_L1REFDMA_25_reg_addr                                                       "0xB800E5E4"
#define RL_L1REFDMA_26_reg_addr                                                       "0xB800E5E8"
#define RL_L1REFDMA_27_reg_addr                                                       "0xB800E5EC"
#define RL_L1REFDMA_28_reg_addr                                                       "0xB800E5F0"
#define RL_L1REFDMA_29_reg_addr                                                       "0xB800E5F4"
#define RL_L1REFDMA_30_reg_addr                                                       "0xB800E5F8"
#define RL_L1REFDMA_31_reg_addr                                                       "0xB800E5FC"
#define RL_L1REFDMA_0_reg                                                            0xB800E580
#define RL_L1REFDMA_1_reg                                                            0xB800E584
#define RL_L1REFDMA_2_reg                                                            0xB800E588
#define RL_L1REFDMA_3_reg                                                            0xB800E58C
#define RL_L1REFDMA_4_reg                                                            0xB800E590
#define RL_L1REFDMA_5_reg                                                            0xB800E594
#define RL_L1REFDMA_6_reg                                                            0xB800E598
#define RL_L1REFDMA_7_reg                                                            0xB800E59C
#define RL_L1REFDMA_8_reg                                                            0xB800E5A0
#define RL_L1REFDMA_9_reg                                                            0xB800E5A4
#define RL_L1REFDMA_10_reg                                                            0xB800E5A8
#define RL_L1REFDMA_11_reg                                                            0xB800E5AC
#define RL_L1REFDMA_12_reg                                                            0xB800E5B0
#define RL_L1REFDMA_13_reg                                                            0xB800E5B4
#define RL_L1REFDMA_14_reg                                                            0xB800E5B8
#define RL_L1REFDMA_15_reg                                                            0xB800E5BC
#define RL_L1REFDMA_16_reg                                                            0xB800E5C0
#define RL_L1REFDMA_17_reg                                                            0xB800E5C4
#define RL_L1REFDMA_18_reg                                                            0xB800E5C8
#define RL_L1REFDMA_19_reg                                                            0xB800E5CC
#define RL_L1REFDMA_20_reg                                                            0xB800E5D0
#define RL_L1REFDMA_21_reg                                                            0xB800E5D4
#define RL_L1REFDMA_22_reg                                                            0xB800E5D8
#define RL_L1REFDMA_23_reg                                                            0xB800E5DC
#define RL_L1REFDMA_24_reg                                                            0xB800E5E0
#define RL_L1REFDMA_25_reg                                                            0xB800E5E4
#define RL_L1REFDMA_26_reg                                                            0xB800E5E8
#define RL_L1REFDMA_27_reg                                                            0xB800E5EC
#define RL_L1REFDMA_28_reg                                                            0xB800E5F0
#define RL_L1REFDMA_29_reg                                                            0xB800E5F4
#define RL_L1REFDMA_30_reg                                                            0xB800E5F8
#define RL_L1REFDMA_31_reg                                                            0xB800E5FC
#define set_RL_L1REFDMA_0_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_0_reg)=data)
#define set_RL_L1REFDMA_1_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_1_reg)=data)
#define set_RL_L1REFDMA_2_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_2_reg)=data)
#define set_RL_L1REFDMA_3_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_3_reg)=data)
#define set_RL_L1REFDMA_4_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_4_reg)=data)
#define set_RL_L1REFDMA_5_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_5_reg)=data)
#define set_RL_L1REFDMA_6_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_6_reg)=data)
#define set_RL_L1REFDMA_7_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_7_reg)=data)
#define set_RL_L1REFDMA_8_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_8_reg)=data)
#define set_RL_L1REFDMA_9_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_9_reg)=data)
#define set_RL_L1REFDMA_10_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_10_reg)=data)
#define set_RL_L1REFDMA_11_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_11_reg)=data)
#define set_RL_L1REFDMA_12_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_12_reg)=data)
#define set_RL_L1REFDMA_13_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_13_reg)=data)
#define set_RL_L1REFDMA_14_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_14_reg)=data)
#define set_RL_L1REFDMA_15_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_15_reg)=data)
#define set_RL_L1REFDMA_16_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_16_reg)=data)
#define set_RL_L1REFDMA_17_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_17_reg)=data)
#define set_RL_L1REFDMA_18_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_18_reg)=data)
#define set_RL_L1REFDMA_19_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_19_reg)=data)
#define set_RL_L1REFDMA_20_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_20_reg)=data)
#define set_RL_L1REFDMA_21_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_21_reg)=data)
#define set_RL_L1REFDMA_22_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_22_reg)=data)
#define set_RL_L1REFDMA_23_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_23_reg)=data)
#define set_RL_L1REFDMA_24_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_24_reg)=data)
#define set_RL_L1REFDMA_25_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_25_reg)=data)
#define set_RL_L1REFDMA_26_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_26_reg)=data)
#define set_RL_L1REFDMA_27_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_27_reg)=data)
#define set_RL_L1REFDMA_28_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_28_reg)=data)
#define set_RL_L1REFDMA_29_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_29_reg)=data)
#define set_RL_L1REFDMA_30_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_30_reg)=data)
#define set_RL_L1REFDMA_31_reg(data)   (*((volatile unsigned int*) RL_L1REFDMA_31_reg)=data)
#define get_RL_L1REFDMA_0_reg   (*((volatile unsigned int*) RL_L1REFDMA_0_reg))
#define get_RL_L1REFDMA_1_reg   (*((volatile unsigned int*) RL_L1REFDMA_1_reg))
#define get_RL_L1REFDMA_2_reg   (*((volatile unsigned int*) RL_L1REFDMA_2_reg))
#define get_RL_L1REFDMA_3_reg   (*((volatile unsigned int*) RL_L1REFDMA_3_reg))
#define get_RL_L1REFDMA_4_reg   (*((volatile unsigned int*) RL_L1REFDMA_4_reg))
#define get_RL_L1REFDMA_5_reg   (*((volatile unsigned int*) RL_L1REFDMA_5_reg))
#define get_RL_L1REFDMA_6_reg   (*((volatile unsigned int*) RL_L1REFDMA_6_reg))
#define get_RL_L1REFDMA_7_reg   (*((volatile unsigned int*) RL_L1REFDMA_7_reg))
#define get_RL_L1REFDMA_8_reg   (*((volatile unsigned int*) RL_L1REFDMA_8_reg))
#define get_RL_L1REFDMA_9_reg   (*((volatile unsigned int*) RL_L1REFDMA_9_reg))
#define get_RL_L1REFDMA_10_reg   (*((volatile unsigned int*) RL_L1REFDMA_10_reg))
#define get_RL_L1REFDMA_11_reg   (*((volatile unsigned int*) RL_L1REFDMA_11_reg))
#define get_RL_L1REFDMA_12_reg   (*((volatile unsigned int*) RL_L1REFDMA_12_reg))
#define get_RL_L1REFDMA_13_reg   (*((volatile unsigned int*) RL_L1REFDMA_13_reg))
#define get_RL_L1REFDMA_14_reg   (*((volatile unsigned int*) RL_L1REFDMA_14_reg))
#define get_RL_L1REFDMA_15_reg   (*((volatile unsigned int*) RL_L1REFDMA_15_reg))
#define get_RL_L1REFDMA_16_reg   (*((volatile unsigned int*) RL_L1REFDMA_16_reg))
#define get_RL_L1REFDMA_17_reg   (*((volatile unsigned int*) RL_L1REFDMA_17_reg))
#define get_RL_L1REFDMA_18_reg   (*((volatile unsigned int*) RL_L1REFDMA_18_reg))
#define get_RL_L1REFDMA_19_reg   (*((volatile unsigned int*) RL_L1REFDMA_19_reg))
#define get_RL_L1REFDMA_20_reg   (*((volatile unsigned int*) RL_L1REFDMA_20_reg))
#define get_RL_L1REFDMA_21_reg   (*((volatile unsigned int*) RL_L1REFDMA_21_reg))
#define get_RL_L1REFDMA_22_reg   (*((volatile unsigned int*) RL_L1REFDMA_22_reg))
#define get_RL_L1REFDMA_23_reg   (*((volatile unsigned int*) RL_L1REFDMA_23_reg))
#define get_RL_L1REFDMA_24_reg   (*((volatile unsigned int*) RL_L1REFDMA_24_reg))
#define get_RL_L1REFDMA_25_reg   (*((volatile unsigned int*) RL_L1REFDMA_25_reg))
#define get_RL_L1REFDMA_26_reg   (*((volatile unsigned int*) RL_L1REFDMA_26_reg))
#define get_RL_L1REFDMA_27_reg   (*((volatile unsigned int*) RL_L1REFDMA_27_reg))
#define get_RL_L1REFDMA_28_reg   (*((volatile unsigned int*) RL_L1REFDMA_28_reg))
#define get_RL_L1REFDMA_29_reg   (*((volatile unsigned int*) RL_L1REFDMA_29_reg))
#define get_RL_L1REFDMA_30_reg   (*((volatile unsigned int*) RL_L1REFDMA_30_reg))
#define get_RL_L1REFDMA_31_reg   (*((volatile unsigned int*) RL_L1REFDMA_31_reg))
#define RL_L1REFDMA_0_inst_adr                                                       "0x0060"
#define RL_L1REFDMA_1_inst_adr                                                       "0x0061"
#define RL_L1REFDMA_2_inst_adr                                                       "0x0062"
#define RL_L1REFDMA_3_inst_adr                                                       "0x0063"
#define RL_L1REFDMA_4_inst_adr                                                       "0x0064"
#define RL_L1REFDMA_5_inst_adr                                                       "0x0065"
#define RL_L1REFDMA_6_inst_adr                                                       "0x0066"
#define RL_L1REFDMA_7_inst_adr                                                       "0x0067"
#define RL_L1REFDMA_8_inst_adr                                                       "0x0068"
#define RL_L1REFDMA_9_inst_adr                                                       "0x0069"
#define RL_L1REFDMA_10_inst_adr                                                       "0x006A"
#define RL_L1REFDMA_11_inst_adr                                                       "0x006B"
#define RL_L1REFDMA_12_inst_adr                                                       "0x006C"
#define RL_L1REFDMA_13_inst_adr                                                       "0x006D"
#define RL_L1REFDMA_14_inst_adr                                                       "0x006E"
#define RL_L1REFDMA_15_inst_adr                                                       "0x006F"
#define RL_L1REFDMA_16_inst_adr                                                       "0x0070"
#define RL_L1REFDMA_17_inst_adr                                                       "0x0071"
#define RL_L1REFDMA_18_inst_adr                                                       "0x0072"
#define RL_L1REFDMA_19_inst_adr                                                       "0x0073"
#define RL_L1REFDMA_20_inst_adr                                                       "0x0074"
#define RL_L1REFDMA_21_inst_adr                                                       "0x0075"
#define RL_L1REFDMA_22_inst_adr                                                       "0x0076"
#define RL_L1REFDMA_23_inst_adr                                                       "0x0077"
#define RL_L1REFDMA_24_inst_adr                                                       "0x0078"
#define RL_L1REFDMA_25_inst_adr                                                       "0x0079"
#define RL_L1REFDMA_26_inst_adr                                                       "0x007A"
#define RL_L1REFDMA_27_inst_adr                                                       "0x007B"
#define RL_L1REFDMA_28_inst_adr                                                       "0x007C"
#define RL_L1REFDMA_29_inst_adr                                                       "0x007D"
#define RL_L1REFDMA_30_inst_adr                                                       "0x007E"
#define RL_L1REFDMA_31_inst_adr                                                       "0x007F"
#define RL_L1REFDMA_0_inst                                                           0x0060
#define RL_L1REFDMA_1_inst                                                           0x0061
#define RL_L1REFDMA_2_inst                                                           0x0062
#define RL_L1REFDMA_3_inst                                                           0x0063
#define RL_L1REFDMA_4_inst                                                           0x0064
#define RL_L1REFDMA_5_inst                                                           0x0065
#define RL_L1REFDMA_6_inst                                                           0x0066
#define RL_L1REFDMA_7_inst                                                           0x0067
#define RL_L1REFDMA_8_inst                                                           0x0068
#define RL_L1REFDMA_9_inst                                                           0x0069
#define RL_L1REFDMA_10_inst                                                           0x006A
#define RL_L1REFDMA_11_inst                                                           0x006B
#define RL_L1REFDMA_12_inst                                                           0x006C
#define RL_L1REFDMA_13_inst                                                           0x006D
#define RL_L1REFDMA_14_inst                                                           0x006E
#define RL_L1REFDMA_15_inst                                                           0x006F
#define RL_L1REFDMA_16_inst                                                           0x0070
#define RL_L1REFDMA_17_inst                                                           0x0071
#define RL_L1REFDMA_18_inst                                                           0x0072
#define RL_L1REFDMA_19_inst                                                           0x0073
#define RL_L1REFDMA_20_inst                                                           0x0074
#define RL_L1REFDMA_21_inst                                                           0x0075
#define RL_L1REFDMA_22_inst                                                           0x0076
#define RL_L1REFDMA_23_inst                                                           0x0077
#define RL_L1REFDMA_24_inst                                                           0x0078
#define RL_L1REFDMA_25_inst                                                           0x0079
#define RL_L1REFDMA_26_inst                                                           0x007A
#define RL_L1REFDMA_27_inst                                                           0x007B
#define RL_L1REFDMA_28_inst                                                           0x007C
#define RL_L1REFDMA_29_inst                                                           0x007D
#define RL_L1REFDMA_30_inst                                                           0x007E
#define RL_L1REFDMA_31_inst                                                           0x007F
#define RL_L1REFDMA_ref_RANGEREDFRM_shift                                            (15)
#define RL_L1REFDMA_ref_RANGEREDFRM_mask                                             (0x00008000)
#define RL_L1REFDMA_ref_RANGEREDFRM(data)                                            (0x00008000&((data)<<15))
#define RL_L1REFDMA_ref_RANGEREDFRM_src(data)                                        ((0x00008000&(data))>>15)
#define RL_L1REFDMA_get_ref_RANGEREDFRM(data)                                        ((0x00008000&(data))>>15)
#define RL_L1REFDMA_bottom_field_flag_shift                                          (14)
#define RL_L1REFDMA_bottom_field_flag_mask                                           (0x00004000)
#define RL_L1REFDMA_bottom_field_flag(data)                                          (0x00004000&((data)<<14))
#define RL_L1REFDMA_bottom_field_flag_src(data)                                      ((0x00004000&(data))>>14)
#define RL_L1REFDMA_get_bottom_field_flag(data)                                      ((0x00004000&(data))>>14)
#define RL_L1REFDMA_lu_addr_index_shift                                              (7)
#define RL_L1REFDMA_lu_addr_index_mask                                               (0x00003F80)
#define RL_L1REFDMA_lu_addr_index(data)                                              (0x00003F80&((data)<<7))
#define RL_L1REFDMA_lu_addr_index_src(data)                                          ((0x00003F80&(data))>>7)
#define RL_L1REFDMA_get_lu_addr_index(data)                                          ((0x00003F80&(data))>>7)
#define RL_L1REFDMA_ch_addr_index_shift                                              (0)
#define RL_L1REFDMA_ch_addr_index_mask                                               (0x0000007F)
#define RL_L1REFDMA_ch_addr_index(data)                                              (0x0000007F&((data)<<0))
#define RL_L1REFDMA_ch_addr_index_src(data)                                          ((0x0000007F&(data))>>0)
#define RL_L1REFDMA_get_ch_addr_index(data)                                          ((0x0000007F&(data))>>0)


#define RL_DBG_SEL                                                                   0x1800EC18
#define RL_DBG_SEL_reg_addr                                                          "0xB800EC18"
#define RL_DBG_SEL_reg                                                               0xB800EC18
#define set_RL_DBG_SEL_reg(data)   (*((volatile unsigned int*) RL_DBG_SEL_reg)=data)
#define get_RL_DBG_SEL_reg   (*((volatile unsigned int*) RL_DBG_SEL_reg))
#define RL_DBG_SEL_inst_adr                                                          "0x0006"
#define RL_DBG_SEL_inst                                                              0x0006
#define RL_DBG_SEL_write_enable3_shift                                               (31)
#define RL_DBG_SEL_write_enable3_mask                                                (0x80000000)
#define RL_DBG_SEL_write_enable3(data)                                               (0x80000000&((data)<<31))
#define RL_DBG_SEL_write_enable3_src(data)                                           ((0x80000000&(data))>>31)
#define RL_DBG_SEL_get_write_enable3(data)                                           ((0x80000000&(data))>>31)
#define RL_DBG_SEL_Trigger_status_shift                                              (30)
#define RL_DBG_SEL_Trigger_status_mask                                               (0x40000000)
#define RL_DBG_SEL_Trigger_status(data)                                              (0x40000000&((data)<<30))
#define RL_DBG_SEL_Trigger_status_src(data)                                          ((0x40000000&(data))>>30)
#define RL_DBG_SEL_get_Trigger_status(data)                                          ((0x40000000&(data))>>30)
#define RL_DBG_SEL_Zero_w_lr_shift                                                   (28)
#define RL_DBG_SEL_Zero_w_lr_mask                                                    (0x30000000)
#define RL_DBG_SEL_Zero_w_lr(data)                                                   (0x30000000&((data)<<28))
#define RL_DBG_SEL_Zero_w_lr_src(data)                                               ((0x30000000&(data))>>28)
#define RL_DBG_SEL_get_Zero_w_lr(data)                                               ((0x30000000&(data))>>28)
#define RL_DBG_SEL_write_enable2_shift                                               (27)
#define RL_DBG_SEL_write_enable2_mask                                                (0x08000000)
#define RL_DBG_SEL_write_enable2(data)                                               (0x08000000&((data)<<27))
#define RL_DBG_SEL_write_enable2_src(data)                                           ((0x08000000&(data))>>27)
#define RL_DBG_SEL_get_write_enable2(data)                                           ((0x08000000&(data))>>27)
#define RL_DBG_SEL_Trigger_select_shift                                              (23)
#define RL_DBG_SEL_Trigger_select_mask                                               (0x07800000)
#define RL_DBG_SEL_Trigger_select(data)                                              (0x07800000&((data)<<23))
#define RL_DBG_SEL_Trigger_select_src(data)                                          ((0x07800000&(data))>>23)
#define RL_DBG_SEL_get_Trigger_select(data)                                          ((0x07800000&(data))>>23)
#define RL_DBG_SEL_Trigger_cond_mb_x_shift                                           (12)
#define RL_DBG_SEL_Trigger_cond_mb_x_mask                                            (0x001FF000)
#define RL_DBG_SEL_Trigger_cond_mb_x(data)                                           (0x001FF000&((data)<<12))
#define RL_DBG_SEL_Trigger_cond_mb_x_src(data)                                       ((0x001FF000&(data))>>12)
#define RL_DBG_SEL_get_Trigger_cond_mb_x(data)                                       ((0x001FF000&(data))>>12)
#define RL_DBG_SEL_Trigger_cond_mb_y_shift                                           (4)
#define RL_DBG_SEL_Trigger_cond_mb_y_mask                                            (0x00000FF0)
#define RL_DBG_SEL_Trigger_cond_mb_y(data)                                           (0x00000FF0&((data)<<4))
#define RL_DBG_SEL_Trigger_cond_mb_y_src(data)                                       ((0x00000FF0&(data))>>4)
#define RL_DBG_SEL_get_Trigger_cond_mb_y(data)                                       ((0x00000FF0&(data))>>4)
#define RL_DBG_SEL_write_enable1_shift                                               (3)
#define RL_DBG_SEL_write_enable1_mask                                                (0x00000008)
#define RL_DBG_SEL_write_enable1(data)                                               (0x00000008&((data)<<3))
#define RL_DBG_SEL_write_enable1_src(data)                                           ((0x00000008&(data))>>3)
#define RL_DBG_SEL_get_write_enable1(data)                                           ((0x00000008&(data))>>3)
#define RL_DBG_SEL_Debug_port_sel_shift                                              (0)
#define RL_DBG_SEL_Debug_port_sel_mask                                               (0x00000007)
#define RL_DBG_SEL_Debug_port_sel(data)                                              (0x00000007&((data)<<0))
#define RL_DBG_SEL_Debug_port_sel_src(data)                                          ((0x00000007&(data))>>0)
#define RL_DBG_SEL_get_Debug_port_sel(data)                                          ((0x00000007&(data))>>0)


#define RL_DBG_STS0                                                                  0x1800EC1C
#define RL_DBG_STS0_reg_addr                                                         "0xB800EC1C"
#define RL_DBG_STS0_reg                                                              0xB800EC1C
#define set_RL_DBG_STS0_reg(data)   (*((volatile unsigned int*) RL_DBG_STS0_reg)=data)
#define get_RL_DBG_STS0_reg   (*((volatile unsigned int*) RL_DBG_STS0_reg))
#define RL_DBG_STS0_inst_adr                                                         "0x0007"
#define RL_DBG_STS0_inst                                                             0x0007
#define RL_DBG_STS0_Tbl_cnt_shift                                                    (16)
#define RL_DBG_STS0_Tbl_cnt_mask                                                     (0xFFFF0000)
#define RL_DBG_STS0_Tbl_cnt(data)                                                    (0xFFFF0000&((data)<<16))
#define RL_DBG_STS0_Tbl_cnt_src(data)                                                ((0xFFFF0000&(data))>>16)
#define RL_DBG_STS0_get_Tbl_cnt(data)                                                ((0xFFFF0000&(data))>>16)
#define RL_DBG_STS0_Trigger_tbl_cnt_shift                                            (0)
#define RL_DBG_STS0_Trigger_tbl_cnt_mask                                             (0x0000FFFF)
#define RL_DBG_STS0_Trigger_tbl_cnt(data)                                            (0x0000FFFF&((data)<<0))
#define RL_DBG_STS0_Trigger_tbl_cnt_src(data)                                        ((0x0000FFFF&(data))>>0)
#define RL_DBG_STS0_get_Trigger_tbl_cnt(data)                                        ((0x0000FFFF&(data))>>0)


#define RL_DBG_STS1                                                                  0x1800EC20
#define RL_DBG_STS1_reg_addr                                                         "0xB800EC20"
#define RL_DBG_STS1_reg                                                              0xB800EC20
#define set_RL_DBG_STS1_reg(data)   (*((volatile unsigned int*) RL_DBG_STS1_reg)=data)
#define get_RL_DBG_STS1_reg   (*((volatile unsigned int*) RL_DBG_STS1_reg))
#define RL_DBG_STS1_inst_adr                                                         "0x0008"
#define RL_DBG_STS1_inst                                                             0x0008
#define RL_DBG_STS1_DBG_STS_shift                                                    (0)
#define RL_DBG_STS1_DBG_STS_mask                                                     (0xFFFFFFFF)
#define RL_DBG_STS1_DBG_STS(data)                                                    (0xFFFFFFFF&((data)<<0))
#define RL_DBG_STS1_DBG_STS_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define RL_DBG_STS1_get_DBG_STS(data)                                                ((0xFFFFFFFF&(data))>>0)


#define RL_DBG_STS2                                                                  0x1800EC24
#define RL_DBG_STS2_reg_addr                                                         "0xB800EC24"
#define RL_DBG_STS2_reg                                                              0xB800EC24
#define set_RL_DBG_STS2_reg(data)   (*((volatile unsigned int*) RL_DBG_STS2_reg)=data)
#define get_RL_DBG_STS2_reg   (*((volatile unsigned int*) RL_DBG_STS2_reg))
#define RL_DBG_STS2_inst_adr                                                         "0x0009"
#define RL_DBG_STS2_inst                                                             0x0009
#define RL_DBG_STS2_DBG_STS_shift                                                    (0)
#define RL_DBG_STS2_DBG_STS_mask                                                     (0xFFFFFFFF)
#define RL_DBG_STS2_DBG_STS(data)                                                    (0xFFFFFFFF&((data)<<0))
#define RL_DBG_STS2_DBG_STS_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define RL_DBG_STS2_get_DBG_STS(data)                                                ((0xFFFFFFFF&(data))>>0)


#define RL_INTR_THRES                                                                0x1800EC28
#define RL_INTR_THRES_reg_addr                                                       "0xB800EC28"
#define RL_INTR_THRES_reg                                                            0xB800EC28
#define set_RL_INTR_THRES_reg(data)   (*((volatile unsigned int*) RL_INTR_THRES_reg)=data)
#define get_RL_INTR_THRES_reg   (*((volatile unsigned int*) RL_INTR_THRES_reg))
#define RL_INTR_THRES_inst_adr                                                       "0x000A"
#define RL_INTR_THRES_inst                                                           0x000A
#define RL_INTR_THRES_Intr_shift                                                     (28)
#define RL_INTR_THRES_Intr_mask                                                      (0x10000000)
#define RL_INTR_THRES_Intr(data)                                                     (0x10000000&((data)<<28))
#define RL_INTR_THRES_Intr_src(data)                                                 ((0x10000000&(data))>>28)
#define RL_INTR_THRES_get_Intr(data)                                                 ((0x10000000&(data))>>28)
#define RL_INTR_THRES_Value_shift                                                    (0)
#define RL_INTR_THRES_Value_mask                                                     (0x0FFFFFFF)
#define RL_INTR_THRES_Value(data)                                                    (0x0FFFFFFF&((data)<<0))
#define RL_INTR_THRES_Value_src(data)                                                ((0x0FFFFFFF&(data))>>0)
#define RL_INTR_THRES_get_Value(data)                                                ((0x0FFFFFFF&(data))>>0)


#define RL_MVBUF_WADD                                                                0x1800EC80
#define RL_MVBUF_WADD_reg_addr                                                       "0xB800EC80"
#define RL_MVBUF_WADD_reg                                                            0xB800EC80
#define set_RL_MVBUF_WADD_reg(data)   (*((volatile unsigned int*) RL_MVBUF_WADD_reg)=data)
#define get_RL_MVBUF_WADD_reg   (*((volatile unsigned int*) RL_MVBUF_WADD_reg))
#define RL_MVBUF_WADD_inst_adr                                                       "0x0020"
#define RL_MVBUF_WADD_inst                                                           0x0020
#define RL_MVBUF_WADD_MVBUF_write_address_shift                                      (0)
#define RL_MVBUF_WADD_MVBUF_write_address_mask                                       (0x0000007F)
#define RL_MVBUF_WADD_MVBUF_write_address(data)                                      (0x0000007F&((data)<<0))
#define RL_MVBUF_WADD_MVBUF_write_address_src(data)                                  ((0x0000007F&(data))>>0)
#define RL_MVBUF_WADD_get_MVBUF_write_address(data)                                  ((0x0000007F&(data))>>0)


#define RL_MVBUF_DATA_0                                                              0x1800EC84
#define RL_MVBUF_DATA_1                                                              0x1800EC88
#define RL_MVBUF_DATA_2                                                              0x1800EC8C
#define RL_MVBUF_DATA_0_reg_addr                                                     "0xB800EC84"
#define RL_MVBUF_DATA_1_reg_addr                                                     "0xB800EC88"
#define RL_MVBUF_DATA_2_reg_addr                                                     "0xB800EC8C"
#define RL_MVBUF_DATA_0_reg                                                          0xB800EC84
#define RL_MVBUF_DATA_1_reg                                                          0xB800EC88
#define RL_MVBUF_DATA_2_reg                                                          0xB800EC8C
#define set_RL_MVBUF_DATA_0_reg(data)   (*((volatile unsigned int*) RL_MVBUF_DATA_0_reg)=data)
#define set_RL_MVBUF_DATA_1_reg(data)   (*((volatile unsigned int*) RL_MVBUF_DATA_1_reg)=data)
#define set_RL_MVBUF_DATA_2_reg(data)   (*((volatile unsigned int*) RL_MVBUF_DATA_2_reg)=data)
#define get_RL_MVBUF_DATA_0_reg   (*((volatile unsigned int*) RL_MVBUF_DATA_0_reg))
#define get_RL_MVBUF_DATA_1_reg   (*((volatile unsigned int*) RL_MVBUF_DATA_1_reg))
#define get_RL_MVBUF_DATA_2_reg   (*((volatile unsigned int*) RL_MVBUF_DATA_2_reg))
#define RL_MVBUF_DATA_0_inst_adr                                                     "0x0021"
#define RL_MVBUF_DATA_1_inst_adr                                                     "0x0022"
#define RL_MVBUF_DATA_2_inst_adr                                                     "0x0023"
#define RL_MVBUF_DATA_0_inst                                                         0x0021
#define RL_MVBUF_DATA_1_inst                                                         0x0022
#define RL_MVBUF_DATA_2_inst                                                         0x0023
#define RL_MVBUF_DATA_MVBUF_read_write_data_shift                                    (0)
#define RL_MVBUF_DATA_MVBUF_read_write_data_mask                                     (0xFFFFFFFF)
#define RL_MVBUF_DATA_MVBUF_read_write_data(data)                                    (0xFFFFFFFF&((data)<<0))
#define RL_MVBUF_DATA_MVBUF_read_write_data_src(data)                                ((0xFFFFFFFF&(data))>>0)
#define RL_MVBUF_DATA_get_MVBUF_read_write_data(data)                                ((0xFFFFFFFF&(data))>>0)


#define RL_MVBUF_RADD                                                                0x1800EC90
#define RL_MVBUF_RADD_reg_addr                                                       "0xB800EC90"
#define RL_MVBUF_RADD_reg                                                            0xB800EC90
#define set_RL_MVBUF_RADD_reg(data)   (*((volatile unsigned int*) RL_MVBUF_RADD_reg)=data)
#define get_RL_MVBUF_RADD_reg   (*((volatile unsigned int*) RL_MVBUF_RADD_reg))
#define RL_MVBUF_RADD_inst_adr                                                       "0x0024"
#define RL_MVBUF_RADD_inst                                                           0x0024
#define RL_MVBUF_RADD_MVBUF_read_address_shift                                       (0)
#define RL_MVBUF_RADD_MVBUF_read_address_mask                                        (0x0000007F)
#define RL_MVBUF_RADD_MVBUF_read_address(data)                                       (0x0000007F&((data)<<0))
#define RL_MVBUF_RADD_MVBUF_read_address_src(data)                                   ((0x0000007F&(data))>>0)
#define RL_MVBUF_RADD_get_MVBUF_read_address(data)                                   ((0x0000007F&(data))>>0)


#define RL_MVBUF_STS0                                                                0x1800EC94
#define RL_MVBUF_STS0_reg_addr                                                       "0xB800EC94"
#define RL_MVBUF_STS0_reg                                                            0xB800EC94
#define set_RL_MVBUF_STS0_reg(data)   (*((volatile unsigned int*) RL_MVBUF_STS0_reg)=data)
#define get_RL_MVBUF_STS0_reg   (*((volatile unsigned int*) RL_MVBUF_STS0_reg))
#define RL_MVBUF_STS0_inst_adr                                                       "0x0025"
#define RL_MVBUF_STS0_inst                                                           0x0025
#define RL_MVBUF_STS0_write_enable3_shift                                            (31)
#define RL_MVBUF_STS0_write_enable3_mask                                             (0x80000000)
#define RL_MVBUF_STS0_write_enable3(data)                                            (0x80000000&((data)<<31))
#define RL_MVBUF_STS0_write_enable3_src(data)                                        ((0x80000000&(data))>>31)
#define RL_MVBUF_STS0_get_write_enable3(data)                                        ((0x80000000&(data))>>31)
#define RL_MVBUF_STS0_MVBUF_hdr_shift                                                (24)
#define RL_MVBUF_STS0_MVBUF_hdr_mask                                                 (0x7F000000)
#define RL_MVBUF_STS0_MVBUF_hdr(data)                                                (0x7F000000&((data)<<24))
#define RL_MVBUF_STS0_MVBUF_hdr_src(data)                                            ((0x7F000000&(data))>>24)
#define RL_MVBUF_STS0_get_MVBUF_hdr(data)                                            ((0x7F000000&(data))>>24)
#define RL_MVBUF_STS0_write_enable2_shift                                            (20)
#define RL_MVBUF_STS0_write_enable2_mask                                             (0x00100000)
#define RL_MVBUF_STS0_write_enable2(data)                                            (0x00100000&((data)<<20))
#define RL_MVBUF_STS0_write_enable2_src(data)                                        ((0x00100000&(data))>>20)
#define RL_MVBUF_STS0_get_write_enable2(data)                                        ((0x00100000&(data))>>20)
#define RL_MVBUF_STS0_MVBUF_pred_rptr_shift                                          (12)
#define RL_MVBUF_STS0_MVBUF_pred_rptr_mask                                           (0x000FF000)
#define RL_MVBUF_STS0_MVBUF_pred_rptr(data)                                          (0x000FF000&((data)<<12))
#define RL_MVBUF_STS0_MVBUF_pred_rptr_src(data)                                      ((0x000FF000&(data))>>12)
#define RL_MVBUF_STS0_get_MVBUF_pred_rptr(data)                                      ((0x000FF000&(data))>>12)
#define RL_MVBUF_STS0_write_enable1_shift                                            (8)
#define RL_MVBUF_STS0_write_enable1_mask                                             (0x00000100)
#define RL_MVBUF_STS0_write_enable1(data)                                            (0x00000100&((data)<<8))
#define RL_MVBUF_STS0_write_enable1_src(data)                                        ((0x00000100&(data))>>8)
#define RL_MVBUF_STS0_get_write_enable1(data)                                        ((0x00000100&(data))>>8)
#define RL_MVBUF_STS0_MVBUF_mvd_wptr_shift                                           (0)
#define RL_MVBUF_STS0_MVBUF_mvd_wptr_mask                                            (0x000000FF)
#define RL_MVBUF_STS0_MVBUF_mvd_wptr(data)                                           (0x000000FF&((data)<<0))
#define RL_MVBUF_STS0_MVBUF_mvd_wptr_src(data)                                       ((0x000000FF&(data))>>0)
#define RL_MVBUF_STS0_get_MVBUF_mvd_wptr(data)                                       ((0x000000FF&(data))>>0)


#define RL_MVBUF_STS1                                                                0x1800EC98
#define RL_MVBUF_STS1_reg_addr                                                       "0xB800EC98"
#define RL_MVBUF_STS1_reg                                                            0xB800EC98
#define set_RL_MVBUF_STS1_reg(data)   (*((volatile unsigned int*) RL_MVBUF_STS1_reg)=data)
#define get_RL_MVBUF_STS1_reg   (*((volatile unsigned int*) RL_MVBUF_STS1_reg))
#define RL_MVBUF_STS1_inst_adr                                                       "0x0026"
#define RL_MVBUF_STS1_inst                                                           0x0026
#define RL_MVBUF_STS1_write_enable1_shift                                            (8)
#define RL_MVBUF_STS1_write_enable1_mask                                             (0x00000100)
#define RL_MVBUF_STS1_write_enable1(data)                                            (0x00000100&((data)<<8))
#define RL_MVBUF_STS1_write_enable1_src(data)                                        ((0x00000100&(data))>>8)
#define RL_MVBUF_STS1_get_write_enable1(data)                                        ((0x00000100&(data))>>8)
#define RL_MVBUF_STS1_MVBUF_rl_rptr_shift                                            (0)
#define RL_MVBUF_STS1_MVBUF_rl_rptr_mask                                             (0x000000FF)
#define RL_MVBUF_STS1_MVBUF_rl_rptr(data)                                            (0x000000FF&((data)<<0))
#define RL_MVBUF_STS1_MVBUF_rl_rptr_src(data)                                        ((0x000000FF&(data))>>0)
#define RL_MVBUF_STS1_get_MVBUF_rl_rptr(data)                                        ((0x000000FF&(data))>>0)


#define RL_CACHE_SET                                                                 0x1800EC9C
#define RL_CACHE_SET_reg_addr                                                        "0xB800EC9C"
#define RL_CACHE_SET_reg                                                             0xB800EC9C
#define set_RL_CACHE_SET_reg(data)   (*((volatile unsigned int*) RL_CACHE_SET_reg)=data)
#define get_RL_CACHE_SET_reg   (*((volatile unsigned int*) RL_CACHE_SET_reg))
#define RL_CACHE_SET_inst_adr                                                        "0x0027"
#define RL_CACHE_SET_inst                                                            0x0027
#define RL_CACHE_SET_write_enable2_shift                                             (4)
#define RL_CACHE_SET_write_enable2_mask                                              (0x00000010)
#define RL_CACHE_SET_write_enable2(data)                                             (0x00000010&((data)<<4))
#define RL_CACHE_SET_write_enable2_src(data)                                         ((0x00000010&(data))>>4)
#define RL_CACHE_SET_get_write_enable2(data)                                         ((0x00000010&(data))>>4)
#define RL_CACHE_SET_Vg_en_shift                                                     (2)
#define RL_CACHE_SET_Vg_en_mask                                                      (0x0000000C)
#define RL_CACHE_SET_Vg_en(data)                                                     (0x0000000C&((data)<<2))
#define RL_CACHE_SET_Vg_en_src(data)                                                 ((0x0000000C&(data))>>2)
#define RL_CACHE_SET_get_Vg_en(data)                                                 ((0x0000000C&(data))>>2)
#define RL_CACHE_SET_write_enable1_shift                                             (1)
#define RL_CACHE_SET_write_enable1_mask                                              (0x00000002)
#define RL_CACHE_SET_write_enable1(data)                                             (0x00000002&((data)<<1))
#define RL_CACHE_SET_write_enable1_src(data)                                         ((0x00000002&(data))>>1)
#define RL_CACHE_SET_get_write_enable1(data)                                         ((0x00000002&(data))>>1)
#define RL_CACHE_SET_Ref_pic_cnt_shift                                               (0)
#define RL_CACHE_SET_Ref_pic_cnt_mask                                                (0x00000001)
#define RL_CACHE_SET_Ref_pic_cnt(data)                                               (0x00000001&((data)<<0))
#define RL_CACHE_SET_Ref_pic_cnt_src(data)                                           ((0x00000001&(data))>>0)
#define RL_CACHE_SET_get_Ref_pic_cnt(data)                                           ((0x00000001&(data))>>0)


#define RL_CACHE_EN                                                                  0x1800ECA0
#define RL_CACHE_EN_reg_addr                                                         "0xB800ECA0"
#define RL_CACHE_EN_reg                                                              0xB800ECA0
#define set_RL_CACHE_EN_reg(data)   (*((volatile unsigned int*) RL_CACHE_EN_reg)=data)
#define get_RL_CACHE_EN_reg   (*((volatile unsigned int*) RL_CACHE_EN_reg))
#define RL_CACHE_EN_inst_adr                                                         "0x0028"
#define RL_CACHE_EN_inst                                                             0x0028
#define RL_CACHE_EN_Cah_en_shift                                                     (0)
#define RL_CACHE_EN_Cah_en_mask                                                      (0x00000001)
#define RL_CACHE_EN_Cah_en(data)                                                     (0x00000001&((data)<<0))
#define RL_CACHE_EN_Cah_en_src(data)                                                 ((0x00000001&(data))>>0)
#define RL_CACHE_EN_get_Cah_en(data)                                                 ((0x00000001&(data))>>0)


#define RL_CACHE_INV                                                                 0x1800ECA4
#define RL_CACHE_INV_reg_addr                                                        "0xB800ECA4"
#define RL_CACHE_INV_reg                                                             0xB800ECA4
#define set_RL_CACHE_INV_reg(data)   (*((volatile unsigned int*) RL_CACHE_INV_reg)=data)
#define get_RL_CACHE_INV_reg   (*((volatile unsigned int*) RL_CACHE_INV_reg))
#define RL_CACHE_INV_inst_adr                                                        "0x0029"
#define RL_CACHE_INV_inst                                                            0x0029
#define RL_CACHE_INV_Cah_inv_shift                                                   (0)
#define RL_CACHE_INV_Cah_inv_mask                                                    (0x00000001)
#define RL_CACHE_INV_Cah_inv(data)                                                   (0x00000001&((data)<<0))
#define RL_CACHE_INV_Cah_inv_src(data)                                               ((0x00000001&(data))>>0)
#define RL_CACHE_INV_get_Cah_inv(data)                                               ((0x00000001&(data))>>0)


#define RL_CAH_PINDX                                                                 0x1800ECA8
#define RL_CAH_PINDX_reg_addr                                                        "0xB800ECA8"
#define RL_CAH_PINDX_reg                                                             0xB800ECA8
#define set_RL_CAH_PINDX_reg(data)   (*((volatile unsigned int*) RL_CAH_PINDX_reg)=data)
#define get_RL_CAH_PINDX_reg   (*((volatile unsigned int*) RL_CAH_PINDX_reg))
#define RL_CAH_PINDX_inst_adr                                                        "0x002A"
#define RL_CAH_PINDX_inst                                                            0x002A
#define RL_CAH_PINDX_Cah_pindx0_LumL0_shift                                          (24)
#define RL_CAH_PINDX_Cah_pindx0_LumL0_mask                                           (0xFF000000)
#define RL_CAH_PINDX_Cah_pindx0_LumL0(data)                                          (0xFF000000&((data)<<24))
#define RL_CAH_PINDX_Cah_pindx0_LumL0_src(data)                                      ((0xFF000000&(data))>>24)
#define RL_CAH_PINDX_get_Cah_pindx0_LumL0(data)                                      ((0xFF000000&(data))>>24)
#define RL_CAH_PINDX_Cah_pindx1_LumL1_shift                                          (16)
#define RL_CAH_PINDX_Cah_pindx1_LumL1_mask                                           (0x00FF0000)
#define RL_CAH_PINDX_Cah_pindx1_LumL1(data)                                          (0x00FF0000&((data)<<16))
#define RL_CAH_PINDX_Cah_pindx1_LumL1_src(data)                                      ((0x00FF0000&(data))>>16)
#define RL_CAH_PINDX_get_Cah_pindx1_LumL1(data)                                      ((0x00FF0000&(data))>>16)
#define RL_CAH_PINDX_Cah_pindx2_ChrL0_shift                                          (8)
#define RL_CAH_PINDX_Cah_pindx2_ChrL0_mask                                           (0x0000FF00)
#define RL_CAH_PINDX_Cah_pindx2_ChrL0(data)                                          (0x0000FF00&((data)<<8))
#define RL_CAH_PINDX_Cah_pindx2_ChrL0_src(data)                                      ((0x0000FF00&(data))>>8)
#define RL_CAH_PINDX_get_Cah_pindx2_ChrL0(data)                                      ((0x0000FF00&(data))>>8)
#define RL_CAH_PINDX_Cah_pindx3_ChrL1_shift                                          (0)
#define RL_CAH_PINDX_Cah_pindx3_ChrL1_mask                                           (0x000000FF)
#define RL_CAH_PINDX_Cah_pindx3_ChrL1(data)                                          (0x000000FF&((data)<<0))
#define RL_CAH_PINDX_Cah_pindx3_ChrL1_src(data)                                      ((0x000000FF&(data))>>0)
#define RL_CAH_PINDX_get_Cah_pindx3_ChrL1(data)                                      ((0x000000FF&(data))>>0)


#endif
