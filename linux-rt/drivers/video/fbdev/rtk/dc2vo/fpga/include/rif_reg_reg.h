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


#ifndef _RIF_REG_REG_H_INCLUDED_
#define _RIF_REG_REG_H_INCLUDED_
#ifdef  _RIF_REG_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     ve_fpga_reset:1;
unsigned int     reserved_1:2;
unsigned int     dbg_out_sel1:5;
unsigned int     dbg_out_sel0:5;
unsigned int     dbg_out_en:1;
unsigned int     reserved_2:8;
unsigned int     ve_soft_reset:1;
unsigned int     vm_idle:1;
unsigned int     decode_en:1;
unsigned int     haltVE_done:1;
unsigned int     HaltVE:1;
unsigned int     Veidle:1;
unsigned int     IntEn:1;
unsigned int     Reset_ptr:1;
}RIF_REG_VE_CTRL;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     first_error:4;
unsigned int     cmd_fifo_full_int:1;
unsigned int     rd_rslt_hang_int:1;
unsigned int     rl_hang_int:1;
unsigned int     pred_hang_int:1;
unsigned int     mb_last_int:1;
unsigned int     mvd_vc1_intfd_err:1;
unsigned int     mvd_h264_direct_err:1;
unsigned int     mvd_h264_mv_err:1;
unsigned int     reserved_1:1;
unsigned int     m64coeff:1;
unsigned int     rstff_oflow:1;
unsigned int     rstff_empty:1;
unsigned int     bitst_fifo:1;
unsigned int     scode_limit:1;
unsigned int     dec_err:1;
unsigned int     write_data:1;
}RIF_REG_VE_INT_STATUS;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     cmd_fifo_full_int_ie:1;
unsigned int     rd_rslt_hang_int_ie:1;
unsigned int     rl_hang_int_ie:1;
unsigned int     pred_hang_int_ie:1;
unsigned int     mb_last_int_ie:1;
unsigned int     mvd_vc1_intfd_ie:1;
unsigned int     mvd_h264_direct_ie:1;
unsigned int     mvd_h264_mv_ie:1;
unsigned int     reserved_1:1;
unsigned int     m64coeff_ie:1;
unsigned int     rstff_oflow_ie:1;
unsigned int     rstff_empty_ie:1;
unsigned int     bitst_fifo_ie:1;
unsigned int     scode_limit_ie:1;
unsigned int     dec_err_ie:1;
unsigned int     write_data:1;
}RIF_REG_VE_INT_EN;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     debk_inst_cnt:6;
unsigned int     reserved_1:2;
unsigned int     pred_inst_cnt:6;
unsigned int     reserved_2:10;
unsigned int     dmaa_inst_cnt:6;
}RIF_REG_VE_FIFOSTATUS;

typedef struct 
{
unsigned int     act_rslt_in_fifo:5;
unsigned int     rslt_fifo_cnt:5;
unsigned int     img_fifo_cnt:6;
unsigned int     reserved_0:2;
unsigned int     dec_inst_cnt:6;
unsigned int     reserved_1:8;
}RIF_REG_VE_FIFOSTAT2;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     rslt_timer:24;
}RIF_REG_VE_RSLT_TIMER;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     cmd_timer:24;
}RIF_REG_VE_CMD_TIMER;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     ve_img_bnk:3;
unsigned int     reserved_1:1;
unsigned int     ve_deb_bnk:3;
unsigned int     reserved_2:1;
unsigned int     ve_prd_bnk:3;
unsigned int     reserved_3:5;
unsigned int     ve_dmaa_bnk:3;
}RIF_REG_VMBANKSEL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     monochrome:1;
unsigned int     level:1;
unsigned int     profile:2;
unsigned int     coding_type:4;
}RIF_REG_DEC_CNTL;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     vp8_bicubic_filtering:1;
unsigned int     bottom_field_flag:1;
unsigned int     field_pic_flag:1;
unsigned int     picmb_h:7;
unsigned int     picmb_w:7;
}RIF_REG_PICINFO1;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     Constrainted_intra_pred_flag:1;
unsigned int     Weighted_pred_flag:1;
unsigned int     Weighted_bipred_idc:2;
unsigned int     frame_mbs_only_flag:1;
unsigned int     mb_adaptive_frame_field_flag:1;
}RIF_REG_H264PICCNTL;

typedef struct 
{
unsigned int     Overlap_enable:1;
unsigned int     field_pictype:3;
unsigned int     mvmode:2;
unsigned int     fcm:2;
unsigned int     disppic_h:12;
unsigned int     disppic_w:12;
}RIF_REG_VC1PICCNTL;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     wmv9_bug_rtmflag:1;
unsigned int     wmv9_bug_it:1;
unsigned int     loopfilter:1;
unsigned int     numref:1;
unsigned int     pquant:5;
}RIF_REG_VC1PICCNTL2;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     priority_thd2:8;
unsigned int     priority_thd1:8;
unsigned int     reserved_1:4;
unsigned int     srg_mode:1;
unsigned int     ddr_page:2;
unsigned int     srg_enable:1;
}RIF_REG_BRG_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vm1:8;
}RIF_REG_RD_PRIORITY0;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     deblk:8;
unsigned int     reserved_1:8;
unsigned int     predblk:8;
}RIF_REG_RD_PRIORITY1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     nm:8;
unsigned int     reserved_1:8;
unsigned int     mvd:8;
}RIF_REG_RD_PRIORITY2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     bs:8;
}RIF_REG_RD_PRIORITY3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rl:8;
}RIF_REG_RD_PRIORITY4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vm1:8;
}RIF_REG_WT_PRIORITY0;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     deblk:8;
unsigned int     reserved_1:8;
unsigned int     predblk:8;
}RIF_REG_WT_PRIORITY1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     nm:8;
unsigned int     reserved_1:8;
unsigned int     mvd:8;
}RIF_REG_WT_PRIORITY2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     bs:8;
}RIF_REG_WT_PRIORITY3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     it:8;
}RIF_REG_WT_PRIORITY4;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     cache_gated_en:1;
unsigned int     rl_gated_en:1;
unsigned int     mvd_gated_en:1;
unsigned int     ndbp2_gated_en:1;
unsigned int     ndb_gated_en:1;
unsigned int     brg_gated_en:1;
unsigned int     cm_gated_en:1;
unsigned int     arb_gated_en:1;
unsigned int     bsfifop2_gated_en:1;
unsigned int     bsfifo_gated_en:1;
unsigned int     deblk_gated_en:1;
unsigned int     pred_gated_en:1;
unsigned int     vm1_gated_en:1;
unsigned int     it_gated_en:1;
unsigned int     cabac_gated_en:1;
unsigned int     vp8p2_gated_en:1;
unsigned int     cabacp2_gated_en:1;
unsigned int     vld_gated_en:1;
unsigned int     acdc_gated_en:1;
}RIF_REG_CLKGATED;

typedef struct 
{
unsigned int     ve_dbg_out1:16;
unsigned int     ve_dbg_out0:16;
}RIF_REG_DBG_OUT;

typedef struct 
{
unsigned int     cache_dbg_sel1:4;
unsigned int     cache_dbg_sel0:4;
unsigned int     bs_dbg_sel1:4;
unsigned int     bs_dbg_sel0:4;
unsigned int     brg_dbg_sel1:4;
unsigned int     brg_dbg_sel0:4;
unsigned int     acdc_dbg_sel1:4;
unsigned int     acdc_dbg_sel0:4;
}RIF_REG_DBG_CTRL1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     cm_dbg_sel1:4;
unsigned int     cm_dbg_sel0:4;
unsigned int     cabacp3_dbg_sel1:4;
unsigned int     cabacp3_dbg_sel0:4;
unsigned int     cabacp2_dbg_sel1:4;
unsigned int     cabacp2_dbg_sel0:4;
}RIF_REG_DBG_CTRL2;

typedef struct 
{
unsigned int     ndb_dbg_sel1:4;
unsigned int     ndb_dbg_sel0:4;
unsigned int     rif_dbg_sel1:4;
unsigned int     rif_dbg_sel0:4;
unsigned int     itblk_dbg_sel1:4;
unsigned int     itblk_dbg_sel0:4;
unsigned int     img_dbg_sel1:4;
unsigned int     img_dbg_sel0:4;
}RIF_REG_DBG_CTRL3;

typedef struct 
{
unsigned int     rl_dbg_sel1:4;
unsigned int     rl_dbg_sel0:4;
unsigned int     vld_dbg_sel1:4;
unsigned int     vld_dbg_sel0:4;
unsigned int     arb_dbg_sel1:4;
unsigned int     arb_dbg_sel0:4;
unsigned int     vm1_dbg_sel1:4;
unsigned int     vm1_dbg_sel0:4;
}RIF_REG_DBG_CTRL4;

typedef struct 
{
unsigned int     deblk_dbg_sel1:6;
unsigned int     deblk_dbg_sel0:6;
unsigned int     mvd_dbg_sel1:4;
unsigned int     mvd_dbg_sel0:4;
unsigned int     prd_dbg_sel1:6;
unsigned int     prd_dbg_sel0:6;
}RIF_REG_DBG_CTRL5;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     cache_busy:1;
unsigned int     brg_busy:1;
unsigned int     ndb_busy:1;
unsigned int     bsfifo_busy:1;
unsigned int     img_busy:1;
unsigned int     vm1_busy:1;
unsigned int     deblk_busy:1;
unsigned int     rl_busy:1;
unsigned int     pred_busy:1;
unsigned int     mvd_busy:1;
unsigned int     itblk_busy:1;
unsigned int     acdc_busy:1;
unsigned int     cabacp2_busy:1;
unsigned int     vld_busy:1;
unsigned int     rifvld_busy:1;
}RIF_REG_FPGA_DBG1;

#endif

#define RIF_REG_VE_CTRL                                                              0x1800E400
#define RIF_REG_VE_CTRL_reg_addr                                                     "0xB800E400"
#define RIF_REG_VE_CTRL_reg                                                          0xB800E400
#define set_RIF_REG_VE_CTRL_reg(data)   (*((volatile unsigned int*) RIF_REG_VE_CTRL_reg)=data)
#define get_RIF_REG_VE_CTRL_reg   (*((volatile unsigned int*) RIF_REG_VE_CTRL_reg))
#define RIF_REG_VE_CTRL_inst_adr                                                     "0x0000"
#define RIF_REG_VE_CTRL_inst                                                         0x0000
#define RIF_REG_VE_CTRL_ve_fpga_reset_shift                                          (29)
#define RIF_REG_VE_CTRL_ve_fpga_reset_mask                                           (0x20000000)
#define RIF_REG_VE_CTRL_ve_fpga_reset(data)                                          (0x20000000&((data)<<29))
#define RIF_REG_VE_CTRL_ve_fpga_reset_src(data)                                      ((0x20000000&(data))>>29)
#define RIF_REG_VE_CTRL_get_ve_fpga_reset(data)                                      ((0x20000000&(data))>>29)
#define RIF_REG_VE_CTRL_dbg_out_sel1_shift                                           (22)
#define RIF_REG_VE_CTRL_dbg_out_sel1_mask                                            (0x07C00000)
#define RIF_REG_VE_CTRL_dbg_out_sel1(data)                                           (0x07C00000&((data)<<22))
#define RIF_REG_VE_CTRL_dbg_out_sel1_src(data)                                       ((0x07C00000&(data))>>22)
#define RIF_REG_VE_CTRL_get_dbg_out_sel1(data)                                       ((0x07C00000&(data))>>22)
#define RIF_REG_VE_CTRL_dbg_out_sel0_shift                                           (17)
#define RIF_REG_VE_CTRL_dbg_out_sel0_mask                                            (0x003E0000)
#define RIF_REG_VE_CTRL_dbg_out_sel0(data)                                           (0x003E0000&((data)<<17))
#define RIF_REG_VE_CTRL_dbg_out_sel0_src(data)                                       ((0x003E0000&(data))>>17)
#define RIF_REG_VE_CTRL_get_dbg_out_sel0(data)                                       ((0x003E0000&(data))>>17)
#define RIF_REG_VE_CTRL_dbg_out_en_shift                                             (16)
#define RIF_REG_VE_CTRL_dbg_out_en_mask                                              (0x00010000)
#define RIF_REG_VE_CTRL_dbg_out_en(data)                                             (0x00010000&((data)<<16))
#define RIF_REG_VE_CTRL_dbg_out_en_src(data)                                         ((0x00010000&(data))>>16)
#define RIF_REG_VE_CTRL_get_dbg_out_en(data)                                         ((0x00010000&(data))>>16)
#define RIF_REG_VE_CTRL_ve_soft_reset_shift                                          (7)
#define RIF_REG_VE_CTRL_ve_soft_reset_mask                                           (0x00000080)
#define RIF_REG_VE_CTRL_ve_soft_reset(data)                                          (0x00000080&((data)<<7))
#define RIF_REG_VE_CTRL_ve_soft_reset_src(data)                                      ((0x00000080&(data))>>7)
#define RIF_REG_VE_CTRL_get_ve_soft_reset(data)                                      ((0x00000080&(data))>>7)
#define RIF_REG_VE_CTRL_vm_idle_shift                                                (6)
#define RIF_REG_VE_CTRL_vm_idle_mask                                                 (0x00000040)
#define RIF_REG_VE_CTRL_vm_idle(data)                                                (0x00000040&((data)<<6))
#define RIF_REG_VE_CTRL_vm_idle_src(data)                                            ((0x00000040&(data))>>6)
#define RIF_REG_VE_CTRL_get_vm_idle(data)                                            ((0x00000040&(data))>>6)
#define RIF_REG_VE_CTRL_decode_en_shift                                              (5)
#define RIF_REG_VE_CTRL_decode_en_mask                                               (0x00000020)
#define RIF_REG_VE_CTRL_decode_en(data)                                              (0x00000020&((data)<<5))
#define RIF_REG_VE_CTRL_decode_en_src(data)                                          ((0x00000020&(data))>>5)
#define RIF_REG_VE_CTRL_get_decode_en(data)                                          ((0x00000020&(data))>>5)
#define RIF_REG_VE_CTRL_haltVE_done_shift                                            (4)
#define RIF_REG_VE_CTRL_haltVE_done_mask                                             (0x00000010)
#define RIF_REG_VE_CTRL_haltVE_done(data)                                            (0x00000010&((data)<<4))
#define RIF_REG_VE_CTRL_haltVE_done_src(data)                                        ((0x00000010&(data))>>4)
#define RIF_REG_VE_CTRL_get_haltVE_done(data)                                        ((0x00000010&(data))>>4)
#define RIF_REG_VE_CTRL_HaltVE_shift                                                 (3)
#define RIF_REG_VE_CTRL_HaltVE_mask                                                  (0x00000008)
#define RIF_REG_VE_CTRL_HaltVE(data)                                                 (0x00000008&((data)<<3))
#define RIF_REG_VE_CTRL_HaltVE_src(data)                                             ((0x00000008&(data))>>3)
#define RIF_REG_VE_CTRL_get_HaltVE(data)                                             ((0x00000008&(data))>>3)
#define RIF_REG_VE_CTRL_Veidle_shift                                                 (2)
#define RIF_REG_VE_CTRL_Veidle_mask                                                  (0x00000004)
#define RIF_REG_VE_CTRL_Veidle(data)                                                 (0x00000004&((data)<<2))
#define RIF_REG_VE_CTRL_Veidle_src(data)                                             ((0x00000004&(data))>>2)
#define RIF_REG_VE_CTRL_get_Veidle(data)                                             ((0x00000004&(data))>>2)
#define RIF_REG_VE_CTRL_IntEn_shift                                                  (1)
#define RIF_REG_VE_CTRL_IntEn_mask                                                   (0x00000002)
#define RIF_REG_VE_CTRL_IntEn(data)                                                  (0x00000002&((data)<<1))
#define RIF_REG_VE_CTRL_IntEn_src(data)                                              ((0x00000002&(data))>>1)
#define RIF_REG_VE_CTRL_get_IntEn(data)                                              ((0x00000002&(data))>>1)
#define RIF_REG_VE_CTRL_Reset_ptr_shift                                              (0)
#define RIF_REG_VE_CTRL_Reset_ptr_mask                                               (0x00000001)
#define RIF_REG_VE_CTRL_Reset_ptr(data)                                              (0x00000001&((data)<<0))
#define RIF_REG_VE_CTRL_Reset_ptr_src(data)                                          ((0x00000001&(data))>>0)
#define RIF_REG_VE_CTRL_get_Reset_ptr(data)                                          ((0x00000001&(data))>>0)


