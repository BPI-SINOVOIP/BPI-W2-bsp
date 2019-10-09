/**************************************************************
// Spec Version                  : 0
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/8/8 16:12:26
***************************************************************/


#ifndef _AIF_REG_H_INCLUDED_
#define _AIF_REG_H_INCLUDED_
#ifdef  _AIF_USE_STRUCT
typedef struct 
{
unsigned int     reg_oapmodel0:3;
unsigned int     reg_oanmodel0:3;
unsigned int     reg_obpmodel0:3;
unsigned int     reg_obnmodel0:3;
unsigned int     reg_ocpmodel0:3;
unsigned int     reg_ocnmodel0:3;
unsigned int     reg_odpmodel0:3;
unsigned int     reg_odnmodel0:3;
unsigned int     reg_oepmodel0:3;
unsigned int     reg_oenmodel0:3;
unsigned int     reserved_0:2;
}AIF_CTRL1;

typedef struct 
{
unsigned int     reg_ofpmodel0:3;
unsigned int     reg_ofnmodel0:3;
unsigned int     reserved_0:26;
}AIF_CTRL2;

typedef struct 
{
unsigned int     reg_eapmodel0:3;
unsigned int     reg_eanmodel0:3;
unsigned int     reg_ebpmodel0:3;
unsigned int     reg_ebnmodel0:3;
unsigned int     reg_ecpmodel0:3;
unsigned int     reg_ecnmodel0:3;
unsigned int     reg_edpmodel0:3;
unsigned int     reg_ednmodel0:3;
unsigned int     reg_eepmodel0:3;
unsigned int     reg_eenmodel0:3;
unsigned int     reserved_0:2;
}AIF_CTRL3;

typedef struct 
{
unsigned int     reg_efpmodel0:3;
unsigned int     reg_efnmodel0:3;
unsigned int     reserved_0:26;
}AIF_CTRL4;

typedef struct 
{
unsigned int     reg_ibhx_sell0:3;
unsigned int     reg_pll_rsl0:3;
unsigned int     reg_ibhn_sell0:3;
unsigned int     reg_ser_sell0:2;
unsigned int     reg_tst_sell0:3;
unsigned int     reserved_0:2;
unsigned int     reg_pll_ipl0:3;
unsigned int     reg_pre_sl0:4;
unsigned int     reg_vcm_sell0:3;
unsigned int     reg_pll_nl0:2;
unsigned int     reg_pll_csl0:2;
unsigned int     reserved_1:2;
}AIF_CTRL5;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     reg_ibtx_sell0:2;
}AIF_CTRL6;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     reg_pll_lvreg:2;
unsigned int     reg_pll_reserved:4;
unsigned int     reg_clk_2xdrvl:1;
unsigned int     reg_ib_powl:1;
unsigned int     reg_pdbl:1;
unsigned int     reserved_1:4;
unsigned int     reg_pll_cpl:1;
unsigned int     reserved_2:2;
unsigned int     reg_pll_powl:1;
unsigned int     reg_pll_reserve1l:1;
unsigned int     reg_pll_rstbl:1;
unsigned int     reg_pll_sel_div2l:1;
unsigned int     reg_pll_vcorstbl:1;
unsigned int     reserved_3:2;
unsigned int     reg_pll_wdrstl:1;
unsigned int     reg_pll_wdsetl:1;
unsigned int     reg_pre_sr_enl:1;
unsigned int     reg_pre_sr_sell:1;
unsigned int     reg_sl:2;
unsigned int     reg_ttlo_2xdrvl:1;
}AIF_CTRL7;

typedef struct 
{
unsigned int     reg_edalagl0:6;
unsigned int     reg_odalagl0:6;
unsigned int     reg_epassrsdsl0:6;
unsigned int     reg_opassrsdsl0:6;
unsigned int     reserved_0:8;
}AIF_CTRL8;

typedef struct 
{
unsigned int     reg_resvrl:24;
unsigned int     reserved_0:8;
}AIF_CTRL9;

typedef struct 
{
unsigned int     reserved_0:32;
}AIF_CTRLA;

typedef struct 
{
unsigned int     reg_slew:24;
unsigned int     reserved_0:8;
}AIF_CTRLB;

typedef struct 
{
unsigned int     reg_shapeh:32;
}AIF_CTRLC;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     reg_shapel:4;
}AIF_CTRLD;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     reg_wdol:1;
}AIF_CTRLE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     reg_pll_ldo_powl:1;
}AIF_CTRLF;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     orsdsttlinfl0:2;
unsigned int     orsdsttlinel0:2;
unsigned int     orsdsttlindl0:2;
unsigned int     orsdsttlincl0:2;
unsigned int     orsdsttlinbl0:2;
unsigned int     orsdsttlinal0:2;
unsigned int     ersdsttlinfl0:2;
unsigned int     ersdsttlinel0:2;
unsigned int     ersdsttlindl0:2;
unsigned int     ersdsttlincl0:2;
unsigned int     ersdsttlinbl0:2;
unsigned int     ersdsttlinal0:2;
}AIF_TTLO;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     op2dfl0:2;
unsigned int     op2del0:2;
unsigned int     op2ddl0:2;
unsigned int     op2dcl0:2;
unsigned int     op2dbl0:2;
unsigned int     op2dal0:2;
unsigned int     ep2dfl0:2;
unsigned int     ep2del0:2;
unsigned int     ep2ddl0:2;
unsigned int     ep2dcl0:2;
unsigned int     ep2dbl0:2;
unsigned int     ep2dal0:2;
}AIF_TTLI;

typedef struct 
{
unsigned int     dummy:32;
}AIF_CTRLG;

#endif

