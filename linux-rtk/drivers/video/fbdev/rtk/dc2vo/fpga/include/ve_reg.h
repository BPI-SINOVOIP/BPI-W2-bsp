// This file is generated using the spec version 1.66, firmware template version 1.39and DVR_Parser_0.46
#ifndef _VE_REG_H_INCLUDED_
#define _VE_REG_H_INCLUDED_

//#define  _VE_USE_STRUCT
#ifdef _VE_USE_STRUCT

typedef struct
{
    unsigned int    reserved_0:9;
    unsigned int    dering_dbg_sel:3;
    unsigned int    vmblk_idle:1;
    unsigned int    dbg_group2_sel:5;
    unsigned int    dbg_group1_sel:5;
    unsigned int    dbg_out_en:1;
    unsigned int    codblk_mode1:1;
    unsigned int    codblk_mode0:1;
    unsigned int    haltve_done:1;
    unsigned int    haltve:1;
    unsigned int    veidle:1;
    unsigned int    inten:1;
    unsigned int    reset_ptr:1;
    unsigned int    write_data:1;
}ve_CNTL;

typedef struct
{
    unsigned int    reserved_0:12;
    unsigned int    first_error_b3:1;
    unsigned int    first_error_b2:1;
    unsigned int    first_error_b1:1;
    unsigned int    first_error_b0:1;
    unsigned int    reserved_1:8;
    unsigned int    mt64coeff:1;
    unsigned int    rstff_oflow:1;
    unsigned int    rstff_empty:1;
    unsigned int    bitst_fifo:1;
    unsigned int    unexp_inst:1;
    unsigned int    scode_limit:1;
    unsigned int    dec_bitst:1;
    unsigned int    write_data:1;
}ve_INT_STATUS;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    mt64coeff:1;
    unsigned int    rstff_oflow:1;
    unsigned int    rstff_empty:1;
    unsigned int    bitst_fifo:1;
    unsigned int    unexp_inst:1;
    unsigned int    scode_limit:1;
    unsigned int    dec_bitst:1;
    unsigned int    write_data:1;
}ve_INTEN;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    codenum:6;
    unsigned int    vspnum:6;
    unsigned int    dmanum:6;
    unsigned int    maxfifo:6;
    unsigned int    rstnum:5;
}ve_FIFOSTATE;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable7:1;
    unsigned int    img_rsltstall_enable:1;
    unsigned int    write_enable6:1;
    unsigned int    dct_rsltstall_enable:1;
    unsigned int    dct_cmstall_enable:1;
    unsigned int    write_enable5:1;
    unsigned int    vlc_cmstall_enable:1;
    unsigned int    vlc_bsstall_enable:1;
    unsigned int    write_enable4:1;
    unsigned int    vld_rsltstall_enable:1;
    unsigned int    vld_cmstall_enable:1;
    unsigned int    vld_bsstall_enable:1;
    unsigned int    write_enable3:1;
    unsigned int    pc2_src:2;
    unsigned int    pc2_enable:1;
    unsigned int    write_enable2:1;
    unsigned int    pc1_src:1;
    unsigned int    reserved1:1;
    unsigned int    pc1_enable:1;
    unsigned int    write_enable1:1;
    unsigned int    pc0_src:1;
    unsigned int    reserved0:1;
    unsigned int    pc0_enable:1;
}ve_PCCNTL;

typedef struct
{
    unsigned int    perf_counter0:32;
}ve_PC0;

typedef struct
{
    unsigned int    perf_counter1:32;
}ve_PC1;

typedef struct
{
    unsigned int    perf_counter2:32;
}ve_PC2;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    write_enable8:1;
    unsigned int    quant_type:1;
    unsigned int    write_enable6:1;
    unsigned int    quant_msk:8;
    unsigned int    write_enable5:1;
    unsigned int    ch_conv:1;
    unsigned int    write_enable4:1;
    unsigned int    intra:1;
    unsigned int    write_enable3:1;
    unsigned int    qst:1;
    unsigned int    write_enable2:1;
    unsigned int    qsc:5;
    unsigned int    write_enable1:1;
    unsigned int    id_pred:2;
    unsigned int    write_enable:1;
    unsigned int    field_dct:1;
}ve_DCTCNTL;

typedef struct
{
    unsigned int    reserved_0:13;
    unsigned int    intra_round_dir:1;
    unsigned int    intra_round_value:3;
    unsigned int    inter_round_dir:1;
    unsigned int    inter_round_value:3;
    unsigned int    threshold:4;
    unsigned int    mb_pattern:1;
    unsigned int    cbp:6;
}ve_CODECPARAM;

typedef struct
{
    unsigned int    write_enable6:1;
    unsigned int    bk_x_fcode:4;
    unsigned int    bk_y_fcode:4;
    unsigned int    write_enable5:1;
    unsigned int    fo_x_fcode:4;
    unsigned int    fo_y_fcode:4;
    unsigned int    write_enable4:1;
    unsigned int    max_xfer_size:1;
    unsigned int    write_enable3:1;
    unsigned int    min_xfer_size:3;
    unsigned int    write_enable2:1;
    unsigned int    pic_type:2;
    unsigned int    write_enable1:1;
    unsigned int    coding_type:4;
}ve_CODECCNTL;

typedef struct
{
    unsigned int    dv_skip_pass3:1;
    unsigned int    ivf:1;
    unsigned int    as:1;
    unsigned int    pseudomode:1;
    unsigned int    reserved_0:20;
    unsigned int    data_partition:1;
    unsigned int    intra_dc_vlc:1;
    unsigned int    short_hdr:1;
    unsigned int    r_vlc:1;
    unsigned int    ac_pred:1;
    unsigned int    q_sample:1;
    unsigned int    ldtable:1;
    unsigned int    write_data:1;
}ve_CODECCNTL1;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    dct_mode:6;
    unsigned int    class_blk:12;
    unsigned int    qno:4;
}ve_DVPARAM;

typedef struct
{
    unsigned int    reserved_0:1;
    unsigned int    struvlc_len:31;
}ve_RVSTRUVLCLEN;

typedef struct
{
    unsigned int    write_enable3:1;
    unsigned int    umem1_mstr:1;
    unsigned int    write_enable2:1;
    unsigned int    rvmb_type:4;
    unsigned int    write_enable1:1;
    unsigned int    24bits_cbp:24;
}ve_RVPARAM;

typedef struct
{
    unsigned int    intra_mode1:32;
}ve_RVINTRAMODE1;

typedef struct
{
    unsigned int    intra_mode2:32;
}ve_RVINTRAMODE2;

typedef struct
{
    unsigned int    reserved_0:29;
    unsigned int    rv9_intramode_use_top:1;
    unsigned int    rv_osvquant:2;
}ve_RVPARAM2;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    tbl_startaddr:11;
}ve_VLDTBLPTR;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    tbl_espptr_saddr:11;
}ve_VLDESPPTR;

typedef struct
{
    unsigned int    max_bit:32;
}ve_DECBITCNT;

typedef struct
{
    unsigned int    bitcount:32;
}ve_BITSTCNT;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    to_value:24;
}ve_BSTTIMER;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    bitcount:24;
}ve_PINSTCLIM;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    bs_base:29;
}ve_BSBASE;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    bs_limit:29;
}ve_BSLIMIT;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    wr_ptr:29;
}ve_BSWRPTR;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    rd_ptr:29;
}ve_BSRDPTR;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    cur_ptr:29;
}ve_BSCURPTR;

typedef struct
{
    unsigned int    dec_bit_ptr:32;
}ve_DECBSPTR;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    write_enable5:1;
    unsigned int    rpt_botline:3;
    unsigned int    rpt_topline:3;
    unsigned int    write_enable4:1;
    unsigned int    rpt_rightpel:3;
    unsigned int    rpt_leftpel:3;
    unsigned int    write_enable3:1;
    unsigned int    start_tap:4;
    unsigned int    write_enable2:1;
    unsigned int    tapnum:4;
    unsigned int    write_enable1:1;
    unsigned int    filt_prec:3;
}ve_FILTCNTL;

typedef struct
{
    unsigned int    reserved_0:9;
    unsigned int    init_value:23;
}ve_FILTINIT;

typedef struct
{
    unsigned int    reserved_0:27;
    unsigned int    alpha_loc:1;
    unsigned int    alpha_enable:1;
    unsigned int    color_key_enable:1;
    unsigned int    format:2;
}ve_CKCNTL;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    color_key2:8;
    unsigned int    color_key1:8;
    unsigned int    color_key0:8;
}ve_CKDATA;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    rshift_size:3;
    unsigned int    reserved_1:1;
    unsigned int    t2:8;
    unsigned int    k1:8;
    unsigned int    t1:8;
}ve_ADAPCNTL;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    alpha:8;
}ve_ALPHA;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    thr_2:4;
    unsigned int    thr_1:4;
}ve_DEBLKCNTL;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    dc_value:8;
}ve_DCVAL;

typedef struct
{
    unsigned int    thr_4:8;
    unsigned int    thr_3:8;
    unsigned int    thr_2:8;
    unsigned int    thr_1:8;
}ve_BLKD_THR;

typedef struct
{
    unsigned int    weight_5:8;
    unsigned int    weight_4:8;
    unsigned int    weight_3:8;
    unsigned int    weight_2:8;
}ve_BLKD_WEIGHT;

typedef struct
{
    unsigned int    reserved_0:31;
    unsigned int    qpel_format:1;
}ve_QPEL_FORMAT;

typedef struct
{
    unsigned int    thr_4:8;
    unsigned int    thr_3:8;
    unsigned int    thr_2:8;
    unsigned int    thr_1:8;
}ve_IMPULSE_THR;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    thr_7:8;
    unsigned int    thr_6:8;
    unsigned int    thr_5:8;
}ve_IMPULSE_THR2;

typedef struct
{
    unsigned int    reserved_0:30;
    unsigned int    chroma_enable:1;
    unsigned int    luma_enable:1;
}ve_DERING_CTRL;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    reserved_1:5;
    unsigned int    coeffnplus1:9;
    unsigned int    reserved_2:7;
    unsigned int    coeffn:9;
}ve_TAPCOEFF;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    cur_cr_cbp:4;
    unsigned int    cur_cb_cbp:4;
    unsigned int    cur_lu_cbp:16;
}ve_RM_CUR_CBP;

typedef struct
{
    unsigned int    reserved_0:13;
    unsigned int    ul_cr_cbp:1;
    unsigned int    ul_cb_cbp:1;
    unsigned int    ul_lu_cbp:1;
    unsigned int    up_cr_cbp:2;
    unsigned int    up_cb_cbp:2;
    unsigned int    up_lu_cbp:4;
    unsigned int    left_cr_cbp:2;
    unsigned int    left_cb_cbp:2;
    unsigned int    left_lu_cbp:4;
}ve_RM_NBR_CBP;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    ul_mvd:1;
    unsigned int    up_mvd:4;
    unsigned int    left_mvd:4;
    unsigned int    cur_mvd:16;
}ve_RM_MVD;

typedef struct
{
    unsigned int    reserved_0:28;
    unsigned int    ul_str_eq2:1;
    unsigned int    up_str_eq2:1;
    unsigned int    left_str_eq2:1;
    unsigned int    cur_str_eq2:1;
}ve_RM_BS;

typedef struct
{
    unsigned int    write_enable2:1;
    unsigned int    refqp:5;
    unsigned int    beta2sel:1;
    unsigned int    write_enable1:1;
    unsigned int    up_ul_refdiff:1;
    unsigned int    left_ul_refdiff:1;
    unsigned int    cur_u_refdiff:1;
    unsigned int    cur_l_refdiff:1;
    unsigned int    qp_ul:5;
    unsigned int    qp_up:5;
    unsigned int    qp_left:5;
    unsigned int    qp:5;
}ve_RMBS_QP;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    str6_initqp:5;
    unsigned int    str5_initqp:5;
    unsigned int    str4_initqp:5;
    unsigned int    str3_initqp:5;
    unsigned int    str2_initqp:5;
    unsigned int    str1_initqp:5;
}ve_RV8_STR_MAP0;

typedef struct
{
    unsigned int    reserved_0:17;
    unsigned int    str9_initqp:5;
    unsigned int    str8_initqp:5;
    unsigned int    str7_initqp:5;
}ve_RV8_STR_MAP1;

typedef struct
{
    unsigned int    reserved_0:27;
    unsigned int    write_enable2:1;
    unsigned int    is_key_frame:1;
    unsigned int    chroma_only:1;
    unsigned int    write_enable1:1;
    unsigned int    sel_s_chroma_deblock:1;
}ve_RV8_CTRL;

typedef struct
{
    unsigned int    reserved_0:29;
    unsigned int    belowmb_refdiff_en:1;
    unsigned int    subblk2clip_ch:1;
    unsigned int    subblk12clip_lu:1;
}ve_RV9_CLIP;

typedef struct
{
    unsigned int    reserved_0:28;
    unsigned int    rv89_mode:4;
}ve_RV_MODE;

typedef struct
{
    unsigned int    reserved_0:31;
    unsigned int    u_cur_refdiff:1;
}ve_BELOWMB_REFDIFF;

typedef struct
{
    unsigned int    str_inc:32;
}ve_RV8_PFILTSTR;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    uravail:1;
    unsigned int    uavail:1;
    unsigned int    lavail:1;
    unsigned int    imode:1;
    unsigned int    weighted_pred:1;
    unsigned int    mb_type:2;
    unsigned int    intra:1;
}ve_RMPREDCCTL;

typedef struct
{
    unsigned int    intrap7:4;
    unsigned int    intrap6:4;
    unsigned int    intrap5:4;
    unsigned int    intrap4:4;
    unsigned int    intrap3:4;
    unsigned int    intrap2:4;
    unsigned int    intrap1:4;
    unsigned int    intrap0:4;
}ve_RMINTRAM0;

typedef struct
{
    unsigned int    intrap15:4;
    unsigned int    intrap14:4;
    unsigned int    intrap13:4;
    unsigned int    intrap12:4;
    unsigned int    intrap11:4;
    unsigned int    intrap10:4;
    unsigned int    intrap9:4;
    unsigned int    intrap8:4;
}ve_RMINTRAM1;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    coeff1:14;
    unsigned int    reserved_1:2;
    unsigned int    coeff0:14;
}ve_RMCOEFF;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    init_phase:25;
}ve_PHASE_INIT;

typedef struct
{
    unsigned int    reserved_0:15;
    unsigned int    phase_inc:17;
}ve_PHASE_INC;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    reserved_1:3;
    unsigned int    final_phase:25;
}ve_PHASE_OUT;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    coeffnplus1:14;
    unsigned int    reserved_1:2;
    unsigned int    coeffn:14;
}ve_TAPCOEFF1;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    coeffnplus1:14;
    unsigned int    reserved_1:2;
    unsigned int    coeffn:14;
}ve_TAPCOEFF2;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    rcrpr:1;
    unsigned int    color_cr:8;
    unsigned int    color_cb:8;
    unsigned int    color_y:8;
    unsigned int    fill_mode:2;
}ve_RMRPR_CNTL;

typedef struct
{
    unsigned int    reserved_0:17;
    unsigned int    m:4;
    unsigned int    pixel_offset:11;
}ve_RMRPR_PAR;

typedef struct
{
    unsigned int    ax:32;
}ve_RMRPR_AX;

typedef struct
{
    unsigned int    ay:32;
}ve_RMRPR_AY;

typedef struct
{
    unsigned int    ax_inc:32;
}ve_RMRPR_AXINC;

typedef struct
{
    unsigned int    reserved_0:19;
    unsigned int    picmb_h:6;
    unsigned int    picmb_w:7;
}ve_RMRPR_PICINFO;

typedef struct
{
    unsigned int    reserved_0:20;
    unsigned int    basea:12;
}ve_BASEA;

typedef struct
{
    unsigned int    reserved_0:20;
    unsigned int    offseta:12;
}ve_OFFSETA;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    x:13;
    unsigned int    y:14;
}ve_DMAREG1;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    field_frame:1;
    unsigned int    decimated:2;
    unsigned int    reserved_1:2;
    unsigned int    bot_addr_idx:6;
    unsigned int    reserved_2:2;
    unsigned int    top_addr_idx:6;
    unsigned int    post_inc_sel:1;
    unsigned int    reserved_3:1;
    unsigned int    post_inc:6;
}ve_DMAREG2;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    line_off:1;
    unsigned int    vm_pitch:7;
    unsigned int    vm_addr:9;
    unsigned int    h:6;
    unsigned int    w:6;
}ve_DMAREG3;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    write_enable3:1;
    unsigned int    q_sample:1;
    unsigned int    write_enable2:1;
    unsigned int    rnd_cntl:1;
    unsigned int    write_enable1:1;
    unsigned int    h:11;
    unsigned int    w:11;
}ve_VMCNTL;
#endif

#define VE_CNTL                                                       0x1800A000
#define VE_CNTL_reg_addr                                              "0xB800A000"
#define VE_CNTL_reg                                                   0xB800A000
#define VE_CNTL_inst_addr                                             "0x0000"
#define VE_CNTL_inst                                                  0x0000
#define VE_CNTL_dering_dbg_sel_shift                                  (20)
#define VE_CNTL_vmblk_idle_shift                                      (19)
#define VE_CNTL_dbg_group2_sel_shift                                  (14)
#define VE_CNTL_dbg_group1_sel_shift                                  (9)
#define VE_CNTL_dbg_out_en_shift                                      (8)
#define VE_CNTL_codblk_mode1_shift                                    (7)
#define VE_CNTL_codblk_mode0_shift                                    (6)
#define VE_CNTL_codblk_mode_shift                                     (6)
#define VE_CNTL_haltve_done_shift                                     (5)
#define VE_CNTL_haltve_shift                                          (4)
#define VE_CNTL_veidle_shift                                          (3)
#define VE_CNTL_inten_shift                                           (2)
#define VE_CNTL_reset_ptr_shift                                       (1)
#define VE_CNTL_write_data_shift                                      (0)
#define VE_CNTL_dering_dbg_sel_mask                                   (0x00700000)
#define VE_CNTL_vmblk_idle_mask                                       (0x00080000)
#define VE_CNTL_dbg_group2_sel_mask                                   (0x0007C000)
#define VE_CNTL_dbg_group1_sel_mask                                   (0x00003E00)
#define VE_CNTL_dbg_out_en_mask                                       (0x00000100)
#define VE_CNTL_codblk_mode1_mask                                     (0x00000080)
#define VE_CNTL_codblk_mode0_mask                                     (0x00000040)
#define VE_CNTL_codblk_mode_mask                                      (0x000000C0)
#define VE_CNTL_haltve_done_mask                                      (0x00000020)
#define VE_CNTL_haltve_mask                                           (0x00000010)
#define VE_CNTL_veidle_mask                                           (0x00000008)
#define VE_CNTL_inten_mask                                            (0x00000004)
#define VE_CNTL_reset_ptr_mask                                        (0x00000002)
#define VE_CNTL_write_data_mask                                       (0x00000001)
#define VE_CNTL_dering_dbg_sel(data)                                  (0x00700000&((data)<<20))
#define VE_CNTL_vmblk_idle(data)                                      (0x00080000&((data)<<19))
#define VE_CNTL_dbg_group2_sel(data)                                  (0x0007C000&((data)<<14))
#define VE_CNTL_dbg_group1_sel(data)                                  (0x00003E00&((data)<<9))
#define VE_CNTL_dbg_out_en(data)                                      (0x00000100&((data)<<8))
#define VE_CNTL_codblk_mode1(data)                                    (0x00000080&((data)<<7))
#define VE_CNTL_codblk_mode0(data)                                    (0x00000040&((data)<<6))
#define VE_CNTL_codblk_mode(data)                                     (0x000000C0&((data)<<6))
#define VE_CNTL_haltve_done(data)                                     (0x00000020&((data)<<5))
#define VE_CNTL_haltve(data)                                          (0x00000010&((data)<<4))
#define VE_CNTL_veidle(data)                                          (0x00000008&((data)<<3))
#define VE_CNTL_inten(data)                                           (0x00000004&((data)<<2))
#define VE_CNTL_reset_ptr(data)                                       (0x00000002&((data)<<1))
#define VE_CNTL_write_data(data)                                      (0x00000001&(data))
#define VE_CNTL_get_dering_dbg_sel(data)                              ((0x00700000&(data))>>20)
#define VE_CNTL_get_vmblk_idle(data)                                  ((0x00080000&(data))>>19)
#define VE_CNTL_get_dbg_group2_sel(data)                              ((0x0007C000&(data))>>14)
#define VE_CNTL_get_dbg_group1_sel(data)                              ((0x00003E00&(data))>>9)
#define VE_CNTL_get_dbg_out_en(data)                                  ((0x00000100&(data))>>8)
#define VE_CNTL_get_codblk_mode1(data)                                ((0x00000080&(data))>>7)
#define VE_CNTL_get_codblk_mode0(data)                                ((0x00000040&(data))>>6)
#define VE_CNTL_get_codblk_mode(data)                                 ((0x000000C0&(data))>>6)
#define VE_CNTL_get_haltve_done(data)                                 ((0x00000020&(data))>>5)
#define VE_CNTL_get_haltve(data)                                      ((0x00000010&(data))>>4)
#define VE_CNTL_get_veidle(data)                                      ((0x00000008&(data))>>3)
#define VE_CNTL_get_inten(data)                                       ((0x00000004&(data))>>2)
#define VE_CNTL_get_reset_ptr(data)                                   ((0x00000002&(data))>>1)
#define VE_CNTL_get_write_data(data)                                  (0x00000001&(data))

#define VE_INT_STATUS                                                 0x1800A004
#define VE_INT_STATUS_reg_addr                                        "0xB800A004"
#define VE_INT_STATUS_reg                                             0xB800A004
#define VE_INT_STATUS_inst_addr                                       "0x0001"
#define VE_INT_STATUS_inst                                            0x0001
#define VE_INT_STATUS_first_error_b3_shift                            (19)
#define VE_INT_STATUS_first_error_b2_shift                            (18)
#define VE_INT_STATUS_first_error_b1_shift                            (17)
#define VE_INT_STATUS_first_error_b0_shift                            (16)
#define VE_INT_STATUS_first_error_shift                               (16)
#define VE_INT_STATUS_mt64coeff_shift                                 (7)
#define VE_INT_STATUS_rstff_oflow_shift                               (6)
#define VE_INT_STATUS_rstff_empty_shift                               (5)
#define VE_INT_STATUS_bitst_fifo_shift                                (4)
#define VE_INT_STATUS_unexp_inst_shift                                (3)
#define VE_INT_STATUS_scode_limit_shift                               (2)
#define VE_INT_STATUS_dec_bitst_shift                                 (1)
#define VE_INT_STATUS_write_data_shift                                (0)
#define VE_INT_STATUS_first_error_b3_mask                             (0x00080000)
#define VE_INT_STATUS_first_error_b2_mask                             (0x00040000)
#define VE_INT_STATUS_first_error_b1_mask                             (0x00020000)
#define VE_INT_STATUS_first_error_b0_mask                             (0x00010000)
#define VE_INT_STATUS_first_error_mask                                (0x000F0000)
#define VE_INT_STATUS_mt64coeff_mask                                  (0x00000080)
#define VE_INT_STATUS_rstff_oflow_mask                                (0x00000040)
#define VE_INT_STATUS_rstff_empty_mask                                (0x00000020)
#define VE_INT_STATUS_bitst_fifo_mask                                 (0x00000010)
#define VE_INT_STATUS_unexp_inst_mask                                 (0x00000008)
#define VE_INT_STATUS_scode_limit_mask                                (0x00000004)
#define VE_INT_STATUS_dec_bitst_mask                                  (0x00000002)
#define VE_INT_STATUS_write_data_mask                                 (0x00000001)
#define VE_INT_STATUS_first_error_b3(data)                            (0x00080000&((data)<<19))
#define VE_INT_STATUS_first_error_b2(data)                            (0x00040000&((data)<<18))
#define VE_INT_STATUS_first_error_b1(data)                            (0x00020000&((data)<<17))
#define VE_INT_STATUS_first_error_b0(data)                            (0x00010000&((data)<<16))
#define VE_INT_STATUS_first_error(data)                               (0x000F0000&((data)<<16))
#define VE_INT_STATUS_mt64coeff(data)                                 (0x00000080&((data)<<7))
#define VE_INT_STATUS_rstff_oflow(data)                               (0x00000040&((data)<<6))
#define VE_INT_STATUS_rstff_empty(data)                               (0x00000020&((data)<<5))
#define VE_INT_STATUS_bitst_fifo(data)                                (0x00000010&((data)<<4))
#define VE_INT_STATUS_unexp_inst(data)                                (0x00000008&((data)<<3))
#define VE_INT_STATUS_scode_limit(data)                               (0x00000004&((data)<<2))
#define VE_INT_STATUS_dec_bitst(data)                                 (0x00000002&((data)<<1))
#define VE_INT_STATUS_write_data(data)                                (0x00000001&(data))
#define VE_INT_STATUS_get_first_error_b3(data)                        ((0x00080000&(data))>>19)
#define VE_INT_STATUS_get_first_error_b2(data)                        ((0x00040000&(data))>>18)
#define VE_INT_STATUS_get_first_error_b1(data)                        ((0x00020000&(data))>>17)
#define VE_INT_STATUS_get_first_error_b0(data)                        ((0x00010000&(data))>>16)
#define VE_INT_STATUS_get_first_error(data)                           ((0x000F0000&(data))>>16)
#define VE_INT_STATUS_get_mt64coeff(data)                             ((0x00000080&(data))>>7)
#define VE_INT_STATUS_get_rstff_oflow(data)                           ((0x00000040&(data))>>6)
#define VE_INT_STATUS_get_rstff_empty(data)                           ((0x00000020&(data))>>5)
#define VE_INT_STATUS_get_bitst_fifo(data)                            ((0x00000010&(data))>>4)
#define VE_INT_STATUS_get_unexp_inst(data)                            ((0x00000008&(data))>>3)
#define VE_INT_STATUS_get_scode_limit(data)                           ((0x00000004&(data))>>2)
#define VE_INT_STATUS_get_dec_bitst(data)                             ((0x00000002&(data))>>1)
#define VE_INT_STATUS_get_write_data(data)                            (0x00000001&(data))

