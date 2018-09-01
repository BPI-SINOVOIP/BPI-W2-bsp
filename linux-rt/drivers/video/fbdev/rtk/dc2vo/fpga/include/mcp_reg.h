/**************************************************************
// Spec Version                  : 0.3
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/4/1 14:32:35
***************************************************************/


#ifndef _MCP_REG_H_INCLUDED_
#define _MCP_REG_H_INCLUDED_
#ifdef  _MCP_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     arb_mode:1;
unsigned int     reserved_1:1;
unsigned int     clear:1;
unsigned int     swap:1;
unsigned int     idle:1;
unsigned int     go:1;
unsigned int     write_data:1;
}MCP_CTRL;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     scramble_region:1;
unsigned int     security_region:1;
unsigned int     tm_out_wr:1;
unsigned int     tm_out_rd:1;
unsigned int     bc_not_empty:1;
unsigned int     pc_range_err:1;
unsigned int     err_reg:1;
unsigned int     mc_dec_err:1;
unsigned int     pp_w_err:1;
unsigned int     pp_r_err:1;
unsigned int     pp_ov:1;
unsigned int     pp_mode_err:1;
unsigned int     reserved_1:5;
unsigned int     k_mcp_error:1;
unsigned int     k_error:1;
unsigned int     k_compare:1;
unsigned int     k_ring_empty:1;
unsigned int     mcp_error:1;
unsigned int     reserved_2:2;
unsigned int     compare:1;
unsigned int     error:1;
unsigned int     ring_empty:1;
unsigned int     write_data:1;
}MCP_STATUS;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     scramble_region_en:1;
unsigned int     cdpu_isr_en:1;
unsigned int     mcp_error_en:1;
unsigned int     reserved_1:2;
unsigned int     compare_en:1;
unsigned int     error_en:1;
unsigned int     ring_empty_en:1;
unsigned int     write_data:1;
}MCP_EN;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     aesh_pad_off:1;
unsigned int     csa_entropy:2;
unsigned int     mcp_round_no:8;
}MCP_CTRL1;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     base:31;
}MCP_BASE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     limit:31;
}MCP_LIMIT;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     rdptr:31;
}MCP_RDPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     wrptr:31;
}MCP_WRPTR;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     count:16;
}MCP_DES_COUNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     compare:16;
}MCP_DES_COMPARE;

typedef struct 
{
unsigned int     data:32;
}MCP_DES_INI_KEY;

typedef struct 
{
unsigned int     data:32;
}MCP_AES_INI_KEY;

typedef struct 
{
unsigned int     data:32;
}MCP_MULTI2_SYS_KEY;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     otp_load:1;
}CP_OTP_LOAD;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     reserved_1:1;
unsigned int     reserved_2:1;
unsigned int     clear:1;
unsigned int     swap:1;
unsigned int     idle:1;
unsigned int     go:1;
unsigned int     write_data:1;
}K_MCP_CTRL;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     scramble_region:1;
unsigned int     security_region:1;
unsigned int     tm_out_wr:1;
unsigned int     tm_out_rd:1;
unsigned int     bc_not_empty:1;
unsigned int     pc_range_err:1;
unsigned int     err_reg:1;
unsigned int     mc_dec_err:1;
unsigned int     pp_w_err:1;
unsigned int     pp_r_err:1;
unsigned int     pp_ov:1;
unsigned int     pp_mode_err:1;
unsigned int     reserved_1:5;
unsigned int     s_mcp_error:1;
unsigned int     s_error:1;
unsigned int     s_compare:1;
unsigned int     s_ring_empty:1;
unsigned int     mcp_error:1;
unsigned int     reserved_2:2;
unsigned int     compare:1;
unsigned int     error:1;
unsigned int     ring_empty:1;
unsigned int     write_data:1;
}K_MCP_STATUS;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     security_region_en:1;
unsigned int     cdpu_isr_en:1;
unsigned int     mcp_error_en:1;
unsigned int     reserved_1:2;
unsigned int     compare_en:1;
unsigned int     error_en:1;
unsigned int     ring_empty_en:1;
unsigned int     write_data:1;
}K_MCP_EN;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     aesh_pad_off:1;
unsigned int     csa_entropy:2;
unsigned int     mcp_round_no:8;
}K_MCP_CTRL1;

typedef struct 
{
unsigned int     base:32;
}K_MCP_BASE;

typedef struct 
{
unsigned int     limit:32;
}K_MCP_LIMIT;

typedef struct 
{
unsigned int     rdptr:32;
}K_MCP_RDPTR;

typedef struct 
{
unsigned int     wrptr:32;
}K_MCP_WRPTR;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     count:16;
}K_MCP_DES_COUNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     compare:16;
}K_MCP_DES_COMPARE;

typedef struct 
{
unsigned int     data:32;
}K_MCP_DES_INI_KEY;

typedef struct 
{
unsigned int     data:32;
}K_MCP_AES_INI_KEY;

typedef struct 
{
unsigned int     data:32;
}K_MCP_MULTI2_SYS_KEY;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     enable:1;
unsigned int     kam:3;
}K_MCP_M2M_DES_KAM;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     rd_sm:4;
unsigned int     wr_sm:3;
unsigned int     reserved_1:10;
unsigned int     mcp_aes_like_sm:11;
}MCP_ST;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     mcp_top_sm:20;
}MCP_ST1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     adr3:10;
unsigned int     reserved_1:6;
unsigned int     adr2:10;
}MC_MAP1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     adr1:10;
unsigned int     reserved_1:6;
unsigned int     adr0:10;
}MC_MAP2;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     pc:10;
}MC_INFO1;

typedef struct 
{
unsigned int     word1:32;
}MC_INFO2;

typedef struct 
{
unsigned int     word2:32;
}MC_INFO3;

typedef struct 
{
unsigned int     word3:32;
}MC_INFO4;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     tmout_ctr:16;
}MC_CTR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rm:4;
unsigned int     rme:1;
unsigned int     drf_test_resume:1;
unsigned int     drf_bist_mode:1;
unsigned int     bist_mode:1;
}MBIST_1;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     drf_bist_fail_5:1;
unsigned int     bist_fail_5:1;
unsigned int     drf_bist_fail_4:1;
unsigned int     bist_fail_4:1;
unsigned int     drf_bist_fail_3:1;
unsigned int     bist_fail_3:1;
unsigned int     drf_bist_fail_2:1;
unsigned int     bist_fail_2:1;
unsigned int     drf_bist_fail_1:1;
unsigned int     bist_fail_1:1;
unsigned int     drf_bist_fail_0:1;
unsigned int     bist_fail_0:1;
unsigned int     drf_start_pause:1;
unsigned int     drf_bist_done:1;
unsigned int     bist_done:1;
}MBIST_2;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     en_cp:1;
unsigned int     en_mcp:1;
unsigned int     en_cdpu:1;
unsigned int     reserved_1:5;
unsigned int     sram_ctr:5;
unsigned int     idle_ctr:10;
}PWM_CTRL;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     write_en3:1;
unsigned int     stop:1;
unsigned int     write_en2:1;
unsigned int     test_mode:2;
unsigned int     write_en1:1;
unsigned int     wait_sec:5;
}RCIC_CTRL;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     write_en7:1;
unsigned int     valid_7:1;
unsigned int     write_en6:1;
unsigned int     valid_6:1;
unsigned int     write_en5:1;
unsigned int     valid_5:1;
unsigned int     write_en4:1;
unsigned int     valid_4:1;
unsigned int     write_en3:1;
unsigned int     valid_3:1;
unsigned int     write_en2:1;
unsigned int     valid_2:1;
unsigned int     write_en1:1;
unsigned int     valid_1:1;
unsigned int     write_en0:1;
unsigned int     valid_0:1;
}RCIC_ENTR_VLD;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     entry:3;
unsigned int     done:1;
}RCIC_STATUS;

typedef struct 
{
unsigned int     adr:32;
}RCIC_ENTR_SRC;

typedef struct 
{
unsigned int     adr:32;
}RCIC_ENTR_DST;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     rcic_bc:1;
unsigned int     int_en:1;
}RCIC_INT_EN;

#endif

#define MCP_CTRL                                                                     0x18015100
#define MCP_CTRL_reg_addr                                                            "0xB8015100"
#define MCP_CTRL_reg                                                                 0xB8015100
#define set_MCP_CTRL_reg(data)   (*((volatile unsigned int*) MCP_CTRL_reg)=data)
#define get_MCP_CTRL_reg   (*((volatile unsigned int*) MCP_CTRL_reg))
#define MCP_CTRL_inst_adr                                                            "0x0040"
#define MCP_CTRL_inst                                                                0x0040
#define MCP_CTRL_arb_mode_shift                                                      (6)
#define MCP_CTRL_arb_mode_mask                                                       (0x00000040)
#define MCP_CTRL_arb_mode(data)                                                      (0x00000040&((data)<<6))
#define MCP_CTRL_arb_mode_src(data)                                                  ((0x00000040&(data))>>6)
#define MCP_CTRL_get_arb_mode(data)                                                  ((0x00000040&(data))>>6)
#define MCP_CTRL_clear_shift                                                         (4)
#define MCP_CTRL_clear_mask                                                          (0x00000010)
#define MCP_CTRL_clear(data)                                                         (0x00000010&((data)<<4))
#define MCP_CTRL_clear_src(data)                                                     ((0x00000010&(data))>>4)
#define MCP_CTRL_get_clear(data)                                                     ((0x00000010&(data))>>4)
#define MCP_CTRL_swap_shift                                                          (3)
#define MCP_CTRL_swap_mask                                                           (0x00000008)
#define MCP_CTRL_swap(data)                                                          (0x00000008&((data)<<3))
#define MCP_CTRL_swap_src(data)                                                      ((0x00000008&(data))>>3)
#define MCP_CTRL_get_swap(data)                                                      ((0x00000008&(data))>>3)
#define MCP_CTRL_idle_shift                                                          (2)
#define MCP_CTRL_idle_mask                                                           (0x00000004)
#define MCP_CTRL_idle(data)                                                          (0x00000004&((data)<<2))
#define MCP_CTRL_idle_src(data)                                                      ((0x00000004&(data))>>2)
#define MCP_CTRL_get_idle(data)                                                      ((0x00000004&(data))>>2)
#define MCP_CTRL_go_shift                                                            (1)
#define MCP_CTRL_go_mask                                                             (0x00000002)
#define MCP_CTRL_go(data)                                                            (0x00000002&((data)<<1))
#define MCP_CTRL_go_src(data)                                                        ((0x00000002&(data))>>1)
#define MCP_CTRL_get_go(data)                                                        ((0x00000002&(data))>>1)
#define MCP_CTRL_write_data_shift                                                    (0)
#define MCP_CTRL_write_data_mask                                                     (0x00000001)
#define MCP_CTRL_write_data(data)                                                    (0x00000001&((data)<<0))
#define MCP_CTRL_write_data_src(data)                                                ((0x00000001&(data))>>0)
#define MCP_CTRL_get_write_data(data)                                                ((0x00000001&(data))>>0)


#define MCP_STATUS                                                                   0x18015104
#define MCP_STATUS_reg_addr                                                          "0xB8015104"
#define MCP_STATUS_reg                                                               0xB8015104
#define set_MCP_STATUS_reg(data)   (*((volatile unsigned int*) MCP_STATUS_reg)=data)
#define get_MCP_STATUS_reg   (*((volatile unsigned int*) MCP_STATUS_reg))
#define MCP_STATUS_inst_adr                                                          "0x0041"
#define MCP_STATUS_inst                                                              0x0041
#define MCP_STATUS_scramble_region_shift                                             (27)
#define MCP_STATUS_scramble_region_mask                                              (0x08000000)
#define MCP_STATUS_scramble_region(data)                                             (0x08000000&((data)<<27))
#define MCP_STATUS_scramble_region_src(data)                                         ((0x08000000&(data))>>27)
#define MCP_STATUS_get_scramble_region(data)                                         ((0x08000000&(data))>>27)
#define MCP_STATUS_security_region_shift                                             (26)
#define MCP_STATUS_security_region_mask                                              (0x04000000)
#define MCP_STATUS_security_region(data)                                             (0x04000000&((data)<<26))
#define MCP_STATUS_security_region_src(data)                                         ((0x04000000&(data))>>26)
#define MCP_STATUS_get_security_region(data)                                         ((0x04000000&(data))>>26)
#define MCP_STATUS_tm_out_wr_shift                                                   (25)
#define MCP_STATUS_tm_out_wr_mask                                                    (0x02000000)
#define MCP_STATUS_tm_out_wr(data)                                                   (0x02000000&((data)<<25))
#define MCP_STATUS_tm_out_wr_src(data)                                               ((0x02000000&(data))>>25)
#define MCP_STATUS_get_tm_out_wr(data)                                               ((0x02000000&(data))>>25)
#define MCP_STATUS_tm_out_rd_shift                                                   (24)
#define MCP_STATUS_tm_out_rd_mask                                                    (0x01000000)
#define MCP_STATUS_tm_out_rd(data)                                                   (0x01000000&((data)<<24))
#define MCP_STATUS_tm_out_rd_src(data)                                               ((0x01000000&(data))>>24)
#define MCP_STATUS_get_tm_out_rd(data)                                               ((0x01000000&(data))>>24)
#define MCP_STATUS_bc_not_empty_shift                                                (23)
#define MCP_STATUS_bc_not_empty_mask                                                 (0x00800000)
#define MCP_STATUS_bc_not_empty(data)                                                (0x00800000&((data)<<23))
#define MCP_STATUS_bc_not_empty_src(data)                                            ((0x00800000&(data))>>23)
#define MCP_STATUS_get_bc_not_empty(data)                                            ((0x00800000&(data))>>23)
#define MCP_STATUS_pc_range_err_shift                                                (22)
#define MCP_STATUS_pc_range_err_mask                                                 (0x00400000)
#define MCP_STATUS_pc_range_err(data)                                                (0x00400000&((data)<<22))
#define MCP_STATUS_pc_range_err_src(data)                                            ((0x00400000&(data))>>22)
#define MCP_STATUS_get_pc_range_err(data)                                            ((0x00400000&(data))>>22)
#define MCP_STATUS_err_reg_shift                                                     (21)
#define MCP_STATUS_err_reg_mask                                                      (0x00200000)
#define MCP_STATUS_err_reg(data)                                                     (0x00200000&((data)<<21))
#define MCP_STATUS_err_reg_src(data)                                                 ((0x00200000&(data))>>21)
#define MCP_STATUS_get_err_reg(data)                                                 ((0x00200000&(data))>>21)
#define MCP_STATUS_mc_dec_err_shift                                                  (20)
#define MCP_STATUS_mc_dec_err_mask                                                   (0x00100000)
#define MCP_STATUS_mc_dec_err(data)                                                  (0x00100000&((data)<<20))
#define MCP_STATUS_mc_dec_err_src(data)                                              ((0x00100000&(data))>>20)
#define MCP_STATUS_get_mc_dec_err(data)                                              ((0x00100000&(data))>>20)
#define MCP_STATUS_pp_w_err_shift                                                    (19)
#define MCP_STATUS_pp_w_err_mask                                                     (0x00080000)
#define MCP_STATUS_pp_w_err(data)                                                    (0x00080000&((data)<<19))
#define MCP_STATUS_pp_w_err_src(data)                                                ((0x00080000&(data))>>19)
#define MCP_STATUS_get_pp_w_err(data)                                                ((0x00080000&(data))>>19)
#define MCP_STATUS_pp_r_err_shift                                                    (18)
#define MCP_STATUS_pp_r_err_mask                                                     (0x00040000)
#define MCP_STATUS_pp_r_err(data)                                                    (0x00040000&((data)<<18))
#define MCP_STATUS_pp_r_err_src(data)                                                ((0x00040000&(data))>>18)
#define MCP_STATUS_get_pp_r_err(data)                                                ((0x00040000&(data))>>18)
#define MCP_STATUS_pp_ov_shift                                                       (17)
#define MCP_STATUS_pp_ov_mask                                                        (0x00020000)
#define MCP_STATUS_pp_ov(data)                                                       (0x00020000&((data)<<17))
#define MCP_STATUS_pp_ov_src(data)                                                   ((0x00020000&(data))>>17)
#define MCP_STATUS_get_pp_ov(data)                                                   ((0x00020000&(data))>>17)
#define MCP_STATUS_pp_mode_err_shift                                                 (16)
#define MCP_STATUS_pp_mode_err_mask                                                  (0x00010000)
#define MCP_STATUS_pp_mode_err(data)                                                 (0x00010000&((data)<<16))
#define MCP_STATUS_pp_mode_err_src(data)                                             ((0x00010000&(data))>>16)
#define MCP_STATUS_get_pp_mode_err(data)                                             ((0x00010000&(data))>>16)
#define MCP_STATUS_k_mcp_error_shift                                                 (10)
#define MCP_STATUS_k_mcp_error_mask                                                  (0x00000400)
#define MCP_STATUS_k_mcp_error(data)                                                 (0x00000400&((data)<<10))
#define MCP_STATUS_k_mcp_error_src(data)                                             ((0x00000400&(data))>>10)
#define MCP_STATUS_get_k_mcp_error(data)                                             ((0x00000400&(data))>>10)
#define MCP_STATUS_k_error_shift                                                     (9)
#define MCP_STATUS_k_error_mask                                                      (0x00000200)
#define MCP_STATUS_k_error(data)                                                     (0x00000200&((data)<<9))
#define MCP_STATUS_k_error_src(data)                                                 ((0x00000200&(data))>>9)
#define MCP_STATUS_get_k_error(data)                                                 ((0x00000200&(data))>>9)
#define MCP_STATUS_k_compare_shift                                                   (8)
#define MCP_STATUS_k_compare_mask                                                    (0x00000100)
#define MCP_STATUS_k_compare(data)                                                   (0x00000100&((data)<<8))
#define MCP_STATUS_k_compare_src(data)                                               ((0x00000100&(data))>>8)
#define MCP_STATUS_get_k_compare(data)                                               ((0x00000100&(data))>>8)
#define MCP_STATUS_k_ring_empty_shift                                                (7)
#define MCP_STATUS_k_ring_empty_mask                                                 (0x00000080)
#define MCP_STATUS_k_ring_empty(data)                                                (0x00000080&((data)<<7))
#define MCP_STATUS_k_ring_empty_src(data)                                            ((0x00000080&(data))>>7)
#define MCP_STATUS_get_k_ring_empty(data)                                            ((0x00000080&(data))>>7)
#define MCP_STATUS_mcp_error_shift                                                   (6)
#define MCP_STATUS_mcp_error_mask                                                    (0x00000040)
#define MCP_STATUS_mcp_error(data)                                                   (0x00000040&((data)<<6))
#define MCP_STATUS_mcp_error_src(data)                                               ((0x00000040&(data))>>6)
#define MCP_STATUS_get_mcp_error(data)                                               ((0x00000040&(data))>>6)
#define MCP_STATUS_compare_shift                                                     (3)
#define MCP_STATUS_compare_mask                                                      (0x00000008)
#define MCP_STATUS_compare(data)                                                     (0x00000008&((data)<<3))
#define MCP_STATUS_compare_src(data)                                                 ((0x00000008&(data))>>3)
#define MCP_STATUS_get_compare(data)                                                 ((0x00000008&(data))>>3)
#define MCP_STATUS_error_shift                                                       (2)
#define MCP_STATUS_error_mask                                                        (0x00000004)
#define MCP_STATUS_error(data)                                                       (0x00000004&((data)<<2))
#define MCP_STATUS_error_src(data)                                                   ((0x00000004&(data))>>2)
#define MCP_STATUS_get_error(data)                                                   ((0x00000004&(data))>>2)
#define MCP_STATUS_ring_empty_shift                                                  (1)
#define MCP_STATUS_ring_empty_mask                                                   (0x00000002)
#define MCP_STATUS_ring_empty(data)                                                  (0x00000002&((data)<<1))
#define MCP_STATUS_ring_empty_src(data)                                              ((0x00000002&(data))>>1)
#define MCP_STATUS_get_ring_empty(data)                                              ((0x00000002&(data))>>1)
#define MCP_STATUS_write_data_shift                                                  (0)
#define MCP_STATUS_write_data_mask                                                   (0x00000001)
#define MCP_STATUS_write_data(data)                                                  (0x00000001&((data)<<0))
#define MCP_STATUS_write_data_src(data)                                              ((0x00000001&(data))>>0)
#define MCP_STATUS_get_write_data(data)                                              ((0x00000001&(data))>>0)


