/*
 * mipi_wrapper_reg.h - RTK hdmi rx driver header file
 *
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */


#ifndef _MIPI_WRAPPER_REG_H_INCLUDED_
#define _MIPI_WRAPPER_REG_H_INCLUDED_

#define MIPI                                                                         0x00
#define MIPI_reg_addr                                                                "0x98004100"
#define MIPI_reg                                                                     0x98004100
#define set_MIPI_reg(data)   (*((volatile unsigned int*) MIPI_reg)=data)
#define get_MIPI_reg   (*((volatile unsigned int*) MIPI_reg))
#define MIPI_inst_adr                                                                "0x0040"
#define MIPI_inst                                                                    0x0040
#define MIPI_dst_fmt_shift                                                           (27)
#define MIPI_dst_fmt_mask                                                            (0xF8000000)
#define MIPI_dst_fmt(data)                                                           (0xF8000000&((data)<<27))
#define MIPI_dst_fmt_src(data)                                                       ((0xF8000000&(data))>>27)
#define MIPI_get_dst_fmt(data)                                                       ((0xF8000000&(data))>>27)
#define MIPI_src_fmt_shift                                                           (25)
#define MIPI_src_fmt_mask                                                            (0x06000000)
#define MIPI_src_fmt(data)                                                           (0x06000000&((data)<<25))
#define MIPI_src_fmt_src(data)                                                       ((0x06000000&(data))>>25)
#define MIPI_get_src_fmt(data)                                                       ((0x06000000&(data))>>25)
#define MIPI_src_sel_shift                                                           (24)
#define MIPI_src_sel_mask                                                            (0x01000000)
#define MIPI_src_sel(data)                                                           (0x01000000&((data)<<24))
#define MIPI_src_sel_src(data)                                                       ((0x01000000&(data))>>24)
#define MIPI_get_src_sel(data)                                                       ((0x01000000&(data))>>24)
#define MIPI_yuv420_uv_seq_shift                                                     (23)
#define MIPI_yuv420_uv_seq_mask                                                      (0x00800000)
#define MIPI_yuv420_uv_seq(data)                                                     (0x00800000&((data)<<23))
#define MIPI_yuv420_uv_seq_src(data)                                                 ((0x00800000&(data))>>23)
#define MIPI_get_yuv420_uv_seq(data)                                                 ((0x00800000&(data))>>23)
#define MIPI_vs_shift                                                                (22)
#define MIPI_vs_mask                                                                 (0x00400000)
#define MIPI_vs(data)                                                                (0x00400000&((data)<<22))
#define MIPI_vs_src(data)                                                            ((0x00400000&(data))>>22)
#define MIPI_get_vs(data)                                                            ((0x00400000&(data))>>22)
#define MIPI_vs_near_shift                                                           (21)
#define MIPI_vs_near_mask                                                            (0x00200000)
#define MIPI_vs_near(data)                                                           (0x00200000&((data)<<21))
#define MIPI_vs_near_src(data)                                                       ((0x00200000&(data))>>21)
#define MIPI_get_vs_near(data)                                                       ((0x00200000&(data))>>21)
#define MIPI_vs_yodd_shift                                                           (20)
#define MIPI_vs_yodd_mask                                                            (0x00100000)
#define MIPI_vs_yodd(data)                                                           (0x00100000&((data)<<20))
#define MIPI_vs_yodd_src(data)                                                       ((0x00100000&(data))>>20)
#define MIPI_get_vs_yodd(data)                                                       ((0x00100000&(data))>>20)
#define MIPI_vs_codd_shift                                                           (19)
#define MIPI_vs_codd_mask                                                            (0x00080000)
#define MIPI_vs_codd(data)                                                           (0x00080000&((data)<<19))
#define MIPI_vs_codd_src(data)                                                       ((0x00080000&(data))>>19)
#define MIPI_get_vs_codd(data)                                                       ((0x00080000&(data))>>19)
#define MIPI_hs_shift                                                                (18)
#define MIPI_hs_mask                                                                 (0x00040000)
#define MIPI_hs(data)                                                                (0x00040000&((data)<<18))
#define MIPI_hs_src(data)                                                            ((0x00040000&(data))>>18)
#define MIPI_get_hs(data)                                                            ((0x00040000&(data))>>18)
#define MIPI_hs_yodd_shift                                                           (17)
#define MIPI_hs_yodd_mask                                                            (0x00020000)
#define MIPI_hs_yodd(data)                                                           (0x00020000&((data)<<17))
#define MIPI_hs_yodd_src(data)                                                       ((0x00020000&(data))>>17)
#define MIPI_get_hs_yodd(data)                                                       ((0x00020000&(data))>>17)
#define MIPI_hs_codd_shift                                                           (16)
#define MIPI_hs_codd_mask                                                            (0x00010000)
#define MIPI_hs_codd(data)                                                           (0x00010000&((data)<<16))
#define MIPI_hs_codd_src(data)                                                       ((0x00010000&(data))>>16)
#define MIPI_get_hs_codd(data)                                                       ((0x00010000&(data))>>16)
#define MIPI_yuv420_fmt_shift                                                        (15)
#define MIPI_yuv420_fmt_mask                                                         (0x00008000)
#define MIPI_yuv420_fmt(data)                                                        (0x00008000&((data)<<15))
#define MIPI_yuv420_fmt_src(data)                                                    ((0x00008000&(data))>>15)
#define MIPI_get_yuv420_fmt(data)                                                    ((0x00008000&(data))>>15)
#define MIPI_ccs_data_format_shift                                                   (13)
#define MIPI_ccs_data_format_mask                                                    (0x00006000)
#define MIPI_ccs_data_format(data)                                                   (0x00006000&((data)<<13))
#define MIPI_ccs_data_format_src(data)                                               ((0x00006000&(data))>>13)
#define MIPI_get_ccs_data_format(data)                                               ((0x00006000&(data))>>13)
#define MIPI_yuv_to_rgb_shift                                                        (12)
#define MIPI_yuv_to_rgb_mask                                                         (0x00001000)
#define MIPI_yuv_to_rgb(data)                                                        (0x00001000&((data)<<12))
#define MIPI_yuv_to_rgb_src(data)                                                    ((0x00001000&(data))>>12)
#define MIPI_get_yuv_to_rgb(data)                                                    ((0x00001000&(data))>>12)
#define MIPI_chroma_ds_mode_shift                                                    (11)
#define MIPI_chroma_ds_mode_mask                                                     (0x00000800)
#define MIPI_chroma_ds_mode(data)                                                    (0x00000800&((data)<<11))
#define MIPI_chroma_ds_mode_src(data)                                                ((0x00000800&(data))>>11)
#define MIPI_get_chroma_ds_mode(data)                                                ((0x00000800&(data))>>11)
#define MIPI_chroma_ds_en_shift                                                      (10)
#define MIPI_chroma_ds_en_mask                                                       (0x00000400)
#define MIPI_chroma_ds_en(data)                                                      (0x00000400&((data)<<10))
#define MIPI_chroma_ds_en_src(data)                                                  ((0x00000400&(data))>>10)
#define MIPI_get_chroma_ds_en(data)                                                  ((0x00000400&(data))>>10)
#define MIPI_chroma_us_mode_shift                                                    (9)
#define MIPI_chroma_us_mode_mask                                                     (0x00000200)
#define MIPI_chroma_us_mode(data)                                                    (0x00000200&((data)<<9))
#define MIPI_chroma_us_mode_src(data)                                                ((0x00000200&(data))>>9)
#define MIPI_get_chroma_us_mode(data)                                                ((0x00000200&(data))>>9)
#define MIPI_chroma_us_en_shift                                                      (8)
#define MIPI_chroma_us_en_mask                                                       (0x00000100)
#define MIPI_chroma_us_en(data)                                                      (0x00000100&((data)<<8))
#define MIPI_chroma_us_en_src(data)                                                  ((0x00000100&(data))>>8)
#define MIPI_get_chroma_us_en(data)                                                  ((0x00000100&(data))>>8)
#define MIPI_hdmirx_interlace_en_shift                                               (7)
#define MIPI_hdmirx_interlace_en_mask                                                (0x00000080)
#define MIPI_hdmirx_interlace_en(data)                                               (0x00000080&((data)<<7))
#define MIPI_hdmirx_interlace_en_src(data)                                           ((0x00000080&(data))>>7)
#define MIPI_get_hdmirx_interlace_en(data)                                           ((0x00000080&(data))>>7)
#define MIPI_hdmirx_interlace_polarity_shift                                         (6)
#define MIPI_hdmirx_interlace_polarity_mask                                          (0x00000040)
#define MIPI_hdmirx_interlace_polarity(data)                                         (0x00000040&((data)<<6))
#define MIPI_hdmirx_interlace_polarity_src(data)                                     ((0x00000040&(data))>>6)
#define MIPI_get_hdmirx_interlace_polarity(data)                                     ((0x00000040&(data))>>6)
#define MIPI_int_en4_shift                                                           (5)
#define MIPI_int_en4_mask                                                            (0x00000020)
#define MIPI_int_en4(data)                                                           (0x00000020&((data)<<5))
#define MIPI_int_en4_src(data)                                                       ((0x00000020&(data))>>5)
#define MIPI_get_int_en4(data)                                                       ((0x00000020&(data))>>5)
#define MIPI_int_en3_shift                                                           (4)
#define MIPI_int_en3_mask                                                            (0x00000010)
#define MIPI_int_en3(data)                                                           (0x00000010&((data)<<4))
#define MIPI_int_en3_src(data)                                                       ((0x00000010&(data))>>4)
#define MIPI_get_int_en3(data)                                                       ((0x00000010&(data))>>4)
#define MIPI_int_en2_shift                                                           (3)
#define MIPI_int_en2_mask                                                            (0x00000008)
#define MIPI_int_en2(data)                                                           (0x00000008&((data)<<3))
#define MIPI_int_en2_src(data)                                                       ((0x00000008&(data))>>3)
#define MIPI_get_int_en2(data)                                                       ((0x00000008&(data))>>3)
#define MIPI_int_en1_shift                                                           (2)
#define MIPI_int_en1_mask                                                            (0x00000004)
#define MIPI_int_en1(data)                                                           (0x00000004&((data)<<2))
#define MIPI_int_en1_src(data)                                                       ((0x00000004&(data))>>2)
#define MIPI_get_int_en1(data)                                                       ((0x00000004&(data))>>2)
#define MIPI_int_en0_shift                                                           (1)
#define MIPI_int_en0_mask                                                            (0x00000002)
#define MIPI_int_en0(data)                                                           (0x00000002&((data)<<1))
#define MIPI_int_en0_src(data)                                                       ((0x00000002&(data))>>1)
#define MIPI_get_int_en0(data)                                                       ((0x00000002&(data))>>1)
#define MIPI_en_shift                                                                (0)
#define MIPI_en_mask                                                                 (0x00000001)
#define MIPI_en(data)                                                                (0x00000001&((data)<<0))
#define MIPI_en_src(data)                                                            ((0x00000001&(data))>>0)
#define MIPI_get_en(data)                                                            ((0x00000001&(data))>>0)


#define MIPI_SA0                                                                     0x04
#define MIPI_SA0_reg_addr                                                            "0x98004104"
#define MIPI_SA0_reg                                                                 0x98004104
#define set_MIPI_SA0_reg(data)   (*((volatile unsigned int*) MIPI_SA0_reg)=data)
#define get_MIPI_SA0_reg   (*((volatile unsigned int*) MIPI_SA0_reg))
#define MIPI_SA0_inst_adr                                                            "0x0041"
#define MIPI_SA0_inst                                                                0x0041
#define MIPI_SA0_sa0_video_shift                                                     (0)
#define MIPI_SA0_sa0_video_mask                                                      (0xFFFFFFFF)
#define MIPI_SA0_sa0_video(data)                                                     (0xFFFFFFFF&((data)<<0))
#define MIPI_SA0_sa0_video_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define MIPI_SA0_get_sa0_video(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define MIPI_SA1                                                                     0x08
#define MIPI_SA1_reg_addr                                                            "0x98004108"
#define MIPI_SA1_reg                                                                 0x98004108
#define set_MIPI_SA1_reg(data)   (*((volatile unsigned int*) MIPI_SA1_reg)=data)
#define get_MIPI_SA1_reg   (*((volatile unsigned int*) MIPI_SA1_reg))
#define MIPI_SA1_inst_adr                                                            "0x0042"
#define MIPI_SA1_inst                                                                0x0042
#define MIPI_SA1_sa1_video_shift                                                     (0)
#define MIPI_SA1_sa1_video_mask                                                      (0xFFFFFFFF)
#define MIPI_SA1_sa1_video(data)                                                     (0xFFFFFFFF&((data)<<0))
#define MIPI_SA1_sa1_video_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define MIPI_SA1_get_sa1_video(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define MIPI_SA2                                                                     0x0C
#define MIPI_SA2_reg_addr                                                            "0x9800410C"
#define MIPI_SA2_reg                                                                 0x9800410C
#define set_MIPI_SA2_reg(data)   (*((volatile unsigned int*) MIPI_SA2_reg)=data)
#define get_MIPI_SA2_reg   (*((volatile unsigned int*) MIPI_SA2_reg))
#define MIPI_SA2_inst_adr                                                            "0x0043"
#define MIPI_SA2_inst                                                                0x0043
#define MIPI_SA2_sa2_pic_shift                                                       (0)
#define MIPI_SA2_sa2_pic_mask                                                        (0xFFFFFFFF)
#define MIPI_SA2_sa2_pic(data)                                                       (0xFFFFFFFF&((data)<<0))
#define MIPI_SA2_sa2_pic_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define MIPI_SA2_get_sa2_pic(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define MIPI_SIZE0                                                                   0x10
#define MIPI_SIZE0_reg_addr                                                          "0x98004110"
#define MIPI_SIZE0_reg                                                               0x98004110
#define set_MIPI_SIZE0_reg(data)   (*((volatile unsigned int*) MIPI_SIZE0_reg)=data)
#define get_MIPI_SIZE0_reg   (*((volatile unsigned int*) MIPI_SIZE0_reg))
#define MIPI_SIZE0_inst_adr                                                          "0x0044"
#define MIPI_SIZE0_inst                                                              0x0044
#define MIPI_SIZE0_dst_width_video_shift                                             (16)
#define MIPI_SIZE0_dst_width_video_mask                                              (0x1FFF0000)
#define MIPI_SIZE0_dst_width_video(data)                                             (0x1FFF0000&((data)<<16))
#define MIPI_SIZE0_dst_width_video_src(data)                                         ((0x1FFF0000&(data))>>16)
#define MIPI_SIZE0_get_dst_width_video(data)                                         ((0x1FFF0000&(data))>>16)
#define MIPI_SIZE0_pitch_video_shift                                                 (0)
#define MIPI_SIZE0_pitch_video_mask                                                  (0x0000FFFF)
#define MIPI_SIZE0_pitch_video(data)                                                 (0x0000FFFF&((data)<<0))
#define MIPI_SIZE0_pitch_video_src(data)                                             ((0x0000FFFF&(data))>>0)
#define MIPI_SIZE0_get_pitch_video(data)                                             ((0x0000FFFF&(data))>>0)


