/**************************************************************
// Spec Version                  : unknown
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/4/18 19:15:35
***************************************************************/


#ifndef _MIPI_DPHY_REG_H_INCLUDED_
#define _MIPI_DPHY_REG_H_INCLUDED_
#ifdef  _MIPI_DPHY_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     L3_pwdb:1;
unsigned int     L2_pwdb:1;
unsigned int     L1_pwdb:1;
unsigned int     L0_pwdb:1;
}MIPI_DPHY_PWDB;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rxpre_lane:8;
}MIPI_DPHY_RXPRE;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rxpos_lane:8;
}MIPI_DPHY_RXPRE;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Div_sel:2;
unsigned int     reserved_1:1;
unsigned int     drst_sel:1;
unsigned int     Lane3_en:1;
unsigned int     Lane2_en:1;
unsigned int     Lane1_en:1;
unsigned int     Lane0_en:1;
}MIPI_DPHY_REG0;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     yuv_src_sel:2;
unsigned int     reserved_1:1;
unsigned int     dec_format:3;
}MIPI_DPHY_REG1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     D_type:8;
}MIPI_DPHY_REG2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     D_type:1;
unsigned int     L3_deglitch:1;
unsigned int     L2_deglitch:1;
unsigned int     L1_deglitch:1;
unsigned int     L0_deglitch:1;
}MIPI_DPHY_REG3;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     SL_RG:1;
unsigned int     reserved_1:2;
unsigned int     Sw_rst:1;
}MIPI_DPHY_REG4;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     Bit_switch_en:1;
unsigned int     Crc16_en:1;
unsigned int     Ecc_en:1;
unsigned int     Con_clk_lane_en:1;
}MIPI_DPHY_REG5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dvld_lane1:4;
unsigned int     Dvld_lane0:4;
}MIPI_DPHY_REG6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dvld_lane3:4;
unsigned int     Dvld_lane2:4;
}MIPI_DPHY_REG7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Lane3_sel:2;
unsigned int     Lane2_sel:2;
unsigned int     Lane1_sel:2;
unsigned int     Lane0_sel:2;
}MIPI_DPHY_REG8;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     Lane3_clk_edge:1;
unsigned int     Lane2_clk_edge:1;
unsigned int     Lane1_clk_edge:1;
unsigned int     Lane0_clk_edge:1;
}MIPI_DPHY_REG9;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Esc_lane3_int_en:1;
unsigned int     Esc_lane2_int_en:1;
unsigned int     Esc_lane1_int_en:1;
unsigned int     Esc_lane0_int_en:1;
unsigned int     Clk_ulps_int_en:1;
unsigned int     Crc16_err_int_en:1;
unsigned int     Ecc_crt_int_en:1;
unsigned int     Ecc_err_int_en:1;
}MIPI_DPHY_REG10;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Esc_lane3_int_flg:1;
unsigned int     Esc_lane2_int_flg:1;
unsigned int     Esc_lane1_int_flg:1;
unsigned int     Esc_lane0_int_flg:1;
unsigned int     Clk_ulps_int_flg:1;
unsigned int     Crc16_err_int_flg:1;
unsigned int     Ecc_crt_int_flg:1;
unsigned int     Ecc_err_int_flg:1;
}MIPI_DPHY_REG11;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Num_ecc_err:8;
}MIPI_DPHY_REG12;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Num_ecc_err:8;
}MIPI_DPHY_REG13;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Num_crc_err:8;
}MIPI_DPHY_REG14;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Num_crc_err:8;
}MIPI_DPHY_REG15;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     Clk_term_en:1;
unsigned int     Lane3_term_en:1;
unsigned int     Lane2_term_en:1;
unsigned int     Lane1_term_en:1;
unsigned int     Lane0_term_en:1;
}MIPI_DPHY_REG16;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     Lane3_pwdb_en:1;
unsigned int     Lane2_pwdb_en:1;
unsigned int     Lane1_pwdb_en:1;
unsigned int     Lane0_pwdb_en:1;
}MIPI_DPHY_REG17;

typedef struct 
{
unsigned int     reserved_0:32;
}MIPI_DPHY_REG18;

typedef struct 
{
unsigned int     reserved_0:32;
}MIPI_DPHY_REG19;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Lane0_esc_cod:8;
}MIPI_DPHY_REG20;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Lane1_esc_cod:8;
}MIPI_DPHY_REG21;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Lane2_esc_cod:8;
}MIPI_DPHY_REG22;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Lane3_esc_cod:8;
}MIPI_DPHY_REG23;

#endif

#define MIPI_DPHY_PWDB                                                               0x18004074
#define MIPI_DPHY_PWDB_reg_addr                                                      "0xB8004074"
#define MIPI_DPHY_PWDB_reg                                                           0xB8004074
#define set_MIPI_DPHY_PWDB_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_PWDB_reg)=data)
#define get_MIPI_DPHY_PWDB_reg   (*((volatile unsigned int*) MIPI_DPHY_PWDB_reg))
#define MIPI_DPHY_PWDB_inst_adr                                                      "0x001D"
#define MIPI_DPHY_PWDB_inst                                                          0x001D
#define MIPI_DPHY_PWDB_L3_pwdb_shift                                                 (3)
#define MIPI_DPHY_PWDB_L3_pwdb_mask                                                  (0x00000008)
#define MIPI_DPHY_PWDB_L3_pwdb(data)                                                 (0x00000008&((data)<<3))
#define MIPI_DPHY_PWDB_L3_pwdb_src(data)                                             ((0x00000008&(data))>>3)
#define MIPI_DPHY_PWDB_get_L3_pwdb(data)                                             ((0x00000008&(data))>>3)
#define MIPI_DPHY_PWDB_L2_pwdb_shift                                                 (2)
#define MIPI_DPHY_PWDB_L2_pwdb_mask                                                  (0x00000004)
#define MIPI_DPHY_PWDB_L2_pwdb(data)                                                 (0x00000004&((data)<<2))
#define MIPI_DPHY_PWDB_L2_pwdb_src(data)                                             ((0x00000004&(data))>>2)
#define MIPI_DPHY_PWDB_get_L2_pwdb(data)                                             ((0x00000004&(data))>>2)
#define MIPI_DPHY_PWDB_L1_pwdb_shift                                                 (1)
#define MIPI_DPHY_PWDB_L1_pwdb_mask                                                  (0x00000002)
#define MIPI_DPHY_PWDB_L1_pwdb(data)                                                 (0x00000002&((data)<<1))
#define MIPI_DPHY_PWDB_L1_pwdb_src(data)                                             ((0x00000002&(data))>>1)
#define MIPI_DPHY_PWDB_get_L1_pwdb(data)                                             ((0x00000002&(data))>>1)
#define MIPI_DPHY_PWDB_L0_pwdb_shift                                                 (0)
#define MIPI_DPHY_PWDB_L0_pwdb_mask                                                  (0x00000001)
#define MIPI_DPHY_PWDB_L0_pwdb(data)                                                 (0x00000001&((data)<<0))
#define MIPI_DPHY_PWDB_L0_pwdb_src(data)                                             ((0x00000001&(data))>>0)
#define MIPI_DPHY_PWDB_get_L0_pwdb(data)                                             ((0x00000001&(data))>>0)


