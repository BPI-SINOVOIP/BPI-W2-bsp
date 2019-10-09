/**************************************************************
// Spec Version                  : unknown
// Parser Version                : DVR_Parser_6.5
// CModelGen Version             : 5.0 2009.04.09
// Naming Rule                   :  Register_Name
// Naming Rule                   : Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/8/14 9:16:18
***************************************************************/


#ifndef _MIPI_WRAPPER_REG_H_INCLUDED_
#define _MIPI_WRAPPER_REG_H_INCLUDED_
#ifdef  _MIPI_WRAPPER_USE_STRUCT
typedef struct 
{
unsigned int     dst_fmt:5;
unsigned int     src_fmt:2;
unsigned int     src_sel:1;
unsigned int     seq_en:1;
unsigned int     vs:1;
unsigned int     vs_near:1;
unsigned int     vs_yodd:1;
unsigned int     vs_codd:1;
unsigned int     hs:1;
unsigned int     hs_yodd:1;
unsigned int     hs_codd:1;
unsigned int     reserved_0:3;
unsigned int     yuv_to_rgb:1;
unsigned int     chroma_ds_mode:1;
unsigned int     chroma_ds_en:1;
unsigned int     chroma_us_mode:1;
unsigned int     chroma_us_en:1;
unsigned int     hdmirx_interlace_en:1;
unsigned int     hdmirx_interlace_polarity:1;
unsigned int     int_en4:1;
unsigned int     int_en3:1;
unsigned int     int_en2:1;
unsigned int     int_en1:1;
unsigned int     int_en0:1;
unsigned int     en:1;
}MIPI;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     sa0_video:31;
}MIPI_SA0;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     sa1_video:31;
}MIPI_SA1;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     sa2_pic:31;
}MIPI_SA2;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     dst_width_video:13;
unsigned int     pitch_video:16;
}MIPI_SIZE0;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     dst_width_pic:13;
unsigned int     pitch_pic:16;
}MIPI_SIZE1;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     src_width_pic:13;
unsigned int     reserved_1:3;
unsigned int     src_width_video:13;
}MIPI_SIZE2;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     index_y0_video:7;
unsigned int     reserved_1:9;
unsigned int     index_c0_video:7;
}MIPI_INDEX0;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     index_y1_video:7;
unsigned int     reserved_1:9;
unsigned int     index_c1_video:7;
}MIPI_INDEX1;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     index_y2_pic:7;
unsigned int     reserved_1:9;
unsigned int     index_c2_pic:7;
}MIPI_INDEX2;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     mipi_data_valid:1;
unsigned int     mipi_line_end:1;
unsigned int     mipi_line_start:1;
unsigned int     mipi_frame_end:1;
unsigned int     mipi_frame_start:1;
unsigned int     esc_lane3_int_flg:1;
unsigned int     esc_lane2_int_flg:1;
unsigned int     esc_lane1_int_flg:1;
unsigned int     esc_lane0_int_flg:1;
unsigned int     clk_ulps_int_flg:1;
unsigned int     crc16_err_int_flg:1;
unsigned int     ecc_crt_int_flg:1;
unsigned int     ecc_err_int_flg:1;
unsigned int     reserved_1:2;
unsigned int     overflow_drop:1;
unsigned int     fm_drop:1;
unsigned int     fm_done2:1;
unsigned int     fm_done1:1;
unsigned int     fm_done0:1;
unsigned int     write_data:1;
}MIPI_INT_ST;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     mipi_type:1;
}MIPI_TYPE;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     cs_trans0_c1:17;
}CS_TRANS0;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     cs_trans1_c2:17;
}CS_TRANS1;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     cs_trans2_c3:17;
}CS_TRANS2;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     cs_trans3_c4:17;
}CS_TRANS3;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     cs_trans4_c5:17;
}CS_TRANS4;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     cs_trans5_c6:17;
}CS_TRANS5;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     cs_trans6_c7:17;
}CS_TRANS6;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     cs_trans7_c8:17;
}CS_TRANS7;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     cs_trans8_c9:17;
}CS_TRANS8;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     cs_trans9_k1:16;
}CS_TRANS9;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     cs_trans10_k2:16;
}CS_TRANS10;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     cs_trans11_k3:16;
}CS_TRANS11;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     hsi_offset:11;
unsigned int     hsi_phase:14;
unsigned int     reserved_1:2;
}SCALER_HSI;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     hsd_out:11;
unsigned int     reserved_1:1;
unsigned int     hsd_delta:19;
}SCALER_HSD;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     vsi_offset:12;
unsigned int     vsi_phase:14;
unsigned int     reserved_1:2;
}SCALER_VSI;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     vsd_out:11;
unsigned int     reserved_1:1;
unsigned int     vsd_delta:19;
}SCALER_VSD;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hsync0_c1:14;
unsigned int     reserved_1:2;
unsigned int     hsync0_c0:14;
}SCALER_HSYNC0;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hsync1_c1:14;
unsigned int     reserved_1:2;
unsigned int     hsync1_c0:14;
}SCALER_HSYNC1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hsync2_c1:14;
unsigned int     reserved_1:2;
unsigned int     hsync2_c0:14;
}SCALER_HSYNC2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hsync3_c1:14;
unsigned int     reserved_1:2;
unsigned int     hsync3_c0:14;
}SCALER_HSYNC3;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hsync4_c1:14;
unsigned int     reserved_1:2;
unsigned int     hsync4_c0:14;
}SCALER_HSYNC4;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hsync5_c1:14;
unsigned int     reserved_1:2;
unsigned int     hsync5_c0:14;
}SCALER_HSYNC5;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hsync6_c1:14;
unsigned int     reserved_1:2;
unsigned int     hsync6_c0:14;
}SCALER_HSYNC6;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hsync7_c1:14;
unsigned int     reserved_1:2;
unsigned int     hsync7_c0:14;
}SCALER_HSYNC7;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hscc0_c1:14;
unsigned int     reserved_1:2;
unsigned int     hscc0_c0:14;
}SCALER_HSCC0;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hscc1_c1:14;
unsigned int     reserved_1:2;
unsigned int     hscc1_c0:14;
}SCALER_HSCC1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hscc2_c1:14;
unsigned int     reserved_1:2;
unsigned int     hscc2_c0:14;
}SCALER_HSCC2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hscc3_c1:14;
unsigned int     reserved_1:2;
unsigned int     hscc3_c0:14;
}SCALER_HSCC3;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hscc4_c1:14;
unsigned int     reserved_1:2;
unsigned int     hscc4_c0:14;
}SCALER_HSCC4;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hscc5_c1:14;
unsigned int     reserved_1:2;
unsigned int     hscc5_c0:14;
}SCALER_HSCC5;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hscc6_c1:14;
unsigned int     reserved_1:2;
unsigned int     hscc6_c0:14;
}SCALER_HSCC6;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hscc7_c1:14;
unsigned int     reserved_1:2;
unsigned int     hscc7_c0:14;
}SCALER_HSCC7;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     vsyc0_c1:14;
unsigned int     reserved_1:2;
unsigned int     vsyc0_c0:14;
}SCALER_VSYC0;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     vsyc1_c1:14;
unsigned int     reserved_1:2;
unsigned int     vsyc1_c0:14;
}SCALER_VSYC1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     vsyc2_c1:14;
unsigned int     reserved_1:2;
unsigned int     vsyc2_c0:14;
}SCALER_VSYC2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     vsyc3_c1:14;
unsigned int     reserved_1:2;
unsigned int     vsyc3_c0:14;
}SCALER_VSYC3;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     vscc0_c1:14;
unsigned int     reserved_1:2;
unsigned int     vscc0_c0:14;
}SCALER_VSCC0;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     vscc1_c1:14;
unsigned int     reserved_1:2;
unsigned int     vscc1_c0:14;
}SCALER_VSCC1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     vscc2_c1:14;
unsigned int     reserved_1:2;
unsigned int     vscc2_c0:14;
}SCALER_VSCC2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     vscc3_c1:14;
unsigned int     reserved_1:2;
unsigned int     vscc3_c0:14;
}SCALER_VSCC3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     alpha:8;
}CONSTANT_ALPHA;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     drf_test_resume:1;
unsigned int     drf_bist_mode:1;
unsigned int     bist_mode:1;
}BIST_MODE;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     drf_start_pause:1;
unsigned int     drf_bist_fail2:1;
unsigned int     drf_bist_fail1:1;
unsigned int     drf_bist_fail0:1;
unsigned int     drf_bist_done:1;
unsigned int     bist_fail2:1;
unsigned int     bist_fail1:1;
unsigned int     bist_fail0:1;
unsigned int     bist_done:1;
}BIST_RESULT0;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     sram_rm:4;
unsigned int     sram_rme:1;
}BIST_RESULT1;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     sa0_video_uv:31;
}MIPI_SA0_UV;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     sa1_video_uv:31;
}MIPI_SA1_UV;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     sa2_pic_uv:31;
}MIPI_SA2_UV;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     mipi_sw_rst:1;
}MIPI_RESET;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     dbg_sel:1;
unsigned int     dbg_sel1:4;
unsigned int     dbg_sel0:4;
}BIST_RESULT1;