#define VE_INTEN                                                      0x1800A008
#define VE_INTEN_reg_addr                                             "0xB800A008"
#define VE_INTEN_reg                                                  0xB800A008
#define VE_INTEN_inst_addr                                            "0x0002"
#define VE_INTEN_inst                                                 0x0002
#define VE_INTEN_mt64coeff_shift                                      (7)
#define VE_INTEN_rstff_oflow_shift                                    (6)
#define VE_INTEN_rstff_empty_shift                                    (5)
#define VE_INTEN_bitst_fifo_shift                                     (4)
#define VE_INTEN_unexp_inst_shift                                     (3)
#define VE_INTEN_scode_limit_shift                                    (2)
#define VE_INTEN_dec_bitst_shift                                      (1)
#define VE_INTEN_write_data_shift                                     (0)
#define VE_INTEN_mt64coeff_mask                                       (0x00000080)
#define VE_INTEN_rstff_oflow_mask                                     (0x00000040)
#define VE_INTEN_rstff_empty_mask                                     (0x00000020)
#define VE_INTEN_bitst_fifo_mask                                      (0x00000010)
#define VE_INTEN_unexp_inst_mask                                      (0x00000008)
#define VE_INTEN_scode_limit_mask                                     (0x00000004)
#define VE_INTEN_dec_bitst_mask                                       (0x00000002)
#define VE_INTEN_write_data_mask                                      (0x00000001)
#define VE_INTEN_mt64coeff(data)                                      (0x00000080&((data)<<7))
#define VE_INTEN_rstff_oflow(data)                                    (0x00000040&((data)<<6))
#define VE_INTEN_rstff_empty(data)                                    (0x00000020&((data)<<5))
#define VE_INTEN_bitst_fifo(data)                                     (0x00000010&((data)<<4))
#define VE_INTEN_unexp_inst(data)                                     (0x00000008&((data)<<3))
#define VE_INTEN_scode_limit(data)                                    (0x00000004&((data)<<2))
#define VE_INTEN_dec_bitst(data)                                      (0x00000002&((data)<<1))
#define VE_INTEN_write_data(data)                                     (0x00000001&(data))
#define VE_INTEN_get_mt64coeff(data)                                  ((0x00000080&(data))>>7)
#define VE_INTEN_get_rstff_oflow(data)                                ((0x00000040&(data))>>6)
#define VE_INTEN_get_rstff_empty(data)                                ((0x00000020&(data))>>5)
#define VE_INTEN_get_bitst_fifo(data)                                 ((0x00000010&(data))>>4)
#define VE_INTEN_get_unexp_inst(data)                                 ((0x00000008&(data))>>3)
#define VE_INTEN_get_scode_limit(data)                                ((0x00000004&(data))>>2)
#define VE_INTEN_get_dec_bitst(data)                                  ((0x00000002&(data))>>1)
#define VE_INTEN_get_write_data(data)                                 (0x00000001&(data))

#define VE_FIFOSTATE                                                  0x1800A020
#define VE_FIFOSTATE_reg_addr                                         "0xB800A020"
#define VE_FIFOSTATE_reg                                              0xB800A020
#define VE_FIFOSTATE_inst_addr                                        "0x0008"
#define VE_FIFOSTATE_inst                                             0x0008
#define VE_FIFOSTATE_codenum_shift                                    (23)
#define VE_FIFOSTATE_vspnum_shift                                     (17)
#define VE_FIFOSTATE_dmanum_shift                                     (11)
#define VE_FIFOSTATE_maxfifo_shift                                    (5)
#define VE_FIFOSTATE_rstnum_shift                                     (0)
#define VE_FIFOSTATE_codenum_mask                                     (0x1F800000)
#define VE_FIFOSTATE_vspnum_mask                                      (0x007E0000)
#define VE_FIFOSTATE_dmanum_mask                                      (0x0001F800)
#define VE_FIFOSTATE_maxfifo_mask                                     (0x000007E0)
#define VE_FIFOSTATE_rstnum_mask                                      (0x0000001F)
#define VE_FIFOSTATE_codenum(data)                                    (0x1F800000&((data)<<23))
#define VE_FIFOSTATE_vspnum(data)                                     (0x007E0000&((data)<<17))
#define VE_FIFOSTATE_dmanum(data)                                     (0x0001F800&((data)<<11))
#define VE_FIFOSTATE_maxfifo(data)                                    (0x000007E0&((data)<<5))
#define VE_FIFOSTATE_rstnum(data)                                     (0x0000001F&(data))
#define VE_FIFOSTATE_get_codenum(data)                                ((0x1F800000&(data))>>23)
#define VE_FIFOSTATE_get_vspnum(data)                                 ((0x007E0000&(data))>>17)
#define VE_FIFOSTATE_get_dmanum(data)                                 ((0x0001F800&(data))>>11)
#define VE_FIFOSTATE_get_maxfifo(data)                                ((0x000007E0&(data))>>5)
#define VE_FIFOSTATE_get_rstnum(data)                                 (0x0000001F&(data))

#define VE_PCCNTL                                                     0x1800A030
#define VE_PCCNTL_reg_addr                                            "0xB800A030"
#define VE_PCCNTL_reg                                                 0xB800A030
#define VE_PCCNTL_inst_addr                                           "0x000C"
#define VE_PCCNTL_inst                                                0x000C
#define VE_PCCNTL_write_enable7_shift                                 (23)
#define VE_PCCNTL_img_rsltstall_enable_shift                          (22)
#define VE_PCCNTL_write_enable6_shift                                 (21)
#define VE_PCCNTL_dct_rsltstall_enable_shift                          (20)
#define VE_PCCNTL_dct_cmstall_enable_shift                            (19)
#define VE_PCCNTL_write_enable5_shift                                 (18)
#define VE_PCCNTL_vlc_cmstall_enable_shift                            (17)
#define VE_PCCNTL_vlc_bsstall_enable_shift                            (16)
#define VE_PCCNTL_write_enable4_shift                                 (15)
#define VE_PCCNTL_vld_rsltstall_enable_shift                          (14)
#define VE_PCCNTL_vld_cmstall_enable_shift                            (13)
#define VE_PCCNTL_vld_bsstall_enable_shift                            (12)
#define VE_PCCNTL_write_enable3_shift                                 (11)
#define VE_PCCNTL_pc2_src_shift                                       (9)
#define VE_PCCNTL_pc2_enable_shift                                    (8)
#define VE_PCCNTL_write_enable2_shift                                 (7)
#define VE_PCCNTL_pc1_src_shift                                       (6)
#define VE_PCCNTL_reserved1_shift                                     (5)
#define VE_PCCNTL_pc1_enable_shift                                    (4)
#define VE_PCCNTL_write_enable1_shift                                 (3)
#define VE_PCCNTL_pc0_src_shift                                       (2)
#define VE_PCCNTL_reserved0_shift                                     (1)
#define VE_PCCNTL_pc0_enable_shift                                    (0)
#define VE_PCCNTL_write_enable7_mask                                  (0x00800000)
#define VE_PCCNTL_img_rsltstall_enable_mask                           (0x00400000)
#define VE_PCCNTL_write_enable6_mask                                  (0x00200000)
#define VE_PCCNTL_dct_rsltstall_enable_mask                           (0x00100000)
#define VE_PCCNTL_dct_cmstall_enable_mask                             (0x00080000)
#define VE_PCCNTL_write_enable5_mask                                  (0x00040000)
#define VE_PCCNTL_vlc_cmstall_enable_mask                             (0x00020000)
#define VE_PCCNTL_vlc_bsstall_enable_mask                             (0x00010000)
#define VE_PCCNTL_write_enable4_mask                                  (0x00008000)
#define VE_PCCNTL_vld_rsltstall_enable_mask                           (0x00004000)
#define VE_PCCNTL_vld_cmstall_enable_mask                             (0x00002000)
#define VE_PCCNTL_vld_bsstall_enable_mask                             (0x00001000)
#define VE_PCCNTL_write_enable3_mask                                  (0x00000800)
#define VE_PCCNTL_pc2_src_mask                                        (0x00000600)
#define VE_PCCNTL_pc2_enable_mask                                     (0x00000100)
#define VE_PCCNTL_write_enable2_mask                                  (0x00000080)
#define VE_PCCNTL_pc1_src_mask                                        (0x00000040)
#define VE_PCCNTL_reserved1_mask                                      (0x00000020)
#define VE_PCCNTL_pc1_enable_mask                                     (0x00000010)
#define VE_PCCNTL_write_enable1_mask                                  (0x00000008)
#define VE_PCCNTL_pc0_src_mask                                        (0x00000004)
#define VE_PCCNTL_reserved0_mask                                      (0x00000002)
#define VE_PCCNTL_pc0_enable_mask                                     (0x00000001)
#define VE_PCCNTL_write_enable7(data)                                 (0x00800000&((data)<<23))
#define VE_PCCNTL_img_rsltstall_enable(data)                          (0x00400000&((data)<<22))
#define VE_PCCNTL_write_enable6(data)                                 (0x00200000&((data)<<21))
#define VE_PCCNTL_dct_rsltstall_enable(data)                          (0x00100000&((data)<<20))
#define VE_PCCNTL_dct_cmstall_enable(data)                            (0x00080000&((data)<<19))
#define VE_PCCNTL_write_enable5(data)                                 (0x00040000&((data)<<18))
#define VE_PCCNTL_vlc_cmstall_enable(data)                            (0x00020000&((data)<<17))
#define VE_PCCNTL_vlc_bsstall_enable(data)                            (0x00010000&((data)<<16))
#define VE_PCCNTL_write_enable4(data)                                 (0x00008000&((data)<<15))
#define VE_PCCNTL_vld_rsltstall_enable(data)                          (0x00004000&((data)<<14))
#define VE_PCCNTL_vld_cmstall_enable(data)                            (0x00002000&((data)<<13))
#define VE_PCCNTL_vld_bsstall_enable(data)                            (0x00001000&((data)<<12))
#define VE_PCCNTL_write_enable3(data)                                 (0x00000800&((data)<<11))
#define VE_PCCNTL_pc2_src(data)                                       (0x00000600&((data)<<9))
#define VE_PCCNTL_pc2_enable(data)                                    (0x00000100&((data)<<8))
#define VE_PCCNTL_write_enable2(data)                                 (0x00000080&((data)<<7))
#define VE_PCCNTL_pc1_src(data)                                       (0x00000040&((data)<<6))
#define VE_PCCNTL_reserved1(data)                                     (0x00000020&((data)<<5))
#define VE_PCCNTL_pc1_enable(data)                                    (0x00000010&((data)<<4))
#define VE_PCCNTL_write_enable1(data)                                 (0x00000008&((data)<<3))
#define VE_PCCNTL_pc0_src(data)                                       (0x00000004&((data)<<2))
#define VE_PCCNTL_reserved0(data)                                     (0x00000002&((data)<<1))
#define VE_PCCNTL_pc0_enable(data)                                    (0x00000001&(data))
#define VE_PCCNTL_get_write_enable7(data)                             ((0x00800000&(data))>>23)
#define VE_PCCNTL_get_img_rsltstall_enable(data)                      ((0x00400000&(data))>>22)
#define VE_PCCNTL_get_write_enable6(data)                             ((0x00200000&(data))>>21)
#define VE_PCCNTL_get_dct_rsltstall_enable(data)                      ((0x00100000&(data))>>20)
#define VE_PCCNTL_get_dct_cmstall_enable(data)                        ((0x00080000&(data))>>19)
#define VE_PCCNTL_get_write_enable5(data)                             ((0x00040000&(data))>>18)
#define VE_PCCNTL_get_vlc_cmstall_enable(data)                        ((0x00020000&(data))>>17)
#define VE_PCCNTL_get_vlc_bsstall_enable(data)                        ((0x00010000&(data))>>16)
#define VE_PCCNTL_get_write_enable4(data)                             ((0x00008000&(data))>>15)
#define VE_PCCNTL_get_vld_rsltstall_enable(data)                      ((0x00004000&(data))>>14)
#define VE_PCCNTL_get_vld_cmstall_enable(data)                        ((0x00002000&(data))>>13)
#define VE_PCCNTL_get_vld_bsstall_enable(data)                        ((0x00001000&(data))>>12)
#define VE_PCCNTL_get_write_enable3(data)                             ((0x00000800&(data))>>11)
#define VE_PCCNTL_get_pc2_src(data)                                   ((0x00000600&(data))>>9)
#define VE_PCCNTL_get_pc2_enable(data)                                ((0x00000100&(data))>>8)
#define VE_PCCNTL_get_write_enable2(data)                             ((0x00000080&(data))>>7)
#define VE_PCCNTL_get_pc1_src(data)                                   ((0x00000040&(data))>>6)
#define VE_PCCNTL_get_reserved1(data)                                 ((0x00000020&(data))>>5)
#define VE_PCCNTL_get_pc1_enable(data)                                ((0x00000010&(data))>>4)
#define VE_PCCNTL_get_write_enable1(data)                             ((0x00000008&(data))>>3)
#define VE_PCCNTL_get_pc0_src(data)                                   ((0x00000004&(data))>>2)
#define VE_PCCNTL_get_reserved0(data)                                 ((0x00000002&(data))>>1)
#define VE_PCCNTL_get_pc0_enable(data)                                (0x00000001&(data))

#define VE_PC0                                                        0x1800A034
#define VE_PC0_reg_addr                                               "0xB800A034"
#define VE_PC0_reg                                                    0xB800A034
#define VE_PC0_inst_addr                                              "0x000D"
#define VE_PC0_inst                                                   0x000D
#define VE_PC0_perf_counter0_shift                                    (0)
#define VE_PC0_perf_counter0_mask                                     (0xFFFFFFFF)
#define VE_PC0_perf_counter0(data)                                    (0xFFFFFFFF&(data))
#define VE_PC0_get_perf_counter0(data)                                (0xFFFFFFFF&(data))

#define VE_PC1                                                        0x1800A038
#define VE_PC1_reg_addr                                               "0xB800A038"
#define VE_PC1_reg                                                    0xB800A038
#define VE_PC1_inst_addr                                              "0x000E"
#define VE_PC1_inst                                                   0x000E
#define VE_PC1_perf_counter1_shift                                    (0)
#define VE_PC1_perf_counter1_mask                                     (0xFFFFFFFF)
#define VE_PC1_perf_counter1(data)                                    (0xFFFFFFFF&(data))
#define VE_PC1_get_perf_counter1(data)                                (0xFFFFFFFF&(data))

#define VE_PC2                                                        0x1800A03C
#define VE_PC2_reg_addr                                               "0xB800A03C"
#define VE_PC2_reg                                                    0xB800A03C
#define VE_PC2_inst_addr                                              "0x000F"
#define VE_PC2_inst                                                   0x000F
#define VE_PC2_perf_counter2_shift                                    (0)
#define VE_PC2_perf_counter2_mask                                     (0xFFFFFFFF)
#define VE_PC2_perf_counter2(data)                                    (0xFFFFFFFF&(data))
#define VE_PC2_get_perf_counter2(data)                                (0xFFFFFFFF&(data))

#define VE_DCTCNTL                                                    0x1800A080
#define VE_DCTCNTL_reg_addr                                           "0xB800A080"
#define VE_DCTCNTL_reg                                                0xB800A080
#define VE_DCTCNTL_inst_addr                                          "0x0020"
#define VE_DCTCNTL_inst                                               0x0020
#define VE_DCTCNTL_write_enable8_shift                                (27)
#define VE_DCTCNTL_quant_type_shift                                   (26)
#define VE_DCTCNTL_write_enable6_shift                                (25)
#define VE_DCTCNTL_quant_msk_shift                                    (17)
#define VE_DCTCNTL_write_enable5_shift                                (16)
#define VE_DCTCNTL_ch_conv_shift                                      (15)
#define VE_DCTCNTL_write_enable4_shift                                (14)
#define VE_DCTCNTL_intra_shift                                        (13)
#define VE_DCTCNTL_write_enable3_shift                                (12)
#define VE_DCTCNTL_qst_shift                                          (11)
#define VE_DCTCNTL_write_enable2_shift                                (10)
#define VE_DCTCNTL_qsc_shift                                          (5)
#define VE_DCTCNTL_write_enable1_shift                                (4)
#define VE_DCTCNTL_id_pred_shift                                      (2)
#define VE_DCTCNTL_write_enable_shift                                 (1)
#define VE_DCTCNTL_field_dct_shift                                    (0)
#define VE_DCTCNTL_write_enable8_mask                                 (0x08000000)
#define VE_DCTCNTL_quant_type_mask                                    (0x04000000)
#define VE_DCTCNTL_write_enable6_mask                                 (0x02000000)
#define VE_DCTCNTL_quant_msk_mask                                     (0x01FE0000)
#define VE_DCTCNTL_write_enable5_mask                                 (0x00010000)
#define VE_DCTCNTL_ch_conv_mask                                       (0x00008000)
#define VE_DCTCNTL_write_enable4_mask                                 (0x00004000)
#define VE_DCTCNTL_intra_mask                                         (0x00002000)
#define VE_DCTCNTL_write_enable3_mask                                 (0x00001000)
#define VE_DCTCNTL_qst_mask                                           (0x00000800)
#define VE_DCTCNTL_write_enable2_mask                                 (0x00000400)
#define VE_DCTCNTL_qsc_mask                                           (0x000003E0)
#define VE_DCTCNTL_write_enable1_mask                                 (0x00000010)
#define VE_DCTCNTL_id_pred_mask                                       (0x0000000C)
#define VE_DCTCNTL_write_enable_mask                                  (0x00000002)
#define VE_DCTCNTL_field_dct_mask                                     (0x00000001)
#define VE_DCTCNTL_write_enable8(data)                                (0x08000000&((data)<<27))
#define VE_DCTCNTL_quant_type(data)                                   (0x04000000&((data)<<26))
#define VE_DCTCNTL_write_enable6(data)                                (0x02000000&((data)<<25))
#define VE_DCTCNTL_quant_msk(data)                                    (0x01FE0000&((data)<<17))
#define VE_DCTCNTL_write_enable5(data)                                (0x00010000&((data)<<16))
#define VE_DCTCNTL_ch_conv(data)                                      (0x00008000&((data)<<15))
#define VE_DCTCNTL_write_enable4(data)                                (0x00004000&((data)<<14))
#define VE_DCTCNTL_intra(data)                                        (0x00002000&((data)<<13))
#define VE_DCTCNTL_write_enable3(data)                                (0x00001000&((data)<<12))
#define VE_DCTCNTL_qst(data)                                          (0x00000800&((data)<<11))
#define VE_DCTCNTL_write_enable2(data)                                (0x00000400&((data)<<10))
#define VE_DCTCNTL_qsc(data)                                          (0x000003E0&((data)<<5))
#define VE_DCTCNTL_write_enable1(data)                                (0x00000010&((data)<<4))
#define VE_DCTCNTL_id_pred(data)                                      (0x0000000C&((data)<<2))
#define VE_DCTCNTL_write_enable(data)                                 (0x00000002&((data)<<1))
#define VE_DCTCNTL_field_dct(data)                                    (0x00000001&(data))
#define VE_DCTCNTL_get_write_enable8(data)                            ((0x08000000&(data))>>27)
#define VE_DCTCNTL_get_quant_type(data)                               ((0x04000000&(data))>>26)
#define VE_DCTCNTL_get_write_enable6(data)                            ((0x02000000&(data))>>25)
#define VE_DCTCNTL_get_quant_msk(data)                                ((0x01FE0000&(data))>>17)
#define VE_DCTCNTL_get_write_enable5(data)                            ((0x00010000&(data))>>16)
#define VE_DCTCNTL_get_ch_conv(data)                                  ((0x00008000&(data))>>15)
#define VE_DCTCNTL_get_write_enable4(data)                            ((0x00004000&(data))>>14)
#define VE_DCTCNTL_get_intra(data)                                    ((0x00002000&(data))>>13)
#define VE_DCTCNTL_get_write_enable3(data)                            ((0x00001000&(data))>>12)
#define VE_DCTCNTL_get_qst(data)                                      ((0x00000800&(data))>>11)
#define VE_DCTCNTL_get_write_enable2(data)                            ((0x00000400&(data))>>10)
#define VE_DCTCNTL_get_qsc(data)                                      ((0x000003E0&(data))>>5)
#define VE_DCTCNTL_get_write_enable1(data)                            ((0x00000010&(data))>>4)
#define VE_DCTCNTL_get_id_pred(data)                                  ((0x0000000C&(data))>>2)
#define VE_DCTCNTL_get_write_enable(data)                             ((0x00000002&(data))>>1)
#define VE_DCTCNTL_get_field_dct(data)                                (0x00000001&(data))