#define MIPI_DPHY_RXPRE                                                              0x18004078
#define MIPI_DPHY_RXPRE_reg_addr                                                     "0xB8004078"
#define MIPI_DPHY_RXPRE_reg                                                          0xB8004078
#define set_MIPI_DPHY_RXPRE_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_RXPRE_reg)=data)
#define get_MIPI_DPHY_RXPRE_reg   (*((volatile unsigned int*) MIPI_DPHY_RXPRE_reg))
#define MIPI_DPHY_RXPRE_inst_adr                                                     "0x001E"
#define MIPI_DPHY_RXPRE_inst                                                         0x001E
#define MIPI_DPHY_RXPRE_rxpre_lane_shift                                             (0)
#define MIPI_DPHY_RXPRE_rxpre_lane_mask                                              (0x000000FF)
#define MIPI_DPHY_RXPRE_rxpre_lane(data)                                             (0x000000FF&((data)<<0))
#define MIPI_DPHY_RXPRE_rxpre_lane_src(data)                                         ((0x000000FF&(data))>>0)
#define MIPI_DPHY_RXPRE_get_rxpre_lane(data)                                         ((0x000000FF&(data))>>0)


#define MIPI_DPHY_RXPRE                                                              0x1800407C
#define MIPI_DPHY_RXPRE_reg_addr                                                     "0xB800407C"
#define MIPI_DPHY_RXPRE_reg                                                          0xB800407C
#define set_MIPI_DPHY_RXPRE_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_RXPRE_reg)=data)
#define get_MIPI_DPHY_RXPRE_reg   (*((volatile unsigned int*) MIPI_DPHY_RXPRE_reg))
#define MIPI_DPHY_RXPRE_inst_adr                                                     "0x001F"
#define MIPI_DPHY_RXPRE_inst                                                         0x001F
#define MIPI_DPHY_RXPRE_rxpos_lane_shift                                             (0)
#define MIPI_DPHY_RXPRE_rxpos_lane_mask                                              (0x000000FF)
#define MIPI_DPHY_RXPRE_rxpos_lane(data)                                             (0x000000FF&((data)<<0))
#define MIPI_DPHY_RXPRE_rxpos_lane_src(data)                                         ((0x000000FF&(data))>>0)
#define MIPI_DPHY_RXPRE_get_rxpos_lane(data)                                         ((0x000000FF&(data))>>0)


#define MIPI_DPHY_REG0                                                               0x18004080
#define MIPI_DPHY_REG0_reg_addr                                                      "0xB8004080"
#define MIPI_DPHY_REG0_reg                                                           0xB8004080
#define set_MIPI_DPHY_REG0_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG0_reg)=data)
#define get_MIPI_DPHY_REG0_reg   (*((volatile unsigned int*) MIPI_DPHY_REG0_reg))
#define MIPI_DPHY_REG0_inst_adr                                                      "0x0020"
#define MIPI_DPHY_REG0_inst                                                          0x0020
#define MIPI_DPHY_REG0_Div_sel_shift                                                 (6)
#define MIPI_DPHY_REG0_Div_sel_mask                                                  (0x000000C0)
#define MIPI_DPHY_REG0_Div_sel(data)                                                 (0x000000C0&((data)<<6))
#define MIPI_DPHY_REG0_Div_sel_src(data)                                             ((0x000000C0&(data))>>6)
#define MIPI_DPHY_REG0_get_Div_sel(data)                                             ((0x000000C0&(data))>>6)
#define MIPI_DPHY_REG0_drst_sel_shift                                                (4)
#define MIPI_DPHY_REG0_drst_sel_mask                                                 (0x00000010)
#define MIPI_DPHY_REG0_drst_sel(data)                                                (0x00000010&((data)<<4))
#define MIPI_DPHY_REG0_drst_sel_src(data)                                            ((0x00000010&(data))>>4)
#define MIPI_DPHY_REG0_get_drst_sel(data)                                            ((0x00000010&(data))>>4)
#define MIPI_DPHY_REG0_Lane3_en_shift                                                (3)
#define MIPI_DPHY_REG0_Lane3_en_mask                                                 (0x00000008)
#define MIPI_DPHY_REG0_Lane3_en(data)                                                (0x00000008&((data)<<3))
#define MIPI_DPHY_REG0_Lane3_en_src(data)                                            ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG0_get_Lane3_en(data)                                            ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG0_Lane2_en_shift                                                (2)
#define MIPI_DPHY_REG0_Lane2_en_mask                                                 (0x00000004)
#define MIPI_DPHY_REG0_Lane2_en(data)                                                (0x00000004&((data)<<2))
#define MIPI_DPHY_REG0_Lane2_en_src(data)                                            ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG0_get_Lane2_en(data)                                            ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG0_Lane1_en_shift                                                (1)
#define MIPI_DPHY_REG0_Lane1_en_mask                                                 (0x00000002)
#define MIPI_DPHY_REG0_Lane1_en(data)                                                (0x00000002&((data)<<1))
#define MIPI_DPHY_REG0_Lane1_en_src(data)                                            ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG0_get_Lane1_en(data)                                            ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG0_Lane0_en_shift                                                (0)
#define MIPI_DPHY_REG0_Lane0_en_mask                                                 (0x00000001)
#define MIPI_DPHY_REG0_Lane0_en(data)                                                (0x00000001&((data)<<0))
#define MIPI_DPHY_REG0_Lane0_en_src(data)                                            ((0x00000001&(data))>>0)
#define MIPI_DPHY_REG0_get_Lane0_en(data)                                            ((0x00000001&(data))>>0)


#define MIPI_DPHY_REG1                                                               0x1800408C
#define MIPI_DPHY_REG1_reg_addr                                                      "0xB800408C"
#define MIPI_DPHY_REG1_reg                                                           0xB800408C
#define set_MIPI_DPHY_REG1_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG1_reg)=data)
#define get_MIPI_DPHY_REG1_reg   (*((volatile unsigned int*) MIPI_DPHY_REG1_reg))
#define MIPI_DPHY_REG1_inst_adr                                                      "0x0023"
#define MIPI_DPHY_REG1_inst                                                          0x0023
#define MIPI_DPHY_REG1_yuv_src_sel_shift                                             (4)
#define MIPI_DPHY_REG1_yuv_src_sel_mask                                              (0x00000030)
#define MIPI_DPHY_REG1_yuv_src_sel(data)                                             (0x00000030&((data)<<4))
#define MIPI_DPHY_REG1_yuv_src_sel_src(data)                                         ((0x00000030&(data))>>4)
#define MIPI_DPHY_REG1_get_yuv_src_sel(data)                                         ((0x00000030&(data))>>4)
#define MIPI_DPHY_REG1_dec_format_shift                                              (0)
#define MIPI_DPHY_REG1_dec_format_mask                                               (0x00000007)
#define MIPI_DPHY_REG1_dec_format(data)                                              (0x00000007&((data)<<0))
#define MIPI_DPHY_REG1_dec_format_src(data)                                          ((0x00000007&(data))>>0)
#define MIPI_DPHY_REG1_get_dec_format(data)                                          ((0x00000007&(data))>>0)


