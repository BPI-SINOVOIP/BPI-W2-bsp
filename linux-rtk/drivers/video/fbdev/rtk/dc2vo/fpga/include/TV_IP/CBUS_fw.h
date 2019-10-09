// This file is generated using the spec version 1.39, firmware template version 1.39and SRIF Parser                                                                                source code SVN rev:802                    Version flow no.:1.1.66
#ifndef _CBUS_REG_H_INCLUDED_
#define _CBUS_REG_H_INCLUDED_

//#define  _CBUS_USE_STRUCT
#ifdef _CBUS_USE_STRUCT

typedef struct
{
    unsigned int    reserved_0:28;
    unsigned int    wake_pulse_det:1;
    unsigned int    dis_pulse_det:1;
    unsigned int    wake_irq_en:1;
    unsigned int    dis_irq_en:1;
}CBUS_standby_00;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    clk_1m_div:4;
    unsigned int    clk_1k_div:10;
}CBUS_standby_01;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    dis_deb_lv:3;
    unsigned int    deb_lv:3;
    unsigned int    disconn:2;
}CBUS_standby_02;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    wake_offset_low2:3;
    unsigned int    wake_offset_low:3;
    unsigned int    wake_cnt:3;
    unsigned int    wake_offset:3;
    unsigned int    cbus_disconn:1;
    unsigned int    disconn_irq_en:1;
}CBUS_standby_04;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    dis_upper:4;
    unsigned int    dis_lower:3;
    unsigned int    wake_eco_en:1;
}CBUS_standby_05;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    wake_num:3;
    unsigned int    dis_num:5;
}CBUS_standby_06;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    cbus_imp_auto:1;
    unsigned int    bypass_mode:1;
    unsigned int    sink_fsm_st:3;
    unsigned int    cbus_100k_en:1;
    unsigned int    cbus_1k_en:1;
    unsigned int    cbus_in_sig:1;
}CBUS_standby_07;

typedef struct
{
    unsigned int    reserved_0:26;
    unsigned int    goto_sink1_pos:1;
    unsigned int    goto_float:1;
    unsigned int    goto_sink1:1;
    unsigned int    cable_det:1;
    unsigned int    reserved_1:1;
    unsigned int    dbg_sel_phy:1;
}CBUS_standby_08;

typedef struct
{
    unsigned int    ctrl_09_resv:32;
}CBUS_standby_09;

typedef struct
{
    unsigned int    reserved_0:25;
    unsigned int    cbus_sr:1;
    unsigned int    cbus_smt:1;
    unsigned int    cbus_pu:1;
    unsigned int    cbus_pd:1;
    unsigned int    cbus_i:1;
    unsigned int    cbus_e2:1;
    unsigned int    cbus_e:1;
}CBUS_phy_0;

typedef struct
{
    unsigned int    adjr_1k:4;
    unsigned int    adjr_100k:5;
    unsigned int    auto_k_1k:1;
    unsigned int    auto_k_100k:1;
    unsigned int    en_res_cal_cbus:1;
    unsigned int    sel_cbus0_input_high:2;
    unsigned int    sel_cbus0_input_low:2;
    unsigned int    sel_cbus_0_driving:3;
    unsigned int    sel_vref_ldo:2;
    unsigned int    trim_ldo_cbus:4;
    unsigned int    triming_mode:1;
    unsigned int    en_cbus:1;
    unsigned int    en_cmp_cbus:1;
    unsigned int    en_driver_cbus:1;
    unsigned int    en_ldo_cbus:1;
    unsigned int    psm_cbus:1;
    unsigned int    sel_cbusb_gpio:1;
}CBUS_phy_1;

typedef struct
{
    unsigned int    reserved_0:31;
    unsigned int    cbus_o:1;
}CBUS_phy_2;

typedef struct
{
    unsigned int    reserved_0:20;
    unsigned int    sel_phy_soft_rst_n:1;
    unsigned int    cbus_res_tst:10;
    unsigned int    res_ok:1;
}CBUS_phy_3;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    dev_state:8;
}MSC_reg_00;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    mhl_ver:8;
}MSC_reg_01;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    dev_cat:1;
    unsigned int    plim:2;
    unsigned int    pow:1;
    unsigned int    dev_type:4;
}MSC_reg_02;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    adop_id_h:8;
}MSC_reg_03;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    adop_id_l:8;
}MSC_reg_04;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    vid_link_md:2;
    unsigned int    supp_vga:1;
    unsigned int    supp_islands:1;
    unsigned int    supp_ppixel:1;
    unsigned int    supp_yuv422:1;
    unsigned int    supp_yuv444:1;
    unsigned int    supp_rgb444:1;
}MSC_reg_05;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    aud_link_md:6;
    unsigned int    aud_8ch:1;
    unsigned int    aud_2ch:1;
}MSC_reg_06;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    supp_vt:1;
    unsigned int    video_type:3;
    unsigned int    vt_game:1;
    unsigned int    vt_cinema:1;
    unsigned int    vt_photo:1;
    unsigned int    vt_graphics:1;
}MSC_reg_07;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    ld_gui:1;
    unsigned int    ld_speaker:1;
    unsigned int    ld_record:1;
    unsigned int    ld_tuner:1;
    unsigned int    ld_media:1;
    unsigned int    ld_audio:1;
    unsigned int    ld_video:1;
    unsigned int    ld_display:1;
}MSC_reg_08;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    bandwid:8;
}MSC_reg_09;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    feature_flag:3;
    unsigned int    ucp_recv_supp:1;
    unsigned int    ucp_send_supp:1;
    unsigned int    sp_supp:1;
    unsigned int    rap_supp:1;
    unsigned int    rcp_supp:1;
}MSC_reg_0a;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    device_id_h:8;
}MSC_reg_0b;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    device_id_l:8;
}MSC_reg_0c;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scr_size:8;
}MSC_reg_0d;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    stat_size:4;
    unsigned int    int_size:4;
}MSC_reg_0e;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    cap_0f:8;
}MSC_reg_0f;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    rchg_int_7:1;
    unsigned int    rchg_int_6:1;
    unsigned int    rchg_int_5:1;
    unsigned int    cbus_3d_req:1;
    unsigned int    grt_wrt:1;
    unsigned int    req_wrt:1;
    unsigned int    dscr_chg:1;
    unsigned int    dcap_chg:1;
}MSC_reg_20;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    dchg_int_7:1;
    unsigned int    dchg_int_6:1;
    unsigned int    dchg_int_5:1;
    unsigned int    dchg_int_4:1;
    unsigned int    dchg_int_3:1;
    unsigned int    dchg_int_2:1;
    unsigned int    edid_chg:1;
    unsigned int    dchg_int_0:1;
}MSC_reg_21;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    chg22_7:1;
    unsigned int    chg22_6:1;
    unsigned int    chg22_5:1;
    unsigned int    chg22_4:1;
    unsigned int    chg22_3:1;
    unsigned int    chg22_2:1;
    unsigned int    chg22_1:1;
    unsigned int    chg22_0:1;
}MSC_reg_22;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    chg23_7:1;
    unsigned int    chg23_6:1;
    unsigned int    chg23_5:1;
    unsigned int    chg23_4:1;
    unsigned int    chg23_3:1;
    unsigned int    chg23_2:1;
    unsigned int    chg23_1:1;
    unsigned int    chg23_0:1;
}MSC_reg_23;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    chg24_7:1;
    unsigned int    chg24_6:1;
    unsigned int    chg24_5:1;
    unsigned int    chg24_4:1;
    unsigned int    chg24_3:1;
    unsigned int    chg24_2:1;
    unsigned int    chg24_1:1;
    unsigned int    chg24_0:1;
}MSC_reg_24;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    chg25_7:1;
    unsigned int    chg25_6:1;
    unsigned int    chg25_5:1;
    unsigned int    chg25_4:1;
    unsigned int    chg25_3:1;
    unsigned int    chg25_2:1;
    unsigned int    chg25_1:1;
    unsigned int    chg25_0:1;
}MSC_reg_25;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    chg26_7:1;
    unsigned int    chg26_6:1;
    unsigned int    chg26_5:1;
    unsigned int    chg26_4:1;
    unsigned int    chg26_3:1;
    unsigned int    chg26_2:1;
    unsigned int    chg26_1:1;
    unsigned int    chg26_0:1;
}MSC_reg_26;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    chg27_7:1;
    unsigned int    chg27_6:1;
    unsigned int    chg27_5:1;
    unsigned int    chg27_4:1;
    unsigned int    chg27_3:1;
    unsigned int    chg27_2:1;
    unsigned int    chg27_1:1;
    unsigned int    chg27_0:1;
}MSC_reg_27;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    conn_rdy:7;
    unsigned int    dcap_rdy:1;
}MSC_reg_30;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    link_mode:3;
    unsigned int    muted:1;
    unsigned int    path_en:1;
    unsigned int    clk_mode:3;
}MSC_reg_31;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    stat_32:8;
}MSC_reg_32;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    stat_33:8;
}MSC_reg_33;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    stat_34:8;
}MSC_reg_34;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    stat_35:8;
}MSC_reg_35;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    stat_36:8;
}MSC_reg_36;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    stat_37:8;
}MSC_reg_37;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_40:8;
}MSC_reg_40;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_41:8;
}MSC_reg_41;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_42:8;
}MSC_reg_42;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_43:8;
}MSC_reg_43;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_44:8;
}MSC_reg_44;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_45:8;
}MSC_reg_45;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_46:8;
}MSC_reg_46;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_47:8;
}MSC_reg_47;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_48:8;
}MSC_reg_48;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_49:8;
}MSC_reg_49;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_4a:8;
}MSC_reg_4a;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_4b:8;
}MSC_reg_4b;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_4c:8;
}MSC_reg_4c;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_4d:8;
}MSC_reg_4d;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_4e:8;
}MSC_reg_4e;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_4f:8;
}MSC_reg_4f;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_50:8;
}MSC_reg_50;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_51:8;
}MSC_reg_51;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_52:8;
}MSC_reg_52;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_53:8;
}MSC_reg_53;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_54:8;
}MSC_reg_54;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_55:8;
}MSC_reg_55;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_56:8;
}MSC_reg_56;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_57:8;
}MSC_reg_57;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_58:8;
}MSC_reg_58;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_59:8;
}MSC_reg_59;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_5a:8;
}MSC_reg_5a;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_5b:8;
}MSC_reg_5b;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_5c:8;
}MSC_reg_5c;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_5d:8;
}MSC_reg_5d;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_5e:8;
}MSC_reg_5e;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scratch_5f:8;
}MSC_reg_5f;

typedef struct
{
    unsigned int    reserved_0:14;
    unsigned int    sync0_hb_8_0:9;
    unsigned int    sync0_lb_8_0:9;
}CBUS_link_00;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    sync1_hb_7_0:8;
    unsigned int    sync1_lb_7_0:8;
}CBUS_link_01;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    sync_bit_time:8;
}CBUS_link_02;

typedef struct
{
    unsigned int    reserved_0:23;
    unsigned int    abs_thres_en:1;
    unsigned int    abs_threshold:8;
}CBUS_link_03;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    parity_time:8;
}CBUS_link_04;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    parity_fail:1;
    unsigned int    parity_irq_en:1;
    unsigned int    ctrl_16_resv:1;
    unsigned int    parity_limit:5;
}CBUS_link_05;

typedef struct
{
    unsigned int    reserved_0:25;
    unsigned int    ack_fall:7;
}CBUS_link_06;

typedef struct
{
    unsigned int    reserved_0:25;
    unsigned int    ack_0:7;
}CBUS_link_07;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    tx_bit_time:8;
}CBUS_link_08;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    chk_win_up:3;
    unsigned int    chk_win_lo:2;
    unsigned int    fast_reply_en:1;
    unsigned int    ctrl_1b_resv:2;
}CBUS_link_09;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    reserved_1:1;
    unsigned int    tx_ack_fal:7;
}CBUS_link_0a;

typedef struct
{
    unsigned int    reserved_0:25;
    unsigned int    tx_ack_low_hb:7;
}CBUS_link_0b;

typedef struct
{
    unsigned int    reserved_0:25;
    unsigned int    tx_ack_low_lb:7;
}CBUS_link_0c;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    retry_lv:3;
    unsigned int    retry_flag:1;
    unsigned int    ctrl_1f_resv:4;
}CBUS_link_0d;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    drv_str:2;
    unsigned int    drv_hi_cbus:6;
}CBUS_link_0e;

typedef struct
{
    unsigned int    reserved_0:26;
    unsigned int    wait:4;
    unsigned int    req_opp_int:2;
}CBUS_link_0f;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    req_opp_flt:8;
}CBUS_link_10;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    req_cont:8;
}CBUS_link_11;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    req_hold:4;
    unsigned int    resp_hold:4;
}CBUS_link_12;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    glob_time:2;
    unsigned int    link_time:5;
    unsigned int    link_err:1;
}CBUS_link_13;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    chk_point:6;
    unsigned int    chk_err:1;
    unsigned int    avoid_conf:1;
}CBUS_link_14;

typedef struct
{
    unsigned int    reserved_0:26;
    unsigned int    mcumsc_en:1;
    unsigned int    msc_wait_arb:1;
    unsigned int    ctrl_28_resv:4;
}CBUS_msc_00;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    na_msc_cmd:8;
}CBUS_msc_01;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    na_msc_offset:8;
}CBUS_msc_02;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    rx_fifo_full:1;
    unsigned int    rx_fifo_empty:1;
    unsigned int    rx_fifo_clr:1;
    unsigned int    na_rx_len:5;
}CBUS_msc_03;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    rx_fifo_data:8;
}CBUS_msc_04;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fwdef_cmd_rev:8;
}CBUS_msc_05;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    ucp_irq:1;
    unsigned int    ucpk_irq:1;
    unsigned int    ucpe_irq:1;
    unsigned int    dcap_rdy_chg:1;
    unsigned int    muted_chg:1;
    unsigned int    path_en_chg:1;
    unsigned int    clk_mode_chg:1;
    unsigned int    msge_irq:1;
    unsigned int    rcp_irq:1;
    unsigned int    rcpk_irq:1;
    unsigned int    rcpe_irq:1;
    unsigned int    rap_irq:1;
    unsigned int    rapk_irq:1;
    unsigned int    msg_sub_irq:1;
    unsigned int    wr_stat_irq:1;
    unsigned int    rd_devcap_irq:1;
    unsigned int    get_stat_irq:1;
    unsigned int    get_id_irq:1;
    unsigned int    get_msg_irq:1;
    unsigned int    sc1_err_irq:1;
    unsigned int    ddc_err_irq:1;
    unsigned int    msc_err_irq:1;
    unsigned int    wr_burst_irq:1;
    unsigned int    sc3_err_irq:1;
    unsigned int    fwdef_cmd_irq:1;
    unsigned int    allmsc_cmd_irq:1;
    unsigned int    abort_res_irq:1;
    unsigned int    abort_req_irq:1;
    unsigned int    ddc_abort_irq:1;
}CBUS_msc_06;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    ucp_irq_en:1;
    unsigned int    ucpk_irq_en:1;
    unsigned int    ucpe_irq_en:1;
    unsigned int    dcap_rdy_irq_en:1;
    unsigned int    muted_chg_irq_en:1;
    unsigned int    path_en_irq_en:1;
    unsigned int    clk_mode_irq_en:1;
    unsigned int    msge_irq_en:1;
    unsigned int    rcp_irq_en:1;
    unsigned int    rcpk_irq_en:1;
    unsigned int    rcpe_irq_en:1;
    unsigned int    rap_irq_en:1;
    unsigned int    rapk_irq_en:1;
    unsigned int    msg_sub_irq_en:1;
    unsigned int    wr_stat_irq_en:1;
    unsigned int    rd_devcap_irq_en:1;
    unsigned int    get_stat_irq_en:1;
    unsigned int    get_id_irq_en:1;
    unsigned int    get_msg_irq_en:1;
    unsigned int    sc1_err_irq_en:1;
    unsigned int    ddc_err_irq_en:1;
    unsigned int    msc_err_irq_en:1;
    unsigned int    wr_burst_irq_en:1;
    unsigned int    sc3_err_irq_en:1;
    unsigned int    fwdef_cmd_irq_en:1;
    unsigned int    allmsc_cmd_irq_en:1;
    unsigned int    abort_res_irq_en:1;
    unsigned int    abort_req_irq_en:1;
    unsigned int    ddc_abort_irq_en:1;
}CBUS_msc_07;

typedef struct
{
    unsigned int    rchg_irq_en:3;
    unsigned int    cbus_3d_req_irq_en:1;
    unsigned int    grt_irq_en:1;
    unsigned int    req_irq_en:1;
    unsigned int    dscr_irq_en:1;
    unsigned int    dcap_irq_en:1;
    unsigned int    dchg_bit7_irq_en:1;
    unsigned int    dchg_bit6_irq_en:1;
    unsigned int    dchg_bit5_irq_en:1;
    unsigned int    dchg_bit4_irq_en:1;
    unsigned int    dchg_bit3_irq_en:1;
    unsigned int    dchg_bit2_irq_en:1;
    unsigned int    edid_irq_en:1;
    unsigned int    dchg_bit0_irq_en:1;
    unsigned int    chg22_irq_en:8;
    unsigned int    chg23_irq_en:8;
}CBUS_msc_08;

typedef struct
{
    unsigned int    chg24_irq_en:8;
    unsigned int    chg25_irq_en:8;
    unsigned int    chg26_irq_en:8;
    unsigned int    chg27_irq_en:8;
}CBUS_msc_09;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    msc_err_code:8;
}CBUS_msc_0a;

typedef struct
{
    unsigned int    reserved_0:22;
    unsigned int    rcp_reply_abort:1;
    unsigned int    rcp_reply_nack:1;
    unsigned int    vendor_id:8;
}CBUS_msc_0b;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    msg_cmd:8;
}CBUS_msc_0c;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    msg_dat:8;
}CBUS_msc_0d;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    msge_rcv:8;
}CBUS_msc_0e;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    rcp_rcv:8;
}CBUS_msc_0f;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    rcpk_rcv:8;
}CBUS_msc_10;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    rcpe_rcv:8;
}CBUS_msc_11;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    rap_rcv:8;
}CBUS_msc_12;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    rapk_rcv:8;
}CBUS_msc_13;

typedef struct
{
    unsigned int    reserved_0:26;
    unsigned int    burst_timeout:1;
    unsigned int    wb_id_chk:1;
    unsigned int    burst_wait:4;
}CBUS_msc_14;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    adop_idh_rcv:8;
    unsigned int    adop_idl_rcv:8;
}CBUS_msc_15;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    auto_handshake:1;
    unsigned int    insert_id:1;
    unsigned int    wb_byte_num0:6;
    unsigned int    wb_byte_num1:6;
    unsigned int    adop_txid_h:8;
    unsigned int    adop_txid_l:8;
}CBUS_msc_16;

typedef struct
{
    unsigned int    reserved_0:29;
    unsigned int    que_fsm_clr:1;
    unsigned int    sch_fsm_clr:1;
    unsigned int    spi_fsm_clr:1;
}CBUS_msc_17;

typedef struct
{
    unsigned int    reserved_0:20;
    unsigned int    que_fsm:4;
    unsigned int    sch_fsm:4;
    unsigned int    spi_fsm:4;
}CBUS_msc_18;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    cap_offset:8;
}CBUS_msc_19;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    int_offset:8;
}CBUS_msc_1a;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    sta_offset:8;
}CBUS_msc_1b;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    scr_offset:8;
}CBUS_msc_1c;

typedef struct
{
    unsigned int    reserved_0:30;
    unsigned int    ddc_err_force:1;
    unsigned int    msc_err_force:1;
}CBUS_msc_1d;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    ddc_err_fw:8;
}CBUS_msc_1e;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    msc_err_fw:8;
}CBUS_msc_1f;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    ucp_rcv:8;
}CBUS_msc_20;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    ucpk_rcv:8;
}CBUS_msc_21;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    ucpe_rcv:8;
}CBUS_msc_22;

typedef struct
{
    unsigned int    reserved_0:23;
    unsigned int    fw0_req:1;
    unsigned int    fw0_fifo_clr:1;
    unsigned int    fw0_fifo_full:1;
    unsigned int    fw0_fifo_empty:1;
    unsigned int    fw0_tx_case:3;
    unsigned int    fw0_head:2;
}FW0_req_00;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw0_cmd1:8;
}FW0_req_01;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw0_cmd2:8;
}FW0_req_02;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw0_offset:8;
}FW0_req_03;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw0_data:8;
}FW0_req_04;

typedef struct
{
    unsigned int    reserved_0:22;
    unsigned int    fw0_rty_ovr:1;
    unsigned int    fw0_fin:1;
    unsigned int    fw0_cmd_event:1;
    unsigned int    fw0_data_event:1;
    unsigned int    fw0_rcv_err:1;
    unsigned int    fw0_fin_irq_en:1;
    unsigned int    fw0_cmd_irq_en:1;
    unsigned int    fw0_data_irq_en:1;
    unsigned int    fw0_wait_case:2;
}FW0_req_05;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw0_cmd_rcv:8;
}FW0_req_06;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw0_data_rcv:8;
}FW0_req_07;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    fw0_rd_en:1;
    unsigned int    fw0_fifo_len:5;
    unsigned int    fw0_rdata:8;
}FW0_req_08;

typedef struct
{
    unsigned int    reserved_0:23;
    unsigned int    fw1_req:1;
    unsigned int    fw1_fifo_clr:1;
    unsigned int    fw1_fifo_full:1;
    unsigned int    fw1_fifo_empty:1;
    unsigned int    fw1_tx_case:3;
    unsigned int    fw1_head:2;
}FW1_req_00;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw1_cmd1:8;
}FW1_req_01;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw1_cmd2:8;
}FW1_req_02;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw1_offset:8;
}FW1_req_03;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw1_data:8;
}FW1_req_04;

typedef struct
{
    unsigned int    reserved_0:22;
    unsigned int    fw1_rty_ovr:1;
    unsigned int    fw1_fin:1;
    unsigned int    fw1_cmd_event:1;
    unsigned int    fw1_data_event:1;
    unsigned int    fw1_rcv_err:1;
    unsigned int    fw1_fin_irq_en:1;
    unsigned int    fw1_cmd_irq_en:1;
    unsigned int    fw1_data_irq_en:1;
    unsigned int    fw1_wait_case:2;
}FW1_req_05;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw1_cmd_rcv:8;
}FW1_req_06;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw1_data_rcv:8;
}FW1_req_07;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    fw1_rd_en:1;
    unsigned int    fw1_fifo_len:5;
    unsigned int    fw1_rdata:8;
}FW1_req_08;

typedef struct
{
    unsigned int    reserved_0:23;
    unsigned int    fw2_req:1;
    unsigned int    fw2_fifo_clr:1;
    unsigned int    fw2_fifo_full:1;
    unsigned int    fw2_fifo_empty:1;
    unsigned int    fw2_tx_case:3;
    unsigned int    fw2_head:2;
}FW2_req_00;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw2_cmd1:8;
}FW2_req_01;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw2_cmd2:8;
}FW2_req_02;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw2_offset:8;
}FW2_req_03;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw2_data:8;
}FW2_req_04;

typedef struct
{
    unsigned int    reserved_0:22;
    unsigned int    fw2_rty_ovr:1;
    unsigned int    fw2_fin:1;
    unsigned int    fw2_cmd_event:1;
    unsigned int    fw2_data_event:1;
    unsigned int    fw2_rcv_err:1;
    unsigned int    fw2_fin_irq_en:1;
    unsigned int    fw2_cmd_irq_en:1;
    unsigned int    fw2_data_irq_en:1;
    unsigned int    fw2_wait_case:2;
}FW2_req_05;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw2_cmd_rcv:8;
}FW2_req_06;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    fw2_data_rcv:8;
}FW2_req_07;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    fw2_rd_en:1;
    unsigned int    fw2_fifo_len:5;
    unsigned int    fw2_rdata:8;
}FW2_req_08;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    ddc_err_code:8;
}CBUS_ddc_00;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    iic_ck_tgt:8;
}CBUS_ddc_01;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    mcuddc_en:1;
    unsigned int    ddc_prior_dis:1;
    unsigned int    ddc_cmd_event:1;
    unsigned int    ddc_data_event:1;
    unsigned int    ddc_cmd_irq_en:1;
    unsigned int    ddc_data_irq_en:1;
    unsigned int    ddc_req_ctrl:1;
    unsigned int    ddc_req:1;
}CBUS_ddc_02;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    ddc_rcv_cmd:8;
}CBUS_ddc_03;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    ddc_rcv_data:8;
}CBUS_ddc_04;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    ddc_data_fw:8;
}CBUS_ddc_05;

typedef struct
{
    unsigned int    reserved_0:28;
    unsigned int    ddc_eof_irq:1;
    unsigned int    ddc_eof_irq_en:1;
    unsigned int    ddcrd_rst_en:1;
    unsigned int    ddcrd_new_md:1;
}CBUS_ddc_06;

typedef struct
{
    unsigned int    reserved_0:26;
    unsigned int    clk_mod_vwd:1;
    unsigned int    clk_mod_awd:1;
    unsigned int    mute_en_vwd:1;
    unsigned int    mute_en_awd:1;
    unsigned int    path_en_off_vwd:1;
    unsigned int    path_en_off_awd:1;
}CBUS_wdog;

typedef struct
{
    unsigned int    reserved_0:26;
    unsigned int    arbiter_irq:1;
    unsigned int    ddc_irq:1;
    unsigned int    msc_ch_irq:1;
    unsigned int    msc_int_irq:1;
    unsigned int    msc_stat_irq:1;
    unsigned int    ctrl_01_resv:1;
}CBUS_int_index;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    cbus_test_md:2;
    unsigned int    fw_out:1;
    unsigned int    dbg_sel:3;
    unsigned int    reserved_1:2;
}CBUS_test;

typedef struct
{
    unsigned int    cbus_dummy0:32;
}CBUS_dummy0;
#endif


#define CBUS_STANDBY_00                                               0x18037400
#define CBUS_STANDBY_00_reg_addr                                      "0xb8037400"
#define CBUS_STANDBY_00_reg                                           0xb8037400
#define CBUS_STANDBY_00_inst_addr                                     "0x0100"
#define CBUS_STANDBY_00_inst                                          0x0100
#define CBUS_STANDBY_00_wake_pulse_det_shift                          (3)
#define CBUS_STANDBY_00_dis_pulse_det_shift                           (2)
#define CBUS_STANDBY_00_wake_irq_en_shift                             (1)
#define CBUS_STANDBY_00_dis_irq_en_shift                              (0)
#define CBUS_STANDBY_00_wake_pulse_det_mask                           (0x00000008)
#define CBUS_STANDBY_00_dis_pulse_det_mask                            (0x00000004)
#define CBUS_STANDBY_00_wake_irq_en_mask                              (0x00000002)
#define CBUS_STANDBY_00_dis_irq_en_mask                               (0x00000001)
#define CBUS_STANDBY_00_wake_pulse_det(data)                          (0x00000008&((data)<<3))
#define CBUS_STANDBY_00_dis_pulse_det(data)                           (0x00000004&((data)<<2))
#define CBUS_STANDBY_00_wake_irq_en(data)                             (0x00000002&((data)<<1))
#define CBUS_STANDBY_00_dis_irq_en(data)                              (0x00000001&(data))
#define CBUS_STANDBY_00_get_wake_pulse_det(data)                      ((0x00000008&(data))>>3)
#define CBUS_STANDBY_00_get_dis_pulse_det(data)                       ((0x00000004&(data))>>2)
#define CBUS_STANDBY_00_get_wake_irq_en(data)                         ((0x00000002&(data))>>1)
#define CBUS_STANDBY_00_get_dis_irq_en(data)                          (0x00000001&(data))


#define CBUS_STANDBY_01                                               0x18037404
#define CBUS_STANDBY_01_reg_addr                                      "0xb8037404"
#define CBUS_STANDBY_01_reg                                           0xb8037404
#define CBUS_STANDBY_01_inst_addr                                     "0x0101"
#define CBUS_STANDBY_01_inst                                          0x0101
#define CBUS_STANDBY_01_clk_1m_div_shift                              (10)
#define CBUS_STANDBY_01_clk_1k_div_shift                              (0)
#define CBUS_STANDBY_01_clk_1m_div_mask                               (0x00003C00)
#define CBUS_STANDBY_01_clk_1k_div_mask                               (0x000003FF)
#define CBUS_STANDBY_01_clk_1m_div(data)                              (0x00003C00&((data)<<10))
#define CBUS_STANDBY_01_clk_1k_div(data)                              (0x000003FF&(data))
#define CBUS_STANDBY_01_get_clk_1m_div(data)                          ((0x00003C00&(data))>>10)
#define CBUS_STANDBY_01_get_clk_1k_div(data)                          (0x000003FF&(data))


#define CBUS_STANDBY_02                                               0x18037408
#define CBUS_STANDBY_02_reg_addr                                      "0xb8037408"
#define CBUS_STANDBY_02_reg                                           0xb8037408
#define CBUS_STANDBY_02_inst_addr                                     "0x0102"
#define CBUS_STANDBY_02_inst                                          0x0102
#define CBUS_STANDBY_02_dis_deb_lv_shift                              (5)
#define CBUS_STANDBY_02_deb_lv_shift                                  (2)
#define CBUS_STANDBY_02_disconn_shift                                 (0)
#define CBUS_STANDBY_02_dis_deb_lv_mask                               (0x000000E0)
#define CBUS_STANDBY_02_deb_lv_mask                                   (0x0000001C)
#define CBUS_STANDBY_02_disconn_mask                                  (0x00000003)
#define CBUS_STANDBY_02_dis_deb_lv(data)                              (0x000000E0&((data)<<5))
#define CBUS_STANDBY_02_deb_lv(data)                                  (0x0000001C&((data)<<2))
#define CBUS_STANDBY_02_disconn(data)                                 (0x00000003&(data))
#define CBUS_STANDBY_02_get_dis_deb_lv(data)                          ((0x000000E0&(data))>>5)
#define CBUS_STANDBY_02_get_deb_lv(data)                              ((0x0000001C&(data))>>2)
#define CBUS_STANDBY_02_get_disconn(data)                             (0x00000003&(data))