#define VE_CODECPARAM                                                 0x1800A084
#define VE_CODECPARAM_reg_addr                                        "0xB800A084"
#define VE_CODECPARAM_reg                                             0xB800A084
#define VE_CODECPARAM_inst_addr                                       "0x0021"
#define VE_CODECPARAM_inst                                            0x0021
#define VE_CODECPARAM_intra_round_dir_shift                           (18)
#define VE_CODECPARAM_intra_round_value_shift                         (15)
#define VE_CODECPARAM_inter_round_dir_shift                           (14)
#define VE_CODECPARAM_inter_round_value_shift                         (11)
#define VE_CODECPARAM_threshold_shift                                 (7)
#define VE_CODECPARAM_mb_pattern_shift                                (6)
#define VE_CODECPARAM_cbp_shift                                       (0)
#define VE_CODECPARAM_intra_round_dir_mask                            (0x00040000)
#define VE_CODECPARAM_intra_round_value_mask                          (0x00038000)
#define VE_CODECPARAM_inter_round_dir_mask                            (0x00004000)
#define VE_CODECPARAM_inter_round_value_mask                          (0x00003800)
#define VE_CODECPARAM_threshold_mask                                  (0x00000780)
#define VE_CODECPARAM_mb_pattern_mask                                 (0x00000040)
#define VE_CODECPARAM_cbp_mask                                        (0x0000003F)
#define VE_CODECPARAM_intra_round_dir(data)                           (0x00040000&((data)<<18))
#define VE_CODECPARAM_intra_round_value(data)                         (0x00038000&((data)<<15))
#define VE_CODECPARAM_inter_round_dir(data)                           (0x00004000&((data)<<14))
#define VE_CODECPARAM_inter_round_value(data)                         (0x00003800&((data)<<11))
#define VE_CODECPARAM_threshold(data)                                 (0x00000780&((data)<<7))
#define VE_CODECPARAM_mb_pattern(data)                                (0x00000040&((data)<<6))
#define VE_CODECPARAM_cbp(data)                                       (0x0000003F&(data))
#define VE_CODECPARAM_get_intra_round_dir(data)                       ((0x00040000&(data))>>18)
#define VE_CODECPARAM_get_intra_round_value(data)                     ((0x00038000&(data))>>15)
#define VE_CODECPARAM_get_inter_round_dir(data)                       ((0x00004000&(data))>>14)
#define VE_CODECPARAM_get_inter_round_value(data)                     ((0x00003800&(data))>>11)
#define VE_CODECPARAM_get_threshold(data)                             ((0x00000780&(data))>>7)
#define VE_CODECPARAM_get_mb_pattern(data)                            ((0x00000040&(data))>>6)
#define VE_CODECPARAM_get_cbp(data)                                   (0x0000003F&(data))

#define VE_CODECCNTL                                                  0x1800A100
#define VE_CODECCNTL_reg_addr                                         "0xB800A100"
#define VE_CODECCNTL_reg                                              0xB800A100
#define VE_CODECCNTL_inst_addr                                        "0x0040"
#define VE_CODECCNTL_inst                                             0x0040
#define VE_CODECCNTL_write_enable6_shift                              (31)
#define VE_CODECCNTL_bk_x_fcode_shift                                 (27)
#define VE_CODECCNTL_bk_y_fcode_shift                                 (23)
#define VE_CODECCNTL_write_enable5_shift                              (22)
#define VE_CODECCNTL_fo_x_fcode_shift                                 (18)
#define VE_CODECCNTL_fo_y_fcode_shift                                 (14)
#define VE_CODECCNTL_write_enable4_shift                              (13)
#define VE_CODECCNTL_max_xfer_size_shift                              (12)
#define VE_CODECCNTL_write_enable3_shift                              (11)
#define VE_CODECCNTL_min_xfer_size_shift                              (8)
#define VE_CODECCNTL_write_enable2_shift                              (7)
#define VE_CODECCNTL_pic_type_shift                                   (5)
#define VE_CODECCNTL_write_enable1_shift                              (4)
#define VE_CODECCNTL_coding_type_shift                                (0)
#define VE_CODECCNTL_write_enable6_mask                               (0x80000000)
#define VE_CODECCNTL_bk_x_fcode_mask                                  (0x78000000)
#define VE_CODECCNTL_bk_y_fcode_mask                                  (0x07800000)
#define VE_CODECCNTL_write_enable5_mask                               (0x00400000)
#define VE_CODECCNTL_fo_x_fcode_mask                                  (0x003C0000)
#define VE_CODECCNTL_fo_y_fcode_mask                                  (0x0003C000)
#define VE_CODECCNTL_write_enable4_mask                               (0x00002000)
#define VE_CODECCNTL_max_xfer_size_mask                               (0x00001000)
#define VE_CODECCNTL_write_enable3_mask                               (0x00000800)
#define VE_CODECCNTL_min_xfer_size_mask                               (0x00000700)
#define VE_CODECCNTL_write_enable2_mask                               (0x00000080)
#define VE_CODECCNTL_pic_type_mask                                    (0x00000060)
#define VE_CODECCNTL_write_enable1_mask                               (0x00000010)
#define VE_CODECCNTL_coding_type_mask                                 (0x0000000F)
#define VE_CODECCNTL_write_enable6(data)                              (0x80000000&((data)<<31))
#define VE_CODECCNTL_bk_x_fcode(data)                                 (0x78000000&((data)<<27))
#define VE_CODECCNTL_bk_y_fcode(data)                                 (0x07800000&((data)<<23))
#define VE_CODECCNTL_write_enable5(data)                              (0x00400000&((data)<<22))
#define VE_CODECCNTL_fo_x_fcode(data)                                 (0x003C0000&((data)<<18))
#define VE_CODECCNTL_fo_y_fcode(data)                                 (0x0003C000&((data)<<14))
#define VE_CODECCNTL_write_enable4(data)                              (0x00002000&((data)<<13))
#define VE_CODECCNTL_max_xfer_size(data)                              (0x00001000&((data)<<12))
#define VE_CODECCNTL_write_enable3(data)                              (0x00000800&((data)<<11))
#define VE_CODECCNTL_min_xfer_size(data)                              (0x00000700&((data)<<8))
#define VE_CODECCNTL_write_enable2(data)                              (0x00000080&((data)<<7))
#define VE_CODECCNTL_pic_type(data)                                   (0x00000060&((data)<<5))
#define VE_CODECCNTL_write_enable1(data)                              (0x00000010&((data)<<4))
#define VE_CODECCNTL_coding_type(data)                                (0x0000000F&(data))
#define VE_CODECCNTL_get_write_enable6(data)                          ((0x80000000&(data))>>31)
#define VE_CODECCNTL_get_bk_x_fcode(data)                             ((0x78000000&(data))>>27)
#define VE_CODECCNTL_get_bk_y_fcode(data)                             ((0x07800000&(data))>>23)
#define VE_CODECCNTL_get_write_enable5(data)                          ((0x00400000&(data))>>22)
#define VE_CODECCNTL_get_fo_x_fcode(data)                             ((0x003C0000&(data))>>18)
#define VE_CODECCNTL_get_fo_y_fcode(data)                             ((0x0003C000&(data))>>14)
#define VE_CODECCNTL_get_write_enable4(data)                          ((0x00002000&(data))>>13)
#define VE_CODECCNTL_get_max_xfer_size(data)                          ((0x00001000&(data))>>12)
#define VE_CODECCNTL_get_write_enable3(data)                          ((0x00000800&(data))>>11)
#define VE_CODECCNTL_get_min_xfer_size(data)                          ((0x00000700&(data))>>8)
#define VE_CODECCNTL_get_write_enable2(data)                          ((0x00000080&(data))>>7)
#define VE_CODECCNTL_get_pic_type(data)                               ((0x00000060&(data))>>5)
#define VE_CODECCNTL_get_write_enable1(data)                          ((0x00000010&(data))>>4)
#define VE_CODECCNTL_get_coding_type(data)                            (0x0000000F&(data))

#define VE_CODECCNTL1                                                 0x1800A104
#define VE_CODECCNTL1_reg_addr                                        "0xB800A104"
#define VE_CODECCNTL1_reg                                             0xB800A104
#define VE_CODECCNTL1_inst_addr                                       "0x0041"
#define VE_CODECCNTL1_inst                                            0x0041
#define VE_CODECCNTL1_dv_skip_pass3_shift                             (31)
#define VE_CODECCNTL1_ivf_shift                                       (30)
#define VE_CODECCNTL1_as_shift                                        (29)
#define VE_CODECCNTL1_pseudomode_shift                                (28)
#define VE_CODECCNTL1_data_partition_shift                            (7)
#define VE_CODECCNTL1_intra_dc_vlc_shift                              (6)
#define VE_CODECCNTL1_short_hdr_shift                                 (5)
#define VE_CODECCNTL1_r_vlc_shift                                     (4)
#define VE_CODECCNTL1_ac_pred_shift                                   (3)
#define VE_CODECCNTL1_q_sample_shift                                  (2)
#define VE_CODECCNTL1_ldtable_shift                                   (1)
#define VE_CODECCNTL1_write_data_shift                                (0)
#define VE_CODECCNTL1_dv_skip_pass3_mask                              (0x80000000)
#define VE_CODECCNTL1_ivf_mask                                        (0x40000000)
#define VE_CODECCNTL1_as_mask                                         (0x20000000)
#define VE_CODECCNTL1_pseudomode_mask                                 (0x10000000)
#define VE_CODECCNTL1_data_partition_mask                             (0x00000080)
#define VE_CODECCNTL1_intra_dc_vlc_mask                               (0x00000040)
#define VE_CODECCNTL1_short_hdr_mask                                  (0x00000020)
#define VE_CODECCNTL1_r_vlc_mask                                      (0x00000010)
#define VE_CODECCNTL1_ac_pred_mask                                    (0x00000008)
#define VE_CODECCNTL1_q_sample_mask                                   (0x00000004)
#define VE_CODECCNTL1_ldtable_mask                                    (0x00000002)
#define VE_CODECCNTL1_write_data_mask                                 (0x00000001)
#define VE_CODECCNTL1_dv_skip_pass3(data)                             (0x80000000&((data)<<31))
#define VE_CODECCNTL1_ivf(data)                                       (0x40000000&((data)<<30))
#define VE_CODECCNTL1_as(data)                                        (0x20000000&((data)<<29))
#define VE_CODECCNTL1_pseudomode(data)                                (0x10000000&((data)<<28))
#define VE_CODECCNTL1_data_partition(data)                            (0x00000080&((data)<<7))
#define VE_CODECCNTL1_intra_dc_vlc(data)                              (0x00000040&((data)<<6))
#define VE_CODECCNTL1_short_hdr(data)                                 (0x00000020&((data)<<5))
#define VE_CODECCNTL1_r_vlc(data)                                     (0x00000010&((data)<<4))
#define VE_CODECCNTL1_ac_pred(data)                                   (0x00000008&((data)<<3))
#define VE_CODECCNTL1_q_sample(data)                                  (0x00000004&((data)<<2))
#define VE_CODECCNTL1_ldtable(data)                                   (0x00000002&((data)<<1))
#define VE_CODECCNTL1_write_data(data)                                (0x00000001&(data))
#define VE_CODECCNTL1_get_dv_skip_pass3(data)                         ((0x80000000&(data))>>31)
#define VE_CODECCNTL1_get_ivf(data)                                   ((0x40000000&(data))>>30)
#define VE_CODECCNTL1_get_as(data)                                    ((0x20000000&(data))>>29)
#define VE_CODECCNTL1_get_pseudomode(data)                            ((0x10000000&(data))>>28)
#define VE_CODECCNTL1_get_data_partition(data)                        ((0x00000080&(data))>>7)
#define VE_CODECCNTL1_get_intra_dc_vlc(data)                          ((0x00000040&(data))>>6)
#define VE_CODECCNTL1_get_short_hdr(data)                             ((0x00000020&(data))>>5)
#define VE_CODECCNTL1_get_r_vlc(data)                                 ((0x00000010&(data))>>4)
#define VE_CODECCNTL1_get_ac_pred(data)                               ((0x00000008&(data))>>3)
#define VE_CODECCNTL1_get_q_sample(data)                              ((0x00000004&(data))>>2)
#define VE_CODECCNTL1_get_ldtable(data)                               ((0x00000002&(data))>>1)
#define VE_CODECCNTL1_get_write_data(data)                            (0x00000001&(data))

#define VE_DVPARAM                                                    0x1800A108
#define VE_DVPARAM_reg_addr                                           "0xB800A108"
#define VE_DVPARAM_reg                                                0xB800A108
#define VE_DVPARAM_inst_addr                                          "0x0042"
#define VE_DVPARAM_inst                                               0x0042
#define VE_DVPARAM_dct_mode_shift                                     (16)
#define VE_DVPARAM_class_blk_shift                                    (4)
#define VE_DVPARAM_qno_shift                                          (0)
#define VE_DVPARAM_dct_mode_mask                                      (0x003F0000)
#define VE_DVPARAM_class_blk_mask                                     (0x0000FFF0)
#define VE_DVPARAM_qno_mask                                           (0x0000000F)
#define VE_DVPARAM_dct_mode(data)                                     (0x003F0000&((data)<<16))
#define VE_DVPARAM_class_blk(data)                                    (0x0000FFF0&((data)<<4))
#define VE_DVPARAM_qno(data)                                          (0x0000000F&(data))
#define VE_DVPARAM_get_dct_mode(data)                                 ((0x003F0000&(data))>>16)
#define VE_DVPARAM_get_class_blk(data)                                ((0x0000FFF0&(data))>>4)
#define VE_DVPARAM_get_qno(data)                                      (0x0000000F&(data))

#define VE_RVSTRUVLCLEN                                               0x1800A10C
#define VE_RVSTRUVLCLEN_reg_addr                                      "0xB800A10C"
#define VE_RVSTRUVLCLEN_reg                                           0xB800A10C
#define VE_RVSTRUVLCLEN_inst_addr                                     "0x0043"
#define VE_RVSTRUVLCLEN_inst                                          0x0043
#define VE_RVSTRUVLCLEN_struvlc_len_shift                             (0)
#define VE_RVSTRUVLCLEN_struvlc_len_mask                              (0x7FFFFFFF)
#define VE_RVSTRUVLCLEN_struvlc_len(data)                             (0x7FFFFFFF&(data))
#define VE_RVSTRUVLCLEN_get_struvlc_len(data)                         (0x7FFFFFFF&(data))

#define VE_RVPARAM                                                    0x1800A110
#define VE_RVPARAM_reg_addr                                           "0xB800A110"
#define VE_RVPARAM_reg                                                0xB800A110
#define VE_RVPARAM_inst_addr                                          "0x0044"
#define VE_RVPARAM_inst                                               0x0044
#define VE_RVPARAM_write_enable3_shift                                (31)
#define VE_RVPARAM_umem1_mstr_shift                                   (30)
#define VE_RVPARAM_write_enable2_shift                                (29)
#define VE_RVPARAM_rvmb_type_shift                                    (25)
#define VE_RVPARAM_write_enable1_shift                                (24)
#define VE_RVPARAM_24bits_cbp_shift                                   (0)
#define VE_RVPARAM_write_enable3_mask                                 (0x80000000)
#define VE_RVPARAM_umem1_mstr_mask                                    (0x40000000)
#define VE_RVPARAM_write_enable2_mask                                 (0x20000000)
#define VE_RVPARAM_rvmb_type_mask                                     (0x1E000000)
#define VE_RVPARAM_write_enable1_mask                                 (0x01000000)
#define VE_RVPARAM_24bits_cbp_mask                                    (0x00FFFFFF)
#define VE_RVPARAM_write_enable3(data)                                (0x80000000&((data)<<31))
#define VE_RVPARAM_umem1_mstr(data)                                   (0x40000000&((data)<<30))
#define VE_RVPARAM_write_enable2(data)                                (0x20000000&((data)<<29))
#define VE_RVPARAM_rvmb_type(data)                                    (0x1E000000&((data)<<25))
#define VE_RVPARAM_write_enable1(data)                                (0x01000000&((data)<<24))
#define VE_RVPARAM_24bits_cbp(data)                                   (0x00FFFFFF&(data))
#define VE_RVPARAM_get_write_enable3(data)                            ((0x80000000&(data))>>31)
#define VE_RVPARAM_get_umem1_mstr(data)                               ((0x40000000&(data))>>30)
#define VE_RVPARAM_get_write_enable2(data)                            ((0x20000000&(data))>>29)
#define VE_RVPARAM_get_rvmb_type(data)                                ((0x1E000000&(data))>>25)
#define VE_RVPARAM_get_write_enable1(data)                            ((0x01000000&(data))>>24)
#define VE_RVPARAM_get_24bits_cbp(data)                               (0x00FFFFFF&(data))

#define VE_RVINTRAMODE1                                               0x1800A114
#define VE_RVINTRAMODE1_reg_addr                                      "0xB800A114"
#define VE_RVINTRAMODE1_reg                                           0xB800A114
#define VE_RVINTRAMODE1_inst_addr                                     "0x0045"
#define VE_RVINTRAMODE1_inst                                          0x0045
#define VE_RVINTRAMODE1_intra_mode1_shift                             (0)
#define VE_RVINTRAMODE1_intra_mode1_mask                              (0xFFFFFFFF)
#define VE_RVINTRAMODE1_intra_mode1(data)                             (0xFFFFFFFF&(data))
#define VE_RVINTRAMODE1_get_intra_mode1(data)                         (0xFFFFFFFF&(data))

#define VE_RVINTRAMODE2                                               0x1800A118
#define VE_RVINTRAMODE2_reg_addr                                      "0xB800A118"
#define VE_RVINTRAMODE2_reg                                           0xB800A118
#define VE_RVINTRAMODE2_inst_addr                                     "0x0046"
#define VE_RVINTRAMODE2_inst                                          0x0046
#define VE_RVINTRAMODE2_intra_mode2_shift                             (0)
#define VE_RVINTRAMODE2_intra_mode2_mask                              (0xFFFFFFFF)
#define VE_RVINTRAMODE2_intra_mode2(data)                             (0xFFFFFFFF&(data))
#define VE_RVINTRAMODE2_get_intra_mode2(data)                         (0xFFFFFFFF&(data))

#define VE_RVPARAM2                                                   0x1800A11C
#define VE_RVPARAM2_reg_addr                                          "0xB800A11C"
#define VE_RVPARAM2_reg                                               0xB800A11C
#define VE_RVPARAM2_inst_addr                                         "0x0047"
#define VE_RVPARAM2_inst                                              0x0047
#define VE_RVPARAM2_rv9_intramode_use_top_shift                       (2)
#define VE_RVPARAM2_rv_osvquant_shift                                 (0)
#define VE_RVPARAM2_rv9_intramode_use_top_mask                        (0x00000004)
#define VE_RVPARAM2_rv_osvquant_mask                                  (0x00000003)
#define VE_RVPARAM2_rv9_intramode_use_top(data)                       (0x00000004&((data)<<2))
#define VE_RVPARAM2_rv_osvquant(data)                                 (0x00000003&(data))
#define VE_RVPARAM2_get_rv9_intramode_use_top(data)                   ((0x00000004&(data))>>2)
#define VE_RVPARAM2_get_rv_osvquant(data)                             (0x00000003&(data))

#define VE_VLDTBLPTR_0                                                0x1800A120
#define VE_VLDTBLPTR_1                                                0x1800A124
#define VE_VLDTBLPTR_2                                                0x1800A128
#define VE_VLDTBLPTR_3                                                0x1800A12C
#define VE_VLDTBLPTR_0_reg_addr                                       "0xB800A120"
#define VE_VLDTBLPTR_1_reg_addr                                       "0xB800A124"
#define VE_VLDTBLPTR_2_reg_addr                                       "0xB800A128"
#define VE_VLDTBLPTR_3_reg_addr                                       "0xB800A12C"
#define VE_VLDTBLPTR_0_reg                                            0xB800A120
#define VE_VLDTBLPTR_1_reg                                            0xB800A124
#define VE_VLDTBLPTR_2_reg                                            0xB800A128
#define VE_VLDTBLPTR_3_reg                                            0xB800A12C
#define VE_VLDTBLPTR_0_inst_addr                                      "0x0048"
#define VE_VLDTBLPTR_0_inst                                           0x0048
#define VE_VLDTBLPTR_1_inst_addr                                      "0x0049"
#define VE_VLDTBLPTR_1_inst                                           0x0049
#define VE_VLDTBLPTR_2_inst_addr                                      "0x004A"
#define VE_VLDTBLPTR_2_inst                                           0x004A
#define VE_VLDTBLPTR_3_inst_addr                                      "0x004B"
#define VE_VLDTBLPTR_3_inst                                           0x004B
#define VE_VLDTBLPTR_tbl_startaddr_shift                              (0)
#define VE_VLDTBLPTR_tbl_startaddr_mask                               (0x000007FF)
#define VE_VLDTBLPTR_tbl_startaddr(data)                              (0x000007FF&(data))
#define VE_VLDTBLPTR_get_tbl_startaddr(data)                          (0x000007FF&(data))

#define VE_VLDESPPTR_0                                                0x1800A130
#define VE_VLDESPPTR_1                                                0x1800A134
#define VE_VLDESPPTR_2                                                0x1800A138
#define VE_VLDESPPTR_3                                                0x1800A13C
#define VE_VLDESPPTR_0_reg_addr                                       "0xB800A130"
#define VE_VLDESPPTR_1_reg_addr                                       "0xB800A134"
#define VE_VLDESPPTR_2_reg_addr                                       "0xB800A138"
#define VE_VLDESPPTR_3_reg_addr                                       "0xB800A13C"
#define VE_VLDESPPTR_0_reg                                            0xB800A130
#define VE_VLDESPPTR_1_reg                                            0xB800A134
#define VE_VLDESPPTR_2_reg                                            0xB800A138
#define VE_VLDESPPTR_3_reg                                            0xB800A13C
#define VE_VLDESPPTR_0_inst_addr                                      "0x004C"
#define VE_VLDESPPTR_0_inst                                           0x004C
#define VE_VLDESPPTR_1_inst_addr                                      "0x004D"
#define VE_VLDESPPTR_1_inst                                           0x004D
#define VE_VLDESPPTR_2_inst_addr                                      "0x004E"
#define VE_VLDESPPTR_2_inst                                           0x004E
#define VE_VLDESPPTR_3_inst_addr                                      "0x004F"
#define VE_VLDESPPTR_3_inst                                           0x004F
#define VE_VLDESPPTR_tbl_espptr_saddr_shift                           (0)
#define VE_VLDESPPTR_tbl_espptr_saddr_mask                            (0x000007FF)
#define VE_VLDESPPTR_tbl_espptr_saddr(data)                           (0x000007FF&(data))
#define VE_VLDESPPTR_get_tbl_espptr_saddr(data)                       (0x000007FF&(data))

#define VE_DECBITCNT                                                  0x1800A140
#define VE_DECBITCNT_reg_addr                                         "0xB800A140"
#define VE_DECBITCNT_reg                                              0xB800A140
#define VE_DECBITCNT_inst_addr                                        "0x0050"
#define VE_DECBITCNT_inst                                             0x0050
#define VE_DECBITCNT_max_bit_shift                                    (0)
#define VE_DECBITCNT_max_bit_mask                                     (0xFFFFFFFF)
#define VE_DECBITCNT_max_bit(data)                                    (0xFFFFFFFF&(data))
#define VE_DECBITCNT_get_max_bit(data)                                (0xFFFFFFFF&(data))

#define VE_BITSTCNT                                                   0x1800A144
#define VE_BITSTCNT_reg_addr                                          "0xB800A144"
#define VE_BITSTCNT_reg                                               0xB800A144
#define VE_BITSTCNT_inst_addr                                         "0x0051"
#define VE_BITSTCNT_inst                                              0x0051
#define VE_BITSTCNT_bitcount_shift                                    (0)
#define VE_BITSTCNT_bitcount_mask                                     (0xFFFFFFFF)
#define VE_BITSTCNT_bitcount(data)                                    (0xFFFFFFFF&(data))
#define VE_BITSTCNT_get_bitcount(data)                                (0xFFFFFFFF&(data))

#define VE_BSTTIMER                                                   0x1800A148
#define VE_BSTTIMER_reg_addr                                          "0xB800A148"
#define VE_BSTTIMER_reg                                               0xB800A148
#define VE_BSTTIMER_inst_addr                                         "0x0052"
#define VE_BSTTIMER_inst                                              0x0052
#define VE_BSTTIMER_to_value_shift                                    (0)
#define VE_BSTTIMER_to_value_mask                                     (0x00FFFFFF)
#define VE_BSTTIMER_to_value(data)                                    (0x00FFFFFF&(data))
#define VE_BSTTIMER_get_to_value(data)                                (0x00FFFFFF&(data))

#define VE_PINSTCLIM                                                  0x1800A14C
#define VE_PINSTCLIM_reg_addr                                         "0xB800A14C"
#define VE_PINSTCLIM_reg                                              0xB800A14C
#define VE_PINSTCLIM_inst_addr                                        "0x0053"
#define VE_PINSTCLIM_inst                                             0x0053
#define VE_PINSTCLIM_bitcount_shift                                   (0)
#define VE_PINSTCLIM_bitcount_mask                                    (0x00FFFFFF)
#define VE_PINSTCLIM_bitcount(data)                                   (0x00FFFFFF&(data))
#define VE_PINSTCLIM_get_bitcount(data)                               (0x00FFFFFF&(data))

