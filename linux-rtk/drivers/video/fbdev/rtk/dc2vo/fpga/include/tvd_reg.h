// This file is generated using the spec version 0.3.3, firmware template version 1.39and DVR_Parser_0.4
#ifndef _TVD_REG_H_INCLUDED_
#define _TVD_REG_H_INCLUDED_

//#define  _TVD_USE_STRUCT
#ifdef _TVD_USE_STRUCT

typedef struct
{
    unsigned int    reserved_0:15;
    unsigned int    write_enable7:1;
    unsigned int    hv_delay:1;
    unsigned int    write_enable6:1;
    unsigned int    hpixel:2;
    unsigned int    write_enable5:1;
    unsigned int    vline_625:1;
    unsigned int    write_enable4:1;
    unsigned int    colour_mode:3;
    unsigned int    write_enable3:1;
    unsigned int    yc_src:1;
    unsigned int    write_enable2:1;
    unsigned int    cv_inv:1;
    unsigned int    write_enable1:1;
    unsigned int    cv_src:1;
}tvd_VDO_CTRL1;

typedef struct
{
    unsigned int    reserved_0:11;
    unsigned int    write_enable9:1;
    unsigned int    luma_notch_bw:2;
    unsigned int    write_enable8:1;
    unsigned int    chroma_bw_lo:2;
    unsigned int    write_enable7:1;
    unsigned int    chroma_burst5or10:1;
    unsigned int    write_enable6:1;
    unsigned int    ped:1;
    unsigned int    write_enable5:1;
    unsigned int    hagc_field:1;
    unsigned int    write_enable4:1;
    unsigned int    mv_hagc:1;
    unsigned int    write_enable3:1;
    unsigned int    dc_clamp_mode:2;
    unsigned int    write_enable2:1;
    unsigned int    cagc_en:1;
    unsigned int    write_enable1:1;
    unsigned int    hagc_en:1;
}tvd_VDO_CTRL2;

typedef struct
{
    unsigned int    reserved_0:26;
    unsigned int    write_enable2:1;
    unsigned int    colour_trap:1;
    unsigned int    write_enable1:1;
    unsigned int    adaptive_mode:3;
}tvd_YC_SEP_CTRL;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    write_enable6:1;
    unsigned int    hagc:8;
    unsigned int    write_enable5:1;
    unsigned int    noise_thresh:8;
    unsigned int    write_enable4:1;
    unsigned int    adc_updn_swap:1;
    unsigned int    write_enable3:1;
    unsigned int    adc_input_swap:1;
    unsigned int    write_enable2:1;
    unsigned int    adc_cbcr_pump_swap:1;
    unsigned int    write_enable1:1;
    unsigned int    adc_gate_thresh:5;
}tvd_HOR_ACQ;

typedef struct
{
    unsigned int    reserved_0:22;
    unsigned int    write_enable3:1;
    unsigned int    cbcr_swap:1;
    unsigned int    write_enable2:1;
    unsigned int    blue_mode:2;
    unsigned int    write_enable1:1;
    unsigned int    yc_delay:4;
}tvd_OUT_CTRL;

typedef struct
{
    unsigned int    reserved_0:14;
    unsigned int    write_enable2:1;
    unsigned int    contrast:8;
    unsigned int    write_enable1:1;
    unsigned int    brightness:8;
}tvd_LUMA_ADJUST;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    write_enable3:1;
    unsigned int    saturation:8;
    unsigned int    write_enable2:1;
    unsigned int    hue:8;
    unsigned int    write_enable1:1;
    unsigned int    cagc:8;
}tvd_CHROMA_ADJUST;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    write_enable7:1;
    unsigned int    user_ckill_mode:2;
    unsigned int    write_enable6:1;
    unsigned int    vbi_ckill:1;
    unsigned int    write_enable5:1;
    unsigned int    hlock_ckill:1;
    unsigned int    write_enable4:1;
    unsigned int    chroma_kill:4;
    unsigned int    write_enable3:1;
    unsigned int    secam_test_mode:1;
    unsigned int    write_enable2:1;
    unsigned int    fixed_burstgate:1;
    unsigned int    write_enable1:1;
    unsigned int    cautopos:5;
}tvd_CHROMA_KILL_AUTOPOS;

typedef struct
{
    unsigned int    reserved_0:11;
    unsigned int    write_enable6:1;
    unsigned int    agc_peak_nominal:7;
    unsigned int    write_enable5:1;
    unsigned int    agc_gate_vsync_coarse:1;
    unsigned int    write_enable4:1;
    unsigned int    agc_gate_vsync_stip:1;
    unsigned int    write_enable3:1;
    unsigned int    agc_gate_kill_mode:2;
    unsigned int    write_enable2:1;
    unsigned int    agc_peak_en:1;
    unsigned int    write_enable1:1;
    unsigned int    agc_peak_cntl:3;
}tvd_AGC_PEAKGATE;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    write_enable3:1;
    unsigned int    agc_gate_start:11;
    unsigned int    write_enable2:1;
    unsigned int    agc_gate_width:7;
    unsigned int    write_enable1:1;
    unsigned int    agc_bp_delay:8;
}tvd_AGC_GATE;

typedef struct
{
    unsigned int    reserved_0:9;
    unsigned int    write_enable7:1;
    unsigned int    locked_count_noisy_max:4;
    unsigned int    write_enable6:1;
    unsigned int    locked_count_clean_max:4;
    unsigned int    write_enable5:1;
    unsigned int    hlock_vsync_mode:2;
    unsigned int    write_enable4:1;
    unsigned int    hstate_fixed:1;
    unsigned int    write_enable3:1;
    unsigned int    disable_hfine:1;
    unsigned int    write_enable2:1;
    unsigned int    hstate_unlocked:1;
    unsigned int    write_enable1:1;
    unsigned int    hstate_max:3;
}tvd_HPLL_CTRL;

typedef struct
{
    unsigned int    reserved_0:1;
    unsigned int    cdto_fixed:1;
    unsigned int    cdto_inc:30;
}tvd_CHROMA_DTO;

typedef struct
{
    unsigned int    reserved_0:1;
    unsigned int    hdto_fixed:1;
    unsigned int    hdto_inc:30;
}tvd_HSYNC_DTO;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    hsync_rising:8;
    unsigned int    hsync_phase_offset:8;
}tvd_HSYNC_OCCUR;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    hsync_gate_start:8;
    unsigned int    hsync_gate_end:8;
}tvd_HSYNC_GATE_TIME;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    hsync_tip_start:8;
    unsigned int    hsync_tip_end:8;
}tvd_HSYNC_TIP_TIME;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    hsync_rising_start:8;
    unsigned int    hsync_rising_end:8;
}tvd_HSYNC_RISING_TIME;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    backporch_start:8;
    unsigned int    backporch_end:8;
}tvd_BACKPROCH_TIME;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    hblank_start:8;
    unsigned int    hblank_end:8;
}tvd_HBLANK_TIME;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    burst_gate_start:8;
    unsigned int    burst_gate_end:8;
}tvd_BURST_GATE_TIME;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    hactive_start:8;
    unsigned int    hactive_width:8;
}tvd_HACTIVE_TIME;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    vactive_start:8;
    unsigned int    vactive_height:8;
}tvd_VACTIVE_TIME;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    vsync_h_min:7;
    unsigned int    vsync_h_max:7;
}tvd_VSYNC_H_LOCKOUT;

typedef struct
{
    unsigned int    reserved_0:17;
    unsigned int    vsync_clamp_mode:2;
    unsigned int    vsync_agc_min:7;
    unsigned int    vsync_agc_max:6;
}tvd_VSYNC_AGC_LOCKOUT;

typedef struct
{
    unsigned int    reserved_0:17;
    unsigned int    vlock_wide_range:1;
    unsigned int    vsync_vbi_min:7;
    unsigned int    vsync_vbi_max:7;
}tvd_VSYNC_VBI_LOCKOUT;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable8:1;
    unsigned int    vsync_cntl:2;
    unsigned int    write_enable7:1;
    unsigned int    vsync_threshold:6;
    unsigned int    write_enable6:1;
    unsigned int    field_polarity:1;
    unsigned int    write_enable5:1;
    unsigned int    flip_field:1;
    unsigned int    write_enable4:1;
    unsigned int    veven_delayed:1;
    unsigned int    write_enable3:1;
    unsigned int    vodd_delayed:1;
    unsigned int    write_enable2:1;
    unsigned int    field_detect_mode:2;
    unsigned int    write_enable1:1;
    unsigned int    vloop_tc:2;
}tvd_VSYNC_CTRL;

typedef struct
{
    unsigned int    reserved_0:14;
    unsigned int    mv_colourstripes:3;
    unsigned int    mv_vbi_detected:1;
    unsigned int    chomalock:1;
    unsigned int    vlock:1;
    unsigned int    hlock:1;
    unsigned int    no_signal:1;
    unsigned int    palm_flag:1;
    unsigned int    proscan_detected:1;
    unsigned int    vcr_rew:1;
    unsigned int    vcr_ff:1;
    unsigned int    vcr_trick:1;
    unsigned int    vcr:1;
    unsigned int    noisy:1;
    unsigned int    625lines_detected:1;
    unsigned int    secam_detected:1;
    unsigned int    pal_detected:1;
}tvd_STATUS1;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    status_hdto_inc:30;
}tvd_HDTO_STATUS;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    status_cdto_inc:30;
}tvd_CDTO_STATUS;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    status_cmag:8;
    unsigned int    status_cgain:14;
}tvd_CHROMA_STATUS;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    status_agc_dgain:8;
    unsigned int    status_cordiq_freq:8;
    unsigned int    status_noise:8;
}tvd_STATUS2;

typedef struct
{
    unsigned int    reserved_0:23;
    unsigned int    write_enable3:1;
    unsigned int    peak_range:2;
    unsigned int    write_enable2:1;
    unsigned int    peak_gain:3;
    unsigned int    write_enable1:1;
    unsigned int    peak_en:1;
}tvd_PEAKING;

typedef struct
{
    unsigned int    reserved_0:23;
    unsigned int    write_enable4:1;
    unsigned int    pal_perr:1;
    unsigned int    write_enable3:1;
    unsigned int    pal_perr_auto_en:1;
    unsigned int    write_enable2:1;
    unsigned int    comb_wide_band:1;
    unsigned int    write_enable1:1;
    unsigned int    palsw_level:2;
}tvd_COMB_CONFIG;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    write_enable3:1;
    unsigned int    lose_chromalock_count:4;
    unsigned int    write_enable2:1;
    unsigned int    lose_chromalock_level:3;
    unsigned int    write_enable1:1;
    unsigned int    lose_chromalock_ckill:1;
}tvd_CHROMA_LOCK;

typedef struct
{
    unsigned int    noise_ntsc_c:8;
    unsigned int    noise_pal_c:8;
    unsigned int    noise_phase_c:8;
    unsigned int    noise_phase_y:8;
}tvd_COMB_THD;

typedef struct
{
    unsigned int    reserved_0:28;
    unsigned int    cstate:3;
    unsigned int    fixed_cstat:1;
}tvd_CHROMA_LPFILTER;

typedef struct
{
    unsigned int    reserved_0:31;
    unsigned int    hresampler_2up:1;
}tvd_HRESAMPLE;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    write_enable5:1;
    unsigned int    cpump_adjust_delay:6;
    unsigned int    write_enable4:1;
    unsigned int    cpump_adjust_polarity:1;
    unsigned int    write_enable3:1;
    unsigned int    cpump_delay_en:1;
    unsigned int    write_enable2:1;
    unsigned int    cpump_adjust:8;
    unsigned int    write_enable1:1;
    unsigned int    cpump_delay:8;
}tvd_CHG_PUMP_DLY;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    write_enable11:1;
    unsigned int    debug_mode:1;
    unsigned int    write_enable10:1;
    unsigned int    debug_enable:1;
    unsigned int    write_enable9:1;
    unsigned int    memory_size:2;
    unsigned int    write_enable8:1;
    unsigned int    ntscpal_select:1;
    unsigned int    write_enable7:1;
    unsigned int    yc_separation_control:3;
    unsigned int    write_enable6:1;
    unsigned int    chroma_vlpf_en:1;
    unsigned int    write_enable5:1;
    unsigned int    bpf_bw_sel:3;
    unsigned int    write_enable4:1;
    unsigned int    vcr3d2d:1;
    unsigned int    write_enable3:1;
    unsigned int    noisy3d2d:1;
    unsigned int    write_enable2:1;
    unsigned int    field_toggle_en:1;
    unsigned int    write_enable1:1;
    unsigned int    debug_tree_monitor:4;
}tvd_3DYC_SEP_CTRL;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    md_y_lo_diff_thresh1:4;
    unsigned int    check_mdt_en:1;
    unsigned int    md_y_lo_diff_thresh2:6;
    unsigned int    md_mesh_det_thresh1:4;
    unsigned int    md_mesh_c_large_thresh:4;
    unsigned int    md_frame_close_chk_enable:1;
    unsigned int    md_mesh_det_thresh2:4;
    unsigned int    md_mesh_det_cnt_thresh:3;
}tvd_3DTHD1;

typedef struct
{
    unsigned int    reserved_0:13;
    unsigned int    md_chk_mesh_thresh:2;
    unsigned int    md_y_lo_line_diff_thresh:4;
    unsigned int    md_chk_three_line_c_thresh1:3;
    unsigned int    md_c_detect_thresh:4;
    unsigned int    md_orig_diff_thresh:6;
}tvd_3DTHD2;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    md_line_close_thresh:4;
    unsigned int    md_c_near_2d_3d_thresh:4;
    unsigned int    md_chk_three_line_c_thresh2:3;
    unsigned int    md_line_compare_thresh1:5;
    unsigned int    md_chk_angle_c_thresh:3;
    unsigned int    md_line_compare_thresh2:5;
}tvd_3DTHD3;

typedef struct
{
    unsigned int    reserved_0:9;
    unsigned int    md_c_3d_large_thresh1:4;
    unsigned int    md_c_3d_large_thresh2:4;
    unsigned int    md_cross_c_suppress_enable:1;
    unsigned int    md_c_edge_thresh1:7;
    unsigned int    md_c_edge_thresh2:7;
}tvd_3DTHD4;

typedef struct
{
    unsigned int    reserved_0:13;
    unsigned int    write_enable6:1;
    unsigned int    cc_hddet_st:8;
    unsigned int    write_enable5:1;
    unsigned int    adap_slvl_en:1;
    unsigned int    write_enable4:1;
    unsigned int    vbi_st_err_ignored:1;
    unsigned int    write_enable3:1;
    unsigned int    vbi_en:1;
    unsigned int    write_enable2:1;
    unsigned int    cgms_bot_en:1;
    unsigned int    write_enable1:1;
    unsigned int    cgms_top_en:1;
}tvd_SLICER_CTRL;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    vps_vbil16o:4;
    unsigned int    vps_vbil16e:4;
}tvd_VPS_LINE_16;

typedef struct
{
    unsigned int    vbio05:4;
    unsigned int    vbie05:4;
    unsigned int    vbio06:4;
    unsigned int    vbie06:4;
    unsigned int    vbio07:4;
    unsigned int    vbie07:4;
    unsigned int    vbio08:4;
    unsigned int    vbie08:4;
}tvd_VBI_LINE0;

typedef struct
{
    unsigned int    vbio09:4;
    unsigned int    vbie09:4;
    unsigned int    vbio10:4;
    unsigned int    vbie10:4;
    unsigned int    vbio11:4;
    unsigned int    vbie11:4;
    unsigned int    vbio12:4;
    unsigned int    vbie12:4;
}tvd_VBI_LINE1;

typedef struct
{
    unsigned int    vbio13:4;
    unsigned int    vbie13:4;
    unsigned int    vbio14:4;
    unsigned int    vbie14:4;
    unsigned int    vbio15:4;
    unsigned int    vbie15:4;
    unsigned int    vbio16:4;
    unsigned int    vbie16:4;
}tvd_VBI_LINE2;

typedef struct
{
    unsigned int    vbio17:4;
    unsigned int    vbie17:4;
    unsigned int    vbio18:4;
    unsigned int    vbie18:4;
    unsigned int    vbio19:4;
    unsigned int    vbie19:4;
    unsigned int    vbio20:4;
    unsigned int    vbie20:4;
}tvd_VBI_LINE3;

typedef struct
{
    unsigned int    vbio21:4;
    unsigned int    vbie21:4;
    unsigned int    vbio22:4;
    unsigned int    vbie22:4;
    unsigned int    vbio23:4;
    unsigned int    vbie23:4;
    unsigned int    vbio_other:4;
    unsigned int    vbie_other:4;
}tvd_VBI_LINE4;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    cgms_line_even:8;
    unsigned int    cgms_line_odd:8;
}tvd_CGMS_LINE;

typedef struct
{
    unsigned int    reserved_0:15;
    unsigned int    data_hlvl:8;
    unsigned int    gain:3;
    unsigned int    igain:3;
    unsigned int    pgain:3;
}tvd_VBI_GAIN_LVL;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    cc_dto:16;
}tvd_CC_DTO;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    tt_dto:16;
}tvd_TT_DTO;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    wss_dto:16;
}tvd_WSS_DTO;

typedef struct
{
    unsigned int    cc_frame_start:8;
    unsigned int    tt_frame_start:8;
    unsigned int    tt_start_code:8;
    unsigned int    wss_frame_start:8;
}tvd_VBI_FRAME_START;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    cc_start:8;
    unsigned int    tt_start:8;
    unsigned int    wss_start:8;
}tvd_VBI_START;

typedef struct
{
    unsigned int    vbi_cal_dc_st:4;
    unsigned int    vbi_cal_dc_end:4;
    unsigned int    wss_cal_dc_st:4;
    unsigned int    wss_cal_dc_end:4;
    unsigned int    vps_cal_dc_st:4;
    unsigned int    vps_cal_dc_end:4;
    unsigned int    cgms_cal_dc_st:4;
    unsigned int    cgms_cal_dc_end:4;
}tvd_VBI_CAL_DC_DETECT;

typedef struct
{
    unsigned int    reserved_0:23;
    unsigned int    adap_cgms_dc_en:1;
    unsigned int    cgms_dc:8;
}tvd_CGMS_DC;

typedef struct
{
    unsigned int    reserved_0:29;
    unsigned int    cc_rdy:1;
    unsigned int    wss_rdy:1;
    unsigned int    cgms_rdy:1;
}tvd_VBI_RDY;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    cc_data:16;
}tvd_CC_DATA;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    wss_data:16;
}tvd_WSS_DATA;

typedef struct
{
    unsigned int    reserved_0:12;
    unsigned int    cgms_data:20;
}tvd_CGMS_DATA;

typedef struct
{
    unsigned int    reserved_0:6;
    unsigned int    apowl:1;
    unsigned int    bpowl:1;
    unsigned int    cpowl:1;
    unsigned int    dpowl:1;
    unsigned int    asgainl:3;
    unsigned int    bsgainl:3;
    unsigned int    csgainl:3;
    unsigned int    dsgainl:3;
    unsigned int    calibratel:4;
    unsigned int    scavl:3;
    unsigned int    svoutl:3;
}tvd_VIDEO_ADC_DIGITAL_CTRL0;

typedef struct
{
    unsigned int    ainswl:2;
    unsigned int    binswl:2;
    unsigned int    cinswl:2;
    unsigned int    dinswl:2;
    unsigned int    aclamp_spl:6;
    unsigned int    bclamp_spl:6;
    unsigned int    cclamp_spl:6;
    unsigned int    dclamp_spl:6;
}tvd_VIDEO_ADC_DIGITAL_CTRL1;

typedef struct
{
    unsigned int    asvicml:3;
    unsigned int    bsvicml:3;
    unsigned int    csvicml:3;
    unsigned int    dsvicml:3;
    unsigned int    sib_bufl:4;
    unsigned int    sib_mdacl:4;
    unsigned int    sib_sourcel:4;
    unsigned int    sib_topl:4;
    unsigned int    sib_vrtbufl:4;
}tvd_VIDEO_ADC_ANALOG_CTRL0;

typedef struct
{
    unsigned int    reserved_0:6;
    unsigned int    avrbl:3;
    unsigned int    bvrbl:3;
    unsigned int    cvrbl:3;
    unsigned int    dvrbl:3;
    unsigned int    svrbl:3;
    unsigned int    clamp_enl:4;
    unsigned int    sckinl:2;
    unsigned int    sckol:1;
    unsigned int    vicmpowl:4;
}tvd_VIDEO_ADC_ANALOG_CTRL1;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    afepowl:4;
    unsigned int    sadcinl:4;
    unsigned int    vrefpowl:5;
    unsigned int    avrtl:3;
    unsigned int    bvrtl:3;
    unsigned int    cvrtl:3;
    unsigned int    dvrtl:3;
    unsigned int    svrtl:3;
}tvd_VIDEO_ADC_ANALOG_CTRL2;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable9:1;
    unsigned int    fsw_en:1;
    unsigned int    write_enable8:1;
    unsigned int    sw_y_r:2;
    unsigned int    write_enable7:1;
    unsigned int    sw_pb_g:2;
    unsigned int    write_enable6:1;
    unsigned int    sw_pr_b:2;
    unsigned int    write_enable5:1;
    unsigned int    ad1_y_sw:1;
    unsigned int    write_enable4:1;
    unsigned int    scart_en:1;
    unsigned int    write_enable3:1;
    unsigned int    clamp_ad2:2;
    unsigned int    write_enable2:1;
    unsigned int    clamp_ad3:2;
    unsigned int    write_enable1:1;
    unsigned int    clamp_ad4:2;
}tvd_AD_SW_CTRL;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    hst:8;
    unsigned int    hwidth:8;
    unsigned int    vst:7;
    unsigned int    vwidth:7;
}tvd_SCART_ACTIVE;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    clamp_a_up_en:1;
    unsigned int    clamp_a_dn_en:1;
    unsigned int    clamp_b_up_en:1;
    unsigned int    clamp_b_dn_en:1;
    unsigned int    clamp_c_up_en:1;
    unsigned int    clamp_c_dn_en:1;
    unsigned int    clamp_d_up_en:1;
    unsigned int    clamp_d_dn_en:1;
}tvd_CLAMP_EN_CTRL;

typedef struct
{
    unsigned int    reserved_0:25;
    unsigned int    value:7;
}tvd_3B_ADC;

typedef struct
{
    unsigned int    reserved_0:20;
    unsigned int    muxanalogb:4;
    unsigned int    muxanaloga:4;
    unsigned int    muxdigital:4;
}tvd_DEBUG;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    serration_thd:8;
    unsigned int    lock_h_on_no_signal:1;
    unsigned int    disable_blue_screen_when_vcr:1;
    unsigned int    detect_vcr_when_h_unlock:1;
}tvd_VCR_OPTION;

typedef struct
{
    unsigned int    reserved_0:12;
    unsigned int    first_v:10;
    unsigned int    second_v:10;
}tvd_HV_MEASURE_1;

typedef struct
{
    unsigned int    reserved_0:11;
    unsigned int    count:8;
    unsigned int    hgt:13;
}tvd_HV_MEASURE_2;

typedef struct
{
    unsigned int    reserved_0:30;
    unsigned int    crc_en:1;
    unsigned int    ptgen_en:1;
}tvd_CRC_CTRL;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    checksum:16;
}tvd_CRC_CHECKSUM;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    mask:22;
}tvd_RAW_MASK;

typedef struct
{
    unsigned int    reserved_0:12;
    unsigned int    start:10;
    unsigned int    end:10;
}tvd_3D_VACTIVE1;

typedef struct
{
    unsigned int    reserved_0:12;
    unsigned int    start:10;
    unsigned int    end:10;
}tvd_3D_VACTIVE2;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    frame_adr0:27;
}tvd_FRAME_ADDR0;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    frame_adr1:27;
}tvd_FRAME_ADDR1;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    write_enable5:1;
    unsigned int    dmaen:1;
    unsigned int    write_enable4:1;
    unsigned int    ififo_thr:6;
    unsigned int    write_enable3:1;
    unsigned int    ofifo_thr:6;
    unsigned int    write_enable2:1;
    unsigned int    ceiladr:6;
    unsigned int    write_enable1:1;
    unsigned int    bstlen:3;
}tvd_DMA_CTRL;

typedef struct
{
    unsigned int    reserved_0:30;
    unsigned int    ififo_err:1;
    unsigned int    ofifo_err:1;
}tvd_DMA_ERR;

typedef struct
{
    unsigned int    reserved_0:12;
    unsigned int    hcnt:10;
    unsigned int    vcnt:10;
}tvd_IPCNT;

typedef struct
{
    unsigned int    reserved_0:31;
    unsigned int    iprstn:1;
}tvd_IP_RESET;

typedef struct
{
    unsigned int    reserved_0:28;
    unsigned int    edge_sel4:1;
    unsigned int    edge_sel3:1;
    unsigned int    edge_sel2:1;
    unsigned int    edge_sel1:1;
}tvd_ADC_SAMPLE;
#endif

#define TVD_VDO_CTRL1                                                 0x18019000
#define TVD_VDO_CTRL1_reg_addr                                        "0xB8019000"
#define TVD_VDO_CTRL1_reg                                             0xB8019000
#define TVD_VDO_CTRL1_inst_addr                                       "0x0000"
#define TVD_VDO_CTRL1_inst                                            0x0000
#define TVD_VDO_CTRL1_write_enable7_shift                             (16)
#define TVD_VDO_CTRL1_hv_delay_shift                                  (15)
#define TVD_VDO_CTRL1_write_enable6_shift                             (14)
#define TVD_VDO_CTRL1_hpixel_shift                                    (12)
#define TVD_VDO_CTRL1_write_enable5_shift                             (11)
#define TVD_VDO_CTRL1_vline_625_shift                                 (10)
#define TVD_VDO_CTRL1_write_enable4_shift                             (9)
#define TVD_VDO_CTRL1_colour_mode_shift                               (6)
#define TVD_VDO_CTRL1_write_enable3_shift                             (5)
#define TVD_VDO_CTRL1_yc_src_shift                                    (4)
#define TVD_VDO_CTRL1_write_enable2_shift                             (3)
#define TVD_VDO_CTRL1_cv_inv_shift                                    (2)
#define TVD_VDO_CTRL1_write_enable1_shift                             (1)
#define TVD_VDO_CTRL1_cv_src_shift                                    (0)
#define TVD_VDO_CTRL1_write_enable7_mask                              (0x00010000)
#define TVD_VDO_CTRL1_hv_delay_mask                                   (0x00008000)
#define TVD_VDO_CTRL1_write_enable6_mask                              (0x00004000)
#define TVD_VDO_CTRL1_hpixel_mask                                     (0x00003000)
#define TVD_VDO_CTRL1_write_enable5_mask                              (0x00000800)
#define TVD_VDO_CTRL1_vline_625_mask                                  (0x00000400)
#define TVD_VDO_CTRL1_write_enable4_mask                              (0x00000200)
#define TVD_VDO_CTRL1_colour_mode_mask                                (0x000001C0)
#define TVD_VDO_CTRL1_write_enable3_mask                              (0x00000020)
#define TVD_VDO_CTRL1_yc_src_mask                                     (0x00000010)
#define TVD_VDO_CTRL1_write_enable2_mask                              (0x00000008)
#define TVD_VDO_CTRL1_cv_inv_mask                                     (0x00000004)
#define TVD_VDO_CTRL1_write_enable1_mask                              (0x00000002)
#define TVD_VDO_CTRL1_cv_src_mask                                     (0x00000001)
#define TVD_VDO_CTRL1_write_enable7(data)                             (0x00010000&((data)<<16))
#define TVD_VDO_CTRL1_hv_delay(data)                                  (0x00008000&((data)<<15))
#define TVD_VDO_CTRL1_write_enable6(data)                             (0x00004000&((data)<<14))
#define TVD_VDO_CTRL1_hpixel(data)                                    (0x00003000&((data)<<12))
#define TVD_VDO_CTRL1_write_enable5(data)                             (0x00000800&((data)<<11))
#define TVD_VDO_CTRL1_vline_625(data)                                 (0x00000400&((data)<<10))
#define TVD_VDO_CTRL1_write_enable4(data)                             (0x00000200&((data)<<9))
#define TVD_VDO_CTRL1_colour_mode(data)                               (0x000001C0&((data)<<6))
#define TVD_VDO_CTRL1_write_enable3(data)                             (0x00000020&((data)<<5))
#define TVD_VDO_CTRL1_yc_src(data)                                    (0x00000010&((data)<<4))
#define TVD_VDO_CTRL1_write_enable2(data)                             (0x00000008&((data)<<3))
#define TVD_VDO_CTRL1_cv_inv(data)                                    (0x00000004&((data)<<2))
#define TVD_VDO_CTRL1_write_enable1(data)                             (0x00000002&((data)<<1))
#define TVD_VDO_CTRL1_cv_src(data)                                    (0x00000001&(data))
#define TVD_VDO_CTRL1_get_write_enable7(data)                         ((0x00010000&(data))>>16)
#define TVD_VDO_CTRL1_get_hv_delay(data)                              ((0x00008000&(data))>>15)
#define TVD_VDO_CTRL1_get_write_enable6(data)                         ((0x00004000&(data))>>14)
#define TVD_VDO_CTRL1_get_hpixel(data)                                ((0x00003000&(data))>>12)
#define TVD_VDO_CTRL1_get_write_enable5(data)                         ((0x00000800&(data))>>11)
#define TVD_VDO_CTRL1_get_vline_625(data)                             ((0x00000400&(data))>>10)
#define TVD_VDO_CTRL1_get_write_enable4(data)                         ((0x00000200&(data))>>9)
#define TVD_VDO_CTRL1_get_colour_mode(data)                           ((0x000001C0&(data))>>6)
#define TVD_VDO_CTRL1_get_write_enable3(data)                         ((0x00000020&(data))>>5)
#define TVD_VDO_CTRL1_get_yc_src(data)                                ((0x00000010&(data))>>4)
#define TVD_VDO_CTRL1_get_write_enable2(data)                         ((0x00000008&(data))>>3)
#define TVD_VDO_CTRL1_get_cv_inv(data)                                ((0x00000004&(data))>>2)
#define TVD_VDO_CTRL1_get_write_enable1(data)                         ((0x00000002&(data))>>1)
#define TVD_VDO_CTRL1_get_cv_src(data)                                (0x00000001&(data))