#define MIPI_DPHY_REG2                                                               0x18004090
#define MIPI_DPHY_REG2_reg_addr                                                      "0xB8004090"
#define MIPI_DPHY_REG2_reg                                                           0xB8004090
#define set_MIPI_DPHY_REG2_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG2_reg)=data)
#define get_MIPI_DPHY_REG2_reg   (*((volatile unsigned int*) MIPI_DPHY_REG2_reg))
#define MIPI_DPHY_REG2_inst_adr                                                      "0x0024"
#define MIPI_DPHY_REG2_inst                                                          0x0024
#define MIPI_DPHY_REG2_D_type_shift                                                  (0)
#define MIPI_DPHY_REG2_D_type_mask                                                   (0x000000FF)
#define MIPI_DPHY_REG2_D_type(data)                                                  (0x000000FF&((data)<<0))
#define MIPI_DPHY_REG2_D_type_src(data)                                              ((0x000000FF&(data))>>0)
#define MIPI_DPHY_REG2_get_D_type(data)                                              ((0x000000FF&(data))>>0)


#define MIPI_DPHY_REG3                                                               0x18004094
#define MIPI_DPHY_REG3_reg_addr                                                      "0xB8004094"
#define MIPI_DPHY_REG3_reg                                                           0xB8004094
#define set_MIPI_DPHY_REG3_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG3_reg)=data)
#define get_MIPI_DPHY_REG3_reg   (*((volatile unsigned int*) MIPI_DPHY_REG3_reg))
#define MIPI_DPHY_REG3_inst_adr                                                      "0x0025"
#define MIPI_DPHY_REG3_inst                                                          0x0025
#define MIPI_DPHY_REG3_D_type_shift                                                  (4)
#define MIPI_DPHY_REG3_D_type_mask                                                   (0x00000010)
#define MIPI_DPHY_REG3_D_type(data)                                                  (0x00000010&((data)<<4))
#define MIPI_DPHY_REG3_D_type_src(data)                                              ((0x00000010&(data))>>4)
#define MIPI_DPHY_REG3_get_D_type(data)                                              ((0x00000010&(data))>>4)
#define MIPI_DPHY_REG3_L3_deglitch_shift                                             (3)
#define MIPI_DPHY_REG3_L3_deglitch_mask                                              (0x00000008)
#define MIPI_DPHY_REG3_L3_deglitch(data)                                             (0x00000008&((data)<<3))
#define MIPI_DPHY_REG3_L3_deglitch_src(data)                                         ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG3_get_L3_deglitch(data)                                         ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG3_L2_deglitch_shift                                             (2)
#define MIPI_DPHY_REG3_L2_deglitch_mask                                              (0x00000004)
#define MIPI_DPHY_REG3_L2_deglitch(data)                                             (0x00000004&((data)<<2))
#define MIPI_DPHY_REG3_L2_deglitch_src(data)                                         ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG3_get_L2_deglitch(data)                                         ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG3_L1_deglitch_shift                                             (1)
#define MIPI_DPHY_REG3_L1_deglitch_mask                                              (0x00000002)
#define MIPI_DPHY_REG3_L1_deglitch(data)                                             (0x00000002&((data)<<1))
#define MIPI_DPHY_REG3_L1_deglitch_src(data)                                         ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG3_get_L1_deglitch(data)                                         ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG3_L0_deglitch_shift                                             (0)
#define MIPI_DPHY_REG3_L0_deglitch_mask                                              (0x00000001)
#define MIPI_DPHY_REG3_L0_deglitch(data)                                             (0x00000001&((data)<<0))
#define MIPI_DPHY_REG3_L0_deglitch_src(data)                                         ((0x00000001&(data))>>0)
#define MIPI_DPHY_REG3_get_L0_deglitch(data)                                         ((0x00000001&(data))>>0)


#define MIPI_DPHY_REG4                                                               0x18004098
#define MIPI_DPHY_REG4_reg_addr                                                      "0xB8004098"
#define MIPI_DPHY_REG4_reg                                                           0xB8004098
#define set_MIPI_DPHY_REG4_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG4_reg)=data)
#define get_MIPI_DPHY_REG4_reg   (*((volatile unsigned int*) MIPI_DPHY_REG4_reg))
#define MIPI_DPHY_REG4_inst_adr                                                      "0x0026"
#define MIPI_DPHY_REG4_inst                                                          0x0026
#define MIPI_DPHY_REG4_SL_RG_shift                                                   (3)
#define MIPI_DPHY_REG4_SL_RG_mask                                                    (0x00000008)
#define MIPI_DPHY_REG4_SL_RG(data)                                                   (0x00000008&((data)<<3))
#define MIPI_DPHY_REG4_SL_RG_src(data)                                               ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG4_get_SL_RG(data)                                               ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG4_Sw_rst_shift                                                  (0)
#define MIPI_DPHY_REG4_Sw_rst_mask                                                   (0x00000001)
#define MIPI_DPHY_REG4_Sw_rst(data)                                                  (0x00000001&((data)<<0))
#define MIPI_DPHY_REG4_Sw_rst_src(data)                                              ((0x00000001&(data))>>0)
#define MIPI_DPHY_REG4_get_Sw_rst(data)                                              ((0x00000001&(data))>>0)


#define MIPI_DPHY_REG5                                                               0x1800409C
#define MIPI_DPHY_REG5_reg_addr                                                      "0xB800409C"
#define MIPI_DPHY_REG5_reg                                                           0xB800409C
#define set_MIPI_DPHY_REG5_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG5_reg)=data)
#define get_MIPI_DPHY_REG5_reg   (*((volatile unsigned int*) MIPI_DPHY_REG5_reg))
#define MIPI_DPHY_REG5_inst_adr                                                      "0x0027"
#define MIPI_DPHY_REG5_inst                                                          0x0027
#define MIPI_DPHY_REG5_Bit_switch_en_shift                                           (3)
#define MIPI_DPHY_REG5_Bit_switch_en_mask                                            (0x00000008)
#define MIPI_DPHY_REG5_Bit_switch_en(data)                                           (0x00000008&((data)<<3))
#define MIPI_DPHY_REG5_Bit_switch_en_src(data)                                       ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG5_get_Bit_switch_en(data)                                       ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG5_Crc16_en_shift                                                (2)
#define MIPI_DPHY_REG5_Crc16_en_mask                                                 (0x00000004)
#define MIPI_DPHY_REG5_Crc16_en(data)                                                (0x00000004&((data)<<2))
#define MIPI_DPHY_REG5_Crc16_en_src(data)                                            ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG5_get_Crc16_en(data)                                            ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG5_Ecc_en_shift                                                  (1)
#define MIPI_DPHY_REG5_Ecc_en_mask                                                   (0x00000002)
#define MIPI_DPHY_REG5_Ecc_en(data)                                                  (0x00000002&((data)<<1))
#define MIPI_DPHY_REG5_Ecc_en_src(data)                                              ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG5_get_Ecc_en(data)                                              ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG5_Con_clk_lane_en_shift                                         (0)
#define MIPI_DPHY_REG5_Con_clk_lane_en_mask                                          (0x00000001)
#define MIPI_DPHY_REG5_Con_clk_lane_en(data)                                         (0x00000001&((data)<<0))
#define MIPI_DPHY_REG5_Con_clk_lane_en_src(data)                                     ((0x00000001&(data))>>0)
#define MIPI_DPHY_REG5_get_Con_clk_lane_en(data)                                     ((0x00000001&(data))>>0)


