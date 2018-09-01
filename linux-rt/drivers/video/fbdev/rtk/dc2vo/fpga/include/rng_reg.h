/**************************************************************
// Spec Version                  : unknown
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/8/8 16:36:29
***************************************************************/


#ifndef _RNG_REG_H_INCLUDED_
#define _RNG_REG_H_INCLUDED_
#ifdef  _RNG_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     lfsr_mode:1;
unsigned int     lfsr_bypass_1:1;
unsigned int     dbg1_sel:4;
unsigned int     dbg0_sel:4;
unsigned int     reserved_1:2;
unsigned int     corrector_imode:1;
unsigned int     reserved_2:1;
unsigned int     rng_cali_srst:1;
unsigned int     corrector_bypass:1;
unsigned int     clk_hf_sel:1;
unsigned int     rng_srst:1;
}CTRL;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     rosc_d:4;
unsigned int     rosc_res:2;
unsigned int     rosc_div:2;
unsigned int     rosc_gain:2;
unsigned int     rosc_fs:2;
unsigned int     reserved_1:2;
unsigned int     rosc_test:1;
unsigned int     rosc_pow:1;
}ANALOG;

typedef struct 
{
unsigned int     prd_ub:16;
unsigned int     prd_lb:16;
}CALI_CHK;

typedef struct 
{
unsigned int     shot_num:12;
unsigned int     cyc_num:3;
unsigned int     wait_num:5;
unsigned int     reserved_0:3;
unsigned int     trig_num:5;
unsigned int     lock:1;
unsigned int     shot_mode:1;
unsigned int     pol:1;
unsigned int     hw_en:1;
}CALI_CTRL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     hw_d:4;
unsigned int     reserved_1:2;
unsigned int     rosc_lock:1;
unsigned int     cnt_ovflw:1;
unsigned int     cnt:16;
}CALI_RETURN;

typedef struct 
{
unsigned int     prd_ub:16;
unsigned int     prd_lb:16;
}LOCK_CHK;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     exit_num:4;
unsigned int     reserved_1:12;
unsigned int     enter_num:4;
}LOCK_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     out_ready:1;
}RETURN3;

typedef struct 
{
unsigned int     valid_bit_num:32;
}RETURN4;

typedef struct 
{
unsigned int     drop_num:32;
}RETURN5;

typedef struct 
{
unsigned int     random_out:32;
}RESULTR;

typedef struct 
{
unsigned int     lfsr_poly_lsb:32;
}LFSR_POLY_LSB;

typedef struct 
{
unsigned int     lfsr_poly_msb:32;
}LFSR_POLY_MSB;

typedef struct 
{
unsigned int     dummy_msb:16;
unsigned int     dummy_lsb:16;
}DUMMY;

#endif