#define RIF_REG_VE_INT_STATUS                                                        0x1800E404
#define RIF_REG_VE_INT_STATUS_reg_addr                                               "0xB800E404"
#define RIF_REG_VE_INT_STATUS_reg                                                    0xB800E404
#define set_RIF_REG_VE_INT_STATUS_reg(data)   (*((volatile unsigned int*) RIF_REG_VE_INT_STATUS_reg)=data)
#define get_RIF_REG_VE_INT_STATUS_reg   (*((volatile unsigned int*) RIF_REG_VE_INT_STATUS_reg))
#define RIF_REG_VE_INT_STATUS_inst_adr                                               "0x0001"
#define RIF_REG_VE_INT_STATUS_inst                                                   0x0001
#define RIF_REG_VE_INT_STATUS_first_error_shift                                      (16)
#define RIF_REG_VE_INT_STATUS_first_error_mask                                       (0x000F0000)
#define RIF_REG_VE_INT_STATUS_first_error(data)                                      (0x000F0000&((data)<<16))
#define RIF_REG_VE_INT_STATUS_first_error_src(data)                                  ((0x000F0000&(data))>>16)
#define RIF_REG_VE_INT_STATUS_get_first_error(data)                                  ((0x000F0000&(data))>>16)
#define RIF_REG_VE_INT_STATUS_cmd_fifo_full_int_shift                                (15)
#define RIF_REG_VE_INT_STATUS_cmd_fifo_full_int_mask                                 (0x00008000)
#define RIF_REG_VE_INT_STATUS_cmd_fifo_full_int(data)                                (0x00008000&((data)<<15))
#define RIF_REG_VE_INT_STATUS_cmd_fifo_full_int_src(data)                            ((0x00008000&(data))>>15)
#define RIF_REG_VE_INT_STATUS_get_cmd_fifo_full_int(data)                            ((0x00008000&(data))>>15)
#define RIF_REG_VE_INT_STATUS_rd_rslt_hang_int_shift                                 (14)
#define RIF_REG_VE_INT_STATUS_rd_rslt_hang_int_mask                                  (0x00004000)
#define RIF_REG_VE_INT_STATUS_rd_rslt_hang_int(data)                                 (0x00004000&((data)<<14))
#define RIF_REG_VE_INT_STATUS_rd_rslt_hang_int_src(data)                             ((0x00004000&(data))>>14)
#define RIF_REG_VE_INT_STATUS_get_rd_rslt_hang_int(data)                             ((0x00004000&(data))>>14)
#define RIF_REG_VE_INT_STATUS_rl_hang_int_shift                                      (13)
#define RIF_REG_VE_INT_STATUS_rl_hang_int_mask                                       (0x00002000)
#define RIF_REG_VE_INT_STATUS_rl_hang_int(data)                                      (0x00002000&((data)<<13))
#define RIF_REG_VE_INT_STATUS_rl_hang_int_src(data)                                  ((0x00002000&(data))>>13)
#define RIF_REG_VE_INT_STATUS_get_rl_hang_int(data)                                  ((0x00002000&(data))>>13)
#define RIF_REG_VE_INT_STATUS_pred_hang_int_shift                                    (12)
#define RIF_REG_VE_INT_STATUS_pred_hang_int_mask                                     (0x00001000)
#define RIF_REG_VE_INT_STATUS_pred_hang_int(data)                                    (0x00001000&((data)<<12))
#define RIF_REG_VE_INT_STATUS_pred_hang_int_src(data)                                ((0x00001000&(data))>>12)
#define RIF_REG_VE_INT_STATUS_get_pred_hang_int(data)                                ((0x00001000&(data))>>12)
#define RIF_REG_VE_INT_STATUS_mb_last_int_shift                                      (11)
#define RIF_REG_VE_INT_STATUS_mb_last_int_mask                                       (0x00000800)
#define RIF_REG_VE_INT_STATUS_mb_last_int(data)                                      (0x00000800&((data)<<11))
#define RIF_REG_VE_INT_STATUS_mb_last_int_src(data)                                  ((0x00000800&(data))>>11)
#define RIF_REG_VE_INT_STATUS_get_mb_last_int(data)                                  ((0x00000800&(data))>>11)
#define RIF_REG_VE_INT_STATUS_mvd_vc1_intfd_err_shift                                (10)
#define RIF_REG_VE_INT_STATUS_mvd_vc1_intfd_err_mask                                 (0x00000400)
#define RIF_REG_VE_INT_STATUS_mvd_vc1_intfd_err(data)                                (0x00000400&((data)<<10))
#define RIF_REG_VE_INT_STATUS_mvd_vc1_intfd_err_src(data)                            ((0x00000400&(data))>>10)
#define RIF_REG_VE_INT_STATUS_get_mvd_vc1_intfd_err(data)                            ((0x00000400&(data))>>10)
#define RIF_REG_VE_INT_STATUS_mvd_h264_direct_err_shift                              (9)
#define RIF_REG_VE_INT_STATUS_mvd_h264_direct_err_mask                               (0x00000200)
#define RIF_REG_VE_INT_STATUS_mvd_h264_direct_err(data)                              (0x00000200&((data)<<9))
#define RIF_REG_VE_INT_STATUS_mvd_h264_direct_err_src(data)                          ((0x00000200&(data))>>9)
#define RIF_REG_VE_INT_STATUS_get_mvd_h264_direct_err(data)                          ((0x00000200&(data))>>9)
#define RIF_REG_VE_INT_STATUS_mvd_h264_mv_err_shift                                  (8)
#define RIF_REG_VE_INT_STATUS_mvd_h264_mv_err_mask                                   (0x00000100)
#define RIF_REG_VE_INT_STATUS_mvd_h264_mv_err(data)                                  (0x00000100&((data)<<8))
#define RIF_REG_VE_INT_STATUS_mvd_h264_mv_err_src(data)                              ((0x00000100&(data))>>8)
#define RIF_REG_VE_INT_STATUS_get_mvd_h264_mv_err(data)                              ((0x00000100&(data))>>8)
#define RIF_REG_VE_INT_STATUS_m64coeff_shift                                         (6)
#define RIF_REG_VE_INT_STATUS_m64coeff_mask                                          (0x00000040)
#define RIF_REG_VE_INT_STATUS_m64coeff(data)                                         (0x00000040&((data)<<6))
#define RIF_REG_VE_INT_STATUS_m64coeff_src(data)                                     ((0x00000040&(data))>>6)
#define RIF_REG_VE_INT_STATUS_get_m64coeff(data)                                     ((0x00000040&(data))>>6)
#define RIF_REG_VE_INT_STATUS_rstff_oflow_shift                                      (5)
#define RIF_REG_VE_INT_STATUS_rstff_oflow_mask                                       (0x00000020)
#define RIF_REG_VE_INT_STATUS_rstff_oflow(data)                                      (0x00000020&((data)<<5))
#define RIF_REG_VE_INT_STATUS_rstff_oflow_src(data)                                  ((0x00000020&(data))>>5)
#define RIF_REG_VE_INT_STATUS_get_rstff_oflow(data)                                  ((0x00000020&(data))>>5)
#define RIF_REG_VE_INT_STATUS_rstff_empty_shift                                      (4)
#define RIF_REG_VE_INT_STATUS_rstff_empty_mask                                       (0x00000010)
#define RIF_REG_VE_INT_STATUS_rstff_empty(data)                                      (0x00000010&((data)<<4))
#define RIF_REG_VE_INT_STATUS_rstff_empty_src(data)                                  ((0x00000010&(data))>>4)
#define RIF_REG_VE_INT_STATUS_get_rstff_empty(data)                                  ((0x00000010&(data))>>4)
#define RIF_REG_VE_INT_STATUS_bitst_fifo_shift                                       (3)
#define RIF_REG_VE_INT_STATUS_bitst_fifo_mask                                        (0x00000008)
#define RIF_REG_VE_INT_STATUS_bitst_fifo(data)                                       (0x00000008&((data)<<3))
#define RIF_REG_VE_INT_STATUS_bitst_fifo_src(data)                                   ((0x00000008&(data))>>3)
#define RIF_REG_VE_INT_STATUS_get_bitst_fifo(data)                                   ((0x00000008&(data))>>3)
#define RIF_REG_VE_INT_STATUS_scode_limit_shift                                      (2)
#define RIF_REG_VE_INT_STATUS_scode_limit_mask                                       (0x00000004)
#define RIF_REG_VE_INT_STATUS_scode_limit(data)                                      (0x00000004&((data)<<2))
#define RIF_REG_VE_INT_STATUS_scode_limit_src(data)                                  ((0x00000004&(data))>>2)
#define RIF_REG_VE_INT_STATUS_get_scode_limit(data)                                  ((0x00000004&(data))>>2)
#define RIF_REG_VE_INT_STATUS_dec_err_shift                                          (1)
#define RIF_REG_VE_INT_STATUS_dec_err_mask                                           (0x00000002)
#define RIF_REG_VE_INT_STATUS_dec_err(data)                                          (0x00000002&((data)<<1))
#define RIF_REG_VE_INT_STATUS_dec_err_src(data)                                      ((0x00000002&(data))>>1)
#define RIF_REG_VE_INT_STATUS_get_dec_err(data)                                      ((0x00000002&(data))>>1)
#define RIF_REG_VE_INT_STATUS_write_data_shift                                       (0)
#define RIF_REG_VE_INT_STATUS_write_data_mask                                        (0x00000001)
#define RIF_REG_VE_INT_STATUS_write_data(data)                                       (0x00000001&((data)<<0))
#define RIF_REG_VE_INT_STATUS_write_data_src(data)                                   ((0x00000001&(data))>>0)
#define RIF_REG_VE_INT_STATUS_get_write_data(data)                                   ((0x00000001&(data))>>0)