#define MIPI_DPHY_REG6                                                               0x180040A0
#define MIPI_DPHY_REG6_reg_addr                                                      "0xB80040A0"
#define MIPI_DPHY_REG6_reg                                                           0xB80040A0
#define set_MIPI_DPHY_REG6_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG6_reg)=data)
#define get_MIPI_DPHY_REG6_reg   (*((volatile unsigned int*) MIPI_DPHY_REG6_reg))
#define MIPI_DPHY_REG6_inst_adr                                                      "0x0028"
#define MIPI_DPHY_REG6_inst                                                          0x0028
#define MIPI_DPHY_REG6_Dvld_lane1_shift                                              (4)
#define MIPI_DPHY_REG6_Dvld_lane1_mask                                               (0x000000F0)
#define MIPI_DPHY_REG6_Dvld_lane1(data)                                              (0x000000F0&((data)<<4))
#define MIPI_DPHY_REG6_Dvld_lane1_src(data)                                          ((0x000000F0&(data))>>4)
#define MIPI_DPHY_REG6_get_Dvld_lane1(data)                                          ((0x000000F0&(data))>>4)
#define MIPI_DPHY_REG6_Dvld_lane0_shift                                              (0)
#define MIPI_DPHY_REG6_Dvld_lane0_mask                                               (0x0000000F)
#define MIPI_DPHY_REG6_Dvld_lane0(data)                                              (0x0000000F&((data)<<0))
#define MIPI_DPHY_REG6_Dvld_lane0_src(data)                                          ((0x0000000F&(data))>>0)
#define MIPI_DPHY_REG6_get_Dvld_lane0(data)                                          ((0x0000000F&(data))>>0)


#define MIPI_DPHY_REG7                                                               0x180040A4
#define MIPI_DPHY_REG7_reg_addr                                                      "0xB80040A4"
#define MIPI_DPHY_REG7_reg                                                           0xB80040A4
#define set_MIPI_DPHY_REG7_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG7_reg)=data)
#define get_MIPI_DPHY_REG7_reg   (*((volatile unsigned int*) MIPI_DPHY_REG7_reg))
#define MIPI_DPHY_REG7_inst_adr                                                      "0x0029"
#define MIPI_DPHY_REG7_inst                                                          0x0029
#define MIPI_DPHY_REG7_Dvld_lane3_shift                                              (4)
#define MIPI_DPHY_REG7_Dvld_lane3_mask                                               (0x000000F0)
#define MIPI_DPHY_REG7_Dvld_lane3(data)                                              (0x000000F0&((data)<<4))
#define MIPI_DPHY_REG7_Dvld_lane3_src(data)                                          ((0x000000F0&(data))>>4)
#define MIPI_DPHY_REG7_get_Dvld_lane3(data)                                          ((0x000000F0&(data))>>4)
#define MIPI_DPHY_REG7_Dvld_lane2_shift                                              (0)
#define MIPI_DPHY_REG7_Dvld_lane2_mask                                               (0x0000000F)
#define MIPI_DPHY_REG7_Dvld_lane2(data)                                              (0x0000000F&((data)<<0))
#define MIPI_DPHY_REG7_Dvld_lane2_src(data)                                          ((0x0000000F&(data))>>0)
#define MIPI_DPHY_REG7_get_Dvld_lane2(data)                                          ((0x0000000F&(data))>>0)


#define MIPI_DPHY_REG8                                                               0x180040A8
#define MIPI_DPHY_REG8_reg_addr                                                      "0xB80040A8"
#define MIPI_DPHY_REG8_reg                                                           0xB80040A8
#define set_MIPI_DPHY_REG8_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG8_reg)=data)
#define get_MIPI_DPHY_REG8_reg   (*((volatile unsigned int*) MIPI_DPHY_REG8_reg))
#define MIPI_DPHY_REG8_inst_adr                                                      "0x002A"
#define MIPI_DPHY_REG8_inst                                                          0x002A
#define MIPI_DPHY_REG8_Lane3_sel_shift                                               (6)
#define MIPI_DPHY_REG8_Lane3_sel_mask                                                (0x000000C0)
#define MIPI_DPHY_REG8_Lane3_sel(data)                                               (0x000000C0&((data)<<6))
#define MIPI_DPHY_REG8_Lane3_sel_src(data)                                           ((0x000000C0&(data))>>6)
#define MIPI_DPHY_REG8_get_Lane3_sel(data)                                           ((0x000000C0&(data))>>6)
#define MIPI_DPHY_REG8_Lane2_sel_shift                                               (4)
#define MIPI_DPHY_REG8_Lane2_sel_mask                                                (0x00000030)
#define MIPI_DPHY_REG8_Lane2_sel(data)                                               (0x00000030&((data)<<4))
#define MIPI_DPHY_REG8_Lane2_sel_src(data)                                           ((0x00000030&(data))>>4)
#define MIPI_DPHY_REG8_get_Lane2_sel(data)                                           ((0x00000030&(data))>>4)
#define MIPI_DPHY_REG8_Lane1_sel_shift                                               (2)
#define MIPI_DPHY_REG8_Lane1_sel_mask                                                (0x0000000C)
#define MIPI_DPHY_REG8_Lane1_sel(data)                                               (0x0000000C&((data)<<2))
#define MIPI_DPHY_REG8_Lane1_sel_src(data)                                           ((0x0000000C&(data))>>2)
#define MIPI_DPHY_REG8_get_Lane1_sel(data)                                           ((0x0000000C&(data))>>2)
#define MIPI_DPHY_REG8_Lane0_sel_shift                                               (0)
#define MIPI_DPHY_REG8_Lane0_sel_mask                                                (0x00000003)
#define MIPI_DPHY_REG8_Lane0_sel(data)                                               (0x00000003&((data)<<0))
#define MIPI_DPHY_REG8_Lane0_sel_src(data)                                           ((0x00000003&(data))>>0)
#define MIPI_DPHY_REG8_get_Lane0_sel(data)                                           ((0x00000003&(data))>>0)