#define MIPI_SIZE1                                                                   0x14
#define MIPI_SIZE1_reg_addr                                                          "0x98004114"
#define MIPI_SIZE1_reg                                                               0x98004114
#define set_MIPI_SIZE1_reg(data)   (*((volatile unsigned int*) MIPI_SIZE1_reg)=data)
#define get_MIPI_SIZE1_reg   (*((volatile unsigned int*) MIPI_SIZE1_reg))
#define MIPI_SIZE1_inst_adr                                                          "0x0045"
#define MIPI_SIZE1_inst                                                              0x0045
#define MIPI_SIZE1_dst_width_pic_shift                                               (16)
#define MIPI_SIZE1_dst_width_pic_mask                                                (0x1FFF0000)
#define MIPI_SIZE1_dst_width_pic(data)                                               (0x1FFF0000&((data)<<16))
#define MIPI_SIZE1_dst_width_pic_src(data)                                           ((0x1FFF0000&(data))>>16)
#define MIPI_SIZE1_get_dst_width_pic(data)                                           ((0x1FFF0000&(data))>>16)
#define MIPI_SIZE1_pitch_pic_shift                                                   (0)
#define MIPI_SIZE1_pitch_pic_mask                                                    (0x0000FFFF)
#define MIPI_SIZE1_pitch_pic(data)                                                   (0x0000FFFF&((data)<<0))
#define MIPI_SIZE1_pitch_pic_src(data)                                               ((0x0000FFFF&(data))>>0)
#define MIPI_SIZE1_get_pitch_pic(data)                                               ((0x0000FFFF&(data))>>0)


#define MIPI_SIZE2                                                                   0x18
#define MIPI_SIZE2_reg_addr                                                          "0x98004118"
#define MIPI_SIZE2_reg                                                               0x98004118
#define set_MIPI_SIZE2_reg(data)   (*((volatile unsigned int*) MIPI_SIZE2_reg)=data)
#define get_MIPI_SIZE2_reg   (*((volatile unsigned int*) MIPI_SIZE2_reg))
#define MIPI_SIZE2_inst_adr                                                          "0x0046"
#define MIPI_SIZE2_inst                                                              0x0046
#define MIPI_SIZE2_src_width_pic_shift                                               (16)
#define MIPI_SIZE2_src_width_pic_mask                                                (0x1FFF0000)
#define MIPI_SIZE2_src_width_pic(data)                                               (0x1FFF0000&((data)<<16))
#define MIPI_SIZE2_src_width_pic_src(data)                                           ((0x1FFF0000&(data))>>16)
#define MIPI_SIZE2_get_src_width_pic(data)                                           ((0x1FFF0000&(data))>>16)
#define MIPI_SIZE2_src_width_video_shift                                             (0)
#define MIPI_SIZE2_src_width_video_mask                                              (0x00001FFF)
#define MIPI_SIZE2_src_width_video(data)                                             (0x00001FFF&((data)<<0))
#define MIPI_SIZE2_src_width_video_src(data)                                         ((0x00001FFF&(data))>>0)
#define MIPI_SIZE2_get_src_width_video(data)                                         ((0x00001FFF&(data))>>0)


#define MIPI_INDEX0                                                                  0x1C
#define MIPI_INDEX0_reg_addr                                                         "0x9800411C"
#define MIPI_INDEX0_reg                                                              0x9800411C
#define set_MIPI_INDEX0_reg(data)   (*((volatile unsigned int*) MIPI_INDEX0_reg)=data)
#define get_MIPI_INDEX0_reg   (*((volatile unsigned int*) MIPI_INDEX0_reg))
#define MIPI_INDEX0_inst_adr                                                         "0x0047"
#define MIPI_INDEX0_inst                                                             0x0047
#define MIPI_INDEX0_index_y0_video_shift                                             (16)
#define MIPI_INDEX0_index_y0_video_mask                                              (0x007F0000)
#define MIPI_INDEX0_index_y0_video(data)                                             (0x007F0000&((data)<<16))
#define MIPI_INDEX0_index_y0_video_src(data)                                         ((0x007F0000&(data))>>16)
#define MIPI_INDEX0_get_index_y0_video(data)                                         ((0x007F0000&(data))>>16)
#define MIPI_INDEX0_index_c0_video_shift                                             (0)
#define MIPI_INDEX0_index_c0_video_mask                                              (0x0000007F)
#define MIPI_INDEX0_index_c0_video(data)                                             (0x0000007F&((data)<<0))
#define MIPI_INDEX0_index_c0_video_src(data)                                         ((0x0000007F&(data))>>0)
#define MIPI_INDEX0_get_index_c0_video(data)                                         ((0x0000007F&(data))>>0)


#define MIPI_INDEX1                                                                  0x20
#define MIPI_INDEX1_reg_addr                                                         "0x98004120"
#define MIPI_INDEX1_reg                                                              0x98004120
#define set_MIPI_INDEX1_reg(data)   (*((volatile unsigned int*) MIPI_INDEX1_reg)=data)
#define get_MIPI_INDEX1_reg   (*((volatile unsigned int*) MIPI_INDEX1_reg))
#define MIPI_INDEX1_inst_adr                                                         "0x0048"
#define MIPI_INDEX1_inst                                                             0x0048
#define MIPI_INDEX1_index_y1_video_shift                                             (16)
#define MIPI_INDEX1_index_y1_video_mask                                              (0x007F0000)
#define MIPI_INDEX1_index_y1_video(data)                                             (0x007F0000&((data)<<16))
#define MIPI_INDEX1_index_y1_video_src(data)                                         ((0x007F0000&(data))>>16)
#define MIPI_INDEX1_get_index_y1_video(data)                                         ((0x007F0000&(data))>>16)
#define MIPI_INDEX1_index_c1_video_shift                                             (0)
#define MIPI_INDEX1_index_c1_video_mask                                              (0x0000007F)
#define MIPI_INDEX1_index_c1_video(data)                                             (0x0000007F&((data)<<0))
#define MIPI_INDEX1_index_c1_video_src(data)                                         ((0x0000007F&(data))>>0)
#define MIPI_INDEX1_get_index_c1_video(data)                                         ((0x0000007F&(data))>>0)


#define MIPI_INDEX2                                                                  0x24
#define MIPI_INDEX2_reg_addr                                                         "0x98004124"
#define MIPI_INDEX2_reg                                                              0x98004124
#define set_MIPI_INDEX2_reg(data)   (*((volatile unsigned int*) MIPI_INDEX2_reg)=data)
#define get_MIPI_INDEX2_reg   (*((volatile unsigned int*) MIPI_INDEX2_reg))
#define MIPI_INDEX2_inst_adr                                                         "0x0049"
#define MIPI_INDEX2_inst                                                             0x0049
#define MIPI_INDEX2_index_y2_pic_shift                                               (16)
#define MIPI_INDEX2_index_y2_pic_mask                                                (0x007F0000)
#define MIPI_INDEX2_index_y2_pic(data)                                               (0x007F0000&((data)<<16))
#define MIPI_INDEX2_index_y2_pic_src(data)                                           ((0x007F0000&(data))>>16)
#define MIPI_INDEX2_get_index_y2_pic(data)                                           ((0x007F0000&(data))>>16)
#define MIPI_INDEX2_index_c2_pic_shift                                               (0)
#define MIPI_INDEX2_index_c2_pic_mask                                                (0x0000007F)
#define MIPI_INDEX2_index_c2_pic(data)                                               (0x0000007F&((data)<<0))
#define MIPI_INDEX2_index_c2_pic_src(data)                                           ((0x0000007F&(data))>>0)
#define MIPI_INDEX2_get_index_c2_pic(data)                                           ((0x0000007F&(data))>>0)


#define MIPI_INT_ST                                                                  0x28
#define MIPI_INT_ST_reg_addr                                                         "0x98004128"
#define MIPI_INT_ST_reg                                                              0x98004128
#define set_MIPI_INT_ST_reg(data)   (*((volatile unsigned int*) MIPI_INT_ST_reg)=data)
#define get_MIPI_INT_ST_reg   (*((volatile unsigned int*) MIPI_INT_ST_reg))
#define MIPI_INT_ST_inst_adr                                                         "0x004A"
#define MIPI_INT_ST_inst                                                             0x004A
#define MIPI_INT_ST_mipi_data_valid_shift                                            (20)
#define MIPI_INT_ST_mipi_data_valid_mask                                             (0x00100000)
#define MIPI_INT_ST_mipi_data_valid(data)                                            (0x00100000&((data)<<20))
#define MIPI_INT_ST_mipi_data_valid_src(data)                                        ((0x00100000&(data))>>20)
#define MIPI_INT_ST_get_mipi_data_valid(data)                                        ((0x00100000&(data))>>20)
#define MIPI_INT_ST_mipi_line_end_shift                                              (19)
#define MIPI_INT_ST_mipi_line_end_mask                                               (0x00080000)
#define MIPI_INT_ST_mipi_line_end(data)                                              (0x00080000&((data)<<19))
#define MIPI_INT_ST_mipi_line_end_src(data)                                          ((0x00080000&(data))>>19)
#define MIPI_INT_ST_get_mipi_line_end(data)                                          ((0x00080000&(data))>>19)
#define MIPI_INT_ST_mipi_line_start_shift                                            (18)
#define MIPI_INT_ST_mipi_line_start_mask                                             (0x00040000)
#define MIPI_INT_ST_mipi_line_start(data)                                            (0x00040000&((data)<<18))
#define MIPI_INT_ST_mipi_line_start_src(data)                                        ((0x00040000&(data))>>18)
#define MIPI_INT_ST_get_mipi_line_start(data)                                        ((0x00040000&(data))>>18)
#define MIPI_INT_ST_mipi_frame_end_shift                                             (17)
#define MIPI_INT_ST_mipi_frame_end_mask                                              (0x00020000)
#define MIPI_INT_ST_mipi_frame_end(data)                                             (0x00020000&((data)<<17))
#define MIPI_INT_ST_mipi_frame_end_src(data)                                         ((0x00020000&(data))>>17)
#define MIPI_INT_ST_get_mipi_frame_end(data)                                         ((0x00020000&(data))>>17)
#define MIPI_INT_ST_mipi_frame_start_shift                                           (16)
#define MIPI_INT_ST_mipi_frame_start_mask                                            (0x00010000)
#define MIPI_INT_ST_mipi_frame_start(data)                                           (0x00010000&((data)<<16))
#define MIPI_INT_ST_mipi_frame_start_src(data)                                       ((0x00010000&(data))>>16)
#define MIPI_INT_ST_get_mipi_frame_start(data)                                       ((0x00010000&(data))>>16)
#define MIPI_INT_ST_esc_lane3_int_flg_shift                                          (15)
#define MIPI_INT_ST_esc_lane3_int_flg_mask                                           (0x00008000)
#define MIPI_INT_ST_esc_lane3_int_flg(data)                                          (0x00008000&((data)<<15))
#define MIPI_INT_ST_esc_lane3_int_flg_src(data)                                      ((0x00008000&(data))>>15)
#define MIPI_INT_ST_get_esc_lane3_int_flg(data)                                      ((0x00008000&(data))>>15)
#define MIPI_INT_ST_esc_lane2_int_flg_shift                                          (14)
#define MIPI_INT_ST_esc_lane2_int_flg_mask                                           (0x00004000)
#define MIPI_INT_ST_esc_lane2_int_flg(data)                                          (0x00004000&((data)<<14))
#define MIPI_INT_ST_esc_lane2_int_flg_src(data)                                      ((0x00004000&(data))>>14)
#define MIPI_INT_ST_get_esc_lane2_int_flg(data)                                      ((0x00004000&(data))>>14)
#define MIPI_INT_ST_esc_lane1_int_flg_shift                                          (13)
#define MIPI_INT_ST_esc_lane1_int_flg_mask                                           (0x00002000)
#define MIPI_INT_ST_esc_lane1_int_flg(data)                                          (0x00002000&((data)<<13))
#define MIPI_INT_ST_esc_lane1_int_flg_src(data)                                      ((0x00002000&(data))>>13)
#define MIPI_INT_ST_get_esc_lane1_int_flg(data)                                      ((0x00002000&(data))>>13)
#define MIPI_INT_ST_esc_lane0_int_flg_shift                                          (12)
#define MIPI_INT_ST_esc_lane0_int_flg_mask                                           (0x00001000)
#define MIPI_INT_ST_esc_lane0_int_flg(data)                                          (0x00001000&((data)<<12))
#define MIPI_INT_ST_esc_lane0_int_flg_src(data)                                      ((0x00001000&(data))>>12)
#define MIPI_INT_ST_get_esc_lane0_int_flg(data)                                      ((0x00001000&(data))>>12)
#define MIPI_INT_ST_clk_ulps_int_flg_shift                                           (11)
#define MIPI_INT_ST_clk_ulps_int_flg_mask                                            (0x00000800)
#define MIPI_INT_ST_clk_ulps_int_flg(data)                                           (0x00000800&((data)<<11))
#define MIPI_INT_ST_clk_ulps_int_flg_src(data)                                       ((0x00000800&(data))>>11)
#define MIPI_INT_ST_get_clk_ulps_int_flg(data)                                       ((0x00000800&(data))>>11)
#define MIPI_INT_ST_crc16_err_int_flg_shift                                          (10)
#define MIPI_INT_ST_crc16_err_int_flg_mask                                           (0x00000400)
#define MIPI_INT_ST_crc16_err_int_flg(data)                                          (0x00000400&((data)<<10))
#define MIPI_INT_ST_crc16_err_int_flg_src(data)                                      ((0x00000400&(data))>>10)
#define MIPI_INT_ST_get_crc16_err_int_flg(data)                                      ((0x00000400&(data))>>10)
#define MIPI_INT_ST_ecc_crt_int_flg_shift                                            (9)
#define MIPI_INT_ST_ecc_crt_int_flg_mask                                             (0x00000200)
#define MIPI_INT_ST_ecc_crt_int_flg(data)                                            (0x00000200&((data)<<9))
#define MIPI_INT_ST_ecc_crt_int_flg_src(data)                                        ((0x00000200&(data))>>9)
#define MIPI_INT_ST_get_ecc_crt_int_flg(data)                                        ((0x00000200&(data))>>9)
#define MIPI_INT_ST_ecc_err_int_flg_shift                                            (8)
#define MIPI_INT_ST_ecc_err_int_flg_mask                                             (0x00000100)
#define MIPI_INT_ST_ecc_err_int_flg(data)                                            (0x00000100&((data)<<8))
#define MIPI_INT_ST_ecc_err_int_flg_src(data)                                        ((0x00000100&(data))>>8)
#define MIPI_INT_ST_get_ecc_err_int_flg(data)                                        ((0x00000100&(data))>>8)
#define MIPI_INT_ST_pic_detect_v_fail_shift                                          (7)
#define MIPI_INT_ST_pic_detect_v_fail_mask                                           (0x00000080)
#define MIPI_INT_ST_pic_detect_v_fail(data)                                          (0x00000080&((data)<<7))
#define MIPI_INT_ST_pic_detect_v_fail_src(data)                                      ((0x00000080&(data))>>7)
#define MIPI_INT_ST_get_pic_detect_v_fail(data)                                      ((0x00000080&(data))>>7)
#define MIPI_INT_ST_pic_detect_h_fail_shift                                          (6)
#define MIPI_INT_ST_pic_detect_h_fail_mask                                           (0x00000040)
#define MIPI_INT_ST_pic_detect_h_fail(data)                                          (0x00000040&((data)<<6))
#define MIPI_INT_ST_pic_detect_h_fail_src(data)                                      ((0x00000040&(data))>>6)
#define MIPI_INT_ST_get_pic_detect_h_fail(data)                                      ((0x00000040&(data))>>6)
#define MIPI_INT_ST_overflow_drop_shift                                              (5)
#define MIPI_INT_ST_overflow_drop_mask                                               (0x00000020)
#define MIPI_INT_ST_overflow_drop(data)                                              (0x00000020&((data)<<5))
#define MIPI_INT_ST_overflow_drop_src(data)                                          ((0x00000020&(data))>>5)
#define MIPI_INT_ST_get_overflow_drop(data)                                          ((0x00000020&(data))>>5)
#define MIPI_INT_ST_fm_drop_shift                                                    (4)
#define MIPI_INT_ST_fm_drop_mask                                                     (0x00000010)
#define MIPI_INT_ST_fm_drop(data)                                                    (0x00000010&((data)<<4))
#define MIPI_INT_ST_fm_drop_src(data)                                                ((0x00000010&(data))>>4)
#define MIPI_INT_ST_get_fm_drop(data)                                                ((0x00000010&(data))>>4)
#define MIPI_INT_ST_fm_done2_shift                                                   (3)
#define MIPI_INT_ST_fm_done2_mask                                                    (0x00000008)
#define MIPI_INT_ST_fm_done2(data)                                                   (0x00000008&((data)<<3))
#define MIPI_INT_ST_fm_done2_src(data)                                               ((0x00000008&(data))>>3)
#define MIPI_INT_ST_get_fm_done2(data)                                               ((0x00000008&(data))>>3)
#define MIPI_INT_ST_fm_done1_shift                                                   (2)
#define MIPI_INT_ST_fm_done1_mask                                                    (0x00000004)
#define MIPI_INT_ST_fm_done1(data)                                                   (0x00000004&((data)<<2))
#define MIPI_INT_ST_fm_done1_src(data)                                               ((0x00000004&(data))>>2)
#define MIPI_INT_ST_get_fm_done1(data)                                               ((0x00000004&(data))>>2)
#define MIPI_INT_ST_fm_done0_shift                                                   (1)
#define MIPI_INT_ST_fm_done0_mask                                                    (0x00000002)
#define MIPI_INT_ST_fm_done0(data)                                                   (0x00000002&((data)<<1))
#define MIPI_INT_ST_fm_done0_src(data)                                               ((0x00000002&(data))>>1)
#define MIPI_INT_ST_get_fm_done0(data)                                               ((0x00000002&(data))>>1)
#define MIPI_INT_ST_write_data_shift                                                 (0)
#define MIPI_INT_ST_write_data_mask                                                  (0x00000001)
#define MIPI_INT_ST_write_data(data)                                                 (0x00000001&((data)<<0))
#define MIPI_INT_ST_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define MIPI_INT_ST_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define MIPI_TYPE                                                                    0x2C
#define MIPI_TYPE_reg_addr                                                           "0x9800412C"
#define MIPI_TYPE_reg                                                                0x9800412C
#define set_MIPI_TYPE_reg(data)   (*((volatile unsigned int*) MIPI_TYPE_reg)=data)
#define get_MIPI_TYPE_reg   (*((volatile unsigned int*) MIPI_TYPE_reg))
#define MIPI_TYPE_inst_adr                                                           "0x004B"
#define MIPI_TYPE_inst                                                               0x004B
#define MIPI_TYPE_mipi_type_shift                                                    (0)
#define MIPI_TYPE_mipi_type_mask                                                     (0x00000001)
#define MIPI_TYPE_mipi_type(data)                                                    (0x00000001&((data)<<0))
#define MIPI_TYPE_mipi_type_src(data)                                                ((0x00000001&(data))>>0)
#define MIPI_TYPE_get_mipi_type(data)                                                ((0x00000001&(data))>>0)


