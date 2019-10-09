/**************************************************************
// Spec Version                  : 1.0.6
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/7/16 15:33:11
***************************************************************/


#ifndef _LVDSOUT_REG_H_INCLUDED_
#define _LVDSOUT_REG_H_INCLUDED_
#ifdef  _LVDSOUT_USE_STRUCT
typedef struct 
{
unsigned int     lvds_arsv1_sel:3;
unsigned int     lvds_arsv0_sel:3;
unsigned int     lvds_aden_sel:3;
unsigned int     lvds_avs_sel:3;
unsigned int     lvds_ahs_sel:3;
unsigned int     reserved_0:1;
unsigned int     lvds_brsv1_sel:3;
unsigned int     lvds_brsv0_sel:3;
unsigned int     lvds_bden_sel:3;
unsigned int     lvds_bvs_sel:3;
unsigned int     lvds_bhs_sel:3;
unsigned int     dual_mode:1;
}LVDS_CTRL1;

typedef struct 
{
unsigned int     reserved:19;
unsigned int     lvds_port_swap:1;
unsigned int     lvds_pn_swap:1;
unsigned int     lvds_mirror:1;
unsigned int     lvds_map:1;
unsigned int     ttl_en:1;
unsigned int     lvds_aport_en:1;
unsigned int     lvds_bport_en:1;
unsigned int     reserved_0:4;
unsigned int     dout_mode:2;
}LVDS_CTRL2;

#endif