#define VE_BSBASE                                                     0x1800A160
#define VE_BSBASE_reg_addr                                            "0xB800A160"
#define VE_BSBASE_reg                                                 0xB800A160
#define VE_BSBASE_inst_addr                                           "0x0058"
#define VE_BSBASE_inst                                                0x0058
#define VE_BSBASE_bs_base_shift                                       (0)
#define VE_BSBASE_bs_base_mask                                        (0x1FFFFFFF)
#define VE_BSBASE_bs_base(data)                                       (0x1FFFFFFF&(data))
#define VE_BSBASE_get_bs_base(data)                                   (0x1FFFFFFF&(data))

#define VE_BSLIMIT                                                    0x1800A164
#define VE_BSLIMIT_reg_addr                                           "0xB800A164"
#define VE_BSLIMIT_reg                                                0xB800A164
#define VE_BSLIMIT_inst_addr                                          "0x0059"
#define VE_BSLIMIT_inst                                               0x0059
#define VE_BSLIMIT_bs_limit_shift                                     (0)
#define VE_BSLIMIT_bs_limit_mask                                      (0x1FFFFFFF)
#define VE_BSLIMIT_bs_limit(data)                                     (0x1FFFFFFF&(data))
#define VE_BSLIMIT_get_bs_limit(data)                                 (0x1FFFFFFF&(data))

#define VE_BSWRPTR                                                    0x1800A168
#define VE_BSWRPTR_reg_addr                                           "0xB800A168"
#define VE_BSWRPTR_reg                                                0xB800A168
#define VE_BSWRPTR_inst_addr                                          "0x005A"
#define VE_BSWRPTR_inst                                               0x005A
#define VE_BSWRPTR_wr_ptr_shift                                       (0)
#define VE_BSWRPTR_wr_ptr_mask                                        (0x1FFFFFFF)
#define VE_BSWRPTR_wr_ptr(data)                                       (0x1FFFFFFF&(data))
#define VE_BSWRPTR_get_wr_ptr(data)                                   (0x1FFFFFFF&(data))

#define VE_BSRDPTR                                                    0x1800A16C
#define VE_BSRDPTR_reg_addr                                           "0xB800A16C"
#define VE_BSRDPTR_reg                                                0xB800A16C
#define VE_BSRDPTR_inst_addr                                          "0x005B"
#define VE_BSRDPTR_inst                                               0x005B
#define VE_BSRDPTR_rd_ptr_shift                                       (0)
#define VE_BSRDPTR_rd_ptr_mask                                        (0x1FFFFFFF)
#define VE_BSRDPTR_rd_ptr(data)                                       (0x1FFFFFFF&(data))
#define VE_BSRDPTR_get_rd_ptr(data)                                   (0x1FFFFFFF&(data))

#define VE_BSCURPTR                                                   0x1800A170
#define VE_BSCURPTR_reg_addr                                          "0xB800A170"
#define VE_BSCURPTR_reg                                               0xB800A170
#define VE_BSCURPTR_inst_addr                                         "0x005C"
#define VE_BSCURPTR_inst                                              0x005C
#define VE_BSCURPTR_cur_ptr_shift                                     (0)
#define VE_BSCURPTR_cur_ptr_mask                                      (0x1FFFFFFF)
#define VE_BSCURPTR_cur_ptr(data)                                     (0x1FFFFFFF&(data))
#define VE_BSCURPTR_get_cur_ptr(data)                                 (0x1FFFFFFF&(data))

#define VE_DECBSPTR                                                   0x1800A174
#define VE_DECBSPTR_reg_addr                                          "0xB800A174"
#define VE_DECBSPTR_reg                                               0xB800A174
#define VE_DECBSPTR_inst_addr                                         "0x005D"
#define VE_DECBSPTR_inst                                              0x005D
#define VE_DECBSPTR_dec_bit_ptr_shift                                 (0)
#define VE_DECBSPTR_dec_bit_ptr_mask                                  (0xFFFFFFFF)
#define VE_DECBSPTR_dec_bit_ptr(data)                                 (0xFFFFFFFF&(data))
#define VE_DECBSPTR_get_dec_bit_ptr(data)                             (0xFFFFFFFF&(data))

#define VE_FILTCNTL                                                   0x1800A200
#define VE_FILTCNTL_reg_addr                                          "0xB800A200"
#define VE_FILTCNTL_reg                                               0xB800A200
#define VE_FILTCNTL_inst_addr                                         "0x0080"
#define VE_FILTCNTL_inst                                              0x0080
#define VE_FILTCNTL_write_enable5_shift                               (27)
#define VE_FILTCNTL_rpt_botline_shift                                 (24)
#define VE_FILTCNTL_rpt_topline_shift                                 (21)
#define VE_FILTCNTL_write_enable4_shift                               (20)
#define VE_FILTCNTL_rpt_rightpel_shift                                (17)
#define VE_FILTCNTL_rpt_leftpel_shift                                 (14)
#define VE_FILTCNTL_write_enable3_shift                               (13)
#define VE_FILTCNTL_start_tap_shift                                   (9)
#define VE_FILTCNTL_write_enable2_shift                               (8)
#define VE_FILTCNTL_tapnum_shift                                      (4)
#define VE_FILTCNTL_write_enable1_shift                               (3)
#define VE_FILTCNTL_filt_prec_shift                                   (0)
#define VE_FILTCNTL_write_enable5_mask                                (0x08000000)
#define VE_FILTCNTL_rpt_botline_mask                                  (0x07000000)
#define VE_FILTCNTL_rpt_topline_mask                                  (0x00E00000)
#define VE_FILTCNTL_write_enable4_mask                                (0x00100000)
#define VE_FILTCNTL_rpt_rightpel_mask                                 (0x000E0000)
#define VE_FILTCNTL_rpt_leftpel_mask                                  (0x0001C000)
#define VE_FILTCNTL_write_enable3_mask                                (0x00002000)
#define VE_FILTCNTL_start_tap_mask                                    (0x00001E00)
#define VE_FILTCNTL_write_enable2_mask                                (0x00000100)
#define VE_FILTCNTL_tapnum_mask                                       (0x000000F0)
#define VE_FILTCNTL_write_enable1_mask                                (0x00000008)
#define VE_FILTCNTL_filt_prec_mask                                    (0x00000007)
#define VE_FILTCNTL_write_enable5(data)                               (0x08000000&((data)<<27))
#define VE_FILTCNTL_rpt_botline(data)                                 (0x07000000&((data)<<24))
#define VE_FILTCNTL_rpt_topline(data)                                 (0x00E00000&((data)<<21))
#define VE_FILTCNTL_write_enable4(data)                               (0x00100000&((data)<<20))
#define VE_FILTCNTL_rpt_rightpel(data)                                (0x000E0000&((data)<<17))
#define VE_FILTCNTL_rpt_leftpel(data)                                 (0x0001C000&((data)<<14))
#define VE_FILTCNTL_write_enable3(data)                               (0x00002000&((data)<<13))
#define VE_FILTCNTL_start_tap(data)                                   (0x00001E00&((data)<<9))
#define VE_FILTCNTL_write_enable2(data)                               (0x00000100&((data)<<8))
#define VE_FILTCNTL_tapnum(data)                                      (0x000000F0&((data)<<4))
#define VE_FILTCNTL_write_enable1(data)                               (0x00000008&((data)<<3))
#define VE_FILTCNTL_filt_prec(data)                                   (0x00000007&(data))
#define VE_FILTCNTL_get_write_enable5(data)                           ((0x08000000&(data))>>27)
#define VE_FILTCNTL_get_rpt_botline(data)                             ((0x07000000&(data))>>24)
#define VE_FILTCNTL_get_rpt_topline(data)                             ((0x00E00000&(data))>>21)
#define VE_FILTCNTL_get_write_enable4(data)                           ((0x00100000&(data))>>20)
#define VE_FILTCNTL_get_rpt_rightpel(data)                            ((0x000E0000&(data))>>17)
#define VE_FILTCNTL_get_rpt_leftpel(data)                             ((0x0001C000&(data))>>14)
#define VE_FILTCNTL_get_write_enable3(data)                           ((0x00002000&(data))>>13)
#define VE_FILTCNTL_get_start_tap(data)                               ((0x00001E00&(data))>>9)
#define VE_FILTCNTL_get_write_enable2(data)                           ((0x00000100&(data))>>8)
#define VE_FILTCNTL_get_tapnum(data)                                  ((0x000000F0&(data))>>4)
#define VE_FILTCNTL_get_write_enable1(data)                           ((0x00000008&(data))>>3)
#define VE_FILTCNTL_get_filt_prec(data)                               (0x00000007&(data))

#define VE_FILTINIT                                                   0x1800A204
#define VE_FILTINIT_reg_addr                                          "0xB800A204"
#define VE_FILTINIT_reg                                               0xB800A204
#define VE_FILTINIT_inst_addr                                         "0x0081"
#define VE_FILTINIT_inst                                              0x0081
#define VE_FILTINIT_init_value_shift                                  (0)
#define VE_FILTINIT_init_value_mask                                   (0x007FFFFF)
#define VE_FILTINIT_init_value(data)                                  (0x007FFFFF&(data))
#define VE_FILTINIT_get_init_value(data)                              (0x007FFFFF&(data))

#define VE_CKCNTL                                                     0x1800A208
#define VE_CKCNTL_reg_addr                                            "0xB800A208"
#define VE_CKCNTL_reg                                                 0xB800A208
#define VE_CKCNTL_inst_addr                                           "0x0082"
#define VE_CKCNTL_inst                                                0x0082
#define VE_CKCNTL_alpha_loc_shift                                     (4)
#define VE_CKCNTL_alpha_enable_shift                                  (3)
#define VE_CKCNTL_color_key_enable_shift                              (2)
#define VE_CKCNTL_format_shift                                        (0)
#define VE_CKCNTL_alpha_loc_mask                                      (0x00000010)
#define VE_CKCNTL_alpha_enable_mask                                   (0x00000008)
#define VE_CKCNTL_color_key_enable_mask                               (0x00000004)
#define VE_CKCNTL_format_mask                                         (0x00000003)
#define VE_CKCNTL_alpha_loc(data)                                     (0x00000010&((data)<<4))
#define VE_CKCNTL_alpha_enable(data)                                  (0x00000008&((data)<<3))
#define VE_CKCNTL_color_key_enable(data)                              (0x00000004&((data)<<2))
#define VE_CKCNTL_format(data)                                        (0x00000003&(data))
#define VE_CKCNTL_get_alpha_loc(data)                                 ((0x00000010&(data))>>4)
#define VE_CKCNTL_get_alpha_enable(data)                              ((0x00000008&(data))>>3)
#define VE_CKCNTL_get_color_key_enable(data)                          ((0x00000004&(data))>>2)
#define VE_CKCNTL_get_format(data)                                    (0x00000003&(data))

#define VE_CKDATA                                                     0x1800A20C
#define VE_CKDATA_reg_addr                                            "0xB800A20C"
#define VE_CKDATA_reg                                                 0xB800A20C
#define VE_CKDATA_inst_addr                                           "0x0083"
#define VE_CKDATA_inst                                                0x0083
#define VE_CKDATA_color_key2_shift                                    (16)
#define VE_CKDATA_color_key1_shift                                    (8)
#define VE_CKDATA_color_key0_shift                                    (0)
#define VE_CKDATA_color_key2_mask                                     (0x00FF0000)
#define VE_CKDATA_color_key1_mask                                     (0x0000FF00)
#define VE_CKDATA_color_key0_mask                                     (0x000000FF)
#define VE_CKDATA_color_key2(data)                                    (0x00FF0000&((data)<<16))
#define VE_CKDATA_color_key1(data)                                    (0x0000FF00&((data)<<8))
#define VE_CKDATA_color_key0(data)                                    (0x000000FF&(data))
#define VE_CKDATA_get_color_key2(data)                                ((0x00FF0000&(data))>>16)
#define VE_CKDATA_get_color_key1(data)                                ((0x0000FF00&(data))>>8)
#define VE_CKDATA_get_color_key0(data)                                (0x000000FF&(data))

#define VE_ADAPCNTL                                                   0x1800A210
#define VE_ADAPCNTL_reg_addr                                          "0xB800A210"
#define VE_ADAPCNTL_reg                                               0xB800A210
#define VE_ADAPCNTL_inst_addr                                         "0x0084"
#define VE_ADAPCNTL_inst                                              0x0084
#define VE_ADAPCNTL_rshift_size_shift                                 (25)
#define VE_ADAPCNTL_t2_shift                                          (16)
#define VE_ADAPCNTL_k1_shift                                          (8)
#define VE_ADAPCNTL_t1_shift                                          (0)
#define VE_ADAPCNTL_rshift_size_mask                                  (0x0E000000)
#define VE_ADAPCNTL_t2_mask                                           (0x00FF0000)
#define VE_ADAPCNTL_k1_mask                                           (0x0000FF00)
#define VE_ADAPCNTL_t1_mask                                           (0x000000FF)
#define VE_ADAPCNTL_rshift_size(data)                                 (0x0E000000&((data)<<25))
#define VE_ADAPCNTL_t2(data)                                          (0x00FF0000&((data)<<16))
#define VE_ADAPCNTL_k1(data)                                          (0x0000FF00&((data)<<8))
#define VE_ADAPCNTL_t1(data)                                          (0x000000FF&(data))
#define VE_ADAPCNTL_get_rshift_size(data)                             ((0x0E000000&(data))>>25)
#define VE_ADAPCNTL_get_t2(data)                                      ((0x00FF0000&(data))>>16)
#define VE_ADAPCNTL_get_k1(data)                                      ((0x0000FF00&(data))>>8)
#define VE_ADAPCNTL_get_t1(data)                                      (0x000000FF&(data))

#define VE_ALPHA                                                      0x1800A214
#define VE_ALPHA_reg_addr                                             "0xB800A214"
#define VE_ALPHA_reg                                                  0xB800A214
#define VE_ALPHA_inst_addr                                            "0x0085"
#define VE_ALPHA_inst                                                 0x0085
#define VE_ALPHA_alpha_shift                                          (0)
#define VE_ALPHA_alpha_mask                                           (0x000000FF)
#define VE_ALPHA_alpha(data)                                          (0x000000FF&(data))
#define VE_ALPHA_get_alpha(data)                                      (0x000000FF&(data))

#define VE_DEBLKCNTL                                                  0x1800A218
#define VE_DEBLKCNTL_reg_addr                                         "0xB800A218"
#define VE_DEBLKCNTL_reg                                              0xB800A218
#define VE_DEBLKCNTL_inst_addr                                        "0x0086"
#define VE_DEBLKCNTL_inst                                             0x0086
#define VE_DEBLKCNTL_thr_2_shift                                      (4)
#define VE_DEBLKCNTL_thr_1_shift                                      (0)
#define VE_DEBLKCNTL_thr_2_mask                                       (0x000000F0)
#define VE_DEBLKCNTL_thr_1_mask                                       (0x0000000F)
#define VE_DEBLKCNTL_thr_2(data)                                      (0x000000F0&((data)<<4))
#define VE_DEBLKCNTL_thr_1(data)                                      (0x0000000F&(data))
#define VE_DEBLKCNTL_get_thr_2(data)                                  ((0x000000F0&(data))>>4)
#define VE_DEBLKCNTL_get_thr_1(data)                                  (0x0000000F&(data))

#define VE_DCVAL                                                      0x1800A220
#define VE_DCVAL_reg_addr                                             "0xB800A220"
#define VE_DCVAL_reg                                                  0xB800A220
#define VE_DCVAL_inst_addr                                            "0x0088"
#define VE_DCVAL_inst                                                 0x0088
#define VE_DCVAL_dc_value_shift                                       (0)
#define VE_DCVAL_dc_value_mask                                        (0x000000FF)
#define VE_DCVAL_dc_value(data)                                       (0x000000FF&(data))
#define VE_DCVAL_get_dc_value(data)                                   (0x000000FF&(data))

#define VE_BLKD_THR                                                   0x1800A224
#define VE_BLKD_THR_reg_addr                                          "0xB800A224"
#define VE_BLKD_THR_reg                                               0xB800A224
#define VE_BLKD_THR_inst_addr                                         "0x0089"
#define VE_BLKD_THR_inst                                              0x0089
#define VE_BLKD_THR_thr_4_shift                                       (24)
#define VE_BLKD_THR_thr_3_shift                                       (16)
#define VE_BLKD_THR_thr_2_shift                                       (8)
#define VE_BLKD_THR_thr_1_shift                                       (0)
#define VE_BLKD_THR_thr_4_mask                                        (0xFF000000)
#define VE_BLKD_THR_thr_3_mask                                        (0x00FF0000)
#define VE_BLKD_THR_thr_2_mask                                        (0x0000FF00)
#define VE_BLKD_THR_thr_1_mask                                        (0x000000FF)
#define VE_BLKD_THR_thr_4(data)                                       (0xFF000000&((data)<<24))
#define VE_BLKD_THR_thr_3(data)                                       (0x00FF0000&((data)<<16))
#define VE_BLKD_THR_thr_2(data)                                       (0x0000FF00&((data)<<8))
#define VE_BLKD_THR_thr_1(data)                                       (0x000000FF&(data))
#define VE_BLKD_THR_get_thr_4(data)                                   ((0xFF000000&(data))>>24)
#define VE_BLKD_THR_get_thr_3(data)                                   ((0x00FF0000&(data))>>16)
#define VE_BLKD_THR_get_thr_2(data)                                   ((0x0000FF00&(data))>>8)
#define VE_BLKD_THR_get_thr_1(data)                                   (0x000000FF&(data))

#define VE_BLKD_WEIGHT                                                0x1800A228
#define VE_BLKD_WEIGHT_reg_addr                                       "0xB800A228"
#define VE_BLKD_WEIGHT_reg                                            0xB800A228
#define VE_BLKD_WEIGHT_inst_addr                                      "0x008A"
#define VE_BLKD_WEIGHT_inst                                           0x008A
#define VE_BLKD_WEIGHT_weight_5_shift                                 (24)
#define VE_BLKD_WEIGHT_weight_4_shift                                 (16)
#define VE_BLKD_WEIGHT_weight_3_shift                                 (8)
#define VE_BLKD_WEIGHT_weight_2_shift                                 (0)
#define VE_BLKD_WEIGHT_weight_5_mask                                  (0xFF000000)
#define VE_BLKD_WEIGHT_weight_4_mask                                  (0x00FF0000)
#define VE_BLKD_WEIGHT_weight_3_mask                                  (0x0000FF00)
#define VE_BLKD_WEIGHT_weight_2_mask                                  (0x000000FF)
#define VE_BLKD_WEIGHT_weight_5(data)                                 (0xFF000000&((data)<<24))
#define VE_BLKD_WEIGHT_weight_4(data)                                 (0x00FF0000&((data)<<16))
#define VE_BLKD_WEIGHT_weight_3(data)                                 (0x0000FF00&((data)<<8))
#define VE_BLKD_WEIGHT_weight_2(data)                                 (0x000000FF&(data))
#define VE_BLKD_WEIGHT_get_weight_5(data)                             ((0xFF000000&(data))>>24)
#define VE_BLKD_WEIGHT_get_weight_4(data)                             ((0x00FF0000&(data))>>16)
#define VE_BLKD_WEIGHT_get_weight_3(data)                             ((0x0000FF00&(data))>>8)
#define VE_BLKD_WEIGHT_get_weight_2(data)                             (0x000000FF&(data))

#define VE_QPEL_FORMAT                                                0x1800A22C
#define VE_QPEL_FORMAT_reg_addr                                       "0xB800A22C"
#define VE_QPEL_FORMAT_reg                                            0xB800A22C
#define VE_QPEL_FORMAT_inst_addr                                      "0x008B"
#define VE_QPEL_FORMAT_inst                                           0x008B
#define VE_QPEL_FORMAT_qpel_format_shift                              (0)
#define VE_QPEL_FORMAT_qpel_format_mask                               (0x00000001)
#define VE_QPEL_FORMAT_qpel_format(data)                              (0x00000001&(data))
#define VE_QPEL_FORMAT_get_qpel_format(data)                          (0x00000001&(data))

#define VE_IMPULSE_THR                                                0x1800A230
#define VE_IMPULSE_THR_reg_addr                                       "0xB800A230"
#define VE_IMPULSE_THR_reg                                            0xB800A230
#define VE_IMPULSE_THR_inst_addr                                      "0x008C"
#define VE_IMPULSE_THR_inst                                           0x008C
#define VE_IMPULSE_THR_thr_4_shift                                    (24)
#define VE_IMPULSE_THR_thr_3_shift                                    (16)
#define VE_IMPULSE_THR_thr_2_shift                                    (8)
#define VE_IMPULSE_THR_thr_1_shift                                    (0)
#define VE_IMPULSE_THR_thr_4_mask                                     (0xFF000000)
#define VE_IMPULSE_THR_thr_3_mask                                     (0x00FF0000)
#define VE_IMPULSE_THR_thr_2_mask                                     (0x0000FF00)
#define VE_IMPULSE_THR_thr_1_mask                                     (0x000000FF)
#define VE_IMPULSE_THR_thr_4(data)                                    (0xFF000000&((data)<<24))
#define VE_IMPULSE_THR_thr_3(data)                                    (0x00FF0000&((data)<<16))
#define VE_IMPULSE_THR_thr_2(data)                                    (0x0000FF00&((data)<<8))
#define VE_IMPULSE_THR_thr_1(data)                                    (0x000000FF&(data))
#define VE_IMPULSE_THR_get_thr_4(data)                                ((0xFF000000&(data))>>24)
#define VE_IMPULSE_THR_get_thr_3(data)                                ((0x00FF0000&(data))>>16)
#define VE_IMPULSE_THR_get_thr_2(data)                                ((0x0000FF00&(data))>>8)
#define VE_IMPULSE_THR_get_thr_1(data)                                (0x000000FF&(data))

#define VE_IMPULSE_THR2                                               0x1800A234
#define VE_IMPULSE_THR2_reg_addr                                      "0xB800A234"
#define VE_IMPULSE_THR2_reg                                           0xB800A234
#define VE_IMPULSE_THR2_inst_addr                                     "0x008D"
#define VE_IMPULSE_THR2_inst                                          0x008D
#define VE_IMPULSE_THR2_thr_7_shift                                   (16)
#define VE_IMPULSE_THR2_thr_6_shift                                   (8)
#define VE_IMPULSE_THR2_thr_5_shift                                   (0)
#define VE_IMPULSE_THR2_thr_7_mask                                    (0x00FF0000)
#define VE_IMPULSE_THR2_thr_6_mask                                    (0x0000FF00)
#define VE_IMPULSE_THR2_thr_5_mask                                    (0x000000FF)
#define VE_IMPULSE_THR2_thr_7(data)                                   (0x00FF0000&((data)<<16))
#define VE_IMPULSE_THR2_thr_6(data)                                   (0x0000FF00&((data)<<8))
#define VE_IMPULSE_THR2_thr_5(data)                                   (0x000000FF&(data))
#define VE_IMPULSE_THR2_get_thr_7(data)                               ((0x00FF0000&(data))>>16)
#define VE_IMPULSE_THR2_get_thr_6(data)                               ((0x0000FF00&(data))>>8)
#define VE_IMPULSE_THR2_get_thr_5(data)                               (0x000000FF&(data))

#define VE_DERING_CTRL                                                0x1800A238
#define VE_DERING_CTRL_reg_addr                                       "0xB800A238"
#define VE_DERING_CTRL_reg                                            0xB800A238
#define VE_DERING_CTRL_inst_addr                                      "0x008E"
#define VE_DERING_CTRL_inst                                           0x008E
#define VE_DERING_CTRL_chroma_enable_shift                            (1)
#define VE_DERING_CTRL_luma_enable_shift                              (0)
#define VE_DERING_CTRL_chroma_enable_mask                             (0x00000002)
#define VE_DERING_CTRL_luma_enable_mask                               (0x00000001)
#define VE_DERING_CTRL_chroma_enable(data)                            (0x00000002&((data)<<1))
#define VE_DERING_CTRL_luma_enable(data)                              (0x00000001&(data))
#define VE_DERING_CTRL_get_chroma_enable(data)                        ((0x00000002&(data))>>1)
#define VE_DERING_CTRL_get_luma_enable(data)                          (0x00000001&(data))

