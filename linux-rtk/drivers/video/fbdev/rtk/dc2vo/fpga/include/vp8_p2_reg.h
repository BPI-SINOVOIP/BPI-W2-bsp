/**************************************************************
// Spec Version                  : 0.2
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2012/6/22 11:40:33
***************************************************************/


#ifndef _VP8_P2_REG_H_INCLUDED_
#define _VP8_P2_REG_H_INCLUDED_
#ifdef  _VP8_P2_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_enable7:1;
unsigned int     slice_cnt:8;
unsigned int     write_enable6:1;
unsigned int     full_pixel:1;
unsigned int     write_enable5:1;
unsigned int     ref_frame_sign_bias:4;
unsigned int     write_enable4:1;
unsigned int     mb_no_coeff_skip:1;
unsigned int     write_enable3:1;
unsigned int     segmentation_enabled:1;
unsigned int     write_enable2:1;
unsigned int     update_mb_segmentation_map:1;
unsigned int     write_enable1:1;
unsigned int     prob_skip_false:8;
}VP8_P2_VP8_P2_FRM1;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     write_enable3:1;
unsigned int     prob_gf:8;
unsigned int     write_enable2:1;
unsigned int     prob_last:8;
unsigned int     write_enable1:1;
unsigned int     prob_intra:8;
}VP8_P2_VP8_P2_FRM2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     write_enable1:1;
unsigned int     picmb_h:7;
}VP8_P2_VP8_P2_FRM3;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     need_to_clamp_mvs:1;
unsigned int     ref_frame:2;
unsigned int     uv_mode:2;
unsigned int     mode:4;
unsigned int     mb_skip_coeff:1;
unsigned int     segment_id:2;
}VP8_P2_VP8_P2_MB1;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     write_enable3:1;
unsigned int     ndb_p2_flush:1;
unsigned int     write_enable2:1;
unsigned int     mby:7;
unsigned int     write_enable1:1;
unsigned int     left_sub_block_mode:16;
}VP8_P2_VP8_P2_MB2;

typedef struct 
{
unsigned int     sub_blk_mode_p0:32;
}VP8_P2_VP8_P2_SUB_BLK0;

typedef struct 
{
unsigned int     sub_blk_mode_p1:32;
}VP8_P2_VP8_P2_SUB_BLK1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     vp8_p2_curmb:9;
unsigned int     vp8_mbpartition:9;
unsigned int     vp8_Inter_pred_option:8;
}VP8_P2_VP8_P2_MB_INFO;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     high:9;
unsigned int     bits:4;
unsigned int     code_word:16;
}VP8_P2_VP8_BAC;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV0;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV1;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV2;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV3;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV4;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV5;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV6;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV7;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV8;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV9;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV10;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV11;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV12;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV13;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV14;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_MV15;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_CH_MV0;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_CH_MV1;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_CH_MV2;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     mv_x:15;
unsigned int     mv_y:14;
}VP8_P2_VP8_MB_CH_MV3;

#endif

#define VP8_P2_VP8_P2_FRM1                                                           0x1800EF00
#define VP8_P2_VP8_P2_FRM1_reg_addr                                                  "0xB800EF00"
#define VP8_P2_VP8_P2_FRM1_reg                                                       0xB800EF00
#define set_VP8_P2_VP8_P2_FRM1_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_P2_FRM1_reg)=data)
#define get_VP8_P2_VP8_P2_FRM1_reg   (*((volatile unsigned int*) VP8_P2_VP8_P2_FRM1_reg))
#define VP8_P2_VP8_P2_FRM1_inst_adr                                                  "0x00C0"
#define VP8_P2_VP8_P2_FRM1_inst                                                      0x00C0
#define VP8_P2_VP8_P2_FRM1_write_enable7_shift                                       (30)
#define VP8_P2_VP8_P2_FRM1_write_enable7_mask                                        (0x40000000)
#define VP8_P2_VP8_P2_FRM1_write_enable7(data)                                       (0x40000000&((data)<<30))
#define VP8_P2_VP8_P2_FRM1_write_enable7_src(data)                                   ((0x40000000&(data))>>30)
#define VP8_P2_VP8_P2_FRM1_get_write_enable7(data)                                   ((0x40000000&(data))>>30)
#define VP8_P2_VP8_P2_FRM1_slice_cnt_shift                                           (22)
#define VP8_P2_VP8_P2_FRM1_slice_cnt_mask                                            (0x3FC00000)
#define VP8_P2_VP8_P2_FRM1_slice_cnt(data)                                           (0x3FC00000&((data)<<22))
#define VP8_P2_VP8_P2_FRM1_slice_cnt_src(data)                                       ((0x3FC00000&(data))>>22)
#define VP8_P2_VP8_P2_FRM1_get_slice_cnt(data)                                       ((0x3FC00000&(data))>>22)
#define VP8_P2_VP8_P2_FRM1_write_enable6_shift                                       (21)
#define VP8_P2_VP8_P2_FRM1_write_enable6_mask                                        (0x00200000)
#define VP8_P2_VP8_P2_FRM1_write_enable6(data)                                       (0x00200000&((data)<<21))
#define VP8_P2_VP8_P2_FRM1_write_enable6_src(data)                                   ((0x00200000&(data))>>21)
#define VP8_P2_VP8_P2_FRM1_get_write_enable6(data)                                   ((0x00200000&(data))>>21)
#define VP8_P2_VP8_P2_FRM1_full_pixel_shift                                          (20)
#define VP8_P2_VP8_P2_FRM1_full_pixel_mask                                           (0x00100000)
#define VP8_P2_VP8_P2_FRM1_full_pixel(data)                                          (0x00100000&((data)<<20))
#define VP8_P2_VP8_P2_FRM1_full_pixel_src(data)                                      ((0x00100000&(data))>>20)
#define VP8_P2_VP8_P2_FRM1_get_full_pixel(data)                                      ((0x00100000&(data))>>20)
#define VP8_P2_VP8_P2_FRM1_write_enable5_shift                                       (19)
#define VP8_P2_VP8_P2_FRM1_write_enable5_mask                                        (0x00080000)
#define VP8_P2_VP8_P2_FRM1_write_enable5(data)                                       (0x00080000&((data)<<19))
#define VP8_P2_VP8_P2_FRM1_write_enable5_src(data)                                   ((0x00080000&(data))>>19)
#define VP8_P2_VP8_P2_FRM1_get_write_enable5(data)                                   ((0x00080000&(data))>>19)
#define VP8_P2_VP8_P2_FRM1_ref_frame_sign_bias_shift                                 (15)
#define VP8_P2_VP8_P2_FRM1_ref_frame_sign_bias_mask                                  (0x00078000)
#define VP8_P2_VP8_P2_FRM1_ref_frame_sign_bias(data)                                 (0x00078000&((data)<<15))
#define VP8_P2_VP8_P2_FRM1_ref_frame_sign_bias_src(data)                             ((0x00078000&(data))>>15)
#define VP8_P2_VP8_P2_FRM1_get_ref_frame_sign_bias(data)                             ((0x00078000&(data))>>15)
#define VP8_P2_VP8_P2_FRM1_write_enable4_shift                                       (14)
#define VP8_P2_VP8_P2_FRM1_write_enable4_mask                                        (0x00004000)
#define VP8_P2_VP8_P2_FRM1_write_enable4(data)                                       (0x00004000&((data)<<14))
#define VP8_P2_VP8_P2_FRM1_write_enable4_src(data)                                   ((0x00004000&(data))>>14)
#define VP8_P2_VP8_P2_FRM1_get_write_enable4(data)                                   ((0x00004000&(data))>>14)
#define VP8_P2_VP8_P2_FRM1_mb_no_coeff_skip_shift                                    (13)
#define VP8_P2_VP8_P2_FRM1_mb_no_coeff_skip_mask                                     (0x00002000)
#define VP8_P2_VP8_P2_FRM1_mb_no_coeff_skip(data)                                    (0x00002000&((data)<<13))
#define VP8_P2_VP8_P2_FRM1_mb_no_coeff_skip_src(data)                                ((0x00002000&(data))>>13)
#define VP8_P2_VP8_P2_FRM1_get_mb_no_coeff_skip(data)                                ((0x00002000&(data))>>13)
#define VP8_P2_VP8_P2_FRM1_write_enable3_shift                                       (12)
#define VP8_P2_VP8_P2_FRM1_write_enable3_mask                                        (0x00001000)
#define VP8_P2_VP8_P2_FRM1_write_enable3(data)                                       (0x00001000&((data)<<12))
#define VP8_P2_VP8_P2_FRM1_write_enable3_src(data)                                   ((0x00001000&(data))>>12)
#define VP8_P2_VP8_P2_FRM1_get_write_enable3(data)                                   ((0x00001000&(data))>>12)
#define VP8_P2_VP8_P2_FRM1_segmentation_enabled_shift                                (11)
#define VP8_P2_VP8_P2_FRM1_segmentation_enabled_mask                                 (0x00000800)
#define VP8_P2_VP8_P2_FRM1_segmentation_enabled(data)                                (0x00000800&((data)<<11))
#define VP8_P2_VP8_P2_FRM1_segmentation_enabled_src(data)                            ((0x00000800&(data))>>11)
#define VP8_P2_VP8_P2_FRM1_get_segmentation_enabled(data)                            ((0x00000800&(data))>>11)
#define VP8_P2_VP8_P2_FRM1_write_enable2_shift                                       (10)
#define VP8_P2_VP8_P2_FRM1_write_enable2_mask                                        (0x00000400)
#define VP8_P2_VP8_P2_FRM1_write_enable2(data)                                       (0x00000400&((data)<<10))
#define VP8_P2_VP8_P2_FRM1_write_enable2_src(data)                                   ((0x00000400&(data))>>10)
#define VP8_P2_VP8_P2_FRM1_get_write_enable2(data)                                   ((0x00000400&(data))>>10)
#define VP8_P2_VP8_P2_FRM1_update_mb_segmentation_map_shift                          (9)
#define VP8_P2_VP8_P2_FRM1_update_mb_segmentation_map_mask                           (0x00000200)
#define VP8_P2_VP8_P2_FRM1_update_mb_segmentation_map(data)                          (0x00000200&((data)<<9))
#define VP8_P2_VP8_P2_FRM1_update_mb_segmentation_map_src(data)                      ((0x00000200&(data))>>9)
#define VP8_P2_VP8_P2_FRM1_get_update_mb_segmentation_map(data)                      ((0x00000200&(data))>>9)
#define VP8_P2_VP8_P2_FRM1_write_enable1_shift                                       (8)
#define VP8_P2_VP8_P2_FRM1_write_enable1_mask                                        (0x00000100)
#define VP8_P2_VP8_P2_FRM1_write_enable1(data)                                       (0x00000100&((data)<<8))
#define VP8_P2_VP8_P2_FRM1_write_enable1_src(data)                                   ((0x00000100&(data))>>8)
#define VP8_P2_VP8_P2_FRM1_get_write_enable1(data)                                   ((0x00000100&(data))>>8)
#define VP8_P2_VP8_P2_FRM1_prob_skip_false_shift                                     (0)
#define VP8_P2_VP8_P2_FRM1_prob_skip_false_mask                                      (0x000000FF)
#define VP8_P2_VP8_P2_FRM1_prob_skip_false(data)                                     (0x000000FF&((data)<<0))
#define VP8_P2_VP8_P2_FRM1_prob_skip_false_src(data)                                 ((0x000000FF&(data))>>0)
#define VP8_P2_VP8_P2_FRM1_get_prob_skip_false(data)                                 ((0x000000FF&(data))>>0)