#define AIF_CTRL1                                                                    0x18009010
#define AIF_CTRL1_reg_addr                                                           "0xB8009010"
#define AIF_CTRL1_reg                                                                0xB8009010
#define set_AIF_CTRL1_reg(data)   (*((volatile unsigned int*) AIF_CTRL1_reg)=data)
#define get_AIF_CTRL1_reg   (*((volatile unsigned int*) AIF_CTRL1_reg))
#define AIF_CTRL1_inst_adr                                                           "0x0004"
#define AIF_CTRL1_inst                                                               0x0004
#define AIF_CTRL1_reg_oapmodel0_shift                                                (29)
#define AIF_CTRL1_reg_oapmodel0_mask                                                 (0xE0000000)
#define AIF_CTRL1_reg_oapmodel0(data)                                                (0xE0000000&((data)<<29))
#define AIF_CTRL1_reg_oapmodel0_src(data)                                            ((0xE0000000&(data))>>29)
#define AIF_CTRL1_get_reg_oapmodel0(data)                                            ((0xE0000000&(data))>>29)
#define AIF_CTRL1_reg_oanmodel0_shift                                                (26)
#define AIF_CTRL1_reg_oanmodel0_mask                                                 (0x1C000000)
#define AIF_CTRL1_reg_oanmodel0(data)                                                (0x1C000000&((data)<<26))
#define AIF_CTRL1_reg_oanmodel0_src(data)                                            ((0x1C000000&(data))>>26)
#define AIF_CTRL1_get_reg_oanmodel0(data)                                            ((0x1C000000&(data))>>26)
#define AIF_CTRL1_reg_obpmodel0_shift                                                (23)
#define AIF_CTRL1_reg_obpmodel0_mask                                                 (0x03800000)
#define AIF_CTRL1_reg_obpmodel0(data)                                                (0x03800000&((data)<<23))
#define AIF_CTRL1_reg_obpmodel0_src(data)                                            ((0x03800000&(data))>>23)
#define AIF_CTRL1_get_reg_obpmodel0(data)                                            ((0x03800000&(data))>>23)
#define AIF_CTRL1_reg_obnmodel0_shift                                                (20)
#define AIF_CTRL1_reg_obnmodel0_mask                                                 (0x00700000)
#define AIF_CTRL1_reg_obnmodel0(data)                                                (0x00700000&((data)<<20))
#define AIF_CTRL1_reg_obnmodel0_src(data)                                            ((0x00700000&(data))>>20)
#define AIF_CTRL1_get_reg_obnmodel0(data)                                            ((0x00700000&(data))>>20)
#define AIF_CTRL1_reg_ocpmodel0_shift                                                (17)
#define AIF_CTRL1_reg_ocpmodel0_mask                                                 (0x000E0000)
#define AIF_CTRL1_reg_ocpmodel0(data)                                                (0x000E0000&((data)<<17))
#define AIF_CTRL1_reg_ocpmodel0_src(data)                                            ((0x000E0000&(data))>>17)
#define AIF_CTRL1_get_reg_ocpmodel0(data)                                            ((0x000E0000&(data))>>17)
#define AIF_CTRL1_reg_ocnmodel0_shift                                                (14)
#define AIF_CTRL1_reg_ocnmodel0_mask                                                 (0x0001C000)
#define AIF_CTRL1_reg_ocnmodel0(data)                                                (0x0001C000&((data)<<14))
#define AIF_CTRL1_reg_ocnmodel0_src(data)                                            ((0x0001C000&(data))>>14)
#define AIF_CTRL1_get_reg_ocnmodel0(data)                                            ((0x0001C000&(data))>>14)
#define AIF_CTRL1_reg_odpmodel0_shift                                                (11)
#define AIF_CTRL1_reg_odpmodel0_mask                                                 (0x00003800)
#define AIF_CTRL1_reg_odpmodel0(data)                                                (0x00003800&((data)<<11))
#define AIF_CTRL1_reg_odpmodel0_src(data)                                            ((0x00003800&(data))>>11)
#define AIF_CTRL1_get_reg_odpmodel0(data)                                            ((0x00003800&(data))>>11)
#define AIF_CTRL1_reg_odnmodel0_shift                                                (8)
#define AIF_CTRL1_reg_odnmodel0_mask                                                 (0x00000700)
#define AIF_CTRL1_reg_odnmodel0(data)                                                (0x00000700&((data)<<8))
#define AIF_CTRL1_reg_odnmodel0_src(data)                                            ((0x00000700&(data))>>8)
#define AIF_CTRL1_get_reg_odnmodel0(data)                                            ((0x00000700&(data))>>8)
#define AIF_CTRL1_reg_oepmodel0_shift                                                (5)
#define AIF_CTRL1_reg_oepmodel0_mask                                                 (0x000000E0)
#define AIF_CTRL1_reg_oepmodel0(data)                                                (0x000000E0&((data)<<5))
#define AIF_CTRL1_reg_oepmodel0_src(data)                                            ((0x000000E0&(data))>>5)
#define AIF_CTRL1_get_reg_oepmodel0(data)                                            ((0x000000E0&(data))>>5)
#define AIF_CTRL1_reg_oenmodel0_shift                                                (2)
#define AIF_CTRL1_reg_oenmodel0_mask                                                 (0x0000001C)
#define AIF_CTRL1_reg_oenmodel0(data)                                                (0x0000001C&((data)<<2))
#define AIF_CTRL1_reg_oenmodel0_src(data)                                            ((0x0000001C&(data))>>2)
#define AIF_CTRL1_get_reg_oenmodel0(data)                                            ((0x0000001C&(data))>>2)


#define AIF_CTRL2                                                                    0x18009014
#define AIF_CTRL2_reg_addr                                                           "0xB8009014"
#define AIF_CTRL2_reg                                                                0xB8009014
#define set_AIF_CTRL2_reg(data)   (*((volatile unsigned int*) AIF_CTRL2_reg)=data)
#define get_AIF_CTRL2_reg   (*((volatile unsigned int*) AIF_CTRL2_reg))
#define AIF_CTRL2_inst_adr                                                           "0x0005"
#define AIF_CTRL2_inst                                                               0x0005
#define AIF_CTRL2_reg_ofpmodel0_shift                                                (29)
#define AIF_CTRL2_reg_ofpmodel0_mask                                                 (0xE0000000)
#define AIF_CTRL2_reg_ofpmodel0(data)                                                (0xE0000000&((data)<<29))
#define AIF_CTRL2_reg_ofpmodel0_src(data)                                            ((0xE0000000&(data))>>29)
#define AIF_CTRL2_get_reg_ofpmodel0(data)                                            ((0xE0000000&(data))>>29)
#define AIF_CTRL2_reg_ofnmodel0_shift                                                (26)
#define AIF_CTRL2_reg_ofnmodel0_mask                                                 (0x1C000000)
#define AIF_CTRL2_reg_ofnmodel0(data)                                                (0x1C000000&((data)<<26))
#define AIF_CTRL2_reg_ofnmodel0_src(data)                                            ((0x1C000000&(data))>>26)
#define AIF_CTRL2_get_reg_ofnmodel0(data)                                            ((0x1C000000&(data))>>26)