#define MCP_EN                                                                       0x18015108
#define MCP_EN_reg_addr                                                              "0xB8015108"
#define MCP_EN_reg                                                                   0xB8015108
#define set_MCP_EN_reg(data)   (*((volatile unsigned int*) MCP_EN_reg)=data)
#define get_MCP_EN_reg   (*((volatile unsigned int*) MCP_EN_reg))
#define MCP_EN_inst_adr                                                              "0x0042"
#define MCP_EN_inst                                                                  0x0042
#define MCP_EN_scramble_region_en_shift                                              (8)
#define MCP_EN_scramble_region_en_mask                                               (0x00000100)
#define MCP_EN_scramble_region_en(data)                                              (0x00000100&((data)<<8))
#define MCP_EN_scramble_region_en_src(data)                                          ((0x00000100&(data))>>8)
#define MCP_EN_get_scramble_region_en(data)                                          ((0x00000100&(data))>>8)
#define MCP_EN_cdpu_isr_en_shift                                                     (7)
#define MCP_EN_cdpu_isr_en_mask                                                      (0x00000080)
#define MCP_EN_cdpu_isr_en(data)                                                     (0x00000080&((data)<<7))
#define MCP_EN_cdpu_isr_en_src(data)                                                 ((0x00000080&(data))>>7)
#define MCP_EN_get_cdpu_isr_en(data)                                                 ((0x00000080&(data))>>7)
#define MCP_EN_mcp_error_en_shift                                                    (6)
#define MCP_EN_mcp_error_en_mask                                                     (0x00000040)
#define MCP_EN_mcp_error_en(data)                                                    (0x00000040&((data)<<6))
#define MCP_EN_mcp_error_en_src(data)                                                ((0x00000040&(data))>>6)
#define MCP_EN_get_mcp_error_en(data)                                                ((0x00000040&(data))>>6)
#define MCP_EN_compare_en_shift                                                      (3)
#define MCP_EN_compare_en_mask                                                       (0x00000008)
#define MCP_EN_compare_en(data)                                                      (0x00000008&((data)<<3))
#define MCP_EN_compare_en_src(data)                                                  ((0x00000008&(data))>>3)
#define MCP_EN_get_compare_en(data)                                                  ((0x00000008&(data))>>3)
#define MCP_EN_error_en_shift                                                        (2)
#define MCP_EN_error_en_mask                                                         (0x00000004)
#define MCP_EN_error_en(data)                                                        (0x00000004&((data)<<2))
#define MCP_EN_error_en_src(data)                                                    ((0x00000004&(data))>>2)
#define MCP_EN_get_error_en(data)                                                    ((0x00000004&(data))>>2)
#define MCP_EN_ring_empty_en_shift                                                   (1)
#define MCP_EN_ring_empty_en_mask                                                    (0x00000002)
#define MCP_EN_ring_empty_en(data)                                                   (0x00000002&((data)<<1))
#define MCP_EN_ring_empty_en_src(data)                                               ((0x00000002&(data))>>1)
#define MCP_EN_get_ring_empty_en(data)                                               ((0x00000002&(data))>>1)
#define MCP_EN_write_data_shift                                                      (0)
#define MCP_EN_write_data_mask                                                       (0x00000001)
#define MCP_EN_write_data(data)                                                      (0x00000001&((data)<<0))
#define MCP_EN_write_data_src(data)                                                  ((0x00000001&(data))>>0)
#define MCP_EN_get_write_data(data)                                                  ((0x00000001&(data))>>0)


#define MCP_CTRL1                                                                    0x18015198
#define MCP_CTRL1_reg_addr                                                           "0xB8015198"
#define MCP_CTRL1_reg                                                                0xB8015198
#define set_MCP_CTRL1_reg(data)   (*((volatile unsigned int*) MCP_CTRL1_reg)=data)
#define get_MCP_CTRL1_reg   (*((volatile unsigned int*) MCP_CTRL1_reg))
#define MCP_CTRL1_inst_adr                                                           "0x0066"
#define MCP_CTRL1_inst                                                               0x0066
#define MCP_CTRL1_aesh_pad_off_shift                                                 (10)
#define MCP_CTRL1_aesh_pad_off_mask                                                  (0x00000400)
#define MCP_CTRL1_aesh_pad_off(data)                                                 (0x00000400&((data)<<10))
#define MCP_CTRL1_aesh_pad_off_src(data)                                             ((0x00000400&(data))>>10)
#define MCP_CTRL1_get_aesh_pad_off(data)                                             ((0x00000400&(data))>>10)
#define MCP_CTRL1_csa_entropy_shift                                                  (8)
#define MCP_CTRL1_csa_entropy_mask                                                   (0x00000300)
#define MCP_CTRL1_csa_entropy(data)                                                  (0x00000300&((data)<<8))
#define MCP_CTRL1_csa_entropy_src(data)                                              ((0x00000300&(data))>>8)
#define MCP_CTRL1_get_csa_entropy(data)                                              ((0x00000300&(data))>>8)
#define MCP_CTRL1_mcp_round_no_shift                                                 (0)
#define MCP_CTRL1_mcp_round_no_mask                                                  (0x000000FF)
#define MCP_CTRL1_mcp_round_no(data)                                                 (0x000000FF&((data)<<0))
#define MCP_CTRL1_mcp_round_no_src(data)                                             ((0x000000FF&(data))>>0)
#define MCP_CTRL1_get_mcp_round_no(data)                                             ((0x000000FF&(data))>>0)


#define MCP_BASE                                                                     0x1801510C
#define MCP_BASE_reg_addr                                                            "0xB801510C"
#define MCP_BASE_reg                                                                 0xB801510C
#define set_MCP_BASE_reg(data)   (*((volatile unsigned int*) MCP_BASE_reg)=data)
#define get_MCP_BASE_reg   (*((volatile unsigned int*) MCP_BASE_reg))
#define MCP_BASE_inst_adr                                                            "0x0043"
#define MCP_BASE_inst                                                                0x0043
#define MCP_BASE_base_shift                                                          (0)
#define MCP_BASE_base_mask                                                           (0x7FFFFFFF)
#define MCP_BASE_base(data)                                                          (0x7FFFFFFF&((data)<<0))
#define MCP_BASE_base_src(data)                                                      ((0x7FFFFFFF&(data))>>0)
#define MCP_BASE_get_base(data)                                                      ((0x7FFFFFFF&(data))>>0)


#define MCP_LIMIT                                                                    0x18015110
#define MCP_LIMIT_reg_addr                                                           "0xB8015110"
#define MCP_LIMIT_reg                                                                0xB8015110
#define set_MCP_LIMIT_reg(data)   (*((volatile unsigned int*) MCP_LIMIT_reg)=data)
#define get_MCP_LIMIT_reg   (*((volatile unsigned int*) MCP_LIMIT_reg))
#define MCP_LIMIT_inst_adr                                                           "0x0044"
#define MCP_LIMIT_inst                                                               0x0044
#define MCP_LIMIT_limit_shift                                                        (0)
#define MCP_LIMIT_limit_mask                                                         (0x7FFFFFFF)
#define MCP_LIMIT_limit(data)                                                        (0x7FFFFFFF&((data)<<0))
#define MCP_LIMIT_limit_src(data)                                                    ((0x7FFFFFFF&(data))>>0)
#define MCP_LIMIT_get_limit(data)                                                    ((0x7FFFFFFF&(data))>>0)


#define MCP_RDPTR                                                                    0x18015114
#define MCP_RDPTR_reg_addr                                                           "0xB8015114"
#define MCP_RDPTR_reg                                                                0xB8015114
#define set_MCP_RDPTR_reg(data)   (*((volatile unsigned int*) MCP_RDPTR_reg)=data)
#define get_MCP_RDPTR_reg   (*((volatile unsigned int*) MCP_RDPTR_reg))
#define MCP_RDPTR_inst_adr                                                           "0x0045"
#define MCP_RDPTR_inst                                                               0x0045
#define MCP_RDPTR_rdptr_shift                                                        (0)
#define MCP_RDPTR_rdptr_mask                                                         (0x7FFFFFFF)
#define MCP_RDPTR_rdptr(data)                                                        (0x7FFFFFFF&((data)<<0))
#define MCP_RDPTR_rdptr_src(data)                                                    ((0x7FFFFFFF&(data))>>0)
#define MCP_RDPTR_get_rdptr(data)                                                    ((0x7FFFFFFF&(data))>>0)


#define MCP_WRPTR                                                                    0x18015118
#define MCP_WRPTR_reg_addr                                                           "0xB8015118"
#define MCP_WRPTR_reg                                                                0xB8015118
#define set_MCP_WRPTR_reg(data)   (*((volatile unsigned int*) MCP_WRPTR_reg)=data)
#define get_MCP_WRPTR_reg   (*((volatile unsigned int*) MCP_WRPTR_reg))
#define MCP_WRPTR_inst_adr                                                           "0x0046"
#define MCP_WRPTR_inst                                                               0x0046
#define MCP_WRPTR_wrptr_shift                                                        (0)
#define MCP_WRPTR_wrptr_mask                                                         (0x7FFFFFFF)
#define MCP_WRPTR_wrptr(data)                                                        (0x7FFFFFFF&((data)<<0))
#define MCP_WRPTR_wrptr_src(data)                                                    ((0x7FFFFFFF&(data))>>0)
#define MCP_WRPTR_get_wrptr(data)                                                    ((0x7FFFFFFF&(data))>>0)


#define MCP_DES_COUNT                                                                0x18015134
#define MCP_DES_COUNT_reg_addr                                                       "0xB8015134"
#define MCP_DES_COUNT_reg                                                            0xB8015134
#define set_MCP_DES_COUNT_reg(data)   (*((volatile unsigned int*) MCP_DES_COUNT_reg)=data)
#define get_MCP_DES_COUNT_reg   (*((volatile unsigned int*) MCP_DES_COUNT_reg))
#define MCP_DES_COUNT_inst_adr                                                       "0x004D"
#define MCP_DES_COUNT_inst                                                           0x004D
#define MCP_DES_COUNT_count_shift                                                    (0)
#define MCP_DES_COUNT_count_mask                                                     (0x0000FFFF)
#define MCP_DES_COUNT_count(data)                                                    (0x0000FFFF&((data)<<0))
#define MCP_DES_COUNT_count_src(data)                                                ((0x0000FFFF&(data))>>0)
#define MCP_DES_COUNT_get_count(data)                                                ((0x0000FFFF&(data))>>0)


#define MCP_DES_COMPARE                                                              0x18015138
#define MCP_DES_COMPARE_reg_addr                                                     "0xB8015138"
#define MCP_DES_COMPARE_reg                                                          0xB8015138
#define set_MCP_DES_COMPARE_reg(data)   (*((volatile unsigned int*) MCP_DES_COMPARE_reg)=data)
#define get_MCP_DES_COMPARE_reg   (*((volatile unsigned int*) MCP_DES_COMPARE_reg))
#define MCP_DES_COMPARE_inst_adr                                                     "0x004E"
#define MCP_DES_COMPARE_inst                                                         0x004E
#define MCP_DES_COMPARE_compare_shift                                                (0)
#define MCP_DES_COMPARE_compare_mask                                                 (0x0000FFFF)
#define MCP_DES_COMPARE_compare(data)                                                (0x0000FFFF&((data)<<0))
#define MCP_DES_COMPARE_compare_src(data)                                            ((0x0000FFFF&(data))>>0)
#define MCP_DES_COMPARE_get_compare(data)                                            ((0x0000FFFF&(data))>>0)