#define RIF_REG_VE_INT_EN                                                            0x1800E408
#define RIF_REG_VE_INT_EN_reg_addr                                                   "0xB800E408"
#define RIF_REG_VE_INT_EN_reg                                                        0xB800E408
#define set_RIF_REG_VE_INT_EN_reg(data)   (*((volatile unsigned int*) RIF_REG_VE_INT_EN_reg)=data)
#define get_RIF_REG_VE_INT_EN_reg   (*((volatile unsigned int*) RIF_REG_VE_INT_EN_reg))
#define RIF_REG_VE_INT_EN_inst_adr                                                   "0x0002"
#define RIF_REG_VE_INT_EN_inst                                                       0x0002
#define RIF_REG_VE_INT_EN_cmd_fifo_full_int_ie_shift                                 (15)
#define RIF_REG_VE_INT_EN_cmd_fifo_full_int_ie_mask                                  (0x00008000)
#define RIF_REG_VE_INT_EN_cmd_fifo_full_int_ie(data)                                 (0x00008000&((data)<<15))
#define RIF_REG_VE_INT_EN_cmd_fifo_full_int_ie_src(data)                             ((0x00008000&(data))>>15)
#define RIF_REG_VE_INT_EN_get_cmd_fifo_full_int_ie(data)                             ((0x00008000&(data))>>15)
#define RIF_REG_VE_INT_EN_rd_rslt_hang_int_ie_shift                                  (14)
#define RIF_REG_VE_INT_EN_rd_rslt_hang_int_ie_mask                                   (0x00004000)
#define RIF_REG_VE_INT_EN_rd_rslt_hang_int_ie(data)                                  (0x00004000&((data)<<14))
#define RIF_REG_VE_INT_EN_rd_rslt_hang_int_ie_src(data)                              ((0x00004000&(data))>>14)
#define RIF_REG_VE_INT_EN_get_rd_rslt_hang_int_ie(data)                              ((0x00004000&(data))>>14)
#define RIF_REG_VE_INT_EN_rl_hang_int_ie_shift                                       (13)
#define RIF_REG_VE_INT_EN_rl_hang_int_ie_mask                                        (0x00002000)
#define RIF_REG_VE_INT_EN_rl_hang_int_ie(data)                                       (0x00002000&((data)<<13))
#define RIF_REG_VE_INT_EN_rl_hang_int_ie_src(data)                                   ((0x00002000&(data))>>13)
#define RIF_REG_VE_INT_EN_get_rl_hang_int_ie(data)                                   ((0x00002000&(data))>>13)
#define RIF_REG_VE_INT_EN_pred_hang_int_ie_shift                                     (12)
#define RIF_REG_VE_INT_EN_pred_hang_int_ie_mask                                      (0x00001000)
#define RIF_REG_VE_INT_EN_pred_hang_int_ie(data)                                     (0x00001000&((data)<<12))
#define RIF_REG_VE_INT_EN_pred_hang_int_ie_src(data)                                 ((0x00001000&(data))>>12)
#define RIF_REG_VE_INT_EN_get_pred_hang_int_ie(data)                                 ((0x00001000&(data))>>12)
#define RIF_REG_VE_INT_EN_mb_last_int_ie_shift                                       (11)
#define RIF_REG_VE_INT_EN_mb_last_int_ie_mask                                        (0x00000800)
#define RIF_REG_VE_INT_EN_mb_last_int_ie(data)                                       (0x00000800&((data)<<11))
#define RIF_REG_VE_INT_EN_mb_last_int_ie_src(data)                                   ((0x00000800&(data))>>11)
#define RIF_REG_VE_INT_EN_get_mb_last_int_ie(data)                                   ((0x00000800&(data))>>11)
#define RIF_REG_VE_INT_EN_mvd_vc1_intfd_ie_shift                                     (10)
#define RIF_REG_VE_INT_EN_mvd_vc1_intfd_ie_mask                                      (0x00000400)
#define RIF_REG_VE_INT_EN_mvd_vc1_intfd_ie(data)                                     (0x00000400&((data)<<10))
#define RIF_REG_VE_INT_EN_mvd_vc1_intfd_ie_src(data)                                 ((0x00000400&(data))>>10)
#define RIF_REG_VE_INT_EN_get_mvd_vc1_intfd_ie(data)                                 ((0x00000400&(data))>>10)
#define RIF_REG_VE_INT_EN_mvd_h264_direct_ie_shift                                   (9)
#define RIF_REG_VE_INT_EN_mvd_h264_direct_ie_mask                                    (0x00000200)
#define RIF_REG_VE_INT_EN_mvd_h264_direct_ie(data)                                   (0x00000200&((data)<<9))
#define RIF_REG_VE_INT_EN_mvd_h264_direct_ie_src(data)                               ((0x00000200&(data))>>9)
#define RIF_REG_VE_INT_EN_get_mvd_h264_direct_ie(data)                               ((0x00000200&(data))>>9)
#define RIF_REG_VE_INT_EN_mvd_h264_mv_ie_shift                                       (8)
#define RIF_REG_VE_INT_EN_mvd_h264_mv_ie_mask                                        (0x00000100)
#define RIF_REG_VE_INT_EN_mvd_h264_mv_ie(data)                                       (0x00000100&((data)<<8))
#define RIF_REG_VE_INT_EN_mvd_h264_mv_ie_src(data)                                   ((0x00000100&(data))>>8)
#define RIF_REG_VE_INT_EN_get_mvd_h264_mv_ie(data)                                   ((0x00000100&(data))>>8)
#define RIF_REG_VE_INT_EN_m64coeff_ie_shift                                          (6)
#define RIF_REG_VE_INT_EN_m64coeff_ie_mask                                           (0x00000040)
#define RIF_REG_VE_INT_EN_m64coeff_ie(data)                                          (0x00000040&((data)<<6))
#define RIF_REG_VE_INT_EN_m64coeff_ie_src(data)                                      ((0x00000040&(data))>>6)
#define RIF_REG_VE_INT_EN_get_m64coeff_ie(data)                                      ((0x00000040&(data))>>6)
#define RIF_REG_VE_INT_EN_rstff_oflow_ie_shift                                       (5)
#define RIF_REG_VE_INT_EN_rstff_oflow_ie_mask                                        (0x00000020)
#define RIF_REG_VE_INT_EN_rstff_oflow_ie(data)                                       (0x00000020&((data)<<5))
#define RIF_REG_VE_INT_EN_rstff_oflow_ie_src(data)                                   ((0x00000020&(data))>>5)
#define RIF_REG_VE_INT_EN_get_rstff_oflow_ie(data)                                   ((0x00000020&(data))>>5)
#define RIF_REG_VE_INT_EN_rstff_empty_ie_shift                                       (4)
#define RIF_REG_VE_INT_EN_rstff_empty_ie_mask                                        (0x00000010)
#define RIF_REG_VE_INT_EN_rstff_empty_ie(data)                                       (0x00000010&((data)<<4))
#define RIF_REG_VE_INT_EN_rstff_empty_ie_src(data)                                   ((0x00000010&(data))>>4)
#define RIF_REG_VE_INT_EN_get_rstff_empty_ie(data)                                   ((0x00000010&(data))>>4)
#define RIF_REG_VE_INT_EN_bitst_fifo_ie_shift                                        (3)
#define RIF_REG_VE_INT_EN_bitst_fifo_ie_mask                                         (0x00000008)
#define RIF_REG_VE_INT_EN_bitst_fifo_ie(data)                                        (0x00000008&((data)<<3))
#define RIF_REG_VE_INT_EN_bitst_fifo_ie_src(data)                                    ((0x00000008&(data))>>3)
#define RIF_REG_VE_INT_EN_get_bitst_fifo_ie(data)                                    ((0x00000008&(data))>>3)
#define RIF_REG_VE_INT_EN_scode_limit_ie_shift                                       (2)
#define RIF_REG_VE_INT_EN_scode_limit_ie_mask                                        (0x00000004)
#define RIF_REG_VE_INT_EN_scode_limit_ie(data)                                       (0x00000004&((data)<<2))
#define RIF_REG_VE_INT_EN_scode_limit_ie_src(data)                                   ((0x00000004&(data))>>2)
#define RIF_REG_VE_INT_EN_get_scode_limit_ie(data)                                   ((0x00000004&(data))>>2)
#define RIF_REG_VE_INT_EN_dec_err_ie_shift                                           (1)
#define RIF_REG_VE_INT_EN_dec_err_ie_mask                                            (0x00000002)
#define RIF_REG_VE_INT_EN_dec_err_ie(data)                                           (0x00000002&((data)<<1))
#define RIF_REG_VE_INT_EN_dec_err_ie_src(data)                                       ((0x00000002&(data))>>1)
#define RIF_REG_VE_INT_EN_get_dec_err_ie(data)                                       ((0x00000002&(data))>>1)
#define RIF_REG_VE_INT_EN_write_data_shift                                           (0)
#define RIF_REG_VE_INT_EN_write_data_mask                                            (0x00000001)
#define RIF_REG_VE_INT_EN_write_data(data)                                           (0x00000001&((data)<<0))
#define RIF_REG_VE_INT_EN_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define RIF_REG_VE_INT_EN_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define RIF_REG_VE_FIFOSTATUS                                                        0x1800E410
#define RIF_REG_VE_FIFOSTATUS_reg_addr                                               "0xB800E410"
#define RIF_REG_VE_FIFOSTATUS_reg                                                    0xB800E410
#define set_RIF_REG_VE_FIFOSTATUS_reg(data)   (*((volatile unsigned int*) RIF_REG_VE_FIFOSTATUS_reg)=data)
#define get_RIF_REG_VE_FIFOSTATUS_reg   (*((volatile unsigned int*) RIF_REG_VE_FIFOSTATUS_reg))
#define RIF_REG_VE_FIFOSTATUS_inst_adr                                               "0x0004"
#define RIF_REG_VE_FIFOSTATUS_inst                                                   0x0004
#define RIF_REG_VE_FIFOSTATUS_debk_inst_cnt_shift                                    (24)
#define RIF_REG_VE_FIFOSTATUS_debk_inst_cnt_mask                                     (0x3F000000)
#define RIF_REG_VE_FIFOSTATUS_debk_inst_cnt(data)                                    (0x3F000000&((data)<<24))
#define RIF_REG_VE_FIFOSTATUS_debk_inst_cnt_src(data)                                ((0x3F000000&(data))>>24)
#define RIF_REG_VE_FIFOSTATUS_get_debk_inst_cnt(data)                                ((0x3F000000&(data))>>24)
#define RIF_REG_VE_FIFOSTATUS_pred_inst_cnt_shift                                    (16)
#define RIF_REG_VE_FIFOSTATUS_pred_inst_cnt_mask                                     (0x003F0000)
#define RIF_REG_VE_FIFOSTATUS_pred_inst_cnt(data)                                    (0x003F0000&((data)<<16))
#define RIF_REG_VE_FIFOSTATUS_pred_inst_cnt_src(data)                                ((0x003F0000&(data))>>16)
#define RIF_REG_VE_FIFOSTATUS_get_pred_inst_cnt(data)                                ((0x003F0000&(data))>>16)
#define RIF_REG_VE_FIFOSTATUS_dmaa_inst_cnt_shift                                    (0)
#define RIF_REG_VE_FIFOSTATUS_dmaa_inst_cnt_mask                                     (0x0000003F)
#define RIF_REG_VE_FIFOSTATUS_dmaa_inst_cnt(data)                                    (0x0000003F&((data)<<0))
#define RIF_REG_VE_FIFOSTATUS_dmaa_inst_cnt_src(data)                                ((0x0000003F&(data))>>0)
#define RIF_REG_VE_FIFOSTATUS_get_dmaa_inst_cnt(data)                                ((0x0000003F&(data))>>0)


#define RIF_REG_VE_FIFOSTAT2                                                         0x1800E414
#define RIF_REG_VE_FIFOSTAT2_reg_addr                                                "0xB800E414"
#define RIF_REG_VE_FIFOSTAT2_reg                                                     0xB800E414
#define set_RIF_REG_VE_FIFOSTAT2_reg(data)   (*((volatile unsigned int*) RIF_REG_VE_FIFOSTAT2_reg)=data)
#define get_RIF_REG_VE_FIFOSTAT2_reg   (*((volatile unsigned int*) RIF_REG_VE_FIFOSTAT2_reg))
#define RIF_REG_VE_FIFOSTAT2_inst_adr                                                "0x0005"
#define RIF_REG_VE_FIFOSTAT2_inst                                                    0x0005
#define RIF_REG_VE_FIFOSTAT2_act_rslt_in_fifo_shift                                  (27)
#define RIF_REG_VE_FIFOSTAT2_act_rslt_in_fifo_mask                                   (0xF8000000)
#define RIF_REG_VE_FIFOSTAT2_act_rslt_in_fifo(data)                                  (0xF8000000&((data)<<27))
#define RIF_REG_VE_FIFOSTAT2_act_rslt_in_fifo_src(data)                              ((0xF8000000&(data))>>27)
#define RIF_REG_VE_FIFOSTAT2_get_act_rslt_in_fifo(data)                              ((0xF8000000&(data))>>27)
#define RIF_REG_VE_FIFOSTAT2_rslt_fifo_cnt_shift                                     (22)
#define RIF_REG_VE_FIFOSTAT2_rslt_fifo_cnt_mask                                      (0x07C00000)
#define RIF_REG_VE_FIFOSTAT2_rslt_fifo_cnt(data)                                     (0x07C00000&((data)<<22))
#define RIF_REG_VE_FIFOSTAT2_rslt_fifo_cnt_src(data)                                 ((0x07C00000&(data))>>22)
#define RIF_REG_VE_FIFOSTAT2_get_rslt_fifo_cnt(data)                                 ((0x07C00000&(data))>>22)
#define RIF_REG_VE_FIFOSTAT2_img_fifo_cnt_shift                                      (16)
#define RIF_REG_VE_FIFOSTAT2_img_fifo_cnt_mask                                       (0x003F0000)
#define RIF_REG_VE_FIFOSTAT2_img_fifo_cnt(data)                                      (0x003F0000&((data)<<16))
#define RIF_REG_VE_FIFOSTAT2_img_fifo_cnt_src(data)                                  ((0x003F0000&(data))>>16)
#define RIF_REG_VE_FIFOSTAT2_get_img_fifo_cnt(data)                                  ((0x003F0000&(data))>>16)
#define RIF_REG_VE_FIFOSTAT2_dec_inst_cnt_shift                                      (8)
#define RIF_REG_VE_FIFOSTAT2_dec_inst_cnt_mask                                       (0x00003F00)
#define RIF_REG_VE_FIFOSTAT2_dec_inst_cnt(data)                                      (0x00003F00&((data)<<8))
#define RIF_REG_VE_FIFOSTAT2_dec_inst_cnt_src(data)                                  ((0x00003F00&(data))>>8)
#define RIF_REG_VE_FIFOSTAT2_get_dec_inst_cnt(data)                                  ((0x00003F00&(data))>>8)


#define RIF_REG_VE_RSLT_TIMER                                                        0x1800E418
#define RIF_REG_VE_RSLT_TIMER_reg_addr                                               "0xB800E418"
#define RIF_REG_VE_RSLT_TIMER_reg                                                    0xB800E418
#define set_RIF_REG_VE_RSLT_TIMER_reg(data)   (*((volatile unsigned int*) RIF_REG_VE_RSLT_TIMER_reg)=data)
#define get_RIF_REG_VE_RSLT_TIMER_reg   (*((volatile unsigned int*) RIF_REG_VE_RSLT_TIMER_reg))
#define RIF_REG_VE_RSLT_TIMER_inst_adr                                               "0x0006"
#define RIF_REG_VE_RSLT_TIMER_inst                                                   0x0006
#define RIF_REG_VE_RSLT_TIMER_rslt_timer_shift                                       (0)
#define RIF_REG_VE_RSLT_TIMER_rslt_timer_mask                                        (0x00FFFFFF)
#define RIF_REG_VE_RSLT_TIMER_rslt_timer(data)                                       (0x00FFFFFF&((data)<<0))
#define RIF_REG_VE_RSLT_TIMER_rslt_timer_src(data)                                   ((0x00FFFFFF&(data))>>0)
#define RIF_REG_VE_RSLT_TIMER_get_rslt_timer(data)                                   ((0x00FFFFFF&(data))>>0)


#define RIF_REG_VE_CMD_TIMER                                                         0x1800E41C
#define RIF_REG_VE_CMD_TIMER_reg_addr                                                "0xB800E41C"
#define RIF_REG_VE_CMD_TIMER_reg                                                     0xB800E41C
#define set_RIF_REG_VE_CMD_TIMER_reg(data)   (*((volatile unsigned int*) RIF_REG_VE_CMD_TIMER_reg)=data)
#define get_RIF_REG_VE_CMD_TIMER_reg   (*((volatile unsigned int*) RIF_REG_VE_CMD_TIMER_reg))
#define RIF_REG_VE_CMD_TIMER_inst_adr                                                "0x0007"
#define RIF_REG_VE_CMD_TIMER_inst                                                    0x0007
#define RIF_REG_VE_CMD_TIMER_cmd_timer_shift                                         (0)
#define RIF_REG_VE_CMD_TIMER_cmd_timer_mask                                          (0x00FFFFFF)
#define RIF_REG_VE_CMD_TIMER_cmd_timer(data)                                         (0x00FFFFFF&((data)<<0))
#define RIF_REG_VE_CMD_TIMER_cmd_timer_src(data)                                     ((0x00FFFFFF&(data))>>0)
#define RIF_REG_VE_CMD_TIMER_get_cmd_timer(data)                                     ((0x00FFFFFF&(data))>>0)


#define RIF_REG_VMBANKSEL                                                            0x1800E420
#define RIF_REG_VMBANKSEL_reg_addr                                                   "0xB800E420"
#define RIF_REG_VMBANKSEL_reg                                                        0xB800E420
#define set_RIF_REG_VMBANKSEL_reg(data)   (*((volatile unsigned int*) RIF_REG_VMBANKSEL_reg)=data)
#define get_RIF_REG_VMBANKSEL_reg   (*((volatile unsigned int*) RIF_REG_VMBANKSEL_reg))
#define RIF_REG_VMBANKSEL_inst_adr                                                   "0x0008"
#define RIF_REG_VMBANKSEL_inst                                                       0x0008
#define RIF_REG_VMBANKSEL_ve_img_bnk_shift                                           (16)
#define RIF_REG_VMBANKSEL_ve_img_bnk_mask                                            (0x00070000)
#define RIF_REG_VMBANKSEL_ve_img_bnk(data)                                           (0x00070000&((data)<<16))
#define RIF_REG_VMBANKSEL_ve_img_bnk_src(data)                                       ((0x00070000&(data))>>16)
#define RIF_REG_VMBANKSEL_get_ve_img_bnk(data)                                       ((0x00070000&(data))>>16)
#define RIF_REG_VMBANKSEL_ve_deb_bnk_shift                                           (12)
#define RIF_REG_VMBANKSEL_ve_deb_bnk_mask                                            (0x00007000)
#define RIF_REG_VMBANKSEL_ve_deb_bnk(data)                                           (0x00007000&((data)<<12))
#define RIF_REG_VMBANKSEL_ve_deb_bnk_src(data)                                       ((0x00007000&(data))>>12)
#define RIF_REG_VMBANKSEL_get_ve_deb_bnk(data)                                       ((0x00007000&(data))>>12)
#define RIF_REG_VMBANKSEL_ve_prd_bnk_shift                                           (8)
#define RIF_REG_VMBANKSEL_ve_prd_bnk_mask                                            (0x00000700)
#define RIF_REG_VMBANKSEL_ve_prd_bnk(data)                                           (0x00000700&((data)<<8))
#define RIF_REG_VMBANKSEL_ve_prd_bnk_src(data)                                       ((0x00000700&(data))>>8)
#define RIF_REG_VMBANKSEL_get_ve_prd_bnk(data)                                       ((0x00000700&(data))>>8)
#define RIF_REG_VMBANKSEL_ve_dmaa_bnk_shift                                          (0)
#define RIF_REG_VMBANKSEL_ve_dmaa_bnk_mask                                           (0x00000007)
#define RIF_REG_VMBANKSEL_ve_dmaa_bnk(data)                                          (0x00000007&((data)<<0))
#define RIF_REG_VMBANKSEL_ve_dmaa_bnk_src(data)                                      ((0x00000007&(data))>>0)
#define RIF_REG_VMBANKSEL_get_ve_dmaa_bnk(data)                                      ((0x00000007&(data))>>0)