#define AIF_CTRL3                                                                    0x18009018
#define AIF_CTRL3_reg_addr                                                           "0xB8009018"
#define AIF_CTRL3_reg                                                                0xB8009018
#define set_AIF_CTRL3_reg(data)   (*((volatile unsigned int*) AIF_CTRL3_reg)=data)
#define get_AIF_CTRL3_reg   (*((volatile unsigned int*) AIF_CTRL3_reg))
#define AIF_CTRL3_inst_adr                                                           "0x0006"
#define AIF_CTRL3_inst                                                               0x0006
#define AIF_CTRL3_reg_eapmodel0_shift                                                (29)
#define AIF_CTRL3_reg_eapmodel0_mask                                                 (0xE0000000)
#define AIF_CTRL3_reg_eapmodel0(data)                                                (0xE0000000&((data)<<29))
#define AIF_CTRL3_reg_eapmodel0_src(data)                                            ((0xE0000000&(data))>>29)
#define AIF_CTRL3_get_reg_eapmodel0(data)                                            ((0xE0000000&(data))>>29)
#define AIF_CTRL3_reg_eanmodel0_shift                                                (26)
#define AIF_CTRL3_reg_eanmodel0_mask                                                 (0x1C000000)
#define AIF_CTRL3_reg_eanmodel0(data)                                                (0x1C000000&((data)<<26))
#define AIF_CTRL3_reg_eanmodel0_src(data)                                            ((0x1C000000&(data))>>26)
#define AIF_CTRL3_get_reg_eanmodel0(data)                                            ((0x1C000000&(data))>>26)
#define AIF_CTRL3_reg_ebpmodel0_shift                                                (23)
#define AIF_CTRL3_reg_ebpmodel0_mask                                                 (0x03800000)
#define AIF_CTRL3_reg_ebpmodel0(data)                                                (0x03800000&((data)<<23))
#define AIF_CTRL3_reg_ebpmodel0_src(data)                                            ((0x03800000&(data))>>23)
#define AIF_CTRL3_get_reg_ebpmodel0(data)                                            ((0x03800000&(data))>>23)
#define AIF_CTRL3_reg_ebnmodel0_shift                                                (20)
#define AIF_CTRL3_reg_ebnmodel0_mask                                                 (0x00700000)
#define AIF_CTRL3_reg_ebnmodel0(data)                                                (0x00700000&((data)<<20))
#define AIF_CTRL3_reg_ebnmodel0_src(data)                                            ((0x00700000&(data))>>20)
#define AIF_CTRL3_get_reg_ebnmodel0(data)                                            ((0x00700000&(data))>>20)
#define AIF_CTRL3_reg_ecpmodel0_shift                                                (17)
#define AIF_CTRL3_reg_ecpmodel0_mask                                                 (0x000E0000)
#define AIF_CTRL3_reg_ecpmodel0(data)                                                (0x000E0000&((data)<<17))
#define AIF_CTRL3_reg_ecpmodel0_src(data)                                            ((0x000E0000&(data))>>17)
#define AIF_CTRL3_get_reg_ecpmodel0(data)                                            ((0x000E0000&(data))>>17)
#define AIF_CTRL3_reg_ecnmodel0_shift                                                (14)
#define AIF_CTRL3_reg_ecnmodel0_mask                                                 (0x0001C000)
#define AIF_CTRL3_reg_ecnmodel0(data)                                                (0x0001C000&((data)<<14))
#define AIF_CTRL3_reg_ecnmodel0_src(data)                                            ((0x0001C000&(data))>>14)
#define AIF_CTRL3_get_reg_ecnmodel0(data)                                            ((0x0001C000&(data))>>14)
#define AIF_CTRL3_reg_edpmodel0_shift                                                (11)
#define AIF_CTRL3_reg_edpmodel0_mask                                                 (0x00003800)
#define AIF_CTRL3_reg_edpmodel0(data)                                                (0x00003800&((data)<<11))
#define AIF_CTRL3_reg_edpmodel0_src(data)                                            ((0x00003800&(data))>>11)
#define AIF_CTRL3_get_reg_edpmodel0(data)                                            ((0x00003800&(data))>>11)
#define AIF_CTRL3_reg_ednmodel0_shift                                                (8)
#define AIF_CTRL3_reg_ednmodel0_mask                                                 (0x00000700)
#define AIF_CTRL3_reg_ednmodel0(data)                                                (0x00000700&((data)<<8))
#define AIF_CTRL3_reg_ednmodel0_src(data)                                            ((0x00000700&(data))>>8)
#define AIF_CTRL3_get_reg_ednmodel0(data)                                            ((0x00000700&(data))>>8)
#define AIF_CTRL3_reg_eepmodel0_shift                                                (5)
#define AIF_CTRL3_reg_eepmodel0_mask                                                 (0x000000E0)
#define AIF_CTRL3_reg_eepmodel0(data)                                                (0x000000E0&((data)<<5))
#define AIF_CTRL3_reg_eepmodel0_src(data)                                            ((0x000000E0&(data))>>5)
#define AIF_CTRL3_get_reg_eepmodel0(data)                                            ((0x000000E0&(data))>>5)
#define AIF_CTRL3_reg_eenmodel0_shift                                                (2)
#define AIF_CTRL3_reg_eenmodel0_mask                                                 (0x0000001C)
#define AIF_CTRL3_reg_eenmodel0(data)                                                (0x0000001C&((data)<<2))
#define AIF_CTRL3_reg_eenmodel0_src(data)                                            ((0x0000001C&(data))>>2)
#define AIF_CTRL3_get_reg_eenmodel0(data)                                            ((0x0000001C&(data))>>2)


#define AIF_CTRL4                                                                    0x1800901C
#define AIF_CTRL4_reg_addr                                                           "0xB800901C"
#define AIF_CTRL4_reg                                                                0xB800901C
#define set_AIF_CTRL4_reg(data)   (*((volatile unsigned int*) AIF_CTRL4_reg)=data)
#define get_AIF_CTRL4_reg   (*((volatile unsigned int*) AIF_CTRL4_reg))
#define AIF_CTRL4_inst_adr                                                           "0x0007"
#define AIF_CTRL4_inst                                                               0x0007
#define AIF_CTRL4_reg_efpmodel0_shift                                                (29)
#define AIF_CTRL4_reg_efpmodel0_mask                                                 (0xE0000000)
#define AIF_CTRL4_reg_efpmodel0(data)                                                (0xE0000000&((data)<<29))
#define AIF_CTRL4_reg_efpmodel0_src(data)                                            ((0xE0000000&(data))>>29)
#define AIF_CTRL4_get_reg_efpmodel0(data)                                            ((0xE0000000&(data))>>29)
#define AIF_CTRL4_reg_efnmodel0_shift                                                (26)
#define AIF_CTRL4_reg_efnmodel0_mask                                                 (0x1C000000)
#define AIF_CTRL4_reg_efnmodel0(data)                                                (0x1C000000&((data)<<26))
#define AIF_CTRL4_reg_efnmodel0_src(data)                                            ((0x1C000000&(data))>>26)
#define AIF_CTRL4_get_reg_efnmodel0(data)                                            ((0x1C000000&(data))>>26)