#define MIPI_DPHY_REG9                                                               0x180040AC
#define MIPI_DPHY_REG9_reg_addr                                                      "0xB80040AC"
#define MIPI_DPHY_REG9_reg                                                           0xB80040AC
#define set_MIPI_DPHY_REG9_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG9_reg)=data)
#define get_MIPI_DPHY_REG9_reg   (*((volatile unsigned int*) MIPI_DPHY_REG9_reg))
#define MIPI_DPHY_REG9_inst_adr                                                      "0x002B"
#define MIPI_DPHY_REG9_inst                                                          0x002B
#define MIPI_DPHY_REG9_Lane3_clk_edge_shift                                          (3)
#define MIPI_DPHY_REG9_Lane3_clk_edge_mask                                           (0x00000008)
#define MIPI_DPHY_REG9_Lane3_clk_edge(data)                                          (0x00000008&((data)<<3))
#define MIPI_DPHY_REG9_Lane3_clk_edge_src(data)                                      ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG9_get_Lane3_clk_edge(data)                                      ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG9_Lane2_clk_edge_shift                                          (2)
#define MIPI_DPHY_REG9_Lane2_clk_edge_mask                                           (0x00000004)
#define MIPI_DPHY_REG9_Lane2_clk_edge(data)                                          (0x00000004&((data)<<2))
#define MIPI_DPHY_REG9_Lane2_clk_edge_src(data)                                      ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG9_get_Lane2_clk_edge(data)                                      ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG9_Lane1_clk_edge_shift                                          (1)
#define MIPI_DPHY_REG9_Lane1_clk_edge_mask                                           (0x00000002)
#define MIPI_DPHY_REG9_Lane1_clk_edge(data)                                          (0x00000002&((data)<<1))
#define MIPI_DPHY_REG9_Lane1_clk_edge_src(data)                                      ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG9_get_Lane1_clk_edge(data)                                      ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG9_Lane0_clk_edge_shift                                          (0)
#define MIPI_DPHY_REG9_Lane0_clk_edge_mask                                           (0x00000001)
#define MIPI_DPHY_REG9_Lane0_clk_edge(data)                                          (0x00000001&((data)<<0))
#define MIPI_DPHY_REG9_Lane0_clk_edge_src(data)                                      ((0x00000001&(data))>>0)
#define MIPI_DPHY_REG9_get_Lane0_clk_edge(data)                                      ((0x00000001&(data))>>0)


#define MIPI_DPHY_REG10                                                              0x180040B0
#define MIPI_DPHY_REG10_reg_addr                                                     "0xB80040B0"
#define MIPI_DPHY_REG10_reg                                                          0xB80040B0
#define set_MIPI_DPHY_REG10_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG10_reg)=data)
#define get_MIPI_DPHY_REG10_reg   (*((volatile unsigned int*) MIPI_DPHY_REG10_reg))
#define MIPI_DPHY_REG10_inst_adr                                                     "0x002C"
#define MIPI_DPHY_REG10_inst                                                         0x002C
#define MIPI_DPHY_REG10_Esc_lane3_int_en_shift                                       (7)
#define MIPI_DPHY_REG10_Esc_lane3_int_en_mask                                        (0x00000080)
#define MIPI_DPHY_REG10_Esc_lane3_int_en(data)                                       (0x00000080&((data)<<7))
#define MIPI_DPHY_REG10_Esc_lane3_int_en_src(data)                                   ((0x00000080&(data))>>7)
#define MIPI_DPHY_REG10_get_Esc_lane3_int_en(data)                                   ((0x00000080&(data))>>7)
#define MIPI_DPHY_REG10_Esc_lane2_int_en_shift                                       (6)
#define MIPI_DPHY_REG10_Esc_lane2_int_en_mask                                        (0x00000040)
#define MIPI_DPHY_REG10_Esc_lane2_int_en(data)                                       (0x00000040&((data)<<6))
#define MIPI_DPHY_REG10_Esc_lane2_int_en_src(data)                                   ((0x00000040&(data))>>6)
#define MIPI_DPHY_REG10_get_Esc_lane2_int_en(data)                                   ((0x00000040&(data))>>6)
#define MIPI_DPHY_REG10_Esc_lane1_int_en_shift                                       (5)
#define MIPI_DPHY_REG10_Esc_lane1_int_en_mask                                        (0x00000020)
#define MIPI_DPHY_REG10_Esc_lane1_int_en(data)                                       (0x00000020&((data)<<5))
#define MIPI_DPHY_REG10_Esc_lane1_int_en_src(data)                                   ((0x00000020&(data))>>5)
#define MIPI_DPHY_REG10_get_Esc_lane1_int_en(data)                                   ((0x00000020&(data))>>5)
#define MIPI_DPHY_REG10_Esc_lane0_int_en_shift                                       (4)
#define MIPI_DPHY_REG10_Esc_lane0_int_en_mask                                        (0x00000010)
#define MIPI_DPHY_REG10_Esc_lane0_int_en(data)                                       (0x00000010&((data)<<4))
#define MIPI_DPHY_REG10_Esc_lane0_int_en_src(data)                                   ((0x00000010&(data))>>4)
#define MIPI_DPHY_REG10_get_Esc_lane0_int_en(data)                                   ((0x00000010&(data))>>4)
#define MIPI_DPHY_REG10_Clk_ulps_int_en_shift                                        (3)
#define MIPI_DPHY_REG10_Clk_ulps_int_en_mask                                         (0x00000008)
#define MIPI_DPHY_REG10_Clk_ulps_int_en(data)                                        (0x00000008&((data)<<3))
#define MIPI_DPHY_REG10_Clk_ulps_int_en_src(data)                                    ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG10_get_Clk_ulps_int_en(data)                                    ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG10_Crc16_err_int_en_shift                                       (2)
#define MIPI_DPHY_REG10_Crc16_err_int_en_mask                                        (0x00000004)
#define MIPI_DPHY_REG10_Crc16_err_int_en(data)                                       (0x00000004&((data)<<2))
#define MIPI_DPHY_REG10_Crc16_err_int_en_src(data)                                   ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG10_get_Crc16_err_int_en(data)                                   ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG10_Ecc_crt_int_en_shift                                         (1)
#define MIPI_DPHY_REG10_Ecc_crt_int_en_mask                                          (0x00000002)
#define MIPI_DPHY_REG10_Ecc_crt_int_en(data)                                         (0x00000002&((data)<<1))
#define MIPI_DPHY_REG10_Ecc_crt_int_en_src(data)                                     ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG10_get_Ecc_crt_int_en(data)                                     ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG10_Ecc_err_int_en_shift                                         (0)
#define MIPI_DPHY_REG10_Ecc_err_int_en_mask                                          (0x00000001)
#define MIPI_DPHY_REG10_Ecc_err_int_en(data)                                         (0x00000001&((data)<<0))
#define MIPI_DPHY_REG10_Ecc_err_int_en_src(data)                                     ((0x00000001&(data))>>0)
#define MIPI_DPHY_REG10_get_Ecc_err_int_en(data)                                     ((0x00000001&(data))>>0)