#define CTRL                                                                         0x18001800
#define CTRL_reg_addr                                                                "0xB8001800"
#define CTRL_reg                                                                     0xB8001800
#define set_CTRL_reg(data)   (*((volatile unsigned int*) CTRL_reg)=data)
#define get_CTRL_reg   (*((volatile unsigned int*) CTRL_reg))
#define CTRL_inst_adr                                                                "0x0000"
#define CTRL_inst                                                                    0x0000
#define CTRL_lfsr_mode_shift                                                         (17)
#define CTRL_lfsr_mode_mask                                                          (0x00020000)
#define CTRL_lfsr_mode(data)                                                         (0x00020000&((data)<<17))
#define CTRL_lfsr_mode_src(data)                                                     ((0x00020000&(data))>>17)
#define CTRL_get_lfsr_mode(data)                                                     ((0x00020000&(data))>>17)
#define CTRL_lfsr_bypass_1_shift                                                     (16)
#define CTRL_lfsr_bypass_1_mask                                                      (0x00010000)
#define CTRL_lfsr_bypass_1(data)                                                     (0x00010000&((data)<<16))
#define CTRL_lfsr_bypass_1_src(data)                                                 ((0x00010000&(data))>>16)
#define CTRL_get_lfsr_bypass_1(data)                                                 ((0x00010000&(data))>>16)
#define CTRL_dbg1_sel_shift                                                          (12)
#define CTRL_dbg1_sel_mask                                                           (0x0000F000)
#define CTRL_dbg1_sel(data)                                                          (0x0000F000&((data)<<12))
#define CTRL_dbg1_sel_src(data)                                                      ((0x0000F000&(data))>>12)
#define CTRL_get_dbg1_sel(data)                                                      ((0x0000F000&(data))>>12)
#define CTRL_dbg0_sel_shift                                                          (8)
#define CTRL_dbg0_sel_mask                                                           (0x00000F00)
#define CTRL_dbg0_sel(data)                                                          (0x00000F00&((data)<<8))
#define CTRL_dbg0_sel_src(data)                                                      ((0x00000F00&(data))>>8)
#define CTRL_get_dbg0_sel(data)                                                      ((0x00000F00&(data))>>8)
#define CTRL_corrector_imode_shift                                                   (5)
#define CTRL_corrector_imode_mask                                                    (0x00000020)
#define CTRL_corrector_imode(data)                                                   (0x00000020&((data)<<5))
#define CTRL_corrector_imode_src(data)                                               ((0x00000020&(data))>>5)
#define CTRL_get_corrector_imode(data)                                               ((0x00000020&(data))>>5)
#define CTRL_rng_cali_srst_shift                                                     (3)
#define CTRL_rng_cali_srst_mask                                                      (0x00000008)
#define CTRL_rng_cali_srst(data)                                                     (0x00000008&((data)<<3))
#define CTRL_rng_cali_srst_src(data)                                                 ((0x00000008&(data))>>3)
#define CTRL_get_rng_cali_srst(data)                                                 ((0x00000008&(data))>>3)
#define CTRL_corrector_bypass_shift                                                  (2)
#define CTRL_corrector_bypass_mask                                                   (0x00000004)
#define CTRL_corrector_bypass(data)                                                  (0x00000004&((data)<<2))
#define CTRL_corrector_bypass_src(data)                                              ((0x00000004&(data))>>2)
#define CTRL_get_corrector_bypass(data)                                              ((0x00000004&(data))>>2)
#define CTRL_clk_hf_sel_shift                                                        (1)
#define CTRL_clk_hf_sel_mask                                                         (0x00000002)
#define CTRL_clk_hf_sel(data)                                                        (0x00000002&((data)<<1))
#define CTRL_clk_hf_sel_src(data)                                                    ((0x00000002&(data))>>1)
#define CTRL_get_clk_hf_sel(data)                                                    ((0x00000002&(data))>>1)
#define CTRL_rng_srst_shift                                                          (0)
#define CTRL_rng_srst_mask                                                           (0x00000001)
#define CTRL_rng_srst(data)                                                          (0x00000001&((data)<<0))
#define CTRL_rng_srst_src(data)                                                      ((0x00000001&(data))>>0)
#define CTRL_get_rng_srst(data)                                                      ((0x00000001&(data))>>0)