#define MCP_DES_INI_KEY_0                                                            0x1801511C
#define MCP_DES_INI_KEY_1                                                            0x18015120
#define MCP_DES_INI_KEY_0_reg_addr                                                   "0xB801511C"
#define MCP_DES_INI_KEY_1_reg_addr                                                   "0xB8015120"
#define MCP_DES_INI_KEY_0_reg                                                        0xB801511C
#define MCP_DES_INI_KEY_1_reg                                                        0xB8015120
#define set_MCP_DES_INI_KEY_0_reg(data)   (*((volatile unsigned int*) MCP_DES_INI_KEY_0_reg)=data)
#define set_MCP_DES_INI_KEY_1_reg(data)   (*((volatile unsigned int*) MCP_DES_INI_KEY_1_reg)=data)
#define get_MCP_DES_INI_KEY_0_reg   (*((volatile unsigned int*) MCP_DES_INI_KEY_0_reg))
#define get_MCP_DES_INI_KEY_1_reg   (*((volatile unsigned int*) MCP_DES_INI_KEY_1_reg))
#define MCP_DES_INI_KEY_0_inst_adr                                                   "0x0047"
#define MCP_DES_INI_KEY_1_inst_adr                                                   "0x0048"
#define MCP_DES_INI_KEY_0_inst                                                       0x0047
#define MCP_DES_INI_KEY_1_inst                                                       0x0048
#define MCP_DES_INI_KEY_data_shift                                                   (0)
#define MCP_DES_INI_KEY_data_mask                                                    (0xFFFFFFFF)
#define MCP_DES_INI_KEY_data(data)                                                   (0xFFFFFFFF&((data)<<0))
#define MCP_DES_INI_KEY_data_src(data)                                               ((0xFFFFFFFF&(data))>>0)
#define MCP_DES_INI_KEY_get_data(data)                                               ((0xFFFFFFFF&(data))>>0)


#define MCP_AES_INI_KEY_0                                                            0x18015124
#define MCP_AES_INI_KEY_1                                                            0x18015128
#define MCP_AES_INI_KEY_2                                                            0x1801512C
#define MCP_AES_INI_KEY_3                                                            0x18015130
#define MCP_AES_INI_KEY_0_reg_addr                                                   "0xB8015124"
#define MCP_AES_INI_KEY_1_reg_addr                                                   "0xB8015128"
#define MCP_AES_INI_KEY_2_reg_addr                                                   "0xB801512C"
#define MCP_AES_INI_KEY_3_reg_addr                                                   "0xB8015130"
#define MCP_AES_INI_KEY_0_reg                                                        0xB8015124
#define MCP_AES_INI_KEY_1_reg                                                        0xB8015128
#define MCP_AES_INI_KEY_2_reg                                                        0xB801512C
#define MCP_AES_INI_KEY_3_reg                                                        0xB8015130
#define set_MCP_AES_INI_KEY_0_reg(data)   (*((volatile unsigned int*) MCP_AES_INI_KEY_0_reg)=data)
#define set_MCP_AES_INI_KEY_1_reg(data)   (*((volatile unsigned int*) MCP_AES_INI_KEY_1_reg)=data)
#define set_MCP_AES_INI_KEY_2_reg(data)   (*((volatile unsigned int*) MCP_AES_INI_KEY_2_reg)=data)
#define set_MCP_AES_INI_KEY_3_reg(data)   (*((volatile unsigned int*) MCP_AES_INI_KEY_3_reg)=data)
#define get_MCP_AES_INI_KEY_0_reg   (*((volatile unsigned int*) MCP_AES_INI_KEY_0_reg))
#define get_MCP_AES_INI_KEY_1_reg   (*((volatile unsigned int*) MCP_AES_INI_KEY_1_reg))
#define get_MCP_AES_INI_KEY_2_reg   (*((volatile unsigned int*) MCP_AES_INI_KEY_2_reg))
#define get_MCP_AES_INI_KEY_3_reg   (*((volatile unsigned int*) MCP_AES_INI_KEY_3_reg))
#define MCP_AES_INI_KEY_0_inst_adr                                                   "0x0049"
#define MCP_AES_INI_KEY_1_inst_adr                                                   "0x004A"
#define MCP_AES_INI_KEY_2_inst_adr                                                   "0x004B"
#define MCP_AES_INI_KEY_3_inst_adr                                                   "0x004C"
#define MCP_AES_INI_KEY_0_inst                                                       0x0049
#define MCP_AES_INI_KEY_1_inst                                                       0x004A
#define MCP_AES_INI_KEY_2_inst                                                       0x004B
#define MCP_AES_INI_KEY_3_inst                                                       0x004C
#define MCP_AES_INI_KEY_data_shift                                                   (0)
#define MCP_AES_INI_KEY_data_mask                                                    (0xFFFFFFFF)
#define MCP_AES_INI_KEY_data(data)                                                   (0xFFFFFFFF&((data)<<0))
#define MCP_AES_INI_KEY_data_src(data)                                               ((0xFFFFFFFF&(data))>>0)
#define MCP_AES_INI_KEY_get_data(data)                                               ((0xFFFFFFFF&(data))>>0)


#define MCP_MULTI2_SYS_KEY_0                                                         0x18015178
#define MCP_MULTI2_SYS_KEY_1                                                         0x1801517C
#define MCP_MULTI2_SYS_KEY_2                                                         0x18015180
#define MCP_MULTI2_SYS_KEY_3                                                         0x18015184
#define MCP_MULTI2_SYS_KEY_4                                                         0x18015188
#define MCP_MULTI2_SYS_KEY_5                                                         0x1801518C
#define MCP_MULTI2_SYS_KEY_6                                                         0x18015190
#define MCP_MULTI2_SYS_KEY_7                                                         0x18015194
#define MCP_MULTI2_SYS_KEY_0_reg_addr                                                "0xB8015178"
#define MCP_MULTI2_SYS_KEY_1_reg_addr                                                "0xB801517C"
#define MCP_MULTI2_SYS_KEY_2_reg_addr                                                "0xB8015180"
#define MCP_MULTI2_SYS_KEY_3_reg_addr                                                "0xB8015184"
#define MCP_MULTI2_SYS_KEY_4_reg_addr                                                "0xB8015188"
#define MCP_MULTI2_SYS_KEY_5_reg_addr                                                "0xB801518C"
#define MCP_MULTI2_SYS_KEY_6_reg_addr                                                "0xB8015190"
#define MCP_MULTI2_SYS_KEY_7_reg_addr                                                "0xB8015194"
#define MCP_MULTI2_SYS_KEY_0_reg                                                     0xB8015178
#define MCP_MULTI2_SYS_KEY_1_reg                                                     0xB801517C
#define MCP_MULTI2_SYS_KEY_2_reg                                                     0xB8015180
#define MCP_MULTI2_SYS_KEY_3_reg                                                     0xB8015184
#define MCP_MULTI2_SYS_KEY_4_reg                                                     0xB8015188
#define MCP_MULTI2_SYS_KEY_5_reg                                                     0xB801518C
#define MCP_MULTI2_SYS_KEY_6_reg                                                     0xB8015190
#define MCP_MULTI2_SYS_KEY_7_reg                                                     0xB8015194
#define set_MCP_MULTI2_SYS_KEY_0_reg(data)   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_0_reg)=data)
#define set_MCP_MULTI2_SYS_KEY_1_reg(data)   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_1_reg)=data)
#define set_MCP_MULTI2_SYS_KEY_2_reg(data)   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_2_reg)=data)
#define set_MCP_MULTI2_SYS_KEY_3_reg(data)   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_3_reg)=data)
#define set_MCP_MULTI2_SYS_KEY_4_reg(data)   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_4_reg)=data)
#define set_MCP_MULTI2_SYS_KEY_5_reg(data)   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_5_reg)=data)
#define set_MCP_MULTI2_SYS_KEY_6_reg(data)   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_6_reg)=data)
#define set_MCP_MULTI2_SYS_KEY_7_reg(data)   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_7_reg)=data)
#define get_MCP_MULTI2_SYS_KEY_0_reg   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_0_reg))
#define get_MCP_MULTI2_SYS_KEY_1_reg   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_1_reg))
#define get_MCP_MULTI2_SYS_KEY_2_reg   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_2_reg))
#define get_MCP_MULTI2_SYS_KEY_3_reg   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_3_reg))
#define get_MCP_MULTI2_SYS_KEY_4_reg   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_4_reg))
#define get_MCP_MULTI2_SYS_KEY_5_reg   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_5_reg))
#define get_MCP_MULTI2_SYS_KEY_6_reg   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_6_reg))
#define get_MCP_MULTI2_SYS_KEY_7_reg   (*((volatile unsigned int*) MCP_MULTI2_SYS_KEY_7_reg))
#define MCP_MULTI2_SYS_KEY_0_inst_adr                                                "0x005E"
#define MCP_MULTI2_SYS_KEY_1_inst_adr                                                "0x005F"
#define MCP_MULTI2_SYS_KEY_2_inst_adr                                                "0x0060"
#define MCP_MULTI2_SYS_KEY_3_inst_adr                                                "0x0061"
#define MCP_MULTI2_SYS_KEY_4_inst_adr                                                "0x0062"
#define MCP_MULTI2_SYS_KEY_5_inst_adr                                                "0x0063"
#define MCP_MULTI2_SYS_KEY_6_inst_adr                                                "0x0064"
#define MCP_MULTI2_SYS_KEY_7_inst_adr                                                "0x0065"
#define MCP_MULTI2_SYS_KEY_0_inst                                                    0x005E
#define MCP_MULTI2_SYS_KEY_1_inst                                                    0x005F
#define MCP_MULTI2_SYS_KEY_2_inst                                                    0x0060
#define MCP_MULTI2_SYS_KEY_3_inst                                                    0x0061
#define MCP_MULTI2_SYS_KEY_4_inst                                                    0x0062
#define MCP_MULTI2_SYS_KEY_5_inst                                                    0x0063
#define MCP_MULTI2_SYS_KEY_6_inst                                                    0x0064
#define MCP_MULTI2_SYS_KEY_7_inst                                                    0x0065
#define MCP_MULTI2_SYS_KEY_data_shift                                                (0)
#define MCP_MULTI2_SYS_KEY_data_mask                                                 (0xFFFFFFFF)
#define MCP_MULTI2_SYS_KEY_data(data)                                                (0xFFFFFFFF&((data)<<0))
#define MCP_MULTI2_SYS_KEY_data_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define MCP_MULTI2_SYS_KEY_get_data(data)                                            ((0xFFFFFFFF&(data))>>0)


#define CP_OTP_LOAD                                                                  0x1801519C
#define CP_OTP_LOAD_reg_addr                                                         "0xB801519C"
#define CP_OTP_LOAD_reg                                                              0xB801519C
#define set_CP_OTP_LOAD_reg(data)   (*((volatile unsigned int*) CP_OTP_LOAD_reg)=data)
#define get_CP_OTP_LOAD_reg   (*((volatile unsigned int*) CP_OTP_LOAD_reg))
#define CP_OTP_LOAD_inst_adr                                                         "0x0067"
#define CP_OTP_LOAD_inst                                                             0x0067
#define CP_OTP_LOAD_otp_load_shift                                                   (0)
#define CP_OTP_LOAD_otp_load_mask                                                    (0x00000001)
#define CP_OTP_LOAD_otp_load(data)                                                   (0x00000001&((data)<<0))
#define CP_OTP_LOAD_otp_load_src(data)                                               ((0x00000001&(data))>>0)
#define CP_OTP_LOAD_get_otp_load(data)                                               ((0x00000001&(data))>>0)


#define K_MCP_CTRL                                                                   0x18015900
#define K_MCP_CTRL_reg_addr                                                          "0xB8015900"
#define K_MCP_CTRL_reg                                                               0xB8015900
#define set_K_MCP_CTRL_reg(data)   (*((volatile unsigned int*) K_MCP_CTRL_reg)=data)
#define get_K_MCP_CTRL_reg   (*((volatile unsigned int*) K_MCP_CTRL_reg))
#define K_MCP_CTRL_inst_adr                                                          "0x0040"
#define K_MCP_CTRL_inst                                                              0x0040
#define K_MCP_CTRL_clear_shift                                                       (4)
#define K_MCP_CTRL_clear_mask                                                        (0x00000010)
#define K_MCP_CTRL_clear(data)                                                       (0x00000010&((data)<<4))
#define K_MCP_CTRL_clear_src(data)                                                   ((0x00000010&(data))>>4)
#define K_MCP_CTRL_get_clear(data)                                                   ((0x00000010&(data))>>4)
#define K_MCP_CTRL_swap_shift                                                        (3)
#define K_MCP_CTRL_swap_mask                                                         (0x00000008)
#define K_MCP_CTRL_swap(data)                                                        (0x00000008&((data)<<3))
#define K_MCP_CTRL_swap_src(data)                                                    ((0x00000008&(data))>>3)
#define K_MCP_CTRL_get_swap(data)                                                    ((0x00000008&(data))>>3)
#define K_MCP_CTRL_idle_shift                                                        (2)
#define K_MCP_CTRL_idle_mask                                                         (0x00000004)
#define K_MCP_CTRL_idle(data)                                                        (0x00000004&((data)<<2))
#define K_MCP_CTRL_idle_src(data)                                                    ((0x00000004&(data))>>2)
#define K_MCP_CTRL_get_idle(data)                                                    ((0x00000004&(data))>>2)
#define K_MCP_CTRL_go_shift                                                          (1)
#define K_MCP_CTRL_go_mask                                                           (0x00000002)
#define K_MCP_CTRL_go(data)                                                          (0x00000002&((data)<<1))
#define K_MCP_CTRL_go_src(data)                                                      ((0x00000002&(data))>>1)
#define K_MCP_CTRL_get_go(data)                                                      ((0x00000002&(data))>>1)
#define K_MCP_CTRL_write_data_shift                                                  (0)
#define K_MCP_CTRL_write_data_mask                                                   (0x00000001)
#define K_MCP_CTRL_write_data(data)                                                  (0x00000001&((data)<<0))
#define K_MCP_CTRL_write_data_src(data)                                              ((0x00000001&(data))>>0)
#define K_MCP_CTRL_get_write_data(data)                                              ((0x00000001&(data))>>0)


