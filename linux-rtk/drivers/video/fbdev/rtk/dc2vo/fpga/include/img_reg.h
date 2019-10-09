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


#ifndef _IMG_REG_H_INCLUDED_
#define _IMG_REG_H_INCLUDED_
#ifdef  _IMG_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     dering_dbg_sel:3;
unsigned int     reserved_1:1;
unsigned int     dbg_group2_sel:5;
unsigned int     dbg_group1_sel:5;
unsigned int     dbg_out_en:1;
unsigned int     reserved_2:8;
}IMG_DBG_CNTL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     chroma_enable:1;
unsigned int     luma_enable:1;
}IMG_DERING_CNTL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     filt_prec:2;
}IMG_FILT_CNTL;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     init_value:10;
}IMG_FILT_INIT;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     rcrpr:1;
unsigned int     color_cr:8;
unsigned int     color_cb:8;
unsigned int     color_y:8;
unsigned int     fill_mode:2;
}IMG_RMRPR_CNTL;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     m:4;
unsigned int     pixel_offset:11;
}IMG_RMRPR_PAR;

typedef struct 
{
unsigned int     ax:32;
}IMG_RMRPR_AX;

typedef struct 
{
unsigned int     ay:32;
}IMG_RMRPR_AY;

typedef struct 
{
unsigned int     ax_inc:32;
}IMG_RMRPR_AXINC;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     picmb_h:6;
unsigned int     picmb_w:7;
}IMG_RMRPR_PICINFO;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     basea:10;
}IMG_BASEA;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     offseta:9;
}IMG_OFFSETA;

#endif

#define IMG_DBG_CNTL                                                                 0x1800ED00
#define IMG_DBG_CNTL_reg_addr                                                        "0xB800ED00"
#define IMG_DBG_CNTL_reg                                                             0xB800ED00
#define set_IMG_DBG_CNTL_reg(data)   (*((volatile unsigned int*) IMG_DBG_CNTL_reg)=data)
#define get_IMG_DBG_CNTL_reg   (*((volatile unsigned int*) IMG_DBG_CNTL_reg))
#define IMG_DBG_CNTL_inst_adr                                                        "0x0040"
#define IMG_DBG_CNTL_inst                                                            0x0040
#define IMG_DBG_CNTL_dering_dbg_sel_shift                                            (20)
#define IMG_DBG_CNTL_dering_dbg_sel_mask                                             (0x00700000)
#define IMG_DBG_CNTL_dering_dbg_sel(data)                                            (0x00700000&((data)<<20))
#define IMG_DBG_CNTL_dering_dbg_sel_src(data)                                        ((0x00700000&(data))>>20)
#define IMG_DBG_CNTL_get_dering_dbg_sel(data)                                        ((0x00700000&(data))>>20)
#define IMG_DBG_CNTL_dbg_group2_sel_shift                                            (14)
#define IMG_DBG_CNTL_dbg_group2_sel_mask                                             (0x0007C000)
#define IMG_DBG_CNTL_dbg_group2_sel(data)                                            (0x0007C000&((data)<<14))
#define IMG_DBG_CNTL_dbg_group2_sel_src(data)                                        ((0x0007C000&(data))>>14)
#define IMG_DBG_CNTL_get_dbg_group2_sel(data)                                        ((0x0007C000&(data))>>14)
#define IMG_DBG_CNTL_dbg_group1_sel_shift                                            (9)
#define IMG_DBG_CNTL_dbg_group1_sel_mask                                             (0x00003E00)
#define IMG_DBG_CNTL_dbg_group1_sel(data)                                            (0x00003E00&((data)<<9))
#define IMG_DBG_CNTL_dbg_group1_sel_src(data)                                        ((0x00003E00&(data))>>9)
#define IMG_DBG_CNTL_get_dbg_group1_sel(data)                                        ((0x00003E00&(data))>>9)
#define IMG_DBG_CNTL_dbg_out_en_shift                                                (8)
#define IMG_DBG_CNTL_dbg_out_en_mask                                                 (0x00000100)
#define IMG_DBG_CNTL_dbg_out_en(data)                                                (0x00000100&((data)<<8))
#define IMG_DBG_CNTL_dbg_out_en_src(data)                                            ((0x00000100&(data))>>8)
#define IMG_DBG_CNTL_get_dbg_out_en(data)                                            ((0x00000100&(data))>>8)