#define CS_TRANS0                                                                    0x30
#define CS_TRANS0_reg_addr                                                           "0x98004130"
#define CS_TRANS0_reg                                                                0x98004130
#define set_CS_TRANS0_reg(data)   (*((volatile unsigned int*) CS_TRANS0_reg)=data)
#define get_CS_TRANS0_reg   (*((volatile unsigned int*) CS_TRANS0_reg))
#define CS_TRANS0_inst_adr                                                           "0x004C"
#define CS_TRANS0_inst                                                               0x004C
#define CS_TRANS0_cs_trans0_c1_shift                                                 (0)
#define CS_TRANS0_cs_trans0_c1_mask                                                  (0x0001FFFF)
#define CS_TRANS0_cs_trans0_c1(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS0_cs_trans0_c1_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS0_get_cs_trans0_c1(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS1                                                                    0x34
#define CS_TRANS1_reg_addr                                                           "0x98004134"
#define CS_TRANS1_reg                                                                0x98004134
#define set_CS_TRANS1_reg(data)   (*((volatile unsigned int*) CS_TRANS1_reg)=data)
#define get_CS_TRANS1_reg   (*((volatile unsigned int*) CS_TRANS1_reg))
#define CS_TRANS1_inst_adr                                                           "0x004D"
#define CS_TRANS1_inst                                                               0x004D
#define CS_TRANS1_cs_trans1_c2_shift                                                 (0)
#define CS_TRANS1_cs_trans1_c2_mask                                                  (0x0001FFFF)
#define CS_TRANS1_cs_trans1_c2(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS1_cs_trans1_c2_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS1_get_cs_trans1_c2(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS2                                                                    0x38
#define CS_TRANS2_reg_addr                                                           "0x98004138"
#define CS_TRANS2_reg                                                                0x98004138
#define set_CS_TRANS2_reg(data)   (*((volatile unsigned int*) CS_TRANS2_reg)=data)
#define get_CS_TRANS2_reg   (*((volatile unsigned int*) CS_TRANS2_reg))
#define CS_TRANS2_inst_adr                                                           "0x004E"
#define CS_TRANS2_inst                                                               0x004E
#define CS_TRANS2_cs_trans2_c3_shift                                                 (0)
#define CS_TRANS2_cs_trans2_c3_mask                                                  (0x0001FFFF)
#define CS_TRANS2_cs_trans2_c3(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS2_cs_trans2_c3_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS2_get_cs_trans2_c3(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS3                                                                    0x3C
#define CS_TRANS3_reg_addr                                                           "0x9800413C"
#define CS_TRANS3_reg                                                                0x9800413C
#define set_CS_TRANS3_reg(data)   (*((volatile unsigned int*) CS_TRANS3_reg)=data)
#define get_CS_TRANS3_reg   (*((volatile unsigned int*) CS_TRANS3_reg))
#define CS_TRANS3_inst_adr                                                           "0x004F"
#define CS_TRANS3_inst                                                               0x004F
#define CS_TRANS3_cs_trans3_c4_shift                                                 (0)
#define CS_TRANS3_cs_trans3_c4_mask                                                  (0x0001FFFF)
#define CS_TRANS3_cs_trans3_c4(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS3_cs_trans3_c4_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS3_get_cs_trans3_c4(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS4                                                                    0x40
#define CS_TRANS4_reg_addr                                                           "0x98004140"
#define CS_TRANS4_reg                                                                0x98004140
#define set_CS_TRANS4_reg(data)   (*((volatile unsigned int*) CS_TRANS4_reg)=data)
#define get_CS_TRANS4_reg   (*((volatile unsigned int*) CS_TRANS4_reg))
#define CS_TRANS4_inst_adr                                                           "0x0050"
#define CS_TRANS4_inst                                                               0x0050
#define CS_TRANS4_cs_trans4_c5_shift                                                 (0)
#define CS_TRANS4_cs_trans4_c5_mask                                                  (0x0001FFFF)
#define CS_TRANS4_cs_trans4_c5(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS4_cs_trans4_c5_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS4_get_cs_trans4_c5(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS5                                                                    0x44
#define CS_TRANS5_reg_addr                                                           "0x98004144"
#define CS_TRANS5_reg                                                                0x98004144
#define set_CS_TRANS5_reg(data)   (*((volatile unsigned int*) CS_TRANS5_reg)=data)
#define get_CS_TRANS5_reg   (*((volatile unsigned int*) CS_TRANS5_reg))
#define CS_TRANS5_inst_adr                                                           "0x0051"
#define CS_TRANS5_inst                                                               0x0051
#define CS_TRANS5_cs_trans5_c6_shift                                                 (0)
#define CS_TRANS5_cs_trans5_c6_mask                                                  (0x0001FFFF)
#define CS_TRANS5_cs_trans5_c6(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS5_cs_trans5_c6_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS5_get_cs_trans5_c6(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS6                                                                    0x48
#define CS_TRANS6_reg_addr                                                           "0x98004148"
#define CS_TRANS6_reg                                                                0x98004148
#define set_CS_TRANS6_reg(data)   (*((volatile unsigned int*) CS_TRANS6_reg)=data)
#define get_CS_TRANS6_reg   (*((volatile unsigned int*) CS_TRANS6_reg))
#define CS_TRANS6_inst_adr                                                           "0x0052"
#define CS_TRANS6_inst                                                               0x0052
#define CS_TRANS6_cs_trans6_c7_shift                                                 (0)
#define CS_TRANS6_cs_trans6_c7_mask                                                  (0x0001FFFF)
#define CS_TRANS6_cs_trans6_c7(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS6_cs_trans6_c7_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS6_get_cs_trans6_c7(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS7                                                                    0x4C
#define CS_TRANS7_reg_addr                                                           "0x9800414C"
#define CS_TRANS7_reg                                                                0x9800414C
#define set_CS_TRANS7_reg(data)   (*((volatile unsigned int*) CS_TRANS7_reg)=data)
#define get_CS_TRANS7_reg   (*((volatile unsigned int*) CS_TRANS7_reg))
#define CS_TRANS7_inst_adr                                                           "0x0053"
#define CS_TRANS7_inst                                                               0x0053
#define CS_TRANS7_cs_trans7_c8_shift                                                 (0)
#define CS_TRANS7_cs_trans7_c8_mask                                                  (0x0001FFFF)
#define CS_TRANS7_cs_trans7_c8(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS7_cs_trans7_c8_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS7_get_cs_trans7_c8(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS8                                                                    0x50
#define CS_TRANS8_reg_addr                                                           "0x98004150"
#define CS_TRANS8_reg                                                                0x98004150
#define set_CS_TRANS8_reg(data)   (*((volatile unsigned int*) CS_TRANS8_reg)=data)
#define get_CS_TRANS8_reg   (*((volatile unsigned int*) CS_TRANS8_reg))
#define CS_TRANS8_inst_adr                                                           "0x0054"
#define CS_TRANS8_inst                                                               0x0054
#define CS_TRANS8_cs_trans8_c9_shift                                                 (0)
#define CS_TRANS8_cs_trans8_c9_mask                                                  (0x0001FFFF)
#define CS_TRANS8_cs_trans8_c9(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS8_cs_trans8_c9_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS8_get_cs_trans8_c9(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS9                                                                    0x54
#define CS_TRANS9_reg_addr                                                           "0x98004154"
#define CS_TRANS9_reg                                                                0x98004154
#define set_CS_TRANS9_reg(data)   (*((volatile unsigned int*) CS_TRANS9_reg)=data)
#define get_CS_TRANS9_reg   (*((volatile unsigned int*) CS_TRANS9_reg))
#define CS_TRANS9_inst_adr                                                           "0x0055"
#define CS_TRANS9_inst                                                               0x0055
#define CS_TRANS9_cs_trans9_k1_shift                                                 (0)
#define CS_TRANS9_cs_trans9_k1_mask                                                  (0x0000FFFF)
#define CS_TRANS9_cs_trans9_k1(data)                                                 (0x0000FFFF&((data)<<0))
#define CS_TRANS9_cs_trans9_k1_src(data)                                             ((0x0000FFFF&(data))>>0)
#define CS_TRANS9_get_cs_trans9_k1(data)                                             ((0x0000FFFF&(data))>>0)


#define CS_TRANS10                                                                   0x58
#define CS_TRANS10_reg_addr                                                          "0x98004158"
#define CS_TRANS10_reg                                                               0x98004158
#define set_CS_TRANS10_reg(data)   (*((volatile unsigned int*) CS_TRANS10_reg)=data)
#define get_CS_TRANS10_reg   (*((volatile unsigned int*) CS_TRANS10_reg))
#define CS_TRANS10_inst_adr                                                          "0x0056"
#define CS_TRANS10_inst                                                              0x0056
#define CS_TRANS10_cs_trans10_k2_shift                                               (0)
#define CS_TRANS10_cs_trans10_k2_mask                                                (0x0000FFFF)
#define CS_TRANS10_cs_trans10_k2(data)                                               (0x0000FFFF&((data)<<0))
#define CS_TRANS10_cs_trans10_k2_src(data)                                           ((0x0000FFFF&(data))>>0)
#define CS_TRANS10_get_cs_trans10_k2(data)                                           ((0x0000FFFF&(data))>>0)


