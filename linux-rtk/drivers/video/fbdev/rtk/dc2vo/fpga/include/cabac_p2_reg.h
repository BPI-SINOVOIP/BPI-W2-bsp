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


#ifndef _CABAC_P2_REG_H_INCLUDED_
#define _CABAC_P2_REG_H_INCLUDED_
#ifdef  _CABAC_P2_USE_STRUCT
typedef struct 
{
unsigned int     left_top:32;
}CABAC_P2_CABAC_LEFTTOP;

typedef struct 
{
unsigned int     left_bot:32;
}CABAC_P2_CABAC_LEFTBOT;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     high:9;
unsigned int     bits:4;
unsigned int     code_word:16;
}CABAC_P2_VP6_BAC;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_enable7:1;
unsigned int     reset_cabacp2_bsfifo:1;
unsigned int     write_enable6:1;
unsigned int     decode_en_cabacp2:1;
unsigned int     write_enable5:1;
unsigned int     cabac_1p_mode:1;
unsigned int     write_enable4:1;
unsigned int     cabac_p2_p3:1;
unsigned int     write_enable3:1;
unsigned int     cabac_p2_go:1;
unsigned int     write_enable2:1;
unsigned int     latch_enable:1;
unsigned int     write_enable1:1;
unsigned int     codioffset:9;
unsigned int     codirange:9;
}CABAC_P2_CABAC_P2_CNTL3;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_enable5:1;
unsigned int     arb_wait_value:5;
unsigned int     write_enable4:1;
unsigned int     HaltCabacp2_done:1;
unsigned int     write_enable3:1;
unsigned int     HaltCabacp2:1;
unsigned int     write_enable2:1;
unsigned int     Cabacp2_idle:1;
unsigned int     write_enable1:1;
unsigned int     cabacp2_header_byte_cnt:18;
}CABAC_P2_CABAC_P2_CNTL4;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     cabac_p2_wfifo_err:1;
unsigned int     cabac_p2_bsfifo_err:1;
unsigned int     cabac_p2_dec_err:1;
unsigned int     cabac_p2_done:1;
unsigned int     write_data:1;
}CABAC_P2_CABACP2_INT_STATUS;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     cabac_p2_wfifo_err_ie:1;
unsigned int     cabac_p2_bsfifo_err_ie:1;
unsigned int     cabac_p2_dec_err_ie:1;
unsigned int     cabac_p2_done_ie:1;
unsigned int     write_data:1;
}CABAC_P2_CABACP2_INT_EN;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     write_enable3:1;
unsigned int     coding_type:4;
unsigned int     write_enable2:1;
unsigned int     cabacp2_pred_counter:10;
unsigned int     write_enable1:1;
unsigned int     cabacp2_curmb_addr:10;
}CABAC_P2_CABAC_P2_CNTL5;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     write_enable3:1;
unsigned int     p2_startcode_prevnt_en:1;
unsigned int     write_enable2:1;
unsigned int     detect_startcode_error:1;
unsigned int     write_enable1:1;
unsigned int     min_xfer_size:2;
}CABAC_P2_P2_BSCNTL;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     min_thre:7;
}CABAC_P2_P2_BS_MIN_THR;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     timer_value:24;
}CABAC_P2_P2_BSTIMER;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     base_addr:31;
}CABAC_P2_P2_RFIFO_BASE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     limit_addr:31;
}CABAC_P2_P2_RFIFO_LIMIT;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     wr_ptr:31;
}CABAC_P2_P2_RFIFO_WPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     rd_ptr:31;
}CABAC_P2_P2_RFIFO_RPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     base_addr:31;
}CABAC_P2_P2_WFIFO_BASE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     limit_addr:31;
}CABAC_P2_P2_WFIFO_LIMIT;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     wr_ptr:31;
}CABAC_P2_P2_WFIFO_WPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     rd_ptr:31;
}CABAC_P2_P2_WFIFO_RPTR;

typedef struct 
{
unsigned int     dec_bit_ptr:32;
}CABAC_P2_P2_RFIFO_DECBSPTR;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     dec_bit_ptr_msb:2;
}CABAC_P2_P2_RFIFO_DECBSPTR_MSB;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     entropy_coding_mode:1;
unsigned int     pic_init_qp:6;
unsigned int     chroma_qp_offset:5;
unsigned int     second_chroma_qp_offset:5;
unsigned int     direct_8x8_inferflg:1;
unsigned int     transform_8x8_mode_flg:1;
unsigned int     num_ref_idx_l0_active_minus1:5;
unsigned int     num_ref_idx_l1_active_minus1:5;
}CABAC_P2_CABAC_P2_CNTL;

typedef struct 
{
unsigned int     write_enable7:1;
unsigned int     mb_adaptive_frame_field_flag:1;
unsigned int     write_enable6:1;
unsigned int     picmb_w:10;
unsigned int     write_enable5:1;
unsigned int     monochrome:1;
unsigned int     write_enable4:1;
unsigned int     field_pic_flag:1;
unsigned int     write_enable3:1;
unsigned int     pic_type:3;
unsigned int     write_enable2:1;
unsigned int     slice_qp_delta:7;
unsigned int     write_enable1:1;
unsigned int     cabac_init_idc:2;
}CABAC_P2_CABAC_P2_CNTL2;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     write_enable3:1;
unsigned int     cabac_halt_done:1;
unsigned int     write_enable2:1;
unsigned int     cabac_halt:1;
unsigned int     write_enable1:1;
unsigned int     postwrite_en:1;
}CABAC_P2_P2_NDB_CTL;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     base_addr:31;
}CABAC_P2_NDB_CABAC_BASE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     limit_addr:31;
}CABAC_P2_NDB_CABAC_LIMIT;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     wr_ptr:31;
}CABAC_P2_NDB_CABAC_WPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     rd_ptr:31;
}CABAC_P2_NDB_CABAC_RPTR;

#endif

#define CABAC_P2_CABAC_LEFTTOP_0                                                     0x1800E030
#define CABAC_P2_CABAC_LEFTTOP_1                                                     0x1800E034
#define CABAC_P2_CABAC_LEFTTOP_2                                                     0x1800E038
#define CABAC_P2_CABAC_LEFTTOP_3                                                     0x1800E03C
#define CABAC_P2_CABAC_LEFTTOP_4                                                     0x1800E040
#define CABAC_P2_CABAC_LEFTTOP_5                                                     0x1800E044
#define CABAC_P2_CABAC_LEFTTOP_0_reg_addr                                            "0xB800E030"
#define CABAC_P2_CABAC_LEFTTOP_1_reg_addr                                            "0xB800E034"
#define CABAC_P2_CABAC_LEFTTOP_2_reg_addr                                            "0xB800E038"
#define CABAC_P2_CABAC_LEFTTOP_3_reg_addr                                            "0xB800E03C"
#define CABAC_P2_CABAC_LEFTTOP_4_reg_addr                                            "0xB800E040"
#define CABAC_P2_CABAC_LEFTTOP_5_reg_addr                                            "0xB800E044"
#define CABAC_P2_CABAC_LEFTTOP_0_reg                                                 0xB800E030
#define CABAC_P2_CABAC_LEFTTOP_1_reg                                                 0xB800E034
#define CABAC_P2_CABAC_LEFTTOP_2_reg                                                 0xB800E038
#define CABAC_P2_CABAC_LEFTTOP_3_reg                                                 0xB800E03C
#define CABAC_P2_CABAC_LEFTTOP_4_reg                                                 0xB800E040
#define CABAC_P2_CABAC_LEFTTOP_5_reg                                                 0xB800E044
#define set_CABAC_P2_CABAC_LEFTTOP_0_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTTOP_0_reg)=data)
#define set_CABAC_P2_CABAC_LEFTTOP_1_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTTOP_1_reg)=data)
#define set_CABAC_P2_CABAC_LEFTTOP_2_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTTOP_2_reg)=data)
#define set_CABAC_P2_CABAC_LEFTTOP_3_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTTOP_3_reg)=data)
#define set_CABAC_P2_CABAC_LEFTTOP_4_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTTOP_4_reg)=data)
#define set_CABAC_P2_CABAC_LEFTTOP_5_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTTOP_5_reg)=data)
#define get_CABAC_P2_CABAC_LEFTTOP_0_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTTOP_0_reg))
#define get_CABAC_P2_CABAC_LEFTTOP_1_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTTOP_1_reg))
#define get_CABAC_P2_CABAC_LEFTTOP_2_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTTOP_2_reg))
#define get_CABAC_P2_CABAC_LEFTTOP_3_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTTOP_3_reg))
#define get_CABAC_P2_CABAC_LEFTTOP_4_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTTOP_4_reg))
#define get_CABAC_P2_CABAC_LEFTTOP_5_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTTOP_5_reg))
#define CABAC_P2_CABAC_LEFTTOP_0_inst_adr                                            "0x000C"
#define CABAC_P2_CABAC_LEFTTOP_1_inst_adr                                            "0x000D"
#define CABAC_P2_CABAC_LEFTTOP_2_inst_adr                                            "0x000E"
#define CABAC_P2_CABAC_LEFTTOP_3_inst_adr                                            "0x000F"
#define CABAC_P2_CABAC_LEFTTOP_4_inst_adr                                            "0x0010"
#define CABAC_P2_CABAC_LEFTTOP_5_inst_adr                                            "0x0011"
#define CABAC_P2_CABAC_LEFTTOP_0_inst                                                0x000C
#define CABAC_P2_CABAC_LEFTTOP_1_inst                                                0x000D
#define CABAC_P2_CABAC_LEFTTOP_2_inst                                                0x000E
#define CABAC_P2_CABAC_LEFTTOP_3_inst                                                0x000F
#define CABAC_P2_CABAC_LEFTTOP_4_inst                                                0x0010
#define CABAC_P2_CABAC_LEFTTOP_5_inst                                                0x0011
#define CABAC_P2_CABAC_LEFTTOP_left_top_shift                                        (0)
#define CABAC_P2_CABAC_LEFTTOP_left_top_mask                                         (0xFFFFFFFF)
#define CABAC_P2_CABAC_LEFTTOP_left_top(data)                                        (0xFFFFFFFF&((data)<<0))
#define CABAC_P2_CABAC_LEFTTOP_left_top_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define CABAC_P2_CABAC_LEFTTOP_get_left_top(data)                                    ((0xFFFFFFFF&(data))>>0)