#define TVD_VDO_CTRL2                                                 0x18019004
#define TVD_VDO_CTRL2_reg_addr                                        "0xB8019004"
#define TVD_VDO_CTRL2_reg                                             0xB8019004
#define TVD_VDO_CTRL2_inst_addr                                       "0x0001"
#define TVD_VDO_CTRL2_inst                                            0x0001
#define TVD_VDO_CTRL2_write_enable9_shift                             (20)
#define TVD_VDO_CTRL2_luma_notch_bw_shift                             (18)
#define TVD_VDO_CTRL2_write_enable8_shift                             (17)
#define TVD_VDO_CTRL2_chroma_bw_lo_shift                              (15)
#define TVD_VDO_CTRL2_write_enable7_shift                             (14)
#define TVD_VDO_CTRL2_chroma_burst5or10_shift                         (13)
#define TVD_VDO_CTRL2_write_enable6_shift                             (12)
#define TVD_VDO_CTRL2_ped_shift                                       (11)
#define TVD_VDO_CTRL2_write_enable5_shift                             (10)
#define TVD_VDO_CTRL2_hagc_field_shift                                (9)
#define TVD_VDO_CTRL2_write_enable4_shift                             (8)
#define TVD_VDO_CTRL2_mv_hagc_shift                                   (7)
#define TVD_VDO_CTRL2_write_enable3_shift                             (6)
#define TVD_VDO_CTRL2_dc_clamp_mode_shift                             (4)
#define TVD_VDO_CTRL2_write_enable2_shift                             (3)
#define TVD_VDO_CTRL2_cagc_en_shift                                   (2)
#define TVD_VDO_CTRL2_write_enable1_shift                             (1)
#define TVD_VDO_CTRL2_hagc_en_shift                                   (0)
#define TVD_VDO_CTRL2_write_enable9_mask                              (0x00100000)
#define TVD_VDO_CTRL2_luma_notch_bw_mask                              (0x000C0000)
#define TVD_VDO_CTRL2_write_enable8_mask                              (0x00020000)
#define TVD_VDO_CTRL2_chroma_bw_lo_mask                               (0x00018000)
#define TVD_VDO_CTRL2_write_enable7_mask                              (0x00004000)
#define TVD_VDO_CTRL2_chroma_burst5or10_mask                          (0x00002000)
#define TVD_VDO_CTRL2_write_enable6_mask                              (0x00001000)
#define TVD_VDO_CTRL2_ped_mask                                        (0x00000800)
#define TVD_VDO_CTRL2_write_enable5_mask                              (0x00000400)
#define TVD_VDO_CTRL2_hagc_field_mask                                 (0x00000200)
#define TVD_VDO_CTRL2_write_enable4_mask                              (0x00000100)
#define TVD_VDO_CTRL2_mv_hagc_mask                                    (0x00000080)
#define TVD_VDO_CTRL2_write_enable3_mask                              (0x00000040)
#define TVD_VDO_CTRL2_dc_clamp_mode_mask                              (0x00000030)
#define TVD_VDO_CTRL2_write_enable2_mask                              (0x00000008)
#define TVD_VDO_CTRL2_cagc_en_mask                                    (0x00000004)
#define TVD_VDO_CTRL2_write_enable1_mask                              (0x00000002)
#define TVD_VDO_CTRL2_hagc_en_mask                                    (0x00000001)
#define TVD_VDO_CTRL2_write_enable9(data)                             (0x00100000&((data)<<20))
#define TVD_VDO_CTRL2_luma_notch_bw(data)                             (0x000C0000&((data)<<18))
#define TVD_VDO_CTRL2_write_enable8(data)                             (0x00020000&((data)<<17))
#define TVD_VDO_CTRL2_chroma_bw_lo(data)                              (0x00018000&((data)<<15))
#define TVD_VDO_CTRL2_write_enable7(data)                             (0x00004000&((data)<<14))
#define TVD_VDO_CTRL2_chroma_burst5or10(data)                         (0x00002000&((data)<<13))
#define TVD_VDO_CTRL2_write_enable6(data)                             (0x00001000&((data)<<12))
#define TVD_VDO_CTRL2_ped(data)                                       (0x00000800&((data)<<11))
#define TVD_VDO_CTRL2_write_enable5(data)                             (0x00000400&((data)<<10))
#define TVD_VDO_CTRL2_hagc_field(data)                                (0x00000200&((data)<<9))
#define TVD_VDO_CTRL2_write_enable4(data)                             (0x00000100&((data)<<8))
#define TVD_VDO_CTRL2_mv_hagc(data)                                   (0x00000080&((data)<<7))
#define TVD_VDO_CTRL2_write_enable3(data)                             (0x00000040&((data)<<6))
#define TVD_VDO_CTRL2_dc_clamp_mode(data)                             (0x00000030&((data)<<4))
#define TVD_VDO_CTRL2_write_enable2(data)                             (0x00000008&((data)<<3))
#define TVD_VDO_CTRL2_cagc_en(data)                                   (0x00000004&((data)<<2))
#define TVD_VDO_CTRL2_write_enable1(data)                             (0x00000002&((data)<<1))
#define TVD_VDO_CTRL2_hagc_en(data)                                   (0x00000001&(data))
#define TVD_VDO_CTRL2_get_write_enable9(data)                         ((0x00100000&(data))>>20)
#define TVD_VDO_CTRL2_get_luma_notch_bw(data)                         ((0x000C0000&(data))>>18)
#define TVD_VDO_CTRL2_get_write_enable8(data)                         ((0x00020000&(data))>>17)
#define TVD_VDO_CTRL2_get_chroma_bw_lo(data)                          ((0x00018000&(data))>>15)
#define TVD_VDO_CTRL2_get_write_enable7(data)                         ((0x00004000&(data))>>14)
#define TVD_VDO_CTRL2_get_chroma_burst5or10(data)                     ((0x00002000&(data))>>13)
#define TVD_VDO_CTRL2_get_write_enable6(data)                         ((0x00001000&(data))>>12)
#define TVD_VDO_CTRL2_get_ped(data)                                   ((0x00000800&(data))>>11)
#define TVD_VDO_CTRL2_get_write_enable5(data)                         ((0x00000400&(data))>>10)
#define TVD_VDO_CTRL2_get_hagc_field(data)                            ((0x00000200&(data))>>9)
#define TVD_VDO_CTRL2_get_write_enable4(data)                         ((0x00000100&(data))>>8)
#define TVD_VDO_CTRL2_get_mv_hagc(data)                               ((0x00000080&(data))>>7)
#define TVD_VDO_CTRL2_get_write_enable3(data)                         ((0x00000040&(data))>>6)
#define TVD_VDO_CTRL2_get_dc_clamp_mode(data)                         ((0x00000030&(data))>>4)
#define TVD_VDO_CTRL2_get_write_enable2(data)                         ((0x00000008&(data))>>3)
#define TVD_VDO_CTRL2_get_cagc_en(data)                               ((0x00000004&(data))>>2)
#define TVD_VDO_CTRL2_get_write_enable1(data)                         ((0x00000002&(data))>>1)
#define TVD_VDO_CTRL2_get_hagc_en(data)                               (0x00000001&(data))

#define TVD_YC_SEP_CTRL                                               0x18019008
#define TVD_YC_SEP_CTRL_reg_addr                                      "0xB8019008"
#define TVD_YC_SEP_CTRL_reg                                           0xB8019008
#define TVD_YC_SEP_CTRL_inst_addr                                     "0x0002"
#define TVD_YC_SEP_CTRL_inst                                          0x0002
#define TVD_YC_SEP_CTRL_write_enable2_shift                           (5)
#define TVD_YC_SEP_CTRL_colour_trap_shift                             (4)
#define TVD_YC_SEP_CTRL_write_enable1_shift                           (3)
#define TVD_YC_SEP_CTRL_adaptive_mode_shift                           (0)
#define TVD_YC_SEP_CTRL_write_enable2_mask                            (0x00000020)
#define TVD_YC_SEP_CTRL_colour_trap_mask                              (0x00000010)
#define TVD_YC_SEP_CTRL_write_enable1_mask                            (0x00000008)
#define TVD_YC_SEP_CTRL_adaptive_mode_mask                            (0x00000007)
#define TVD_YC_SEP_CTRL_write_enable2(data)                           (0x00000020&((data)<<5))
#define TVD_YC_SEP_CTRL_colour_trap(data)                             (0x00000010&((data)<<4))
#define TVD_YC_SEP_CTRL_write_enable1(data)                           (0x00000008&((data)<<3))
#define TVD_YC_SEP_CTRL_adaptive_mode(data)                           (0x00000007&(data))
#define TVD_YC_SEP_CTRL_get_write_enable2(data)                       ((0x00000020&(data))>>5)
#define TVD_YC_SEP_CTRL_get_colour_trap(data)                         ((0x00000010&(data))>>4)
#define TVD_YC_SEP_CTRL_get_write_enable1(data)                       ((0x00000008&(data))>>3)
#define TVD_YC_SEP_CTRL_get_adaptive_mode(data)                       (0x00000007&(data))

#define TVD_HOR_ACQ                                                   0x1801900C
#define TVD_HOR_ACQ_reg_addr                                          "0xB801900C"
#define TVD_HOR_ACQ_reg                                               0xB801900C
#define TVD_HOR_ACQ_inst_addr                                         "0x0003"
#define TVD_HOR_ACQ_inst                                              0x0003
#define TVD_HOR_ACQ_write_enable6_shift                               (29)
#define TVD_HOR_ACQ_hagc_shift                                        (21)
#define TVD_HOR_ACQ_write_enable5_shift                               (20)
#define TVD_HOR_ACQ_noise_thresh_shift                                (12)
#define TVD_HOR_ACQ_write_enable4_shift                               (11)
#define TVD_HOR_ACQ_adc_updn_swap_shift                               (10)
#define TVD_HOR_ACQ_write_enable3_shift                               (9)
#define TVD_HOR_ACQ_adc_input_swap_shift                              (8)
#define TVD_HOR_ACQ_write_enable2_shift                               (7)
#define TVD_HOR_ACQ_adc_cbcr_pump_swap_shift                          (6)
#define TVD_HOR_ACQ_write_enable1_shift                               (5)
#define TVD_HOR_ACQ_adc_gate_thresh_shift                             (0)
#define TVD_HOR_ACQ_write_enable6_mask                                (0x20000000)
#define TVD_HOR_ACQ_hagc_mask                                         (0x1FE00000)
#define TVD_HOR_ACQ_write_enable5_mask                                (0x00100000)
#define TVD_HOR_ACQ_noise_thresh_mask                                 (0x000FF000)
#define TVD_HOR_ACQ_write_enable4_mask                                (0x00000800)
#define TVD_HOR_ACQ_adc_updn_swap_mask                                (0x00000400)
#define TVD_HOR_ACQ_write_enable3_mask                                (0x00000200)
#define TVD_HOR_ACQ_adc_input_swap_mask                               (0x00000100)
#define TVD_HOR_ACQ_write_enable2_mask                                (0x00000080)
#define TVD_HOR_ACQ_adc_cbcr_pump_swap_mask                           (0x00000040)
#define TVD_HOR_ACQ_write_enable1_mask                                (0x00000020)
#define TVD_HOR_ACQ_adc_gate_thresh_mask                              (0x0000001F)
#define TVD_HOR_ACQ_write_enable6(data)                               (0x20000000&((data)<<29))
#define TVD_HOR_ACQ_hagc(data)                                        (0x1FE00000&((data)<<21))
#define TVD_HOR_ACQ_write_enable5(data)                               (0x00100000&((data)<<20))
#define TVD_HOR_ACQ_noise_thresh(data)                                (0x000FF000&((data)<<12))
#define TVD_HOR_ACQ_write_enable4(data)                               (0x00000800&((data)<<11))
#define TVD_HOR_ACQ_adc_updn_swap(data)                               (0x00000400&((data)<<10))
#define TVD_HOR_ACQ_write_enable3(data)                               (0x00000200&((data)<<9))
#define TVD_HOR_ACQ_adc_input_swap(data)                              (0x00000100&((data)<<8))
#define TVD_HOR_ACQ_write_enable2(data)                               (0x00000080&((data)<<7))
#define TVD_HOR_ACQ_adc_cbcr_pump_swap(data)                          (0x00000040&((data)<<6))
#define TVD_HOR_ACQ_write_enable1(data)                               (0x00000020&((data)<<5))
#define TVD_HOR_ACQ_adc_gate_thresh(data)                             (0x0000001F&(data))
#define TVD_HOR_ACQ_get_write_enable6(data)                           ((0x20000000&(data))>>29)
#define TVD_HOR_ACQ_get_hagc(data)                                    ((0x1FE00000&(data))>>21)
#define TVD_HOR_ACQ_get_write_enable5(data)                           ((0x00100000&(data))>>20)
#define TVD_HOR_ACQ_get_noise_thresh(data)                            ((0x000FF000&(data))>>12)
#define TVD_HOR_ACQ_get_write_enable4(data)                           ((0x00000800&(data))>>11)
#define TVD_HOR_ACQ_get_adc_updn_swap(data)                           ((0x00000400&(data))>>10)
#define TVD_HOR_ACQ_get_write_enable3(data)                           ((0x00000200&(data))>>9)
#define TVD_HOR_ACQ_get_adc_input_swap(data)                          ((0x00000100&(data))>>8)
#define TVD_HOR_ACQ_get_write_enable2(data)                           ((0x00000080&(data))>>7)
#define TVD_HOR_ACQ_get_adc_cbcr_pump_swap(data)                      ((0x00000040&(data))>>6)
#define TVD_HOR_ACQ_get_write_enable1(data)                           ((0x00000020&(data))>>5)
#define TVD_HOR_ACQ_get_adc_gate_thresh(data)                         (0x0000001F&(data))

#define TVD_OUT_CTRL                                                  0x18019010
#define TVD_OUT_CTRL_reg_addr                                         "0xB8019010"
#define TVD_OUT_CTRL_reg                                              0xB8019010
#define TVD_OUT_CTRL_inst_addr                                        "0x0004"
#define TVD_OUT_CTRL_inst                                             0x0004
#define TVD_OUT_CTRL_write_enable3_shift                              (9)
#define TVD_OUT_CTRL_cbcr_swap_shift                                  (8)
#define TVD_OUT_CTRL_write_enable2_shift                              (7)
#define TVD_OUT_CTRL_blue_mode_shift                                  (5)
#define TVD_OUT_CTRL_write_enable1_shift                              (4)
#define TVD_OUT_CTRL_yc_delay_shift                                   (0)
#define TVD_OUT_CTRL_write_enable3_mask                               (0x00000200)
#define TVD_OUT_CTRL_cbcr_swap_mask                                   (0x00000100)
#define TVD_OUT_CTRL_write_enable2_mask                               (0x00000080)
#define TVD_OUT_CTRL_blue_mode_mask                                   (0x00000060)
#define TVD_OUT_CTRL_write_enable1_mask                               (0x00000010)
#define TVD_OUT_CTRL_yc_delay_mask                                    (0x0000000F)
#define TVD_OUT_CTRL_write_enable3(data)                              (0x00000200&((data)<<9))
#define TVD_OUT_CTRL_cbcr_swap(data)                                  (0x00000100&((data)<<8))
#define TVD_OUT_CTRL_write_enable2(data)                              (0x00000080&((data)<<7))
#define TVD_OUT_CTRL_blue_mode(data)                                  (0x00000060&((data)<<5))
#define TVD_OUT_CTRL_write_enable1(data)                              (0x00000010&((data)<<4))
#define TVD_OUT_CTRL_yc_delay(data)                                   (0x0000000F&(data))
#define TVD_OUT_CTRL_get_write_enable3(data)                          ((0x00000200&(data))>>9)
#define TVD_OUT_CTRL_get_cbcr_swap(data)                              ((0x00000100&(data))>>8)
#define TVD_OUT_CTRL_get_write_enable2(data)                          ((0x00000080&(data))>>7)
#define TVD_OUT_CTRL_get_blue_mode(data)                              ((0x00000060&(data))>>5)
#define TVD_OUT_CTRL_get_write_enable1(data)                          ((0x00000010&(data))>>4)
#define TVD_OUT_CTRL_get_yc_delay(data)                               (0x0000000F&(data))

#define TVD_LUMA_ADJUST                                               0x18019014
#define TVD_LUMA_ADJUST_reg_addr                                      "0xB8019014"
#define TVD_LUMA_ADJUST_reg                                           0xB8019014
#define TVD_LUMA_ADJUST_inst_addr                                     "0x0005"
#define TVD_LUMA_ADJUST_inst                                          0x0005
#define TVD_LUMA_ADJUST_write_enable2_shift                           (17)
#define TVD_LUMA_ADJUST_contrast_shift                                (9)
#define TVD_LUMA_ADJUST_write_enable1_shift                           (8)
#define TVD_LUMA_ADJUST_brightness_shift                              (0)
#define TVD_LUMA_ADJUST_write_enable2_mask                            (0x00020000)
#define TVD_LUMA_ADJUST_contrast_mask                                 (0x0001FE00)
#define TVD_LUMA_ADJUST_write_enable1_mask                            (0x00000100)
#define TVD_LUMA_ADJUST_brightness_mask                               (0x000000FF)
#define TVD_LUMA_ADJUST_write_enable2(data)                           (0x00020000&((data)<<17))
#define TVD_LUMA_ADJUST_contrast(data)                                (0x0001FE00&((data)<<9))
#define TVD_LUMA_ADJUST_write_enable1(data)                           (0x00000100&((data)<<8))
#define TVD_LUMA_ADJUST_brightness(data)                              (0x000000FF&(data))
#define TVD_LUMA_ADJUST_get_write_enable2(data)                       ((0x00020000&(data))>>17)
#define TVD_LUMA_ADJUST_get_contrast(data)                            ((0x0001FE00&(data))>>9)
#define TVD_LUMA_ADJUST_get_write_enable1(data)                       ((0x00000100&(data))>>8)
#define TVD_LUMA_ADJUST_get_brightness(data)                          (0x000000FF&(data))

#define TVD_CHROMA_ADJUST                                             0x18019018
#define TVD_CHROMA_ADJUST_reg_addr                                    "0xB8019018"
#define TVD_CHROMA_ADJUST_reg                                         0xB8019018
#define TVD_CHROMA_ADJUST_inst_addr                                   "0x0006"
#define TVD_CHROMA_ADJUST_inst                                        0x0006
#define TVD_CHROMA_ADJUST_write_enable3_shift                         (26)
#define TVD_CHROMA_ADJUST_saturation_shift                            (18)
#define TVD_CHROMA_ADJUST_write_enable2_shift                         (17)
#define TVD_CHROMA_ADJUST_hue_shift                                   (9)
#define TVD_CHROMA_ADJUST_write_enable1_shift                         (8)
#define TVD_CHROMA_ADJUST_cagc_shift                                  (0)
#define TVD_CHROMA_ADJUST_write_enable3_mask                          (0x04000000)
#define TVD_CHROMA_ADJUST_saturation_mask                             (0x03FC0000)
#define TVD_CHROMA_ADJUST_write_enable2_mask                          (0x00020000)
#define TVD_CHROMA_ADJUST_hue_mask                                    (0x0001FE00)
#define TVD_CHROMA_ADJUST_write_enable1_mask                          (0x00000100)
#define TVD_CHROMA_ADJUST_cagc_mask                                   (0x000000FF)
#define TVD_CHROMA_ADJUST_write_enable3(data)                         (0x04000000&((data)<<26))
#define TVD_CHROMA_ADJUST_saturation(data)                            (0x03FC0000&((data)<<18))
#define TVD_CHROMA_ADJUST_write_enable2(data)                         (0x00020000&((data)<<17))
#define TVD_CHROMA_ADJUST_hue(data)                                   (0x0001FE00&((data)<<9))
#define TVD_CHROMA_ADJUST_write_enable1(data)                         (0x00000100&((data)<<8))
#define TVD_CHROMA_ADJUST_cagc(data)                                  (0x000000FF&(data))
#define TVD_CHROMA_ADJUST_get_write_enable3(data)                     ((0x04000000&(data))>>26)
#define TVD_CHROMA_ADJUST_get_saturation(data)                        ((0x03FC0000&(data))>>18)
#define TVD_CHROMA_ADJUST_get_write_enable2(data)                     ((0x00020000&(data))>>17)
#define TVD_CHROMA_ADJUST_get_hue(data)                               ((0x0001FE00&(data))>>9)
#define TVD_CHROMA_ADJUST_get_write_enable1(data)                     ((0x00000100&(data))>>8)
#define TVD_CHROMA_ADJUST_get_cagc(data)                              (0x000000FF&(data))

#define TVD_CHROMA_KILL_AUTOPOS                                       0x1801901C
#define TVD_CHROMA_KILL_AUTOPOS_reg_addr                              "0xB801901C"
#define TVD_CHROMA_KILL_AUTOPOS_reg                                   0xB801901C
#define TVD_CHROMA_KILL_AUTOPOS_inst_addr                             "0x0007"
#define TVD_CHROMA_KILL_AUTOPOS_inst                                  0x0007
#define TVD_CHROMA_KILL_AUTOPOS_write_enable7_shift                   (21)
#define TVD_CHROMA_KILL_AUTOPOS_user_ckill_mode_shift                 (19)
#define TVD_CHROMA_KILL_AUTOPOS_write_enable6_shift                   (18)
#define TVD_CHROMA_KILL_AUTOPOS_vbi_ckill_shift                       (17)
#define TVD_CHROMA_KILL_AUTOPOS_write_enable5_shift                   (16)
#define TVD_CHROMA_KILL_AUTOPOS_hlock_ckill_shift                     (15)
#define TVD_CHROMA_KILL_AUTOPOS_write_enable4_shift                   (14)
#define TVD_CHROMA_KILL_AUTOPOS_chroma_kill_shift                     (10)
#define TVD_CHROMA_KILL_AUTOPOS_write_enable3_shift                   (9)
#define TVD_CHROMA_KILL_AUTOPOS_secam_test_mode_shift                 (8)
#define TVD_CHROMA_KILL_AUTOPOS_write_enable2_shift                   (7)
#define TVD_CHROMA_KILL_AUTOPOS_fixed_burstgate_shift                 (6)
#define TVD_CHROMA_KILL_AUTOPOS_write_enable1_shift                   (5)
#define TVD_CHROMA_KILL_AUTOPOS_cautopos_shift                        (0)
#define TVD_CHROMA_KILL_AUTOPOS_write_enable7_mask                    (0x00200000)
#define TVD_CHROMA_KILL_AUTOPOS_user_ckill_mode_mask                  (0x00180000)
#define TVD_CHROMA_KILL_AUTOPOS_write_enable6_mask                    (0x00040000)
#define TVD_CHROMA_KILL_AUTOPOS_vbi_ckill_mask                        (0x00020000)
#define TVD_CHROMA_KILL_AUTOPOS_write_enable5_mask                    (0x00010000)
#define TVD_CHROMA_KILL_AUTOPOS_hlock_ckill_mask                      (0x00008000)
#define TVD_CHROMA_KILL_AUTOPOS_write_enable4_mask                    (0x00004000)
#define TVD_CHROMA_KILL_AUTOPOS_chroma_kill_mask                      (0x00003C00)
#define TVD_CHROMA_KILL_AUTOPOS_write_enable3_mask                    (0x00000200)
#define TVD_CHROMA_KILL_AUTOPOS_secam_test_mode_mask                  (0x00000100)
#define TVD_CHROMA_KILL_AUTOPOS_write_enable2_mask                    (0x00000080)
#define TVD_CHROMA_KILL_AUTOPOS_fixed_burstgate_mask                  (0x00000040)
#define TVD_CHROMA_KILL_AUTOPOS_write_enable1_mask                    (0x00000020)
#define TVD_CHROMA_KILL_AUTOPOS_cautopos_mask                         (0x0000001F)
#define TVD_CHROMA_KILL_AUTOPOS_write_enable7(data)                   (0x00200000&((data)<<21))
#define TVD_CHROMA_KILL_AUTOPOS_user_ckill_mode(data)                 (0x00180000&((data)<<19))
#define TVD_CHROMA_KILL_AUTOPOS_write_enable6(data)                   (0x00040000&((data)<<18))
#define TVD_CHROMA_KILL_AUTOPOS_vbi_ckill(data)                       (0x00020000&((data)<<17))
#define TVD_CHROMA_KILL_AUTOPOS_write_enable5(data)                   (0x00010000&((data)<<16))
#define TVD_CHROMA_KILL_AUTOPOS_hlock_ckill(data)                     (0x00008000&((data)<<15))
#define TVD_CHROMA_KILL_AUTOPOS_write_enable4(data)                   (0x00004000&((data)<<14))
#define TVD_CHROMA_KILL_AUTOPOS_chroma_kill(data)                     (0x00003C00&((data)<<10))
#define TVD_CHROMA_KILL_AUTOPOS_write_enable3(data)                   (0x00000200&((data)<<9))
#define TVD_CHROMA_KILL_AUTOPOS_secam_test_mode(data)                 (0x00000100&((data)<<8))
#define TVD_CHROMA_KILL_AUTOPOS_write_enable2(data)                   (0x00000080&((data)<<7))
#define TVD_CHROMA_KILL_AUTOPOS_fixed_burstgate(data)                 (0x00000040&((data)<<6))
#define TVD_CHROMA_KILL_AUTOPOS_write_enable1(data)                   (0x00000020&((data)<<5))
#define TVD_CHROMA_KILL_AUTOPOS_cautopos(data)                        (0x0000001F&(data))
#define TVD_CHROMA_KILL_AUTOPOS_get_write_enable7(data)               ((0x00200000&(data))>>21)
#define TVD_CHROMA_KILL_AUTOPOS_get_user_ckill_mode(data)             ((0x00180000&(data))>>19)
#define TVD_CHROMA_KILL_AUTOPOS_get_write_enable6(data)               ((0x00040000&(data))>>18)
#define TVD_CHROMA_KILL_AUTOPOS_get_vbi_ckill(data)                   ((0x00020000&(data))>>17)
#define TVD_CHROMA_KILL_AUTOPOS_get_write_enable5(data)               ((0x00010000&(data))>>16)
#define TVD_CHROMA_KILL_AUTOPOS_get_hlock_ckill(data)                 ((0x00008000&(data))>>15)
#define TVD_CHROMA_KILL_AUTOPOS_get_write_enable4(data)               ((0x00004000&(data))>>14)
#define TVD_CHROMA_KILL_AUTOPOS_get_chroma_kill(data)                 ((0x00003C00&(data))>>10)
#define TVD_CHROMA_KILL_AUTOPOS_get_write_enable3(data)               ((0x00000200&(data))>>9)
#define TVD_CHROMA_KILL_AUTOPOS_get_secam_test_mode(data)             ((0x00000100&(data))>>8)
#define TVD_CHROMA_KILL_AUTOPOS_get_write_enable2(data)               ((0x00000080&(data))>>7)
#define TVD_CHROMA_KILL_AUTOPOS_get_fixed_burstgate(data)             ((0x00000040&(data))>>6)
#define TVD_CHROMA_KILL_AUTOPOS_get_write_enable1(data)               ((0x00000020&(data))>>5)
#define TVD_CHROMA_KILL_AUTOPOS_get_cautopos(data)                    (0x0000001F&(data))