#define CBUS_STANDBY_04                                               0x18037410
#define CBUS_STANDBY_04_reg_addr                                      "0xb8037410"
#define CBUS_STANDBY_04_reg                                           0xb8037410
#define CBUS_STANDBY_04_inst_addr                                     "0x0104"
#define CBUS_STANDBY_04_inst                                          0x0104
#define CBUS_STANDBY_04_wake_offset_low2_shift                        (11)
#define CBUS_STANDBY_04_wake_offset_low_shift                         (8)
#define CBUS_STANDBY_04_wake_cnt_shift                                (5)
#define CBUS_STANDBY_04_wake_offset_shift                             (2)
#define CBUS_STANDBY_04_cbus_disconn_shift                            (1)
#define CBUS_STANDBY_04_disconn_irq_en_shift                          (0)
#define CBUS_STANDBY_04_wake_offset_low2_mask                         (0x00003800)
#define CBUS_STANDBY_04_wake_offset_low_mask                          (0x00000700)
#define CBUS_STANDBY_04_wake_cnt_mask                                 (0x000000E0)
#define CBUS_STANDBY_04_wake_offset_mask                              (0x0000001C)
#define CBUS_STANDBY_04_cbus_disconn_mask                             (0x00000002)
#define CBUS_STANDBY_04_disconn_irq_en_mask                           (0x00000001)
#define CBUS_STANDBY_04_wake_offset_low2(data)                        (0x00003800&((data)<<11))
#define CBUS_STANDBY_04_wake_offset_low(data)                         (0x00000700&((data)<<8))
#define CBUS_STANDBY_04_wake_cnt(data)                                (0x000000E0&((data)<<5))
#define CBUS_STANDBY_04_wake_offset(data)                             (0x0000001C&((data)<<2))
#define CBUS_STANDBY_04_cbus_disconn(data)                            (0x00000002&((data)<<1))
#define CBUS_STANDBY_04_disconn_irq_en(data)                          (0x00000001&(data))
#define CBUS_STANDBY_04_get_wake_offset_low2(data)                    ((0x00003800&(data))>>11)
#define CBUS_STANDBY_04_get_wake_offset_low(data)                     ((0x00000700&(data))>>8)
#define CBUS_STANDBY_04_get_wake_cnt(data)                            ((0x000000E0&(data))>>5)
#define CBUS_STANDBY_04_get_wake_offset(data)                         ((0x0000001C&(data))>>2)
#define CBUS_STANDBY_04_get_cbus_disconn(data)                        ((0x00000002&(data))>>1)
#define CBUS_STANDBY_04_get_disconn_irq_en(data)                      (0x00000001&(data))


#define CBUS_STANDBY_05                                               0x18037414
#define CBUS_STANDBY_05_reg_addr                                      "0xb8037414"
#define CBUS_STANDBY_05_reg                                           0xb8037414
#define CBUS_STANDBY_05_inst_addr                                     "0x0105"
#define CBUS_STANDBY_05_inst                                          0x0105
#define CBUS_STANDBY_05_dis_upper_shift                               (4)
#define CBUS_STANDBY_05_dis_lower_shift                               (1)
#define CBUS_STANDBY_05_wake_eco_en_shift                             (0)
#define CBUS_STANDBY_05_dis_upper_mask                                (0x000000F0)
#define CBUS_STANDBY_05_dis_lower_mask                                (0x0000000E)
#define CBUS_STANDBY_05_wake_eco_en_mask                              (0x00000001)
#define CBUS_STANDBY_05_dis_upper(data)                               (0x000000F0&((data)<<4))
#define CBUS_STANDBY_05_dis_lower(data)                               (0x0000000E&((data)<<1))
#define CBUS_STANDBY_05_wake_eco_en(data)                             (0x00000001&(data))
#define CBUS_STANDBY_05_get_dis_upper(data)                           ((0x000000F0&(data))>>4)
#define CBUS_STANDBY_05_get_dis_lower(data)                           ((0x0000000E&(data))>>1)
#define CBUS_STANDBY_05_get_wake_eco_en(data)                         (0x00000001&(data))


#define CBUS_STANDBY_06                                               0x18037418
#define CBUS_STANDBY_06_reg_addr                                      "0xb8037418"
#define CBUS_STANDBY_06_reg                                           0xb8037418
#define CBUS_STANDBY_06_inst_addr                                     "0x0106"
#define CBUS_STANDBY_06_inst                                          0x0106
#define CBUS_STANDBY_06_wake_num_shift                                (5)
#define CBUS_STANDBY_06_dis_num_shift                                 (0)
#define CBUS_STANDBY_06_wake_num_mask                                 (0x000000E0)
#define CBUS_STANDBY_06_dis_num_mask                                  (0x0000001F)
#define CBUS_STANDBY_06_wake_num(data)                                (0x000000E0&((data)<<5))
#define CBUS_STANDBY_06_dis_num(data)                                 (0x0000001F&(data))
#define CBUS_STANDBY_06_get_wake_num(data)                            ((0x000000E0&(data))>>5)
#define CBUS_STANDBY_06_get_dis_num(data)                             (0x0000001F&(data))


#define CBUS_STANDBY_07                                               0x1803741c
#define CBUS_STANDBY_07_reg_addr                                      "0xb803741c"
#define CBUS_STANDBY_07_reg                                           0xb803741c
#define CBUS_STANDBY_07_inst_addr                                     "0x0107"
#define CBUS_STANDBY_07_inst                                          0x0107
#define CBUS_STANDBY_07_cbus_imp_auto_shift                           (7)
#define CBUS_STANDBY_07_bypass_mode_shift                             (6)
#define CBUS_STANDBY_07_sink_fsm_st_shift                             (3)
#define CBUS_STANDBY_07_cbus_100k_en_shift                            (2)
#define CBUS_STANDBY_07_cbus_1k_en_shift                              (1)
#define CBUS_STANDBY_07_cbus_in_sig_shift                             (0)
#define CBUS_STANDBY_07_cbus_imp_auto_mask                            (0x00000080)
#define CBUS_STANDBY_07_bypass_mode_mask                              (0x00000040)
#define CBUS_STANDBY_07_sink_fsm_st_mask                              (0x00000038)
#define CBUS_STANDBY_07_cbus_100k_en_mask                             (0x00000004)
#define CBUS_STANDBY_07_cbus_1k_en_mask                               (0x00000002)
#define CBUS_STANDBY_07_cbus_in_sig_mask                              (0x00000001)
#define CBUS_STANDBY_07_cbus_imp_auto(data)                           (0x00000080&((data)<<7))
#define CBUS_STANDBY_07_bypass_mode(data)                             (0x00000040&((data)<<6))
#define CBUS_STANDBY_07_sink_fsm_st(data)                             (0x00000038&((data)<<3))
#define CBUS_STANDBY_07_cbus_100k_en(data)                            (0x00000004&((data)<<2))
#define CBUS_STANDBY_07_cbus_1k_en(data)                              (0x00000002&((data)<<1))
#define CBUS_STANDBY_07_cbus_in_sig(data)                             (0x00000001&(data))
#define CBUS_STANDBY_07_get_cbus_imp_auto(data)                       ((0x00000080&(data))>>7)
#define CBUS_STANDBY_07_get_bypass_mode(data)                         ((0x00000040&(data))>>6)
#define CBUS_STANDBY_07_get_sink_fsm_st(data)                         ((0x00000038&(data))>>3)
#define CBUS_STANDBY_07_get_cbus_100k_en(data)                        ((0x00000004&(data))>>2)
#define CBUS_STANDBY_07_get_cbus_1k_en(data)                          ((0x00000002&(data))>>1)
#define CBUS_STANDBY_07_get_cbus_in_sig(data)                         (0x00000001&(data))


#define CBUS_STANDBY_08                                               0x18037420
#define CBUS_STANDBY_08_reg_addr                                      "0xb8037420"
#define CBUS_STANDBY_08_reg                                           0xb8037420
#define CBUS_STANDBY_08_inst_addr                                     "0x0108"
#define CBUS_STANDBY_08_inst                                          0x0108
#define CBUS_STANDBY_08_goto_sink1_pos_shift                          (5)
#define CBUS_STANDBY_08_goto_float_shift                              (4)
#define CBUS_STANDBY_08_goto_sink1_shift                              (3)
#define CBUS_STANDBY_08_cable_det_shift                               (2)
#define CBUS_STANDBY_08_dbg_sel_phy_shift                             (0)
#define CBUS_STANDBY_08_goto_sink1_pos_mask                           (0x00000020)
#define CBUS_STANDBY_08_goto_float_mask                               (0x00000010)
#define CBUS_STANDBY_08_goto_sink1_mask                               (0x00000008)
#define CBUS_STANDBY_08_cable_det_mask                                (0x00000004)
#define CBUS_STANDBY_08_dbg_sel_phy_mask                              (0x00000001)
#define CBUS_STANDBY_08_goto_sink1_pos(data)                          (0x00000020&((data)<<5))
#define CBUS_STANDBY_08_goto_float(data)                              (0x00000010&((data)<<4))
#define CBUS_STANDBY_08_goto_sink1(data)                              (0x00000008&((data)<<3))
#define CBUS_STANDBY_08_cable_det(data)                               (0x00000004&((data)<<2))
#define CBUS_STANDBY_08_dbg_sel_phy(data)                             (0x00000001&(data))
#define CBUS_STANDBY_08_get_goto_sink1_pos(data)                      ((0x00000020&(data))>>5)
#define CBUS_STANDBY_08_get_goto_float(data)                          ((0x00000010&(data))>>4)
#define CBUS_STANDBY_08_get_goto_sink1(data)                          ((0x00000008&(data))>>3)
#define CBUS_STANDBY_08_get_cable_det(data)                           ((0x00000004&(data))>>2)
#define CBUS_STANDBY_08_get_dbg_sel_phy(data)                         (0x00000001&(data))


#define CBUS_STANDBY_09                                               0x18037424
#define CBUS_STANDBY_09_reg_addr                                      "0xb8037424"
#define CBUS_STANDBY_09_reg                                           0xb8037424
#define CBUS_STANDBY_09_inst_addr                                     "0x0109"
#define CBUS_STANDBY_09_inst                                          0x0109
#define CBUS_STANDBY_09_ctrl_09_resv_shift                            (0)
#define CBUS_STANDBY_09_ctrl_09_resv_mask                             (0xFFFFFFFF)
#define CBUS_STANDBY_09_ctrl_09_resv(data)                            (0xFFFFFFFF&(data))
#define CBUS_STANDBY_09_get_ctrl_09_resv(data)                        (0xFFFFFFFF&(data))


#define CBUS_PHY_0                                                    0x18037430
#define CBUS_PHY_0_reg_addr                                           "0xb8037430"
#define CBUS_PHY_0_reg                                                0xb8037430
#define CBUS_PHY_0_inst_addr                                          "0x010C"
#define CBUS_PHY_0_inst                                               0x010C
#define CBUS_PHY_0_cbus_sr_shift                                      (6)
#define CBUS_PHY_0_cbus_smt_shift                                     (5)
#define CBUS_PHY_0_cbus_pu_shift                                      (4)
#define CBUS_PHY_0_cbus_pd_shift                                      (3)
#define CBUS_PHY_0_cbus_i_shift                                       (2)
#define CBUS_PHY_0_cbus_e2_shift                                      (1)
#define CBUS_PHY_0_cbus_e_shift                                       (0)
#define CBUS_PHY_0_cbus_sr_mask                                       (0x00000040)
#define CBUS_PHY_0_cbus_smt_mask                                      (0x00000020)
#define CBUS_PHY_0_cbus_pu_mask                                       (0x00000010)
#define CBUS_PHY_0_cbus_pd_mask                                       (0x00000008)
#define CBUS_PHY_0_cbus_i_mask                                        (0x00000004)
#define CBUS_PHY_0_cbus_e2_mask                                       (0x00000002)
#define CBUS_PHY_0_cbus_e_mask                                        (0x00000001)
#define CBUS_PHY_0_cbus_sr(data)                                      (0x00000040&((data)<<6))
#define CBUS_PHY_0_cbus_smt(data)                                     (0x00000020&((data)<<5))
#define CBUS_PHY_0_cbus_pu(data)                                      (0x00000010&((data)<<4))
#define CBUS_PHY_0_cbus_pd(data)                                      (0x00000008&((data)<<3))
#define CBUS_PHY_0_cbus_i(data)                                       (0x00000004&((data)<<2))
#define CBUS_PHY_0_cbus_e2(data)                                      (0x00000002&((data)<<1))
#define CBUS_PHY_0_cbus_e(data)                                       (0x00000001&(data))
#define CBUS_PHY_0_get_cbus_sr(data)                                  ((0x00000040&(data))>>6)
#define CBUS_PHY_0_get_cbus_smt(data)                                 ((0x00000020&(data))>>5)
#define CBUS_PHY_0_get_cbus_pu(data)                                  ((0x00000010&(data))>>4)
#define CBUS_PHY_0_get_cbus_pd(data)                                  ((0x00000008&(data))>>3)
#define CBUS_PHY_0_get_cbus_i(data)                                   ((0x00000004&(data))>>2)
#define CBUS_PHY_0_get_cbus_e2(data)                                  ((0x00000002&(data))>>1)
#define CBUS_PHY_0_get_cbus_e(data)                                   (0x00000001&(data))


#define CBUS_PHY_1                                                    0x18037434
#define CBUS_PHY_1_reg_addr                                           "0xb8037434"
#define CBUS_PHY_1_reg                                                0xb8037434
#define CBUS_PHY_1_inst_addr                                          "0x010D"
#define CBUS_PHY_1_inst                                               0x010D
#define CBUS_PHY_1_adjr_1k_shift                                      (28)
#define CBUS_PHY_1_adjr_100k_shift                                    (23)
#define CBUS_PHY_1_auto_k_1k_shift                                    (22)
#define CBUS_PHY_1_auto_k_100k_shift                                  (21)
#define CBUS_PHY_1_en_res_cal_cbus_shift                              (20)
#define CBUS_PHY_1_sel_cbus0_input_high_shift                         (18)
#define CBUS_PHY_1_sel_cbus0_input_low_shift                          (16)
#define CBUS_PHY_1_sel_cbus_0_driving_shift                           (13)
#define CBUS_PHY_1_sel_vref_ldo_shift                                 (11)
#define CBUS_PHY_1_trim_ldo_cbus_shift                                (7)
#define CBUS_PHY_1_triming_mode_shift                                 (6)
#define CBUS_PHY_1_en_cbus_shift                                      (5)
#define CBUS_PHY_1_en_cmp_cbus_shift                                  (4)
#define CBUS_PHY_1_en_driver_cbus_shift                               (3)
#define CBUS_PHY_1_en_ldo_cbus_shift                                  (2)
#define CBUS_PHY_1_psm_cbus_shift                                     (1)
#define CBUS_PHY_1_sel_cbusb_gpio_shift                               (0)
#define CBUS_PHY_1_adjr_1k_mask                                       (0xF0000000)
#define CBUS_PHY_1_adjr_100k_mask                                     (0x0F800000)
#define CBUS_PHY_1_auto_k_1k_mask                                     (0x00400000)
#define CBUS_PHY_1_auto_k_100k_mask                                   (0x00200000)
#define CBUS_PHY_1_en_res_cal_cbus_mask                               (0x00100000)
#define CBUS_PHY_1_sel_cbus0_input_high_mask                          (0x000C0000)
#define CBUS_PHY_1_sel_cbus0_input_low_mask                           (0x00030000)
#define CBUS_PHY_1_sel_cbus_0_driving_mask                            (0x0000E000)
#define CBUS_PHY_1_sel_vref_ldo_mask                                  (0x00001800)
#define CBUS_PHY_1_trim_ldo_cbus_mask                                 (0x00000780)
#define CBUS_PHY_1_triming_mode_mask                                  (0x00000040)
#define CBUS_PHY_1_en_cbus_mask                                       (0x00000020)
#define CBUS_PHY_1_en_cmp_cbus_mask                                   (0x00000010)
#define CBUS_PHY_1_en_driver_cbus_mask                                (0x00000008)
#define CBUS_PHY_1_en_ldo_cbus_mask                                   (0x00000004)
#define CBUS_PHY_1_psm_cbus_mask                                      (0x00000002)
#define CBUS_PHY_1_sel_cbusb_gpio_mask                                (0x00000001)
#define CBUS_PHY_1_adjr_1k(data)                                      (0xF0000000&((data)<<28))
#define CBUS_PHY_1_adjr_100k(data)                                    (0x0F800000&((data)<<23))
#define CBUS_PHY_1_auto_k_1k(data)                                    (0x00400000&((data)<<22))
#define CBUS_PHY_1_auto_k_100k(data)                                  (0x00200000&((data)<<21))
#define CBUS_PHY_1_en_res_cal_cbus(data)                              (0x00100000&((data)<<20))
#define CBUS_PHY_1_sel_cbus0_input_high(data)                         (0x000C0000&((data)<<18))
#define CBUS_PHY_1_sel_cbus0_input_low(data)                          (0x00030000&((data)<<16))
#define CBUS_PHY_1_sel_cbus_0_driving(data)                           (0x0000E000&((data)<<13))
#define CBUS_PHY_1_sel_vref_ldo(data)                                 (0x00001800&((data)<<11))
#define CBUS_PHY_1_trim_ldo_cbus(data)                                (0x00000780&((data)<<7))
#define CBUS_PHY_1_triming_mode(data)                                 (0x00000040&((data)<<6))
#define CBUS_PHY_1_en_cbus(data)                                      (0x00000020&((data)<<5))
#define CBUS_PHY_1_en_cmp_cbus(data)                                  (0x00000010&((data)<<4))
#define CBUS_PHY_1_en_driver_cbus(data)                               (0x00000008&((data)<<3))
#define CBUS_PHY_1_en_ldo_cbus(data)                                  (0x00000004&((data)<<2))
#define CBUS_PHY_1_psm_cbus(data)                                     (0x00000002&((data)<<1))
#define CBUS_PHY_1_sel_cbusb_gpio(data)                               (0x00000001&(data))
#define CBUS_PHY_1_get_adjr_1k(data)                                  ((0xF0000000&(data))>>28)
#define CBUS_PHY_1_get_adjr_100k(data)                                ((0x0F800000&(data))>>23)
#define CBUS_PHY_1_get_auto_k_1k(data)                                ((0x00400000&(data))>>22)
#define CBUS_PHY_1_get_auto_k_100k(data)                              ((0x00200000&(data))>>21)
#define CBUS_PHY_1_get_en_res_cal_cbus(data)                          ((0x00100000&(data))>>20)
#define CBUS_PHY_1_get_sel_cbus0_input_high(data)                     ((0x000C0000&(data))>>18)
#define CBUS_PHY_1_get_sel_cbus0_input_low(data)                      ((0x00030000&(data))>>16)
#define CBUS_PHY_1_get_sel_cbus_0_driving(data)                       ((0x0000E000&(data))>>13)
#define CBUS_PHY_1_get_sel_vref_ldo(data)                             ((0x00001800&(data))>>11)
#define CBUS_PHY_1_get_trim_ldo_cbus(data)                            ((0x00000780&(data))>>7)
#define CBUS_PHY_1_get_triming_mode(data)                             ((0x00000040&(data))>>6)
#define CBUS_PHY_1_get_en_cbus(data)                                  ((0x00000020&(data))>>5)
#define CBUS_PHY_1_get_en_cmp_cbus(data)                              ((0x00000010&(data))>>4)
#define CBUS_PHY_1_get_en_driver_cbus(data)                           ((0x00000008&(data))>>3)
#define CBUS_PHY_1_get_en_ldo_cbus(data)                              ((0x00000004&(data))>>2)
#define CBUS_PHY_1_get_psm_cbus(data)                                 ((0x00000002&(data))>>1)
#define CBUS_PHY_1_get_sel_cbusb_gpio(data)                           (0x00000001&(data))


#define CBUS_PHY_2                                                    0x18037438
#define CBUS_PHY_2_reg_addr                                           "0xb8037438"
#define CBUS_PHY_2_reg                                                0xb8037438
#define CBUS_PHY_2_inst_addr                                          "0x010E"
#define CBUS_PHY_2_inst                                               0x010E
#define CBUS_PHY_2_cbus_o_shift                                       (0)
#define CBUS_PHY_2_cbus_o_mask                                        (0x00000001)
#define CBUS_PHY_2_cbus_o(data)                                       (0x00000001&(data))
#define CBUS_PHY_2_get_cbus_o(data)                                   (0x00000001&(data))


#define CBUS_PHY_3                                                    0x1803743c
#define CBUS_PHY_3_reg_addr                                           "0xb803743c"
#define CBUS_PHY_3_reg                                                0xb803743c
#define CBUS_PHY_3_inst_addr                                          "0x010F"
#define CBUS_PHY_3_inst                                               0x010F
#define CBUS_PHY_3_sel_phy_soft_rst_n_shift                           (11)
#define CBUS_PHY_3_cbus_res_tst_shift                                 (1)
#define CBUS_PHY_3_res_ok_shift                                       (0)
#define CBUS_PHY_3_sel_phy_soft_rst_n_mask                            (0x00000800)
#define CBUS_PHY_3_cbus_res_tst_mask                                  (0x000007FE)
#define CBUS_PHY_3_res_ok_mask                                        (0x00000001)
#define CBUS_PHY_3_sel_phy_soft_rst_n(data)                           (0x00000800&((data)<<11))
#define CBUS_PHY_3_cbus_res_tst(data)                                 (0x000007FE&((data)<<1))
#define CBUS_PHY_3_res_ok(data)                                       (0x00000001&(data))
#define CBUS_PHY_3_get_sel_phy_soft_rst_n(data)                       ((0x00000800&(data))>>11)
#define CBUS_PHY_3_get_cbus_res_tst(data)                             ((0x000007FE&(data))>>1)
#define CBUS_PHY_3_get_res_ok(data)                                   (0x00000001&(data))


#define MSC_REG_00                                                    0x1800f000
#define MSC_REG_00_reg_addr                                           "0xb800f000"
#define MSC_REG_00_reg                                                0xb800f000
#define MSC_REG_00_inst_addr                                          "0x0000"
#define MSC_REG_00_inst                                               0x0000
#define MSC_REG_00_dev_state_shift                                    (0)
#define MSC_REG_00_dev_state_mask                                     (0x000000FF)
#define MSC_REG_00_dev_state(data)                                    (0x000000FF&(data))
#define MSC_REG_00_get_dev_state(data)                                (0x000000FF&(data))


#define MSC_REG_01                                                    0x1800f004
#define MSC_REG_01_reg_addr                                           "0xb800f004"
#define MSC_REG_01_reg                                                0xb800f004
#define MSC_REG_01_inst_addr                                          "0x0001"
#define MSC_REG_01_inst                                               0x0001
#define MSC_REG_01_mhl_ver_shift                                      (0)
#define MSC_REG_01_mhl_ver_mask                                       (0x000000FF)
#define MSC_REG_01_mhl_ver(data)                                      (0x000000FF&(data))
#define MSC_REG_01_get_mhl_ver(data)                                  (0x000000FF&(data))


#define MSC_REG_02                                                    0x1800f008
#define MSC_REG_02_reg_addr                                           "0xb800f008"
#define MSC_REG_02_reg                                                0xb800f008
#define MSC_REG_02_inst_addr                                          "0x0002"
#define MSC_REG_02_inst                                               0x0002
#define MSC_REG_02_dev_cat_shift                                      (7)
#define MSC_REG_02_plim_shift                                         (5)
#define MSC_REG_02_pow_shift                                          (4)
#define MSC_REG_02_dev_type_shift                                     (0)
#define MSC_REG_02_dev_cat_mask                                       (0x00000080)
#define MSC_REG_02_plim_mask                                          (0x00000060)
#define MSC_REG_02_pow_mask                                           (0x00000010)
#define MSC_REG_02_dev_type_mask                                      (0x0000000F)
#define MSC_REG_02_dev_cat(data)                                      (0x00000080&((data)<<7))
#define MSC_REG_02_plim(data)                                         (0x00000060&((data)<<5))
#define MSC_REG_02_pow(data)                                          (0x00000010&((data)<<4))
#define MSC_REG_02_dev_type(data)                                     (0x0000000F&(data))
#define MSC_REG_02_get_dev_cat(data)                                  ((0x00000080&(data))>>7)
#define MSC_REG_02_get_plim(data)                                     ((0x00000060&(data))>>5)
#define MSC_REG_02_get_pow(data)                                      ((0x00000010&(data))>>4)
#define MSC_REG_02_get_dev_type(data)                                 (0x0000000F&(data))


#define MSC_REG_03                                                    0x1800f00c
#define MSC_REG_03_reg_addr                                           "0xb800f00c"
#define MSC_REG_03_reg                                                0xb800f00c
#define MSC_REG_03_inst_addr                                          "0x0003"
#define MSC_REG_03_inst                                               0x0003
#define MSC_REG_03_adop_id_h_shift                                    (0)
#define MSC_REG_03_adop_id_h_mask                                     (0x000000FF)
#define MSC_REG_03_adop_id_h(data)                                    (0x000000FF&(data))
#define MSC_REG_03_get_adop_id_h(data)                                (0x000000FF&(data))


#define MSC_REG_04                                                    0x1800f010
#define MSC_REG_04_reg_addr                                           "0xb800f010"
#define MSC_REG_04_reg                                                0xb800f010
#define MSC_REG_04_inst_addr                                          "0x0004"
#define MSC_REG_04_inst                                               0x0004
#define MSC_REG_04_adop_id_l_shift                                    (0)
#define MSC_REG_04_adop_id_l_mask                                     (0x000000FF)
#define MSC_REG_04_adop_id_l(data)                                    (0x000000FF&(data))
#define MSC_REG_04_get_adop_id_l(data)                                (0x000000FF&(data))


#define MSC_REG_05                                                    0x1800f014
#define MSC_REG_05_reg_addr                                           "0xb800f014"
#define MSC_REG_05_reg                                                0xb800f014
#define MSC_REG_05_inst_addr                                          "0x0005"
#define MSC_REG_05_inst                                               0x0005
#define MSC_REG_05_vid_link_md_shift                                  (6)
#define MSC_REG_05_supp_vga_shift                                     (5)
#define MSC_REG_05_supp_islands_shift                                 (4)
#define MSC_REG_05_supp_ppixel_shift                                  (3)
#define MSC_REG_05_supp_yuv422_shift                                  (2)
#define MSC_REG_05_supp_yuv444_shift                                  (1)
#define MSC_REG_05_supp_rgb444_shift                                  (0)
#define MSC_REG_05_vid_link_md_mask                                   (0x000000C0)
#define MSC_REG_05_supp_vga_mask                                      (0x00000020)
#define MSC_REG_05_supp_islands_mask                                  (0x00000010)
#define MSC_REG_05_supp_ppixel_mask                                   (0x00000008)
#define MSC_REG_05_supp_yuv422_mask                                   (0x00000004)
#define MSC_REG_05_supp_yuv444_mask                                   (0x00000002)
#define MSC_REG_05_supp_rgb444_mask                                   (0x00000001)
#define MSC_REG_05_vid_link_md(data)                                  (0x000000C0&((data)<<6))
#define MSC_REG_05_supp_vga(data)                                     (0x00000020&((data)<<5))
#define MSC_REG_05_supp_islands(data)                                 (0x00000010&((data)<<4))
#define MSC_REG_05_supp_ppixel(data)                                  (0x00000008&((data)<<3))
#define MSC_REG_05_supp_yuv422(data)                                  (0x00000004&((data)<<2))
#define MSC_REG_05_supp_yuv444(data)                                  (0x00000002&((data)<<1))
#define MSC_REG_05_supp_rgb444(data)                                  (0x00000001&(data))
#define MSC_REG_05_get_vid_link_md(data)                              ((0x000000C0&(data))>>6)
#define MSC_REG_05_get_supp_vga(data)                                 ((0x00000020&(data))>>5)
#define MSC_REG_05_get_supp_islands(data)                             ((0x00000010&(data))>>4)
#define MSC_REG_05_get_supp_ppixel(data)                              ((0x00000008&(data))>>3)
#define MSC_REG_05_get_supp_yuv422(data)                              ((0x00000004&(data))>>2)
#define MSC_REG_05_get_supp_yuv444(data)                              ((0x00000002&(data))>>1)
#define MSC_REG_05_get_supp_rgb444(data)                              (0x00000001&(data))


#define MSC_REG_06                                                    0x1800f018
#define MSC_REG_06_reg_addr                                           "0xb800f018"
#define MSC_REG_06_reg                                                0xb800f018
#define MSC_REG_06_inst_addr                                          "0x0006"
#define MSC_REG_06_inst                                               0x0006
#define MSC_REG_06_aud_link_md_shift                                  (2)
#define MSC_REG_06_aud_8ch_shift                                      (1)
#define MSC_REG_06_aud_2ch_shift                                      (0)
#define MSC_REG_06_aud_link_md_mask                                   (0x000000FC)
#define MSC_REG_06_aud_8ch_mask                                       (0x00000002)
#define MSC_REG_06_aud_2ch_mask                                       (0x00000001)
#define MSC_REG_06_aud_link_md(data)                                  (0x000000FC&((data)<<2))
#define MSC_REG_06_aud_8ch(data)                                      (0x00000002&((data)<<1))
#define MSC_REG_06_aud_2ch(data)                                      (0x00000001&(data))
#define MSC_REG_06_get_aud_link_md(data)                              ((0x000000FC&(data))>>2)
#define MSC_REG_06_get_aud_8ch(data)                                  ((0x00000002&(data))>>1)
#define MSC_REG_06_get_aud_2ch(data)                                  (0x00000001&(data))


#define MSC_REG_07                                                    0x1800f01c
#define MSC_REG_07_reg_addr                                           "0xb800f01c"
#define MSC_REG_07_reg                                                0xb800f01c
#define MSC_REG_07_inst_addr                                          "0x0007"
#define MSC_REG_07_inst                                               0x0007
#define MSC_REG_07_supp_vt_shift                                      (7)
#define MSC_REG_07_video_type_shift                                   (4)
#define MSC_REG_07_vt_game_shift                                      (3)
#define MSC_REG_07_vt_cinema_shift                                    (2)
#define MSC_REG_07_vt_photo_shift                                     (1)
#define MSC_REG_07_vt_graphics_shift                                  (0)
#define MSC_REG_07_supp_vt_mask                                       (0x00000080)
#define MSC_REG_07_video_type_mask                                    (0x00000070)
#define MSC_REG_07_vt_game_mask                                       (0x00000008)
#define MSC_REG_07_vt_cinema_mask                                     (0x00000004)
#define MSC_REG_07_vt_photo_mask                                      (0x00000002)
#define MSC_REG_07_vt_graphics_mask                                   (0x00000001)
#define MSC_REG_07_supp_vt(data)                                      (0x00000080&((data)<<7))
#define MSC_REG_07_video_type(data)                                   (0x00000070&((data)<<4))
#define MSC_REG_07_vt_game(data)                                      (0x00000008&((data)<<3))
#define MSC_REG_07_vt_cinema(data)                                    (0x00000004&((data)<<2))
#define MSC_REG_07_vt_photo(data)                                     (0x00000002&((data)<<1))
#define MSC_REG_07_vt_graphics(data)                                  (0x00000001&(data))
#define MSC_REG_07_get_supp_vt(data)                                  ((0x00000080&(data))>>7)
#define MSC_REG_07_get_video_type(data)                               ((0x00000070&(data))>>4)
#define MSC_REG_07_get_vt_game(data)                                  ((0x00000008&(data))>>3)
#define MSC_REG_07_get_vt_cinema(data)                                ((0x00000004&(data))>>2)
#define MSC_REG_07_get_vt_photo(data)                                 ((0x00000002&(data))>>1)
#define MSC_REG_07_get_vt_graphics(data)                              (0x00000001&(data))