#define CABAC_P2_CABAC_LEFTBOT_0                                                     0x1800E050
#define CABAC_P2_CABAC_LEFTBOT_1                                                     0x1800E054
#define CABAC_P2_CABAC_LEFTBOT_2                                                     0x1800E058
#define CABAC_P2_CABAC_LEFTBOT_3                                                     0x1800E05C
#define CABAC_P2_CABAC_LEFTBOT_4                                                     0x1800E060
#define CABAC_P2_CABAC_LEFTBOT_5                                                     0x1800E064
#define CABAC_P2_CABAC_LEFTBOT_0_reg_addr                                            "0xB800E050"
#define CABAC_P2_CABAC_LEFTBOT_1_reg_addr                                            "0xB800E054"
#define CABAC_P2_CABAC_LEFTBOT_2_reg_addr                                            "0xB800E058"
#define CABAC_P2_CABAC_LEFTBOT_3_reg_addr                                            "0xB800E05C"
#define CABAC_P2_CABAC_LEFTBOT_4_reg_addr                                            "0xB800E060"
#define CABAC_P2_CABAC_LEFTBOT_5_reg_addr                                            "0xB800E064"
#define CABAC_P2_CABAC_LEFTBOT_0_reg                                                 0xB800E050
#define CABAC_P2_CABAC_LEFTBOT_1_reg                                                 0xB800E054
#define CABAC_P2_CABAC_LEFTBOT_2_reg                                                 0xB800E058
#define CABAC_P2_CABAC_LEFTBOT_3_reg                                                 0xB800E05C
#define CABAC_P2_CABAC_LEFTBOT_4_reg                                                 0xB800E060
#define CABAC_P2_CABAC_LEFTBOT_5_reg                                                 0xB800E064
#define set_CABAC_P2_CABAC_LEFTBOT_0_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTBOT_0_reg)=data)
#define set_CABAC_P2_CABAC_LEFTBOT_1_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTBOT_1_reg)=data)
#define set_CABAC_P2_CABAC_LEFTBOT_2_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTBOT_2_reg)=data)
#define set_CABAC_P2_CABAC_LEFTBOT_3_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTBOT_3_reg)=data)
#define set_CABAC_P2_CABAC_LEFTBOT_4_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTBOT_4_reg)=data)
#define set_CABAC_P2_CABAC_LEFTBOT_5_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTBOT_5_reg)=data)
#define get_CABAC_P2_CABAC_LEFTBOT_0_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTBOT_0_reg))
#define get_CABAC_P2_CABAC_LEFTBOT_1_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTBOT_1_reg))
#define get_CABAC_P2_CABAC_LEFTBOT_2_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTBOT_2_reg))
#define get_CABAC_P2_CABAC_LEFTBOT_3_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTBOT_3_reg))
#define get_CABAC_P2_CABAC_LEFTBOT_4_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTBOT_4_reg))
#define get_CABAC_P2_CABAC_LEFTBOT_5_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_LEFTBOT_5_reg))
#define CABAC_P2_CABAC_LEFTBOT_0_inst_adr                                            "0x0014"
#define CABAC_P2_CABAC_LEFTBOT_1_inst_adr                                            "0x0015"
#define CABAC_P2_CABAC_LEFTBOT_2_inst_adr                                            "0x0016"
#define CABAC_P2_CABAC_LEFTBOT_3_inst_adr                                            "0x0017"
#define CABAC_P2_CABAC_LEFTBOT_4_inst_adr                                            "0x0018"
#define CABAC_P2_CABAC_LEFTBOT_5_inst_adr                                            "0x0019"
#define CABAC_P2_CABAC_LEFTBOT_0_inst                                                0x0014
#define CABAC_P2_CABAC_LEFTBOT_1_inst                                                0x0015
#define CABAC_P2_CABAC_LEFTBOT_2_inst                                                0x0016
#define CABAC_P2_CABAC_LEFTBOT_3_inst                                                0x0017
#define CABAC_P2_CABAC_LEFTBOT_4_inst                                                0x0018
#define CABAC_P2_CABAC_LEFTBOT_5_inst                                                0x0019
#define CABAC_P2_CABAC_LEFTBOT_left_bot_shift                                        (0)
#define CABAC_P2_CABAC_LEFTBOT_left_bot_mask                                         (0xFFFFFFFF)
#define CABAC_P2_CABAC_LEFTBOT_left_bot(data)                                        (0xFFFFFFFF&((data)<<0))
#define CABAC_P2_CABAC_LEFTBOT_left_bot_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define CABAC_P2_CABAC_LEFTBOT_get_left_bot(data)                                    ((0xFFFFFFFF&(data))>>0)


#define CABAC_P2_VP6_BAC                                                             0x1800E070
#define CABAC_P2_VP6_BAC_reg_addr                                                    "0xB800E070"
#define CABAC_P2_VP6_BAC_reg                                                         0xB800E070
#define set_CABAC_P2_VP6_BAC_reg(data)   (*((volatile unsigned int*) CABAC_P2_VP6_BAC_reg)=data)
#define get_CABAC_P2_VP6_BAC_reg   (*((volatile unsigned int*) CABAC_P2_VP6_BAC_reg))
#define CABAC_P2_VP6_BAC_inst_adr                                                    "0x001C"
#define CABAC_P2_VP6_BAC_inst                                                        0x001C
#define CABAC_P2_VP6_BAC_high_shift                                                  (20)
#define CABAC_P2_VP6_BAC_high_mask                                                   (0x1FF00000)
#define CABAC_P2_VP6_BAC_high(data)                                                  (0x1FF00000&((data)<<20))
#define CABAC_P2_VP6_BAC_high_src(data)                                              ((0x1FF00000&(data))>>20)
#define CABAC_P2_VP6_BAC_get_high(data)                                              ((0x1FF00000&(data))>>20)
#define CABAC_P2_VP6_BAC_bits_shift                                                  (16)
#define CABAC_P2_VP6_BAC_bits_mask                                                   (0x000F0000)
#define CABAC_P2_VP6_BAC_bits(data)                                                  (0x000F0000&((data)<<16))
#define CABAC_P2_VP6_BAC_bits_src(data)                                              ((0x000F0000&(data))>>16)
#define CABAC_P2_VP6_BAC_get_bits(data)                                              ((0x000F0000&(data))>>16)
#define CABAC_P2_VP6_BAC_code_word_shift                                             (0)
#define CABAC_P2_VP6_BAC_code_word_mask                                              (0x0000FFFF)
#define CABAC_P2_VP6_BAC_code_word(data)                                             (0x0000FFFF&((data)<<0))
#define CABAC_P2_VP6_BAC_code_word_src(data)                                         ((0x0000FFFF&(data))>>0)
#define CABAC_P2_VP6_BAC_get_code_word(data)                                         ((0x0000FFFF&(data))>>0)


#define CABAC_P2_CABAC_P2_CNTL3                                                      0x1800E360
#define CABAC_P2_CABAC_P2_CNTL3_reg_addr                                             "0xB800E360"
#define CABAC_P2_CABAC_P2_CNTL3_reg                                                  0xB800E360
#define set_CABAC_P2_CABAC_P2_CNTL3_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_P2_CNTL3_reg)=data)
#define get_CABAC_P2_CABAC_P2_CNTL3_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_P2_CNTL3_reg))
#define CABAC_P2_CABAC_P2_CNTL3_inst_adr                                             "0x00D8"
#define CABAC_P2_CABAC_P2_CNTL3_inst                                                 0x00D8
#define CABAC_P2_CABAC_P2_CNTL3_write_enable7_shift                                  (30)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable7_mask                                   (0x40000000)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable7(data)                                  (0x40000000&((data)<<30))
#define CABAC_P2_CABAC_P2_CNTL3_write_enable7_src(data)                              ((0x40000000&(data))>>30)
#define CABAC_P2_CABAC_P2_CNTL3_get_write_enable7(data)                              ((0x40000000&(data))>>30)
#define CABAC_P2_CABAC_P2_CNTL3_reset_cabacp2_bsfifo_shift                           (29)
#define CABAC_P2_CABAC_P2_CNTL3_reset_cabacp2_bsfifo_mask                            (0x20000000)
#define CABAC_P2_CABAC_P2_CNTL3_reset_cabacp2_bsfifo(data)                           (0x20000000&((data)<<29))
#define CABAC_P2_CABAC_P2_CNTL3_reset_cabacp2_bsfifo_src(data)                       ((0x20000000&(data))>>29)
#define CABAC_P2_CABAC_P2_CNTL3_get_reset_cabacp2_bsfifo(data)                       ((0x20000000&(data))>>29)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable6_shift                                  (28)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable6_mask                                   (0x10000000)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable6(data)                                  (0x10000000&((data)<<28))
#define CABAC_P2_CABAC_P2_CNTL3_write_enable6_src(data)                              ((0x10000000&(data))>>28)
#define CABAC_P2_CABAC_P2_CNTL3_get_write_enable6(data)                              ((0x10000000&(data))>>28)
#define CABAC_P2_CABAC_P2_CNTL3_decode_en_cabacp2_shift                              (27)
#define CABAC_P2_CABAC_P2_CNTL3_decode_en_cabacp2_mask                               (0x08000000)
#define CABAC_P2_CABAC_P2_CNTL3_decode_en_cabacp2(data)                              (0x08000000&((data)<<27))
#define CABAC_P2_CABAC_P2_CNTL3_decode_en_cabacp2_src(data)                          ((0x08000000&(data))>>27)
#define CABAC_P2_CABAC_P2_CNTL3_get_decode_en_cabacp2(data)                          ((0x08000000&(data))>>27)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable5_shift                                  (26)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable5_mask                                   (0x04000000)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable5(data)                                  (0x04000000&((data)<<26))
#define CABAC_P2_CABAC_P2_CNTL3_write_enable5_src(data)                              ((0x04000000&(data))>>26)
#define CABAC_P2_CABAC_P2_CNTL3_get_write_enable5(data)                              ((0x04000000&(data))>>26)
#define CABAC_P2_CABAC_P2_CNTL3_cabac_1p_mode_shift                                  (25)
#define CABAC_P2_CABAC_P2_CNTL3_cabac_1p_mode_mask                                   (0x02000000)
#define CABAC_P2_CABAC_P2_CNTL3_cabac_1p_mode(data)                                  (0x02000000&((data)<<25))
#define CABAC_P2_CABAC_P2_CNTL3_cabac_1p_mode_src(data)                              ((0x02000000&(data))>>25)
#define CABAC_P2_CABAC_P2_CNTL3_get_cabac_1p_mode(data)                              ((0x02000000&(data))>>25)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable4_shift                                  (24)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable4_mask                                   (0x01000000)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable4(data)                                  (0x01000000&((data)<<24))
#define CABAC_P2_CABAC_P2_CNTL3_write_enable4_src(data)                              ((0x01000000&(data))>>24)
#define CABAC_P2_CABAC_P2_CNTL3_get_write_enable4(data)                              ((0x01000000&(data))>>24)
#define CABAC_P2_CABAC_P2_CNTL3_cabac_p2_p3_shift                                    (23)
#define CABAC_P2_CABAC_P2_CNTL3_cabac_p2_p3_mask                                     (0x00800000)
#define CABAC_P2_CABAC_P2_CNTL3_cabac_p2_p3(data)                                    (0x00800000&((data)<<23))
#define CABAC_P2_CABAC_P2_CNTL3_cabac_p2_p3_src(data)                                ((0x00800000&(data))>>23)
#define CABAC_P2_CABAC_P2_CNTL3_get_cabac_p2_p3(data)                                ((0x00800000&(data))>>23)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable3_shift                                  (22)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable3_mask                                   (0x00400000)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable3(data)                                  (0x00400000&((data)<<22))
#define CABAC_P2_CABAC_P2_CNTL3_write_enable3_src(data)                              ((0x00400000&(data))>>22)
#define CABAC_P2_CABAC_P2_CNTL3_get_write_enable3(data)                              ((0x00400000&(data))>>22)
#define CABAC_P2_CABAC_P2_CNTL3_cabac_p2_go_shift                                    (21)
#define CABAC_P2_CABAC_P2_CNTL3_cabac_p2_go_mask                                     (0x00200000)
#define CABAC_P2_CABAC_P2_CNTL3_cabac_p2_go(data)                                    (0x00200000&((data)<<21))
#define CABAC_P2_CABAC_P2_CNTL3_cabac_p2_go_src(data)                                ((0x00200000&(data))>>21)
#define CABAC_P2_CABAC_P2_CNTL3_get_cabac_p2_go(data)                                ((0x00200000&(data))>>21)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable2_shift                                  (20)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable2_mask                                   (0x00100000)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable2(data)                                  (0x00100000&((data)<<20))
#define CABAC_P2_CABAC_P2_CNTL3_write_enable2_src(data)                              ((0x00100000&(data))>>20)
#define CABAC_P2_CABAC_P2_CNTL3_get_write_enable2(data)                              ((0x00100000&(data))>>20)
#define CABAC_P2_CABAC_P2_CNTL3_latch_enable_shift                                   (19)
#define CABAC_P2_CABAC_P2_CNTL3_latch_enable_mask                                    (0x00080000)
#define CABAC_P2_CABAC_P2_CNTL3_latch_enable(data)                                   (0x00080000&((data)<<19))
#define CABAC_P2_CABAC_P2_CNTL3_latch_enable_src(data)                               ((0x00080000&(data))>>19)
#define CABAC_P2_CABAC_P2_CNTL3_get_latch_enable(data)                               ((0x00080000&(data))>>19)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable1_shift                                  (18)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable1_mask                                   (0x00040000)
#define CABAC_P2_CABAC_P2_CNTL3_write_enable1(data)                                  (0x00040000&((data)<<18))
#define CABAC_P2_CABAC_P2_CNTL3_write_enable1_src(data)                              ((0x00040000&(data))>>18)
#define CABAC_P2_CABAC_P2_CNTL3_get_write_enable1(data)                              ((0x00040000&(data))>>18)
#define CABAC_P2_CABAC_P2_CNTL3_codioffset_shift                                     (9)
#define CABAC_P2_CABAC_P2_CNTL3_codioffset_mask                                      (0x0003FE00)
#define CABAC_P2_CABAC_P2_CNTL3_codioffset(data)                                     (0x0003FE00&((data)<<9))
#define CABAC_P2_CABAC_P2_CNTL3_codioffset_src(data)                                 ((0x0003FE00&(data))>>9)
#define CABAC_P2_CABAC_P2_CNTL3_get_codioffset(data)                                 ((0x0003FE00&(data))>>9)
#define CABAC_P2_CABAC_P2_CNTL3_codirange_shift                                      (0)
#define CABAC_P2_CABAC_P2_CNTL3_codirange_mask                                       (0x000001FF)
#define CABAC_P2_CABAC_P2_CNTL3_codirange(data)                                      (0x000001FF&((data)<<0))
#define CABAC_P2_CABAC_P2_CNTL3_codirange_src(data)                                  ((0x000001FF&(data))>>0)
#define CABAC_P2_CABAC_P2_CNTL3_get_codirange(data)                                  ((0x000001FF&(data))>>0)