#define VP8_P2_VP8_P2_FRM2                                                           0x1800EF04
#define VP8_P2_VP8_P2_FRM2_reg_addr                                                  "0xB800EF04"
#define VP8_P2_VP8_P2_FRM2_reg                                                       0xB800EF04
#define set_VP8_P2_VP8_P2_FRM2_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_P2_FRM2_reg)=data)
#define get_VP8_P2_VP8_P2_FRM2_reg   (*((volatile unsigned int*) VP8_P2_VP8_P2_FRM2_reg))
#define VP8_P2_VP8_P2_FRM2_inst_adr                                                  "0x00C1"
#define VP8_P2_VP8_P2_FRM2_inst                                                      0x00C1
#define VP8_P2_VP8_P2_FRM2_write_enable3_shift                                       (26)
#define VP8_P2_VP8_P2_FRM2_write_enable3_mask                                        (0x04000000)
#define VP8_P2_VP8_P2_FRM2_write_enable3(data)                                       (0x04000000&((data)<<26))
#define VP8_P2_VP8_P2_FRM2_write_enable3_src(data)                                   ((0x04000000&(data))>>26)
#define VP8_P2_VP8_P2_FRM2_get_write_enable3(data)                                   ((0x04000000&(data))>>26)
#define VP8_P2_VP8_P2_FRM2_prob_gf_shift                                             (18)
#define VP8_P2_VP8_P2_FRM2_prob_gf_mask                                              (0x03FC0000)
#define VP8_P2_VP8_P2_FRM2_prob_gf(data)                                             (0x03FC0000&((data)<<18))
#define VP8_P2_VP8_P2_FRM2_prob_gf_src(data)                                         ((0x03FC0000&(data))>>18)
#define VP8_P2_VP8_P2_FRM2_get_prob_gf(data)                                         ((0x03FC0000&(data))>>18)
#define VP8_P2_VP8_P2_FRM2_write_enable2_shift                                       (17)
#define VP8_P2_VP8_P2_FRM2_write_enable2_mask                                        (0x00020000)
#define VP8_P2_VP8_P2_FRM2_write_enable2(data)                                       (0x00020000&((data)<<17))
#define VP8_P2_VP8_P2_FRM2_write_enable2_src(data)                                   ((0x00020000&(data))>>17)
#define VP8_P2_VP8_P2_FRM2_get_write_enable2(data)                                   ((0x00020000&(data))>>17)
#define VP8_P2_VP8_P2_FRM2_prob_last_shift                                           (9)
#define VP8_P2_VP8_P2_FRM2_prob_last_mask                                            (0x0001FE00)
#define VP8_P2_VP8_P2_FRM2_prob_last(data)                                           (0x0001FE00&((data)<<9))
#define VP8_P2_VP8_P2_FRM2_prob_last_src(data)                                       ((0x0001FE00&(data))>>9)
#define VP8_P2_VP8_P2_FRM2_get_prob_last(data)                                       ((0x0001FE00&(data))>>9)
#define VP8_P2_VP8_P2_FRM2_write_enable1_shift                                       (8)
#define VP8_P2_VP8_P2_FRM2_write_enable1_mask                                        (0x00000100)
#define VP8_P2_VP8_P2_FRM2_write_enable1(data)                                       (0x00000100&((data)<<8))
#define VP8_P2_VP8_P2_FRM2_write_enable1_src(data)                                   ((0x00000100&(data))>>8)
#define VP8_P2_VP8_P2_FRM2_get_write_enable1(data)                                   ((0x00000100&(data))>>8)
#define VP8_P2_VP8_P2_FRM2_prob_intra_shift                                          (0)
#define VP8_P2_VP8_P2_FRM2_prob_intra_mask                                           (0x000000FF)
#define VP8_P2_VP8_P2_FRM2_prob_intra(data)                                          (0x000000FF&((data)<<0))
#define VP8_P2_VP8_P2_FRM2_prob_intra_src(data)                                      ((0x000000FF&(data))>>0)
#define VP8_P2_VP8_P2_FRM2_get_prob_intra(data)                                      ((0x000000FF&(data))>>0)