#define IMG_DERING_CNTL                                                              0x1800ED04
#define IMG_DERING_CNTL_reg_addr                                                     "0xB800ED04"
#define IMG_DERING_CNTL_reg                                                          0xB800ED04
#define set_IMG_DERING_CNTL_reg(data)   (*((volatile unsigned int*) IMG_DERING_CNTL_reg)=data)
#define get_IMG_DERING_CNTL_reg   (*((volatile unsigned int*) IMG_DERING_CNTL_reg))
#define IMG_DERING_CNTL_inst_adr                                                     "0x0041"
#define IMG_DERING_CNTL_inst                                                         0x0041
#define IMG_DERING_CNTL_chroma_enable_shift                                          (1)
#define IMG_DERING_CNTL_chroma_enable_mask                                           (0x00000002)
#define IMG_DERING_CNTL_chroma_enable(data)                                          (0x00000002&((data)<<1))
#define IMG_DERING_CNTL_chroma_enable_src(data)                                      ((0x00000002&(data))>>1)
#define IMG_DERING_CNTL_get_chroma_enable(data)                                      ((0x00000002&(data))>>1)
#define IMG_DERING_CNTL_luma_enable_shift                                            (0)
#define IMG_DERING_CNTL_luma_enable_mask                                             (0x00000001)
#define IMG_DERING_CNTL_luma_enable(data)                                            (0x00000001&((data)<<0))
#define IMG_DERING_CNTL_luma_enable_src(data)                                        ((0x00000001&(data))>>0)
#define IMG_DERING_CNTL_get_luma_enable(data)                                        ((0x00000001&(data))>>0)


#define IMG_FILT_CNTL                                                                0x1800ED08
#define IMG_FILT_CNTL_reg_addr                                                       "0xB800ED08"
#define IMG_FILT_CNTL_reg                                                            0xB800ED08
#define set_IMG_FILT_CNTL_reg(data)   (*((volatile unsigned int*) IMG_FILT_CNTL_reg)=data)
#define get_IMG_FILT_CNTL_reg   (*((volatile unsigned int*) IMG_FILT_CNTL_reg))
#define IMG_FILT_CNTL_inst_adr                                                       "0x0042"
#define IMG_FILT_CNTL_inst                                                           0x0042
#define IMG_FILT_CNTL_filt_prec_shift                                                (0)
#define IMG_FILT_CNTL_filt_prec_mask                                                 (0x00000003)
#define IMG_FILT_CNTL_filt_prec(data)                                                (0x00000003&((data)<<0))
#define IMG_FILT_CNTL_filt_prec_src(data)                                            ((0x00000003&(data))>>0)
#define IMG_FILT_CNTL_get_filt_prec(data)                                            ((0x00000003&(data))>>0)


#define IMG_FILT_INIT                                                                0x1800ED0C
#define IMG_FILT_INIT_reg_addr                                                       "0xB800ED0C"
#define IMG_FILT_INIT_reg                                                            0xB800ED0C
#define set_IMG_FILT_INIT_reg(data)   (*((volatile unsigned int*) IMG_FILT_INIT_reg)=data)
#define get_IMG_FILT_INIT_reg   (*((volatile unsigned int*) IMG_FILT_INIT_reg))
#define IMG_FILT_INIT_inst_adr                                                       "0x0043"
#define IMG_FILT_INIT_inst                                                           0x0043
#define IMG_FILT_INIT_init_value_shift                                               (0)
#define IMG_FILT_INIT_init_value_mask                                                (0x000003FF)
#define IMG_FILT_INIT_init_value(data)                                               (0x000003FF&((data)<<0))
#define IMG_FILT_INIT_init_value_src(data)                                           ((0x000003FF&(data))>>0)
#define IMG_FILT_INIT_get_init_value(data)                                           ((0x000003FF&(data))>>0)