#define TVD_AGC_PEAKGATE                                              0x18019020
#define TVD_AGC_PEAKGATE_reg_addr                                     "0xB8019020"
#define TVD_AGC_PEAKGATE_reg                                          0xB8019020
#define TVD_AGC_PEAKGATE_inst_addr                                    "0x0008"
#define TVD_AGC_PEAKGATE_inst                                         0x0008
#define TVD_AGC_PEAKGATE_write_enable6_shift                          (20)
#define TVD_AGC_PEAKGATE_agc_peak_nominal_shift                       (13)
#define TVD_AGC_PEAKGATE_write_enable5_shift                          (12)
#define TVD_AGC_PEAKGATE_agc_gate_vsync_coarse_shift                  (11)
#define TVD_AGC_PEAKGATE_write_enable4_shift                          (10)
#define TVD_AGC_PEAKGATE_agc_gate_vsync_stip_shift                    (9)
#define TVD_AGC_PEAKGATE_write_enable3_shift                          (8)
#define TVD_AGC_PEAKGATE_agc_gate_kill_mode_shift                     (6)
#define TVD_AGC_PEAKGATE_write_enable2_shift                          (5)
#define TVD_AGC_PEAKGATE_agc_peak_en_shift                            (4)
#define TVD_AGC_PEAKGATE_write_enable1_shift                          (3)
#define TVD_AGC_PEAKGATE_agc_peak_cntl_shift                          (0)
#define TVD_AGC_PEAKGATE_write_enable6_mask                           (0x00100000)
#define TVD_AGC_PEAKGATE_agc_peak_nominal_mask                        (0x000FE000)
#define TVD_AGC_PEAKGATE_write_enable5_mask                           (0x00001000)
#define TVD_AGC_PEAKGATE_agc_gate_vsync_coarse_mask                   (0x00000800)
#define TVD_AGC_PEAKGATE_write_enable4_mask                           (0x00000400)
#define TVD_AGC_PEAKGATE_agc_gate_vsync_stip_mask                     (0x00000200)
#define TVD_AGC_PEAKGATE_write_enable3_mask                           (0x00000100)
#define TVD_AGC_PEAKGATE_agc_gate_kill_mode_mask                      (0x000000C0)
#define TVD_AGC_PEAKGATE_write_enable2_mask                           (0x00000020)
#define TVD_AGC_PEAKGATE_agc_peak_en_mask                             (0x00000010)
#define TVD_AGC_PEAKGATE_write_enable1_mask                           (0x00000008)
#define TVD_AGC_PEAKGATE_agc_peak_cntl_mask                           (0x00000007)
#define TVD_AGC_PEAKGATE_write_enable6(data)                          (0x00100000&((data)<<20))
#define TVD_AGC_PEAKGATE_agc_peak_nominal(data)                       (0x000FE000&((data)<<13))
#define TVD_AGC_PEAKGATE_write_enable5(data)                          (0x00001000&((data)<<12))
#define TVD_AGC_PEAKGATE_agc_gate_vsync_coarse(data)                  (0x00000800&((data)<<11))
#define TVD_AGC_PEAKGATE_write_enable4(data)                          (0x00000400&((data)<<10))
#define TVD_AGC_PEAKGATE_agc_gate_vsync_stip(data)                    (0x00000200&((data)<<9))
#define TVD_AGC_PEAKGATE_write_enable3(data)                          (0x00000100&((data)<<8))
#define TVD_AGC_PEAKGATE_agc_gate_kill_mode(data)                     (0x000000C0&((data)<<6))
#define TVD_AGC_PEAKGATE_write_enable2(data)                          (0x00000020&((data)<<5))
#define TVD_AGC_PEAKGATE_agc_peak_en(data)                            (0x00000010&((data)<<4))
#define TVD_AGC_PEAKGATE_write_enable1(data)                          (0x00000008&((data)<<3))
#define TVD_AGC_PEAKGATE_agc_peak_cntl(data)                          (0x00000007&(data))
#define TVD_AGC_PEAKGATE_get_write_enable6(data)                      ((0x00100000&(data))>>20)
#define TVD_AGC_PEAKGATE_get_agc_peak_nominal(data)                   ((0x000FE000&(data))>>13)
#define TVD_AGC_PEAKGATE_get_write_enable5(data)                      ((0x00001000&(data))>>12)
#define TVD_AGC_PEAKGATE_get_agc_gate_vsync_coarse(data)              ((0x00000800&(data))>>11)
#define TVD_AGC_PEAKGATE_get_write_enable4(data)                      ((0x00000400&(data))>>10)
#define TVD_AGC_PEAKGATE_get_agc_gate_vsync_stip(data)                ((0x00000200&(data))>>9)
#define TVD_AGC_PEAKGATE_get_write_enable3(data)                      ((0x00000100&(data))>>8)
#define TVD_AGC_PEAKGATE_get_agc_gate_kill_mode(data)                 ((0x000000C0&(data))>>6)
#define TVD_AGC_PEAKGATE_get_write_enable2(data)                      ((0x00000020&(data))>>5)
#define TVD_AGC_PEAKGATE_get_agc_peak_en(data)                        ((0x00000010&(data))>>4)
#define TVD_AGC_PEAKGATE_get_write_enable1(data)                      ((0x00000008&(data))>>3)
#define TVD_AGC_PEAKGATE_get_agc_peak_cntl(data)                      (0x00000007&(data))

#define TVD_AGC_GATE                                                  0x18019024
#define TVD_AGC_GATE_reg_addr                                         "0xB8019024"
#define TVD_AGC_GATE_reg                                              0xB8019024
#define TVD_AGC_GATE_inst_addr                                        "0x0009"
#define TVD_AGC_GATE_inst                                             0x0009
#define TVD_AGC_GATE_write_enable3_shift                              (28)
#define TVD_AGC_GATE_agc_gate_start_shift                             (17)
#define TVD_AGC_GATE_write_enable2_shift                              (16)
#define TVD_AGC_GATE_agc_gate_width_shift                             (9)
#define TVD_AGC_GATE_write_enable1_shift                              (8)
#define TVD_AGC_GATE_agc_bp_delay_shift                               (0)
#define TVD_AGC_GATE_write_enable3_mask                               (0x10000000)
#define TVD_AGC_GATE_agc_gate_start_mask                              (0x0FFE0000)
#define TVD_AGC_GATE_write_enable2_mask                               (0x00010000)
#define TVD_AGC_GATE_agc_gate_width_mask                              (0x0000FE00)
#define TVD_AGC_GATE_write_enable1_mask                               (0x00000100)
#define TVD_AGC_GATE_agc_bp_delay_mask                                (0x000000FF)
#define TVD_AGC_GATE_write_enable3(data)                              (0x10000000&((data)<<28))
#define TVD_AGC_GATE_agc_gate_start(data)                             (0x0FFE0000&((data)<<17))
#define TVD_AGC_GATE_write_enable2(data)                              (0x00010000&((data)<<16))
#define TVD_AGC_GATE_agc_gate_width(data)                             (0x0000FE00&((data)<<9))
#define TVD_AGC_GATE_write_enable1(data)                              (0x00000100&((data)<<8))
#define TVD_AGC_GATE_agc_bp_delay(data)                               (0x000000FF&(data))
#define TVD_AGC_GATE_get_write_enable3(data)                          ((0x10000000&(data))>>28)
#define TVD_AGC_GATE_get_agc_gate_start(data)                         ((0x0FFE0000&(data))>>17)
#define TVD_AGC_GATE_get_write_enable2(data)                          ((0x00010000&(data))>>16)
#define TVD_AGC_GATE_get_agc_gate_width(data)                         ((0x0000FE00&(data))>>9)
#define TVD_AGC_GATE_get_write_enable1(data)                          ((0x00000100&(data))>>8)
#define TVD_AGC_GATE_get_agc_bp_delay(data)                           (0x000000FF&(data))

#define TVD_HPLL_CTRL                                                 0x18019028
#define TVD_HPLL_CTRL_reg_addr                                        "0xB8019028"
#define TVD_HPLL_CTRL_reg                                             0xB8019028
#define TVD_HPLL_CTRL_inst_addr                                       "0x000A"
#define TVD_HPLL_CTRL_inst                                            0x000A
#define TVD_HPLL_CTRL_write_enable7_shift                             (22)
#define TVD_HPLL_CTRL_locked_count_noisy_max_shift                    (18)
#define TVD_HPLL_CTRL_write_enable6_shift                             (17)
#define TVD_HPLL_CTRL_locked_count_clean_max_shift                    (13)
#define TVD_HPLL_CTRL_write_enable5_shift                             (12)
#define TVD_HPLL_CTRL_hlock_vsync_mode_shift                          (10)
#define TVD_HPLL_CTRL_write_enable4_shift                             (9)
#define TVD_HPLL_CTRL_hstate_fixed_shift                              (8)
#define TVD_HPLL_CTRL_write_enable3_shift                             (7)
#define TVD_HPLL_CTRL_disable_hfine_shift                             (6)
#define TVD_HPLL_CTRL_write_enable2_shift                             (5)
#define TVD_HPLL_CTRL_hstate_unlocked_shift                           (4)
#define TVD_HPLL_CTRL_write_enable1_shift                             (3)
#define TVD_HPLL_CTRL_hstate_max_shift                                (0)
#define TVD_HPLL_CTRL_write_enable7_mask                              (0x00400000)
#define TVD_HPLL_CTRL_locked_count_noisy_max_mask                     (0x003C0000)
#define TVD_HPLL_CTRL_write_enable6_mask                              (0x00020000)
#define TVD_HPLL_CTRL_locked_count_clean_max_mask                     (0x0001E000)
#define TVD_HPLL_CTRL_write_enable5_mask                              (0x00001000)
#define TVD_HPLL_CTRL_hlock_vsync_mode_mask                           (0x00000C00)
#define TVD_HPLL_CTRL_write_enable4_mask                              (0x00000200)
#define TVD_HPLL_CTRL_hstate_fixed_mask                               (0x00000100)
#define TVD_HPLL_CTRL_write_enable3_mask                              (0x00000080)
#define TVD_HPLL_CTRL_disable_hfine_mask                              (0x00000040)
#define TVD_HPLL_CTRL_write_enable2_mask                              (0x00000020)
#define TVD_HPLL_CTRL_hstate_unlocked_mask                            (0x00000010)
#define TVD_HPLL_CTRL_write_enable1_mask                              (0x00000008)
#define TVD_HPLL_CTRL_hstate_max_mask                                 (0x00000007)
#define TVD_HPLL_CTRL_write_enable7(data)                             (0x00400000&((data)<<22))
#define TVD_HPLL_CTRL_locked_count_noisy_max(data)                    (0x003C0000&((data)<<18))
#define TVD_HPLL_CTRL_write_enable6(data)                             (0x00020000&((data)<<17))
#define TVD_HPLL_CTRL_locked_count_clean_max(data)                    (0x0001E000&((data)<<13))
#define TVD_HPLL_CTRL_write_enable5(data)                             (0x00001000&((data)<<12))
#define TVD_HPLL_CTRL_hlock_vsync_mode(data)                          (0x00000C00&((data)<<10))
#define TVD_HPLL_CTRL_write_enable4(data)                             (0x00000200&((data)<<9))
#define TVD_HPLL_CTRL_hstate_fixed(data)                              (0x00000100&((data)<<8))
#define TVD_HPLL_CTRL_write_enable3(data)                             (0x00000080&((data)<<7))
#define TVD_HPLL_CTRL_disable_hfine(data)                             (0x00000040&((data)<<6))
#define TVD_HPLL_CTRL_write_enable2(data)                             (0x00000020&((data)<<5))
#define TVD_HPLL_CTRL_hstate_unlocked(data)                           (0x00000010&((data)<<4))
#define TVD_HPLL_CTRL_write_enable1(data)                             (0x00000008&((data)<<3))
#define TVD_HPLL_CTRL_hstate_max(data)                                (0x00000007&(data))
#define TVD_HPLL_CTRL_get_write_enable7(data)                         ((0x00400000&(data))>>22)
#define TVD_HPLL_CTRL_get_locked_count_noisy_max(data)                ((0x003C0000&(data))>>18)
#define TVD_HPLL_CTRL_get_write_enable6(data)                         ((0x00020000&(data))>>17)
#define TVD_HPLL_CTRL_get_locked_count_clean_max(data)                ((0x0001E000&(data))>>13)
#define TVD_HPLL_CTRL_get_write_enable5(data)                         ((0x00001000&(data))>>12)
#define TVD_HPLL_CTRL_get_hlock_vsync_mode(data)                      ((0x00000C00&(data))>>10)
#define TVD_HPLL_CTRL_get_write_enable4(data)                         ((0x00000200&(data))>>9)
#define TVD_HPLL_CTRL_get_hstate_fixed(data)                          ((0x00000100&(data))>>8)
#define TVD_HPLL_CTRL_get_write_enable3(data)                         ((0x00000080&(data))>>7)
#define TVD_HPLL_CTRL_get_disable_hfine(data)                         ((0x00000040&(data))>>6)
#define TVD_HPLL_CTRL_get_write_enable2(data)                         ((0x00000020&(data))>>5)
#define TVD_HPLL_CTRL_get_hstate_unlocked(data)                       ((0x00000010&(data))>>4)
#define TVD_HPLL_CTRL_get_write_enable1(data)                         ((0x00000008&(data))>>3)
#define TVD_HPLL_CTRL_get_hstate_max(data)                            (0x00000007&(data))

#define TVD_CHROMA_DTO                                                0x1801902C
#define TVD_CHROMA_DTO_reg_addr                                       "0xB801902C"
#define TVD_CHROMA_DTO_reg                                            0xB801902C
#define TVD_CHROMA_DTO_inst_addr                                      "0x000B"
#define TVD_CHROMA_DTO_inst                                           0x000B
#define TVD_CHROMA_DTO_cdto_fixed_shift                               (30)
#define TVD_CHROMA_DTO_cdto_inc_shift                                 (0)
#define TVD_CHROMA_DTO_cdto_fixed_mask                                (0x40000000)
#define TVD_CHROMA_DTO_cdto_inc_mask                                  (0x3FFFFFFF)
#define TVD_CHROMA_DTO_cdto_fixed(data)                               (0x40000000&((data)<<30))
#define TVD_CHROMA_DTO_cdto_inc(data)                                 (0x3FFFFFFF&(data))
#define TVD_CHROMA_DTO_get_cdto_fixed(data)                           ((0x40000000&(data))>>30)
#define TVD_CHROMA_DTO_get_cdto_inc(data)                             (0x3FFFFFFF&(data))

#define TVD_HSYNC_DTO                                                 0x18019030
#define TVD_HSYNC_DTO_reg_addr                                        "0xB8019030"
#define TVD_HSYNC_DTO_reg                                             0xB8019030
#define TVD_HSYNC_DTO_inst_addr                                       "0x000C"
#define TVD_HSYNC_DTO_inst                                            0x000C
#define TVD_HSYNC_DTO_hdto_fixed_shift                                (30)
#define TVD_HSYNC_DTO_hdto_inc_shift                                  (0)
#define TVD_HSYNC_DTO_hdto_fixed_mask                                 (0x40000000)
#define TVD_HSYNC_DTO_hdto_inc_mask                                   (0x3FFFFFFF)
#define TVD_HSYNC_DTO_hdto_fixed(data)                                (0x40000000&((data)<<30))
#define TVD_HSYNC_DTO_hdto_inc(data)                                  (0x3FFFFFFF&(data))
#define TVD_HSYNC_DTO_get_hdto_fixed(data)                            ((0x40000000&(data))>>30)
#define TVD_HSYNC_DTO_get_hdto_inc(data)                              (0x3FFFFFFF&(data))

#define TVD_HSYNC_OCCUR                                               0x18019034
#define TVD_HSYNC_OCCUR_reg_addr                                      "0xB8019034"
#define TVD_HSYNC_OCCUR_reg                                           0xB8019034
#define TVD_HSYNC_OCCUR_inst_addr                                     "0x000D"
#define TVD_HSYNC_OCCUR_inst                                          0x000D
#define TVD_HSYNC_OCCUR_hsync_rising_shift                            (8)
#define TVD_HSYNC_OCCUR_hsync_phase_offset_shift                      (0)
#define TVD_HSYNC_OCCUR_hsync_rising_mask                             (0x0000FF00)
#define TVD_HSYNC_OCCUR_hsync_phase_offset_mask                       (0x000000FF)
#define TVD_HSYNC_OCCUR_hsync_rising(data)                            (0x0000FF00&((data)<<8))
#define TVD_HSYNC_OCCUR_hsync_phase_offset(data)                      (0x000000FF&(data))
#define TVD_HSYNC_OCCUR_get_hsync_rising(data)                        ((0x0000FF00&(data))>>8)
#define TVD_HSYNC_OCCUR_get_hsync_phase_offset(data)                  (0x000000FF&(data))

#define TVD_HSYNC_GATE_TIME                                           0x18019038
#define TVD_HSYNC_GATE_TIME_reg_addr                                  "0xB8019038"
#define TVD_HSYNC_GATE_TIME_reg                                       0xB8019038
#define TVD_HSYNC_GATE_TIME_inst_addr                                 "0x000E"
#define TVD_HSYNC_GATE_TIME_inst                                      0x000E
#define TVD_HSYNC_GATE_TIME_hsync_gate_start_shift                    (8)
#define TVD_HSYNC_GATE_TIME_hsync_gate_end_shift                      (0)
#define TVD_HSYNC_GATE_TIME_hsync_gate_start_mask                     (0x0000FF00)
#define TVD_HSYNC_GATE_TIME_hsync_gate_end_mask                       (0x000000FF)
#define TVD_HSYNC_GATE_TIME_hsync_gate_start(data)                    (0x0000FF00&((data)<<8))
#define TVD_HSYNC_GATE_TIME_hsync_gate_end(data)                      (0x000000FF&(data))
#define TVD_HSYNC_GATE_TIME_get_hsync_gate_start(data)                ((0x0000FF00&(data))>>8)
#define TVD_HSYNC_GATE_TIME_get_hsync_gate_end(data)                  (0x000000FF&(data))

#define TVD_HSYNC_TIP_TIME                                            0x1801903C
#define TVD_HSYNC_TIP_TIME_reg_addr                                   "0xB801903C"
#define TVD_HSYNC_TIP_TIME_reg                                        0xB801903C
#define TVD_HSYNC_TIP_TIME_inst_addr                                  "0x000F"
#define TVD_HSYNC_TIP_TIME_inst                                       0x000F
#define TVD_HSYNC_TIP_TIME_hsync_tip_start_shift                      (8)
#define TVD_HSYNC_TIP_TIME_hsync_tip_end_shift                        (0)
#define TVD_HSYNC_TIP_TIME_hsync_tip_start_mask                       (0x0000FF00)
#define TVD_HSYNC_TIP_TIME_hsync_tip_end_mask                         (0x000000FF)
#define TVD_HSYNC_TIP_TIME_hsync_tip_start(data)                      (0x0000FF00&((data)<<8))
#define TVD_HSYNC_TIP_TIME_hsync_tip_end(data)                        (0x000000FF&(data))
#define TVD_HSYNC_TIP_TIME_get_hsync_tip_start(data)                  ((0x0000FF00&(data))>>8)
#define TVD_HSYNC_TIP_TIME_get_hsync_tip_end(data)                    (0x000000FF&(data))

#define TVD_HSYNC_RISING_TIME                                         0x18019040
#define TVD_HSYNC_RISING_TIME_reg_addr                                "0xB8019040"
#define TVD_HSYNC_RISING_TIME_reg                                     0xB8019040
#define TVD_HSYNC_RISING_TIME_inst_addr                               "0x0010"
#define TVD_HSYNC_RISING_TIME_inst                                    0x0010
#define TVD_HSYNC_RISING_TIME_hsync_rising_start_shift                (8)
#define TVD_HSYNC_RISING_TIME_hsync_rising_end_shift                  (0)
#define TVD_HSYNC_RISING_TIME_hsync_rising_start_mask                 (0x0000FF00)
#define TVD_HSYNC_RISING_TIME_hsync_rising_end_mask                   (0x000000FF)
#define TVD_HSYNC_RISING_TIME_hsync_rising_start(data)                (0x0000FF00&((data)<<8))
#define TVD_HSYNC_RISING_TIME_hsync_rising_end(data)                  (0x000000FF&(data))
#define TVD_HSYNC_RISING_TIME_get_hsync_rising_start(data)            ((0x0000FF00&(data))>>8)
#define TVD_HSYNC_RISING_TIME_get_hsync_rising_end(data)              (0x000000FF&(data))

#define TVD_BACKPROCH_TIME                                            0x18019044
#define TVD_BACKPROCH_TIME_reg_addr                                   "0xB8019044"
#define TVD_BACKPROCH_TIME_reg                                        0xB8019044
#define TVD_BACKPROCH_TIME_inst_addr                                  "0x0011"
#define TVD_BACKPROCH_TIME_inst                                       0x0011
#define TVD_BACKPROCH_TIME_backporch_start_shift                      (8)
#define TVD_BACKPROCH_TIME_backporch_end_shift                        (0)
#define TVD_BACKPROCH_TIME_backporch_start_mask                       (0x0000FF00)
#define TVD_BACKPROCH_TIME_backporch_end_mask                         (0x000000FF)
#define TVD_BACKPROCH_TIME_backporch_start(data)                      (0x0000FF00&((data)<<8))
#define TVD_BACKPROCH_TIME_backporch_end(data)                        (0x000000FF&(data))
#define TVD_BACKPROCH_TIME_get_backporch_start(data)                  ((0x0000FF00&(data))>>8)
#define TVD_BACKPROCH_TIME_get_backporch_end(data)                    (0x000000FF&(data))

#define TVD_HBLANK_TIME                                               0x18019048
#define TVD_HBLANK_TIME_reg_addr                                      "0xB8019048"
#define TVD_HBLANK_TIME_reg                                           0xB8019048
#define TVD_HBLANK_TIME_inst_addr                                     "0x0012"
#define TVD_HBLANK_TIME_inst                                          0x0012
#define TVD_HBLANK_TIME_hblank_start_shift                            (8)
#define TVD_HBLANK_TIME_hblank_end_shift                              (0)
#define TVD_HBLANK_TIME_hblank_start_mask                             (0x0000FF00)
#define TVD_HBLANK_TIME_hblank_end_mask                               (0x000000FF)
#define TVD_HBLANK_TIME_hblank_start(data)                            (0x0000FF00&((data)<<8))
#define TVD_HBLANK_TIME_hblank_end(data)                              (0x000000FF&(data))
#define TVD_HBLANK_TIME_get_hblank_start(data)                        ((0x0000FF00&(data))>>8)
#define TVD_HBLANK_TIME_get_hblank_end(data)                          (0x000000FF&(data))

#define TVD_BURST_GATE_TIME                                           0x1801904C
#define TVD_BURST_GATE_TIME_reg_addr                                  "0xB801904C"
#define TVD_BURST_GATE_TIME_reg                                       0xB801904C
#define TVD_BURST_GATE_TIME_inst_addr                                 "0x0013"
#define TVD_BURST_GATE_TIME_inst                                      0x0013
#define TVD_BURST_GATE_TIME_burst_gate_start_shift                    (8)
#define TVD_BURST_GATE_TIME_burst_gate_end_shift                      (0)
#define TVD_BURST_GATE_TIME_burst_gate_start_mask                     (0x0000FF00)
#define TVD_BURST_GATE_TIME_burst_gate_end_mask                       (0x000000FF)
#define TVD_BURST_GATE_TIME_burst_gate_start(data)                    (0x0000FF00&((data)<<8))
#define TVD_BURST_GATE_TIME_burst_gate_end(data)                      (0x000000FF&(data))
#define TVD_BURST_GATE_TIME_get_burst_gate_start(data)                ((0x0000FF00&(data))>>8)
#define TVD_BURST_GATE_TIME_get_burst_gate_end(data)                  (0x000000FF&(data))

#define TVD_HACTIVE_TIME                                              0x18019050
#define TVD_HACTIVE_TIME_reg_addr                                     "0xB8019050"
#define TVD_HACTIVE_TIME_reg                                          0xB8019050
#define TVD_HACTIVE_TIME_inst_addr                                    "0x0014"
#define TVD_HACTIVE_TIME_inst                                         0x0014
#define TVD_HACTIVE_TIME_hactive_start_shift                          (8)
#define TVD_HACTIVE_TIME_hactive_width_shift                          (0)
#define TVD_HACTIVE_TIME_hactive_start_mask                           (0x0000FF00)
#define TVD_HACTIVE_TIME_hactive_width_mask                           (0x000000FF)
#define TVD_HACTIVE_TIME_hactive_start(data)                          (0x0000FF00&((data)<<8))
#define TVD_HACTIVE_TIME_hactive_width(data)                          (0x000000FF&(data))
#define TVD_HACTIVE_TIME_get_hactive_start(data)                      ((0x0000FF00&(data))>>8)
#define TVD_HACTIVE_TIME_get_hactive_width(data)                      (0x000000FF&(data))

#define TVD_VACTIVE_TIME                                              0x18019054
#define TVD_VACTIVE_TIME_reg_addr                                     "0xB8019054"
#define TVD_VACTIVE_TIME_reg                                          0xB8019054
#define TVD_VACTIVE_TIME_inst_addr                                    "0x0015"
#define TVD_VACTIVE_TIME_inst                                         0x0015
#define TVD_VACTIVE_TIME_vactive_start_shift                          (8)
#define TVD_VACTIVE_TIME_vactive_height_shift                         (0)
#define TVD_VACTIVE_TIME_vactive_start_mask                           (0x0000FF00)
#define TVD_VACTIVE_TIME_vactive_height_mask                          (0x000000FF)
#define TVD_VACTIVE_TIME_vactive_start(data)                          (0x0000FF00&((data)<<8))
#define TVD_VACTIVE_TIME_vactive_height(data)                         (0x000000FF&(data))
#define TVD_VACTIVE_TIME_get_vactive_start(data)                      ((0x0000FF00&(data))>>8)
#define TVD_VACTIVE_TIME_get_vactive_height(data)                     (0x000000FF&(data))

#define TVD_VSYNC_H_LOCKOUT                                           0x18019058
#define TVD_VSYNC_H_LOCKOUT_reg_addr                                  "0xB8019058"
#define TVD_VSYNC_H_LOCKOUT_reg                                       0xB8019058
#define TVD_VSYNC_H_LOCKOUT_inst_addr                                 "0x0016"
#define TVD_VSYNC_H_LOCKOUT_inst                                      0x0016
#define TVD_VSYNC_H_LOCKOUT_vsync_h_min_shift                         (7)
#define TVD_VSYNC_H_LOCKOUT_vsync_h_max_shift                         (0)
#define TVD_VSYNC_H_LOCKOUT_vsync_h_min_mask                          (0x00003F80)
#define TVD_VSYNC_H_LOCKOUT_vsync_h_max_mask                          (0x0000007F)
#define TVD_VSYNC_H_LOCKOUT_vsync_h_min(data)                         (0x00003F80&((data)<<7))
#define TVD_VSYNC_H_LOCKOUT_vsync_h_max(data)                         (0x0000007F&(data))
#define TVD_VSYNC_H_LOCKOUT_get_vsync_h_min(data)                     ((0x00003F80&(data))>>7)
#define TVD_VSYNC_H_LOCKOUT_get_vsync_h_max(data)                     (0x0000007F&(data))