#define CS_TRANS11                                                                   0x5C
#define CS_TRANS11_reg_addr                                                          "0x9800415C"
#define CS_TRANS11_reg                                                               0x9800415C
#define set_CS_TRANS11_reg(data)   (*((volatile unsigned int*) CS_TRANS11_reg)=data)
#define get_CS_TRANS11_reg   (*((volatile unsigned int*) CS_TRANS11_reg))
#define CS_TRANS11_inst_adr                                                          "0x0057"
#define CS_TRANS11_inst                                                              0x0057
#define CS_TRANS11_cs_trans11_k3_shift                                               (0)
#define CS_TRANS11_cs_trans11_k3_mask                                                (0x0000FFFF)
#define CS_TRANS11_cs_trans11_k3(data)                                               (0x0000FFFF&((data)<<0))
#define CS_TRANS11_cs_trans11_k3_src(data)                                           ((0x0000FFFF&(data))>>0)
#define CS_TRANS11_get_cs_trans11_k3(data)                                           ((0x0000FFFF&(data))>>0)


#define SCALER_HSI                                                                   0x60
#define SCALER_HSI_reg_addr                                                          "0x98004160"
#define SCALER_HSI_reg                                                               0x98004160
#define set_SCALER_HSI_reg(data)   (*((volatile unsigned int*) SCALER_HSI_reg)=data)
#define get_SCALER_HSI_reg   (*((volatile unsigned int*) SCALER_HSI_reg))
#define SCALER_HSI_inst_adr                                                          "0x0058"
#define SCALER_HSI_inst                                                              0x0058
#define SCALER_HSI_hsi_offset_shift                                                  (16)
#define SCALER_HSI_hsi_offset_mask                                                   (0x1FFF0000)
#define SCALER_HSI_hsi_offset(data)                                                  (0x1FFF0000&((data)<<16))
#define SCALER_HSI_hsi_offset_src(data)                                              ((0x1FFF0000&(data))>>16)
#define SCALER_HSI_get_hsi_offset(data)                                              ((0x1FFF0000&(data))>>16)
#define SCALER_HSI_hsi_phase_shift                                                   (2)
#define SCALER_HSI_hsi_phase_mask                                                    (0x0000FFFC)
#define SCALER_HSI_hsi_phase(data)                                                   (0x0000FFFC&((data)<<2))
#define SCALER_HSI_hsi_phase_src(data)                                               ((0x0000FFFC&(data))>>2)
#define SCALER_HSI_get_hsi_phase(data)                                               ((0x0000FFFC&(data))>>2)


#define SCALER_HSD                                                                   0x64
#define SCALER_HSD_reg_addr                                                          "0x98004164"
#define SCALER_HSD_reg                                                               0x98004164
#define set_SCALER_HSD_reg(data)   (*((volatile unsigned int*) SCALER_HSD_reg)=data)
#define get_SCALER_HSD_reg   (*((volatile unsigned int*) SCALER_HSD_reg))
#define SCALER_HSD_inst_adr                                                          "0x0059"
#define SCALER_HSD_inst                                                              0x0059
#define SCALER_HSD_hsd_out_shift                                                     (19)
#define SCALER_HSD_hsd_out_mask                                                      (0xFFF80000)
#define SCALER_HSD_hsd_out(data)                                                     (0xFFF80000&((data)<<19))
#define SCALER_HSD_hsd_out_src(data)                                                 ((0xFFF80000&(data))>>19)
#define SCALER_HSD_get_hsd_out(data)                                                 ((0xFFF80000&(data))>>19)
#define SCALER_HSD_hsd_delta_shift                                                   (0)
#define SCALER_HSD_hsd_delta_mask                                                    (0x0007FFFF)
#define SCALER_HSD_hsd_delta(data)                                                   (0x0007FFFF&((data)<<0))
#define SCALER_HSD_hsd_delta_src(data)                                               ((0x0007FFFF&(data))>>0)
#define SCALER_HSD_get_hsd_delta(data)                                               ((0x0007FFFF&(data))>>0)


#define SCALER_VSI                                                                   0x68
#define SCALER_VSI_reg_addr                                                          "0x98004168"
#define SCALER_VSI_reg                                                               0x98004168
#define set_SCALER_VSI_reg(data)   (*((volatile unsigned int*) SCALER_VSI_reg)=data)
#define get_SCALER_VSI_reg   (*((volatile unsigned int*) SCALER_VSI_reg))
#define SCALER_VSI_inst_adr                                                          "0x005A"
#define SCALER_VSI_inst                                                              0x005A
#define SCALER_VSI_vsi_offset_shift                                                  (16)
#define SCALER_VSI_vsi_offset_mask                                                   (0x1FFF0000)
#define SCALER_VSI_vsi_offset(data)                                                  (0x1FFF0000&((data)<<16))
#define SCALER_VSI_vsi_offset_src(data)                                              ((0x1FFF0000&(data))>>16)
#define SCALER_VSI_get_vsi_offset(data)                                              ((0x1FFF0000&(data))>>16)
#define SCALER_VSI_vsi_phase_shift                                                   (2)
#define SCALER_VSI_vsi_phase_mask                                                    (0x0000FFFC)
#define SCALER_VSI_vsi_phase(data)                                                   (0x0000FFFC&((data)<<2))
#define SCALER_VSI_vsi_phase_src(data)                                               ((0x0000FFFC&(data))>>2)
#define SCALER_VSI_get_vsi_phase(data)                                               ((0x0000FFFC&(data))>>2)


#define SCALER_VSD                                                                   0x6C
#define SCALER_VSD_reg_addr                                                          "0x9800416C"
#define SCALER_VSD_reg                                                               0x9800416C
#define set_SCALER_VSD_reg(data)   (*((volatile unsigned int*) SCALER_VSD_reg)=data)
#define get_SCALER_VSD_reg   (*((volatile unsigned int*) SCALER_VSD_reg))
#define SCALER_VSD_inst_adr                                                          "0x005B"
#define SCALER_VSD_inst                                                              0x005B
#define SCALER_VSD_vsd_out_shift                                                     (19)
#define SCALER_VSD_vsd_out_mask                                                      (0xFFF80000)
#define SCALER_VSD_vsd_out(data)                                                     (0xFFF80000&((data)<<19))
#define SCALER_VSD_vsd_out_src(data)                                                 ((0xFFF80000&(data))>>19)
#define SCALER_VSD_get_vsd_out(data)                                                 ((0xFFF80000&(data))>>19)
#define SCALER_VSD_vsd_delta_shift                                                   (0)
#define SCALER_VSD_vsd_delta_mask                                                    (0x0007FFFF)
#define SCALER_VSD_vsd_delta(data)                                                   (0x0007FFFF&((data)<<0))
#define SCALER_VSD_vsd_delta_src(data)                                               ((0x0007FFFF&(data))>>0)
#define SCALER_VSD_get_vsd_delta(data)                                               ((0x0007FFFF&(data))>>0)


#define SCALER_HSYNC0                                                                0x70
#define SCALER_HSYNC0_reg_addr                                                       "0x98004170"
#define SCALER_HSYNC0_reg                                                            0x98004170
#define set_SCALER_HSYNC0_reg(data)   (*((volatile unsigned int*) SCALER_HSYNC0_reg)=data)
#define get_SCALER_HSYNC0_reg   (*((volatile unsigned int*) SCALER_HSYNC0_reg))
#define SCALER_HSYNC0_inst_adr                                                       "0x005C"
#define SCALER_HSYNC0_inst                                                           0x005C
#define SCALER_HSYNC0_hsync0_c1_shift                                                (16)
#define SCALER_HSYNC0_hsync0_c1_mask                                                 (0x3FFF0000)
#define SCALER_HSYNC0_hsync0_c1(data)                                                (0x3FFF0000&((data)<<16))
#define SCALER_HSYNC0_hsync0_c1_src(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC0_get_hsync0_c1(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC0_hsync0_c0_shift                                                (0)
#define SCALER_HSYNC0_hsync0_c0_mask                                                 (0x00003FFF)
#define SCALER_HSYNC0_hsync0_c0(data)                                                (0x00003FFF&((data)<<0))
#define SCALER_HSYNC0_hsync0_c0_src(data)                                            ((0x00003FFF&(data))>>0)
#define SCALER_HSYNC0_get_hsync0_c0(data)                                            ((0x00003FFF&(data))>>0)


#define SCALER_HSYNC1                                                                0x74
#define SCALER_HSYNC1_reg_addr                                                       "0x98004174"
#define SCALER_HSYNC1_reg                                                            0x98004174
#define set_SCALER_HSYNC1_reg(data)   (*((volatile unsigned int*) SCALER_HSYNC1_reg)=data)
#define get_SCALER_HSYNC1_reg   (*((volatile unsigned int*) SCALER_HSYNC1_reg))
#define SCALER_HSYNC1_inst_adr                                                       "0x005D"
#define SCALER_HSYNC1_inst                                                           0x005D
#define SCALER_HSYNC1_hsync1_c1_shift                                                (16)
#define SCALER_HSYNC1_hsync1_c1_mask                                                 (0x3FFF0000)
#define SCALER_HSYNC1_hsync1_c1(data)                                                (0x3FFF0000&((data)<<16))
#define SCALER_HSYNC1_hsync1_c1_src(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC1_get_hsync1_c1(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC1_hsync1_c0_shift                                                (0)
#define SCALER_HSYNC1_hsync1_c0_mask                                                 (0x00003FFF)
#define SCALER_HSYNC1_hsync1_c0(data)                                                (0x00003FFF&((data)<<0))
#define SCALER_HSYNC1_hsync1_c0_src(data)                                            ((0x00003FFF&(data))>>0)
#define SCALER_HSYNC1_get_hsync1_c0(data)                                            ((0x00003FFF&(data))>>0)


#define SCALER_HSYNC2                                                                0x78
#define SCALER_HSYNC2_reg_addr                                                       "0x98004178"
#define SCALER_HSYNC2_reg                                                            0x98004178
#define set_SCALER_HSYNC2_reg(data)   (*((volatile unsigned int*) SCALER_HSYNC2_reg)=data)
#define get_SCALER_HSYNC2_reg   (*((volatile unsigned int*) SCALER_HSYNC2_reg))
#define SCALER_HSYNC2_inst_adr                                                       "0x005E"
#define SCALER_HSYNC2_inst                                                           0x005E
#define SCALER_HSYNC2_hsync2_c1_shift                                                (16)
#define SCALER_HSYNC2_hsync2_c1_mask                                                 (0x3FFF0000)
#define SCALER_HSYNC2_hsync2_c1(data)                                                (0x3FFF0000&((data)<<16))
#define SCALER_HSYNC2_hsync2_c1_src(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC2_get_hsync2_c1(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC2_hsync2_c0_shift                                                (0)
#define SCALER_HSYNC2_hsync2_c0_mask                                                 (0x00003FFF)
#define SCALER_HSYNC2_hsync2_c0(data)                                                (0x00003FFF&((data)<<0))
#define SCALER_HSYNC2_hsync2_c0_src(data)                                            ((0x00003FFF&(data))>>0)
#define SCALER_HSYNC2_get_hsync2_c0(data)                                            ((0x00003FFF&(data))>>0)


#define SCALER_HSYNC3                                                                0x7C
#define SCALER_HSYNC3_reg_addr                                                       "0x9800417C"
#define SCALER_HSYNC3_reg                                                            0x9800417C
#define set_SCALER_HSYNC3_reg(data)   (*((volatile unsigned int*) SCALER_HSYNC3_reg)=data)
#define get_SCALER_HSYNC3_reg   (*((volatile unsigned int*) SCALER_HSYNC3_reg))
#define SCALER_HSYNC3_inst_adr                                                       "0x005F"
#define SCALER_HSYNC3_inst                                                           0x005F
#define SCALER_HSYNC3_hsync3_c1_shift                                                (16)
#define SCALER_HSYNC3_hsync3_c1_mask                                                 (0x3FFF0000)
#define SCALER_HSYNC3_hsync3_c1(data)                                                (0x3FFF0000&((data)<<16))
#define SCALER_HSYNC3_hsync3_c1_src(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC3_get_hsync3_c1(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC3_hsync3_c0_shift                                                (0)
#define SCALER_HSYNC3_hsync3_c0_mask                                                 (0x00003FFF)
#define SCALER_HSYNC3_hsync3_c0(data)                                                (0x00003FFF&((data)<<0))
#define SCALER_HSYNC3_hsync3_c0_src(data)                                            ((0x00003FFF&(data))>>0)
#define SCALER_HSYNC3_get_hsync3_c0(data)                                            ((0x00003FFF&(data))>>0)


#define SCALER_HSYNC4                                                                0x80
#define SCALER_HSYNC4_reg_addr                                                       "0x98004180"
#define SCALER_HSYNC4_reg                                                            0x98004180
#define set_SCALER_HSYNC4_reg(data)   (*((volatile unsigned int*) SCALER_HSYNC4_reg)=data)
#define get_SCALER_HSYNC4_reg   (*((volatile unsigned int*) SCALER_HSYNC4_reg))
#define SCALER_HSYNC4_inst_adr                                                       "0x0060"
#define SCALER_HSYNC4_inst                                                           0x0060
#define SCALER_HSYNC4_hsync4_c1_shift                                                (16)
#define SCALER_HSYNC4_hsync4_c1_mask                                                 (0x3FFF0000)
#define SCALER_HSYNC4_hsync4_c1(data)                                                (0x3FFF0000&((data)<<16))
#define SCALER_HSYNC4_hsync4_c1_src(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC4_get_hsync4_c1(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC4_hsync4_c0_shift                                                (0)
#define SCALER_HSYNC4_hsync4_c0_mask                                                 (0x00003FFF)
#define SCALER_HSYNC4_hsync4_c0(data)                                                (0x00003FFF&((data)<<0))
#define SCALER_HSYNC4_hsync4_c0_src(data)                                            ((0x00003FFF&(data))>>0)
#define SCALER_HSYNC4_get_hsync4_c0(data)                                            ((0x00003FFF&(data))>>0)