#define MIPI_DPHY_REG11                                                              0x180040B4
#define MIPI_DPHY_REG11_reg_addr                                                     "0xB80040B4"
#define MIPI_DPHY_REG11_reg                                                          0xB80040B4
#define set_MIPI_DPHY_REG11_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG11_reg)=data)
#define get_MIPI_DPHY_REG11_reg   (*((volatile unsigned int*) MIPI_DPHY_REG11_reg))
#define MIPI_DPHY_REG11_inst_adr                                                     "0x002D"
#define MIPI_DPHY_REG11_inst                                                         0x002D
#define MIPI_DPHY_REG11_Esc_lane3_int_flg_shift                                      (7)
#define MIPI_DPHY_REG11_Esc_lane3_int_flg_mask                                       (0x00000080)
#define MIPI_DPHY_REG11_Esc_lane3_int_flg(data)                                      (0x00000080&((data)<<7))
#define MIPI_DPHY_REG11_Esc_lane3_int_flg_src(data)                                  ((0x00000080&(data))>>7)
#define MIPI_DPHY_REG11_get_Esc_lane3_int_flg(data)                                  ((0x00000080&(data))>>7)
#define MIPI_DPHY_REG11_Esc_lane2_int_flg_shift                                      (6)
#define MIPI_DPHY_REG11_Esc_lane2_int_flg_mask                                       (0x00000040)
#define MIPI_DPHY_REG11_Esc_lane2_int_flg(data)                                      (0x00000040&((data)<<6))
#define MIPI_DPHY_REG11_Esc_lane2_int_flg_src(data)                                  ((0x00000040&(data))>>6)
#define MIPI_DPHY_REG11_get_Esc_lane2_int_flg(data)                                  ((0x00000040&(data))>>6)
#define MIPI_DPHY_REG11_Esc_lane1_int_flg_shift                                      (5)
#define MIPI_DPHY_REG11_Esc_lane1_int_flg_mask                                       (0x00000020)
#define MIPI_DPHY_REG11_Esc_lane1_int_flg(data)                                      (0x00000020&((data)<<5))
#define MIPI_DPHY_REG11_Esc_lane1_int_flg_src(data)                                  ((0x00000020&(data))>>5)
#define MIPI_DPHY_REG11_get_Esc_lane1_int_flg(data)                                  ((0x00000020&(data))>>5)
#define MIPI_DPHY_REG11_Esc_lane0_int_flg_shift                                      (4)
#define MIPI_DPHY_REG11_Esc_lane0_int_flg_mask                                       (0x00000010)
#define MIPI_DPHY_REG11_Esc_lane0_int_flg(data)                                      (0x00000010&((data)<<4))
#define MIPI_DPHY_REG11_Esc_lane0_int_flg_src(data)                                  ((0x00000010&(data))>>4)
#define MIPI_DPHY_REG11_get_Esc_lane0_int_flg(data)                                  ((0x00000010&(data))>>4)
#define MIPI_DPHY_REG11_Clk_ulps_int_flg_shift                                       (3)
#define MIPI_DPHY_REG11_Clk_ulps_int_flg_mask                                        (0x00000008)
#define MIPI_DPHY_REG11_Clk_ulps_int_flg(data)                                       (0x00000008&((data)<<3))
#define MIPI_DPHY_REG11_Clk_ulps_int_flg_src(data)                                   ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG11_get_Clk_ulps_int_flg(data)                                   ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG11_Crc16_err_int_flg_shift                                      (2)
#define MIPI_DPHY_REG11_Crc16_err_int_flg_mask                                       (0x00000004)
#define MIPI_DPHY_REG11_Crc16_err_int_flg(data)                                      (0x00000004&((data)<<2))
#define MIPI_DPHY_REG11_Crc16_err_int_flg_src(data)                                  ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG11_get_Crc16_err_int_flg(data)                                  ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG11_Ecc_crt_int_flg_shift                                        (1)
#define MIPI_DPHY_REG11_Ecc_crt_int_flg_mask                                         (0x00000002)
#define MIPI_DPHY_REG11_Ecc_crt_int_flg(data)                                        (0x00000002&((data)<<1))
#define MIPI_DPHY_REG11_Ecc_crt_int_flg_src(data)                                    ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG11_get_Ecc_crt_int_flg(data)                                    ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG11_Ecc_err_int_flg_shift                                        (0)
#define MIPI_DPHY_REG11_Ecc_err_int_flg_mask                                         (0x00000001)
#define MIPI_DPHY_REG11_Ecc_err_int_flg(data)                                        (0x00000001&((data)<<0))
#define MIPI_DPHY_REG11_Ecc_err_int_flg_src(data)                                    ((0x00000001&(data))>>0)
#define MIPI_DPHY_REG11_get_Ecc_err_int_flg(data)                                    ((0x00000001&(data))>>0)


#define MIPI_DPHY_REG12                                                              0x180040B8
#define MIPI_DPHY_REG12_reg_addr                                                     "0xB80040B8"
#define MIPI_DPHY_REG12_reg                                                          0xB80040B8
#define set_MIPI_DPHY_REG12_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG12_reg)=data)
#define get_MIPI_DPHY_REG12_reg   (*((volatile unsigned int*) MIPI_DPHY_REG12_reg))
#define MIPI_DPHY_REG12_inst_adr                                                     "0x002E"
#define MIPI_DPHY_REG12_inst                                                         0x002E
#define MIPI_DPHY_REG12_Num_ecc_err_shift                                            (0)
#define MIPI_DPHY_REG12_Num_ecc_err_mask                                             (0x000000FF)
#define MIPI_DPHY_REG12_Num_ecc_err(data)                                            (0x000000FF&((data)<<0))
#define MIPI_DPHY_REG12_Num_ecc_err_src(data)                                        ((0x000000FF&(data))>>0)
#define MIPI_DPHY_REG12_get_Num_ecc_err(data)                                        ((0x000000FF&(data))>>0)


#define MIPI_DPHY_REG13                                                              0x180040BC
#define MIPI_DPHY_REG13_reg_addr                                                     "0xB80040BC"
#define MIPI_DPHY_REG13_reg                                                          0xB80040BC
#define set_MIPI_DPHY_REG13_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG13_reg)=data)
#define get_MIPI_DPHY_REG13_reg   (*((volatile unsigned int*) MIPI_DPHY_REG13_reg))
#define MIPI_DPHY_REG13_inst_adr                                                     "0x002F"
#define MIPI_DPHY_REG13_inst                                                         0x002F
#define MIPI_DPHY_REG13_Num_ecc_err_shift                                            (0)
#define MIPI_DPHY_REG13_Num_ecc_err_mask                                             (0x000000FF)
#define MIPI_DPHY_REG13_Num_ecc_err(data)                                            (0x000000FF&((data)<<0))
#define MIPI_DPHY_REG13_Num_ecc_err_src(data)                                        ((0x000000FF&(data))>>0)
#define MIPI_DPHY_REG13_get_Num_ecc_err(data)                                        ((0x000000FF&(data))>>0)