#define ANALOG                                                                       0x18001814
#define ANALOG_reg_addr                                                              "0xB8001814"
#define ANALOG_reg                                                                   0xB8001814
#define set_ANALOG_reg(data)   (*((volatile unsigned int*) ANALOG_reg)=data)
#define get_ANALOG_reg   (*((volatile unsigned int*) ANALOG_reg))
#define ANALOG_inst_adr                                                              "0x0005"
#define ANALOG_inst                                                                  0x0005
#define ANALOG_rosc_d_shift                                                          (12)
#define ANALOG_rosc_d_mask                                                           (0x0000F000)
#define ANALOG_rosc_d(data)                                                          (0x0000F000&((data)<<12))
#define ANALOG_rosc_d_src(data)                                                      ((0x0000F000&(data))>>12)
#define ANALOG_get_rosc_d(data)                                                      ((0x0000F000&(data))>>12)
#define ANALOG_rosc_res_shift                                                        (10)
#define ANALOG_rosc_res_mask                                                         (0x00000C00)
#define ANALOG_rosc_res(data)                                                        (0x00000C00&((data)<<10))
#define ANALOG_rosc_res_src(data)                                                    ((0x00000C00&(data))>>10)
#define ANALOG_get_rosc_res(data)                                                    ((0x00000C00&(data))>>10)
#define ANALOG_rosc_div_shift                                                        (8)
#define ANALOG_rosc_div_mask                                                         (0x00000300)
#define ANALOG_rosc_div(data)                                                        (0x00000300&((data)<<8))
#define ANALOG_rosc_div_src(data)                                                    ((0x00000300&(data))>>8)
#define ANALOG_get_rosc_div(data)                                                    ((0x00000300&(data))>>8)
#define ANALOG_rosc_gain_shift                                                       (6)
#define ANALOG_rosc_gain_mask                                                        (0x000000C0)
#define ANALOG_rosc_gain(data)                                                       (0x000000C0&((data)<<6))
#define ANALOG_rosc_gain_src(data)                                                   ((0x000000C0&(data))>>6)
#define ANALOG_get_rosc_gain(data)                                                   ((0x000000C0&(data))>>6)
#define ANALOG_rosc_fs_shift                                                         (4)
#define ANALOG_rosc_fs_mask                                                          (0x00000030)
#define ANALOG_rosc_fs(data)                                                         (0x00000030&((data)<<4))
#define ANALOG_rosc_fs_src(data)                                                     ((0x00000030&(data))>>4)
#define ANALOG_get_rosc_fs(data)                                                     ((0x00000030&(data))>>4)
#define ANALOG_rosc_test_shift                                                       (1)
#define ANALOG_rosc_test_mask                                                        (0x00000002)
#define ANALOG_rosc_test(data)                                                       (0x00000002&((data)<<1))
#define ANALOG_rosc_test_src(data)                                                   ((0x00000002&(data))>>1)
#define ANALOG_get_rosc_test(data)                                                   ((0x00000002&(data))>>1)
#define ANALOG_rosc_pow_shift                                                        (0)
#define ANALOG_rosc_pow_mask                                                         (0x00000001)
#define ANALOG_rosc_pow(data)                                                        (0x00000001&((data)<<0))
#define ANALOG_rosc_pow_src(data)                                                    ((0x00000001&(data))>>0)
#define ANALOG_get_rosc_pow(data)                                                    ((0x00000001&(data))>>0)


#define CALI_CHK                                                                     0x18001818
#define CALI_CHK_reg_addr                                                            "0xB8001818"
#define CALI_CHK_reg                                                                 0xB8001818
#define set_CALI_CHK_reg(data)   (*((volatile unsigned int*) CALI_CHK_reg)=data)
#define get_CALI_CHK_reg   (*((volatile unsigned int*) CALI_CHK_reg))
#define CALI_CHK_inst_adr                                                            "0x0006"
#define CALI_CHK_inst                                                                0x0006
#define CALI_CHK_prd_ub_shift                                                        (16)
#define CALI_CHK_prd_ub_mask                                                         (0xFFFF0000)
#define CALI_CHK_prd_ub(data)                                                        (0xFFFF0000&((data)<<16))
#define CALI_CHK_prd_ub_src(data)                                                    ((0xFFFF0000&(data))>>16)
#define CALI_CHK_get_prd_ub(data)                                                    ((0xFFFF0000&(data))>>16)
#define CALI_CHK_prd_lb_shift                                                        (0)
#define CALI_CHK_prd_lb_mask                                                         (0x0000FFFF)
#define CALI_CHK_prd_lb(data)                                                        (0x0000FFFF&((data)<<0))
#define CALI_CHK_prd_lb_src(data)                                                    ((0x0000FFFF&(data))>>0)
#define CALI_CHK_get_prd_lb(data)                                                    ((0x0000FFFF&(data))>>0)