#define MSC_REG_08                                                    0x1800f020
#define MSC_REG_08_reg_addr                                           "0xb800f020"
#define MSC_REG_08_reg                                                0xb800f020
#define MSC_REG_08_inst_addr                                          "0x0008"
#define MSC_REG_08_inst                                               0x0008
#define MSC_REG_08_ld_gui_shift                                       (7)
#define MSC_REG_08_ld_speaker_shift                                   (6)
#define MSC_REG_08_ld_record_shift                                    (5)
#define MSC_REG_08_ld_tuner_shift                                     (4)
#define MSC_REG_08_ld_media_shift                                     (3)
#define MSC_REG_08_ld_audio_shift                                     (2)
#define MSC_REG_08_ld_video_shift                                     (1)
#define MSC_REG_08_ld_display_shift                                   (0)
#define MSC_REG_08_ld_gui_mask                                        (0x00000080)
#define MSC_REG_08_ld_speaker_mask                                    (0x00000040)
#define MSC_REG_08_ld_record_mask                                     (0x00000020)
#define MSC_REG_08_ld_tuner_mask                                      (0x00000010)
#define MSC_REG_08_ld_media_mask                                      (0x00000008)
#define MSC_REG_08_ld_audio_mask                                      (0x00000004)
#define MSC_REG_08_ld_video_mask                                      (0x00000002)
#define MSC_REG_08_ld_display_mask                                    (0x00000001)
#define MSC_REG_08_ld_gui(data)                                       (0x00000080&((data)<<7))
#define MSC_REG_08_ld_speaker(data)                                   (0x00000040&((data)<<6))
#define MSC_REG_08_ld_record(data)                                    (0x00000020&((data)<<5))
#define MSC_REG_08_ld_tuner(data)                                     (0x00000010&((data)<<4))
#define MSC_REG_08_ld_media(data)                                     (0x00000008&((data)<<3))
#define MSC_REG_08_ld_audio(data)                                     (0x00000004&((data)<<2))
#define MSC_REG_08_ld_video(data)                                     (0x00000002&((data)<<1))
#define MSC_REG_08_ld_display(data)                                   (0x00000001&(data))
#define MSC_REG_08_get_ld_gui(data)                                   ((0x00000080&(data))>>7)
#define MSC_REG_08_get_ld_speaker(data)                               ((0x00000040&(data))>>6)
#define MSC_REG_08_get_ld_record(data)                                ((0x00000020&(data))>>5)
#define MSC_REG_08_get_ld_tuner(data)                                 ((0x00000010&(data))>>4)
#define MSC_REG_08_get_ld_media(data)                                 ((0x00000008&(data))>>3)
#define MSC_REG_08_get_ld_audio(data)                                 ((0x00000004&(data))>>2)
#define MSC_REG_08_get_ld_video(data)                                 ((0x00000002&(data))>>1)
#define MSC_REG_08_get_ld_display(data)                               (0x00000001&(data))


#define MSC_REG_09                                                    0x1800f024
#define MSC_REG_09_reg_addr                                           "0xb800f024"
#define MSC_REG_09_reg                                                0xb800f024
#define MSC_REG_09_inst_addr                                          "0x0009"
#define MSC_REG_09_inst                                               0x0009
#define MSC_REG_09_bandwid_shift                                      (0)
#define MSC_REG_09_bandwid_mask                                       (0x000000FF)
#define MSC_REG_09_bandwid(data)                                      (0x000000FF&(data))
#define MSC_REG_09_get_bandwid(data)                                  (0x000000FF&(data))


#define MSC_REG_0A                                                    0x1800f028
#define MSC_REG_0A_reg_addr                                           "0xb800f028"
#define MSC_REG_0A_reg                                                0xb800f028
#define MSC_REG_0A_inst_addr                                          "0x000A"
#define MSC_REG_0A_inst                                               0x000A
#define MSC_REG_0A_feature_flag_shift                                 (5)
#define MSC_REG_0A_ucp_recv_supp_shift                                (4)
#define MSC_REG_0A_ucp_send_supp_shift                                (3)
#define MSC_REG_0A_sp_supp_shift                                      (2)
#define MSC_REG_0A_rap_supp_shift                                     (1)
#define MSC_REG_0A_rcp_supp_shift                                     (0)
#define MSC_REG_0A_feature_flag_mask                                  (0x000000E0)
#define MSC_REG_0A_ucp_recv_supp_mask                                 (0x00000010)
#define MSC_REG_0A_ucp_send_supp_mask                                 (0x00000008)
#define MSC_REG_0A_sp_supp_mask                                       (0x00000004)
#define MSC_REG_0A_rap_supp_mask                                      (0x00000002)
#define MSC_REG_0A_rcp_supp_mask                                      (0x00000001)
#define MSC_REG_0A_feature_flag(data)                                 (0x000000E0&((data)<<5))
#define MSC_REG_0A_ucp_recv_supp(data)                                (0x00000010&((data)<<4))
#define MSC_REG_0A_ucp_send_supp(data)                                (0x00000008&((data)<<3))
#define MSC_REG_0A_sp_supp(data)                                      (0x00000004&((data)<<2))
#define MSC_REG_0A_rap_supp(data)                                     (0x00000002&((data)<<1))
#define MSC_REG_0A_rcp_supp(data)                                     (0x00000001&(data))
#define MSC_REG_0A_get_feature_flag(data)                             ((0x000000E0&(data))>>5)
#define MSC_REG_0A_get_ucp_recv_supp(data)                            ((0x00000010&(data))>>4)
#define MSC_REG_0A_get_ucp_send_supp(data)                            ((0x00000008&(data))>>3)
#define MSC_REG_0A_get_sp_supp(data)                                  ((0x00000004&(data))>>2)
#define MSC_REG_0A_get_rap_supp(data)                                 ((0x00000002&(data))>>1)
#define MSC_REG_0A_get_rcp_supp(data)                                 (0x00000001&(data))


#define MSC_REG_0B                                                    0x1800f02c
#define MSC_REG_0B_reg_addr                                           "0xb800f02c"
#define MSC_REG_0B_reg                                                0xb800f02c
#define MSC_REG_0B_inst_addr                                          "0x000B"
#define MSC_REG_0B_inst                                               0x000B
#define MSC_REG_0B_device_id_h_shift                                  (0)
#define MSC_REG_0B_device_id_h_mask                                   (0x000000FF)
#define MSC_REG_0B_device_id_h(data)                                  (0x000000FF&(data))
#define MSC_REG_0B_get_device_id_h(data)                              (0x000000FF&(data))


#define MSC_REG_0C                                                    0x1800f030
#define MSC_REG_0C_reg_addr                                           "0xb800f030"
#define MSC_REG_0C_reg                                                0xb800f030
#define MSC_REG_0C_inst_addr                                          "0x000C"
#define MSC_REG_0C_inst                                               0x000C
#define MSC_REG_0C_device_id_l_shift                                  (0)
#define MSC_REG_0C_device_id_l_mask                                   (0x000000FF)
#define MSC_REG_0C_device_id_l(data)                                  (0x000000FF&(data))
#define MSC_REG_0C_get_device_id_l(data)                              (0x000000FF&(data))


#define MSC_REG_0D                                                    0x1800f034
#define MSC_REG_0D_reg_addr                                           "0xb800f034"
#define MSC_REG_0D_reg                                                0xb800f034
#define MSC_REG_0D_inst_addr                                          "0x000D"
#define MSC_REG_0D_inst                                               0x000D
#define MSC_REG_0D_scr_size_shift                                     (0)
#define MSC_REG_0D_scr_size_mask                                      (0x000000FF)
#define MSC_REG_0D_scr_size(data)                                     (0x000000FF&(data))
#define MSC_REG_0D_get_scr_size(data)                                 (0x000000FF&(data))


#define MSC_REG_0E                                                    0x1800f038
#define MSC_REG_0E_reg_addr                                           "0xb800f038"
#define MSC_REG_0E_reg                                                0xb800f038
#define MSC_REG_0E_inst_addr                                          "0x000E"
#define MSC_REG_0E_inst                                               0x000E
#define MSC_REG_0E_stat_size_shift                                    (4)
#define MSC_REG_0E_int_size_shift                                     (0)
#define MSC_REG_0E_stat_size_mask                                     (0x000000F0)
#define MSC_REG_0E_int_size_mask                                      (0x0000000F)
#define MSC_REG_0E_stat_size(data)                                    (0x000000F0&((data)<<4))
#define MSC_REG_0E_int_size(data)                                     (0x0000000F&(data))
#define MSC_REG_0E_get_stat_size(data)                                ((0x000000F0&(data))>>4)
#define MSC_REG_0E_get_int_size(data)                                 (0x0000000F&(data))


#define MSC_REG_0F                                                    0x1800f03c
#define MSC_REG_0F_reg_addr                                           "0xb800f03c"
#define MSC_REG_0F_reg                                                0xb800f03c
#define MSC_REG_0F_inst_addr                                          "0x000F"
#define MSC_REG_0F_inst                                               0x000F
#define MSC_REG_0F_cap_0f_shift                                       (0)
#define MSC_REG_0F_cap_0f_mask                                        (0x000000FF)
#define MSC_REG_0F_cap_0f(data)                                       (0x000000FF&(data))
#define MSC_REG_0F_get_cap_0f(data)                                   (0x000000FF&(data))


#define MSC_REG_20                                                    0x1800f080
#define MSC_REG_20_reg_addr                                           "0xb800f080"
#define MSC_REG_20_reg                                                0xb800f080
#define MSC_REG_20_inst_addr                                          "0x0020"
#define MSC_REG_20_inst                                               0x0020
#define MSC_REG_20_rchg_int_7_shift                                   (7)
#define MSC_REG_20_rchg_int_6_shift                                   (6)
#define MSC_REG_20_rchg_int_5_shift                                   (5)
#define MSC_REG_20_cbus_3d_req_shift                                  (4)
#define MSC_REG_20_grt_wrt_shift                                      (3)
#define MSC_REG_20_req_wrt_shift                                      (2)
#define MSC_REG_20_dscr_chg_shift                                     (1)
#define MSC_REG_20_dcap_chg_shift                                     (0)
#define MSC_REG_20_rchg_int_7_mask                                    (0x00000080)
#define MSC_REG_20_rchg_int_6_mask                                    (0x00000040)
#define MSC_REG_20_rchg_int_5_mask                                    (0x00000020)
#define MSC_REG_20_cbus_3d_req_mask                                   (0x00000010)
#define MSC_REG_20_grt_wrt_mask                                       (0x00000008)
#define MSC_REG_20_req_wrt_mask                                       (0x00000004)
#define MSC_REG_20_dscr_chg_mask                                      (0x00000002)
#define MSC_REG_20_dcap_chg_mask                                      (0x00000001)
#define MSC_REG_20_rchg_int_7(data)                                   (0x00000080&((data)<<7))
#define MSC_REG_20_rchg_int_6(data)                                   (0x00000040&((data)<<6))
#define MSC_REG_20_rchg_int_5(data)                                   (0x00000020&((data)<<5))
#define MSC_REG_20_cbus_3d_req(data)                                  (0x00000010&((data)<<4))
#define MSC_REG_20_grt_wrt(data)                                      (0x00000008&((data)<<3))
#define MSC_REG_20_req_wrt(data)                                      (0x00000004&((data)<<2))
#define MSC_REG_20_dscr_chg(data)                                     (0x00000002&((data)<<1))
#define MSC_REG_20_dcap_chg(data)                                     (0x00000001&(data))
#define MSC_REG_20_get_rchg_int_7(data)                               ((0x00000080&(data))>>7)
#define MSC_REG_20_get_rchg_int_6(data)                               ((0x00000040&(data))>>6)
#define MSC_REG_20_get_rchg_int_5(data)                               ((0x00000020&(data))>>5)
#define MSC_REG_20_get_cbus_3d_req(data)                              ((0x00000010&(data))>>4)
#define MSC_REG_20_get_grt_wrt(data)                                  ((0x00000008&(data))>>3)
#define MSC_REG_20_get_req_wrt(data)                                  ((0x00000004&(data))>>2)
#define MSC_REG_20_get_dscr_chg(data)                                 ((0x00000002&(data))>>1)
#define MSC_REG_20_get_dcap_chg(data)                                 (0x00000001&(data))


#define MSC_REG_21                                                    0x1800f084
#define MSC_REG_21_reg_addr                                           "0xb800f084"
#define MSC_REG_21_reg                                                0xb800f084
#define MSC_REG_21_inst_addr                                          "0x0021"
#define MSC_REG_21_inst                                               0x0021
#define MSC_REG_21_dchg_int_7_shift                                   (7)
#define MSC_REG_21_dchg_int_6_shift                                   (6)
#define MSC_REG_21_dchg_int_5_shift                                   (5)
#define MSC_REG_21_dchg_int_4_shift                                   (4)
#define MSC_REG_21_dchg_int_3_shift                                   (3)
#define MSC_REG_21_dchg_int_2_shift                                   (2)
#define MSC_REG_21_edid_chg_shift                                     (1)
#define MSC_REG_21_dchg_int_0_shift                                   (0)
#define MSC_REG_21_dchg_int_7_mask                                    (0x00000080)
#define MSC_REG_21_dchg_int_6_mask                                    (0x00000040)
#define MSC_REG_21_dchg_int_5_mask                                    (0x00000020)
#define MSC_REG_21_dchg_int_4_mask                                    (0x00000010)
#define MSC_REG_21_dchg_int_3_mask                                    (0x00000008)
#define MSC_REG_21_dchg_int_2_mask                                    (0x00000004)
#define MSC_REG_21_edid_chg_mask                                      (0x00000002)
#define MSC_REG_21_dchg_int_0_mask                                    (0x00000001)
#define MSC_REG_21_dchg_int_7(data)                                   (0x00000080&((data)<<7))
#define MSC_REG_21_dchg_int_6(data)                                   (0x00000040&((data)<<6))
#define MSC_REG_21_dchg_int_5(data)                                   (0x00000020&((data)<<5))
#define MSC_REG_21_dchg_int_4(data)                                   (0x00000010&((data)<<4))
#define MSC_REG_21_dchg_int_3(data)                                   (0x00000008&((data)<<3))
#define MSC_REG_21_dchg_int_2(data)                                   (0x00000004&((data)<<2))
#define MSC_REG_21_edid_chg(data)                                     (0x00000002&((data)<<1))
#define MSC_REG_21_dchg_int_0(data)                                   (0x00000001&(data))
#define MSC_REG_21_get_dchg_int_7(data)                               ((0x00000080&(data))>>7)
#define MSC_REG_21_get_dchg_int_6(data)                               ((0x00000040&(data))>>6)
#define MSC_REG_21_get_dchg_int_5(data)                               ((0x00000020&(data))>>5)
#define MSC_REG_21_get_dchg_int_4(data)                               ((0x00000010&(data))>>4)
#define MSC_REG_21_get_dchg_int_3(data)                               ((0x00000008&(data))>>3)
#define MSC_REG_21_get_dchg_int_2(data)                               ((0x00000004&(data))>>2)
#define MSC_REG_21_get_edid_chg(data)                                 ((0x00000002&(data))>>1)
#define MSC_REG_21_get_dchg_int_0(data)                               (0x00000001&(data))


#define MSC_REG_22                                                    0x1800f088
#define MSC_REG_22_reg_addr                                           "0xb800f088"
#define MSC_REG_22_reg                                                0xb800f088
#define MSC_REG_22_inst_addr                                          "0x0022"
#define MSC_REG_22_inst                                               0x0022
#define MSC_REG_22_chg22_7_shift                                      (7)
#define MSC_REG_22_chg22_6_shift                                      (6)
#define MSC_REG_22_chg22_5_shift                                      (5)
#define MSC_REG_22_chg22_4_shift                                      (4)
#define MSC_REG_22_chg22_3_shift                                      (3)
#define MSC_REG_22_chg22_2_shift                                      (2)
#define MSC_REG_22_chg22_1_shift                                      (1)
#define MSC_REG_22_chg22_0_shift                                      (0)
#define MSC_REG_22_chg22_7_mask                                       (0x00000080)
#define MSC_REG_22_chg22_6_mask                                       (0x00000040)
#define MSC_REG_22_chg22_5_mask                                       (0x00000020)
#define MSC_REG_22_chg22_4_mask                                       (0x00000010)
#define MSC_REG_22_chg22_3_mask                                       (0x00000008)
#define MSC_REG_22_chg22_2_mask                                       (0x00000004)
#define MSC_REG_22_chg22_1_mask                                       (0x00000002)
#define MSC_REG_22_chg22_0_mask                                       (0x00000001)
#define MSC_REG_22_chg22_7(data)                                      (0x00000080&((data)<<7))
#define MSC_REG_22_chg22_6(data)                                      (0x00000040&((data)<<6))
#define MSC_REG_22_chg22_5(data)                                      (0x00000020&((data)<<5))
#define MSC_REG_22_chg22_4(data)                                      (0x00000010&((data)<<4))
#define MSC_REG_22_chg22_3(data)                                      (0x00000008&((data)<<3))
#define MSC_REG_22_chg22_2(data)                                      (0x00000004&((data)<<2))
#define MSC_REG_22_chg22_1(data)                                      (0x00000002&((data)<<1))
#define MSC_REG_22_chg22_0(data)                                      (0x00000001&(data))
#define MSC_REG_22_get_chg22_7(data)                                  ((0x00000080&(data))>>7)
#define MSC_REG_22_get_chg22_6(data)                                  ((0x00000040&(data))>>6)
#define MSC_REG_22_get_chg22_5(data)                                  ((0x00000020&(data))>>5)
#define MSC_REG_22_get_chg22_4(data)                                  ((0x00000010&(data))>>4)
#define MSC_REG_22_get_chg22_3(data)                                  ((0x00000008&(data))>>3)
#define MSC_REG_22_get_chg22_2(data)                                  ((0x00000004&(data))>>2)
#define MSC_REG_22_get_chg22_1(data)                                  ((0x00000002&(data))>>1)
#define MSC_REG_22_get_chg22_0(data)                                  (0x00000001&(data))


#define MSC_REG_23                                                    0x1800f08c
#define MSC_REG_23_reg_addr                                           "0xb800f08c"
#define MSC_REG_23_reg                                                0xb800f08c
#define MSC_REG_23_inst_addr                                          "0x0023"
#define MSC_REG_23_inst                                               0x0023
#define MSC_REG_23_chg23_7_shift                                      (7)
#define MSC_REG_23_chg23_6_shift                                      (6)
#define MSC_REG_23_chg23_5_shift                                      (5)
#define MSC_REG_23_chg23_4_shift                                      (4)
#define MSC_REG_23_chg23_3_shift                                      (3)
#define MSC_REG_23_chg23_2_shift                                      (2)
#define MSC_REG_23_chg23_1_shift                                      (1)
#define MSC_REG_23_chg23_0_shift                                      (0)
#define MSC_REG_23_chg23_7_mask                                       (0x00000080)
#define MSC_REG_23_chg23_6_mask                                       (0x00000040)
#define MSC_REG_23_chg23_5_mask                                       (0x00000020)
#define MSC_REG_23_chg23_4_mask                                       (0x00000010)
#define MSC_REG_23_chg23_3_mask                                       (0x00000008)
#define MSC_REG_23_chg23_2_mask                                       (0x00000004)
#define MSC_REG_23_chg23_1_mask                                       (0x00000002)
#define MSC_REG_23_chg23_0_mask                                       (0x00000001)
#define MSC_REG_23_chg23_7(data)                                      (0x00000080&((data)<<7))
#define MSC_REG_23_chg23_6(data)                                      (0x00000040&((data)<<6))
#define MSC_REG_23_chg23_5(data)                                      (0x00000020&((data)<<5))
#define MSC_REG_23_chg23_4(data)                                      (0x00000010&((data)<<4))
#define MSC_REG_23_chg23_3(data)                                      (0x00000008&((data)<<3))
#define MSC_REG_23_chg23_2(data)                                      (0x00000004&((data)<<2))
#define MSC_REG_23_chg23_1(data)                                      (0x00000002&((data)<<1))
#define MSC_REG_23_chg23_0(data)                                      (0x00000001&(data))
#define MSC_REG_23_get_chg23_7(data)                                  ((0x00000080&(data))>>7)
#define MSC_REG_23_get_chg23_6(data)                                  ((0x00000040&(data))>>6)
#define MSC_REG_23_get_chg23_5(data)                                  ((0x00000020&(data))>>5)
#define MSC_REG_23_get_chg23_4(data)                                  ((0x00000010&(data))>>4)
#define MSC_REG_23_get_chg23_3(data)                                  ((0x00000008&(data))>>3)
#define MSC_REG_23_get_chg23_2(data)                                  ((0x00000004&(data))>>2)
#define MSC_REG_23_get_chg23_1(data)                                  ((0x00000002&(data))>>1)
#define MSC_REG_23_get_chg23_0(data)                                  (0x00000001&(data))


#define MSC_REG_24                                                    0x1800f090
#define MSC_REG_24_reg_addr                                           "0xb800f090"
#define MSC_REG_24_reg                                                0xb800f090
#define MSC_REG_24_inst_addr                                          "0x0024"
#define MSC_REG_24_inst                                               0x0024
#define MSC_REG_24_chg24_7_shift                                      (7)
#define MSC_REG_24_chg24_6_shift                                      (6)
#define MSC_REG_24_chg24_5_shift                                      (5)
#define MSC_REG_24_chg24_4_shift                                      (4)
#define MSC_REG_24_chg24_3_shift                                      (3)
#define MSC_REG_24_chg24_2_shift                                      (2)
#define MSC_REG_24_chg24_1_shift                                      (1)
#define MSC_REG_24_chg24_0_shift                                      (0)
#define MSC_REG_24_chg24_7_mask                                       (0x00000080)
#define MSC_REG_24_chg24_6_mask                                       (0x00000040)
#define MSC_REG_24_chg24_5_mask                                       (0x00000020)
#define MSC_REG_24_chg24_4_mask                                       (0x00000010)
#define MSC_REG_24_chg24_3_mask                                       (0x00000008)
#define MSC_REG_24_chg24_2_mask                                       (0x00000004)
#define MSC_REG_24_chg24_1_mask                                       (0x00000002)
#define MSC_REG_24_chg24_0_mask                                       (0x00000001)
#define MSC_REG_24_chg24_7(data)                                      (0x00000080&((data)<<7))
#define MSC_REG_24_chg24_6(data)                                      (0x00000040&((data)<<6))
#define MSC_REG_24_chg24_5(data)                                      (0x00000020&((data)<<5))
#define MSC_REG_24_chg24_4(data)                                      (0x00000010&((data)<<4))
#define MSC_REG_24_chg24_3(data)                                      (0x00000008&((data)<<3))
#define MSC_REG_24_chg24_2(data)                                      (0x00000004&((data)<<2))
#define MSC_REG_24_chg24_1(data)                                      (0x00000002&((data)<<1))
#define MSC_REG_24_chg24_0(data)                                      (0x00000001&(data))
#define MSC_REG_24_get_chg24_7(data)                                  ((0x00000080&(data))>>7)
#define MSC_REG_24_get_chg24_6(data)                                  ((0x00000040&(data))>>6)
#define MSC_REG_24_get_chg24_5(data)                                  ((0x00000020&(data))>>5)
#define MSC_REG_24_get_chg24_4(data)                                  ((0x00000010&(data))>>4)
#define MSC_REG_24_get_chg24_3(data)                                  ((0x00000008&(data))>>3)
#define MSC_REG_24_get_chg24_2(data)                                  ((0x00000004&(data))>>2)
#define MSC_REG_24_get_chg24_1(data)                                  ((0x00000002&(data))>>1)
#define MSC_REG_24_get_chg24_0(data)                                  (0x00000001&(data))


#define MSC_REG_25                                                    0x1800f094
#define MSC_REG_25_reg_addr                                           "0xb800f094"
#define MSC_REG_25_reg                                                0xb800f094
#define MSC_REG_25_inst_addr                                          "0x0025"
#define MSC_REG_25_inst                                               0x0025
#define MSC_REG_25_chg25_7_shift                                      (7)
#define MSC_REG_25_chg25_6_shift                                      (6)
#define MSC_REG_25_chg25_5_shift                                      (5)
#define MSC_REG_25_chg25_4_shift                                      (4)
#define MSC_REG_25_chg25_3_shift                                      (3)
#define MSC_REG_25_chg25_2_shift                                      (2)
#define MSC_REG_25_chg25_1_shift                                      (1)
#define MSC_REG_25_chg25_0_shift                                      (0)
#define MSC_REG_25_chg25_7_mask                                       (0x00000080)
#define MSC_REG_25_chg25_6_mask                                       (0x00000040)
#define MSC_REG_25_chg25_5_mask                                       (0x00000020)
#define MSC_REG_25_chg25_4_mask                                       (0x00000010)
#define MSC_REG_25_chg25_3_mask                                       (0x00000008)
#define MSC_REG_25_chg25_2_mask                                       (0x00000004)
#define MSC_REG_25_chg25_1_mask                                       (0x00000002)
#define MSC_REG_25_chg25_0_mask                                       (0x00000001)
#define MSC_REG_25_chg25_7(data)                                      (0x00000080&((data)<<7))
#define MSC_REG_25_chg25_6(data)                                      (0x00000040&((data)<<6))
#define MSC_REG_25_chg25_5(data)                                      (0x00000020&((data)<<5))
#define MSC_REG_25_chg25_4(data)                                      (0x00000010&((data)<<4))
#define MSC_REG_25_chg25_3(data)                                      (0x00000008&((data)<<3))
#define MSC_REG_25_chg25_2(data)                                      (0x00000004&((data)<<2))
#define MSC_REG_25_chg25_1(data)                                      (0x00000002&((data)<<1))
#define MSC_REG_25_chg25_0(data)                                      (0x00000001&(data))
#define MSC_REG_25_get_chg25_7(data)                                  ((0x00000080&(data))>>7)
#define MSC_REG_25_get_chg25_6(data)                                  ((0x00000040&(data))>>6)
#define MSC_REG_25_get_chg25_5(data)                                  ((0x00000020&(data))>>5)
#define MSC_REG_25_get_chg25_4(data)                                  ((0x00000010&(data))>>4)
#define MSC_REG_25_get_chg25_3(data)                                  ((0x00000008&(data))>>3)
#define MSC_REG_25_get_chg25_2(data)                                  ((0x00000004&(data))>>2)
#define MSC_REG_25_get_chg25_1(data)                                  ((0x00000002&(data))>>1)
#define MSC_REG_25_get_chg25_0(data)                                  (0x00000001&(data))


#define MSC_REG_26                                                    0x1800f098
#define MSC_REG_26_reg_addr                                           "0xb800f098"
#define MSC_REG_26_reg                                                0xb800f098
#define MSC_REG_26_inst_addr                                          "0x0026"
#define MSC_REG_26_inst                                               0x0026
#define MSC_REG_26_chg26_7_shift                                      (7)
#define MSC_REG_26_chg26_6_shift                                      (6)
#define MSC_REG_26_chg26_5_shift                                      (5)
#define MSC_REG_26_chg26_4_shift                                      (4)
#define MSC_REG_26_chg26_3_shift                                      (3)
#define MSC_REG_26_chg26_2_shift                                      (2)
#define MSC_REG_26_chg26_1_shift                                      (1)
#define MSC_REG_26_chg26_0_shift                                      (0)
#define MSC_REG_26_chg26_7_mask                                       (0x00000080)
#define MSC_REG_26_chg26_6_mask                                       (0x00000040)
#define MSC_REG_26_chg26_5_mask                                       (0x00000020)
#define MSC_REG_26_chg26_4_mask                                       (0x00000010)
#define MSC_REG_26_chg26_3_mask                                       (0x00000008)
#define MSC_REG_26_chg26_2_mask                                       (0x00000004)
#define MSC_REG_26_chg26_1_mask                                       (0x00000002)
#define MSC_REG_26_chg26_0_mask                                       (0x00000001)
#define MSC_REG_26_chg26_7(data)                                      (0x00000080&((data)<<7))
#define MSC_REG_26_chg26_6(data)                                      (0x00000040&((data)<<6))
#define MSC_REG_26_chg26_5(data)                                      (0x00000020&((data)<<5))
#define MSC_REG_26_chg26_4(data)                                      (0x00000010&((data)<<4))
#define MSC_REG_26_chg26_3(data)                                      (0x00000008&((data)<<3))
#define MSC_REG_26_chg26_2(data)                                      (0x00000004&((data)<<2))
#define MSC_REG_26_chg26_1(data)                                      (0x00000002&((data)<<1))
#define MSC_REG_26_chg26_0(data)                                      (0x00000001&(data))
#define MSC_REG_26_get_chg26_7(data)                                  ((0x00000080&(data))>>7)
#define MSC_REG_26_get_chg26_6(data)                                  ((0x00000040&(data))>>6)
#define MSC_REG_26_get_chg26_5(data)                                  ((0x00000020&(data))>>5)
#define MSC_REG_26_get_chg26_4(data)                                  ((0x00000010&(data))>>4)
#define MSC_REG_26_get_chg26_3(data)                                  ((0x00000008&(data))>>3)
#define MSC_REG_26_get_chg26_2(data)                                  ((0x00000004&(data))>>2)
#define MSC_REG_26_get_chg26_1(data)                                  ((0x00000002&(data))>>1)
#define MSC_REG_26_get_chg26_0(data)                                  (0x00000001&(data))


#define MSC_REG_27                                                    0x1800f09c
#define MSC_REG_27_reg_addr                                           "0xb800f09c"
#define MSC_REG_27_reg                                                0xb800f09c
#define MSC_REG_27_inst_addr                                          "0x0027"
#define MSC_REG_27_inst                                               0x0027
#define MSC_REG_27_chg27_7_shift                                      (7)
#define MSC_REG_27_chg27_6_shift                                      (6)
#define MSC_REG_27_chg27_5_shift                                      (5)
#define MSC_REG_27_chg27_4_shift                                      (4)
#define MSC_REG_27_chg27_3_shift                                      (3)
#define MSC_REG_27_chg27_2_shift                                      (2)
#define MSC_REG_27_chg27_1_shift                                      (1)
#define MSC_REG_27_chg27_0_shift                                      (0)
#define MSC_REG_27_chg27_7_mask                                       (0x00000080)
#define MSC_REG_27_chg27_6_mask                                       (0x00000040)
#define MSC_REG_27_chg27_5_mask                                       (0x00000020)
#define MSC_REG_27_chg27_4_mask                                       (0x00000010)
#define MSC_REG_27_chg27_3_mask                                       (0x00000008)
#define MSC_REG_27_chg27_2_mask                                       (0x00000004)
#define MSC_REG_27_chg27_1_mask                                       (0x00000002)
#define MSC_REG_27_chg27_0_mask                                       (0x00000001)
#define MSC_REG_27_chg27_7(data)                                      (0x00000080&((data)<<7))
#define MSC_REG_27_chg27_6(data)                                      (0x00000040&((data)<<6))
#define MSC_REG_27_chg27_5(data)                                      (0x00000020&((data)<<5))
#define MSC_REG_27_chg27_4(data)                                      (0x00000010&((data)<<4))
#define MSC_REG_27_chg27_3(data)                                      (0x00000008&((data)<<3))
#define MSC_REG_27_chg27_2(data)                                      (0x00000004&((data)<<2))
#define MSC_REG_27_chg27_1(data)                                      (0x00000002&((data)<<1))
#define MSC_REG_27_chg27_0(data)                                      (0x00000001&(data))
#define MSC_REG_27_get_chg27_7(data)                                  ((0x00000080&(data))>>7)
#define MSC_REG_27_get_chg27_6(data)                                  ((0x00000040&(data))>>6)
#define MSC_REG_27_get_chg27_5(data)                                  ((0x00000020&(data))>>5)
#define MSC_REG_27_get_chg27_4(data)                                  ((0x00000010&(data))>>4)
#define MSC_REG_27_get_chg27_3(data)                                  ((0x00000008&(data))>>3)
#define MSC_REG_27_get_chg27_2(data)                                  ((0x00000004&(data))>>2)
#define MSC_REG_27_get_chg27_1(data)                                  ((0x00000002&(data))>>1)
#define MSC_REG_27_get_chg27_0(data)                                  (0x00000001&(data))