typedef struct 
{
unsigned int     mipi_dummy_reg0:32;
}MIPI_DUMMY_REG0;

typedef struct 
{
unsigned int     mipi_dummy_reg1:32;
}MIPI_DUMMY_REG1;

#endif

#define MIPI                                                                         0x18004100
#define MIPI_reg_addr                                                                "0xB8004100"
#define MIPI_reg                                                                     0xB8004100
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
#define MIPI_seq_en_shift                                                            (23)
#define MIPI_seq_en_mask                                                             (0x00800000)
#define MIPI_seq_en(data)                                                            (0x00800000&((data)<<23))
#define MIPI_seq_en_src(data)                                                        ((0x00800000&(data))>>23)
#define MIPI_get_seq_en(data)                                                        ((0x00800000&(data))>>23)
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


#define MIPI_SA0                                                                     0x18004104
#define MIPI_SA0_reg_addr                                                            "0xB8004104"
#define MIPI_SA0_reg                                                                 0xB8004104
#define set_MIPI_SA0_reg(data)   (*((volatile unsigned int*) MIPI_SA0_reg)=data)
#define get_MIPI_SA0_reg   (*((volatile unsigned int*) MIPI_SA0_reg))
#define MIPI_SA0_inst_adr                                                            "0x0041"
#define MIPI_SA0_inst                                                                0x0041
#define MIPI_SA0_sa0_video_shift                                                     (0)
#define MIPI_SA0_sa0_video_mask                                                      (0x7FFFFFFF)
#define MIPI_SA0_sa0_video(data)                                                     (0x7FFFFFFF&((data)<<0))
#define MIPI_SA0_sa0_video_src(data)                                                 ((0x7FFFFFFF&(data))>>0)
#define MIPI_SA0_get_sa0_video(data)                                                 ((0x7FFFFFFF&(data))>>0)


#define MIPI_SA1                                                                     0x18004108
#define MIPI_SA1_reg_addr                                                            "0xB8004108"
#define MIPI_SA1_reg                                                                 0xB8004108
#define set_MIPI_SA1_reg(data)   (*((volatile unsigned int*) MIPI_SA1_reg)=data)
#define get_MIPI_SA1_reg   (*((volatile unsigned int*) MIPI_SA1_reg))
#define MIPI_SA1_inst_adr                                                            "0x0042"
#define MIPI_SA1_inst                                                                0x0042
#define MIPI_SA1_sa1_video_shift                                                     (0)
#define MIPI_SA1_sa1_video_mask                                                      (0x7FFFFFFF)
#define MIPI_SA1_sa1_video(data)                                                     (0x7FFFFFFF&((data)<<0))
#define MIPI_SA1_sa1_video_src(data)                                                 ((0x7FFFFFFF&(data))>>0)
#define MIPI_SA1_get_sa1_video(data)                                                 ((0x7FFFFFFF&(data))>>0)


#define MIPI_SA2                                                                     0x1800410C
#define MIPI_SA2_reg_addr                                                            "0xB800410C"
#define MIPI_SA2_reg                                                                 0xB800410C
#define set_MIPI_SA2_reg(data)   (*((volatile unsigned int*) MIPI_SA2_reg)=data)
#define get_MIPI_SA2_reg   (*((volatile unsigned int*) MIPI_SA2_reg))
#define MIPI_SA2_inst_adr                                                            "0x0043"
#define MIPI_SA2_inst                                                                0x0043
#define MIPI_SA2_sa2_pic_shift                                                       (0)
#define MIPI_SA2_sa2_pic_mask                                                        (0x7FFFFFFF)
#define MIPI_SA2_sa2_pic(data)                                                       (0x7FFFFFFF&((data)<<0))
#define MIPI_SA2_sa2_pic_src(data)                                                   ((0x7FFFFFFF&(data))>>0)
#define MIPI_SA2_get_sa2_pic(data)                                                   ((0x7FFFFFFF&(data))>>0)


#define MIPI_SIZE0                                                                   0x18004110
#define MIPI_SIZE0_reg_addr                                                          "0xB8004110"
#define MIPI_SIZE0_reg                                                               0xB8004110
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


#define MIPI_SIZE1                                                                   0x18004114
#define MIPI_SIZE1_reg_addr                                                          "0xB8004114"
#define MIPI_SIZE1_reg                                                               0xB8004114
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


#define MIPI_SIZE2                                                                   0x18004118
#define MIPI_SIZE2_reg_addr                                                          "0xB8004118"
#define MIPI_SIZE2_reg                                                               0xB8004118
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


#define MIPI_INDEX0                                                                  0x1800411C
#define MIPI_INDEX0_reg_addr                                                         "0xB800411C"
#define MIPI_INDEX0_reg                                                              0xB800411C
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