#define CALI_CTRL                                                                    0x1800181C
#define CALI_CTRL_reg_addr                                                           "0xB800181C"
#define CALI_CTRL_reg                                                                0xB800181C
#define set_CALI_CTRL_reg(data)   (*((volatile unsigned int*) CALI_CTRL_reg)=data)
#define get_CALI_CTRL_reg   (*((volatile unsigned int*) CALI_CTRL_reg))
#define CALI_CTRL_inst_adr                                                           "0x0007"
#define CALI_CTRL_inst                                                               0x0007
#define CALI_CTRL_shot_num_shift                                                     (20)
#define CALI_CTRL_shot_num_mask                                                      (0xFFF00000)
#define CALI_CTRL_shot_num(data)                                                     (0xFFF00000&((data)<<20))
#define CALI_CTRL_shot_num_src(data)                                                 ((0xFFF00000&(data))>>20)
#define CALI_CTRL_get_shot_num(data)                                                 ((0xFFF00000&(data))>>20)
#define CALI_CTRL_cyc_num_shift                                                      (17)
#define CALI_CTRL_cyc_num_mask                                                       (0x000E0000)
#define CALI_CTRL_cyc_num(data)                                                      (0x000E0000&((data)<<17))
#define CALI_CTRL_cyc_num_src(data)                                                  ((0x000E0000&(data))>>17)
#define CALI_CTRL_get_cyc_num(data)                                                  ((0x000E0000&(data))>>17)
#define CALI_CTRL_wait_num_shift                                                     (12)
#define CALI_CTRL_wait_num_mask                                                      (0x0001F000)
#define CALI_CTRL_wait_num(data)                                                     (0x0001F000&((data)<<12))
#define CALI_CTRL_wait_num_src(data)                                                 ((0x0001F000&(data))>>12)
#define CALI_CTRL_get_wait_num(data)                                                 ((0x0001F000&(data))>>12)
#define CALI_CTRL_trig_num_shift                                                     (4)
#define CALI_CTRL_trig_num_mask                                                      (0x000001F0)
#define CALI_CTRL_trig_num(data)                                                     (0x000001F0&((data)<<4))
#define CALI_CTRL_trig_num_src(data)                                                 ((0x000001F0&(data))>>4)
#define CALI_CTRL_get_trig_num(data)                                                 ((0x000001F0&(data))>>4)
#define CALI_CTRL_lock_shift                                                         (3)
#define CALI_CTRL_lock_mask                                                          (0x00000008)
#define CALI_CTRL_lock(data)                                                         (0x00000008&((data)<<3))
#define CALI_CTRL_lock_src(data)                                                     ((0x00000008&(data))>>3)
#define CALI_CTRL_get_lock(data)                                                     ((0x00000008&(data))>>3)
#define CALI_CTRL_shot_mode_shift                                                    (2)
#define CALI_CTRL_shot_mode_mask                                                     (0x00000004)
#define CALI_CTRL_shot_mode(data)                                                    (0x00000004&((data)<<2))
#define CALI_CTRL_shot_mode_src(data)                                                ((0x00000004&(data))>>2)
#define CALI_CTRL_get_shot_mode(data)                                                ((0x00000004&(data))>>2)
#define CALI_CTRL_pol_shift                                                          (1)
#define CALI_CTRL_pol_mask                                                           (0x00000002)
#define CALI_CTRL_pol(data)                                                          (0x00000002&((data)<<1))
#define CALI_CTRL_pol_src(data)                                                      ((0x00000002&(data))>>1)
#define CALI_CTRL_get_pol(data)                                                      ((0x00000002&(data))>>1)
#define CALI_CTRL_hw_en_shift                                                        (0)
#define CALI_CTRL_hw_en_mask                                                         (0x00000001)
#define CALI_CTRL_hw_en(data)                                                        (0x00000001&((data)<<0))
#define CALI_CTRL_hw_en_src(data)                                                    ((0x00000001&(data))>>0)
#define CALI_CTRL_get_hw_en(data)                                                    ((0x00000001&(data))>>0)