#define AIF_CTRL5                                                                    0x18009020
#define AIF_CTRL5_reg_addr                                                           "0xB8009020"
#define AIF_CTRL5_reg                                                                0xB8009020
#define set_AIF_CTRL5_reg(data)   (*((volatile unsigned int*) AIF_CTRL5_reg)=data)
#define get_AIF_CTRL5_reg   (*((volatile unsigned int*) AIF_CTRL5_reg))
#define AIF_CTRL5_inst_adr                                                           "0x0008"
#define AIF_CTRL5_inst                                                               0x0008
#define AIF_CTRL5_reg_ibhx_sell0_shift                                               (29)
#define AIF_CTRL5_reg_ibhx_sell0_mask                                                (0xE0000000)
#define AIF_CTRL5_reg_ibhx_sell0(data)                                               (0xE0000000&((data)<<29))
#define AIF_CTRL5_reg_ibhx_sell0_src(data)                                           ((0xE0000000&(data))>>29)
#define AIF_CTRL5_get_reg_ibhx_sell0(data)                                           ((0xE0000000&(data))>>29)
#define AIF_CTRL5_reg_pll_rsl0_shift                                                 (26)
#define AIF_CTRL5_reg_pll_rsl0_mask                                                  (0x1C000000)
#define AIF_CTRL5_reg_pll_rsl0(data)                                                 (0x1C000000&((data)<<26))
#define AIF_CTRL5_reg_pll_rsl0_src(data)                                             ((0x1C000000&(data))>>26)
#define AIF_CTRL5_get_reg_pll_rsl0(data)                                             ((0x1C000000&(data))>>26)
#define AIF_CTRL5_reg_ibhn_sell0_shift                                               (23)
#define AIF_CTRL5_reg_ibhn_sell0_mask                                                (0x03800000)
#define AIF_CTRL5_reg_ibhn_sell0(data)                                               (0x03800000&((data)<<23))
#define AIF_CTRL5_reg_ibhn_sell0_src(data)                                           ((0x03800000&(data))>>23)
#define AIF_CTRL5_get_reg_ibhn_sell0(data)                                           ((0x03800000&(data))>>23)
#define AIF_CTRL5_reg_ser_sell0_shift                                                (21)
#define AIF_CTRL5_reg_ser_sell0_mask                                                 (0x00600000)
#define AIF_CTRL5_reg_ser_sell0(data)                                                (0x00600000&((data)<<21))
#define AIF_CTRL5_reg_ser_sell0_src(data)                                            ((0x00600000&(data))>>21)
#define AIF_CTRL5_get_reg_ser_sell0(data)                                            ((0x00600000&(data))>>21)
#define AIF_CTRL5_reg_tst_sell0_shift                                                (18)
#define AIF_CTRL5_reg_tst_sell0_mask                                                 (0x001C0000)
#define AIF_CTRL5_reg_tst_sell0(data)                                                (0x001C0000&((data)<<18))
#define AIF_CTRL5_reg_tst_sell0_src(data)                                            ((0x001C0000&(data))>>18)
#define AIF_CTRL5_get_reg_tst_sell0(data)                                            ((0x001C0000&(data))>>18)
#define AIF_CTRL5_reg_pll_ipl0_shift                                                 (13)
#define AIF_CTRL5_reg_pll_ipl0_mask                                                  (0x0000E000)
#define AIF_CTRL5_reg_pll_ipl0(data)                                                 (0x0000E000&((data)<<13))
#define AIF_CTRL5_reg_pll_ipl0_src(data)                                             ((0x0000E000&(data))>>13)
#define AIF_CTRL5_get_reg_pll_ipl0(data)                                             ((0x0000E000&(data))>>13)
#define AIF_CTRL5_reg_pre_sl0_shift                                                  (9)
#define AIF_CTRL5_reg_pre_sl0_mask                                                   (0x00001E00)
#define AIF_CTRL5_reg_pre_sl0(data)                                                  (0x00001E00&((data)<<9))
#define AIF_CTRL5_reg_pre_sl0_src(data)                                              ((0x00001E00&(data))>>9)
#define AIF_CTRL5_get_reg_pre_sl0(data)                                              ((0x00001E00&(data))>>9)
#define AIF_CTRL5_reg_vcm_sell0_shift                                                (6)
#define AIF_CTRL5_reg_vcm_sell0_mask                                                 (0x000001C0)
#define AIF_CTRL5_reg_vcm_sell0(data)                                                (0x000001C0&((data)<<6))
#define AIF_CTRL5_reg_vcm_sell0_src(data)                                            ((0x000001C0&(data))>>6)
#define AIF_CTRL5_get_reg_vcm_sell0(data)                                            ((0x000001C0&(data))>>6)
#define AIF_CTRL5_reg_pll_nl0_shift                                                  (4)
#define AIF_CTRL5_reg_pll_nl0_mask                                                   (0x00000030)
#define AIF_CTRL5_reg_pll_nl0(data)                                                  (0x00000030&((data)<<4))
#define AIF_CTRL5_reg_pll_nl0_src(data)                                              ((0x00000030&(data))>>4)
#define AIF_CTRL5_get_reg_pll_nl0(data)                                              ((0x00000030&(data))>>4)
#define AIF_CTRL5_reg_pll_csl0_shift                                                 (2)
#define AIF_CTRL5_reg_pll_csl0_mask                                                  (0x0000000C)
#define AIF_CTRL5_reg_pll_csl0(data)                                                 (0x0000000C&((data)<<2))
#define AIF_CTRL5_reg_pll_csl0_src(data)                                             ((0x0000000C&(data))>>2)
#define AIF_CTRL5_get_reg_pll_csl0(data)                                             ((0x0000000C&(data))>>2)


#define AIF_CTRL6                                                                    0x18009024
#define AIF_CTRL6_reg_addr                                                           "0xB8009024"
#define AIF_CTRL6_reg                                                                0xB8009024
#define set_AIF_CTRL6_reg(data)   (*((volatile unsigned int*) AIF_CTRL6_reg)=data)
#define get_AIF_CTRL6_reg   (*((volatile unsigned int*) AIF_CTRL6_reg))
#define AIF_CTRL6_inst_adr                                                           "0x0009"
#define AIF_CTRL6_inst                                                               0x0009
#define AIF_CTRL6_reg_ibtx_sell0_shift                                               (0)
#define AIF_CTRL6_reg_ibtx_sell0_mask                                                (0x00000003)
#define AIF_CTRL6_reg_ibtx_sell0(data)                                               (0x00000003&((data)<<0))
#define AIF_CTRL6_reg_ibtx_sell0_src(data)                                           ((0x00000003&(data))>>0)
#define AIF_CTRL6_get_reg_ibtx_sell0(data)                                           ((0x00000003&(data))>>0)