#define MIPI_INDEX1                                                                  0x18004120
#define MIPI_INDEX1_reg_addr                                                         "0xB8004120"
#define MIPI_INDEX1_reg                                                              0xB8004120
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


#define MIPI_INDEX2                                                                  0x18004124
#define MIPI_INDEX2_reg_addr                                                         "0xB8004124"
#define MIPI_INDEX2_reg                                                              0xB8004124
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


#define MIPI_INT_ST                                                                  0x18004128
#define MIPI_INT_ST_reg_addr                                                         "0xB8004128"
#define MIPI_INT_ST_reg                                                              0xB8004128
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


#define MIPI_TYPE                                                                    0x1800412C
#define MIPI_TYPE_reg_addr                                                           "0xB800412C"
#define MIPI_TYPE_reg                                                                0xB800412C
#define set_MIPI_TYPE_reg(data)   (*((volatile unsigned int*) MIPI_TYPE_reg)=data)
#define get_MIPI_TYPE_reg   (*((volatile unsigned int*) MIPI_TYPE_reg))
#define MIPI_TYPE_inst_adr                                                           "0x004B"
#define MIPI_TYPE_inst                                                               0x004B
#define MIPI_TYPE_mipi_type_shift                                                    (0)
#define MIPI_TYPE_mipi_type_mask                                                     (0x00000001)
#define MIPI_TYPE_mipi_type(data)                                                    (0x00000001&((data)<<0))
#define MIPI_TYPE_mipi_type_src(data)                                                ((0x00000001&(data))>>0)
#define MIPI_TYPE_get_mipi_type(data)                                                ((0x00000001&(data))>>0)


#define CS_TRANS0                                                                    0x18004130
#define CS_TRANS0_reg_addr                                                           "0xB8004130"
#define CS_TRANS0_reg                                                                0xB8004130
#define set_CS_TRANS0_reg(data)   (*((volatile unsigned int*) CS_TRANS0_reg)=data)
#define get_CS_TRANS0_reg   (*((volatile unsigned int*) CS_TRANS0_reg))
#define CS_TRANS0_inst_adr                                                           "0x004C"
#define CS_TRANS0_inst                                                               0x004C
#define CS_TRANS0_cs_trans0_c1_shift                                                 (0)
#define CS_TRANS0_cs_trans0_c1_mask                                                  (0x0001FFFF)
#define CS_TRANS0_cs_trans0_c1(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS0_cs_trans0_c1_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS0_get_cs_trans0_c1(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS1                                                                    0x18004134
#define CS_TRANS1_reg_addr                                                           "0xB8004134"
#define CS_TRANS1_reg                                                                0xB8004134
#define set_CS_TRANS1_reg(data)   (*((volatile unsigned int*) CS_TRANS1_reg)=data)
#define get_CS_TRANS1_reg   (*((volatile unsigned int*) CS_TRANS1_reg))
#define CS_TRANS1_inst_adr                                                           "0x004D"
#define CS_TRANS1_inst                                                               0x004D
#define CS_TRANS1_cs_trans1_c2_shift                                                 (0)
#define CS_TRANS1_cs_trans1_c2_mask                                                  (0x0001FFFF)
#define CS_TRANS1_cs_trans1_c2(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS1_cs_trans1_c2_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS1_get_cs_trans1_c2(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS2                                                                    0x18004138
#define CS_TRANS2_reg_addr                                                           "0xB8004138"
#define CS_TRANS2_reg                                                                0xB8004138
#define set_CS_TRANS2_reg(data)   (*((volatile unsigned int*) CS_TRANS2_reg)=data)
#define get_CS_TRANS2_reg   (*((volatile unsigned int*) CS_TRANS2_reg))
#define CS_TRANS2_inst_adr                                                           "0x004E"
#define CS_TRANS2_inst                                                               0x004E
#define CS_TRANS2_cs_trans2_c3_shift                                                 (0)
#define CS_TRANS2_cs_trans2_c3_mask                                                  (0x0001FFFF)
#define CS_TRANS2_cs_trans2_c3(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS2_cs_trans2_c3_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS2_get_cs_trans2_c3(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS3                                                                    0x1800413C
#define CS_TRANS3_reg_addr                                                           "0xB800413C"
#define CS_TRANS3_reg                                                                0xB800413C
#define set_CS_TRANS3_reg(data)   (*((volatile unsigned int*) CS_TRANS3_reg)=data)
#define get_CS_TRANS3_reg   (*((volatile unsigned int*) CS_TRANS3_reg))
#define CS_TRANS3_inst_adr                                                           "0x004F"
#define CS_TRANS3_inst                                                               0x004F
#define CS_TRANS3_cs_trans3_c4_shift                                                 (0)
#define CS_TRANS3_cs_trans3_c4_mask                                                  (0x0001FFFF)
#define CS_TRANS3_cs_trans3_c4(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS3_cs_trans3_c4_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS3_get_cs_trans3_c4(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS4                                                                    0x18004140
#define CS_TRANS4_reg_addr                                                           "0xB8004140"
#define CS_TRANS4_reg                                                                0xB8004140
#define set_CS_TRANS4_reg(data)   (*((volatile unsigned int*) CS_TRANS4_reg)=data)
#define get_CS_TRANS4_reg   (*((volatile unsigned int*) CS_TRANS4_reg))
#define CS_TRANS4_inst_adr                                                           "0x0050"
#define CS_TRANS4_inst                                                               0x0050
#define CS_TRANS4_cs_trans4_c5_shift                                                 (0)
#define CS_TRANS4_cs_trans4_c5_mask                                                  (0x0001FFFF)
#define CS_TRANS4_cs_trans4_c5(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS4_cs_trans4_c5_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS4_get_cs_trans4_c5(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS5                                                                    0x18004144
#define CS_TRANS5_reg_addr                                                           "0xB8004144"
#define CS_TRANS5_reg                                                                0xB8004144
#define set_CS_TRANS5_reg(data)   (*((volatile unsigned int*) CS_TRANS5_reg)=data)
#define get_CS_TRANS5_reg   (*((volatile unsigned int*) CS_TRANS5_reg))
#define CS_TRANS5_inst_adr                                                           "0x0051"
#define CS_TRANS5_inst                                                               0x0051
#define CS_TRANS5_cs_trans5_c6_shift                                                 (0)
#define CS_TRANS5_cs_trans5_c6_mask                                                  (0x0001FFFF)
#define CS_TRANS5_cs_trans5_c6(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS5_cs_trans5_c6_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS5_get_cs_trans5_c6(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS6                                                                    0x18004148
#define CS_TRANS6_reg_addr                                                           "0xB8004148"
#define CS_TRANS6_reg                                                                0xB8004148
#define set_CS_TRANS6_reg(data)   (*((volatile unsigned int*) CS_TRANS6_reg)=data)
#define get_CS_TRANS6_reg   (*((volatile unsigned int*) CS_TRANS6_reg))
#define CS_TRANS6_inst_adr                                                           "0x0052"
#define CS_TRANS6_inst                                                               0x0052
#define CS_TRANS6_cs_trans6_c7_shift                                                 (0)
#define CS_TRANS6_cs_trans6_c7_mask                                                  (0x0001FFFF)
#define CS_TRANS6_cs_trans6_c7(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS6_cs_trans6_c7_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS6_get_cs_trans6_c7(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS7                                                                    0x1800414C
#define CS_TRANS7_reg_addr                                                           "0xB800414C"
#define CS_TRANS7_reg                                                                0xB800414C
#define set_CS_TRANS7_reg(data)   (*((volatile unsigned int*) CS_TRANS7_reg)=data)
#define get_CS_TRANS7_reg   (*((volatile unsigned int*) CS_TRANS7_reg))
#define CS_TRANS7_inst_adr                                                           "0x0053"
#define CS_TRANS7_inst                                                               0x0053
#define CS_TRANS7_cs_trans7_c8_shift                                                 (0)
#define CS_TRANS7_cs_trans7_c8_mask                                                  (0x0001FFFF)
#define CS_TRANS7_cs_trans7_c8(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS7_cs_trans7_c8_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS7_get_cs_trans7_c8(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS8                                                                    0x18004150
#define CS_TRANS8_reg_addr                                                           "0xB8004150"
#define CS_TRANS8_reg                                                                0xB8004150
#define set_CS_TRANS8_reg(data)   (*((volatile unsigned int*) CS_TRANS8_reg)=data)
#define get_CS_TRANS8_reg   (*((volatile unsigned int*) CS_TRANS8_reg))
#define CS_TRANS8_inst_adr                                                           "0x0054"
#define CS_TRANS8_inst                                                               0x0054
#define CS_TRANS8_cs_trans8_c9_shift                                                 (0)
#define CS_TRANS8_cs_trans8_c9_mask                                                  (0x0001FFFF)
#define CS_TRANS8_cs_trans8_c9(data)                                                 (0x0001FFFF&((data)<<0))
#define CS_TRANS8_cs_trans8_c9_src(data)                                             ((0x0001FFFF&(data))>>0)
#define CS_TRANS8_get_cs_trans8_c9(data)                                             ((0x0001FFFF&(data))>>0)