#define VP8_P2_VP8_P2_FRM3                                                           0x1800EF08
#define VP8_P2_VP8_P2_FRM3_reg_addr                                                  "0xB800EF08"
#define VP8_P2_VP8_P2_FRM3_reg                                                       0xB800EF08
#define set_VP8_P2_VP8_P2_FRM3_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_P2_FRM3_reg)=data)
#define get_VP8_P2_VP8_P2_FRM3_reg   (*((volatile unsigned int*) VP8_P2_VP8_P2_FRM3_reg))
#define VP8_P2_VP8_P2_FRM3_inst_adr                                                  "0x00C2"
#define VP8_P2_VP8_P2_FRM3_inst                                                      0x00C2
#define VP8_P2_VP8_P2_FRM3_write_enable1_shift                                       (7)
#define VP8_P2_VP8_P2_FRM3_write_enable1_mask                                        (0x00000080)
#define VP8_P2_VP8_P2_FRM3_write_enable1(data)                                       (0x00000080&((data)<<7))
#define VP8_P2_VP8_P2_FRM3_write_enable1_src(data)                                   ((0x00000080&(data))>>7)
#define VP8_P2_VP8_P2_FRM3_get_write_enable1(data)                                   ((0x00000080&(data))>>7)
#define VP8_P2_VP8_P2_FRM3_picmb_h_shift                                             (0)
#define VP8_P2_VP8_P2_FRM3_picmb_h_mask                                              (0x0000007F)
#define VP8_P2_VP8_P2_FRM3_picmb_h(data)                                             (0x0000007F&((data)<<0))
#define VP8_P2_VP8_P2_FRM3_picmb_h_src(data)                                         ((0x0000007F&(data))>>0)
#define VP8_P2_VP8_P2_FRM3_get_picmb_h(data)                                         ((0x0000007F&(data))>>0)


#define VP8_P2_VP8_P2_MB1                                                            0x1800EF0C
#define VP8_P2_VP8_P2_MB1_reg_addr                                                   "0xB800EF0C"
#define VP8_P2_VP8_P2_MB1_reg                                                        0xB800EF0C
#define set_VP8_P2_VP8_P2_MB1_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_P2_MB1_reg)=data)
#define get_VP8_P2_VP8_P2_MB1_reg   (*((volatile unsigned int*) VP8_P2_VP8_P2_MB1_reg))
#define VP8_P2_VP8_P2_MB1_inst_adr                                                   "0x00C3"
#define VP8_P2_VP8_P2_MB1_inst                                                       0x00C3
#define VP8_P2_VP8_P2_MB1_need_to_clamp_mvs_shift                                    (11)
#define VP8_P2_VP8_P2_MB1_need_to_clamp_mvs_mask                                     (0x00000800)
#define VP8_P2_VP8_P2_MB1_need_to_clamp_mvs(data)                                    (0x00000800&((data)<<11))
#define VP8_P2_VP8_P2_MB1_need_to_clamp_mvs_src(data)                                ((0x00000800&(data))>>11)
#define VP8_P2_VP8_P2_MB1_get_need_to_clamp_mvs(data)                                ((0x00000800&(data))>>11)
#define VP8_P2_VP8_P2_MB1_ref_frame_shift                                            (9)
#define VP8_P2_VP8_P2_MB1_ref_frame_mask                                             (0x00000600)
#define VP8_P2_VP8_P2_MB1_ref_frame(data)                                            (0x00000600&((data)<<9))
#define VP8_P2_VP8_P2_MB1_ref_frame_src(data)                                        ((0x00000600&(data))>>9)
#define VP8_P2_VP8_P2_MB1_get_ref_frame(data)                                        ((0x00000600&(data))>>9)
#define VP8_P2_VP8_P2_MB1_uv_mode_shift                                              (7)
#define VP8_P2_VP8_P2_MB1_uv_mode_mask                                               (0x00000180)
#define VP8_P2_VP8_P2_MB1_uv_mode(data)                                              (0x00000180&((data)<<7))
#define VP8_P2_VP8_P2_MB1_uv_mode_src(data)                                          ((0x00000180&(data))>>7)
#define VP8_P2_VP8_P2_MB1_get_uv_mode(data)                                          ((0x00000180&(data))>>7)
#define VP8_P2_VP8_P2_MB1_mode_shift                                                 (3)
#define VP8_P2_VP8_P2_MB1_mode_mask                                                  (0x00000078)
#define VP8_P2_VP8_P2_MB1_mode(data)                                                 (0x00000078&((data)<<3))
#define VP8_P2_VP8_P2_MB1_mode_src(data)                                             ((0x00000078&(data))>>3)
#define VP8_P2_VP8_P2_MB1_get_mode(data)                                             ((0x00000078&(data))>>3)
#define VP8_P2_VP8_P2_MB1_mb_skip_coeff_shift                                        (2)
#define VP8_P2_VP8_P2_MB1_mb_skip_coeff_mask                                         (0x00000004)
#define VP8_P2_VP8_P2_MB1_mb_skip_coeff(data)                                        (0x00000004&((data)<<2))
#define VP8_P2_VP8_P2_MB1_mb_skip_coeff_src(data)                                    ((0x00000004&(data))>>2)
#define VP8_P2_VP8_P2_MB1_get_mb_skip_coeff(data)                                    ((0x00000004&(data))>>2)
#define VP8_P2_VP8_P2_MB1_segment_id_shift                                           (0)
#define VP8_P2_VP8_P2_MB1_segment_id_mask                                            (0x00000003)
#define VP8_P2_VP8_P2_MB1_segment_id(data)                                           (0x00000003&((data)<<0))
#define VP8_P2_VP8_P2_MB1_segment_id_src(data)                                       ((0x00000003&(data))>>0)
#define VP8_P2_VP8_P2_MB1_get_segment_id(data)                                       ((0x00000003&(data))>>0)