#define IMG_RMRPR_CNTL                                                               0x1800ED10
#define IMG_RMRPR_CNTL_reg_addr                                                      "0xB800ED10"
#define IMG_RMRPR_CNTL_reg                                                           0xB800ED10
#define set_IMG_RMRPR_CNTL_reg(data)   (*((volatile unsigned int*) IMG_RMRPR_CNTL_reg)=data)
#define get_IMG_RMRPR_CNTL_reg   (*((volatile unsigned int*) IMG_RMRPR_CNTL_reg))
#define IMG_RMRPR_CNTL_inst_adr                                                      "0x0044"
#define IMG_RMRPR_CNTL_inst                                                          0x0044
#define IMG_RMRPR_CNTL_rcrpr_shift                                                   (26)
#define IMG_RMRPR_CNTL_rcrpr_mask                                                    (0x04000000)
#define IMG_RMRPR_CNTL_rcrpr(data)                                                   (0x04000000&((data)<<26))
#define IMG_RMRPR_CNTL_rcrpr_src(data)                                               ((0x04000000&(data))>>26)
#define IMG_RMRPR_CNTL_get_rcrpr(data)                                               ((0x04000000&(data))>>26)
#define IMG_RMRPR_CNTL_color_cr_shift                                                (18)
#define IMG_RMRPR_CNTL_color_cr_mask                                                 (0x03FC0000)
#define IMG_RMRPR_CNTL_color_cr(data)                                                (0x03FC0000&((data)<<18))
#define IMG_RMRPR_CNTL_color_cr_src(data)                                            ((0x03FC0000&(data))>>18)
#define IMG_RMRPR_CNTL_get_color_cr(data)                                            ((0x03FC0000&(data))>>18)
#define IMG_RMRPR_CNTL_color_cb_shift                                                (10)
#define IMG_RMRPR_CNTL_color_cb_mask                                                 (0x0003FC00)
#define IMG_RMRPR_CNTL_color_cb(data)                                                (0x0003FC00&((data)<<10))
#define IMG_RMRPR_CNTL_color_cb_src(data)                                            ((0x0003FC00&(data))>>10)
#define IMG_RMRPR_CNTL_get_color_cb(data)                                            ((0x0003FC00&(data))>>10)
#define IMG_RMRPR_CNTL_color_y_shift                                                 (2)
#define IMG_RMRPR_CNTL_color_y_mask                                                  (0x000003FC)
#define IMG_RMRPR_CNTL_color_y(data)                                                 (0x000003FC&((data)<<2))
#define IMG_RMRPR_CNTL_color_y_src(data)                                             ((0x000003FC&(data))>>2)
#define IMG_RMRPR_CNTL_get_color_y(data)                                             ((0x000003FC&(data))>>2)
#define IMG_RMRPR_CNTL_fill_mode_shift                                               (0)
#define IMG_RMRPR_CNTL_fill_mode_mask                                                (0x00000003)
#define IMG_RMRPR_CNTL_fill_mode(data)                                               (0x00000003&((data)<<0))
#define IMG_RMRPR_CNTL_fill_mode_src(data)                                           ((0x00000003&(data))>>0)
#define IMG_RMRPR_CNTL_get_fill_mode(data)                                           ((0x00000003&(data))>>0)