#define CALI_RETURN                                                                  0x18001820
#define CALI_RETURN_reg_addr                                                         "0xB8001820"
#define CALI_RETURN_reg                                                              0xB8001820
#define set_CALI_RETURN_reg(data)   (*((volatile unsigned int*) CALI_RETURN_reg)=data)
#define get_CALI_RETURN_reg   (*((volatile unsigned int*) CALI_RETURN_reg))
#define CALI_RETURN_inst_adr                                                         "0x0008"
#define CALI_RETURN_inst                                                             0x0008
#define CALI_RETURN_hw_d_shift                                                       (20)
#define CALI_RETURN_hw_d_mask                                                        (0x00F00000)
#define CALI_RETURN_hw_d(data)                                                       (0x00F00000&((data)<<20))
#define CALI_RETURN_hw_d_src(data)                                                   ((0x00F00000&(data))>>20)
#define CALI_RETURN_get_hw_d(data)                                                   ((0x00F00000&(data))>>20)
#define CALI_RETURN_rosc_lock_shift                                                  (17)
#define CALI_RETURN_rosc_lock_mask                                                   (0x00020000)
#define CALI_RETURN_rosc_lock(data)                                                  (0x00020000&((data)<<17))
#define CALI_RETURN_rosc_lock_src(data)                                              ((0x00020000&(data))>>17)
#define CALI_RETURN_get_rosc_lock(data)                                              ((0x00020000&(data))>>17)
#define CALI_RETURN_cnt_ovflw_shift                                                  (16)
#define CALI_RETURN_cnt_ovflw_mask                                                   (0x00010000)
#define CALI_RETURN_cnt_ovflw(data)                                                  (0x00010000&((data)<<16))
#define CALI_RETURN_cnt_ovflw_src(data)                                              ((0x00010000&(data))>>16)
#define CALI_RETURN_get_cnt_ovflw(data)                                              ((0x00010000&(data))>>16)
#define CALI_RETURN_cnt_shift                                                        (0)
#define CALI_RETURN_cnt_mask                                                         (0x0000FFFF)
#define CALI_RETURN_cnt(data)                                                        (0x0000FFFF&((data)<<0))
#define CALI_RETURN_cnt_src(data)                                                    ((0x0000FFFF&(data))>>0)
#define CALI_RETURN_get_cnt(data)                                                    ((0x0000FFFF&(data))>>0)


#define LOCK_CHK                                                                     0x18001824
#define LOCK_CHK_reg_addr                                                            "0xB8001824"
#define LOCK_CHK_reg                                                                 0xB8001824
#define set_LOCK_CHK_reg(data)   (*((volatile unsigned int*) LOCK_CHK_reg)=data)
#define get_LOCK_CHK_reg   (*((volatile unsigned int*) LOCK_CHK_reg))
#define LOCK_CHK_inst_adr                                                            "0x0009"
#define LOCK_CHK_inst                                                                0x0009
#define LOCK_CHK_prd_ub_shift                                                        (16)
#define LOCK_CHK_prd_ub_mask                                                         (0xFFFF0000)
#define LOCK_CHK_prd_ub(data)                                                        (0xFFFF0000&((data)<<16))
#define LOCK_CHK_prd_ub_src(data)                                                    ((0xFFFF0000&(data))>>16)
#define LOCK_CHK_get_prd_ub(data)                                                    ((0xFFFF0000&(data))>>16)
#define LOCK_CHK_prd_lb_shift                                                        (0)
#define LOCK_CHK_prd_lb_mask                                                         (0x0000FFFF)
#define LOCK_CHK_prd_lb(data)                                                        (0x0000FFFF&((data)<<0))
#define LOCK_CHK_prd_lb_src(data)                                                    ((0x0000FFFF&(data))>>0)
#define LOCK_CHK_get_prd_lb(data)                                                    ((0x0000FFFF&(data))>>0)