#define RIF_REG_DEC_CNTL                                                             0x1800E450
#define RIF_REG_DEC_CNTL_reg_addr                                                    "0xB800E450"
#define RIF_REG_DEC_CNTL_reg                                                         0xB800E450
#define set_RIF_REG_DEC_CNTL_reg(data)   (*((volatile unsigned int*) RIF_REG_DEC_CNTL_reg)=data)
#define get_RIF_REG_DEC_CNTL_reg   (*((volatile unsigned int*) RIF_REG_DEC_CNTL_reg))
#define RIF_REG_DEC_CNTL_inst_adr                                                    "0x0014"
#define RIF_REG_DEC_CNTL_inst                                                        0x0014
#define RIF_REG_DEC_CNTL_monochrome_shift                                            (7)
#define RIF_REG_DEC_CNTL_monochrome_mask                                             (0x00000080)
#define RIF_REG_DEC_CNTL_monochrome(data)                                            (0x00000080&((data)<<7))
#define RIF_REG_DEC_CNTL_monochrome_src(data)                                        ((0x00000080&(data))>>7)
#define RIF_REG_DEC_CNTL_get_monochrome(data)                                        ((0x00000080&(data))>>7)
#define RIF_REG_DEC_CNTL_level_shift                                                 (6)
#define RIF_REG_DEC_CNTL_level_mask                                                  (0x00000040)
#define RIF_REG_DEC_CNTL_level(data)                                                 (0x00000040&((data)<<6))
#define RIF_REG_DEC_CNTL_level_src(data)                                             ((0x00000040&(data))>>6)
#define RIF_REG_DEC_CNTL_get_level(data)                                             ((0x00000040&(data))>>6)
#define RIF_REG_DEC_CNTL_profile_shift                                               (4)
#define RIF_REG_DEC_CNTL_profile_mask                                                (0x00000030)
#define RIF_REG_DEC_CNTL_profile(data)                                               (0x00000030&((data)<<4))
#define RIF_REG_DEC_CNTL_profile_src(data)                                           ((0x00000030&(data))>>4)
#define RIF_REG_DEC_CNTL_get_profile(data)                                           ((0x00000030&(data))>>4)
#define RIF_REG_DEC_CNTL_coding_type_shift                                           (0)
#define RIF_REG_DEC_CNTL_coding_type_mask                                            (0x0000000F)
#define RIF_REG_DEC_CNTL_coding_type(data)                                           (0x0000000F&((data)<<0))
#define RIF_REG_DEC_CNTL_coding_type_src(data)                                       ((0x0000000F&(data))>>0)
#define RIF_REG_DEC_CNTL_get_coding_type(data)                                       ((0x0000000F&(data))>>0)


#define RIF_REG_PICINFO1                                                             0x1800E454
#define RIF_REG_PICINFO1_reg_addr                                                    "0xB800E454"
#define RIF_REG_PICINFO1_reg                                                         0xB800E454
#define set_RIF_REG_PICINFO1_reg(data)   (*((volatile unsigned int*) RIF_REG_PICINFO1_reg)=data)
#define get_RIF_REG_PICINFO1_reg   (*((volatile unsigned int*) RIF_REG_PICINFO1_reg))
#define RIF_REG_PICINFO1_inst_adr                                                    "0x0015"
#define RIF_REG_PICINFO1_inst                                                        0x0015
#define RIF_REG_PICINFO1_vp8_bicubic_filtering_shift                                 (16)
#define RIF_REG_PICINFO1_vp8_bicubic_filtering_mask                                  (0x00010000)
#define RIF_REG_PICINFO1_vp8_bicubic_filtering(data)                                 (0x00010000&((data)<<16))
#define RIF_REG_PICINFO1_vp8_bicubic_filtering_src(data)                             ((0x00010000&(data))>>16)
#define RIF_REG_PICINFO1_get_vp8_bicubic_filtering(data)                             ((0x00010000&(data))>>16)
#define RIF_REG_PICINFO1_bottom_field_flag_shift                                     (15)
#define RIF_REG_PICINFO1_bottom_field_flag_mask                                      (0x00008000)
#define RIF_REG_PICINFO1_bottom_field_flag(data)                                     (0x00008000&((data)<<15))
#define RIF_REG_PICINFO1_bottom_field_flag_src(data)                                 ((0x00008000&(data))>>15)
#define RIF_REG_PICINFO1_get_bottom_field_flag(data)                                 ((0x00008000&(data))>>15)
#define RIF_REG_PICINFO1_field_pic_flag_shift                                        (14)
#define RIF_REG_PICINFO1_field_pic_flag_mask                                         (0x00004000)
#define RIF_REG_PICINFO1_field_pic_flag(data)                                        (0x00004000&((data)<<14))
#define RIF_REG_PICINFO1_field_pic_flag_src(data)                                    ((0x00004000&(data))>>14)
#define RIF_REG_PICINFO1_get_field_pic_flag(data)                                    ((0x00004000&(data))>>14)
#define RIF_REG_PICINFO1_picmb_h_shift                                               (7)
#define RIF_REG_PICINFO1_picmb_h_mask                                                (0x00003F80)
#define RIF_REG_PICINFO1_picmb_h(data)                                               (0x00003F80&((data)<<7))
#define RIF_REG_PICINFO1_picmb_h_src(data)                                           ((0x00003F80&(data))>>7)
#define RIF_REG_PICINFO1_get_picmb_h(data)                                           ((0x00003F80&(data))>>7)
#define RIF_REG_PICINFO1_picmb_w_shift                                               (0)
#define RIF_REG_PICINFO1_picmb_w_mask                                                (0x0000007F)
#define RIF_REG_PICINFO1_picmb_w(data)                                               (0x0000007F&((data)<<0))
#define RIF_REG_PICINFO1_picmb_w_src(data)                                           ((0x0000007F&(data))>>0)
#define RIF_REG_PICINFO1_get_picmb_w(data)                                           ((0x0000007F&(data))>>0)


#define RIF_REG_H264PICCNTL                                                          0x1800E460
#define RIF_REG_H264PICCNTL_reg_addr                                                 "0xB800E460"
#define RIF_REG_H264PICCNTL_reg                                                      0xB800E460
#define set_RIF_REG_H264PICCNTL_reg(data)   (*((volatile unsigned int*) RIF_REG_H264PICCNTL_reg)=data)
#define get_RIF_REG_H264PICCNTL_reg   (*((volatile unsigned int*) RIF_REG_H264PICCNTL_reg))
#define RIF_REG_H264PICCNTL_inst_adr                                                 "0x0018"
#define RIF_REG_H264PICCNTL_inst                                                     0x0018
#define RIF_REG_H264PICCNTL_Constrainted_intra_pred_flag_shift                       (5)
#define RIF_REG_H264PICCNTL_Constrainted_intra_pred_flag_mask                        (0x00000020)
#define RIF_REG_H264PICCNTL_Constrainted_intra_pred_flag(data)                       (0x00000020&((data)<<5))
#define RIF_REG_H264PICCNTL_Constrainted_intra_pred_flag_src(data)                   ((0x00000020&(data))>>5)
#define RIF_REG_H264PICCNTL_get_Constrainted_intra_pred_flag(data)                   ((0x00000020&(data))>>5)
#define RIF_REG_H264PICCNTL_Weighted_pred_flag_shift                                 (4)
#define RIF_REG_H264PICCNTL_Weighted_pred_flag_mask                                  (0x00000010)
#define RIF_REG_H264PICCNTL_Weighted_pred_flag(data)                                 (0x00000010&((data)<<4))
#define RIF_REG_H264PICCNTL_Weighted_pred_flag_src(data)                             ((0x00000010&(data))>>4)
#define RIF_REG_H264PICCNTL_get_Weighted_pred_flag(data)                             ((0x00000010&(data))>>4)
#define RIF_REG_H264PICCNTL_Weighted_bipred_idc_shift                                (2)
#define RIF_REG_H264PICCNTL_Weighted_bipred_idc_mask                                 (0x0000000C)
#define RIF_REG_H264PICCNTL_Weighted_bipred_idc(data)                                (0x0000000C&((data)<<2))
#define RIF_REG_H264PICCNTL_Weighted_bipred_idc_src(data)                            ((0x0000000C&(data))>>2)
#define RIF_REG_H264PICCNTL_get_Weighted_bipred_idc(data)                            ((0x0000000C&(data))>>2)
#define RIF_REG_H264PICCNTL_frame_mbs_only_flag_shift                                (1)
#define RIF_REG_H264PICCNTL_frame_mbs_only_flag_mask                                 (0x00000002)
#define RIF_REG_H264PICCNTL_frame_mbs_only_flag(data)                                (0x00000002&((data)<<1))
#define RIF_REG_H264PICCNTL_frame_mbs_only_flag_src(data)                            ((0x00000002&(data))>>1)
#define RIF_REG_H264PICCNTL_get_frame_mbs_only_flag(data)                            ((0x00000002&(data))>>1)
#define RIF_REG_H264PICCNTL_mb_adaptive_frame_field_flag_shift                       (0)
#define RIF_REG_H264PICCNTL_mb_adaptive_frame_field_flag_mask                        (0x00000001)
#define RIF_REG_H264PICCNTL_mb_adaptive_frame_field_flag(data)                       (0x00000001&((data)<<0))
#define RIF_REG_H264PICCNTL_mb_adaptive_frame_field_flag_src(data)                   ((0x00000001&(data))>>0)
#define RIF_REG_H264PICCNTL_get_mb_adaptive_frame_field_flag(data)                   ((0x00000001&(data))>>0)


#define RIF_REG_VC1PICCNTL                                                           0x1800E470
#define RIF_REG_VC1PICCNTL_reg_addr                                                  "0xB800E470"
#define RIF_REG_VC1PICCNTL_reg                                                       0xB800E470
#define set_RIF_REG_VC1PICCNTL_reg(data)   (*((volatile unsigned int*) RIF_REG_VC1PICCNTL_reg)=data)
#define get_RIF_REG_VC1PICCNTL_reg   (*((volatile unsigned int*) RIF_REG_VC1PICCNTL_reg))
#define RIF_REG_VC1PICCNTL_inst_adr                                                  "0x001C"
#define RIF_REG_VC1PICCNTL_inst                                                      0x001C
#define RIF_REG_VC1PICCNTL_Overlap_enable_shift                                      (31)
#define RIF_REG_VC1PICCNTL_Overlap_enable_mask                                       (0x80000000)
#define RIF_REG_VC1PICCNTL_Overlap_enable(data)                                      (0x80000000&((data)<<31))
#define RIF_REG_VC1PICCNTL_Overlap_enable_src(data)                                  ((0x80000000&(data))>>31)
#define RIF_REG_VC1PICCNTL_get_Overlap_enable(data)                                  ((0x80000000&(data))>>31)
#define RIF_REG_VC1PICCNTL_field_pictype_shift                                       (28)
#define RIF_REG_VC1PICCNTL_field_pictype_mask                                        (0x70000000)
#define RIF_REG_VC1PICCNTL_field_pictype(data)                                       (0x70000000&((data)<<28))
#define RIF_REG_VC1PICCNTL_field_pictype_src(data)                                   ((0x70000000&(data))>>28)
#define RIF_REG_VC1PICCNTL_get_field_pictype(data)                                   ((0x70000000&(data))>>28)
#define RIF_REG_VC1PICCNTL_mvmode_shift                                              (26)
#define RIF_REG_VC1PICCNTL_mvmode_mask                                               (0x0C000000)
#define RIF_REG_VC1PICCNTL_mvmode(data)                                              (0x0C000000&((data)<<26))
#define RIF_REG_VC1PICCNTL_mvmode_src(data)                                          ((0x0C000000&(data))>>26)
#define RIF_REG_VC1PICCNTL_get_mvmode(data)                                          ((0x0C000000&(data))>>26)
#define RIF_REG_VC1PICCNTL_fcm_shift                                                 (24)
#define RIF_REG_VC1PICCNTL_fcm_mask                                                  (0x03000000)
#define RIF_REG_VC1PICCNTL_fcm(data)                                                 (0x03000000&((data)<<24))
#define RIF_REG_VC1PICCNTL_fcm_src(data)                                             ((0x03000000&(data))>>24)
#define RIF_REG_VC1PICCNTL_get_fcm(data)                                             ((0x03000000&(data))>>24)
#define RIF_REG_VC1PICCNTL_disppic_h_shift                                           (12)
#define RIF_REG_VC1PICCNTL_disppic_h_mask                                            (0x00FFF000)
#define RIF_REG_VC1PICCNTL_disppic_h(data)                                           (0x00FFF000&((data)<<12))
#define RIF_REG_VC1PICCNTL_disppic_h_src(data)                                       ((0x00FFF000&(data))>>12)
#define RIF_REG_VC1PICCNTL_get_disppic_h(data)                                       ((0x00FFF000&(data))>>12)
#define RIF_REG_VC1PICCNTL_disppic_w_shift                                           (0)
#define RIF_REG_VC1PICCNTL_disppic_w_mask                                            (0x00000FFF)
#define RIF_REG_VC1PICCNTL_disppic_w(data)                                           (0x00000FFF&((data)<<0))
#define RIF_REG_VC1PICCNTL_disppic_w_src(data)                                       ((0x00000FFF&(data))>>0)
#define RIF_REG_VC1PICCNTL_get_disppic_w(data)                                       ((0x00000FFF&(data))>>0)


#define RIF_REG_VC1PICCNTL2                                                          0x1800E474
#define RIF_REG_VC1PICCNTL2_reg_addr                                                 "0xB800E474"
#define RIF_REG_VC1PICCNTL2_reg                                                      0xB800E474
#define set_RIF_REG_VC1PICCNTL2_reg(data)   (*((volatile unsigned int*) RIF_REG_VC1PICCNTL2_reg)=data)
#define get_RIF_REG_VC1PICCNTL2_reg   (*((volatile unsigned int*) RIF_REG_VC1PICCNTL2_reg))
#define RIF_REG_VC1PICCNTL2_inst_adr                                                 "0x001D"
#define RIF_REG_VC1PICCNTL2_inst                                                     0x001D
#define RIF_REG_VC1PICCNTL2_wmv9_bug_rtmflag_shift                                   (8)
#define RIF_REG_VC1PICCNTL2_wmv9_bug_rtmflag_mask                                    (0x00000100)
#define RIF_REG_VC1PICCNTL2_wmv9_bug_rtmflag(data)                                   (0x00000100&((data)<<8))
#define RIF_REG_VC1PICCNTL2_wmv9_bug_rtmflag_src(data)                               ((0x00000100&(data))>>8)
#define RIF_REG_VC1PICCNTL2_get_wmv9_bug_rtmflag(data)                               ((0x00000100&(data))>>8)
#define RIF_REG_VC1PICCNTL2_wmv9_bug_it_shift                                        (7)
#define RIF_REG_VC1PICCNTL2_wmv9_bug_it_mask                                         (0x00000080)
#define RIF_REG_VC1PICCNTL2_wmv9_bug_it(data)                                        (0x00000080&((data)<<7))
#define RIF_REG_VC1PICCNTL2_wmv9_bug_it_src(data)                                    ((0x00000080&(data))>>7)
#define RIF_REG_VC1PICCNTL2_get_wmv9_bug_it(data)                                    ((0x00000080&(data))>>7)
#define RIF_REG_VC1PICCNTL2_loopfilter_shift                                         (6)
#define RIF_REG_VC1PICCNTL2_loopfilter_mask                                          (0x00000040)
#define RIF_REG_VC1PICCNTL2_loopfilter(data)                                         (0x00000040&((data)<<6))
#define RIF_REG_VC1PICCNTL2_loopfilter_src(data)                                     ((0x00000040&(data))>>6)
#define RIF_REG_VC1PICCNTL2_get_loopfilter(data)                                     ((0x00000040&(data))>>6)
#define RIF_REG_VC1PICCNTL2_numref_shift                                             (5)
#define RIF_REG_VC1PICCNTL2_numref_mask                                              (0x00000020)
#define RIF_REG_VC1PICCNTL2_numref(data)                                             (0x00000020&((data)<<5))
#define RIF_REG_VC1PICCNTL2_numref_src(data)                                         ((0x00000020&(data))>>5)
#define RIF_REG_VC1PICCNTL2_get_numref(data)                                         ((0x00000020&(data))>>5)
#define RIF_REG_VC1PICCNTL2_pquant_shift                                             (0)
#define RIF_REG_VC1PICCNTL2_pquant_mask                                              (0x0000001F)
#define RIF_REG_VC1PICCNTL2_pquant(data)                                             (0x0000001F&((data)<<0))
#define RIF_REG_VC1PICCNTL2_pquant_src(data)                                         ((0x0000001F&(data))>>0)
#define RIF_REG_VC1PICCNTL2_get_pquant(data)                                         ((0x0000001F&(data))>>0)