#define CABAC_P2_CABAC_P2_CNTL4                                                      0x1800E3D0
#define CABAC_P2_CABAC_P2_CNTL4_reg_addr                                             "0xB800E3D0"
#define CABAC_P2_CABAC_P2_CNTL4_reg                                                  0xB800E3D0
#define set_CABAC_P2_CABAC_P2_CNTL4_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_P2_CNTL4_reg)=data)
#define get_CABAC_P2_CABAC_P2_CNTL4_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_P2_CNTL4_reg))
#define CABAC_P2_CABAC_P2_CNTL4_inst_adr                                             "0x00F4"
#define CABAC_P2_CABAC_P2_CNTL4_inst                                                 0x00F4
#define CABAC_P2_CABAC_P2_CNTL4_write_enable5_shift                                  (30)
#define CABAC_P2_CABAC_P2_CNTL4_write_enable5_mask                                   (0x40000000)
#define CABAC_P2_CABAC_P2_CNTL4_write_enable5(data)                                  (0x40000000&((data)<<30))
#define CABAC_P2_CABAC_P2_CNTL4_write_enable5_src(data)                              ((0x40000000&(data))>>30)
#define CABAC_P2_CABAC_P2_CNTL4_get_write_enable5(data)                              ((0x40000000&(data))>>30)
#define CABAC_P2_CABAC_P2_CNTL4_arb_wait_value_shift                                 (25)
#define CABAC_P2_CABAC_P2_CNTL4_arb_wait_value_mask                                  (0x3E000000)
#define CABAC_P2_CABAC_P2_CNTL4_arb_wait_value(data)                                 (0x3E000000&((data)<<25))
#define CABAC_P2_CABAC_P2_CNTL4_arb_wait_value_src(data)                             ((0x3E000000&(data))>>25)
#define CABAC_P2_CABAC_P2_CNTL4_get_arb_wait_value(data)                             ((0x3E000000&(data))>>25)
#define CABAC_P2_CABAC_P2_CNTL4_write_enable4_shift                                  (24)
#define CABAC_P2_CABAC_P2_CNTL4_write_enable4_mask                                   (0x01000000)
#define CABAC_P2_CABAC_P2_CNTL4_write_enable4(data)                                  (0x01000000&((data)<<24))
#define CABAC_P2_CABAC_P2_CNTL4_write_enable4_src(data)                              ((0x01000000&(data))>>24)
#define CABAC_P2_CABAC_P2_CNTL4_get_write_enable4(data)                              ((0x01000000&(data))>>24)
#define CABAC_P2_CABAC_P2_CNTL4_HaltCabacp2_done_shift                               (23)
#define CABAC_P2_CABAC_P2_CNTL4_HaltCabacp2_done_mask                                (0x00800000)
#define CABAC_P2_CABAC_P2_CNTL4_HaltCabacp2_done(data)                               (0x00800000&((data)<<23))
#define CABAC_P2_CABAC_P2_CNTL4_HaltCabacp2_done_src(data)                           ((0x00800000&(data))>>23)
#define CABAC_P2_CABAC_P2_CNTL4_get_HaltCabacp2_done(data)                           ((0x00800000&(data))>>23)
#define CABAC_P2_CABAC_P2_CNTL4_write_enable3_shift                                  (22)
#define CABAC_P2_CABAC_P2_CNTL4_write_enable3_mask                                   (0x00400000)
#define CABAC_P2_CABAC_P2_CNTL4_write_enable3(data)                                  (0x00400000&((data)<<22))
#define CABAC_P2_CABAC_P2_CNTL4_write_enable3_src(data)                              ((0x00400000&(data))>>22)
#define CABAC_P2_CABAC_P2_CNTL4_get_write_enable3(data)                              ((0x00400000&(data))>>22)
#define CABAC_P2_CABAC_P2_CNTL4_HaltCabacp2_shift                                    (21)
#define CABAC_P2_CABAC_P2_CNTL4_HaltCabacp2_mask                                     (0x00200000)
#define CABAC_P2_CABAC_P2_CNTL4_HaltCabacp2(data)                                    (0x00200000&((data)<<21))
#define CABAC_P2_CABAC_P2_CNTL4_HaltCabacp2_src(data)                                ((0x00200000&(data))>>21)
#define CABAC_P2_CABAC_P2_CNTL4_get_HaltCabacp2(data)                                ((0x00200000&(data))>>21)
#define CABAC_P2_CABAC_P2_CNTL4_write_enable2_shift                                  (20)
#define CABAC_P2_CABAC_P2_CNTL4_write_enable2_mask                                   (0x00100000)
#define CABAC_P2_CABAC_P2_CNTL4_write_enable2(data)                                  (0x00100000&((data)<<20))
#define CABAC_P2_CABAC_P2_CNTL4_write_enable2_src(data)                              ((0x00100000&(data))>>20)
#define CABAC_P2_CABAC_P2_CNTL4_get_write_enable2(data)                              ((0x00100000&(data))>>20)
#define CABAC_P2_CABAC_P2_CNTL4_Cabacp2_idle_shift                                   (19)
#define CABAC_P2_CABAC_P2_CNTL4_Cabacp2_idle_mask                                    (0x00080000)
#define CABAC_P2_CABAC_P2_CNTL4_Cabacp2_idle(data)                                   (0x00080000&((data)<<19))
#define CABAC_P2_CABAC_P2_CNTL4_Cabacp2_idle_src(data)                               ((0x00080000&(data))>>19)
#define CABAC_P2_CABAC_P2_CNTL4_get_Cabacp2_idle(data)                               ((0x00080000&(data))>>19)
#define CABAC_P2_CABAC_P2_CNTL4_write_enable1_shift                                  (18)
#define CABAC_P2_CABAC_P2_CNTL4_write_enable1_mask                                   (0x00040000)
#define CABAC_P2_CABAC_P2_CNTL4_write_enable1(data)                                  (0x00040000&((data)<<18))
#define CABAC_P2_CABAC_P2_CNTL4_write_enable1_src(data)                              ((0x00040000&(data))>>18)
#define CABAC_P2_CABAC_P2_CNTL4_get_write_enable1(data)                              ((0x00040000&(data))>>18)
#define CABAC_P2_CABAC_P2_CNTL4_cabacp2_header_byte_cnt_shift                        (0)
#define CABAC_P2_CABAC_P2_CNTL4_cabacp2_header_byte_cnt_mask                         (0x0003FFFF)
#define CABAC_P2_CABAC_P2_CNTL4_cabacp2_header_byte_cnt(data)                        (0x0003FFFF&((data)<<0))
#define CABAC_P2_CABAC_P2_CNTL4_cabacp2_header_byte_cnt_src(data)                    ((0x0003FFFF&(data))>>0)
#define CABAC_P2_CABAC_P2_CNTL4_get_cabacp2_header_byte_cnt(data)                    ((0x0003FFFF&(data))>>0)