#define AIF_CTRL7                                                                    0x18009028
#define AIF_CTRL7_reg_addr                                                           "0xB8009028"
#define AIF_CTRL7_reg                                                                0xB8009028
#define set_AIF_CTRL7_reg(data)   (*((volatile unsigned int*) AIF_CTRL7_reg)=data)
#define get_AIF_CTRL7_reg   (*((volatile unsigned int*) AIF_CTRL7_reg))
#define AIF_CTRL7_inst_adr                                                           "0x000A"
#define AIF_CTRL7_inst                                                               0x000A
#define AIF_CTRL7_reg_pll_lvreg_shift                                                (28)
#define AIF_CTRL7_reg_pll_lvreg_mask                                                 (0x30000000)
#define AIF_CTRL7_reg_pll_lvreg(data)                                                (0x30000000&((data)<<28))
#define AIF_CTRL7_reg_pll_lvreg_src(data)                                            ((0x30000000&(data))>>28)
#define AIF_CTRL7_get_reg_pll_lvreg(data)                                            ((0x30000000&(data))>>28)
#define AIF_CTRL7_reg_pll_reserved_shift                                             (24)
#define AIF_CTRL7_reg_pll_reserved_mask                                              (0x0F000000)
#define AIF_CTRL7_reg_pll_reserved(data)                                             (0x0F000000&((data)<<24))
#define AIF_CTRL7_reg_pll_reserved_src(data)                                         ((0x0F000000&(data))>>24)
#define AIF_CTRL7_get_reg_pll_reserved(data)                                         ((0x0F000000&(data))>>24)
#define AIF_CTRL7_reg_clk_2xdrvl_shift                                               (23)
#define AIF_CTRL7_reg_clk_2xdrvl_mask                                                (0x00800000)
#define AIF_CTRL7_reg_clk_2xdrvl(data)                                               (0x00800000&((data)<<23))
#define AIF_CTRL7_reg_clk_2xdrvl_src(data)                                           ((0x00800000&(data))>>23)
#define AIF_CTRL7_get_reg_clk_2xdrvl(data)                                           ((0x00800000&(data))>>23)
#define AIF_CTRL7_reg_ib_powl_shift                                                  (22)
#define AIF_CTRL7_reg_ib_powl_mask                                                   (0x00400000)
#define AIF_CTRL7_reg_ib_powl(data)                                                  (0x00400000&((data)<<22))
#define AIF_CTRL7_reg_ib_powl_src(data)                                              ((0x00400000&(data))>>22)
#define AIF_CTRL7_get_reg_ib_powl(data)                                              ((0x00400000&(data))>>22)
#define AIF_CTRL7_reg_pdbl_shift                                                     (21)
#define AIF_CTRL7_reg_pdbl_mask                                                      (0x00200000)
#define AIF_CTRL7_reg_pdbl(data)                                                     (0x00200000&((data)<<21))
#define AIF_CTRL7_reg_pdbl_src(data)                                                 ((0x00200000&(data))>>21)
#define AIF_CTRL7_get_reg_pdbl(data)                                                 ((0x00200000&(data))>>21)
#define AIF_CTRL7_reg_pll_cpl_shift                                                  (16)
#define AIF_CTRL7_reg_pll_cpl_mask                                                   (0x00010000)
#define AIF_CTRL7_reg_pll_cpl(data)                                                  (0x00010000&((data)<<16))
#define AIF_CTRL7_reg_pll_cpl_src(data)                                              ((0x00010000&(data))>>16)
#define AIF_CTRL7_get_reg_pll_cpl(data)                                              ((0x00010000&(data))>>16)
#define AIF_CTRL7_reg_pll_powl_shift                                                 (13)
#define AIF_CTRL7_reg_pll_powl_mask                                                  (0x00002000)
#define AIF_CTRL7_reg_pll_powl(data)                                                 (0x00002000&((data)<<13))
#define AIF_CTRL7_reg_pll_powl_src(data)                                             ((0x00002000&(data))>>13)
#define AIF_CTRL7_get_reg_pll_powl(data)                                             ((0x00002000&(data))>>13)
#define AIF_CTRL7_reg_pll_reserve1l_shift                                            (12)
#define AIF_CTRL7_reg_pll_reserve1l_mask                                             (0x00001000)
#define AIF_CTRL7_reg_pll_reserve1l(data)                                            (0x00001000&((data)<<12))
#define AIF_CTRL7_reg_pll_reserve1l_src(data)                                        ((0x00001000&(data))>>12)
#define AIF_CTRL7_get_reg_pll_reserve1l(data)                                        ((0x00001000&(data))>>12)
#define AIF_CTRL7_reg_pll_rstbl_shift                                                (11)
#define AIF_CTRL7_reg_pll_rstbl_mask                                                 (0x00000800)
#define AIF_CTRL7_reg_pll_rstbl(data)                                                (0x00000800&((data)<<11))
#define AIF_CTRL7_reg_pll_rstbl_src(data)                                            ((0x00000800&(data))>>11)
#define AIF_CTRL7_get_reg_pll_rstbl(data)                                            ((0x00000800&(data))>>11)
#define AIF_CTRL7_reg_pll_sel_div2l_shift                                            (10)
#define AIF_CTRL7_reg_pll_sel_div2l_mask                                             (0x00000400)
#define AIF_CTRL7_reg_pll_sel_div2l(data)                                            (0x00000400&((data)<<10))
#define AIF_CTRL7_reg_pll_sel_div2l_src(data)                                        ((0x00000400&(data))>>10)
#define AIF_CTRL7_get_reg_pll_sel_div2l(data)                                        ((0x00000400&(data))>>10)
#define AIF_CTRL7_reg_pll_vcorstbl_shift                                             (9)
#define AIF_CTRL7_reg_pll_vcorstbl_mask                                              (0x00000200)
#define AIF_CTRL7_reg_pll_vcorstbl(data)                                             (0x00000200&((data)<<9))
#define AIF_CTRL7_reg_pll_vcorstbl_src(data)                                         ((0x00000200&(data))>>9)
#define AIF_CTRL7_get_reg_pll_vcorstbl(data)                                         ((0x00000200&(data))>>9)
#define AIF_CTRL7_reg_pll_wdrstl_shift                                               (6)
#define AIF_CTRL7_reg_pll_wdrstl_mask                                                (0x00000040)
#define AIF_CTRL7_reg_pll_wdrstl(data)                                               (0x00000040&((data)<<6))
#define AIF_CTRL7_reg_pll_wdrstl_src(data)                                           ((0x00000040&(data))>>6)
#define AIF_CTRL7_get_reg_pll_wdrstl(data)                                           ((0x00000040&(data))>>6)
#define AIF_CTRL7_reg_pll_wdsetl_shift                                               (5)
#define AIF_CTRL7_reg_pll_wdsetl_mask                                                (0x00000020)
#define AIF_CTRL7_reg_pll_wdsetl(data)                                               (0x00000020&((data)<<5))
#define AIF_CTRL7_reg_pll_wdsetl_src(data)                                           ((0x00000020&(data))>>5)
#define AIF_CTRL7_get_reg_pll_wdsetl(data)                                           ((0x00000020&(data))>>5)
#define AIF_CTRL7_reg_pre_sr_enl_shift                                               (4)
#define AIF_CTRL7_reg_pre_sr_enl_mask                                                (0x00000010)
#define AIF_CTRL7_reg_pre_sr_enl(data)                                               (0x00000010&((data)<<4))
#define AIF_CTRL7_reg_pre_sr_enl_src(data)                                           ((0x00000010&(data))>>4)
#define AIF_CTRL7_get_reg_pre_sr_enl(data)                                           ((0x00000010&(data))>>4)
#define AIF_CTRL7_reg_pre_sr_sell_shift                                              (3)
#define AIF_CTRL7_reg_pre_sr_sell_mask                                               (0x00000008)
#define AIF_CTRL7_reg_pre_sr_sell(data)                                              (0x00000008&((data)<<3))
#define AIF_CTRL7_reg_pre_sr_sell_src(data)                                          ((0x00000008&(data))>>3)
#define AIF_CTRL7_get_reg_pre_sr_sell(data)                                          ((0x00000008&(data))>>3)
#define AIF_CTRL7_reg_sl_shift                                                       (1)
#define AIF_CTRL7_reg_sl_mask                                                        (0x00000006)
#define AIF_CTRL7_reg_sl(data)                                                       (0x00000006&((data)<<1))
#define AIF_CTRL7_reg_sl_src(data)                                                   ((0x00000006&(data))>>1)
#define AIF_CTRL7_get_reg_sl(data)                                                   ((0x00000006&(data))>>1)
#define AIF_CTRL7_reg_ttlo_2xdrvl_shift                                              (0)
#define AIF_CTRL7_reg_ttlo_2xdrvl_mask                                               (0x00000001)
#define AIF_CTRL7_reg_ttlo_2xdrvl(data)                                              (0x00000001&((data)<<0))
#define AIF_CTRL7_reg_ttlo_2xdrvl_src(data)                                          ((0x00000001&(data))>>0)
#define AIF_CTRL7_get_reg_ttlo_2xdrvl(data)                                          ((0x00000001&(data))>>0)