#define IMG_RMRPR_PAR                                                                0x1800ED14
#define IMG_RMRPR_PAR_reg_addr                                                       "0xB800ED14"
#define IMG_RMRPR_PAR_reg                                                            0xB800ED14
#define set_IMG_RMRPR_PAR_reg(data)   (*((volatile unsigned int*) IMG_RMRPR_PAR_reg)=data)
#define get_IMG_RMRPR_PAR_reg   (*((volatile unsigned int*) IMG_RMRPR_PAR_reg))
#define IMG_RMRPR_PAR_inst_adr                                                       "0x0045"
#define IMG_RMRPR_PAR_inst                                                           0x0045
#define IMG_RMRPR_PAR_m_shift                                                        (11)
#define IMG_RMRPR_PAR_m_mask                                                         (0x00007800)
#define IMG_RMRPR_PAR_m(data)                                                        (0x00007800&((data)<<11))
#define IMG_RMRPR_PAR_m_src(data)                                                    ((0x00007800&(data))>>11)
#define IMG_RMRPR_PAR_get_m(data)                                                    ((0x00007800&(data))>>11)
#define IMG_RMRPR_PAR_pixel_offset_shift                                             (0)
#define IMG_RMRPR_PAR_pixel_offset_mask                                              (0x000007FF)
#define IMG_RMRPR_PAR_pixel_offset(data)                                             (0x000007FF&((data)<<0))
#define IMG_RMRPR_PAR_pixel_offset_src(data)                                         ((0x000007FF&(data))>>0)
#define IMG_RMRPR_PAR_get_pixel_offset(data)                                         ((0x000007FF&(data))>>0)


#define IMG_RMRPR_AX                                                                 0x1800ED18
#define IMG_RMRPR_AX_reg_addr                                                        "0xB800ED18"
#define IMG_RMRPR_AX_reg                                                             0xB800ED18
#define set_IMG_RMRPR_AX_reg(data)   (*((volatile unsigned int*) IMG_RMRPR_AX_reg)=data)
#define get_IMG_RMRPR_AX_reg   (*((volatile unsigned int*) IMG_RMRPR_AX_reg))
#define IMG_RMRPR_AX_inst_adr                                                        "0x0046"
#define IMG_RMRPR_AX_inst                                                            0x0046
#define IMG_RMRPR_AX_ax_shift                                                        (0)
#define IMG_RMRPR_AX_ax_mask                                                         (0xFFFFFFFF)
#define IMG_RMRPR_AX_ax(data)                                                        (0xFFFFFFFF&((data)<<0))
#define IMG_RMRPR_AX_ax_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define IMG_RMRPR_AX_get_ax(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define IMG_RMRPR_AY                                                                 0x1800ED1C
#define IMG_RMRPR_AY_reg_addr                                                        "0xB800ED1C"
#define IMG_RMRPR_AY_reg                                                             0xB800ED1C
#define set_IMG_RMRPR_AY_reg(data)   (*((volatile unsigned int*) IMG_RMRPR_AY_reg)=data)
#define get_IMG_RMRPR_AY_reg   (*((volatile unsigned int*) IMG_RMRPR_AY_reg))
#define IMG_RMRPR_AY_inst_adr                                                        "0x0047"
#define IMG_RMRPR_AY_inst                                                            0x0047
#define IMG_RMRPR_AY_ay_shift                                                        (0)
#define IMG_RMRPR_AY_ay_mask                                                         (0xFFFFFFFF)
#define IMG_RMRPR_AY_ay(data)                                                        (0xFFFFFFFF&((data)<<0))
#define IMG_RMRPR_AY_ay_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define IMG_RMRPR_AY_get_ay(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define IMG_RMRPR_AXINC                                                              0x1800ED20
#define IMG_RMRPR_AXINC_reg_addr                                                     "0xB800ED20"
#define IMG_RMRPR_AXINC_reg                                                          0xB800ED20
#define set_IMG_RMRPR_AXINC_reg(data)   (*((volatile unsigned int*) IMG_RMRPR_AXINC_reg)=data)
#define get_IMG_RMRPR_AXINC_reg   (*((volatile unsigned int*) IMG_RMRPR_AXINC_reg))
#define IMG_RMRPR_AXINC_inst_adr                                                     "0x0048"
#define IMG_RMRPR_AXINC_inst                                                         0x0048
#define IMG_RMRPR_AXINC_ax_inc_shift                                                 (0)
#define IMG_RMRPR_AXINC_ax_inc_mask                                                  (0xFFFFFFFF)
#define IMG_RMRPR_AXINC_ax_inc(data)                                                 (0xFFFFFFFF&((data)<<0))
#define IMG_RMRPR_AXINC_ax_inc_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define IMG_RMRPR_AXINC_get_ax_inc(data)                                             ((0xFFFFFFFF&(data))>>0)