#define CABAC_P2_CABACP2_INT_STATUS                                                  0x1800E3D4
#define CABAC_P2_CABACP2_INT_STATUS_reg_addr                                         "0xB800E3D4"
#define CABAC_P2_CABACP2_INT_STATUS_reg                                              0xB800E3D4
#define set_CABAC_P2_CABACP2_INT_STATUS_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABACP2_INT_STATUS_reg)=data)
#define get_CABAC_P2_CABACP2_INT_STATUS_reg   (*((volatile unsigned int*) CABAC_P2_CABACP2_INT_STATUS_reg))
#define CABAC_P2_CABACP2_INT_STATUS_inst_adr                                         "0x00F5"
#define CABAC_P2_CABACP2_INT_STATUS_inst                                             0x00F5
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_wfifo_err_shift                         (4)
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_wfifo_err_mask                          (0x00000010)
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_wfifo_err(data)                         (0x00000010&((data)<<4))
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_wfifo_err_src(data)                     ((0x00000010&(data))>>4)
#define CABAC_P2_CABACP2_INT_STATUS_get_cabac_p2_wfifo_err(data)                     ((0x00000010&(data))>>4)
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_bsfifo_err_shift                        (3)
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_bsfifo_err_mask                         (0x00000008)
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_bsfifo_err(data)                        (0x00000008&((data)<<3))
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_bsfifo_err_src(data)                    ((0x00000008&(data))>>3)
#define CABAC_P2_CABACP2_INT_STATUS_get_cabac_p2_bsfifo_err(data)                    ((0x00000008&(data))>>3)
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_dec_err_shift                           (2)
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_dec_err_mask                            (0x00000004)
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_dec_err(data)                           (0x00000004&((data)<<2))
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_dec_err_src(data)                       ((0x00000004&(data))>>2)
#define CABAC_P2_CABACP2_INT_STATUS_get_cabac_p2_dec_err(data)                       ((0x00000004&(data))>>2)
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_done_shift                              (1)
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_done_mask                               (0x00000002)
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_done(data)                              (0x00000002&((data)<<1))
#define CABAC_P2_CABACP2_INT_STATUS_cabac_p2_done_src(data)                          ((0x00000002&(data))>>1)
#define CABAC_P2_CABACP2_INT_STATUS_get_cabac_p2_done(data)                          ((0x00000002&(data))>>1)
#define CABAC_P2_CABACP2_INT_STATUS_write_data_shift                                 (0)
#define CABAC_P2_CABACP2_INT_STATUS_write_data_mask                                  (0x00000001)
#define CABAC_P2_CABACP2_INT_STATUS_write_data(data)                                 (0x00000001&((data)<<0))
#define CABAC_P2_CABACP2_INT_STATUS_write_data_src(data)                             ((0x00000001&(data))>>0)
#define CABAC_P2_CABACP2_INT_STATUS_get_write_data(data)                             ((0x00000001&(data))>>0)


#define CABAC_P2_CABACP2_INT_EN                                                      0x1800E3D8
#define CABAC_P2_CABACP2_INT_EN_reg_addr                                             "0xB800E3D8"
#define CABAC_P2_CABACP2_INT_EN_reg                                                  0xB800E3D8
#define set_CABAC_P2_CABACP2_INT_EN_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABACP2_INT_EN_reg)=data)
#define get_CABAC_P2_CABACP2_INT_EN_reg   (*((volatile unsigned int*) CABAC_P2_CABACP2_INT_EN_reg))
#define CABAC_P2_CABACP2_INT_EN_inst_adr                                             "0x00F6"
#define CABAC_P2_CABACP2_INT_EN_inst                                                 0x00F6
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_wfifo_err_ie_shift                          (4)
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_wfifo_err_ie_mask                           (0x00000010)
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_wfifo_err_ie(data)                          (0x00000010&((data)<<4))
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_wfifo_err_ie_src(data)                      ((0x00000010&(data))>>4)
#define CABAC_P2_CABACP2_INT_EN_get_cabac_p2_wfifo_err_ie(data)                      ((0x00000010&(data))>>4)
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_bsfifo_err_ie_shift                         (3)
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_bsfifo_err_ie_mask                          (0x00000008)
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_bsfifo_err_ie(data)                         (0x00000008&((data)<<3))
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_bsfifo_err_ie_src(data)                     ((0x00000008&(data))>>3)
#define CABAC_P2_CABACP2_INT_EN_get_cabac_p2_bsfifo_err_ie(data)                     ((0x00000008&(data))>>3)
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_dec_err_ie_shift                            (2)
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_dec_err_ie_mask                             (0x00000004)
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_dec_err_ie(data)                            (0x00000004&((data)<<2))
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_dec_err_ie_src(data)                        ((0x00000004&(data))>>2)
#define CABAC_P2_CABACP2_INT_EN_get_cabac_p2_dec_err_ie(data)                        ((0x00000004&(data))>>2)
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_done_ie_shift                               (1)
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_done_ie_mask                                (0x00000002)
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_done_ie(data)                               (0x00000002&((data)<<1))
#define CABAC_P2_CABACP2_INT_EN_cabac_p2_done_ie_src(data)                           ((0x00000002&(data))>>1)
#define CABAC_P2_CABACP2_INT_EN_get_cabac_p2_done_ie(data)                           ((0x00000002&(data))>>1)
#define CABAC_P2_CABACP2_INT_EN_write_data_shift                                     (0)
#define CABAC_P2_CABACP2_INT_EN_write_data_mask                                      (0x00000001)
#define CABAC_P2_CABACP2_INT_EN_write_data(data)                                     (0x00000001&((data)<<0))
#define CABAC_P2_CABACP2_INT_EN_write_data_src(data)                                 ((0x00000001&(data))>>0)
#define CABAC_P2_CABACP2_INT_EN_get_write_data(data)                                 ((0x00000001&(data))>>0)


#define CABAC_P2_CABAC_P2_CNTL5                                                      0x1800E3DC
#define CABAC_P2_CABAC_P2_CNTL5_reg_addr                                             "0xB800E3DC"
#define CABAC_P2_CABAC_P2_CNTL5_reg                                                  0xB800E3DC
#define set_CABAC_P2_CABAC_P2_CNTL5_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_P2_CNTL5_reg)=data)
#define get_CABAC_P2_CABAC_P2_CNTL5_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_P2_CNTL5_reg))
#define CABAC_P2_CABAC_P2_CNTL5_inst_adr                                             "0x00F7"
#define CABAC_P2_CABAC_P2_CNTL5_inst                                                 0x00F7
#define CABAC_P2_CABAC_P2_CNTL5_write_enable3_shift                                  (26)
#define CABAC_P2_CABAC_P2_CNTL5_write_enable3_mask                                   (0x04000000)
#define CABAC_P2_CABAC_P2_CNTL5_write_enable3(data)                                  (0x04000000&((data)<<26))
#define CABAC_P2_CABAC_P2_CNTL5_write_enable3_src(data)                              ((0x04000000&(data))>>26)
#define CABAC_P2_CABAC_P2_CNTL5_get_write_enable3(data)                              ((0x04000000&(data))>>26)
#define CABAC_P2_CABAC_P2_CNTL5_coding_type_shift                                    (22)
#define CABAC_P2_CABAC_P2_CNTL5_coding_type_mask                                     (0x03C00000)
#define CABAC_P2_CABAC_P2_CNTL5_coding_type(data)                                    (0x03C00000&((data)<<22))
#define CABAC_P2_CABAC_P2_CNTL5_coding_type_src(data)                                ((0x03C00000&(data))>>22)
#define CABAC_P2_CABAC_P2_CNTL5_get_coding_type(data)                                ((0x03C00000&(data))>>22)
#define CABAC_P2_CABAC_P2_CNTL5_write_enable2_shift                                  (21)
#define CABAC_P2_CABAC_P2_CNTL5_write_enable2_mask                                   (0x00200000)
#define CABAC_P2_CABAC_P2_CNTL5_write_enable2(data)                                  (0x00200000&((data)<<21))
#define CABAC_P2_CABAC_P2_CNTL5_write_enable2_src(data)                              ((0x00200000&(data))>>21)
#define CABAC_P2_CABAC_P2_CNTL5_get_write_enable2(data)                              ((0x00200000&(data))>>21)
#define CABAC_P2_CABAC_P2_CNTL5_cabacp2_pred_counter_shift                           (11)
#define CABAC_P2_CABAC_P2_CNTL5_cabacp2_pred_counter_mask                            (0x001FF800)
#define CABAC_P2_CABAC_P2_CNTL5_cabacp2_pred_counter(data)                           (0x001FF800&((data)<<11))
#define CABAC_P2_CABAC_P2_CNTL5_cabacp2_pred_counter_src(data)                       ((0x001FF800&(data))>>11)
#define CABAC_P2_CABAC_P2_CNTL5_get_cabacp2_pred_counter(data)                       ((0x001FF800&(data))>>11)
#define CABAC_P2_CABAC_P2_CNTL5_write_enable1_shift                                  (10)
#define CABAC_P2_CABAC_P2_CNTL5_write_enable1_mask                                   (0x00000400)
#define CABAC_P2_CABAC_P2_CNTL5_write_enable1(data)                                  (0x00000400&((data)<<10))
#define CABAC_P2_CABAC_P2_CNTL5_write_enable1_src(data)                              ((0x00000400&(data))>>10)
#define CABAC_P2_CABAC_P2_CNTL5_get_write_enable1(data)                              ((0x00000400&(data))>>10)
#define CABAC_P2_CABAC_P2_CNTL5_cabacp2_curmb_addr_shift                             (0)
#define CABAC_P2_CABAC_P2_CNTL5_cabacp2_curmb_addr_mask                              (0x000003FF)
#define CABAC_P2_CABAC_P2_CNTL5_cabacp2_curmb_addr(data)                             (0x000003FF&((data)<<0))
#define CABAC_P2_CABAC_P2_CNTL5_cabacp2_curmb_addr_src(data)                         ((0x000003FF&(data))>>0)
#define CABAC_P2_CABAC_P2_CNTL5_get_cabacp2_curmb_addr(data)                         ((0x000003FF&(data))>>0)