#define AIF_CTRL8                                                                    0x1800902C
#define AIF_CTRL8_reg_addr                                                           "0xB800902C"
#define AIF_CTRL8_reg                                                                0xB800902C
#define set_AIF_CTRL8_reg(data)   (*((volatile unsigned int*) AIF_CTRL8_reg)=data)
#define get_AIF_CTRL8_reg   (*((volatile unsigned int*) AIF_CTRL8_reg))
#define AIF_CTRL8_inst_adr                                                           "0x000B"
#define AIF_CTRL8_inst                                                               0x000B
#define AIF_CTRL8_reg_edalagl0_shift                                                 (26)
#define AIF_CTRL8_reg_edalagl0_mask                                                  (0xFC000000)
#define AIF_CTRL8_reg_edalagl0(data)                                                 (0xFC000000&((data)<<26))
#define AIF_CTRL8_reg_edalagl0_src(data)                                             ((0xFC000000&(data))>>26)
#define AIF_CTRL8_get_reg_edalagl0(data)                                             ((0xFC000000&(data))>>26)
#define AIF_CTRL8_reg_odalagl0_shift                                                 (20)
#define AIF_CTRL8_reg_odalagl0_mask                                                  (0x03F00000)
#define AIF_CTRL8_reg_odalagl0(data)                                                 (0x03F00000&((data)<<20))
#define AIF_CTRL8_reg_odalagl0_src(data)                                             ((0x03F00000&(data))>>20)
#define AIF_CTRL8_get_reg_odalagl0(data)                                             ((0x03F00000&(data))>>20)
#define AIF_CTRL8_reg_epassrsdsl0_shift                                              (14)
#define AIF_CTRL8_reg_epassrsdsl0_mask                                               (0x000FC000)
#define AIF_CTRL8_reg_epassrsdsl0(data)                                              (0x000FC000&((data)<<14))
#define AIF_CTRL8_reg_epassrsdsl0_src(data)                                          ((0x000FC000&(data))>>14)
#define AIF_CTRL8_get_reg_epassrsdsl0(data)                                          ((0x000FC000&(data))>>14)
#define AIF_CTRL8_reg_opassrsdsl0_shift                                              (8)
#define AIF_CTRL8_reg_opassrsdsl0_mask                                               (0x00003F00)
#define AIF_CTRL8_reg_opassrsdsl0(data)                                              (0x00003F00&((data)<<8))
#define AIF_CTRL8_reg_opassrsdsl0_src(data)                                          ((0x00003F00&(data))>>8)
#define AIF_CTRL8_get_reg_opassrsdsl0(data)                                          ((0x00003F00&(data))>>8)


#define AIF_CTRL9                                                                    0x18009030
#define AIF_CTRL9_reg_addr                                                           "0xB8009030"
#define AIF_CTRL9_reg                                                                0xB8009030
#define set_AIF_CTRL9_reg(data)   (*((volatile unsigned int*) AIF_CTRL9_reg)=data)
#define get_AIF_CTRL9_reg   (*((volatile unsigned int*) AIF_CTRL9_reg))
#define AIF_CTRL9_inst_adr                                                           "0x000C"
#define AIF_CTRL9_inst                                                               0x000C
#define AIF_CTRL9_reg_resvrl_shift                                                   (8)
#define AIF_CTRL9_reg_resvrl_mask                                                    (0xFFFFFF00)
#define AIF_CTRL9_reg_resvrl(data)                                                   (0xFFFFFF00&((data)<<8))
#define AIF_CTRL9_reg_resvrl_src(data)                                               ((0xFFFFFF00&(data))>>8)
#define AIF_CTRL9_get_reg_resvrl(data)                                               ((0xFFFFFF00&(data))>>8)


#define AIF_CTRLA                                                                    0x18009034
#define AIF_CTRLA_reg_addr                                                           "0xB8009034"
#define AIF_CTRLA_reg                                                                0xB8009034
#define set_AIF_CTRLA_reg(data)   (*((volatile unsigned int*) AIF_CTRLA_reg)=data)
#define get_AIF_CTRLA_reg   (*((volatile unsigned int*) AIF_CTRLA_reg))
#define AIF_CTRLA_inst_adr                                                           "0x000D"
#define AIF_CTRLA_inst                                                               0x000D


#define AIF_CTRLB                                                                    0x18009038
#define AIF_CTRLB_reg_addr                                                           "0xB8009038"
#define AIF_CTRLB_reg                                                                0xB8009038
#define set_AIF_CTRLB_reg(data)   (*((volatile unsigned int*) AIF_CTRLB_reg)=data)
#define get_AIF_CTRLB_reg   (*((volatile unsigned int*) AIF_CTRLB_reg))
#define AIF_CTRLB_inst_adr                                                           "0x000E"
#define AIF_CTRLB_inst                                                               0x000E
#define AIF_CTRLB_reg_slew_shift                                                     (8)
#define AIF_CTRLB_reg_slew_mask                                                      (0xFFFFFF00)
#define AIF_CTRLB_reg_slew(data)                                                     (0xFFFFFF00&((data)<<8))
#define AIF_CTRLB_reg_slew_src(data)                                                 ((0xFFFFFF00&(data))>>8)
#define AIF_CTRLB_get_reg_slew(data)                                                 ((0xFFFFFF00&(data))>>8)


#define AIF_CTRLC                                                                    0x18009040
#define AIF_CTRLC_reg_addr                                                           "0xB8009040"
#define AIF_CTRLC_reg                                                                0xB8009040
#define set_AIF_CTRLC_reg(data)   (*((volatile unsigned int*) AIF_CTRLC_reg)=data)
#define get_AIF_CTRLC_reg   (*((volatile unsigned int*) AIF_CTRLC_reg))
#define AIF_CTRLC_inst_adr                                                           "0x0010"
#define AIF_CTRLC_inst                                                               0x0010
#define AIF_CTRLC_reg_shapeh_shift                                                   (0)
#define AIF_CTRLC_reg_shapeh_mask                                                    (0xFFFFFFFF)
#define AIF_CTRLC_reg_shapeh(data)                                                   (0xFFFFFFFF&((data)<<0))
#define AIF_CTRLC_reg_shapeh_src(data)                                               ((0xFFFFFFFF&(data))>>0)
#define AIF_CTRLC_get_reg_shapeh(data)                                               ((0xFFFFFFFF&(data))>>0)


#define AIF_CTRLD                                                                    0x18009044
#define AIF_CTRLD_reg_addr                                                           "0xB8009044"
#define AIF_CTRLD_reg                                                                0xB8009044
#define set_AIF_CTRLD_reg(data)   (*((volatile unsigned int*) AIF_CTRLD_reg)=data)
#define get_AIF_CTRLD_reg   (*((volatile unsigned int*) AIF_CTRLD_reg))
#define AIF_CTRLD_inst_adr                                                           "0x0011"
#define AIF_CTRLD_inst                                                               0x0011
#define AIF_CTRLD_reg_shapel_shift                                                   (0)
#define AIF_CTRLD_reg_shapel_mask                                                    (0x0000000F)
#define AIF_CTRLD_reg_shapel(data)                                                   (0x0000000F&((data)<<0))
#define AIF_CTRLD_reg_shapel_src(data)                                               ((0x0000000F&(data))>>0)
#define AIF_CTRLD_get_reg_shapel(data)                                               ((0x0000000F&(data))>>0)


#define AIF_CTRLE                                                                    0x18009048
#define AIF_CTRLE_reg_addr                                                           "0xB8009048"
#define AIF_CTRLE_reg                                                                0xB8009048
#define set_AIF_CTRLE_reg(data)   (*((volatile unsigned int*) AIF_CTRLE_reg)=data)
#define get_AIF_CTRLE_reg   (*((volatile unsigned int*) AIF_CTRLE_reg))
#define AIF_CTRLE_inst_adr                                                           "0x0012"
#define AIF_CTRLE_inst                                                               0x0012
#define AIF_CTRLE_reg_wdol_shift                                                     (0)
#define AIF_CTRLE_reg_wdol_mask                                                      (0x00000001)
#define AIF_CTRLE_reg_wdol(data)                                                     (0x00000001&((data)<<0))
#define AIF_CTRLE_reg_wdol_src(data)                                                 ((0x00000001&(data))>>0)
#define AIF_CTRLE_get_reg_wdol(data)                                                 ((0x00000001&(data))>>0)