#define K_MCP_STATUS                                                                 0x18015904
#define K_MCP_STATUS_reg_addr                                                        "0xB8015904"
#define K_MCP_STATUS_reg                                                             0xB8015904
#define set_K_MCP_STATUS_reg(data)   (*((volatile unsigned int*) K_MCP_STATUS_reg)=data)
#define get_K_MCP_STATUS_reg   (*((volatile unsigned int*) K_MCP_STATUS_reg))
#define K_MCP_STATUS_inst_adr                                                        "0x0041"
#define K_MCP_STATUS_inst                                                            0x0041
#define K_MCP_STATUS_scramble_region_shift                                           (27)
#define K_MCP_STATUS_scramble_region_mask                                            (0x08000000)
#define K_MCP_STATUS_scramble_region(data)                                           (0x08000000&((data)<<27))
#define K_MCP_STATUS_scramble_region_src(data)                                       ((0x08000000&(data))>>27)
#define K_MCP_STATUS_get_scramble_region(data)                                       ((0x08000000&(data))>>27)
#define K_MCP_STATUS_security_region_shift                                           (26)
#define K_MCP_STATUS_security_region_mask                                            (0x04000000)
#define K_MCP_STATUS_security_region(data)                                           (0x04000000&((data)<<26))
#define K_MCP_STATUS_security_region_src(data)                                       ((0x04000000&(data))>>26)
#define K_MCP_STATUS_get_security_region(data)                                       ((0x04000000&(data))>>26)
#define K_MCP_STATUS_tm_out_wr_shift                                                 (25)
#define K_MCP_STATUS_tm_out_wr_mask                                                  (0x02000000)
#define K_MCP_STATUS_tm_out_wr(data)                                                 (0x02000000&((data)<<25))
#define K_MCP_STATUS_tm_out_wr_src(data)                                             ((0x02000000&(data))>>25)
#define K_MCP_STATUS_get_tm_out_wr(data)                                             ((0x02000000&(data))>>25)
#define K_MCP_STATUS_tm_out_rd_shift                                                 (24)
#define K_MCP_STATUS_tm_out_rd_mask                                                  (0x01000000)
#define K_MCP_STATUS_tm_out_rd(data)                                                 (0x01000000&((data)<<24))
#define K_MCP_STATUS_tm_out_rd_src(data)                                             ((0x01000000&(data))>>24)
#define K_MCP_STATUS_get_tm_out_rd(data)                                             ((0x01000000&(data))>>24)
#define K_MCP_STATUS_bc_not_empty_shift                                              (23)
#define K_MCP_STATUS_bc_not_empty_mask                                               (0x00800000)
#define K_MCP_STATUS_bc_not_empty(data)                                              (0x00800000&((data)<<23))
#define K_MCP_STATUS_bc_not_empty_src(data)                                          ((0x00800000&(data))>>23)
#define K_MCP_STATUS_get_bc_not_empty(data)                                          ((0x00800000&(data))>>23)
#define K_MCP_STATUS_pc_range_err_shift                                              (22)
#define K_MCP_STATUS_pc_range_err_mask                                               (0x00400000)
#define K_MCP_STATUS_pc_range_err(data)                                              (0x00400000&((data)<<22))
#define K_MCP_STATUS_pc_range_err_src(data)                                          ((0x00400000&(data))>>22)
#define K_MCP_STATUS_get_pc_range_err(data)                                          ((0x00400000&(data))>>22)
#define K_MCP_STATUS_err_reg_shift                                                   (21)
#define K_MCP_STATUS_err_reg_mask                                                    (0x00200000)
#define K_MCP_STATUS_err_reg(data)                                                   (0x00200000&((data)<<21))
#define K_MCP_STATUS_err_reg_src(data)                                               ((0x00200000&(data))>>21)
#define K_MCP_STATUS_get_err_reg(data)                                               ((0x00200000&(data))>>21)
#define K_MCP_STATUS_mc_dec_err_shift                                                (20)
#define K_MCP_STATUS_mc_dec_err_mask                                                 (0x00100000)
#define K_MCP_STATUS_mc_dec_err(data)                                                (0x00100000&((data)<<20))
#define K_MCP_STATUS_mc_dec_err_src(data)                                            ((0x00100000&(data))>>20)
#define K_MCP_STATUS_get_mc_dec_err(data)                                            ((0x00100000&(data))>>20)
#define K_MCP_STATUS_pp_w_err_shift                                                  (19)
#define K_MCP_STATUS_pp_w_err_mask                                                   (0x00080000)
#define K_MCP_STATUS_pp_w_err(data)                                                  (0x00080000&((data)<<19))
#define K_MCP_STATUS_pp_w_err_src(data)                                              ((0x00080000&(data))>>19)
#define K_MCP_STATUS_get_pp_w_err(data)                                              ((0x00080000&(data))>>19)
#define K_MCP_STATUS_pp_r_err_shift                                                  (18)
#define K_MCP_STATUS_pp_r_err_mask                                                   (0x00040000)
#define K_MCP_STATUS_pp_r_err(data)                                                  (0x00040000&((data)<<18))
#define K_MCP_STATUS_pp_r_err_src(data)                                              ((0x00040000&(data))>>18)
#define K_MCP_STATUS_get_pp_r_err(data)                                              ((0x00040000&(data))>>18)
#define K_MCP_STATUS_pp_ov_shift                                                     (17)
#define K_MCP_STATUS_pp_ov_mask                                                      (0x00020000)
#define K_MCP_STATUS_pp_ov(data)                                                     (0x00020000&((data)<<17))
#define K_MCP_STATUS_pp_ov_src(data)                                                 ((0x00020000&(data))>>17)
#define K_MCP_STATUS_get_pp_ov(data)                                                 ((0x00020000&(data))>>17)
#define K_MCP_STATUS_pp_mode_err_shift                                               (16)
#define K_MCP_STATUS_pp_mode_err_mask                                                (0x00010000)
#define K_MCP_STATUS_pp_mode_err(data)                                               (0x00010000&((data)<<16))
#define K_MCP_STATUS_pp_mode_err_src(data)                                           ((0x00010000&(data))>>16)
#define K_MCP_STATUS_get_pp_mode_err(data)                                           ((0x00010000&(data))>>16)
#define K_MCP_STATUS_s_mcp_error_shift                                               (10)
#define K_MCP_STATUS_s_mcp_error_mask                                                (0x00000400)
#define K_MCP_STATUS_s_mcp_error(data)                                               (0x00000400&((data)<<10))
#define K_MCP_STATUS_s_mcp_error_src(data)                                           ((0x00000400&(data))>>10)
#define K_MCP_STATUS_get_s_mcp_error(data)                                           ((0x00000400&(data))>>10)
#define K_MCP_STATUS_s_error_shift                                                   (9)
#define K_MCP_STATUS_s_error_mask                                                    (0x00000200)
#define K_MCP_STATUS_s_error(data)                                                   (0x00000200&((data)<<9))
#define K_MCP_STATUS_s_error_src(data)                                               ((0x00000200&(data))>>9)
#define K_MCP_STATUS_get_s_error(data)                                               ((0x00000200&(data))>>9)
#define K_MCP_STATUS_s_compare_shift                                                 (8)
#define K_MCP_STATUS_s_compare_mask                                                  (0x00000100)
#define K_MCP_STATUS_s_compare(data)                                                 (0x00000100&((data)<<8))
#define K_MCP_STATUS_s_compare_src(data)                                             ((0x00000100&(data))>>8)
#define K_MCP_STATUS_get_s_compare(data)                                             ((0x00000100&(data))>>8)
#define K_MCP_STATUS_s_ring_empty_shift                                              (7)
#define K_MCP_STATUS_s_ring_empty_mask                                               (0x00000080)
#define K_MCP_STATUS_s_ring_empty(data)                                              (0x00000080&((data)<<7))
#define K_MCP_STATUS_s_ring_empty_src(data)                                          ((0x00000080&(data))>>7)
#define K_MCP_STATUS_get_s_ring_empty(data)                                          ((0x00000080&(data))>>7)
#define K_MCP_STATUS_mcp_error_shift                                                 (6)
#define K_MCP_STATUS_mcp_error_mask                                                  (0x00000040)
#define K_MCP_STATUS_mcp_error(data)                                                 (0x00000040&((data)<<6))
#define K_MCP_STATUS_mcp_error_src(data)                                             ((0x00000040&(data))>>6)
#define K_MCP_STATUS_get_mcp_error(data)                                             ((0x00000040&(data))>>6)
#define K_MCP_STATUS_compare_shift                                                   (3)
#define K_MCP_STATUS_compare_mask                                                    (0x00000008)
#define K_MCP_STATUS_compare(data)                                                   (0x00000008&((data)<<3))
#define K_MCP_STATUS_compare_src(data)                                               ((0x00000008&(data))>>3)
#define K_MCP_STATUS_get_compare(data)                                               ((0x00000008&(data))>>3)
#define K_MCP_STATUS_error_shift                                                     (2)
#define K_MCP_STATUS_error_mask                                                      (0x00000004)
#define K_MCP_STATUS_error(data)                                                     (0x00000004&((data)<<2))
#define K_MCP_STATUS_error_src(data)                                                 ((0x00000004&(data))>>2)
#define K_MCP_STATUS_get_error(data)                                                 ((0x00000004&(data))>>2)
#define K_MCP_STATUS_ring_empty_shift                                                (1)
#define K_MCP_STATUS_ring_empty_mask                                                 (0x00000002)
#define K_MCP_STATUS_ring_empty(data)                                                (0x00000002&((data)<<1))
#define K_MCP_STATUS_ring_empty_src(data)                                            ((0x00000002&(data))>>1)
#define K_MCP_STATUS_get_ring_empty(data)                                            ((0x00000002&(data))>>1)
#define K_MCP_STATUS_write_data_shift                                                (0)
#define K_MCP_STATUS_write_data_mask                                                 (0x00000001)
#define K_MCP_STATUS_write_data(data)                                                (0x00000001&((data)<<0))
#define K_MCP_STATUS_write_data_src(data)                                            ((0x00000001&(data))>>0)
#define K_MCP_STATUS_get_write_data(data)                                            ((0x00000001&(data))>>0)


#define K_MCP_EN                                                                     0x18015908
#define K_MCP_EN_reg_addr                                                            "0xB8015908"
#define K_MCP_EN_reg                                                                 0xB8015908
#define set_K_MCP_EN_reg(data)   (*((volatile unsigned int*) K_MCP_EN_reg)=data)
#define get_K_MCP_EN_reg   (*((volatile unsigned int*) K_MCP_EN_reg))
#define K_MCP_EN_inst_adr                                                            "0x0042"
#define K_MCP_EN_inst                                                                0x0042
#define K_MCP_EN_security_region_en_shift                                            (8)
#define K_MCP_EN_security_region_en_mask                                             (0x00000100)
#define K_MCP_EN_security_region_en(data)                                            (0x00000100&((data)<<8))
#define K_MCP_EN_security_region_en_src(data)                                        ((0x00000100&(data))>>8)
#define K_MCP_EN_get_security_region_en(data)                                        ((0x00000100&(data))>>8)
#define K_MCP_EN_cdpu_isr_en_shift                                                   (7)
#define K_MCP_EN_cdpu_isr_en_mask                                                    (0x00000080)
#define K_MCP_EN_cdpu_isr_en(data)                                                   (0x00000080&((data)<<7))
#define K_MCP_EN_cdpu_isr_en_src(data)                                               ((0x00000080&(data))>>7)
#define K_MCP_EN_get_cdpu_isr_en(data)                                               ((0x00000080&(data))>>7)
#define K_MCP_EN_mcp_error_en_shift                                                  (6)
#define K_MCP_EN_mcp_error_en_mask                                                   (0x00000040)
#define K_MCP_EN_mcp_error_en(data)                                                  (0x00000040&((data)<<6))
#define K_MCP_EN_mcp_error_en_src(data)                                              ((0x00000040&(data))>>6)
#define K_MCP_EN_get_mcp_error_en(data)                                              ((0x00000040&(data))>>6)
#define K_MCP_EN_compare_en_shift                                                    (3)
#define K_MCP_EN_compare_en_mask                                                     (0x00000008)
#define K_MCP_EN_compare_en(data)                                                    (0x00000008&((data)<<3))
#define K_MCP_EN_compare_en_src(data)                                                ((0x00000008&(data))>>3)
#define K_MCP_EN_get_compare_en(data)                                                ((0x00000008&(data))>>3)
#define K_MCP_EN_error_en_shift                                                      (2)
#define K_MCP_EN_error_en_mask                                                       (0x00000004)
#define K_MCP_EN_error_en(data)                                                      (0x00000004&((data)<<2))
#define K_MCP_EN_error_en_src(data)                                                  ((0x00000004&(data))>>2)
#define K_MCP_EN_get_error_en(data)                                                  ((0x00000004&(data))>>2)
#define K_MCP_EN_ring_empty_en_shift                                                 (1)
#define K_MCP_EN_ring_empty_en_mask                                                  (0x00000002)
#define K_MCP_EN_ring_empty_en(data)                                                 (0x00000002&((data)<<1))
#define K_MCP_EN_ring_empty_en_src(data)                                             ((0x00000002&(data))>>1)
#define K_MCP_EN_get_ring_empty_en(data)                                             ((0x00000002&(data))>>1)
#define K_MCP_EN_write_data_shift                                                    (0)
#define K_MCP_EN_write_data_mask                                                     (0x00000001)
#define K_MCP_EN_write_data(data)                                                    (0x00000001&((data)<<0))
#define K_MCP_EN_write_data_src(data)                                                ((0x00000001&(data))>>0)
#define K_MCP_EN_get_write_data(data)                                                ((0x00000001&(data))>>0)


#define K_MCP_CTRL1                                                                  0x18015998
#define K_MCP_CTRL1_reg_addr                                                         "0xB8015998"
#define K_MCP_CTRL1_reg                                                              0xB8015998
#define set_K_MCP_CTRL1_reg(data)   (*((volatile unsigned int*) K_MCP_CTRL1_reg)=data)
#define get_K_MCP_CTRL1_reg   (*((volatile unsigned int*) K_MCP_CTRL1_reg))
#define K_MCP_CTRL1_inst_adr                                                         "0x0066"
#define K_MCP_CTRL1_inst                                                             0x0066
#define K_MCP_CTRL1_aesh_pad_off_shift                                               (10)
#define K_MCP_CTRL1_aesh_pad_off_mask                                                (0x00000400)
#define K_MCP_CTRL1_aesh_pad_off(data)                                               (0x00000400&((data)<<10))
#define K_MCP_CTRL1_aesh_pad_off_src(data)                                           ((0x00000400&(data))>>10)
#define K_MCP_CTRL1_get_aesh_pad_off(data)                                           ((0x00000400&(data))>>10)
#define K_MCP_CTRL1_csa_entropy_shift                                                (8)
#define K_MCP_CTRL1_csa_entropy_mask                                                 (0x00000300)
#define K_MCP_CTRL1_csa_entropy(data)                                                (0x00000300&((data)<<8))
#define K_MCP_CTRL1_csa_entropy_src(data)                                            ((0x00000300&(data))>>8)
#define K_MCP_CTRL1_get_csa_entropy(data)                                            ((0x00000300&(data))>>8)
#define K_MCP_CTRL1_mcp_round_no_shift                                               (0)
#define K_MCP_CTRL1_mcp_round_no_mask                                                (0x000000FF)
#define K_MCP_CTRL1_mcp_round_no(data)                                               (0x000000FF&((data)<<0))
#define K_MCP_CTRL1_mcp_round_no_src(data)                                           ((0x000000FF&(data))>>0)
#define K_MCP_CTRL1_get_mcp_round_no(data)                                           ((0x000000FF&(data))>>0)