#define VE_TAPCOEFF_0                                                 0x1800A240
#define VE_TAPCOEFF_1                                                 0x1800A244
#define VE_TAPCOEFF_2                                                 0x1800A248
#define VE_TAPCOEFF_3                                                 0x1800A24C
#define VE_TAPCOEFF_4                                                 0x1800A250
#define VE_TAPCOEFF_5                                                 0x1800A254
#define VE_TAPCOEFF_6                                                 0x1800A258
#define VE_TAPCOEFF_7                                                 0x1800A25C
#define VE_TAPCOEFF_0_reg_addr                                        "0xB800A240"
#define VE_TAPCOEFF_1_reg_addr                                        "0xB800A244"
#define VE_TAPCOEFF_2_reg_addr                                        "0xB800A248"
#define VE_TAPCOEFF_3_reg_addr                                        "0xB800A24C"
#define VE_TAPCOEFF_4_reg_addr                                        "0xB800A250"
#define VE_TAPCOEFF_5_reg_addr                                        "0xB800A254"
#define VE_TAPCOEFF_6_reg_addr                                        "0xB800A258"
#define VE_TAPCOEFF_7_reg_addr                                        "0xB800A25C"
#define VE_TAPCOEFF_0_reg                                             0xB800A240
#define VE_TAPCOEFF_1_reg                                             0xB800A244
#define VE_TAPCOEFF_2_reg                                             0xB800A248
#define VE_TAPCOEFF_3_reg                                             0xB800A24C
#define VE_TAPCOEFF_4_reg                                             0xB800A250
#define VE_TAPCOEFF_5_reg                                             0xB800A254
#define VE_TAPCOEFF_6_reg                                             0xB800A258
#define VE_TAPCOEFF_7_reg                                             0xB800A25C
#define VE_TAPCOEFF_0_inst_addr                                       "0x0090"
#define VE_TAPCOEFF_0_inst                                            0x0090
#define VE_TAPCOEFF_1_inst_addr                                       "0x0091"
#define VE_TAPCOEFF_1_inst                                            0x0091
#define VE_TAPCOEFF_2_inst_addr                                       "0x0092"
#define VE_TAPCOEFF_2_inst                                            0x0092
#define VE_TAPCOEFF_3_inst_addr                                       "0x0093"
#define VE_TAPCOEFF_3_inst                                            0x0093
#define VE_TAPCOEFF_4_inst_addr                                       "0x0094"
#define VE_TAPCOEFF_4_inst                                            0x0094
#define VE_TAPCOEFF_5_inst_addr                                       "0x0095"
#define VE_TAPCOEFF_5_inst                                            0x0095
#define VE_TAPCOEFF_6_inst_addr                                       "0x0096"
#define VE_TAPCOEFF_6_inst                                            0x0096
#define VE_TAPCOEFF_7_inst_addr                                       "0x0097"
#define VE_TAPCOEFF_7_inst                                            0x0097
#define VE_TAPCOEFF_coeffnplus1_shift                                 (16)
#define VE_TAPCOEFF_coeffn_shift                                      (0)
#define VE_TAPCOEFF_coeffnplus1_mask                                  (0x01FF0000)
#define VE_TAPCOEFF_coeffn_mask                                       (0x000001FF)
#define VE_TAPCOEFF_coeffnplus1(data)                                 (0x01FF0000&((data)<<16))
#define VE_TAPCOEFF_coeffn(data)                                      (0x000001FF&(data))
#define VE_TAPCOEFF_get_coeffnplus1(data)                             ((0x01FF0000&(data))>>16)
#define VE_TAPCOEFF_get_coeffn(data)                                  (0x000001FF&(data))

#define VE_RM_CUR_CBP                                                 0x1800A2A0
#define VE_RM_CUR_CBP_reg_addr                                        "0xB800A2A0"
#define VE_RM_CUR_CBP_reg                                             0xB800A2A0
#define VE_RM_CUR_CBP_inst_addr                                       "0x00A8"
#define VE_RM_CUR_CBP_inst                                            0x00A8
#define VE_RM_CUR_CBP_cur_cr_cbp_shift                                (20)
#define VE_RM_CUR_CBP_cur_cb_cbp_shift                                (16)
#define VE_RM_CUR_CBP_cur_lu_cbp_shift                                (0)
#define VE_RM_CUR_CBP_cur_cr_cbp_mask                                 (0x00F00000)
#define VE_RM_CUR_CBP_cur_cb_cbp_mask                                 (0x000F0000)
#define VE_RM_CUR_CBP_cur_lu_cbp_mask                                 (0x0000FFFF)
#define VE_RM_CUR_CBP_cur_cr_cbp(data)                                (0x00F00000&((data)<<20))
#define VE_RM_CUR_CBP_cur_cb_cbp(data)                                (0x000F0000&((data)<<16))
#define VE_RM_CUR_CBP_cur_lu_cbp(data)                                (0x0000FFFF&(data))
#define VE_RM_CUR_CBP_get_cur_cr_cbp(data)                            ((0x00F00000&(data))>>20)
#define VE_RM_CUR_CBP_get_cur_cb_cbp(data)                            ((0x000F0000&(data))>>16)
#define VE_RM_CUR_CBP_get_cur_lu_cbp(data)                            (0x0000FFFF&(data))

#define VE_RM_NBR_CBP                                                 0x1800A2A4
#define VE_RM_NBR_CBP_reg_addr                                        "0xB800A2A4"
#define VE_RM_NBR_CBP_reg                                             0xB800A2A4
#define VE_RM_NBR_CBP_inst_addr                                       "0x00A9"
#define VE_RM_NBR_CBP_inst                                            0x00A9
#define VE_RM_NBR_CBP_ul_cr_cbp_shift                                 (18)
#define VE_RM_NBR_CBP_ul_cb_cbp_shift                                 (17)
#define VE_RM_NBR_CBP_ul_lu_cbp_shift                                 (16)
#define VE_RM_NBR_CBP_up_cr_cbp_shift                                 (14)
#define VE_RM_NBR_CBP_up_cb_cbp_shift                                 (12)
#define VE_RM_NBR_CBP_up_lu_cbp_shift                                 (8)
#define VE_RM_NBR_CBP_left_cr_cbp_shift                               (6)
#define VE_RM_NBR_CBP_left_cb_cbp_shift                               (4)
#define VE_RM_NBR_CBP_left_lu_cbp_shift                               (0)
#define VE_RM_NBR_CBP_ul_cr_cbp_mask                                  (0x00040000)
#define VE_RM_NBR_CBP_ul_cb_cbp_mask                                  (0x00020000)
#define VE_RM_NBR_CBP_ul_lu_cbp_mask                                  (0x00010000)
#define VE_RM_NBR_CBP_up_cr_cbp_mask                                  (0x0000C000)
#define VE_RM_NBR_CBP_up_cb_cbp_mask                                  (0x00003000)
#define VE_RM_NBR_CBP_up_lu_cbp_mask                                  (0x00000F00)
#define VE_RM_NBR_CBP_left_cr_cbp_mask                                (0x000000C0)
#define VE_RM_NBR_CBP_left_cb_cbp_mask                                (0x00000030)
#define VE_RM_NBR_CBP_left_lu_cbp_mask                                (0x0000000F)
#define VE_RM_NBR_CBP_ul_cr_cbp(data)                                 (0x00040000&((data)<<18))
#define VE_RM_NBR_CBP_ul_cb_cbp(data)                                 (0x00020000&((data)<<17))
#define VE_RM_NBR_CBP_ul_lu_cbp(data)                                 (0x00010000&((data)<<16))
#define VE_RM_NBR_CBP_up_cr_cbp(data)                                 (0x0000C000&((data)<<14))
#define VE_RM_NBR_CBP_up_cb_cbp(data)                                 (0x00003000&((data)<<12))
#define VE_RM_NBR_CBP_up_lu_cbp(data)                                 (0x00000F00&((data)<<8))
#define VE_RM_NBR_CBP_left_cr_cbp(data)                               (0x000000C0&((data)<<6))
#define VE_RM_NBR_CBP_left_cb_cbp(data)                               (0x00000030&((data)<<4))
#define VE_RM_NBR_CBP_left_lu_cbp(data)                               (0x0000000F&(data))
#define VE_RM_NBR_CBP_get_ul_cr_cbp(data)                             ((0x00040000&(data))>>18)
#define VE_RM_NBR_CBP_get_ul_cb_cbp(data)                             ((0x00020000&(data))>>17)
#define VE_RM_NBR_CBP_get_ul_lu_cbp(data)                             ((0x00010000&(data))>>16)
#define VE_RM_NBR_CBP_get_up_cr_cbp(data)                             ((0x0000C000&(data))>>14)
#define VE_RM_NBR_CBP_get_up_cb_cbp(data)                             ((0x00003000&(data))>>12)
#define VE_RM_NBR_CBP_get_up_lu_cbp(data)                             ((0x00000F00&(data))>>8)
#define VE_RM_NBR_CBP_get_left_cr_cbp(data)                           ((0x000000C0&(data))>>6)
#define VE_RM_NBR_CBP_get_left_cb_cbp(data)                           ((0x00000030&(data))>>4)
#define VE_RM_NBR_CBP_get_left_lu_cbp(data)                           (0x0000000F&(data))

#define VE_RM_MVD                                                     0x1800A2A8
#define VE_RM_MVD_reg_addr                                            "0xB800A2A8"
#define VE_RM_MVD_reg                                                 0xB800A2A8
#define VE_RM_MVD_inst_addr                                           "0x00AA"
#define VE_RM_MVD_inst                                                0x00AA
#define VE_RM_MVD_ul_mvd_shift                                        (24)
#define VE_RM_MVD_up_mvd_shift                                        (20)
#define VE_RM_MVD_left_mvd_shift                                      (16)
#define VE_RM_MVD_cur_mvd_shift                                       (0)
#define VE_RM_MVD_ul_mvd_mask                                         (0x01000000)
#define VE_RM_MVD_up_mvd_mask                                         (0x00F00000)
#define VE_RM_MVD_left_mvd_mask                                       (0x000F0000)
#define VE_RM_MVD_cur_mvd_mask                                        (0x0000FFFF)
#define VE_RM_MVD_ul_mvd(data)                                        (0x01000000&((data)<<24))
#define VE_RM_MVD_up_mvd(data)                                        (0x00F00000&((data)<<20))
#define VE_RM_MVD_left_mvd(data)                                      (0x000F0000&((data)<<16))
#define VE_RM_MVD_cur_mvd(data)                                       (0x0000FFFF&(data))
#define VE_RM_MVD_get_ul_mvd(data)                                    ((0x01000000&(data))>>24)
#define VE_RM_MVD_get_up_mvd(data)                                    ((0x00F00000&(data))>>20)
#define VE_RM_MVD_get_left_mvd(data)                                  ((0x000F0000&(data))>>16)
#define VE_RM_MVD_get_cur_mvd(data)                                   (0x0000FFFF&(data))

#define VE_RM_BS                                                      0x1800A2AC
#define VE_RM_BS_reg_addr                                             "0xB800A2AC"
#define VE_RM_BS_reg                                                  0xB800A2AC
#define VE_RM_BS_inst_addr                                            "0x00AB"
#define VE_RM_BS_inst                                                 0x00AB
#define VE_RM_BS_ul_str_eq2_shift                                     (3)
#define VE_RM_BS_up_str_eq2_shift                                     (2)
#define VE_RM_BS_left_str_eq2_shift                                   (1)
#define VE_RM_BS_cur_str_eq2_shift                                    (0)
#define VE_RM_BS_ul_str_eq2_mask                                      (0x00000008)
#define VE_RM_BS_up_str_eq2_mask                                      (0x00000004)
#define VE_RM_BS_left_str_eq2_mask                                    (0x00000002)
#define VE_RM_BS_cur_str_eq2_mask                                     (0x00000001)
#define VE_RM_BS_ul_str_eq2(data)                                     (0x00000008&((data)<<3))
#define VE_RM_BS_up_str_eq2(data)                                     (0x00000004&((data)<<2))
#define VE_RM_BS_left_str_eq2(data)                                   (0x00000002&((data)<<1))
#define VE_RM_BS_cur_str_eq2(data)                                    (0x00000001&(data))
#define VE_RM_BS_get_ul_str_eq2(data)                                 ((0x00000008&(data))>>3)
#define VE_RM_BS_get_up_str_eq2(data)                                 ((0x00000004&(data))>>2)
#define VE_RM_BS_get_left_str_eq2(data)                               ((0x00000002&(data))>>1)
#define VE_RM_BS_get_cur_str_eq2(data)                                (0x00000001&(data))

#define VE_RMBS_QP                                                    0x1800A2B0
#define VE_RMBS_QP_reg_addr                                           "0xB800A2B0"
#define VE_RMBS_QP_reg                                                0xB800A2B0
#define VE_RMBS_QP_inst_addr                                          "0x00AC"
#define VE_RMBS_QP_inst                                               0x00AC
#define VE_RMBS_QP_write_enable2_shift                                (31)
#define VE_RMBS_QP_refqp_shift                                        (26)
#define VE_RMBS_QP_beta2sel_shift                                     (25)
#define VE_RMBS_QP_write_enable1_shift                                (24)
#define VE_RMBS_QP_up_ul_refdiff_shift                                (23)
#define VE_RMBS_QP_left_ul_refdiff_shift                              (22)
#define VE_RMBS_QP_cur_u_refdiff_shift                                (21)
#define VE_RMBS_QP_cur_l_refdiff_shift                                (20)
#define VE_RMBS_QP_qp_ul_shift                                        (15)
#define VE_RMBS_QP_qp_up_shift                                        (10)
#define VE_RMBS_QP_qp_left_shift                                      (5)
#define VE_RMBS_QP_qp_shift                                           (0)
#define VE_RMBS_QP_write_enable2_mask                                 (0x80000000)
#define VE_RMBS_QP_refqp_mask                                         (0x7C000000)
#define VE_RMBS_QP_beta2sel_mask                                      (0x02000000)
#define VE_RMBS_QP_write_enable1_mask                                 (0x01000000)
#define VE_RMBS_QP_up_ul_refdiff_mask                                 (0x00800000)
#define VE_RMBS_QP_left_ul_refdiff_mask                               (0x00400000)
#define VE_RMBS_QP_cur_u_refdiff_mask                                 (0x00200000)
#define VE_RMBS_QP_cur_l_refdiff_mask                                 (0x00100000)
#define VE_RMBS_QP_qp_ul_mask                                         (0x000F8000)
#define VE_RMBS_QP_qp_up_mask                                         (0x00007C00)
#define VE_RMBS_QP_qp_left_mask                                       (0x000003E0)
#define VE_RMBS_QP_qp_mask                                            (0x0000001F)
#define VE_RMBS_QP_write_enable2(data)                                (0x80000000&((data)<<31))
#define VE_RMBS_QP_refqp(data)                                        (0x7C000000&((data)<<26))
#define VE_RMBS_QP_beta2sel(data)                                     (0x02000000&((data)<<25))
#define VE_RMBS_QP_write_enable1(data)                                (0x01000000&((data)<<24))
#define VE_RMBS_QP_up_ul_refdiff(data)                                (0x00800000&((data)<<23))
#define VE_RMBS_QP_left_ul_refdiff(data)                              (0x00400000&((data)<<22))
#define VE_RMBS_QP_cur_u_refdiff(data)                                (0x00200000&((data)<<21))
#define VE_RMBS_QP_cur_l_refdiff(data)                                (0x00100000&((data)<<20))
#define VE_RMBS_QP_qp_ul(data)                                        (0x000F8000&((data)<<15))
#define VE_RMBS_QP_qp_up(data)                                        (0x00007C00&((data)<<10))
#define VE_RMBS_QP_qp_left(data)                                      (0x000003E0&((data)<<5))
#define VE_RMBS_QP_qp(data)                                           (0x0000001F&(data))
#define VE_RMBS_QP_get_write_enable2(data)                            ((0x80000000&(data))>>31)
#define VE_RMBS_QP_get_refqp(data)                                    ((0x7C000000&(data))>>26)
#define VE_RMBS_QP_get_beta2sel(data)                                 ((0x02000000&(data))>>25)
#define VE_RMBS_QP_get_write_enable1(data)                            ((0x01000000&(data))>>24)
#define VE_RMBS_QP_get_up_ul_refdiff(data)                            ((0x00800000&(data))>>23)
#define VE_RMBS_QP_get_left_ul_refdiff(data)                          ((0x00400000&(data))>>22)
#define VE_RMBS_QP_get_cur_u_refdiff(data)                            ((0x00200000&(data))>>21)
#define VE_RMBS_QP_get_cur_l_refdiff(data)                            ((0x00100000&(data))>>20)
#define VE_RMBS_QP_get_qp_ul(data)                                    ((0x000F8000&(data))>>15)
#define VE_RMBS_QP_get_qp_up(data)                                    ((0x00007C00&(data))>>10)
#define VE_RMBS_QP_get_qp_left(data)                                  ((0x000003E0&(data))>>5)
#define VE_RMBS_QP_get_qp(data)                                       (0x0000001F&(data))

#define VE_RV8_STR_MAP0                                               0x1800A2B4
#define VE_RV8_STR_MAP0_reg_addr                                      "0xB800A2B4"
#define VE_RV8_STR_MAP0_reg                                           0xB800A2B4
#define VE_RV8_STR_MAP0_inst_addr                                     "0x00AD"
#define VE_RV8_STR_MAP0_inst                                          0x00AD
#define VE_RV8_STR_MAP0_str6_initqp_shift                             (25)
#define VE_RV8_STR_MAP0_str5_initqp_shift                             (20)
#define VE_RV8_STR_MAP0_str4_initqp_shift                             (15)
#define VE_RV8_STR_MAP0_str3_initqp_shift                             (10)
#define VE_RV8_STR_MAP0_str2_initqp_shift                             (5)
#define VE_RV8_STR_MAP0_str1_initqp_shift                             (0)
#define VE_RV8_STR_MAP0_str6_initqp_mask                              (0x3E000000)
#define VE_RV8_STR_MAP0_str5_initqp_mask                              (0x01F00000)
#define VE_RV8_STR_MAP0_str4_initqp_mask                              (0x000F8000)
#define VE_RV8_STR_MAP0_str3_initqp_mask                              (0x00007C00)
#define VE_RV8_STR_MAP0_str2_initqp_mask                              (0x000003E0)
#define VE_RV8_STR_MAP0_str1_initqp_mask                              (0x0000001F)
#define VE_RV8_STR_MAP0_str6_initqp(data)                             (0x3E000000&((data)<<25))
#define VE_RV8_STR_MAP0_str5_initqp(data)                             (0x01F00000&((data)<<20))
#define VE_RV8_STR_MAP0_str4_initqp(data)                             (0x000F8000&((data)<<15))
#define VE_RV8_STR_MAP0_str3_initqp(data)                             (0x00007C00&((data)<<10))
#define VE_RV8_STR_MAP0_str2_initqp(data)                             (0x000003E0&((data)<<5))
#define VE_RV8_STR_MAP0_str1_initqp(data)                             (0x0000001F&(data))
#define VE_RV8_STR_MAP0_get_str6_initqp(data)                         ((0x3E000000&(data))>>25)
#define VE_RV8_STR_MAP0_get_str5_initqp(data)                         ((0x01F00000&(data))>>20)
#define VE_RV8_STR_MAP0_get_str4_initqp(data)                         ((0x000F8000&(data))>>15)
#define VE_RV8_STR_MAP0_get_str3_initqp(data)                         ((0x00007C00&(data))>>10)
#define VE_RV8_STR_MAP0_get_str2_initqp(data)                         ((0x000003E0&(data))>>5)
#define VE_RV8_STR_MAP0_get_str1_initqp(data)                         (0x0000001F&(data))

#define VE_RV8_STR_MAP1                                               0x1800A2B8
#define VE_RV8_STR_MAP1_reg_addr                                      "0xB800A2B8"
#define VE_RV8_STR_MAP1_reg                                           0xB800A2B8
#define VE_RV8_STR_MAP1_inst_addr                                     "0x00AE"
#define VE_RV8_STR_MAP1_inst                                          0x00AE
#define VE_RV8_STR_MAP1_str9_initqp_shift                             (10)
#define VE_RV8_STR_MAP1_str8_initqp_shift                             (5)
#define VE_RV8_STR_MAP1_str7_initqp_shift                             (0)
#define VE_RV8_STR_MAP1_str9_initqp_mask                              (0x00007C00)
#define VE_RV8_STR_MAP1_str8_initqp_mask                              (0x000003E0)
#define VE_RV8_STR_MAP1_str7_initqp_mask                              (0x0000001F)
#define VE_RV8_STR_MAP1_str9_initqp(data)                             (0x00007C00&((data)<<10))
#define VE_RV8_STR_MAP1_str8_initqp(data)                             (0x000003E0&((data)<<5))
#define VE_RV8_STR_MAP1_str7_initqp(data)                             (0x0000001F&(data))
#define VE_RV8_STR_MAP1_get_str9_initqp(data)                         ((0x00007C00&(data))>>10)
#define VE_RV8_STR_MAP1_get_str8_initqp(data)                         ((0x000003E0&(data))>>5)
#define VE_RV8_STR_MAP1_get_str7_initqp(data)                         (0x0000001F&(data))

#define VE_RV8_CTRL                                                   0x1800A2BC
#define VE_RV8_CTRL_reg_addr                                          "0xB800A2BC"
#define VE_RV8_CTRL_reg                                               0xB800A2BC
#define VE_RV8_CTRL_inst_addr                                         "0x00AF"
#define VE_RV8_CTRL_inst                                              0x00AF
#define VE_RV8_CTRL_write_enable2_shift                               (4)
#define VE_RV8_CTRL_is_key_frame_shift                                (3)
#define VE_RV8_CTRL_chroma_only_shift                                 (2)
#define VE_RV8_CTRL_write_enable1_shift                               (1)
#define VE_RV8_CTRL_sel_s_chroma_deblock_shift                        (0)
#define VE_RV8_CTRL_write_enable2_mask                                (0x00000010)
#define VE_RV8_CTRL_is_key_frame_mask                                 (0x00000008)
#define VE_RV8_CTRL_chroma_only_mask                                  (0x00000004)
#define VE_RV8_CTRL_write_enable1_mask                                (0x00000002)
#define VE_RV8_CTRL_sel_s_chroma_deblock_mask                         (0x00000001)
#define VE_RV8_CTRL_write_enable2(data)                               (0x00000010&((data)<<4))
#define VE_RV8_CTRL_is_key_frame(data)                                (0x00000008&((data)<<3))
#define VE_RV8_CTRL_chroma_only(data)                                 (0x00000004&((data)<<2))
#define VE_RV8_CTRL_write_enable1(data)                               (0x00000002&((data)<<1))
#define VE_RV8_CTRL_sel_s_chroma_deblock(data)                        (0x00000001&(data))
#define VE_RV8_CTRL_get_write_enable2(data)                           ((0x00000010&(data))>>4)
#define VE_RV8_CTRL_get_is_key_frame(data)                            ((0x00000008&(data))>>3)
#define VE_RV8_CTRL_get_chroma_only(data)                             ((0x00000004&(data))>>2)
#define VE_RV8_CTRL_get_write_enable1(data)                           ((0x00000002&(data))>>1)
#define VE_RV8_CTRL_get_sel_s_chroma_deblock(data)                    (0x00000001&(data))