#define RIF_REG_BRG_CTRL                                                             0x1800E490
#define RIF_REG_BRG_CTRL_reg_addr                                                    "0xB800E490"
#define RIF_REG_BRG_CTRL_reg                                                         0xB800E490
#define set_RIF_REG_BRG_CTRL_reg(data)   (*((volatile unsigned int*) RIF_REG_BRG_CTRL_reg)=data)
#define get_RIF_REG_BRG_CTRL_reg   (*((volatile unsigned int*) RIF_REG_BRG_CTRL_reg))
#define RIF_REG_BRG_CTRL_inst_adr                                                    "0x0024"
#define RIF_REG_BRG_CTRL_inst                                                        0x0024
#define RIF_REG_BRG_CTRL_priority_thd2_shift                                         (16)
#define RIF_REG_BRG_CTRL_priority_thd2_mask                                          (0x00FF0000)
#define RIF_REG_BRG_CTRL_priority_thd2(data)                                         (0x00FF0000&((data)<<16))
#define RIF_REG_BRG_CTRL_priority_thd2_src(data)                                     ((0x00FF0000&(data))>>16)
#define RIF_REG_BRG_CTRL_get_priority_thd2(data)                                     ((0x00FF0000&(data))>>16)
#define RIF_REG_BRG_CTRL_priority_thd1_shift                                         (8)
#define RIF_REG_BRG_CTRL_priority_thd1_mask                                          (0x0000FF00)
#define RIF_REG_BRG_CTRL_priority_thd1(data)                                         (0x0000FF00&((data)<<8))
#define RIF_REG_BRG_CTRL_priority_thd1_src(data)                                     ((0x0000FF00&(data))>>8)
#define RIF_REG_BRG_CTRL_get_priority_thd1(data)                                     ((0x0000FF00&(data))>>8)
#define RIF_REG_BRG_CTRL_srg_mode_shift                                              (3)
#define RIF_REG_BRG_CTRL_srg_mode_mask                                               (0x00000008)
#define RIF_REG_BRG_CTRL_srg_mode(data)                                              (0x00000008&((data)<<3))
#define RIF_REG_BRG_CTRL_srg_mode_src(data)                                          ((0x00000008&(data))>>3)
#define RIF_REG_BRG_CTRL_get_srg_mode(data)                                          ((0x00000008&(data))>>3)
#define RIF_REG_BRG_CTRL_ddr_page_shift                                              (1)
#define RIF_REG_BRG_CTRL_ddr_page_mask                                               (0x00000006)
#define RIF_REG_BRG_CTRL_ddr_page(data)                                              (0x00000006&((data)<<1))
#define RIF_REG_BRG_CTRL_ddr_page_src(data)                                          ((0x00000006&(data))>>1)
#define RIF_REG_BRG_CTRL_get_ddr_page(data)                                          ((0x00000006&(data))>>1)
#define RIF_REG_BRG_CTRL_srg_enable_shift                                            (0)
#define RIF_REG_BRG_CTRL_srg_enable_mask                                             (0x00000001)
#define RIF_REG_BRG_CTRL_srg_enable(data)                                            (0x00000001&((data)<<0))
#define RIF_REG_BRG_CTRL_srg_enable_src(data)                                        ((0x00000001&(data))>>0)
#define RIF_REG_BRG_CTRL_get_srg_enable(data)                                        ((0x00000001&(data))>>0)


#define RIF_REG_RD_PRIORITY0                                                         0x1800E494
#define RIF_REG_RD_PRIORITY0_reg_addr                                                "0xB800E494"
#define RIF_REG_RD_PRIORITY0_reg                                                     0xB800E494
#define set_RIF_REG_RD_PRIORITY0_reg(data)   (*((volatile unsigned int*) RIF_REG_RD_PRIORITY0_reg)=data)
#define get_RIF_REG_RD_PRIORITY0_reg   (*((volatile unsigned int*) RIF_REG_RD_PRIORITY0_reg))
#define RIF_REG_RD_PRIORITY0_inst_adr                                                "0x0025"
#define RIF_REG_RD_PRIORITY0_inst                                                    0x0025
#define RIF_REG_RD_PRIORITY0_vm1_shift                                               (0)
#define RIF_REG_RD_PRIORITY0_vm1_mask                                                (0x000000FF)
#define RIF_REG_RD_PRIORITY0_vm1(data)                                               (0x000000FF&((data)<<0))
#define RIF_REG_RD_PRIORITY0_vm1_src(data)                                           ((0x000000FF&(data))>>0)
#define RIF_REG_RD_PRIORITY0_get_vm1(data)                                           ((0x000000FF&(data))>>0)


#define RIF_REG_RD_PRIORITY1                                                         0x1800E498
#define RIF_REG_RD_PRIORITY1_reg_addr                                                "0xB800E498"
#define RIF_REG_RD_PRIORITY1_reg                                                     0xB800E498
#define set_RIF_REG_RD_PRIORITY1_reg(data)   (*((volatile unsigned int*) RIF_REG_RD_PRIORITY1_reg)=data)
#define get_RIF_REG_RD_PRIORITY1_reg   (*((volatile unsigned int*) RIF_REG_RD_PRIORITY1_reg))
#define RIF_REG_RD_PRIORITY1_inst_adr                                                "0x0026"
#define RIF_REG_RD_PRIORITY1_inst                                                    0x0026
#define RIF_REG_RD_PRIORITY1_deblk_shift                                             (16)
#define RIF_REG_RD_PRIORITY1_deblk_mask                                              (0x00FF0000)
#define RIF_REG_RD_PRIORITY1_deblk(data)                                             (0x00FF0000&((data)<<16))
#define RIF_REG_RD_PRIORITY1_deblk_src(data)                                         ((0x00FF0000&(data))>>16)
#define RIF_REG_RD_PRIORITY1_get_deblk(data)                                         ((0x00FF0000&(data))>>16)
#define RIF_REG_RD_PRIORITY1_predblk_shift                                           (0)
#define RIF_REG_RD_PRIORITY1_predblk_mask                                            (0x000000FF)
#define RIF_REG_RD_PRIORITY1_predblk(data)                                           (0x000000FF&((data)<<0))
#define RIF_REG_RD_PRIORITY1_predblk_src(data)                                       ((0x000000FF&(data))>>0)
#define RIF_REG_RD_PRIORITY1_get_predblk(data)                                       ((0x000000FF&(data))>>0)


#define RIF_REG_RD_PRIORITY2                                                         0x1800E49C
#define RIF_REG_RD_PRIORITY2_reg_addr                                                "0xB800E49C"
#define RIF_REG_RD_PRIORITY2_reg                                                     0xB800E49C
#define set_RIF_REG_RD_PRIORITY2_reg(data)   (*((volatile unsigned int*) RIF_REG_RD_PRIORITY2_reg)=data)
#define get_RIF_REG_RD_PRIORITY2_reg   (*((volatile unsigned int*) RIF_REG_RD_PRIORITY2_reg))
#define RIF_REG_RD_PRIORITY2_inst_adr                                                "0x0027"
#define RIF_REG_RD_PRIORITY2_inst                                                    0x0027
#define RIF_REG_RD_PRIORITY2_nm_shift                                                (16)
#define RIF_REG_RD_PRIORITY2_nm_mask                                                 (0x00FF0000)
#define RIF_REG_RD_PRIORITY2_nm(data)                                                (0x00FF0000&((data)<<16))
#define RIF_REG_RD_PRIORITY2_nm_src(data)                                            ((0x00FF0000&(data))>>16)
#define RIF_REG_RD_PRIORITY2_get_nm(data)                                            ((0x00FF0000&(data))>>16)
#define RIF_REG_RD_PRIORITY2_mvd_shift                                               (0)
#define RIF_REG_RD_PRIORITY2_mvd_mask                                                (0x000000FF)
#define RIF_REG_RD_PRIORITY2_mvd(data)                                               (0x000000FF&((data)<<0))
#define RIF_REG_RD_PRIORITY2_mvd_src(data)                                           ((0x000000FF&(data))>>0)
#define RIF_REG_RD_PRIORITY2_get_mvd(data)                                           ((0x000000FF&(data))>>0)


#define RIF_REG_RD_PRIORITY3                                                         0x1800E4A0
#define RIF_REG_RD_PRIORITY3_reg_addr                                                "0xB800E4A0"
#define RIF_REG_RD_PRIORITY3_reg                                                     0xB800E4A0
#define set_RIF_REG_RD_PRIORITY3_reg(data)   (*((volatile unsigned int*) RIF_REG_RD_PRIORITY3_reg)=data)
#define get_RIF_REG_RD_PRIORITY3_reg   (*((volatile unsigned int*) RIF_REG_RD_PRIORITY3_reg))
#define RIF_REG_RD_PRIORITY3_inst_adr                                                "0x0028"
#define RIF_REG_RD_PRIORITY3_inst                                                    0x0028
#define RIF_REG_RD_PRIORITY3_bs_shift                                                (0)
#define RIF_REG_RD_PRIORITY3_bs_mask                                                 (0x000000FF)
#define RIF_REG_RD_PRIORITY3_bs(data)                                                (0x000000FF&((data)<<0))
#define RIF_REG_RD_PRIORITY3_bs_src(data)                                            ((0x000000FF&(data))>>0)
#define RIF_REG_RD_PRIORITY3_get_bs(data)                                            ((0x000000FF&(data))>>0)


#define RIF_REG_RD_PRIORITY4                                                         0x1800E4A4
#define RIF_REG_RD_PRIORITY4_reg_addr                                                "0xB800E4A4"
#define RIF_REG_RD_PRIORITY4_reg                                                     0xB800E4A4
#define set_RIF_REG_RD_PRIORITY4_reg(data)   (*((volatile unsigned int*) RIF_REG_RD_PRIORITY4_reg)=data)
#define get_RIF_REG_RD_PRIORITY4_reg   (*((volatile unsigned int*) RIF_REG_RD_PRIORITY4_reg))
#define RIF_REG_RD_PRIORITY4_inst_adr                                                "0x0029"
#define RIF_REG_RD_PRIORITY4_inst                                                    0x0029
#define RIF_REG_RD_PRIORITY4_rl_shift                                                (0)
#define RIF_REG_RD_PRIORITY4_rl_mask                                                 (0x000000FF)
#define RIF_REG_RD_PRIORITY4_rl(data)                                                (0x000000FF&((data)<<0))
#define RIF_REG_RD_PRIORITY4_rl_src(data)                                            ((0x000000FF&(data))>>0)
#define RIF_REG_RD_PRIORITY4_get_rl(data)                                            ((0x000000FF&(data))>>0)


#define RIF_REG_WT_PRIORITY0                                                         0x1800E4B0
#define RIF_REG_WT_PRIORITY0_reg_addr                                                "0xB800E4B0"
#define RIF_REG_WT_PRIORITY0_reg                                                     0xB800E4B0
#define set_RIF_REG_WT_PRIORITY0_reg(data)   (*((volatile unsigned int*) RIF_REG_WT_PRIORITY0_reg)=data)
#define get_RIF_REG_WT_PRIORITY0_reg   (*((volatile unsigned int*) RIF_REG_WT_PRIORITY0_reg))
#define RIF_REG_WT_PRIORITY0_inst_adr                                                "0x002C"
#define RIF_REG_WT_PRIORITY0_inst                                                    0x002C
#define RIF_REG_WT_PRIORITY0_vm1_shift                                               (0)
#define RIF_REG_WT_PRIORITY0_vm1_mask                                                (0x000000FF)
#define RIF_REG_WT_PRIORITY0_vm1(data)                                               (0x000000FF&((data)<<0))
#define RIF_REG_WT_PRIORITY0_vm1_src(data)                                           ((0x000000FF&(data))>>0)
#define RIF_REG_WT_PRIORITY0_get_vm1(data)                                           ((0x000000FF&(data))>>0)


#define RIF_REG_WT_PRIORITY1                                                         0x1800E4B4
#define RIF_REG_WT_PRIORITY1_reg_addr                                                "0xB800E4B4"
#define RIF_REG_WT_PRIORITY1_reg                                                     0xB800E4B4
#define set_RIF_REG_WT_PRIORITY1_reg(data)   (*((volatile unsigned int*) RIF_REG_WT_PRIORITY1_reg)=data)
#define get_RIF_REG_WT_PRIORITY1_reg   (*((volatile unsigned int*) RIF_REG_WT_PRIORITY1_reg))
#define RIF_REG_WT_PRIORITY1_inst_adr                                                "0x002D"
#define RIF_REG_WT_PRIORITY1_inst                                                    0x002D
#define RIF_REG_WT_PRIORITY1_deblk_shift                                             (16)
#define RIF_REG_WT_PRIORITY1_deblk_mask                                              (0x00FF0000)
#define RIF_REG_WT_PRIORITY1_deblk(data)                                             (0x00FF0000&((data)<<16))
#define RIF_REG_WT_PRIORITY1_deblk_src(data)                                         ((0x00FF0000&(data))>>16)
#define RIF_REG_WT_PRIORITY1_get_deblk(data)                                         ((0x00FF0000&(data))>>16)
#define RIF_REG_WT_PRIORITY1_predblk_shift                                           (0)
#define RIF_REG_WT_PRIORITY1_predblk_mask                                            (0x000000FF)
#define RIF_REG_WT_PRIORITY1_predblk(data)                                           (0x000000FF&((data)<<0))
#define RIF_REG_WT_PRIORITY1_predblk_src(data)                                       ((0x000000FF&(data))>>0)
#define RIF_REG_WT_PRIORITY1_get_predblk(data)                                       ((0x000000FF&(data))>>0)


#define RIF_REG_WT_PRIORITY2                                                         0x1800E4B8
#define RIF_REG_WT_PRIORITY2_reg_addr                                                "0xB800E4B8"
#define RIF_REG_WT_PRIORITY2_reg                                                     0xB800E4B8
#define set_RIF_REG_WT_PRIORITY2_reg(data)   (*((volatile unsigned int*) RIF_REG_WT_PRIORITY2_reg)=data)
#define get_RIF_REG_WT_PRIORITY2_reg   (*((volatile unsigned int*) RIF_REG_WT_PRIORITY2_reg))
#define RIF_REG_WT_PRIORITY2_inst_adr                                                "0x002E"
#define RIF_REG_WT_PRIORITY2_inst                                                    0x002E
#define RIF_REG_WT_PRIORITY2_nm_shift                                                (16)
#define RIF_REG_WT_PRIORITY2_nm_mask                                                 (0x00FF0000)
#define RIF_REG_WT_PRIORITY2_nm(data)                                                (0x00FF0000&((data)<<16))
#define RIF_REG_WT_PRIORITY2_nm_src(data)                                            ((0x00FF0000&(data))>>16)
#define RIF_REG_WT_PRIORITY2_get_nm(data)                                            ((0x00FF0000&(data))>>16)
#define RIF_REG_WT_PRIORITY2_mvd_shift                                               (0)
#define RIF_REG_WT_PRIORITY2_mvd_mask                                                (0x000000FF)
#define RIF_REG_WT_PRIORITY2_mvd(data)                                               (0x000000FF&((data)<<0))
#define RIF_REG_WT_PRIORITY2_mvd_src(data)                                           ((0x000000FF&(data))>>0)
#define RIF_REG_WT_PRIORITY2_get_mvd(data)                                           ((0x000000FF&(data))>>0)


#define RIF_REG_WT_PRIORITY3                                                         0x1800E4BC
#define RIF_REG_WT_PRIORITY3_reg_addr                                                "0xB800E4BC"
#define RIF_REG_WT_PRIORITY3_reg                                                     0xB800E4BC
#define set_RIF_REG_WT_PRIORITY3_reg(data)   (*((volatile unsigned int*) RIF_REG_WT_PRIORITY3_reg)=data)
#define get_RIF_REG_WT_PRIORITY3_reg   (*((volatile unsigned int*) RIF_REG_WT_PRIORITY3_reg))
#define RIF_REG_WT_PRIORITY3_inst_adr                                                "0x002F"
#define RIF_REG_WT_PRIORITY3_inst                                                    0x002F
#define RIF_REG_WT_PRIORITY3_bs_shift                                                (0)
#define RIF_REG_WT_PRIORITY3_bs_mask                                                 (0x000000FF)
#define RIF_REG_WT_PRIORITY3_bs(data)                                                (0x000000FF&((data)<<0))
#define RIF_REG_WT_PRIORITY3_bs_src(data)                                            ((0x000000FF&(data))>>0)
#define RIF_REG_WT_PRIORITY3_get_bs(data)                                            ((0x000000FF&(data))>>0)