#define SCALER_HSYNC5                                                                0x84
#define SCALER_HSYNC5_reg_addr                                                       "0x98004184"
#define SCALER_HSYNC5_reg                                                            0x98004184
#define set_SCALER_HSYNC5_reg(data)   (*((volatile unsigned int*) SCALER_HSYNC5_reg)=data)
#define get_SCALER_HSYNC5_reg   (*((volatile unsigned int*) SCALER_HSYNC5_reg))
#define SCALER_HSYNC5_inst_adr                                                       "0x0061"
#define SCALER_HSYNC5_inst                                                           0x0061
#define SCALER_HSYNC5_hsync5_c1_shift                                                (16)
#define SCALER_HSYNC5_hsync5_c1_mask                                                 (0x3FFF0000)
#define SCALER_HSYNC5_hsync5_c1(data)                                                (0x3FFF0000&((data)<<16))
#define SCALER_HSYNC5_hsync5_c1_src(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC5_get_hsync5_c1(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC5_hsync5_c0_shift                                                (0)
#define SCALER_HSYNC5_hsync5_c0_mask                                                 (0x00003FFF)
#define SCALER_HSYNC5_hsync5_c0(data)                                                (0x00003FFF&((data)<<0))
#define SCALER_HSYNC5_hsync5_c0_src(data)                                            ((0x00003FFF&(data))>>0)
#define SCALER_HSYNC5_get_hsync5_c0(data)                                            ((0x00003FFF&(data))>>0)


#define SCALER_HSYNC6                                                                0x88
#define SCALER_HSYNC6_reg_addr                                                       "0x98004188"
#define SCALER_HSYNC6_reg                                                            0x98004188
#define set_SCALER_HSYNC6_reg(data)   (*((volatile unsigned int*) SCALER_HSYNC6_reg)=data)
#define get_SCALER_HSYNC6_reg   (*((volatile unsigned int*) SCALER_HSYNC6_reg))
#define SCALER_HSYNC6_inst_adr                                                       "0x0062"
#define SCALER_HSYNC6_inst                                                           0x0062
#define SCALER_HSYNC6_hsync6_c1_shift                                                (16)
#define SCALER_HSYNC6_hsync6_c1_mask                                                 (0x3FFF0000)
#define SCALER_HSYNC6_hsync6_c1(data)                                                (0x3FFF0000&((data)<<16))
#define SCALER_HSYNC6_hsync6_c1_src(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC6_get_hsync6_c1(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC6_hsync6_c0_shift                                                (0)
#define SCALER_HSYNC6_hsync6_c0_mask                                                 (0x00003FFF)
#define SCALER_HSYNC6_hsync6_c0(data)                                                (0x00003FFF&((data)<<0))
#define SCALER_HSYNC6_hsync6_c0_src(data)                                            ((0x00003FFF&(data))>>0)
#define SCALER_HSYNC6_get_hsync6_c0(data)                                            ((0x00003FFF&(data))>>0)


#define SCALER_HSYNC7                                                                0x8C
#define SCALER_HSYNC7_reg_addr                                                       "0x9800418C"
#define SCALER_HSYNC7_reg                                                            0x9800418C
#define set_SCALER_HSYNC7_reg(data)   (*((volatile unsigned int*) SCALER_HSYNC7_reg)=data)
#define get_SCALER_HSYNC7_reg   (*((volatile unsigned int*) SCALER_HSYNC7_reg))
#define SCALER_HSYNC7_inst_adr                                                       "0x0063"
#define SCALER_HSYNC7_inst                                                           0x0063
#define SCALER_HSYNC7_hsync7_c1_shift                                                (16)
#define SCALER_HSYNC7_hsync7_c1_mask                                                 (0x3FFF0000)
#define SCALER_HSYNC7_hsync7_c1(data)                                                (0x3FFF0000&((data)<<16))
#define SCALER_HSYNC7_hsync7_c1_src(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC7_get_hsync7_c1(data)                                            ((0x3FFF0000&(data))>>16)
#define SCALER_HSYNC7_hsync7_c0_shift                                                (0)
#define SCALER_HSYNC7_hsync7_c0_mask                                                 (0x00003FFF)
#define SCALER_HSYNC7_hsync7_c0(data)                                                (0x00003FFF&((data)<<0))
#define SCALER_HSYNC7_hsync7_c0_src(data)                                            ((0x00003FFF&(data))>>0)
#define SCALER_HSYNC7_get_hsync7_c0(data)                                            ((0x00003FFF&(data))>>0)


#define SCALER_HSCC0                                                                 0x90
#define SCALER_HSCC0_reg_addr                                                        "0x98004190"
#define SCALER_HSCC0_reg                                                             0x98004190
#define set_SCALER_HSCC0_reg(data)   (*((volatile unsigned int*) SCALER_HSCC0_reg)=data)
#define get_SCALER_HSCC0_reg   (*((volatile unsigned int*) SCALER_HSCC0_reg))
#define SCALER_HSCC0_inst_adr                                                        "0x0064"
#define SCALER_HSCC0_inst                                                            0x0064
#define SCALER_HSCC0_hscc0_c1_shift                                                  (16)
#define SCALER_HSCC0_hscc0_c1_mask                                                   (0x3FFF0000)
#define SCALER_HSCC0_hscc0_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_HSCC0_hscc0_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC0_get_hscc0_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC0_hscc0_c0_shift                                                  (0)
#define SCALER_HSCC0_hscc0_c0_mask                                                   (0x00003FFF)
#define SCALER_HSCC0_hscc0_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_HSCC0_hscc0_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_HSCC0_get_hscc0_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_HSCC1                                                                 0x94
#define SCALER_HSCC1_reg_addr                                                        "0x98004194"
#define SCALER_HSCC1_reg                                                             0x98004194
#define set_SCALER_HSCC1_reg(data)   (*((volatile unsigned int*) SCALER_HSCC1_reg)=data)
#define get_SCALER_HSCC1_reg   (*((volatile unsigned int*) SCALER_HSCC1_reg))
#define SCALER_HSCC1_inst_adr                                                        "0x0065"
#define SCALER_HSCC1_inst                                                            0x0065
#define SCALER_HSCC1_hscc1_c1_shift                                                  (16)
#define SCALER_HSCC1_hscc1_c1_mask                                                   (0x3FFF0000)
#define SCALER_HSCC1_hscc1_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_HSCC1_hscc1_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC1_get_hscc1_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC1_hscc1_c0_shift                                                  (0)
#define SCALER_HSCC1_hscc1_c0_mask                                                   (0x00003FFF)
#define SCALER_HSCC1_hscc1_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_HSCC1_hscc1_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_HSCC1_get_hscc1_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_HSCC2                                                                 0x98
#define SCALER_HSCC2_reg_addr                                                        "0x98004198"
#define SCALER_HSCC2_reg                                                             0x98004198
#define set_SCALER_HSCC2_reg(data)   (*((volatile unsigned int*) SCALER_HSCC2_reg)=data)
#define get_SCALER_HSCC2_reg   (*((volatile unsigned int*) SCALER_HSCC2_reg))
#define SCALER_HSCC2_inst_adr                                                        "0x0066"
#define SCALER_HSCC2_inst                                                            0x0066
#define SCALER_HSCC2_hscc2_c1_shift                                                  (16)
#define SCALER_HSCC2_hscc2_c1_mask                                                   (0x3FFF0000)
#define SCALER_HSCC2_hscc2_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_HSCC2_hscc2_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC2_get_hscc2_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC2_hscc2_c0_shift                                                  (0)
#define SCALER_HSCC2_hscc2_c0_mask                                                   (0x00003FFF)
#define SCALER_HSCC2_hscc2_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_HSCC2_hscc2_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_HSCC2_get_hscc2_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_HSCC3                                                                 0x9C
#define SCALER_HSCC3_reg_addr                                                        "0x9800419C"
#define SCALER_HSCC3_reg                                                             0x9800419C
#define set_SCALER_HSCC3_reg(data)   (*((volatile unsigned int*) SCALER_HSCC3_reg)=data)
#define get_SCALER_HSCC3_reg   (*((volatile unsigned int*) SCALER_HSCC3_reg))
#define SCALER_HSCC3_inst_adr                                                        "0x0067"
#define SCALER_HSCC3_inst                                                            0x0067
#define SCALER_HSCC3_hscc3_c1_shift                                                  (16)
#define SCALER_HSCC3_hscc3_c1_mask                                                   (0x3FFF0000)
#define SCALER_HSCC3_hscc3_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_HSCC3_hscc3_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC3_get_hscc3_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC3_hscc3_c0_shift                                                  (0)
#define SCALER_HSCC3_hscc3_c0_mask                                                   (0x00003FFF)
#define SCALER_HSCC3_hscc3_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_HSCC3_hscc3_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_HSCC3_get_hscc3_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_HSCC4                                                                 0xA0
#define SCALER_HSCC4_reg_addr                                                        "0x980041A0"
#define SCALER_HSCC4_reg                                                             0x980041A0
#define set_SCALER_HSCC4_reg(data)   (*((volatile unsigned int*) SCALER_HSCC4_reg)=data)
#define get_SCALER_HSCC4_reg   (*((volatile unsigned int*) SCALER_HSCC4_reg))
#define SCALER_HSCC4_inst_adr                                                        "0x0068"
#define SCALER_HSCC4_inst                                                            0x0068
#define SCALER_HSCC4_hscc4_c1_shift                                                  (16)
#define SCALER_HSCC4_hscc4_c1_mask                                                   (0x3FFF0000)
#define SCALER_HSCC4_hscc4_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_HSCC4_hscc4_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC4_get_hscc4_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC4_hscc4_c0_shift                                                  (0)
#define SCALER_HSCC4_hscc4_c0_mask                                                   (0x00003FFF)
#define SCALER_HSCC4_hscc4_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_HSCC4_hscc4_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_HSCC4_get_hscc4_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_HSCC5                                                                 0xA4
#define SCALER_HSCC5_reg_addr                                                        "0x980041A4"
#define SCALER_HSCC5_reg                                                             0x980041A4
#define set_SCALER_HSCC5_reg(data)   (*((volatile unsigned int*) SCALER_HSCC5_reg)=data)
#define get_SCALER_HSCC5_reg   (*((volatile unsigned int*) SCALER_HSCC5_reg))
#define SCALER_HSCC5_inst_adr                                                        "0x0069"
#define SCALER_HSCC5_inst                                                            0x0069
#define SCALER_HSCC5_hscc5_c1_shift                                                  (16)
#define SCALER_HSCC5_hscc5_c1_mask                                                   (0x3FFF0000)
#define SCALER_HSCC5_hscc5_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_HSCC5_hscc5_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC5_get_hscc5_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC5_hscc5_c0_shift                                                  (0)
#define SCALER_HSCC5_hscc5_c0_mask                                                   (0x00003FFF)
#define SCALER_HSCC5_hscc5_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_HSCC5_hscc5_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_HSCC5_get_hscc5_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_HSCC6                                                                 0xA8
#define SCALER_HSCC6_reg_addr                                                        "0x980041A8"
#define SCALER_HSCC6_reg                                                             0x980041A8
#define set_SCALER_HSCC6_reg(data)   (*((volatile unsigned int*) SCALER_HSCC6_reg)=data)
#define get_SCALER_HSCC6_reg   (*((volatile unsigned int*) SCALER_HSCC6_reg))
#define SCALER_HSCC6_inst_adr                                                        "0x006A"
#define SCALER_HSCC6_inst                                                            0x006A
#define SCALER_HSCC6_hscc6_c1_shift                                                  (16)
#define SCALER_HSCC6_hscc6_c1_mask                                                   (0x3FFF0000)
#define SCALER_HSCC6_hscc6_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_HSCC6_hscc6_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC6_get_hscc6_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC6_hscc6_c0_shift                                                  (0)
#define SCALER_HSCC6_hscc6_c0_mask                                                   (0x00003FFF)
#define SCALER_HSCC6_hscc6_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_HSCC6_hscc6_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_HSCC6_get_hscc6_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_HSCC7                                                                 0xAC
#define SCALER_HSCC7_reg_addr                                                        "0x980041AC"
#define SCALER_HSCC7_reg                                                             0x980041AC
#define set_SCALER_HSCC7_reg(data)   (*((volatile unsigned int*) SCALER_HSCC7_reg)=data)
#define get_SCALER_HSCC7_reg   (*((volatile unsigned int*) SCALER_HSCC7_reg))
#define SCALER_HSCC7_inst_adr                                                        "0x006B"
#define SCALER_HSCC7_inst                                                            0x006B
#define SCALER_HSCC7_hscc7_c1_shift                                                  (16)
#define SCALER_HSCC7_hscc7_c1_mask                                                   (0x3FFF0000)
#define SCALER_HSCC7_hscc7_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_HSCC7_hscc7_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC7_get_hscc7_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_HSCC7_hscc7_c0_shift                                                  (0)
#define SCALER_HSCC7_hscc7_c0_mask                                                   (0x00003FFF)
#define SCALER_HSCC7_hscc7_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_HSCC7_hscc7_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_HSCC7_get_hscc7_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_VSYC0                                                                 0xB0
#define SCALER_VSYC0_reg_addr                                                        "0x980041B0"
#define SCALER_VSYC0_reg                                                             0x980041B0
#define set_SCALER_VSYC0_reg(data)   (*((volatile unsigned int*) SCALER_VSYC0_reg)=data)
#define get_SCALER_VSYC0_reg   (*((volatile unsigned int*) SCALER_VSYC0_reg))
#define SCALER_VSYC0_inst_adr                                                        "0x006C"
#define SCALER_VSYC0_inst                                                            0x006C
#define SCALER_VSYC0_vsyc0_c1_shift                                                  (16)
#define SCALER_VSYC0_vsyc0_c1_mask                                                   (0x3FFF0000)
#define SCALER_VSYC0_vsyc0_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_VSYC0_vsyc0_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSYC0_get_vsyc0_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSYC0_vsyc0_c0_shift                                                  (0)
#define SCALER_VSYC0_vsyc0_c0_mask                                                   (0x00003FFF)
#define SCALER_VSYC0_vsyc0_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_VSYC0_vsyc0_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_VSYC0_get_vsyc0_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_VSYC1                                                                 0xB4
#define SCALER_VSYC1_reg_addr                                                        "0x980041B4"
#define SCALER_VSYC1_reg                                                             0x980041B4
#define set_SCALER_VSYC1_reg(data)   (*((volatile unsigned int*) SCALER_VSYC1_reg)=data)
#define get_SCALER_VSYC1_reg   (*((volatile unsigned int*) SCALER_VSYC1_reg))
#define SCALER_VSYC1_inst_adr                                                        "0x006D"
#define SCALER_VSYC1_inst                                                            0x006D
#define SCALER_VSYC1_vsyc1_c1_shift                                                  (16)
#define SCALER_VSYC1_vsyc1_c1_mask                                                   (0x3FFF0000)
#define SCALER_VSYC1_vsyc1_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_VSYC1_vsyc1_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSYC1_get_vsyc1_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSYC1_vsyc1_c0_shift                                                  (0)
#define SCALER_VSYC1_vsyc1_c0_mask                                                   (0x00003FFF)
#define SCALER_VSYC1_vsyc1_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_VSYC1_vsyc1_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_VSYC1_get_vsyc1_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_VSYC2                                                                 0xB8
#define SCALER_VSYC2_reg_addr                                                        "0x980041B8"
#define SCALER_VSYC2_reg                                                             0x980041B8
#define set_SCALER_VSYC2_reg(data)   (*((volatile unsigned int*) SCALER_VSYC2_reg)=data)
#define get_SCALER_VSYC2_reg   (*((volatile unsigned int*) SCALER_VSYC2_reg))
#define SCALER_VSYC2_inst_adr                                                        "0x006E"
#define SCALER_VSYC2_inst                                                            0x006E
#define SCALER_VSYC2_vsyc2_c1_shift                                                  (16)
#define SCALER_VSYC2_vsyc2_c1_mask                                                   (0x3FFF0000)
#define SCALER_VSYC2_vsyc2_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_VSYC2_vsyc2_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSYC2_get_vsyc2_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSYC2_vsyc2_c0_shift                                                  (0)
#define SCALER_VSYC2_vsyc2_c0_mask                                                   (0x00003FFF)
#define SCALER_VSYC2_vsyc2_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_VSYC2_vsyc2_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_VSYC2_get_vsyc2_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_VSYC3                                                                 0xBC
#define SCALER_VSYC3_reg_addr                                                        "0x980041BC"
#define SCALER_VSYC3_reg                                                             0x980041BC
#define set_SCALER_VSYC3_reg(data)   (*((volatile unsigned int*) SCALER_VSYC3_reg)=data)
#define get_SCALER_VSYC3_reg   (*((volatile unsigned int*) SCALER_VSYC3_reg))
#define SCALER_VSYC3_inst_adr                                                        "0x006F"
#define SCALER_VSYC3_inst                                                            0x006F
#define SCALER_VSYC3_vsyc3_c1_shift                                                  (16)
#define SCALER_VSYC3_vsyc3_c1_mask                                                   (0x3FFF0000)
#define SCALER_VSYC3_vsyc3_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_VSYC3_vsyc3_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSYC3_get_vsyc3_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSYC3_vsyc3_c0_shift                                                  (0)
#define SCALER_VSYC3_vsyc3_c0_mask                                                   (0x00003FFF)
#define SCALER_VSYC3_vsyc3_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_VSYC3_vsyc3_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_VSYC3_get_vsyc3_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_VSCC0                                                                 0xC0
#define SCALER_VSCC0_reg_addr                                                        "0x980041C0"
#define SCALER_VSCC0_reg                                                             0x980041C0
#define set_SCALER_VSCC0_reg(data)   (*((volatile unsigned int*) SCALER_VSCC0_reg)=data)
#define get_SCALER_VSCC0_reg   (*((volatile unsigned int*) SCALER_VSCC0_reg))
#define SCALER_VSCC0_inst_adr                                                        "0x0070"
#define SCALER_VSCC0_inst                                                            0x0070
#define SCALER_VSCC0_vscc0_c1_shift                                                  (16)
#define SCALER_VSCC0_vscc0_c1_mask                                                   (0x3FFF0000)
#define SCALER_VSCC0_vscc0_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_VSCC0_vscc0_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSCC0_get_vscc0_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSCC0_vscc0_c0_shift                                                  (0)
#define SCALER_VSCC0_vscc0_c0_mask                                                   (0x00003FFF)
#define SCALER_VSCC0_vscc0_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_VSCC0_vscc0_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_VSCC0_get_vscc0_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_VSCC1                                                                 0xC4
#define SCALER_VSCC1_reg_addr                                                        "0x980041C4"
#define SCALER_VSCC1_reg                                                             0x980041C4
#define set_SCALER_VSCC1_reg(data)   (*((volatile unsigned int*) SCALER_VSCC1_reg)=data)
#define get_SCALER_VSCC1_reg   (*((volatile unsigned int*) SCALER_VSCC1_reg))
#define SCALER_VSCC1_inst_adr                                                        "0x0071"
#define SCALER_VSCC1_inst                                                            0x0071
#define SCALER_VSCC1_vscc1_c1_shift                                                  (16)
#define SCALER_VSCC1_vscc1_c1_mask                                                   (0x3FFF0000)
#define SCALER_VSCC1_vscc1_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_VSCC1_vscc1_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSCC1_get_vscc1_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSCC1_vscc1_c0_shift                                                  (0)
#define SCALER_VSCC1_vscc1_c0_mask                                                   (0x00003FFF)
#define SCALER_VSCC1_vscc1_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_VSCC1_vscc1_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_VSCC1_get_vscc1_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_VSCC2                                                                 0xC8
#define SCALER_VSCC2_reg_addr                                                        "0x980041C8"
#define SCALER_VSCC2_reg                                                             0x980041C8
#define set_SCALER_VSCC2_reg(data)   (*((volatile unsigned int*) SCALER_VSCC2_reg)=data)
#define get_SCALER_VSCC2_reg   (*((volatile unsigned int*) SCALER_VSCC2_reg))
#define SCALER_VSCC2_inst_adr                                                        "0x0072"
#define SCALER_VSCC2_inst                                                            0x0072
#define SCALER_VSCC2_vscc2_c1_shift                                                  (16)
#define SCALER_VSCC2_vscc2_c1_mask                                                   (0x3FFF0000)
#define SCALER_VSCC2_vscc2_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_VSCC2_vscc2_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSCC2_get_vscc2_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSCC2_vscc2_c0_shift                                                  (0)
#define SCALER_VSCC2_vscc2_c0_mask                                                   (0x00003FFF)
#define SCALER_VSCC2_vscc2_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_VSCC2_vscc2_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_VSCC2_get_vscc2_c0(data)                                              ((0x00003FFF&(data))>>0)