#define CABAC_P2_P2_BSCNTL                                                           0x1800E3E0
#define CABAC_P2_P2_BSCNTL_reg_addr                                                  "0xB800E3E0"
#define CABAC_P2_P2_BSCNTL_reg                                                       0xB800E3E0
#define set_CABAC_P2_P2_BSCNTL_reg(data)   (*((volatile unsigned int*) CABAC_P2_P2_BSCNTL_reg)=data)
#define get_CABAC_P2_P2_BSCNTL_reg   (*((volatile unsigned int*) CABAC_P2_P2_BSCNTL_reg))
#define CABAC_P2_P2_BSCNTL_inst_adr                                                  "0x00F8"
#define CABAC_P2_P2_BSCNTL_inst                                                      0x00F8
#define CABAC_P2_P2_BSCNTL_write_enable3_shift                                       (6)
#define CABAC_P2_P2_BSCNTL_write_enable3_mask                                        (0x00000040)
#define CABAC_P2_P2_BSCNTL_write_enable3(data)                                       (0x00000040&((data)<<6))
#define CABAC_P2_P2_BSCNTL_write_enable3_src(data)                                   ((0x00000040&(data))>>6)
#define CABAC_P2_P2_BSCNTL_get_write_enable3(data)                                   ((0x00000040&(data))>>6)
#define CABAC_P2_P2_BSCNTL_p2_startcode_prevnt_en_shift                              (5)
#define CABAC_P2_P2_BSCNTL_p2_startcode_prevnt_en_mask                               (0x00000020)
#define CABAC_P2_P2_BSCNTL_p2_startcode_prevnt_en(data)                              (0x00000020&((data)<<5))
#define CABAC_P2_P2_BSCNTL_p2_startcode_prevnt_en_src(data)                          ((0x00000020&(data))>>5)
#define CABAC_P2_P2_BSCNTL_get_p2_startcode_prevnt_en(data)                          ((0x00000020&(data))>>5)
#define CABAC_P2_P2_BSCNTL_write_enable2_shift                                       (4)
#define CABAC_P2_P2_BSCNTL_write_enable2_mask                                        (0x00000010)
#define CABAC_P2_P2_BSCNTL_write_enable2(data)                                       (0x00000010&((data)<<4))
#define CABAC_P2_P2_BSCNTL_write_enable2_src(data)                                   ((0x00000010&(data))>>4)
#define CABAC_P2_P2_BSCNTL_get_write_enable2(data)                                   ((0x00000010&(data))>>4)
#define CABAC_P2_P2_BSCNTL_detect_startcode_error_shift                              (3)
#define CABAC_P2_P2_BSCNTL_detect_startcode_error_mask                               (0x00000008)
#define CABAC_P2_P2_BSCNTL_detect_startcode_error(data)                              (0x00000008&((data)<<3))
#define CABAC_P2_P2_BSCNTL_detect_startcode_error_src(data)                          ((0x00000008&(data))>>3)
#define CABAC_P2_P2_BSCNTL_get_detect_startcode_error(data)                          ((0x00000008&(data))>>3)
#define CABAC_P2_P2_BSCNTL_write_enable1_shift                                       (2)
#define CABAC_P2_P2_BSCNTL_write_enable1_mask                                        (0x00000004)
#define CABAC_P2_P2_BSCNTL_write_enable1(data)                                       (0x00000004&((data)<<2))
#define CABAC_P2_P2_BSCNTL_write_enable1_src(data)                                   ((0x00000004&(data))>>2)
#define CABAC_P2_P2_BSCNTL_get_write_enable1(data)                                   ((0x00000004&(data))>>2)
#define CABAC_P2_P2_BSCNTL_min_xfer_size_shift                                       (0)
#define CABAC_P2_P2_BSCNTL_min_xfer_size_mask                                        (0x00000003)
#define CABAC_P2_P2_BSCNTL_min_xfer_size(data)                                       (0x00000003&((data)<<0))
#define CABAC_P2_P2_BSCNTL_min_xfer_size_src(data)                                   ((0x00000003&(data))>>0)
#define CABAC_P2_P2_BSCNTL_get_min_xfer_size(data)                                   ((0x00000003&(data))>>0)


#define CABAC_P2_P2_BS_MIN_THR                                                       0x1800E3E4
#define CABAC_P2_P2_BS_MIN_THR_reg_addr                                              "0xB800E3E4"
#define CABAC_P2_P2_BS_MIN_THR_reg                                                   0xB800E3E4
#define set_CABAC_P2_P2_BS_MIN_THR_reg(data)   (*((volatile unsigned int*) CABAC_P2_P2_BS_MIN_THR_reg)=data)
#define get_CABAC_P2_P2_BS_MIN_THR_reg   (*((volatile unsigned int*) CABAC_P2_P2_BS_MIN_THR_reg))
#define CABAC_P2_P2_BS_MIN_THR_inst_adr                                              "0x00F9"
#define CABAC_P2_P2_BS_MIN_THR_inst                                                  0x00F9
#define CABAC_P2_P2_BS_MIN_THR_min_thre_shift                                        (0)
#define CABAC_P2_P2_BS_MIN_THR_min_thre_mask                                         (0x0000007F)
#define CABAC_P2_P2_BS_MIN_THR_min_thre(data)                                        (0x0000007F&((data)<<0))
#define CABAC_P2_P2_BS_MIN_THR_min_thre_src(data)                                    ((0x0000007F&(data))>>0)
#define CABAC_P2_P2_BS_MIN_THR_get_min_thre(data)                                    ((0x0000007F&(data))>>0)


#define CABAC_P2_P2_BSTIMER                                                          0x1800E3E8
#define CABAC_P2_P2_BSTIMER_reg_addr                                                 "0xB800E3E8"
#define CABAC_P2_P2_BSTIMER_reg                                                      0xB800E3E8
#define set_CABAC_P2_P2_BSTIMER_reg(data)   (*((volatile unsigned int*) CABAC_P2_P2_BSTIMER_reg)=data)
#define get_CABAC_P2_P2_BSTIMER_reg   (*((volatile unsigned int*) CABAC_P2_P2_BSTIMER_reg))
#define CABAC_P2_P2_BSTIMER_inst_adr                                                 "0x00FA"
#define CABAC_P2_P2_BSTIMER_inst                                                     0x00FA
#define CABAC_P2_P2_BSTIMER_timer_value_shift                                        (0)
#define CABAC_P2_P2_BSTIMER_timer_value_mask                                         (0x00FFFFFF)
#define CABAC_P2_P2_BSTIMER_timer_value(data)                                        (0x00FFFFFF&((data)<<0))
#define CABAC_P2_P2_BSTIMER_timer_value_src(data)                                    ((0x00FFFFFF&(data))>>0)
#define CABAC_P2_P2_BSTIMER_get_timer_value(data)                                    ((0x00FFFFFF&(data))>>0)


#define CABAC_P2_P2_RFIFO_BASE                                                       0x1800E364
#define CABAC_P2_P2_RFIFO_BASE_reg_addr                                              "0xB800E364"
#define CABAC_P2_P2_RFIFO_BASE_reg                                                   0xB800E364
#define set_CABAC_P2_P2_RFIFO_BASE_reg(data)   (*((volatile unsigned int*) CABAC_P2_P2_RFIFO_BASE_reg)=data)
#define get_CABAC_P2_P2_RFIFO_BASE_reg   (*((volatile unsigned int*) CABAC_P2_P2_RFIFO_BASE_reg))
#define CABAC_P2_P2_RFIFO_BASE_inst_adr                                              "0x00D9"
#define CABAC_P2_P2_RFIFO_BASE_inst                                                  0x00D9
#define CABAC_P2_P2_RFIFO_BASE_base_addr_shift                                       (0)
#define CABAC_P2_P2_RFIFO_BASE_base_addr_mask                                        (0x7FFFFFFF)
#define CABAC_P2_P2_RFIFO_BASE_base_addr(data)                                       (0x7FFFFFFF&((data)<<0))
#define CABAC_P2_P2_RFIFO_BASE_base_addr_src(data)                                   ((0x7FFFFFFF&(data))>>0)
#define CABAC_P2_P2_RFIFO_BASE_get_base_addr(data)                                   ((0x7FFFFFFF&(data))>>0)


#define CABAC_P2_P2_RFIFO_LIMIT                                                      0x1800E368
#define CABAC_P2_P2_RFIFO_LIMIT_reg_addr                                             "0xB800E368"
#define CABAC_P2_P2_RFIFO_LIMIT_reg                                                  0xB800E368
#define set_CABAC_P2_P2_RFIFO_LIMIT_reg(data)   (*((volatile unsigned int*) CABAC_P2_P2_RFIFO_LIMIT_reg)=data)
#define get_CABAC_P2_P2_RFIFO_LIMIT_reg   (*((volatile unsigned int*) CABAC_P2_P2_RFIFO_LIMIT_reg))
#define CABAC_P2_P2_RFIFO_LIMIT_inst_adr                                             "0x00DA"
#define CABAC_P2_P2_RFIFO_LIMIT_inst                                                 0x00DA
#define CABAC_P2_P2_RFIFO_LIMIT_limit_addr_shift                                     (0)
#define CABAC_P2_P2_RFIFO_LIMIT_limit_addr_mask                                      (0x7FFFFFFF)
#define CABAC_P2_P2_RFIFO_LIMIT_limit_addr(data)                                     (0x7FFFFFFF&((data)<<0))
#define CABAC_P2_P2_RFIFO_LIMIT_limit_addr_src(data)                                 ((0x7FFFFFFF&(data))>>0)
#define CABAC_P2_P2_RFIFO_LIMIT_get_limit_addr(data)                                 ((0x7FFFFFFF&(data))>>0)


#define CABAC_P2_P2_RFIFO_WPTR                                                       0x1800E36C
#define CABAC_P2_P2_RFIFO_WPTR_reg_addr                                              "0xB800E36C"
#define CABAC_P2_P2_RFIFO_WPTR_reg                                                   0xB800E36C
#define set_CABAC_P2_P2_RFIFO_WPTR_reg(data)   (*((volatile unsigned int*) CABAC_P2_P2_RFIFO_WPTR_reg)=data)
#define get_CABAC_P2_P2_RFIFO_WPTR_reg   (*((volatile unsigned int*) CABAC_P2_P2_RFIFO_WPTR_reg))
#define CABAC_P2_P2_RFIFO_WPTR_inst_adr                                              "0x00DB"
#define CABAC_P2_P2_RFIFO_WPTR_inst                                                  0x00DB
#define CABAC_P2_P2_RFIFO_WPTR_wr_ptr_shift                                          (0)
#define CABAC_P2_P2_RFIFO_WPTR_wr_ptr_mask                                           (0x7FFFFFFF)
#define CABAC_P2_P2_RFIFO_WPTR_wr_ptr(data)                                          (0x7FFFFFFF&((data)<<0))
#define CABAC_P2_P2_RFIFO_WPTR_wr_ptr_src(data)                                      ((0x7FFFFFFF&(data))>>0)
#define CABAC_P2_P2_RFIFO_WPTR_get_wr_ptr(data)                                      ((0x7FFFFFFF&(data))>>0)


#define CABAC_P2_P2_RFIFO_RPTR                                                       0x1800E370
#define CABAC_P2_P2_RFIFO_RPTR_reg_addr                                              "0xB800E370"
#define CABAC_P2_P2_RFIFO_RPTR_reg                                                   0xB800E370
#define set_CABAC_P2_P2_RFIFO_RPTR_reg(data)   (*((volatile unsigned int*) CABAC_P2_P2_RFIFO_RPTR_reg)=data)
#define get_CABAC_P2_P2_RFIFO_RPTR_reg   (*((volatile unsigned int*) CABAC_P2_P2_RFIFO_RPTR_reg))
#define CABAC_P2_P2_RFIFO_RPTR_inst_adr                                              "0x00DC"
#define CABAC_P2_P2_RFIFO_RPTR_inst                                                  0x00DC
#define CABAC_P2_P2_RFIFO_RPTR_rd_ptr_shift                                          (0)
#define CABAC_P2_P2_RFIFO_RPTR_rd_ptr_mask                                           (0x7FFFFFFF)
#define CABAC_P2_P2_RFIFO_RPTR_rd_ptr(data)                                          (0x7FFFFFFF&((data)<<0))
#define CABAC_P2_P2_RFIFO_RPTR_rd_ptr_src(data)                                      ((0x7FFFFFFF&(data))>>0)
#define CABAC_P2_P2_RFIFO_RPTR_get_rd_ptr(data)                                      ((0x7FFFFFFF&(data))>>0)