#define K_MCP_BASE                                                                   0x1801590C
#define K_MCP_BASE_reg_addr                                                          "0xB801590C"
#define K_MCP_BASE_reg                                                               0xB801590C
#define set_K_MCP_BASE_reg(data)   (*((volatile unsigned int*) K_MCP_BASE_reg)=data)
#define get_K_MCP_BASE_reg   (*((volatile unsigned int*) K_MCP_BASE_reg))
#define K_MCP_BASE_inst_adr                                                          "0x0043"
#define K_MCP_BASE_inst                                                              0x0043
#define K_MCP_BASE_base_shift                                                        (0)
#define K_MCP_BASE_base_mask                                                         (0xFFFFFFFF)
#define K_MCP_BASE_base(data)                                                        (0xFFFFFFFF&((data)<<0))
#define K_MCP_BASE_base_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define K_MCP_BASE_get_base(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define K_MCP_LIMIT                                                                  0x18015910
#define K_MCP_LIMIT_reg_addr                                                         "0xB8015910"
#define K_MCP_LIMIT_reg                                                              0xB8015910
#define set_K_MCP_LIMIT_reg(data)   (*((volatile unsigned int*) K_MCP_LIMIT_reg)=data)
#define get_K_MCP_LIMIT_reg   (*((volatile unsigned int*) K_MCP_LIMIT_reg))
#define K_MCP_LIMIT_inst_adr                                                         "0x0044"
#define K_MCP_LIMIT_inst                                                             0x0044
#define K_MCP_LIMIT_limit_shift                                                      (0)
#define K_MCP_LIMIT_limit_mask                                                       (0xFFFFFFFF)
#define K_MCP_LIMIT_limit(data)                                                      (0xFFFFFFFF&((data)<<0))
#define K_MCP_LIMIT_limit_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define K_MCP_LIMIT_get_limit(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define K_MCP_RDPTR                                                                  0x18015914
#define K_MCP_RDPTR_reg_addr                                                         "0xB8015914"
#define K_MCP_RDPTR_reg                                                              0xB8015914
#define set_K_MCP_RDPTR_reg(data)   (*((volatile unsigned int*) K_MCP_RDPTR_reg)=data)
#define get_K_MCP_RDPTR_reg   (*((volatile unsigned int*) K_MCP_RDPTR_reg))
#define K_MCP_RDPTR_inst_adr                                                         "0x0045"
#define K_MCP_RDPTR_inst                                                             0x0045
#define K_MCP_RDPTR_rdptr_shift                                                      (0)
#define K_MCP_RDPTR_rdptr_mask                                                       (0xFFFFFFFF)
#define K_MCP_RDPTR_rdptr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define K_MCP_RDPTR_rdptr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define K_MCP_RDPTR_get_rdptr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define K_MCP_WRPTR                                                                  0x18015918
#define K_MCP_WRPTR_reg_addr                                                         "0xB8015918"
#define K_MCP_WRPTR_reg                                                              0xB8015918
#define set_K_MCP_WRPTR_reg(data)   (*((volatile unsigned int*) K_MCP_WRPTR_reg)=data)
#define get_K_MCP_WRPTR_reg   (*((volatile unsigned int*) K_MCP_WRPTR_reg))
#define K_MCP_WRPTR_inst_adr                                                         "0x0046"
#define K_MCP_WRPTR_inst                                                             0x0046
#define K_MCP_WRPTR_wrptr_shift                                                      (0)
#define K_MCP_WRPTR_wrptr_mask                                                       (0xFFFFFFFF)
#define K_MCP_WRPTR_wrptr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define K_MCP_WRPTR_wrptr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define K_MCP_WRPTR_get_wrptr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define K_MCP_DES_COUNT                                                              0x18015934
#define K_MCP_DES_COUNT_reg_addr                                                     "0xB8015934"
#define K_MCP_DES_COUNT_reg                                                          0xB8015934
#define set_K_MCP_DES_COUNT_reg(data)   (*((volatile unsigned int*) K_MCP_DES_COUNT_reg)=data)
#define get_K_MCP_DES_COUNT_reg   (*((volatile unsigned int*) K_MCP_DES_COUNT_reg))
#define K_MCP_DES_COUNT_inst_adr                                                     "0x004D"
#define K_MCP_DES_COUNT_inst                                                         0x004D
#define K_MCP_DES_COUNT_count_shift                                                  (0)
#define K_MCP_DES_COUNT_count_mask                                                   (0x0000FFFF)
#define K_MCP_DES_COUNT_count(data)                                                  (0x0000FFFF&((data)<<0))
#define K_MCP_DES_COUNT_count_src(data)                                              ((0x0000FFFF&(data))>>0)
#define K_MCP_DES_COUNT_get_count(data)                                              ((0x0000FFFF&(data))>>0)


#define K_MCP_DES_COMPARE                                                            0x18015938
#define K_MCP_DES_COMPARE_reg_addr                                                   "0xB8015938"
#define K_MCP_DES_COMPARE_reg                                                        0xB8015938
#define set_K_MCP_DES_COMPARE_reg(data)   (*((volatile unsigned int*) K_MCP_DES_COMPARE_reg)=data)
#define get_K_MCP_DES_COMPARE_reg   (*((volatile unsigned int*) K_MCP_DES_COMPARE_reg))
#define K_MCP_DES_COMPARE_inst_adr                                                   "0x004E"
#define K_MCP_DES_COMPARE_inst                                                       0x004E
#define K_MCP_DES_COMPARE_compare_shift                                              (0)
#define K_MCP_DES_COMPARE_compare_mask                                               (0x0000FFFF)
#define K_MCP_DES_COMPARE_compare(data)                                              (0x0000FFFF&((data)<<0))
#define K_MCP_DES_COMPARE_compare_src(data)                                          ((0x0000FFFF&(data))>>0)
#define K_MCP_DES_COMPARE_get_compare(data)                                          ((0x0000FFFF&(data))>>0)


#define K_MCP_DES_INI_KEY_0                                                          0x1801591C
#define K_MCP_DES_INI_KEY_1                                                          0x18015920
#define K_MCP_DES_INI_KEY_0_reg_addr                                                 "0xB801591C"
#define K_MCP_DES_INI_KEY_1_reg_addr                                                 "0xB8015920"
#define K_MCP_DES_INI_KEY_0_reg                                                      0xB801591C
#define K_MCP_DES_INI_KEY_1_reg                                                      0xB8015920
#define set_K_MCP_DES_INI_KEY_0_reg(data)   (*((volatile unsigned int*) K_MCP_DES_INI_KEY_0_reg)=data)
#define set_K_MCP_DES_INI_KEY_1_reg(data)   (*((volatile unsigned int*) K_MCP_DES_INI_KEY_1_reg)=data)
#define get_K_MCP_DES_INI_KEY_0_reg   (*((volatile unsigned int*) K_MCP_DES_INI_KEY_0_reg))
#define get_K_MCP_DES_INI_KEY_1_reg   (*((volatile unsigned int*) K_MCP_DES_INI_KEY_1_reg))
#define K_MCP_DES_INI_KEY_0_inst_adr                                                 "0x0047"
#define K_MCP_DES_INI_KEY_1_inst_adr                                                 "0x0048"
#define K_MCP_DES_INI_KEY_0_inst                                                     0x0047
#define K_MCP_DES_INI_KEY_1_inst                                                     0x0048
#define K_MCP_DES_INI_KEY_data_shift                                                 (0)
#define K_MCP_DES_INI_KEY_data_mask                                                  (0xFFFFFFFF)
#define K_MCP_DES_INI_KEY_data(data)                                                 (0xFFFFFFFF&((data)<<0))
#define K_MCP_DES_INI_KEY_data_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define K_MCP_DES_INI_KEY_get_data(data)                                             ((0xFFFFFFFF&(data))>>0)


#define K_MCP_AES_INI_KEY_0                                                          0x18015924
#define K_MCP_AES_INI_KEY_1                                                          0x18015928
#define K_MCP_AES_INI_KEY_2                                                          0x1801592C
#define K_MCP_AES_INI_KEY_3                                                          0x18015930
#define K_MCP_AES_INI_KEY_0_reg_addr                                                 "0xB8015924"
#define K_MCP_AES_INI_KEY_1_reg_addr                                                 "0xB8015928"
#define K_MCP_AES_INI_KEY_2_reg_addr                                                 "0xB801592C"
#define K_MCP_AES_INI_KEY_3_reg_addr                                                 "0xB8015930"
#define K_MCP_AES_INI_KEY_0_reg                                                      0xB8015924
#define K_MCP_AES_INI_KEY_1_reg                                                      0xB8015928
#define K_MCP_AES_INI_KEY_2_reg                                                      0xB801592C
#define K_MCP_AES_INI_KEY_3_reg                                                      0xB8015930
#define set_K_MCP_AES_INI_KEY_0_reg(data)   (*((volatile unsigned int*) K_MCP_AES_INI_KEY_0_reg)=data)
#define set_K_MCP_AES_INI_KEY_1_reg(data)   (*((volatile unsigned int*) K_MCP_AES_INI_KEY_1_reg)=data)
#define set_K_MCP_AES_INI_KEY_2_reg(data)   (*((volatile unsigned int*) K_MCP_AES_INI_KEY_2_reg)=data)
#define set_K_MCP_AES_INI_KEY_3_reg(data)   (*((volatile unsigned int*) K_MCP_AES_INI_KEY_3_reg)=data)
#define get_K_MCP_AES_INI_KEY_0_reg   (*((volatile unsigned int*) K_MCP_AES_INI_KEY_0_reg))
#define get_K_MCP_AES_INI_KEY_1_reg   (*((volatile unsigned int*) K_MCP_AES_INI_KEY_1_reg))
#define get_K_MCP_AES_INI_KEY_2_reg   (*((volatile unsigned int*) K_MCP_AES_INI_KEY_2_reg))
#define get_K_MCP_AES_INI_KEY_3_reg   (*((volatile unsigned int*) K_MCP_AES_INI_KEY_3_reg))
#define K_MCP_AES_INI_KEY_0_inst_adr                                                 "0x0049"
#define K_MCP_AES_INI_KEY_1_inst_adr                                                 "0x004A"
#define K_MCP_AES_INI_KEY_2_inst_adr                                                 "0x004B"
#define K_MCP_AES_INI_KEY_3_inst_adr                                                 "0x004C"
#define K_MCP_AES_INI_KEY_0_inst                                                     0x0049
#define K_MCP_AES_INI_KEY_1_inst                                                     0x004A
#define K_MCP_AES_INI_KEY_2_inst                                                     0x004B
#define K_MCP_AES_INI_KEY_3_inst                                                     0x004C
#define K_MCP_AES_INI_KEY_data_shift                                                 (0)
#define K_MCP_AES_INI_KEY_data_mask                                                  (0xFFFFFFFF)
#define K_MCP_AES_INI_KEY_data(data)                                                 (0xFFFFFFFF&((data)<<0))
#define K_MCP_AES_INI_KEY_data_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define K_MCP_AES_INI_KEY_get_data(data)                                             ((0xFFFFFFFF&(data))>>0)


#define K_MCP_MULTI2_SYS_KEY_0                                                       0x18015978
#define K_MCP_MULTI2_SYS_KEY_1                                                       0x1801597C
#define K_MCP_MULTI2_SYS_KEY_2                                                       0x18015980
#define K_MCP_MULTI2_SYS_KEY_3                                                       0x18015984
#define K_MCP_MULTI2_SYS_KEY_4                                                       0x18015988
#define K_MCP_MULTI2_SYS_KEY_5                                                       0x1801598C
#define K_MCP_MULTI2_SYS_KEY_6                                                       0x18015990
#define K_MCP_MULTI2_SYS_KEY_7                                                       0x18015994
#define K_MCP_MULTI2_SYS_KEY_0_reg_addr                                              "0xB8015978"
#define K_MCP_MULTI2_SYS_KEY_1_reg_addr                                              "0xB801597C"
#define K_MCP_MULTI2_SYS_KEY_2_reg_addr                                              "0xB8015980"
#define K_MCP_MULTI2_SYS_KEY_3_reg_addr                                              "0xB8015984"
#define K_MCP_MULTI2_SYS_KEY_4_reg_addr                                              "0xB8015988"
#define K_MCP_MULTI2_SYS_KEY_5_reg_addr                                              "0xB801598C"
#define K_MCP_MULTI2_SYS_KEY_6_reg_addr                                              "0xB8015990"
#define K_MCP_MULTI2_SYS_KEY_7_reg_addr                                              "0xB8015994"
#define K_MCP_MULTI2_SYS_KEY_0_reg                                                   0xB8015978
#define K_MCP_MULTI2_SYS_KEY_1_reg                                                   0xB801597C
#define K_MCP_MULTI2_SYS_KEY_2_reg                                                   0xB8015980
#define K_MCP_MULTI2_SYS_KEY_3_reg                                                   0xB8015984
#define K_MCP_MULTI2_SYS_KEY_4_reg                                                   0xB8015988
#define K_MCP_MULTI2_SYS_KEY_5_reg                                                   0xB801598C
#define K_MCP_MULTI2_SYS_KEY_6_reg                                                   0xB8015990
#define K_MCP_MULTI2_SYS_KEY_7_reg                                                   0xB8015994
#define set_K_MCP_MULTI2_SYS_KEY_0_reg(data)   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_0_reg)=data)
#define set_K_MCP_MULTI2_SYS_KEY_1_reg(data)   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_1_reg)=data)
#define set_K_MCP_MULTI2_SYS_KEY_2_reg(data)   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_2_reg)=data)
#define set_K_MCP_MULTI2_SYS_KEY_3_reg(data)   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_3_reg)=data)
#define set_K_MCP_MULTI2_SYS_KEY_4_reg(data)   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_4_reg)=data)
#define set_K_MCP_MULTI2_SYS_KEY_5_reg(data)   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_5_reg)=data)
#define set_K_MCP_MULTI2_SYS_KEY_6_reg(data)   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_6_reg)=data)
#define set_K_MCP_MULTI2_SYS_KEY_7_reg(data)   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_7_reg)=data)
#define get_K_MCP_MULTI2_SYS_KEY_0_reg   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_0_reg))
#define get_K_MCP_MULTI2_SYS_KEY_1_reg   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_1_reg))
#define get_K_MCP_MULTI2_SYS_KEY_2_reg   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_2_reg))
#define get_K_MCP_MULTI2_SYS_KEY_3_reg   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_3_reg))
#define get_K_MCP_MULTI2_SYS_KEY_4_reg   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_4_reg))
#define get_K_MCP_MULTI2_SYS_KEY_5_reg   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_5_reg))
#define get_K_MCP_MULTI2_SYS_KEY_6_reg   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_6_reg))
#define get_K_MCP_MULTI2_SYS_KEY_7_reg   (*((volatile unsigned int*) K_MCP_MULTI2_SYS_KEY_7_reg))
#define K_MCP_MULTI2_SYS_KEY_0_inst_adr                                              "0x005E"
#define K_MCP_MULTI2_SYS_KEY_1_inst_adr                                              "0x005F"
#define K_MCP_MULTI2_SYS_KEY_2_inst_adr                                              "0x0060"
#define K_MCP_MULTI2_SYS_KEY_3_inst_adr                                              "0x0061"
#define K_MCP_MULTI2_SYS_KEY_4_inst_adr                                              "0x0062"
#define K_MCP_MULTI2_SYS_KEY_5_inst_adr                                              "0x0063"
#define K_MCP_MULTI2_SYS_KEY_6_inst_adr                                              "0x0064"
#define K_MCP_MULTI2_SYS_KEY_7_inst_adr                                              "0x0065"
#define K_MCP_MULTI2_SYS_KEY_0_inst                                                  0x005E
#define K_MCP_MULTI2_SYS_KEY_1_inst                                                  0x005F
#define K_MCP_MULTI2_SYS_KEY_2_inst                                                  0x0060
#define K_MCP_MULTI2_SYS_KEY_3_inst                                                  0x0061
#define K_MCP_MULTI2_SYS_KEY_4_inst                                                  0x0062
#define K_MCP_MULTI2_SYS_KEY_5_inst                                                  0x0063
#define K_MCP_MULTI2_SYS_KEY_6_inst                                                  0x0064
#define K_MCP_MULTI2_SYS_KEY_7_inst                                                  0x0065
#define K_MCP_MULTI2_SYS_KEY_data_shift                                              (0)
#define K_MCP_MULTI2_SYS_KEY_data_mask                                               (0xFFFFFFFF)
#define K_MCP_MULTI2_SYS_KEY_data(data)                                              (0xFFFFFFFF&((data)<<0))
#define K_MCP_MULTI2_SYS_KEY_data_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define K_MCP_MULTI2_SYS_KEY_get_data(data)                                          ((0xFFFFFFFF&(data))>>0)