#define SCALER_VSCC3                                                                 0xCC
#define SCALER_VSCC3_reg_addr                                                        "0x980041CC"
#define SCALER_VSCC3_reg                                                             0x980041CC
#define set_SCALER_VSCC3_reg(data)   (*((volatile unsigned int*) SCALER_VSCC3_reg)=data)
#define get_SCALER_VSCC3_reg   (*((volatile unsigned int*) SCALER_VSCC3_reg))
#define SCALER_VSCC3_inst_adr                                                        "0x0073"
#define SCALER_VSCC3_inst                                                            0x0073
#define SCALER_VSCC3_vscc3_c1_shift                                                  (16)
#define SCALER_VSCC3_vscc3_c1_mask                                                   (0x3FFF0000)
#define SCALER_VSCC3_vscc3_c1(data)                                                  (0x3FFF0000&((data)<<16))
#define SCALER_VSCC3_vscc3_c1_src(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSCC3_get_vscc3_c1(data)                                              ((0x3FFF0000&(data))>>16)
#define SCALER_VSCC3_vscc3_c0_shift                                                  (0)
#define SCALER_VSCC3_vscc3_c0_mask                                                   (0x00003FFF)
#define SCALER_VSCC3_vscc3_c0(data)                                                  (0x00003FFF&((data)<<0))
#define SCALER_VSCC3_vscc3_c0_src(data)                                              ((0x00003FFF&(data))>>0)
#define SCALER_VSCC3_get_vscc3_c0(data)                                              ((0x00003FFF&(data))>>0)


#define CONSTANT_ALPHA                                                               0xD0
#define CONSTANT_ALPHA_reg_addr                                                      "0x980041D0"
#define CONSTANT_ALPHA_reg                                                           0x980041D0
#define set_CONSTANT_ALPHA_reg(data)   (*((volatile unsigned int*) CONSTANT_ALPHA_reg)=data)
#define get_CONSTANT_ALPHA_reg   (*((volatile unsigned int*) CONSTANT_ALPHA_reg))
#define CONSTANT_ALPHA_inst_adr                                                      "0x0074"
#define CONSTANT_ALPHA_inst                                                          0x0074
#define CONSTANT_ALPHA_alpha_shift                                                   (0)
#define CONSTANT_ALPHA_alpha_mask                                                    (0x000000FF)
#define CONSTANT_ALPHA_alpha(data)                                                   (0x000000FF&((data)<<0))
#define CONSTANT_ALPHA_alpha_src(data)                                               ((0x000000FF&(data))>>0)
#define CONSTANT_ALPHA_get_alpha(data)                                               ((0x000000FF&(data))>>0)


#define MIPI_BIST_MODE                                                               0xD4
#define MIPI_BIST_MODE_reg_addr                                                      "0x980041D4"
#define MIPI_BIST_MODE_reg                                                           0x980041D4
#define set_MIPI_BIST_MODE_reg(data)   (*((volatile unsigned int*) MIPI_BIST_MODE_reg)=data)
#define get_MIPI_BIST_MODE_reg   (*((volatile unsigned int*) MIPI_BIST_MODE_reg))
#define MIPI_BIST_MODE_inst_adr                                                      "0x0075"
#define MIPI_BIST_MODE_inst                                                          0x0075
#define MIPI_BIST_MODE_drf_test_resume_shift                                         (2)
#define MIPI_BIST_MODE_drf_test_resume_mask                                          (0x00000004)
#define MIPI_BIST_MODE_drf_test_resume(data)                                         (0x00000004&((data)<<2))
#define MIPI_BIST_MODE_drf_test_resume_src(data)                                     ((0x00000004&(data))>>2)
#define MIPI_BIST_MODE_get_drf_test_resume(data)                                     ((0x00000004&(data))>>2)
#define MIPI_BIST_MODE_drf_bist_mode_shift                                           (1)
#define MIPI_BIST_MODE_drf_bist_mode_mask                                            (0x00000002)
#define MIPI_BIST_MODE_drf_bist_mode(data)                                           (0x00000002&((data)<<1))
#define MIPI_BIST_MODE_drf_bist_mode_src(data)                                       ((0x00000002&(data))>>1)
#define MIPI_BIST_MODE_get_drf_bist_mode(data)                                       ((0x00000002&(data))>>1)
#define MIPI_BIST_MODE_bist_mode_shift                                               (0)
#define MIPI_BIST_MODE_bist_mode_mask                                                (0x00000001)
#define MIPI_BIST_MODE_bist_mode(data)                                               (0x00000001&((data)<<0))
#define MIPI_BIST_MODE_bist_mode_src(data)                                           ((0x00000001&(data))>>0)
#define MIPI_BIST_MODE_get_bist_mode(data)                                           ((0x00000001&(data))>>0)