#define RIF_REG_WT_PRIORITY4                                                         0x1800E4C0
#define RIF_REG_WT_PRIORITY4_reg_addr                                                "0xB800E4C0"
#define RIF_REG_WT_PRIORITY4_reg                                                     0xB800E4C0
#define set_RIF_REG_WT_PRIORITY4_reg(data)   (*((volatile unsigned int*) RIF_REG_WT_PRIORITY4_reg)=data)
#define get_RIF_REG_WT_PRIORITY4_reg   (*((volatile unsigned int*) RIF_REG_WT_PRIORITY4_reg))
#define RIF_REG_WT_PRIORITY4_inst_adr                                                "0x0030"
#define RIF_REG_WT_PRIORITY4_inst                                                    0x0030
#define RIF_REG_WT_PRIORITY4_it_shift                                                (0)
#define RIF_REG_WT_PRIORITY4_it_mask                                                 (0x000000FF)
#define RIF_REG_WT_PRIORITY4_it(data)                                                (0x000000FF&((data)<<0))
#define RIF_REG_WT_PRIORITY4_it_src(data)                                            ((0x000000FF&(data))>>0)
#define RIF_REG_WT_PRIORITY4_get_it(data)                                            ((0x000000FF&(data))>>0)


#define RIF_REG_CLKGATED                                                             0x1800E4D8
#define RIF_REG_CLKGATED_reg_addr                                                    "0xB800E4D8"
#define RIF_REG_CLKGATED_reg                                                         0xB800E4D8
#define set_RIF_REG_CLKGATED_reg(data)   (*((volatile unsigned int*) RIF_REG_CLKGATED_reg)=data)
#define get_RIF_REG_CLKGATED_reg   (*((volatile unsigned int*) RIF_REG_CLKGATED_reg))
#define RIF_REG_CLKGATED_inst_adr                                                    "0x0036"
#define RIF_REG_CLKGATED_inst                                                        0x0036
#define RIF_REG_CLKGATED_cache_gated_en_shift                                        (18)
#define RIF_REG_CLKGATED_cache_gated_en_mask                                         (0x00040000)
#define RIF_REG_CLKGATED_cache_gated_en(data)                                        (0x00040000&((data)<<18))
#define RIF_REG_CLKGATED_cache_gated_en_src(data)                                    ((0x00040000&(data))>>18)
#define RIF_REG_CLKGATED_get_cache_gated_en(data)                                    ((0x00040000&(data))>>18)
#define RIF_REG_CLKGATED_rl_gated_en_shift                                           (17)
#define RIF_REG_CLKGATED_rl_gated_en_mask                                            (0x00020000)
#define RIF_REG_CLKGATED_rl_gated_en(data)                                           (0x00020000&((data)<<17))
#define RIF_REG_CLKGATED_rl_gated_en_src(data)                                       ((0x00020000&(data))>>17)
#define RIF_REG_CLKGATED_get_rl_gated_en(data)                                       ((0x00020000&(data))>>17)
#define RIF_REG_CLKGATED_mvd_gated_en_shift                                          (16)
#define RIF_REG_CLKGATED_mvd_gated_en_mask                                           (0x00010000)
#define RIF_REG_CLKGATED_mvd_gated_en(data)                                          (0x00010000&((data)<<16))
#define RIF_REG_CLKGATED_mvd_gated_en_src(data)                                      ((0x00010000&(data))>>16)
#define RIF_REG_CLKGATED_get_mvd_gated_en(data)                                      ((0x00010000&(data))>>16)
#define RIF_REG_CLKGATED_ndbp2_gated_en_shift                                        (15)
#define RIF_REG_CLKGATED_ndbp2_gated_en_mask                                         (0x00008000)
#define RIF_REG_CLKGATED_ndbp2_gated_en(data)                                        (0x00008000&((data)<<15))
#define RIF_REG_CLKGATED_ndbp2_gated_en_src(data)                                    ((0x00008000&(data))>>15)
#define RIF_REG_CLKGATED_get_ndbp2_gated_en(data)                                    ((0x00008000&(data))>>15)
#define RIF_REG_CLKGATED_ndb_gated_en_shift                                          (14)
#define RIF_REG_CLKGATED_ndb_gated_en_mask                                           (0x00004000)
#define RIF_REG_CLKGATED_ndb_gated_en(data)                                          (0x00004000&((data)<<14))
#define RIF_REG_CLKGATED_ndb_gated_en_src(data)                                      ((0x00004000&(data))>>14)
#define RIF_REG_CLKGATED_get_ndb_gated_en(data)                                      ((0x00004000&(data))>>14)
#define RIF_REG_CLKGATED_brg_gated_en_shift                                          (13)
#define RIF_REG_CLKGATED_brg_gated_en_mask                                           (0x00002000)
#define RIF_REG_CLKGATED_brg_gated_en(data)                                          (0x00002000&((data)<<13))
#define RIF_REG_CLKGATED_brg_gated_en_src(data)                                      ((0x00002000&(data))>>13)
#define RIF_REG_CLKGATED_get_brg_gated_en(data)                                      ((0x00002000&(data))>>13)
#define RIF_REG_CLKGATED_cm_gated_en_shift                                           (12)
#define RIF_REG_CLKGATED_cm_gated_en_mask                                            (0x00001000)
#define RIF_REG_CLKGATED_cm_gated_en(data)                                           (0x00001000&((data)<<12))
#define RIF_REG_CLKGATED_cm_gated_en_src(data)                                       ((0x00001000&(data))>>12)
#define RIF_REG_CLKGATED_get_cm_gated_en(data)                                       ((0x00001000&(data))>>12)
#define RIF_REG_CLKGATED_arb_gated_en_shift                                          (11)
#define RIF_REG_CLKGATED_arb_gated_en_mask                                           (0x00000800)
#define RIF_REG_CLKGATED_arb_gated_en(data)                                          (0x00000800&((data)<<11))
#define RIF_REG_CLKGATED_arb_gated_en_src(data)                                      ((0x00000800&(data))>>11)
#define RIF_REG_CLKGATED_get_arb_gated_en(data)                                      ((0x00000800&(data))>>11)
#define RIF_REG_CLKGATED_bsfifop2_gated_en_shift                                     (10)
#define RIF_REG_CLKGATED_bsfifop2_gated_en_mask                                      (0x00000400)
#define RIF_REG_CLKGATED_bsfifop2_gated_en(data)                                     (0x00000400&((data)<<10))
#define RIF_REG_CLKGATED_bsfifop2_gated_en_src(data)                                 ((0x00000400&(data))>>10)
#define RIF_REG_CLKGATED_get_bsfifop2_gated_en(data)                                 ((0x00000400&(data))>>10)
#define RIF_REG_CLKGATED_bsfifo_gated_en_shift                                       (9)
#define RIF_REG_CLKGATED_bsfifo_gated_en_mask                                        (0x00000200)
#define RIF_REG_CLKGATED_bsfifo_gated_en(data)                                       (0x00000200&((data)<<9))
#define RIF_REG_CLKGATED_bsfifo_gated_en_src(data)                                   ((0x00000200&(data))>>9)
#define RIF_REG_CLKGATED_get_bsfifo_gated_en(data)                                   ((0x00000200&(data))>>9)
#define RIF_REG_CLKGATED_deblk_gated_en_shift                                        (8)
#define RIF_REG_CLKGATED_deblk_gated_en_mask                                         (0x00000100)
#define RIF_REG_CLKGATED_deblk_gated_en(data)                                        (0x00000100&((data)<<8))
#define RIF_REG_CLKGATED_deblk_gated_en_src(data)                                    ((0x00000100&(data))>>8)
#define RIF_REG_CLKGATED_get_deblk_gated_en(data)                                    ((0x00000100&(data))>>8)
#define RIF_REG_CLKGATED_pred_gated_en_shift                                         (7)
#define RIF_REG_CLKGATED_pred_gated_en_mask                                          (0x00000080)
#define RIF_REG_CLKGATED_pred_gated_en(data)                                         (0x00000080&((data)<<7))
#define RIF_REG_CLKGATED_pred_gated_en_src(data)                                     ((0x00000080&(data))>>7)
#define RIF_REG_CLKGATED_get_pred_gated_en(data)                                     ((0x00000080&(data))>>7)
#define RIF_REG_CLKGATED_vm1_gated_en_shift                                          (6)
#define RIF_REG_CLKGATED_vm1_gated_en_mask                                           (0x00000040)
#define RIF_REG_CLKGATED_vm1_gated_en(data)                                          (0x00000040&((data)<<6))
#define RIF_REG_CLKGATED_vm1_gated_en_src(data)                                      ((0x00000040&(data))>>6)
#define RIF_REG_CLKGATED_get_vm1_gated_en(data)                                      ((0x00000040&(data))>>6)
#define RIF_REG_CLKGATED_it_gated_en_shift                                           (5)
#define RIF_REG_CLKGATED_it_gated_en_mask                                            (0x00000020)
#define RIF_REG_CLKGATED_it_gated_en(data)                                           (0x00000020&((data)<<5))
#define RIF_REG_CLKGATED_it_gated_en_src(data)                                       ((0x00000020&(data))>>5)
#define RIF_REG_CLKGATED_get_it_gated_en(data)                                       ((0x00000020&(data))>>5)
#define RIF_REG_CLKGATED_cabac_gated_en_shift                                        (4)
#define RIF_REG_CLKGATED_cabac_gated_en_mask                                         (0x00000010)
#define RIF_REG_CLKGATED_cabac_gated_en(data)                                        (0x00000010&((data)<<4))
#define RIF_REG_CLKGATED_cabac_gated_en_src(data)                                    ((0x00000010&(data))>>4)
#define RIF_REG_CLKGATED_get_cabac_gated_en(data)                                    ((0x00000010&(data))>>4)
#define RIF_REG_CLKGATED_vp8p2_gated_en_shift                                        (3)
#define RIF_REG_CLKGATED_vp8p2_gated_en_mask                                         (0x00000008)
#define RIF_REG_CLKGATED_vp8p2_gated_en(data)                                        (0x00000008&((data)<<3))
#define RIF_REG_CLKGATED_vp8p2_gated_en_src(data)                                    ((0x00000008&(data))>>3)
#define RIF_REG_CLKGATED_get_vp8p2_gated_en(data)                                    ((0x00000008&(data))>>3)
#define RIF_REG_CLKGATED_cabacp2_gated_en_shift                                      (2)
#define RIF_REG_CLKGATED_cabacp2_gated_en_mask                                       (0x00000004)
#define RIF_REG_CLKGATED_cabacp2_gated_en(data)                                      (0x00000004&((data)<<2))
#define RIF_REG_CLKGATED_cabacp2_gated_en_src(data)                                  ((0x00000004&(data))>>2)
#define RIF_REG_CLKGATED_get_cabacp2_gated_en(data)                                  ((0x00000004&(data))>>2)
#define RIF_REG_CLKGATED_vld_gated_en_shift                                          (1)
#define RIF_REG_CLKGATED_vld_gated_en_mask                                           (0x00000002)
#define RIF_REG_CLKGATED_vld_gated_en(data)                                          (0x00000002&((data)<<1))
#define RIF_REG_CLKGATED_vld_gated_en_src(data)                                      ((0x00000002&(data))>>1)
#define RIF_REG_CLKGATED_get_vld_gated_en(data)                                      ((0x00000002&(data))>>1)
#define RIF_REG_CLKGATED_acdc_gated_en_shift                                         (0)
#define RIF_REG_CLKGATED_acdc_gated_en_mask                                          (0x00000001)
#define RIF_REG_CLKGATED_acdc_gated_en(data)                                         (0x00000001&((data)<<0))
#define RIF_REG_CLKGATED_acdc_gated_en_src(data)                                     ((0x00000001&(data))>>0)
#define RIF_REG_CLKGATED_get_acdc_gated_en(data)                                     ((0x00000001&(data))>>0)


#define RIF_REG_DBG_OUT                                                              0x1800E4E0
#define RIF_REG_DBG_OUT_reg_addr                                                     "0xB800E4E0"
#define RIF_REG_DBG_OUT_reg                                                          0xB800E4E0
#define set_RIF_REG_DBG_OUT_reg(data)   (*((volatile unsigned int*) RIF_REG_DBG_OUT_reg)=data)
#define get_RIF_REG_DBG_OUT_reg   (*((volatile unsigned int*) RIF_REG_DBG_OUT_reg))
#define RIF_REG_DBG_OUT_inst_adr                                                     "0x0038"
#define RIF_REG_DBG_OUT_inst                                                         0x0038
#define RIF_REG_DBG_OUT_ve_dbg_out1_shift                                            (16)
#define RIF_REG_DBG_OUT_ve_dbg_out1_mask                                             (0xFFFF0000)
#define RIF_REG_DBG_OUT_ve_dbg_out1(data)                                            (0xFFFF0000&((data)<<16))
#define RIF_REG_DBG_OUT_ve_dbg_out1_src(data)                                        ((0xFFFF0000&(data))>>16)
#define RIF_REG_DBG_OUT_get_ve_dbg_out1(data)                                        ((0xFFFF0000&(data))>>16)
#define RIF_REG_DBG_OUT_ve_dbg_out0_shift                                            (0)
#define RIF_REG_DBG_OUT_ve_dbg_out0_mask                                             (0x0000FFFF)
#define RIF_REG_DBG_OUT_ve_dbg_out0(data)                                            (0x0000FFFF&((data)<<0))
#define RIF_REG_DBG_OUT_ve_dbg_out0_src(data)                                        ((0x0000FFFF&(data))>>0)
#define RIF_REG_DBG_OUT_get_ve_dbg_out0(data)                                        ((0x0000FFFF&(data))>>0)