#define VP8_P2_VP8_P2_MB2                                                            0x1800EF10
#define VP8_P2_VP8_P2_MB2_reg_addr                                                   "0xB800EF10"
#define VP8_P2_VP8_P2_MB2_reg                                                        0xB800EF10
#define set_VP8_P2_VP8_P2_MB2_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_P2_MB2_reg)=data)
#define get_VP8_P2_VP8_P2_MB2_reg   (*((volatile unsigned int*) VP8_P2_VP8_P2_MB2_reg))
#define VP8_P2_VP8_P2_MB2_inst_adr                                                   "0x00C4"
#define VP8_P2_VP8_P2_MB2_inst                                                       0x00C4
#define VP8_P2_VP8_P2_MB2_write_enable3_shift                                        (26)
#define VP8_P2_VP8_P2_MB2_write_enable3_mask                                         (0x04000000)
#define VP8_P2_VP8_P2_MB2_write_enable3(data)                                        (0x04000000&((data)<<26))
#define VP8_P2_VP8_P2_MB2_write_enable3_src(data)                                    ((0x04000000&(data))>>26)
#define VP8_P2_VP8_P2_MB2_get_write_enable3(data)                                    ((0x04000000&(data))>>26)
#define VP8_P2_VP8_P2_MB2_ndb_p2_flush_shift                                         (25)
#define VP8_P2_VP8_P2_MB2_ndb_p2_flush_mask                                          (0x02000000)
#define VP8_P2_VP8_P2_MB2_ndb_p2_flush(data)                                         (0x02000000&((data)<<25))
#define VP8_P2_VP8_P2_MB2_ndb_p2_flush_src(data)                                     ((0x02000000&(data))>>25)
#define VP8_P2_VP8_P2_MB2_get_ndb_p2_flush(data)                                     ((0x02000000&(data))>>25)
#define VP8_P2_VP8_P2_MB2_write_enable2_shift                                        (24)
#define VP8_P2_VP8_P2_MB2_write_enable2_mask                                         (0x01000000)
#define VP8_P2_VP8_P2_MB2_write_enable2(data)                                        (0x01000000&((data)<<24))
#define VP8_P2_VP8_P2_MB2_write_enable2_src(data)                                    ((0x01000000&(data))>>24)
#define VP8_P2_VP8_P2_MB2_get_write_enable2(data)                                    ((0x01000000&(data))>>24)
#define VP8_P2_VP8_P2_MB2_mby_shift                                                  (17)
#define VP8_P2_VP8_P2_MB2_mby_mask                                                   (0x00FE0000)
#define VP8_P2_VP8_P2_MB2_mby(data)                                                  (0x00FE0000&((data)<<17))
#define VP8_P2_VP8_P2_MB2_mby_src(data)                                              ((0x00FE0000&(data))>>17)
#define VP8_P2_VP8_P2_MB2_get_mby(data)                                              ((0x00FE0000&(data))>>17)
#define VP8_P2_VP8_P2_MB2_write_enable1_shift                                        (16)
#define VP8_P2_VP8_P2_MB2_write_enable1_mask                                         (0x00010000)
#define VP8_P2_VP8_P2_MB2_write_enable1(data)                                        (0x00010000&((data)<<16))
#define VP8_P2_VP8_P2_MB2_write_enable1_src(data)                                    ((0x00010000&(data))>>16)
#define VP8_P2_VP8_P2_MB2_get_write_enable1(data)                                    ((0x00010000&(data))>>16)
#define VP8_P2_VP8_P2_MB2_left_sub_block_mode_shift                                  (0)
#define VP8_P2_VP8_P2_MB2_left_sub_block_mode_mask                                   (0x0000FFFF)
#define VP8_P2_VP8_P2_MB2_left_sub_block_mode(data)                                  (0x0000FFFF&((data)<<0))
#define VP8_P2_VP8_P2_MB2_left_sub_block_mode_src(data)                              ((0x0000FFFF&(data))>>0)
#define VP8_P2_VP8_P2_MB2_get_left_sub_block_mode(data)                              ((0x0000FFFF&(data))>>0)


#define VP8_P2_VP8_P2_SUB_BLK0                                                       0x1800EF14
#define VP8_P2_VP8_P2_SUB_BLK0_reg_addr                                              "0xB800EF14"
#define VP8_P2_VP8_P2_SUB_BLK0_reg                                                   0xB800EF14
#define set_VP8_P2_VP8_P2_SUB_BLK0_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_P2_SUB_BLK0_reg)=data)
#define get_VP8_P2_VP8_P2_SUB_BLK0_reg   (*((volatile unsigned int*) VP8_P2_VP8_P2_SUB_BLK0_reg))
#define VP8_P2_VP8_P2_SUB_BLK0_inst_adr                                              "0x00C5"
#define VP8_P2_VP8_P2_SUB_BLK0_inst                                                  0x00C5
#define VP8_P2_VP8_P2_SUB_BLK0_sub_blk_mode_p0_shift                                 (0)
#define VP8_P2_VP8_P2_SUB_BLK0_sub_blk_mode_p0_mask                                  (0xFFFFFFFF)
#define VP8_P2_VP8_P2_SUB_BLK0_sub_blk_mode_p0(data)                                 (0xFFFFFFFF&((data)<<0))
#define VP8_P2_VP8_P2_SUB_BLK0_sub_blk_mode_p0_src(data)                             ((0xFFFFFFFF&(data))>>0)
#define VP8_P2_VP8_P2_SUB_BLK0_get_sub_blk_mode_p0(data)                             ((0xFFFFFFFF&(data))>>0)


#define VP8_P2_VP8_P2_SUB_BLK1                                                       0x1800EF18
#define VP8_P2_VP8_P2_SUB_BLK1_reg_addr                                              "0xB800EF18"
#define VP8_P2_VP8_P2_SUB_BLK1_reg                                                   0xB800EF18
#define set_VP8_P2_VP8_P2_SUB_BLK1_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_P2_SUB_BLK1_reg)=data)
#define get_VP8_P2_VP8_P2_SUB_BLK1_reg   (*((volatile unsigned int*) VP8_P2_VP8_P2_SUB_BLK1_reg))
#define VP8_P2_VP8_P2_SUB_BLK1_inst_adr                                              "0x00C6"
#define VP8_P2_VP8_P2_SUB_BLK1_inst                                                  0x00C6
#define VP8_P2_VP8_P2_SUB_BLK1_sub_blk_mode_p1_shift                                 (0)
#define VP8_P2_VP8_P2_SUB_BLK1_sub_blk_mode_p1_mask                                  (0xFFFFFFFF)
#define VP8_P2_VP8_P2_SUB_BLK1_sub_blk_mode_p1(data)                                 (0xFFFFFFFF&((data)<<0))
#define VP8_P2_VP8_P2_SUB_BLK1_sub_blk_mode_p1_src(data)                             ((0xFFFFFFFF&(data))>>0)
#define VP8_P2_VP8_P2_SUB_BLK1_get_sub_blk_mode_p1(data)                             ((0xFFFFFFFF&(data))>>0)