#define CABAC_P2_P2_WFIFO_BASE                                                       0x1800E374
#define CABAC_P2_P2_WFIFO_BASE_reg_addr                                              "0xB800E374"
#define CABAC_P2_P2_WFIFO_BASE_reg                                                   0xB800E374
#define set_CABAC_P2_P2_WFIFO_BASE_reg(data)   (*((volatile unsigned int*) CABAC_P2_P2_WFIFO_BASE_reg)=data)
#define get_CABAC_P2_P2_WFIFO_BASE_reg   (*((volatile unsigned int*) CABAC_P2_P2_WFIFO_BASE_reg))
#define CABAC_P2_P2_WFIFO_BASE_inst_adr                                              "0x00DD"
#define CABAC_P2_P2_WFIFO_BASE_inst                                                  0x00DD
#define CABAC_P2_P2_WFIFO_BASE_base_addr_shift                                       (0)
#define CABAC_P2_P2_WFIFO_BASE_base_addr_mask                                        (0x7FFFFFFF)
#define CABAC_P2_P2_WFIFO_BASE_base_addr(data)                                       (0x7FFFFFFF&((data)<<0))
#define CABAC_P2_P2_WFIFO_BASE_base_addr_src(data)                                   ((0x7FFFFFFF&(data))>>0)
#define CABAC_P2_P2_WFIFO_BASE_get_base_addr(data)                                   ((0x7FFFFFFF&(data))>>0)


#define CABAC_P2_P2_WFIFO_LIMIT                                                      0x1800E378
#define CABAC_P2_P2_WFIFO_LIMIT_reg_addr                                             "0xB800E378"
#define CABAC_P2_P2_WFIFO_LIMIT_reg                                                  0xB800E378
#define set_CABAC_P2_P2_WFIFO_LIMIT_reg(data)   (*((volatile unsigned int*) CABAC_P2_P2_WFIFO_LIMIT_reg)=data)
#define get_CABAC_P2_P2_WFIFO_LIMIT_reg   (*((volatile unsigned int*) CABAC_P2_P2_WFIFO_LIMIT_reg))
#define CABAC_P2_P2_WFIFO_LIMIT_inst_adr                                             "0x00DE"
#define CABAC_P2_P2_WFIFO_LIMIT_inst                                                 0x00DE
#define CABAC_P2_P2_WFIFO_LIMIT_limit_addr_shift                                     (0)
#define CABAC_P2_P2_WFIFO_LIMIT_limit_addr_mask                                      (0x7FFFFFFF)
#define CABAC_P2_P2_WFIFO_LIMIT_limit_addr(data)                                     (0x7FFFFFFF&((data)<<0))
#define CABAC_P2_P2_WFIFO_LIMIT_limit_addr_src(data)                                 ((0x7FFFFFFF&(data))>>0)
#define CABAC_P2_P2_WFIFO_LIMIT_get_limit_addr(data)                                 ((0x7FFFFFFF&(data))>>0)


#define CABAC_P2_P2_WFIFO_WPTR                                                       0x1800E37C
#define CABAC_P2_P2_WFIFO_WPTR_reg_addr                                              "0xB800E37C"
#define CABAC_P2_P2_WFIFO_WPTR_reg                                                   0xB800E37C
#define set_CABAC_P2_P2_WFIFO_WPTR_reg(data)   (*((volatile unsigned int*) CABAC_P2_P2_WFIFO_WPTR_reg)=data)
#define get_CABAC_P2_P2_WFIFO_WPTR_reg   (*((volatile unsigned int*) CABAC_P2_P2_WFIFO_WPTR_reg))
#define CABAC_P2_P2_WFIFO_WPTR_inst_adr                                              "0x00DF"
#define CABAC_P2_P2_WFIFO_WPTR_inst                                                  0x00DF
#define CABAC_P2_P2_WFIFO_WPTR_wr_ptr_shift                                          (0)
#define CABAC_P2_P2_WFIFO_WPTR_wr_ptr_mask                                           (0x7FFFFFFF)
#define CABAC_P2_P2_WFIFO_WPTR_wr_ptr(data)                                          (0x7FFFFFFF&((data)<<0))
#define CABAC_P2_P2_WFIFO_WPTR_wr_ptr_src(data)                                      ((0x7FFFFFFF&(data))>>0)
#define CABAC_P2_P2_WFIFO_WPTR_get_wr_ptr(data)                                      ((0x7FFFFFFF&(data))>>0)


#define CABAC_P2_P2_WFIFO_RPTR                                                       0x1800E380
#define CABAC_P2_P2_WFIFO_RPTR_reg_addr                                              "0xB800E380"
#define CABAC_P2_P2_WFIFO_RPTR_reg                                                   0xB800E380
#define set_CABAC_P2_P2_WFIFO_RPTR_reg(data)   (*((volatile unsigned int*) CABAC_P2_P2_WFIFO_RPTR_reg)=data)
#define get_CABAC_P2_P2_WFIFO_RPTR_reg   (*((volatile unsigned int*) CABAC_P2_P2_WFIFO_RPTR_reg))
#define CABAC_P2_P2_WFIFO_RPTR_inst_adr                                              "0x00E0"
#define CABAC_P2_P2_WFIFO_RPTR_inst                                                  0x00E0
#define CABAC_P2_P2_WFIFO_RPTR_rd_ptr_shift                                          (0)
#define CABAC_P2_P2_WFIFO_RPTR_rd_ptr_mask                                           (0x7FFFFFFF)
#define CABAC_P2_P2_WFIFO_RPTR_rd_ptr(data)                                          (0x7FFFFFFF&((data)<<0))
#define CABAC_P2_P2_WFIFO_RPTR_rd_ptr_src(data)                                      ((0x7FFFFFFF&(data))>>0)
#define CABAC_P2_P2_WFIFO_RPTR_get_rd_ptr(data)                                      ((0x7FFFFFFF&(data))>>0)


#define CABAC_P2_P2_RFIFO_DECBSPTR                                                   0x1800E384
#define CABAC_P2_P2_RFIFO_DECBSPTR_reg_addr                                          "0xB800E384"
#define CABAC_P2_P2_RFIFO_DECBSPTR_reg                                               0xB800E384
#define set_CABAC_P2_P2_RFIFO_DECBSPTR_reg(data)   (*((volatile unsigned int*) CABAC_P2_P2_RFIFO_DECBSPTR_reg)=data)
#define get_CABAC_P2_P2_RFIFO_DECBSPTR_reg   (*((volatile unsigned int*) CABAC_P2_P2_RFIFO_DECBSPTR_reg))
#define CABAC_P2_P2_RFIFO_DECBSPTR_inst_adr                                          "0x00E1"
#define CABAC_P2_P2_RFIFO_DECBSPTR_inst                                              0x00E1
#define CABAC_P2_P2_RFIFO_DECBSPTR_dec_bit_ptr_shift                                 (0)
#define CABAC_P2_P2_RFIFO_DECBSPTR_dec_bit_ptr_mask                                  (0xFFFFFFFF)
#define CABAC_P2_P2_RFIFO_DECBSPTR_dec_bit_ptr(data)                                 (0xFFFFFFFF&((data)<<0))
#define CABAC_P2_P2_RFIFO_DECBSPTR_dec_bit_ptr_src(data)                             ((0xFFFFFFFF&(data))>>0)
#define CABAC_P2_P2_RFIFO_DECBSPTR_get_dec_bit_ptr(data)                             ((0xFFFFFFFF&(data))>>0)


#define CABAC_P2_P2_RFIFO_DECBSPTR_MSB                                               0x1800E24C
#define CABAC_P2_P2_RFIFO_DECBSPTR_MSB_reg_addr                                      "0xB800E24C"
#define CABAC_P2_P2_RFIFO_DECBSPTR_MSB_reg                                           0xB800E24C
#define set_CABAC_P2_P2_RFIFO_DECBSPTR_MSB_reg(data)   (*((volatile unsigned int*) CABAC_P2_P2_RFIFO_DECBSPTR_MSB_reg)=data)
#define get_CABAC_P2_P2_RFIFO_DECBSPTR_MSB_reg   (*((volatile unsigned int*) CABAC_P2_P2_RFIFO_DECBSPTR_MSB_reg))
#define CABAC_P2_P2_RFIFO_DECBSPTR_MSB_inst_adr                                      "0x0093"
#define CABAC_P2_P2_RFIFO_DECBSPTR_MSB_inst                                          0x0093
#define CABAC_P2_P2_RFIFO_DECBSPTR_MSB_dec_bit_ptr_msb_shift                         (0)
#define CABAC_P2_P2_RFIFO_DECBSPTR_MSB_dec_bit_ptr_msb_mask                          (0x00000003)
#define CABAC_P2_P2_RFIFO_DECBSPTR_MSB_dec_bit_ptr_msb(data)                         (0x00000003&((data)<<0))
#define CABAC_P2_P2_RFIFO_DECBSPTR_MSB_dec_bit_ptr_msb_src(data)                     ((0x00000003&(data))>>0)
#define CABAC_P2_P2_RFIFO_DECBSPTR_MSB_get_dec_bit_ptr_msb(data)                     ((0x00000003&(data))>>0)