#define IMG_RMRPR_PICINFO                                                            0x1800ED24
#define IMG_RMRPR_PICINFO_reg_addr                                                   "0xB800ED24"
#define IMG_RMRPR_PICINFO_reg                                                        0xB800ED24
#define set_IMG_RMRPR_PICINFO_reg(data)   (*((volatile unsigned int*) IMG_RMRPR_PICINFO_reg)=data)
#define get_IMG_RMRPR_PICINFO_reg   (*((volatile unsigned int*) IMG_RMRPR_PICINFO_reg))
#define IMG_RMRPR_PICINFO_inst_adr                                                   "0x0049"
#define IMG_RMRPR_PICINFO_inst                                                       0x0049
#define IMG_RMRPR_PICINFO_picmb_h_shift                                              (7)
#define IMG_RMRPR_PICINFO_picmb_h_mask                                               (0x00001F80)
#define IMG_RMRPR_PICINFO_picmb_h(data)                                              (0x00001F80&((data)<<7))
#define IMG_RMRPR_PICINFO_picmb_h_src(data)                                          ((0x00001F80&(data))>>7)
#define IMG_RMRPR_PICINFO_get_picmb_h(data)                                          ((0x00001F80&(data))>>7)
#define IMG_RMRPR_PICINFO_picmb_w_shift                                              (0)
#define IMG_RMRPR_PICINFO_picmb_w_mask                                               (0x0000007F)
#define IMG_RMRPR_PICINFO_picmb_w(data)                                              (0x0000007F&((data)<<0))
#define IMG_RMRPR_PICINFO_picmb_w_src(data)                                          ((0x0000007F&(data))>>0)
#define IMG_RMRPR_PICINFO_get_picmb_w(data)                                          ((0x0000007F&(data))>>0)


#define IMG_BASEA_0                                                                  0x1800ED28
#define IMG_BASEA_1                                                                  0x1800ED2C
#define IMG_BASEA_2                                                                  0x1800ED30
#define IMG_BASEA_3                                                                  0x1800ED34
#define IMG_BASEA_0_reg_addr                                                         "0xB800ED28"
#define IMG_BASEA_1_reg_addr                                                         "0xB800ED2C"
#define IMG_BASEA_2_reg_addr                                                         "0xB800ED30"
#define IMG_BASEA_3_reg_addr                                                         "0xB800ED34"
#define IMG_BASEA_0_reg                                                              0xB800ED28
#define IMG_BASEA_1_reg                                                              0xB800ED2C
#define IMG_BASEA_2_reg                                                              0xB800ED30
#define IMG_BASEA_3_reg                                                              0xB800ED34
#define set_IMG_BASEA_0_reg(data)   (*((volatile unsigned int*) IMG_BASEA_0_reg)=data)
#define set_IMG_BASEA_1_reg(data)   (*((volatile unsigned int*) IMG_BASEA_1_reg)=data)
#define set_IMG_BASEA_2_reg(data)   (*((volatile unsigned int*) IMG_BASEA_2_reg)=data)
#define set_IMG_BASEA_3_reg(data)   (*((volatile unsigned int*) IMG_BASEA_3_reg)=data)
#define get_IMG_BASEA_0_reg   (*((volatile unsigned int*) IMG_BASEA_0_reg))
#define get_IMG_BASEA_1_reg   (*((volatile unsigned int*) IMG_BASEA_1_reg))
#define get_IMG_BASEA_2_reg   (*((volatile unsigned int*) IMG_BASEA_2_reg))
#define get_IMG_BASEA_3_reg   (*((volatile unsigned int*) IMG_BASEA_3_reg))
#define IMG_BASEA_0_inst_adr                                                         "0x004A"
#define IMG_BASEA_1_inst_adr                                                         "0x004B"
#define IMG_BASEA_2_inst_adr                                                         "0x004C"
#define IMG_BASEA_3_inst_adr                                                         "0x004D"
#define IMG_BASEA_0_inst                                                             0x004A
#define IMG_BASEA_1_inst                                                             0x004B
#define IMG_BASEA_2_inst                                                             0x004C
#define IMG_BASEA_3_inst                                                             0x004D
#define IMG_BASEA_basea_shift                                                        (0)
#define IMG_BASEA_basea_mask                                                         (0x000003FF)
#define IMG_BASEA_basea(data)                                                        (0x000003FF&((data)<<0))
#define IMG_BASEA_basea_src(data)                                                    ((0x000003FF&(data))>>0)
#define IMG_BASEA_get_basea(data)                                                    ((0x000003FF&(data))>>0)