#define MIPI_BIST_RESULT0                                                            0xD8
#define MIPI_BIST_RESULT0_reg_addr                                                   "0x980041D8"
#define MIPI_BIST_RESULT0_reg                                                        0x980041D8
#define set_MIPI_BIST_RESULT0_reg(data)   (*((volatile unsigned int*) MIPI_BIST_RESULT0_reg)=data)
#define get_MIPI_BIST_RESULT0_reg   (*((volatile unsigned int*) MIPI_BIST_RESULT0_reg))
#define MIPI_BIST_RESULT0_inst_adr                                                   "0x0076"
#define MIPI_BIST_RESULT0_inst                                                       0x0076
#define MIPI_BIST_RESULT0_drf_start_pause_shift                                      (14)
#define MIPI_BIST_RESULT0_drf_start_pause_mask                                       (0x00004000)
#define MIPI_BIST_RESULT0_drf_start_pause(data)                                      (0x00004000&((data)<<14))
#define MIPI_BIST_RESULT0_drf_start_pause_src(data)                                  ((0x00004000&(data))>>14)
#define MIPI_BIST_RESULT0_get_drf_start_pause(data)                                  ((0x00004000&(data))>>14)
#define MIPI_BIST_RESULT0_drf_bist_fail5_shift                                       (13)
#define MIPI_BIST_RESULT0_drf_bist_fail5_mask                                        (0x00002000)
#define MIPI_BIST_RESULT0_drf_bist_fail5(data)                                       (0x00002000&((data)<<13))
#define MIPI_BIST_RESULT0_drf_bist_fail5_src(data)                                   ((0x00002000&(data))>>13)
#define MIPI_BIST_RESULT0_get_drf_bist_fail5(data)                                   ((0x00002000&(data))>>13)
#define MIPI_BIST_RESULT0_drf_bist_fail4_shift                                       (12)
#define MIPI_BIST_RESULT0_drf_bist_fail4_mask                                        (0x00001000)
#define MIPI_BIST_RESULT0_drf_bist_fail4(data)                                       (0x00001000&((data)<<12))
#define MIPI_BIST_RESULT0_drf_bist_fail4_src(data)                                   ((0x00001000&(data))>>12)
#define MIPI_BIST_RESULT0_get_drf_bist_fail4(data)                                   ((0x00001000&(data))>>12)
#define MIPI_BIST_RESULT0_drf_bist_fail3_shift                                       (11)
#define MIPI_BIST_RESULT0_drf_bist_fail3_mask                                        (0x00000800)
#define MIPI_BIST_RESULT0_drf_bist_fail3(data)                                       (0x00000800&((data)<<11))
#define MIPI_BIST_RESULT0_drf_bist_fail3_src(data)                                   ((0x00000800&(data))>>11)
#define MIPI_BIST_RESULT0_get_drf_bist_fail3(data)                                   ((0x00000800&(data))>>11)
#define MIPI_BIST_RESULT0_drf_bist_fail2_shift                                       (10)
#define MIPI_BIST_RESULT0_drf_bist_fail2_mask                                        (0x00000400)
#define MIPI_BIST_RESULT0_drf_bist_fail2(data)                                       (0x00000400&((data)<<10))
#define MIPI_BIST_RESULT0_drf_bist_fail2_src(data)                                   ((0x00000400&(data))>>10)
#define MIPI_BIST_RESULT0_get_drf_bist_fail2(data)                                   ((0x00000400&(data))>>10)
#define MIPI_BIST_RESULT0_drf_bist_fail1_shift                                       (9)
#define MIPI_BIST_RESULT0_drf_bist_fail1_mask                                        (0x00000200)
#define MIPI_BIST_RESULT0_drf_bist_fail1(data)                                       (0x00000200&((data)<<9))
#define MIPI_BIST_RESULT0_drf_bist_fail1_src(data)                                   ((0x00000200&(data))>>9)
#define MIPI_BIST_RESULT0_get_drf_bist_fail1(data)                                   ((0x00000200&(data))>>9)
#define MIPI_BIST_RESULT0_drf_bist_fail0_shift                                       (8)
#define MIPI_BIST_RESULT0_drf_bist_fail0_mask                                        (0x00000100)
#define MIPI_BIST_RESULT0_drf_bist_fail0(data)                                       (0x00000100&((data)<<8))
#define MIPI_BIST_RESULT0_drf_bist_fail0_src(data)                                   ((0x00000100&(data))>>8)
#define MIPI_BIST_RESULT0_get_drf_bist_fail0(data)                                   ((0x00000100&(data))>>8)
#define MIPI_BIST_RESULT0_drf_bist_done_shift                                        (7)
#define MIPI_BIST_RESULT0_drf_bist_done_mask                                         (0x00000080)
#define MIPI_BIST_RESULT0_drf_bist_done(data)                                        (0x00000080&((data)<<7))
#define MIPI_BIST_RESULT0_drf_bist_done_src(data)                                    ((0x00000080&(data))>>7)
#define MIPI_BIST_RESULT0_get_drf_bist_done(data)                                    ((0x00000080&(data))>>7)
#define MIPI_BIST_RESULT0_bist_fail5_shift                                           (6)
#define MIPI_BIST_RESULT0_bist_fail5_mask                                            (0x00000040)
#define MIPI_BIST_RESULT0_bist_fail5(data)                                           (0x00000040&((data)<<6))
#define MIPI_BIST_RESULT0_bist_fail5_src(data)                                       ((0x00000040&(data))>>6)
#define MIPI_BIST_RESULT0_get_bist_fail5(data)                                       ((0x00000040&(data))>>6)
#define MIPI_BIST_RESULT0_bist_fail4_shift                                           (5)
#define MIPI_BIST_RESULT0_bist_fail4_mask                                            (0x00000020)
#define MIPI_BIST_RESULT0_bist_fail4(data)                                           (0x00000020&((data)<<5))
#define MIPI_BIST_RESULT0_bist_fail4_src(data)                                       ((0x00000020&(data))>>5)
#define MIPI_BIST_RESULT0_get_bist_fail4(data)                                       ((0x00000020&(data))>>5)
#define MIPI_BIST_RESULT0_bist_fail3_shift                                           (4)
#define MIPI_BIST_RESULT0_bist_fail3_mask                                            (0x00000010)
#define MIPI_BIST_RESULT0_bist_fail3(data)                                           (0x00000010&((data)<<4))
#define MIPI_BIST_RESULT0_bist_fail3_src(data)                                       ((0x00000010&(data))>>4)
#define MIPI_BIST_RESULT0_get_bist_fail3(data)                                       ((0x00000010&(data))>>4)
#define MIPI_BIST_RESULT0_bist_fail2_shift                                           (3)
#define MIPI_BIST_RESULT0_bist_fail2_mask                                            (0x00000008)
#define MIPI_BIST_RESULT0_bist_fail2(data)                                           (0x00000008&((data)<<3))
#define MIPI_BIST_RESULT0_bist_fail2_src(data)                                       ((0x00000008&(data))>>3)
#define MIPI_BIST_RESULT0_get_bist_fail2(data)                                       ((0x00000008&(data))>>3)
#define MIPI_BIST_RESULT0_bist_fail1_shift                                           (2)
#define MIPI_BIST_RESULT0_bist_fail1_mask                                            (0x00000004)
#define MIPI_BIST_RESULT0_bist_fail1(data)                                           (0x00000004&((data)<<2))
#define MIPI_BIST_RESULT0_bist_fail1_src(data)                                       ((0x00000004&(data))>>2)
#define MIPI_BIST_RESULT0_get_bist_fail1(data)                                       ((0x00000004&(data))>>2)
#define MIPI_BIST_RESULT0_bist_fail0_shift                                           (1)
#define MIPI_BIST_RESULT0_bist_fail0_mask                                            (0x00000002)
#define MIPI_BIST_RESULT0_bist_fail0(data)                                           (0x00000002&((data)<<1))
#define MIPI_BIST_RESULT0_bist_fail0_src(data)                                       ((0x00000002&(data))>>1)
#define MIPI_BIST_RESULT0_get_bist_fail0(data)                                       ((0x00000002&(data))>>1)
#define MIPI_BIST_RESULT0_bist_done_shift                                            (0)
#define MIPI_BIST_RESULT0_bist_done_mask                                             (0x00000001)
#define MIPI_BIST_RESULT0_bist_done(data)                                            (0x00000001&((data)<<0))
#define MIPI_BIST_RESULT0_bist_done_src(data)                                        ((0x00000001&(data))>>0)
#define MIPI_BIST_RESULT0_get_bist_done(data)                                        ((0x00000001&(data))>>0)


#define MIPI_BIST_RESULT1                                                            0xDC
#define MIPI_BIST_RESULT1_reg_addr                                                   "0x980041DC"
#define MIPI_BIST_RESULT1_reg                                                        0x980041DC
#define set_MIPI_BIST_RESULT1_reg(data)   (*((volatile unsigned int*) MIPI_BIST_RESULT1_reg)=data)
#define get_MIPI_BIST_RESULT1_reg   (*((volatile unsigned int*) MIPI_BIST_RESULT1_reg))
#define MIPI_BIST_RESULT1_inst_adr                                                   "0x0077"
#define MIPI_BIST_RESULT1_inst                                                       0x0077
#define MIPI_BIST_RESULT1_clk_gate_l4_dis_shift                                      (8)
#define MIPI_BIST_RESULT1_clk_gate_l4_dis_mask                                       (0x00000100)
#define MIPI_BIST_RESULT1_clk_gate_l4_dis(data)                                      (0x00000100&((data)<<8))
#define MIPI_BIST_RESULT1_clk_gate_l4_dis_src(data)                                  ((0x00000100&(data))>>8)
#define MIPI_BIST_RESULT1_get_clk_gate_l4_dis(data)                                  ((0x00000100&(data))>>8)
#define MIPI_BIST_RESULT1_clk_gate_dbus_dis_shift                                    (7)
#define MIPI_BIST_RESULT1_clk_gate_dbus_dis_mask                                     (0x00000080)
#define MIPI_BIST_RESULT1_clk_gate_dbus_dis(data)                                    (0x00000080&((data)<<7))
#define MIPI_BIST_RESULT1_clk_gate_dbus_dis_src(data)                                ((0x00000080&(data))>>7)
#define MIPI_BIST_RESULT1_get_clk_gate_dbus_dis(data)                                ((0x00000080&(data))>>7)
#define MIPI_BIST_RESULT1_sram_ls_gate_en_shift                                      (6)
#define MIPI_BIST_RESULT1_sram_ls_gate_en_mask                                       (0x00000040)
#define MIPI_BIST_RESULT1_sram_ls_gate_en(data)                                      (0x00000040&((data)<<6))
#define MIPI_BIST_RESULT1_sram_ls_gate_en_src(data)                                  ((0x00000040&(data))>>6)
#define MIPI_BIST_RESULT1_get_sram_ls_gate_en(data)                                  ((0x00000040&(data))>>6)
#define MIPI_BIST_RESULT1_sram_ls_shift                                              (5)
#define MIPI_BIST_RESULT1_sram_ls_mask                                               (0x00000020)
#define MIPI_BIST_RESULT1_sram_ls(data)                                              (0x00000020&((data)<<5))
#define MIPI_BIST_RESULT1_sram_ls_src(data)                                          ((0x00000020&(data))>>5)
#define MIPI_BIST_RESULT1_get_sram_ls(data)                                          ((0x00000020&(data))>>5)
#define MIPI_BIST_RESULT1_sram_rm_shift                                              (1)
#define MIPI_BIST_RESULT1_sram_rm_mask                                               (0x0000001E)
#define MIPI_BIST_RESULT1_sram_rm(data)                                              (0x0000001E&((data)<<1))
#define MIPI_BIST_RESULT1_sram_rm_src(data)                                          ((0x0000001E&(data))>>1)
#define MIPI_BIST_RESULT1_get_sram_rm(data)                                          ((0x0000001E&(data))>>1)
#define MIPI_BIST_RESULT1_sram_rme_shift                                             (0)
#define MIPI_BIST_RESULT1_sram_rme_mask                                              (0x00000001)
#define MIPI_BIST_RESULT1_sram_rme(data)                                             (0x00000001&((data)<<0))
#define MIPI_BIST_RESULT1_sram_rme_src(data)                                         ((0x00000001&(data))>>0)
#define MIPI_BIST_RESULT1_get_sram_rme(data)                                         ((0x00000001&(data))>>0)


#define MIPI_SA0_UV                                                                  0xE0
#define MIPI_SA0_UV_reg_addr                                                         "0x980041E0"
#define MIPI_SA0_UV_reg                                                              0x980041E0
#define set_MIPI_SA0_UV_reg(data)   (*((volatile unsigned int*) MIPI_SA0_UV_reg)=data)
#define get_MIPI_SA0_UV_reg   (*((volatile unsigned int*) MIPI_SA0_UV_reg))
#define MIPI_SA0_UV_inst_adr                                                         "0x0078"
#define MIPI_SA0_UV_inst                                                             0x0078
#define MIPI_SA0_UV_sa0_video_uv_shift                                               (0)
#define MIPI_SA0_UV_sa0_video_uv_mask                                                (0xFFFFFFFF)
#define MIPI_SA0_UV_sa0_video_uv(data)                                               (0xFFFFFFFF&((data)<<0))
#define MIPI_SA0_UV_sa0_video_uv_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define MIPI_SA0_UV_get_sa0_video_uv(data)                                           ((0xFFFFFFFF&(data))>>0)


#define MIPI_SA1_UV                                                                  0xE4
#define MIPI_SA1_UV_reg_addr                                                         "0x980041E4"
#define MIPI_SA1_UV_reg                                                              0x980041E4
#define set_MIPI_SA1_UV_reg(data)   (*((volatile unsigned int*) MIPI_SA1_UV_reg)=data)
#define get_MIPI_SA1_UV_reg   (*((volatile unsigned int*) MIPI_SA1_UV_reg))
#define MIPI_SA1_UV_inst_adr                                                         "0x0079"
#define MIPI_SA1_UV_inst                                                             0x0079
#define MIPI_SA1_UV_sa1_video_uv_shift                                               (0)
#define MIPI_SA1_UV_sa1_video_uv_mask                                                (0xFFFFFFFF)
#define MIPI_SA1_UV_sa1_video_uv(data)                                               (0xFFFFFFFF&((data)<<0))
#define MIPI_SA1_UV_sa1_video_uv_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define MIPI_SA1_UV_get_sa1_video_uv(data)                                           ((0xFFFFFFFF&(data))>>0)


#define MIPI_SA2_UV                                                                  0xE8
#define MIPI_SA2_UV_reg_addr                                                         "0x980041E8"
#define MIPI_SA2_UV_reg                                                              0x980041E8
#define set_MIPI_SA2_UV_reg(data)   (*((volatile unsigned int*) MIPI_SA2_UV_reg)=data)
#define get_MIPI_SA2_UV_reg   (*((volatile unsigned int*) MIPI_SA2_UV_reg))
#define MIPI_SA2_UV_inst_adr                                                         "0x007A"
#define MIPI_SA2_UV_inst                                                             0x007A
#define MIPI_SA2_UV_sa2_pic_uv_shift                                                 (0)
#define MIPI_SA2_UV_sa2_pic_uv_mask                                                  (0xFFFFFFFF)
#define MIPI_SA2_UV_sa2_pic_uv(data)                                                 (0xFFFFFFFF&((data)<<0))
#define MIPI_SA2_UV_sa2_pic_uv_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define MIPI_SA2_UV_get_sa2_pic_uv(data)                                             ((0xFFFFFFFF&(data))>>0)


#define MIPI_RESET                                                                   0xEC
#define MIPI_RESET_reg_addr                                                          "0x980041EC"
#define MIPI_RESET_reg                                                               0x980041EC
#define set_MIPI_RESET_reg(data)   (*((volatile unsigned int*) MIPI_RESET_reg)=data)
#define get_MIPI_RESET_reg   (*((volatile unsigned int*) MIPI_RESET_reg))
#define MIPI_RESET_inst_adr                                                          "0x007B"
#define MIPI_RESET_inst                                                              0x007B
#define MIPI_RESET_pic_detect_en_shift                                               (2)
#define MIPI_RESET_pic_detect_en_mask                                                (0x00000004)
#define MIPI_RESET_pic_detect_en(data)                                               (0x00000004&((data)<<2))
#define MIPI_RESET_pic_detect_en_src(data)                                           ((0x00000004&(data))>>2)
#define MIPI_RESET_get_pic_detect_en(data)                                           ((0x00000004&(data))>>2)
#define MIPI_RESET_pic_detect_int_en_shift                                           (1)
#define MIPI_RESET_pic_detect_int_en_mask                                            (0x00000002)
#define MIPI_RESET_pic_detect_int_en(data)                                           (0x00000002&((data)<<1))
#define MIPI_RESET_pic_detect_int_en_src(data)                                       ((0x00000002&(data))>>1)
#define MIPI_RESET_get_pic_detect_int_en(data)                                       ((0x00000002&(data))>>1)
#define MIPI_RESET_mipi_sw_rst_shift                                                 (0)
#define MIPI_RESET_mipi_sw_rst_mask                                                  (0x00000001)
#define MIPI_RESET_mipi_sw_rst(data)                                                 (0x00000001&((data)<<0))
#define MIPI_RESET_mipi_sw_rst_src(data)                                             ((0x00000001&(data))>>0)
#define MIPI_RESET_get_mipi_sw_rst(data)                                             ((0x00000001&(data))>>0)