#define CABAC_P2_CABAC_P2_CNTL                                                       0x1800E388
#define CABAC_P2_CABAC_P2_CNTL_reg_addr                                              "0xB800E388"
#define CABAC_P2_CABAC_P2_CNTL_reg                                                   0xB800E388
#define set_CABAC_P2_CABAC_P2_CNTL_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_P2_CNTL_reg)=data)
#define get_CABAC_P2_CABAC_P2_CNTL_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_P2_CNTL_reg))
#define CABAC_P2_CABAC_P2_CNTL_inst_adr                                              "0x00E2"
#define CABAC_P2_CABAC_P2_CNTL_inst                                                  0x00E2
#define CABAC_P2_CABAC_P2_CNTL_entropy_coding_mode_shift                             (28)
#define CABAC_P2_CABAC_P2_CNTL_entropy_coding_mode_mask                              (0x10000000)
#define CABAC_P2_CABAC_P2_CNTL_entropy_coding_mode(data)                             (0x10000000&((data)<<28))
#define CABAC_P2_CABAC_P2_CNTL_entropy_coding_mode_src(data)                         ((0x10000000&(data))>>28)
#define CABAC_P2_CABAC_P2_CNTL_get_entropy_coding_mode(data)                         ((0x10000000&(data))>>28)
#define CABAC_P2_CABAC_P2_CNTL_pic_init_qp_shift                                     (22)
#define CABAC_P2_CABAC_P2_CNTL_pic_init_qp_mask                                      (0x0FC00000)
#define CABAC_P2_CABAC_P2_CNTL_pic_init_qp(data)                                     (0x0FC00000&((data)<<22))
#define CABAC_P2_CABAC_P2_CNTL_pic_init_qp_src(data)                                 ((0x0FC00000&(data))>>22)
#define CABAC_P2_CABAC_P2_CNTL_get_pic_init_qp(data)                                 ((0x0FC00000&(data))>>22)
#define CABAC_P2_CABAC_P2_CNTL_chroma_qp_offset_shift                                (17)
#define CABAC_P2_CABAC_P2_CNTL_chroma_qp_offset_mask                                 (0x003E0000)
#define CABAC_P2_CABAC_P2_CNTL_chroma_qp_offset(data)                                (0x003E0000&((data)<<17))
#define CABAC_P2_CABAC_P2_CNTL_chroma_qp_offset_src(data)                            ((0x003E0000&(data))>>17)
#define CABAC_P2_CABAC_P2_CNTL_get_chroma_qp_offset(data)                            ((0x003E0000&(data))>>17)
#define CABAC_P2_CABAC_P2_CNTL_second_chroma_qp_offset_shift                         (12)
#define CABAC_P2_CABAC_P2_CNTL_second_chroma_qp_offset_mask                          (0x0001F000)
#define CABAC_P2_CABAC_P2_CNTL_second_chroma_qp_offset(data)                         (0x0001F000&((data)<<12))
#define CABAC_P2_CABAC_P2_CNTL_second_chroma_qp_offset_src(data)                     ((0x0001F000&(data))>>12)
#define CABAC_P2_CABAC_P2_CNTL_get_second_chroma_qp_offset(data)                     ((0x0001F000&(data))>>12)
#define CABAC_P2_CABAC_P2_CNTL_direct_8x8_inferflg_shift                             (11)
#define CABAC_P2_CABAC_P2_CNTL_direct_8x8_inferflg_mask                              (0x00000800)
#define CABAC_P2_CABAC_P2_CNTL_direct_8x8_inferflg(data)                             (0x00000800&((data)<<11))
#define CABAC_P2_CABAC_P2_CNTL_direct_8x8_inferflg_src(data)                         ((0x00000800&(data))>>11)
#define CABAC_P2_CABAC_P2_CNTL_get_direct_8x8_inferflg(data)                         ((0x00000800&(data))>>11)
#define CABAC_P2_CABAC_P2_CNTL_transform_8x8_mode_flg_shift                          (10)
#define CABAC_P2_CABAC_P2_CNTL_transform_8x8_mode_flg_mask                           (0x00000400)
#define CABAC_P2_CABAC_P2_CNTL_transform_8x8_mode_flg(data)                          (0x00000400&((data)<<10))
#define CABAC_P2_CABAC_P2_CNTL_transform_8x8_mode_flg_src(data)                      ((0x00000400&(data))>>10)
#define CABAC_P2_CABAC_P2_CNTL_get_transform_8x8_mode_flg(data)                      ((0x00000400&(data))>>10)
#define CABAC_P2_CABAC_P2_CNTL_num_ref_idx_l0_active_minus1_shift                    (5)
#define CABAC_P2_CABAC_P2_CNTL_num_ref_idx_l0_active_minus1_mask                     (0x000003E0)
#define CABAC_P2_CABAC_P2_CNTL_num_ref_idx_l0_active_minus1(data)                    (0x000003E0&((data)<<5))
#define CABAC_P2_CABAC_P2_CNTL_num_ref_idx_l0_active_minus1_src(data)                ((0x000003E0&(data))>>5)
#define CABAC_P2_CABAC_P2_CNTL_get_num_ref_idx_l0_active_minus1(data)                ((0x000003E0&(data))>>5)
#define CABAC_P2_CABAC_P2_CNTL_num_ref_idx_l1_active_minus1_shift                    (0)
#define CABAC_P2_CABAC_P2_CNTL_num_ref_idx_l1_active_minus1_mask                     (0x0000001F)
#define CABAC_P2_CABAC_P2_CNTL_num_ref_idx_l1_active_minus1(data)                    (0x0000001F&((data)<<0))
#define CABAC_P2_CABAC_P2_CNTL_num_ref_idx_l1_active_minus1_src(data)                ((0x0000001F&(data))>>0)
#define CABAC_P2_CABAC_P2_CNTL_get_num_ref_idx_l1_active_minus1(data)                ((0x0000001F&(data))>>0)


#define CABAC_P2_CABAC_P2_CNTL2                                                      0x1800E38C
#define CABAC_P2_CABAC_P2_CNTL2_reg_addr                                             "0xB800E38C"
#define CABAC_P2_CABAC_P2_CNTL2_reg                                                  0xB800E38C
#define set_CABAC_P2_CABAC_P2_CNTL2_reg(data)   (*((volatile unsigned int*) CABAC_P2_CABAC_P2_CNTL2_reg)=data)
#define get_CABAC_P2_CABAC_P2_CNTL2_reg   (*((volatile unsigned int*) CABAC_P2_CABAC_P2_CNTL2_reg))
#define CABAC_P2_CABAC_P2_CNTL2_inst_adr                                             "0x00E3"
#define CABAC_P2_CABAC_P2_CNTL2_inst                                                 0x00E3
#define CABAC_P2_CABAC_P2_CNTL2_write_enable7_shift                                  (31)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable7_mask                                   (0x80000000)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable7(data)                                  (0x80000000&((data)<<31))
#define CABAC_P2_CABAC_P2_CNTL2_write_enable7_src(data)                              ((0x80000000&(data))>>31)
#define CABAC_P2_CABAC_P2_CNTL2_get_write_enable7(data)                              ((0x80000000&(data))>>31)
#define CABAC_P2_CABAC_P2_CNTL2_mb_adaptive_frame_field_flag_shift                   (30)
#define CABAC_P2_CABAC_P2_CNTL2_mb_adaptive_frame_field_flag_mask                    (0x40000000)
#define CABAC_P2_CABAC_P2_CNTL2_mb_adaptive_frame_field_flag(data)                   (0x40000000&((data)<<30))
#define CABAC_P2_CABAC_P2_CNTL2_mb_adaptive_frame_field_flag_src(data)               ((0x40000000&(data))>>30)
#define CABAC_P2_CABAC_P2_CNTL2_get_mb_adaptive_frame_field_flag(data)               ((0x40000000&(data))>>30)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable6_shift                                  (29)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable6_mask                                   (0x20000000)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable6(data)                                  (0x20000000&((data)<<29))
#define CABAC_P2_CABAC_P2_CNTL2_write_enable6_src(data)                              ((0x20000000&(data))>>29)
#define CABAC_P2_CABAC_P2_CNTL2_get_write_enable6(data)                              ((0x20000000&(data))>>29)
#define CABAC_P2_CABAC_P2_CNTL2_picmb_w_shift                                        (19)
#define CABAC_P2_CABAC_P2_CNTL2_picmb_w_mask                                         (0x1FF80000)
#define CABAC_P2_CABAC_P2_CNTL2_picmb_w(data)                                        (0x1FF80000&((data)<<19))
#define CABAC_P2_CABAC_P2_CNTL2_picmb_w_src(data)                                    ((0x1FF80000&(data))>>19)
#define CABAC_P2_CABAC_P2_CNTL2_get_picmb_w(data)                                    ((0x1FF80000&(data))>>19)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable5_shift                                  (18)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable5_mask                                   (0x00040000)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable5(data)                                  (0x00040000&((data)<<18))
#define CABAC_P2_CABAC_P2_CNTL2_write_enable5_src(data)                              ((0x00040000&(data))>>18)
#define CABAC_P2_CABAC_P2_CNTL2_get_write_enable5(data)                              ((0x00040000&(data))>>18)
#define CABAC_P2_CABAC_P2_CNTL2_monochrome_shift                                     (17)
#define CABAC_P2_CABAC_P2_CNTL2_monochrome_mask                                      (0x00020000)
#define CABAC_P2_CABAC_P2_CNTL2_monochrome(data)                                     (0x00020000&((data)<<17))
#define CABAC_P2_CABAC_P2_CNTL2_monochrome_src(data)                                 ((0x00020000&(data))>>17)
#define CABAC_P2_CABAC_P2_CNTL2_get_monochrome(data)                                 ((0x00020000&(data))>>17)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable4_shift                                  (16)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable4_mask                                   (0x00010000)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable4(data)                                  (0x00010000&((data)<<16))
#define CABAC_P2_CABAC_P2_CNTL2_write_enable4_src(data)                              ((0x00010000&(data))>>16)
#define CABAC_P2_CABAC_P2_CNTL2_get_write_enable4(data)                              ((0x00010000&(data))>>16)
#define CABAC_P2_CABAC_P2_CNTL2_field_pic_flag_shift                                 (15)
#define CABAC_P2_CABAC_P2_CNTL2_field_pic_flag_mask                                  (0x00008000)
#define CABAC_P2_CABAC_P2_CNTL2_field_pic_flag(data)                                 (0x00008000&((data)<<15))
#define CABAC_P2_CABAC_P2_CNTL2_field_pic_flag_src(data)                             ((0x00008000&(data))>>15)
#define CABAC_P2_CABAC_P2_CNTL2_get_field_pic_flag(data)                             ((0x00008000&(data))>>15)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable3_shift                                  (14)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable3_mask                                   (0x00004000)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable3(data)                                  (0x00004000&((data)<<14))
#define CABAC_P2_CABAC_P2_CNTL2_write_enable3_src(data)                              ((0x00004000&(data))>>14)
#define CABAC_P2_CABAC_P2_CNTL2_get_write_enable3(data)                              ((0x00004000&(data))>>14)
#define CABAC_P2_CABAC_P2_CNTL2_pic_type_shift                                       (11)
#define CABAC_P2_CABAC_P2_CNTL2_pic_type_mask                                        (0x00003800)
#define CABAC_P2_CABAC_P2_CNTL2_pic_type(data)                                       (0x00003800&((data)<<11))
#define CABAC_P2_CABAC_P2_CNTL2_pic_type_src(data)                                   ((0x00003800&(data))>>11)
#define CABAC_P2_CABAC_P2_CNTL2_get_pic_type(data)                                   ((0x00003800&(data))>>11)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable2_shift                                  (10)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable2_mask                                   (0x00000400)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable2(data)                                  (0x00000400&((data)<<10))
#define CABAC_P2_CABAC_P2_CNTL2_write_enable2_src(data)                              ((0x00000400&(data))>>10)
#define CABAC_P2_CABAC_P2_CNTL2_get_write_enable2(data)                              ((0x00000400&(data))>>10)
#define CABAC_P2_CABAC_P2_CNTL2_slice_qp_delta_shift                                 (3)
#define CABAC_P2_CABAC_P2_CNTL2_slice_qp_delta_mask                                  (0x000003F8)
#define CABAC_P2_CABAC_P2_CNTL2_slice_qp_delta(data)                                 (0x000003F8&((data)<<3))
#define CABAC_P2_CABAC_P2_CNTL2_slice_qp_delta_src(data)                             ((0x000003F8&(data))>>3)
#define CABAC_P2_CABAC_P2_CNTL2_get_slice_qp_delta(data)                             ((0x000003F8&(data))>>3)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable1_shift                                  (2)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable1_mask                                   (0x00000004)
#define CABAC_P2_CABAC_P2_CNTL2_write_enable1(data)                                  (0x00000004&((data)<<2))
#define CABAC_P2_CABAC_P2_CNTL2_write_enable1_src(data)                              ((0x00000004&(data))>>2)
#define CABAC_P2_CABAC_P2_CNTL2_get_write_enable1(data)                              ((0x00000004&(data))>>2)
#define CABAC_P2_CABAC_P2_CNTL2_cabac_init_idc_shift                                 (0)
#define CABAC_P2_CABAC_P2_CNTL2_cabac_init_idc_mask                                  (0x00000003)
#define CABAC_P2_CABAC_P2_CNTL2_cabac_init_idc(data)                                 (0x00000003&((data)<<0))
#define CABAC_P2_CABAC_P2_CNTL2_cabac_init_idc_src(data)                             ((0x00000003&(data))>>0)
#define CABAC_P2_CABAC_P2_CNTL2_get_cabac_init_idc(data)                             ((0x00000003&(data))>>0)