#define VE_RV9_CLIP                                                   0x1800A2C0
#define VE_RV9_CLIP_reg_addr                                          "0xB800A2C0"
#define VE_RV9_CLIP_reg                                               0xB800A2C0
#define VE_RV9_CLIP_inst_addr                                         "0x00B0"
#define VE_RV9_CLIP_inst                                              0x00B0
#define VE_RV9_CLIP_belowmb_refdiff_en_shift                          (2)
#define VE_RV9_CLIP_subblk2clip_ch_shift                              (1)
#define VE_RV9_CLIP_subblk12clip_lu_shift                             (0)
#define VE_RV9_CLIP_belowmb_refdiff_en_mask                           (0x00000004)
#define VE_RV9_CLIP_subblk2clip_ch_mask                               (0x00000002)
#define VE_RV9_CLIP_subblk12clip_lu_mask                              (0x00000001)
#define VE_RV9_CLIP_belowmb_refdiff_en(data)                          (0x00000004&((data)<<2))
#define VE_RV9_CLIP_subblk2clip_ch(data)                              (0x00000002&((data)<<1))
#define VE_RV9_CLIP_subblk12clip_lu(data)                             (0x00000001&(data))
#define VE_RV9_CLIP_get_belowmb_refdiff_en(data)                      ((0x00000004&(data))>>2)
#define VE_RV9_CLIP_get_subblk2clip_ch(data)                          ((0x00000002&(data))>>1)
#define VE_RV9_CLIP_get_subblk12clip_lu(data)                         (0x00000001&(data))

#define VE_RV_MODE                                                    0x1800A2C4
#define VE_RV_MODE_reg_addr                                           "0xB800A2C4"
#define VE_RV_MODE_reg                                                0xB800A2C4
#define VE_RV_MODE_inst_addr                                          "0x00B1"
#define VE_RV_MODE_inst                                               0x00B1
#define VE_RV_MODE_rv89_mode_shift                                    (0)
#define VE_RV_MODE_rv89_mode_mask                                     (0x0000000F)
#define VE_RV_MODE_rv89_mode(data)                                    (0x0000000F&(data))
#define VE_RV_MODE_get_rv89_mode(data)                                (0x0000000F&(data))

#define VE_BELOWMB_REFDIFF                                            0x1800A2C8
#define VE_BELOWMB_REFDIFF_reg_addr                                   "0xB800A2C8"
#define VE_BELOWMB_REFDIFF_reg                                        0xB800A2C8
#define VE_BELOWMB_REFDIFF_inst_addr                                  "0x00B2"
#define VE_BELOWMB_REFDIFF_inst                                       0x00B2
#define VE_BELOWMB_REFDIFF_u_cur_refdiff_shift                        (0)
#define VE_BELOWMB_REFDIFF_u_cur_refdiff_mask                         (0x00000001)
#define VE_BELOWMB_REFDIFF_u_cur_refdiff(data)                        (0x00000001&(data))
#define VE_BELOWMB_REFDIFF_get_u_cur_refdiff(data)                    (0x00000001&(data))

#define VE_RV8_PFILTSTR_0                                             0x1800A2D0
#define VE_RV8_PFILTSTR_1                                             0x1800A2D4
#define VE_RV8_PFILTSTR_2                                             0x1800A2D8
#define VE_RV8_PFILTSTR_0_reg_addr                                    "0xB800A2D0"
#define VE_RV8_PFILTSTR_1_reg_addr                                    "0xB800A2D4"
#define VE_RV8_PFILTSTR_2_reg_addr                                    "0xB800A2D8"
#define VE_RV8_PFILTSTR_0_reg                                         0xB800A2D0
#define VE_RV8_PFILTSTR_1_reg                                         0xB800A2D4
#define VE_RV8_PFILTSTR_2_reg                                         0xB800A2D8
#define VE_RV8_PFILTSTR_0_inst_addr                                   "0x00B4"
#define VE_RV8_PFILTSTR_0_inst                                        0x00B4
#define VE_RV8_PFILTSTR_1_inst_addr                                   "0x00B5"
#define VE_RV8_PFILTSTR_1_inst                                        0x00B5
#define VE_RV8_PFILTSTR_2_inst_addr                                   "0x00B6"
#define VE_RV8_PFILTSTR_2_inst                                        0x00B6
#define VE_RV8_PFILTSTR_str_inc_shift                                 (0)
#define VE_RV8_PFILTSTR_str_inc_mask                                  (0xFFFFFFFF)
#define VE_RV8_PFILTSTR_str_inc(data)                                 (0xFFFFFFFF&(data))
#define VE_RV8_PFILTSTR_get_str_inc(data)                             (0xFFFFFFFF&(data))

#define VE_RMPREDCCTL                                                 0x1800A2E0
#define VE_RMPREDCCTL_reg_addr                                        "0xB800A2E0"
#define VE_RMPREDCCTL_reg                                             0xB800A2E0
#define VE_RMPREDCCTL_inst_addr                                       "0x00B8"
#define VE_RMPREDCCTL_inst                                            0x00B8
#define VE_RMPREDCCTL_uravail_shift                                   (7)
#define VE_RMPREDCCTL_uavail_shift                                    (6)
#define VE_RMPREDCCTL_lavail_shift                                    (5)
#define VE_RMPREDCCTL_imode_shift                                     (4)
#define VE_RMPREDCCTL_weighted_pred_shift                             (3)
#define VE_RMPREDCCTL_mb_type_shift                                   (1)
#define VE_RMPREDCCTL_intra_shift                                     (0)
#define VE_RMPREDCCTL_uravail_mask                                    (0x00000080)
#define VE_RMPREDCCTL_uavail_mask                                     (0x00000040)
#define VE_RMPREDCCTL_lavail_mask                                     (0x00000020)
#define VE_RMPREDCCTL_imode_mask                                      (0x00000010)
#define VE_RMPREDCCTL_weighted_pred_mask                              (0x00000008)
#define VE_RMPREDCCTL_mb_type_mask                                    (0x00000006)
#define VE_RMPREDCCTL_intra_mask                                      (0x00000001)
#define VE_RMPREDCCTL_uravail(data)                                   (0x00000080&((data)<<7))
#define VE_RMPREDCCTL_uavail(data)                                    (0x00000040&((data)<<6))
#define VE_RMPREDCCTL_lavail(data)                                    (0x00000020&((data)<<5))
#define VE_RMPREDCCTL_imode(data)                                     (0x00000010&((data)<<4))
#define VE_RMPREDCCTL_weighted_pred(data)                             (0x00000008&((data)<<3))
#define VE_RMPREDCCTL_mb_type(data)                                   (0x00000006&((data)<<1))
#define VE_RMPREDCCTL_intra(data)                                     (0x00000001&(data))
#define VE_RMPREDCCTL_get_uravail(data)                               ((0x00000080&(data))>>7)
#define VE_RMPREDCCTL_get_uavail(data)                                ((0x00000040&(data))>>6)
#define VE_RMPREDCCTL_get_lavail(data)                                ((0x00000020&(data))>>5)
#define VE_RMPREDCCTL_get_imode(data)                                 ((0x00000010&(data))>>4)
#define VE_RMPREDCCTL_get_weighted_pred(data)                         ((0x00000008&(data))>>3)
#define VE_RMPREDCCTL_get_mb_type(data)                               ((0x00000006&(data))>>1)
#define VE_RMPREDCCTL_get_intra(data)                                 (0x00000001&(data))

#define VE_RMINTRAM0                                                  0x1800A2E4
#define VE_RMINTRAM0_reg_addr                                         "0xB800A2E4"
#define VE_RMINTRAM0_reg                                              0xB800A2E4
#define VE_RMINTRAM0_inst_addr                                        "0x00B9"
#define VE_RMINTRAM0_inst                                             0x00B9
#define VE_RMINTRAM0_intrap7_shift                                    (28)
#define VE_RMINTRAM0_intrap6_shift                                    (24)
#define VE_RMINTRAM0_intrap5_shift                                    (20)
#define VE_RMINTRAM0_intrap4_shift                                    (16)
#define VE_RMINTRAM0_intrap3_shift                                    (12)
#define VE_RMINTRAM0_intrap2_shift                                    (8)
#define VE_RMINTRAM0_intrap1_shift                                    (4)
#define VE_RMINTRAM0_intrap0_shift                                    (0)
#define VE_RMINTRAM0_intrap7_mask                                     (0xF0000000)
#define VE_RMINTRAM0_intrap6_mask                                     (0x0F000000)
#define VE_RMINTRAM0_intrap5_mask                                     (0x00F00000)
#define VE_RMINTRAM0_intrap4_mask                                     (0x000F0000)
#define VE_RMINTRAM0_intrap3_mask                                     (0x0000F000)
#define VE_RMINTRAM0_intrap2_mask                                     (0x00000F00)
#define VE_RMINTRAM0_intrap1_mask                                     (0x000000F0)
#define VE_RMINTRAM0_intrap0_mask                                     (0x0000000F)
#define VE_RMINTRAM0_intrap7(data)                                    (0xF0000000&((data)<<28))
#define VE_RMINTRAM0_intrap6(data)                                    (0x0F000000&((data)<<24))
#define VE_RMINTRAM0_intrap5(data)                                    (0x00F00000&((data)<<20))
#define VE_RMINTRAM0_intrap4(data)                                    (0x000F0000&((data)<<16))
#define VE_RMINTRAM0_intrap3(data)                                    (0x0000F000&((data)<<12))
#define VE_RMINTRAM0_intrap2(data)                                    (0x00000F00&((data)<<8))
#define VE_RMINTRAM0_intrap1(data)                                    (0x000000F0&((data)<<4))
#define VE_RMINTRAM0_intrap0(data)                                    (0x0000000F&(data))
#define VE_RMINTRAM0_get_intrap7(data)                                ((0xF0000000&(data))>>28)
#define VE_RMINTRAM0_get_intrap6(data)                                ((0x0F000000&(data))>>24)
#define VE_RMINTRAM0_get_intrap5(data)                                ((0x00F00000&(data))>>20)
#define VE_RMINTRAM0_get_intrap4(data)                                ((0x000F0000&(data))>>16)
#define VE_RMINTRAM0_get_intrap3(data)                                ((0x0000F000&(data))>>12)
#define VE_RMINTRAM0_get_intrap2(data)                                ((0x00000F00&(data))>>8)
#define VE_RMINTRAM0_get_intrap1(data)                                ((0x000000F0&(data))>>4)
#define VE_RMINTRAM0_get_intrap0(data)                                (0x0000000F&(data))

#define VE_RMINTRAM1                                                  0x1800A2E8
#define VE_RMINTRAM1_reg_addr                                         "0xB800A2E8"
#define VE_RMINTRAM1_reg                                              0xB800A2E8
#define VE_RMINTRAM1_inst_addr                                        "0x00BA"
#define VE_RMINTRAM1_inst                                             0x00BA
#define VE_RMINTRAM1_intrap15_shift                                   (28)
#define VE_RMINTRAM1_intrap14_shift                                   (24)
#define VE_RMINTRAM1_intrap13_shift                                   (20)
#define VE_RMINTRAM1_intrap12_shift                                   (16)
#define VE_RMINTRAM1_intrap11_shift                                   (12)
#define VE_RMINTRAM1_intrap10_shift                                   (8)
#define VE_RMINTRAM1_intrap9_shift                                    (4)
#define VE_RMINTRAM1_intrap8_shift                                    (0)
#define VE_RMINTRAM1_intrap15_mask                                    (0xF0000000)
#define VE_RMINTRAM1_intrap14_mask                                    (0x0F000000)
#define VE_RMINTRAM1_intrap13_mask                                    (0x00F00000)
#define VE_RMINTRAM1_intrap12_mask                                    (0x000F0000)
#define VE_RMINTRAM1_intrap11_mask                                    (0x0000F000)
#define VE_RMINTRAM1_intrap10_mask                                    (0x00000F00)
#define VE_RMINTRAM1_intrap9_mask                                     (0x000000F0)
#define VE_RMINTRAM1_intrap8_mask                                     (0x0000000F)
#define VE_RMINTRAM1_intrap15(data)                                   (0xF0000000&((data)<<28))
#define VE_RMINTRAM1_intrap14(data)                                   (0x0F000000&((data)<<24))
#define VE_RMINTRAM1_intrap13(data)                                   (0x00F00000&((data)<<20))
#define VE_RMINTRAM1_intrap12(data)                                   (0x000F0000&((data)<<16))
#define VE_RMINTRAM1_intrap11(data)                                   (0x0000F000&((data)<<12))
#define VE_RMINTRAM1_intrap10(data)                                   (0x00000F00&((data)<<8))
#define VE_RMINTRAM1_intrap9(data)                                    (0x000000F0&((data)<<4))
#define VE_RMINTRAM1_intrap8(data)                                    (0x0000000F&(data))
#define VE_RMINTRAM1_get_intrap15(data)                               ((0xF0000000&(data))>>28)
#define VE_RMINTRAM1_get_intrap14(data)                               ((0x0F000000&(data))>>24)
#define VE_RMINTRAM1_get_intrap13(data)                               ((0x00F00000&(data))>>20)
#define VE_RMINTRAM1_get_intrap12(data)                               ((0x000F0000&(data))>>16)
#define VE_RMINTRAM1_get_intrap11(data)                               ((0x0000F000&(data))>>12)
#define VE_RMINTRAM1_get_intrap10(data)                               ((0x00000F00&(data))>>8)
#define VE_RMINTRAM1_get_intrap9(data)                                ((0x000000F0&(data))>>4)
#define VE_RMINTRAM1_get_intrap8(data)                                (0x0000000F&(data))

#define VE_RMCOEFF                                                    0x1800A2EC
#define VE_RMCOEFF_reg_addr                                           "0xB800A2EC"
#define VE_RMCOEFF_reg                                                0xB800A2EC
#define VE_RMCOEFF_inst_addr                                          "0x00BB"
#define VE_RMCOEFF_inst                                               0x00BB
#define VE_RMCOEFF_coeff1_shift                                       (16)
#define VE_RMCOEFF_coeff0_shift                                       (0)
#define VE_RMCOEFF_coeff1_mask                                        (0x3FFF0000)
#define VE_RMCOEFF_coeff0_mask                                        (0x00003FFF)
#define VE_RMCOEFF_coeff1(data)                                       (0x3FFF0000&((data)<<16))
#define VE_RMCOEFF_coeff0(data)                                       (0x00003FFF&(data))
#define VE_RMCOEFF_get_coeff1(data)                                   ((0x3FFF0000&(data))>>16)
#define VE_RMCOEFF_get_coeff0(data)                                   (0x00003FFF&(data))

#define VE_PHASE_INIT_0                                               0x1800A400
#define VE_PHASE_INIT_1                                               0x1800A404
#define VE_PHASE_INIT_2                                               0x1800A408
#define VE_PHASE_INIT_3                                               0x1800A40C
#define VE_PHASE_INIT_0_reg_addr                                      "0xB800A400"
#define VE_PHASE_INIT_1_reg_addr                                      "0xB800A404"
#define VE_PHASE_INIT_2_reg_addr                                      "0xB800A408"
#define VE_PHASE_INIT_3_reg_addr                                      "0xB800A40C"
#define VE_PHASE_INIT_0_reg                                           0xB800A400
#define VE_PHASE_INIT_1_reg                                           0xB800A404
#define VE_PHASE_INIT_2_reg                                           0xB800A408
#define VE_PHASE_INIT_3_reg                                           0xB800A40C
#define VE_PHASE_INIT_0_inst_addr                                     "0x0100"
#define VE_PHASE_INIT_0_inst                                          0x0100
#define VE_PHASE_INIT_1_inst_addr                                     "0x0101"
#define VE_PHASE_INIT_1_inst                                          0x0101
#define VE_PHASE_INIT_2_inst_addr                                     "0x0102"
#define VE_PHASE_INIT_2_inst                                          0x0102
#define VE_PHASE_INIT_3_inst_addr                                     "0x0103"
#define VE_PHASE_INIT_3_inst                                          0x0103
#define VE_PHASE_INIT_init_phase_shift                                (0)
#define VE_PHASE_INIT_init_phase_mask                                 (0x01FFFFFF)
#define VE_PHASE_INIT_init_phase(data)                                (0x01FFFFFF&(data))
#define VE_PHASE_INIT_get_init_phase(data)                            (0x01FFFFFF&(data))

#define VE_PHASE_INC_0                                                0x1800A410
#define VE_PHASE_INC_1                                                0x1800A414
#define VE_PHASE_INC_2                                                0x1800A418
#define VE_PHASE_INC_3                                                0x1800A41C
#define VE_PHASE_INC_0_reg_addr                                       "0xB800A410"
#define VE_PHASE_INC_1_reg_addr                                       "0xB800A414"
#define VE_PHASE_INC_2_reg_addr                                       "0xB800A418"
#define VE_PHASE_INC_3_reg_addr                                       "0xB800A41C"
#define VE_PHASE_INC_0_reg                                            0xB800A410
#define VE_PHASE_INC_1_reg                                            0xB800A414
#define VE_PHASE_INC_2_reg                                            0xB800A418
#define VE_PHASE_INC_3_reg                                            0xB800A41C
#define VE_PHASE_INC_0_inst_addr                                      "0x0104"
#define VE_PHASE_INC_0_inst                                           0x0104
#define VE_PHASE_INC_1_inst_addr                                      "0x0105"
#define VE_PHASE_INC_1_inst                                           0x0105
#define VE_PHASE_INC_2_inst_addr                                      "0x0106"
#define VE_PHASE_INC_2_inst                                           0x0106
#define VE_PHASE_INC_3_inst_addr                                      "0x0107"
#define VE_PHASE_INC_3_inst                                           0x0107
#define VE_PHASE_INC_phase_inc_shift                                  (0)
#define VE_PHASE_INC_phase_inc_mask                                   (0x0001FFFF)
#define VE_PHASE_INC_phase_inc(data)                                  (0x0001FFFF&(data))
#define VE_PHASE_INC_get_phase_inc(data)                              (0x0001FFFF&(data))

#define VE_PHASE_OUT_0                                                0x1800A420
#define VE_PHASE_OUT_1                                                0x1800A424
#define VE_PHASE_OUT_2                                                0x1800A428
#define VE_PHASE_OUT_3                                                0x1800A42C
#define VE_PHASE_OUT_0_reg_addr                                       "0xB800A420"
#define VE_PHASE_OUT_1_reg_addr                                       "0xB800A424"
#define VE_PHASE_OUT_2_reg_addr                                       "0xB800A428"
#define VE_PHASE_OUT_3_reg_addr                                       "0xB800A42C"
#define VE_PHASE_OUT_0_reg                                            0xB800A420
#define VE_PHASE_OUT_1_reg                                            0xB800A424
#define VE_PHASE_OUT_2_reg                                            0xB800A428
#define VE_PHASE_OUT_3_reg                                            0xB800A42C
#define VE_PHASE_OUT_0_inst_addr                                      "0x0108"
#define VE_PHASE_OUT_0_inst                                           0x0108
#define VE_PHASE_OUT_1_inst_addr                                      "0x0109"
#define VE_PHASE_OUT_1_inst                                           0x0109
#define VE_PHASE_OUT_2_inst_addr                                      "0x010A"
#define VE_PHASE_OUT_2_inst                                           0x010A
#define VE_PHASE_OUT_3_inst_addr                                      "0x010B"
#define VE_PHASE_OUT_3_inst                                           0x010B
#define VE_PHASE_OUT_final_phase_shift                                (0)
#define VE_PHASE_OUT_final_phase_mask                                 (0x01FFFFFF)
#define VE_PHASE_OUT_final_phase(data)                                (0x01FFFFFF&(data))
#define VE_PHASE_OUT_get_final_phase(data)                            (0x01FFFFFF&(data))