#define MSC_REG_30                                                    0x1800f0c0
#define MSC_REG_30_reg_addr                                           "0xb800f0c0"
#define MSC_REG_30_reg                                                0xb800f0c0
#define MSC_REG_30_inst_addr                                          "0x0030"
#define MSC_REG_30_inst                                               0x0030
#define MSC_REG_30_conn_rdy_shift                                     (1)
#define MSC_REG_30_dcap_rdy_shift                                     (0)
#define MSC_REG_30_conn_rdy_mask                                      (0x000000FE)
#define MSC_REG_30_dcap_rdy_mask                                      (0x00000001)
#define MSC_REG_30_conn_rdy(data)                                     (0x000000FE&((data)<<1))
#define MSC_REG_30_dcap_rdy(data)                                     (0x00000001&(data))
#define MSC_REG_30_get_conn_rdy(data)                                 ((0x000000FE&(data))>>1)
#define MSC_REG_30_get_dcap_rdy(data)                                 (0x00000001&(data))


#define MSC_REG_31                                                    0x1800f0c4
#define MSC_REG_31_reg_addr                                           "0xb800f0c4"
#define MSC_REG_31_reg                                                0xb800f0c4
#define MSC_REG_31_inst_addr                                          "0x0031"
#define MSC_REG_31_inst                                               0x0031
#define MSC_REG_31_link_mode_shift                                    (5)
#define MSC_REG_31_muted_shift                                        (4)
#define MSC_REG_31_path_en_shift                                      (3)
#define MSC_REG_31_clk_mode_shift                                     (0)
#define MSC_REG_31_link_mode_mask                                     (0x000000E0)
#define MSC_REG_31_muted_mask                                         (0x00000010)
#define MSC_REG_31_path_en_mask                                       (0x00000008)
#define MSC_REG_31_clk_mode_mask                                      (0x00000007)
#define MSC_REG_31_link_mode(data)                                    (0x000000E0&((data)<<5))
#define MSC_REG_31_muted(data)                                        (0x00000010&((data)<<4))
#define MSC_REG_31_path_en(data)                                      (0x00000008&((data)<<3))
#define MSC_REG_31_clk_mode(data)                                     (0x00000007&(data))
#define MSC_REG_31_get_link_mode(data)                                ((0x000000E0&(data))>>5)
#define MSC_REG_31_get_muted(data)                                    ((0x00000010&(data))>>4)
#define MSC_REG_31_get_path_en(data)                                  ((0x00000008&(data))>>3)
#define MSC_REG_31_get_clk_mode(data)                                 (0x00000007&(data))


#define MSC_REG_32                                                    0x1800f0c8
#define MSC_REG_32_reg_addr                                           "0xb800f0c8"
#define MSC_REG_32_reg                                                0xb800f0c8
#define MSC_REG_32_inst_addr                                          "0x0032"
#define MSC_REG_32_inst                                               0x0032
#define MSC_REG_32_stat_32_shift                                      (0)
#define MSC_REG_32_stat_32_mask                                       (0x000000FF)
#define MSC_REG_32_stat_32(data)                                      (0x000000FF&(data))
#define MSC_REG_32_get_stat_32(data)                                  (0x000000FF&(data))


#define MSC_REG_33                                                    0x1800f0cc
#define MSC_REG_33_reg_addr                                           "0xb800f0cc"
#define MSC_REG_33_reg                                                0xb800f0cc
#define MSC_REG_33_inst_addr                                          "0x0033"
#define MSC_REG_33_inst                                               0x0033
#define MSC_REG_33_stat_33_shift                                      (0)
#define MSC_REG_33_stat_33_mask                                       (0x000000FF)
#define MSC_REG_33_stat_33(data)                                      (0x000000FF&(data))
#define MSC_REG_33_get_stat_33(data)                                  (0x000000FF&(data))


#define MSC_REG_34                                                    0x1800f0d0
#define MSC_REG_34_reg_addr                                           "0xb800f0d0"
#define MSC_REG_34_reg                                                0xb800f0d0
#define MSC_REG_34_inst_addr                                          "0x0034"
#define MSC_REG_34_inst                                               0x0034
#define MSC_REG_34_stat_34_shift                                      (0)
#define MSC_REG_34_stat_34_mask                                       (0x000000FF)
#define MSC_REG_34_stat_34(data)                                      (0x000000FF&(data))
#define MSC_REG_34_get_stat_34(data)                                  (0x000000FF&(data))


#define MSC_REG_35                                                    0x1800f0d4
#define MSC_REG_35_reg_addr                                           "0xb800f0d4"
#define MSC_REG_35_reg                                                0xb800f0d4
#define MSC_REG_35_inst_addr                                          "0x0035"
#define MSC_REG_35_inst                                               0x0035
#define MSC_REG_35_stat_35_shift                                      (0)
#define MSC_REG_35_stat_35_mask                                       (0x000000FF)
#define MSC_REG_35_stat_35(data)                                      (0x000000FF&(data))
#define MSC_REG_35_get_stat_35(data)                                  (0x000000FF&(data))


#define MSC_REG_36                                                    0x1800f0d8
#define MSC_REG_36_reg_addr                                           "0xb800f0d8"
#define MSC_REG_36_reg                                                0xb800f0d8
#define MSC_REG_36_inst_addr                                          "0x0036"
#define MSC_REG_36_inst                                               0x0036
#define MSC_REG_36_stat_36_shift                                      (0)
#define MSC_REG_36_stat_36_mask                                       (0x000000FF)
#define MSC_REG_36_stat_36(data)                                      (0x000000FF&(data))
#define MSC_REG_36_get_stat_36(data)                                  (0x000000FF&(data))


#define MSC_REG_37                                                    0x1800f0dc
#define MSC_REG_37_reg_addr                                           "0xb800f0dc"
#define MSC_REG_37_reg                                                0xb800f0dc
#define MSC_REG_37_inst_addr                                          "0x0037"
#define MSC_REG_37_inst                                               0x0037
#define MSC_REG_37_stat_37_shift                                      (0)
#define MSC_REG_37_stat_37_mask                                       (0x000000FF)
#define MSC_REG_37_stat_37(data)                                      (0x000000FF&(data))
#define MSC_REG_37_get_stat_37(data)                                  (0x000000FF&(data))


#define MSC_REG_40                                                    0x1800f100
#define MSC_REG_40_reg_addr                                           "0xb800f100"
#define MSC_REG_40_reg                                                0xb800f100
#define MSC_REG_40_inst_addr                                          "0x0040"
#define MSC_REG_40_inst                                               0x0040
#define MSC_REG_40_scratch_40_shift                                   (0)
#define MSC_REG_40_scratch_40_mask                                    (0x000000FF)
#define MSC_REG_40_scratch_40(data)                                   (0x000000FF&(data))
#define MSC_REG_40_get_scratch_40(data)                               (0x000000FF&(data))


#define MSC_REG_41                                                    0x1800f104
#define MSC_REG_41_reg_addr                                           "0xb800f104"
#define MSC_REG_41_reg                                                0xb800f104
#define MSC_REG_41_inst_addr                                          "0x0041"
#define MSC_REG_41_inst                                               0x0041
#define MSC_REG_41_scratch_41_shift                                   (0)
#define MSC_REG_41_scratch_41_mask                                    (0x000000FF)
#define MSC_REG_41_scratch_41(data)                                   (0x000000FF&(data))
#define MSC_REG_41_get_scratch_41(data)                               (0x000000FF&(data))


#define MSC_REG_42                                                    0x1800f108
#define MSC_REG_42_reg_addr                                           "0xb800f108"
#define MSC_REG_42_reg                                                0xb800f108
#define MSC_REG_42_inst_addr                                          "0x0042"
#define MSC_REG_42_inst                                               0x0042
#define MSC_REG_42_scratch_42_shift                                   (0)
#define MSC_REG_42_scratch_42_mask                                    (0x000000FF)
#define MSC_REG_42_scratch_42(data)                                   (0x000000FF&(data))
#define MSC_REG_42_get_scratch_42(data)                               (0x000000FF&(data))


#define MSC_REG_43                                                    0x1800f10c
#define MSC_REG_43_reg_addr                                           "0xb800f10c"
#define MSC_REG_43_reg                                                0xb800f10c
#define MSC_REG_43_inst_addr                                          "0x0043"
#define MSC_REG_43_inst                                               0x0043
#define MSC_REG_43_scratch_43_shift                                   (0)
#define MSC_REG_43_scratch_43_mask                                    (0x000000FF)
#define MSC_REG_43_scratch_43(data)                                   (0x000000FF&(data))
#define MSC_REG_43_get_scratch_43(data)                               (0x000000FF&(data))


#define MSC_REG_44                                                    0x1800f110
#define MSC_REG_44_reg_addr                                           "0xb800f110"
#define MSC_REG_44_reg                                                0xb800f110
#define MSC_REG_44_inst_addr                                          "0x0044"
#define MSC_REG_44_inst                                               0x0044
#define MSC_REG_44_scratch_44_shift                                   (0)
#define MSC_REG_44_scratch_44_mask                                    (0x000000FF)
#define MSC_REG_44_scratch_44(data)                                   (0x000000FF&(data))
#define MSC_REG_44_get_scratch_44(data)                               (0x000000FF&(data))


#define MSC_REG_45                                                    0x1800f114
#define MSC_REG_45_reg_addr                                           "0xb800f114"
#define MSC_REG_45_reg                                                0xb800f114
#define MSC_REG_45_inst_addr                                          "0x0045"
#define MSC_REG_45_inst                                               0x0045
#define MSC_REG_45_scratch_45_shift                                   (0)
#define MSC_REG_45_scratch_45_mask                                    (0x000000FF)
#define MSC_REG_45_scratch_45(data)                                   (0x000000FF&(data))
#define MSC_REG_45_get_scratch_45(data)                               (0x000000FF&(data))


#define MSC_REG_46                                                    0x1800f118
#define MSC_REG_46_reg_addr                                           "0xb800f118"
#define MSC_REG_46_reg                                                0xb800f118
#define MSC_REG_46_inst_addr                                          "0x0046"
#define MSC_REG_46_inst                                               0x0046
#define MSC_REG_46_scratch_46_shift                                   (0)
#define MSC_REG_46_scratch_46_mask                                    (0x000000FF)
#define MSC_REG_46_scratch_46(data)                                   (0x000000FF&(data))
#define MSC_REG_46_get_scratch_46(data)                               (0x000000FF&(data))


#define MSC_REG_47                                                    0x1800f11c
#define MSC_REG_47_reg_addr                                           "0xb800f11c"
#define MSC_REG_47_reg                                                0xb800f11c
#define MSC_REG_47_inst_addr                                          "0x0047"
#define MSC_REG_47_inst                                               0x0047
#define MSC_REG_47_scratch_47_shift                                   (0)
#define MSC_REG_47_scratch_47_mask                                    (0x000000FF)
#define MSC_REG_47_scratch_47(data)                                   (0x000000FF&(data))
#define MSC_REG_47_get_scratch_47(data)                               (0x000000FF&(data))


#define MSC_REG_48                                                    0x1800f120
#define MSC_REG_48_reg_addr                                           "0xb800f120"
#define MSC_REG_48_reg                                                0xb800f120
#define MSC_REG_48_inst_addr                                          "0x0048"
#define MSC_REG_48_inst                                               0x0048
#define MSC_REG_48_scratch_48_shift                                   (0)
#define MSC_REG_48_scratch_48_mask                                    (0x000000FF)
#define MSC_REG_48_scratch_48(data)                                   (0x000000FF&(data))
#define MSC_REG_48_get_scratch_48(data)                               (0x000000FF&(data))


#define MSC_REG_49                                                    0x1800f124
#define MSC_REG_49_reg_addr                                           "0xb800f124"
#define MSC_REG_49_reg                                                0xb800f124
#define MSC_REG_49_inst_addr                                          "0x0049"
#define MSC_REG_49_inst                                               0x0049
#define MSC_REG_49_scratch_49_shift                                   (0)
#define MSC_REG_49_scratch_49_mask                                    (0x000000FF)
#define MSC_REG_49_scratch_49(data)                                   (0x000000FF&(data))
#define MSC_REG_49_get_scratch_49(data)                               (0x000000FF&(data))


#define MSC_REG_4A                                                    0x1800f128
#define MSC_REG_4A_reg_addr                                           "0xb800f128"
#define MSC_REG_4A_reg                                                0xb800f128
#define MSC_REG_4A_inst_addr                                          "0x004A"
#define MSC_REG_4A_inst                                               0x004A
#define MSC_REG_4A_scratch_4a_shift                                   (0)
#define MSC_REG_4A_scratch_4a_mask                                    (0x000000FF)
#define MSC_REG_4A_scratch_4a(data)                                   (0x000000FF&(data))
#define MSC_REG_4A_get_scratch_4a(data)                               (0x000000FF&(data))


#define MSC_REG_4B                                                    0x1800f12c
#define MSC_REG_4B_reg_addr                                           "0xb800f12c"
#define MSC_REG_4B_reg                                                0xb800f12c
#define MSC_REG_4B_inst_addr                                          "0x004B"
#define MSC_REG_4B_inst                                               0x004B
#define MSC_REG_4B_scratch_4b_shift                                   (0)
#define MSC_REG_4B_scratch_4b_mask                                    (0x000000FF)
#define MSC_REG_4B_scratch_4b(data)                                   (0x000000FF&(data))
#define MSC_REG_4B_get_scratch_4b(data)                               (0x000000FF&(data))


#define MSC_REG_4C                                                    0x1800f130
#define MSC_REG_4C_reg_addr                                           "0xb800f130"
#define MSC_REG_4C_reg                                                0xb800f130
#define MSC_REG_4C_inst_addr                                          "0x004C"
#define MSC_REG_4C_inst                                               0x004C
#define MSC_REG_4C_scratch_4c_shift                                   (0)
#define MSC_REG_4C_scratch_4c_mask                                    (0x000000FF)
#define MSC_REG_4C_scratch_4c(data)                                   (0x000000FF&(data))
#define MSC_REG_4C_get_scratch_4c(data)                               (0x000000FF&(data))


#define MSC_REG_4D                                                    0x1800f134
#define MSC_REG_4D_reg_addr                                           "0xb800f134"
#define MSC_REG_4D_reg                                                0xb800f134
#define MSC_REG_4D_inst_addr                                          "0x004D"
#define MSC_REG_4D_inst                                               0x004D
#define MSC_REG_4D_scratch_4d_shift                                   (0)
#define MSC_REG_4D_scratch_4d_mask                                    (0x000000FF)
#define MSC_REG_4D_scratch_4d(data)                                   (0x000000FF&(data))
#define MSC_REG_4D_get_scratch_4d(data)                               (0x000000FF&(data))


#define MSC_REG_4E                                                    0x1800f138
#define MSC_REG_4E_reg_addr                                           "0xb800f138"
#define MSC_REG_4E_reg                                                0xb800f138
#define MSC_REG_4E_inst_addr                                          "0x004E"
#define MSC_REG_4E_inst                                               0x004E
#define MSC_REG_4E_scratch_4e_shift                                   (0)
#define MSC_REG_4E_scratch_4e_mask                                    (0x000000FF)
#define MSC_REG_4E_scratch_4e(data)                                   (0x000000FF&(data))
#define MSC_REG_4E_get_scratch_4e(data)                               (0x000000FF&(data))


#define MSC_REG_4F                                                    0x1800f13c
#define MSC_REG_4F_reg_addr                                           "0xb800f13c"
#define MSC_REG_4F_reg                                                0xb800f13c
#define MSC_REG_4F_inst_addr                                          "0x004F"
#define MSC_REG_4F_inst                                               0x004F
#define MSC_REG_4F_scratch_4f_shift                                   (0)
#define MSC_REG_4F_scratch_4f_mask                                    (0x000000FF)
#define MSC_REG_4F_scratch_4f(data)                                   (0x000000FF&(data))
#define MSC_REG_4F_get_scratch_4f(data)                               (0x000000FF&(data))


#define MSC_REG_50                                                    0x1800f140
#define MSC_REG_50_reg_addr                                           "0xb800f140"
#define MSC_REG_50_reg                                                0xb800f140
#define MSC_REG_50_inst_addr                                          "0x0050"
#define MSC_REG_50_inst                                               0x0050
#define MSC_REG_50_scratch_50_shift                                   (0)
#define MSC_REG_50_scratch_50_mask                                    (0x000000FF)
#define MSC_REG_50_scratch_50(data)                                   (0x000000FF&(data))
#define MSC_REG_50_get_scratch_50(data)                               (0x000000FF&(data))


#define MSC_REG_51                                                    0x1800f144
#define MSC_REG_51_reg_addr                                           "0xb800f144"
#define MSC_REG_51_reg                                                0xb800f144
#define MSC_REG_51_inst_addr                                          "0x0051"
#define MSC_REG_51_inst                                               0x0051
#define MSC_REG_51_scratch_51_shift                                   (0)
#define MSC_REG_51_scratch_51_mask                                    (0x000000FF)
#define MSC_REG_51_scratch_51(data)                                   (0x000000FF&(data))
#define MSC_REG_51_get_scratch_51(data)                               (0x000000FF&(data))


#define MSC_REG_52                                                    0x1800f148
#define MSC_REG_52_reg_addr                                           "0xb800f148"
#define MSC_REG_52_reg                                                0xb800f148
#define MSC_REG_52_inst_addr                                          "0x0052"
#define MSC_REG_52_inst                                               0x0052
#define MSC_REG_52_scratch_52_shift                                   (0)
#define MSC_REG_52_scratch_52_mask                                    (0x000000FF)
#define MSC_REG_52_scratch_52(data)                                   (0x000000FF&(data))
#define MSC_REG_52_get_scratch_52(data)                               (0x000000FF&(data))


#define MSC_REG_53                                                    0x1800f14c
#define MSC_REG_53_reg_addr                                           "0xb800f14c"
#define MSC_REG_53_reg                                                0xb800f14c
#define MSC_REG_53_inst_addr                                          "0x0053"
#define MSC_REG_53_inst                                               0x0053
#define MSC_REG_53_scratch_53_shift                                   (0)
#define MSC_REG_53_scratch_53_mask                                    (0x000000FF)
#define MSC_REG_53_scratch_53(data)                                   (0x000000FF&(data))
#define MSC_REG_53_get_scratch_53(data)                               (0x000000FF&(data))


#define MSC_REG_54                                                    0x1800f150
#define MSC_REG_54_reg_addr                                           "0xb800f150"
#define MSC_REG_54_reg                                                0xb800f150
#define MSC_REG_54_inst_addr                                          "0x0054"
#define MSC_REG_54_inst                                               0x0054
#define MSC_REG_54_scratch_54_shift                                   (0)
#define MSC_REG_54_scratch_54_mask                                    (0x000000FF)
#define MSC_REG_54_scratch_54(data)                                   (0x000000FF&(data))
#define MSC_REG_54_get_scratch_54(data)                               (0x000000FF&(data))


#define MSC_REG_55                                                    0x1800f154
#define MSC_REG_55_reg_addr                                           "0xb800f154"
#define MSC_REG_55_reg                                                0xb800f154
#define MSC_REG_55_inst_addr                                          "0x0055"
#define MSC_REG_55_inst                                               0x0055
#define MSC_REG_55_scratch_55_shift                                   (0)
#define MSC_REG_55_scratch_55_mask                                    (0x000000FF)
#define MSC_REG_55_scratch_55(data)                                   (0x000000FF&(data))
#define MSC_REG_55_get_scratch_55(data)                               (0x000000FF&(data))


#define MSC_REG_56                                                    0x1800f158
#define MSC_REG_56_reg_addr                                           "0xb800f158"
#define MSC_REG_56_reg                                                0xb800f158
#define MSC_REG_56_inst_addr                                          "0x0056"
#define MSC_REG_56_inst                                               0x0056
#define MSC_REG_56_scratch_56_shift                                   (0)
#define MSC_REG_56_scratch_56_mask                                    (0x000000FF)
#define MSC_REG_56_scratch_56(data)                                   (0x000000FF&(data))
#define MSC_REG_56_get_scratch_56(data)                               (0x000000FF&(data))


#define MSC_REG_57                                                    0x1800f15c
#define MSC_REG_57_reg_addr                                           "0xb800f15c"
#define MSC_REG_57_reg                                                0xb800f15c
#define MSC_REG_57_inst_addr                                          "0x0057"
#define MSC_REG_57_inst                                               0x0057
#define MSC_REG_57_scratch_57_shift                                   (0)
#define MSC_REG_57_scratch_57_mask                                    (0x000000FF)
#define MSC_REG_57_scratch_57(data)                                   (0x000000FF&(data))
#define MSC_REG_57_get_scratch_57(data)                               (0x000000FF&(data))


#define MSC_REG_58                                                    0x1800f160
#define MSC_REG_58_reg_addr                                           "0xb800f160"
#define MSC_REG_58_reg                                                0xb800f160
#define MSC_REG_58_inst_addr                                          "0x0058"
#define MSC_REG_58_inst                                               0x0058
#define MSC_REG_58_scratch_58_shift                                   (0)
#define MSC_REG_58_scratch_58_mask                                    (0x000000FF)
#define MSC_REG_58_scratch_58(data)                                   (0x000000FF&(data))
#define MSC_REG_58_get_scratch_58(data)                               (0x000000FF&(data))


#define MSC_REG_59                                                    0x1800f164
#define MSC_REG_59_reg_addr                                           "0xb800f164"
#define MSC_REG_59_reg                                                0xb800f164
#define MSC_REG_59_inst_addr                                          "0x0059"
#define MSC_REG_59_inst                                               0x0059
#define MSC_REG_59_scratch_59_shift                                   (0)
#define MSC_REG_59_scratch_59_mask                                    (0x000000FF)
#define MSC_REG_59_scratch_59(data)                                   (0x000000FF&(data))
#define MSC_REG_59_get_scratch_59(data)                               (0x000000FF&(data))


#define MSC_REG_5A                                                    0x1800f168
#define MSC_REG_5A_reg_addr                                           "0xb800f168"
#define MSC_REG_5A_reg                                                0xb800f168
#define MSC_REG_5A_inst_addr                                          "0x005A"
#define MSC_REG_5A_inst                                               0x005A
#define MSC_REG_5A_scratch_5a_shift                                   (0)
#define MSC_REG_5A_scratch_5a_mask                                    (0x000000FF)
#define MSC_REG_5A_scratch_5a(data)                                   (0x000000FF&(data))
#define MSC_REG_5A_get_scratch_5a(data)                               (0x000000FF&(data))


#define MSC_REG_5B                                                    0x1800f16c
#define MSC_REG_5B_reg_addr                                           "0xb800f16c"
#define MSC_REG_5B_reg                                                0xb800f16c
#define MSC_REG_5B_inst_addr                                          "0x005B"
#define MSC_REG_5B_inst                                               0x005B
#define MSC_REG_5B_scratch_5b_shift                                   (0)
#define MSC_REG_5B_scratch_5b_mask                                    (0x000000FF)
#define MSC_REG_5B_scratch_5b(data)                                   (0x000000FF&(data))
#define MSC_REG_5B_get_scratch_5b(data)                               (0x000000FF&(data))


#define MSC_REG_5C                                                    0x1800f170
#define MSC_REG_5C_reg_addr                                           "0xb800f170"
#define MSC_REG_5C_reg                                                0xb800f170
#define MSC_REG_5C_inst_addr                                          "0x005C"
#define MSC_REG_5C_inst                                               0x005C
#define MSC_REG_5C_scratch_5c_shift                                   (0)
#define MSC_REG_5C_scratch_5c_mask                                    (0x000000FF)
#define MSC_REG_5C_scratch_5c(data)                                   (0x000000FF&(data))
#define MSC_REG_5C_get_scratch_5c(data)                               (0x000000FF&(data))


#define MSC_REG_5D                                                    0x1800f174
#define MSC_REG_5D_reg_addr                                           "0xb800f174"
#define MSC_REG_5D_reg                                                0xb800f174
#define MSC_REG_5D_inst_addr                                          "0x005D"
#define MSC_REG_5D_inst                                               0x005D
#define MSC_REG_5D_scratch_5d_shift                                   (0)
#define MSC_REG_5D_scratch_5d_mask                                    (0x000000FF)
#define MSC_REG_5D_scratch_5d(data)                                   (0x000000FF&(data))
#define MSC_REG_5D_get_scratch_5d(data)                               (0x000000FF&(data))


#define MSC_REG_5E                                                    0x1800f178
#define MSC_REG_5E_reg_addr                                           "0xb800f178"
#define MSC_REG_5E_reg                                                0xb800f178
#define MSC_REG_5E_inst_addr                                          "0x005E"
#define MSC_REG_5E_inst                                               0x005E
#define MSC_REG_5E_scratch_5e_shift                                   (0)
#define MSC_REG_5E_scratch_5e_mask                                    (0x000000FF)
#define MSC_REG_5E_scratch_5e(data)                                   (0x000000FF&(data))
#define MSC_REG_5E_get_scratch_5e(data)                               (0x000000FF&(data))


#define MSC_REG_5F                                                    0x1800f17c
#define MSC_REG_5F_reg_addr                                           "0xb800f17c"
#define MSC_REG_5F_reg                                                0xb800f17c
#define MSC_REG_5F_inst_addr                                          "0x005F"
#define MSC_REG_5F_inst                                               0x005F
#define MSC_REG_5F_scratch_5f_shift                                   (0)
#define MSC_REG_5F_scratch_5f_mask                                    (0x000000FF)
#define MSC_REG_5F_scratch_5f(data)                                   (0x000000FF&(data))
#define MSC_REG_5F_get_scratch_5f(data)                               (0x000000FF&(data))


#define CBUS_LINK_00                                                  0x1800f200
#define CBUS_LINK_00_reg_addr                                         "0xb800f200"
#define CBUS_LINK_00_reg                                              0xb800f200
#define CBUS_LINK_00_inst_addr                                        "0x0080"
#define CBUS_LINK_00_inst                                             0x0080
#define CBUS_LINK_00_sync0_hb_8_0_shift                               (9)
#define CBUS_LINK_00_sync0_lb_8_0_shift                               (0)
#define CBUS_LINK_00_sync0_hb_8_0_mask                                (0x0003FE00)
#define CBUS_LINK_00_sync0_lb_8_0_mask                                (0x000001FF)
#define CBUS_LINK_00_sync0_hb_8_0(data)                               (0x0003FE00&((data)<<9))
#define CBUS_LINK_00_sync0_lb_8_0(data)                               (0x000001FF&(data))
#define CBUS_LINK_00_get_sync0_hb_8_0(data)                           ((0x0003FE00&(data))>>9)
#define CBUS_LINK_00_get_sync0_lb_8_0(data)                           (0x000001FF&(data))


#define CBUS_LINK_01                                                  0x1800f204
#define CBUS_LINK_01_reg_addr                                         "0xb800f204"
#define CBUS_LINK_01_reg                                              0xb800f204
#define CBUS_LINK_01_inst_addr                                        "0x0081"
#define CBUS_LINK_01_inst                                             0x0081
#define CBUS_LINK_01_sync1_hb_7_0_shift                               (8)
#define CBUS_LINK_01_sync1_lb_7_0_shift                               (0)
#define CBUS_LINK_01_sync1_hb_7_0_mask                                (0x0000FF00)
#define CBUS_LINK_01_sync1_lb_7_0_mask                                (0x000000FF)
#define CBUS_LINK_01_sync1_hb_7_0(data)                               (0x0000FF00&((data)<<8))
#define CBUS_LINK_01_sync1_lb_7_0(data)                               (0x000000FF&(data))
#define CBUS_LINK_01_get_sync1_hb_7_0(data)                           ((0x0000FF00&(data))>>8)
#define CBUS_LINK_01_get_sync1_lb_7_0(data)                           (0x000000FF&(data))


#define CBUS_LINK_02                                                  0x1800f208
#define CBUS_LINK_02_reg_addr                                         "0xb800f208"
#define CBUS_LINK_02_reg                                              0xb800f208
#define CBUS_LINK_02_inst_addr                                        "0x0082"
#define CBUS_LINK_02_inst                                             0x0082
#define CBUS_LINK_02_sync_bit_time_shift                              (0)
#define CBUS_LINK_02_sync_bit_time_mask                               (0x000000FF)
#define CBUS_LINK_02_sync_bit_time(data)                              (0x000000FF&(data))
#define CBUS_LINK_02_get_sync_bit_time(data)                          (0x000000FF&(data))


#define CBUS_LINK_03                                                  0x1800f20c
#define CBUS_LINK_03_reg_addr                                         "0xb800f20c"
#define CBUS_LINK_03_reg                                              0xb800f20c
#define CBUS_LINK_03_inst_addr                                        "0x0083"
#define CBUS_LINK_03_inst                                             0x0083
#define CBUS_LINK_03_abs_thres_en_shift                               (8)
#define CBUS_LINK_03_abs_threshold_shift                              (0)
#define CBUS_LINK_03_abs_thres_en_mask                                (0x00000100)
#define CBUS_LINK_03_abs_threshold_mask                               (0x000000FF)
#define CBUS_LINK_03_abs_thres_en(data)                               (0x00000100&((data)<<8))
#define CBUS_LINK_03_abs_threshold(data)                              (0x000000FF&(data))
#define CBUS_LINK_03_get_abs_thres_en(data)                           ((0x00000100&(data))>>8)
#define CBUS_LINK_03_get_abs_threshold(data)                          (0x000000FF&(data))


#define CBUS_LINK_04                                                  0x1800f210
#define CBUS_LINK_04_reg_addr                                         "0xb800f210"
#define CBUS_LINK_04_reg                                              0xb800f210
#define CBUS_LINK_04_inst_addr                                        "0x0084"
#define CBUS_LINK_04_inst                                             0x0084
#define CBUS_LINK_04_parity_time_shift                                (0)
#define CBUS_LINK_04_parity_time_mask                                 (0x000000FF)
#define CBUS_LINK_04_parity_time(data)                                (0x000000FF&(data))
#define CBUS_LINK_04_get_parity_time(data)                            (0x000000FF&(data))