#define RIF_REG_DBG_CTRL1                                                            0x1800E4E4
#define RIF_REG_DBG_CTRL1_reg_addr                                                   "0xB800E4E4"
#define RIF_REG_DBG_CTRL1_reg                                                        0xB800E4E4
#define set_RIF_REG_DBG_CTRL1_reg(data)   (*((volatile unsigned int*) RIF_REG_DBG_CTRL1_reg)=data)
#define get_RIF_REG_DBG_CTRL1_reg   (*((volatile unsigned int*) RIF_REG_DBG_CTRL1_reg))
#define RIF_REG_DBG_CTRL1_inst_adr                                                   "0x0039"
#define RIF_REG_DBG_CTRL1_inst                                                       0x0039
#define RIF_REG_DBG_CTRL1_cache_dbg_sel1_shift                                       (28)
#define RIF_REG_DBG_CTRL1_cache_dbg_sel1_mask                                        (0xF0000000)
#define RIF_REG_DBG_CTRL1_cache_dbg_sel1(data)                                       (0xF0000000&((data)<<28))
#define RIF_REG_DBG_CTRL1_cache_dbg_sel1_src(data)                                   ((0xF0000000&(data))>>28)
#define RIF_REG_DBG_CTRL1_get_cache_dbg_sel1(data)                                   ((0xF0000000&(data))>>28)
#define RIF_REG_DBG_CTRL1_cache_dbg_sel0_shift                                       (24)
#define RIF_REG_DBG_CTRL1_cache_dbg_sel0_mask                                        (0x0F000000)
#define RIF_REG_DBG_CTRL1_cache_dbg_sel0(data)                                       (0x0F000000&((data)<<24))
#define RIF_REG_DBG_CTRL1_cache_dbg_sel0_src(data)                                   ((0x0F000000&(data))>>24)
#define RIF_REG_DBG_CTRL1_get_cache_dbg_sel0(data)                                   ((0x0F000000&(data))>>24)
#define RIF_REG_DBG_CTRL1_bs_dbg_sel1_shift                                          (20)
#define RIF_REG_DBG_CTRL1_bs_dbg_sel1_mask                                           (0x00F00000)
#define RIF_REG_DBG_CTRL1_bs_dbg_sel1(data)                                          (0x00F00000&((data)<<20))
#define RIF_REG_DBG_CTRL1_bs_dbg_sel1_src(data)                                      ((0x00F00000&(data))>>20)
#define RIF_REG_DBG_CTRL1_get_bs_dbg_sel1(data)                                      ((0x00F00000&(data))>>20)
#define RIF_REG_DBG_CTRL1_bs_dbg_sel0_shift                                          (16)
#define RIF_REG_DBG_CTRL1_bs_dbg_sel0_mask                                           (0x000F0000)
#define RIF_REG_DBG_CTRL1_bs_dbg_sel0(data)                                          (0x000F0000&((data)<<16))
#define RIF_REG_DBG_CTRL1_bs_dbg_sel0_src(data)                                      ((0x000F0000&(data))>>16)
#define RIF_REG_DBG_CTRL1_get_bs_dbg_sel0(data)                                      ((0x000F0000&(data))>>16)
#define RIF_REG_DBG_CTRL1_brg_dbg_sel1_shift                                         (12)
#define RIF_REG_DBG_CTRL1_brg_dbg_sel1_mask                                          (0x0000F000)
#define RIF_REG_DBG_CTRL1_brg_dbg_sel1(data)                                         (0x0000F000&((data)<<12))
#define RIF_REG_DBG_CTRL1_brg_dbg_sel1_src(data)                                     ((0x0000F000&(data))>>12)
#define RIF_REG_DBG_CTRL1_get_brg_dbg_sel1(data)                                     ((0x0000F000&(data))>>12)
#define RIF_REG_DBG_CTRL1_brg_dbg_sel0_shift                                         (8)
#define RIF_REG_DBG_CTRL1_brg_dbg_sel0_mask                                          (0x00000F00)
#define RIF_REG_DBG_CTRL1_brg_dbg_sel0(data)                                         (0x00000F00&((data)<<8))
#define RIF_REG_DBG_CTRL1_brg_dbg_sel0_src(data)                                     ((0x00000F00&(data))>>8)
#define RIF_REG_DBG_CTRL1_get_brg_dbg_sel0(data)                                     ((0x00000F00&(data))>>8)
#define RIF_REG_DBG_CTRL1_acdc_dbg_sel1_shift                                        (4)
#define RIF_REG_DBG_CTRL1_acdc_dbg_sel1_mask                                         (0x000000F0)
#define RIF_REG_DBG_CTRL1_acdc_dbg_sel1(data)                                        (0x000000F0&((data)<<4))
#define RIF_REG_DBG_CTRL1_acdc_dbg_sel1_src(data)                                    ((0x000000F0&(data))>>4)
#define RIF_REG_DBG_CTRL1_get_acdc_dbg_sel1(data)                                    ((0x000000F0&(data))>>4)
#define RIF_REG_DBG_CTRL1_acdc_dbg_sel0_shift                                        (0)
#define RIF_REG_DBG_CTRL1_acdc_dbg_sel0_mask                                         (0x0000000F)
#define RIF_REG_DBG_CTRL1_acdc_dbg_sel0(data)                                        (0x0000000F&((data)<<0))
#define RIF_REG_DBG_CTRL1_acdc_dbg_sel0_src(data)                                    ((0x0000000F&(data))>>0)
#define RIF_REG_DBG_CTRL1_get_acdc_dbg_sel0(data)                                    ((0x0000000F&(data))>>0)


#define RIF_REG_DBG_CTRL2                                                            0x1800E4E8
#define RIF_REG_DBG_CTRL2_reg_addr                                                   "0xB800E4E8"
#define RIF_REG_DBG_CTRL2_reg                                                        0xB800E4E8
#define set_RIF_REG_DBG_CTRL2_reg(data)   (*((volatile unsigned int*) RIF_REG_DBG_CTRL2_reg)=data)
#define get_RIF_REG_DBG_CTRL2_reg   (*((volatile unsigned int*) RIF_REG_DBG_CTRL2_reg))
#define RIF_REG_DBG_CTRL2_inst_adr                                                   "0x003A"
#define RIF_REG_DBG_CTRL2_inst                                                       0x003A
#define RIF_REG_DBG_CTRL2_cm_dbg_sel1_shift                                          (20)
#define RIF_REG_DBG_CTRL2_cm_dbg_sel1_mask                                           (0x00F00000)
#define RIF_REG_DBG_CTRL2_cm_dbg_sel1(data)                                          (0x00F00000&((data)<<20))
#define RIF_REG_DBG_CTRL2_cm_dbg_sel1_src(data)                                      ((0x00F00000&(data))>>20)
#define RIF_REG_DBG_CTRL2_get_cm_dbg_sel1(data)                                      ((0x00F00000&(data))>>20)
#define RIF_REG_DBG_CTRL2_cm_dbg_sel0_shift                                          (16)
#define RIF_REG_DBG_CTRL2_cm_dbg_sel0_mask                                           (0x000F0000)
#define RIF_REG_DBG_CTRL2_cm_dbg_sel0(data)                                          (0x000F0000&((data)<<16))
#define RIF_REG_DBG_CTRL2_cm_dbg_sel0_src(data)                                      ((0x000F0000&(data))>>16)
#define RIF_REG_DBG_CTRL2_get_cm_dbg_sel0(data)                                      ((0x000F0000&(data))>>16)
#define RIF_REG_DBG_CTRL2_cabacp3_dbg_sel1_shift                                     (12)
#define RIF_REG_DBG_CTRL2_cabacp3_dbg_sel1_mask                                      (0x0000F000)
#define RIF_REG_DBG_CTRL2_cabacp3_dbg_sel1(data)                                     (0x0000F000&((data)<<12))
#define RIF_REG_DBG_CTRL2_cabacp3_dbg_sel1_src(data)                                 ((0x0000F000&(data))>>12)
#define RIF_REG_DBG_CTRL2_get_cabacp3_dbg_sel1(data)                                 ((0x0000F000&(data))>>12)
#define RIF_REG_DBG_CTRL2_cabacp3_dbg_sel0_shift                                     (8)
#define RIF_REG_DBG_CTRL2_cabacp3_dbg_sel0_mask                                      (0x00000F00)
#define RIF_REG_DBG_CTRL2_cabacp3_dbg_sel0(data)                                     (0x00000F00&((data)<<8))
#define RIF_REG_DBG_CTRL2_cabacp3_dbg_sel0_src(data)                                 ((0x00000F00&(data))>>8)
#define RIF_REG_DBG_CTRL2_get_cabacp3_dbg_sel0(data)                                 ((0x00000F00&(data))>>8)
#define RIF_REG_DBG_CTRL2_cabacp2_dbg_sel1_shift                                     (4)
#define RIF_REG_DBG_CTRL2_cabacp2_dbg_sel1_mask                                      (0x000000F0)
#define RIF_REG_DBG_CTRL2_cabacp2_dbg_sel1(data)                                     (0x000000F0&((data)<<4))
#define RIF_REG_DBG_CTRL2_cabacp2_dbg_sel1_src(data)                                 ((0x000000F0&(data))>>4)
#define RIF_REG_DBG_CTRL2_get_cabacp2_dbg_sel1(data)                                 ((0x000000F0&(data))>>4)
#define RIF_REG_DBG_CTRL2_cabacp2_dbg_sel0_shift                                     (0)
#define RIF_REG_DBG_CTRL2_cabacp2_dbg_sel0_mask                                      (0x0000000F)
#define RIF_REG_DBG_CTRL2_cabacp2_dbg_sel0(data)                                     (0x0000000F&((data)<<0))
#define RIF_REG_DBG_CTRL2_cabacp2_dbg_sel0_src(data)                                 ((0x0000000F&(data))>>0)
#define RIF_REG_DBG_CTRL2_get_cabacp2_dbg_sel0(data)                                 ((0x0000000F&(data))>>0)


#define RIF_REG_DBG_CTRL3                                                            0x1800E4EC
#define RIF_REG_DBG_CTRL3_reg_addr                                                   "0xB800E4EC"
#define RIF_REG_DBG_CTRL3_reg                                                        0xB800E4EC
#define set_RIF_REG_DBG_CTRL3_reg(data)   (*((volatile unsigned int*) RIF_REG_DBG_CTRL3_reg)=data)
#define get_RIF_REG_DBG_CTRL3_reg   (*((volatile unsigned int*) RIF_REG_DBG_CTRL3_reg))
#define RIF_REG_DBG_CTRL3_inst_adr                                                   "0x003B"
#define RIF_REG_DBG_CTRL3_inst                                                       0x003B
#define RIF_REG_DBG_CTRL3_ndb_dbg_sel1_shift                                         (28)
#define RIF_REG_DBG_CTRL3_ndb_dbg_sel1_mask                                          (0xF0000000)
#define RIF_REG_DBG_CTRL3_ndb_dbg_sel1(data)                                         (0xF0000000&((data)<<28))
#define RIF_REG_DBG_CTRL3_ndb_dbg_sel1_src(data)                                     ((0xF0000000&(data))>>28)
#define RIF_REG_DBG_CTRL3_get_ndb_dbg_sel1(data)                                     ((0xF0000000&(data))>>28)
#define RIF_REG_DBG_CTRL3_ndb_dbg_sel0_shift                                         (24)
#define RIF_REG_DBG_CTRL3_ndb_dbg_sel0_mask                                          (0x0F000000)
#define RIF_REG_DBG_CTRL3_ndb_dbg_sel0(data)                                         (0x0F000000&((data)<<24))
#define RIF_REG_DBG_CTRL3_ndb_dbg_sel0_src(data)                                     ((0x0F000000&(data))>>24)
#define RIF_REG_DBG_CTRL3_get_ndb_dbg_sel0(data)                                     ((0x0F000000&(data))>>24)
#define RIF_REG_DBG_CTRL3_rif_dbg_sel1_shift                                         (20)
#define RIF_REG_DBG_CTRL3_rif_dbg_sel1_mask                                          (0x00F00000)
#define RIF_REG_DBG_CTRL3_rif_dbg_sel1(data)                                         (0x00F00000&((data)<<20))
#define RIF_REG_DBG_CTRL3_rif_dbg_sel1_src(data)                                     ((0x00F00000&(data))>>20)
#define RIF_REG_DBG_CTRL3_get_rif_dbg_sel1(data)                                     ((0x00F00000&(data))>>20)
#define RIF_REG_DBG_CTRL3_rif_dbg_sel0_shift                                         (16)
#define RIF_REG_DBG_CTRL3_rif_dbg_sel0_mask                                          (0x000F0000)
#define RIF_REG_DBG_CTRL3_rif_dbg_sel0(data)                                         (0x000F0000&((data)<<16))
#define RIF_REG_DBG_CTRL3_rif_dbg_sel0_src(data)                                     ((0x000F0000&(data))>>16)
#define RIF_REG_DBG_CTRL3_get_rif_dbg_sel0(data)                                     ((0x000F0000&(data))>>16)
#define RIF_REG_DBG_CTRL3_itblk_dbg_sel1_shift                                       (12)
#define RIF_REG_DBG_CTRL3_itblk_dbg_sel1_mask                                        (0x0000F000)
#define RIF_REG_DBG_CTRL3_itblk_dbg_sel1(data)                                       (0x0000F000&((data)<<12))
#define RIF_REG_DBG_CTRL3_itblk_dbg_sel1_src(data)                                   ((0x0000F000&(data))>>12)
#define RIF_REG_DBG_CTRL3_get_itblk_dbg_sel1(data)                                   ((0x0000F000&(data))>>12)
#define RIF_REG_DBG_CTRL3_itblk_dbg_sel0_shift                                       (8)
#define RIF_REG_DBG_CTRL3_itblk_dbg_sel0_mask                                        (0x00000F00)
#define RIF_REG_DBG_CTRL3_itblk_dbg_sel0(data)                                       (0x00000F00&((data)<<8))
#define RIF_REG_DBG_CTRL3_itblk_dbg_sel0_src(data)                                   ((0x00000F00&(data))>>8)
#define RIF_REG_DBG_CTRL3_get_itblk_dbg_sel0(data)                                   ((0x00000F00&(data))>>8)
#define RIF_REG_DBG_CTRL3_img_dbg_sel1_shift                                         (4)
#define RIF_REG_DBG_CTRL3_img_dbg_sel1_mask                                          (0x000000F0)
#define RIF_REG_DBG_CTRL3_img_dbg_sel1(data)                                         (0x000000F0&((data)<<4))
#define RIF_REG_DBG_CTRL3_img_dbg_sel1_src(data)                                     ((0x000000F0&(data))>>4)
#define RIF_REG_DBG_CTRL3_get_img_dbg_sel1(data)                                     ((0x000000F0&(data))>>4)
#define RIF_REG_DBG_CTRL3_img_dbg_sel0_shift                                         (0)
#define RIF_REG_DBG_CTRL3_img_dbg_sel0_mask                                          (0x0000000F)
#define RIF_REG_DBG_CTRL3_img_dbg_sel0(data)                                         (0x0000000F&((data)<<0))
#define RIF_REG_DBG_CTRL3_img_dbg_sel0_src(data)                                     ((0x0000000F&(data))>>0)
#define RIF_REG_DBG_CTRL3_get_img_dbg_sel0(data)                                     ((0x0000000F&(data))>>0)