#define CS_TRANS9                                                                    0x18004154
#define CS_TRANS9_reg_addr                                                           "0xB8004154"
#define CS_TRANS9_reg                                                                0xB8004154
#define set_CS_TRANS9_reg(data)   (*((volatile unsigned int*) CS_TRANS9_reg)=data)
#define get_CS_TRANS9_reg   (*((volatile unsigned int*) CS_TRANS9_reg))
#define CS_TRANS9_inst_adr                                                           "0x0055"
#define CS_TRANS9_inst                                                               0x0055
#define CS_TRANS9_cs_trans9_k1_shift                                                 (0)
#define CS_TRANS9_cs_trans9_k1_mask                                                  (0x0000FFFF)
#define CS_TRANS9_cs_trans9_k1(data)                                                 (0x0000FFFF&((data)<<0))
#define CS_TRANS9_cs_trans9_k1_src(data)                                             ((0x0000FFFF&(data))>>0)
#define CS_TRANS9_get_cs_trans9_k1(data)                                             ((0x0000FFFF&(data))>>0)


#define CS_TRANS10                                                                   0x18004158
#define CS_TRANS10_reg_addr                                                          "0xB8004158"
#define CS_TRANS10_reg                                                               0xB8004158
#define set_CS_TRANS10_reg(data)   (*((volatile unsigned int*) CS_TRANS10_reg)=data)
#define get_CS_TRANS10_reg   (*((volatile unsigned int*) CS_TRANS10_reg))
#define CS_TRANS10_inst_adr                                                          "0x0056"
#define CS_TRANS10_inst                                                              0x0056
#define CS_TRANS10_cs_trans10_k2_shift                                               (0)
#define CS_TRANS10_cs_trans10_k2_mask                                                (0x0000FFFF)
#define CS_TRANS10_cs_trans10_k2(data)                                               (0x0000FFFF&((data)<<0))
#define CS_TRANS10_cs_trans10_k2_src(data)                                           ((0x0000FFFF&(data))>>0)
#define CS_TRANS10_get_cs_trans10_k2(data)                                           ((0x0000FFFF&(data))>>0)


#define CS_TRANS11                                                                   0x1800415C
#define CS_TRANS11_reg_addr                                                          "0xB800415C"
#define CS_TRANS11_reg                                                               0xB800415C
#define set_CS_TRANS11_reg(data)   (*((volatile unsigned int*) CS_TRANS11_reg)=data)
#define get_CS_TRANS11_reg   (*((volatile unsigned int*) CS_TRANS11_reg))
#define CS_TRANS11_inst_adr                                                          "0x0057"
#define CS_TRANS11_inst                                                              0x0057
#define CS_TRANS11_cs_trans11_k3_shift                                               (0)
#define CS_TRANS11_cs_trans11_k3_mask                                                (0x0000FFFF)
#define CS_TRANS11_cs_trans11_k3(data)                                               (0x0000FFFF&((data)<<0))
#define CS_TRANS11_cs_trans11_k3_src(data)                                           ((0x0000FFFF&(data))>>0)
#define CS_TRANS11_get_cs_trans11_k3(data)                                           ((0x0000FFFF&(data))>>0)


#define SCALER_HSI                                                                   0x18004160
#define SCALER_HSI_reg_addr                                                          "0xB8004160"
#define SCALER_HSI_reg                                                               0xB8004160
#define set_SCALER_HSI_reg(data)   (*((volatile unsigned int*) SCALER_HSI_reg)=data)
#define get_SCALER_HSI_reg   (*((volatile unsigned int*) SCALER_HSI_reg))
#define SCALER_HSI_inst_adr                                                          "0x0058"
#define SCALER_HSI_inst                                                              0x0058
#define SCALER_HSI_hsi_offset_shift                                                  (16)
#define SCALER_HSI_hsi_offset_mask                                                   (0x07FF0000)
#define SCALER_HSI_hsi_offset(data)                                                  (0x07FF0000&((data)<<16))
#define SCALER_HSI_hsi_offset_src(data)                                              ((0x07FF0000&(data))>>16)
#define SCALER_HSI_get_hsi_offset(data)                                              ((0x07FF0000&(data))>>16)
#define SCALER_HSI_hsi_phase_shift                                                   (2)
#define SCALER_HSI_hsi_phase_mask                                                    (0x0000FFFC)
#define SCALER_HSI_hsi_phase(data)                                                   (0x0000FFFC&((data)<<2))
#define SCALER_HSI_hsi_phase_src(data)                                               ((0x0000FFFC&(data))>>2)
#define SCALER_HSI_get_hsi_phase(data)                                               ((0x0000FFFC&(data))>>2)