#define VP8_P2_VP8_P2_MB_INFO                                                        0x1800EF1C
#define VP8_P2_VP8_P2_MB_INFO_reg_addr                                               "0xB800EF1C"
#define VP8_P2_VP8_P2_MB_INFO_reg                                                    0xB800EF1C
#define set_VP8_P2_VP8_P2_MB_INFO_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_P2_MB_INFO_reg)=data)
#define get_VP8_P2_VP8_P2_MB_INFO_reg   (*((volatile unsigned int*) VP8_P2_VP8_P2_MB_INFO_reg))
#define VP8_P2_VP8_P2_MB_INFO_inst_adr                                               "0x00C7"
#define VP8_P2_VP8_P2_MB_INFO_inst                                                   0x00C7
#define VP8_P2_VP8_P2_MB_INFO_vp8_p2_curmb_shift                                     (17)
#define VP8_P2_VP8_P2_MB_INFO_vp8_p2_curmb_mask                                      (0x03FE0000)
#define VP8_P2_VP8_P2_MB_INFO_vp8_p2_curmb(data)                                     (0x03FE0000&((data)<<17))
#define VP8_P2_VP8_P2_MB_INFO_vp8_p2_curmb_src(data)                                 ((0x03FE0000&(data))>>17)
#define VP8_P2_VP8_P2_MB_INFO_get_vp8_p2_curmb(data)                                 ((0x03FE0000&(data))>>17)
#define VP8_P2_VP8_P2_MB_INFO_vp8_mbpartition_shift                                  (8)
#define VP8_P2_VP8_P2_MB_INFO_vp8_mbpartition_mask                                   (0x0001FF00)
#define VP8_P2_VP8_P2_MB_INFO_vp8_mbpartition(data)                                  (0x0001FF00&((data)<<8))
#define VP8_P2_VP8_P2_MB_INFO_vp8_mbpartition_src(data)                              ((0x0001FF00&(data))>>8)
#define VP8_P2_VP8_P2_MB_INFO_get_vp8_mbpartition(data)                              ((0x0001FF00&(data))>>8)
#define VP8_P2_VP8_P2_MB_INFO_vp8_Inter_pred_option_shift                            (0)
#define VP8_P2_VP8_P2_MB_INFO_vp8_Inter_pred_option_mask                             (0x000000FF)
#define VP8_P2_VP8_P2_MB_INFO_vp8_Inter_pred_option(data)                            (0x000000FF&((data)<<0))
#define VP8_P2_VP8_P2_MB_INFO_vp8_Inter_pred_option_src(data)                        ((0x000000FF&(data))>>0)
#define VP8_P2_VP8_P2_MB_INFO_get_vp8_Inter_pred_option(data)                        ((0x000000FF&(data))>>0)


#define VP8_P2_VP8_BAC                                                               0x1800EF20
#define VP8_P2_VP8_BAC_reg_addr                                                      "0xB800EF20"
#define VP8_P2_VP8_BAC_reg                                                           0xB800EF20
#define set_VP8_P2_VP8_BAC_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_BAC_reg)=data)
#define get_VP8_P2_VP8_BAC_reg   (*((volatile unsigned int*) VP8_P2_VP8_BAC_reg))
#define VP8_P2_VP8_BAC_inst_adr                                                      "0x00C8"
#define VP8_P2_VP8_BAC_inst                                                          0x00C8
#define VP8_P2_VP8_BAC_high_shift                                                    (20)
#define VP8_P2_VP8_BAC_high_mask                                                     (0x1FF00000)
#define VP8_P2_VP8_BAC_high(data)                                                    (0x1FF00000&((data)<<20))
#define VP8_P2_VP8_BAC_high_src(data)                                                ((0x1FF00000&(data))>>20)
#define VP8_P2_VP8_BAC_get_high(data)                                                ((0x1FF00000&(data))>>20)
#define VP8_P2_VP8_BAC_bits_shift                                                    (16)
#define VP8_P2_VP8_BAC_bits_mask                                                     (0x000F0000)
#define VP8_P2_VP8_BAC_bits(data)                                                    (0x000F0000&((data)<<16))
#define VP8_P2_VP8_BAC_bits_src(data)                                                ((0x000F0000&(data))>>16)
#define VP8_P2_VP8_BAC_get_bits(data)                                                ((0x000F0000&(data))>>16)
#define VP8_P2_VP8_BAC_code_word_shift                                               (0)
#define VP8_P2_VP8_BAC_code_word_mask                                                (0x0000FFFF)
#define VP8_P2_VP8_BAC_code_word(data)                                               (0x0000FFFF&((data)<<0))
#define VP8_P2_VP8_BAC_code_word_src(data)                                           ((0x0000FFFF&(data))>>0)
#define VP8_P2_VP8_BAC_get_code_word(data)                                           ((0x0000FFFF&(data))>>0)