#define MIPI_DPHY_REG14                                                              0x180040C0
#define MIPI_DPHY_REG14_reg_addr                                                     "0xB80040C0"
#define MIPI_DPHY_REG14_reg                                                          0xB80040C0
#define set_MIPI_DPHY_REG14_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG14_reg)=data)
#define get_MIPI_DPHY_REG14_reg   (*((volatile unsigned int*) MIPI_DPHY_REG14_reg))
#define MIPI_DPHY_REG14_inst_adr                                                     "0x0030"
#define MIPI_DPHY_REG14_inst                                                         0x0030
#define MIPI_DPHY_REG14_Num_crc_err_shift                                            (0)
#define MIPI_DPHY_REG14_Num_crc_err_mask                                             (0x000000FF)
#define MIPI_DPHY_REG14_Num_crc_err(data)                                            (0x000000FF&((data)<<0))
#define MIPI_DPHY_REG14_Num_crc_err_src(data)                                        ((0x000000FF&(data))>>0)
#define MIPI_DPHY_REG14_get_Num_crc_err(data)                                        ((0x000000FF&(data))>>0)


#define MIPI_DPHY_REG15                                                              0x180040C4
#define MIPI_DPHY_REG15_reg_addr                                                     "0xB80040C4"
#define MIPI_DPHY_REG15_reg                                                          0xB80040C4
#define set_MIPI_DPHY_REG15_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG15_reg)=data)
#define get_MIPI_DPHY_REG15_reg   (*((volatile unsigned int*) MIPI_DPHY_REG15_reg))
#define MIPI_DPHY_REG15_inst_adr                                                     "0x0031"
#define MIPI_DPHY_REG15_inst                                                         0x0031
#define MIPI_DPHY_REG15_Num_crc_err_shift                                            (0)
#define MIPI_DPHY_REG15_Num_crc_err_mask                                             (0x000000FF)
#define MIPI_DPHY_REG15_Num_crc_err(data)                                            (0x000000FF&((data)<<0))
#define MIPI_DPHY_REG15_Num_crc_err_src(data)                                        ((0x000000FF&(data))>>0)
#define MIPI_DPHY_REG15_get_Num_crc_err(data)                                        ((0x000000FF&(data))>>0)


#define MIPI_DPHY_REG16                                                              0x180040C8
#define MIPI_DPHY_REG16_reg_addr                                                     "0xB80040C8"
#define MIPI_DPHY_REG16_reg                                                          0xB80040C8
#define set_MIPI_DPHY_REG16_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG16_reg)=data)
#define get_MIPI_DPHY_REG16_reg   (*((volatile unsigned int*) MIPI_DPHY_REG16_reg))
#define MIPI_DPHY_REG16_inst_adr                                                     "0x0032"
#define MIPI_DPHY_REG16_inst                                                         0x0032
#define MIPI_DPHY_REG16_Clk_term_en_shift                                            (4)
#define MIPI_DPHY_REG16_Clk_term_en_mask                                             (0x00000010)
#define MIPI_DPHY_REG16_Clk_term_en(data)                                            (0x00000010&((data)<<4))
#define MIPI_DPHY_REG16_Clk_term_en_src(data)                                        ((0x00000010&(data))>>4)
#define MIPI_DPHY_REG16_get_Clk_term_en(data)                                        ((0x00000010&(data))>>4)
#define MIPI_DPHY_REG16_Lane3_term_en_shift                                          (3)
#define MIPI_DPHY_REG16_Lane3_term_en_mask                                           (0x00000008)
#define MIPI_DPHY_REG16_Lane3_term_en(data)                                          (0x00000008&((data)<<3))
#define MIPI_DPHY_REG16_Lane3_term_en_src(data)                                      ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG16_get_Lane3_term_en(data)                                      ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG16_Lane2_term_en_shift                                          (2)
#define MIPI_DPHY_REG16_Lane2_term_en_mask                                           (0x00000004)
#define MIPI_DPHY_REG16_Lane2_term_en(data)                                          (0x00000004&((data)<<2))
#define MIPI_DPHY_REG16_Lane2_term_en_src(data)                                      ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG16_get_Lane2_term_en(data)                                      ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG16_Lane1_term_en_shift                                          (1)
#define MIPI_DPHY_REG16_Lane1_term_en_mask                                           (0x00000002)
#define MIPI_DPHY_REG16_Lane1_term_en(data)                                          (0x00000002&((data)<<1))
#define MIPI_DPHY_REG16_Lane1_term_en_src(data)                                      ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG16_get_Lane1_term_en(data)                                      ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG16_Lane0_term_en_shift                                          (0)
#define MIPI_DPHY_REG16_Lane0_term_en_mask                                           (0x00000001)
#define MIPI_DPHY_REG16_Lane0_term_en(data)                                          (0x00000001&((data)<<0))
#define MIPI_DPHY_REG16_Lane0_term_en_src(data)                                      ((0x00000001&(data))>>0)
#define MIPI_DPHY_REG16_get_Lane0_term_en(data)                                      ((0x00000001&(data))>>0)


#define MIPI_DPHY_REG17                                                              0x180040CC
#define MIPI_DPHY_REG17_reg_addr                                                     "0xB80040CC"
#define MIPI_DPHY_REG17_reg                                                          0xB80040CC
#define set_MIPI_DPHY_REG17_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG17_reg)=data)
#define get_MIPI_DPHY_REG17_reg   (*((volatile unsigned int*) MIPI_DPHY_REG17_reg))
#define MIPI_DPHY_REG17_inst_adr                                                     "0x0033"
#define MIPI_DPHY_REG17_inst                                                         0x0033
#define MIPI_DPHY_REG17_Lane3_pwdb_en_shift                                          (3)
#define MIPI_DPHY_REG17_Lane3_pwdb_en_mask                                           (0x00000008)
#define MIPI_DPHY_REG17_Lane3_pwdb_en(data)                                          (0x00000008&((data)<<3))
#define MIPI_DPHY_REG17_Lane3_pwdb_en_src(data)                                      ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG17_get_Lane3_pwdb_en(data)                                      ((0x00000008&(data))>>3)
#define MIPI_DPHY_REG17_Lane2_pwdb_en_shift                                          (2)
#define MIPI_DPHY_REG17_Lane2_pwdb_en_mask                                           (0x00000004)
#define MIPI_DPHY_REG17_Lane2_pwdb_en(data)                                          (0x00000004&((data)<<2))
#define MIPI_DPHY_REG17_Lane2_pwdb_en_src(data)                                      ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG17_get_Lane2_pwdb_en(data)                                      ((0x00000004&(data))>>2)
#define MIPI_DPHY_REG17_Lane1_pwdb_en_shift                                          (1)
#define MIPI_DPHY_REG17_Lane1_pwdb_en_mask                                           (0x00000002)
#define MIPI_DPHY_REG17_Lane1_pwdb_en(data)                                          (0x00000002&((data)<<1))
#define MIPI_DPHY_REG17_Lane1_pwdb_en_src(data)                                      ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG17_get_Lane1_pwdb_en(data)                                      ((0x00000002&(data))>>1)
#define MIPI_DPHY_REG17_Lane0_pwdb_en_shift                                          (0)
#define MIPI_DPHY_REG17_Lane0_pwdb_en_mask                                           (0x00000001)
#define MIPI_DPHY_REG17_Lane0_pwdb_en(data)                                          (0x00000001&((data)<<0))
#define MIPI_DPHY_REG17_Lane0_pwdb_en_src(data)                                      ((0x00000001&(data))>>0)
#define MIPI_DPHY_REG17_get_Lane0_pwdb_en(data)                                      ((0x00000001&(data))>>0)