#define CBUS_LINK_05                                                  0x1800f214
#define CBUS_LINK_05_reg_addr                                         "0xb800f214"
#define CBUS_LINK_05_reg                                              0xb800f214
#define CBUS_LINK_05_inst_addr                                        "0x0085"
#define CBUS_LINK_05_inst                                             0x0085
#define CBUS_LINK_05_parity_fail_shift                                (7)
#define CBUS_LINK_05_parity_irq_en_shift                              (6)
#define CBUS_LINK_05_ctrl_16_resv_shift                               (5)
#define CBUS_LINK_05_parity_limit_shift                               (0)
#define CBUS_LINK_05_parity_fail_mask                                 (0x00000080)
#define CBUS_LINK_05_parity_irq_en_mask                               (0x00000040)
#define CBUS_LINK_05_ctrl_16_resv_mask                                (0x00000020)
#define CBUS_LINK_05_parity_limit_mask                                (0x0000001F)
#define CBUS_LINK_05_parity_fail(data)                                (0x00000080&((data)<<7))
#define CBUS_LINK_05_parity_irq_en(data)                              (0x00000040&((data)<<6))
#define CBUS_LINK_05_ctrl_16_resv(data)                               (0x00000020&((data)<<5))
#define CBUS_LINK_05_parity_limit(data)                               (0x0000001F&(data))
#define CBUS_LINK_05_get_parity_fail(data)                            ((0x00000080&(data))>>7)
#define CBUS_LINK_05_get_parity_irq_en(data)                          ((0x00000040&(data))>>6)
#define CBUS_LINK_05_get_ctrl_16_resv(data)                           ((0x00000020&(data))>>5)
#define CBUS_LINK_05_get_parity_limit(data)                           (0x0000001F&(data))


#define CBUS_LINK_06                                                  0x1800f218
#define CBUS_LINK_06_reg_addr                                         "0xb800f218"
#define CBUS_LINK_06_reg                                              0xb800f218
#define CBUS_LINK_06_inst_addr                                        "0x0086"
#define CBUS_LINK_06_inst                                             0x0086
#define CBUS_LINK_06_ack_fall_shift                                   (0)
#define CBUS_LINK_06_ack_fall_mask                                    (0x0000007F)
#define CBUS_LINK_06_ack_fall(data)                                   (0x0000007F&(data))
#define CBUS_LINK_06_get_ack_fall(data)                               (0x0000007F&(data))


#define CBUS_LINK_07                                                  0x1800f21c
#define CBUS_LINK_07_reg_addr                                         "0xb800f21c"
#define CBUS_LINK_07_reg                                              0xb800f21c
#define CBUS_LINK_07_inst_addr                                        "0x0087"
#define CBUS_LINK_07_inst                                             0x0087
#define CBUS_LINK_07_ack_0_shift                                      (0)
#define CBUS_LINK_07_ack_0_mask                                       (0x0000007F)
#define CBUS_LINK_07_ack_0(data)                                      (0x0000007F&(data))
#define CBUS_LINK_07_get_ack_0(data)                                  (0x0000007F&(data))


#define CBUS_LINK_08                                                  0x1800f220
#define CBUS_LINK_08_reg_addr                                         "0xb800f220"
#define CBUS_LINK_08_reg                                              0xb800f220
#define CBUS_LINK_08_inst_addr                                        "0x0088"
#define CBUS_LINK_08_inst                                             0x0088
#define CBUS_LINK_08_tx_bit_time_shift                                (0)
#define CBUS_LINK_08_tx_bit_time_mask                                 (0x000000FF)
#define CBUS_LINK_08_tx_bit_time(data)                                (0x000000FF&(data))
#define CBUS_LINK_08_get_tx_bit_time(data)                            (0x000000FF&(data))


#define CBUS_LINK_09                                                  0x1800f224
#define CBUS_LINK_09_reg_addr                                         "0xb800f224"
#define CBUS_LINK_09_reg                                              0xb800f224
#define CBUS_LINK_09_inst_addr                                        "0x0089"
#define CBUS_LINK_09_inst                                             0x0089
#define CBUS_LINK_09_chk_win_up_shift                                 (5)
#define CBUS_LINK_09_chk_win_lo_shift                                 (3)
#define CBUS_LINK_09_fast_reply_en_shift                              (2)
#define CBUS_LINK_09_ctrl_1b_resv_shift                               (0)
#define CBUS_LINK_09_chk_win_up_mask                                  (0x000000E0)
#define CBUS_LINK_09_chk_win_lo_mask                                  (0x00000018)
#define CBUS_LINK_09_fast_reply_en_mask                               (0x00000004)
#define CBUS_LINK_09_ctrl_1b_resv_mask                                (0x00000003)
#define CBUS_LINK_09_chk_win_up(data)                                 (0x000000E0&((data)<<5))
#define CBUS_LINK_09_chk_win_lo(data)                                 (0x00000018&((data)<<3))
#define CBUS_LINK_09_fast_reply_en(data)                              (0x00000004&((data)<<2))
#define CBUS_LINK_09_ctrl_1b_resv(data)                               (0x00000003&(data))
#define CBUS_LINK_09_get_chk_win_up(data)                             ((0x000000E0&(data))>>5)
#define CBUS_LINK_09_get_chk_win_lo(data)                             ((0x00000018&(data))>>3)
#define CBUS_LINK_09_get_fast_reply_en(data)                          ((0x00000004&(data))>>2)
#define CBUS_LINK_09_get_ctrl_1b_resv(data)                           (0x00000003&(data))


#define CBUS_LINK_0A                                                  0x1800f228
#define CBUS_LINK_0A_reg_addr                                         "0xb800f228"
#define CBUS_LINK_0A_reg                                              0xb800f228
#define CBUS_LINK_0A_inst_addr                                        "0x008A"
#define CBUS_LINK_0A_inst                                             0x008A
#define CBUS_LINK_0A_tx_ack_fal_shift                                 (0)
#define CBUS_LINK_0A_tx_ack_fal_mask                                  (0x0000007F)
#define CBUS_LINK_0A_tx_ack_fal(data)                                 (0x0000007F&(data))
#define CBUS_LINK_0A_get_tx_ack_fal(data)                             (0x0000007F&(data))


#define CBUS_LINK_0B                                                  0x1800f22c
#define CBUS_LINK_0B_reg_addr                                         "0xb800f22c"
#define CBUS_LINK_0B_reg                                              0xb800f22c
#define CBUS_LINK_0B_inst_addr                                        "0x008B"
#define CBUS_LINK_0B_inst                                             0x008B
#define CBUS_LINK_0B_tx_ack_low_hb_shift                              (0)
#define CBUS_LINK_0B_tx_ack_low_hb_mask                               (0x0000007F)
#define CBUS_LINK_0B_tx_ack_low_hb(data)                              (0x0000007F&(data))
#define CBUS_LINK_0B_get_tx_ack_low_hb(data)                          (0x0000007F&(data))


#define CBUS_LINK_0C                                                  0x1800f230
#define CBUS_LINK_0C_reg_addr                                         "0xb800f230"
#define CBUS_LINK_0C_reg                                              0xb800f230
#define CBUS_LINK_0C_inst_addr                                        "0x008C"
#define CBUS_LINK_0C_inst                                             0x008C
#define CBUS_LINK_0C_tx_ack_low_lb_shift                              (0)
#define CBUS_LINK_0C_tx_ack_low_lb_mask                               (0x0000007F)
#define CBUS_LINK_0C_tx_ack_low_lb(data)                              (0x0000007F&(data))
#define CBUS_LINK_0C_get_tx_ack_low_lb(data)                          (0x0000007F&(data))


#define CBUS_LINK_0D                                                  0x1800f234
#define CBUS_LINK_0D_reg_addr                                         "0xb800f234"
#define CBUS_LINK_0D_reg                                              0xb800f234
#define CBUS_LINK_0D_inst_addr                                        "0x008D"
#define CBUS_LINK_0D_inst                                             0x008D
#define CBUS_LINK_0D_retry_lv_shift                                   (5)
#define CBUS_LINK_0D_retry_flag_shift                                 (4)
#define CBUS_LINK_0D_ctrl_1f_resv_shift                               (0)
#define CBUS_LINK_0D_retry_lv_mask                                    (0x000000E0)
#define CBUS_LINK_0D_retry_flag_mask                                  (0x00000010)
#define CBUS_LINK_0D_ctrl_1f_resv_mask                                (0x0000000F)
#define CBUS_LINK_0D_retry_lv(data)                                   (0x000000E0&((data)<<5))
#define CBUS_LINK_0D_retry_flag(data)                                 (0x00000010&((data)<<4))
#define CBUS_LINK_0D_ctrl_1f_resv(data)                               (0x0000000F&(data))
#define CBUS_LINK_0D_get_retry_lv(data)                               ((0x000000E0&(data))>>5)
#define CBUS_LINK_0D_get_retry_flag(data)                             ((0x00000010&(data))>>4)
#define CBUS_LINK_0D_get_ctrl_1f_resv(data)                           (0x0000000F&(data))


#define CBUS_LINK_0E                                                  0x1800f238
#define CBUS_LINK_0E_reg_addr                                         "0xb800f238"
#define CBUS_LINK_0E_reg                                              0xb800f238
#define CBUS_LINK_0E_inst_addr                                        "0x008E"
#define CBUS_LINK_0E_inst                                             0x008E
#define CBUS_LINK_0E_drv_str_shift                                    (6)
#define CBUS_LINK_0E_drv_hi_cbus_shift                                (0)
#define CBUS_LINK_0E_drv_str_mask                                     (0x000000C0)
#define CBUS_LINK_0E_drv_hi_cbus_mask                                 (0x0000003F)
#define CBUS_LINK_0E_drv_str(data)                                    (0x000000C0&((data)<<6))
#define CBUS_LINK_0E_drv_hi_cbus(data)                                (0x0000003F&(data))
#define CBUS_LINK_0E_get_drv_str(data)                                ((0x000000C0&(data))>>6)
#define CBUS_LINK_0E_get_drv_hi_cbus(data)                            (0x0000003F&(data))


#define CBUS_LINK_0F                                                  0x1800f23c
#define CBUS_LINK_0F_reg_addr                                         "0xb800f23c"
#define CBUS_LINK_0F_reg                                              0xb800f23c
#define CBUS_LINK_0F_inst_addr                                        "0x008F"
#define CBUS_LINK_0F_inst                                             0x008F
#define CBUS_LINK_0F_wait_shift                                       (2)
#define CBUS_LINK_0F_req_opp_int_shift                                (0)
#define CBUS_LINK_0F_wait_mask                                        (0x0000003C)
#define CBUS_LINK_0F_req_opp_int_mask                                 (0x00000003)
#define CBUS_LINK_0F_wait(data)                                       (0x0000003C&((data)<<2))
#define CBUS_LINK_0F_req_opp_int(data)                                (0x00000003&(data))
#define CBUS_LINK_0F_get_wait(data)                                   ((0x0000003C&(data))>>2)
#define CBUS_LINK_0F_get_req_opp_int(data)                            (0x00000003&(data))


#define CBUS_LINK_10                                                  0x1800f240
#define CBUS_LINK_10_reg_addr                                         "0xb800f240"
#define CBUS_LINK_10_reg                                              0xb800f240
#define CBUS_LINK_10_inst_addr                                        "0x0090"
#define CBUS_LINK_10_inst                                             0x0090
#define CBUS_LINK_10_req_opp_flt_shift                                (0)
#define CBUS_LINK_10_req_opp_flt_mask                                 (0x000000FF)
#define CBUS_LINK_10_req_opp_flt(data)                                (0x000000FF&(data))
#define CBUS_LINK_10_get_req_opp_flt(data)                            (0x000000FF&(data))


#define CBUS_LINK_11                                                  0x1800f244
#define CBUS_LINK_11_reg_addr                                         "0xb800f244"
#define CBUS_LINK_11_reg                                              0xb800f244
#define CBUS_LINK_11_inst_addr                                        "0x0091"
#define CBUS_LINK_11_inst                                             0x0091
#define CBUS_LINK_11_req_cont_shift                                   (0)
#define CBUS_LINK_11_req_cont_mask                                    (0x000000FF)
#define CBUS_LINK_11_req_cont(data)                                   (0x000000FF&(data))
#define CBUS_LINK_11_get_req_cont(data)                               (0x000000FF&(data))


#define CBUS_LINK_12                                                  0x1800f248
#define CBUS_LINK_12_reg_addr                                         "0xb800f248"
#define CBUS_LINK_12_reg                                              0xb800f248
#define CBUS_LINK_12_inst_addr                                        "0x0092"
#define CBUS_LINK_12_inst                                             0x0092
#define CBUS_LINK_12_req_hold_shift                                   (4)
#define CBUS_LINK_12_resp_hold_shift                                  (0)
#define CBUS_LINK_12_req_hold_mask                                    (0x000000F0)
#define CBUS_LINK_12_resp_hold_mask                                   (0x0000000F)
#define CBUS_LINK_12_req_hold(data)                                   (0x000000F0&((data)<<4))
#define CBUS_LINK_12_resp_hold(data)                                  (0x0000000F&(data))
#define CBUS_LINK_12_get_req_hold(data)                               ((0x000000F0&(data))>>4)
#define CBUS_LINK_12_get_resp_hold(data)                              (0x0000000F&(data))


#define CBUS_LINK_13                                                  0x1800f24c
#define CBUS_LINK_13_reg_addr                                         "0xb800f24c"
#define CBUS_LINK_13_reg                                              0xb800f24c
#define CBUS_LINK_13_inst_addr                                        "0x0093"
#define CBUS_LINK_13_inst                                             0x0093
#define CBUS_LINK_13_glob_time_shift                                  (6)
#define CBUS_LINK_13_link_time_shift                                  (1)
#define CBUS_LINK_13_link_err_shift                                   (0)
#define CBUS_LINK_13_glob_time_mask                                   (0x000000C0)
#define CBUS_LINK_13_link_time_mask                                   (0x0000003E)
#define CBUS_LINK_13_link_err_mask                                    (0x00000001)
#define CBUS_LINK_13_glob_time(data)                                  (0x000000C0&((data)<<6))
#define CBUS_LINK_13_link_time(data)                                  (0x0000003E&((data)<<1))
#define CBUS_LINK_13_link_err(data)                                   (0x00000001&(data))
#define CBUS_LINK_13_get_glob_time(data)                              ((0x000000C0&(data))>>6)
#define CBUS_LINK_13_get_link_time(data)                              ((0x0000003E&(data))>>1)
#define CBUS_LINK_13_get_link_err(data)                               (0x00000001&(data))


#define CBUS_LINK_14                                                  0x1800f250
#define CBUS_LINK_14_reg_addr                                         "0xb800f250"
#define CBUS_LINK_14_reg                                              0xb800f250
#define CBUS_LINK_14_inst_addr                                        "0x0094"
#define CBUS_LINK_14_inst                                             0x0094
#define CBUS_LINK_14_chk_point_shift                                  (2)
#define CBUS_LINK_14_chk_err_shift                                    (1)
#define CBUS_LINK_14_avoid_conf_shift                                 (0)
#define CBUS_LINK_14_chk_point_mask                                   (0x000000FC)
#define CBUS_LINK_14_chk_err_mask                                     (0x00000002)
#define CBUS_LINK_14_avoid_conf_mask                                  (0x00000001)
#define CBUS_LINK_14_chk_point(data)                                  (0x000000FC&((data)<<2))
#define CBUS_LINK_14_chk_err(data)                                    (0x00000002&((data)<<1))
#define CBUS_LINK_14_avoid_conf(data)                                 (0x00000001&(data))
#define CBUS_LINK_14_get_chk_point(data)                              ((0x000000FC&(data))>>2)
#define CBUS_LINK_14_get_chk_err(data)                                ((0x00000002&(data))>>1)
#define CBUS_LINK_14_get_avoid_conf(data)                             (0x00000001&(data))


#define CBUS_MSC_00                                                   0x1800f260
#define CBUS_MSC_00_reg_addr                                          "0xb800f260"
#define CBUS_MSC_00_reg                                               0xb800f260
#define CBUS_MSC_00_inst_addr                                         "0x0098"
#define CBUS_MSC_00_inst                                              0x0098
#define CBUS_MSC_00_mcumsc_en_shift                                   (5)
#define CBUS_MSC_00_msc_wait_arb_shift                                (4)
#define CBUS_MSC_00_ctrl_28_resv_shift                                (0)
#define CBUS_MSC_00_mcumsc_en_mask                                    (0x00000020)
#define CBUS_MSC_00_msc_wait_arb_mask                                 (0x00000010)
#define CBUS_MSC_00_ctrl_28_resv_mask                                 (0x0000000F)
#define CBUS_MSC_00_mcumsc_en(data)                                   (0x00000020&((data)<<5))
#define CBUS_MSC_00_msc_wait_arb(data)                                (0x00000010&((data)<<4))
#define CBUS_MSC_00_ctrl_28_resv(data)                                (0x0000000F&(data))
#define CBUS_MSC_00_get_mcumsc_en(data)                               ((0x00000020&(data))>>5)
#define CBUS_MSC_00_get_msc_wait_arb(data)                            ((0x00000010&(data))>>4)
#define CBUS_MSC_00_get_ctrl_28_resv(data)                            (0x0000000F&(data))


#define CBUS_MSC_01                                                   0x1800f264
#define CBUS_MSC_01_reg_addr                                          "0xb800f264"
#define CBUS_MSC_01_reg                                               0xb800f264
#define CBUS_MSC_01_inst_addr                                         "0x0099"
#define CBUS_MSC_01_inst                                              0x0099
#define CBUS_MSC_01_na_msc_cmd_shift                                  (0)
#define CBUS_MSC_01_na_msc_cmd_mask                                   (0x000000FF)
#define CBUS_MSC_01_na_msc_cmd(data)                                  (0x000000FF&(data))
#define CBUS_MSC_01_get_na_msc_cmd(data)                              (0x000000FF&(data))


#define CBUS_MSC_02                                                   0x1800f268
#define CBUS_MSC_02_reg_addr                                          "0xb800f268"
#define CBUS_MSC_02_reg                                               0xb800f268
#define CBUS_MSC_02_inst_addr                                         "0x009A"
#define CBUS_MSC_02_inst                                              0x009A
#define CBUS_MSC_02_na_msc_offset_shift                               (0)
#define CBUS_MSC_02_na_msc_offset_mask                                (0x000000FF)
#define CBUS_MSC_02_na_msc_offset(data)                               (0x000000FF&(data))
#define CBUS_MSC_02_get_na_msc_offset(data)                           (0x000000FF&(data))


#define CBUS_MSC_03                                                   0x1800f26c
#define CBUS_MSC_03_reg_addr                                          "0xb800f26c"
#define CBUS_MSC_03_reg                                               0xb800f26c
#define CBUS_MSC_03_inst_addr                                         "0x009B"
#define CBUS_MSC_03_inst                                              0x009B
#define CBUS_MSC_03_rx_fifo_full_shift                                (7)
#define CBUS_MSC_03_rx_fifo_empty_shift                               (6)
#define CBUS_MSC_03_rx_fifo_clr_shift                                 (5)
#define CBUS_MSC_03_na_rx_len_shift                                   (0)
#define CBUS_MSC_03_rx_fifo_full_mask                                 (0x00000080)
#define CBUS_MSC_03_rx_fifo_empty_mask                                (0x00000040)
#define CBUS_MSC_03_rx_fifo_clr_mask                                  (0x00000020)
#define CBUS_MSC_03_na_rx_len_mask                                    (0x0000001F)
#define CBUS_MSC_03_rx_fifo_full(data)                                (0x00000080&((data)<<7))
#define CBUS_MSC_03_rx_fifo_empty(data)                               (0x00000040&((data)<<6))
#define CBUS_MSC_03_rx_fifo_clr(data)                                 (0x00000020&((data)<<5))
#define CBUS_MSC_03_na_rx_len(data)                                   (0x0000001F&(data))
#define CBUS_MSC_03_get_rx_fifo_full(data)                            ((0x00000080&(data))>>7)
#define CBUS_MSC_03_get_rx_fifo_empty(data)                           ((0x00000040&(data))>>6)
#define CBUS_MSC_03_get_rx_fifo_clr(data)                             ((0x00000020&(data))>>5)
#define CBUS_MSC_03_get_na_rx_len(data)                               (0x0000001F&(data))


#define CBUS_MSC_04                                                   0x1800f270
#define CBUS_MSC_04_reg_addr                                          "0xb800f270"
#define CBUS_MSC_04_reg                                               0xb800f270
#define CBUS_MSC_04_inst_addr                                         "0x009C"
#define CBUS_MSC_04_inst                                              0x009C
#define CBUS_MSC_04_rx_fifo_data_shift                                (0)
#define CBUS_MSC_04_rx_fifo_data_mask                                 (0x000000FF)
#define CBUS_MSC_04_rx_fifo_data(data)                                (0x000000FF&(data))
#define CBUS_MSC_04_get_rx_fifo_data(data)                            (0x000000FF&(data))


#define CBUS_MSC_05                                                   0x1800f274
#define CBUS_MSC_05_reg_addr                                          "0xb800f274"
#define CBUS_MSC_05_reg                                               0xb800f274
#define CBUS_MSC_05_inst_addr                                         "0x009D"
#define CBUS_MSC_05_inst                                              0x009D
#define CBUS_MSC_05_fwdef_cmd_rev_shift                               (0)
#define CBUS_MSC_05_fwdef_cmd_rev_mask                                (0x000000FF)
#define CBUS_MSC_05_fwdef_cmd_rev(data)                               (0x000000FF&(data))
#define CBUS_MSC_05_get_fwdef_cmd_rev(data)                           (0x000000FF&(data))


#define CBUS_MSC_06                                                   0x1800f278
#define CBUS_MSC_06_reg_addr                                          "0xb800f278"
#define CBUS_MSC_06_reg                                               0xb800f278
#define CBUS_MSC_06_inst_addr                                         "0x009E"
#define CBUS_MSC_06_inst                                              0x009E
#define CBUS_MSC_06_ucp_irq_shift                                     (28)
#define CBUS_MSC_06_ucpk_irq_shift                                    (27)
#define CBUS_MSC_06_ucpe_irq_shift                                    (26)
#define CBUS_MSC_06_dcap_rdy_chg_shift                                (25)
#define CBUS_MSC_06_muted_chg_shift                                   (24)
#define CBUS_MSC_06_path_en_chg_shift                                 (23)
#define CBUS_MSC_06_clk_mode_chg_shift                                (22)
#define CBUS_MSC_06_msge_irq_shift                                    (21)
#define CBUS_MSC_06_rcp_irq_shift                                     (20)
#define CBUS_MSC_06_rcpk_irq_shift                                    (19)
#define CBUS_MSC_06_rcpe_irq_shift                                    (18)
#define CBUS_MSC_06_rap_irq_shift                                     (17)
#define CBUS_MSC_06_rapk_irq_shift                                    (16)
#define CBUS_MSC_06_msg_sub_irq_shift                                 (15)
#define CBUS_MSC_06_wr_stat_irq_shift                                 (14)
#define CBUS_MSC_06_rd_devcap_irq_shift                               (13)
#define CBUS_MSC_06_get_stat_irq_shift                                (12)
#define CBUS_MSC_06_get_id_irq_shift                                  (11)
#define CBUS_MSC_06_get_msg_irq_shift                                 (10)
#define CBUS_MSC_06_sc1_err_irq_shift                                 (9)
#define CBUS_MSC_06_ddc_err_irq_shift                                 (8)
#define CBUS_MSC_06_msc_err_irq_shift                                 (7)
#define CBUS_MSC_06_wr_burst_irq_shift                                (6)
#define CBUS_MSC_06_sc3_err_irq_shift                                 (5)
#define CBUS_MSC_06_fwdef_cmd_irq_shift                               (4)
#define CBUS_MSC_06_allmsc_cmd_irq_shift                              (3)
#define CBUS_MSC_06_abort_res_irq_shift                               (2)
#define CBUS_MSC_06_abort_req_irq_shift                               (1)
#define CBUS_MSC_06_ddc_abort_irq_shift                               (0)
#define CBUS_MSC_06_ucp_irq_mask                                      (0x10000000)
#define CBUS_MSC_06_ucpk_irq_mask                                     (0x08000000)
#define CBUS_MSC_06_ucpe_irq_mask                                     (0x04000000)
#define CBUS_MSC_06_dcap_rdy_chg_mask                                 (0x02000000)
#define CBUS_MSC_06_muted_chg_mask                                    (0x01000000)
#define CBUS_MSC_06_path_en_chg_mask                                  (0x00800000)
#define CBUS_MSC_06_clk_mode_chg_mask                                 (0x00400000)
#define CBUS_MSC_06_msge_irq_mask                                     (0x00200000)
#define CBUS_MSC_06_rcp_irq_mask                                      (0x00100000)
#define CBUS_MSC_06_rcpk_irq_mask                                     (0x00080000)
#define CBUS_MSC_06_rcpe_irq_mask                                     (0x00040000)
#define CBUS_MSC_06_rap_irq_mask                                      (0x00020000)
#define CBUS_MSC_06_rapk_irq_mask                                     (0x00010000)
#define CBUS_MSC_06_msg_sub_irq_mask                                  (0x00008000)
#define CBUS_MSC_06_wr_stat_irq_mask                                  (0x00004000)
#define CBUS_MSC_06_rd_devcap_irq_mask                                (0x00002000)
#define CBUS_MSC_06_get_stat_irq_mask                                 (0x00001000)
#define CBUS_MSC_06_get_id_irq_mask                                   (0x00000800)
#define CBUS_MSC_06_get_msg_irq_mask                                  (0x00000400)
#define CBUS_MSC_06_sc1_err_irq_mask                                  (0x00000200)
#define CBUS_MSC_06_ddc_err_irq_mask                                  (0x00000100)
#define CBUS_MSC_06_msc_err_irq_mask                                  (0x00000080)
#define CBUS_MSC_06_wr_burst_irq_mask                                 (0x00000040)
#define CBUS_MSC_06_sc3_err_irq_mask                                  (0x00000020)
#define CBUS_MSC_06_fwdef_cmd_irq_mask                                (0x00000010)
#define CBUS_MSC_06_allmsc_cmd_irq_mask                               (0x00000008)
#define CBUS_MSC_06_abort_res_irq_mask                                (0x00000004)
#define CBUS_MSC_06_abort_req_irq_mask                                (0x00000002)
#define CBUS_MSC_06_ddc_abort_irq_mask                                (0x00000001)
#define CBUS_MSC_06_ucp_irq(data)                                     (0x10000000&((data)<<28))
#define CBUS_MSC_06_ucpk_irq(data)                                    (0x08000000&((data)<<27))
#define CBUS_MSC_06_ucpe_irq(data)                                    (0x04000000&((data)<<26))
#define CBUS_MSC_06_dcap_rdy_chg(data)                                (0x02000000&((data)<<25))
#define CBUS_MSC_06_muted_chg(data)                                   (0x01000000&((data)<<24))
#define CBUS_MSC_06_path_en_chg(data)                                 (0x00800000&((data)<<23))
#define CBUS_MSC_06_clk_mode_chg(data)                                (0x00400000&((data)<<22))
#define CBUS_MSC_06_msge_irq(data)                                    (0x00200000&((data)<<21))
#define CBUS_MSC_06_rcp_irq(data)                                     (0x00100000&((data)<<20))
#define CBUS_MSC_06_rcpk_irq(data)                                    (0x00080000&((data)<<19))
#define CBUS_MSC_06_rcpe_irq(data)                                    (0x00040000&((data)<<18))
#define CBUS_MSC_06_rap_irq(data)                                     (0x00020000&((data)<<17))
#define CBUS_MSC_06_rapk_irq(data)                                    (0x00010000&((data)<<16))
#define CBUS_MSC_06_msg_sub_irq(data)                                 (0x00008000&((data)<<15))
#define CBUS_MSC_06_wr_stat_irq(data)                                 (0x00004000&((data)<<14))
#define CBUS_MSC_06_rd_devcap_irq(data)                               (0x00002000&((data)<<13))
#define CBUS_MSC_06_get_stat_irq(data)                                (0x00001000&((data)<<12))
#define CBUS_MSC_06_get_id_irq(data)                                  (0x00000800&((data)<<11))
#define CBUS_MSC_06_get_msg_irq(data)                                 (0x00000400&((data)<<10))
#define CBUS_MSC_06_sc1_err_irq(data)                                 (0x00000200&((data)<<9))
#define CBUS_MSC_06_ddc_err_irq(data)                                 (0x00000100&((data)<<8))
#define CBUS_MSC_06_msc_err_irq(data)                                 (0x00000080&((data)<<7))
#define CBUS_MSC_06_wr_burst_irq(data)                                (0x00000040&((data)<<6))
#define CBUS_MSC_06_sc3_err_irq(data)                                 (0x00000020&((data)<<5))
#define CBUS_MSC_06_fwdef_cmd_irq(data)                               (0x00000010&((data)<<4))
#define CBUS_MSC_06_allmsc_cmd_irq(data)                              (0x00000008&((data)<<3))
#define CBUS_MSC_06_abort_res_irq(data)                               (0x00000004&((data)<<2))
#define CBUS_MSC_06_abort_req_irq(data)                               (0x00000002&((data)<<1))
#define CBUS_MSC_06_ddc_abort_irq(data)                               (0x00000001&(data))
#define CBUS_MSC_06_get_ucp_irq(data)                                 ((0x10000000&(data))>>28)
#define CBUS_MSC_06_get_ucpk_irq(data)                                ((0x08000000&(data))>>27)
#define CBUS_MSC_06_get_ucpe_irq(data)                                ((0x04000000&(data))>>26)
#define CBUS_MSC_06_get_dcap_rdy_chg(data)                            ((0x02000000&(data))>>25)
#define CBUS_MSC_06_get_muted_chg(data)                               ((0x01000000&(data))>>24)
#define CBUS_MSC_06_get_path_en_chg(data)                             ((0x00800000&(data))>>23)
#define CBUS_MSC_06_get_clk_mode_chg(data)                            ((0x00400000&(data))>>22)
#define CBUS_MSC_06_get_msge_irq(data)                                ((0x00200000&(data))>>21)
#define CBUS_MSC_06_get_rcp_irq(data)                                 ((0x00100000&(data))>>20)
#define CBUS_MSC_06_get_rcpk_irq(data)                                ((0x00080000&(data))>>19)
#define CBUS_MSC_06_get_rcpe_irq(data)                                ((0x00040000&(data))>>18)
#define CBUS_MSC_06_get_rap_irq(data)                                 ((0x00020000&(data))>>17)
#define CBUS_MSC_06_get_rapk_irq(data)                                ((0x00010000&(data))>>16)
#define CBUS_MSC_06_get_msg_sub_irq(data)                             ((0x00008000&(data))>>15)
#define CBUS_MSC_06_get_wr_stat_irq(data)                             ((0x00004000&(data))>>14)
#define CBUS_MSC_06_get_rd_devcap_irq(data)                           ((0x00002000&(data))>>13)
#define CBUS_MSC_06_get_get_stat_irq(data)                            ((0x00001000&(data))>>12)
#define CBUS_MSC_06_get_get_id_irq(data)                              ((0x00000800&(data))>>11)
#define CBUS_MSC_06_get_get_msg_irq(data)                             ((0x00000400&(data))>>10)
#define CBUS_MSC_06_get_sc1_err_irq(data)                             ((0x00000200&(data))>>9)
#define CBUS_MSC_06_get_ddc_err_irq(data)                             ((0x00000100&(data))>>8)
#define CBUS_MSC_06_get_msc_err_irq(data)                             ((0x00000080&(data))>>7)
#define CBUS_MSC_06_get_wr_burst_irq(data)                            ((0x00000040&(data))>>6)
#define CBUS_MSC_06_get_sc3_err_irq(data)                             ((0x00000020&(data))>>5)
#define CBUS_MSC_06_get_fwdef_cmd_irq(data)                           ((0x00000010&(data))>>4)
#define CBUS_MSC_06_get_allmsc_cmd_irq(data)                          ((0x00000008&(data))>>3)
#define CBUS_MSC_06_get_abort_res_irq(data)                           ((0x00000004&(data))>>2)
#define CBUS_MSC_06_get_abort_req_irq(data)                           ((0x00000002&(data))>>1)
#define CBUS_MSC_06_get_ddc_abort_irq(data)                           (0x00000001&(data))