#define AIF_CTRLF                                                                    0x1800904C
#define AIF_CTRLF_reg_addr                                                           "0xB800904C"
#define AIF_CTRLF_reg                                                                0xB800904C
#define set_AIF_CTRLF_reg(data)   (*((volatile unsigned int*) AIF_CTRLF_reg)=data)
#define get_AIF_CTRLF_reg   (*((volatile unsigned int*) AIF_CTRLF_reg))
#define AIF_CTRLF_inst_adr                                                           "0x0013"
#define AIF_CTRLF_inst                                                               0x0013
#define AIF_CTRLF_reg_pll_ldo_powl_shift                                             (0)
#define AIF_CTRLF_reg_pll_ldo_powl_mask                                              (0x00000001)
#define AIF_CTRLF_reg_pll_ldo_powl(data)                                             (0x00000001&((data)<<0))
#define AIF_CTRLF_reg_pll_ldo_powl_src(data)                                         ((0x00000001&(data))>>0)
#define AIF_CTRLF_get_reg_pll_ldo_powl(data)                                         ((0x00000001&(data))>>0)


#define AIF_TTLO                                                                     0x18009050
#define AIF_TTLO_reg_addr                                                            "0xB8009050"
#define AIF_TTLO_reg                                                                 0xB8009050
#define set_AIF_TTLO_reg(data)   (*((volatile unsigned int*) AIF_TTLO_reg)=data)
#define get_AIF_TTLO_reg   (*((volatile unsigned int*) AIF_TTLO_reg))
#define AIF_TTLO_inst_adr                                                            "0x0014"
#define AIF_TTLO_inst                                                                0x0014
#define AIF_TTLO_orsdsttlinfl0_shift                                                 (22)
#define AIF_TTLO_orsdsttlinfl0_mask                                                  (0x00C00000)
#define AIF_TTLO_orsdsttlinfl0(data)                                                 (0x00C00000&((data)<<22))
#define AIF_TTLO_orsdsttlinfl0_src(data)                                             ((0x00C00000&(data))>>22)
#define AIF_TTLO_get_orsdsttlinfl0(data)                                             ((0x00C00000&(data))>>22)
#define AIF_TTLO_orsdsttlinel0_shift                                                 (20)
#define AIF_TTLO_orsdsttlinel0_mask                                                  (0x00300000)
#define AIF_TTLO_orsdsttlinel0(data)                                                 (0x00300000&((data)<<20))
#define AIF_TTLO_orsdsttlinel0_src(data)                                             ((0x00300000&(data))>>20)
#define AIF_TTLO_get_orsdsttlinel0(data)                                             ((0x00300000&(data))>>20)
#define AIF_TTLO_orsdsttlindl0_shift                                                 (18)
#define AIF_TTLO_orsdsttlindl0_mask                                                  (0x000C0000)
#define AIF_TTLO_orsdsttlindl0(data)                                                 (0x000C0000&((data)<<18))
#define AIF_TTLO_orsdsttlindl0_src(data)                                             ((0x000C0000&(data))>>18)
#define AIF_TTLO_get_orsdsttlindl0(data)                                             ((0x000C0000&(data))>>18)
#define AIF_TTLO_orsdsttlincl0_shift                                                 (16)
#define AIF_TTLO_orsdsttlincl0_mask                                                  (0x00030000)
#define AIF_TTLO_orsdsttlincl0(data)                                                 (0x00030000&((data)<<16))
#define AIF_TTLO_orsdsttlincl0_src(data)                                             ((0x00030000&(data))>>16)
#define AIF_TTLO_get_orsdsttlincl0(data)                                             ((0x00030000&(data))>>16)
#define AIF_TTLO_orsdsttlinbl0_shift                                                 (14)
#define AIF_TTLO_orsdsttlinbl0_mask                                                  (0x0000C000)
#define AIF_TTLO_orsdsttlinbl0(data)                                                 (0x0000C000&((data)<<14))
#define AIF_TTLO_orsdsttlinbl0_src(data)                                             ((0x0000C000&(data))>>14)
#define AIF_TTLO_get_orsdsttlinbl0(data)                                             ((0x0000C000&(data))>>14)
#define AIF_TTLO_orsdsttlinal0_shift                                                 (12)
#define AIF_TTLO_orsdsttlinal0_mask                                                  (0x00003000)
#define AIF_TTLO_orsdsttlinal0(data)                                                 (0x00003000&((data)<<12))
#define AIF_TTLO_orsdsttlinal0_src(data)                                             ((0x00003000&(data))>>12)
#define AIF_TTLO_get_orsdsttlinal0(data)                                             ((0x00003000&(data))>>12)
#define AIF_TTLO_ersdsttlinfl0_shift                                                 (10)
#define AIF_TTLO_ersdsttlinfl0_mask                                                  (0x00000C00)
#define AIF_TTLO_ersdsttlinfl0(data)                                                 (0x00000C00&((data)<<10))
#define AIF_TTLO_ersdsttlinfl0_src(data)                                             ((0x00000C00&(data))>>10)
#define AIF_TTLO_get_ersdsttlinfl0(data)                                             ((0x00000C00&(data))>>10)
#define AIF_TTLO_ersdsttlinel0_shift                                                 (8)
#define AIF_TTLO_ersdsttlinel0_mask                                                  (0x00000300)
#define AIF_TTLO_ersdsttlinel0(data)                                                 (0x00000300&((data)<<8))
#define AIF_TTLO_ersdsttlinel0_src(data)                                             ((0x00000300&(data))>>8)
#define AIF_TTLO_get_ersdsttlinel0(data)                                             ((0x00000300&(data))>>8)
#define AIF_TTLO_ersdsttlindl0_shift                                                 (6)
#define AIF_TTLO_ersdsttlindl0_mask                                                  (0x000000C0)
#define AIF_TTLO_ersdsttlindl0(data)                                                 (0x000000C0&((data)<<6))
#define AIF_TTLO_ersdsttlindl0_src(data)                                             ((0x000000C0&(data))>>6)
#define AIF_TTLO_get_ersdsttlindl0(data)                                             ((0x000000C0&(data))>>6)
#define AIF_TTLO_ersdsttlincl0_shift                                                 (4)
#define AIF_TTLO_ersdsttlincl0_mask                                                  (0x00000030)
#define AIF_TTLO_ersdsttlincl0(data)                                                 (0x00000030&((data)<<4))
#define AIF_TTLO_ersdsttlincl0_src(data)                                             ((0x00000030&(data))>>4)
#define AIF_TTLO_get_ersdsttlincl0(data)                                             ((0x00000030&(data))>>4)
#define AIF_TTLO_ersdsttlinbl0_shift                                                 (2)
#define AIF_TTLO_ersdsttlinbl0_mask                                                  (0x0000000C)
#define AIF_TTLO_ersdsttlinbl0(data)                                                 (0x0000000C&((data)<<2))
#define AIF_TTLO_ersdsttlinbl0_src(data)                                             ((0x0000000C&(data))>>2)
#define AIF_TTLO_get_ersdsttlinbl0(data)                                             ((0x0000000C&(data))>>2)
#define AIF_TTLO_ersdsttlinal0_shift                                                 (0)
#define AIF_TTLO_ersdsttlinal0_mask                                                  (0x00000003)
#define AIF_TTLO_ersdsttlinal0(data)                                                 (0x00000003&((data)<<0))
#define AIF_TTLO_ersdsttlinal0_src(data)                                             ((0x00000003&(data))>>0)
#define AIF_TTLO_get_ersdsttlinal0(data)                                             ((0x00000003&(data))>>0)