#define VE_TAPCOEFF1_0                                                0x1800A430
#define VE_TAPCOEFF1_1                                                0x1800A434
#define VE_TAPCOEFF1_2                                                0x1800A438
#define VE_TAPCOEFF1_3                                                0x1800A43C
#define VE_TAPCOEFF1_4                                                0x1800A440
#define VE_TAPCOEFF1_5                                                0x1800A444
#define VE_TAPCOEFF1_6                                                0x1800A448
#define VE_TAPCOEFF1_7                                                0x1800A44C
#define VE_TAPCOEFF1_8                                                0x1800A450
#define VE_TAPCOEFF1_9                                                0x1800A454
#define VE_TAPCOEFF1_10                                               0x1800A458
#define VE_TAPCOEFF1_11                                               0x1800A45C
#define VE_TAPCOEFF1_12                                               0x1800A460
#define VE_TAPCOEFF1_13                                               0x1800A464
#define VE_TAPCOEFF1_14                                               0x1800A468
#define VE_TAPCOEFF1_15                                               0x1800A46C
#define VE_TAPCOEFF1_16                                               0x1800A470
#define VE_TAPCOEFF1_17                                               0x1800A474
#define VE_TAPCOEFF1_18                                               0x1800A478
#define VE_TAPCOEFF1_19                                               0x1800A47C
#define VE_TAPCOEFF1_20                                               0x1800A480
#define VE_TAPCOEFF1_21                                               0x1800A484
#define VE_TAPCOEFF1_22                                               0x1800A488
#define VE_TAPCOEFF1_23                                               0x1800A48C
#define VE_TAPCOEFF1_0_reg_addr                                       "0xB800A430"
#define VE_TAPCOEFF1_1_reg_addr                                       "0xB800A434"
#define VE_TAPCOEFF1_2_reg_addr                                       "0xB800A438"
#define VE_TAPCOEFF1_3_reg_addr                                       "0xB800A43C"
#define VE_TAPCOEFF1_4_reg_addr                                       "0xB800A440"
#define VE_TAPCOEFF1_5_reg_addr                                       "0xB800A444"
#define VE_TAPCOEFF1_6_reg_addr                                       "0xB800A448"
#define VE_TAPCOEFF1_7_reg_addr                                       "0xB800A44C"
#define VE_TAPCOEFF1_8_reg_addr                                       "0xB800A450"
#define VE_TAPCOEFF1_9_reg_addr                                       "0xB800A454"
#define VE_TAPCOEFF1_10_reg_addr                                      "0xB800A458"
#define VE_TAPCOEFF1_11_reg_addr                                      "0xB800A45C"
#define VE_TAPCOEFF1_12_reg_addr                                      "0xB800A460"
#define VE_TAPCOEFF1_13_reg_addr                                      "0xB800A464"
#define VE_TAPCOEFF1_14_reg_addr                                      "0xB800A468"
#define VE_TAPCOEFF1_15_reg_addr                                      "0xB800A46C"
#define VE_TAPCOEFF1_16_reg_addr                                      "0xB800A470"
#define VE_TAPCOEFF1_17_reg_addr                                      "0xB800A474"
#define VE_TAPCOEFF1_18_reg_addr                                      "0xB800A478"
#define VE_TAPCOEFF1_19_reg_addr                                      "0xB800A47C"
#define VE_TAPCOEFF1_20_reg_addr                                      "0xB800A480"
#define VE_TAPCOEFF1_21_reg_addr                                      "0xB800A484"
#define VE_TAPCOEFF1_22_reg_addr                                      "0xB800A488"
#define VE_TAPCOEFF1_23_reg_addr                                      "0xB800A48C"
#define VE_TAPCOEFF1_0_reg                                            0xB800A430
#define VE_TAPCOEFF1_1_reg                                            0xB800A434
#define VE_TAPCOEFF1_2_reg                                            0xB800A438
#define VE_TAPCOEFF1_3_reg                                            0xB800A43C
#define VE_TAPCOEFF1_4_reg                                            0xB800A440
#define VE_TAPCOEFF1_5_reg                                            0xB800A444
#define VE_TAPCOEFF1_6_reg                                            0xB800A448
#define VE_TAPCOEFF1_7_reg                                            0xB800A44C
#define VE_TAPCOEFF1_8_reg                                            0xB800A450
#define VE_TAPCOEFF1_9_reg                                            0xB800A454
#define VE_TAPCOEFF1_10_reg                                           0xB800A458
#define VE_TAPCOEFF1_11_reg                                           0xB800A45C
#define VE_TAPCOEFF1_12_reg                                           0xB800A460
#define VE_TAPCOEFF1_13_reg                                           0xB800A464
#define VE_TAPCOEFF1_14_reg                                           0xB800A468
#define VE_TAPCOEFF1_15_reg                                           0xB800A46C
#define VE_TAPCOEFF1_16_reg                                           0xB800A470
#define VE_TAPCOEFF1_17_reg                                           0xB800A474
#define VE_TAPCOEFF1_18_reg                                           0xB800A478
#define VE_TAPCOEFF1_19_reg                                           0xB800A47C
#define VE_TAPCOEFF1_20_reg                                           0xB800A480
#define VE_TAPCOEFF1_21_reg                                           0xB800A484
#define VE_TAPCOEFF1_22_reg                                           0xB800A488
#define VE_TAPCOEFF1_23_reg                                           0xB800A48C
#define VE_TAPCOEFF1_0_inst_addr                                      "0x010C"
#define VE_TAPCOEFF1_0_inst                                           0x010C
#define VE_TAPCOEFF1_1_inst_addr                                      "0x010D"
#define VE_TAPCOEFF1_1_inst                                           0x010D
#define VE_TAPCOEFF1_2_inst_addr                                      "0x010E"
#define VE_TAPCOEFF1_2_inst                                           0x010E
#define VE_TAPCOEFF1_3_inst_addr                                      "0x010F"
#define VE_TAPCOEFF1_3_inst                                           0x010F
#define VE_TAPCOEFF1_4_inst_addr                                      "0x0110"
#define VE_TAPCOEFF1_4_inst                                           0x0110
#define VE_TAPCOEFF1_5_inst_addr                                      "0x0111"
#define VE_TAPCOEFF1_5_inst                                           0x0111
#define VE_TAPCOEFF1_6_inst_addr                                      "0x0112"
#define VE_TAPCOEFF1_6_inst                                           0x0112
#define VE_TAPCOEFF1_7_inst_addr                                      "0x0113"
#define VE_TAPCOEFF1_7_inst                                           0x0113
#define VE_TAPCOEFF1_8_inst_addr                                      "0x0114"
#define VE_TAPCOEFF1_8_inst                                           0x0114
#define VE_TAPCOEFF1_9_inst_addr                                      "0x0115"
#define VE_TAPCOEFF1_9_inst                                           0x0115
#define VE_TAPCOEFF1_10_inst_addr                                     "0x0116"
#define VE_TAPCOEFF1_10_inst                                          0x0116
#define VE_TAPCOEFF1_11_inst_addr                                     "0x0117"
#define VE_TAPCOEFF1_11_inst                                          0x0117
#define VE_TAPCOEFF1_12_inst_addr                                     "0x0118"
#define VE_TAPCOEFF1_12_inst                                          0x0118
#define VE_TAPCOEFF1_13_inst_addr                                     "0x0119"
#define VE_TAPCOEFF1_13_inst                                          0x0119
#define VE_TAPCOEFF1_14_inst_addr                                     "0x011A"
#define VE_TAPCOEFF1_14_inst                                          0x011A
#define VE_TAPCOEFF1_15_inst_addr                                     "0x011B"
#define VE_TAPCOEFF1_15_inst                                          0x011B
#define VE_TAPCOEFF1_16_inst_addr                                     "0x011C"
#define VE_TAPCOEFF1_16_inst                                          0x011C
#define VE_TAPCOEFF1_17_inst_addr                                     "0x011D"
#define VE_TAPCOEFF1_17_inst                                          0x011D
#define VE_TAPCOEFF1_18_inst_addr                                     "0x011E"
#define VE_TAPCOEFF1_18_inst                                          0x011E
#define VE_TAPCOEFF1_19_inst_addr                                     "0x011F"
#define VE_TAPCOEFF1_19_inst                                          0x011F
#define VE_TAPCOEFF1_20_inst_addr                                     "0x0120"
#define VE_TAPCOEFF1_20_inst                                          0x0120
#define VE_TAPCOEFF1_21_inst_addr                                     "0x0121"
#define VE_TAPCOEFF1_21_inst                                          0x0121
#define VE_TAPCOEFF1_22_inst_addr                                     "0x0122"
#define VE_TAPCOEFF1_22_inst                                          0x0122
#define VE_TAPCOEFF1_23_inst_addr                                     "0x0123"
#define VE_TAPCOEFF1_23_inst                                          0x0123
#define VE_TAPCOEFF1_coeffnplus1_shift                                (16)
#define VE_TAPCOEFF1_coeffn_shift                                     (0)
#define VE_TAPCOEFF1_coeffnplus1_mask                                 (0x3FFF0000)
#define VE_TAPCOEFF1_coeffn_mask                                      (0x00003FFF)
#define VE_TAPCOEFF1_coeffnplus1(data)                                (0x3FFF0000&((data)<<16))
#define VE_TAPCOEFF1_coeffn(data)                                     (0x00003FFF&(data))
#define VE_TAPCOEFF1_get_coeffnplus1(data)                            ((0x3FFF0000&(data))>>16)
#define VE_TAPCOEFF1_get_coeffn(data)                                 (0x00003FFF&(data))

#define VE_TAPCOEFF2_0                                                0x1800A490
#define VE_TAPCOEFF2_1                                                0x1800A494
#define VE_TAPCOEFF2_2                                                0x1800A498
#define VE_TAPCOEFF2_3                                                0x1800A49C
#define VE_TAPCOEFF2_4                                                0x1800A4A0
#define VE_TAPCOEFF2_5                                                0x1800A4A4
#define VE_TAPCOEFF2_6                                                0x1800A4A8
#define VE_TAPCOEFF2_7                                                0x1800A4AC
#define VE_TAPCOEFF2_8                                                0x1800A4B0
#define VE_TAPCOEFF2_9                                                0x1800A4B4
#define VE_TAPCOEFF2_10                                               0x1800A4B8
#define VE_TAPCOEFF2_11                                               0x1800A4BC
#define VE_TAPCOEFF2_12                                               0x1800A4C0
#define VE_TAPCOEFF2_13                                               0x1800A4C4
#define VE_TAPCOEFF2_14                                               0x1800A4C8
#define VE_TAPCOEFF2_15                                               0x1800A4CC
#define VE_TAPCOEFF2_16                                               0x1800A4D0
#define VE_TAPCOEFF2_17                                               0x1800A4D4
#define VE_TAPCOEFF2_18                                               0x1800A4D8
#define VE_TAPCOEFF2_19                                               0x1800A4DC
#define VE_TAPCOEFF2_20                                               0x1800A4E0
#define VE_TAPCOEFF2_21                                               0x1800A4E4
#define VE_TAPCOEFF2_22                                               0x1800A4E8
#define VE_TAPCOEFF2_23                                               0x1800A4EC
#define VE_TAPCOEFF2_0_reg_addr                                       "0xB800A490"
#define VE_TAPCOEFF2_1_reg_addr                                       "0xB800A494"
#define VE_TAPCOEFF2_2_reg_addr                                       "0xB800A498"
#define VE_TAPCOEFF2_3_reg_addr                                       "0xB800A49C"
#define VE_TAPCOEFF2_4_reg_addr                                       "0xB800A4A0"
#define VE_TAPCOEFF2_5_reg_addr                                       "0xB800A4A4"
#define VE_TAPCOEFF2_6_reg_addr                                       "0xB800A4A8"
#define VE_TAPCOEFF2_7_reg_addr                                       "0xB800A4AC"
#define VE_TAPCOEFF2_8_reg_addr                                       "0xB800A4B0"
#define VE_TAPCOEFF2_9_reg_addr                                       "0xB800A4B4"
#define VE_TAPCOEFF2_10_reg_addr                                      "0xB800A4B8"
#define VE_TAPCOEFF2_11_reg_addr                                      "0xB800A4BC"
#define VE_TAPCOEFF2_12_reg_addr                                      "0xB800A4C0"
#define VE_TAPCOEFF2_13_reg_addr                                      "0xB800A4C4"
#define VE_TAPCOEFF2_14_reg_addr                                      "0xB800A4C8"
#define VE_TAPCOEFF2_15_reg_addr                                      "0xB800A4CC"
#define VE_TAPCOEFF2_16_reg_addr                                      "0xB800A4D0"
#define VE_TAPCOEFF2_17_reg_addr                                      "0xB800A4D4"
#define VE_TAPCOEFF2_18_reg_addr                                      "0xB800A4D8"
#define VE_TAPCOEFF2_19_reg_addr                                      "0xB800A4DC"
#define VE_TAPCOEFF2_20_reg_addr                                      "0xB800A4E0"
#define VE_TAPCOEFF2_21_reg_addr                                      "0xB800A4E4"
#define VE_TAPCOEFF2_22_reg_addr                                      "0xB800A4E8"
#define VE_TAPCOEFF2_23_reg_addr                                      "0xB800A4EC"
#define VE_TAPCOEFF2_0_reg                                            0xB800A490
#define VE_TAPCOEFF2_1_reg                                            0xB800A494
#define VE_TAPCOEFF2_2_reg                                            0xB800A498
#define VE_TAPCOEFF2_3_reg                                            0xB800A49C
#define VE_TAPCOEFF2_4_reg                                            0xB800A4A0
#define VE_TAPCOEFF2_5_reg                                            0xB800A4A4
#define VE_TAPCOEFF2_6_reg                                            0xB800A4A8
#define VE_TAPCOEFF2_7_reg                                            0xB800A4AC
#define VE_TAPCOEFF2_8_reg                                            0xB800A4B0
#define VE_TAPCOEFF2_9_reg                                            0xB800A4B4
#define VE_TAPCOEFF2_10_reg                                           0xB800A4B8
#define VE_TAPCOEFF2_11_reg                                           0xB800A4BC
#define VE_TAPCOEFF2_12_reg                                           0xB800A4C0
#define VE_TAPCOEFF2_13_reg                                           0xB800A4C4
#define VE_TAPCOEFF2_14_reg                                           0xB800A4C8
#define VE_TAPCOEFF2_15_reg                                           0xB800A4CC
#define VE_TAPCOEFF2_16_reg                                           0xB800A4D0
#define VE_TAPCOEFF2_17_reg                                           0xB800A4D4
#define VE_TAPCOEFF2_18_reg                                           0xB800A4D8
#define VE_TAPCOEFF2_19_reg                                           0xB800A4DC
#define VE_TAPCOEFF2_20_reg                                           0xB800A4E0
#define VE_TAPCOEFF2_21_reg                                           0xB800A4E4
#define VE_TAPCOEFF2_22_reg                                           0xB800A4E8
#define VE_TAPCOEFF2_23_reg                                           0xB800A4EC
#define VE_TAPCOEFF2_0_inst_addr                                      "0x0124"
#define VE_TAPCOEFF2_0_inst                                           0x0124
#define VE_TAPCOEFF2_1_inst_addr                                      "0x0125"
#define VE_TAPCOEFF2_1_inst                                           0x0125
#define VE_TAPCOEFF2_2_inst_addr                                      "0x0126"
#define VE_TAPCOEFF2_2_inst                                           0x0126
#define VE_TAPCOEFF2_3_inst_addr                                      "0x0127"
#define VE_TAPCOEFF2_3_inst                                           0x0127
#define VE_TAPCOEFF2_4_inst_addr                                      "0x0128"
#define VE_TAPCOEFF2_4_inst                                           0x0128
#define VE_TAPCOEFF2_5_inst_addr                                      "0x0129"
#define VE_TAPCOEFF2_5_inst                                           0x0129
#define VE_TAPCOEFF2_6_inst_addr                                      "0x012A"
#define VE_TAPCOEFF2_6_inst                                           0x012A
#define VE_TAPCOEFF2_7_inst_addr                                      "0x012B"
#define VE_TAPCOEFF2_7_inst                                           0x012B
#define VE_TAPCOEFF2_8_inst_addr                                      "0x012C"
#define VE_TAPCOEFF2_8_inst                                           0x012C
#define VE_TAPCOEFF2_9_inst_addr                                      "0x012D"
#define VE_TAPCOEFF2_9_inst                                           0x012D
#define VE_TAPCOEFF2_10_inst_addr                                     "0x012E"
#define VE_TAPCOEFF2_10_inst                                          0x012E
#define VE_TAPCOEFF2_11_inst_addr                                     "0x012F"
#define VE_TAPCOEFF2_11_inst                                          0x012F
#define VE_TAPCOEFF2_12_inst_addr                                     "0x0130"
#define VE_TAPCOEFF2_12_inst                                          0x0130
#define VE_TAPCOEFF2_13_inst_addr                                     "0x0131"
#define VE_TAPCOEFF2_13_inst                                          0x0131
#define VE_TAPCOEFF2_14_inst_addr                                     "0x0132"
#define VE_TAPCOEFF2_14_inst                                          0x0132
#define VE_TAPCOEFF2_15_inst_addr                                     "0x0133"
#define VE_TAPCOEFF2_15_inst                                          0x0133
#define VE_TAPCOEFF2_16_inst_addr                                     "0x0134"
#define VE_TAPCOEFF2_16_inst                                          0x0134
#define VE_TAPCOEFF2_17_inst_addr                                     "0x0135"
#define VE_TAPCOEFF2_17_inst                                          0x0135
#define VE_TAPCOEFF2_18_inst_addr                                     "0x0136"
#define VE_TAPCOEFF2_18_inst                                          0x0136
#define VE_TAPCOEFF2_19_inst_addr                                     "0x0137"
#define VE_TAPCOEFF2_19_inst                                          0x0137
#define VE_TAPCOEFF2_20_inst_addr                                     "0x0138"
#define VE_TAPCOEFF2_20_inst                                          0x0138
#define VE_TAPCOEFF2_21_inst_addr                                     "0x0139"
#define VE_TAPCOEFF2_21_inst                                          0x0139
#define VE_TAPCOEFF2_22_inst_addr                                     "0x013A"
#define VE_TAPCOEFF2_22_inst                                          0x013A
#define VE_TAPCOEFF2_23_inst_addr                                     "0x013B"
#define VE_TAPCOEFF2_23_inst                                          0x013B
#define VE_TAPCOEFF2_coeffnplus1_shift                                (16)
#define VE_TAPCOEFF2_coeffn_shift                                     (0)
#define VE_TAPCOEFF2_coeffnplus1_mask                                 (0x3FFF0000)
#define VE_TAPCOEFF2_coeffn_mask                                      (0x00003FFF)
#define VE_TAPCOEFF2_coeffnplus1(data)                                (0x3FFF0000&((data)<<16))
#define VE_TAPCOEFF2_coeffn(data)                                     (0x00003FFF&(data))
#define VE_TAPCOEFF2_get_coeffnplus1(data)                            ((0x3FFF0000&(data))>>16)
#define VE_TAPCOEFF2_get_coeffn(data)                                 (0x00003FFF&(data))

#define VE_RMRPR_CNTL                                                 0x1800A2F0
#define VE_RMRPR_CNTL_reg_addr                                        "0xB800A2F0"
#define VE_RMRPR_CNTL_reg                                             0xB800A2F0
#define VE_RMRPR_CNTL_inst_addr                                       "0x00BC"
#define VE_RMRPR_CNTL_inst                                            0x00BC
#define VE_RMRPR_CNTL_rcrpr_shift                                     (26)
#define VE_RMRPR_CNTL_color_cr_shift                                  (18)
#define VE_RMRPR_CNTL_color_cb_shift                                  (10)
#define VE_RMRPR_CNTL_color_y_shift                                   (2)
#define VE_RMRPR_CNTL_fill_mode_shift                                 (0)
#define VE_RMRPR_CNTL_rcrpr_mask                                      (0x04000000)
#define VE_RMRPR_CNTL_color_cr_mask                                   (0x03FC0000)
#define VE_RMRPR_CNTL_color_cb_mask                                   (0x0003FC00)
#define VE_RMRPR_CNTL_color_y_mask                                    (0x000003FC)
#define VE_RMRPR_CNTL_fill_mode_mask                                  (0x00000003)
#define VE_RMRPR_CNTL_rcrpr(data)                                     (0x04000000&((data)<<26))
#define VE_RMRPR_CNTL_color_cr(data)                                  (0x03FC0000&((data)<<18))
#define VE_RMRPR_CNTL_color_cb(data)                                  (0x0003FC00&((data)<<10))
#define VE_RMRPR_CNTL_color_y(data)                                   (0x000003FC&((data)<<2))
#define VE_RMRPR_CNTL_fill_mode(data)                                 (0x00000003&(data))
#define VE_RMRPR_CNTL_get_rcrpr(data)                                 ((0x04000000&(data))>>26)
#define VE_RMRPR_CNTL_get_color_cr(data)                              ((0x03FC0000&(data))>>18)
#define VE_RMRPR_CNTL_get_color_cb(data)                              ((0x0003FC00&(data))>>10)
#define VE_RMRPR_CNTL_get_color_y(data)                               ((0x000003FC&(data))>>2)
#define VE_RMRPR_CNTL_get_fill_mode(data)                             (0x00000003&(data))

#define VE_RMRPR_PAR                                                  0x1800A2F4
#define VE_RMRPR_PAR_reg_addr                                         "0xB800A2F4"
#define VE_RMRPR_PAR_reg                                              0xB800A2F4
#define VE_RMRPR_PAR_inst_addr                                        "0x00BD"
#define VE_RMRPR_PAR_inst                                             0x00BD
#define VE_RMRPR_PAR_m_shift                                          (11)
#define VE_RMRPR_PAR_pixel_offset_shift                               (0)
#define VE_RMRPR_PAR_m_mask                                           (0x00007800)
#define VE_RMRPR_PAR_pixel_offset_mask                                (0x000007FF)
#define VE_RMRPR_PAR_m(data)                                          (0x00007800&((data)<<11))
#define VE_RMRPR_PAR_pixel_offset(data)                               (0x000007FF&(data))
#define VE_RMRPR_PAR_get_m(data)                                      ((0x00007800&(data))>>11)
#define VE_RMRPR_PAR_get_pixel_offset(data)                           (0x000007FF&(data))

#define VE_RMRPR_AX                                                   0x1800A2F8
#define VE_RMRPR_AX_reg_addr                                          "0xB800A2F8"
#define VE_RMRPR_AX_reg                                               0xB800A2F8
#define VE_RMRPR_AX_inst_addr                                         "0x00BE"
#define VE_RMRPR_AX_inst                                              0x00BE
#define VE_RMRPR_AX_ax_shift                                          (0)
#define VE_RMRPR_AX_ax_mask                                           (0xFFFFFFFF)
#define VE_RMRPR_AX_ax(data)                                          (0xFFFFFFFF&(data))
#define VE_RMRPR_AX_get_ax(data)                                      (0xFFFFFFFF&(data))

#define VE_RMRPR_AY                                                   0x1800A2FC
#define VE_RMRPR_AY_reg_addr                                          "0xB800A2FC"
#define VE_RMRPR_AY_reg                                               0xB800A2FC
#define VE_RMRPR_AY_inst_addr                                         "0x00BF"
#define VE_RMRPR_AY_inst                                              0x00BF
#define VE_RMRPR_AY_ay_shift                                          (0)
#define VE_RMRPR_AY_ay_mask                                           (0xFFFFFFFF)
#define VE_RMRPR_AY_ay(data)                                          (0xFFFFFFFF&(data))
#define VE_RMRPR_AY_get_ay(data)                                      (0xFFFFFFFF&(data))

#define VE_RMRPR_AXINC                                                0x1800A4F0
#define VE_RMRPR_AXINC_reg_addr                                       "0xB800A4F0"
#define VE_RMRPR_AXINC_reg                                            0xB800A4F0
#define VE_RMRPR_AXINC_inst_addr                                      "0x013C"
#define VE_RMRPR_AXINC_inst                                           0x013C
#define VE_RMRPR_AXINC_ax_inc_shift                                   (0)
#define VE_RMRPR_AXINC_ax_inc_mask                                    (0xFFFFFFFF)
#define VE_RMRPR_AXINC_ax_inc(data)                                   (0xFFFFFFFF&(data))
#define VE_RMRPR_AXINC_get_ax_inc(data)                               (0xFFFFFFFF&(data))

#define VE_RMRPR_PICINFO                                              0x1800A4F4
#define VE_RMRPR_PICINFO_reg_addr                                     "0xB800A4F4"
#define VE_RMRPR_PICINFO_reg                                          0xB800A4F4
#define VE_RMRPR_PICINFO_inst_addr                                    "0x013D"
#define VE_RMRPR_PICINFO_inst                                         0x013D
#define VE_RMRPR_PICINFO_picmb_h_shift                                (7)
#define VE_RMRPR_PICINFO_picmb_w_shift                                (0)
#define VE_RMRPR_PICINFO_picmb_h_mask                                 (0x00001F80)
#define VE_RMRPR_PICINFO_picmb_w_mask                                 (0x0000007F)
#define VE_RMRPR_PICINFO_picmb_h(data)                                (0x00001F80&((data)<<7))
#define VE_RMRPR_PICINFO_picmb_w(data)                                (0x0000007F&(data))
#define VE_RMRPR_PICINFO_get_picmb_h(data)                            ((0x00001F80&(data))>>7)
#define VE_RMRPR_PICINFO_get_picmb_w(data)                            (0x0000007F&(data))

#define VE_BASEA_0                                                    0x1800A280
#define VE_BASEA_1                                                    0x1800A284
#define VE_BASEA_2                                                    0x1800A288
#define VE_BASEA_3                                                    0x1800A28C
#define VE_BASEA_0_reg_addr                                           "0xB800A280"
#define VE_BASEA_1_reg_addr                                           "0xB800A284"
#define VE_BASEA_2_reg_addr                                           "0xB800A288"
#define VE_BASEA_3_reg_addr                                           "0xB800A28C"
#define VE_BASEA_0_reg                                                0xB800A280
#define VE_BASEA_1_reg                                                0xB800A284
#define VE_BASEA_2_reg                                                0xB800A288
#define VE_BASEA_3_reg                                                0xB800A28C
#define VE_BASEA_0_inst_addr                                          "0x00A0"
#define VE_BASEA_0_inst                                               0x00A0
#define VE_BASEA_1_inst_addr                                          "0x00A1"
#define VE_BASEA_1_inst                                               0x00A1
#define VE_BASEA_2_inst_addr                                          "0x00A2"
#define VE_BASEA_2_inst                                               0x00A2
#define VE_BASEA_3_inst_addr                                          "0x00A3"
#define VE_BASEA_3_inst                                               0x00A3
#define VE_BASEA_basea_shift                                          (0)
#define VE_BASEA_basea_mask                                           (0x00000FFF)
#define VE_BASEA_basea(data)                                          (0x00000FFF&(data))
#define VE_BASEA_get_basea(data)                                      (0x00000FFF&(data))

#define VE_OFFSETA_0                                                  0x1800A290
#define VE_OFFSETA_1                                                  0x1800A294
#define VE_OFFSETA_2                                                  0x1800A298
#define VE_OFFSETA_3                                                  0x1800A29C
#define VE_OFFSETA_0_reg_addr                                         "0xB800A290"
#define VE_OFFSETA_1_reg_addr                                         "0xB800A294"
#define VE_OFFSETA_2_reg_addr                                         "0xB800A298"
#define VE_OFFSETA_3_reg_addr                                         "0xB800A29C"
#define VE_OFFSETA_0_reg                                              0xB800A290
#define VE_OFFSETA_1_reg                                              0xB800A294
#define VE_OFFSETA_2_reg                                              0xB800A298
#define VE_OFFSETA_3_reg                                              0xB800A29C
#define VE_OFFSETA_0_inst_addr                                        "0x00A4"
#define VE_OFFSETA_0_inst                                             0x00A4
#define VE_OFFSETA_1_inst_addr                                        "0x00A5"
#define VE_OFFSETA_1_inst                                             0x00A5
#define VE_OFFSETA_2_inst_addr                                        "0x00A6"
#define VE_OFFSETA_2_inst                                             0x00A6
#define VE_OFFSETA_3_inst_addr                                        "0x00A7"
#define VE_OFFSETA_3_inst                                             0x00A7
#define VE_OFFSETA_offseta_shift                                      (0)
#define VE_OFFSETA_offseta_mask                                       (0x00000FFF)
#define VE_OFFSETA_offseta(data)                                      (0x00000FFF&(data))
#define VE_OFFSETA_get_offseta(data)                                  (0x00000FFF&(data))