#define TVD_VSYNC_AGC_LOCKOUT                                         0x1801905C
#define TVD_VSYNC_AGC_LOCKOUT_reg_addr                                "0xB801905C"
#define TVD_VSYNC_AGC_LOCKOUT_reg                                     0xB801905C
#define TVD_VSYNC_AGC_LOCKOUT_inst_addr                               "0x0017"
#define TVD_VSYNC_AGC_LOCKOUT_inst                                    0x0017
#define TVD_VSYNC_AGC_LOCKOUT_vsync_clamp_mode_shift                  (13)
#define TVD_VSYNC_AGC_LOCKOUT_vsync_agc_min_shift                     (6)
#define TVD_VSYNC_AGC_LOCKOUT_vsync_agc_max_shift                     (0)
#define TVD_VSYNC_AGC_LOCKOUT_vsync_clamp_mode_mask                   (0x00006000)
#define TVD_VSYNC_AGC_LOCKOUT_vsync_agc_min_mask                      (0x00001FC0)
#define TVD_VSYNC_AGC_LOCKOUT_vsync_agc_max_mask                      (0x0000003F)
#define TVD_VSYNC_AGC_LOCKOUT_vsync_clamp_mode(data)                  (0x00006000&((data)<<13))
#define TVD_VSYNC_AGC_LOCKOUT_vsync_agc_min(data)                     (0x00001FC0&((data)<<6))
#define TVD_VSYNC_AGC_LOCKOUT_vsync_agc_max(data)                     (0x0000003F&(data))
#define TVD_VSYNC_AGC_LOCKOUT_get_vsync_clamp_mode(data)              ((0x00006000&(data))>>13)
#define TVD_VSYNC_AGC_LOCKOUT_get_vsync_agc_min(data)                 ((0x00001FC0&(data))>>6)
#define TVD_VSYNC_AGC_LOCKOUT_get_vsync_agc_max(data)                 (0x0000003F&(data))

#define TVD_VSYNC_VBI_LOCKOUT                                         0x18019060
#define TVD_VSYNC_VBI_LOCKOUT_reg_addr                                "0xB8019060"
#define TVD_VSYNC_VBI_LOCKOUT_reg                                     0xB8019060
#define TVD_VSYNC_VBI_LOCKOUT_inst_addr                               "0x0018"
#define TVD_VSYNC_VBI_LOCKOUT_inst                                    0x0018
#define TVD_VSYNC_VBI_LOCKOUT_vlock_wide_range_shift                  (14)
#define TVD_VSYNC_VBI_LOCKOUT_vsync_vbi_min_shift                     (7)
#define TVD_VSYNC_VBI_LOCKOUT_vsync_vbi_max_shift                     (0)
#define TVD_VSYNC_VBI_LOCKOUT_vlock_wide_range_mask                   (0x00004000)
#define TVD_VSYNC_VBI_LOCKOUT_vsync_vbi_min_mask                      (0x00003F80)
#define TVD_VSYNC_VBI_LOCKOUT_vsync_vbi_max_mask                      (0x0000007F)
#define TVD_VSYNC_VBI_LOCKOUT_vlock_wide_range(data)                  (0x00004000&((data)<<14))
#define TVD_VSYNC_VBI_LOCKOUT_vsync_vbi_min(data)                     (0x00003F80&((data)<<7))
#define TVD_VSYNC_VBI_LOCKOUT_vsync_vbi_max(data)                     (0x0000007F&(data))
#define TVD_VSYNC_VBI_LOCKOUT_get_vlock_wide_range(data)              ((0x00004000&(data))>>14)
#define TVD_VSYNC_VBI_LOCKOUT_get_vsync_vbi_min(data)                 ((0x00003F80&(data))>>7)
#define TVD_VSYNC_VBI_LOCKOUT_get_vsync_vbi_max(data)                 (0x0000007F&(data))

#define TVD_VSYNC_CTRL                                                0x18019064
#define TVD_VSYNC_CTRL_reg_addr                                       "0xB8019064"
#define TVD_VSYNC_CTRL_reg                                            0xB8019064
#define TVD_VSYNC_CTRL_inst_addr                                      "0x0019"
#define TVD_VSYNC_CTRL_inst                                           0x0019
#define TVD_VSYNC_CTRL_write_enable8_shift                            (23)
#define TVD_VSYNC_CTRL_vsync_cntl_shift                               (21)
#define TVD_VSYNC_CTRL_write_enable7_shift                            (20)
#define TVD_VSYNC_CTRL_vsync_threshold_shift                          (14)
#define TVD_VSYNC_CTRL_write_enable6_shift                            (13)
#define TVD_VSYNC_CTRL_field_polarity_shift                           (12)
#define TVD_VSYNC_CTRL_write_enable5_shift                            (11)
#define TVD_VSYNC_CTRL_flip_field_shift                               (10)
#define TVD_VSYNC_CTRL_write_enable4_shift                            (9)
#define TVD_VSYNC_CTRL_veven_delayed_shift                            (8)
#define TVD_VSYNC_CTRL_write_enable3_shift                            (7)
#define TVD_VSYNC_CTRL_vodd_delayed_shift                             (6)
#define TVD_VSYNC_CTRL_write_enable2_shift                            (5)
#define TVD_VSYNC_CTRL_field_detect_mode_shift                        (3)
#define TVD_VSYNC_CTRL_write_enable1_shift                            (2)
#define TVD_VSYNC_CTRL_vloop_tc_shift                                 (0)
#define TVD_VSYNC_CTRL_write_enable8_mask                             (0x00800000)
#define TVD_VSYNC_CTRL_vsync_cntl_mask                                (0x00600000)
#define TVD_VSYNC_CTRL_write_enable7_mask                             (0x00100000)
#define TVD_VSYNC_CTRL_vsync_threshold_mask                           (0x000FC000)
#define TVD_VSYNC_CTRL_write_enable6_mask                             (0x00002000)
#define TVD_VSYNC_CTRL_field_polarity_mask                            (0x00001000)
#define TVD_VSYNC_CTRL_write_enable5_mask                             (0x00000800)
#define TVD_VSYNC_CTRL_flip_field_mask                                (0x00000400)
#define TVD_VSYNC_CTRL_write_enable4_mask                             (0x00000200)
#define TVD_VSYNC_CTRL_veven_delayed_mask                             (0x00000100)
#define TVD_VSYNC_CTRL_write_enable3_mask                             (0x00000080)
#define TVD_VSYNC_CTRL_vodd_delayed_mask                              (0x00000040)
#define TVD_VSYNC_CTRL_write_enable2_mask                             (0x00000020)
#define TVD_VSYNC_CTRL_field_detect_mode_mask                         (0x00000018)
#define TVD_VSYNC_CTRL_write_enable1_mask                             (0x00000004)
#define TVD_VSYNC_CTRL_vloop_tc_mask                                  (0x00000003)
#define TVD_VSYNC_CTRL_write_enable8(data)                            (0x00800000&((data)<<23))
#define TVD_VSYNC_CTRL_vsync_cntl(data)                               (0x00600000&((data)<<21))
#define TVD_VSYNC_CTRL_write_enable7(data)                            (0x00100000&((data)<<20))
#define TVD_VSYNC_CTRL_vsync_threshold(data)                          (0x000FC000&((data)<<14))
#define TVD_VSYNC_CTRL_write_enable6(data)                            (0x00002000&((data)<<13))
#define TVD_VSYNC_CTRL_field_polarity(data)                           (0x00001000&((data)<<12))
#define TVD_VSYNC_CTRL_write_enable5(data)                            (0x00000800&((data)<<11))
#define TVD_VSYNC_CTRL_flip_field(data)                               (0x00000400&((data)<<10))
#define TVD_VSYNC_CTRL_write_enable4(data)                            (0x00000200&((data)<<9))
#define TVD_VSYNC_CTRL_veven_delayed(data)                            (0x00000100&((data)<<8))
#define TVD_VSYNC_CTRL_write_enable3(data)                            (0x00000080&((data)<<7))
#define TVD_VSYNC_CTRL_vodd_delayed(data)                             (0x00000040&((data)<<6))
#define TVD_VSYNC_CTRL_write_enable2(data)                            (0x00000020&((data)<<5))
#define TVD_VSYNC_CTRL_field_detect_mode(data)                        (0x00000018&((data)<<3))
#define TVD_VSYNC_CTRL_write_enable1(data)                            (0x00000004&((data)<<2))
#define TVD_VSYNC_CTRL_vloop_tc(data)                                 (0x00000003&(data))
#define TVD_VSYNC_CTRL_get_write_enable8(data)                        ((0x00800000&(data))>>23)
#define TVD_VSYNC_CTRL_get_vsync_cntl(data)                           ((0x00600000&(data))>>21)
#define TVD_VSYNC_CTRL_get_write_enable7(data)                        ((0x00100000&(data))>>20)
#define TVD_VSYNC_CTRL_get_vsync_threshold(data)                      ((0x000FC000&(data))>>14)
#define TVD_VSYNC_CTRL_get_write_enable6(data)                        ((0x00002000&(data))>>13)
#define TVD_VSYNC_CTRL_get_field_polarity(data)                       ((0x00001000&(data))>>12)
#define TVD_VSYNC_CTRL_get_write_enable5(data)                        ((0x00000800&(data))>>11)
#define TVD_VSYNC_CTRL_get_flip_field(data)                           ((0x00000400&(data))>>10)
#define TVD_VSYNC_CTRL_get_write_enable4(data)                        ((0x00000200&(data))>>9)
#define TVD_VSYNC_CTRL_get_veven_delayed(data)                        ((0x00000100&(data))>>8)
#define TVD_VSYNC_CTRL_get_write_enable3(data)                        ((0x00000080&(data))>>7)
#define TVD_VSYNC_CTRL_get_vodd_delayed(data)                         ((0x00000040&(data))>>6)
#define TVD_VSYNC_CTRL_get_write_enable2(data)                        ((0x00000020&(data))>>5)
#define TVD_VSYNC_CTRL_get_field_detect_mode(data)                    ((0x00000018&(data))>>3)
#define TVD_VSYNC_CTRL_get_write_enable1(data)                        ((0x00000004&(data))>>2)
#define TVD_VSYNC_CTRL_get_vloop_tc(data)                             (0x00000003&(data))

#define TVD_STATUS1                                                   0x18019068
#define TVD_STATUS1_reg_addr                                          "0xB8019068"
#define TVD_STATUS1_reg                                               0xB8019068
#define TVD_STATUS1_inst_addr                                         "0x001A"
#define TVD_STATUS1_inst                                              0x001A
#define TVD_STATUS1_mv_colourstripes_shift                            (15)
#define TVD_STATUS1_mv_vbi_detected_shift                             (14)
#define TVD_STATUS1_chomalock_shift                                   (13)
#define TVD_STATUS1_vlock_shift                                       (12)
#define TVD_STATUS1_hlock_shift                                       (11)
#define TVD_STATUS1_no_signal_shift                                   (10)
#define TVD_STATUS1_palm_flag_shift                                   (9)
#define TVD_STATUS1_proscan_detected_shift                            (8)
#define TVD_STATUS1_vcr_rew_shift                                     (7)
#define TVD_STATUS1_vcr_ff_shift                                      (6)
#define TVD_STATUS1_vcr_trick_shift                                   (5)
#define TVD_STATUS1_vcr_shift                                         (4)
#define TVD_STATUS1_noisy_shift                                       (3)
#define TVD_STATUS1_625lines_detected_shift                           (2)
#define TVD_STATUS1_secam_detected_shift                              (1)
#define TVD_STATUS1_pal_detected_shift                                (0)
#define TVD_STATUS1_mv_colourstripes_mask                             (0x00038000)
#define TVD_STATUS1_mv_vbi_detected_mask                              (0x00004000)
#define TVD_STATUS1_chomalock_mask                                    (0x00002000)
#define TVD_STATUS1_vlock_mask                                        (0x00001000)
#define TVD_STATUS1_hlock_mask                                        (0x00000800)
#define TVD_STATUS1_no_signal_mask                                    (0x00000400)
#define TVD_STATUS1_palm_flag_mask                                    (0x00000200)
#define TVD_STATUS1_proscan_detected_mask                             (0x00000100)
#define TVD_STATUS1_vcr_rew_mask                                      (0x00000080)
#define TVD_STATUS1_vcr_ff_mask                                       (0x00000040)
#define TVD_STATUS1_vcr_trick_mask                                    (0x00000020)
#define TVD_STATUS1_vcr_mask                                          (0x00000010)
#define TVD_STATUS1_noisy_mask                                        (0x00000008)
#define TVD_STATUS1_625lines_detected_mask                            (0x00000004)
#define TVD_STATUS1_secam_detected_mask                               (0x00000002)
#define TVD_STATUS1_pal_detected_mask                                 (0x00000001)
#define TVD_STATUS1_mv_colourstripes(data)                            (0x00038000&((data)<<15))
#define TVD_STATUS1_mv_vbi_detected(data)                             (0x00004000&((data)<<14))
#define TVD_STATUS1_chomalock(data)                                   (0x00002000&((data)<<13))
#define TVD_STATUS1_vlock(data)                                       (0x00001000&((data)<<12))
#define TVD_STATUS1_hlock(data)                                       (0x00000800&((data)<<11))
#define TVD_STATUS1_no_signal(data)                                   (0x00000400&((data)<<10))
#define TVD_STATUS1_palm_flag(data)                                   (0x00000200&((data)<<9))
#define TVD_STATUS1_proscan_detected(data)                            (0x00000100&((data)<<8))
#define TVD_STATUS1_vcr_rew(data)                                     (0x00000080&((data)<<7))
#define TVD_STATUS1_vcr_ff(data)                                      (0x00000040&((data)<<6))
#define TVD_STATUS1_vcr_trick(data)                                   (0x00000020&((data)<<5))
#define TVD_STATUS1_vcr(data)                                         (0x00000010&((data)<<4))
#define TVD_STATUS1_noisy(data)                                       (0x00000008&((data)<<3))
#define TVD_STATUS1_625lines_detected(data)                           (0x00000004&((data)<<2))
#define TVD_STATUS1_secam_detected(data)                              (0x00000002&((data)<<1))
#define TVD_STATUS1_pal_detected(data)                                (0x00000001&(data))
#define TVD_STATUS1_get_mv_colourstripes(data)                        ((0x00038000&(data))>>15)
#define TVD_STATUS1_get_mv_vbi_detected(data)                         ((0x00004000&(data))>>14)
#define TVD_STATUS1_get_chomalock(data)                               ((0x00002000&(data))>>13)
#define TVD_STATUS1_get_vlock(data)                                   ((0x00001000&(data))>>12)
#define TVD_STATUS1_get_hlock(data)                                   ((0x00000800&(data))>>11)
#define TVD_STATUS1_get_no_signal(data)                               ((0x00000400&(data))>>10)
#define TVD_STATUS1_get_palm_flag(data)                               ((0x00000200&(data))>>9)
#define TVD_STATUS1_get_proscan_detected(data)                        ((0x00000100&(data))>>8)
#define TVD_STATUS1_get_vcr_rew(data)                                 ((0x00000080&(data))>>7)
#define TVD_STATUS1_get_vcr_ff(data)                                  ((0x00000040&(data))>>6)
#define TVD_STATUS1_get_vcr_trick(data)                               ((0x00000020&(data))>>5)
#define TVD_STATUS1_get_vcr(data)                                     ((0x00000010&(data))>>4)
#define TVD_STATUS1_get_noisy(data)                                   ((0x00000008&(data))>>3)
#define TVD_STATUS1_get_625lines_detected(data)                       ((0x00000004&(data))>>2)
#define TVD_STATUS1_get_secam_detected(data)                          ((0x00000002&(data))>>1)
#define TVD_STATUS1_get_pal_detected(data)                            (0x00000001&(data))

#define TVD_HDTO_STATUS                                               0x1801906C
#define TVD_HDTO_STATUS_reg_addr                                      "0xB801906C"
#define TVD_HDTO_STATUS_reg                                           0xB801906C
#define TVD_HDTO_STATUS_inst_addr                                     "0x001B"
#define TVD_HDTO_STATUS_inst                                          0x001B
#define TVD_HDTO_STATUS_status_hdto_inc_shift                         (0)
#define TVD_HDTO_STATUS_status_hdto_inc_mask                          (0x3FFFFFFF)
#define TVD_HDTO_STATUS_status_hdto_inc(data)                         (0x3FFFFFFF&(data))
#define TVD_HDTO_STATUS_get_status_hdto_inc(data)                     (0x3FFFFFFF&(data))

#define TVD_CDTO_STATUS                                               0x18019070
#define TVD_CDTO_STATUS_reg_addr                                      "0xB8019070"
#define TVD_CDTO_STATUS_reg                                           0xB8019070
#define TVD_CDTO_STATUS_inst_addr                                     "0x001C"
#define TVD_CDTO_STATUS_inst                                          0x001C
#define TVD_CDTO_STATUS_status_cdto_inc_shift                         (0)
#define TVD_CDTO_STATUS_status_cdto_inc_mask                          (0x3FFFFFFF)
#define TVD_CDTO_STATUS_status_cdto_inc(data)                         (0x3FFFFFFF&(data))
#define TVD_CDTO_STATUS_get_status_cdto_inc(data)                     (0x3FFFFFFF&(data))

#define TVD_CHROMA_STATUS                                             0x18019074
#define TVD_CHROMA_STATUS_reg_addr                                    "0xB8019074"
#define TVD_CHROMA_STATUS_reg                                         0xB8019074
#define TVD_CHROMA_STATUS_inst_addr                                   "0x001D"
#define TVD_CHROMA_STATUS_inst                                        0x001D
#define TVD_CHROMA_STATUS_status_cmag_shift                           (14)
#define TVD_CHROMA_STATUS_status_cgain_shift                          (0)
#define TVD_CHROMA_STATUS_status_cmag_mask                            (0x003FC000)
#define TVD_CHROMA_STATUS_status_cgain_mask                           (0x00003FFF)
#define TVD_CHROMA_STATUS_status_cmag(data)                           (0x003FC000&((data)<<14))
#define TVD_CHROMA_STATUS_status_cgain(data)                          (0x00003FFF&(data))
#define TVD_CHROMA_STATUS_get_status_cmag(data)                       ((0x003FC000&(data))>>14)
#define TVD_CHROMA_STATUS_get_status_cgain(data)                      (0x00003FFF&(data))

#define TVD_STATUS2                                                   0x18019078
#define TVD_STATUS2_reg_addr                                          "0xB8019078"
#define TVD_STATUS2_reg                                               0xB8019078
#define TVD_STATUS2_inst_addr                                         "0x001E"
#define TVD_STATUS2_inst                                              0x001E
#define TVD_STATUS2_status_agc_dgain_shift                            (16)
#define TVD_STATUS2_status_cordiq_freq_shift                          (8)
#define TVD_STATUS2_status_noise_shift                                (0)
#define TVD_STATUS2_status_agc_dgain_mask                             (0x00FF0000)
#define TVD_STATUS2_status_cordiq_freq_mask                           (0x0000FF00)
#define TVD_STATUS2_status_noise_mask                                 (0x000000FF)
#define TVD_STATUS2_status_agc_dgain(data)                            (0x00FF0000&((data)<<16))
#define TVD_STATUS2_status_cordiq_freq(data)                          (0x0000FF00&((data)<<8))
#define TVD_STATUS2_status_noise(data)                                (0x000000FF&(data))
#define TVD_STATUS2_get_status_agc_dgain(data)                        ((0x00FF0000&(data))>>16)
#define TVD_STATUS2_get_status_cordiq_freq(data)                      ((0x0000FF00&(data))>>8)
#define TVD_STATUS2_get_status_noise(data)                            (0x000000FF&(data))

#define TVD_PEAKING                                                   0x1801907C
#define TVD_PEAKING_reg_addr                                          "0xB801907C"
#define TVD_PEAKING_reg                                               0xB801907C
#define TVD_PEAKING_inst_addr                                         "0x001F"
#define TVD_PEAKING_inst                                              0x001F
#define TVD_PEAKING_write_enable3_shift                               (8)
#define TVD_PEAKING_peak_range_shift                                  (6)
#define TVD_PEAKING_write_enable2_shift                               (5)
#define TVD_PEAKING_peak_gain_shift                                   (2)
#define TVD_PEAKING_write_enable1_shift                               (1)
#define TVD_PEAKING_peak_en_shift                                     (0)
#define TVD_PEAKING_write_enable3_mask                                (0x00000100)
#define TVD_PEAKING_peak_range_mask                                   (0x000000C0)
#define TVD_PEAKING_write_enable2_mask                                (0x00000020)
#define TVD_PEAKING_peak_gain_mask                                    (0x0000001C)
#define TVD_PEAKING_write_enable1_mask                                (0x00000002)
#define TVD_PEAKING_peak_en_mask                                      (0x00000001)
#define TVD_PEAKING_write_enable3(data)                               (0x00000100&((data)<<8))
#define TVD_PEAKING_peak_range(data)                                  (0x000000C0&((data)<<6))
#define TVD_PEAKING_write_enable2(data)                               (0x00000020&((data)<<5))
#define TVD_PEAKING_peak_gain(data)                                   (0x0000001C&((data)<<2))
#define TVD_PEAKING_write_enable1(data)                               (0x00000002&((data)<<1))
#define TVD_PEAKING_peak_en(data)                                     (0x00000001&(data))
#define TVD_PEAKING_get_write_enable3(data)                           ((0x00000100&(data))>>8)
#define TVD_PEAKING_get_peak_range(data)                              ((0x000000C0&(data))>>6)
#define TVD_PEAKING_get_write_enable2(data)                           ((0x00000020&(data))>>5)
#define TVD_PEAKING_get_peak_gain(data)                               ((0x0000001C&(data))>>2)
#define TVD_PEAKING_get_write_enable1(data)                           ((0x00000002&(data))>>1)
#define TVD_PEAKING_get_peak_en(data)                                 (0x00000001&(data))

#define TVD_COMB_CONFIG                                               0x18019080
#define TVD_COMB_CONFIG_reg_addr                                      "0xB8019080"
#define TVD_COMB_CONFIG_reg                                           0xB8019080
#define TVD_COMB_CONFIG_inst_addr                                     "0x0020"
#define TVD_COMB_CONFIG_inst                                          0x0020
#define TVD_COMB_CONFIG_write_enable4_shift                           (8)
#define TVD_COMB_CONFIG_pal_perr_shift                                (7)
#define TVD_COMB_CONFIG_write_enable3_shift                           (6)
#define TVD_COMB_CONFIG_pal_perr_auto_en_shift                        (5)
#define TVD_COMB_CONFIG_write_enable2_shift                           (4)
#define TVD_COMB_CONFIG_comb_wide_band_shift                          (3)
#define TVD_COMB_CONFIG_write_enable1_shift                           (2)
#define TVD_COMB_CONFIG_palsw_level_shift                             (0)
#define TVD_COMB_CONFIG_write_enable4_mask                            (0x00000100)
#define TVD_COMB_CONFIG_pal_perr_mask                                 (0x00000080)
#define TVD_COMB_CONFIG_write_enable3_mask                            (0x00000040)
#define TVD_COMB_CONFIG_pal_perr_auto_en_mask                         (0x00000020)
#define TVD_COMB_CONFIG_write_enable2_mask                            (0x00000010)
#define TVD_COMB_CONFIG_comb_wide_band_mask                           (0x00000008)
#define TVD_COMB_CONFIG_write_enable1_mask                            (0x00000004)
#define TVD_COMB_CONFIG_palsw_level_mask                              (0x00000003)
#define TVD_COMB_CONFIG_write_enable4(data)                           (0x00000100&((data)<<8))
#define TVD_COMB_CONFIG_pal_perr(data)                                (0x00000080&((data)<<7))
#define TVD_COMB_CONFIG_write_enable3(data)                           (0x00000040&((data)<<6))
#define TVD_COMB_CONFIG_pal_perr_auto_en(data)                        (0x00000020&((data)<<5))
#define TVD_COMB_CONFIG_write_enable2(data)                           (0x00000010&((data)<<4))
#define TVD_COMB_CONFIG_comb_wide_band(data)                          (0x00000008&((data)<<3))
#define TVD_COMB_CONFIG_write_enable1(data)                           (0x00000004&((data)<<2))
#define TVD_COMB_CONFIG_palsw_level(data)                             (0x00000003&(data))
#define TVD_COMB_CONFIG_get_write_enable4(data)                       ((0x00000100&(data))>>8)
#define TVD_COMB_CONFIG_get_pal_perr(data)                            ((0x00000080&(data))>>7)
#define TVD_COMB_CONFIG_get_write_enable3(data)                       ((0x00000040&(data))>>6)
#define TVD_COMB_CONFIG_get_pal_perr_auto_en(data)                    ((0x00000020&(data))>>5)
#define TVD_COMB_CONFIG_get_write_enable2(data)                       ((0x00000010&(data))>>4)
#define TVD_COMB_CONFIG_get_comb_wide_band(data)                      ((0x00000008&(data))>>3)
#define TVD_COMB_CONFIG_get_write_enable1(data)                       ((0x00000004&(data))>>2)
#define TVD_COMB_CONFIG_get_palsw_level(data)                         (0x00000003&(data))

#define TVD_CHROMA_LOCK                                               0x18019084
#define TVD_CHROMA_LOCK_reg_addr                                      "0xB8019084"
#define TVD_CHROMA_LOCK_reg                                           0xB8019084
#define TVD_CHROMA_LOCK_inst_addr                                     "0x0021"
#define TVD_CHROMA_LOCK_inst                                          0x0021
#define TVD_CHROMA_LOCK_write_enable3_shift                           (10)
#define TVD_CHROMA_LOCK_lose_chromalock_count_shift                   (6)
#define TVD_CHROMA_LOCK_write_enable2_shift                           (5)
#define TVD_CHROMA_LOCK_lose_chromalock_level_shift                   (2)
#define TVD_CHROMA_LOCK_write_enable1_shift                           (1)
#define TVD_CHROMA_LOCK_lose_chromalock_ckill_shift                   (0)
#define TVD_CHROMA_LOCK_write_enable3_mask                            (0x00000400)
#define TVD_CHROMA_LOCK_lose_chromalock_count_mask                    (0x000003C0)
#define TVD_CHROMA_LOCK_write_enable2_mask                            (0x00000020)
#define TVD_CHROMA_LOCK_lose_chromalock_level_mask                    (0x0000001C)
#define TVD_CHROMA_LOCK_write_enable1_mask                            (0x00000002)
#define TVD_CHROMA_LOCK_lose_chromalock_ckill_mask                    (0x00000001)
#define TVD_CHROMA_LOCK_write_enable3(data)                           (0x00000400&((data)<<10))
#define TVD_CHROMA_LOCK_lose_chromalock_count(data)                   (0x000003C0&((data)<<6))
#define TVD_CHROMA_LOCK_write_enable2(data)                           (0x00000020&((data)<<5))
#define TVD_CHROMA_LOCK_lose_chromalock_level(data)                   (0x0000001C&((data)<<2))
#define TVD_CHROMA_LOCK_write_enable1(data)                           (0x00000002&((data)<<1))
#define TVD_CHROMA_LOCK_lose_chromalock_ckill(data)                   (0x00000001&(data))
#define TVD_CHROMA_LOCK_get_write_enable3(data)                       ((0x00000400&(data))>>10)
#define TVD_CHROMA_LOCK_get_lose_chromalock_count(data)               ((0x000003C0&(data))>>6)
#define TVD_CHROMA_LOCK_get_write_enable2(data)                       ((0x00000020&(data))>>5)
#define TVD_CHROMA_LOCK_get_lose_chromalock_level(data)               ((0x0000001C&(data))>>2)
#define TVD_CHROMA_LOCK_get_write_enable1(data)                       ((0x00000002&(data))>>1)
#define TVD_CHROMA_LOCK_get_lose_chromalock_ckill(data)               (0x00000001&(data))