#define SCALER_HSD                                                                   0x18004164
#define SCALER_HSD_reg_addr                                                          "0xB8004164"
#define SCALER_HSD_reg                                                               0xB8004164
#define set_SCALER_HSD_reg(data)   (*((volatile unsigned int*) SCALER_HSD_reg)=data)
#define get_SCALER_HSD_reg   (*((volatile unsigned int*) SCALER_HSD_reg))
#define SCALER_HSD_inst_adr                                                          "0x0059"
#define SCALER_HSD_inst                                                              0x0059
#define SCALER_HSD_hsd_out_shift                                                     (20)
#define SCALER_HSD_hsd_out_mask                                                      (0x7FF00000)
#define SCALER_HSD_hsd_out(data)                                                     (0x7FF00000&((data)<<20))
#define SCALER_HSD_hsd_out_src(data)                                                 ((0x7FF00000&(data))>>20)
#define SCALER_HSD_get_hsd_out(data)                                                 ((0x7FF00000&(data))>>20)
#define SCALER_HSD_hsd_delta_shift                                                   (0)
#define SCALER_HSD_hsd_delta_mask                                                    (0x0007FFFF)
#define SCALER_HSD_hsd_delta(data)                                                   (0x0007FFFF&((data)<<0))
#define SCALER_HSD_hsd_delta_src(data)                                               ((0x0007FFFF&(data))>>0)
#define SCALER_HSD_get_hsd_delta(data)                                               ((0x0007FFFF&(data))>>0)


#define SCALER_VSI                                                                   0x18004168
#define SCALER_VSI_reg_addr                                                          "0xB8004168"
#define SCALER_VSI_reg                                                               0xB8004168
#define set_SCALER_VSI_reg(data)   (*((volatile unsigned int*) SCALER_VSI_reg)=data)
#define get_SCALER_VSI_reg   (*((volatile unsigned int*) SCALER_VSI_reg))
#define SCALER_VSI_inst_adr                                                          "0x005A"
#define SCALER_VSI_inst                                                              0x005A
#define SCALER_VSI_vsi_offset_shift                                                  (16)
#define SCALER_VSI_vsi_offset_mask                                                   (0x0FFF0000)
#define SCALER_VSI_vsi_offset(data)                                                  (0x0FFF0000&((data)<<16))
#define SCALER_VSI_vsi_offset_src(data)                                              ((0x0FFF0000&(data))>>16)
#define SCALER_VSI_get_vsi_offset(data)                                              ((0x0FFF0000&(data))>>16)
#define SCALER_VSI_vsi_phase_shift                                                   (2)
#define SCALER_VSI_vsi_phase_mask                                                    (0x0000FFFC)
#define SCALER_VSI_vsi_phase(data)                                                   (0x0000FFFC&((data)<<2))
#define SCALER_VSI_vsi_phase_src(data)                                               ((0x0000FFFC&(data))>>2)
#define SCALER_VSI_get_vsi_phase(data)                                               ((0x0000FFFC&(data))>>2)


#define SCALER_VSD                                                                   0x1800416C
#define SCALER_VSD_reg_addr                                                          "0xB800416C"
#define SCALER_VSD_reg                                                               0xB800416C
#define set_SCALER_VSD_reg(data)   (*((volatile unsigned int*) SCALER_VSD_reg)=data)
#define get_SCALER_VSD_reg   (*((volatile unsigned int*) SCALER_VSD_reg))
#define SCALER_VSD_inst_adr                                                          "0x005B"
#define SCALER_VSD_inst                                                              0x005B
#define SCALER_VSD_vsd_out_shift                                                     (20)
#define SCALER_VSD_vsd_out_mask                                                      (0x7FF00000)
#define SCALER_VSD_vsd_out(data)                                                     (0x7FF00000&((data)<<20))
#define SCALER_VSD_vsd_out_src(data)                                                 ((0x7FF00000&(data))>>20)
#define SCALER_VSD_get_vsd_out(data)                                                 ((0x7FF00000&(data))>>20)
#define SCALER_VSD_vsd_delta_shift                                                   (0)
#define SCALER_VSD_vsd_delta_mask                                                    (0x0007FFFF)
#define SCALER_VSD_vsd_delta(data)                                                   (0x0007FFFF&((data)<<0))
#define SCALER_VSD_vsd_delta_src(data)                                               ((0x0007FFFF&(data))>>0)
#define SCALER_VSD_get_vsd_delta(data)                                               ((0x0007FFFF&(data))>>0)


#define SCALER_HSYNC0                                                                0x18004170
#define SCALER_HSYNC0_reg_addr                                                       "0xB8004170"
#define SCALER_HSYNC0_reg                                                            0xB8004170
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


#define SCALER_HSYNC1                                                                0x18004174
#define SCALER_HSYNC1_reg_addr                                                       "0xB8004174"
#define SCALER_HSYNC1_reg                                                            0xB8004174
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


#define SCALER_HSYNC2                                                                0x18004178
#define SCALER_HSYNC2_reg_addr                                                       "0xB8004178"
#define SCALER_HSYNC2_reg                                                            0xB8004178
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


#define SCALER_HSYNC3                                                                0x1800417C
#define SCALER_HSYNC3_reg_addr                                                       "0xB800417C"
#define SCALER_HSYNC3_reg                                                            0xB800417C
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


#define SCALER_HSYNC4                                                                0x18004180
#define SCALER_HSYNC4_reg_addr                                                       "0xB8004180"
#define SCALER_HSYNC4_reg                                                            0xB8004180
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


#define SCALER_HSYNC5                                                                0x18004184
#define SCALER_HSYNC5_reg_addr                                                       "0xB8004184"
#define SCALER_HSYNC5_reg                                                            0xB8004184
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


#define SCALER_HSYNC6                                                                0x18004188
#define SCALER_HSYNC6_reg_addr                                                       "0xB8004188"
#define SCALER_HSYNC6_reg                                                            0xB8004188
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


#define SCALER_HSYNC7                                                                0x1800418C
#define SCALER_HSYNC7_reg_addr                                                       "0xB800418C"
#define SCALER_HSYNC7_reg                                                            0xB800418C
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


#define SCALER_HSCC0                                                                 0x18004190
#define SCALER_HSCC0_reg_addr                                                        "0xB8004190"
#define SCALER_HSCC0_reg                                                             0xB8004190
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


#define SCALER_HSCC1                                                                 0x18004194
#define SCALER_HSCC1_reg_addr                                                        "0xB8004194"
#define SCALER_HSCC1_reg                                                             0xB8004194
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


#define SCALER_HSCC2                                                                 0x18004198
#define SCALER_HSCC2_reg_addr                                                        "0xB8004198"
#define SCALER_HSCC2_reg                                                             0xB8004198
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


#define SCALER_HSCC3                                                                 0x1800419C
#define SCALER_HSCC3_reg_addr                                                        "0xB800419C"
#define SCALER_HSCC3_reg                                                             0xB800419C
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