#define LVDS_CTRL1                                                                   0x18009008
#define LVDS_CTRL1_reg_addr                                                          "0xB8009008"
#define LVDS_CTRL1_reg                                                               0xB8009008
#define set_LVDS_CTRL1_reg(data)   (*((volatile unsigned int*) LVDS_CTRL1_reg)=data)
#define get_LVDS_CTRL1_reg   (*((volatile unsigned int*) LVDS_CTRL1_reg))
#define LVDS_CTRL1_inst_adr                                                          "0x0002"
#define LVDS_CTRL1_inst                                                              0x0002
#define LVDS_CTRL1_lvds_arsv1_sel_shift                                              (29)
#define LVDS_CTRL1_lvds_arsv1_sel_mask                                               (0xE0000000)
#define LVDS_CTRL1_lvds_arsv1_sel(data)                                              (0xE0000000&((data)<<29))
#define LVDS_CTRL1_lvds_arsv1_sel_src(data)                                          ((0xE0000000&(data))>>29)
#define LVDS_CTRL1_get_lvds_arsv1_sel(data)                                          ((0xE0000000&(data))>>29)
#define LVDS_CTRL1_lvds_arsv0_sel_shift                                              (26)
#define LVDS_CTRL1_lvds_arsv0_sel_mask                                               (0x1C000000)
#define LVDS_CTRL1_lvds_arsv0_sel(data)                                              (0x1C000000&((data)<<26))
#define LVDS_CTRL1_lvds_arsv0_sel_src(data)                                          ((0x1C000000&(data))>>26)
#define LVDS_CTRL1_get_lvds_arsv0_sel(data)                                          ((0x1C000000&(data))>>26)
#define LVDS_CTRL1_lvds_aden_sel_shift                                               (23)
#define LVDS_CTRL1_lvds_aden_sel_mask                                                (0x03800000)
#define LVDS_CTRL1_lvds_aden_sel(data)                                               (0x03800000&((data)<<23))
#define LVDS_CTRL1_lvds_aden_sel_src(data)                                           ((0x03800000&(data))>>23)
#define LVDS_CTRL1_get_lvds_aden_sel(data)                                           ((0x03800000&(data))>>23)
#define LVDS_CTRL1_lvds_avs_sel_shift                                                (20)
#define LVDS_CTRL1_lvds_avs_sel_mask                                                 (0x00700000)
#define LVDS_CTRL1_lvds_avs_sel(data)                                                (0x00700000&((data)<<20))
#define LVDS_CTRL1_lvds_avs_sel_src(data)                                            ((0x00700000&(data))>>20)
#define LVDS_CTRL1_get_lvds_avs_sel(data)                                            ((0x00700000&(data))>>20)
#define LVDS_CTRL1_lvds_ahs_sel_shift                                                (17)
#define LVDS_CTRL1_lvds_ahs_sel_mask                                                 (0x000E0000)
#define LVDS_CTRL1_lvds_ahs_sel(data)                                                (0x000E0000&((data)<<17))
#define LVDS_CTRL1_lvds_ahs_sel_src(data)                                            ((0x000E0000&(data))>>17)
#define LVDS_CTRL1_get_lvds_ahs_sel(data)                                            ((0x000E0000&(data))>>17)
#define LVDS_CTRL1_lvds_brsv1_sel_shift                                              (13)
#define LVDS_CTRL1_lvds_brsv1_sel_mask                                               (0x0000E000)
#define LVDS_CTRL1_lvds_brsv1_sel(data)                                              (0x0000E000&((data)<<13))
#define LVDS_CTRL1_lvds_brsv1_sel_src(data)                                          ((0x0000E000&(data))>>13)
#define LVDS_CTRL1_get_lvds_brsv1_sel(data)                                          ((0x0000E000&(data))>>13)
#define LVDS_CTRL1_lvds_brsv0_sel_shift                                              (10)
#define LVDS_CTRL1_lvds_brsv0_sel_mask                                               (0x00001C00)
#define LVDS_CTRL1_lvds_brsv0_sel(data)                                              (0x00001C00&((data)<<10))
#define LVDS_CTRL1_lvds_brsv0_sel_src(data)                                          ((0x00001C00&(data))>>10)
#define LVDS_CTRL1_get_lvds_brsv0_sel(data)                                          ((0x00001C00&(data))>>10)
#define LVDS_CTRL1_lvds_bden_sel_shift                                               (7)
#define LVDS_CTRL1_lvds_bden_sel_mask                                                (0x00000380)
#define LVDS_CTRL1_lvds_bden_sel(data)                                               (0x00000380&((data)<<7))
#define LVDS_CTRL1_lvds_bden_sel_src(data)                                           ((0x00000380&(data))>>7)
#define LVDS_CTRL1_get_lvds_bden_sel(data)                                           ((0x00000380&(data))>>7)
#define LVDS_CTRL1_lvds_bvs_sel_shift                                                (4)
#define LVDS_CTRL1_lvds_bvs_sel_mask                                                 (0x00000070)
#define LVDS_CTRL1_lvds_bvs_sel(data)                                                (0x00000070&((data)<<4))
#define LVDS_CTRL1_lvds_bvs_sel_src(data)                                            ((0x00000070&(data))>>4)
#define LVDS_CTRL1_get_lvds_bvs_sel(data)                                            ((0x00000070&(data))>>4)
#define LVDS_CTRL1_lvds_bhs_sel_shift                                                (1)
#define LVDS_CTRL1_lvds_bhs_sel_mask                                                 (0x0000000E)
#define LVDS_CTRL1_lvds_bhs_sel(data)                                                (0x0000000E&((data)<<1))
#define LVDS_CTRL1_lvds_bhs_sel_src(data)                                            ((0x0000000E&(data))>>1)
#define LVDS_CTRL1_get_lvds_bhs_sel(data)                                            ((0x0000000E&(data))>>1)
#define LVDS_CTRL1_dual_mode_shift                                                   (0)
#define LVDS_CTRL1_dual_mode_mask                                                    (0x00000001)
#define LVDS_CTRL1_dual_mode(data)                                                   (0x00000001&((data)<<0))
#define LVDS_CTRL1_dual_mode_src(data)                                               ((0x00000001&(data))>>0)
#define LVDS_CTRL1_get_dual_mode(data)                                               ((0x00000001&(data))>>0)