#define TVD_COMB_THD                                                  0x18019088
#define TVD_COMB_THD_reg_addr                                         "0xB8019088"
#define TVD_COMB_THD_reg                                              0xB8019088
#define TVD_COMB_THD_inst_addr                                        "0x0022"
#define TVD_COMB_THD_inst                                             0x0022
#define TVD_COMB_THD_noise_ntsc_c_shift                               (24)
#define TVD_COMB_THD_noise_pal_c_shift                                (16)
#define TVD_COMB_THD_noise_phase_c_shift                              (8)
#define TVD_COMB_THD_noise_phase_y_shift                              (0)
#define TVD_COMB_THD_noise_ntsc_c_mask                                (0xFF000000)
#define TVD_COMB_THD_noise_pal_c_mask                                 (0x00FF0000)
#define TVD_COMB_THD_noise_phase_c_mask                               (0x0000FF00)
#define TVD_COMB_THD_noise_phase_y_mask                               (0x000000FF)
#define TVD_COMB_THD_noise_ntsc_c(data)                               (0xFF000000&((data)<<24))
#define TVD_COMB_THD_noise_pal_c(data)                                (0x00FF0000&((data)<<16))
#define TVD_COMB_THD_noise_phase_c(data)                              (0x0000FF00&((data)<<8))
#define TVD_COMB_THD_noise_phase_y(data)                              (0x000000FF&(data))
#define TVD_COMB_THD_get_noise_ntsc_c(data)                           ((0xFF000000&(data))>>24)
#define TVD_COMB_THD_get_noise_pal_c(data)                            ((0x00FF0000&(data))>>16)
#define TVD_COMB_THD_get_noise_phase_c(data)                          ((0x0000FF00&(data))>>8)
#define TVD_COMB_THD_get_noise_phase_y(data)                          (0x000000FF&(data))

#define TVD_CHROMA_LPFILTER                                           0x1801908C
#define TVD_CHROMA_LPFILTER_reg_addr                                  "0xB801908C"
#define TVD_CHROMA_LPFILTER_reg                                       0xB801908C
#define TVD_CHROMA_LPFILTER_inst_addr                                 "0x0023"
#define TVD_CHROMA_LPFILTER_inst                                      0x0023
#define TVD_CHROMA_LPFILTER_cstate_shift                              (1)
#define TVD_CHROMA_LPFILTER_fixed_cstat_shift                         (0)
#define TVD_CHROMA_LPFILTER_cstate_mask                               (0x0000000E)
#define TVD_CHROMA_LPFILTER_fixed_cstat_mask                          (0x00000001)
#define TVD_CHROMA_LPFILTER_cstate(data)                              (0x0000000E&((data)<<1))
#define TVD_CHROMA_LPFILTER_fixed_cstat(data)                         (0x00000001&(data))
#define TVD_CHROMA_LPFILTER_get_cstate(data)                          ((0x0000000E&(data))>>1)
#define TVD_CHROMA_LPFILTER_get_fixed_cstat(data)                     (0x00000001&(data))

#define TVD_HRESAMPLE                                                 0x18019090
#define TVD_HRESAMPLE_reg_addr                                        "0xB8019090"
#define TVD_HRESAMPLE_reg                                             0xB8019090
#define TVD_HRESAMPLE_inst_addr                                       "0x0024"
#define TVD_HRESAMPLE_inst                                            0x0024
#define TVD_HRESAMPLE_hresampler_2up_shift                            (0)
#define TVD_HRESAMPLE_hresampler_2up_mask                             (0x00000001)
#define TVD_HRESAMPLE_hresampler_2up(data)                            (0x00000001&(data))
#define TVD_HRESAMPLE_get_hresampler_2up(data)                        (0x00000001&(data))

#define TVD_CHG_PUMP_DLY                                              0x18019094
#define TVD_CHG_PUMP_DLY_reg_addr                                     "0xB8019094"
#define TVD_CHG_PUMP_DLY_reg                                          0xB8019094
#define TVD_CHG_PUMP_DLY_inst_addr                                    "0x0025"
#define TVD_CHG_PUMP_DLY_inst                                         0x0025
#define TVD_CHG_PUMP_DLY_write_enable5_shift                          (28)
#define TVD_CHG_PUMP_DLY_cpump_adjust_delay_shift                     (22)
#define TVD_CHG_PUMP_DLY_write_enable4_shift                          (21)
#define TVD_CHG_PUMP_DLY_cpump_adjust_polarity_shift                  (20)
#define TVD_CHG_PUMP_DLY_write_enable3_shift                          (19)
#define TVD_CHG_PUMP_DLY_cpump_delay_en_shift                         (18)
#define TVD_CHG_PUMP_DLY_write_enable2_shift                          (17)
#define TVD_CHG_PUMP_DLY_cpump_adjust_shift                           (9)
#define TVD_CHG_PUMP_DLY_write_enable1_shift                          (8)
#define TVD_CHG_PUMP_DLY_cpump_delay_shift                            (0)
#define TVD_CHG_PUMP_DLY_write_enable5_mask                           (0x10000000)
#define TVD_CHG_PUMP_DLY_cpump_adjust_delay_mask                      (0x0FC00000)
#define TVD_CHG_PUMP_DLY_write_enable4_mask                           (0x00200000)
#define TVD_CHG_PUMP_DLY_cpump_adjust_polarity_mask                   (0x00100000)
#define TVD_CHG_PUMP_DLY_write_enable3_mask                           (0x00080000)
#define TVD_CHG_PUMP_DLY_cpump_delay_en_mask                          (0x00040000)
#define TVD_CHG_PUMP_DLY_write_enable2_mask                           (0x00020000)
#define TVD_CHG_PUMP_DLY_cpump_adjust_mask                            (0x0001FE00)
#define TVD_CHG_PUMP_DLY_write_enable1_mask                           (0x00000100)
#define TVD_CHG_PUMP_DLY_cpump_delay_mask                             (0x000000FF)
#define TVD_CHG_PUMP_DLY_write_enable5(data)                          (0x10000000&((data)<<28))
#define TVD_CHG_PUMP_DLY_cpump_adjust_delay(data)                     (0x0FC00000&((data)<<22))
#define TVD_CHG_PUMP_DLY_write_enable4(data)                          (0x00200000&((data)<<21))
#define TVD_CHG_PUMP_DLY_cpump_adjust_polarity(data)                  (0x00100000&((data)<<20))
#define TVD_CHG_PUMP_DLY_write_enable3(data)                          (0x00080000&((data)<<19))
#define TVD_CHG_PUMP_DLY_cpump_delay_en(data)                         (0x00040000&((data)<<18))
#define TVD_CHG_PUMP_DLY_write_enable2(data)                          (0x00020000&((data)<<17))
#define TVD_CHG_PUMP_DLY_cpump_adjust(data)                           (0x0001FE00&((data)<<9))
#define TVD_CHG_PUMP_DLY_write_enable1(data)                          (0x00000100&((data)<<8))
#define TVD_CHG_PUMP_DLY_cpump_delay(data)                            (0x000000FF&(data))
#define TVD_CHG_PUMP_DLY_get_write_enable5(data)                      ((0x10000000&(data))>>28)
#define TVD_CHG_PUMP_DLY_get_cpump_adjust_delay(data)                 ((0x0FC00000&(data))>>22)
#define TVD_CHG_PUMP_DLY_get_write_enable4(data)                      ((0x00200000&(data))>>21)
#define TVD_CHG_PUMP_DLY_get_cpump_adjust_polarity(data)              ((0x00100000&(data))>>20)
#define TVD_CHG_PUMP_DLY_get_write_enable3(data)                      ((0x00080000&(data))>>19)
#define TVD_CHG_PUMP_DLY_get_cpump_delay_en(data)                     ((0x00040000&(data))>>18)
#define TVD_CHG_PUMP_DLY_get_write_enable2(data)                      ((0x00020000&(data))>>17)
#define TVD_CHG_PUMP_DLY_get_cpump_adjust(data)                       ((0x0001FE00&(data))>>9)
#define TVD_CHG_PUMP_DLY_get_write_enable1(data)                      ((0x00000100&(data))>>8)
#define TVD_CHG_PUMP_DLY_get_cpump_delay(data)                        (0x000000FF&(data))

#define TVD_3DYC_SEP_CTRL                                             0x18019098
#define TVD_3DYC_SEP_CTRL_reg_addr                                    "0xB8019098"
#define TVD_3DYC_SEP_CTRL_reg                                         0xB8019098
#define TVD_3DYC_SEP_CTRL_inst_addr                                   "0x0026"
#define TVD_3DYC_SEP_CTRL_inst                                        0x0026
#define TVD_3DYC_SEP_CTRL_write_enable11_shift                        (29)
#define TVD_3DYC_SEP_CTRL_debug_mode_shift                            (28)
#define TVD_3DYC_SEP_CTRL_write_enable10_shift                        (27)
#define TVD_3DYC_SEP_CTRL_debug_enable_shift                          (26)
#define TVD_3DYC_SEP_CTRL_write_enable9_shift                         (25)
#define TVD_3DYC_SEP_CTRL_memory_size_shift                           (23)
#define TVD_3DYC_SEP_CTRL_write_enable8_shift                         (22)
#define TVD_3DYC_SEP_CTRL_ntscpal_select_shift                        (21)
#define TVD_3DYC_SEP_CTRL_write_enable7_shift                         (20)
#define TVD_3DYC_SEP_CTRL_yc_separation_control_shift                 (17)
#define TVD_3DYC_SEP_CTRL_write_enable6_shift                         (16)
#define TVD_3DYC_SEP_CTRL_chroma_vlpf_en_shift                        (15)
#define TVD_3DYC_SEP_CTRL_write_enable5_shift                         (14)
#define TVD_3DYC_SEP_CTRL_bpf_bw_sel_shift                            (11)
#define TVD_3DYC_SEP_CTRL_write_enable4_shift                         (10)
#define TVD_3DYC_SEP_CTRL_vcr3d2d_shift                               (9)
#define TVD_3DYC_SEP_CTRL_write_enable3_shift                         (8)
#define TVD_3DYC_SEP_CTRL_noisy3d2d_shift                             (7)
#define TVD_3DYC_SEP_CTRL_write_enable2_shift                         (6)
#define TVD_3DYC_SEP_CTRL_field_toggle_en_shift                       (5)
#define TVD_3DYC_SEP_CTRL_write_enable1_shift                         (4)
#define TVD_3DYC_SEP_CTRL_debug_tree_monitor_shift                    (0)
#define TVD_3DYC_SEP_CTRL_write_enable11_mask                         (0x20000000)
#define TVD_3DYC_SEP_CTRL_debug_mode_mask                             (0x10000000)
#define TVD_3DYC_SEP_CTRL_write_enable10_mask                         (0x08000000)
#define TVD_3DYC_SEP_CTRL_debug_enable_mask                           (0x04000000)
#define TVD_3DYC_SEP_CTRL_write_enable9_mask                          (0x02000000)
#define TVD_3DYC_SEP_CTRL_memory_size_mask                            (0x01800000)
#define TVD_3DYC_SEP_CTRL_write_enable8_mask                          (0x00400000)
#define TVD_3DYC_SEP_CTRL_ntscpal_select_mask                         (0x00200000)
#define TVD_3DYC_SEP_CTRL_write_enable7_mask                          (0x00100000)
#define TVD_3DYC_SEP_CTRL_yc_separation_control_mask                  (0x000E0000)
#define TVD_3DYC_SEP_CTRL_write_enable6_mask                          (0x00010000)
#define TVD_3DYC_SEP_CTRL_chroma_vlpf_en_mask                         (0x00008000)
#define TVD_3DYC_SEP_CTRL_write_enable5_mask                          (0x00004000)
#define TVD_3DYC_SEP_CTRL_bpf_bw_sel_mask                             (0x00003800)
#define TVD_3DYC_SEP_CTRL_write_enable4_mask                          (0x00000400)
#define TVD_3DYC_SEP_CTRL_vcr3d2d_mask                                (0x00000200)
#define TVD_3DYC_SEP_CTRL_write_enable3_mask                          (0x00000100)
#define TVD_3DYC_SEP_CTRL_noisy3d2d_mask                              (0x00000080)
#define TVD_3DYC_SEP_CTRL_write_enable2_mask                          (0x00000040)
#define TVD_3DYC_SEP_CTRL_field_toggle_en_mask                        (0x00000020)
#define TVD_3DYC_SEP_CTRL_write_enable1_mask                          (0x00000010)
#define TVD_3DYC_SEP_CTRL_debug_tree_monitor_mask                     (0x0000000F)
#define TVD_3DYC_SEP_CTRL_write_enable11(data)                        (0x20000000&((data)<<29))
#define TVD_3DYC_SEP_CTRL_debug_mode(data)                            (0x10000000&((data)<<28))
#define TVD_3DYC_SEP_CTRL_write_enable10(data)                        (0x08000000&((data)<<27))
#define TVD_3DYC_SEP_CTRL_debug_enable(data)                          (0x04000000&((data)<<26))
#define TVD_3DYC_SEP_CTRL_write_enable9(data)                         (0x02000000&((data)<<25))
#define TVD_3DYC_SEP_CTRL_memory_size(data)                           (0x01800000&((data)<<23))
#define TVD_3DYC_SEP_CTRL_write_enable8(data)                         (0x00400000&((data)<<22))
#define TVD_3DYC_SEP_CTRL_ntscpal_select(data)                        (0x00200000&((data)<<21))
#define TVD_3DYC_SEP_CTRL_write_enable7(data)                         (0x00100000&((data)<<20))
#define TVD_3DYC_SEP_CTRL_yc_separation_control(data)                 (0x000E0000&((data)<<17))
#define TVD_3DYC_SEP_CTRL_write_enable6(data)                         (0x00010000&((data)<<16))
#define TVD_3DYC_SEP_CTRL_chroma_vlpf_en(data)                        (0x00008000&((data)<<15))
#define TVD_3DYC_SEP_CTRL_write_enable5(data)                         (0x00004000&((data)<<14))
#define TVD_3DYC_SEP_CTRL_bpf_bw_sel(data)                            (0x00003800&((data)<<11))
#define TVD_3DYC_SEP_CTRL_write_enable4(data)                         (0x00000400&((data)<<10))
#define TVD_3DYC_SEP_CTRL_vcr3d2d(data)                               (0x00000200&((data)<<9))
#define TVD_3DYC_SEP_CTRL_write_enable3(data)                         (0x00000100&((data)<<8))
#define TVD_3DYC_SEP_CTRL_noisy3d2d(data)                             (0x00000080&((data)<<7))
#define TVD_3DYC_SEP_CTRL_write_enable2(data)                         (0x00000040&((data)<<6))
#define TVD_3DYC_SEP_CTRL_field_toggle_en(data)                       (0x00000020&((data)<<5))
#define TVD_3DYC_SEP_CTRL_write_enable1(data)                         (0x00000010&((data)<<4))
#define TVD_3DYC_SEP_CTRL_debug_tree_monitor(data)                    (0x0000000F&(data))
#define TVD_3DYC_SEP_CTRL_get_write_enable11(data)                    ((0x20000000&(data))>>29)
#define TVD_3DYC_SEP_CTRL_get_debug_mode(data)                        ((0x10000000&(data))>>28)
#define TVD_3DYC_SEP_CTRL_get_write_enable10(data)                    ((0x08000000&(data))>>27)
#define TVD_3DYC_SEP_CTRL_get_debug_enable(data)                      ((0x04000000&(data))>>26)
#define TVD_3DYC_SEP_CTRL_get_write_enable9(data)                     ((0x02000000&(data))>>25)
#define TVD_3DYC_SEP_CTRL_get_memory_size(data)                       ((0x01800000&(data))>>23)
#define TVD_3DYC_SEP_CTRL_get_write_enable8(data)                     ((0x00400000&(data))>>22)
#define TVD_3DYC_SEP_CTRL_get_ntscpal_select(data)                    ((0x00200000&(data))>>21)
#define TVD_3DYC_SEP_CTRL_get_write_enable7(data)                     ((0x00100000&(data))>>20)
#define TVD_3DYC_SEP_CTRL_get_yc_separation_control(data)             ((0x000E0000&(data))>>17)
#define TVD_3DYC_SEP_CTRL_get_write_enable6(data)                     ((0x00010000&(data))>>16)
#define TVD_3DYC_SEP_CTRL_get_chroma_vlpf_en(data)                    ((0x00008000&(data))>>15)
#define TVD_3DYC_SEP_CTRL_get_write_enable5(data)                     ((0x00004000&(data))>>14)
#define TVD_3DYC_SEP_CTRL_get_bpf_bw_sel(data)                        ((0x00003800&(data))>>11)
#define TVD_3DYC_SEP_CTRL_get_write_enable4(data)                     ((0x00000400&(data))>>10)
#define TVD_3DYC_SEP_CTRL_get_vcr3d2d(data)                           ((0x00000200&(data))>>9)
#define TVD_3DYC_SEP_CTRL_get_write_enable3(data)                     ((0x00000100&(data))>>8)
#define TVD_3DYC_SEP_CTRL_get_noisy3d2d(data)                         ((0x00000080&(data))>>7)
#define TVD_3DYC_SEP_CTRL_get_write_enable2(data)                     ((0x00000040&(data))>>6)
#define TVD_3DYC_SEP_CTRL_get_field_toggle_en(data)                   ((0x00000020&(data))>>5)
#define TVD_3DYC_SEP_CTRL_get_write_enable1(data)                     ((0x00000010&(data))>>4)
#define TVD_3DYC_SEP_CTRL_get_debug_tree_monitor(data)                (0x0000000F&(data))

#define TVD_3DTHD1                                                    0x1801909C
#define TVD_3DTHD1_reg_addr                                           "0xB801909C"
#define TVD_3DTHD1_reg                                                0xB801909C
#define TVD_3DTHD1_inst_addr                                          "0x0027"
#define TVD_3DTHD1_inst                                               0x0027
#define TVD_3DTHD1_md_y_lo_diff_thresh1_shift                         (23)
#define TVD_3DTHD1_check_mdt_en_shift                                 (22)
#define TVD_3DTHD1_md_y_lo_diff_thresh2_shift                         (16)
#define TVD_3DTHD1_md_mesh_det_thresh1_shift                          (12)
#define TVD_3DTHD1_md_mesh_c_large_thresh_shift                       (8)
#define TVD_3DTHD1_md_frame_close_chk_enable_shift                    (7)
#define TVD_3DTHD1_md_mesh_det_thresh2_shift                          (3)
#define TVD_3DTHD1_md_mesh_det_cnt_thresh_shift                       (0)
#define TVD_3DTHD1_md_y_lo_diff_thresh1_mask                          (0x07800000)
#define TVD_3DTHD1_check_mdt_en_mask                                  (0x00400000)
#define TVD_3DTHD1_md_y_lo_diff_thresh2_mask                          (0x003F0000)
#define TVD_3DTHD1_md_mesh_det_thresh1_mask                           (0x0000F000)
#define TVD_3DTHD1_md_mesh_c_large_thresh_mask                        (0x00000F00)
#define TVD_3DTHD1_md_frame_close_chk_enable_mask                     (0x00000080)
#define TVD_3DTHD1_md_mesh_det_thresh2_mask                           (0x00000078)
#define TVD_3DTHD1_md_mesh_det_cnt_thresh_mask                        (0x00000007)
#define TVD_3DTHD1_md_y_lo_diff_thresh1(data)                         (0x07800000&((data)<<23))
#define TVD_3DTHD1_check_mdt_en(data)                                 (0x00400000&((data)<<22))
#define TVD_3DTHD1_md_y_lo_diff_thresh2(data)                         (0x003F0000&((data)<<16))
#define TVD_3DTHD1_md_mesh_det_thresh1(data)                          (0x0000F000&((data)<<12))
#define TVD_3DTHD1_md_mesh_c_large_thresh(data)                       (0x00000F00&((data)<<8))
#define TVD_3DTHD1_md_frame_close_chk_enable(data)                    (0x00000080&((data)<<7))
#define TVD_3DTHD1_md_mesh_det_thresh2(data)                          (0x00000078&((data)<<3))
#define TVD_3DTHD1_md_mesh_det_cnt_thresh(data)                       (0x00000007&(data))
#define TVD_3DTHD1_get_md_y_lo_diff_thresh1(data)                     ((0x07800000&(data))>>23)
#define TVD_3DTHD1_get_check_mdt_en(data)                             ((0x00400000&(data))>>22)
#define TVD_3DTHD1_get_md_y_lo_diff_thresh2(data)                     ((0x003F0000&(data))>>16)
#define TVD_3DTHD1_get_md_mesh_det_thresh1(data)                      ((0x0000F000&(data))>>12)
#define TVD_3DTHD1_get_md_mesh_c_large_thresh(data)                   ((0x00000F00&(data))>>8)
#define TVD_3DTHD1_get_md_frame_close_chk_enable(data)                ((0x00000080&(data))>>7)
#define TVD_3DTHD1_get_md_mesh_det_thresh2(data)                      ((0x00000078&(data))>>3)
#define TVD_3DTHD1_get_md_mesh_det_cnt_thresh(data)                   (0x00000007&(data))

#define TVD_3DTHD2                                                    0x180190A0
#define TVD_3DTHD2_reg_addr                                           "0xB80190A0"
#define TVD_3DTHD2_reg                                                0xB80190A0
#define TVD_3DTHD2_inst_addr                                          "0x0028"
#define TVD_3DTHD2_inst                                               0x0028
#define TVD_3DTHD2_md_chk_mesh_thresh_shift                           (17)
#define TVD_3DTHD2_md_y_lo_line_diff_thresh_shift                     (13)
#define TVD_3DTHD2_md_chk_three_line_c_thresh1_shift                  (10)
#define TVD_3DTHD2_md_c_detect_thresh_shift                           (6)
#define TVD_3DTHD2_md_orig_diff_thresh_shift                          (0)
#define TVD_3DTHD2_md_chk_mesh_thresh_mask                            (0x00060000)
#define TVD_3DTHD2_md_y_lo_line_diff_thresh_mask                      (0x0001E000)
#define TVD_3DTHD2_md_chk_three_line_c_thresh1_mask                   (0x00001C00)
#define TVD_3DTHD2_md_c_detect_thresh_mask                            (0x000003C0)
#define TVD_3DTHD2_md_orig_diff_thresh_mask                           (0x0000003F)
#define TVD_3DTHD2_md_chk_mesh_thresh(data)                           (0x00060000&((data)<<17))
#define TVD_3DTHD2_md_y_lo_line_diff_thresh(data)                     (0x0001E000&((data)<<13))
#define TVD_3DTHD2_md_chk_three_line_c_thresh1(data)                  (0x00001C00&((data)<<10))
#define TVD_3DTHD2_md_c_detect_thresh(data)                           (0x000003C0&((data)<<6))
#define TVD_3DTHD2_md_orig_diff_thresh(data)                          (0x0000003F&(data))
#define TVD_3DTHD2_get_md_chk_mesh_thresh(data)                       ((0x00060000&(data))>>17)
#define TVD_3DTHD2_get_md_y_lo_line_diff_thresh(data)                 ((0x0001E000&(data))>>13)
#define TVD_3DTHD2_get_md_chk_three_line_c_thresh1(data)              ((0x00001C00&(data))>>10)
#define TVD_3DTHD2_get_md_c_detect_thresh(data)                       ((0x000003C0&(data))>>6)
#define TVD_3DTHD2_get_md_orig_diff_thresh(data)                      (0x0000003F&(data))

#define TVD_3DTHD3                                                    0x180190A4
#define TVD_3DTHD3_reg_addr                                           "0xB80190A4"
#define TVD_3DTHD3_reg                                                0xB80190A4
#define TVD_3DTHD3_inst_addr                                          "0x0029"
#define TVD_3DTHD3_inst                                               0x0029
#define TVD_3DTHD3_md_line_close_thresh_shift                         (20)
#define TVD_3DTHD3_md_c_near_2d_3d_thresh_shift                       (16)
#define TVD_3DTHD3_md_chk_three_line_c_thresh2_shift                  (13)
#define TVD_3DTHD3_md_line_compare_thresh1_shift                      (8)
#define TVD_3DTHD3_md_chk_angle_c_thresh_shift                        (5)
#define TVD_3DTHD3_md_line_compare_thresh2_shift                      (0)
#define TVD_3DTHD3_md_line_close_thresh_mask                          (0x00F00000)
#define TVD_3DTHD3_md_c_near_2d_3d_thresh_mask                        (0x000F0000)
#define TVD_3DTHD3_md_chk_three_line_c_thresh2_mask                   (0x0000E000)
#define TVD_3DTHD3_md_line_compare_thresh1_mask                       (0x00001F00)
#define TVD_3DTHD3_md_chk_angle_c_thresh_mask                         (0x000000E0)
#define TVD_3DTHD3_md_line_compare_thresh2_mask                       (0x0000001F)
#define TVD_3DTHD3_md_line_close_thresh(data)                         (0x00F00000&((data)<<20))
#define TVD_3DTHD3_md_c_near_2d_3d_thresh(data)                       (0x000F0000&((data)<<16))
#define TVD_3DTHD3_md_chk_three_line_c_thresh2(data)                  (0x0000E000&((data)<<13))
#define TVD_3DTHD3_md_line_compare_thresh1(data)                      (0x00001F00&((data)<<8))
#define TVD_3DTHD3_md_chk_angle_c_thresh(data)                        (0x000000E0&((data)<<5))
#define TVD_3DTHD3_md_line_compare_thresh2(data)                      (0x0000001F&(data))
#define TVD_3DTHD3_get_md_line_close_thresh(data)                     ((0x00F00000&(data))>>20)
#define TVD_3DTHD3_get_md_c_near_2d_3d_thresh(data)                   ((0x000F0000&(data))>>16)
#define TVD_3DTHD3_get_md_chk_three_line_c_thresh2(data)              ((0x0000E000&(data))>>13)
#define TVD_3DTHD3_get_md_line_compare_thresh1(data)                  ((0x00001F00&(data))>>8)
#define TVD_3DTHD3_get_md_chk_angle_c_thresh(data)                    ((0x000000E0&(data))>>5)
#define TVD_3DTHD3_get_md_line_compare_thresh2(data)                  (0x0000001F&(data))

#define TVD_3DTHD4                                                    0x180190A8
#define TVD_3DTHD4_reg_addr                                           "0xB80190A8"
#define TVD_3DTHD4_reg                                                0xB80190A8
#define TVD_3DTHD4_inst_addr                                          "0x002A"
#define TVD_3DTHD4_inst                                               0x002A
#define TVD_3DTHD4_md_c_3d_large_thresh1_shift                        (19)
#define TVD_3DTHD4_md_c_3d_large_thresh2_shift                        (15)
#define TVD_3DTHD4_md_cross_c_suppress_enable_shift                   (14)
#define TVD_3DTHD4_md_c_edge_thresh1_shift                            (7)
#define TVD_3DTHD4_md_c_edge_thresh2_shift                            (0)
#define TVD_3DTHD4_md_c_3d_large_thresh1_mask                         (0x00780000)
#define TVD_3DTHD4_md_c_3d_large_thresh2_mask                         (0x00078000)
#define TVD_3DTHD4_md_cross_c_suppress_enable_mask                    (0x00004000)
#define TVD_3DTHD4_md_c_edge_thresh1_mask                             (0x00003F80)
#define TVD_3DTHD4_md_c_edge_thresh2_mask                             (0x0000007F)
#define TVD_3DTHD4_md_c_3d_large_thresh1(data)                        (0x00780000&((data)<<19))
#define TVD_3DTHD4_md_c_3d_large_thresh2(data)                        (0x00078000&((data)<<15))
#define TVD_3DTHD4_md_cross_c_suppress_enable(data)                   (0x00004000&((data)<<14))
#define TVD_3DTHD4_md_c_edge_thresh1(data)                            (0x00003F80&((data)<<7))
#define TVD_3DTHD4_md_c_edge_thresh2(data)                            (0x0000007F&(data))
#define TVD_3DTHD4_get_md_c_3d_large_thresh1(data)                    ((0x00780000&(data))>>19)
#define TVD_3DTHD4_get_md_c_3d_large_thresh2(data)                    ((0x00078000&(data))>>15)
#define TVD_3DTHD4_get_md_cross_c_suppress_enable(data)               ((0x00004000&(data))>>14)
#define TVD_3DTHD4_get_md_c_edge_thresh1(data)                        ((0x00003F80&(data))>>7)
#define TVD_3DTHD4_get_md_c_edge_thresh2(data)                        (0x0000007F&(data))