#define VP8_P2_VP8_MB_MV0                                                            0x1800EF24
#define VP8_P2_VP8_MB_MV0_reg_addr                                                   "0xB800EF24"
#define VP8_P2_VP8_MB_MV0_reg                                                        0xB800EF24
#define set_VP8_P2_VP8_MB_MV0_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV0_reg)=data)
#define get_VP8_P2_VP8_MB_MV0_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV0_reg))
#define VP8_P2_VP8_MB_MV0_inst_adr                                                   "0x00C9"
#define VP8_P2_VP8_MB_MV0_inst                                                       0x00C9
#define VP8_P2_VP8_MB_MV0_mv_x_shift                                                 (14)
#define VP8_P2_VP8_MB_MV0_mv_x_mask                                                  (0x1FFFC000)
#define VP8_P2_VP8_MB_MV0_mv_x(data)                                                 (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV0_mv_x_src(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV0_get_mv_x(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV0_mv_y_shift                                                 (0)
#define VP8_P2_VP8_MB_MV0_mv_y_mask                                                  (0x00003FFF)
#define VP8_P2_VP8_MB_MV0_mv_y(data)                                                 (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV0_mv_y_src(data)                                             ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV0_get_mv_y(data)                                             ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV1                                                            0x1800EF28
#define VP8_P2_VP8_MB_MV1_reg_addr                                                   "0xB800EF28"
#define VP8_P2_VP8_MB_MV1_reg                                                        0xB800EF28
#define set_VP8_P2_VP8_MB_MV1_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV1_reg)=data)
#define get_VP8_P2_VP8_MB_MV1_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV1_reg))
#define VP8_P2_VP8_MB_MV1_inst_adr                                                   "0x00CA"
#define VP8_P2_VP8_MB_MV1_inst                                                       0x00CA
#define VP8_P2_VP8_MB_MV1_mv_x_shift                                                 (14)
#define VP8_P2_VP8_MB_MV1_mv_x_mask                                                  (0x1FFFC000)
#define VP8_P2_VP8_MB_MV1_mv_x(data)                                                 (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV1_mv_x_src(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV1_get_mv_x(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV1_mv_y_shift                                                 (0)
#define VP8_P2_VP8_MB_MV1_mv_y_mask                                                  (0x00003FFF)
#define VP8_P2_VP8_MB_MV1_mv_y(data)                                                 (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV1_mv_y_src(data)                                             ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV1_get_mv_y(data)                                             ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV2                                                            0x1800EF2C
#define VP8_P2_VP8_MB_MV2_reg_addr                                                   "0xB800EF2C"
#define VP8_P2_VP8_MB_MV2_reg                                                        0xB800EF2C
#define set_VP8_P2_VP8_MB_MV2_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV2_reg)=data)
#define get_VP8_P2_VP8_MB_MV2_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV2_reg))
#define VP8_P2_VP8_MB_MV2_inst_adr                                                   "0x00CB"
#define VP8_P2_VP8_MB_MV2_inst                                                       0x00CB
#define VP8_P2_VP8_MB_MV2_mv_x_shift                                                 (14)
#define VP8_P2_VP8_MB_MV2_mv_x_mask                                                  (0x1FFFC000)
#define VP8_P2_VP8_MB_MV2_mv_x(data)                                                 (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV2_mv_x_src(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV2_get_mv_x(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV2_mv_y_shift                                                 (0)
#define VP8_P2_VP8_MB_MV2_mv_y_mask                                                  (0x00003FFF)
#define VP8_P2_VP8_MB_MV2_mv_y(data)                                                 (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV2_mv_y_src(data)                                             ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV2_get_mv_y(data)                                             ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV3                                                            0x1800EF30
#define VP8_P2_VP8_MB_MV3_reg_addr                                                   "0xB800EF30"
#define VP8_P2_VP8_MB_MV3_reg                                                        0xB800EF30
#define set_VP8_P2_VP8_MB_MV3_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV3_reg)=data)
#define get_VP8_P2_VP8_MB_MV3_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV3_reg))
#define VP8_P2_VP8_MB_MV3_inst_adr                                                   "0x00CC"
#define VP8_P2_VP8_MB_MV3_inst                                                       0x00CC
#define VP8_P2_VP8_MB_MV3_mv_x_shift                                                 (14)
#define VP8_P2_VP8_MB_MV3_mv_x_mask                                                  (0x1FFFC000)
#define VP8_P2_VP8_MB_MV3_mv_x(data)                                                 (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV3_mv_x_src(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV3_get_mv_x(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV3_mv_y_shift                                                 (0)
#define VP8_P2_VP8_MB_MV3_mv_y_mask                                                  (0x00003FFF)
#define VP8_P2_VP8_MB_MV3_mv_y(data)                                                 (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV3_mv_y_src(data)                                             ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV3_get_mv_y(data)                                             ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV4                                                            0x1800EF34
#define VP8_P2_VP8_MB_MV4_reg_addr                                                   "0xB800EF34"
#define VP8_P2_VP8_MB_MV4_reg                                                        0xB800EF34
#define set_VP8_P2_VP8_MB_MV4_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV4_reg)=data)
#define get_VP8_P2_VP8_MB_MV4_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV4_reg))
#define VP8_P2_VP8_MB_MV4_inst_adr                                                   "0x00CD"
#define VP8_P2_VP8_MB_MV4_inst                                                       0x00CD
#define VP8_P2_VP8_MB_MV4_mv_x_shift                                                 (14)
#define VP8_P2_VP8_MB_MV4_mv_x_mask                                                  (0x1FFFC000)
#define VP8_P2_VP8_MB_MV4_mv_x(data)                                                 (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV4_mv_x_src(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV4_get_mv_x(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV4_mv_y_shift                                                 (0)
#define VP8_P2_VP8_MB_MV4_mv_y_mask                                                  (0x00003FFF)
#define VP8_P2_VP8_MB_MV4_mv_y(data)                                                 (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV4_mv_y_src(data)                                             ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV4_get_mv_y(data)                                             ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV5                                                            0x1800EF38
#define VP8_P2_VP8_MB_MV5_reg_addr                                                   "0xB800EF38"
#define VP8_P2_VP8_MB_MV5_reg                                                        0xB800EF38
#define set_VP8_P2_VP8_MB_MV5_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV5_reg)=data)
#define get_VP8_P2_VP8_MB_MV5_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV5_reg))
#define VP8_P2_VP8_MB_MV5_inst_adr                                                   "0x00CE"
#define VP8_P2_VP8_MB_MV5_inst                                                       0x00CE
#define VP8_P2_VP8_MB_MV5_mv_x_shift                                                 (14)
#define VP8_P2_VP8_MB_MV5_mv_x_mask                                                  (0x1FFFC000)
#define VP8_P2_VP8_MB_MV5_mv_x(data)                                                 (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV5_mv_x_src(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV5_get_mv_x(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV5_mv_y_shift                                                 (0)
#define VP8_P2_VP8_MB_MV5_mv_y_mask                                                  (0x00003FFF)
#define VP8_P2_VP8_MB_MV5_mv_y(data)                                                 (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV5_mv_y_src(data)                                             ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV5_get_mv_y(data)                                             ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV6                                                            0x1800EF3C
#define VP8_P2_VP8_MB_MV6_reg_addr                                                   "0xB800EF3C"
#define VP8_P2_VP8_MB_MV6_reg                                                        0xB800EF3C
#define set_VP8_P2_VP8_MB_MV6_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV6_reg)=data)
#define get_VP8_P2_VP8_MB_MV6_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV6_reg))
#define VP8_P2_VP8_MB_MV6_inst_adr                                                   "0x00CF"
#define VP8_P2_VP8_MB_MV6_inst                                                       0x00CF
#define VP8_P2_VP8_MB_MV6_mv_x_shift                                                 (14)
#define VP8_P2_VP8_MB_MV6_mv_x_mask                                                  (0x1FFFC000)
#define VP8_P2_VP8_MB_MV6_mv_x(data)                                                 (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV6_mv_x_src(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV6_get_mv_x(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV6_mv_y_shift                                                 (0)
#define VP8_P2_VP8_MB_MV6_mv_y_mask                                                  (0x00003FFF)
#define VP8_P2_VP8_MB_MV6_mv_y(data)                                                 (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV6_mv_y_src(data)                                             ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV6_get_mv_y(data)                                             ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV7                                                            0x1800EF40
#define VP8_P2_VP8_MB_MV7_reg_addr                                                   "0xB800EF40"
#define VP8_P2_VP8_MB_MV7_reg                                                        0xB800EF40
#define set_VP8_P2_VP8_MB_MV7_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV7_reg)=data)
#define get_VP8_P2_VP8_MB_MV7_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV7_reg))
#define VP8_P2_VP8_MB_MV7_inst_adr                                                   "0x00D0"
#define VP8_P2_VP8_MB_MV7_inst                                                       0x00D0
#define VP8_P2_VP8_MB_MV7_mv_x_shift                                                 (14)
#define VP8_P2_VP8_MB_MV7_mv_x_mask                                                  (0x1FFFC000)
#define VP8_P2_VP8_MB_MV7_mv_x(data)                                                 (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV7_mv_x_src(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV7_get_mv_x(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV7_mv_y_shift                                                 (0)
#define VP8_P2_VP8_MB_MV7_mv_y_mask                                                  (0x00003FFF)
#define VP8_P2_VP8_MB_MV7_mv_y(data)                                                 (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV7_mv_y_src(data)                                             ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV7_get_mv_y(data)                                             ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV8                                                            0x1800EF44
#define VP8_P2_VP8_MB_MV8_reg_addr                                                   "0xB800EF44"
#define VP8_P2_VP8_MB_MV8_reg                                                        0xB800EF44
#define set_VP8_P2_VP8_MB_MV8_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV8_reg)=data)
#define get_VP8_P2_VP8_MB_MV8_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV8_reg))
#define VP8_P2_VP8_MB_MV8_inst_adr                                                   "0x00D1"
#define VP8_P2_VP8_MB_MV8_inst                                                       0x00D1
#define VP8_P2_VP8_MB_MV8_mv_x_shift                                                 (14)
#define VP8_P2_VP8_MB_MV8_mv_x_mask                                                  (0x1FFFC000)
#define VP8_P2_VP8_MB_MV8_mv_x(data)                                                 (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV8_mv_x_src(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV8_get_mv_x(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV8_mv_y_shift                                                 (0)
#define VP8_P2_VP8_MB_MV8_mv_y_mask                                                  (0x00003FFF)
#define VP8_P2_VP8_MB_MV8_mv_y(data)                                                 (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV8_mv_y_src(data)                                             ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV8_get_mv_y(data)                                             ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV9                                                            0x1800EF48
#define VP8_P2_VP8_MB_MV9_reg_addr                                                   "0xB800EF48"
#define VP8_P2_VP8_MB_MV9_reg                                                        0xB800EF48
#define set_VP8_P2_VP8_MB_MV9_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV9_reg)=data)
#define get_VP8_P2_VP8_MB_MV9_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV9_reg))
#define VP8_P2_VP8_MB_MV9_inst_adr                                                   "0x00D2"
#define VP8_P2_VP8_MB_MV9_inst                                                       0x00D2
#define VP8_P2_VP8_MB_MV9_mv_x_shift                                                 (14)
#define VP8_P2_VP8_MB_MV9_mv_x_mask                                                  (0x1FFFC000)
#define VP8_P2_VP8_MB_MV9_mv_x(data)                                                 (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV9_mv_x_src(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV9_get_mv_x(data)                                             ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV9_mv_y_shift                                                 (0)
#define VP8_P2_VP8_MB_MV9_mv_y_mask                                                  (0x00003FFF)
#define VP8_P2_VP8_MB_MV9_mv_y(data)                                                 (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV9_mv_y_src(data)                                             ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV9_get_mv_y(data)                                             ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV10                                                           0x1800EF4C
#define VP8_P2_VP8_MB_MV10_reg_addr                                                  "0xB800EF4C"
#define VP8_P2_VP8_MB_MV10_reg                                                       0xB800EF4C
#define set_VP8_P2_VP8_MB_MV10_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV10_reg)=data)
#define get_VP8_P2_VP8_MB_MV10_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV10_reg))
#define VP8_P2_VP8_MB_MV10_inst_adr                                                  "0x00D3"
#define VP8_P2_VP8_MB_MV10_inst                                                      0x00D3
#define VP8_P2_VP8_MB_MV10_mv_x_shift                                                (14)
#define VP8_P2_VP8_MB_MV10_mv_x_mask                                                 (0x1FFFC000)
#define VP8_P2_VP8_MB_MV10_mv_x(data)                                                (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV10_mv_x_src(data)                                            ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV10_get_mv_x(data)                                            ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV10_mv_y_shift                                                (0)
#define VP8_P2_VP8_MB_MV10_mv_y_mask                                                 (0x00003FFF)
#define VP8_P2_VP8_MB_MV10_mv_y(data)                                                (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV10_mv_y_src(data)                                            ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV10_get_mv_y(data)                                            ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV11                                                           0x1800EF50
#define VP8_P2_VP8_MB_MV11_reg_addr                                                  "0xB800EF50"
#define VP8_P2_VP8_MB_MV11_reg                                                       0xB800EF50
#define set_VP8_P2_VP8_MB_MV11_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV11_reg)=data)
#define get_VP8_P2_VP8_MB_MV11_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV11_reg))
#define VP8_P2_VP8_MB_MV11_inst_adr                                                  "0x00D4"
#define VP8_P2_VP8_MB_MV11_inst                                                      0x00D4
#define VP8_P2_VP8_MB_MV11_mv_x_shift                                                (14)
#define VP8_P2_VP8_MB_MV11_mv_x_mask                                                 (0x1FFFC000)
#define VP8_P2_VP8_MB_MV11_mv_x(data)                                                (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV11_mv_x_src(data)                                            ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV11_get_mv_x(data)                                            ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV11_mv_y_shift                                                (0)
#define VP8_P2_VP8_MB_MV11_mv_y_mask                                                 (0x00003FFF)
#define VP8_P2_VP8_MB_MV11_mv_y(data)                                                (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV11_mv_y_src(data)                                            ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV11_get_mv_y(data)                                            ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV12                                                           0x1800EF54
#define VP8_P2_VP8_MB_MV12_reg_addr                                                  "0xB800EF54"
#define VP8_P2_VP8_MB_MV12_reg                                                       0xB800EF54
#define set_VP8_P2_VP8_MB_MV12_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV12_reg)=data)
#define get_VP8_P2_VP8_MB_MV12_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV12_reg))
#define VP8_P2_VP8_MB_MV12_inst_adr                                                  "0x00D5"
#define VP8_P2_VP8_MB_MV12_inst                                                      0x00D5
#define VP8_P2_VP8_MB_MV12_mv_x_shift                                                (14)
#define VP8_P2_VP8_MB_MV12_mv_x_mask                                                 (0x1FFFC000)
#define VP8_P2_VP8_MB_MV12_mv_x(data)                                                (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV12_mv_x_src(data)                                            ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV12_get_mv_x(data)                                            ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV12_mv_y_shift                                                (0)
#define VP8_P2_VP8_MB_MV12_mv_y_mask                                                 (0x00003FFF)
#define VP8_P2_VP8_MB_MV12_mv_y(data)                                                (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV12_mv_y_src(data)                                            ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV12_get_mv_y(data)                                            ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV13                                                           0x1800EF58
#define VP8_P2_VP8_MB_MV13_reg_addr                                                  "0xB800EF58"
#define VP8_P2_VP8_MB_MV13_reg                                                       0xB800EF58
#define set_VP8_P2_VP8_MB_MV13_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV13_reg)=data)
#define get_VP8_P2_VP8_MB_MV13_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV13_reg))
#define VP8_P2_VP8_MB_MV13_inst_adr                                                  "0x00D6"
#define VP8_P2_VP8_MB_MV13_inst                                                      0x00D6
#define VP8_P2_VP8_MB_MV13_mv_x_shift                                                (14)
#define VP8_P2_VP8_MB_MV13_mv_x_mask                                                 (0x1FFFC000)
#define VP8_P2_VP8_MB_MV13_mv_x(data)                                                (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV13_mv_x_src(data)                                            ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV13_get_mv_x(data)                                            ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV13_mv_y_shift                                                (0)
#define VP8_P2_VP8_MB_MV13_mv_y_mask                                                 (0x00003FFF)
#define VP8_P2_VP8_MB_MV13_mv_y(data)                                                (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV13_mv_y_src(data)                                            ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV13_get_mv_y(data)                                            ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV14                                                           0x1800EF5C
#define VP8_P2_VP8_MB_MV14_reg_addr                                                  "0xB800EF5C"
#define VP8_P2_VP8_MB_MV14_reg                                                       0xB800EF5C
#define set_VP8_P2_VP8_MB_MV14_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV14_reg)=data)
#define get_VP8_P2_VP8_MB_MV14_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV14_reg))
#define VP8_P2_VP8_MB_MV14_inst_adr                                                  "0x00D7"
#define VP8_P2_VP8_MB_MV14_inst                                                      0x00D7
#define VP8_P2_VP8_MB_MV14_mv_x_shift                                                (14)
#define VP8_P2_VP8_MB_MV14_mv_x_mask                                                 (0x1FFFC000)
#define VP8_P2_VP8_MB_MV14_mv_x(data)                                                (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV14_mv_x_src(data)                                            ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV14_get_mv_x(data)                                            ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV14_mv_y_shift                                                (0)
#define VP8_P2_VP8_MB_MV14_mv_y_mask                                                 (0x00003FFF)
#define VP8_P2_VP8_MB_MV14_mv_y(data)                                                (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV14_mv_y_src(data)                                            ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV14_get_mv_y(data)                                            ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_MV15                                                           0x1800EF60
#define VP8_P2_VP8_MB_MV15_reg_addr                                                  "0xB800EF60"
#define VP8_P2_VP8_MB_MV15_reg                                                       0xB800EF60
#define set_VP8_P2_VP8_MB_MV15_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV15_reg)=data)
#define get_VP8_P2_VP8_MB_MV15_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_MV15_reg))
#define VP8_P2_VP8_MB_MV15_inst_adr                                                  "0x00D8"
#define VP8_P2_VP8_MB_MV15_inst                                                      0x00D8
#define VP8_P2_VP8_MB_MV15_mv_x_shift                                                (14)
#define VP8_P2_VP8_MB_MV15_mv_x_mask                                                 (0x1FFFC000)
#define VP8_P2_VP8_MB_MV15_mv_x(data)                                                (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_MV15_mv_x_src(data)                                            ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV15_get_mv_x(data)                                            ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_MV15_mv_y_shift                                                (0)
#define VP8_P2_VP8_MB_MV15_mv_y_mask                                                 (0x00003FFF)
#define VP8_P2_VP8_MB_MV15_mv_y(data)                                                (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_MV15_mv_y_src(data)                                            ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_MV15_get_mv_y(data)                                            ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_CH_MV0                                                         0x1800EF64
#define VP8_P2_VP8_MB_CH_MV0_reg_addr                                                "0xB800EF64"
#define VP8_P2_VP8_MB_CH_MV0_reg                                                     0xB800EF64
#define set_VP8_P2_VP8_MB_CH_MV0_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_CH_MV0_reg)=data)
#define get_VP8_P2_VP8_MB_CH_MV0_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_CH_MV0_reg))
#define VP8_P2_VP8_MB_CH_MV0_inst_adr                                                "0x00D9"
#define VP8_P2_VP8_MB_CH_MV0_inst                                                    0x00D9
#define VP8_P2_VP8_MB_CH_MV0_mv_x_shift                                              (14)
#define VP8_P2_VP8_MB_CH_MV0_mv_x_mask                                               (0x1FFFC000)
#define VP8_P2_VP8_MB_CH_MV0_mv_x(data)                                              (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_CH_MV0_mv_x_src(data)                                          ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_CH_MV0_get_mv_x(data)                                          ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_CH_MV0_mv_y_shift                                              (0)
#define VP8_P2_VP8_MB_CH_MV0_mv_y_mask                                               (0x00003FFF)
#define VP8_P2_VP8_MB_CH_MV0_mv_y(data)                                              (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_CH_MV0_mv_y_src(data)                                          ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_CH_MV0_get_mv_y(data)                                          ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_CH_MV1                                                         0x1800EF68
#define VP8_P2_VP8_MB_CH_MV1_reg_addr                                                "0xB800EF68"
#define VP8_P2_VP8_MB_CH_MV1_reg                                                     0xB800EF68
#define set_VP8_P2_VP8_MB_CH_MV1_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_CH_MV1_reg)=data)
#define get_VP8_P2_VP8_MB_CH_MV1_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_CH_MV1_reg))
#define VP8_P2_VP8_MB_CH_MV1_inst_adr                                                "0x00DA"
#define VP8_P2_VP8_MB_CH_MV1_inst                                                    0x00DA
#define VP8_P2_VP8_MB_CH_MV1_mv_x_shift                                              (14)
#define VP8_P2_VP8_MB_CH_MV1_mv_x_mask                                               (0x1FFFC000)
#define VP8_P2_VP8_MB_CH_MV1_mv_x(data)                                              (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_CH_MV1_mv_x_src(data)                                          ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_CH_MV1_get_mv_x(data)                                          ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_CH_MV1_mv_y_shift                                              (0)
#define VP8_P2_VP8_MB_CH_MV1_mv_y_mask                                               (0x00003FFF)
#define VP8_P2_VP8_MB_CH_MV1_mv_y(data)                                              (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_CH_MV1_mv_y_src(data)                                          ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_CH_MV1_get_mv_y(data)                                          ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_CH_MV2                                                         0x1800EF6C
#define VP8_P2_VP8_MB_CH_MV2_reg_addr                                                "0xB800EF6C"
#define VP8_P2_VP8_MB_CH_MV2_reg                                                     0xB800EF6C
#define set_VP8_P2_VP8_MB_CH_MV2_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_CH_MV2_reg)=data)
#define get_VP8_P2_VP8_MB_CH_MV2_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_CH_MV2_reg))
#define VP8_P2_VP8_MB_CH_MV2_inst_adr                                                "0x00DB"
#define VP8_P2_VP8_MB_CH_MV2_inst                                                    0x00DB
#define VP8_P2_VP8_MB_CH_MV2_mv_x_shift                                              (14)
#define VP8_P2_VP8_MB_CH_MV2_mv_x_mask                                               (0x1FFFC000)
#define VP8_P2_VP8_MB_CH_MV2_mv_x(data)                                              (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_CH_MV2_mv_x_src(data)                                          ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_CH_MV2_get_mv_x(data)                                          ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_CH_MV2_mv_y_shift                                              (0)
#define VP8_P2_VP8_MB_CH_MV2_mv_y_mask                                               (0x00003FFF)
#define VP8_P2_VP8_MB_CH_MV2_mv_y(data)                                              (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_CH_MV2_mv_y_src(data)                                          ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_CH_MV2_get_mv_y(data)                                          ((0x00003FFF&(data))>>0)