#define SCALER_HSCC4                                                                 0x180041A0
#define SCALER_HSCC4_reg_addr                                                        "0xB80041A0"
#define SCALER_HSCC4_reg                                                             0xB80041A0
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


#define SCALER_HSCC5                                                                 0x180041A4
#define SCALER_HSCC5_reg_addr                                                        "0xB80041A4"
#define SCALER_HSCC5_reg                                                             0xB80041A4
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


#define SCALER_HSCC6                                                                 0x180041A8
#define SCALER_HSCC6_reg_addr                                                        "0xB80041A8"
#define SCALER_HSCC6_reg                                                             0xB80041A8
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


#define SCALER_HSCC7                                                                 0x180041AC
#define SCALER_HSCC7_reg_addr                                                        "0xB80041AC"
#define SCALER_HSCC7_reg                                                             0xB80041AC
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


#define SCALER_VSYC0                                                                 0x180041B0
#define SCALER_VSYC0_reg_addr                                                        "0xB80041B0"
#define SCALER_VSYC0_reg                                                             0xB80041B0
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


#define SCALER_VSYC1                                                                 0x180041B4
#define SCALER_VSYC1_reg_addr                                                        "0xB80041B4"
#define SCALER_VSYC1_reg                                                             0xB80041B4
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


#define SCALER_VSYC2                                                                 0x180041B8
#define SCALER_VSYC2_reg_addr                                                        "0xB80041B8"
#define SCALER_VSYC2_reg                                                             0xB80041B8
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


#define SCALER_VSYC3                                                                 0x180041BC
#define SCALER_VSYC3_reg_addr                                                        "0xB80041BC"
#define SCALER_VSYC3_reg                                                             0xB80041BC
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


#define SCALER_VSCC0                                                                 0x180041C0
#define SCALER_VSCC0_reg_addr                                                        "0xB80041C0"
#define SCALER_VSCC0_reg                                                             0xB80041C0
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


#define SCALER_VSCC1                                                                 0x180041C4
#define SCALER_VSCC1_reg_addr                                                        "0xB80041C4"
#define SCALER_VSCC1_reg                                                             0xB80041C4
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


#define SCALER_VSCC2                                                                 0x180041C8
#define SCALER_VSCC2_reg_addr                                                        "0xB80041C8"
#define SCALER_VSCC2_reg                                                             0xB80041C8
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


#define SCALER_VSCC3                                                                 0x180041CC
#define SCALER_VSCC3_reg_addr                                                        "0xB80041CC"
#define SCALER_VSCC3_reg                                                             0xB80041CC
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


#define CONSTANT_ALPHA                                                               0x180041D0
#define CONSTANT_ALPHA_reg_addr                                                      "0xB80041D0"
#define CONSTANT_ALPHA_reg                                                           0xB80041D0
#define set_CONSTANT_ALPHA_reg(data)   (*((volatile unsigned int*) CONSTANT_ALPHA_reg)=data)
#define get_CONSTANT_ALPHA_reg   (*((volatile unsigned int*) CONSTANT_ALPHA_reg))
#define CONSTANT_ALPHA_inst_adr                                                      "0x0074"
#define CONSTANT_ALPHA_inst                                                          0x0074
#define CONSTANT_ALPHA_alpha_shift                                                   (0)
#define CONSTANT_ALPHA_alpha_mask                                                    (0x000000FF)
#define CONSTANT_ALPHA_alpha(data)                                                   (0x000000FF&((data)<<0))
#define CONSTANT_ALPHA_alpha_src(data)                                               ((0x000000FF&(data))>>0)
#define CONSTANT_ALPHA_get_alpha(data)                                               ((0x000000FF&(data))>>0)


#define BIST_MODE                                                                    0x180041D4
#define BIST_MODE_reg_addr                                                           "0xB80041D4"
#define BIST_MODE_reg                                                                0xB80041D4
#define set_BIST_MODE_reg(data)   (*((volatile unsigned int*) BIST_MODE_reg)=data)
#define get_BIST_MODE_reg   (*((volatile unsigned int*) BIST_MODE_reg))
#define BIST_MODE_inst_adr                                                           "0x0075"
#define BIST_MODE_inst                                                               0x0075
#define BIST_MODE_drf_test_resume_shift                                              (2)
#define BIST_MODE_drf_test_resume_mask                                               (0x00000004)
#define BIST_MODE_drf_test_resume(data)                                              (0x00000004&((data)<<2))
#define BIST_MODE_drf_test_resume_src(data)                                          ((0x00000004&(data))>>2)
#define BIST_MODE_get_drf_test_resume(data)                                          ((0x00000004&(data))>>2)
#define BIST_MODE_drf_bist_mode_shift                                                (1)
#define BIST_MODE_drf_bist_mode_mask                                                 (0x00000002)
#define BIST_MODE_drf_bist_mode(data)                                                (0x00000002&((data)<<1))
#define BIST_MODE_drf_bist_mode_src(data)                                            ((0x00000002&(data))>>1)
#define BIST_MODE_get_drf_bist_mode(data)                                            ((0x00000002&(data))>>1)
#define BIST_MODE_bist_mode_shift                                                    (0)
#define BIST_MODE_bist_mode_mask                                                     (0x00000001)
#define BIST_MODE_bist_mode(data)                                                    (0x00000001&((data)<<0))
#define BIST_MODE_bist_mode_src(data)                                                ((0x00000001&(data))>>0)
#define BIST_MODE_get_bist_mode(data)                                                ((0x00000001&(data))>>0)