#define LOCK_CTRL                                                                    0x18001828
#define LOCK_CTRL_reg_addr                                                           "0xB8001828"
#define LOCK_CTRL_reg                                                                0xB8001828
#define set_LOCK_CTRL_reg(data)   (*((volatile unsigned int*) LOCK_CTRL_reg)=data)
#define get_LOCK_CTRL_reg   (*((volatile unsigned int*) LOCK_CTRL_reg))
#define LOCK_CTRL_inst_adr                                                           "0x000A"
#define LOCK_CTRL_inst                                                               0x000A
#define LOCK_CTRL_exit_num_shift                                                     (16)
#define LOCK_CTRL_exit_num_mask                                                      (0x000F0000)
#define LOCK_CTRL_exit_num(data)                                                     (0x000F0000&((data)<<16))
#define LOCK_CTRL_exit_num_src(data)                                                 ((0x000F0000&(data))>>16)
#define LOCK_CTRL_get_exit_num(data)                                                 ((0x000F0000&(data))>>16)
#define LOCK_CTRL_enter_num_shift                                                    (0)
#define LOCK_CTRL_enter_num_mask                                                     (0x0000000F)
#define LOCK_CTRL_enter_num(data)                                                    (0x0000000F&((data)<<0))
#define LOCK_CTRL_enter_num_src(data)                                                ((0x0000000F&(data))>>0)
#define LOCK_CTRL_get_enter_num(data)                                                ((0x0000000F&(data))>>0)


#define RETURN3                                                                      0x1800182C
#define RETURN3_reg_addr                                                             "0xB800182C"
#define RETURN3_reg                                                                  0xB800182C
#define set_RETURN3_reg(data)   (*((volatile unsigned int*) RETURN3_reg)=data)
#define get_RETURN3_reg   (*((volatile unsigned int*) RETURN3_reg))
#define RETURN3_inst_adr                                                             "0x000B"
#define RETURN3_inst                                                                 0x000B
#define RETURN3_out_ready_shift                                                      (0)
#define RETURN3_out_ready_mask                                                       (0x00000001)
#define RETURN3_out_ready(data)                                                      (0x00000001&((data)<<0))
#define RETURN3_out_ready_src(data)                                                  ((0x00000001&(data))>>0)
#define RETURN3_get_out_ready(data)                                                  ((0x00000001&(data))>>0)


#define RETURN4                                                                      0x18001830
#define RETURN4_reg_addr                                                             "0xB8001830"
#define RETURN4_reg                                                                  0xB8001830
#define set_RETURN4_reg(data)   (*((volatile unsigned int*) RETURN4_reg)=data)
#define get_RETURN4_reg   (*((volatile unsigned int*) RETURN4_reg))
#define RETURN4_inst_adr                                                             "0x000C"
#define RETURN4_inst                                                                 0x000C
#define RETURN4_valid_bit_num_shift                                                  (0)
#define RETURN4_valid_bit_num_mask                                                   (0xFFFFFFFF)
#define RETURN4_valid_bit_num(data)                                                  (0xFFFFFFFF&((data)<<0))
#define RETURN4_valid_bit_num_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define RETURN4_get_valid_bit_num(data)                                              ((0xFFFFFFFF&(data))>>0)