#define TVD_SLICER_CTRL                                               0x180190AC
#define TVD_SLICER_CTRL_reg_addr                                      "0xB80190AC"
#define TVD_SLICER_CTRL_reg                                           0xB80190AC
#define TVD_SLICER_CTRL_inst_addr                                     "0x002B"
#define TVD_SLICER_CTRL_inst                                          0x002B
#define TVD_SLICER_CTRL_write_enable6_shift                           (18)
#define TVD_SLICER_CTRL_cc_hddet_st_shift                             (10)
#define TVD_SLICER_CTRL_write_enable5_shift                           (9)
#define TVD_SLICER_CTRL_adap_slvl_en_shift                            (8)
#define TVD_SLICER_CTRL_write_enable4_shift                           (7)
#define TVD_SLICER_CTRL_vbi_st_err_ignored_shift                      (6)
#define TVD_SLICER_CTRL_write_enable3_shift                           (5)
#define TVD_SLICER_CTRL_vbi_en_shift                                  (4)
#define TVD_SLICER_CTRL_write_enable2_shift                           (3)
#define TVD_SLICER_CTRL_cgms_bot_en_shift                             (2)
#define TVD_SLICER_CTRL_write_enable1_shift                           (1)
#define TVD_SLICER_CTRL_cgms_top_en_shift                             (0)
#define TVD_SLICER_CTRL_write_enable6_mask                            (0x00040000)
#define TVD_SLICER_CTRL_cc_hddet_st_mask                              (0x0003FC00)
#define TVD_SLICER_CTRL_write_enable5_mask                            (0x00000200)
#define TVD_SLICER_CTRL_adap_slvl_en_mask                             (0x00000100)
#define TVD_SLICER_CTRL_write_enable4_mask                            (0x00000080)
#define TVD_SLICER_CTRL_vbi_st_err_ignored_mask                       (0x00000040)
#define TVD_SLICER_CTRL_write_enable3_mask                            (0x00000020)
#define TVD_SLICER_CTRL_vbi_en_mask                                   (0x00000010)
#define TVD_SLICER_CTRL_write_enable2_mask                            (0x00000008)
#define TVD_SLICER_CTRL_cgms_bot_en_mask                              (0x00000004)
#define TVD_SLICER_CTRL_write_enable1_mask                            (0x00000002)
#define TVD_SLICER_CTRL_cgms_top_en_mask                              (0x00000001)
#define TVD_SLICER_CTRL_write_enable6(data)                           (0x00040000&((data)<<18))
#define TVD_SLICER_CTRL_cc_hddet_st(data)                             (0x0003FC00&((data)<<10))
#define TVD_SLICER_CTRL_write_enable5(data)                           (0x00000200&((data)<<9))
#define TVD_SLICER_CTRL_adap_slvl_en(data)                            (0x00000100&((data)<<8))
#define TVD_SLICER_CTRL_write_enable4(data)                           (0x00000080&((data)<<7))
#define TVD_SLICER_CTRL_vbi_st_err_ignored(data)                      (0x00000040&((data)<<6))
#define TVD_SLICER_CTRL_write_enable3(data)                           (0x00000020&((data)<<5))
#define TVD_SLICER_CTRL_vbi_en(data)                                  (0x00000010&((data)<<4))
#define TVD_SLICER_CTRL_write_enable2(data)                           (0x00000008&((data)<<3))
#define TVD_SLICER_CTRL_cgms_bot_en(data)                             (0x00000004&((data)<<2))
#define TVD_SLICER_CTRL_write_enable1(data)                           (0x00000002&((data)<<1))
#define TVD_SLICER_CTRL_cgms_top_en(data)                             (0x00000001&(data))
#define TVD_SLICER_CTRL_get_write_enable6(data)                       ((0x00040000&(data))>>18)
#define TVD_SLICER_CTRL_get_cc_hddet_st(data)                         ((0x0003FC00&(data))>>10)
#define TVD_SLICER_CTRL_get_write_enable5(data)                       ((0x00000200&(data))>>9)
#define TVD_SLICER_CTRL_get_adap_slvl_en(data)                        ((0x00000100&(data))>>8)
#define TVD_SLICER_CTRL_get_write_enable4(data)                       ((0x00000080&(data))>>7)
#define TVD_SLICER_CTRL_get_vbi_st_err_ignored(data)                  ((0x00000040&(data))>>6)
#define TVD_SLICER_CTRL_get_write_enable3(data)                       ((0x00000020&(data))>>5)
#define TVD_SLICER_CTRL_get_vbi_en(data)                              ((0x00000010&(data))>>4)
#define TVD_SLICER_CTRL_get_write_enable2(data)                       ((0x00000008&(data))>>3)
#define TVD_SLICER_CTRL_get_cgms_bot_en(data)                         ((0x00000004&(data))>>2)
#define TVD_SLICER_CTRL_get_write_enable1(data)                       ((0x00000002&(data))>>1)
#define TVD_SLICER_CTRL_get_cgms_top_en(data)                         (0x00000001&(data))

#define TVD_VPS_LINE_16                                               0x180190B0
#define TVD_VPS_LINE_16_reg_addr                                      "0xB80190B0"
#define TVD_VPS_LINE_16_reg                                           0xB80190B0
#define TVD_VPS_LINE_16_inst_addr                                     "0x002C"
#define TVD_VPS_LINE_16_inst                                          0x002C
#define TVD_VPS_LINE_16_vps_vbil16o_shift                             (4)
#define TVD_VPS_LINE_16_vps_vbil16e_shift                             (0)
#define TVD_VPS_LINE_16_vps_vbil16o_mask                              (0x000000F0)
#define TVD_VPS_LINE_16_vps_vbil16e_mask                              (0x0000000F)
#define TVD_VPS_LINE_16_vps_vbil16o(data)                             (0x000000F0&((data)<<4))
#define TVD_VPS_LINE_16_vps_vbil16e(data)                             (0x0000000F&(data))
#define TVD_VPS_LINE_16_get_vps_vbil16o(data)                         ((0x000000F0&(data))>>4)
#define TVD_VPS_LINE_16_get_vps_vbil16e(data)                         (0x0000000F&(data))

#define TVD_VBI_LINE0                                                 0x180190B4
#define TVD_VBI_LINE0_reg_addr                                        "0xB80190B4"
#define TVD_VBI_LINE0_reg                                             0xB80190B4
#define TVD_VBI_LINE0_inst_addr                                       "0x002D"
#define TVD_VBI_LINE0_inst                                            0x002D
#define TVD_VBI_LINE0_vbio05_shift                                    (28)
#define TVD_VBI_LINE0_vbie05_shift                                    (24)
#define TVD_VBI_LINE0_vbio06_shift                                    (20)
#define TVD_VBI_LINE0_vbie06_shift                                    (16)
#define TVD_VBI_LINE0_vbio07_shift                                    (12)
#define TVD_VBI_LINE0_vbie07_shift                                    (8)
#define TVD_VBI_LINE0_vbio08_shift                                    (4)
#define TVD_VBI_LINE0_vbie08_shift                                    (0)
#define TVD_VBI_LINE0_vbio05_mask                                     (0xF0000000)
#define TVD_VBI_LINE0_vbie05_mask                                     (0x0F000000)
#define TVD_VBI_LINE0_vbio06_mask                                     (0x00F00000)
#define TVD_VBI_LINE0_vbie06_mask                                     (0x000F0000)
#define TVD_VBI_LINE0_vbio07_mask                                     (0x0000F000)
#define TVD_VBI_LINE0_vbie07_mask                                     (0x00000F00)
#define TVD_VBI_LINE0_vbio08_mask                                     (0x000000F0)
#define TVD_VBI_LINE0_vbie08_mask                                     (0x0000000F)
#define TVD_VBI_LINE0_vbio05(data)                                    (0xF0000000&((data)<<28))
#define TVD_VBI_LINE0_vbie05(data)                                    (0x0F000000&((data)<<24))
#define TVD_VBI_LINE0_vbio06(data)                                    (0x00F00000&((data)<<20))
#define TVD_VBI_LINE0_vbie06(data)                                    (0x000F0000&((data)<<16))
#define TVD_VBI_LINE0_vbio07(data)                                    (0x0000F000&((data)<<12))
#define TVD_VBI_LINE0_vbie07(data)                                    (0x00000F00&((data)<<8))
#define TVD_VBI_LINE0_vbio08(data)                                    (0x000000F0&((data)<<4))
#define TVD_VBI_LINE0_vbie08(data)                                    (0x0000000F&(data))
#define TVD_VBI_LINE0_get_vbio05(data)                                ((0xF0000000&(data))>>28)
#define TVD_VBI_LINE0_get_vbie05(data)                                ((0x0F000000&(data))>>24)
#define TVD_VBI_LINE0_get_vbio06(data)                                ((0x00F00000&(data))>>20)
#define TVD_VBI_LINE0_get_vbie06(data)                                ((0x000F0000&(data))>>16)
#define TVD_VBI_LINE0_get_vbio07(data)                                ((0x0000F000&(data))>>12)
#define TVD_VBI_LINE0_get_vbie07(data)                                ((0x00000F00&(data))>>8)
#define TVD_VBI_LINE0_get_vbio08(data)                                ((0x000000F0&(data))>>4)
#define TVD_VBI_LINE0_get_vbie08(data)                                (0x0000000F&(data))

#define TVD_VBI_LINE1                                                 0x180190B8
#define TVD_VBI_LINE1_reg_addr                                        "0xB80190B8"
#define TVD_VBI_LINE1_reg                                             0xB80190B8
#define TVD_VBI_LINE1_inst_addr                                       "0x002E"
#define TVD_VBI_LINE1_inst                                            0x002E
#define TVD_VBI_LINE1_vbio09_shift                                    (28)
#define TVD_VBI_LINE1_vbie09_shift                                    (24)
#define TVD_VBI_LINE1_vbio10_shift                                    (20)
#define TVD_VBI_LINE1_vbie10_shift                                    (16)
#define TVD_VBI_LINE1_vbio11_shift                                    (12)
#define TVD_VBI_LINE1_vbie11_shift                                    (8)
#define TVD_VBI_LINE1_vbio12_shift                                    (4)
#define TVD_VBI_LINE1_vbie12_shift                                    (0)
#define TVD_VBI_LINE1_vbio09_mask                                     (0xF0000000)
#define TVD_VBI_LINE1_vbie09_mask                                     (0x0F000000)
#define TVD_VBI_LINE1_vbio10_mask                                     (0x00F00000)
#define TVD_VBI_LINE1_vbie10_mask                                     (0x000F0000)
#define TVD_VBI_LINE1_vbio11_mask                                     (0x0000F000)
#define TVD_VBI_LINE1_vbie11_mask                                     (0x00000F00)
#define TVD_VBI_LINE1_vbio12_mask                                     (0x000000F0)
#define TVD_VBI_LINE1_vbie12_mask                                     (0x0000000F)
#define TVD_VBI_LINE1_vbio09(data)                                    (0xF0000000&((data)<<28))
#define TVD_VBI_LINE1_vbie09(data)                                    (0x0F000000&((data)<<24))
#define TVD_VBI_LINE1_vbio10(data)                                    (0x00F00000&((data)<<20))
#define TVD_VBI_LINE1_vbie10(data)                                    (0x000F0000&((data)<<16))
#define TVD_VBI_LINE1_vbio11(data)                                    (0x0000F000&((data)<<12))
#define TVD_VBI_LINE1_vbie11(data)                                    (0x00000F00&((data)<<8))
#define TVD_VBI_LINE1_vbio12(data)                                    (0x000000F0&((data)<<4))
#define TVD_VBI_LINE1_vbie12(data)                                    (0x0000000F&(data))
#define TVD_VBI_LINE1_get_vbio09(data)                                ((0xF0000000&(data))>>28)
#define TVD_VBI_LINE1_get_vbie09(data)                                ((0x0F000000&(data))>>24)
#define TVD_VBI_LINE1_get_vbio10(data)                                ((0x00F00000&(data))>>20)
#define TVD_VBI_LINE1_get_vbie10(data)                                ((0x000F0000&(data))>>16)
#define TVD_VBI_LINE1_get_vbio11(data)                                ((0x0000F000&(data))>>12)
#define TVD_VBI_LINE1_get_vbie11(data)                                ((0x00000F00&(data))>>8)
#define TVD_VBI_LINE1_get_vbio12(data)                                ((0x000000F0&(data))>>4)
#define TVD_VBI_LINE1_get_vbie12(data)                                (0x0000000F&(data))

#define TVD_VBI_LINE2                                                 0x180190BC
#define TVD_VBI_LINE2_reg_addr                                        "0xB80190BC"
#define TVD_VBI_LINE2_reg                                             0xB80190BC
#define TVD_VBI_LINE2_inst_addr                                       "0x002F"
#define TVD_VBI_LINE2_inst                                            0x002F
#define TVD_VBI_LINE2_vbio13_shift                                    (28)
#define TVD_VBI_LINE2_vbie13_shift                                    (24)
#define TVD_VBI_LINE2_vbio14_shift                                    (20)
#define TVD_VBI_LINE2_vbie14_shift                                    (16)
#define TVD_VBI_LINE2_vbio15_shift                                    (12)
#define TVD_VBI_LINE2_vbie15_shift                                    (8)
#define TVD_VBI_LINE2_vbio16_shift                                    (4)
#define TVD_VBI_LINE2_vbie16_shift                                    (0)
#define TVD_VBI_LINE2_vbio13_mask                                     (0xF0000000)
#define TVD_VBI_LINE2_vbie13_mask                                     (0x0F000000)
#define TVD_VBI_LINE2_vbio14_mask                                     (0x00F00000)
#define TVD_VBI_LINE2_vbie14_mask                                     (0x000F0000)
#define TVD_VBI_LINE2_vbio15_mask                                     (0x0000F000)
#define TVD_VBI_LINE2_vbie15_mask                                     (0x00000F00)
#define TVD_VBI_LINE2_vbio16_mask                                     (0x000000F0)
#define TVD_VBI_LINE2_vbie16_mask                                     (0x0000000F)
#define TVD_VBI_LINE2_vbio13(data)                                    (0xF0000000&((data)<<28))
#define TVD_VBI_LINE2_vbie13(data)                                    (0x0F000000&((data)<<24))
#define TVD_VBI_LINE2_vbio14(data)                                    (0x00F00000&((data)<<20))
#define TVD_VBI_LINE2_vbie14(data)                                    (0x000F0000&((data)<<16))
#define TVD_VBI_LINE2_vbio15(data)                                    (0x0000F000&((data)<<12))
#define TVD_VBI_LINE2_vbie15(data)                                    (0x00000F00&((data)<<8))
#define TVD_VBI_LINE2_vbio16(data)                                    (0x000000F0&((data)<<4))
#define TVD_VBI_LINE2_vbie16(data)                                    (0x0000000F&(data))
#define TVD_VBI_LINE2_get_vbio13(data)                                ((0xF0000000&(data))>>28)
#define TVD_VBI_LINE2_get_vbie13(data)                                ((0x0F000000&(data))>>24)
#define TVD_VBI_LINE2_get_vbio14(data)                                ((0x00F00000&(data))>>20)
#define TVD_VBI_LINE2_get_vbie14(data)                                ((0x000F0000&(data))>>16)
#define TVD_VBI_LINE2_get_vbio15(data)                                ((0x0000F000&(data))>>12)
#define TVD_VBI_LINE2_get_vbie15(data)                                ((0x00000F00&(data))>>8)
#define TVD_VBI_LINE2_get_vbio16(data)                                ((0x000000F0&(data))>>4)
#define TVD_VBI_LINE2_get_vbie16(data)                                (0x0000000F&(data))

#define TVD_VBI_LINE3                                                 0x180190C0
#define TVD_VBI_LINE3_reg_addr                                        "0xB80190C0"
#define TVD_VBI_LINE3_reg                                             0xB80190C0
#define TVD_VBI_LINE3_inst_addr                                       "0x0030"
#define TVD_VBI_LINE3_inst                                            0x0030
#define TVD_VBI_LINE3_vbio17_shift                                    (28)
#define TVD_VBI_LINE3_vbie17_shift                                    (24)
#define TVD_VBI_LINE3_vbio18_shift                                    (20)
#define TVD_VBI_LINE3_vbie18_shift                                    (16)
#define TVD_VBI_LINE3_vbio19_shift                                    (12)
#define TVD_VBI_LINE3_vbie19_shift                                    (8)
#define TVD_VBI_LINE3_vbio20_shift                                    (4)
#define TVD_VBI_LINE3_vbie20_shift                                    (0)
#define TVD_VBI_LINE3_vbio17_mask                                     (0xF0000000)
#define TVD_VBI_LINE3_vbie17_mask                                     (0x0F000000)
#define TVD_VBI_LINE3_vbio18_mask                                     (0x00F00000)
#define TVD_VBI_LINE3_vbie18_mask                                     (0x000F0000)
#define TVD_VBI_LINE3_vbio19_mask                                     (0x0000F000)
#define TVD_VBI_LINE3_vbie19_mask                                     (0x00000F00)
#define TVD_VBI_LINE3_vbio20_mask                                     (0x000000F0)
#define TVD_VBI_LINE3_vbie20_mask                                     (0x0000000F)
#define TVD_VBI_LINE3_vbio17(data)                                    (0xF0000000&((data)<<28))
#define TVD_VBI_LINE3_vbie17(data)                                    (0x0F000000&((data)<<24))
#define TVD_VBI_LINE3_vbio18(data)                                    (0x00F00000&((data)<<20))
#define TVD_VBI_LINE3_vbie18(data)                                    (0x000F0000&((data)<<16))
#define TVD_VBI_LINE3_vbio19(data)                                    (0x0000F000&((data)<<12))
#define TVD_VBI_LINE3_vbie19(data)                                    (0x00000F00&((data)<<8))
#define TVD_VBI_LINE3_vbio20(data)                                    (0x000000F0&((data)<<4))
#define TVD_VBI_LINE3_vbie20(data)                                    (0x0000000F&(data))
#define TVD_VBI_LINE3_get_vbio17(data)                                ((0xF0000000&(data))>>28)
#define TVD_VBI_LINE3_get_vbie17(data)                                ((0x0F000000&(data))>>24)
#define TVD_VBI_LINE3_get_vbio18(data)                                ((0x00F00000&(data))>>20)
#define TVD_VBI_LINE3_get_vbie18(data)                                ((0x000F0000&(data))>>16)
#define TVD_VBI_LINE3_get_vbio19(data)                                ((0x0000F000&(data))>>12)
#define TVD_VBI_LINE3_get_vbie19(data)                                ((0x00000F00&(data))>>8)
#define TVD_VBI_LINE3_get_vbio20(data)                                ((0x000000F0&(data))>>4)
#define TVD_VBI_LINE3_get_vbie20(data)                                (0x0000000F&(data))

#define TVD_VBI_LINE4                                                 0x180190C4
#define TVD_VBI_LINE4_reg_addr                                        "0xB80190C4"
#define TVD_VBI_LINE4_reg                                             0xB80190C4
#define TVD_VBI_LINE4_inst_addr                                       "0x0031"
#define TVD_VBI_LINE4_inst                                            0x0031
#define TVD_VBI_LINE4_vbio21_shift                                    (28)
#define TVD_VBI_LINE4_vbie21_shift                                    (24)
#define TVD_VBI_LINE4_vbio22_shift                                    (20)
#define TVD_VBI_LINE4_vbie22_shift                                    (16)
#define TVD_VBI_LINE4_vbio23_shift                                    (12)
#define TVD_VBI_LINE4_vbie23_shift                                    (8)
#define TVD_VBI_LINE4_vbio_other_shift                                (4)
#define TVD_VBI_LINE4_vbie_other_shift                                (0)
#define TVD_VBI_LINE4_vbio21_mask                                     (0xF0000000)
#define TVD_VBI_LINE4_vbie21_mask                                     (0x0F000000)
#define TVD_VBI_LINE4_vbio22_mask                                     (0x00F00000)
#define TVD_VBI_LINE4_vbie22_mask                                     (0x000F0000)
#define TVD_VBI_LINE4_vbio23_mask                                     (0x0000F000)
#define TVD_VBI_LINE4_vbie23_mask                                     (0x00000F00)
#define TVD_VBI_LINE4_vbio_other_mask                                 (0x000000F0)
#define TVD_VBI_LINE4_vbie_other_mask                                 (0x0000000F)
#define TVD_VBI_LINE4_vbio21(data)                                    (0xF0000000&((data)<<28))
#define TVD_VBI_LINE4_vbie21(data)                                    (0x0F000000&((data)<<24))
#define TVD_VBI_LINE4_vbio22(data)                                    (0x00F00000&((data)<<20))
#define TVD_VBI_LINE4_vbie22(data)                                    (0x000F0000&((data)<<16))
#define TVD_VBI_LINE4_vbio23(data)                                    (0x0000F000&((data)<<12))
#define TVD_VBI_LINE4_vbie23(data)                                    (0x00000F00&((data)<<8))
#define TVD_VBI_LINE4_vbio_other(data)                                (0x000000F0&((data)<<4))
#define TVD_VBI_LINE4_vbie_other(data)                                (0x0000000F&(data))
#define TVD_VBI_LINE4_get_vbio21(data)                                ((0xF0000000&(data))>>28)
#define TVD_VBI_LINE4_get_vbie21(data)                                ((0x0F000000&(data))>>24)
#define TVD_VBI_LINE4_get_vbio22(data)                                ((0x00F00000&(data))>>20)
#define TVD_VBI_LINE4_get_vbie22(data)                                ((0x000F0000&(data))>>16)
#define TVD_VBI_LINE4_get_vbio23(data)                                ((0x0000F000&(data))>>12)
#define TVD_VBI_LINE4_get_vbie23(data)                                ((0x00000F00&(data))>>8)
#define TVD_VBI_LINE4_get_vbio_other(data)                            ((0x000000F0&(data))>>4)
#define TVD_VBI_LINE4_get_vbie_other(data)                            (0x0000000F&(data))

#define TVD_CGMS_LINE                                                 0x180190C8
#define TVD_CGMS_LINE_reg_addr                                        "0xB80190C8"
#define TVD_CGMS_LINE_reg                                             0xB80190C8
#define TVD_CGMS_LINE_inst_addr                                       "0x0032"
#define TVD_CGMS_LINE_inst                                            0x0032
#define TVD_CGMS_LINE_cgms_line_even_shift                            (8)
#define TVD_CGMS_LINE_cgms_line_odd_shift                             (0)
#define TVD_CGMS_LINE_cgms_line_even_mask                             (0x0000FF00)
#define TVD_CGMS_LINE_cgms_line_odd_mask                              (0x000000FF)
#define TVD_CGMS_LINE_cgms_line_even(data)                            (0x0000FF00&((data)<<8))
#define TVD_CGMS_LINE_cgms_line_odd(data)                             (0x000000FF&(data))
#define TVD_CGMS_LINE_get_cgms_line_even(data)                        ((0x0000FF00&(data))>>8)
#define TVD_CGMS_LINE_get_cgms_line_odd(data)                         (0x000000FF&(data))

#define TVD_VBI_GAIN_LVL                                              0x180190CC
#define TVD_VBI_GAIN_LVL_reg_addr                                     "0xB80190CC"
#define TVD_VBI_GAIN_LVL_reg                                          0xB80190CC
#define TVD_VBI_GAIN_LVL_inst_addr                                    "0x0033"
#define TVD_VBI_GAIN_LVL_inst                                         0x0033
#define TVD_VBI_GAIN_LVL_data_hlvl_shift                              (9)
#define TVD_VBI_GAIN_LVL_gain_shift                                   (6)
#define TVD_VBI_GAIN_LVL_igain_shift                                  (3)
#define TVD_VBI_GAIN_LVL_pgain_shift                                  (0)
#define TVD_VBI_GAIN_LVL_data_hlvl_mask                               (0x0001FE00)
#define TVD_VBI_GAIN_LVL_gain_mask                                    (0x000001C0)
#define TVD_VBI_GAIN_LVL_igain_mask                                   (0x00000038)
#define TVD_VBI_GAIN_LVL_pgain_mask                                   (0x00000007)
#define TVD_VBI_GAIN_LVL_data_hlvl(data)                              (0x0001FE00&((data)<<9))
#define TVD_VBI_GAIN_LVL_gain(data)                                   (0x000001C0&((data)<<6))
#define TVD_VBI_GAIN_LVL_igain(data)                                  (0x00000038&((data)<<3))
#define TVD_VBI_GAIN_LVL_pgain(data)                                  (0x00000007&(data))
#define TVD_VBI_GAIN_LVL_get_data_hlvl(data)                          ((0x0001FE00&(data))>>9)
#define TVD_VBI_GAIN_LVL_get_gain(data)                               ((0x000001C0&(data))>>6)
#define TVD_VBI_GAIN_LVL_get_igain(data)                              ((0x00000038&(data))>>3)
#define TVD_VBI_GAIN_LVL_get_pgain(data)                              (0x00000007&(data))

#define TVD_CC_DTO                                                    0x180190D0
#define TVD_CC_DTO_reg_addr                                           "0xB80190D0"
#define TVD_CC_DTO_reg                                                0xB80190D0
#define TVD_CC_DTO_inst_addr                                          "0x0034"
#define TVD_CC_DTO_inst                                               0x0034
#define TVD_CC_DTO_cc_dto_shift                                       (0)
#define TVD_CC_DTO_cc_dto_mask                                        (0x0000FFFF)
#define TVD_CC_DTO_cc_dto(data)                                       (0x0000FFFF&(data))
#define TVD_CC_DTO_get_cc_dto(data)                                   (0x0000FFFF&(data))

#define TVD_TT_DTO                                                    0x180190D4
#define TVD_TT_DTO_reg_addr                                           "0xB80190D4"
#define TVD_TT_DTO_reg                                                0xB80190D4
#define TVD_TT_DTO_inst_addr                                          "0x0035"
#define TVD_TT_DTO_inst                                               0x0035
#define TVD_TT_DTO_tt_dto_shift                                       (0)
#define TVD_TT_DTO_tt_dto_mask                                        (0x0000FFFF)
#define TVD_TT_DTO_tt_dto(data)                                       (0x0000FFFF&(data))
#define TVD_TT_DTO_get_tt_dto(data)                                   (0x0000FFFF&(data))

#define TVD_WSS_DTO                                                   0x180190D8
#define TVD_WSS_DTO_reg_addr                                          "0xB80190D8"
#define TVD_WSS_DTO_reg                                               0xB80190D8
#define TVD_WSS_DTO_inst_addr                                         "0x0036"
#define TVD_WSS_DTO_inst                                              0x0036
#define TVD_WSS_DTO_wss_dto_shift                                     (0)
#define TVD_WSS_DTO_wss_dto_mask                                      (0x0000FFFF)
#define TVD_WSS_DTO_wss_dto(data)                                     (0x0000FFFF&(data))
#define TVD_WSS_DTO_get_wss_dto(data)                                 (0x0000FFFF&(data))

#define TVD_VBI_FRAME_START                                           0x180190DC
#define TVD_VBI_FRAME_START_reg_addr                                  "0xB80190DC"
#define TVD_VBI_FRAME_START_reg                                       0xB80190DC
#define TVD_VBI_FRAME_START_inst_addr                                 "0x0037"
#define TVD_VBI_FRAME_START_inst                                      0x0037
#define TVD_VBI_FRAME_START_cc_frame_start_shift                      (24)
#define TVD_VBI_FRAME_START_tt_frame_start_shift                      (16)
#define TVD_VBI_FRAME_START_tt_start_code_shift                       (8)
#define TVD_VBI_FRAME_START_wss_frame_start_shift                     (0)
#define TVD_VBI_FRAME_START_cc_frame_start_mask                       (0xFF000000)
#define TVD_VBI_FRAME_START_tt_frame_start_mask                       (0x00FF0000)
#define TVD_VBI_FRAME_START_tt_start_code_mask                        (0x0000FF00)
#define TVD_VBI_FRAME_START_wss_frame_start_mask                      (0x000000FF)
#define TVD_VBI_FRAME_START_cc_frame_start(data)                      (0xFF000000&((data)<<24))
#define TVD_VBI_FRAME_START_tt_frame_start(data)                      (0x00FF0000&((data)<<16))
#define TVD_VBI_FRAME_START_tt_start_code(data)                       (0x0000FF00&((data)<<8))
#define TVD_VBI_FRAME_START_wss_frame_start(data)                     (0x000000FF&(data))
#define TVD_VBI_FRAME_START_get_cc_frame_start(data)                  ((0xFF000000&(data))>>24)
#define TVD_VBI_FRAME_START_get_tt_frame_start(data)                  ((0x00FF0000&(data))>>16)
#define TVD_VBI_FRAME_START_get_tt_start_code(data)                   ((0x0000FF00&(data))>>8)
#define TVD_VBI_FRAME_START_get_wss_frame_start(data)                 (0x000000FF&(data))