#define K_MCP_M2M_DES_KAM                                                            0x1801599c
#define K_MCP_M2M_DES_KAM_reg_addr                                                   "0xB801599C"
#define K_MCP_M2M_DES_KAM_reg                                                        0xB801599C
#define set_K_MCP_M2M_DES_KAM_reg(data)   (*((volatile unsigned int*) K_MCP_M2M_DES_KAM_reg)=data)
#define get_K_MCP_M2M_DES_KAM_reg   (*((volatile unsigned int*) K_MCP_M2M_DES_KAM_reg))
#define K_MCP_M2M_DES_KAM_inst_adr                                                   "0x0067"
#define K_MCP_M2M_DES_KAM_inst                                                       0x0067
#define K_MCP_M2M_DES_KAM_enable_shift                                               (3)
#define K_MCP_M2M_DES_KAM_enable_mask                                                (0x00000008)
#define K_MCP_M2M_DES_KAM_enable(data)                                               (0x00000008&((data)<<3))
#define K_MCP_M2M_DES_KAM_enable_src(data)                                           ((0x00000008&(data))>>3)
#define K_MCP_M2M_DES_KAM_get_enable(data)                                           ((0x00000008&(data))>>3)
#define K_MCP_M2M_DES_KAM_kam_shift                                                  (0)
#define K_MCP_M2M_DES_KAM_kam_mask                                                   (0x00000007)
#define K_MCP_M2M_DES_KAM_kam(data)                                                  (0x00000007&((data)<<0))
#define K_MCP_M2M_DES_KAM_kam_src(data)                                              ((0x00000007&(data))>>0)
#define K_MCP_M2M_DES_KAM_get_kam(data)                                              ((0x00000007&(data))>>0)


#define MCP_ST                                                                       0x180151a0
#define MCP_ST_reg_addr                                                              "0xB80151A0"
#define MCP_ST_reg                                                                   0xB80151A0
#define set_MCP_ST_reg(data)   (*((volatile unsigned int*) MCP_ST_reg)=data)
#define get_MCP_ST_reg   (*((volatile unsigned int*) MCP_ST_reg))
#define MCP_ST_inst_adr                                                              "0x0068"
#define MCP_ST_inst                                                                  0x0068
#define MCP_ST_rd_sm_shift                                                           (24)
#define MCP_ST_rd_sm_mask                                                            (0x0F000000)
#define MCP_ST_rd_sm(data)                                                           (0x0F000000&((data)<<24))
#define MCP_ST_rd_sm_src(data)                                                       ((0x0F000000&(data))>>24)
#define MCP_ST_get_rd_sm(data)                                                       ((0x0F000000&(data))>>24)
#define MCP_ST_wr_sm_shift                                                           (21)
#define MCP_ST_wr_sm_mask                                                            (0x00E00000)
#define MCP_ST_wr_sm(data)                                                           (0x00E00000&((data)<<21))
#define MCP_ST_wr_sm_src(data)                                                       ((0x00E00000&(data))>>21)
#define MCP_ST_get_wr_sm(data)                                                       ((0x00E00000&(data))>>21)
#define MCP_ST_mcp_aes_like_sm_shift                                                 (0)
#define MCP_ST_mcp_aes_like_sm_mask                                                  (0x000007FF)
#define MCP_ST_mcp_aes_like_sm(data)                                                 (0x000007FF&((data)<<0))
#define MCP_ST_mcp_aes_like_sm_src(data)                                             ((0x000007FF&(data))>>0)
#define MCP_ST_get_mcp_aes_like_sm(data)                                             ((0x000007FF&(data))>>0)


#define MCP_ST1                                                                      0x180151a4
#define MCP_ST1_reg_addr                                                             "0xB80151A4"
#define MCP_ST1_reg                                                                  0xB80151A4
#define set_MCP_ST1_reg(data)   (*((volatile unsigned int*) MCP_ST1_reg)=data)
#define get_MCP_ST1_reg   (*((volatile unsigned int*) MCP_ST1_reg))
#define MCP_ST1_inst_adr                                                             "0x0069"
#define MCP_ST1_inst                                                                 0x0069
#define MCP_ST1_mcp_top_sm_shift                                                     (0)
#define MCP_ST1_mcp_top_sm_mask                                                      (0x000FFFFF)
#define MCP_ST1_mcp_top_sm(data)                                                     (0x000FFFFF&((data)<<0))
#define MCP_ST1_mcp_top_sm_src(data)                                                 ((0x000FFFFF&(data))>>0)
#define MCP_ST1_get_mcp_top_sm(data)                                                 ((0x000FFFFF&(data))>>0)


#define MC_MAP1                                                                      0x180151a8
#define MC_MAP1_reg_addr                                                             "0xB80151A8"
#define MC_MAP1_reg                                                                  0xB80151A8
#define set_MC_MAP1_reg(data)   (*((volatile unsigned int*) MC_MAP1_reg)=data)
#define get_MC_MAP1_reg   (*((volatile unsigned int*) MC_MAP1_reg))
#define MC_MAP1_inst_adr                                                             "0x006A"
#define MC_MAP1_inst                                                                 0x006A
#define MC_MAP1_adr3_shift                                                           (16)
#define MC_MAP1_adr3_mask                                                            (0x03FF0000)
#define MC_MAP1_adr3(data)                                                           (0x03FF0000&((data)<<16))
#define MC_MAP1_adr3_src(data)                                                       ((0x03FF0000&(data))>>16)
#define MC_MAP1_get_adr3(data)                                                       ((0x03FF0000&(data))>>16)
#define MC_MAP1_adr2_shift                                                           (0)
#define MC_MAP1_adr2_mask                                                            (0x000003FF)
#define MC_MAP1_adr2(data)                                                           (0x000003FF&((data)<<0))
#define MC_MAP1_adr2_src(data)                                                       ((0x000003FF&(data))>>0)
#define MC_MAP1_get_adr2(data)                                                       ((0x000003FF&(data))>>0)


#define MC_MAP2                                                                      0x180151ac
#define MC_MAP2_reg_addr                                                             "0xB80151AC"
#define MC_MAP2_reg                                                                  0xB80151AC
#define set_MC_MAP2_reg(data)   (*((volatile unsigned int*) MC_MAP2_reg)=data)
#define get_MC_MAP2_reg   (*((volatile unsigned int*) MC_MAP2_reg))
#define MC_MAP2_inst_adr                                                             "0x006B"
#define MC_MAP2_inst                                                                 0x006B
#define MC_MAP2_adr1_shift                                                           (16)
#define MC_MAP2_adr1_mask                                                            (0x03FF0000)
#define MC_MAP2_adr1(data)                                                           (0x03FF0000&((data)<<16))
#define MC_MAP2_adr1_src(data)                                                       ((0x03FF0000&(data))>>16)
#define MC_MAP2_get_adr1(data)                                                       ((0x03FF0000&(data))>>16)
#define MC_MAP2_adr0_shift                                                           (0)
#define MC_MAP2_adr0_mask                                                            (0x000003FF)
#define MC_MAP2_adr0(data)                                                           (0x000003FF&((data)<<0))
#define MC_MAP2_adr0_src(data)                                                       ((0x000003FF&(data))>>0)
#define MC_MAP2_get_adr0(data)                                                       ((0x000003FF&(data))>>0)


#define MC_INFO1                                                                     0x180151b0
#define MC_INFO1_reg_addr                                                            "0xB80151B0"
#define MC_INFO1_reg                                                                 0xB80151B0
#define set_MC_INFO1_reg(data)   (*((volatile unsigned int*) MC_INFO1_reg)=data)
#define get_MC_INFO1_reg   (*((volatile unsigned int*) MC_INFO1_reg))
#define MC_INFO1_inst_adr                                                            "0x006C"
#define MC_INFO1_inst                                                                0x006C
#define MC_INFO1_pc_shift                                                            (0)
#define MC_INFO1_pc_mask                                                             (0x000003FF)
#define MC_INFO1_pc(data)                                                            (0x000003FF&((data)<<0))
#define MC_INFO1_pc_src(data)                                                        ((0x000003FF&(data))>>0)
#define MC_INFO1_get_pc(data)                                                        ((0x000003FF&(data))>>0)


#define MC_INFO2                                                                     0x180151b4
#define MC_INFO2_reg_addr                                                            "0xB80151B4"
#define MC_INFO2_reg                                                                 0xB80151B4
#define set_MC_INFO2_reg(data)   (*((volatile unsigned int*) MC_INFO2_reg)=data)
#define get_MC_INFO2_reg   (*((volatile unsigned int*) MC_INFO2_reg))
#define MC_INFO2_inst_adr                                                            "0x006D"
#define MC_INFO2_inst                                                                0x006D
#define MC_INFO2_word1_shift                                                         (0)
#define MC_INFO2_word1_mask                                                          (0xFFFFFFFF)
#define MC_INFO2_word1(data)                                                         (0xFFFFFFFF&((data)<<0))
#define MC_INFO2_word1_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define MC_INFO2_get_word1(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define MC_INFO3                                                                     0x180151b8
#define MC_INFO3_reg_addr                                                            "0xB80151B8"
#define MC_INFO3_reg                                                                 0xB80151B8
#define set_MC_INFO3_reg(data)   (*((volatile unsigned int*) MC_INFO3_reg)=data)
#define get_MC_INFO3_reg   (*((volatile unsigned int*) MC_INFO3_reg))
#define MC_INFO3_inst_adr                                                            "0x006E"
#define MC_INFO3_inst                                                                0x006E
#define MC_INFO3_word2_shift                                                         (0)
#define MC_INFO3_word2_mask                                                          (0xFFFFFFFF)
#define MC_INFO3_word2(data)                                                         (0xFFFFFFFF&((data)<<0))
#define MC_INFO3_word2_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define MC_INFO3_get_word2(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define MC_INFO4                                                                     0x180151bc
#define MC_INFO4_reg_addr                                                            "0xB80151BC"
#define MC_INFO4_reg                                                                 0xB80151BC
#define set_MC_INFO4_reg(data)   (*((volatile unsigned int*) MC_INFO4_reg)=data)
#define get_MC_INFO4_reg   (*((volatile unsigned int*) MC_INFO4_reg))
#define MC_INFO4_inst_adr                                                            "0x006F"
#define MC_INFO4_inst                                                                0x006F
#define MC_INFO4_word3_shift                                                         (0)
#define MC_INFO4_word3_mask                                                          (0xFFFFFFFF)
#define MC_INFO4_word3(data)                                                         (0xFFFFFFFF&((data)<<0))
#define MC_INFO4_word3_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define MC_INFO4_get_word3(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define MC_CTR                                                                       0x180151c0
#define MC_CTR_reg_addr                                                              "0xB80151C0"
#define MC_CTR_reg                                                                   0xB80151C0
#define set_MC_CTR_reg(data)   (*((volatile unsigned int*) MC_CTR_reg)=data)
#define get_MC_CTR_reg   (*((volatile unsigned int*) MC_CTR_reg))
#define MC_CTR_inst_adr                                                              "0x0070"
#define MC_CTR_inst                                                                  0x0070
#define MC_CTR_tmout_ctr_shift                                                       (0)
#define MC_CTR_tmout_ctr_mask                                                        (0x0000FFFF)
#define MC_CTR_tmout_ctr(data)                                                       (0x0000FFFF&((data)<<0))
#define MC_CTR_tmout_ctr_src(data)                                                   ((0x0000FFFF&(data))>>0)
#define MC_CTR_get_tmout_ctr(data)                                                   ((0x0000FFFF&(data))>>0)


#define MBIST_1                                                                      0x180151d0
#define MBIST_1_reg_addr                                                             "0xB80151D0"
#define MBIST_1_reg                                                                  0xB80151D0
#define set_MBIST_1_reg(data)   (*((volatile unsigned int*) MBIST_1_reg)=data)
#define get_MBIST_1_reg   (*((volatile unsigned int*) MBIST_1_reg))
#define MBIST_1_inst_adr                                                             "0x0074"
#define MBIST_1_inst                                                                 0x0074
#define MBIST_1_rm_shift                                                             (4)
#define MBIST_1_rm_mask                                                              (0x000000F0)
#define MBIST_1_rm(data)                                                             (0x000000F0&((data)<<4))
#define MBIST_1_rm_src(data)                                                         ((0x000000F0&(data))>>4)
#define MBIST_1_get_rm(data)                                                         ((0x000000F0&(data))>>4)
#define MBIST_1_rme_shift                                                            (3)
#define MBIST_1_rme_mask                                                             (0x00000008)
#define MBIST_1_rme(data)                                                            (0x00000008&((data)<<3))
#define MBIST_1_rme_src(data)                                                        ((0x00000008&(data))>>3)
#define MBIST_1_get_rme(data)                                                        ((0x00000008&(data))>>3)
#define MBIST_1_drf_test_resume_shift                                                (2)
#define MBIST_1_drf_test_resume_mask                                                 (0x00000004)
#define MBIST_1_drf_test_resume(data)                                                (0x00000004&((data)<<2))
#define MBIST_1_drf_test_resume_src(data)                                            ((0x00000004&(data))>>2)
#define MBIST_1_get_drf_test_resume(data)                                            ((0x00000004&(data))>>2)
#define MBIST_1_drf_bist_mode_shift                                                  (1)
#define MBIST_1_drf_bist_mode_mask                                                   (0x00000002)
#define MBIST_1_drf_bist_mode(data)                                                  (0x00000002&((data)<<1))
#define MBIST_1_drf_bist_mode_src(data)                                              ((0x00000002&(data))>>1)
#define MBIST_1_get_drf_bist_mode(data)                                              ((0x00000002&(data))>>1)
#define MBIST_1_bist_mode_shift                                                      (0)
#define MBIST_1_bist_mode_mask                                                       (0x00000001)
#define MBIST_1_bist_mode(data)                                                      (0x00000001&((data)<<0))
#define MBIST_1_bist_mode_src(data)                                                  ((0x00000001&(data))>>0)
#define MBIST_1_get_bist_mode(data)                                                  ((0x00000001&(data))>>0)