#define LVDS_CTRL2                                                                   0x1800900C
#define LVDS_CTRL2_reg_addr                                                          "0xB800900C"
#define LVDS_CTRL2_reg                                                               0xB800900C
#define set_LVDS_CTRL2_reg(data)   (*((volatile unsigned int*) LVDS_CTRL2_reg)=data)
#define get_LVDS_CTRL2_reg   (*((volatile unsigned int*) LVDS_CTRL2_reg))
#define LVDS_CTRL2_inst_adr                                                          "0x0003"
#define LVDS_CTRL2_inst                                                              0x0003
#define LVDS_CTRL2_reserved_shift                                                    (13)
#define LVDS_CTRL2_reserved_mask                                                     (0xFFFFE000)
#define LVDS_CTRL2_reserved(data)                                                    (0xFFFFE000&((data)<<13))
#define LVDS_CTRL2_reserved_src(data)                                                ((0xFFFFE000&(data))>>13)
#define LVDS_CTRL2_get_reserved(data)                                                ((0xFFFFE000&(data))>>13)
#define LVDS_CTRL2_lvds_port_swap_shift                                              (12)
#define LVDS_CTRL2_lvds_port_swap_mask                                               (0x00001000)
#define LVDS_CTRL2_lvds_port_swap(data)                                              (0x00001000&((data)<<12))
#define LVDS_CTRL2_lvds_port_swap_src(data)                                          ((0x00001000&(data))>>12)
#define LVDS_CTRL2_get_lvds_port_swap(data)                                          ((0x00001000&(data))>>12)
#define LVDS_CTRL2_lvds_pn_swap_shift                                                (11)
#define LVDS_CTRL2_lvds_pn_swap_mask                                                 (0x00000800)
#define LVDS_CTRL2_lvds_pn_swap(data)                                                (0x00000800&((data)<<11))
#define LVDS_CTRL2_lvds_pn_swap_src(data)                                            ((0x00000800&(data))>>11)
#define LVDS_CTRL2_get_lvds_pn_swap(data)                                            ((0x00000800&(data))>>11)
#define LVDS_CTRL2_lvds_mirror_shift                                                 (10)
#define LVDS_CTRL2_lvds_mirror_mask                                                  (0x00000400)
#define LVDS_CTRL2_lvds_mirror(data)                                                 (0x00000400&((data)<<10))
#define LVDS_CTRL2_lvds_mirror_src(data)                                             ((0x00000400&(data))>>10)
#define LVDS_CTRL2_get_lvds_mirror(data)                                             ((0x00000400&(data))>>10)
#define LVDS_CTRL2_lvds_map_shift                                                    (9)
#define LVDS_CTRL2_lvds_map_mask                                                     (0x00000200)
#define LVDS_CTRL2_lvds_map(data)                                                    (0x00000200&((data)<<9))
#define LVDS_CTRL2_lvds_map_src(data)                                                ((0x00000200&(data))>>9)
#define LVDS_CTRL2_get_lvds_map(data)                                                ((0x00000200&(data))>>9)
#define LVDS_CTRL2_ttl_en_shift                                                      (8)
#define LVDS_CTRL2_ttl_en_mask                                                       (0x00000100)
#define LVDS_CTRL2_ttl_en(data)                                                      (0x00000100&((data)<<8))
#define LVDS_CTRL2_ttl_en_src(data)                                                  ((0x00000100&(data))>>8)
#define LVDS_CTRL2_get_ttl_en(data)                                                  ((0x00000100&(data))>>8)
#define LVDS_CTRL2_lvds_aport_en_shift                                               (7)
#define LVDS_CTRL2_lvds_aport_en_mask                                                (0x00000080)
#define LVDS_CTRL2_lvds_aport_en(data)                                               (0x00000080&((data)<<7))
#define LVDS_CTRL2_lvds_aport_en_src(data)                                           ((0x00000080&(data))>>7)
#define LVDS_CTRL2_get_lvds_aport_en(data)                                           ((0x00000080&(data))>>7)
#define LVDS_CTRL2_lvds_bport_en_shift                                               (6)
#define LVDS_CTRL2_lvds_bport_en_mask                                                (0x00000040)
#define LVDS_CTRL2_lvds_bport_en(data)                                               (0x00000040&((data)<<6))
#define LVDS_CTRL2_lvds_bport_en_src(data)                                           ((0x00000040&(data))>>6)
#define LVDS_CTRL2_get_lvds_bport_en(data)                                           ((0x00000040&(data))>>6)
#define LVDS_CTRL2_dout_mode_shift                                                   (0)
#define LVDS_CTRL2_dout_mode_mask                                                    (0x00000003)
#define LVDS_CTRL2_dout_mode(data)                                                   (0x00000003&((data)<<0))
#define LVDS_CTRL2_dout_mode_src(data)                                               ((0x00000003&(data))>>0)
#define LVDS_CTRL2_get_dout_mode(data)                                               ((0x00000003&(data))>>0)


#endif