#define BIST_RESULT0                                                                 0x180041D8
#define BIST_RESULT0_reg_addr                                                        "0xB80041D8"
#define BIST_RESULT0_reg                                                             0xB80041D8
#define set_BIST_RESULT0_reg(data)   (*((volatile unsigned int*) BIST_RESULT0_reg)=data)
#define get_BIST_RESULT0_reg   (*((volatile unsigned int*) BIST_RESULT0_reg))
#define BIST_RESULT0_inst_adr                                                        "0x0076"
#define BIST_RESULT0_inst                                                            0x0076
#define BIST_RESULT0_drf_start_pause_shift                                           (8)
#define BIST_RESULT0_drf_start_pause_mask                                            (0x00000100)
#define BIST_RESULT0_drf_start_pause(data)                                           (0x00000100&((data)<<8))
#define BIST_RESULT0_drf_start_pause_src(data)                                       ((0x00000100&(data))>>8)
#define BIST_RESULT0_get_drf_start_pause(data)                                       ((0x00000100&(data))>>8)
#define BIST_RESULT0_drf_bist_fail2_shift                                            (7)
#define BIST_RESULT0_drf_bist_fail2_mask                                             (0x00000080)
#define BIST_RESULT0_drf_bist_fail2(data)                                            (0x00000080&((data)<<7))
#define BIST_RESULT0_drf_bist_fail2_src(data)                                        ((0x00000080&(data))>>7)
#define BIST_RESULT0_get_drf_bist_fail2(data)                                        ((0x00000080&(data))>>7)
#define BIST_RESULT0_drf_bist_fail1_shift                                            (6)
#define BIST_RESULT0_drf_bist_fail1_mask                                             (0x00000040)
#define BIST_RESULT0_drf_bist_fail1(data)                                            (0x00000040&((data)<<6))
#define BIST_RESULT0_drf_bist_fail1_src(data)                                        ((0x00000040&(data))>>6)
#define BIST_RESULT0_get_drf_bist_fail1(data)                                        ((0x00000040&(data))>>6)
#define BIST_RESULT0_drf_bist_fail0_shift                                            (5)
#define BIST_RESULT0_drf_bist_fail0_mask                                             (0x00000020)
#define BIST_RESULT0_drf_bist_fail0(data)                                            (0x00000020&((data)<<5))
#define BIST_RESULT0_drf_bist_fail0_src(data)                                        ((0x00000020&(data))>>5)
#define BIST_RESULT0_get_drf_bist_fail0(data)                                        ((0x00000020&(data))>>5)
#define BIST_RESULT0_drf_bist_done_shift                                             (4)
#define BIST_RESULT0_drf_bist_done_mask                                              (0x00000010)
#define BIST_RESULT0_drf_bist_done(data)                                             (0x00000010&((data)<<4))
#define BIST_RESULT0_drf_bist_done_src(data)                                         ((0x00000010&(data))>>4)
#define BIST_RESULT0_get_drf_bist_done(data)                                         ((0x00000010&(data))>>4)
#define BIST_RESULT0_bist_fail2_shift                                                (3)
#define BIST_RESULT0_bist_fail2_mask                                                 (0x00000008)
#define BIST_RESULT0_bist_fail2(data)                                                (0x00000008&((data)<<3))
#define BIST_RESULT0_bist_fail2_src(data)                                            ((0x00000008&(data))>>3)
#define BIST_RESULT0_get_bist_fail2(data)                                            ((0x00000008&(data))>>3)
#define BIST_RESULT0_bist_fail1_shift                                                (2)
#define BIST_RESULT0_bist_fail1_mask                                                 (0x00000004)
#define BIST_RESULT0_bist_fail1(data)                                                (0x00000004&((data)<<2))
#define BIST_RESULT0_bist_fail1_src(data)                                            ((0x00000004&(data))>>2)
#define BIST_RESULT0_get_bist_fail1(data)                                            ((0x00000004&(data))>>2)
#define BIST_RESULT0_bist_fail0_shift                                                (1)
#define BIST_RESULT0_bist_fail0_mask                                                 (0x00000002)
#define BIST_RESULT0_bist_fail0(data)                                                (0x00000002&((data)<<1))
#define BIST_RESULT0_bist_fail0_src(data)                                            ((0x00000002&(data))>>1)
#define BIST_RESULT0_get_bist_fail0(data)                                            ((0x00000002&(data))>>1)
#define BIST_RESULT0_bist_done_shift                                                 (0)
#define BIST_RESULT0_bist_done_mask                                                  (0x00000001)
#define BIST_RESULT0_bist_done(data)                                                 (0x00000001&((data)<<0))
#define BIST_RESULT0_bist_done_src(data)                                             ((0x00000001&(data))>>0)
#define BIST_RESULT0_get_bist_done(data)                                             ((0x00000001&(data))>>0)


#define BIST_RESULT1                                                                 0x180041DC
#define BIST_RESULT1_reg_addr                                                        "0xB80041DC"
#define BIST_RESULT1_reg                                                             0xB80041DC
#define set_BIST_RESULT1_reg(data)   (*((volatile unsigned int*) BIST_RESULT1_reg)=data)
#define get_BIST_RESULT1_reg   (*((volatile unsigned int*) BIST_RESULT1_reg))
#define BIST_RESULT1_inst_adr                                                        "0x0077"
#define BIST_RESULT1_inst                                                            0x0077
#define BIST_RESULT1_sram_rm_shift                                                   (1)
#define BIST_RESULT1_sram_rm_mask                                                    (0x0000001E)
#define BIST_RESULT1_sram_rm(data)                                                   (0x0000001E&((data)<<1))
#define BIST_RESULT1_sram_rm_src(data)                                               ((0x0000001E&(data))>>1)
#define BIST_RESULT1_get_sram_rm(data)                                               ((0x0000001E&(data))>>1)
#define BIST_RESULT1_sram_rme_shift                                                  (0)
#define BIST_RESULT1_sram_rme_mask                                                   (0x00000001)
#define BIST_RESULT1_sram_rme(data)                                                  (0x00000001&((data)<<0))
#define BIST_RESULT1_sram_rme_src(data)                                              ((0x00000001&(data))>>0)
#define BIST_RESULT1_get_sram_rme(data)                                              ((0x00000001&(data))>>0)


#define MIPI_SA0_UV                                                                  0x180041E0
#define MIPI_SA0_UV_reg_addr                                                         "0xB80041E0"
#define MIPI_SA0_UV_reg                                                              0xB80041E0
#define set_MIPI_SA0_UV_reg(data)   (*((volatile unsigned int*) MIPI_SA0_UV_reg)=data)
#define get_MIPI_SA0_UV_reg   (*((volatile unsigned int*) MIPI_SA0_UV_reg))
#define MIPI_SA0_UV_inst_adr                                                         "0x0078"
#define MIPI_SA0_UV_inst                                                             0x0078
#define MIPI_SA0_UV_sa0_video_uv_shift                                               (0)
#define MIPI_SA0_UV_sa0_video_uv_mask                                                (0x7FFFFFFF)
#define MIPI_SA0_UV_sa0_video_uv(data)                                               (0x7FFFFFFF&((data)<<0))
#define MIPI_SA0_UV_sa0_video_uv_src(data)                                           ((0x7FFFFFFF&(data))>>0)
#define MIPI_SA0_UV_get_sa0_video_uv(data)                                           ((0x7FFFFFFF&(data))>>0)


#define MIPI_SA1_UV                                                                  0x180041E4
#define MIPI_SA1_UV_reg_addr                                                         "0xB80041E4"
#define MIPI_SA1_UV_reg                                                              0xB80041E4
#define set_MIPI_SA1_UV_reg(data)   (*((volatile unsigned int*) MIPI_SA1_UV_reg)=data)
#define get_MIPI_SA1_UV_reg   (*((volatile unsigned int*) MIPI_SA1_UV_reg))
#define MIPI_SA1_UV_inst_adr                                                         "0x0079"
#define MIPI_SA1_UV_inst                                                             0x0079
#define MIPI_SA1_UV_sa1_video_uv_shift                                               (0)
#define MIPI_SA1_UV_sa1_video_uv_mask                                                (0x7FFFFFFF)
#define MIPI_SA1_UV_sa1_video_uv(data)                                               (0x7FFFFFFF&((data)<<0))
#define MIPI_SA1_UV_sa1_video_uv_src(data)                                           ((0x7FFFFFFF&(data))>>0)
#define MIPI_SA1_UV_get_sa1_video_uv(data)                                           ((0x7FFFFFFF&(data))>>0)