#define CABAC_P2_P2_NDB_CTL                                                          0x1800E3B8
#define CABAC_P2_P2_NDB_CTL_reg_addr                                                 "0xB800E3B8"
#define CABAC_P2_P2_NDB_CTL_reg                                                      0xB800E3B8
#define set_CABAC_P2_P2_NDB_CTL_reg(data)   (*((volatile unsigned int*) CABAC_P2_P2_NDB_CTL_reg)=data)
#define get_CABAC_P2_P2_NDB_CTL_reg   (*((volatile unsigned int*) CABAC_P2_P2_NDB_CTL_reg))
#define CABAC_P2_P2_NDB_CTL_inst_adr                                                 "0x00EE"
#define CABAC_P2_P2_NDB_CTL_inst                                                     0x00EE
#define CABAC_P2_P2_NDB_CTL_write_enable3_shift                                      (5)
#define CABAC_P2_P2_NDB_CTL_write_enable3_mask                                       (0x00000020)
#define CABAC_P2_P2_NDB_CTL_write_enable3(data)                                      (0x00000020&((data)<<5))
#define CABAC_P2_P2_NDB_CTL_write_enable3_src(data)                                  ((0x00000020&(data))>>5)
#define CABAC_P2_P2_NDB_CTL_get_write_enable3(data)                                  ((0x00000020&(data))>>5)
#define CABAC_P2_P2_NDB_CTL_cabac_halt_done_shift                                    (4)
#define CABAC_P2_P2_NDB_CTL_cabac_halt_done_mask                                     (0x00000010)
#define CABAC_P2_P2_NDB_CTL_cabac_halt_done(data)                                    (0x00000010&((data)<<4))
#define CABAC_P2_P2_NDB_CTL_cabac_halt_done_src(data)                                ((0x00000010&(data))>>4)
#define CABAC_P2_P2_NDB_CTL_get_cabac_halt_done(data)                                ((0x00000010&(data))>>4)
#define CABAC_P2_P2_NDB_CTL_write_enable2_shift                                      (3)
#define CABAC_P2_P2_NDB_CTL_write_enable2_mask                                       (0x00000008)
#define CABAC_P2_P2_NDB_CTL_write_enable2(data)                                      (0x00000008&((data)<<3))
#define CABAC_P2_P2_NDB_CTL_write_enable2_src(data)                                  ((0x00000008&(data))>>3)
#define CABAC_P2_P2_NDB_CTL_get_write_enable2(data)                                  ((0x00000008&(data))>>3)
#define CABAC_P2_P2_NDB_CTL_cabac_halt_shift                                         (2)
#define CABAC_P2_P2_NDB_CTL_cabac_halt_mask                                          (0x00000004)
#define CABAC_P2_P2_NDB_CTL_cabac_halt(data)                                         (0x00000004&((data)<<2))
#define CABAC_P2_P2_NDB_CTL_cabac_halt_src(data)                                     ((0x00000004&(data))>>2)
#define CABAC_P2_P2_NDB_CTL_get_cabac_halt(data)                                     ((0x00000004&(data))>>2)
#define CABAC_P2_P2_NDB_CTL_write_enable1_shift                                      (1)
#define CABAC_P2_P2_NDB_CTL_write_enable1_mask                                       (0x00000002)
#define CABAC_P2_P2_NDB_CTL_write_enable1(data)                                      (0x00000002&((data)<<1))
#define CABAC_P2_P2_NDB_CTL_write_enable1_src(data)                                  ((0x00000002&(data))>>1)
#define CABAC_P2_P2_NDB_CTL_get_write_enable1(data)                                  ((0x00000002&(data))>>1)
#define CABAC_P2_P2_NDB_CTL_postwrite_en_shift                                       (0)
#define CABAC_P2_P2_NDB_CTL_postwrite_en_mask                                        (0x00000001)
#define CABAC_P2_P2_NDB_CTL_postwrite_en(data)                                       (0x00000001&((data)<<0))
#define CABAC_P2_P2_NDB_CTL_postwrite_en_src(data)                                   ((0x00000001&(data))>>0)
#define CABAC_P2_P2_NDB_CTL_get_postwrite_en(data)                                   ((0x00000001&(data))>>0)


#define CABAC_P2_NDB_CABAC_BASE                                                      0x1800E394
#define CABAC_P2_NDB_CABAC_BASE_reg_addr                                             "0xB800E394"
#define CABAC_P2_NDB_CABAC_BASE_reg                                                  0xB800E394
#define set_CABAC_P2_NDB_CABAC_BASE_reg(data)   (*((volatile unsigned int*) CABAC_P2_NDB_CABAC_BASE_reg)=data)
#define get_CABAC_P2_NDB_CABAC_BASE_reg   (*((volatile unsigned int*) CABAC_P2_NDB_CABAC_BASE_reg))
#define CABAC_P2_NDB_CABAC_BASE_inst_adr                                             "0x00E5"
#define CABAC_P2_NDB_CABAC_BASE_inst                                                 0x00E5
#define CABAC_P2_NDB_CABAC_BASE_base_addr_shift                                      (0)
#define CABAC_P2_NDB_CABAC_BASE_base_addr_mask                                       (0x7FFFFFFF)
#define CABAC_P2_NDB_CABAC_BASE_base_addr(data)                                      (0x7FFFFFFF&((data)<<0))
#define CABAC_P2_NDB_CABAC_BASE_base_addr_src(data)                                  ((0x7FFFFFFF&(data))>>0)
#define CABAC_P2_NDB_CABAC_BASE_get_base_addr(data)                                  ((0x7FFFFFFF&(data))>>0)


#define CABAC_P2_NDB_CABAC_LIMIT                                                     0x1800E39C
#define CABAC_P2_NDB_CABAC_LIMIT_reg_addr                                            "0xB800E39C"
#define CABAC_P2_NDB_CABAC_LIMIT_reg                                                 0xB800E39C
#define set_CABAC_P2_NDB_CABAC_LIMIT_reg(data)   (*((volatile unsigned int*) CABAC_P2_NDB_CABAC_LIMIT_reg)=data)
#define get_CABAC_P2_NDB_CABAC_LIMIT_reg   (*((volatile unsigned int*) CABAC_P2_NDB_CABAC_LIMIT_reg))
#define CABAC_P2_NDB_CABAC_LIMIT_inst_adr                                            "0x00E7"
#define CABAC_P2_NDB_CABAC_LIMIT_inst                                                0x00E7
#define CABAC_P2_NDB_CABAC_LIMIT_limit_addr_shift                                    (0)
#define CABAC_P2_NDB_CABAC_LIMIT_limit_addr_mask                                     (0x7FFFFFFF)
#define CABAC_P2_NDB_CABAC_LIMIT_limit_addr(data)                                    (0x7FFFFFFF&((data)<<0))
#define CABAC_P2_NDB_CABAC_LIMIT_limit_addr_src(data)                                ((0x7FFFFFFF&(data))>>0)
#define CABAC_P2_NDB_CABAC_LIMIT_get_limit_addr(data)                                ((0x7FFFFFFF&(data))>>0)


#define CABAC_P2_NDB_CABAC_WPTR                                                      0x1800E3A0
#define CABAC_P2_NDB_CABAC_WPTR_reg_addr                                             "0xB800E3A0"
#define CABAC_P2_NDB_CABAC_WPTR_reg                                                  0xB800E3A0
#define set_CABAC_P2_NDB_CABAC_WPTR_reg(data)   (*((volatile unsigned int*) CABAC_P2_NDB_CABAC_WPTR_reg)=data)
#define get_CABAC_P2_NDB_CABAC_WPTR_reg   (*((volatile unsigned int*) CABAC_P2_NDB_CABAC_WPTR_reg))
#define CABAC_P2_NDB_CABAC_WPTR_inst_adr                                             "0x00E8"
#define CABAC_P2_NDB_CABAC_WPTR_inst                                                 0x00E8
#define CABAC_P2_NDB_CABAC_WPTR_wr_ptr_shift                                         (0)
#define CABAC_P2_NDB_CABAC_WPTR_wr_ptr_mask                                          (0x7FFFFFFF)
#define CABAC_P2_NDB_CABAC_WPTR_wr_ptr(data)                                         (0x7FFFFFFF&((data)<<0))
#define CABAC_P2_NDB_CABAC_WPTR_wr_ptr_src(data)                                     ((0x7FFFFFFF&(data))>>0)
#define CABAC_P2_NDB_CABAC_WPTR_get_wr_ptr(data)                                     ((0x7FFFFFFF&(data))>>0)


#define CABAC_P2_NDB_CABAC_RPTR                                                      0x1800E3A4
#define CABAC_P2_NDB_CABAC_RPTR_reg_addr                                             "0xB800E3A4"
#define CABAC_P2_NDB_CABAC_RPTR_reg                                                  0xB800E3A4
#define set_CABAC_P2_NDB_CABAC_RPTR_reg(data)   (*((volatile unsigned int*) CABAC_P2_NDB_CABAC_RPTR_reg)=data)
#define get_CABAC_P2_NDB_CABAC_RPTR_reg   (*((volatile unsigned int*) CABAC_P2_NDB_CABAC_RPTR_reg))
#define CABAC_P2_NDB_CABAC_RPTR_inst_adr                                             "0x00E9"
#define CABAC_P2_NDB_CABAC_RPTR_inst                                                 0x00E9
#define CABAC_P2_NDB_CABAC_RPTR_rd_ptr_shift                                         (0)
#define CABAC_P2_NDB_CABAC_RPTR_rd_ptr_mask                                          (0x7FFFFFFF)
#define CABAC_P2_NDB_CABAC_RPTR_rd_ptr(data)                                         (0x7FFFFFFF&((data)<<0))
#define CABAC_P2_NDB_CABAC_RPTR_rd_ptr_src(data)                                     ((0x7FFFFFFF&(data))>>0)
#define CABAC_P2_NDB_CABAC_RPTR_get_rd_ptr(data)                                     ((0x7FFFFFFF&(data))>>0)


#endif