#define TVD_VBI_START                                                 0x180190E0
#define TVD_VBI_START_reg_addr                                        "0xB80190E0"
#define TVD_VBI_START_reg                                             0xB80190E0
#define TVD_VBI_START_inst_addr                                       "0x0038"
#define TVD_VBI_START_inst                                            0x0038
#define TVD_VBI_START_cc_start_shift                                  (16)
#define TVD_VBI_START_tt_start_shift                                  (8)
#define TVD_VBI_START_wss_start_shift                                 (0)
#define TVD_VBI_START_cc_start_mask                                   (0x00FF0000)
#define TVD_VBI_START_tt_start_mask                                   (0x0000FF00)
#define TVD_VBI_START_wss_start_mask                                  (0x000000FF)
#define TVD_VBI_START_cc_start(data)                                  (0x00FF0000&((data)<<16))
#define TVD_VBI_START_tt_start(data)                                  (0x0000FF00&((data)<<8))
#define TVD_VBI_START_wss_start(data)                                 (0x000000FF&(data))
#define TVD_VBI_START_get_cc_start(data)                              ((0x00FF0000&(data))>>16)
#define TVD_VBI_START_get_tt_start(data)                              ((0x0000FF00&(data))>>8)
#define TVD_VBI_START_get_wss_start(data)                             (0x000000FF&(data))

#define TVD_VBI_CAL_DC_DETECT                                         0x180190E4
#define TVD_VBI_CAL_DC_DETECT_reg_addr                                "0xB80190E4"
#define TVD_VBI_CAL_DC_DETECT_reg                                     0xB80190E4
#define TVD_VBI_CAL_DC_DETECT_inst_addr                               "0x0039"
#define TVD_VBI_CAL_DC_DETECT_inst                                    0x0039
#define TVD_VBI_CAL_DC_DETECT_vbi_cal_dc_st_shift                     (28)
#define TVD_VBI_CAL_DC_DETECT_vbi_cal_dc_end_shift                    (24)
#define TVD_VBI_CAL_DC_DETECT_wss_cal_dc_st_shift                     (20)
#define TVD_VBI_CAL_DC_DETECT_wss_cal_dc_end_shift                    (16)
#define TVD_VBI_CAL_DC_DETECT_vps_cal_dc_st_shift                     (12)
#define TVD_VBI_CAL_DC_DETECT_vps_cal_dc_end_shift                    (8)
#define TVD_VBI_CAL_DC_DETECT_cgms_cal_dc_st_shift                    (4)
#define TVD_VBI_CAL_DC_DETECT_cgms_cal_dc_end_shift                   (0)
#define TVD_VBI_CAL_DC_DETECT_vbi_cal_dc_st_mask                      (0xF0000000)
#define TVD_VBI_CAL_DC_DETECT_vbi_cal_dc_end_mask                     (0x0F000000)
#define TVD_VBI_CAL_DC_DETECT_wss_cal_dc_st_mask                      (0x00F00000)
#define TVD_VBI_CAL_DC_DETECT_wss_cal_dc_end_mask                     (0x000F0000)
#define TVD_VBI_CAL_DC_DETECT_vps_cal_dc_st_mask                      (0x0000F000)
#define TVD_VBI_CAL_DC_DETECT_vps_cal_dc_end_mask                     (0x00000F00)
#define TVD_VBI_CAL_DC_DETECT_cgms_cal_dc_st_mask                     (0x000000F0)
#define TVD_VBI_CAL_DC_DETECT_cgms_cal_dc_end_mask                    (0x0000000F)
#define TVD_VBI_CAL_DC_DETECT_vbi_cal_dc_st(data)                     (0xF0000000&((data)<<28))
#define TVD_VBI_CAL_DC_DETECT_vbi_cal_dc_end(data)                    (0x0F000000&((data)<<24))
#define TVD_VBI_CAL_DC_DETECT_wss_cal_dc_st(data)                     (0x00F00000&((data)<<20))
#define TVD_VBI_CAL_DC_DETECT_wss_cal_dc_end(data)                    (0x000F0000&((data)<<16))
#define TVD_VBI_CAL_DC_DETECT_vps_cal_dc_st(data)                     (0x0000F000&((data)<<12))
#define TVD_VBI_CAL_DC_DETECT_vps_cal_dc_end(data)                    (0x00000F00&((data)<<8))
#define TVD_VBI_CAL_DC_DETECT_cgms_cal_dc_st(data)                    (0x000000F0&((data)<<4))
#define TVD_VBI_CAL_DC_DETECT_cgms_cal_dc_end(data)                   (0x0000000F&(data))
#define TVD_VBI_CAL_DC_DETECT_get_vbi_cal_dc_st(data)                 ((0xF0000000&(data))>>28)
#define TVD_VBI_CAL_DC_DETECT_get_vbi_cal_dc_end(data)                ((0x0F000000&(data))>>24)
#define TVD_VBI_CAL_DC_DETECT_get_wss_cal_dc_st(data)                 ((0x00F00000&(data))>>20)
#define TVD_VBI_CAL_DC_DETECT_get_wss_cal_dc_end(data)                ((0x000F0000&(data))>>16)
#define TVD_VBI_CAL_DC_DETECT_get_vps_cal_dc_st(data)                 ((0x0000F000&(data))>>12)
#define TVD_VBI_CAL_DC_DETECT_get_vps_cal_dc_end(data)                ((0x00000F00&(data))>>8)
#define TVD_VBI_CAL_DC_DETECT_get_cgms_cal_dc_st(data)                ((0x000000F0&(data))>>4)
#define TVD_VBI_CAL_DC_DETECT_get_cgms_cal_dc_end(data)               (0x0000000F&(data))

#define TVD_CGMS_DC                                                   0x180190E8
#define TVD_CGMS_DC_reg_addr                                          "0xB80190E8"
#define TVD_CGMS_DC_reg                                               0xB80190E8
#define TVD_CGMS_DC_inst_addr                                         "0x003A"
#define TVD_CGMS_DC_inst                                              0x003A
#define TVD_CGMS_DC_adap_cgms_dc_en_shift                             (8)
#define TVD_CGMS_DC_cgms_dc_shift                                     (0)
#define TVD_CGMS_DC_adap_cgms_dc_en_mask                              (0x00000100)
#define TVD_CGMS_DC_cgms_dc_mask                                      (0x000000FF)
#define TVD_CGMS_DC_adap_cgms_dc_en(data)                             (0x00000100&((data)<<8))
#define TVD_CGMS_DC_cgms_dc(data)                                     (0x000000FF&(data))
#define TVD_CGMS_DC_get_adap_cgms_dc_en(data)                         ((0x00000100&(data))>>8)
#define TVD_CGMS_DC_get_cgms_dc(data)                                 (0x000000FF&(data))

#define TVD_VBI_RDY                                                   0x180190EC
#define TVD_VBI_RDY_reg_addr                                          "0xB80190EC"
#define TVD_VBI_RDY_reg                                               0xB80190EC
#define TVD_VBI_RDY_inst_addr                                         "0x003B"
#define TVD_VBI_RDY_inst                                              0x003B
#define TVD_VBI_RDY_cc_rdy_shift                                      (2)
#define TVD_VBI_RDY_wss_rdy_shift                                     (1)
#define TVD_VBI_RDY_cgms_rdy_shift                                    (0)
#define TVD_VBI_RDY_cc_rdy_mask                                       (0x00000004)
#define TVD_VBI_RDY_wss_rdy_mask                                      (0x00000002)
#define TVD_VBI_RDY_cgms_rdy_mask                                     (0x00000001)
#define TVD_VBI_RDY_cc_rdy(data)                                      (0x00000004&((data)<<2))
#define TVD_VBI_RDY_wss_rdy(data)                                     (0x00000002&((data)<<1))
#define TVD_VBI_RDY_cgms_rdy(data)                                    (0x00000001&(data))
#define TVD_VBI_RDY_get_cc_rdy(data)                                  ((0x00000004&(data))>>2)
#define TVD_VBI_RDY_get_wss_rdy(data)                                 ((0x00000002&(data))>>1)
#define TVD_VBI_RDY_get_cgms_rdy(data)                                (0x00000001&(data))

#define TVD_CC_DATA                                                   0x180190F0
#define TVD_CC_DATA_reg_addr                                          "0xB80190F0"
#define TVD_CC_DATA_reg                                               0xB80190F0
#define TVD_CC_DATA_inst_addr                                         "0x003C"
#define TVD_CC_DATA_inst                                              0x003C
#define TVD_CC_DATA_cc_data_shift                                     (0)
#define TVD_CC_DATA_cc_data_mask                                      (0x0000FFFF)
#define TVD_CC_DATA_cc_data(data)                                     (0x0000FFFF&(data))
#define TVD_CC_DATA_get_cc_data(data)                                 (0x0000FFFF&(data))

#define TVD_WSS_DATA                                                  0x180190F4
#define TVD_WSS_DATA_reg_addr                                         "0xB80190F4"
#define TVD_WSS_DATA_reg                                              0xB80190F4
#define TVD_WSS_DATA_inst_addr                                        "0x003D"
#define TVD_WSS_DATA_inst                                             0x003D
#define TVD_WSS_DATA_wss_data_shift                                   (0)
#define TVD_WSS_DATA_wss_data_mask                                    (0x0000FFFF)
#define TVD_WSS_DATA_wss_data(data)                                   (0x0000FFFF&(data))
#define TVD_WSS_DATA_get_wss_data(data)                               (0x0000FFFF&(data))

#define TVD_CGMS_DATA                                                 0x180190F8
#define TVD_CGMS_DATA_reg_addr                                        "0xB80190F8"
#define TVD_CGMS_DATA_reg                                             0xB80190F8
#define TVD_CGMS_DATA_inst_addr                                       "0x003E"
#define TVD_CGMS_DATA_inst                                            0x003E
#define TVD_CGMS_DATA_cgms_data_shift                                 (0)
#define TVD_CGMS_DATA_cgms_data_mask                                  (0x000FFFFF)
#define TVD_CGMS_DATA_cgms_data(data)                                 (0x000FFFFF&(data))
#define TVD_CGMS_DATA_get_cgms_data(data)                             (0x000FFFFF&(data))

#define TVD_VIDEO_ADC_DIGITAL_CTRL0                                   0x180190FC
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_reg_addr                          "0xB80190FC"
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_reg                               0xB80190FC
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_inst_addr                         "0x003F"
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_inst                              0x003F
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_apowl_shift                       (25)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_bpowl_shift                       (24)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_cpowl_shift                       (23)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_dpowl_shift                       (22)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_asgainl_shift                     (19)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_bsgainl_shift                     (16)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_csgainl_shift                     (13)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_dsgainl_shift                     (10)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_calibratel_shift                  (6)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_scavl_shift                       (3)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_svoutl_shift                      (0)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_apowl_mask                        (0x02000000)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_bpowl_mask                        (0x01000000)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_cpowl_mask                        (0x00800000)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_dpowl_mask                        (0x00400000)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_asgainl_mask                      (0x00380000)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_bsgainl_mask                      (0x00070000)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_csgainl_mask                      (0x0000E000)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_dsgainl_mask                      (0x00001C00)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_calibratel_mask                   (0x000003C0)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_scavl_mask                        (0x00000038)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_svoutl_mask                       (0x00000007)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_apowl(data)                       (0x02000000&((data)<<25))
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_bpowl(data)                       (0x01000000&((data)<<24))
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_cpowl(data)                       (0x00800000&((data)<<23))
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_dpowl(data)                       (0x00400000&((data)<<22))
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_asgainl(data)                     (0x00380000&((data)<<19))
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_bsgainl(data)                     (0x00070000&((data)<<16))
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_csgainl(data)                     (0x0000E000&((data)<<13))
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_dsgainl(data)                     (0x00001C00&((data)<<10))
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_calibratel(data)                  (0x000003C0&((data)<<6))
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_scavl(data)                       (0x00000038&((data)<<3))
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_svoutl(data)                      (0x00000007&(data))
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_get_apowl(data)                   ((0x02000000&(data))>>25)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_get_bpowl(data)                   ((0x01000000&(data))>>24)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_get_cpowl(data)                   ((0x00800000&(data))>>23)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_get_dpowl(data)                   ((0x00400000&(data))>>22)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_get_asgainl(data)                 ((0x00380000&(data))>>19)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_get_bsgainl(data)                 ((0x00070000&(data))>>16)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_get_csgainl(data)                 ((0x0000E000&(data))>>13)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_get_dsgainl(data)                 ((0x00001C00&(data))>>10)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_get_calibratel(data)              ((0x000003C0&(data))>>6)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_get_scavl(data)                   ((0x00000038&(data))>>3)
#define TVD_VIDEO_ADC_DIGITAL_CTRL0_get_svoutl(data)                  (0x00000007&(data))

#define TVD_VIDEO_ADC_DIGITAL_CTRL1                                   0x18019100
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_reg_addr                          "0xB8019100"
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_reg                               0xB8019100
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_inst_addr                         "0x0040"
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_inst                              0x0040
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_ainswl_shift                      (30)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_binswl_shift                      (28)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_cinswl_shift                      (26)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_dinswl_shift                      (24)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_aclamp_spl_shift                  (18)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_bclamp_spl_shift                  (12)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_cclamp_spl_shift                  (6)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_dclamp_spl_shift                  (0)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_ainswl_mask                       (0xC0000000)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_binswl_mask                       (0x30000000)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_cinswl_mask                       (0x0C000000)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_dinswl_mask                       (0x03000000)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_aclamp_spl_mask                   (0x00FC0000)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_bclamp_spl_mask                   (0x0003F000)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_cclamp_spl_mask                   (0x00000FC0)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_dclamp_spl_mask                   (0x0000003F)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_ainswl(data)                      (0xC0000000&((data)<<30))
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_binswl(data)                      (0x30000000&((data)<<28))
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_cinswl(data)                      (0x0C000000&((data)<<26))
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_dinswl(data)                      (0x03000000&((data)<<24))
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_aclamp_spl(data)                  (0x00FC0000&((data)<<18))
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_bclamp_spl(data)                  (0x0003F000&((data)<<12))
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_cclamp_spl(data)                  (0x00000FC0&((data)<<6))
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_dclamp_spl(data)                  (0x0000003F&(data))
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_get_ainswl(data)                  ((0xC0000000&(data))>>30)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_get_binswl(data)                  ((0x30000000&(data))>>28)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_get_cinswl(data)                  ((0x0C000000&(data))>>26)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_get_dinswl(data)                  ((0x03000000&(data))>>24)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_get_aclamp_spl(data)              ((0x00FC0000&(data))>>18)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_get_bclamp_spl(data)              ((0x0003F000&(data))>>12)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_get_cclamp_spl(data)              ((0x00000FC0&(data))>>6)
#define TVD_VIDEO_ADC_DIGITAL_CTRL1_get_dclamp_spl(data)              (0x0000003F&(data))

#define TVD_VIDEO_ADC_ANALOG_CTRL0                                    0x18019104
#define TVD_VIDEO_ADC_ANALOG_CTRL0_reg_addr                           "0xB8019104"
#define TVD_VIDEO_ADC_ANALOG_CTRL0_reg                                0xB8019104
#define TVD_VIDEO_ADC_ANALOG_CTRL0_inst_addr                          "0x0041"
#define TVD_VIDEO_ADC_ANALOG_CTRL0_inst                               0x0041
#define TVD_VIDEO_ADC_ANALOG_CTRL0_asvicml_shift                      (29)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_bsvicml_shift                      (26)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_csvicml_shift                      (23)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_dsvicml_shift                      (20)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_bufl_shift                     (16)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_mdacl_shift                    (12)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_sourcel_shift                  (8)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_topl_shift                     (4)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_vrtbufl_shift                  (0)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_asvicml_mask                       (0xE0000000)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_bsvicml_mask                       (0x1C000000)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_csvicml_mask                       (0x03800000)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_dsvicml_mask                       (0x00700000)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_bufl_mask                      (0x000F0000)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_mdacl_mask                     (0x0000F000)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_sourcel_mask                   (0x00000F00)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_topl_mask                      (0x000000F0)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_vrtbufl_mask                   (0x0000000F)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_asvicml(data)                      (0xE0000000&((data)<<29))
#define TVD_VIDEO_ADC_ANALOG_CTRL0_bsvicml(data)                      (0x1C000000&((data)<<26))
#define TVD_VIDEO_ADC_ANALOG_CTRL0_csvicml(data)                      (0x03800000&((data)<<23))
#define TVD_VIDEO_ADC_ANALOG_CTRL0_dsvicml(data)                      (0x00700000&((data)<<20))
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_bufl(data)                     (0x000F0000&((data)<<16))
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_mdacl(data)                    (0x0000F000&((data)<<12))
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_sourcel(data)                  (0x00000F00&((data)<<8))
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_topl(data)                     (0x000000F0&((data)<<4))
#define TVD_VIDEO_ADC_ANALOG_CTRL0_sib_vrtbufl(data)                  (0x0000000F&(data))
#define TVD_VIDEO_ADC_ANALOG_CTRL0_get_asvicml(data)                  ((0xE0000000&(data))>>29)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_get_bsvicml(data)                  ((0x1C000000&(data))>>26)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_get_csvicml(data)                  ((0x03800000&(data))>>23)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_get_dsvicml(data)                  ((0x00700000&(data))>>20)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_get_sib_bufl(data)                 ((0x000F0000&(data))>>16)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_get_sib_mdacl(data)                ((0x0000F000&(data))>>12)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_get_sib_sourcel(data)              ((0x00000F00&(data))>>8)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_get_sib_topl(data)                 ((0x000000F0&(data))>>4)
#define TVD_VIDEO_ADC_ANALOG_CTRL0_get_sib_vrtbufl(data)              (0x0000000F&(data))

#define TVD_VIDEO_ADC_ANALOG_CTRL1                                    0x18019108
#define TVD_VIDEO_ADC_ANALOG_CTRL1_reg_addr                           "0xB8019108"
#define TVD_VIDEO_ADC_ANALOG_CTRL1_reg                                0xB8019108
#define TVD_VIDEO_ADC_ANALOG_CTRL1_inst_addr                          "0x0042"
#define TVD_VIDEO_ADC_ANALOG_CTRL1_inst                               0x0042
#define TVD_VIDEO_ADC_ANALOG_CTRL1_avrbl_shift                        (23)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_bvrbl_shift                        (20)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_cvrbl_shift                        (17)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_dvrbl_shift                        (14)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_svrbl_shift                        (11)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_clamp_enl_shift                    (7)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_sckinl_shift                       (5)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_sckol_shift                        (4)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_vicmpowl_shift                     (0)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_avrbl_mask                         (0x03800000)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_bvrbl_mask                         (0x00700000)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_cvrbl_mask                         (0x000E0000)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_dvrbl_mask                         (0x0001C000)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_svrbl_mask                         (0x00003800)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_clamp_enl_mask                     (0x00000780)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_sckinl_mask                        (0x00000060)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_sckol_mask                         (0x00000010)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_vicmpowl_mask                      (0x0000000F)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_avrbl(data)                        (0x03800000&((data)<<23))
#define TVD_VIDEO_ADC_ANALOG_CTRL1_bvrbl(data)                        (0x00700000&((data)<<20))
#define TVD_VIDEO_ADC_ANALOG_CTRL1_cvrbl(data)                        (0x000E0000&((data)<<17))
#define TVD_VIDEO_ADC_ANALOG_CTRL1_dvrbl(data)                        (0x0001C000&((data)<<14))
#define TVD_VIDEO_ADC_ANALOG_CTRL1_svrbl(data)                        (0x00003800&((data)<<11))
#define TVD_VIDEO_ADC_ANALOG_CTRL1_clamp_enl(data)                    (0x00000780&((data)<<7))
#define TVD_VIDEO_ADC_ANALOG_CTRL1_sckinl(data)                       (0x00000060&((data)<<5))
#define TVD_VIDEO_ADC_ANALOG_CTRL1_sckol(data)                        (0x00000010&((data)<<4))
#define TVD_VIDEO_ADC_ANALOG_CTRL1_vicmpowl(data)                     (0x0000000F&(data))
#define TVD_VIDEO_ADC_ANALOG_CTRL1_get_avrbl(data)                    ((0x03800000&(data))>>23)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_get_bvrbl(data)                    ((0x00700000&(data))>>20)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_get_cvrbl(data)                    ((0x000E0000&(data))>>17)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_get_dvrbl(data)                    ((0x0001C000&(data))>>14)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_get_svrbl(data)                    ((0x00003800&(data))>>11)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_get_clamp_enl(data)                ((0x00000780&(data))>>7)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_get_sckinl(data)                   ((0x00000060&(data))>>5)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_get_sckol(data)                    ((0x00000010&(data))>>4)
#define TVD_VIDEO_ADC_ANALOG_CTRL1_get_vicmpowl(data)                 (0x0000000F&(data))

#define TVD_VIDEO_ADC_ANALOG_CTRL2                                    0x1801910C
#define TVD_VIDEO_ADC_ANALOG_CTRL2_reg_addr                           "0xB801910C"
#define TVD_VIDEO_ADC_ANALOG_CTRL2_reg                                0xB801910C
#define TVD_VIDEO_ADC_ANALOG_CTRL2_inst_addr                          "0x0043"
#define TVD_VIDEO_ADC_ANALOG_CTRL2_inst                               0x0043
#define TVD_VIDEO_ADC_ANALOG_CTRL2_afepowl_shift                      (24)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_sadcinl_shift                      (20)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_vrefpowl_shift                     (15)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_avrtl_shift                        (12)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_bvrtl_shift                        (9)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_cvrtl_shift                        (6)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_dvrtl_shift                        (3)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_svrtl_shift                        (0)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_afepowl_mask                       (0x0F000000)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_sadcinl_mask                       (0x00F00000)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_vrefpowl_mask                      (0x000F8000)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_avrtl_mask                         (0x00007000)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_bvrtl_mask                         (0x00000E00)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_cvrtl_mask                         (0x000001C0)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_dvrtl_mask                         (0x00000038)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_svrtl_mask                         (0x00000007)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_afepowl(data)                      (0x0F000000&((data)<<24))
#define TVD_VIDEO_ADC_ANALOG_CTRL2_sadcinl(data)                      (0x00F00000&((data)<<20))
#define TVD_VIDEO_ADC_ANALOG_CTRL2_vrefpowl(data)                     (0x000F8000&((data)<<15))
#define TVD_VIDEO_ADC_ANALOG_CTRL2_avrtl(data)                        (0x00007000&((data)<<12))
#define TVD_VIDEO_ADC_ANALOG_CTRL2_bvrtl(data)                        (0x00000E00&((data)<<9))
#define TVD_VIDEO_ADC_ANALOG_CTRL2_cvrtl(data)                        (0x000001C0&((data)<<6))
#define TVD_VIDEO_ADC_ANALOG_CTRL2_dvrtl(data)                        (0x00000038&((data)<<3))
#define TVD_VIDEO_ADC_ANALOG_CTRL2_svrtl(data)                        (0x00000007&(data))
#define TVD_VIDEO_ADC_ANALOG_CTRL2_get_afepowl(data)                  ((0x0F000000&(data))>>24)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_get_sadcinl(data)                  ((0x00F00000&(data))>>20)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_get_vrefpowl(data)                 ((0x000F8000&(data))>>15)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_get_avrtl(data)                    ((0x00007000&(data))>>12)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_get_bvrtl(data)                    ((0x00000E00&(data))>>9)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_get_cvrtl(data)                    ((0x000001C0&(data))>>6)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_get_dvrtl(data)                    ((0x00000038&(data))>>3)
#define TVD_VIDEO_ADC_ANALOG_CTRL2_get_svrtl(data)                    (0x00000007&(data))

#define TVD_AD_SW_CTRL                                                0x18019110
#define TVD_AD_SW_CTRL_reg_addr                                       "0xB8019110"
#define TVD_AD_SW_CTRL_reg                                            0xB8019110
#define TVD_AD_SW_CTRL_inst_addr                                      "0x0044"
#define TVD_AD_SW_CTRL_inst                                           0x0044
#define TVD_AD_SW_CTRL_write_enable9_shift                            (23)
#define TVD_AD_SW_CTRL_fsw_en_shift                                   (22)
#define TVD_AD_SW_CTRL_write_enable8_shift                            (21)
#define TVD_AD_SW_CTRL_sw_y_r_shift                                   (19)
#define TVD_AD_SW_CTRL_write_enable7_shift                            (18)
#define TVD_AD_SW_CTRL_sw_pb_g_shift                                  (16)
#define TVD_AD_SW_CTRL_write_enable6_shift                            (15)
#define TVD_AD_SW_CTRL_sw_pr_b_shift                                  (13)
#define TVD_AD_SW_CTRL_write_enable5_shift                            (12)
#define TVD_AD_SW_CTRL_ad1_y_sw_shift                                 (11)
#define TVD_AD_SW_CTRL_write_enable4_shift                            (10)
#define TVD_AD_SW_CTRL_scart_en_shift                                 (9)
#define TVD_AD_SW_CTRL_write_enable3_shift                            (8)
#define TVD_AD_SW_CTRL_clamp_ad2_shift                                (6)
#define TVD_AD_SW_CTRL_write_enable2_shift                            (5)
#define TVD_AD_SW_CTRL_clamp_ad3_shift                                (3)
#define TVD_AD_SW_CTRL_write_enable1_shift                            (2)
#define TVD_AD_SW_CTRL_clamp_ad4_shift                                (0)
#define TVD_AD_SW_CTRL_write_enable9_mask                             (0x00800000)
#define TVD_AD_SW_CTRL_fsw_en_mask                                    (0x00400000)
#define TVD_AD_SW_CTRL_write_enable8_mask                             (0x00200000)
#define TVD_AD_SW_CTRL_sw_y_r_mask                                    (0x00180000)
#define TVD_AD_SW_CTRL_write_enable7_mask                             (0x00040000)
#define TVD_AD_SW_CTRL_sw_pb_g_mask                                   (0x00030000)
#define TVD_AD_SW_CTRL_write_enable6_mask                             (0x00008000)
#define TVD_AD_SW_CTRL_sw_pr_b_mask                                   (0x00006000)
#define TVD_AD_SW_CTRL_write_enable5_mask                             (0x00001000)
#define TVD_AD_SW_CTRL_ad1_y_sw_mask                                  (0x00000800)
#define TVD_AD_SW_CTRL_write_enable4_mask                             (0x00000400)
#define TVD_AD_SW_CTRL_scart_en_mask                                  (0x00000200)
#define TVD_AD_SW_CTRL_write_enable3_mask                             (0x00000100)
#define TVD_AD_SW_CTRL_clamp_ad2_mask                                 (0x000000C0)
#define TVD_AD_SW_CTRL_write_enable2_mask                             (0x00000020)
#define TVD_AD_SW_CTRL_clamp_ad3_mask                                 (0x00000018)
#define TVD_AD_SW_CTRL_write_enable1_mask                             (0x00000004)
#define TVD_AD_SW_CTRL_clamp_ad4_mask                                 (0x00000003)
#define TVD_AD_SW_CTRL_write_enable9(data)                            (0x00800000&((data)<<23))
#define TVD_AD_SW_CTRL_fsw_en(data)                                   (0x00400000&((data)<<22))
#define TVD_AD_SW_CTRL_write_enable8(data)                            (0x00200000&((data)<<21))
#define TVD_AD_SW_CTRL_sw_y_r(data)                                   (0x00180000&((data)<<19))
#define TVD_AD_SW_CTRL_write_enable7(data)                            (0x00040000&((data)<<18))
#define TVD_AD_SW_CTRL_sw_pb_g(data)                                  (0x00030000&((data)<<16))
#define TVD_AD_SW_CTRL_write_enable6(data)                            (0x00008000&((data)<<15))
#define TVD_AD_SW_CTRL_sw_pr_b(data)                                  (0x00006000&((data)<<13))
#define TVD_AD_SW_CTRL_write_enable5(data)                            (0x00001000&((data)<<12))
#define TVD_AD_SW_CTRL_ad1_y_sw(data)                                 (0x00000800&((data)<<11))
#define TVD_AD_SW_CTRL_write_enable4(data)                            (0x00000400&((data)<<10))
#define TVD_AD_SW_CTRL_scart_en(data)                                 (0x00000200&((data)<<9))
#define TVD_AD_SW_CTRL_write_enable3(data)                            (0x00000100&((data)<<8))
#define TVD_AD_SW_CTRL_clamp_ad2(data)                                (0x000000C0&((data)<<6))
#define TVD_AD_SW_CTRL_write_enable2(data)                            (0x00000020&((data)<<5))
#define TVD_AD_SW_CTRL_clamp_ad3(data)                                (0x00000018&((data)<<3))
#define TVD_AD_SW_CTRL_write_enable1(data)                            (0x00000004&((data)<<2))
#define TVD_AD_SW_CTRL_clamp_ad4(data)                                (0x00000003&(data))
#define TVD_AD_SW_CTRL_get_write_enable9(data)                        ((0x00800000&(data))>>23)
#define TVD_AD_SW_CTRL_get_fsw_en(data)                               ((0x00400000&(data))>>22)
#define TVD_AD_SW_CTRL_get_write_enable8(data)                        ((0x00200000&(data))>>21)
#define TVD_AD_SW_CTRL_get_sw_y_r(data)                               ((0x00180000&(data))>>19)
#define TVD_AD_SW_CTRL_get_write_enable7(data)                        ((0x00040000&(data))>>18)
#define TVD_AD_SW_CTRL_get_sw_pb_g(data)                              ((0x00030000&(data))>>16)
#define TVD_AD_SW_CTRL_get_write_enable6(data)                        ((0x00008000&(data))>>15)
#define TVD_AD_SW_CTRL_get_sw_pr_b(data)                              ((0x00006000&(data))>>13)
#define TVD_AD_SW_CTRL_get_write_enable5(data)                        ((0x00001000&(data))>>12)
#define TVD_AD_SW_CTRL_get_ad1_y_sw(data)                             ((0x00000800&(data))>>11)
#define TVD_AD_SW_CTRL_get_write_enable4(data)                        ((0x00000400&(data))>>10)
#define TVD_AD_SW_CTRL_get_scart_en(data)                             ((0x00000200&(data))>>9)
#define TVD_AD_SW_CTRL_get_write_enable3(data)                        ((0x00000100&(data))>>8)
#define TVD_AD_SW_CTRL_get_clamp_ad2(data)                            ((0x000000C0&(data))>>6)
#define TVD_AD_SW_CTRL_get_write_enable2(data)                        ((0x00000020&(data))>>5)
#define TVD_AD_SW_CTRL_get_clamp_ad3(data)                            ((0x00000018&(data))>>3)
#define TVD_AD_SW_CTRL_get_write_enable1(data)                        ((0x00000004&(data))>>2)
#define TVD_AD_SW_CTRL_get_clamp_ad4(data)                            (0x00000003&(data))