#define AIF_TTLI                                                                     0x18009054
#define AIF_TTLI_reg_addr                                                            "0xB8009054"
#define AIF_TTLI_reg                                                                 0xB8009054
#define set_AIF_TTLI_reg(data)   (*((volatile unsigned int*) AIF_TTLI_reg)=data)
#define get_AIF_TTLI_reg   (*((volatile unsigned int*) AIF_TTLI_reg))
#define AIF_TTLI_inst_adr                                                            "0x0015"
#define AIF_TTLI_inst                                                                0x0015
#define AIF_TTLI_op2dfl0_shift                                                       (22)
#define AIF_TTLI_op2dfl0_mask                                                        (0x00C00000)
#define AIF_TTLI_op2dfl0(data)                                                       (0x00C00000&((data)<<22))
#define AIF_TTLI_op2dfl0_src(data)                                                   ((0x00C00000&(data))>>22)
#define AIF_TTLI_get_op2dfl0(data)                                                   ((0x00C00000&(data))>>22)
#define AIF_TTLI_op2del0_shift                                                       (20)
#define AIF_TTLI_op2del0_mask                                                        (0x00300000)
#define AIF_TTLI_op2del0(data)                                                       (0x00300000&((data)<<20))
#define AIF_TTLI_op2del0_src(data)                                                   ((0x00300000&(data))>>20)
#define AIF_TTLI_get_op2del0(data)                                                   ((0x00300000&(data))>>20)
#define AIF_TTLI_op2ddl0_shift                                                       (18)
#define AIF_TTLI_op2ddl0_mask                                                        (0x000C0000)
#define AIF_TTLI_op2ddl0(data)                                                       (0x000C0000&((data)<<18))
#define AIF_TTLI_op2ddl0_src(data)                                                   ((0x000C0000&(data))>>18)
#define AIF_TTLI_get_op2ddl0(data)                                                   ((0x000C0000&(data))>>18)
#define AIF_TTLI_op2dcl0_shift                                                       (16)
#define AIF_TTLI_op2dcl0_mask                                                        (0x00030000)
#define AIF_TTLI_op2dcl0(data)                                                       (0x00030000&((data)<<16))
#define AIF_TTLI_op2dcl0_src(data)                                                   ((0x00030000&(data))>>16)
#define AIF_TTLI_get_op2dcl0(data)                                                   ((0x00030000&(data))>>16)
#define AIF_TTLI_op2dbl0_shift                                                       (14)
#define AIF_TTLI_op2dbl0_mask                                                        (0x0000C000)
#define AIF_TTLI_op2dbl0(data)                                                       (0x0000C000&((data)<<14))
#define AIF_TTLI_op2dbl0_src(data)                                                   ((0x0000C000&(data))>>14)
#define AIF_TTLI_get_op2dbl0(data)                                                   ((0x0000C000&(data))>>14)
#define AIF_TTLI_op2dal0_shift                                                       (12)
#define AIF_TTLI_op2dal0_mask                                                        (0x00003000)
#define AIF_TTLI_op2dal0(data)                                                       (0x00003000&((data)<<12))
#define AIF_TTLI_op2dal0_src(data)                                                   ((0x00003000&(data))>>12)
#define AIF_TTLI_get_op2dal0(data)                                                   ((0x00003000&(data))>>12)
#define AIF_TTLI_ep2dfl0_shift                                                       (10)
#define AIF_TTLI_ep2dfl0_mask                                                        (0x00000C00)
#define AIF_TTLI_ep2dfl0(data)                                                       (0x00000C00&((data)<<10))
#define AIF_TTLI_ep2dfl0_src(data)                                                   ((0x00000C00&(data))>>10)
#define AIF_TTLI_get_ep2dfl0(data)                                                   ((0x00000C00&(data))>>10)
#define AIF_TTLI_ep2del0_shift                                                       (8)
#define AIF_TTLI_ep2del0_mask                                                        (0x00000300)
#define AIF_TTLI_ep2del0(data)                                                       (0x00000300&((data)<<8))
#define AIF_TTLI_ep2del0_src(data)                                                   ((0x00000300&(data))>>8)
#define AIF_TTLI_get_ep2del0(data)                                                   ((0x00000300&(data))>>8)
#define AIF_TTLI_ep2ddl0_shift                                                       (6)
#define AIF_TTLI_ep2ddl0_mask                                                        (0x000000C0)
#define AIF_TTLI_ep2ddl0(data)                                                       (0x000000C0&((data)<<6))
#define AIF_TTLI_ep2ddl0_src(data)                                                   ((0x000000C0&(data))>>6)
#define AIF_TTLI_get_ep2ddl0(data)                                                   ((0x000000C0&(data))>>6)
#define AIF_TTLI_ep2dcl0_shift                                                       (4)
#define AIF_TTLI_ep2dcl0_mask                                                        (0x00000030)
#define AIF_TTLI_ep2dcl0(data)                                                       (0x00000030&((data)<<4))
#define AIF_TTLI_ep2dcl0_src(data)                                                   ((0x00000030&(data))>>4)
#define AIF_TTLI_get_ep2dcl0(data)                                                   ((0x00000030&(data))>>4)
#define AIF_TTLI_ep2dbl0_shift                                                       (2)
#define AIF_TTLI_ep2dbl0_mask                                                        (0x0000000C)
#define AIF_TTLI_ep2dbl0(data)                                                       (0x0000000C&((data)<<2))
#define AIF_TTLI_ep2dbl0_src(data)                                                   ((0x0000000C&(data))>>2)
#define AIF_TTLI_get_ep2dbl0(data)                                                   ((0x0000000C&(data))>>2)
#define AIF_TTLI_ep2dal0_shift                                                       (0)
#define AIF_TTLI_ep2dal0_mask                                                        (0x00000003)
#define AIF_TTLI_ep2dal0(data)                                                       (0x00000003&((data)<<0))
#define AIF_TTLI_ep2dal0_src(data)                                                   ((0x00000003&(data))>>0)
#define AIF_TTLI_get_ep2dal0(data)                                                   ((0x00000003&(data))>>0)


#define AIF_CTRLG                                                                    0x18009058
#define AIF_CTRLG_reg_addr                                                           "0xB8009058"
#define AIF_CTRLG_reg                                                                0xB8009058
#define set_AIF_CTRLG_reg(data)   (*((volatile unsigned int*) AIF_CTRLG_reg)=data)
#define get_AIF_CTRLG_reg   (*((volatile unsigned int*) AIF_CTRLG_reg))
#define AIF_CTRLG_inst_adr                                                           "0x0016"
#define AIF_CTRLG_inst                                                               0x0016
#define AIF_CTRLG_dummy_shift                                                        (0)
#define AIF_CTRLG_dummy_mask                                                         (0xFFFFFFFF)
#define AIF_CTRLG_dummy(data)                                                        (0xFFFFFFFF&((data)<<0))
#define AIF_CTRLG_dummy_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define AIF_CTRLG_get_dummy(data)                                                    ((0xFFFFFFFF&(data))>>0)


#endif