#define MIPI_DEBUGPORTS                                                              0xF0
#define MIPI_DEBUGPORTS_reg_addr                                                     "0x980041F0"
#define MIPI_DEBUGPORTS_reg                                                          0x980041F0
#define set_MIPI_DEBUGPORTS_reg(data)   (*((volatile unsigned int*) MIPI_DEBUGPORTS_reg)=data)
#define get_MIPI_DEBUGPORTS_reg   (*((volatile unsigned int*) MIPI_DEBUGPORTS_reg))
#define MIPI_DEBUGPORTS_inst_adr                                                     "0x007C"
#define MIPI_DEBUGPORTS_inst                                                         0x007C
#define MIPI_DEBUGPORTS_dbg_sel_shift                                                (8)
#define MIPI_DEBUGPORTS_dbg_sel_mask                                                 (0x00000100)
#define MIPI_DEBUGPORTS_dbg_sel(data)                                                (0x00000100&((data)<<8))
#define MIPI_DEBUGPORTS_dbg_sel_src(data)                                            ((0x00000100&(data))>>8)
#define MIPI_DEBUGPORTS_get_dbg_sel(data)                                            ((0x00000100&(data))>>8)
#define MIPI_DEBUGPORTS_dbg_sel1_shift                                               (4)
#define MIPI_DEBUGPORTS_dbg_sel1_mask                                                (0x000000F0)
#define MIPI_DEBUGPORTS_dbg_sel1(data)                                               (0x000000F0&((data)<<4))
#define MIPI_DEBUGPORTS_dbg_sel1_src(data)                                           ((0x000000F0&(data))>>4)
#define MIPI_DEBUGPORTS_get_dbg_sel1(data)                                           ((0x000000F0&(data))>>4)
#define MIPI_DEBUGPORTS_dbg_sel0_shift                                               (0)
#define MIPI_DEBUGPORTS_dbg_sel0_mask                                                (0x0000000F)
#define MIPI_DEBUGPORTS_dbg_sel0(data)                                               (0x0000000F&((data)<<0))
#define MIPI_DEBUGPORTS_dbg_sel0_src(data)                                           ((0x0000000F&(data))>>0)
#define MIPI_DEBUGPORTS_get_dbg_sel0(data)                                           ((0x0000000F&(data))>>0)


#define MIPI_DUMMY_REG0                                                              0xF4
#define MIPI_DUMMY_REG0_reg_addr                                                     "0x980041F4"
#define MIPI_DUMMY_REG0_reg                                                          0x980041F4
#define set_MIPI_DUMMY_REG0_reg(data)   (*((volatile unsigned int*) MIPI_DUMMY_REG0_reg)=data)
#define get_MIPI_DUMMY_REG0_reg   (*((volatile unsigned int*) MIPI_DUMMY_REG0_reg))
#define MIPI_DUMMY_REG0_inst_adr                                                     "0x007D"
#define MIPI_DUMMY_REG0_inst                                                         0x007D
#define MIPI_DUMMY_REG0_mipi_dummy_reg0_shift                                        (0)
#define MIPI_DUMMY_REG0_mipi_dummy_reg0_mask                                         (0xFFFFFFFF)
#define MIPI_DUMMY_REG0_mipi_dummy_reg0(data)                                        (0xFFFFFFFF&((data)<<0))
#define MIPI_DUMMY_REG0_mipi_dummy_reg0_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define MIPI_DUMMY_REG0_get_mipi_dummy_reg0(data)                                    ((0xFFFFFFFF&(data))>>0)


#define MIPI_DUMMY_REG1                                                              0xF8
#define MIPI_DUMMY_REG1_reg_addr                                                     "0x980041F8"
#define MIPI_DUMMY_REG1_reg                                                          0x980041F8
#define set_MIPI_DUMMY_REG1_reg(data)   (*((volatile unsigned int*) MIPI_DUMMY_REG1_reg)=data)
#define get_MIPI_DUMMY_REG1_reg   (*((volatile unsigned int*) MIPI_DUMMY_REG1_reg))
#define MIPI_DUMMY_REG1_inst_adr                                                     "0x007E"
#define MIPI_DUMMY_REG1_inst                                                         0x007E
#define MIPI_DUMMY_REG1_mipi_dummy_reg1_shift                                        (0)
#define MIPI_DUMMY_REG1_mipi_dummy_reg1_mask                                         (0xFFFFFFFF)
#define MIPI_DUMMY_REG1_mipi_dummy_reg1(data)                                        (0xFFFFFFFF&((data)<<0))
#define MIPI_DUMMY_REG1_mipi_dummy_reg1_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define MIPI_DUMMY_REG1_get_mipi_dummy_reg1(data)                                    ((0xFFFFFFFF&(data))>>0)


#define MIPI_SIZE3                                                                   0xFC
#define MIPI_SIZE3_reg_addr                                                          "0x980041FC"
#define MIPI_SIZE3_reg                                                               0x980041FC
#define set_MIPI_SIZE3_reg(data)   (*((volatile unsigned int*) MIPI_SIZE3_reg)=data)
#define get_MIPI_SIZE3_reg   (*((volatile unsigned int*) MIPI_SIZE3_reg))
#define MIPI_SIZE3_inst_adr                                                          "0x007F"
#define MIPI_SIZE3_inst                                                              0x007F
#define MIPI_SIZE3_src_height_shift                                                  (0)
#define MIPI_SIZE3_src_height_mask                                                   (0x00001FFF)
#define MIPI_SIZE3_src_height(data)                                                  (0x00001FFF&((data)<<0))
#define MIPI_SIZE3_src_height_src(data)                                              ((0x00001FFF&(data))>>0)
#define MIPI_SIZE3_get_src_height(data)                                              ((0x00001FFF&(data))>>0)


#define MIPI_RESOLUTION_DETECT                                                       0x98004200
#define MIPI_RESOLUTION_DETECT_reg_addr                                              "0xD8004200"
#define MIPI_RESOLUTION_DETECT_reg                                                   0xD8004200
#define set_MIPI_RESOLUTION_DETECT_reg(data)   (*((volatile unsigned int*) MIPI_RESOLUTION_DETECT_reg)=data)
#define get_MIPI_RESOLUTION_DETECT_reg   (*((volatile unsigned int*) MIPI_RESOLUTION_DETECT_reg))
#define MIPI_RESOLUTION_DETECT_inst_adr                                              "0x0080"
#define MIPI_RESOLUTION_DETECT_inst                                                  0x0080
#define MIPI_RESOLUTION_DETECT_pic_detect_vcnt_shift                                 (13)
#define MIPI_RESOLUTION_DETECT_pic_detect_vcnt_mask                                  (0x03FFE000)
#define MIPI_RESOLUTION_DETECT_pic_detect_vcnt(data)                                 (0x03FFE000&((data)<<13))
#define MIPI_RESOLUTION_DETECT_pic_detect_vcnt_src(data)                             ((0x03FFE000&(data))>>13)
#define MIPI_RESOLUTION_DETECT_get_pic_detect_vcnt(data)                             ((0x03FFE000&(data))>>13)
#define MIPI_RESOLUTION_DETECT_pic_detect_hcnt_shift                                 (0)
#define MIPI_RESOLUTION_DETECT_pic_detect_hcnt_mask                                  (0x00001FFF)
#define MIPI_RESOLUTION_DETECT_pic_detect_hcnt(data)                                 (0x00001FFF&((data)<<0))
#define MIPI_RESOLUTION_DETECT_pic_detect_hcnt_src(data)                             ((0x00001FFF&(data))>>0)
#define MIPI_RESOLUTION_DETECT_get_pic_detect_hcnt(data)                             ((0x00001FFF&(data))>>0)


#define MIPI_URGENT                                                                  0x98004204
#define MIPI_URGENT_reg_addr                                                         "0xD8004204"
#define MIPI_URGENT_reg                                                              0xD8004204
#define set_MIPI_URGENT_reg(data)   (*((volatile unsigned int*) MIPI_URGENT_reg)=data)
#define get_MIPI_URGENT_reg   (*((volatile unsigned int*) MIPI_URGENT_reg))
#define MIPI_URGENT_inst_adr                                                         "0x0081"
#define MIPI_URGENT_inst                                                             0x0081
#define MIPI_URGENT_buf_up_bound_shift                                               (0)
#define MIPI_URGENT_buf_up_bound_mask                                                (0x0000003F)
#define MIPI_URGENT_buf_up_bound(data)                                               (0x0000003F&((data)<<0))
#define MIPI_URGENT_buf_up_bound_src(data)                                           ((0x0000003F&(data))>>0)
#define MIPI_URGENT_get_buf_up_bound(data)                                           ((0x0000003F&(data))>>0)


#define MIPI_BUF_USAGE                                                               0x98004208
#define MIPI_BUF_USAGE_reg_addr                                                      "0xD8004208"
#define MIPI_BUF_USAGE_reg                                                           0xD8004208
#define set_MIPI_BUF_USAGE_reg(data)   (*((volatile unsigned int*) MIPI_BUF_USAGE_reg)=data)
#define get_MIPI_BUF_USAGE_reg   (*((volatile unsigned int*) MIPI_BUF_USAGE_reg))
#define MIPI_BUF_USAGE_inst_adr                                                      "0x0082"
#define MIPI_BUF_USAGE_inst                                                          0x0082
#define MIPI_BUF_USAGE_mipi_buf_usage_shift                                          (0)
#define MIPI_BUF_USAGE_mipi_buf_usage_mask                                           (0x0000003F)
#define MIPI_BUF_USAGE_mipi_buf_usage(data)                                          (0x0000003F&((data)<<0))
#define MIPI_BUF_USAGE_mipi_buf_usage_src(data)                                      ((0x0000003F&(data))>>0)
#define MIPI_BUF_USAGE_get_mipi_buf_usage(data)                                      ((0x0000003F&(data))>>0)


#define ISOLATION_ENABLE                                                             0x9800420C
#define ISOLATION_ENABLE_reg_addr                                                    "0xD800420C"
#define ISOLATION_ENABLE_reg                                                         0xD800420C
#define set_ISOLATION_ENABLE_reg(data)   (*((volatile unsigned int*) ISOLATION_ENABLE_reg)=data)
#define get_ISOLATION_ENABLE_reg   (*((volatile unsigned int*) ISOLATION_ENABLE_reg))
#define ISOLATION_ENABLE_inst_adr                                                    "0x0083"
#define ISOLATION_ENABLE_inst                                                        0x0083
#define ISOLATION_ENABLE_mipi_isolation_enable_shift                                 (0)
#define ISOLATION_ENABLE_mipi_isolation_enable_mask                                  (0x00000001)
#define ISOLATION_ENABLE_mipi_isolation_enable(data)                                 (0x00000001&((data)<<0))
#define ISOLATION_ENABLE_mipi_isolation_enable_src(data)                             ((0x00000001&(data))>>0)
#define ISOLATION_ENABLE_get_mipi_isolation_enable(data)                             ((0x00000001&(data))>>0)


#define BIST_SETTING                                                                 0x98004210
#define BIST_SETTING_reg_addr                                                        "0xD8004210"
#define BIST_SETTING_reg                                                             0xD8004210
#define set_BIST_SETTING_reg(data)   (*((volatile unsigned int*) BIST_SETTING_reg)=data)
#define get_BIST_SETTING_reg   (*((volatile unsigned int*) BIST_SETTING_reg))
#define BIST_SETTING_inst_adr                                                        "0x0084"
#define BIST_SETTING_inst                                                            0x0084
#define BIST_SETTING_bist_set_on_shift                                               (0)
#define BIST_SETTING_bist_set_on_mask                                                (0x00000001)
#define BIST_SETTING_bist_set_on(data)                                               (0x00000001&((data)<<0))
#define BIST_SETTING_bist_set_on_src(data)                                           ((0x00000001&(data))>>0)
#define BIST_SETTING_get_bist_set_on(data)                                           ((0x00000001&(data))>>0)


#define GROUP                                                                        0x98004214
#define GROUP_reg_addr                                                               "0xD8004214"
#define GROUP_reg                                                                    0xD8004214
#define set_GROUP_reg(data)   (*((volatile unsigned int*) GROUP_reg)=data)
#define get_GROUP_reg   (*((volatile unsigned int*) GROUP_reg))
#define GROUP_inst_adr                                                               "0x0085"
#define GROUP_inst                                                                   0x0085
#define GROUP_grp_lmt_shift                                                          (4)
#define GROUP_grp_lmt_mask                                                           (0x000001F0)
#define GROUP_grp_lmt(data)                                                          (0x000001F0&((data)<<4))
#define GROUP_grp_lmt_src(data)                                                      ((0x000001F0&(data))>>4)
#define GROUP_get_grp_lmt(data)                                                      ((0x000001F0&(data))>>4)
#define GROUP_grp_size_shift                                                         (1)
#define GROUP_grp_size_mask                                                          (0x0000000E)
#define GROUP_grp_size(data)                                                         (0x0000000E&((data)<<1))
#define GROUP_grp_size_src(data)                                                     ((0x0000000E&(data))>>1)
#define GROUP_get_grp_size(data)                                                     ((0x0000000E&(data))>>1)
#define GROUP_grp_wen_shift                                                          (0)
#define GROUP_grp_wen_mask                                                           (0x00000001)
#define GROUP_grp_wen(data)                                                          (0x00000001&((data)<<0))
#define GROUP_grp_wen_src(data)                                                      ((0x00000001&(data))>>0)
#define GROUP_get_grp_wen(data)                                                      ((0x00000001&(data))>>0)


#define DC_PROTECT                                                                   0x98004220
#define DC_PROTECT_reg_addr                                                          "0xD8004220"
#define DC_PROTECT_reg                                                               0xD8004220
#define set_DC_PROTECT_reg(data)   (*((volatile unsigned int*) DC_PROTECT_reg)=data)
#define get_DC_PROTECT_reg   (*((volatile unsigned int*) DC_PROTECT_reg))
#define DC_PROTECT_inst_adr                                                          "0x0088"
#define DC_PROTECT_inst                                                              0x0088
#define DC_PROTECT_dc_protect_shift                                                  (0)
#define DC_PROTECT_dc_protect_mask                                                   (0x00000001)
#define DC_PROTECT_dc_protect(data)                                                  (0x00000001&((data)<<0))
#define DC_PROTECT_dc_protect_src(data)                                              ((0x00000001&(data))>>0)
#define DC_PROTECT_get_dc_protect(data)                                              ((0x00000001&(data))>>0)


#endif