#define TVD_SCART_ACTIVE                                              0x18019114
#define TVD_SCART_ACTIVE_reg_addr                                     "0xB8019114"
#define TVD_SCART_ACTIVE_reg                                          0xB8019114
#define TVD_SCART_ACTIVE_inst_addr                                    "0x0045"
#define TVD_SCART_ACTIVE_inst                                         0x0045
#define TVD_SCART_ACTIVE_hst_shift                                    (22)
#define TVD_SCART_ACTIVE_hwidth_shift                                 (14)
#define TVD_SCART_ACTIVE_vst_shift                                    (7)
#define TVD_SCART_ACTIVE_vwidth_shift                                 (0)
#define TVD_SCART_ACTIVE_hst_mask                                     (0x3FC00000)
#define TVD_SCART_ACTIVE_hwidth_mask                                  (0x003FC000)
#define TVD_SCART_ACTIVE_vst_mask                                     (0x00003F80)
#define TVD_SCART_ACTIVE_vwidth_mask                                  (0x0000007F)
#define TVD_SCART_ACTIVE_hst(data)                                    (0x3FC00000&((data)<<22))
#define TVD_SCART_ACTIVE_hwidth(data)                                 (0x003FC000&((data)<<14))
#define TVD_SCART_ACTIVE_vst(data)                                    (0x00003F80&((data)<<7))
#define TVD_SCART_ACTIVE_vwidth(data)                                 (0x0000007F&(data))
#define TVD_SCART_ACTIVE_get_hst(data)                                ((0x3FC00000&(data))>>22)
#define TVD_SCART_ACTIVE_get_hwidth(data)                             ((0x003FC000&(data))>>14)
#define TVD_SCART_ACTIVE_get_vst(data)                                ((0x00003F80&(data))>>7)
#define TVD_SCART_ACTIVE_get_vwidth(data)                             (0x0000007F&(data))

#define TVD_CLAMP_EN_CTRL                                             0x18019118
#define TVD_CLAMP_EN_CTRL_reg_addr                                    "0xB8019118"
#define TVD_CLAMP_EN_CTRL_reg                                         0xB8019118
#define TVD_CLAMP_EN_CTRL_inst_addr                                   "0x0046"
#define TVD_CLAMP_EN_CTRL_inst                                        0x0046
#define TVD_CLAMP_EN_CTRL_clamp_a_up_en_shift                         (7)
#define TVD_CLAMP_EN_CTRL_clamp_a_dn_en_shift                         (6)
#define TVD_CLAMP_EN_CTRL_clamp_b_up_en_shift                         (5)
#define TVD_CLAMP_EN_CTRL_clamp_b_dn_en_shift                         (4)
#define TVD_CLAMP_EN_CTRL_clamp_c_up_en_shift                         (3)
#define TVD_CLAMP_EN_CTRL_clamp_c_dn_en_shift                         (2)
#define TVD_CLAMP_EN_CTRL_clamp_d_up_en_shift                         (1)
#define TVD_CLAMP_EN_CTRL_clamp_d_dn_en_shift                         (0)
#define TVD_CLAMP_EN_CTRL_clamp_a_up_en_mask                          (0x00000080)
#define TVD_CLAMP_EN_CTRL_clamp_a_dn_en_mask                          (0x00000040)
#define TVD_CLAMP_EN_CTRL_clamp_b_up_en_mask                          (0x00000020)
#define TVD_CLAMP_EN_CTRL_clamp_b_dn_en_mask                          (0x00000010)
#define TVD_CLAMP_EN_CTRL_clamp_c_up_en_mask                          (0x00000008)
#define TVD_CLAMP_EN_CTRL_clamp_c_dn_en_mask                          (0x00000004)
#define TVD_CLAMP_EN_CTRL_clamp_d_up_en_mask                          (0x00000002)
#define TVD_CLAMP_EN_CTRL_clamp_d_dn_en_mask                          (0x00000001)
#define TVD_CLAMP_EN_CTRL_clamp_a_up_en(data)                         (0x00000080&((data)<<7))
#define TVD_CLAMP_EN_CTRL_clamp_a_dn_en(data)                         (0x00000040&((data)<<6))
#define TVD_CLAMP_EN_CTRL_clamp_b_up_en(data)                         (0x00000020&((data)<<5))
#define TVD_CLAMP_EN_CTRL_clamp_b_dn_en(data)                         (0x00000010&((data)<<4))
#define TVD_CLAMP_EN_CTRL_clamp_c_up_en(data)                         (0x00000008&((data)<<3))
#define TVD_CLAMP_EN_CTRL_clamp_c_dn_en(data)                         (0x00000004&((data)<<2))
#define TVD_CLAMP_EN_CTRL_clamp_d_up_en(data)                         (0x00000002&((data)<<1))
#define TVD_CLAMP_EN_CTRL_clamp_d_dn_en(data)                         (0x00000001&(data))
#define TVD_CLAMP_EN_CTRL_get_clamp_a_up_en(data)                     ((0x00000080&(data))>>7)
#define TVD_CLAMP_EN_CTRL_get_clamp_a_dn_en(data)                     ((0x00000040&(data))>>6)
#define TVD_CLAMP_EN_CTRL_get_clamp_b_up_en(data)                     ((0x00000020&(data))>>5)
#define TVD_CLAMP_EN_CTRL_get_clamp_b_dn_en(data)                     ((0x00000010&(data))>>4)
#define TVD_CLAMP_EN_CTRL_get_clamp_c_up_en(data)                     ((0x00000008&(data))>>3)
#define TVD_CLAMP_EN_CTRL_get_clamp_c_dn_en(data)                     ((0x00000004&(data))>>2)
#define TVD_CLAMP_EN_CTRL_get_clamp_d_up_en(data)                     ((0x00000002&(data))>>1)
#define TVD_CLAMP_EN_CTRL_get_clamp_d_dn_en(data)                     (0x00000001&(data))

#define TVD_3B_ADC                                                    0x1801911C
#define TVD_3B_ADC_reg_addr                                           "0xB801911C"
#define TVD_3B_ADC_reg                                                0xB801911C
#define TVD_3B_ADC_inst_addr                                          "0x0047"
#define TVD_3B_ADC_inst                                               0x0047
#define TVD_3B_ADC_value_shift                                        (0)
#define TVD_3B_ADC_value_mask                                         (0x0000007F)
#define TVD_3B_ADC_value(data)                                        (0x0000007F&(data))
#define TVD_3B_ADC_get_value(data)                                    (0x0000007F&(data))

#define TVD_DEBUG                                                     0x18019120
#define TVD_DEBUG_reg_addr                                            "0xB8019120"
#define TVD_DEBUG_reg                                                 0xB8019120
#define TVD_DEBUG_inst_addr                                           "0x0048"
#define TVD_DEBUG_inst                                                0x0048
#define TVD_DEBUG_muxanalogb_shift                                    (8)
#define TVD_DEBUG_muxanaloga_shift                                    (4)
#define TVD_DEBUG_muxdigital_shift                                    (0)
#define TVD_DEBUG_muxanalogb_mask                                     (0x00000F00)
#define TVD_DEBUG_muxanaloga_mask                                     (0x000000F0)
#define TVD_DEBUG_muxdigital_mask                                     (0x0000000F)
#define TVD_DEBUG_muxanalogb(data)                                    (0x00000F00&((data)<<8))
#define TVD_DEBUG_muxanaloga(data)                                    (0x000000F0&((data)<<4))
#define TVD_DEBUG_muxdigital(data)                                    (0x0000000F&(data))
#define TVD_DEBUG_get_muxanalogb(data)                                ((0x00000F00&(data))>>8)
#define TVD_DEBUG_get_muxanaloga(data)                                ((0x000000F0&(data))>>4)
#define TVD_DEBUG_get_muxdigital(data)                                (0x0000000F&(data))

#define TVD_VCR_OPTION                                                0x18019128
#define TVD_VCR_OPTION_reg_addr                                       "0xB8019128"
#define TVD_VCR_OPTION_reg                                            0xB8019128
#define TVD_VCR_OPTION_inst_addr                                      "0x004A"
#define TVD_VCR_OPTION_inst                                           0x004A
#define TVD_VCR_OPTION_serration_thd_shift                            (3)
#define TVD_VCR_OPTION_lock_h_on_no_signal_shift                      (2)
#define TVD_VCR_OPTION_disable_blue_screen_when_vcr_shift             (1)
#define TVD_VCR_OPTION_detect_vcr_when_h_unlock_shift                 (0)
#define TVD_VCR_OPTION_serration_thd_mask                             (0x000007F8)
#define TVD_VCR_OPTION_lock_h_on_no_signal_mask                       (0x00000004)
#define TVD_VCR_OPTION_disable_blue_screen_when_vcr_mask              (0x00000002)
#define TVD_VCR_OPTION_detect_vcr_when_h_unlock_mask                  (0x00000001)
#define TVD_VCR_OPTION_serration_thd(data)                            (0x000007F8&((data)<<3))
#define TVD_VCR_OPTION_lock_h_on_no_signal(data)                      (0x00000004&((data)<<2))
#define TVD_VCR_OPTION_disable_blue_screen_when_vcr(data)             (0x00000002&((data)<<1))
#define TVD_VCR_OPTION_detect_vcr_when_h_unlock(data)                 (0x00000001&(data))
#define TVD_VCR_OPTION_get_serration_thd(data)                        ((0x000007F8&(data))>>3)
#define TVD_VCR_OPTION_get_lock_h_on_no_signal(data)                  ((0x00000004&(data))>>2)
#define TVD_VCR_OPTION_get_disable_blue_screen_when_vcr(data)         ((0x00000002&(data))>>1)
#define TVD_VCR_OPTION_get_detect_vcr_when_h_unlock(data)             (0x00000001&(data))

#define TVD_HV_MEASURE_1                                              0x1801912C
#define TVD_HV_MEASURE_1_reg_addr                                     "0xB801912C"
#define TVD_HV_MEASURE_1_reg                                          0xB801912C
#define TVD_HV_MEASURE_1_inst_addr                                    "0x004B"
#define TVD_HV_MEASURE_1_inst                                         0x004B
#define TVD_HV_MEASURE_1_first_v_shift                                (10)
#define TVD_HV_MEASURE_1_second_v_shift                               (0)
#define TVD_HV_MEASURE_1_first_v_mask                                 (0x000FFC00)
#define TVD_HV_MEASURE_1_second_v_mask                                (0x000003FF)
#define TVD_HV_MEASURE_1_first_v(data)                                (0x000FFC00&((data)<<10))
#define TVD_HV_MEASURE_1_second_v(data)                               (0x000003FF&(data))
#define TVD_HV_MEASURE_1_get_first_v(data)                            ((0x000FFC00&(data))>>10)
#define TVD_HV_MEASURE_1_get_second_v(data)                           (0x000003FF&(data))

#define TVD_HV_MEASURE_2                                              0x18019130
#define TVD_HV_MEASURE_2_reg_addr                                     "0xB8019130"
#define TVD_HV_MEASURE_2_reg                                          0xB8019130
#define TVD_HV_MEASURE_2_inst_addr                                    "0x004C"
#define TVD_HV_MEASURE_2_inst                                         0x004C
#define TVD_HV_MEASURE_2_count_shift                                  (13)
#define TVD_HV_MEASURE_2_hgt_shift                                    (0)
#define TVD_HV_MEASURE_2_count_mask                                   (0x001FE000)
#define TVD_HV_MEASURE_2_hgt_mask                                     (0x00001FFF)
#define TVD_HV_MEASURE_2_count(data)                                  (0x001FE000&((data)<<13))
#define TVD_HV_MEASURE_2_hgt(data)                                    (0x00001FFF&(data))
#define TVD_HV_MEASURE_2_get_count(data)                              ((0x001FE000&(data))>>13)
#define TVD_HV_MEASURE_2_get_hgt(data)                                (0x00001FFF&(data))

#define TVD_CRC_CTRL                                                  0x18019134
#define TVD_CRC_CTRL_reg_addr                                         "0xB8019134"
#define TVD_CRC_CTRL_reg                                              0xB8019134
#define TVD_CRC_CTRL_inst_addr                                        "0x004D"
#define TVD_CRC_CTRL_inst                                             0x004D
#define TVD_CRC_CTRL_crc_en_shift                                     (1)
#define TVD_CRC_CTRL_ptgen_en_shift                                   (0)
#define TVD_CRC_CTRL_crc_en_mask                                      (0x00000002)
#define TVD_CRC_CTRL_ptgen_en_mask                                    (0x00000001)
#define TVD_CRC_CTRL_crc_en(data)                                     (0x00000002&((data)<<1))
#define TVD_CRC_CTRL_ptgen_en(data)                                   (0x00000001&(data))
#define TVD_CRC_CTRL_get_crc_en(data)                                 ((0x00000002&(data))>>1)
#define TVD_CRC_CTRL_get_ptgen_en(data)                               (0x00000001&(data))

#define TVD_CRC_CHECKSUM                                              0x18019138
#define TVD_CRC_CHECKSUM_reg_addr                                     "0xB8019138"
#define TVD_CRC_CHECKSUM_reg                                          0xB8019138
#define TVD_CRC_CHECKSUM_inst_addr                                    "0x004E"
#define TVD_CRC_CHECKSUM_inst                                         0x004E
#define TVD_CRC_CHECKSUM_checksum_shift                               (0)
#define TVD_CRC_CHECKSUM_checksum_mask                                (0x0000FFFF)
#define TVD_CRC_CHECKSUM_checksum(data)                               (0x0000FFFF&(data))
#define TVD_CRC_CHECKSUM_get_checksum(data)                           (0x0000FFFF&(data))

#define TVD_RAW_MASK                                                  0x1801913C
#define TVD_RAW_MASK_reg_addr                                         "0xB801913C"
#define TVD_RAW_MASK_reg                                              0xB801913C
#define TVD_RAW_MASK_inst_addr                                        "0x004F"
#define TVD_RAW_MASK_inst                                             0x004F
#define TVD_RAW_MASK_mask_shift                                       (0)
#define TVD_RAW_MASK_mask_mask                                        (0x003FFFFF)
#define TVD_RAW_MASK_mask(data)                                       (0x003FFFFF&(data))
#define TVD_RAW_MASK_get_mask(data)                                   (0x003FFFFF&(data))

#define TVD_3D_VACTIVE1                                               0x18019140
#define TVD_3D_VACTIVE1_reg_addr                                      "0xB8019140"
#define TVD_3D_VACTIVE1_reg                                           0xB8019140
#define TVD_3D_VACTIVE1_inst_addr                                     "0x0050"
#define TVD_3D_VACTIVE1_inst                                          0x0050
#define TVD_3D_VACTIVE1_start_shift                                   (10)
#define TVD_3D_VACTIVE1_end_shift                                     (0)
#define TVD_3D_VACTIVE1_start_mask                                    (0x000FFC00)
#define TVD_3D_VACTIVE1_end_mask                                      (0x000003FF)
#define TVD_3D_VACTIVE1_start(data)                                   (0x000FFC00&((data)<<10))
#define TVD_3D_VACTIVE1_end(data)                                     (0x000003FF&(data))
#define TVD_3D_VACTIVE1_get_start(data)                               ((0x000FFC00&(data))>>10)
#define TVD_3D_VACTIVE1_get_end(data)                                 (0x000003FF&(data))

#define TVD_3D_VACTIVE2                                               0x18019144
#define TVD_3D_VACTIVE2_reg_addr                                      "0xB8019144"
#define TVD_3D_VACTIVE2_reg                                           0xB8019144
#define TVD_3D_VACTIVE2_inst_addr                                     "0x0051"
#define TVD_3D_VACTIVE2_inst                                          0x0051
#define TVD_3D_VACTIVE2_start_shift                                   (10)
#define TVD_3D_VACTIVE2_end_shift                                     (0)
#define TVD_3D_VACTIVE2_start_mask                                    (0x000FFC00)
#define TVD_3D_VACTIVE2_end_mask                                      (0x000003FF)
#define TVD_3D_VACTIVE2_start(data)                                   (0x000FFC00&((data)<<10))
#define TVD_3D_VACTIVE2_end(data)                                     (0x000003FF&(data))
#define TVD_3D_VACTIVE2_get_start(data)                               ((0x000FFC00&(data))>>10)
#define TVD_3D_VACTIVE2_get_end(data)                                 (0x000003FF&(data))

#define TVD_FRAME_ADDR0                                               0x18019148
#define TVD_FRAME_ADDR0_reg_addr                                      "0xB8019148"
#define TVD_FRAME_ADDR0_reg                                           0xB8019148
#define TVD_FRAME_ADDR0_inst_addr                                     "0x0052"
#define TVD_FRAME_ADDR0_inst                                          0x0052
#define TVD_FRAME_ADDR0_frame_adr0_shift                              (0)
#define TVD_FRAME_ADDR0_frame_adr0_mask                               (0x07FFFFFF)
#define TVD_FRAME_ADDR0_frame_adr0(data)                              (0x07FFFFFF&(data))
#define TVD_FRAME_ADDR0_get_frame_adr0(data)                          (0x07FFFFFF&(data))

#define TVD_FRAME_ADDR1                                               0x1801914C
#define TVD_FRAME_ADDR1_reg_addr                                      "0xB801914C"
#define TVD_FRAME_ADDR1_reg                                           0xB801914C
#define TVD_FRAME_ADDR1_inst_addr                                     "0x0053"
#define TVD_FRAME_ADDR1_inst                                          0x0053
#define TVD_FRAME_ADDR1_frame_adr1_shift                              (0)
#define TVD_FRAME_ADDR1_frame_adr1_mask                               (0x07FFFFFF)
#define TVD_FRAME_ADDR1_frame_adr1(data)                              (0x07FFFFFF&(data))
#define TVD_FRAME_ADDR1_get_frame_adr1(data)                          (0x07FFFFFF&(data))

#define TVD_DMA_CTRL                                                  0x18019150
#define TVD_DMA_CTRL_reg_addr                                         "0xB8019150"
#define TVD_DMA_CTRL_reg                                              0xB8019150
#define TVD_DMA_CTRL_inst_addr                                        "0x0054"
#define TVD_DMA_CTRL_inst                                             0x0054
#define TVD_DMA_CTRL_write_enable5_shift                              (26)
#define TVD_DMA_CTRL_dmaen_shift                                      (25)
#define TVD_DMA_CTRL_write_enable4_shift                              (24)
#define TVD_DMA_CTRL_ififo_thr_shift                                  (18)
#define TVD_DMA_CTRL_write_enable3_shift                              (17)
#define TVD_DMA_CTRL_ofifo_thr_shift                                  (11)
#define TVD_DMA_CTRL_write_enable2_shift                              (10)
#define TVD_DMA_CTRL_ceiladr_shift                                    (4)
#define TVD_DMA_CTRL_write_enable1_shift                              (3)
#define TVD_DMA_CTRL_bstlen_shift                                     (0)
#define TVD_DMA_CTRL_write_enable5_mask                               (0x04000000)
#define TVD_DMA_CTRL_dmaen_mask                                       (0x02000000)
#define TVD_DMA_CTRL_write_enable4_mask                               (0x01000000)
#define TVD_DMA_CTRL_ififo_thr_mask                                   (0x00FC0000)
#define TVD_DMA_CTRL_write_enable3_mask                               (0x00020000)
#define TVD_DMA_CTRL_ofifo_thr_mask                                   (0x0001F800)
#define TVD_DMA_CTRL_write_enable2_mask                               (0x00000400)
#define TVD_DMA_CTRL_ceiladr_mask                                     (0x000003F0)
#define TVD_DMA_CTRL_write_enable1_mask                               (0x00000008)
#define TVD_DMA_CTRL_bstlen_mask                                      (0x00000007)
#define TVD_DMA_CTRL_write_enable5(data)                              (0x04000000&((data)<<26))
#define TVD_DMA_CTRL_dmaen(data)                                      (0x02000000&((data)<<25))
#define TVD_DMA_CTRL_write_enable4(data)                              (0x01000000&((data)<<24))
#define TVD_DMA_CTRL_ififo_thr(data)                                  (0x00FC0000&((data)<<18))
#define TVD_DMA_CTRL_write_enable3(data)                              (0x00020000&((data)<<17))
#define TVD_DMA_CTRL_ofifo_thr(data)                                  (0x0001F800&((data)<<11))
#define TVD_DMA_CTRL_write_enable2(data)                              (0x00000400&((data)<<10))
#define TVD_DMA_CTRL_ceiladr(data)                                    (0x000003F0&((data)<<4))
#define TVD_DMA_CTRL_write_enable1(data)                              (0x00000008&((data)<<3))
#define TVD_DMA_CTRL_bstlen(data)                                     (0x00000007&(data))
#define TVD_DMA_CTRL_get_write_enable5(data)                          ((0x04000000&(data))>>26)
#define TVD_DMA_CTRL_get_dmaen(data)                                  ((0x02000000&(data))>>25)
#define TVD_DMA_CTRL_get_write_enable4(data)                          ((0x01000000&(data))>>24)
#define TVD_DMA_CTRL_get_ififo_thr(data)                              ((0x00FC0000&(data))>>18)
#define TVD_DMA_CTRL_get_write_enable3(data)                          ((0x00020000&(data))>>17)
#define TVD_DMA_CTRL_get_ofifo_thr(data)                              ((0x0001F800&(data))>>11)
#define TVD_DMA_CTRL_get_write_enable2(data)                          ((0x00000400&(data))>>10)
#define TVD_DMA_CTRL_get_ceiladr(data)                                ((0x000003F0&(data))>>4)
#define TVD_DMA_CTRL_get_write_enable1(data)                          ((0x00000008&(data))>>3)
#define TVD_DMA_CTRL_get_bstlen(data)                                 (0x00000007&(data))

#define TVD_DMA_ERR                                                   0x18019154
#define TVD_DMA_ERR_reg_addr                                          "0xB8019154"
#define TVD_DMA_ERR_reg                                               0xB8019154
#define TVD_DMA_ERR_inst_addr                                         "0x0055"
#define TVD_DMA_ERR_inst                                              0x0055
#define TVD_DMA_ERR_ififo_err_shift                                   (1)
#define TVD_DMA_ERR_ofifo_err_shift                                   (0)
#define TVD_DMA_ERR_ififo_err_mask                                    (0x00000002)
#define TVD_DMA_ERR_ofifo_err_mask                                    (0x00000001)
#define TVD_DMA_ERR_ififo_err(data)                                   (0x00000002&((data)<<1))
#define TVD_DMA_ERR_ofifo_err(data)                                   (0x00000001&(data))
#define TVD_DMA_ERR_get_ififo_err(data)                               ((0x00000002&(data))>>1)
#define TVD_DMA_ERR_get_ofifo_err(data)                               (0x00000001&(data))

#define TVD_IPCNT                                                     0x18019158
#define TVD_IPCNT_reg_addr                                            "0xB8019158"
#define TVD_IPCNT_reg                                                 0xB8019158
#define TVD_IPCNT_inst_addr                                           "0x0056"
#define TVD_IPCNT_inst                                                0x0056
#define TVD_IPCNT_hcnt_shift                                          (10)
#define TVD_IPCNT_vcnt_shift                                          (0)
#define TVD_IPCNT_hcnt_mask                                           (0x000FFC00)
#define TVD_IPCNT_vcnt_mask                                           (0x000003FF)
#define TVD_IPCNT_hcnt(data)                                          (0x000FFC00&((data)<<10))
#define TVD_IPCNT_vcnt(data)                                          (0x000003FF&(data))
#define TVD_IPCNT_get_hcnt(data)                                      ((0x000FFC00&(data))>>10)
#define TVD_IPCNT_get_vcnt(data)                                      (0x000003FF&(data))

#define TVD_IP_RESET                                                  0x1801915C
#define TVD_IP_RESET_reg_addr                                         "0xB801915C"
#define TVD_IP_RESET_reg                                              0xB801915C
#define TVD_IP_RESET_inst_addr                                        "0x0057"
#define TVD_IP_RESET_inst                                             0x0057
#define TVD_IP_RESET_iprstn_shift                                     (0)
#define TVD_IP_RESET_iprstn_mask                                      (0x00000001)
#define TVD_IP_RESET_iprstn(data)                                     (0x00000001&(data))
#define TVD_IP_RESET_get_iprstn(data)                                 (0x00000001&(data))

#define TVD_ADC_SAMPLE                                                0x18019160
#define TVD_ADC_SAMPLE_reg_addr                                       "0xB8019160"
#define TVD_ADC_SAMPLE_reg                                            0xB8019160
#define TVD_ADC_SAMPLE_inst_addr                                      "0x0058"
#define TVD_ADC_SAMPLE_inst                                           0x0058
#define TVD_ADC_SAMPLE_edge_sel4_shift                                (3)
#define TVD_ADC_SAMPLE_edge_sel3_shift                                (2)
#define TVD_ADC_SAMPLE_edge_sel2_shift                                (1)
#define TVD_ADC_SAMPLE_edge_sel1_shift                                (0)
#define TVD_ADC_SAMPLE_edge_sel4_mask                                 (0x00000008)
#define TVD_ADC_SAMPLE_edge_sel3_mask                                 (0x00000004)
#define TVD_ADC_SAMPLE_edge_sel2_mask                                 (0x00000002)
#define TVD_ADC_SAMPLE_edge_sel1_mask                                 (0x00000001)
#define TVD_ADC_SAMPLE_edge_sel4(data)                                (0x00000008&((data)<<3))
#define TVD_ADC_SAMPLE_edge_sel3(data)                                (0x00000004&((data)<<2))
#define TVD_ADC_SAMPLE_edge_sel2(data)                                (0x00000002&((data)<<1))
#define TVD_ADC_SAMPLE_edge_sel1(data)                                (0x00000001&(data))
#define TVD_ADC_SAMPLE_get_edge_sel4(data)                            ((0x00000008&(data))>>3)
#define TVD_ADC_SAMPLE_get_edge_sel3(data)                            ((0x00000004&(data))>>2)
#define TVD_ADC_SAMPLE_get_edge_sel2(data)                            ((0x00000002&(data))>>1)
#define TVD_ADC_SAMPLE_get_edge_sel1(data)                            (0x00000001&(data))
#endif