#define CBUS_MSC_07                                                   0x1800f27c
#define CBUS_MSC_07_reg_addr                                          "0xb800f27c"
#define CBUS_MSC_07_reg                                               0xb800f27c
#define CBUS_MSC_07_inst_addr                                         "0x009F"
#define CBUS_MSC_07_inst                                              0x009F
#define CBUS_MSC_07_ucp_irq_en_shift                                  (28)
#define CBUS_MSC_07_ucpk_irq_en_shift                                 (27)
#define CBUS_MSC_07_ucpe_irq_en_shift                                 (26)
#define CBUS_MSC_07_dcap_rdy_irq_en_shift                             (25)
#define CBUS_MSC_07_muted_chg_irq_en_shift                            (24)
#define CBUS_MSC_07_path_en_irq_en_shift                              (23)
#define CBUS_MSC_07_clk_mode_irq_en_shift                             (22)
#define CBUS_MSC_07_msge_irq_en_shift                                 (21)
#define CBUS_MSC_07_rcp_irq_en_shift                                  (20)
#define CBUS_MSC_07_rcpk_irq_en_shift                                 (19)
#define CBUS_MSC_07_rcpe_irq_en_shift                                 (18)
#define CBUS_MSC_07_rap_irq_en_shift                                  (17)
#define CBUS_MSC_07_rapk_irq_en_shift                                 (16)
#define CBUS_MSC_07_msg_sub_irq_en_shift                              (15)
#define CBUS_MSC_07_wr_stat_irq_en_shift                              (14)
#define CBUS_MSC_07_rd_devcap_irq_en_shift                            (13)
#define CBUS_MSC_07_get_stat_irq_en_shift                             (12)
#define CBUS_MSC_07_get_id_irq_en_shift                               (11)
#define CBUS_MSC_07_get_msg_irq_en_shift                              (10)
#define CBUS_MSC_07_sc1_err_irq_en_shift                              (9)
#define CBUS_MSC_07_ddc_err_irq_en_shift                              (8)
#define CBUS_MSC_07_msc_err_irq_en_shift                              (7)
#define CBUS_MSC_07_wr_burst_irq_en_shift                             (6)
#define CBUS_MSC_07_sc3_err_irq_en_shift                              (5)
#define CBUS_MSC_07_fwdef_cmd_irq_en_shift                            (4)
#define CBUS_MSC_07_allmsc_cmd_irq_en_shift                           (3)
#define CBUS_MSC_07_abort_res_irq_en_shift                            (2)
#define CBUS_MSC_07_abort_req_irq_en_shift                            (1)
#define CBUS_MSC_07_ddc_abort_irq_en_shift                            (0)
#define CBUS_MSC_07_ucp_irq_en_mask                                   (0x10000000)
#define CBUS_MSC_07_ucpk_irq_en_mask                                  (0x08000000)
#define CBUS_MSC_07_ucpe_irq_en_mask                                  (0x04000000)
#define CBUS_MSC_07_dcap_rdy_irq_en_mask                              (0x02000000)
#define CBUS_MSC_07_muted_chg_irq_en_mask                             (0x01000000)
#define CBUS_MSC_07_path_en_irq_en_mask                               (0x00800000)
#define CBUS_MSC_07_clk_mode_irq_en_mask                              (0x00400000)
#define CBUS_MSC_07_msge_irq_en_mask                                  (0x00200000)
#define CBUS_MSC_07_rcp_irq_en_mask                                   (0x00100000)
#define CBUS_MSC_07_rcpk_irq_en_mask                                  (0x00080000)
#define CBUS_MSC_07_rcpe_irq_en_mask                                  (0x00040000)
#define CBUS_MSC_07_rap_irq_en_mask                                   (0x00020000)
#define CBUS_MSC_07_rapk_irq_en_mask                                  (0x00010000)
#define CBUS_MSC_07_msg_sub_irq_en_mask                               (0x00008000)
#define CBUS_MSC_07_wr_stat_irq_en_mask                               (0x00004000)
#define CBUS_MSC_07_rd_devcap_irq_en_mask                             (0x00002000)
#define CBUS_MSC_07_get_stat_irq_en_mask                              (0x00001000)
#define CBUS_MSC_07_get_id_irq_en_mask                                (0x00000800)
#define CBUS_MSC_07_get_msg_irq_en_mask                               (0x00000400)
#define CBUS_MSC_07_sc1_err_irq_en_mask                               (0x00000200)
#define CBUS_MSC_07_ddc_err_irq_en_mask                               (0x00000100)
#define CBUS_MSC_07_msc_err_irq_en_mask                               (0x00000080)
#define CBUS_MSC_07_wr_burst_irq_en_mask                              (0x00000040)
#define CBUS_MSC_07_sc3_err_irq_en_mask                               (0x00000020)
#define CBUS_MSC_07_fwdef_cmd_irq_en_mask                             (0x00000010)
#define CBUS_MSC_07_allmsc_cmd_irq_en_mask                            (0x00000008)
#define CBUS_MSC_07_abort_res_irq_en_mask                             (0x00000004)
#define CBUS_MSC_07_abort_req_irq_en_mask                             (0x00000002)
#define CBUS_MSC_07_ddc_abort_irq_en_mask                             (0x00000001)
#define CBUS_MSC_07_ucp_irq_en(data)                                  (0x10000000&((data)<<28))
#define CBUS_MSC_07_ucpk_irq_en(data)                                 (0x08000000&((data)<<27))
#define CBUS_MSC_07_ucpe_irq_en(data)                                 (0x04000000&((data)<<26))
#define CBUS_MSC_07_dcap_rdy_irq_en(data)                             (0x02000000&((data)<<25))
#define CBUS_MSC_07_muted_chg_irq_en(data)                            (0x01000000&((data)<<24))
#define CBUS_MSC_07_path_en_irq_en(data)                              (0x00800000&((data)<<23))
#define CBUS_MSC_07_clk_mode_irq_en(data)                             (0x00400000&((data)<<22))
#define CBUS_MSC_07_msge_irq_en(data)                                 (0x00200000&((data)<<21))
#define CBUS_MSC_07_rcp_irq_en(data)                                  (0x00100000&((data)<<20))
#define CBUS_MSC_07_rcpk_irq_en(data)                                 (0x00080000&((data)<<19))
#define CBUS_MSC_07_rcpe_irq_en(data)                                 (0x00040000&((data)<<18))
#define CBUS_MSC_07_rap_irq_en(data)                                  (0x00020000&((data)<<17))
#define CBUS_MSC_07_rapk_irq_en(data)                                 (0x00010000&((data)<<16))
#define CBUS_MSC_07_msg_sub_irq_en(data)                              (0x00008000&((data)<<15))
#define CBUS_MSC_07_wr_stat_irq_en(data)                              (0x00004000&((data)<<14))
#define CBUS_MSC_07_rd_devcap_irq_en(data)                            (0x00002000&((data)<<13))
#define CBUS_MSC_07_get_stat_irq_en(data)                             (0x00001000&((data)<<12))
#define CBUS_MSC_07_get_id_irq_en(data)                               (0x00000800&((data)<<11))
#define CBUS_MSC_07_get_msg_irq_en(data)                              (0x00000400&((data)<<10))
#define CBUS_MSC_07_sc1_err_irq_en(data)                              (0x00000200&((data)<<9))
#define CBUS_MSC_07_ddc_err_irq_en(data)                              (0x00000100&((data)<<8))
#define CBUS_MSC_07_msc_err_irq_en(data)                              (0x00000080&((data)<<7))
#define CBUS_MSC_07_wr_burst_irq_en(data)                             (0x00000040&((data)<<6))
#define CBUS_MSC_07_sc3_err_irq_en(data)                              (0x00000020&((data)<<5))
#define CBUS_MSC_07_fwdef_cmd_irq_en(data)                            (0x00000010&((data)<<4))
#define CBUS_MSC_07_allmsc_cmd_irq_en(data)                           (0x00000008&((data)<<3))
#define CBUS_MSC_07_abort_res_irq_en(data)                            (0x00000004&((data)<<2))
#define CBUS_MSC_07_abort_req_irq_en(data)                            (0x00000002&((data)<<1))
#define CBUS_MSC_07_ddc_abort_irq_en(data)                            (0x00000001&(data))
#define CBUS_MSC_07_get_ucp_irq_en(data)                              ((0x10000000&(data))>>28)
#define CBUS_MSC_07_get_ucpk_irq_en(data)                             ((0x08000000&(data))>>27)
#define CBUS_MSC_07_get_ucpe_irq_en(data)                             ((0x04000000&(data))>>26)
#define CBUS_MSC_07_get_dcap_rdy_irq_en(data)                         ((0x02000000&(data))>>25)
#define CBUS_MSC_07_get_muted_chg_irq_en(data)                        ((0x01000000&(data))>>24)
#define CBUS_MSC_07_get_path_en_irq_en(data)                          ((0x00800000&(data))>>23)
#define CBUS_MSC_07_get_clk_mode_irq_en(data)                         ((0x00400000&(data))>>22)
#define CBUS_MSC_07_get_msge_irq_en(data)                             ((0x00200000&(data))>>21)
#define CBUS_MSC_07_get_rcp_irq_en(data)                              ((0x00100000&(data))>>20)
#define CBUS_MSC_07_get_rcpk_irq_en(data)                             ((0x00080000&(data))>>19)
#define CBUS_MSC_07_get_rcpe_irq_en(data)                             ((0x00040000&(data))>>18)
#define CBUS_MSC_07_get_rap_irq_en(data)                              ((0x00020000&(data))>>17)
#define CBUS_MSC_07_get_rapk_irq_en(data)                             ((0x00010000&(data))>>16)
#define CBUS_MSC_07_get_msg_sub_irq_en(data)                          ((0x00008000&(data))>>15)
#define CBUS_MSC_07_get_wr_stat_irq_en(data)                          ((0x00004000&(data))>>14)
#define CBUS_MSC_07_get_rd_devcap_irq_en(data)                        ((0x00002000&(data))>>13)
#define CBUS_MSC_07_get_get_stat_irq_en(data)                         ((0x00001000&(data))>>12)
#define CBUS_MSC_07_get_get_id_irq_en(data)                           ((0x00000800&(data))>>11)
#define CBUS_MSC_07_get_get_msg_irq_en(data)                          ((0x00000400&(data))>>10)
#define CBUS_MSC_07_get_sc1_err_irq_en(data)                          ((0x00000200&(data))>>9)
#define CBUS_MSC_07_get_ddc_err_irq_en(data)                          ((0x00000100&(data))>>8)
#define CBUS_MSC_07_get_msc_err_irq_en(data)                          ((0x00000080&(data))>>7)
#define CBUS_MSC_07_get_wr_burst_irq_en(data)                         ((0x00000040&(data))>>6)
#define CBUS_MSC_07_get_sc3_err_irq_en(data)                          ((0x00000020&(data))>>5)
#define CBUS_MSC_07_get_fwdef_cmd_irq_en(data)                        ((0x00000010&(data))>>4)
#define CBUS_MSC_07_get_allmsc_cmd_irq_en(data)                       ((0x00000008&(data))>>3)
#define CBUS_MSC_07_get_abort_res_irq_en(data)                        ((0x00000004&(data))>>2)
#define CBUS_MSC_07_get_abort_req_irq_en(data)                        ((0x00000002&(data))>>1)
#define CBUS_MSC_07_get_ddc_abort_irq_en(data)                        (0x00000001&(data))


#define CBUS_MSC_08                                                   0x1800f280
#define CBUS_MSC_08_reg_addr                                          "0xb800f280"
#define CBUS_MSC_08_reg                                               0xb800f280
#define CBUS_MSC_08_inst_addr                                         "0x00A0"
#define CBUS_MSC_08_inst                                              0x00A0
#define CBUS_MSC_08_rchg_irq_en_shift                                 (29)
#define CBUS_MSC_08_cbus_3d_req_irq_en_shift                          (28)
#define CBUS_MSC_08_grt_irq_en_shift                                  (27)
#define CBUS_MSC_08_req_irq_en_shift                                  (26)
#define CBUS_MSC_08_dscr_irq_en_shift                                 (25)
#define CBUS_MSC_08_dcap_irq_en_shift                                 (24)
#define CBUS_MSC_08_dchg_bit7_irq_en_shift                            (23)
#define CBUS_MSC_08_dchg_bit6_irq_en_shift                            (22)
#define CBUS_MSC_08_dchg_bit5_irq_en_shift                            (21)
#define CBUS_MSC_08_dchg_bit4_irq_en_shift                            (20)
#define CBUS_MSC_08_dchg_bit3_irq_en_shift                            (19)
#define CBUS_MSC_08_dchg_bit2_irq_en_shift                            (18)
#define CBUS_MSC_08_edid_irq_en_shift                                 (17)
#define CBUS_MSC_08_dchg_bit0_irq_en_shift                            (16)
#define CBUS_MSC_08_chg22_irq_en_shift                                (8)
#define CBUS_MSC_08_chg23_irq_en_shift                                (0)
#define CBUS_MSC_08_rchg_irq_en_mask                                  (0xE0000000)
#define CBUS_MSC_08_cbus_3d_req_irq_en_mask                           (0x10000000)
#define CBUS_MSC_08_grt_irq_en_mask                                   (0x08000000)
#define CBUS_MSC_08_req_irq_en_mask                                   (0x04000000)
#define CBUS_MSC_08_dscr_irq_en_mask                                  (0x02000000)
#define CBUS_MSC_08_dcap_irq_en_mask                                  (0x01000000)
#define CBUS_MSC_08_dchg_bit7_irq_en_mask                             (0x00800000)
#define CBUS_MSC_08_dchg_bit6_irq_en_mask                             (0x00400000)
#define CBUS_MSC_08_dchg_bit5_irq_en_mask                             (0x00200000)
#define CBUS_MSC_08_dchg_bit4_irq_en_mask                             (0x00100000)
#define CBUS_MSC_08_dchg_bit3_irq_en_mask                             (0x00080000)
#define CBUS_MSC_08_dchg_bit2_irq_en_mask                             (0x00040000)
#define CBUS_MSC_08_edid_irq_en_mask                                  (0x00020000)
#define CBUS_MSC_08_dchg_bit0_irq_en_mask                             (0x00010000)
#define CBUS_MSC_08_chg22_irq_en_mask                                 (0x0000FF00)
#define CBUS_MSC_08_chg23_irq_en_mask                                 (0x000000FF)
#define CBUS_MSC_08_rchg_irq_en(data)                                 (0xE0000000&((data)<<29))
#define CBUS_MSC_08_cbus_3d_req_irq_en(data)                          (0x10000000&((data)<<28))
#define CBUS_MSC_08_grt_irq_en(data)                                  (0x08000000&((data)<<27))
#define CBUS_MSC_08_req_irq_en(data)                                  (0x04000000&((data)<<26))
#define CBUS_MSC_08_dscr_irq_en(data)                                 (0x02000000&((data)<<25))
#define CBUS_MSC_08_dcap_irq_en(data)                                 (0x01000000&((data)<<24))
#define CBUS_MSC_08_dchg_bit7_irq_en(data)                            (0x00800000&((data)<<23))
#define CBUS_MSC_08_dchg_bit6_irq_en(data)                            (0x00400000&((data)<<22))
#define CBUS_MSC_08_dchg_bit5_irq_en(data)                            (0x00200000&((data)<<21))
#define CBUS_MSC_08_dchg_bit4_irq_en(data)                            (0x00100000&((data)<<20))
#define CBUS_MSC_08_dchg_bit3_irq_en(data)                            (0x00080000&((data)<<19))
#define CBUS_MSC_08_dchg_bit2_irq_en(data)                            (0x00040000&((data)<<18))
#define CBUS_MSC_08_edid_irq_en(data)                                 (0x00020000&((data)<<17))
#define CBUS_MSC_08_dchg_bit0_irq_en(data)                            (0x00010000&((data)<<16))
#define CBUS_MSC_08_chg22_irq_en(data)                                (0x0000FF00&((data)<<8))
#define CBUS_MSC_08_chg23_irq_en(data)                                (0x000000FF&(data))
#define CBUS_MSC_08_get_rchg_irq_en(data)                             ((0xE0000000&(data))>>29)
#define CBUS_MSC_08_get_cbus_3d_req_irq_en(data)                      ((0x10000000&(data))>>28)
#define CBUS_MSC_08_get_grt_irq_en(data)                              ((0x08000000&(data))>>27)
#define CBUS_MSC_08_get_req_irq_en(data)                              ((0x04000000&(data))>>26)
#define CBUS_MSC_08_get_dscr_irq_en(data)                             ((0x02000000&(data))>>25)
#define CBUS_MSC_08_get_dcap_irq_en(data)                             ((0x01000000&(data))>>24)
#define CBUS_MSC_08_get_dchg_bit7_irq_en(data)                        ((0x00800000&(data))>>23)
#define CBUS_MSC_08_get_dchg_bit6_irq_en(data)                        ((0x00400000&(data))>>22)
#define CBUS_MSC_08_get_dchg_bit5_irq_en(data)                        ((0x00200000&(data))>>21)
#define CBUS_MSC_08_get_dchg_bit4_irq_en(data)                        ((0x00100000&(data))>>20)
#define CBUS_MSC_08_get_dchg_bit3_irq_en(data)                        ((0x00080000&(data))>>19)
#define CBUS_MSC_08_get_dchg_bit2_irq_en(data)                        ((0x00040000&(data))>>18)
#define CBUS_MSC_08_get_edid_irq_en(data)                             ((0x00020000&(data))>>17)
#define CBUS_MSC_08_get_dchg_bit0_irq_en(data)                        ((0x00010000&(data))>>16)
#define CBUS_MSC_08_get_chg22_irq_en(data)                            ((0x0000FF00&(data))>>8)
#define CBUS_MSC_08_get_chg23_irq_en(data)                            (0x000000FF&(data))


#define CBUS_MSC_09                                                   0x1800f284
#define CBUS_MSC_09_reg_addr                                          "0xb800f284"
#define CBUS_MSC_09_reg                                               0xb800f284
#define CBUS_MSC_09_inst_addr                                         "0x00A1"
#define CBUS_MSC_09_inst                                              0x00A1
#define CBUS_MSC_09_chg24_irq_en_shift                                (24)
#define CBUS_MSC_09_chg25_irq_en_shift                                (16)
#define CBUS_MSC_09_chg26_irq_en_shift                                (8)
#define CBUS_MSC_09_chg27_irq_en_shift                                (0)
#define CBUS_MSC_09_chg24_irq_en_mask                                 (0xFF000000)
#define CBUS_MSC_09_chg25_irq_en_mask                                 (0x00FF0000)
#define CBUS_MSC_09_chg26_irq_en_mask                                 (0x0000FF00)
#define CBUS_MSC_09_chg27_irq_en_mask                                 (0x000000FF)
#define CBUS_MSC_09_chg24_irq_en(data)                                (0xFF000000&((data)<<24))
#define CBUS_MSC_09_chg25_irq_en(data)                                (0x00FF0000&((data)<<16))
#define CBUS_MSC_09_chg26_irq_en(data)                                (0x0000FF00&((data)<<8))
#define CBUS_MSC_09_chg27_irq_en(data)                                (0x000000FF&(data))
#define CBUS_MSC_09_get_chg24_irq_en(data)                            ((0xFF000000&(data))>>24)
#define CBUS_MSC_09_get_chg25_irq_en(data)                            ((0x00FF0000&(data))>>16)
#define CBUS_MSC_09_get_chg26_irq_en(data)                            ((0x0000FF00&(data))>>8)
#define CBUS_MSC_09_get_chg27_irq_en(data)                            (0x000000FF&(data))


#define CBUS_MSC_0A                                                   0x1800f288
#define CBUS_MSC_0A_reg_addr                                          "0xb800f288"
#define CBUS_MSC_0A_reg                                               0xb800f288
#define CBUS_MSC_0A_inst_addr                                         "0x00A2"
#define CBUS_MSC_0A_inst                                              0x00A2
#define CBUS_MSC_0A_msc_err_code_shift                                (0)
#define CBUS_MSC_0A_msc_err_code_mask                                 (0x000000FF)
#define CBUS_MSC_0A_msc_err_code(data)                                (0x000000FF&(data))
#define CBUS_MSC_0A_get_msc_err_code(data)                            (0x000000FF&(data))


#define CBUS_MSC_0B                                                   0x1800f28c
#define CBUS_MSC_0B_reg_addr                                          "0xb800f28c"
#define CBUS_MSC_0B_reg                                               0xb800f28c
#define CBUS_MSC_0B_inst_addr                                         "0x00A3"
#define CBUS_MSC_0B_inst                                              0x00A3
#define CBUS_MSC_0B_rcp_reply_abort_shift                             (9)
#define CBUS_MSC_0B_rcp_reply_nack_shift                              (8)
#define CBUS_MSC_0B_vendor_id_shift                                   (0)
#define CBUS_MSC_0B_rcp_reply_abort_mask                              (0x00000200)
#define CBUS_MSC_0B_rcp_reply_nack_mask                               (0x00000100)
#define CBUS_MSC_0B_vendor_id_mask                                    (0x000000FF)
#define CBUS_MSC_0B_rcp_reply_abort(data)                             (0x00000200&((data)<<9))
#define CBUS_MSC_0B_rcp_reply_nack(data)                              (0x00000100&((data)<<8))
#define CBUS_MSC_0B_vendor_id(data)                                   (0x000000FF&(data))
#define CBUS_MSC_0B_get_rcp_reply_abort(data)                         ((0x00000200&(data))>>9)
#define CBUS_MSC_0B_get_rcp_reply_nack(data)                          ((0x00000100&(data))>>8)
#define CBUS_MSC_0B_get_vendor_id(data)                               (0x000000FF&(data))


#define CBUS_MSC_0C                                                   0x1800f290
#define CBUS_MSC_0C_reg_addr                                          "0xb800f290"
#define CBUS_MSC_0C_reg                                               0xb800f290
#define CBUS_MSC_0C_inst_addr                                         "0x00A4"
#define CBUS_MSC_0C_inst                                              0x00A4
#define CBUS_MSC_0C_msg_cmd_shift                                     (0)
#define CBUS_MSC_0C_msg_cmd_mask                                      (0x000000FF)
#define CBUS_MSC_0C_msg_cmd(data)                                     (0x000000FF&(data))
#define CBUS_MSC_0C_get_msg_cmd(data)                                 (0x000000FF&(data))


#define CBUS_MSC_0D                                                   0x1800f294
#define CBUS_MSC_0D_reg_addr                                          "0xb800f294"
#define CBUS_MSC_0D_reg                                               0xb800f294
#define CBUS_MSC_0D_inst_addr                                         "0x00A5"
#define CBUS_MSC_0D_inst                                              0x00A5
#define CBUS_MSC_0D_msg_dat_shift                                     (0)
#define CBUS_MSC_0D_msg_dat_mask                                      (0x000000FF)
#define CBUS_MSC_0D_msg_dat(data)                                     (0x000000FF&(data))
#define CBUS_MSC_0D_get_msg_dat(data)                                 (0x000000FF&(data))


#define CBUS_MSC_0E                                                   0x1800f298
#define CBUS_MSC_0E_reg_addr                                          "0xb800f298"
#define CBUS_MSC_0E_reg                                               0xb800f298
#define CBUS_MSC_0E_inst_addr                                         "0x00A6"
#define CBUS_MSC_0E_inst                                              0x00A6
#define CBUS_MSC_0E_msge_rcv_shift                                    (0)
#define CBUS_MSC_0E_msge_rcv_mask                                     (0x000000FF)
#define CBUS_MSC_0E_msge_rcv(data)                                    (0x000000FF&(data))
#define CBUS_MSC_0E_get_msge_rcv(data)                                (0x000000FF&(data))


#define CBUS_MSC_0F                                                   0x1800f29c
#define CBUS_MSC_0F_reg_addr                                          "0xb800f29c"
#define CBUS_MSC_0F_reg                                               0xb800f29c
#define CBUS_MSC_0F_inst_addr                                         "0x00A7"
#define CBUS_MSC_0F_inst                                              0x00A7
#define CBUS_MSC_0F_rcp_rcv_shift                                     (0)
#define CBUS_MSC_0F_rcp_rcv_mask                                      (0x000000FF)
#define CBUS_MSC_0F_rcp_rcv(data)                                     (0x000000FF&(data))
#define CBUS_MSC_0F_get_rcp_rcv(data)                                 (0x000000FF&(data))


#define CBUS_MSC_10                                                   0x1800f2a0
#define CBUS_MSC_10_reg_addr                                          "0xb800f2a0"
#define CBUS_MSC_10_reg                                               0xb800f2a0
#define CBUS_MSC_10_inst_addr                                         "0x00A8"
#define CBUS_MSC_10_inst                                              0x00A8
#define CBUS_MSC_10_rcpk_rcv_shift                                    (0)
#define CBUS_MSC_10_rcpk_rcv_mask                                     (0x000000FF)
#define CBUS_MSC_10_rcpk_rcv(data)                                    (0x000000FF&(data))
#define CBUS_MSC_10_get_rcpk_rcv(data)                                (0x000000FF&(data))


#define CBUS_MSC_11                                                   0x1800f2a4
#define CBUS_MSC_11_reg_addr                                          "0xb800f2a4"
#define CBUS_MSC_11_reg                                               0xb800f2a4
#define CBUS_MSC_11_inst_addr                                         "0x00A9"
#define CBUS_MSC_11_inst                                              0x00A9
#define CBUS_MSC_11_rcpe_rcv_shift                                    (0)
#define CBUS_MSC_11_rcpe_rcv_mask                                     (0x000000FF)
#define CBUS_MSC_11_rcpe_rcv(data)                                    (0x000000FF&(data))
#define CBUS_MSC_11_get_rcpe_rcv(data)                                (0x000000FF&(data))


#define CBUS_MSC_12                                                   0x1800f2a8
#define CBUS_MSC_12_reg_addr                                          "0xb800f2a8"
#define CBUS_MSC_12_reg                                               0xb800f2a8
#define CBUS_MSC_12_inst_addr                                         "0x00AA"
#define CBUS_MSC_12_inst                                              0x00AA
#define CBUS_MSC_12_rap_rcv_shift                                     (0)
#define CBUS_MSC_12_rap_rcv_mask                                      (0x000000FF)
#define CBUS_MSC_12_rap_rcv(data)                                     (0x000000FF&(data))
#define CBUS_MSC_12_get_rap_rcv(data)                                 (0x000000FF&(data))


#define CBUS_MSC_13                                                   0x1800f2ac
#define CBUS_MSC_13_reg_addr                                          "0xb800f2ac"
#define CBUS_MSC_13_reg                                               0xb800f2ac
#define CBUS_MSC_13_inst_addr                                         "0x00AB"
#define CBUS_MSC_13_inst                                              0x00AB
#define CBUS_MSC_13_rapk_rcv_shift                                    (0)
#define CBUS_MSC_13_rapk_rcv_mask                                     (0x000000FF)
#define CBUS_MSC_13_rapk_rcv(data)                                    (0x000000FF&(data))
#define CBUS_MSC_13_get_rapk_rcv(data)                                (0x000000FF&(data))


#define CBUS_MSC_14                                                   0x1800f2b0
#define CBUS_MSC_14_reg_addr                                          "0xb800f2b0"
#define CBUS_MSC_14_reg                                               0xb800f2b0
#define CBUS_MSC_14_inst_addr                                         "0x00AC"
#define CBUS_MSC_14_inst                                              0x00AC
#define CBUS_MSC_14_burst_timeout_shift                               (5)
#define CBUS_MSC_14_wb_id_chk_shift                                   (4)
#define CBUS_MSC_14_burst_wait_shift                                  (0)
#define CBUS_MSC_14_burst_timeout_mask                                (0x00000020)
#define CBUS_MSC_14_wb_id_chk_mask                                    (0x00000010)
#define CBUS_MSC_14_burst_wait_mask                                   (0x0000000F)
#define CBUS_MSC_14_burst_timeout(data)                               (0x00000020&((data)<<5))
#define CBUS_MSC_14_wb_id_chk(data)                                   (0x00000010&((data)<<4))
#define CBUS_MSC_14_burst_wait(data)                                  (0x0000000F&(data))
#define CBUS_MSC_14_get_burst_timeout(data)                           ((0x00000020&(data))>>5)
#define CBUS_MSC_14_get_wb_id_chk(data)                               ((0x00000010&(data))>>4)
#define CBUS_MSC_14_get_burst_wait(data)                              (0x0000000F&(data))


#define CBUS_MSC_15                                                   0x1800f2b4
#define CBUS_MSC_15_reg_addr                                          "0xb800f2b4"
#define CBUS_MSC_15_reg                                               0xb800f2b4
#define CBUS_MSC_15_inst_addr                                         "0x00AD"
#define CBUS_MSC_15_inst                                              0x00AD
#define CBUS_MSC_15_adop_idh_rcv_shift                                (8)
#define CBUS_MSC_15_adop_idl_rcv_shift                                (0)
#define CBUS_MSC_15_adop_idh_rcv_mask                                 (0x0000FF00)
#define CBUS_MSC_15_adop_idl_rcv_mask                                 (0x000000FF)
#define CBUS_MSC_15_adop_idh_rcv(data)                                (0x0000FF00&((data)<<8))
#define CBUS_MSC_15_adop_idl_rcv(data)                                (0x000000FF&(data))
#define CBUS_MSC_15_get_adop_idh_rcv(data)                            ((0x0000FF00&(data))>>8)
#define CBUS_MSC_15_get_adop_idl_rcv(data)                            (0x000000FF&(data))