#define MBIST_2                                                                      0x180151d4
#define MBIST_2_reg_addr                                                             "0xB80151D4"
#define MBIST_2_reg                                                                  0xB80151D4
#define set_MBIST_2_reg(data)   (*((volatile unsigned int*) MBIST_2_reg)=data)
#define get_MBIST_2_reg   (*((volatile unsigned int*) MBIST_2_reg))
#define MBIST_2_inst_adr                                                             "0x0075"
#define MBIST_2_inst                                                                 0x0075
#define MBIST_2_drf_bist_fail_5_shift                                                (14)
#define MBIST_2_drf_bist_fail_5_mask                                                 (0x00004000)
#define MBIST_2_drf_bist_fail_5(data)                                                (0x00004000&((data)<<14))
#define MBIST_2_drf_bist_fail_5_src(data)                                            ((0x00004000&(data))>>14)
#define MBIST_2_get_drf_bist_fail_5(data)                                            ((0x00004000&(data))>>14)
#define MBIST_2_bist_fail_5_shift                                                    (13)
#define MBIST_2_bist_fail_5_mask                                                     (0x00002000)
#define MBIST_2_bist_fail_5(data)                                                    (0x00002000&((data)<<13))
#define MBIST_2_bist_fail_5_src(data)                                                ((0x00002000&(data))>>13)
#define MBIST_2_get_bist_fail_5(data)                                                ((0x00002000&(data))>>13)
#define MBIST_2_drf_bist_fail_4_shift                                                (12)
#define MBIST_2_drf_bist_fail_4_mask                                                 (0x00001000)
#define MBIST_2_drf_bist_fail_4(data)                                                (0x00001000&((data)<<12))
#define MBIST_2_drf_bist_fail_4_src(data)                                            ((0x00001000&(data))>>12)
#define MBIST_2_get_drf_bist_fail_4(data)                                            ((0x00001000&(data))>>12)
#define MBIST_2_bist_fail_4_shift                                                    (11)
#define MBIST_2_bist_fail_4_mask                                                     (0x00000800)
#define MBIST_2_bist_fail_4(data)                                                    (0x00000800&((data)<<11))
#define MBIST_2_bist_fail_4_src(data)                                                ((0x00000800&(data))>>11)
#define MBIST_2_get_bist_fail_4(data)                                                ((0x00000800&(data))>>11)
#define MBIST_2_drf_bist_fail_3_shift                                                (10)
#define MBIST_2_drf_bist_fail_3_mask                                                 (0x00000400)
#define MBIST_2_drf_bist_fail_3(data)                                                (0x00000400&((data)<<10))
#define MBIST_2_drf_bist_fail_3_src(data)                                            ((0x00000400&(data))>>10)
#define MBIST_2_get_drf_bist_fail_3(data)                                            ((0x00000400&(data))>>10)
#define MBIST_2_bist_fail_3_shift                                                    (9)
#define MBIST_2_bist_fail_3_mask                                                     (0x00000200)
#define MBIST_2_bist_fail_3(data)                                                    (0x00000200&((data)<<9))
#define MBIST_2_bist_fail_3_src(data)                                                ((0x00000200&(data))>>9)
#define MBIST_2_get_bist_fail_3(data)                                                ((0x00000200&(data))>>9)
#define MBIST_2_drf_bist_fail_2_shift                                                (8)
#define MBIST_2_drf_bist_fail_2_mask                                                 (0x00000100)
#define MBIST_2_drf_bist_fail_2(data)                                                (0x00000100&((data)<<8))
#define MBIST_2_drf_bist_fail_2_src(data)                                            ((0x00000100&(data))>>8)
#define MBIST_2_get_drf_bist_fail_2(data)                                            ((0x00000100&(data))>>8)
#define MBIST_2_bist_fail_2_shift                                                    (7)
#define MBIST_2_bist_fail_2_mask                                                     (0x00000080)
#define MBIST_2_bist_fail_2(data)                                                    (0x00000080&((data)<<7))
#define MBIST_2_bist_fail_2_src(data)                                                ((0x00000080&(data))>>7)
#define MBIST_2_get_bist_fail_2(data)                                                ((0x00000080&(data))>>7)
#define MBIST_2_drf_bist_fail_1_shift                                                (6)
#define MBIST_2_drf_bist_fail_1_mask                                                 (0x00000040)
#define MBIST_2_drf_bist_fail_1(data)                                                (0x00000040&((data)<<6))
#define MBIST_2_drf_bist_fail_1_src(data)                                            ((0x00000040&(data))>>6)
#define MBIST_2_get_drf_bist_fail_1(data)                                            ((0x00000040&(data))>>6)
#define MBIST_2_bist_fail_1_shift                                                    (5)
#define MBIST_2_bist_fail_1_mask                                                     (0x00000020)
#define MBIST_2_bist_fail_1(data)                                                    (0x00000020&((data)<<5))
#define MBIST_2_bist_fail_1_src(data)                                                ((0x00000020&(data))>>5)
#define MBIST_2_get_bist_fail_1(data)                                                ((0x00000020&(data))>>5)
#define MBIST_2_drf_bist_fail_0_shift                                                (4)
#define MBIST_2_drf_bist_fail_0_mask                                                 (0x00000010)
#define MBIST_2_drf_bist_fail_0(data)                                                (0x00000010&((data)<<4))
#define MBIST_2_drf_bist_fail_0_src(data)                                            ((0x00000010&(data))>>4)
#define MBIST_2_get_drf_bist_fail_0(data)                                            ((0x00000010&(data))>>4)
#define MBIST_2_bist_fail_0_shift                                                    (3)
#define MBIST_2_bist_fail_0_mask                                                     (0x00000008)
#define MBIST_2_bist_fail_0(data)                                                    (0x00000008&((data)<<3))
#define MBIST_2_bist_fail_0_src(data)                                                ((0x00000008&(data))>>3)
#define MBIST_2_get_bist_fail_0(data)                                                ((0x00000008&(data))>>3)
#define MBIST_2_drf_start_pause_shift                                                (2)
#define MBIST_2_drf_start_pause_mask                                                 (0x00000004)
#define MBIST_2_drf_start_pause(data)                                                (0x00000004&((data)<<2))
#define MBIST_2_drf_start_pause_src(data)                                            ((0x00000004&(data))>>2)
#define MBIST_2_get_drf_start_pause(data)                                            ((0x00000004&(data))>>2)
#define MBIST_2_drf_bist_done_shift                                                  (1)
#define MBIST_2_drf_bist_done_mask                                                   (0x00000002)
#define MBIST_2_drf_bist_done(data)                                                  (0x00000002&((data)<<1))
#define MBIST_2_drf_bist_done_src(data)                                              ((0x00000002&(data))>>1)
#define MBIST_2_get_drf_bist_done(data)                                              ((0x00000002&(data))>>1)
#define MBIST_2_bist_done_shift                                                      (0)
#define MBIST_2_bist_done_mask                                                       (0x00000001)
#define MBIST_2_bist_done(data)                                                      (0x00000001&((data)<<0))
#define MBIST_2_bist_done_src(data)                                                  ((0x00000001&(data))>>0)
#define MBIST_2_get_bist_done(data)                                                  ((0x00000001&(data))>>0)


#define PWM_CTRL                                                                     0x180151e0
#define PWM_CTRL_reg_addr                                                            "0xB80151E0"
#define PWM_CTRL_reg                                                                 0xB80151E0
#define set_PWM_CTRL_reg(data)   (*((volatile unsigned int*) PWM_CTRL_reg)=data)
#define get_PWM_CTRL_reg   (*((volatile unsigned int*) PWM_CTRL_reg))
#define PWM_CTRL_inst_adr                                                            "0x0078"
#define PWM_CTRL_inst                                                                0x0078
#define PWM_CTRL_en_cp_shift                                                         (22)
#define PWM_CTRL_en_cp_mask                                                          (0x00400000)
#define PWM_CTRL_en_cp(data)                                                         (0x00400000&((data)<<22))
#define PWM_CTRL_en_cp_src(data)                                                     ((0x00400000&(data))>>22)
#define PWM_CTRL_get_en_cp(data)                                                     ((0x00400000&(data))>>22)
#define PWM_CTRL_en_mcp_shift                                                        (21)
#define PWM_CTRL_en_mcp_mask                                                         (0x00200000)
#define PWM_CTRL_en_mcp(data)                                                        (0x00200000&((data)<<21))
#define PWM_CTRL_en_mcp_src(data)                                                    ((0x00200000&(data))>>21)
#define PWM_CTRL_get_en_mcp(data)                                                    ((0x00200000&(data))>>21)
#define PWM_CTRL_en_cdpu_shift                                                       (20)
#define PWM_CTRL_en_cdpu_mask                                                        (0x00100000)
#define PWM_CTRL_en_cdpu(data)                                                       (0x00100000&((data)<<20))
#define PWM_CTRL_en_cdpu_src(data)                                                   ((0x00100000&(data))>>20)
#define PWM_CTRL_get_en_cdpu(data)                                                   ((0x00100000&(data))>>20)
#define PWM_CTRL_sram_ctr_shift                                                      (10)
#define PWM_CTRL_sram_ctr_mask                                                       (0x00007C00)
#define PWM_CTRL_sram_ctr(data)                                                      (0x00007C00&((data)<<10))
#define PWM_CTRL_sram_ctr_src(data)                                                  ((0x00007C00&(data))>>10)
#define PWM_CTRL_get_sram_ctr(data)                                                  ((0x00007C00&(data))>>10)
#define PWM_CTRL_idle_ctr_shift                                                      (0)
#define PWM_CTRL_idle_ctr_mask                                                       (0x000003FF)
#define PWM_CTRL_idle_ctr(data)                                                      (0x000003FF&((data)<<0))
#define PWM_CTRL_idle_ctr_src(data)                                                  ((0x000003FF&(data))>>0)
#define PWM_CTRL_get_idle_ctr(data)                                                  ((0x000003FF&(data))>>0)


#define RCIC_CTRL                                                                    0x180159a0
#define RCIC_CTRL_reg_addr                                                           "0xB80159A0"
#define RCIC_CTRL_reg                                                                0xB80159A0
#define set_RCIC_CTRL_reg(data)   (*((volatile unsigned int*) RCIC_CTRL_reg)=data)
#define get_RCIC_CTRL_reg   (*((volatile unsigned int*) RCIC_CTRL_reg))
#define RCIC_CTRL_inst_adr                                                           "0x0068"
#define RCIC_CTRL_inst                                                               0x0068
#define RCIC_CTRL_write_en3_shift                                                    (10)
#define RCIC_CTRL_write_en3_mask                                                     (0x00000400)
#define RCIC_CTRL_write_en3(data)                                                    (0x00000400&((data)<<10))
#define RCIC_CTRL_write_en3_src(data)                                                ((0x00000400&(data))>>10)
#define RCIC_CTRL_get_write_en3(data)                                                ((0x00000400&(data))>>10)
#define RCIC_CTRL_stop_shift                                                         (9)
#define RCIC_CTRL_stop_mask                                                          (0x00000200)
#define RCIC_CTRL_stop(data)                                                         (0x00000200&((data)<<9))
#define RCIC_CTRL_stop_src(data)                                                     ((0x00000200&(data))>>9)
#define RCIC_CTRL_get_stop(data)                                                     ((0x00000200&(data))>>9)
#define RCIC_CTRL_write_en2_shift                                                    (8)
#define RCIC_CTRL_write_en2_mask                                                     (0x00000100)
#define RCIC_CTRL_write_en2(data)                                                    (0x00000100&((data)<<8))
#define RCIC_CTRL_write_en2_src(data)                                                ((0x00000100&(data))>>8)
#define RCIC_CTRL_get_write_en2(data)                                                ((0x00000100&(data))>>8)
#define RCIC_CTRL_test_mode_shift                                                    (6)
#define RCIC_CTRL_test_mode_mask                                                     (0x000000C0)
#define RCIC_CTRL_test_mode(data)                                                    (0x000000C0&((data)<<6))
#define RCIC_CTRL_test_mode_src(data)                                                ((0x000000C0&(data))>>6)
#define RCIC_CTRL_get_test_mode(data)                                                ((0x000000C0&(data))>>6)
#define RCIC_CTRL_write_en1_shift                                                    (5)
#define RCIC_CTRL_write_en1_mask                                                     (0x00000020)
#define RCIC_CTRL_write_en1(data)                                                    (0x00000020&((data)<<5))
#define RCIC_CTRL_write_en1_src(data)                                                ((0x00000020&(data))>>5)
#define RCIC_CTRL_get_write_en1(data)                                                ((0x00000020&(data))>>5)
#define RCIC_CTRL_wait_sec_shift                                                     (0)
#define RCIC_CTRL_wait_sec_mask                                                      (0x0000001F)
#define RCIC_CTRL_wait_sec(data)                                                     (0x0000001F&((data)<<0))
#define RCIC_CTRL_wait_sec_src(data)                                                 ((0x0000001F&(data))>>0)
#define RCIC_CTRL_get_wait_sec(data)                                                 ((0x0000001F&(data))>>0)


#define RCIC_ENTR_VLD                                                                0x180159a4
#define RCIC_ENTR_VLD_reg_addr                                                       "0xB80159A4"
#define RCIC_ENTR_VLD_reg                                                            0xB80159A4
#define set_RCIC_ENTR_VLD_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_VLD_reg)=data)
#define get_RCIC_ENTR_VLD_reg   (*((volatile unsigned int*) RCIC_ENTR_VLD_reg))
#define RCIC_ENTR_VLD_inst_adr                                                       "0x0069"
#define RCIC_ENTR_VLD_inst                                                           0x0069
#define RCIC_ENTR_VLD_write_en7_shift                                                (15)
#define RCIC_ENTR_VLD_write_en7_mask                                                 (0x00008000)
#define RCIC_ENTR_VLD_write_en7(data)                                                (0x00008000&((data)<<15))
#define RCIC_ENTR_VLD_write_en7_src(data)                                            ((0x00008000&(data))>>15)
#define RCIC_ENTR_VLD_get_write_en7(data)                                            ((0x00008000&(data))>>15)
#define RCIC_ENTR_VLD_valid_7_shift                                                  (14)
#define RCIC_ENTR_VLD_valid_7_mask                                                   (0x00004000)
#define RCIC_ENTR_VLD_valid_7(data)                                                  (0x00004000&((data)<<14))
#define RCIC_ENTR_VLD_valid_7_src(data)                                              ((0x00004000&(data))>>14)
#define RCIC_ENTR_VLD_get_valid_7(data)                                              ((0x00004000&(data))>>14)
#define RCIC_ENTR_VLD_write_en6_shift                                                (13)
#define RCIC_ENTR_VLD_write_en6_mask                                                 (0x00002000)
#define RCIC_ENTR_VLD_write_en6(data)                                                (0x00002000&((data)<<13))
#define RCIC_ENTR_VLD_write_en6_src(data)                                            ((0x00002000&(data))>>13)
#define RCIC_ENTR_VLD_get_write_en6(data)                                            ((0x00002000&(data))>>13)
#define RCIC_ENTR_VLD_valid_6_shift                                                  (12)
#define RCIC_ENTR_VLD_valid_6_mask                                                   (0x00001000)
#define RCIC_ENTR_VLD_valid_6(data)                                                  (0x00001000&((data)<<12))
#define RCIC_ENTR_VLD_valid_6_src(data)                                              ((0x00001000&(data))>>12)
#define RCIC_ENTR_VLD_get_valid_6(data)                                              ((0x00001000&(data))>>12)
#define RCIC_ENTR_VLD_write_en5_shift                                                (11)
#define RCIC_ENTR_VLD_write_en5_mask                                                 (0x00000800)
#define RCIC_ENTR_VLD_write_en5(data)                                                (0x00000800&((data)<<11))
#define RCIC_ENTR_VLD_write_en5_src(data)                                            ((0x00000800&(data))>>11)
#define RCIC_ENTR_VLD_get_write_en5(data)                                            ((0x00000800&(data))>>11)
#define RCIC_ENTR_VLD_valid_5_shift                                                  (10)
#define RCIC_ENTR_VLD_valid_5_mask                                                   (0x00000400)
#define RCIC_ENTR_VLD_valid_5(data)                                                  (0x00000400&((data)<<10))
#define RCIC_ENTR_VLD_valid_5_src(data)                                              ((0x00000400&(data))>>10)
#define RCIC_ENTR_VLD_get_valid_5(data)                                              ((0x00000400&(data))>>10)
#define RCIC_ENTR_VLD_write_en4_shift                                                (9)
#define RCIC_ENTR_VLD_write_en4_mask                                                 (0x00000200)
#define RCIC_ENTR_VLD_write_en4(data)                                                (0x00000200&((data)<<9))
#define RCIC_ENTR_VLD_write_en4_src(data)                                            ((0x00000200&(data))>>9)
#define RCIC_ENTR_VLD_get_write_en4(data)                                            ((0x00000200&(data))>>9)
#define RCIC_ENTR_VLD_valid_4_shift                                                  (8)
#define RCIC_ENTR_VLD_valid_4_mask                                                   (0x00000100)
#define RCIC_ENTR_VLD_valid_4(data)                                                  (0x00000100&((data)<<8))
#define RCIC_ENTR_VLD_valid_4_src(data)                                              ((0x00000100&(data))>>8)
#define RCIC_ENTR_VLD_get_valid_4(data)                                              ((0x00000100&(data))>>8)
#define RCIC_ENTR_VLD_write_en3_shift                                                (7)
#define RCIC_ENTR_VLD_write_en3_mask                                                 (0x00000080)
#define RCIC_ENTR_VLD_write_en3(data)                                                (0x00000080&((data)<<7))
#define RCIC_ENTR_VLD_write_en3_src(data)                                            ((0x00000080&(data))>>7)
#define RCIC_ENTR_VLD_get_write_en3(data)                                            ((0x00000080&(data))>>7)
#define RCIC_ENTR_VLD_valid_3_shift                                                  (6)
#define RCIC_ENTR_VLD_valid_3_mask                                                   (0x00000040)
#define RCIC_ENTR_VLD_valid_3(data)                                                  (0x00000040&((data)<<6))
#define RCIC_ENTR_VLD_valid_3_src(data)                                              ((0x00000040&(data))>>6)
#define RCIC_ENTR_VLD_get_valid_3(data)                                              ((0x00000040&(data))>>6)
#define RCIC_ENTR_VLD_write_en2_shift                                                (5)
#define RCIC_ENTR_VLD_write_en2_mask                                                 (0x00000020)
#define RCIC_ENTR_VLD_write_en2(data)                                                (0x00000020&((data)<<5))
#define RCIC_ENTR_VLD_write_en2_src(data)                                            ((0x00000020&(data))>>5)
#define RCIC_ENTR_VLD_get_write_en2(data)                                            ((0x00000020&(data))>>5)
#define RCIC_ENTR_VLD_valid_2_shift                                                  (4)
#define RCIC_ENTR_VLD_valid_2_mask                                                   (0x00000010)
#define RCIC_ENTR_VLD_valid_2(data)                                                  (0x00000010&((data)<<4))
#define RCIC_ENTR_VLD_valid_2_src(data)                                              ((0x00000010&(data))>>4)
#define RCIC_ENTR_VLD_get_valid_2(data)                                              ((0x00000010&(data))>>4)
#define RCIC_ENTR_VLD_write_en1_shift                                                (3)
#define RCIC_ENTR_VLD_write_en1_mask                                                 (0x00000008)
#define RCIC_ENTR_VLD_write_en1(data)                                                (0x00000008&((data)<<3))
#define RCIC_ENTR_VLD_write_en1_src(data)                                            ((0x00000008&(data))>>3)
#define RCIC_ENTR_VLD_get_write_en1(data)                                            ((0x00000008&(data))>>3)
#define RCIC_ENTR_VLD_valid_1_shift                                                  (2)
#define RCIC_ENTR_VLD_valid_1_mask                                                   (0x00000004)
#define RCIC_ENTR_VLD_valid_1(data)                                                  (0x00000004&((data)<<2))
#define RCIC_ENTR_VLD_valid_1_src(data)                                              ((0x00000004&(data))>>2)
#define RCIC_ENTR_VLD_get_valid_1(data)                                              ((0x00000004&(data))>>2)
#define RCIC_ENTR_VLD_write_en0_shift                                                (1)
#define RCIC_ENTR_VLD_write_en0_mask                                                 (0x00000002)
#define RCIC_ENTR_VLD_write_en0(data)                                                (0x00000002&((data)<<1))
#define RCIC_ENTR_VLD_write_en0_src(data)                                            ((0x00000002&(data))>>1)
#define RCIC_ENTR_VLD_get_write_en0(data)                                            ((0x00000002&(data))>>1)
#define RCIC_ENTR_VLD_valid_0_shift                                                  (0)
#define RCIC_ENTR_VLD_valid_0_mask                                                   (0x00000001)
#define RCIC_ENTR_VLD_valid_0(data)                                                  (0x00000001&((data)<<0))
#define RCIC_ENTR_VLD_valid_0_src(data)                                              ((0x00000001&(data))>>0)
#define RCIC_ENTR_VLD_get_valid_0(data)                                              ((0x00000001&(data))>>0)