#define VE_DMAREG1_0                                                  0x1800A300
#define VE_DMAREG1_1                                                  0x1800A304
#define VE_DMAREG1_2                                                  0x1800A308
#define VE_DMAREG1_3                                                  0x1800A30C
#define VE_DMAREG1_4                                                  0x1800A310
#define VE_DMAREG1_5                                                  0x1800A314
#define VE_DMAREG1_6                                                  0x1800A318
#define VE_DMAREG1_7                                                  0x1800A31C
#define VE_DMAREG1_8                                                  0x1800A320
#define VE_DMAREG1_9                                                  0x1800A324
#define VE_DMAREG1_10                                                 0x1800A328
#define VE_DMAREG1_11                                                 0x1800A32C
#define VE_DMAREG1_12                                                 0x1800A330
#define VE_DMAREG1_13                                                 0x1800A334
#define VE_DMAREG1_14                                                 0x1800A338
#define VE_DMAREG1_15                                                 0x1800A33C
#define VE_DMAREG1_0_reg_addr                                         "0xB800A300"
#define VE_DMAREG1_1_reg_addr                                         "0xB800A304"
#define VE_DMAREG1_2_reg_addr                                         "0xB800A308"
#define VE_DMAREG1_3_reg_addr                                         "0xB800A30C"
#define VE_DMAREG1_4_reg_addr                                         "0xB800A310"
#define VE_DMAREG1_5_reg_addr                                         "0xB800A314"
#define VE_DMAREG1_6_reg_addr                                         "0xB800A318"
#define VE_DMAREG1_7_reg_addr                                         "0xB800A31C"
#define VE_DMAREG1_8_reg_addr                                         "0xB800A320"
#define VE_DMAREG1_9_reg_addr                                         "0xB800A324"
#define VE_DMAREG1_10_reg_addr                                        "0xB800A328"
#define VE_DMAREG1_11_reg_addr                                        "0xB800A32C"
#define VE_DMAREG1_12_reg_addr                                        "0xB800A330"
#define VE_DMAREG1_13_reg_addr                                        "0xB800A334"
#define VE_DMAREG1_14_reg_addr                                        "0xB800A338"
#define VE_DMAREG1_15_reg_addr                                        "0xB800A33C"
#define VE_DMAREG1_0_reg                                              0xB800A300
#define VE_DMAREG1_1_reg                                              0xB800A304
#define VE_DMAREG1_2_reg                                              0xB800A308
#define VE_DMAREG1_3_reg                                              0xB800A30C
#define VE_DMAREG1_4_reg                                              0xB800A310
#define VE_DMAREG1_5_reg                                              0xB800A314
#define VE_DMAREG1_6_reg                                              0xB800A318
#define VE_DMAREG1_7_reg                                              0xB800A31C
#define VE_DMAREG1_8_reg                                              0xB800A320
#define VE_DMAREG1_9_reg                                              0xB800A324
#define VE_DMAREG1_10_reg                                             0xB800A328
#define VE_DMAREG1_11_reg                                             0xB800A32C
#define VE_DMAREG1_12_reg                                             0xB800A330
#define VE_DMAREG1_13_reg                                             0xB800A334
#define VE_DMAREG1_14_reg                                             0xB800A338
#define VE_DMAREG1_15_reg                                             0xB800A33C
#define VE_DMAREG1_0_inst_addr                                        "((0<<4)|0)"
#define VE_DMAREG1_0_inst                                             ((0<<4)|0)
#define VE_DMAREG1_1_inst_addr                                        "((0<<4)|1)"
#define VE_DMAREG1_1_inst                                             ((0<<4)|1)
#define VE_DMAREG1_2_inst_addr                                        "((0<<4)|2)"
#define VE_DMAREG1_2_inst                                             ((0<<4)|2)
#define VE_DMAREG1_3_inst_addr                                        "((0<<4)|3)"
#define VE_DMAREG1_3_inst                                             ((0<<4)|3)
#define VE_DMAREG1_4_inst_addr                                        "((0<<4)|4)"
#define VE_DMAREG1_4_inst                                             ((0<<4)|4)
#define VE_DMAREG1_5_inst_addr                                        "((0<<4)|5)"
#define VE_DMAREG1_5_inst                                             ((0<<4)|5)
#define VE_DMAREG1_6_inst_addr                                        "((0<<4)|6)"
#define VE_DMAREG1_6_inst                                             ((0<<4)|6)
#define VE_DMAREG1_7_inst_addr                                        "((0<<4)|7)"
#define VE_DMAREG1_7_inst                                             ((0<<4)|7)
#define VE_DMAREG1_8_inst_addr                                        "((0<<4)|8)"
#define VE_DMAREG1_8_inst                                             ((0<<4)|8)
#define VE_DMAREG1_9_inst_addr                                        "((0<<4)|9)"
#define VE_DMAREG1_9_inst                                             ((0<<4)|9)
#define VE_DMAREG1_10_inst_addr                                       "((0<<4)|10)"
#define VE_DMAREG1_10_inst                                            ((0<<4)|10)
#define VE_DMAREG1_11_inst_addr                                       "((0<<4)|11)"
#define VE_DMAREG1_11_inst                                            ((0<<4)|11)
#define VE_DMAREG1_12_inst_addr                                       "((0<<4)|12)"
#define VE_DMAREG1_12_inst                                            ((0<<4)|12)
#define VE_DMAREG1_13_inst_addr                                       "((0<<4)|13)"
#define VE_DMAREG1_13_inst                                            ((0<<4)|13)
#define VE_DMAREG1_14_inst_addr                                       "((0<<4)|14)"
#define VE_DMAREG1_14_inst                                            ((0<<4)|14)
#define VE_DMAREG1_15_inst_addr                                       "((0<<4)|15)"
#define VE_DMAREG1_15_inst                                            ((0<<4)|15)
#define VE_DMAREG1_x_shift                                            (14)
#define VE_DMAREG1_y_shift                                            (0)
#define VE_DMAREG1_x_mask                                             (0x07FFC000)
#define VE_DMAREG1_y_mask                                             (0x00003FFF)
#define VE_DMAREG1_x(data)                                            (0x07FFC000&((data)<<14))
#define VE_DMAREG1_y(data)                                            (0x00003FFF&(data))
#define VE_DMAREG1_get_x(data)                                        ((0x07FFC000&(data))>>14)
#define VE_DMAREG1_get_y(data)                                        (0x00003FFF&(data))

#define VE_DMAREG2_0                                                  0x1800A340
#define VE_DMAREG2_1                                                  0x1800A344
#define VE_DMAREG2_2                                                  0x1800A348
#define VE_DMAREG2_3                                                  0x1800A34C
#define VE_DMAREG2_4                                                  0x1800A350
#define VE_DMAREG2_5                                                  0x1800A354
#define VE_DMAREG2_6                                                  0x1800A358
#define VE_DMAREG2_7                                                  0x1800A35C
#define VE_DMAREG2_8                                                  0x1800A360
#define VE_DMAREG2_9                                                  0x1800A364
#define VE_DMAREG2_10                                                 0x1800A368
#define VE_DMAREG2_11                                                 0x1800A36C
#define VE_DMAREG2_12                                                 0x1800A370
#define VE_DMAREG2_13                                                 0x1800A374
#define VE_DMAREG2_14                                                 0x1800A378
#define VE_DMAREG2_15                                                 0x1800A37C
#define VE_DMAREG2_0_reg_addr                                         "0xB800A340"
#define VE_DMAREG2_1_reg_addr                                         "0xB800A344"
#define VE_DMAREG2_2_reg_addr                                         "0xB800A348"
#define VE_DMAREG2_3_reg_addr                                         "0xB800A34C"
#define VE_DMAREG2_4_reg_addr                                         "0xB800A350"
#define VE_DMAREG2_5_reg_addr                                         "0xB800A354"
#define VE_DMAREG2_6_reg_addr                                         "0xB800A358"
#define VE_DMAREG2_7_reg_addr                                         "0xB800A35C"
#define VE_DMAREG2_8_reg_addr                                         "0xB800A360"
#define VE_DMAREG2_9_reg_addr                                         "0xB800A364"
#define VE_DMAREG2_10_reg_addr                                        "0xB800A368"
#define VE_DMAREG2_11_reg_addr                                        "0xB800A36C"
#define VE_DMAREG2_12_reg_addr                                        "0xB800A370"
#define VE_DMAREG2_13_reg_addr                                        "0xB800A374"
#define VE_DMAREG2_14_reg_addr                                        "0xB800A378"
#define VE_DMAREG2_15_reg_addr                                        "0xB800A37C"
#define VE_DMAREG2_0_reg                                              0xB800A340
#define VE_DMAREG2_1_reg                                              0xB800A344
#define VE_DMAREG2_2_reg                                              0xB800A348
#define VE_DMAREG2_3_reg                                              0xB800A34C
#define VE_DMAREG2_4_reg                                              0xB800A350
#define VE_DMAREG2_5_reg                                              0xB800A354
#define VE_DMAREG2_6_reg                                              0xB800A358
#define VE_DMAREG2_7_reg                                              0xB800A35C
#define VE_DMAREG2_8_reg                                              0xB800A360
#define VE_DMAREG2_9_reg                                              0xB800A364
#define VE_DMAREG2_10_reg                                             0xB800A368
#define VE_DMAREG2_11_reg                                             0xB800A36C
#define VE_DMAREG2_12_reg                                             0xB800A370
#define VE_DMAREG2_13_reg                                             0xB800A374
#define VE_DMAREG2_14_reg                                             0xB800A378
#define VE_DMAREG2_15_reg                                             0xB800A37C
#define VE_DMAREG2_0_inst_addr                                        "((1<<4)|0)"
#define VE_DMAREG2_0_inst                                             ((1<<4)|0)
#define VE_DMAREG2_1_inst_addr                                        "((1<<4)|1)"
#define VE_DMAREG2_1_inst                                             ((1<<4)|1)
#define VE_DMAREG2_2_inst_addr                                        "((1<<4)|2)"
#define VE_DMAREG2_2_inst                                             ((1<<4)|2)
#define VE_DMAREG2_3_inst_addr                                        "((1<<4)|3)"
#define VE_DMAREG2_3_inst                                             ((1<<4)|3)
#define VE_DMAREG2_4_inst_addr                                        "((1<<4)|4)"
#define VE_DMAREG2_4_inst                                             ((1<<4)|4)
#define VE_DMAREG2_5_inst_addr                                        "((1<<4)|5)"
#define VE_DMAREG2_5_inst                                             ((1<<4)|5)
#define VE_DMAREG2_6_inst_addr                                        "((1<<4)|6)"
#define VE_DMAREG2_6_inst                                             ((1<<4)|6)
#define VE_DMAREG2_7_inst_addr                                        "((1<<4)|7)"
#define VE_DMAREG2_7_inst                                             ((1<<4)|7)
#define VE_DMAREG2_8_inst_addr                                        "((1<<4)|8)"
#define VE_DMAREG2_8_inst                                             ((1<<4)|8)
#define VE_DMAREG2_9_inst_addr                                        "((1<<4)|9)"
#define VE_DMAREG2_9_inst                                             ((1<<4)|9)
#define VE_DMAREG2_10_inst_addr                                       "((1<<4)|10)"
#define VE_DMAREG2_10_inst                                            ((1<<4)|10)
#define VE_DMAREG2_11_inst_addr                                       "((1<<4)|11)"
#define VE_DMAREG2_11_inst                                            ((1<<4)|11)
#define VE_DMAREG2_12_inst_addr                                       "((1<<4)|12)"
#define VE_DMAREG2_12_inst                                            ((1<<4)|12)
#define VE_DMAREG2_13_inst_addr                                       "((1<<4)|13)"
#define VE_DMAREG2_13_inst                                            ((1<<4)|13)
#define VE_DMAREG2_14_inst_addr                                       "((1<<4)|14)"
#define VE_DMAREG2_14_inst                                            ((1<<4)|14)
#define VE_DMAREG2_15_inst_addr                                       "((1<<4)|15)"
#define VE_DMAREG2_15_inst                                            ((1<<4)|15)
#define VE_DMAREG2_field_frame_shift                                  (26)
#define VE_DMAREG2_decimated_shift                                    (24)
#define VE_DMAREG2_bot_addr_idx_shift                                 (16)
#define VE_DMAREG2_top_addr_idx_shift                                 (8)
#define VE_DMAREG2_post_inc_sel_shift                                 (7)
#define VE_DMAREG2_post_inc_shift                                     (0)
#define VE_DMAREG2_field_frame_mask                                   (0x04000000)
#define VE_DMAREG2_decimated_mask                                     (0x03000000)
#define VE_DMAREG2_bot_addr_idx_mask                                  (0x003F0000)
#define VE_DMAREG2_top_addr_idx_mask                                  (0x00003F00)
#define VE_DMAREG2_post_inc_sel_mask                                  (0x00000080)
#define VE_DMAREG2_post_inc_mask                                      (0x0000003F)
#define VE_DMAREG2_field_frame(data)                                  (0x04000000&((data)<<26))
#define VE_DMAREG2_decimated(data)                                    (0x03000000&((data)<<24))
#define VE_DMAREG2_bot_addr_idx(data)                                 (0x003F0000&((data)<<16))
#define VE_DMAREG2_top_addr_idx(data)                                 (0x00003F00&((data)<<8))
#define VE_DMAREG2_post_inc_sel(data)                                 (0x00000080&((data)<<7))
#define VE_DMAREG2_post_inc(data)                                     (0x0000003F&(data))
#define VE_DMAREG2_get_field_frame(data)                              ((0x04000000&(data))>>26)
#define VE_DMAREG2_get_decimated(data)                                ((0x03000000&(data))>>24)
#define VE_DMAREG2_get_bot_addr_idx(data)                             ((0x003F0000&(data))>>16)
#define VE_DMAREG2_get_top_addr_idx(data)                             ((0x00003F00&(data))>>8)
#define VE_DMAREG2_get_post_inc_sel(data)                             ((0x00000080&(data))>>7)
#define VE_DMAREG2_get_post_inc(data)                                 (0x0000003F&(data))

#define VE_DMAREG3_0                                                  0x1800A380
#define VE_DMAREG3_1                                                  0x1800A384
#define VE_DMAREG3_2                                                  0x1800A388
#define VE_DMAREG3_3                                                  0x1800A38C
#define VE_DMAREG3_4                                                  0x1800A390
#define VE_DMAREG3_5                                                  0x1800A394
#define VE_DMAREG3_6                                                  0x1800A398
#define VE_DMAREG3_7                                                  0x1800A39C
#define VE_DMAREG3_8                                                  0x1800A3A0
#define VE_DMAREG3_9                                                  0x1800A3A4
#define VE_DMAREG3_10                                                 0x1800A3A8
#define VE_DMAREG3_11                                                 0x1800A3AC
#define VE_DMAREG3_12                                                 0x1800A3B0
#define VE_DMAREG3_13                                                 0x1800A3B4
#define VE_DMAREG3_14                                                 0x1800A3B8
#define VE_DMAREG3_15                                                 0x1800A3BC
#define VE_DMAREG3_0_reg_addr                                         "0xB800A380"
#define VE_DMAREG3_1_reg_addr                                         "0xB800A384"
#define VE_DMAREG3_2_reg_addr                                         "0xB800A388"
#define VE_DMAREG3_3_reg_addr                                         "0xB800A38C"
#define VE_DMAREG3_4_reg_addr                                         "0xB800A390"
#define VE_DMAREG3_5_reg_addr                                         "0xB800A394"
#define VE_DMAREG3_6_reg_addr                                         "0xB800A398"
#define VE_DMAREG3_7_reg_addr                                         "0xB800A39C"
#define VE_DMAREG3_8_reg_addr                                         "0xB800A3A0"
#define VE_DMAREG3_9_reg_addr                                         "0xB800A3A4"
#define VE_DMAREG3_10_reg_addr                                        "0xB800A3A8"
#define VE_DMAREG3_11_reg_addr                                        "0xB800A3AC"
#define VE_DMAREG3_12_reg_addr                                        "0xB800A3B0"
#define VE_DMAREG3_13_reg_addr                                        "0xB800A3B4"
#define VE_DMAREG3_14_reg_addr                                        "0xB800A3B8"
#define VE_DMAREG3_15_reg_addr                                        "0xB800A3BC"
#define VE_DMAREG3_0_reg                                              0xB800A380
#define VE_DMAREG3_1_reg                                              0xB800A384
#define VE_DMAREG3_2_reg                                              0xB800A388
#define VE_DMAREG3_3_reg                                              0xB800A38C
#define VE_DMAREG3_4_reg                                              0xB800A390
#define VE_DMAREG3_5_reg                                              0xB800A394
#define VE_DMAREG3_6_reg                                              0xB800A398
#define VE_DMAREG3_7_reg                                              0xB800A39C
#define VE_DMAREG3_8_reg                                              0xB800A3A0
#define VE_DMAREG3_9_reg                                              0xB800A3A4
#define VE_DMAREG3_10_reg                                             0xB800A3A8
#define VE_DMAREG3_11_reg                                             0xB800A3AC
#define VE_DMAREG3_12_reg                                             0xB800A3B0
#define VE_DMAREG3_13_reg                                             0xB800A3B4
#define VE_DMAREG3_14_reg                                             0xB800A3B8
#define VE_DMAREG3_15_reg                                             0xB800A3BC
#define VE_DMAREG3_0_inst_addr                                        "((2<<4)|0)"
#define VE_DMAREG3_0_inst                                             ((2<<4)|0)
#define VE_DMAREG3_1_inst_addr                                        "((2<<4)|1)"
#define VE_DMAREG3_1_inst                                             ((2<<4)|1)
#define VE_DMAREG3_2_inst_addr                                        "((2<<4)|2)"
#define VE_DMAREG3_2_inst                                             ((2<<4)|2)
#define VE_DMAREG3_3_inst_addr                                        "((2<<4)|3)"
#define VE_DMAREG3_3_inst                                             ((2<<4)|3)
#define VE_DMAREG3_4_inst_addr                                        "((2<<4)|4)"
#define VE_DMAREG3_4_inst                                             ((2<<4)|4)
#define VE_DMAREG3_5_inst_addr                                        "((2<<4)|5)"
#define VE_DMAREG3_5_inst                                             ((2<<4)|5)
#define VE_DMAREG3_6_inst_addr                                        "((2<<4)|6)"
#define VE_DMAREG3_6_inst                                             ((2<<4)|6)
#define VE_DMAREG3_7_inst_addr                                        "((2<<4)|7)"
#define VE_DMAREG3_7_inst                                             ((2<<4)|7)
#define VE_DMAREG3_8_inst_addr                                        "((2<<4)|8)"
#define VE_DMAREG3_8_inst                                             ((2<<4)|8)
#define VE_DMAREG3_9_inst_addr                                        "((2<<4)|9)"
#define VE_DMAREG3_9_inst                                             ((2<<4)|9)
#define VE_DMAREG3_10_inst_addr                                       "((2<<4)|10)"
#define VE_DMAREG3_10_inst                                            ((2<<4)|10)
#define VE_DMAREG3_11_inst_addr                                       "((2<<4)|11)"
#define VE_DMAREG3_11_inst                                            ((2<<4)|11)
#define VE_DMAREG3_12_inst_addr                                       "((2<<4)|12)"
#define VE_DMAREG3_12_inst                                            ((2<<4)|12)
#define VE_DMAREG3_13_inst_addr                                       "((2<<4)|13)"
#define VE_DMAREG3_13_inst                                            ((2<<4)|13)
#define VE_DMAREG3_14_inst_addr                                       "((2<<4)|14)"
#define VE_DMAREG3_14_inst                                            ((2<<4)|14)
#define VE_DMAREG3_15_inst_addr                                       "((2<<4)|15)"
#define VE_DMAREG3_15_inst                                            ((2<<4)|15)
#define VE_DMAREG3_line_off_shift                                     (28)
#define VE_DMAREG3_vm_pitch_shift                                     (21)
#define VE_DMAREG3_vm_addr_shift                                      (12)
#define VE_DMAREG3_h_shift                                            (6)
#define VE_DMAREG3_w_shift                                            (0)
#define VE_DMAREG3_line_off_mask                                      (0x10000000)
#define VE_DMAREG3_vm_pitch_mask                                      (0x0FE00000)
#define VE_DMAREG3_vm_addr_mask                                       (0x001FF000)
#define VE_DMAREG3_h_mask                                             (0x00000FC0)
#define VE_DMAREG3_w_mask                                             (0x0000003F)
#define VE_DMAREG3_line_off(data)                                     (0x10000000&((data)<<28))
#define VE_DMAREG3_vm_pitch(data)                                     (0x0FE00000&((data)<<21))
#define VE_DMAREG3_vm_addr(data)                                      (0x001FF000&((data)<<12))
#define VE_DMAREG3_h(data)                                            (0x00000FC0&((data)<<6))
#define VE_DMAREG3_w(data)                                            (0x0000003F&(data))
#define VE_DMAREG3_get_line_off(data)                                 ((0x10000000&(data))>>28)
#define VE_DMAREG3_get_vm_pitch(data)                                 ((0x0FE00000&(data))>>21)
#define VE_DMAREG3_get_vm_addr(data)                                  ((0x001FF000&(data))>>12)
#define VE_DMAREG3_get_h(data)                                        ((0x00000FC0&(data))>>6)
#define VE_DMAREG3_get_w(data)                                        (0x0000003F&(data))

#define VE_VMCNTL                                                     0x1800A3C0
#define VE_VMCNTL_reg_addr                                            "0xB800A3C0"
#define VE_VMCNTL_reg                                                 0xB800A3C0
#define VE_VMCNTL_inst_addr                                           "(3<<4)"
#define VE_VMCNTL_inst                                                (3<<4)
#define VE_VMCNTL_write_enable3_shift                                 (26)
#define VE_VMCNTL_q_sample_shift                                      (25)
#define VE_VMCNTL_write_enable2_shift                                 (24)
#define VE_VMCNTL_rnd_cntl_shift                                      (23)
#define VE_VMCNTL_write_enable1_shift                                 (22)
#define VE_VMCNTL_h_shift                                             (11)
#define VE_VMCNTL_w_shift                                             (0)
#define VE_VMCNTL_write_enable3_mask                                  (0x04000000)
#define VE_VMCNTL_q_sample_mask                                       (0x02000000)
#define VE_VMCNTL_write_enable2_mask                                  (0x01000000)
#define VE_VMCNTL_rnd_cntl_mask                                       (0x00800000)
#define VE_VMCNTL_write_enable1_mask                                  (0x00400000)
#define VE_VMCNTL_h_mask                                              (0x003FF800)
#define VE_VMCNTL_w_mask                                              (0x000007FF)
#define VE_VMCNTL_write_enable3(data)                                 (0x04000000&((data)<<26))
#define VE_VMCNTL_q_sample(data)                                      (0x02000000&((data)<<25))
#define VE_VMCNTL_write_enable2(data)                                 (0x01000000&((data)<<24))
#define VE_VMCNTL_rnd_cntl(data)                                      (0x00800000&((data)<<23))
#define VE_VMCNTL_write_enable1(data)                                 (0x00400000&((data)<<22))
#define VE_VMCNTL_h(data)                                             (0x003FF800&((data)<<11))
#define VE_VMCNTL_w(data)                                             (0x000007FF&(data))
#define VE_VMCNTL_get_write_enable3(data)                             ((0x04000000&(data))>>26)
#define VE_VMCNTL_get_q_sample(data)                                  ((0x02000000&(data))>>25)
#define VE_VMCNTL_get_write_enable2(data)                             ((0x01000000&(data))>>24)
#define VE_VMCNTL_get_rnd_cntl(data)                                  ((0x00800000&(data))>>23)
#define VE_VMCNTL_get_write_enable1(data)                             ((0x00400000&(data))>>22)
#define VE_VMCNTL_get_h(data)                                         ((0x003FF800&(data))>>11)
#define VE_VMCNTL_get_w(data)                                         (0x000007FF&(data))
#endif