#define CBUS_MSC_16                                                   0x1800f2b8
#define CBUS_MSC_16_reg_addr                                          "0xb800f2b8"
#define CBUS_MSC_16_reg                                               0xb800f2b8
#define CBUS_MSC_16_inst_addr                                         "0x00AE"
#define CBUS_MSC_16_inst                                              0x00AE
#define CBUS_MSC_16_auto_handshake_shift                              (29)
#define CBUS_MSC_16_insert_id_shift                                   (28)
#define CBUS_MSC_16_wb_byte_num0_shift                                (22)
#define CBUS_MSC_16_wb_byte_num1_shift                                (16)
#define CBUS_MSC_16_adop_txid_h_shift                                 (8)
#define CBUS_MSC_16_adop_txid_l_shift                                 (0)
#define CBUS_MSC_16_auto_handshake_mask                               (0x20000000)
#define CBUS_MSC_16_insert_id_mask                                    (0x10000000)
#define CBUS_MSC_16_wb_byte_num0_mask                                 (0x0FC00000)
#define CBUS_MSC_16_wb_byte_num1_mask                                 (0x003F0000)
#define CBUS_MSC_16_adop_txid_h_mask                                  (0x0000FF00)
#define CBUS_MSC_16_adop_txid_l_mask                                  (0x000000FF)
#define CBUS_MSC_16_auto_handshake(data)                              (0x20000000&((data)<<29))
#define CBUS_MSC_16_insert_id(data)                                   (0x10000000&((data)<<28))
#define CBUS_MSC_16_wb_byte_num0(data)                                (0x0FC00000&((data)<<22))
#define CBUS_MSC_16_wb_byte_num1(data)                                (0x003F0000&((data)<<16))
#define CBUS_MSC_16_adop_txid_h(data)                                 (0x0000FF00&((data)<<8))
#define CBUS_MSC_16_adop_txid_l(data)                                 (0x000000FF&(data))
#define CBUS_MSC_16_get_auto_handshake(data)                          ((0x20000000&(data))>>29)
#define CBUS_MSC_16_get_insert_id(data)                               ((0x10000000&(data))>>28)
#define CBUS_MSC_16_get_wb_byte_num0(data)                            ((0x0FC00000&(data))>>22)
#define CBUS_MSC_16_get_wb_byte_num1(data)                            ((0x003F0000&(data))>>16)
#define CBUS_MSC_16_get_adop_txid_h(data)                             ((0x0000FF00&(data))>>8)
#define CBUS_MSC_16_get_adop_txid_l(data)                             (0x000000FF&(data))


#define CBUS_MSC_17                                                   0x1800f2bc
#define CBUS_MSC_17_reg_addr                                          "0xb800f2bc"
#define CBUS_MSC_17_reg                                               0xb800f2bc
#define CBUS_MSC_17_inst_addr                                         "0x00AF"
#define CBUS_MSC_17_inst                                              0x00AF
#define CBUS_MSC_17_que_fsm_clr_shift                                 (2)
#define CBUS_MSC_17_sch_fsm_clr_shift                                 (1)
#define CBUS_MSC_17_spi_fsm_clr_shift                                 (0)
#define CBUS_MSC_17_que_fsm_clr_mask                                  (0x00000004)
#define CBUS_MSC_17_sch_fsm_clr_mask                                  (0x00000002)
#define CBUS_MSC_17_spi_fsm_clr_mask                                  (0x00000001)
#define CBUS_MSC_17_que_fsm_clr(data)                                 (0x00000004&((data)<<2))
#define CBUS_MSC_17_sch_fsm_clr(data)                                 (0x00000002&((data)<<1))
#define CBUS_MSC_17_spi_fsm_clr(data)                                 (0x00000001&(data))
#define CBUS_MSC_17_get_que_fsm_clr(data)                             ((0x00000004&(data))>>2)
#define CBUS_MSC_17_get_sch_fsm_clr(data)                             ((0x00000002&(data))>>1)
#define CBUS_MSC_17_get_spi_fsm_clr(data)                             (0x00000001&(data))


#define CBUS_MSC_18                                                   0x1800f2c0
#define CBUS_MSC_18_reg_addr                                          "0xb800f2c0"
#define CBUS_MSC_18_reg                                               0xb800f2c0
#define CBUS_MSC_18_inst_addr                                         "0x00B0"
#define CBUS_MSC_18_inst                                              0x00B0
#define CBUS_MSC_18_que_fsm_shift                                     (8)
#define CBUS_MSC_18_sch_fsm_shift                                     (4)
#define CBUS_MSC_18_spi_fsm_shift                                     (0)
#define CBUS_MSC_18_que_fsm_mask                                      (0x00000F00)
#define CBUS_MSC_18_sch_fsm_mask                                      (0x000000F0)
#define CBUS_MSC_18_spi_fsm_mask                                      (0x0000000F)
#define CBUS_MSC_18_que_fsm(data)                                     (0x00000F00&((data)<<8))
#define CBUS_MSC_18_sch_fsm(data)                                     (0x000000F0&((data)<<4))
#define CBUS_MSC_18_spi_fsm(data)                                     (0x0000000F&(data))
#define CBUS_MSC_18_get_que_fsm(data)                                 ((0x00000F00&(data))>>8)
#define CBUS_MSC_18_get_sch_fsm(data)                                 ((0x000000F0&(data))>>4)
#define CBUS_MSC_18_get_spi_fsm(data)                                 (0x0000000F&(data))


#define CBUS_MSC_19                                                   0x1800f2c4
#define CBUS_MSC_19_reg_addr                                          "0xb800f2c4"
#define CBUS_MSC_19_reg                                               0xb800f2c4
#define CBUS_MSC_19_inst_addr                                         "0x00B1"
#define CBUS_MSC_19_inst                                              0x00B1
#define CBUS_MSC_19_cap_offset_shift                                  (0)
#define CBUS_MSC_19_cap_offset_mask                                   (0x000000FF)
#define CBUS_MSC_19_cap_offset(data)                                  (0x000000FF&(data))
#define CBUS_MSC_19_get_cap_offset(data)                              (0x000000FF&(data))


#define CBUS_MSC_1A                                                   0x1800f2c8
#define CBUS_MSC_1A_reg_addr                                          "0xb800f2c8"
#define CBUS_MSC_1A_reg                                               0xb800f2c8
#define CBUS_MSC_1A_inst_addr                                         "0x00B2"
#define CBUS_MSC_1A_inst                                              0x00B2
#define CBUS_MSC_1A_int_offset_shift                                  (0)
#define CBUS_MSC_1A_int_offset_mask                                   (0x000000FF)
#define CBUS_MSC_1A_int_offset(data)                                  (0x000000FF&(data))
#define CBUS_MSC_1A_get_int_offset(data)                              (0x000000FF&(data))


#define CBUS_MSC_1B                                                   0x1800f2cc
#define CBUS_MSC_1B_reg_addr                                          "0xb800f2cc"
#define CBUS_MSC_1B_reg                                               0xb800f2cc
#define CBUS_MSC_1B_inst_addr                                         "0x00B3"
#define CBUS_MSC_1B_inst                                              0x00B3
#define CBUS_MSC_1B_sta_offset_shift                                  (0)
#define CBUS_MSC_1B_sta_offset_mask                                   (0x000000FF)
#define CBUS_MSC_1B_sta_offset(data)                                  (0x000000FF&(data))
#define CBUS_MSC_1B_get_sta_offset(data)                              (0x000000FF&(data))


#define CBUS_MSC_1C                                                   0x1800f2d0
#define CBUS_MSC_1C_reg_addr                                          "0xb800f2d0"
#define CBUS_MSC_1C_reg                                               0xb800f2d0
#define CBUS_MSC_1C_inst_addr                                         "0x00B4"
#define CBUS_MSC_1C_inst                                              0x00B4
#define CBUS_MSC_1C_scr_offset_shift                                  (0)
#define CBUS_MSC_1C_scr_offset_mask                                   (0x000000FF)
#define CBUS_MSC_1C_scr_offset(data)                                  (0x000000FF&(data))
#define CBUS_MSC_1C_get_scr_offset(data)                              (0x000000FF&(data))


#define CBUS_MSC_1D                                                   0x1800f2d4
#define CBUS_MSC_1D_reg_addr                                          "0xb800f2d4"
#define CBUS_MSC_1D_reg                                               0xb800f2d4
#define CBUS_MSC_1D_inst_addr                                         "0x00B5"
#define CBUS_MSC_1D_inst                                              0x00B5
#define CBUS_MSC_1D_ddc_err_force_shift                               (1)
#define CBUS_MSC_1D_msc_err_force_shift                               (0)
#define CBUS_MSC_1D_ddc_err_force_mask                                (0x00000002)
#define CBUS_MSC_1D_msc_err_force_mask                                (0x00000001)
#define CBUS_MSC_1D_ddc_err_force(data)                               (0x00000002&((data)<<1))
#define CBUS_MSC_1D_msc_err_force(data)                               (0x00000001&(data))
#define CBUS_MSC_1D_get_ddc_err_force(data)                           ((0x00000002&(data))>>1)
#define CBUS_MSC_1D_get_msc_err_force(data)                           (0x00000001&(data))


#define CBUS_MSC_1E                                                   0x1800f2d8
#define CBUS_MSC_1E_reg_addr                                          "0xb800f2d8"
#define CBUS_MSC_1E_reg                                               0xb800f2d8
#define CBUS_MSC_1E_inst_addr                                         "0x00B6"
#define CBUS_MSC_1E_inst                                              0x00B6
#define CBUS_MSC_1E_ddc_err_fw_shift                                  (0)
#define CBUS_MSC_1E_ddc_err_fw_mask                                   (0x000000FF)
#define CBUS_MSC_1E_ddc_err_fw(data)                                  (0x000000FF&(data))
#define CBUS_MSC_1E_get_ddc_err_fw(data)                              (0x000000FF&(data))


#define CBUS_MSC_1F                                                   0x1800f2dc
#define CBUS_MSC_1F_reg_addr                                          "0xb800f2dc"
#define CBUS_MSC_1F_reg                                               0xb800f2dc
#define CBUS_MSC_1F_inst_addr                                         "0x00B7"
#define CBUS_MSC_1F_inst                                              0x00B7
#define CBUS_MSC_1F_msc_err_fw_shift                                  (0)
#define CBUS_MSC_1F_msc_err_fw_mask                                   (0x000000FF)
#define CBUS_MSC_1F_msc_err_fw(data)                                  (0x000000FF&(data))
#define CBUS_MSC_1F_get_msc_err_fw(data)                              (0x000000FF&(data))


#define CBUS_MSC_20                                                   0x1800f2e0
#define CBUS_MSC_20_reg_addr                                          "0xb800f2e0"
#define CBUS_MSC_20_reg                                               0xb800f2e0
#define CBUS_MSC_20_inst_addr                                         "0x00B8"
#define CBUS_MSC_20_inst                                              0x00B8
#define CBUS_MSC_20_ucp_rcv_shift                                     (0)
#define CBUS_MSC_20_ucp_rcv_mask                                      (0x000000FF)
#define CBUS_MSC_20_ucp_rcv(data)                                     (0x000000FF&(data))
#define CBUS_MSC_20_get_ucp_rcv(data)                                 (0x000000FF&(data))


#define CBUS_MSC_21                                                   0x1800f2e4
#define CBUS_MSC_21_reg_addr                                          "0xb800f2e4"
#define CBUS_MSC_21_reg                                               0xb800f2e4
#define CBUS_MSC_21_inst_addr                                         "0x00B9"
#define CBUS_MSC_21_inst                                              0x00B9
#define CBUS_MSC_21_ucpk_rcv_shift                                    (0)
#define CBUS_MSC_21_ucpk_rcv_mask                                     (0x000000FF)
#define CBUS_MSC_21_ucpk_rcv(data)                                    (0x000000FF&(data))
#define CBUS_MSC_21_get_ucpk_rcv(data)                                (0x000000FF&(data))


#define CBUS_MSC_22                                                   0x1800f2e8
#define CBUS_MSC_22_reg_addr                                          "0xb800f2e8"
#define CBUS_MSC_22_reg                                               0xb800f2e8
#define CBUS_MSC_22_inst_addr                                         "0x00BA"
#define CBUS_MSC_22_inst                                              0x00BA
#define CBUS_MSC_22_ucpe_rcv_shift                                    (0)
#define CBUS_MSC_22_ucpe_rcv_mask                                     (0x000000FF)
#define CBUS_MSC_22_ucpe_rcv(data)                                    (0x000000FF&(data))
#define CBUS_MSC_22_get_ucpe_rcv(data)                                (0x000000FF&(data))


#define FW0_REQ_00                                                    0x1800f300
#define FW0_REQ_00_reg_addr                                           "0xb800f300"
#define FW0_REQ_00_reg                                                0xb800f300
#define FW0_REQ_00_inst_addr                                          "0x00C0"
#define FW0_REQ_00_inst                                               0x00C0
#define FW0_REQ_00_fw0_req_shift                                      (8)
#define FW0_REQ_00_fw0_fifo_clr_shift                                 (7)
#define FW0_REQ_00_fw0_fifo_full_shift                                (6)
#define FW0_REQ_00_fw0_fifo_empty_shift                               (5)
#define FW0_REQ_00_fw0_tx_case_shift                                  (2)
#define FW0_REQ_00_fw0_head_shift                                     (0)
#define FW0_REQ_00_fw0_req_mask                                       (0x00000100)
#define FW0_REQ_00_fw0_fifo_clr_mask                                  (0x00000080)
#define FW0_REQ_00_fw0_fifo_full_mask                                 (0x00000040)
#define FW0_REQ_00_fw0_fifo_empty_mask                                (0x00000020)
#define FW0_REQ_00_fw0_tx_case_mask                                   (0x0000001C)
#define FW0_REQ_00_fw0_head_mask                                      (0x00000003)
#define FW0_REQ_00_fw0_req(data)                                      (0x00000100&((data)<<8))
#define FW0_REQ_00_fw0_fifo_clr(data)                                 (0x00000080&((data)<<7))
#define FW0_REQ_00_fw0_fifo_full(data)                                (0x00000040&((data)<<6))
#define FW0_REQ_00_fw0_fifo_empty(data)                               (0x00000020&((data)<<5))
#define FW0_REQ_00_fw0_tx_case(data)                                  (0x0000001C&((data)<<2))
#define FW0_REQ_00_fw0_head(data)                                     (0x00000003&(data))
#define FW0_REQ_00_get_fw0_req(data)                                  ((0x00000100&(data))>>8)
#define FW0_REQ_00_get_fw0_fifo_clr(data)                             ((0x00000080&(data))>>7)
#define FW0_REQ_00_get_fw0_fifo_full(data)                            ((0x00000040&(data))>>6)
#define FW0_REQ_00_get_fw0_fifo_empty(data)                           ((0x00000020&(data))>>5)
#define FW0_REQ_00_get_fw0_tx_case(data)                              ((0x0000001C&(data))>>2)
#define FW0_REQ_00_get_fw0_head(data)                                 (0x00000003&(data))


#define FW0_REQ_01                                                    0x1800f304
#define FW0_REQ_01_reg_addr                                           "0xb800f304"
#define FW0_REQ_01_reg                                                0xb800f304
#define FW0_REQ_01_inst_addr                                          "0x00C1"
#define FW0_REQ_01_inst                                               0x00C1
#define FW0_REQ_01_fw0_cmd1_shift                                     (0)
#define FW0_REQ_01_fw0_cmd1_mask                                      (0x000000FF)
#define FW0_REQ_01_fw0_cmd1(data)                                     (0x000000FF&(data))
#define FW0_REQ_01_get_fw0_cmd1(data)                                 (0x000000FF&(data))


#define FW0_REQ_02                                                    0x1800f308
#define FW0_REQ_02_reg_addr                                           "0xb800f308"
#define FW0_REQ_02_reg                                                0xb800f308
#define FW0_REQ_02_inst_addr                                          "0x00C2"
#define FW0_REQ_02_inst                                               0x00C2
#define FW0_REQ_02_fw0_cmd2_shift                                     (0)
#define FW0_REQ_02_fw0_cmd2_mask                                      (0x000000FF)
#define FW0_REQ_02_fw0_cmd2(data)                                     (0x000000FF&(data))
#define FW0_REQ_02_get_fw0_cmd2(data)                                 (0x000000FF&(data))


#define FW0_REQ_03                                                    0x1800f30c
#define FW0_REQ_03_reg_addr                                           "0xb800f30c"
#define FW0_REQ_03_reg                                                0xb800f30c
#define FW0_REQ_03_inst_addr                                          "0x00C3"
#define FW0_REQ_03_inst                                               0x00C3
#define FW0_REQ_03_fw0_offset_shift                                   (0)
#define FW0_REQ_03_fw0_offset_mask                                    (0x000000FF)
#define FW0_REQ_03_fw0_offset(data)                                   (0x000000FF&(data))
#define FW0_REQ_03_get_fw0_offset(data)                               (0x000000FF&(data))


#define FW0_REQ_04                                                    0x1800f310
#define FW0_REQ_04_reg_addr                                           "0xb800f310"
#define FW0_REQ_04_reg                                                0xb800f310
#define FW0_REQ_04_inst_addr                                          "0x00C4"
#define FW0_REQ_04_inst                                               0x00C4
#define FW0_REQ_04_fw0_data_shift                                     (0)
#define FW0_REQ_04_fw0_data_mask                                      (0x000000FF)
#define FW0_REQ_04_fw0_data(data)                                     (0x000000FF&(data))
#define FW0_REQ_04_get_fw0_data(data)                                 (0x000000FF&(data))


#define FW0_REQ_05                                                    0x1800f314
#define FW0_REQ_05_reg_addr                                           "0xb800f314"
#define FW0_REQ_05_reg                                                0xb800f314
#define FW0_REQ_05_inst_addr                                          "0x00C5"
#define FW0_REQ_05_inst                                               0x00C5
#define FW0_REQ_05_fw0_rty_ovr_shift                                  (9)
#define FW0_REQ_05_fw0_fin_shift                                      (8)
#define FW0_REQ_05_fw0_cmd_event_shift                                (7)
#define FW0_REQ_05_fw0_data_event_shift                               (6)
#define FW0_REQ_05_fw0_rcv_err_shift                                  (5)
#define FW0_REQ_05_fw0_fin_irq_en_shift                               (4)
#define FW0_REQ_05_fw0_cmd_irq_en_shift                               (3)
#define FW0_REQ_05_fw0_data_irq_en_shift                              (2)
#define FW0_REQ_05_fw0_wait_case_shift                                (0)
#define FW0_REQ_05_fw0_rty_ovr_mask                                   (0x00000200)
#define FW0_REQ_05_fw0_fin_mask                                       (0x00000100)
#define FW0_REQ_05_fw0_cmd_event_mask                                 (0x00000080)
#define FW0_REQ_05_fw0_data_event_mask                                (0x00000040)
#define FW0_REQ_05_fw0_rcv_err_mask                                   (0x00000020)
#define FW0_REQ_05_fw0_fin_irq_en_mask                                (0x00000010)
#define FW0_REQ_05_fw0_cmd_irq_en_mask                                (0x00000008)
#define FW0_REQ_05_fw0_data_irq_en_mask                               (0x00000004)
#define FW0_REQ_05_fw0_wait_case_mask                                 (0x00000003)
#define FW0_REQ_05_fw0_rty_ovr(data)                                  (0x00000200&((data)<<9))
#define FW0_REQ_05_fw0_fin(data)                                      (0x00000100&((data)<<8))
#define FW0_REQ_05_fw0_cmd_event(data)                                (0x00000080&((data)<<7))
#define FW0_REQ_05_fw0_data_event(data)                               (0x00000040&((data)<<6))
#define FW0_REQ_05_fw0_rcv_err(data)                                  (0x00000020&((data)<<5))
#define FW0_REQ_05_fw0_fin_irq_en(data)                               (0x00000010&((data)<<4))
#define FW0_REQ_05_fw0_cmd_irq_en(data)                               (0x00000008&((data)<<3))
#define FW0_REQ_05_fw0_data_irq_en(data)                              (0x00000004&((data)<<2))
#define FW0_REQ_05_fw0_wait_case(data)                                (0x00000003&(data))
#define FW0_REQ_05_get_fw0_rty_ovr(data)                              ((0x00000200&(data))>>9)
#define FW0_REQ_05_get_fw0_fin(data)                                  ((0x00000100&(data))>>8)
#define FW0_REQ_05_get_fw0_cmd_event(data)                            ((0x00000080&(data))>>7)
#define FW0_REQ_05_get_fw0_data_event(data)                           ((0x00000040&(data))>>6)
#define FW0_REQ_05_get_fw0_rcv_err(data)                              ((0x00000020&(data))>>5)
#define FW0_REQ_05_get_fw0_fin_irq_en(data)                           ((0x00000010&(data))>>4)
#define FW0_REQ_05_get_fw0_cmd_irq_en(data)                           ((0x00000008&(data))>>3)
#define FW0_REQ_05_get_fw0_data_irq_en(data)                          ((0x00000004&(data))>>2)
#define FW0_REQ_05_get_fw0_wait_case(data)                            (0x00000003&(data))


#define FW0_REQ_06                                                    0x1800f318
#define FW0_REQ_06_reg_addr                                           "0xb800f318"
#define FW0_REQ_06_reg                                                0xb800f318
#define FW0_REQ_06_inst_addr                                          "0x00C6"
#define FW0_REQ_06_inst                                               0x00C6
#define FW0_REQ_06_fw0_cmd_rcv_shift                                  (0)
#define FW0_REQ_06_fw0_cmd_rcv_mask                                   (0x000000FF)
#define FW0_REQ_06_fw0_cmd_rcv(data)                                  (0x000000FF&(data))
#define FW0_REQ_06_get_fw0_cmd_rcv(data)                              (0x000000FF&(data))


#define FW0_REQ_07                                                    0x1800f31c
#define FW0_REQ_07_reg_addr                                           "0xb800f31c"
#define FW0_REQ_07_reg                                                0xb800f31c
#define FW0_REQ_07_inst_addr                                          "0x00C7"
#define FW0_REQ_07_inst                                               0x00C7
#define FW0_REQ_07_fw0_data_rcv_shift                                 (0)
#define FW0_REQ_07_fw0_data_rcv_mask                                  (0x000000FF)
#define FW0_REQ_07_fw0_data_rcv(data)                                 (0x000000FF&(data))
#define FW0_REQ_07_get_fw0_data_rcv(data)                             (0x000000FF&(data))


#define FW0_REQ_08                                                    0x1800f320
#define FW0_REQ_08_reg_addr                                           "0xb800f320"
#define FW0_REQ_08_reg                                                0xb800f320
#define FW0_REQ_08_inst_addr                                          "0x00C8"
#define FW0_REQ_08_inst                                               0x00C8
#define FW0_REQ_08_fw0_rd_en_shift                                    (13)
#define FW0_REQ_08_fw0_fifo_len_shift                                 (8)
#define FW0_REQ_08_fw0_rdata_shift                                    (0)
#define FW0_REQ_08_fw0_rd_en_mask                                     (0x00002000)
#define FW0_REQ_08_fw0_fifo_len_mask                                  (0x00001F00)
#define FW0_REQ_08_fw0_rdata_mask                                     (0x000000FF)
#define FW0_REQ_08_fw0_rd_en(data)                                    (0x00002000&((data)<<13))
#define FW0_REQ_08_fw0_fifo_len(data)                                 (0x00001F00&((data)<<8))
#define FW0_REQ_08_fw0_rdata(data)                                    (0x000000FF&(data))
#define FW0_REQ_08_get_fw0_rd_en(data)                                ((0x00002000&(data))>>13)
#define FW0_REQ_08_get_fw0_fifo_len(data)                             ((0x00001F00&(data))>>8)
#define FW0_REQ_08_get_fw0_rdata(data)                                (0x000000FF&(data))


#define FW1_REQ_00                                                    0x1800f340
#define FW1_REQ_00_reg_addr                                           "0xb800f340"
#define FW1_REQ_00_reg                                                0xb800f340
#define FW1_REQ_00_inst_addr                                          "0x00D0"
#define FW1_REQ_00_inst                                               0x00D0
#define FW1_REQ_00_fw1_req_shift                                      (8)
#define FW1_REQ_00_fw1_fifo_clr_shift                                 (7)
#define FW1_REQ_00_fw1_fifo_full_shift                                (6)
#define FW1_REQ_00_fw1_fifo_empty_shift                               (5)
#define FW1_REQ_00_fw1_tx_case_shift                                  (2)
#define FW1_REQ_00_fw1_head_shift                                     (0)
#define FW1_REQ_00_fw1_req_mask                                       (0x00000100)
#define FW1_REQ_00_fw1_fifo_clr_mask                                  (0x00000080)
#define FW1_REQ_00_fw1_fifo_full_mask                                 (0x00000040)
#define FW1_REQ_00_fw1_fifo_empty_mask                                (0x00000020)
#define FW1_REQ_00_fw1_tx_case_mask                                   (0x0000001C)
#define FW1_REQ_00_fw1_head_mask                                      (0x00000003)
#define FW1_REQ_00_fw1_req(data)                                      (0x00000100&((data)<<8))
#define FW1_REQ_00_fw1_fifo_clr(data)                                 (0x00000080&((data)<<7))
#define FW1_REQ_00_fw1_fifo_full(data)                                (0x00000040&((data)<<6))
#define FW1_REQ_00_fw1_fifo_empty(data)                               (0x00000020&((data)<<5))
#define FW1_REQ_00_fw1_tx_case(data)                                  (0x0000001C&((data)<<2))
#define FW1_REQ_00_fw1_head(data)                                     (0x00000003&(data))
#define FW1_REQ_00_get_fw1_req(data)                                  ((0x00000100&(data))>>8)
#define FW1_REQ_00_get_fw1_fifo_clr(data)                             ((0x00000080&(data))>>7)
#define FW1_REQ_00_get_fw1_fifo_full(data)                            ((0x00000040&(data))>>6)
#define FW1_REQ_00_get_fw1_fifo_empty(data)                           ((0x00000020&(data))>>5)
#define FW1_REQ_00_get_fw1_tx_case(data)                              ((0x0000001C&(data))>>2)
#define FW1_REQ_00_get_fw1_head(data)                                 (0x00000003&(data))


#define FW1_REQ_01                                                    0x1800f344
#define FW1_REQ_01_reg_addr                                           "0xb800f344"
#define FW1_REQ_01_reg                                                0xb800f344
#define FW1_REQ_01_inst_addr                                          "0x00D1"
#define FW1_REQ_01_inst                                               0x00D1
#define FW1_REQ_01_fw1_cmd1_shift                                     (0)
#define FW1_REQ_01_fw1_cmd1_mask                                      (0x000000FF)
#define FW1_REQ_01_fw1_cmd1(data)                                     (0x000000FF&(data))
#define FW1_REQ_01_get_fw1_cmd1(data)                                 (0x000000FF&(data))


#define FW1_REQ_02                                                    0x1800f348
#define FW1_REQ_02_reg_addr                                           "0xb800f348"
#define FW1_REQ_02_reg                                                0xb800f348
#define FW1_REQ_02_inst_addr                                          "0x00D2"
#define FW1_REQ_02_inst                                               0x00D2
#define FW1_REQ_02_fw1_cmd2_shift                                     (0)
#define FW1_REQ_02_fw1_cmd2_mask                                      (0x000000FF)
#define FW1_REQ_02_fw1_cmd2(data)                                     (0x000000FF&(data))
#define FW1_REQ_02_get_fw1_cmd2(data)                                 (0x000000FF&(data))


#define FW1_REQ_03                                                    0x1800f34c
#define FW1_REQ_03_reg_addr                                           "0xb800f34c"
#define FW1_REQ_03_reg                                                0xb800f34c
#define FW1_REQ_03_inst_addr                                          "0x00D3"
#define FW1_REQ_03_inst                                               0x00D3
#define FW1_REQ_03_fw1_offset_shift                                   (0)
#define FW1_REQ_03_fw1_offset_mask                                    (0x000000FF)
#define FW1_REQ_03_fw1_offset(data)                                   (0x000000FF&(data))
#define FW1_REQ_03_get_fw1_offset(data)                               (0x000000FF&(data))


#define FW1_REQ_04                                                    0x1800f350
#define FW1_REQ_04_reg_addr                                           "0xb800f350"
#define FW1_REQ_04_reg                                                0xb800f350
#define FW1_REQ_04_inst_addr                                          "0x00D4"
#define FW1_REQ_04_inst                                               0x00D4
#define FW1_REQ_04_fw1_data_shift                                     (0)
#define FW1_REQ_04_fw1_data_mask                                      (0x000000FF)
#define FW1_REQ_04_fw1_data(data)                                     (0x000000FF&(data))
#define FW1_REQ_04_get_fw1_data(data)                                 (0x000000FF&(data))


#define FW1_REQ_05                                                    0x1800f354
#define FW1_REQ_05_reg_addr                                           "0xb800f354"
#define FW1_REQ_05_reg                                                0xb800f354
#define FW1_REQ_05_inst_addr                                          "0x00D5"
#define FW1_REQ_05_inst                                               0x00D5
#define FW1_REQ_05_fw1_rty_ovr_shift                                  (9)
#define FW1_REQ_05_fw1_fin_shift                                      (8)
#define FW1_REQ_05_fw1_cmd_event_shift                                (7)
#define FW1_REQ_05_fw1_data_event_shift                               (6)
#define FW1_REQ_05_fw1_rcv_err_shift                                  (5)
#define FW1_REQ_05_fw1_fin_irq_en_shift                               (4)
#define FW1_REQ_05_fw1_cmd_irq_en_shift                               (3)
#define FW1_REQ_05_fw1_data_irq_en_shift                              (2)
#define FW1_REQ_05_fw1_wait_case_shift                                (0)
#define FW1_REQ_05_fw1_rty_ovr_mask                                   (0x00000200)
#define FW1_REQ_05_fw1_fin_mask                                       (0x00000100)
#define FW1_REQ_05_fw1_cmd_event_mask                                 (0x00000080)
#define FW1_REQ_05_fw1_data_event_mask                                (0x00000040)
#define FW1_REQ_05_fw1_rcv_err_mask                                   (0x00000020)
#define FW1_REQ_05_fw1_fin_irq_en_mask                                (0x00000010)
#define FW1_REQ_05_fw1_cmd_irq_en_mask                                (0x00000008)
#define FW1_REQ_05_fw1_data_irq_en_mask                               (0x00000004)
#define FW1_REQ_05_fw1_wait_case_mask                                 (0x00000003)
#define FW1_REQ_05_fw1_rty_ovr(data)                                  (0x00000200&((data)<<9))
#define FW1_REQ_05_fw1_fin(data)                                      (0x00000100&((data)<<8))
#define FW1_REQ_05_fw1_cmd_event(data)                                (0x00000080&((data)<<7))
#define FW1_REQ_05_fw1_data_event(data)                               (0x00000040&((data)<<6))
#define FW1_REQ_05_fw1_rcv_err(data)                                  (0x00000020&((data)<<5))
#define FW1_REQ_05_fw1_fin_irq_en(data)                               (0x00000010&((data)<<4))
#define FW1_REQ_05_fw1_cmd_irq_en(data)                               (0x00000008&((data)<<3))
#define FW1_REQ_05_fw1_data_irq_en(data)                              (0x00000004&((data)<<2))
#define FW1_REQ_05_fw1_wait_case(data)                                (0x00000003&(data))
#define FW1_REQ_05_get_fw1_rty_ovr(data)                              ((0x00000200&(data))>>9)
#define FW1_REQ_05_get_fw1_fin(data)                                  ((0x00000100&(data))>>8)
#define FW1_REQ_05_get_fw1_cmd_event(data)                            ((0x00000080&(data))>>7)
#define FW1_REQ_05_get_fw1_data_event(data)                           ((0x00000040&(data))>>6)
#define FW1_REQ_05_get_fw1_rcv_err(data)                              ((0x00000020&(data))>>5)
#define FW1_REQ_05_get_fw1_fin_irq_en(data)                           ((0x00000010&(data))>>4)
#define FW1_REQ_05_get_fw1_cmd_irq_en(data)                           ((0x00000008&(data))>>3)
#define FW1_REQ_05_get_fw1_data_irq_en(data)                          ((0x00000004&(data))>>2)
#define FW1_REQ_05_get_fw1_wait_case(data)                            (0x00000003&(data))