#define RETURN5                                                                      0x18001834
#define RETURN5_reg_addr                                                             "0xB8001834"
#define RETURN5_reg                                                                  0xB8001834
#define set_RETURN5_reg(data)   (*((volatile unsigned int*) RETURN5_reg)=data)
#define get_RETURN5_reg   (*((volatile unsigned int*) RETURN5_reg))
#define RETURN5_inst_adr                                                             "0x000D"
#define RETURN5_inst                                                                 0x000D
#define RETURN5_drop_num_shift                                                       (0)
#define RETURN5_drop_num_mask                                                        (0xFFFFFFFF)
#define RETURN5_drop_num(data)                                                       (0xFFFFFFFF&((data)<<0))
#define RETURN5_drop_num_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define RETURN5_get_drop_num(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define RESULTR                                                                      0x18001838
#define RESULTR_reg_addr                                                             "0xB8001838"
#define RESULTR_reg                                                                  0xB8001838
#define set_RESULTR_reg(data)   (*((volatile unsigned int*) RESULTR_reg)=data)
#define get_RESULTR_reg   (*((volatile unsigned int*) RESULTR_reg))
#define RESULTR_inst_adr                                                             "0x000E"
#define RESULTR_inst                                                                 0x000E
#define RESULTR_random_out_shift                                                     (0)
#define RESULTR_random_out_mask                                                      (0xFFFFFFFF)
#define RESULTR_random_out(data)                                                     (0xFFFFFFFF&((data)<<0))
#define RESULTR_random_out_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define RESULTR_get_random_out(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define LFSR_POLY_LSB                                                                0x1800183C
#define LFSR_POLY_LSB_reg_addr                                                       "0xB800183C"
#define LFSR_POLY_LSB_reg                                                            0xB800183C
#define set_LFSR_POLY_LSB_reg(data)   (*((volatile unsigned int*) LFSR_POLY_LSB_reg)=data)
#define get_LFSR_POLY_LSB_reg   (*((volatile unsigned int*) LFSR_POLY_LSB_reg))
#define LFSR_POLY_LSB_inst_adr                                                       "0x000F"
#define LFSR_POLY_LSB_inst                                                           0x000F
#define LFSR_POLY_LSB_lfsr_poly_lsb_shift                                            (0)
#define LFSR_POLY_LSB_lfsr_poly_lsb_mask                                             (0xFFFFFFFF)
#define LFSR_POLY_LSB_lfsr_poly_lsb(data)                                            (0xFFFFFFFF&((data)<<0))
#define LFSR_POLY_LSB_lfsr_poly_lsb_src(data)                                        ((0xFFFFFFFF&(data))>>0)
#define LFSR_POLY_LSB_get_lfsr_poly_lsb(data)                                        ((0xFFFFFFFF&(data))>>0)


#define LFSR_POLY_MSB                                                                0x18001840
#define LFSR_POLY_MSB_reg_addr                                                       "0xB8001840"
#define LFSR_POLY_MSB_reg                                                            0xB8001840
#define set_LFSR_POLY_MSB_reg(data)   (*((volatile unsigned int*) LFSR_POLY_MSB_reg)=data)
#define get_LFSR_POLY_MSB_reg   (*((volatile unsigned int*) LFSR_POLY_MSB_reg))
#define LFSR_POLY_MSB_inst_adr                                                       "0x0010"
#define LFSR_POLY_MSB_inst                                                           0x0010
#define LFSR_POLY_MSB_lfsr_poly_msb_shift                                            (0)
#define LFSR_POLY_MSB_lfsr_poly_msb_mask                                             (0xFFFFFFFF)
#define LFSR_POLY_MSB_lfsr_poly_msb(data)                                            (0xFFFFFFFF&((data)<<0))
#define LFSR_POLY_MSB_lfsr_poly_msb_src(data)                                        ((0xFFFFFFFF&(data))>>0)
#define LFSR_POLY_MSB_get_lfsr_poly_msb(data)                                        ((0xFFFFFFFF&(data))>>0)


#define DUMMY                                                                        0x18001844
#define DUMMY_reg_addr                                                               "0xB8001844"
#define DUMMY_reg                                                                    0xB8001844
#define set_DUMMY_reg(data)   (*((volatile unsigned int*) DUMMY_reg)=data)
#define get_DUMMY_reg   (*((volatile unsigned int*) DUMMY_reg))
#define DUMMY_inst_adr                                                               "0x0011"
#define DUMMY_inst                                                                   0x0011
#define DUMMY_dummy_msb_shift                                                        (16)
#define DUMMY_dummy_msb_mask                                                         (0xFFFF0000)
#define DUMMY_dummy_msb(data)                                                        (0xFFFF0000&((data)<<16))
#define DUMMY_dummy_msb_src(data)                                                    ((0xFFFF0000&(data))>>16)
#define DUMMY_get_dummy_msb(data)                                                    ((0xFFFF0000&(data))>>16)
#define DUMMY_dummy_lsb_shift                                                        (0)
#define DUMMY_dummy_lsb_mask                                                         (0x0000FFFF)
#define DUMMY_dummy_lsb(data)                                                        (0x0000FFFF&((data)<<0))
#define DUMMY_dummy_lsb_src(data)                                                    ((0x0000FFFF&(data))>>0)
#define DUMMY_get_dummy_lsb(data)                                                    ((0x0000FFFF&(data))>>0)


#endif