#define RIF_REG_DBG_CTRL4                                                            0x1800E4F0
#define RIF_REG_DBG_CTRL4_reg_addr                                                   "0xB800E4F0"
#define RIF_REG_DBG_CTRL4_reg                                                        0xB800E4F0
#define set_RIF_REG_DBG_CTRL4_reg(data)   (*((volatile unsigned int*) RIF_REG_DBG_CTRL4_reg)=data)
#define get_RIF_REG_DBG_CTRL4_reg   (*((volatile unsigned int*) RIF_REG_DBG_CTRL4_reg))
#define RIF_REG_DBG_CTRL4_inst_adr                                                   "0x003C"
#define RIF_REG_DBG_CTRL4_inst                                                       0x003C
#define RIF_REG_DBG_CTRL4_rl_dbg_sel1_shift                                          (28)
#define RIF_REG_DBG_CTRL4_rl_dbg_sel1_mask                                           (0xF0000000)
#define RIF_REG_DBG_CTRL4_rl_dbg_sel1(data)                                          (0xF0000000&((data)<<28))
#define RIF_REG_DBG_CTRL4_rl_dbg_sel1_src(data)                                      ((0xF0000000&(data))>>28)
#define RIF_REG_DBG_CTRL4_get_rl_dbg_sel1(data)                                      ((0xF0000000&(data))>>28)
#define RIF_REG_DBG_CTRL4_rl_dbg_sel0_shift                                          (24)
#define RIF_REG_DBG_CTRL4_rl_dbg_sel0_mask                                           (0x0F000000)
#define RIF_REG_DBG_CTRL4_rl_dbg_sel0(data)                                          (0x0F000000&((data)<<24))
#define RIF_REG_DBG_CTRL4_rl_dbg_sel0_src(data)                                      ((0x0F000000&(data))>>24)
#define RIF_REG_DBG_CTRL4_get_rl_dbg_sel0(data)                                      ((0x0F000000&(data))>>24)
#define RIF_REG_DBG_CTRL4_vld_dbg_sel1_shift                                         (20)
#define RIF_REG_DBG_CTRL4_vld_dbg_sel1_mask                                          (0x00F00000)
#define RIF_REG_DBG_CTRL4_vld_dbg_sel1(data)                                         (0x00F00000&((data)<<20))
#define RIF_REG_DBG_CTRL4_vld_dbg_sel1_src(data)                                     ((0x00F00000&(data))>>20)
#define RIF_REG_DBG_CTRL4_get_vld_dbg_sel1(data)                                     ((0x00F00000&(data))>>20)
#define RIF_REG_DBG_CTRL4_vld_dbg_sel0_shift                                         (16)
#define RIF_REG_DBG_CTRL4_vld_dbg_sel0_mask                                          (0x000F0000)
#define RIF_REG_DBG_CTRL4_vld_dbg_sel0(data)                                         (0x000F0000&((data)<<16))
#define RIF_REG_DBG_CTRL4_vld_dbg_sel0_src(data)                                     ((0x000F0000&(data))>>16)
#define RIF_REG_DBG_CTRL4_get_vld_dbg_sel0(data)                                     ((0x000F0000&(data))>>16)
#define RIF_REG_DBG_CTRL4_arb_dbg_sel1_shift                                         (12)
#define RIF_REG_DBG_CTRL4_arb_dbg_sel1_mask                                          (0x0000F000)
#define RIF_REG_DBG_CTRL4_arb_dbg_sel1(data)                                         (0x0000F000&((data)<<12))
#define RIF_REG_DBG_CTRL4_arb_dbg_sel1_src(data)                                     ((0x0000F000&(data))>>12)
#define RIF_REG_DBG_CTRL4_get_arb_dbg_sel1(data)                                     ((0x0000F000&(data))>>12)
#define RIF_REG_DBG_CTRL4_arb_dbg_sel0_shift                                         (8)
#define RIF_REG_DBG_CTRL4_arb_dbg_sel0_mask                                          (0x00000F00)
#define RIF_REG_DBG_CTRL4_arb_dbg_sel0(data)                                         (0x00000F00&((data)<<8))
#define RIF_REG_DBG_CTRL4_arb_dbg_sel0_src(data)                                     ((0x00000F00&(data))>>8)
#define RIF_REG_DBG_CTRL4_get_arb_dbg_sel0(data)                                     ((0x00000F00&(data))>>8)
#define RIF_REG_DBG_CTRL4_vm1_dbg_sel1_shift                                         (4)
#define RIF_REG_DBG_CTRL4_vm1_dbg_sel1_mask                                          (0x000000F0)
#define RIF_REG_DBG_CTRL4_vm1_dbg_sel1(data)                                         (0x000000F0&((data)<<4))
#define RIF_REG_DBG_CTRL4_vm1_dbg_sel1_src(data)                                     ((0x000000F0&(data))>>4)
#define RIF_REG_DBG_CTRL4_get_vm1_dbg_sel1(data)                                     ((0x000000F0&(data))>>4)
#define RIF_REG_DBG_CTRL4_vm1_dbg_sel0_shift                                         (0)
#define RIF_REG_DBG_CTRL4_vm1_dbg_sel0_mask                                          (0x0000000F)
#define RIF_REG_DBG_CTRL4_vm1_dbg_sel0(data)                                         (0x0000000F&((data)<<0))
#define RIF_REG_DBG_CTRL4_vm1_dbg_sel0_src(data)                                     ((0x0000000F&(data))>>0)
#define RIF_REG_DBG_CTRL4_get_vm1_dbg_sel0(data)                                     ((0x0000000F&(data))>>0)


#define RIF_REG_DBG_CTRL5                                                            0x1800E4F4
#define RIF_REG_DBG_CTRL5_reg_addr                                                   "0xB800E4F4"
#define RIF_REG_DBG_CTRL5_reg                                                        0xB800E4F4
#define set_RIF_REG_DBG_CTRL5_reg(data)   (*((volatile unsigned int*) RIF_REG_DBG_CTRL5_reg)=data)
#define get_RIF_REG_DBG_CTRL5_reg   (*((volatile unsigned int*) RIF_REG_DBG_CTRL5_reg))
#define RIF_REG_DBG_CTRL5_inst_adr                                                   "0x003D"
#define RIF_REG_DBG_CTRL5_inst                                                       0x003D
#define RIF_REG_DBG_CTRL5_deblk_dbg_sel1_shift                                       (26)
#define RIF_REG_DBG_CTRL5_deblk_dbg_sel1_mask                                        (0xFC000000)
#define RIF_REG_DBG_CTRL5_deblk_dbg_sel1(data)                                       (0xFC000000&((data)<<26))
#define RIF_REG_DBG_CTRL5_deblk_dbg_sel1_src(data)                                   ((0xFC000000&(data))>>26)
#define RIF_REG_DBG_CTRL5_get_deblk_dbg_sel1(data)                                   ((0xFC000000&(data))>>26)
#define RIF_REG_DBG_CTRL5_deblk_dbg_sel0_shift                                       (20)
#define RIF_REG_DBG_CTRL5_deblk_dbg_sel0_mask                                        (0x03F00000)
#define RIF_REG_DBG_CTRL5_deblk_dbg_sel0(data)                                       (0x03F00000&((data)<<20))
#define RIF_REG_DBG_CTRL5_deblk_dbg_sel0_src(data)                                   ((0x03F00000&(data))>>20)
#define RIF_REG_DBG_CTRL5_get_deblk_dbg_sel0(data)                                   ((0x03F00000&(data))>>20)
#define RIF_REG_DBG_CTRL5_mvd_dbg_sel1_shift                                         (16)
#define RIF_REG_DBG_CTRL5_mvd_dbg_sel1_mask                                          (0x000F0000)
#define RIF_REG_DBG_CTRL5_mvd_dbg_sel1(data)                                         (0x000F0000&((data)<<16))
#define RIF_REG_DBG_CTRL5_mvd_dbg_sel1_src(data)                                     ((0x000F0000&(data))>>16)
#define RIF_REG_DBG_CTRL5_get_mvd_dbg_sel1(data)                                     ((0x000F0000&(data))>>16)
#define RIF_REG_DBG_CTRL5_mvd_dbg_sel0_shift                                         (12)
#define RIF_REG_DBG_CTRL5_mvd_dbg_sel0_mask                                          (0x0000F000)
#define RIF_REG_DBG_CTRL5_mvd_dbg_sel0(data)                                         (0x0000F000&((data)<<12))
#define RIF_REG_DBG_CTRL5_mvd_dbg_sel0_src(data)                                     ((0x0000F000&(data))>>12)
#define RIF_REG_DBG_CTRL5_get_mvd_dbg_sel0(data)                                     ((0x0000F000&(data))>>12)
#define RIF_REG_DBG_CTRL5_prd_dbg_sel1_shift                                         (6)
#define RIF_REG_DBG_CTRL5_prd_dbg_sel1_mask                                          (0x00000FC0)
#define RIF_REG_DBG_CTRL5_prd_dbg_sel1(data)                                         (0x00000FC0&((data)<<6))
#define RIF_REG_DBG_CTRL5_prd_dbg_sel1_src(data)                                     ((0x00000FC0&(data))>>6)
#define RIF_REG_DBG_CTRL5_get_prd_dbg_sel1(data)                                     ((0x00000FC0&(data))>>6)
#define RIF_REG_DBG_CTRL5_prd_dbg_sel0_shift                                         (0)
#define RIF_REG_DBG_CTRL5_prd_dbg_sel0_mask                                          (0x0000003F)
#define RIF_REG_DBG_CTRL5_prd_dbg_sel0(data)                                         (0x0000003F&((data)<<0))
#define RIF_REG_DBG_CTRL5_prd_dbg_sel0_src(data)                                     ((0x0000003F&(data))>>0)
#define RIF_REG_DBG_CTRL5_get_prd_dbg_sel0(data)                                     ((0x0000003F&(data))>>0)


#define RIF_REG_FPGA_DBG1                                                            0x1800E4F8
#define RIF_REG_FPGA_DBG1_reg_addr                                                   "0xB800E4F8"
#define RIF_REG_FPGA_DBG1_reg                                                        0xB800E4F8
#define set_RIF_REG_FPGA_DBG1_reg(data)   (*((volatile unsigned int*) RIF_REG_FPGA_DBG1_reg)=data)
#define get_RIF_REG_FPGA_DBG1_reg   (*((volatile unsigned int*) RIF_REG_FPGA_DBG1_reg))
#define RIF_REG_FPGA_DBG1_inst_adr                                                   "0x003E"
#define RIF_REG_FPGA_DBG1_inst                                                       0x003E
#define RIF_REG_FPGA_DBG1_cache_busy_shift                                           (14)
#define RIF_REG_FPGA_DBG1_cache_busy_mask                                            (0x00004000)
#define RIF_REG_FPGA_DBG1_cache_busy(data)                                           (0x00004000&((data)<<14))
#define RIF_REG_FPGA_DBG1_cache_busy_src(data)                                       ((0x00004000&(data))>>14)
#define RIF_REG_FPGA_DBG1_get_cache_busy(data)                                       ((0x00004000&(data))>>14)
#define RIF_REG_FPGA_DBG1_brg_busy_shift                                             (13)
#define RIF_REG_FPGA_DBG1_brg_busy_mask                                              (0x00002000)
#define RIF_REG_FPGA_DBG1_brg_busy(data)                                             (0x00002000&((data)<<13))
#define RIF_REG_FPGA_DBG1_brg_busy_src(data)                                         ((0x00002000&(data))>>13)
#define RIF_REG_FPGA_DBG1_get_brg_busy(data)                                         ((0x00002000&(data))>>13)
#define RIF_REG_FPGA_DBG1_ndb_busy_shift                                             (12)
#define RIF_REG_FPGA_DBG1_ndb_busy_mask                                              (0x00001000)
#define RIF_REG_FPGA_DBG1_ndb_busy(data)                                             (0x00001000&((data)<<12))
#define RIF_REG_FPGA_DBG1_ndb_busy_src(data)                                         ((0x00001000&(data))>>12)
#define RIF_REG_FPGA_DBG1_get_ndb_busy(data)                                         ((0x00001000&(data))>>12)
#define RIF_REG_FPGA_DBG1_bsfifo_busy_shift                                          (11)
#define RIF_REG_FPGA_DBG1_bsfifo_busy_mask                                           (0x00000800)
#define RIF_REG_FPGA_DBG1_bsfifo_busy(data)                                          (0x00000800&((data)<<11))
#define RIF_REG_FPGA_DBG1_bsfifo_busy_src(data)                                      ((0x00000800&(data))>>11)
#define RIF_REG_FPGA_DBG1_get_bsfifo_busy(data)                                      ((0x00000800&(data))>>11)
#define RIF_REG_FPGA_DBG1_img_busy_shift                                             (10)
#define RIF_REG_FPGA_DBG1_img_busy_mask                                              (0x00000400)
#define RIF_REG_FPGA_DBG1_img_busy(data)                                             (0x00000400&((data)<<10))
#define RIF_REG_FPGA_DBG1_img_busy_src(data)                                         ((0x00000400&(data))>>10)
#define RIF_REG_FPGA_DBG1_get_img_busy(data)                                         ((0x00000400&(data))>>10)
#define RIF_REG_FPGA_DBG1_vm1_busy_shift                                             (9)
#define RIF_REG_FPGA_DBG1_vm1_busy_mask                                              (0x00000200)
#define RIF_REG_FPGA_DBG1_vm1_busy(data)                                             (0x00000200&((data)<<9))
#define RIF_REG_FPGA_DBG1_vm1_busy_src(data)                                         ((0x00000200&(data))>>9)
#define RIF_REG_FPGA_DBG1_get_vm1_busy(data)                                         ((0x00000200&(data))>>9)
#define RIF_REG_FPGA_DBG1_deblk_busy_shift                                           (8)
#define RIF_REG_FPGA_DBG1_deblk_busy_mask                                            (0x00000100)
#define RIF_REG_FPGA_DBG1_deblk_busy(data)                                           (0x00000100&((data)<<8))
#define RIF_REG_FPGA_DBG1_deblk_busy_src(data)                                       ((0x00000100&(data))>>8)
#define RIF_REG_FPGA_DBG1_get_deblk_busy(data)                                       ((0x00000100&(data))>>8)
#define RIF_REG_FPGA_DBG1_rl_busy_shift                                              (7)
#define RIF_REG_FPGA_DBG1_rl_busy_mask                                               (0x00000080)
#define RIF_REG_FPGA_DBG1_rl_busy(data)                                              (0x00000080&((data)<<7))
#define RIF_REG_FPGA_DBG1_rl_busy_src(data)                                          ((0x00000080&(data))>>7)
#define RIF_REG_FPGA_DBG1_get_rl_busy(data)                                          ((0x00000080&(data))>>7)
#define RIF_REG_FPGA_DBG1_pred_busy_shift                                            (6)
#define RIF_REG_FPGA_DBG1_pred_busy_mask                                             (0x00000040)
#define RIF_REG_FPGA_DBG1_pred_busy(data)                                            (0x00000040&((data)<<6))
#define RIF_REG_FPGA_DBG1_pred_busy_src(data)                                        ((0x00000040&(data))>>6)
#define RIF_REG_FPGA_DBG1_get_pred_busy(data)                                        ((0x00000040&(data))>>6)
#define RIF_REG_FPGA_DBG1_mvd_busy_shift                                             (5)
#define RIF_REG_FPGA_DBG1_mvd_busy_mask                                              (0x00000020)
#define RIF_REG_FPGA_DBG1_mvd_busy(data)                                             (0x00000020&((data)<<5))
#define RIF_REG_FPGA_DBG1_mvd_busy_src(data)                                         ((0x00000020&(data))>>5)
#define RIF_REG_FPGA_DBG1_get_mvd_busy(data)                                         ((0x00000020&(data))>>5)
#define RIF_REG_FPGA_DBG1_itblk_busy_shift                                           (4)
#define RIF_REG_FPGA_DBG1_itblk_busy_mask                                            (0x00000010)
#define RIF_REG_FPGA_DBG1_itblk_busy(data)                                           (0x00000010&((data)<<4))
#define RIF_REG_FPGA_DBG1_itblk_busy_src(data)                                       ((0x00000010&(data))>>4)
#define RIF_REG_FPGA_DBG1_get_itblk_busy(data)                                       ((0x00000010&(data))>>4)
#define RIF_REG_FPGA_DBG1_acdc_busy_shift                                            (3)
#define RIF_REG_FPGA_DBG1_acdc_busy_mask                                             (0x00000008)
#define RIF_REG_FPGA_DBG1_acdc_busy(data)                                            (0x00000008&((data)<<3))
#define RIF_REG_FPGA_DBG1_acdc_busy_src(data)                                        ((0x00000008&(data))>>3)
#define RIF_REG_FPGA_DBG1_get_acdc_busy(data)                                        ((0x00000008&(data))>>3)
#define RIF_REG_FPGA_DBG1_cabacp2_busy_shift                                         (2)
#define RIF_REG_FPGA_DBG1_cabacp2_busy_mask                                          (0x00000004)
#define RIF_REG_FPGA_DBG1_cabacp2_busy(data)                                         (0x00000004&((data)<<2))
#define RIF_REG_FPGA_DBG1_cabacp2_busy_src(data)                                     ((0x00000004&(data))>>2)
#define RIF_REG_FPGA_DBG1_get_cabacp2_busy(data)                                     ((0x00000004&(data))>>2)
#define RIF_REG_FPGA_DBG1_vld_busy_shift                                             (1)
#define RIF_REG_FPGA_DBG1_vld_busy_mask                                              (0x00000002)
#define RIF_REG_FPGA_DBG1_vld_busy(data)                                             (0x00000002&((data)<<1))
#define RIF_REG_FPGA_DBG1_vld_busy_src(data)                                         ((0x00000002&(data))>>1)
#define RIF_REG_FPGA_DBG1_get_vld_busy(data)                                         ((0x00000002&(data))>>1)
#define RIF_REG_FPGA_DBG1_rifvld_busy_shift                                          (0)
#define RIF_REG_FPGA_DBG1_rifvld_busy_mask                                           (0x00000001)
#define RIF_REG_FPGA_DBG1_rifvld_busy(data)                                          (0x00000001&((data)<<0))
#define RIF_REG_FPGA_DBG1_rifvld_busy_src(data)                                      ((0x00000001&(data))>>0)
#define RIF_REG_FPGA_DBG1_get_rifvld_busy(data)                                      ((0x00000001&(data))>>0)


#endif