#define VP8_P2_VP8_MB_CH_MV3                                                         0x1800EF70
#define VP8_P2_VP8_MB_CH_MV3_reg_addr                                                "0xB800EF70"
#define VP8_P2_VP8_MB_CH_MV3_reg                                                     0xB800EF70
#define set_VP8_P2_VP8_MB_CH_MV3_reg(data)   (*((volatile unsigned int*) VP8_P2_VP8_MB_CH_MV3_reg)=data)
#define get_VP8_P2_VP8_MB_CH_MV3_reg   (*((volatile unsigned int*) VP8_P2_VP8_MB_CH_MV3_reg))
#define VP8_P2_VP8_MB_CH_MV3_inst_adr                                                "0x00DC"
#define VP8_P2_VP8_MB_CH_MV3_inst                                                    0x00DC
#define VP8_P2_VP8_MB_CH_MV3_mv_x_shift                                              (14)
#define VP8_P2_VP8_MB_CH_MV3_mv_x_mask                                               (0x1FFFC000)
#define VP8_P2_VP8_MB_CH_MV3_mv_x(data)                                              (0x1FFFC000&((data)<<14))
#define VP8_P2_VP8_MB_CH_MV3_mv_x_src(data)                                          ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_CH_MV3_get_mv_x(data)                                          ((0x1FFFC000&(data))>>14)
#define VP8_P2_VP8_MB_CH_MV3_mv_y_shift                                              (0)
#define VP8_P2_VP8_MB_CH_MV3_mv_y_mask                                               (0x00003FFF)
#define VP8_P2_VP8_MB_CH_MV3_mv_y(data)                                              (0x00003FFF&((data)<<0))
#define VP8_P2_VP8_MB_CH_MV3_mv_y_src(data)                                          ((0x00003FFF&(data))>>0)
#define VP8_P2_VP8_MB_CH_MV3_get_mv_y(data)                                          ((0x00003FFF&(data))>>0)


#endif