#define RCIC_STATUS                                                                  0x180159a8
#define RCIC_STATUS_reg_addr                                                         "0xB80159A8"
#define RCIC_STATUS_reg                                                              0xB80159A8
#define set_RCIC_STATUS_reg(data)   (*((volatile unsigned int*) RCIC_STATUS_reg)=data)
#define get_RCIC_STATUS_reg   (*((volatile unsigned int*) RCIC_STATUS_reg))
#define RCIC_STATUS_inst_adr                                                         "0x006A"
#define RCIC_STATUS_inst                                                             0x006A
#define RCIC_STATUS_entry_shift                                                      (1)
#define RCIC_STATUS_entry_mask                                                       (0x0000000E)
#define RCIC_STATUS_entry(data)                                                      (0x0000000E&((data)<<1))
#define RCIC_STATUS_entry_src(data)                                                  ((0x0000000E&(data))>>1)
#define RCIC_STATUS_get_entry(data)                                                  ((0x0000000E&(data))>>1)
#define RCIC_STATUS_done_shift                                                       (0)
#define RCIC_STATUS_done_mask                                                        (0x00000001)
#define RCIC_STATUS_done(data)                                                       (0x00000001&((data)<<0))
#define RCIC_STATUS_done_src(data)                                                   ((0x00000001&(data))>>0)
#define RCIC_STATUS_get_done(data)                                                   ((0x00000001&(data))>>0)


#define RCIC_ENTR_SRC_0                                                              0x180159AC
#define RCIC_ENTR_SRC_1                                                              0x180159B0
#define RCIC_ENTR_SRC_2                                                              0x180159B4
#define RCIC_ENTR_SRC_3                                                              0x180159B8
#define RCIC_ENTR_SRC_4                                                              0x180159BC
#define RCIC_ENTR_SRC_5                                                              0x180159C0
#define RCIC_ENTR_SRC_6                                                              0x180159C4
#define RCIC_ENTR_SRC_7                                                              0x180159C8
#define RCIC_ENTR_SRC_0_reg_addr                                                     "0xB80159AC"
#define RCIC_ENTR_SRC_1_reg_addr                                                     "0xB80159B0"
#define RCIC_ENTR_SRC_2_reg_addr                                                     "0xB80159B4"
#define RCIC_ENTR_SRC_3_reg_addr                                                     "0xB80159B8"
#define RCIC_ENTR_SRC_4_reg_addr                                                     "0xB80159BC"
#define RCIC_ENTR_SRC_5_reg_addr                                                     "0xB80159C0"
#define RCIC_ENTR_SRC_6_reg_addr                                                     "0xB80159C4"
#define RCIC_ENTR_SRC_7_reg_addr                                                     "0xB80159C8"
#define RCIC_ENTR_SRC_0_reg                                                          0xB80159AC
#define RCIC_ENTR_SRC_1_reg                                                          0xB80159B0
#define RCIC_ENTR_SRC_2_reg                                                          0xB80159B4
#define RCIC_ENTR_SRC_3_reg                                                          0xB80159B8
#define RCIC_ENTR_SRC_4_reg                                                          0xB80159BC
#define RCIC_ENTR_SRC_5_reg                                                          0xB80159C0
#define RCIC_ENTR_SRC_6_reg                                                          0xB80159C4
#define RCIC_ENTR_SRC_7_reg                                                          0xB80159C8
#define set_RCIC_ENTR_SRC_0_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_SRC_0_reg)=data)
#define set_RCIC_ENTR_SRC_1_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_SRC_1_reg)=data)
#define set_RCIC_ENTR_SRC_2_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_SRC_2_reg)=data)
#define set_RCIC_ENTR_SRC_3_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_SRC_3_reg)=data)
#define set_RCIC_ENTR_SRC_4_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_SRC_4_reg)=data)
#define set_RCIC_ENTR_SRC_5_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_SRC_5_reg)=data)
#define set_RCIC_ENTR_SRC_6_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_SRC_6_reg)=data)
#define set_RCIC_ENTR_SRC_7_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_SRC_7_reg)=data)
#define get_RCIC_ENTR_SRC_0_reg   (*((volatile unsigned int*) RCIC_ENTR_SRC_0_reg))
#define get_RCIC_ENTR_SRC_1_reg   (*((volatile unsigned int*) RCIC_ENTR_SRC_1_reg))
#define get_RCIC_ENTR_SRC_2_reg   (*((volatile unsigned int*) RCIC_ENTR_SRC_2_reg))
#define get_RCIC_ENTR_SRC_3_reg   (*((volatile unsigned int*) RCIC_ENTR_SRC_3_reg))
#define get_RCIC_ENTR_SRC_4_reg   (*((volatile unsigned int*) RCIC_ENTR_SRC_4_reg))
#define get_RCIC_ENTR_SRC_5_reg   (*((volatile unsigned int*) RCIC_ENTR_SRC_5_reg))
#define get_RCIC_ENTR_SRC_6_reg   (*((volatile unsigned int*) RCIC_ENTR_SRC_6_reg))
#define get_RCIC_ENTR_SRC_7_reg   (*((volatile unsigned int*) RCIC_ENTR_SRC_7_reg))
#define RCIC_ENTR_SRC_0_inst_adr                                                     "0x006B"
#define RCIC_ENTR_SRC_1_inst_adr                                                     "0x006C"
#define RCIC_ENTR_SRC_2_inst_adr                                                     "0x006D"
#define RCIC_ENTR_SRC_3_inst_adr                                                     "0x006E"
#define RCIC_ENTR_SRC_4_inst_adr                                                     "0x006F"
#define RCIC_ENTR_SRC_5_inst_adr                                                     "0x0070"
#define RCIC_ENTR_SRC_6_inst_adr                                                     "0x0071"
#define RCIC_ENTR_SRC_7_inst_adr                                                     "0x0072"
#define RCIC_ENTR_SRC_0_inst                                                         0x006B
#define RCIC_ENTR_SRC_1_inst                                                         0x006C
#define RCIC_ENTR_SRC_2_inst                                                         0x006D
#define RCIC_ENTR_SRC_3_inst                                                         0x006E
#define RCIC_ENTR_SRC_4_inst                                                         0x006F
#define RCIC_ENTR_SRC_5_inst                                                         0x0070
#define RCIC_ENTR_SRC_6_inst                                                         0x0071
#define RCIC_ENTR_SRC_7_inst                                                         0x0072
#define RCIC_ENTR_SRC_adr_shift                                                      (0)
#define RCIC_ENTR_SRC_adr_mask                                                       (0xFFFFFFFF)
#define RCIC_ENTR_SRC_adr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define RCIC_ENTR_SRC_adr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define RCIC_ENTR_SRC_get_adr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define RCIC_ENTR_DST_0                                                              0x180159CC
#define RCIC_ENTR_DST_1                                                              0x180159D0
#define RCIC_ENTR_DST_2                                                              0x180159D4
#define RCIC_ENTR_DST_3                                                              0x180159D8
#define RCIC_ENTR_DST_4                                                              0x180159DC
#define RCIC_ENTR_DST_5                                                              0x180159E0
#define RCIC_ENTR_DST_6                                                              0x180159E4
#define RCIC_ENTR_DST_7                                                              0x180159E8
#define RCIC_ENTR_DST_0_reg_addr                                                     "0xB80159CC"
#define RCIC_ENTR_DST_1_reg_addr                                                     "0xB80159D0"
#define RCIC_ENTR_DST_2_reg_addr                                                     "0xB80159D4"
#define RCIC_ENTR_DST_3_reg_addr                                                     "0xB80159D8"
#define RCIC_ENTR_DST_4_reg_addr                                                     "0xB80159DC"
#define RCIC_ENTR_DST_5_reg_addr                                                     "0xB80159E0"
#define RCIC_ENTR_DST_6_reg_addr                                                     "0xB80159E4"
#define RCIC_ENTR_DST_7_reg_addr                                                     "0xB80159E8"
#define RCIC_ENTR_DST_0_reg                                                          0xB80159CC
#define RCIC_ENTR_DST_1_reg                                                          0xB80159D0
#define RCIC_ENTR_DST_2_reg                                                          0xB80159D4
#define RCIC_ENTR_DST_3_reg                                                          0xB80159D8
#define RCIC_ENTR_DST_4_reg                                                          0xB80159DC
#define RCIC_ENTR_DST_5_reg                                                          0xB80159E0
#define RCIC_ENTR_DST_6_reg                                                          0xB80159E4
#define RCIC_ENTR_DST_7_reg                                                          0xB80159E8
#define set_RCIC_ENTR_DST_0_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_DST_0_reg)=data)
#define set_RCIC_ENTR_DST_1_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_DST_1_reg)=data)
#define set_RCIC_ENTR_DST_2_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_DST_2_reg)=data)
#define set_RCIC_ENTR_DST_3_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_DST_3_reg)=data)
#define set_RCIC_ENTR_DST_4_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_DST_4_reg)=data)
#define set_RCIC_ENTR_DST_5_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_DST_5_reg)=data)
#define set_RCIC_ENTR_DST_6_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_DST_6_reg)=data)
#define set_RCIC_ENTR_DST_7_reg(data)   (*((volatile unsigned int*) RCIC_ENTR_DST_7_reg)=data)
#define get_RCIC_ENTR_DST_0_reg   (*((volatile unsigned int*) RCIC_ENTR_DST_0_reg))
#define get_RCIC_ENTR_DST_1_reg   (*((volatile unsigned int*) RCIC_ENTR_DST_1_reg))
#define get_RCIC_ENTR_DST_2_reg   (*((volatile unsigned int*) RCIC_ENTR_DST_2_reg))
#define get_RCIC_ENTR_DST_3_reg   (*((volatile unsigned int*) RCIC_ENTR_DST_3_reg))
#define get_RCIC_ENTR_DST_4_reg   (*((volatile unsigned int*) RCIC_ENTR_DST_4_reg))
#define get_RCIC_ENTR_DST_5_reg   (*((volatile unsigned int*) RCIC_ENTR_DST_5_reg))
#define get_RCIC_ENTR_DST_6_reg   (*((volatile unsigned int*) RCIC_ENTR_DST_6_reg))
#define get_RCIC_ENTR_DST_7_reg   (*((volatile unsigned int*) RCIC_ENTR_DST_7_reg))
#define RCIC_ENTR_DST_0_inst_adr                                                     "0x0073"
#define RCIC_ENTR_DST_1_inst_adr                                                     "0x0074"
#define RCIC_ENTR_DST_2_inst_adr                                                     "0x0075"
#define RCIC_ENTR_DST_3_inst_adr                                                     "0x0076"
#define RCIC_ENTR_DST_4_inst_adr                                                     "0x0077"
#define RCIC_ENTR_DST_5_inst_adr                                                     "0x0078"
#define RCIC_ENTR_DST_6_inst_adr                                                     "0x0079"
#define RCIC_ENTR_DST_7_inst_adr                                                     "0x007A"
#define RCIC_ENTR_DST_0_inst                                                         0x0073
#define RCIC_ENTR_DST_1_inst                                                         0x0074
#define RCIC_ENTR_DST_2_inst                                                         0x0075
#define RCIC_ENTR_DST_3_inst                                                         0x0076
#define RCIC_ENTR_DST_4_inst                                                         0x0077
#define RCIC_ENTR_DST_5_inst                                                         0x0078
#define RCIC_ENTR_DST_6_inst                                                         0x0079
#define RCIC_ENTR_DST_7_inst                                                         0x007A
#define RCIC_ENTR_DST_adr_shift                                                      (0)
#define RCIC_ENTR_DST_adr_mask                                                       (0xFFFFFFFF)
#define RCIC_ENTR_DST_adr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define RCIC_ENTR_DST_adr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define RCIC_ENTR_DST_get_adr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define RCIC_INT_EN                                                                  0x180159ec
#define RCIC_INT_EN_reg_addr                                                         "0xB80159EC"
#define RCIC_INT_EN_reg                                                              0xB80159EC
#define set_RCIC_INT_EN_reg(data)   (*((volatile unsigned int*) RCIC_INT_EN_reg)=data)
#define get_RCIC_INT_EN_reg   (*((volatile unsigned int*) RCIC_INT_EN_reg))
#define RCIC_INT_EN_inst_adr                                                         "0x007B"
#define RCIC_INT_EN_inst                                                             0x007B
#define RCIC_INT_EN_rcic_bc_shift                                                    (1)
#define RCIC_INT_EN_rcic_bc_mask                                                     (0x00000002)
#define RCIC_INT_EN_rcic_bc(data)                                                    (0x00000002&((data)<<1))
#define RCIC_INT_EN_rcic_bc_src(data)                                                ((0x00000002&(data))>>1)
#define RCIC_INT_EN_get_rcic_bc(data)                                                ((0x00000002&(data))>>1)
#define RCIC_INT_EN_int_en_shift                                                     (0)
#define RCIC_INT_EN_int_en_mask                                                      (0x00000001)
#define RCIC_INT_EN_int_en(data)                                                     (0x00000001&((data)<<0))
#define RCIC_INT_EN_int_en_src(data)                                                 ((0x00000001&(data))>>0)
#define RCIC_INT_EN_get_int_en(data)                                                 ((0x00000001&(data))>>0)


#endif