#define MIPI_DPHY_REG18                                                              0x180040D0
#define MIPI_DPHY_REG18_reg_addr                                                     "0xB80040D0"
#define MIPI_DPHY_REG18_reg                                                          0xB80040D0
#define set_MIPI_DPHY_REG18_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG18_reg)=data)
#define get_MIPI_DPHY_REG18_reg   (*((volatile unsigned int*) MIPI_DPHY_REG18_reg))
#define MIPI_DPHY_REG18_inst_adr                                                     "0x0034"
#define MIPI_DPHY_REG18_inst                                                         0x0034


#define MIPI_DPHY_REG19                                                              0x180040D4
#define MIPI_DPHY_REG19_reg_addr                                                     "0xB80040D4"
#define MIPI_DPHY_REG19_reg                                                          0xB80040D4
#define set_MIPI_DPHY_REG19_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG19_reg)=data)
#define get_MIPI_DPHY_REG19_reg   (*((volatile unsigned int*) MIPI_DPHY_REG19_reg))
#define MIPI_DPHY_REG19_inst_adr                                                     "0x0035"
#define MIPI_DPHY_REG19_inst                                                         0x0035


#define MIPI_DPHY_REG20                                                              0x180040D8
#define MIPI_DPHY_REG20_reg_addr                                                     "0xB80040D8"
#define MIPI_DPHY_REG20_reg                                                          0xB80040D8
#define set_MIPI_DPHY_REG20_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG20_reg)=data)
#define get_MIPI_DPHY_REG20_reg   (*((volatile unsigned int*) MIPI_DPHY_REG20_reg))
#define MIPI_DPHY_REG20_inst_adr                                                     "0x0036"
#define MIPI_DPHY_REG20_inst                                                         0x0036
#define MIPI_DPHY_REG20_Lane0_esc_cod_shift                                          (0)
#define MIPI_DPHY_REG20_Lane0_esc_cod_mask                                           (0x000000FF)
#define MIPI_DPHY_REG20_Lane0_esc_cod(data)                                          (0x000000FF&((data)<<0))
#define MIPI_DPHY_REG20_Lane0_esc_cod_src(data)                                      ((0x000000FF&(data))>>0)
#define MIPI_DPHY_REG20_get_Lane0_esc_cod(data)                                      ((0x000000FF&(data))>>0)


#define MIPI_DPHY_REG21                                                              0x180040DC
#define MIPI_DPHY_REG21_reg_addr                                                     "0xB80040DC"
#define MIPI_DPHY_REG21_reg                                                          0xB80040DC
#define set_MIPI_DPHY_REG21_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG21_reg)=data)
#define get_MIPI_DPHY_REG21_reg   (*((volatile unsigned int*) MIPI_DPHY_REG21_reg))
#define MIPI_DPHY_REG21_inst_adr                                                     "0x0037"
#define MIPI_DPHY_REG21_inst                                                         0x0037
#define MIPI_DPHY_REG21_Lane1_esc_cod_shift                                          (0)
#define MIPI_DPHY_REG21_Lane1_esc_cod_mask                                           (0x000000FF)
#define MIPI_DPHY_REG21_Lane1_esc_cod(data)                                          (0x000000FF&((data)<<0))
#define MIPI_DPHY_REG21_Lane1_esc_cod_src(data)                                      ((0x000000FF&(data))>>0)
#define MIPI_DPHY_REG21_get_Lane1_esc_cod(data)                                      ((0x000000FF&(data))>>0)


#define MIPI_DPHY_REG22                                                              0x180040E0
#define MIPI_DPHY_REG22_reg_addr                                                     "0xB80040E0"
#define MIPI_DPHY_REG22_reg                                                          0xB80040E0
#define set_MIPI_DPHY_REG22_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG22_reg)=data)
#define get_MIPI_DPHY_REG22_reg   (*((volatile unsigned int*) MIPI_DPHY_REG22_reg))
#define MIPI_DPHY_REG22_inst_adr                                                     "0x0038"
#define MIPI_DPHY_REG22_inst                                                         0x0038
#define MIPI_DPHY_REG22_Lane2_esc_cod_shift                                          (0)
#define MIPI_DPHY_REG22_Lane2_esc_cod_mask                                           (0x000000FF)
#define MIPI_DPHY_REG22_Lane2_esc_cod(data)                                          (0x000000FF&((data)<<0))
#define MIPI_DPHY_REG22_Lane2_esc_cod_src(data)                                      ((0x000000FF&(data))>>0)
#define MIPI_DPHY_REG22_get_Lane2_esc_cod(data)                                      ((0x000000FF&(data))>>0)


#define MIPI_DPHY_REG23                                                              0x180040E4
#define MIPI_DPHY_REG23_reg_addr                                                     "0xB80040E4"
#define MIPI_DPHY_REG23_reg                                                          0xB80040E4
#define set_MIPI_DPHY_REG23_reg(data)   (*((volatile unsigned int*) MIPI_DPHY_REG23_reg)=data)
#define get_MIPI_DPHY_REG23_reg   (*((volatile unsigned int*) MIPI_DPHY_REG23_reg))
#define MIPI_DPHY_REG23_inst_adr                                                     "0x0039"
#define MIPI_DPHY_REG23_inst                                                         0x0039
#define MIPI_DPHY_REG23_Lane3_esc_cod_shift                                          (0)
#define MIPI_DPHY_REG23_Lane3_esc_cod_mask                                           (0x000000FF)
#define MIPI_DPHY_REG23_Lane3_esc_cod(data)                                          (0x000000FF&((data)<<0))
#define MIPI_DPHY_REG23_Lane3_esc_cod_src(data)                                      ((0x000000FF&(data))>>0)
#define MIPI_DPHY_REG23_get_Lane3_esc_cod(data)                                      ((0x000000FF&(data))>>0)


#endif