#define FW1_REQ_06                                                    0x1800f358
#define FW1_REQ_06_reg_addr                                           "0xb800f358"
#define FW1_REQ_06_reg                                                0xb800f358
#define FW1_REQ_06_inst_addr                                          "0x00D6"
#define FW1_REQ_06_inst                                               0x00D6
#define FW1_REQ_06_fw1_cmd_rcv_shift                                  (0)
#define FW1_REQ_06_fw1_cmd_rcv_mask                                   (0x000000FF)
#define FW1_REQ_06_fw1_cmd_rcv(data)                                  (0x000000FF&(data))
#define FW1_REQ_06_get_fw1_cmd_rcv(data)                              (0x000000FF&(data))


#define FW1_REQ_07                                                    0x1800f35c
#define FW1_REQ_07_reg_addr                                           "0xb800f35c"
#define FW1_REQ_07_reg                                                0xb800f35c
#define FW1_REQ_07_inst_addr                                          "0x00D7"
#define FW1_REQ_07_inst                                               0x00D7
#define FW1_REQ_07_fw1_data_rcv_shift                                 (0)
#define FW1_REQ_07_fw1_data_rcv_mask                                  (0x000000FF)
#define FW1_REQ_07_fw1_data_rcv(data)                                 (0x000000FF&(data))
#define FW1_REQ_07_get_fw1_data_rcv(data)                             (0x000000FF&(data))


#define FW1_REQ_08                                                    0x1800f360
#define FW1_REQ_08_reg_addr                                           "0xb800f360"
#define FW1_REQ_08_reg                                                0xb800f360
#define FW1_REQ_08_inst_addr                                          "0x00D8"
#define FW1_REQ_08_inst                                               0x00D8
#define FW1_REQ_08_fw1_rd_en_shift                                    (13)
#define FW1_REQ_08_fw1_fifo_len_shift                                 (8)
#define FW1_REQ_08_fw1_rdata_shift                                    (0)
#define FW1_REQ_08_fw1_rd_en_mask                                     (0x00002000)
#define FW1_REQ_08_fw1_fifo_len_mask                                  (0x00001F00)
#define FW1_REQ_08_fw1_rdata_mask                                     (0x000000FF)
#define FW1_REQ_08_fw1_rd_en(data)                                    (0x00002000&((data)<<13))
#define FW1_REQ_08_fw1_fifo_len(data)                                 (0x00001F00&((data)<<8))
#define FW1_REQ_08_fw1_rdata(data)                                    (0x000000FF&(data))
#define FW1_REQ_08_get_fw1_rd_en(data)                                ((0x00002000&(data))>>13)
#define FW1_REQ_08_get_fw1_fifo_len(data)                             ((0x00001F00&(data))>>8)
#define FW1_REQ_08_get_fw1_rdata(data)                                (0x000000FF&(data))


#define FW2_REQ_00                                                    0x1800f380
#define FW2_REQ_00_reg_addr                                           "0xb800f380"
#define FW2_REQ_00_reg                                                0xb800f380
#define FW2_REQ_00_inst_addr                                          "0x00E0"
#define FW2_REQ_00_inst                                               0x00E0
#define FW2_REQ_00_fw2_req_shift                                      (8)
#define FW2_REQ_00_fw2_fifo_clr_shift                                 (7)
#define FW2_REQ_00_fw2_fifo_full_shift                                (6)
#define FW2_REQ_00_fw2_fifo_empty_shift                               (5)
#define FW2_REQ_00_fw2_tx_case_shift                                  (2)
#define FW2_REQ_00_fw2_head_shift                                     (0)
#define FW2_REQ_00_fw2_req_mask                                       (0x00000100)
#define FW2_REQ_00_fw2_fifo_clr_mask                                  (0x00000080)
#define FW2_REQ_00_fw2_fifo_full_mask                                 (0x00000040)
#define FW2_REQ_00_fw2_fifo_empty_mask                                (0x00000020)
#define FW2_REQ_00_fw2_tx_case_mask                                   (0x0000001C)
#define FW2_REQ_00_fw2_head_mask                                      (0x00000003)
#define FW2_REQ_00_fw2_req(data)                                      (0x00000100&((data)<<8))
#define FW2_REQ_00_fw2_fifo_clr(data)                                 (0x00000080&((data)<<7))
#define FW2_REQ_00_fw2_fifo_full(data)                                (0x00000040&((data)<<6))
#define FW2_REQ_00_fw2_fifo_empty(data)                               (0x00000020&((data)<<5))
#define FW2_REQ_00_fw2_tx_case(data)                                  (0x0000001C&((data)<<2))
#define FW2_REQ_00_fw2_head(data)                                     (0x00000003&(data))
#define FW2_REQ_00_get_fw2_req(data)                                  ((0x00000100&(data))>>8)
#define FW2_REQ_00_get_fw2_fifo_clr(data)                             ((0x00000080&(data))>>7)
#define FW2_REQ_00_get_fw2_fifo_full(data)                            ((0x00000040&(data))>>6)
#define FW2_REQ_00_get_fw2_fifo_empty(data)                           ((0x00000020&(data))>>5)
#define FW2_REQ_00_get_fw2_tx_case(data)                              ((0x0000001C&(data))>>2)
#define FW2_REQ_00_get_fw2_head(data)                                 (0x00000003&(data))


#define FW2_REQ_01                                                    0x1800f384
#define FW2_REQ_01_reg_addr                                           "0xb800f384"
#define FW2_REQ_01_reg                                                0xb800f384
#define FW2_REQ_01_inst_addr                                          "0x00E1"
#define FW2_REQ_01_inst                                               0x00E1
#define FW2_REQ_01_fw2_cmd1_shift                                     (0)
#define FW2_REQ_01_fw2_cmd1_mask                                      (0x000000FF)
#define FW2_REQ_01_fw2_cmd1(data)                                     (0x000000FF&(data))
#define FW2_REQ_01_get_fw2_cmd1(data)                                 (0x000000FF&(data))


#define FW2_REQ_02                                                    0x1800f388
#define FW2_REQ_02_reg_addr                                           "0xb800f388"
#define FW2_REQ_02_reg                                                0xb800f388
#define FW2_REQ_02_inst_addr                                          "0x00E2"
#define FW2_REQ_02_inst                                               0x00E2
#define FW2_REQ_02_fw2_cmd2_shift                                     (0)
#define FW2_REQ_02_fw2_cmd2_mask                                      (0x000000FF)
#define FW2_REQ_02_fw2_cmd2(data)                                     (0x000000FF&(data))
#define FW2_REQ_02_get_fw2_cmd2(data)                                 (0x000000FF&(data))


#define FW2_REQ_03                                                    0x1800f38c
#define FW2_REQ_03_reg_addr                                           "0xb800f38c"
#define FW2_REQ_03_reg                                                0xb800f38c
#define FW2_REQ_03_inst_addr                                          "0x00E3"
#define FW2_REQ_03_inst                                               0x00E3
#define FW2_REQ_03_fw2_offset_shift                                   (0)
#define FW2_REQ_03_fw2_offset_mask                                    (0x000000FF)
#define FW2_REQ_03_fw2_offset(data)                                   (0x000000FF&(data))
#define FW2_REQ_03_get_fw2_offset(data)                               (0x000000FF&(data))


#define FW2_REQ_04                                                    0x1800f390
#define FW2_REQ_04_reg_addr                                           "0xb800f390"
#define FW2_REQ_04_reg                                                0xb800f390
#define FW2_REQ_04_inst_addr                                          "0x00E4"
#define FW2_REQ_04_inst                                               0x00E4
#define FW2_REQ_04_fw2_data_shift                                     (0)
#define FW2_REQ_04_fw2_data_mask                                      (0x000000FF)
#define FW2_REQ_04_fw2_data(data)                                     (0x000000FF&(data))
#define FW2_REQ_04_get_fw2_data(data)                                 (0x000000FF&(data))


#define FW2_REQ_05                                                    0x1800f394
#define FW2_REQ_05_reg_addr                                           "0xb800f394"
#define FW2_REQ_05_reg                                                0xb800f394
#define FW2_REQ_05_inst_addr                                          "0x00E5"
#define FW2_REQ_05_inst                                               0x00E5
#define FW2_REQ_05_fw2_rty_ovr_shift                                  (9)
#define FW2_REQ_05_fw2_fin_shift                                      (8)
#define FW2_REQ_05_fw2_cmd_event_shift                                (7)
#define FW2_REQ_05_fw2_data_event_shift                               (6)
#define FW2_REQ_05_fw2_rcv_err_shift                                  (5)
#define FW2_REQ_05_fw2_fin_irq_en_shift                               (4)
#define FW2_REQ_05_fw2_cmd_irq_en_shift                               (3)
#define FW2_REQ_05_fw2_data_irq_en_shift                              (2)
#define FW2_REQ_05_fw2_wait_case_shift                                (0)
#define FW2_REQ_05_fw2_rty_ovr_mask                                   (0x00000200)
#define FW2_REQ_05_fw2_fin_mask                                       (0x00000100)
#define FW2_REQ_05_fw2_cmd_event_mask                                 (0x00000080)
#define FW2_REQ_05_fw2_data_event_mask                                (0x00000040)
#define FW2_REQ_05_fw2_rcv_err_mask                                   (0x00000020)
#define FW2_REQ_05_fw2_fin_irq_en_mask                                (0x00000010)
#define FW2_REQ_05_fw2_cmd_irq_en_mask                                (0x00000008)
#define FW2_REQ_05_fw2_data_irq_en_mask                               (0x00000004)
#define FW2_REQ_05_fw2_wait_case_mask                                 (0x00000003)
#define FW2_REQ_05_fw2_rty_ovr(data)                                  (0x00000200&((data)<<9))
#define FW2_REQ_05_fw2_fin(data)                                      (0x00000100&((data)<<8))
#define FW2_REQ_05_fw2_cmd_event(data)                                (0x00000080&((data)<<7))
#define FW2_REQ_05_fw2_data_event(data)                               (0x00000040&((data)<<6))
#define FW2_REQ_05_fw2_rcv_err(data)                                  (0x00000020&((data)<<5))
#define FW2_REQ_05_fw2_fin_irq_en(data)                               (0x00000010&((data)<<4))
#define FW2_REQ_05_fw2_cmd_irq_en(data)                               (0x00000008&((data)<<3))
#define FW2_REQ_05_fw2_data_irq_en(data)                              (0x00000004&((data)<<2))
#define FW2_REQ_05_fw2_wait_case(data)                                (0x00000003&(data))
#define FW2_REQ_05_get_fw2_rty_ovr(data)                              ((0x00000200&(data))>>9)
#define FW2_REQ_05_get_fw2_fin(data)                                  ((0x00000100&(data))>>8)
#define FW2_REQ_05_get_fw2_cmd_event(data)                            ((0x00000080&(data))>>7)
#define FW2_REQ_05_get_fw2_data_event(data)                           ((0x00000040&(data))>>6)
#define FW2_REQ_05_get_fw2_rcv_err(data)                              ((0x00000020&(data))>>5)
#define FW2_REQ_05_get_fw2_fin_irq_en(data)                           ((0x00000010&(data))>>4)
#define FW2_REQ_05_get_fw2_cmd_irq_en(data)                           ((0x00000008&(data))>>3)
#define FW2_REQ_05_get_fw2_data_irq_en(data)                          ((0x00000004&(data))>>2)
#define FW2_REQ_05_get_fw2_wait_case(data)                            (0x00000003&(data))


#define FW2_REQ_06                                                    0x1800f398
#define FW2_REQ_06_reg_addr                                           "0xb800f398"
#define FW2_REQ_06_reg                                                0xb800f398
#define FW2_REQ_06_inst_addr                                          "0x00E6"
#define FW2_REQ_06_inst                                               0x00E6
#define FW2_REQ_06_fw2_cmd_rcv_shift                                  (0)
#define FW2_REQ_06_fw2_cmd_rcv_mask                                   (0x000000FF)
#define FW2_REQ_06_fw2_cmd_rcv(data)                                  (0x000000FF&(data))
#define FW2_REQ_06_get_fw2_cmd_rcv(data)                              (0x000000FF&(data))


#define FW2_REQ_07                                                    0x1800f39c
#define FW2_REQ_07_reg_addr                                           "0xb800f39c"
#define FW2_REQ_07_reg                                                0xb800f39c
#define FW2_REQ_07_inst_addr                                          "0x00E7"
#define FW2_REQ_07_inst                                               0x00E7
#define FW2_REQ_07_fw2_data_rcv_shift                                 (0)
#define FW2_REQ_07_fw2_data_rcv_mask                                  (0x000000FF)
#define FW2_REQ_07_fw2_data_rcv(data)                                 (0x000000FF&(data))
#define FW2_REQ_07_get_fw2_data_rcv(data)                             (0x000000FF&(data))


#define FW2_REQ_08                                                    0x1800f3a0
#define FW2_REQ_08_reg_addr                                           "0xb800f3a0"
#define FW2_REQ_08_reg                                                0xb800f3a0
#define FW2_REQ_08_inst_addr                                          "0x00E8"
#define FW2_REQ_08_inst                                               0x00E8
#define FW2_REQ_08_fw2_rd_en_shift                                    (13)
#define FW2_REQ_08_fw2_fifo_len_shift                                 (8)
#define FW2_REQ_08_fw2_rdata_shift                                    (0)
#define FW2_REQ_08_fw2_rd_en_mask                                     (0x00002000)
#define FW2_REQ_08_fw2_fifo_len_mask                                  (0x00001F00)
#define FW2_REQ_08_fw2_rdata_mask                                     (0x000000FF)
#define FW2_REQ_08_fw2_rd_en(data)                                    (0x00002000&((data)<<13))
#define FW2_REQ_08_fw2_fifo_len(data)                                 (0x00001F00&((data)<<8))
#define FW2_REQ_08_fw2_rdata(data)                                    (0x000000FF&(data))
#define FW2_REQ_08_get_fw2_rd_en(data)                                ((0x00002000&(data))>>13)
#define FW2_REQ_08_get_fw2_fifo_len(data)                             ((0x00001F00&(data))>>8)
#define FW2_REQ_08_get_fw2_rdata(data)                                (0x000000FF&(data))


#define CBUS_DDC_00                                                   0x1800f3c0
#define CBUS_DDC_00_reg_addr                                          "0xb800f3c0"
#define CBUS_DDC_00_reg                                               0xb800f3c0
#define CBUS_DDC_00_inst_addr                                         "0x00F0"
#define CBUS_DDC_00_inst                                              0x00F0
#define CBUS_DDC_00_ddc_err_code_shift                                (0)
#define CBUS_DDC_00_ddc_err_code_mask                                 (0x000000FF)
#define CBUS_DDC_00_ddc_err_code(data)                                (0x000000FF&(data))
#define CBUS_DDC_00_get_ddc_err_code(data)                            (0x000000FF&(data))


#define CBUS_DDC_01                                                   0x1800f3c4
#define CBUS_DDC_01_reg_addr                                          "0xb800f3c4"
#define CBUS_DDC_01_reg                                               0xb800f3c4
#define CBUS_DDC_01_inst_addr                                         "0x00F1"
#define CBUS_DDC_01_inst                                              0x00F1
#define CBUS_DDC_01_iic_ck_tgt_shift                                  (0)
#define CBUS_DDC_01_iic_ck_tgt_mask                                   (0x000000FF)
#define CBUS_DDC_01_iic_ck_tgt(data)                                  (0x000000FF&(data))
#define CBUS_DDC_01_get_iic_ck_tgt(data)                              (0x000000FF&(data))


#define CBUS_DDC_02                                                   0x1800f3c8
#define CBUS_DDC_02_reg_addr                                          "0xb800f3c8"
#define CBUS_DDC_02_reg                                               0xb800f3c8
#define CBUS_DDC_02_inst_addr                                         "0x00F2"
#define CBUS_DDC_02_inst                                              0x00F2
#define CBUS_DDC_02_mcuddc_en_shift                                   (7)
#define CBUS_DDC_02_ddc_prior_dis_shift                               (6)
#define CBUS_DDC_02_ddc_cmd_event_shift                               (5)
#define CBUS_DDC_02_ddc_data_event_shift                              (4)
#define CBUS_DDC_02_ddc_cmd_irq_en_shift                              (3)
#define CBUS_DDC_02_ddc_data_irq_en_shift                             (2)
#define CBUS_DDC_02_ddc_req_ctrl_shift                                (1)
#define CBUS_DDC_02_ddc_req_shift                                     (0)
#define CBUS_DDC_02_mcuddc_en_mask                                    (0x00000080)
#define CBUS_DDC_02_ddc_prior_dis_mask                                (0x00000040)
#define CBUS_DDC_02_ddc_cmd_event_mask                                (0x00000020)
#define CBUS_DDC_02_ddc_data_event_mask                               (0x00000010)
#define CBUS_DDC_02_ddc_cmd_irq_en_mask                               (0x00000008)
#define CBUS_DDC_02_ddc_data_irq_en_mask                              (0x00000004)
#define CBUS_DDC_02_ddc_req_ctrl_mask                                 (0x00000002)
#define CBUS_DDC_02_ddc_req_mask                                      (0x00000001)
#define CBUS_DDC_02_mcuddc_en(data)                                   (0x00000080&((data)<<7))
#define CBUS_DDC_02_ddc_prior_dis(data)                               (0x00000040&((data)<<6))
#define CBUS_DDC_02_ddc_cmd_event(data)                               (0x00000020&((data)<<5))
#define CBUS_DDC_02_ddc_data_event(data)                              (0x00000010&((data)<<4))
#define CBUS_DDC_02_ddc_cmd_irq_en(data)                              (0x00000008&((data)<<3))
#define CBUS_DDC_02_ddc_data_irq_en(data)                             (0x00000004&((data)<<2))
#define CBUS_DDC_02_ddc_req_ctrl(data)                                (0x00000002&((data)<<1))
#define CBUS_DDC_02_ddc_req(data)                                     (0x00000001&(data))
#define CBUS_DDC_02_get_mcuddc_en(data)                               ((0x00000080&(data))>>7)
#define CBUS_DDC_02_get_ddc_prior_dis(data)                           ((0x00000040&(data))>>6)
#define CBUS_DDC_02_get_ddc_cmd_event(data)                           ((0x00000020&(data))>>5)
#define CBUS_DDC_02_get_ddc_data_event(data)                          ((0x00000010&(data))>>4)
#define CBUS_DDC_02_get_ddc_cmd_irq_en(data)                          ((0x00000008&(data))>>3)
#define CBUS_DDC_02_get_ddc_data_irq_en(data)                         ((0x00000004&(data))>>2)
#define CBUS_DDC_02_get_ddc_req_ctrl(data)                            ((0x00000002&(data))>>1)
#define CBUS_DDC_02_get_ddc_req(data)                                 (0x00000001&(data))


#define CBUS_DDC_03                                                   0x1800f3cc
#define CBUS_DDC_03_reg_addr                                          "0xb800f3cc"
#define CBUS_DDC_03_reg                                               0xb800f3cc
#define CBUS_DDC_03_inst_addr                                         "0x00F3"
#define CBUS_DDC_03_inst                                              0x00F3
#define CBUS_DDC_03_ddc_rcv_cmd_shift                                 (0)
#define CBUS_DDC_03_ddc_rcv_cmd_mask                                  (0x000000FF)
#define CBUS_DDC_03_ddc_rcv_cmd(data)                                 (0x000000FF&(data))
#define CBUS_DDC_03_get_ddc_rcv_cmd(data)                             (0x000000FF&(data))


#define CBUS_DDC_04                                                   0x1800f3d0
#define CBUS_DDC_04_reg_addr                                          "0xb800f3d0"
#define CBUS_DDC_04_reg                                               0xb800f3d0
#define CBUS_DDC_04_inst_addr                                         "0x00F4"
#define CBUS_DDC_04_inst                                              0x00F4
#define CBUS_DDC_04_ddc_rcv_data_shift                                (0)
#define CBUS_DDC_04_ddc_rcv_data_mask                                 (0x000000FF)
#define CBUS_DDC_04_ddc_rcv_data(data)                                (0x000000FF&(data))
#define CBUS_DDC_04_get_ddc_rcv_data(data)                            (0x000000FF&(data))


#define CBUS_DDC_05                                                   0x1800f3d4
#define CBUS_DDC_05_reg_addr                                          "0xb800f3d4"
#define CBUS_DDC_05_reg                                               0xb800f3d4
#define CBUS_DDC_05_inst_addr                                         "0x00F5"
#define CBUS_DDC_05_inst                                              0x00F5
#define CBUS_DDC_05_ddc_data_fw_shift                                 (0)
#define CBUS_DDC_05_ddc_data_fw_mask                                  (0x000000FF)
#define CBUS_DDC_05_ddc_data_fw(data)                                 (0x000000FF&(data))
#define CBUS_DDC_05_get_ddc_data_fw(data)                             (0x000000FF&(data))


#define CBUS_DDC_06                                                   0x1800f3d8
#define CBUS_DDC_06_reg_addr                                          "0xb800f3d8"
#define CBUS_DDC_06_reg                                               0xb800f3d8
#define CBUS_DDC_06_inst_addr                                         "0x00F6"
#define CBUS_DDC_06_inst                                              0x00F6
#define CBUS_DDC_06_ddc_eof_irq_shift                                 (3)
#define CBUS_DDC_06_ddc_eof_irq_en_shift                              (2)
#define CBUS_DDC_06_ddcrd_rst_en_shift                                (1)
#define CBUS_DDC_06_ddcrd_new_md_shift                                (0)
#define CBUS_DDC_06_ddc_eof_irq_mask                                  (0x00000008)
#define CBUS_DDC_06_ddc_eof_irq_en_mask                               (0x00000004)
#define CBUS_DDC_06_ddcrd_rst_en_mask                                 (0x00000002)
#define CBUS_DDC_06_ddcrd_new_md_mask                                 (0x00000001)
#define CBUS_DDC_06_ddc_eof_irq(data)                                 (0x00000008&((data)<<3))
#define CBUS_DDC_06_ddc_eof_irq_en(data)                              (0x00000004&((data)<<2))
#define CBUS_DDC_06_ddcrd_rst_en(data)                                (0x00000002&((data)<<1))
#define CBUS_DDC_06_ddcrd_new_md(data)                                (0x00000001&(data))
#define CBUS_DDC_06_get_ddc_eof_irq(data)                             ((0x00000008&(data))>>3)
#define CBUS_DDC_06_get_ddc_eof_irq_en(data)                          ((0x00000004&(data))>>2)
#define CBUS_DDC_06_get_ddcrd_rst_en(data)                            ((0x00000002&(data))>>1)
#define CBUS_DDC_06_get_ddcrd_new_md(data)                            (0x00000001&(data))


#define CBUS_WDOG                                                     0x1800f3e0
#define CBUS_WDOG_reg_addr                                            "0xb800f3e0"
#define CBUS_WDOG_reg                                                 0xb800f3e0
#define CBUS_WDOG_inst_addr                                           "0x00F8"
#define CBUS_WDOG_inst                                                0x00F8
#define CBUS_WDOG_clk_mod_vwd_shift                                   (5)
#define CBUS_WDOG_clk_mod_awd_shift                                   (4)
#define CBUS_WDOG_mute_en_vwd_shift                                   (3)
#define CBUS_WDOG_mute_en_awd_shift                                   (2)
#define CBUS_WDOG_path_en_off_vwd_shift                               (1)
#define CBUS_WDOG_path_en_off_awd_shift                               (0)
#define CBUS_WDOG_clk_mod_vwd_mask                                    (0x00000020)
#define CBUS_WDOG_clk_mod_awd_mask                                    (0x00000010)
#define CBUS_WDOG_mute_en_vwd_mask                                    (0x00000008)
#define CBUS_WDOG_mute_en_awd_mask                                    (0x00000004)
#define CBUS_WDOG_path_en_off_vwd_mask                                (0x00000002)
#define CBUS_WDOG_path_en_off_awd_mask                                (0x00000001)
#define CBUS_WDOG_clk_mod_vwd(data)                                   (0x00000020&((data)<<5))
#define CBUS_WDOG_clk_mod_awd(data)                                   (0x00000010&((data)<<4))
#define CBUS_WDOG_mute_en_vwd(data)                                   (0x00000008&((data)<<3))
#define CBUS_WDOG_mute_en_awd(data)                                   (0x00000004&((data)<<2))
#define CBUS_WDOG_path_en_off_vwd(data)                               (0x00000002&((data)<<1))
#define CBUS_WDOG_path_en_off_awd(data)                               (0x00000001&(data))
#define CBUS_WDOG_get_clk_mod_vwd(data)                               ((0x00000020&(data))>>5)
#define CBUS_WDOG_get_clk_mod_awd(data)                               ((0x00000010&(data))>>4)
#define CBUS_WDOG_get_mute_en_vwd(data)                               ((0x00000008&(data))>>3)
#define CBUS_WDOG_get_mute_en_awd(data)                               ((0x00000004&(data))>>2)
#define CBUS_WDOG_get_path_en_off_vwd(data)                           ((0x00000002&(data))>>1)
#define CBUS_WDOG_get_path_en_off_awd(data)                           (0x00000001&(data))


#define CBUS_INT_INDEX                                                0x1800f3e4
#define CBUS_INT_INDEX_reg_addr                                       "0xb800f3e4"
#define CBUS_INT_INDEX_reg                                            0xb800f3e4
#define CBUS_INT_INDEX_inst_addr                                      "0x00F9"
#define CBUS_INT_INDEX_inst                                           0x00F9
#define CBUS_INT_INDEX_arbiter_irq_shift                              (5)
#define CBUS_INT_INDEX_ddc_irq_shift                                  (4)
#define CBUS_INT_INDEX_msc_ch_irq_shift                               (3)
#define CBUS_INT_INDEX_msc_int_irq_shift                              (2)
#define CBUS_INT_INDEX_msc_stat_irq_shift                             (1)
#define CBUS_INT_INDEX_ctrl_01_resv_shift                             (0)
#define CBUS_INT_INDEX_arbiter_irq_mask                               (0x00000020)
#define CBUS_INT_INDEX_ddc_irq_mask                                   (0x00000010)
#define CBUS_INT_INDEX_msc_ch_irq_mask                                (0x00000008)
#define CBUS_INT_INDEX_msc_int_irq_mask                               (0x00000004)
#define CBUS_INT_INDEX_msc_stat_irq_mask                              (0x00000002)
#define CBUS_INT_INDEX_ctrl_01_resv_mask                              (0x00000001)
#define CBUS_INT_INDEX_arbiter_irq(data)                              (0x00000020&((data)<<5))
#define CBUS_INT_INDEX_ddc_irq(data)                                  (0x00000010&((data)<<4))
#define CBUS_INT_INDEX_msc_ch_irq(data)                               (0x00000008&((data)<<3))
#define CBUS_INT_INDEX_msc_int_irq(data)                              (0x00000004&((data)<<2))
#define CBUS_INT_INDEX_msc_stat_irq(data)                             (0x00000002&((data)<<1))
#define CBUS_INT_INDEX_ctrl_01_resv(data)                             (0x00000001&(data))
#define CBUS_INT_INDEX_get_arbiter_irq(data)                          ((0x00000020&(data))>>5)
#define CBUS_INT_INDEX_get_ddc_irq(data)                              ((0x00000010&(data))>>4)
#define CBUS_INT_INDEX_get_msc_ch_irq(data)                           ((0x00000008&(data))>>3)
#define CBUS_INT_INDEX_get_msc_int_irq(data)                          ((0x00000004&(data))>>2)
#define CBUS_INT_INDEX_get_msc_stat_irq(data)                         ((0x00000002&(data))>>1)
#define CBUS_INT_INDEX_get_ctrl_01_resv(data)                         (0x00000001&(data))


#define CBUS_TEST                                                     0x1800f3e8
#define CBUS_TEST_reg_addr                                            "0xb800f3e8"
#define CBUS_TEST_reg                                                 0xb800f3e8
#define CBUS_TEST_inst_addr                                           "0x00FA"
#define CBUS_TEST_inst                                                0x00FA
#define CBUS_TEST_cbus_test_md_shift                                  (6)
#define CBUS_TEST_fw_out_shift                                        (5)
#define CBUS_TEST_dbg_sel_shift                                       (2)
#define CBUS_TEST_cbus_test_md_mask                                   (0x000000C0)
#define CBUS_TEST_fw_out_mask                                         (0x00000020)
#define CBUS_TEST_dbg_sel_mask                                        (0x0000001C)
#define CBUS_TEST_cbus_test_md(data)                                  (0x000000C0&((data)<<6))
#define CBUS_TEST_fw_out(data)                                        (0x00000020&((data)<<5))
#define CBUS_TEST_dbg_sel(data)                                       (0x0000001C&((data)<<2))
#define CBUS_TEST_get_cbus_test_md(data)                              ((0x000000C0&(data))>>6)
#define CBUS_TEST_get_fw_out(data)                                    ((0x00000020&(data))>>5)
#define CBUS_TEST_get_dbg_sel(data)                                   ((0x0000001C&(data))>>2)


#define CBUS_DUMMY0                                                   0x1800f3ec
#define CBUS_DUMMY0_reg_addr                                          "0xb800f3ec"
#define CBUS_DUMMY0_reg                                               0xb800f3ec
#define CBUS_DUMMY0_inst_addr                                         "0x00FB"
#define CBUS_DUMMY0_inst                                              0x00FB
#define CBUS_DUMMY0_cbus_dummy0_shift                                 (0)
#define CBUS_DUMMY0_cbus_dummy0_mask                                  (0xFFFFFFFF)
#define CBUS_DUMMY0_cbus_dummy0(data)                                 (0xFFFFFFFF&(data))
#define CBUS_DUMMY0_get_cbus_dummy0(data)                             (0xFFFFFFFF&(data))
#endif