#define MIPI_SA2_UV                                                                  0x180041E8
#define MIPI_SA2_UV_reg_addr                                                         "0xB80041E8"
#define MIPI_SA2_UV_reg                                                              0xB80041E8
#define set_MIPI_SA2_UV_reg(data)   (*((volatile unsigned int*) MIPI_SA2_UV_reg)=data)
#define get_MIPI_SA2_UV_reg   (*((volatile unsigned int*) MIPI_SA2_UV_reg))
#define MIPI_SA2_UV_inst_adr                                                         "0x007A"
#define MIPI_SA2_UV_inst                                                             0x007A
#define MIPI_SA2_UV_sa2_pic_uv_shift                                                 (0)
#define MIPI_SA2_UV_sa2_pic_uv_mask                                                  (0x7FFFFFFF)
#define MIPI_SA2_UV_sa2_pic_uv(data)                                                 (0x7FFFFFFF&((data)<<0))
#define MIPI_SA2_UV_sa2_pic_uv_src(data)                                             ((0x7FFFFFFF&(data))>>0)
#define MIPI_SA2_UV_get_sa2_pic_uv(data)                                             ((0x7FFFFFFF&(data))>>0)


#define MIPI_RESET                                                                   0x180041EC
#define MIPI_RESET_reg_addr                                                          "0xB80041EC"
#define MIPI_RESET_reg                                                               0xB80041EC
#define set_MIPI_RESET_reg(data)   (*((volatile unsigned int*) MIPI_RESET_reg)=data)
#define get_MIPI_RESET_reg   (*((volatile unsigned int*) MIPI_RESET_reg))
#define MIPI_RESET_inst_adr                                                          "0x007B"
#define MIPI_RESET_inst                                                              0x007B
#define MIPI_RESET_mipi_sw_rst_shift                                                 (0)
#define MIPI_RESET_mipi_sw_rst_mask                                                  (0x00000001)
#define MIPI_RESET_mipi_sw_rst(data)                                                 (0x00000001&((data)<<0))
#define MIPI_RESET_mipi_sw_rst_src(data)                                             ((0x00000001&(data))>>0)
#define MIPI_RESET_get_mipi_sw_rst(data)                                             ((0x00000001&(data))>>0)


#define BIST_RESULT1                                                                 0x180041F0
#define BIST_RESULT1_reg_addr                                                        "0xB80041F0"
#define BIST_RESULT1_reg                                                             0xB80041F0
#define set_BIST_RESULT1_reg(data)   (*((volatile unsigned int*) BIST_RESULT1_reg)=data)
#define get_BIST_RESULT1_reg   (*((volatile unsigned int*) BIST_RESULT1_reg))
#define BIST_RESULT1_inst_adr                                                        "0x007C"
#define BIST_RESULT1_inst                                                            0x007C
#define BIST_RESULT1_dbg_sel_shift                                                   (8)
#define BIST_RESULT1_dbg_sel_mask                                                    (0x00000100)
#define BIST_RESULT1_dbg_sel(data)                                                   (0x00000100&((data)<<8))
#define BIST_RESULT1_dbg_sel_src(data)                                               ((0x00000100&(data))>>8)
#define BIST_RESULT1_get_dbg_sel(data)                                               ((0x00000100&(data))>>8)
#define BIST_RESULT1_dbg_sel1_shift                                                  (4)
#define BIST_RESULT1_dbg_sel1_mask                                                   (0x000000F0)
#define BIST_RESULT1_dbg_sel1(data)                                                  (0x000000F0&((data)<<4))
#define BIST_RESULT1_dbg_sel1_src(data)                                              ((0x000000F0&(data))>>4)
#define BIST_RESULT1_get_dbg_sel1(data)                                              ((0x000000F0&(data))>>4)
#define BIST_RESULT1_dbg_sel0_shift                                                  (0)
#define BIST_RESULT1_dbg_sel0_mask                                                   (0x0000000F)
#define BIST_RESULT1_dbg_sel0(data)                                                  (0x0000000F&((data)<<0))
#define BIST_RESULT1_dbg_sel0_src(data)                                              ((0x0000000F&(data))>>0)
#define BIST_RESULT1_get_dbg_sel0(data)                                              ((0x0000000F&(data))>>0)


#define MIPI_DUMMY_REG0                                                              0x180041F4
#define MIPI_DUMMY_REG0_reg_addr                                                     "0xB80041F4"
#define MIPI_DUMMY_REG0_reg                                                          0xB80041F4
#define set_MIPI_DUMMY_REG0_reg(data)   (*((volatile unsigned int*) MIPI_DUMMY_REG0_reg)=data)
#define get_MIPI_DUMMY_REG0_reg   (*((volatile unsigned int*) MIPI_DUMMY_REG0_reg))
#define MIPI_DUMMY_REG0_inst_adr                                                     "0x007D"
#define MIPI_DUMMY_REG0_inst                                                         0x007D
#define MIPI_DUMMY_REG0_mipi_dummy_reg0_shift                                        (0)
#define MIPI_DUMMY_REG0_mipi_dummy_reg0_mask                                         (0xFFFFFFFF)
#define MIPI_DUMMY_REG0_mipi_dummy_reg0(data)                                        (0xFFFFFFFF&((data)<<0))
#define MIPI_DUMMY_REG0_mipi_dummy_reg0_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define MIPI_DUMMY_REG0_get_mipi_dummy_reg0(data)                                    ((0xFFFFFFFF&(data))>>0)


#define MIPI_DUMMY_REG1                                                              0x180041F8
#define MIPI_DUMMY_REG1_reg_addr                                                     "0xB80041F8"
#define MIPI_DUMMY_REG1_reg                                                          0xB80041F8
#define set_MIPI_DUMMY_REG1_reg(data)   (*((volatile unsigned int*) MIPI_DUMMY_REG1_reg)=data)
#define get_MIPI_DUMMY_REG1_reg   (*((volatile unsigned int*) MIPI_DUMMY_REG1_reg))
#define MIPI_DUMMY_REG1_inst_adr                                                     "0x007E"
#define MIPI_DUMMY_REG1_inst                                                         0x007E
#define MIPI_DUMMY_REG1_mipi_dummy_reg1_shift                                        (0)
#define MIPI_DUMMY_REG1_mipi_dummy_reg1_mask                                         (0xFFFFFFFF)
#define MIPI_DUMMY_REG1_mipi_dummy_reg1(data)                                        (0xFFFFFFFF&((data)<<0))
#define MIPI_DUMMY_REG1_mipi_dummy_reg1_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define MIPI_DUMMY_REG1_get_mipi_dummy_reg1(data)                                    ((0xFFFFFFFF&(data))>>0)


#endif