#define IMG_OFFSETA_0                                                                0x1800ED38
#define IMG_OFFSETA_1                                                                0x1800ED3C
#define IMG_OFFSETA_2                                                                0x1800ED40
#define IMG_OFFSETA_3                                                                0x1800ED44
#define IMG_OFFSETA_0_reg_addr                                                       "0xB800ED38"
#define IMG_OFFSETA_1_reg_addr                                                       "0xB800ED3C"
#define IMG_OFFSETA_2_reg_addr                                                       "0xB800ED40"
#define IMG_OFFSETA_3_reg_addr                                                       "0xB800ED44"
#define IMG_OFFSETA_0_reg                                                            0xB800ED38
#define IMG_OFFSETA_1_reg                                                            0xB800ED3C
#define IMG_OFFSETA_2_reg                                                            0xB800ED40
#define IMG_OFFSETA_3_reg                                                            0xB800ED44
#define set_IMG_OFFSETA_0_reg(data)   (*((volatile unsigned int*) IMG_OFFSETA_0_reg)=data)
#define set_IMG_OFFSETA_1_reg(data)   (*((volatile unsigned int*) IMG_OFFSETA_1_reg)=data)
#define set_IMG_OFFSETA_2_reg(data)   (*((volatile unsigned int*) IMG_OFFSETA_2_reg)=data)
#define set_IMG_OFFSETA_3_reg(data)   (*((volatile unsigned int*) IMG_OFFSETA_3_reg)=data)
#define get_IMG_OFFSETA_0_reg   (*((volatile unsigned int*) IMG_OFFSETA_0_reg))
#define get_IMG_OFFSETA_1_reg   (*((volatile unsigned int*) IMG_OFFSETA_1_reg))
#define get_IMG_OFFSETA_2_reg   (*((volatile unsigned int*) IMG_OFFSETA_2_reg))
#define get_IMG_OFFSETA_3_reg   (*((volatile unsigned int*) IMG_OFFSETA_3_reg))
#define IMG_OFFSETA_0_inst_adr                                                       "0x004E"
#define IMG_OFFSETA_1_inst_adr                                                       "0x004F"
#define IMG_OFFSETA_2_inst_adr                                                       "0x0050"
#define IMG_OFFSETA_3_inst_adr                                                       "0x0051"
#define IMG_OFFSETA_0_inst                                                           0x004E
#define IMG_OFFSETA_1_inst                                                           0x004F
#define IMG_OFFSETA_2_inst                                                           0x0050
#define IMG_OFFSETA_3_inst                                                           0x0051
#define IMG_OFFSETA_offseta_shift                                                    (0)
#define IMG_OFFSETA_offseta_mask                                                     (0x000001FF)
#define IMG_OFFSETA_offseta(data)                                                    (0x000001FF&((data)<<0))
#define IMG_OFFSETA_offseta_src(data)                                                ((0x000001FF&(data))>>0)
#define IMG_OFFSETA_get_offseta(data)                                                ((0x000001FF&(data))>>0)


#endif
